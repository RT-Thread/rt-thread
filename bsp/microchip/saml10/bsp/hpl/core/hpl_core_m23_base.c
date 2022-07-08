/**
 * \file
 *
 * \brief Core related functionality implementation.
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
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

#include <hpl_core.h>
#include <hpl_irq.h>
#include <hpl_reset.h>
#include <hpl_sleep.h>
#include <hpl_delay.h>
#ifndef _UNIT_TEST_
#include <utils.h>
#endif
#include <utils_assert.h>
#include <peripheral_clk_config.h>

#ifndef CONF_CPU_FREQUENCY
#define CONF_CPU_FREQUENCY 1000000
#endif

#if CONF_CPU_FREQUENCY < 1000
#define CPU_FREQ_POWER 3
#elif CONF_CPU_FREQUENCY < 10000
#define CPU_FREQ_POWER 4
#elif CONF_CPU_FREQUENCY < 100000
#define CPU_FREQ_POWER 5
#elif CONF_CPU_FREQUENCY < 1000000
#define CPU_FREQ_POWER 6
#elif CONF_CPU_FREQUENCY < 10000000
#define CPU_FREQ_POWER 7
#elif CONF_CPU_FREQUENCY < 100000000
#define CPU_FREQ_POWER 8
#endif

/**
 * \brief The array of interrupt handlers
 */
struct _irq_descriptor *_irq_table[PERIPH_COUNT_IRQn];

/**
 * \brief Reset MCU
 */
void _reset_mcu(void)
{
	NVIC_SystemReset();
}

/**
 * \brief Put MCU to sleep
 */
void _go_to_sleep(void)
{
	__DSB();
	__WFI();
}

/**
 * \brief Retrieve current IRQ number
 */
uint8_t _irq_get_current(void)
{
	return (uint8_t)__get_IPSR() - 16;
}

/**
 * \brief Disable the given IRQ
 */
void _irq_disable(uint8_t n)
{
	NVIC_DisableIRQ((IRQn_Type)n);
}

/**
 * \brief Set the given IRQ
 */
void _irq_set(uint8_t n)
{
	NVIC_SetPendingIRQ((IRQn_Type)n);
}

/**
 * \brief Clear the given IRQ
 */
void _irq_clear(uint8_t n)
{
	NVIC_ClearPendingIRQ((IRQn_Type)n);
}

/**
 * \brief Enable the given IRQ
 */
void _irq_enable(uint8_t n)
{
	NVIC_EnableIRQ((IRQn_Type)n);
}

/**
 * \brief Register IRQ handler
 */
void _irq_register(const uint8_t n, struct _irq_descriptor *const irq)
{
	ASSERT(n < PERIPH_COUNT_IRQn);

	_irq_table[n] = irq;
}

/**
 * \brief Default interrupt handler for unused IRQs.
 */
void Default_Handler(void)
{
	while (1) {
	}
}

/**
 * \brief Retrieve the amount of cycles to delay for the given amount of us
 */
static inline uint32_t _get_cycles_for_us_internal(const uint16_t us, const uint32_t freq, const uint8_t power)
{
	switch (power) {
	case 8:
		return (us * (freq / 100000) + 29) / 30;
	case 7:
		return (us * (freq / 10000) + 299) / 300;
	case 6:
		return (us * (freq / 1000) + 2999) / 3000;
	case 5:
		return (us * (freq / 100) + 29999) / 30000;
	case 4:
		return (us * (freq / 10) + 299999) / 300000;
	default:
		return (us * freq + 2999999) / 3000000;
	}
}

/**
 * \brief Retrieve the amount of cycles to delay for the given amount of us
 */
uint32_t _get_cycles_for_us(const uint16_t us)
{
	return _get_cycles_for_us_internal(us, CONF_CPU_FREQUENCY, CPU_FREQ_POWER);
}

/**
 * \brief Retrieve the amount of cycles to delay for the given amount of ms
 */
static inline uint32_t _get_cycles_for_ms_internal(const uint16_t ms, const uint32_t freq, const uint8_t power)
{
	switch (power) {
	case 8:
		return (ms * (freq / 100000) + 2) / 3 * 100;
	case 7:
		return (ms * (freq / 10000) + 2) / 3 * 10;
	case 6:
		return (ms * (freq / 1000) + 2) / 3;
	case 5:
		return (ms * (freq / 100) + 29) / 30;
	case 4:
		return (ms * (freq / 10) + 299) / 300;
	default:
		return (ms * (freq / 1) + 2999) / 3000;
	}
}

/**
 * \brief Retrieve the amount of cycles to delay for the given amount of ms
 */
uint32_t _get_cycles_for_ms(const uint16_t ms)
{
	return _get_cycles_for_ms_internal(ms, CONF_CPU_FREQUENCY, CPU_FREQ_POWER);
}
/**
 * \brief Initialize delay functionality
 */
void _delay_init(void *const hw)
{
	(void)hw;
}
/**
 * \brief Delay loop to delay n number of cycles
 */
void _delay_cycles(void *const hw, uint32_t cycles)
{
#ifndef _UNIT_TEST_
	(void)hw;
	(void)cycles;
#if defined(__GNUC__) && (__ARMCOMPILER_VERSION > 6000000) /*  Keil MDK with ARM Compiler 6 */
	__asm("__delay:\n"
	      "subs r1, r1, #1\n"
	      "bhi __delay\n");
#elif defined __GNUC__
	__asm(".syntax unified\n"
	      "__delay:\n"
	      "subs r1, r1, #1\n"
	      "bhi __delay\n"
	      ".syntax divided");
#elif defined __CC_ARM
	__asm("__delay:\n"
	      "subs cycles, cycles, #1\n"
	      "bhi __delay\n");
#elif defined __ICCARM__
	__asm("__delay:\n"
	      "subs r1, r1, #1\n"
	      "bhi __delay\n");
#endif
#endif
}
