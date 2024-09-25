Ariane FPGA SoC Platform
========================
Ariane is a 6-stage, single issue, in-order CPU which implements the 64-bit
RISC-V instruction set. The Ariane FPGA development platform is based on FPGA
SoC (which currently supports only Genesys 2 board) and is capable of running
Linux.

The FPGA SoC currently contains the following peripherals:
- DDR3 memory controller
- SPI controller to conncet to an SDCard
- Ethernet controller
- JTAG port (see debugging section below)
- Bootrom containing zero stage bootloader and device tree.

To build platform specific library and firmwares, provide the
*PLATFORM=fpga/ariane* parameter to the top level `make` command.

Platform Options
----------------

The *Ariane FPGA* platform does not have any platform-specific options.

Building Ariane FPGA Platform
-----------------------------

**Linux Kernel Payload**

```
make PLATFORM=fpga/ariane FW_PAYLOAD_PATH=<linux_build_directory>/arch/riscv/boot/Image
```

Booting Ariane FPGA Platform
----------------------------

**Linux Kernel Payload**

As Linux kernel image is embedded in the OpenSBI firmware binary, Ariane will
directly boot into Linux directly after powered on.
