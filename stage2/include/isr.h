#ifndef ISR_H_
#define ISR_H_

/*
 * Author: jrahm
 * created: 2013/09/24
 * isr.h: <description>
 */

#include "idt.h"

extern void isr0( );

extern void isr1( );

extern void isr2( );

extern void isr3( );

extern void isr4( );

extern void isr5( );

extern void isr6( );

extern void isr7( );

extern void isr8( );

extern void isr9( );

extern void isr10( );

extern void isr11( );

extern void isr12( );

extern void isr13( );

extern void isr14( );

extern void isr15( );

extern void isr16( );

extern void isr17( );

extern void isr18( );

extern void isr19( );

extern void isr20( );

extern void isr21( );

extern void isr22( );

extern void isr23( );

void setup_standard_isr( idt_descriptor_t* table );

#endif /* ISR_H_ */
