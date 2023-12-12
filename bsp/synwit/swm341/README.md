# SWM341 BSP 说明

标签： SYNWIT、Cortex-M33、SWM341、国产MCU

---

## 简介

本文档为SWM341开发板提供的 BSP (板级支持包) 说明。

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。

## 芯片介绍

- 内核
  - 32位ARM® Cortex™-M33 内核
  - 24位系统定时器
  - 工作频率最高150MHz
  - 硬件单周期乘法
  - 集成嵌套向量中断控制器（NVIC），提供最多104个、8级可配置优先级的中断
  - 通过SWD接口烧录
- 内置LDO
  - 供电电压范围为2.0V至3.6V
- 片上SRAM存储器
  - 64KB
- 片上FLASH存储器
  - 512KB
  - 支持用户定制ISP（在系统编程）更新用户程序
  - 自带Cache
- SDRAMC模块
  - 支持16Bit位宽的SDRAM
  - 支持兼容PC133标准的SDRAM颗粒
  - 支持2MB到32MB的外部SDRAM颗粒
- SFC模块
  - 最大支持外置16MB大小的SPI NOR FLASH
- GPIO
  - 多达7组共112个GPIO
  - 每个IO均支持位带操作
  - 灵活的中断配置
  - 触发类型设置（边沿检测、电平检测）
  - 触发电平设置（高电平、低电平）
  - 触发边沿设置（上升沿、下降沿、双边沿）
- 串行接口
  - 4路UART模块，具有独立8字节FIFO
  - 2路SPI模块，具有8字节独立FIFO，支持SPI、SSI协议，支持Master/Slave模式
  - 2路I2C模块，支持7位、10位地址方式，支持Master/Slave模式
  - 2路CAN模块，支持协议2.0A(11Bit标识符)和2.0B（29Bit标识符）
  - 1路SDIO模块
  - 1路USB OTG模块
- TFT-LCD驱动模块
  - 支持SYNC接口和MPU接口的外部LCD扩展
  - 支持最高分辨率1024*768，实际分辨率可以配置
  - RGB565和RGB888格式可选
- PWM控制模块
  - 5组16位宽PWM发生器，每组PWM支持4路PWM输出
  - 提供新周期开始中断，高电平结束中断、刹车中断以及中心对称模式下的半周期中断
  - 支持死区控制
  - 支持硬件自动触发 ADC 采样
- 定时器模块
  - 5路32位通用定时器
  - 12路32位基本定时器
  - 32位看门狗定时器，溢出后可配置触发中断或复位芯片
- RTC模块
  - 可自由设置日期（年、月、周、日）和时间（时、分、秒）
  - 可自由设置闹钟（周、时、分、秒）
  - 自动识别当前设置年份是否为闰年
  - 支持RTC中断从Sleep模式下唤醒芯片
- DMA模块
  - 4路DAM，支持特定外设和存储器之间或存储器和存储器之间的数据搬运
- 模拟外设
  - 2路12位高精度SAR ADC
  - 1路12位高精度DAC
  - 3路比较器
  - 4路运算放大器
- 欠压检测（BOD）
  - 支持欠压检测
  - 支持欠压中断和复位选择
- 时钟源
  - 20MHz/40MHz精度可达1%的片内时钟源
  - 32K片内时钟源
  - 2～32MHz片外晶振

芯片更多详细信息请参考[华芯微特技术支持](https://www.synwit.cn/)。

## 编译说明

本 BSP 为开发者提供 MDK5 工程。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 Jlink 仿真器下载程序，在通过 Jlink 连接开发板到 PC 的基础上，点击下载按钮即可下载程序到开发板

推荐熟悉 RT_Thread 的用户使用[env工具](https://www.rt-thread.org/download.html#download-rt-thread-env-tool)，可以在console下进入到 `bsp/synwit/swm341` 目录中，运行以下命令：

`scons`

来编译这个板级支持包。如果编译正确无误，会产生rtthread.elf、rtthread.bin文件。其中 rtthread.bin 可以烧写到设备中运行。

## 烧写及执行

### 硬件连接

- 使用 USB 数据线连接开发板到 PC（注意：需要下载安装串口驱动支持 CH340 芯片，使用 MDK5 需要安装 SWM341 相关的 pack）。

  >  USB 数据线用于串口通讯，同时供电

- 使用 Jlink 连接开发板到 PC （需要 Jlink 驱动）

将串口 0 引脚为：`[PM0/PM1]`和 USB 转串口模块 J8 相连，串口配置方式为115200-N-8-1。

当使用 [env工具](https://www.rt-thread.org/download.html#download-rt-thread-env-tool) 正确编译产生出rtthread.bin映像文件后，可以使用 ISP 的方式来烧写到设备中。

**建议使用 keil 软件直接下载**。ISP 下载较复杂。

### 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到板子上的蓝色LED闪烁。串口打印RT-Thread的启动logo信息：

```
 \ | /
- RT -     Thread Operating System
 / | \     4.1.1 build May 13 2022 10:16:43
 2006 - 2022 Copyright by RT-Thread team
msh >
```
## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设** | **支持情况**  | **备注**                                   |
| :---------- | :----------: | :---------------------------------------- |
| GPIO        |     支持     | 共112个                                    |
| UART        |     支持     | UART0/1/2/3                                |
| ADC         |     支持     | ADC0/1                                     |
| DAC         |     支持     | DAC                                        |
| CAN         |     支持     | CAN0/1                                     |
| TIM         |     支持     | TIM0/1/2/3/4,BTIM0/1/2/3/4/5/6/7/8/9/10/11 |
| I2C         |     支持     | 软件 I2C0/1                                |
| PWM         |     支持     | PWM0/1/2/3/4                               |
| RTC         |     支持     | RTC                                        |
| SPI         |     支持     | SPI0/1                                     |
| WDT         |     支持     | WDT                                        |
| CRC/RNG     |     支持     | CRC/RNG                                    |
| SDIO        |     支持     | SDIO                                       |
| SDRAM       |     支持     | SDRAM                                      |

## 参考资料

* [RT-Thread 文档中心](https://www.rt-thread.org/document/site/)

* [SWM341数据手册](https://www.synwit.cn/)
