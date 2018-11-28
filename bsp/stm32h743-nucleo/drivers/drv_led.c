/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-25     LongfeiMa    the first version for stm32h7xx
 */
#include <rtthread.h>
#include <board.h>

#include "drv_led.h"

static void led_thread_entry(void *parameter)
{
	while (1)
	{
		led_on();
		rt_thread_delay(RT_TICK_PER_SECOND);
		led_off();
		rt_thread_delay(RT_TICK_PER_SECOND);
	}
}

int led_hw_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/* Configure GPIO pin: PI1 (LD2) */
	GPIO_InitStruct.Pin   = GPIO_PIN_14;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	return 0;
}
INIT_BOARD_EXPORT(led_hw_init);

int led_init(void)
{
	rt_thread_t tid;

	tid = rt_thread_create("led",
						   led_thread_entry, RT_NULL,
						   512, 12, 5);

	if (tid != RT_NULL)
		rt_thread_startup(tid);

	return 0;
}
INIT_APP_EXPORT(led_init);
