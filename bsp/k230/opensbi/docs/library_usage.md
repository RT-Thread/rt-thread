OpenSBI Library Usage
=====================

OpenSBI provides two types of static libraries:

1. *libsbi.a* - A platform-independent generic static library implementing the
   interface defined by the SBI specifications. Platform-specific processing
   hooks for the execution of this interface must be provided by the firmware or
   bootloader linking with this library. This library is installed as
   *<install_directory>/lib/libsbi.a*
2. *libsbiutils.a* - A static library that will contain all common code required
   by any platform supported in OpenSBI. It will be built by default and included
   in libplatsbi.a. This library is installed as
   *<install_directory>/lib/libsbiutils.a*.
3. *libplatsbi.a* - An example platform-specific static library integrating
   *libsbi.a* with platform-specific hooks. This library is available only for
   the platforms supported by OpenSBI. This library is installed as
   *<install_directory>/platform/<platform_subdir>/lib/libplatsbi.a*

Implementations may choose either *libsbi.a* or *libplatsbi.a* to link with
their firmware or bootloader. In the case of *libsbi.a*, platform-specific
hooks in the form of a *struct sbi_platform* instance need to be provided.

The platform-specific example firmwares provided by OpenSBI are not mandatory.
An implementation may choose to link the OpenSBI generic static library together
with an M-mode firmware or bootloader providing the hardware-specific hooks.
Since OpenSBI is a statically linked library, users must ensure that the
license of these external components is compatible with the OpenSBI license.

Constraints on OpenSBI usage from external firmware
---------------------------------------------------

Users have to ensure that an external firmware or bootloader linking against
OpenSBI static libraries (*libsbi.a* or *libplatsbi.a*) is compiled with the
same GCC target options *-mabi*, *-march*, and *-mcmodel*.

There are only two constraints on calling any OpenSBI library function from an
external M-mode firmware or bootloader:

1. The RISC-V *MSCRATCH* CSR must point to a valid OpenSBI scratch space
   (i.e. a *struct sbi_scratch* instance).
2. The RISC-V *SP* register (i.e. the stack pointer) must be set per-HART
   pointing to distinct non-overlapping stacks.

The most important functions from an external firmware or bootloader
perspective are *sbi_init()* and *sbi_trap_handler()*.

In addition to the above constraints, the external firmware or bootloader must
ensure that interrupts are disabled in the *MSTATUS* and *MIE* CSRs when calling
the functions *sbi_init()* and *sbi_trap_handler()*.

The *sbi_init()* function should be called by the external firmware or
bootloader for each HART that is powered-up at boot-time or in response to a
CPU hotplug event.

The *sbi_trap_handler()* function should be called by the external firmware or
bootloader to service the following interrupts and traps:

1. M-mode timer interrupt
2. M-mode software interrupt
3. Illegal instruction trap
4. Misaligned load trap
5. Misaligned store trap
6. Supervisor ecall trap
7. Hypervisor ecall trap

**Note:** external firmwares or bootloaders can be more conservative by
forwarding all traps and interrupts to *sbi_trap_handler()*.

Definitions of OpenSBI Data Types for the External Firmware
-----------------------------------------------------------

OpenSBI can be built as library using external firmware build system such as EDK2
code base (The open source of UEFI firmware implementation) and linked with external
firmware drivers based on the external firmware architecture.

**OPENSBI_EXTERNAL_SBI_TYPES** identifier is introduced to *sbi_types.h* for selecting
external header file during the build preprocess in order to define OpensSBI data types
based on external firmware data type binding.
For example, *bool* is declared as *int* in sbi_types.h. However in EDK2 build system,
*bool* is declared as *BOOLEAN* which is defined as *unsigned char* data type.

External firmware can define **OPENSBI_EXTERNAL_SBI_TYPES** in CFLAGS and specify it to the
header file maintained in its code tree. However, the external build system has to address
the additional include directory for the external header file based on its own build system.
For example,
*-D***OPENSBI_EXTERNAL_SBI_TYPES***=OpensbiTypes.h*
Above tells *sbi_types.h* to refer to *OpensbiTypes.h* instead of using original definitions of
data types.
