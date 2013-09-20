AS=gcc
LD?=ld

AS_FLAGS=-ffreestanding
LD_SCRIPT=link_stage1.ld
LD_FLAGS=-static -T$(LD_SCRIPT) -nostdlib

OBJCOPY=objcopy

stage1.o: stage1.s
	$(AS) -ostage1.o -c stage1.s $(AS_FLAGS)


stage1.bin: stage1.o
	- mkdir -p bin/
	$(LD) $(LD_FLAGS) -o bin/stage1.elf stage1.o
	$(OBJCOPY) -O binary bin/stage1.elf bin/stage1.bin
	
clean:
	- rm -r bin/ *.o
