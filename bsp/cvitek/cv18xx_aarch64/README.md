# Milkv-Duo256M 板级支持包说明

## 1. 简介

Milk-V Duo 256M 是 Duo 的升级版本，内存提升至 256M，满足需要更大内存容量的应用。采用 SG2002 计算系列芯片，计算能力提升至 1.0TOPS@INT8。它可以实现 RISC-V/ARM 架构之间的无缝切换，并支持双系统同时运行。此外，它还包含 SPI、UART 等一系列丰富的 GPIO 接口，适合边缘智能监控领域的各种硬件开发，包括 IP 摄像头、智能猫眼锁、可视门铃等。

该板级支持包主要是针对**ARM架构的大核**实现的一份移植，支持RT-Thread标准版和Smart版内核。

## 2. 编译说明

推荐使用ubuntu20的[env环境](https://github.com/RT-Thread/env)，当然也可以使用windows上的[env工具](https://www.rt-thread.org/download.html#download-rt-thread-env-tool)进行编译。下面介绍**标准版**和**Smart版本**的编译流程。

### 2.1 RT-Thread编译

**1.menuconfig配置工程：**

该BSP默认menuconfig支持的就是RT-Thread标准版，无需配置工程。

**2.配置工具链相关环境：**

依次执行下面命令进行环境变量的相关配置：

```shell
export RTT_CC=gcc
export RTT_EXEC_PATH="/opt/tools/gnu_gcc/arm-gnu-toolchain-13.2.Rel1-x86_64-aarch64-none-elf/bin"
export RTT_CC_PREFIX=aarch64-none-elf-
export PATH=$PATH:$RTT_EXEC_PATH
```

**3.编译：**

```shell
scons -j12
```

### 2.2 RT-Smart编译

**1.menuconfig配置工程：**

```shell
RT-Thread Kernel --->
    [*] Enable RT-Thread Smart (microkernel on kernel/userland)
```

**2.配置工具链相关环境：**

依次执行下面命令进行环境变量的相关配置：

```shell
export RTT_CC=gcc
export RTT_EXEC_PATH="/opt/tools/gnu_gcc/aarch64-linux-musleabi_for_x86_64-pc-linux-gnu/bin"
export RTT_CC_PREFIX=aarch64-linux-musleabi-
export PATH=$PATH:$RTT_EXEC_PATH
```

**3.编译：**

```shell
scons -j12
```

如果编译正确无误，会产生 `rtthread.elf`, `rtthread.bin` 文件。

## 3. 运行

### 3.1 uboot加载rtthread.bin

1. 将 SD 卡分为 2 个分区，第 1 个分区用于存放 bin 文件，第 2 个分区用于作为数据存储分区，分区格式为 `FAT32`。

2. 将bsp的boot目录下的 `fip.bin` 和编译生成的 `rtthread.bin` 复制 SD 卡第一个分区中。后续更新固件只需要复制 `rtthread.bin` 文件即可。

配置**串口0**参数： 115200 8N1 ，硬件和软件流控为关。

进入uboot命令行后依次输入以下命令。

```shell
fatload mmc 0:1 0x80200000 rtthread.bin
dcache flush
go 0x80200000
```

> 0x80200000为rtthread.bin加载到内存的位置，可在menuconfig中自己修改，注意不能与小核固件加载位置重叠。

### 3.2 uboot加载boot.sd

1. 将 SD 卡分为 2 个分区，第 1 个分区用于存放 bin 文件，第 2 个分区用于作为数据存储分区，分区格式为 `FAT32`。

2. 将bsp的boot目录下的 `fip.bin` 和编译生成的 `boot.sd` 复制 SD 卡第一个分区中。后续更新固件只需要复制 `boot.sd` 文件即可。

配置**串口0**参数： 115200 8N1 ，硬件和软件流控为关。

直接上电运行，uboot会自动调用bootcmd解析boot.sd文件，然后加载`rtthread.bin`运行。

### 3.3 如何生成fip.bin

在本bsp的boot/milkv-duo256m目录下存放了所有需要构建出fip.bin的一些依赖文件和相关脚本。用户只需要在boot目录下执行`combine.sh`即可生成fip.bin。

> 如何用户编译了小核c906_little的bsp，那么`combine.sh`脚本将会生成带有小核程序的fip.bin。未编译则不会。

完成后可以看到串口的输出信息：

**标准版log信息：**

```shell
heap: [0x8028f2b0 - 0x84000000]

 \ | /
- RT -     Thread Operating System
 / | \     5.1.0 build Apr 16 2024 00:05:56
 2006 - 2024 Copyright by RT-Thread team
hello rt-thread!
msh />
```

**Smart版log信息：**

```shell
heap: [0x002f62c0 - 0x04000000]

 \ | /
- RT -     Thread Smart Operating System
 / | \     5.1.0 build Apr 16 2024 00:04:47
 2006 - 2024 Copyright by RT-Thread team
[E/lwp] lwp_startup: init program not found
Switching to legacy mode...
hello rt-thread!
msh />
```
## 4. 注意事项

目前RISC-V(Smart版本)支持外设物理地址映射到完全相同的虚拟地址，而ARM(Smart版本)目前是不支持这样搞的，所以在编写驱动的时候应该使用rt_ioremap这样的函数将物理地址映射到可访问的虚拟地址上去。为了保证ARM的Smart版本内核能够成功运行，目前仅对uart和pinctrl的驱动进行了适配。其他驱动可能会因为未进行ioremap（IO口重映射）导致不可用。

## 5. 联系人信息

维护人：[liYony](https://github.com/liYony)
