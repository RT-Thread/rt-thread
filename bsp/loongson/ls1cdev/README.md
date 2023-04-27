龙芯1C板级支持包


---

## 1. 简介

龙芯1C是基于GS232处理器核的高性价比单芯片系统，可应用于工业控制及物联网等领域。龙芯1C包含浮点处理单元，支持多种类型的内存，支持高容量的MLC NAND Flash。龙芯1C为开发者提供了丰富的外设接口及片上模块，包括Camera控制器、USB OTG及USB HOST接口、AC97/I2S控制器、LCD控制器、SPI接口、UART接口等，提供足够的计算能力和多应用的连接能力。

此BSP基于龙芯俱乐部推出的智龙开发板，包括如下硬件特性：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| 1C300A/1C300B |
|CPU| GS232 |
|主频| 300MHz |
|片外SDRAM| 32MB |
|片外Flash| 128MB NandFlash、512K NorFlash |

## 2. 编译说明

Windows平台推荐使用[env工具][1]。龙芯1C的LS232处理器核是一款MIPS32兼容处理器，由于env工具中并未默认携带MIPS的工具链，需要下载如下工具链：

* [mips-2015.05-19-mips-sde-elf.exe][2]

安装好工具链后，假设工具链安装在`D:\mgc\embedded\codebench`目录下。使用env工具，打开console后，进入到命令行环境中，需要手动设置工具链的环境变量`RTT_EXEC_PATH`：

```
    set RTT_EXEC_PATH=D:\mgc\embedded\codebench\bin
```

使用env工具，可以在console下进入到`bsp/ls1cdev`目录中，运行以下命令：

```
    scons
```

或者通过 `scons --exec-path="GCC工具链路径"` 命令，在指定工具链位置的同时直接编译，推荐使用该方法。

来编译这个板级支持包。如果编译正确无误，会产生rtthread.elf、rtthread.bin文件。

## 3. 烧写及执行

连接好串口，PC上使用终端软件以115200-N-8-1的配置方式连接到设备上。设备使用的串口引脚是：`[GPIO36/GPIO37]`

目前在智龙上推荐使用PMON通过tftp的方式下载到设备内存中运行。

智龙上电按下非enter键，进入PMON命令行

```
PMON> ifaddr syn0 192.168.1.100
PMON> load tftp://192.168.1.5/rtthread.elf
PMON> g
```

### 3.1 运行结果

如果编译 & 烧写无误，会在串口上看到RT-Thread的启动logo信息：

```

 \ | /
- RT -     Thread Operating System
 / | \     3.0.4 build May 10 2018
 2006 - 2018 Copyright by rt-thread team
eth_inited!
lwIP-1.4.1 initialized!
msh />Link is up in FULL DUPLEX mode
Link is with 100M Speed

```

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | 仅注册UART2，其他UART引脚未固定 |
| IIC | 支持 |  |
| SPI | 支持 |  |
| GPIO | 支持 |  |
| ETH | 支持 | RMII |

### 4.1 IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| -- | -- |
| 调试串口 | GPIO36/GPIO37 |

## 5. 联系人信息

维护人：

- [zhuangwei123](https://github.com/zhuangwei123)

## 6. 参考

* 1C芯片[用户手册][3]
* 1C芯片[数据手册][4]

  [1]: https://www.rt-thread.org/download.html#download-rt-thread-env-tool
  [2]: https://sourcery.mentor.com/GNUToolchain/package13851/public/mips-sde-elf/mips-2015.05-19-mips-sde-elf.exe
  [3]: http://www.loongson.cn/uploadfile/cpu/1C/Loongson_1C300_user.pdf
  [4]: http://www.loongson.cn/uploadfile/cpu/1C/Loongson_1C300_data.pdf
