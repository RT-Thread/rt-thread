
# ESP32-C3 BSP 说明

## 简介

本文档为 乐鑫ESP32-C3 开发板的[ESP32C3](http://luatos.com/t/esp32c3) BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。

## 开发板介绍

目前测试了两款开发板，运行都正常，由于两款开发板LED小灯引脚不同，请根据自己开发板修改GPIO引脚，目前默认使用的开发板是LUATOS_ESP32C3 `GPIO 12` (HX 开发板引脚是`GPIO 8`)。已测开发板外观如下图所示：

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
  - SPI FLASH: 2M 
- 常用接口：USB UART等

开发板更多详细信息请参考 [ESP32-C3开发板介绍](https://wiki.luatos.com/chips/esp32c3/board.html)。

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设**      | **支持情况** | **备注**                              |
| :----------------- | :----------: | :------------------------------------- |
| GPIO              |     支持     |  |
| UART              |     支持中     |                                 |

## 使用说明

### 快速上手

说先要搭建IDE开发环境，乐鑫官方推荐使用IDF开发。

IDF的搭建方法有很多种，尝试了很多种方法之后，总结了一个最快速的方法，并且可以使用vscode跨平台安装，非常简单方便，具体方法见链接[ESP-IDF 一键式搭建环境基于VSCODE](https://blog.csdn.net/lt6210925/article/details/123699249)。 安装的时候IDF版本请选择IDF 4.4版本。如果你对官方IDF命令行的方式熟悉的话，你也可以使用命令行的方式，这边已经测试过，是可以使用的。

### IDF patch加载

由于IDF使用的是FREERTOS需要修改一些文件，将`0001-add-the-config-of-RTTHREAD.patch` 这个文件拷贝到安装的时候的IDF的代码目录，执行命令 下面的命令可以打上patch

```
cd esp/esp-idf
git checkout v4.4
git am 0001-add-the-config-of-RTTHREAD.patch
```

如果不想用patch文件，我已经将代码上传到github上面，可以进入[supperthomas/esp-idf](https://github.com/supperthomas/esp-idf) 下载最新的master分支。修改之后的IDF，原来的IDF的example还是正常使用，互不干扰。

#### 编译下载

用VSCODE 在bsp/ESP32_C3中右击打开

编译选择最下面的按钮：

![build](images/build.png)

这边通常采用串口下载，需要根据你自己开发板选择对应的串口（如果有JTAG的，也可以用JTAG下载和调试）

![burn](images/burn.png)

#### 运行结果

下载程序成功之后，系统会运行，红色的 D4以 1S 周期闪烁。
刚接触ESP32, 目前仅实现LED小灯闪烁，可以print打印，后续计划将pin设备和console对接上去，也欢迎大家一起来贡献，感兴趣的可以通过公众号`Thomas的小火车`来联系

## 注意事项

- 目前RTTHREAD支持起来了，后续会需要继续完善一些其他功能，刚开始使用ESP32，欢迎小伙伴一起来讨论和贡献。

## 联系人信息

维护人:

-  [supperthomas](https://github.com/supperthomas) 邮箱：<78900636@qq.com>

## 特别感谢

- 感谢[chenyingchun0312](https://github.com/chenyingchun0312) 提供了RISCV的强力支持
