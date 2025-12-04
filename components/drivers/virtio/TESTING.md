# VirtIO Testing Guide

This guide helps you test VirtIO support on RT-Thread with both legacy and modern versions.

## Prerequisites

- QEMU installed (version 2.4+ for modern VirtIO support)
- RT-Thread build environment
- RISC-V or AArch64 toolchain

## Testing Legacy VirtIO (v0.95)

### 1. Configure RT-Thread

```bash
cd bsp/qemu-virt64-riscv
scons --menuconfig
```

Navigate to:
```
RT-Thread Components → Device Drivers → Using VirtIO device drivers → VirtIO Version
→ Select "VirtIO Legacy (v0.95)" or "VirtIO Legacy (v1.0 - alias for compatibility)"
```

### 2. Build

```bash
scons
```

### 3. Run with QEMU (Legacy Mode)

Force QEMU to use legacy VirtIO:

```bash
qemu-system-riscv64 \
  -M virt \
  -kernel rtthread.bin \
  -nographic \
  -device virtio-blk-device,disable-modern=on,drive=blk0 \
  -drive if=none,id=blk0,file=sd.bin \
  -device virtio-net-device,disable-modern=on,netdev=net0 \
  -netdev user,id=net0
```

### 4. Verify

Check that VirtIO devices are detected:
```
msh /> list_device
device         type         ref count
------ -------------------- ----------
virtio-blk0    Block Device      0
virtio-net0    Network Interface 0
```

## Testing Modern VirtIO (v1.0+)

### 1. Configure RT-Thread

```bash
cd bsp/qemu-virt64-riscv
scons --menuconfig
```

Navigate to:
```
RT-Thread Components → Device Drivers → Using VirtIO device drivers → VirtIO Version
→ Select "VirtIO Modern (v1.0+)"
```

### 2. Build

```bash
scons
```

### 3. Run with QEMU (Modern Mode)

Use default QEMU settings (modern VirtIO):

```bash
qemu-system-riscv64 \
  -M virt \
  -kernel rtthread.bin \
  -nographic \
  -device virtio-blk-device,drive=blk0 \
  -drive if=none,id=blk0,file=sd.bin \
  -device virtio-net-device,netdev=net0 \
  -netdev user,id=net0
```

Or explicitly enable modern mode:

```bash
qemu-system-riscv64 \
  -M virt \
  -kernel rtthread.bin \
  -nographic \
  -device virtio-blk-device,disable-legacy=on,drive=blk0 \
  -drive if=none,id=blk0,file=sd.bin \
  -device virtio-net-device,disable-legacy=on,netdev=net0 \
  -netdev user,id=net0
```

### 4. Verify

Check that VirtIO devices are detected:
```
msh /> list_device
device         type         ref count
------ -------------------- ----------
virtio-blk0    Block Device      0
virtio-net0    Network Interface 0
```

## Testing Auto-Detection (Recommended)

The driver can auto-detect the VirtIO version. To test this:

### 1. Build with Default Settings

Use the existing configuration (legacy by default):
```bash
cd bsp/qemu-virt64-riscv
scons
```

### 2. Test with Both QEMU Modes

**Test 1: Legacy QEMU**
```bash
qemu-system-riscv64 -M virt -kernel rtthread.bin -nographic \
  -device virtio-blk-device,disable-modern=on,drive=blk0 \
  -drive if=none,id=blk0,file=sd.bin
```

**Test 2: Modern QEMU**
```bash
qemu-system-riscv64 -M virt -kernel rtthread.bin -nographic \
  -device virtio-blk-device,drive=blk0 \
  -drive if=none,id=blk0,file=sd.bin
```

Both should work because the driver detects the version from the MMIO config.

## Testing Individual Devices

### VirtIO Block Device

```bash
# Create a test disk image
dd if=/dev/zero of=sd.bin bs=1M count=32

# Run QEMU with block device
qemu-system-riscv64 -M virt -kernel rtthread.bin -nographic \
  -device virtio-blk-device,drive=blk0 \
  -drive if=none,id=blk0,file=sd.bin

# In RT-Thread shell
msh /> mkfs -t elm virtio-blk0
msh /> mount virtio-blk0 / elm
```

### VirtIO Network Device

```bash
# Run QEMU with network device
qemu-system-riscv64 -M virt -kernel rtthread.bin -nographic \
  -device virtio-net-device,netdev=net0 \
  -netdev user,id=net0,hostfwd=tcp::5555-:23

# In RT-Thread shell
msh /> ifconfig
```

### VirtIO Console

```bash
# Run QEMU with console device
qemu-system-riscv64 -M virt -kernel rtthread.bin -nographic \
  -device virtio-serial-device \
  -chardev stdio,id=console0 \
  -device virtconsole,chardev=console0

# Check for virtio-console devices
msh /> list_device
```

### VirtIO GPU

```bash
# Run QEMU with GPU device (requires display)
qemu-system-riscv64 -M virt -kernel rtthread.bin \
  -device virtio-gpu-device \
  -serial stdio

# Or with VNC
qemu-system-riscv64 -M virt -kernel rtthread.bin -nographic \
  -device virtio-gpu-device \
  -vnc :0
```

### VirtIO Input (Keyboard/Mouse)

```bash
# Run QEMU with input devices
qemu-system-riscv64 -M virt -kernel rtthread.bin \
  -device virtio-keyboard-device \
  -device virtio-mouse-device \
  -device virtio-tablet-device

# Check for input devices
msh /> list_device
```

## Debugging

### Enable Debug Output

Add debug prints to check version detection:

```c
// In your application or driver init
rt_kprintf("VirtIO version: %d\n", virtio_dev->version);
rt_kprintf("VirtIO magic: 0x%x\n", virtio_dev->mmio_config->magic);
rt_kprintf("VirtIO device_id: %d\n", virtio_dev->mmio_config->device_id);
```

### Check QEMU Version

```bash
qemu-system-riscv64 --version
```

Modern VirtIO requires QEMU 2.4+.

### Check Feature Negotiation

Add debug output in `virtio_get_features` and `virtio_set_features` to verify feature negotiation.

## Expected Results

### Legacy Mode (Version 1)
- `dev->version == 1`
- Features are 32-bit
- Queue uses `queue_pfn` register
- No FEATURES_OK check

### Modern Mode (Version 2)
- `dev->version == 2`
- Features are 64-bit
- Queue uses separate desc/driver/device registers
- FEATURES_OK status check performed
- VERSION_1 feature negotiated

## Common Issues

### Issue: Device not detected
**Solution**: Check QEMU device configuration and memory mapping

### Issue: Feature negotiation fails
**Solution**: Verify QEMU supports the features you're requesting

### Issue: Queue initialization fails
**Solution**: Check memory alignment and addresses

### Issue: Build errors
**Solution**: Ensure Kconfig is properly configured and rtconfig.h is generated

## Performance Testing

### Block Device Performance

```bash
# In RT-Thread shell (with filesystem mounted)
msh /> dd if=/dev/zero of=/test.bin bs=4096 count=1000
```

### Network Performance

```bash
# Use iperf or similar tools
# Configure network and run throughput tests
```

## Reporting Issues

When reporting issues, include:
1. QEMU version
2. RT-Thread configuration (legacy/modern)
3. QEMU command line
4. Error messages or unexpected behavior
5. Debug output (if enabled)

## Reference

- [QEMU VirtIO Documentation](https://wiki.qemu.org/Features/VirtIO)
- [VirtIO Specification](https://docs.oasis-open.org/virtio/virtio/v1.2/virtio-v1.2.html)
- [RT-Thread VirtIO README](README.md)
