# AXU4EV-E 开发板 BSP 说明

## 简介

本文档是为 AXU4EV-E 开发板提供的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 RT-Thread 驱动更多板载资源。

## 开发板介绍

AXU4EV-E 开发板是 芯驿电子科技（上海）有限公司 推出的一款基于 XILINX Zynq UltraScale+ MPSoCs 开发平台的开发板。这款 MPSoCs 开发平台采用核心板加扩展板的模式，方便用户对核心板的二次开发利用。核心板使用 XILINX Zynq UltraScale+ EV 芯片 ZU4EV 的解决方案，它采用Processing System(PS)+Programmable Logic(PL)技术将四核ARM Cortex-A53 和FPGA 可编程逻辑集成在一颗芯片上。另外核心板上 PS 端带有 4 片共 4GB 高速 DDR4 SDRAM 芯片，1 片 8GB的 eMMC 存储芯片和 1 片 256Mb 的 QSPI FLASH 芯片；核心板上 PL 端带有 1 片 1GB 的DDR4 SDRAM 芯片 。

开发板更多详细信息请参考[芯驿电子科技（上海）有限公司](http://www.alinx.cn/)。

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **核心**      | **支持情况** | **备注**                              |
| :----------------- | :----------: | :------------------------------------- |
| R5-CPU0   |     支持     | 运行系统的为R5核的CPU0 |
| **板载外设**      | **支持情况** | **备注**                              |
| 无 |          |  |
| **片上外设**      | **支持情况** | **备注**                              |
| GPIO              |     支持     |  |
| UART              |     支持     | UART0                            |
| TIMER     |     支持     |     TTC0提供系统时钟         |
| EMMC | 支持 | SD0控制器 |
| EMAC | 支持 | e0网卡 |

## 使用说明

使用说明分为如下两个章节：

- 快速上手

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

    本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。


### 快速上手

本 BSP 为仅支持 GCC 开发环境，下面介绍如何将系统运行起来。

#### 编译下载

1. 在 bsp 下打开 env 工具，输入`scons`进行编译。

2. 编译完成后在 bsp 目录下会生成 `rtthread-zynqmp-r5.elf` 文件。

3. 使用 Xilinx Vitis 产生 FSBL，然后创建 “Debug Configuration”，Application 选择`rtthread-zynqmp-r5.elf` 文件。

4. 使用调试器连接 PC 和开发板，通过拨码开关设置为 JTAG 启动，然后连接电源，点击开始调试或运行即可。

   由于编译时默认带有调试信息（见 rtconfig.py 中 BUILD），所以在 Xilinx Vitis 中调试时同样可以打开源文件设断点进行调试。

#### 固化程序

1. 在 bsp 下打开 env 工具，输入`scons`进行编译。

2. 编译完成后在 bsp 目录下会生成 `rtthread-zynqmp-r5.elf` 文件。

3. 使用 Xilinx Vitis 或 Xilinx SDK 产生 FSBL，然后使用 Xilinx 提供的 bootgen 工具制作 BOOT.bin 文件。

   例如使用命令行方式：

   ```
    bootgen -image ./output.bif -arch zynqmp -o ./BOOT.bin -w on
   ```
   
   其中 output.bif 文件可以是：
   ```
   //arch = zynqmp; split = false; format = BIN
   the_ROM_image:
   {
        [bootloader, destination_cpu = r5-0]./fsbl.elf
        [destination_cpu = r5-0, exception_level = el-3]./rtthread-zynqmp-r5.elf
   }
   ```
   
4. 根据 ALINX 提供的文档将 BOOT.bin 放进SD卡或烧录到 QSPI FLASH 中，通过拨码开关设置启动方式，然后连接电源即可启动。


#### 运行结果

下载程序成功之后，系统会自动运行。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Nov 27 2020
 2006 - 2020 Copyright by rt-thread team
msh />
```

### 进阶使用

此 BSP 默认开启了 EMMC 驱动和 DFS 文件系统，如果需要使用文件系统可以自行格式化并挂载。

此 BSP 默认开启并配置了网卡驱动及lwip协议栈，相关配置需要注意如下几点：

1. 注意将`RT_LWIP_PBUF_NUM`至少设置为256
2. 注意将`RT_LWIP_MEM_ALIGNMENT`设置为32。若使用RTT中lwip 2.0.2以外的版本时，由于其他版本未使用该宏，需要手动修改`lwipopts.h`中的`MEM_ALIGNMENT`宏。


## 板级移植

如果需要将BSP移植到其他 XILINX Zynq UltraScale+ MPSoCs 开发平台的开发板上也比较方便，主要修改的地方有以下几点：

1. 内存： 如果 DDR memory 小于 2G，需要修改`zynqmp-r5.ld`链接文件中的`psu_r5_ddr_0_MEM_0` 以及`board.h`中的`HEAP_END`
2. 主频： `xparameters.h`中的`XPAR_CPU_CORTEXR5_0_CPU_CLK_FREQ_HZ`
3. 串口引脚和频率：`drv_uart.c`中的`rxmio`, `txmio` 和`xparameters.h`中的`XPAR_PSU_UART_0_UART_CLK_FREQ_HZ`
4. 定时器频率：`xparameters.h`中的`XPAR_PSU_TTC_0_TTC_CLK_FREQ_HZ` 
5. SD控制器：`drv_sdcard.c`中的块设备驱动初始化
6. 网卡驱动：若使用的PHY芯片不在驱动支持范围内，可能需要在`xemacpsif_physpeed.c`中实现相应芯片的速率识别函数，可参考ALINX的相应教程。

以上需要修改的`xparameters.h`中的参数宏定义不需要手动修改，可以直接将Xilinx Vitis中产生的开发板的`xparameters.h`文件复制过来即可。



## 注意事项

- 无

## 联系人信息

维护人:

-  [王华辰](https://github.com/Wang-Huachen/)
