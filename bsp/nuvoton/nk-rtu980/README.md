# NK-RTU980
## 1. Introduction
NuMaker-RTU-NUC980, also known as Chili, is a Nuvoton’s development platform that uses NUC980DR61YC microprocessor with a 64-pin package on a 50 mm x 50 mm dimension PCB. Chili board provides a high-end hardware features including a NUC980DR61YC ARM926EJ-S processor with 64 MB DRAM, 32MB SPI NOR Flash, 10/100 Ethernet MAC interface, USB 2.0 High Speed host/device connector, CAN bus, RS-485 and five GPIOs. Crypto engine supports RSA2048, AES256, ECC, SHA512 algorithm and a Pseudo Random Number Generator for communication security protection.


[![NK-RTU980](https://i.imgur.com/gCKG4PN.png "NK-RTU980")](https://i.imgur.com/gCKG4PN.png "NK-RTU980")


### 1.1 MCU specification

|  | Features |
| -- | -- |
| Part NO. | NUC980DR61YC |
| CPU ARCH. | 32-bit ARM926EJ-STM |
| Operation frequency | 300 MHz |
| Embedded SDRAM size | Built-in 64MB |
| Crypto engine |  AES, RSA, ECC, HMAC and SHA crypto accelerator |
| RMII interface |  10/100 Mbps x1 |
| USB 2.0 |  High Speed Host x1, High Speed Host/Device x1 |
| Extern storage |  32 MB SPI-NOR Flash |

### 1.2 Interface

| Interface |
| -- |
| Arduino UNO |
| A RJ45 Ethernet |
| An USB 2.0 HS port |
| An USB 2.0 HS OTG port |
| A RS-485 |
| A CAN bus |
| An ICE connector |

### 1.3 On-board devices

| Device | Description | Driver supporting status |
| -- | -- | -- |
|Ethernet PHY | IP101GR | Supported |
|Button |  | Supported |
|LEDs |  | Supported |
|USB Device | VCOM + MStorage | Supported |
|USB Host | MStorage | Supported |
|SPI NOR flash | W25Q256F | Supported |
|VCOM | For console | Ready.(Need to install VCOM driver) |

## 2. Supported compiler
Support GCC and MDK IDE/compilers. More information of these compiler version as following:
| IDE/Compiler  | Tested version            |
| ---------- | ---------------------------- |
| MDK        | uVision 5.25.2               |
| GCC        | 6-2017-q1-update             |

Notice: Please install ICE driver for development and [NuMicro_ARM9_Device_Database_Keil](https://www.nuvoton.com/resource-download.jsp?tp_GUID=SW1820201207155701).

## 3. Program firmware
### 3.1 SDRAM Downloading using NuWriter
You can use NuWriter to download rtthread.bin into SDRAM, then run it.
[![SDRAM Downloading using NuWriter](https://i.imgur.com/NvbzsRp.gif "SDRAM Downloading using NuWriter")](https://i.imgur.com/NvbzsRp.gif "SDRAM Downloading using NuWriter")
<br>
Choose type: DDR/SRAM<br>
<< Press Re-Connect >><br>
Choose file: Specify your rtthread.bin file.<br>
Execute Address: 0x0<br>
Option: Download and run<br>
<< Press Download >><br>
Enjoy!! <br>
<br>

### 3.2 SPI NOR flash using NuWriter
You can use NuWriter to program rtthread.bin into SPI NOR flash.
[![SPI NOR flash](https://i.imgur.com/8OtXGSQ.gif "SPI NOR flash")](https://i.imgur.com/8OtXGSQ.gif "SPI NOR flash using NuWriter")
<br>
Choose type: SPI<br>
<< Press Re-Connect >><br>
Choose file: Specify your rtthread.bin file.<br>
Image Type: Loader<br>
Execute Address: 0x0<br>
<< Press Program >><br>
<< Press OK & Wait it down >><br>
<< Set Power-on setting to SPI NOR booting >><br>
<< Press Reset button on board >><br>
Enjoy!! <br>
<br>

## 4. Test
You can use Tera Term terminate emulator (or other software) to type commands of RTT. All parameters of serial communication are shown in below image. Here, you can find out the corresponding port number of Nuvoton Virtual Com Port in window device manager.

[![Serial settings](https://i.imgur.com/5NYuSNM.png "Serial settings")](https://i.imgur.com/5NYuSNM.png "Serial settings")

## 5. Purchase
* [Nuvoton Direct][1]

## 6. Resources
* [Download Board Schematics][2]
* [Download NK-RTU980 Quick Start Guide][3]
* [Download TRM][4]
* [Download NuWriter][5]

  [1]: https://direct.nuvoton.com/tw/numaker-rtu-nuc980
  [2]: https://www.nuvoton.com/resource-download.jsp?tp_GUID=HL1020200508155209
  [3]: https://www.nuvoton.com/resource-download.jsp?tp_GUID=UG1320200623183237
  [4]: https://www.nuvoton.com/resource-download.jsp?tp_GUID=DA05-NUC980-1
  [5]: https://github.com/OpenNuvoton/NUC980_NuWriter
  