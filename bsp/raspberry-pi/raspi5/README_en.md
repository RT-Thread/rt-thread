# Raspberry Pi 5 BSP User Guide

[中文](README.md)

## 1. Introduction

This BSP provides 64-bit RT-Thread support for Raspberry Pi 5. It targets the Broadcom BCM2712 SoC, which contains four Cortex-A76 cores, and uses the RT-Thread Device Model to manage on-board devices and RP1 southbridge peripherals.

The current boot flow is: Raspberry Pi firmware loads U-Boot, U-Boot loads `rtthread.bin`, and the firmware-provided device tree is passed to RT-Thread. SMP is enabled by default, and the default console device is `uart10` from the device tree.

## 2. Prerequisites

### 2.1 Hardware

- Raspberry Pi 5;
- A microSD card and card reader;
- A 3.3 V TTL serial adapter;
- Optional: a wired network for TFTP boot.

> The serial interface must use 3.3 V levels. Do not connect an RS-232 or 5 V serial adapter directly. The default serial settings are `115200 8N1`, with hardware and software flow control disabled.

### 2.2 Software

- Python 3;
- SCons and the RT-Thread Env tools;
- An AArch64 bare-metal GCC toolchain;
- A Raspberry Pi 5-compatible U-Boot image;
- Optional: a TFTP server.

The default toolchain prefix is `aarch64-none-elf-`. The default search path in `rtconfig.py` is:

```text
/opt/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/bin/
```

Using environment variables is recommended so that repository files do not need to be modified:

```bash
export RTT_EXEC_PATH=/path/to/aarch64-toolchain/bin
export RTT_CC_PREFIX=aarch64-none-elf-
```

The build script prefers `-mtune=cortex-a76`. If an older compiler does not support it, the script falls back to `cortex-a73` and then `generic`.

## 3. Configuration and Build

Enter the BSP directory:

```bash
cd bsp/raspberry-pi/raspi5
```

To change the default configuration, open menuconfig first:

```bash
scons --menuconfig
```

Build the BSP:

```bash
scons -j$(nproc)
```

On Windows, run `scons` directly or replace `$(nproc)` with a suitable number of parallel jobs.

A successful build produces:

| File | Description |
| --- | --- |
| `rtthread.elf` | ELF image with symbols for debugging and disassembly |
| `rtthread.bin` | Raw binary image loaded by U-Boot |
| `rtthread.map` | Linker map |
| `rtt.asm` | Disassembly output |

The load address of `rtthread.bin` is `0x210000`, matching `ARCH_TEXT_OFFSET` in the default configuration. Do not change this address in the boot commands without updating the BSP configuration accordingly.

## 4. Preparing the Boot Media

### 4.1 Preparing U-Boot

Prepare a microSD card that can be recognized by the Raspberry Pi 5 firmware. Place a Raspberry Pi 5-compatible U-Boot image in the root of the FAT boot partition and name it:

```text
u-boot.bin
```

The [`tools/config.txt`](tools/config.txt) file contains the minimum firmware configuration required by this BSP:

```ini
kernel=u-boot.bin
dtparam=pciex1
```

If the boot partition already contains a `config.txt`, merge these settings into it. Do not overwrite display, serial, or other board-specific settings that are still required.

### 4.2 Copying the RT-Thread Image

For SD card boot, copy the generated `rtthread.bin` to the root of the first FAT partition:

```text
<boot partition>/rtthread.bin
```

The default commands use U-Boot device and partition `mmc 0:1`. If your SD controller or partition number differs, inspect it first:

```text
mmc list
mmc dev 0
part list mmc 0
fatls mmc 0:1
```

## 5. Booting from U-Boot

### 5.1 Common Boot Arguments

Set the RT-Thread boot arguments at the U-Boot console:

```text
setenv bootargs_rtt 'earlycon cma=8M coherent_pool=2M'
saveenv
```

The boot commands copy the live device tree provided by the firmware and update `/chosen/bootargs`. Do not replace it with a static DTB for another board revision or Raspberry Pi model, because RP1, PCIe, and on-board peripheral information may be incomplete.

### 5.2 Booting from the SD Card

```text
setenv bootrtt 'mmc dev 0; fatload mmc 0:1 0x210000 rtthread.bin; fdt addr ${fdtcontroladdr}; fdt move ${fdt_addr_r} 0x20000; fdt addr ${fdt_addr_r}; fdt resize 8192; setenv bootargs ${bootargs_rtt}; fdt set /chosen bootargs ${bootargs}; booti 0x210000 - ${fdt_addr_r}'
saveenv
run bootrtt
```

After manual boot has been verified, enable automatic boot if desired:

```text
setenv bootcmd 'run bootrtt'
saveenv
```

### 5.3 Booting over TFTP

Place `rtthread.bin` in the TFTP server root. The addresses below are examples and must be adjusted for your network:

```text
setenv bootrtt_tftp 'setenv ethprime eth0; setenv ipaddr 192.168.10.2; setenv serverip 192.168.10.1; setenv netmask 255.255.255.0; ping 192.168.10.1; tftp 0x210000 rtthread.bin; fdt addr ${fdtcontroladdr}; fdt move ${fdt_addr_r} 0x20000; fdt addr ${fdt_addr_r}; fdt resize 8192; setenv bootargs ${bootargs_rtt}; fdt set /chosen bootargs ${bootargs}; booti 0x210000 - ${fdt_addr_r}'
saveenv
run bootrtt_tftp
```

If the U-Boot Ethernet device is not named `eth0`, inspect `printenv ethact ethprime` or `bdinfo` and adjust `ethprime`.

## 6. Expected Output

After a successful boot, the serial console should display the RT-Thread banner and SMP initialization messages before entering MSH:

```text
 \ | /
- RT -     Thread Operating System
 / | \
 2006 - 2026 Copyright by RT-Thread team
Hi, this is RT-Thread!!
msh />
```

The exact version, build time, and device initialization messages depend on the active configuration.

## 7. Default Configuration

The default `rtconfig.h` enables the major features listed below. Whether a particular device is detected still depends on the Raspberry Pi firmware version, live device tree, expansion boards, and connected peripherals.

| Category | Major features enabled by default |
| --- | --- |
| CPU | AArch64, four-core SMP, MMU, cache, and ASID |
| Console | PL011/8250 serial drivers; `uart10` is the default console |
| Storage | SDHCI/MMC, FatFs, and NVMe over PCIe |
| Networking | RP1 Ethernet, PHY support, lwIP, and DHCP |
| Buses | PCIe, I2C, SPI, SDIO, and Device Tree/OFW |
| RP1 peripherals | ADC, PWM, GPIO/pinctrl, clocks, and MFD |
| System services | RTC, watchdog, DMA, thermal control, DVFS, and mailbox |
| Multimedia and input | I2S audio, framebuffer, touchscreen, joystick, and keyboard |
| User space | RT-Smart, DFS, POSIX, LWP, and dynamic linking |

## 8. Troubleshooting

### 8.1 U-Boot Cannot Find `rtthread.bin`

Run:

```text
fatls mmc 0:1
```

Check the filename, device number, and partition number. Linux filenames are case-sensitive.

### 8.2 `Bad Linux ARM64 Image magic!` or No Output After Jumping

- Make sure `rtthread.bin`, not `rtthread.elf`, was loaded;
- Make sure both the load and boot addresses are `0x210000`;
- Make sure the command is `booti 0x210000 - ${fdt_addr_r}`;
- Check the serial settings and `stdout-path` in the device tree.

### 8.3 Device Tree or RP1 Peripheral Initialization Fails

- Make sure the Raspberry Pi firmware and U-Boot support Raspberry Pi 5;
- Make sure `config.txt` contains `dtparam=pciex1`;
- Preserve and pass the live device tree provided by the firmware;
- Do not replace it in U-Boot with a DTB for another Raspberry Pi model.

### 8.4 TFTP Download Fails

Check `ipaddr`, `serverip`, `netmask`, the TFTP root, the host firewall, and the Ethernet connection. Run `ping ${serverip}` in U-Boot before downloading the image.

## 9. Notes After Reconfiguration

After running `scons --menuconfig`, the active configuration may differ from the default `rtconfig.h` documented here. Before submitting BSP configuration changes, inspect the generated `rtconfig.h` and verify newly enabled drivers on Raspberry Pi 5 hardware.
