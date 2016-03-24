/*
 * exceptionstub.S
 *
 * Circle - A C++ bare metal environment for Raspberry Pi
 * Copyright (C) 2014-2016  R. Stange <rsta2@o2online.de>
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
#include <circle/exception.h>

	.macro	vector handler

	.align	7

	b	\handler

	.endm
	
	.macro	stub name, exception

	.globl	\name
\name:
	mrs	x0, esr_el1
	mrs	x1, spsr_el1
	mov	x2, x30				/* lr */
	mrs	x3, elr_el1
	mrs	x4, sp_el0
	mov	x5, sp

	stp	x4, x5, [sp, #-16]!
	stp	x2, x3, [sp, #-16]!
	stp	x0, x1, [sp, #-16]!

	mov	x0, #\exception
	mov	x1, sp
	b	ExceptionHandler		/* never returns */

	.endm

	.text

	.align	11

	.globl	VectorTable
VectorTable:

	/* from current EL with sp_el0 */
	vector	SynchronousStub
	vector	IRQStub
	vector	UnexpectedStub			/* FIQ */
	vector	SErrorStub

	/* from current EL with sp_elx, x != 0 */
	vector	SynchronousStub
	vector	UnexpectedStub
	vector	UnexpectedStub
	vector	SErrorStub

	/* from lower EL, target EL minus 1 is AArch64 */
	vector	UnexpectedStub
	vector	UnexpectedStub
	vector	UnexpectedStub
	vector	UnexpectedStub

	/* from lower EL, target EL minus 1 is AArch32 */
	vector	UnexpectedStub
	vector	UnexpectedStub
	vector	UnexpectedStub
	vector	UnexpectedStub

/*
 * Abort stubs
 */
	stub	UnexpectedStub,		EXCEPTION_UNEXPECTED
	stub	SynchronousStub,	EXCEPTION_SYNCHRONOUS
	stub	SErrorStub,		EXCEPTION_SYSTEM_ERROR

/*
 * IRQ stub
 */
	.globl	IRQStub
IRQStub:
	stp	x29, x30, [sp, #-16]!
	stp	x27, x28, [sp, #-16]!
	stp	x25, x26, [sp, #-16]!
	stp	x23, x24, [sp, #-16]!
	stp	x21, x22, [sp, #-16]!
	stp	x19, x20, [sp, #-16]!
	stp	x17, x18, [sp, #-16]!
	stp	x15, x16, [sp, #-16]!
	stp	x13, x14, [sp, #-16]!
	stp	x11, x12, [sp, #-16]!
	stp	x9, x10, [sp, #-16]!
	stp	x7, x8, [sp, #-16]!
	stp	x5, x6, [sp, #-16]!
	stp	x3, x4, [sp, #-16]!
	stp	x1, x2, [sp, #-16]!
	str	x0, [sp, #-16]!

	bl	InterruptHandler

	ldr	x0, [sp], #16
	ldp	x1, x2, [sp], #16
	ldp	x3, x4, [sp], #16
	ldp	x5, x6, [sp], #16
	ldp	x7, x8, [sp], #16
	ldp	x9, x10, [sp], #16
	ldp	x11, x12, [sp], #16
	ldp	x13, x14, [sp], #16
	ldp	x15, x16, [sp], #16
	ldp	x17, x18, [sp], #16
	ldp	x19, x20, [sp], #16
	ldp	x21, x22, [sp], #16
	ldp	x23, x24, [sp], #16
	ldp	x25, x26, [sp], #16
	ldp	x27, x28, [sp], #16
	ldp	x29, x30, [sp], #16

	eret

/* End */
