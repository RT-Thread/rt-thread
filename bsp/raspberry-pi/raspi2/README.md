# Raspberry PI 2B板级支持包说明

## 1. 简介

树莓派由注册于英国的慈善组织“Raspberry Pi 基金会”开发，莓派2采用4核Broadcom BCM2836 (ARMv7-A)芯片、双核VideoCore IV GPU和1GB内存。

这份RT-Thread BSP是针对 Raspberry Pi 2B 的一份移植，树莓派价格便宜, 使用者甚众，是研究和运行RT-Thread的可选平台之一。

![raspi2](figures/raspi2.png)

当前Raspberry Pi 2B对应的硬件特性：

| 硬件   | 描述 |
|------- | ------------------------------- |
|  CPU   | ARM Cortex-A7（4核心） |
|  主频  | 900M |
| Memory | 1GB  (0x0000000 - 0x40000000) |
| | 其中0x3f000000 - 0x40000000为peripheral |

## 2. 编译说明

Windows环境下推荐使用[env工具][1]进行编译。

Linux下推荐使用gcc工具 [gcc-arm-none-eabi-4_8-2014q1_linux][2]，如果还没有编译工具，下载后，解开文件。

```
tar vxf gcc-arm-none-eabi-4_8-2014q1_linux.tar.bz2
```

Linux环境下需要修改编译器目录设置，修改`bsp/raspi2/rtconfig.py`中的

```
EXEC_PATH = r'/opt/gcc-arm-none-eabi-4_8-2014q1_gri/bin'
```

为编译工具的实际所在目录，这里注意要加上后缀 `/bin`

进入到`rt-thread/bsp/raspi2`目录中，运行以下命令：

```
scons
```

来编译这个板级支持包。如果编译正确无误，会产生kernel.elf、kernel.img文件。
kernel.img即是要cp到raspberry SD卡中根目录的文件

## 3. 执行

### 3.1 下载[raspbian镜像][3]，生成可以运行的raspbian SD卡

Windows下，去[etcher.io][4]下载etcher,这是个可以烧写img的工具

解开下载的镜像文件, linux下使用如下的命令

```
unzip 2018-06-27-raspbian-stretch-lite.zip
```

准备一张空SD卡，linux环境下，插入电脑并执行

```
sudo dd if=2018-06-27-raspbian-stretch-lite.img of=/dev/xxx bs=32M conv=fsync
```

**注意: /dev/xxx 要换成真实环境中的SD卡所在设置，千万不要弄错。**

Windows环境下，执行etcher选择解压后的2018-06-27-raspbian-stretch-lite.img文件和SD卡就可以开始烧写了。

最后把kernel7.img放入SD boot分区，覆盖原来的文件。

### 3.2 准备好串口线

目前版本是使用raspi2的 GPIO 14, GPIO 15来作路口输出，连线情况如下图所示：

![raspi2](figures/raspi_uart.png)

串口参数： 115200 8N1 ，硬件和软件流控为关。

按上面的方法做好SD卡后，插入树莓派2B，通电可以在串口上看到如下所示的输出信息：

```text
 heap: 0x00020b20 - 0x00400000

 \ | /
- RT -     Thread Operating System
 / | \     3.1.0 build Aug 23 2018
 2006 - 2018 Copyright by rt-thread team
Hello RT-Thread!
msh >
```

## 4. 支持情况

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0|

## 5. 联系人信息

维护人：[bernard][5]

  [1]: https://www.rt-thread.org/page/download.html
  [2]: https://launchpad.net/gcc-arm-embedded/4.8/4.8-2014-q1-update/+download/gcc-arm-none-eabi-4_8-2014q1-20140314-linux.tar.bz2
  [3]: https://downloads.raspberrypi.org/raspbian_lite_latest
  [4]: https://etcher.io
  [5]: https://github.com/BernardXiong
