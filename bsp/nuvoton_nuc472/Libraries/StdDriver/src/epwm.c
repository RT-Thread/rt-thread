/**************************************************************************//**
 * @file     EPWM.c
 * @version  V1.00
 * $Revision: 3 $
 * $Date: 15/11/18 2:33p $
 * @brief    NUC472/NUC442 EPWM driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC472_442.h"

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_EPWM_Driver EPWM Driver
  @{
*/


/** @addtogroup NUC472_442_EPWM_EXPORTED_FUNCTIONS EPWM Exported Functions
  @{
*/

/**
 * @brief This function config PWM generator and get the nearest frequency in edge aligned auto-reload mode
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32Frequency Target generator frequency
 * @param[in] u32DutyCycle Target generator duty cycle percentage. Valid range are between 0 ~ 100. 10 means 10%, 20 means 20%...
 * @return Nearest frequency clock in nano second
 */
uint32_t EPWM_ConfigOutputChannel (EPWM_T *pwm,
                                   uint32_t u32ChannelNum,
                                   uint32_t u32Frequency,
                                   uint32_t u32DutyCycle)
{
    uint32_t i;
    uint32_t u32PWM_CLock;
    uint8_t  u8Divider = 1;
    uint16_t u16CNR = 0xFFFF;

    u32PWM_CLock = SystemCoreClock;

    for(; u8Divider < 17; u8Divider <<= 1) {  // clk divider could only be 1, 2, 4, 16
        // clk divider not support 8
        if (u8Divider == 8)
            continue;

        i = (u32PWM_CLock / u32Frequency) / u8Divider;
        // If target value is larger than CNR, need to use a larger divider
        if(i > 0x10000)
            continue;

        // CNR = 0xFFFF + 1, get a prescaler that CNR value is below 0xFFFF

        if(i <= 0x10000) {
            if(i == 1)
                u16CNR = 1;     // Too fast, and PWM cannot generate expected frequency...
            else
                u16CNR = i;
            break;
        }

    }
    // Store return value here 'cos we're gonna change u8Divider & u16CNR to the real value to fill into register
    i = u32PWM_CLock / (u8Divider * u16CNR);

    u16CNR -= 1;
    // convert to real register value
    if(u8Divider == 1)
        u8Divider = 0;
    else if (u8Divider == 2)
        u8Divider = 1;
    else if (u8Divider == 4)
        u8Divider = 2;
    else // 16
        u8Divider = 3;

    pwm->CTL = (pwm->CTL & ~EPWM_CTL_CLKDIV_Msk) | ( u8Divider << EPWM_CTL_CLKDIV_Pos);

    if(u32DutyCycle == 0)
        pwm->CMPDAT[u32ChannelNum >> 1] = 0;
    else
        pwm->CMPDAT[u32ChannelNum >> 1] = u32DutyCycle * (u16CNR + 1) / 100 - 1;

    pwm->PERIOD = u16CNR;

    return(i);
}


/**
 * @brief This function start PWM module
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask This parameter is not used
 * @note All channels share one counter
 * @return None
 */
void EPWM_Start (EPWM_T *pwm, uint32_t u32ChannelMask)
{
    pwm->CTL |= EPWM_CTL_CNTEN_Msk;
}

/**
 * @brief This function stop PWM module
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask This parameter is not used
 * @note All channels share one counter
 * @return None
 */
void EPWM_Stop (EPWM_T *pwm, uint32_t u32ChannelMask)
{
    pwm->CTL &= ~EPWM_CTL_CNTEN_Msk;
}

/**
 * @brief This function stop PWM generation immediately by clear channel enable bit
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask This parameter is not used
 * @note All channels share one counter
 * @return None
 */
void EPWM_ForceStop (EPWM_T *pwm, uint32_t u32ChannelMask)
{
    pwm->CTL &= ~EPWM_CTL_CNTEN_Msk;
}

/**
 * @brief This function enable fault brake of selected channels
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask This parameter is not used
 * @param[in] u32LevelMask Output high or low while fault brake occurs, each bit represent the level of a channel
 *                         while fault brake occurs. Bit 0 represents channel 0, bit 1 represents channel 1...
 *                         , bit 5 represent channel 5
 * @param[in] u32BrakeSource Fault brake source, could be one of following source
 *                  - \ref EPWM_BRK0_BKP0
 *                  - \ref EPWM_BRK0_CPO0
 *                  - \ref EPWM_BRK0_CPO1
 *                  - \ref EPWM_BRK0_CPO2
 *                  - \ref EPWM_BRK1_LVDBKEN
 *                  - \ref EPWM_BK1SEL_BKP1
 *                  - \ref EPWM_BK1SEL_CPO0
 *                  - \ref EPWM_BK1SEL_CPO1
 *                  - \ref EPWM_BK1SEL_CPO2
 * @return None
 */
void EPWM_EnableFaultBrake (EPWM_T *pwm,
                            uint32_t u32ChannelMask,
                            uint32_t u32LevelMask,
                            uint32_t u32BrakeSource)
{
    if ((u32BrakeSource == EPWM_BRK0_BKP0)||(u32BrakeSource == EPWM_BRK0_CPO0)||(u32BrakeSource == EPWM_BRK0_CPO1)||(u32BrakeSource == EPWM_BRK0_CPO2))
        pwm->CTL |= (u32BrakeSource | EPWM_CTL_BRKP0EN_Msk);
    else if (u32BrakeSource == EPWM_BRK1_LVDBKEN)
        pwm->CTL |= EPWM_BRK1_LVDBKEN;
    else
        pwm->CTL = (pwm->CTL & ~EPWM_CTL_BRK1SEL_Msk) | u32BrakeSource | EPWM_CTL_BRKP1EN_Msk;

    pwm->BRKOUT = (pwm->BRKOUT & ~EPWM_BRKOUT_BRKOUT_Msk) | u32LevelMask;
}

/**
 * @brief This function clear fault brake flag
 * @param[in] pwm The base address of PWM module
 * @param[in] u32BrakeSource This parameter is not used
 * @return None
 * @note After fault brake occurred, application must clear fault brake source before re-enable PWM output
 */
void EPWM_ClearFaultBrakeFlag (EPWM_T *pwm, uint32_t u32BrakeSource)
{
    pwm->STATUS = EPWM_STATUS_BRK0LOCK_Msk | EPWM_STATUS_BRKIF0_Msk;
}


/**
 * @brief This function enables PWM output generation of selected channels
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Set bit 0 to 1 enables channel 0 output, set bit 1 to 1 enables channel 1 output...
 * @return None
 */
void EPWM_EnableOutput (EPWM_T *pwm, uint32_t u32ChannelMask)
{
    if (u32ChannelMask & 0x15)
        pwm->OUTEN0 |= EPWM_OUTEN0_EVENOUTEN_Msk;
    if (u32ChannelMask & 0x2A)
        pwm->OUTEN0 |= EPWM_OUTEN0_ODDOUTEN_Msk;
}

/**
 * @brief This function disables PWM output generation of selected channels
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Set bit 0 to 1 disables channel 0 output, set bit 1 to 1 disables channel 1 output...
 * @return None
 */
void EPWM_DisableOutput (EPWM_T *pwm, uint32_t u32ChannelMask)
{
    if (u32ChannelMask & 0x15)
        pwm->OUTEN0 &= ~EPWM_OUTEN0_EVENOUTEN_Msk;
    if (u32ChannelMask & 0x2A)
        pwm->OUTEN0 &= ~EPWM_OUTEN0_ODDOUTEN_Msk;

}

/**
 * @brief This function enable Dead zone of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32Duration Dead Zone length in PWM clock count, valid values are between 0~0x7FF
 * @return None
 */
void EPWM_EnableDeadZone (EPWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Duration)
{
    // every two channels shares the same setting
    u32ChannelNum >>= 1;
    // set duration
    pwm->DTCTL = (pwm->DTCTL & ~EPWM_DTCTL_DTCNT_Msk) | u32Duration;
    // enable dead zone
    pwm->DTCTL |= (EPWM_DTCTL_DTEN0_Msk << u32ChannelNum);
}

/**
 * @brief This function disable Dead zone of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return None
 */
void EPWM_DisableDeadZone (EPWM_T *pwm, uint32_t u32ChannelNum)
{
    // every two channels shares the same setting
    u32ChannelNum >>= 1;
    // enable dead zone
    pwm->DTCTL &= ~(EPWM_DTCTL_DTEN0_Msk << u32ChannelNum);
}

/**
 * @brief This function enable duty interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32IntDutyType This parameter is not used
 * @return None
 */
void EPWM_EnableDutyInt (EPWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32IntDutyType)
{
    // every two channels shares the same setting
    u32ChannelNum >>= 1;
    // set duty interrupt type
    pwm->CTL = (pwm->CTL & ~EPWM_CTL_INTTYPE_Msk) | EPWM_CTL_PWMIEN_Msk;

    pwm->EINTCTL |= ((EPWM_EINTCTL_EINTTYPE0_Msk << u32ChannelNum) | (EPWM_EINTCTL_EDGEIEN0_Msk << u32ChannelNum));
}

/**
 * @brief This function disable duty interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return None
 */
void EPWM_DisableDutyInt (EPWM_T *pwm, uint32_t u32ChannelNum)
{
    // every two channels shares the same setting
    u32ChannelNum >>= 1;
    pwm->CTL &= ~(EPWM_EINTCTL_EDGEIEN0_Msk << u32ChannelNum);
}

/**
 * @brief This function clears duty interrupt flag of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return None
 */
void EPWM_ClearDutyIntFlag (EPWM_T *pwm, uint32_t u32ChannelNum)
{
    // every two channels shares the same setting
    u32ChannelNum >>= 1;
    // write 1 clear
    pwm->STATUS = (EPWM_STATUS_EIF0_Msk << u32ChannelNum);
}

/**
 * @brief This function get duty interrupt flag of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return Duty interrupt flag of specified channel
 * @retval 0 Duty interrupt did not occurred
 * @retval 1 Duty interrupt occurred
 */
uint32_t EPWM_GetDutyIntFlag (EPWM_T *pwm, uint32_t u32ChannelNum)
{
    return((pwm->STATUS & (EPWM_STATUS_EIF0_Msk << u32ChannelNum)) ? 1 : 0);
}

/**
 * @brief This function enable fault brake interrupt
 * @param[in] pwm The base address of PWM module
 * @param[in] u32BrakeSource This parameter is not used
 * @return None
 */
void EPWM_EnableFaultBrakeInt (EPWM_T *pwm, uint32_t u32BrakeSource)
{
    pwm->CTL |= EPWM_CTL_BRKIEN_Msk;
}

/**
 * @brief This function disable fault brake interrupt
 * @param[in] pwm The base address of PWM module
 * @param[in] u32BrakeSource This parameter is not used
 * @return None
 */
void EPWM_DisableFaultBrakeInt (EPWM_T *pwm, uint32_t u32BrakeSource)
{
    pwm->CTL &= ~EPWM_CTL_BRKIEN_Msk;
}

/**
 * @brief This function clear fault brake interrupt of selected source
 * @param[in] pwm The base address of PWM module
 * @param[in] u32BrakeSource Fault brake source, could be either
 *                  - \ref EPWM_STATUS_BRKIF0_Msk, or
 *                  - \ref EPWM_STATUS_BRKIF1_Msk
 * @return None
 */
void EPWM_ClearFaultBrakeIntFlag (EPWM_T *pwm, uint32_t u32BrakeSource)
{
    pwm->STATUS = u32BrakeSource;
}

/**
 * @brief This function get fault brake interrupt of selected source
 * @param[in] pwm The base address of PWM module
 * @param[in] u32BrakeSource Fault brake source, could be either
 *                  - \ref EPWM_STATUS_BRKIF0_Msk, or
 *                  - \ref EPWM_STATUS_BRKIF1_Msk
 * @return Fault brake interrupt flag of specified source
 * @retval 0 Fault brake interrupt did not occurred
 * @retval 1 Fault brake interrupt occurred
 */
uint32_t EPWM_GetFaultBrakeIntFlag (EPWM_T *pwm, uint32_t u32BrakeSource)
{
    return (pwm->STATUS & u32BrakeSource ? 1 : 0);
}

/**
 * @brief This function enable period interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum This parameter is not used
 * @param[in] u32IntPeriodType This parameter is not used
 * @return None
 * @note All channels share the same period interrupt type setting.
 */
void EPWM_EnablePeriodInt (EPWM_T *pwm, uint32_t u32ChannelNum,  uint32_t u32IntPeriodType)
{
    // set period interrupt type and enable period interrupt
    pwm->CTL |= (EPWM_CTL_INTTYPE_Msk | EPWM_CTL_PWMIEN_Msk);
}

/**
 * @brief This function disable period interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum This parameter is not used
 * @return None
 */
void EPWM_DisablePeriodInt (EPWM_T *pwm, uint32_t u32ChannelNum)
{
    pwm->CTL &= ~EPWM_CTL_PWMIEN_Msk;
}

/**
 * @brief This function clear period interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return None
 */
void EPWM_ClearPeriodIntFlag (EPWM_T *pwm, uint32_t u32ChannelNum)
{
    // write 1 clear
    pwm->STATUS = EPWM_STATUS_PIF_Msk;
}

/**
 * @brief This function get period interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return Period interrupt flag of specified channel
 * @retval 0 Period interrupt did not occurred
 * @retval 1 Period interrupt occurred
 */
uint32_t EPWM_GetPeriodIntFlag (EPWM_T *pwm, uint32_t u32ChannelNum)
{
    return(pwm->STATUS & EPWM_STATUS_PIF_Msk ? 1 : 0);
}



/*@}*/ /* end of group NUC472_442_EPWM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_EPWM_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
