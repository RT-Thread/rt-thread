# STM32L476-nucleo 板级支持包

## 1. 简介

[STM32F411-nucleo](http://www.st.com/resource/en/data_brief/nucleo-f411re.pdf) 是由意法半导体推出的搭载Cortex-M4内核的高性能微控制器开发板，包括如下硬件特性：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| [STM32F411RE](http://www.st.com/en/microcontrollers/stm32f411re.html) |
|CPU  | Cortex-M4 |
|主频 | 100MHz |
|Flash| 512kB |
|SRAM | 128KB |

![stm32f411](http://www.st.com/content/ccc/fragment/product_related/rpn_information/product_circuit_diagram/4b/82/41/cc/25/ec/4b/3d/bd_stm32f411xe_512k.jpg/files/bd_stm32f411xe_512k.jpg/_jcr_content/translations/en.bd_stm32f411xe_512k.jpg)

## 2. 编译说明

| 环境         | 说明                                                         |
| ------------ | ------------------------------------------------------------ |
| PC操作系统   | Linux/MacOS/Windows                                          |
| 编译器       | arm-none-eabi-gcc version 6.3.1 20170620 (release)/armcc/    |
| 构建工具     | scons/mdk5                                                  |
| 依赖软件环境 | Env工具/(MDK或arm-none-eabi-gcc)/git/调试器驱动              |

1) 下载源码

```bash
    git clone https://github.com/RT-Thread/rt-thread.git
```

2) 配置工程并准备env

* Windows

>在[RT-Thread官网][1]下载ENV工具包

* Linux/Mac

```bash
    cd rt-thread/bsp/stm32l476-nucleo
    scons --menuconfig
    source ~/.env/env.sh
    pkgs --upgrade
```

3) 生成工程(Mac/Linux下请跳过此步骤)

* Windows MDK5

```bash
    scons --target=mdk5 -s
```

4) 编译

* Windows

使用MDK或IAR请参见对应教程。Windows下使用ENV工具，已经携带GNU GCC工具链，只需要在console下在`bsp/stm32f411-nucleo`目录下使用

```bash
    scons
```

即可编译成功。

* Linux/MAC

请使用以下指令设置gcc路径

```bash
    export RTT_EXEC_PATH=[GCC路径]
```

而后在`rt-thread/bsp/stm32f411-nucleo`目录下使用

```bash
    scons
```

即可编译成功。

GNU GCC编译成功，会在最后有如下类似信息显示：

```bash
    LINK rtthread-stm32f411.elf
    arm-none-eabi-objcopy -O binary rtthread-stm32f411.elf rtthread.bin
    arm-none-eabi-size rtthread-stm32f411.elf
    text    data     bss     dec     hex filename
    55916     208    2456   58580    e4d4 rtthread-stm32f411.elf
    scons: done building targets.
```

并产生rtthread-stm32f411.elf、rtthread.bin文件。其中rtthread.bin为二进制固件

## 3. 烧写及执行

对于STM32F411-Nucleo开发板，在Windows上可以直接把rtthread.bin文件拖到U盘中实现烧写。在Linux下，请查找Linux下如何使用 ST-Link 的教程。

**注：**
如果需要使用Keil MDK来调试GNU GCC编译后的映像文件，可以在编译出`rt-thread/bsp/stm32f411-nucleo/rtthread-stm32f411.elf`后，把这个文件改名成`rtthread-stm32f4xx.axf`，
并放置于build目录下。然后在Keil MDK工程配置的Debug页中，把`Run to main()`选项拿掉，然后直接点击下载或调试即可进行调试（千万别再编译这个工程）。

### 3.1 运行结果

如果编译 & 烧写无误，会在串口2上看到RT-Thread的启动logo信息：

```bash
 \ | /
- RT -     Thread Operating System
 / | \     3.0.4 build May 29 2018
 2006 - 2018 Copyright by rt-thread team
msh >
```

## 4. 驱动支持情况及计划

| 驱动       | 支持情况 | 备注                         |
| ---------- | :------: | :--------------------------: |
| UART       | 支持     | UART2        |

### 4.1 IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| -- | -- |
| PA2 | USART2 TX |
| PA3 | USART2 RX |

## 5. menuconfig Bsp菜单详解

| 选项 | 解释 |
| -- | -- |
| Using UART2 | 开启串口2，设备名为"uart2" |

  [1]: https://www.rt-thread.org/page/download.html
