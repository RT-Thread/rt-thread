/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __PIN_DM_H__
#define __PIN_DM_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

/**
 * Bind GPIO pin to system PIN API
 *
 * @param gpio Pin device
 * @param pin_nr GPIO pin number
 *
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t pin_api_init(struct rt_device_pin *gpio, rt_size_t pin_nr);

/**
 * Bind GPIO pin to system PIN PIC
 *
 * @param gpio Pin device
 * @param pin_irq GPIO irqno
 *
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t pin_pic_init(struct rt_device_pin *gpio, int pin_irq);

/**
 * Handle GPIO one pin's ISR
 *
 * @param gpio Pin device
 * @param pin GPIO pin
 *
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t pin_pic_handle_isr(struct rt_device_pin *gpio, rt_base_t pin);

#ifdef RT_USING_PINCTRL
/**
 * Request GPIO pin configuration from pinctrl
 *
 * @param pinctrl Pinctrl device
 * @param gpio GPIO pin number
 * @param flags GPIO configuration flags
 *
 * @return RT_EOK on success, error code otherwise
 */
rt_err_t pin_gpio_request(struct rt_device_pin *pinctrl, rt_base_t gpio, rt_uint32_t flags);
#endif

#endif /* __DEV_PIN_DM_H__ */
