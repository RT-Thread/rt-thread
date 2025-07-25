/*
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"

#if __has_include("stm32f0xx_hal.h")
#include "stm32f0xx_hal.h"
#elif __has_include("stm32f1xx_hal.h")
#include "stm32f1xx_hal.h"
#elif __has_include("stm32f3xx_hal.h")
#include "stm32f3xx_hal.h"
#elif __has_include("stm32g0xx_hal.h")
#include "stm32g0xx_hal.h"
#elif __has_include("stm32g4xx_hal.h")
#include "stm32g4xx_hal.h"
#elif __has_include("stm32l0xx_hal.h")
#include "stm32l0xx_hal.h"
#elif __has_include("stm32l1xx_hal.h")
#include "stm32l1xx_hal.h"
#elif __has_include("stm32l4xx_hal.h")
#include "stm32l4xx_hal.h"
#elif __has_include("stm32l5xx_hal.h")
#include "stm32l5xx_hal.h"
#endif

#if !defined(HAL_PCD_MODULE_ENABLED)
#error please define HAL_PCD_MODULE_ENABLED in stm32xxx_hal_conf.h
#endif

#ifndef CONFIG_USBDEV_FSDEV_PMA_ACCESS
#error "please define CONFIG_USBDEV_FSDEV_PMA_ACCESS in usb_config.h"
#endif

#if CONFIG_USBDEV_FSDEV_PMA_ACCESS != PMA_ACCESS
#error "CONFIG_USBDEV_FSDEV_PMA_ACCESS must be equal PMA_ACCESS"
#endif

struct fsdev_instance {
    USB_TypeDef *Instance;
};

static struct fsdev_instance g_fsdev_instance;

void usb_dc_low_level_init(uint8_t busid)
{
    g_fsdev_instance.Instance = (USB_TypeDef *)g_usbdev_bus[busid].reg_base;
    HAL_PCD_MspInit((PCD_HandleTypeDef *)&g_fsdev_instance);
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    g_fsdev_instance.Instance = (USB_TypeDef *)g_usbdev_bus[busid].reg_base;
    HAL_PCD_MspDeInit((PCD_HandleTypeDef *)&g_fsdev_instance);
}

void USB_IRQHandler(void)
{
    USBD_IRQHandler(0);
}

void USB_LP_IRQHandler(void)
{
    USBD_IRQHandler(0);
}