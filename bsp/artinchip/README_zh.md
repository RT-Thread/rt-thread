# ArtInChip 板级支持包

[English](README.md) | [中文](README_zh.md)

本目录提供 ArtInChip SoC 的 RT-Thread 板级支持。

| 开发板 | SoC / CPU | 支持功能 |
|--------|-----------|----------|
| [D213ECV-DEMO-V4-0](d213ecv-demo-v4-0/README_zh.md) | D213ECV / T-Head C906，RV64GC | M-mode 基础内核、UART0 控制台 |

## 源码结构

```text
artinchip/
├── d213ecv-demo-v4-0/          板级配置与构建入口
│   ├── applications/          启动应用
│   └── board/                 板级接线与初始化编排
└── libraries/
    ├── include/               UART 寄存器定义
    └── soc/d21x/
        ├── include/           SoC 地址与 MMIO 访问接口
        ├── drivers/           D213 UART0 串口适配
        └── port/              CPU、时钟、PLIC 和定时器平台接口
```

板级目录用于配置开发板接线和内存布局，`libraries/soc/d21x` 存放 D21x 共用的寄存器定义、驱动和平台初始化代码。

BSP 使用 RT-Thread RISC-V common port 完成启动、上下文切换、FPU 状态保存、中断处理和系统定时，提供 UART0 及所需的时钟、复位和引脚配置。Bootloader 在启动 RT-Thread 前完成 DDR、PLL 和内存/Cache 属性初始化。

独立构建、配置、loader 要求、验证状态和源码归属见 [开发板说明](d213ecv-demo-v4-0/README_zh.md)。
