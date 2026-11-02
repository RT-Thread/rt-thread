/**
 * \addtogroup PLA_BSP_CONFIG
 * \{
 * \addtogroup PLA_BSP_CFG_BOARDS
 * \{
 */

/**
 ****************************************************************************************
 *
 * @file brd_io_config_ra6w1.h
 *
 * @brief Board Support Package. RA6W1 Board I/O configuration.
 *
 * Copyright (c) 2023-2024 Renesas Electronics. All rights reserved.
 *
 * This software ("Software") is owned by Renesas Electronics.
 *
 * By using this Software you agree that Renesas Electronics retains all
 * intellectual property and proprietary rights in and to this Software and any
 * use, reproduction, disclosure or distribution of the Software without express
 * written permission or a license agreement from Renesas Electronics is
 * strictly prohibited. This Software is solely for use on or in conjunction
 * with Renesas Electronics products.
 *
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, THE
 * SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. EXCEPT AS OTHERWISE
 * PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, IN NO EVENT SHALL
 * RENESAS ELECTRONICS BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 *
 ****************************************************************************************
 */

#ifndef BRD_IO_CONFIG_RA6W1_H
#define BRD_IO_CONFIG_RA6W1_H

#ifdef BSP_MCU_GROUP_RA6W1
 #include "bsp_pin_cfg.h"
#endif

#ifdef EXT_INTR1_PIN
 #define BTN_FR               EXT_INTR1_PIN
#endif

#ifdef EXT_INTR2_PIN
 #define BTN_WPS              EXT_INTR2_PIN
#endif

/* LED configuration section */
#ifdef LED0
 #define LED0_PORT            (LED0 >> BSP_IO_PORT_OFFSET)
 #define LED0_PIN             (LED0 & BSP_IO_PIN_BITS)
 #define LED0_MODE            (GPIO_W_CFG_PORT_DIRECTION_OUTPUT)
 #define LED0_FUNC            (GPIO_W_PERIPHERAL_GPIO)
#endif

/*WAKUP PIN*/
#define RTC_WAKEUP_IO         (BSP_WAKEUP_GPIO_P0_11)
#define RTC_WAKEUP_IO_EDGE    (BSP_WAKEUP_EDGE_LOW)

#define BTN_WAKEUP_MODE       (GPIO_W_CFG_PULLUP_ENABLE)
#define BTN_WAKEUP_FUNC       (GPIO_W_PERIPHERAL_GPIO)

#define ADC_WAKEUP_MODE       (GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_ANALOG_ENABLE)

#ifdef BTN_FR
 #define BTN_FR_PORT          (BTN_FR >> BSP_IO_PORT_OFFSET)
 #define BTN_FR_PIN           (BTN_FR & BSP_IO_PIN_BITS)
 #define BTN_FR_MODE          (GPIO_W_CFG_PULLUP_ENABLE | GPIO_W_CFG_RETENTION)
 #define BTN_FR_FUNC          (GPIO_W_PERIPHERAL_GPIO)
 #define BTN_FR_INT_POL       (BSP_IO_LEVEL_HIGH)
 #define BTN_FR_INT_SEL       (HW_GPIO_INT_EDGE)
 #define BTN_FR_CHK_TIME      5        /* 5 sec. */
#endif

#ifdef BTN_WPS
 #define BTN_WPS_PORT         (BTN_WPS >> BSP_IO_PORT_OFFSET)
 #define BTN_WPS_PIN          (BTN_WPS & BSP_IO_PIN_BITS)
 #define BTN_WPS_MODE         (GPIO_W_CFG_PULLUP_ENABLE | GPIO_W_CFG_RETENTION)
 #define BTN_WPS_FUNC         (GPIO_W_PERIPHERAL_GPIO)
 #define BTN_WPS_INT_POL      (BSP_IO_LEVEL_HIGH)
 #define BTN_WPS_INT_SEL      (HW_GPIO_INT_EDGE)
 #define BTN_WPS_CHK_TIME     1        /* 1 sec. */
#endif

#ifdef LED0
 #define FR_WPS_LED_PORT      (LED0_PORT)
 #define FR_WPS_LED_PIN       (LED0_PIN)
 #define FR_WPS_LED_MODE      (LED0_MODE)
 #define FR_WPS_LED_FUNC      (LED0_FUNC)
#endif

#endif                                 /* BRD_IO_CONFIG_RA6W1_H */

/**
 \}
 \}
 */
