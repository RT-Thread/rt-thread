**QEMU/RISCV64 VIRT 板级支持包使用说明**

中文页 | [English](./README.md)

<!-- TOC -->

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
- [4. 如何使用 rv64ilp32 工具链](#4-如何使用-rv64ilp32-工具链)
- [5. 联系人信息](#5-联系人信息)

<!-- /TOC -->

# 1. 简介

RISC-V 是一种开放和免费的指令集体系结构 (ISA)。本工程是在 QEMU 的 RISCV64 VIRT 版本上进行的一份移植。

本工程支持玄铁团队联合中科院软件所共同推出的全球首款 rv64ilp32 产品级开源工具链。

# 2. 构建

工作系统：以 Ubuntu 22.04 为例：

```shell
$ lsb_release -a
No LSB modules are available.
Distributor ID: Ubuntu
Description:    Ubuntu 22.04.2 LTS
Release:        22.04
Codename:       jammy
```

## 2.1. 安装工具链

具体使用的工具链，和 RT-Thread 官方保持一致，具体的工具链版本可以参考 RT-Thread 仓库的 <https://github.com/RT-Thread/rt-thread/blob/master/.github/workflows/action_utest.yml> 这个文件。

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

其中 `riscv64-unknown-elf-gcc` 用于构建 RT-Thread 标准版，`riscv64-unknown-linux-musl-gcc` 用于构建 RT-Thread Smart 版。根据上面所示链接分别下载到本地后解压缩。

## 2.2. 设置 RT-Thread 工具链环境变量

和 RT-Thread 工具链相关的环境变量有三个

- `RTT_CC` 为工具链名称, 这里统一为 `"gcc"`
- `RTT_CC_PREFIX`: 为工具链前缀, 这里对于标准版是 `"riscv64-unknown-elf-"`，对于 Smart 版是 `"riscv64-unknown-linux-musl-"`。
- `RTT_EXEC_PATH`: 工具链的 bin 文件夹所在路径, 如 `"$HOME/tools/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14/bin"`, 这个根据个人下载解压后的实际路径进行设置，注意 RT-Thread 标准版和 Smart 版本的工具链是两套不同的版本，而且设置 `RTT_EXEC_PATH` 的路径名时要一直到 `bin`。

如果一直使用的话，建议将这三个环境变量在 `.bashrc` 文件中 export。

## 2.3. 下载内核

假设工作路径是 `$WORKSPACE`。

```shell
$ cd $WORKSPACE
$ git clone git@github.com:RT-Thread/rt-thread.git
```

**注：本文档基于的内核版本 git commit ID 为: ebe2926cd6。**

进入 qemu-virt64-riscv 所在 BSP 目录，后面的操作不做另外介绍，默认就在这个目录下。

```shell
$ cd $WORKSPACE/rt-thread/bsp/qemu-virt64-riscv
```

## 2.4. 配置内核

第一次编译前先刷新一下配置文件。

```shell
$ scons --menuconfig
```

默认配置就是 RT-Thread 标准版，所以如果没有什么特别需求，什么都不要改动，直接保存退出即可。

如果要使用 RT-Thread Smart 版，进入配置菜单后至少要打开 `RT_USING_SMART` 这个选项(见下图)，其他的看自己的需求。

```
(Top) → RT-Thread Kernel
                                                                RT-Thread Project Configuration
(24) The maximal size of kernel object name
[ ] Use the data types defined in ARCH_CPU
[*] Enable RT-Thread Smart (microkernel on kernel/userland)
[ ] Enable RT-Thread Nano
...
```

修改后保存退出。

## 2.5. 编译内核

如果以前编译后，可以清理一下：

```shell
$ scons --clean
```

或者直接编译：

```shell
$ scons -j$(nproc)
```

在 `$WORKSPACE/rt-thread/bsp/qemu-virt64-riscv` 路径下会生成内核的二进制文件 `rtthread.bin`。

# 3. 运行

## 3.1. 安装 QEMU

```shell
$ sudo apt update
$ sudo apt install qemu-system-misc
```

安装完毕后可以看一下版本。

```shell
$ qemu-system-riscv64 --version
QEMU emulator version 6.2.0 (Debian 1:6.2+dfsg-2ubuntu6.24)
Copyright (c) 2003-2021 Fabrice Bellard and the QEMU Project developers
```

## 3.2. 运行 QEMU

仓库里已经提供了现成的执行脚本，可以直接执行：

```shell
$ ./qemu-nographic.sh
```

RT-Thread 标准版运行结果如下：

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

RT-Thread Smart 版本运行结果如下：

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

# 4. 如何使用 rv64ilp32 工具链

- 工具链地址：https://github.com/ruyisdk/riscv-gnu-toolchain-rv64ilp32/tags

- 使用方法：

  - 配置工具链路径

  - 修改ABI参数为：`-mabi=ilp32d`

  - 然后执行常规编译

  - 使用 [脚本](./qemu-rv64ilp32-nographic.sh) 启动 QEMU (INFO: QEMU 二进制同样在工具链目录)

- 使用传统 64 位工具链与使用新 32 位工具链编译相同工程的固件大小对比：

  传统 64 位工具链固件大小：

  ```bash
  Memory region         Used Size  Region Size  %age Used
              SRAM:      225856 B        16 MB      1.35%
  riscv64-unknown-elf-objcopy -O binary rtthread.elf rtthread.bin
  riscv64-unknown-elf-size rtthread.elf
     text    data     bss     dec     hex filename
   150907    3664   71268  225839   3722f rtthread.elf
  ```

  新 32 位工具链固件大小：

  ```bash
  Memory region         Used Size  Region Size  %age Used
              SRAM:      209376 B        16 MB      1.25%
  riscv64-unknown-elf-objcopy -O binary rtthread.elf rtthread.bin
  riscv64-unknown-elf-size rtthread.elf
     text    data     bss     dec     hex filename
   138739    1356   69276  209371   331db rtthread.elf
  ```

# 5. 联系人信息

维护人：[bernard][1]

[1]: https://github.com/BernardXiong



