# CM33 Memory Layout

[Chinese version](readme.md)

This directory provides four CM33 memory layouts, each with GCC `.ld`, Keil `.scf`, and IAR `.icf` files.
Addresses are from the CM33 perspective and table end addresses are inclusive. KB/MB mean 1024/1048576 bytes; capacities are not actual usage.

## 1. Current Memory Layout

| Memory | Start | End | Capacity | Purpose |
| --- | --- | --- | --- | --- |
| Code TCM | `0x0FFE0000` | `0x0FFFFFFF` | 128KB | Vectors and code for RAM targets; quick-access code for XIP targets |
| System TCM | `0x20000000` | `0x2001FFFF` | 128KB | Ordinary data and main stack, or quick-access data |
| OCRAM1 | `0x20484000` | `0x204FFFFF` | 496KB | Heap and non-cacheable buffers in standard layouts; reserved for CM7 in the industry layout |
| OCRAM2 | `0x20500000` | `0x2053FFFF` | 256KB | Multicore shared memory; the industry layout also reserves exclusive areas |
| HyperRAM, without dual-image mode | `0x04000000` | `0x047FFFFF` | 8MB | Ordinary data and main stack for the HyperRAM target |
| HyperRAM, with dual-image mode | `0x04600000` | `0x047FFFFF` | 2MB | CM33 uses the final 2MB when `__dual_image__` is defined |
| FlexSPI NOR, standard XIP window | `0x28000000` | `0x287FFFFF` | 8MB | Boot information, vectors, code, and data initial values for XIP targets; the GCC HyperRAM file has an exception noted below |

RAM targets reserve the first 1KB of Code TCM for vectors, with code starting at `0x0FFE0400`. Initialization copies also consume TCM image space.
XIP vectors are at `0x2800B000`, with ordinary code starting at `0x2800B400`; earlier Flash space is used for boot information.
The HyperRAM target keeps quick-access data in System TCM and the heap in OCRAM1. None of these four layouts places its main contents in SDRAM.

### Standard OCRAM Layout

Applies to `RAM`, `FLEXSPI_NOR`, and `FLEXSPI_NOR_HYPERRAM`.
The table assumes multicore configuration (`__multicore__` defined) and a cacheable heap. Shared memory requires `__use_shmem__` to be enabled.

| Region | Start | End | Capacity |
| --- | --- | --- | --- |
| CM33 available heap window | `0x20484000` | `0x2049FFFF` | 112KB |
| CM33 non-cacheable buffers | `0x204A0000` | `0x204BFFFF` | 128KB |
| OCRAM1 reserved for CM7 | `0x204C0000` | `0x204FFFFF` | 256KB |
| Multicore shared OCRAM2 | `0x20500000` | `0x2053FFFF` | 256KB |

Without `__multicore__`, the CM33 heap window expands to the lower 240KB of OCRAM1, and the non-cacheable window becomes the upper 256KB.

### Industrial Ethernet OCRAM Layout

Applies to `RAM_INDUSTRY`. The table assumes a cacheable heap.

| Region | Start | End | Capacity |
| --- | --- | --- | --- |
| OCRAM1 reserved for CM7 | `0x20484000` | `0x204FFFFF` | 496KB |
| CM33 heap | `0x20500000` | `0x2050FFFF` | 64KB |
| CM33 non-cacheable buffers | `0x20510000` | `0x2051FFFF` | 64KB |
| CM7-exclusive additional OCRAM2 | `0x20520000` | `0x20537FFF` | 96KB |
| Multicore shared OCRAM2 | `0x20538000` | `0x2053FFFF` | 32KB |

CM33 uses 256KB of TCM and 128KB of exclusive OCRAM2, without using OCRAM1. The shared window is reduced to 32KB.
CM7 must use a matching industry partition rather than treating all OCRAM2 as shared memory.

## 2. Target Differences

| Target type | Vectors/ordinary code | Ordinary data/main stack | OCRAM layout | GCC default heap / main stack | Keil, IAR default heap / main stack |
| --- | --- | --- | --- | --- | --- |
| `RAM` | Code TCM | System TCM | Standard | 1KB / 1KB | 32KB / 4KB |
| `RAM_INDUSTRY` | Code TCM | System TCM | Industry | 64KB / 4KB | 64KB / 4KB |
| `FLEXSPI_NOR` | Flash XIP | System TCM | Standard | 32KB / 4KB | 32KB / 4KB |
| `FLEXSPI_NOR_HYPERRAM` | Flash XIP | HyperRAM | Standard | 32KB / 4KB | 32KB / 4KB |

Heap window capacity is not the default allocated heap size, and the main stack is not each RT-Thread thread's individual stack. Projects can override sizes or select a non-cacheable heap.
CM33 currently has no standalone `HYPERRAM` or `FLEXSPI_NOR_INDUSTRY` target.

The current [GCC FLEXSPI_NOR_HYPERRAM file](MIMXRT1189xxxxx_cm33_flexspi_nor_hyperram.ld) declares a Flash size of `0x08000000` (128MB), whereas Keil/IAR declare `0x00800000` (8MB). This is a file difference, not evidence of 128MB of physical Flash. Check the actual capacity when using GCC.

## 3. Application Scope

| Target type | Suitable applications |
| --- | --- |
| `RAM` | Internal-TCM debugging and small control or real-time applications without external RAM |
| `RAM_INDUSTRY` | Industrial Ethernet multicore development with CM33 handling control or communication management and OCRAM1 reserved for CM7 |
| `FLEXSPI_NOR` | Conventional Flash XIP applications with larger code and ordinary data that fits in internal System TCM |
| `FLEXSPI_NOR_HYPERRAM` | Flash XIP communications, acquisition, or data-processing applications requiring larger data buffers |

RAM images require loading by a debugger or boot flow. HyperRAM must be accessible before ordinary data and the main stack are used.
When sharing HyperRAM with CM7, use matching dual-image allocations. Shared communication requires shared memory to be enabled, and industry partitions must match CM7.
Memory layouts determine placement, not peripheral or communication initialization.