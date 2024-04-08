[中文](README.md) | **English** 

## Overview
The CV18xx series of chips are high-performance, low-power chips launched for various products in the field of civilian consumer surveillance IP cameras, smart homes, and more. These chips integrate H.264/H.265 video compression encoders, as well as ISP; they support various image enhancement and correction algorithms such as digital wide dynamic range, 3D noise reduction, defogging, and lens distortion correction, providing customers with professional-level video image quality.

1. Processor Core
- Main Processor: RISC-V C906 @ 1.0Ghz
  - 32KB I-cache, 64KB D-Cache
  - Integrated Vector and Floating-Point Unit (FPU).
- Co-processor: RISC-V C906 @ 700Mhz
  - Integrated Floating-Point Unit (FPU)

2. Storage Interface
- Built-in DRAM: DDR2 16bitx1, with a maximum speed of 1333Mbps, and a capacity of 512Mbit (64MB)
- Support for SPI NOR flash interface (1.8V / 3.0V)
  - Supports 1, 2, 4 line modes
  - Maximum support of 256MByte
- Support for SPI Nand flash interface (1.8V / 3.0V)
  - Supports 1KB/2KB/4KB page (corresponding to maximum capacity of 16GB/32GB/64GB)
  - Utilizes the device's built-in ECC module

3. Peripherals
- Up to 26 GPIO pins on the MilkV-Duo 40-pin header provide access to internal peripherals such as SDIO, I2C, PWM, SPI, J-TAG, and UART
- Up to 3x I2C
- Up to 5x UART
- Up to 1x SDIO1
- Up to 1x SPI
- Up to 2x ADC
- Up to 7x PWM
- Up to 1x RUN
- Up to 1x JTAG
- Integrated MAC PHY supports 10/100Mbps full or half duplex mode
- One USB host/device interface

## Toolchain Download
1. RT-Thread Standard Edition Toolchain: `riscv64-unknown-elf-gcc` Download Link [https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz](https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz)

2. RT-Smart Edition Toolchain: `riscv64-unknown-linux-musl-gcc` Download Link [https://github.com/RT-Thread/toolchains-ci/releases/download/v1.7/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2](https://github.com/RT-Thread/toolchains-ci/releases/download/v1.7/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2)

> Note:
The current bsp only supports Linux compilation, and it is recommended to use Ubuntu 22.04

After correctly extracting, add the local path of the `riscv64-unknown-elf-gcc` or `riscv64-unknown-linux-musl-gcc` toolchain to `EXEC_PATH` in `rtconfig.py` or specify the path through the `RTT_EXEC_PATH` environment variable.

```shell
# For RT-Thread Standard Edition, use the following configuration:
$ export RTT_CC_PREFIX=riscv64-unknown-elf-
$ export RTT_EXEC_PATH=/opt/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1/bin

# For RT-Smart Edition, use the following configuration:
$ export RTT_CC_PREFIX=riscv64-unknown-linux-musl-
$ export RTT_EXEC_PATH=/opt/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin
```

## Compilation

### Dependency Installation
```shell
$ sudo apt install -y scons libncurses5-dev device-tree-compiler
```

## Modify Current Project Configuration

For the Linux platform, execute:
```shell
$ scons --menuconfig
```

1. By default, compile as RT-Thread Standard Edition. If you need to compile as RT-Smart Edition, modify as follows:
```shell
RT-Thread Kernel  --->
    [*] Enable RT-Thread Smart (microkernel on kernel/userland)

    (0x80000000) The virtual address of kernel start
```

2. Select the current target development board type:
```shell
Board Type (milkv-duo)  --->
    ( ) milkv-duo
    (X) milkv-duo256m
```

It will automatically download relevant scripts to the ~/.env directory, then execute:
```shell
$ source ~/.env/env.sh
$ pkgs --update
```
After updating the software package, execute `scons -j10` or `scons -j10 --verbose` to compile this board support package. If the compilation is successful, an rtthread.elf file will be generated.

After the compilation is complete, the script automatically calls the `./mksdimg.sh` script to package and generate `boot.sd`, which is the kernel file for SD card startup.

## Running
1. Divide the SD card into 2 partitions, with the first partition used to store bin files, and the second partition used as a data storage partition, with `FAT32` format.
2. Copy the `fip.bin` and `boot.sd` files from the root directory to the first partition of the SD card. Subsequent firmware updates only require copying the `boot.sd` file.
Where:
- fip.bin: fsbl, opensbi, and uboot packaged bin file
- boot.sd: kernel packaged bin file

After updating `boot.sd`, restart to see the serial port output:

```shell
U-Boot 2021.10 (Jun 26 2023 - 14:09:06 +0800)cvitek_cv180x

DRAM:  63.3 MiB
gd->relocaddr=0x82435000. offset=0x2235000
MMC:   cv-sd@4310000: 0
Loading Environment from <NULL>... OK
In:    serial
Out:   serial
Err:   serial
Net:
Warning: ethernet@4070000 (eth0) using random MAC address - 62:80:19:6c:d4:64
eth0: ethernet@4070000
Hit any key to stop autoboot:  0
Boot from SD ...
switch to partitions #0, OK
mmc0 is current device
132692 bytes read in 12 ms (10.5 MiB/s)
## Loading kernel from FIT Image at 81400000 ...
   Using 'config-cv1800b_milkv_duo_sd' configuration
   Trying 'kernel-1' kernel subimage
   Verifying Hash Integrity ... crc32+ OK
## Loading fdt from FIT Image at 81400000 ...
   Using 'config-cv1800b_milkv_duo_sd' configuration
   Trying 'fdt-cv1800b_milkv_duo_sd' fdt subimage
   Verifying Hash Integrity ... sha256+ OK
   Booting using the fdt blob at 0x8141b590
   Uncompressing Kernel Image
   Decompressing 296768 bytes used 42ms
   Loading Device Tree to 0000000081be5000, end 0000000081becb60 ... OK

Starting kernel ...

heap: [0x802766b0 - 0x812766b0]

 \ | /
- RT -     Thread Operating System
 / | \     5.1.0 build Apr  7 2024 23:33:20
 2006 - 2024 Copyright by RT-Thread team
Hello RISC-V!
msh />
```