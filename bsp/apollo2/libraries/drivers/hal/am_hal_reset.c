//*****************************************************************************
//
//  am_hal_reset.c
//! @file
//!
//! @brief Hardware abstraction layer for the Reset Generator module.
//!
//! @addtogroup rstgen2 Reset Generator (RSTGEN)
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

#include "am_mcu_apollo.h"

//*****************************************************************************
//
//! @brief Configure the Reset Generator.
//!
//! @param ui32Config - Or together the supplied macros to enable
//! configurations to obtain the desired reset generator settings.
//!
//! This function will set the reset generator's configuration register based on
//! the user's desired settings listed in the supplied arugment.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_reset_init(uint32_t ui32Config)
{
    //
    // Write the configuration to the reset generator
    //
    AM_REG(RSTGEN, CFG) = ui32Config;
}

//*****************************************************************************
//
//! @brief Issue a POR (Apollo's last stage interrupt).
//!
//! This function will issue a POR reset.
//! The Apollo chip has numerous stages of reset. POR is the last and is also
//! the reset invoked by the chip's reset pin, the watchdog timer, the AIRCR
//! reset, and the SWD debugger requested interrupt.
//!
//! The Debug Access Port in the M4 is not cleared by this reset.
//!
//! @return None.
//
//*****************************************************************************
void am_hal_reset_por(void)
{
    //
    // Write the POR key to the software POR register.
    //
    AM_REG(RSTGEN, SWPOR) =
           AM_REG_RSTGEN_SWPOR_SWPORKEY(AM_REG_RSTGEN_SWPOR_SWPORKEY_KEYVALUE);
}

//*****************************************************************************
//
//! @brief Issue a POI (Apollo's second stage interrupt).
//!
//! This function will issue a POI reset.
//! The Apollo chip has numerous stages of reset. POI is the second stage.
//! A few modules are reset by POI that are not reset by POR, notably POI
//! causes the shadow registers to be reloaded from the OTP. A full power
//! cycle or POI should be used after writing new flash, debug or SRAM
//! protection bits into the OTP for these protections to take effect.
//!
//! The Debug Access Port in the M4 is not cleared by this reset.
//!
//! @return None.
//
//*****************************************************************************
void am_hal_reset_poi(void)
{
    //
    // Write the POI key to the software POI register.
    //
    AM_REG(RSTGEN, SWPOI) =
           AM_REG_RSTGEN_SWPOI_SWPOIKEY(AM_REG_RSTGEN_SWPOI_SWPOIKEY_KEYVALUE);
}

//*****************************************************************************
//
//! @brief Retrieve the status bits from the reset generator.
//!
//! This function will get the status bits from the reset generator.
//! These bits are sticky and show the accumulation of reset types that the
//! Apollo chip has experienced since power on. One should clear these out
//! after reading them.
//!
//! @return None.
//
//*****************************************************************************
uint32_t am_hal_reset_status_get(void)
{
    //
    // Retrieve the reset generator status bits
    //
    return AM_REG(RSTGEN, STAT);
}

//*****************************************************************************
//
//! @brief Clear ALL of the status bits in the reset generator.
//!
//! This function will clear all status bits in the reset generator status.
//!
//! @return None.
//
//*****************************************************************************
void am_hal_reset_status_clear(void)
{
    AM_REG(RSTGEN, CLRSTAT) = AM_REG_RSTGEN_CLRSTAT_CLRSTAT(1);
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
