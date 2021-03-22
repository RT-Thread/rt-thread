/*
 * File      : fal_flash.c
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
#include <string.h>

/* flash device table, must defined by user */
#if !defined(FAL_FLASH_DEV_TABLE)
#error "You must defined flash device table (FAL_FLASH_DEV_TABLE) on 'fal_cfg.h'"
#endif

static const struct fal_flash_dev * const device_table[] = FAL_FLASH_DEV_TABLE;
static const size_t device_table_len = sizeof(device_table) / sizeof(device_table[0]);
static uint8_t init_ok = 0;

/**
 * Initialize all flash device on FAL flash table
 *
 * @return result
 */
int fal_flash_init(void)
{
    size_t i;

    if (init_ok)
    {
        return 0;
    }

    for (i = 0; i < device_table_len; i++)
    {
        assert(device_table[i]->ops.read);
        assert(device_table[i]->ops.write);
        assert(device_table[i]->ops.erase);
        /* init flash device on flash table */
        if (device_table[i]->ops.init)
        {
            device_table[i]->ops.init();
        }
        log_d("Flash device | %*.*s | addr: 0x%08lx | len: 0x%08x | blk_size: 0x%08x |initialized finish.",
                FAL_DEV_NAME_MAX, FAL_DEV_NAME_MAX, device_table[i]->name, device_table[i]->addr, device_table[i]->len,
                device_table[i]->blk_size);
    }

    init_ok = 1;
    return 0;
}

/**
 * find flash device by name
 *
 * @param name flash device name
 *
 * @return != NULL: flash device
 *            NULL: not found
 */
const struct fal_flash_dev *fal_flash_device_find(const char *name)
{
    assert(init_ok);
    assert(name);

    size_t i;

    for (i = 0; i < device_table_len; i++)
    {
        if (!strncmp(name, device_table[i]->name, FAL_DEV_NAME_MAX)) {
            return device_table[i];
        }
    }

    return NULL;
}
