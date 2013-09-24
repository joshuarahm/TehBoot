CC?=gcc
LD?=ld
LD_SCRIPT=link_stage2.ld
LD_FLAGS=-m elf_i386 -static -T$(LD_SCRIPT) -nostdlib
C_FLAGS=-m32 -ffreestanding -Iinclude
OBJCOPY=objcopy
LIBOBJS=lib/vga.o lib/idt.o

lib/vga.o: lib/vga.c
	$(CC) -olib/vga.o -c lib/vga.c $(C_FLAGS)

lib/idt.o: lib/idt.c
	$(CC) -olib/idt.o -c lib/idt.c $(C_FLAGS)

stage2.o: stage2_main.c
	$(CC) -ostage2.o -c stage2_main.c $(C_FLAGS)

stage2.bin: stage2.o $(LIBOBJS)
	- mkdir -p bin/
	$(LD) $(LD_FLAGS) -o bin/stage2.elf stage2.o $(LIBOBJS)
	$(OBJCOPY) -O binary bin/stage2.elf bin/stage2.bin

clean:
	- rm -r bin/ *.o lib/*.o
	
