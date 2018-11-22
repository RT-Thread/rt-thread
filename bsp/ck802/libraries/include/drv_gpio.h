/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * @file     drv_gpio.h
 * @brief    header file for gpio driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CSI_GPIO_H_
#define _CSI_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <drv_common.h>
#include <pin_name.h>

/// definition for gpio port handle.
typedef void *gpio_port_handle_t;
/// definition for gpio pin handle.
typedef void *gpio_pin_handle_t;

/****** GPIO specific error codes *****/
typedef enum {
    GPIO_ERROR_MODE  = (EDRV_SPECIFIC + 1),      ///< Specified Mode not suphandleed
    GPIO_ERROR_DIRECTION,                        ///< Specified direction not suphandleed
    GPIO_ERROR_IRQ_MODE,                         ///< Specified irq mode not suphandleed
} drv_gpio_error_e;

/*----- GPIO Control Codes: Mode -----*/
typedef enum {
    GPIO_MODE_PULLNONE         = 0,   ///< pull none for input
    GPIO_MODE_PULLUP              ,   ///< pull up for input
    GPIO_MODE_PULLDOWM            ,   ///< pull down for input
    GPIO_MODE_OPEN_DRAIN          ,   ///< open drain mode for output
    GPIO_MODE_PUSH_PULL               ///< push-pull mode for output
} gpio_mode_e;

/*----- GPIO Control Codes: Mode Parameters: Data Bits -----*/
typedef enum {
    GPIO_DIRECTION_INPUT             = 0,    ///< gpio as input
    GPIO_DIRECTION_OUTPUT               ,    ///< gpio as output
} gpio_direction_e;

/*----- GPIO Control Codes: Mode Parameters: Parity -----*/
typedef enum {
    GPIO_IRQ_MODE_RISING_EDGE     = 0,       ///< interrupt mode for rising edge
    GPIO_IRQ_MODE_FALLING_EDGE       ,       ///< interrupt mode for falling edge
    GPIO_IRQ_MODE_DOUBLE_EDGE        ,       ///< interrupt mode for double edge
    GPIO_IRQ_MODE_LOW_LEVEL          ,       ///< interrupt mode for low level
    GPIO_IRQ_MODE_HIGH_LEVEL         ,       ///< interrupt mode for high level
} gpio_irq_mode_e;

/**
\brief GPIO Driver Capabilities.
*/
typedef struct  {
    uint32_t interrupt_mode       : 1;      ///< suphandles GPIO interrupt mode
    uint32_t pull_mode            : 1;
} gpio_capabilities_t;


typedef void (*gpio_event_cb_t)(gpio_pin_handle_t io);   ///< gpio Event call back.

/**
  \brief       Initialize GPIO module. 1. Initializes the resources needed for the GPIO handle 2.registers event callback function
                3.get gpio_port_handle
  \param[in]   port      port_name.
  \param[in]   cb_event  Pointer to \ref gpio_event_cb_t
  \return      gpio_port_handle
*/
gpio_port_handle_t csi_gpio_port_initialize(port_name_t port, gpio_event_cb_t cb_event);

/**
  \brief       De-initialize GPIO handle. stops operation and releases the software resources used by the handle
  \param[in]   handle   gpio port handle to operate.
  \return      error code
*/
int32_t csi_gpio_port_uninitialize(gpio_port_handle_t handle);

/**
  \brief       Get gpio capabilities.all pins have same capabilities in one handle
  \param[in]   handle  handle instance to operate.
  \return      \ref    gpio_capabilities_t
*/
gpio_capabilities_t csi_gpio_get_io_capabilities(gpio_port_handle_t handle);

/**
  \brief       config multiple pin within one handle
  \param[in]   handle    gpio port handle to operate.
  \param[in]   mask      the bitmask to identify which bits in the handle should be included (0 - ignore)
  \param[in]   mode      \ref gpio_mode_e
  \param[in]   dir       \ref gpio_direction_e
  \return      error code
*/
int32_t csi_gpio_port_config(gpio_port_handle_t handle,
                             uint32_t mask,
                             gpio_mode_e mode,
                             gpio_direction_e dir);

/**
  \brief       Write value to the handle(write value to multiple pins on one handle at the same time)
  \param[in]   handle    gpio port handle to operate.
  \param[in]   mask      The bitmask to identify which bits in the handle should be included (0 - ignore)
  \param[in]   value     the value to be set
  \return      error code
*/
int32_t csi_gpio_port_write(gpio_port_handle_t handle, uint32_t mask, uint32_t value);

/**
  \brief       Read the current value on the handle(read value of multiple pins on one handle at the same time)
  \param[in]   handle    gpio port handle to operate.
  \param[in]   mask      The bitmask to identify which bits in the handle should be included (0 - ignore)
  \param[out]  value     an integer with each bit corresponding to an associated handle pin setting
  \return      error code
*/
int32_t csi_gpio_port_read(gpio_port_handle_t handle, uint32_t mask, uint32_t *value);

/**
  \brief       Initialize GPIO handle.
  \param[in]   gpio_pin    Pointer to the pin_t.
  \return      gpio_pin_handle
*/
gpio_pin_handle_t csi_gpio_pin_initialize(pin_t gpio_pin);
/**
  \brief       config pin
  \param[in]   pin       gpio pin handle to operate.
  \param[in]   mode      \ref gpio_mode_e
  \param[in]   dir       \ref gpio_direction_e
  \return      error code
*/
int32_t csi_gpio_pin_config(gpio_pin_handle_t pin,
                            gpio_mode_e mode,
                            gpio_direction_e dir);

/**
  \brief       Set one or zero to the selected GPIO pin.
  \param[in]   pin       gpio pin handle to operate.
  \param[in]   value     the value to be set
  \return      error code
*/
int32_t csi_gpio_pin_write(gpio_pin_handle_t pin, bool value);

/**
  \brief       Get the value of  selected GPIO pin.
  \param[in]   pin       gpio pin handle to operate.
  \param[out]  value     buf to store the pin value
  \return      error code
*/
int32_t csi_gpio_pin_read(gpio_pin_handle_t pin, bool *value);

/**
  \brief       set GPIO interrupt mode.
  \param[in]   pin       gpio pin handle to operate.
  \param[in]   mode      the irq mode to be set
  \param[in]   enable    the enable flag
  \return      error code
*/
int32_t csi_gpio_pin_irq_set(gpio_pin_handle_t pin, gpio_irq_mode_e mode, bool enable);


#ifdef __cplusplus
}
#endif

#endif /* _CSI_GPIO_H_ */
