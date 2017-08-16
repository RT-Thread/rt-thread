
all:floppy.img
	scons
	mkdir -p tmp
	sudo mount -t vfat floppy.img tmp -o loop
	sudo cp rtthread.elf tmp/boot/oskernel
	sudo umount tmp

clean:
	scons -c clean
	rm -fr build rtthread*

floppy.img:
	wget https://github.com/bajdcc/tinix/raw/master/floppy.img

run:
	qemu-system-i386 -fda floppy.img -boot a -m 64M
