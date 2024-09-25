SiFive FU540 SoC Platform
=========================
The FU540-C000 is the world’s first 4+1 64-bit RISC-V SoC from SiFive.
The HiFive Unleashed development platform is based on FU540-C000 and capable
of running Linux.

With QEMU v4.2 or above release, the 'sifive_u' machine can be used to test
OpenSBI image built for the real hardware as well.

To build platform specific library and firmwares, provide the
*PLATFORM=sifive/fu540* parameter to the top level `make` command.

Platform Options
----------------

The *SiFive FU540 SoC* platform does not have any platform-specific
options.

Building SiFive Fu540 Platform
------------------------------

In order to boot SMP Linux in U-Boot, Linux v5.1 (or higher) and latest
U-Boot v2020.01 (or higher) should be used.

**Linux Kernel Payload**

The HiFive Unleashed device tree(DT) is merged in Linux v5.2 release. This
DT (device tree) is not backward compatible with the DT passed from FSBL.

To use Linux v5.2 (or higher), the pre-built DTB (DT binary) from Linux v5.2
(or higher) should be used to build SiFive FU540 OpenSBI binaries by using
the compile time option *FW_FDT_PATH*.

```
make PLATFORM=sifive/fu540 FW_PAYLOAD_PATH=<linux_build_directory>/arch/riscv/boot/Image
or
(For Linux v5.2 or higher)
make PLATFORM=sifive/fu540 FW_PAYLOAD_PATH=<linux_build_directory>/arch/riscv/boot/Image FW_FDT_PATH=<hifive-unleashed-a00.dtb path from Linux kernel>
```

**U-Boot Payload**

The command-line example here assumes that U-Boot was compiled using the
sifive_fu540_defconfig configuration and with U-Boot v2020.01, and up to
v2021.04. sifive_unleashed_defconfig shall be used with v2021.07 or above.

```
make PLATFORM=sifive/fu540 FW_PAYLOAD_PATH=<u-boot_build_dir>/u-boot-dtb.bin
```
For U-Boot v2020.07-rc4 or later releases, SPL support was added in U-Boot.
Please refer to the detailed U-Boot booting guide available at [U-Boot].

Flashing the OpenSBI firmware binary to storage media:
------------------------------------------------------
The first stage boot loader ([FSBL]) expects the storage media to have a GPT
partition table. It tries to look for a partition with following GUID to load
the next stage boot loader (OpenSBI in this case).

```
2E54B353-1271-4842-806F-E436D6AF6985
```

That's why the generated firmware binary in above steps should be copied to
the partition of the sdcard with above GUID.

```
dd if=build/platform/sifive/fu540/firmware/fw_payload.bin of=/dev/disk2s1 bs=1024
```

In my case, it is the first partition is **disk2s1** that has been formatted
with the above specified GUID.

In case of a brand new sdcard, it should be formatted with below partition
tables as described here.

```
sgdisk --clear                                                               \
       --new=1:2048:67583  --change-name=1:bootloader --typecode=1:2E54B353-1271-4842-806F-E436D6AF6985   \
       --new=2:264192:     --change-name=2:root       --typecode=2:0FC63DAF-8483-4772-8E79-3D69D8477DE4 \
       ${DISK}
```

Booting SiFive Fu540 Platform
-----------------------------

**Linux Kernel Payload**

As Linux kernel image is embedded in the OpenSBI firmware binary, HiFive
Unleashed will directly boot into Linux directly after powered on.

**U-Boot Payload**

As U-Boot image is used as payload, HiFive Unleashed will boot into a U-Boot
prompt. U-Boot tftp boot method can be used to load kernel image in U-Boot
prompt. Here are the steps do a tftpboot.

1. Set the ip address of the board.
```
setenv ipaddr <ipaddr of the board>
```
2. Set the tftpboot server IP.
```
setenv serverip <ipaddr of the tftp server>
```
3. Set the network gateway address.
```
setenv gatewayip <ipaddress of the network gateway>
```
4. Load the Linux kernel image from the tftp server.
```
tftpboot ${kernel_addr_r} <Image path in tftpboot directory>
```
5. Load the ramdisk image from the tftp server. This is only required if
ramdisk is loaded from tftp server. This step is optional, if rootfs is
already part of the kernel or loaded from an external storage by kernel.
```
tftpboot ${ramdisk_addr_r} <ramdisk path in tftpboot directory>
```
6. Load the pre-compiled device tree via tftpboot.
```
tftpboot ${fdt_addr_r} <hifive-unleashed-a00.dtb path in tftpboot directory>
```
7. Set the boot command-line arguments.
```
setenv bootargs "root=<root partition> rw console=ttySIF0 earlycon=sbi"
```
(Note: root partition should point to
** /dev/ram ** - If a ramdisk is used
** root=/dev/mmcblk0pX ** - If a rootfs is already on some other partition
of sdcard)
8. Now boot into Linux.
```
booti ${kernel_addr_r} ${ramdisk_addr_r} ${fdt_addr_r}
or
(If ramdisk is not loaded from network)
booti ${kernel_addr_r} - ${fdt_addr_r}
```

**U-Boot & Linux Kernel as a single payload**

At U-Boot prompt execute the following boot command to boot Linux.

```
booti ${kernel_addr_r} - ${fdt_addr_r}
```

QEMU Specific Instructions
--------------------------
If you want to test OpenSBI with QEMU 'sifive_u' machine, please follow the
same instructions above, with the exception of not passing FW_FDT_PATH.

This is because QEMU generates a device tree blob on the fly based on the
command line parameters and it's compatible with the one used in the upstream
Linux kernel.

When U-Boot v2021.07 (or higher) is used as the payload, as the SiFive FU540
DTB for the real hardware is embedded in U-Boot binary itself, due to the same
reason above, we need to switch the U-Boot sifive_unleashed_defconfig
configuration from **CONFIG_OF_SEPARATE** to **CONFIG_OF_PRIOR_STAGE** so that
U-Boot uses the DTB generated by QEMU, and u-boot.bin should be used as the
payload image, like:

```
make PLATFORM=sifive/fu540 FW_PAYLOAD_PATH=<u-boot_build_dir>/u-boot.bin
```

U-Boot v2020.07 release added SPL support to SiFive HiFive Unleashed board,
hence a build error will be seen after you switch to **CONFIG_OF_PRIOR_STAGE**.

```
./tools/mkimage: Can't open arch/riscv/dts/hifive-unleashed-a00.dtb: No such file or directory
./tools/mkimage: failed to build FIT
Makefile:1402: recipe for target 'u-boot.img' failed
make: *** [u-boot.img] Error 1
```

The above errors can be safely ignored as we don't run U-Boot SPL under QEMU.

Run:
```
qemu-system-riscv64 -M sifive_u -m 256M -nographic \
	-bios build/platform/sifive/fu540/firmware/fw_payload.bin
```
or
```
qemu-system-riscv64 -M sifive_u -m 256M -nographic \
	-bios build/platform/sifive/fu540/firmware/fw_jump.bin \
	-kernel <uboot_build_dir>/u-boot.bin
```

While the real hardware operates at the 64-bit mode, it's possible for QEMU to
test the 32-bit OpenSBI firmware. This can be helpful for testing 32-bit SiFive
specific drivers.

[U-Boot]: https://gitlab.denx.de/u-boot/u-boot/blob/master/doc/board/sifive/fu540.rst
[FSBL]: https://github.com/sifive/freedom-u540-c000-bootloader
