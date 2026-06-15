# QEMU/AArch64 VIRT BSP Introduction

[中文页](README_zh.md) | English

## 1. Introduction

AArch64 is the 64-bit execution state of the ARMv8 architecture for machines executing A64 instructions. This BSP ports RT-Thread to the QEMU `virt` AArch64 machine, based on the device model (DM), Open Firmware (OFW/FDT), and PCI bus framework. It serves as a development and validation platform for VirtIO, PCI, and other platform drivers.

Default configuration highlights:

| Item | Description |
| ---- | ----------- |
| RT-Thread version | 5.3 |
| Architecture | ARMv8 AArch64, MMU |
| SMP | 4 cores (`RT_CPUS_NR=4`) |
| Interrupt controller | GICv2 / GICv3 (with ITS, MSI) |
| Console | UART0 (PL011, `ttyAMA0`) |
| Root filesystem | VirtIO Block `vda0`, FatFs (elm-chan) |
| Memory | 128 MB by default (adjustable via `qemu.py -mem`) |

## 2. Compiling

ARM Developer GNU cross-compiler toolchain is recommended, supporting Linux and Windows:

```
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads/
```

Download the `xxx-aarch64-none-elf` package for the x86_64 hosted platform, extract it, and set the `RTT_EXEC_PATH` environment variable to the compiler's `bin` directory.

Enter the `rt-thread/bsp/qemu-virt64-aarch64` directory and run:

```
scons
```

This produces `rtthread.elf` and `rtthread.bin`.

You can also compile with a specific toolchain path:

```
scons --exec-path="path-to-gcc-toolchain"
```

Use `scons --menuconfig` to change configuration, then run `scons` again to rebuild.

## 3. Running

This BSP uses the `qemu-system-aarch64` emulator and is started via `qemu.py`.

### 3.1 Installing QEMU

Windows:

```
https://www.qemu.org/download/
```

Linux (Ubuntu, Deepin, etc.):

```
sudo apt update
sudo apt install qemu-system-arm
```

Some optional features require a minimum QEMU version:

| Feature | Minimum QEMU version |
| ------- | -------------------- |
| UFS storage | 8.2.0 |
| VirtIO Sound (`-sound virtio`) | 8.2.0 |

### 3.2 Environment Variables

| Variable | Description |
| -------- | ----------- |
| `RTT_QEMU_ROOT` | Prefix path to QEMU binaries (the script appends `qemu-system-aarch64`) |
| `RTT_ROOT` | RT-Thread source root; defaults to two levels above the BSP directory |

### 3.3 Basic Startup

In the BSP directory, run:

```
python qemu.py
```

or:

```
./qemu.py
```

On first run, 64 MB `qcow2` disk images are created automatically for each storage device. The default is `-nographic` mode with serial output on the current terminal.

Typical boot log:

```
heap: [0x40042aa0 - 0x40142aa0]

 \ | /
- RT -     Thread Operating System
 / | \     5.3.0 build ...
 2006 - 2026 Copyright by rt-thread team
hello rt-thread
msh />
```

### 3.4 `qemu.py` Command-Line Options

| Option | Default | Description |
| ------ | ------- | ----------- |
| `-gic` | `2` | GIC version (`2` or `3`); auto-switches to GICv3 when `-smp` > 8; with `-el 2` and GICv3, internally uses `gic-version=max` (not passable via `-gic max`) |
| `-smp` | `RT_CPUS_NR` (4) | Number of CPU cores; `-dtbo` adds 1 automatically when `amp_soc` is present |
| `-mem` | `128` | Memory size (MB) |
| `-el` | `1` | Exception level: `1` default; `2` virtualization on; `3` secure on |
| `-bootargs` | see below | Kernel boot arguments |
| `-initrd` | — | Path to initrd image |
| `-graphic` | — | Graphics mode (ramfb + `virtio-gpu-device` + VirtIO keyboard/tablet), replaces `-nographic` |
| `-gl` | — | In graphics mode, attach `virtio-gpu-gl-pci` and enable QEMU display OpenGL (e.g. `-gl gtk`); requires QEMU built with `--enable-opengl` and `--enable-virglrenderer`; must be used with `-graphic` |
| `-debug` | — | Enable GDB debugging (`-S -s`) |
| `-dumpdtb` | — | Export runtime DTB and convert to DTS |
| `-dtb` | — | Use a custom DTB file |
| `-virtio-block` | `virtio` | VirtIO Block disk image prefix (creates `virtio.qcow2`, mounted as `vda`) |
| `-scsi` | `scsi` | VirtIO SCSI disk image prefix |
| `-flash` | `flash` | pflash disk image prefix (pflash1, CFI NOR) |
| `-emmc` | `emmc` | SDHCI eMMC disk image prefix |
| `-nvme` | `nvme` | NVMe disk image prefix |
| `-ahci` | `ahci` | AHCI SATA disk image prefix |
| `-ufs` | `ufs` | UFS disk image prefix (QEMU ≥ 8.2.0) |
| `-cdrom` | — | SCSI CD-ROM image path (e.g. ISO file) |
| `-sound` | `hda` | Audio device: `hda` (Intel HDA) or `virtio` (VirtIO Sound PCI) |
| `-tap` | — | Use TAP networking (replaces user mode) |
| `-ssh` | `12055` | SSH port forwarding in user mode (`hostfwd=tcp::PORT-:22`) |
| `-9p` | — | VirtIO 9P shared directory path (enable VirtIO 9P in menuconfig) |
| `-camera` | — | Host V4L2 device path (e.g. `/dev/video0`); Linux only; read access to the device is required (usually add your user to the `video` group); compiles and runs `qemu-device-camera.c` in the background, then attaches a vfio-user PCI camera (requires **libvfio-user**) |
| `-dtbo` | — | AMP mode: DTBO overlay file (e.g. `amp.dtsi`); auto-increments `-smp` by 1; **requires Smart kernel** and sufficient `-mem` (see below) |

Default `-bootargs`:

```
console=ttyAMA0 earlycon cma=8M coherent_pool=2M root=vda0 rootfstype=elm rootwait rw
```

### 3.5 Common Startup Examples

Graphics (VirtIO GPU + keyboard/mouse):

```
./qemu.py -graphic
```

QEMU OpenGL display (`-gl`):

```
./qemu.py -graphic -gl gtk
```

> **Note**: `-gl` enables OpenGL only on the QEMU / host display path (`virtio-gpu-gl-pci` + VirGL). This BSP includes only the VirtIO GPU 2D framebuffer driver by default — **no OpenGL / VirGL user-space or kernel implementation**. `-gl` does not provide OpenGL acceleration inside RT-Thread. For graphics demos, use `-graphic` (`virtio-gpu-device`) with the framebuffer stack.

GDB debugging:

```
./qemu.py -debug
```

More memory and GICv3:

```
./qemu.py -mem 256 -gic 3
```

Mount CD-ROM:

```
./qemu.py -cdrom /path/to/image.iso
```

VirtIO Sound:

```
./qemu.py -sound virtio
```

9P directory sharing (enable `RT_VIRTIO_9P` first):

```
./qemu.py -9p /path/to/share
```

AMP heterogeneous multi-core (RPMSG slave, **requires Smart version**):

```
./qemu.py -dtbo amp.dtsi -mem 258
```

> **Note**: The AMP demo requires the **Smart version** (`RT_USING_SMART`) and **`-mem 258`** (memory layout in `amp.dtsi` needs ~258 MB; the default 128 MB is insufficient). `qemu.py` also increments `-smp` by 1 when `amp_soc` is detected (e.g. `RT_CPUS_NR=4` runs as `-smp 5`). QEMU `loader` pre-loads `amp.dtb` and `rtthread.bin` to fixed physical addresses in `amp.dtsi` (e.g. `kernel-entry = 0x48480000`); the primary core then starts the slave via PSCI. The standard kernel must run in a region where virtual addresses equal physical addresses and cannot be used for the slave address space. Enable Smart in menuconfig and rebuild.

Camera demo (requires `-graphic` for framebuffer overlay in `camera.c`):

```
./qemu.py -graphic -camera /dev/video0
```

> **Note**: `-camera` requires a host V4L2 device path. On Linux, install [libvfio-user](https://github.com/nutanix/libvfio-user) first (see comments in `qemu-device-camera.c`), and ensure your user can read the device node (e.g. `sudo usermod -aG video $USER` then log in again, or check with `ls -l /dev/video0`). Open will also fail if another program is using the camera. The script compiles `qemu-device-camera.c`, waits for `/tmp/qemu-device-camera.sock`, starts QEMU, and stops the helper process when QEMU exits.

### 3.6 Console and Telnet

| Port | Device | Description |
| ---- | ------ | ----------- |
| Current terminal | UART0 (PL011) | Default `-nographic` serial |
| `4321` | VirtIO Console | `telnet 127.0.0.1 4321`, port name `org.rt-thread.console` |
| `4322` | PCI 8250 serial | `telnet 127.0.0.1 4322` |
| `4323` | AMP slave console | `-dtbo` mode only, `telnet localhost 4323` |

VirtIO Console connection example:

```
telnet 127.0.0.1 4321
```

### 3.7 Networking

User-mode networking (`-netdev user`) is used by default, with SSH forwarded to local port `12055` (changeable via `-ssh`).

TAP networking example:

```
./qemu.py -tap
```

TAP requires bridge setup on Linux; support on Windows / WSL is limited. SSH port forwarding is not available in TAP mode.

## 4. Default QEMU Devices

`qemu.py` attaches the following devices by default (matching the default driver configuration). UFS is included only when QEMU ≥ 8.2.0; optional devices are listed with their triggering option.

| QEMU device | Image file | RT-Thread side |
| ----------- | ---------- | -------------- |
| `virtio-blk-device` | `virtio.qcow2` | VirtIO Block, root partition `vda0` |
| `virtio-scsi-pci` + `scsi-hd` | `scsi.qcow2` | VirtIO SCSI |
| `scsi-cd` (optional `-cdrom`) | user-specified | SCSI CD-ROM |
| `pflash` (index=1) | `flash.qcow2` | MTD NOR CFI |
| `sdhci-pci` + `sd-card` | `emmc.qcow2` | SDHCI eMMC (enable SDIO) |
| `nvme` + `nvme-ns` | `nvme.qcow2` | NVMe |
| `ahci` + `ide-hd` | `ahci.qcow2` | AHCI SATA |
| `ufs` + `ufs-lu` (QEMU ≥ 8.2.0 only) | `ufs.qcow2` | UFS |
| `virtio-net-device` | — | VirtIO Net (enable network stack) |
| `virtio-rng-device` | — | VirtIO RNG |
| `virtio-crypto-device` | — | VirtIO Crypto |
| `virtio-serial-device` | — | VirtIO Console / RPROC Serial |
| `pci-serial` (8250 PCI) | — | PCI 8250 serial |
| `intel-hda` + `hda-duplex` | — | Intel HDA audio |
| `i6300esb` | — | I6300ESB watchdog |
| `edu` | — | QEMU EDU teaching device (MFD) |
| `virtio-gpu-device` (`-graphic`) | — | VirtIO GPU 2D (default) |
| `virtio-gpu-gl-pci` (`-graphic -gl`) | — | QEMU OpenGL display; no GL driver on RT-Thread side |
| `virtio-keyboard-device` / `virtio-tablet-device` | — | VirtIO Input |
| `virtio-9p-device` (`-9p`) | — | VirtIO 9P (enable driver) |
| `virtio-sound-pci` (`-sound virtio`) | — | VirtIO Sound |
| vfio-user camera (`-camera <path>`) | host V4L2 device | PCI camera (BSP `drv_camera`) |

## 5. Driver Support

### 5.1 Enabled by Default

| Category | Driver | Description |
| -------- | ------ | ----------- |
| Serial | PL011 | UART0, system console `uart0` / `ttyAMA0` |
| Serial | 8250 PCI | PCI serial, Telnet port 4322 |
| RTC | PL031 | Real-time clock |
| GPIO | PL061 | GPIO controller |
| Watchdog | I6300ESB | PCI watchdog |
| Storage | VirtIO Block | Block device, `vda` |
| Storage | VirtIO SCSI | SD / CD-ROM |
| Storage | AHCI PCI | SATA disk |
| Storage | NVMe PCI | NVMe disk |
| Storage | UFS PCI | UFS disk |
| Storage | MTD NOR CFI | pflash flash |
| Storage | BLK partition | DFS / EFI partition table |
| Graphics | VirtIO GPU | 2D framebuffer (`-graphic`); no OpenGL / VirGL |
| Graphics | Framebuffer | RAMFB 800×600 (`RT_GRAPHIC_ROMFB_WIDTH` / `HEIGHT`, `drv_romfb.c`) |
| Graphics | LCD | LCD device framework |
| Input | VirtIO Input | Keyboard, mouse, tablet (`-graphic`) |
| Audio | Intel HDA | Default `-sound hda` |
| Audio | VirtIO Sound | `-sound virtio` |
| Crypto | VirtIO Crypto | VirtIO crypto backend |
| Random | VirtIO RNG | Hardware random number |
| Comm | VirtIO Console | Telnet 4321 |
| Comm | RPMSG | VirtIO RPMSG character device |
| Comm | Mailbox PIC | Mailbox interrupt controller |
| Firmware | QEMU FW_CFG | Firmware configuration interface |
| Bus | PCI | ECAM + Generic Host, MSI / MSI-X |
| Other | MFD EDU | Multi-function device |

### 5.2 Not Enabled by Default but Available via menuconfig

This BSP enables the PCI bus and VirtIO PCI transport; QEMU also attaches the corresponding devices. The following drivers are unchecked in the default `.config` but can be used after enabling the Kconfig options and rebuilding (no `qemu.py` changes required):

| Driver / feature | Kconfig | QEMU device | Notes |
| ---------------- | ------- | ----------- | ----- |
| VirtIO Net | `RT_USING_SAL` + `RT_USING_LWIP` + `RT_USING_ETHERNET` | `virtio-net-device` | Network stack not enabled by default |
| VirtIO 9P | `RT_VIRTIO_9P` | `virtio-9p-device` | Use with `-9p` shared directory |
| SDHCI eMMC | `RT_USING_SDIO` + `RT_SDIO_SDHCI_PCI` | `sdhci-pci` | eMMC storage |

> **Note**: Any PCI driver marked `depends on RT_USING_PCI` can be enabled on this BSP via menuconfig. If QEMU does not attach the device by default, add the corresponding `-device` argument in `qemu.py`.

### 5.3 BSP-Specific Features (Driver Layer)

| Feature | Config | Startup |
| ------- | ------ | ------- |
| RAMFB resolution | `RT_GRAPHIC_ROMFB_WIDTH` / `RT_GRAPHIC_ROMFB_HEIGHT` | `-graphic` (`drv_romfb.c` supplies size to RAMFB) |
| Camera driver | `RT_SOC_CAMERA` | `-camera <v4l2-path>`; use `-graphic` for `camera.c` preview |

### 5.4 Sample Applications (`applications/`)

| Source | Build condition | Description |
| ------ | --------------- | ----------- |
| `main.c` | Always | Entry `main()`, prints `hello rt-thread` |
| `amp.c` | `RT_RPMSG_RT_THREAD_VIRTIO` | AMP heterogeneous multi-core and RPMSG demo |
| `camera.c` | `RT_SOC_CAMERA` | Overlay camera feed onto framebuffer |

**`main.c`**

Default application. Prints `hello rt-thread` after boot, then enters msh.

**`amp.c` (AMP + RPMSG)**

QEMU `loader` pre-loads `amp.dtb` and `rtthread.bin` to addresses in `amp.dtsi`; the primary core then boots the slave CPU via the `amp_soc` devicetree node and PSCI. Primary and slave communicate through VirtIO RPMSG and Mailbox. The primary writes VirtIO Block `vdb` resource info into the slave DTB before starting the slave. `qemu.py` increments `-smp` by 1 for the extra CPU.

**Version requirement**: **Smart version** required (`RT_USING_SMART` in menuconfig), plus **`-mem 258`**. The standard kernel must run with virtual addresses equal to physical addresses. The AMP slave is loaded into a separate physical memory region (see `amp_memory`, `kernel-entry` in `amp.dtsi`), which violates that constraint — the standard kernel cannot be used for AMP demos.

Startup:

```
./qemu.py -dtbo amp.dtsi -mem 258
```

Slave console: `telnet localhost 4323`.

msh commands:

| Command | Description |
| ------- | ----------- |
| `rpmsg_write <device> <message>` | Write a message to an RPMSG character device |
| `rpmsg_read <device>` | Read all messages from an RPMSG character device |
| `amp_startup` | Manually trigger AMP slave boot (exported when console and msh are both enabled; otherwise runs automatically at app init) |

An RPMSG endpoint is created automatically at boot (`rpmsg_char0`, endpoint name `rpmsg-char`, addresses 114/514). Addresses are swapped on the slave side.

**`camera.c` (Camera Preview)**

Centers and overlays the vfio-user PCI camera feed onto the framebuffer. Default devices `camera0` → `fb0`, runs for about 10 seconds (300 frames).

Startup (Linux host with libvfio-user and a V4L2 camera):

```
./qemu.py -graphic -camera /dev/video0
```

msh command:

```
camera [camera_device] [framebuffer_device]
```

Example: `camera camera0 fb0`

## 6. Storage and Partitions

- Root filesystem is mounted on the first partition of VirtIO Block `vda0`, filesystem type `elm` (FatFs).
- Storage images are auto-created as 64 MB `qcow2` files on first run; resize with `qemu-img` or replace beforehand.
- pflash0 is used for BootROM (e.g. UEFI); this BSP uses pflash1 (`flash.qcow2`) as CFI NOR. pflash0 data is not preserved after QEMU exits.
- On Linux, partition `qcow2` images with `qemu-nbd` + `fdisk` (not supported on Windows).

## 7. QEMU Monitor Hot-Plug Tips

Dynamically add or remove VirtIO serial ports in the QEMU Monitor:

```
(qemu) chardev-add socket,host=127.0.0.1,port=4323,server=on,wait=off,telnet=on,id=console2
(qemu) device_add virtserialport,chardev=console2,name=org.rt-thread.port,id=port2
(qemu) device_del port2
(qemu) chardev-remove console2
```

Optional VirtIO device arguments (add in `qemu.py` as needed):

- Disable legacy: `-global virtio-mmio.force-legacy=false`
- Virtqueue packed: `-device virtio-XXX-device,packed=on`
- PCI mode (≥ 1.0): `-device virtio-XXX-pci,disable-legacy=on`

## 8. Notes After Configuration Changes

- After changing CPU count, rebuild so `RT_CPUS_NR` matches (or override with `qemu.py -smp`). In `-dtbo` mode, `qemu.py` adds 1 to the CPU count automatically.
- GIC auto-switches to v3 when exceeding 8 cores; or specify `-gic 3` manually. `gic-version=max` is set only internally when using `-el 2` with GICv3.
- 9P directory sharing requires QEMU built with virtfs (`--enable-virtfs`).
- `-gl` requires QEMU built with OpenGL / VirGL (`--enable-opengl`, `--enable-virglrenderer`); this is independent of RT-Thread OpenGL support — the default software stack is 2D graphics only.
- AMP (`-dtbo`) requires Smart kernel (`RT_USING_SMART`), `-mem 258`, and auto-increments CPU count; the standard kernel requires VA=PA and cannot be used with slave images loaded at fixed physical addresses.
- `-camera` requires a host V4L2 device path, Linux, and libvfio-user; your user must have read access to the device (typically via the `video` group); `-graphic` is needed only for the `camera.c` framebuffer preview demo.
- Override root device or boot parameters via `-bootargs`.
