# Raspberry PI 3–64 BSP (Board Support Package) Execution Instruction 

[中文页](README_zh.md) |

## Introduction

This document records the execution instruction of the BSP (board support package) provided by the RT-Thread development team for the Raspberry PI 3–64 development board.

## **Compilation Instruction**

### Build Environment on Windows

It's recommended to use the [env tool ](https://github.com/RT-Thread/rt-thread/blob/master/documentation/env/env.md)to compile the Raspberry PI 3–64 BSP on Windows. Firstly, download the compiler GCC on Windows, from the official ARM website. You can refer to [Here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads).

Here we choose the version "[gcc-arm-8.3–2019.03-i686-mingw32-aarch64-elf]. 

Unzip the compressed package to the local directory, like "E:/env/tools/gnu_gcc/arm_gcc".

Then edit the file "<rt-thread_directory>/bsp/raspberry-pi/raspi3–64/rtconfig. py", modify the variable "EXEC_PATH" to the compiler path:

```
EXEC_PATH = r'E:/env/tools/gnu_gcc/arm_gcc/gcc-arm-8.3–2019.03-i686-mingw32-aarch64-elf/bin'
```

Finally, enter the BSP directory "<rt-thread_directory>/bsp/raspberry-pi/raspi3–64/" and execute the "scons" command.

### Build Environment on Linux

The steps to build Raspberry PI 3–64 BSP on Linux is pretty similar to that on Windows, the only difference is that we need to download the GCC on Linux instead, such as the version "gcc-arm-8.3–2019.03-x86_64-aarch64-elf".

Then we unpack the compiler package, modify the file "rtconfig.h" and run "scons".

## Execution

### Prepare the raspbian SD card

- Download the raspbian image, for example, "2018–06–27-raspbian-stretch-lite.zip". Unpack it.

- Burn the SD card on Windows

On Windows, download the burning tool "[etcher.io](http://etcher.io/)", run it and choose the unpacked image "2018–06–27-raspbian-stretch-lite.img".

When the burning process is completed, put "kernel8.img" into the boot partition to replace the file wit the same name.

- Burn the SD card on Linux

Prepare an empty SD card, plug it in the computer and then execute the command below: "sudo dd if=2018–06–27-raspbian-stretch-lite.img of=/dev/xxx bs=32M conv=fsync"

Note that the device file "/dev/xxx" should be replaced with the real SD card.

### Prepare the serial port wire

The BSP uses GPIO 14 & GPIO 15 of raspi 3 as the communication ports, as shown in the following image (The board is raspberry-pi2, which uses the same pins as raspi-3):



[![raspi2](https://github.com/RT-Thread/rt-thread/raw/master/bsp/raspberry-pi/raspi3-64/figures/raspi_uart.png)](https://github.com/RT-Thread/rt-thread/blob/master/bsp/raspberry-pi/raspi3-64/figures/raspi_uart.png)

The serial port parameters: 115200 8N1, hardware and software flow control is off.

## Running Result

Insert the burned SD card into Raspberry Pi, power up, the output information on serial port should be like this:

```
 heap: 0x00020b20 - 0x00400000

 \ | /
- RT -     Thread Operating System
 / | \     3.1.0 build Aug 23 2019
 2006 - 2019 Copyright by rt-thread team
Hello RT-Thread!
msh >
```

## Peripheral Condition

| Drive | Support | Remark |
| ----- | ------- | ------ |
| UART  | Support | UART0  |
| GPIO | Support | - |
| I2C | Support | - |
| RTC | Support | - |
| SDIO | Support | SDCARD |
| SPI | Support | - |
| TIMER | Support | - |
| WDT | Support | - |
| MBOX | Support | - |
| FRAMEBUFFER | Support | HDMI |

