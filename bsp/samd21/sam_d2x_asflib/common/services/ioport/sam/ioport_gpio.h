/**
 * \file
 *
 * \brief SAM architecture specific IOPORT service implementation header file.
 *
 * Copyright (c) 2012-2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#ifndef IOPORT_SAM_H
#define IOPORT_SAM_H

#include <sysclk.h>

#define IOPORT_CREATE_PIN(port, pin) ((port) * 32 + (pin))

// Aliases
#define IOPORT_GPIOA     0
#define IOPORT_GPIOB     1
#define IOPORT_GPIOC     2
#define IOPORT_GPIOD     3
#define IOPORT_GPIOE     4
#define IOPORT_GPIOF     5

/**
 * \weakgroup ioport_group
 * \section ioport_modes IOPORT Modes
 *
 * For details on these please see the device datasheet.
 *
 * @{
 */

/** \name IOPORT Mode bit definitions */
/** @{ */
#define IOPORT_MODE_MUX_MASK            (7 << 0) /*!< MUX bits mask */
#define IOPORT_MODE_MUX_BIT0            (1 << 0) /*!< MUX BIT0 mask */
#define IOPORT_MODE_MUX_BIT1            (1 << 1) /*!< MUX BIT1 mask */
#define IOPORT_MODE_MUX_A               (0 << 0) /*!< MUX function A */
#define IOPORT_MODE_MUX_B               (1 << 0) /*!< MUX function B */
#define IOPORT_MODE_MUX_C               (2 << 0) /*!< MUX function C */
#define IOPORT_MODE_MUX_D               (3 << 0) /*!< MUX function D */

#define IOPORT_MODE_MUX_BIT2            (1 << 2) /*!< MUX BIT2 mask */
#define IOPORT_MODE_MUX_E               (4 << 0) /*!< MUX function E */
#define IOPORT_MODE_MUX_F               (5 << 0) /*!< MUX function F */
#define IOPORT_MODE_MUX_G               (6 << 0) /*!< MUX function G */
#define IOPORT_MODE_MUX_H               (7 << 0) /*!< MUX function H */

#define IOPORT_MODE_PULLUP              (1 << 3) /*!< Pull-up */
#define IOPORT_MODE_PULLDOWN            (1 << 4) /*!< Pull-down */
#define IOPORT_MODE_GLITCH_FILTER       (1 << 6) /*!< Glitch filter */
#define IOPORT_MODE_DRIVE_STRENGTH      (1 << 7) /*!< Extra drive strength */
/** @} */

/** @} */

typedef uint32_t ioport_mode_t;
typedef uint32_t ioport_pin_t;
typedef uint32_t ioport_port_t;
typedef uint32_t ioport_port_mask_t;

__always_inline static ioport_port_t arch_ioport_pin_to_port_id(ioport_pin_t pin)
{
	return pin >> 5;
}

__always_inline static volatile GpioPort *arch_ioport_port_to_base(
		ioport_port_t port)
{
	return (volatile GpioPort *)(GPIO_ADDR
		+ port * sizeof(GpioPort));
}

__always_inline static volatile GpioPort *arch_ioport_pin_to_base(ioport_pin_t pin)
{
	return arch_ioport_port_to_base(arch_ioport_pin_to_port_id(pin));
}

__always_inline static ioport_port_mask_t arch_ioport_pin_to_mask(ioport_pin_t pin)
{
	return 1U << (pin & 0x1F);
}

__always_inline static void arch_ioport_init(void)
{
	sysclk_enable_peripheral_clock(GPIO);
}

__always_inline static void arch_ioport_enable_port(ioport_port_t port,
		ioport_port_mask_t mask)
{
	arch_ioport_port_to_base(port)->GPIO_GPERS = mask;
}

__always_inline static void arch_ioport_disable_port(ioport_port_t port,
		ioport_port_mask_t mask)
{
	arch_ioport_port_to_base(port)->GPIO_GPERC = mask;
}

__always_inline static void arch_ioport_enable_pin(ioport_pin_t pin)
{
	arch_ioport_enable_port(arch_ioport_pin_to_port_id(pin),
			arch_ioport_pin_to_mask(pin));
}

__always_inline static void arch_ioport_disable_pin(ioport_pin_t pin)
{
	arch_ioport_disable_port(arch_ioport_pin_to_port_id(pin),
			arch_ioport_pin_to_mask(pin));
}

__always_inline static void arch_ioport_set_port_mode(ioport_port_t port,
		ioport_port_mask_t mask, ioport_mode_t mode)
{
	volatile GpioPort *base = arch_ioport_port_to_base(port);

	if (mode & IOPORT_MODE_PULLUP) {
		base->GPIO_PUERS = mask;
	} else {
		base->GPIO_PUERC = mask;
	}

#ifdef IOPORT_MODE_PULLDOWN
	if (mode & IOPORT_MODE_PULLDOWN) {
		base->GPIO_PDERS = mask;
	} else {
		base->GPIO_PDERC = mask;
	}
#endif

	if (mode & IOPORT_MODE_GLITCH_FILTER) {
		base->GPIO_GFERS = mask;
	} else {
		base->GPIO_GFERC = mask;
	}

#ifdef IOPORT_MODE_DRIVE_STRENGTH
	if (mode & IOPORT_MODE_DRIVE_STRENGTH) {
		base->GPIO_ODCR0S = mask;
	} else {
		base->GPIO_ODCR0C = mask;
	}
#endif

	if (mode & IOPORT_MODE_MUX_BIT0) {
		base->GPIO_PMR0S = mask;
	} else {
		base->GPIO_PMR0C = mask;
	}

	if (mode & IOPORT_MODE_MUX_BIT1) {
		base->GPIO_PMR1S = mask;
	} else {
		base->GPIO_PMR1C = mask;
	}

#ifdef IOPORT_MODE_MUX_BIT2
	if (mode & IOPORT_MODE_MUX_BIT2) {
		base->GPIO_PMR2S = mask;
	} else {
		base->GPIO_PMR2C = mask;
	}
#endif
}

__always_inline static void arch_ioport_set_pin_mode(ioport_pin_t pin,
		ioport_mode_t mode)
{
	arch_ioport_set_port_mode(arch_ioport_pin_to_port_id(pin),
			arch_ioport_pin_to_mask(pin), mode);
}

__always_inline static void arch_ioport_set_port_dir(ioport_port_t port,
		ioport_port_mask_t mask, unsigned char group_direction)
{
	if (group_direction == IOPORT_DIR_OUTPUT) {
		arch_ioport_port_to_base(port)->GPIO_ODERS = mask;
		// Always disable the Schmitt trigger for output pins.
		arch_ioport_port_to_base(port)->GPIO_STERC = mask;
	} else if (group_direction == IOPORT_DIR_INPUT) {
		arch_ioport_port_to_base(port)->GPIO_ODERC = mask;
		// Always enable the Schmitt trigger for input pins.
		arch_ioport_port_to_base(port)->GPIO_STERS = mask;
	}
}

__always_inline static void arch_ioport_set_pin_dir(ioport_pin_t pin,
		enum ioport_direction dir)
{
	if (dir == IOPORT_DIR_OUTPUT) {
		arch_ioport_pin_to_base(pin)->GPIO_ODERS = arch_ioport_pin_to_mask(pin);
		// Always disable the Schmitt trigger for output pins.
		arch_ioport_pin_to_base(pin)->GPIO_STERC = arch_ioport_pin_to_mask(pin);
	} else if (dir == IOPORT_DIR_INPUT) {
		arch_ioport_pin_to_base(pin)->GPIO_ODERC = arch_ioport_pin_to_mask(pin);
		// Always enable the Schmitt trigger for input pins.
		arch_ioport_pin_to_base(pin)->GPIO_STERS = arch_ioport_pin_to_mask(pin);
	}
}

__always_inline static void arch_ioport_set_pin_level(ioport_pin_t pin,
		bool level)
{
	if (level) {
		arch_ioport_pin_to_base(pin)->GPIO_OVRS = arch_ioport_pin_to_mask(pin);
	} else {
		arch_ioport_pin_to_base(pin)->GPIO_OVRC = arch_ioport_pin_to_mask(pin);
	}
}

__always_inline static void arch_ioport_set_port_level(ioport_port_t port,
		ioport_port_mask_t mask, enum ioport_value level)
{
	volatile GpioPort *base = arch_ioport_port_to_base(port);
	if (level){
		base->GPIO_OVRS = mask;
	} else{
		base->GPIO_OVRC = mask;
	}
}

__always_inline static bool arch_ioport_get_pin_level(ioport_pin_t pin)
{
	return arch_ioport_pin_to_base(pin)->GPIO_PVR & arch_ioport_pin_to_mask(pin);
}

__always_inline static ioport_port_mask_t arch_ioport_get_port_level(
		ioport_port_t port, ioport_port_mask_t mask)
{
	return arch_ioport_port_to_base(port)->GPIO_PVR & mask;
}

__always_inline static void arch_ioport_toggle_pin_level(ioport_pin_t pin)
{
	arch_ioport_pin_to_base(pin)->GPIO_OVRT = arch_ioport_pin_to_mask(pin);
}

__always_inline static void arch_ioport_toggle_port_level(ioport_port_t port,
		ioport_port_mask_t mask)
{
	arch_ioport_port_to_base(port)->GPIO_OVRT = mask;
}

__always_inline static void arch_ioport_set_port_sense_mode(ioport_port_t port,
		ioport_port_mask_t mask, enum ioport_sense pin_sense)
{
	volatile GpioPort *base = arch_ioport_port_to_base(port);

	if (pin_sense & 0x01) {
		base->GPIO_IMR0S = mask;
	} else {
		base->GPIO_IMR0C = mask;
	}

	if (pin_sense & 0x02) {
		base->GPIO_IMR1S = mask;
	} else {
		base->GPIO_IMR1C = mask;
	}
}

__always_inline static void arch_ioport_set_pin_sense_mode(ioport_pin_t pin,
		enum ioport_sense pin_sense)
{
	arch_ioport_set_port_sense_mode(arch_ioport_pin_to_port_id(pin),
			arch_ioport_pin_to_mask(pin), pin_sense);
}

#endif /* IOPORT_SAM_H */
