QEMU RISC-V Virt Machine Platform
=================================

The **QEMU RISC-V Virt Machine** is a virtual platform created for RISC-V
software development and testing. It is also referred to as
*QEMU RISC-V VirtIO machine* because it uses VirtIO devices for network,
storage, and other types of IO.

To build the platform-specific library and firmware images, provide the
*PLATFORM=generic* parameter to the top level `make` command.

Platform Options
----------------

The *QEMU RISC-V Virt Machine* platform does not have any platform-specific
options.

Execution on QEMU RISC-V 64-bit
-------------------------------

**No Payload Case**

Build:
```
make PLATFORM=generic
```

Run:
```
qemu-system-riscv64 -M virt -m 256M -nographic \
	-bios build/platform/generic/firmware/fw_payload.bin
```

**U-Boot Payload**

Note: the command line examples here assume that U-Boot was compiled using
the `qemu-riscv64_smode_defconfig` configuration.

Build:
```
make PLATFORM=generic FW_PAYLOAD_PATH=<uboot_build_directory>/u-boot.bin
```

Run:
```
qemu-system-riscv64 -M virt -m 256M -nographic \
	-bios build/platform/generic/firmware/fw_payload.elf
```
or
```
qemu-system-riscv64 -M virt -m 256M -nographic \
	-bios build/platform/generic/firmware/fw_jump.bin \
	-kernel <uboot_build_directory>/u-boot.bin
```

**Linux Kernel Payload**

Note: We assume that the Linux kernel is compiled using
*arch/riscv/configs/defconfig*.

Build:
```
make PLATFORM=generic FW_PAYLOAD_PATH=<linux_build_directory>/arch/riscv/boot/Image
```

Run:
```
qemu-system-riscv64 -M virt -m 256M -nographic \
	-bios build/platform/generic/firmware/fw_payload.elf \
	-drive file=<path_to_linux_rootfs>,format=raw,id=hd0 \
	-device virtio-blk-device,drive=hd0 \
	-append "root=/dev/vda rw console=ttyS0"
```
or
```
qemu-system-riscv64 -M virt -m 256M -nographic \
	-bios build/platform/generic/firmware/fw_jump.bin \
	-kernel <linux_build_directory>/arch/riscv/boot/Image \
	-drive file=<path_to_linux_rootfs>,format=raw,id=hd0 \
	-device virtio-blk-device,drive=hd0 \
	-append "root=/dev/vda rw console=ttyS0"
```


Execution on QEMU RISC-V 32-bit
-------------------------------

**No Payload Case**

Build:
```
make PLATFORM=generic PLATFORM_RISCV_XLEN=32
```

Run:
```
qemu-system-riscv32 -M virt -m 256M -nographic \
	-bios build/platform/generic/firmware/fw_payload.bin
```

**U-Boot Payload**

Note: the command line examples here assume that U-Boot was compiled using
the `qemu-riscv32_smode_defconfig` configuration.

Build:
```
make PLATFORM=generic PLATFORM_RISCV_XLEN=32 FW_PAYLOAD_PATH=<uboot_build_directory>/u-boot.bin
```

Run:
```
qemu-system-riscv32 -M virt -m 256M -nographic \
	-bios build/platform/generic/firmware/fw_payload.elf
```
or
```
qemu-system-riscv32 -M virt -m 256M -nographic \
	-bios build/platform/generic/firmware/fw_jump.bin \
	-kernel <uboot_build_directory>/u-boot.bin
```

**Linux Kernel Payload**

Note: We assume that the Linux kernel is compiled using
*arch/riscv/configs/rv32_defconfig*.

Build:
```
make PLATFORM=generic PLATFORM_RISCV_XLEN=32 FW_PAYLOAD_PATH=<linux_build_directory>/arch/riscv/boot/Image
```

Run:
```
qemu-system-riscv32 -M virt -m 256M -nographic \
	-bios build/platform/generic/firmware/fw_payload.elf \
	-drive file=<path_to_linux_rootfs>,format=raw,id=hd0 \
	-device virtio-blk-device,drive=hd0 \
	-append "root=/dev/vda rw console=ttyS0"
```
or
```
qemu-system-riscv32 -M virt -m 256M -nographic \
	-bios build/platform/generic/firmware/fw_jump.bin \
	-kernel <linux_build_directory>/arch/riscv/boot/Image \
	-drive file=<path_to_linux_rootfs>,format=raw,id=hd0 \
	-device virtio-blk-device,drive=hd0 \
	-append "root=/dev/vda rw console=ttyS0"
```
