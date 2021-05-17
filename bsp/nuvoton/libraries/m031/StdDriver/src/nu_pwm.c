/**************************************************************************//**
 * @file     pwm.c
 * @version  V1.00
 * $Revision: 4 $
 * $Date: 18/04/25 11:43a $
 * @brief    M031 series PWM driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup PWM_Driver PWM Driver
  @{
*/


/** @addtogroup PWM_EXPORTED_FUNCTIONS PWM Exported Functions
  @{
*/

/**
 * @brief Configure PWM capture and get the nearest unit time.
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32UnitTimeNsec The unit time of counter
 * @param[in] u32CaptureEdge The condition to latch the counter. This parameter is not used
 * @return The nearest unit time in nano second.
 * @details This function is used to Configure PWM capture and get the nearest unit time.
 */
uint32_t PWM_ConfigCaptureChannel(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32UnitTimeNsec, uint32_t u32CaptureEdge)
{
    uint32_t u32Src;
    uint32_t u32PWMClockSrc;
    uint32_t u32NearestUnitTimeNsec;
    uint16_t u16Prescale = 1UL, u16CNR = 0xFFFFUL;
    uint8_t u8BreakLoop = 0UL;

    if (pwm == PWM0)
        u32Src = CLK->CLKSEL2 & CLK_CLKSEL2_PWM0SEL_Msk;
    else//(pwm == PWM1)
        u32Src = CLK->CLKSEL2 & CLK_CLKSEL2_PWM1SEL_Msk;

    if (u32Src == 0UL)
    {
        //clock source is from PLL clock
        u32PWMClockSrc = CLK_GetPLLClockFreq();
    }
    else
    {
        //clock source is from PCLK
        SystemCoreClockUpdate();

        if (pwm == PWM0)
        {
            u32PWMClockSrc = CLK_GetPCLK0Freq();
        }
        else     /* (pwm == PWM1) */
        {
            u32PWMClockSrc = CLK_GetPCLK1Freq();
        }
    }

    u32PWMClockSrc /= 1000UL;

    for (u16Prescale = 1UL; u16Prescale <= 0x1000UL; u16Prescale++)
    {
        u32NearestUnitTimeNsec = (1000000UL * u16Prescale) / u32PWMClockSrc;

        if (u32NearestUnitTimeNsec < u32UnitTimeNsec)
        {
            if (u16Prescale == 0x1000UL)
            {
                /* limit to the maximum unit time(nano second) */
                u8BreakLoop = 1UL;
            }

            if (!((1000000UL * (u16Prescale + 1UL) > (u32NearestUnitTimeNsec * u32PWMClockSrc))))
            {
                u8BreakLoop = 1UL;
            }
        }
        else
        {
            u8BreakLoop = 1UL;
        }

        if (u8BreakLoop)
        {
            break;
        }
    }

    // convert to real register value
    u16Prescale = u16Prescale - 1UL;
    // every two channels share a prescaler
    PWM_SET_PRESCALER(pwm, u32ChannelNum, (uint32_t)u16Prescale);

    // set PWM to down count type(edge aligned)
    (pwm)->CTL1 = ((pwm)->CTL1 & ~(PWM_CTL1_CNTTYPE0_Msk << ((u32ChannelNum >> 1UL) << 2UL))) | (1UL << ((u32ChannelNum >> 1UL) << 2UL));

    PWM_SET_CNR(pwm, u32ChannelNum, u16CNR);

    return (u32NearestUnitTimeNsec);
}

/**
 * @brief This function Configure PWM generator and get the nearest frequency in edge aligned auto-reload mode
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32Frequency Target generator frequency
 * @param[in] u32DutyCycle Target generator duty cycle percentage. Valid range are between 0 ~ 100. 10 means 10%, 20 means 20%...
 * @return Nearest frequency clock in nano second
 * @note Since every two channels, (0 & 1), (2 & 3), shares a prescaler. Call this API to configure PWM frequency may affect
 *       existing frequency of other channel.
 */
uint32_t PWM_ConfigOutputChannel(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Frequency, uint32_t u32DutyCycle)
{
    uint32_t u32Src;
    uint32_t u32PWMClockSrc;
    uint32_t i;
    uint16_t u16Prescale = 1UL, u16CNR = 0xFFFFUL;

    if (pwm == PWM0)
        u32Src = CLK->CLKSEL2 & CLK_CLKSEL2_PWM0SEL_Msk;
    else//(pwm == PWM1)
        u32Src = CLK->CLKSEL2 & CLK_CLKSEL2_PWM1SEL_Msk;

    if (u32Src == 0UL)
    {
        //clock source is from PLL clock
        u32PWMClockSrc = CLK_GetPLLClockFreq();
    }
    else
    {
        //clock source is from PCLK
        SystemCoreClockUpdate();

        if (pwm == PWM0)
        {
            u32PWMClockSrc = CLK_GetPCLK0Freq();
        }
        else     /* (pwm == PWM1) */
        {
            u32PWMClockSrc = CLK_GetPCLK1Freq();
        }
    }

    for (u16Prescale = 1UL; u16Prescale < 0xFFFUL; u16Prescale++)   //prescale could be 0~0xFFF
    {
        i = (u32PWMClockSrc / u32Frequency) / u16Prescale;

        // If target value is larger than CNR, need to use a larger prescaler
        if (i <= (0x10000UL))
        {
            u16CNR = (uint16_t)i;
            break;
        }
    }

    // Store return value here 'cos we're gonna change u16Prescale & u16CNR to the real value to fill into register
    i = u32PWMClockSrc / ((uint32_t)u16Prescale * (uint32_t)u16CNR);

    // convert to real register value
    u16Prescale = u16Prescale - 1UL;
    // every two channels share a prescaler
    PWM_SET_PRESCALER(pwm, u32ChannelNum, (uint32_t)u16Prescale);
    // set PWM to down count type(edge aligned)
    (pwm)->CTL1 = ((pwm)->CTL1 & ~(PWM_CTL1_CNTTYPE0_Msk << ((u32ChannelNum >> 1UL) << 2UL))) | (1UL << ((u32ChannelNum >> 1UL) << 2UL));

    u16CNR -= 1UL;
    PWM_SET_CNR(pwm, u32ChannelNum, u16CNR);

    if (u32DutyCycle)
    {
        if (u32DutyCycle >= 100UL)
            PWM_SET_CMR(pwm, u32ChannelNum, u16CNR);
        else
            PWM_SET_CMR(pwm, u32ChannelNum, u32DutyCycle * (u16CNR + 1UL) / 100UL);

        (pwm)->WGCTL0 &= ~((PWM_WGCTL0_PRDPCTL0_Msk | PWM_WGCTL0_ZPCTL0_Msk) << (u32ChannelNum << 1UL));
        (pwm)->WGCTL0 |= (PWM_OUTPUT_LOW << ((u32ChannelNum << 1UL) + PWM_WGCTL0_PRDPCTL0_Pos));
        (pwm)->WGCTL1 &= ~((PWM_WGCTL1_CMPDCTL0_Msk | PWM_WGCTL1_CMPUCTL0_Msk) << (u32ChannelNum << 1UL));
        (pwm)->WGCTL1 |= (PWM_OUTPUT_HIGH << ((u32ChannelNum << 1UL) + PWM_WGCTL1_CMPDCTL0_Pos));
    }
    else
    {
        PWM_SET_CMR(pwm, u32ChannelNum, 0UL);
        (pwm)->WGCTL0 &= ~((PWM_WGCTL0_PRDPCTL0_Msk | PWM_WGCTL0_ZPCTL0_Msk) << (u32ChannelNum << 1UL));
        (pwm)->WGCTL0 |= (PWM_OUTPUT_LOW << ((u32ChannelNum << 1UL) + PWM_WGCTL0_ZPCTL0_Pos));
        (pwm)->WGCTL1 &= ~((PWM_WGCTL1_CMPDCTL0_Msk | PWM_WGCTL1_CMPUCTL0_Msk) << (u32ChannelNum << 1UL));
        (pwm)->WGCTL1 |= (PWM_OUTPUT_HIGH << ((u32ChannelNum << 1UL) + PWM_WGCTL1_CMPDCTL0_Pos));
    }

    return (i);
}

/**
 * @brief Start PWM module
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to start PWM module.
 * @note Every two channels share the same setting.
 */
void PWM_Start(PWM_T *pwm, uint32_t u32ChannelMask)
{
    uint32_t i;

    for (i = 0UL; i < PWM_CHANNEL_NUM; i ++)
    {
        if (u32ChannelMask & (1UL << i))
        {
            (pwm)->CNTEN |= (1UL << ((i >> 1UL) << 1UL));
        }
    }
}

/**
 * @brief Stop PWM module
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to stop PWM module.
 * @note Every two channels share the same setting.
 */
void PWM_Stop(PWM_T *pwm, uint32_t u32ChannelMask)
{
    uint32_t i;

    for (i = 0UL; i < PWM_CHANNEL_NUM; i ++)
    {
        if (u32ChannelMask & (1UL << i))
        {
            (pwm)->PERIOD[((i >> 1UL) << 1UL)] = 0UL;
        }
    }
}

/**
 * @brief Stop PWM generation immediately by clear channel enable bit
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to stop PWM generation immediately by clear channel enable bit.
 * @note Every two channels share the same setting.
 */
void PWM_ForceStop(PWM_T *pwm, uint32_t u32ChannelMask)
{
    uint32_t i;

    for (i = 0UL; i < PWM_CHANNEL_NUM; i ++)
    {
        if (u32ChannelMask & (1UL << i))
        {
            (pwm)->CNTEN &= ~(1UL << ((i >> 1UL) << 1UL));
        }
    }
}

/**
 * @brief Enable selected channel to trigger ADC
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32Condition The condition to trigger ADC. Combination of following conditions:
 *                  - \ref PWM_TRIGGER_ADC_EVEN_ZERO_POINT
 *                  - \ref PWM_TRIGGER_ADC_EVEN_PERIOD_POINT
 *                  - \ref PWM_TRIGGER_ADC_EVEN_ZERO_OR_PERIOD_POINT
 *                  - \ref PWM_TRIGGER_ADC_EVEN_COMPARE_UP_COUNT_POINT
 *                  - \ref PWM_TRIGGER_ADC_EVEN_COMPARE_DOWN_COUNT_POINT
 *                  - \ref PWM_TRIGGER_ADC_ODD_COMPARE_UP_COUNT_POINT
 *                  - \ref PWM_TRIGGER_ADC_ODD_COMPARE_DOWN_COUNT_POINT
 * @return None
 * @details This function is used to enable selected channel to trigger ADC.
 */
void PWM_EnableADCTrigger(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Condition)
{
    if (u32ChannelNum < 4UL)
    {
        (pwm)->ADCTS0 &= ~((PWM_ADCTS0_TRGSEL0_Msk) << (u32ChannelNum << 3UL));
        (pwm)->ADCTS0 |= ((PWM_ADCTS0_TRGEN0_Msk | u32Condition) << (u32ChannelNum << 3UL));
    }
    else
    {
        (pwm)->ADCTS1 &= ~((PWM_ADCTS1_TRGSEL4_Msk) << ((u32ChannelNum - 4UL) << 3UL));
        (pwm)->ADCTS1 |= ((PWM_ADCTS1_TRGEN4_Msk | u32Condition) << ((u32ChannelNum - 4UL) << 3UL));
    }
}

/**
 * @brief Disable selected channel to trigger ADC
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to disable selected channel to trigger ADC.
 */
void PWM_DisableADCTrigger(PWM_T *pwm, uint32_t u32ChannelNum)
{
    if (u32ChannelNum < 4UL)
    {
        (pwm)->ADCTS0 &= ~(PWM_ADCTS0_TRGEN0_Msk << (u32ChannelNum << 3UL));
    }
    else
    {
        (pwm)->ADCTS1 &= ~(PWM_ADCTS1_TRGEN4_Msk << ((u32ChannelNum - 4UL) << 3UL));
    }
}

/**
 * @brief Clear selected channel trigger ADC flag
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32Condition This parameter is not used
 * @return None
 * @details This function is used to clear selected channel trigger ADC flag.
 */
void PWM_ClearADCTriggerFlag(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Condition)
{
    (pwm)->STATUS = (PWM_STATUS_ADCTRG0_Msk << u32ChannelNum);
}

/**
 * @brief Get selected channel trigger ADC flag
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @retval 0 The specified channel trigger ADC to start of conversion flag is not set
 * @retval 1 The specified channel trigger ADC to start of conversion flag is set
 * @details This function is used to get PWM trigger ADC to start of conversion flag for specified channel.
 */
uint32_t PWM_GetADCTriggerFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    return (((pwm)->STATUS & (PWM_STATUS_ADCTRG0_Msk << u32ChannelNum)) ? 1UL : 0UL);
}

/**
 * @brief This function enable fault brake of selected channel(s)
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 * @param[in] u32LevelMask Output high or low while fault brake occurs, each bit represent the level of a channel
 *                         while fault brake occurs. Bit 0 represents channel 0, bit 1 represents channel 1...
 * @param[in] u32BrakeSource Fault brake source, could be one of following source
 *                  - \ref PWM_FB_EDGE_ACMP0
 *                  - \ref PWM_FB_EDGE_ACMP1
 *                  - \ref PWM_FB_EDGE_BKP0
 *                  - \ref PWM_FB_EDGE_BKP1
 *                  - \ref PWM_FB_EDGE_SYS_CSS
 *                  - \ref PWM_FB_EDGE_SYS_BOD
 *                  - \ref PWM_FB_EDGE_SYS_COR
 *                  - \ref PWM_FB_LEVEL_ACMP0
 *                  - \ref PWM_FB_LEVEL_ACMP1
 *                  - \ref PWM_FB_LEVEL_BKP0
 *                  - \ref PWM_FB_LEVEL_BKP1
 *                  - \ref PWM_FB_LEVEL_SYS_CSS
 *                  - \ref PWM_FB_LEVEL_SYS_BOD
 *                  - \ref PWM_FB_LEVEL_SYS_COR
 * @return None
 * @details This function is used to enable fault brake of selected channel(s).
 *          The write-protection function should be disabled before using this function.
 */
void PWM_EnableFaultBrake(PWM_T *pwm, uint32_t u32ChannelMask, uint32_t u32LevelMask, uint32_t u32BrakeSource)
{
    uint32_t i;

    for (i = 0UL; i < PWM_CHANNEL_NUM; i ++)
    {
        if (u32ChannelMask & (1UL << i))
        {
            if ((u32BrakeSource == PWM_FB_EDGE_SYS_CSS) || (u32BrakeSource == PWM_FB_EDGE_SYS_BOD) || \
                    (u32BrakeSource == PWM_FB_EDGE_SYS_COR) || \
                    (u32BrakeSource == PWM_FB_LEVEL_SYS_CSS) || (u32BrakeSource == PWM_FB_LEVEL_SYS_BOD) || \
                    (u32BrakeSource == PWM_FB_LEVEL_SYS_COR))
            {
                (pwm)->BRKCTL[i >> 1UL] |= (u32BrakeSource & (PWM_BRKCTL_SYSEBEN_Msk | PWM_BRKCTL_SYSLBEN_Msk));
                (pwm)->FAILBRK |= (u32BrakeSource & 0xBUL);
            }
            else
            {
                (pwm)->BRKCTL[i >> 1UL] |= u32BrakeSource;
            }
        }

        if (u32LevelMask & (1UL << i))
        {
            if ((i & 0x1UL) == 0UL)
            {
                //set brake action as high level for even channel
                (pwm)->BRKCTL[i >> 1UL] &= ~PWM_BRKCTL0_1_BRKAEVEN_Msk;
                (pwm)->BRKCTL[i >> 1UL] |= ((3UL) << PWM_BRKCTL0_1_BRKAEVEN_Pos);
            }
            else
            {
                //set brake action as high level for odd channel
                (pwm)->BRKCTL[i >> 1UL] &= ~PWM_BRKCTL0_1_BRKAODD_Msk;
                (pwm)->BRKCTL[i >> 1UL] |= ((3UL) << PWM_BRKCTL0_1_BRKAODD_Pos);
            }
        }
        else
        {
            if ((i & 0x1UL) == 0UL)
            {
                //set brake action as low level for even channel
                (pwm)->BRKCTL[i >> 1UL] &= ~PWM_BRKCTL0_1_BRKAEVEN_Msk;
                (pwm)->BRKCTL[i >> 1UL] |= ((2UL) << PWM_BRKCTL0_1_BRKAEVEN_Pos);
            }
            else
            {
                //set brake action as low level for odd channel
                (pwm)->BRKCTL[i >> 1UL] &= ~PWM_BRKCTL0_1_BRKAODD_Msk;
                (pwm)->BRKCTL[i >> 1UL] |= ((2UL) << PWM_BRKCTL0_1_BRKAODD_Pos);
            }
        }
    }

}

/**
 * @brief Enable capture of selected channel(s)
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to enable capture of selected channel(s).
 */
void PWM_EnableCapture(PWM_T *pwm, uint32_t u32ChannelMask)
{
    (pwm)->CAPINEN |= u32ChannelMask;
    (pwm)->CAPCTL |= u32ChannelMask;
}

/**
 * @brief Disable capture of selected channel(s)
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to disable capture of selected channel(s).
 */
void PWM_DisableCapture(PWM_T *pwm, uint32_t u32ChannelMask)
{
    (pwm)->CAPINEN &= ~u32ChannelMask;
    (pwm)->CAPCTL &= ~u32ChannelMask;
}

/**
 * @brief Enables PWM output generation of selected channel(s)
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Set bit 0 to 1 enables channel 0 output, set bit 1 to 1 enables channel 1 output...
 * @return None
 * @details This function is used to enable PWM output generation of selected channel(s).
 */
void PWM_EnableOutput(PWM_T *pwm, uint32_t u32ChannelMask)
{
    (pwm)->POEN |= u32ChannelMask;
}

/**
 * @brief Disables PWM output generation of selected channel(s)
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Set bit 0 to 1 disables channel 0 output, set bit 1 to 1 disables channel 1 output...
 * @return None
 * @details This function is used to disable PWM output generation of selected channel(s).
 */
void PWM_DisableOutput(PWM_T *pwm, uint32_t u32ChannelMask)
{
    (pwm)->POEN &= ~u32ChannelMask;
}

/**
 * @brief Enable Dead zone of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32Duration Dead zone length in PWM clock count, valid values are between 0~0xFFF, but 0 means there is no Dead zone.
 * @return None
 * @details This function is used to enable Dead zone of selected channel.
 *          The write-protection function should be disabled before using this function.
 * @note Every two channels share the same setting.
 */
void PWM_EnableDeadZone(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Duration)
{
    // every two channels share the same setting
    (pwm)->DTCTL[(u32ChannelNum) >> 1UL] &= ~PWM_DTCTL0_1_DTCNT_Msk;
    (pwm)->DTCTL[(u32ChannelNum) >> 1UL] |= PWM_DTCTL0_1_DTEN_Msk | u32Duration;
}

/**
 * @brief Disable Dead zone of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to disable Dead zone of selected channel.
 *          The write-protection function should be disabled before using this function.
 */
void PWM_DisableDeadZone(PWM_T *pwm, uint32_t u32ChannelNum)
{
    // every two channels shares the same setting
    (pwm)->DTCTL[(u32ChannelNum) >> 1UL] &= ~PWM_DTCTL0_1_DTEN_Msk;
}

/**
 * @brief Enable capture interrupt of selected channel.
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32Edge Rising or falling edge to latch counter.
 *              - \ref PWM_CAPTURE_INT_RISING_LATCH
 *              - \ref PWM_CAPTURE_INT_FALLING_LATCH
 * @return None
 * @details This function is used to enable capture interrupt of selected channel.
 */
void PWM_EnableCaptureInt(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge)
{
    (pwm)->CAPIEN |= (u32Edge << u32ChannelNum);
}

/**
 * @brief Disable capture interrupt of selected channel.
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32Edge Rising or falling edge to latch counter.
 *              - \ref PWM_CAPTURE_INT_RISING_LATCH
 *              - \ref PWM_CAPTURE_INT_FALLING_LATCH
 * @return None
 * @details This function is used to disable capture interrupt of selected channel.
 */
void PWM_DisableCaptureInt(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge)
{
    (pwm)->CAPIEN &= ~(u32Edge << u32ChannelNum);
}

/**
 * @brief Clear capture interrupt of selected channel.
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32Edge Rising or falling edge to latch counter.
 *              - \ref PWM_CAPTURE_INT_RISING_LATCH
 *              - \ref PWM_CAPTURE_INT_FALLING_LATCH
 * @return None
 * @details This function is used to clear capture interrupt of selected channel.
 */
void PWM_ClearCaptureIntFlag(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge)
{
    (pwm)->CAPIF = (u32Edge << u32ChannelNum);
}

/**
 * @brief Get capture interrupt of selected channel.
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @retval 0 No capture interrupt
 * @retval 1 Rising edge latch interrupt
 * @retval 2 Falling edge latch interrupt
 * @retval 3 Rising and falling latch interrupt
 * @details This function is used to get capture interrupt of selected channel.
 */
uint32_t PWM_GetCaptureIntFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    uint32_t u32CapFFlag, u32CapRFlag ;
    u32CapFFlag = (((pwm)->CAPIF & (PWM_CAPIF_CFLIF0_Msk << u32ChannelNum)) ? 1UL : 0UL) ;
    u32CapRFlag = (((pwm)->CAPIF & (PWM_CAPIF_CRLIF0_Msk << u32ChannelNum)) ? 1UL : 0UL) ;
    return ((u32CapFFlag << 1UL) | u32CapRFlag);
}
/**
 * @brief Enable duty interrupt of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32IntDutyType Duty interrupt type, could be either
 *              - \ref PWM_DUTY_INT_DOWN_COUNT_MATCH_CMP
 *              - \ref PWM_DUTY_INT_UP_COUNT_MATCH_CMP
 * @return None
 * @details This function is used to enable duty interrupt of selected channel.
 */
void PWM_EnableDutyInt(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32IntDutyType)
{
    (pwm)->INTEN0 |= (u32IntDutyType << u32ChannelNum);
}

/**
 * @brief Disable duty interrupt of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to disable duty interrupt of selected channel.
 */
void PWM_DisableDutyInt(PWM_T *pwm, uint32_t u32ChannelNum)
{
    (pwm)->INTEN0 &= ~((PWM_DUTY_INT_DOWN_COUNT_MATCH_CMP | PWM_DUTY_INT_UP_COUNT_MATCH_CMP) << u32ChannelNum);
}

/**
 * @brief Clear duty interrupt flag of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to clear duty interrupt flag of selected channel.
 */
void PWM_ClearDutyIntFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    (pwm)->INTSTS0 = (PWM_INTSTS0_CMPUIF0_Msk | PWM_INTSTS0_CMPDIF0_Msk) << u32ChannelNum;
}

/**
 * @brief Get duty interrupt flag of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return Duty interrupt flag of specified channel
 * @retval 0 Duty interrupt did not occur
 * @retval 1 Duty interrupt occurred
 * @details This function is used to get duty interrupt flag of selected channel.
 */
uint32_t PWM_GetDutyIntFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    return ((((pwm)->INTSTS0 & ((PWM_INTSTS0_CMPDIF0_Msk | PWM_INTSTS0_CMPUIF0_Msk) << u32ChannelNum))) ? 1 : 0);
}

/**
 * @brief Enable load mode of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32LoadMode PWM counter loading mode.
 *              - \ref PWM_LOAD_MODE_IMMEDIATE
 *              - \ref PWM_LOAD_MODE_CENTER
 * @return None
 * @details This function is used to enable load mode of selected channel.
 */
void PWM_EnableLoadMode(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32LoadMode)
{
    (pwm)->CTL0 |= (u32LoadMode << u32ChannelNum);
}

/**
 * @brief Disable load mode of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32LoadMode PWM counter loading mode.
 *              - \ref PWM_LOAD_MODE_IMMEDIATE
 *              - \ref PWM_LOAD_MODE_CENTER
 * @return None
 * @details This function is used to disable load mode of selected channel.
 */
void PWM_DisableLoadMode(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32LoadMode)
{
    (pwm)->CTL0 &= ~(u32LoadMode << u32ChannelNum);
}

/**
 * @brief This function enable fault brake interrupt
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32BrakeSource Fault brake source.
 *              - \ref PWM_FB_EDGE
 *              - \ref PWM_FB_LEVEL
 * @return None
 * @details This function is used to enable fault brake interrupt.
 *          The write-protection function should be disabled before using this function.
 * @note Every two channels share the same setting.
 */
void PWM_EnableFaultBrakeInt(PWM_T *pwm, uint32_t u32BrakeSource)
{
    (pwm)->INTEN1 |= (0x7UL << u32BrakeSource);
}

/**
 * @brief This function disable fault brake interrupt
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32BrakeSource Fault brake source.
 *              - \ref PWM_FB_EDGE
 *              - \ref PWM_FB_LEVEL
 * @return None
 * @details This function is used to disable fault brake interrupt.
 *          The write-protection function should be disabled before using this function.
 * @note Every two channels share the same setting.
 */
void PWM_DisableFaultBrakeInt(PWM_T *pwm, uint32_t u32BrakeSource)
{
    (pwm)->INTEN1 &= ~(0x7UL << u32BrakeSource);
}

/**
 * @brief This function clear fault brake interrupt of selected source
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32BrakeSource Fault brake source.
 *              - \ref PWM_FB_EDGE
 *              - \ref PWM_FB_LEVEL
 * @return None
 * @details This function is used to clear fault brake interrupt of selected source.
 *          The write-protection function should be disabled before using this function.
 */
void PWM_ClearFaultBrakeIntFlag(PWM_T *pwm, uint32_t u32BrakeSource)
{
    (pwm)->INTSTS1 = (0x3fUL << u32BrakeSource);
}

/**
 * @brief This function get fault brake interrupt flag of selected source
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32BrakeSource Fault brake source, could be either
 *              - \ref PWM_FB_EDGE
 *              - \ref PWM_FB_LEVEL
 * @return Fault brake interrupt flag of specified source
 * @retval 0 Fault brake interrupt did not occurred
 * @retval 1 Fault brake interrupt occurred
 * @details This function is used to get fault brake interrupt flag of selected source.
 */
uint32_t PWM_GetFaultBrakeIntFlag(PWM_T *pwm, uint32_t u32BrakeSource)
{
    return (((pwm)->INTSTS1 & (0x3fUL << u32BrakeSource)) ? 1UL : 0UL);
}

/**
 * @brief Enable period interrupt of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5. Every two channels share the same setting.
 * @param[in] u32IntPeriodType Period interrupt type. This parameter is not used.
 * @return None
 * @details This function is used to enable period interrupt of selected channel.
 */
void PWM_EnablePeriodInt(PWM_T *pwm, uint32_t u32ChannelNum,  uint32_t u32IntPeriodType)
{
    (pwm)->INTEN0 |= (PWM_INTEN0_PIEN0_Msk << ((u32ChannelNum >> 1UL) << 1UL));
}

/**
 * @brief Disable period interrupt of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5. Every two channels share the same setting.
 * @return None
 * @details This function is used to disable period interrupt of selected channel.
 */
void PWM_DisablePeriodInt(PWM_T *pwm, uint32_t u32ChannelNum)
{
    (pwm)->INTEN0 &= ~(PWM_INTEN0_PIEN0_Msk << ((u32ChannelNum >> 1UL) << 1UL));
}

/**
 * @brief Clear period interrupt of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5. Every two channels share the same setting.
 * @return None
 * @details This function is used to clear period interrupt of selected channel.
 */
void PWM_ClearPeriodIntFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    (pwm)->INTSTS0 = (PWM_INTSTS0_PIF0_Msk << ((u32ChannelNum >> 1UL) << 1UL));
}

/**
 * @brief Get period interrupt of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5. Every two channels share the same setting.
 * @return Period interrupt flag of specified channel
 * @retval 0 Period interrupt did not occur
 * @retval 1 Period interrupt occurred
 * @details This function is used to get period interrupt of selected channel.
 */
uint32_t PWM_GetPeriodIntFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    return (((pwm)->INTSTS0 & (PWM_INTSTS0_PIF0_Msk << ((u32ChannelNum >> 1UL) << 1UL))) ? 1UL : 0UL);
}

/**
 * @brief Enable zero interrupt of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5. Every two channels share the same setting.
 * @return None
 * @details This function is used to enable zero interrupt of selected channel.
 */
void PWM_EnableZeroInt(PWM_T *pwm, uint32_t u32ChannelNum)
{
    (pwm)->INTEN0 |= (PWM_INTEN0_ZIEN0_Msk << ((u32ChannelNum >> 1UL) << 1UL));
}

/**
 * @brief Disable zero interrupt of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5. Every two channels share the same setting.
 * @return None
 * @details This function is used to disable zero interrupt of selected channel.
 */
void PWM_DisableZeroInt(PWM_T *pwm, uint32_t u32ChannelNum)
{
    (pwm)->INTEN0 &= ~(PWM_INTEN0_ZIEN0_Msk << ((u32ChannelNum >> 1UL) << 1UL));
}

/**
 * @brief Clear zero interrupt of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5. Every two channels share the same setting.
 * @return None
 * @details This function is used to clear zero interrupt of selected channel.
 */
void PWM_ClearZeroIntFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    (pwm)->INTSTS0 = (PWM_INTSTS0_ZIF0_Msk << ((u32ChannelNum >> 1UL) << 1UL));
}

/**
 * @brief Get zero interrupt of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5. Every two channels share the same setting.
 * @return zero interrupt flag of specified channel
 * @retval 0 zero interrupt did not occur
 * @retval 1 zero interrupt occurred
 * @details This function is used to get zero interrupt of selected channel.
 */
uint32_t PWM_GetZeroIntFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    return (((pwm)->INTSTS0 & (PWM_INTSTS0_ZIF0_Msk << ((u32ChannelNum >> 1UL) << 1UL))) ? 1UL : 0UL);
}

/**
 * @brief Set PWM clock source
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32ClkSrcSel PWM external clock source.
 *              - \ref PWM_CLKSRC_PWM_CLK
 *              - \ref PWM_CLKSRC_TIMER0
 *              - \ref PWM_CLKSRC_TIMER1
 *              - \ref PWM_CLKSRC_TIMER2
 *              - \ref PWM_CLKSRC_TIMER3
 * @return None
 * @details This function is used to set PWM clock source.
 * @note Every two channels share the same setting.
 */
void PWM_SetClockSource(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32ClkSrcSel)
{
    (pwm)->CLKSRC = ((pwm)->CLKSRC & ~(PWM_CLKSRC_ECLKSRC0_Msk << ((u32ChannelNum >> 1UL) * PWM_CLKSRC_ECLKSRC2_Pos))) | \
                    (u32ClkSrcSel << ((u32ChannelNum >> 1UL) * PWM_CLKSRC_ECLKSRC2_Pos));
}

/**
 * @brief Enable PWM brake noise filter function
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32BrakePinNum Brake pin selection. Valid values are 0 or 1.
 * @param[in] u32ClkCnt SYNC Edge Detector Filter Count. This controls the counter number of edge detector
 * @param[in] u32ClkDivSel SYNC Edge Detector Filter Clock Selection.
 *              - \ref PWM_NF_CLK_DIV_1
 *              - \ref PWM_NF_CLK_DIV_2
 *              - \ref PWM_NF_CLK_DIV_4
 *              - \ref PWM_NF_CLK_DIV_8
 *              - \ref PWM_NF_CLK_DIV_16
 *              - \ref PWM_NF_CLK_DIV_32
 *              - \ref PWM_NF_CLK_DIV_64
 *              - \ref PWM_NF_CLK_DIV_128
 * @return None
 * @details This function is used to enable PWM brake noise filter function.
 */
void PWM_EnableBrakeNoiseFilter(PWM_T *pwm, uint32_t u32BrakePinNum, uint32_t u32ClkCnt, uint32_t u32ClkDivSel)
{
    (pwm)->BNF = ((pwm)->BNF & ~((PWM_BNF_BRK0FCNT_Msk | PWM_BNF_BRK0NFSEL_Msk) << (u32BrakePinNum * PWM_BNF_BRK1NFEN_Pos))) | \
                 (((u32ClkCnt << PWM_BNF_BRK0FCNT_Pos) | (u32ClkDivSel << PWM_BNF_BRK0NFSEL_Pos) | PWM_BNF_BRK0NFEN_Msk) << (u32BrakePinNum * PWM_BNF_BRK1NFEN_Pos));
}

/**
 * @brief Disable PWM brake noise filter function
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32BrakePinNum Brake pin selection. Valid values are 0 or 1.
 * @return None
 * @details This function is used to disable PWM brake noise filter function.
 */
void PWM_DisableBrakeNoiseFilter(PWM_T *pwm, uint32_t u32BrakePinNum)
{
    (pwm)->BNF &= ~(PWM_BNF_BRK0NFEN_Msk << (u32BrakePinNum * PWM_BNF_BRK1NFEN_Pos));
}

/**
 * @brief Enable PWM brake pin inverse function
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32BrakePinNum Brake pin selection. Valid values are 0 or 1.
 * @return None
 * @details This function is used to enable PWM brake pin inverse function.
 */
void PWM_EnableBrakePinInverse(PWM_T *pwm, uint32_t u32BrakePinNum)
{
    (pwm)->BNF |= (PWM_BNF_BRK0PINV_Msk << (u32BrakePinNum * PWM_BNF_BRK1NFEN_Pos));
}

/**
 * @brief Disable PWM brake pin inverse function
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32BrakePinNum Brake pin selection. Valid values are 0 or 1.
 * @return None
 * @details This function is used to disable PWM brake pin inverse function.
 */
void PWM_DisableBrakePinInverse(PWM_T *pwm, uint32_t u32BrakePinNum)
{
    (pwm)->BNF &= ~(PWM_BNF_BRK0PINV_Msk << (u32BrakePinNum * PWM_BNF_BRK1NFEN_Pos));
}

/**
 * @brief Set PWM brake pin source
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32BrakePinNum Brake pin selection. Valid values are 0 or 1.
 * @param[in] u32SelAnotherModule Select to another module. Valid values are TRUE or FALSE.
 * @return None
 * @details This function is used to set PWM brake pin source.
 */
void PWM_SetBrakePinSource(PWM_T *pwm, uint32_t u32BrakePinNum, uint32_t u32SelAnotherModule)
{
    (pwm)->BNF = ((pwm)->BNF & ~(PWM_BNF_BK0SRC_Msk << (u32BrakePinNum << 3UL))) | (u32SelAnotherModule << (PWM_BNF_BK0SRC_Pos + (u32BrakePinNum << 3UL)));
}

/**
 * @brief Get the time-base counter reached its maximum value flag of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5. Every two channels share the same setting.
 * @return Count to max interrupt flag of specified channel
 * @retval 0 Count to max interrupt did not occur
 * @retval 1 Count to max interrupt occurred
 * @details This function is used to get the time-base counter reached its maximum value flag of selected channel.
 */
uint32_t PWM_GetWrapAroundFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    return (((pwm)->STATUS & (PWM_STATUS_CNTMAX0_Msk << ((u32ChannelNum >> 1UL) << 1UL))) ? 1UL : 0UL);
}

/**
 * @brief Clear the time-base counter reached its maximum value flag of selected channel
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5. Every two channels share the same setting.
 * @return None
 * @details This function is used to clear the time-base counter reached its maximum value flag of selected channel.
 */
void PWM_ClearWrapAroundFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    (pwm)->STATUS = (PWM_STATUS_CNTMAX0_Msk << ((u32ChannelNum >> 1UL) << 1UL));
}

/**
 * @brief Enables PDMA transfer of selected channel for PWM capture
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number.
 * @param[in] u32RisingFirst The capture order is rising, falling first. Every two channels share the same setting. Valid values are TRUE and FALSE.
 * @param[in] u32Mode Captured data transferred by PDMA interrupt type. It could be either
 *              - \ref PWM_CAPTURE_PDMA_RISING_LATCH
 *              - \ref PWM_CAPTURE_PDMA_FALLING_LATCH
 *              - \ref PWM_CAPTURE_PDMA_RISING_FALLING_LATCH
 * @return None
 * @details This function is used to enable PDMA transfer of selected channel(s) for PWM capture.
 * @note This function can only selects even or odd channel of pairs to do PDMA transfer.
 */
void PWM_EnablePDMA(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32RisingFirst, uint32_t u32Mode)
{
    uint32_t u32IsOddCh;
    u32IsOddCh = u32ChannelNum % 2UL;
    (pwm)->PDMACTL = ((pwm)->PDMACTL & ~((PWM_PDMACTL_CHSEL0_1_Msk | PWM_PDMACTL_CAPORD0_1_Msk | PWM_PDMACTL_CAPMOD0_1_Msk) << ((u32ChannelNum >> 1UL) << 3UL))) | \
                     (((u32IsOddCh << PWM_PDMACTL_CHSEL0_1_Pos) | (u32RisingFirst << PWM_PDMACTL_CAPORD0_1_Pos) | \
                       u32Mode | PWM_PDMACTL_CHEN0_1_Msk) << ((u32ChannelNum >> 1UL) << 3UL));
}

/**
 * @brief Disables PDMA transfer of selected channel for PWM capture
 * @param[in] pwm The pointer of the specified PWM module
 *                - PWM0 : PWM Group 0
 *                - PWM1 : PWM Group 1
 * @param[in] u32ChannelNum PWM channel number.
 * @return None
 * @details This function is used to enable PDMA transfer of selected channel(s) for PWM capture.
 */
void PWM_DisablePDMA(PWM_T *pwm, uint32_t u32ChannelNum)
{
    (pwm)->PDMACTL &= ~(PWM_PDMACTL_CHEN0_1_Msk << ((u32ChannelNum >> 1UL) << 3UL));
}

/*@}*/ /* end of group PWM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group PWM_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
