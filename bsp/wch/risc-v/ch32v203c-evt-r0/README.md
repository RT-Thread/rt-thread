# ch32v203c-evt-r0 BSP 说明

**中文**

## 1 开发板简介

CH32V203C8T6-EVT-R0 是 WCH 沁恒的 RISC-V 评估板。芯片是 QingKe **V4B（CH32V20x_D6）**，手册零等待 Flash **64KB**、SRAM **20KB**。LinkUtility 读到的 224KB 是 V203 系列总 CodeFlash，**不要**写进链接脚本。

**基本特性：**

- MCU：CH32V203C8T6，最高 144MHz
- 封装：LQFP48
- 板载用户灯默认**没接到 GPIO**，要杜邦线才闪
- **无板载 WCH-Link**，需外接 WCH-LinkE

资料：[CH32V203](https://www.wch.cn/products/CH32V203.html)、[openwch/ch32v20x](https://github.com/openwch/ch32v20x)

本 BSP 骨架对齐主仓 `ch32v208w-r0`（同一套 `CH32V20x` SDK、仓内 `ch32_drivers`），堆和 64K/20K 按手册与 `ch32v307v-r1` 的 `HEAP_BEGIN`/`HEAP_END`。USART1 默认 **PA9 TX / PA10 RX**。

官方软件包 `CH32V20x-SDK-for-RTT` 只带 D8W 启动文件，D6 会 `Exit()`。本 BSP 在 `board/startup_ch32v20x_D6.S` 使用沁恒 EVT 的 D6 向量表，复位后跳到 RT-Thread `entry`（与该包 D8W 的 rtt-patch 相同）。`SConstruct` 会去掉包里对 D6 的 `Exit()`。

## 2 编译说明

| IDE/编译器 | 已测试版本           |
| ---------- | -------------------- |
| GCC        | WCH RISC-V GCC 8.2.0 |

默认配置只打开 GPIO 和 UART1，给 64KB 留余量。PWM、ADC、RTC、看门狗、USB 都在 menuconfig 里，默认关着。64KB 放不下 USB 和 PWM、ADC、RTC、看门狗同时打开。

已在这块板上分开测过：

- 打开 TIM1 通道 1（PA8）、ADC1、RTC（LSE）和独立看门狗，并关掉命令帮助文字。本机那次 Flash **64892** 字节，**99.02%**。
- 只开 USB CDC，关掉上面四项。USB 线程栈用 **1024**（菜单默认 4096，20KB SRAM 不合适）。扁口插电脑、Type-C 插板子 P7 后，电脑串口是 COM12，`help` 和 `version` 有回应。

`pwm` 命令依赖 Finsh 的选项补全。

### 2.1 使用 Env 编译

1. 安装 [WCH RISC-V GCC](https://github.com/NanjingQinheng/sdk-toolchain-RISC-V-GCC-WCH) 与 [Env](https://github.com/RT-Thread/env-windows/releases)
2. 进入本目录，设置 `RTT_EXEC_PATH` 为工具链 `bin`
3. clone [CH32V20x-SDK-for-RTT](https://github.com/kaidegit/CH32V20x-SDK-for-RTT) 到 `packages/CH32V20x-SDK-for-RTT`
4. `scons -j4`，生成 **rtthread.bin**

## 3 硬件连接与下载

### 3.1 SWD（已用于认出芯片）

独立 WCH-LinkE：

- 3V3 — 3V3
- GND — GND
- SWDIO — PA13
- SWCLK — PA14

不要把 LinkE 的 5V USB 和板子供电叠在一起。

### 3.2 USART1（msh）

SWD 那四根（3V3 / GND / PA13 / PA14）不够出串口。LinkE 排针上另外有丝印 **TX** / **RX**（WCH-Link 手册图一），接到板上 **P1** 排针的 PA9 / PA10（沁恒 EVT 原理图 `CH32V203C8T6-R0`）。交叉：

- LinkE **TX** → 板 **PA10**（USART1_RX）
- LinkE **RX** → 板 **PA9**（USART1_TX）
- GND 已共地就不用再加

本机 LinkE 虚拟串口是 **COM11**，115200-8-1-N。

### 3.3 下载

WCH-LinkUtility：Series **CH32V20X**。固件按手册 **64K Flash + 20K SRAM** 链接。默认镜像只含 GPIO 和 UART1，本机 `scons` 为 Flash **44480** 字节，**67.87%**。

V20X 的 Chip Mem 下拉没有 64K+20K（常见是 128K+64K 等），**不要点 Set** 改 option bytes。不要用 307 的 224K+96K。Target → Program（F10），不要勾 Erase All。界面读到 Flash Size 224KB 是系列总 CodeFlash，不是这份 bin 的大小。

复位后 COM11 应出现 RT-Thread / `msh >`。`help`、`ps`、`free` 有输出即启动成功。

### 3.4 已核对的外设

TIM1 通道 1 在 **PA8**，不占用 USART1 和 SWD：

```
pwm probe pwm1
pwm set 1 1000000 500000
pwm enable 1
pwm get 1
```

读回 period `1000000` ns、pulse `500000` ns，即 1 kHz、50%。

ADC1 内部通道要在本板 `board.c` 里打开 `ADC_TempSensorVrefintCmd`。通道 17（Vref）连续读到 `0x5C9`、`0x5C9`、`0x5CA`、`0x5C9`。通道 16（温度）换通道后的第一次会带上一路的值，随后三次都是 `0x6C4`。

```
adc probe adc1
adc enable 17
adc read 17
adc enable 16
adc read 16
```

RTC 用 LSE，不要选 LSI。默认镜像没开 RTC，要在 menuconfig 里打开。设置后几秒再读，时间应往前走：

```
date
date 2026 9 22 12 40 0
date
```

设置后约 5 秒再读，时间从 `12:40:00` 走到 `12:40:05`。

独立看门狗设备名是 `wdt`。`wdt start 5` 之后 `wdt feed`，`msh` 还在；停止喂狗后约 5 秒串口重新打出 RT-Thread 横幅。看门狗一旦启动，复位后如果没有再喂，会按同一超时再次复位。要停掉就重新下载这份默认镜像。V2 的 `drv_iwdt.c` 必须包含 `ch32v20x_iwdg.h`，不能用 V3 的头文件。

## 4 外设表

`bsp/README.md` 里本板勾了 GPIO、UART、ADC、RTC、PWM、WDT、USBD。这些勾选表示驱动在、而且板上见过结果，不是默认镜像全开。SPI、I2C、CAN、DAC、USBH 仍不勾。外部 ADC 通道 0 是 PA0。接到板子自己的 3V3，连续四次都是 `0xFFF`。改接到 GND，四次是 `0x4`、`0x4`、`0x5`、`0x5`。

USB 设备走板子下边的 Type-C（丝印 P7，PA11/PA12）。扁口插电脑，Type-C 插这块板。打开 USB、关掉 PWM、ADC、RTC 和看门狗之后，电脑多出一个串口，这边是 COM12，厂商号 `0FFE`，产品号 `0001`。把控制台切到 `vcom` 之后，在 COM12 上敲 `help` 能收回命令列表，`version` 打出 RT-Thread 5.3.1。PA8 的 PWM 只核对了寄存器读回，没有示波器波形。
