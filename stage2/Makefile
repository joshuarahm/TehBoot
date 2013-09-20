CC?=gcc
LD?=ld
LD_SCRIPT=link_stage2.ld
LD_FLAGS=-m elf_i386 -static -T$(LD_SCRIPT) -nostdlib
C_FLAGS=-m32 -ffreestanding
OBJCOPY=objcopy

stage2.o: stage2_main.c
	$(CC) -ostage2.o -c stage2_main.c $(C_FLAGS)

stage2.bin: stage2.o
	- mkdir -p bin/
	$(LD) $(LD_FLAGS) -o bin/stage2.elf stage2.o
	$(OBJCOPY) -O binary bin/stage2.elf bin/stage2.bin

clean:
	- rm -r bin/ *.o
	
