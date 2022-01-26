/**************************************************************************//**
 * @file     gpio.c
 * @version  V3.00
 * @brief    M2354 series General Purpose I/O (GPIO) driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"


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
 *
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port. \n
 *                          It could be BIT0 ~ BIT15 for PA, PB and PE. \n
 *                          It could be BIT0 ~ BIT13 for PC. \n
 *                          It could be BIT0 ~ BIT12, BIT14 for PD. \n
 *                          It could be BIT0 ~ BIT11 for PF. \n
 *                          It could be BIT2 ~ BIT3, BIT9 ~ BIT15 for PG. \n
 *                          It could be BIT4 ~ BIT11 for PH.
 * @param[in]   u32Mode     Operation mode. It could be
 *                          - \ref GPIO_MODE_INPUT
 *                          - \ref GPIO_MODE_OUTPUT
 *                          - \ref GPIO_MODE_OPEN_DRAIN
 *                          - \ref GPIO_MODE_QUASI
 *
 * @return      None
 *
 * @details     This function is used to set specified GPIO operation mode.
 */
void GPIO_SetMode(GPIO_T *port, uint32_t u32PinMask, uint32_t u32Mode)
{
    uint32_t u32Idx;

    for(u32Idx = 0ul; u32Idx < GPIO_PIN_MAX; u32Idx++)
    {
        if((u32PinMask & (1ul << u32Idx)) == (1ul << u32Idx))
        {
            port->MODE = (port->MODE & ~(0x3ul << (u32Idx << 1))) | (u32Mode << (u32Idx << 1));
        }
    }
}

/**
 * @brief       Enable GPIO interrupt
 *
 * @param[in]   port            GPIO port. It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32Pin          The pin of specified GPIO port. \n
 *                              It could be 0 ~ 15 for PA, PB and PE. \n
 *                              It could be 0 ~ 13 for PC GPIO port. \n
 *                              It could be 0 ~ 12, 14 for PD GPIO port. \n
 *                              It could be 0 ~ 11 for PF GPIO port. \n
 *                              It could be 2 ~ 4, 9 ~ 15 for PG GPIO port. \n
 *                              It could be 4 ~ 11 for PH GPIO port.
 * @param[in]   u32IntAttribs   The interrupt attribute of specified GPIO pin. It could be
 *                              - \ref GPIO_INT_RISING
 *                              - \ref GPIO_INT_FALLING
 *                              - \ref GPIO_INT_BOTH_EDGE
 *                              - \ref GPIO_INT_HIGH
 *                              - \ref GPIO_INT_LOW
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
void GPIO_EnableInt(GPIO_T *port, uint32_t u32Pin, uint32_t u32IntAttribs)
{
    /* Configure interrupt mode of specified pin */
    port->INTTYPE = (port->INTTYPE & ~(1ul << u32Pin)) | (((u32IntAttribs >> 24) & 0xFFUL) << u32Pin);

    /* Enable interrupt function of specified pin */
    port->INTEN = (port->INTEN & ~(0x00010001ul << u32Pin)) | ((u32IntAttribs & 0xFFFFFFUL) << u32Pin);
}


/**
 * @brief       Disable GPIO interrupt
 *

 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32Pin      The pin of specified GPIO port. \n
 *                          It could be 0 ~ 15 for PA, PB and PE. \n
 *                          It could be 0 ~ 13 for PC GPIO port. \n
 *                          It could be 0 ~ 12, 14 for PD GPIO port. \n
 *                          It could be 0 ~ 11 for PF GPIO port. \n
 *                          It could be 2 ~ 4, 9 ~ 15 for PG GPIO port. \n
 *                          It could be 4 ~ 11 for PH GPIO port.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
void GPIO_DisableInt(GPIO_T *port, uint32_t u32Pin)
{
    /* Configure interrupt mode of specified pin */
    port->INTTYPE &= ~(1UL << u32Pin);

    /* Disable interrupt function of specified pin */
    port->INTEN &= ~((0x00010001UL) << u32Pin);
}

/**
 * @brief       Set GPIO slew rate control
 *

 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port. \n
 *                          It could be BIT0 ~ BIT15 for PA, PB and PE. \n
 *                          It could be BIT0 ~ BIT13 for PC. \n
 *                          It could be BIT0 ~ BIT12, BIT14. \n
 *                          It could be BIT0 ~ BIT11 for PF. \n
 *                          It could be BIT2 ~ BIT3, BIT9 ~ BIT15 for PG. \n
 *                          It could be BIT4 ~ BIT11 for PH.
 * @param[in]   u32Mode     Slew rate mode. It could be
 *                          - \ref GPIO_SLEWCTL_NORMAL (maximum 40 MHz at 2.7V)
 *                          - \ref GPIO_SLEWCTL_HIGH (maximum 80 MHz at 2.7V)
 *                          - \ref GPIO_SLEWCTL_FAST (maximum 100 MHz at 2.7V)
 *
 * @return      None
 *
 * @details     This function is used to set specified GPIO operation mode.
 */
void GPIO_SetSlewCtl(GPIO_T *port, uint32_t u32PinMask, uint32_t u32Mode)
{
    uint32_t u32Idx;

    for(u32Idx = 0ul; u32Idx < GPIO_PIN_MAX; u32Idx++)
    {
        if(u32PinMask & (1ul << u32Idx))
        {
            port->SLEWCTL = (port->SLEWCTL & ~(0x3ul << (u32Idx << 1))) | (u32Mode << (u32Idx << 1));
        }
    }
}

/**
 * @brief       Set GPIO Pull-up and Pull-down control
 *

 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE, PF, PG or PH.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port. \n
 *                          It could be BIT0 ~ BIT15 for PA, PB and PE. \n
 *                          It could be BIT0 ~ BIT13 for PC. \n
 *                          It could be BIT0 ~ BIT12, BIT14 for PD. \n
 *                          It could be BIT0 ~ BIT11 for PF. \n
 *                          It could be BIT2 ~ BIT3, BIT9 ~ BIT15 for PG. \n
 *                          It could be BIT4 ~ BIT11 for PH.
 * @param[in]   u32Mode     The pin mode of specified GPIO pin. It could be
 *                          - \ref GPIO_PUSEL_DISABLE
 *                          - \ref GPIO_PUSEL_PULL_UP
 *                          - \ref GPIO_PUSEL_PULL_DOWN
 *
 * @return      None
 *
 * @details     Set the pin mode of specified GPIO pin.
 */
void GPIO_SetPullCtl(GPIO_T *port, uint32_t u32PinMask, uint32_t u32Mode)
{
    uint32_t u32Idx;

    for(u32Idx = 0ul; u32Idx < GPIO_PIN_MAX; u32Idx++)
    {
        if(u32PinMask & (1ul << u32Idx))
        {
            port->PUSEL = (port->PUSEL & ~(0x3ul << (u32Idx << 1))) | (u32Mode << (u32Idx << 1));
        }
    }
}

/**@}*/ /* end of group GPIO_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group GPIO_Driver */

/**@}*/ /* end of group Standard_Driver */

