/*
 * board.h
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
#ifndef _DISP_BOARD_CONFIG_H
#define _DISP_BOARD_CONFIG_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

enum proerty_type {
    PROPERTY_UNDEFINED = 0,
    PROPERTY_INTGER,
    PROPERTY_STRING,
    /*for the pins which function is GPIO(IN or OUT)*/
    PROPERTY_GPIO,
    /*for the pins which function is not GPIO*/
    PROPERTY_PIN,
    /*for axp power*/
    PROPERTY_POWER,
};

/**
 * pro
 */
struct property_t {
    char name[40];
    enum proerty_type type;
    union value_t {
        u32 value;
        char str[40];
        struct disp_gpio_set_t gpio_list;
        struct disp_power_t power;
    } v;
};

u32 disp_get_property_value(const char *main_name, const char *sub_name, void *value);

struct disp_gpio_set_t *disp_get_all_pin_property(const char *main_name,
                         u32 *list_len);

#ifdef __cplusplus
}
#endif

#endif /*End of file*/
