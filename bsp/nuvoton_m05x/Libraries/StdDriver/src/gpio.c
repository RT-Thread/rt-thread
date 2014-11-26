/**************************************************************************//**
 * @file     gpio.c
 * @version  V3.00
 * $Revision: 4 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series GPIO driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "M051Series.h"


/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_GPIO_Driver GPIO Driver
  @{
*/

/** @addtogroup M051_GPIO_EXPORTED_FUNCTIONS GPIO Exported Functions
  @{
*/

/**
 * @brief       Set GPIO operation mode
 *
 * @param[in]   port        GPIO port. It could be P0, P1, P2, P3 or P4.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port. It could be BIT0 ~ BIT7.
 * @param[in]   u32Mode     Operation mode. GPIO_PMD_INPUT, GPIO_PMD_OUTPUT, GPIO_PMD_OPEN_DRAIN, GPIO_PMD_QUASI
 *
 * @return      None
 *
 * @details     This function is used to set specified GPIO operation mode.
 */
void GPIO_SetMode(GPIO_T *port, uint32_t u32PinMask, uint32_t u32Mode)
{
    uint32_t i;

    for(i = 0; i < GPIO_PIN_MAX; i++)
    {
        if(u32PinMask & (1 << i))
        {
            port->PMD = (port->PMD & ~(0x3 << (i << 1))) | (u32Mode << (i << 1));
        }
    }
}

/**
 * @brief       Enable GPIO interrupt
 *
 * @param[in]   port            GPIO port. It could be P0, P1, P2, P3 or P4.
 * @param[in]   u32Pin          The pin of specified GPIO port. It could be 0 ~ 7.
 * @param[in]   u32IntAttribs   The interrupt attribute of specified GPIO pin. It could be \n
 *                              GPIO_INT_RISING, GPIO_INT_FALLING, GPIO_INT_BOTH_EDGE, GPIO_INT_HIGH, GPIO_INT_LOW.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
void GPIO_EnableInt(GPIO_T *port, uint32_t u32Pin, uint32_t u32IntAttribs)
{
    port->IMD |= (((u32IntAttribs >> 24) & 0xFFUL) << u32Pin);
    port->IEN |= ((u32IntAttribs & 0xFFFFFFUL) << u32Pin);
}


/**
 * @brief       Disable GPIO interrupt
 *
 * @param[in]   port        GPIO port. It could be P0, P1, P2, P3 or P4.
 * @param[in]   u32Pin      The pin of specified GPIO port. It could be 0 ~ 7.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
void GPIO_DisableInt(GPIO_T *port, uint32_t u32Pin)
{
    port->IMD &= ~(1UL << u32Pin);
    port->IEN &= ~((0x00010001UL) << u32Pin);
}


/*@}*/ /* end of group M051_GPIO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_GPIO_Driver */

/*@}*/ /* end of group M051_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
