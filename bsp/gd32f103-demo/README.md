# GD32F103-demo #

## 1. 简介

GD32F10x系列是[兆易创新](http://gd32mcu.21ic.com)基于ARM® Cortex™-M3处理器的32位通用微控制器。 ARM® Cortex™-
M3处理器包括三条AHB总线分别称为I-CODE总线、 D-Code总线和系统总线。 Cortex™-M3处
理器的所有存储访问，根据不同的目的和目标存储空间，都会在这三条总线上执行。存储器的
组织采用了哈佛结构，预先定义的存储器映射和高达4 GB的存储空间，充分保证了系统的灵活
性和可扩展性。引脚与STM32同系列兼容，经测试除了片内FLASH驱动外，STM32的程序只需很小的改动甚至不改动就可直接在GD32F103上运行。

## 开发环境说明
本bsp所用的MCU具体型号为GD32F103RCT6，IDE为Keil-MDK5(需要安装对应pack,因为要用到RTE),调试器为DAPLink。

## 引脚
    LED:PB13
    控制台串口:TX--->PA2,RX--->PA3

## 配置说明
```c
#define RT_CONSOLE_DEVICE_NAME "uart1"
#define PKG_EASYFLASH_WRITE_GRAN 32
```
### 使用步骤：
    1.切换到本目录,使用menuconfig修改配置。
    2.使用 pkgs --update 拉取需要的组件包。
    3.使用 scons --target=mdk5 更新生成项目。
    4.使用MDK打开project.uvprojx，编写、调试和下载程序。

## 参考
* gd32303e-eval
* stm32f103-atk-nano
