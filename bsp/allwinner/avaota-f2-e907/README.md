# Avaota F2 / V861 — E907（异构主核）

E907 上跑 RT-Thread，按 SyterKit 风格拉起 C907，用 **DRAM 槽**做最小跨核 + AMP endpoint 往返（**非** libmetal OpenAMP）。

## 已在板子上证实

| 项 | 串口关键字 |
|----|------------|
| E907 RTT | banner + `avaota-f2 v861 e907` + `msh >` |
| 异构 | `[E907] HETERO-OK c907=0xc907a11c reply=0xa11c0002` |
| AMP endpoint | `[E907] OPENAMP-EPT-OK name=avaota-ept tx=3 rx=3` |

UART0 在 `rt_hw_board_init()` 注册一次；异构时 **E907 占用控制台 RX**，不要在 `main` 里再次 `rt_hw_uart_init()`。

共享驱动：`bsp/allwinner/libraries/drivers/avaota/`（UART/FDT）。

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
`RT_SERIAL_EVENT_RX_IND`，`uart_getc()` 空时返回 `-1`。

> 本提交把 uart0 改成 `INT_RX` 并改用 `board.dts` + `dtc`，这两项**尚未上板验证**，
> 只完成干净构建与静态对照。

## 未宣称

完整 virtio OpenAMP、MMC/文件系统。合入以实际 PR 为准。