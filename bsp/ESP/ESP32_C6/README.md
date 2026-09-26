# ESP32-C6-DevKitC-1 BSP 说明

## 1 开发板简介

ESP32-C6-DevKitC-1 是乐鑫推出的一款基于 RISC-V 内核的开发板，模组为 ESP32-C6-WROOM-1。本板读到的芯片 revision 是 v0.2。

**基本特性：**

- MCU：ESP32-C6，主频 160MHz，Flash 8MB
- 晶振：40MHz
- USB：2 个 Type-C。标着 UART 的口是 CP210x，接到 UART0（TX GPIO16，RX GPIO17）
- 不用 WCH-Link

更多信息请访问 [ESP32-C6-DevKitC-1](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32c6/esp32-c6-devkitc-1/user_guide.html)

## 2 编译说明

板级包支持 RISC-V GCC 开发环境，以下是具体版本信息：

| IDE/编译器 | 已测试版本 |
| ---------- | ---------- |
| GCC        | Espressif riscv32-esp-elf GCC 11.2.0 |

## 3 使用说明

> 本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果。

### 3.1 使用 Env 编译 BSP

1. 下载 [riscv32-esp-elf GCC 11.2.0](https://github.com/espressif/crosstool-NG/releases/download/esp-2022r1-RC1/riscv32-esp-elf-gcc11_2_0-esp-2022r1-RC1-win64.zip)（Windows）。Linux 用同版本的 `linux-amd64` 包。
2. 下载 Env 工具 [最新版本](https://github.com/RT-Thread/env-windows/releases)
3. 将 [esp-idf 提交 `4fa003074a73774369d38123749fe64b7b4acbd3`](https://github.com/cms19859230182-lang/esp-idf/commit/4fa003074a73774369d38123749fe64b7b4acbd3)（`bsp/esp32c6-scons`）放到 `packages/ESP-IDF-latest`。官方 `RT-Thread-packages/esp-idf` 里还没有这些 C6 源码，`pkgs --update` 下到的包编不过。SConstruct 发现包里没有 C6 时，拉取的也是这一次提交，不跟分支尖走。
4. 在当前 BSP 目录下执行 `scons --exec-path=工具链的bin目录`
5. 编译完成之后会生成 **rtthread.bin** 文件。默认打开 GPIO、UART0 和 ADC。

### 3.2 硬件连接

串口用板上标着 UART 的 USB 口。不用杜邦线，也不用 WCH-Link。

### 3.3 下载

bootloader 和分区表在 `builtin_imgs`。bootloader 必须是这份 ESP32-C6 的，不能用 ESP32-C3 的。

```sh
esptool.py --chip esp32c6 -p COMx -b 460800 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_size 8MB --flash_freq 80m 0x0 builtin_imgs/bootloader.bin 0x8000 builtin_imgs/partition-table.bin 0x10000 rtthread.bin
```

### 3.4 运行结果

在终端工具里打开串口（115200-8-1-N），先打开串口再复位，可以看到 RT-Thread 的输出信息和 `msh >`。`help`、`version` 有回应。

GDB 默认关闭。要在出错后停住，打开 `BSP_ENABLE_GDBSTUB` 再烧录，然后用本目录的 `esp32c6.gdb`。
