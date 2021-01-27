# RISC-V RV32M1 VEGA Board BSP(Board Support Package) Execution Instruction

[中文页](README_zh.md) |

## Introduction

RV32M1_VEGA board is a heterogeneous multi-core RISC-V 32 development board that contains two RISC-V 32-bit cores, as well as BLE peripherals.

| Hardware       | Description                                                  |
| -------------- | ------------------------------------------------------------ |
| Chip Model     | RV32M1                                                       |
| CPU            | RV32IMC, with extensons for post-incrementing load and stores, |
|                | multiply-accumulate extensions, ALU extensions, hardware loops. |
|                | RV32IEMC                                                     |
| Main Frequency | 48MHz or 72MHz                                               |
|                | 48MHz or 72MHz                                               |
| On-chip SRAM   | 256kB + 128kB                                                |
| On-chip Flash  | 1MB + 256kB                                                  |

## **Compilation**

The toolchain currently used for test is built from the standard GNU GCC 7.2.0 and newlib 2.5.0 and for the standard RV32IMC architecture, so the extension instructions of RV32M1 is not supported, note that the version of RT-Thread ENV used in this BSP is 1.0.

It's recommended to use the [env tool](https://www.rt-thread.io/download.html?download=Env) to compile programs on Windows. Switch to the directory `bsp/rv32m1_vega/ri5cy` in the console and run the following command to compile this BSP:

```
scons
```

If successfully compiled, a new 'rtthread.elf' and 'rtthread.bin' file will be generated. ‘rtthread.bin' needs to be burned to the device and run.

## Burn and Execution

Please use JLink to connect to the JTAG interface of the RISC-V core on the RV32M1_VEGA board, and change the JLink driver to WinUSB mode. The JTAG interface is located next to the RV32M1 chip and the antenna seat, with a small 20pin JTAG interface.

Use a USB cable to connect to a USB port marked with SDA, then a serial device is recognized by PC, which can be opened with the configuration of 115200-N-8-1. The serial pins used by the device are: `[PTC7/PTC8]`

When the rtthread.bin image file is generated after being correctly compiled, you can use gdb to connect to openocd and burn it to flash with the `load` command.

For more information about how to use JTAG and how to use gdb to debug the RV32M1_VEGA development board, please refer to [Development Environment Construction](https://github.com/open-isa-org/open-isa-org/open-isa.org/blob/master/RV32M1_Vega_Develop_Environment_Setup.pdf).

## Running Results

When the compiling and burning are done correctly, press the reset button `SW1` to reset the device, the startup message of RT-Thread can be observed via the serial port :

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.0 build Dec  5 2018
 2006 - 2018 Copyright by rt-thread team
File System initialized!
Hello RT-Thread!
msh />
```

## Peripheral Condition

| Drive  | Support                                                      | Remark                      |
| ------ | ------------------------------------------------------------ | --------------------------- |
| UART   | Support                                                      | UART0, RX(PTC7), TX(PTC8)   |
|        | Support                                                      | UART1, RX(PTA25), TX(PTA26) |
| clock  | Support                                                      |                             |
| GPIO   | Support(The list may not complete, also you need to modify pinmux, clock according to the IO being used.) |                             |
| MMC/SD | Support                                                      |                             |

## **IO mapping in BSP**

| IO Number | BSP Code Definition |
| --------- | ------------------- |
| PTA22     | LED_BLUE            |
| PTA23     | LED_GREEN           |
| PTA24     | LED_RED             |
| PTA24     | LED_STS             |
| PTA25     | UART1_RX            |
| PTA26     | UART1_TX            |
| PTE8      | BTN_SW3             |
| PTE9      | BTN_SW4             |
| PTE12     | BTN_SW5             |
| PTA0      | BTN_SW2/BTN_NMI     |

## References

- [User Guide](https://github.com/open-isa-org/open-isa.org/blob/master/RV32M1_VEGA_Board_User_Guide.pdf)
- Chip [Reference Manual and Data Sheet](https://github.com/open-isa-org/open-isa.org/blob/master/Reference Manual and Data Sheet/RV32M1DS_Rev.1.1.pdf)
- [open-isa](https://github.com/open-isa-org/open-isa.org)

