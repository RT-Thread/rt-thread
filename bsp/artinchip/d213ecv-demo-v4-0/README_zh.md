# D213ECV-DEMO-V4-0

[English](README.md) | [中文](README_zh.md)

## 硬件信息

- 开发板：ArtInChip D213ECV-DEMO-V4-0。
- SoC：D213ECV，T-Head C906，RV64GC（IMAFDC），单 hart，M-mode。
- 内存：128 MiB DDR3，起始地址 `0x40000000`。
- 控制台：UART0，PA.0 TX / PA.1 RX，115200 波特率、8N1、无流控。
- [官方开发板资料](https://aicdoc.artinchip.com/topics/product/d213ecV4.html)。

| 功能 | 支持情况 |
|------|----------|
| 启动、调度器、双精度 FPU 上下文 | RT-Thread RISC-V common port |
| 系统 Tick | D213 CLINT 比较器与 time CSR，复用 common 定时器核心 |
| 中断控制器 | common PLIC 驱动，补充 D213 priority-enable 初始化 |
| 时钟/复位 | GPIO 与 UART0 的门控；PLL/DDR 由 loader 管理 |
| UART0 | Serial-v1，轮询发送，接收线程填充标准接收 FIFO |
| FinSH/MSH、堆、设备框架 | 默认开启 |

UART 适配器保持UART0 的 PLIC 中断屏蔽，以标称 1 ms 间隔轮询接收。接收线程比 FinSH 高一个优先级，避免控制台持续输出时接收轮询无法运行；默认串口接收缓冲区为 512 字节。该方案面向交互式控制台，持续大流量传输或调度长时间延迟可能丢字节。不支持 UART 硬件中断和 DMA；由于使用 Serial-v1 API，选择 Serial-v2 时会关闭 UART0 选项。

## UART 配置

通过 `BSP_USING_UART0` 默认启用 UART0，使用 PA.0 TX / PA.1 RX（功能 5），沿用 Bootloader 配置的输入时钟，默认为 48 MHz。

打开设备前，通过 `RT_DEVICE_CTRL_CONFIG` 和 `struct serial_configure` 配置。适配器接受 5–8 位数据、无/奇/偶校验，以及 1 或 2 位停止位。5 位数据加 2 位停止位会被拒绝：硬件实际产生 1.5 位停止位，Serial-v1 无法表达。不支持的格式、流控、反相/MSB 优先，以及超出 1–65535 的分频值均返回 `-RT_EINVAL`，且不修改寄存器。配置时先清空 FIFO，最多等待 100 ms 让控制器进入空闲状态，并回读 LCR 确认切换成功后才访问分频寄存器。忙等待超时返回 `-RT_ETIMEOUT`，LCR 写入未生效返回 `-RT_EIO`。波特率采用最接近的整数分频，实际误差取决于输入时钟和请求值。

使用 `RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX` 打开可使用框架接收 FIFO 和回调；不带 `INT_RX` 时可轮询读取。这里的 `INT_RX` 选择 Serial-v1 缓冲接口，硬件中断接收仍关闭。关闭设备后停止缓冲接收。重新配置会清空硬件 FIFO，应停止收发后再配置。不提供 DMA 和 RS-485 方向控制。

## 独立构建

安装 Python 3、SCons、kconfiglib，以及支持 RV64GC、`lp64d` ABI 并提供 `riscv64-unknown-elf-*` 的 GNU 裸机 RISC-V 工具链：

```sh
python -m pip install scons kconfiglib
cd bsp/artinchip/d213ecv-demo-v4-0
export RTT_EXEC_PATH=/path/to/riscv-toolchain/bin
scons --pyconfig-silent
scons -j8
```

PowerShell 使用以下方式设置工具链路径：

```powershell
$env:RTT_EXEC_PATH = 'C:/path/to/riscv-toolchain/bin'
scons --pyconfig-silent
scons -j8
```

也可将编译器加入 PATH，通过 `RTT_CC_PREFIX` 指定其他工具链前缀。构建产物为 `rtthread.elf`、`rtthread.bin` 和 `rtthread.map`。

本地构建使用 Xuantie V2.6.1（GCC 10.2.0），CI 使用 RT-Thread 公开的 GCC 10.2.0 RISC-V 工具链。针对 GCC 12 及以上版本，`rtconfig.py` 会在 ISA 字符串中显式加入 `zicsr_zifencei`；本 BSP 尚未实际验证这些新版工具链。

## 配置与独立工程导出

默认 `.config` 启用 UART0/Serial-v1、MSH、堆和基础内核，系统 Tick 为 1000 Hz。使用以下命令配置工程并生成 `rtconfig.h`：

```sh
scons --menuconfig
scons --pyconfig-silent
scons -j8
scons --dist
```

板级选项包括 UART0 开关、UART 输入时钟（默认 48 MHz）及 CLINT 时基（默认 4 MHz）。频率设置应与 Bootloader 配置一致，这些选项不会改变硬件分频器。`rtconfig.h` 由上述配置工具生成。

将 `dist/project.zip` 解压到独立目录，清除 `RTT_ROOT`，在解压后的 `project/` 目录中运行相同的配置及构建命令。导出包包含 BSP、所需库文件、RT-Thread 源码及构建工具。

## 内存与启动要求

| 区域 | 地址 / 用途 |
|------|-------------|
| DDR3 | `0x40000000..0x47ffffff`，128 MiB |
| RT-Thread | `0x40000000..0x477fffff`，120 MiB |
| loader 保留区 | `0x47800000..0x47ffffff`，顶部 8 MiB |
| BIN 加载地址 / ELF 入口 | `0x40000000` |

堆起点位于静态段和早期栈之后，终点为 `0x47800000`。common port 早期栈按 16 字节对齐，中断栈位于 BSS。链接脚本检查段顺序、栈对齐和堆边界。

外部 ArtInChip 兼容 loader 必须：

1. 初始化 DDR、PLL、总线时钟及 CPU 内存/Cache 属性。
2. 将 UART0 输入时钟配置为 48 MHz，并提供 4 MHz 时基，或使 BSP 频率设置与实际值一致。
3. 将镜像加载到 `0x40000000`；Cache 开启时清理已加载数据并同步指令 Cache。
4. 在 hart 0、M-mode 下进入第一条指令，进入时中断关闭、MMIO 不可缓存，无活动 DMA，也无尚未完成的已 claim PLIC 中断。

BSP 沿用 Bootloader 的 DDR、PLL、UART0 时钟分频和 Cache 配置。RISC-V common port 负责启动及 PLIC claim/complete，板级代码完成 C906、外设门控和定时器访问初始化。

## 加载与控制台使用

根据所用 ArtInChip Bootloader 的要求，将 `rtthread.bin` 打包为 FIT 或烧录镜像，并加载到 `0x40000000`。Bootloader 需包含 DDR 初始化程序，并使用匹配的分区布局。

使用 2 KiB 页 NAND 的 `demo128-nand` 整包时，拼接后的 `bootloader.aic` 应控制在 411,648 字节以内，包含 PBP、头部和资源。这是 SPL 页表的容量限制。仅更新 OS 时，沿用现有 Bootloader 和分区布局。

加载后，以 115200 8N1 连接 UART0，应出现以下输出：

```text
RT-Thread Operating System
D213ECV-DEMO-V4-0
msh >
```

| 命令 | 用途 |
|------|------|
| `help` | 列出 shell 命令 |
| `version` | 查看 RT-Thread 版本 |
| `ps` 或 `list thread` | 查看线程 |
| `list device` | 查看注册设备；默认包含 `uart0` |
| `list timer` | 查看定时器及当前 Tick |
| `free` | 查看堆使用情况 |

启动应用退出后，默认线程列表包含 `tshell`、`uart0rx` 和 `tidle0`。

## 验证状态

2026 年 11 月 14 日 02:39:03 构建的 UART0 镜像已在实机进入 MSH。串口日志确认重复执行 `help`，以及 `list device`、`list timer` 和 `ps` 正常，仅注册 `uart0`。接收线程优先级为 19，高于 shell 的 20。实机验证还确认，完全断电后重新上电可稳定进入 MSH，在 `help`、`ps` 输出过程中重复输入下一条命令均正常。

| 检查项 | 结果 |
|--------|------|
| 默认 UART0 配置及独立 SCons 构建 | GCC 10.2.0 下通过 |
| 无 UART 和 Serial-v2 排除配置 | GCC 10.2.0 下通过 |
| dist 导出及仓库外独立重建 | GCC 10.2.0 下通过 |
| UART0 格式、参数校验、发送超时、接收关闭/重开及 DLAB 保护 | 主机 MMIO 模拟通过，覆盖 21 种有效格式 |
| SPI NAND loader 交接、FIT CRC32、RT-Thread 启动 | 上一 UART0 版本实机通过 |
| UART0 收发、重复执行 MSH `help` 及 `ps` | 本次镜像实机日志确认 |
| MSH `version` 和 `free` | 上一 UART0 版本实机通过 |
| 设备/定时器枚举 | 本次镜像仅注册 `uart0`，已输出接收线程定时器及当前 Tick |
| 完全断电后启动及 `help` / `ps` 输出期间输入命令 | 本次 UART0 镜像实机通过 |
| Tick 精度、抢占及反复唤醒 | 待验证 |
| 堆压力/对齐及抢占、中断下的 FPU/FCSR 保存 | 待验证 |
| 受控外部 PLIC 投递/完成、反复复位和长时间运行 | 待验证 |

## 源码与许可证

BSP 使用 Apache-2.0 许可证。

SoC/寄存器定义、硬件时序及板级 pinmux 来自公开的 [ArtInChip Luban-Lite SDK](https://gitee.com/artinchip/luban-lite)。原厂源码路径如下：

| BSP 内容 | SDK 来源 | 许可证 |
|----------|----------|--------|
| D213 地址、CMU 门控/复位位 | `bsp/artinchip/sys/d21x/include/aic_soc.h`、`aic_clk_id.h` | Apache-2.0 |
| C906 和 PLIC 初始化 | `bsp/artinchip/sys/d21x/system.c` | Apache-2.0 |
| UART 寄存器/编程 | `bsp/artinchip/hal/uart/aic_hal_uart.c` | Apache-2.0 |
| GPIO 引脚配置 | `bsp/artinchip/hal/gpio/aic_hal_gpio.c`、`target/d21x/demo128-nand/pinmux.c` | Apache-2.0 |
| 门控/复位时序 | `bsp/artinchip/hal/cmu/aic_hal_clk.c` | Apache-2.0 |
