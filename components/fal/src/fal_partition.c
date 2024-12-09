/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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


/* partition magic word */
#define FAL_PART_MAGIC_WORD         0x45503130
#define FAL_PART_MAGIC_WORD_H       0x4550L
#define FAL_PART_MAGIC_WORD_L       0x3130L
#define FAL_PART_MAGIC_WROD         0x45503130

struct part_flash_info
{
    const struct fal_flash_dev *flash_dev;
};

/**
 * FAL partition table config has defined on 'fal_cfg.h'.
 * When this option is disable, it will auto find the partition table on a specified location in flash partition.
 */
#ifdef FAL_PART_HAS_TABLE_CFG

/* check partition table definition */
#if !defined(FAL_PART_TABLE)
#error "You must defined FAL_PART_TABLE on 'fal_cfg.h'"
#endif

/* partition table definition */
static const struct fal_partition partition_table_def[] = FAL_PART_TABLE;
static const struct fal_partition *partition_table = NULL;
/* partition and flash object information cache table */
static struct part_flash_info part_flash_cache[sizeof(partition_table_def) / sizeof(partition_table_def[0])] = { 0 };

#else /* FAL_PART_HAS_TABLE_CFG */

#if !defined(FAL_PART_TABLE_FLASH_DEV_NAME)
#error "You must defined FAL_PART_TABLE_FLASH_DEV_NAME on 'fal_cfg.h'"
#endif

/* check partition table end offset address definition */
#if !defined(FAL_PART_TABLE_END_OFFSET)
#error "You must defined FAL_PART_TABLE_END_OFFSET on 'fal_cfg.h'"
#endif

static struct fal_partition *partition_table = NULL;
static struct part_flash_info *part_flash_cache = NULL;
#endif /* FAL_PART_HAS_TABLE_CFG */

static rt_uint8_t init_ok = 0;
static rt_size_t partition_table_len = 0;

/**
 * print the partition table
 */
void fal_show_part_table(void)
{
    char *item1 = "name", *item2 = "flash_dev";
    rt_size_t i, part_name_max = strlen(item1), flash_dev_name_max = strlen(item2);
    const struct fal_partition *part;

    if (partition_table_len)
    {
        for (i = 0; i < partition_table_len; i++)
        {
            part = &partition_table[i];
            if (strlen(part->name) > part_name_max)
            {
                part_name_max = strlen(part->name);
            }
            if (strlen(part->flash_name) > flash_dev_name_max)
            {
                flash_dev_name_max = strlen(part->flash_name);
            }
        }
    }
    LOG_I("==================== FAL partition table ====================");
    LOG_I("| %-*.*s | %-*.*s |   offset   |    length  |", part_name_max, FAL_DEV_NAME_MAX, item1, flash_dev_name_max,
            FAL_DEV_NAME_MAX, item2);
    LOG_I("-------------------------------------------------------------");
    for (i = 0; i < partition_table_len; i++)
    {

#ifdef FAL_PART_HAS_TABLE_CFG
        part = &partition_table[i];
#else
        part = &partition_table[partition_table_len - i - 1];
#endif

        LOG_I("| %-*.*s | %-*.*s | 0x%08lx | 0x%08x |", part_name_max, FAL_DEV_NAME_MAX, part->name, flash_dev_name_max,
                FAL_DEV_NAME_MAX, part->flash_name, part->offset, part->len);
    }
    LOG_I("=============================================================");
}

static int check_and_update_part_cache(const struct fal_partition *table, rt_size_t len)
{
    const struct fal_flash_dev *flash_dev = NULL;
    rt_size_t i;

#ifndef FAL_PART_HAS_TABLE_CFG
    if (part_flash_cache)
    {
        rt_free(part_flash_cache);
    }
    part_flash_cache = rt_malloc(len * sizeof(struct part_flash_info));
    if (part_flash_cache == NULL)
    {
        LOG_E("Initialize failed! No memory for partition table cache");
        return -2;
    }
#endif

    for (i = 0; i < len; i++)
    {
        flash_dev = fal_flash_device_find(table[i].flash_name);
        if (flash_dev == NULL)
        {
            LOG_D("Warning: Do NOT found the flash device(%s).", table[i].flash_name);
            continue;
        }

        if (table[i].offset >= (long)flash_dev->len)
        {
            LOG_E("Initialize failed! Partition(%s) offset address(%ld) out of flash bound(<%d).",
                    table[i].name, table[i].offset, flash_dev->len);
            partition_table_len = 0;

            return -1;
        }

        part_flash_cache[i].flash_dev = flash_dev;
    }

    return 0;
}

/**
 * Initialize all flash partition on FAL partition table
 *
 * @return partitions total number
 */
int fal_partition_init(void)
{

    if (init_ok)
    {
        return partition_table_len;
    }

#ifdef FAL_PART_HAS_TABLE_CFG
    partition_table = &partition_table_def[0];
    partition_table_len = sizeof(partition_table_def) / sizeof(partition_table_def[0]);
#else
    /* load partition table from the end address FAL_PART_TABLE_END_OFFSET, error return 0 */
    long part_table_offset = FAL_PART_TABLE_END_OFFSET;
    rt_size_t table_num = 0, table_item_size = 0;
    rt_uint8_t part_table_find_ok = 0;
    rt_uint32_t read_magic_word;
    fal_partition_t new_part = NULL;
    rt_size_t i;
    const struct fal_flash_dev *flash_dev = NULL;

    flash_dev = fal_flash_device_find(FAL_PART_TABLE_FLASH_DEV_NAME);
    if (flash_dev == NULL)
    {
        LOG_E("Initialize failed! Flash device (%s) NOT found.", FAL_PART_TABLE_FLASH_DEV_NAME);
        goto _exit;
    }

    /* check partition table offset address */
    if (part_table_offset < 0 || part_table_offset >= (long) flash_dev->len)
    {
        LOG_E("Setting partition table end offset address(%ld) out of flash bound(<%d).", part_table_offset, flash_dev->len);
        goto _exit;
    }

    table_item_size = sizeof(struct fal_partition);
    new_part = (fal_partition_t)rt_malloc(table_item_size);
    if (new_part == NULL)
    {
        LOG_E("Initialize failed! No memory for table buffer.");
        goto _exit;
    }

    /* find partition table location */
    {
        rt_uint8_t read_buf[64];

        part_table_offset -= sizeof(read_buf);
        while (part_table_offset >= 0)
        {
            if (flash_dev->ops.read(part_table_offset, read_buf, sizeof(read_buf)) > 0)
            {
                /* find magic word in read buf */
                for (i = 0; i < sizeof(read_buf) - sizeof(read_magic_word) + 1; i++)
                {
                    read_magic_word = read_buf[0 + i] + (read_buf[1 + i] << 8) + (read_buf[2 + i] << 16) + (read_buf[3 + i] << 24);
                    if (read_magic_word == ((FAL_PART_MAGIC_WORD_H << 16) + FAL_PART_MAGIC_WORD_L))
                    {
                        part_table_find_ok = 1;
                        part_table_offset += i;
                        LOG_D("Find the partition table on '%s' offset @0x%08lx.", FAL_PART_TABLE_FLASH_DEV_NAME,
                                part_table_offset);
                        break;
                    }
                }
            }
            else
            {
                /* read failed */
                break;
            }

            if (part_table_find_ok)
            {
                break;
            }
            else
            {
                /* calculate next read buf position */
                if (part_table_offset >= (long)sizeof(read_buf))
                {
                    part_table_offset -= sizeof(read_buf);
                    part_table_offset += (sizeof(read_magic_word) - 1);
                }
                else if (part_table_offset != 0)
                {
                    part_table_offset = 0;
                }
                else
                {
                    /* find failed */
                    break;
                }
            }
        }
    }

    /* load partition table */
    while (part_table_find_ok)
    {
        memset(new_part, 0x00, table_num);
        if (flash_dev->ops.read(part_table_offset - table_item_size * (table_num), (rt_uint8_t *) new_part,
                table_item_size) < 0)
        {
            LOG_E("Initialize failed! Flash device (%s) read error!", flash_dev->name);
            table_num = 0;
            break;
        }

        if (new_part->magic_word != ((FAL_PART_MAGIC_WORD_H << 16) + FAL_PART_MAGIC_WORD_L))
        {
            break;
        }

        partition_table = (fal_partition_t) rt_realloc(partition_table, table_item_size * (table_num + 1));
        if (partition_table == NULL)
        {
            LOG_E("Initialize failed! No memory for partition table");
            table_num = 0;
            break;
        }

        memcpy(partition_table + table_num, new_part, table_item_size);

        table_num++;
    };

    if (table_num == 0)
    {
        LOG_E("Partition table NOT found on flash: %s (len: %d) from offset: 0x%08x.", FAL_PART_TABLE_FLASH_DEV_NAME,
                FAL_DEV_NAME_MAX, FAL_PART_TABLE_END_OFFSET);
        goto _exit;
    }
    else
    {
        partition_table_len = table_num;
    }
#endif /* FAL_PART_HAS_TABLE_CFG */

    /* check the partition table device exists */
    if (check_and_update_part_cache(partition_table, partition_table_len) != 0)
    {
        goto _exit;
    }

    init_ok = 1;

_exit:

#ifdef FAL_USING_DEBUG
    fal_show_part_table();
#endif /* FAL_USING_DEBUG */

#ifndef FAL_PART_HAS_TABLE_CFG
    if (new_part)
    {
        rt_free(new_part);
    }
#endif /* !FAL_PART_HAS_TABLE_CFG */

    return partition_table_len;
}

/**
 * find the partition by name
 *
 * @param name partition name
 *
 * @return != NULL: partition
 *            NULL: not found
 */
const struct fal_partition *fal_partition_find(const char *name)
{
    if (!init_ok)
        return NULL;

    rt_size_t i;

    for (i = 0; i < partition_table_len; i++)
    {
        if (!strcmp(name, partition_table[i].name))
        {
            return &partition_table[i];
        }
    }

    return NULL;
}

static const struct fal_flash_dev *flash_device_find_by_part(const struct fal_partition *part)
{
    RT_ASSERT(part >= partition_table);
    RT_ASSERT(part <= &partition_table[partition_table_len - 1]);

    return part_flash_cache[part - partition_table].flash_dev;
}

/**
 * get the partition table
 *
 * @param len return the partition table length
 *
 * @return partition table
 */
const struct fal_partition *fal_get_partition_table(rt_size_t *len)
{
    RT_ASSERT(len);

    if (!init_ok)
        return NULL;

    *len = partition_table_len;

    return partition_table;
}

/**
 * set partition table temporarily
 * This setting will modify the partition table temporarily, the setting will be lost after restart.
 *
 * @param table partition table
 * @param len partition table length
 */
void fal_set_partition_table_temp(struct fal_partition *table, rt_size_t len)
{
    RT_ASSERT(table);

    if (!init_ok)
    {
        LOG_E("FAL NOT initialized");
        return;
    }

    check_and_update_part_cache(table, len);

    partition_table_len = len;
    partition_table = table;
}

/**
 * read data from partition
 *
 * @param part partition
 * @param addr relative address for partition
 * @param buf read buffer
 * @param size read size
 *
 * @return >= 0: successful read data size
 *           -1: error
 */
int fal_partition_read(const struct fal_partition *part, rt_uint32_t addr, rt_uint8_t *buf, rt_size_t size)
{
    int ret = 0;
    const struct fal_flash_dev *flash_dev = NULL;

    RT_ASSERT(part);
    RT_ASSERT(buf);

    if (addr + size > part->len)
    {
        LOG_E("Partition read error! Partition(%s) address(0x%08x) out of bound(0x%08x).", part->name, addr + size, part->len);
        return -1;
    }

    flash_dev = flash_device_find_by_part(part);
    if (flash_dev == NULL)
    {
        LOG_E("Partition read error! Don't found flash device(%s) of the partition(%s).", part->flash_name, part->name);
        return -1;
    }

    ret = flash_dev->ops.read(part->offset + addr, buf, size);
    if (ret < 0)
    {
        LOG_E("Partition read error! Flash device(%s) read error!", part->flash_name);
    }

    return ret;
}

/**
 * write data to partition
 *
 * @param part partition
 * @param addr relative address for partition
 * @param buf write buffer
 * @param size write size
 *
 * @return >= 0: successful write data size
 *           -1: error
 */
int fal_partition_write(const struct fal_partition *part, rt_uint32_t addr, const rt_uint8_t *buf, rt_size_t size)
{
    int ret = 0;
    const struct fal_flash_dev *flash_dev = NULL;

    RT_ASSERT(part);
    RT_ASSERT(buf);

    if (addr + size > part->len)
    {
        LOG_E("Partition write error! Partition address out of bound.");
        return -1;
    }

    flash_dev = flash_device_find_by_part(part);
    if (flash_dev == NULL)
    {
        LOG_E("Partition write error!  Don't found flash device(%s) of the partition(%s).", part->flash_name, part->name);
        return -1;
    }

    ret = flash_dev->ops.write(part->offset + addr, buf, size);
    if (ret < 0)
    {
        LOG_E("Partition write error! Flash device(%s) write error!", part->flash_name);
    }

    return ret;
}

/**
 * erase partition data
 *
 * @param part partition
 * @param addr relative address for partition
 * @param size erase size
 *
 * @return >= 0: successful erased data size
 *           -1: error
 */
int fal_partition_erase(const struct fal_partition *part, rt_uint32_t addr, rt_size_t size)
{
    int ret = 0;
    const struct fal_flash_dev *flash_dev = NULL;

    RT_ASSERT(part);

    if (addr + size > part->len)
    {
        LOG_E("Partition erase error! Partition address out of bound.");
        return -1;
    }

    flash_dev = flash_device_find_by_part(part);
    if (flash_dev == NULL)
    {
        LOG_E("Partition erase error! Don't found flash device(%s) of the partition(%s).", part->flash_name, part->name);
        return -1;
    }

    ret = flash_dev->ops.erase(part->offset + addr, size);
    if (ret < 0)
    {
        LOG_E("Partition erase error! Flash device(%s) erase error!", part->flash_name);
    }

    return ret;
}

/**
 * erase partition all data
 *
 * @param part partition
 *
 * @return >= 0: successful erased data size
 *           -1: error
 */
int fal_partition_erase_all(const struct fal_partition *part)
{
    return fal_partition_erase(part, 0, part->len);
}
