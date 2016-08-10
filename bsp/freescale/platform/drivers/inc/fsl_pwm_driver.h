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

#ifndef __FSL_PWM_DRIVER_H__
#define __FSL_PWM_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>

#include "fsl_pwm_hal.h"
#include "fsl_os_abstraction.h"

#if FSL_FEATURE_SOC_PWM_COUNT

/*!
 * @addtogroup pwm_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! Used to indicate that a particular pin in the submodule does NOT  output a PWM signal */
#define FLEXPWM_NO_PWM_OUT_SIGNAL      (0)

/*! @brief PWM Signal Type options */
typedef enum _pwm_signal_type
{
    kFlexPwmSignedCenterAligned = 0U,   /*!< Signed center-aligned. @internal gui name="Signed center-aligned PWM" */
    kFlexPwmCenterAligned,              /*!< Unsigned cente-aligned. @internal gui name="Center-aligned PWM" */
    kFlexPwmSignedEdgeAligned,          /*!< Signed edge-aligned. @internal gui name="Signed edge-aligned PWM" */
    kFlexPwmEdgeAligned                 /*!< Unsigned edge-aligned. @internal gui name="Edge-aligned PWM" */
} pwm_signal_type_t;

/*!
 * @brief Configuration structure for the user to define the PWM signal characteristics
 *
 * @internal gui name="PWM signal configuration" id="pwmSignalCfg"
 */
typedef struct PwmModuleSignalSetup {
    uint32_t pwmPeriod;        /*!< PWM period specified in microseconds. @internal gui name="PWM period" id="pwm_pwmPeriod" */
    pwm_signal_type_t pwmType; /*!< PWM type, edge or center, signed or unsigned. @internal gui name="PWM signal type" id="pwm_pwmType" */
    uint32_t pwmAPulseWidth;   /*!< PWM A pulse width specified in microseconds. Specify FLEXPWM_NO_PWM_OUT_SIGNAL if no PWM output on this pin. @internal gui name="PWM-A pulse width" id="pwm_pwmAPulseWidth" */
    uint32_t pwmBPulseWidth;   /*!< PWM B pulse width specified in microseconds. Specify FLEXPWM_NO_PWM_OUT_SIGNAL if no PWM output on this pin. @internal gui name="PWM-B pulse width" id="pwm_pwmBPulseWidth" */
    bool pwmAPolarity;         /*!< true: if output is to be inverted; false: if no output inversion. @internal gui name="PWM-A signal polarity" id="pwm_pwmAPolarity" */
    bool pwmBPolarity;         /*!< true: if output is to be inverted; false: if no output inversion. @internal gui name="PWM-B signal polarity" id="pwm_pwmBPolarity" */
} pwm_module_signal_setup_t;

/*! @brief Table of base addresses for PWM instances. */
extern PWM_Type * const g_pwmBase[PWM_INSTANCE_COUNT];

/*! @brief Table to save PWM IRQ enumeration numbers defined in CMSIS header file. */
extern const IRQn_Type g_pwmCmpIrqId[FSL_FEATURE_PWM_CMP_INT_HANDLER_COUNT];
extern const IRQn_Type g_pwmReloadIrqId[FSL_FEATURE_PWM_RELOAD_INT_HANDLER_COUNT];
extern const IRQn_Type g_pwmCapIrqId[FSL_FEATURE_PWM_CAP_INT_HANDLER_COUNT];
extern const IRQn_Type g_pwmRerrIrqId[FSL_FEATURE_PWM_RERR_INT_HANDLER_COUNT];
extern const IRQn_Type g_pwmFaultIrqId[FSL_FEATURE_PWM_FAULT_INT_HANDLER_COUNT];

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the PWM module.
 *
 * Enables the module clocks and interrupts in the interrupt controller.
 *
 * @param instance      Instance number of the PWM module.
 * @return kStatusPwmSuccess means success. Otherwise, means failure.
 */
pwm_status_t PWM_DRV_Init(uint32_t instance);

/*!
 * @brief Shuts down the PWM driver.
 *
 * This function de-initializes the EflexPWM module and disables the clock for the submodules.
 * It also disables the module-level interrupts.
 *
 * @param instance      Instance number of the PWM module.
 */
void PWM_DRV_Deinit(uint32_t instance);

/*!
 * @brief Sets up the PWM signals from the FlewPWM module.
 *
 * The function initializes the submodule according to the parameters passed in by the user. The function
 * also sets up the value compare registers to match the PWM signal requirements.
 * If the dead time insertion logic is enabled, the pulse period is reduced by the
 * dead time period specified by the user.
 *
 * @param instance      Instance number of the PWM module.
 * @param subModule     The FlexPWM submodule that is configured
 * @param moduleSetupParams  The initialization values used to set up the submodule
 * @param signalParams  Signal parameters which generate the submodules PWM signals
 * @return Returns an error if the requested submodule clock is incorrect, i.e., the request for kFlexPwmModule0
 *         for submodule 0 or request for external clock without informing the driver of the external
 *         clock frequency by calling PWM_DVR_SetExternalClkFreq(). Success otherwise.
 */
pwm_status_t PWM_DRV_SetupPwm(uint32_t instance, pwm_module_t subModule, pwm_module_setup_t *moduleSetupParams,
                                       pwm_module_signal_setup_t *signalParams);

/*!
 * @brief Updates the PWM signal settings.
 *
 * The function updates the PWM signal to the new value that is passed in.
 * If the dead time insertion logic is enabled then the pulse period is reduced by the
 * dead time period specified by the user.
 *
 * @param instance      Instance number of the PWM module.
 * @param subModule     The FlexPWM submodule that is configured
 * @param signalParams  Signal parameters which generate the submodules PWM signals
 */
void PWM_DRV_UpdatePwmSignal(uint32_t instance, pwm_module_t subModule,
                                        pwm_module_signal_setup_t *signalParams);

/*!
 * @brief Enables or disables the PWM output trigger.
 *
 * This function allows the user to enable or disable the PWM trigger. The PWM has 2 triggers. The trigger 0
 * is activated when the counter matches VAL 0, VAL 2, or VAL 4 register. The trigger 1 is activated
 * when the counter matches VAL 1, VAL 3, or VAL 5.
 *
 * @param instance      Instance number of the PWM module.
 * @param subModule     The FlexPWM submodule that is configured
 * @param trigger       Trigger number that the user wants to activate
 * @param activate      Enable or disable the trigger
 */
void PWM_DRV_SetTriggerCmd(uint32_t instance, pwm_module_t subModule, pwm_val_regs_t trigger, bool activate);

/*!
 * @brief Sets the PWM trigger value.
 *
 * This function sets the value in the compare register that generates a trigger.
 * Note that the user must make sure that the value of the register being modified is not currently used to generate
 * a PWM signal.
 *
 * @param instance      Instance number of the PWM module.
 * @param subModule     The FlexPWM submodule that is configured
 * @param trigger       Trigger number that we wish to configure
 * @param triggerVal    Trigger value
 */
void PWM_DRV_SetTriggerVal(uint32_t instance, pwm_module_t subModule, pwm_val_regs_t trigger, uint16_t triggerVal);

/*!
 * @brief Sets up the PWM fault.
 *
 * This function configures a fault parameter and enables the fault for the appropriate
 * sub-module signals.
 *
 * @param instance      Instance number of the PWM module.
 * @param subModule     The FlexPWM submodule that is configured
 * @param faultNum      Fault that should be configured
 * @param faultParams   Parameters that configure the fault
 * @param pwmA          true: PWM A is disabled by this fault; false: PWM A is not affected by this fault
 * @param pwmB          true: PWM B is disabled by this fault; false: PWM A is not affected by this fault
 * @param pwmX          true: PWM X is disabled by this fault; false: PWM A is not affected by this fault
 */
void PWM_DRV_SetupFault(uint32_t instance, pwm_module_t subModule, pwm_fault_input_t faultNum, pwm_fault_setup_t *faultParams,
                               bool pwmA, bool pwmB, bool pwmX);

/*!
 * @brief Starts the PWM counter.
 *
 * This function starts the PWM submodule counters.
 *
 * @param instance      Instance number of the PWM module.
 * @param value         Submodules to start; 4 bit value, 1-bit for each submodule
 */
void PWM_DRV_CounterStart(uint32_t instance, uint8_t value);

/*!
 * @brief Stops the PWM counter.
 *
 * This function stops the the PWM submodule counters.
 *
 * @param instance      Instance number of the PWM module.
 * @param value         Submodules to stop;  4 bit value, 1-bit for each submodule
 */
void PWM_DRV_CounterStop(uint32_t instance, uint8_t value);

/*!
 * @brief Provides the frequency of the external clock source.
 *
 * When using an external signal as clock source, the user should provide the frequency
 * of this clock source so that this driver can calculate the register values used to generate
 * the requested PWM signal.
 *
 * @param instance        Instance number of the PWM module.
 * @param externalClkFreq External clock frequency (in Hz).
 */
void PWM_DRV_SetExternalClkFreq(uint32_t instance, uint32_t externalClkFreq);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_PWM_COUNT */

#endif /* __FSL_PWM_DRIVER_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

