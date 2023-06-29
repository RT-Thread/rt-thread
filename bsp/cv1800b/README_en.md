[中文](README.md) | **English** 

## Overview
CV180ZB/CV1800B/CV1801B are high-performance, low-power chips designed for consumer surveillance IP cameras, smart home devices, and other product areas. They integrate H.264/H.265 video compression encoders and ISPs, and support various image enhancement and correction algorithms such as digital wide dynamic range, 3D noise reduction, defogging, and lens distortion correction, providing professional-grade video image quality to customers.

1. Processor Core
- Main processor: RISCV C906 @ 1.0Ghz
  - 32KB I-cache, 64KB D-Cache
  - Integrated vector and floating-point units (FPU).
- Coprocessor: RISCV C906 @ 700Mhz
  - Integrated floating-point unit (FPU).

2. Memory Interface
- Built-in DRAM: DDR2 16bitx1, with a maximum speed of 1333Mbps, capacity of 512Mbit (64MB).
- Support for SPI NOR flash interface (1.8V / 3.0V)
  - Support for 1, 2, 4-wire modes
  - Maximum support of 256MBytes
- Support for SPI Nand flash interface (1.8V / 3.0V)
  - Support for 1KB/2KB/4KB page (corresponding to a maximum capacity of 16GB/32GB/64GB)
  - Use the built-in ECC module of the device itself

3. Peripherals
- Up to 26 GPIO pins on the MilkV-Duo 40-pin header provide access to internal peripherals such as SDIO, I2C, PWM, SPI, J-TAG, and UART.
- Up to 3x I2C
- Up to 5x UART
- Up to 1x SDIO1
- Up to 1x SPI
- Up to 2x ADC
- Up to 7x PWM
- Up to 1x RUN
- Up to 1x JTAG
- Integrated MAC PHY supporting 10/100Mbps full-duplex or half-duplex mode
- One USB Host / device interface

## Toolchain Download
Download the `riscv64-unknown-linux-musl-gcc` toolchain from: [https://github.com/RT-Thread/toolchains-ci/releases/download/v1.7/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2](https://github.com/RT-Thread/toolchains-ci/releases/download/v1.7/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2)

> Note:
The current BSP only supports Linux compilation.

After correct extraction, add the local path of the `riscv64-unknown-linux-musl-gcc` toolchain to `EXEC_PATH` in `rtconfig.py`, or specify the path through the `RTT_EXEC_PATH` environment variable.

```shell
$ export RTT_EXEC_PATH=/opt/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin
```

## Compilation
1. Installing Dependencies
```shell
$ sudo apt install -y device-tree-compiler
```
On the Linux platform, you can execute:

```shell
$ scons --menuconfig
```
It will automatically download environment-related scripts to the ~/.env directory, and then execute
```shell
$ source ~/.env/env.sh
$ pkgs --update
```

After updating the software packages, use `scons -j10` or `scons -j10 --verbose` to compile this board support package. Alternatively, you can use the command `scons --exec-path="GCC_toolchain_path"` to specify the toolchain location for compilation. If the compilation is successful, an rtthread.elf file will be generated.

After the compilation is completed, the script automatically calls the `./mksdimg.sh` script to package and generate the `boot.sd` file, which is the kernel file for SD card boot.

## Running
1. Divide the SD card into 2 partitions, with the first partition used to store bin files and the second partition used as a data storage partition. The partition format is FAT32.

2. Copy the `fip.bin` and `boot.sd` files from the root directory to the first partition of the SD card. For subsequent firmware updates, you only need to copy the `boot.sd` file.
Where:
- fip.bin: the bin file after fsbl、opensbi and U-Boot are packaged
- boot.sd: the bin file after the kernel is packaged

After updating `boot.sd`, power on again and you will see the serial output information:

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
- RT -     Thread Smart Operating System
 / | \     5.0.1 build Jun 28 2023 23:44:36
 2006 - 2022 Copyright by RT-Thread team
Hello RT-Smart!
msh />
```
## Driver Support List

| Driver | Support Status | Remarks                |
| :----- | :------------- | :--------------------- |
| UART   | Supported      | Default baud rate 115200 |

## Supported Development Boards
- milk-v duo: [https://milkv.io/duo](https://milkv.io/duo)

## Contact information

Maintenance person：[flyingcys](https://github.com/flyingcys)
