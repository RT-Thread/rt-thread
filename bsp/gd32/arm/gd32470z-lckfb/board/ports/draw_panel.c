/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-05-23     godmial      Refactor to conform to RT-Thread coding style.
 */

#include <board.h>
#include <rthw.h>
#include <rtthread.h>
#include "drv_lcd.h"
#include "drv_touch.h"

#define COLOR_MAX 14

/* Maximum magnification of pixels */
#define PIXEL_SIZE_MAX 20

typedef struct button_struct
{
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    uint16_t color;
    uint16_t value;
} widget_object_t;

uint16_t        color_buf[COLOR_MAX] = {GRAYBLUE, BLACK, BLUE, BRED, GRED, GBLUE, RED, MAGENTA, GREEN, YELLOW, CYAN, BROWN, BRRED, GRAY};
widget_object_t button_clear, button_color, button_pixel, button_eraser;


/**
 * @brief    Initialize a widget button with given properties.
 *
 * @param    obj     Pointer to the widget object.
 * @param    x       X coordinate of the top-left corner.
 * @param    y       Y coordinate of the top-left corner.
 * @param    w       Width of the widget.
 * @param    h       Height of the widget.
 * @param    color   Color value of the widget.
 * @param    value   Initial value of the widget.
 *
 * @return   None.
 */
void widget_object_init(widget_object_t *obj, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color, uint16_t value)
{
    obj->x     = x;
    obj->y     = y;
    obj->h     = h;
    obj->w     = w;
    obj->color = color;
    obj->value = value;
}


/**
 * @brief    Initialize and display the user interface.
 *
 * This function draws the control buttons for clear, color,
 * pixel size, and eraser on the screen.
 *
 * @return   None.
 */
void ui_init(void)
{
    char temp_buf[20] = {0};

    tli_show_button(button_clear.x, button_clear.y, button_clear.w, button_clear.h, 12, button_clear.color);
    tli_show_string(button_clear.x + 20, button_clear.y + 20, WHITE, button_clear.color, 2, "clear", 0);

    tli_show_button(button_color.x, button_color.y, button_color.w, button_color.h, 12, button_color.color);
    tli_show_string(button_color.x + 20, button_color.y + 20, WHITE, button_color.color, 2, "color", 0);

    tli_show_button(button_pixel.x, button_pixel.y, button_pixel.w, button_pixel.h, 12, button_pixel.color);
    if (button_pixel.value == 0)
    {
        tli_show_string(button_pixel.x + 20, button_pixel.y + 20, WHITE, button_pixel.color, 2, "pixel", 0);
        button_pixel.value = 1;
    }
    else
    {
        sprintf(temp_buf, "%d", button_pixel.value);
        tli_show_string(button_pixel.x + (button_pixel.w / 2) - (strlen(temp_buf) / 2 * 16), button_pixel.y + 20, WHITE, button_pixel.color, 2, (uint8_t *)temp_buf, 0);
    }

    tli_show_button(button_eraser.x, button_eraser.y, button_eraser.w, button_eraser.h, 12, button_eraser.color);
    tli_show_string(button_eraser.x + (button_eraser.w / 2) - (strlen("eraser") / 2 * 16), button_eraser.y + 20, WHITE, button_eraser.color, 2, "eraser", 0);
}

/**
 * @brief    Main routine to test the drawing panel with touch interaction.
 *
 * Initializes LCD and touch interface, sets up buttons and handles user input
 * to draw or erase on the screen based on touch events.
 *
 * @return   Always returns 0.
 */
int draw_panel_test(void)
{
    int  touch_state = 0;
    char color_num   = 0;
    char pixel_size  = 0;

    lcd_disp_config();
    FT5206_Init();
    tli_draw_rectangle(0, 0, 800, 480, WHITE, 1);

    widget_object_init(&button_clear, 800 - 130, 480 - 80, 120, 70, BLUE, 0);
    widget_object_init(&button_color, 10, 480 - 80, 120, 70, BLUE, 0);
    widget_object_init(&button_pixel, 400 - 60, 480 - 80, 120, 70, BLUE, pixel_size);
    widget_object_init(&button_eraser, 800 - 130 - 130, 480 - 80, 120, 70, BLUE, 0);

    ui_init();

    while (1)
    {
        touch_state = FT5206_Scan(0);
        if (touch_state == 1)
        {
            if (tp_dev.x[0] >= button_color.x && tp_dev.x[0] <= (button_color.x + button_color.w))
            {
                if (tp_dev.y[0] >= button_color.y && tp_dev.y[0] <= (button_color.y + button_color.h))
                {
                    letgo_scan(0, button_color.x, button_color.y, (button_color.x + button_color.w), (button_color.y + button_color.h));
                    color_num = (color_num + 1) % COLOR_MAX;
                    widget_object_init(&button_color, button_color.x, button_color.y, button_color.w, button_color.h, color_buf[color_num], 0);
                    ui_init();
                }
            }
            if (tp_dev.x[0] >= button_clear.x && tp_dev.x[0] <= (button_clear.x + button_clear.w))
            {
                if (tp_dev.y[0] >= button_clear.y && tp_dev.y[0] <= (button_clear.y + button_clear.h))
                {
                    letgo_scan(0, button_clear.x, button_clear.y, (button_clear.x + button_clear.w), (button_clear.y + button_clear.h));
                    tli_draw_rectangle(0, 0, 800, 480, WHITE, 1);
                    ui_init();
                }
            }
            if (tp_dev.x[0] >= button_pixel.x && tp_dev.x[0] <= (button_pixel.x + button_pixel.w))
            {
                if (tp_dev.y[0] >= button_pixel.y && tp_dev.y[0] <= (button_pixel.y + button_pixel.h))
                {
                    letgo_scan(0, button_pixel.x, button_pixel.y, (button_pixel.x + button_pixel.w), (button_pixel.y + button_pixel.h));
                    pixel_size++;
                    if (pixel_size > PIXEL_SIZE_MAX) pixel_size = 1;
                    widget_object_init(&button_pixel, button_pixel.x, button_pixel.y, button_pixel.w, button_pixel.h, button_pixel.color, pixel_size);
                    ui_init();
                }
            }

            if (tp_dev.x[0] >= button_eraser.x && tp_dev.x[0] <= (button_eraser.x + button_eraser.w))
            {
                if (tp_dev.y[0] >= button_eraser.y && tp_dev.y[0] <= (button_eraser.y + button_eraser.h))
                {
                    letgo_scan(0, button_eraser.x, button_eraser.y, (button_eraser.x + button_eraser.w), (button_eraser.y + button_eraser.h));
                    button_eraser.value = !button_eraser.value;
                    if (button_eraser.value)
                    {
                        widget_object_init(&button_eraser, 800 - 130 - 130, 480 - 80, 120, 70, BLACK, button_eraser.value);
                    }
                    else
                    {
                        widget_object_init(&button_eraser, 800 - 130 - 130, 480 - 80, 120, 70, BLUE, button_eraser.value);
                    }

                    ui_init();
                }
            }


            if (!button_eraser.value)
            {
                tli_point_enlarge(tp_dev.x[0], tp_dev.y[0], color_buf[color_num], button_pixel.value);
            }
            else
            {
                tli_point_enlarge(tp_dev.x[0], tp_dev.y[0], WHITE, button_pixel.value);
            }
        }
    }
}

INIT_COMPONENT_EXPORT(draw_panel_test);
