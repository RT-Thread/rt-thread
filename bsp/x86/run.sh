cp rtthread.elf root
grub-mkrescue -o bootable.iso root

qemu-system-i386 -cdrom bootable.iso -boot d -nographic
