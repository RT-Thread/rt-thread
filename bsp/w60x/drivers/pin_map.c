/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-21     fanwenl      first version
 */

#include <rtthread.h>
#include "wm_io.h"
#include "pin_map.h"

#if defined(SOC_W600_A8xx)
#define WM60X_PIN_NUMBERS 33
#elif defined(SOC_W601_A8xx)
#define WM60X_PIN_NUMBERS 69
#endif

#define __WM_PIN(index, gpio_index) (gpio_index)
#define WM_PIN_NUM(items) (sizeof(items) / sizeof(items[0]))

/* WM chip GPIO map*/
static const rt_int16_t pins[] =
{
    __WM_PIN(0, WM_PIN_DEFAULT),
#if (WM60X_PIN_NUMBERS == 33)
    __WM_PIN(1, WM_PIN_DEFAULT),
    __WM_PIN(2, WM_PIN_DEFAULT),
    __WM_PIN(3, WM_PIN_DEFAULT),
    __WM_PIN(4, WM_PIN_DEFAULT),
    __WM_PIN(5, WM_PIN_DEFAULT),
    __WM_PIN(6, WM_PIN_DEFAULT),
    __WM_PIN(7, WM_PIN_DEFAULT),
    __WM_PIN(8, WM_PIN_DEFAULT),
    __WM_PIN(9, WM_PIN_DEFAULT),
    __WM_PIN(10, WM_PIN_DEFAULT),
    __WM_PIN(11, WM_PIN_DEFAULT),
    __WM_PIN(12, WM_PIN_DEFAULT),
    __WM_PIN(13, WM_IO_PA_00),
    __WM_PIN(14, WM_IO_PA_01),
    __WM_PIN(15, WM_IO_PA_04),
    __WM_PIN(16, WM_PIN_DEFAULT),
    __WM_PIN(17, WM_IO_PA_05),
    __WM_PIN(18, WM_IO_PB_13),
    __WM_PIN(19, WM_IO_PB_14),
    __WM_PIN(20, WM_IO_PB_15),
    __WM_PIN(21, WM_IO_PB_16),
    __WM_PIN(22, WM_IO_PB_17),
    __WM_PIN(23, WM_IO_PB_18),
    __WM_PIN(24, WM_PIN_DEFAULT),
    __WM_PIN(25, WM_PIN_DEFAULT),
    __WM_PIN(26, WM_IO_PB_06),
    __WM_PIN(27, WM_IO_PB_07),
    __WM_PIN(28, WM_IO_PB_08),
    __WM_PIN(29, WM_IO_PB_09),
    __WM_PIN(30, WM_IO_PB_10),
    __WM_PIN(31, WM_IO_PB_11),
    __WM_PIN(32, WM_IO_PB_12),
    __WM_PIN(33, WM_PIN_DEFAULT),
#elif (WM60X_PIN_NUMBERS == 69)
    __WM_PIN(1, WM_IO_PB_19),
    __WM_PIN(2, WM_IO_PB_20),
    __WM_PIN(3, WM_IO_PB_21),
    __WM_PIN(4, WM_IO_PB_22),
    __WM_PIN(5, WM_IO_PB_23),
    __WM_PIN(6, WM_IO_PB_24),
    __WM_PIN(7, WM_IO_PB_25),
    __WM_PIN(8, WM_IO_PB_26),
    __WM_PIN(9, WM_PIN_DEFAULT),
    __WM_PIN(10, WM_PIN_DEFAULT),
    __WM_PIN(11, WM_PIN_DEFAULT),
    __WM_PIN(12, WM_PIN_DEFAULT),
    __WM_PIN(13, WM_PIN_DEFAULT),
    __WM_PIN(14, WM_PIN_DEFAULT),
    __WM_PIN(15, WM_PIN_DEFAULT),
    __WM_PIN(16, WM_PIN_DEFAULT),
    __WM_PIN(17, WM_PIN_DEFAULT),
    __WM_PIN(18, WM_PIN_DEFAULT),
    __WM_PIN(19, WM_PIN_DEFAULT),
    __WM_PIN(20, WM_PIN_DEFAULT),
    __WM_PIN(21, WM_PIN_DEFAULT),
    __WM_PIN(22, WM_PIN_DEFAULT),
    __WM_PIN(23, WM_IO_PA_00),
    __WM_PIN(24, WM_IO_PA_01),
    __WM_PIN(25, WM_IO_PA_02),
    __WM_PIN(26, WM_IO_PA_03),
    __WM_PIN(27, WM_IO_PA_04),
    __WM_PIN(28, WM_PIN_DEFAULT),
    __WM_PIN(29, WM_IO_PA_05),
    __WM_PIN(30, WM_IO_PA_13),
    __WM_PIN(31, WM_IO_PA_14),
    __WM_PIN(32, WM_IO_PA_15),
    __WM_PIN(33, WM_IO_PA_06),
    __WM_PIN(34, WM_PIN_DEFAULT),
    __WM_PIN(35, WM_IO_PA_07),
    __WM_PIN(36, WM_IO_PA_08),
    __WM_PIN(37, WM_IO_PA_09),
    __WM_PIN(38, WM_IO_PA_10),
    __WM_PIN(39, WM_IO_PA_11),
    __WM_PIN(40, WM_IO_PA_12),
    __WM_PIN(41, WM_IO_PB_28),
    __WM_PIN(42, WM_PIN_DEFAULT),
    __WM_PIN(43, WM_IO_PB_13),
    __WM_PIN(44, WM_IO_PB_14),
    __WM_PIN(45, WM_IO_PB_15),
    __WM_PIN(46, WM_PIN_DEFAULT),
    __WM_PIN(47, WM_IO_PB_16),
    __WM_PIN(48, WM_IO_PB_17),
    __WM_PIN(49, WM_IO_PB_18),
    __WM_PIN(50, WM_PIN_DEFAULT),
    __WM_PIN(51, WM_IO_PB_30),
    __WM_PIN(52, WM_IO_PB_31),
    __WM_PIN(53, WM_IO_PB_27),
    __WM_PIN(54, WM_IO_PB_00),
    __WM_PIN(55, WM_IO_PB_01),
    __WM_PIN(56, WM_IO_PB_02),
    __WM_PIN(57, WM_IO_PB_03),
    __WM_PIN(58, WM_PIN_DEFAULT),
    __WM_PIN(59, WM_IO_PB_04),
    __WM_PIN(60, WM_IO_PB_05),
    __WM_PIN(61, WM_IO_PB_06),
    __WM_PIN(62, WM_IO_PB_07),
    __WM_PIN(63, WM_IO_PB_08),
    __WM_PIN(64, WM_IO_PB_09),
    __WM_PIN(65, WM_IO_PB_10),
    __WM_PIN(66, WM_IO_PB_11),
    __WM_PIN(67, WM_IO_PB_12),
    __WM_PIN(68, WM_PIN_DEFAULT),
    __WM_PIN(69, WM_PIN_DEFAULT),
#endif
};

rt_int16_t wm_get_pin(rt_base_t pin_index)
{
    rt_int16_t gpio_pin = WM_PIN_DEFAULT;
    if (pin_index < WM_PIN_NUM(pins))
    {
        gpio_pin = pins[pin_index];
    }
    return gpio_pin;
}
