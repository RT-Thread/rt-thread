# BSP 外设驱动使用教程

## 简介

本文档是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。

主要包括以下内容：

1. 如何使用开发板上更多的板载资源
2. 如何使用更多的片上资源
3. 如何添加更多片上资源选项

## 前提要求

- 学会如何使用 ENV 工具，参考：[RT-Thread env 工具用户手册](https://www.rt-thread.org/document/site/rtthread-development-guide/rtthread-tool-manual/env/env-user-manual/)

## 如何使用更多的板载资源

开发板上一般有很多板载资源，如 Flash、SD卡、以太网等，但是 BSP 工程默认没有开启这些外设驱动。RT-Thread 提供了 ENV 工具来开启或关闭 BSP 的外设驱动。下面以在野火 imxrt1052 pro 开发板上开启 MPU6050 驱动为例，一步步的展示如何使用 ENV 工具对 BSP 进行配置。

### 1）打开配置工具

在目录 `rt-thread\bsp\imxrt\imxrt1052-fire-pro` 下打开 menuconfig 配置界面。

![打开 menuconfig](figures/menuconfig_apolo.png)

打开的配置工具界面如下所示：

![RT-Thread 配置菜单](figures/config1.png)

通过键盘上的上下键移动光标，选中 `Hardware Drivers Config`然后按回车键进入硬件驱动配置菜单。

### 2）进入硬件驱动配置菜单

在硬件配置菜单里有三个选项，分别是 **板载外设配置菜单**、**片上外设配置菜单**和**扩展模块配置菜单**，按回车键进入板载外设配置菜单。

![硬件驱动 配置菜单](figures/config2.png)

### 3）在板载外设配置菜单里开启 MPU6050 选项

![板载外设 配置菜单](figures/mpu6050.png)

### 4）保存退出

然后右移光标选中 Save 按回车键保存，然后按 Esc 键退出配置工具。

![保存退出](figures/save.png)

### 5）更新软件包

输入命令 `pkgs --update` 使软件包配置生效。

![1543477036034](figures/update.png)

### 6）生成 MDK5 工程

输入命令 `scons --target=mdk5` 生成 MDK5 的工程。

![1543477194829](figures/scons_mdk5.png)

### 7）编译下载

打开生成的 MDK5 工程文件，编译并下载。

![1543478492157](figures/complise.png)

### 8）查看运行结果

程序运行后，输入命令 `list_device` 可以看到名为 I2C 的块设备，MPU6050 通信选择的是 I2C 通信,此时 `MPU6050` 已经可以使用了。

![1543478742034](figures/i2c_device1.png)

## 如何使用更多的片上资源

如果想要使用除了当前支持的片上资源（GPIO 和 UART1），又不想开启板载资源的支持，可以通过直接配置 **片上外设配置菜单** 的方式，使用更多片上资源。

配置方法和上一章节介绍的 **如何使用更多的板载资源的配置方法** 一样，只是本次需要进入 `片上外设配置菜单`。

![1543481275711](figures/on_chip_config.png)

配置完成后重新生成工程，编译下载，在 FinSH 控制台输入 `list_device` 命令，可以看到 PWM 已经启用。

![i2c_device](figures/pwm_device.png)

## 总结

当开发者需要使用未开启的外设时，只要在 ENV 工具中使能相关的外设即可，重新生成的工程中就会添加对应的驱动文件。开发者就可以利用 RT-Thread 提供的驱动开快速开发应用了。