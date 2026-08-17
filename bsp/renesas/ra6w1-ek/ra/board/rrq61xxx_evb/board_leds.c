/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BOARD_RRQ61XXX_EVB_LEDS
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#if defined(BOARD_RRQ61XXX_EVB)
 #include "bsp_pin_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/** Array of LED GPIO pins.
 * @note In this board any GPIO can be used as an LED. For enabling an LED, a jumper wire must be connected
 *       between a GPIO and one of the pins of J611. Then, through the Pin Configurator of E2S, the
 *       BSP_GPIO_LED_<X> 'Symbolic Name' must be assigned to the corresponding GPIO.
 */
static const uint16_t g_bsp_prv_leds[] =
{
 #if defined(BSP_GPIO_LED_0)
    (uint16_t) BSP_GPIO_LED_0,         ///< LED0
 #endif
 #if defined(BSP_GPIO_LED_1)
    (uint16_t) BSP_GPIO_LED_1,         ///< LED1
 #endif
 #if defined(BSP_GPIO_LED_2)
    (uint16_t) BSP_GPIO_LED_2,         ///< LED2
 #endif
 #if defined(BSP_GPIO_LED_3)
    (uint16_t) BSP_GPIO_LED_3,         ///< LED3
 #endif
};

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/** Structure with LED information for this board. */

const bsp_leds_t g_bsp_leds =
{
    .led_count = (uint16_t) FSP_ARRAY_LENGTH(g_bsp_prv_leds),
    .p_leds    = &g_bsp_prv_leds[0]
};

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

#endif

/** @} (end addtogroup BOARD_RRQ61XXX_EVB_LEDS) */
