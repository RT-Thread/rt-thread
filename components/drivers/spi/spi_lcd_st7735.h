/*
 * File      : spi_lcd_st7735.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2016, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/15     xiaofan      first version.
 */
#ifndef __SPI_LCD_ST7735_H__
#define __SPI_LCD_ST7735_H__

/**
 * Probe st7735 lcd
 *
 * @param lcd_name the name which will create graphic device
 *
 * @param spi_dev_name using SPI device name
 *
 * @param horizontal horizontal screen if true, otherwise vertical screen
 *
 * @param pin_dc data/command selection pin
 *
 * @param pin_bl backlight pin, set to -1 if the pin not connected to chip.
 *
 * @param pin_rst reset pin, set to -1 if the pin not connected to chip.
 *
 * @return probed ST7735 device, probe failed will return RT_NULL
 */
rt_device_t rt_st7735_probe(const char * lcd_name, const char * spi_dev_name, rt_bool_t horizontal, rt_base_t pin_dc, rt_base_t pin_bl, rt_base_t pin_rst);

#endif
