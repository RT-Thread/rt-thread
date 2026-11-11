# LXB723ZG-P1 Development Board BSP Instructions

[中文页](README_zh.md) |

## Introduction

This document provides the BSP (Board Support Package) instructions for the LXB723ZG-P1 development board developed by Pcb-yun based on STM32H723.

The main content includes:

- Development board resources introduction
- BSP quick start guide
- Advanced usage methods

By reading the quick start section, developers can quickly get started with this BSP and run RT-Thread on the development board. In the advanced usage guide section, more advanced features will be introduced to help developers use RT-Thread to drive more on-board resources.

## Development Board Introduction

LXB723ZG-P1 is a development board launched by LXB (鹿小班) based on the ARM Cortex-M7 core, with a maximum frequency of 550MHz.
The development board integrates resources including: W25Q64 8MB OSPI Flash (available for user's own use), SPI screen and 8-bit DCMI camera FPC socket (corresponding accessories need to be purchased separately), self-ejecting TF card socket, Type-C interface, 108 extended IO interfaces, reset button and BOOT button (no custom buttons).

The appearance of the development board is shown in the figure below:

![board](figures/board.png)

The commonly used **on-board resources** of this development board are as follows:

- MCU: STM32H723ZGT6, frequency 550MHz, 1MB FLASH, 564K RAM
- External FLASH: W25Q64, 8MB
- Common peripherals
  - LED: 1, DS0 (blue, PG7)
- Common interfaces: Type-C interface, TF card interface, 8-bit DCMI camera interface (FPC), SPI screen interface (FPC)
- Debugging interface: Standard SWD interface

For more detailed information about the development board, please refer to [LXB723ZG-P1 Core Board](https://item.taobao.com/item.htm?abbucket=17&id=831139393305&mi_id=0000Hr_7YuvNzXkf9ukTHb3zeHF5wgFLDumgDHyYZNYGbIs&ns=1&priceTId=2150419217612182188817937e1045&skuId=5739335367823&spm=a21n57.sem.item.1.47ef3a43Uq2LAX&utparam=%7B%22aplus_abtest%22%3A%229add53b62022488d347cf05287760183%22%7D&xxc=taobaoSearch).

## Peripheral Support

The current support status of peripherals for this BSP is as follows:

| **On-board Peripherals** | **Support Status** | **Notes**                            |
| :---------------------- | :---------------- | :----------------------------------- |
| OSPI Flash              | Not supported     | OSPI1                                |
| TF card                 | Not supported     | SDMMC1                               |
| SPI screen              | Not supported     | SPI6                                 |
| DCMI camera             | Not supported     |                                      |

| **On-chip Peripherals**  | **Support Status** | **Notes**                            |
| :---------------------- | :---------------- | :----------------------------------- |
| GPIO                    | Supported         |                                      |
| UART                    | Supported         |                                      |

## Usage Instructions

Usage instructions are divided into the following two chapters:

- Quick Start

    This chapter is a usage guide prepared for beginners who are new to RT-Thread. Following simple steps, you can run the RT-Thread operating system on this development board and see the experimental results.

- Advanced Usage

    This chapter is prepared for developers who need to use more development board resources on the RT-Thread operating system. By configuring the BSP using the ENV tool, you can enable more on-board resources and implement more advanced functions.

### Quick Start

This BSP provides an MDK5 project for developers and supports the GCC development environment. The following takes the MDK5 development environment as an example to introduce how to run the system.

**Please note!!!**

Before performing the compilation work, please open the ENV tool in the BSP directory and execute the following command (this command is used to pull the necessary HAL library and CMSIS library, otherwise compilation cannot pass):

```bash
pkgs --update
```

#### Hardware Connection

The development board has separate debugging interfaces (SWD, LPUART1). Connect to the debugger as needed.

#### Compilation and Download

Double-click the project.uvprojx file to open the MDK5 project, compile and download the program to the development board.

> The project is configured to use CMSIS_DAP emulator to download the program by default. On the basis of connecting the development board through CMSIS_DAP, click the download button to download the program to the development board.

#### Running Results

After successfully downloading the program, the system will run automatically, and the LED will blink.

Connect the corresponding serial port of the development board to the PC, open the corresponding serial port (115200-8-1-N) in the terminal tool, and after resetting the device, you can see the output information of RT-Thread:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     5.2.2 build Oct 23 2025 18:41:53
 2006 - 2024 Copyright by RT-Thread team
msh >
```

### Advanced Usage

This BSP only enables the functions of GPIO and UART1 by default. If you need to use more advanced functions, you need to use the ENV tool to configure the BSP. The steps are as follows:

1. Open the env tool under the bsp directory.

2. Enter the `menuconfig` command to configure the project, save and exit after configuration.

3. Enter the `pkgs --update` command to update the software package.

4. Enter the `scons --target=mdk5` command to regenerate the project.

For more detailed introduction in this chapter, please refer to [STM32 Series BSP Peripheral Driver Usage Tutorial](../docs/STM32系列BSP外设驱动使用教程.md).

## Notes

- Debugging serial port is low-power UART1 mapping description

    PA9     ------> LPUART1_TX

    PA10    ------> LPUART1_RX

## Contact Information

Maintainer:

- [Pcb-yun](https://github.com/Pcb-yun)