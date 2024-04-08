# **NUCLEO-STM32H563ZI** BSP Introduction

[中文页](README_zh.md) |

## Introduction

This document records the execution instruction of the BSP (board support package) provided by the RT-Thread development team for the NUCLEO-STM32H563ZIT6 development board.

The document is covered in three parts:

- NUCLEO-STM32H563ZIT6 Board Resources Introduction
- Quickly Get Started
- Advanced Features

By reading the Quickly Get Started section developers can quickly get their hands on this BSP and run RT-Thread on the board. More advanced features will be introduced in the Advanced Features section to help developers take advantage of RT-Thread to drive more on-board resources.

## Board Resources Introduction

the ARM Cortex-M33 core. It operates at a maximum frequency of 250MHz and comes equipped with 2 MB Flash and 640 KB RAM. This development board offers abundant onboard resources, allowing for the full utilization of the STM32H563ZIT6 chip's performance capabilities.

The appearance of the development board is as shown in the following picture.

![board](images/board.png)

The mainly-used **on-board resources** are shown as follows:

- MCU: The STM32H563ZI is a high-performance microcontroller unit (MCU) featuring an Arm Cortex-M33 with TrustZone. The MCU is equipped with 2 MB Flash, 640 KB RAM, a 250 MHz CPU, and achieves 375 DMIPS (Dhrystone 2.1).
- Common features
  - STM32 microcontroller in an LQFP144 package
  - 3 user LEDs
  - 2 user and reset push-buttons
  - 32.768 kHz crystal oscillator
  - Board connectors:
    - SWD
    - ST Zio expansion connector including ARDUINO® Uno V3
    - ST morpho expansion connector
  - Flexible power-supply options: ST-LINK USB VBUS, USB connector, or external sources
  - On-board ST-LINK debugger/programmer with USB re-enumeration capability: mass storage, Virtual COM port, and debug port
  - Comprehensive free software libraries and examples available with the STM32Cube MCU Package
  - Support of a wide choice of Integrated Development Environments (IDEs) including IAR Embedded Workbench®, MDK-ARM, and STM32CubeIDE

#### For more details about this board, please refer to the [ST official documentation](https://www.st.com/en/evaluation-tools/nucleo-h563zi.html)

The hardware block diagram is as follows:

![hardware_block_diagram](images/hardware_block_diagram.png)

### Peripheral Condition

Each peripheral supporting condition for this BSP is as follows:

| **On-chip Peripheral Drivers**          | **Support** | **Remark** |
| --------------------------------------- | ----------- | ---------- |
| GPIO                                    | Support     |            |
| UART                                    | Support     | UART3      |
| USB to Serial (Onboard **STLINK-V3EC**) | Support     |            |
| PWM                                     | Support     |            |
| ADC                                     | Support     |            |

## User Manual

The user manual is divided into the following two sections:

- Quick Start

  This section is designed for beginners who are new to RT-Thread. By following simple steps, you can run the RT-Thread operating system on the development board and observe the experimental results.

- Advanced Usage

  This section is intended for developers who need to leverage more development board resources on the RT-Thread operating system. By using the ENV tool to configure the Board Support Package (BSP), you can enable additional onboard resources and implement more advanced functionalities.

### Quickly Get Started

This BSP provides MDK5 and IAR projects for developers. Also support GCC development environment. Here's an example of the MDK5 development environment, to introduce how to run the system.

#### Hardware Connection

Connect the development board to the PC using a Type-C data cable.

#### Compile And Download

Double-click the `project.uvprojx` file, to open the MDK5 project, compile and download the program to the board.

> By default, the project uses ST_LINK simulator to download the program, when the ST_LINK connects the board, clicking the download button can download the program to the board.

### Running Results

After the program is successfully downloaded, the system runs automatically. Observe the running results of the LED on the development board, the  LED1 will flash periodically.

Connect the corresponding serial port of the development board to the PC. Open the corresponding serial port in the terminal tool (115200-8-1-N). After resetting the device, you should be able to see the output information from RT-Thread.

```
 \ | /
- RT -     Thread Operating System
 / | \     5.0.1 build Aug 27 2023 20:47:55
 2006 - 2022 Copyright by RT-Thread team
do components initialization.
initialize rti_board_end:0 done
initialize rt_work_sys_workqueue_init:0 done
initialize finsh_system_init:0 done
msh >
```

### Advanced Features

This BSP only enables GPIO and serial port 1 by default. If need more advanced features, you need to configure the BSP with RT-Thread Env tools, as follows:

- Open the [Env](https://www.rt-thread.io/download.html?download=Env) tool under this BSP;

- Enter the `menuconfig` command to configure the project, then save and exit;

- Enter the `pkgs --update` command to update the packages;

- Enter the  `scons --target=mdk4/mdk5/iar` command to regenerate the project.

  

## Notes

- Debug the UART3 serial port with mapping details (refer to the configuration in STM32CubeMX for more details):

  ```
  PD8     ------> USART3_TX（T_VCP_TX）
  PD9     ------> USART3_RX（T_VCP_RX）
  ```

- It is recommended to use a relatively recent version of MDK. The setup for this project was done using MDK version 5.36.



## References:

1. [Download STM32H563-NUCLEO Schematic](https://www.st.com/resource/en/schematic_pack/mb1404-h563zi-c01-schematic.pdf)
2. [STM32H563 Official Introduction](https://www.st.com/en/microcontrollers-microprocessors/stm32h563zi.html)
3. [STM32H563-NUCLEO Development Board Manual](https://www.st.com/resource/en/user_manual/um3115-stm32h5-nucleo144-board-mb1404-stmicroelectronics.pdf)



## Maintained By

[yuanzihao](https://github.com/zihao-yuan/)  [y@yzh.email](mailto:y@yzh.email)
