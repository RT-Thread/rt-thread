OpenSBI Firmware with Dynamic Information (FW_DYNAMIC)
======================================================

OpenSBI **firmware with dynamic info (FW_DYNAMIC)** is a firmware which gets
information about next booting stage (e.g. a bootloader or an OS) and runtime
OpenSBI library options from previous booting stage.

The previous booting stage will pass information to *FW_DYNAMIC* by creating
*struct fw_dynamic_info* in memory and passing it's address to *FW_DYNAMIC*
via *a2* register of RISC-V CPU.

A *FW_DYNAMIC* firmware is particularly useful when the booting stage executed
prior to OpenSBI firmware is capable of loading both the OpenSBI firmware and
the booting stage binary to follow OpenSBI firmware.

*FW_DYNAMIC* Compilation
------------------------

A platform can enable *FW_DYNAMIC* firmware using any of the following methods.

1. Specifying `FW_DYNAMIC=y` on the top level `make` command line.
2. Specifying `FW_DYNAMIC=y` in the target platform *config.mk* configuration
file.

The compiled *FW_DYNAMIC* firmware ELF file is named *fw_dynamic.elf*. It's
expanded image file is *fw_dynamic.bin*. Both files are created in the platform
specific build directory under the *build/platform/<platform_subdir>/firmware*
directory.

*FW_DYNAMIC* Firmware Configuration Options
-------------------------------------------

The *FW_DYNAMIC* firmware does not requires any platform specific configuration
parameters because all required information is passed by previous booting stage
at runtime via *struct fw_dynamic_info*.
