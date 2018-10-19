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
| 编译器       | arm-none-eabi-gcc version 6.3.1 20170620 (release) |
| 构建工具     | scons                                               |
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

>在[RT-Thread官网][1]下载ENV工具包，并参考官网给出的env使用教程

3) 配置工程（可选）

（Linux/Mac）

```bash
    scons --menuconfig
```

（Windows(ENV环境中)）

```bash
    menuconfig
```

4) 下载package

amebaz配套的驱动库以package形式提供，故需先下载对应的package(realtek-ameba)，请使用env下载package

```bash
    pkgs --update
```

*该板级支持包不支持生成mdk的工程及iar工程，后续会支持iar工程

5) 编译

Windows可以使用env编译工程，无需设置GCC工具链路径，直接在bsp/amebaz工程目录下编译即可。

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

## 4. WIFI简单使用


### 4.1 wifi扫描命令

wifi 扫描命令格式如下

```unknown
 wifi scan
```

命令说明  

| 字段 | 描述                     |
| ---- | ------------------------ |
| wifi | 有关wifi命令都以wifi开头 |
| scan | wifi执行扫描动作         |

在调试工具中输入该命令，即可进行 wifi 命令扫描，调试信息如下

```unknown

scan ap down
             SSID                      MAC              security    rssi   chn    Mbps
------------------------------- -----------------    -------------- ----   ---    ----
NEO-shanghai-ap2                58:66:ba:a1:ee:71    WPA2_TKIP_PSK   -74    11    0
WQ1                             88:25:93:94:51:54    WPA2_AES_PSK    -76    13    0
shyc1                           a0:40:a0:a3:e8:c9    WPA2_AES_PSK    -77    13    0
KVIP                            70:65:82:3b:71:43    WPA2_AES_PSK    -83    11    0
YST2016                         88:25:93:c6:67:d1    WPA2_TKIP_PSK   -84     4    0

```

> 注：
>
> 测试命令有关 wifi,均以wifi开头。

### 4.2 wifi 接入

接入 wifi 之前，先介绍一下其接入的命令 ，如下

```unknown
 wifi join ssid 123456789
```

命令说明

| 字段      | 描述                               |
| --------- | ---------------------------------- |
| wifi      | 有关wifi命令都以wifi开头           |
| join      | wifi执行连接动作                   |
| ssid      | 热点的名字                         |
| 123456789 | 热点的密码，没有密码可不输入这一项 |

了解上述命令，并且成功完成前面步骤，在串口中输入 `wifi w0 join realthread_VIP 123456789` ，如下日志表示连接成功

```unknown

WIFI  wlan0 Setting:
==============================
      MODE => STATION
      SSID => realthread_VIP
   CHANNEL => 6
  SECURITY => AES
  PASSWORD => 123456789
[I/WLAN.mgnt] wifi connect success ssid:realthread_VIP

```

另外，提供一个简单的测试使用命令，查询设备IP地址命令：ifconfig。

```unknown

network interface: w0 (Default)
MTU: 1500
MAC: 00 e0 4c d5 ac 46
FLAGS: UP LINK_UP ETHARP BROADCAST
ip address: 172.16.200.110
gw address: 172.16.200.1
net mask  : 255.255.255.0
dns server #0: 172.16.200.1
dns server #1: 223.5.5.5

```

## 5. 驱动支持情况及计划

| 驱动       | 支持情况 | 备注                         |
| ---------- | :------: | :--------------------------: |
| UART       | 支持     | UART0                        |
| WLAN       | 部分支持 | 仅支持STA模式                |

## 6. 已知问题

wlan仅支持STA模式，连接WIFI输入错误密码时，会宕机。

## 7. 联系人信息

维护人:
[flyingcys][4] < [flyingcys@163.com][5] >

  [1]: https://www.rt-thread.org/page/download.html
  [4]: https://github.com/flyingcys
  [5]: mailto:flyingcys@163.com
