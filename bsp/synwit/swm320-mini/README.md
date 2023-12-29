# SWM320 BSP 说明

标签： SYNWIT、Cortex-M4、SWM320、国产MCU

---

## 简介

本文档为SWM320开发板提供的 BSP (板级支持包) 说明。

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。

## 芯片介绍

- 内核
  - 32位ARM® Cortex™-M4 内核
  - 24位系统定时器
  - 工作频率最高120MHz
  - 硬件单周期乘法
  - 集成嵌套向量中断控制器（NVIC），提供最多240个、8级可配置优先级的中断
  - 通过SWD接口烧录
- 内置LDO
  - 供电电压范围为2.0V至3.6V
- 片上SRAM存储器
  - 128KB
- 片上FLASH存储器
  - 128KB/256KB/512KB
  - 支持用户定制ISP（在系统编程）更新用户程序
- 串行接口
  - UART模块，具有独立8字节FIFO，最高支持主时钟16分频
  - SPI模块，具有8字节独立FIFO，支持SPI、SSI协议，支持Master/slave模式
  - I2C模块，支持7位、10位地址方式，支持Master/slave模式
  - CAN模块，支持协议2.0A(11Bit标识符)和2.0B（29Bit标识符）
- PWM控制模块
  - 12通道16位PWM产生器
  - 可设置高电平结束或周期开始两种条件触发中断
  - 具有普通、互补、中心对称等多种输出模式
  - 支持死区控制
  - ADC采样触发
- 定时器模块
  - 6路32位通用定时器
  - 具备独立中断
  - 可做计数器使用
  - 支持输入单脉冲捕获功能
  - 32位看门狗定时器，溢出后可配置触发中断或复位芯片
- RTC模块
  - 可自由设置日期（年、月、周、日）和时间（时、分、秒）
  - 可自由设置闹钟（周、时、分、秒）
  - 自动识别当前设置年份是否为闰年
  - 支持RTC中断从Sleep模式下唤醒芯片
- DMA模块
  - 支持存储器到存储器之间的数据搬运
- SRAMC模块
  - 支持8位数据位宽和16位数据位宽的外部SRAM存储器
  - 最大支持24位地址线
- SDRAMC模块
  - 支持16Bit位宽的SDRAM
  - 支持兼容PC133标准的SDRAM颗粒
  - 支持2MB到32MB的外部SDRAM颗粒
- NORFLC模块
  - 支持并行NOR FLASH接口
  - 支持8位数据位宽和16位数据位宽的外部NOR FLASH存储器
  - 最大支持24位地址线
- SDIO接口模块
  - 支持标准SDIO接口协议
- TFT-LCD驱动模块
  - 支持SYNC接口的外部LCD扩展
  - 支持最高分辨率1024*768，实际分辨率可以配置
  - 输出数据宽度16Bit
  - 支持横屏和竖屏模式
- GPIO
  - 最多可达100个GPIO
  - 可配置2种IO模式
  - 上拉输入
  - 下拉输入
  - 灵活的中断配置
  - 触发类型设置（边沿检测、电平检测）
  - 触发电平设置（高电平、低电平）
  - 触发边沿设置（上升沿、下降沿、双边沿）
- 模拟外设
  - 最多2个12位8通道高精度SAR ADC
  - 采样率高达1M SPS
  - 内建参考电压
  - 支持single、scan两种模式
  - 独立的结果寄存器
  - 提供独立FIFO
  - 可由软件、PWM触发
- 欠压检测（BOD）
  - 支持欠压检测
  - 支持欠压中断和复位选择
- 时钟源
  - 20MHz/40MHz精度可达1%的片内时钟源
  - 32K片内时钟源
  - 2～32MHz片外晶振

芯片更多详细信息请参考[华芯微特技术支持](http://www.synwit.cn/support-1/3.html)。

## 编译说明

本 BSP 为开发者提供 MDK5 工程。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 Jlink 仿真器下载程序，在通过 Jlink 连接开发板到 PC 的基础上，点击下载按钮即可下载程序到开发板

推荐熟悉 RT_Thread 的用户使用[env工具](https://www.rt-thread.org/download.html#download-rt-thread-env-tool)，可以在console下进入到 `bsp/synwit/swm320` 目录中，运行以下命令：

`scons`

来编译这个板级支持包。如果编译正确无误，会产生rtthread.elf、rtthread.bin文件。其中 rtthread.bin 可以烧写到设备中运行。

## 烧写及执行

### 硬件连接

- 使用 USB B-Type 数据线连接开发板到 PC（注意：需要下载安装串口驱动支持 CH340 芯片，使用 MDK5 需要安装 SWM320 相关的 pack）。

  >  USB B-Type 数据线用于串口通讯，同时供电

- 使用 Jlink 连接开发板到 PC （需要 Jlink 驱动）

将串口 1 引脚为：`[PC2/PC3]`和 USB 转串口模块 J11 相连，串口配置方式为115200-N-8-1。

当使用 [env工具](https://www.rt-thread.org/download.html#download-rt-thread-env-tool) 正确编译产生出rtthread.bin映像文件后，可以使用 ISP 的方式来烧写到设备中。

**建议使用 keil 软件直接下载**。ISP 下载较复杂。

### 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到板子上的蓝色LED闪烁。串口打印RT-Thread的启动logo信息：

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.0 build Dec 11 2018
 2006 - 2018 Copyright by rt-thread team
msh />
```
## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设**        | **支持情况**  | **备注**                              |
| :----------------- | :----------: | :----------------------------------- |
| GPIO               |     支持     | PA0, PA1... PP23 ---> PIN: 0, 1...100 |
| UART               |     支持     | UART0/1/2/3                           |
| ADC                |     支持     | ADC0/1                                |
| TIM                |     支持     | TIM0/1/2/3/4/5                        |
| I2C                |     支持     | 软件 I2C0/1                            |
| PWM                |     支持     | PWM0/1/2/3/4/5                        |
| RTC                |     支持     | RTC                                   |
| SPI                |     支持     | SPI0/1                                |
| WDT                |     支持     | WDT                                   |
| CRC                |     支持     | CRC                                   |
| SDIO               |     支持     | SDIO                                  |
| SRAM               |     支持     | SRAM                                  |
| NOR FLASH          |     支持     | NOR FLASH                             |
| CAN                |    暂不支持   |                                       |

## 参考资料

* [RT-Thread 文档中心](https://www.rt-thread.org/document/site/)

* [SWM320数据手册](https://www.synwit.cn/col.jsp?id=155)
