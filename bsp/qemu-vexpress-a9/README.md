# QEMU/VExpress A9板级支持包说明

## 1. 简介

Versatile Express系统由ARM Ltd提供，作为CortexA9四核处理器的开发环境，硬件由uATX主板和CoreTile Express A9x4子板组成。有关该系统的详细信息，可以访问 [ARM官方页面][1] 。

Versatile Express的核心是一套FPGA的开发环境，Cortex-A芯片基于FPGA上的硬件逻辑，所以本身是不存在这么一款真实芯片。

QEMU/VExpress A9是QEMU模拟器针对ARM VExpress-A9 FPGA开发板进行软件模拟的指令级虚拟机。QEMU/VExpress因为是软件仿真模式，可以配置成多种模式，例如单核Cortex-A9，多核Cortex-A9，以及多核Cortex-A15等。同时也能够模拟出VExpress FPGA开发板上大多数的外设。

这份RT-Thread BSP是针对QEMU/VExpress-A9的一份移植，也并未在真实的VExpress FPGA开发板上运行过，主要是提供给开发者一定的便利，能够使用、验证一定的功能。对于真实FPGA开发板的执行情况，不做任何假设。

当前QEMU/VExpress-A9对应的硬件特性：

| 硬件 | 描述 |
| -- | -- |
| CPU | ARM Cortex-A9（单核） |
| 主频 | NA |
| Memory | 128MB(0x60000000 - 0x68000000) |

## 2. 编译说明

推荐使用[env工具][2]，可以在console下进入到`bsp/qemu-vexpress-a9`目录中，运行以下命令：

    scons

来编译这个板级支持包。如果编译正确无误，会产生rtthread.elf、rtthread.bin文件。在QEMU中一般使用elf方式来运行，所以只需要使用rtthread.elf文件即可。

**注：** RT-Thread/ENV中携带的工具版本是：

    gcc version 5.4.1 20160919 (release) [ARM/embedded-5-branch revision 240496]

如果在Linux下使用，请自行下载[GNU GCC工具链][3]。

## 3. 执行

当要执行编译好的RT-Thread时，在这个bsp目录下已经提供了运行脚本文件：qemu.bat/qemu.sh

这个执行脚本默认把串口输出到stdio（即控制台）上，所以直接执行脚本后就可以输出结果了。

```text
 \ | /
- RT -     Thread Operating System
 / | \     3.0.4 build May  4 2018
 2006 - 2018 Copyright by rt-thread team
SD card capacity 65536 KB
probe mmcsd block device!
hello rt-thread
msh />
```

## 4. 支持情况

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0/1 |
| SD/MMC | 支持 |  |
| CLCD | 支持 |  |
| Key | 支持 |  |
| Mouse | 支持 |  |
| EMAC | 支持 |  |

## 5. 联系人信息

维护人：bernard

  [1]: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.subset.boards.express/index.html
  [2]: https://www.rt-thread.org/page/download.html
  [3]: https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q3-update/+download/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2
