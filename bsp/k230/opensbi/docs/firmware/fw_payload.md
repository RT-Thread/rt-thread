OpenSBI Firmware with Payload (FW_PAYLOAD)
==========================================

OpenSBI **firmware with Payload (FW_PAYLOAD)** is a firmware which directly
includes the binary for the booting stage to follow the OpenSBI firmware
execution. Typically, this payload will be a bootloader or an OS kernel.

A *FW_PAYLOAD* firmware is particularly useful when the booting stage executed
prior to the OpenSBI firmware is not capable of loading both the OpenSBI
firmware and the booting stage to follow OpenSBI firmware.

A *FW_PAYLOAD* firmware is also useful for cases where the booting stage prior
to the OpenSBI firmware does not pass a *flattened device tree (FDT file)*. In
such a case, a *FW_PAYLOAD* firmware allows embedding a flattened device tree
in the .text section of the final firmware.

Enabling *FW_PAYLOAD* compilation
---------------------------------

The *FW_PAYLOAD* firmware can be enabled by any of the following methods:

1. Specifying `FW_PAYLOAD=y` on the top level `make` command line.
2. Specifying `FW_PAYLOAD=y` in the target platform *config.mk* configuration
   file.

The compiled *FW_PAYLOAD* firmware ELF file is named *fw_jump.elf*. Its
expanded image file is *fw_payload.bin*. Both files are created in the
platform-specific build directory under the
*build/platform/<platform_subdir>/firmware* directory.

Configuration Options
---------------------

A *FW_PAYLOAD* firmware is built according to configuration parameters and
options. These configuration parameters can be defined using either the top
level `make` command line or the target platform *config.mk* configuration
file. The parameters currently defined are as follows:

* **FW_PAYLOAD_OFFSET** - Offset from *FW_TEXT_BASE* where the payload binary
  will be linked in the final *FW_PAYLOAD* firmware binary image. This
  configuration parameter is mandatory if *FW_PAYLOAD_ALIGN* is not defined.
  Compilation errors will result from an incorrect definition of
  *FW_PAYLOAD_OFFSET* or of *FW_PAYLOAD_ALIGN*, or if neither of these
  parameters are defined.

* **FW_PAYLOAD_ALIGN** - Address alignment constraint where the payload binary
  will be linked after the end of the base firmware binary in the final
  *FW_PAYLOAD* firmware binary image. This configuration parameter is mandatory
  if *FW_PAYLOAD_OFFSET* is not defined. If both *FW_PAYLOAD_OFFSET* and
  *FW_PAYLOAD_ALIGN* are defined, *FW_PAYLOAD_OFFSET* is used and
  *FW_PAYLOAD_ALIGN* is ignored.

* **FW_PAYLOAD_PATH** - Path to the image file of the next booting stage
  binary.  If this option is not provided then a simple test payload is
  automatically generated and used as a payload. This test payload executes
  an infinite `while (1)` loop after printing a message on the platform console.

* **FW_PAYLOAD_FDT_ADDR** - Address where the FDT passed by the prior booting
  stage or specified by the *FW_FDT_PATH* parameter and embedded in the
  *.rodata* section will be placed before executing the next booting stage,
  that is, the payload firmware. If this option is not provided, then the
  firmware will pass the FDT address passed by the previous booting stage
  to the next booting stage.

*FW_PAYLOAD* Example
--------------------

The *[qemu/virt]* platforms illustrate how to configure and use a *FW_PAYLOAD*
firmware. Detailed information regarding these platforms can be found in the
platform documentation files.

[qemu/virt]: ../platform/qemu_virt.md
