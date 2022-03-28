# STM32F469-ST-DISCO BSP Introduction

[中文](README_zh.md) 

This document records the instruction of the BSP (board support package) that provided by the RT-Thread development team for the STM32F469-ST-DISCO development board.

The document is covered in three parts:

- Resources Introduction
- Quickly Get Started
- Advanced Features

By reading the ***Quickly Get Started*** section developers can quickly get their hands on this BSP and run RT-Thread on the board. More advanced features will be introduced in the Advanced Features section to help developers take advantage of RT-Thread to drive more on-board resources.

## Resources Introduction

The STM32F469 Discovery kit allows users to easily develop applications with the STM32F469 high-performance MCUs with ARM®Cortex®-M4 core and Chrom-ART Accelerator™. The discovery kit enables a wide range of use cases taking advantage of premium graphics, audio, multi-sensor support, WVGA color display, security, memory extension and connectivity features. 

[![board](https://github.com/RT-Thread/rt-thread/raw/master/bsp/stm32/stm32f469-st-disco/figures/board.png)](https://github.com/RT-Thread/rt-thread/blob/master/bsp/stm32/stm32f469-st-disco/figures/board.png)

Features:

- MCU: STM32F469NIH6U, 180MHz, 2048KB FLASH, 384KB(Includes 64KB CCM) RAM
- External RAM: 25Q128A, 16MB
- External FLASH: 7LL12D9NOR, 16MB
- Common-used Peripherals:
  - LED: 4, LD1(Green, PG6), LD2(Orange, PD4), LD3(Red,PD5), LD4(Blue, PK3)
  - Button: 1, USER( has wake-up feature, PA0）
  - LCD：4 inches 800x480 pixel TFT
  - Audio: SAI Audio DAC
- Common-used interface: Arduino UNO V3 、MicroSD Card、Audio、LCD、I2C, etc.
- Debugging interface, standard ST-LINK/V2-1 SWD 

More info about this board, please check [ST Official](https://www.st.com/en/evaluation-tools/32f469idiscovery.html). 

## Peripherals Condition

Each peripheral supporting condition for this BSP is as follows:

| **On-board Peripherals** | **Support** | Remark                                                    |
| ------------------------ | ----------- | --------------------------------------------------------- |
| SDRAM                    | √           | 16MB                                                      |
| LCD                      | √           | MIPI LCD, otm8009a                                        |
| SDCARD                   | √           | Support hot swapping, plug-in detection interval of 200ms |
| TOUCH                    | √           | ft6206                                                    |
| **On-chip Peripherals**  | **Support** | **Remark**                                                |
| GPIO                     | √           |                                                           |
| USART                    | v           | USART3                                                    |
| SPI                      | √           | SPI3                                                      |
| QSPI                     | √           |                                                           |
| I2C                      | √           | I2C                                                       |
| FLASH                    | √           | Fits to [FAL](https://github.com/RT-Thread-packages/fal)  |
| SDI                      | √           |                                                           |
| USB Device               | √           |                                                           |
| **Expansion Module**     | **Support** | **Remark**                                                |
| N/A                      | N/A         | N/A                                                       |

### Quickly Get Started

This BSP provides MDK4, MDK5, and IAR projects for developers and it supports the GCC development environment. Here's an example of the MDK5 development environment, to introduce how to run the system.

#### Hardware Connection

Use a cable to connect the development board to the PC and turn on the power switch.

#### Compile and Download

Double-click the `project.uvprojx` file to open the MDK5 project, compile and download the program to the development board.

> The project defaults to use the st-link emulator to download the program, and as we're connecting the development board via st-link, click the Download button can directly download the program to the development board.

#### Running Results

After the program is successfully downloaded, the system runs automatically. The LED(LD1, Green) will flash. 

Connect the corresponding serial port of the development board to the PC, and when the corresponding serial port ( 115200-8-1-N) is opened in the terminal tool, the output information of RT-Thread can be seen when the device is reset:

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.1 build Apr  9 2019
 2006 - 2019 Copyright by rt-thread team
msh >
```

## **Advanced Features**

This BSP only enables GPIO and UART3 by default. If you need more advanced features such as SD Card, Flash, or you need to configure the BSP with RT-Thread homegrown [ENV tool](https://www.rt-thread.io/download.html?download=Env), as follows:

1. Open the ENV tool under the specific BSP folder;
2. Enter `menuconfig` command to configure the project, then save and exit;
3. Enter `pkgs --update` command to update the package;
4. Enter `scons --target=mdk4/mdk5/iar` command to regenerate the project.
