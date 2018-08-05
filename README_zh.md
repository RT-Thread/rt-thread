# RT-Thread #

[![GitHub release](https://img.shields.io/github/release/RT-Thread/rt-thread.svg)](https://github.com/RT-Thread/rt-thread/releases)
[![Build Status](https://travis-ci.org/RT-Thread/rt-thread.svg)](https://travis-ci.org/RT-Thread/rt-thread)
[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/RT-Thread/rt-thread?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![GitHub pull-requests](https://img.shields.io/github/issues-pr/RT-Thread/rt-thread.svg)](https://github.com/RT-Thread/rt-thread/pulls)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat)](https://github.com/RT-Thread/rt-thread/pulls)

RT-Thread是一个来自中国的开源物联网操作系统，它提供了非常强的可伸缩能力：从一个可以运行在ARM Cortex-M0芯片上的极小内核，到中等的ARM Cortex-M3/4/7系统，甚至是运行于MIPS32、ARM Cortex-A系列处理器上功能丰富系统。

## 简介 ##

RT-Thread包含了一个自有的、传统的硬实时内核：可抢占的多任务实时调度器，信号量，互斥量，邮箱，消息队列，信号等。当然，它和传统的实时操作系统还存在着三种不同：

* 设备驱动框架；
* 软件组件；
* 应用模块

设备驱动框架更类似一套驱动框架，涉及到UART，IIC，SPI，SDIO，USB从设备/主设备，EMAC，NAND闪存设备等。它会把这些设备驱动中的共性抽象/抽取出来，而驱动工程师只需要按照固定的模式实现少量的底层硬件操作及板级配置。通过这样的方式，让一个硬件外设更容易地对接到RT-Thread系统中，并获得RT-Thread平台上的完整软件栈功能。

软件组件是位于RT-Thread内核上的软件单元，例如命令行（finsh/msh shell），虚拟文件系统（FAT，YAFFS，UFFS，ROM/RAM文件系统等），TCP/IP网络协议栈（lwIP），Libc/POSIX标准层等。一般的，一个软件组件放置于一个目录下，例如RT-Thread/components目录下的文件夹，并且每个软件组件通过一个 SConscript文件来描述并被添加到RT-Thread的构建系统中。当系统配置中开启了这一软件组件时，这个组件将被编译并链接到最终的RT-Thread固件中。

注：随着RT-Thread 3.0中的包管理器开启，越来越多的软件组件将以package方式出现在RT-Thread平台中。而RT-Thread平台更多的是指：

* RT-Thread内核；
* shell命令行；
* 虚拟文件系统；
* TCP/IP网络协议栈；
* 设备驱动框架；
* Libc/POSIX标准层。

更多的IoT软件包则以package方式被添加到RT-Thread系统中。

应用模块，或者说用户应用（User Application，UA）是一个可动态加载的模块：它可以独立于RT-Thread固件而单独编译。一般的，每个UA都包含一个main函数入口；一个它自己的对象容器，用于管理这个应用的任务/信号量/消息队列等内核对象，创建、初始化、销毁等。更多关于UA的信息，请访问另外一个 [git 仓库](https://github.com/RT-Thread/rtthread-apps) 了解。

## 支持的芯片架构 ##

RT-Thread支持数种芯片体系架构，已经覆盖当前应用中的主流体系架构：

* ARM Cortex-M0
* ARM Cortex-M3/M4/7
* ARM Cortex-R4
* ARM Cortex-A8/A9
* ARM920T/ARM926 etc
* MIPS32
* x86
* Andes
* C-Sky
* RISC-V
* PowerPC

## 许可证 ##

RT-Thread is free software; you can redistribute it and/or modify it under terms of the GNU General Public License version 2 as published by the Free Software Foundation. RT-Thread RTOS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with RT-Thread; see file COPYING. If not, write to the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

As a special exception, including RT-Thread RTOS header files in a file, instantiating RT-Thread RTOS generics or templates, or linking other files with RT-Thread RTOS objects to produce an executable application, does not by itself cause the resulting executable application to be covered by the GNU General Public License. This exception does not however invalidate any other reasons why the executable file might be covered by the GNU Public License.

RT-Thread始终以开源的方式发展，所有发布的代码都遵循GPLv2+许可证。注意，GPLv2+的意思是，它是GPLv2的一个修改版本，添加了一定的例外。简单的来说，当使用RT-Thread时，除了RT-Thread发布的源代码以外的代码，可以不用遵循GPLv2的方式开源代码。

## 编译 ##

RT-Thread使用了[scons](http://www.scons.org)做为自身的编译构建系统，并进行一定的定制以满足自身的需求（可以通过scons --help查看RT-Thread中额外添加的命令）。在编译RT-Thread前，请先安装Python 2.7.x及scons。

截至目前，RT-Thread scons构建系统可以使用命令行方式编译代码，或者使用scons来生成不同IDE的工程文件。在使用scons时，需要对构建配置文件（rtconfig.py）中如下的变量进行配置：

* ```CROSS_TOOL``` 指定希望使用的工具链，例如gcc/keil/iar. 
* ```EXEC_PATH``` 工具链的路径. 

注：在SConstruct文件中：

```RTT_ROOT``` 这个变量指向了RT-Thread的发布源代码根目录。如果你仅计划编译bsp目录下的target，这个`RTT_ROOT`可以使用默认配置。另外，你也可以设置同名的环境变量来指向不同的RT-Thread源代码根目录。

当你把相关的配置都配置正确后，你可以在具有目标目录下（这个目录应包括rtconfig.py、SContruct文件）执行以下命令：

    scons 

从而简单地就编译好RT-Thread。

如果你希望使用IDE来编译RT-Thread，你也可以使用命令行：

    scons --target=mdk/mdk4/mdk5/iar/cb -s 

来生成mdk/iar等的工程文件。而后在IDE中打开project前缀的工程文件来编译RT-Thread。

注意：RT-Thread的scons构建系统会根据配置头文件rtconfig.h来裁剪系统。例如，如果你关闭了rtconfig.h中的lwIP定义（通过注释掉```#define RT_USING_LWIP```的方式），则scons生成的IDE工程文件中将自动不包括lwIP相关的文件。而在RT-Thread 3.0版本中，可以通过menuconfig的方式来配置整个系统，而不需要再手工更改rtconfig.h配置头文件。

## 贡献者 ##

请访问github上RT-Thread项目上的contributors了解已经为RT-Thread提交过代码，PR的贡献者。感谢所有为RT-Thread付出的开发者们！
