
Nuclei UX600 Platform
=====================

The **Nuclei UX600** is a 64-bit RISC-V Core which is capable of running Linux.

> Nuclei UX600: single core, pipeline as single-issue and 6~9 variable stages, in-order dispatch and out-of-order write-back, running up to >1.2GHz

To build the platform-specific library and firmware images, provide the
*PLATFORM=nuclei/ux600* parameter to the top level `make` command.

Platform Options
----------------

The *Nuclei UX600* platform does not have any platform-specific options.

Building Nuclei UX600 Platform
------------------------------

```
make PLATFORM=nuclei/ux600 clean all
```
