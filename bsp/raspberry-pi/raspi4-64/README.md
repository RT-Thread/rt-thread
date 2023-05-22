# Raspberry PI 4板级支持包说明

## 1. 简介

树莓派4B的核心处理器为博通BCM2711（四核1.5GHz，Cortex A72架构，树莓派3是四核A53）。LPDDR4内存，由5V/3A USB-C供电或GPIO 5V。

外设支持上，引入了双频Wi-Fi，蓝牙5.0，千兆网卡，MIPI CSI相机接口，两个USB口，40个扩展帧。

这份RT-Thread BSP是针对 Raspberry Pi 4的一份移植，树莓派价格便宜, 使用者甚众，是研究和运行RT-Thread的可选平台之一。


## 2. 编译说明

推荐使用[env工具](https://www.rt-thread.org/download.html#download-rt-thread-env-tool)，可以在console下进入到`bsp\raspberry-pi\raspi4-64`目录中，运行以下命令：

```
scons
```

来编译这个板级支持包。如果编译正确无误，会产生 `rtthread.elf`, `rtthread.bin` 文件。

## 3. 环境搭建
### 3.1 准备好串口线

目前版本是使用raspi4的 GPIO 14, GPIO 15来作路口输出，连线情况如下图所示：

![raspi2](../raspi3-32/figures/raspberrypi-console.png)

串口参数： 115200 8N1 ，硬件和软件流控为关。

### 3.2 RTT固件放在SD卡运行

暂时不支持，需要使用 u-boot 加载。

### 3.3 RTT程序用uboot加载

此 bsp 的 `tools` 下可以找到 [u-boot64.bin](./tools/u-boot64.bin) 和 [config.txt](./tools/config.txt) 两个文件。将其与准备好的 sd 卡中文件替换即可。sd 卡推荐通过树莓派 [imager](https://www.raspberrypi.com/software/) 制作。

需要注意的以下步骤：

**1.电脑上启动tftp服务器**

windows系统电脑上可以安装tftpd搭建tftp服务器。将目录指定到`bsp\raspberry-pi\raspi4-64`。

**2.修改设置uboot**

在控制台输入下列命令：

```
setenv bootcmd "dhcp 0x00208000 x.x.x.x:rtthread.bin;dcache flush;go 0x00208000"
saveenv
reset
```

其中`x.x.x.x`为tftp服务器的pc的ip地址。

**3.修改链接脚本**

链接脚本会在 python 脚本中自行替换，不用处理

**3.插入网线**

上述准备完成后，将网线插入，保证开发板和tftp服务器在同一个网段的路由器上。上电后uboot可以自动从tftp服务器上获取固件，然后开始执行了。

完成后可以看到串口的输出信息

```
 \ | /
- RT -     Thread Operating System
 / | \     5.0.0 build Mar 29 2023 10:56:23
 2006 - 2022 Copyright by RT-Thread team
lwIP-2.1.2 initialized!
EMMC: assuming clock rate to be 100MHz
[I/sal.skt] Socket Abstraction Layer initialize success.
[I/utest] utest is initialize success.
[I/utest] total utest testcase num: (0)
[I/DBG] version is B1

[I/SDIO] SD card capacity 31166976 KB.
found part[0], begin: 4194304, size: 256.0MB
found part[1], begin: 272629760, size: 3.856GB
file system initialization done!
cpu 2 boot success
cpu 1 boot success
cpu 3 boot success
msh />
```

## 4. 支持情况

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0,UART2,UART3,UART4,UART5 |
| GPIO | 支持 | - |
| SPI | 支持 | SPI0 |
| MAILBOX | 支持 | - |
| WATCHDOG | 支持 | - |
| HDMI | 支持 | - |
| SDIO | 支持 | - |
| ETH | 支持 | - |

## 5. 注意事项

目前rt-thread程序可以使用的内存在100MB以内，可以通过调整`board.c`中`platform_mem_desc`表的数据进行相关内存的映射以及修改`board.h`来确定程序使用的堆栈大小。

## 6. 联系人信息

维护人：[bernard][5]

[1]: https://www.rt-thread.org/download.html#download-rt-thread-env-tool
[2]: https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads
[3]: https://downloads.raspberrypi.org/raspbian_lite_latest
[4]: https://etcher.io
[5]: https://github.com/BernardXiong
