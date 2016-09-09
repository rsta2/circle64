//
// spinlock.cpp
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2015-2016  R. Stange <rsta2@o2online.de>
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
#include <circle/spinlock.h>

#ifdef ARM_ALLOW_MULTI_CORE

#include <circle/multicore.h>
#include <assert.h>

boolean CSpinLock::s_bEnabled = FALSE;

CSpinLock::CSpinLock (boolean bDisableIRQ)
:	m_bDisableIRQ (bDisableIRQ),
	m_bLocked (FALSE)
{
}

CSpinLock::~CSpinLock (void)
{
	assert (!m_bLocked);
}

void CSpinLock::Acquire (void)
{
	if (m_bDisableIRQ)
	{
		asm volatile
		(
			"mrs %0, DAIF\n"
			"msr DAIFSet, #2\n"

			: "=r" (m_nDAIF[CMultiCoreSupport::ThisCore ()])
		);
	}

	if (s_bEnabled)
	{
		// See: ARMv8-A Architecture Reference Manual, Section K10.3.1
		asm volatile
		(
			"mov x1, %0\n"
			"mov w2, #1\n"
			"prfm pstl1keep, [x1]\n"
			"1: ldaxr w3, [x1]\n"
			"cbnz w3, 1b\n"
			"stxr w3, w2, [x1]\n"
			"cbnz w3, 1b\n"

			: : "r" ((uintptr) &m_bLocked)
		);
	}
}

void CSpinLock::Release (void)
{
	if (s_bEnabled)
	{
		// See: ARMv8-A Architecture Reference Manual, Section K10.3.2
		asm volatile
		(
			"mov x1, %0\n"
			"stlr wzr, [x1]\n"

			: : "r" ((uintptr) &m_bLocked)
		);
	}

	if (m_bDisableIRQ)
	{
		asm volatile
		(
			"tst %0, #0x80\n"	// test IRQ disable bit
			"bne 1f\n"
			"msr DAIFClr, #2\n"
			"1:\n"

			: : "r" (m_nDAIF[CMultiCoreSupport::ThisCore ()])
		);
	};
}

void CSpinLock::Enable (void)
{
	assert (!s_bEnabled);
	s_bEnabled = TRUE;
}

#endif
