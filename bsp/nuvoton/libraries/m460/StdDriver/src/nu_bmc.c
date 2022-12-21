/**************************************************************************//**
 * @file     bmc.c
 * @version  V3.00
 * @brief    M460 series BMC driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup BMC_Driver BMC Driver
  @{
*/


/** @addtogroup BMC_EXPORTED_FUNCTIONS BMC Exported Functions
  @{
*/

/**
  * @brief      Set the BMC bit clock
  * @param[in]  u32BitClock The expected frequency of BMC bit clock in Hz
  * @return     Actual frequency of BMC bit clock
  * @details    The actual clock rate may be different from the target BMC bit clock rate.
  *             For example, if the system clock rate is 200 MHz and the target BMC bit clock rate is 3 MHz, the actual BMC bit clock
  *             rate will be 2 MHz.
  * \hideinitializer
  */
uint32_t BMC_SetBitClock(uint32_t u32BitClock)
{
    uint32_t u32HCLKFreq, u32Div, u32RetValue;

    /* Get system clock frequency */
    u32HCLKFreq = CLK_GetHCLKFreq();

    u32Div = ((u32HCLKFreq * 10UL) / u32BitClock + 5UL) / 10UL; /* Round to the nearest integer */

    BMC->CTL = (BMC->CTL & (~BMC_CTL_BTDIV_Msk)) | (u32Div << BMC_CTL_BTDIV_Pos);

    /* Return BMC bit clock rate */
    u32RetValue = u32HCLKFreq / u32Div;

    return u32RetValue;
}

/**
  * @brief      Get the actual frequency of BMC bit clock
  * @return     Actual BMC bit frequency in Hz
  * @details    This API will calculate the actual BMC bit clock rate according to the HBTDIV setting.
  * \hideinitializer
  */
uint32_t BMC_GetBitClock(void)
{
    uint32_t u32HCLKFreq, u32Div;

    /* Get BTDIV setting */
    u32Div = (BMC->CTL & BMC_CTL_BTDIV_Msk) >> BMC_CTL_BTDIV_Pos;

    /* Get system clock frequency */
    u32HCLKFreq = CLK_GetHCLKFreq();

    /* Return BMC bit clock rate */
    return (u32HCLKFreq / u32Div);
}

/**
  * @brief      Set the dummy delay time period of each group
  * @param[in]  u32ChGroup BMC channel group selection, valid values are:
  *                        - \ref BMC_GROUP_0
  *                        - \ref BMC_GROUP_1
  *                        - \ref BMC_GROUP_2
  *                        - \ref BMC_GROUP_3
  *                        - \ref BMC_GROUP_4
  *                        - \ref BMC_GROUP_5
  *                        - \ref BMC_GROUP_6
  *                        - \ref BMC_GROUP_7
  * @param[in]  u32DumDelay The expected BMC dummy delay period in microsecond
  * @return     Actual dummy delay time period in microsecond
  * @details    This API is used to set each group dummy delay time period.
  * \hideinitializer
  */
uint32_t BMC_SetDummyDelayPeriod(uint32_t u32ChGroup, uint32_t u32DumDelay)
{
    uint32_t i, u32BitNum;

    u32BitNum = ((BMC_GetBitClock() * u32DumDelay) / 1000000UL) / 8UL;

    for (i = 0UL; i < (uint32_t)BMC_CHANNEL_NUM; i += 4UL)
    {
        if ((u32ChGroup == i) && (u32ChGroup <= BMC_GROUP_3))
        {
            outp8((uint32_t) & (BMC->DNUM0) + (i >> 2UL), u32BitNum);
            break;
        }
        else if ((u32ChGroup == i) && (u32ChGroup > BMC_GROUP_3))
        {
            outp8((uint32_t) & (BMC->DNUM1) + ((i >> 2UL) - 4UL), u32BitNum);
            break;
        }
    }

    /* Return BMC dummy delay time period */
    return (8UL * 1000000UL / BMC_GetBitClock() * u32BitNum);
}

/**
  * @brief      Enable interrupt function
  * @param[in]  u32Mask The combination of all related interrupt enable bits.
  *                     Each bit corresponds to a interrupt enable bit.
  *                     This parameter decides which interrupts will be enabled. It is combination of:
  *                     - \ref BMC_FTXD_INT_MASK
  *                     - \ref BMC_TXUND_INT_MASK
  * @return     None
  * @details    This API is used to enable BMC related interrupts specified by u32Mask parameter.
  * \hideinitializer
  */
void BMC_EnableInt(uint32_t u32Mask)
{
    /* Enable frame transmit done interrupt flag */
    if ((u32Mask & BMC_FTXD_INT_MASK) == BMC_FTXD_INT_MASK)
    {
        BMC->INTEN |= BMC_INTEN_FTXDIEN_Msk;
    }

    /* Enable transmit data under run interrupt flag */
    if ((u32Mask & BMC_TXUND_INT_MASK) == BMC_TXUND_INT_MASK)
    {
        BMC->INTEN |= BMC_INTEN_TXUNDIEN_Msk;
    }
}

/**
  * @brief      Disable interrupt function
  * @param[in]  u32Mask The combination of all related interrupt enable bits.
  *                     Each bit corresponds to a interrupt enable bit.
  *                     This parameter decides which interrupts will be disabled. It is combination of:
  *                     - \ref BMC_FTXD_INT_MASK
  *                     - \ref BMC_TXUND_INT_MASK
  * @return     None
  * @details    This API is used to disable BMC related interrupts specified by u32Mask parameter.
  * \hideinitializer
  */
void BMC_DisableInt(uint32_t u32Mask)
{
    /* Disable frame transmit done interrupt flag */
    if ((u32Mask & BMC_FTXD_INT_MASK) == BMC_FTXD_INT_MASK)
    {
        BMC->INTEN &= ~BMC_INTEN_FTXDIEN_Msk;
    }

    /* Disable transmit data under run interrupt flag */
    if ((u32Mask & BMC_TXUND_INT_MASK) == BMC_TXUND_INT_MASK)
    {
        BMC->INTEN &= ~BMC_INTEN_TXUNDIEN_Msk;
    }
}

/**
  * @brief      Get interrupt flag
  * @param[in]  u32Mask The combination of all related interrupt sources.
  *                     Each bit corresponds to a interrupt source.
  *                     This parameter decides which interrupt flags will be read. It is combination of:
  *                     - \ref BMC_FTXD_INT_MASK
  *                     - \ref BMC_TXUND_INT_MASK
  * @return     Interrupt flags of selected sources
  * @details    This API is used to get BMC related interrupt flags specified by u32Mask parameter.
  * \hideinitializer
  */
uint32_t BMC_GetIntFlag(uint32_t u32Mask)
{
    uint32_t u32IntStatus;
    uint32_t u32IntFlag = 0UL;

    u32IntStatus = BMC->INTSTS;

    /* Check frame transmit done interrupt flag */
    if ((u32Mask & BMC_FTXD_INT_MASK) && (u32IntStatus & BMC_INTSTS_FTXDIF_Msk))
    {
        u32IntFlag |= BMC_FTXD_INT_MASK;
    }

    /* Check transmit data under run interrupt flag */
    if ((u32Mask & BMC_TXUND_INT_MASK) && (u32IntStatus & BMC_INTSTS_TXUNDIF_Msk))
    {
        u32IntFlag |= BMC_TXUND_INT_MASK;
    }

    return u32IntFlag;
}

/**
  * @brief      Clear interrupt flag
  * @param[in]  u32Mask The related interrupt source.
  *                     This parameter decides which interrupt flag will be cleared. Possible option is:
  *                     - \ref BMC_FTXD_INT_MASK
  * @return     None
  * @details    This API is used to clear BMC related interrupt flag specified by u32Mask parameter.
  * \hideinitializer
  */
void BMC_ClearIntFlag(uint32_t u32Mask)
{
    if (u32Mask & BMC_FTXD_INT_MASK)
    {
        BMC->INTSTS = BMC_INTSTS_FTXDIF_Msk; /* Clear frame transmit done interrupt flag */
    }
}

/**
  * @brief      Get BMC status
  * @param[in]  u32Mask The combination of all related sources.
  *                     Each bit corresponds to a related source.
  *                     This parameter decides which flags will be read. It is combination of:
  *                     - \ref BMC_G0TXUND_MASK
  *                     - \ref BMC_G1TXUND_MASK
  *                     - \ref BMC_G2TXUND_MASK
  *                     - \ref BMC_G3TXUND_MASK
  *                     - \ref BMC_G4TXUND_MASK
  *                     - \ref BMC_G5TXUND_MASK
  *                     - \ref BMC_G6TXUND_MASK
  *                     - \ref BMC_G7TXUND_MASK
  * @return     Flags of selected sources
  * @details    This API is used to get BMC related status specified by u32Mask parameter.
  * \hideinitializer
  */
uint32_t BMC_GetStatus(uint32_t u32Mask)
{
    uint32_t u32TmpStatus;
    uint32_t u32Flag = 0UL;

    u32TmpStatus = BMC->INTSTS;

    /* Check group 0 transmit data under run status */
    if ((u32Mask & BMC_G0TXUND_MASK) && (u32TmpStatus & BMC_INTSTS_G0TXUND_Msk))
    {
        u32Flag |= BMC_G0TXUND_MASK;
    }

    /* Check group 1 transmit data under run status */
    if ((u32Mask & BMC_G1TXUND_MASK) && (u32TmpStatus & BMC_INTSTS_G1TXUND_Msk))
    {
        u32Flag |= BMC_G1TXUND_MASK;
    }

    /* Check group 2 transmit data under run status */
    if ((u32Mask & BMC_G2TXUND_MASK) && (u32TmpStatus & BMC_INTSTS_G2TXUND_Msk))
    {
        u32Flag |= BMC_G2TXUND_MASK;
    }

    /* Check group 3 transmit data under run status */
    if ((u32Mask & BMC_G3TXUND_MASK) && (u32TmpStatus & BMC_INTSTS_G3TXUND_Msk))
    {
        u32Flag |= BMC_G3TXUND_MASK;
    }

    /* Check group 4 transmit data under run status */
    if ((u32Mask & BMC_G4TXUND_MASK) && (u32TmpStatus & BMC_INTSTS_G4TXUND_Msk))
    {
        u32Flag |= BMC_G4TXUND_MASK;
    }

    /* Check group 5 transmit data under run status */
    if ((u32Mask & BMC_G5TXUND_MASK) && (u32TmpStatus & BMC_INTSTS_G5TXUND_Msk))
    {
        u32Flag |= BMC_G5TXUND_MASK;
    }

    /* Check group 6 transmit data under run status */
    if ((u32Mask & BMC_G6TXUND_MASK) && (u32TmpStatus & BMC_INTSTS_G6TXUND_Msk))
    {
        u32Flag |= BMC_G6TXUND_MASK;
    }

    /* Check group 7 transmit data under run status */
    if ((u32Mask & BMC_G7TXUND_MASK) && (u32TmpStatus & BMC_INTSTS_G7TXUND_Msk))
    {
        u32Flag |= BMC_G7TXUND_MASK;
    }

    return u32Flag;
}

/**
  * @brief      Clear BMC status
  * @param[in]  u32Mask The combination of all related sources.
  *                     Each bit corresponds to a related source.
  *                     This parameter decides which flags will be cleared. It is combination of:
  *                     - \ref BMC_G0TXUND_MASK
  *                     - \ref BMC_G1TXUND_MASK
  *                     - \ref BMC_G2TXUND_MASK
  *                     - \ref BMC_G3TXUND_MASK
  *                     - \ref BMC_G4TXUND_MASK
  *                     - \ref BMC_G5TXUND_MASK
  *                     - \ref BMC_G6TXUND_MASK
  *                     - \ref BMC_G7TXUND_MASK
  * @return     None
  * @details    This API is used to clear BMC related status specified by u32Mask parameter.
  * \hideinitializer
  */
void BMC_ClearStatus(uint32_t u32Mask)
{
    if (u32Mask & BMC_G0TXUND_MASK)
    {
        BMC->INTSTS = BMC_INTSTS_G0TXUND_Msk; /* Check group 0 transmit data under run status */
    }

    if (u32Mask & BMC_G1TXUND_MASK)
    {
        BMC->INTSTS = BMC_INTSTS_G1TXUND_Msk; /* Check group 1 transmit data under run status */
    }

    if (u32Mask & BMC_G2TXUND_MASK)
    {
        BMC->INTSTS = BMC_INTSTS_G2TXUND_Msk; /* Check group 2 transmit data under run status */
    }

    if (u32Mask & BMC_G3TXUND_MASK)
    {
        BMC->INTSTS = BMC_INTSTS_G3TXUND_Msk; /* Check group 3 transmit data under run status */
    }

    if (u32Mask & BMC_G4TXUND_MASK)
    {
        BMC->INTSTS = BMC_INTSTS_G4TXUND_Msk; /* Check group 4 transmit data under run status */
    }

    if (u32Mask & BMC_G5TXUND_MASK)
    {
        BMC->INTSTS = BMC_INTSTS_G5TXUND_Msk; /* Check group 5 transmit data under run status */
    }

    if (u32Mask & BMC_G6TXUND_MASK)
    {
        BMC->INTSTS = BMC_INTSTS_G6TXUND_Msk; /* Check group 6 transmit data under run status */
    }

    if (u32Mask & BMC_G7TXUND_MASK)
    {
        BMC->INTSTS = BMC_INTSTS_G7TXUND_Msk; /* Check group 7 transmit data under run status */
    }
}


/*@}*/ /* end of group BMC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group BMC_Driver */

/*@}*/ /* end of group Standard_Driver */
