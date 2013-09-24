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

    while(1) ;

    return 0;
}
