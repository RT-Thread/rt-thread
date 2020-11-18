# STM32F401 Nucleo-64 BSP (Board Support Package) Execution Instruction

[中文页](README_zh.md) |

## Introduction

This document records the execution instruction of the BSP (board support package) provided by the RT-Thread development team for the STM32F401 Nucleo-64 development board.

The document is covered in three parts:

- STM32F401 Nucleo-64 Board Resources Introduction
- Quickly Get Started
- Advanced Features

By reading the Quickly Get Started section developers can quickly get their hands on this BSP and run RT-Thread on the board. More advanced features will be introduced in the Advanced Features section to help developers take advantage of RT-Thread to drive more on-board resources.

## Board Resources Introduction

The STM32 Nucleo-64 is a development board based on STM32F401RE, which contains a Cortex-M4 core. The maximum main frequency is 84 MHz, and it has a wealth of on-board resources that can take full advantage of the STM32F401RE's chip performance.

![board.jpg](https://github.com/RT-Thread/rt-thread/blob/master/bsp/stm32/stm32f401-st-nucleo/figures/board.jpg?raw=true)



The mainly-used **on-board resources** are shown as follows:

- MCU: STM32F401RET6
- Main Frequency: 84MHz
- Memory: 512KB FLASH , 96KB RAM
- Common-used peripherals:
  - 3 LEDs: USB communication (LD1), user LED (LD2), power LED (LD3) 
  - 2 Buttons: USER and RESET 
- Common-used interface: USB, Arduino Uno, and ST morpho
- Debug interface: ST-LINK/V2-1 

For more details about this board, please refer to the ST official documentation: [STM32 Nucleo-64 development board with STM32F401RE MCU](https://www.st.com/zh/evaluation-tools/nucleo-f401re.html)

## Peripheral Condition

Each peripheral supporting condition for this BSP is as follows:

| **On-chip Peripheral Drivers** | **Support** | **Remark**                          |
| ------------------------------ | ----------- | ----------------------------------- |
| GPIO                           | Support     | PA0, PA1... PH1 ---> PIN: 0, 1...63 |
| UART                           | Support     | UART2                               |
| SPI                            | Support     | SPI1                                |

## Execution Instruction

### Quickly Get Started

This BSP provides MDK5 and IAR projects for developers. Also support GCC development environment Here's an example of the MDK5 development environment, to introduce how to run the system.

#### Hardware Connection

Use a Type-A to Mini-B cable to connect the development board to the PC and turn on the power switch. The red LED LD3 (PWR) and LD1 (COM) will lit.

#### Compile And Download

Double-click the project.uvprojx file, to open the MDK5 project, compile and download the program to the board.

> By default, the project uses ST_LINK simulator to download the program, when the ST_LINK connects the board, clicking the download button can download the program to the board.

### Running Results

After the program is successfully downloaded, the system runs automatically. Observe the running results of the LED on the development board, the red LD3 and LD1 will lit all the time, green LD2 will flash periodically.

The USB virtual COM port connects to serial port 2 by default, and when the corresponding serial port (115200-8-1-N) is opened in the terminal tool, the output information of RT-Thread can be seen when the device is reset:

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.1 build Mar  7 2019
 2006 - 2019 Copyright by rt-thread team
msh >
```

### Advanced Features

This BSP only enables GPIO and serial port 2 by default. If need more advanced features, you need to configure the BSP with RT-Thread Env tools, as follows:

- Open the [Env](https://www.rt-thread.io/download.html?download=Env) tool under this BSP;

- Enter the `menuconfig` command to configure the project, then save and exit;

- Enter the `pkgs --update` command to update the packages;

- Enter the  `scons --target=mdk4/mdk5/iar` command to regenerate the project.

  

## Notes

According to the pin number specification, in the new stm32 bsp framework, the GPIO driver is managed in a sequential numbering manner.

## Notes

The pin serial number corresponds to the pin name as shown in the following table:

| STM32 Pin Name | Pin Sequence Number |
| -------------- | ------------------- |
| PA0 - PA15     | 0 - 15              |
| PB0 - PB15     | 16 - 31             |
| PC0 - PC15     | 32 - 47             |
| PD0 - ...      | 48 - ...            |

