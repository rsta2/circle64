#
# Makefile
#
# Circle - A C++ bare metal environment for Raspberry Pi
# Copyright (C) 2014-2016  R. Stange <rsta2@o2online.de>
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

OBJS	= actled.o alloc.o assert.o bcmframebuffer.o bcmmailbox.o bcmpropertytags.o chargenerator.o \
	  debug.o delayloop.o device.o devicenameservice.o exceptionstub.o exceptionhandler.o \
	  gpiomanager.o gpiopin.o interrupt.o koptions.o logger.o memory.o new.o ptrarray.o \
	  ptrlist.o screen.o serial.o string.o synchronize.o sysinit.o timer.o util.o virtualgpiopin.o \
	  translationtable.o util_fast.o

all: startup.o libcircle.a

startup.o: startup.S

libcircle.a: $(OBJS)
	rm -f libcircle.a
	$(AR) cr libcircle.a $(OBJS)

include ../Rules.mk
