# amebaz on RT-Thread

## 1. 简介

amebaz 是由Realtek推出的Cortex-M4内核的WiFi SOC芯片rtl8710b系列
包括如下硬件特性：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| amebaz |
|CPU| Cortex-M4 |
|主频| 125MHz |

## 2. 编译说明


| 环境         | 说明                                                         |
| ------------ | ------------------------------------------------------------ |
| PC操作系统   | Linux/MacOS/Windows                                          |
| 编译器       | arm-none-eabi-gcc version 6.3.1 20170620 (release)/iar |
| 构建工具     | scons/iar                                               |
| 依赖软件环境 | Env工具/(IAR或arm-none-eabi-gcc)/git/调试器驱动         |

1) 下载源码

```bash
    git clone https://github.com/RT-Thread/rt-thread.git
```

2) 配置工程并准备env

（Linux/Mac）

```bash
    cd rt-thread/bsp/amebaz
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

在menuconfig页面配置并选择对应的芯片型号，若开发环境为IAR，则需要生成工程

4) 下载package

amebaz配套的驱动库以package形式提供，故需先下载对应的package(realtek-ameba)，请使用env下载package

```bash
    pkgs --update
```

5) 生成工程(Mac/Linux下请跳过此步骤)

（Windows IAR）

```bash
    SET RTT_CC=iar
    scons --target=iar -s
```

*该板级支持包不支持生成mdk的工程


6) 编译

使用IAR请参见对应教程

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
LINK rtthread.axf
arm-none-eabi-objcopy -j .ram_image2.entry -j .ram_image2.data -j .ram_image2.bss -j .ram_image2.skb.bss -j .ram_heap.data -Obinary rtthread.axf ram_2.r.bin
arm-none-eabi-objcopy -j .xip_image2.text -Obinary rtthread.axf xip_image2.bin
arm-none-eabi-objcopy -j .ram_rdp.text -Obinary rtthread.axf rdp.bin
python gen_bin.py
is_law = 1
start = 10005000, end = 0, base = 10000000
Input file size: 65852
copy size 45372
start = 10005000, end = 0, base = 10000000
Input file size: 45372
copy size 24892
start = 0, end = 0, base = 0
Input file size: 336816
copy size 336816
size = 361772
checksum 209b36c
'true' is not recognized as an internal or external command,
operable program or batch file.
Done...
scons: done building targets.
```

如果编译正确无误，会产生image2_all_ota1.bin文件。

## 3. 烧写及执行

烧写可以使用仿真器 串口等多种方式 此处不再赘述

### 3.1 运行结果

如果编译 & 烧写无误，会在专用日志串口*上看到RT-Thread的启动logo信息：

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
| UART       | 支持     | UART0                   |


## 5. 联系人信息

维护人:
[flyingcys][4] < [flyingcys@163.com][5] >

  [1]: https://www.rt-thread.org/page/download.html
  [4]: https://github.com/flyingcys
  [5]: mailto:flyingcys@163.com
