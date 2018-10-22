/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "timer.h"
#include <rtdevice.h>
#include "fh_arch.h"
#include "libraries/inc/fh_timer.h"
//#include "fh_pmu.h"
//#include "chip_reg.h"
//NEED_CAUTION.

#define TIMER_CLOCK 1000000

#define CONFIG_PAE_PTS_CLOCK   (1000000)
#define TICKS_PER_USEC         (CONFIG_PAE_PTS_CLOCK / 1000000)
#define REG_PAE_PTS_REG        (0xec100000 + 0x0040)

static unsigned long lastdec;
static unsigned long long timestamp;

rt_uint32_t read_pts(void)
{
	return GET_REG(REG_PAE_PTS_REG);
}

unsigned long long get_ticks(void)
{
	rt_uint32_t now = read_pts();
	if (now >= lastdec) {
		/* normal mode */
		timestamp += now - lastdec;
	} else {
		now = read_pts();
		if (now >= lastdec)
			timestamp += now - lastdec;
		else {
			/* we have an overflow ... */
			timestamp += now + 0xffffffff - lastdec;
		}
	}
	lastdec = now;
	return timestamp / (TICKS_PER_USEC * 10);
}

void udelay(unsigned long usec)
{
	unsigned long long tmp;
	rt_uint32_t tmo;
	tmo = (usec + 9) / 10;
	tmp = get_ticks() + tmo; /* get current timestamp */

	while (get_ticks() < tmp)
		/* loop till event */
		/*NOP*/;
}

void rt_timer_handler(int vector, void *param)
{
	timer *tim = param;

	rt_interrupt_enter();
	timer_get_eoi(tim);
	rt_tick_increase();
	rt_interrupt_leave();
}

/**
 * This function will init pit for system ticks
 */
void rt_hw_timer_init()
{
	timer *tim = (timer *) TMR_REG_BASE;
	timer_init(tim);
	/* install interrupt handler */
	rt_hw_interrupt_install(TMR0_IRQn, rt_timer_handler, (void *) tim,
				"sys_tick");
	rt_hw_interrupt_umask(TMR0_IRQn);

	timer_set_mode(tim, TIMER_MODE_PERIODIC);
	timer_set_period(tim, RT_TICK_PER_SECOND, TIMER_CLOCK);
	//timer_set_period(tim, RT_TIMER_TICK_PER_SECOND, TIMER_CLOCK);
	timer_enable_irq(tim);
	timer_enable(tim);

}

