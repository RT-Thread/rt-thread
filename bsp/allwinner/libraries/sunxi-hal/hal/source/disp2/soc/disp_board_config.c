/*
 * disp_board_config.c
 *
 * Copyright (c) 2007-2020 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <hal_clk.h>
#include <hal_gpio.h>
#include "../disp/disp_sys_intf.h"
#include "disp_board_config.h"


// extern struct property_t g_lcd0_config[];
extern struct property_t *g_lcd0_config;
extern struct property_t g_lcd1_config[];
extern struct property_t g_disp_config[];
extern u32 g_disp_config_len;
extern u32 g_lcd0_config_len;
extern u32 g_lcd1_config_len;
#define MAX_PIN_NUM 32

static struct property_t *disp_get_board_config(const char *main_name, u32 *len)
{
    u32 i = 0, j = 0;
    struct property_t *cur = NULL;

    if (!main_name || !len) {
        goto OUT;
    }

    if (!strcmp(main_name, "lcd0")) {
        cur = g_lcd0_config;
        *len = g_lcd0_config_len;
    } else if (!strcmp(main_name, "lcd1")) {
        cur = g_lcd1_config;
        *len = g_lcd1_config_len;
    } else if (!strcmp(main_name, "disp")) {
        cur = g_disp_config;
        *len = g_disp_config_len;
    }
OUT:
    return cur;
}

u32 disp_get_property_value(const char *main_name, const char *sub_name, void *value)
{
    u32 i = 0, len = 0;
    struct property_t *cur = NULL;

    if (!main_name || !sub_name || !value)
        return 0;

    cur = disp_get_board_config(main_name, &len);
    if (!cur || !len)
        goto OUT;

    for (i = 0; i < len; ++i) {
        if(!strcmp(sub_name, cur[i].name)) {
            if (cur[i].type == PROPERTY_INTGER) {
                *(u32 *)value = cur[i].v.value;
            } else if (cur[i].type == PROPERTY_STRING) {
                memcpy(value, cur[i].v.str, strlen(cur[i].v.str) + 1);
            } else if (cur[i].type == PROPERTY_GPIO) {
                struct disp_gpio_set_t *gpio_info =
                    (struct disp_gpio_set_t *)value;
                gpio_info->gpio = cur[i].v.gpio_list.gpio;
                gpio_info->mul_sel = cur[i].v.gpio_list.mul_sel;
                gpio_info->pull = cur[i].v.gpio_list.pull;
                gpio_info->drv_level = cur[i].v.gpio_list.drv_level;
                gpio_info->data = cur[i].v.gpio_list.data;
                memcpy(gpio_info->gpio_name, sub_name, strlen(sub_name) + 1);
            } else if (cur[i].type == PROPERTY_POWER) {
                struct disp_power_t *power =
                    (struct disp_power_t *)value;
                memcpy(power, &cur[i].v.power, sizeof(struct disp_power_t));
            }
            return cur[i].type;
        }
    }
OUT:
    return PROPERTY_UNDEFINED;
}

struct disp_gpio_set_t *disp_get_all_pin_property(const char *main_name,
                         u32 *list_len)
{
    static struct disp_gpio_set_t gpio_list[MAX_PIN_NUM];
    u32 i = 0, len = 0, j = 0;
    struct property_t *cur = NULL;

    memset(gpio_list, 0, 30 * sizeof(struct disp_gpio_set_t));

    if (!main_name)
        return NULL;

    cur = disp_get_board_config(main_name, &len);
    if (!cur || !len)
        return NULL;

    for (i = 0, j = 0; i < len; ++i) {
        if (cur[i].type == PROPERTY_PIN) {
            if (j == MAX_PIN_NUM)
                return NULL;
            memcpy(&gpio_list[j], &cur[i].v.gpio_list,
                   sizeof(struct disp_gpio_set_t));
            ++j;
        }
    }

    *list_len = j;

    return gpio_list;
}
