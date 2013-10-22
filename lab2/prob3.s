.section .text	

._start: .global start
	.global main
	.func main

main:
	MOV r0, A
	LDR r1, B

	ADD r0, r0, r1
	MUL r0, r1

	
	bx 	lr	

A:	.word	1
B	DCD	2
