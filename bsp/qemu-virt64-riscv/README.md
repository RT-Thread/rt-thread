# QEMU RISC-V virt BSP

English | [中文](README_cn.md)

This BSP runs RT-Thread in S-mode on QEMU's RISC-V `virt` machine. The directory
name is retained for compatibility, while Kconfig supports both RV32 and RV64.
RV64 is the default. RT-Thread Smart remains RV64-only; RV32 currently targets
the standard RT-Thread kernel.

## Build

Install SCons, QEMU RISC-V system emulation, and a RISC-V GCC toolchain. The
toolchain used for RV32 must provide the selected RV32 multilib.

```sh
export RTT_EXEC_PATH=/path/to/toolchain/bin
export RTT_CC_PREFIX=riscv64-unknown-elf-

scons --menuconfig
scons -j$(nproc)
```

Select the XLEN under `RISC-V XLEN`. Configuration regeneration produces
`rtconfig.h`; the build then emits `rtthread.elf` and `rtthread.bin`. The BSP
sets `ARCH_RAM_OFFSET=0x80000000` and uses a 4 MiB RV32 or 2 MiB RV64 image
offset, matching QEMU/OpenSBI's default load addresses without a BSP linker
script.

## Run

```sh
./qemu.py
```

Both XLEN configurations enable user-mode networking and one virtio block disk
by default. RV64 additionally defaults to AIA (APLIC/IMSIC), NVMe,
virtio-console, and PCI serial. RV32 defaults to PLIC/ACLINT and legacy
virtio-mmio; NVMe and the additional consoles are not attached by default.
Missing qcow2 images are created automatically. Storage emulation is
intentionally limited to virtio block and NVMe.

With QEMU 10.1 and OpenSBI 1.5.1, RV32 S-mode AIA reaches IMSIC setup but traps
when accessing `siselect/sireg`. The `-aia` option remains available for testing
newer emulator and firmware combinations, but it is not the RV32 default.

Useful options:

```sh
./qemu.py -no-aia
./qemu.py -no-net -no-nvme
./qemu.py -nvme -virtio-console -pci-serial
./qemu.py -pci
./qemu.py -graphic
./qemu.py -dumpdtb qemu-virt.dtb
./qemu.py -dry-run
```

The QEMU CPU count must match `RT_CPUS_NR` in the kernel configuration. Change
`RT_CPUS_NR` and rebuild before changing `-smp`; the script rejects a mismatch
because the kernel does not currently maintain a separate online-CPU mask.

When `ARCH_RISCV_VECTOR` is enabled, the script reads the selected VLEN from
`rtconfig.h` and configures QEMU accordingly. `-v` can force the default
128-bit vector configuration for a kernel built without that option.

## Debug

Start QEMU paused and attach GDB:

```sh
./qemu.py -debug
riscv64-linux-gnu-gdb rtthread.elf -ex "target remote :1234"
```

Use a GDB matching the configured XLEN and toolchain when building RV32.
