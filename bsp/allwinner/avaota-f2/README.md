# Avaota F2 / V861 — C907

Allwinner V861（Avaota F2）C907 最小 BSP：UART 控制台 + msh。

## 硬件要点

| 项 | 值 |
|----|----|
| 装载 | `0x40000000`（2MB DRAM 窗口，见 `link.lds`） |
| UART0 | `0x02500000`，115200 8N1；引脚 PH9/PH10；PLIC source 2（见 `board/board.dts`） |
| PLIC | `0x30000000`（见 `board/plic.h` / `board.dts`） |
| 核 | C907，RV32 工具链配置（见 `rtconfig.py`） |

## 已在板子上验证

- RT-Thread banner + FinSH/`msh`
- DT 解析 UART（`uart-from-fdt`）
- 双核 SMP（可选配置；默认 `RT_CPUS_NR=2`）
- 异构（配合 `avaota-f2-e907`）：`[C907] HETERO-OK`（经 ping 槽）、`[C907] OPENAMP-EPT-OK echo=3`

> 本提交把 uart0 改成 `INT_RX`（PLIC 中断收数）并改用 `board.dts` + `dtc` 生成
> 设备树；PLIC 基址更新为 `0x30000000`。**部分项尚未上板复测**，以 PR 实测为准。

共享驱动：`bsp/allwinner/libraries/drivers/avaota/`（UART/FDT），两 BSP 的 `driver/SConscript` 引用该路径。

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
- 异构模式下若 E907 已上线（`AMP_SLOT_E907` magic），C907 侧 UART 跳过 gate/reset 全复位，避免打断对端控制台。

## 烧录提示

板级常用 FEL 冷链（`init_dram` → payload @`0x40000000` → `c907_boot`）。具体工具与镜像以你的 SyterKit / xfel 流程为准。