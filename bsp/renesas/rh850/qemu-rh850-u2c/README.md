# QEMU RH850/U2C BSP

## Introduction

This BSP runs RT-Thread on the Renesas RH850/U2C8 (R7F702600, G4KH core) as
modelled by the QEMU machine `rh850-u2c`. It is the first RH850 BSP; the CPU
port is in `libcpu/rh850`, and the parts shared by RH850 BSPs are in
`bsp/renesas/rh850/libraries`.

The QEMU machine and the toolchain are available as prebuilt Linux x86_64
releases:

- QEMU: https://github.com/linumiz/qemu-rh850/releases (v1.0.0)
- GCC 14.3.0 for v850-elf with picolibc:
  https://github.com/linumiz/rh850-gcc-toolchain/releases

## Supported Features

| Feature | Notes |
|---------|-------|
| CPU | G4KH (PE0 only), hard float (default) or soft float (RT_USING_FPU off) |
| Interrupts | INTC1/INTC2, 16 priorities, nested, switch at the outermost exit |
| Tick | OSTM0, interval mode, RT_TICK_PER_SECOND |
| Console | RLIN311 UART, serial device "rlin311", interrupt-driven receive |
| Memory | code flash 8 MB, PE0 local RAM 128 KB, heap in cluster RAM (1248 KB) |
| Idle | HALT in the idle hook |
| Faults | register dump of FE/EI exceptions, rt_hw_exception_install |

## Build

Install the toolchain, then build with scons:

```
export RTT_EXEC_PATH=/opt/v850-elf/bin
cd bsp/renesas/rh850/qemu-rh850-u2c
scons -j8
```

Use `scons --menuconfig` to change the configuration.

## Run on QEMU

```
qemu-system-rh850 -M rh850-u2c -nographic -kernel rtthread.elf
```

The console shows the RT-Thread logo and the `msh />` prompt. Exit QEMU with
`Ctrl-A X`.

## References

- RH850/U2C User's Manual: Hardware, R01UH1018EJ0100
- RH850G4KH User's Manual: Software, R01US0598EJ0100
