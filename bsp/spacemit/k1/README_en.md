**English** | [中文](README.md)

# SpacemiT K1 BSP

## 1. Introduction

This BSP ports the RT-Thread standard edition to the SpacemiT K1 64-bit
RISC-V SoC. The boot procedure is currently validated only on the
**Banana Pi BPI-F3 SBC**. It relies on the vendor U-Boot/OpenSBI firmware and
the Device Tree selected by U-Boot.

The default configuration enables the MMU and starts four CPUs. RT-Thread
runs in S-mode. The early console uses SBI, while the normal console is
`ttyS0` at 115200 baud, 8 data bits, no parity, and 1 stop bit.

## 2. Supported Features

| Feature | Status | Notes |
| --- | --- | --- |
| RISC-V MMU / SMP | Supported | Four CPUs are enabled by default |
| UART / early console | Supported | SBI early console and 8250/PXA UART |
| Clock / reset / power domain | Supported | K1 CCU, reset, and PM domain |
| I2C / SPI / QSPI / PWM | Supported | Includes PMIC child devices |
| SD / eMMC | Supported | SDHCI and eMMC HS400 |
| RTC / ADC / power key | Supported | SpacemiT PMIC |
| PCIe / NVMe | Supported | DesignWare PCIe host |
| Ethernet / PTP | Supported | Enable `RT_USING_ETHERNET` and `RT_ETHERNET_K1X_EMAC` |
| HDMI framebuffer | Supported | Initializes the HDMI display path from a cold boot |
| JPU / V2D | Supported | JPEG decoding and 2D acceleration |
| HDMI / ES8326 audio | Supported | 48 kHz, stereo, 16-bit PCM |
| DVFS / thermal | Supported | CPUfreq, OPP, and four thermal zones |
| AES / hardware RNG / eFuse | Supported | Includes SoC ID and serial number |
| MIPI DSI / camera / USB | Not ported | These functions are not included in this BSP |

## 3. Build Environment

### 3.1 Dependencies

A 64-bit Linux host is recommended. On Ubuntu or Debian, install:

```shell
sudo apt install scons python3 python3-pip
pip3 install kconfiglib
```

### 3.2 Toolchain

A RISC-V64 Linux musl GCC toolchain can be obtained from:

- SpacemiT toolchain archive: <https://archive.spacemit.com/toolchain/>
- RT-Thread RISC-V64 musl toolchain: <https://download.rt-thread.org/rt-smart/riscv64/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu_251248.tar.bz2>

The following example assumes that the toolchain is extracted to
`/opt/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu`:

```shell
export RTT_CC=gcc
export RTT_EXEC_PATH=/opt/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin
export RTT_CC_PREFIX=riscv64-unknown-linux-musl-
```

Verify the toolchain with:

```shell
${RTT_EXEC_PATH}/${RTT_CC_PREFIX}gcc --version
```

## 4. Build

Enter the BSP directory:

```shell
cd bsp/spacemit/k1
```

To change the configuration, run:

```shell
scons --menuconfig
```

Build the BSP:

```shell
scons -j$(nproc)
```

A successful build generates:

| File | Description |
| --- | --- |
| `rtthread.elf` | ELF image with debug information |
| `rtthread.bin` | Kernel image loaded by U-Boot |
| `rtthread.map` | Linker map |

Clean the build output with:

```shell
scons -c
```

## 5. Boot on Banana Pi BPI-F3

> The commands in this section apply only to the vendor U-Boot environment
> on the Banana Pi BPI-F3. Other K1 boards may use different partitions,
> Device Trees, and U-Boot variables.

### 5.1 Install the Image

Place `rtthread.bin` in the root of the BPI-F3 boot filesystem, next to the
Linux `Image` file and the `k1-x_*.dtb` files. The U-Boot `loadknl` command
loads the file specified by `knl_name` from the active boot filesystem.

### 5.2 Configure U-Boot

Run the following commands from the U-Boot console:

```shell
setenv rtt_bootargs 'earlycon=sbi console=ttyS0,115200 cma=32M coherent_pool=8M root=sd0p4 rootfstype=elm rootwait rw'
setenv boot_rtt 'setenv knl_name rtthread.bin; setenv bootargs ${rtt_bootargs}; run detect_dtb; run loadknl; run loaddtb; setenv ramdisk_combo -; run start_kernel'
saveenv
```

`saveenv` is only required once. Boot RT-Thread with:

```shell
run boot_rtt
```

Important boot arguments:

- `earlycon=sbi` provides output before the normal UART driver is ready.
- `cma=32M coherent_pool=8M` reserves memory for the framebuffer, JPU, V2D,
  NVMe, and other DMA devices.
- `root=sd0p4 rootfstype=elm` mounts the FAT filesystem on the RT-Thread
  `sd0p4` device as the root filesystem.

Change `root=` if the storage enumeration order or partition layout differs.
The vendor U-Boot environment must provide the `detect_dtb`, `loadknl`,
`loaddtb`, and `start_kernel` commands.

### 5.3 Expected Output

After a successful boot, the serial console displays:

```text
 \ | /
- RT -     Thread Operating System
 / | \
 ...
msh />
```

## 6. Validation Commands

```shell
list_device
list_irq
list_blk
list_thermal
list_dvfs
dvfs dump cpufreq0
core_mark
adc probe adc0
adc read 0
date
jpu_show /path/to/image.jpg fb0
v2d_test fb0
audio_test snd-hdmi 2
ptp_test
```

`jpu_show` reads a baseline JPEG from the filesystem. No test image is
embedded in the BSP.

Before using Ethernet, enable Ethernet and the K1X EMAC in `menuconfig`.
Then configure the actual interface, `e0` or `e1`, for example:

```shell
ifconfig e1 192.168.10.2 192.168.10.1 255.255.255.0
ping 192.168.10.1 e1
```

## 7. Notes

- The Device Tree is selected by the BPI-F3 U-Boot `detect_dtb` command. Do
  not use a DTB for a different board.
- HDMI display requires the `cma` and `coherent_pool` reservations. The
  framebuffer may fail to initialize if either pool is too small.
- HDMI ADMA requires the embedded K1 RCPU `esos.elf` firmware and the
  reserved-memory regions in the Device Tree.
- MIPI display is not validated. The current display driver targets HDMI.

