.section .text	

._start: .global start
	.global main
	.func main

main:
	LDR r0, A	
	LDR r1, B
	LDR r2, C
	LDR r3, D
	LDR r4, E 

	ADD r0, r0, r1
	ADD r0, r0, r2
	MUL r2, r3, r4
	SUB r0, r0, r2
	bx 	lr	

A:	.word	1
B:	.word	2
C: 	.word	1
D:	.word	3
E:	.word	1
