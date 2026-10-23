# Allwinner H616

[English](README.md)

本 BSP 面向 Allwinner H616 系列 64 位 ARM 平台，使用 RT-Thread Device Model
（DM）驱动，并通过板子既有的 TF-A 与 U-Boot 启动 AArch64 镜像。生成的
`rtthread.bin` 是裸镜像，不包含也不替换启动固件或设备树。

## 板卡介绍

当前使用 MQ-Quad 板。现有固件提供的 DTB 文件名为
`sun50i-h616-orangepi-zero2.dtb`，所以启动时会显示 `OrangePi Zero2`。这只是
固件设备树的型号字符串，并不表示 MQ-Quad 的引脚和 Orange Pi Zero2 完全相同。
尤其不能只依据该名称启用以太网、Wi-Fi、显示或 GPIO 外设，应以板子原理图为准。

## 工具链

需要裸机 AArch64 GNU 工具链。本 BSP 使用 Arm GNU Toolchain 14.3.Rel1 的
`aarch64-none-elf-gcc` 编译验证；其它兼容工具链也可通过以下环境变量选择：

```sh
export RTT_EXEC_PATH=/opt/arm-gnu-toolchain-14.3.rel1-x86_64-aarch64-none-elf/bin
export RTT_CC_PREFIX=aarch64-none-elf-
aarch64-none-elf-gcc --version
```

SCons 可由 RT-Thread ENV 安装，也可以使用 `python -m pip install scons`。

## 构建

```sh
cd bsp/allwinner/h616
scons --menuconfig
scons -j$(nproc)
```

构建产物：

- `rtthread.elf`：调试和符号解析使用；
- `rtthread.bin`：由 U-Boot 加载的裸 AArch64 镜像。

`SOC_H616` 会选择 MMU、SMP、Cache、DM 与 OFW 支持。

## 启动

保留板子原有的 TF-A、U-Boot、Linux 镜像和基础 DTB。U-Boot 启动脚本应将
`rtthread.bin` 加载到正常的内核加载地址，再加载相同的基础 DTB 和该板必须的 DT
overlay，最后使用标准 AArch64 镜像启动命令并传入该 DTB。当前固件使用
`kernel_addr_r=0x40080000`、`fdt_addr_r=0x4fa00000`。

将裸镜像放到启动分区，例如 `/boot/rtthread.bin`。保留现有 `boot.scr` 中的
overlay 处理。

启动参数需要保留串口控制台。当前固件中 UART0 位于 `0x05000000`，可使用：

```text
earlycon=uart8250,mmio32,0x05000000,115200n8 console=ttyS0,115200n8
```

启用 DMA 或视频负载时，可按需添加 `cma=` 与 `coherent_pool=`。大小应按板卡内存
规划确定，且不得与固件保留内存重叠。

## 设备驱动支持

| 设备 | 状态 | 说明 |
| --- | --- | --- |
| UART | 支持 | DesignWare 8250 控制台。 |
| 时钟 / 复位 / pinctrl / 稳压器 | 支持 | H616 CCU/R CCU、引脚控制器和 AXP313A PMIC。 |
| RTC | 支持 | 日历和闹钟框架。 |
| DMA | 支持 | Sunxi DMA 控制器。 |
| SDIO | 支持 | SDC0、SDC1 和 SDC2 host。 |
| I2C | 支持 | Sunxi I2C 控制器。 |
| SPI | 支持 | Sunxi SPI 控制器。 |
| PWM | 支持 | Sunxi PWM 控制器。 |
| LED | 支持 | DT GPIO LED。 |
| Watchdog | 支持 | Sunxi watchdog。 |
| 温度传感器 | 支持 | 四个 H616 thermal sensor。 |
| 红外接收 | 支持 | Sunxi IR receiver。 |
| 内部 codec | 支持 | `sound0`；扬声器需要接功放。 |
| HDMI 音频 | 支持 | AHUB I2S1 LPCM 路径（`hdmi-sound0`）。 |
| JPEG 解码 | 支持 | 视频引擎 JPEG/MJPEG 解码器（`jpegd0`）。 |
| DE33 / HDMI 视频 | 支持 | DE33 mixer、TCON-TV 和 DW-HDMI framebuffer 路径。 |
| G2D | 支持 | H616 图形加速器。 |
| HWCrypto | 支持 | H616 CE AES 和 TRNG。 |
| GPADC / LRADC | 支持 | H616 模拟输入控制器。 |

## 参考资料

- [Allwinner H616 Linux device tree binding sources](https://github.com/torvalds/linux/tree/master/Documentation/devicetree/bindings)
- [RT-Thread Device Model 文档](https://www.rt-thread.io/document/site/#/rt-thread-version/rt-thread-standard/programming-manual/device/device)
