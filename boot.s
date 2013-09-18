.code16
.section .data
HELLO:
.ascii "Welcome to Teh Boot Bootloader!"
.byte 0x21,0x0a
.ascii "The most awesome, but equally useless boot loader" 
.byte 0x21,0x0a
.ascii "Give it TEH BOOT"
.byte 0x21,0x21,0x21,0x0a,0x00

READ_BYTES_STR:
.ascii "I read some bytes"
.byte 0

DAP:
/* This is the struct for accessing crap on the disk.
 * Ill use this as a place of the next stage of the boot
 * loader
 */

/* The size of the DAP. Always 0x10 */
.byte 0x10 

/* unused, must be 0 */
.byte 0x00

/* We are going to read 16 sectors */
.short 0x10

/* Load to the address 0xFF000.
 * Yes, I mean that address, thank you obscure
 * memory segmentation */
.long 0xFF000000

/* Start at sector 1. Skip the initial
 * boot code which is on sector 0 */
.quad 0x01

END_DAP:

.section .text

.global print_str
.global main
.type print_str, @function
.type main, @function

main:
	/* Push hello. Apparently push only works
	 * with constants in 16 bit mode */
	push $HELLO
	call print_str

	/* Now let's load some data from the
	 * drive */

	mov $0x42,%ah /* Use the read drive sectors command */
	mov $0x0,%dl /* We use drive 0 */

	/* set the segment to 0x0000:$DAP
	 * (DS:SI) */
	mov $0,%ax
	mov %ax,%ds /* for some reason a move to %ds requires ax */
	mov $DAP,%si

	/* Invoke the disk read */
	int $0x13

	add $2,%sp

	hlt

	push $READ_BYTES_STR
	call print_str

	hlt


print_str:
	mov $0x000F,%bx
	mov $1,%cx
	xor %dx,%dx
	mov %dx,%ds

	cld

	/* Begin the operation of moving the argument
	 * into %si, by first making %si point to the
	 * bottom of the stack */
	mov %sp,%si

	/* add 2 from %si so it is now pointing to
	 * the argument */
	add $2,%si

	/* Dereference that argument into %si itself */
	mov (%si),%si
	
put_char:
	mov $2,%ah
	int $0x10
	lodsb
	mov $9,%ah
// Check for a new line character.
	cmp $0x0a,%al
	je new_line

	int $0x10

	inc %dl
	cmp $80,%dl

	jne try_end

new_line:
	xor %dl,%dl
	inc %dh

	cmp $25,%dh
	jne try_end

	xor %dh,%dh

try_end:
	mov (%si),%ah
	cmp $0,%ah
	jne put_char
	ret

// print_str:
// 	mov $0x000F,%bx
// 	mov 1, %cx
// 	xor %dx,%dx
// 	cld
// 	pop %si
// 	call put_char
// 
// put_char:
// 	mov $2,%ah
// 	int $0x10
// 	lodsb
// 
// 	mov $9,%ah
// 	int $0x10
// 
// 	inc %dl
// 	cmp $80,%dl
// 	jne put_char_skip
// 
// 	xor %dl,%dl
// 	inc %dh
// 
// 	cmp %dh,%dh
// 	jne put_char_skip
// 	xor %dh,%dh
// 
// put_char_skip:
// 	mov (%si),%cl
// 	cmp $0,%cl
// 	jne put_char
// 	ret
