# STM32N657-st-nucleo Board BSP Introduction

[中文](README_zh.md)

## Introduction

This document describes the BSP (Board Support Package) provided by tyustli for the STM32N657-st-nucleo development board.

The main contents are as follows:

- Development board resources
- BSP quick start
- Advanced usage

By reading the Quick Start section, developers can quickly get started with this BSP and run RT-Thread on the development board. The Advanced Usage section introduces more advanced features to help developers use RT-Thread to drive more onboard resources.

## Development Board Introduction

The STM32N657 is a development board from ST based on the ARM Cortex-M55 core, with a maximum operating frequency of 800 MHz. The board provides abundant onboard resources to fully utilize the performance of the STM32N657 chip.

The development board is shown below:

![board](figures/board.jpg)

The main **onboard resources** are as follows:

- MCU: STM32N657, 800 MHz, with built-in 32 KB instruction cache (ICACHE) and 32 KB data cache (DCACHE)
  - RAM: 4.2 MB of contiguous SRAM (divided into multiple memory groups) and 8 KB of backup SRAM (operating in VBAT mode)
  - Accelerator: 1 GHz ST Neural-ART accelerator, providing 600 Gops
  - GPU: Neo-Chrom GPU
- Common interfaces: USB-to-UART, Ethernet, Arduino, and others
- Onboard ST-LINK (ST-LINK/V2-1, STLINK-V3E, or STLINK-V3EC) debugger/programmer, supporting USB re-enumeration as mass storage, virtual COM port, and debug port

For more information about the development board, see the ST [STM32N657](https://www.st.com/en/evaluation-tools/nucleo-n657x0-q.html) page.

## Peripheral Support

The current peripheral support status of this BSP is as follows:

| **Onboard peripheral** | **Support status** | **Notes** |
| :--------------------- | :----------------: | :-------- |
| USB-to-UART            | Supported          |           |
| **On-chip peripheral** | **Support status** | **Notes** |
| GPIO                   | Supported          |           |
| UART                   | Supported          | UART1     |
| SPI                    | Supported          |           |
| PWM                    | Supported          |           |
| TIM                    | Supported          |           |

## Usage Instructions

The usage instructions are divided into the following sections:

- STM32N657 startup process

  This section describes the STM32N657 startup process.

- Configure environment variables for signing/programming tools

  This section configures the environment variables required for signing and programming firmware in the subsequent steps.

- Quick start

  This section is intended for developers who are new to RT-Thread. By following the simple steps, you can run the RT-Thread operating system on the development board and see the results.

- Advanced usage

  This section is intended for developers who need to use more development board resources with the RT-Thread operating system. More onboard resources can be enabled through BSP configuration with the ENV tool to implement additional advanced features.

### STM32N657 Startup Process

The STM32N6 is ST's first MCU with an NPU. It contains only a small ROM for the first boot stage, so user code must be stored in external Flash or booted through a USB or U(S)ART interface.

There are three STM32N6 boot modes. This BSP uses the third mode:

#### FSBL

FSBL stands for First Stage Boot Loader. After power-on, the on-chip BootROM executes first. It then executes the FSBL at the corresponding address according to the boot options and address. The example below shows the boot process from external Flash.

![image-20260911113129450](figures/image-20260911113129450.png)

As shown above, the system startup process is as follows:

1. After BootROM starts, it verifies the FSBL header. The dark yellow area in the figure contains the 1024-byte header information. The script provided by ST can be used to sign the FSBL; the FSBL must be signed or it cannot start correctly. After verification succeeds, BootROM copies the FSBL program to internal SRAM2 at `0x34180000`, then jumps the PC to that address to begin executing the FSBL.

2. The FSBL begins execution.

#### FSBL + Load & Run

The application can be debugged in internal SRAM during development. After development is complete, it can be downloaded to external Flash through an external loader.

![image-20260911113257650](figures/image-20260911113257650.png)

As shown above, the system startup process is as follows:

1. As with FSBL execution, BootROM starts first, verifies the FSBL, copies it to SRAM, and jumps to the FSBL.

2. The FSBL begins execution, then copies the complete application to internal SRAM, including data and code. It then jumps to the application code.

3. The application code begins execution.

#### FSBL + XiP (Execute in Place)

![image-20260911113738785](figures/image-20260911113738785.png)

As shown above, the system startup process is as follows:

1. BootROM begins execution. As in the first mode, after verifying the FSBL, it copies the FSBL to SRAM.

2. The FSBL begins execution and configures the external Flash for XiP mode. After the FSBL completes, the PC jumps to the first instruction of the application in external Flash.

3. The application begins execution.

### Configure Environment Variables for Signing/Programming Tools

The following instructions use Windows as an example. Three environment variables need to be configured:

- Signing tool

- Programming tool

- Programming algorithm

All three tools can be obtained from `STM32CubeIDE_2.1.1`. First, configure the signing and programming tools:

![image-20260911110923343](figures/image-20260911110923343.png)

The tools numbered 2 and 3 in the figure above are required. Add their paths to the system environment variables:

![image-20260911110954590](figures/image-20260911110954590.png)

Add the signing and programming tool paths to the environment variables as follows:

![image-20260911111014180](figures/image-20260911111014180.png)

The programming algorithm is located at the following path:

![image-20260911111036134](figures/image-20260911111036134.png)

Add the environment variable as follows:

![image-20260911111101078](figures/image-20260911111101078.png)

### Quick Start

This BSP provides MDK5 and IAR projects and also supports the GCC development environment. The following describes how to run the system.

**Important!**

Before compiling, open ENV and run the following commands. These commands pull the required HAL and CMSIS packages; otherwise, compilation will fail:

```bash
pkgs --upgrade
pkgs --update
```

#### Hardware Connection

Use a USB Type-C to Type-C cable to connect the development board to the PC, and make sure that ST-Link is recognized in Device Manager.

#### Build and Download

##### MDK Environment

Double-click the `Project.uvmpw` file to open the workspace containing the two MDK5 projects (FSBL and APP).

Switch projects in the workspace:

1. Right-click the workspace name.
2. Click `Manage Multi-Project Workspace...`.

![image-20260911112015746](figures/image-20260911112015746.png)

3. Select the project to switch to.
4. Click `Set as Active Project`.
5. Click `OK` to complete the switch.

![image-20260911112425301](figures/image-20260911112425301.png)

6. The workspace is now switched to the `stm32n657xx_fsbl` project.

![image-20260911112556644](figures/image-20260911112556644.png)

Build and download both projects separately.

> The projects are configured to use the ST_LINK debugger for downloading by default. After connecting the development board through ST_LINK, click the download button to download the program to the board.

##### SCons Environment

1. Build the FSBL firmware:

```
scons fsbl -j16
```

2. Build the APP firmware:

```
scons -j16
```

The program can be downloaded using `tools\STM32N6固件烧录工具.exe`.

After opening the programming tool, select `fsbl\Signing_Programmer.bat` as the FSBL programming script and `.\Signing_Programmer.bat` as the APP programming script. Click the "One-click download complete firmware" button to download the complete firmware.

#### Running Result

After the program is downloaded successfully, the system runs automatically and the LED blinks.

Connect the corresponding serial port on the development board to the PC and open the serial port in a terminal tool (`115200-8-1-N`). After resetting the device, you can see the RT-Thread output:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     5.3.1 build Sep 11 2026 09:31:55
 2006 - 2026 Copyright by RT-Thread team
msh >
```

### Advanced Usage

This BSP enables only GPIO and UART1 by default. To use more advanced features, configure the BSP with the ENV tool as follows:

1. Open the ENV tool in the `bsp` directory.

2. Enter the `menuconfig` command to configure the project, then save and exit.

3. Enter the `pkgs --update` command to update the software packages.

4. Enter the `scons --target=mdk4/mdk5/iar` command to regenerate the project.

For more information, see [STM32 Series BSP Peripheral Driver Usage Tutorial](../docs/STM32系列BSP外设驱动使用教程.md).

## Notes

- Debug serial port mapping for UART1:

  PE5 ------> VCP_TX

  PE6 ------> VCP_RX

- If the FSBL project cannot be found during compilation, check whether the `stm32n657xx_fsbl-latest` package exists in the `packages` directory.
