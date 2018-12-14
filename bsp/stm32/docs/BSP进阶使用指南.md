# BSP 进阶使用指南

## 简介

本文档是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。

主要包括以下内容：

1. 如何使用开发板上更多的板载资源
2. 如何使用更多的片上资源
3. 如何添加更多片上资源选项

## 前提要求

- 学会如何使用 ENV 工具，参考：[RT-Thread env 工具用户手册](https://www.rt-thread.org/document/site/rtthread-development-guide/rtthread-tool-manual/env/env-user-manual/)

## 如何使用更多的板载资源

开发板上一般有很多的板载资源，如 Flash、SD卡、以太网等，但是 BSP 工程默认没有添加对这些外设的支持。如何在工程里添加这些外设的支持呢？这就需要使用 ENV 工具了。下面以在正点原子阿波罗 F429 开发板上开启 SPI Flash 支持为例，一步步的展示如何使用 ENV 工具对 BSP 进行配置。

### 1）打开配置工具

在目录 `rt-thread\bsp\stm32\stm32f429-atk-apollo` 下打开 menuconfig 配置界面。

![打开 menuconfig](figures/menuconfig_apolo.png)

打开的配置工具界面如下所示：

![RT-Thread 配置菜单](figures/config1.png)

通过键盘上的上下键移动光标，选中 `Hardware Drivers Config`然后按回车键进入硬件驱动配置菜单。

### 2）进入硬件驱动配置菜单

在硬件配置菜单里有三个选项，分别是 **板载外设配置菜单**、**片上外设配置菜单**和**扩展模块配置菜单**，按回车键进入板载外设配置菜单。

![硬件驱动 配置菜单](figures/config2.png)

### 3）在板载外设配置菜单里开启 SPI Flash 选项

![板载外设 配置菜单](figures/spi_flash.png)

### 4）保存退出

然后右移光标选中 Save 按回车键保存，然后按 Esc 键退出配置工具。

![保存退出](figures/save.png)

### 5）更新软件包

输入命令 `pkgs --update` 使软件包配置生效。

![1543477036034](figures/update.png)

### 6）生成 MDK5 工程

输入命令 `scons --target=mdk5 -s` 重新生成 MDK5 的工程。

![1543477194829](figures/scons_mdk5.png)

### 7）编译下载

打开生成的 MDK5 工程文件，编译并下载。

![1543478492157](figures/complise.png)

### 8）查看运行结果

程序运行后，输入命令 `list_device` 可以看到名为 W25Q256 的块设备，此时 `SPI Flash` 设备已经可以使用了。

![1543478742034](figures/run_flash.png)

## 如何使用更多的片上资源

如果想要使用除了当前支持的片上资源（GPIO 和 UART1），又不想开启板载资源的支持，可以通过直接配置 **片上外设配置菜单** 的方式，使用更多片上资源。

配置方法和上一章节介绍的 **如何使用更多的板载资源的配置方法** 一样，只是本次需要进入 `片上外设配置菜单`。

![1543481275711](figures/on_chip_config.png)

## 如何添加更多的片上资源选项

如果想使用的片上外设是 `片上外设配置菜单` 里没有的，就需要自己添加了。下面以添加 SPI3 的驱动支持为例讲解如何添加更多片上外设支持。

> 没有安装 stm32cubemx 软件的移步 STM32cube中文网：<http://www.stm32cube.com/> ，在 `资源下载` 里下载 stm32cubemx 软件。

添加 SPI3 的外设支持需要以下几步：

### 1）打开 Cube 的工程

![1543486779576](figures/cubemx.png)

### 2）配置好 SPI3 的引脚，并生成代码

按照图中所示步骤操作：

![1543487684698](figures/cube_spi3.png)

### 3）修改 Konfig 文件

打开board文件夹下的 Konfig 文件，拷贝 SPI2 的配置项，并重命名 SPI2 为 SPI3。

![1543542657074](figures/Kconfig2.png)

### 4）重新配置工程

经过上一步的修改，此时重新打开 ENV 工具，在 menuconfig 中就会出现添加的 SPI3 的配置项。

![1543543081284](figures/config5.png)

### 5）生成工程，编译下载

重新生成工程之后，编译下载到开发板，程序会自动开始运行。输入 `list_device` 命令可以看到 spi3 总线设备已经挂载成功了。

![1543543446786](figures/run_spi3.png)
