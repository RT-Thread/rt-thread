# NuMaker-M2354
## 1. Introduction
The NuMaker-M2354 is an evaluation board for Nuvoton NuMicro M2354 microcontrollers. The NuMaker-M2354 consists of two parts, a M2354 target board and an on-board Nu-Link2-Me debugger and programmer. The NuMaker-M2354 is designed for secure evaluation, prototype development and validation with power consumption monitoring function.

[![NuMaker-M2354](https://i.imgur.com/uncXX0g.jpg "NuMaker-M2354")](https://i.imgur.com/uncXX0g.jpg "NuMaker-M2354")

### 1.1 MCU specification

|  | Features |
| -- | -- |
| MCU | M2354KJFAE |
| Operation frequency | 96MHz |
| embedded Flash size | 1MB, Dual Bank |
| SRAM size | 256kB |
| Crypto engine | PRNG, AES, ECC, RSA, HMAC and SHA crypto accelerator |

### 1.2 Interface

| Interface |
| -- |
| Arduino UNO |
| USB 1.1 OTG ports |
| A microSD slot |
| A segment LCD port |

### 1.3 On-board devices

| Device | Description | Driver supporting status |
| -- | -- | -- |
|Wi-Fi module| ESP8266-ESP12, AT firmware v1.7 | Supported |
|Segment LCD module| | Supported |

## 2. Supported compiler
Support GCC, MDK5, IAR IDE/compilers. More information of these compiler version as following:

| IDE/Compiler  | Tested version                    |
| ---------- | ------------------------------------ |
| MDK5       | 5.26.2                               |
| IAR        | 8.32                                 |
| GCC        | GCC 6.3.1 20170620 (Need update env) |

Notice: 
(1) Please install Nu-Link_Keil_Driver or Nu-Link_IAR_Driver for development.

## 3. Program firmware
### Step 1:
At first, you need to configure ISW1 switch on the NuMaker-M2354 board. Set the four switches to ‘ON’ position. After the configuration is done, connect the NuMaker-M2354 board and your computer using the USB Micro cable. After that, window manager will show a ‘NuMicro MCU’ virtual disk. Finally, you will use this virtual disk to burn firmware.

[![NuLinkMe](https://i.imgur.com/us0Fhhu.png "NuLinkMe")](https://i.imgur.com/us0Fhhu.png "NuLinkMe")

[![NuMicro MCU](https://i.imgur.com/lWnNtpM.png "NuMicro MCU")](https://i.imgur.com/lWnNtpM.png "NuMicro MCU")

### Step 2:
A simple firmware burning method is that you can drag and drop the binary image file to NuMicro MCU virtual disk or copy the binary file to NuMicro MCU disk to burn firmware.

[![CopyTo](https://i.imgur.com/6NfGS7m.png "CopyTo")](https://i.imgur.com/6NfGS7m.png "CopyTo")

## 4. Test
You can use Tera Term terminate emulator (or other software) to type commands of RTT. All parameters of serial communication are shown in below image. Here, you can find out the corresponding port number of Nuvoton Virtual Com Port in window device manager.

[![Serial settings](https://i.imgur.com/5NYuSNM.png "Serial settings")](https://i.imgur.com/5NYuSNM.png "Serial settings")

## 5. Purchase
* [Nuvoton Direct][1]

## 6. Resources
* [Board Introduction][2]
* [Download Board Schematics][3]
* [Download MCU TRM][4]

  [1]: https://direct.nuvoton.com/en/numaker-m2354
  [2]: https://www.nuvoton.com/board/numaker-m2354/index.html
  [3]: https://www.nuvoton.com/resource-download.jsp?tp_GUID=HL1020201102161956
  [4]: https://www.nuvoton.com/resource-download.jsp?tp_GUID=DA05-M2354
