/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#include <fal.h>
#include <string.h>

#define DBG_TAG "FAL"
#ifdef FAL_USING_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_WARNING
#endif
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
    rt_size_t i, j, offset;

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
        offset = 0;
        for (j = 0; j < FAL_DEV_BLK_MAX; j ++)
        {
            const struct flash_blk *blk = &device_table[i]->blocks[j];
            rt_size_t blk_len = blk->count * blk->size;
            if (blk->count == 0 || blk->size == 0)
                break;

            if(offset > device_table[i]->len)
            {
                LOG_I("Flash device %*.*s: add block failed, offset %d > len %d.",
                FAL_DEV_NAME_MAX, FAL_DEV_NAME_MAX, device_table[i]->name, device_table[i]->addr, offset, device_table[i]->len);
                break;
            }

            LOG_D("                  blk%2d | addr: 0x%08lx | len: 0x%08x | blk_size: 0x%08x |initialized finish.",
                    j, device_table[i]->addr + offset, blk_len, blk->size);
            offset += blk_len;
        }
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
    RT_ASSERT(init_ok);
    RT_ASSERT(name);

    rt_size_t i;

    for (i = 0; i < device_table_len; i++)
    {
        if (!strncmp(name, device_table[i]->name, FAL_DEV_NAME_MAX)) {
            return device_table[i];
        }
    }

    return NULL;
}
