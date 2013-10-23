.section .text	

._start: .global start
	.global main
	.func main

main:
	MOV 	r0, #1
	ADR	r1, str
	ADR	r2, str
	ADD	r2, r2, #str_len

START:
	TEQ 	r1, r2
	BEQ 	END 
	LDRB 	r3, [r1], #1 
	LDRB 	r4, [r2], #-1 
	TEQ 	r3, r4 
	BNE 	NO 
	B 	START 
NO:
	MOV r0, #0 
END: 
	BX	lr	

str:	.ascii "aba"
	.set	str_len, .-str-1
        
