
# QEMU/RISCV64/C906 VIRT 板级支持包使用说明

中文页 | [English](./README.md)

<!-- TOC -->

- [QEMU/RISCV64/C906 VIRT 板级支持包使用说明](#qemuriscv64c906-virt-板级支持包使用说明)
  - [1. 简介](#1-简介)
  - [2. 构建](#2-构建)
    - [2.1. 安装工具链](#21-安装工具链)
    - [2.2. 设置 RT-Thread 工具链环境变量](#22-设置-rt-thread-工具链环境变量)
    - [2.3. 下载内核](#23-下载内核)
    - [2.4. 配置内核](#24-配置内核)
    - [2.5. 编译内核](#25-编译内核)
  - [3. 运行](#3-运行)
    - [3.1. 安装 QEMU](#31-安装-qemu)
    - [3.2. 运行 QEMU](#32-运行-qemu)
      - [3.2.1. 运行 RT-Thread Smart 版](#321-运行-rt-thread-smart-版)
    - [3.2.2. 运行 RT-Thread Smart 版 + 根文件系统](#322-运行-rt-thread-smart-版--根文件系统)
  - [4. 联系人信息](#4-联系人信息)

<!-- /TOC -->

## 1. 简介

RISC-V 是一种开放和免费的指令集体系结构 (ISA)。本工程基于 QEMU 的 RISC-V64 VIRT 平台，移植至 C906 处理器平台。

## 2. 构建

工作系统：以 Ubuntu 24.04 为例：

```shell
$ lsb_release -a
No LSB modules are available.
Distributor ID: Ubuntu
Description:    Ubuntu 24.04.2 LTS
Release:        24.04
Codename:       noble
```

### 2.1. 安装工具链

- 编译器： [Xuantie-900-gcc-linux-6.6.0-musl64-x86_64-V3.0.2-20250410.tar.gz](https://github.com/RT-Thread/toolchains-ci/releases/download/v1.9/Xuantie-900-gcc-linux-6.6.0-musl64-x86_64-V3.0.2.tar.gz)
- 模拟器： [Xuantie-qemu-x86_64-Ubuntu-20.04-V5.0.5-B20250108-0335.tar.gz](https://www.xrvm.cn/community/download?id=4397435198627713024)

注：若上述链接中的模拟器不能使用，可以使用下述仓库编译模拟器
> [XUANTIE-RV/qemu](https://github.com/XUANTIE-RV/qemu)

### 2.2. 设置 RT-Thread 工具链环境变量

和 RT-Thread 工具链相关的环境变量有三个

- `RTT_CC` 为工具链名称, 这里统一为 `"gcc"`
- `RTT_CC_PREFIX`: 为工具链前缀, 这里对于标准版是 `"riscv64-unknown-elf-"`，对于 Smart 版是 `"riscv64-unknown-linux-musl-"`。
- `RTT_EXEC_PATH`: 工具链的 bin 文件夹所在路径, 如 `"$HOME/tools/Xuantie-900-gcc-linux-6.6.0-musl64-x86_64-V3.0.2/bin"`, 这个根据个人下载解压后的实际路径进行设置，注意 RT-Thread 标准版和 Smart 版本的工具链是两套不同的版本，而且设置 `RTT_EXEC_PATH` 的路径名时要一直到 `bin`。

>注：对于不同的工具链`RTT_CC_PREFIX`可能有所不同，可在工具链 bin 文件夹所在路径下查看  
如果一直使用的话，建议将这三个环境变量在 `.bashrc` 文件中 export。

### 2.3. 下载内核

假设工作路径是 `$WORKSPACE`。

```shell
cd $WORKSPACE
git clone git@github.com:RT-Thread/rt-thread.git
```

进入 xuantie/virt64/c906 所在 BSP 目录，后面的操作不做另外介绍，默认就在这个目录下。

```shell
cd $WORKSPACE/rt-thread/bsp/xuantie/virt64/c906
```

### 2.4. 配置内核

第一次编译前先刷新一下配置文件。

```shell
scons --menuconfig
```

要使用 RT-Thread Smart 版，进入配置菜单后至少要打开 `RT_USING_SMART` 这个选项(见下图)，其他的看自己的需求,如果此处已开启，直接保存退出即可。

```kconfiglib
(Top) → RT-Thread Kernel
                                        RT-Thread Project Configuration
(24) The maximal size of kernel object name
[ ] Use the data types defined in ARCH_CPU
[*] Enable RT-Thread Smart (microkernel on kernel/userland)
[ ] Enable RT-Thread Nano
...
```

修改后保存退出。

### 2.5. 编译内核

如果以前编译后，可以清理一下：

```shell
scons --clean
```

或者直接编译：

```shell
scons -j$(nproc)
```

在 `$WORKSPACE/rt-thread/bsp/xuantie/virt64/c906` 路径下会生成内核的二进制文件 `rtthread.bin`。

## 3. 运行

### 3.1. 安装 QEMU

这里通过编译`XUANTIE-RV/qemu`仓库安装qemu模拟器

```shell

git clone git@github.com:XUANTIE-RV/qemu.git

mkdir build

cd build

../configure --target-list="riscv64-softmmu riscv64-linux-user"

make -j8

make install

```

安装完毕后可以看一下版本。

```shell
$ qemu-system-riscv64 --version
QEMU emulator version 8.2.94 (v6.1.0-22774-ge0ace167ef)
Copyright (c) 2003-2024 Fabrice Bellard and the QEMU Project developers
```

### 3.2. 运行 QEMU

仓库里已经提供了现成的执行脚本，可以直接执行：

```shell
 ./run.sh
```

#### 3.2.1. 运行 RT-Thread Smart 版

示例如下：

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

### 3.2.2. 运行 RT-Thread Smart 版 + 根文件系统

对于 Smart 版本的内核，也可以在执行 `run.sh` 脚本时指定根文件系统镜像文件的路径在启动过程中挂载根文件系统。

需要注意的是，内核默认支持 fat, 如果要挂载 ext4 的文件系统，则还需要额外安装 lwext4 软件包，即使能 `PKG_USING_LWEXT4`
>具体 menuconfig 路径是 (Top) -> RT-Thread online packages -> system packages ->  lwext4: an excellent choice of ext2/3/4 filesystem for microcontrollers

如果在菜单中找不到该软件包，可以退出 menuconfig 并执行 `pkgs --upgrade` 更新软件包索引后再尝试使能软件包。  
勾选该选项后还需要执行如下操作更新软件并安装源码到 bsp 的 packages 目录下(该操作只要执行一次即可)：

```shell
source ~/.env/env.sh
pkgs --update
```

保存后重新编译内核。

有关如何制作根文件系统,以及更多详细内容，请参考 <https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-smart/quick-start/qemu-xuantie/quickstart>，这里不再赘述。

示例如下：

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

## 4. 联系人信息

如有意向咨询请联系：<business@rt-thread.com>
