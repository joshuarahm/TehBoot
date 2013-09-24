/*
 * this file contains functions for abstracting the vga
 * buffer usage.
 */

#ifndef VGA_H_
#define VGA_H_

#include "tbtype.h"

typedef enum {
	   vga_color_black = 0
	,  vga_color_blue = 1
	,  vga_color_green = 2
	,  vga_color_cyan = 3
	,  vga_color_red = 4
	,  vga_color_magenta = 5
	,  vga_color_brown = 6
	,  vga_color_light_grey = 7
	,  vga_color_dark_grey = 8
	,  vga_color_light_blue = 9
	,  vga_color_light_green = 10
	,  vga_color_light_cyan = 11
	,  vga_color_light_red = 12
	,  vga_color_light_magenta = 13
	,  vga_color_light_brown = 14
	,  vga_color_white = 15
} vga_color_t;

typedef struct {
    int somethin;
    int someelse;
} blat_t;

void vga_clear( void );

/* Shifts all lines up by one and moves
 * the cursor to the beginning of the last
 * line */
void vga_shift( void ) ;

/* Put a newline at the cursor. */
void vga_newline( void );

/* Puts a character on the current position
 * in the vga buffer. If c is a newline character
 * than the cursor is moved down a line
 * and reset to the beginning. If the 
 * character is a carridge return '\r' then
 * the cursor is put back to the beginning */
void vga_putc( char c );

/* Move the vga cursor */
int vga_move( u16_t row, u16_t col ) ;

/* Prints a fulls string to the VGA buffer */
void vga_print( const char* chrs );

/* Print a string, but this string
 * may not have a null terminator, so
 * instead pass a length to it */
void vga_printn( const char* chrs, ksize_t len );

/*
 * Print an integer in decimal
 */
void vga_printid( sint_t i );

/* set the higher order bits to use for printing */
void vga_sethigher( u8_t byte );

#endif
