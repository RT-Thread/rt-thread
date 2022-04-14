/**
 * \file
 *
 * \brief SysTick related functionality implementation.
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

#include <compiler.h>
#include <hpl_time_measure.h>
#include <hpl_systick_ARMv7_config.h>
#ifdef _UNIT_TEST_
#include <hri_systick_ARMv7_mock.h>
#endif

/**
 * \brief Initialize system time module
 */
void _system_time_init(void *const hw)
{
	(void)hw;
	SysTick->LOAD = (0xFFFFFF << SysTick_LOAD_RELOAD_Pos);
	SysTick->CTRL = (1 << SysTick_CTRL_ENABLE_Pos) | (CONF_SYSTICK_TICKINT << SysTick_CTRL_TICKINT_Pos)
	                | (1 << SysTick_CTRL_CLKSOURCE_Pos);
}
/**
 * \brief Initialize delay functionality
 */
void _delay_init(void *const hw)
{
	_system_time_init(hw);
}

/**
 * \brief De-initialize system time module
 */
void _system_time_deinit(void *const hw)
{
	(void)hw;
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

/**
 * \brief Get system time
 */
system_time_t _system_time_get(const void *const hw)
{
	(void)hw;
	return (system_time_t)SysTick->VAL;
}

/**
 * \brief Get maximum possible system time
 */
system_time_t _system_time_get_max_time_value(const void *const hw)
{
	(void)hw;
	return 0xFFFFFF;
}
/**
 * \brief Delay loop to delay n number of cycles
 */
void _delay_cycles(void *const hw, uint32_t cycles)
{
	(void)hw;
	uint8_t  n   = cycles >> 24;
	uint32_t buf = cycles;

	while (n--) {
		SysTick->LOAD = 0xFFFFFF;
		SysTick->VAL  = 0xFFFFFF;
		while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
			;
		buf -= 0xFFFFFF;
	}

	SysTick->LOAD = buf;
	SysTick->VAL  = buf;
	while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
		;
}
