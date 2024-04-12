/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-02-28     Rbb666         first commit
 */
#ifndef __DRV_LCD_H_
#define __DRV_LCD_H_

void lcd_draw_pixel(uint32_t x, uint32_t y, uint16_t color);
void lcd_draw_jpg(int32_t x, int32_t y, const void *p, int32_t xSize, int32_t ySize);
void lcd_gpu_fill_array(size_t x1, size_t y1, size_t x2, size_t y2, uint16_t *color_data);

#endif