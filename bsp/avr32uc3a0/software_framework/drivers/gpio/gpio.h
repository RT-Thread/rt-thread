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

#ifndef _GPIO_H_
#define _GPIO_H_

/**
 * \defgroup group_avr32_drivers_gpio GPIO - General-Purpose Input/Output
 *
 * GPIO gives access to the MCU pins.
 *
 * @{
 */

#include <avr32/io.h>
#include "compiler.h"

/** \name Return Values of the GPIO API
 * @{ */
#define GPIO_SUCCESS            0 /**< Function successfully completed. */
#define GPIO_INVALID_ARGUMENT   1 /**< Input parameters are out of range. */
/** @} */

/** \name Interrupt Trigger Modes
 * @{ */
#define GPIO_PIN_CHANGE         0 /**< Interrupt triggered upon pin change. */
#define GPIO_RISING_EDGE        1 /**< Interrupt triggered upon rising edge. */
#define GPIO_FALLING_EDGE       2 /**< Interrupt triggered upon falling edge. */
/** @} */

/** \name Common defines for GPIO_FLAGS parameter
 * @{ */
#define GPIO_DIR_INPUT  (0 << 0) /**< Pin is Input */
#define GPIO_DIR_OUTPUT (1 << 0) /**< Pin is Output */
#define GPIO_INIT_LOW   (0 << 1) /**< Initial Output State is Low */
#define GPIO_INIT_HIGH  (1 << 1) /**< Initial Output State is High */
#define GPIO_PULL_UP    (1 << 2) /**< Pull-Up (when input) */
#define GPIO_PULL_DOWN  (2 << 2) /**< Pull-Down (when input) */
#define GPIO_BUSKEEPER  (3 << 2) /**< Bus Keeper */
#define GPIO_DRIVE_MIN  (0 << 4) /**< Drive Min Configuration */
#define GPIO_DRIVE_LOW  (1 << 4) /**< Drive Low Configuration */
#define GPIO_DRIVE_HIGH (2 << 4) /**< Drive High Configuration */
#define GPIO_DRIVE_MAX  (3 << 4) /**< Drive Max Configuration */
#define GPIO_OPEN_DRAIN (1 << 6) /**< Open-Drain (when output) */
#define GPIO_INTERRUPT  (1 << 7) /**< Enable Pin/Group Interrupt */
#define GPIO_BOTHEDGES  (3 << 7) /**< Sense Both Edges */
#define GPIO_RISING     (5 << 7) /**< Sense Rising Edge */
#define GPIO_FALLING    (7 << 7) /**< Sense Falling Edge */
/** @} */

/** A type definition of pins and modules connectivity. */
typedef struct {
	uint32_t pin;      /**< Module pin. */
	uint32_t function; /**< Module function. */
} gpio_map_t[];

/** \name Peripheral Bus Interface
 *
 * Low-speed interface with a non-deterministic number of clock cycles per
 * access.
 *
 * This interface operates with lower clock frequencies (fPB <= fCPU), and its
 * timing is not deterministic since it needs to access a shared bus which may
 * be heavily loaded.
 *
 * \note This interface is immediately available without initialization.
 *
 * @{
 */

uint32_t gpio_enable_module(const gpio_map_t gpiomap, uint32_t size);

uint32_t gpio_enable_module_pin(uint32_t pin, uint32_t function);

void gpio_enable_gpio(const gpio_map_t gpiomap, uint32_t size);

void gpio_enable_gpio_pin(uint32_t pin);

void gpio_enable_pin_pull_up(uint32_t pin);

void gpio_disable_pin_pull_up(uint32_t pin);

#if defined(AVR32_GPIO_200_H_INCLUDED) || defined(AVR32_GPIO_210_H_INCLUDED) ||	\
	defined(AVR32_GPIO_212_H_INCLUDED)

void gpio_enable_pin_pull_down(uint32_t pin);

void gpio_disable_pin_pull_down(uint32_t pin);

void gpio_enable_pin_buskeeper(uint32_t pin);

void gpio_disable_pin_buskeeper(uint32_t pin);

#endif

void gpio_configure_pin(uint32_t pin, uint32_t flags);

void gpio_configure_group(uint32_t port, uint32_t mask, uint32_t flags);

bool gpio_get_pin_value(uint32_t pin);

/**
 * \brief Check if the pin is in low logical level.
 *
 * \param pin The pin number.
 * \return bool    \c true if the pin is in low logical level
 *                 \c false if the pin is not in low logical level
 */
__always_inline static bool gpio_pin_is_low(uint32_t pin)
{
	return (gpio_get_pin_value(pin) == 0);
}

/**
 * \brief Check if the pin is in high logical level.
 *
 * \param pin The pin number.
 * \return bool    \c true  if the pin is in high logical level
 *                 \c false if the pin is not in high logical level
 */
__always_inline static bool gpio_pin_is_high(uint32_t pin)
{
	return (gpio_get_pin_value(pin) != 0);
}

bool gpio_get_gpio_pin_output_value(uint32_t pin);

bool gpio_get_gpio_open_drain_pin_output_value(uint32_t pin);

void gpio_set_gpio_pin(uint32_t pin);

void gpio_set_pin_high(uint32_t pin);

void gpio_set_group_high(uint32_t port, uint32_t mask);

void gpio_clr_gpio_pin(uint32_t pin);

void gpio_set_pin_low(uint32_t pin);

void gpio_set_group_low(uint32_t port, uint32_t mask);

void gpio_tgl_gpio_pin(uint32_t pin);

void gpio_toggle_pin(uint32_t pin);

void gpio_toggle_group(uint32_t port, uint32_t mask);

void gpio_set_gpio_open_drain_pin(uint32_t pin);

void gpio_clr_gpio_open_drain_pin(uint32_t pin);

void gpio_tgl_gpio_open_drain_pin(uint32_t pin);

void gpio_enable_pin_glitch_filter(uint32_t pin);

void gpio_disable_pin_glitch_filter(uint32_t pin);

uint32_t gpio_enable_pin_interrupt(uint32_t pin, uint32_t mode);

void gpio_disable_pin_interrupt(uint32_t pin);

bool gpio_get_pin_interrupt_flag(uint32_t pin);

void gpio_clear_pin_interrupt_flag(uint32_t pin);

/** @} */

#if (defined AVR32_GPIO_LOCAL_ADDRESS) || defined(__DOXYGEN__)

/** \name Local Bus Interface
 *
 * High-speed interface with only one clock cycle per access.
 *
 * This interface operates with high clock frequency (fCPU), and its timing is
 * deterministic since it does not need to access a shared bus which may be
 * heavily loaded.
 *
 * \warning To use this interface, the clock frequency of the peripheral bus on
 *          which the GPIO peripheral is connected must be set to the CPU clock
 *          frequency (fPB = fCPU).
 *
 * \note This interface has to be initialized in order to be available.
 *
 * @{
 */

/** \brief Enables the local bus interface for GPIO.
 *
 * \note This function must have been called at least once before using other
 *       functions in this interface.
 */
__always_inline static void gpio_local_init(void)
{
	Set_system_register(AVR32_CPUCR,
			Get_system_register(AVR32_CPUCR) | AVR32_CPUCR_LOCEN_MASK);
}

/** \brief Enables the output driver of a pin.
 *
 * \param pin The pin number.
 *
 * \note \ref gpio_local_init must have been called beforehand.
 *
 * \note This function does not enable the GPIO mode of the pin.
 *       \ref gpio_enable_gpio_pin can be called for this purpose.
 */
__always_inline static void gpio_local_enable_pin_output_driver(uint32_t pin)
{
	AVR32_GPIO_LOCAL.port[pin >> 5].oders = 1 << (pin & 0x1F);
}

/** \brief Disables the output driver of a pin.
 *
 * \param pin The pin number.
 *
 * \note \ref gpio_local_init must have been called beforehand.
 */
__always_inline static void gpio_local_disable_pin_output_driver(uint32_t pin)
{
	AVR32_GPIO_LOCAL.port[pin >> 5].oderc = 1 << (pin & 0x1F);
}

/** \brief Returns the value of a pin.
 *
 * \param pin The pin number.
 *
 * \return The pin value.
 *
 * \note \ref gpio_local_init must have been called beforehand.
 */
__always_inline static bool gpio_local_get_pin_value(uint32_t pin)
{
	return (AVR32_GPIO_LOCAL.port[pin >> 5].pvr >> (pin & 0x1F)) & 1;
}

/** \brief Drives a GPIO pin to 1.
 *
 * \param pin The pin number.
 *
 * \note \ref gpio_local_init must have been called beforehand.
 *
 * \note This function does not enable the GPIO mode of the pin nor its output
 *       driver. \ref gpio_enable_gpio_pin and
 *       \ref gpio_local_enable_pin_output_driver can be called for this
 *       purpose.
 */
__always_inline static void gpio_local_set_gpio_pin(uint32_t pin)
{
	AVR32_GPIO_LOCAL.port[pin >> 5].ovrs = 1 << (pin & 0x1F);
}

/** \brief Drives a GPIO pin to 0.
 *
 * \param pin The pin number.
 *
 * \note \ref gpio_local_init must have been called beforehand.
 *
 * \note This function does not enable the GPIO mode of the pin nor its output
 *       driver. \ref gpio_enable_gpio_pin and
 *       \ref gpio_local_enable_pin_output_driver can be called for this
 *       purpose.
 */
__always_inline static void gpio_local_clr_gpio_pin(uint32_t pin)
{
	AVR32_GPIO_LOCAL.port[pin >> 5].ovrc = 1 << (pin & 0x1F);
}

/** \brief Toggles a GPIO pin.
 *
 * \param pin The pin number.
 *
 * \note \ref gpio_local_init must have been called beforehand.
 *
 * \note This function does not enable the GPIO mode of the pin nor its output
 *       driver. \ref gpio_enable_gpio_pin and
 *       \ref gpio_local_enable_pin_output_driver can be called for this
 *       purpose.
 */
__always_inline static void gpio_local_tgl_gpio_pin(uint32_t pin)
{
	AVR32_GPIO_LOCAL.port[pin >> 5].ovrt = 1 << (pin & 0x1F);
}

/** \brief Initializes the configuration of a GPIO pin so that it can be used
 *         with GPIO open-drain functions.
 *
 * \note This function must have been called at least once before using
 *       \ref gpio_local_set_gpio_open_drain_pin,
 *       \ref gpio_local_clr_gpio_open_drain_pin or
 *       \ref gpio_local_tgl_gpio_open_drain_pin.
 */
__always_inline static void gpio_local_init_gpio_open_drain_pin(uint32_t pin)
{
	AVR32_GPIO_LOCAL.port[pin >> 5].ovrc = 1 << (pin & 0x1F);
}

/** \brief Drives a GPIO pin to 1 using open drain.
 *
 * \param pin The pin number.
 *
 * \note \ref gpio_local_init and \ref gpio_local_init_gpio_open_drain_pin must
 *       have been called beforehand.
 *
 * \note This function does not enable the GPIO mode of the pin.
 *       \ref gpio_enable_gpio_pin can be called for this purpose.
 */
__always_inline static void gpio_local_set_gpio_open_drain_pin(uint32_t pin)
{
	AVR32_GPIO_LOCAL.port[pin >> 5].oderc = 1 << (pin & 0x1F);
}

/** \brief Drives a GPIO pin to 0 using open drain.
 *
 * \param pin The pin number.
 *
 * \note \ref gpio_local_init and \ref gpio_local_init_gpio_open_drain_pin must
 *       have been called beforehand.
 *
 * \note This function does not enable the GPIO mode of the pin.
 *       \ref gpio_enable_gpio_pin can be called for this purpose.
 */
__always_inline static void gpio_local_clr_gpio_open_drain_pin(uint32_t pin)
{
	AVR32_GPIO_LOCAL.port[pin >> 5].oders = 1 << (pin & 0x1F);
}

/** \brief Toggles a GPIO pin using open drain.
 *
 * \param pin The pin number.
 *
 * \note \ref gpio_local_init and \ref gpio_local_init_gpio_open_drain_pin must
 *       have been called beforehand.
 *
 * \note This function does not enable the GPIO mode of the pin.
 *       \ref gpio_enable_gpio_pin can be called for this purpose.
 */
__always_inline static void gpio_local_tgl_gpio_open_drain_pin(uint32_t pin)
{
	AVR32_GPIO_LOCAL.port[pin >> 5].odert = 1 << (pin & 0x1F);
}

/** @} */
#endif /* AVR32_GPIO_LOCAL_ADDRESS */

#if UC3L

/** \name Peripheral Event System support
 *
 * The GPIO can be programmed to output peripheral events whenever an interrupt
 * condition is detected, such as pin value change, or only when a rising or
 * falling edge is detected.
 *
 * @{
 */

/** \brief Enables the peripheral event generation of a pin.
 *
 * \param pin The pin number.
 *
 */
__always_inline static void gpio_enable_pin_periph_event(uint32_t pin)
{
	AVR32_GPIO.port[pin >> 5].oderc = 1 << (pin & 0x1F); /* The GPIO output
	                                                      * driver is
	                                                      * disabled for
	                                                      * that pin. */
	AVR32_GPIO.port[pin >> 5].evers = 1 << (pin & 0x1F);
}

/** \brief Disables the peripheral event generation of a pin.
 *
 * \param pin The pin number.
 *
 */
__always_inline static void gpio_disable_pin_periph_event(uint32_t pin)
{
	AVR32_GPIO.port[pin >> 5].everc = 1 << (pin & 0x1F);
}

uint32_t gpio_configure_pin_periph_event_mode(uint32_t pin, uint32_t mode,
		uint32_t use_igf);

/** @} */

#endif

/** @} */

#endif  /* _GPIO_H_ */
