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

#include "fsl_pwm_hal.h"

#if FSL_FEATURE_SOC_PWM_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/


/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_HAL_Init
 * Description   : Initialize the PWM registers
 * Bring the control registers to their reset state.
 *
 *END**************************************************************************/
void PWM_HAL_Init(PWM_Type *base)
{
    uint8_t i = 0;

    PWM_WR_MCTRL(base, 0);
    PWM_WR_OUTEN(base, 0);
    PWM_WR_MASK(base, 0);
    PWM_WR_FCTRL(base, 0);
    PWM_WR_FCTRL2(base, 0);
    PWM_WR_FSTS(base, 0xF);

    for (i = 0; i <= kFlexPwmModule3; i++)
    {
        PWM_WR_CTRL(base, i, 0);
        PWM_WR_CTRL2(base, i, 0);
        PWM_WR_OCTRL(base, i, 0);
        PWM_WR_TCTRL(base, i, 0);
        PWM_WR_DISMAP(base, i, 0, 0x0);
        PWM_WR_DTCNT0_DTCNT0(base, i, 0);
        PWM_WR_DTCNT1_DTCNT1(base, i, 0);
        PWM_WR_INTEN(base, i, 0);
        PWM_WR_STS(base, i, 0x3FFF);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_HAL_SetupPwmSubModule
 * Description   : Sets PWM sub-module.
 * Flex PWM has 4 sub-modules. This function sets up key features that configure the
 * working of each sub-module. This function will setup:
 * 1. Clock source and clock prescaler
 * 2. Submodules PWM A & PWM B signals operation (independent or complementary)
 * 3. Reload logic to use and reload freqeuncy
 * 4. Force trigger to use to generate the FORCE_OUT signal.
 *
 *END**************************************************************************/
void PWM_HAL_SetupPwmSubModule(PWM_Type *base, pwm_module_t subModuleNum,
                                           pwm_module_setup_t *setupParams)
{
    PWM_BWR_CTRL_PRSC(base, subModuleNum, setupParams->prescale);
    PWM_BWR_CTRL2_CLK_SEL(base, subModuleNum, setupParams->clkSrc);
    PWM_BWR_CTRL2_INIT_SEL(base, subModuleNum, setupParams->cntrInitSel);
    PWM_BWR_CTRL2_FORCE_SEL(base, subModuleNum, setupParams->forceTrig);

    /* Setup PWM A & B to be independent or complementary-pair */
    switch(setupParams->chnlPairOper)
    {
        case kFlexPwmIndependent:
            PWM_BWR_CTRL2_INDEP(base, subModuleNum, 1U);
            break;
        case kFlexPwmComplementaryPwmA:
            PWM_BWR_CTRL2_INDEP(base, subModuleNum, 0U);
            PWM_CLR_MCTRL(base, (unsigned)1 << (PWM_MCTRL_IPOL_SHIFT + subModuleNum));
            break;
        case kFlexPwmComplementaryPwmB:
            PWM_BWR_CTRL2_INDEP(base, subModuleNum, 0U);
            PWM_SET_MCTRL(base, (unsigned)1 << (PWM_MCTRL_IPOL_SHIFT + subModuleNum));
            break;
        default:
            break;
    }

    /* Setup reload logic */
    PWM_BWR_CTRL_LDFQ(base, subModuleNum, setupParams->reloadFreq);
    /* Initially clear the immediate reload option */
    PWM_BWR_CTRL_LDMOD(base, subModuleNum, 0U);

    switch(setupParams->reloadLogic)
    {
        case kFlexPwmReloadImmediate:
            PWM_BWR_CTRL_LDMOD(base, subModuleNum, 1U);
            break;
        case kFlexPwmReloadPwmHalfCycle:
            PWM_BWR_CTRL_HALF(base, subModuleNum, 1U);
            PWM_BWR_CTRL_FULL(base, subModuleNum, 0U);
            break;
        case kFlexPwmReloadPwmFullCycle:
            PWM_BWR_CTRL_HALF(base, subModuleNum, 0U);
            PWM_BWR_CTRL_FULL(base, subModuleNum, 1U);
            break;
        case kFlexPwmReloadPwmHalfAndFullCycle:
            PWM_BWR_CTRL_HALF(base, subModuleNum, 1U);
            PWM_BWR_CTRL_FULL(base, subModuleNum, 1U);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_HAL_SetupFaults
 * Description   : Sets up the working of the Flex PWM fault protection.
 * Flex PWM has 4 fault inputs. This function sets up the working of each fault.
 * The function will setup:
 * 1. Fault automatic clearing function
 * 2. Sets up the fault level
 * 3. Defines if the fault filter should be used for this fault input
 * 4. Recovery mode to be used to re-enable the PWM output
 *
 *END**************************************************************************/
void PWM_HAL_SetupFaults(PWM_Type *base, pwm_fault_input_t faultNum,
                                 pwm_fault_setup_t *setupParams)
{
    /* Set the faults level-settting */
    setupParams->faultLevel ? PWM_SET_FCTRL(base, (unsigned)1 << (PWM_FCTRL_FLVL_SHIFT + faultNum)) :
                              PWM_CLR_FCTRL(base, (unsigned)1 << (PWM_FCTRL_FLVL_SHIFT + faultNum));
    /* Set the auto-clearing option */
    setupParams->automaticClearing ? PWM_SET_FCTRL(base, (unsigned)1 << (PWM_FCTRL_FAUTO_SHIFT + faultNum)) :
                                     PWM_CLR_FCTRL(base, (unsigned)1 << (PWM_FCTRL_FAUTO_SHIFT + faultNum));
    /* Set fault filter enable option */
    setupParams->useFaultFilter ? PWM_SET_FCTRL2(base, (unsigned)1 << faultNum) :
                                  PWM_CLR_FCTRL2(base, (unsigned)1 << faultNum);


    /* Initially clear both recovery modes */
    PWM_CLR_FSTS(base, (unsigned)1 << (PWM_FSTS_FFULL_SHIFT + faultNum));
    PWM_CLR_FSTS(base, (unsigned)1 << (PWM_FSTS_FHALF_SHIFT + faultNum));
    /* Setup fault recovery */
    switch(setupParams->recMode)
    {
        case kFlexPwmNoRecovery:
            break;
        case kFlexPwmRecoverHalfCycle:
            PWM_SET_FSTS(base, (unsigned)1 << (PWM_FSTS_FHALF_SHIFT + faultNum));
            break;
        case kFlexPwmRecoverFullCycle:
            PWM_SET_FSTS(base, (unsigned)1 << (PWM_FSTS_FFULL_SHIFT + faultNum));
            break;
        case kFlexPwmRecoverHalfAndFullCycle:
            PWM_SET_FSTS(base, (unsigned)1 << (PWM_FSTS_FHALF_SHIFT + faultNum));
            PWM_SET_FSTS(base, (unsigned)1 << (PWM_FSTS_FFULL_SHIFT + faultNum));
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_HAL_SetupCapture
 * Description   : Sets up the Flex PWM capture
 * Each PWM submodule has 3 pins can be configured to use for capture. This function will
 * setup the capture for each pin as follows:
 * 1. Whether to use the edge counter or raw input
 * 2. Edge capture mode
 * 3. One-shot or continuous
 *
 *END**************************************************************************/
void PWM_HAL_SetupCapture(PWM_Type *base, pwm_module_t subModuleNum,
                                   pwm_module_signal_t pwmSignal, pwm_capture_setup_t *setupParams)
{
    switch(pwmSignal)
    {
        case kFlexPwmA:
            PWM_BWR_CAPTCTRLA_INP_SELA(base, subModuleNum, setupParams->captureInputSel);
            setupParams->captureInputSel ? PWM_BWR_CAPTCTRLA_EDGCNTA_EN(base, subModuleNum, 1) :
                                           PWM_BWR_CAPTCTRLA_EDGCNTA_EN(base, subModuleNum, 0);
            PWM_BWR_CAPTCTRLA_EDGA0(base, subModuleNum, setupParams->edge0);
            PWM_BWR_CAPTCTRLA_EDGA1(base, subModuleNum, setupParams->edge1);
            PWM_BWR_CAPTCOMPA_EDGCMPA(base, subModuleNum, setupParams->edgeCompareVal);
            PWM_BWR_CAPTCTRLA_ONESHOTA(base, subModuleNum, setupParams->oneShotCapture);
            break;
        case kFlexPwmB:
            PWM_BWR_CAPTCTRLB_INP_SELB(base, subModuleNum, setupParams->captureInputSel);
            setupParams->captureInputSel ? PWM_BWR_CAPTCTRLB_EDGCNTB_EN(base, subModuleNum, 1) :
                                           PWM_BWR_CAPTCTRLB_EDGCNTB_EN(base, subModuleNum, 0);
            PWM_BWR_CAPTCTRLB_EDGB0(base, subModuleNum, setupParams->edge0);
            PWM_BWR_CAPTCTRLB_EDGB1(base, subModuleNum, setupParams->edge1);
            PWM_BWR_CAPTCOMPB_EDGCMPB(base, subModuleNum, setupParams->edgeCompareVal);
            PWM_BWR_CAPTCTRLB_ONESHOTB(base, subModuleNum, setupParams->oneShotCapture);
            break;
        case kFlexPwmX:
            PWM_BWR_CAPTCTRLX_INP_SELX(base, subModuleNum, setupParams->captureInputSel);
            setupParams->captureInputSel ? PWM_BWR_CAPTCTRLX_EDGCNTX_EN(base, subModuleNum, 1) :
                                           PWM_BWR_CAPTCTRLX_EDGCNTX_EN(base, subModuleNum, 0);
            PWM_BWR_CAPTCTRLX_EDGX0(base, subModuleNum, setupParams->edge0);
            PWM_BWR_CAPTCTRLX_EDGX1(base, subModuleNum, setupParams->edge1);
            PWM_BWR_CAPTCOMPX_EDGCMPX(base, subModuleNum, setupParams->edgeCompareVal);
            PWM_BWR_CAPTCTRLX_ONESHOTX(base, subModuleNum, setupParams->oneShotCapture);
            break;
        default:
            break;
    }

}

/*******************************************************************************
 *
 * Function Name : PWM_HAL_SetValReg
 * Description   : Sets PWM value register.
 * Sets one of the 6 value registers.
 *
 *END**************************************************************************/
void PWM_HAL_SetValReg (PWM_Type *base, uint8_t subModuleNum, pwm_val_regs_t valReg, uint16_t val)
{
    assert(subModuleNum < FSL_FEATURE_PWM_SUBMODULE_COUNT);

    switch(valReg)
    {
        case kFlexPwmVAL0:
            PWM_WR_VAL0(base, subModuleNum, val);
            break;
        case kFlexPwmVAL1:
            PWM_WR_VAL1(base, subModuleNum, val);
            break;
        case kFlexPwmVAL2:
            PWM_WR_VAL2(base, subModuleNum, val);
            break;
        case kFlexPwmVAL3:
            PWM_WR_VAL3(base, subModuleNum, val);
            break;
        case kFlexPwmVAL4:
            PWM_WR_VAL4(base, subModuleNum, val);
            break;
        case kFlexPwmVAL5:
            PWM_WR_VAL5(base, subModuleNum, val);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_HAL_GetCaptureValReg
 * Description   : Gets PWM capture value.
 * Read one of the 6 capture value registers
 *
 *END**************************************************************************/
uint16_t PWM_HAL_GetCaptureValReg(PWM_Type *base, pwm_module_t subModuleNum, pwm_val_regs_t cmpReg)
{
    uint16_t temp;
    assert(cmpReg < 6U);

    switch(cmpReg)
    {
        case kFlexPwmVAL0:
            temp = PWM_RD_CVAL0(base, subModuleNum);
            break;
        case kFlexPwmVAL1:
            temp = PWM_RD_CVAL1(base, subModuleNum);
            break;
        case kFlexPwmVAL2:
            temp = PWM_RD_CVAL2(base, subModuleNum);
            break;
        case kFlexPwmVAL3:
            temp = PWM_RD_CVAL3(base, subModuleNum);
            break;
        case kFlexPwmVAL4:
            temp = PWM_RD_CVAL4(base, subModuleNum);
            break;
        case kFlexPwmVAL5:
            temp = PWM_RD_CVAL5(base, subModuleNum);
            break;
        default:
            temp = 0U;
            break;
    }

    return temp;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_HAL_SetupForceSignal
 * Description   : Selects the signal to output when a FORCE_OUT signal is asserted
 * User specifies which pin to configure by supplying the submodule number and whether
 * he wishes to modify PWM A or PWM B within that submodule
 *
 *END**************************************************************************/
void PWM_HAL_SetupForceSignal(PWM_Type *base, pwm_module_t subModuleNum,
                                       pwm_module_signal_t pwmSignal, pwm_force_signal_t mode)
{
    uint32_t shift, mask;

    shift = subModuleNum * 4 + pwmSignal * 2;
    mask = 0x3 << shift;

    PWM_WR_DTSRCSEL(base, (PWM_RD_DTSRCSEL(base) & ~mask) | (mode << shift));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_HAL_EnableInterrupts
 * Description   : Enables all PWM interrupts that the user is interested to use
 * User can pass in an OR'ed list of PWM interrupts to enable. The list of available PWM interrupts
 * is available in the enum pwm_event_t
 *
 *END**************************************************************************/
void PWM_HAL_EnableInterrupts(PWM_Type *base, pwm_module_t subModuleNum, uint32_t eventmask)
{
    PWM_SET_INTEN(base, subModuleNum, eventmask & (kFlexPwmFault0Event - 1));
    /* Check if we should enable Fault interrupts which are in a different register */
    if ((eventmask >> 16) & PWM_FCTRL_FIE_MASK)
    {
        PWM_SET_FCTRL(base, (eventmask >> 16) & PWM_FCTRL_FIE_MASK);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_HAL_DisableInterrupts
 * Description   : Disables all PWM interrupts
 * User can pass in an OR'ed list of PWM interrupts to disable. The list of available PWM interrupts
 * is available in the enum pwm_event_t
 *
 *END**************************************************************************/
void PWM_HAL_DisableInterrupts(PWM_Type *base, pwm_module_t subModuleNum, uint32_t eventmask)
{
    PWM_CLR_INTEN(base, subModuleNum, eventmask & (kFlexPwmFault0Event - 1));
    /* Check if we should disable Fault interrupts which are in a different register */
    if ((eventmask >> 16) & PWM_FCTRL_FIE_MASK)
    {
        PWM_CLR_FCTRL(base, (eventmask >> 16) & PWM_FCTRL_FIE_MASK);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PWM_HAL_ClearStatus
 * Description   : Clear all PWM status flags
 * User can pass in an OR'ed list of status flags to clear. The list of available PWM interrupts
 * is available in the enum pwm_event_t
 *
 *END**************************************************************************/
void PWM_HAL_ClearStatus(PWM_Type *base, pwm_module_t subModuleNum, uint32_t eventmask)
{
    PWM_SET_STS(base, subModuleNum, eventmask & (kFlexPwmFault0Event - 1));
    /* Check if we should clear Fault status flags which are in a different register */
    if ((eventmask >> 16) & PWM_FSTS_FFLAG_MASK)
    {
        PWM_SET_FSTS(base, (eventmask >> 16) & PWM_FSTS_FFLAG_MASK);
    }
}

#endif /* FSL_FEATURE_SOC_PWM_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/

