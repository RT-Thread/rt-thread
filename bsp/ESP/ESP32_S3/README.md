# ESP32-S3-DevKitM-1 BSP 说明

## 1 开发板简介

ESP32-S3-DevKitM-1 是乐鑫推出的一款基于 Xtensa LX7 的开发板，模组为 ESP32-S3-MINI-1。本板读到的芯片是 QFN56，revision v0.2。这颗不是 RISC-V，不能用 ESP32-C3 / C6 的工具链，也不能搬它们的中断接法。

**基本特性：**

- MCU：ESP32-S3，本 BSP 以单核模式运行，主频 160MHz，Flash 8MB，DIO
- 晶振：40MHz
- 片内 PSRAM 8MB，本版没有启用
- USB：标着 UART 的口是 CP210x，接到 UART0（TX GPIO43，RX GPIO44）
- 不用 WCH-Link

更多信息请访问 [ESP32-S3-DevKitM-1](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitm-1/user_guide.html)

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设** | **支持情况** | **备注** |
| :----------- | :----------: | :------- |
| UART         |     支持     | UART0，TX GPIO43，RX GPIO44。115200，能进 msh |
| GPIO         |    待支持    | `help` 里有 `pin`，还没在板上做电平输入 |
| I2C          |    待支持    |          |
| SPI          |    待支持    |          |
| ADC          |    待支持    |          |
| PWM          |    待支持    |          |
| Wi-Fi        |    待支持    |          |
| BLE          |    待支持    |          |
| 板载 LED     |    待支持    |          |
| PSRAM        |    待支持    | 8MB 未启用，堆来自片内 SRAM |

### IO 在板级支持包中的映射情况

| IO     | 板级包中的定义 |
| ------ | -------------- |
| GPIO43 | UART0_TX       |
| GPIO44 | UART0_RX       |

## 2 编译说明

板级包使用乐鑫 Xtensa GCC，以下是具体版本信息：

| IDE/编译器 | 已测试版本 |
| ---------- | ---------- |
| GCC        | Espressif xtensa-esp32s3-elf GCC 12.2.0（esp-12.2.0_20230208） |

不要用 `riscv32-esp-elf`。

## 3 使用说明

> 本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果。

### 3.1 使用 Env 编译 BSP

1. 下载 [xtensa-esp32s3-elf GCC 12.2.0](https://github.com/espressif/crosstool-NG/releases/tag/esp-12.2.0_20230208)。Windows 用该标签下的 mingw 包，Linux 用同版本的 linux 包。
2. 下载 Env 工具 [最新版本](https://github.com/RT-Thread/env-windows/releases)
3. 在当前 BSP 目录执行 `pkgs --update`，拉官方 `RT-Thread-packages/esp-idf`。这份包的 SConscript 只编 ESP32-C3；S3 的源文件由本目录 `idf_components/SConscript` 从包里挑出来编。
4. 在当前 BSP 目录下执行 `scons --exec-path=工具链的bin目录`。改过 `idf_port/ld/sections.ld` 之后先删掉 `rtthread.elf` 再编，scons 不跟踪链接脚本。
5. 编译完成之后会生成 **rtthread.bin** 文件。默认打开 GPIO 和 UART0。GPIO 还没在板上做电平测试。

### 3.2 硬件连接

串口用板上标着 UART 的 USB 口。不用杜邦线，也不用 WCH-Link。

### 3.3 下载

bootloader 和分区表在 `builtin_imgs`。必须是这份 ESP32-S3 的，不能用 ESP32-C3 的。

```sh
esptool.py --chip esp32s3 -p COMx -b 460800 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_size 8MB --flash_freq 80m 0x0 builtin_imgs/bootloader.bin 0x8000 builtin_imgs/partition-table.bin 0x10000 rtthread.bin
```

### 3.4 运行结果

在终端工具里打开串口（115200-8-1-N），先打开串口再复位，可以看到 RT-Thread 的输出信息、`Hello! RT-Thread on ESP32-S3-DevKitM-1` 和 `msh >`。`help`、`version`、`ps`、`free` 有回应。隔开再执行 `ps`，`left tick` 会变。

中断看门狗默认关掉。IDF 用自己的向量去喂 TG1WDT，这份 BSP 换了向量（`libcpu/xtensa/esp32s3/context_gcc.S`）。不关的话，启动大约 300 ms 后复位，原因是 `rst:0x8 (TG1WDT_SYS_RST)`。

本 BSP 只服务 level-1 中断。注册中断时要带 `ESP_INTR_FLAG_LEVEL1`。
