all: | bootloader.o link bootload
	
me: boot.s
	gcc -obootloader.o -c boot.s -ffreestanding
	ld -static -Tlink.ld -nostdlib -o bootloader.elf bootloader.o;
	objcopy -O binary bootloader.elf bootloader.bin
	dd if=bootloader.bin of=hda.img conv=notrunc

them: boot2.asm
	nasm -obootloader.bin boot2.asm
	dd if=bootloader.bin of=hda.img conv=notrunc

run:
	qemu-system-x86_64 -hda hda.img

debug:
	qemu-system-x86_64 -hda hda.img -s -S &
	gdb -ex 'target remote localhost:1234' -ex 'break *0x7c00' -ex 'break *0x1000' -ex 'c'

hda:
	head -c 128000000 /dev/zero > hda.img

stage2: stage2.c
	gcc -m32 -ostage2.o -c stage2.c -ffreestanding
	ld -m elf_i386 -static -T link_stage2.ld -nostdlib -o stage2.elf stage2.o
	objcopy -O binary stage2.elf stage2.bin
	dd if=stage2.bin of=hda.img bs=1 seek=512 conv=notrunc

clean:
	rm *.o *.bin *.elf
