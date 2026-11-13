# CM7 Memory Layout

[English version](readme_en.md)

本目录提供六种 CM7 内存布局，每种都有 GCC `.ld`、Keil `.scf` 和 IAR `.icf` 文件。
下表地址为 CM7 视角，结束地址包含在区域内；KB/MB 按 1024/1048576 字节计算，容量不代表实际占用。

## 1. 当前内存布局

| 内存 | 起始地址 | 结束地址 | 容量 | 用途 |
| --- | --- | --- | --- | --- |
| ITCM | `0x00000000` | `0x0003FFFF` | 256KB | RAM 类 target 的向量和代码；XIP 类 target 的快速代码 |
| DTCM | `0x20000000` | `0x2003FFFF` | 256KB | 普通数据和主栈，或快速数据 |
| OCRAM1 | `0x20484000` | `0x204FFFFF` | 496KB | Heap 和 non-cacheable 缓冲区；避开 TRDC 禁止访问的前 16KB |
| OCRAM2 | `0x20500000` | `0x2053FFFF` | 256KB | 双核共享内存，工业布局另划分独占区域 |
| HyperRAM | `0x04000000` | `0x045FFFFF` | 6MB | HyperRAM 类 target 的普通数据和主栈；另预留 2MB 给 CM33 |
| FlexSPI NOR | `0x28800000` | `0x28FFFFFF` | 8MB | XIP 类 target 的向量、代码及数据初值 |

RAM 类向量占 ITCM 首部 1KB，代码从 `0x00000400` 开始；其初始化数据副本也占用 ITCM 镜像空间。
XIP 类向量占 Flash 首部 1KB，普通代码从 `0x28800400` 开始。
HyperRAM 类的快速数据仍在 DTCM，Heap 仍在 OCRAM1。当前六种布局的主要内容均不放入 SDRAM。

### 普通 OCRAM 布局

适用于 `RAM`、`HYPERRAM`、`FLEXSPI_NOR`、`FLEXSPI_NOR_HYPERRAM`。
以下按双核配置（定义 `__multicore__`）且使用 cacheable Heap 说明，共享区需启用 `__use_shmem__`。

| 区域 | 起始地址 | 结束地址 | 容量 |
| --- | --- | --- | --- |
| OCRAM1 低地址部分，未分配给本 CM7 布局 | `0x20484000` | `0x204BFFFF` | 240KB |
| CM7 Heap 可用窗口 | `0x204C0000` | `0x204DFFFF` | 128KB |
| CM7 non-cacheable 缓冲区 | `0x204E0000` | `0x204FFFFF` | 128KB |
| 双核共享 OCRAM2 | `0x20500000` | `0x2053FFFF` | 256KB |

未定义 `__multicore__` 时，Heap 窗口改为 OCRAM1 低地址 240KB，non-cacheable 窗口改为高地址 256KB。

### 工业以太网 OCRAM 布局

适用于 `RAM_INDUSTRY`、`FLEXSPI_NOR_INDUSTRY`，以下按 cacheable Heap 说明。

| 区域 | 起始地址 | 结束地址 | 容量 |
| --- | --- | --- | --- |
| CM7 Heap 可用窗口 | `0x20484000` | `0x204BFFFF` | 240KB |
| CM7 non-cacheable 缓冲区 | `0x204C0000` | `0x204FFFFF` | 256KB |
| CM33 独占 OCRAM2 | `0x20500000` | `0x2051FFFF` | 128KB |
| CM7 独占额外 OCRAM2 | `0x20520000` | `0x20537FFF` | 96KB |
| 双核共享 OCRAM2 | `0x20538000` | `0x2053FFFF` | 32KB |

工业布局将更多 OCRAM1 留给 CM7，并把 OCRAM2 分成 CM33 128KB、CM7 96KB、共享 32KB。
双核必须使用匹配的分区；额外 96KB 不会自动加入系统 Heap。

## 2. 各 Target 的差异

| Target 类型 | 向量/普通代码 | 普通数据/主栈 | OCRAM 布局 | 默认 Heap | 默认主栈 |
| --- | --- | --- | --- | --- | --- |
| `RAM` | ITCM | DTCM | 普通 | 32KB | 4KB |
| `RAM_INDUSTRY` | ITCM | DTCM | 工业 | 64KB | 4KB |
| `HYPERRAM` | ITCM | HyperRAM | 普通 | 32KB | 4KB |
| `FLEXSPI_NOR` | Flash XIP | DTCM | 普通 | 32KB | 4KB |
| `FLEXSPI_NOR_HYPERRAM` | Flash XIP | HyperRAM | 普通 | 32KB | 4KB |
| `FLEXSPI_NOR_INDUSTRY` | Flash XIP | DTCM | 工业 | 64KB | 4KB |

GCC、Keil、IAR 的默认 Heap/主栈容量已一致，但具体 Heap 放置地址可能不同。
Heap 窗口容量不等于默认分配大小，主栈也不是各 RT-Thread 线程的独立栈。
以上为默认值；工程可覆盖堆栈大小或将 Heap 改为 non-cacheable。

## 3. 应用范围

| Target 类型 | 适用场景 |
| --- | --- |
| `RAM` | 内部 RAM 调试、小型实时应用，不依赖外部 RAM |
| `RAM_INDUSTRY` | 内部 RAM 运行的工业以太网/EtherCAT 双核开发，需要更大的内部缓冲区 |
| `HYPERRAM` | 代码在 ITCM 运行，数据量较大的采集、图像处理或大缓冲区应用 |
| `FLEXSPI_NOR` | 常规 Flash XIP 应用，代码较大但普通数据可放入内部 DTCM |
| `FLEXSPI_NOR_HYPERRAM` | 同时需要较大代码空间和数据空间的图形、通信或数据处理应用 |
| `FLEXSPI_NOR_INDUSTRY` | Flash XIP 的工业以太网/EtherCAT 双核应用，需要 CM7 独占 OCRAM2 和更多 non-cacheable 缓冲区 |

RAM 类镜像需要调试器或启动流程装载；HyperRAM 必须在数据和主栈使用前可访问。
共享通信需启用共享区，工业双核分区需与 CM33 一致。链接布局只决定存放位置，不代替外设和通信初始化。