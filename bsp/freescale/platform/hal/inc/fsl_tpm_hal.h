/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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
#if !defined(__FSL_TPM_HAL_H__)
#define __FSL_TPM_HAL_H__

#include "fsl_device_registers.h"
#include <stdbool.h>
#include <assert.h>

#if FSL_FEATURE_SOC_TPM_COUNT

/*!
 * @addtogroup tpm_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Table of number of channels for each TPM instance */
extern const uint32_t g_tpmChannelCount[TPM_INSTANCE_COUNT];

/*! @brief TPM clock source selection for TPM_SC[CMOD].*/
typedef enum _tpm_clock_mode
{
     kTpmClockSourceNoneClk = 0,    /*TPM clock mode, None CLK*/
     kTpmClockSourceModuleClk,      /*TPM clock mode, Module CLK*/
     kTpmClockSourceExternalClk,    /*TPM clock mode, External input clock*/
     kTpmClockSourceReservedClk     /*TPM clock mode, Reserved*/
}tpm_clock_mode_t;

/*! @brief TPM counting mode, up or down*/
typedef enum _tpm_counting_mode
{
     kTpmCountingUp = 0,           /*TPM counter mode, Up counting only*/
     kTpmCountingUpDown            /*TPM counter mode, Up/Down counting mode*/
}tpm_counting_mode_t;

/*! @brief TPM prescaler factor selection for clock source*/
typedef enum _tpm_clock_ps
{
     kTpmDividedBy1 = 0,          /*TPM module clock prescaler, by 1*/
     kTpmDividedBy2 ,             /*TPM module clock prescaler, by 2*/
     kTpmDividedBy4 ,             /*TPM module clock prescaler, by 4*/
     kTpmDividedBy8,              /*TPM module clock prescaler, by 8*/
     kTpmDividedBy16,             /*TPM module clock prescaler, by 16*/
     kTpmDividedBy32,             /*TPM module clock prescaler, by 32*/
     kTpmDividedBy64,             /*TPM module clock prescaler, by 64*/
     kTpmDividedBy128             /*TPM module clock prescaler, by 128*/
}tpm_clock_ps_t;

/*! @brief TPM trigger sources, please refer to the chip reference manual for available options */
typedef enum _tpm_trigger_source_t
{
    kTpmTrigSel0 = 0,       /*!< TPM trigger source 0 */
    kTpmTrigSel1,           /*!< TPM trigger source 1 */
    kTpmTrigSel2,           /*!< TPM trigger source 2 */
    kTpmTrigSel3,           /*!< TPM trigger source 3 */
    kTpmTrigSel4,           /*!< TPM trigger source 4 */
    kTpmTrigSel5,           /*!< TPM trigger source 5 */
    kTpmTrigSel6,           /*!< TPM trigger source 6 */
    kTpmTrigSel7,           /*!< TPM trigger source 7 */
    kTpmTrigSel8,           /*!< TPM trigger source 8 */
    kTpmTrigSel9,           /*!< TPM trigger source 8 */
    kTpmTrigSel10,          /*!< TPM trigger source 10 */
    kTpmTrigSel11,          /*!< TPM trigger source 11 */
    kTpmTrigSel12,          /*!< TPM trigger source 12 */
    kTpmTrigSel13,          /*!< TPM trigger source 13 */
    kTpmTrigSel14,          /*!< TPM trigger source 14 */
    kTpmTrigSel15           /*!< TPM trigger source 15 */
}tpm_trigger_source_t;

/*! @brief TPM operation mode */
typedef enum _tpm_pwm_mode_t
{
    kTpmEdgeAlignedPWM = 0, /*!< Edge aligned mode @internal gui name="Edge aligned" */
    kTpmCenterAlignedPWM /*!< Center aligned mode @internal gui name="Center aligned" */
}tpm_pwm_mode_t;

/*! @brief TPM PWM output pulse mode, high-true or low-true on match up */
typedef enum _tpm_pwm_edge_mode_t
{
    kTpmHighTrue = 0, /*!< Clear output on match, set output on reload @internal gui name="High true" */
    kTpmLowTrue /*!< Set output on match, clear output on reload @internal gui name="Low true" */
}tpm_pwm_edge_mode_t;

/*! @brief TPM input capture modes */
typedef enum _tpm_input_capture_mode_t
{
    kTpmRisingEdge = 1,
    kTpmFallingEdge,
    kTpmRiseOrFallEdge
}tpm_input_capture_mode_t;

/*! @brief TPM output compare modes */
typedef enum _tpm_output_compare_mode_t
{
    kTpmOutputNone = 0,
    kTpmToggleOutput,
    kTpmClearOutput,
    kTpmSetOutput,
    kTpmHighPulseOutput,
    kTpmLowPulseOutput
}tpm_output_compare_mode_t;

/*! @brief Error codes for TPM driver. */
typedef enum _tpm_status
{
    kStatusTpmSuccess = 0x00U,        /*!< TPM success status.*/
    kStatusTpmFail    = 0x01U         /*!< TPM error status.*/
} tpm_status_t;

/*!
 * @brief TPM driver PWM parameter
 * @internal gui name="PWM channels configuration" id="tpmPwmCfg"
 */
typedef struct TpmPwmParam
{
    tpm_pwm_mode_t mode;          /*!< TPM PWM operation mode  @internal gui name="Mode" id="PWMmode" */
    tpm_pwm_edge_mode_t edgeMode;    /*!< PWM output mode  @internal gui name="Edge mode" id="ChannelEdgeMode" */
    uint32_t uFrequencyHZ;           /*!< PWM period in Hz  @internal gui name="Frequency" id="Frequency" */
    uint32_t uDutyCyclePercent;      /*!< PWM pulse width, value should be between 0 to 100
                                          0=inactive signal(0% duty cycle)...
                                          100=active signal (100% duty cycle).  @internal gui name="Duty cycle" id="ChannelDuty" */
}tpm_pwm_param_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Resets the TPM registers.
 *
 * @param base TPM module base address pointer
 * @param instance The TPM peripheral instance number.
 */
void TPM_HAL_Reset(TPM_Type *base, uint32_t instance);

/*!
 * @brief Enables the TPM PWM output mode.
 *
 * @param base TPM module base address pointer
 * @param config PWM configuration parameter
 * @param channel The TPM channel number.
 */
void TPM_HAL_EnablePwmMode(TPM_Type *base, tpm_pwm_param_t *config, uint8_t channel);

/*!
 * @brief Disables the TPM channel.
 *
 * @param base TPM module base address pointer
 * @param channel The TPM channel number.
 */
void TPM_HAL_DisableChn(TPM_Type *base, uint8_t channel);

/*!
 * @brief Sets the TPM clock mode.
 *
 * When disabling the TPM counter, the function waits till it receives an acknowledge from the
 * TPM clock domain.
 *
 * @param base TPM module base address pointer
 * @param mode The TPM counter clock mode (source).
 */
void TPM_HAL_SetClockMode(TPM_Type *base, tpm_clock_mode_t mode);

/*!
 * @brief get TPM clock mode.
 * @param base TPM module base address pointer
 * @return The TPM counter clock mode (source).
 */
static inline tpm_clock_mode_t TPM_HAL_GetClockMode(TPM_Type *base)
{
    return (tpm_clock_mode_t) TPM_BRD_SC_CMOD(base);
}

/*!
 * @brief Sets the TPM clock divider.
 * @param base TPM module base address pointer
 * @param ps  The TPM peripheral clock prescale divider
 */
static inline void TPM_HAL_SetClockDiv(TPM_Type *base, tpm_clock_ps_t ps)
{
    TPM_BWR_SC_PS(base, ps);
}

/*!
 * @brief Gets the TPM clock divider.
 * @param base TPM module base address pointer
 * @return The TPM peripheral clock prescale divider.
 */
static inline tpm_clock_ps_t TPM_HAL_GetClockDiv(TPM_Type *base)
{
    return (tpm_clock_ps_t)TPM_BRD_SC_PS(base);
}

/*!
 * @brief Enables the TPM peripheral timer overflow interrupt.
 *
 * @param base TPM module base address pointer
 */
static inline void TPM_HAL_EnableTimerOverflowInt(TPM_Type *base)
{
    TPM_BWR_SC_TOIE(base, 1);
}

/*!
 * @brief Disables the TPM peripheral timer overflow interrupt.
 *
 * @param base TPM module base address pointer
 */
static inline void TPM_HAL_DisableTimerOverflowInt(TPM_Type *base)
{
    TPM_BWR_SC_TOIE(base, 0);
}

/*!
 * @brief Reads the bit that controls TPM timer overflow interrupt enablement.
 *
 * @param base TPM module base address pointer
 * @return true if overflow interrupt is enabled, false if not
 */
static inline bool TPM_HAL_IsOverflowIntEnabled(TPM_Type *base)
{
    return (bool)(TPM_BRD_SC_TOIE(base));
}

/*!
 * @brief Returns the TPM peripheral timer overflow interrupt flag.
 * @param base TPM module base address pointer
 * @return true if overflow, false if not
 */
static inline bool TPM_HAL_GetTimerOverflowStatus(TPM_Type *base)
{
    return (bool)(TPM_BRD_SC_TOF(base));
}

/*!
 * @brief Clears the TPM timer overflow interrupt flag.
 * @param base TPM module base address pointer
 */
static inline void TPM_HAL_ClearTimerOverflowFlag(TPM_Type *base)
{
    TPM_BWR_SC_TOF(base, 1);
}

/*!
 * @brief set TPM center-aligned PWM select.
 * @param base TPM module base address pointer
 * @param mode 1 : upcounting mode 0:up_down counting mode.
 */
static inline void TPM_HAL_SetCpwms(TPM_Type *base, uint8_t mode)
{
    assert(mode < 2);
    TPM_BWR_SC_CPWMS(base, mode);
}

/*!
 * @brief Gets the TPM center-aligned PWM selection value.
 * @param base TPM module base address pointer
 * @return Whether the TPM center-aligned PWM is selected or not.
 */
static inline bool TPM_HAL_GetCpwms(TPM_Type *base)
{
    return (bool)TPM_BRD_SC_CPWMS(base);
}

/*!
 * @brief Clears the TPM peripheral current counter value.
 * @param base TPM module base address pointer
 */
static inline void  TPM_HAL_ClearCounter(TPM_Type *base)
{
    TPM_BWR_CNT_COUNT(base, 0);
}

/*!
 * @brief Returns the TPM peripheral current counter value.
 * @param base TPM module base address pointer
 * @return current TPM timer counter value
 */
static inline uint16_t  TPM_HAL_GetCounterVal(TPM_Type *base)
{
    return TPM_BRD_CNT_COUNT(base);
}

/*!
 * @brief Sets the TPM peripheral timer modulo value.
 * @param base TPM module base address pointer
 * @param val The value to be set to the timer modulo
 */
static inline void TPM_HAL_SetMod(TPM_Type *base, uint16_t val)
{
    /*As RM mentioned, first clear TPM_CNT then write value to TPM_MOD*/
    TPM_BWR_CNT_COUNT(base, 0);
    TPM_BWR_MOD_MOD(base, val);
}

/*!
 * @brief Returns the TPM peripheral counter modulo value.
 * @param base TPM module base address pointer
 * @return TPM timer modula value
 */
static inline uint16_t  TPM_HAL_GetMod(TPM_Type *base)
{
    return TPM_BRD_MOD_MOD(base);
}

/*TPM channel operating mode (mode, edge, and level selection) for capture, output, and PWM*/

/*!
 * @brief Sets the TPM peripheral timer channel mode and edge level,
 *
 * TPM channel operate mode, MSnB, and ELSnBA should be set at the same time.
 *
 * @param base The TPM base address
 * @param channel  The TPM peripheral channel number
 * @param value    The value to set for MSnBA and ELSnBA
 */
static inline void TPM_HAL_SetChnMsnbaElsnbaVal(TPM_Type *base, uint8_t channel, uint8_t value)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);

    /* Keep CHIE bit value not changed by this function, so read it first and or with value*/
    value |= TPM_RD_CnSC(base, channel) & TPM_CnSC_CHIE_MASK;

    TPM_WR_CnSC(base, channel, value);
}

/*!
 * @brief Gets the TPM peripheral timer channel mode.
 * @param base TPM module base address pointer
 * @param channel  The TPM peripheral channel number
 * @return The MSnB:MSnA mode value, will be 00,01, 10, 11
 */
static inline uint8_t TPM_HAL_GetChnMsnbaVal(TPM_Type *base, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    return (TPM_RD_CnSC(base, channel) & (TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK)) >> TPM_CnSC_MSA_SHIFT;
}

/*!
 * @brief Gets the TPM peripheral timer channel edge level.
 * @param base TPM module base address pointer
 * @param channel  The TPM peripheral channel number
 * @return The ELSnB:ELSnA mode value, will be 00,01, 10, 11
 */
static inline uint8_t TPM_HAL_GetChnElsnbaVal(TPM_Type *base, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    return (TPM_RD_CnSC(base, channel) & (TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK)) >> TPM_CnSC_ELSA_SHIFT;
}

/*!
 * @brief Enables the TPM peripheral timer channel(n) interrupt.
 * @param base TPM module base address pointer
 * @param channel  The TPM peripheral channel number
 */
static inline void TPM_HAL_EnableChnInt(TPM_Type *base, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    TPM_BWR_CnSC_CHIE(base, channel, 1);
}

/*!
 * @brief Disables the TPM peripheral timer channel(n) interrupt.
 * @param base TPM module base address pointer
 * @param channel  The TPM peripheral channel number
 */
static inline void TPM_HAL_DisableChnInt(TPM_Type *base, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    TPM_BWR_CnSC_CHIE(base, channel, 0);
}

/*!
 * @brief Gets the TPM peripheral timer channel(n) interrupt enabled or not.
 * @param base TPM module base address pointer
 * @param channel  The TPM peripheral channel number
 * @return Whether the TPM peripheral timer channel(n) interrupt is enabled or not.
 */
static inline bool TPM_HAL_IsChnIntEnabled(TPM_Type *base, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    return (bool)(TPM_BRD_CnSC_CHIE(base, channel));
}

/*!
 * @brief Returns whether any event for TPM peripheral timer channel has occurred.
 * @param base TPM module base address pointer
 * @param channel  The TPM peripheral channel number.
 * @return true if event occurred, false otherwise
 */
static inline bool TPM_HAL_GetChnStatus(TPM_Type *base, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    return (bool)(TPM_BRD_CnSC_CHF(base, channel));
}

/*!
 * @brief Returns whether any event for the TPM peripheral timer channel has occurred.
 * @param base TPM module base address pointer
 * @param channel  The TPM peripheral channel number.
 */
static inline void TPM_HAL_ClearChnInt(TPM_Type *base, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    TPM_BWR_CnSC_CHF(base, channel, 0x1);
}

/*TPM Channel control*/
/*!
 * @brief Sets the TPM peripheral timer channel counter value.
 * @param base TPM module base address pointer
 * @param channel  The TPM peripheral channel number.
 * @param val counter value to be set
 */
static inline void TPM_HAL_SetChnCountVal(TPM_Type *base, uint8_t channel, uint16_t val)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    TPM_BWR_CnV_VAL(base, channel, val);
}

/*!
 * @brief Gets the TPM peripheral timer channel counter value.
 * @param base TPM module base address pointer
 * @param channel  The TPM peripheral channel number.
 * @return The TPM timer channel counter value.
 */
static inline uint16_t TPM_HAL_GetChnCountVal(TPM_Type *base, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    return TPM_BRD_CnV_VAL(base, channel);
}

/*!
 * @brief Gets the TPM peripheral timer channel event status.
 * @param base TPM module base address pointer
 * @return The TPM timer channel event status.
 */
static inline uint32_t TPM_HAL_GetStatusRegVal(TPM_Type *base)
{
    return TPM_RD_STATUS(base);
}

/*!
 * @brief Clears the TPM peripheral timer clear status register value,
 * @param base TPM module base address pointer
 * @param tpm_status TPM channel or overflow flag to clear
 */
static inline void TPM_HAL_ClearStatusReg(TPM_Type *base, uint16_t tpm_status)
{
    TPM_WR_STATUS(base, tpm_status);
}

/*!
 * @brief Sets the TPM peripheral timer trigger.
 * @param base TPM module base address pointer
 * @param trigger_num  0-15
 */
static inline void TPM_HAL_SetTriggerSrc(TPM_Type *base, tpm_trigger_source_t trigger_num)
{
    TPM_BWR_CONF_TRGSEL(base, trigger_num);
}

/*!
 * @brief Sets the TPM peripheral timer running on trigger or not.
 * @param base TPM module base address pointer
 * @param enable true to enable, 1 to enable
 */
static inline void TPM_HAL_SetTriggerMode(TPM_Type *base, bool enable)
{
    TPM_BWR_CONF_CSOT (base, enable);
}

/*!
 * @brief Enables the TPM timer counter reload on selected trigger or not.
 * @param base TPM module base address pointer
 * @param enable  true to enable, false to disable.
 */
static inline void TPM_HAL_SetReloadOnTriggerMode(TPM_Type *base, bool enable)
{
    TPM_BWR_CONF_CROT(base, enable);
}

/*!
 * @brief Enables the TPM timer counter stop on selected trigger or not.
 * @param base TPM module base address pointer
 * @param enable  true to enable, false to disable.
 */
static inline void TPM_HAL_SetStopOnOverflowMode(TPM_Type *base, bool enable)
{
    TPM_BWR_CONF_CSOO(base, enable);
}

/*!
 * @brief Enables the TPM timer global time base.
 * @param base TPM module base address pointer
 * @param enable  true to enable, false to disable.
 */
static inline void TPM_HAL_EnableGlobalTimeBase(TPM_Type *base, bool enable)
{
    TPM_BWR_CONF_GTBEEN(base, enable);
}

/*!
 * @brief Sets BDM mode.
 * @param base TPM module base address pointer
 * @param enable  false pause, true continue work
 */
static inline void TPM_HAL_SetDbgMode(TPM_Type *base, bool enable)
{
    TPM_BWR_CONF_DBGMODE(base, enable ? 3 : 0);
}

/*!
 * @brief Sets the WAIT mode behavior.
 * @param base TPM module base address pointer
 * @param enable  0 continue running, 1 stop running
 */
static inline void TPM_HAL_SetWaitMode(TPM_Type *base, bool enable)
{
    TPM_BWR_CONF_DOZEEN(base, enable ? 0 : 1);
}

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_TPM_COUNT */

#endif /* __FSL_TPM_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

