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
	gdb -ex 'target remote localhost:1234' -ex 'break *0x7c00' -ex 'c'

hda:
	head -c 128000000 /dev/zero > hda.img

clean:
	rm *.o *.bin *.elf
