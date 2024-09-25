Shakti C-class SoC Platform
===========================
C-Class is a member of the SHAKTI family of processors from
Indian Institute of Technology - Madras (IIT-M).

It is an extremely configurable and commercial-grade 5-stage
in-order core supporting the standard RV64GCSUN ISA extensions.

For more details, refer:
* https://gitlab.com/shaktiproject/cores/c-class/blob/master/README.md
* https://c-class.readthedocs.io/en/latest
* https://shakti.org.in

Platform Options
----------------

The *Shakti C-class SoC* platform does not have any platform-specific
options.

Building Shakti C-class Platform
--------------------------------

**Linux Kernel Payload**

```
make PLATFORM=generic FW_PAYLOAD_PATH=<linux_build_directory>/arch/riscv/boot/Image FW_FDT_PATH=<shakti.dtb path>
```

**Test Payload**

```
make PLATFORM=generic FW_FDT_PATH=<shakti.dtb path>
```
