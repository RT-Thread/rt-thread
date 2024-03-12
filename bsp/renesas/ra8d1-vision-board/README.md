# Vision Board BSP Introduction

**English** | [**中文**](./README_zh.md)

## Overview

The Vision-Board is introduced by RT-Thread, in collaboration with Renesas Electronics, the vision board is based on the Renesas Cortex-M85 architecture RA8D1 chip, to provide engineers with a flexible and comprehensive development platform, empowering developers to gain deeper experiences in the field of machine vision.

[![img](https://github.com/RT-Thread/rt-thread/raw/master/bsp/renesas/ra8d1-vision-board/docs/picture/logo.png)](https://github.com/RT-Thread/rt-thread/blob/master/bsp/renesas/ra8d1-vision-board/docs/picture/logo.png)

## Hardware Introduction

The Vision-Board comes equipped with various onboard resources, including:

![img](https://cdn-images-1.medium.com/max/1250/1*yuc1gyHjYpg7yd7x_8ICAg.png)



## Peripheral Support

The BSP currently supports several peripherals as listed below:

| On-Chip Peripheral | Support Status | Remarks                              |
| ------------------ | -------------- | ------------------------------------ |
| UART               | Supported      | UART9 is the default log output port |
| GPIO               | Supported      |                                      |
| USB                | Supported      | TinyUSB                              |
| Camera             | Supported      | ov2640, ov7725, ov7670...            |
| SDHC               | Supported      | 1-bit, 4-bit                         |
| ADC                | Supported      |                                      |
| DAC                | Supported      |                                      |
| SPI                | Supported      |                                      |
| PWM                | Supported      |                                      |
| RTC                | Supported      |                                      |
| FLASH              | Supported      |                                      |
| WDT                | Supported      |                                      |
| I2C                | Supported      |                                      |
| Wi-Fi              | Supported      | RW007                                |

- Note: The repository initially contains the minimal system. Additional peripherals can be added/enabled by referring to the [Peripheral Driver Usage Tutorial](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/tutorial/make-bsp/renesas-ra/RA系列BSP外设驱动使用教程).

## Template Project Description



[![img](https://github.com/RT-Thread/rt-thread/raw/master/bsp/renesas/ra8d1-vision-board/docs/picture/1.png)](https://github.com/RT-Thread/rt-thread/blob/master/bsp/renesas/ra8d1-vision-board/docs/picture/1.png)

[![img](https://github.com/RT-Thread/rt-thread/raw/master/bsp/renesas/ra8d1-vision-board/docs/picture/2.png)](https://github.com/RT-Thread/rt-thread/blob/master/bsp/renesas/ra8d1-vision-board/docs/picture/2.png)

The RGB-LED, as shown above, is a common anode LED. The cathodes are connected to the microcontroller pins. For instance, the blue LED corresponds to pin P102. The LED can be lit by setting the microcontroller pin to a low level and turned off by setting it to a high level.

## Software Introduction

The source code for flashing the LED is located in `ra8d1-vision-board/src/hal_entry.c`. It defines a macro `LED_PIN` representing the LED pin number, corresponding to `BSP_IO_PORT_01_PIN_02` (P102). 

```
#define LED_PIN    BSP_IO_PORT_01_PIN_02 /* Onboard LED pins */
```

In the `hal_entry` function, this pin is configured as an output. The LED is toggled periodically (every 500 milliseconds) in the while loop.

```
void hal_entry(void)
{
    rt_kprintf("\nHello RT-Thread!\n");

    while (1)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
```



## Usage Instructions

Usage instructions are divided into two sections:

- Quick Start
  - This section provides instructions for newcomers to RT-Thread to run the RT-Thread operating system on this development board and observe experimental results.
- Advanced Usage
  - This section is for developers who need to utilize more development board resources on the RT-Thread operating system. It guides users on enabling more onboard resources using the ENV tool to achieve more advanced functionality.

### Supported Compilation Platforms

- armclang (AC6 V6.19)
- LLVM (V16/17) [ARM-software/LLVM-embedded-toolchain-for-Arm (github.com)](https://github.com/ARM-software/LLVM-embedded-toolchain-for-Arm/releases/tag/release-17.0.1)

## FSP Version Introduction

This BSP uses FSP 5.1.0 version for peripheral-related development. Users need to download and install it. Additionally, instructions for enabling additional peripherals are provided in the [Peripheral Driver Usage Tutorial](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/tutorial/make-bsp/renesas-ra/RA系列BSP外设驱动使用教程).



### Quick Start

#### 1. Compiling with MDK:

This BSP provides an MDK5 project. Compile and download the program using the MDK5 development environment.

**Compile and Download**

- Compile: Double-click the project.uvprojx file to open the MDK5 project and compile the program.
- Download: Click the Debug button in MDK to download and debug."



#### 2. Compiling with LLVM

Open the current BSP using the ENV tool to set the toolchain and its corresponding path. Then, execute the `scons` command to compile.

```
set RTT_CC=llvm-arm
set RTT_EXEC_PATH=D:\Progrem\LLVMEmbeddedToolchainForArm-17.0.1-Windows-x86_64\bin
```

execute the `scons` command to compile.

```
scons
```

**Observing the Program Execution**

Once the program is downloaded successfully, the system will initiate automatically, displaying system information.

Connect the development board's respective serial port to the PC. Launch the terminal tool and configure the serial port settings accordingly (115200-8-1-N). Upon resetting the device, you'll observe output information from RT-Thread. To explore the system's supported commands, enter the "help" command.

```
[D/main] sdram init success, mapped at 0x68000000, size is 33554432 bytes, data width is 16

 \ | /
- RT -     Thread Operating System
 / | \     5.1.0 build Mar  5 2024 13:57:23
 2006 - 2024 Copyright by RT-Thread team

Hello RT-Thread!
msh >
msh >
```



### Advanced Usage

**Resources and Documentation**

- [Official Development Board Website](https://www.renesas.com/us/en/products/microcontrollers-microprocessors/ra-cortex-m-mcus/ek-ra8d1-evaluation-kit-ra8d1-mcu-group)
- [Development Board User Manual](https://www.renesas.cn/cn/zh/document/mat/ek-ra8d1-v1-users-manual?r=25452351)

**ENV Configuration**

- How to use the ENV tool: [RT-Thread ENV Tool User Manual](https://www.rt-thread.io/document/site/programming-manual/env/env/)

By default, this BSP only enables UART9 functionality. If you require more advanced features such as components, software packages, etc., you'll need to configure them using the ENV tool.

The steps are as follows:

1. Open the ENV tool in the bsp directory.
2. Enter the "menuconfig" command to configure the project. Once configured, save and exit.
3. Use the "pkgs --update" command to update software packages.
4. Use the "scons --target=mdk5" command to regenerate the project.

***FSP Configuration**

- How to use FSP: [Configuring Peripheral Drivers Using FSP for RA Series](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/tutorial/make-bsp/renesas-ra/RA系列使用FSP配置外设驱动?id=ra系列使用-fsp-配置外设驱动)

The BSP repository currently enables the minimum configuration by default. Users can enable ENV peripheral configurations through the following steps:

1. Open the ENV tool in the bsp directory and generate an MDK project using the `scons --target=mdk5'`Command.
2. Open the `project.uvprojx` file in the bsp directory. Navigate to the `Software Components"`configuration in the top navigation bar. Open the configuration button next to `RA Configuration` under `Flex Software`. This action will automatically detect the installed FSP version on your computer. After selecting the specified version, enter FSP.

[![img](https://github.com/RT-Thread/rt-thread/raw/master/bsp/renesas/docs/figures/mdk_rasc.png)](https://github.com/RT-Thread/rt-thread/blob/master/bsp/renesas/docs/figures/mdk_rasc.png)

3. Inside FSP, you'll find some pre-configured peripherals. Click the `Generate Project Content` button to generate the required driver files.

1. [![img](https://github.com/RT-Thread/rt-thread/raw/master/bsp/renesas/docs/figures/fsp_configure.png)](https://github.com/RT-Thread/rt-thread/blob/master/bsp/renesas/docs/figures/fsp_configure.png)
   4. Return to ENV, save and exit after enabling the required peripheral configurations.



## Contact Information

If you have any ideas or suggestions during usage, we encourage you to contact us via the [RT-Thread Community Forum](https://club.rt-thread.io/).

## SDK Repository

This is the SDK repository for Vision Board: [sdk-bsp-ra8d1-vision-board](https://github.com/RT-Thread-Studio/sdk-bsp-ra8d1-vision-board). This repository includes peripheral drivers and a variety of sample projects. If you'd like to experience open-source examples provided by the official website/community, please visit this repository for development. The RT-Thread main repository only maintains the latest driver-related code.

## Code Contributions

If you're interested in Vision Board and have some exciting projects to share with the community, wlecome any contributions. Please refer to [How to Contribute to RT-Thread Code](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/development-guide/github/github).