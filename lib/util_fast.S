/*
 * util_fast.S
 *
 * Circle - A C++ bare metal environment for Raspberry Pi
 * Copyright (C) 2016  R. Stange <rsta2@o2online.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

	.text

	.globl	memcpyblk
memcpyblk:
	stp	x0, x3, [sp, #-16]!
	stp	x4, x5, [sp, #-16]!
	mov	x3, #64
1:	ldp	x4, x5, [x1], #16
	subs	x2, x2, #16
	stp	x4, x5, [x0], #16
	prfm	pldl1strm, [x1, x3]
	bne	1b
	ldp	x4, x5, [sp], #16
	ldp	x0, x3, [sp], #16
	ret

/* End */
