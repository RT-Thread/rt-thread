# CherryUSB

[English](./README.md)

CherryUSB 是一个小而美的、可移植性高的、用于嵌入式系统(带 USB IP)的 USB 主从协议栈。

![CherryUSB](CherryUSB.svg)

## 为什么选择

### 易于学习 USB

为了方便用户学习 USB 基本知识、枚举、驱动加载、IP 驱动，因此，编写的代码具备以下优点：

- 代码精简，逻辑简单，无复杂 C 语言语法
- 树状化编程，代码层层递进
- Class 驱动和 porting 驱动模板化、精简化
- API 分类清晰（从机：初始化、注册类、命令回调类、数据收发类；主机：初始化、查找类、数据收发类）

### 易于使用 USB

为了方便用户使用 USB 接口，考虑到用户学习过 uart 和 dma，因此，设计的数据收发类接口具备以下优点：

- 等价于使用 uart tx dma/uart rx dma
- 收发长度没有限制，用户不需要关心 USB 分包过程（分包过程在 porting 中处理）

### 易于发挥 USB 性能

考虑到 USB 性能问题，尽量达到 USB 硬件理论带宽，因此，设计的数据收发类接口具备以下优点：

- Porting 驱动直接对接寄存器，无抽象层封装
- Memory zero copy
- IP 如果带 DMA 则使用 DMA 模式（DMA 带硬件分包功能）
- 长度无限制，方便对接硬件 DMA 并且发挥 DMA 的优势
- 分包过程在中断中执行

## 目录结构

|   目录名       |  描述                          |
|:-------------:|:-------------------------------:|
|class          |  usb class 类主从驱动           |
|common         |  usb spec 定义、常用宏、标准接口定义 |
|core           |  usb 主从协议栈核心实现          |
|demo           |  主从 class demo                 |
|docs           |  文档                            |
|osal           |  os 封装层                       |
|platform       |  其他 os 全家桶适配              |
|port           |  usb 主从需要实现的 porting 接口 |
|tools          |  工具链接                        |

## Device 协议栈简介

CherryUSB Device 协议栈对标准设备请求、CLASS 请求、VENDOR 请求以及 custom 特殊请求规范了一套统一的函数框架，采用面向对象和链表的方式，能够使得用户快速上手复合设备，不用管底层的逻辑。同时，规范了一套标准的 dcd porting 接口，用于适配不同的 USB IP，达到面向 ip 编程。

CherryUSB Device 协议栈当前实现以下功能：

- 支持 USB2.0 全速和高速设备，USB3.0 超速设备
- 支持端点中断注册功能，porting 给用户自己处理中断里的数据
- 支持复合设备
- 支持 Communication Device Class (CDC_ACM, CDC_ECM)
- 支持 Human Interface Device (HID)
- 支持 Mass Storage Class (MSC)
- 支持 USB VIDEO CLASS (UVC1.0、UVC1.5)
- 支持 USB AUDIO CLASS (UAC1.0、UAC2.0)
- 支持 Device Firmware Upgrade CLASS (DFU)
- 支持 USB MIDI CLASS (MIDI)
- 支持 Remote NDIS (RNDIS)
- 支持 WINUSB1.0、WINUSB2.0、WEBUSB、BOS
- 支持 Vendor 类 class
- 支持 UF2
- 支持 Android Debug Bridge (Only support shell)
- 支持相同 USB IP 的多从机

CherryUSB Device 协议栈资源占用说明（GCC 10.2 with -O2）：

|   file        |  FLASH (Byte)  |  No Cache RAM (Byte)      |  RAM (Byte)   |  Heap (Byte)     |
|:-------------:|:--------------:|:-------------------------:|:-------------:|:----------------:|
|usbd_core.c    |  ~4400          | 512(default) + 320        | 0             | 0                |
|usbd_cdc_acm.c |  ~400           | 0                         | 0             | 0                |
|usbd_msc.c     |  ~3800          | 128 + 512(default)        | 16            | 0                |
|usbd_hid.c     |  ~360           | 0                         | 0             | 0                |
|usbd_audio.c   |  ~1500          | 0                         | 0             | 0                |
|usbd_video.c   |  ~2600          | 0                         | 84            | 0                |
|usbd_rndis.c   |  ~2100          | 2 * 1580(default)+156+8     | 76            | 0                |

## Host 协议栈简介

CherryUSB Host 协议栈对挂载在 roothub、外部 hub 上的设备规范了一套标准的枚举实现，对不同的 Class 类也规范了一套标准接口，用来指示在枚举后和断开连接后该 Class 驱动需要做的事情。同时，规范了一套标准的 hcd porting 接口，用于适配不同的 USB IP，达到面向 IP 编程。最后，协议栈使用 OS 管理，并提供了 osal 用来适配不同的 os。

CherryUSB Host 协议栈当前实现以下功能：

- 支持 low speed, full speed, high speed 和 super speed 设备
- 自动加载支持的Class 驱动
- 支持阻塞式传输和异步传输
- 支持复合设备
- 支持多级 HUB,最高可拓展到 7 级(目前测试 1拖 10 没有问题，当前仅支持 dwc2 和 ehci)
- 支持 Communication Device Class (CDC_ACM, CDC_ECM)
- 支持 Human Interface Device (HID)
- 支持 Mass Storage Class (MSC)
- Support USB Video CLASS (UVC1.0、UVC1.5)
- Support USB Audio CLASS (UAC1.0)
- 支持 Remote NDIS (RNDIS)
- 支持 USB Bluetooth (支持 nimble and zephyr bluetooth 协议栈，支持 **CLASS: 0xE0** 或者厂家自定义类，类似于 cdc acm 功能)
- 支持 Vendor 类 class (serial, net, wifi)
- 支持 USB modeswitch
- 支持相同 USB IP 的多主机

同时，CherryUSB Host 协议栈还提供了 lsusb 的功能，借助 shell 插件可以查看所有挂载设备的信息，包括外部 hub 上的设备的信息。

CherryUSB Host 协议栈资源占用说明（GCC 10.2 with -O2）：

|   file        |  FLASH (Byte)  |  No Cache RAM (Byte)            |  RAM (Byte)                 |  Heap (Byte) |
|:-------------:|:--------------:|:-------------------------------:|:---------------------------:|:------------:|
|usbh_core.c    |  ~9000          | 512 + 8 * (1+x) *n              | 28                          | raw_config_desc |
|usbh_hub.c     |  ~6000          | 32 + 4 * (1+x) | 12 + sizeof(struct usbh_hub) * (1+x)          | 0            |
|usbh_cdc_acm.c |  ~900           | 7             | 4  + sizeof(struct usbh_cdc_acm) * x          | 0            |
|usbh_msc.c     |  ~2700          | 64            | 4  + sizeof(struct usbh_msc) * x              | 0            |
|usbh_hid.c     |  ~1400          | 256           | 4  + sizeof(struct usbh_hid) * x              | 0            |
|usbh_video.c   |  ~3800          | 128           | 4  + sizeof(struct usbh_video) * x            | 0            |
|usbh_audio.c   |  ~4100          | 128           | 4  + sizeof(struct usbh_audio) * x            | 0            |
|usbh_rndis.c   |  ~4200          | 512 + 2 * 2048(default)| sizeof(struct usbh_rndis) * 1       | 0            |
|usbh_cdc_ecm.c |  ~2200          | 2 * 1514 + 16           | sizeof(struct usbh_cdc_ecm) * 1     | 0            |
|usbh_cdc_ncm.c |  ~3300          | 2 * 2048(default) + 16 + 32   | sizeof(struct usbh_cdc_ncm) * 1  | 0         |
|usbh_bluetooth.c |  ~1000        | 2 * 2048(default)   | sizeof(struct usbh_bluetooth) * 1       | 0            |

其中，`sizeof(struct usbh_hub)` 和 `sizeof(struct usbh_hubport)` 受以下宏影响：

```
#define CONFIG_USBHOST_MAX_EXTHUBS          1
#define CONFIG_USBHOST_MAX_EHPORTS          4
#define CONFIG_USBHOST_MAX_INTERFACES       8
#define CONFIG_USBHOST_MAX_INTF_ALTSETTINGS 8
#define CONFIG_USBHOST_MAX_ENDPOINTS        4
```

x 受以下宏影响：

```
#define CONFIG_USBHOST_MAX_CDC_ACM_CLASS 4
#define CONFIG_USBHOST_MAX_HID_CLASS     4
#define CONFIG_USBHOST_MAX_MSC_CLASS     2
#define CONFIG_USBHOST_MAX_AUDIO_CLASS   1
#define CONFIG_USBHOST_MAX_VIDEO_CLASS   1
```

## USB IP 支持情况

仅列举标准 USB IP 和商业性 USB IP

|   IP             |  device    | host     | Support status |
|:----------------:|:----------:|:--------:|:--------------:|
|  OHCI(intel)     |  none      | OHCI     |  ×   |
|  EHCI(intel)     |  none      | EHCI     |  √   |
|  XHCI(intel)     |  none      | XHCI     |  √   |
|  UHCI(intel)     |  none      | UHCI     |  ×   |
|  DWC2(synopsys)  |  DWC2      | DWC2     |  √   |
|  MUSB(mentor)    |  MUSB      | MUSB     |  √   |
|  FOTG210(faraday)|  FOTG210   | EHCI     |  √   |
|  CHIPIDEA(synopsys)| CHIPIDEA | EHCI     |  √   |
|  CDNS2(cadence)  |  CDNS2     | CDNS2    |  √   |
|  CDNS3(cadence)  |  CDNS3     | XHCI     |  ×   |
|  DWC3(synopsys)  |  DWC3      | XHCI     |  ×   |

## 文档教程

CherryUSB 快速入门、USB 基本概念，API 手册，Class 基本概念和例程，参考 [CherryUSB Documentation Tutorial](https://cherryusb.readthedocs.io/)

## 视频教程

- USB 基本知识点与 CherryUSB Device 协议栈是如何编写的（使用v0.4.1 版本），参考 https://www.bilibili.com/video/BV1Ef4y1t73d.
- CherryUSB 腾讯会议（使用v1.1.0 版本），参考 https://www.bilibili.com/video/BV16x421y7mM.

## 图形化界面配置工具

[chryusb_configurator](https://github.com/Egahp/chryusb_configurator) 采用 **electron + vite2 + ts** 框架编写，当前用于自动化生成描述符数组，后续会增加其他功能。

## 示例仓库

|   Manufacturer       |  CHIP or Series    | USB IP| Repo Url | Support version     | Support status |
|:--------------------:|:------------------:|:-----:|:--------:|:------------------:|:-------------:|
|Bouffalolab    |  BL702/BL616/BL808 | bouffalolab/ehci|[bouffalo_sdk](https://github.com/CherryUSB/bouffalo_sdk)|<= latest | Long-term |
|ST             |  STM32F1x | fsdev |[stm32_repo](https://github.com/CherryUSB/cherryusb_stm32)|<= latest | Long-term |
|ST             |  STM32F4/STM32H7 | dwc2 |[stm32_repo](https://github.com/CherryUSB/cherryusb_stm32)|<= latest | Long-term |
|HPMicro        |  HPM6000/HPM5000 | hpm/ehci |[hpm_sdk](https://github.com/CherryUSB/hpm_sdk)|<= latest | Long-term |
|Essemi         |  ES32F36xx | musb |[es32f369_repo](https://github.com/CherryUSB/cherryusb_es32)|<= latest | Long-term |
|Phytium        |  e2000 | pusb2/xhci |[phytium_repo](https://gitee.com/phytium_embedded/phytium-free-rtos-sdk)|>=1.4.0  | Long-term |
|Artinchip      |  d12x/d13x/d21x | aic/ehci/ohci |[luban-lite](https://gitee.com/artinchip/luban-lite)|<= latest  | Long-term |
|Espressif      |  esp32s2/esp32s3/esp32p4 | dwc2 |[esp32_repo](https://github.com/CherryUSB/cherryusb_esp32)|<= latest | Long-term |
|NXP            |  mcx | kinetis/chipidea/ehci |[nxp_mcx_repo](https://github.com/CherryUSB/cherryusb_mcx)|<= latest | Long-term |
|AllwinnerTech  |  F1C100S/F1C200S | musb |[cherryusb_rtt_f1c100s](https://github.com/CherryUSB/cherryusb_rtt_f1c100s)|<= latest | the same with musb |
|Bekencorp      |  bk7256/bk7258 | musb |[bk_idk](https://github.com/CherryUSB/bk_idk)| v0.7.0 | the same with musb |
|Sophgo         |  cv18xx | dwc2 |[cvi_alios_open](https://github.com/CherryUSB/cvi_alios_open)| v0.7.0 | TBD |
|WCH            |  CH32V307/ch58x | ch32_usbfs/ch32_usbhs/ch58x |[wch_repo](https://github.com/CherryUSB/cherryusb_wch)|<= v0.10.2 | TBD |
|Raspberry pi   |  rp2040 | rp2040 |[pico-examples](https://github.com/CherryUSB/pico-examples)|<= v0.10.2 | No more updated |

## 软件包支持

CherryUSB 软件包可以通过以下方式获取:

- [RT-Thread](https://packages.rt-thread.org/detail.html?package=CherryUSB)
- [YOC](https://www.xrvm.cn/document?temp=usb-host-protocol-stack-device-driver-adaptation-instructions&slug=yocbook)
- [ESP-Registry](https://components.espressif.com/components/cherry-embedded/cherryusb)

## 商业支持

参考 https://cherryusb.readthedocs.io/zh-cn/latest/support/index.html 。

## 联系

CherryUSB QQ 群:642693751
CherryUSB 微信群：与我联系后邀请加入

## 支持企业

感谢以下企业支持（顺序不分先后）。

<img src="docs/assets/bouffalolab.jpg"  width="100" height="80"/> <img src="docs/assets/hpmicro.jpg"  width="100" height="80" /> <img src="docs/assets/eastsoft.jpg"  width="100" height="80" /> <img src="docs/assets/rtthread.jpg"  width="100" height="80" /> <img src="docs/assets/sophgo.jpg"  width="100" height="80" /> <img src="docs/assets/phytium.jpg"  width="100" height="80" /> <img src="docs/assets/thead.jpg"  width="100" height="80" /> <img src="docs/assets/nuvoton.jpg"  width="100" height="80" /> <img src="docs/assets/artinchip.jpg"  width="100" height="80" /> <img src="docs/assets/bekencorp.jpg"  width="100" height="80" /> <img src="docs/assets/nxp.png"  width="100" height="80" /> <img src="docs/assets/espressif.png"  width="100" height="80" />
