
CC = gcc -O0 -m32 -fno-builtin -fno-stack-protector -nostdinc -nostdlib
LD = ld -melf_i386 -nostdlib

all: rtthread rtsym exe dll floppy.img
	@mkdir -p tmp
	@sudo mount -t vfat floppy.img tmp -o loop
	@sudo cp -fv rtthread.elf tmp/boot/oskernel
	@sudo rm tmp/bin/* -fr
	@sudo cp out/* tmp/bin/ -fv
	@sudo umount tmp

QEMU ?= as/release/download/qemu/i386-softmmu

qemu:
	@(cd as/release/ascore; make asqemu)

drivers/dep-as-done:
	@(git clone https://github.com/parai/as)
	@(cd drivers;wget https://raw.githubusercontent.com/torvalds/linux/v4.8/include/uapi/linux/pci.h -O pci.h)
	@(cd drivers;wget https://raw.githubusercontent.com/torvalds/linux/v4.8/include/uapi/linux/pci_regs.h -O pci_regs.h)
	@(cd drivers;wget https://raw.githubusercontent.com/torvalds/linux/v4.8/include/linux/pci_ids.h -O pci_ids.h)
	@(cd drivers;sed -i "20c #include \"pci_regs.h\"" pci.h)
	@(cp -v as/com/as.infrastructure/include/Std_Types.h drivers/)
	@(sed -i "164c /* " drivers/Std_Types.h)
	@(sed -i "175c */ " drivers/Std_Types.h)
	@(cp -v as/com/as.infrastructure/include/asdebug.h drivers/)
	@(cp -v as/com/as.infrastructure/include/__debug.h drivers/)
	@(cp -v as/com/as.infrastructure/include/Compiler.h drivers/)
	@(cp -v as/com/as.infrastructure/include/io.h drivers/)
	@(cp -v as/com/as.infrastructure/communication/Pci/pci_core.* drivers/)
	@(sed -i "28c #include <rtthread.h>" drivers/pci_core.c)
	@(sed -i "31c #define _sys_printf    rt_kprintf" drivers/pci_core.c)
	@(sed -i "32c #define _sys_kmalloc   rt_malloc" drivers/pci_core.c)
	@(sed -i "35c #define _sys_putchar(c)  rt_kprintf(\"%c\",c)" drivers/pci_core.c)
	@(cp -v as/com/as.application/common/config/pci_cfg.* drivers/)
	@(cp -v as/com/as.infrastructure/arch/x86/bsp/pci-x86.c drivers/)
	@touch $@

dep-as: drivers/dep-as-done

rtthread: dep-as
	@scons

rtsym:
	@./src/extract.sh ./rtthread-ia32.map ./src/rt_thread_sym.h

obj:
	mkdir -p obj

out:
	mkdir -p out

dll: obj out
	$(CC) -shared -s -fPIC -e main -Isrc src/hello.c -o out/hello.mo

disasm: obj out
	$(CC) -shared -S -fPIC -Isrc src/hello.c -o obj/hello.s
	cat obj/hello.s
	objdump --disassemble out/hello.mo

exe: obj out


clean:
	scons -c clean
	rm -fr build rtthread* out obj

floppy.img:
	wget https://github.com/bajdcc/tinix/raw/master/floppy.img

# https://en.wikibooks.org/wiki/QEMU/Devices/Network
run:
	$(QEMU)/qemu-system-i386 -fda floppy.img -boot a -m 64M -serial stdio \
		-device pci-ascan \
		-device pci-asnet \
		-device pci-asblk \

