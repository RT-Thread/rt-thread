
CC = gcc -O0 -m32 -fno-builtin -fno-stack-protector -nostdinc -nostdlib
LD = ld -melf_i386 -nostdlib

all: rtthread rtsym exe dll floppy.img

rtthread:
	@scons

rtsym:
	@./src/extract.sh ./rtthread-ia32.map ./src/rt_thread_sym.h

obj:
	mkdir -p obj

out:
	mkdir -p out

dll: obj out
	$(CC) -c -fPIC -Isrc src/hello.c -o out/hello.o
	$(CC) -s -Wl,-shared,-melf_i386,--entry=main -o out/hello.mo out/hello.o

disasm: obj out
	$(CC) -shared -S -fPIC -Isrc src/hello.c -o obj/hello.s
	cat obj/hello.s
	objdump --disassemble out/hello.mo

exe: obj out


clean:
	scons -c clean
	rm -fr build rtthread* out obj

floppy-orig.img:
	wget https://github.com/bajdcc/tinix/raw/master/floppy.img -O floppy-orig.img

floppy.img: floppy-orig.img
	cp floppy-orig.img floppy.img.tmp
	mcopy -oi floppy.img.tmp rtthread.elf ::/boot/oskernel
	mdeltree -i floppy.img.tmp ::/bin
	mmd -i floppy.img.tmp ::/bin
	mcopy -i floppy.img.tmp out/*.mo ::bin/
	mv floppy.img.tmp floppy.img

# https://en.wikibooks.org/wiki/QEMU/Devices/Network
run:
	qemu-system-i386 -fda floppy.img -boot a -m 64M -serial stdio -net nic,model=ne2k_pci
