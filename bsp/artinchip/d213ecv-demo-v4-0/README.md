# D213ECV-DEMO-V4-0

[English](README.md) | [中文](README_zh.md)

## Overview

This BSP supports the ArtInChip D213ECV-DEMO-V4-0 development board with RT-Thread running in M-mode on a single T-Head C906 core.

| Item | Description |
|------|-------------|
| SoC | ArtInChip D213ECV |
| CPU | T-Head C906, RV64GC |
| Memory | 128 MiB DDR3 at `0x40000000` |
| Console | UART0, PA.0 (TX) / PA.1 (RX), 115200 baud, 8N1, no flow control |

See the [official board documentation](https://aicdoc.artinchip.com/topics/product/d213ecV4.html) for hardware details.

## Supported features

| Feature | Description |
|---------|-------------|
| Kernel port | RT-Thread RISC-V common port, including double-precision FPU context switching |
| System tick | CLINT timer, 1000 Hz tick by default |
| Interrupt controller | PLIC |
| UART0 | Serial-v1, polling TX and thread-based polling RX |
| FinSH/MSH | Enabled by default |
| Heap and device framework | Enabled by default |

UART0 is intended for an interactive console. Sustained input or long scheduling delays may cause data loss. UART hardware interrupts, DMA and flow control are not supported. The BSP provides the clock, reset and pin configuration required by UART0; DDR and PLL initialization are handled by the bootloader.

## Build and configuration

Install Python 3, SCons, kconfiglib and a GNU bare-metal RISC-V toolchain supporting RV64GC and the `lp64d` ABI. GCC 10.2.0 is recommended.

From the repository root:

```sh
python -m pip install scons kconfiglib
cd bsp/artinchip/d213ecv-demo-v4-0
export RTT_EXEC_PATH=/path/to/riscv-toolchain/bin
scons --pyconfig-silent
scons -j8
```

On PowerShell, use `$env:RTT_EXEC_PATH = 'C:/path/to/riscv-toolchain/bin'` to set the toolchain path. The default compiler prefix is `riscv64-unknown-elf-`; set `RTT_CC_PREFIX` if your toolchain uses a different prefix. The compiler can also be located through PATH.

The build produces `rtthread.elf`, `rtthread.bin` and `rtthread.map`.

To change the configuration, run:

```sh
scons --menuconfig
scons --pyconfig-silent
scons -j8
```

Generate `rtconfig.h` with the configuration tools rather than editing it directly.

| Board option | Default | Description |
|--------------|---------|-------------|
| `BSP_USING_UART0` | Enabled | UART0 console; requires Serial-v1 |
| `BSP_UART_CLK_FREQ` | 48000000 | UART0 input clock in Hz |
| `BSP_CLINT_FREQ` | 4000000 | CLINT timebase in Hz |

The clock settings must match the bootloader configuration; they do not change hardware clock dividers. Serial-v2 is not supported by the UART0 driver.

UTest is disabled by default. To use it, enable `RT_USING_UTESTCASES` and select the required test cases in menuconfig, then regenerate the configuration and rebuild.

To export a standalone project, run `scons --dist`. Extract `dist/project.zip`, unset `RTT_ROOT` if it is set, and run the same configuration and build commands in the extracted `project/` directory.

## Download and run

This BSP requires an external ArtInChip-compatible bootloader. Package `rtthread.bin` in the FIT or firmware format expected by that bootloader, using a matching partition layout.

| Region | Address range |
|--------|---------------|
| RT-Thread, including heap | `0x40000000`–`0x477fffff` (120 MiB) |
| Bootloader reservation | `0x47800000`–`0x47ffffff` (8 MiB) |
| Binary load address and ELF entry | `0x40000000` |

Before entering RT-Thread, the bootloader must:

1. Initialize DDR, PLLs, bus clocks and CPU memory/cache attributes, with MMIO mapped as non-cacheable.
2. Provide the UART0 input clock and CLINT timebase specified in the BSP configuration.
3. Load the image at `0x40000000`, clean the loaded data from the data cache and synchronize the instruction cache if caches are enabled.
4. Enter the image on hart 0 in M-mode with interrupts disabled, no active DMA and no outstanding claimed PLIC interrupts.

Connect a serial terminal to UART0 using 115200 baud, 8 data bits, no parity, 1 stop bit and no flow control. After boot, the console displays:

```text
RT-Thread Operating System
D213ECV-DEMO-V4-0
msh >
```

Use `help` to list shell commands, `ps` to view threads, `free` to view heap usage, and `list device` to view registered devices. The default configuration registers `uart0`.

## UART usage

UART0 is enabled by default. To change its format, use `RT_DEVICE_CTRL_CONFIG` with `struct serial_configure` before opening the device. Supported formats are 5–8 data bits, no/odd/even parity, and one or two stop bits, except for 5 data bits with two stop bits. The available baud rates depend on the configured input clock and the hardware divisor range of 1–65535.

Open with `RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX` for buffered reception and receive callbacks. In this driver, `INT_RX` uses a polling thread rather than hardware interrupts. Polling reads are available when opened without `INT_RX`.

Stop traffic before reconfiguring the device because configuration clears the hardware FIFOs. Transmit waits have a timeout; check the returned byte count for short writes. RS-485 direction control is not supported.

## References and license

- [ArtInChip board documentation](https://aicdoc.artinchip.com/topics/product/d213ecV4.html)
- [ArtInChip Luban-Lite SDK](https://gitee.com/artinchip/luban-lite), the source of the SoC definitions and hardware initialization sequences used by this BSP.

The BSP is licensed under Apache-2.0. Copyright and license notices are retained in the source files.
