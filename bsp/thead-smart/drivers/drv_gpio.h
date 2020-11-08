/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      header file for gpio driver
 */

#ifndef _CSI_GPIO_H_
#define _CSI_GPIO_H_


#include <stdint.h>
#include <stdbool.h>
#include <drv_common.h>

#ifdef __cplusplus
extern "C" {
#endif
/// definition for gpio pin handle.
typedef void *gpio_pin_handle_t;

/****** GPIO specific error codes *****/
typedef enum
{
    GPIO_ERROR_MODE  = (DRV_ERROR_SPECIFIC + 1),      ///< Specified Mode not supported
    GPIO_ERROR_DIRECTION,                        ///< Specified direction not supported
    GPIO_ERROR_IRQ_MODE,                         ///< Specified irq mode not supported
} gpio_error_e;

/*----- GPIO Control Codes: Mode -----*/
typedef enum
{
    GPIO_MODE_PULLNONE         = 0,    ///< pull none for input
    GPIO_MODE_PULLUP,                  ///< pull up for input
    GPIO_MODE_PULLDOWN,                ///< pull down for input
    GPIO_MODE_OPEN_DRAIN,              ///< open drain mode for output
    GPIO_MODE_PUSH_PULL,               ///< push-pull mode for output
} gpio_mode_e;

/*----- GPIO Control Codes: Mode Parameters: Data Bits -----*/
typedef enum
{
    GPIO_DIRECTION_INPUT             = 0,    ///< gpio as input
    GPIO_DIRECTION_OUTPUT,                   ///< gpio as output
} gpio_direction_e;

/*----- GPIO Control Codes: Mode Parameters: Parity -----*/
typedef enum
{
    GPIO_IRQ_MODE_RISING_EDGE     = 0,       ///< interrupt mode for rising edge
    GPIO_IRQ_MODE_FALLING_EDGE,              ///< interrupt mode for falling edge
    GPIO_IRQ_MODE_DOUBLE_EDGE,               ///< interrupt mode for double edge
    GPIO_IRQ_MODE_LOW_LEVEL,                 ///< interrupt mode for low level
    GPIO_IRQ_MODE_HIGH_LEVEL,                ///< interrupt mode for high level
} gpio_irq_mode_e;

typedef void (*gpio_event_cb_t)(int32_t idx);   ///< gpio Event call back.

/**
  \brief       Initialize GPIO handle.
  \param[in]   gpio_pin    gpio pin idx.
  \param[in]   cb_event  event callback function \ref gpio_event_cb_t
  \return      gpio_pin_handle
*/
gpio_pin_handle_t csi_gpio_pin_initialize(int32_t gpio_pin, gpio_event_cb_t cb_event);

/**
  \brief       De-initialize GPIO pin handle.stops operation and releases the software resources used by the handle.
  \param[in]   handle    gpio pin handle to operate.
  \return      error code
*/
int32_t csi_gpio_pin_uninitialize(gpio_pin_handle_t handle);

/**
  \brief       control gpio power.
  \param[in]   handle  gpio handle to operate.
  \param[in]   state   power state.\ref csi_power_stat_e.
  \return      error code
*/
int32_t csi_gpio_power_control(gpio_pin_handle_t handle, csi_power_stat_e state);

/**
  \brief       config pin mode
  \param[in]   pin       gpio pin handle to operate.
  \param[in]   mode      \ref gpio_mode_e
  \return      error code
*/
int32_t csi_gpio_pin_config_mode(gpio_pin_handle_t handle,
                                 gpio_mode_e mode);

/**
  \brief       config pin direction
  \param[in]   pin       gpio pin handle to operate.
  \param[in]   dir       \ref gpio_direction_e
  \return      error code
*/
int32_t csi_gpio_pin_config_direction(gpio_pin_handle_t handle,
                                      gpio_direction_e dir);

/**
  \brief       config pin
  \param[in]   pin       gpio pin handle to operate.
  \param[in]   mode      \ref gpio_mode_e
  \param[in]   dir       \ref gpio_direction_e
  \return      error code
*/
int32_t csi_gpio_pin_config(gpio_pin_handle_t handle,
                            gpio_mode_e mode,
                            gpio_direction_e dir);

/**
  \brief       Set one or zero to the selected GPIO pin.
  \param[in]   pin       gpio pin handle to operate.
  \param[in]   value     value to be set
  \return      error code
*/
int32_t csi_gpio_pin_write(gpio_pin_handle_t handle, bool value);

/**
  \brief       Get the value of  selected GPIO pin.
  \param[in]   pin       gpio pin handle to operate.
  \param[out]  value     buffer to store the pin value
  \return      error code
*/
int32_t csi_gpio_pin_read(gpio_pin_handle_t handle, bool *value);

/**
  \brief       set GPIO interrupt mode.
  \param[in]   pin       gpio pin handle to operate.
  \param[in]   mode      irq mode to be set
  \param[in]   enable    enable flag
  \return      error code
*/
int32_t csi_gpio_pin_set_irq(gpio_pin_handle_t handle, gpio_irq_mode_e mode, bool enable);


#ifdef __cplusplus
}
#endif

#endif /* _CSI_GPIO_H_ */
