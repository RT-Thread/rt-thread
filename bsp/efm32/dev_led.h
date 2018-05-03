/***************************************************************************//**
 * @file    dev_led.h
 * @brief   LED driver of RT-Thread RTOS for EFM32
 *  COPYRIGHT (C) 2012, RT-Thread Development Team
 * @author  onelife
 * @version 1.0
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 * LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date         Author      Notes
 * 2009-01-05   Bernard     the first version
 * 2010-12-27   onelife     Modify for EFM32
 * 2011-05-06   onelife     Add EFM32 development kit support
 * 2011-12-08   onelife     Add giant gecko development kit support
 ******************************************************************************/
#ifndef __DEV_LED_H__
#define __DEV_LED_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#if defined(EFM32_G8XX_STK)
#define LEDS_MAX_NUMBER         (4)
    /* Configure GPIO port C 0-3 for LEDs */
#define LEDS_PIN_PORT_0         gpioPortC
#define LEDS_PIN_NUMBER_0       (0)
#define LEDS_PIN_PORT_1         gpioPortC
#define LEDS_PIN_NUMBER_1       (1)
#define LEDS_PIN_PORT_2         gpioPortC
#define LEDS_PIN_NUMBER_2       (2)
#define LEDS_PIN_PORT_3         gpioPortC
#define LEDS_PIN_NUMBER_3       (3)
#elif (defined(EFM32_GXXX_DK) || defined(EFM32GG_DK3750))
#define LEDS_MAX_NUMBER         (16)
#endif

/* Exported functions ------------------------------------------------------- */
rt_err_t rt_hw_led_init(void);
void rt_hw_led_on(rt_uint8_t num);
void rt_hw_led_off(rt_uint8_t num);
void rt_hw_led_toggle(rt_uint8_t num);
rt_uint8_t rt_hw_led_state(rt_uint8_t num);

#endif /* __DEV_LED_H__ */
