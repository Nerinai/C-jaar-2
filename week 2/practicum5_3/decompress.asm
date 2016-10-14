.cpu cortex-m3
.data
decompressed:
.ascii ""
.skip 4096

.text
.align 1
.global decompress




decompress:
	push {r4 - r7, lr} //push registers
	ldr r0, =string // load adress of to be decompressed string
	ldr r1, =decompressed //load the location where the string will be stored.
	mov r7, #0

loop:
	ldrb r2, [r0]
	
	//push {r0 - r3} //debug
	//mov r0, r7
	//bl put_int
	//pop {r0 - r3} //enddebug
	
	cmp r2, #'@'
	beq readback
	
	cmp r2, #0
	beq done
	
	strb r2, [r1]
	
	push {r0 - r3} //debug
	mov r0, r2
	bl put_char
	pop {r0 - r3} //enddebug
	
	add r0, r0, #1
	add r1, r1, #1
	add r7, r7, #1
	b loop

readback:
	add r0, r0, #1
	ldrb r3, [r0]
	add r3, r3, #1
	add r0, r0, #1
	ldrb r4, [r0]
	mov r5, r1
	sub r3, r3, #' '
	sub r4, r4, #' '
	
	
	//push {r0 - r3} //debug
	//mov r0, r3
	//bl put_int
	//mov r0, r4
	//bl put_int
	//pop {r0 - r3} //enddebug
	
	
	sub r5, r5, r3
	
	
	//push {r0 - r3} //debug
	//mov r0, r5
	//bl put_int
	//pop {r0 - r3} //enddebug
	
	
length_loop:
	
	
	//push {r0 - r3} //debug
	//mov r0, r4
	//bl put_int
	//pop {r0 - r3} //enddebug
	
	cmp r4, #0
	beq loop
	ldrb r2, [r5]
	strb r2, [r1]
	
	push {r0 - r3} //debug
	mov r0, r2
	bl put_char
	pop {r0 - r3} //enddebug
	
	add r5, r5, #1
	add r1, r1, #1
	add r7, r7, #1
	sub r4, r4, #1
	b length_loop

done:
	ldr r6, =decompressed
	ldrb r0, [r6]
	cmp r7, #0
	beq really_done
	push {r0 - r3}
	bl put_char
	pop {r0 - r3}
	sub r7, r7, #1
	add r6, r6, #1
	b done

really_done:
pop {r5 - r7, pc}
