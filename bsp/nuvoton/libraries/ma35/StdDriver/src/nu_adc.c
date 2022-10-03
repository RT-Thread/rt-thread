/**************************************************************************//**
 * @file     adc.c
 * @brief    ADC driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright(C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup ADC_Driver ADC Driver
  @{
*/


/** @addtogroup ADC_EXPORTED_FUNCTIONS ADC Exported Functions
  @{
*/

/**
  * @brief This API configures ADC module to be ready for convert the input from selected channel
  * @param[in] adc Base address of ADC module
  * @param[in] u32InputMode Input mode. Valid values are:
  *                     - \ref ADC_INPUT_MODE_NORMAL_CONV
  *                     - \ref ADC_INPUT_MODE_4WIRE_TOUCH
  *                     - \ref ADC_INPUT_MODE_5WIRE_TOUCH
  * @param[in] u32OpMode Could be
  *                     - \ref ADC_HIGH_SPEED_MODE
  *                     - \ref ADC_NORMAL_SPEED_MODE
  * @param[in] u32ChMask Channel enable bit. Each bit corresponds to a input channel. Bit 0 is channel 0, bit 1 is channel 1...
  *                      This parameter is only used while u32InputMode set to ADC_INPUT_MODE_NORMAL_CONV.
  * @return  None
  * @note ADC can only convert 1 channel at a time. If more than 1 channels are enabled, only channel
  *       with smallest number will be convert.
  * @note This API does not turn on ADC power nor does trigger ADC conversion
  */
void ADC_Open(ADC_T *adc,
              uint32_t u32InputMode,
              uint32_t u32OpMode,
              uint32_t u32ChMask)
{
    uint32_t u32Ch = 0, i;

    if (u32InputMode == ADC_INPUT_MODE_NORMAL_CONV)
    {
        for (i = 0; i < ADC_CH_NUM; i++)
        {
            if (u32ChMask & (1 << i))
            {
                u32Ch = i;
                break;
            }
        }
        adc->CONF = (u32Ch << ADC_CONF_CHSEL_Pos) | u32OpMode | ADC_CONF_NACEN_Msk;
    }
    else if (u32InputMode == ADC_INPUT_MODE_4WIRE_TOUCH)
    {
        adc->CONF = 0;
    }
    else // 5-wire mode
    {
        adc->CTL |= ADC_CTL_WMSWCH_Msk;
        adc->CONF = 0;
    }
}

/**
  * @brief Disable ADC module
  * @param[in] adc Base address of ADC module
  * @return None
  */
void ADC_Close(ADC_T *adc)
{
    adc->CTL = 0;
    adc->CONF = 0;
    adc->IER = 0;
    adc->ISR = adc->ISR;
}

/*@}*/ /* end of group ADC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group ADC_Driver */

/*@}*/ /* end of group Standard_Driver */
