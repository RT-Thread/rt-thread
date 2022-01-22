/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-17     lgnq         the first version
 */

Summary:
========
This directory contains the source code for M16C porting to rt-thread

two tasks is running:
led_task - blink the LED
finsh    - a user shell, comes with rt-thread

Where to get help:
==================
In case you have questions about, problems with or contributions for
Renesas M16C prot to rt-thread, you can send a mail to dzzxzz@gmail.com.

or you can post a message to the rt-thread forum
there are two forums:
http://www.rt-thread.org/phpbbforum
http://www.ourdev.cn/bbs

Where to get source code:
=========================
The rt-thread source code is maintained in google code
http://code.google.com/p/rt-thread/

use the following command to anonymously check out the latest source code:
svn checkout http://rt-thread.googlecode.com/svn/trunk/ rt-thread-read-only

Directory Hierarchy:
====================
/rt-thread
    /bsp
        /m16c62p
            /applications
                /application.c          - init led task
                /startup.c              - rt-thread start, include main()
            /drivers
                /board.c                - hardware init, init uart0
                /board.h
                /bsp.c                  - include led_init(), mcu_init(), timer0_init()
                /bsp.h
                /uart.c                 - implement uart0 device
                /uart.h
                /start_iar.asm          - assembly start of iar
                /interrupts_iar.asm     - include time0 interrupt handler, uart0 interrupt handler
                /vectors_iar.asm        - relocatable exception vector table
                /start_gcc.asm          - assembly start of gcc
                /interrupts_gcc.asm     - include time0 interrupt handler, uart0 interrupt handler
                /vectors_gcc.asm        - relocatable exception vector table
            /lnkm30627fhp.xcl       - IAR link file for m16c62p(m30627fhp)
            /m16c62p.ld             - GCC link file for m16c62p(m30627fhp)
            /rtconfig.h             - rt-thread config file
            /rtconfig.py            - SCONS config file
            /project.ewp            - IAR project file
            /project.eww            - IAR project file
            /SConsscript            - SCONS script file
            /SConstruct             - SCONS struct file
    /libcpu
        /m16c
            /m16c62p
                /context_iar.asm    - rt-thread context switch, used by IAR project
                /context_iar.S      - rt-thread context switch, used by SCONS + iar
                /context_gcc.S      - rt-thread context switch, used by SCONS + gcc
                /interrupt.c
                /stack.c            - rt-thread stack initlization

Build Project:
==============
there are two ways to build the renesase M16C project:
1,  install IAR Embedded Workbench for renesas m16c(recommend EWM16C-EV-3501.exe)
    Open Workspace rtt2m16c.eww by IAR directly
    rebuild all
    the target file(rtt2m16c.mot) will be produced in /rt-thread/bsp/m16c62p/Debug/Exe
    you can download the rtt2m16c.mot to m16c board with E8A

2,  install python, scons and IAR for m16c(recommend python2.7, scons1.3.1 and EWM16C-EV-3501.exe)
    open a windows cmd, and change directory to m16c project, like /rt-thread/bsp/m16c62p/
    #set PATH=C:\Python27\Scripts;%PATH%
    #scons -c
    #scons -j 2

3,  crate IAR project with template project
    #set PATH=C:\Python27\Scripts;%PATH%
    #scons --target=iar -s
    add the context_iar.asm to M16C62P, and remove the context_iar.S
