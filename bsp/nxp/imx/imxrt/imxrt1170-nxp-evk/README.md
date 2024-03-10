# NXP i. MX RT1170 EVK BSP(Board Support Package) Execution Instruction.

[中文页](README_zh.md) |

## Introduction

This document records the execution instruction of the BSP (board support package) provided by the RT-Thread development team for the NXP i. MX RT1170 EVK development board.

The document is covered in three parts:

- NXP i. MX RT1170 EVK Board Resources Introduction
- Quickly Get Started
- Advanced Features

By reading the Quickly Get Started section developers can quickly get their hands on this BSP and run RT-Thread on the board. More advanced features will be introduced in the Advanced Features section to help developers take advantage of RT-Thread to drive more on-board resources.

## Board Resources Introduction

i.MX RT1170 crossover MCUs are part of the EdgeVerse™ edge computing platform and are setting speed records at 1 GHz. This ground-breaking family combines superior computing power and multiple media capabilities with ease-of-use and real-time functionality. The dual core i.MX RT1170 MCU runs on the Arm® Cortex®-M7 core at 1 GHz and Arm Cortex-M4 at 400 MHz, while providing advanced security. The i.MX RT1170 MCU offers support over a wide temperature range and is designed for consumer, industrial and automotive markets.

![board](figures/board.jpg)


## Peripheral Condition

Each peripheral supporting condition for this BSP is as follows:


| **On-board Peripherals** | **Support** | **Remark**                            |
| ------------------------ | ----------- | ------------------------------------- |
| USB                      | √           |                                       |
| SPI Flash                | √           |                                       |
| Ethernet                 | √           |                                       |
| **On-chip Peripherals**  | **Support** | **Remark**                            |
| GPIO                     | √           |                                       |
| SPI                      | √           |                                       |
| I2C                      | √           |                                       |
| SDIO                     | √           |                                       |
| RTC                      | √           |                                       |
| PWM                      | √           |                                       |
| CAN                      | √           |                                       |

## Execution Instruction

### Quickly Get Started

This BSP provides MDK 5 and IAR projects for developers. Here's an example of the IAR development environment, to introduce how to run the system.

#### Hardware Connection

Use a USB cable to connect the development board to the PC and turn on the power switch.

#### Compile and Download

Double-click the project.eww file, to open the IAR project, compile and download the project to the board.

> By default, the project uses the CMSIS-DAP to download the program, when the CMSIS-DAP connects the board, clicking the download button can download the program to the board.

### **Running Results**

Once the project is successfully downloaded, the system runs automatically.

Connect the serial port of the board to the PC, communicate with it via a serial terminal tool(115200-8-1-N). Reset the board and the startup information of RT-Thread will be observed:

```
 \ | /
- RT -     Thread Operating System
 / | \     4.1.1 build May 13 2022 11:37:59
 2006 - 2022 Copyright by RT-Thread team
```

## **Advanced Features**

This BSP only enables serial port 1 by default. If you need more advanced features, you need to configure the BSP with RT-Thread [Env tools](https://www.rt-thread.io/download.html?download=Env), as follows:

1. Open the env tool under BSP;
2. Enter menuconfig command to configure the project, then save and exit;
3. Enter pkgs --update command to update the package;
4. Enter scons --target=mdk5/iar command to regenerate the project.

Learn how to use RT-Thread Env, click [Here](https://github.com/RT-Thread/rtthread-manual-doc/blob/master/env/env.md).