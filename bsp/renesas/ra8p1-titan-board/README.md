# Titan Board BSP Description

**English** | [**Chinese**](./README_zh.md)

## Introduction

This document provides the BSP (Board Support Package) description for the RT-Thread **Titan Board** development board. By following the Quick Start Guide, developers can quickly get started with this BSP and run RT-Thread on the development board.

The main contents include:

- Introduction to the development board
- BSP Quick Start Guide

## Development Board Introduction

The Titan Board is an RT-Thread development board based on Renesas **Cortex-M85 + Cortex-M33 dual-core architecture R7KA8P1** MCU. It provides engineers a flexible and comprehensive development platform, enabling deeper exploration in embedded IoT development.

Titan Board integrates the **RA8P1** chip featuring a **1GHz Arm® Cortex®-M85** core and a **250MHz Arm® Cortex®-M33** core. The RA8P1 series is Renesas’ first 32-bit AI-accelerated MCU featuring high-performance **Arm® Cortex®-M85 (CM85)** with **Helium™ vector extensions**, and an integrated **Ethos™-U55 NPU**. It delivers **256 GOPS AI performance**, over **7300 CoreMarks**, and advanced AI capabilities supporting voice, vision, and real-time analytics.

The front view of the development board is shown below:

![big](figures/big.png)

Common **on-board resources** are as follows:

![titan_board_hw_resource](figures/titan_board_hw_resource.png)

## Peripheral Support

The current peripheral support status in this BSP is as follows:

| **On-chip Peripheral** | **Support Status** | **Component**               | **Support Status** |
| ---------------------- | ------------------ | --------------------------- | ------------------ |
| UART                   | Supported          | LWIP                        | Supported          |
| GPIO                   | Supported          | TCP/UDP                     | Supported          |
| HWTIMER                | Supported          | MQTT                        | Supported          |
| I2C                    | Supported          | TFTP                        | Supported          |
| WDT                    | Supported          | Telnet                      | Supported          |
| RTC                    | Supported          | **Multicore Communication** | **Support Status** |
| ADC                    | Supported          | RPMsg-Lite                  | Supported          |
| DAC                    | Supported          | **Extended peripheral**     | **Support Status** |
| SPI                    | Supported          | MIPI CSI Camera             | Supported          |
| RS485                  | Supported          | CEU Camera                  | Supported          |
| CANFD                  | Supported          | RGB LCD                     | Supported          |
| SDHI                   | Supported          | CYW43438 WIFI               | Supported          |
| USB                    | Supported          |                             |                    |
| HyperRAM               | Supported          |                             |                    |
| HyperFlash             | Supported          |                             |                    |

> **Note:** The repository provides a minimal system by default. To enable or add additional peripherals, please refer to:
>  Peripheral Driver Usage Guide (rt-thread.org)

## User Guide

The user guide is divided into the following two sections:

- **Quick Start**

  This section is intended for beginners who are just getting started with RT-Thread. By following simple steps, you can run the RT-Thread operating system on this development board and observe the experimental results.

- **Advanced Usage**

  This section is intended for developers who need to use more board resources on the RT-Thread operating system. By using the FSP and RT-Thread Settings tools to configure the project, more on-board resources can be enabled to achieve advanced functionality.

### FSP Version Information

This BSP uses **FSP 6.2.0**. You must download and install it for peripheral development.

- Download link: [rasc-6.2.0](https://github.com/renesas/fsp/releases/download/v6.2.0/setup_fsp_v6_2_0_rasc_v2025-10.exe)
- Note: The BSP provides minimal configuration by default. To enable other peripherals, refer to: [Peripheral Driver Usage Guide](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/tutorial/make-bsp/renesas-ra/RA系列BSP外设驱动使用教程)

### Quick Start

This BSP can be directly imported into **RT-Thread Studio v2.3.0**. The following steps demonstrate how to run the system using RT-Thread Studio.

### **Install Toolchains**

1. Install the compiler toolchain:

![image-20251127164450247](figures/image-20251127164450247.png)

2. Install debugging tools:

Download **J-Link v8.48** and **PyOCD 0.2.9**.

![image-20251127164534568](figures/image-20251127164534568.png)

### **Create a Project**

1. Click **File → Import**.

![image-20251127164859503](figures/image-20251127164859503.png)

2. Select **Import RT-Thread BSP**, then click **Next**.

![image-20251127164952040](figures/image-20251127164952040.png)

3. Select the BSP root directory and fill in project information, then click **Finish**.

![image-20251127165319591](figures/image-20251127165319591.png)

4. The project based on the BSP is created.

![image-20251127165406340](figures/image-20251127165406340.png)

### **Configure Debug/Download Settings**

> **Note: Sometimes you may need to modify the settings twice for them to take effect.**

Modify the debugger configuration in the **Debugger** tab.

![image-20251127165957537](figures/image-20251127165957537.png)

In the **Download** tab, change the download method to **Flash Hex File**, then click **OK**.

![image-20251127170436152](figures/image-20251127170436152.png)

![image-20251127171037225](figures/image-20251127171037225.png)

**Hardware Connection**

Use a USB cable to connect the development board to the PC, and use the DAP-Link interface to download and debug the program.

**Build and Download**

![image-20251127165554294](figures/image-20251127165554294.png)

**View Running Results**

After the program is successfully downloaded, the system will automatically run and print system information.

Connect the development board’s corresponding serial port to the PC, open the corresponding serial port in a terminal tool (115200-8-1-N), and reset the device. You will then see the RT-Thread output information. Enter the `help` command to view the commands supported in the system.

```bash
 \ | /
- RT -     Thread Operating System
 / | \     5.3.0 build Nov 27 2025 13:12:46
 2006 - 2024 Copyright by RT-Thread team

==================================================
Hello, Titan Board!
==================================================
msh >help
RT-Thread shell commands:
backtrace        - print backtrace of a thread
clear            - clear the terminal screen
version          - show RT-Thread version information
list             - list objects
help             - RT-Thread shell help
ps               - List threads in the system
free             - Show the memory usage in the system
pin              - pin [option]
reboot           - Reboot System

msh >

```

**Application Entry Function**

The entry function of the application layer is located in **src\hal_entry.c** within `void hal_entry(void)`. User-created source files can be placed directly in the **src** directory.

```c
#include <rtthread.h>
#include "hal_data.h"
#include <rtdevice.h>
#include <board.h>

#define LED_PIN     BSP_IO_PORT_00_PIN_12 /* Onboard LED pins */

void hal_entry(void)
{
    rt_kprintf("\n==================================================\n");
    rt_kprintf("Hello, Titan Board!\n");
    rt_kprintf("==================================================\n");

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(1000);
    }
}
```

### Advanced Usage

**Resources and Documentation**

- [Development Board Official Homepage](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/hw-board/ra8p1-titan-board/ra8p1-titan-board)
- [Development Board Datasheet](https://www.renesas.cn/zh/document/dst/25574255?r=25574019)
- [Development Board Hardware Manual](https://www.renesas.cn/zh/document/mah/25574257?r=25574019)
- [Dualcore Development Guide](https://www.renesas.cn/zh/document/apn/developing-ra8-dual-core-mcu?r=25574019)
- [Renesas RA8P1 Group](https://www.renesas.cn/zh/document/fly/renesas-ra8p1-group?r=25574019)

**FSP Configuration**

If you need to modify the Renesas BSP peripheral configuration or add new peripheral interfaces, you will need to use the Renesas [Flexible Software Package (FSP)](https://www.renesas.cn/zh/software-tool/flexible-software-package-fsp?queryID=c20a16b5f7f3866713b62c7acb07f2fc) configuration tool. Please make sure to follow the steps below for configuration. If you encounter any issues, you may ask questions in the [RT-Thread Community Forum](https://club.rt-thread.org/).

1. [Download Flexible Software Package (FSP) | Renesas](https://github.com/renesas/fsp/releases/download/v6.2.0/setup_fsp_v6_2_0_rasc_v2025-10.exe), please use **FSP version 6.2.0**
2. Refer to the documentation: [Configuring Peripheral Drivers Using FSP for the RA Series](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/tutorial/make-bsp/renesas-ra/RA系列使用FSP配置外设驱动?id=ra系列使用-fsp-配置外设驱动).

- **Configure development by importing FSP:**

Users can locate the `configuration.xml` file in the project and import it into FSP to start configuration:

Select **File → Open** at the top-left corner to open the configuration file.

![image-20251030163423452](figures/image-20251030163423452.png)

* **Generate FSP Code:**

![image-20251030163707813](figures/image-20251030163707813.png)

**RT-Thread Settings**

In **RT-Thread Settings**, you can configure the RT-Thread kernel, components, software packages, and Titan Board device drivers.

![image-20250819173700386](figures/image-20250819173700386.png)

## Contact Information

If you have any thoughts or suggestions during usage, please feel free to contact us via the [RT-Thread Community Forum](https://club.rt-thread.org/).

## Contribute Code

If you're interested in Titan Board and have some exciting projects you'd like to share, we welcome code contributions. Please refer to [How to Contribute to RT-Thread Code](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/development-guide/github/github).