	.cpu arm7tdmi-s
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"palindrome.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"racecar\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #20
	ldr	r3, .L6
	str	r3, [fp, #-16]
	ldr	r3, [fp, #-16]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-16]
	add	r3, r3, #6
	str	r3, [fp, #-12]
	b	.L2
.L5:
	ldr	r3, [fp, #-8]
	ldrb	r2, [r3, #0]	@ zero_extendqisi2
	ldr	r3, [fp, #-12]
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r2, r3
	beq	.L3
	mov	r3, #0
	b	.L4
.L3:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-12]
	sub	r3, r3, #1
	str	r3, [fp, #-12]
.L2:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-12]
	cmp	r2, r3
	bne	.L5
	mov	r3, #1
.L4:
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.L7:
	.align	2
.L6:
	.word	.LC0
	.size	main, .-main
	.ident	"GCC: (GNU) 4.5.4 20120305 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
