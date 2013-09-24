#ifndef IDT_H_
#define IDT_H_

/*
 * Author: jrahm
 * created: 2013/09/24
 * idt.h: Structures for the Interrupt Descriptor Table
 */

#include "tbtype.h"

#define IDT_PRESENT (1<<7)
#define IDT_STORAGE_SEGMENT (1<<4)

#define isr_return asm("iret")

typedef enum {
      IdtType_TaskGate32      = 0x05 
    , IdtType_InterruptGate16 = 0x06
    , IdtType_TrapGate16      = 0x07
    , IdtType_InterruptGate32 = 0x0e
    , IdtType_TrapGate32      = 0x0F
} idt_type_t;

/*
 * This struct represents the raw form
 * of an IDT (Interrupt Descriptor Table) entry
 */
struct __IDT_STR {
    /* The lower order bits of the
     * offset */
    u16_t off1;

    /* The code segment selector to
     * long jump to for the interrupt
     * handler */
    u16_t segment;

    /* an unused byte */
    u8_t  unused;

    /* Stuff for setting the values
     * of different types */
    u8_t  type_attr;

    /* The higher bits of the offset */
    u16_t off2;
} __attribute__((packed)) ;

/* 
 * A typedef to make things
 * easier to remember
 */
typedef struct __IDT_STR idt_descriptor_t;

/* 
 * Loads the interrupt descriptor table
 * pointed to by base
 */
void load_idt( idt_descriptor_t* base, u16_t limit );

/*
 * Set the offset in an
 * idt entry
 */
void idt_set_offset( idt_descriptor_t* idt_entry, void* offset );

/*
 * Set the segment in the idt entry.
 */
void idt_set_segment( idt_descriptor_t* idt_entry, u16_t segment );

/*
 * Set the type of the idt entry
 */
void idt_set_type( idt_descriptor_t* idt_entry, idt_type_t type );

/*
 * Set the privlegde level of the
 * idt entry
 */
void idt_set_privledge_level( idt_descriptor_t* idt_entry, privledge_level_t leverage );

#endif /* IDT_H_ */
