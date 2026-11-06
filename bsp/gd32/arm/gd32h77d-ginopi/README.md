# GD32H77D GinoPi BSP 说明

## 简介

本 BSP 面向搭载 GD32H77DIW 的 GD32H77D GinoPi 开发板，处理器内核为 Arm Cortex-M7，最高主频为 600 MHz。

当前 BSP 支持 GCC 和 MDK5 工具链，默认启用 GPIO、UART1 控制台和 RT-Thread FinSH/MSH。示例程序每隔 500 ms 翻转一次 PC4；其他板载外设均可按需通过 menuconfig 开启。

默认 `.config` 仅启用串口和 PIN 外设，LVGL、文件系统、网络、串口 DMA 及其他外设均关闭，仅保留启动必需的 CMSIS 和厂家外设库软件包。

## 外设支持

| 外设               | 支持情况 | 说明                                                                                         |
| :----------------- | :------: | :------------------------------------------------------------------------------------------- |
| GPIO               |   支持   | 默认启用，使用`GET_PIN()` 访问引脚                                                         |
| UART0              |   支持   | 默认引脚 PF4/PF5，复用功能 AF4                                                               |
| UART1              |   支持   | 默认控制台，PA2/PA3，复用功能 AF7                                                            |
| UART2              |   支持   | 默认引脚 PB10/PB11，复用功能 AF7                                                             |
| UART3              |   支持   | 默认引脚 PC10/PC11，复用功能 AF8                                                             |
| UART4              |   支持   | 默认连接 GD32VW553 AT Wi-Fi，TX: PB12/AF14、RX: PB13/AF14                                    |
| I2C1               |   支持   | 默认未启用，SCL: PH4、SDA: PB11，复用功能 AF4                                                |
| CAN1               |   支持   | 默认未启用，TX: PB4/AF4、RX: PB5/AF9                                                         |
| OSPI0/QSPI Flash   |   支持   | 默认未启用，板载 8 MiB GD25Q64ESIG，Quad SPI 模式                                            |
| GD32VW553 AT Wi-Fi |   支持   | 默认未启用，基于 RT-Thread at_device、SAL 和 AT socket，设备名`wifi0`，AT 串口为 `uart4` |
| ENET1              |   支持   | 默认未启用，RMII 接口，PHY 默认地址为 2                                                      |
| SDRAM              |   支持   | 默认未启用，板载 32 MiB、16 位 SDRAM                                                         |
| USBHS0 Device      |   支持   | 默认未启用，Type-C 接口，PA11/PA12，支持高速和全速模式                                       |
| USBHS1 Host        |   支持   | 默认未启用，USB-A 接口，PB14/PB15，全速模式                                                  |
| RTC                |   支持   | 默认未启用，可通过 menuconfig 开启                                                           |

UART 引脚可在 `Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable UART` 中修改。
I2C1 引脚和复用功能可在 `Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable I2C` 中修改。
CAN1 引脚和 TX/RX 复用功能可在 `Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable CAN` 中分别修改。
OSPI0 控制器以 QSPI 模式使用，CS、CLK 和 IO0-IO3 引脚及复用功能可在 `Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable OSPI0 (QSPI)` 中分别修改。
QSPI Flash 文件系统可在 `Hardware Drivers Config -> Onboard Peripheral Drivers -> Enable File System -> Enable FAL filesystem partition based on GD25Q64ESIG` 中配置。
GD32VW553 AT Wi-Fi 可在 `Hardware Drivers Config -> Board extended module Drivers -> Enable GD32VW553 AT Wi-Fi module` 中配置。
ENET、SDRAM 和 USB 可在 `Hardware Drivers Config -> Onboard Peripheral Drivers` 中开启。

## 默认配置

| 项目         | 配置             |
| :----------- | :--------------- |
| 芯片         | GD32H77DIW       |
| 控制台设备   | `uart1`        |
| 控制台引脚   | TX: PA2，RX: PA3 |
| 串口参数     | 115200-8-N-1     |
| 示例输出引脚 | PC4              |
| 系统时钟     | 600 MHz          |

## 存储器布局

启动表位于 `0x08000000`，保存栈顶和复位入口；应用中断向量表与 VTOR 位于 `0x08010000`。GCC 与 SDK 一致，将启动代码、只读代码和数据加载映像放入 CNVM。MDK 的散装文件保留 ECNVM 作为额外代码区。

| 区域        | 起始地址       | 长度     | 用途                   |
| :---------- | :------------- | :------- | :--------------------- |
| CNVM 启动表 | `0x08000000` | 8 B      | 初始 SP 和复位入口     |
| CNVM 应用区 | `0x08010000` | 1984 KiB | 向量表、代码和只读数据 |
| ECNVM       | `0x08200000` | 7680 KiB | MDK 额外代码区         |
| AXI SRAM    | `0x24000000` | 768 KiB  | 数据、栈和堆           |
| SRAM1       | `0x30004000` | 16 KiB   | ENET DMA               |
| ITCM RAM    | `0x00000000` | 128 KiB  | ITCM 段                |
| DTCM RAM    | `0x20000000` | 256 KiB  | DTCM 段                |

## 使用说明

### 准备软件包

系列宏使用 `SOC_SERIES_GD32H77x_H78X`，芯片型号使用 `SOC_GD32H77DIW`。需要支持 `GD32H77x_78x` 的 `gd32-arm-cmsis` 和 `gd32-arm-series` 软件包，源码位于 `../libraries/`。CMSIS 软件包负责启动文件与系统时钟，series 软件包负责厂家外设源码及其构建选择；RT-Thread 驱动仅构建适配层。

首次编译或软件包配置发生变化后，在 BSP 目录执行：

```bash
pkgs --update
```

### GCC 编译

SDK 链接脚本使用 `READONLY` 段属性，建议使用 Arm GNU Toolchain 13.3。已用该版本检查启动汇编及启动表、向量表、LVGL DTCM 内存池和 ENET DMA 的链接布局。

确保 `arm-none-eabi-gcc` 所在目录已经加入 `PATH`，或者通过 `RTT_EXEC_PATH` 指定工具链目录，然后执行：

```bash
scons -j8
```

构建成功后生成：

| 文件              | 说明                                         |
| :---------------- | :------------------------------------------- |
| `rt-thread.elf` | 包含两个加载区域和调试信息，推荐用于调试下载 |
| `rt-thread.bin` | 包含启动表和 CNVM 应用区的镜像               |
| `rtthread.map`  | GCC 链接映射文件                             |

使用调试器下载 `rt-thread.elf` 时，调试器会根据 ELF 加载段写入对应存储区。

直接下载 `rt-thread.bin` 时，下载起始地址必须设置为 `0x08000000`。程序代码位于该文件偏移 `0x00200000`，对应 MCU 地址 `0x08200000`。

### MDK5 编译

可以重新生成 MDK5 工程：

```bash
scons --target=mdk5
```

然后使用 MDK5 打开 `project.uvprojx`，编译并通过 SWD 调试器下载 `rt-thread.axf`。

### 硬件连接

使用 SWD 调试器连接开发板并供电。查看控制台时，将串口适配器连接到以下引脚：

| 串口适配器 | 开发板          |
| :--------- | :-------------- |
| RX         | PA2（UART1 TX） |
| TX         | PA3（UART1 RX） |
| GND        | GND             |

### 运行结果

复位开发板后，PC4 每隔 500 ms 翻转一次；启用 MIPI DSI LCD 时，屏幕会显示一个文本框和触摸虚拟键盘。打开串口终端可以看到 RT-Thread 启动信息并进入 MSH：

```text
 \ | /
- RT -     Thread Operating System
 / | \
msh />
```

### QSPI Flash 文件系统

板载 GD25Q64ESIG 注册为 FAL Flash 设备 `gd25q64e`，整个 8 MiB 空间配置为 `filesystem` 分区。系统会创建同名块设备，并尝试将 Elm-FAT 挂载到 `/flash`。

新 Flash 尚未格式化时，首次自动挂载会失败。确认分区中没有需要保留的数据后执行以下命令，`mkfs` 会清空整个 `filesystem` 分区：

```text
fal probe filesystem
fal read 0 16
mkfs -t elm filesystem
mount filesystem /flash elm
echo qspi-ok > /flash/qspi.txt
cat /flash/qspi.txt
```

复位后自动挂载成功，再执行 `cat /flash/qspi.txt`，可验证文件系统数据是否能够持久保存。FAL 块大小和 Elm-FAT 最大扇区大小均为 4096 字节。

### GD32VW553 MQTT 示例

GD32VW553 模块默认通过 `uart4` 接入 `at_device`，MQTT 应用通过 kawaii-mqtt、SAL socket 和 AT socket 访问网络。Wi-Fi 与 MQTT 参数在 `menuconfig` 中配置，MSH 命令如下：

```text
gd32vw553_mqtt_start
gd32vw553_mqtt_pub <topic> <message>
gd32vw553_mqtt_stop
```

## 配置 BSP

在 BSP 目录打开 RT-Thread Env，执行：

```bash
menuconfig
pkgs --update
scons -j8
```

修改配置后应由 `.config` 重新生成 `rtconfig.h`，不要直接编辑 `rtconfig.h`。

## 注意事项

- 启动表位于 `0x08000000`，应用向量表位于 `0x08010000`，下载时必须包含启动表。
- 当前 SDK 使用 Serial V1，未适配此芯片的 Serial V2 和串口 DMA，不应切换到这些配置。
- 如果修改 CNVM 或 ECNVM 起始地址，需要同时更新链接脚本、VTOR 和下载配置。
