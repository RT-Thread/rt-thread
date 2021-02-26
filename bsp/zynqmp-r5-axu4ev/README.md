# AXU4EV-E BSP (Board Support Package) Execution Instruction

[中文页](README_zh.md) |

## **Introduction**

This document records the execution instruction of the BSP (board support package) for the AXU4EV-E development board.

The document is covered in three parts:

- AXU4EV-E Board Resources Introduction
- Quickly Get Started
- Advanced Features
- BSP Migration

By reading the Quickly Get Started section developers can quickly get their hands on this BSP and run RT-Thread on the board. More advanced features will be introduced in the Advanced Features section to help developers take advantage of RT-Thread to drive more on-board resources.

## AXU4EV-E Resources Introduction

ALINX AXU4EV-E: Xilinx Zynq UltraScale+ MPSOC XCZU4EV-1SFVC784I Ethernet FPGA development board, the SoM Core board is the smallest system, mainly composed of XCZU4EV-1SFVC784I + 5 DDR4 + eMMC + 1 QSPI FLASH. The Carrier board expands a wealth of peripheral interfaces for the core board, including 1 SATA M.2 interface, 1 DP output interface, 4 USB3.0 interfaces, 2 Gigabit Ethernet interfaces, 2 UART interfaces, 1 SD card interface, 2*40-pin Expansion Connectors for Modules, 2 CAN bus interfaces, 2 RS485 interfaces, 1 MIPI interface, Keys and LEDs. High-speed data exchange and transmission, data storage, pre-verification and post-application of data processing, video transmission processing, deep learning, artificial intelligence and industrial control, is a professional ZYNQ development platform. suitable for students, engineers and other groups engaged in the development of MPSoCs.

For more details about this board, please refer to [Alinx Electronic Technology (Shanghai) Co.,Ltd.](http://www.alinx.com/en/)。

## **Peripheral Condition**

Each peripheral supporting condition for this BSP is as follows:

| **Core**      | **Support** | **Remark**                              |
| :----------------- | :----------: | :------------------------------------- |
| R5-CPU0   |     Support     | The R5-CPU0 is running the system |
| **On-board Peripherals**      | **Support** | **Remark**                              |
| None |          |  |
| **On-chip Peripherals**      | **Support** | **Remark**                              |
| GPIO              |     Support     |  |
| UART              |     Support     | UART0                            |
| TIMER     |     Support     |     TTC0 provides system clock         |
| EMMC | Support | SD0 Controller |

## Execution Instruction

### Quickly Get Started

This BSP only support the GCC development environment. Here's an example to introduce how to run the system.

#### Compile and Download

1. Open the env tool under BSP. Enter `scons` to compile.

2. After compiling, `rtthread-zynqmp-r5.elf` file will be generated in BSP directory.

3. Use Xilinx Vitis to generate fsbl, and then create "Debug Configuration", select the `rtthread-zynqmp-r5.elf` file as the application.

4. Use the debugger to connect the PC and the development board. Set the dial switch to JTAG to start. Then connect the power supply. Click start debugging or running.

   Since the compiler has debugging information by default (see rtconfig.py In BUILD, so when debugging in Xilinx Vitis, you can also open source files to set breakpoints for debugging.

#### Software Solidification

1. Open the env tool under BSP. Enter `scons` to compile.

2. After compiling, `rtthread-zynqmp-r5.elf` file will be generated in BSP directory.

3. Use Xilinx Vitis or Xilinx SDK to generate fsbl, and then use the bootgen tool provided by Xilinx to make fsbl BOOT.bin Documents.

   For example, use the command line:

   ```
    bootgen -image ./output.bif -arch zynqmp -o ./BOOT.bin -w on
   ```
   
   And the outpu.bif file could be：
   ```
   //arch = zynqmp; split = false; format = BIN
   the_ROM_image:
   {
        [bootloader, destination_cpu = r5-0]./fsbl.elf
        [destination_cpu = r5-0, exception_level = el-3]./rtthread-zynqmp-r5.elf
   }
   ```
   
4. According to the document provided by Alinx, put BOOT.bin into SD card or burn to QSPI flash, set the startup mode through dial switch, and then connect the power supply to start.


#### Running Results

Once the project is successfully downloaded, the system runs automatically.

Connect the serial port of the board to PC, communicate with it via a serial terminal tool (115200bps, 8N1). Restart the board and the startup information of RT-Thread will be observed:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Nov 27 2020
 2006 - 2020 Copyright by rt-thread team
msh />
```

### **Advanced Features**

This BSP enables EMMC driver and DFS file system by default. If you need to use a file system, you can format and mount it by yourself.

## BSP Migration

If you need to ported the BSP to another development board of Xilinx Zynq UltraScale+ MPSOC development platform, it is also convenient. The main modifications are as follows:

1. Memory: `psu_r5_ddr_0_MEM_0` in `zynqmp-r5.ld` (if DDR memory is less than 2G)
2. Main Frequency: `XPAR_CPU_CORTEXR5_0_CPU_CLK_FREQ_HZ` in `zynqmp-r5.h`
3. Pin and Frequency of Serial Port: `rxmio`, `txmio` and `XPAR_PSU_UART_0_UART_CLK_FREQ_HZ` in `drv_uart.c`
4. Timer Frequency: `XPAR_PSU_TTC_0_TTC_CLK_FREQ_HZ` in `drv_timer.c`
5. SD Controller: Block device driver initialization in `drv_sdcard.c`

The parameter macro definition in `xparameters.h` does not need to be modified manually. You can directly copy the `xparameters.h` file of the development board generated in Xilinx Vitis.
