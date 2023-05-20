$1 --version
$1\
	-machine arm-generic-fdt\
	-serial stdio\
	-device loader,file=rtthread.elf,cpu-num=4\
	-device loader,addr=0xff5e023c,data=0x80008fde,data-len=4\
	-device loader,addr=0xff9a0000,data=0x80000218,data-len=4\
	-hw-dtb zcu102-arm.dtb\
	-display none
