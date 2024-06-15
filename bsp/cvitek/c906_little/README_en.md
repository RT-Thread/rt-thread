# c906_little bsp
This BSP is a coprocessor in the cv18xx series processor, using RISCV C906 @ 700Mhz.
Features:
- No MMU
- Integrated Floating-point Unit (FPU)

## Toolchain Download
Download the toolchain for `riscv64-unknown-elf-gcc`: [https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz](https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz)

> Note:
Current BSP only supports Linux compilation.

After correct decompression, add the local path of the `riscv64-unknown-elf-gcc` toolchain to `EXEC_PATH` in `rtconfig.py`, or specify the path through the `RTT_EXEC_PATH` environment variable.

```shell
$ export RTT_EXEC_PATH=/opt/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1/bin
```

## Compilation
1. Dependency Installation

```shell
$ sudo apt install -y scons libncurses5-dev wget flex bison
```

2. On Linux platform, execute:
```shell
$ scons --menuconfig
```

Choose the target development board type that needs to be compiled:
```shell
Board Type (milkv-duo)  --->
    ( ) milkv-duo
    ( ) milkv-duo-spinor
    (X) milkv-duo256m
    ( ) milkv-duo256m-spinor
```

It will automatically download env related scripts to the ~/.env directory, then execute
```shell
$ source ~/.env/env.sh
$ pkgs --update
```
After updating the software packages, execute `scons -j10` or `scons -j10 --verbose` to compile this BSP. Or use the `scons --exec-path="GCC toolchain path"` command to compile directly while specifying the toolchain location. If the compilation is correct, the rtthread.elf file will be generated.

After the compilation is completed, the script automatically calls the `combine-fip.sh` script for packaging, and generates `fip.sd`, which is the c906_little file for SD card startup.

The first time the `combine-fip.sh` script is called, it will automatically download the required `opsbsbi`, `fsbl`, `uboot`, and other related files to the `bsp/cvitek/cvitek_bootloader` directory, please be patient.

After downloading, it will automatically decompress and compile. Subsequently, when compiling the same type of development board again, only the relevant files will be called to package and synthesize `fip.bin`. If you need to manually compile the related `cvitek_bootloader` files, you can execute `bash build.sh lunch` in the `bsp/cvitek/cvitek_bootloader` directory to choose the corresponding development board for compilation.

## Running
1. Divide the SD card into 2 partitions, the 1st partition is used to store bin files, and the 2nd partition is used as a data storage partition, with the partition format being `FAT32`.
2. Copy the `fip.bin` and `boot.sd` from the root directory into the 1st partition of the SD card. Subsequent firmware updates only require copying the `fip.sd` file.
Where:
- fip.bin: fsbl, opensbi, uboot, c906_little packaged bin file
- boot.sd: bin file packaged by the main kernel

After updating `fip.sd`, restarting will show the output information on the serial port:
```shell
HW_HEAP_BEGIN:83f74dc0 RT_HW_HEAP_END:84000000 size: 569920

 \ | /
- RT -     Thread Operating System
 / | \     5.1.0 build Jan 27 2024 22:45:49
 2006 - 2022 Copyright by RT-Thread team
Hello, RISC-V!
msh />
```

> Note: The default log serial port for the c906 little core is uart1