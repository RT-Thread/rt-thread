/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#include <fal.h>
#include <string.h>

#define DBG_TAG    "fal.flash"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

/* flash device table, must defined by user */
#if !defined(FAL_FLASH_DEV_TABLE)
#error "You must defined flash device table (FAL_FLASH_DEV_TABLE) on 'fal_cfg.h'"
#endif

static const struct fal_flash_dev * const device_table[] = FAL_FLASH_DEV_TABLE;
static const rt_size_t device_table_len = sizeof(device_table) / sizeof(device_table[0]);
static rt_uint8_t init_ok = 0;

/**
 * Initialize all flash device on FAL flash table
 *
 * @return result
 */
int fal_flash_init(void)
{
    rt_size_t i;

    if (init_ok)
    {
        return 0;
    }

    for (i = 0; i < device_table_len; i++)
    {
        RT_ASSERT(device_table[i]->ops.read);
        RT_ASSERT(device_table[i]->ops.write);
        RT_ASSERT(device_table[i]->ops.erase);
        /* init flash device on flash table */
        if (device_table[i]->ops.init)
        {
            device_table[i]->ops.init();
        }
        LOG_D("Flash device | %*.*s | addr: 0x%08lx | len: 0x%08x | blk_size: 0x%08x |initialized finish.",
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
 * @return != RT_NULL: flash device
 *            RT_NULL: not found
 */
const struct fal_flash_dev *fal_flash_device_find(const char *name)
{
    RT_ASSERT(init_ok);
    RT_ASSERT(name);

    rt_size_t i;

    for (i = 0; i < device_table_len; i++)
    {
        if (!strncmp(name, device_table[i]->name, FAL_DEV_NAME_MAX)) {
            return device_table[i];
        }
    }

    return RT_NULL;
}
