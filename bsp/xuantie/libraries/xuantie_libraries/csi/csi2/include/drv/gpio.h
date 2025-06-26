 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     drv/gpio.h
 * @brief    Header File for GPIO Driver
 * @version  V1.0
 * @date     8. Apr 2020
 * @model    gpio
 ******************************************************************************/

#ifndef _DRV_GPIO_H_
#define _DRV_GPIO_H_

#include <stdint.h>
#include <stdbool.h>
#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \enum     csi_gpio_dir_t
 * \brief    GPIO dir define
 */
typedef enum {
    GPIO_DIRECTION_INPUT       = 0,    ///< GPIO as input
    GPIO_DIRECTION_OUTPUT,             ///< GPIO as output
} csi_gpio_dir_t;

/**
 * \enum     csi_gpio_pin_state_t
 * \brief    GPIO pin state define
 */
typedef enum {
    GPIO_PIN_LOW                = 0,   ///< GPIO low level
    GPIO_PIN_HIGH,                     ///< GPIO high level
} csi_gpio_pin_state_t;

/**
 * \enum     csi_gpio_mode_t
 * \brief    GPIO mode define
 */
typedef enum {
    GPIO_MODE_PULLNONE         = 0,    ///< Pull none
    GPIO_MODE_PULLUP,                  ///< Pull up for input
    GPIO_MODE_PULLDOWN,                ///< Pull down for input
    GPIO_MODE_OPEN_DRAIN,              ///< Open drain mode for output
    GPIO_MODE_PUSH_PULL,               ///< Push-pull mode for output
} csi_gpio_mode_t;

/**
 * \enum     csi_gpio_irq_mode_t
 * \brief    GPIO irq triger type
 */
typedef enum {
    GPIO_IRQ_MODE_RISING_EDGE  = 0,    ///< Interrupt mode for rising edge
    GPIO_IRQ_MODE_FALLING_EDGE,        ///< Interrupt mode for falling edge
    GPIO_IRQ_MODE_BOTH_EDGE,           ///< Interrupt mode for both edge
    GPIO_IRQ_MODE_LOW_LEVEL,           ///< Interrupt mode for low level
    GPIO_IRQ_MODE_HIGH_LEVEL,          ///< Interrupt mode for high level
} csi_gpio_irq_mode_t;

/**
 * \struct   csi_gpio_t
 * \brief    GPIO control block
 */

typedef struct csi_gpio csi_gpio_t;
struct csi_gpio {
    csi_dev_t           dev;           ///< Hw-dev info
    void (*callback)(csi_gpio_t *gpio, uint32_t pins, void *arg); ///<   Call-back of gpio port
    void                *arg;          ///< User param passed to callback
    void                *priv;         ///< User private param
};

/**
  \brief       Initialize GPIO Port handle
  \param[in]   gpio        GPIO port handle
  \param[in]   port_idx    GPIO port index
  \return      Error code
*/
csi_error_t csi_gpio_init(csi_gpio_t *gpio, uint32_t port_idx);

/**
  \brief       De-initialize GPIO pin.stops operation
               releases the software resources used by the gpio-pin
  \param[in]   gpio    GPIO port handle
  \return      None
*/
void csi_gpio_uninit(csi_gpio_t *gpio);

/**
  \brief       Config pin direction
  \param[in]   gpio        GPIO port handle
  \param[in]   pin_mask    Pin mask need to be set
  \param[in]   dir         \ref csi_gpio_dir_t
  \return      Error code
*/
csi_error_t csi_gpio_dir(csi_gpio_t *gpio, uint32_t pin_mask, csi_gpio_dir_t dir);

/**
  \brief       Config pin mode
               If one of pins config error, then the rest of pins will not config, and function return CSI_ERROR
               If one or more pin unsupport, function will return CSI_UNSUPPORT, but the other pin still configured
  \param[in]   gpio        GPIO port handle
  \param[in]   pin_mask    Pin mask need to be set
  \param[in]   mode        \ref csi_gpio_mode_t
  \return      Error code
*/
csi_error_t csi_gpio_mode(csi_gpio_t *gpio, uint32_t pin_mask, csi_gpio_mode_t mode);

/**
  \brief       Config gpio irq params
  \param[in]   gpio        GPIO port handle
  \param[in]   pin_mask    Pin mask need to be set
  \param[in]   mode        Interrupt trigger mode \ref csi_gpio_irq_mode_t
  \return      Error code
*/
csi_error_t csi_gpio_irq_mode(csi_gpio_t *gpio, uint32_t pin_mask, csi_gpio_irq_mode_t mode);

/**
  \brief       Enable or disable gpio pin interrupt
  \param[in]   gpio        GPIO port handle
  \param[in]   pin_mask    Pin mask need to be set
  \param[in]   enable      0:disable  1:enable
  \return      Error code
*/
csi_error_t csi_gpio_irq_enable(csi_gpio_t *gpio, uint32_t pin_mask, bool enable);

/**
  \brief       Set debounce of gpio when gpio configed as input
  \param[in]   gpio        GPIO port handle
  \param[in]   pin_mask    Pin mask need to be set
  \param[in]   enbale      0: disable   1:enable
  \return      Error code
*/
csi_error_t csi_gpio_debounce(csi_gpio_t *gpio, uint32_t pin_mask, bool enable);
/**
  \brief       Set one or zero to the selected pin mask
  \param[in]   gpio        GPIO port handle
  \param[in]   pin_mask    Pin mask need to be set
  \param[in]   value       Value to be set \ref csi_gpio_pin_state_t
  \return      None
*/
void  csi_gpio_write(csi_gpio_t *gpio, uint32_t pin_mask, csi_gpio_pin_state_t value);

/**
  \brief       Toggle output gpio value,ex.if previous value is 1, then output 0
  \param[in]   gpio        GPIO port handle
  \param[in]   pin_mask    Pin mask need to be set
  \return      None
*/
void csi_gpio_toggle(csi_gpio_t *gpio, uint32_t pin_mask);

/**
  \brief       Get the value of  selected GPIO pin mask
  \param[in]   gpio        GPIO port handle
  \param[in]   pin_mask    Pin mask need to be set
  \return      According to the bit mask, the corresponding pin status is obtained
*/
uint32_t csi_gpio_read(csi_gpio_t *gpio, uint32_t pin_mask);

/**
  \brief       Attach the interrupt callback to the port
  \param[in]   gpio        GPIO port handle
  \param[in]   callback    Callback function
  \param[in]   arg         User param passed to callback
  \return      Error code
*/
csi_error_t  csi_gpio_attach_callback(csi_gpio_t *gpio, void *callback, void *arg);

/**
  \brief       Detach the interrupt callback to the port
  \param[in]   gpio    GPIO port handle
  \return      None
*/
void         csi_gpio_detach_callback(csi_gpio_t *gpio);

/**
  \brief       Enable gpio power manage
  \param[in]   gpio    GPIO handle to operate
  \return      Error code
*/
csi_error_t csi_gpio_enable_pm(csi_gpio_t *gpio);

/**
  \brief       Disable gpio power manage
  \param[in]   gpio    GPIO handle to operate
  \return      None
*/
void csi_gpio_disable_pm(csi_gpio_t *gpio);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_GPIO_H_ */
