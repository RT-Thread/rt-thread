# YuzukiNeko (Allwinner F101S3)

[简体中文版](README_zh.md)

This BSP supports YuzukiNeko, a Raspberry Pi Pico-sized single-board computer
built around the Allwinner F101S3 (Sun252i F101). Its C907 core is RV32IMAFDC
and the SoC integrates 16 MiB of LPSRAM at `0x40000000`. RT-Thread is linked to load
at `0x40010000`.

The board uses RT-Thread Device Model (DM) drivers and the built-in device
tree in `bsp/allwinner/dm/dts`. It does not use `libraries/sunxi-hal`.

## Board Overview

| Item | YuzukiNeko hardware |
| --- | --- |
| SoC | Allwinner F101S3, single T-Head C907 RISC-V CPU, up to 1 GHz |
| Memory | 16 MiB integrated LPSRAM |
| Boot storage | 16 MiB SPI NOR flash (PY25Q128HA) |
| Removable storage | microSD card socket, SDC0 |
| USB and power | USB Type-C for 5 V power, USB 2.0 device/FEL access |
| Expansion | Two 20-pin headers with GPIO, ADC, 5 V, 3.3 V, and GND |
| Audio | HPOUT analog-audio pads |
| Controls | FEL button and power LED; there is no reset button |
| Form factor | Approximately 51 x 21 mm |

UART1 is available on H2-11 (PB0/TX) and H2-10 (PB1/RX) at 115200 8N1. These
signals share the Type-C SBU routing, so a connected USB data cable can disturb
an external UART adapter.

## Toolchain

Use a bare-metal GNU toolchain with RV32 `imafdc` and `ilp32d` multilibs. The
following downloads the `riscv64-unknown-elf` toolchain used by RT-Thread CI.
Despite its `riscv64` prefix, it contains the required RV32 multilib.

```sh
toolchain_url=https://github.com/RT-Thread/toolchains-ci/releases/download/v1.4/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14.tar.gz
mkdir -p "$HOME/opt/riscv64-unknown-elf"
curl -L "$toolchain_url" | tar -xz -C "$HOME/opt/riscv64-unknown-elf" --strip-components=1
export RTT_EXEC_PATH="$HOME/opt/riscv64-unknown-elf/bin"
export RTT_CC_PREFIX=riscv64-unknown-elf-
riscv64-unknown-elf-gcc -v
```

Any compatible GNU toolchain can be used by setting the same two variables.
Install SCons through RT-Thread ENV or with `python -m pip install scons`.

## Build

```sh
cd bsp/allwinner/f101
scons --menuconfig
scons
```

`YuzukiNeko boot privilege mode` defaults to direct M-mode boot. Select
S-mode only when the installed boot firmware enters RT-Thread through an SBI
implementation and passes the standard RISC-V boot arguments.

The build creates:

- `rtthread.elf`, for debugging and symbol lookup;
- `rtthread.bin`, the raw image loaded at `0x40010000`.

### Display selection and validation

`YuzukiNeko display` selects one board display configuration at a time. The
default is the 360x360 ST77916 QSPI LCD. Select `CO6300 262x928 one-lane
MIPI-DSI AMOLED` for the OSPTEK AM319M262928ZS module; it enables DE0, TCON0,
and the one-lane RGB888 MIPI-DSI output. The module's VCI supply must already
be enabled by the display adapter. Its DSI pin group occupies PD12 through
PD21, so it cannot be used together with the ST77916 SPI1 panel configuration.

The same module has a CST3530 capacitive touchscreen at I2C address `0x58`.
The CO6300 board configuration enables it on I2C2 (`PB2`/SDA and `PB3`/SCL)
at 400 kHz and uses 20 ms polling, so only the I2C pair is required. When the
module's interrupt and reset lines are connected, add `interrupt-gpios` and
`reset-gpios` to its DTS node to use interrupt-driven reporting and hardware
reset.

The DE framebuffer is registered as `fb0`. After boot, these commands cover
the DE scanout and G2D paths:

```text
g2d_test
g2d_anim
```

`g2d_test` presents fill, BitBlt, scale, rotation, and alpha blend results on
`fb0`. `g2d_anim` exercises scaled and rotated composition continuously. Both
commands accept optional `g2d` and framebuffer device names. `jpegshow` and
`mjpegplay` can additionally validate JPEG decode and framebuffer presentation
when a compatible JPEG or MJPEG AVI file is available.

## Download and Run

This BSP produces a raw `rtthread.bin`; it does not replace the boot ROM,
boot0, GPT, or the board's boot configuration. The M-mode boot firmware copies
the `rtos` payload to `0x40010000` and jumps to `_start`. When S-mode is
selected, it must instead enter through SBI and pass the standard RISC-V boot
arguments.

### SPI NOR update

Use the current [xboot/xfel](https://github.com/xboot/xfel) for F101 FEL
access. Build it on the host, hold the board's FEL button while powering it,
then confirm that `xfel version` reports `F101`.

```sh
git clone https://github.com/xboot/xfel.git
make -C xfel
XFEL=$PWD/xfel/xfel
$XFEL version
$XFEL spinor
```

Do not write `rtthread.bin` directly to SPI NOR. Preserve the current
`melis-config` TOC item and package it together with the new `rtos` item as a
`sunxi-package` `boot_package.fex` using the board's existing
`package_rtos.cfg` and Allwinner `dragonsecboot` packaging tool. Only replace
the `bootA` package after taking a backup:

```sh
$XFEL spinor read 0xe0000 0x154000 f101-boota-backup.fex
$XFEL spinor write 0xe0000 boot_package.fex
$XFEL reset
```

`0xe0000` is the start of the `bootA` partition on the factory 16 MiB SPI NOR
layout. The backup is sufficient to restore the previous RTOS package with the
same `spinor write` command. Do not overwrite flash offset zero or the GPT.

## Device Support

| Device | Status | Notes |
| --- | --- | --- |
| ADC | Support | - |
| AUDIO | Support | - |
| UART | Support | - |
| DMA | Support | - |
| HWCrypto | Support | - |
| I2C | Support | - |
| SPI | Support | - |
| PWM | Support | - |
| Flash | Support | SPI-NOR/MTD |
| SDIO | Support | - |
| USB | Support | CDC ACM character-device |
| Watchdog | Support | - |
| IR-RX | Support | - |
| RTC | Support | - |
| Display | Support | QSPI ST77916 or MIPI-DSI CO6300; RGB/LVDS/DSI backend |
| Touch | Support | CST3530 on the CO6300 module |
| G2D | Support | - |
| Video | Support | - |

## References

- [YuzukiNeko hardware project](https://github.com/YuzukiHD/YuzukiNeko)
- [YuzukiNeko documentation](https://dshanpi.100ask.net/docs/F101-YuzukiNeko/)
- [OSPTEK AM319M262928ZS CO6300 panel reference](https://github.com/osptek/amoled-3.19-262x928-mipi-co6300)
- [OpenixSuit releases](https://github.com/YuzukiTsuru/OpenixSuit/releases)
