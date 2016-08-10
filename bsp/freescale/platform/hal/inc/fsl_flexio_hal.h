/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
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

#ifndef __FSL_FLEXIO_HAL_H__
#define __FSL_FLEXIO_HAL_H__

#include <stdint.h>
#include <stdbool.h>

#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_FLEXIO_COUNT

/*!
 * @addtogroup flexio_hal
 * @{
 */

/*******************************************************************************
 * Enumeration.
 ******************************************************************************/
/*!
 * @brief FlexIO status return code.
 */
typedef enum
{
    kStatus_FLEXIO_Success = 0U,         /*!< Success. */
    kStatus_FLEXIO_InvalidArgument = 1U, /*!< Invalid argument existed. */
    kStatus_FLEXIO_Failed = 2U           /*!< Execution failed. */
} flexio_status_t;

/*!
 * @brief Define time of timer trigger polarity.
 */
typedef enum _flexio_timer_trigger_polarity
{
    kFlexioTimerTriggerPolarityActiveHigh = 0U, /*!< Active high. */
    kFlexioTimerTriggerPolarityActiveLow  = 1U  /*!< Active low. */
} flexio_timer_trigger_polarity_t;

/*!
 * @brief Define type of timer trigger source.
 */
typedef enum _flexio_timer_trigger_source
{
    kFlexioTimerTriggerSourceExternal = 0U, /*!< External trigger selected. */
    kFlexioTimerTriggerSourceInternal = 1U  /*!< Internal trigger selected. */
} flexio_timer_trigger_source_t;

/*!
 * @brief Define type of timer/shifter pin configuration.
 */
typedef enum _flexio_pin_config
{
    kFlexioPinConfigOutputDisabled         = 0U, /*!< Pin output disabled. */
    kFlexioPinConfigOpenDrainOrBidirection = 1U, /*!< Pin open drain or bidirectional output enable. */
    kFlexioPinConfigBidirectionOutputData  = 2U, /*!< Pin bidirectional output data. */
    kFlexioPinConfigOutput                 = 3U  /*!< Pin output. */
} flexio_pin_config_t;

/*!
 * @brief Definition of pin polarity.
 */
typedef enum _flexio_pin_polarity
{
    kFlexioPinActiveHigh = 0U, /*!< Active high. */
    kFlexioPinActiveLow  = 1U  /*!< Active low. */
} flexio_pin_polarity_t;

/*!
 * @brief Define type of timer work mode.
 */
typedef enum _flexio_timer_mode 
{
    kFlexioTimerModeDisabled        = 0U, /*!< Timer Disabled. */
    kFlexioTimerModeDual8BitBaudBit = 1U, /*!< Dual 8-bit counters baud/bit mode. */
    kFlexioTimerModeDual8BitPWM     = 2U, /*!< Dual 8-bit counters PWM mode. */
    kFlexioTimerModeSingle16Bit     = 3U  /*!< Single 16-bit counter mode. */
} flexio_timer_mode_t;

/*!
 * @brief Define type of timer initial output or timer reset condition.
 */
typedef enum _flexio_timer_output
{
    kFlexioTimerOutputOneNotAffectedByReset  = 0U, /*!< Logic one when enabled and is not affected by timer reset. */
    kFlexioTimerOutputZeroNotAffectedByReset = 1U, /*!< Logic zero when enabled and is not affected by timer reset. */
    kFlexioTimerOutputOneAffectedByReset     = 2U, /*!< Logic one when enabled and on timer reset. */
    kFlexioTimerOutputZeroAffectedByReset    = 3U  /*!< Logic zero when enabled and on timer reset. */
} flexio_timer_output_t;

/*!
 * @brief Define type of timer decrement.
 */
typedef enum _flexio_timer_decrement_source
{
    kFlexioTimerDecSrcOnFlexIOClockShiftTimerOutput   = 0U, /*!< Decrement counter on FlexIO clock, Shift clock equals Timer output. */
    kFlexioTimerDecSrcOnTriggerInputShiftTimerOutput  = 1U, /*!< Decrement counter on Trigger input (both edges), Shift clock equals Timer output. */
    kFlexioTimerDecSrcOnPinInputShiftPinInput         = 2U, /*!< Decrement counter on Pin input (both edges), Shift clock equals Pin input. */
    kFlexioTimerDecSrcOnTriggerInputShiftTriggerInput = 3U  /*!< Decrement counter on Trigger input (both edges), Shift clock equals Trigger input. */
} flexio_timer_decrement_source_t;

/*!
 * @brief Define type of timer reset condition.
 */
typedef enum _flexio_timer_reset_condition
{
    kFlexioTimerResetNever                            = 0U, /*!< Timer never reset. */
    kFlexioTimerResetOnTimerPinEqualToTimerOutput     = 2U, /*!< Timer reset on Timer Pin equal to Timer Output. */
    kFlexioTimerResetOnTimerTriggerEqualToTimerOutput = 3U, /*!< Timer reset on Timer Trigger equal to Timer Output. */
    kFlexioTimerResetOnTimerPinRisingEdge             = 4U, /*!< Timer reset on Timer Pin rising edge. */
    kFlexioTimerResetOnTimerTriggerRisingEdge         = 6U, /*!< Timer reset on Trigger rising edge. */
    kFlexioTimerResetOnTimerTriggerBothEdge           = 7U  /*!< Timer reset on Trigger rising or falling edge. */
} flexio_timer_reset_condition_t;

/*!
 * @brief Define type of timer disable condition.
 */
typedef enum _flexio_timer_disable_condition
{
    kFlexioTimerDisableNever                    = 0U, /*!< Timer never disabled. */
    kFlexioTimerDisableOnPreTimerDisable        = 1U, /*!< Timer disabled on Timer N-1 disable. */
    kFlexioTimerDisableOnTimerCompare           = 2U, /*!< Timer disabled on Timer compare. */
    kFlexioTimerDisableOnTimerCompareTriggerLow = 3U, /*!< Timer disabled on Timer compare and Trigger Low. */
    kFlexioTimerDisableOnPinBothEdge            = 4U, /*!< Timer disabled on Pin rising or falling edge. */
    kFlexioTimerDisableOnPinBothEdgeTriggerHigh = 5U, /*!< Timer disabled on Pin rising or falling edge provided Trigger is high. */
    kFlexioTimerDisableOnTriggerFallingEdge     = 6U  /*!< Timer disabled on Trigger falling edge. */
} flexio_timer_disable_condition_t;

/*!
 * @brief Define type of timer enable condition.
 */
typedef enum _flexio_timer_enable_condition
{
    kFlexioTimerEnabledAlways                    = 0U, /*!< Timer always enabled. */
    kFlexioTimerEnableOnPrevTimerEnable          = 1U, /*!< Timer enabled on Timer N-1 enable. */
    kFlexioTimerEnableOnTriggerHigh              = 2U, /*!< Timer enabled on Trigger high. */
    kFlexioTimerEnableOnTriggerHighPinHigh       = 3U, /*!< Timer enabled on Trigger high and Pin high. */
    kFlexioTimerEnableOnPinRisingEdge            = 4U, /*!< Timer enabled on Pin rising edge. */
    kFlexioTimerEnableOnPinRisingEdgeTriggerHigh = 5U, /*!< Timer enabled on Pin rising edge and Trigger high. */
    kFlexioTimerEnableOnTriggerRisingEdge        = 6U, /*!< Timer enabled on Trigger rising edge. */
    kFlexioTimerEnableOnTriggerBothEdge          = 7U  /*!< Timer enabled on Trigger rising or falling edge. */
} flexio_timer_enable_condition_t;

/*!
 * @brief Define type of timer stop bit generate condition. 
 */
typedef enum _flexio_timer_stop_bit_condition
{
    kFlexioTimerStopBitDisabled                    = 0U, /*!< Stop bit disabled. */
    kFlexioTimerStopBitEnableOnTimerCompare        = 1U, /*!< Stop bit is enabled on timer compare. */
    kFlexioTimerStopBitEnableOnTimerDisable        = 2U, /*!< Stop bit is enabled on timer disable. */
    kFlexioTimerStopBitEnableOnTimerCompareDisable = 3U  /*!< Stop bit is enabled on timer compare and timer disable. */
} flexio_timer_stop_bit_condition_t;

/*!
 * @brief Define type of timer start bit generate condition. 
 */
typedef enum _flexio_timer_start_bit_condition
{
    kFlexioTimerStartBitDisabled = 0U, /*!< Start bit disabled. */
    kFlexioTimerStartBitEnabled  = 1U  /*!< Start bit enabled. */
} flexio_timer_start_bit_condition_t;

/*! @briedf Define type of timer polarity for shifter control. */
typedef enum _flexio_shifter_timer_polarity
{
    kFlexioShifterTimerPolarityOnPositive = 0U, /* Shift on positive edge of shift clock. */
    kFlexioShifterTimerPolarityOnNegitive = 1U  /* Shift on negative edge of shift clock. */
} flexio_shifter_timer_polarity_t;

/*!
 * @brief Define type of shifter working mode.
 */
typedef enum _flexio_shifter_mode
{
    kFlexioShifterDisabled            = 0U, /*!< Shifter is disabled. */
    kFlexioShifterModeReceive         = 1U, /*!< Receive mode. */
    kFlexioShifterModeTransmit        = 2U, /*!< Transmit mode. */
    kFlexioShifterModeMatchStore      = 4U, /*!< Match store mode. */
    kFlexioShifterModeMatchContinuous = 5U  /*!< Match continuous mode. */
#if FSL_FEATURE_FLEXIO_HAS_STATE_MODE
    , kFlexioShifterModeState         = 6U  /*!< SHIFTBUF contents are used for storing programmable state attributes. */
#endif /* FSL_FEATURE_FLEXIO_HAS_STATE_MODE */
#if FSL_FEATURE_FLEXIO_HAS_LOGIC_MODE
    , kFlexioShifterModeLogic         = 7U  /*!< SHIFTBUF contents are used for implementing programmable logic look up table. */
#endif /* FSL_FEATURE_FLEXIO_HAS_LOGIC_MODE */

} flexio_shifter_mode_t;

/*!
 * @brief Define type of shifter input source.
 */
typedef enum _flexio_shifter_input_source
{
    kFlexioShifterInputFromPin = 0U,              /*!< Shifter input from pin. */
    kFlexioShifterInputFromNextShifterOutput = 1U /*!< Shifter input from Shifter N+1. */
} flexio_shifter_input_source_t;

/*!
 * @brief Define of STOP bit configuration.
 */
typedef enum _flexio_shifter_stop_bit
{
    kFlexioShifterStopBitDisable = 0U, /*!< Disable shifter stop bit. */
    kFlexioShifterStopBitLow     = 2U, /*!< Set shifter stop bit to logic low level. */
    kFlexioShifterStopBitHigh    = 3U  /*!< Set shifter stop bit to logic high level. */
} flexio_shifter_stop_bit_t;

/*!
 * @brief Define type of START bit configuration.
 */
typedef enum _flexio_shifter_start_bit
{
    kFlexioShifterStartBitDisabledLoadDataOnEnable = 0U, /*!< Disable shifter start bit, transmitter loads data on enable. */
    kFlexioShifterStartBitDisabledLoadDataOnShift  = 1U, /*!< Disable shifter start bit, transmitter loads data on first shift. */
    kFlexioShifterStartBitLow                      = 2U, /*!< Set shifter start bit to logic low level. */
    kFlexioShifterStartBitHigh                     = 3U  /*!< Set shifter start bit to logic high level. */
} flexio_shifter_start_bit_t;

/*******************************************************************************
 * Definitions.
 ******************************************************************************/

/*!
 * @brief Define structure of configuring the FlexIO timer. 
 */
typedef struct _flexio_timer_config_t
{
    /* Trigger. */
    uint32_t                           trgsel; /*!< The internal trigger selection number using MACROs. */
    flexio_timer_trigger_polarity_t    trgpol; /*!< Trigger Polarity. */
    flexio_timer_trigger_source_t      trgsrc; /*!< Trigger Source, internal(see to 'trgsel') or external. */
    /* Pin. */
    flexio_pin_config_t                pincfg; /*!< Timer Pin Configuration. */
    uint32_t                           pinsel; /*!< Timer Pin number Select. */
    flexio_pin_polarity_t              pinpol; /*!< Timer Pin Polarity. */
    /* Timer. */
    flexio_timer_mode_t                timod;  /*!< Timer work Mode. */
    flexio_timer_output_t              timout; /*!< Configures the initial state of the Timer Output and whether it is affected by the Timer reset. */
    flexio_timer_decrement_source_t    timdec; /*!< Configures the source of the Timer decrement and the source of the Shift clock. */
    flexio_timer_reset_condition_t     timrst; /*!< Configures the condition that causes the timer counter (and optionally the timer output) to be reset. */
    flexio_timer_disable_condition_t   timdis; /*!< Configures the condition that causes the Timer to be disabled and stop decrementing. */
    flexio_timer_enable_condition_t    timena; /*!< Configures the condition that causes the Timer to be enabled and start decrementing. */
    flexio_timer_stop_bit_condition_t  tstop;  /*!< Timer STOP Bit generation. */
    flexio_timer_start_bit_condition_t tstart; /*!< Timer STRAT Bit generation. */
    uint32_t                           timcmp; /*!< Value for Timer Compare N Register. */
} flexio_timer_config_t;

#define FLEXIO_HAL_TIMER_TRIGGER_SEL_PININPUT(x)   ((x) << 1)
#define FLEXIO_HAL_TIMER_TRIGGER_SEL_SHIFTnSTAT(x) (((x) << 2) | 0x1)
#define FLEXIO_HAL_TIMER_TRIGGER_SEL_TIMn(x)       (((x) << 2) | 0x3)

/*!
 * @brief Define structure of configure the FlexIO shifter.
 */
typedef struct _flexio_shifter_config_t
{
    /* Timer. */
    uint32_t                        timsel; /*!< Selects which Timer is used for controlling the logic/shift register and generating the Shift clock. */
    flexio_shifter_timer_polarity_t timpol; /*!< Timer Polarity. */
    /* Pin. */
    flexio_pin_config_t             pincfg; /*!< Shifter Pin Configuration. */
    uint32_t                        pinsel; /*!< Shifter Pin number Select. */
    flexio_pin_polarity_t           pinpol; /*!< Shifter Pin Polarity. */
    /* Shifter. */
    flexio_shifter_mode_t           smode;  /*!< Configures the mode of the Shifter. */
#if FSL_FEATURE_FLEXIO_HAS_PARALLEL_WIDTH
    uint32_t                        pwidth; /*!< Configures the parallel width when using parallel mode.*/
#endif /* FSL_FEATURE_FLEXIO_HAS_PARALLEL_WIDTH */
    flexio_shifter_input_source_t   insrc;  /*!< Selects the input source for the shifter. */
    flexio_shifter_stop_bit_t       sstop;  /*!< Shifter STOP bit. */
    flexio_shifter_start_bit_t      sstart; /*!< Shifter START bit. */
} flexio_shifter_config_t;

/*******************************************************************************
 * APIs.
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*------------------------------------------------------------------------------
 * FLEXIO_VERID
 *----------------------------------------------------------------------------*/
/*!
 * @brief Gets the FlexIO major version number.
 *
 * @param base base address
 * @return major version
 */
static inline uint32_t FLEXIO_HAL_GetMajorVersionNumber(FLEXIO_Type * base)
{
    return FLEXIO_BRD_VERID_MAJOR(base);
}

/*!
 * @brief Gets the FlexIO minor version number.
 *
 * @param base base address
 * @return minor version
 */
static inline uint32_t FLEXIO_HAL_GetMinorVersionNumber(FLEXIO_Type * base)
{
    return FLEXIO_BRD_VERID_MINOR(base);
}

/*!
 * @brief Gets the FlexIO feature specification number.
 *
 * @param base base address
 * @return feature number
 */
static inline uint32_t FLEXIO_HAL_GetFeatureNumber(FLEXIO_Type * base)
{
    return FLEXIO_BRD_VERID_FEATURE(base);
}

/*------------------------------------------------------------------------------
 * FLEXIO_PARAM
 *----------------------------------------------------------------------------*/
/*!
 * @brief Gets the number of implemented external triggers.
 *
 * @param base base address
 * @return number of external triggers
 */
static inline uint32_t FLEXIO_HAL_GetTriggerNumber(FLEXIO_Type * base)
{
    return FLEXIO_BRD_PARAM_TRIGGER(base);
}

/*!
 * @brief Gets the number of implemented pins.
 *
 * @param base base address
 * @return number of pins
 */
static inline uint32_t FLEXIO_HAL_GetPinNumber(FLEXIO_Type * base)
{
    return FLEXIO_BRD_PARAM_PIN(base);
}

/*!
 * @brief Gets the number of implemented timers.
 *
 * @param base base address
 * @return number of timers
 */
static inline uint32_t FLEXIO_HAL_GetTimerNumber(FLEXIO_Type * base)
{
    return FLEXIO_BRD_PARAM_TIMER(base);
}

/*!
 * @brief Gets the number of implemented shifters.
 *
 * @param base base address
 * @return number of shifters
 */
static inline uint32_t FLEXIO_HAL_GetShifterNumber(FLEXIO_Type * base)
{
    return FLEXIO_BRD_PARAM_SHIFTER(base);
}

/*------------------------------------------------------------------------------
 * FLEXIO_CTRL
 *----------------------------------------------------------------------------*/
/*!
 * @brief Controls the FlexIO operation in doze modes.
 *
 * @param base base address
 * @param enable Pass true to enable FlexIO in Doze modes.
 */
static inline void FLEXIO_HAL_SetDozeModeCmd(FLEXIO_Type * base, bool enable)
{
    FLEXIO_BWR_CTRL_DOZEN(base, enable ? 1U : 0U);
}

/*!
 * @brief Controls the FlexIO operation in debug mode.
 *
 * @param base base address
 * @param enable Pass true to enable FlexIO in debug mode.
 */
static inline void FLEXIO_HAL_SetDebugModeCmd(FLEXIO_Type * base, bool enable)
{
    FLEXIO_BWR_CTRL_DBGE(base, enable ? 1U : 0U);
}

/*!
 * @brief Controls the FlexIO register accesses speed.
 *
 * @param base base address
 * @param enable true if fast register access is enabled, FlexIO clock to be set
 * at least twice the frequency of the bus clock. Or false if normal register 
 * accesses is selected.
 */
static inline void FLEXIO_HAL_SetFastAccessCmd(FLEXIO_Type * base, bool enable)
{
    FLEXIO_BWR_CTRL_FASTACC(base, enable ? 1U : 0U);
}

/*!
 * @brief Software reset of the module.
 *
 * @param base base address
 * @param enable true  - Enable software reset
 *               false - Clear software reset
 */
static inline void FLEXIO_HAL_SetSoftwareResetCmd(FLEXIO_Type * base, bool enable)
{
    FLEXIO_BWR_CTRL_SWRST(base, enable ? 1U : 0U);
}

/*!
 * @brief Enables the FlexIO module operation.
 *
 * @param base base address
 * @param enable Pass true to enable FlexIO
 */
static inline void FLEXIO_HAL_SetFlexioEnableCmd(FLEXIO_Type * base, bool enable)
{
    uint32_t tmp32 = FLEXIO_RD_CTRL(base);
    tmp32 &= ~FLEXIO_CTRL_FLEXEN_MASK;
    if (enable)
    {
        tmp32 |= FLEXIO_CTRL_FLEXEN_MASK;
    }
    FLEXIO_WR_CTRL(base, tmp32);
}

/*------------------------------------------------------------------------------
 * Timer
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * FLEXIO_TIMIEN - Timer Interrupt Enable Register
 *----------------------------------------------------------------------------*/
/*!
 * @brief Enables or disables the timer status interrupt requests.
 *
 * @param base base address
 * @param mask Mask of timers to be enabled/disabled interrupt status
 * @param enable Pass true to enable interrupt, false to disable
 */
void FLEXIO_HAL_SetTimerStatusIntCmd(FLEXIO_Type * base, uint32_t mask, bool enable);

/*------------------------------------------------------------------------------
 * FLEXIO_TIMSTAT - Timer Status Register
 *----------------------------------------------------------------------------*/
/*!
 * @brief Gets timer status flags.
 *
 * @param base base address
 *
 * @return timer status flags
 */
static inline uint32_t FLEXIO_HAL_GetTimerStatusFlags(FLEXIO_Type * base)
{
    return FLEXIO_BRD_TIMSTAT_TSF(base);
}

/*!
 * @brief Clears timer status flags.
 *
 * @param base base address
 * @param mask timer mask
 *
 * @return timer status flags
 */
static inline void FLEXIO_HAL_ClearTimerStatusFlags(FLEXIO_Type * base, uint32_t mask)
{
    FLEXIO_BWR_TIMSTAT_TSF(base, mask);
}

/*------------------------------------------------------------------------------
 * FLEXIO_TIMCTLn - Timer Control N Register
 * FLEXIO_TIMCFGn - Timer Configuration N Register
 * FLEXIO_TIMCMPn - Timer Compare N Register
 *----------------------------------------------------------------------------*/
/*!
 * @brief Configures a FlexIO timer.
 *
 * @param base base address
 * @param timerIdx timer id number
 * @param timerConfigPtr pointer to FlexIO's timer configuration data
 */
void FLEXIO_HAL_ConfigureTimer(FLEXIO_Type * base, uint32_t timerIdx,
    const flexio_timer_config_t *timerConfigPtr);

/*------------------------------------------------------------------------------
 * Shifter
 *----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
 * FLEXIO_SHIFTSTAT - Shifter Status Register
 *----------------------------------------------------------------------------*/
/*!
 * @brief Gets shifter status flags.
 *
 * @param base base address
 *
 * @return shifter status flags
 */
static inline uint32_t FLEXIO_HAL_GetShifterStatusFlags(FLEXIO_Type * base)
{
    return FLEXIO_BRD_SHIFTSTAT_SSF(base);
}

/*!
 * @brief Clears shifter status flags.
 *
 * @param base base address
 * @param mask shifter mask
 *
 * @return shifter status flags
 */
static inline void FLEXIO_HAL_ClearShifterStatusFlags(FLEXIO_Type * base, uint32_t mask)
{
    FLEXIO_BWR_SHIFTSTAT_SSF(base, mask);
}

/*------------------------------------------------------------------------------
 * FLEXIO_SHIFTSIEN - Shifter Status Interrupt Enable
 *----------------------------------------------------------------------------*/
/*!
 * @brief Enables or disables shifter status interrupt requests.
 *
 * @param base base address
 * @param mask Mask of shifters to be enabled/disabled status interrupt status
 * @param enable Pass true to enable interrupt, false to disable
 */
void FLEXIO_HAL_SetShifterStatusIntCmd(FLEXIO_Type * base, uint32_t mask, bool enable);

/*!
 * @brief Returns enabled shifter status interrupts.
 *
 * @param base base address
 *
 * @return mask - Mask of enabled shifter status interrupt
 */
static inline uint32_t FLEXIO_HAL_GetShifterStatusIntCmd(FLEXIO_Type * base)
{
    return FLEXIO_BRD_SHIFTSIEN_SSIE(base);
}

/*------------------------------------------------------------------------------
 * FLEXIO_SHIFTERR - Shifter Error Register
 *----------------------------------------------------------------------------*/
/*!
 * @brief Gets shifter error flags.
 *
 * @param base base address
 *
 * @return shifter error flags
 */
static inline uint32_t FLEXIO_HAL_GetShifterErrorFlags(FLEXIO_Type * base)
{
    return FLEXIO_BRD_SHIFTERR_SEF(base);
}

/*!
 * @brief Clears shifter error flags.
 *
 * @param base base address
 * @param mask shifter mask
 *
 * @return shifter error flags
 */
static inline void FLEXIO_HAL_ClearShifterErrorFlags(FLEXIO_Type * base, uint32_t mask)
{
    FLEXIO_BWR_SHIFTERR_SEF(base, mask);
}

/*------------------------------------------------------------------------------
 * FLEXIO_SHIFTEIEN - Shifter Error Interrupt Enable
 *----------------------------------------------------------------------------*/
/*!
 * @brief Returns shifter enabled error interrupts.
 *
 * @param base base address
 *
 * @return mask - Mask of enabled shifter error interrupt
 */
static inline uint32_t FLEXIO_HAL_GetShifterErrorInt(FLEXIO_Type * base)
{
    return FLEXIO_BRD_SHIFTEIEN_SEIE(base);
}

/*!
 * @brief Enables or disables shifter error interrupt requests.
 *
 * @param base base address
 * @param mask Mask of shifters to be enabled/disabled error interrupt status
 * @param enable Pass true to enable interrupt, false to disable
 */
void FLEXIO_HAL_SetShifterErrorIntCmd(FLEXIO_Type * base, uint32_t mask, bool enable);

/*------------------------------------------------------------------------------
 * FLEXIO_SHIFTCTLn - Shifter Control N Register
 * FLEXIO_SHIFTCFGn - Shifter Configuration N Register
 *----------------------------------------------------------------------------*/
/*!
 * @brief Configures a shifter including CTL and CFG
 *
 * @param base base address
 * @param shifterIdx shifter index
 * @param shifterConfigPtr pointer to shifter configuration structure
 */
void FLEXIO_HAL_ConfigureShifter(FLEXIO_Type * base, uint32_t shifterIdx,
    const flexio_shifter_config_t *shifterConfigPtr);

/*------------------------------------------------------------------------------
 * FLEXIO_SHIFTSDEN - Shifter Status DMA Enable
 *----------------------------------------------------------------------------*/
/*!
 * @brief Returns the shifter-enabled status DMA support.
 *
 * @param base base address
 *
 * @return mask Mask of shifters' DMA status
 */
static inline uint32_t FLEXIO_HAL_GetShiftStatusDma(FLEXIO_Type * base)
{
    return FLEXIO_BRD_SHIFTSDEN_SSDE(base);
}

/*!
 * @brief Enables or disables the shifter status DMA support.
 *
 * @param base base address
 * @param mask Mask of shifters to be enabled/disabled DMA status
 * @param enable Pass true to enable DMA transfer signalling
 */
void FLEXIO_HAL_SetShifterStatusDmaCmd(FLEXIO_Type * base, uint32_t mask, bool enable);

/*------------------------------------------------------------------------------
 * FLEXIO_SHIFTBUFn - Shifter Buffer N Register
 *----------------------------------------------------------------------------*/
/*!
 * @brief Stores data from the shifter buffer.
 *
 * @param base base address
 * @param shifterIdx shifter index
 *
 * @return shifter buffer content
 */
static inline uint32_t FLEXIO_HAL_GetShifterBuffer(FLEXIO_Type * base, uint32_t shifterIdx)
{
    return FLEXIO_RD_SHIFTBUF(base, shifterIdx);
}

/*!
 * @brief Loads data to the shifter buffer.
 *
 * @param base base address
 * @param shifterIdx shifter index
 * @param value Value to be load to shifter buffer
 */
static inline void FLEXIO_HAL_SetShifterBuffer(FLEXIO_Type * base, uint32_t shifterIdx, uint32_t value)
{
    FLEXIO_WR_SHIFTBUF(base, shifterIdx, value);
}

/*------------------------------------------------------------------------------
 * FLEXIO_SHIFTBUFBBSn - Shifter Buffer N Bit Byte Swapped Register
 *----------------------------------------------------------------------------*/
/*!
 * @brief Stores data from the bit byte swapped shifter buffer.
 *
 * @param base base address
 * @param shifterIdx shifter index
 *
 * @return bit byte swapped shifter buffer content
 * SHIFTBUF[24:31], SHIFTBUF[16:23], SHIFTBUF[8:15], SHIFTBUF[0:7]
 */
static inline uint32_t FLEXIO_HAL_GetShifterBufferBitByteSwapped(FLEXIO_Type * base, uint32_t shifterIdx)
{
    return FLEXIO_RD_SHIFTBUFBBS(base, shifterIdx);
}

/*!
 * @brief Loads data to the bit byte swapped shifter buffer.
 *
 * @param base base address
 * @param shifterIdx shifter index
 * @param value Value to be load to bit byte swapped shifter buffer
 */
static inline void FLEXIO_HAL_SetShifterBufferBitByteSwapped(FLEXIO_Type * base, uint32_t shifterIdx, uint32_t value)
{
    FLEXIO_WR_SHIFTBUFBBS(base, shifterIdx, value);
}

/*------------------------------------------------------------------------------
 * FLEXIO_SHIFTBUFBYSn - Shifter Buffer N Byte Swapped Register
 *----------------------------------------------------------------------------*/
/*!
 * @brief Stores data from the byte swapped shifter buffer.
 *
 * @param base base address
 * @param shifterIdx shifter index
 *
 * @return bit byte swapped shifter buffer content
 * SHIFTBUF[7:0], SHIFTBUF[15:8], SHIFTBUF[23:16], SHIFTBUF[31:24]
 */
static inline uint32_t FLEXIO_HAL_GetShifterBufferByteSwapped(FLEXIO_Type * base, uint32_t shifterIdx)
{
    return FLEXIO_RD_SHIFTBUFBYS(base, shifterIdx);
}

/*!
 * @brief Loads data to the byte swapped shifter buffer.
 *
 * @param base base address
 * @param shifterIdx shifter index
 * @param value Value to be load to byte swapped shifter buffer
 */
static inline void FLEXIO_HAL_SetShifterBufferByteSwapped(FLEXIO_Type * base, uint32_t shifterIdx, uint32_t value)
{
    FLEXIO_WR_SHIFTBUFBYS(base, shifterIdx, value);
}

/*------------------------------------------------------------------------------
 * FLEXIO_SHIFTBUFBISn - Shifter Buffer N Bit Swapped Register
 *----------------------------------------------------------------------------*/
/*!
 * @brief Stores data from the bit swapped shifter buffer.
 *
 * @param base base address
 * @param shifterIdx shifter index
 *
 * @return bit swapped shifter buffer content
 * SHIFTBUF[0:31]
 */
static inline uint32_t FLEXIO_HAL_GetShifterBufferBitSwapped(FLEXIO_Type * base, uint32_t shifterIdx)
{
    return FLEXIO_RD_SHIFTBUFBIS(base, shifterIdx);
}

/*!
 * @brief Loads data to the bit swapped shifter buffer.
 *
 * @param base base address
 * @param shifterIdx shifter index
 * @param value Value to be load to bit swapped shifter buffer
 */
static inline void FLEXIO_HAL_SetShifterBufferBitSwapped(FLEXIO_Type * base, uint32_t shifterIdx, uint32_t value)
{
    FLEXIO_WR_SHIFTBUFBIS(base, shifterIdx, value);
}

#if FSL_FEATURE_FLEXIO_HAS_SHFT_BUFFER_NIBBLE_BYTE_SWAP
/*------------------------------------------------------------------------------
 * FLEXIOx_SHIFTBUFNBSn - shifter buffer N Nibble Byte Swapped register
 *----------------------------------------------------------------------------*/
/*!
 * @brief Stores data from the shifter buffer N Nibble Byte Swapped register.
 *
 * @param base base address
 * @param shifterIdx shifter index
 *
 * @return Shifter Buffer N Nibble Byte Swapped register content
 * SHIFTBUF{ [27:24],[31:28],[19:16],[23:20],[11:8],[15:12],[3:0],[7:4]}.
 */
static inline uint32_t FLEXIO_HAL_GetShifterBufferNibbleByteSwapped(FLEXIO_Type * base, uint32_t shifterIdx)
{
    return FLEXIO_RD_SHIFTBUFNBS(base, shifterIdx);
}

/*!
 * @brief Loads data to the shifter buffer N Nibble Byte Swapped register.
 *
 * @param base base address
 * @param shifterIdx shifter index
 * @param value Value to be load to Shifter Buffer N Nibble Byte Swapped register
 */
static inline void FLEXIO_HAL_SetShifterBufferNibbleByteSwapped(FLEXIO_Type * base, uint32_t shifterIdx, uint32_t value)
{
    FLEXIO_WR_SHIFTBUFNBS(base, shifterIdx, value);
}

#endif /* FSL_FEATURE_FLEXIO_HAS_SHFT_BUFFER_NIBBLE_BYTE_SWAP */

#if FSL_FEATURE_FLEXIO_HAS_SHFT_BUFFER_HALF_WORD_SWAP
/*------------------------------------------------------------------------------
 * FLEXIOx_SHIFTBUFHWSn - shifter buffer N Half Word Swapped register
 *----------------------------------------------------------------------------*/
/*!
 * @brief Stores data from the shifter buffer N Half Word Swapped register.
 *
 * @param base base address
 * @param shifterIdx shifter index
 *
 * @return Shifter Buffer N Half Word Swapped Register content.
 * SHIFTBUF{[15:0], [31:24]}.
 */
static inline uint32_t FLEXIO_HAL_GetShifterBufferHalfWordSwapped(FLEXIO_Type * base, uint32_t shifterIdx)
{
    return FLEXIO_RD_SHIFTBUFHWS(base, shifterIdx);
}

/*!
 * @brief Loads data to the shifter buffer N Half Word Swapped register.
 *
 * @param base base address
 * @param shifterIdx shifter index
 * @param value Value to be load to Shifter Buffer N Half Word Swapped register.
 */
static inline void FLEXIO_HAL_SetShifterBufferHalfWordSwapped(FLEXIO_Type * base, uint32_t shifterIdx, uint32_t value)
{
    FLEXIO_WR_SHIFTBUFHWS(base, shifterIdx, value);
}

#endif /* FSL_FEATURE_FLEXIO_HAS_SHFT_BUFFER_HALF_WORD_SWAP */

#if FSL_FEATURE_FLEXIO_HAS_SHFT_BUFFER_NIBBLE_SWAP
/*------------------------------------------------------------------------------
 * FLEXIOx_SHIFTBUFNISn - shifter buffer N Nibble Swapped register
 *----------------------------------------------------------------------------*/
/*!
 * @brief Stores data from the shifter buffer N Nibble Swapped register.
 *
 * @param base base address
 * @param shifterIdx shifter index
 *
 * @return Shifter Buffer N Nibble Swapped Register content.
 * SHIFTBUF{[3:0],[7:4],[11:8],[15:12],[19:16],[23:20],[27:24],[31:28] }.
 */
static inline uint32_t FLEXIO_HAL_GetShifterBufferNibbleSwapped(FLEXIO_Type * base, uint32_t shifterIdx)
{
    return FLEXIO_RD_SHIFTBUFNIS(base, shifterIdx);
}

/*!
 * @brief Loads data to the shifter buffer N Nibble Swapped register.
 *
 * @param base base address
 * @param shifterIdx shifter index
 * @param value Value to be load to shifter buffer N Nibble Swapped register.
 */
static inline void FLEXIO_HAL_SetShifterBufferNibbleSwapped(FLEXIO_Type * base, uint32_t shifterIdx, uint32_t value)
{
    FLEXIO_WR_SHIFTBUFNIS(base, shifterIdx, value);
}

#endif /* FSL_FEATURE_FLEXIO_HAS_SHFT_BUFFER_NIBBLE_SWAP */

/*!
 * @brief Restores the FlexIO peripheral to reset state.
 *
 * @param base base address
 */
void FLEXIO_HAL_Init(FLEXIO_Type * base);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
#endif /* __FSL_FLEXIO_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

