# STM32F4xx-HAL 板级支持包

## 1. 简介

STM32F4 是由意法半导体推出的Cortex-M4内核的高性能单片机
包括如下硬件特性：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| STM32F4全系列 |
|CPU| Cortex-M4 |
|主频| 84MHz-208MHz |

## 2. 编译说明


| 环境         | 说明                                                         |
| ------------ | ------------------------------------------------------------ |
| PC操作系统   | Linux/MacOS/Windows                                          |
| 编译器       | arm-none-eabi-gcc version 6.3.1 20170620 (release)/armcc/iar |
| 构建工具     | scons/mdk5/iar                                               |
| 依赖软件环境 | Env工具/(MDK或IAR或arm-none-eabi-gcc)/git/调试器驱动         |

1) 下载源码

```bash
    git clone https://github.com/RT-Thread/rt-thread.git
```

2) 配置工程并准备env

（Linux/Mac）

```bash
    cd rt-thread/bsp/stm32f4xx-HAL
    scons --menuconfig
    source ~/.env/env.sh
    pkgs --upgrade
```

（Windows）

>在[RT-Thread官网][1]下载ENV工具包

3) 配置芯片型号

（Linux/Mac）

```bash
    scons --menuconfig
```

（Windows(ENV环境中)）

```bash
    menuconfig
```

在menuconfig页面配置并选择对应的芯片型号，若开发环境为MDK/IAR，则需要生成工程

4) 生成工程(Mac/Linux下请跳过此步骤)

（Windows IAR）

```bash
    SET RTT_CC=iar
    scons --target=iar -s
```

（Windows MDK5）*

```bash
    scons --target=mdk5 -s
```

*该板级支持包不支持生成mdk4的工程

**MDK 与 IAR 在生成完成工程之后一定要在工程中手动选择一次芯片信号，否则会产生严重编译错误**

![figure1](https://raw.githubusercontent.com/RT-Thread/rt-thread/master/bsp/stm32f4xx-HAL/figures/figure1.png)

![figure2](https://raw.githubusercontent.com/RT-Thread/rt-thread/master/bsp/stm32f4xx-HAL/figures/figure2.png)

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

编译（WindowsLinux/Mac arm-none-eabi-gcc）

```bash
    scons -j4
```

出现下列信息即为编译成功

```bash
    LINK rtthread-stm32f4xx.elf
    arm-none-eabi-objcopy -O binary rtthread-stm32f4xx.elf rtthread.bin
    arm-none-eabi-size rtthread-stm32f4xx.elf
    text    data     bss     dec     hex filename
    41596     356    1456   43408    a990 rtthread-stm32f4xx.elf
    scons: done building targets.
```


如果编译正确无误，会产生rtthread-stm23f4xx.elf、rtthread.bin文件。其中rtthread.bin为二进制固件

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
| UART       | 支持     | UART1/2/6                    |
| GPIO       | 支持     | 自动根据芯片型号选择引脚布局 |
| SPI        | 支持     | SPI1/2/3                     |
| SPI Flash  | 支持     | W25QXX                      |
| USB Device | 支持     | OTGFS,暂不支持OTGHS          |
| USB Host   | 支持     | OTGFS,暂不支持OTGHS          |
| IWG        | 支持     | /                            |
| I2c        | 支持     | 软件I2C                      |
| RTC        | 支持     | RTC时钟自动配置              |


### 4.1 IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| -- | -- |
| PB6 | I2C SCL |
| PB7 | I2C SDA |
| PA9 | USART1 TX |
| PA10 | USART1 RX |
| PA2 | USART2 TX |
| PA3 | USART2 RX |
| PC6 | USART6 TX |
| PC7 | USART6 RX |
| PA5 | SPI1 SCK |
| PA6 | SPI1 MISO |
| PA7 | SPI1 MOSI |
| PB13 |SPI2 SCK |
| PB14 |SPI2 MISO |
| PB15 |SPI2 MOSI |
| PC10 |SPI3 SCK |
| PC11 |SPI3 MISO |
| PC12 |SPI3 MOSI |

## 5. menuconfig Bsp菜单详解

| 选项 | 解释 |
| -- | -- |
| Device type | 选择芯片型号，修改此处需修改MDK/IAR工程为相同芯片型号 |
| Using HSI as clock source | 不使用外部时钟源，该选项目前不能开启 |
| HSE Value | 外部时钟源的频率，单位(HZ) |
| System Clock Value | 系统时钟频率，该值会自动计算时钟树，某些特定频率下无法通过PLLQ产生48M时钟，可能导致USB SDIO等设备时钟异常，可使用STM32 Cube MX工具配置需要的时钟树替换board.c中的时钟初始化部分 |
| Using UART1 | 开启串口1，串口1的设备名为"uart1" |
| Using UART2 | 开启串口2，串口1的设备名为"uart2" |
| Using UART6 | 开启串口6，串口1的设备名为"uart6" |
| Using SPI1 | 开启SPI1，设备名为"spi1" |
| Using SPI2 | 开启SPI2，设备名为"spi2" |
| Using SPI3 | 开启SPI3，设备名为"spi3" |
| W25QXX CS Pin index | SPI flash 的片选，接入单片机的引脚号 |
| W25QXX Spi bus name | SPI flash 所使用的总线设备名称 |
| USB Host Config | USB主机模式的配置菜单 |
| using a gpio control usb power | 根据具体硬件，选择是否使用一个GPIO来控制USB主机的电源开启 |
| power control pin | 控制USB主机的电源控制引脚号 |
| current check pin | USB主机的电流过载检测引脚号 |
| using vbus check pin | 选择是否开启USB VBUS检测 |

*部分选项需要在RT-Thread组件菜单中开启对应的设备框架才能显示。

## 6. 联系人信息

维护人:
[uestczyh222][4] < [lymz@foxmail.com][5] >

  [1]: https://www.rt-thread.org/page/download.html
  [4]: https://github.com/uestczyh222
  [5]: mailto:lymz@foxmail.com
