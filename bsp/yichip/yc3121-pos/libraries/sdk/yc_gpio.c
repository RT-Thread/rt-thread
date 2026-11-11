/*
File Name    : yc_gpio.c
Author       : Yichip
Version      : V1.0
Date         : 2019/12/03
Description  : gpio encapsulation.
*/

#include "yc_gpio.h"

void GPIO_Config(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin, GPIO_FunTypeDef function)
{
    _ASSERT(ISGPIOGROUP(GPIOx));
    _ASSERT(IS_GET_GPIO_PIN(GPIO_Pin));

    int i;

    for (i = 0; i < GPIO_PIN_NUM; i++)
    {
        if (GPIO_Pin & 1 << i)
            GPIO_CONFIG(GPIOx * GPIO_PIN_NUM + i) = function;
    }
}

void GPIO_Init(GPIO_TypeDef GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)
{
    _ASSERT(ISGPIOGROUP(GPIOx));
    _ASSERT(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
    _ASSERT(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));

    int i;

    switch (GPIO_InitStruct->GPIO_Mode)
    {
    case GPIO_Mode_IN_FLOATING:
        for (i = 0; i < GPIO_PIN_NUM; i++)
        {
            if (GPIO_InitStruct->GPIO_Pin & 1 << i)
                GPIO_CONFIG(GPIOx * GPIO_PIN_NUM + i) = 0x00;
        }
        break;

    case GPIO_Mode_IPU:
        for (i = 0; i < GPIO_PIN_NUM; i++)
        {
            if (GPIO_InitStruct->GPIO_Pin & 1 << i)
                GPIO_CONFIG(GPIOx * GPIO_PIN_NUM + i) = 0x40;
        }
        break;

    case GPIO_Mode_IPD:
        for (i = 0; i < GPIO_PIN_NUM; i++)
        {
            if (GPIO_InitStruct->GPIO_Pin & 1 << i)
                GPIO_CONFIG(GPIOx * GPIO_PIN_NUM + i) = 0x80;
        }
        break;

    case GPIO_Mode_AIN:
        for (i = 0; i < GPIO_PIN_NUM; i++)
        {
            if (GPIO_InitStruct->GPIO_Pin & 1 << i)
                GPIO_CONFIG(GPIOx * GPIO_PIN_NUM + i) = 0xC0;
        }
        break;

    case GPIO_Mode_Out_PP:
        for (i = 0; i < GPIO_PIN_NUM; i++)
        {
            if (GPIO_InitStruct->GPIO_Pin & 1 << i)
                GPIO_CONFIG(GPIOx * GPIO_PIN_NUM + i) = 0x3E;
        }
        break;

    default:
        break;
    }
}

void GPIO_PullUpCmd(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin, FunctionalState NewState)
{
    _ASSERT(ISGPIOGROUP(GPIOx));
    _ASSERT(IS_GET_GPIO_PIN(GPIO_Pin));

    int i;

    for (i = 0; i < GPIO_PIN_NUM; i++)
    {
        if (GPIO_Pin & 1 << i)
        {
            if (NewState == ENABLE)
            {
                GPIO_CONFIG(GPIOx * GPIO_PIN_NUM + i) |= 1 << 6;
            }
            else if (NewState == DISABLE)
            {
                GPIO_CONFIG(GPIOx * GPIO_PIN_NUM + i) &= ~(1 << 6);
            }
        }
    }
}

uint16_t GPIO_ReadInputData(GPIO_TypeDef GPIOx)
{
    _ASSERT(ISGPIOGROUP(GPIOx));

    return GPIO_IN(GPIOx);
}

uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin)
{
    _ASSERT(ISGPIOGROUP(GPIOx));
    _ASSERT(IS_GET_GPIO_PIN(GPIO_Pin));

    if (GPIO_IN(GPIOx) & GPIO_Pin)
    {
        return (uint8_t)0x01;
    }
    else
    {
        return (uint8_t)0x00;
    }
}

uint16_t GPIO_ReadOutputData(GPIO_TypeDef GPIOx)
{
    _ASSERT(ISGPIOGROUP(GPIOx));

    return GPIO_IN(GPIOx);
}

uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin)
{
    _ASSERT(ISGPIOGROUP(GPIOx));
    _ASSERT(IS_GET_GPIO_PIN(GPIO_Pin));

    if (GPIO_IN(GPIOx) & GPIO_Pin)
    {
        return (uint8_t)0x01;
    }
    else
    {
        return (uint8_t)0x00;
    }
}

void GPIO_ResetBits(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin)
{
    _ASSERT(ISGPIOGROUP(GPIOx));
    _ASSERT(IS_GET_GPIO_PIN(GPIO_Pin));

    int i;
    uint8_t Temp;

    for (i = 0; i < GPIO_PIN_NUM; i++)
    {
        if (GPIO_Pin & 1 << i)
        {
            Temp = GPIO_CONFIG(GPIOx * GPIO_PIN_NUM + i);
            Temp |= 0x3F; //00111111
            Temp &= 0xFE; //11111110
            GPIO_CONFIG(GPIOx * GPIO_PIN_NUM + i) = Temp;
        }
    }
}

void GPIO_SetBits(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin)
{
    _ASSERT(ISGPIOGROUP(GPIOx));
    _ASSERT(IS_GET_GPIO_PIN(GPIO_Pin));

    int i;

    for (i = 0; i < GPIO_PIN_NUM; i++)
    {
        if (GPIO_Pin & 1 << i)
            GPIO_CONFIG(GPIOx * GPIO_PIN_NUM + i) |= 0x3F; //00111111
    }
}

void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct)
{
    GPIO_InitStruct->GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN_FLOATING;
}

void GPIO_Write(GPIO_TypeDef GPIOx, uint16_t value)
{
    _ASSERT(ISGPIOGROUP(GPIOx));

    int i;

    for (i = 0; i < GPIO_PIN_NUM; i++)
    {
        if (BIT_GET(value, i))
            GPIO_SetBits(GPIOx, 1 << i);
        else
            GPIO_ResetBits(GPIOx, 1 << i);
    }
}

void GPIO_WriteBit(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
    _ASSERT(ISGPIOGROUP(GPIOx));
    _ASSERT(IS_GET_GPIO_PIN(GPIO_Pin));

    if (BitVal == Bit_SET)
        GPIO_SetBits(GPIOx, GPIO_Pin);
    else if (BitVal == Bit_RESET)
        GPIO_ResetBits(GPIOx, GPIO_Pin);
}
