# 瑞萨 RSK-RZT2M 开发板 BSP 说明

**中文** | [**English**](./README.md)

## 简介

本文档为瑞萨 RSK-RZT2M 开发板提供的 BSP (板级支持包) 说明。通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。

主要内容如下：

- 开发板介绍
- BSP 快速上手指南

## 开发板介绍

基于瑞萨 RZ/T2M 开发的 RSK-RZT2M MCU 评估板，通过灵活配置软件包和 IDE，对嵌入系统应用程序进行开发。

开发板正面外观如下图：

![](figures/board.png)

该开发板常用 **板载资源** 如下：

- MPU：R9A07G075M24GBG，最大工作频率 800MHz，双Arm Cortex®-R52 内核，紧密耦合内存 576KB（带 ECC），内部 RAM 2 MB（带 ECC）
- 调试接口：板载 J-Link 接口
- 扩展接口：两个 PMOD 连接器

**更多详细资料及工具**

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设** | **支持情况** | **备注** |
| :----------------- | :----------------- | :------------- |
| UART               | 支持               | UART0 为默认日志输出端口 |
| GPIO               | 支持               |                |
| HWIMER                | 支持           |            |
| IIC                | 不支持           |            |
| WDT                | 不支持              |                |
| RTC                | 不支持              |                |
| ADC                | 不支持              |                |
| DAC                | 不支持              |                |
| SPI                | 不支持              |                |
| FLASH              | 不支持              |                |
| PWM                | 不支持              |                |
| CAN                | 不支持              |                |
| ETH             | 不支持              |                |
| 持续更新中...      |                    |                |


## 使用说明

使用说明分为如下两个章节：

- 快速上手

  本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。
- 进阶使用

  本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。

### 快速上手

本 BSP 目前仅提供 IAR 工程。下面以 [IAR Embedded Workbench for Arm](https://www.iar.com/products/architectures/arm/iar-embedded-workbench-for-arm/) 开发环境为例，介绍如何将系统运行起来。

**硬件连接**

使用 USB 数据线连接开发板到 PC，使用 J-link 接口下载和 DEBUG 程序。

**编译下载**

- 进入 bsp 目录下，打开 ENV 使用命令 `scons --target=iar` 生成 IAR工程。
- 编译：双击 project.eww 文件，打开 IAR 工程，编译程序。
- 调试：IAR 左上方导航栏点击 `Project->Download and Debug`下载并启动调试。



**查看运行结果**

下载程序成功之后，系统会自动运行并打印系统信息。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息。输入 help 命令可查看系统中支持的命令。

```bash
 \ | /
- RT -     Thread Operating System
 / | \     5.1.0 build Mar 14 2024 18:26:01
 2006 - 2024 Copyright by RT-Thread team

Hello RT-Thread!
==================================================
This is a iar project which mode is ram execution!
==================================================
msh >help
RT-Thread shell commands:
clear            - clear the terminal screen
version          - show RT-Thread version information
list             - list objects
backtrace        - print backtrace of a thread
help             - RT-Thread shell help
ps               - List threads in the system
free             - Show the memory usage in the system
pin              - pin [option]

msh >
```

**应用入口函数**

应用层的入口函数在 **src\hal_entry.c** 中 的 `void hal_entry(void)` 。用户编写的源文件可直接放在 src 目录下。

```c
void hal_entry(void)
{
    rt_kprintf("\nHello RT-Thread!\n");
    rt_kprintf("==================================================\n");
    rt_kprintf("This is a iar project which mode is ram execution!\n");
    rt_kprintf("==================================================\n");

    while (1)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
```

### 进阶使用

**资料及文档**

- [开发板官网主页](https://www.renesas.cn/cn/zh/products/microcontrollers-microprocessors/rz-mpus/rzt2m-high-performance-multi-function-mpu-realizing-high-speed-processing-and-high-precision-control#overview)
- [开发板数据手册](https://www.renesas.cn/cn/zh/document/dst/rzt2m-group-datasheet?r=1574901)
- [开发板硬件手册](https://www.renesas.cn/cn/zh/document/mah/rzt2m-group-users-manual-hardware?r=1574901)
- [RZ/T2M Easy Download Guide](https://www.renesas.cn/cn/zh/document/gde/rzt2m-easy-download-guide?r=1574901)
- [Renesas RZ/T2M Group](https://www.renesas.cn/cn/zh/document/fly/renesas-rzt2m-group?r=1574901)

**FSP 配置**

需要修改瑞萨的 BSP 外设配置或添加新的外设端口，需要用到瑞萨的 [FSP](https://www2.renesas.cn/jp/zh/software-tool/flexible-software-package-fsp#document) 配置工具。请务必按照如下步骤完成配置。配置中有任何问题可到[RT-Thread 社区论坛](https://club.rt-thread.org/)中提问。

1. [下载灵活配置软件包 (FSP) | Renesas](https://github.com/renesas/rzn-fsp/releases/download/v1.3.0/setup_rznfsp_v1_3_0_rzsc_v2023-07.exe)，请使用 FSP 1.3.0 版本
2. 如何将 **”RSK-RZT2M板级支持包“**添加到 FSP 中，请参考文档[如何导入板级支持包](https://www2.renesas.cn/document/ppt/1527171?language=zh&r=1527191)
3. 请参考文档：[RA系列使用FSP配置外设驱动](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/tutorial/make-bsp/renesas-ra/RA系列使用FSP配置外设驱动?id=ra系列使用-fsp-配置外设驱动)。

**ENV 配置**

- 如何使用 ENV 工具：[RT-Thread env 工具用户手册](https://www.rt-thread.org/document/site/#/development-tools/env/env)

此 BSP 默认只开启了 UART1 的功能，如果需使用更多高级功能例如组件、软件包等，需要利用 ENV 工具进行配置。

步骤如下：
1. 在 bsp 下打开 env 工具。
2. 输入`menuconfig`命令配置工程，配置好之后保存退出。
3. 输入`pkgs --update`命令更新软件包。
4. 输入`scons --target=iar` 命令重新生成工程。

## 联系人信息

在使用过程中若您有任何的想法和建议，建议您通过以下方式来联系到我们  [RT-Thread 社区论坛](https://club.rt-thread.org/)

## 贡献代码

如果您对 RSK-RZT2M 感兴趣，并且有一些好玩的项目愿意与大家分享的话欢迎给我们贡献代码，您可以参考 [如何向 RT-Thread 代码贡献](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/development-guide/github/github)。
