#include "idt.h"

void load_idt( idt_descriptor_t* base, u16_t limit ) {
    unsigned int i[2];
    i[0] = limit << 16;
    i[1] = (unsigned int) base;

    asm ("lidt (%0)": :"p" (((char *) i)+2));
}

void idt_set_offset( idt_descriptor_t* idt_entry, void* offset ) {
    idt_entry->off1 = ((long)offset) & 0xFFFF;
    idt_entry->off2 = (((long)offset) >> 16) & 0xFFFF;
}

void idt_set_segment( idt_descriptor_t* idt_entry, u16_t segment ) {
    idt_entry->segment = segment;
}

void idt_set_type( idt_descriptor_t* idt_entry, idt_type_t type ) {
   idt_entry->type_attr |= type;
}

void idt_set_privledge_level( idt_descriptor_t* idt_entry, privledge_level_t priv ) {
    idt_entry->type_attr |= priv << 5;
}
