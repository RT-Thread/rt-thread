# D213ECV-DEMO-V4-0

[English](README.md) | [中文](README_zh.md)

## 简介

本 BSP 支持 ArtInChip D213ECV-DEMO-V4-0 开发板，RT-Thread 在单核 T-Head C906 上以 M-mode 运行。

| 项目 | 说明 |
|------|------|
| SoC | ArtInChip D213ECV |
| CPU | T-Head C906，RV64GC |
| 内存 | 128 MiB DDR3，起始地址 `0x40000000` |
| 控制台 | UART0，PA.0（TX）/ PA.1（RX），115200 波特率，8N1，无流控 |

硬件信息请参阅[官方开发板文档](https://aicdoc.artinchip.com/topics/product/d213ecV4.html)。

## 支持功能

| 功能 | 说明 |
|------|------|
| 内核移植 | RT-Thread RISC-V common port，包含双精度 FPU 上下文切换 |
| 系统时钟 | CLINT 定时器，默认系统 Tick 为 1000 Hz |
| 中断控制器 | PLIC |
| UART0 | Serial-v1，轮询发送，线程轮询接收 |
| FinSH/MSH | 默认启用 |
| 堆与设备框架 | 默认启用 |

UART0 面向交互式控制台，持续输入或调度长时间延迟可能导致数据丢失。不支持 UART 硬件中断、DMA 和流控。BSP 提供 UART0 所需的时钟、复位和引脚配置，DDR 与 PLL 由 Bootloader 初始化。

## 构建与配置

安装 Python 3、SCons、kconfiglib，以及支持 RV64GC 和 `lp64d` ABI 的 GNU 裸机 RISC-V 工具链。推荐使用 GCC 10.2.0。

在仓库根目录执行：

```sh
python -m pip install scons kconfiglib
cd bsp/artinchip/d213ecv-demo-v4-0
export RTT_EXEC_PATH=/path/to/riscv-toolchain/bin
scons --pyconfig-silent
scons -j8
```

PowerShell 中使用 `$env:RTT_EXEC_PATH = 'C:/path/to/riscv-toolchain/bin'` 设置工具链路径。默认编译器前缀为 `riscv64-unknown-elf-`，使用其他前缀时设置 `RTT_CC_PREFIX`。也可通过 PATH 查找编译器。

构建产物为 `rtthread.elf`、`rtthread.bin` 和 `rtthread.map`。

修改配置时执行：

```sh
scons --menuconfig
scons --pyconfig-silent
scons -j8
```

请通过配置工具生成 `rtconfig.h`，不要直接编辑该文件。

| 板级选项 | 默认值 | 说明 |
|----------|--------|------|
| `BSP_USING_UART0` | 启用 | UART0 控制台，依赖 Serial-v1 |
| `BSP_UART_CLK_FREQ` | 48000000 | UART0 输入时钟，单位 Hz |
| `BSP_CLINT_FREQ` | 4000000 | CLINT 时基，单位 Hz |

时钟设置必须与 Bootloader 配置一致，这些选项不会改变硬件时钟分频器。UART0 驱动不支持 Serial-v2。

UTest 默认关闭。如需使用，在 menuconfig 中启用 `RT_USING_UTESTCASES` 并选择所需测试用例，然后重新生成配置并构建。

使用 `scons --dist` 导出独立工程。解压 `dist/project.zip`，清除已设置的 `RTT_ROOT` 环境变量，在解压后的 `project/` 目录运行相同的配置与构建命令。

## 下载与运行

本 BSP 需要外部 ArtInChip 兼容 Bootloader。请按 Bootloader 要求将 `rtthread.bin` 打包为 FIT 或烧录镜像，并使用匹配的分区布局。

| 区域 | 地址范围 |
|------|----------|
| RT-Thread，包含堆 | `0x40000000`–`0x477fffff`（120 MiB）|
| Bootloader 保留区 | `0x47800000`–`0x47ffffff`（8 MiB）|
| BIN 加载地址与 ELF 入口 | `0x40000000` |

进入 RT-Thread 前，Bootloader 必须：

1. 初始化 DDR、PLL、总线时钟及 CPU 内存/Cache 属性，将 MMIO 区域设为不可缓存。
2. 提供与 BSP 配置一致的 UART0 输入时钟和 CLINT 时基。
3. 将镜像加载到 `0x40000000`；Cache 开启时，将已加载数据从数据 Cache 写回，并同步指令 Cache。
4. 在 hart 0、M-mode 下进入镜像，进入时关闭中断，无活动 DMA，也无尚未完成的已 claim PLIC 中断。

将串口终端连接至 UART0，设置为 115200 波特率、8 位数据、无校验、1 位停止位、无流控。启动后控制台显示：

```text
RT-Thread Operating System
D213ECV-DEMO-V4-0
msh >
```

使用 `help` 查看 shell 命令，`ps` 查看线程，`free` 查看堆使用情况，`list device` 查看注册设备。默认配置注册 `uart0`。

## UART 使用

UART0 默认启用。修改串口格式时，在打开设备前通过 `RT_DEVICE_CTRL_CONFIG` 和 `struct serial_configure` 配置。支持 5–8 位数据、无/奇/偶校验、1 或 2 位停止位，但不支持 5 位数据加 2 位停止位。可用波特率取决于配置的输入时钟和 1–65535 的硬件分频范围。

使用 `RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX` 打开设备可启用缓冲接收与接收回调。本驱动的 `INT_RX` 通过轮询线程实现，不使用硬件中断。不带 `INT_RX` 打开时可轮询读取。

重新配置会清空硬件 FIFO，请先停止收发。发送等待有超时限制，应检查返回的实际写入字节数。不支持 RS-485 方向控制。

## 参考资料与许可证

- [ArtInChip 开发板文档](https://aicdoc.artinchip.com/topics/product/d213ecV4.html)
- [ArtInChip Luban-Lite SDK](https://gitee.com/artinchip/luban-lite)，本 BSP 使用的 SoC 定义与硬件初始化时序来源。

BSP 使用 Apache-2.0 许可证，源码文件保留相应版权与许可证声明。
