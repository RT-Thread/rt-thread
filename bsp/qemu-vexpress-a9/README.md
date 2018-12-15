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

### 4.1 使用VSCode编辑、编译、调试

在qemu-vexpress-a9中已经携带了部分vscode的配置，需要配合着env一起来使用。步骤包括：

先使用env打开console，然后在console中切换都qemu-vexpress-a9 bsp的目录下，

```bash
scons --target=vsc -s
```

更新vscode需要用到的C/C++头文件搜索路径信息（不是每次都需要更新，只有在使用了menuconfig重新配置了RT-Thread或更改了rtconfig.h头文件时才需要）

然后在console下输入

```bash
code .
```

启动vscode。使用vscode，目前包含如下的一些功能：

* 编译 `Ctrl+Shift+B` - 开启vscode内置终端，调用scons进行编译；如果有编译错误也会侦测问题，双击问题跳到指定代码文件、代码行；
* 包含执行`qemu`模拟器，`scons -c`进行目标文件清理的任务
* `F5` 一键开启QEMU调试模式，并断点停留在`main`函数上；(需要更改下qemu-dbg.bat文件，在qemu-system-arm前加入`start`)，即

```batch
@echo off
if exist sd.bin goto run
qemu-img create -f raw sd.bin 64M

:run
start qemu-system-arm -M vexpress-a9 -kernel rtthread.elf -serial stdio -sd sd.bin -S -s
```

**已知问题** 如果在vscode的目录中额外添加了文件夹，会导致调试不能够启动。

## 5. 联系人信息

维护人：[bernard][4]

  [1]: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.subset.boards.express/index.html
  [2]: https://www.rt-thread.org/page/download.html
  [3]: https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q3-update/+download/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2
  [4]: https://github.com/BernardXiong
