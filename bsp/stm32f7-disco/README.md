# STM32F769-DISCO 板级支持包

## 1. 简介

STM32F769-DISCO 是由意法半导体推出的搭载Cortex-M7内核的高性能单片机的开发板
包括如下硬件特性：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| STM32F769NI |
|CPU| Cortex-M7 |
|主频| 216MHz |
|Flash|2MB|
|SRAM|512K|

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
    cd rt-thread/bsp/stm32f7-disco
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

（Windows IAR）

```bash
    scons --target=iar -s
```

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
    LINK rtthread.elf
    arm-none-eabi-objcopy -O binary rtthread.elf rtthread.bin
    arm-none-eabi-size rtthread.elf
    text    data     bss     dec     hex filename
    41596     356    1456   43408    a990 rtthread.elf
    scons: done building targets.
```


如果编译正确无误，会产生rtthread.elf、rtthread.bin文件。其中rtthread.bin为二进制固件

## 3. 烧写及执行

烧写可以使用仿真器 ISP等多种方式 此处不再赘述

### 3.1 运行结果

如果编译 & 烧写无误，会在串口1*上看到RT-Thread的启动logo信息：

```bash
 \ | /
- RT -     Thread Operating System
 / | \     3.0.4 build May 15 2018
 2006 - 2018 Copyright by rt-thread team
msh />
```

*默认串口


## 4. 驱动支持情况及计划

| 驱动       | 支持情况 | 备注                               |
| ---------- | :------: | :--------------------------------: |
| UART       | 支持     | UART1/4/5/7                        |
| cache      | 支持     | /                                  |
| MPU        | 支持     | SRAM cache使能权限全开 SDRAM未配置 |
| SDRAM      | 支持     | /                                  |


### 4.1 IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| -- | -- |
| PA9 | USART1 TX |
| PA10 | USART1 RX |
| PA0 | UART4 TX |
| PC11 | UART4 RX |
| PC12 | UART5 TX |
| PB8 | UART5 RX |
| PA15 | UART7 TX |
| PA8  | UART7 RX |

## 5. menuconfig Bsp菜单详解

| 选项 | 解释 |
| -- | -- |
| Using SDRAM | 使能SDRAM 若开启RT_USING_MEMHEAP_AS_HEAP 可作为heap使用 默认开启 |
| using uart1 | 开启串口1，串口1的设备名为"uart1" |
| using uart4 | 开启串口2，串口1的设备名为"uart4" |
| using uart5 | 开启串口3，串口1的设备名为"uart5" |
| using uart7 | 开启串口4，串口1的设备名为"uart7" |

## 6. 联系人信息

维护人:
[uestczyh222][4] < [lymz@foxmail.com][5] >

  [1]: https://www.rt-thread.org/page/download.html
  [4]: https://github.com/uestczyh222
  [5]: mailto:lymz@foxmail.com
