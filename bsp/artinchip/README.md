# ArtInChip BSPs

[English](README.md) | [中文](README_zh.md)

This directory provides RT-Thread board support for ArtInChip SoCs.

| Board | SoC / CPU | Support |
|-------|-----------|-----------------|
| [D213ECV-DEMO-V4-0](d213ecv-demo-v4-0/README.md) | D213ECV / T-Head C906, RV64GC | M-mode base kernel, UART0 console |

## Source organization

```text
artinchip/
├── d213ecv-demo-v4-0/          Board configuration and build entry
│   ├── applications/          Startup application
│   └── board/                 Board wiring and initialization sequence
└── libraries/
    ├── include/               UART register definitions
    └── soc/d21x/
        ├── include/           SoC addresses and MMIO accessors
        ├── drivers/           D213 UART0 serial adapter
        └── port/              CPU, clock, PLIC and timer platform hooks
```

Board wiring and memory layout are configured in the board directory. Shared D21x register definitions, drivers and platform initialization are in `libraries/soc/d21x`.

The BSP uses the RT-Thread RISC-V common port for startup, context switching, FPU state, interrupts and system ticks. It provides UART0 with the required clock, reset and pin configuration. The bootloader initializes DDR, PLLs and memory/cache attributes before starting RT-Thread.

See the [board README](d213ecv-demo-v4-0/README.md) for independent builds, configuration, loader requirements, validation status and source attribution.
