/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __PMU_DRIVER_H__
#define __PMU_DRIVER_H__

#include "sdk.h"

//! @addtogroup diag_pmu
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Available voltage regulators.
//!
//! The regulators are divided into two groups of three based on what type loads they power,
//! analog and digital. The digital regulators are called digital only because they power
//! digital portions of the chip, not because of their construction.
//!
//! Analog regulators:
//! - kPMURegulator_1p1
//! - kPMURegulator_2p5
//! - kPMURegulator_3p0
//!
//! Digital regulators:
//! - kPMURegulator_ArmCore
//! - kPMURegulator_Graphics
//! - kPMURegulator_SoC
typedef enum _pmu_regs {
    kPMURegulator_1p1 = 0, //!< 1.1V nominal regulator (REG_1P1).
    kPMURegulator_2p5,     //!< 2.5V nominal regulator (REG_2P5).
    kPMURegulator_3p0,     //!< 3.0V nominal regulator (REG_3P0).
    kPMURegulator_ArmCore, //!< ARM core regulator (REG_ARM_CORE).
    kPMURegulator_Graphics,      //!< VPU/GPU/OpenVG regulator (REG_PU).
    kPMURegulator_SoC      //!< SoC regulator (REG_SOC).
} pmu_regulators_t;

//! @brief Ramp rate constants.
//!
//! The #kPMUProperty_RampRate property is used to control how fast the digital regulators
//! switch to higher voltage levels. There are four available rates, each associated with a
//! number of 24MHz clock ticks to delay at each 25mV step from the original voltage to the
//! new one.
enum _pmu_ramp_rates
{
    kPMURate_Fast = 0,  //!< 64 clocks. This is the default rate.
    kPMURate_Medium,    //!< 128 clocks.
    kPMURate_Slow,      //!< 256 clocks.
    kPMURate_VerySlow,  //!< 512 clocks.
};

//! @brief Properties of PMU regulators.
//!
//! Some properties are read-only. If you call pmu_set_property() on a read-only property,
//! you will get a #kPMUError_ReadOnlyProperty error.
//!
//! Most properties apply only to the regulator specified in the get/set call. However, some
//! properties are global, and changing their value will affect other regulators, as well. These
//! properties are documented below.
typedef enum _pmu_regulator_properties {
    //! @brief Output voltage in millivolts. [uint32_t]
    //!
    //! The valid voltage ranges differ for each regulator. In addition to the range supported
    //! by the regulator hardware, the PMU driver normally disallows setting the output voltages
    //! to values that could prevent proper functioning or damage the hardware. See the 
    //! #kPMUProperty_SafetyOverrideIsEnabled property for more details.
    kPMUProperty_OutputMillivolts,
    
    //! @brief Minimum allowed output voltage in millivolts. [uint32_t, read-only]
    kPMUProperty_MinOutputMillivolts,
    
    //! @brief Maximum allowed output voltage in millivolts. [uint32_t, read-only]
    kPMUProperty_MaxOutputMillivolts,
    
    //! @brief Brownout voltage in millivolts. [uint32_t]
    //!
    //! The brownout voltage must be between 75mV and 175mV below the output voltage. Any value
    //! outside this range will result in a #kPMUError_ValueOutOfRange error.
    kPMUProperty_BrownoutMillivolts,
    
    //! @brief Minimum allowed brownout voltage in millivolts. [uint32_t, read-only]
    kPMUProperty_MinBrownoutMillivolts,
    
    //! @brief Maximum allowed brownout voltage in millivolts. [uint32_t, read-only]
    kPMUProperty_MaxBrownoutMillivolts,
    
    //! @brief Enable flag for the regulator. [bool]
    kPMUProperty_IsEnabled,
    
    //! @brief Enable property for the bypass mode of the core regulators. [bool]
    //!
    //! The digital or core regulators have an option to turn the pass FET completely on,
    //! which is effectively a bypass. The input voltage is passed through unregulated. This
    //! mode can be used if external regulation is provided, in order to reduce losses.
    //!
    //! Only applies to core regulators. Attempting to get or set this property for the analog
    //! regulators will result in a #kPMUError_UnsupportedProperty error.
    kPMUProperty_IsBypassed,
    
    //! @brief Enable for the brownout detector. [bool]
    kPMUProperty_BrownoutDetectIsEnabled,
    
    //! @brief Whether the current limiter is enabled. [bool]
    //!
    //! The core regulators do not have a current limiter.
    kPMUProperty_CurrentLimitIsEnabled,
    
    //! @brief Whether the regulator is functioning properly. [bool, read-only]
    kPMUProperty_IsOK,
    
    //! @brief Whether the regulator is currently browning out. [bool, read-only]
    kPMUProperty_IsInBrownout,
    
    //! @brief Enable for the regulator pulldown. [bool]
    //!
    //! The core regulators and 3p0 do not have a pulldown.
    kPMUProperty_PulldownIsEnabled,
    
    //! @brief Ramp rate. [uint32_t]
    //!
    //! One of the ramp rate constants:
    //! - #kPMURate_VerySlow
    //! - #kPMURate_Slow
    //! - #kPMURate_Medium
    //! - #kPMURate_Fast
    kPMUProperty_RampRate,
    
    //! @brief Function to be called when a regulator browns out. [pmu_bo_handler_t]
    kPMUProperty_BrownoutHandler,
    
    //! @brief Boolean that controls whether unsafe voltages are allowed. [bool]
    //!
    //! Normally, the PMU driver disallows setting regulator voltages to unsafe values. These
    //! are either voltages that are too low to continue operation, or so high that the chip may
    //! be damaged or have its lifetime reduced. Changing this property value to true will
    //! disable the safety checks and allow the caller to set the output voltage to any value
    //! supported by the regulator hardware.
    kPMUProperty_SafetyOverrideIsEnabled
} pmu_property_t;

//! @brief Status codes returned by the PMU driver.
enum _pmu_status
{
    kPMUSuccess = 0,
    
    kPMUError_ValueOutOfRange = -1,
    kPMUError_ReadOnlyProperty = -2,
    kPMUError_UnsupportedProperty = -3,
    kPMUError_UnsafeVoltage = -4
};

//! @brief Brownout handler function.
//! @param regulator The regulator that is in brownout.
typedef void (*pmu_bo_handler_t)(pmu_regulators_t regulator);

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif


//! @brief Initialize the PMU driver.
//!
//! Self-bias of the analog bandgap is turned off, to enable better precision. Brownout detect 
//! is turned off for all regulators.
void pmu_init(void);

//! @brief Get the current value of a regulator's property.
//!
//! @retval kPMUSuccess
//! @retval kPMUValueOutOfRangeError
//! @retval kPMUUnsupportedPropertyError
int pmu_get_property(pmu_regulators_t regulator, pmu_property_t selector, void * value);

//! @brief Change the value of a property for a regulator.
//!
//! @retval kPMUSuccess
//! @retval kPMUPropertyIsReadOnlyError
//! @retval kPMUUnsupportedPropertyError
int pmu_set_property(pmu_regulators_t regulator, pmu_property_t selector, const void * value);


#if defined(__cplusplus)
}
#endif

//! @}

#endif // __PMU_DRIVER_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
