# signal that this is supposed to be
# 16 bit code.
.code16

# start the data section
.section .data

ERRORSTR:
# Super helpful error message
.asciz "There was an error"

DAP:
# This is the struct for accessing crap on the disk.
# Ill use this as a place of the next stage of the boot
# loader
# 

# The size of the DAP. Always 0x10 
.byte 0x10 

# unused, must be 0 
.byte 0x00

# We are going to read 1 sector 
.short 0x1

# Load to the address 0xFF000.
# Yes, I mean that address, thank you obscure
# memory segmentation 
.short 0x1000
.short 0x0000

# Start at sector 1. Skip the initial
# boot code which is on sector 0 
.long 1
.long 0

END_DAP:

.section .text

.global print_str
.global main
.type print_str, @function
.type main, @function

main:
	xor %dx,%dx

	# Push hello. Apparently push only works
	# with constants in 16 bit mode 
	# push $HELLO
	# call print_str

	# Now let's load some data from the
	# drive


	# set the segment to 0x0000:$DAP
	# (DS:SI)
	mov $0,%ax
	mov %ax,%ds # for some reason a move to %ds requires ax
	mov $DAP,%si

	mov $0x42,%ah # Use the read drive sectors command 
	mov $0x80,%dl # We use drive 0 

	# Invoke the disk read 
	int $0x13

	hlt # Wait for the disk to finish to come back 

	# set the cursor back to 0
	xor %dx,%dx

	# Jump if there was no error reading
	# from the disk
	jnc ok

	# if eip is here, then there was an error
	# reading code
	push $ERRORSTR
	call print_str

	# we're done here
	jmp done

ok:
	# at this point, the disk was successfully
	# read!
	
	# Simply print out what we find.
	# Later I can jump to it
	push $0x1000
	call print_str

done:
	hlt


# Print a string that has been pushed on the stack,
# this is pretty buggy right now.
print_str:
	mov $0x000F,%bx
	mov $1,%cx
	mov %dx,%ds

	cld

	# Begin the operation of moving the argument
	# into %si, by first making %si point to the
	# bottom of the stack 
	mov %sp,%si

	# add 2 from %si so it is now pointing to
	# the argument 
	add $2,%si

	# Dereference that argument into %si itself 
	mov (%si),%si
	
put_char:
	mov $2,%ah
	int $0x10
	lodsb
	mov $9,%ah
# Check for a new line character.
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
