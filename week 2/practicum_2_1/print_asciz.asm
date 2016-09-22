	.cpu cortex-m0
	.data
string:
	.asciz "Hello world!? [@] {`} 12345==67890\n abcDEFgbasdl\n"
	.text
	.align 1
	.global print_asciz
	.global application
	.global invert
	
application:
	push {r0, lr }
	ldr r0, =string
	bl print_asciz
	pop { r0, pc }

print_asciz:
	push { r5, lr }
	mov r5, r0
loop:
	ldrb r0, [r5]
	add r0, r0, #0
	beq done
	bl invert
	bl put_char
	add r5, r5, #1
	b loop
done:
	pop { r5, pc }
	
invert:
	push { r1 - r5, lr}
	ldr r1, =32
	ldr r2, ='a'
	ldr r3, ='z'
	ldr r4, ='A'
	ldr r5, ='Z'
	cmp r0, r2
	bge greater_a
	cmp r0, r4
	bge greater_A
	b done_inv
greater_a:
	cmp r0, r3
	ble inversion_noncaps
	b done_inv
greater_A:
	cmp r0, r5
	ble inversion_caps
	b done_inv
inversion_noncaps:
	sub r0, r0, r1
	b done_inv
inversion_caps:
	add r0, r0, r1
done_inv:
	pop {r1 - r5, pc}