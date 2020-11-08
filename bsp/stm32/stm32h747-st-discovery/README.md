# STM32H747-ST-DISCOVERY BSP (Board Support Package) Execution Instruction

[中文页](README_zh.md) |

## Introduction

This document records the execution instruction of the BSP (board support package) provided by the RT-Thread development team for the STM32H747-ST-DISCOVERY development board.

The document is covered in three parts:

- STM32H747-ST-DISCOVERY Board Resources Introduction
- Quickly Get Started
- Advanced Features

By reading the Quickly Get Started section developers can quickly get their hands on this BSP and run RT-Thread on the board. More advanced features will be introduced in the Advanced Features section to help developers take advantage of RT-Thread to drive more on-board resources.

## Board Resources Introduction

The STM32H747-ST-DISCOVERY is a development board that contains a ARM Cortex-M7. The maximum main frequency is 480 MHz, and it has a wealth of on-board resources that can take full advantage of the STM32H747's chip performance.



[![board](https://github.com/RT-Thread/rt-thread/raw/master/bsp/stm32/stm32h747-st-discovery/figures/board.png)](https://github.com/RT-Thread/rt-thread/blob/master/bsp/stm32/stm32h747-st-discovery/figures/board.png)

The mainly-used resources of this board are shown as follows:

- MCU: STM32H747
- Main Frequency 480MHz
- Memory: 2MB FLASH, 1MB RAM
- Common-used peripherals: USB、Ethernet、arduino API etc.
- Debug interface: Standard JTAG/SWD.

For more details about this board, please refer to the ST official documentation [STM32H747I-DISCO](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-mpu-eval-tools/stm32-mcu-mpu-eval-tools/stm32-discovery-kits/stm32h747i-disco.html)。

## Peripheral Condition

Each peripheral supporting condition for this BSP is as follows:

| **On-board Peripheral** | **Support** | **Remark** |
| ----------------------- | ----------- | ---------- |
| USB                     | Support     |            |
| **On-chip Peripheral**  | **Support** | **Remark** |
| GPIO                    | Support     |            |
| UART                    | Support     | UART1      |

## Execution Instruction

### Quickly Get Started

This BSP provides MDK 5 and IAR projects for developers and it supports the GCC development environment. Here's an example of the MDK5 development environment, to introduce how to run the system.

#### **Hardware Connection**

Use a USB cable to connect the development board to the PC and turn on the power switch.

#### **Compile and Download**

Double-click the project.uvprojx file, to open the MDK 5 project (MDK requires to download V 5.29 and above to support ST-LINK V3), compile and download the project to the board.

> By default, the project uses the ST_LINK simulator to download the program, when the ST_LINK connects the board, clicking the download button can download the program to the board.

### **Running Results**

Once the project is successfully downloaded, the system runs automatically, and LED will flash.

Connect the serial port of the board to PC, communicate with it via a serial terminal tool (115200-8-1-N). Restart the board and the startup information of RT-Thread will be observed:

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Feb 24 2020
 2006 - 2020 Copyright by rt-thread team
msh >
```

### **Advanced Features**

This BSP only enables GPIO and serial port 1 by default. If you need more advanced features, you need to configure the BSP with [RT-Thread ENV tools](https://www.rt-thread.io/download.html?download=Env) , as follows:

1. Open the env tool under BSP.
2. Enter menuconfig command to configure the project, then save and exit.
3. Enter pkgs --update command to update the package.
4. Enter scons --target=mdk4/mdk5/iar command to regenerate the project.

Learn how to use RT-Thread Env, click [Here](https://github.com/RT-Thread/rtthread-manual-doc/blob/master/env/env.md).

## **Notes**

- Debug serial port has the mapping description for serial port 1.

  PA9 ------> USART1_TX

  PA10 ------> USART1_RX