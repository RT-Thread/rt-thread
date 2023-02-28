# Synopsys ARC Boards support with embARC_BSP

## embARC_BSP

The embARC Board support Package (BSP) is a software distributions aimed at facilitating
the development and evaluation of embedded systems based on ARCv2 processors, which is
designed to provide a minimal board support package for ARC users by defining
consistent and simple software interfaces to the processors and onboard devices.

The embARC BSP is a new generation embARC software development package. ​
It is designed to be the inter-layer between hardware and operating system. ​
BSP could hide the difference of hardware/boards, provide a unified interface to upper-layer. ​
In the scenarios that no OS is required, embARC BSP can also standalone and work in baremetal.

embARC_BSP features:

* Support MetaWare & GNU toolchains​
* Support all development boards and tcf​
* Support various build systems and compiling environments,
  such as ARC MetaWare & GNU IDE, makefile​
* Designware and Subsystem drivers, including UART and GPIO, I2C, SPI, etc. ​
* No middleware, no OS​
* Easy to port to different platform / OS​
* One example (UART, GPIO, timer)​
* Code coverage reach 100% in test. ​
* MISRA-C compliance​
* C & C++ support, assembly support

## Supported Boards

* [ARC Software Development Platform](https://www.synopsys.com/dw/ipdir.php?ds=arc-software-development-platform)
* [ARC EM Starter Kit](https://www.synopsys.com/dw/ipdir.php?ds=arc_em_starter_kit)
* [ARC EM Software Development Platform](https://www.synopsys.com/dw/ipdir.php?ds=arc-em-software-development-platform)
* [ARC HS Development Kit](https://www.synopsys.com/dw/ipdir.php?ds=arc-hs-development-kit)
* [ARC IoT Development Kit](https://www.synopsys.com/dw/ipdir.php?ds=arc_iot_development_kit)


## Software Requirement

### embarc_bsp

There are two ways to get embarc_bsp:

#### use RT-Thread ENV tool:

embARC_BSP has been configured as package module, you can just run the command `pkgs --update` in <RTT_ROOT>/bsp/synopsys/boards
folder using ENV tool.

#### without RT-Thread ENV tool:

We can get it from github: [embarc_bsp](https://github.com/foss-for-synopsys-dwc-arc-processors)

The default path for embarc_bsp is <RTT_ROOT>/bsp/synopsys/boards/packages/embARC_bsp-upstream,
when you use other path, please set the environment variable `EMBARC_BSP_ROOT`.

### Toolchain

Now both GNU and MetaWare Toolchain are supported, set the System environment variable RTT_CC select the toolchain.

GNU:

    set RTT_CC=gcc

MetaWare:

    set RTT_CC=mw

#### GNU

The ARC GNU Toolchain offers all of the benefits of open source tools, including complete source code and a large install base. The ARC GNU IDE Installer consists of Eclipse IDE with [ARC GNU plugin for Eclipse](https://github.com/foss-for-synopsys-dwc-arc-processors/arc_gnu_eclipse/releases), [ARC GNU prebuilt toolchain](https://github.com/foss-for-synopsys-dwc-arc-processors/toolchain/releases) and [OpenOCD for ARC](https://github.com/foss-for-synopsys-dwc-arc-processors/openocd>)

Here, the ARC GNU toolchain is installed to `c:\arc_gnu`. If not, please change the path configuration in rtconfig.py.

When you use GNU Toolchain, you need to install [Zadig](http://zadig.akeo.ie) to replace the default FTDI driver with WinUSB driver. See [How to Use OpenOCD on Windows](https://github.com/foss-for-synopsys-dwc-arc-processors/arc_gnu_eclipse/wiki/How-to-Use-OpenOCD-on-Windows>) for more information.

#### MetaWare
The [DesignWare ARC MetaWare Development Toolkit](https://www.synopsys.com/dw/ipdir.php?ds=sw_metaware) builds on a long legacy of industry-leading compiler and debugger products for embedded applications. It is a complete solution that contains all the components needed to support the development, debugging, and tuning of embedded applications for the DesignWare® ARC® processors.

Here, the ARC MetaWare toolchain is installed to `C:\ARC\MetaWare`. If not, please change the path configuration in rtconfig.py.





## Build & Debug

### Build embarc_lib

please run the following cmds to build embarc_lib

    cd <rt-thread-root>/bsp/synopsys/boards
    scons --embarc_build

### Build

please run the following cmds to build

    cd <rt-thread-root>/bsp/synopsys/boards
    scons

### Debug

After compile, please use the following cmds to debug

    scons --gdb #use gdb debugger
    scons --mdb #use mdb debugger


### How to choose different boards

There are some parameters we can use in scons, for example:

    scons --BOARD=emsk --BD_VER=23 --CUR_CORE=arcem9d --TOOLCHAIN=mw --OLEVEL=O2

 * BOARD: choose the board, we can set: `emsk, iotdk, emsdp, hsdk, axs`.
 * BD_VER: choose the board version, some boards have different versions, for example,
   we can set: `10, 22, 23` for emsk board.
 * CUR_CORE: choose the arc cores, some boards have different cores, for example,
   we can set: `arcem7d, arcem9d, arcem11d` for emsk board.
 * TOOLCHAIN: choose the toolchain to build embarc_lib, we can set: `mw, gnu`.
 * OLEVEL: choose the build optimize level, we can set: `O0, O2, Os`.

For more information, you can run the command `scons -h`.


## Maintainer
- [vonhust](https://github.com/vonhust)
- [IRISZZW](https://github.com/IRISZZW)
