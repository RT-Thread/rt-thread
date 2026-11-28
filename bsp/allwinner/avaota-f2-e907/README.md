# Avaota F2 / V861 — E907（异构主核）

E907 上跑 RT-Thread，按 SyterKit 风格拉起 C907，用 **DRAM 槽**做最小跨核 + AMP mailbox 风格往返（**非** OpenAMP）。

## 已在板子上证实

| 项 | 串口关键字 |
|----|------------|
| E907 RTT | banner + `avaota-f2 v861 e907` + `msh >` |
| 异构 | `[E907] HETERO-OK c907=0xc907a11c reply=0xa11c0002` |
| AMP mailbox | `[E907] RPMSG-OK tx=3 rx=3`（关键字保留，实现为 DRAM 槽） |

## 装载

| 步 | 地址 / 动作 |
|----|-------------|
| 1 | `init_dram_efex.bin` @`0x100000` write + exec |
| 2 | `../avaota-f2/rtthread.bin` @`0x40000000` |
| 3 | 本目录 `rtthread.bin` @`0x42000000` |
| 4 | `xfel exec 0x42000000` |
| 串口 | 115200 8N1，DTR/RTS 关 |

邮箱（DRAM）：基址 `0x41000000`（见 `board/amp_mbox.h`）。

## 编译

`board/builtin_fdt.S` 用 `.incbin` 内嵌 `board/board.dtb`。该 DTB 由 `board/board.dts`
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
cd bsp/allwinner/avaota-f2-e907
scons -j8
```

C907 侧在 `../avaota-f2` 同样编译（DTB 同样由 `dtc` 从 `board.dts` 生成，不入库）。
`rtconfig.h` 由 `Kconfig` + `.config` 生成（`scons --pyconfig` / `--pyconfig-silent`），不要手改。

串口：FinSH 以 `RDWR | INT_RX` 打开 `uart0`，`v861_uart0_isr()` 上报
`RT_SERIAL_EVENT_RX_IND`，`uart_getc()` 空时返回 `-1`（C907 侧已上板验证 INT_RX）。
C907 发现 E907 已在跑时跳过 UART 全量硬件复位，避免打掉共享串口。

公共驱动（`drv_uart` / `drv_fdt`）在 `bsp/allwinner/libraries/drivers/avaota/`；
板级 AMP 接口为 `drv_amp_mailbox`（不再使用 `rpmsg_lite` 命名）。

## 未宣称

硬件 MSGBOX 门铃、完整 OpenAMP、MMC/文件系统。合入以实际 PR 为准。
