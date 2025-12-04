# VirtIO Specification References

## Official VirtIO Specifications

### Latest Version (v1.2)
**VirtIO 1.2 Specification** (2022-07-14)
- **Official Link**: https://docs.oasis-open.org/virtio/virtio/v1.2/virtio-v1.2.html
- **PDF**: https://docs.oasis-open.org/virtio/virtio/v1.2/csd01/virtio-v1.2-csd01.pdf
- **Status**: OASIS Committee Specification Draft 01
- **Key Features**: 
  - All features from v1.1
  - New devices: Audio, File System, PMEM, RPMB, Video Encoder/Decoder, SCMI, GPIO, RDMA
  - Enhanced device specifications
  - Better security and performance features

### VirtIO 1.1 Specification (2019-01-29)
- **Official Link**: https://docs.oasis-open.org/virtio/virtio/v1.1/virtio-v1.1.html
- **PDF**: https://docs.oasis-open.org/virtio/virtio/v1.1/csprd01/virtio-v1.1-csprd01.pdf
- **Status**: OASIS Committee Specification Public Review Draft 01
- **Key Features**:
  - All features from v1.0
  - Packed ring support (VIRTIO_F_RING_PACKED)
  - New devices: Socket, Crypto, Signal Distribution Module, IOMMU, Memory
  - Order-independent feature negotiation

### VirtIO 1.0 Specification (2016-03-08)
- **Official Link**: https://docs.oasis-open.org/virtio/virtio/v1.0/virtio-v1.0.html
- **PDF**: https://docs.oasis-open.org/virtio/virtio/v1.0/cs04/virtio-v1.0-cs04.pdf
- **Status**: OASIS Committee Specification 04
- **Key Features**:
  - Modern interface (version field = 0x2)
  - 64-bit feature negotiation
  - Separate queue descriptor/driver/device areas
  - FEATURES_OK status check
  - Better memory alignment requirements

### Legacy VirtIO (v0.95)
- **Reference**: Part of Linux kernel documentation
- **Link**: https://wiki.libvirt.org/VirtIO.html
- **Status**: Legacy interface (version field = 0x1)
- **Note**: Used by older QEMU versions and some embedded systems

## OASIS VirtIO Technical Committee

- **Website**: https://www.oasis-open.org/committees/virtio/
- **Charter**: Defines standard interfaces for virtual I/O devices
- **Mailing List**: virtio@lists.oasis-open.org
- **Git Repository**: https://github.com/oasis-tcs/virtio-spec

## Implementation in RT-Thread

RT-Thread now supports:
- ✅ **Legacy VirtIO (v0.95)**: Version field 0x1, 32-bit features, legacy queue setup
- ✅ **Modern VirtIO (v1.0+)**: Version field 0x2, 64-bit features, modern queue setup

The implementation follows the VirtIO 1.2 specification for modern devices while maintaining backward compatibility with legacy devices.

## Device-Specific Specifications

### VirtIO Block Device
- **Section**: 5.2 in VirtIO 1.2 spec
- **Features**: Basic block I/O, multiple queues, discard support
- **Status**: Fully implemented in RT-Thread

### VirtIO Network Device  
- **Section**: 5.1 in VirtIO 1.2 spec
- **Features**: Ethernet interface, checksum offload, multiple queues
- **Status**: Fully implemented in RT-Thread

### VirtIO Console Device
- **Section**: 5.3 in VirtIO 1.2 spec
- **Features**: Serial console, multiple ports, control messages
- **Status**: Fully implemented in RT-Thread

### VirtIO GPU Device
- **Section**: 5.7 in VirtIO 1.2 spec
- **Features**: 2D graphics, scanout, resource management
- **Status**: Fully implemented in RT-Thread

### VirtIO Input Device
- **Section**: 5.8 in VirtIO 1.2 spec
- **Features**: Keyboard, mouse, tablet input events
- **Status**: Fully implemented in RT-Thread

## QEMU VirtIO Implementation

### QEMU Documentation
- **VirtIO Devices**: https://qemu.readthedocs.io/en/latest/system/devices/virtio-net.html
- **MMIO Transport**: https://qemu.readthedocs.io/en/latest/specs/virtio-mmio.html

### QEMU Version Requirements
- **Legacy VirtIO**: QEMU 1.0+
- **Modern VirtIO**: QEMU 2.4+ (recommended 2.6+)

### QEMU Command Line Examples

**Legacy Mode:**
```bash
qemu-system-riscv64 -M virt \
  -device virtio-blk-device,disable-modern=on,drive=blk0
```

**Modern Mode:**
```bash
qemu-system-riscv64 -M virt \
  -device virtio-blk-device,disable-legacy=on,drive=blk0
```

**Auto-detect (Default):**
```bash
qemu-system-riscv64 -M virt \
  -device virtio-blk-device,drive=blk0
```

## Feature Bits Reference

### Common Features (Section 6 in VirtIO 1.2 spec)

| Bit | Name | Description |
|-----|------|-------------|
| 24 | VIRTIO_F_NOTIFY_ON_EMPTY | Notify on empty available ring |
| 27 | VIRTIO_F_ANY_LAYOUT | Flexible descriptor layout |
| 28 | VIRTIO_F_RING_INDIRECT_DESC | Indirect descriptors |
| 29 | VIRTIO_F_RING_EVENT_IDX | Event index for notifications |
| 32 | VIRTIO_F_VERSION_1 | Compliance with VirtIO 1.0+ |
| 34 | VIRTIO_F_RING_PACKED | Packed ring layout (1.1+) |

### Device-Specific Features

**Block Device:**
- Bit 0: VIRTIO_BLK_F_BARRIER - Legacy barrier support
- Bit 1: VIRTIO_BLK_F_SIZE_MAX - Maximum segment size
- Bit 2: VIRTIO_BLK_F_SEG_MAX - Maximum segments
- Bit 5: VIRTIO_BLK_F_RO - Read-only device
- Bit 9: VIRTIO_BLK_F_FLUSH - Cache flush support

**Network Device:**
- Bit 0: VIRTIO_NET_F_CSUM - Checksum offload
- Bit 1: VIRTIO_NET_F_GUEST_CSUM - Guest checksum
- Bit 5: VIRTIO_NET_F_MAC - MAC address
- Bit 6: VIRTIO_NET_F_GSO - Generic segmentation offload

## Status Bits Reference

| Bit | Name | Description |
|-----|------|-------------|
| 0 | ACKNOWLEDGE | Driver has found the device |
| 1 | DRIVER | Driver knows how to drive the device |
| 2 | DRIVER_OK | Driver is set up and ready |
| 3 | FEATURES_OK | Feature negotiation complete |
| 6 | NEEDS_RESET | Device experienced unrecoverable error |
| 7 | FAILED | Driver gave up on device |

## Additional Resources

### Linux Kernel VirtIO Implementation
- **Source**: https://github.com/torvalds/linux/tree/master/drivers/virtio
- **Documentation**: https://www.kernel.org/doc/Documentation/virtual/

### KVM/QEMU VirtIO
- **KVM Forum**: https://www.linux-kvm.org/page/Virtio
- **QEMU Wiki**: https://wiki.qemu.org/Features/VirtIO

### Books and Papers
- **"Hardware Virtualization: Platforms and Applications"** - Covers VirtIO design
- **"Virtual Machines: Versatile Platforms for Systems and Processes"** - Chapter on I/O virtualization

## RT-Thread Specific Documentation

- **[README.md](README.md)**: RT-Thread VirtIO usage guide
- **[TESTING.md](TESTING.md)**: Testing procedures for both legacy and modern modes

## Version History

| Date | Version | RT-Thread Support | Notes |
|------|---------|------------------|-------|
| 2022-07-14 | 1.2 | ✅ Yes | Latest specification |
| 2019-01-29 | 1.1 | ✅ Yes | Packed ring support |
| 2016-03-08 | 1.0 | ✅ Yes | Modern interface |
| ~2013 | 0.95 | ✅ Yes | Legacy interface (default) |

## Contact and Support

- **RT-Thread Forum**: https://club.rt-thread.io/
- **GitHub Issues**: https://github.com/RT-Thread/rt-thread/issues
- **VirtIO Mailing List**: virtio@lists.oasis-open.org

## License

VirtIO specifications are licensed under:
- OASIS Open Source License (VirtIO 1.0+)

RT-Thread VirtIO driver is licensed under:
- Apache License 2.0
