/**
  ******************************************************************************
  * @file               ft32f4xx_gpio.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the GPIO peripheral:
  *                 + Initialization and Configuration functions
  *                 + GPIO Read and Write functions
  *                 + GPIO Alternate functions configuration functions
  * @version            V1.0.0
  * @date                   2025-03-27
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_gpio.h"
#include "ft32f4xx_rcc.h"

/**
  * @brief  Deinitializes the GPIOx peripheral registers to their default reset
  *         values.
  * @param  GPIOx: where x can be (A, B, C, D, E or H) to select the GPIO peripheral.
  * @retval None
  */
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    if (GPIOx == GPIOA)
    {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA, DISABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOB, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOB, DISABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOC, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOC, DISABLE);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOD, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOD, DISABLE);
    }
    else if (GPIOx == GPIOE)
    {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOE, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOE, DISABLE);
    }
    else if (GPIOx == GPIOH)
    {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOH, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOH, DISABLE);
    }
}

/**
  * @brief  Initializes the GPIOx peripheral according to the specified
  *         parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A, B, C, D, E or H) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint32_t pinpos = 0x00, pos = 0x00, currentpin = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
    assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
    assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

    /*-------------------------- Configure the port pins -----------------------*/
    /*-- GPIO Mode Configuration --*/
    for (pinpos = 0x00; pinpos < 0x10; pinpos++)
    {
        pos = ((uint32_t)0x01) << pinpos;

        /* Get the port pins position */
        currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

        if (currentpin == pos)
        {
            if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
            {
                /* Check Speed mode parameters */
                assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));

                /* Speed mode configuration */
                GPIOx->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR0 << (pinpos * 2));
                GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

                /* Check Output mode parameters */
                assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));

                /* Output mode configuration */
                GPIOx->OTYPER &= ~((GPIO_OTYPER_OT0) << ((uint16_t)pinpos));
                GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
            }

            GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));

            GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

            /* Pull-up Pull down resistor configuration */
            GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
            GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
        }
    }
}

/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
    /* Reset GPIO init structure parameters values */
    GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
    GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct->GPIO_Speed = GPIO_Speed_Level_0;
    GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
}

/**
  * @brief  Locks GPIO Pins configuration registers.
  * @note   The locked registers are GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR,
  *         GPIOx_PUPDR, GPIOx_AFRL and GPIOx_AFRH.
  * @note   The configuration of the locked GPIO pins can no longer be modified
  *         until the next device reset.
  * @param  GPIOx: where x can be (A, B, C, D, E or H) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0,1) for GPIOH.
  * @retval None
  */
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    __IO uint32_t tmp = 0x00010000;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    tmp |= GPIO_Pin;
    /* Set LCKK bit */
    GPIOx->LCKR = tmp;
    /* Reset LCKK bit */
    GPIOx->LCKR = GPIO_Pin;
    /* Set LCKK bit */
    GPIOx->LCKR = tmp;
    /* Read LCKK bit */
    tmp = GPIOx->LCKR;
    /* Read LCKK bit */
    tmp = GPIOx->LCKR;
}
/**
  * @}
  */

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A, B, C, D, E or H) to select the GPIO peripheral.

  * @param  GPIO_Pin: specifies the port bit to read.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0,1) for GPIOH.
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A, B, C, D, E or H) to select the GPIO peripheral.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0,1) for GPIOH.
  * @retval The input port pin value.
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    return ((uint16_t)GPIOx->IDR);
}

/**
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: where x can be (A, B, C, D, E or H) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the port bit to read.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0,1) for GPIOH.
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if ((GPIOx->ODR & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

/**
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: where x can be (A, B, C, D, E or H) to select the GPIO peripheral.
  * @retval GPIO output data port value.
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    return ((uint16_t)GPIOx->ODR);
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (A, B, C, D, E or H) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0..1) for GPIOH.
  * @retval None
  */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->BSRR = GPIO_Pin;
}

/**
  * @brief  Clears the selected data port bits.
  * @param  GPIOx: where x can be (A, B, C, D, E or H) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0..1) for GPIOH.
  * @retval None
  */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
}

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIOx: where x can be (A, B, C, D, E or H) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0,1) for GPIOH.
  * @param  BitVal: specifies the value to be written to the selected bit.
  *          This parameter can be one of the BitAction enumeration values:
  *            @arg Bit_RESET: to clear the port pin
  *            @arg Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    assert_param(IS_GPIO_BIT_ACTION(BitVal));

    if (BitVal != Bit_RESET)
    {
        GPIOx->BSRR = GPIO_Pin;
    }
    else
    {
        GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
    }
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (A, B, C, D, E or H) to select the GPIO peripheral.
  * @param  PortVal: specifies the value to be written to the port output data register.
  * @retval None
  */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIOx->ODR = PortVal;
}

/**
  * @}
  */


/**
  * @brief  Set GPIO port for alternate function.
  * @param  GPIOx: where x can be (A, B, C, D, E or H) to select the GPIO peripheral.
  * @param  GPIO_PinSource: specifies the pin for the Alternate function.
  *          This parameter can be GPIO_PinSourcex where x can be (0..15) for GPIOA, GPIOB, GPIOD, GPIOE
  *          and (0..12) for GPIOC.
  * @param  GPIO_AF: selects the pin to used as Alternate function.
  *          This parameter can be one of the following value:
  *            @arg GPIO_AF_0:  SYS
  *            @arg GPIO_AF_1:  TIM1/2, LPTIM
  *            @arg GPIO_AF_2:  TIM3/4/5
  *            @arg GPIO_AF_3:  TIM8/9/10/11, CRS
  *            @arg GPIO_AF_4:  I2C1/2/3, SPI3, I2S3
  *            @arg GPIO_AF_5:  SPI1/2, I2S2
  *            @arg GPIO_AF_6:  SPI3, I2S2, SDIO
  *            @arg GPIO_AF_7:  USART1/2/3, UART7
  *            @arg GPIO_AF_8:  UART4/5, LPUART, USART6, COMP1/2/3/4/5/6
  *            @arg GPIO_AF_9:  CAN1/2/3/4, TIM12/13/14
  *            @arg GPIO_AF_10: OTG_FS, QUADSPI
  *            @arg GPIO_AF_11: ETH,
  *            @arg GPIO_AF_12: OTH_HS, FMC
  *            @arg GPIO_AF_13: SSI, SPDIF
  *            @arg GPIO_AF_14: EPWM, EQEP, ECAP
  *            @arg GPIO_AF_15: EVENTOUT
  * @note   The pin should already been configured in Alternate Function mode(AF)
  *         using GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
  * @note   Refer to the Alternate function mapping table in the device datasheet
  *         for the detailed mapping of the system and peripherals'alternate
  *         function I/O pins.
  * @retval None
  */
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
    uint32_t temp = 0x00;
    uint32_t temp_2 = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
    assert_param(IS_GPIO_AF(GPIO_AF));

    temp = ((uint32_t)(GPIO_AF) << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4));
    GPIOx->AFR[GPIO_PinSource >> 0x03] &= ~((uint32_t)(0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07)) * 4));
    temp_2 = GPIOx->AFR[GPIO_PinSource >> 0x03] | temp;
    GPIOx->AFR[GPIO_PinSource >> 0x03] = temp_2;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE*******************/
