.section .text	

._start: .global start
	.global main

main:
	MOV r0, #1 ; A = 1
	MOV r1, #2 ; B = 2
	MOV r2, #1 ; C = 1
	MOV r3, #3 ; D = 2
	MOV r4, #1 ; E = 1

	ADD r0, r0, r1
	ADD r0, r0, r2
	MUL r2, r3, r4
	SUB r0, r0, r2

	BX lr
	
