/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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
#if !defined(__FSL_FTM_HAL_H__)
#define __FSL_FTM_HAL_H__

#include "fsl_device_registers.h"
#include <stdbool.h>
#include <assert.h>

#if FSL_FEATURE_SOC_FTM_COUNT

/*!
 * @addtogroup ftm_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define CHAN0_IDX (0U) /*!< Channel number for CHAN0.*/
#define CHAN1_IDX (1U) /*!< Channel number for CHAN1.*/
#define CHAN2_IDX (2U) /*!< Channel number for CHAN2.*/
#define CHAN3_IDX (3U) /*!< Channel number for CHAN3.*/
#define CHAN4_IDX (4U) /*!< Channel number for CHAN4.*/
#define CHAN5_IDX (5U) /*!< Channel number for CHAN5.*/
#define CHAN6_IDX (6U) /*!< Channel number for CHAN6.*/
#define CHAN7_IDX (7U) /*!< Channel number for CHAN7.*/

#define FTM_COMBINE_CHAN_CTRL_WIDTH  (8U)

/*! @brief FlexTimer clock source selection*/
typedef enum _ftm_clock_source
{
    kClock_source_FTM_None = 0, /*!< @internal gui name="None" */
    kClock_source_FTM_SystemClk, /*!< @internal gui name="System clock" */
    kClock_source_FTM_FixedClk, /*!< @internal gui name="Fixed clock" */
    kClock_source_FTM_ExternalClk /*!< @internal gui name="External clock" */
}ftm_clock_source_t;

/*! @brief FlexTimer counting mode selection */
typedef enum _ftm_counting_mode
{
    kCounting_FTM_UP = 0,
    kCounting_FTM_UpDown
}ftm_counting_mode_t;

/*! @brief FlexTimer pre-scaler factor selection for the clock source*/
typedef enum _ftm_clock_ps
{
    kFtmDividedBy1 = 0, /*!< @internal gui name="Divide by 1" */
    kFtmDividedBy2 , /*!< @internal gui name="Divide by 2" */
    kFtmDividedBy4 , /*!< @internal gui name="Divide by 4" */
    kFtmDividedBy8,  /*!< @internal gui name="Divide by 8" */
    kFtmDividedBy16, /*!< @internal gui name="Divide by 16" */
    kFtmDividedBy32, /*!< @internal gui name="Divide by 32" */
    kFtmDividedBy64, /*!< @internal gui name="Divide by 64" */
    kFtmDividedBy128 /*!< @internal gui name="Divide by 128" */
}ftm_clock_ps_t;

/*! @brief FlexTimer pre-scaler factor for the deadtime insertion*/
typedef enum _ftm_deadtime_ps
{
    kFtmDivided1 = 1, /*!< @internal gui name="Divide by 1" */
    kFtmDivided4, /*!< @internal gui name="Divide by 4" */
    kFtmDivided16, /*!< @internal gui name="Divide by 16" */
}ftm_deadtime_ps_t;

/*! @brief FlexTimer operation mode, capture, output, dual */
typedef enum _ftm_config_mode_t
{
    kFtmInputCapture, /*!< @internal gui name="Input capture" */
    kFtmOutputCompare, /*!< @internal gui name="Output compare" */
    kFtmEdgeAlignedPWM, /*!< @internal gui name="Edge aligned PWM" */
    kFtmCenterAlignedPWM, /*!< @internal gui name="Center aligned PWM" */
    kFtmCombinedPWM, /*!< @internal gui name="Combined PWM" */
    kFtmDualEdgeCapture /*!< @internal gui name="Dual edge capture" */
}ftm_config_mode_t;

/*! @brief FlexTimer input capture edge mode, rising edge, or falling edge */
typedef enum _ftm_input_capture_edge_mode_t
{
   kFtmRisingEdge = 1,
   kFtmFallingEdge,
   kFtmRisingAndFalling
}ftm_input_capture_edge_mode_t;

/*! @brief FlexTimer output compare edge mode. Toggle, clear or set.*/
typedef enum _ftm_output_compare_edge_mode_t
{
   kFtmToggleOnMatch = 1,
   kFtmClearOnMatch,
   kFtmSetOnMatch
}ftm_output_compare_edge_mode_t;

/*! @brief FlexTimer PWM output pulse mode, high-true or low-true on match up */
typedef enum _ftm_pwm_edge_mode_t
{
    kFtmHighTrue = 0, /*!< @internal gui name="High true" */
    kFtmLowTrue /*!< @internal gui name="Low true" */
}ftm_pwm_edge_mode_t;

/*! @brief FlexTimer dual capture edge mode, one shot or continuous */
typedef enum _ftm_dual_capture_edge_mode_t
{
    kFtmOneShot = 0,
    kFtmContinuous
}ftm_dual_capture_edge_mode_t;

/*! @brief FlexTimer quadrature decode modes, phase encode or count and direction mode */
typedef enum _ftm_quad_decode_mode_t
{
    kFtmQuadPhaseEncode = 0,
    kFtmQuadCountAndDir
}ftm_quad_decode_mode_t;

/*! @brief FlexTimer quadrature phase polarities, normal or inverted polarity */
typedef enum _ftm_quad_phase_polarity_t
{
    kFtmQuadPhaseNormal = 0, /*!< Phase A input signal is not inverted before identifying the rising and falling edges of this signal. @internal gui name="Normal polarity" */
    kFtmQuadPhaseInvert /*!< Phase A input signal is inverted before identifying the rising and falling edges of this signal. @internal gui name="Inverted polarity" */
}ftm_quad_phase_polarity_t;

/*! @brief FlexTimer sync options to update registers with buffer */
typedef enum _ftm_sync_method_t
{
    kFtmUseSoftwareTrig = (1U << FTM_SYNC_SWSYNC_SHIFT),
    kFtmUseHardwareTrig0 = (1U << FTM_SYNC_TRIG0_SHIFT),
    kFtmUseHardwareTrig1 = (1U << FTM_SYNC_TRIG1_SHIFT),
    kFtmUseHardwareTrig2 = (1U << FTM_SYNC_TRIG2_SHIFT)
}ftm_sync_method_t;

/*! @brief Options for the FlexTimer behaviour in BDM Mode */
typedef enum _ftm_bdm_mode_t
{
    kFtmBdmMode_00 = 0,
    /*!< FTM counter stopped, CH(n)F bit can be set, FTM channels in functional mode, writes to MOD,CNTIN and C(n)V registers bypass the register buffers. @internal gui name="Mode 0" */
    kFtmBdmMode_01,
    /*!< FTM counter stopped, CH(n)F bit is not set, FTM channels outputs are forced to their safe value , writes to MOD,CNTIN and C(n)V registers bypass the register buffers. @internal gui name="Mode 1" */
    kFtmBdmMode_10,
    /*!< FTM counter stopped, CH(n)F bit is not set, FTM channels outputs are frozen when chip enters in BDM mode, writes to MOD,CNTIN and C(n)V registers bypass the register buffers. @internal gui name="Mode 2" */
    kFtmBdmMode_11
    /*!< FTM counter in functional mode, CH(n)F bit can be set, FTM channels in functional mode, writes to MOD,CNTIN and C(n)V registers is in fully functional mode. @internal gui name="Mode 3" */
}ftm_bdm_mode_t;

/*! @brief FTM status */
typedef enum _ftm_status {
    kStatusFtmSuccess = 0U,                   /*!< FTM success status.*/
    kStatusFtmError = 1U,                     /*!< FTM error status.*/
} ftm_status_t;

/*! @brief FlexTimer edge mode*/
typedef union _ftm_edge_mode_t
{
    ftm_input_capture_edge_mode_t  input_capture_edge_mode;
    ftm_output_compare_edge_mode_t output_compare_edge_mode;
    ftm_pwm_edge_mode_t            ftm_pwm_edge_mode;
    ftm_dual_capture_edge_mode_t   ftm_dual_capture_edge_mode;
}ftm_edge_mode_t;

/*!
 * @brief FlexTimer driver PWM parameter
 * @internal gui name="PWM configuration" id="ftmPwmCfg"
 */
typedef struct FtmPwmParam
{
    ftm_config_mode_t mode;          /*!< FlexTimer PWM operation mode @internal gui name="Mode" id="ChannelMode" default="2" */
    ftm_pwm_edge_mode_t edgeMode;    /*!< PWM output mode @internal gui name="Edge mode" id="ChannelEdgeMode" */
    uint32_t uFrequencyHZ;           /*!< PWM period in Hz @internal gui name="Frequency" id="Frequency" default="1000" */
    uint32_t uDutyCyclePercent;      /*!< PWM pulse width, value should be between 0 to 100
                                          0=inactive signal(0% duty cycle)...
                                          100=active signal (100% duty cycle). @internal gui name="Duty cycle" id="ChannelDuty" default="50" */
    uint16_t uFirstEdgeDelayPercent; /*!< Used only in combined PWM mode to generate asymmetrical PWM.
                                          Specifies the delay to the first edge in a PWM period.
                                          If unsure please leave as 0, should be specified as
                                          percentage of the PWM period @internal gui name="First edge delay" id="ChannelFirstEdge" */
}ftm_pwm_param_t;

/*! @brief FlexTimer Dual Edge Capture parameters */
typedef struct FtmDualEdgeCaptureParam
{
    ftm_dual_capture_edge_mode_t mode;              /*!< Dual Edge Capture mode: one-shot or continuous */
    ftm_input_capture_edge_mode_t currChanEdgeMode; /*!< Input Edge select for Channel n */
    ftm_input_capture_edge_mode_t nextChanEdgeMode; /*!< Input Edge select for Channel n + 1 */
}ftm_dual_edge_capture_param_t;

/*! @brief FlexTimer quadrature decode phase parameters
 * @internal gui name="Quadrature decode configuration" id="ftmQuadCfg"
 */
typedef struct FtmPhaseParam
{
    bool kFtmPhaseInputFilter;      /*!< false: disable phase filter, true: enable phase filter  @internal gui name="Phase input filter" id="QuadPhaseFilter" */
    uint32_t kFtmPhaseFilterVal;    /*!< Filter value, used only if phase input filter is enabled  @internal gui name="Phase filter value" id="QuadPhaseValue" */
    ftm_quad_phase_polarity_t kFtmPhasePolarity; /*!< kFtmQuadPhaseNormal or kFtmQuadPhaseInvert  @internal gui name="Phase polarity" id="QuadPhasePol" */
}ftm_phase_params_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*FTM timer control*/
/*!
 * @brief Sets the FTM clock source.
 *
 * @param ftmBase The FTM base address pointer
 * @param clock  The FTM peripheral clock selection\n
 *        bits - 00: No clock  01: system clock  10: fixed clock   11: External clock
 */
static inline void FTM_HAL_SetClockSource(FTM_Type *ftmBase, ftm_clock_source_t clock)
{
    FTM_BWR_SC_CLKS(ftmBase, clock);
}

/*!
 * @brief Reads the FTM clock source.
 *
 * @param ftmBase The FTM base address pointer
 *
 * @return  The FTM clock source selection\n
 *          bits - 00: No clock  01: system clock  10: fixed clock   11:External clock
 */
static inline uint8_t FTM_HAL_GetClockSource(FTM_Type *ftmBase)
{
    return FTM_BRD_SC_CLKS(ftmBase);
}

/*!
 * @brief Sets the FTM clock divider.
 *
 * @param ftmBase The FTM base address pointer
 * @param ps  The FTM peripheral clock pre-scale divider
 */
static inline void FTM_HAL_SetClockPs(FTM_Type *ftmBase, ftm_clock_ps_t ps)
{
    FTM_BWR_SC_PS(ftmBase, ps);
}

/*!
 * @brief Reads the FTM clock divider.
 *
 * @param ftmBase The FTM base address pointer
 *
 * @return The FTM clock pre-scale divider
 */
static inline uint8_t FTM_HAL_GetClockPs(FTM_Type *ftmBase)
{
    return FTM_BRD_SC_PS(ftmBase);
}

/*!
 * @brief Enables the FTM peripheral timer overflow interrupt.
 *
 * @param ftmBase The FTM base address pointer
 */
static inline void FTM_HAL_EnableTimerOverflowInt(FTM_Type *ftmBase)
{
    FTM_BWR_SC_TOIE(ftmBase, 1);
}

/*!
 * @brief Disables the FTM peripheral timer overflow interrupt.
 *
 * @param ftmBase The FTM base address pointer
 */
static inline void FTM_HAL_DisableTimerOverflowInt(FTM_Type *ftmBase)
{
     FTM_BWR_SC_TOIE(ftmBase, 0);
}

/*!
 * @brief Reads the bit that controls enabling the FTM timer overflow interrupt.
 *
 * @param ftmBase The FTM base address pointer
 * @return true if overflow interrupt is enabled, false if not
 */
static inline bool FTM_HAL_IsOverflowIntEnabled(FTM_Type *ftmBase)
{
    return (bool)(FTM_BRD_SC_TOIE(ftmBase));
}

/*!
 * @brief Clears the timer overflow interrupt flag.
 *
 * @param ftmBase The FTM base address pointer
 */
static inline void FTM_HAL_ClearTimerOverflow(FTM_Type *ftmBase)
{
    FTM_BWR_SC_TOF(ftmBase, 0);
}

/*!
 * @brief Returns the FTM peripheral timer overflow interrupt flag.
 *
 * @param ftmBase The FTM base address pointer
 * @return true if overflow, false if not
 */
static inline bool FTM_HAL_HasTimerOverflowed(FTM_Type *ftmBase)
{
     return FTM_BRD_SC_TOF(ftmBase);
}

/*!
 * @brief Sets the FTM center-aligned PWM select.
 *
 * @param ftmBase The FTM base address pointer
 * @param mode 1:upcounting mode 0:up_down counting mode
 */
static inline void FTM_HAL_SetCpwms(FTM_Type *ftmBase, uint8_t mode)
{
    assert(mode < 2);
    FTM_BWR_SC_CPWMS(ftmBase, mode);
}

/*!
 * @brief Sets the FTM peripheral current counter value.
 *
 * @param ftmBase The FTM base address pointer
 * @param val  FTM timer counter value to be set
 */
static inline void  FTM_HAL_SetCounter(FTM_Type *ftmBase, uint16_t val)
{
    FTM_WR_CNT_COUNT(ftmBase, val);
}

/*!
 * @brief Returns the FTM peripheral current counter value.
 *
 * @param ftmBase The FTM base address pointer
 * @return current FTM timer counter value
 */
static inline uint16_t  FTM_HAL_GetCounter(FTM_Type *ftmBase)
{
    return FTM_RD_CNT_COUNT(ftmBase);
}

/*!
 * @brief Sets the FTM peripheral timer modulo value.
 *
 * @param ftmBase The FTM base address pointer
 * @param val The value to be set to the timer modulo
 */
static inline void FTM_HAL_SetMod(FTM_Type *ftmBase, uint16_t val)
{
    FTM_WR_MOD_MOD(ftmBase, val);
}

/*!
 * @brief Returns the FTM peripheral counter modulo value.
 *
 * @param ftmBase The FTM base address pointer
 * @return FTM timer modulo value
 */
static inline uint16_t  FTM_HAL_GetMod(FTM_Type *ftmBase)
{
    return FTM_RD_MOD_MOD(ftmBase);
}

/*!
 * @brief Sets the FTM peripheral timer counter initial value.
 *
 * @param ftmBase The FTM base address pointer
 * @param val initial value to be set
 */
static inline void FTM_HAL_SetCounterInitVal(FTM_Type *ftmBase, uint16_t val)
{
    FTM_WR_CNTIN_INIT(ftmBase, val & FTM_CNTIN_INIT_MASK);
}

/*!
 * @brief Returns the FTM peripheral counter initial value.
 *
 * @param ftmBase The FTM base address pointer
 * @return FTM timer counter initial value
 */
static inline uint16_t  FTM_HAL_GetCounterInitVal(FTM_Type *ftmBase)
{
    return FTM_RD_CNTIN_INIT(ftmBase);
}

/*FTM channel operating mode (mode, edge and level selection) for capture, output, PWM, combine, and dual */
/*!
 * @brief Sets the FTM peripheral timer channel mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 * @param selection The mode to be set valid value MSnB:MSnA : 00, 01, 10, 11
 */
static inline void FTM_HAL_SetChnMSnBAMode(FTM_Type *ftmBase, uint8_t channel, uint8_t selection)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    FTM_BWR_CnSC_MSA(ftmBase, channel, selection & 1);
    FTM_BWR_CnSC_MSB(ftmBase, channel, selection & 2 ? 1 : 0);
}

/*!
 * @brief Sets the FTM peripheral timer channel edge level.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 * @param level The rising or falling edge to be set, valid value ELSnB:ELSnA : 00, 01, 10, 11
 */
static inline void FTM_HAL_SetChnEdgeLevel(FTM_Type *ftmBase, uint8_t channel, uint8_t level)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    FTM_BWR_CnSC_ELSA(ftmBase, channel, level & 1 ? 1 : 0);
    FTM_BWR_CnSC_ELSB(ftmBase, channel, level & 2 ? 1 : 0);
}

/*!
 * @brief Gets the FTM peripheral timer channel mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 * @return The MSnB:MSnA mode value, will be 00, 01, 10, 11
 */
static inline uint8_t FTM_HAL_GetChnMode(FTM_Type *ftmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    return (FTM_BRD_CnSC_MSA(ftmBase, channel)|| (FTM_BRD_CnSC_MSB(ftmBase, channel) << 1));
}

/*!
 * @brief Gets the FTM peripheral timer channel edge level.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 * @return The ELSnB:ELSnA mode value, will be 00, 01, 10, 11
 */
static inline uint8_t FTM_HAL_GetChnEdgeLevel(FTM_Type *ftmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    return (FTM_BRD_CnSC_ELSA(ftmBase, channel)|| (FTM_BRD_CnSC_ELSB(ftmBase, channel) << 1));
}

/*!
 * @brief Enables or disables the FTM peripheral timer channel DMA.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 * @param val enable or disable
 */
static inline void FTM_HAL_SetChnDmaCmd(FTM_Type *ftmBase, uint8_t channel, bool val)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    FTM_BWR_CnSC_DMA(ftmBase, channel,(val? 1 : 0));
}

/*!
 * @brief Returns whether the FTM peripheral timer channel DMA is enabled.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 * @return true if enabled, false if disabled
 */
static inline bool FTM_HAL_IsChnDma(FTM_Type *ftmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    return (FTM_BRD_CnSC_DMA(ftmBase, channel) ? true : false);
}

/*!
 * @brief Gets the FTM channel(n) interrupt enabled or not.
 * @param ftmBase FTM module base address.
 * @param channel  The FTM peripheral channel number
 * @return true if enabled, false if disabled
 */
static inline bool FTM_HAL_IsChnIntEnabled(FTM_Type *ftmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    return (bool)(FTM_BRD_CnSC_CHIE(ftmBase, channel));
}

/*!
 * @brief Enables the FTM peripheral timer channel(n) interrupt.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 */
static inline void FTM_HAL_EnableChnInt(FTM_Type *ftmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    FTM_BWR_CnSC_CHIE(ftmBase, channel, 1);
}
/*!
 * @brief Disables the FTM peripheral timer channel(n) interrupt.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 */
static inline void FTM_HAL_DisableChnInt(FTM_Type *ftmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    FTM_BWR_CnSC_CHIE(ftmBase, channel, 0);
}

/*!
 * @brief Returns whether any event for the FTM peripheral timer channel has occurred.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 * @return true if event occurred, false otherwise.
 */
static inline bool FTM_HAL_HasChnEventOccurred(FTM_Type *ftmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    return (FTM_BRD_CnSC_CHF(ftmBase, channel)) ? true : false;
}

/*!
 * @brief Clears the channel flag by writing a 0 to the CHF bit.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 */
static inline void FTM_HAL_ClearChnEventFlag(FTM_Type *ftmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    FTM_BWR_CnSC_CHF(ftmBase, channel, 0);
}

/*FTM channel control*/
/*!
 * @brief Sets the FTM peripheral timer channel counter value.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 * @param val counter value to be set
 */
static inline void FTM_HAL_SetChnCountVal(FTM_Type *ftmBase, uint8_t channel, uint16_t val)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    FTM_WR_CnV_VAL(ftmBase, channel, val);
}

/*!
 * @brief Gets the FTM peripheral timer channel counter value.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 * @return return channel counter value
 */
static inline uint16_t FTM_HAL_GetChnCountVal(FTM_Type *ftmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    return FTM_RD_CnV_VAL(ftmBase, channel);
}

/*!
 * @brief Gets the FTM peripheral timer  channel event status.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 * @return return channel event status value
 */
static inline uint32_t FTM_HAL_GetChnEventStatus(FTM_Type *ftmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    return (FTM_RD_STATUS(ftmBase) & (1U << channel)) ? true : false;
}

/*!
 * @brief Clears the FTM peripheral timer all channel event status.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 */
static inline void FTM_HAL_ClearChnEventStatus(FTM_Type *ftmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    FTM_CLR_STATUS(ftmBase, 1U << channel);
}

/*!
 * @brief Writes the provided value to the OUTMASK register.
 *
 * This function will mask/uumask multiple channels.
 *
 * @param ftmBase The FTM base address pointer
 * @param regVal  value to be written to the register
 */
static inline void FTM_HAL_SetOutmaskReg(FTM_Type *ftmBase, uint32_t regVal)
{
    FTM_WR_OUTMASK(ftmBase, regVal);
}

/*!
 * @brief Sets the FTM peripheral timer channel output mask.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 * @param mask mask to be set 0 or 1, unmasked or masked
 */
static inline void FTM_HAL_SetChnOutputMask(FTM_Type *ftmBase, uint8_t channel, bool  mask)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    mask ? FTM_SET_OUTMASK(ftmBase, 1U << channel) : FTM_CLR_OUTMASK(ftmBase, 1U << channel);
}

/*!
 * @brief Sets the FTM peripheral timer channel output initial state 0 or 1.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 * @param state counter value to be set 0 or 1
 */
static inline void FTM_HAL_SetChnOutputInitStateCmd(FTM_Type *ftmBase, uint8_t channel, uint8_t state)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    FTM_CLR_OUTINIT(ftmBase, 1U << channel);
    FTM_SET_OUTINIT(ftmBase, (uint8_t)(state << channel));
}

/*!
 * @brief Sets the FTM peripheral timer channel output polarity.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 * @param pol polarity to be set 0 or 1
 */
static inline void FTM_HAL_SetChnOutputPolarityCmd(FTM_Type *ftmBase, uint8_t channel, uint8_t pol)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    FTM_CLR_POL(ftmBase, 1U << channel);
    FTM_SET_POL(ftmBase, (uint8_t)(pol << channel));
}
/*!
 * @brief Sets the FTM peripheral timer channel input polarity.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number
 * @param pol polarity  to be set, 0: active high, 1:active low
 */
static inline void FTM_HAL_SetChnFaultInputPolarityCmd(FTM_Type *ftmBase, uint8_t channel, uint8_t pol)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    FTM_CLR_FLTPOL(ftmBase, 1U << channel);
    FTM_SET_FLTPOL(ftmBase, (uint8_t)(pol << channel));
}


/*Feature mode selection HAL*/
    /*FTM fault control*/
/*!
 * @brief Enables the FTM peripheral timer fault interrupt.
 *
 * @param ftmBase The FTM base address pointer
 */
static inline void FTM_HAL_EnableFaultInt(FTM_Type *ftmBase)
{
    FTM_BWR_MODE_FAULTIE(ftmBase, 1);
}

/*!
 * @brief Disables the FTM peripheral timer fault interrupt.
 *
 * @param ftmBase The FTM base address pointer
 */
static inline void FTM_HAL_DisableFaultInt(FTM_Type *ftmBase)
{
    FTM_BWR_MODE_FAULTIE(ftmBase, 0);
}

/*!
 * @brief Defines the FTM fault control mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param mode, valid options are 1, 2, 3, 4
 */
static inline void FTM_HAL_SetFaultControlMode(FTM_Type *ftmBase, uint8_t mode)
{
    FTM_BWR_MODE_FAULTM(ftmBase, mode);
}

/*!
 * @brief Enables or disables the FTM peripheral timer capture test mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true to enable capture test mode, false to disable
 */
static inline void FTM_HAL_SetCaptureTestCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_MODE_CAPTEST(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Enables or disables the FTM write protection.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true: Write-protection is enabled, false: Write-protection is disabled
 */
static inline void FTM_HAL_SetWriteProtectionCmd(FTM_Type *ftmBase, bool enable)
{
     enable ? FTM_BWR_FMS_WPEN(ftmBase, 1) : FTM_BWR_MODE_WPDIS(ftmBase, 1);
}

/*!
 * @brief Enables the FTM peripheral timer group.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true: all registers including FTM-specific registers are available
 *                false: only the TPM-compatible registers are available
 */
static inline void FTM_HAL_Enable(FTM_Type *ftmBase, bool enable)
{
     assert(FTM_BRD_MODE_WPDIS(ftmBase));
     FTM_BWR_MODE_FTMEN(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Initializes the channels output.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true: the channels output is initialized according to the state of OUTINIT reg
 *                false: has no effect
 */
static inline void FTM_HAL_SetInitChnOutputCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_MODE_INIT(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets the FTM peripheral timer sync mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true: no restriction both software and hardware triggers can be used\n
 *                false: software trigger can only be used for MOD and CnV synch, hardware trigger
 *                       only for OUTMASK and FTM counter synch.
 */
static inline void FTM_HAL_SetPwmSyncMode(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_MODE_PWMSYNC(ftmBase, enable ? 1 : 0);
}

/*FTM synchronization control*/
/*!
 * @brief Enables or disables the FTM peripheral timer software trigger.
 *
 * @param ftmBase The FTM base address pointer.
 * @param enable  true: software trigger is selected, false: software trigger is not selected
 */
static inline void FTM_HAL_SetSoftwareTriggerCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNC_SWSYNC(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets the FTM peripheral timer hardware trigger.
 *
 * @param ftmBase The FTM base address pointer
 * @param trigger_num  0, 1, 2 for trigger0, trigger1, and trigger3
 * @param enable true: enable hardware trigger from field trigger_num for PWM synch
 *               false: disable hardware trigger from field trigger_num for PWM synch
 */
void FTM_HAL_SetHardwareSyncTriggerSrc(FTM_Type *ftmBase, uint32_t trigger_num, bool enable);

/*!
 * @brief Determines when the OUTMASK register is updated with the value of its buffer.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true if OUTMASK register is updated only by PWM sync\n
 *                false if OUTMASK register is updated in all rising edges of the system clock
 */
static inline void FTM_HAL_SetOutmaskPwmSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNC_SYNCHOM(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Determines if the FTM counter is re-initialized when the selected trigger for
 * synchronization is detected.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  True to update FTM counter when triggered , false to count normally
 */
static inline void FTM_HAL_SetCountReinitSyncCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNC_REINIT(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Enables or disables the FTM peripheral timer maximum loading points.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  True to enable maximum loading point, false to disable
 */
static inline void FTM_HAL_SetMaxLoadingCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNC_CNTMAX(ftmBase, enable ? 1 : 0);
}
/*!
 * @brief Enables or disables the FTM peripheral timer minimum loading points.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  True to enable minimum loading point, false to disable
 */
static inline void FTM_HAL_SetMinLoadingCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNC_CNTMIN(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Combines the channel control.
 *
 * Returns an index for each channel pair.
 *
 * @param channel  The FTM peripheral channel number.
 * @return 0 for channel pair 0 & 1\n
 *         1 for channel pair 2 & 3\n
 *         2 for channel pair 4 & 5\n
 *         3 for channel pair 6 & 7
 */
uint32_t FTM_HAL_GetChnPairIndex(uint8_t channel);

/*!
 * @brief Enables the FTM peripheral timer channel pair fault control.
 *
 * @param ftmBase The FTM base address pointer
 * @param chnlPairNum The FTM peripheral channel pair number
 * @param enable  True to enable fault control, false to disable
 */
static inline  void FTM_HAL_SetDualChnFaultCmd(FTM_Type *ftmBase, uint8_t chnlPairNum, bool enable)
{
    assert(chnlPairNum < (FSL_FEATURE_FTM_CHANNEL_COUNT / 2));

    enable ? FTM_SET_COMBINE(ftmBase, FTM_COMBINE_FAULTEN0_MASK << (chnlPairNum * FTM_COMBINE_CHAN_CTRL_WIDTH)):
             FTM_CLR_COMBINE(ftmBase, FTM_COMBINE_FAULTEN0_MASK << (chnlPairNum * FTM_COMBINE_CHAN_CTRL_WIDTH));
}

/*!
 * @brief Enables or disables the FTM peripheral timer channel pair counter PWM sync.
 *
 * @param ftmBase The FTM base address pointer
 * @param chnlPairNum The FTM peripheral channel pair number
 * @param enable  True to enable PWM synchronization, false to disable
 */
static inline void FTM_HAL_SetDualChnPwmSyncCmd(FTM_Type *ftmBase, uint8_t chnlPairNum, bool enable)
{
    assert(chnlPairNum < (FSL_FEATURE_FTM_CHANNEL_COUNT / 2));

    enable ? FTM_SET_COMBINE(ftmBase, FTM_COMBINE_SYNCEN0_MASK << (chnlPairNum * FTM_COMBINE_CHAN_CTRL_WIDTH)):
             FTM_CLR_COMBINE(ftmBase, FTM_COMBINE_SYNCEN0_MASK << (chnlPairNum * FTM_COMBINE_CHAN_CTRL_WIDTH));
}

/*!
 * @brief Enables or disabled the FTM peripheral timer channel pair deadtime insertion.
 *
 * @param ftmBase The FTM base address pointer
 * @param chnlPairNum The FTM peripheral channel pair number
 * @param enable  True to enable deadtime insertion, false to disable
 */
static inline void FTM_HAL_SetDualChnDeadtimeCmd(FTM_Type *ftmBase, uint8_t chnlPairNum, bool enable)
{
    assert(chnlPairNum < FSL_FEATURE_FTM_CHANNEL_COUNT);

    enable ? FTM_SET_COMBINE(ftmBase, FTM_COMBINE_DTEN0_MASK << (chnlPairNum * FTM_COMBINE_CHAN_CTRL_WIDTH)):
             FTM_CLR_COMBINE(ftmBase, FTM_COMBINE_DTEN0_MASK << (chnlPairNum * FTM_COMBINE_CHAN_CTRL_WIDTH));
}

/*!
 * @brief Enables or disables the FTM peripheral timer channel dual edge capture decap.
 *
 * @param ftmBase The FTM base address pointer
 * @param chnlPairNum The FTM peripheral channel pair number
 * @param enable  True to enable dual edge capture mode, false to disable
 */
static inline void FTM_HAL_SetDualChnDecapCmd(FTM_Type *ftmBase, uint8_t chnlPairNum, bool enable)
{
    assert(chnlPairNum < (FSL_FEATURE_FTM_CHANNEL_COUNT / 2));

    enable ? FTM_SET_COMBINE(ftmBase, FTM_COMBINE_DECAP0_MASK << (chnlPairNum * FTM_COMBINE_CHAN_CTRL_WIDTH)):
             FTM_CLR_COMBINE(ftmBase, FTM_COMBINE_DECAP0_MASK << (chnlPairNum * FTM_COMBINE_CHAN_CTRL_WIDTH));
}

/*!
 * @brief Enables the FTM peripheral timer dual edge capture mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param chnlPairNum The FTM peripheral channel pair number
 * @param enable  True to enable dual edge capture, false to disable
 */
static inline void FTM_HAL_SetDualEdgeCaptureCmd(FTM_Type *ftmBase, uint8_t chnlPairNum, bool enable)
{
    assert(chnlPairNum < (FSL_FEATURE_FTM_CHANNEL_COUNT / 2));

    enable ? FTM_SET_COMBINE(ftmBase, FTM_COMBINE_DECAPEN0_MASK << (chnlPairNum * FTM_COMBINE_CHAN_CTRL_WIDTH)):
             FTM_CLR_COMBINE(ftmBase, FTM_COMBINE_DECAPEN0_MASK << (chnlPairNum * FTM_COMBINE_CHAN_CTRL_WIDTH));
}

/*!
 * @brief Enables or disables the FTM peripheral timer channel pair output complement mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param chnlPairNum The FTM peripheral channel pair number
 * @param enable  True to enable complementary mode, false to disable
 */
static inline void FTM_HAL_SetDualChnCompCmd(FTM_Type *ftmBase, uint8_t chnlPairNum, bool enable)
{
    assert(chnlPairNum < (FSL_FEATURE_FTM_CHANNEL_COUNT / 2));

    enable ? FTM_SET_COMBINE(ftmBase, FTM_COMBINE_COMP0_MASK << (chnlPairNum * FTM_COMBINE_CHAN_CTRL_WIDTH)):
             FTM_CLR_COMBINE(ftmBase, FTM_COMBINE_COMP0_MASK << (chnlPairNum * FTM_COMBINE_CHAN_CTRL_WIDTH));

}

/*!
 * @brief Enables or disables the FTM peripheral timer channel pair output combine mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param chnlPairNum The FTM peripheral channel pair number
 * @param enable  True to enable channel pair to combine, false to disable
 */
static inline void FTM_HAL_SetDualChnCombineCmd(FTM_Type *ftmBase, uint8_t chnlPairNum, bool enable)
{
    assert(chnlPairNum < (FSL_FEATURE_FTM_CHANNEL_COUNT / 2));

    enable ? FTM_SET_COMBINE(ftmBase, FTM_COMBINE_COMBINE0_MASK << (chnlPairNum * FTM_COMBINE_CHAN_CTRL_WIDTH)):
             FTM_CLR_COMBINE(ftmBase, FTM_COMBINE_COMBINE0_MASK << (chnlPairNum * FTM_COMBINE_CHAN_CTRL_WIDTH));
}

/*FTM dead time insertion control*/
/*!
 * @brief Sets the FTM deadtime divider.
 *
 * @param ftmBase The FTM base address pointer
 * @param divider  The FTM peripheral prescale divider\n
 *                 0x :divided by 1, 10: divided by 4, 11:divided by 16
 */
static inline void FTM_HAL_SetDeadtimePrescale(FTM_Type *ftmBase, ftm_deadtime_ps_t divider)
{
    FTM_WR_DEADTIME_DTPS(ftmBase, divider);
}

/*!
 * @brief Sets the FTM deadtime value.
 *
 * @param ftmBase The FTM base address pointer
 * @param count  The FTM peripheral  prescale divider\n
 *               0: no counts inserted, 1: 1 count is inserted, 2: 2 count is inserted....
 */
static inline void FTM_HAL_SetDeadtimeCount(FTM_Type *ftmBase, uint8_t count)
{
    FTM_WR_DEADTIME_DTVAL(ftmBase, count);
}

/*!
* @brief Enables or disables the generation of the trigger when the FTM counter is equal to the CNTIN register.
*
* @param ftmBase The FTM base address pointer
* @param enable  True to enable, false to disable
*/
static inline void FTM_HAL_SetInitTriggerCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_EXTTRIG_INITTRIGEN(ftmBase, enable ? 1 : 0);
}

/*FTM external trigger */
/*!
 * @brief Enables or disables the generation of the FTM peripheral timer channel trigger.
 *
 * Enables or disables the generation of the FTM peripheral timer channel trigger when the
 * FTM counter is equal to its initial value. Channels 6 and 7 cannot be used as triggers.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel Channel to be enabled,  valid value 0, 1, 2, 3, 4, 5
 * @param val  True to enable, false to disable
 */
void FTM_HAL_SetChnTriggerCmd(FTM_Type *ftmBase, uint8_t channel, bool val);

/*!
 * @brief Checks whether any channel trigger event has occurred.
 *
 * @param ftmBase The FTM base address pointer
 * @return true if there is a channel trigger event, false if not.
 */
static inline bool FTM_HAL_IsChnTriggerGenerated(FTM_Type *ftmBase)
{
    return FTM_BRD_EXTTRIG_TRIGF(ftmBase);
}

/*Fault mode status*/
/*!
 * @brief Gets the FTM detected fault input.
 *
 * This function reads the status for all fault inputs
 *
 * @param ftmBase The FTM base address pointer
 * @return Return fault byte
 */
static inline uint8_t FTM_HAL_GetDetectedFaultInput(FTM_Type *ftmBase)
{
    return (FTM_RD_FMS(ftmBase) & 0x0f);
}

/*!
 * @brief Checks whether the write protection is enabled.
 *
 * @param ftmBase The FTM base address pointer
 * @return True if enabled, false if not
 */
static inline bool FTM_HAL_IsWriteProtectionEnabled(FTM_Type *ftmBase)
{
    return FTM_BRD_FMS_WPEN(ftmBase) ? true : false;
}

/*Quadrature decoder control*/

/*!
 * @brief Enables the channel quadrature decoder.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  True to enable, false to disable
 */
static inline void FTM_HAL_SetQuadDecoderCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_QDCTRL_QUADEN(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Enables or disables the phase A input filter.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable true enables the phase input filter, false disables the filter
 */
static inline void FTM_HAL_SetQuadPhaseAFilterCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_QDCTRL_PHAFLTREN(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Enables or disables the phase B input filter.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable true enables the phase input filter, false disables the filter
 */
static inline void FTM_HAL_SetQuadPhaseBFilterCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_QDCTRL_PHBFLTREN(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Selects polarity for the quadrature decode phase A input.
 *
 * @param ftmBase The FTM base address pointer
 * @param mode 0: Normal polarity, 1: Inverted polarity
 */
static inline void FTM_HAL_SetQuadPhaseAPolarity(FTM_Type *ftmBase,
                                                           ftm_quad_phase_polarity_t mode)
{
    FTM_BWR_QDCTRL_PHAPOL(ftmBase, mode);
}

/*!
 * @brief Selects polarity for the quadrature decode phase B input.
 *
 * @param ftmBase The FTM base address pointer
 * @param mode 0: Normal polarity, 1: Inverted polarity
 */
static inline void FTM_HAL_SetQuadPhaseBPolarity(FTM_Type *ftmBase,
                                                           ftm_quad_phase_polarity_t mode)
{
    FTM_BWR_QDCTRL_PHBPOL(ftmBase, mode);
}

/*!
 * @brief Sets the encoding mode used in quadrature decoding mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param quadMode 0: Phase A and Phase B encoding mode\n
 *                 1: Count and direction encoding mode
 */
static inline void FTM_HAL_SetQuadMode(FTM_Type *ftmBase, ftm_quad_decode_mode_t quadMode)
{
    FTM_BWR_QDCTRL_QUADMODE(ftmBase, quadMode);
}

/*!
 * @brief Gets the FTM counter direction in quadrature mode.
 *
 * @param ftmBase The FTM base address pointer
 *
 * @return 1 if counting direction is increasing, 0 if counting direction is decreasing
 */
static inline uint8_t FTM_HAL_GetQuadDir(FTM_Type *ftmBase)
{
    return FTM_BRD_QDCTRL_QUADMODE(ftmBase);
}

/*!
 * @brief Gets the timer overflow direction in quadrature mode.
 *
 * @param ftmBase The FTM base address pointer
 *
 * @return 1 if TOF bit was set on the top of counting, 0 if TOF bit was set on the bottom of counting
 */
static inline uint8_t FTM_HAL_GetQuadTimerOverflowDir(FTM_Type *ftmBase)
{
    return FTM_BRD_QDCTRL_TOFDIR(ftmBase);
}

/*!
 * @brief Sets the FTM peripheral timer channel input capture filter value.
 * @param ftmBase The FTM base address pointer
 * @param channel  The FTM peripheral channel number, only 0, 1, 2, 3, channel 4, 5, 6, 7 don't have.
 * @param val  Filter value to be set
 */
void FTM_HAL_SetChnInputCaptureFilter(FTM_Type *ftmBase, uint8_t channel, uint8_t val);

/*!
 * @brief Sets the fault input filter value.
 *
 * @param ftmBase The FTM base address pointer
 * @param val fault input filter value
 */
static inline void FTM_HAL_SetFaultInputFilterVal(FTM_Type *ftmBase, uint32_t val)
{
    FTM_BWR_FLTCTRL_FFVAL(ftmBase, val);
}

/*!
 * @brief Enables or disables the fault input filter.
 *
 * @param ftmBase The FTM base address pointer
 * @param inputNum fault input to be configured, valid value 0, 1, 2, 3
 * @param val  true to enable fault input filter, false to disable fault input filter
 */
static inline void FTM_HAL_SetFaultInputFilterCmd(FTM_Type *ftmBase, uint8_t inputNum, bool val)
{
    assert(inputNum < CHAN4_IDX);
    val ? FTM_SET_FLTCTRL(ftmBase, (1U << (inputNum + 4))) :
          FTM_CLR_FLTCTRL(ftmBase, (1U << (inputNum + 4)));
}

/*!
 * @brief Enables or disables the fault input.
 *
 * @param ftmBase The FTM base address pointer
 * @param inputNum fault input to be configured, valid value 0, 1, 2, 3
 * @param val  true to enable fault input, false to disable fault input
 */
static inline void FTM_HAL_SetFaultInputCmd(FTM_Type *ftmBase, uint8_t inputNum, bool val)
{
    assert(inputNum < CHAN4_IDX);
    val ? FTM_SET_FLTCTRL(ftmBase, (1U << inputNum)) :
          FTM_CLR_FLTCTRL(ftmBase, (1U << inputNum));
}

/*!
 * @brief Enables or disables the channel invert for a channel pair.
 *
 * @param ftmBase The FTM base address pointer
 * @param chnlPairNum The FTM peripheral channel pair number
 * @param val  true to enable channel inverting, false to disable channel inver
 */
static inline void FTM_HAL_SetDualChnInvertCmd(FTM_Type *ftmBase, uint8_t chnlPairNum, bool val)
{
    assert(chnlPairNum < (FSL_FEATURE_FTM_CHANNEL_COUNT / 2));

    val ? FTM_SET_INVCTRL(ftmBase, (1U << chnlPairNum)) :
          FTM_CLR_INVCTRL(ftmBase, (1U << chnlPairNum));
}

/*!
 * @brief Writes the provided value to the Inverting Control register.
 *
 * This function is enable/disable inverting control on multiple channel pairs.
 *
 * @param ftmBase The FTM base address pointer
 * @param regVal  value to be written to the register
 */
static inline void FTM_HAL_SetInvctrlReg(FTM_Type *ftmBase, uint32_t regVal)
{
    FTM_WR_INVCTRL(ftmBase, regVal);
}

/*FTM software output control*/
/*!
 * @brief Enables or disables the channel software output control.
 * @param ftmBase The FTM base address pointer
 * @param channel Channel to be enabled or disabled
 * @param val  true to enable, channel output will be affected by software output control\n
                  false to disable, channel output is unaffected
 */
static inline void FTM_HAL_SetChnSoftwareCtrlCmd(FTM_Type *ftmBase, uint8_t channel, bool val)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    val ? FTM_SET_SWOCTRL(ftmBase, (1U << channel)) :
          FTM_CLR_SWOCTRL(ftmBase, (1U << channel));
}
/*!
 * @brief Sets the channel software output control value.
 *
 * @param ftmBase The FTM base address pointer.
 * @param channel Channel to be configured
 * @param val  True to set 1, false to set 0
 */
static inline void FTM_HAL_SetChnSoftwareCtrlVal(FTM_Type *ftmBase, uint8_t channel, bool val)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    val ? FTM_SET_SWOCTRL(ftmBase, (1U << (channel + 8))) :
          FTM_CLR_SWOCTRL(ftmBase, (1U << (channel + 8)));
}

/*FTM PWM load control*/
/*!
 * @brief Enables or disables the loading of MOD, CNTIN, and CV with values of their write buffer.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true to enable, false to disable
 */
static inline void FTM_HAL_SetPwmLoadCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_PWMLOAD_LDOK(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Includes or excludes the channel in the matching process.
 *
 * @param ftmBase The FTM base address pointer
 * @param channel Channel to be configured
 * @param val  true means include the channel in the matching process\n
 *                false means do not include channel in the matching process
 */
static inline void FTM_HAL_SetPwmLoadChnSelCmd(FTM_Type *ftmBase, uint8_t channel, bool val)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    val ? FTM_SET_PWMLOAD(ftmBase, 1U << channel) : FTM_CLR_PWMLOAD(ftmBase, 1U << channel);
}

/*FTM configuration*/
/*!
 * @brief Enables or disables the FTM global time base signal generation to other FTM's.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  True to enable, false to disable
 */
static inline void FTM_HAL_SetGlobalTimeBaseOutputCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_CONF_GTBEOUT(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Enables or disables the FTM timer global time base.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  True to enable, false to disable
 */
static inline void FTM_HAL_SetGlobalTimeBaseCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_CONF_GTBEEN(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets the BDM mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param val FTM behaviour in BDM mode, options are defined in the enum ftm_bdm_mode_t
 */
static inline void FTM_HAL_SetBdmMode(FTM_Type *ftmBase, ftm_bdm_mode_t val)
{
    FTM_WR_CONF_BDMMODE(ftmBase, val);
}

/*!
 * @brief Sets the FTM timer TOF Frequency
 *
 * @param ftmBase The FTM base address pointer
 * @param val  Value of the TOF bit set frequency
 */
static inline void FTM_HAL_SetTofFreq(FTM_Type *ftmBase, uint8_t val)
{
    FTM_WR_CONF_NUMTOF(ftmBase, val);
}

/*FTM sync configuration*/

/*!
 * @brief Sets the FTM register synchronization method.
 *
 * This function will set the necessary bits for the synchronization mode that user wishes to use.
 *
 * @param ftmBase The FTM base address pointer
 * @param syncMethod  Synchronization method defined by ftm_sync_method_t enum. User can choose
 *                    multiple synch methods by OR'ing options
 */
void FTM_HAL_SetSyncMode(FTM_Type *ftmBase, uint32_t syncMethod);

/*!
 * @brief Sets the sync mode for the FTM SWOCTRL register when using a hardware trigger.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true means the hardware trigger activates register sync\n
 *                false means the hardware trigger does not activate register sync.
 */
static inline void FTM_HAL_SetSwoctrlHardwareSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNCONF_HWSOC(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM INVCTRL register when using a hardware trigger.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true means the hardware trigger activates register sync\n
 *                false means the hardware trigger does not activate register sync.
 */
static inline void FTM_HAL_SetInvctrlHardwareSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNCONF_HWINVC(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM OUTMASK register when using a hardware trigger.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true means hardware trigger activates register sync\n
 *                false means hardware trigger does not activate register sync.
 */
static inline void FTM_HAL_SetOutmaskHardwareSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNCONF_HWOM(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM MOD, CNTIN and CV registers when using a hardware trigger.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true means hardware trigger activates register sync\n
 *                false means hardware trigger does not activate register sync.
 */
static inline void FTM_HAL_SetModCntinCvHardwareSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNCONF_HWWRBUF(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM counter register when using a hardware trigger.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true means hardware trigger activates register sync\n
 *                false means hardware trigger does not activate register sync.
 */
static inline void FTM_HAL_SetCounterHardwareSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNCONF_HWRSTCNT(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM SWOCTRL register when using a software trigger.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true means software trigger activates register sync\n
 *                false means software trigger does not activate register sync.
 */
static inline void FTM_HAL_SetSwoctrlSoftwareSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNCONF_SWSOC(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM INVCTRL register when using a software trigger.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true means software trigger activates register sync\n
 *                false means software trigger does not activate register sync.
 */
static inline void FTM_HAL_SetInvctrlSoftwareSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNCONF_SWINVC(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM OUTMASK register when using a software trigger.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true means software trigger activates register sync\n
 *                false means software trigger does not activate register sync.
 */
static inline void FTM_HAL_SetOutmaskSoftwareSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNCONF_SWOM(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets synch mode for FTM MOD, CNTIN, and CV registers when using a software trigger.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true means software trigger activates register sync\n
 *                false means software trigger does not activate register sync.
 */
static inline void FTM_HAL_SetModCntinCvSoftwareSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNCONF_SWWRBUF(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM counter register when using a software trigger.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true means software trigger activates register sync\n
 *                false means software trigger does not activate register sync.
 */
static inline void FTM_HAL_SetCounterSoftwareSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNCONF_SWRSTCNT(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets the PWM synchronization mode to enhanced or legacy.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true means use Enhanced PWM synchronization\n
 *                false means to use Legacy mode
 */
static inline void FTM_HAL_SetPwmSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNCONF_SYNCMODE(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets the SWOCTRL register PWM synchronization mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true means SWOCTRL register is updated by PWM synch\n
 *                false means SWOCTRL register is updated at all rising edges of system clock
 */
static inline void FTM_HAL_SetSwoctrlPwmSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNCONF_SWOC(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets the INVCTRL register PWM synchronization mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true means INVCTRL register is updated by PWM synch\n
 *                false means INVCTRL register is updated at all rising edges of system clock
 */
static inline void FTM_HAL_SetInvctrlPwmSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNCONF_INVC(ftmBase, enable ? 1 : 0);
}

/*!
 * @brief Sets the CNTIN register PWM synchronization mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param enable  true means CNTIN register is updated by PWM synch\n
 *                false means CNTIN register is updated at all rising edges of system clock
 */
static inline void FTM_HAL_SetCntinPwmSyncModeCmd(FTM_Type *ftmBase, bool enable)
{
    FTM_BWR_SYNCONF_CNTINC(ftmBase, enable ? 1 : 0);
}


/*HAL functionality*/
/*!
 * @brief Resets the FTM registers
 *
 * @param ftmBase The FTM base address pointer
 */
void FTM_HAL_Reset(FTM_Type *ftmBase);

/*!
 * @brief Initializes the FTM.
 *
 * @param ftmBase The FTM base address pointer.
 */
void FTM_HAL_Init(FTM_Type *ftmBase);

/*!
 * @brief Enables the FTM timer when it is PWM output mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param config PWM configuration parameter
 * @param channel The channel or channel pair number(combined mode).
 */
void FTM_HAL_EnablePwmMode(FTM_Type *ftmBase, ftm_pwm_param_t *config, uint8_t channel);

/*!
 * @brief Disables the PWM output mode.
 *
 * @param ftmBase The FTM base address pointer
 * @param config PWM configuration parameter
 * @param channel The channel or channel pair number(combined mode).
 */
void FTM_HAL_DisablePwmMode(FTM_Type *ftmBase, ftm_pwm_param_t *config, uint8_t channel);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_FTM_COUNT */

#endif /* __FSL_FTM_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

