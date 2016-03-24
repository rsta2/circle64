/*
 * delayloop.S
 */

	.text

	.align	6

	.globl	DelayLoop
DelayLoop:
	subs	w0, w0, #1
	bne	DelayLoop
	ret

/* End */
