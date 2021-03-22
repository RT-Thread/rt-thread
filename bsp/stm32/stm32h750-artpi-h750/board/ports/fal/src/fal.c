/*
 * File      : fal.c
 * This file is part of FAL (Flash Abstraction Layer) package
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
 * 2018-05-17     armink       the first version
 */

#include <fal.h>

static uint8_t init_ok = 0;

/**
 * FAL (Flash Abstraction Layer) initialization.
 * It will initialize all flash device and all flash partition.
 *
 * @return >= 0: partitions total number
 */
int fal_init(void)
{
    extern int fal_flash_init(void);
    extern int fal_partition_init(void);

    int result;

    /* initialize all flash device on FAL flash table */
    result = fal_flash_init();

    if (result < 0) {
        goto __exit;
    }

    /* initialize all flash partition on FAL partition table */
    result = fal_partition_init();

__exit:

    if ((result > 0) && (!init_ok))
    {
        init_ok = 1;
        log_i("RT-Thread Flash Abstraction Layer (V%s) initialize success.", FAL_SW_VERSION);
    }
    else if(result <= 0)
    {
        init_ok = 0;
        log_e("RT-Thread Flash Abstraction Layer (V%s) initialize failed.", FAL_SW_VERSION);
    }

    return result;
}

/**
 * Check if the FAL is initialized successfully
 * 
 * @return 0: not init or init failed; 1: init success
 */
int fal_init_check(void)
{
    return init_ok;
}
