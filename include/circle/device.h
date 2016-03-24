//
// device.h
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
#ifndef _circle_device_h
#define _circle_device_h

class CDevice
{
public:
	CDevice (void);
	virtual ~CDevice (void);

	// returns number of read bytes or < 0 on failure
	virtual int Read (void *pBuffer, unsigned nCount);

	// returns number of written bytes or < 0 on failure
	virtual int Write (const void *pBuffer, unsigned nCount);

	// returns the resulting offset, (unsigned long) -1 on error
	virtual unsigned long Seek (unsigned long ulOffset);		// byte offset
};

#endif
