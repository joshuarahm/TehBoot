/*
 * This is stage 2 of TehBoot
 */

/* 
 * Include functions for controlling
 * the vga buffer
 */
#include "vga.h"
#include "tehboot.h"
#include "gdt.h"

const short int const* VGA_BUFFER_PTR = ((short int*)0xB8000);

gdt_entry_t gdt_entries[3];

void setup_gdt( gdt_entry_t* table, ksize_t len  ) {
    gdt_entry_set_limit( &table[0], sizeof( gdt_entry_t ) * len );
    gdt_entry_set_base( &table[0], (kptr_t)table );
}


int main() {
    vga_color_t color;

    // enable_int();
    /* Clear the vga buffer */
    vga_clear();

    /* Print things in white */
    vga_sethigher( color = vga_color_light_grey );

    /* Print the message */
    vga_print( "Start stage 2 ...\n" );

//    setup_gdt( gdt_entries, 3 );

    vga_print( "Welcome to Teh Boot.\n" );
    vga_print( "  Starting stage2 complete\n" );

    vga_sethigher( vga_color_white );
    vga_print("                            .-'\\                                               \n");
    vga_print("                         .-'  `/\\                                              \n");
    vga_print("                      .-'      `/\\                                             \n");
    vga_print("                      \\         `/\\                                            \n");
    vga_print("                       \\         `/\\                                           \n");
    vga_print("                        \\    _-   `/\\       _.--.                              \n");
    vga_print("                         \\    _-   `/`-..--\\     )                             \n");
    vga_print("                          \\    _-   `,','  /    ,')                            \n");
    vga_print("                           `-_   -   ` -- ~   ,','                             \n");
    vga_print("                            `-              ,','                               \n");
    vga_print("                             \\,--.    ____==-~                                 \n");
    vga_print("                              \\   \\_-~\\                                        \n");
    vga_print("                               `_-~_.-'                                        \n");
    vga_print("                                \\-~                                            \n");
    vga_sethigher( vga_color_white );
    vga_print("        ___ _           _ _     _____    _    ___         _   _                \n");
    vga_print("       / __(___ _____  (_| |_  |_   ____| |_ | _ )___ ___| |_| |               \n");
    vga_print("      | (_ | \\ V / -_) | |  _|   | |/ -_| ' \\| _ / _ / _ |  _|_|               \n");
    vga_print("       \\___|_|\\_/\\___| |_|\\__|   |_|\\___|_||_|___\\___\\___/\\__(_)               \n");
    vga_move( 24, 0 );
    vga_print("Press any key to continue . . .");

    // sint_t cnt = 0;
    // while( 1 ) {
    //     // halt();
    //     vga_print( "Interrupt detected " );
    //     vga_printid( cnt ++ );
    //     vga_newline();
    // }
    
    halt();
    
    return 0;
}
