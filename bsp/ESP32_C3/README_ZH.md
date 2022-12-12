
# ESP32-C3 BSP 说明

中文 | [English](README.md)

## 简介

本文档为基于RT-THREAD的乐鑫ESP32-C3的[ESP32C3](http://luatos.com/t/esp32c3) BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。

## 开发板介绍

目前测试了两款开发板，运行都正常，由于两款开发板LED小灯引脚不同，请在menuconfig中选择自己手上的开发板。已测开发板外观如下图所示：

- [LUATOS_ESP32C3](https://wiki.luatos.com/chips/esp32c3/board.html)

![LUATOS_ESP32C3](images/luatos_esp32c3.png)

- [HX-DK-商](https://docs.wireless-tech.cn/doc/7/)

![hongxu](images/hx_shang.png)



该LUATOS_ESP32C3开发板常用 **板载资源** 如下：

- MCU：[esp32-c3](https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_en.pdf)，主频  160MHz， 407.22 CoreMark; 2.55  CoreMark/MHz
- 芯片内置：384KB ROM,  400KB SRAM,
- 常用外设
  - 红色LED：2个，LED: D4 (IO12), D5（IO13）
  - 按键：2个，K1（BOOT） K2(RST)
  - SPI FLASH: 4M 
- 常用接口：USB UART等

开发板更多详细信息请参考 [ESP32-C3开发板介绍](https://wiki.luatos.com/chips/esp32c3/board.html)。

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设**      | **支持情况** | **备注**                              |
| :----------------- | :----------: | :------------------------------------- |
| GPIO              |     支持     |  |
| UART              |     支持     | 使用LUATOS_ESP32C3开发板需要在UART0_TX和UART0_RX连接串口转USB芯片（如CP2102）|
| JTAG调试          |     支持     | ESP32C3采用USB方式和PC链接的开发板可以调试                                |

## 安装ESP-IDF
可以使用两种方法安装ESP-IDF
1. 使用Env工具安装
- 下载软件包
```
pkgs --update
```
- 进入到ESP-IDF软件包路径，安装IDf工具链。此命令只需要在下载完软件包后执行一次。
```
cd packages/ESP-IDF-latest
./install.sh
# Windows环境下使用install.bat
```
- 在软件包路径下设置IDF路径。每当在新的命令行编译BSP时需要执行此命令。
```
. export.sh
# Windows环境下使用export.bat
```
2. 在本地ESP-IDF加载patch
- 通过`SCons --menuconfig`选择
```
Hardware Drivers Config
    [*] Use local ESP-IDF installation
```
并取消勾选ESP-IDF软件包
```
RT-Thread online packages
    peripheral libraries and drivers
        [ ] ESP-IDF: Espressif IoT Development Framework
```
- 可以选择其他方式在本地安装ESP-IDF，如[VSCode插件](https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/tutorial/install.md)。确保安装的ESP-IDF是master版本。
- 进入本地ESP-IDF目录执行以下命令
```
git checkout 5c1044d84d625219eafa18c24758d9f0e4006b2c
# 把rtt.patch换成BSP目录下rtt.patch的正确路径
git am rtt.patch
```
- 加载patch后不会影响使用ESP-IDF编译基于FreeRTOS的工程

## 编译和烧录
1. 在BSP路径下配置RT-Thread
```
scons --menuconfig
```
2. 每当使用`scons --menuconfig`更改RT-Thread配置后需要重新生成`CMakeLists.txt`。
```
scons --target=esp-idf
```
3. 如果使用Env安装了ESP-IDF，使用`idf.py`命令编译，烧录。具体参考[乐鑫官网](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/get-started/index.html#build-your-first-project)。如果使用了在本地ESP-IDF加载patch的方式，可使用其他相应的编译和烧录方法，如[VSCode插件](https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/tutorial/install.md)。
4. 下载程序成功之后，系统会运行，红色的 LED灯以 1S 周期闪烁。

## 注意事项

- 目前RTTHREAD支持起来了，后续会需要继续完善一些其他功能，刚开始使用ESP32，欢迎小伙伴一起来讨论和贡献。感兴趣的可以通过公众号`Thomas的小火车`来联系

## 联系人信息

维护人:

-  [supperthomas](https://github.com/supperthomas) 邮箱：<78900636@qq.com>
-  [tangzz98](https://github.com/tangzz98) 邮箱：<tangz98@outlook.com>

## 特别感谢

- 感谢[chenyingchun0312](https://github.com/chenyingchun0312) 提供了RISCV的强力支持
