/**************************************************************************//**
* @file     gpio.c
* @version  V1.00
* @brief    N9H30 GPIO driver source file
*
* SPDX-License-Identifier: Apache-2.0
* @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "N9H30.h"
#include "nu_sys.h"
#include "nu_gpio.h"

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_GPIO_Driver GPIO Driver
  @{
*/

/** @addtogroup N9H30_GPIO_EXPORTED_FUNCTIONS GPIO Exported Functions
  @{
*/

/**
 * @brief       Set GPIO Port
 *
 * @param[in]   port       GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 * @param[in]   bitMap     GPIO port. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     This function is used to set GPIO port output data.
 */
INT32 GPIO_Set(GPIO_PORT port, UINT32 bitMap)
{
    INT32 offset;
    INT32 reg;

    offset = (INT32)port;

    reg = inpw(REG_GPIOA_DATAOUT + offset);
    reg = reg | bitMap;
    outpw(REG_GPIOA_DATAOUT + offset, reg);

    return SUCCESSFUL;
}

/**
* @brief       Clear GPIO port OUT Data
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
* @param[in]   bitMap      GPIO port data. It could be 0x00 ~ 0xFF.
*
* @retval      <0          Fail
* @retval      0           Success
*
* @details     Clear GPIO port output data to 0.
*/
INT32 GPIO_Clr(GPIO_PORT port, UINT32 bitMap)
{
    INT32 offset;
    INT32 reg;

    offset = (INT32)port;

    reg = inpw(REG_GPIOA_DATAOUT + offset);
    reg = reg & (~bitMap);
    outpw(REG_GPIOA_DATAOUT + offset, reg);

    return SUCCESSFUL;
}



/**
 * @brief       Open GPIO bit
 *
 * @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 * @param[in]   bit         GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
 * @param[in]   direction   GPIO direction. It could be \ref DIR_INPUT or \ref DIR_OUTPUT
 * @param[in]   pull        GPIO pull-up. It could be \ref NO_PULL_UP or \ref PULL_UP
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     This function is used to open gpio pin.
 */
INT32 GPIO_OpenBit(GPIO_PORT port, UINT32 bit, GPIO_DIR direction, GPIO_PULL pull)
{
    UINT32 reg;
    UINT32 mask;
    INT32 offset;

    offset = (INT32)port;

    mask = (UINT32)bit;

    reg = inpw(REG_GPIOA_DIR + offset);
    reg = reg & (~mask);

    if (direction == DIR_OUTPUT)
    {
        reg = reg | mask;
    }

    outpw(REG_GPIOA_DIR + offset, reg);

    reg = inpw(REG_GPIOA_PUEN + offset);
    reg = reg & (~mask);

    if (pull == PULL_UP)
    {
        reg = reg | mask;
        outpw(REG_GPIOA_PUEN + offset, reg);
    }
    else if (pull == PULL_DOWN)
    {
        reg = reg | mask;
        outpw(REG_GPIOA_PDEN + offset, reg);
    }
    else
    {
        outpw(REG_GPIOA_PUEN + offset, reg);
        outpw(REG_GPIOA_PDEN + offset, reg);
    }

    return SUCCESSFUL;
}

/**
* @brief       Set GPIO pin OUT Data
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
* @param[in]   bit         GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
*
* @retval      <0              Fail
* @retval      0               Success
*
* @details     Set the Data into specified GPIO pin.
*/
INT32 GPIO_CloseBit(GPIO_PORT port, UINT32 bit)
{
    UINT32 reg;
    UINT32 mask;
    INT32 offset;

    offset = (INT32)port;
    mask = (UINT32)bit;

    reg = inpw(REG_GPIOA_DIR + offset);
    reg = reg & (~mask);
    outpw(REG_GPIOA_DIR + offset, reg);

    reg = inpw(REG_GPIOA_PUEN + offset);
    reg = reg & (~mask);
    outpw(REG_GPIOA_PUEN + offset, reg);

    return SUCCESSFUL;
}


/**
 * @brief       Set GPIO pin OUT Data
 *
 * @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 * @param[in]   bit          GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     Set the Data into specified GPIO pin.
 */
INT32 GPIO_SetBit(GPIO_PORT port, UINT32 bit)
{
    UINT32 bitMap;
    INT32 offset;
    INT32 reg;

    offset = (INT32)port;
    bitMap = (UINT32)bit;

    reg = inpw(REG_GPIOA_DATAOUT + offset);
    reg = reg | bitMap;
    outpw(REG_GPIOA_DATAOUT + offset, reg);

    return SUCCESSFUL;
}

/**
* @brief       Clear GPIO port Interrupt Flag
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
* @param[in]   bitMap      GPIO port data. It could be 0x00 ~ 0xFF.
*
* @retval      <0              Fail
* @retval      0               Success
*
* @details     Clear the interrupt status of specified GPIO port.
*/
INT32 GPIO_ClrISR(GPIO_PORT port, UINT32 bitMap)
{
    INT32 offset;

    offset = (INT32)port;

    outpw(REG_GPIOA_ISR + offset, bitMap);

    return SUCCESSFUL;
}

/**
 * @brief       Clear GPIO Pin Interrupt Flag
 *
 * @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 * @param[in]   bit         GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     Clear the interrupt status of specified GPIO pin.
 */
INT32 GPIO_ClrISRBit(GPIO_PORT port, UINT32 bit)
{
    UINT32 bitMap;
    INT32 offset;

    offset = (INT32)port;
    bitMap = (UINT32)bit;

    outpw(REG_GPIOA_ISR + offset, bitMap);

    return SUCCESSFUL;
}

/**
* @brief       Clear GPIO pin OUT Data
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
* @param[in]   bit         GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
*
* @retval      <0              Fail
* @retval      0               Success
*
* @details     Set the Data into specified GPIO pin.
*/
INT32 GPIO_ClrBit(GPIO_PORT port, UINT32 bit)
{
    UINT32 bitMap;
    INT32 offset;
    INT32 reg;

    offset = (INT32)port;
    bitMap = (UINT32)bit;

    reg = inpw(REG_GPIOA_DATAOUT + offset);
    reg = reg & (~bitMap);
    outpw(REG_GPIOA_DATAOUT + offset, reg);

    return SUCCESSFUL;
}

/**
* @brief       Read GPIO pin In Data
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
* @param[in]   bit         GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
*
* @retval      1/0         GPIO pin input data.
*
* @details     Read the In Data from GPIO pin.
*/
INT32 GPIO_ReadBit(GPIO_PORT port, UINT32 bit)
{
    UINT32 reg;
    UINT32 bitMap;
    INT32 offset;

    offset = (INT32)port;
    bitMap = (UINT32)bit;

    reg = inpw(REG_GPIOA_DATAIN + offset);

    return ((reg & bitMap) ? 1 : 0);
}

/**
* @brief       Set GPIO pin direction
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
* @param[in]   bit         GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
* @param[in]   direction   GPIO direction. It could be \ref DIR_INPUT, \ref DIR_OUTPUT.
*
* @retval      <0              Fail
* @retval      0               Success
*
* @details     Set the GPIO direction into specified GPIO pin.
*/
INT32 GPIO_SetBitDir(GPIO_PORT port, UINT32 bit, GPIO_DIR direction)
{
    UINT32 reg;
    UINT32 bitMap;
    INT32 offset;

    offset = (INT32)port;
    bitMap = (UINT32)bit;

    reg = inpw(REG_GPIOA_DIR + offset);
    reg = reg & (~bitMap);

    if (direction == DIR_OUTPUT)
    {
        reg = reg | bitMap;
    }

    outpw(REG_GPIOA_DIR + offset, reg);

    return SUCCESSFUL;
}

/**
 * @brief       Enable GPIO trigger type.
 *
 * @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 * @param[in]   bitMap      GPIO port. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
 * @param[in]   triggerType The triggerType of specified GPIO pin. It could be \n
 *                          \ref RISING, \ref FALLING, \ref BOTH_EDGE, \ref HIGH, \ref LOW.
 *
 * @retval      <0          Fail
 * @retval      0           Success
 *
 * @details     This function is used to enable trigger type.
 */
INT32 GPIO_EnableTriggerType(GPIO_PORT port, UINT32 bitMap, GPIO_TRIGGER_TYPE triggerType)
{
    UINT32 reg;
    INT32 offset;

    offset = (INT32)port;

    switch (triggerType)
    {
    case LOW:
        reg = inpw(REG_GPIOA_IMD + offset);
        outpw(REG_GPIOA_IMD + offset, reg | bitMap);

        reg = inpw(REG_GPIOA_IREN + offset);
        outpw(REG_GPIOA_IREN + offset, reg & ~bitMap);

        reg = inpw(REG_GPIOA_IFEN + offset);
        outpw(REG_GPIOA_IFEN + offset, reg  | bitMap);
        break;
    case HIGH:
        reg = inpw(REG_GPIOA_IMD + offset);
        outpw(REG_GPIOA_IMD + offset, reg | bitMap);

        reg = inpw(REG_GPIOA_IREN + offset);
        outpw(REG_GPIOA_IREN + offset, reg | bitMap);

        reg = inpw(REG_GPIOA_IFEN + offset);
        outpw(REG_GPIOA_IFEN + offset, reg & ~bitMap);
        break;
    case FALLING:
        reg = inpw(REG_GPIOA_IMD + offset);
        outpw(REG_GPIOA_IMD + offset, reg & ~bitMap);

        reg = inpw(REG_GPIOA_IREN + offset);
        outpw(REG_GPIOA_IREN + offset, reg & ~bitMap);

        reg = inpw(REG_GPIOA_IFEN + offset);
        outpw(REG_GPIOA_IFEN + offset, reg  | bitMap);
        break;
    case RISING:
        reg = inpw(REG_GPIOA_IMD + offset);
        outpw(REG_GPIOA_IMD + offset, reg & ~bitMap);

        reg = inpw(REG_GPIOA_IREN + offset);
        outpw(REG_GPIOA_IREN + offset, reg | bitMap);

        reg = inpw(REG_GPIOA_IFEN + offset);
        outpw(REG_GPIOA_IFEN + offset, reg & ~bitMap);
        break;
    case BOTH_EDGE:
        reg = inpw(REG_GPIOA_IMD + offset);
        outpw(REG_GPIOA_IMD + offset, reg & ~bitMap);

        reg = inpw(REG_GPIOA_IREN + offset);
        outpw(REG_GPIOA_IREN + offset, reg | bitMap);

        reg = inpw(REG_GPIOA_IFEN + offset);
        outpw(REG_GPIOA_IFEN + offset, reg | bitMap);
        break;
    }
    return SUCCESSFUL;
}

/**
 * @brief       Disable GPIO trigger type.
 *
 * @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 * @param[in]   bitMap      GPIO port. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
 *
 * @retval      <0          Fail
 * @retval      0           Success
 *
 * @details     This function is used to disable trigger type.
 */
INT32 GPIO_DisableTriggerType(GPIO_PORT port, UINT32 bitMap)
{
    UINT32 reg;
    INT32 offset;

    offset = (INT32)port;

    reg = inpw(REG_GPIOA_IMD + offset);
    outpw(REG_GPIOA_IMD + offset, reg & ~bitMap);

    reg = inpw(REG_GPIOA_IREN + offset);
    outpw(REG_GPIOA_IREN + offset, reg & ~bitMap);

    reg = inpw(REG_GPIOA_IFEN + offset);
    outpw(REG_GPIOA_IFEN + offset, reg & ~bitMap);

    return SUCCESSFUL;
}

/**
 * @brief       Enable GPIO De-bounce Function
 *
 * @param[in]   debounceClkSel        The de-bounce sampling cycle selection. It could be 0~0xF.  \n
 *                                     0 = Sample interrupt input once per 1 clocks. \n
 *                                     1 = Sample interrupt input once per 2 clocks. \n
 *                                     2 = Sample interrupt input once per 4 clocks. \n
 *                                     3 = Sample interrupt input once per 8 clocks. \n
 *                                     4 = Sample interrupt input once per 16 clocks. \n
 *                                     5 = Sample interrupt input once per 32 clocks. \n
 *                                     6 = Sample interrupt input once per 64 clocks. \n
 *                                     7 = Sample interrupt input once per 128 clocks. \n
 *                                     8 = Sample interrupt input once per 256 clocks. \n
 *                                     9 = Sample interrupt input once per 2*256 clocks. \n
 *                                    10 = Sample interrupt input once per 4*256 clocks. \n
 *                                    11 = Sample interrupt input once per 8*256 clocks. \n
 *                                    12 = Sample interrupt input once per 16*256 clocks. \n
 *                                    13 = Sample interrupt input once per 32*256 clocks. \n
 *                                    14 = Sample interrupt input once per 64*256 clocks. \n
 *                                    15 = Sample interrupt input once per 128*256 clocks
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     Enable the interrupt de-bounce function of specified GPIO.
 */
INT32 GPIO_EnableDebounce(INT32 debounceClkSel)
{
    UINT32 reg;

    reg = inpw(REG_GPIO_DBNCECON);

    /* Setting the debounce timing */
    reg = ((reg & ~0xf) | debounceClkSel);

    /* Enable the debounce function */
    reg = reg | 0x20;
    outpw(REG_GPIO_DBNCECON, reg);

    return SUCCESSFUL;
}

/**
 * @brief       Disable GPIO De-bounce Function.
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     Disable the interrupt de-bounce function of specified GPIO.
 */
INT32 GPIO_DisableDebounce(void)
{
    UINT32 reg;

    reg = inpw(REG_GPIO_DBNCECON);

    /* Setting the debounce timing */
    reg = ((reg & ~0xf));

    /* Enable the debounce function */
    reg = reg | 0x20;
    outpw(REG_GPIO_DBNCECON, reg);

    return SUCCESSFUL;
}

/*@}*/ /* end of group N9H30_GPIO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_GPIO_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

