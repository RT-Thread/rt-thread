
**English** | [中文](README.md)

# STM32H750-artpi Development Board BSP Guide

## Introduction

Welcome to the realm of innovation with the STM32H7S78-DK development board. This document serves as your guide to unleash the full potential of the Board Support Package (BSP) tailored for this cutting-edge hardware.

What's Inside? Let's embark on an exciting journey through this guide, which covers:

- Introduction to the wealth of resources onboard.
- Quick Start for rapid deployment.
- Advanced Usage for harnessing the board's full capabilities.

By reading the Quick Start section, developers can quickly get started with this BSP and run RT-Thread on the development board. In the Advanced Usage Guide section, more advanced features will be introduced to help developers utilize RT-Thread to drive more onboard resources.

## Development Board Introduction

Development Board Introduction The STM32H7S78-DK is a development board based on the ARM Cortex-M7 core, with a maximum main frequency of 600MHz. This development board has abundant onboard resources, allowing for a comprehensive evaluation of the performance of the STM32H7S7 chip.

Take a look at the development board's sleek design:

![board](figures/board.jpg)

Explore its features:

- MCU: STM32H7S7, running at 550MHz with 64KB FLASH and 456KB RAM.
- Interfaces: From USB to serial and USB OTG.
- Debugging: Seamlessly debug with the standard ST-LINK V3.

## Peripheral Playground

The current support status of peripherals in this BSP is as follows:

| **Onboard peripherals** | Support     | Remark       |
| ----------------------- | ----------- | ------------ |
| LED                     | YES         | One green LE |
| **On-chip peripherals** | **Support** | **Remark**   |
| GPIO                    | YES         |              |
| UART                    | YES         | UART4        |
| SPI                     | YES         | SPI          |

## Instructions for Use 

Instructions for use are divided into the following two sections:

**Quick Start**

This section provides instructions for newcomers to RT-Thread, following simple steps to run the RT-Thread operating system on this development board and observe experimental results.

**Advanced Usage**

This section is for developers who need to use more development board resources on the RT-Thread operating system. By configuring the BSP using the ENV tool, more onboard resources can be enabled to implement more advanced features.

### Quick Start

This BSP provides an MDK5 project for developers and supports the GCC development environment. Below is an example using the MDK5 development environment to start the system.

#### Hardware Connection 

Connect the ST-Link port of the development board to the PC using a data cable and ensure that the power supply jumpers on the board are properly configured.

#### Compilation and Download

Double-click the project.uvprojx file to open the MDK5 project, compile it, and download the program to the development board.

> The project default configuration uses the ST-LINK emulator to download the program. After connecting the development board via ST-LINK, click the download button to download the program to the development board.

#### Running Result

After successful program download, the system will run automatically, and the LED will blink.

Connect the corresponding serial port of the development board to the PC, open the terminal tool, and reset the device. You will see RT-Thread output information:

```
[I/board] System Clock information
[I/board] SYSCLK_Frequency = 550000000
[I/board] HCLK_Frequency   = 275000000
[I/board] PCLK1_Frequency  = 137500000
[I/board] PCLK2_Frequency  = 137500000
[I/board] XSPI1_Frequency  = 200000000
[I/board] XSPI2_Frequency  = 200000000

 \ | /
- RT -     Thread Operating System
 / | \     5.1.0 build Apr 10 2024 14:32:06
 2006 - 2024 Copyright by RT-Thread team
msh >
```



### Advanced Usage 

By default, this BSP only enables the functions of GPIO and UART4. If more advanced features are required, ENV tools need to be used to configure BSP, as follows:

1. Open the env tool under bsp.
2. Enter the `menuconfig` command to configure the project, save and exit after configuration.
3. Enter the `pkgs --update` command to update the software package.
4. Enter the `scons --target=mdk4/mdk5/iar` command to regenerate the project.

## Pro Tips

- Mapping of debug serial port to USART4:

  PD0 ------> USART4_RX

  PD1 ------> USART4_TX

- Bootloader Damage or Loss

  In case the board does not boot after program download, please first check if the bootloader is not burned or is lost due to erasure of internal flash. If the bootloader is missing, it needs to be rewritten by downloading the h7s7_disco_bootloader.bin file under the directory to the chip's internal flash using the STM32CubeProgrammer tool (ST official download tool) after connecting the development board to the PC. Then disconnect and manually reset the MCU, and the external jump should be executed at this time.

  This bin file is generated from the STM32H7RS SDK internal example project. If the external Flash model is modified, you can refer to ST's example for modification.

## Contact Info

RT-Thread Club: https://club.rt-thread.io/

## Code Contribution

 This project is still in its initial stage, and the BSP is not yet perfect. If you are interested in this project and have some interesting projects to share with us, you are welcome to contribute code.