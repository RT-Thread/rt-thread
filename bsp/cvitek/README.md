<!-- TOC -->

- [参考文档](#参考文档)
- [概述](#概述)
- [BSP 支持情况](#bsp-支持情况)
	- [驱动支持列表](#驱动支持列表)
- [编译](#编译)
	- [Toolchain 下载](#toolchain-下载)
	- [依赖安装](#依赖安装)
	- [构建](#构建)
- [运行](#运行)
- [FAQ](#faq)
- [联系人信息](#联系人信息)

<!-- /TOC -->

# 参考文档

- 【参考 1】CV1800B/CV1801B Datasheet（中文版）：<https://github.com/milkv-duo/duo-files/blob/main/duo/datasheet/CV1800B-CV1801B-Preliminary-Datasheet-full-zh.pdf>
- 【参考 2】SG2002/SG2000 技术参考手册（中文版）：<https://github.com/sophgo/sophgo-doc/releases>。官方定期发布 pdf 形式。可以下载下载最新版本的中文版本技术参考手册：`sg2002_trm_cn.pdf` 或者 `sg2000_trm_cn.pdf`。

# 概述

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

# BSP 支持情况

由于大小核的存在，以及不同 SoC 下不同工作模式的存在，bsp/cvitek 提供了三种不同 BSP/OS，需要单独编译。

| BSP 名称      | 大小核  | 芯片架构        | 默认串口控制台 | 备注     |
| ------------- | ------- |---------------- | -------------- | -------- |
| cv18xx_risc-v | 大核    | RISC-V C906     | uart0          | 支持 MMU，支持 RT-Thread 标准版 和 RT-SMART 模式，默认运行 RT-Thread 标准版本 |
| c906-little   | 小核    | RISC-V C906     | uart1          | 无 MMU，运行 RT-Thread 标准版 |
| cv18xx_aarch64| 大核    | ARM Cortex A53  | uart0          | 支持 MMU， 支持 RT-Thread 标准版 和 RT-SMART 版，默认运行 RT-Thread 标准版本 |

由于开发板默认运行的大核为 "cv18xx_risc-v", 所以本文将主要介绍 "cv18xx_risc-v" 和 "c906-little" 的构建和使用。有关 "cv18xx_aarch64" 的介绍请参考 [这里](./cv18xx_aarch64/README.md)。

## 驱动支持列表

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

# 编译

## Toolchain 下载

> 注：当前 bsp 只支持 Linux 编译，推荐 ubuntu 22.04

1. RT-Thread 标准版工具链：`riscv64-unknown-elf-gcc` 下载地址  [https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz](https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1705395512373/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1-20240115.tar.gz)

2. RT-Smart 版工具链： `riscv64-unknown-linux-musl-gcc` 下载地址 [https://github.com/RT-Thread/toolchains-ci/releases/download/v1.7/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2](https://github.com/RT-Thread/toolchains-ci/releases/download/v1.7/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_latest.tar.bz2)


正确解压后，在`rtconfig.py`中将 `riscv64-unknown-elf-gcc` 或 `riscv64-unknown-linux-musl-gcc` 工具链的本地路径加入 `EXEC_PATH` 或通过 `RTT_EXEC_PATH` 环境变量指定路径。

```shell
# RT-Thread 标准版按照以下配置：
$ export RTT_CC_PREFIX=riscv64-unknown-elf-
$ export RTT_EXEC_PATH=/opt/Xuantie-900-gcc-elf-newlib-x86_64-V2.8.1/bin

# RT-Samrt 版按照以下配置：
$ export RTT_CC_PREFIX=riscv64-unknown-linux-musl-
$ export RTT_EXEC_PATH=/opt/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin
```

## 依赖安装
```shell
$ sudo apt install -y scons libncurses5-dev device-tree-compiler
```

## 构建

异构芯片需单独编译每个核的 OS，在大/小核对应的目录下，依次执行:

1. 开发板选择
Linux平台下，可以先执行：
```shell
$ scons --menuconfig
```

选择当前需要编译的目标开发板类型
```shell
Board Type (milkv-duo)  --->
    ( ) milkv-duo
    ( ) milkv-duo-spinor
    (X) milkv-duo256m
    ( ) milkv-duo256m-spinor
    ( ) milkv-duos
```

2. 编译
```shell
$ scons
```

编译成功后，会在 `bsp/cvitek/output` 对应开发板型号目录下自动生成 `fip.bin` 和 `boot.sd` 文件，其中大核运行文件在 `boot.sd` 中，小核的运行文件在 `fip.bin` 中。

- fip.bin：fsbl、opensbi、uboot、小核运行文件打包后的 bin 文件
- boot.sd：大核打包后的 bin 文件

# 运行

1. 将 SD 卡分为 2 个分区，第 1 个分区用于存放 bin 文件，第 2 个分区用于作为数据存储分区，分区格式为 `FAT32`。

2. 将根目录下的 `fip.bin` 和 `boot.sd` 复制到 SD 卡第一个分区中。两个固件文件可以独立修改更新，譬如后续只需要更新大核，只需要重新编译 "cv18xx_risc-v" 并复制 `boot.sd` 文件即可。

3. 更新完固件文件后， 重新上电可以看到串口的输出信息。

# FAQ

1. 如遇到不能正常编译，请先使用 `scons --menuconfig` 重新生成配置。

2. 错误：./mkimage: error while loading shared libraries: libssl.so.1.1: cannot open shared object file: No such file or directory

可在 [http://security.ubuntu.com/ubuntu/pool/main/o/openssl](http://security.ubuntu.com/ubuntu/pool/main/o/openssl) 下载 `libssl1.1_1.1.1f-1ubuntu2_amd64.deb` 文件后安装即可解决。
或使用以下命令下载安装:
```shell
$ wget http://security.ubuntu.com/ubuntu/pool/main/o/openssl/libssl1.1_1.1.1f-1ubuntu2_amd64.deb
$ sudo dpkg -i libssl1.1_1.1.1f-1ubuntu2_amd64.deb
```

3. 如发现切换开发板编译正常，但无法正常打包，请切换至自动下载的 `cvi_bootloader` 目录，并手工运行 `git pull` 更新，或删除该目录后重新自动下载。

# 联系人信息

维护人：[flyingcys](https://github.com/flyingcys)

更多信息请参考 [https://riscv-rtthread-programming-manual.readthedocs.io](https://riscv-rtthread-programming-manual.readthedocs.io)
