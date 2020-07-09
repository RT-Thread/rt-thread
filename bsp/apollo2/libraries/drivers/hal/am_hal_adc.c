//*****************************************************************************
//
//  am_hal_adc.c
//! @file
//!
//! @brief Functions for interfacing with the Analog to Digital Converter.
//!
//! @addtogroup adc2 Analog-to-Digital Converter (ADC)
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
//! @brief Private SRAM view of temperature trims.
//!
//! This static SRAM union is private to the ADC HAL functions.
//
//*****************************************************************************
static union
{
    //! These trim values are loaded as uint32_t values.
    struct
    {
              //! Temperature of the package test head (in degrees Kelvin)
              uint32_t ui32CalibrationTemperature;

              //! Voltage corresponding to temperature measured on test head.
              uint32_t ui32CalibrationVoltage;

              //! ADC offset voltage measured on the package test head.
              uint32_t ui32CalibrationOffset;

              //! Flag if default (guess) or measured.
              bool bMeasured;
    } ui32;
    //! These trim values are accessed as floats when used in temp calculations.
    struct
    {
              //! Temperature of the package test head in degrees Kelvin
              float    fCalibrationTemperature;

              //! Voltage corresponding to temperature measured on test head.
              float    fCalibrationVoltage;

              //! ADC offset voltage measured on the package test head.
              float    fCalibrationOffset;

              //! Flag if default (guess) or measured.
              float fMeasuredFlag;
    } flt;
} priv_temp_trims;

//*****************************************************************************
//
//! @brief Configure the ADC.
//!
//! @param psConfig - pointer to the configuration structure for the ADC.
//!
//! This function may be used to perform the initial setup of the ADC based on
//! setting found in a configuration structure.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_adc_config(am_hal_adc_config_t *psConfig)
{
    //
    // Set general ADC configuration parameters.
    //
    AM_REG(ADC, CFG) = (psConfig->ui32Clock |
                        psConfig->ui32TriggerConfig |
                        psConfig->ui32Reference |
                        psConfig->ui32ClockMode |
                        psConfig->ui32PowerMode |
                        psConfig->ui32Repeat |
                        AM_REG_ADC_CFG_ADCEN(1));

    //
    // Grab the temperature trims.
    //
    priv_temp_trims.ui32.ui32CalibrationTemperature =
                  am_hal_flash_load_ui32(AM_HAL_ADC_CALIB_TEMP_ADDR);
    priv_temp_trims.ui32.ui32CalibrationVoltage     =
                  am_hal_flash_load_ui32(AM_HAL_ADC_CALIB_AMBIENT_ADDR);
    priv_temp_trims.ui32.ui32CalibrationOffset      =
                  am_hal_flash_load_ui32(AM_HAL_ADC_CALIB_ADC_OFFSET_ADDR);

    if ( (priv_temp_trims.ui32.ui32CalibrationTemperature == 0xffffffff)    ||
         (priv_temp_trims.ui32.ui32CalibrationVoltage     == 0xffffffff)    ||
         (priv_temp_trims.ui32.ui32CalibrationOffset      == 0xffffffff) )
    {
        //
        // Since the device has not been calibrated on the tester, we'll load
        // default calibration values.  These default values should result
        // in worst-case temperature measurements of +-6 degress C.
        //
        priv_temp_trims.flt.fCalibrationTemperature = AM_HAL_ADC_CALIB_TEMP_DEFAULT;
        priv_temp_trims.flt.fCalibrationVoltage     = AM_HAL_ADC_CALIB_AMBIENT_DEFAULT;
        priv_temp_trims.flt.fCalibrationOffset      = AM_HAL_ADC_CALIB_ADC_OFFSET_DEFAULT;
        priv_temp_trims.ui32.bMeasured = false;
    }
    else
    {
        priv_temp_trims.ui32.bMeasured = true;
    }
}

//*****************************************************************************
//
//! @brief Get the temperature trim parameters after configuring the ADC.
//!
//! @param pfTemp - pointer to a location to store the calibration temperature.
//! @param pfVoltage - pointer to a location to store the calibration voltage.
//! @param pfOffsetV - pointer to a location to store the calibration offset.
//!
//! This function may be used to access the actual temperature sensor trim
//! values from the private structure.
//!
//! WARNING: only call this after the ADC has been configured with
//!          am_hal_adc_config.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_adc_temp_trims_get(float * pfTemp, float * pfVoltage, float * pfOffsetV)
{
    //
    // Return trim temperature as a float, if you can.
    //
    if ( pfTemp != NULL )
    {
        *pfTemp = priv_temp_trims.flt.fCalibrationTemperature;
    }

    //
    // Return trim voltage as a float, if you can.
    //
    if ( pfVoltage != NULL )
    {
        *pfVoltage = priv_temp_trims.flt.fCalibrationVoltage;
    }

    //
    // Return trim ADC offset voltage as a float, if you can.
    //
    if ( pfOffsetV != NULL )
    {
        *pfOffsetV = priv_temp_trims.flt.fCalibrationOffset;
    }
}

//*****************************************************************************
//
//! @brief Set the ADC window parameters.
//!
//! @param ui32Upper - the upper limit for the ADC window.
//! @param ui32Upper - the lower limit for the ADC window.
//!
//! This function may be used to change the ADC window parameters. Please note
//! that the upper and lower limits are only 16-bits wide in the ADC hardware.
//! This function will ignore the upper 16 bits of these arguments.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_adc_window_set(uint32_t ui32Upper, uint32_t ui32Lower)
{
    //
    // Set the window limits for the ADC.
    //
     AM_BFW(ADC, WULIM, ULIM, ui32Upper);
     AM_BFW(ADC, WLLIM, LLIM, ui32Lower);
}

//*****************************************************************************
//
//! @brief Configure a single ADC slot.
//!
//! @param ui32SlotNumber - the number of the ADC slot to be configured.
//! @param ui32SlotConfig - contains slot-specific options.
//!
//! This function may be used to configure the settings for an individual ADC
//! slot. The parameter \b ui32SlotConfig should be the logical 'OR' of a slot
//! average macro, a slot hold-time macro, a slot channel macro, and
//! optionally, the slot window enable macro.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_adc_slot_config(uint32_t ui32SlotNumber, uint32_t ui32SlotConfig)
{
    uint32_t ui32RegOffset;

    //
    // Make sure we're accessing a real slot.
    //
    am_hal_debug_assert_msg((ui32SlotNumber & 0xFFFFFFFF0) == 0,
                            "Trying to configure an ADC slot that doesn't exist.");

    //
    // Locate the correct register for this ADC slot.
    //
    ui32RegOffset = (AM_REG_ADCn(0) + AM_REG_ADC_SL0CFG_O + (4 * ui32SlotNumber));

    //
    // Write the register with the caller's configuration value.
    //
    AM_REGVAL(ui32RegOffset) = ui32SlotConfig;
}

//*****************************************************************************
//
//! @brief Peek at the next fifo entry.
//!
//! This function reads the oldest value in the ADC sample fifo but doesn't
//! actually advance the fifo to the next entry. This function is useful when
//! you need information from the fifo but you don't want to also empty the
//! fifo. This could be helpful if you want to check the FIFO depth without
//! pulling any data out.
//!
//! The value returned by this function is the raw 32-bit value provided by the
//! ADC hardware. In order to interpret this value, you will need to use one of
//! the following macros.
//!
//! @return 32-bit FIFO entry.
//!
//
//*****************************************************************************
uint32_t
am_hal_adc_fifo_peek(void)
{
    uint32_t ui32FIFOValue;

    //
    // Grab a value from the ADC FIFO.
    //
    ui32FIFOValue = AM_REG(ADC, FIFO);

    //
    // Return FIFO entry.
    //
    return ui32FIFOValue;
}

//*****************************************************************************
//
//! @brief
//!
//! This function reads the oldest value in the ADC fifo and then pops the
//! fifo. Use this function when you actually want to pull data out of the
//! fifo.
//!
//! @return 32-bit FIFO entry.
//!
//
//*****************************************************************************
uint32_t
am_hal_adc_fifo_pop(void)
{
    uint32_t ui32FIFOValue;

    //
    // Grab a value from the ADC FIFO.
    //
    ui32FIFOValue = AM_REG(ADC, FIFO);

    //
    // Pop the FIFO.
    //
    AM_REG(ADC, FIFO) = 0;

    //
    // Return FIFO valid bits.
    //
    return ui32FIFOValue;
}

//*****************************************************************************
//
//! @brief Issue Software Trigger to the ADC.
//!
//! This function issues the software trigger to the ADC.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_adc_trigger(void)
{
    //
    // Write to the Software trigger register in the ADC.
    //
    AM_REG(ADC, SWT) = 0x37;
}

//*****************************************************************************
//
//! @brief Enable the ADC.
//!
//! Use this function to enable the ADC.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_adc_enable(void)
{
    //
    // Enable the ADC.
    //
    AM_BFW(ADC, CFG, ADCEN, 0x1);
}

//*****************************************************************************
//
//! @brief Disable the ADC.
//!
//! Use this function to disable the ADC.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_adc_disable(void)
{
    //
    // Disable the ADC.
    //
    AM_BFW(ADC, CFG, ADCEN, 0x0);
}

//*****************************************************************************
//
//! @brief Enable selected ADC Interrupts.
//!
//! @param ui32Interrupt - Use the macro bit fields provided in am_hal_adc.h.
//!
//! Use this function to enable the ADC interrupts.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_adc_int_enable(uint32_t ui32Interrupt)
{
    //
    // Enable the interrupts.
    //
    AM_REG(ADC, INTEN) |= ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Return enabled ADC Interrupts.
//!
//! Use this function to get all enabled ADC interrupts.
//!
//! @return enabled ADC Interrupts.
//
//*****************************************************************************
uint32_t
am_hal_adc_int_enable_get(void)
{
    //
    // Return enabled interrupts.
    //
    return AM_REG(ADC, INTEN);
}

//*****************************************************************************
//
//! @brief Disable selected ADC Interrupts.
//!
//! @param ui32Interrupt - Use the macro bit fields provided in am_hal_adc.h.
//!
//! Use this function to disable the ADC interrupts.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_adc_int_disable(uint32_t ui32Interrupt)
{
    //
    // Disable the interrupts.
    //
    AM_REG(ADC, INTEN) &= ~ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Clear selected ADC Interrupts.
//!
//! @param ui32Interrupt - Use the macro bit fields provided in am_hal_adc.h.
//!
//! Use this function to clear the ADC interrupts.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_adc_int_clear(uint32_t ui32Interrupt)
{
    //
    // Clear the interrupts.
    //
    AM_REG(ADC, INTCLR) = ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Set selected ADC Interrupts.
//!
//! @param ui32Interrupt - Use the macro bit fields provided in am_hal_adc.h.
//!
//! Use this function to set the ADC interrupts.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_adc_int_set(uint32_t ui32Interrupt)
{
    //
    // Set the interrupts.
    //
    AM_REG(ADC, INTSET) = ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Return either enabled or raw selected ADC interrupt status.
//!
//! @param bEnabledOnly - return the status of only the enabled interrupts.
//!
//! Use this function to get the ADC interrupt status.
//!
//! @return enabled or raw ADC interrupt status.
//
//*****************************************************************************
uint32_t
am_hal_adc_int_status_get(bool bEnabledOnly)
{
    //
    // Return the status.
    //
    if (bEnabledOnly)
    {
        uint32_t u32RetVal = AM_REG(ADC, INTEN);
        u32RetVal &= AM_REG(ADC, INTSTAT);
        return u32RetVal;
    }
    else
    {
        return AM_REG(ADC, INTSTAT);
    }
}

//*****************************************************************************
//
//! @brief Return temperature in degrees C of supplied voltage.
//!
//! @param fVoltage - return the temperature corresponding to this voltage.
//!
//! Use this function to convert volts from the temperature sensor into degrees
//! C.  Caller converts ADC binary code to volts based on reference used.
//! This routine looks up the trim parameters and returns corrected temperature.
//!
//! The computation is based on a line running through 0 degrees K.
//! We find the slope from the trimmed temperature calibration point.
//!
//!
//! @return the temperature in degrees C.
//
//*****************************************************************************
float
am_hal_adc_volts_to_celsius(float fVoltage)
{
    float fTemp;

    //
    // Get calibration temperature from trimmed values & convert to degrees K.
    //
    float fCalibration_temp = priv_temp_trims.flt.fCalibrationTemperature;

    //
    // Get remaining trimmed values.
    //
    float fCalibration_voltage = priv_temp_trims.flt.fCalibrationVoltage;
    float fCalibration_offset  = priv_temp_trims.flt.fCalibrationOffset;

    //
    // Compute the temperature.
    //
    fTemp  = fCalibration_temp;
    fTemp /= (fCalibration_voltage - fCalibration_offset);
    fTemp *= (fVoltage - fCalibration_offset);

    //
    // Give it back to the caller in Celsius.
    //
    return fTemp - 273.15f;
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
