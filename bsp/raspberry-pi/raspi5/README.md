# Raspberry Pi 5 BSP 使用说明

[English](README_en.md)

## 1. 简介

本 BSP 为 Raspberry Pi 5 提供 RT-Thread 64 位板级支持，目标 SoC 为 Broadcom BCM2712（4 核 Cortex-A76），并使用 RT-Thread Device Model 管理板载设备及 RP1 南桥外设。

当前启动流程为：Raspberry Pi 固件加载 U-Boot，U-Boot 再加载 `rtthread.bin`，并将固件提供的设备树传递给 RT-Thread。BSP 默认启用 SMP，控制台设备为设备树中的 `uart10`。

## 2. 准备工作

### 2.1 硬件

- Raspberry Pi 5；
- microSD 卡及读卡器；
- 3.3 V TTL 串口工具；
- 可选：用于 TFTP 启动的有线网络。

> 串口电平必须为 3.3 V，请勿直接连接 RS-232 或 5 V 串口。默认波特率为 `115200 8N1`，关闭硬件和软件流控。

### 2.2 软件

- Python 3；
- SCons 及 RT-Thread Env 工具；
- AArch64 bare-metal GCC 工具链；
- 适用于 Raspberry Pi 5 的 U-Boot；
- 可选：TFTP 服务器。

默认工具链前缀为 `aarch64-none-elf-`，`rtconfig.py` 中的默认搜索路径为：

```text
/opt/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/bin/
```

推荐通过环境变量指定本机工具链，避免修改仓库文件：

```bash
export RTT_EXEC_PATH=/path/to/aarch64-toolchain/bin
export RTT_CC_PREFIX=aarch64-none-elf-
```

编译脚本优先使用 `-mtune=cortex-a76`；旧工具链不支持时，会依次回退到 `cortex-a73` 或 `generic`。

## 3. 配置与编译

进入 BSP 目录：

```bash
cd bsp/raspberry-pi/raspi5
```

如需调整功能，可先打开配置菜单：

```bash
scons --menuconfig
```

编译 BSP：

```bash
scons -j$(nproc)
```

Windows 环境可直接使用 `scons`，或将 `$(nproc)` 替换为合适的并行任务数。

成功后会生成：

| 文件 | 说明 |
| --- | --- |
| `rtthread.elf` | 带符号信息的 ELF 文件，用于调试和反汇编 |
| `rtthread.bin` | U-Boot 实际加载的裸二进制镜像 |
| `rtthread.map` | 链接映射文件 |
| `rtt.asm` | 反汇编结果 |

`rtthread.bin` 的加载地址为 `0x210000`，与默认配置中的 `ARCH_TEXT_OFFSET` 一致，请勿随意修改启动命令中的地址。

## 4. 准备启动介质

### 4.1 准备 U-Boot

先准备一张能够由 Raspberry Pi 5 固件正常识别的 microSD 卡。将适用于 Raspberry Pi 5 的 U-Boot 镜像放到 FAT 启动分区根目录，并命名为：

```text
u-boot.bin
```

本目录的 [`tools/config.txt`](tools/config.txt) 包含 BSP 所需的最小固件配置：

```ini
kernel=u-boot.bin
dtparam=pciex1
```

如果启动分区已经存在 `config.txt`，请合并上述配置，不要直接覆盖其中仍需保留的显示、串口或其他板级设置。

### 4.2 放置 RT-Thread 镜像

使用 SD 卡启动时，将编译生成的 `rtthread.bin` 复制到第一个 FAT 分区的根目录：

```text
<boot partition>/rtthread.bin
```

默认命令使用 U-Boot 的 `mmc 0:1`。如果实际 SD 卡控制器或分区编号不同，请先用以下命令确认：

```text
mmc list
mmc dev 0
part list mmc 0
fatls mmc 0:1
```

## 5. U-Boot 启动

### 5.1 设置公共启动参数

在 U-Boot 控制台设置 RT-Thread 使用的启动参数：

```text
setenv bootargs_rtt 'earlycon cma=8M coherent_pool=2M'
saveenv
```

启动命令会复制固件提供的活动设备树，并更新 `/chosen/bootargs`。不要使用与当前开发板不匹配的静态 DTB 替代该设备树，否则 RP1、PCIe 和板载外设信息可能不完整。

### 5.2 从 SD 卡加载

```text
setenv bootrtt 'mmc dev 0; fatload mmc 0:1 0x210000 rtthread.bin; fdt addr ${fdtcontroladdr}; fdt move ${fdt_addr_r} 0x20000; fdt addr ${fdt_addr_r}; fdt resize 8192; setenv bootargs ${bootargs_rtt}; fdt set /chosen bootargs ${bootargs}; booti 0x210000 - ${fdt_addr_r}'
saveenv
run bootrtt
```

如需每次上电自动启动，可在确认手动启动正常后设置：

```text
setenv bootcmd 'run bootrtt'
saveenv
```

### 5.3 从 TFTP 加载

先将 `rtthread.bin` 放到 TFTP 服务器根目录。下面地址仅为示例，请根据实际网络修改：

```text
setenv bootrtt_tftp 'setenv ethprime eth0; setenv ipaddr 192.168.10.2; setenv serverip 192.168.10.1; setenv netmask 255.255.255.0; ping 192.168.10.1; tftp 0x210000 rtthread.bin; fdt addr ${fdtcontroladdr}; fdt move ${fdt_addr_r} 0x20000; fdt addr ${fdt_addr_r}; fdt resize 8192; setenv bootargs ${bootargs_rtt}; fdt set /chosen bootargs ${bootargs}; booti 0x210000 - ${fdt_addr_r}'
saveenv
run bootrtt_tftp
```

如果 U-Boot 中的有线网卡名称不是 `eth0`，可通过 `printenv ethact ethprime` 或 `bdinfo` 检查后调整 `ethprime`。

## 6. 启动结果

启动成功后，串口应出现 RT-Thread 标志、SMP 初始化信息，随后进入 MSH：

```text
 \ | /
- RT -     Thread Operating System
 / | \
 2006 - 2026 Copyright by RT-Thread team
Hi, this is RT-Thread!!
msh />
```

实际版本号、构建时间和设备初始化日志会随配置变化。

## 7. 默认配置

默认 `rtconfig.h` 启用了以下主要功能。是否能探测到具体设备，仍取决于 Raspberry Pi 固件版本、活动设备树、扩展板和外设连接情况。

| 类别 | 默认配置中的主要支持 |
| --- | --- |
| CPU | AArch64、4 核 SMP、MMU、Cache、ASID |
| 控制台 | PL011/8250 串口，默认 `uart10` |
| 存储 | SDHCI/MMC、FatFs、NVMe over PCIe |
| 网络 | RP1 以太网、PHY、lwIP、DHCP |
| 总线 | PCIe、I2C、SPI、SDIO、Device Tree/OFW |
| RP1 外设 | ADC、PWM、GPIO/Pinctrl、时钟、MFD |
| 系统服务 | RTC、Watchdog、DMA、Thermal、DVFS、Mailbox |
| 多媒体与输入 | I2S Audio、Framebuffer、Touchscreen、Joystick、Keyboard |
| 用户态 | RT-Smart、DFS、POSIX、LWP、动态链接支持 |

## 8. 常见问题

### 8.1 U-Boot 找不到 `rtthread.bin`

先执行：

```text
fatls mmc 0:1
```

确认文件名、设备号和分区号。Linux 文件名区分大小写。

### 8.2 `Bad Linux ARM64 Image magic!` 或跳转后无输出

- 确认加载的是 `rtthread.bin`，而不是 `rtthread.elf`；
- 确认加载及启动地址均为 `0x210000`；
- 确认使用 `booti 0x210000 - ${fdt_addr_r}`；
- 检查串口参数以及设备树中的 `stdout-path`。

### 8.3 设备树或 RP1 外设初始化失败

- 确认 Raspberry Pi 固件和 U-Boot 支持 Raspberry Pi 5；
- 确认 `config.txt` 中包含 `dtparam=pciex1`；
- 保留并传递固件提供的活动设备树；
- 不要在 U-Boot 中覆盖成其他 Raspberry Pi 型号的 DTB。

### 8.4 TFTP 下载失败

检查 `ipaddr`、`serverip`、`netmask`、TFTP 根目录、防火墙和网线连接，并先在 U-Boot 中执行 `ping ${serverip}`。

## 9. 重新配置后的注意事项

运行 `scons --menuconfig` 后，配置可能与本文记录的默认 `rtconfig.h` 不同。提交 BSP 配置变更前，应同时检查生成的 `rtconfig.h`，并确认新增驱动在 Raspberry Pi 5 实机上完成验证。
