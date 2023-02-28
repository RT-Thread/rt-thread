/**************************************************************************//**
 * @file     eadc.c
 * @brief    series EADC driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup EADC_Driver EADC Driver
  @{
*/

/** @addtogroup EADC_EXPORTED_FUNCTIONS EADC Exported Functions
  @{
*/

/**
  * @brief This function make EADC_module be ready to convert.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32InputMode Decides the input mode.
  *                       - \ref EADC_CTL_DIFFEN_SINGLE_END      :Single end input mode.
  *                       - \ref EADC_CTL_DIFFEN_DIFFERENTIAL    :Differential input type.
  * @return None
  * @details This function is used to set analog input mode and enable A/D Converter.
  *         Before starting A/D conversion function, ADCEN bit (EADC_CTL[0]) should be set to 1.
  * @note
  */
void EADC_Open(EADC_T *eadc, uint32_t u32InputMode)
{
    eadc->CTL &= (~EADC_CTL_DIFFEN_Msk);

    eadc->CTL |= (u32InputMode | EADC_CTL_ADCEN_Msk);
    while (!(eadc->PWRM & EADC_PWRM_PWUPRDY_Msk)) {}
}

/**
  * @brief Disable EADC_module.
  * @param[in] eadc The pointer of the specified EADC module..
  * @return None
  * @details Clear ADCEN bit (EADC_CTL[0]) to disable A/D converter analog circuit power consumption.
  */
void EADC_Close(EADC_T *eadc)
{
    eadc->CTL &= ~EADC_CTL_ADCEN_Msk;
}

/**
  * @brief Configure the sample control logic module.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid value are from 0 to 15.
  * @param[in] u32TriggerSrc Decides the trigger source. Valid values are:
  *                            - \ref EADC_SOFTWARE_TRIGGER              : Disable trigger
  *                            - \ref EADC_FALLING_EDGE_TRIGGER          : STADC pin falling edge trigger
  *                            - \ref EADC_RISING_EDGE_TRIGGER           : STADC pin rising edge trigger
  *                            - \ref EADC_FALLING_RISING_EDGE_TRIGGER   : STADC pin both falling and rising edge trigger
  *                            - \ref EADC_ADINT0_TRIGGER                : EADC ADINT0 interrupt EOC pulse trigger
  *                            - \ref EADC_ADINT1_TRIGGER                : EADC ADINT1 interrupt EOC pulse trigger
  *                            - \ref EADC_TIMER0_TRIGGER                : Timer0 overflow pulse trigger
  *                            - \ref EADC_TIMER1_TRIGGER                : Timer1 overflow pulse trigger
  *                            - \ref EADC_TIMER2_TRIGGER                : Timer2 overflow pulse trigger
  *                            - \ref EADC_TIMER3_TRIGGER                : Timer3 overflow pulse trigger
  *                            - \ref EADC_EPWM0TG0_TRIGGER              : EPWM0TG0 trigger
  *                            - \ref EADC_EPWM0TG1_TRIGGER              : EPWM0TG1 trigger
  *                            - \ref EADC_EPWM0TG2_TRIGGER              : EPWM0TG2 trigger
  *                            - \ref EADC_EPWM0TG3_TRIGGER              : EPWM0TG3 trigger
  *                            - \ref EADC_EPWM0TG4_TRIGGER              : EPWM0TG4 trigger
  *                            - \ref EADC_EPWM0TG5_TRIGGER              : EPWM0TG5 trigger
  *                            - \ref EADC_EPWM1TG0_TRIGGER              : EPWM1TG0 trigger
  *                            - \ref EADC_EPWM1TG1_TRIGGER              : EPWM1TG1 trigger
  *                            - \ref EADC_EPWM1TG2_TRIGGER              : EPWM1TG2 trigger
  *                            - \ref EADC_EPWM1TG3_TRIGGER              : EPWM1TG3 trigger
  *                            - \ref EADC_EPWM1TG4_TRIGGER              : EPWM1TG4 trigger
  *                            - \ref EADC_EPWM1TG5_TRIGGER              : EPWM1TG5 trigger
  *                            - \ref EADC_BPWM0TG_TRIGGER               : BPWM0TG trigger
  *                            - \ref EADC_BPWM1TG_TRIGGER               : BPWM1TG trigger
  * @param[in] u32Channel Specifies the sample module channel, valid value are from 0 to 15.
  * @return None
  * @details Each of ADC control logic modules 0~15 which is configurable for ADC converter channel EADC_CH0~15 and trigger source.
  *         sample module 16~18 is fixed for ADC channel 16, 17, 18 input sources as band-gap voltage, temperature sensor, and battery power (VBAT).
  */
void EADC_ConfigSampleModule(EADC_T *eadc, \
                             uint32_t u32ModuleNum, \
                             uint32_t u32TriggerSrc, \
                             uint32_t u32Channel)
{
    eadc->SCTL[u32ModuleNum] &= ~(EADC_SCTL_EXTFEN_Msk | EADC_SCTL_EXTREN_Msk | EADC_SCTL_TRGSEL_Msk | EADC_SCTL_CHSEL_Msk);
    eadc->SCTL[u32ModuleNum] |= (u32TriggerSrc | u32Channel);
}


/**
  * @brief Set trigger delay time.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid value are from 0 to 15.
  * @param[in] u32TriggerDelayTime Decides the trigger delay time, valid range are between 0~0xFF.
  * @param[in] u32DelayClockDivider Decides the trigger delay clock divider. Valid values are:
    *                                - \ref EADC_SCTL_TRGDLYDIV_DIVIDER_1    : Trigger delay clock frequency is ADC_CLK/1
    *                                - \ref EADC_SCTL_TRGDLYDIV_DIVIDER_2    : Trigger delay clock frequency is ADC_CLK/2
    *                                - \ref EADC_SCTL_TRGDLYDIV_DIVIDER_4    : Trigger delay clock frequency is ADC_CLK/4
    *                                - \ref EADC_SCTL_TRGDLYDIV_DIVIDER_16   : Trigger delay clock frequency is ADC_CLK/16
  * @return None
  * @details User can configure the trigger delay time by setting TRGDLYCNT (EADC_SCTLn[15:8], n=0~15) and TRGDLYDIV (EADC_SCTLn[7:6], n=0~15).
  *         Trigger delay time = (u32TriggerDelayTime) x Trigger delay clock period.
  */
void EADC_SetTriggerDelayTime(EADC_T *eadc, \
                              uint32_t u32ModuleNum, \
                              uint32_t u32TriggerDelayTime, \
                              uint32_t u32DelayClockDivider)
{
    eadc->SCTL[u32ModuleNum] &= ~(EADC_SCTL_TRGDLYDIV_Msk | EADC_SCTL_TRGDLYCNT_Msk);
    eadc->SCTL[u32ModuleNum] |= ((u32TriggerDelayTime << EADC_SCTL_TRGDLYCNT_Pos) | u32DelayClockDivider);
}

/**
  * @brief Set ADC extend sample time.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid value are from 0 to 18.
  * @param[in] u32ExtendSampleTime Decides the extend sampling time, the range is from 0~255 ADC clock. Valid value are from 0 to 0xFF.
  * @return None
  * @details When A/D converting at high conversion rate, the sampling time of analog input voltage may not enough if input channel loading is heavy,
  *         user can extend A/D sampling time after trigger source is coming to get enough sampling time.
  */
void EADC_SetExtendSampleTime(EADC_T *eadc, uint32_t u32ModuleNum, uint32_t u32ExtendSampleTime)
{
    eadc->SCTL[u32ModuleNum] &= ~EADC_SCTL_EXTSMPT_Msk;

    eadc->SCTL[u32ModuleNum] |= (u32ExtendSampleTime << EADC_SCTL_EXTSMPT_Pos);

}

/*@}*/ /* end of group EADC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group EADC_Driver */

/*@}*/ /* end of group Standard_Driver */

