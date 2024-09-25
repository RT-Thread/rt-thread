Andes AE350 SoC Platform
========================
The AE350 AXI/AHB-based platform N25(F)/NX25(F)/D25F/A25/AX25 CPU with level-one
memories,interrupt controller, debug module, AXI and AHB Bus Matrix Controller,
AXI-to-AHB Bridge and a collection of fundamentalAHB/APB bus IP components
pre-integrated together as a system design.The high-quality and configurable
AHB/APB IPs suites a majority embedded systems, and the verified platform serves
as a starting point to jump start SoC designs.

To build platform specific library and firmwares, provide the
*PLATFORM=andes/ae350* parameter to the top level make command.

Platform Options
----------------

The Andes AE350 platform does not have any platform-specific options.

Building Andes AE350 Platform
-----------------------------

To use Linux v5.2 should be used to build Andes AE350 OpenSBI binaries by using
the compile time option FW_FDT_PATH.

AE350's dts is included in https://github.com/andestech/linux/tree/ast-v3_2_0-release-public

**Linux Kernel Payload**

```
make PLATFORM=andes/ae350 FW_PAYLOAD_PATH=<linux_build_directory>/arch/riscv/boot/Image FW_FDT_PATH=<ae350.dtb path>
```
