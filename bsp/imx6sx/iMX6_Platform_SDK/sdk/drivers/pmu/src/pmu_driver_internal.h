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
#if !defined(__PMU_DRIVER_INTERNAL_H__)
#define __PMU_DRIVER_INTERNAL_H__

extern "C" {
#include "pmu/pmu_driver.h"
#include "interrupt.h"
#include "irq_numbers.h"
#include "registers/regspmu.h"
}

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)

namespace pmu {

//! @brief Number of regulators in the PMU.
const unsigned kRegulatorCount = 6;

//! @brief Constants for voltage values.
//!
//! Voltage ranges as documented in the datasheet:
//!
//! @b LDO_SOC
//! - HDMI_VP: 0.99-1.21
//! - SATA_VP: 0.99-1.21
//! - PCIE_VP: 1.023-1.21
//! - PCIE_VPTX: 1.023-1.21
//!
//! @b LDO_2P5
//! - HDMI_VPH: 2.25-2.75
//! - SATA_VPH: 2.25-2.75
//! - PCIE_VPH: 2.325-2.75
//! - NVCC_MIPI: 2.25-2.75
//! - NVCC_LVDS2P5: 2.25-2.75
//!
//! @b LDO_ARM
//! - max = 1.3V
//! - run @ 1.0GHz = 1.225V-1.3V
//! - standby = 0.9-1.0V
//!
//! Voltages at startup (?), as dumped from pmu_test:
//! - REG_1P1 = 1200 mV
//! - REG_2P5 = 2400 mV
//! - REG_3P0 = 3000 mV
//! - REG_ARM = 1125 mV
//! - REG_PU = 1125 mV
//! - REG_SOC = 1125 mV
//!
enum _pmu_voltage_constants
{
    _25_mV = 25,        //!< 25mV.
    _75_mV = 75,        //!< 75mV.

//     _725_mV = 725,      //!< 0.725V.
//     _800_mV = 800,      //!< 0.8V
//     _900_mV = 900,      //!< 0.9V
//     _1210_mV = 1210,    //!< 1.21V
//     _2000_mV = 2000,    //!< 2.0V
//     _2325_mV = 2325,    //!< 2.325V
//     _2625_mV = 2625,    //!< 2.625V
//     _2750_mV = 2750,     //!< 2.75V
    
    kLdo1p1MinVoltage = 800,
    kLdo1p1MinSafeVoltage = 900,
    kLdo1p1MaxSafeVoltage = 1300,
    
    kLdo2p5MinVoltage = 2000,
    kLdo2p5MinSafeVoltage = 2350,
    kLdo2p5MaxSafeVoltage = 2750,

    kLdo3p0MinVoltage = 2625,
    kLdo3p0MinSafeVoltage = 2900,
    kLdo3p0MaxSafeVoltage = 3100,
    
    kLdoCoreMinVoltage = 725,
    
    kLdoArmMinSafeVoltage = 900,
    kLdoArmMaxSafeVoltage = 1300,

    kLdoGraphicsMinSafeVoltage = 900,
    kLdoGraphicsMaxSafeVoltage = 1300,

    kLdoSoCMinSafeVoltage = 900,
    kLdoSoCMaxSafeVoltage = 1300
};

/*!
 * @brief Base class for the LDO regulators in the PMU.
 */
class Regulator
{
public:

    //! @brief Default constructor.
    Regulator()
    :   m_brownoutHandler(0),
        m_minMillivolts(0),
        m_minSafeMillivolts(0),
        m_maxSafeMillivolts(0)
    {}

    //! @name Property access
    //@{
        //! @brief Read a property's current value.
        virtual int getProperty(pmu_property_t selector, void * value);
        
        //! @brief Change the value of a property.
        virtual int setProperty(pmu_property_t selector, const void * value);
    //@}

    //! @name Brownout
    //@{
        //! @brief Change the brownout handler routine.
        void setBrownoutHandler(pmu_bo_handler_t handler) { m_brownoutHandler = handler; }
        
        //! @brief Get the brownout handler.
        pmu_bo_handler_t getBrownoutHandler() { return m_brownoutHandler; }
        
        //! @brief Returns the current brownout voltage.
        virtual uint32_t getBrownoutMillivolts() const=0;
        
        //! @brief Changes the brownout voltage.
        virtual int setBrownoutMillivolts(uint32_t mV)=0;
    
        //! @brief Returns whether the brownout detector is enabled.
        virtual bool isBrownoutDetectEnabled() const=0;
        
        //! @brief Enables or disables the brownout detector.
        virtual int setBrownoutDetectIsEnabled(bool enableIt)=0;
    
        //! @brief Returns whether the regulator is browning out.
        virtual bool isInBrownout() const=0;
    //@}
    
    //! @name Output voltage
    //@{
        //! @brief Gets the current target output voltage for the regulator.
        virtual uint32_t getOutputMillivolts() const=0;
        
        //! @brief Set a new output voltage.
        virtual int setOutputMillivolts(uint32_t mV)=0;
    //@}
    
    //! @name Enabled status
    //@{
        //! @brief Returns whether the regulator is enabled.
        virtual bool isEnabled() const=0;
        
        //! @brief Enable or disable the regulator.
        virtual int setIsEnabled(bool enableIt)=0;
    //@}
    
    //! @name Functioning properly status
    //@{
        //! @brief Returns whether the regulator is functioning properly.
        virtual bool isOK() const=0;
    //@}

protected:
    
    //! @brief Constants for the output trigger of the regulators.
    enum _trigger_constants
    {
        kMaxOutputTriggerValue = 0x1f,  //!< 5 bits
        kMaxBrownoutOffsetValue = 0x7   //!< 3 bits
    };
    
    pmu_bo_handler_t m_brownoutHandler; //!< The brownout handler routine for this regulator.
    uint32_t m_minMillivolts;  //!< Output voltage with the trigger set to 0.
    uint32_t m_minSafeMillivolts;   //!< Minimum safe voltage.
    uint32_t m_maxSafeMillivolts;   //!< Maximum safe voltage.
    bool m_isSafetyOverrideEnabled; //!< True if safe voltage range checks are disabled.
    
    void setVoltageRange(uint32_t min_mV, uint32_t minSafe_mV, uint32_t maxSafe_mV);
};

/*!
 * @brief Represents an analog regulator.
 *
 * Used for REG_1P1 and REG_2P5.
 */
class AnalogRegulator : public Regulator
{
public:

    //! @brief Constructor.
    AnalogRegulator(volatile hw_pmu_reg_1p1_t & reg)
    :   Regulator(),
        m_controlRegister(reg)
    {}

    //! @brief Template constructor used to pass other register pointers.
    //!
    //! This constructor exists so that a pointer to a register other than HW_PMU_REG_1P1
    //! can be passed without casting. Obviously, the provided register must be compatible
    //! with HW_PMU_REG_1P1.
    template <typename T>
    AnalogRegulator(volatile T & reg)
    :   Regulator(),
        m_controlRegister(*reinterpret_cast<volatile hw_pmu_reg_1p1_t *>(&reg))
    {}

    //! @name Property access
    //@{
        //! @copydoc Regulator::getProperty()
        virtual int getProperty(pmu_property_t selector, void * value);
        
        //! @copydoc Regulator::setProperty()
        virtual int setProperty(pmu_property_t selector, const void * value);
    //@}    

    //! @name Brownout
    //@{
        //! @copydoc Regulator::getBrownoutMillivolts()
        virtual uint32_t getBrownoutMillivolts() const;
        
        //! @copydoc Regulator::setBrownoutMillivolts()
        virtual int setBrownoutMillivolts(uint32_t mV);
    
        //! @copydoc Regulator::isBrownoutDetectEnabled()
        virtual bool isBrownoutDetectEnabled() const;
        
        //! @copydoc Regulator::setBrownoutDetectIsEnabled
        virtual int setBrownoutDetectIsEnabled(bool enableIt);
    //@}
    
    //! @name Output voltage
    //@{
        //! @copydoc Regulator::getOutputMillivolts()
        virtual uint32_t getOutputMillivolts() const;
        
        //! @copydoc Regulator::setOutputMillivolts()
        virtual int setOutputMillivolts(uint32_t mV);
    //@}
    
    //! @name Enabled status
    //@{
        //! @copydoc Regulator::isEnabled()
        virtual bool isEnabled() const;
        
        //! @copydoc Regulator::setIsEnabled()
        virtual int setIsEnabled(bool enableIt);
    //@}

protected:
    volatile hw_pmu_reg_1p1_t & m_controlRegister;  //!< Register used to control the regulator.
};

/*!
 * @brief Represents an REG_1P1.
 *
 * One difference with the other two analog regulators (2p5 and 3p0) is that 1p1 has a
 * limited range of OUTPUT_TRG settings. The value must be between 0x04 and 0x1b, inclusive.
 * For the other analog regulators, the full range of 0 through 0x1f is allowed.
 */
class LDO1p1Regulator : public AnalogRegulator
{
public:
    //! @brief Constructor.
    LDO1p1Regulator();

    //! @name Property access
    //@{
        //! @copydoc Regulator::getProperty();
        virtual int getProperty(pmu_property_t selector, void * value);
    //@}    
    
    //! @name Status
    //@{
        //! @copydoc Regulator::isInBrownout()
        virtual bool isInBrownout() const { return isBrownoutDetectEnabled() && HW_PMU_REG_1P1.B.BO_VDD1P1 == 1; }
        
        //! @copydoc Regulator::isOK()
        virtual bool isOK() const { return !isBrownoutDetectEnabled() || HW_PMU_REG_1P1.B.OK_VDD1P1 == 1; }
    //@}
    
    //! @name Output voltage
    //@{
        //! @copydoc Regulator::getOutputMillivolts()
        virtual uint32_t getOutputMillivolts() const;
        
        //! @copydoc Regulator::setOutputMillivolts()
        virtual int setOutputMillivolts(uint32_t mV);
    //@}

protected:

    //! @brief Constants for the LDO_1P1 output trigger value.
    enum _1p1_trigger_constants
    {
        kMin1p1TriggerValue = 0x4,
        kMax1p1TriggerValue = 0x1b,
        k1p1TriggerValueRange = kMax1p1TriggerValue - kMin1p1TriggerValue
    };
};

/*!
 * @brief Represents an REG_2P5.
 */
class LDO2p5Regulator : public AnalogRegulator
{
public:
    //! @brief Constructor.
    LDO2p5Regulator();
    
    //! @name Status
    //@{
        //! @copydoc Regulator::isInBrownout()
        virtual bool isInBrownout() const { return isBrownoutDetectEnabled() && HW_PMU_REG_2P5.B.BO_VDD2P5 == 1; }
        
        //! @copydoc Regulator::isOK()
        virtual bool isOK() const { return !isBrownoutDetectEnabled() || HW_PMU_REG_2P5.B.OK_VDD2P5 == 1; }
    //@}

protected:
};

/*!
 * @brief Represents an REG_3P0.
 *
 * Used exclusively for REG_3P0, since it has a few minor variations from 1p1 and 2p5.
 */
class LDO3p0Regulator : public AnalogRegulator
{
public:

    //! @brief Constructor.
    LDO3p0Regulator();

    //! @name Property access
    //@{
        //! @copydoc Regulator::getProperty();
        virtual int getProperty(pmu_property_t selector, void * value);
        
        //! @copydoc Regulator::setProperty();
        virtual int setProperty(pmu_property_t selector, const void * value);
    //@}    
    
    //! @name Status
    //@{
        //! @copydoc Regulator::isInBrownout()
        virtual bool isInBrownout() const { return isBrownoutDetectEnabled() && HW_PMU_REG_3P0.B.BO_VDD3P0 == 1; }
        
        //! @copydoc Regulator::isOK()
        virtual bool isOK() const { return !isBrownoutDetectEnabled() || HW_PMU_REG_3P0.B.OK_VDD3P0 == 1; }
    //@}
    

protected:
};

/*!
 * @brief Represents a digital regulator.
 *
 * Used for REG_ARM_CORE, REG_PU, and REG_SOC.
 */
class DigitalRegulator : public Regulator
{
public:
    //! @brief Constants for the output trigger of the digital regulators.
    enum _trigger_constants
    {
        kPowerGated = 0x00, //!< Power is gated off.
        kMinDigitalTriggerValue = 0x1,
        kMaxDigitalTriggerValue = 0x1e,
        kDigitalTriggerValueRange = kMaxDigitalTriggerValue - kMinDigitalTriggerValue,
        kNoRegulation = 0x1f,  //!< Power FET switched full on. No regulation.
        
        kDefaultOutputMillivolts = 1100
    };

    //! @brief Constructor.
    DigitalRegulator();

    //! @name Property access
    //@{
        //! @copydoc Regulator::getProperty();
        virtual int getProperty(pmu_property_t selector, void * value);
        
        //! @copydoc Regulator::setProperty();
        virtual int setProperty(pmu_property_t selector, const void * value);
    //@}    
    
    //! @name Brownout
    //@{
        //! @copydoc Regulator::getBrownoutMillivolts()
        virtual uint32_t getBrownoutMillivolts() const;
        
        //! @copydoc Regulator::setBrownoutMillivolts()
        virtual int setBrownoutMillivolts(uint32_t mV);
    //@}
    
    //! @name Output voltage
    //@{
        //! @copydoc Regulator::getOutputMillivolts()
        virtual uint32_t getOutputMillivolts() const;
        
        //! @copydoc Regulator::setOutputMillivolts()
        virtual int setOutputMillivolts(uint32_t mV);
        
        virtual bool isBypassed() const;

        virtual int setIsBypassed(bool bypassIt);
    //@}
    
    //! @name Enabled status
    //@{
        //! @copydoc Regulator::isEnabled()
        virtual bool isEnabled() const;
        
        //! @copydoc Regulator::setIsEnabled()
        virtual int setIsEnabled(bool enableIt);
    //@}
    
    //! @name Ramp rate
    //@{
        //! @brief Get the current ramp rate.
        virtual uint32_t getRampRate() const=0;
        
        //! @brief Change the ramp rate.
        virtual int setRampRate(uint32_t rate)=0;
    //@}

protected:

    //! @brief Returns the unmodified value of the trigger bitfield.
    virtual uint32_t getTrigger() const=0;
    
    //! @brief Change the output trigger value.
    virtual void setTrigger(uint32_t trigger)=0;
    
    //! @brief Returns the unmodified value of the brownout offset bitfield.
    virtual uint32_t getBrownout() const=0;
    
    //! @brief Change the brownout offset value.
    virtual void setBrownout(uint32_t offset)=0;
    
};

/*!
 * @brief Represents the REG_ARM.
 */
class LDOARMRegulator : public DigitalRegulator
{
public:
    //! @brief Constructor.
    LDOARMRegulator();
    
    //! @name Status
    //@{
        //! @copydoc Regulator::isBrownoutDetectEnabled()
        virtual bool isBrownoutDetectEnabled() const { return HW_PMU_MISC2.B.REG0_ENABLE_BO; }
        
        //! @copydoc Regulator::setBrownoutDetectIsEnabled
        virtual int setBrownoutDetectIsEnabled(bool enableIt);

        //! @copydoc Regulator::isInBrownout()
        virtual bool isInBrownout() const { return isBrownoutDetectEnabled() && HW_PMU_MISC2.B.REG0_BO_STATUS == 1; }
        
        //! @copydoc Regulator::isOK()
        virtual bool isOK() const { return true; /*HW_PMU_MISC2.B.REG0_OK == 1;*/ }
    //@}
    
    //! @name Ramp rate
    //@{
        //! @brief Get the current ramp rate.
        virtual uint32_t getRampRate() const { return HW_PMU_MISC2.B.REG0_STEP_TIME; }
        
        //! @brief Change the ramp rate.
        virtual int setRampRate(uint32_t rate);
    //@}

protected:

    virtual uint32_t getTrigger() const { return HW_PMU_REG_CORE.B.REG0_TARG; }
    
    virtual void setTrigger(uint32_t trigger) { HW_PMU_REG_CORE.B.REG0_TARG = trigger; }

    virtual uint32_t getBrownout() const { return HW_PMU_MISC2.B.REG0_BO_OFFSET; }

    virtual void setBrownout(uint32_t offset) { HW_PMU_MISC2.B.REG0_BO_OFFSET = offset; }

};

/*!
 * @brief Represents the REG_PU.
 */
class LDOGraphicsRegulator : public DigitalRegulator
{
public:
    //! @brief Constructor.
    LDOGraphicsRegulator();
    
    //! @name Status
    //@{
        //! @copydoc Regulator::isBrownoutDetectEnabled()
        virtual bool isBrownoutDetectEnabled() const { return HW_PMU_MISC2.B.REG1_ENABLE_BO; }
        
        //! @copydoc Regulator::setBrownoutDetectIsEnabled
        virtual int setBrownoutDetectIsEnabled(bool enableIt);

        //! @copydoc Regulator::isInBrownout()
        virtual bool isInBrownout() const { return isBrownoutDetectEnabled() && HW_PMU_MISC2.B.REG1_BO_STATUS == 1; }
        
        //! @copydoc Regulator::isOK()
        virtual bool isOK() const { return true; /*HW_PMU_MISC2.B.REG0_OK == 1;*/ }
    //@}
    
    //! @name Ramp rate
    //@{
        //! @brief Get the current ramp rate.
        virtual uint32_t getRampRate() const { return HW_PMU_MISC2.B.REG1_STEP_TIME; }
        
        //! @brief Change the ramp rate.
        virtual int setRampRate(uint32_t rate);
    //@}

protected:

    virtual uint32_t getTrigger() const { return HW_PMU_REG_CORE.B.REG1_TARG; }
    
    virtual void setTrigger(uint32_t trigger) { HW_PMU_REG_CORE.B.REG1_TARG = trigger; }

    virtual uint32_t getBrownout() const { return HW_PMU_MISC2.B.REG1_BO_OFFSET; }

    virtual void setBrownout(uint32_t offset) { HW_PMU_MISC2.B.REG1_BO_OFFSET = offset; }

};

/*!
 * @brief Represents the REG_SOC.
 */
class LDOSoCRegulator : public DigitalRegulator
{
public:
    //! @brief Constructor.
    LDOSoCRegulator();
    
    //! @name Status
    //@{
        //! @copydoc Regulator::isBrownoutDetectEnabled()
        virtual bool isBrownoutDetectEnabled() const { return HW_PMU_MISC2.B.REG2_ENABLE_BO; }
        
        //! @copydoc Regulator::setBrownoutDetectIsEnabled
        virtual int setBrownoutDetectIsEnabled(bool enableIt);

        //! @copydoc Regulator::isInBrownout()
        virtual bool isInBrownout() const { return isBrownoutDetectEnabled() && HW_PMU_MISC2.B.REG2_BO_STATUS == 1; }
        
        //! @copydoc Regulator::isOK()
        virtual bool isOK() const { return !isBrownoutDetectEnabled() || HW_PMU_MISC2.B.REG2_OK == 1; }
    //@}
    
    //! @name Ramp rate
    //@{
        //! @brief Get the current ramp rate.
        virtual uint32_t getRampRate() const { return HW_PMU_MISC2.B.REG2_STEP_TIME; }
        
        //! @brief Change the ramp rate.
        virtual int setRampRate(uint32_t rate);
    //@}

protected:

    virtual uint32_t getTrigger() const { return HW_PMU_REG_CORE.B.REG2_TARG; }
    
    virtual void setTrigger(uint32_t trigger) { HW_PMU_REG_CORE.B.REG2_TARG = trigger; }

    virtual uint32_t getBrownout() const { return HW_PMU_MISC2.B.REG2_BO_OFFSET; }

    virtual void setBrownout(uint32_t offset) { HW_PMU_MISC2.B.REG2_BO_OFFSET = offset; }
    
};

/*!
 * @brief State information for the PMU driver.
 *
 * Holds the object instances for each of the LDO regulators in the PMU.
 */
typedef struct _pmu_info {
    bool isInited;
    LDO1p1Regulator ldo1p1;
    LDO2p5Regulator ldo2p5;
    LDO3p0Regulator ldo3p0;
    LDOARMRegulator ldoArm;
    LDOGraphicsRegulator ldoGraphics;
    LDOSoCRegulator ldoSoC;
} pmu_info_t;

} // namespace pmu

#endif // defined(__cplusplus)

#endif // __PMU_DRIVER_INTERNAL_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
