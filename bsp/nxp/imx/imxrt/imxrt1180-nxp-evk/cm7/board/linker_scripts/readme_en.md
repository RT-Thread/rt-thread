# CM7 Memory Layout

[Chinese version](readme.md)

This directory provides six CM7 memory layouts, each with GCC `.ld`, Keil `.scf`, and IAR `.icf` files.
Addresses are from the CM7 perspective and table end addresses are inclusive. KB/MB mean 1024/1048576 bytes; capacities are not actual usage.

## 1. Current Memory Layout

| Memory | Start | End | Capacity | Purpose |
| --- | --- | --- | --- | --- |
| ITCM | `0x00000000` | `0x0003FFFF` | 256KB | Vectors and code for RAM targets; quick-access code for XIP targets |
| DTCM | `0x20000000` | `0x2003FFFF` | 256KB | Ordinary data and main stack, or quick-access data |
| OCRAM1 | `0x20484000` | `0x204FFFFF` | 496KB | Heap and non-cacheable buffers; excludes the first 16KB blocked by TRDC |
| OCRAM2 | `0x20500000` | `0x2053FFFF` | 256KB | Multicore shared memory; industry layouts also reserve exclusive areas |
| HyperRAM | `0x04000000` | `0x045FFFFF` | 6MB | Ordinary data and main stack for HyperRAM targets; another 2MB is reserved for CM33 |
| FlexSPI NOR | `0x28800000` | `0x28FFFFFF` | 8MB | Vectors, code, and data initial values for XIP targets |

RAM targets reserve the first 1KB of ITCM for vectors, with code starting at `0x00000400`. Initialization copies also consume ITCM image space.
XIP targets reserve the first 1KB of Flash for vectors, with ordinary code starting at `0x28800400`.
HyperRAM targets keep quick-access data in DTCM and the heap in OCRAM1. None of these six layouts places its main contents in SDRAM.

### Standard OCRAM Layout

Applies to `RAM`, `HYPERRAM`, `FLEXSPI_NOR`, and `FLEXSPI_NOR_HYPERRAM`.
The table assumes multicore configuration (`__multicore__` defined) and a cacheable heap. Shared memory requires `__use_shmem__` to be enabled.

| Region | Start | End | Capacity |
| --- | --- | --- | --- |
| Lower OCRAM1, not assigned to this CM7 layout | `0x20484000` | `0x204BFFFF` | 240KB |
| CM7 available heap window | `0x204C0000` | `0x204DFFFF` | 128KB |
| CM7 non-cacheable buffers | `0x204E0000` | `0x204FFFFF` | 128KB |
| Multicore shared OCRAM2 | `0x20500000` | `0x2053FFFF` | 256KB |

Without `__multicore__`, the heap window moves to the lower 240KB of OCRAM1, and the non-cacheable window becomes the upper 256KB.

### Industrial Ethernet OCRAM Layout

Applies to `RAM_INDUSTRY` and `FLEXSPI_NOR_INDUSTRY`. The table assumes a cacheable heap.

| Region | Start | End | Capacity |
| --- | --- | --- | --- |
| CM7 available heap window | `0x20484000` | `0x204BFFFF` | 240KB |
| CM7 non-cacheable buffers | `0x204C0000` | `0x204FFFFF` | 256KB |
| CM33-exclusive OCRAM2 | `0x20500000` | `0x2051FFFF` | 128KB |
| CM7-exclusive additional OCRAM2 | `0x20520000` | `0x20537FFF` | 96KB |
| Multicore shared OCRAM2 | `0x20538000` | `0x2053FFFF` | 32KB |

Industry layouts assign more OCRAM1 to CM7 and split OCRAM2 into 128KB for CM33, 96KB for CM7, and 32KB shared.
Both cores must use matching partitions. The additional 96KB is not automatically added to the system heap.

## 2. Target Differences

| Target type | Vectors/ordinary code | Ordinary data/main stack | OCRAM layout | Default heap | Default main stack |
| --- | --- | --- | --- | --- | --- |
| `RAM` | ITCM | DTCM | Standard | 32KB | 4KB |
| `RAM_INDUSTRY` | ITCM | DTCM | Industry | 64KB | 4KB |
| `HYPERRAM` | ITCM | HyperRAM | Standard | 32KB | 4KB |
| `FLEXSPI_NOR` | Flash XIP | DTCM | Standard | 32KB | 4KB |
| `FLEXSPI_NOR_HYPERRAM` | Flash XIP | HyperRAM | Standard | 32KB | 4KB |
| `FLEXSPI_NOR_INDUSTRY` | Flash XIP | DTCM | Industry | 64KB | 4KB |

GCC, Keil, and IAR now use the same default heap/main-stack capacities, although actual heap placement can differ.
Heap window capacity is not the default allocated heap size, and the main stack is not each RT-Thread thread's individual stack.
These are defaults; projects can override sizes or select a non-cacheable heap.

## 3. Application Scope

| Target type | Suitable applications |
| --- | --- |
| `RAM` | Internal-RAM debugging and small real-time applications without external RAM |
| `RAM_INDUSTRY` | Internal-RAM industrial Ethernet/EtherCAT multicore development requiring larger internal buffers |
| `HYPERRAM` | ITCM code execution with data-intensive acquisition, image processing, or large buffers |
| `FLEXSPI_NOR` | Conventional Flash XIP applications with larger code and ordinary data that fits in internal DTCM |
| `FLEXSPI_NOR_HYPERRAM` | Graphics, communications, or data-processing applications needing both larger code and data spaces |
| `FLEXSPI_NOR_INDUSTRY` | Flash XIP industrial Ethernet/EtherCAT multicore applications requiring CM7-exclusive OCRAM2 and more non-cacheable buffers |

RAM images require loading by a debugger or boot flow. HyperRAM must be accessible before ordinary data and the main stack are used.
Shared communication requires shared memory to be enabled, and industry partitions must match CM33. Memory layouts determine placement, not peripheral or communication initialization.