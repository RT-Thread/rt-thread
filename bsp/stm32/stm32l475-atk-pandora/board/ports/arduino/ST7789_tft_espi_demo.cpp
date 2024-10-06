/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-10-05     Meco Man      port to RTduino
 */

#include <RTduino.h>

static void st7789_setup(void)
{
}

static void st7789_loop(void)
{
    delay(500);
}
RTDUINO_SKETCH_LOADER("ST7789", st7789_setup, st7789_loop);
