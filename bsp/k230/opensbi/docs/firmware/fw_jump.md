OpenSBI Firmware with Jump Address (FW_JUMP)
============================================

OpenSBI **firmware with Jump Address (FW_JUMP)** is a firmware which only
handles the address of the next booting stage entry, e.g. a bootloader or an OS
kernel, without directly including the binary code for this next stage.

A *FW_JUMP* firmware is particularly useful when the booting stage executed
prior to the OpenSBI firmware is capable of loading both the OpenSBI firmware
and the booting stage binary to follow the OpenSBI firmware.

*FW_JUMP* Compilation
---------------------

A platform *FW_JUMP* firmware can be enabled by any of the following methods:

1. Specifying `FW_JUMP=y` on the top level `make` command line.
2. Specifying `FW_JUMP=y` in the target platform *config.mk* configuration file.

The compiled *FW_JUMP* firmware ELF file is named *fw_jump.elf*. Its expanded
image file is *fw_jump.bin*. Both files are created in the platform-specific
build directory under the *build/platform/<platform_subdir>/firmware* directory.

*FW_JUMP* Firmware Configuration Options
----------------------------------------

To operate correctly, a *FW_JUMP* firmware requires some configuration
parameters to be defined using either the top level `make` command line or the
target platform *config.mk* configuration file. The possible parameters are as
follows:

* **FW_JUMP_ADDR** - Address of the entry point of the booting stage to be
  executed following OpenSBI firmware. This address generally corresponds
  exactly to the address where this next booting stage was loaded. This is a
  mandatory parameter. Compilation errors will result from not defining this
  address.

* **FW_JUMP_FDT_ADDR** - Address where the *flattened device tree (FDT file)*
  passed by the prior booting stage will be placed in memory before executing
  the booting stage following the OpenSBI firmware. If this option is not
  provided, then the OpenSBI firmware will pass the FDT address passed by the
  previous booting stage to the next booting stage.

*FW_JUMP* Example
-----------------

The *[qemu/virt]* platform illustrates how to configure and use a *FW_JUMP*
firmware. Detailed information regarding these platforms can be found in the
platform documentation files.

[qemu/virt]: ../platform/qemu_virt.md
