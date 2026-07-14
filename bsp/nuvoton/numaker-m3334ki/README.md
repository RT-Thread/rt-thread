# NuMaker-M3334KI

## 1. Introduction
The NuMaker M3334KI is a microcontroller platform with comprehensive peripheral integration specially developed by Nuvoton. The NuMaker-M3334KI is based on the NuMicro® M3331 series MCU with ARM® -Cortex®-M33 core.


### 1.1 MCU specification

|  | Features |
| -- | -- |
| MCU | 32-bit Arm CM33 M3334KIGAE |
| Operation frequency | 180 MHz |
| Embedded Flash size | 512KB, Dual Bank |
| SRAM size | 320 kB |

### 1.2 Interface

| Interface |
| -- |
| Arduino UNO |
| USB 2.0 Type-C ports |

### 1.3 On-board devices (NuMaker-M3334KI V2.0)

| Device | Description | Driver supporting status |
| -- | -- | -- |
| LED | on-board | Supported |
| HSUSB | DRP (HOST or Device Role) | Supported |

### 1.4 Extended boards

| Board | Description | Driver supporting status |
| -- | -- | -- |
| NUTFT | v1.3 | Supported |
| NUFUN | v2.0 | Coming soon |

## 2. Supported compiler

Support GCC, MDK5 IDE/compilers. More information of these compiler version as following:

| IDE/Compiler  | Tested version                    |
| ---------- | ------------------------------------ |
| MDK5       | 5.40                                 |
| GCC        | Arm Embedded Toolchain 10.3-2021.10 (Env 1.3.5 embedded version)|

Notice:
(1) Please install Nu-Link_Keil_Driver for development.

## 3. Program firmware

### Step 1

At first, you need to configure ICESW2 switch on the NuMaker-M2L31KI board. Set the four switches to ‘ON’ position. After the configuration is done, connect the NuMaker-M2L31KI board and your computer using the USB Type-C cable. After that, window manager will show a ‘NuMicro MCU’ virtual disk. Finally, you will use this virtual disk to burn firmware.

### Step 2

A simple firmware burning method is that you can drag and drop the binary image file to NuMicro MCU virtual disk or copy the binary file to NuMicro MCU disk to burn firmware.

## 4. Test

You can use Tera Term terminate emulator (or other software) to type commands of RTT. All parameters of serial communication are shown in below image. Here, you can find out the corresponding port number of Nuvoton Virtual Com Port in window device manager.
