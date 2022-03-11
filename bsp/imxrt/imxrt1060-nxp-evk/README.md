# NXP MIMXRT1060-EVK BSP Introduction

[中文页](README_zh.md) |

This document records the instruction of the BSP (board support package) that provided by the RT-Thread development team for the MIMXRT1060-EVK development board.

The document is covered in three parts:

- Resources Introduction
- Quickly Get Started
- Advanced Features

By reading the ***Quickly Get Started*** section developers can quickly get their hands on this BSP and run RT-Thread on the board. More advanced features will be introduced in the Advanced Features section to help developers take advantage of RT-Thread to drive more on-board resources.

## Resources Introduction

[![board](https://github.com/RT-Thread/rt-thread/raw/master/bsp/imxrt/imxrt1060-nxp-evk/figures/MIMXRT1060EVKB.jpg)](https://github.com/RT-Thread/rt-thread/blob/master/bsp/imxrt/imxrt1060-nxp-evk/figures/MIMXRT1060EVKB.jpg)

Features:

- MCU: MIMXRT1062DVL6A, 600MHz, 4096KB FLASH, 1024KB RAM
- External RAM: IS42S16160J-6BLI, 32MB
- External FLASH: S26KS512SDPBHI02, 64MB
- Common-used Peripherals:
  - LED: One, D18(Green)
  - Button: One
- Common-used Interfaces: USB 、SD Card、Ethernet、LCD, etc
- Debugging interface, standard JTAG/SWD

### For more details about these boards, please refer to [NXP Official Website](https://www.nxp.com/part/MIMXRT1060-EVK#/)





## Peripherals Condition

Each peripheral supporting condition for this BSP is as follows:

| **On-board Peripherals** | **Support** | **Remark**                            |
| ------------------------ | ----------- | ------------------------------------- |
| USB                      | √           |                                       |
| SPI Flash                | √           |                                       |
| Ethernet                 | √           |                                       |
| **On-chip Peripherals**  | **Support** | **Remark**                            |
| GPIO                     | √           | PA0, PA1... PK15 ---> PIN: 0, 1...176 |
| UART                     | √           | UART1                                 |
| SPI                      |             | Coming Soon                           |
| I2C                      |             | Coming Soon                           |
| SDIO                     |             | Coming Soon                           |
| RTC                      |             | Coming Soon                           |
| PWM                      |             | Coming Soon                           |
| USB Device               |             | Coming Soon                           |
| USB Host                 |             | Coming Soon                           |
| IWG                      |             | Coming Soon                           |
| **Expansion Module**     | **Support** | **Remark**                            |
| LVGL                     | √           |                                       |

## Quickly Get Started

This BSP provides MDK4, MDK5, and IAR projects for developers and it supports the GCC development environment. Here's an example of the MDK5 development environment, to introduce how to run the system.

#### Hardware Connection

Use a cable to connect the development board to the PC and turn on the power switch.

### Compile and Download

Double-click the `project.uvprojx` file to open the MDK5 project, compile and download the program to the development board.

> The project defaults to use the CMSIS-DAP emulator to download the program, and as we're connecting the development board via USB, click the Download button can directly download the program to the development board

#### Running Results

After the program is successfully downloaded, the system runs automatically. Observe the running results of the LED on the development board, the LED will light in 1Hz.

Connect the corresponding serial port of the development board to the PC, and when the corresponding serial port ( 115200-8-1-N) is opened in the terminal tool, the output information of RT-Thread can be seen when the device is reset:

```
 \ | /
- RT -     Thread Operating System
 / | \     4.1.0 build Mar 10 2022 18:07:41
 2006 - 2022 Copyright by RT-Thread team
msh >
```

## **Advanced Features**

This BSP only enables GPIO and UART1 by default. If you need more advanced features such as SD Card, Flash, or you need to configure the BSP with RT-Thread homegrown [ENV tool](https://www.rt-thread.io/download.html?download=Env), as follows:

1. Open the ENV tool under the specific BSP folder;
2. Enter `menuconfig` command to configure the project, then save and exit;
3. Enter `pkgs --update` command to update the package;
4. Enter `scons --target=mdk4/mdk5/iar` command to regenerate the project.

More details about NXP MIMXRT1060-EVK , check out [Here](https://github.com/RT-Thread/rt-thread/blob/master/bsp/imxrt/docs/IMXRT%E7%B3%BB%E5%88%97BSP%E5%A4%96%E8%AE%BE%E9%A9%B1%E5%8A%A8%E4%BD%BF%E7%94%A8%E6%95%99%E7%A8%8B.md). 

