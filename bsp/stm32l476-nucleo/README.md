# STM32L476-nucleo 板级支持包

## 1. 简介

STM32L476-nucleo 是由意法半导体推出的搭载Cortex-M4内核的高性能低功耗单片机的开发板
包括如下硬件特性：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| STM32L476RGT6 |
|CPU| Cortex-M4 |
|主频| 80MHz |
|Flash|1MB|
|SRAM|96K + 32K|

## 2. 编译说明


| 环境         | 说明                                                         |
| ------------ | ------------------------------------------------------------ |
| PC操作系统   | Linux/MacOS/Windows                                          |
| 编译器       | arm-none-eabi-gcc version 6.3.1 20170620 (release)/armcc/    |
| 构建工具     | scons/mdk5/                                                  |
| 依赖软件环境 | Env工具/(MDK或arm-none-eabi-gcc)/git/调试器驱动              |

1) 下载源码

```bash
    git clone https://github.com/RT-Thread/rt-thread.git
```

2) 配置工程并准备env

（Linux/Mac）

```bash
    cd rt-thread/bsp/stm32l476-nucleo
    scons --menuconfig
    source ~/.env/env.sh
    pkgs --upgrade
```

（Windows）

>在[RT-Thread官网][1]下载ENV工具包

4) 生成工程(Mac/Linux下请跳过此步骤)

（Windows MDK5）*

```bash
    scons --target=mdk5 -s
```

*该板级支持包不支持生成mdk4的工程

5) 编译

使用MDK或IAR请参见对应教程

（Windows arm-none-eabi-gcc）
使用以下指令设置gcc路径

```bash
    SET RTT_EXEC_PATH=[GCC路径]
```

（Linux/Mac arm-none-eabi-gcc）
使用以下指令设置gcc路径

```bash
    export RTT_EXEC_PATH=[GCC路径]
```

编译（Windows/Linux/Mac arm-none-eabi-gcc）

```bash
    scons -j4
```

出现下列信息即为编译成功

```bash
    LINK rtthread-stm32l476.elf
    arm-none-eabi-objcopy -O binary rtthread-stm32l476.elf rtthread.bin
    arm-none-eabi-size rtthread-stm32l476.elf
    text    data     bss     dec     hex filename
    41596     356    1456   43408    a990 rtthread-stm32l476.elf
    scons: done building targets.
```


如果编译正确无误，会产生rtthread-stm32l476.elf、rtthread.bin文件。其中rtthread.bin为二进制固件

## 3. 烧写及执行

烧写可以使用仿真器 ISP等多种方式 此处不再赘述

### 3.1 运行结果

如果编译 & 烧写无误，会在串口2*上看到RT-Thread的启动logo信息：

```bash
 \ | /
- RT -     Thread Operating System
 / | \     3.0.4 build May 15 2018
 2006 - 2018 Copyright by rt-thread team
msh />
```

*默认串口


## 4. 驱动支持情况及计划

| 驱动       | 支持情况 | 备注                         |
| ---------- | :------: | :--------------------------: |
| UART       | 支持     | UART1/2/3/4/5/LPUART1        |
| GPIO       | 支持     | /                            |


### 4.1 IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| -- | -- |
| PC0 | LPUART1_RX |
| PC1 | LPUART1_TX |
| PA9 | USART1 TX |
| PA10 | USART1 RX |
| PA2 | USART2 TX |
| PA3 | USART2 RX |
| PC4 | USART3_TX |
| PC5 | USART3_RX |
| PA0 | USART4_TX |
| PA1 | USART4_RX |
| PC12 | UART5 TX |
| PD2  | UART5 RX |

## 5. menuconfig Bsp菜单详解

| 选项 | 解释 |
| -- | -- |
| using uart1 | 开启串口1，串口1的设备名为"uart1" |
| using uart2 | 开启串口2，串口1的设备名为"uart2" |
| using uart3 | 开启串口3，串口1的设备名为"uart3" |
| using uart4 | 开启串口4，串口1的设备名为"uart4" |
| using uart5 | 开启串口5，串口1的设备名为"uart5" |
| using lpuart1 | 开启低功耗串口1，低功耗串口1的设备名为"lpuart1" |

*部分选项需要在RT-Thread组件菜单中开启对应的设备框架才能显示。

## 6. 联系人信息

维护人:
[uestczyh222][4] < [lymz@foxmail.com][5] >

  [1]: https://www.rt-thread.org/page/download.html
  [4]: https://github.com/uestczyh222
  [5]: mailto:lymz@foxmail.com
