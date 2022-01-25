/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : SYSINFO
// Version        : 1
// Bus type       : apb
// Description    : None
// =============================================================================
#ifndef HARDWARE_REGS_SYSINFO_DEFINED
#define HARDWARE_REGS_SYSINFO_DEFINED
// =============================================================================
// Register    : SYSINFO_CHIP_ID
// Description : JEDEC JEP-106 compliant chip identifier.
#define SYSINFO_CHIP_ID_OFFSET 0x00000000
#define SYSINFO_CHIP_ID_BITS   0xffffffff
#define SYSINFO_CHIP_ID_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SYSINFO_CHIP_ID_REVISION
// Description : None
#define SYSINFO_CHIP_ID_REVISION_RESET  "-"
#define SYSINFO_CHIP_ID_REVISION_BITS   0xf0000000
#define SYSINFO_CHIP_ID_REVISION_MSB    31
#define SYSINFO_CHIP_ID_REVISION_LSB    28
#define SYSINFO_CHIP_ID_REVISION_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SYSINFO_CHIP_ID_PART
// Description : None
#define SYSINFO_CHIP_ID_PART_RESET  "-"
#define SYSINFO_CHIP_ID_PART_BITS   0x0ffff000
#define SYSINFO_CHIP_ID_PART_MSB    27
#define SYSINFO_CHIP_ID_PART_LSB    12
#define SYSINFO_CHIP_ID_PART_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SYSINFO_CHIP_ID_MANUFACTURER
// Description : None
#define SYSINFO_CHIP_ID_MANUFACTURER_RESET  "-"
#define SYSINFO_CHIP_ID_MANUFACTURER_BITS   0x00000fff
#define SYSINFO_CHIP_ID_MANUFACTURER_MSB    11
#define SYSINFO_CHIP_ID_MANUFACTURER_LSB    0
#define SYSINFO_CHIP_ID_MANUFACTURER_ACCESS "RO"
// =============================================================================
// Register    : SYSINFO_PLATFORM
// Description : Platform register. Allows software to know what environment it
//               is running in.
#define SYSINFO_PLATFORM_OFFSET 0x00000004
#define SYSINFO_PLATFORM_BITS   0x00000003
#define SYSINFO_PLATFORM_RESET  0x00000000
// -----------------------------------------------------------------------------
// Field       : SYSINFO_PLATFORM_ASIC
// Description : None
#define SYSINFO_PLATFORM_ASIC_RESET  0x0
#define SYSINFO_PLATFORM_ASIC_BITS   0x00000002
#define SYSINFO_PLATFORM_ASIC_MSB    1
#define SYSINFO_PLATFORM_ASIC_LSB    1
#define SYSINFO_PLATFORM_ASIC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : SYSINFO_PLATFORM_FPGA
// Description : None
#define SYSINFO_PLATFORM_FPGA_RESET  0x0
#define SYSINFO_PLATFORM_FPGA_BITS   0x00000001
#define SYSINFO_PLATFORM_FPGA_MSB    0
#define SYSINFO_PLATFORM_FPGA_LSB    0
#define SYSINFO_PLATFORM_FPGA_ACCESS "RO"
// =============================================================================
// Register    : SYSINFO_GITREF_RP2040
// Description : Git hash of the chip source. Used to identify chip version.
#define SYSINFO_GITREF_RP2040_OFFSET 0x00000040
#define SYSINFO_GITREF_RP2040_BITS   0xffffffff
#define SYSINFO_GITREF_RP2040_RESET  "-"
#define SYSINFO_GITREF_RP2040_MSB    31
#define SYSINFO_GITREF_RP2040_LSB    0
#define SYSINFO_GITREF_RP2040_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_SYSINFO_DEFINED
