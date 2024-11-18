**QEMU/RISCV64 VIRT Board Support Package User Guide**

English | [中文](./README_cn.md)

<!-- TOC -->

- [1. Introduction](#1-introduction)
- [2. Building](#2-building)
	- [2.1. Installing the toolchain](#21-installing-the-toolchain)
	- [2.2. Setting RT-Thread toolchain environment variables](#22-setting-rt-thread-toolchain-environment-variables)
	- [2.3. Downloading the kernel](#23-downloading-the-kernel)
	- [2.4. Configuring the kernel](#24-configuring-the-kernel)
	- [2.5. Compiling the kernel](#25-compiling-the-kernel)
- [3. Running](#3-running)
	- [3.1. Installing QEMU](#31-installing-qemu)
	- [3.2. Running QEMU](#32-running-qemu)
- [4. How to use rv64ilp32 toolchain](#4-how-to-use-rv64ilp32-toolchain)
- [5. Contact information](#5-contact-information)

<!-- /TOC -->

# 1. Introduction

RISC-V is an open and free instruction set architecture (ISA). This project is a port on the RISCV64 VIRT version of QEMU.

This project supports the world's first rv64ilp32 product-level open source toolchain jointly launched by the Xuantie team and the Institute of Software of the Chinese Academy of Sciences.

# 2. Building

Working system: take Ubuntu 22.04 as an example:

```shell
$ lsb_release -a
No LSB modules are available.
Distributor ID: Ubuntu
Description: Ubuntu 22.04.2 LTS
Release: 22.04
Codename: jammy
```

## 2.1. Installing the toolchain

The specific toolchain used is consistent with the official RT-Thread. For the specific toolchain version, please refer to the file <https://github.com/RT-Thread/rt-thread/blob/master/.github/workflows/action_utest.yml> in the RT-Thread repository.

```yaml
    - name: Install RISC-V ToolChains
      if: ${{ matrix.legs.QEMU_ARCH == 'riscv64' && matrix.legs.UTEST != 'rtsmart/riscv64' && success() }}
      run: |
        wget -q https://github.com/RT-Thread/toolchains-ci/releases/download/v1.4/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14.tar.gz
        sudo tar zxvf riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14.tar.gz -C /opt
        /opt/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14/bin/riscv64-unknown-elf-gcc --version
        echo "RTT_EXEC_PATH=/opt/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14/bin" >> $GITHUB_ENV

    - name: Install RISC-V Musl ToolChains
      if: ${{ matrix.legs.QEMU_ARCH == 'riscv64' && matrix.legs.UTEST == 'rtsmart/riscv64' && success() }}
      shell: bash
      run: |
        wget -q https://github.com/RT-Thread/toolchains-ci/releases/download/v1.7/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2
        sudo tar xjf riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2 -C /opt
        /opt/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin/riscv64-unknown-linux-musl-gcc --version
        echo "RTT_EXEC_PATH=/opt/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin" >> $GITHUB_ENV
        echo "RTT_CC_PREFIX=riscv64-unknown-linux-musl-" >> $GITHUB_ENV
```

Among them, `riscv64-unknown-elf-gcc` is used to build the RT-Thread Standard version, and `riscv64-unknown-linux-musl-gcc` is used to build the RT-Thread Smart version. Download them to your local computer according to the links shown above and decompress them.

## 2.2. Setting RT-Thread toolchain environment variables

There are three environment variables related to the RT-Thread toolchain

- `RTT_CC` is the toolchain name, which is `"gcc"` here
- `RTT_CC_PREFIX`: is the toolchain prefix, which is `"riscv64-unknown-elf-"` for the Standard version and `"riscv64-unknown-linux-musl-"` for the Smart version.
- `RTT_EXEC_PATH`: the path where the bin folder of the toolchain is located, such as `"$HOME/tools/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14/bin"`. This is set according to the actual path after personal download and decompression. Note that the toolchains of the RT-Thread standard version and the Smart version are two different versions, and the path name of `RTT_EXEC_PATH` must be set to `bin`.

If you use them all the time, it is recommended to export these three environment variables in the `.bashrc` file.

## 2.3. Downloading the kernel

Assume that the working path is `$WORKSPACE`.

```shell
$ cd $WORKSPACE
$ git clone git@github.com:RT-Thread/rt-thread.git
```

**Note: This document is based on the kernel version git commit ID: ebe2926cd6.**

Enter the BSP directory where qemu-virt64-riscv is located. The following operations will not be introduced separately. By default, it is in this directory.

```shell
$ cd $WORKSPACE/rt-thread/bsp/qemu-virt64-riscv
```

## 2.4. Configuring the kernel

Refresh the configuration file before compiling for the first time.

```shell
$ scons --menuconfig
```

The default configuration is the RT-Thread standard version, so if you don't have any special requirements, don't change anything, just save and exit.

If you want to use the RT-Thread Smart version, at least turn on the `RT_USING_SMART` option after entering the configuration menu (see the figure below), and the rest depends on your needs.

```
(Top) → RT-Thread Kernel
RT-Thread Project Configuration
(24) The maximal size of kernel object name
[ ] Use the data types defined in ARCH_CPU
[*] Enable RT-Thread Smart (microkernel on kernel/userland)
[ ] Enable RT-Thread Nano
...
```

Save and exit after modification.

## 2.5. Compiling the kernel

If you have compiled before, you can clean it up:

```shell
$ scons --clean
```

Or compile directly:

```shell
$ scons -j$(nproc)
```

The kernel binary file `rtthread.bin` will be generated in the `$WORKSPACE/rt-thread/bsp/qemu-virt64-riscv`.

# 3. Running

## 3.1. Installing QEMU

```shell
$ sudo apt update
$ sudo apt install qemu-system-misc
```

After the installation is complete, you can check the version.

```shell
$ qemu-system-riscv64 --version
QEMU emulator version 6.2.0 (Debian 1:6.2+dfsg-2ubuntu6.24)
Copyright (c) 2003-2021 Fabrice Bellard and the QEMU Project developers
```

## 3.2. Running QEMU

The repository has provided a ready-made execution script, which can be executed directly:

```shell
$ ./qemu-nographic.sh
```

The running results of the RT-Thread Standard version are as follows:

```shell
$ ./qemu-nographic.sh 

OpenSBI v0.9
   ____                    _____ ____ _____
  / __ \                  / ____|  _ \_   _|
 | |  | |_ __   ___ _ __ | (___ | |_) || |
 | |  | | '_ \ / _ \ '_ \ \___ \|  _ < | |
 | |__| | |_) |  __/ | | |____) | |_) || |_
  \____/| .__/ \___|_| |_|_____/|____/_____|
        | |
        |_|

Platform Name             : riscv-virtio,qemu
Platform Features         : timer,mfdeleg
Platform HART Count       : 1
Firmware Base             : 0x80000000
Firmware Size             : 100 KB
Runtime SBI Version       : 0.2

Domain0 Name              : root
Domain0 Boot HART         : 0
Domain0 HARTs             : 0*
Domain0 Region00          : 0x0000000080000000-0x000000008001ffff ()
Domain0 Region01          : 0x0000000000000000-0xffffffffffffffff (R,W,X)
Domain0 Next Address      : 0x0000000080200000
Domain0 Next Arg1         : 0x000000008f000000
Domain0 Next Mode         : S-mode
Domain0 SysReset          : yes

Boot HART ID              : 0
Boot HART Domain          : root
Boot HART ISA             : rv64imafdcsu
Boot HART Features        : scounteren,mcounteren,time
Boot HART PMP Count       : 16
Boot HART PMP Granularity : 4
Boot HART PMP Address Bits: 54
Boot HART MHPM Count      : 0
Boot HART MHPM Count      : 0
Boot HART MIDELEG         : 0x0000000000000222
Boot HART MEDELEG         : 0x000000000000b109
heap: [0x8028d8a8 - 0x8428d8a8]

 \ | /
- RT -     Thread Operating System
 / | \     5.2.0 build Nov 14 2024 15:41:57
 2006 - 2024 Copyright by RT-Thread team
lwIP-2.0.3 initialized!
[I/sal.skt] Socket Abstraction Layer initialize success.
[I/utest] utest is initialize success.
[I/utest] total utest testcase num: (0)
file system initialization done!
Hello RISC-V
msh />
```

The running results of RT-Thread Smart version are as follows:

```shell
$ ./qemu-nographic.sh 

OpenSBI v0.9
   ____                    _____ ____ _____
  / __ \                  / ____|  _ \_   _|
 | |  | |_ __   ___ _ __ | (___ | |_) || |
 | |  | | '_ \ / _ \ '_ \ \___ \|  _ < | |
 | |__| | |_) |  __/ | | |____) | |_) || |_
  \____/| .__/ \___|_| |_|_____/|____/_____|
        | |
        |_|

Platform Name             : riscv-virtio,qemu
Platform Features         : timer,mfdeleg
Platform HART Count       : 1
Firmware Base             : 0x80000000
Firmware Size             : 100 KB
Runtime SBI Version       : 0.2

Domain0 Name              : root
Domain0 Boot HART         : 0
Domain0 HARTs             : 0*
Domain0 Region00          : 0x0000000080000000-0x000000008001ffff ()
Domain0 Region01          : 0x0000000000000000-0xffffffffffffffff (R,W,X)
Domain0 Next Address      : 0x0000000080200000
Domain0 Next Arg1         : 0x000000008f000000
Domain0 Next Mode         : S-mode
Domain0 SysReset          : yes

Boot HART ID              : 0
Boot HART Domain          : root
Boot HART ISA             : rv64imafdcsu
Boot HART Features        : scounteren,mcounteren,time
Boot HART PMP Count       : 16
Boot HART PMP Granularity : 4
Boot HART PMP Address Bits: 54
Boot HART MHPM Count      : 0
Boot HART MHPM Count      : 0
Boot HART MIDELEG         : 0x0000000000000222
Boot HART MEDELEG         : 0x000000000000b109
heap: [0x002ef030 - 0x042ef030]

 \ | /
- RT -     Thread Smart Operating System
 / | \     5.2.0 build Nov 14 2024 15:48:43
 2006 - 2024 Copyright by RT-Thread team
lwIP-2.0.3 initialized!
[I/sal.skt] Socket Abstraction Layer initialize success.
[I/utest] utest is initialize success.
[I/utest] total utest testcase num: (0)
[I/drivers.serial] Using /dev/ttyS0 as default console
file system initialization done!
Hello RISC-V
msh />
```

# 4. How to use rv64ilp32 toolchain

- Toolchain address: <https://github.com/ruyisdk/riscv-gnu-toolchain-rv64ilp32/tags>

- Usage:

  - Configure toolchain path

  - Modify ABI parameter to: `-mabi=ilp32d`

  - Then perform regular compilation

  - Use [script](./qemu-rv64ilp32-nographic.sh) to start QEMU (INFO: QEMU binary is also in the toolchain directory)

- Compare the firmware size of the same project compiled using the traditional 64-bit toolchain and the new 32-bit toolchain:

  Traditional 64-bit toolchain firmware size:

  ```bash
  Memory region         Used Size  Region Size  %age Used
              SRAM:      225856 B        16 MB      1.35%
  riscv64-unknown-elf-objcopy -O binary rtthread.elf rtthread.bin
  riscv64-unknown-elf-size rtthread.elf
     text    data     bss     dec     hex filename
   150907    3664   71268  225839   3722f rtthread.elf
  ```
  
  New 32-bit toolchain firmware size:

  ```bash
  Memory region         Used Size  Region Size  %age Used
              SRAM:      209376 B        16 MB      1.25%
  riscv64-unknown-elf-objcopy -O binary rtthread.elf rtthread.bin
  riscv64-unknown-elf-size rtthread.elf
     text    data     bss     dec     hex filename
   138739    1356   69276  209371   331db rtthread.elf
  ```

# 5. Contact information

Maintainer: [bernard][1]

[1]: https://github.com/BernardXiong