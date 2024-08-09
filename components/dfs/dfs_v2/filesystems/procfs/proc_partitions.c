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


#define LIST_FIND_OBJ_NR 8

typedef struct
{
    rt_list_t *list;
    rt_list_t **array;
    rt_uint8_t type;
    int nr;             /* input: max nr, can't be 0 */
    int nr_out;         /* out: got nr */
} list_get_next_t;

static void list_find_init(list_get_next_t *p, rt_uint8_t type, rt_list_t **array, int nr)
{
    struct rt_object_information *info;
    rt_list_t *list;

    info = rt_object_get_information((enum rt_object_class_type)type);
    list = &info->object_list;

    p->list = list;
    p->type = type;
    p->array = array;
    p->nr = nr;
    p->nr_out = 0;
}

static rt_list_t *list_get_next(rt_list_t *current, list_get_next_t *arg)
{
    int first_flag = 0;
    rt_base_t level;
    rt_list_t *node, *list;
    rt_list_t **array;
    struct rt_object_information *info;
    int nr;

    arg->nr_out = 0;

    if (!arg->nr || !arg->type)
    {
        return (rt_list_t *)RT_NULL;
    }

    list = arg->list;
    info = rt_list_entry(list, struct rt_object_information, object_list);

    if (!current) /* find first */
    {
        node = list;
        first_flag = 1;
    }
    else
    {
        node = current;
    }

    level = rt_spin_lock_irqsave(&info->spinlock);

    if (!first_flag)
    {
        struct rt_object *obj;
        /* The node in the list? */
        obj = rt_list_entry(node, struct rt_object, list);
        if ((obj->type & ~RT_Object_Class_Static) != arg->type)
        {
            rt_spin_unlock_irqrestore(&info->spinlock, level);
            return (rt_list_t *)RT_NULL;
        }
    }

    nr = 0;
    array = arg->array;
    while (1)
    {
        node = node->next;

        if (node == list)
        {
            node = (rt_list_t *)RT_NULL;
            break;
        }
        nr++;
        *array++ = node;
        if (nr == arg->nr)
        {
            break;
        }
    }

    rt_spin_unlock_irqrestore(&info->spinlock, level);
    arg->nr_out = nr;
    return node;
}

static int show_info(struct dfs_seq_file *seq)
{
    rt_base_t level;
    list_get_next_t find_arg;
    struct rt_object_information *info;
    rt_list_t *obj_list[LIST_FIND_OBJ_NR];
    rt_list_t *next = (rt_list_t *)RT_NULL;

    list_find_init(&find_arg, RT_Object_Class_Device, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));
    info = rt_list_entry(find_arg.list, struct rt_object_information, object_list);

    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct rt_object *obj;
                struct rt_device *device;

                obj = rt_list_entry(obj_list[i], struct rt_object, list);
                level = rt_spin_lock_irqsave(&info->spinlock);
                if ((obj->type & ~RT_Object_Class_Static) != find_arg.type)
                {
                    rt_spin_unlock_irqrestore(&info->spinlock, level);
                    continue;
                }

                rt_spin_unlock_irqrestore(&info->spinlock, level);

                device = (struct rt_device *)obj;

                if (device->type == RT_Device_Class_Block)
                {
                    struct rt_device_blk_geometry geometry = { 0 };

                    rt_device_control(device, RT_DEVICE_CTRL_BLK_GETGEOME, &geometry);

                    dfs_seq_printf(seq, "%4d  %7d %14llu   %s\n", 0, 0,
                        geometry.sector_count, device->parent.name);
                }
            }
        }
    } while (next != (rt_list_t *)RT_NULL);

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
    dfs_seq_puts(seq, "major    minor        #blocks  name\n\n");
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

int proc_partitions_init(void)
{
    struct proc_dentry *dentry = proc_create_data("partitions", 0, NULL, NULL, NULL);
    if (dentry)
    {
        dentry->seq_ops = &seq_ops;
    }
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_partitions_init);
