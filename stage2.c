/*
 * This is stage 2 of TehBoot
 */

#define VGA_BUFFER_PTR ((short int*)0xB8000)

const char* message = "Start Stage 2";

void main() {
	const char* ptr = message;
	register int i = 0;

	for( i = 0 ; *ptr != 0; ++ i ) {
		VGA_BUFFER_PTR[i] = 0x0F00 | *ptr; /* Print char with white color */
		*ptr ++;
	}

	/* Infaloop */
	while( 1 ) ;
}
