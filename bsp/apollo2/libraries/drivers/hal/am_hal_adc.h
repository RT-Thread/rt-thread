//*****************************************************************************
//
//  am_hal_adc.h
//! @file
//!
//! @brief Functions for interfacing with the Analog to Digital Converter
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
#ifndef AM_HAL_ADC_H
#define AM_HAL_ADC_H

//*****************************************************************************
//
//! @name Clock Selection
//! @brief These macros may be used to set the ADC module's clock source.
//! @{
//
//*****************************************************************************
#define AM_HAL_ADC_CLOCK_OFF                AM_REG_ADC_CFG_CLKSEL_OFF
#define AM_HAL_ADC_CLOCK_HFRC               AM_REG_ADC_CFG_CLKSEL_HFRC
#define AM_HAL_ADC_CLOCK_DIV2               AM_REG_ADC_CFG_CLKSEL_HFRC_DIV2
//! @}

//*****************************************************************************
//
//! @name Trigger Settings
//! @brief ADC trigger setting macros.
//!
//! These macros alter the ADC's trigger source and trigger polarity. Note that
//! the external trigger setting needs to be ORed with a POS or NEG option to
//! define the desired trigger polarity.
//! @{
//
//*****************************************************************************
#define AM_HAL_ADC_TRIGGER_SOFT             AM_REG_ADC_CFG_TRIGSEL_SWT
#define AM_HAL_ADC_TRIGGER_VCOMP            AM_REG_ADC_CFG_TRIGSEL_VCOMP
#define AM_HAL_ADC_TRIGGER_EXT0             AM_REG_ADC_CFG_TRIGSEL_EXT0
#define AM_HAL_ADC_TRIGGER_EXT1             AM_REG_ADC_CFG_TRIGSEL_EXT1
#define AM_HAL_ADC_TRIGGER_EXT2             AM_REG_ADC_CFG_TRIGSEL_EXT2
#define AM_HAL_ADC_TRIGGER_EXT3             AM_REG_ADC_CFG_TRIGSEL_EXT3
#define AM_HAL_ADC_TRIGGER_FALL             AM_REG_ADC_CFG_TRIGPOL_FALLING_EDGE
#define AM_HAL_ADC_TRIGGER_RISE             AM_REG_ADC_CFG_TRIGPOL_RISING_EDGE
//! @}

//*****************************************************************************
//
//! @name Reference Settings
//! @brief ADC reference voltage setting macros.
//!
//! These macros control the ADC reference voltage source.
//! @{
//
//*****************************************************************************
#define AM_HAL_ADC_REF_EXT_2P0              AM_REG_ADC_CFG_REFSEL_EXT2P0
#define AM_HAL_ADC_REF_EXT_1P5              AM_REG_ADC_CFG_REFSEL_EXT1P5
#define AM_HAL_ADC_REF_INT_2P0              AM_REG_ADC_CFG_REFSEL_INT2P0
#define AM_HAL_ADC_REF_INT_1P5              AM_REG_ADC_CFG_REFSEL_INT1P5
//! @}

//*****************************************************************************
//
//! @name Clock Mode
//! @brief ADC clock mode settings
//!
//! These macros determine whether the ADC shuts down its clock between
//! samples. Shutting down the clock will reduce power consumption, but
//! increase latency. This setting is only valid for LPMODE 0. For other modes,
//! it will be ignored.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_ADC_CK_LOW_POWER             AM_REG_ADC_CFG_CKMODE_LPCKMODE
#define AM_HAL_ADC_CK_LOW_LATENCY           AM_REG_ADC_CFG_CKMODE_LLCKMODE
//! @}

//*****************************************************************************
//
//! @name Low Power Mode
//! @brief ADC power conservation settings.
//!
//! These macros select the power state to enter between active scans. Each low
//! power mode has its own set of timing constraints. Please see the datasheet
//! for additional timing information on each power mode.
//! @{
//
//*****************************************************************************
#define AM_HAL_ADC_LPMODE_0                 AM_REG_ADC_CFG_LPMODE_MODE0
#define AM_HAL_ADC_LPMODE_1                 AM_REG_ADC_CFG_LPMODE_MODE1
//! @}

//*****************************************************************************
//
//! @name Repeat Mode
//! @brief Enable repeating scan mode.
//!
//! Use this macro to enable repeating scans using timer 3.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_ADC_REPEAT                   AM_REG_ADC_CFG_RPTEN(1)
#define AM_HAL_ADC_NO_REPEAT                AM_REG_ADC_CFG_RPTEN(0)
//! @}

//*****************************************************************************
//
//! @name Slot configuration
//! @brief Slot configuration macros
//!
//! These macros may be used to configure an individual ADC slot.
//! @{
//
//*****************************************************************************

// Set number of samples to average.
#define AM_HAL_ADC_SLOT_AVG_1               AM_REG_ADC_SL0CFG_ADSEL0(0)
#define AM_HAL_ADC_SLOT_AVG_2               AM_REG_ADC_SL0CFG_ADSEL0(1)
#define AM_HAL_ADC_SLOT_AVG_4               AM_REG_ADC_SL0CFG_ADSEL0(2)
#define AM_HAL_ADC_SLOT_AVG_8               AM_REG_ADC_SL0CFG_ADSEL0(3)
#define AM_HAL_ADC_SLOT_AVG_16              AM_REG_ADC_SL0CFG_ADSEL0(4)
#define AM_HAL_ADC_SLOT_AVG_32              AM_REG_ADC_SL0CFG_ADSEL0(5)
#define AM_HAL_ADC_SLOT_AVG_64              AM_REG_ADC_SL0CFG_ADSEL0(6)
#define AM_HAL_ADC_SLOT_AVG_128             AM_REG_ADC_SL0CFG_ADSEL0(7)

// Set slot precision mode.
#define AM_HAL_ADC_SLOT_14BIT               AM_REG_ADC_SL0CFG_PRMODE0_P14B
#define AM_HAL_ADC_SLOT_12BIT               AM_REG_ADC_SL0CFG_PRMODE0_P14B
#define AM_HAL_ADC_SLOT_10BIT               AM_REG_ADC_SL0CFG_PRMODE0_P14B
#define AM_HAL_ADC_SLOT_8BIT                AM_REG_ADC_SL0CFG_PRMODE0_P14B

// Select a channel by number.
#define AM_HAL_ADC_SLOT_CHANNEL(n)          AM_REG_ADC_SL0CFG_CHSEL0(n)

// Single-ended channels
#define AM_HAL_ADC_SLOT_CHSEL_SE0           AM_REG_ADC_SL0CFG_CHSEL0_SE0
#define AM_HAL_ADC_SLOT_CHSEL_SE1           AM_REG_ADC_SL0CFG_CHSEL0_SE1
#define AM_HAL_ADC_SLOT_CHSEL_SE2           AM_REG_ADC_SL0CFG_CHSEL0_SE2
#define AM_HAL_ADC_SLOT_CHSEL_SE3           AM_REG_ADC_SL0CFG_CHSEL0_SE3
#define AM_HAL_ADC_SLOT_CHSEL_SE4           AM_REG_ADC_SL0CFG_CHSEL0_SE4
#define AM_HAL_ADC_SLOT_CHSEL_SE5           AM_REG_ADC_SL0CFG_CHSEL0_SE5
#define AM_HAL_ADC_SLOT_CHSEL_SE6           AM_REG_ADC_SL0CFG_CHSEL0_SE6
#define AM_HAL_ADC_SLOT_CHSEL_SE7           AM_REG_ADC_SL0CFG_CHSEL0_SE7
#define AM_HAL_ADC_SLOT_CHSEL_SE8           AM_REG_ADC_SL0CFG_CHSEL0_SE8
#define AM_HAL_ADC_SLOT_CHSEL_SE9           AM_REG_ADC_SL0CFG_CHSEL0_SE9

// Differential channels.
#define AM_HAL_ADC_SLOT_CHSEL_DF0           AM_REG_ADC_SL0CFG_CHSEL0_DF0
#define AM_HAL_ADC_SLOT_CHSEL_DF1           AM_REG_ADC_SL0CFG_CHSEL0_DF1

// Miscellaneous other signals.
#define AM_HAL_ADC_SLOT_CHSEL_TEMP          AM_REG_ADC_SL0CFG_CHSEL0_TEMP
#define AM_HAL_ADC_SLOT_CHSEL_VSS           AM_REG_ADC_SL0CFG_CHSEL0_VSS
#define AM_HAL_ADC_SLOT_CHSEL_VBATT         AM_REG_ADC_SL0CFG_CHSEL0_BATT

// Window enable.
#define AM_HAL_ADC_SLOT_WINDOW_EN           AM_REG_ADC_SL0CFG_WCEN0(1)

// Enable the slot.
#define AM_HAL_ADC_SLOT_ENABLE              AM_REG_ADC_SL0CFG_SLEN0(1)
//! @}

//*****************************************************************************
//
//! @name Interrupt Status Bits
//! @brief Interrupt Status Bits for enable/disble use
//!
//! These macros may be used to enable an individual ADC interrupt cause.
//! @{
//
//*****************************************************************************
#define AM_HAL_ADC_INT_WCINC              AM_REG_ADC_INTEN_WCINC(1)
#define AM_HAL_ADC_INT_WCEXC              AM_REG_ADC_INTEN_WCEXC(1)
#define AM_HAL_ADC_INT_FIFOOVR2           AM_REG_ADC_INTEN_FIFOOVR2(1)
#define AM_HAL_ADC_INT_FIFOOVR1           AM_REG_ADC_INTEN_FIFOOVR1(1)
#define AM_HAL_ADC_INT_SCNCMP             AM_REG_ADC_INTEN_SCNCMP(1)
#define AM_HAL_ADC_INT_CNVCMP             AM_REG_ADC_INTEN_CNVCMP(1)
//! @}

//*****************************************************************************
//
//! @name Temperature Trim Value Locations
//! @brief Temperature calibration cofficients are stored in readable space.
//!
//! These macros are used to access the temperature trim values in readable
//! space.
//! @{
//
//*****************************************************************************
#define AM_HAL_ADC_CALIB_TEMP_ADDR          (0x50023010)
#define AM_HAL_ADC_CALIB_AMBIENT_ADDR       (0x50023014)
#define AM_HAL_ADC_CALIB_ADC_OFFSET_ADDR    (0x50023018)

//
// Default coefficients (used when trims not provided):
//  TEMP_DEFAULT    = Temperature in deg K (e.g. 299.5 - 273.15 = 26.35)
//  AMBIENT_DEFAULT = Voltage measurement at default temperature.
//  OFFSET_DEFAULT  = Default ADC offset at 1v.
//
#define AM_HAL_ADC_CALIB_TEMP_DEFAULT       (299.5F)
#define AM_HAL_ADC_CALIB_AMBIENT_DEFAULT    (1.02809F)
#define AM_HAL_ADC_CALIB_ADC_OFFSET_DEFAULT (-0.004281F)
//! @}

//*****************************************************************************
//
//! @brief Configuration structure for the ADC.
//
//*****************************************************************************
typedef struct
{
    //! Select the ADC Clock source using one of the clock source macros.
    uint32_t ui32Clock;

    //! Select the ADC trigger source using a trigger source macro.
    uint32_t ui32TriggerConfig;

    //! Use a macro to select the ADC reference voltage.
    uint32_t ui32Reference;

    //! Use a macro to decide whether to disable clocks between samples.
    uint32_t ui32ClockMode;

    //! Use a macro to select the ADC power mode.
    uint32_t ui32PowerMode;

    //! Select whether the ADC will re-trigger based on a signal from timer 3.
    uint32_t ui32Repeat;
}
am_hal_adc_config_t;

//*****************************************************************************
//
//! @brief ADC Fifo Read macros
//!
//! These are helper macros for interpreting FIFO data. Each ADC FIFO entry
//! contains information about the slot number and the FIFO depth alongside the
//! current sample. These macros perform the correct masking and shifting to
//! read those values.
//!
//! The SAMPLE and FULL_SAMPLE options refer to the fractional part of averaged
//! samples. If you are not using hardware averaging or don't need the
//! fractional part of the ADC sample, you should just use
//! AM_HAL_ADC_FIFO_SAMPLE.
//!
//! If you do need the fractional part, use AM_HAL_ADC_FIFO_FULL_SAMPLE. This
//! macro will keep six bits of precision past the decimal point. Depending on
//! the number of averaged samples, anywhere between 1 and 6 of these bits will
//! be valid. Please consult the datasheet to find out how many bits of data
//! are valid for your chosen averaging settings.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_ADC_FIFO_SAMPLE(value)                                         \
    ((((value) & AM_REG_ADC_FIFO_DATA_M) >> AM_REG_ADC_FIFO_DATA_S) >> 6)

#define AM_HAL_ADC_FIFO_FULL_SAMPLE(value)                                    \
    (((value) & AM_REG_ADC_FIFO_DATA_M) >> AM_REG_ADC_FIFO_DATA_S )

#define AM_HAL_ADC_FIFO_SLOT(value)                                           \
    (((value) & AM_REG_ADC_FIFO_SLOTNUM_M) >> AM_REG_ADC_FIFO_SLOTNUM_S)

#define AM_HAL_ADC_FIFO_COUNT(value)                                          \
    (((value) & AM_REG_ADC_FIFO_COUNT_M) >> AM_REG_ADC_FIFO_COUNT_S)
//! @}

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// External function definitions
//
//*****************************************************************************
extern void am_hal_adc_config(am_hal_adc_config_t *psConfig);
extern void am_hal_adc_window_set(uint32_t ui32Upper, uint32_t ui32Lower);
extern void am_hal_adc_slot_config(uint32_t ui32SlotNumber,
                                   uint32_t ui32SlotConfig);

extern uint32_t am_hal_adc_fifo_peek(void);
extern uint32_t am_hal_adc_fifo_pop(void);

extern void am_hal_adc_trigger(void);
extern void am_hal_adc_enable(void);
extern void am_hal_adc_disable(void);
extern void am_hal_adc_int_enable(uint32_t ui32Interrupt);
extern uint32_t am_hal_adc_int_enable_get(void);
extern void am_hal_adc_int_disable(uint32_t ui32Interrupt);
extern void am_hal_adc_int_clear(uint32_t ui32Interrupt);
extern void am_hal_adc_int_set(uint32_t ui32Interrupt);
extern uint32_t am_hal_adc_int_status_get(bool bEnabledOnly);
extern float am_hal_adc_volts_to_celsius(float fVoltage);
extern void am_hal_adc_temp_trims_get(float * pfTemp, float * pfVoltage, float * pfOffsetV);

#ifdef __cplusplus
}
#endif

#endif // AM_HAL_ADC_H

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
