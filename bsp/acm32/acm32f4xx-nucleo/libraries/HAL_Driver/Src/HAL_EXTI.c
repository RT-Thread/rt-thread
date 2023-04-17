/*
  ******************************************************************************
  * @file    HAL_EXTI.c
  * @version V1.0.0
  * @date    2020
  * @brief   EXTI HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the General Purpose Input/Output (EXTI) peripheral:
  *           + Initialization functions
  *           + IO operation functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

/*********************************************************************************
* Function    : HAL_EXTI_IRQHandler
* Description : Handle EXTI interrupt request.
* Input       : huart: EXTI handle.
* Output      :
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
void HAL_EXTI_IRQHandler(EXTI_HandleTypeDef *hexti)
{
    if (EXTI->PDR & hexti->u32_Line)
    {
        EXTI->PDR = hexti->u32_Line;
    }
}

/*********************************************************************************
* Function    : HAL_EXTI_SetConfigLine
* Description :
* Input       :
* Outpu       :
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti)
{
    uint32_t lu32_IndexLine;

#if (USE_FULL_ASSERT == 1)
    if (!IS_EXTI_ALL_LINE(hexti->u32_Line))      return HAL_ERROR;
    if (!IS_EXTI_MODE(hexti->u32_Mode))          return HAL_ERROR;
    if (!IS_EXTI_TRIGGER(hexti->u32_Trigger))    return HAL_ERROR;

    /* Line0 ~ 15 trigger from GPIO */
    if (!(hexti->u32_Line >> 16))
    {
        if (!IS_EXTI_GPIOSEL(hexti->u32_GPIOSel))    return HAL_ERROR;
    }
#endif

    lu32_IndexLine = hexti->u32_Line;

    /* Interrupt Mode */
    if (hexti->u32_Mode == EXTI_MODE_INTERRUPT)
    {
        EXTI->IENR |=  lu32_IndexLine;
        EXTI->EENR &= ~lu32_IndexLine;

        NVIC_ClearPendingIRQ(EXTI_IRQn);
        NVIC_EnableIRQ(EXTI_IRQn);
    }
    /* Event Mode */
    else if (hexti->u32_Mode == EXTI_MODE_EVENT)
    {
        EXTI->EENR |=  lu32_IndexLine;
        EXTI->IENR &= ~lu32_IndexLine;
    }


    if (hexti->u32_Trigger == EXTI_TRIGGER_RISING)
    {
        EXTI->RTENR |=  lu32_IndexLine;
        EXTI->FTENR &= ~lu32_IndexLine;
    }
    else if (hexti->u32_Trigger == EXTI_TRIGGER_FALLING)
    {
        EXTI->FTENR |=  lu32_IndexLine;
        EXTI->RTENR &= ~lu32_IndexLine;
    }
    else
    {
        EXTI->FTENR |= lu32_IndexLine;
        EXTI->RTENR |= lu32_IndexLine;
    }

    /* Line0 ~ 15 trigger from GPIO */
    if (!(hexti->u32_Line >> 16))
    {
        lu32_IndexLine = 0;

        while(hexti->u32_Line >> lu32_IndexLine != 0x01)
        {
            lu32_IndexLine++;
        }

        /* Line0 ~ 7 */
        if (lu32_IndexLine < 8)
        {
            EXTI->EXTICR1 = (EXTI->EXTICR1 & ~(0x0F << (lu32_IndexLine * 4))) | hexti->u32_GPIOSel << (lu32_IndexLine * 4);
        }
        /* Line8 ~ 15 */
        else
        {
            lu32_IndexLine -= 8;

            EXTI->EXTICR2 = (EXTI->EXTICR2 & ~(0x0F << (lu32_IndexLine * 4))) | hexti->u32_GPIOSel << (lu32_IndexLine * 4);
        }
    }

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_EXTI_SoftTrigger
* Description : Software trigger EXTI
* Input       :
* Outpu       :
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
void HAL_EXTI_SoftTrigger(EXTI_HandleTypeDef *hexti)
{
#if (USE_FULL_ASSERT == 1)
    if (!IS_EXTI_ALL_LINE(hexti->u32_Line))    return;
#endif

    /* Set pending BIT */
    EXTI->SWIER |= hexti->u32_Line;
}

/*********************************************************************************
* Function    : HAL_EXTI_GetPending
* Description : Get interrupt pending bit of a dedicated line.
* Input       :
* Outpu       :
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
bool HAL_EXTI_GetPending(EXTI_HandleTypeDef *hexti)
{
#if (USE_FULL_ASSERT == 1)
    if (!IS_EXTI_ALL_LINE(hexti->u32_Line))    return HAL_ERROR;
#endif

    if (hexti->u32_Line & EXTI->PDR)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*********************************************************************************
* Function    : HAL_EXTI_ClearPending
* Description : Clear interrupt pending bit of a dedicated line.
* Input       :
* Outpu       :
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
void HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti)
{
#if (USE_FULL_ASSERT == 1)
    if (!IS_EXTI_ALL_LINE(hexti->u32_Line))    return;
#endif

    /* Clear pending status */
    EXTI->PDR |= hexti->u32_Line;
}

/*********************************************************************************
* Function    : HAL_EXTI_ClearAllPending
* Description : Clear all interrupt pending bit.
* Input       :
* Outpu       :
* Author      : xwl                         Data : 2021年
**********************************************************************************/
void HAL_EXTI_ClearAllPending(void)
{
    /* Clear pending status */
    EXTI->PDR |= EXTI_LINE_MASK;
}

