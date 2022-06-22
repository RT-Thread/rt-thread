# STM32F091-Nucleo BSP Introduction

[中文页](README_zh.md) |

## Introduction

This document records the execution instruction of the BSP (board support package) provided by the RT-Thread development team for the STM32F091RC-Nucleo development board.

The document is covered in three parts:

- STM32F091RC-Nucleo Board Resources Introduction
- Quickly Get Started
- Advanced Features

By reading the Quickly Get Started section developers can quickly get their hands on this BSP and run RT-Thread on the board. More advanced features will be introduced in the Advanced Features section to help developers take advantage of RT-Thread to drive more on-board resources.



## STM32F091RC-Nucleo Resources Introduction

The STM32F091RC-Nucleo is a development board that contains a ARM Cortex-M0. The maximum main frequency is 48 MHz, and it has a wealth of on-board resources that can take full advantage of the STM32F091's chip performance.

[![board](figures\board.jpg)](https://github.com/RT-Thread/rt-thread/blob/master/bsp/stm32/stm32f091-st-nucleo/figures/board.jpg)

The mainly-used resources of this board are shown as follows:

- MCU: STM32F091, Main Frequency 48MHz, 256KB FLASH, 32KB RAM
- External RAM: None
- External FLASH: None
- Common peripherals -Button: one, user (has the wake-up feature, PC13)
- Common-used interfaces: USB, Arduino interface, etc.
- Debug interface: Standard SWD interface.

### For more details about this board, please refer to [ST official](https://www.st.com/en/evaluation-tools/stm32-nucleo-boards.html?querycriteria=productId=LN1847).



## **Peripheral Condition**

Each peripheral supporting condition for this BSP is as follows:

| **On-board Peripherals**    | **Support** | **Remark**                                                   |
| --------------------------- | ----------- | ------------------------------------------------------------ |
| ST-LINK Virtual Serial Port | Support     | Using USART2                                                 |
| **On-chip Peripherals**     | **Support** | **Remark**                                                   |
| GPIO                        | Support     | PA0, PA1... PC15 ---> PIN: 0, 1...64                         |
| UART                        | Support     | USART1/2                                                     |
| SPI                         | Support     | SPI1                                                         |
| I2C                         | Support     |                                                              |
| TIMER                       | Support     |                                                              |
| ADC                         | Support     |                                                              |
| RTC                         | Support     | Support for external crystal oscillator and internal low-speed clocks |
| PWM                         | Support     |                                                              |
| FLASH                       | Support     |                                                              |
| IWGSupport                  |             |                                                              |



## Quickly Get Started

This BSP provides MDK4, MDK5, and IAR projects for developers and it supports the GCC development environment. Here's an example of the MDK5 development environment, to introduce how to run the system.

#### Hardware connection

Use a USB cable to connect the development board to the PC and turn on the power switch.

#### Compile and Download

Double-click the project.uvprojx file, to open the MDK5 project, compile and download the project to the board.

> By default, the executable file will be downloaded to the board by the simulator, which is connected to PC via the USB cable.

### Running Results

Once the project is successfully downloaded, the system runs automatically.

Connect the serial port of the board to PC, communicate with it via a serial terminal tool (115200bps, 8N1). Restart the board and the startup information of RT-Thread will be observed:

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.0 build Dec 21 2018
 2006 - 2018 Copyright by rt-thread team
msh >
```

### **Advanced Features**

This BSP only enables GPIO and serial port 2 by default. If you need more advanced features such as SPI, I2C, you need to configure the BSP with RT-Thread [ENV tools](https://www.rt-thread.io/download.html?download=Env) , as follows:

1. Open the env tool under BSP;
2. Enter menuconfig command to configure the project, then save and exit;
3. Enter pkgs --update command to update the package;
4. Enter scons --target=mdk4/mdk5/iar command to regenerate the project.

Learn how to use RT-Thread Env, click [Here](https://github.com/RT-Thread/rt-thread/blob/master/documentation/env/env.md).

