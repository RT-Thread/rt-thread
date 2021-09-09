# YC3121-pos 板级支持包 说明

标签： YICHIP、Cortex-M0、YC3121、国产MCU

---

## 1. 简介

本文档为 YC3121-pos 的 BSP(板级支持包) 说明。

通过阅读本文档，开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。

### 1.1  开发板介绍

YC3121-pos 开发板由易兆微提供，可满足基础测试及高端开发需求。

开发板外观如下图所示：

YC3121-pos

![YC3121-pos](figures/YC3121-pos.jpg "YC3121-pos")

YC3121-pos 开发板板载资源如下：

- MCU：YC3121  ARM 32-bit Cortex-M0，主频 96MHz，512KB FLASH ，64KB SRAM
- 常用外设
  - LED：4 个
  - 梯形矩阵键盘
  - 蜂鸣器
  - USB
  - UART
  - SPI LCD
  - SPI NFC
  - 7816
  - 7811
- 调试接口：SWD
