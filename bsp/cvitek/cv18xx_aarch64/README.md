<!-- TOC -->

- [1. 概述](#1-概述)
	- [1.1. 驱动支持列表](#11-驱动支持列表)
- [2. 构建说明](#2-构建说明)
	- [2.1. Toolchain 下载](#21-toolchain-下载)
	- [2.2. 依赖安装](#22-依赖安装)
	- [2.3. 执行构建](#23-执行构建)
		- [2.3.1. 开发板选择](#231-开发板选择)
		- [2.3.2. 开启 RT-Smart](#232-开启-rt-smart)
		- [2.3.3. 编译大核固件 `boot.sd`](#233-编译大核固件-bootsd)
		- [2.3.4. 编译小核固件 `fip.bin`](#234-编译小核固件-fipbin)
- [3. 运行](#3-运行)
	- [3.1. RT-Thread 标准版的例子](#31-rt-thread-标准版的例子)
	- [3.2. RT-Thread Smart 版的例子](#32-rt-thread-smart-版的例子)
- [4. 联系人信息](#4-联系人信息)

<!-- /TOC -->

# 1. 概述

本文档用于介绍 BSP "cv18xx_aarch64"，该 BSP 目前仅支持 Milk-V Duo 256M 的 ARM Cortex A53 大核。支持 RT-Thread 标准版和 RT-Thread Smart 版内核。

## 1.1. 驱动支持列表

| 驱动  | 支持情况 | 备注              |
| :---- | :------- | :---------------- |
| uart  | 支持     | 默认波特率115200  |

# 2. 构建说明

**注：当前 bsp 只支持 Linux 环境下编译，推荐 ubuntu 22.04**

## 2.1. Toolchain 下载

用于编译 RT-Thread 标准版和 RT-Thread Smart 版的工具链可以通用，下载地址：<https://github.com/RT-Thread/toolchains-ci/releases/download/v1.7/aarch64-linux-musleabi_for_x86_64-pc-linux-gnu_stable.tar.bz2>。

正确解压后(假设解压到 `/opt` 下, 也可以自己设定解压后的目录)，导出如下环境变量，建议将这些 export 命令写入 `~/.bashrc`。

```shell
export RTT_CC="gcc"
export RTT_CC_PREFIX=aarch64-linux-musleabi-
export RTT_EXEC_PATH=/opt/aarch64-linux-musleabi_for_x86_64-pc-linux-gnu/bin
```

## 2.2. 依赖安装

参考 [bsp cvitek 的 README.md 文件](../README.md)。

## 2.3. 执行构建

这里我们只需要构建 ARM 大核的 OS，进入 `bsp/cvitek/cv18xx_aarch64` 目录下（记为当前工作目录 `$CWD`），依次执行以下步骤：

### 2.3.1. 开发板选择

```shell
$ scons --menuconfig
```

选择当前需要编译的目标开发板类型，默认是 "milkv-duo256m"，目前也仅支持了 "milkv-duo256m"。

### 2.3.2. 开启 RT-Smart

目前 ARM 的大核默认没有开启 RT-Smart，默认配置是 RT 标准版，如果要对大核启用 RT-Smart，可以按如下方式设置。

```shell
RT-Thread Kernel  --->
    [*] Enable RT-Thread Smart (microkernel on kernel/userland)
```

### 2.3.3. 编译大核固件 `boot.sd`

```shell
$ scons
```

如果编译正确无误，在 $CWD 下会产生 `rtthread.elf`, `rtthread.bin` 文件。同时在 `$CWD/../output/milkv-duo256m/` 下生成 `boot.sd` 文件，`boot.sd` 中封装了 RT-Thread 的内核 `rtthread.bin`。

### 2.3.4. 编译小核固件 `fip.bin`

`fip.bin`：这是一个打包后生成的 bin 文件，包含了 `fsbl`、`uboot` 以及小核的内核镜像文件 `rtthread.bin`。Duo 256m 的小核是一个 RISC-V 的 core，对应的 bsp 是 c906_little。具体构建的说明参考 [对应的 README 文件](../README.md)。但注意 BSP `c906_little` 构建生成的 `fip.bin` 中的 `fsbl`、`uboot` 这些文件都是 RISC-V 的，所以我们并不能把 BSP `c906_little` 构建生成的 `fip.bin` 直接拿来用。

为此 BSP `cv18xx_aarch64` 下预先提供了 ARM 核上可以运行的 `fsbl`、`uboot` 等文件，在 `bsp/cvitek/cv18xx_aarch64/prebuild/milkv-duo256m` 下，可以用来打包生成 ARM 的 `fip.bin`。具体打包的脚本是 BSP `cv18xx_aarch64` 目录下的 `combine.sh`。

所以如果您需要使用最新的小核版本，可以先基于 BSP `c906_little` 做出 `rtthread.bin`，然后在 cv18xx_aarch64 目录下运行 `combine.sh` 即可生成 ARM 可用的 `fip.bin`。生成路径和 `boot.sd` 一样，在 `$CWD/../output/milkv-duo256m/` 下。

```shell
$ cd $CWD
$ ./combine.sh
```

如果您不关心小核的版本，BSP cv18xx_aarch64 也提供了一个 prebuild 的 `fip.bin`，在 `bsp/cvitek/cv18xx_aarch64/prebuild/milkv-duo256m` 下，直接烧录到 sd-card 中就可以使用。

# 3. 运行

1. 将 SD 卡分为 2 个分区，第 1 个分区的分区格式为 `FAT32`，用于存放 `fip.bin` 和 `boot.sd` 文件，第 2 个分区可选，如果有可用于作为数据存储分区或者存放文件系统。

2. 将 `fip.bin` (自己打包生成的或者 prebuild 的) 和编译生成的 `boot.sd` 复制到 SD 卡第一个分区中。`fip.bin` 是小核启动固件，如果只关注 ARM 大核系统，后续只需更新大核的固件，即更新 `boot.sd` 文件即可。

3. Duo256M 的大核可以选择使用 RISC-V 或者 ARM，默认使用的是 RISC-V 核，所以这里需要通过短接物理引脚 35（Boot-Switch）和 GND 来切换到 ARM 核。具体参考 [Milk-V Duo 256M 的官方说明](https://milkv.io/zh/docs/duo/getting-started/duo256m#risc-v-%E4%B8%8E-arm-%E5%88%87%E6%8D%A2)。

4. 配置 **串口0** 参数： 115200 8N1 ，硬件和软件流控为关。

直接上电运行，uboot 会自动调用 bootcmd 解析 `boot.sd` 文件，然后加载 `rtthread.bin` 运行。

## 3.1. RT-Thread 标准版的例子

```shell
......

U-Boot 2021.10-ga57aa1f29b (Apr 20 2024 - 23:53:08 +0800)cvitek_cv181x

......

Starting kernel ...

[I/rtdm.ofw] Booting RT-Thread on physical CPU 0x0
[I/rtdm.ofw] Machine model: SOPHGO ASIC. ARM.
[I/rtdm.ofw] Memory node(1) ranges: 0x0000000080000000 - 0x000000008fe00000
[E/rtdm.ofw] Allocating reserved memory in setup is not yet supported
[E/rtdm.ofw] Allocating reserved memory in setup is not yet supported
[I/mm.memblock] System memory:
[I/mm.memblock]                    [0x0000000080000000, 0x000000008fe00000]
[I/mm.memblock] Reserved memory:
[I/mm.memblock]                    [0x0000000080000000, 0x0000000080080000]
[I/mm.memblock]                    [0x0000000080200000, 0x00000000802dd000]
[I/mm.memblock]                    [0x00000000802dd000, 0x00000000842dd000]
[I/mm.memblock]                    [0x00000000842dd000, 0x00000000844dd000]
[I/mm.memblock]                    [0x00000000844dd000, 0x00000000844e2000]
[I/mm.memblock] physical memory region [0x0000000080080000-0x0000000080200000] installed to system page
[I/mm.memblock] physical memory region [0x00000000844e2000-0x000000008fe00000] installed to system page
[I/mm.memblock] 195 MB memory installed to system page
[I/drv.pinmux] Pin Name = "UART0_RX", Func Type = 281, selected Func [0]

[I/drv.pinmux] Pin Name = "UART0_TX", Func Type = 282, selected Func [0]

[I/osi.psci] Using PSCI v1.0 Function IDs
[I/rtdm.ofw] Console: uart0 (<no-node>)

 \ | /
- RT -     Thread Operating System
 / | \     5.2.0 build Dec 25 2024 14:16:49
 2006 - 2024 Copyright by RT-Thread team
[I/rtdm.mnt] File system initialization done
hello rt-thread!
msh />
```

## 3.2. RT-Thread Smart 版的例子

```shell
U-Boot 2021.10-ga57aa1f29b (Apr 20 2024 - 23:53:08 +0800)cvitek_cv181x

......

Starting kernel ...

[I/rtdm.ofw] Booting RT-Thread on physical CPU 0x0
[I/rtdm.ofw] Machine model: SOPHGO ASIC. ARM.
[I/rtdm.ofw] Memory node(1) ranges: 0x0000000080000000 - 0x000000008fe00000
[E/rtdm.ofw] Allocating reserved memory in setup is not yet supported
[E/rtdm.ofw] Allocating reserved memory in setup is not yet supported
[I/mm.memblock] System memory:
[I/mm.memblock]                    [0x0000000080000000, 0x000000008fe00000]
[I/mm.memblock] Reserved memory:
[I/mm.memblock]                    [0x0000000080000000, 0x0000000080080000]
[I/mm.memblock]                    [0x0000000080200000, 0x0000000080346000]
[I/mm.memblock]                    [0x0000000080346000, 0x0000000084346000]
[I/mm.memblock]                    [0x0000000084346000, 0x0000000084546000]
[I/mm.memblock]                    [0x0000000084546000, 0x000000008454b000]
[I/mm.memblock] physical memory region [0x0000000080080000-0x0000000080200000] installed to system page
[I/mm.memblock] physical memory region [0x000000008454b000-0x000000008fe00000] installed to system page
[I/mm.memblock] 195 MB memory installed to system page
[I/drv.pinmux] Pin Name = "UART0_RX", Func Type = 281, selected Func [0]

[I/drv.pinmux] Pin Name = "UART0_TX", Func Type = 282, selected Func [0]

[I/osi.psci] Using PSCI v1.0 Function IDs
[I/rtdm.ofw] Console: uart0 (<no-node>)

 \ | /
- RT -     Thread Smart Operating System
 / | \     5.2.0 build Dec 25 2024 12:10:56
 2006 - 2024 Copyright by RT-Thread team
[I/drivers.serial] Using /dev/ttyS0 as default console
[I/rtdm.mnt] File system initialization done
hello rt-thread!
msh />
```

# 4. 联系人信息

维护人：[liYony](https://github.com/liYony)
