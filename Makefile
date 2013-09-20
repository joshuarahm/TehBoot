IMAGE?=hda.img
SIZE?=1000000 # 1 MB disk
QEMU?=qemu-system-x86_64

all: | image

.PHONY: stage1 stage2
stage1:
	cd stage1 && make stage1.bin && cd ..

stage2:
	cd stage2 && make stage2.bin && cd ..

$(IMAGE):
	head -c $(SIZE) /dev/zero > $(IMAGE)

image: stage1 stage2 $(IMAGE)
	dd if=stage1/bin/stage1.bin of=$(IMAGE) conv=notrunc 
	dd if=stage2/bin/stage2.bin of=$(IMAGE) conv=notrunc bs=512 seek=1

run:
	$(QEMU) -hda $(IMAGE)

debug:
	$(QEMU) -hda $(IMAGE) -s -S &
	gdb -ex 'target remote localhost:1234' -ex 'break *0x7c00' -ex 'break *0x1000' -ex 'c'

clean:
	cd stage1 && make clean && cd .. && \
	cd stage2 && make clean && cd ..

spotless: clean
	rm $(IMAGE)
