# STM32F407-lckfb-skystar立创天空星开发板BSP说明

## 简介

该开发板是由立创开发板精心打造的一款高性价比的开发工具，**软硬件全开源**。设计上充分考虑了与多种100脚封装的单片机的兼容性。这种设计使得它不仅适用于特定的芯片，还能够适配市场上多种不同厂家生产的100脚微控制器，极大地提高了适用范围和灵活性。该BSP适配立创梁山派·天空星开发板的主控芯片为STM32F407VET6。

为了最大限度的方便开发者和爱好者，该核心板通过排针将所有可用的IO（输入/输出）引脚都引出，这样大家就可以轻松地连接各种外部模块和设备，无需进行复杂的焊接工作。这一特点特别适合那些需要快速原型制作和迭代的场合，如学生电子竞赛、创客活动以及个人DIY项目。

此外，这款核心板的设计考虑到了大家在电子竞赛中对于稳定性和可靠性的需求，以及在小型项目开发中对低成本的追求。具体请看硬件设计手册。

![[(lckfb.com)](https://lckfb.com/project/detail/lckfb-lspi-skystar-stm32f407vet6-lite?param=baseInfo)](figures/board.png)

## 资料罗列：

* [硬件开源地址](https://oshwhub.com/li-chuang-kai-fa-ban/li-chuang-liang-shan-pai-tian-kong-xing-kai-fa-ban)
* [硬件文档](https://lceda001.feishu.cn/wiki/D4cqwUkiTi6723knO2cczSThnYb)
* [入门手册](https://lceda001.feishu.cn/wiki/Zawdwg0laig3Qnk2XuxcKrQRn2g)
* [模块移植手册](https://lceda001.feishu.cn/wiki/GySKwn3jMitXbAkhX0GcDjtBnQd)
* [购买地址](https://lckfb.com/project/detail/lckfb-lspi-skystar-stm32f407vet6-lite?param=baseInfo)

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设** | **支持情况** | **备注**                        |
| :----------- | :----------: | :------------------------------ |
| GPIO         |     支持     | PA0, PA1... ---> PIN: 0, 1...81 |
| UART         |     支持     | UART0 - UART6                   |
| I2C          |     支持     | I2C1                            |
| SPI          |     支持     | SPI0 -  SPI2                    |
| ADC          |     支持     | ADC0 - ADC2                     |
| TF CARD      |     支持     | SDIO                            |
| SPI FLASH    |     支持     | SPI1                            |
| **扩展模块** | **支持情况** | **备注**                        |
| 暂无         |   暂不支持   | 暂不支持                        |

## 使用说明

使用说明分为如下两个章节：

- 快速上手
  
  本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用
  
  本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。

### 快速上手

本 BSP 为开发者提供 MDK4、MDK5 工程，并且支持 GCC 开发环境，也可使用RT-Thread Studio开发。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC，使用USB转TTL模块连接PA9(MCU TX)和PA10(MCU RX)，上电。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 CMSIS-DAP 仿真器下载程序，在通过 CMSIS-DAP 连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，LED 闪烁。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     5.1.0 build Apr 13 2024 11:59:40
 2006 - 2024 Copyright by RT-Thread team

```

### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口0的功能，如果需使用高级功能，需要利用 ENV 工具对BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk4/mdk5/iar` 命令重新生成工程。

## 注意事项

暂无

## 联系人信息

维护人:

- [yuanzihao](https://github.com/zihao-yuan/), 邮箱：[y@yzh.email](mailto:y@yzh.email)