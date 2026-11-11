/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     yc_gpio.c
 * @brief    source file for setting gpio
 *
 * Change Logs:
 * Date            Author             Version        Notes
 * 2021-01-20      yangzhengfeng      V1.0.2         Update library function
 * 2021-07-29      xubo               V1.0.3         Update library function
 */

#include "yc_gpio.h"

uint8_t const  UnMapTb[256] = {
    0u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x00 to 0x0F */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x10 to 0x1F */
    5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x20 to 0x2F */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x30 to 0x3F */
    6u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x40 to 0x4F */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x50 to 0x5F */
    5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x60 to 0x6F */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x70 to 0x7F */
    7u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x80 to 0x8F */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0x90 to 0x9F */
    5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xA0 to 0xAF */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xB0 to 0xBF */
    6u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xC0 to 0xCF */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xD0 to 0xDF */
    5u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, /* 0xE0 to 0xEF */
    4u, 0u, 1u, 0u, 2u, 0u, 1u, 0u, 3u, 0u, 1u, 0u, 2u, 0u, 1u, 0u  /* 0xF0 to 0xFF */
};

uint8_t UnMap(uint16_t x)
{
    uint8_t lx = x;
    uint8_t hx = x >> 8;
    if(lx)
    {
        return  UnMapTb[lx];
    }
    else
    {
        return  UnMapTb[hx] + 8;
    }
}

/**
 * @method GPIO_Config
 * @brief  config gpio function(Only one can be configured at a time)
 * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
 * @param  GPIO_Pin: select the pin to read.(GPIO_Pin_0...GPIO_Pin_15)(Only one can be configured at a time)
 * @param  function:gpio function
 * @retval none
 */
void GPIO_Config(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin, GPIO_FUN_TYPEDEF function)
{
    _ASSERT(IS_GPIO_PORT(GPIOx));
    _ASSERT(IS_GPIO_PIN_SINGLE(GPIO_Pin));
    _ASSERT(IS_GPIO_FUN(function));

    MGPIO->CTRL.reg[GPIO_GetNum(GPIOx, GPIO_Pin)] = function;
}

/**
 * @method GPIO_Init
 * @brief  gpio mode Init
 * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
 * @param  GPIO_InitStruct:GPIO_InitStruct
 * @retval none
 */
void GPIO_Init(GPIO_TypeDef GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    _ASSERT(IS_GPIO_PORT(GPIOx));
    _ASSERT(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
    _ASSERT(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));

    for(uint8_t i = 0; i < GPIO_PIN_NUM; i++)
    {
        if(GPIO_InitStruct->GPIO_Pin & (BIT0<<i))
        {
            MGPIO->CTRL.reg[GPIO_GetNum(GPIOx, (BIT0<<i))] = GPIO_InitStruct->GPIO_Mode << 6;
        }
    }
}

/**
 * @method GPIO_PullUpCmd
 * @brief  gpio pull up
 * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
 * @param  GPIO_Pin:  select the pin to read.(GPIO_Pin_0...GPIO_Pin_7)
 * @param  NewState: new state of the port pin Pull Up.(ENABLE or DISABLE)
 * @retval none
 */
void GPIO_PullUpCmd(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin, FunctionalState NewState)
{
    _ASSERT(IS_GPIO_PORT(GPIOx));
    _ASSERT(IS_GPIO_PIN(GPIO_Pin));
    _ASSERT(IS_FUNCTIONAL_STATE(NewState));
    uint8_t i = 0;

    if (ENABLE == NewState)
    {
        for(i = 0; i<GPIO_PIN_NUM; i++)
        {
            MGPIO->CTRL.bit[GPIO_GetNum(GPIOx,(GPIO_Pin_TypeDef)(BIT0 << i))].MODE = GPIO_Mode_IPU;
        }
    }
    else if (DISABLE == NewState)
    {
        for(i = 0; i<GPIO_PIN_NUM; i++)
        {
            MGPIO->CTRL.bit[GPIO_GetNum(GPIOx, (GPIO_Pin_TypeDef)(BIT0 << i))].MODE = GPIO_Mode_IN_FLOATING;
        }
    }
}

/**
 * @method GPIO_ReadInputData
 * @brief  Reads the GPIO input data for 2byte.
 * @param  GPIOx_IN: where x can be (GPIOA_IN...GPIOF_IN) to select the GPIO group.
 * @retval GPIO input data.
 */
uint16_t GPIO_ReadInputData(GPIO_TypeDef GPIOx)
{
    _ASSERT(IS_GPIO_PORT(GPIOx));

    return MGPIO->IN_LEVEL.reg[GPIOx];
}

/**
 * @method GPIO_ReadInputDataBit
 * @brief  Reads the GPIO input data(status) for bit.
 * @param  GPIOx_IN: where x can be (GPIOA_IN...GPIOF_IN) to select the GPIO group.
 * @param  GPIO_Pin:  select the pin to read.(GPIO_Pin_0...GPIO_Pin_15)
 * @retval The input bit
 */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
{
    _ASSERT(IS_GPIO_PORT(GPIOx));
    _ASSERT(IS_GPIO_PIN_SINGLE(GPIO_Pin));

    if (((MGPIO->IN_LEVEL.reg[GPIOx]) & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        return (uint8_t)Bit_SET;
    }
    return (uint8_t)Bit_RESET;
}

/**
 * @method GPIO_ReadOutputData
 * @brief  Reads the GPIO output data(status) for byte.
 * @param  GPIOx: where x can be (GPIOA...GPIOE) to select the GPIO group.
 * @retval GPIO output data(status).
 */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef GPIOx)
{
    _ASSERT(IS_GPIO_PORT(GPIOx));

    return MGPIO->IN_LEVEL.reg[GPIOx];
}

/**
 * @method GPIO_ReadOutputDataBit
 * @brief  Reads the GPIO output data(status) for bit.
 * @param  GPIOx: where x can be (GPIOA...GPIOF) to select the GPIO group.
 * @param  GPIO_Pin:  select the pin to read.(GPIO_Pin_0...GPIO_Pin_15)
 * @retval The output status
 */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
{
    _ASSERT(IS_GPIO_PORT(GPIOx));
    _ASSERT(IS_GPIO_PIN_SINGLE(GPIO_Pin));
    
    if (((MGPIO->IN_LEVEL.reg[GPIOx]) & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        return (uint8_t)Bit_SET;
    }
    return (uint8_t)Bit_RESET;
}

/**
 * @method GPIO_ResetBit
 * @brief  Reset the GPIO bit data(status) for bit.
 * @param  GPIOx: where x can be (GPIOA...GPIOE) to select the GPIO group.
 * @param  GPIO_Pin:  select the pin to reset.(GPIO_Pin_0...GPIO_Pin_15)
 * @retval none
 */
void GPIO_ResetBit(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
{
    _ASSERT(IS_GPIO_PORT(GPIOx));
    _ASSERT(IS_GPIO_PIN_SINGLE(GPIO_Pin));
    MGPIO->CTRL.reg[GPIO_GetNum(GPIOx, GPIO_Pin)]    = OUTPUT_LOW;
}
/**
 * @method GPIO_ResetBits
 * @brief  Reset the GPIO bit data(status) for bit.
 * @param  GPIOx: where x can be (GPIOA...GPIOE) to select the GPIO group.
 * @param  GPIO_Pin:  select the pin to reset.(GPIO_Pin_0...GPIO_Pin_15)
 * @retval none
 */
void GPIO_ResetBits(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin)
{
    _ASSERT(IS_GPIO_PORT(GPIOx));
    _ASSERT(IS_GPIO_PIN(GPIO_Pin));
    for(uint8_t i = 0; i < GPIO_PIN_NUM; i++)
    {
        if(GPIO_Pin & (BIT0<<i))
        {
            MGPIO->CTRL.reg[GPIO_GetNum(GPIOx, (BIT0<<i))]    = OUTPUT_LOW;
        }
    }
}

/**
 * @method GPIO_SetBit
 * @brief  Set the GPIO bit data(status) for bit.
 * @param  GPIOx: where x can be (GPIOA...GPIOE) to select the GPIO group.
 * @param  GPIO_Pin:  select the pin to read.(GPIO_Pin_0...GPIO_Pin_15)
 * @retval none
 */
void GPIO_SetBit(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
{
    _ASSERT(IS_GPIO_PORT(GPIOx));
    _ASSERT(IS_GPIO_PIN_SINGLE(GPIO_Pin));
    MGPIO->CTRL.reg[GPIO_GetNum(GPIOx, GPIO_Pin)]    = OUTPUT_HIGH;
}

/**
 * @method GPIO_SetBits
 * @brief  Set the GPIO bit data(status) for bit.
 * @param  GPIOx: where x can be (GPIOA...GPIOE) to select the GPIO group.
 * @param  GPIO_Pin:  select the pin to read.(GPIO_Pin_0...GPIO_Pin_15)
 * @retval none
 */
void GPIO_SetBits(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin)
{
    _ASSERT(IS_GPIO_PORT(GPIOx));
    _ASSERT(IS_GPIO_PIN(GPIO_Pin));
    for(uint8_t i = 0; i < GPIO_PIN_NUM; i++)
    {
        if(GPIO_Pin & (BIT0<<i))
        {
            MGPIO->CTRL.reg[GPIO_GetNum(GPIOx, (BIT0<<i))]    = OUTPUT_HIGH;
        }
    }
}

/**
 * @method GPIO_Write
 * @brief  Write the GPIO group data(status) for bit.
 * @param  GPIOx: where x can be (GPIOA...GPIOE) to select the GPIO group.
 * @param  value:  select the value to read.(0 or 1)
 * @retval none
 */
void GPIO_Write(GPIO_TypeDef  GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
{
    _ASSERT(IS_GPIO_PORT(GPIOx));
    _ASSERT(IS_GPIO_PIN(GPIO_Pin));
    GPIO_SetBits(GPIOx, GPIO_Pin);
    GPIO_ResetBits(GPIOx, (GPIO_Pin_TypeDef)(~GPIO_Pin));
}

/**
 * @method GPIO_WriteBit
 * @brief  Write the GPIO bit data(status) for bit.
 * @param  GPIOx: where x can be (GPIOA...GPIOE) to select the GPIO group.
 * @param  GPIO_Pin:  select the pin to read.(GPIO_Pin_0...GPIO_Pin_15)
 * @param  BitVal: select the value to read.(0 or 1)
 * @retval none
 */
void GPIO_WriteBit(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef GPIO_Pin, BitAction BitVal)
{
    _ASSERT(IS_GPIO_PORT(GPIOx));
    _ASSERT(IS_GPIO_PIN_SINGLE(GPIO_Pin));

    if (BitVal == Bit_SET)
        GPIO_SetBit(GPIOx, GPIO_Pin);
    else if (BitVal == Bit_RESET)
        GPIO_ResetBit(GPIOx, GPIO_Pin);
}


/**
 * @method GPIO_ODSet
 * @brief  Set the GPIO OD MODE
 * @param  GPIOx_Drv: where x can be (GPIOA_Drv...GPIOE_Drv) to select the GPIO_Drv group.
 * @param  GPIO_Pin:  select the pin to read.(GPIO_Pin_0...GPIO_Pin_15)
 * @param  Drvtype: select the value to set DRV value.(0x00....0x11)
 * @retval none
 */
void GPIO_ODSet(GPIO_OD_TypeDef GPIOx_OD, GPIO_ODTypeDef GPIO_OD_Set)
{
    _ASSERT(IS_GPIO_OD(GPIOx_OD));
    _ASSERT(IS_GPIO_MODE_OUT(GPIO_OD_Set));

    (MGPIO->OD_CTRL.reg) |= (GPIO_OD_Set << GPIOx_OD);
}
/************************ (C) COPYRIGHT Yichip Microelectronics *****END OF FILE****/
