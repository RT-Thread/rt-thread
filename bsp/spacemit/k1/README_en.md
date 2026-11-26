**English** | [中文](README.md)

# SpacemiT K1 BSP

## Introduction

The SpacemiT K1 is a 64-bit RISC-V SoC with eight X60 CPU cores, floating-point
and vector extensions, and peripheral interfaces for SD/eMMC, PCIe, Ethernet,
display, and audio.

This BSP uses the RT-Thread standard edition and device model, with board
hardware described by a Device Tree. U-Boot/OpenSBI boots RT-Thread in S-mode.
The default configuration enables the MMU and eight-core SMP, with support for
storage, networking, multimedia, and power management.

The validation platform is the **Banana Pi BPI-F3 SBC**. SBI provides early
console output, followed by UART0 at 115200 8N1. The boot commands below apply
only to this board's vendor firmware environment.

## Supported Features

| Feature | Status | Notes |
| --- | --- | --- |
| MMU / SMP | Supported | Eight CPU cores enabled by default |
| UART / early console | Supported | UART0 and SBI early output |
| Clock / reset / power domain | Supported | Clock, reset, and power domain control |
| GPIO / pinctrl / I2C / PWM | Supported | Pin configuration and basic peripherals |
| SPI / QSPI | Supported | SPI NOR |
| SD / eMMC | Supported | SDHCI and eMMC HS400 |
| RTC / ADC / power key | Supported | SpacemiT PMIC child devices |
| PCIe / NVMe | Supported | PCIe host and NVMe block devices |
| Ethernet / PTP | Supported | K1X EMAC and PTP clocks |
| HDMI framebuffer | Supported | Cold-boot display initialization |
| JPU / V2D | Supported | JPEG decoding and 2D graphics acceleration |
| HDMI / ES8326 audio | Supported | 48 kHz, stereo, 16-bit PCM |
| CPUfreq | Supported | OPP-based frequency and voltage scaling |
| Thermal | Supported | Four sensors; sampling initialization fix awaits validation |
| AES / RNG / eFuse | Supported | Hardware crypto, random numbers, and chip information |
| Display | Supported | HDMI |

## Build

Install SCons, Python 3, and kconfiglib. Toolchain downloads:

- [SpacemiT toolchain archive](https://archive.spacemit.com/toolchain/)
- [RT-Thread RISC-V64 musl GCC](https://download.rt-thread.org/rt-smart/riscv64/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_251248.tar.bz2)

With the toolchain installed under `/opt`, run from the RT-Thread root:

```shell
cd bsp/spacemit/k1
export RTT_CC=gcc
export RTT_EXEC_PATH=/opt/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin
export RTT_CC_PREFIX=riscv64-unknown-linux-musl-
scons
```

This generates `rtthread.bin` and `rtthread.elf`.
Use `scons --menuconfig` to change the configuration.

## Boot

These commands apply only to the **Banana Pi BPI-F3 vendor U-Boot/OpenSBI environment**.

Place `rtthread.bin` on the boot partition alongside Linux `Image` and
`k1-x_*.dtb`. Run in the U-Boot console:

```shell
setenv rtt_bootargs 'earlycon=sbi console=ttyS0,115200 cma=32M coherent_pool=8M root=sd0p4 rootfstype=elm rootwait rw'
setenv boot_rtt 'setenv knl_name rtthread.bin; setenv bootargs ${rtt_bootargs}; run detect_dtb; run loadknl; run loaddtb; setenv ramdisk_combo -; run start_kernel'
saveenv
run boot_rtt
```

For subsequent boots, run `run boot_rtt`. Adjust `root=sd0p4` for your
partition layout and retain the DMA memory arguments for display and other devices.
