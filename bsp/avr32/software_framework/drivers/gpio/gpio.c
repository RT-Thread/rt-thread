/*****************************************************************************
*
* \file
*
* \brief GPIO software driver interface for AVR UC3.
*
 * Copyright (c) 2010-2018 Microchip Technology Inc. and its subsidiaries.
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
*****************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "gpio.h"

/** \name Peripheral Bus Interface
 *
 * @{
 */

/** \brief Enables specific module modes for a set of pins.
 *
 * \param gpiomap The pin map.
 * \param size The number of pins in \a gpiomap.
 *
 * \return \ref GPIO_SUCCESS or \ref GPIO_INVALID_ARGUMENT.
 */
uint32_t gpio_enable_module(const gpio_map_t gpiomap, uint32_t size)
{
	uint32_t status = GPIO_SUCCESS;
	uint32_t i;

	for (i = 0; i < size; i++) {
		status |= gpio_enable_module_pin(gpiomap->pin, gpiomap->function);
		gpiomap++;
	}

	return status;
}

/** \brief Enables a specific module mode for a pin.
 *
 * \note A pin and pin function index can be found in the device part header
 *       file. The \c AVR32_*_PIN constants map a GPIO number from the device
 *       datasheet to the appropriate pin function, while the corresponding
 *       \c AVR32_*_FUNCTION macro contains the appropriate function index.
 *       \n\n
 *       For example, the constants \c AVR32_PWM_3_PIN and
 *       \c AVR32_PWM_3_FUNCTION contain the pin and function index of the PWM
 *       module, channel 3, for the current device (if available).
 *
 * \param pin The pin number.
 * \param function The pin function.
 *
 * \return \ref GPIO_SUCCESS or \ref GPIO_INVALID_ARGUMENT.
 */
uint32_t gpio_enable_module_pin(uint32_t pin, uint32_t function)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];

	/* Enable the correct function. */
	switch (function) {
	case 0: /* A function. */
		gpio_port->pmr0c = 1 << (pin & 0x1F);
		gpio_port->pmr1c = 1 << (pin & 0x1F);
#if (AVR32_GPIO_H_VERSION >= 210)
		gpio_port->pmr2c = 1 << (pin & 0x1F);
#endif
		break;

	case 1: /* B function. */
		gpio_port->pmr0s = 1 << (pin & 0x1F);
		gpio_port->pmr1c = 1 << (pin & 0x1F);
#if (AVR32_GPIO_H_VERSION >= 210)
		gpio_port->pmr2c = 1 << (pin & 0x1F);
#endif
		break;

	case 2: /* C function. */
		gpio_port->pmr0c = 1 << (pin & 0x1F);
		gpio_port->pmr1s = 1 << (pin & 0x1F);
#if (AVR32_GPIO_H_VERSION >= 210)
		gpio_port->pmr2c = 1 << (pin & 0x1F);
#endif
		break;

	case 3: /* D function. */
		gpio_port->pmr0s = 1 << (pin & 0x1F);
		gpio_port->pmr1s = 1 << (pin & 0x1F);
#if (AVR32_GPIO_H_VERSION >= 210)
		gpio_port->pmr2c = 1 << (pin & 0x1F);
#endif
		break;

#if (AVR32_GPIO_H_VERSION >= 210)
	case 4: /* E function. */
		gpio_port->pmr0c = 1 << (pin & 0x1F);
		gpio_port->pmr1c = 1 << (pin & 0x1F);
		gpio_port->pmr2s = 1 << (pin & 0x1F);
		break;

	case 5: /* F function. */
		gpio_port->pmr0s = 1 << (pin & 0x1F);
		gpio_port->pmr1c = 1 << (pin & 0x1F);
		gpio_port->pmr2s = 1 << (pin & 0x1F);
		break;

	case 6: /* G function. */
		gpio_port->pmr0c = 1 << (pin & 0x1F);
		gpio_port->pmr1s = 1 << (pin & 0x1F);
		gpio_port->pmr2s = 1 << (pin & 0x1F);
		break;

	case 7: /* H function. */
		gpio_port->pmr0s = 1 << (pin & 0x1F);
		gpio_port->pmr1s = 1 << (pin & 0x1F);
		gpio_port->pmr2s = 1 << (pin & 0x1F);
		break;
#endif

	default:
		return GPIO_INVALID_ARGUMENT;
	}

	/* Disable GPIO control. */
	gpio_port->gperc = 1 << (pin & 0x1F);

	return GPIO_SUCCESS;
}

/** \brief Enables the GPIO mode of a set of pins.
 *
 * \param gpiomap The pin map.
 * \param size The number of pins in \a gpiomap.
 */
void gpio_enable_gpio(const gpio_map_t gpiomap, uint32_t size)
{
	uint32_t i;

	for (i = 0; i < size; i++) {
		gpio_enable_gpio_pin(gpiomap->pin);
		gpiomap++;
	}
}

/** \brief Enables the GPIO mode of a pin.
 *
 * \param pin The pin number.\n
 *            Refer to the product header file `uc3x.h' (where x is the part
 *            number; e.g. x = a0512) for pin definitions. E.g., to enable the
 *            GPIO mode of PX21, AVR32_PIN_PX21 can be used. Module pins such as
 *            AVR32_PWM_3_PIN for PWM channel 3 can also be used to release
 *            module pins for GPIO.
 */
void gpio_enable_gpio_pin(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	gpio_port->oderc = 1 << (pin & 0x1F);
	gpio_port->gpers = 1 << (pin & 0x1F);
}

/** \brief Enables the pull-up resistor of a pin.
 *
 * \param pin The pin number.
 */
void gpio_enable_pin_pull_up(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	gpio_port->puers = 1 << (pin & 0x1F);
#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) ||	\
	defined(AVR32_GPIO_212_H_INCLUDED)
	gpio_port->pderc = 1 << (pin & 0x1F);
#endif
}

/** \brief Disables the pull-up resistor of a pin.
 *
 * \param pin The pin number.
 */
void gpio_disable_pin_pull_up(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	gpio_port->puerc = 1 << (pin & 0x1F);
}

#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) ||	\
	defined(AVR32_GPIO_212_H_INCLUDED)
/* Added support of Pull-up Resistor, Pull-down Resistor and Buskeeper Control. */

/** \brief Enables the pull-down resistor of a pin.
 *
 * \param pin The pin number.
 */
void gpio_enable_pin_pull_down(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	gpio_port->puerc = 1 << (pin & 0x1F);
	gpio_port->pders = 1 << (pin & 0x1F);
}

/** \brief Disables the pull-down resistor of a pin.
 *
 * \param pin The pin number.
 */
void gpio_disable_pin_pull_down(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	gpio_port->pderc = 1 << (pin & 0x1F);
}

/** \brief Enables the buskeeper functionality on a pin.
 *
 * \param pin The pin number.
 */
void gpio_enable_pin_buskeeper(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	gpio_port->puers = 1 << (pin & 0x1F);
	gpio_port->pders = 1 << (pin & 0x1F);
}

/** \brief Disables the buskeeper functionality on a pin.
 *
 * \param pin The pin number.
 */
void gpio_disable_pin_buskeeper(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	gpio_port->puerc = 1 << (pin & 0x1F);
	gpio_port->pderc = 1 << (pin & 0x1F);
}

#endif

/** \brief Configuration functionality on a pin.
 *
 * \param pin The pin number.
 * \param flags The configuration.
 */
void gpio_configure_pin(uint32_t pin, uint32_t flags)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];

	/* Both pull-up and pull-down set means buskeeper */
#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) ||	\
	defined(AVR32_GPIO_212_H_INCLUDED)
	if (flags & GPIO_PULL_DOWN) {
		gpio_port->pders = 1 << (pin & 0x1F);
	} else {
		gpio_port->pderc = 1 << (pin & 0x1F);
	}

#endif
	if (flags & GPIO_PULL_UP) {
		gpio_port->puers = 1 << (pin & 0x1F);
	} else {
		gpio_port->puerc = 1 << (pin & 0x1F);
	}

	/* Enable open-drain mode if requested */
#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) ||	\
	defined(AVR32_GPIO_212_H_INCLUDED)
	if (flags & GPIO_OPEN_DRAIN) {
		gpio_port->odmers = 1 << (pin & 0x1F);
	} else {
		gpio_port->odmerc = 1 << (pin & 0x1F);
	}

#endif

#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) ||	\
	defined(AVR32_GPIO_212_H_INCLUDED)
	/* Select drive strength */
	if (flags & GPIO_DRIVE_LOW) {
		gpio_port->odcr0s = 1 << (pin & 0x1F);
	} else {
		gpio_port->odcr0c = 1 << (pin & 0x1F);
	}

	if (flags & GPIO_DRIVE_HIGH) {
		gpio_port->odcr1s = 1 << (pin & 0x1F);
	} else {
		gpio_port->odcr1c = 1 << (pin & 0x1F);
	}

#endif

	/* Select interrupt level for group */
	if (flags & GPIO_INTERRUPT) {
		if (flags & GPIO_BOTHEDGES) {
			gpio_port->imr0c = 1 << (pin & 0x1F);
			gpio_port->imr1c = 1 << (pin & 0x1F);
		} else if (flags & GPIO_RISING) {
			gpio_port->imr0s = 1 << (pin & 0x1F);
			gpio_port->imr1c = 1 << (pin & 0x1F);
		} else if (flags & GPIO_FALLING) {
			gpio_port->imr0c = 1 << (pin & 0x1F);
			gpio_port->imr1s = 1 << (pin & 0x1F);
		}
	}

	/* Select direction and initial pin state */
	if (flags & GPIO_DIR_OUTPUT) {
		if (flags & GPIO_INIT_HIGH) {
			gpio_port->ovrs = 1 << (pin & 0x1F);
		} else {
			gpio_port->ovrc = 1 << (pin & 0x1F);
		}

		gpio_port->oders = 1 << (pin & 0x1F);
	} else {
		gpio_port->oderc = 1 << (pin & 0x1F);
	}

	/* Enable GPIO */
	gpio_port->gpers = 1 << (pin & 0x1F);
}

/** \brief Configuration functionality on a port.
 *
 * \param port The port number.
 * \param mask The mask.
 * \param flags The configuration.
 */
void gpio_configure_group(uint32_t port, uint32_t mask, uint32_t flags)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[port];

	/* Both pull-up and pull-down set means buskeeper */
#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) ||	\
	defined(AVR32_GPIO_212_H_INCLUDED)
	if (flags & GPIO_PULL_DOWN) {
		gpio_port->pders = mask;
	} else {
		gpio_port->pderc = mask;
	}

#endif
	if (flags & GPIO_PULL_UP) {
		gpio_port->puers = mask;
	} else {
		gpio_port->puerc = mask;
	}

	/* Enable open-drain mode if requested */
#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) ||	\
	defined(AVR32_GPIO_212_H_INCLUDED)
	if (flags & GPIO_OPEN_DRAIN) {
		gpio_port->odmers = mask;
	} else {
		gpio_port->odmerc = mask;
	}

	if (flags & GPIO_OPEN_DRAIN) {
		gpio_port->pders = mask;
	} else {
		gpio_port->pderc = mask;
	}

#endif

#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) ||	\
	defined(AVR32_GPIO_212_H_INCLUDED)
	/* Select drive strength */
	if (flags & GPIO_DRIVE_LOW) {
		gpio_port->odcr0s = mask;
	} else {
		gpio_port->odcr0c = mask;
	}

	if (flags & GPIO_DRIVE_HIGH) {
		gpio_port->odcr1s = mask;
	} else {
		gpio_port->odcr1c = mask;
	}

#endif

	/* Select interrupt level for group */
	if (flags & GPIO_INTERRUPT) {
		if (flags & GPIO_BOTHEDGES) {
			gpio_port->imr0c = mask;
			gpio_port->imr1c = mask;
		} else if (flags & GPIO_RISING) {
			gpio_port->imr0s = mask;
			gpio_port->imr1c = mask;
		} else if (flags & GPIO_FALLING) {
			gpio_port->imr0c = mask;
			gpio_port->imr1s = mask;
		}
	}

	/* Select direction and initial pin state */
	if (flags & GPIO_DIR_OUTPUT) {
		if (flags & GPIO_INIT_HIGH) {
			gpio_port->ovrs = mask;
		} else {
			gpio_port->ovrc = mask;
		}

		gpio_port->oders = mask;
	} else {
		gpio_port->oderc = mask;
	}

	/* Enable GPIO */
	gpio_port->gpers = mask;
}

/** \brief Returns the value of a pin.
 *
 * \param pin The pin number.
 *
 * \return The pin value.
 */
bool gpio_get_pin_value(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	return (gpio_port->pvr >> (pin & 0x1F)) & 1;
}

/** \brief Returns the output value set for a GPIO pin.
 *
 * \param pin The pin number.
 *
 * \return The pin output value.
 *
 * \note This function must be used in conjunction with \ref gpio_set_gpio_pin,
 *       \ref gpio_clr_gpio_pin and \ref gpio_tgl_gpio_pin.
 */
bool gpio_get_gpio_pin_output_value(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	return (gpio_port->ovr >> (pin & 0x1F)) & 1;
}

/** \brief Returns the output value set for a GPIO pin using open drain.
 *
 * \param pin The pin number.
 *
 * \return The pin output value.
 *
 * \note This function must be used in conjunction with
 *       \ref gpio_set_gpio_open_drain_pin, \ref gpio_clr_gpio_open_drain_pin
 *       and \ref gpio_tgl_gpio_open_drain_pin.
 */
bool gpio_get_gpio_open_drain_pin_output_value(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	return ((gpio_port->oder >> (pin & 0x1F)) & 1) ^ 1;
}

/** \brief Drives a GPIO pin to 1.
 *
 * \param pin The pin number.
 */
void gpio_set_gpio_pin(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	/* Value to be driven on the I/O line: 1. */
	gpio_port->ovrs  = 1 << (pin & 0x1F);
	/* The GPIO output driver is enabled for that pin. */ 
	gpio_port->oders = 1 << (pin & 0x1F);
	/* The GPIO module controls that pin. */
	gpio_port->gpers = 1 << (pin & 0x1F);
}

/** \brief Drives a GPIO pin to 1.
 *
 * \param pin The pin number.
 *
 * \note The function \ref gpio_configure_pin must be called before.
 */
void gpio_set_pin_high(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	/* Value to be driven on the I/O line: 1. */
	gpio_port->ovrs  = 1 << (pin & 0x1F);
}

/** \brief Drives a GPIO port to 1.
 *
 * \param port The port number.
 * \param mask The mask.
 */
void gpio_set_group_high(uint32_t port, uint32_t mask)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[port];
	
	/* Value to be driven on the I/O group: 1. */
	gpio_port->ovrs  = mask;
}

/** \brief Drives a GPIO pin to 0.
 *
 * \param pin The pin number.
 *
 * \note The function \ref gpio_configure_pin must be called before.
 */
void gpio_set_pin_low(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	/* Value to be driven on the I/O line: 0. */
	gpio_port->ovrc  = 1 << (pin & 0x1F);
}

/** \brief Drives a GPIO pin to 0.
 *
 * \param pin The pin number.
 */
void gpio_clr_gpio_pin(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	/* Value to be driven on the I/O line: 0. */
	gpio_port->ovrc  = 1 << (pin & 0x1F);
	/* The GPIO output driver is enabled for that pin. */
	gpio_port->oders = 1 << (pin & 0x1F);
	/* The GPIO module controls that pin. */
	gpio_port->gpers = 1 << (pin & 0x1F);
}

/** \brief Drives a GPIO port to 0.
 *
 * \param port The port number.
 * \param mask The mask.
 */
void gpio_set_group_low(uint32_t port, uint32_t mask)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[port];
	
	/* Value to be driven on the I/O group: 0. */
	gpio_port->ovrc  = mask;
}

/** \brief Toggles a GPIO pin.
 *
 * \param pin The pin number.
 */
void gpio_tgl_gpio_pin(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	/* Toggle the I/O line. */
	gpio_port->ovrt  = 1 << (pin & 0x1F);
	/* The GPIO output driver is enabled for that pin. */
	gpio_port->oders = 1 << (pin & 0x1F);
	/* The GPIO module controls that pin. */
	gpio_port->gpers = 1 << (pin & 0x1F);
}

/** \brief Toggles a GPIO pin.
 *
 * \param pin The pin number.
 *
 * \note The function \ref gpio_configure_pin must be called before.
 */
void gpio_toggle_pin(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	/* Toggle the I/O line. */
	gpio_port->ovrt  = 1 << (pin & 0x1F);
}

/** \brief Toggles a GPIO group.
 *
 * \param port The port number.
 * \param mask The mask.
 */
void gpio_toggle_group(uint32_t port, uint32_t mask)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[port];
	
	/* Toggle the I/O port. */
	gpio_port->ovrt  = mask;
}

/** \brief Drives a GPIO pin to 1 using open drain.
 *
 * \param pin The pin number.
 */
void gpio_set_gpio_open_drain_pin(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];

	/* The GPIO output driver is disabled for that pin. */
	gpio_port->oderc = 1 << (pin & 0x1F);
	/* The GPIO module controls that pin. */
	gpio_port->gpers = 1 << (pin & 0x1F);
}

/** \brief Drives a GPIO pin to 0 using open drain.
 *
 * \param pin The pin number.
 */
void gpio_clr_gpio_open_drain_pin(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];

	/* Value to be driven on the I/O line: 0. */
	gpio_port->ovrc  = 1 << (pin & 0x1F);
	/* The GPIO output driver is enabled for that pin. */
	gpio_port->oders = 1 << (pin & 0x1F);
	/* The GPIO module controls that pin. */
	gpio_port->gpers = 1 << (pin & 0x1F);
}

/** \brief Toggles a GPIO pin using open drain.
 *
 * \param pin The pin number.
 */
void gpio_tgl_gpio_open_drain_pin(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];

	/* Value to be driven on the I/O line if the GPIO output driver is
	 * enabled: 0. */
	gpio_port->ovrc  = 1 << (pin & 0x1F);
	/* The GPIO output driver is toggled for that pin. */
	gpio_port->odert = 1 << (pin & 0x1F);
	/* The GPIO module controls that pin. */
	gpio_port->gpers = 1 << (pin & 0x1F);
}

/** \brief Enables the glitch filter of a pin.
 *
 * When the glitch filter is enabled, a glitch with duration of less than 1
 * clock cycle is automatically rejected, while a pulse with duration of 2 clock
 * cycles or more is accepted. For pulse durations between 1 clock cycle and 2
 * clock cycles, the pulse may or may not be taken into account, depending on
 * the precise timing of its occurrence. Thus for a pulse to be guaranteed
 * visible it must exceed 2 clock cycles, whereas for a glitch to be reliably
 * filtered out, its duration must not exceed 1 clock cycle. The filter
 * introduces 2 clock cycles latency.
 *
 * \param pin The pin number.
 */
void gpio_enable_pin_glitch_filter(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	gpio_port->gfers = 1 << (pin & 0x1F);
}

/** \brief Disables the glitch filter of a pin.
 *
 * \param pin The pin number.
 */
void gpio_disable_pin_glitch_filter(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	gpio_port->gferc = 1 << (pin & 0x1F);
}

/** \brief Configure the edge detector of an input pin
 *
 * \param pin The pin number.
 * \param mode The edge detection mode (\ref GPIO_PIN_CHANGE,
 *             \ref GPIO_RISING_EDGE or \ref GPIO_FALLING_EDGE).
 *
 * \return \ref GPIO_SUCCESS or \ref GPIO_INVALID_ARGUMENT.
 */
static uint32_t gpio_configure_edge_detector(uint32_t pin, uint32_t mode)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];

	/* Configure the edge detector. */
	switch (mode) {
	case GPIO_PIN_CHANGE:
		gpio_port->imr0c = 1 << (pin & 0x1F);
		gpio_port->imr1c = 1 << (pin & 0x1F);
		break;

	case GPIO_RISING_EDGE:
		gpio_port->imr0s = 1 << (pin & 0x1F);
		gpio_port->imr1c = 1 << (pin & 0x1F);
		break;

	case GPIO_FALLING_EDGE:
		gpio_port->imr0c = 1 << (pin & 0x1F);
		gpio_port->imr1s = 1 << (pin & 0x1F);
		break;

	default:
		return GPIO_INVALID_ARGUMENT;
	}

	return GPIO_SUCCESS;
}

/** \brief Enables the interrupt of a pin with the specified settings.
 *
 * \param pin The pin number.
 * \param mode The trigger mode (\ref GPIO_PIN_CHANGE, \ref GPIO_RISING_EDGE or
 *             \ref GPIO_FALLING_EDGE).
 *
 * \return \ref GPIO_SUCCESS or \ref GPIO_INVALID_ARGUMENT.
 */
uint32_t gpio_enable_pin_interrupt(uint32_t pin, uint32_t mode)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];

	/* Enable the glitch filter. */
	gpio_port->gfers = 1 << (pin & 0x1F);

	/* Configure the edge detector. */
	if (GPIO_INVALID_ARGUMENT == gpio_configure_edge_detector(pin, mode)) {
		return(GPIO_INVALID_ARGUMENT);
	}

	/* Enable interrupt. */
	gpio_port->iers = 1 << (pin & 0x1F);

	return GPIO_SUCCESS;
}

/** \brief Disables the interrupt of a pin.
 *
 * \param pin The pin number.
 */
void gpio_disable_pin_interrupt(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	gpio_port->ierc = 1 << (pin & 0x1F);
}

/** \brief Gets the interrupt flag of a pin.
 *
 * \param pin The pin number.
 *
 * \return The pin interrupt flag.
 */
bool gpio_get_pin_interrupt_flag(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];
	
	return (gpio_port->ifr >> (pin & 0x1F)) & 1;
}

/** \brief Clears the interrupt flag of a pin.
 *
 * \param pin The pin number.
 */
void gpio_clear_pin_interrupt_flag(uint32_t pin)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];

#if (AVR32_GPIO_H_VERSION == 211)
	/* GPIO erratum - Writing a one to the GPIO.IFRC register */
	/* to clear an interrupt will be ignored if interrupt is enabled for the */
	/* corresponding port. */
	/* Work around for the erratum - Disable the interrupt, clear it by
	 * writing */
	/* a one to GPIO.IFRC, then enable the interrupt. */

	/* Save interrupt enable register. */
	uint32_t const gpio_ier = gpio_port->ier;

	/* Disable interrupt. */
	gpio_port->ierc = gpio_ier;

	/* Clear pin interrupt. */
	gpio_port->ifrc = 1 << (pin & 0x1F);

	/* Restore interrupt enable register. */
	gpio_port->ier = gpio_ier;
#else
	gpio_port->ifrc = 1 << (pin & 0x1F);
#endif
}

#if UC3L

/** \brief Configure the peripheral event trigger mode of a pin
 *
 * \param pin The pin number.
 * \param mode The trigger mode (\ref GPIO_PIN_CHANGE, \ref GPIO_RISING_EDGE or
 *             \ref GPIO_FALLING_EDGE).
 * \param use_igf use the Input Glitch Filter (true) or not (false).
 *
 * \return \ref GPIO_SUCCESS or \ref GPIO_INVALID_ARGUMENT.
 */
uint32_t gpio_configure_pin_periph_event_mode(uint32_t pin, uint32_t mode,
		uint32_t use_igf)
{
	volatile avr32_gpio_port_t *gpio_port = &AVR32_GPIO.port[pin >> 5];

	if (true == use_igf) {
		/* Enable the glitch filter. */
		gpio_port->gfers = 1 << (pin & 0x1F);
	} else {
		/* Disable the glitch filter. */
		gpio_port->gferc = 1 << (pin & 0x1F);
	}

	/* Configure the edge detector. */
	return gpio_configure_edge_detector(pin, mode);
}

#endif

/** @} */
