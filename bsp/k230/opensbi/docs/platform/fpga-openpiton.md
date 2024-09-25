OpenPiton FPGA SoC Platform
========================
OpenPiton is the world's first open source, general purpose, multithreaded
manycore processor. It is a tiled manycore framework scalable from one to
1/2 billion cores. Currently, OpenPiton supports the 64bit Ariane RISC-V
processor from ETH Zurich. To this end, Ariane has been equipped with a
different L1 cache subsystem that follows a write-through protocol and that has
support for cache invalidations and atomics.

To build platform specific library and firmwares, provide the
*PLATFORM=fpga/openpiton* parameter to the top level `make` command.

Platform Options
----------------

The *OpenPiton* platform does not have any platform-specific options.

Building Ariane FPGA Platform
-----------------------------

**Linux Kernel Payload**

```
make PLATFORM=fpga/openpiton FW_PAYLOAD_PATH=<linux_build_directory>/arch/riscv/boot/Image
```

Booting Ariane FPGA Platform
----------------------------

**Linux Kernel Payload**

As Linux kernel image is embedded in the OpenSBI firmware binary, Ariane will
directly boot into Linux directly after powered on.
