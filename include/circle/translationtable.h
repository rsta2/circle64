//
// translationtable.h
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2016-2018  R. Stange <rsta2@o2online.de>
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
#ifndef _circle_translationtable_h
#define _circle_translationtable_h

#include <circle/armv8mmu.h>
#include <circle/types.h>
#include <circle/macros.h>

// index into MAIR_EL1 register
#define ATTRINDX_NORMAL		0
#define ATTRINDX_DEVICE		1
#define ATTRINDX_COHERENT	2

class CTranslationTable
{
public:
	CTranslationTable (u64 nMemSize) NOOPT;
	~CTranslationTable (void);

	u64 GetBaseAddress (void) const;

private:
	TARMV8MMU_LEVEL3_DESCRIPTOR *CreateLevel3Table (u64 nBaseAddress) NOOPT;

private:
	u64 m_nMemSize;

	TARMV8MMU_LEVEL2_DESCRIPTOR *m_pTable;
};

#endif
