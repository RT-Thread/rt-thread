
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

## 环境搭建及编译

1. 下载 RISC-V 工具链：

    ```sh
    wget https://github.com/espressif/crosstool-NG/releases/download/esp-2022r1-RC1/riscv32-esp-elf-gcc11_2_0-esp-2022r1-RC1-linux-amd64.tar.xz
    tar xf riscv32-esp-elf-gcc11_2_0-esp-2022r1-RC1-linux-amd64.tar.xz
    ```

  2. 配置工具链的路径：

     在`bsp/ESP32_C3/rtconfig.py`文件中将`RISC-V`工具链的本地路径添加到`EXEC_PATH`变量中，或者通过设置 `RTT_EXEC_PATH`环境变量指定路径，例如：

     ```sh
     export RTT_EXEC_PATH=/opt/riscv32-esp-elf/bin
     ```

  3. 编译

     安装 esptool 用于转换 ELF 文件为二进制烧录文件：

     ```sh
     pip install esptool
     ```

     在 Linux 平台下进入`bsp/ESP32_C3/`执行以下命令进行配置：

     ```
     scons --menuconfig
     ```

     它会自动下载env相关脚本到`~/.env`目录，然后执行：

     ```sh
     source ~/.env/env.sh
     
     cd bsp/ESP32_C3/
     pkgs --update
     ```

     它会自动下载`RT-Thread-packages/esp-idf`和`RT-Thread-packages/FreeRTOS-Wrapper`，更新完软件包后，执行 `scons` 来编译这个板级支持包。

     如果编译成功，将生成`rtthread.elf`、`rtthread.bin`文件。

## 下载烧录

1. 烧录工具下载

    当前bsp测试使用`flash_download_tool_3.9.4`工具进行烧录无误。

    烧录工具下载地址：[https://www.espressif.com.cn/sites/default/files/tools/flash_download_tool_3.9.4_0.zip](https://www.espressif.com.cn/sites/default/files/tools/flash_download_tool_3.9.4_0.zip)

2. 烧录工具配置

    芯片型号选择`ESP32-C3`

    将二进制文件与偏移地址配置如下：

    | 二进制文件          | 偏移地址 |
    | ------------------- | -------- |
    | bootloader.bin      | 0x0      |
    | partition-table.bin | 0x8000   |
    | rtthread.bin        | 0x10000  |

    其中`bootloader.bin`和`partition-table.bin`可在`bsp/ESP32_C3/builtin_imgs`文件夹下找到，配置完成后截图如下，之后点击`START`即可下载。

    ![flash_download_tools](images/flash_download_tools.png)

## 注意事项

- 目前RTTHREAD支持起来了，后续会需要继续完善一些其他功能，刚开始使用ESP32，欢迎小伙伴一起来讨论和贡献。感兴趣的可以通过公众号`Thomas的小火车`来联系

## 联系人信息

维护人:

-  [supperthomas](https://github.com/supperthomas) 邮箱：<78900636@qq.com>
-  [tangzz98](https://github.com/tangzz98) 邮箱：<tangz98@outlook.com>

## 特别感谢

- 感谢[chenyingchun0312](https://github.com/chenyingchun0312) 提供了RISCV的强力支持
