/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2018-07-28     liu2guang      the first version for STM32F469NI-Discovery.
 */
 
#ifndef __DRV_LCD_H_ 
#define __DRV_LCD_H_ 

#include <rtthread.h> 
#include <rtdevice.h>
#include <board.h> 

rt_err_t otm8009a_init(void); 
void otm8009a_layer_init(uint16_t index, uint32_t framebuffer); 
void lcd_clear(uint32_t color); 
void lcd_fill_rect(uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t height); 

#endif
