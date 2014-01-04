# RT-Thread #

[![Build Status](https://travis-ci.org/RT-Thread/rt-thread.png)](https://travis-ci.org/RT-Thread/rt-thread)

RT-Thread is an open source real-time operating system for embedded devices from China. RT-Thread RTOS is a scalable real-time operating system: a tiny kernel for ARM Cortex-M0, Cortex-M3/4, or a full feature system in ARM Cortex-A8, ARM Cortex-A9 DualCore etc. 

## Overview ##

RT-Thread RTOS like a traditional real-time operating system. The kernel has real-time multi-task scheduling, semaphore, mutex, mail box, message queue etc. However, it has two different things:

* Device Driver;
* Component. 

The device driver is more like a driver framework, UART, SPI, USB device/host, EMAC, MTD NAND etc. The developer can easyly add low level driver and board configuration, then he/she can use lots of features. 

The Component is a software concept upon RT-Thread kernel, for example a shell (finsh shell), virtual file system (FAT, YAFFS, UFFS, ROM/RAM file system etc), TCP/IP protocol stack (lwIP), POSIX interface etc. One component must be a directory under RT-Thread/Components and one component can be descripted by a SConscript file (then be compiled and linked into the system).

## Board Support Package ##

RT-Thread RTOS can support many architectures:

* ARM Cortex-M0
* ARM Cortex-M3/M4
* ARM Cortex-R4
* ARM Cortex-A8/A9
* ARM920T/ARM926 etc

* MIPS 
* x86
* PowerPC

## License ##

RT-Thread RTOS is released under GPLv2+ license, that means any modification of RT-Thread RTOS should be feed back to community, but it can be friendly used in commercial products when mention your product is using RT-Thread RTOS. 

## Usage ##

RT-Thread RTOS uses [scons](http://www.scons.org) as its building system. Therefore, please install scons and Python 2.7 firstly. 

## Contribution ##

Thank all of RT-Thread Developers. 
