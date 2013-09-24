#include "vga.h"


/*
 * The pointer to the
 * VGA buffer. The VGA
 * buffer is essentially
 * an array of 16-bit ints
 */
u16_t* const VGA_BUFFER_PTR = (u16_t*)0xB8000;
const int VGA_HEGIHT = 25;
const int VGA_WIDTH  = 80;
#define VGA_BUFFER_SIZE ((VGA_HEGIHT)*(VGA_WIDTH))

/*
 * The current cursor position
 */
static u16_t vga_col = 0;
static u16_t vga_row = 0;

/* The current value set for
 * the high bits */
static u8_t  vga_high_bits = 0;

void vga_clear( void ) {
	u16_t* front = ( u16_t*)(VGA_BUFFER_PTR);
	vga_col = vga_row = 0;

	for( ; front < VGA_BUFFER_PTR + VGA_BUFFER_SIZE ; ++ front ) {
		*front = 0;
	}
}

void vga_shift( void ) {
	u16_t* back;
	u16_t* front;

	back = ( u16_t*)VGA_BUFFER_PTR;
	front = ( u16_t*)(VGA_BUFFER_PTR)+VGA_WIDTH;
	
	// could be faster, but whatever
	// backfill all bytes a line ago
	for( ; front < VGA_BUFFER_PTR + VGA_BUFFER_SIZE ; ++ front, ++ back ) {
		*back = *front;
	}

	// delete the last line
	for( ; back < VGA_BUFFER_PTR + VGA_BUFFER_SIZE ; ++ back ) {
		*back = 0;
	}
}

void vga_newline( void ) {
	if( vga_row+1 == VGA_HEGIHT ) {
		vga_shift( );
	} else {
		++ vga_row;
	}
	vga_col = 0;
}

void vga_putc( char c ) {
	if( c == '\n' ) {
		vga_newline();
	} else if ( c == '\r' ) {
		vga_col = 0;
	} else {
		*(VGA_BUFFER_PTR + vga_col + vga_row * VGA_WIDTH) = ( (u16_t)vga_high_bits << 8) | c;
		++ vga_col;
		if( vga_col == VGA_WIDTH ) {
			vga_newline( );
		}
	}
}

int vga_move( u16_t row, u16_t col ) {
	if( row >= VGA_HEGIHT || col >= VGA_WIDTH )
		return 1;
	vga_col = col;
	vga_row = row;
	return 0;
}

void vga_print( const char* chrs ) {
	for( ; *chrs != '\0'; ++ chrs ) {
		vga_putc( *chrs );
	}
}

void vga_printn( const char* chrs, ksize_t len ) {
	ksize_t i = 0;
	for( ; i != len ; ++ i ) {
		vga_putc( *chrs ++ );
	}
}

void vga_printid( sint_t i ) {
	if( i == 0 ) {
		vga_putc( '0' );
		return ;
	}

	if( i < 0 ) {
		vga_putc( '-' );
		i *= -1;
	}

	char buf[32];
	sint_t ptr = 0;
	while( i > 0 ) {
		buf[ptr++] = 0x30 + (i % 10);
		i /= 10;
	}

	for( ; ptr >= 0; -- ptr ) {
		vga_putc( buf[ptr] );
	}
}

void vga_sethigher( u8_t byte ) {
	vga_high_bits = byte;
}
