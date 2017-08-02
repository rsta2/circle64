//
// memory.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2017  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_memory_h
#define _circle_memory_h

#include <circle/sysconfig.h>
#include <circle/translationtable.h>
#include <circle/types.h>

class CMemorySystem
{
public:
	CMemorySystem (boolean bEnableMMU = TRUE);
	~CMemorySystem (void);

#ifdef ARM_ALLOW_MULTI_CORE
	void InitializeSecondary (void);
#endif

	u64 GetMemSize (void) const;

	static u64 GetCoherentPage (unsigned nSlot);
#define COHERENT_SLOT_PROP_MAILBOX	0
#define COHERENT_SLOT_GPIO_VIRTBUF	1

private:
	void EnableMMU (void);

private:
	boolean m_bEnableMMU;

	u64 m_nMemSize;

	CTranslationTable *m_pTranslationTable;
};

#endif
