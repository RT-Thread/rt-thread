# QEMU/RISCV64/C906 VIRT Board Support Package User Guide

English | [中文](./README_cn.md)

<!-- TOC -->

- [QEMU/RISCV64/C906 VIRT Board Support Package User Guide](#qemuriscv64c906-virt-board-support-package-user-guide)
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
      - [3.2.1. Running RT-Thread Smart version](#321-running-rt-thread-smart-version)
    - [3.2.2. Running RT-Thread Smart Edition + Root File System](#322-running-rt-thread-smart-edition--root-file-system)
  - [4. Contact Information](#4-contact-information)

<!-- /TOC -->

## 1. Introduction

RISC-V is an open and free instruction set architecture (ISA). This project is based on QEMU's RISC-V64 VIRT platform, ported to the C906 processor platform.

## 2. Building

Working system: take Ubuntu 24.04 as an example:

```shell
$ lsb_release -a
No LSB modules are available.
Distributor ID: Ubuntu
Description:    Ubuntu 24.04.2 LTS
Release:        24.04
Codename:       noble
```

### 2.1. Installing the toolchain

- Compiler: [Xuantie-900-gcc-linux-6.6.0-musl64-x86_64-V3.0.2-20250410.tar.gz](https://github.com/RT-Thread/toolchains-ci/releases/download/v1.9/Xuantie-900-gcc-linux-6.6.0-musl64-x86_64-V3.0.2.tar.gz)
- Emulator: [Xuantie-qemu-x86_64-Ubuntu-20.04-V5.0.5-B20250108-0335.tar.gz](https://www.xrvm.cn/community/download?id=4397435198627713024)

Note: If the emulator in the above link does not work, you can compile the emulator using the following repository
> [XUANTIE-RV/qemu](https://github.com/XUANTIE-RV/qemu )

### 2.2. Setting RT-Thread toolchain environment variables

There are three environment variables related to the RT-Thread toolchain

- `RTT_CC` is the toolchain name, which is `"gcc"` here
- `RTT_CC_PREFIX`: is the toolchain prefix, in this case `"riscv64-unknown-elf-"` for the Standard Edition and `"riscv64-unknown-linux-musl-"` for the Smart Edition.
- `RTT_EXEC_PATH`: the path to the bin folder of the toolchain, e.g. `"$HOME/tools/Xuantie-900-gcc-linux-6.6.0-musl64-x86_64-V3.0.2/bin"`, this is based on the path of the toolchain that was downloaded and unpacked by the user. Thread Standard and Smart versions are two different toolchains, and the path name of `RTT_EXEC_PATH` should be set to `bin`.

>Note: This may vary for different toolchains `RTT_CC_PREFIX`, which can be viewed in the toolchain bin folder path.
It is recommended to export these three environment variables in the `.bashrc` file if you use them all the time.

### 2.3. Downloading the kernel

Assume that the working path is `$WORKSPACE`.

```shell
cd $WORKSPACE
git clone git@github.com:RT-Thread/rt-thread.git
```

Enter xuantie/virt64/c906 the location of the BSP directory, the latter operation is not otherwise described, the default is in this directory.

```shell
cd $WORKSPACE/rt-thread/bsp/xuantie/virt64/c906
```

### 2.4. Configuring the kernel

Refresh the configuration file before compiling for the first time.

```shell
scons --menuconfig
```

If you want to use the RT-Thread Smart version, at least turn on the `RT_USING_SMART` option after entering the configuration menu (see the figure below), and the rest depends on your needs.

```kconfiglib
(Top) → RT-Thread Kernel
                                        RT-Thread Project Configuration
(24) The maximal size of kernel object name
[ ] Use the data types defined in ARCH_CPU
[*] Enable RT-Thread Smart (microkernel on kernel/userland)
[ ] Enable RT-Thread Nano
...
```

Save and exit after modification.

### 2.5. Compiling the kernel

If you have compiled before, you can clean it up:

```shell
scons --clean
```

Or compile directly:

```shell
scons -j$(nproc)
```

The kernel binary file `rtthread.bin` will be generated in the `$WORKSPACE/rt-thread/bsp/xuantie/virt64/c906`.

## 3. Running

### 3.1. Installing QEMU

Here the qemu emulator is installed by compiling the `XUANTIE-RV/qemu` repository.

```shell

git clone git@github.com:XUANTIE-RV/qemu.git

mkdir build

cd build

../configure --target-list="riscv64-softmmu riscv64-linux-user"

make -j8

make install
```

After the installation is complete, you can check the version.

```shell
$ qemu-system-riscv64 --version
QEMU emulator version 8.2.94 (v6.1.0-22774-ge0ace167ef)
Copyright (c) 2003-2024 Fabrice Bellard and the QEMU Project developers
```

### 3.2. Running QEMU

The repository has provided a ready-made execution script, which can be executed directly:

```shell
./run.sh
```

#### 3.2.1. Running RT-Thread Smart version

The following is an example:

```shell
$ ./run.sh

OpenSBI v1.4
   ____                    _____ ____ _____
  / __ \                  / ____|  _ \_   _|
 | |  | |_ __   ___ _ __ | (___ | |_) || |
 | |  | | '_ \ / _ \ '_ \ \___ \|  _ < | |
 | |__| | |_) |  __/ | | |____) | |_) || |_
  \____/| .__/ \___|_| |_|_____/|____/_____|
        | |
        |_|

Platform Name             : riscv-virtio,qemu
Platform Features         : medeleg
Platform HART Count       : 1
Platform IPI Device       : aclint-mswi
Platform Timer Device     : aclint-mtimer @ 10000000Hz
Platform Console Device   : uart8250
Platform HSM Device       : ---
Platform PMU Device       : ---
Platform Reboot Device    : syscon-reboot
Platform Shutdown Device  : syscon-poweroff
Platform Suspend Device   : ---
Platform CPPC Device      : ---
Firmware Base             : 0x80000000
Firmware Size             : 323 KB
Firmware RW Offset        : 0x40000
Firmware RW Size          : 67 KB
Firmware Heap Offset      : 0x48000
Firmware Heap Size        : 35 KB (total), 2 KB (reserved), 9 KB (used), 23 KB (free)
Firmware Scratch Size     : 4096 B (total), 328 B (used), 3768 B (free)
Runtime SBI Version       : 2.0

Domain0 Name              : root
Domain0 Boot HART         : 0
Domain0 HARTs             : 0*
Domain0 Region00          : 0x0000000000100000-0x0000000000100fff M: (I,R,W) S/U: (R,W)
Domain0 Region01          : 0x0000000010000000-0x0000000010000fff M: (I,R,W) S/U: (R,W)
Domain0 Region02          : 0x0000000002000000-0x000000000200ffff M: (I,R,W) S/U: ()
Domain0 Region03          : 0x0000000080040000-0x000000008005ffff M: (R,W) S/U: ()
Domain0 Region04          : 0x0000000080000000-0x000000008003ffff M: (R,X) S/U: ()
Domain0 Region05          : 0x000000000c400000-0x000000000c5fffff M: (I,R,W) S/U: (R,W)
Domain0 Region06          : 0x000000000c000000-0x000000000c3fffff M: (I,R,W) S/U: (R,W)
Domain0 Region07          : 0x0000000000000000-0xffffffffffffffff M: () S/U: (R,W,X)
Domain0 Next Address      : 0x0000000080200000
Domain0 Next Arg1         : 0x000000008fe00000
Domain0 Next Mode         : S-mode
Domain0 SysReset          : yes
Domain0 SysSuspend        : yes

Boot HART ID              : 0
Boot HART Domain          : root
Boot HART Priv Version    : v1.10
Boot HART Base ISA        : rv64imafdc
Boot HART ISA Extensions  : zicntr,zihpm
Boot HART PMP Count       : 16
Boot HART PMP Granularity : 2 bits
Boot HART PMP Address Bits: 54
Boot HART MHPM Info       : 16 (0x0007fff8)
Boot HART MIDELEG         : 0x0000000000000222
Boot HART MEDELEG         : 0x000000000000b109
heap: [0x003280c0 - 0x043280c0]

 \ | /
- RT -     Thread Smart Operating System
 / | \     5.2.1 build Jun  9 2025 09:03:23
 2006 - 2024 Copyright by RT-Thread team
lwIP-2.0.3 initialized!
[I/sal.skt] Socket Abstraction Layer initialize success.
[I/utest] utest is initialize success.
[I/utest] total utest testcase num: (1)
[I/drivers.serial] Using /dev/ttyS0 as default console
file system initialization done!
Hello RISC-V
msh />
```

### 3.2.2. Running RT-Thread Smart Edition + Root File System

For the Smart kernel, you can also mount the root filesystem during the boot process by specifying the path to the root filesystem image when executing the `run.sh` script.

Note that the kernel supports fat by default, and if you want to mount an ext4 filesystem, you need to install the lwext4 package, even if you can `PKG_USING_LWEXT4`
> the menuconfig path is (Top) -> RT-Thread online packages -> system). packages -> lwext4: an excellent choice of ext2/3/4 filesystem for microcontrollers.

If you can't find the package in the menu, you can exit menuconfig and run `pkgs --upgrade` to update the package index before trying to enable the package.  
After checking this option, you will also need to update the software and install the source code into the packages directory of bsp as follows (you only need to do this once):

```shell
source ~/.env/env.sh 
pkgs --update 
```

Save and recompile the kernel.

For more information on how to make a root filesystem, please refer to <https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-smart/quick-start/qemu-xuantie/quickstart>, which will not be repeated here.

The example is as follows:

```shell
$ bash run.sh ext4.img

OpenSBI v1.4
   ____                    _____ ____ _____
  / __ \                  / ____|  _ \_   _|
 | |  | |_ __   ___ _ __ | (___ | |_) || |
 | |  | | '_ \ / _ \ '_ \ \___ \|  _ < | |
 | |__| | |_) |  __/ | | |____) | |_) || |_
  \____/| .__/ \___|_| |_|_____/|____/_____|
        | |
        |_|

Platform Name             : riscv-virtio,qemu
Platform Features         : medeleg
Platform HART Count       : 1
Platform IPI Device       : aclint-mswi
Platform Timer Device     : aclint-mtimer @ 10000000Hz
Platform Console Device   : uart8250
Platform HSM Device       : ---
Platform PMU Device       : ---
Platform Reboot Device    : syscon-reboot
Platform Shutdown Device  : syscon-poweroff
Platform Suspend Device   : ---
Platform CPPC Device      : ---
Firmware Base             : 0x80000000
Firmware Size             : 323 KB
Firmware RW Offset        : 0x40000
Firmware RW Size          : 67 KB
Firmware Heap Offset      : 0x48000
Firmware Heap Size        : 35 KB (total), 2 KB (reserved), 9 KB (used), 23 KB (free)
Firmware Scratch Size     : 4096 B (total), 328 B (used), 3768 B (free)
Runtime SBI Version       : 2.0

Domain0 Name              : root
Domain0 Boot HART         : 0
Domain0 HARTs             : 0*
Domain0 Region00          : 0x0000000000100000-0x0000000000100fff M: (I,R,W) S/U: (R,W)
Domain0 Region01          : 0x0000000010000000-0x0000000010000fff M: (I,R,W) S/U: (R,W)
Domain0 Region02          : 0x0000000002000000-0x000000000200ffff M: (I,R,W) S/U: ()
Domain0 Region03          : 0x0000000080040000-0x000000008005ffff M: (R,W) S/U: ()
Domain0 Region04          : 0x0000000080000000-0x000000008003ffff M: (R,X) S/U: ()
Domain0 Region05          : 0x000000000c400000-0x000000000c5fffff M: (I,R,W) S/U: (R,W)
Domain0 Region06          : 0x000000000c000000-0x000000000c3fffff M: (I,R,W) S/U: (R,W)
Domain0 Region07          : 0x0000000000000000-0xffffffffffffffff M: () S/U: (R,W,X)
Domain0 Next Address      : 0x0000000080200000
Domain0 Next Arg1         : 0x000000008fe00000
Domain0 Next Mode         : S-mode
Domain0 SysReset          : yes
Domain0 SysSuspend        : yes

Boot HART ID              : 0
Boot HART Domain          : root
Boot HART Priv Version    : v1.10
Boot HART Base ISA        : rv64imafdc
Boot HART ISA Extensions  : zicntr,zihpm
Boot HART PMP Count       : 16
Boot HART PMP Granularity : 2 bits
Boot HART PMP Address Bits: 54
Boot HART MHPM Info       : 16 (0x0007fff8)
Boot HART MIDELEG         : 0x0000000000000222
Boot HART MEDELEG         : 0x000000000000b109
heap: [0x003404c0 - 0x043404c0]

 \ | /
- RT -     Thread Smart Operating System
 / | \     5.2.1 build Jun 13 2025 09:43:35
 2006 - 2024 Copyright by RT-Thread team
[I/utest] utest is initialize success.
[I/utest] total utest testcase num: (1)
[I/drivers.serial] Using /dev/ttyS0 as default console
[W/DFS.fs] mount / failed with file system type: elm
file system initialization done!
Hello RISC-V
msh />/ # 
/ # 
/ # ls
bin         lib         proc        sbin        usr
dev         lost+found  root        services    var
etc         mnt         run         tmp
/ #
```

## 4. Contact Information

If you are interested in making an inquiry, please contact: <business@rt-thread.com>
