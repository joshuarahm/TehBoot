.code32

.section .data

GPF_STR:
.asciz "General Protection Fault ErrorCode: 0x"

IRQ_STR0:
.asciz "Interrupt Caught. Number: 0x"
IRQ_STR1:
.asciz " ErrorCode: 0x"

.extern isr_main

.section .text
.globl isr_common
isr_common:
    # reset two registers to 0
#    xorl %eax,%eax
#    xorl %ebx,%ebx
#
#    # pop bytes into those registersj
#    movl (%esp),%eax
#    movl -4(%esp),%ebx

    pushal

    # Save most of the registers
    subl $4,%esp

    # print the first part of
    # the string
    movl $IRQ_STR0,(%esp)
    call vga_print    # IRQ_STR 0
    # Move the irq number to the top
    # of the stack and print
    movl 0x4(%esp),%eax
    movl %eax,(%esp)
    call vga_printix  # irq number
    # print the second irq str
    movl $IRQ_STR1,(%esp)
    call vga_print    # IRQ str 1
    # Move the Error code to the top
    # of the stack
    movl 0x8(%esp),%eax
    movl %eax,(%esp)
    call vga_printix  # Error Code
    call vga_newline  # newline

    # Cover the printing tracks
    addl $4,%esp


    # # Set the lower bits of eax to the
    # # current data segment descriptor */
    # # mov %ds,%ax
    # # # Save the date segment descriptor */
    # # pushl %eax

    # # Kernel data segment descriptor */
    # # mov $0x10,%ax
    # # mov %ax, %ds 
    # # mov %ax, %es 
    # # mov %ax, %fs 
    # # mov %ax, %gs 

    # call isr_main

    # # popl %eax        # reload the original data segment descriptor
    # # mov %ax, %ds 
    # # mov %ax, %es 
    # # mov %ax, %fs 
    # # mov %ax, %gs 

    popal                     # Pops edi,esi,ebp...;
    add $8,%esp     # Cleans up the pushed error code and pushed ISR number
    sti
    iret           # pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

    


.macro ISR_GATE_NO_ERROR num
.globl isr\num
isr\num:
    cli
    pushl $0x0
    pushl $\num
    jmp isr_common
.endm

.macro ISR_GATE_ERROR num
.globl isr\num
isr\num:
    cli
    pushl $\num
    jmp isr_common
.endm

ISR_GATE_NO_ERROR 0
ISR_GATE_NO_ERROR 1
ISR_GATE_NO_ERROR 2
ISR_GATE_NO_ERROR 3
ISR_GATE_NO_ERROR 4
ISR_GATE_NO_ERROR 5
ISR_GATE_NO_ERROR 6
ISR_GATE_NO_ERROR 7
ISR_GATE_ERROR    8
ISR_GATE_NO_ERROR 9
ISR_GATE_ERROR    10
ISR_GATE_ERROR    11
ISR_GATE_ERROR    12
# # General Protection Fault Handler # #
.globl isr13
.extern vga_print
.extern vga_printix
isr13:
    cli
    pushl $GPF_STR
    call  vga_print
    popl %eax
    call vga_printix
    popl %eax
    call vga_newline
    hlt
    iret


ISR_GATE_ERROR    14
ISR_GATE_NO_ERROR 15
ISR_GATE_NO_ERROR 16
ISR_GATE_ERROR    17
ISR_GATE_NO_ERROR 18
ISR_GATE_NO_ERROR 19
ISR_GATE_NO_ERROR 20
ISR_GATE_NO_ERROR 21
ISR_GATE_NO_ERROR 22
ISR_GATE_NO_ERROR 23
