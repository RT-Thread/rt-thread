# Avaota F2 / V861 — E907（异构主核）

E907 上跑 RT-Thread，按 SyterKit 风格拉起 C907，用 **DRAM 槽**做最小跨核 + RPMsg 风格往返（**非** OpenAMP）。

## 已在板子上证实

| 项 | 串口关键字 |
|----|------------|
| E907 RTT | banner + `avaota-f2 v861 e907` + `msh >` |
| 异构 | `[E907] HETERO-OK c907=0xc907a11c reply=0xa11c0002` |
| RPMsg-lite | `[E907] RPMSG-OK tx=3 rx=3` |

详见 `ACCEPTANCE.md`。

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

```text
set RTT_EXEC_PATH=<riscv-none-embed-gcc 所在 bin>
cd bsp/allwinner/avaota-f2-e907
scons -j8
```

C907 侧在 `../avaota-f2` 同样编译。

## 未宣称

硬件 MSGBOX 门铃、完整 OpenAMP、MMC/文件系统。合入以实际 PR 为准。
