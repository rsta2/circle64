//
// sysconfig.h
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
#ifndef _circle_sysconfig_h
#define _circle_sysconfig_h

// system options
//#define ARM_ALLOW_MULTI_CORE	// slower on single core if defined

// memory addresses and sizes
#define MEGABYTE		0x100000

#define MEM_SIZE		(512 * MEGABYTE)		// default size
#define GPU_MEM_SIZE		(64 * MEGABYTE)			// set in config.txt
#define ARM_MEM_SIZE		(MEM_SIZE - GPU_MEM_SIZE)	// normally overwritten

#define PAGE_SIZE		0x10000				// page size used by us

#define KERNEL_MAX_SIZE		(2 * MEGABYTE)
#define KERNEL_STACK_SIZE	0x20000
#define EXCEPTION_STACK_SIZE	0x8000
#define PAGE_RESERVE		(16 * MEGABYTE)

#define MEM_KERNEL_START	0x80000						// main code starts here
#define MEM_KERNEL_END		(MEM_KERNEL_START + KERNEL_MAX_SIZE)
#define MEM_KERNEL_STACK	(MEM_KERNEL_END + KERNEL_STACK_SIZE)		// expands down
#ifndef ARM_ALLOW_MULTI_CORE
#define MEM_EXCEPTION_STACK	(MEM_KERNEL_STACK + EXCEPTION_STACK_SIZE)	// expands down
#else
#define CORES			4						// must be a power of 2
#define MEM_EXCEPTION_STACK	(MEM_KERNEL_STACK + KERNEL_STACK_SIZE * (CORES-1) + EXCEPTION_STACK_SIZE)
#endif

#define MEM_COHERENT_REGION	0x400000
#define MEM_HEAP_START		0x500000

#endif
