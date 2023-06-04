/*
 * Copyright (c) 2006-2023
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author			Notes
 * 2022-07-07	  zengjianwei		first version
 */
#ifndef __ADC_CONFIG_H__
#define __ADC_CONFIG_H__
#include <gd32f30x.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define 	ADC_PORT_CHANNEL_MAP_TABLE									\
			{															\
			{0, GPIOA, 0, 0, 0},										\
			{0, GPIOA, 1, 1, 1},										\
			{0, GPIOA, 4, 2, 4},										\
			{0, GPIOA, 5, 3, 5},										\
			{0, GPIOC, 4, 4, 14},										\
			{0, GPIOC, 5, 5, 15},										\
			{0, GPIOB, 0, 6, 8},										\
			{0, GPIOB, 1, 7, 9},										\
			{0, GPIOA, 6, 8, 6},										\
			{0, GPIOA, 7, 9, 7},										\
			}

	typedef struct {
		rt_int8_t		ADCindex;					// ADC index:0~2
		rt_uint32_t 	Port;						// gpio port:GPIOA/GPIOB/GPIOC/...
		rt_uint32_t 	pin;						// gpio pin:GPIO_PIN_0~GPIO_PIN_15
		rt_int8_t		rank;						// Order of regular channels
		rt_int8_t		channel;					// ADC channel
	} ADC_PORT_CHANNEL_MAP_S;


#ifdef __cplusplus
}


#endif

#endif /* __ADC_CONFIG_H__ */

