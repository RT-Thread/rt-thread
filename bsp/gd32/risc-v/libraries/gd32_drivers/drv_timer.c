/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       				Notes
 * 2026/01/19     1085582540@qq.com         first version

 */

#include <rtthread.h>
#ifdef BSP_USING_TIM
#define DBG_LEVEL DBG_LOG
#define LOG_TAG "drv.tim"
#include <rtdbg.h>
#include <rtdevice.h>
#include <board.h>

#define TIMER_INPUT_CLOCK (160 * 1000 * 1000)

#ifndef TIM_DEV_INFO_CONFIG
#define TIM_DEV_INFO_CONFIG            \
	{                                  \
		.maxfreq = 10*1000*1000,            \
		.minfreq = 1000,               \
		.maxcnt = 0xFFFF,              \
		.cntmode = HWTIMER_CNTMODE_UP, \
	}
#endif /* TIM_DEV_INFO_CONFIG */

enum
{
#ifdef BSP_USING_TIM0
	TIM0_INDEX,
#endif

#ifdef BSP_USING_TIM1
	TIM1_INDEX,
#endif

#ifdef BSP_USING_TIM2
	TIM2_INDEX,
#endif

#ifdef BSP_USING_TIM5
	TIM5_INDEX,
#endif

#ifdef BSP_USING_TIM15
	TIM15_INDEX,
#endif

#ifdef BSP_USING_TIM16
	TIM16_INDEX,
#endif
};

struct gd32vw5_hwtimer
{
	rt_hwtimer_t time_device;/*timer object*/
	uint32_t timer_periph; /*timer base address */ 
	IRQn_Type irq;/*time irq*/
	char *name;/*timer name*/
};

static struct gd32vw5_hwtimer gd32vw5_hwtimer_obj[] =
	{
#ifdef BSP_USING_TIM0
		{
			.timer_periph = TIMER0,
			.irq = TIMER0_UP_IRQn,
			.name = "tim0",
		},
#endif
#ifdef BSP_USING_TIM1
		{
			.timer_periph = TIMER1,
			.irq = TIMER1_IRQn,
			.name = "tim1",
		},
#endif
#ifdef BSP_USING_TIM2
		{
			.timer_periph = TIMER2,
			.irq = TIMER2_IRQn,
			.name = "tim2",
		},
#endif
#ifdef BSP_USING_TIM5
		{
			.timer_periph = TIMER5,
			.irq = TIMER5_IRQn,
			.name = "tim5",
		},
#endif
#ifdef BSP_USING_TIM15
		{
			.timer_periph = TIMER15,
			.irq = TIMER15_IRQn,
			.name = "tim15",
		},
#endif
#ifdef BSP_USING_TIM16
		{
			.timer_periph = TIMER16,
			.irq = TIMER16_IRQn,
			.name = "tim16",
		},
#endif
};

/**
 * @brief enable timer clock
 *
 * @param  htim_base
 */
static void gd32vw5_tim_enable_clock(uint32_t timer_periph)
{
	/*set timer clock source prescaler*/ 
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	/*enable timer rcc*/ 
	if (timer_periph == TIMER0)
	{
		rcu_periph_clock_enable(RCU_TIMER0);
	}
	else if (timer_periph == TIMER1)
	{
		rcu_periph_clock_enable(RCU_TIMER1);
	}
	else if (timer_periph == TIMER2)
	{
		rcu_periph_clock_enable(RCU_TIMER2);
	}
	else if (timer_periph == TIMER5)
	{
		rcu_periph_clock_enable(RCU_TIMER5);
	}
	else if (timer_periph == TIMER15)
	{
		rcu_periph_clock_enable(RCU_TIMER15);
	}
	else if (timer_periph == TIMER16)
	{
		rcu_periph_clock_enable(RCU_TIMER16);
	}
}
/**
 * @brief nvic enable
 *
 * @param  gdhwtimer
 */
static void enable_nvic_group(const struct gd32vw5_hwtimer *gdhwtimer)
{

	eclic_irq_disable(gdhwtimer->irq);
}

/**
 * @brief init timer
 * 1.set default period and prescaler
 * 2.enable timer update interrupt
 *
 * @param  timer
 * @param  state
 */
static void gd_timer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
	uint32_t prescaler_value = 0;
	timer_parameter_struct timer_initpara;
	const struct gd32vw5_hwtimer *gdhwtimer = RT_NULL;
	gdhwtimer = rt_container_of(timer, struct gd32vw5_hwtimer, time_device); // 得到定时器的对象
	RT_ASSERT(gdhwtimer);
	LOG_I("%s init", gdhwtimer->name);

	if (state)
	{
		/*enable clk*/
		gd32vw5_tim_enable_clock(gdhwtimer->timer_periph);
		/*restore timer*/
		timer_deinit(gdhwtimer->timer_periph);

		enable_nvic_group(gdhwtimer);
		/* initialize TIMER init parameter struct */
		timer_struct_para_init(&timer_initpara);
		/* TIMER2 configuration */
		timer_initpara.prescaler = TIMER_INPUT_CLOCK / 10000 - 1;
		timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
		timer_initpara.counterdirection = TIMER_COUNTER_UP;
		timer_initpara.period = 10000 - 1;
		timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
		timer_init(gdhwtimer->timer_periph, &timer_initpara);

		/* clear update interrupt bit */
		timer_interrupt_flag_clear(gdhwtimer->timer_periph, TIMER_INT_FLAG_UP);
		/* enable the TIMER update interrupt */
		timer_interrupt_enable(gdhwtimer->timer_periph, TIMER_INT_UP);
*
		/* disable a TIMER */
		timer_disable(gdhwtimer->timer_periph);
	}
	else
	{
		timer_deinit(gdhwtimer->timer_periph);
		timer_disable(gdhwtimer->timer_periph);
	}
}

/**
 * @brief enable timer
 * 1.clean counter
 * 2.set period
 * 3.timer enable
 * 3.timer interrupt enable
 * @param  timer
 * @param  t
 * @param  opmode
 * @return rt_err_t
 */
static rt_err_t timer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t opmode)
{
	rt_err_t result = RT_EOK;

	RT_ASSERT(timer != RT_NULL);
	const struct gd32vw5_hwtimer *gdhwtimer = RT_NULL;
	gdhwtimer = rt_container_of(timer, struct gd32vw5_hwtimer, time_device); // 得到定时器的对象
	RT_ASSERT(gdhwtimer);

	timer_autoreload_value_config(gdhwtimer->timer_periph, cnt - 1);
	timer_counter_value_config(gdhwtimer->timer_periph, 0);
	timer_enable(gdhwtimer->timer_periph);
	eclic_irq_enable(gdhwtimer->irq, 0, 1);

	LOG_I("TIM start period: %d prescaler: %d", cnt, 1 + timer_prescaler_read(gdhwtimer->timer_periph));

	return result;
}

/**
 * @brief stop timer
 * 1.close timer
 * 2.disable interrupt
 * 3.clean time counter
 * @param  timer
 */
static void timer_stop(rt_hwtimer_t *timer)
{
	RT_ASSERT(timer != RT_NULL);
	const struct gd32vw5_hwtimer *gdhwtimer = RT_NULL;
	gdhwtimer = rt_container_of(timer, struct gd32vw5_hwtimer, time_device); // 得到定时器的对象
	RT_ASSERT(gdhwtimer);
	LOG_I("%s stop", gdhwtimer->name);

	timer_disable(gdhwtimer->timer_periph);
	eclic_irq_disable(gdhwtimer->irq);
	timer_counter_value_config(gdhwtimer->timer_periph, 0);
}
/**
 * @brief hwtimer_control
 * 1.repair the timer prescaler
 * @param  timer
 * @param  cmd
 * @param  arg
 * @return rt_err_t
 */
static rt_err_t timer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
	rt_err_t result = -RT_ERROR;
	rt_uint32_t freq = 0;
	rt_uint32_t prescaler_value = 0;
	RT_ASSERT(timer != RT_NULL);
	const struct gd32vw5_hwtimer *gdhwtimer = RT_NULL;
	gdhwtimer = rt_container_of(timer, struct gd32vw5_hwtimer, time_device); // get timer object
	RT_ASSERT(gdhwtimer);
	RT_ASSERT(arg != RT_NULL);
	switch (cmd)
	{
	case HWTIMER_CTRL_FREQ_SET:
	{
		/* set timer frequence */
		freq = *((rt_uint32_t *)arg);
		/*set prescaler*/
		timer_prescaler_config(gdhwtimer->timer_periph, TIMER_INPUT_CLOCK / freq - 1, TIMER_PSC_RELOAD_NOW);
		LOG_I("freq :%d; prescaler: %d", freq, TIMER_INPUT_CLOCK / freq);
		result = RT_EOK;
	}
	break;
	default:
	{
		result = -RT_EINVAL;
	}
	break;
	}

	return result;
}
/**
 * @brief get timer counter
 *
 * @param  timer:handler
 * @return rt_uint32_t return cnt valule
 */
static rt_uint32_t gd_timer_counter_get(rt_hwtimer_t *timer)
{
	rt_uint32_t cnt;
	RT_ASSERT(timer != RT_NULL);
	const struct gd32vw5_hwtimer *gdhwtimer = RT_NULL;
	gdhwtimer = rt_container_of(timer, struct gd32vw5_hwtimer, time_device); // 得到定时器的对象
	RT_ASSERT(gdhwtimer);
	LOG_I("%s init", gdhwtimer->name);
	cnt = timer_counter_read(gdhwtimer->timer_periph);
	return cnt;
}

static const struct rt_hwtimer_info _info = TIM_DEV_INFO_CONFIG;
static const struct rt_hwtimer_ops _ops =
	{
		.init = gd_timer_init,
		.start = timer_start,
		.stop = timer_stop,
		.count_get = gd_timer_counter_get,
		.control = timer_ctrl,
};
/**
 * @brief gd32vw5 time isr
 *
 * @param  gdhwtimer handler
 */
void gd32_timer_isr(struct gd32vw5_hwtimer *gdhwtimer)
{
	if (SET == timer_interrupt_flag_get(gdhwtimer->timer_periph, TIMER_INT_UP))
	{
		/* clear channel 0 interrupt bit */
		timer_interrupt_flag_clear(gdhwtimer->timer_periph, TIMER_INT_UP);
		rt_device_hwtimer_isr(&gdhwtimer->time_device);
	}
}

#ifdef BSP_USING_TIM0
void TIMER0_UP_IRQHandler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();
	gd32_timer_isr(gd32vw5_hwtimer_obj + TIM0_INDEX);
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM1
void TIMER1_IRQHandler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();
	gd32_timer_isr(gd32vw5_hwtimer_obj + TIM1_INDEX);
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM2
void TIMER2_IRQHandler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();
	gd32_timer_isr(gd32vw5_hwtimer_obj + TIM2_INDEX);
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM5
void TIMER5_IRQHandler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();
	gd32_timer_isr(gd32vw5_hwtimer_obj + TIM5_INDEX);
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM15
void TIMER15_IRQHandler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();
	gd32_timer_isr(gd32vw5_hwtimer_obj + TIM15_INDEX);
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM16
void TIMER16_IRQHandler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();
	gd32_timer_isr(gd32vw5_hwtimer_obj + TIM16_INDEX);
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif
/**
 * @brief register hwtimer
 *
 * @return int RT_EOK: register ok;-RT_ERROR:-RT_ERROR fail
 */
static int gd32vw5_hwtimer_init(void)
{
	int i = 0;
	int result = RT_EOK;

	for (i = 0; i < sizeof(gd32vw5_hwtimer_obj) / sizeof(gd32vw5_hwtimer_obj[0]); i++)
	{
		gd32vw5_hwtimer_obj[i].time_device.info = &_info;
		gd32vw5_hwtimer_obj[i].time_device.ops = &_ops;
		if (rt_device_hwtimer_register(&gd32vw5_hwtimer_obj[i].time_device,
									   gd32vw5_hwtimer_obj[i].name, gd32vw5_hwtimer_obj + i) == RT_EOK)
		{
			LOG_D("%s register success", gd32vw5_hwtimer_obj[i].name);
		}
		else
		{
			LOG_E("%s register failed", gd32vw5_hwtimer_obj[i].name);
			result = -RT_ERROR;
		}
	}

	return result;
}
INIT_BOARD_EXPORT(gd32vw5_hwtimer_init);

#endif /* BSP_USING_TIM */
