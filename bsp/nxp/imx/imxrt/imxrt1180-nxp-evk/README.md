# i.MX RT1180 EVK Board BSP Guide

## Introduction

This document provides an initial BSP (Board Support Package) guide for the NXP i.MX RT1180 EVK development board.

The BSP currently supports independent compilation for CM33 and CM7, with CM33 as the primary core and CM7 as the secondary core. It is also possible to use the MCUXpresso Secure Provisioning Tool to generate a bootable dual-core image.

Main content includes:

- Development board resource overview
- BSP quick start guide
- Advanced usage instructions

By following the quick start guide, developers can quickly get this BSP running and bring RT-Thread up on the board. The advanced usage section introduces more features and helps developers use additional onboard resources with RT-Thread.

## Development Board Overview

The dual-core i.MX RT1180 combines an 800 MHz Cortex-M7 core with a 240 MHz Arm Cortex-M33 core, offering strong security and extensive networking capabilities, including dual gigabit Ethernet and multiple industrial communication interfaces. The i.MX RT1180 MCU supports a wide temperature range, making it suitable for industrial control, motor drive, and other applications.

## Peripheral Support

This BSP currently provides peripheral support:

| **Onboard Peripheral** | **Support Status** | **Notes** |
| :--------------------- | :---------------: | :-------- |
| QSPI Flash XIP         | Supported         |           |
| Flash driver(flexspi)  | supported         |           |
| CherryUSB              | Supported         |           |
| NETC                   | Supported         |           |
| EtherCAT               | Supported         |           |
| **On-chip Peripheral** | **Support Status** | **Notes** |
| Multicore kick-off     | Supported         |           |
| Rpmsg-lite             | Supported         |           |
| GPIO                   | supported         |           |
| UART                   | Supported         |           |
| SPI                    | Not yet supported |           |
| I2C                    | supported         |           |
| ADC                    | supported         |           |
| Timer                  | supported         |           |
| SDIO                   | Not yet supported |           |
| RTC                    | Not yet supported |           |
| PWM                    | Not yet supported |           |
| CAN                    | Not yet supported |           |

## Usage Instructions

Usage instructions are divided into two sections:

- Quick Start

  This section is aimed at beginners new to RT-Thread. Following the simple steps here will get the RT-Thread operating system running on the development board.

- Advanced Usage

  This section is for developers who want to use more board resources with RT-Thread. Using the ENV tool to configure the BSP enables additional onboard features and more advanced functionality.

### Quick Start

This BSP provides MDK5, IAR, and GCC projects. The following example uses the IAR development environment to describe how to run the system.

**Please note:**

Before compiling, open the ENV tool and run the following command to pull required packages (otherwise compilation may fail):

```bash
pkgs --update
```

Generate the IAR project:

```bash
scons --target=iar
```

Generate the KEIL MDK5 project:

```bash
scons --target=mdk5
```

Or compile the GCC project directly:

```bash
scons -j8
```

#### Hardware Connection

Connect the development board to the PC using a data cable, then turn on the power switch.

#### Build and Download

Double-click the `project.eww` file to open the IAR project, then build and download the program to the development board.

> The project is configured by default to use CMSIS-DAP for downloading. With CMSIS-DAP connected to the board, click the download button to program the board.

#### Run Result

After the program is downloaded successfully, the system starts automatically.

Connect the board's serial port to the PC and open the corresponding serial port in a terminal tool with settings `115200-8-1-N`. After resetting the device, you should see RT-Thread output like:

```
 \ | /
- RT -     Thread Operating System
 / | \     5.2.2 build May 15 2026 17:19:35
 2006 - 2024 Copyright by RT-Thread team
```

### Advanced Usage

This BSP enables only UART1 by default. To use additional advanced peripherals, configure the BSP with the ENV tool as follows:

1. Open the env tool in the BSP directory.
2. Enter `menuconfig` to configure the project, then save and exit.
3. Run `pkgs --update` to update the packages.
4. Run `scons --target=mdk5` or `scons --target=iar` to regenerate the project.

## Notes

None at this time.

## Contact

Maintainer:
