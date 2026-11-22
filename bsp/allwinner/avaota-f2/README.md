# Avaota F2 / V861 — C907

Allwinner V861（Avaota F2）C907 最小 BSP：UART 控制台 + msh。

## 硬件要点

| 项 | 值 |
|----|----|
| 装载 | `0x40000000`（2MB DRAM 窗口，见 `link.lds`） |
| UART0 | `0x02500000`，115200 8N1；引脚 PH9/PH10；PLIC source 2（见 `board/board.dts`） |
| 核 | C907，RV32 工具链配置（见 `rtconfig.py`） |

## 已在板子上验证

- RT-Thread banner + FinSH/`msh`
- DT 解析 UART（`uart-from-fdt`）
- 双核 SMP（可选配置；默认 `RT_CPUS_NR=2`）

> 本提交把 uart0 改成 `INT_RX`（PLIC 中断收数）并改用 `board.dts` + `dtc` 生成
> 设备树；这两项**尚未上板验证**，仅完成干净构建与静态对照。

MMC、异构 AMP、OpenAMP **不在本阶段声明为已支持**。源码中的 `drv_mmc.c` / `amp_mbox.h` 为后续工作保留，默认 `main` 不依赖它们。

## 配置

`rtconfig.h` 由 `Kconfig` + `.config` 生成，不要手改：

```sh
# 图形化配置（Env / menuconfig）
scons --pyconfig
# 或者按已提交的 .config 静默重生成 rtconfig.h
scons --pyconfig-silent
```

## 编译

`board/builtin_fdt.S` 用 `.incbin` 内嵌 `board/board.dtb`。DTB 由 `board/board.dts`
经 `dtc` 在构建时生成（`board/SConscript` 已接入），**不再需要** `gen_board_dtb.py`
或 Python `fdt` 模块。请先装 device-tree-compiler：

```sh
# Debian/Ubuntu
sudo apt-get install device-tree-compiler
# macOS
brew install dtc
```

推荐 [RT-Thread Env 2.x](https://github.com/RT-Thread/rt-thread/blob/master/documentation/env/env.md)：用 `sdk` 安装/卸载工具链；本机已有工具链时，简单配置后 Env 可自动探测。

```text
cd bsp/allwinner/avaota-f2
scons -j8
```

产物：`rtthread.bin`（已在 `.gitignore`）；`board/board.dtb` 为构建产物，同样不入库。

## 串口

- FinSH 以 `RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX` 打开 `uart0`；
- 收到数据时 UART 触发中断，`v861_uart0_isr()` 调 `rt_hw_serial_isr(..., RT_SERIAL_EVENT_RX_IND)`，
  由串口框架把 FIFO 读空；
- `uart_getc()` 在 FIFO 空时返回 `-1`（不阻塞）。

## 烧录提示

板级常用 FEL 冷链（`init_dram` → payload @`0x40000000` → `c907_boot`）。具体工具与镜像以你的 SyterKit / xfel 流程为准。
