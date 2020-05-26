# Raspberry PI 4板级支持包说明

## 1. 简介

树莓派4B的核心处理器为博通BCM2711（四核1.5GHz，Cortex A72架构，树莓派3是四核A53）。LPDDR4内存，由5V/3A USB-C供电或GPIO 5V。

外设支持上，引入了双频Wi-Fi，蓝牙5.0，千兆网卡，MIPI CSI相机接口，两个USB口，40个扩展帧。

这份RT-Thread BSP是针对 Raspberry Pi 4的一份移植，树莓派价格便宜, 使用者甚众，是研究和运行RT-Thread的可选平台之一。


## 2. 编译说明



### 2.1 Window上的环境搭建

Windows环境下推荐使用[env工具](https://www.rt-thread.org/page/download.html)进行编译。

首先下载windows上的aarch64的gcc交叉编译工具，版本为gcc-arm-8.3选择aarch64-elf就可以。

将推荐将gcc解压到`\env\tools\gnu_gcc\arm_gcc`目录下。

接着修改`bsp\raspberry-pi\raspi4-64\rtconfig.py`

修改路径：

```
EXEC_PATH = r'E:/env_released_1.1.2/env/tools/gnu_gcc/arm_gcc/gcc-arm-8.3-2019.03-i686-mingw32-aarch64-elf/bin'
```

然后在`bsp\raspberry-pi\raspi4-64\`下输入scons编译即可。

**window环境搭建注意**

下载完成`gcc-arm-8.3-2019.03-i686-mingw32-aarch64-elf.tar.xz`交叉编译工具链后，最好采用7-zip解压工具进行两次解压。
确保解压目录下的`/bin/aarch64-elf-ld.exe`文件的size不为0。
否则编译会出现如下错误:

```
collect2.exe:fatal error:CreateProcess:No such file or directory
```

### 2.2 Linux上的环境搭建

Linux下推荐使用[gcc工具][2]。Linux版本下gcc版本可采用`gcc-arm-8.3-2019.03-x86_64-aarch64-elf`。

将工具链解压到指定目录,并修改当前bsp下的`EXEC_PATH`为自定义gcc目录。

```
PLATFORM    = 'gcc'
EXEC_PATH   = r'/opt/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/bin/'  
```

直接进入`bsp\raspberry-pi\raspi4-64`，输入scons编译即可。


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
arm_64bit=1
kernel=rtthread.bin
core_freq=250
```

按上面的方法做好SD卡后，插入树莓派4，通电可以在串口上看到如下所示的输出信息：

```text
heap: 0x000c9350 - 0x040c9350

 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Apr 16 2020
 2006 - 2020 Copyright by rt-thread team
Hi, this is RT-Thread!!
msh />
```

## 4. 支持情况

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0|

## 5. 联系人信息

维护人：[bernard][5]

[1]: https://www.rt-thread.org/page/download.html
[2]: https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads
[3]: https://downloads.raspberrypi.org/raspbian_lite_latest
[4]: https://etcher.io
[5]: https://github.com/BernardXiong
