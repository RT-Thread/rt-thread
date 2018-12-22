/**************************************************************************//**
 * @file     pwm.c
 * @version  V3.00
 * $Revision: 14 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series PWM driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "M051Series.h"

/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_PWM_Driver PWM Driver
  @{
*/


/** @addtogroup M051_PWM_EXPORTED_FUNCTIONS PWM Exported Functions
  @{
*/

/**
 * @brief Config PWM capture and get the nearest unit time.
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32UnitTimeNsec The unit time of counter
 * @param[in] u32CaptureEdge The condition to latch the counter. This parameter is not used
 * @return The nearest unit time in nano second.
 * @details This function is used to config PWM capture and get the nearest unit time.
 */
uint32_t PWM_ConfigCaptureChannel(PWM_T *pwm,
                                  uint32_t u32ChannelNum,
                                  uint32_t u32UnitTimeNsec,
                                  uint32_t u32CaptureEdge)
{
    uint32_t u32Src;
    uint32_t u32PWMClockSrc;
    uint32_t u32PWMClkTbl[4] = {__HXT, __LIRC, 0, __HIRC};
    uint32_t u32NearestUnitTimeNsec;
    uint8_t  u8Divider = 1;
    /* this table is mapping divider value to register configuration */
    uint32_t u32PWMDividerToRegTbl[17] = {NULL, 4, 0, NULL, 1, NULL, NULL, NULL, 2, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 3};
    uint16_t u16Prescale = 2;
    uint16_t u16CNR = 0xFFFF;

    if(pwm == PWMA)
        u32Src = (CLK->CLKSEL1 & (CLK_CLKSEL1_PWM01_S_Msk << (u32ChannelNum >> 1))) >> (CLK_CLKSEL1_PWM01_S_Pos << (u32ChannelNum >> 1));
    else /*pwm == PWMB*/
        u32Src = (CLK->CLKSEL2 & (CLK_CLKSEL2_PWM45_S_Msk << (u32ChannelNum >> 1))) >> (CLK_CLKSEL2_PWM45_S_Pos << (u32ChannelNum >> 1));

    if(u32Src == 2)
    {
        SystemCoreClockUpdate();
        u32PWMClockSrc = SystemCoreClock;
    }
    else
    {
        u32PWMClockSrc = u32PWMClkTbl[u32Src];
    }

    u32PWMClockSrc /= 1000;
    for(; u16Prescale <= 0x100; u16Prescale++)
    {
        u32NearestUnitTimeNsec = (1000000 * u16Prescale * u8Divider) / u32PWMClockSrc;
        if(u32NearestUnitTimeNsec < u32UnitTimeNsec)
        {
            if((u16Prescale == 0x100) && (u8Divider == 16))  //limit to the maximum unit time(nano second)
                break;
            if(u16Prescale == 0x100)
            {
                u16Prescale = 2;
                u8Divider <<= 1; // clk divider could only be 1, 2, 4, 8, 16
                continue;
            }
            if(!((1000000  * ((u16Prescale * u8Divider) + 1)) > (u32NearestUnitTimeNsec * u32PWMClockSrc)))
                break;
            continue;
        }
        break;
    }

    // Store return value here 'cos we're gonna change u8Divider & u16Prescale & u16CNR to the real value to fill into register
    u16Prescale -= 1;

    // convert to real register value
    u8Divider = u32PWMDividerToRegTbl[u8Divider];

    // every two channels share a prescaler
    (pwm)->PPR = ((pwm)->PPR & ~(PWM_PPR_CP01_Msk << ((u32ChannelNum >> 1) * 8))) | (u16Prescale << ((u32ChannelNum >> 1) * 8));
    (pwm)->CSR = ((pwm)->CSR & ~(PWM_CSR_CSR0_Msk << (4 * u32ChannelNum))) | (u8Divider << (4 * u32ChannelNum));
    // set PWM to edge aligned type
    (pwm)->PCR &= ~(PWM_PCR_PWM01TYPE_Msk << (u32ChannelNum >> 1));
    (pwm)->PCR |= PWM_PCR_CH0MOD_Msk << (8 * u32ChannelNum);
    *((__IO uint32_t *)((((uint32_t) & ((pwm)->CNR0)) + (u32ChannelNum) * 12))) = u16CNR;

    return (u32NearestUnitTimeNsec);
}

/**
 * @brief This function config PWM generator and get the nearest frequency in edge aligned auto-reload mode
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32Frequency Target generator frequency
 * @param[in] u32DutyCycle Target generator duty cycle percentage. Valid range are between 0 ~ 100. 10 means 10%, 20 means 20%...
 * @return Nearest frequency clock in nano second
 * @note Since every two channels, (0 & 1), (2 & 3), shares a prescaler. Call this API to configure PWM frequency may affect
 *       existing frequency of other channel.
 */
uint32_t PWM_ConfigOutputChannel(PWM_T *pwm,
                                 uint32_t u32ChannelNum,
                                 uint32_t u32Frequency,
                                 uint32_t u32DutyCycle)
{
    uint32_t u32Src;
    uint32_t u32PWMClockSrc;
    uint32_t u32PWMClkTbl[4] = {__HXT, __LIRC, 0, __HIRC};
    uint32_t i;
    uint8_t  u8Divider = 1, u8Prescale = 0xFF;
    /* this table is mapping divider value to register configuration */
    uint32_t u32PWMDividerToRegTbl[17] = {NULL, 4, 0, NULL, 1, NULL, NULL, NULL, 2, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 3};
    uint16_t u16CNR = 0xFFFF;

    if(pwm == PWMA)
        u32Src = (CLK->CLKSEL1 & (CLK_CLKSEL1_PWM01_S_Msk << (u32ChannelNum >> 1))) >> (CLK_CLKSEL1_PWM01_S_Pos << (u32ChannelNum >> 1));
    else /*pwm == PWMB*/
        u32Src = (CLK->CLKSEL2 & (CLK_CLKSEL2_PWM45_S_Msk << (u32ChannelNum >> 1))) >> (CLK_CLKSEL2_PWM45_S_Pos << (u32ChannelNum >> 1));

    if(u32Src == 2)
    {
        SystemCoreClockUpdate();
        u32PWMClockSrc = SystemCoreClock;
    }
    else
    {
        u32PWMClockSrc = u32PWMClkTbl[u32Src];
    }

    for(; u8Divider < 17; u8Divider <<= 1)    // clk divider could only be 1, 2, 4, 8, 16
    {
        i = (u32PWMClockSrc / u32Frequency) / u8Divider;
        // If target value is larger than CNR * prescale, need to use a larger divider
        if(i > (0x10000 * 0x100))
            continue;

        // CNR = 0xFFFF + 1, get a prescaler that CNR value is below 0xFFFF
        u8Prescale = (i + 0xFFFF) / 0x10000;

        // u8Prescale must at least be 2, otherwise the output stop
        if(u8Prescale < 3)
            u8Prescale = 2;

        i /= u8Prescale;

        if(i <= 0x10000)
        {
            if(i == 1)
                u16CNR = 1;     // Too fast, and PWM cannot generate expected frequency...
            else
                u16CNR = i;
            break;
        }
    }
    // Store return value here 'cos we're gonna change u8Divider & u8Prescale & u16CNR to the real value to fill into register
    i = u32PWMClockSrc / (u8Prescale * u8Divider * u16CNR);

    u8Prescale -= 1;
    u16CNR -= 1;
    // convert to real register value
    u8Divider = u32PWMDividerToRegTbl[u8Divider];

    // every two channels share a prescaler
    (pwm)->PPR = ((pwm)->PPR & ~(PWM_PPR_CP01_Msk << ((u32ChannelNum >> 1) * 8))) | (u8Prescale << ((u32ChannelNum >> 1) * 8));
    (pwm)->CSR = ((pwm)->CSR & ~(PWM_CSR_CSR0_Msk << (4 * u32ChannelNum))) | (u8Divider << (4 * u32ChannelNum));
    // set PWM to edge aligned type
    (pwm)->PCR &= ~(PWM_PCR_PWM01TYPE_Msk << (u32ChannelNum >> 1));
    (pwm)->PCR |= PWM_PCR_CH0MOD_Msk << (8 * u32ChannelNum);
    *((__IO uint32_t *)((((uint32_t) & ((pwm)->CMR0)) + u32ChannelNum * 12))) = u32DutyCycle * (u16CNR + 1) / 100 - 1;
    *((__IO uint32_t *)((((uint32_t) & ((pwm)->CNR0)) + (u32ChannelNum) * 12))) = u16CNR;

    return(i);
}


/**
 * @brief Start PWM module
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to start PWM module
 */
void PWM_Start(PWM_T *pwm, uint32_t u32ChannelMask)
{
    uint32_t u32Mask = 0, i;
    for(i = 0; i < PWM_CHANNEL_NUM; i ++)
    {
        if(u32ChannelMask & (1 << i))
        {
            u32Mask |= (PWM_PCR_CH0EN_Msk << (i * 8));
        }
    }

    (pwm)->PCR |= u32Mask;
}

/**
 * @brief Stop PWM module
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to stop PWM module
 */
void PWM_Stop(PWM_T *pwm, uint32_t u32ChannelMask)
{
    uint32_t i;
    for(i = 0; i < PWM_CHANNEL_NUM; i ++)
    {
        if(u32ChannelMask & (1 << i))
        {
            *((__IO uint32_t *)((((uint32_t) & ((pwm)->CNR0)) + i * 12))) = 0;
        }
    }
}

/**
 * @brief Stop PWM generation immediately by clear channel enable bit
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to stop PWM generation immediately by clear channel enable bit
 */
void PWM_ForceStop(PWM_T *pwm, uint32_t u32ChannelMask)
{
    uint32_t u32Mask = 0, i;
    for(i = 0; i < PWM_CHANNEL_NUM; i ++)
    {
        if(u32ChannelMask & (1 << i))
        {
            u32Mask |= (PWM_PCR_CH0EN_Msk << (i * 8));
        }
    }

    (pwm)->PCR &= ~u32Mask;
}

/**
 * @brief Enable selected channel to trigger ADC
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32Condition The condition to trigger ADC. Combination of following conditions:
 *                  - \ref PWM_DUTY_TRIGGER_ADC
 *                  - \ref PWM_PERIOD_TRIGGER_ADC
 * @return None
 * @details This function is used to enable selected channel to trigger ADC
 */
void PWM_EnableADCTrigger(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Condition)
{
    (pwm)->TCON = ((pwm)->TCON & ~((PWM_DUTY_TRIGGER_ADC |
                                    PWM_PERIOD_TRIGGER_ADC) << u32ChannelNum)) | (u32Condition << u32ChannelNum);
}

/**
 * @brief Disable selected channel to trigger ADC
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return None
 * @details This function is used to disable selected channel to trigger ADC
 */
void PWM_DisableADCTrigger(PWM_T *pwm, uint32_t u32ChannelNum)
{
    (pwm)->TCON = ((pwm)->TCON & ~((PWM_DUTY_TRIGGER_ADC | PWM_PERIOD_TRIGGER_ADC) << u32ChannelNum));
}

/**
 * @brief Clear selected channel trigger ADC flag
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32Condition This parameter is not used
 * @return None
 * @details This function is used to clear selected channel trigger ADC flag
 */
void PWM_ClearADCTriggerFlag(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Condition)
{
    (pwm)->TSTATUS = (PWM_TSTATUS_PWM0TF_Msk << u32ChannelNum);
}

/**
 * @brief Get selected channel trigger ADC flag
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @retval 0 The specified channel trigger ADC to start of conversion flag is not set
 * @retval 1 The specified channel trigger ADC to start of conversion flag is set
 * @details This function is used to get PWM trigger ADC to start of conversion flag for specified channel
 */
uint32_t PWM_GetADCTriggerFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    return (((pwm)->TSTATUS & (PWM_TSTATUS_PWM0TF_Msk << (u32ChannelNum))) ? 1 : 0);
}

/**
 * @brief Enable capture of selected channel(s)
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to enable capture of selected channel(s)
 */
void PWM_EnableCapture(PWM_T *pwm, uint32_t u32ChannelMask)
{
    uint32_t i;
    for(i = 0; i < PWM_CHANNEL_NUM; i ++)
    {
        if(u32ChannelMask & (1 << i))
        {
            if(i < 2)
            {
                (pwm)->CCR0 |= PWM_CCR0_CAPCH0EN_Msk << (i * 16);
            }
            else
            {
                (pwm)->CCR2 |= PWM_CCR2_CAPCH2EN_Msk << ((i - 2) * 16);
            }
        }
    }
    (pwm)->CAPENR |= u32ChannelMask;
}

/**
 * @brief Disable capture of selected channel(s)
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to disable capture of selected channel(s)
 */
void PWM_DisableCapture(PWM_T *pwm, uint32_t u32ChannelMask)
{
    uint32_t i;
    for(i = 0; i < PWM_CHANNEL_NUM; i ++)
    {
        if(u32ChannelMask & (1 << i))
        {
            if(i < 2)
            {
                (pwm)->CCR0 &= ~(PWM_CCR0_CAPCH0EN_Msk << (i * 16));
            }
            else
            {
                (pwm)->CCR2 &= ~(PWM_CCR2_CAPCH2EN_Msk << ((i - 2) * 16));
            }
        }
    }
    (pwm)->CAPENR &= ~u32ChannelMask;
}

/**
 * @brief Enables PWM output generation of selected channel(s)
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Set bit 0 to 1 enables channel 0 output, set bit 1 to 1 enables channel 1 output...
 * @return None
 * @details This function is used to enables PWM output generation of selected channel(s)
 */
void PWM_EnableOutput(PWM_T *pwm, uint32_t u32ChannelMask)
{
    (pwm)->POE |= u32ChannelMask;
}

/**
 * @brief Disables PWM output generation of selected channel(s)
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Set bit 0 to 1 disables channel 0 output, set bit 1 to 1 disables channel 1 output...
 * @return None
 * @details This function is used to disables PWM output generation of selected channel(s)
 */
void PWM_DisableOutput(PWM_T *pwm, uint32_t u32ChannelMask)
{
    (pwm)->POE &= ~u32ChannelMask;
}

/**
 * @brief Enable Dead zone of selected channel
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32Duration Dead Zone length in PWM clock count, valid values are between 0~0xFF, but 0 means there is no
 *                        dead zone.
 * @return None
 * @details This function is used to enable Dead zone of selected channel
 */
void PWM_EnableDeadZone(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Duration)
{
    // every two channels shares the same setting
    u32ChannelNum >>= 1;
    // set duration
    (pwm)->PPR = ((pwm)->PPR & ~(PWM_PPR_DZI01_Msk << (8 * u32ChannelNum))) | (u32Duration << (PWM_PPR_DZI01_Pos + 8 * u32ChannelNum));
    // enable dead zone
    (pwm)->PCR |= (PWM_PCR_DZEN01_Msk << u32ChannelNum);
}

/**
 * @brief Disable Dead zone of selected channel
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return None
 * @details This function is used to disable Dead zone of selected channel
 */
void PWM_DisableDeadZone(PWM_T *pwm, uint32_t u32ChannelNum)
{
    // every two channels shares the same setting
    u32ChannelNum >>= 1;
    // enable dead zone
    (pwm)->PCR &= ~(PWM_PCR_DZEN01_Msk << u32ChannelNum);
}

/**
 * @brief Enable capture interrupt of selected channel.
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32Edge Rising or falling edge to latch counter.
 *              - \ref PWM_CAPTURE_INT_RISING_LATCH
 *              - \ref PWM_CAPTURE_INT_FALLING_LATCH
 * @return None
 * @details This function is used to enable capture interrupt of selected channel.
 */
void PWM_EnableCaptureInt(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge)
{
    if(u32ChannelNum < 2)
        (pwm)->CCR0 |= u32Edge << (u32ChannelNum * 16);
    else
        (pwm)->CCR2 |= u32Edge << ((u32ChannelNum - 2) * 16);

}

/**
 * @brief Disable capture interrupt of selected channel.
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32Edge Rising or falling edge to latch counter.
 *              - \ref PWM_CAPTURE_INT_RISING_LATCH
 *              - \ref PWM_CAPTURE_INT_FALLING_LATCH
 * @return None
 * @details This function is used to disable capture interrupt of selected channel.
 */
void PWM_DisableCaptureInt(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge)
{
    if(u32ChannelNum < 2)
        (pwm)->CCR0 &= u32Edge << ~(u32ChannelNum * 16);
    else
        (pwm)->CCR2 &= u32Edge << ~((u32ChannelNum - 2) * 16);
}

/**
 * @brief Clear capture interrupt of selected channel.
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32Edge Rising or falling edge to latch counter.
 *              - \ref PWM_CAPTURE_INT_RISING_LATCH
 *              - \ref PWM_CAPTURE_INT_FALLING_LATCH
 * @return None
 * @details This function is used to clear capture interrupt of selected channel.
 */
void PWM_ClearCaptureIntFlag(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge)
{
    //clear capture interrupt flag, and clear CRLR or CFLR latched indicator
    if(u32ChannelNum < 2)
        (pwm)->CCR0 = ((pwm)->CCR0 & PWM_CCR_MASK) | (PWM_CCR0_CAPIF0_Msk << (u32ChannelNum * 16)) | (u32Edge << (u32ChannelNum * 16 + 5));
    else
        (pwm)->CCR2 = ((pwm)->CCR2 & PWM_CCR_MASK) | (PWM_CCR2_CAPIF2_Msk << ((u32ChannelNum - 2) * 16)) | (u32Edge << ((u32ChannelNum - 2) * 16 + 5));
}

/**
 * @brief Get capture interrupt of selected channel.
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @retval 0 No capture interrupt
 * @retval 1 Rising edge latch interrupt
 * @retval 2 Falling edge latch interrupt
 * @retval 3 Rising and falling latch interrupt
 * @details This function is used to get capture interrupt of selected channel.
 */
uint32_t PWM_GetCaptureIntFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    if(u32ChannelNum < 2)
    {
        return (((pwm)->CCR0 & ((PWM_CCR0_CRLRI0_Msk | PWM_CCR0_CFLRI0_Msk) << (u32ChannelNum * 16))) >> (PWM_CCR0_CRLRI0_Pos + u32ChannelNum * 16));
    }
    else
    {
        return (((pwm)->CCR2 & ((PWM_CCR2_CRLRI2_Msk | PWM_CCR2_CFLRI2_Msk) << ((u32ChannelNum - 2) * 16))) >> (PWM_CCR2_CRLRI2_Pos + (u32ChannelNum - 2) * 16));
    }

}
/**
 * @brief Enable duty interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32IntDutyType Duty interrupt type, could be either
 *              - \ref PWM_DUTY_INT_DOWN_COUNT_MATCH_CMR
 *              - \ref PWM_DUTY_INT_UP_COUNT_MATCH_CMR
 * @return None
 * @details This function is used to enable duty interrupt of selected channel.
 *          Every two channels, (0 & 1), (2 & 3), shares the duty interrupt type setting.
 */
void PWM_EnableDutyInt(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32IntDutyType)
{
    (pwm)->PIER = ((pwm)->PIER & ~(PWM_PIER_INT01DTYPE_Msk << (u32ChannelNum >> 1))) | \
                  (PWM_PIER_PWMDIE0_Msk << u32ChannelNum) | (u32IntDutyType << (u32ChannelNum >> 1));
}

/**
 * @brief Disable duty interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 *                - PWMA : PWM Group A
 *                - PWMB : PWM Group B
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return None
 * @details This function is used to disable duty interrupt of selected channel
 */
void PWM_DisableDutyInt(PWM_T *pwm, uint32_t u32ChannelNum)
{
    (pwm)->PIER &= ~(PWM_PIER_PWMDIE0_Msk << u32ChannelNum);
}

/**
 * @brief Clear duty interrupt flag of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return None
 * @details This function is used to clear duty interrupt flag of selected channel
 */
void PWM_ClearDutyIntFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    (pwm)->PIIR = PWM_PIIR_PWMDIF0_Msk << u32ChannelNum;
}

/**
 * @brief Get duty interrupt flag of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return Duty interrupt flag of specified channel
 * @retval 0 Duty interrupt did not occur
 * @retval 1 Duty interrupt occurred
 * @details This function is used to get duty interrupt flag of selected channel
 */
uint32_t PWM_GetDutyIntFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    return (((pwm)->PIIR & (PWM_PIIR_PWMDIF0_Msk << u32ChannelNum)) ? 1 : 0);
}

/**
 * @brief Enable period interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32IntPeriodType Period interrupt type, could be either
 *              - \ref PWM_PERIOD_INT_UNDERFLOW
 *              - \ref PWM_PERIOD_INT_MATCH_CNR
 * @return None
 * @details This function is used to enable period interrupt of selected channel.
 *          Every two channels, (0 & 1), (2 & 3), shares the period interrupt type setting.
 */
void PWM_EnablePeriodInt(PWM_T *pwm, uint32_t u32ChannelNum,  uint32_t u32IntPeriodType)
{
    (pwm)->PIER = ((pwm)->PIER & ~(PWM_PIER_INT01TYPE_Msk << (u32ChannelNum >> 1))) | \
                  (PWM_PIER_PWMIE0_Msk << u32ChannelNum) | (u32IntPeriodType << (u32ChannelNum >> 1));
}

/**
 * @brief Disable period interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return None
 * @details This function is used to disable period interrupt of selected channel.
 */
void PWM_DisablePeriodInt(PWM_T *pwm, uint32_t u32ChannelNum)
{
    (pwm)->PIER &= ~(PWM_PIER_PWMIE0_Msk << u32ChannelNum);
}

/**
 * @brief Clear period interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return None
 * @details This function is used to clear period interrupt of selected channel
 */
void PWM_ClearPeriodIntFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    (pwm)->PIIR = (PWM_PIIR_PWMIF0_Msk << u32ChannelNum);
}

/**
 * @brief Get period interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return Period interrupt flag of specified channel
 * @retval 0 Period interrupt did not occur
 * @retval 1 Period interrupt occurred
 * @details This function is used to get period interrupt of selected channel
 */
uint32_t PWM_GetPeriodIntFlag(PWM_T *pwm, uint32_t u32ChannelNum)
{
    return (((pwm)->PIIR & (PWM_PIIR_PWMIF0_Msk << (u32ChannelNum))) ? 1 : 0);
}



/*@}*/ /* end of group M051_PWM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_PWM_Driver */

/*@}*/ /* end of group M051_Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
