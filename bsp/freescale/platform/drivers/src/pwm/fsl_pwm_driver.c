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

#include <assert.h>
#include <string.h>
#include "fsl_pwm_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_PWM_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* External source clock frequency */
static uint32_t moduleExternalSrcFreq = 0;
/* Module 0 clock frequency */
static uint32_t pwmModuleFreq[kFlexPwmModule3 + 1] = { 0 };

/*!
 * @addtogroup pwm_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_DRV_Init
 * Description   : Initializes the PWM module.
 * Enables the module clocks and interrupts in the interrupt controller.
 *
 *END**************************************************************************/
pwm_status_t PWM_DRV_Init(uint32_t instance)
{
    assert(instance < PWM_INSTANCE_COUNT);
    PWM_Type *pwmBase = g_pwmBase[instance];
    int i = 0;

    CLOCK_SYS_EnablePwmClock(0U);
    CLOCK_SYS_EnablePwmClock(1U);
    CLOCK_SYS_EnablePwmClock(2U);
    CLOCK_SYS_EnablePwmClock(3U);

    /* Enable eFlexPWM interrupts on NVIC level. */
    for (i = 0; i < FSL_FEATURE_PWM_CMP_INT_HANDLER_COUNT; i++)
    {
        INT_SYS_EnableIRQ(g_pwmCmpIrqId[i]);
    }
    for (i = 0; i < FSL_FEATURE_PWM_RELOAD_INT_HANDLER_COUNT; i++)
    {
        INT_SYS_EnableIRQ(g_pwmReloadIrqId[i]);
    }
    for (i = 0; i < FSL_FEATURE_PWM_CAP_INT_HANDLER_COUNT; i++)
    {
        INT_SYS_EnableIRQ(g_pwmCapIrqId[i]);
    }
    for (i = 0; i < FSL_FEATURE_PWM_RERR_INT_HANDLER_COUNT; i++)
    {
        INT_SYS_EnableIRQ(g_pwmRerrIrqId[instance]);
    }
    for (i = 0; i < FSL_FEATURE_PWM_FAULT_INT_HANDLER_COUNT; i++)
    {
        INT_SYS_EnableIRQ(g_pwmFaultIrqId[instance]);
    }
    /* Initialize the module */
    PWM_HAL_Init(pwmBase);

    /* Set the initial clock frequency from module 0 */
    pwmModuleFreq[kFlexPwmModule0] = CLOCK_SYS_GetPwmFreq(0);

    return kStatusPwmSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_DRV_Deinit
 * Description   : Shuts down the PWM driver.
 * This function de-initializes the EflexPWM module and dissables the clock for the submodules.
 * Function disables the module-level interrupts.
 *
 *END**************************************************************************/
void PWM_DRV_Deinit(uint32_t instance)
{
    assert(instance < PWM_INSTANCE_COUNT);
    int i = 0;

    /* Disable Clock to each eFlexPWM submodules. */
    CLOCK_SYS_DisablePwmClock(0U);
    CLOCK_SYS_DisablePwmClock(1U);
    CLOCK_SYS_DisablePwmClock(2U);
    CLOCK_SYS_DisablePwmClock(3U);

    /* Disable eFlexPWM interrupts on NVIC level. */
    for (i = 0; i < FSL_FEATURE_PWM_CMP_INT_HANDLER_COUNT; i++)
    {
        INT_SYS_DisableIRQ(g_pwmCmpIrqId[i]);
    }
    for (i = 0; i < FSL_FEATURE_PWM_RELOAD_INT_HANDLER_COUNT; i++)
    {
        INT_SYS_DisableIRQ(g_pwmReloadIrqId[i]);
    }
    for (i = 0; i < FSL_FEATURE_PWM_CAP_INT_HANDLER_COUNT; i++)
    {
        INT_SYS_DisableIRQ(g_pwmCapIrqId[i]);
    }
    for (i = 0; i < FSL_FEATURE_PWM_RERR_INT_HANDLER_COUNT; i++)
    {
        INT_SYS_DisableIRQ(g_pwmRerrIrqId[instance]);
    }
    for (i = 0; i < FSL_FEATURE_PWM_FAULT_INT_HANDLER_COUNT; i++)
    {
        INT_SYS_DisableIRQ(g_pwmFaultIrqId[instance]);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_DRV_SetupPwm
 * Description   : Sets up the PWM signals from the FlewPWM module.
 * The function will initialize the submodule per the parameters passed in by the user. The function
 * will also setup the value compare registers to match the PWM signal requirements
 * NOTE: If the deadtime insertion logic is enabled then the pulse period will be reduced by the
 * deadtime period specified by the user.
 *
 *END**************************************************************************/
pwm_status_t PWM_DRV_SetupPwm(uint32_t instance, pwm_module_t subModule, pwm_module_setup_t *moduleSetupParams,
                                       pwm_module_signal_setup_t *signalParams)
{
    assert(instance < PWM_INSTANCE_COUNT);

    PWM_Type *pwmBase = g_pwmBase[instance];
    uint32_t freq = 0;

    /* Source clock for submodule 0 cannot be itself */
    if ((moduleSetupParams->clkSrc == kClkSrcPwm0Clk) && (subModule == kFlexPwmModule0))
    {
        return kStatusPwmInvalidArgument;
    }
    /*
     * If source clock selection is an external clock, then user should have first provide the
     * source frequency by calling PWM_DVR_SetExternalClkFreq() before calling this function
     */
    if ((moduleSetupParams->clkSrc == kClkSrcPwmExtClk) && (moduleExternalSrcFreq == 0))
    {
        return kStatusPwmInvalidArgument;
    }

    /* Setup the PWM submodule */
    PWM_HAL_SetupPwmSubModule(pwmBase, subModule, moduleSetupParams);

    if (moduleSetupParams->clkSrc == kClkSrcPwmIPBusClk)
    {
        freq = CLOCK_SYS_GetPwmFreq(0);
    }
    else if (moduleSetupParams->clkSrc == kClkSrcPwm0Clk)
    {
        freq = pwmModuleFreq[kFlexPwmModule0];
    }
    else
    {
        freq = moduleExternalSrcFreq;
    }
    freq = freq / (1 << moduleSetupParams->prescale);

    /* Save the module ferquency */
    pwmModuleFreq[subModule] = freq;

    PWM_DRV_UpdatePwmSignal(instance, subModule, signalParams);

    return kStatusPwmSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_DRV_UpdatePwmSignal
 * Description   : Update the PWM signal settings.
 * The function will update the PWM signal that to the new value that is passed in
 * NOTE: If the deadtime insertion logic is enabled then the pulse period will be reduced by the
 * deadtime period specified by the user.
 *
 *END**************************************************************************/
void PWM_DRV_UpdatePwmSignal(uint32_t instance, pwm_module_t subModule,
                                        pwm_module_signal_setup_t *signalParams)
{
    assert(instance < PWM_INSTANCE_COUNT);

    PWM_Type *pwmBase = g_pwmBase[instance];
    uint16_t pulseCnt, pwmAHighPulse = 0, pwmBHighPulse = 0;
    int16_t modulo = 0;

    pulseCnt = ((uint64_t)pwmModuleFreq[subModule] * signalParams->pwmPeriod) / 1000000;

    /* Set signal polarity */
    PWM_HAL_SetOutputPolarityPwmACmd (pwmBase, subModule, signalParams->pwmAPolarity);
    PWM_HAL_SetOutputPolarityPwmBCmd (pwmBase, subModule, signalParams->pwmBPolarity);

    /* Pulse width of PWM A */
    if (signalParams->pwmAPulseWidth != FLEXPWM_NO_PWM_OUT_SIGNAL)
    {
        pwmAHighPulse = ((uint64_t)pwmModuleFreq[subModule] * signalParams->pwmAPulseWidth) / 1000000;
        /* Enable output on PWM A */
        PWM_SET_OUTEN(pwmBase, (1U << (PWM_OUTEN_PWMA_EN_SHIFT + subModule)));
    }
    else
    {
        /* Disable output on PWM A */
        PWM_CLR_OUTEN(pwmBase, (1U << (PWM_OUTEN_PWMA_EN_SHIFT + subModule)));
    }

    /* Pulse width of PWM B */
    if (signalParams->pwmBPulseWidth != FLEXPWM_NO_PWM_OUT_SIGNAL)
    {
        pwmBHighPulse = ((uint64_t)pwmModuleFreq[subModule] * signalParams->pwmBPulseWidth) / 1000000;
        /* Enable output on PWM A */
        PWM_SET_OUTEN(pwmBase, (1U << (PWM_OUTEN_PWMB_EN_SHIFT + subModule)));

    }
    else
    {
        /* Disable output on PWM B */
        PWM_CLR_OUTEN(pwmBase, (1U << (PWM_OUTEN_PWMB_EN_SHIFT + subModule)));
    }

    /* Setup the different match registers to generate the PWM signal */
    switch(signalParams->pwmType)
    {
        case kFlexPwmSignedCenterAligned:
            modulo = pulseCnt >> 1;
            PWM_WR_INIT(pwmBase, subModule, -modulo);
            PWM_WR_VAL0(pwmBase, subModule, 0);
            PWM_WR_VAL1(pwmBase, subModule, modulo);
            if (pwmAHighPulse != 0)
            {
                PWM_WR_VAL2(pwmBase, subModule, -(pwmAHighPulse / 2));
                PWM_WR_VAL3(pwmBase, subModule, pwmAHighPulse / 2);
            }
            if (pwmBHighPulse != 0)
            {
                PWM_WR_VAL4(pwmBase, subModule, -(pwmBHighPulse / 2));
                PWM_WR_VAL5(pwmBase, subModule, pwmBHighPulse / 2);
            }

            break;
        case kFlexPwmCenterAligned:
            PWM_WR_INIT(pwmBase, subModule, 0);
            PWM_WR_VAL0(pwmBase, subModule, pulseCnt / 2);
            PWM_WR_VAL1(pwmBase, subModule, pulseCnt);
            if (pwmAHighPulse != 0)
            {
                PWM_WR_VAL2(pwmBase, subModule, (pulseCnt - pwmAHighPulse) / 2);
                PWM_WR_VAL3(pwmBase, subModule, (pulseCnt + pwmAHighPulse) / 2);
            }
            if (pwmBHighPulse != 0)
            {
                PWM_WR_VAL4(pwmBase, subModule, (pulseCnt - pwmBHighPulse) / 2);
                PWM_WR_VAL5(pwmBase, subModule, (pulseCnt - pwmBHighPulse) / 2);
            }

            break;
        case kFlexPwmSignedEdgeAligned:
            modulo = pulseCnt >> 1;
            PWM_WR_INIT(pwmBase, subModule, -modulo);
            PWM_WR_VAL0(pwmBase, subModule, 0);
            PWM_WR_VAL1(pwmBase, subModule, modulo);
            if (pwmAHighPulse != 0)
            {
                PWM_WR_VAL2(pwmBase, subModule, -modulo);
                PWM_WR_VAL3(pwmBase, subModule, (-modulo + pwmAHighPulse));
            }
            if (pwmBHighPulse != 0)
            {
                PWM_WR_VAL4(pwmBase, subModule, -modulo);
                PWM_WR_VAL5(pwmBase, subModule, (-modulo + pwmBHighPulse));
            }

            break;
        case kFlexPwmEdgeAligned:
            PWM_WR_INIT(pwmBase, subModule, 0);
            PWM_WR_VAL0(pwmBase, subModule, pulseCnt / 2);
            PWM_WR_VAL1(pwmBase, subModule, pulseCnt);
            if (pwmAHighPulse != 0)
            {
                PWM_WR_VAL2(pwmBase, subModule, 0);
                PWM_WR_VAL3(pwmBase, subModule, pwmAHighPulse);
            }
            if (pwmBHighPulse != 0)
            {
                PWM_WR_VAL4(pwmBase, subModule, 0);
                PWM_WR_VAL5(pwmBase, subModule, pwmBHighPulse);
            }
            break;
        default:
            break;
    }
    /* Set LDOK bit for this submodule */
    PWM_SET_MCTRL(pwmBase, (1U << subModule));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_DRV_CounterStart
 * Description   : Starts the PWM.
 *
 *END**************************************************************************/
void PWM_DRV_CounterStart(uint32_t instance, uint8_t value)
{
    assert(instance < PWM_INSTANCE_COUNT);
    PWM_Type *pwmBase = g_pwmBase[instance];

    /* Start multiple PWM sub-modules based on the value passed in */
    PWM_HAL_SetPwmRunCmd(pwmBase, value, true);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_DRV_CounterStop
 * Description   : Stops the PWM.
 *
 *END**************************************************************************/
void PWM_DRV_CounterStop(uint32_t instance, uint8_t value)
{
    assert(instance < PWM_INSTANCE_COUNT);
    PWM_Type *pwmBase = g_pwmBase[instance];

    /* Stop PWM counters */
    PWM_HAL_SetPwmRunCmd(pwmBase, 0x7U, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_DRV_SetTriggerCmd
 * Description   : Enable or disable the PWM output trigger.
 * This function will allow user to enable or disable a PWM triger. PWM has 2 triggers. Trigger 0 is
 * activated when the counter matches VAL 0, VAL 2 or VAL 4 register. Trigger 1 is activated when the
 * counter matches VAL 1, VAL 3 or VAL 5.
 *
 *END**************************************************************************/
void PWM_DRV_SetTriggerCmd(uint32_t instance, pwm_module_t subModule, pwm_val_regs_t trigger,
                                    bool activate)
{
    assert(instance < PWM_INSTANCE_COUNT);
    PWM_Type *pwmBase = g_pwmBase[instance];

    activate ? PWM_SET_TCTRL(pwmBase, subModule, (1U << trigger)) :
               PWM_CLR_TCTRL(pwmBase, subModule, (1U << trigger));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_DRV_SetTriggerVal
 * Description   : Set the PWM trigger value.
 * This function sets the value in the compare register that will be used to generate a trigger.
 * NOTE: User must make sure the value register being modified is not currently used to generate a
 * PWM signal.
 *
 *END**************************************************************************/
void PWM_DRV_SetTriggerVal(uint32_t instance, pwm_module_t subModule, pwm_val_regs_t trigger,
                                  uint16_t triggerVal)
{
    assert(instance < PWM_INSTANCE_COUNT);
    PWM_Type *pwmBase = g_pwmBase[instance];

    PWM_HAL_SetValReg(pwmBase, subModule, trigger, triggerVal);
    /* Set LDOK bit for this submodule */
    PWM_SET_MCTRL(pwmBase, (1U << subModule));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_DRV_SetupFault
 * Description   : Sets up the PWM fault.
 * This function will configure a fault parameters and enable the fault for the appropriate
 * sub-module signals
 *
 *END**************************************************************************/
void PWM_DRV_SetupFault(uint32_t instance, pwm_module_t subModule, pwm_fault_input_t faultNum, pwm_fault_setup_t *faultParams,
                               bool pwmA, bool pwmB, bool pwmX)
{
    assert(instance < PWM_INSTANCE_COUNT);
    PWM_Type *pwmBase = g_pwmBase[instance];

    PWM_HAL_SetupFaults(pwmBase, faultNum, faultParams);

    PWM_HAL_SetPwmAFaultInputCmd(pwmBase, subModule, faultNum, pwmA);
    PWM_HAL_SetPwmBFaultInputCmd(pwmBase, subModule, faultNum, pwmB);
    PWM_HAL_SetPwmXFaultInputCmd(pwmBase, subModule, faultNum, pwmX);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_DRV_SetExternalFreq
 * Description   : Provide the frequency of the external clock source.
 * When using an external signal as clock source, the user should provide the frequency
 * of this clock source so that this driver can calculate the register values used to generate
 * the requested PWM signal.
 *
 *END**************************************************************************/
void PWM_DRV_SetExternalClkFreq(uint32_t instance, uint32_t externalClkFreq)
{
    assert(instance < PWM_INSTANCE_COUNT);

    moduleExternalSrcFreq = externalClkFreq;
}

#endif /* FSL_FEATURE_SOC_PWM_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/

