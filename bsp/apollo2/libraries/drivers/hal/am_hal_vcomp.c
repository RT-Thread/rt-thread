//*****************************************************************************
//
//  am_hal_vcomp.c
//! @file
//!
//! @brief Functions for operating the on-chip Voltage Comparator
//!
//! @addtogroup vcomp2 Voltage Comparator (VCOMP)
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

//*****************************************************************************
//
//! @brief Configure the Voltage Comparator module.
//!
//! @param psConfig is a structure containing configuration information for the
//! voltage comparator.
//!
//! This function configures the positive and negative input signals for the
//! voltage comparator.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_vcomp_config(const am_hal_vcomp_config_t *psConfig)
{
    //
    // The configuration word should be a simple OR of the components of the
    // configuration structure.
    //
    AM_REG(VCOMP, CFG) = (psConfig->ui32LevelSelect |
                          psConfig->ui32PosInput |
                          psConfig->ui32NegInput);
}

//*****************************************************************************
//
//! @brief Set the Voltage Comparator DAC Level Select in Configuration Reg.
//!
//! @param ui32Level - DAC voltage selector (use macros enumerations)
//!
//! This function sets the DAC level select in the configuration register.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_vcomp_dac_level_set(uint32_t ui32Level)
{
    //
    // Insert the supplied level into the vcomp configuration register
    //
    AM_BFW(VCOMP, CFG, LVLSEL, ui32Level >> AM_REG_VCOMP_CFG_LVLSEL_S);
}

//*****************************************************************************
//
//! @brief Read the state of the voltage comparator.
//!
//! This function extracts the comparator state from the status register.
//!
//! @return the voltage comparator state
//
//*****************************************************************************
bool
am_hal_vcomp_read(void)
{
    return (AM_BFR(VCOMP,  STAT, CMPOUT) == 1);
}

//*****************************************************************************
//
//! @brief Enable the voltage comparator.
//!
//! This function powers up the voltage comparator.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_vcomp_enable(void)
{
    AM_REG(VCOMP, PWDKEY) = 0;
}

//*****************************************************************************
//
//! @brief Disable the voltage comparator.
//!
//! This function powers down the voltage comparator.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_vcomp_disable(void)
{
    AM_REG(VCOMP, PWDKEY) = AM_REG_VCOMP_PWDKEY_KEYVAL;
}

//*****************************************************************************
//
//! @brief Read the state of the voltage comparator interrupt status bits.
//!
//! @param bEnabledOnly - return the status of only the enabled interrupts.
//!
//! This function extracts the interrupt status bits and returns the raw or
//! only the enabled based on bEnabledOnly.
//!
//! @return Bitwise representation of the current interrupt status.
//!
//! The return value will be the logical OR of one or more of the following
//! values:
//!
//! AM_HAL_VCOMP_INT_OUTHI
//! AM_HAL_VCOMP_INT_OUTLO
//
//*****************************************************************************
uint32_t
am_hal_vcomp_int_status_get(bool bEnabledOnly)
{
    if (bEnabledOnly)
    {
        uint32_t u32RetVal = AM_REG(VCOMP, INTSTAT);
        return u32RetVal & AM_REG(VCOMP, INTEN);
    }
    else
    {
        return AM_REG(VCOMP, INTSTAT);
    }
}

//*****************************************************************************
//
//! @brief Set the state of the voltage comparator interrupt status bits.
//!
//! @param ui32Interrupt - interrupts to be set.
//!
//! This function sets the specified interrupt status bits.
//!
//! ui32Interrupt should be a logical or of:
//!
//! AM_HAL_VCOMP_INT_OUTHI
//! AM_HAL_VCOMP_INT_OUTLO
//!
//! @return None
//
//*****************************************************************************
void
am_hal_vcomp_int_set(uint32_t ui32Interrupt)
{
    AM_REG(VCOMP, INTSET) = ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Clear the state of the voltage comparator interrupt status bits.
//!
//! @param ui32Interrupt - interrupts to be cleared.
//!
//! This function clears the specified interrupt status bits.
//!
//! ui32Interrupt should be a logical or of:
//!
//! AM_HAL_VCOMP_INT_OUTHI
//! AM_HAL_VCOMP_INT_OUTLO
//!
//! @return None
//
//*****************************************************************************
void
am_hal_vcomp_int_clear(uint32_t ui32Interrupt)
{
    AM_REG(VCOMP, INTCLR) = ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Enable the voltage comparator interrupt status bits.
//!
//! @param ui32Interrupt - interrupts to be enabled.
//!
//! This function enables desired interrupt status bits.
//!
//! ui32Interrupt should be a logical or of:
//!
//! AM_HAL_VCOMP_INT_OUTHI
//! AM_HAL_VCOMP_INT_OUTLO
//!
//! @return None
//
//*****************************************************************************
void
am_hal_vcomp_int_enable(uint32_t ui32Interrupt)
{
    AM_REG(VCOMP, INTEN) |= ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Return the enabled, voltage comparator interrupt status bits.
//!
//! This function returns the enabled interrupt status bits
//!
//! @return returns the enabled interrupt status bits. The return is a logical
//! or of:
//!
//! AM_HAL_VCOMP_INT_OUTHI
//! AM_HAL_VCOMP_INT_OUTLO
//
//*****************************************************************************
uint32_t
am_hal_vcomp_int_enable_get(void)
{
    return AM_REG(VCOMP, INTEN);
}

//*****************************************************************************
//
//! @brief Disable the voltage comparator interrupt status bits.
//!
//! @param ui32Interrupt - interrupts to be disabled.
//!
//! This function disables desired interrupt status bits.
//!
//! ui32Interrupt should be a logical or of:
//!
//! AM_HAL_VCOMP_INT_OUTHI
//! AM_HAL_VCOMP_INT_OUTLO
//!
//! @return None
//
//*****************************************************************************
void
am_hal_vcomp_int_disable(uint32_t ui32Interrupt)
{
    AM_REG(VCOMP, INTEN) &= ~ui32Interrupt;
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
