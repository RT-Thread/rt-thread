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

#include <string.h>
#include <new>
#include "pmu_driver_internal.h"

using namespace pmu;

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

static void pmu_analog_brownout_isr(void);
static void pmu_digital_brownout_isr(void);
static Regulator & pmu_get_regulator(pmu_regulators_t regulator);
static void pmu_set_all_property(pmu_property_t selector, const void * value);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Global state information for the PMU driver.
static pmu_info_t s_pmu;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! @brief Interrupt service routine for the analog regulator brownout.
//!
//! Determines which analog regulator is in brownout, then calls the installed brownout handler
//! routine.
void pmu_analog_brownout_isr(void)
{
    // Check 1p1 regulator.
    if (s_pmu.ldo1p1.isInBrownout())
    {
        s_pmu.ldo1p1.getBrownoutHandler()(kPMURegulator_1p1);
    }

    // Check 2p5 regulator.
    if (s_pmu.ldo2p5.isInBrownout())
    {
        s_pmu.ldo2p5.getBrownoutHandler()(kPMURegulator_2p5);
    }

    // Check 3p0 regulator.
    if (s_pmu.ldo3p0.isInBrownout())
    {
        s_pmu.ldo3p0.getBrownoutHandler()(kPMURegulator_3p0);
    }

    // Clear the IRQ.
    HW_PMU_MISC1_SET(BM_PMU_MISC1_IRQ_ANA_BO);
}

//! @brief Interrupt service routine for the digital regulator brownout.
//!
//! Determines which digital regulator is in brownout, then calls the installed brownout handler
//! routine.
void pmu_digital_brownout_isr(void)
{
    // Check ARM core regulator.
    if (s_pmu.ldoArm.isInBrownout())
    {
        s_pmu.ldoArm.getBrownoutHandler()(kPMURegulator_ArmCore);
    }

    // Check PU regulator.
    if (s_pmu.ldoGraphics.isInBrownout())
    {
        s_pmu.ldoGraphics.getBrownoutHandler()(kPMURegulator_Graphics);
    }

    // Check SoC regulator.
    if (s_pmu.ldoSoC.isInBrownout())
    {
        s_pmu.ldoSoC.getBrownoutHandler()(kPMURegulator_SoC);
    }

    // Clear the IRQ.
    HW_PMU_MISC1_SET(BM_PMU_MISC1_IRQ_DIG_BO);
}

//! @brief Returns the regulator object for the requested regulator.
Regulator & pmu_get_regulator(pmu_regulators_t regulator)
{
    switch (regulator)
    {
        case kPMURegulator_1p1:
            return s_pmu.ldo1p1;
            
        case kPMURegulator_2p5:
            return s_pmu.ldo2p5;
            
        case kPMURegulator_3p0:
            return s_pmu.ldo3p0;
            
        case kPMURegulator_ArmCore:
            return s_pmu.ldoArm;
            
        case kPMURegulator_Graphics:
            return s_pmu.ldoGraphics;
            
        case kPMURegulator_SoC:
            return s_pmu.ldoSoC;
        
        // Need a default case to make the compiler happy.
        default:
            return s_pmu.ldo1p1;
    }
}

//! @brief Utility to change a property on all regulators simultaneously.
void pmu_set_all_property(pmu_property_t selector, const void * value)
{
    unsigned regulator;
    for (regulator = kPMURegulator_1p1; regulator <= kPMURegulator_SoC; ++regulator)
    {
        pmu_get_regulator(static_cast<pmu_regulators_t>(regulator)).setProperty(selector, value);
    }
}

// See documentation comment in pmu_driver.h.
void pmu_init(void)
{
    // Don't re-init.
    if (s_pmu.isInited)
    {
        return;
    }
    
    // Clear globals.
    memset(&s_pmu, 0, sizeof(s_pmu));
    
    // Construct regulator objects in-place, so we don't depend on static initialization to
    // fill in the vtables correctly, while also not requiring dynamic allocation.
    new (&s_pmu.ldo1p1) LDO1p1Regulator;
    new (&s_pmu.ldo2p5) LDO2p5Regulator;
    new (&s_pmu.ldo3p0) LDO3p0Regulator;
    new (&s_pmu.ldoArm) LDOARMRegulator;
    new (&s_pmu.ldoGraphics) LDOGraphicsRegulator;
    new (&s_pmu.ldoSoC) LDOSoCRegulator;
    
    // Turn off self-bias of the bandgap.
    HW_PMU_MISC0.B.REFTOP_SELFBIASOFF = 1;
    
    // Turn off the brownout detector for all regulators.
    bool value = false;
    pmu_set_all_property(kPMUProperty_BrownoutDetectIsEnabled, &value);
    
    // Init brownout interrupt handling.
    register_interrupt_routine(IMX_INT_PMU_ANA_BO, pmu_analog_brownout_isr);
    register_interrupt_routine(IMX_INT_PMU_DIG_BO, pmu_digital_brownout_isr);
    
    // Clear IRQs.
    HW_PMU_MISC1_SET(BM_PMU_MISC1_IRQ_ANA_BO | BM_PMU_MISC1_IRQ_DIG_BO);
    
    // And enable the IRQs.
//     enable_interrupt(IMX_INT_PMU_ANA_BO, CPU_0, 1);
//     enable_interrupt(IMX_INT_PMU_DIG_BO, CPU_0, 1);
    
    // We are finished initing.
    s_pmu.isInited = true;
}

// See documentation comment in pmu_driver.h.
int pmu_get_property(pmu_regulators_t regulator, pmu_property_t selector, void * value)
{
    return pmu_get_regulator(regulator).getProperty(selector, value);
}

// See documentation comment in pmu_driver.h.
int pmu_set_property(pmu_regulators_t regulator, pmu_property_t selector, const void * value)
{
    return pmu_get_regulator(regulator).setProperty(selector, value);
}

//------------------------------------------------------------------------------

int Regulator::getProperty(pmu_property_t selector, void * value)
{
    int status = kPMUSuccess;
    
    switch (selector)
    {
        case kPMUProperty_OutputMillivolts:
            *reinterpret_cast<uint32_t *>(value) = getOutputMillivolts();
            break;
        
        case kPMUProperty_BrownoutMillivolts:
            *reinterpret_cast<uint32_t *>(value) = getBrownoutMillivolts();
            break;

        case kPMUProperty_MinOutputMillivolts:
            *reinterpret_cast<uint32_t *>(value) = m_isSafetyOverrideEnabled
                ? m_minMillivolts
                : m_minSafeMillivolts;
            break;
        
        case kPMUProperty_MaxOutputMillivolts:
            *reinterpret_cast<uint32_t *>(value) = m_isSafetyOverrideEnabled
                ? (m_minMillivolts + kMaxOutputTriggerValue * _25_mV)
                : m_maxSafeMillivolts;
            break;
        
        case kPMUProperty_MinBrownoutMillivolts:
            *reinterpret_cast<uint32_t *>(value) = getOutputMillivolts() - _75_mV - kMaxBrownoutOffsetValue * _25_mV;
            break;
        
        case kPMUProperty_MaxBrownoutMillivolts:
            *reinterpret_cast<uint32_t *>(value) = getOutputMillivolts() - _75_mV;
            break;
        
        case kPMUProperty_IsEnabled:
            *reinterpret_cast<bool *>(value) = isEnabled();
            break;
        
        case kPMUProperty_BrownoutDetectIsEnabled:
            *reinterpret_cast<bool *>(value) = isBrownoutDetectEnabled();
            break;
        
        case kPMUProperty_IsOK:
            *reinterpret_cast<bool *>(value) = isOK();
            break;
        
        case kPMUProperty_IsInBrownout:
            *reinterpret_cast<bool *>(value) = isInBrownout();
            break;
        
        case kPMUProperty_BrownoutHandler:
            *reinterpret_cast<pmu_bo_handler_t *>(value) = getBrownoutHandler();
            break;
        
        case kPMUProperty_SafetyOverrideIsEnabled:
            *reinterpret_cast<bool *>(value) = m_isSafetyOverrideEnabled;
            break;
        
        default:
            status = kPMUError_UnsupportedProperty;
    }
    
    return status;
}

int Regulator::setProperty(pmu_property_t selector, const void * value)
{
    int status = kPMUSuccess;
    
    switch (selector)
    {
        case kPMUProperty_OutputMillivolts:
            status = setOutputMillivolts(*reinterpret_cast<const uint32_t *>(value));
            break;
        
        case kPMUProperty_BrownoutMillivolts:
            status = setBrownoutMillivolts(*reinterpret_cast<const uint32_t *>(value));
            break;
        
        case kPMUProperty_IsEnabled:
            status = setIsEnabled(*reinterpret_cast<const bool *>(value));
            break;
        
        case kPMUProperty_BrownoutDetectIsEnabled:
            status = setBrownoutDetectIsEnabled(*reinterpret_cast<const bool *>(value));
            break;
        
        case kPMUProperty_BrownoutHandler:
            setBrownoutHandler(*reinterpret_cast<const pmu_bo_handler_t *>(value));
            break;
        
        case kPMUProperty_SafetyOverrideIsEnabled:
            m_isSafetyOverrideEnabled = *reinterpret_cast<const bool *>(value);
            break;
        
        // Catch attempts to set read-only properties.
        case kPMUProperty_IsOK:
        case kPMUProperty_IsInBrownout:
        case kPMUProperty_MinOutputMillivolts:
        case kPMUProperty_MaxOutputMillivolts:
        case kPMUProperty_MinBrownoutMillivolts:
        case kPMUProperty_MaxBrownoutMillivolts:
            status = kPMUError_ReadOnlyProperty;
            break;
        
        default:
            status = kPMUError_UnsupportedProperty;
    }
    
    return status;
}

void Regulator::setVoltageRange(uint32_t min_mV, uint32_t minSafe_mV, uint32_t maxSafe_mV)
{
    m_minMillivolts = min_mV;
    m_minSafeMillivolts = minSafe_mV;
    m_maxSafeMillivolts = maxSafe_mV;
}

//------------------------------------------------------------------------------

int AnalogRegulator::getProperty(pmu_property_t selector, void * value)
{
    int status = kPMUSuccess;
    
    switch (selector)
    {
        case kPMUProperty_CurrentLimitIsEnabled:
            *reinterpret_cast<bool *>(value) = m_controlRegister.B.ENABLE_ILIMIT;
            break;
        
        case kPMUProperty_PulldownIsEnabled:
            *reinterpret_cast<bool *>(value) = m_controlRegister.B.ENABLE_PULLDOWN;
            break;
        
        default:
            status = Regulator::getProperty(selector, value);
    }
    
    return status;
}

int AnalogRegulator::setProperty(pmu_property_t selector, const void * value)
{
    int status = kPMUSuccess;
    
    switch (selector)
    {
        case kPMUProperty_CurrentLimitIsEnabled:
            m_controlRegister.B.ENABLE_ILIMIT = *reinterpret_cast<const bool *>(value);
            break;
        
        case kPMUProperty_PulldownIsEnabled:
            m_controlRegister.B.ENABLE_PULLDOWN = *reinterpret_cast<const bool *>(value);
            break;
        
        default:
            return Regulator::setProperty(selector, value);
    }
    
    return status;
}

uint32_t AnalogRegulator::getOutputMillivolts() const
{
    return m_minMillivolts + m_controlRegister.B.OUTPUT_TRG * _25_mV;
}

int AnalogRegulator::setOutputMillivolts(uint32_t mV)
{
    // First check the safe voltage range.
    if (!m_isSafetyOverrideEnabled && (mV < m_minSafeMillivolts || mV > m_maxSafeMillivolts))
    {
        return kPMUError_UnsafeVoltage;
    }
    
    // Validate low end of the voltage range. The high end is checked below.
    if (mV < m_minMillivolts)
    {
        return kPMUError_ValueOutOfRange;
    }
    
    // Calculate the trigger and make sure it's valid.
    uint32_t trigger = (mV - m_minMillivolts) / _25_mV;
    if (trigger > kMaxOutputTriggerValue)
    {
        return kPMUError_ValueOutOfRange;
    }
    
    // Passed all checks, so set the new voltage.
    m_controlRegister.B.OUTPUT_TRG = trigger;
    
    return kPMUSuccess;
}

uint32_t AnalogRegulator::getBrownoutMillivolts() const
{
    return getOutputMillivolts() - _75_mV - m_controlRegister.B.BO_OFFSET * _25_mV;
}

int AnalogRegulator::setBrownoutMillivolts(uint32_t mV)
{
    uint32_t output_mV = getOutputMillivolts();
    
    // Brownout must be at least 75 mV below the output voltage.
    if (mV > output_mV - _75_mV)
    {
        return kPMUError_ValueOutOfRange;
    }
    
    // Compute the offset value.
    uint32_t offset = (output_mV - _75_mV - mV) / _25_mV;
    if (offset > kMaxBrownoutOffsetValue)
    {
        return kPMUError_ValueOutOfRange;
    }
    
    return kPMUSuccess;
}

bool AnalogRegulator::isBrownoutDetectEnabled() const
{
    return m_controlRegister.B.ENABLE_BO == 1;
}

int AnalogRegulator::setBrownoutDetectIsEnabled(bool enableIt)
{
    m_controlRegister.B.ENABLE_BO = enableIt;
    return kPMUSuccess;
}

bool AnalogRegulator::isEnabled() const
{
    return m_controlRegister.B.ENABLE_LINREG == 1;
}

int AnalogRegulator::setIsEnabled(bool enableIt)
{
    m_controlRegister.B.ENABLE_LINREG = enableIt;
    return kPMUSuccess;
}

//------------------------------------------------------------------------------

DigitalRegulator::DigitalRegulator()
:   Regulator()
{
}

int DigitalRegulator::getProperty(pmu_property_t selector, void * value)
{
    int status = kPMUSuccess;
    
    switch (selector)
    {
        case kPMUProperty_MaxOutputMillivolts:
            *reinterpret_cast<uint32_t *>(value) = m_isSafetyOverrideEnabled
                ? (m_minMillivolts + kDigitalTriggerValueRange * _25_mV)
                : m_maxSafeMillivolts;
            break;

        case kPMUProperty_IsBypassed:
            *reinterpret_cast<bool *>(value) = isBypassed();
            break;
        
        case kPMUProperty_RampRate:
            *reinterpret_cast<uint32_t *>(value) = getRampRate();
            break;
            
        default:
            return Regulator::getProperty(selector, value);
    }
    
    return status;
}

int DigitalRegulator::setProperty(pmu_property_t selector, const void * value)
{
    int status = kPMUSuccess;
    
    switch (selector)
    {
        case kPMUProperty_IsBypassed:
            status = setIsBypassed(*reinterpret_cast<const bool *>(value));
            break;
        
        case kPMUProperty_RampRate:
            status = setRampRate(*reinterpret_cast<const uint32_t *>(value));
            break;
            
        default:
            return Regulator::setProperty(selector, value);
    }
    
    return status;
}

bool DigitalRegulator::isBypassed() const
{
    return (getTrigger() == kNoRegulation);
}

int DigitalRegulator::setIsBypassed(bool bypassIt)
{
    // Do nothing if the value isn't changing.
    if (isBypassed() == bypassIt)
    {
        return kPMUSuccess;
    }
    
    if (bypassIt)
    {
        setTrigger(kNoRegulation);
    }
    else
    {
        // Turning off bypass, so return to the nominal output voltage.
        setOutputMillivolts(kDefaultOutputMillivolts);
    }

    return kPMUSuccess;
}

uint32_t DigitalRegulator::getOutputMillivolts() const
{
    uint32_t trigger = getTrigger();
    
    // Handle special trigger values.
    if (trigger == kPowerGated || trigger == kNoRegulation)
    {
        return m_minSafeMillivolts;
    }
    
    // Convert the trigger to millivolts.
    return m_minMillivolts + getTrigger() * _25_mV;
}

int DigitalRegulator::setOutputMillivolts(uint32_t mV)
{
    // First check the safe voltage range.
    if (!m_isSafetyOverrideEnabled && (mV < m_minSafeMillivolts || mV > m_maxSafeMillivolts))
    {
        return kPMUError_UnsafeVoltage;
    }
    
    // Validate low end of the voltage range. The high end is checked below.
    if (mV < m_minMillivolts)
    {
        return kPMUError_ValueOutOfRange;
    }
    
    // Calculate the trigger and make sure it's valid.
    uint32_t trigger = kMinDigitalTriggerValue + (mV - m_minMillivolts) / _25_mV;
    if (trigger > kMaxDigitalTriggerValue)
    {
        return kPMUError_ValueOutOfRange;
    }
    
    // Passed all checks, so set the new voltage.
    setTrigger(trigger);
    
    return kPMUSuccess;
}

uint32_t DigitalRegulator::getBrownoutMillivolts() const
{
    return getOutputMillivolts() - _75_mV - getBrownout() * _25_mV;
}

int DigitalRegulator::setBrownoutMillivolts(uint32_t mV)
{
    uint32_t output_mV = getOutputMillivolts();
    
    // Brownout must be at least 75 mV below the output voltage.
    if (mV > output_mV - _75_mV)
    {
        return kPMUError_ValueOutOfRange;
    }
    
    // Compute the offset value.
    uint32_t offset = (output_mV - _75_mV - mV) / _25_mV;
    if (offset > kMaxBrownoutOffsetValue)
    {
        return kPMUError_ValueOutOfRange;
    }
    
    return kPMUSuccess;
}

bool DigitalRegulator::isEnabled() const
{
    return getTrigger() != kPowerGated;
}

int DigitalRegulator::setIsEnabled(bool enableIt)
{
    // Don't do anything if the value isn't changing.
    if (isEnabled() == enableIt)
    {
        return kPMUSuccess;
    }
    
    if (!enableIt)
    {
        setTrigger(kPowerGated);
    }
    else
    {
        // Enabling when it was disabled, so return to the nominal output voltage.
        setOutputMillivolts(kDefaultOutputMillivolts);
    }
    return kPMUSuccess;
}

//------------------------------------------------------------------------------

LDO1p1Regulator::LDO1p1Regulator()
:   AnalogRegulator(HW_PMU_REG_1P1)
{
    setVoltageRange(kLdo1p1MinVoltage, kLdo1p1MinSafeVoltage, kLdo1p1MaxSafeVoltage);
}

//! We must override the get property handlers for max output voltage, since the 1p1
//! regulator has a special limited range.
int LDO1p1Regulator::getProperty(pmu_property_t selector, void * value)
{
    int status = kPMUSuccess;
    
    switch (selector)
    {
        case kPMUProperty_MaxOutputMillivolts:
            *reinterpret_cast<uint32_t *>(value) = m_isSafetyOverrideEnabled
                ? (m_minMillivolts + k1p1TriggerValueRange * _25_mV)
                : m_maxSafeMillivolts;
            break;
        
        default:
            status = AnalogRegulator::getProperty(selector, value);
    }
    
    return status;
}

//! The 1p1 regulator's minimum trigger setting is 0x04 for 800 mV.
uint32_t LDO1p1Regulator::getOutputMillivolts() const
{
    return m_minMillivolts + (m_controlRegister.B.OUTPUT_TRG - kMin1p1TriggerValue) * _25_mV;
}

int LDO1p1Regulator::setOutputMillivolts(uint32_t mV)
{
    // First check the safe voltage range.
    if (!m_isSafetyOverrideEnabled && (mV < m_minSafeMillivolts || mV > m_maxSafeMillivolts))
    {
        return kPMUError_UnsafeVoltage;
    }
    
    // Validate low end of the voltage range. The high end is checked below.
    if (mV < m_minMillivolts)
    {
        return kPMUError_ValueOutOfRange;
    }
    
    // Calculate the trigger and make sure it's valid.
    uint32_t trigger = (mV - m_minMillivolts) / _25_mV;
    if (trigger > k1p1TriggerValueRange)
    {
        return kPMUError_ValueOutOfRange;
    }
    
    // Shift the trigger to its minimum value of 0x4 for 800mV.
    trigger += kMin1p1TriggerValue;
    
    // Passed all checks, so set the new voltage.
    m_controlRegister.B.OUTPUT_TRG = trigger;
    
    return kPMUSuccess;
}

//------------------------------------------------------------------------------

LDO2p5Regulator::LDO2p5Regulator()
:   AnalogRegulator(HW_PMU_REG_2P5)
{
    setVoltageRange(kLdo2p5MinVoltage, kLdo2p5MinSafeVoltage, kLdo2p5MaxSafeVoltage);
}

//------------------------------------------------------------------------------

LDO3p0Regulator::LDO3p0Regulator()
:   AnalogRegulator(HW_PMU_REG_3P0)
{
    setVoltageRange(kLdo3p0MinVoltage, kLdo3p0MinSafeVoltage, kLdo3p0MaxSafeVoltage);
}

int LDO3p0Regulator::getProperty(pmu_property_t selector, void * value)
{
    int status = kPMUSuccess;
    
    switch (selector)
    {
        case kPMUProperty_PulldownIsEnabled:
            status = kPMUError_UnsupportedProperty;
            break;
        
        default:
            status = AnalogRegulator::getProperty(selector, value);
    }
    
    return status;
}

int LDO3p0Regulator::setProperty(pmu_property_t selector, const void * value)
{
    int status = kPMUSuccess;
    
    switch (selector)
    {
        case kPMUProperty_PulldownIsEnabled:
            status = kPMUError_UnsupportedProperty;
            break;
        
        default:
            return AnalogRegulator::setProperty(selector, value);
    }
    
    return status;
}

//------------------------------------------------------------------------------

LDOARMRegulator::LDOARMRegulator()
:   DigitalRegulator()
{
    setVoltageRange(kLdoCoreMinVoltage, kLdoArmMinSafeVoltage, kLdoArmMaxSafeVoltage);
}

int LDOARMRegulator::setBrownoutDetectIsEnabled(bool enableIt)
{
    HW_PMU_MISC2.B.REG0_ENABLE_BO = enableIt;
    return kPMUSuccess;
}

int LDOARMRegulator::setRampRate(uint32_t rate)
{
    if (rate > kPMURate_VerySlow)
    {
        return kPMUError_ValueOutOfRange;
    }
    
    HW_PMU_MISC2.B.REG0_STEP_TIME = rate;
    
    return kPMUSuccess;
}

//------------------------------------------------------------------------------

LDOGraphicsRegulator::LDOGraphicsRegulator()
:   DigitalRegulator()
{
    setVoltageRange(kLdoCoreMinVoltage, kLdoGraphicsMinSafeVoltage, kLdoGraphicsMaxSafeVoltage);
}

int LDOGraphicsRegulator::setBrownoutDetectIsEnabled(bool enableIt)
{
    HW_PMU_MISC2.B.REG1_ENABLE_BO = enableIt;
    return kPMUSuccess;
}

int LDOGraphicsRegulator::setRampRate(uint32_t rate)
{
    if (rate > kPMURate_VerySlow)
    {
        return kPMUError_ValueOutOfRange;
    }
    
    HW_PMU_MISC2.B.REG1_STEP_TIME = rate;
    
    return kPMUSuccess;
}

//------------------------------------------------------------------------------

LDOSoCRegulator::LDOSoCRegulator()
:   DigitalRegulator()
{
    setVoltageRange(kLdoCoreMinVoltage, kLdoSoCMinSafeVoltage, kLdoSoCMaxSafeVoltage);
}

int LDOSoCRegulator::setBrownoutDetectIsEnabled(bool enableIt)
{
    HW_PMU_MISC2.B.REG2_ENABLE_BO = enableIt;
    return kPMUSuccess;
}

int LDOSoCRegulator::setRampRate(uint32_t rate)
{
    if (rate > kPMURate_VerySlow)
    {
        return kPMUError_ValueOutOfRange;
    }
    
    HW_PMU_MISC2.B.REG2_STEP_TIME = rate;
    
    return kPMUSuccess;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
