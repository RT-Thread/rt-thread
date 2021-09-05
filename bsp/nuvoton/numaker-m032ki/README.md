# NuMaker-M032KI

## 1. Introduction

The NuMaker-M032KI is an evaluation board for Nuvoton NuMicro M032 microcontrollers. The NuMaker-M032KI consists of two parts, a M032 target board and an on-board Nu-Link2-Me debugger and programmer. The NuMaker-M032KI is designed for secure evaluation, prototype development and validation with power consumption monitoring function.

[![NuMaker-M032KI](https://i.imgur.com/6SEc2Aa.png "NuMaker-M032KI")](https://i.imgur.com/uncXX0g.jpg "NuMaker-M032KI")

### 1.1 MCU specification

|  | Features |
| -- | -- |
| MCU | M032KIAAE |
| Operation frequency | 72MHz |
| embedded Flash size | 512KB, Dual Bank |
| SRAM size | 96kB |

### 1.2 Interface

| Interface |
| -- |
| Arduino UNO |
| USB 1.1 port |

### 1.3 On-board devices

| Device | Description | Driver supporting status |
| -- | -- | -- |
| LED | PB14 Led | Supported

## 2. Supported compiler

Support GCC, MDK5, IAR IDE/compilers. More information of these compiler version as following:

| IDE/Compiler  | Tested version                    |
| ---------- | ------------------------------------ |
| MDK5       | 5.28.0                               |
| IAR        | 8.32                                 |
| GCC        | GCC 6.3.1 20170620 (Need update env) |

Notice: Please install Nu-Link_Keil_Driver or Nu-Link_IAR_Driver for development.

## 3. Program firmware

### Step 1:

At first, you need to configure ISW1 switch on the NuMaker-M032KI board. Set the four switches to ‘ON’ position. After the configuration is done, connect the NuMaker-M032KI board and your computer using the USB Micro cable. After that, window manager will show a ‘NuMicro MCU’ virtual disk. Finally, you will use this virtual disk to burn firmware.

[![NuLinkMe](https://i.imgur.com/us0Fhhu.png "NuLinkMe")](https://i.imgur.com/us0Fhhu.png "NuLinkMe")

[![NuMicro MCU](https://i.imgur.com/lWnNtpM.png "NuMicro MCU")](https://i.imgur.com/lWnNtpM.png "NuMicro MCU")

### Step 2:

A simple firmware burning method is that you can drag and drop the binary image file to NuMicro MCU virtual disk or copy the binary file to NuMicro MCU disk to burn firmware.

[![CopyTo](https://i.imgur.com/6NfGS7m.png "CopyTo")](https://i.imgur.com/6NfGS7m.png "CopyTo")


## 4. Test

You can use Tera Term terminate emulator (or other software) to type commands of RTT. All parameters of serial communication are shown in below image. Here, you can find out the corresponding port number of Nuvoton Virtual Com Port in window device manager.

[![Serial settings](https://i.imgur.com/5NYuSNM.png "Serial settings")](https://i.imgur.com/5NYuSNM.png "Serial settings")

## 5. Purchase
* [Nuvoton Direct](https://direct.nuvoton.com/en/numaker-m032ki)

## 6. Resources
* [Board Introduction](https://www.nuvoton.com/board/numaker-m032ki/?index=2)
* [Download Board Schematics](https://www.nuvoton.com/resource-download.jsp?tp_GUID=UG0120191106152943)
* [Download MCU TRM](https://www.nuvoton.com/resource-download.jsp?tp_GUID=DA05-M031)
