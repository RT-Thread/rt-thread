# RT-Thread #

[![Build Status](https://travis-ci.org/RT-Thread/rt-thread.svg)](https://travis-ci.org/RT-Thread/rt-thread)
[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/RT-Thread/rt-thread?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

RT-Thread is an open source real-time operating system for embedded devices from China, which has strong scalability: from a tiny kernel running on a tiny core, for example ARM Cortex-M0, or Cortex-M3/4/7, to a rich feature system running on ARM Cortex-A8, ARM Cortex-A9 DualCore etc.

## Overview ##

RT-Thread RTOS like a traditional real-time operating system. The kernel has real-time multi-task scheduling, semaphore, mutex, mail box, message queue etc. However, it has three different things:

* Device Driver;
* Component;
* Application Module

The device driver is more like a driver framework, UART, IIC, SPI, SDIO, USB device/host, EMAC, MTD NAND etc. The developer can easily add low level driver and board configuration, then combined with the upper framework, he/she can use lots of features.

The Component is a software concept upon RT-Thread kernel, for example a shell (finsh/msh shell), virtual file system (FAT, YAFFS, UFFS, ROM/RAM file system etc), TCP/IP protocol stack (lwIP), POSIX (thread) interface etc. One component must be a directory under RT-Thread/Components and one component can be descripted by a SConscript file (then be compiled and linked into the system).

The Appliation Module, or User Applicaion (UA) is a dyanmic loaded module, it can be compiled standalone without Kernel. Each UA has its own object container to manage thread/semaphore/kernel object which was created or initialized inside this UA. More information about UA, please visit another [git repo](https://github.com/RT-Thread/rtthread-apps). 

## Board Support Package ##

RT-Thread RTOS can support many architectures:

* ARM Cortex-M0
* ARM Cortex-M3/M4/7
* ARM Cortex-R4
* ARM Cortex-A8/A9
* ARM920T/ARM926 etc
* MIPS 
* x86
* PowerPC

## License ##

RT-Thread RTOS is free software; you can redistribute it and/or modify it under terms of the GNU General Public License version 2 as published by the Free Software Foundation. RT-Thread RTOS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with RT-Thread; see file COPYING. If not, write to the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

As a special exception, including RT-Thread RTOS header files in a file, instantiating RT-Thread RTOS generics or templates, or linking other files with RT-Thread RTOS objects to produce an executable application, does not by itself cause the resulting executable application to be covered by the GNU General Public License. This exception does not however invalidate any other reasons why the executable file might be covered by the GNU Public License.

## Usage ##

RT-Thread RTOS uses [scons](http://www.scons.org) as building system. Therefore, please install scons and Python 2.7 firstly. 
So far, the RT-Thread scons building system support the command line compile or generate some IDE's project. There are some option varaibles in the scons building script (rtconfig.py):

* ```CROSS_TOOL``` the compiler which you want to use, gcc/keil/iar. 
* ```EXEC_PATH``` the path of compiler. 

In SConstruct file:

```RTT_ROOT``` This variable is the root directory of RT-Thread RTOS. If you build the porting in the bsp directory, you can use the default setting. Also, you can set the root directory in ```RTT_ROOT``` environment variable and not modify SConstruct files.

When you set these variables correctly, you can use command:

    scons 

under BSP directory to simplely compile RT-Thread RTOS.

If you want to generate the IDE's project file, you can use command:

    scons --target=mdk/mdk4/mdk5/iar/cb -s 

to generate the project file. 

NOTE: RT-Thread scons building system will tailor the system according to your rtconfig.h configuration header file. For example, if you disable the lwIP in the rtconfig.h by commenting the ```#define RT_USING_LWIP```, the generated project file should have no lwIP related files. 

## Contribution ##

Please refer the contributors in the github. Thank all of RT-Thread Developers. 
