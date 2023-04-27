<p align="center">
<img src="documentation/figures/logo.png" width="60%" >
</p>

**English** | [中文](README_zh.md) | [Español](README_es.md) | [Deutsch](README_de.md)

[![GitHubStars](https://img.shields.io/github/stars/RT-Thread/rt-thread?style=flat-square&logo=GitHub)](https://github.com/RT-Thread/rt-thread/stargazers)
[![GiteeStars](https://gitee.com/rtthread/rt-thread/badge/star.svg?theme=gvp)](https://gitee.com/rtthread/rt-thread/stargazers)
[![GitHub](https://img.shields.io/github/license/RT-Thread/rt-thread.svg)](https://github.com/RT-Thread/rt-thread/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RT-Thread/rt-thread.svg)](https://github.com/RT-Thread/rt-thread/releases)
[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/RT-Thread/rt-thread?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![GitHub pull-requests](https://img.shields.io/github/issues-pr/RT-Thread/rt-thread.svg)](https://github.com/RT-Thread/rt-thread/pulls)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat)](https://github.com/RT-Thread/rt-thread/pulls)

# RT-Thread

RT-Thread was born in 2006, it is an open source, neutral, and community-based real-time operating system (RTOS).

RT-Thread is mainly written in C language, easy to understand and easy to port(can be quickly port to a wide range of mainstream MCUs and module chips). It applies object-oriented programming methods to real-time system design, making the code elegant, structured, modular, and very tailorable.

RT-Thread has Standard version and Nano version. For resource-constrained microcontroller (MCU) systems, the Nano version that requires only 3KB Flash and 1.2KB RAM memory resources can be tailored with easy-to-use tools. For resource-rich IoT devices, RT-Thread can use the on-line software package management tool, together with system configuration tools, to achieve intuitive and rapid modular cutting, seamlessly import rich software packages; thus, achieving complex functions like Android's graphical interface and touch sliding effects, smart voice interaction effects, and so on.

## RT-Thread Architecture

RT-Thread has not only a real-time kernel, but also rich components. Its architecture is as follows:


![architecture](./documentation/figures/architecture.png)


It includes:

- Kernel layer: RT-Thread kernel, the core part of RT-Thread, includes the implementation of objects in the kernel system, such as multi-threading and its scheduling, semaphore, mailbox, message queue, memory management, timer, etc.; libcpu/BSP (Chip Migration Related Files/Board Support Package) is closely related to hardware and consists of peripheral drivers and CPU porting.

- Components and Service Layer: Components are based on upper-level software on top of the RT-Thread kernel, such as virtual file systems, FinSH command-line interfaces, network frameworks, device frameworks, and more. Its modular design allows for high internal cohesion inside the components and low coupling between components.

- [RT-Thread software package](https://packages.rt-thread.org/en/index.html): A general-purpose software component running on the RT-Thread IoT operating system platform for different application areas, consisting of description information, source code or library files. RT-Thread provides an open package platform with officially available or developer-supplied packages that provide developers with a choice of reusable packages that are an important part of the RT-Thread ecosystem. The package ecosystem is critical to the choice of an operating system because these packages are highly reusable and modular, making it easy for application developers to build the system they want in the shortest amount of time. RT-Thread supports 450+ software packages.

## RT-Thread Features

- Designed for resource-constrained devices, the minimum kernel requires only 1.2KB of RAM and 3 KB of Flash.
- A variety of standard interfaces, such as POSIX, CMSIS, C++ application environment.
- Has rich components and a prosperous and fast growing package ecosystem.
- Elegant code style, easy to use, read and master.
- High Scalability. RT-Thread has high-quality scalable software architecture, loose coupling, modularity, is easy to tailor and expand.
- Supports high-performance applications.
- Supports all mainstream compiling tools such as GCC, Keil and IAR.
- Supports a wide range of <a href="https://www.rt-thread.io/board.html">architectures and chips</a>.

## Code Catalogue

   RT-Thread source code catalog is shown as follow:

| Name          | Description                                             |
| ------------- | ------------------------------------------------------- |
| BSP          | Board Support Package based on the porting of various development boards |
| components    | Components, such as finsh shell, file system, protocol stack etc. |
| documentation | Related documents, like coding style, doxygen etc.        |
| examples      | Related sample code                                     |
| include       | Head files of RT-Thread kernel                           |
| libcpu        | CPU porting code such as ARM/MIPS/RISC-V etc. |
| src           | The source files for the RT-Thread kernel. |
| tools         | The script files for the RT-Thread command build tool. |

RT-Thread has now been ported for nearly 200 development boards, most BSPs support MDK, IAR development environment and GCC compiler, and have provided default MDK and IAR project, which allows users to add their own application code directly based on the project. Each BSP has a similar directory structure, and most BSPs provide a README.md file, which is a markdown-format file that contains the basic introduction of BSP, and introduces how to simply start using BSP.

# Resources

## Supported Architectures

RT-Thread supports many architectures, and has covered the major architectures in current applications. Architecture and chip manufacturer involved:

- **ARM Cortex-M0/M0+**：manufacturers like ST
- **ARM Cortex-M3**：manufacturers like ST、Winner Micro、MindMotion, ect.
- **ARM Cortex-M4**：manufacturers like ST、Infineon、Nuvoton、NXP、[Nordic](https://github.com/RT-Thread/rt-thread/tree/master/bsp/nrf5x)、GigaDevice、Realtek、Ambiq Micro, ect.
- **ARM Cortex-M7**：manufacturers like ST、NXP
- **ARM Cortex-M23**：manufacturers like GigaDevice
- **ARM Cortex-M33**：manufacturers like ST
- **ARM Cortex-R4**
- **ARM Cortex-A8/A9**：manufacturers like NXP
- **ARM7**：manufacturers like Samsung
- **ARM9**：manufacturers like Allwinner、Xilinx 、GOKE
- **ARM11**：manufacturers like Fullhan
- **MIPS32**：manufacturers like loongson、Ingenic
- **RISC-V RV32E/RV32I[F]/RV64[D]**：manufacturers like sifive、[Canaan Kendryte](https://github.com/RT-Thread/rt-thread/tree/master/bsp/k210)、[bouffalo_lab](https://github.com/RT-Thread/rt-thread/tree/master/bsp/bouffalo_lab)、[Nuclei](https://nucleisys.com/)、[T-Head](https://www.t-head.cn/)
- **ARC**：manufacturers like SYNOPSYS
- **DSP**：manufacturers like TI
- **C-Sky**
- **x86**

## Supported IDE and Compiler

The main IDE/compilers supported by RT-Thread are:

- RT-Thread Studio IDE
- MDK KEIL
- IAR
- GCC

## RT-Thread Studio IDE

[User Manual](https://www.rt-thread.io/document/site/rtthread-studio/um/studio-user-manual/) | [Tutorial Videos](https://youtu.be/ucq5eJgZIQg)

RT-Thread Studio IDE (a.k.a. RT-Studio) is a one-stop intergrated development environment built by RT-Thread team. It has a easy-to-use graphical configuration system and a wealth of software packages and components resources. RT-Studio has the features of project creation, configuration and management,as well as code editing, SDK management, build configuration, debugging configuration, program download and debug. We're looking to make the use of RT-Studio as intuitive as possible, reducing the duplication of work and improving the development efficiency.

![studio](./documentation/figures/studio.gif)

## Env Tool

[User Manual](documentation/env/env.md) | [Tutorial Videos](https://www.youtube.com/watch?v=dEK94o_YoSo)

In the early stage, RT-Thread team also created an auxiliary tool called Env. It is an auxiliary tool with a TUI (Text-based user interface). Developers can use Env tool to configure and generate the GCC, Keil MDK, and IAR projects.

![env](./documentation/figures/env.png)

# Getting Started

[RT-Thread Programming Guide](https://www.rt-thread.io/document/site/tutorial/quick-start/introduction/introduction/) | [RT-Thread Studio IDE](https://www.rt-thread.io/studio.html) | [Kernel Sample](https://github.com/RT-Thread-packages/kernel-sample) | [RT-Thread Beginners Guide](https://www.youtube.com/watch?v=ZMi1O-Rr7yc&list=PLXUV89C_M3G5KVw2IerI-pqApdSM_IaZo)

Based on [STM32F103 BluePill](https://github.com/RT-Thread/rt-thread/tree/master/bsp/stm32/stm32f103-blue-pill) | [Raspberry Pi Pico](https://github.com/RT-Thread/rt-thread/tree/master/bsp/raspberry-pico)

## Simulator

RT-Thread BSP can be compiled directly and downloaded to the corresponding development board for use. In addition, RT-Thread also provides qemu-vexpress-a9 BSP, which can be used without hardware platform. See the getting started guide below for details. Getting Started of QEMU with Env:
[Windows](documentation/quick-start/quick_start_qemu/quick_start_qemu.md) | [Linux Ubuntu](documentation/quick-start/quick_start_qemu/quick_start_qemu_linux.md) | [Mac OS](documentation/quick-start/quick_start_qemu/quick_start_qemu_macos.md)

# License

RT-Thread follows the Apache License 2.0 free software license. It's completely open-source, can be used in commercial applications for free, does not require the disclosure of code, and has no potential commercial risk. License information and copyright information can generally be seen at the beginning of the code:

```c
/* Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 * ...
 */
```

# Community

RT-Thread is very grateful for the support from all community developers, and if you have any ideas, suggestions or questions in the process of using RT-Thread, RT-Thread can be reached by the following means, and we are also updating RT-Thread in real time on these channels. At the same time, any questions can be asked in the [issue section of RT-Thread repository](https://github.com/RT-Thread/rt-thread/issues) or [RT-Thread forum](https://club.rt-thread.io/), and community members will answer them.

[Website](https://www.rt-thread.io) | [Github](https://github.com/RT-Thread/rt-thread) | [Twitter](https://twitter.com/rt_thread) | [LinkedIn](https://www.linkedin.com/company/rt-thread-iot-os/posts/?feedView=all) | [Youtube](https://www.youtube.com/channel/UCdDHtIfSYPq4002r27ffqPw) | [Facebook](https://www.facebook.com/RT-Thread-IoT-OS-110395723808463/?modal=admin_todo_tour) | [Medium](https://rt-thread.medium.com/)

# Contribution

If you are interested in RT-Thread and want to join in the development of RT-Thread and become a code contributor,please refer to the [Code Contribution Guide](documentation/contribution_guide/contribution_guide.md).

## Thanks for the following contributors!

<a href="https://github.com/RT-Thread/rt-thread/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=RT-Thread/rt-thread" />
</a>
