/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "proc.h"
#include "procfs.h"

#include <rthw.h>
#include <rtdbg.h>

#include <fcntl.h>
#include <errno.h>

#include <dfs_dentry.h>
#include <rthw.h>
#include <rtthread.h>
#include <string.h>

struct device_show
{
    char *buf;
    int size;
    int len;
    int index;
};

static char *const device_type_str[RT_Device_Class_Unknown] =
{
    "Character Device",
    "Block Device",
    "Network Interface",
    "MTD Device",
    "CAN Device",
    "RTC",
    "Sound Device",
    "Graphic Device",
    "I2C Bus",
    "USB Slave Device",
    "USB Host Bus",
    "USB OTG Bus",
    "SPI Bus",
    "SPI Device",
    "SDIO Bus",
    "PM Pseudo Device",
    "Pipe",
    "Portal Device",
    "Timer Device",
    "Miscellaneous Device",
    "Sensor Device",
    "Touch Device",
    "Phy Device",
    "Security Device",
    "WLAN Device",
    "Pin Device",
    "ADC Device",
    "DAC Device",
    "WDT Device",
    "PWM Device",
    "Bus Device",
};

static void save_info(struct device_show *dev, char *dev_name)
{
    char tmp[256] = {0};
    int len;

    dev->index ++;

    rt_snprintf(tmp, 256, "%d %s\n", dev->index, dev_name);
    tmp[255] = 0;

    len = rt_strlen(tmp);
    if (dev->size > dev->len + len)
    {
        strcat(dev->buf, tmp);
        dev->len += len;
    }
    else
    {
        if (dev->buf == RT_NULL)
        {
            dev->buf = rt_calloc(1, 4096);
        }
        else
        {
            dev->buf = rt_realloc(dev->buf, dev->size + 4096);
        }
        if (dev->buf)
        {
            dev->size += 4096;
            strcat(dev->buf, tmp);
            dev->len += len;
        }
    }
}

static rt_err_t list_device_hook_(rt_object_t object, void *data)
{
    struct device_show *dev = (struct device_show *)data;
    struct rt_device *device = (struct rt_device *)object;

    if (device->type < RT_Device_Class_Unknown)
    {
        save_info(dev + device->type, device->parent.name);
    }

    return RT_EOK;
}

static void list_device(struct device_show *dev)
{
    rt_list_t *obj_list[RT_LIST_FIND_OBJ_NR];

    rt_object_for_each_safe(RT_Object_Class_Device, list_device_hook_, dev, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));
}

static int show_info(struct dfs_seq_file *seq)
{
    struct device_show _show[RT_Device_Class_Unknown] = {0};

    list_device(_show);

    for (int i = 0; i < RT_Device_Class_Unknown; i++)
    {
        if (_show[i].buf)
        {
            dfs_seq_printf(seq, "%s:\n", device_type_str[i]);
            dfs_seq_write(seq, _show[i].buf, _show[i].len);
            dfs_seq_putc(seq, '\n');

            rt_free(_show[i].buf);
        }
    }

    return 0;
}

static void *seq_start(struct dfs_seq_file *seq, off_t *index)
{
    off_t i = *index; // seq->index

    return NULL + (i == 0);
}

static void seq_stop(struct dfs_seq_file *seq, void *data)
{
}

static void *seq_next(struct dfs_seq_file *seq, void *data, off_t *index)
{
    /* data: The return value of the start or next*/
    off_t i = *index + 1; // seq->index

    *index = i;

    return NULL;
}

static int seq_show(struct dfs_seq_file *seq, void *data)
{
    /* data: The return value of the start or next*/
    show_info(seq);

    return 0;
}

static const struct dfs_seq_ops seq_ops = {
    .start  = seq_start,
    .stop   = seq_stop,
    .next   = seq_next,
    .show   = seq_show,
};

int proc_devices_init(void)
{
    struct proc_dentry *dentry = proc_create_data("devices", 0, NULL, NULL, NULL);
    if (dentry)
    {
        dentry->seq_ops = &seq_ops;
    }
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_devices_init);
