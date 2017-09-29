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

#define IOPORT_CREATE_PIN(port, pin) ((IOPORT_ ## port) * 32 + (pin))
#define IOPORT_BASE_ADDRESS (uintptr_t)PIOA
#define IOPORT_PIO_OFFSET   ((uintptr_t)PIOB - (uintptr_t)PIOA)

#define IOPORT_PIOA     0
#define IOPORT_PIOB     1
#define IOPORT_PIOC     2
#define IOPORT_PIOD     3
#define IOPORT_PIOE     4
#define IOPORT_PIOF     5

/**
 * \weakgroup ioport_group
 * \section ioport_modes IOPORT Modes
 *
 * For details on these please see the SAM Manual.
 *
 * @{
 */

/** \name IOPORT Mode bit definitions */
/** @{ */
#define IOPORT_MODE_MUX_MASK            (0x7 << 0) /*!< MUX bits mask */
#define IOPORT_MODE_MUX_BIT0            (  1 << 0) /*!< MUX BIT0 mask */

#if SAM3N || SAM3S || SAM4S || SAM4E || SAM4N || SAM4C || SAM4CM || SAMG || SAM4CP || SAMV71 || SAMV70 || SAME70 || SAMS70
#define IOPORT_MODE_MUX_BIT1            (  1 << 1) /*!< MUX BIT1 mask */
#endif

#define IOPORT_MODE_MUX_A               (  0 << 0) /*!< MUX function A */
#define IOPORT_MODE_MUX_B               (  1 << 0) /*!< MUX function B */

#if SAM3N || SAM3S || SAM4S || SAM4E || SAM4N || SAM4C || SAM4CM || SAMG || SAM4CP || SAMV71 || SAMV70 || SAME70 || SAMS70
#define IOPORT_MODE_MUX_C               (  2 << 0) /*!< MUX function C */
#define IOPORT_MODE_MUX_D               (  3 << 0) /*!< MUX function D */
#endif

#define IOPORT_MODE_PULLUP              (  1 << 3) /*!< Pull-up */

#if SAM3N || SAM3S || SAM4S || SAM4E || SAM4N || SAM4C || SAM4CM || SAMG || SAM4CP || SAMV71 || SAMV70 || SAME70 || SAMS70
#define IOPORT_MODE_PULLDOWN            (  1 << 4) /*!< Pull-down */
#endif

#define IOPORT_MODE_OPEN_DRAIN          (  1 << 5) /*!< Open drain */

#define IOPORT_MODE_GLITCH_FILTER       (  1 << 6) /*!< Glitch filter */
#define IOPORT_MODE_DEBOUNCE            (  1 << 7) /*!< Input debounce */
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

__always_inline static Pio *arch_ioport_port_to_base(ioport_port_t port)
{
#if (SAM4C || SAM4CM || SAM4CP)
	if (port == IOPORT_PIOC) {
		return (Pio *)(uintptr_t)PIOC;
#  ifdef ID_PIOD
	} else if (port == IOPORT_PIOD) {
		return (Pio *)(uintptr_t)PIOD;
#  endif
	} else {
		return (Pio *)((uintptr_t)IOPORT_BASE_ADDRESS +
		       (IOPORT_PIO_OFFSET * port));
	}
#else
	return (Pio *)((uintptr_t)IOPORT_BASE_ADDRESS +
	       (IOPORT_PIO_OFFSET * port));
#endif
}

__always_inline static Pio *arch_ioport_pin_to_base(ioport_pin_t pin)
{
	return arch_ioport_port_to_base(arch_ioport_pin_to_port_id(pin));
}

__always_inline static ioport_port_mask_t arch_ioport_pin_to_mask(ioport_pin_t pin)
{
	return 1U << (pin & 0x1F);
}

__always_inline static void arch_ioport_init(void)
{
#ifdef ID_PIOA
	sysclk_enable_peripheral_clock(ID_PIOA);
#endif
#ifdef ID_PIOB
	sysclk_enable_peripheral_clock(ID_PIOB);
#endif
#ifdef ID_PIOC
	sysclk_enable_peripheral_clock(ID_PIOC);
#endif
#ifdef ID_PIOD
	sysclk_enable_peripheral_clock(ID_PIOD);
#endif
#ifdef ID_PIOE
	sysclk_enable_peripheral_clock(ID_PIOE);
#endif
#ifdef ID_PIOF
	sysclk_enable_peripheral_clock(ID_PIOF);
#endif
}

__always_inline static void arch_ioport_enable_port(ioport_port_t port,
		ioport_port_mask_t mask)
{
	arch_ioport_port_to_base(port)->PIO_PER = mask;
}

__always_inline static void arch_ioport_disable_port(ioport_port_t port,
		ioport_port_mask_t mask)
{
	arch_ioport_port_to_base(port)->PIO_PDR = mask;
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
	Pio *base = arch_ioport_port_to_base(port);

	if (mode & IOPORT_MODE_PULLUP) {
		base->PIO_PUER = mask;
	} else {
		base->PIO_PUDR = mask;
	}

#if defined(IOPORT_MODE_PULLDOWN)
	if (mode & IOPORT_MODE_PULLDOWN) {
		base->PIO_PPDER = mask;
	} else {
		base->PIO_PPDDR = mask;
	}
#endif

	if (mode & IOPORT_MODE_OPEN_DRAIN) {
		base->PIO_MDER = mask;
	} else {
		base->PIO_MDDR = mask;
	}

	if (mode & (IOPORT_MODE_GLITCH_FILTER | IOPORT_MODE_DEBOUNCE)) {
		base->PIO_IFER = mask;
	} else {
		base->PIO_IFDR = mask;
	}

	if (mode & IOPORT_MODE_DEBOUNCE) {
#if SAM3U || SAM3XA
		base->PIO_DIFSR = mask;
#else
		base->PIO_IFSCER = mask;
#endif
	} else {
#if SAM3U || SAM3XA
		base->PIO_SCIFSR = mask;
#else
		base->PIO_IFSCDR = mask;
#endif
	}

#if !defined(IOPORT_MODE_MUX_BIT1)
	if (mode & IOPORT_MODE_MUX_BIT0) {
		base->PIO_ABSR |= mask;
	} else {
		base->PIO_ABSR &= ~mask;
	}
#else
	if (mode & IOPORT_MODE_MUX_BIT0) {
		base->PIO_ABCDSR[0] |= mask;
	} else {
		base->PIO_ABCDSR[0] &= ~mask;
	}

	if (mode & IOPORT_MODE_MUX_BIT1) {
		base->PIO_ABCDSR[1] |= mask;
	} else {
		base->PIO_ABCDSR[1] &= ~mask;
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
		ioport_port_mask_t mask, enum ioport_direction group_direction)
{
	Pio *base = arch_ioport_port_to_base(port);

	if (group_direction == IOPORT_DIR_OUTPUT) {
		base->PIO_OER = mask;
	} else if (group_direction == IOPORT_DIR_INPUT) {
		base->PIO_ODR = mask;
	}

	base->PIO_OWER = mask;
}

__always_inline static void arch_ioport_set_pin_dir(ioport_pin_t pin,
		enum ioport_direction dir)
{
	Pio *base = arch_ioport_pin_to_base(pin);

	if (dir == IOPORT_DIR_OUTPUT) {
		base->PIO_OER = arch_ioport_pin_to_mask(pin);
	} else if (dir == IOPORT_DIR_INPUT) {
		base->PIO_ODR = arch_ioport_pin_to_mask(pin);
	}

	base->PIO_OWER = arch_ioport_pin_to_mask(pin);
}

__always_inline static void arch_ioport_set_pin_level(ioport_pin_t pin,
		bool level)
{
	Pio *base = arch_ioport_pin_to_base(pin);

	if (level) {
		base->PIO_SODR = arch_ioport_pin_to_mask(pin);
	} else {
		base->PIO_CODR = arch_ioport_pin_to_mask(pin);
	}
}

__always_inline static void arch_ioport_set_port_level(ioport_port_t port,
		ioport_port_mask_t mask, enum ioport_value level)
{
	Pio *base = arch_ioport_port_to_base(port);

	if (level){
		base->PIO_SODR = mask;
	} else {
		base->PIO_CODR = mask;
	}
}

__always_inline static bool arch_ioport_get_pin_level(ioport_pin_t pin)
{
	return arch_ioport_pin_to_base(pin)->PIO_PDSR & arch_ioport_pin_to_mask(pin);
}

__always_inline static ioport_port_mask_t arch_ioport_get_port_level(
		ioport_port_t port, ioport_port_mask_t mask)
{
	return arch_ioport_port_to_base(port)->PIO_PDSR & mask;
}

__always_inline static void arch_ioport_toggle_pin_level(ioport_pin_t pin)
{
	Pio *port = arch_ioport_pin_to_base(pin);
	ioport_port_mask_t mask = arch_ioport_pin_to_mask(pin);

	if (port->PIO_PDSR & arch_ioport_pin_to_mask(pin)) {
		port->PIO_CODR = mask;
	} else {
		port->PIO_SODR = mask;
	}
}

__always_inline static void arch_ioport_toggle_port_level(ioport_port_t port,
		ioport_port_mask_t mask)
{
	arch_ioport_port_to_base(port)->PIO_ODSR ^= mask;
}

__always_inline static void arch_ioport_set_port_sense_mode(ioport_port_t port,
		ioport_port_mask_t mask, enum ioport_sense pin_sense)
{
	Pio *base = arch_ioport_port_to_base(port);
	/*   AIMMR    ELSR    FRLHSR
	 *       0       X         X    IOPORT_SENSE_BOTHEDGES (Default)
	 *       1       0         0    IOPORT_SENSE_FALLING
	 *       1       0         1    IOPORT_SENSE_RISING
	 *       1       1         0    IOPORT_SENSE_LEVEL_LOW
	 *       1       1         1    IOPORT_SENSE_LEVEL_HIGH
	 */
	switch(pin_sense) {
	case IOPORT_SENSE_LEVEL_LOW:
		base->PIO_LSR = mask;
		base->PIO_FELLSR = mask;
		break;
	case IOPORT_SENSE_LEVEL_HIGH:
		base->PIO_LSR = mask;
		base->PIO_REHLSR = mask;
		break;
	case IOPORT_SENSE_FALLING:
		base->PIO_ESR = mask;
		base->PIO_FELLSR = mask;
		break;
	case IOPORT_SENSE_RISING:
		base->PIO_ESR = mask;
		base->PIO_REHLSR = mask;
		break;
	default:
		base->PIO_AIMDR = mask;
		return;
	}
	base->PIO_AIMER = mask;
}

__always_inline static void arch_ioport_set_pin_sense_mode(ioport_pin_t pin,
		enum ioport_sense pin_sense)
{
	arch_ioport_set_port_sense_mode(arch_ioport_pin_to_port_id(pin),
			arch_ioport_pin_to_mask(pin), pin_sense);
}

#endif /* IOPORT_SAM_H */
