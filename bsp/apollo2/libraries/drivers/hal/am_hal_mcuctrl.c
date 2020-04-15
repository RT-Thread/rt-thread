//*****************************************************************************
//
//  am_hal_mcuctrl.c
//! @file
//!
//! @brief Functions for interfacing with the MCUCTRL.
//!
//! @addtogroup mcuctrl2 MCU Control (MCUCTRL)
//! @ingroup apollo2hal
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "am_mcu_apollo.h"

#define LDO_TRIM_REG_ADDR   (0x50023004)
#define BUCK_TRIM_REG_ADDR  (0x50023000)

//*****************************************************************************
//
// Global Variables.
//
//*****************************************************************************
//
// Define the flash sizes from CHIP_INFO.
//
const uint32_t g_am_hal_mcuctrl_flash_size[16] =
{
     16 * 1024,             /* 0x0 0x00004000   16 KB */
     32 * 1024,             /* 0x1 0x00008000   32 KB */
     64 * 1024,             /* 0x2 0x00010000   64 KB */
    128 * 1024,             /* 0x3 0x00020000  128 KB */
    256 * 1024,             /* 0x4 0x00040000  256 KB */
    512 * 1024,             /* 0x5 0x00080000  512 KB */
      1 * 1024 * 1024,      /* 0x6 0x00100000    1 MB */
      2 * 1024 * 1024,      /* 0x7 0x00200000    2 MB */
      4 * 1024 * 1024,      /* 0x8 0x00400000    4 MB */
      8 * 1024 * 1024,      /* 0x9 0x00800000    8 MB */
     16 * 1024 * 1024,      /* 0xA 0x01000000    16 MB */
     32 * 1024 * 1024,      /* 0xB 0x02000000    32 MB */
     64 * 1024 * 1024,      /* 0xC 0x04000000    64 MB */
    128 * 1024 * 1024,      /* 0xD 0x08000000   128 MB */
    256 * 1024 * 1024,      /* 0xE 0x10000000   256 MB */
    512 * 1024 * 1024       /* 0xF 0x20000000   512 MB */
};

//
// Define the SRAM sizes from CHIP_INFO.
// For Apollo2, the SRAM sizes are defined exactly the same as the flash sizes.
//
#define g_am_hal_mcuctrl_sram_size  g_am_hal_mcuctrl_flash_size

//*****************************************************************************
//
//! @brief Gets all relevant device information.
//!
//! @param psDevice is a pointer to a structure that will be used to store all
//! device info.
//!
//! This function gets the device part number, chip IDs, and revision and
//! stores them in the passed structure.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_mcuctrl_device_info_get(am_hal_mcuctrl_device_t *psDevice)
{
    //
    // Read the Part Number.
    //
    psDevice->ui32ChipPN = AM_REG(MCUCTRL, CHIP_INFO);

    //
    // Read the Chip ID0.
    //
    psDevice->ui32ChipID0 = AM_REG(MCUCTRL, CHIPID0);

    //
    // Read the Chip ID1.
    //
    psDevice->ui32ChipID1 = AM_REG(MCUCTRL, CHIPID1);

    //
    // Read the Chip Revision.
    //
    psDevice->ui32ChipRev = AM_REG(MCUCTRL, CHIPREV);

    //
    // Read the Part Number.
    //
    psDevice->ui32ChipPN = AM_REG(MCUCTRL, CHIP_INFO);

    //
    // Read the Chip ID0.
    //
    psDevice->ui32ChipID0 = AM_REG(MCUCTRL, CHIPID0);

    //
    // Read the Chip ID1.
    //
    psDevice->ui32ChipID1 = AM_REG(MCUCTRL, CHIPID1);

    //
    // Read the Chip Revision.
    //
    psDevice->ui32ChipRev = AM_REG(MCUCTRL, CHIPREV);

    //
    // Read the Chip VENDOR ID.
    //
    psDevice->ui32VendorID = AM_REG(MCUCTRL, VENDORID);

    //
    // Qualified from Part Number.
    //
    psDevice->ui32Qualified =
            (psDevice->ui32ChipPN & AM_HAL_MCUCTRL_CHIP_INFO_QUAL_M) >>
             AM_HAL_MCUCTRL_CHIP_INFO_QUAL_S;

    //
    // Flash size from Part Number.
    //
    psDevice->ui32FlashSize =
        g_am_hal_mcuctrl_flash_size[
            (psDevice->ui32ChipPN & AM_HAL_MCUCTRL_CHIP_INFO_FLASH_SIZE_M) >>
            AM_HAL_MCUCTRL_CHIP_INFO_FLASH_SIZE_S];

    //
    // SRAM size from Part Number.
    //
    psDevice->ui32SRAMSize =
        g_am_hal_mcuctrl_flash_size[
            (psDevice->ui32ChipPN & AM_HAL_MCUCTRL_CHIP_INFO_SRAM_SIZE_M) >>
            AM_HAL_MCUCTRL_CHIP_INFO_SRAM_SIZE_S];

    //
    // Now, let's look at the JEDEC info.
    // The full partnumber is 12 bits total, but is scattered across 2 registers.
    // Bits [11:8] are 0xE.
    // Bits [7:4] are 0xE for Apollo, 0xD for Apollo2.
    // Bits [3:0] are defined differently for Apollo and Apollo2.
    //   For Apollo, the low nibble is 0x0.
    //   For Apollo2, the low nibble indicates flash and SRAM size.
    //
    psDevice->ui32JedecPN  = (AM_BFR(JEDEC, PID0, PNL8) << 0);
    psDevice->ui32JedecPN |= (AM_BFR(JEDEC, PID1, PNH4) << 8);

    //
    // JEPID is the JEP-106 Manufacturer ID Code, which is assigned to Ambiq as
    //  0x1B, with parity bit is 0x9B.  It is 8 bits located across 2 registers.
    //
    psDevice->ui32JedecJEPID  = (AM_BFR(JEDEC, PID1, JEPIDL) << 0);
    psDevice->ui32JedecJEPID |= (AM_BFR(JEDEC, PID2, JEPIDH) << 4);

    //
    // CHIPREV is 8 bits located across 2 registers.
    //
    psDevice->ui32JedecCHIPREV  = (AM_BFR(JEDEC, PID2, CHIPREVH4) << 4);
    psDevice->ui32JedecCHIPREV |= (AM_BFR(JEDEC, PID3, CHIPREVL4) << 0);

    //
    // Let's get the Coresight ID (32-bits across 4 registers)
    // For Apollo and Apollo2, it's expected to be 0xB105100D.
    //
    psDevice->ui32JedecCID  = (AM_BFR(JEDEC, CID3, CID) << 24);
    psDevice->ui32JedecCID |= (AM_BFR(JEDEC, CID2, CID) << 16);
    psDevice->ui32JedecCID |= (AM_BFR(JEDEC, CID1, CID) <<  8);
    psDevice->ui32JedecCID |= (AM_BFR(JEDEC, CID0, CID) <<  0);
}

//*****************************************************************************
//
//! @brief Enables the fault capture registers.
//!
//! This function enables the DCODEFAULTADDR and ICODEFAULTADDR registers.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_mcuctrl_fault_capture_enable(void)
{
    //
    // Enable the Fault Capture registers.
    //
    AM_BFW(MCUCTRL, FAULTCAPTUREEN, ENABLE, 1);
}

//*****************************************************************************
//
//! @brief Disables the fault capture registers.
//!
//! This function disables the DCODEFAULTADDR and ICODEFAULTADDR registers.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_mcuctrl_fault_capture_disable(void)
{
    //
    // Disable the Fault Capture registers.
    //
    AM_BFW(MCUCTRL, FAULTCAPTUREEN, ENABLE, 0);
}

//*****************************************************************************
//
//! @brief Gets the fault status and capture registers.
//!
//! @param psFault is a pointer to a structure that will be used to store all
//! fault info.
//!
//! This function gets the status of the ICODE, DCODE, and SYS bus faults and
//! the addresses associated with the fault.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_mcuctrl_fault_status(am_hal_mcuctrl_fault_t *psFault)
{
    uint32_t ui32FaultStat;

    //
    // Read the Fault Status Register.
    //
    ui32FaultStat = AM_REG(MCUCTRL, FAULTSTATUS);
    psFault->bICODE = (ui32FaultStat & AM_REG_MCUCTRL_FAULTSTATUS_ICODE_M);
    psFault->bDCODE = (ui32FaultStat & AM_REG_MCUCTRL_FAULTSTATUS_DCODE_M);
    psFault->bSYS = (ui32FaultStat & AM_REG_MCUCTRL_FAULTSTATUS_SYS_M);

    //
    // Read the DCODE fault capture address register.
    //
    psFault->ui32DCODE = AM_REG(MCUCTRL, DCODEFAULTADDR);

    //
    // Read the ICODE fault capture address register.
    //
    psFault->ui32ICODE |= AM_REG(MCUCTRL, ICODEFAULTADDR);

    //
    // Read the ICODE fault capture address register.
    //
    psFault->ui32SYS |= AM_REG(MCUCTRL, SYSFAULTADDR);
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
