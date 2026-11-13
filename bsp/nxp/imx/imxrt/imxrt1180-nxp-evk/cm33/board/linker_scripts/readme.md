# CM33 Memory Layout

[English version](readme_en.md)

本目录提供四种 CM33 内存布局，每种都有 GCC `.ld`、Keil `.scf` 和 IAR `.icf` 文件。
下表地址为 CM33 视角，结束地址包含在区域内；KB/MB 按 1024/1048576 字节计算，容量不代表实际占用。

## 1. 当前内存布局

| 内存 | 起始地址 | 结束地址 | 容量 | 用途 |
| --- | --- | --- | --- | --- |
| Code TCM | `0x0FFE0000` | `0x0FFFFFFF` | 128KB | RAM 类 target 的向量和代码；XIP 类 target 的快速代码 |
| System TCM | `0x20000000` | `0x2001FFFF` | 128KB | 普通数据和主栈，或快速数据 |
| OCRAM1 | `0x20484000` | `0x204FFFFF` | 496KB | 普通布局的 Heap 和 non-cacheable 缓冲区；工业布局留给 CM7 |
| OCRAM2 | `0x20500000` | `0x2053FFFF` | 256KB | 双核共享内存，工业布局另划分独占区域 |
| HyperRAM，非双镜像模式 | `0x04000000` | `0x047FFFFF` | 8MB | HyperRAM target 的普通数据和主栈 |
| HyperRAM，双镜像模式 | `0x04600000` | `0x047FFFFF` | 2MB | 定义 `__dual_image__` 后，CM33 使用末尾 2MB |
| FlexSPI NOR，常规 XIP 窗口 | `0x28000000` | `0x287FFFFF` | 8MB | XIP 类 target 的启动信息、向量、代码及数据初值；GCC HyperRAM 文件有例外，见下文 |

RAM 类向量占 Code TCM 首部 1KB，代码从 `0x0FFE0400` 开始；初始化数据副本也占用 TCM 镜像空间。
XIP 类向量位于 `0x2800B000`，普通代码从 `0x2800B400` 开始，前部空间用于启动信息。
HyperRAM target 的快速数据仍在 System TCM，Heap 仍在 OCRAM1。当前四种布局的主要内容均不放入 SDRAM。

### 普通 OCRAM 布局

适用于 `RAM`、`FLEXSPI_NOR`、`FLEXSPI_NOR_HYPERRAM`。
以下按双核配置（定义 `__multicore__`）且使用 cacheable Heap 说明，共享区需启用 `__use_shmem__`。

| 区域 | 起始地址 | 结束地址 | 容量 |
| --- | --- | --- | --- |
| CM33 Heap 可用窗口 | `0x20484000` | `0x2049FFFF` | 112KB |
| CM33 non-cacheable 缓冲区 | `0x204A0000` | `0x204BFFFF` | 128KB |
| 留给 CM7 的 OCRAM1 | `0x204C0000` | `0x204FFFFF` | 256KB |
| 双核共享 OCRAM2 | `0x20500000` | `0x2053FFFF` | 256KB |

未定义 `__multicore__` 时，CM33 Heap 窗口扩展到 OCRAM1 低地址 240KB，non-cacheable 窗口改为高地址 256KB。

### 工业以太网 OCRAM 布局

适用于 `RAM_INDUSTRY`，以下按 cacheable Heap 说明。

| 区域 | 起始地址 | 结束地址 | 容量 |
| --- | --- | --- | --- |
| OCRAM1，留给 CM7 | `0x20484000` | `0x204FFFFF` | 496KB |
| CM33 Heap | `0x20500000` | `0x2050FFFF` | 64KB |
| CM33 non-cacheable 缓冲区 | `0x20510000` | `0x2051FFFF` | 64KB |
| CM7 独占额外 OCRAM2 | `0x20520000` | `0x20537FFF` | 96KB |
| 双核共享 OCRAM2 | `0x20538000` | `0x2053FFFF` | 32KB |

CM33 使用 256KB TCM 和独占的 128KB OCRAM2，不使用 OCRAM1；双核共享区缩小到 32KB。
CM7 应使用匹配的工业分区，不能继续把整个 OCRAM2 当作共享区。

## 2. 各 Target 的差异

| Target 类型 | 向量/普通代码 | 普通数据/主栈 | OCRAM 布局 | GCC 默认 Heap / 主栈 | Keil、IAR 默认 Heap / 主栈 |
| --- | --- | --- | --- | --- | --- |
| `RAM` | Code TCM | System TCM | 普通 | 1KB / 1KB | 32KB / 4KB |
| `RAM_INDUSTRY` | Code TCM | System TCM | 工业 | 64KB / 4KB | 64KB / 4KB |
| `FLEXSPI_NOR` | Flash XIP | System TCM | 普通 | 32KB / 4KB | 32KB / 4KB |
| `FLEXSPI_NOR_HYPERRAM` | Flash XIP | HyperRAM | 普通 | 32KB / 4KB | 32KB / 4KB |

Heap 窗口容量不等于默认分配大小，主栈也不是各 RT-Thread 线程的独立栈。工程可覆盖堆栈大小或将 Heap 改为 non-cacheable。
CM33 目前没有独立 `HYPERRAM` 或 `FLEXSPI_NOR_INDUSTRY` target。

当前 [GCC FLEXSPI_NOR_HYPERRAM 文件](MIMXRT1189xxxxx_cm33_flexspi_nor_hyperram.ld) 的 Flash 大小声明为 `0x08000000`（128MB），Keil/IAR 则为 `0x00800000`（8MB）。这只是当前文件差异，不表示板上有 128MB Flash；使用 GCC 时需核对实际容量。

## 3. 应用范围

| Target 类型 | 适用场景 |
| --- | --- |
| `RAM` | 内部 TCM 调试、小型控制和实时应用，不依赖外部 RAM |
| `RAM_INDUSTRY` | 工业以太网双核开发，CM33 承担控制或通信管理，OCRAM1 留给 CM7 |
| `FLEXSPI_NOR` | 常规 Flash XIP 应用，代码较大但普通数据可放入内部 System TCM |
| `FLEXSPI_NOR_HYPERRAM` | Flash XIP 且需要较大数据缓冲区的通信、采集或数据处理应用 |

RAM 类镜像需要调试器或启动流程装载；HyperRAM 必须在数据和主栈使用前可访问。
与 CM7 共用 HyperRAM 时，应选择匹配的双镜像分配；共享通信需启用共享区，工业分区需与 CM7 一致。
链接布局只决定存放位置，不代替外设和通信初始化。