ifconfig e0 192.168.10.2 192.168.10.1 255.255.255.0
ping 192.168.10.1

[English](README_en.md) | **中文**

# SpacemiT K1 BSP

## 1. 简介

本 BSP 将 RT-Thread 标准版移植到 SpacemiT K1 64 位 RISC-V SoC。当前启动方式仅在
**Banana Pi BPI-F3 SBC** 上验证，依赖开发板原厂 U-Boot/OpenSBI 和其动态选择的
Device Tree。

默认配置使用 MMU 并启动 4 个 CPU，从 S-mode 运行 RT-Thread。早期控制台使用
SBI，正常串口为 `ttyS0`，参数为 115200 8N1。

## 2. 支持情况

| 功能 | 状态 | 说明 |
| --- | --- | --- |
| RISC-V MMU / SMP | 支持 | 默认启动 4 个 CPU |
| UART / early console | 支持 | SBI early console，8250/PXA UART |
| Clock / reset / power domain | 支持 | K1 CCU、reset 和 PM domain |
| I2C / SPI / QSPI / PWM | 支持 | 包含 PMIC 子设备 |
| SD / eMMC | 支持 | SDHCI，eMMC HS400 |
| RTC / ADC / power key | 支持 | SpacemiT PMIC |
| PCIe / NVMe | 支持 | DesignWare PCIe host |
| Ethernet / PTP | 支持 | K1X EMAC；需启用 `RT_USING_ETHERNET` 和 `RT_ETHERNET_K1X_EMAC` |
| HDMI framebuffer | 支持 | 冷启动建立 HDMI 显示链路 |
| JPU / V2D | 支持 | JPEG 解码和 2D 加速 |
| HDMI / ES8326 audio | 支持 | 48 kHz、双声道、16-bit PCM |
| DVFS / thermal | 支持 | CPUfreq、OPP 和 4 路温度区 |
| AES / hardware RNG / eFuse | 支持 | 包含 SoC ID 和序列号 |
| MIPI DSI / camera / USB | 未移植 | 当前 BSP 不包含这些功能 |

## 3. 构建环境

### 3.1 依赖

建议使用 64 位 Linux 主机。Ubuntu/Debian 可安装：

```shell
sudo apt install scons python3 python3-pip
pip3 install kconfiglib
```

### 3.2 工具链

可从以下地址获取 RISC-V64 Linux musl GCC 工具链：

- SpacemiT 官方工具链归档：<https://archive.spacemit.com/toolchain/>
- RT-Thread RISC-V64 musl 工具链：<https://download.rt-thread.org/rt-smart/riscv64/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_251248.tar.bz2>

以解压到 `/opt/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu` 为例：

```shell
export RTT_CC=gcc
export RTT_EXEC_PATH=/opt/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin
export RTT_CC_PREFIX=riscv64-unknown-linux-musl-
```

可使用下列命令检查工具链：

```shell
${RTT_EXEC_PATH}/${RTT_CC_PREFIX}gcc --version
```

## 4. 编译

进入 BSP 目录：

```shell
cd bsp/spacemit/k1
```

需要调整功能时先运行：

```shell
scons --menuconfig
```

编译：

```shell
scons -j$(nproc)
```

编译成功后会生成：

| 文件 | 用途 |
| --- | --- |
| `rtthread.elf` | 带调试信息的 ELF 文件 |
| `rtthread.bin` | U-Boot 加载的内核镜像 |
| `rtthread.map` | 链接 map |

清理构建产物：

```shell
scons -c
```

## 5. Banana Pi BPI-F3 启动

> 本节命令仅适用于 Banana Pi BPI-F3 原厂 U-Boot 环境。其他 K1 开发板的分区、
> Device Tree 和 U-Boot 环境变量可能不同。

### 5.1 准备镜像

将 `rtthread.bin` 放到 BPI-F3 启动文件系统根目录，即与 Linux `Image` 和
`k1-x_*.dtb` 相同的目录。U-Boot 的 `loadknl` 命令会从当前启动文件系统加载
`knl_name` 指定的文件。

### 5.2 配置 U-Boot

在 U-Boot 控制台执行以下命令：

```shell
setenv rtt_bootargs 'earlycon=sbi console=ttyS0,115200 cma=32M coherent_pool=8M root=sd0p4 rootfstype=elm rootwait rw'
setenv boot_rtt 'setenv knl_name rtthread.bin; setenv bootargs ${rtt_bootargs}; run detect_dtb; run loadknl; run loaddtb; setenv ramdisk_combo -; run start_kernel'
saveenv
```

`saveenv` 只需执行一次。之后可使用以下命令启动 RT-Thread：

```shell
run boot_rtt
```

主要 bootargs 说明：

- `earlycon=sbi`：在正常 UART 驱动就绪前使用 SBI 输出。
- `cma=32M coherent_pool=8M`：为 framebuffer、JPU、V2D、NVMe 和其他 DMA 设备预留内存。
- `root=sd0p4 rootfstype=elm`：将 RT-Thread 设备 `sd0p4` 上的 FAT 文件系统作为根文件系统。

如果存储设备的枚举顺序或分区布局不同，需要相应修改 `root=`。原厂 U-Boot
必须存在 `detect_dtb`、`loadknl`、`loaddtb` 和 `start_kernel` 这几个环境命令。

### 5.3 启动输出

启动成功后串口将显示：

```text
 \ | /
- RT -     Thread Operating System
 / | \
 ...
msh />
```

## 6. 常用验证命令

```shell
list_device
list_irq
list_blk
list_thermal
list_dvfs
dvfs dump cpufreq0
core_mark
adc probe adc0
adc read 0
date
jpu_show /path/to/image.jpg fb0
v2d_test fb0
audio_test snd-hdmi 2
ptp_test
```

`jpu_show` 仅从文件系统读取 baseline JPEG，BSP 不内置测试图片。

使用网卡前请先在 `menuconfig` 中启用 Ethernet 和 K1X EMAC，然后根据实际端口
`e0` 或 `e1` 配置地址：

```shell
ifconfig e1 192.168.10.2 192.168.10.1 255.255.255.0
ping 192.168.10.1 e1
```

## 7. 注意事项

- Device Tree 由 BPI-F3 U-Boot 的 `detect_dtb` 选择，不要使用与开发板不匹配的 DTB。
- HDMI 显示依赖 `cma` 和 `coherent_pool`；内存过小时 framebuffer 初始化会失败。
- HDMI ADMA 依赖嵌入镜像的 K1 RCPU `esos.elf` 和 Device Tree 中的 reserved-memory。
- MIPI 显示未验证，当前显示驱动仅面向 HDMI。

