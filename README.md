# RT-Thread #

[中文页](README_zh.md) |

[![GitHub](https://img.shields.io/github/license/RT-Thread/rt-thread.svg)](https://github.com/RT-Thread/rt-thread/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RT-Thread/rt-thread.svg)](https://github.com/RT-Thread/rt-thread/releases)
[![Build Status](https://travis-ci.org/RT-Thread/rt-thread.svg)](https://travis-ci.org/RT-Thread/rt-thread)
[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/RT-Thread/rt-thread?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![GitHub pull-requests](https://img.shields.io/github/issues-pr/RT-Thread/rt-thread.svg)](https://github.com/RT-Thread/rt-thread/pulls)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat)](https://github.com/RT-Thread/rt-thread/pulls)

# Introduction

RT-Thread was born in 2006, it is an open source, neutral, and community-based real-time operating system (RTOS). 

RT-Thread is mainly written in C language, easy to understand and easy to port(can be quickly port to a wide range of mainstream MCUs and module chips). It applies object-oriented programming methods to real-time system design, making the code elegant, structured, modular, and very tailorable. 

RT-Thread has Standard version and Nano version. For resource-constrained microcontroller (MCU) systems, the NANO kernel version that requires only 3KB Flash and 1.2KB RAM memory resources can be tailored  with easy-to-use tools; And for resource-rich IoT devices, RT-Thread can use the on-line software package management tool, together with system configuration tools, to achieve intuitive and rapid modular cutting, seamlessly import rich software packages, thus achieving complex functions like Android's graphical interface and touch sliding effects, smart voice interaction effects, and so on.

## RT-Thread Architecture

RT-Thread has not only a real-time kernel, but also rich components. Its architecture is as follows:


![architecture](./documentation/figures/architecture.png)


It includes:

- Kernel layer: RT-Thread kernel, the core part of RT-Thread, includes the implementation of objects in the kernel system, such as multi-threading and its scheduling, semaphore, mailbox, message queue, memory management, timer, etc.; libcpu/BSP (Chip Migration Related Files/Board Support Package) is closely related to hardware and consists of peripheral drivers and CPU porting.

- Components and Service Layer: Components are based on upper-level software on top of the RT-Thread kernel, such as virtual file systems, FinSH command-line interfaces, network frameworks, device frameworks, and more. Its modular design allows for high internal cohesion inside the components and low coupling between components. 
  
- RT-Thread software package: A general-purpose software component running on the RT-Thread IoT operating system platform for different application areas, consisting of description information, source code or library files. RT-Thread provides an open package platform with officially available or developer-supplied packages that provide developers with a choice of reusable packages that are an important part of the RT-Thread ecosystem. The package ecosystem is critical to the choice of an operating system because these packages are highly reusable and modular, making it easy for application developers to build the system they want in the shortest amount of time. RT-Thread supports more than 180 software packages. 

## RT-Thread Features

- Designed for resource-constrained devices, the minimum kernel requires only 1.2KB of RAM and 3 KB of Flash.                                                                                                              

- Has rich components and a prosperous and fast growing package ecosystem.                                                              

- Elegant code style, easy to use, read and master.                                                                                                                                                                             

- High Scalability. RT-Thread has high-quality scalable software architecture, loose coupling, modularity, is easy to tailor and expand.                                                                                                                                                                           

- Supports high-performance applications.                                                                                                                    

- Supports cross-platform and a wide range of chips.                                                                                                          

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

RT-Thread has now been ported for nearly 90 development boards, most BSPs support MDK, IAR development environment and GCC compiler, and have provided default MDK and IAR project, which allows users to add their own application code directly based on the project. Each BSP has a similar directory structure, and most BSPs provide a README.md file, which is a markdown-format file that contains the basic introduction of BSP, and introduces how to simply start using BSP.

Env is a development tool developed by RT-Thread which provides a build environment, text graphical system configuration, and package management capabilities for project based on the RT-Thread operating system. Its built-in `menuconfig` provides an easy-to-use configuration tool. It can tailor the kernels, components and software packages freely, so that the system can be constructed by building blocks.

- [Download Env Tool](https://www.rt-thread.io/download.html?download=Env)
- [User manual of Env](https://github.com/RT-Thread/rtthread-manual-doc/blob/master/env/env.md)

# Resources

## Supported Architectures

RT-Thread supports many architectures, and has covered the major architectures in current applications. Architecture and chip manufacturer involved:

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
- **RISC-V**：manufacturers like Hifive、Kendryte、[Nuclei](https://nucleisys.com/)
- **ARC**：manufacturers like SYNOPSYS
- **DSP**：manufacturers like TI
- **C-Sky**
- **x86**

## Supported IDE and Compiler

The main IDE/compilers supported by RT-Thread are:

- MDK KEIL
- IAR
- GCC
- RT-Thread Studio

Use Python-based [scons](http://www.scons.org/) for command-line builds.

RT-Thread Studio Demonstration:

![studio](./documentation/figures/studio.gif)                                                 

## Getting Started

RT-Thread BSP can be compiled directly and downloaded to the corresponding development board for use. In addition, RT-Thread also provides qemu-vexpress-a9 BSP, which can be used without hardware platform. See the getting started guide below for details.

- [Getting Started of QEMU (Windows)](https://github.com/RT-Thread/rtthread-manual-doc/blob/master/documentation/quick_start_qemu/quick_start_qemu.md)

- [Getting Started of QEMU (Ubuntu)](https://github.com/RT-Thread/rtthread-manual-doc/blob/master/documentation/quick_start_qemu/quick_start_qemu_linux.md)

## Documentation

[RT-Thread Programming Guide](https://github.com/RT-Thread/rtthread-manual-doc) | [RT-Thread Supported Chips & Boards](https://www.rt-thread.io/board.html) |
[RT-Thread Software Package](https://github.com/RT-Thread/packages) | [RT-Thread Studio](https://www.rt-thread.io/studio.html) 

## Sample

[Kernel Sample](https://github.com/RT-Thread-packages/kernel-sample) | [Device Sample Code](https://github.com/RT-Thread-packages/peripheral-sample) | [File System Sample Code](https://github.com/RT-Thread-packages/filesystem-sample ) | [Network Sample Code](https://github.com/RT-Thread-packages/network-sample ) | 

[Based on the STM32L475 IoT Board SDK](https://github.com/RT-Thread/IoT_Board) | [Based on the W601 IoT Board SDK](https://github.com/RT-Thread/W601_IoT_Board)

# License

RT-Thread is an open source software and has been licensed under Apache License Version 2.0 since v3.1.1. License information and copyright information can generally be seen at the beginning of the code:

```c
/* Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 * ...
 */
```

To avoid possible future license conflicts, developers need to sign a Contributor License Agreement (CLA) when submitting PR to RT-Thread.

# Community

RT-Thread is very grateful for the support from all community developers, and if you have any ideas, suggestions or questions in the process of using RT-Thread, RT-Thread can be reached by the following means, and we are also updating RT-Thread in real time on these channels. At the same time, Any questions can be asked in the [issue section of rtthread-manual-doc](https://github.com/RT-Thread/rtthread-manual-doc/issues). By creating a new issue to describe your questions, community members will answer them.

[Website](https://www.rt-thread.io) | [Twitter](https://twitter.com/rt_thread) | [Youtube]( https://www.youtube.com/channel/UCdDHtIfSYPq4002r27ffqPw?view_as=subscriber) | [Gitter](  https://gitter.im/RT-Thread) | [Facebook](https://www.facebook.com/RT-Thread-IoT-OS-110395723808463/?modal=admin_todo_tour) | [Medium](https://medium.com/@rt_thread)

# Contribution

If you are interested in RT-Thread and want to join in the development of RT-Thread and become a code contributor,please refer to the [Code Contribution Guide](https://github.com/RT-Thread/rtthread-manual-doc/blob/master/documentation/contribution_guide/contribution_guide.md).
