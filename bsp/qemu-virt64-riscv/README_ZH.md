# QEMU/RISCV64 VIRT板级支持包说明

中文页 | [English](README.md)

## 1. 简介

RISC-V是一种开放和免费的指令集体系结构(ISA)。本工程是在QEMU的RISCV64 VIRT版本上进行的一份移植。

## 2. 编译说明

首先可以下载交叉编译工具链,建议采用sifive的工具链进行编译。
```
https://www.sifive.com/software
```
选择对应的平台即可。

这里推荐在Ubuntu上进行开发工作。

解压工具链到指定的目录。

```
export RTT_EXEC_PATH=~/gcc/bin
```

进入到`rt-thread/bsp/qemu-virt64-riscv`目录进行输入
```
scons
```
可以看到正常生成`rtthread.elf`与`rtthread.bin`文件。

或者通过 `scons --exec-path="GCC工具链路径"` 命令，在指定工具链位置的同时直接编译。

## 3. 执行

本工程提供了riscv64的两种可配置运行模式,默认运行在M-Mode下。

*M-Mode*

首先安装`qemu-system-riscv64`。

```
sudo apt install qemu-system-misc
```
直接输入
```
./qemu-nographic.sh
```
可以看到程序运行

```
heap: [0x80035804 - 0x86435804]

 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build May 21 2021
 2006 - 2021 Copyright by rt-thread team
Hello RISC-V!
msh />
```

*S-Mode*

如果运行在S-Mode下，那么需要通过menuconfig选择配置

```
scons --menuconfig
```
选择如下：
```
RISCV qemu virt64 configs  ---> 
    [*] RT-Thread run in riscv smode
```
保存后，重新`scons`编译即可。

要让rt-thread运行在S-Mode，首先需要启动opensbi,然后通过opensbi启动rt-thread。

自行编译的qemu或者下载的高版本的qemu内置opensbi，执行`./qemu-nographic-smode.sh`即可正常运行。

通过`sudo apt install qemu-system-misc`安装的qemu版本较低，可自行编译opensbi。

```
git clone git@github.com:riscv/opensbi.git
cd opensbi
make PLATFORM=generic CROSS_COMPILE=~/gcc/bin/riscv64-unknown-elf-
```
最后生成的`/build/platform/generic/firmware/fw_jump.elf`则是需要的文件。

输入以下的命令即可运行:

```
qemu-system-riscv64 -nographic -machine virt -m 256M -kernel rtthread.bin -bios ~/opensbi/build/platform/generic/firmware/fw_jump.elf
```
可以看到如下的结果
```
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
.
.
.
Boot HART ISA             : rv64imafdcsu
Boot HART Features        : scounteren,mcounteren
Boot HART PMP Count       : 16
Boot HART PMP Granularity : 4
Boot HART PMP Address Bits: 54
Boot HART MHPM Count      : 0
Boot HART MHPM Count      : 0
Boot HART MIDELEG         : 0x0000000000000222
Boot HART MEDELEG         : 0x000000000000b109
heap: [0x80235a58 - 0x86635a58]

 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build May 21 2021
 2006 - 2021 Copyright by rt-thread team
Hello RISC-V!
msh />
```
## 4. 支持情况

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0 |
| PLIC | 支持 | - |
| CLIC | 支持 | - |

## 5. 联系人信息

维护人：[bernard][1]

[1]: https://github.com/BernardXiong
