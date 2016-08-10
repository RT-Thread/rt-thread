/*******************************************************************************
*
* Copyright [2014-]2014 Freescale Semiconductor, Inc.

*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale License
* distributed with this Material.
* See the LICENSE file distributed for more details.
* 
*
*******************************************************************************/

#ifndef __FSL_ENC_HAL_H__
#define __FSL_ENC_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_ENC_COUNT

/*!
 * @addtogroup enc_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Encoder status */
typedef enum _enc_status_t {
    kStatus_ENC_Success = 0U,           /*!< Encoder success status.*/
    kStatus_ENC_Error = 1U,             /*!< Encoder error status.*/
    kStatus_ENC_InvalidArgument = 2U    /*!< Encoder invalid argument.*/
} enc_status_t;

/*! @brief Encoder operation modes*/
typedef enum _enc_operation_mode_t {
    kEncNormalMode = 0U,                     /*!< Normal mode (transition signal counting).*/
    kEncModuloCountingMode = 1U,             /*!< Modulo counting mode.*/
    kEncSignalPhaseCountMode = 2U            /*!< Signal phase count mode (pulse counting).*/
} enc_operation_mode_t;

/*! @brief Encoder status flags */
typedef enum _enc_status_flag {
    kEncCmpFlag = 0U,                        /*!< Encoder Compare status flag.*/
    kEncHomeSignalFlag = 1U,                 /*!< Encoder HOME Signal transition status flag.*/
    kEncWatchdogTimeoutFlag = 2U,            /*!< Encoder Watchdog timeout status flag.*/
    kEncIndexPulseFlag = 3U,                 /*!< Encoder INDEX Pulse transition status flag.*/
    kEncRollunderFlag = 4U,                  /*!< Encoder Roll-under status flag.*/
    kEncRolloverFlag = 5U,                   /*!< Encoder Roll-over status flag.*/
    kEncSimultaneousFlag = 6U,               /*!< Encoder Simultaneous PHA and PHB change status flag.*/
    kEncCountDirectionFlag = 7U              /*!< Encoder Last count direction status flag.*/
} enc_status_flag_t;

/*! @brief Encoder interrupts*/
typedef enum _enc_int_source_t {
    kEncIntCmp = 0U,                         /*!< Compare interrupt source.*/
    kEncIntHomeSignal = 1U,                  /*!< HOME signal interrupt source.*/
    kEncIntWatchdogTimeout = 2U,             /*!< Watchdog timeout interrupt source.*/
    kEncIntIndexPulse = 3U,                  /*!< INDEX pulse interrupt source.*/
    kEncIntRollunder = 4U,                   /*!< Roll-under position counter interrupt source.*/
    kEncIntRollover = 5U,                    /*!< Roll-over position counter interrupt source.*/
    kEncIntSimultaneous = 6U                 /*!< Simultaneous PHASEA and PHASEB change interrupt source.*/
} enc_int_source_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Configuration
 * @{
 */

/*!
 * @brief Resets all configurable registers to be in the reset state for ENC.
 *
 * This function resets all configurable registers to be in the reset state for ENC.
 * It should be called before configuring the ENC module.
 *
 * @param   base    The ENC peripheral base address.
 */
void ENC_HAL_Init(ENC_Type* base);
  
/*!
 * @brief Switches to enable the Compare interrupt.
 *
 * This function allows the user to enable/disable compare interrupt.
 *
 * @param   base    The ENC module base address.
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetCmpIntCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL_CMPIE(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the Compare Interrupt configuration setting.
 *
 * This function allows the user to get the compare interrupt
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of compare interrupt setting.
 */
static inline bool ENC_HAL_GetCmpIntCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL_CMPIE(base);
}

/*!
 * @brief Gets the Compare Interrupt Request configuration setting.
 *
 * This function returns the configuration setting of the compare interrupt
 * request. This bit is set when a match occurs between the counter and
 * the COMP value. It will remain set until cleared by software.
 *
 * @param   base    The ENC module base address.
 * @return              Bit setting of the compare interrupt request bit.
 */
static inline bool ENC_HAL_GetCmpIntFlag(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL_CMPIRQ(base);
}

/*!
 * @brief Clears the Compare Interrupt Request bit pending.
 *
 * This function clears the compare interrupt request bit.
 *
 * @param   base    The ENC module base address.
 */
static inline void ENC_HAL_ClearCmpIntFlag(ENC_Type* base)
{
    ENC_BWR_CTRL_CMPIRQ(base, 1U);
}

/*!
 * @brief Switches to enable the Watchdog.
 *
 * This function allows the user to enable watchdog timer. Allow operation
 * of the watchdog timer monitoring the PHESEA and PHASEB inputs for motor
 * movement.
 *
 * @param   base    The ENC module base address. 
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetWatchdogCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL_WDE(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the Watchdog configuration setting.
 *
 * This function allows the user to get the watchdog configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of watchdog.
 */
static inline bool ENC_HAL_GetWatchdogCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL_WDE(base);
}
 
/*!
 * @brief Switches to enable the Watchdog Timeout Interrupt.
 *
 * This function allows the user to enable watchdog timeout interrupt.
 *
 * @param   base    The ENC module base address.  
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetWatchdogIntCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL_DIE(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the Watchdog Timeout Interrupt configuration setting.
 *
 * This function allows the user to get the watchdog timeout interrupt
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of wdt timeout interrupt setting.
 */
static inline bool ENC_HAL_GetWatchdogIntCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL_DIE(base);
}

/*!
 * @brief Gets the Watchdog Timeout Interrupt Request configuration setting.
 *
 * This function returns the configuration setting of the watchdog timeout
 * interrupt request. This bit is set when a watchdog timeout interrupt occurs.
 * It will remain set until cleared by software. This bit is also cleared
 * when watchdog is disabled.
 *
 * @param   base    The ENC module base address.
 * @return              Bit setting of the wdt timetout interrupt request bit.
 */
static inline bool ENC_HAL_GetWatchdogIntFlag(ENC_Type* base)
{
    return (bool)ENC_BRD_CTRL_DIRQ(base);
}

/*!
 * @brief Clears the Watchdog Timeout Interrupt Request pending.
 *
 * This function clears the watchdog timeout interrupt request bit.
 *
 * @param   base    The ENC module base address.
 */
static inline void ENC_HAL_ClearWatchdogIntFlag(ENC_Type* base)
{
    ENC_BWR_CTRL_DIRQ(base, 1U);
}

/*!
 * @brief Sets the type of INDEX pulse edge.
 *
 * This function allows the user to set the type of INDEX pulse edge used
 * to initialize the position counter.
 *
 * @param   base    The ENC module base address.
 * @param   enable      The edge type of INDEX pulse input.
 */
static inline void ENC_HAL_SetIndexPulseNegativeEdgeCmd
  (ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL_XNE(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets INDEX pulse edge configuration setting.
 *
 * This function allows the user to get the type of INDEX pulse edge.
 *
 * @param   base    The ENC module base address.
 * @return              The INDEX pulse edge configuration setting
 */
static inline bool ENC_HAL_GetIndexPulseNegativeEdgeCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL_XNE(base);
}

/*!
 * @brief Switches to enable the INDEX to Initialize Position Counters UPOS and LPOS.
 *
 * This function allows the user to enable INDEX pulse to initialize position
 * counters UPOS and LPOS.
 *
 * @param   base    The ENC module base address.  
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetIndexInitPosCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL_XIP(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the INDEX to Initialize Position Counters configuration setting.
 *
 * This function allows the user to get the INDEX to initialize position
 * counters configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of INDEX init position counters.
 */
static inline bool ENC_HAL_GetIndexInitPosCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL_XIP(base);
}

/*!
 * @brief Switches to enable the INDEX Pulse Interrupt.
 *
 * This function allows the user to enable the INDEX pulse interrupt.
 *
 * @param   base    The ENC module base address.
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetIndexPulseIntCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL_XIE(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the INDEX Pulse Interrupt configuration setting.
 *
 * This function allows the user to get the INDEX pulse interrupt
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of INDEX pulse interrupt setting.
 */
static inline bool ENC_HAL_GetIndexPulseIntCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL_XIE(base);
}

/*!
 * @brief Gets the INDEX Pulse Interrupt Request configuration setting.
 *
 * This function returns the configuration setting of the INDEX pulse
 * interrupt request. This bit is set when an INDEX interrupt occurs. It will
 * remain set until cleared by software.
 *
 * @param   base    The ENC module base address.
 * @return              Bit setting of the INDEX pulse interrupt request bit.
 */
static inline bool ENC_HAL_GetIndexPulseIntFlag(ENC_Type* base)
{
    return (bool)ENC_BRD_CTRL_XIRQ(base);
}

/*!
 * @brief Clears the INDEX Pulse Interrupt Request pending.
 *
 * This function clears the INDEX pulse interrupt request bit.
 *
 * @param   base    The ENC module base address.
 */
static inline void ENC_HAL_ClearIndexPulseIntFlag(ENC_Type* base)
{
    ENC_BWR_CTRL_XIRQ(base, 1U);
}

/*!
 * @brief Enables Signal Phase Count Mode.
 *
 * This function allows the user to enable the signal phase count mode which
 * bypasses the quadrature decoder. A positive transition of the PHASEA input
 * generates a count signal. The PHASEB input and the REV (direction control bit)
 * control the counter direction.
 *
 * @param   base    The ENC module base address.
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetSignalPhaseCountModeCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL_PH1(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the Signal Phase Count Mode configuration setting.
 *
 * This function allows the user to get the signal phase counter mode
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of signal phase count mode setting.
 */
static inline bool ENC_HAL_GetSignalPhaseCountModeCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL_PH1(base);
}

/*!
 * @brief Switches to enable the Reverse Direction Counting.
 *
 * This function allows the user to enable the reverse direction counting.
 * It reverses the interpretation of the quadrature signal,
 * changing the direction of count.
 *
 * @param   base    The ENC module base address.
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetReverseCountingCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL_REV(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets Direction Counting configuration setting.
 *
 * This function allows the user to get the counting type
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The count type configuration setting.
 */
static inline bool ENC_HAL_GetReverseCountingCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL_REV(base);
}

/*!
 * @brief Gets the Last Count Direction Flag.
 *
 * This function allows the user to get the flag that indicates the direction
 * of the last count. Returns true if last count was in the up direction or
 * returns false if last count was in the down direction.
 *
 * @param   base    The ENC module base address.
 * @return              The state of count direction.
 */
static inline bool ENC_HAL_GetLastCountDirectionFlag(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL2_DIR(base);
}

/*!
 * @brief Initializes the Position Counter.
 *
 * This function allows the user to initialize position counters UPOS and LPOS.
 * It will transfer the UINIT and LINIT contents to UPOS and LPOS.
 *
 * @param   base    The ENC module base address.
 */
static inline void ENC_HAL_InitPosCounter(ENC_Type* base)
{
    ENC_BWR_CTRL_SWIP(base, 1U);
}

/*!
 * @brief Sets the type of HOME Input Signal Edge.
 *
 * This function allows the user to set the type of HOME input signal edge.
 * Use positive or negative going edge-to-trigger initialization of position
 * counters UPOS and LPOS.
 *
 * @param   base    The ENC module base address.
 * @param   enable      The edge type of HOME input signal.
 */
static inline void ENC_HAL_SetHomeSignalNegativeEdgeCmd
  (ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL_HNE(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets HOME Input Signal Edge configuration setting.
 *
 * This function allows the user to get the HOME input signal edge
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The edge type of HOME input signal.
 */
static inline bool ENC_HAL_GetHomeSignalNegativeEdgeCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL_HNE(base);
}

/*!
 * @brief Switches to enable the Initialize Position Counters UPOS and LPOS.
 *
 * This function allows the user to enable HOME signal to initialize position
 * counters UPOS and LPOS.
 *
 * @param   base    The ENC module base address.  
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetHomeInitPosCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL_HIP(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the HOME to Initialize Position Counters configuration setting.
 *
 * This function allows the user to get the HOME signal input init
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of HOME signal initialization POS counters.
 */
static inline bool ENC_HAL_GetHomeInitPosCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL_HIP(base);
}

/*!
 * @brief Switches to enable the HOME Signal Interrupt.
 *
 * This function allows the user to enable the HOME signal interrupt.
 *
 * @param   base    The ENC module base address 
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetHomeSignalIntCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL_HIE(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the HOME Signal Interrupt configuration setting.
 *
 * This function allows the user to get the HOME signal interrupt
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of HOME signal interrupt setting.
 */
static inline bool ENC_HAL_GetHomeSignalIntCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL_HIE(base);
}

/*!
 * @brief Gets the HOME Signal Interrupt Request configuration setting.
 *
 * This function returns the configuration setting of the HOME signal
 * interrupt request. This bit is set when a transition on the HOME signal
 * occurs. It will remain set until it is cleared by software.
 *
 * @param   base    The ENC module base address.
 * @return              Bit setting of the HOME signal interrupt request bit.
 */
static inline bool ENC_HAL_GetHomeSignalIntFlag(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL_HIRQ(base);
}

/*!
 * @brief Clears the HOME Signal Interrupt Request pending.
 *
 * This function clears the HOME signal interrupt request bit.
 *
 * @param   base    The ENC module base address.
 */
static inline void ENC_HAL_ClearHomeSignalIntFlag(ENC_Type* base)
{
    ENC_BWR_CTRL_HIRQ(base, 1U);
}

/*!
 * @brief Sets the Input Filter Sample Count.
 *
 * This function allows the user to set the input filter sample counts. 
 * The value represents the number of consecutive samples that must agree 
 * prior to the input filter accepting an input transition.
 * A value of 0x0 represents 3 samples. A value of 0x7 represents 10 samples.
 * A value of sampleCount affects the input latency.
 *
 * @param   base    The ENC module base address.
 * @param   sampleCount Value that represents the number of consecutive samples.
 */
static inline void ENC_HAL_SetInputFilterSampleCount
  (ENC_Type* base, uint8_t sampleCount)
{
    assert(sampleCount < 0x08);
    ENC_BWR_FILT_FILT_CNT(base, sampleCount);
}

/*!
 * @brief Gets the Input Filter Sample Count.
 *
 * This function allows the user to read the input filter sample counts.
 * The value represents the number of consecutive samples that must agree
 * prior to the input filter accepting an input transition.
 *
 * @param   base    The ENC module base address.
 * @return              Value that represents the number of consecutive samples.
 */
static inline uint8_t ENC_HAL_GetInputFilterSampleCount(ENC_Type* base)
{
    return (uint8_t)ENC_BRD_FILT_FILT_CNT(base);
}

/*!
 * @brief Sets the Input Filter Sample Period.
 *
 * This function allows the user to set the input filter sample period.
 * This value represents the sampling period of the decoder input signals. Each
 * input is sampled multiple times at the rate specified by this field.
 * If samplePeriod is 0x00 (default), then the input filter is bypassed. Bypassing
 * the digital filter enables the position/position difference counters to operate
 * with count rates up to the IPBus frequency. The value of samplePeriod affects
 * the input latency.
 *
 * @param   base            The ENC module base address.
 * @param   samplePeriod        Value of filter sample period.
 */
void ENC_HAL_SetInputFilterSamplePeriod(ENC_Type* base, uint8_t samplePeriod);

/*!
 * @brief Gets the Input Filter Sample Period.
 *
 * This function allows the user to read the input filter sample period.
 * This value represents the sampling period of the decoder input signals.
 *
 * @param   base    The ENC module base address.
 * @return              Value of filter sample period.
 */
static inline uint8_t ENC_HAL_GetInputFilterSamplePeriod(ENC_Type* base)
{
    return (uint8_t) ENC_BRD_FILT_FILT_PER(base);
}

/*!
 * @brief Sets the Watchdog timeout register.
 *
 * This function allows the user to set the timeout value for Watchdog timer,
 * which is separated from the watchdog timer in the COP module.
 * Timeout value is the number of clock cycles plus one that the watchdog timer
 * counts before timing out and optionally generating an interrupt.
 *
 * @param   base    The ENC module base address.
 * @param   wdtTimeout  Value of watchdog timeout.
 */
static inline void ENC_HAL_SetWatchdogTimeout(ENC_Type* base, uint16_t wdtTimeout)
{
    ENC_WR_WTR(base, wdtTimeout);
}

/*!
 * @brief Gets the Watchdog timeout register.
 *
 * This function allows the user to read the timeout value for Watchdog timer,
 * which is separated from the watchdog timer in the COP module.
 * Timeout value is the number of clock cycles plus one that the watchdog timer
 * counts before timing out and optionally generating an interrupt.
 *
 * @param   base    The ENC module base address.
 * @return              Value of watchdog timeout.
 */
static inline uint16_t ENC_HAL_GetWatchdogTimeout(ENC_Type* base)
{
    return (uint16_t) ENC_RD_WTR(base);
}

/*!
 * @brief Sets the Position Difference Counter Register.
 *
 * This function allows the user to write the POSD register. It contains the
 * position change in value occuring between each read of the position register.
 * The value of the position difference counter register can be used 
 * to calculate velocity.
 *
 * @param   base    The ENC module base address.
 * @param   diffPosition Value of position difference.
 */
static inline void ENC_HAL_SetPosDiffCounterReg
  (ENC_Type* base, uint16_t diffPosition)
{
    ENC_WR_POSD(base, diffPosition);
}

/*!
 * @brief Gets the Position Difference Counter Register.
 *
 * This function allows the user to read the POSD register. It contains the
 * position change in value occurring between each read of the position register.
 * The value of the position difference counter register can be used 
 * to calculate velocity.
 * The 16-bit position difference counter computes up or down on every count pulse.
 * This counter acts as a differentiator whose count value is proportional
 * to the change in position since the last time the position counter was read.
 * When the position register, the position difference counter, or the revolution
 * counter is read, the position difference counter's contents are copied into
 * the position difference hold register (POSDH) and the position difference
 * counter is cleared.
 *
 * @param   base    The ENC module base address.
 * @return              Value of position difference hold register.
 */
static inline uint16_t ENC_HAL_GetPosDiffCounterReg
  (ENC_Type* base)
{
    return (uint16_t) ENC_RD_POSD(base);
}

/*!
 * @brief Gets the Position Difference Hold Register.
 *
 * This function allows the user to read the POSD Hold register. Hold register
 * contains a snapshot of the value of the position difference register.
 * The value of the position difference hold register can be used to calculate
 * velocity.
 *
 * @param   base    The ENC module base address.
 * @return              Value of position difference hold register.
 */
static inline uint16_t ENC_HAL_GetPosDiffHoldReg(ENC_Type* base)
{
    return (uint16_t) ENC_RD_POSDH(base);
}

/*!
 * @brief Sets the Revolution Counter Register.
 *
 * This function allows the user to write the Revolution counter.
 *
 * @param   base    The ENC module base address.
 * @param   revValue   Value of revolution.
 */
static inline void ENC_HAL_SetRevolutionCounterReg
  (ENC_Type* base, uint16_t revValue)
{
    ENC_WR_REV(base, revValue);
}

/*!
 * @brief Gets the Revolution Counter Register.
 *
 * This function allows the user to read the Revolution counter.
 *
 * @param   base    The ENC module base address.
 * @return              Value of revolution counter.
 */
static inline uint16_t ENC_HAL_GetRevolutionCounterReg(ENC_Type* base)
{
    return (uint16_t) ENC_RD_REV(base);
}

/*!
 * @brief Gets the Revolution Hold Register.
 *
 * This function allows the user to read the Revolution Hold register. Contains
 * a snapshot of the value of the revolution counter register.
 *
 * @param   base    The ENC module base address.
 * @return              Value of revolution hold register.
 */
static inline uint16_t ENC_HAL_GetRevolutionHoldReg(ENC_Type* base)
{
    return (uint16_t) ENC_RD_REVH(base);
}

/*!
 * @brief Gets the Position Counter Register.
 *
 * This function allows the user to read the Position counter.
 *
 * @param   base    The ENC module base address.
 * @return              Value of position counter.
 */
uint32_t ENC_HAL_GetPosCounterReg(ENC_Type* base);

/*!
 * @brief Sets the Position Counter Register.
 *
 * This function allows the user to write the Position counter.
 *
 * @param   base    The ENC module base address.
 * @param   posVal      Value of position counter.
 */
void ENC_HAL_SetPosCounterReg(ENC_Type* base, uint32_t posVal);

/*!
 * @brief Gets the Position Hold Register.
 *
 * This function allows the user to read the Position hold register. Contains
 * a snapshot of the position counter register.
 *
 * @param   base    The ENC module base address.
 * @return              Value of position hold register.
 */
uint32_t ENC_HAL_GetPosHoldReg(ENC_Type* base);

/*!
 * @brief Sets the Initialization Register.
 *
 * This function allows the user to write the initialization register.
 *
 * @param   base    The ENC module base address.
 * @param   initValue   Value of initialization register.
 */
void ENC_HAL_SetInitReg(ENC_Type* base, uint32_t initValue);

/*!
 * @brief Gets the Initialization Register.
 *
 * This function allows the user to read the initialization register.
 *
 * @param   base    The ENC module base address.
 * @return              Value of initialization register.
 */
uint32_t ENC_HAL_GetInitReg(ENC_Type* base);

/*!
 * @brief Gets the Raw HOME Input.
 *
 * This function allows the user to read the value of the raw HOME input.
 *
 * @param   base    The ENC module base address.
 * @return              Value of the raw HOME input.
 */
static inline bool ENC_HAL_GetRawHomeInput(ENC_Type* base)
{
    return (bool) ENC_BRD_IMR_HOME(base);
}

/*!
 * @brief Gets the Raw INDEX Input.
 *
 * This function allows the user to read the value of the raw INDEX input.
 *
 * @param   base    The ENC module base address.
 * @return              Value of the raw INDEX input.
 */
static inline bool ENC_HAL_GetRawIndexInput(ENC_Type* base)
{
    return (bool) ENC_BRD_IMR_INDEX(base);
}

/*!
 * @brief Gets the Raw PHASEB Input.
 *
 * This function allows the user to read the value of the raw PHASEB input.
 *
 * @param   base    The ENC module base address.
 * @return              Value of the raw PHASEB input.
 */
static inline bool ENC_HAL_GetRawPhaseBInput(ENC_Type* base)
{
    return (bool) ENC_BRD_IMR_PHB(base);
}

/*!
 * @brief Gets the Raw PHASEA Input.
 *
 * This function allows the user to read the value of the raw PHASEA input.
 *
 * @param   base    The ENC module base address.
 * @return              Value of the raw PHASEA input.
 */
static inline bool ENC_HAL_GetRawPhaseAInput(ENC_Type* base)
{
    return (bool) ENC_BRD_IMR_PHA(base);
}

/*!
 * @brief Gets the Filtered HOME Input.
 *
 * This function allows the user to read the value of the filtered HOME input.
 *
 * @param   base    The ENC module base address.
 * @return              Value of the filtered HOME input.
 */
static inline bool ENC_HAL_GetFilteredHomeInput(ENC_Type* base)
{
    return (bool) ENC_BRD_IMR_FHOM(base);
}

/*!
 * @brief Gets the Filtered INDEX Input.
 *
 * This function allows the user to read the value of the filtered INDEX input.
 *
 * @param   base    The ENC module base address.
 * @return              Value of the filtered INDEX input.
 */
static inline bool ENC_HAL_GetFilteredIndexInput(ENC_Type* base)
{
    return (bool) ENC_BRD_IMR_FIND(base);
}

/*!
 * @brief Gets the Filtered PHASEB Input.
 *
 * This function allows the user to read the value of the filtered PHASEB input.
 *
 * @param   base    The ENC module base address.
 * @return              Value of the filtered PHASEB input.
 */
static inline bool ENC_HAL_GetFilteredPhaseBInput(ENC_Type* base)
{
    return (bool) ENC_BRD_IMR_FPHB(base);
}

/*!
 * @brief Gets the Filtered PHASEA Input.
 *
 * This function allows the user to read the value of the filtered PHASEA input.
 *
 * @param   base    The ENC module base address.
 * @return              Value of the filtered PHASEA input.
 */
static inline bool ENC_HAL_GetFilteredPhaseAInput(ENC_Type* base)
{
    return (bool) ENC_BRD_IMR_FPHA(base);
}

/*!
 * @brief Gets the ENC Test Count.
 *
 * This function allows the user to read the test count value 
 * of the test register.
 * This value holds the number of quadrature advances to generate.
 *
 * @param   base    The ENC module base address.
 * @return              Value of test count.
 */
static inline uint8_t ENC_HAL_GetTestCount(ENC_Type* base)
{
    return (uint8_t) ENC_BRD_TST_TEST_COUNT(base);
}

/*!
 * @brief Sets the ENC Test Count.
 *
 * This function allows the user to write the test count value 
 * of the test register.
 * This value holds the number of quadrature advances to generate.
 *
 * @param   base    The ENC module base address.
 * @param   testCount  Value of test count.
 */
static inline void ENC_HAL_SetTestCount(ENC_Type* base, uint8_t testCount)
{
    ENC_BWR_TST_TEST_COUNT(base, testCount);
}

/*!
 * @brief Gets the ENC Test Period.
 *
 * This function allows the user to read the test period value 
 * of the test register.
 * This value holds the period of quadrature phase in IPBus clock cycles.
 *
 * @param   base    The ENC module base address.
 * @return              Value of test period.
 */
static inline uint8_t ENC_HAL_GetTestPeriod(ENC_Type* base)
{
    return (uint8_t) (ENC_BRD_TST_TEST_PERIOD(base) & 0x1F);
}

/*!
 * @brief Sets the ENC Test Period.
 *
 * This function allows the user to write the test period value 
 * of the test register.
 * This value holds the period of quadrature phase in IPBus clock cycles.
 *
 * @param   base    The ENC module base address.
 * @param   testPeriod  Value of test period.
 */
static inline void ENC_HAL_SetTestPeriod(ENC_Type* base, uint8_t testPeriod)
{
    assert(testPeriod < 0x20);
    ENC_BWR_TST_TEST_PERIOD(base, testPeriod);
}

/*!
 * @brief Sets the Quadrature Decoder Test Signal.
 *
 * This function allows the user to set the quadrature decoder test signal.
 * Test module can generates quadrature decoder signal in a positive 
 * or negative direction.
 *
 * @param   base    The ENC module base address.
 * @param   enable      The type of test signal.
 */
static inline void ENC_HAL_SetNegativeTestSignalCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_TST_QDN(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the Quadrature Decoder Test Signal configuration setting.
 *
 * This function allows the user to get the test signal configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The type of test signal.
 */
static inline bool ENC_HAL_GetNegativeTestSignalCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_TST_QDN(base);
}

/*!
 * @brief Switches to enable the Test Counter.
 *
 * This function allows the user to enable test counter. It connects the test
 * counter to inputs of the quadrature decoder module.
 *
 * @param   base    The ENC module base address. 
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetTestCounterCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_TST_TCE(base, (enable ? 1U : 0U));
}

/*!
 * @brief Tests the Test Counter Enable bit.
 *
 * This function returns the configuration setting of the test 
 * counter enable bit.
 *
 * @param   base    The ENC module base address.
 * @return              Bit setting of the test counter enable. 
 */
static inline bool ENC_HAL_GetTestCounterCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_TST_TCE(base);
}

/*!
 * @brief Switches to enable the Test Module.
 *
 * This function allows the user to enable test module.
 * Connects the test module to inputs of the quadrature decoder module.
 *
 * @param   base    The ENC module base address.
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetTestModuleCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_TST_TEN(base, (enable ? 1U : 0U));
}

/*!
 * @brief Tests the Test Module Enable bit.
 *
 * This function returns the configuration setting of the test 
 * module enable bit.
 *
 * @param   base    The ENC module base address.
 * @return              Bit setting of the test module enable. 
 */
static inline bool ENC_HAL_GetTestModuleCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_TST_TEN(base);
}

/*!
 * @brief Sets the ENC Modulus Register.
 *
 * This function allows the user to write the ENC modulus register. Modulus
 * acts as the upper bound during modulo counting and as the upper reload value
 * when rolling over from the lower bound.
 *
 * @param   base    The ENC module base address.
 * @param   modValue    Value of modulo register.
 */
void ENC_HAL_SetModulusReg(ENC_Type* base, uint32_t modValue);

/*!
 * @brief Gets the ENC Modulus Register.
 *
 * This function allows the user to read the ENC modulus register. Modulus
 * acts as the upper bound during modulo counting and as the upper reload value
 * when rolling over from the lower bound.
 *
 * @param   base    The ENC module base address.
 * @return              Value of modulo register.
 */
uint32_t ENC_HAL_GetModulusReg(ENC_Type* base);

/*!
 * @brief Sets the ENC Compare Register.
 *
 * This function allows the user to write the ENC compare register. When the
 * value of Position counter matches the value of Compare register 
 * the CTRL[CMPIRQ] flag is set and the POSMATCH output is asserted.
 *
 * @param   base    The ENC module base address.
 * @param   cmpValue    Value of modulo register.
 */
void ENC_HAL_SetCmpReg(ENC_Type* base, uint32_t cmpValue);

/*!
 * @brief Gets the ENC Compare Register.
 *
 * This function allows the user to read the ENC compare register. When the
 * value of Position counter matches the value of Compare register 
 * the CTRL[CMPIRQ] flag is set and the POSMATCH output is asserted.
 *
 * @param   base    The ENC module base address.
 * @return              Value of modulo register.
 */
uint32_t ENC_HAL_GetCmpReg(ENC_Type* base);

/*!
 * @brief Switches to enable the Update Hold Registers.
 *
 * This function allows the user to enable the update hold registers 
 * on external trigger input. Updating POSDH register will also cause
 * the POSD register to be cleared.
 *
 * @param   base    The ENC module base address.
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetTriggerUpdateHoldRegCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL2_UPDHLD(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the Update Hold Registers configuration setting.
 *
 * This function allows the user to get the update hold registers
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of update hold registers
 */
static inline bool ENC_HAL_GetTriggerUpdateHoldRegCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL2_UPDHLD(base);
}

/*!
 * @brief Enables Update Position Registers.
 *
 * This function allows the user to enable the update of position registers 
 * on external trigger input. Allows the TRIGGER input to clear POSD, REV,
 * UPOS and LPOS registers on rising edge.
 *
 * @param   base    The ENC module base address.
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetTriggerClearPosRegCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL2_UPDPOS(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the Update Position Registers configuration setting.
 *
 * This function allows the user to get the update of position registers
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of update position registers
 */
static inline bool ENC_HAL_GetTriggerClearPosRegCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL2_UPDPOS(base);
}

/*!
 * @brief Switches to enable the Modulo Counting.
 *
 * This function allows the user to enable the modulo counting. It allows
 * the position counters to count in a modulo fashion using MOD and INIT
 * as the upper and lower bounds of the counting range.
 *
 * @param   base    The ENC module base address.
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetModuloCountingCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL2_MOD(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the Modulo Counting configuration setting.
 *
 * This function allows the user to get the modulo counting
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of modulo counting.
 */
static inline bool ENC_HAL_GetModuloCountingCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL2_MOD(base);
}

/*!
 * @brief Switches to enable the Roll-under Interrupt.
 *
 * This function allows the user to enable the roll-under interrupt.
 *
 * @param   base    The ENC module base address.
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetRollunderIntCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL2_RUIE(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the Roll-under Interrupt configuration setting.
 *
 * This function allows the user to get the roll-under interrupt
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of roll-under interrupt setting.
 */
static inline bool ENC_HAL_GetRollunderIntCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL2_RUIE(base);
}

/*!
 * @brief Gets the Roll-under Interrupt Request configuration setting.
 *
 * This function returns the configuration setting of the Roll-under
 * interrupt request. It is set when the position counter rolls under from
 * the INIT value to the MOD value or from 0x00000000 to 0xFFFFFFFF. It will
 * remain set until cleared by software.
 *
 * @param   base    The ENC module base address.
 * @return              Bit setting of the interrupt request bit.
 */
static inline bool ENC_HAL_GetRollunderIntFlag(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL2_RUIRQ(base);
}

/*!
 * @brief Clears the Roll-under Interrupt Request pending.
 *
 * This function clears the roll-under interrupt request bit.
 *
 * @param   base    The ENC module base address.
 */
static inline void ENC_HAL_ClearRollunderIntFlag(ENC_Type* base)
{
    ENC_BWR_CTRL2_RUIRQ(base, 1U);
}

/*!
 * @brief Switches to enable the Roll-over Interrupt.
 *
 * This function allows the user to enable the roll-over interrupt.
 *
 * @param   base    The ENC module base address.
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetRolloverIntCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL2_ROIE(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the Roll-over Interrupt configuration setting.
 *
 * This function allows the user to get the roll-over interrupt
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of roll-over interrupt setting.
 */
static inline bool ENC_HAL_GetRolloverIntCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL2_ROIE(base);
}

/*!
 * @brief Gets the Roll-over Interrupt Request configuration setting.
 *
 * This function returns the configuration setting of the Roll-over
 * interrupt request. It is set when the position counter rolls over the MOD
 * value to the INIT value or from 0xFFFFFFFF to 0x00000000. It will remain
 * set until cleared by software.
 *
 * @param   base    The ENC module base address.
 * @return              Bit setting of the interrupt request bit.
 */
static inline bool ENC_HAL_GetRolloverIntFlag(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL2_ROIRQ(base);
}

/*!
 * @brief Clears the Roll-over Interrupt Request pending.
 *
 * This function clears the roll-over interrupt request bit.
 *
 * @param   base    The ENC module base address.
 */
static inline void ENC_HAL_ClearRolloverIntFlag(ENC_Type* base)
{
    ENC_BWR_CTRL2_ROIRQ(base, 1U);
}

/*!
 * @brief Switches to enable the Modulus Revolution Counter.
 *
 * This function allows the user to enable the modulo revolution counter.
 * This is used to determine how the revolution counter (REV) is incremented
 * or decremented. By default REV is controlled based on the count direction
 * and the INDEX pulse. As an option, REV can be controlled using
 * the roll-over/under detection during modulo counting.
 *
 * @param   base    The ENC module base address.
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetModulusRevCounterCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL2_REVMOD(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the Modulus Revolution Counter configuration setting.
 *
 * This function allows the user to get the modulus revolution counter
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of modulus revolution counter.
 */
static inline bool ENC_HAL_GetModulusRevCounterCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL2_REVMOD(base);
}

/*!
 * @brief Switches to enable the POSMATCH to pulse on Counters registers reading.
 * 
 * This function allows the user to config control of the POSMATCH output. 
 * POSMATCH pulses when the UPOS, LPOS, REV or POSD registers are read - when set true
 * or when match occurred between position register and Compare value register (false).
 *
 * @param   base    The ENC module base address.
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetPosmatchOnReadingCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL2_OUTCTL(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the POSMATCH Output configuration setting.
 *
 * This function allows the user to get the POSMATCH output
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of POSMATCH output setting.
 */
static inline bool ENC_HAL_GetPosmatchOnReadingCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL2_OUTCTL(base);
}

/*!
 * @brief Switches to enable the Simultaneous PHASEA and PHASEB Change Interrupt.
 *
 * This function allows the user to enable the SAB interrupt.
 *
 * @param   base    The ENC module base address.
 * @param   enable      Bool parameter to enable/disable.
 */
static inline void ENC_HAL_SetSimultaneousIntCmd(ENC_Type* base, bool enable)
{
    ENC_BWR_CTRL2_SABIE(base, (enable ? 1U : 0U));
}

/*!
 * @brief Gets the SAB Interrupt configuration setting.
 *
 * This function allows the user to get the SAB interrupt
 * configuration setting.
 *
 * @param   base    The ENC module base address.
 * @return              The state of SAB interrupt setting.
 */
static inline bool ENC_HAL_GetSimultaneousIntCmd(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL2_SABIE(base);
}

/*!
 * @brief Gets the SAB Interrupt Request configuration setting.
 *
 * This function returns the configuration setting of the SAB
 * interrupt request. It indicates that the PHASEA and PHASEB inputs changed
 * simultaneously (within a single clock period). This event typically indicates
 * an error condition because quadrature coding requires only one of these inputs
 * to change at a time. The bit remains set until it is cleared by software or a reset.
 *
 * @param   base    The ENC module base address.
 * @return              Bit setting of the interrupt request bit.
 */
static inline bool ENC_HAL_GetSimultaneousIntFlag(ENC_Type* base)
{
    return (bool) ENC_BRD_CTRL2_SABIRQ(base);
}

/*!
 * @brief Clears the SAB Interrupt Request pending.
 *
 * This function clears the SAB interrupt request bit.
 *
 * @param   base    The ENC module base address.
 */
static inline void ENC_HAL_ClearSimultaneousIntFlag(ENC_Type* base)
{
    ENC_BWR_CTRL2_SABIRQ(base, 1U);
}

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_ENC_HAL_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/
