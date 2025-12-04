# VirtIO Driver for RT-Thread

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

```
RT-Thread Components → Device Drivers → Using VirtIO device drivers
```

- `RT_USING_VIRTIO_BLK`: VirtIO block device support
- `RT_USING_VIRTIO_NET`: VirtIO network device support
- `RT_USING_VIRTIO_CONSOLE`: VirtIO console device support
- `RT_USING_VIRTIO_GPU`: VirtIO GPU device support
- `RT_USING_VIRTIO_INPUT`: VirtIO input device support

## Key Differences Between Legacy and Modern VirtIO

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
- Config generation field for atomic configuration reads

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

- [VirtIO Specification v1.0](https://docs.oasis-open.org/virtio/virtio/v1.0/virtio-v1.0.html)
- [VirtIO Specification v1.1](https://docs.oasis-open.org/virtio/virtio/v1.1/virtio-v1.1.html)
- [VirtIO Specification v1.2](https://docs.oasis-open.org/virtio/virtio/v1.2/virtio-v1.2.html)

## Implementation Details

### Feature Negotiation

Modern VirtIO uses 64-bit feature negotiation:
- Device exposes features via `device_features` register (selected by `device_features_sel`)
- Driver acknowledges features via `driver_features` register (selected by `driver_features_sel`)
- For modern devices, the driver must negotiate `VIRTIO_F_VERSION_1` (feature bit 32)

### Queue Initialization

**Legacy VirtIO:**
- Uses single `queue_pfn` register pointing to the start of the queue area
- Guest page size configured via `guest_page_size`

**Modern VirtIO:**
- Uses separate registers for descriptor, driver (avail), and device (used) areas:
  - `queue_desc_low`/`queue_desc_high`: Descriptor table address
  - `queue_driver_low`/`queue_driver_high`: Available ring address
  - `queue_device_low`/`queue_device_high`: Used ring address
- Queue activated via `queue_ready` register

### Status Flow

**Modern VirtIO adds FEATURES_OK check:**
1. Reset device (status = 0)
2. Set ACKNOWLEDGE and DRIVER status bits
3. Read and negotiate features
4. Write negotiated features to device
5. Set FEATURES_OK status bit
6. Re-read status to verify FEATURES_OK (device may reject features)
7. If accepted, proceed with queue setup and set DRIVER_OK

## Troubleshooting

### Device Not Detected

Check that:
1. QEMU is configured with VirtIO devices
2. The VirtIO version matches your QEMU configuration
3. The device memory region is correctly mapped

### Build Errors

Ensure:
1. The Kconfig is properly configured
2. All VirtIO header files are included
3. The BSP supports VirtIO (check `BSP_USING_VIRTIO`)

### Runtime Issues

Debug tips:
1. Check device version in MMIO config
2. Verify feature negotiation succeeded
3. Check queue initialization (descriptor, avail, used ring addresses)
4. Monitor interrupt status and acknowledgment

## Contributing

When adding new VirtIO devices or features:
1. Support both legacy and modern versions
2. Use the helper functions for feature negotiation (`virtio_get_features`, `virtio_set_features`)
3. Use version checking (`dev->version`) for version-specific code
4. Test on both legacy and modern QEMU configurations

## License

Apache-2.0
