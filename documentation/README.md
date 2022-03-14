# RT-Thread

RT-Thread (Real-Time Thread) is an open source embedded real-time operating system and released under Apache License v2.0. It has a strong scalability: from a nano kernel running on a tiny MCU, for example ARM Cortex-M0, or Cortex-M3/4/7, to a rich feature system running on MIPS32, ARM Cortex-A, even the emerging open source RISC-V architecture is supported. RT-Thread can run either on single-core systems or on symmetric multi-core processors(SMP) systems.

## Introduction

RT-Thread has not noly a real-time kernel, but also rich components. Its architecture is as follows:

![RT-Thread system framework](figures/02Software_framework_diagram.png)

- **Kernel**: It includes preemptive multi-task real-time scheduler, and infrastructure such as semaphore, mutex, mailbox, message queue, signal, event, memory management, timer management, interrupt management, etc. It also includes libcpu/BSP (file related to chip transplantation/board support package).
- **components**: It is a software unit on the RT-Thread kernel layer, such as command line (FinSH), device driver framework (Device Drivers), network framework, virtual file system (FAT, YAFFS, UFFS, ROM/RAM file system, etc.), TCP/IP network protocol stack (lwIP), libc/POSIX standard layer and so on. Generally, a software component is placed in a folder in the RT-Thread/components directory, and each software component is described by a *SConscript* file and added to the RT-Thread construction system. When a software component is opened in the system configuration, it will be compiled and linked to the final RT-Thread firmware.
- **Packages**: It is a middleware running on RT-Thread IoT operating system platform and facing different application fields. Packages consist of description information, source code or library files. These packages can be provided by RT-Thread, third-party developers and enterprises, and the license agreement of the packages is provided by the author of the packages. These software packages have strong reusability and high modularity, which greatly facilitates application developers to build their desired application systems in the shortest time. For more package information, visit the [RT-Thread package repository](https://github.com/RT-Thread-packages).

## Licence

RT-Thread  is an open source software and has been licensed under Apache License Version 2.0 since v3.1.1. License information and copyright information can generally be seen at the beginning of the code:

```
/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
```

To avoid possible future license conflicts, developers need to sign a Contributor License Agreement (CLA) when submitting PR to RT-Thread.

> Note: Because the BSP also contains the code provided by the chip manufacturer, this part of the code follows the license provided by the chip manufacturer, such as STM32 HAL, NXP, Atmel, etc. Relevant codes are usually only used in the chips of the corresponding manufacturers.

## Supported Architectures

RT-Thread RTOS can support many architectures,and has covered the major architectures in current applications. Architecture and chip manufacturer involved:

- **ARM Cortex-M0/M0+**：manufacturers like ST
- **ARM Cortex-M3**：manufacturers like ST、Winner Micro、MindMotion, ect.
- **ARM Cortex-M4**：manufacturers like ST、Nuvton、NXP、GigaDevice、Realtek、Ambiq Micro, ect.
- **ARM Cortex-M7**：manufacturers like ST、NXP
- **ARM Cortex-M23**：manufacturers like GigaDevice
- **ARM Cortex-R4**
- **ARM Cortex-A8/A9**：manufacturers like NXP
- **ARM7**：manufacturers like Samsung
- **ARM9**：manufacturers like Allwinner、Xilinx 、GOKE
- **ARM11**：manufacturers like Fullhan
- **MIPS32**：manufacturers like loongson、Ingenic
- **RISC-V**：manufacturers like Hifive、Kendryte
- **ARC**：manufacturers like SYNOPSYS
- **DSP**：manufacturers like TI
- **C-Sky**
- **x86**

## Supported IDE and Compiler

The main IDE/compilers supported by RT-Thread are:

- MDK KEIL
- IAR
- GCC

Use Python-based [scons](http://www.scons.org) for command-line builds.

# Source Code and Tools

**Get the source code**: The source code of RT-Thread is hosted on Github, and click on the link to get the source code.

- [Download RT-Thread source code](https://github.com/RT-Thread/rt-thread)

**Get the Env Tool**: To better help developers, the RT-Thread team also provides Env tools (or Env scripts for Linux/MacOS). On Windows, Env tool is a development assistant tool launched by RT-Thread. It provides compiling and building environment, graphical system configuration and software package management functions for project projects based on RT-Thread operating system. Its built-in menuconfig provides a simple and easy-to-use configuration tailoring tool, which can tailor the kernel, components and software packages freely, so that the system can be built in the way of building blocks.

- [Download Env Tool]()
- [User manual of Env](env/env.md)

# Getting Started

RT-Thread BSP can be compiled directly and downloaded to the corresponding development board for use. In addition, RT-Thread also provides qemu-vexpress-a9 BSP, which can be used without hardware platform. See the getting started guide below for details.

- [Getting Started of QEMU (Windows)](quick-start/quick_start_qemu/quick_start_qemu.md)
- [Getting Started of QEMU (Ubuntu)](quick-start/quick_start_qemu/quick_start_qemu_linux.md)

# Help

Any questions can be asked in the [issue section of rtthread-manual-doc](https://github.com/RT-Thread/rtthread-manual-doc/issues). By creating a new issue to describe your questions, community members will answer them.

# Contribution

If you are interested in RT-Thread and want to join in the development of RT-Thread and become a code contributor,please refer to the [Code Contribution Guide](documentation/contribution_guide/contribution_guide.md).

# Manual Catalogue

- [RT-Thread Introduction](introduction/introduction.md)
- [Start Guide: Simulate STM32F103 on KEIL simulator](quick-start/quick-start.md)

**Kernel**

- [Kernel Basics](basic/basic.md)
- [Thread Management](thread/thread.md)
- [Clock&Timer Management](timer/timer.md)
- [Inter-thread Synchronization](thread-sync/thread-sync.md)
- [Inter-thread Communication](thread-comm/thread-comm.md)
- [Memory Management](memory/memory.md)
- [Interrupt Management](interrupt/interrupt.md)
- [Kernel Porting](kernel-porting/kernel-porting.md)

**Tool**

- [User Manual of Env](env/env.md)
- [SCons](scons/scons.md)

**Device**

- [I/O Device Framework](device/device.md)
- [PIN Device](device/pin/pin.md)
- [UART Device](device/uart/uart.md)
- [ADC Device](device/adc/adc.md)
- [I2C Bus Device](device/i2c/i2c.md)
- [SPI Device](device/spi/spi.md)
- [PWM Device](device/pwm/pwm.md)
- [RTC Device](device/rtc/rtc.md)
- [HWTIMER Device](device/hwtimer/hwtimer.md)
- [WATCHDOG Device](device/watchdog/watchdog.md)
- [WLAN Device](device/wlan/wlan.md)
- [Sensor Device](device/sensor/sensor.md)

**Components**

- [FinSH Console](finsh/finsh.md)
- [Virtual File System](filesystem/README.md)
- [utest Framework](utest/utest.md)
- [Dynamic Module: dlmodule](dlmodule/README.md)
- [Socket Abstraction Layer: SAL](sal/sal.md)
- [AT Commands](at/at.md)
- [POSIX Interface](posix/README.md)
- [Ulog Log](ulog/ulog.md)
- [Power Management: PM](pm/pm.md)
- [Network Framework](network/network.md)

