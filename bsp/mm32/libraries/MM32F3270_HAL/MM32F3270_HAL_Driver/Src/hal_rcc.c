/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "hal_common.h"
#include "hal_rcc.h"

void RCC_EnableAHB1Periphs(uint32_t ahb1_periphs, bool enable)
{
    (enable) ? (RCC->AHB1ENR |= ahb1_periphs) : (RCC->AHB1ENR &= ~ahb1_periphs);
}

void RCC_EnableAHB2Periphs(uint32_t ahb2_periphs, bool enable)
{
    (enable) ? (RCC->AHB2ENR |= ahb2_periphs) : (RCC->AHB2ENR &= ~ahb2_periphs);
}

void RCC_EnableAHB3Periphs(uint32_t ahb3_periphs, bool enable)
{
    (enable) ? (RCC->AHB3ENR |= ahb3_periphs) : (RCC->AHB3ENR &= ~ahb3_periphs);
}

void RCC_EnableAPB1Periphs(uint32_t apb1_periphs, bool enable)
{
    (enable) ? (RCC->APB1ENR |= apb1_periphs) : (RCC->APB1ENR &= ~apb1_periphs);
}

void RCC_EnableAPB2Periphs(uint32_t apb2_periphs, bool enable)
{
    (enable) ? (RCC->APB2ENR |= apb2_periphs) : (RCC->APB2ENR &= ~apb2_periphs);
}

void RCC_ResetAHB1Periphs(uint32_t ahb1_periphs)
{
    RCC->AHB1RSTR |= ahb1_periphs;
    RCC->AHB1RSTR &= ~ahb1_periphs;
}

void RCC_ResetAHB2Periphs(uint32_t ahb2_periphs)
{
    RCC->AHB2RSTR |= ahb2_periphs;
    RCC->AHB2RSTR &= ~ahb2_periphs;
}

void RCC_ResetAHB3Periphs(uint32_t ahb3_periphs)
{
    RCC->AHB3RSTR |= ahb3_periphs;
    RCC->AHB3RSTR &= ~ahb3_periphs;
}

void RCC_ResetAPB1Periphs(uint32_t apb1_periphs)
{
    RCC->APB1RSTR |= apb1_periphs;
    RCC->APB1RSTR &= ~apb1_periphs;
}

void RCC_ResetAPB2Periphs(uint32_t apb2_periphs)
{
    RCC->APB2RSTR |= apb2_periphs;
    RCC->APB2RSTR &= ~apb2_periphs;
}

void RCC_MCOConf(RCC_MCO_Type source)
{
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_MCO_MASK) | RCC_CFGR_MCO(source);
}

/* EOF. */
