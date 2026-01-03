# VirtIO Driver for RT-Thread

[中文](README_zh.md) | English

## Overview

The VirtIO driver provides support for virtual I/O devices in RT-Thread, primarily used in virtualized environments like QEMU.

## Supported Versions

The driver now supports both legacy and modern VirtIO specifications:

- **Legacy VirtIO (v0.95)**: Version field 0x1, compatible with older QEMU versions
- **Modern VirtIO (v1.0+)**: Version field 0x2, supports VirtIO 1.0, 1.1, and 1.2 specifications

## Supported Devices

- **VirtIO Block (virtio-blk)**: Virtual block device
- **VirtIO Network (virtio-net)**: Virtual network interface
- **VirtIO Console (virtio-console)**: Virtual serial console
- **VirtIO GPU (virtio-gpu)**: Virtual graphics device
- **VirtIO Input (virtio-input)**: Virtual input device (keyboard, mouse, tablet)

## Configuration

Use `menuconfig` to configure VirtIO support:

```
RT-Thread Components → Device Drivers → Using VirtIO device drivers
```

### Version Selection

Choose between legacy and modern VirtIO:

```
RT-Thread Components → Device Drivers → Using VirtIO device drivers → VirtIO Version
```

Options:
- **VirtIO Legacy (v0.95)**: For compatibility with older QEMU versions (default)
- **VirtIO Modern (v1.0+)**: For newer QEMU versions (2.4+) with enhanced features

### Device Selection

Enable individual VirtIO devices:

- `RT_USING_VIRTIO_BLK`: VirtIO block device support
- `RT_USING_VIRTIO_NET`: VirtIO network device support
- `RT_USING_VIRTIO_CONSOLE`: VirtIO console device support
- `RT_USING_VIRTIO_GPU`: VirtIO GPU device support
- `RT_USING_VIRTIO_INPUT`: VirtIO input device support

## Key Differences

### Legacy VirtIO (v0.95)
- 32-bit feature negotiation
- Single queue descriptor area
- Simple status flags
- Guest page size configuration

### Modern VirtIO (v1.0+)
- 64-bit feature negotiation (supports more features)
- Separate descriptor/driver/device queue areas
- Enhanced status flow with FEATURES_OK check
- Better memory alignment and atomicity guarantees

## Migration Guide

### From Legacy to Modern

1. Update your QEMU command line to use modern VirtIO devices (most recent QEMU versions default to modern)
2. Change the VirtIO version in menuconfig:
   ```
   RT-Thread Components → Device Drivers → Using VirtIO device drivers → VirtIO Version
   → Select "VirtIO Modern (v1.0+)"
   ```
3. Rebuild your application
4. The driver will automatically negotiate the VERSION_1 feature with the device

### Backward Compatibility

The driver automatically detects the device version from the MMIO config and adapts its behavior accordingly. Both legacy (version 0x1) and modern (version 0x2) devices are supported in the same build.

## BSP Support

The following BSPs have been updated to support both legacy and modern VirtIO:

- `qemu-virt64-riscv`: QEMU RISC-V 64-bit
- `qemu-virt64-aarch64`: QEMU ARM64 (AArch64)

## Reference Specifications

- [VirtIO Specification v1.2](https://docs.oasis-open.org/virtio/virtio/v1.2/virtio-v1.2.html) (Latest, 2022)
- [VirtIO Specification v1.1](https://docs.oasis-open.org/virtio/virtio/v1.1/virtio-v1.1.html) (2019)
- [VirtIO Specification v1.0](https://docs.oasis-open.org/virtio/virtio/v1.0/virtio-v1.0.html) (2016)
- [OASIS VirtIO TC](https://www.oasis-open.org/committees/virtio/)

## License

Apache-2.0
