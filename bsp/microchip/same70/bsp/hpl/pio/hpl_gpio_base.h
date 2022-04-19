
/**
 * \file
 *
 * \brief SAM PIO.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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
 *
 */

#include <hpl_gpio.h>
#include <utils_assert.h>

/**
 * \brief Transfer gpio_port to hardware address
 */
static inline void *port_to_reg(const enum gpio_port port)
{
	/* PIO instance offset is 0x200 */
	return (void *)((uint32_t)PIOA + port * 0x200);
}

/**
 * \brief Set direction on port with mask
 */
static inline void _gpio_set_direction(const enum gpio_port port, const uint32_t mask,
                                       const enum gpio_direction direction)
{
	void *const hw = port_to_reg(port);
	switch (direction) {
	case GPIO_DIRECTION_OFF:
	case GPIO_DIRECTION_IN:
		hri_pio_clear_OSR_reg(hw, mask);
		break;

	case GPIO_DIRECTION_OUT:
		hri_pio_set_OSR_reg(hw, mask);
		break;

	default:
		ASSERT(false);
	}
}

/**
 * \brief Set output level on port with mask
 */
static inline void _gpio_set_level(const enum gpio_port port, const uint32_t mask, const bool level)
{
	void *const hw = port_to_reg(port);
	if (level) {
		hri_pio_set_ODSR_reg(hw, mask);
	} else {
		hri_pio_clear_ODSR_reg(hw, mask);
	}
}

/**
 * \brief Change output level to the opposite with mask
 */
static inline void _gpio_toggle_level(const enum gpio_port port, const uint32_t mask)
{
	uint32_t    bits_clear, bits_set;
	void *const hw = port_to_reg(port);

	bits_clear = hri_pio_get_ODSR_reg(hw, mask);
	bits_set   = (~bits_clear) & mask;
	hri_pio_set_ODSR_reg(hw, bits_set);
	hri_pio_clear_ODSR_reg(hw, bits_clear);
}

/**
 * \brief Get input levels on all port pins
 */
static inline uint32_t _gpio_get_level(const enum gpio_port port)
{
	uint32_t    tmp;
	void *const hw = port_to_reg(port);
	tmp            = hri_pio_read_PDSR_reg(hw);
	return tmp;
}

/**
 * \brief Set pin pull mode
 */
static inline void _gpio_set_pin_pull_mode(const enum gpio_port port, const uint8_t pin,
                                           const enum gpio_pull_mode pull_mode)
{
	void *const hw = port_to_reg(port);
	switch (pull_mode) {
	case GPIO_PULL_OFF:
		hri_pio_clear_PUSR_reg(hw, 1U << pin);
		hri_pio_clear_PPDSR_reg(hw, 1U << pin);
		break;

	case GPIO_PULL_UP:
		hri_pio_clear_PPDSR_reg(hw, 1U << pin);
		hri_pio_set_PUSR_reg(hw, 1U << pin);
		break;

	case GPIO_PULL_DOWN:
		hri_pio_clear_PUSR_reg(hw, 1U << pin);
		hri_pio_set_PPDSR_reg(hw, 1U << pin);
		break;

	default:
		ASSERT(false);
		break;
	}
}

/**
 * \brief Set pin function
 */
static inline void _gpio_set_pin_function(const uint32_t gpio, const uint32_t function)
{
	uint8_t     port = GPIO_PORT(gpio);
	uint8_t     pin  = GPIO_PIN(gpio);
	void *const hw   = port_to_reg((enum gpio_port)port);

	if ((enum gpio_port)port == GPIO_PORTB) {
		if ((pin == 4) || (pin == 5) || (pin == 6) || (pin == 7) || (pin == 12)) {
			hri_matrix_set_CCFG_SYSIO_reg(MATRIX, (0x1 << pin));
		}
	}

	if (function == GPIO_PIN_FUNCTION_OFF) {
		hri_pio_set_PSR_reg(hw, 1U << pin);
	} else {
		if (function & 0x1) {
			hri_pio_set_ABCDSR_reg(hw, 0, 1U << pin);
		} else {
			hri_pio_clear_ABCDSR_reg(hw, 0, 1U << pin);
		}

		if (function & 0x2) {
			hri_pio_set_ABCDSR_reg(hw, 1, 1U << pin);
		} else {
			hri_pio_clear_ABCDSR_reg(hw, 1, 1U << pin);
		}

		hri_pio_clear_PSR_reg(hw, 1U << pin);
	}
}
