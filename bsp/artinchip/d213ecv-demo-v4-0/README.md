# D213ECV-DEMO-V4-0

[English](README.md) | [中文](README_zh.md)

## Hardware

- Board: ArtInChip D213ECV-DEMO-V4-0.
- SoC: D213ECV, T-Head C906, RV64GC (IMAFDC), single hart, M-mode.
- Memory: 128 MiB DDR3 at `0x40000000`.
- Console: UART0, PA.0 TX / PA.1 RX, 115200 baud, 8N1, no flow control.
- [Official board information](https://aicdoc.artinchip.com/topics/product/d213ecV4.html).

| Function | Support |
|----------|-------------|
| Startup, scheduler, double-precision FPU context | RT-Thread RISC-V common port |
| System tick | D213 CLINT comparator and time CSR, common timer core |
| Interrupt controller | Common PLIC driver, D213 priority-enable setup |
| Clock/reset | GPIO and UART0 gates only; loader retains PLL/DDR ownership |
| UART0 | Serial-v1, polling TX and a thread feeding the standard RX FIFO |
| FinSH/MSH, heap, device framework | Enabled by default |

The UART adapter keeps the UART0 PLIC line masked and polls RX at a nominal 1 ms interval. The RX thread runs one priority level above FinSH so console output cannot starve polling; the default serial receive buffer is 512 bytes. It is intended for an interactive console; sustained transfers or long scheduling delays can lose received data. UART hardware interrupts and DMA are not supported. Selecting serial-v2 disables the UART0 option because this adapter uses the serial-v1 API.

## UART configuration

UART0 is enabled by default with `BSP_USING_UART0`. It uses PA.0 TX / PA.1 RX (function 5) and retains the loader-configured input clock, 48 MHz by default.

Use `RT_DEVICE_CTRL_CONFIG` with `struct serial_configure` before opening the port. The adapter accepts 5–8 data bits, no/odd/even parity, and one or two stop bits. Five data bits with two stop bits is rejected: the hardware would produce 1.5 stop bits, which serial-v1 cannot express. Unsupported formats, flow control, inverted/MSB-first operation and divisors outside 1–65535 return `-RT_EINVAL` before changing registers. Configuration clears FIFOs, waits up to 100 ms for the controller to become idle and checks LCR readback before accessing the divisor registers. A busy timeout returns `-RT_ETIMEOUT`; rejected LCR writes return `-RT_EIO`. Baud rates use the nearest integer divisor; the resulting baud error depends on the input clock and requested rate.

Open with `RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX` to use the framework's receive FIFO and callback, or use polling reads without `INT_RX`. Here `INT_RX` selects the serial-v1 buffered interface; hardware IRQ reception remains disabled. Closing the device disables buffered reception. Reconfiguration resets the hardware FIFOs, so configure only with traffic stopped. DMA and RS-485 direction control are not provided.

## Build independently

Install Python 3, SCons, kconfiglib and a GNU bare-metal RISC-V toolchain providing `riscv64-unknown-elf-*`, RV64GC and the `lp64d` ABI:

```sh
python -m pip install scons kconfiglib
cd bsp/artinchip/d213ecv-demo-v4-0
export RTT_EXEC_PATH=/path/to/riscv-toolchain/bin
scons --pyconfig-silent
scons -j8
```

On PowerShell, set the toolchain path with:

```powershell
$env:RTT_EXEC_PATH = 'C:/path/to/riscv-toolchain/bin'
scons --pyconfig-silent
scons -j8
```

The compiler can also be added to PATH. Set `RTT_CC_PREFIX` when using a different toolchain prefix. The build produces `rtthread.elf`, `rtthread.bin` and `rtthread.map`.

Local builds use Xuantie V2.6.1 (GCC 10.2.0); CI uses RT-Thread's public GCC 10.2.0 RISC-V toolchain. For GCC 12 and later, `rtconfig.py` adds explicit `zicsr_zifencei` to the ISA string. Those newer toolchains have not been validated for this BSP.

## Configuration and distribution

The default `.config` enables UART0/Serial-v1, MSH, heap and the base kernel, with a 1000 Hz system tick. Configure the project and generate `rtconfig.h` with:

```sh
scons --menuconfig
scons --pyconfig-silent
scons -j8
scons --dist
```

Board options include UART0 selection, the UART input clock (default 48 MHz) and the CLINT timebase (default 4 MHz). Set the frequency values to match the bootloader configuration; these options do not change hardware dividers. Generate `rtconfig.h` with the configuration tools above.

Extract `dist/project.zip` into a separate directory and unset `RTT_ROOT`. Run the same configuration and build commands in the extracted `project/` directory. The archive contains the BSP, its libraries, RT-Thread sources and build tools.

## Memory and startup requirements

| Region | Address / purpose |
|--------|-------------------|
| DDR3 | `0x40000000..0x47ffffff`, 128 MiB |
| RT-Thread | `0x40000000..0x477fffff`, 120 MiB |
| Loader reservation | `0x47800000..0x47ffffff`, upper 8 MiB |
| Binary load address / ELF entry | `0x40000000` |

The heap starts after static sections and the early stack, and ends at `0x47800000`. The early common-port stack is 16-byte aligned; the interrupt stack resides in BSS. Linker assertions check section ordering, stack alignment and heap bounds.

An ArtInChip-compatible external loader must:

1. Initialize DDR, PLLs, bus clocks and CPU memory/cache attributes.
2. Configure UART0 for a 48 MHz input clock and provide a 4 MHz timebase, or use matching BSP frequency settings.
3. Load the image at `0x40000000`, clean loaded data and synchronize the instruction cache if caches are enabled.
4. Enter the first instruction on hart 0 in M-mode, with interrupts disabled, MMIO non-cacheable, no active DMA and no outstanding claimed PLIC IRQs.

The BSP retains the bootloader's DDR, PLL, UART0 clock-divider and cache configuration. The RISC-V common port handles startup and PLIC claim/complete; board initialization sets up the C906, peripheral gates and timer access.

## Load and use the console

Package `rtthread.bin` in the FIT or firmware format required by your ArtInChip bootloader, then load it at `0x40000000`. Use a bootloader with DDR initialization and a matching partition layout.

For a `demo128-nand` full image on 2 KiB-page NAND, keep the assembled `bootloader.aic` within 411,648 bytes, including PBP, headers and resources. This is the SPL page-table limit. Use the existing bootloader and partition layout for an OS-only update.

After loading, connect UART0 at 115200 8N1. Expected output includes:

```text
RT-Thread Operating System
D213ECV-DEMO-V4-0
msh >
```

| Command | Purpose |
|---------|---------|
| `help` | List shell commands |
| `version` | Show RT-Thread version |
| `ps` or `list thread` | List threads |
| `list device` | List registered devices; the default exposes `uart0` |
| `list timer` | List timers and the current tick |
| `free` | Show heap usage |

The default thread list includes `tshell`, `uart0rx` and `tidle0` after the startup application exits.

## Validation status

The UART0 image built on November 14, 2026 at 02:39:03 reached MSH on the board. Serial logs confirm repeated `help`, `list device`, `list timer` and `ps` commands, with only `uart0` registered. The receive thread runs at priority 19, above the shell at priority 20. Board testing also confirmed stable MSH startup after a full power cycle and repeated command entry while `help` and `ps` output was in progress.

| Check | Result |
|-------|--------|
| Default UART0 configuration and independent SCons build | Passed with GCC 10.2.0 |
| No-UART and serial-v2 exclusion configurations | Passed with GCC 10.2.0 |
| Dist export and independent rebuild outside the repository | Passed with GCC 10.2.0 |
| UART0 formats, parameter validation, TX timeout, RX close/reopen and DLAB protection | Host MMIO simulation passed; 21 valid formats |
| SPI-NAND loader handoff, FIT CRC32 and RT-Thread startup | Passed on the previous UART0 revision |
| UART0 TX/RX, repeated MSH `help` and `ps` | Confirmed by current image board logs |
| MSH `version` and `free` | Passed on the previous UART0 revision |
| Device/timer enumeration | Current image reports only `uart0`, receive-thread timer and current tick |
| Full power-cycle startup and command input during `help` / `ps` output | Passed on the current UART0 image |
| Tick accuracy, preemption and repeated wakeup | Pending |
| Heap stress/alignment and FPU/FCSR preservation under preemption/IRQs | Pending |
| Controlled external PLIC delivery/complete, reset cycles and soak | Pending |

## Source and license

The BSP is licensed under Apache-2.0.

SoC/register definitions, hardware sequences and board pinmux derive from the public [ArtInChip Luban-Lite SDK](https://gitee.com/artinchip/luban-lite). The following table lists the vendor source paths:

| BSP content | SDK source | License |
|-------------|------------|---------|
| D213 addresses and CMU gate/reset bits | `bsp/artinchip/sys/d21x/include/aic_soc.h`, `aic_clk_id.h` | Apache-2.0 |
| C906 and PLIC setup | `bsp/artinchip/sys/d21x/system.c` | Apache-2.0 |
| UART registers/programming | `bsp/artinchip/hal/uart/aic_hal_uart.c` | Apache-2.0 |
| GPIO pin configuration | `bsp/artinchip/hal/gpio/aic_hal_gpio.c`, `target/d21x/demo128-nand/pinmux.c` | Apache-2.0 |
| Gate/reset sequencing | `bsp/artinchip/hal/cmu/aic_hal_clk.c` | Apache-2.0 |
