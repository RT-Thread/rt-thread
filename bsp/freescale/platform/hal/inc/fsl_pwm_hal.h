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

#ifndef __FSL_PWM_HAL_H__
#define __FSL_PWM_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

#if FSL_FEATURE_SOC_PWM_COUNT

/*!
 * @addtogroup pwm_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief PWM submodules */
typedef enum _pwm_module
{
    kFlexPwmModule0 = 0U,                /*!< Sub-module 0. @internal gui name="PWM Sub-module 0" */
    kFlexPwmModule1,                     /*!< Sub-module 1. @internal gui name="PWM Sub-module 1" */
    kFlexPwmModule2,                     /*!< Sub-module 2. @internal gui name="PWM Sub-module 2" */
    kFlexPwmModule3                      /*!< Sub-module 3. @internal gui name="PWM Sub-module 3" */
} pwm_module_t;

/*! @brief PWM signals from each module */
typedef enum _pwm_module_signal
{
    kFlexPwmB = 0U,
    kFlexPwmA,
    kFlexPwmX
} pwm_module_signal_t;

/*! @brief PWM value registers */
typedef enum _pwm_val_regs
{
    kFlexPwmVAL0 = 0U,   /*!< PWM VAL0 reg. @internal gui name="PWM value register 0" */
    kFlexPwmVAL1,        /*!< PWM VAL1 reg. @internal gui name="PWM value register 1" */
    kFlexPwmVAL2,        /*!< PWM VAL2 reg. @internal gui name="PWM value register 2" */
    kFlexPwmVAL3,        /*!< PWM VAL3 reg. @internal gui name="PWM value register 3" */
    kFlexPwmVAL4,        /*!< PWM VAL4 reg. @internal gui name="PWM value register 4" */
    kFlexPwmVAL5         /*!< PWM VAL5 reg. @internal gui name="PWM value register 5" */
} pwm_val_regs_t;

/*! @brief PWM status */
typedef enum _pwm_status {
    kStatusPwmSuccess = 0U,                   /*!< PWM success status.*/
    kStatusPwmError = 1U,                     /*!< PWM error status.*/
    kStatusPwmInvalidArgument = 2U            /*!< PWM invalid argument.*/
} pwm_status_t;

/*! @brief PWM clock source selection.*/
typedef enum _pwm_clock_src
{
    kClkSrcPwmIPBusClk = 0U,  /*!< The IPBus clock is used as the clock. @internal gui name="IPBus clock" */
    kClkSrcPwmExtClk,         /*!< EXT_CLK is used as the clock. @internal gui name="External clock (EXT_CLK)" */
    kClkSrcPwm0Clk            /*!< Clock of the submodule 0 (AUX_CLK) is used as the source clock. @internal gui name="Clock of Submodule 0 clock (AUX_CLK)" */
} pwm_clock_src_t;

/*! @brief PWM prescaler factor selection for clock source*/
typedef enum _pwm_clock_ps
{
    kPwmDividedBy1 = 0U,                       /*!< PWM clock frequency = fclk/1. @internal gui name="PWM clock divided by 1" */
    kPwmDividedBy2,                            /*!< PWM clock frequency = fclk/2. @internal gui name="PWM clock divided by 2" */
    kPwmDividedBy4,                            /*!< PWM clock frequency = fclk/4. @internal gui name="PWM clock divided by 4" */
    kPwmDividedBy8,                            /*!< PWM clock frequency = fclk/8. @internal gui name="PWM clock divided by 8" */
    kPwmDividedBy16,                           /*!< PWM clock frequency = fclk/16. @internal gui name="PWM clock divided by 16" */
    kPwmDividedBy32,                           /*!< PWM clock frequency = fclk/32. @internal gui name="PWM clock divided by 32" */
    kPwmDividedBy64,                           /*!< PWM clock frequency = fclk/64. @internal gui name="PWM clock divided by 64" */
    kPwmDividedBy128                           /*!< PWM clock frequency = fclk/128. @internal gui name="PWM clock divided by 128" */
} pwm_clock_ps_t;

/*! @brief Options that can trigger a PWM FORCE_OUT */
typedef enum _pwm_force_output_trigger
{
    kForceOutputLocalForce = 0U,  /*!< The local force signal, CTRL2[FORCE], from this submodule is used to force updates. @internal gui name="The local force signal, CTRL2[FORCE], from this submodule is used to force updates" */
    kForceOutputMasterForce,      /*!< The master force signal from submodule 0 is used to force updates. @internal gui name="The master force signal from submodule 0 is used to force updates" */
    kForceOutputLocalReload,      /*!< The local reload signal from this submodule is used to force updates without regard to the state of LDOK. @internal gui name="The local reload signal from this submodule is used to force updates without regard to the state of LDOK" */
    kForceOutputMasterReload,     /*!< The master reload signal from submodule 0 is used to force updates if LDOK is set. @internal gui name="The master reload signal from submodule 0 is used to force updates if LDOK is set" */
    kForceOutputLocalSync,        /*!< The local sync signal from this submodule is used to force updates. @internal gui name="The local sync signal from this submodule is used to force updates" */
    kForceOutputMasterSync,       /*!< The master sync signal from submodule0 is used to force updates. @internal gui name="The master sync signal from submodule0 is used to force updates" */
    kForceOutputExternalForce,    /*!< The external force signal, EXT_FORCE, from outside the PWM module causes updates. @internal gui name="The external force signal, EXT_FORCE, from outside the PWM module causes updates" */
    kForceOutputExternalSync      /*!< The external sync signal, EXT_SYNC, from outside the PWM module causes updates. @internal gui name="The external sync signal, EXT_SYNC, from outside the PWM module causes updates" */
} pwm_force_output_trigger_t;

/*! @brief PWM counter initialization options */
typedef enum _pwm_init_src
{
    kInitSrcLocalSync = 0U,                   /*!< Local sync (PWM_X) causes initialization. @internal gui name="Local sync (PWM_X) causes initialization"*/
    kInitSrcMasterReload,                     /*!< Master reload from submodule 0 causes initialization. @internal gui name="Master reload from submodule 0 causes initialization" */
    kInitSrcMasterSync,                       /*!< Master sync from submodule 0 causes initialization. @internal gui name="Master sync from submodule 0 causes initialization" */
    kInitSrcExtSync                           /*!< EXT_SYNC causes initialization. @internal gui name="EXT_SYNC causes initialization" */
} pwm_init_src_t;

/*! @brief PWM load frequency selection */
typedef enum _pwm_load_frequency
{
    kPwmLoadEvery1Oportunity = 0U,             /*!< Every 1 PWM opportunity. @internal gui name="Every 1 PWM opportunity" */
    kPwmLoadEvery2Oportunity,                  /*!< Every 2 PWM opportunities. @internal gui name="Every 2 PWM opportunities" */
    kPwmLoadEvery3Oportunity,                  /*!< Every 3 PWM opportunities. @internal gui name="Every 3 PWM opportunities" */
    kPwmLoadEvery4Oportunity,                  /*!< Every 4 PWM opportunities. @internal gui name="Every 4 PWM opportunities" */
    kPwmLoadEvery5Oportunity,                  /*!< Every 5 PWM opportunities. @internal gui name="Every 5 PWM opportunities" */
    kPwmLoadEvery6Oportunity,                  /*!< Every 6 PWM opportunities. @internal gui name="Every 6 PWM opportunities" */
    kPwmLoadEvery7Oportunity,                  /*!< Every 7 PWM opportunities. @internal gui name="Every 7 PWM opportunities" */
    kPwmLoadEvery8Oportunity,                  /*!< Every 8 PWM opportunities. @internal gui name="Every 8 PWM opportunities" */
    kPwmLoadEvery9Oportunity,                  /*!< Every 9 PWM opportunities. @internal gui name="Every 9 PWM opportunities" */
    kPwmLoadEvery10Oportunity,                 /*!< Every 10 PWM opportunities. @internal gui name="Every 10 PWM opportunities" */
    kPwmLoadEvery11Oportunity,                 /*!< Every 11 PWM opportunities. @internal gui name="Every 11 PWM opportunities" */
    kPwmLoadEvery12Oportunity,                 /*!< Every 12 PWM opportunities. @internal gui name="Every 12 PWM opportunities" */
    kPwmLoadEvery13Oportunity,                 /*!< Every 13 PWM opportunities. @internal gui name="Every 13 PWM opportunities" */
    kPwmLoadEvery14Oportunity,                 /*!< Every 14 PWM opportunities. @internal gui name="Every 14 PWM opportunities" */
    kPwmLoadEvery15Oportunity,                 /*!< Every 15 PWM opportunities. @internal gui name="Every 15 PWM opportunities" */
    kPwmLoadEvery16Oportunity                  /*!< Every 16 PWM opportunities. @internal gui name="Every 16 PWM opportunities" */
} pwm_load_frequency_t;

/*! @brief PWM fault select */
typedef enum _pwm_fault_input
{
    kFlexPwmFault0 = 0U,                /*!< Fault 0 input pin. @internal gui name="Fault pin 0" */
    kFlexPwmFault1,                     /*!< Fault 1 input pin. @internal gui name="Fault pin 1" */
    kFlexPwmFault2,                     /*!< Fault 2 input pin. @internal gui name="Fault pin 2" */
    kFlexPwmFault3                      /*!< Fault 3 input pin. @internal gui name="Fault pin 3" */
} pwm_fault_input_t;

/*! @brief PWM capture edge select */
typedef enum _pwm_capture_edge
{
    kCaptureDisable = 0U,                    /*!< Disabled */
    kCaptureFallingEdges,                    /*!< Capture falling edges */
    kCaptureRisingEdges,                     /*!< Capture rising edges */
    kCaptureAnyEdges                         /*!< Capture any edge */
} pwm_capture_edge_t;

/*! @brief PWM output options when a FORCE_OUT signal is asserted */
typedef enum _pwm_force_signal
{
    kFlexPwmUsePwm = 0U,        /*!< Generated PWM signal is used by the deadtime logic.*/
    kFlexPwmInvertedPwm,        /*!< Inverted PWM signal is used by the deadtime logic.*/
    kFlexPwmSoftwareControl,    /*!< Software controlled value is used by the deadtime logic. */
    kFlexPwmUseExternal         /*!< PWM_EXTA signal is used by the deadtime logic. */
} pwm_force_signal_t;

/*! @brief Optiona available for the PWM A & B pair operation */
typedef enum _pwm_chnl_pair_operation
{
    kFlexPwmIndependent = 0U,   /*!< PWM A & PWM B operation as 2 independent channels. @internal gui name="Independent" */
    kFlexPwmComplementaryPwmA,  /*!< PWM A & PWM B are complementary channels, PWM A generates the signal. @internal gui name="Complementary, PWM A generates the signal" */
    kFlexPwmComplementaryPwmB   /*!< PWM A & PWM B are complementary channels, PWM B generates the signal. @internal gui name="Complementary, PWM B generates the signal" */
} pwm_chnl_pair_operation_t;

/*! @brief Options available on how to load the buffered-registers with new values */
typedef enum _pwm_reg_reload
{
    kFlexPwmReloadImmediate = 0U,     /*!< Buffered-registers get loaded with new values as soon as LDOK bit is set. @internal gui name="Reload immediately upon MCTRL[LDOK] being set" */
    kFlexPwmReloadPwmHalfCycle,       /*!< Registers loaded on a PWM half cycle. @internal gui name="Reload on a PWM half cycle" */
    kFlexPwmReloadPwmFullCycle,       /*!< Registers loaded on a PWM full cycle. @internal gui name="Reload on a PWM full cycle" */
    kFlexPwmReloadPwmHalfAndFullCycle /*!< Registers loaded on a PWM half & full cycle. @internal gui name="Reload on both half and full PWM cycle" */
} pwm_reg_reload_t;

/*! @brief Options available on how to re-enable the PWM output when recovering from a fault */
typedef enum _pwm_fault_recovery_mode
{
    kFlexPwmNoRecovery = 0U,        /*!< PWM output will stay inactive. @internal gui name="No Recovery" */
    kFlexPwmRecoverHalfCycle,       /*!< PWM output re-enabled at the first half cycle. @internal gui name="Half cycle recovery" */
    kFlexPwmRecoverFullCycle,       /*!< PWM output re-enabled at the first full cycle. @internal gui name="Full cycle recovery" */
    kFlexPwmRecoverHalfAndFullCycle /*!< PWM output re-enabled at the first half or full cycle. @internal gui name="Half and Full cycle recovery" */
} pwm_fault_recovery_mode_t;

/*! @brief PWM interrupt options available */
typedef enum _pwm_event
{
    kFlexPwmCompareVal0Event = (1U << 0),  /*!< PWM VAL0 compare event */
    kFlexPwmCompareVal1Event = (1U << 1),  /*!< PWM VAL1 compare event */
    kFlexPwmCompareVal2Event = (1U << 2),  /*!< PWM VAL2 compare event */
    kFlexPwmCompareVal3Event = (1U << 3),  /*!< PWM VAL3 compare event */
    kFlexPwmCompareVal4Event = (1U << 4),  /*!< PWM VAL4 compare event */
    kFlexPwmCompareVal5Event = (1U << 5),  /*!< PWM VAL5 compare event */
    kFlexPwmCaptureX0Event = (1U << 6),    /*!< PWM capture X0 event */
    kFlexPwmCaptureX1Event = (1U << 7),    /*!< PWM capture X1 event */
    kFlexPwmCaptureB0Event = (1U << 8),    /*!< PWM capture B0 event */
    kFlexPwmCaptureB1Event = (1U << 9),    /*!< PWM capture B1 event */
    kFlexPwmCaptureA0Event = (1U << 10),   /*!< PWM capture A0 event */
    kFlexPwmCaptureA1Event = (1U << 11),   /*!< PWM capture A1 event */
    kFlexPwmReloadEvent = (1U << 12),      /*!< PWM reload event */
    kFlexPwmReloadErrorEvent = (1U << 13), /*!< PWM reload error event */
    kFlexPwmFault0Event = (1U << 16),      /*!< PWM fault 0 event */
    kFlexPwmFault1Event = (1U << 17),      /*!< PWM fault 1 event */
    kFlexPwmFault2Event = (1U << 18),      /*!< PWM fault 2 event */
    kFlexPwmFault3Event = (1U << 19)       /*!< PWM fault 3 event */
} pwm_event_t;

/*!
 * @brief Structure is used to hold the parameters to configure a PWM module
 *
 * @internal gui name="PWM Sub-module configuration" id="pwmModuleCfg"
 */
typedef struct PwmModuleSetup
{
    pwm_init_src_t cntrInitSel;      /*!< Option to initialize the counter. @internal gui name="PWM counter initialization" id="pwm_cntrInitSel" */
    pwm_clock_src_t clkSrc;          /*!< Clock source for the counter. @internal gui name="PWM clock source" id="pwm_clkSrc" */
    pwm_clock_ps_t prescale;         /*!< Pre-scaler to divide down the clock. @internal gui name="PWM clock prescaler" id="pwm_prescale" */
    pwm_chnl_pair_operation_t chnlPairOper; /*!< Channel pair in indepedent or complementary mode. @internal gui name="PWM channel mode" id="pwm_chnlPairOper" */
    pwm_reg_reload_t reloadLogic;    /*!< PWM Reload logic setup. @internal gui name="PWM reload logic" id="pwm_reloadLogic" */
    pwm_load_frequency_t reloadFreq; /*!< Specifies when to reload, used when user's choice is not immediate reload. @internal gui name="PWM reload frequency" id="pwm_reloadFreq" */
    pwm_force_output_trigger_t forceTrig; /*!< Specify which signal will trigger a FORCE_OUT. @internal gui name="PWM trigger settings" id="pwm_forceTrig" */
} pwm_module_setup_t;

 /*!
 * @brief Structure is used to hold the parameters to configure a PWM fault
 *
 * @internal gui name="PWM Fault configuration" id="pwmFaultCfg"
 */
typedef struct PwmFaultSetup
{
    bool automaticClearing;            /*!< true: Use automatic fault clearing; false: Manual fault clearing. @internal gui name="Automatic clearing" id="pwm_automaticClearing" */
    bool faultLevel;                   /*!< true: Logic 1 indicates fault; false: Logic 0 indicates fault. @internal gui name="Fault level" id="pwm_faultLevel" */
    bool useFaultFilter;               /*!< true: Use the filtered fault signal; false: Use the direct path from fault input. @internal gui name="Use fault filter" id="pwm_useFaultFilter" */
    pwm_fault_recovery_mode_t recMode; /*!< Specify when to re-enable the PWM output. @internal gui name="Fault recovery mode" id="pwm_recMode" */
} pwm_fault_setup_t;

/*!
 * @brief Structure is used to hold parameters to configure the capture capability of a signal pin
 */
typedef struct PwmCaptureSetup
{
    bool captureInputSel;     /*!< true: Use the edge counter signal as source
                                   false: Use the raw input signal from the pin as source */
    uint8_t edgeCompareVal;   /*!< Compare value, used only if edge counter is used as source */
    pwm_capture_edge_t edge0; /*!< Specify which edge causes a capture for input circuitry 0 */
    pwm_capture_edge_t edge1; /*!< Specify which edge causes a capture for input circuitry 1 */
    bool oneShotCapture;      /*!< true: Use one-shot capture mode;
                                   false: Use free-running capture mode */
} pwm_capture_setup_t;


/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the PWM to its reset state.
 *
 * Set the control registers to their reset state
 *
 * @param base  Base address pointer of eflexPWM module
 */
void PWM_HAL_Init(PWM_Type *base);

/*!
 * @brief Sets up a PWM sub-module.
 *
 * Flex PWM has 4 sub-modules. This function sets up the key features that configure
 * each sub-module. This function sets up the following:
 * 1. Clock source and clock prescaler
 * 2. Submodules PWM A & PWM B signals operation (independent or complementary)
 * 3. Reload logic to use and reload frequency
 * 4. Force trigger to use to generate the FORCE_OUT signal.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param setupParams Parameters passed in to set up the submodule
 */
void PWM_HAL_SetupPwmSubModule(PWM_Type *base, pwm_module_t subModuleNum,
                                           pwm_module_setup_t *setupParams);

/*!
 * @brief Sets up the Flex PWM fault protection.
 *
 * Flex PWM has 4 fault inputs. This function sets up each fault as follows:
 * 
 * 1. Fault automatic clearing function
 * 2. Sets up the fault level
 * 3. Defines if the fault filter should be used for this fault input
 * 4. Recovery mode to be used to re-enable the PWM output
 *
 * @param base  Base address pointer of eflexPWM module
 * @param faultNum is a number of the PWM fault to configure.
 * @param setupParams Parameters passed in to set up the fault
 */
void PWM_HAL_SetupFaults(PWM_Type *base, pwm_fault_input_t faultNum,
                                 pwm_fault_setup_t *setupParams);

/*!
 * @brief Sets up the Flex PWM capture.s
 *
 * Each PWM submodule has 3 pins can be configured to use for capture. This function 
 * sets up the capture for each pin as follows:
 * 1. Whether to use the edge counter or raw input
 * 2. Edge capture mode
 * 3. One-shot or continuous
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param pwmSignal Which signal in the submodule to setup
 * @param setupParams Parameters passed in to set up the input pin
 */
void PWM_HAL_SetupCapture(PWM_Type *base, pwm_module_t subModuleNum,
                                   pwm_module_signal_t pwmSignal, pwm_capture_setup_t *setupParams);

/*!
 * @brief Gets the PWM capture value.
 *
 * Reads one of the 6 capture value registers.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param cmpReg is a number of value compare register to get
 * @return PWM value register
 */
uint16_t PWM_HAL_GetCaptureValReg(PWM_Type *base, pwm_module_t subModuleNum,
                                            pwm_val_regs_t cmpReg);

/*!
 * @brief Sets the PWM value register.
 *
 * Sets one of the 6 value registers.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param valReg is the number of the value register to be set
 * @param val is a number of value to write
 */
void PWM_HAL_SetValReg (PWM_Type *base, uint8_t subModuleNum, pwm_val_regs_t valReg,
                               uint16_t val);

/*!
 * @brief Selects the signal to output when a FORCE_OUT signal is asserted.
 *
 * The user specifies which pin to configure by supplying the submodule number and whether
 * to modify the PWM A or the PWM B within that submodule.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param pwmSignal specifies which signal to work with in the module
 * @param mode signal to output when a FORCE_OUT is triggered
 */
void PWM_HAL_SetupForceSignal(PWM_Type *base, pwm_module_t subModuleNum,
                                       pwm_module_signal_t pwmSignal, pwm_force_signal_t mode);

/*!
 * @brief Enables all relevant PWM interrupts.
 *
 * The user can pass in an OR'ed list of PWM interrupts to enable. The list of PWM interrupts
 * is available in the enum pwm_event_t.
 *
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param eventmask OR'ed list of interrupts to enable
 */
void PWM_HAL_EnableInterrupts(PWM_Type *base, pwm_module_t subModuleNum, uint32_t eventmask);

/*!
 * @brief Disables all PWM interrupts.
 *
 * The user can pass in an OR'ed list of PWM interrupts to disable. The list of PWM interrupts
 * is available in the enum pwm_event_t.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param eventmask OR'ed list of interrupts to disable
 */
void PWM_HAL_DisableInterrupts(PWM_Type *base, pwm_module_t subModuleNum, uint32_t eventmask);

/*!
 * @brief Clears all PWM status flags.
 *
 * The user can pass in an OR'ed list of status flags to clear. The list of PWM interrupts
 * is available in the enum pwm_event_t.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param eventmask OR'ed list of status flags to clear
 */
void PWM_HAL_ClearStatus(PWM_Type *base, pwm_module_t subModuleNum, uint32_t eventmask);

/*!
 * @brief Returns the PWM peripheral current counter value.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @return current PWM counter value
 */
static inline uint16_t PWM_HAL_GetCounter(PWM_Type *base, pwm_module_t subModuleNum)
{
    return PWM_RD_CNT(base, subModuleNum);
}

/*!
 * @brief Sets the PWM timer counter initial value.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param val initial value to be set
 */
static inline void PWM_HAL_SetCounterInitVal(PWM_Type *base, pwm_module_t subModuleNum,
                                                     uint16_t val)
{
    PWM_WR_INIT(base, subModuleNum, val);
}

/*!
 * @brief Outputs a FORCE signal.
 *
 * This function enables/disables the force initialization logic and asserts/deasserts the FORCE signal.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param val true to enable, false to disable.
 */
static inline void PWM_HAL_SetForceCmd(PWM_Type *base, pwm_module_t subModuleNum, bool val )
{
    PWM_BWR_CTRL2_FRCEN(base, subModuleNum, val);
    PWM_BWR_CTRL2_FORCE(base, subModuleNum, val);
}

/*!
 * @brief Sets the output polarity for the PWM_B.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param val true to set inverted output, false to set non inverted output.
 */
static inline void PWM_HAL_SetOutputPolarityPwmBCmd(PWM_Type *base, pwm_module_t subModuleNum,
                                                                  bool val)
{
    PWM_BWR_OCTRL_POLB(base, subModuleNum, val);
}

/*!
 * @brief Sets the output polarity for the PWM_A.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param val true to set inverted output, false to set non inverted output.
 */
static inline void PWM_HAL_SetOutputPolarityPwmACmd(PWM_Type *base, pwm_module_t subModuleNum,
                                                                 bool val)
{
    PWM_BWR_OCTRL_POLA(base, subModuleNum, val);
}

/*!
 * @brief Sets the output polarity for the PWM_X.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param val true to set inverted output, false to set non inverted output.
 */
static inline void PWM_HAL_SetOutputPolarityPwmXCmd(PWM_Type *base, pwm_module_t subModuleNum,
                                                                 bool val)
{
    PWM_BWR_OCTRL_POLX(base, subModuleNum, val);
}

/*!
 * @brief Enables or disables if a match with a value register causes an output trigger.
 *
 * There are 2 triggers available per PWM submodule. This function allows the user 
 * to activate a trigger when the counter matches one of the 6 value registers. Enabling
 * VAL0, VAL2, or VAL4 outputs a trigger on a match on TRIG0. Enabling VAL1, VAL3, VAL5 
 * outputs a trigger on a match on TRIG1.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param valueReg register that is the cause for the output triger.
 * @param val true to trigger enable, false to disable.
 */
static inline void PWM_HAL_SetOutputTriggerCmd(PWM_Type *base, pwm_module_t subModuleNum,
                                                          uint8_t valueReg, bool val)
{
    assert(valueReg < 6U);
    val ? PWM_SET_TCTRL(base, subModuleNum, 1U << valueReg) :
          PWM_CLR_TCTRL(base, subModuleNum, 1U << valueReg);
}

/*!
 * @brief Enables or disables the fault input for the PWM A.
 *
 * Enabling the specified fault causes the PWM A signal to deactivate when the fault occurs.
 * The user should configure the PWM faults by calling the PWM_HAL_SetupFaults() function prior to enabling them
 * in the submodules.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param fault number, options: 0,1,2,3 .
 * @param val true to enable the fault input, false to disable fault input.
 */
static inline void PWM_HAL_SetPwmAFaultInputCmd(PWM_Type *base, pwm_module_t subModuleNum,
                                                            pwm_fault_input_t fault, bool val)
{
    val ? PWM_SET_DISMAP(base, subModuleNum, 0, 1U << fault) :
          PWM_CLR_DISMAP(base, subModuleNum, 0, 1U << fault);
}

/*!
 * @brief Enables or disables the fault input for the PWM B.
 *
 * Enabling the specified fault causes the PWM B signal to deactivate when the fault occurs.
 * The user should configure the PWM faults by calling the PWM_HAL_SetupFaults() function prior to enabling them
 * in the submodules.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param fault number, options: 0,1,2,3 .
 * @param val true to enable the fault input, false to disable fault input.
 */
static inline void PWM_HAL_SetPwmBFaultInputCmd(PWM_Type *base, pwm_module_t subModuleNum,
                                                            pwm_fault_input_t fault, bool val)
{
    val ? PWM_SET_DISMAP(base, subModuleNum, 0, 1U << (fault + PWM_DISMAP_DIS0B_SHIFT)) :
          PWM_CLR_DISMAP(base, subModuleNum, 0, 1U << (fault + PWM_DISMAP_DIS0B_SHIFT));
}

/*!
 * @brief Enables or disables the fault input for the PWM X.
 *
 * Enabling the specified fault causes the PWM X signal to deactivate when the fault occurs.
 * The user should configure the PWM faults by calling the PWM_HAL_SetupFaults() function prior to enabling them
 * in the submodules.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param fault number, options: 0,1,2,3.
 * @param val true to enable the fault input; false to disable the fault input
 */
static inline void PWM_HAL_SetPwmXFaultInputCmd(PWM_Type *base, pwm_module_t subModuleNum,
                                                            pwm_fault_input_t fault, bool val)
{
    val ? PWM_SET_DISMAP(base, subModuleNum, 0, 1U << (fault + PWM_DISMAP_DIS0X_SHIFT)) :
          PWM_CLR_DISMAP(base, subModuleNum, 0, 1U << (fault + PWM_DISMAP_DIS0X_SHIFT));
}

/*!
 * @brief Sets the PWM_X pin to input or output.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum Number of the PWM submodule.
 * @param val true to make the pin as output output, false to make the pin as input
 */
static inline void PWM_HAL_SetOutputPwmXCmd(PWM_Type *base, pwm_module_t subModuleNum,
                                                         bool val)
{
    val ? PWM_SET_OUTEN(base, 1U << subModuleNum) :
          PWM_CLR_OUTEN(base, 1U << subModuleNum);
}

/*!
 * @brief Sets the PWM_B pin to input or output.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum Number of the PWM submodule.
 * @param val true to make the pin as output output, false to make the pin as input
 */
static inline void PWM_HAL_SetOutputPwmBCmd(PWM_Type *base, pwm_module_t subModuleNum,
                                                         bool val)
{
    val ? PWM_SET_OUTEN(base, 1U << (subModuleNum + PWM_OUTEN_PWMB_EN_SHIFT)) :
          PWM_CLR_OUTEN(base, 1U << (subModuleNum + PWM_OUTEN_PWMB_EN_SHIFT));
}

/*!
 * @brief Sets the PWM_A pin to input or output.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum Number of the PWM submodule.
 * @param val true to make the pin as output output, false to make the pin as input
 */
static inline void PWM_HAL_SetOutputPwmACmd(PWM_Type *base, pwm_module_t subModuleNum,
                                                         bool val)
{
    val ? PWM_SET_OUTEN(base, 1U << (subModuleNum + PWM_OUTEN_PWMA_EN_SHIFT)) :
          PWM_CLR_OUTEN(base, 1U << (subModuleNum + PWM_OUTEN_PWMA_EN_SHIFT));
}

/*!
 * @brief Sets the software control output for a pin to high or low.
 *
 * The user specifies which signal to modify by supplying the submodule number and whether
 * to modify the PWM A or the PWM B within that submodule.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModuleNum is a number of the PWM submodule.
 * @param output specifies which signal to work with in the module, 0 is PWM B, 1 is PWM A
 * @param val true to supply a logic 1, false to supply a logic 0.
 */
static inline void PWM_HAL_SetSwCtrlOutCmd(PWM_Type *base, pwm_module_t subModuleNum,
                                                      pwm_module_signal_t output, bool val)
{
    val ? PWM_SET_SWCOUT(base, (1U << ((subModuleNum * 2) + output))) :
          PWM_CLR_SWCOUT(base, (1U << ((subModuleNum * 2) + output)));
}

/*!
 * @brief Sets the PWM generator run.
 *
 * @param base  Base address pointer of eflexPWM module
 * @param subModules represented by corresponded bits.
 * @param val true to run selected subModuleNums, false to stop selected subModuleNums output.
 */
static inline void PWM_HAL_SetPwmRunCmd(PWM_Type *base, uint8_t subModules, bool val)
{
    assert(subModules < 16U);
    val ? PWM_SET_MCTRL(base, (unsigned)subModules << PWM_MCTRL_RUN_SHIFT) :
          PWM_CLR_MCTRL(base, (unsigned)subModules << PWM_MCTRL_RUN_SHIFT);
}

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_PWM_COUNT */

#endif /* __FSL_PWM_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/
