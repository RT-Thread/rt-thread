# NuMaker-PFM-M487

## 1. Introduction
NuMaker-PFM-M487 provides multiple networking, interfaces, audio recording, playback functions, and flexible extended data storage. 

[![NuMaker-PFM-M487](https://i.imgur.com/k8krqTW.png "NuMaker-PFM-M487")](https://i.imgur.com/k8krqTW.png "NuMaker-PFM-M487")

### 1.1 MCU specification

|  | Features |
| -- | -- |
| MCU | M487JIDAE |
| Operation frequency | 192MHz |
| embedded Flash size | 512kB, Dual Bank |
| SRAM size | 160kB |
| Crypto engine | DES, AES, ECC, 3DES, HMAC and SHA crypto accelerator |
| RMII interface | Support 10/100 Mbps Ethernet |

### 1.2 Interface

| Interface |
| -- |
| Arduino UNO |
| RJ45 Ethernet |
| USB 1.1/2.0 OTG ports |
| A microSD slot |
| A 3.5mm Audio connector |

### 1.3 On-board devices

| Device | Description | Driver supporting status |
| -- | -- | -- |
|SPI flash | W25Q32 | Supported |
|Ethernet PHY| IP101GR | Supported |
|Audio Codec| NAU88L25, Supports MIC and earphone | Supported |

## 2. Supported compiler
Support GCC, MDK4, MDK5, IAR IDE/compilers. More information of these compiler version as following:

| IDE/Compiler  | Tested version            |
| ---------- | ---------------------------- |
| MDK4       | 4.76                         |
| MDK5       | 5.26.2                       |
| IAR        | 8.2                          |
| GCC        | GCC 5.4.1 20160919 (release) |

Notice: Please install Nu-Link_Keil_Driver or Nu-Link_IAR_Driver for development.

## 3. Program firmware
### Step 1:
At first, you need to configure ISW1 switch on the NuMaker-PFM-M487 board. Set the four switches to ‘ON’ position. After the configuration is done,  connect the NuMaker-PFM-M487 board and your computer using the USB Micro cable. After that, window manager will show a ‘NuMicro MCU’ virtual disk. Finally, you will use this virtual disk to burn firmware.

[![NuLinkMe](https://i.imgur.com/daoohon.png "NuLinkMe")](https://i.imgur.com/daoohon.png "NuLinkMe")

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
* [Download board schematics][2]
* [Download MCU TRM][3]

  [1]: https://direct.nuvoton.com/en/numaker-pfm-m487
  [2]: https://www.nuvoton.com/resource-download.jsp?tp_GUID=HL0120180420145943
  [3]: https://www.nuvoton.com/resource-download.jsp?tp_GUID=DA05-M480
