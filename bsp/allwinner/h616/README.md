# Allwinner H616

[简体中文版](README_zh.md)

This BSP targets the Allwinner H616 family on 64-bit ARM systems. It uses
RT-Thread Device Model (DM) drivers and boots as an AArch64 image through the
existing TF-A and U-Boot firmware. `rtthread.bin` is a raw image; it neither
contains nor replaces boot firmware or a device tree.

## Board Overview

The BSP is used with an MQ-Quad board. The supplied firmware DTB is
currently named `sun50i-h616-orangepi-zero2.dtb` and therefore reports
`OrangePi Zero2` as its model at boot. This is a firmware-device-tree label,
not an assertion that the MQ-Quad has Orange Pi Zero2 wiring. In particular,
do not enable Ethernet, Wi-Fi, displays, or GPIO-connected peripherals based
only on that board name; use the physical board schematic.

## Toolchain

Use a bare-metal AArch64 GNU toolchain. The BSP is regularly built with
`aarch64-none-elf-gcc` from Arm GNU Toolchain 14.3.Rel1. Any compatible
toolchain can be selected through these variables:

```sh
export RTT_EXEC_PATH=/opt/arm-gnu-toolchain-14.3.rel1-x86_64-aarch64-none-elf/bin
export RTT_CC_PREFIX=aarch64-none-elf-
aarch64-none-elf-gcc --version
```

Install SCons with RT-Thread ENV or `python -m pip install scons`.

## Build

```sh
cd bsp/allwinner/h616
scons --menuconfig
scons -j$(nproc)
```

The build creates:

- `rtthread.elf`, for debugging and symbol lookup;
- `rtthread.bin`, the raw AArch64 image loaded by U-Boot.

`SOC_H616` selects MMU, SMP, cache, DM, and OFW support.

## Boot

Keep the board's TF-A, U-Boot, Linux image, and base DTB intact. A U-Boot
script should load `rtthread.bin` to the board's normal kernel load address,
load the base DTB, then invoke the standard AArch64 image boot command. The
supplied firmware uses `kernel_addr_r=0x40080000` and `fdt_addr_r=0x4fa00000`.

Install the raw image on the boot filesystem, for example as
`/boot/rtthread.bin`. Preserve the existing board boot script and its overlay
processing.

The boot arguments must retain a serial console. For the current firmware,
UART0 is at `0x05000000`; a suitable early console argument is:

```text
earlycon=uart8250,mmio32,0x05000000,115200n8 console=ttyS0,115200n8
```

`cma=` and `coherent_pool=` may be added when the enabled DMA/video workload
needs reserved contiguous memory. Choose their sizes for the board's RAM and
do not overlap firmware-reserved regions.

## Device Support

| Device | Status | Notes |
| --- | --- | --- |
| UART | Support | DesignWare 8250 console. |
| Clock / reset / pinctrl / regulator | Support | H616 CCU/R CCU, pin controller, and AXP313A PMIC. |
| RTC | Support | Calendar and alarm framework. |
| DMA | Support | Sunxi DMA controller. |
| SDIO | Support | SDC0, SDC1, and SDC2 hosts. |
| I2C | Support | Sunxi I2C controller. |
| SPI | Support | Sunxi SPI controller. |
| PWM | Support | Sunxi PWM controller. |
| LED | Support | DT GPIO LEDs. |
| Watchdog | Support | Sunxi watchdog. |
| Thermal | Support | Four H616 thermal sensors. |
| IR receiver | Support | Sunxi IR receiver. |
| Internal codec | Support | `sound0`; LINEOUT requires an amplifier for a speaker. |
| HDMI audio | Support | AHUB I2S1 LPCM path (`hdmi-sound0`). |
| JPEG decode | Support | Video Engine JPEG/MJPEG decoder (`jpegd0`). |
| DE33 / HDMI video | Support | DE33 mixer, TCON-TV, and DW-HDMI framebuffer path. |
| G2D | Support | H616 graphics accelerator. |
| HWCrypto | Support | H616 CE AES and TRNG. |
| GPADC / LRADC | Support | H616 analog input controllers. |

## References

- [Allwinner H616 Linux device tree binding sources](https://github.com/torvalds/linux/tree/master/Documentation/devicetree/bindings)
- [RT-Thread Device Model documentation](https://www.rt-thread.io/document/site/#/rt-thread-version/rt-thread-standard/programming-manual/device/device)
