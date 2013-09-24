/*
 * This is stage 2 of TehBoot
 */

#include "vga.h"

/*
 * Get the message of the day
 * to display to the user
 */
#include "tehboot_motd.h"

/*
 * Include the header file for the
 * interrupt descriptor table
 */
#include "idt.h"

/* The interrupt descriptor table */
idt_descriptor_t interrupt_table[256];

void call_interrupt( );
 

/*
 * Main entry point for teh boot.
 */
int main() {
    /* VGA color */
    vga_color_t color;

    /* Clear the vga buffer */
    vga_clear();

    /* Print things in white */
    vga_sethigher( color = vga_color_light_grey );

    /* Print the message */
    vga_print( "Start stage 2 ...\n" );
    vga_print( "Welcome to Teh Boot.\n" );
    vga_print( "  Starting stage2 complete\n" );

    vga_sethigher( vga_color_white );
    vga_print( MOTD );
    vga_move( 24, 0 );
    vga_print("Press any key to continue . . .");

    ksize_t i = 0;
    for( ; i < 256; ++ i ) {
        idt_set_offset( &interrupt_table[i], call_interrupt );
        /* Set the segment to the same segment
         * currently executing */
        idt_set_segment( &interrupt_table[i], 8 );
        idt_set_type( &interrupt_table[i], IdtType_TaskGate32 );
        idt_set_privledge_level( &interrupt_table[i], 0 );
    }


    while(1) ;

    return 0;
}

void call_interrupt( ) {
    vga_print( "There was an interrupt! " );

    /* have to use iret to return from an interrupt
     * service routine */
    asm ("hlt");
    isr_return;
}
