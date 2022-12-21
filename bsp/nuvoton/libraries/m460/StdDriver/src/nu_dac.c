/**************************************************************************//**
 * @file     dac.c
 * @version  V1.00
 * @brief    DAC driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup DAC_Driver DAC Driver
  @{
*/

/** @addtogroup DAC_EXPORTED_FUNCTIONS DAC Exported Functions
  @{
*/

/**
  * @brief This function make DAC module be ready to convert.
  * @param[in] dac The pointer of the specified DAC module.
  * @param[in] u32Ch Not used.
  * @param[in] u32TrgSrc Decides the trigger source. Valid values are:
  *                      - \ref DAC_WRITE_DAT_TRIGGER             :Write DAC_DAT trigger
  *                      - \ref DAC_SOFTWARE_TRIGGER              :Software trigger
  *                      - \ref DAC_LOW_LEVEL_TRIGGER             :STDAC pin low level trigger
  *                      - \ref DAC_HIGH_LEVEL_TRIGGER            :STDAC pin high level trigger
  *                      - \ref DAC_FALLING_EDGE_TRIGGER          :STDAC pin falling edge trigger
  *                      - \ref DAC_RISING_EDGE_TRIGGER           :STDAC pin rising edge trigger
  *                      - \ref DAC_TIMER0_TRIGGER                :Timer 0 trigger
  *                      - \ref DAC_TIMER1_TRIGGER                :Timer 1 trigger
  *                      - \ref DAC_TIMER2_TRIGGER                :Timer 2 trigger
  *                      - \ref DAC_TIMER3_TRIGGER                :Timer 3 trigger
  *                      - \ref DAC_EPWM0_TRIGGER                 :EPWM0 trigger
  *                      - \ref DAC_EPWM1_TRIGGER                 :EPWM1 trigger
  * @return None
  * @details The DAC conversion can be started by writing DAC_DAT, software trigger or hardware trigger.
  *         When TRGEN (DAC_CTL[4]) is 0, the data conversion is started by writing DAC_DAT register.
  *         When TRGEN (DAC_CTL[4]) is 1, the data conversion is started by SWTRG (DAC_SWTRG[0]) is set to 1,
  *         external STDAC pin, timer event, or EPWM event.
  */
void DAC_Open(DAC_T *dac,
              uint32_t u32Ch,
              uint32_t u32TrgSrc)
{
    (void)u32Ch;
    dac->CTL &= ~(DAC_CTL_ETRGSEL_Msk | DAC_CTL_TRGSEL_Msk | DAC_CTL_TRGEN_Msk);
    dac->CTL |= (u32TrgSrc | DAC_CTL_DACEN_Msk);
}

/**
  * @brief Disable DAC analog power.
  * @param[in] dac The pointer of the specified DAC module.
  * @param[in] u32Ch Not used.
  * @return None
  * @details Disable DAC analog power for saving power consumption.
  */
void DAC_Close(DAC_T *dac, uint32_t u32Ch)
{
    (void)u32Ch;
    dac->CTL &= (~DAC_CTL_DACEN_Msk);
}

/**
  * @brief Set delay time for DAC to become stable.
  * @param[in] dac The pointer of the specified DAC module.
  * @param[in] u32Delay Decides the DAC conversion settling time, the range is from 0~(1023/PCLK1*1000000) micro seconds.
  * @return Real DAC conversion settling time (micro second).
  * @details For example, DAC controller clock speed is 160MHz and DAC conversion setting time is 1 us, SETTLET (DAC_TCTL[9:0]) value must be greater than 0xA0.
  * @note User needs to write appropriate value to meet DAC conversion settling time base on PCLK (APB clock) speed.
  */
uint32_t DAC_SetDelayTime(DAC_T *dac, uint32_t u32Delay)
{

    dac->TCTL = ((CLK_GetPCLK1Freq() * u32Delay / 1000000UL) & 0x3FFUL);

    return ((dac->TCTL) * 1000000UL / CLK_GetPCLK1Freq());
}



/*@}*/ /* end of group DAC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group DAC_Driver */

/*@}*/ /* end of group Standard_Driver */
