CanMV-K230 Board Support Package 使用说明

<!-- TOC -->

- [1. 参考文档](#1-参考文档)
- [2. 概述](#2-概述)
- [3. 构建](#3-构建)
	- [3.1. 安装 GCC 工具链](#31-安装-gcc-工具链)
	- [3.2. 安装依赖](#32-安装依赖)
		- [3.2.1. apt 软件包](#321-apt-软件包)
		- [3.2.2. kconfiglib](#322-kconfiglib)
		- [3.2.3. Env](#323-env)
	- [3.3. 下载 RT-Thread 并更新依赖的软件包](#33-下载-rt-thread-并更新依赖的软件包)
	- [3.4. 构建](#34-构建)
- [4. 烧写](#4-烧写)
	- [4.1. 制作启动 SD 卡](#41-制作启动-sd-卡)
		- [4.1.1. 编译固件](#411-编译固件)
		- [4.1.2. 烧录固件](#412-烧录固件)
	- [4.2. 单独更新 RT-Thread 内核](#42-单独更新-rt-thread-内核)
- [5. 上电启动](#5-上电启动)

<!-- /TOC -->

# 1. 参考文档

- 【参考 1】Canaan CanMV K230 文档: <https://www.canaan-creative.com/k230_canmv/zh/main/index.html>
- 【参考 2】K230 RTOS Only SDK 文档: <https://developer.canaan-creative.com/k230_rtos/zh/dev/index.html>
- 【参考 3】01Studio CanMV-K230 教程: <https://wiki.01studio.cc/docs/canmv_k230/intro/canmv_k230/>

# 2. 概述

CanMV 是一个由嘉楠科技（Canaan）官方创建和维护的开源项目。该项目将 MicroPython 移植到嘉楠科技边缘计算AI 芯片 K230 上，这就是 CanMV-K230 开发板。该项目旨在创建低成本，可扩展的，使用 Python 驱动的 AI 人工智能模块。

目前市面上生产的以 CanMV-K230 为原型的开发板有多种型号。本 BSP 支持 01Studio CanMV-K230 AI 开发板（内存 512MB）。

K230 是一款嘉楠科技（Canaan）出品的 64 位双核带硬件 FPU 和卷积加速器的 RISC-V SoC。

采用本 BSP 构建生成的 RT-Smart 和官方 SDK (【参考 2】) 配套使用并在大核上运行。

# 3. 构建

目前只验证了 Ubuntu/Linux 下构建。

```shell
$ lsb_release -a
No LSB modules are available.
Distributor ID:	Ubuntu
Description:	Ubuntu 22.04.5 LTS
Release:	22.04
Codename:	jammy
```

## 3.1. 安装 GCC 工具链

下载地址：<https://download.rt-thread.org/rt-smart/riscv64/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_251248.tar.bz2>

正确解压后(假设下载后解压在 `$USER/toolchain`, 也可以自己设定解压后的目录)，导出如下环境变量，建议将这些 export 命令写入 `~/.bashrc`。

```shell
export RTT_CC="gcc"
export RTT_CC_PREFIX="riscv64-unknown-linux-musl-"
export RTT_EXEC_PATH="$USER/toolchain/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin"
```

## 3.2. 安装依赖

### 3.2.1. apt 软件包

```shell
$ sudo apt install -y scons python3-pip
```

### 3.2.2. kconfiglib

因为本 BSP 只在 RT-Thread v5.1.0 以上才支持，所以需要确保本地已经安装过 kconfiglib。

```shell
$ pip3 install kconfiglib i https://pypi.tuna.tsinghua.edu.cn/simple
```
采用清华源是为了加快安装速度。

### 3.2.3. Env

安装 env，具体参考 <https://github.com/RT-Thread/env>

## 3.3. 下载 RT-Thread 并更新依赖的软件包

假设我们的工作路径是 `$WS`
```shell
$ cd $WS
$ git clone git@github.com:RT-Thread/rt-thread.git
$ cd rt-thread/bsp/k230
$ source ~/.env/env.sh
$ pkgs --update
```

## 3.4. 构建

在 `$WS/rt-thread/bsp/k230` 下执行如下命令：

```shell
$ scons --menuconfig # 默认不需要修改，直接保存即可，保存后可以达到同步最新配置的效果
$ scons -j$(nproc)
```

此时在 `$WS/rt-thread/bsp/k230` 下会看到生成了 `rtthread.bin`, 这个就是我们构建出来的内核二进制文件。


# 4. 烧写

`rtthread.bin` 并不能直接运行。目前我们基于 Canaan 官方的 RTOS-only SDK 制作 SD 卡，并基于 SD 卡启动内核。

## 4.1. 制作启动 SD 卡

### 4.1.1. 编译固件

参考 K230 RTOS Only 用户指南中的 “如何编译固件”：<https://developer.canaan-creative.com/k230_rtos/zh/dev/userguide/how_to_build.html>。

假设 sdk 安装的路径在 `$WS/rtos_k230`
注意事项如下：

- 目前用户指南的环境只在 Ubuntu 20.04 LTS (x86_64) 上验证过，*其他 Linux 发行版未经充分测试，可能存在兼容性问题*。为避免和 BSP 构建环境冲突，建议在另外一台机器或者虚拟机中搭建此环境。

- `rtos_k230` 克隆自 `git@gitee.com:canmv-k230/manifest.git`(国内用户建议从 gitee 下载，否则速度太慢)，本文基于的 commit 是 75662ae。

- 根据指南步骤操作，在 “4.4 选择目标硬件配置” 中选择 01studio 的 defconfig。

  和 01studio 相关的配置有两项：

  ```shell
  $ make list-def
  1 [ ] k230_canmv_01studio_defconfig 
  ......
  10 [*] k230_rtos_01studio_defconfig
  ```

  其中：
  - 1：01Studio 的带 micropython 的 canMV。
  - 10： 01Studio 的不带 micropython 的 canMV。

  为简单起见，这里选择 “ k230_rtos_01studio_defconfig” 。

最后在 `$WS/rtos_k230/output/k230_rtos_01studio_defconfig/` 下生成 `RtSmart-K230_01Studio_rtsmart_local_nncase_v2.9.0.img`

### 4.1.2. 烧录固件

参考 K230 RTOS Only 用户指南中的 “如何烧录固件”：<https://developer.canaan-creative.com/k230_rtos/zh/dev/userguide/how_to_flash.html>, 通过 SD 卡烧录。熟悉 Windows 平台的可以使用 balenaEtcher。

## 4.2. 单独更新 RT-Thread 内核

在开发 BSP 过程中每次更新内核都烧写整个 SD 卡是一件非常麻烦的事情。以下操作只更新内核所在分区。

首先前面构建生成的 `rtthread.bin` 并不能直接用，而是需要和 opensbi 的 image 打包后才能被 u-boot 加载。我们这里利用 K230 RTOS Only SDK 来打包。具体步骤如下：

先将前面生成的 `rtthread.bin` 拷贝到 `$WS/rtos_k230/output/k230_rtos_01studio_defconfig/images/rtsmart` 下。

修改 `rtos_k230/Makefile`：

```diff
diff --git a/Makefile b/Makefile
index 45a3f0c..39a017b 100644
--- a/Makefile
+++ b/Makefile
@@ -93,13 +93,20 @@ rtsmart-menuconfig:
        @$(MAKE) -C $(SDK_RTSMART_SRC_DIR) menuconfig
 
 .PHONY: opensbi opensbi-clean opensbi-distclean
-opensbi: .autoconf rtsmart
+opensbi: .autoconf
        @$(MAKE) -C $(SDK_OPENSBI_SRC_DIR) all
 opensbi-clean:
        @$(MAKE) -C $(SDK_OPENSBI_SRC_DIR) clean
 opensbi-distclean:
        @$(MAKE) -C $(SDK_OPENSBI_SRC_DIR) distclean
```
然后执行：

```shell
$ make opensbi
```

会在 `$WS/rtos_k230/output/k230_rtos_01studio_defconfig/images/opensbi` 下生成一个新的 `opensbi_rtt_system.bin`，这也是我们要烧写的最终文件。

将 SD卡通过 USB 读卡器接入 Ubuntu 机器。假设枚举为 `/dev/sdb`。执行如下命令烧写：

```shell
$ sudo dd if=$WS/rtos_k230/output/k230_rtos_01studio_defconfig/images/opensbi/opensbi_rtt_system.bin of=/dev/sdb seek=20480
```

# 5. 上电启动

将 SD 卡插入 01Studo 开发板的 SD 卡槽。

连接 USB 转 UART 串口线到 “CPU0 调试口”，具体见下图：

![](https://wiki.01studio.cc/assets/images/pinout-4d00bfa5ce28bf9723c94c00c7087fee.png)

上电后串口控制台如下所示：

```shell
U-Boot SPL 2022.10-00015-gcf105752 (Apr 09 2025 - 22:49:49 +0800)
lpddr4 2660
00000000: PMU Major Msg: End of CA training                                            
00000000: PMU Major Msg: End of initialization                                         
00000000: PMU Major Msg: End of read enable training                                   
00000000: PMU Major Msg: End of fine write leveling                                    
00000000: PMU Major Msg: End of read dq deskew training                                
00000000: PMU Major Msg: End of MPR read delay center optimization                     
00000000: PMU Major Msg: End of Write leveling coarse delay                            
00000000: PMU Major Msg: End of write delay center optimization                        
00000000: PMU Major Msg: End of read delay center optimization                         
00000000: PMU Major Msg: End of max read latency training                              
00000000: PMU Major Msg: Firmware run has completed                                    
image: uboot load to 0x1000000, compress=1 src=0x2aaaacff len=0x49e27


U-Boot 2022.10-00015-gcf105752 (Apr 09 2025 - 22:49:49 +0800)

CPU:   rv64imafdcvsu
Model: kendryte k230 canmv 01studio
DRAM:  1 GiB
Core:  22 devices, 13 uclasses, devicetree: embed
MMC:   mmc0@91580000: 0
Loading Environment from MMC... OK
In:    serial@91400000
Out:   serial@91400000
Err:   serial@91400000
Net:   No ethernet found.
Hit any key to stop autoboot:  0 
image: rtt load to 0x0, compress=1 src=0x2aaaad07 len=0x5fb7b
Jump to big hart

OpenSBI v1.1-2-g1de130d

 \ | /
- RT -     Thread Smart Operating System
 / | \     5.2.1 build Apr 23 2025 16:04:02
 2006 - 2024 Copyright by RT-Thread team
lwIP-2.1.2 initialized!
[I/sal.skt] Socket Abstraction Layer initialize success.
[I/drivers.serial] Using /dev/ttyS0 as default console
CromFS mount failed!
Press any key to stop init process startup ... 3
Press any key to stop init process startup ... 2
Press any key to stop init process startup ... 1
Starting init ...
Hello RISC-V
msh />
```