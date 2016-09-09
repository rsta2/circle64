//
// sysinit.cpp
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2016  R. Stange <rsta2@o2online.de>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include <circle/startup.h>
#include <circle/memio.h>
#include <circle/bcm2835.h>
#include <circle/synchronize.h>
#include <circle/sysconfig.h>
#include <circle/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void *__dso_handle;

void __cxa_atexit (void *pThis, void (*pFunc)(void *pThis), void *pHandle)
{
	// TODO
}

void halt (void)
{
#ifdef ARM_ALLOW_MULTI_CORE
	static volatile boolean s_bCoreHalted[CORES] = {FALSE};

	u64 nMPIDR;
	asm volatile ("mrs %0, mpidr_el1" : "=r" (nMPIDR));
	unsigned nCore = nMPIDR & (CORES-1);

	// core 0 must not halt until all secondary cores have been halted
	if (nCore == 0)
	{
		unsigned nSecCore = 1;
		while (nSecCore < CORES)
		{
			DataMemBarrier ();
			if (!s_bCoreHalted[nSecCore])
			{
				DataSyncBarrier ();
				asm volatile ("wfi");

				nSecCore = 1;
			}
			else
			{
				nSecCore++;
			}
		}
	}

	s_bCoreHalted[nCore] = TRUE;
	DataMemBarrier ();
#endif

	DisableInterrupts ();

	DataSyncBarrier ();

	for (;;)
	{
		asm volatile ("wfi");
	}
}

void reboot (void)					// by PlutoniumBob@raspi-forum
{
	write32 (ARM_PM_WDOG, ARM_PM_PASSWD | 1);	// set some timeout

#define PM_RSTC_WRCFG_FULL_RESET	0x20
	write32 (ARM_PM_RSTC, ARM_PM_PASSWD | PM_RSTC_WRCFG_FULL_RESET);

	for (;;);					// wait for reset
}

void sysinit (void)
{
	// clear BSS
	extern unsigned char __bss_start;
	extern unsigned char _end;
	for (unsigned char *pBSS = &__bss_start; pBSS < &_end; pBSS++)
	{
		*pBSS = 0;
	}

	// call construtors of static objects
	extern void (*__init_start) (void);
	extern void (*__init_end) (void);
	for (void (**pFunc) (void) = &__init_start; pFunc < &__init_end; pFunc++)
	{
		(**pFunc) ();
	}

	extern int main (void);
	if (main () == EXIT_REBOOT)
	{
		reboot ();
	}

	halt ();
}

#ifdef ARM_ALLOW_MULTI_CORE

void sysinit_secondary (void)
{
	main_secondary ();

	halt ();
}

#endif

#ifdef __cplusplus
}
#endif
