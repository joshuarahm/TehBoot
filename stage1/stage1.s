# signal that this is supposed to be
# 16 bit code.
.code16

# start the data section
.section .data

LoadState2Ptr = 0x1000

ERRORSTR:
# Super helpful error message
.asciz "There was an error"

PROTECTED_STR:
.asciz "Processor In Protected Mode"

DAP:
# This is the struct for accessing crap on the disk.
# Ill use this as a place of the next stage of the boot
# loader
# 

# The size of the DAP. Always 0x10 
.byte 0x10 

# unused, must be 0 
.byte 0x00

# We are going to read 54 sectors
.short 0x36

# Load to the address 0xFF000.
# Yes, I mean that address, thank you obscure
# memory segmentation 
.short LoadState2Ptr
.short 0x0000

# Start at sector 1. Skip the initial
# boot code which is on sector 0 
.long 1
.long 0

END_DAP:

GDT:
	# Data segment for GDT iteself - 0x00
	.short GDT_End - GDT - 1
	.short GDT
	.byte 0
	.byte 0, 0
	.byte 0

    # ############################################### #
	# This is the CODE section for the Kernel. - 0x08 #
    # ############################################### #

	.short 0xFFFF # Segment length bits 0-15, 5-4k blocks
	# Starting at location 0
	.short 0x0000 # Segment address bits 0-15
	# Still at 0
	.byte 0x00 # segment address bits 16-23
	.byte 0b10011010 # Access byte # Present = 1
	                               # Privledge = 0
								   # Executable = 1
								   # DC = 0
								   # RW = 1
								   # Ac = 0
	.byte 0b11000000 # flags size=4k blocks, 32-bit protected mode, rest of limit
	.byte 0x00 # final bits for address

    # ############################################### #
	# This is the DATA section for the Kernel. - 0x10 #
    # ############################################### #

	.short 0xFFFF # Segment length bits 0-15, 5-4k blocks
	# Starting at location 0
	.short 0x0000 # Segment address bits 0-15
	# Still at 0
	.byte 0x00 # segment address bits 16-23
	.byte 0b10010010 # Access byte # Present = 1
	                               # Privledge = 0
								   # Executable = 0
								   # DC = 0
								   # RW = 1
								   # Ac = 0
	.byte 0b11000000 # flags size=4k blocks, 32-bit protected mode, rest of limit
	.byte 0x00 # final bits for address

    # ############################################## #
    # This is the TSS section for the kernel. - 0x18 #
    # ############################################## #

	.short 0xFFFF # Segment length bits 0-15, 5-4k blocks
	# Starting at location 0
	.short 0x0000 # Segment address bits 0-15
	# Still at 0
	.byte 0x00 # segment address bits 16-23
	.byte 0b10001001 # Access byte # Present = 1
	                               # Privledge = 0
								   # Executable = 0
								   # DC = 0
								   # RW = 1
								   # Ac = 0
	.byte 0b11000000 # flags size=4k blocks, 32-bit protected mode, rest of limit
	.byte 0x00 # final bits for address
GDT_End:

.section .text

.global main
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

	# we're done here
	jmp done

ok:
	# at this point, the disk was successfully
	# read!
	
	# Simply print out what we find.
	# Later I can jump to it
	# push $0x1000
	# call print_str
	call enter_protected
done:
	hlt

enter_protected:
	mov $3,%ax
	int $0x10
	xor %edx,%edx
	mov %dx,%ds
	shl $4,%edx
	add	%edx,(GDT+2)
	lgdt (GDT)
	mov %cr0,%eax
	or  $1,%al
	cli
	mov %eax,%cr0
	mov $0x08,%bx
	mov %bx,%fs
	jmp protected_main

protected_main:
	mov $0xB8000,%ebx
	mov $PROTECTED_STR,%si

	loop_chars:
		lodsb
		cmp $0x00,%al
		je end_loop_chars
		mov %al,(%ebx)
		add $2,%ebx
		jmp loop_chars
	
	end_loop_chars:

    # clobber the memory where this code
    # resides, we can no longer get back
    # to it anyway
	mov $0x7e00,%esp
	mov $0x7e00,%ebp

	ljmp $0x08,$0x1000 # jump to 0x1000 with code segment 0x8
