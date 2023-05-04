#  Seeed i.MX RT1052 Arch Mix 开发板 BSP 说明

## 简介

![Arch_Mix](figures/Arch_Mix.jpg)

Arch Mix 是 [Seeed Studio](https://www.seeedstudio.com/) 推出的一款基于 i.MX RT 1050 系列芯片的开发板，板载一颗 RGB 灯和一个用户按键，外扩 32M SDRAM，板载资源丰富，运行速度快（主频可达 600MHZ），并且支持外接 LCD 屏幕。Seeed Studio 是一家致力于促进开源硬件发展的服务型企业。目前，已经与众多设计者建立了紧密的合作关系，并且合作推出了涉及新媒体艺术、嵌入式平台、物联网、智能家居、便携式仪器等领域的一系列明星产品和方案。

### 板载资源：

| 硬件 | 描述 |
| ---- | ---- |
| 芯片 | i.MX RT 1052 |
| 架构 | ARM Cortex-M7 |
| 最高频率 | 600MHz |
| 内部存储器 | 512KB  SRAM |
| 外部存储器 | 32M SDRAM、8M QSPI FLASH（存储代码） |

## 编译说明

Arch Mix 板级包支持MDK5﹑IAR开发环境和GCC编译器，以下是具体版本信息：

| IDE/编译器 | 已测试版本 |
| ---------- | --------- |
| MDK5 | MDK525 |
| IAR | IAR 8.11.3.13984 |
| GCC | GCC 5.4.1 20160919 (release) |

## BSP使用

### 配置工程

- 在 bsp 下打开 env 工具
- 输入`menuconfig`命令配置工程，配置好之后保存退出。
- 输入`scons --target=mdk5 -s`或`scons --target=iar`来生成需要的工程

### 下载和仿真

开发板支持 SWD 调试接口，连接外置仿真器后，就可以进行下载和仿真。

> 注意：下载算法默认使用 board目录下的 MIMXRT105x_QuadSPI_4KB_SEC.FLM 文件，将此文件拷贝到 Keil5安装目录下 `ARM\Flash` 目录下即可。
>
> 下载失败时：先按下 `Reset 按键`，再按下 `Boot Mode 按键`，先松开 `Reset 按键`，再松开 `Boot Mode 按键`，即可进入`下载模式`。

### 运行结果

下载程序成功之后，系统会自动运行，观察开发板上 LED 的运行效果，绿色 DS1 会周期性闪烁。

使用 TTL 转串口工具连接开发板上 RXD/TXD ，在终端工具里打开相应的串口(115200-N-8-1)。如果编译 & 烧写无误，当复位设备后，可以看到RT-Thread的输出信息:

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build May  7 2021
 2006 - 2021 Copyright by rt-thread team
msh >
```

## 驱动支持情况及计划

| 驱动 | 支持情况  | 备注 |
| ------ | ----  | ------ |
| UART | 支持 | UART 1 |
| GPIO | 支持 | GPIO1~GPIO5 |
| IIC | 暂不支持 |  |
| SPI | 暂不支持 |                                        |
| LCD | 暂不支持 |  |
| RTC | 暂不支持 |  |
| SDIO | 暂不支持 |  |
| SDRAM | 支持 | 32M SDRAM，后面 2M 作为 Non Cache 区域 |

## 联系人信息

维护人：

- [guozhanxin](https://github.com/Guozhanxin)
