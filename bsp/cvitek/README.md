<!-- TOC -->

- [1. 参考文档](#1-参考文档)
- [2. 概述](#2-概述)
- [3. BSP 支持情况](#3-bsp-支持情况)
	- [3.1. 驱动支持列表](#31-驱动支持列表)
	- [3.2. 默认串口控制台管脚配置](#32-默认串口控制台管脚配置)
- [4. 编译](#4-编译)
	- [4.1. Toolchain 下载](#41-toolchain-下载)
	- [4.2. 依赖安装](#42-依赖安装)
	- [4.3. 构建](#43-构建)
		- [4.3.1. 开发板选择](#431-开发板选择)
		- [4.3.2. 开启 RT-Smart](#432-开启-rt-smart)
		- [4.3.3. 编译](#433-编译)
- [5. 运行](#5-运行)
- [6. 大核 RT-Smart 启动并自动挂载根文件系统](#6-大核-rt-smart-启动并自动挂载根文件系统)
	- [6.1. 内核构建配置](#61-内核构建配置)
	- [6.2. 构建文件系统](#62-构建文件系统)
	- [6.3. 将文件系统写入 sd-card](#63-将文件系统写入-sd-card)
	- [6.4. 上电启动](#64-上电启动)
- [7. FAQ](#7-faq)
- [8. 联系人信息](#8-联系人信息)

<!-- /TOC -->

# 1. 参考文档

- 【参考 1】CV1800B/CV1801B Datasheet（中文版）：<https://github.com/milkv-duo/duo-files/blob/main/duo/datasheet/CV1800B-CV1801B-Preliminary-Datasheet-full-zh.pdf>
- 【参考 2】SG2002/SG2000 技术参考手册（中文版）：<https://github.com/sophgo/sophgo-doc/releases>。官方定期发布 pdf 形式。可以下载下载最新版本的中文版本技术参考手册：`sg2002_trm_cn.pdf` 或者 `sg2000_trm_cn.pdf`。

# 2. 概述

支持开发板以及集成 SoC 芯片信息如下

- milk-v duo: [https://milkv.io/duo](https://milkv.io/duo)，SoC 采用 CV1800B。
- milk-v duo256m: [https://milkv.io/duo256m](https://milkv.io/docs/duo/getting-started/duo256m)，SoC 采用 SG2002（原 CV181xC）。
- milk-v duos: [https://milkv.io/duos](https://milkv.io/docs/duo/getting-started/duos)，SoC 采用 SG2000（原 CV181xH）。

Duo 家族开发板采用 CV18xx 系列芯片。芯片的工作模式总结如下：

- CV1800B，支持一种工作模式：
  - 大核（RISC-V C906@1GHz）+ 小核（RISC-V C906@700MHz）。
- SG2002（原 CV181xC），支持两种工作模式，通过管脚 GPIO_RTX 的外围电路控制进行切换：
  - 大核（RISC-V C906@1GHz）+ 小核（RISC-V C906@700MHz）。
  - 大核（ARM Cortex-A53@1GHz）+ 小核（RISC-V C906@700MHz）。
- SG2000（原 CV181xH），支持两种工作模式，通过管脚 GPIO_RTX 的外围电路控制进行切换：
  - 大核（RISC-V C906@1GHz）+ 小核（RISC-V C906@700MHz）。
  - 大核（ARM Cortex-A53@1GHz）+ 小核（RISC-V C906@700MHz）。

# 3. BSP 支持情况

由于大小核的存在，以及不同 SoC 下不同工作模式的存在，bsp/cvitek 提供了三种不同 BSP/OS，需要单独编译。

| BSP 名称      | 大小核  | 芯片架构        | 默认串口控制台 | 备注     |
| ------------- | ------- |---------------- | -------------- | -------- |
| cv18xx_risc-v | 大核    | RISC-V C906     | uart0          | 支持 MMU，支持 RT-Thread 标准版 和 RT-SMART 模式，默认运行 RT-SMART 版本 |
| c906-little   | 小核    | RISC-V C906     | uart1          | 无 MMU，运行 RT-Thread 标准版 |
| cv18xx_aarch64| 大核    | ARM Cortex A53  | uart0          | 支持 MMU， 支持 RT-Thread 标准版 和 RT-SMART 版，默认运行 RT-Thread 标准版本 |

由于开发板默认运行的大核为 "cv18xx_risc-v", 所以本文将主要介绍 "cv18xx_risc-v" 和 "c906-little" 的构建和使用。有关 "cv18xx_aarch64" 的介绍请参考 [这里](./cv18xx_aarch64/README.md)。



## 3.1. 驱动支持列表

| 驱动  | 支持情况 | 备注              |
| :---- | :------- | :---------------- |
| uart  | 支持     | 默认波特率115200 |
| gpio  | 支持     |  |
| i2c   | 支持     |  |
| adc   | 支持     |  |
| spi   | 支持     | 默认CS引脚，每个数据之间CS会拉高，请根据时序选择GPIO作为CS。若读取数据，tx需持续dummy数据。|
| pwm   | 支持     |  |
| timer | 支持     |  |
| wdt   | 支持     |  |
| sdio  | 支持     |  |
| eth   | 支持     |  |

## 3.2. 默认串口控制台管脚配置
不同开发板 uart 输出管脚不同，默认配置可能导致串口无法正常显示，请根据开发板 uart 通过 `scons --menuconfig` 配置对应 uart 的输出管脚。
```shell
$ scons --menuconfig
  General Drivers Configuration  --->
      [*] Using UART  --->
          [*] Enable UART 1
          (IIC0_SDA) uart1 rx pin name
          (IIC0_SCL) uart1 tx pin name
```

| 开发板 | 大核 uart0 默认管脚 | 小核 uart1 默认管脚 |
| ------ | ---- | ---- |
| Duo   |  rx: UART0_RX<br>tx: UART0_TX | rx: IIC0_SDA<br>tx: IIC0_SCL |
| Duo 256M | rx: UART0_RX<br>tx: UART0_TX | rx: IIC0_SDA<br>tx: IIC0_SCL |
| Duo S  | rx: UART0_RX<br>tx: UART0_TX | rx: JTAG_CPU_TCK<br>tx: JTAG_CPU_TMS |

如需配置其他管脚可参考 [https://milkv.io/zh/docs/duo/getting-started](https://milkv.io/zh/docs/duo/getting-started) 对应型号的开发板。


# 4. 编译

## 4.1. Toolchain 下载

> 注：当前 bsp 只支持 Linux 编译，推荐 ubuntu 22.04

1. 用于编译 RT-Thread 标准版的工具链是 `riscv64-unknown-elf-gcc` 下载地址  [https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz](https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz)

2. 用于编译 RT-Thread Smart 版的工具链是 `riscv64-unknown-linux-musl-gcc` 下载地址 [https://github.com/RT-Thread/toolchains-ci/releases/download/v1.7/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2](https://github.com/RT-Thread/toolchains-ci/releases/download/v1.7/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2)


正确解压后，导出如下环境变量，建议将这些 export 命令写入 `~/.bashrc`。**并注意在使用不同工具链时确保导出正确的一组环境变量**。

构建 RT-Thread 标准版时按照以下配置：

```shell
export RTT_CC="gcc"
export RTT_CC_PREFIX=riscv64-unknown-elf-
export RTT_EXEC_PATH=/opt/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1/bin
```

构建 RT-Thread Smart 版时按照以下配置：

```shell
export RTT_CC="gcc"
export RTT_CC_PREFIX=riscv64-unknown-linux-musl-
export RTT_EXEC_PATH=/opt/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin
```

## 4.2. 依赖安装
```shell
$ sudo apt install -y scons libncurses5-dev device-tree-compiler
```

## 4.3. 构建

异构芯片需单独编译每个核的 OS，在大/小核对应的目录下，依次执行:

### 4.3.1. 开发板选择

   Linux平台下，可以先执行：

```shell
$ scons --menuconfig
```

选择当前需要编译的目标开发板类型，默认是 "milkv-duo256m"。

```shell
Board Type (milkv-duo)  --->
    ( ) milkv-duo
    ( ) milkv-duo-spinor
    (X) milkv-duo256m
    ( ) milkv-duo256m-spinor
    ( ) milkv-duos
```

### 4.3.2. 开启 RT-Smart

目前大核默认启用 RT-Smart，小核不支持 RT-Smart。

如果要对大核启用 RT-Smart，可以按如下方式设置。

```shell
RT-Thread Kernel  --->
    [*] Enable RT-Thread Smart (microkernel on kernel/userland)
```

**注意检查内核虚拟起始地址的配置，确保为 `0xFFFFFFC000200000`。**

```shell
    RT-Thread Kernel  --->
(0xFFFFFFC000200000) The virtural address of kernel start
    RT-Thread Components  --->
```

### 4.3.3. 编译

```shell
$ scons
```

编译成功后，会在 `bsp/cvitek/output` 对应开发板型号目录下自动生成 `fip.bin` 和 `boot.sd` 文件。

- `fip.bin`：这是一个打包后生成的 bin 文件，包含了 `fsbl`、`opensbi`、`uboot` 以及小核的内核镜像文件 `rtthread.bin`。
- `boot.sd`：这也是一个打包后生成的 bin 文件，包含了大核的内核镜像文件 `rtthread.bin`。

# 5. 运行

1. 将 SD 卡分为 2 个分区，第 1 个分区的分区格式为 `FAT32`，用于存放 `fip.bin` 和 `boot.sd` 文件，第 2 个分区可选，如果有可用于作为数据存储分区或者存放文件系统。

2. 将根目录下的 `fip.bin` 和 `boot.sd` 复制到 SD 卡第一个分区中。两个固件文件可以独立修改更新，譬如后续只需要更新大核，只需要重新编译 "cv18xx_risc-v" 并替换 SD 卡第一个分区中的 `boot.sd` 文件即可。

3. 更新完固件文件后， 重新上电可以看到串口的输出信息。

# 6. 大核 RT-Smart 启动并自动挂载根文件系统

大核启用 RT-Smart 后可以在启动阶段挂载根文件系统。目前 Duo 支持 ext4，fat 文件格式，下面以 fat 格式为例，具体操作说明如下：

## 6.1. 内核构建配置

首先确保开启 RT-Smart，参考 [4.3.2. 可按照以下方式开启 RT-Smart](#432-可按照以下方式开启-rt-smart)。

在开启 RT-Smart 基础上确保如下配置修改。

- 使能 `BSP_USING_SDH`: Enable Secure Digital Host Controller, 因为使用 sd-card 存放文件系统。
- 使能 `BSP_USING_RTC`: Enable RTC, 避免挂载文件系统后执行命令报错：`[W/time] Cannot find a RTC device!`
- 使能 `BSP_ROOTFS_TYPE_DISKFS`: Disk FileSystems, e.g. ext4, fat ..., 该配置默认已打开。

保存后重新编译内核。

## 6.2. 构建文件系统

这里用 RT-Thread 官方的 userapps 工具制作文件系统。

userapps 仓库地址: <https://github.com/RT-Thread/userapps>。具体操作参考 [《介绍与快速入门》](https://github.com/RT-Thread/userapps/blob/main/README.md)。

制作根文件系统步骤如下，供参考：

```shell
cd $WS
git clone https://github.com/RT-Thread/userapps.git
cd $WS/userapps
source ./env.sh
cd apps
xmake f -a riscv64gc
xmake -j$(nproc)
xmake smart-rootfs
xmake smart-image -f fat
```

在 `$WS/userapps/apps/build` 路径下生成根文件系统镜像文件 `fat.img`。

## 6.3. 将文件系统写入 sd-card

将 SD 卡分为 2 个分区，第 1 个分区用于存放 `fip.bin` 和 `boot.sd` 文件，第 2 个分区用于存放文件系统，分区格式为 `FAT32`。

将 SD 卡插入 PC 主机系统，假设为 Ubuntu，识别为 `/dev/sdb`，则第二个分区为 `/dev/sdb2`。将第二个分区挂载，假设挂载到 `~/ws/u-disk`。

将上一步生成的 `fat.img` 文件也挂载到一个临时目录，假设是 `/tmp`。

最后将 /tmp 下的文件全部拷贝到 `~/ws/u-disk` 中，即完成对 SD 卡中文件系统分区的烧写。

最后不要忘记卸载 SD 卡的分区。

简单步骤示例如下，供参考：

```shell
sudo mount -o loop fat.img /tmp
sudo mount /dev/sdb2 ~/ws/u-disk
sudo cp -a /tmp/* ~/ws/u-disk
sudo umount ~/ws/u-disk
sudo umount /tmp
```

## 6.4. 上电启动

启动完成后, 会看到 `[I/app.filesystem] device 'sd1' is mounted to '/' as FAT` 的输出，说明文件系统挂载成功。此时 `msh` 被替换为 `/bin/ash`。

```shell
 \ | /
- RT -     Thread Smart Operating System
 / | \     5.2.0 build Nov 26 2024 09:55:38
 2006 - 2024 Copyright by RT-Thread team
lwIP-2.1.2 initialized!
[I/sal.skt] Socket Abstraction Layer initialize success.
[I/drivers.serial] Using /dev/ttyS0 as default console
[I/SDIO] SD card capacity 30216192 KB.
[I/SDIO] sd: switch to High Speed / SDR25 mode 

found part[0], begin: 1048576, size: 128.0MB
found part[1], begin: 135266304, size: 28.707GB
[I/app.filesystem] device 'sd1' is mounted to '/' as FAT
Hello RT-Smart!
msh />[E/sal.skt] not find network interface device by protocol family(1).
[E/sal.skt] SAL socket protocol family input failed, return error -3.
/ # ls
bin       etc       mnt       root      sbin      tc        usr
dev       lib       proc      run       services  tmp       var
```

# 7. FAQ

1. 如遇到不能正常编译，请先使用 `scons --menuconfig` 重新生成配置。

2. 错误：./mkimage: error while loading shared libraries: libssl.so.1.1: cannot open shared object file: No such file or directory

可在 [http://security.ubuntu.com/ubuntu/pool/main/o/openssl](http://security.ubuntu.com/ubuntu/pool/main/o/openssl) 下载 `libssl1.1_1.1.1f-1ubuntu2_amd64.deb` 文件后安装即可解决。
或使用以下命令下载安装:
```shell
$ wget http://security.ubuntu.com/ubuntu/pool/main/o/openssl/libssl1.1_1.1.1f-1ubuntu2_amd64.deb
$ sudo dpkg -i libssl1.1_1.1.1f-1ubuntu2_amd64.deb
```

3. 如发现切换开发板编译正常，但无法正常打包，请切换至自动下载的 `cvi_bootloader` 目录，并手工运行 `git pull` 更新，或删除该目录后重新自动下载。

# 8. 联系人信息

维护人：[flyingcys](https://github.com/flyingcys)

更多信息请参考 [https://riscv-rtthread-programming-manual.readthedocs.io](https://riscv-rtthread-programming-manual.readthedocs.io)
