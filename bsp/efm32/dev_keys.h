/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-12-29   onelife     Initial creation for EFM32GG_DK3750 board
 */

#ifndef __DEV_KEYS_H__
#define __DEV_KEYS_H__

/* Includes ------------------------------------------------------------------*/
/* Exported defines ----------------------------------------------------------*/
#define KEYS_INT_PORT       (gpioPortE)
#define KEYS_INT_PIN        (0)
#define KEYS_POLL_TIME      (RT_TICK_PER_SECOND / 10)

/* Exported types ------------------------------------------------------------*/
struct efm32_joy_device
{
    rt_int16_t x, y;
    rt_uint16_t min_x, max_x;
    rt_uint16_t min_y, max_y;

    struct rt_timer timer;
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void efm32_hw_keys_init(void);

#endif /* __DEV_KEYS_H__ */
