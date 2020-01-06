# Cypress CY8CKIT-062-BLE PSoC 6 BLE Pioneer Kit 说明

## 简介

本文档为Cypress为PSoC6 BLE Pioneer Kit开发板提供的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 RT-Thread 驱动更多板载资源。

## 开发板介绍

CY8CKIT-062-BLE PSoC6 BLE Pioneer Kit 是赛普拉斯推出的一款32位双核CPU子系统（ ARM Cortex-M4 和 ARM Cortex-M0）的开发板，具有单周期乘法的150-MHz Arm Cortex-M4F CPU (浮点和
存储器保护单元)，100-MHz Cortex M0+ CPU，带单周期乘法和MPU，可以充分发挥 PSoC6 双核芯片性能。

开发板外观详细信息：https://www.cypress.com/file/390496/download


该开发板常用 **板载资源** 如下：

- MCU：CY8C6347BZI-BLD53，Cortex-M4主频 150MHz，Cortex-M0主频 100MHz，1 MB 应用闪存，32 KB EEPROM 区域和32 KB 安全闪存 ，288 KB 集成SRAM
	    MCU手册更多详细信息请参考文档 https://www.cypress.com/file/457541/download
		
- 开发环境：ModusToolbox 2.0
		PSoC® Creator™ 下载链接 https://www.cypress.com/products/modustoolbox-software-environment
		
- 开发板：CY8CKIT-062-BLE PSoC 6 BLE Pioneer Kit
		开发板更多详细信息请参考文档 https://www.cypress.com/file/390496/download
		

## 外设支持

本 BSP 目前对外设的支持情况详细信息请参考文档 https://www.cypress.com/file/390496/download

## 使用说明

使用说明分为如下两个章节：

- 快速上手

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

    本章节是为需要在 RT-Thread 操作系统上使用赛普拉斯开发板资源的开发者准备的。


### 快速上手

本 BSP 以 ModusToolbox 2.0开发环境（GCC），介绍如何将系统运行起来。

#### 硬件连接

使用Type-C数据线连接开发板到 PC.

#### 编译下载
1, 安装ModusToolbox 2.0时请使用默认路径
 
2, 打开ModusToolbox 2.0时workspace选择工程所在目录下（例如workspace: C:\Git\rt-thread\bsp\cypress）

3, 在Project Explorer的空白处右键，点击import，General->Existing Projects into Workspace ->next，点击Browse选择
   此BSP所在目录加载工程->Finish

4, 下载lib：在左下角Quick Panel的Tools栏，点击library Manager-> BSPs下面勾选CY8CKIT-062-BLE (若已勾选可以不用再选)
			-> Libraries里PSoC6 Base Libraries下面全部勾选core-lib,psoc6cm0p,psoc6hal,psoc6make,psoc6pdl -> 点击apply 进行下载

5, 编译此工程

6, 下载此工程


工程默认配置使用 SWD方式下载程序，Type-C数据线连接开发板，编译之后直接点击下载按钮即可。

#### 运行结果

下载程序成功之后，系统会自动运行。打开终端工具串口小助手，复位设备后，可以看到 RT-Thread 的输出信息:

注：推荐使用串口调试助手如：sscom

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Jan  6 2020
 2006 - 2019 Copyright by rt-thread team
hello rt-thread
msh >hello rt-thread
hello rt-thread
```                                  

## 联系人信息

维护人:

- [amyqian379](https://github.com/amyqian379)