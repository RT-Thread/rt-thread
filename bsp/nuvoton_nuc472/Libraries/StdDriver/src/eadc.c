/**************************************************************************//**
 * @file     eadc.c
 * @version  V1.00
 * $Revision: 7 $
 * $Date: 15/12/01 10:12a $
 * @brief    NUC472/NUC442 EADC driver source file
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC472_442.h"

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_EADC_Driver EADC Driver
  @{
*/


/** @addtogroup NUC472_442_EADC_EXPORTED_FUNCTIONS EADC Exported Functions
  @{
*/

/**
  * @brief This function make EADC_module be ready to convert.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32InputMode This parameter is not used.
  * @return None
  * @details This function is used to set analog input mode and enable A/D Converter.
  *         Before starting A/D conversion function, ADCEN bit (EADC_CTL[0]) should be set to 1.
  * @note
  */
void EADC_Open(EADC_T *eadc, uint32_t u32InputMode)
{
    eadc->CTL |= EADC_CTL_ADCEN_Msk;
}

/**
  * @brief Disable EADC_module.
  * @param[in] eadc Base address of EADC module..
  * @return None
  * @details Clear ADCEN bit (EADC_CTL[0]) to disable A/D converter analog circuit power consumption.
  */
void EADC_Close(EADC_T *eadc)
{
    eadc->CTL &= ~EADC_CTL_ADCEN_Msk;
}

/**
  * @brief Configure the sample control logic module.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid values are:
  *                            - \ref EADC0_SAMPLE_MODULE0      : EADC0 SAMPLE module 0
  *                            - \ref EADC0_SAMPLE_MODULE1      : EADC0 SAMPLE module 1
  *                            - \ref EADC0_SAMPLE_MODULE2      : EADC0 SAMPLE module 2
  *                            - \ref EADC0_SAMPLE_MODULE3      : EADC0 SAMPLE module 3
  *                            - \ref EADC0_SAMPLE_MODULE4      : EADC0 SAMPLE module 4
  *                            - \ref EADC0_SAMPLE_MODULE5      : EADC0 SAMPLE module 5
  *                            - \ref EADC0_SAMPLE_MODULE6      : EADC0 SAMPLE module 6
  *                            - \ref EADC0_SAMPLE_MODULE7      : EADC0 SAMPLE module 7
  *                            - \ref EADC1_SAMPLE_MODULE0      : EADC1 SAMPLE module 0
  *                            - \ref EADC1_SAMPLE_MODULE1      : EADC1 SAMPLE module 1
  *                            - \ref EADC1_SAMPLE_MODULE2      : EADC1 SAMPLE module 2
  *                            - \ref EADC1_SAMPLE_MODULE3      : EADC1 SAMPLE module 3
  *                            - \ref EADC1_SAMPLE_MODULE4      : EADC1 SAMPLE module 4
  *                            - \ref EADC1_SAMPLE_MODULE5      : EADC1 SAMPLE module 5
  *                            - \ref EADC1_SAMPLE_MODULE6      : EADC1 SAMPLE module 6
  *                            - \ref EADC1_SAMPLE_MODULE7      : EADC1 SAMPLE module 7
  * @param[in] u32TriggerSrc Decides the trigger source. Valid values are:
  *                            - \ref EADC_SOFTWARE_TRIGGER     : Disable trigger
  *                            - \ref EADC_STADC_TRIGGER        : STADC pin trigger
  *                            - \ref EADC_ADINT0_TRIGGER       : EADC ADINT0 interrupt EOC pulse trigger
  *                            - \ref EADC_ADINT1_TRIGGER       : EADC ADINT1 interrupt EOC pulse trigger
  *                            - \ref EADC_TIMER0_TRIGGER       : Timer0 overflow pulse trigger
  *                            - \ref EADC_TIMER1_TRIGGER       : Timer1 overflow pulse trigger
  *                            - \ref EADC_TIMER2_TRIGGER       : Timer2 overflow pulse trigger
  *                            - \ref EADC_TIMER3_TRIGGER       : Timer3 overflow pulse trigger
  *                            - \ref EADC_EPWM0CH0_TRIGGER     : EPWM0CH0 trigger
  *                            - \ref EADC_EPWM0CH2_TRIGGER     : EPWM0CH2 trigger
  *                            - \ref EADC_EPWM0CH4_TRIGGER     : EPWM0CH4 trigger
  *                            - \ref EADC_EPWM1CH0_TRIGGER     : EPWM0CH0 trigger
  *                            - \ref EADC_EPWM1CH2_TRIGGER     : EPWM0CH2 trigger
  *                            - \ref EADC_EPWM1CH4_TRIGGER     : EPWM0CH4 trigger
  *                            - \ref EADC_PWM0CH0_TRIGGER      : PWM0CH0 trigger
  *                            - \ref EADC_PWM0CH1_TRIGGER      : PWM0CH1 trigger
  * @param[in] u32Channel Specifies the sample module channel, valid value are:
  *                            - \ref EADC0_CH0     : EADC0 channel 0
  *                            - \ref EADC0_CH1     : EADC0 channel 1
  *                            - \ref EADC0_CH2     : EADC0 channel 2
  *                            - \ref EADC0_CH3     : EADC0 channel 3
  *                            - \ref EADC0_CH4     : EADC0 channel 4
  *                            - \ref EADC0_CH5     : EADC0 channel 5
  *                            - \ref EADC0_CH6     : EADC0 channel 6
  *                            - \ref EADC0_CH7     : EADC0 channel 7
  *                            - \ref EADC0_VBG     : EADC0 VBG
  *                            - \ref EADC0_VTEMP   : EADC0 VTEMP
  *                            - \ref EADC0_AVSS    : EADC0 AVSS
  *                            - \ref EADC0_OP0     : EADC0 OP0
  *                            - \ref EADC1_CH0     : EADC1 channel 0
  *                            - \ref EADC1_CH1     : EADC1 channel 1
  *                            - \ref EADC1_CH2     : EADC1 channel 2
  *                            - \ref EADC1_CH3     : EADC1 channel 3
  *                            - \ref EADC1_CH4     : EADC1 channel 4
  *                            - \ref EADC1_CH5     : EADC1 channel 5
  *                            - \ref EADC1_CH6     : EADC1 channel 6
  *                            - \ref EADC1_CH7     : EADC1 channel 7
  *                            - \ref EADC1_OP1     : EADC1 OP1
  * @return None
  * @details Each of EADC control logic modules 0~15 which is configurable for EADC converter channel and trigger source.
  */
void EADC_ConfigSampleModule(EADC_T *eadc, \
                             uint32_t u32ModuleNum, \
                             uint32_t u32TriggerSrc, \
                             uint32_t u32Channel)
{
    *(__IO uint32_t *)(&eadc->AD0SPCTL0 + u32ModuleNum) &= ~(EADC_AD0SPCTL0_TRGSEL_Msk | EADC_AD0SPCTL0_CHSEL_Msk);
    *(__IO uint32_t *)(&eadc->AD0SPCTL0 + u32ModuleNum) |= (u32TriggerSrc | u32Channel);
    if (u32TriggerSrc == EADC_STADC_TRIGGER)
        *(__IO uint32_t *)(&eadc->AD0SPCTL0 + u32ModuleNum) |= (EADC_AD0SPCTL0_EXTREN_Msk | EADC_AD0SPCTL0_EXTFEN_Msk);

}


/**
  * @brief Set trigger delay time.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid values are:
  *                            - \ref EADC0_SAMPLE_MODULE0      : EADC0 SAMPLE module 0
  *                            - \ref EADC0_SAMPLE_MODULE1      : EADC0 SAMPLE module 1
  *                            - \ref EADC0_SAMPLE_MODULE2      : EADC0 SAMPLE module 2
  *                            - \ref EADC0_SAMPLE_MODULE3      : EADC0 SAMPLE module 3
  *                            - \ref EADC0_SAMPLE_MODULE4      : EADC0 SAMPLE module 4
  *                            - \ref EADC0_SAMPLE_MODULE5      : EADC0 SAMPLE module 5
  *                            - \ref EADC0_SAMPLE_MODULE6      : EADC0 SAMPLE module 6
  *                            - \ref EADC0_SAMPLE_MODULE7      : EADC0 SAMPLE module 7
  *                            - \ref EADC1_SAMPLE_MODULE0      : EADC1 SAMPLE module 0
  *                            - \ref EADC1_SAMPLE_MODULE1      : EADC1 SAMPLE module 1
  *                            - \ref EADC1_SAMPLE_MODULE2      : EADC1 SAMPLE module 2
  *                            - \ref EADC1_SAMPLE_MODULE3      : EADC1 SAMPLE module 3
  *                            - \ref EADC1_SAMPLE_MODULE4      : EADC1 SAMPLE module 4
  *                            - \ref EADC1_SAMPLE_MODULE5      : EADC1 SAMPLE module 5
  *                            - \ref EADC1_SAMPLE_MODULE6      : EADC1 SAMPLE module 6
  *                            - \ref EADC1_SAMPLE_MODULE7      : EADC1 SAMPLE module 7
  * @param[in] u32TriggerDelayTime Decides the trigger delay time, valid range are between 0~0xFF.
  * @param[in] u32DelayClockDivider Decides the trigger delay clock divider. Valid values are:
  *                            - \ref EADC_SPCTL_TRGDLYDIV_DIVIDER_1    : Trigger delay clock frequency is ADC_CLK/1
  *                            - \ref EADC_SPCTL_TRGDLYDIV_DIVIDER_2    : Trigger delay clock frequency is ADC_CLK/2
  *                            - \ref EADC_SPCTL_TRGDLYDIV_DIVIDER_4    : Trigger delay clock frequency is ADC_CLK/4
  *                            - \ref EADC_SPCTL_TRGDLYDIV_DIVIDER_16   : Trigger delay clock frequency is ADC_CLK/16
  * @return None
  * @details User can configure the trigger delay time by setting TRGDLYCNT (EADC_ADxSPCTLn[15:8], x=0~1, n=0~7) and TRGDLYDIV (EADC_ADxSPCTLn[17:16], x=0~1, n=0~7).
  *         Trigger delay time = (u32TriggerDelayTime) x Trigger delay clock period.
  */
void EADC_SetTriggerDelayTime(EADC_T *eadc, \
                              uint32_t u32ModuleNum, \
                              uint32_t u32TriggerDelayTime, \
                              uint32_t u32DelayClockDivider)
{
    *(__IO uint32_t *)(&eadc->AD0SPCTL0 + u32ModuleNum) &= ~(EADC_AD0SPCTL0_TRGDLYDIV_Msk | EADC_AD0SPCTL0_TRGDLYCNT_Msk);
    *(__IO uint32_t *)(&eadc->AD0SPCTL0 + u32ModuleNum) |= ((u32TriggerDelayTime << EADC_AD0SPCTL0_TRGDLYCNT_Pos) | u32DelayClockDivider);
}


/**
  * @brief Set EADC extend sample time.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid values are:
  *                            - \ref EADC0_SAMPLE_MODULE0      : EADC0 SAMPLE module 0
  *                            - \ref EADC0_SAMPLE_MODULE1      : EADC0 SAMPLE module 1
  *                            - \ref EADC0_SAMPLE_MODULE2      : EADC0 SAMPLE module 2
  *                            - \ref EADC0_SAMPLE_MODULE3      : EADC0 SAMPLE module 3
  *                            - \ref EADC0_SAMPLE_MODULE4      : EADC0 SAMPLE module 4
  *                            - \ref EADC0_SAMPLE_MODULE5      : EADC0 SAMPLE module 5
  *                            - \ref EADC0_SAMPLE_MODULE6      : EADC0 SAMPLE module 6
  *                            - \ref EADC0_SAMPLE_MODULE7      : EADC0 SAMPLE module 7
  *                            - \ref EADC1_SAMPLE_MODULE0      : EADC1 SAMPLE module 0
  *                            - \ref EADC1_SAMPLE_MODULE1      : EADC1 SAMPLE module 1
  *                            - \ref EADC1_SAMPLE_MODULE2      : EADC1 SAMPLE module 2
  *                            - \ref EADC1_SAMPLE_MODULE3      : EADC1 SAMPLE module 3
  *                            - \ref EADC1_SAMPLE_MODULE4      : EADC1 SAMPLE module 4
  *                            - \ref EADC1_SAMPLE_MODULE5      : EADC1 SAMPLE module 5
  *                            - \ref EADC1_SAMPLE_MODULE6      : EADC1 SAMPLE module 6
  *                            - \ref EADC1_SAMPLE_MODULE7      : EADC1 SAMPLE module 7
  * @param[in] u32ExtendSampleTime Decides the extend sampling time, the range is from 0~255 EADC clock. Valid value are from 0 to 0xFF.
  * @return None
  * @details When A/D converting at high conversion rate, the sampling time of analog input voltage may not enough if input channel loading is heavy,
  *         user can extend A/D sampling time after trigger source is coming to get enough sampling time.
  */
void EADC_SetExtendSampleTime(EADC_T *eadc, uint32_t u32ModuleNum, uint32_t u32ExtendSampleTime)
{
    if (u32ModuleNum < EADC1_SAMPLE_MODULE0) {
        eadc->EXTSMPT &= ~EADC_EXTSMPT_EXTSMPT0_Msk;
        eadc->EXTSMPT |= u32ExtendSampleTime;
    } else {
        eadc->EXTSMPT &= ~EADC_EXTSMPT_EXTSMPT1_Msk;
        eadc->EXTSMPT |= (u32ExtendSampleTime << EADC_EXTSMPT_EXTSMPT1_Pos);
    }
}

/*@}*/ /* end of group NUC472_442_EADC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_EADC_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
