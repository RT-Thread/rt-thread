/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-20     tfx2001      first version
 */

#ifdef PKG_USING_TINYUSB

#include <tusb.h>
#include <drv_config.h>

int tusb_board_init(void)
{
    PCD_HandleTypeDef hpcd;

    memset(&hpcd, 0, sizeof(hpcd));
    /* Set LL Driver parameters */
    hpcd.Instance = USBD_INSTANCE;
    hpcd.Init.dev_endpoints = 8;
    hpcd.Init.speed = USBD_PCD_SPEED;
#if defined(SOC_SERIES_STM32F3) || defined(SOC_SERIES_STM32F4)
    hpcd.Init.ep0_mps = EP_MPS_64;
#else
    hpcd.Init.ep0_mps = DEP0CTL_MPS_64;
#endif
#if !defined(SOC_SERIES_STM32F1)
    hpcd.Init.phy_itface = USBD_PCD_PHY_MODULE;
#endif
    /* Initialize LL Driver */
    HAL_PCD_Init(&hpcd);
    /* USB interrupt Init */
    HAL_NVIC_SetPriority(USBD_IRQ_TYPE, 2, 0);
    HAL_NVIC_EnableIRQ(USBD_IRQ_TYPE);
    return 0;
}

void USBD_IRQ_HANDLER(void)
{
    tud_int_handler(0);
}

#endif
