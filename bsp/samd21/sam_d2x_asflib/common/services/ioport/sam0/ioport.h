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
#ifndef IOPORT_SAM0_H
#define IOPORT_SAM0_H

#include <compiler.h>

#define IOPORT_CREATE_PIN(port, pin) ((port) * 32 + (pin))

// Aliases
#if (PORT_GROUPS > 0)
#  define IOPORT_PORTA     0
#endif
#if (PORT_GROUPS > 1)
#  define IOPORT_PORTB     1
#endif
#if (PORT_GROUPS > 2)
#  define IOPORT_PORTC     2
#endif
#if (PORT_GROUPS > 3)
#  define IOPORT_PORTD     3
#endif

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
#define IOPORT_MODE_MUX_MASK            (0xF << 0) /*!< MUX bits mask */
#define IOPORT_MODE_MUX_BIT0            (1 << 0) /*!< MUX BIT0 mask */
#define IOPORT_MODE_MUX_BIT1            (1 << 1) /*!< MUX BIT1 mask */
#define IOPORT_MODE_MUX_BIT2            (1 << 2) /*!< MUX BIT2 mask */
#define IOPORT_MODE_MUX_BIT3            (1 << 3) /*!< MUX BIT3 mask */
#define IOPORT_MODE_MUX_A               (0 << 0) /*!< MUX function A */
#define IOPORT_MODE_MUX_B               (1 << 0) /*!< MUX function B */
#define IOPORT_MODE_MUX_C               (2 << 0) /*!< MUX function C */
#define IOPORT_MODE_MUX_D               (3 << 0) /*!< MUX function D */
#define IOPORT_MODE_MUX_E               (4 << 0) /*!< MUX function E */
#define IOPORT_MODE_MUX_F               (5 << 0) /*!< MUX function F */
#define IOPORT_MODE_MUX_G               (6 << 0) /*!< MUX function G */
#define IOPORT_MODE_MUX_H               (7 << 0) /*!< MUX function H */

#define IOPORT_MODE_PULLUP              (1 << 4) /*!< Pull-up */
#define IOPORT_MODE_PULLDOWN            (1 << 5) /*!< Pull-down */
#define IOPORT_MODE_OPEN_DRAIN          (1 << 6) /*!< Open Drain */
#define IOPORT_MODE_DRIVE_STRENGTH      (1 << 7) /*!< Extra drive strength */
/** @} */

/** @} */

typedef uint32_t ioport_mode_t;
typedef uint32_t ioport_pin_t;
typedef uint32_t ioport_port_t;
typedef uint32_t ioport_port_mask_t;

inline static ioport_port_t arch_ioport_pin_to_port_id(ioport_pin_t pin)
{
	return pin >> 5;
}

inline static PortGroup *arch_ioport_port_to_base(
		ioport_port_t port)
{
	return &PORT->Group[port];
}

inline static PortGroup *arch_ioport_pin_to_base(ioport_pin_t pin)
{
	return arch_ioport_port_to_base(arch_ioport_pin_to_port_id(pin));
}

inline static ioport_port_mask_t arch_ioport_pin_to_mask(ioport_pin_t pin)
{
	return 1U << (pin & 0x1F);
}

inline static void arch_ioport_init(void)
{
	/* No implementation for SAM0 */
}


inline static void arch_ioport_enable_port(ioport_port_t port,
		ioport_port_mask_t mask)
{
	volatile PortGroup *base = arch_ioport_port_to_base(port);

	for (uint32_t i = 0; i < 32; i++) {
		if (mask & (1 << i)) {
			base->PINCFG[i].reg &= ~PORT_PINCFG_PMUXEN;
		}
	}
}

inline static void arch_ioport_disable_port(ioport_port_t port,
		ioport_port_mask_t mask)
{
	volatile PortGroup *base = arch_ioport_port_to_base(port);

	for (uint32_t i = 0; i < 32; i++) {
		if (mask & (1 << i)) {
			base->PINCFG[i].reg |= PORT_PINCFG_PMUXEN;
		}
	}
}

inline static void arch_ioport_enable_pin(ioport_pin_t pin)
{
	arch_ioport_enable_port(arch_ioport_pin_to_port_id(pin),
			arch_ioport_pin_to_mask(pin));
}

inline static void arch_ioport_disable_pin(ioport_pin_t pin)
{
	arch_ioport_disable_port(arch_ioport_pin_to_port_id(pin),
			arch_ioport_pin_to_mask(pin));
}

inline static void arch_ioport_set_port_mode(ioport_port_t port,
		ioport_port_mask_t mask, ioport_mode_t mode)
{
	PortGroup *base = arch_ioport_port_to_base(port);

	uint32_t config_mask = 0;
	uint32_t config_mux  = 0;

	config_mask |= PORT_WRCONFIG_INEN;

	if ((mode & IOPORT_MODE_PULLDOWN) || (mode & IOPORT_MODE_PULLUP)) {
		config_mask |= PORT_WRCONFIG_PULLEN;
	}

#ifdef PORT_WRCONFIG_ODRAIN
	if (mode & IOPORT_MODE_OPEN_DRAIN) {
		config_mask |= PORT_WRCONFIG_ODRAIN;
	}
#endif

	if (mode & IOPORT_MODE_DRIVE_STRENGTH) {
		config_mask |= PORT_WRCONFIG_DRVSTR;
	}

	config_mux = (mode & IOPORT_MODE_MUX_MASK) << PORT_WRCONFIG_PMUX_Pos;

	uint32_t lower_pin_mask = (mask & 0xFFFF);
	uint32_t upper_pin_mask = (mask >> 16);

	base->WRCONFIG.reg =
			(lower_pin_mask << PORT_WRCONFIG_PINMASK_Pos) |
			config_mask | config_mux |
			PORT_WRCONFIG_WRPMUX | PORT_WRCONFIG_WRPINCFG;

	base->WRCONFIG.reg =
			(upper_pin_mask << PORT_WRCONFIG_PINMASK_Pos) |
			config_mask | config_mux |
			PORT_WRCONFIG_WRPMUX | PORT_WRCONFIG_WRPINCFG |
			PORT_WRCONFIG_HWSEL;

	if (mode & IOPORT_MODE_PULLDOWN) {
		base->OUTCLR.reg = mask;
	}
	else if (mode & IOPORT_MODE_PULLUP) {
		base->OUTSET.reg = mask;
	}
}

inline static void arch_ioport_set_pin_mode(ioport_pin_t pin,
		ioport_mode_t mode)
{
	arch_ioport_set_port_mode(arch_ioport_pin_to_port_id(pin),
			arch_ioport_pin_to_mask(pin), mode);
}

inline static void arch_ioport_set_port_dir(ioport_port_t port,
		ioport_port_mask_t mask, unsigned char dir)
{
	if (dir == IOPORT_DIR_OUTPUT) {
		arch_ioport_port_to_base(port)->DIRSET.reg = mask;
	} else if (dir == IOPORT_DIR_INPUT) {
		arch_ioport_port_to_base(port)->DIRCLR.reg = mask;
	}
}

inline static void arch_ioport_set_pin_dir(ioport_pin_t pin,
		enum ioport_direction dir)
{
	PortGroup *base = arch_ioport_pin_to_base(pin);

	if (dir == IOPORT_DIR_OUTPUT) {
		base->DIRSET.reg = arch_ioport_pin_to_mask(pin);
	} else if (dir == IOPORT_DIR_INPUT) {
		base->DIRCLR.reg = arch_ioport_pin_to_mask(pin);
	}

	base->PINCFG[pin].reg |= PORT_PINCFG_INEN;
}

inline static void arch_ioport_set_pin_level(ioport_pin_t pin,
		bool level)
{
	if (level) {
		arch_ioport_pin_to_base(pin)->OUTSET.reg = arch_ioport_pin_to_mask(pin);
	} else {
		arch_ioport_pin_to_base(pin)->OUTCLR.reg = arch_ioport_pin_to_mask(pin);
	}
}

inline static void arch_ioport_set_port_level(ioport_port_t port,
		ioport_port_mask_t mask, enum ioport_value level)
{
	volatile PortGroup *base = arch_ioport_port_to_base(port);

	if (level){
		base->OUTSET.reg = mask;
	} else {
		base->OUTCLR.reg = mask;
	}
}

inline static bool arch_ioport_get_pin_level(ioport_pin_t pin)
{
	return arch_ioport_pin_to_base(pin)->IN.reg & arch_ioport_pin_to_mask(pin);
}

inline static ioport_port_mask_t arch_ioport_get_port_level(
		ioport_port_t port, ioport_port_mask_t mask)
{
	return arch_ioport_port_to_base(port)->IN.reg & mask;
}

inline static void arch_ioport_toggle_pin_level(ioport_pin_t pin)
{
	arch_ioport_pin_to_base(pin)->OUTTGL.reg = arch_ioport_pin_to_mask(pin);
}

inline static void arch_ioport_toggle_port_level(ioport_port_t port,
		ioport_port_mask_t mask)
{
	arch_ioport_port_to_base(port)->OUTTGL.reg = mask;
}

inline static void arch_ioport_set_port_sense_mode(ioport_port_t port,
		ioport_port_mask_t mask, enum ioport_sense pin_sense)
{
	// TODO
	Assert(false);
}

inline static void arch_ioport_set_pin_sense_mode(ioport_pin_t pin,
		enum ioport_sense pin_sense)
{
	arch_ioport_set_port_sense_mode(arch_ioport_pin_to_port_id(pin),
			arch_ioport_pin_to_mask(pin), pin_sense);
}

#endif /* IOPORT_SAM0_H */
