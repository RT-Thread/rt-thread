/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __HOSAL_GPIO_H_
#define __HOSAL_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/** @addtogroup hosal_gpio GPIO
 *  HOSAL GPIO API
 *
 *  @{
 */

/**
 * @brief gpio config struct
 */
typedef enum {
    ANALOG_MODE,               /**< @brief Used as a function pin, input and output analog */
    INPUT_PULL_UP,             /**< @brief Input with an internal pull-up resistor - use with devices that actively drive the signal low - e.g. button connected to ground */
    INPUT_PULL_DOWN,           /**< @brief Input with an internal pull-down resistor - use with devices that actively drive the signal high - e.g. button connected to a power rail */
    INPUT_HIGH_IMPEDANCE,      /**< @brief Input - must always be driven, either actively or by an external pullup resistor */
    OUTPUT_PUSH_PULL,          /**< @brief Output actively driven high and actively driven low - must not be connected to other active outputs - e.g. LED output */
    OUTPUT_OPEN_DRAIN_NO_PULL, /**< @brief Output actively driven low but is high-impedance when set high - can be connected to other open-drain/open-collector outputs.  Needs an external pull-up resistor */
    OUTPUT_OPEN_DRAIN_PULL_UP, /**< @brief Output actively driven low and is pulled high with an internal resistor when set high - can be connected to other open-drain/open-collector outputs. */
    OUTPUT_OPEN_DRAIN_AF,      /**< @brief Alternate Function Open Drain Mode. */
    OUTPUT_PUSH_PULL_AF,       /**< @brief Alternate Function Push Pull Mode. */
} hosal_gpio_config_t;

/**
 * @brief GPIO interrupt trigger
 */
typedef enum {
    HOSAL_IRQ_TRIG_NEG_PULSE,        /**< @brief GPIO negedge pulse trigger interrupt */
    HOSAL_IRQ_TRIG_POS_PULSE,        /**< @brief GPIO posedge pulse trigger interrupt */
    HOSAL_IRQ_TRIG_NEG_LEVEL,        /**< @brief  GPIO negedge level trigger interrupt (32k 3T)*/
    HOSAL_IRQ_TRIG_POS_LEVEL,        /**< @brief  GPIO posedge level trigger interrupt (32k 3T)*/
} hosal_gpio_irq_trigger_t;

/**
 * @brief GPIO interrupt callback handler
 *
 *@param[in] parg  ：Set the custom parameters specified
 */
typedef void (*hosal_gpio_irq_handler_t)(void *arg);

/**
 * @brief hosal gpio ctx, use for multi gpio irq
 */
typedef struct hosal_gpio_ctx {
    struct hosal_gpio_ctx *next;
    hosal_gpio_irq_handler_t handle;
    void *arg;
    uint8_t pin;
    uint8_t intCtrlMod;
    uint8_t intTrigMod;
}hosal_gpio_ctx_t;

/**
 * @brief GPIO dev struct
 */
typedef struct {
    uint8_t        port;         /**< @brief gpio port */
    hosal_gpio_config_t  config; /**< @brief gpio config */
    void          *priv;         /**< @brief priv data */
} hosal_gpio_dev_t;

/**
 * @brief Initialises a GPIO pin
 *
 * @note  Prepares a GPIO pin for use.
 *
 * @param[in]  gpio           the gpio pin which should be initialised
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_gpio_init(hosal_gpio_dev_t *gpio);

/**
 * @brief Set GPIO output high or low
 *
 * @note  Using this function on a gpio pin which is set to input mode is undefined.
 *
 * @param[in]  gpio  the gpio pin which should be set 
 * @param[in]  value 0 : output low | >0 : output high
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_gpio_output_set(hosal_gpio_dev_t *gpio, uint8_t value);

/**
 * @brief Get the state of an input GPIO pin. Using this function on a
 * gpio pin which is set to output mode will return an undefined value.
 *
 * @param[in]  gpio   the gpio pin which should be read
 * @param[out] value  gpio value
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_gpio_input_get(hosal_gpio_dev_t *gpio, uint8_t *value);

/**
 * @brief Enables an interrupt trigger for an input GPIO pin.
 * Using this function on a gpio pin which is set to
 * output mode is undefined.
 *
 * @param[in]  gpio     the gpio pin which will provide the interrupt trigger
 * @param[in]  trigger  the type of trigger (rising/falling edge or both)
 * @param[in]  handler  a function pointer to the interrupt handler
 * @param[in]  arg      an argument that will be passed to the interrupt handler
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_gpio_irq_set(hosal_gpio_dev_t *gpio, hosal_gpio_irq_trigger_t trigger_type, hosal_gpio_irq_handler_t handler, void *arg);

/**
 * @brief Clear an interrupt status for an input GPIO pin.
 * Using this function on a gpio pin which has generated a interrupt.
 *
 * @param[in]  gpio  the gpio pin which provided the interrupt trigger
 * @param[in]  mask  0 : mask | 1 : umask
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_gpio_irq_mask(hosal_gpio_dev_t *gpio, uint8_t mask);

/**
 * @brief Set a GPIO pin in default state.
 *
 * @param[in]  gpio  the gpio pin which should be deinitialised
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_gpio_finalize(hosal_gpio_dev_t *gpio);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* HAL_GPIO_H */

