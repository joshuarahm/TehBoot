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

#include "isr.h"

/* The interrupt descriptor table */
idt_descriptor_t interrupt_table[256];

void isr_main( );

void print_idt_descriptor( idt_descriptor_t* desc ) ;

void load_tss( );

/* Enables interrupts */
#define enable_int( ) __asm__("sti\n")

/* Halts the CPU */
#define halt( ) __asm__("hlt\n")

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

    setup_standard_isr( interrupt_table );
    /* Load the newly created interrupt descriptor table */
    load_idt( interrupt_table, 20*sizeof(idt_descriptor_t) );

    vga_print( "Starting stage2 complete.\n" );
    vga_print( "     Welcome to Teh Boot.\n" );

    vga_sethigher( vga_color_white );
    vga_print( MOTD );
    vga_move( 24, 0 );
    vga_print("Press any key to continue . . .\n");

    ksize_t i;
    for( i = 0; i < 20; ++ i ) {
        vga_printid(i);
        vga_putc( '\t' );
        print_idt_descriptor( & interrupt_table[i] );
        vga_print("\n");
    }

    // halt();

    load_tss( );
    /* enable interrupts. Here be dragons */
    enable_int();
    asm( "int $0x03" );

    /* indefinately wait */
    while(1);


    return 0;
}

void load_tss( ) {
    asm( "mov $0x18,%ax" );
    asm( "ltr %ax" );
}

 
void print_idt_descriptor( idt_descriptor_t* desc ) {
    vga_print(" |");
    vga_print(" off1=0x");
    vga_printix( desc->off1 );
    vga_print(" seg=0x");
    vga_printix( desc->segment );
    vga_print(" unused=0x");
    vga_printix( desc->unused );
    vga_print(" typ=0x");
    vga_printix( desc->type_attr );
    vga_print(" off2=0x");
    vga_printix( desc->off2 );
}

void isr_main( ) {
    asm("cli");
    vga_print( "There was an interrupt!\n" );
}
