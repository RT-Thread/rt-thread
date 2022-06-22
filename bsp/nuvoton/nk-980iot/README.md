# NK-980IoT
## 1. Introduction
Nuvoton Technology provides industrial IoT development platform using NUC980DK61Y microprocessor, which is an industrial IoT open platform, including complete hardware design and software reference design. The platform is powered by Nuvoton ARM9 MPU with a 300 MHz internal speed and up to 128 MB DDR memory, single 10/100 Ethernet port, 2 high-speed USB hosts, 1 Gb SPI NAND Flash memory, microphone input, stereo headphone output and Arduino compatible interface.

[![NK-980IOT](https://i.imgur.com/bKvBJLA.png "NK-980IOT")](https://i.imgur.com/bKvBJLA.png "NK-980IOT")


### 1.1 MCU specification

|  | Features |
| -- | -- |
| Part NO. | NUC980DK61Y |
| CPU ARCH. | 32-bit ARM926EJ-STM |
| Operation frequency | 300 MHz |
| Embedded SDRAM size | Built-in 64MB (Up to 128 MB DDR memory) |
| Crypto engine |  AES, RSA, ECC, HMAC and SHA crypto accelerator |
| RMII interface |  10/100 Mbps x2 |
| USB 2.0 |  High Speed Host x1, High Speed Host/Device x1 |
| Audio |  Mono microphone / Stereo headphone |
| Extern storage |  1 Gbit SPI-NAND Flash |
| SD card slot |  SD |
| EBI interface |  External memory expansion interface |

### 1.2 Interface

| Interface |
| -- |
| Arduino UNO |
| A RJ45 Ethernet |
| An USB 2.0 HS port |
| An USB 2.0 HS OTG port |
| A microSD slot |
| A 3.5mm Audio connector |
| An EBI connector |
| An ICE connector |

### 1.3 On-board devices

| Device | Description | Driver supporting status |
| -- | -- | -- |
|Ethernet PHY | IP101GR | Supported |
|Button |  | Supported |
|LEDs |  | Supported |
|Audio Codec | NAU8822, Supports MIC and earphone | Supported |
|USB Device | VCOM + MStorage | Supported |
|2xUSB Host | MStorage | Supported |
|SPI NAND flash | W25N01GVZE1G | Supported |
|VCOM | For console | Ready.(Need to install VCOM driver) |

## 2. Supported compiler
Support GCC and MDK IDE/compilers. More information of these compiler version as following:
| IDE/Compiler  | Tested version            |
| ---------- | ---------------------------- |
| MDK        | uVision 5.25                 |
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

### 3.3 SPI NAND flash using NuWriter
You can use NuWriter to program rtthread.bin into SPI NAND flash.
[![SPI NAND flash](https://i.imgur.com/p9LudBK.gif "SPI NAND flash")](https://i.imgur.com/p9LudBK.gif "SPI NAND flash using NuWriter")
<br>
Choose type: SPINAND<br>
<< Press Re-Connect >><br>

<< Press Erase >><br>
<< Select Erase All >><br>
<< Press OK >><br>

Choose file: Specify your uboot-spl.bin file.<br>
Image Type: Loader<br>
Execute Address: 0x200<br>
<< Press Program >><br>

Choose file: Specify your uboot.bin file.<br>
Image Type: Data<br>
Image start address: 0x100000<br>
<< Press Program >><br>

Choose file: Specify your rtthread.bin file.<br>
Image Type: Data<br>
Image start address: 0x200000<br>
<< Press Program >><br>

Choose file: Specify your env.txt file.<br>
Image Type: Environment<br>
Image start address: 0x80000<br>
<< Press Program >><br>

<< Press OK & Wait it down >><br>
<< Set Power-on setting to SPI NAND booting >><br>
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
* [Download NK-980IOT Quick Start Guide][3]
* [Download TRM][4]
* [Download NuWriter][5]

  [1]: https://direct.nuvoton.com/tw/numaker-iiot-nuc980
  [2]: https://www.nuvoton.com/resource-download.jsp?tp_GUID=UG1020190308162722
  [3]: http://www.nuvoton.com/resource-download.jsp?tp_GUID=UG0520190311115040
  [4]: https://www.nuvoton.com/resource-download.jsp?tp_GUID=DA05-NUC980-1
  [5]: https://github.com/OpenNuvoton/NUC980_NuWriter
  