/**
 * \file
 *
 * \brief Port
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 */
#ifndef _HAL_GPIO_INCLUDED_
#define _HAL_GPIO_INCLUDED_

#include <hpl_gpio.h>
#include <utils_assert.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Set gpio pull mode
 *
 * Set pin pull mode, non existing pull modes throws an fatal assert
 *
 * \param[in] pin       The pin number for device
 * \param[in] pull_mode GPIO_PULL_DOWN = Pull pin low with internal resistor
 *                      GPIO_PULL_UP   = Pull pin high with internal resistor
 *                      GPIO_PULL_OFF  = Disable pin pull mode
 */
static inline void gpio_set_pin_pull_mode(const uint8_t pin, const enum gpio_pull_mode pull_mode)
{
	_gpio_set_pin_pull_mode((enum gpio_port)GPIO_PORT(pin), pin & 0x1F, pull_mode);
}

/**
 * \brief Set pin function
 *
 * Select which function a pin will be used for
 *
 * \param[in] pin       The pin number for device
 * \param[in] function  The pin function is given by a 32-bit wide bitfield
 *                      found in the header files for the device
 *
 */
static inline void gpio_set_pin_function(const uint32_t pin, uint32_t function)
{
	_gpio_set_pin_function(pin, function);
}

/**
 * \brief Set port data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] port      Ports are grouped into groups of maximum 32 pins,
 *                      GPIO_PORTA = group 0, GPIO_PORTB = group 1, etc
 * \param[in] mask      Bit mask where 1 means apply direction setting to the
 *                      corresponding pin
 * \param[in] direction GPIO_DIRECTION_IN  = Data direction in
 *                      GPIO_DIRECTION_OUT = Data direction out
 *                      GPIO_DIRECTION_OFF = Disables the pin
 *                      (low power state)
 */
static inline void gpio_set_port_direction(const enum gpio_port port, const uint32_t mask,
                                           const enum gpio_direction direction)
{
	_gpio_set_direction(port, mask, direction);
}

/**
 * \brief Set gpio data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] pin       The pin number for device
 * \param[in] direction GPIO_DIRECTION_IN  = Data direction in
 *                      GPIO_DIRECTION_OUT = Data direction out
 *                      GPIO_DIRECTION_OFF = Disables the pin
 *                      (low power state)
 */
static inline void gpio_set_pin_direction(const uint8_t pin, const enum gpio_direction direction)
{
	_gpio_set_direction((enum gpio_port)GPIO_PORT(pin), 1U << GPIO_PIN(pin), direction);
}

/**
 * \brief Set port level
 *
 * Sets output level on the pins defined by the bit mask
 *
 * \param[in] port  Ports are grouped into groups of maximum 32 pins,
 *                  GPIO_PORTA = group 0, GPIO_PORTB = group 1, etc
 * \param[in] mask  Bit mask where 1 means apply port level to the corresponding
 *                  pin
 * \param[in] level true  = Pin levels set to "high" state
 *                  false = Pin levels set to "low" state
 */
static inline void gpio_set_port_level(const enum gpio_port port, const uint32_t mask, const bool level)
{
	_gpio_set_level(port, mask, level);
}

/**
 * \brief Set gpio level
 *
 * Sets output level on a pin
 *
 * \param[in] pin       The pin number for device
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void gpio_set_pin_level(const uint8_t pin, const bool level)
{
	_gpio_set_level((enum gpio_port)GPIO_PORT(pin), 1U << GPIO_PIN(pin), level);
}

/**
 * \brief Toggle out level on pins
 *
 * Toggle the pin levels on pins defined by bit mask
 *
 * \param[in] port  Ports are grouped into groups of maximum 32 pins,
 *                  GPIO_PORTA = group 0, GPIO_PORTB = group 1, etc
 * \param[in] mask  Bit mask where 1 means toggle pin level to the corresponding
 *                  pin
 */
static inline void gpio_toggle_port_level(const enum gpio_port port, const uint32_t mask)
{
	_gpio_toggle_level(port, mask);
}

/**
 * \brief Toggle output level on pin
 *
 * Toggle the pin levels on pins defined by bit mask
 *
 * \param[in] pin       The pin number for device
 */
static inline void gpio_toggle_pin_level(const uint8_t pin)
{
	_gpio_toggle_level((enum gpio_port)GPIO_PORT(pin), 1U << GPIO_PIN(pin));
}

/**
 * \brief Get input level on pins
 *
 * Read the input level on pins connected to a port
 *
 * \param[in] port  Ports are grouped into groups of maximum 32 pins,
 *                  GPIO_PORTA = group 0, GPIO_PORTB = group 1, etc
 */
static inline uint32_t gpio_get_port_level(const enum gpio_port port)
{
	return _gpio_get_level(port);
}

/**
 * \brief Get level on pin
 *
 * Reads the level on pins connected to a port
 *
 * \param[in] pin       The pin number for device
 */
static inline bool gpio_get_pin_level(const uint8_t pin)
{
	return (bool)(_gpio_get_level((enum gpio_port)GPIO_PORT(pin)) & (0x01U << GPIO_PIN(pin)));
}
/**
 * \brief Get current driver version
 */
uint32_t gpio_get_version(void);

#ifdef __cplusplus
}
#endif

#endif
