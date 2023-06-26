# 第一部分：NUCLEO-U575ZI-Q 开发板 BSP 说明

[English](README.md) | **中文**

## 简介

本文档为 liukang 为 NUCLEO-U575ZI-Q 开发板提供的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 RT-Thread 驱动更多板载资源。

## 开发板介绍

STM32U575ZI 是 ST 推出的一款基于 ARM Cortex-M33 内核的开发板，最高主频为 160 Mhz，该开发板具有丰富的板载资源，可以充分发挥 STM32U575 的芯片性能。

开发板外观如下图所示：

![board](figures/board.png)

该开发板常用 **板载资源** 如下：

- MCU：STM32U575ZI，主频 160 MHz，2048KB FLASH ，786KB RAM
- 常用接口：USB 转串口、USB 接口、arduino 接口等
- 调试接口，标准 JTAG/SWD

开发板更多详细信息请参考 ST [STM32U575ZI](https://www.st.com/en/evaluation-tools/nucleo-u575zi-q.html)。

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **板载外设**      | **支持情况** | **备注**                              |
| :----------------- | :----------: | :------------------------------------- |
| USB 转串口        |     支持     ||
| **片上外设**      | **支持情况** | **备注**                              |
| GPIO              |     支持     | |
| UART              |     支持     |   UART1                           |


## 使用说明

使用说明分为如下两个章节：

- 快速上手

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

    本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。


### 快速上手

本 BSP 为开发者提供 MDK5 和 IAR 工程，并且支持 GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC，打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 ST_LINK 仿真器下载程序，在通过 ST_LINK 连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，LED闪烁。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build Nov 14 2021 21:15:06
 2006 - 2021 Copyright by rt-thread team
msh >
```
### 进阶使用

此 BSP 默认只开启了 GPIO 和 UART1 的功能，如果需使用更多高级功能，需要利用 ENV 工具对BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk4/mdk5/iar` 命令重新生成工程。

本章节更多详细的介绍请参考 [STM32 系列 BSP 外设驱动使用教程](../docs/STM32系列BSP外设驱动使用教程.md)。

## 注意事项

- 调试串口为 UART1 1 映射说明

  ```c
  PA9     ------> USART1_TX
  PA10     ------> USART1_RX
  ```

# 第二部分：NUCLEO-U575ZI-Q 上手指南

NUCLEO-U575ZI-Q 上手指南是通过使用 SPI1 驱动 RW007 模块实例进行介绍，实现 NUCLEO-U575ZI-Q 入门

## 准备工作
在 NUCLEO-U575ZI-Q 驱动`RW007`畅快跑起来之前，以下准备工作必不可少，你将需要：

> 1.NUCLEO-U575ZI-Q 开发板  
> 2.RW007 WiFi 模块  
> 3.Mini-USB 连接线（连接开发板与电脑）  
> 4.ENV 编译构建环境（[安装使用说明](https://www.rt-thread.org/document/site/#/development-tools/env/env)）  
> 5.开发常用软件（git、Keil5、STM32CubeMX、串口调试等）  

## 开始上路
RT-Thread 包含了 RW007 的软件包，用户无需自己编写驱动程序，下面以 SPI 模式为例，介绍如何在 NUCLEO-U575ZI-Q 上驱动 RW007 模块，并完成 AP 扫描、连接等基本 WiFi 功能。

## 硬件连接
得益于 Nucleo 上的 Arduino 接口，只需把 RW007 往开发板上一插，即可完成了两者的硬件连接。  

![](figures/board1.png)  

根据下面原理图可查找各 IO 接口与功能之间的对应关系表如下：  

![](figures/Schematic_diagram.png)    

	|STM32引脚名 | 封装管脚序号  |Arduino接口序号|	功能       |   
	|PA5        |	5	       |D13	          |BOOT0/CLK  |  
	|PA6        |	6	       |D12           |MISO       |  
	|PA7        |	7	       |D11	          |MOSI       |    
	|PD14       |	62         |D10	          |BOOT1/CS   |  
	|PD15       |	63	       |D9	          |INT/BUSY   |  
	|PF12       |	92	       |D8	          |RESET      |  

## STM32 bsp 配置（Menuconfig）
### 1.下载 RT-Thread源码
GitHub链接：[https://github.com/RT-Thread/rt-thread](https://github.com/RT-Thread/rt-thread)  
打开 `rt-thread\bsp\stm32` 目录，能看到 RT-Thread 所支持的开发板型号，把 RT-Thread 在 STM32 上跑起来并不是一件难事，但在编译内核组件之前，要对 bsp 进行简单配置。本次实验所使用的 bsp 为 stm32u575-st-nucleo。

### 2.通过 CubeMX 配置 SPI 初始化程序
一般 STM32 系列的引脚分配可以通过对应 BSP 中board\CubeMX_Config目录下的CubeMX_Config.ioc打开 CubeMX 工程，进行配置 SPI1，并生成代码，保存退出即可 。  
![](figures/CubeMX.png)  

### 3.通过menuconfig配置 RW007 软件包
进入 rt-thread\bsp\stm32\stm32u575-st-nucleo 文件夹，右键打开 ENV 窗口（前提是已在 Windows 下搭好 ENV 环境），输入 menuconfig 进行系统配置：  

#### 3.1开启 SPI 设备
开发板与模块的通讯依赖 SPI 设备，在 bsp 中已经实现了 SPI 驱动，只需在设置中打开即可使用。 进入 `Hardware Drivers Config --->` 下的 `On-chip Peripheral Drivers`，勾选 `Enable SPI BUS --->` 选项，并按回车键进入，进一步选中 `Enable SPI1 BUS`，完成配置：
![](figures/menuconfig1.png) 
![](figures/menuconfig2.png)
![](figures/menuconfig3.png)
![](figures/menuconfig4.png)

如果在 bsp 中的 menuconfig 中没有对应 spi的配置，可以通过修改 Kconfig文件增加对应spi的配置。 Kconfig 的路径在board/Kconfig ，`menu "On-chip Peripheral Drivers"`下面添加 SPI1的配置。  

	menuconfig BSP_USING_SPI
		bool "Enable SPI BUS"
		default n
		select RT_USING_SPI
		if BSP_USING_SPI
		    config BSP_USING_SPI1
		        bool "Enable SPI1 BUS"
		        default n
		
		    config BSP_SPI1_TX_USING_DMA
		        bool "Enable SPI1 TX DMA"
		        depends on BSP_USING_SPI1
		        default n
		        
		    config BSP_SPI1_RX_USING_DMA
		        bool "Enable SPI1 RX DMA"
		        depends on BSP_USING_SPI1
		        select BSP_SPI1_TX_USING_DMA
		        default n
				
		endif

#### 3.2配置 RW007 软件包
RT-Thread 通过软件包的形式，对 RW007 模块提供配套驱动支持，系统默认选项不包含软件包，用户需手动开启：通过 Esc 键回到 Menuconfig 主界面，依次进入 `RT-Thread online packages  --->` 、`IoT - internet of things  --->`、`Wi-Fi  --->`，勾选 `rw007: SPI WIFI rw007 driver  --->` 选项：
![](figures/menuconfig5.png)  
RW007 软件包 Github 仓库链接：[RT-Thread-packages/rw007: RW007 (SPI Wi-Fi module) driver for RT-Thread](https://github.com/RT-Thread-packages/rw007)  

紧接着按下 Enter 键进一步设置软件包参数，完成 SPI 总线和 IO 的配置，更改总线设备名称 RW007 BUS NAME 为 spi1,然后配置 SPI 控制 IO，各管脚号依次按下图序号填入：   
![](figures/menuconfig6.png)  

#### 3.4保存 Menuconfig 配置
完成了上面的 3 步，bsp 配置算大功告成了，但最最重要的一步不能漏，保存 Menuconfig 配置：直接一路狂按 Esc 键退出，在保存提示窗口中选择 Yes 确认即可。

### 4.编译、下载工程

使用工具栏的 Build 按钮编译工程，出现 0 Error(s) 表示编译成功，将开发板连接电脑，再点击 Download 按钮下载固件到开发板

## 运行、测试模块功能
下载完程序便能自动复位运行，打开串口工具（推荐使用 XShell 等交互型终端），设置参数为 115200 8-1-N。若系统启动正常，且开发板与模块间的通讯也没有问题，会看到如下初始化打印信息：  
![](figures/result1.png)  
rw007 sn 与 rw007 ver 可以正常输出无乱码时，RW007驱动成功！！！  

wifi联网测试
在shell中输入 wifi scan 命令搜索wifi:
![](figures/result2.png)  

连接目标wifi测试：  
![](figures/result3.png)
上图可见wifi成功连接热点Meet。  
至此`STM32U575-NUCLEO`的基础环境便搭建测试完毕！！！


## 参考资料：   
1. [STM32F401 Nucleo-64使用SPI驱动RW007](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/application-note/packages/rw007_module_using/an0034-rw007-module-using?id=rw007)  
2. [STM32U575-NUCLEO原理图下载](https://www.st.com/resource/en/schematic_pack/mb1549-u575ziq-c03_schematic.pdf)

## 注意事项：  
1. MDK版本最好使用比较新的版本的，本次实验是在MDK5.36版本下进行的。
2. RW007软件包请选用最新版本的，否则会出现版本不兼容的问题，导致工程报错。若未选择最新版本的RW007软件包，就把下面链接里面的RW007软件包下载，替换掉`bsp\stm32\stm32u575-st-nucleo\packages\rw007-xxx`里面的文件即可！（但上述修改部分工程代码这一步也是要做的，如果工程`rw007_stm32_port.c`文件中`wifi_spi_device_init(void)`函数内容与所给内容相同可忽略！）   
    RW007 软件包 Github 仓库链接：[RT-Thread-packages/rw007: RW007 (SPI Wi-Fi module) driver for RT-Thread](https://github.com/RT-Thread-packages/rw007) 


