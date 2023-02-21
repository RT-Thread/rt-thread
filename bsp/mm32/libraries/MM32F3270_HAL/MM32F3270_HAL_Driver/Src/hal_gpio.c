/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_gpio.h"

void GPIO_Init(GPIO_Type  * GPIOx, GPIO_Init_Type * init)
{
    uint8_t idx;
    uint8_t i;
    uint32_t pin;
    __IO uint32_t * addr;

    /* 1x. */
    uint32_t dat = init->PinMode & 0xFu;
    if (init->PinMode & 0x10u)
    {
        dat |= init->Speed;
    }

    /* 0x. */
    addr = &(GPIOx->CRL);
    for (i = 0u; i < 8u; i++)
    {
        idx = i * 4u;
        if ( (init->Pins) & (1u << i) )
        {
            *addr = ( *addr  & ~(0xFu << idx) ) | (dat << idx);
        }
    }

    addr = &(GPIOx->CRH);
    pin = init->Pins >> 8u;
    for (i = 0u; i < 8u; i++)
    {
        idx = i * 4u;
        if ( pin & (1u << i) )
        {
            *addr  = ( *addr  & ~(0xFu << idx) ) | (dat << idx);
        }
    }

    /* 2x,4x. */
    if (init->PinMode == GPIO_PinMode_In_PullDown)
    {
        GPIOx->BRR |= init->Pins;
    }
    else if (init->PinMode == GPIO_PinMode_In_PullUp)
    {
        GPIOx->BSRR |= init->Pins;
    }
}

bool GPIO_ReadInDataBit(GPIO_Type  * GPIOx, uint16_t pin)
{
    return (GPIOx->IDR & pin);
}

uint16_t GPIO_ReadInData(GPIO_Type * GPIOx)
{
    return (uint16_t)(GPIOx->IDR);
}

bool GPIO_ReadOutDataBit(GPIO_Type * GPIOx, uint16_t pins)
{
    return (GPIOx->ODR & pins);
}

uint16_t GPIO_ReadOutData(GPIO_Type * GPIOx)
{
    return (uint16_t)GPIOx->ODR;
}

void GPIO_SetBits(GPIO_Type * GPIOx, uint16_t pins)
{
    GPIOx->BSRR = pins;
}

void GPIO_ClearBits(GPIO_Type * GPIOx, uint16_t pins)
{
    GPIOx->BRR = pins;
}

void GPIO_WriteBit(GPIO_Type * GPIOx, uint16_t pins, uint16_t val)
{
    (val != 0u) ? (GPIOx->BSRR = pins) : (GPIOx->BRR = pins);
}

void GPIO_WriteBits(GPIO_Type * GPIOx, uint16_t val)
{
    GPIOx->ODR = val;
}

void GPIO_PinLock(GPIO_Type * GPIOx, uint16_t pins, bool enable_lock)
{
    (enable_lock) ? (GPIOx->LCKR |= pins) : (GPIOx->LCKR &= ~pins);
}

void GPIO_PinLockConf(GPIO_Type * GPIOx, uint16_t pins)
{
    GPIOx->LCKR = GPIO_LCKR_LCKK_MASK | GPIO_LCKR_LCK(pins);
    GPIOx->LCKR = pins;
    GPIOx->LCKR = GPIO_LCKR_LCKK_MASK | GPIO_LCKR_LCK(pins);
    GPIOx->LCKR;
    GPIOx->LCKR;
}

void GPIO_PinAFConf(GPIO_Type * GPIOx, uint16_t pins, uint8_t af)
{
    uint32_t shift = 0u;
    uint32_t idx = 0u;
    uint32_t val = GPIOx->AFRL;
    while (idx < 8u)
    {
        if ( ( (1u << idx) & pins) != 0u )
        {
            shift = idx * 4u;
            val &= ~(0xFu << shift);
            val |= (uint32_t)af << shift;
        }
        idx++;
    }
    GPIOx->AFRL = val;

    val = GPIOx->AFRH;
    while (idx < 16u)
    {
        if ( ( (1u << idx) & pins) != 0u )
        {
            shift = (idx - 8u) * 4u;
            val &= ~(0xFu << shift);
            val |= (uint32_t)af << shift;
        }
        idx++;
    }
    GPIOx->AFRH = val;
}

void GPIO_PortAFConfig(GPIO_Type * GPIOx, uint32_t af_high, uint32_t af_low)
{
    GPIOx->AFRL = af_low;
    GPIOx->AFRH = af_high;
}

/* EOF. */

