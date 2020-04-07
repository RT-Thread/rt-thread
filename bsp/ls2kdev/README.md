# loogson_pi2 板级支持包说明

## 1. 简介

2K龙芯派采是首款采用2K1000低功耗处理的嵌入式方案验证板，具有资源丰富、接口齐全、低功耗、高可靠的特点。

| 硬件 | 描述 |
| -- | -- |
|芯片型号| 2K1000 |
|CPU| GS264 |
|主频| 1GHz |
|DDR3| 2GB |
|片外Flash| 8Mb SPI FLASH |

[龙芯派][1]搭载 2K1000 处理器（主频 1GHz），板载 DDR3 颗粒，实现 DDR3 的运行存储功能。实现了 GPIO 的输入输出，中断功能。板上集成 1 个网 口，集成 3 个 USB 接口，HDMI 接口，LCD 接口，音频输入/输出，集成 SD 卡接口，集成 2 个 CAN 接口，集成 RTC 计时功能。可以外扩 WIFI 模块。2K 龙芯派可以广泛应用于信息安 全、电力、轨道交通、工业控制、信号处理、数据通信、信息教育等领域。


## 2. 编译说明

环境搭建在Ubuntu上进行，首先下载[mips-sde-elf-gcc][2]。该文件存放在网盘中，提取码为ucb2。

解压到指定的目录，然后修改当前目录下的`rtconfig.py`文件。

```python
if  CROSS_TOOL == 'gcc':
	PLATFORM    = 'gcc'
	EXEC_PATH   = "/opt/mips-2015.05-19-mips-sde-elf-i686-pc-linux-gnu/mips-2015.05/bin/"
```

然后在控制台输入`scons`即可，可以生成`rtthread.elf`、`rtthread.bin`文件，其中`rtthread.elf`是下载到开发板上的程序。

## 3.程序运行

首先龙芯派开发板必须先运行[pmon][3]。rt-thread是通过龙芯的pmon引导起来的。

![2020-04-07_11-53](figures/loongsonpi.png)

首先板子接上12V的电源，然后连接串口，该串口为RS232，所以需要RS232转USB线来进行连接。接着连接`LAN0`网口。

初次上电时，需要按下开发板的`START`按键，听到`滴`启动声后可以在控制台看到串口打印信息。通过启动时在控制台不停的按下字符`c`直到进入到pmon控制台。

目前在龙芯派上推荐使用PMON通过tftp的方式下载到设备内存中运行。

需要让开发板和主机处于同一网段，利用pmon的tftp进行固件传输。首先查看主机的ip地址，如果`ifconfig`查看ip是`192.168.12.35`。输入以下指令开始运行。

```
ifaddr syn0 192.168.12.100 
load tftp://192.168.12.35/rtthread.elf;
g
```

其中`ifaddr`是设置pmon设置网络的命令，`syn0`表示第一个网卡。然后从tftp的主机上加载`rtthread.elf`文件，此时主机必须有tftp服务器。`g`表示程序跳转运行。

而后可以看到rtthread程序正常的运行。

```
   zero      at       v0       v1       a0       a1       a2       a3   
 00000000 00000000 00000000 00000000 00000003 aafffea8 8f800000 8f1371d0
    t0       t1       t2       t3       t4       t5       t6       t7   
 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
    s0       s1       s2       s3       s4       s5       s6       s7   
 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
    t8       t9       k0       k1       gp       sp       s8       ra   
 00000000 00000000 00000000 00000000 00000000 aafffe88 00000000 8f0b1418
Current SR: 0x10008080

 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Apr  7 2020
 2006 - 2020 Copyright by rt-thread team
Hi, this is RT-Thread!!
msh >
```

## 4. 支持情况

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0|

## 5. 联系人信息

维护人：[bernard][4]
[1]:http://ftp.loongnix.org/loongsonpi/pi_2/doc
[2]: https://pan.baidu.com/s/17dbdOE4NAJ-qEW7drVRq2w
[3]:http://ftp.loongnix.org/embedd/ls2k/
[4]: https://github.com/BernardXiong
