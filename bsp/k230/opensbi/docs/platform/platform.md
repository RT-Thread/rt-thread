OpenSBI Supported Platforms
===========================

OpenSBI currently supports the following virtual and hardware platforms:

* **Generic**: Flattened device tree (FDT) based platform where platform
  specific functionality is provided based on the FDT passed by previous
  booting stage. More details on this platform can be found in the file
  *[generic.md]*.

* **QEMU RISC-V Virt Machine**: Platform support for the QEMU *virt* virtual
  RISC-V machine. This virtual machine is intended for RISC-V software
  development and tests. More details on this platform can be found in the
  file *[qemu_virt.md]*.

* **SiFive FU540 SoC**: Platform support for SiFive FU540 SoC used on the
  HiFive Unleashed board, as well as the *sifive_u* QEMU virtual RISC-V
  machine. More details on this platform can be found in the file
  *[sifive_fu540.md]*.

* **Kendryte K210 SoC**: Platform support for the Kendryte K210 SoC used on
  boards such as the Kendryte KD233 or the Sipeed MAIX Dock.

* **Ariane FPGA SoC**: Platform support for the Ariane FPGA SoC used on
  Genesys 2 board. More details on this platform can be found in the file
  *[fpga-ariane.md]*.

* **Andes AE350 SoC**: Platform support for the Andes's SoC (AE350). More
  details on this platform can be found in the file *[andes-ae350.md]*.

* **Spike**: Platform support for the Spike emulator. More
  details on this platform can be found in the file *[spike.md]*.

* **OpenPiton FPGA SoC**: Platform support OpenPiton research platform based
  on ariane core. More details on this platform can be found in the file
  *[fpga-openpiton.md]*.

* **Shakti C-class SoC Platform**: Platform support for Shakti C-class
  processor based SOCs. More details on this platform can be found in the
  file *[shakti_cclass.md]*.

The code for these supported platforms can be used as example to implement
support for other platforms. The *platform/template* directory also provides
template files for implementing support for a new platform. The *object.mk*,
*config.mk* and *platform.c* template files provides enough comments to
facilitate the implementation.

[generic.md]: generic.md
[qemu_virt.md]: qemu_virt.md
[sifive_fu540.md]: sifive_fu540.md
[fpga-ariane.md]: fpga-ariane.md
[andes-ae350.md]: andes-ae350.md
[thead-c910.md]: thead-c910.md
[spike.md]: spike.md
[fpga-openpiton.md]: fpga-openpiton.md
[shakti_cclass.md]: shakti_cclass.md
