/**
 * \file
 *
 * \brief Time tick for SAM.
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
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

#include "asf.h"
#include "time_tick.h"

/** Counts for 1ms time ticks. */
volatile uint32_t g_ms_ticks = 0;

#define TICK_MS 1000
/**
 * \brief Handler for Sytem Tick interrupt.
 *
 * Process System Tick Event
 * Increments the g_ms_ticks counter.
 */
void SysTick_Handler(void)
{
	g_ms_ticks++;
}

void time_tick_init(void)
{
	g_ms_ticks = 0;

	/* Configure systick */
	if (SysTick_Config(system_gclk_gen_get_hz(0) / TICK_MS)) {
		Assert(false);
	}
}

uint32_t time_tick_get(void)
{
	return g_ms_ticks;
}

uint32_t time_tick_calc_delay(uint32_t tick_start, uint32_t tick_end)
{
	if (tick_end >= tick_start) {
		return (tick_end - tick_start);
	} else {
		/* In the case of 32-bit couter number overflow */
		return (tick_end + (0xFFFFFFFF - tick_start));
	}
}
