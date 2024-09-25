OpenSBI Platform Requirements
=============================

The RISC-V platform requirements for OpenSBI can change over time
with advances in RISC-V specifications and ecosystem.

To handle this, we have two types of RISC-V platform requirements:

1. **Base platform requirements** which apply to all OpenSBI releases
2. **Release specific platform requirements** which apply to a OpenSBI
   release and later releases

Currently, we don't have any **Release specific platform requirements**
but such platform requirements will be added in future.

Base Platform Requirements
--------------------------

The base RISC-V platform requirements for OpenSBI are as follows:

1. At least rv32ima or rv64ima required on all HARTs
2. At least one HART should have S-mode support because:

     * SBI calls are meant for RISC-V S-mode (Supervisor mode)
     * OpenSBI implements SBI calls for S-mode software

3. The MTVEC CSR on all HARTs must support direct mode
4. The PMP CSRs are optional. If PMP CSRs are not implemented then
   OpenSBI cannot protect M-mode firmware and secured memory regions
5. The TIME CSR is optional. If TIME CSR is not implemented in
   hardware then a 64-bit MMIO counter is required to track time
   and emulate TIME CSR
6. Hardware support for injecting M-mode software interrupts on
   a multi-HART platform

The RISC-V extensions not covered by rv32ima or rv64ima are optional
for OpenSBI. Although, OpenSBI will detect and handle some of these
optional RISC-V extensions at runtime.

The optional RISC-V extensions handled by OpenSBI at runtime are:

* D-extension: Double precision floating point
* F-extension: Single precision floating point
* H-extension: Hypervisor
