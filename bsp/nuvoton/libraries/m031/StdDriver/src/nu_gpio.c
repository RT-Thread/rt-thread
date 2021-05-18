/**************************************************************************//**
 * @file     gpio.c
 * @version  V3.00
 * $Revision: 2 $
 * $Date: 18/03/28 5:52p $
 * @brief    M031 Series General Purpose I/O (GPIO) Driver Source File
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "M031Series.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup GPIO_Driver GPIO Driver
  @{
*/

/** @addtogroup GPIO_EXPORTED_FUNCTIONS GPIO Exported Functions
  @{
*/

/**
 * @brief       Set GPIO operation mode
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, or PF.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT15 for PA and PB.
 *                          It could be BIT0 ~ BIT7, and BIT14 for PC.
 *                          It could be BIT0 ~ BIT3, and BIT15 for PD.
 *                          It could be BIT0 ~ BIT6, BIT14, and BIT15 for PF.
 * @param[in]   u32Mode     Operation mode.  It could be
 *                          - \ref GPIO_MODE_INPUT
 *                          - \ref GPIO_MODE_OUTPUT
 *                          - \ref GPIO_MODE_OPEN_DRAIN
 *                          - \ref GPIO_MODE_QUASI
 * @return      None
 * @details     This function is used to set specified GPIO operation mode.
 */
void GPIO_SetMode(GPIO_T *port, uint32_t u32PinMask, uint32_t u32Mode)
{
    uint32_t i;

    for(i = 0; i < GPIO_PIN_MAX; i++)
    {
        if(u32PinMask & (1 << i))
        {
            port->MODE = (port->MODE & ~(GPIO_MODE_MODE0_Msk << (i << 1))) | (u32Mode << (i << 1));
        }
    }
}

/**
 * @brief       Enable GPIO interrupt
 * @param[in]   port    GPIO port. It could be PA, PB, PC, PD, or PF.
 * @param[in]   u32Pin  The pin of specified GPIO port.
 *                      It could be 0 ~ 15 for PA and PB.
 *                      It could be 0 ~ 7, and 14 for PC.
 *                      It could be 0 ~ 3, and 15 for PD.
 *                      It could be 0 ~ 6, 14, and 15 for PF.
 * @param[in]   u32IntAttribs   The interrupt attribute of specified GPIO pin. It could be
 *                            - \ref GPIO_INT_RISING
 *                            - \ref GPIO_INT_FALLING
 *                            - \ref GPIO_INT_BOTH_EDGE
 *                            - \ref GPIO_INT_HIGH
 *                            - \ref GPIO_INT_LOW
 * @return      None
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
void GPIO_EnableInt(GPIO_T *port, uint32_t u32Pin, uint32_t u32IntAttribs)
{
    /* Configure interrupt mode of specified pin */
    port->INTTYPE |= (((u32IntAttribs >> 24) & 0xFFUL) << u32Pin);

    /* Enable interrupt function of specified pin */
    port->INTEN |= ((u32IntAttribs & 0xFFFFFFUL) << u32Pin);
}

/**
 * @brief       Disable GPIO interrupt
 * @param[in]   port    GPIO port. It could be PA, PB, PC, PD, or PF.
 * @param[in]   u32Pin  The pin of specified GPIO port.
 *                      It could be 0 ~ 15 for PA and PB.
 *                      It could be 0 ~ 7, and 14 for PC.
 *                      It could be 0 ~ 3, and 15 for PD.
 *                      It could be 0 ~ 6, 14, and 15 for PF.
 * @return      None
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
void GPIO_DisableInt(GPIO_T *port, uint32_t u32Pin)
{
    /* Configure interrupt mode of specified pin */
    port->INTTYPE &= ~(1UL << u32Pin);

    /* Disable interrupt function of specified pin */
    port->INTEN &= ~((0x00010001UL) << u32Pin);
}


/*@}*/ /* end of group GPIO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group GPIO_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
