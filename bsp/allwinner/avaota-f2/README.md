# Avaota F2 / V861 — C907

Allwinner V861（Avaota F2）C907 最小 BSP：UART 控制台 + msh。

## 硬件要点

| 项 | 值 |
|----|----|
| 装载 | `0x40000000`（2MB DRAM 窗口，见 `link.lds`） |
| UART0 | `0x02500000`，115200 8N1；引脚 PH9/PH10（DT：`board/board.dtb`，构建时生成） |
| 核 | C907，RV32 工具链配置（见 `rtconfig.py`） |

## 已在板子上验证

- RT-Thread banner + FinSH/`msh`
- DT 解析 UART（`uart-from-fdt`）
- 双核 SMP（可选配置；默认 `RT_CPUS_NR=2`）

MMC、异构 AMP、OpenAMP **不在本阶段声明为已支持**。源码中的 `drv_mmc.c` / `amp_mbox.h` 为后续工作保留，默认 `main` 不依赖它们。

## 编译

`board/builtin_fdt.S` 用 `.incbin` 内嵌 `board/board.dtb`。该 DTB 由 `board/gen_board_dtb.py` 在构建时自动生成（SCons 已接入，无需手工准备）。首次构建需要 `python3` 与 `fdt` 模块：

```sh
pip3 install fdt
```

推荐 [RT-Thread Env 2.x](https://github.com/RT-Thread/rt-thread/blob/master/documentation/env/env.md)：用 `sdk` 安装/卸载工具链；本机已有工具链时，简单配置后 Env 可自动探测。

```text
cd bsp/allwinner/avaota-f2
scons -j8
```

产物：`rtthread.bin`（已在 `.gitignore`）；`board/board.dtb` 为构建产物，同样不入库。

## 烧录提示

板级常用 FEL 冷链（`init_dram` → payload @`0x40000000` → `c907_boot`）。具体工具与镜像以你的 SyterKit / xfel 流程为准。
