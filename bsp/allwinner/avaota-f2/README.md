# Avaota F2 / V861 — C907

Allwinner V861（Avaota F2）C907 最小 BSP：UART 控制台 + msh。

## 硬件要点

| 项 | 值 |
|----|----|
| 装载 | `0x40000000`（2MB DRAM 窗口，见 `link.lds`） |
| UART0 | `0x02500000`，115200 8N1；引脚 PH9/PH10（DT：`board/board.dtb`） |
| 核 | C907，RV32 工具链配置（见 `rtconfig.py`） |

## 已在板子上验证

- RT-Thread banner + FinSH/`msh`
- DT 解析 UART（`uart-from-fdt`）
- 双核 SMP（可选配置；默认 `RT_CPUS_NR=2`）

默认 `applications/main.c` 可作为异构从核应答 DRAM ping（配合 `avaota-f2-e907`）。单独启动、无 ping 时超时后进入 `msh`。

MMC、OpenAMP、硬件 MSGBOX **不在本 BSP 宣称范围内**。

## 编译

```text
set RTT_EXEC_PATH=<riscv-none-embed 或等价 gcc 的 bin>
cd bsp/allwinner/avaota-f2
scons -j8
```

产物：`rtthread.bin`（已在 `.gitignore`）。

## 烧录提示

板级常用 FEL 冷链（`init_dram` → payload @`0x40000000` → `c907_boot`）。具体工具与镜像以你的 SyterKit / xfel 流程为准。
