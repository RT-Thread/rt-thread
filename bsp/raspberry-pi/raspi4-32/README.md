# Raspberry PI 4板级支持包说明

## 1. 简介

树莓派4B的核心处理器为博通BCM2711（四核1.5GHz，Cortex A72架构，树莓派3是四核A53）。LPDDR4内存，由5V/3A USB-C供电或GPIO 5V。

外设支持上，引入了双频Wi-Fi，蓝牙5.0，千兆网卡，MIPI CSI相机接口，两个USB口，40个扩展帧。

这份RT-Thread BSP是针对 Raspberry Pi 4的一份移植，树莓派价格便宜, 使用者甚众，是研究和运行RT-Thread的可选平台之一。


## 2. 编译说明

推荐使用[env工具](https://www.rt-thread.org/page/download.html)，可以在console下进入到`bsp\raspberry-pi\raspi4-32`目录中，运行以下命令：

```
scons
```

来编译这个板级支持包。如果编译正确无误，会产生rtthread.elf、kernel7.img文件。


## 3. 执行

### 3.1 下载**Raspberry Pi Imager**，生成可以运行的raspbian SD卡

首先下载镜像

* [Raspberry Pi Imager for Ubuntu](https://downloads.raspberrypi.org/imager/imager_amd64.deb)
* [Raspberry Pi Imager for Windows](https://downloads.raspberrypi.org/imager/imager.exe)
* [Raspberry Pi Imager for macOS](https://downloads.raspberrypi.org/imager/imager.dmg)

### 3.2 准备好串口线

目前版本是使用raspi4的 GPIO 14, GPIO 15来作路口输出，连线情况如下图所示：

![raspi2](../raspi3-32/figures/raspberrypi-console.png)

串口参数： 115200 8N1 ，硬件和软件流控为关。

### 3.3 程序下载

当编译生成了rtthread.bin文件后，我们可以将该文件放到sd卡上，并修改sd卡中的`config.txt`文件如下：

```
enable_uart=1
arm_64bit=0
kernel_addr=0x8000
kernel=kernel7.img
core_freq=250
```

按上面的方法做好SD卡后，插入树莓派4，通电可以在串口上看到如下所示的输出信息：

```text
heap: 0x00044270 - 0x04044270

 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build May 25 2020
 2006 - 2020 Copyright by rt-thread team
Hi, this is RT-Thread!!
msh />
```

## 4. 支持情况

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0,UART2,UART3,UART4,UART5 |

## 5. 联系人信息

维护人：[bernard][5]

[1]: https://www.rt-thread.org/page/download.html
[2]: https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads
[3]: https://downloads.raspberrypi.org/raspbian_lite_latest
[4]: https://etcher.io
[5]: https://github.com/BernardXiong
