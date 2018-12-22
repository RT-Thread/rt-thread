//*****************************************************************************
//
//  am_hal_mcuctrl.h
//! @file
//!
//! @brief Functions for accessing and configuring the MCUCTRL.
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
#ifndef AM_HAL_MCUCTRL_H
#define AM_HAL_MCUCTRL_H

//
// Deprecate the am_hal_mcuctrl_bucks_enable() and disable() functions.
// This functionality is now handled in pwrctrl.
//
#define am_hal_mcuctrl_bucks_enable     am_hal_pwrctrl_bucks_enable
#define am_hal_mcuctrl_bucks_disable    am_hal_pwrctrl_bucks_disable


//*****************************************************************************
//
// Define CHIP_INFO fields, which for Apollo2 are not defined in the register
// definitions.
//
//*****************************************************************************
#define AM_HAL_MCUCTRL_CHIP_INFO_CLASS_M        0xFF000000
#define AM_HAL_MCUCTRL_CHIP_INFO_CLASS_S        24
#define AM_HAL_MCUCTRL_CHIP_INFO_FLASH_SIZE_M   0x00F00000
#define AM_HAL_MCUCTRL_CHIP_INFO_FLASH_SIZE_S   20
#define AM_HAL_MCUCTRL_CHIP_INFO_SRAM_SIZE_M    0x000F0000
#define AM_HAL_MCUCTRL_CHIP_INFO_SRAM_SIZE_S    16
#define AM_HAL_MCUCTRL_CHIP_INFO_REV_M          0x0000FF00
#define AM_HAL_MCUCTRL_CHIP_INFO_REV_S          8
#define AM_HAL_MCUCTRL_CHIP_INFO_PKG_M          0x000000C0
#define AM_HAL_MCUCTRL_CHIP_INFO_PKG_S          6
#define AM_HAL_MCUCTRL_CHIP_INFO_PINS_M         0x00000038
#define AM_HAL_MCUCTRL_CHIP_INFO_PINS_S         3
#define AM_HAL_MCUCTRL_CHIP_INFO_TEMP_M         0x00000006
#define AM_HAL_MCUCTRL_CHIP_INFO_TEMP_S         1
#define AM_HAL_MCUCTRL_CHIP_INFO_QUAL_M         0x00000001
#define AM_HAL_MCUCTRL_CHIP_INFO_QUAL_S         0

//*****************************************************************************
//
// Apollo Number Decode.
//
//*****************************************************************************
extern const uint32_t g_am_hal_mcuctrl_flash_size[];
extern const uint32_t g_am_hal_mcuctrl_sram_size[];

//*****************************************************************************
//
//! MCUCTRL device structure
//
//*****************************************************************************
typedef struct
{
    //
    //! Device part number. (BCD format)
    //
    uint32_t ui32ChipPN;

    //
    //! Unique Chip ID 0.
    //
    uint32_t ui32ChipID0;

    //
    //! Unique Chip ID 1.
    //
    uint32_t ui32ChipID1;

    //
    //! Chip Revision.
    //
    uint32_t ui32ChipRev;

    //
    //! Vendor ID.
    //
    uint32_t ui32VendorID;

    //
    //! Qualified chip.
    //
    uint32_t ui32Qualified;

    //
    //! Flash Size.
    //
    uint32_t ui32FlashSize;

    //
    //! SRAM Size.
    //
    uint32_t ui32SRAMSize;

    //
    // JEDEC chip info
    //
    uint32_t ui32JedecPN;
    uint32_t ui32JedecJEPID;
    uint32_t ui32JedecCHIPREV;
    uint32_t ui32JedecCID;
}
am_hal_mcuctrl_device_t;

//*****************************************************************************
//
//! MCUCTRL fault structure
//
//*****************************************************************************
typedef struct
{
    //
    //! ICODE bus fault occurred.
    //
    bool bICODE;

    //
    //! ICODE bus fault address.
    //
    uint32_t ui32ICODE;

    //
    //! DCODE bus fault occurred.
    //
    bool bDCODE;

    //
    //! DCODE bus fault address.
    //
    uint32_t ui32DCODE;

    //
    //! SYS bus fault occurred.
    //
    bool bSYS;

    //
    //! SYS bus fault address.
    //
    uint32_t ui32SYS;
}
am_hal_mcuctrl_fault_t;

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// External function definitions
//
//*****************************************************************************
extern void am_hal_mcuctrl_device_info_get(am_hal_mcuctrl_device_t *psDevice);
extern void am_hal_mcuctrl_fault_capture_enable(void);
extern void am_hal_mcuctrl_fault_capture_disable(void);
extern void am_hal_mcuctrl_fault_status(am_hal_mcuctrl_fault_t *psFault);

#ifdef __cplusplus
}
#endif

#endif // AM_HAL_MCUCTRL_H

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
