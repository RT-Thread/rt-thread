# NXP i. MX RT1050 EVK BSP(Board Support Package) Execution Instruction.

[中文页](README_zh.md) |

## Introduction

This document records the execution instruction of the BSP (board support package) provided by the RT-Thread development team for the NXP i. MX RT1050 EVK development board.

The document is covered in three parts:

- NXP i. MX RT1050 EVK Board Resources Introduction
- Quickly Get Started
- Advanced Features

By reading the Quickly Get Started section developers can quickly get their hands on this BSP and run RT-Thread on the board. More advanced features will be introduced in the Advanced Features section to help developers take advantage of RT-Thread to drive more on-board resources.

## Board Resources Introduction

The i.MX RT1050 EVK  is a development board based on ARM Cortex-M7. The maximum main frequency is 600 MHz, and it has a wealth of on-board resources that can take full advantage of the RT1052's chip performance.

[![board](https://github.com/RT-Thread/rt-thread/raw/master/bsp/imxrt/imxrt1052-nxp-evk/figures/board.jpg)](https://github.com/RT-Thread/rt-thread/blob/master/bsp/imxrt/imxrt1052-nxp-evk/figures/board.jpg)

The mainly-used resources of this board are shown as follows:

- MCU: MIMXRT1052DVL6A. Main Frequency 600MHz,
- Memory: 256MB SDRAM、512MB Hyper FLASH
- Common-used peripherals:
  - Motion Sensors: FXOS8700CQ
  - LED
- Common-used interfaces: USB、SD Card、Ethernet、LCD、Camera.
- Debug interface: Standard JTAG/SWD. For more details about this board, please refer to [nxp.com](https://www.nxp.com/)

## Peripheral Condition

Each peripheral supporting condition for this BSP is as follows:

| **On-chip Peripheral** | **Support** | **Remark** |
| ---------------------- | ----------- | ---------- |
| GPIO                   | Support     |            |
| UART                   | Support     | UART1      |

## Execution Instruction

### Quickly Get Started

This BSP provides MDK 5 and IAR projects for developers and it supports the GCC development environment. Here's an example of the MDK5 development environment, to introduce how to run the system.

Then, the necessary libraries should be pulled; otherwise, the compilation will fail.

```bash
    pkgs --update
```

#### Hardware Connection

Use a USB cable to connect the development board to the PC and turn on the power switch.

#### Compile and Download

Double-click the project.uvprojx file, to open the MDK 5 project, compile and download the project to the board.

> By default, the project uses the CMSIS-DAP to download the program, when the CMSIS-DAP connects the board, clicking the download button can download the program to the board.

### **Running Results**

Once the project is successfully downloaded, the system runs automatically. The green LED on the board will flash periodically.

Connect the serial port of the board to the PC, communicate with it via a serial terminal tool(115200-8-1-N). Reset the board and the startup information of RT-Thread will be observed:

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.1 build May 5 2019
 2006 - 2019 Copyright by rt-thread team
```

## **Advanced Features**

This BSP only enables GPIO and serial port 1 by default. If you need more advanced features, you need to configure the BSP with RT-Thread [Env tools](https://www.rt-thread.io/download.html?download=Env), as follows:

1. Open the env tool under BSP;
2. Enter menuconfig command to configure the project, then save and exit;
3. Enter pkgs --update command to update the package;
4. Enter scons --target=mdk4/mdk5/iar command to regenerate the project.

Learn how to use RT-Thread Env, click [Here](https://github.com/RT-Thread/rt-thread/blob/master/documentation/env/env.md).