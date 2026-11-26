[English](README_en.md) | **中文**

# SpacemiT K1 BSP

## 简介

SpacemiT K1（进迭时空 K1）是一款 64 位 RISC-V SoC，集成 8 个 X60 CPU 核心，
支持浮点和向量扩展，并提供 SD/eMMC、PCIe、以太网、显示及音频等外设接口。

本 BSP 基于 RT-Thread 标准版和设备模型，通过 Device Tree 描述板级硬件，
由 U-Boot/OpenSBI 引导，在 S-mode 下运行。默认启用 MMU 和 8 核 SMP，
支持存储、网络、多媒体及电源管理等功能。

验证平台为 **Banana Pi BPI-F3 SBC**。早期控制台使用 SBI，正常控制台为
UART0，串口参数为 115200 8N1。下文启动命令仅适用于该板原厂固件环境。

## 支持情况

| 功能 | 状态 | 说明 |
| --- | --- | --- |
| MMU / SMP | 支持 | 默认启用 8 个 CPU 核心 |
| UART / early console | 支持 | UART0、SBI 早期输出 |
| Clock / reset / power domain | 支持 | 时钟、复位及电源域控制 |
| GPIO / pinctrl / I2C / PWM | 支持 | 引脚配置及基础外设 |
| SPI / QSPI | 支持 | SPI NOR |
| SD / eMMC | 支持 | SDHCI、eMMC HS400 |
| RTC / ADC / 电源键 | 支持 | SpacemiT PMIC 子设备 |
| PCIe / NVMe | 支持 | PCIe host、NVMe 块设备 |
| Ethernet / PTP | 支持 | K1X EMAC、PTP 时钟 |
| HDMI framebuffer | 支持 | 支持冷启动显示 |
| JPU / V2D | 支持 | JPEG 解码、2D 图形加速 |
| HDMI / ES8326 audio | 支持 | 48 kHz、双声道、16-bit PCM |
| CPUfreq | 支持 | OPP 调频调压 |
| Thermal | 支持 | 4 路温度传感器，采样时序修复待验证 |
| AES / RNG / eFuse | 支持 | 硬件加密、随机数及芯片信息 |
| Display | 支持 | HDMI |

## 编译

安装 SCons、Python 3 和 kconfiglib。工具链下载：

- [SpacemiT 工具链归档](https://archive.spacemit.com/toolchain/)
- [RT-Thread RISC-V64 musl GCC](https://download.rt-thread.org/rt-smart/riscv64/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_251248.tar.bz2)

以工具链安装在 `/opt` 为例，在 RT-Thread 根目录执行：

```shell
cd bsp/spacemit/k1
export RTT_CC=gcc
export RTT_EXEC_PATH=/opt/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin
export RTT_CC_PREFIX=riscv64-unknown-linux-musl-
scons
```

生成 `rtthread.bin` 和 `rtthread.elf`。可通过 `scons --menuconfig` 调整配置。

## 启动

以下命令仅适用于 **Banana Pi BPI-F3 原厂 U-Boot/OpenSBI 环境**。

将 `rtthread.bin` 放到启动分区中，与 Linux `Image`、`k1-x_*.dtb` 同目录。
在 U-Boot 控制台执行：

```shell
setenv rtt_bootargs 'earlycon=sbi console=ttyS0,115200 cma=32M coherent_pool=8M root=sd0p4 rootfstype=elm rootwait rw'
setenv boot_rtt 'setenv knl_name rtthread.bin; setenv bootargs ${rtt_bootargs}; run detect_dtb; run loadknl; run loaddtb; setenv ramdisk_combo -; run start_kernel'
saveenv
run boot_rtt
```

后续直接执行 `run boot_rtt`。根据实际分区修改 `root=sd0p4`；
保留 DMA 内存参数以供显示等设备使用。
