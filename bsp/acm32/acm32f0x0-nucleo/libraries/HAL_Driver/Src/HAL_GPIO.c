/*
  ******************************************************************************
  * @file    HAL_GPIO.c
  * @version V1.0.0
  * @date    2020
  * @brief   GPIO HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the General Purpose Input/Output (GPIO) peripheral:
  *           @ Initialization  functions
  *           @ IO operation functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

/*********************************************************************************
* Function    : HAL_GPIO_IRQHandler
* Description : GPIO interrupt Handler
* Input       :
* Outpu       :
* Author      : Chris_Kyle                         Date : 2020年
**********************************************************************************/
void HAL_GPIO_IRQHandler(enum_GPIOx_t fe_GPIO, uint32_t fu32_GPIO_Pin)
{
    GPIO_TypeDef *GPIOx;

    switch (fe_GPIO)
    {
        case GPIOA:
        case GPIOB:
        {
            GPIOx = GPIOAB;
        }break;

        case GPIOC:
        case GPIOD:
        {
            GPIOx = GPIOCD;
        }break;

        default: break;
    }

    if (fe_GPIO == GPIOB || fe_GPIO == GPIOD )
    {
        fu32_GPIO_Pin <<= 16;
    }

    if (GPIOx->RIS & fu32_GPIO_Pin)
    {
        GPIOx->IC = fu32_GPIO_Pin;

        /* user can call your application process function here */
        /* ...... */
    }
}

/*********************************************************************************
* Function    : HAL_GPIO_Init
* Description : Initializes the GPIOx peripheral according to the specified parameters in the GPIO_Init
* Input       : fe_GPIO: to select the GPIO peripheral.
* Input       : GPIO_Init: pointer to a GPIO_InitTypeDef structure that contains
                           the configuration information for the specified GPIO peripheral.
* Outpu       :
* Author      : Chris_Kyle                         Date : 2020年
**********************************************************************************/
void HAL_GPIO_Init(enum_GPIOx_t fe_GPIO, GPIO_InitTypeDef *GPIO_Init)
{
    uint32_t lu32_Position = 0;
    uint32_t lu32_Current_Pin;
    uint32_t lu32_Position_Mask;

    volatile uint32_t *lu32_SEL1 = NULL;        // 指向 -> 管脚复用寄存器1
    volatile uint32_t *lu32_SEL2 = NULL;        // 指向 -> 管脚复用寄存器2
    volatile uint32_t *lu32_PollUP   = NULL;    // 指向 -> 上拉选择寄存器
    volatile uint32_t *lu32_PollDown = NULL;    // 指向 -> 下拉选择寄存器
    volatile uint32_t *lu32_ODEnable = NULL;    // 指向 -> 开漏使能寄存器
    volatile uint32_t *lu32_ADS      = NULL;    // 指向 -> 数字、模拟选择寄存器

    GPIO_TypeDef *GPIOx;

#if (USE_FULL_ASSERT == 1)
    /* Check the parameters */
    if (!IS_GPIO_ALL_INSTANCE(fe_GPIO))             return;
    if (!IS_GPIO_PIN(GPIO_Init->Pin))               return;
    if (!IS_GPIO_MODE(GPIO_Init->Mode))             return;
    if (!IS_GPIO_PULL(GPIO_Init->Pull))             return;
#endif

    switch (fe_GPIO)
    {
        case GPIOA:
        case GPIOB:
        {
            GPIOx = GPIOAB;

            System_Module_Enable(EN_GPIOAB);

            lu32_PollUP   = &(SCU->PABPUR);
            lu32_PollDown = &(SCU->PABPDR);
            lu32_ODEnable = &(SCU->PABODR);
            lu32_ADS      = &(SCU->PABADS);

            if (fe_GPIO == GPIOB)
            {
                GPIO_Init->Pin <<= 16;

                lu32_SEL1 = &(SCU->PBSEL1);
                lu32_SEL2 = &(SCU->PBSEL2);
            }
            else
            {
                lu32_SEL1 = &(SCU->PASEL1);
                lu32_SEL2 = &(SCU->PASEL2);
            }
        }break;

        case GPIOC:
        case GPIOD:
        {
            GPIOx = GPIOCD;

            System_Module_Enable(EN_GPIOCD);

            lu32_PollUP   = &(SCU->PCDPUR);
            lu32_PollDown = &(SCU->PCDPDR);
            lu32_ODEnable = &(SCU->PCDODR);
            lu32_ADS      = &(SCU->PCDADS);

            if (fe_GPIO == GPIOD)
            {
                GPIO_Init->Pin <<= 16;

                lu32_SEL1 = &(SCU->PDSEL1);

            }
            else
            {
                lu32_SEL1 = &(SCU->PCSEL1);
                lu32_SEL2 = &(SCU->PCSEL2);
            }
        }break;

        default: break;
    }

    /* Configure Select pins */
    while ((GPIO_Init->Pin) >> lu32_Position != 0)
    {
        /* Get current pin position */
        lu32_Current_Pin = (GPIO_Init->Pin) & (1uL << lu32_Position);

        if (lu32_Current_Pin)
        {
            switch (GPIO_Init->Mode)
            {
                /* GPIO IN Function */
                case GPIO_MODE_INPUT:
                {
                    GPIOx->DIR &= ~lu32_Current_Pin;
                }break;

                /* GPIO OUT Function */
                case GPIO_MODE_OUTPUT_PP:
                case GPIO_MODE_OUTPUT_OD:
                {
                    GPIOx->DIR |= lu32_Current_Pin;
                }break;

                /* Alternate Function */
                case GPIO_MODE_AF_PP:
                case GPIO_MODE_AF_OD:
                {
                    /* Get Position Mask */
                    if (lu32_Position < 16)
                    {   /* GOIOA、GPIOC、GPIOE */
                        lu32_Position_Mask = lu32_Position;
                    }
                    else
                    {   /* GPIOB、GPIOD、GPIOF */
                        lu32_Position_Mask = lu32_Position - 16;
                    }

                    /* SET GPIO Function */
                    if (lu32_Position_Mask < 8)
                    {
                        *lu32_SEL1 = (*lu32_SEL1 & ~(0xF << (lu32_Position_Mask * 4))) | (GPIO_Init->Alternate << (lu32_Position_Mask * 4));
                    }
                    else
                    {
                        *lu32_SEL2 = (*lu32_SEL2 & ~(0xF << ((lu32_Position_Mask - 8) * 4))) | (GPIO_Init->Alternate << ((lu32_Position_Mask - 8) * 4));
                    }
                }break;

                /* GPIO INT Function */
                case GPIO_MODE_IT_RISING:
                case GPIO_MODE_IT_FALLING:
                case GPIO_MODE_IT_RISING_FALLING:
                case GPIO_MODE_IT_HIGH_LEVEL:
                case GPIO_MODE_IT_LOW_LEVEL:
                {
                    /* Set direction Input、Enable INT */
                    GPIOx->DIR &= ~lu32_Current_Pin;
                    GPIOx->IEN |=  lu32_Current_Pin;

                    /* Single edge */
                    if (GPIO_Init->Mode == GPIO_MODE_IT_RISING || GPIO_Init->Mode == GPIO_MODE_IT_FALLING)
                    {
                        /* edge trigger */
                        GPIOx->IS  &= ~lu32_Current_Pin;
                        /* Single trigger */
                        GPIOx->IBE &= ~lu32_Current_Pin;

                        if (GPIO_Init->Mode == GPIO_MODE_IT_RISING)
                        {
                            GPIOx->IEV |= lu32_Current_Pin;
                        }
                        else
                        {
                            GPIOx->IEV &= ~lu32_Current_Pin;
                        }
                    }

                    /* Double edge */
                    if (GPIO_Init->Mode == GPIO_MODE_IT_RISING_FALLING)
                    {
                        /* edge trigger */
                        GPIOx->IS  &= ~lu32_Current_Pin;
                        /* Double trigger */
                        GPIOx->IBE |=  lu32_Current_Pin;
                    }

                    /* LEVEL trigger */
                    if (GPIO_Init->Mode == GPIO_MODE_IT_HIGH_LEVEL || GPIO_Init->Mode == GPIO_MODE_IT_LOW_LEVEL)
                    {
                        /* LEVEL trigger */
                        GPIOx->IS |= lu32_Current_Pin;

                        if (GPIO_Init->Mode == GPIO_MODE_IT_HIGH_LEVEL)
                        {
                            GPIOx->IEV |= lu32_Current_Pin;
                        }
                        else
                        {
                            GPIOx->IEV &= ~lu32_Current_Pin;
                        }
                    }
                }break;

                default: break;
            }

            /* Set Pull UP or DOWN or NO */
            if (GPIO_Init->Pull == GPIO_NOPULL)
            {
                *lu32_PollUP   &= ~lu32_Current_Pin;
                *lu32_PollDown &= ~lu32_Current_Pin;
            }
            else if (GPIO_Init->Pull == GPIO_PULLUP)
            {
                *lu32_PollUP   |=  lu32_Current_Pin;
                *lu32_PollDown &= ~lu32_Current_Pin;
            }
            else if (GPIO_Init->Pull == GPIO_PULLDOWN)
            {
                *lu32_PollUP   &= ~lu32_Current_Pin;
                *lu32_PollDown |=  lu32_Current_Pin;
            }

            /* Set Open Drain Mode */
            if (GPIO_Init->Mode & GPIO_MODE_OD_MASK)
            {
                *lu32_ODEnable |= lu32_Current_Pin;
            }
            else
            {
                *lu32_ODEnable &= ~lu32_Current_Pin;
            }

            /* GPIO Function */
            if (GPIO_Init->Mode & GPIO_MODE_IO_MASK)
            {
                /* Get Position Mask */
                if (lu32_Position < 16)
                {   /* GOIOA、GPIOC、GPIOE */
                    lu32_Position_Mask = lu32_Position;
                }
                else
                {   /* GPIOB、GPIOD、GPIOF */
                    lu32_Position_Mask = lu32_Position - 16;
                }

                /* SET GPIO Function */
                if (lu32_Position_Mask < 8)
                {
                    *lu32_SEL1 = (*lu32_SEL1 & ~(0xF << (lu32_Position_Mask * 4))) | (GPIO_FUNCTION_0 << (lu32_Position_Mask * 4));
                }
                else
                {
                    *lu32_SEL2 = (*lu32_SEL2 & ~(0xF << ((lu32_Position_Mask - 8) * 4))) | (GPIO_FUNCTION_0 << ((lu32_Position_Mask - 8) * 4));
                }
            }

            /* SET Digital or Analog */
            if (GPIO_Init->Mode == GPIO_MODE_ANALOG)
            {
                *lu32_ADS |= lu32_Current_Pin;
            }
            else
            {
                *lu32_ADS &= ~lu32_Current_Pin;
            }
        }

        lu32_Position++;
    }
}

/*********************************************************************************
* Function    : HAL_GPIO_DeInit
* Description : De-initializes the GPIOx peripheral registers to their default reset values.
* Input       : fe_GPIO：to select the GPIO peripheral.
* Input       : fu32_Pin：specifies the port bit to be written.
                This parameter can be one of GPIO_PIN_x where x can be (0..15).
* Outpu       :
* Author      : Chris_Kyle                         Date : 2020
**********************************************************************************/
void HAL_GPIO_DeInit(enum_GPIOx_t fe_GPIO, uint32_t fu32_Pin)
{
    uint32_t lu32_Position = 0;
    uint32_t lu32_Current_Pin;
    uint32_t lu32_Position_Mask;

    volatile uint32_t *lu32_SEL1 = NULL;        // 指向 -> 管脚复用寄存器1
    volatile uint32_t *lu32_SEL2 = NULL;        // 指向 -> 管脚复用寄存器2
    volatile uint32_t *lu32_PollUP   = NULL;    // 指向 -> 上拉选择寄存器
    volatile uint32_t *lu32_PollDown = NULL;    // 指向 -> 下拉选择寄存器
    volatile uint32_t *lu32_ODEnable = NULL;    // 指向 -> 开漏使能寄存器
    volatile uint32_t *lu32_ADS      = NULL;    // 指向 -> 数字、模拟选择寄存器

    GPIO_TypeDef *GPIOx;

#if (USE_FULL_ASSERT == 1)
    /* Check the parameters */
    if (!IS_GPIO_ALL_INSTANCE(fe_GPIO))    return;
    if (!IS_GPIO_PIN(fu32_Pin))            return;
#endif

    switch (fe_GPIO)
    {
        case GPIOA:
        case GPIOB:
        {
            GPIOx = GPIOAB;

            System_Module_Enable(EN_GPIOAB);

            lu32_PollUP   = &(SCU->PABPUR);
            lu32_PollDown = &(SCU->PABPDR);
            lu32_ODEnable = &(SCU->PABODR);
            lu32_ADS      = &(SCU->PABADS);

            if (fe_GPIO == GPIOB)
            {
                fu32_Pin <<= 16;

                lu32_SEL1 = &(SCU->PBSEL1);
                lu32_SEL2 = &(SCU->PBSEL2);
            }
            else
            {
                lu32_SEL1 = &(SCU->PASEL1);
                lu32_SEL2 = &(SCU->PASEL2);
            }
        }break;

        case GPIOC:
        case GPIOD:
        {
            GPIOx = GPIOCD;

            System_Module_Enable(EN_GPIOCD);

            lu32_PollUP   = &(SCU->PCDPUR);
            lu32_PollDown = &(SCU->PCDPDR);
            lu32_ODEnable = &(SCU->PCDODR);
            lu32_ADS      = &(SCU->PCDADS);

            if (fe_GPIO == GPIOD)
            {
                fu32_Pin <<= 16;

                lu32_SEL1 = &(SCU->PDSEL1);
            }
            else
            {
                lu32_SEL1 = &(SCU->PCSEL1);
                lu32_SEL2 = &(SCU->PCSEL2);
            }
        }break;

        default: break;
    }

    /* Configure Select pins */
    while (fu32_Pin >> lu32_Position != 0)
    {
        /* Get current pin position */
        lu32_Current_Pin = fu32_Pin & (1uL << lu32_Position);

        if (lu32_Current_Pin)
        {
            /* GPIO IN Function */
            GPIOx->DIR &= ~lu32_Current_Pin;
            GPIOx->CLR |=  lu32_Current_Pin;

            /* Disable Enable INT */
            GPIOx->IEN &= ~lu32_Current_Pin;

            /* Clear trigger config */
            GPIOx->IS  &= ~lu32_Current_Pin;
            GPIOx->IBE &= ~lu32_Current_Pin;
            GPIOx->IEV &= ~lu32_Current_Pin;


            /* Get Position Mask */
            if (lu32_Position < 16)
            {   /* GOIOA、GPIOC、GPIOE */
                lu32_Position_Mask = lu32_Position;
            }
            else
            {   /* GPIOB、GPIOD、GPIOF */
                lu32_Position_Mask = lu32_Position - 16;
            }

            /* SET GPIO Function */
            if (lu32_Position_Mask < 8)
            {
                *lu32_SEL1 &= ~(0xF << (lu32_Position_Mask * 4));
            }
            else
            {
                *lu32_SEL2 &= ~(0xF << ((lu32_Position_Mask - 8) * 4));
            }

            /* NO Pull */
            *lu32_PollUP   &= ~lu32_Current_Pin;
            *lu32_PollDown &= ~lu32_Current_Pin;

            /* Not Open Drain */
            *lu32_ODEnable &= ~lu32_Current_Pin;

            /* Analog Mode */
            *lu32_ADS |= lu32_Current_Pin;
        }

        lu32_Position++;
    }
}

/*********************************************************************************
* Function    : HAL_GPIO_AnalogEnable
* Description : Quickly Configure to analog function
* Input       : fe_GPIO：to select the GPIO peripheral.
* Input       : fu32_Pin：specifies the port bit to be written.
                This parameter can be one of GPIO_PIN_x where x can be (0..15).
* Outpu       :
* Author      : Chris_Kyle                         Date : 2020年
**********************************************************************************/
void HAL_GPIO_AnalogEnable(enum_GPIOx_t fe_GPIO, uint32_t fu32_Pin)
{
    uint32_t lu32_Position = 0;
    uint32_t lu32_Current_Pin;

    volatile uint32_t *lp32_ADS = NULL;    // 指向 -> 数字、模拟选择寄存器

#if (USE_FULL_ASSERT == 1)
    /* Check the parameters */
    if (!IS_GPIO_ALL_INSTANCE(fe_GPIO))      return;
    if (!IS_GPIO_PIN(fu32_Pin))              return;
#endif

    switch (fe_GPIO)
    {
        case GPIOA:
        case GPIOB:
        {
            System_Module_Enable(EN_GPIOAB);

            lp32_ADS = &(SCU->PABADS);

            if (fe_GPIO == GPIOB)
            {
                fu32_Pin <<= 16;
            }
        }break;

        case GPIOC:
        case GPIOD:
        {
            System_Module_Enable(EN_GPIOCD);

            lp32_ADS = &(SCU->PCDADS);

            if (fe_GPIO == GPIOD)
            {
                fu32_Pin <<= 16;
            }
        }break;


        default: break;
    }

    /* Configure Select pins */
    while ((fu32_Pin) >> lu32_Position != 0)
    {
        /* Get current pin position */
        lu32_Current_Pin = (fu32_Pin) & (1uL << lu32_Position);

        if (lu32_Current_Pin)
        {
            *lp32_ADS |= lu32_Current_Pin;
        }

        lu32_Position++;
    }
}

/*********************************************************************************
* Function    : HAL_GPIO_WritePin
* Description : Set or clear the selected data port bit.
* Input       :
* Outpu       :
* Author      : Chris_Kyle                         Date : 2020年
**********************************************************************************/
void HAL_GPIO_WritePin(enum_GPIOx_t fe_GPIO, uint32_t fu32_GPIO_Pin, enum_PinState_t fe_PinState)
{
    GPIO_TypeDef *GPIOx;

#if (USE_FULL_ASSERT == 1)
    /* Check the parameters */
    if (!IS_GPIO_ALL_INSTANCE(fe_GPIO))      return;
    if (!IS_GPIO_PIN(fu32_GPIO_Pin))         return;
    if (!IS_GPIO_PIN_ACTION(fe_PinState))    return;
#endif

    switch (fe_GPIO)
    {
        case GPIOA:
        case GPIOB:
        {
            GPIOx = GPIOAB;
        }break;

        case GPIOC:
        case GPIOD:
        {
            GPIOx = GPIOCD;
        }break;

        default: break;
    }

    if (fe_GPIO == GPIOB || fe_GPIO == GPIOD )
    {
        fu32_GPIO_Pin <<= 16;
    }

    if (GPIO_PIN_SET == fe_PinState)
    {
        GPIOx->ODATA |= fu32_GPIO_Pin;
    }
    else
    {
        GPIOx->ODATA &= ~fu32_GPIO_Pin;
    }
}

/*********************************************************************************
* Function    : HAL_GPIO_ReadPin
* Description : Read the specified input port pin.
* Input       :
* Outpu       :
* Author      : Chris_Kyle                         Date : 2020年
**********************************************************************************/
enum_PinState_t HAL_GPIO_ReadPin(enum_GPIOx_t fe_GPIO, uint32_t fu32_GPIO_Pin)
{
    GPIO_TypeDef *GPIOx;

    switch (fe_GPIO)
    {
        case GPIOA:
        case GPIOB:
        {
            GPIOx = GPIOAB;
        }break;

        case GPIOC:
        case GPIOD:
        {
            GPIOx = GPIOCD;
        }break;

        default: break;
    }

    if (fe_GPIO == GPIOB || fe_GPIO == GPIOD )
    {
        fu32_GPIO_Pin <<= 16;
    }

    if (GPIOx->IDATA & fu32_GPIO_Pin)
    {
        return GPIO_PIN_SET;
    }
    else
    {
        return GPIO_PIN_CLEAR;
    }
}

