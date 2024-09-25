OpenSBI Platform Firmwares
==========================

OpenSBI provides firmware builds for specific platforms. Different types of
firmwares are supported to deal with the differences between different platforms
early boot stage. All firmwares will execute the same initialization procedure
of the platform hardware according to the platform specific code as well as
OpenSBI generic library code. The supported firmwares type will differ in how
the arguments passed by the platform early boot stage are handled, as well as
how the boot stage following the firmware will be handled and executed.

OpenSBI currently supports three different types of firmwares.

Firmware with Dynamic Information (*FW_DYNAMIC*)
------------------------------------------------

The *FW_DYNAMIC* firmware gets information about the next booting stage entry,
e.g. a bootloader or an OS kernel, from previous booting stage at runtime.

A *FW_DYNAMIC* firmware is particularly useful when the booting stage executed
prior to OpenSBI firmware is capable of loading both the OpenSBI firmware
and the booting stage binary to follow OpenSBI firmware.

Firmware with Jump Address (*FW_JUMP*)
--------------------------------------

The *FW_JUMP* firmware assumes a fixed address of the next booting stage
entry, e.g. a bootloader or an OS kernel, without directly including the
binary code for this next stage.

A *FW_JUMP* firmware is particularly useful when the booting stage executed
prior to OpenSBI firmware is capable of loading both the OpenSBI firmware
and the booting stage binary to follow OpenSBI firmware.

Firmware with Payload (*FW_PAYLOAD*)
------------------------------------

The *FW_PAYLOAD* firmware directly includes the binary code for the booting
stage to follow OpenSBI firmware execution. Typically, this payload will be a
bootloader or an OS kernel.

A *FW_PAYLOAD* firmware is particularly useful when the booting stage executed
prior to OpenSBI firmware is not capable of loading both OpenSBI firmware and
the booting stage to follow OpenSBI firmware.

A *FW_PAYLOAD* firmware is also useful for cases where the booting stage prior
to OpenSBI firmware does not pass a *flattened device tree (FDT file)*. In such
case, a *FW_PAYLOAD* firmware allows embedding a flattened device tree in the
.text section of the final firmware.

Firmware Configuration and Compilation
--------------------------------------

All firmware types support the following common compile time configuration
parameters:

* **FW_TEXT_ADDR** - Defines the execution address of the OpenSBI firmware.
  This configuration parameter is mandatory.
* **FW_FDT_PATH** - Path to an external flattened device tree binary file to
  be embedded in the *.rodata* section of the final firmware. If this option
  is not provided then the firmware will expect the FDT to be passed as an
  argument by the prior booting stage.
* **FW_FDT_PADDING** - Optional zero bytes padding to the embedded flattened
  device tree binary file specified by **FW_FDT_PATH** option.

Additionally, each firmware type as a set of type specific configuration
parameters. Detailed information for each firmware type can be found in the
following documents.

* *[FW_DYNAMIC]*: The *Firmware with Dynamic Information (FW_DYNAMIC)* is
  described in more details in the file *fw_dynamic.md*.
* *[FW_JUMP]*: The *Firmware with Jump Address (FW_JUMP)* is described in more
  details in the file *fw_jump.md*.
* *[FW_PAYLOAD]*: The *Firmware with Payload (FW_PAYLOAD)* is described in more
  details in the file *fw_payload.md*.

[FW_DYNAMIC]: fw_dynamic.md
[FW_JUMP]: fw_jump.md
[FW_PAYLOAD]: fw_payload.md

Providing different payloads to OpenSBI Firmware
------------------------------------------------
OpenSBI firmware can accept various payloads using a compile time option.
Typically, these payloads refer to the next stage boot loader (e.g. U-Boot)
or operating system kernel images (e.g. Linux). By default, OpenSBI
automatically provides a test payload if no specific payload is specified
at compile time.

To specify a payload at compile time, the make variable _FW_PAYLOAD_PATH_ is
used.
```
make PLATFORM=<platform_subdir> FW_PAYLOAD_PATH=<payload path>
```
The instructions to build each payload is different and the details can
be found in the
*docs/firmware/payload_<payload_name>.md* files.

Options for OpenSBI Firmware behaviors
--------------------------------------
An optional compile time flag FW_OPTIONS can be used to control the OpenSBI
firmware run-time behaviors.

```
make PLATFORM=<platform_subdir> FW_OPTIONS=<options>
```

FW_OPTIONS is a bitwise or'ed value of various options, eg: *FW_OPTIONS=0x1*
stands for disabling boot prints from the OpenSBI library.

For all supported options, please check "enum sbi_scratch_options" in the
*include/sbi/sbi_scratch.h* header file.
