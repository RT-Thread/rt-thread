# STM32F407 RT-Thread Spark Board BSP Introduction

## Overview

This document is a description of the BSP (Board Support Package) provided by the RT-Thread development team for the STM32F407 RT-Thread Spark Board.

The main contents are as follows:

- Introduction of Development Board Resources
- BSP Quick Start
- Advanced Usage

By reading Quick Start Section, developers can quickly get started with the BSP and run RT-Thread on the board. In the Advanced Usage Section, more advanced features will be introduced to help developers utilize RT-Thread to drive more on-board resources.

## Spark-1 Introduction

The STM32F407 is a development board based on the ARM Cortex-M4 core from RT-THREAD, with a maximum main frequency of 168Mhz. The board has a wealth of on-board resources, which can fully utilize the performance of the STM32F407 chip.

The appearance of the board is shown in the figure below:

![board](figures/board.png)

The development board commonly used **on-board resources** as follows:

- MCU: STM32F407ZGT6, 168MHz, 1024KB FLASH, 192KB RAM.
- External FLASH: W25Q128 (SPI, 16MB)
- Common Peripherals
  - LEDs: 2, LED_R (red, PF12), LED_B (green, PF11)
  - Keys, 4, KEY_UP (both wake-up function, PIN: PC5), KEY_DOWN (PIN: PC1), KEY_LEFT (PIN: PC0), KEY_RIGHT (PIN: PC4)
- Common interfaces: USB to serial port, SD card interface, USB SLAVE, USB HOST
- Debugging interface, standard ST-LINK 

For more details about the board, please refer to the official document [Introduction to STM32 Spark-1 Development Board](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/hw-board/spark-1/spark-1).


## Peripheral Support

The BSP currently supports the following peripherals:
| **Onboard peripherals** | **Support** |               **note**               |
| :------------ | :----------: | :-----------------------------------: |
| USB to Serial(COM1) |     Support     |                                    |
| COM2         |  Support  | Conflicts with Ethernet and PWM. Use CubeMX to reconfigure the UART2 pin if you want to use this peripheral. |
| COM3         |  Support  |                                           |
| **On-chip peripherals**              | **Supoort** |               **Note**               |
| UART         |     Support     |              UART1/2/3              |
| SPI          |     Support     |               SPI1/2/3                |
| ADC          |     Support     |                                       |
| RTC   | Support | Support external crystal and internal low-speed clock |
| WDT          |     Support     |                                       |

## Instructions for Use

The instructions for use are divided into two sections as follows:

- Quick Start

  This section is intended for newcomers to RT-Thread. Follow the simple steps to get the RT-Thread operating system running on the board and see the results.

- Advanced Usage

  This section is for developers who want to use more of the board's resources with the RT-Thread operating system. By using the ENV tool to configure the BSP, you can enable more on-board resources and realize more advanced functions.

### Quick Start

This BSP provides developers with MDK5 and IAR projects and supports GCC development environment. The following is an example of how to get the system up and running using the MDK5 development environment.

#### Hardware Connection

Connect the board to the PC with a cable and turn on the power switch.

#### Compile and Download

Double click the project.uvprojx file to open the MDK5 project, compile and download the program to the development board.

> The default configuration of the project is to use JLink to download the program. On the basis of connecting the development board via JLink, click the Download button to download the program to the development board.

#### Running Result

After successfully downloading the program, the system will run automatically. Observe the running effect of the LED on the development board, where the red LED is always on, the green LED will blink periodically.

Connect the corresponding serial port of the development board to PC, open the corresponding serial port (115200-8-1-N) in the terminal tool, and reset the device, you can see the output information of RT-Thread.



```bash

 \ | /
- RT -     Thread Operating System
 / | \     5.0.1 build Jul  4 2023 07:49:10
 2006 - 2022 Copyright by RT-Thread team
msh >
```

### Advanced Usage

This BSP only enables GPIO and Serial1 by default. If you want to use more advanced functions such as SD card, Flash, etc., you need to configure the BSP by using ENV utility, the steps are as below:

1. Open the env utility under bsp. 

2. Input `menuconfig` command to configure the project, save and exit after configuration. 

3. Enter the `pkgs --update` command to update the package. 

4. Enter the `scons --target=mdk5/iar` command to regenerate the project.

For a more detailed description of this chapter, please refer to [STM32 Series BSP Peripheral Driver Tutorial](... /docs/STM32 Series BSP Peripheral Driver Tutorial.md).

## Notes

Not available at this time

## Connection

Maintainer:

- [Supperthomas](https://github.com/supperthomas)



