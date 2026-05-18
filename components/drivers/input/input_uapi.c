/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <poll.h>
#include <errno.h>
#include <drivers/clock_time.h>
#include <dfs_file.h>

#define DBG_TAG "input.uapi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define _IOC_NRBITS     8
#define _IOC_TYPEBITS   8
#ifndef _IOC_SIZEBITS
#define _IOC_SIZEBITS   14
#endif
#ifndef _IOC_DIRBITS
#define _IOC_DIRBITS    2
#endif

#define _IOC_SIZEMASK   ((1 << _IOC_SIZEBITS) - 1)

#define _IOC_NRSHIFT    0
#define _IOC_TYPESHIFT  (_IOC_NRSHIFT + _IOC_NRBITS)
#define _IOC_SIZESHIFT  (_IOC_TYPESHIFT + _IOC_TYPEBITS)
#define _IOC_DIRSHIFT   (_IOC_SIZESHIFT + _IOC_SIZEBITS)

#define _IOC_NR(nr)     (((nr) >> _IOC_NRSHIFT) & 0xFF)
#define _IOC_TYPE(nr)   (((nr) >> _IOC_TYPESHIFT) & 0xFF)
#define _IOC_SIZE(nr)   (((nr) >> _IOC_SIZESHIFT) & 0x3FFF)
#define _IOC_DIR(nr)    (((nr) >> _IOC_DIRSHIFT) & 0x3)

#ifndef _IOC_READ
#define _IOC_READ       2U
#endif
#ifndef _IOC
#define _IOC(dir, type, nr, size)   \
(                                   \
    ((dir)  << _IOC_DIRSHIFT) |     \
    ((type) << _IOC_TYPESHIFT) |    \
    ((nr)   << _IOC_NRSHIFT) |      \
    ((size) << _IOC_SIZESHIFT)      \
)
#endif

struct input_uapi
{
    struct dfs_file *grabbed_file;

    rt_atomic_t write_idx;
    rt_atomic_t read_idx;
    rt_atomic_t sync_count;
    struct input_event events[RT_INPUT_UAPI_EVENT_MAX];
};

static int input_uapi_fops_open(struct dfs_file *file)
{
    struct rt_input_device *idev = file->vnode->data;

    rt_device_open(&idev->parent, RT_DEVICE_OFLAG_RDWR);

    return 0;
}

static int input_uapi_fops_close(struct dfs_file *file)
{
    struct rt_input_device *idev = file->vnode->data;
    struct input_uapi *uapi = idev->uapi;

    rt_device_close(&idev->parent);

    if (uapi->grabbed_file == file)
    {
        rt_spin_lock(&idev->lock);
        uapi->grabbed_file = RT_NULL;
        rt_spin_unlock(&idev->lock);
    }

    return 0;
}

static int input_uapi_fops_ioctl(struct dfs_file *file, int cmd, void *args)
{
    unsigned int size;
    struct rt_input_device *idev = file->vnode->data;
    struct input_uapi *uapi = idev->uapi;

    switch (cmd)
    {
    case EVIOCGVERSION:
    {
        int version = EV_VERSION;

        rt_memcpy(args, &version, sizeof(int));
        return 0;
    }

    case EVIOCGID:
    {
        static struct input_id virtual_id =
        {
            .bustype = 0x06,    /* BUS_VIRTUAL */
            .vendor = 0x5354,   /* "RT" */
            .product = 0x4556,  /* "EV" */
            .version = RT_VER_NUM >> 16,
        };

        rt_memcpy(args, &virtual_id, sizeof(virtual_id));
        return 0;
    }

    case EVIOCGRAB:
        rt_spin_lock(&idev->lock);

        if (uapi->grabbed_file && uapi->grabbed_file != file)
        {
            rt_spin_unlock(&idev->lock);
            return -EBUSY;
        }

        uapi->grabbed_file = args ? file : RT_NULL;
        rt_spin_unlock(&idev->lock);

        return 0;
    }

    size = _IOC_SIZE(cmd);

    switch (((cmd) & ~(_IOC_SIZEMASK << _IOC_SIZESHIFT)))
    {
    case EVIOCGNAME(0):
        rt_strncpy(args, idev->parent.parent.name, rt_min_t(unsigned int, size, RT_NAME_MAX));
        return 0;

    case EVIOCGPROP(0):
    {
        rt_bitmap_t *bitmap = args;
        const int input_prop_direct = 0x1;

        rt_memset(bitmap, 0, size);

        if (size >= sizeof(rt_bitmap_t))
        {
            bitmap[RT_BIT_WORD(input_prop_direct)] |= RT_BIT_MASK(input_prop_direct);
        }
        return 0;
    }
    }

    if (_IOC_TYPE(cmd) != 'E')
    {
        return -EINVAL;
    }

    if (_IOC_DIR(cmd) == _IOC_READ)
    {
        if ((_IOC_NR(cmd) & ~EV_MAX) == _IOC_NR(EVIOCGBIT(0, 0)))
        {
            rt_size_t bit_len;
            rt_bitmap_t *bitmap;

            switch (_IOC_NR(cmd) & EV_MAX)
            {
            case      0: bitmap = idev->cap;     bit_len = EV_MAX;  break;
            case EV_KEY: bitmap = idev->key_map; bit_len = KEY_MAX; break;
            case EV_REL: bitmap = idev->rel_map; bit_len = REL_MAX; break;
            case EV_ABS: bitmap = idev->abs_map; bit_len = ABS_MAX; break;
            default:
                return -EINVAL;
            }

            size = rt_min_t(rt_size_t, size, ((bit_len + 8) / 8));
            rt_memcpy(args, bitmap, size);

            return 0;
        }

        if ((_IOC_NR(cmd) & ~ABS_MAX) == _IOC_NR(EVIOCGABS(0)))
        {
            rt_size_t max;

            if (!idev->absinfo)
            {
                return -EINVAL;
            }

            max = _IOC_NR(cmd) & ABS_MAX;

            rt_memcpy(args, &idev->absinfo[max], rt_min_t(rt_size_t, size, sizeof(struct input_absinfo)));

            return 0;
        }
    }

    return -EINVAL;
}

static ssize_t input_uapi_fops_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
{
    int err;
    size_t read = 0;
    struct input_event *event = buf;
    struct rt_input_device *idev = file->vnode->data;
    struct input_uapi *uapi = idev->uapi;

    rt_spin_lock(&idev->lock);

    if (uapi->grabbed_file && uapi->grabbed_file != file)
    {
        rt_spin_unlock(&idev->lock);
        return -EAGAIN;
    }

    rt_spin_unlock(&idev->lock);

    if (count != 0 && count < sizeof(struct input_event))
    {
        return -EINVAL;
    }

    for (;;)
    {
        if (!rt_atomic_load(&uapi->sync_count) && (file->flags & O_NONBLOCK))
        {
        #ifdef RT_UAPI_FAKE_BLOCK
            static struct input_event fake_event =
            {
                .type = EV_SYN,
                .code = SYN_REPORT,
            };

            rt_memcpy(event, &fake_event, sizeof(struct input_event));
            read += sizeof(struct input_event);

            return read;
        #else
            return -EAGAIN;
        #endif
        }

        /* No IO is done but we check for error conditions */
        if (count == 0)
        {
            break;
        }

        while (read + sizeof(struct input_event) <= count && rt_atomic_load(&uapi->sync_count))
        {
            rt_ubase_t r_idx = rt_atomic_load(&uapi->read_idx);

            rt_memcpy(event, &uapi->events[r_idx], sizeof(struct input_event));

            rt_atomic_store(&uapi->read_idx, (r_idx + 1) % RT_ARRAY_SIZE(uapi->events));

            if (event->type == EV_SYN && event->code == SYN_REPORT)
            {
                rt_atomic_sub(&uapi->sync_count, 1);
            }

            ++event;
            read += sizeof(struct input_event);
        }

        if (read)
        {
            break;
        }

        if (!(file->flags & O_NONBLOCK))
        {
            err = rt_wqueue_wait_interruptible(&idev->parent.wait_queue, 0, RT_WAITING_FOREVER);

            if (err)
            {
                return err;
            }
        }
    }

    return read;
}

static ssize_t input_uapi_fops_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos)
{
    return -ENOSYS;
}

static int input_uapi_fops_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    /* Only support POLLIN */
    int mask = 0, flags = file->flags & O_ACCMODE;
    struct rt_input_device *idev = file->vnode->data;
    struct input_uapi *uapi = idev->uapi;

    if (flags == O_RDONLY || flags == O_RDWR)
    {
        rt_poll_add(&idev->parent.wait_queue, req);

        if (rt_atomic_load(&uapi->sync_count))
        {
            mask |= POLLIN;
        }
    }

    return mask;
}

static const struct dfs_file_ops input_uapi_fops =
{
    .open = input_uapi_fops_open,
    .close = input_uapi_fops_close,
    .ioctl = input_uapi_fops_ioctl,
    .read = input_uapi_fops_read,
    .write = input_uapi_fops_write,
    .lseek = generic_dfs_lseek,
    .poll = input_uapi_fops_poll,
};

void input_uapi_init(struct rt_input_device *idev)
{
    struct input_uapi *uapi = rt_calloc(1, sizeof(struct input_uapi));

    if (!uapi)
    {
        LOG_W("%s: No memory to create UAPI", rt_dm_dev_get_name(&idev->parent));
        return;
    }

    idev->uapi = uapi;
    idev->parent.fops = &input_uapi_fops;

    RT_ASSERT(sizeof(struct input_absinfo) == sizeof(struct rt_input_absinfo));
    RT_ASSERT(rt_offsetof(struct input_absinfo, value)      == rt_offsetof(struct rt_input_absinfo, value));
    RT_ASSERT(rt_offsetof(struct input_absinfo, minimum)    == rt_offsetof(struct rt_input_absinfo, minimum));
    RT_ASSERT(rt_offsetof(struct input_absinfo, maximum)    == rt_offsetof(struct rt_input_absinfo, maximum));
    RT_ASSERT(rt_offsetof(struct input_absinfo, fuzz)       == rt_offsetof(struct rt_input_absinfo, fuzz));
    RT_ASSERT(rt_offsetof(struct input_absinfo, flat)       == rt_offsetof(struct rt_input_absinfo, flat));
    RT_ASSERT(rt_offsetof(struct input_absinfo, resolution) == rt_offsetof(struct rt_input_absinfo, resolution));
}

void input_uapi_finit(struct rt_input_device *idev)
{
    if (idev->uapi)
    {
        rt_free(idev->uapi);
        idev->uapi = RT_NULL;
        idev->parent.fops = RT_NULL;
    }
}

void input_uapi_event(struct rt_input_device *idev, struct rt_input_event *event)
{
    rt_ubase_t w_idx, next;
    struct input_event *uapi_event;
    struct input_uapi *uapi = idev->uapi;

    if (!idev->parent.ref_count)
    {
        return;
    }

    w_idx = rt_atomic_load(&uapi->write_idx);
    next = (w_idx + 1) % RT_ARRAY_SIZE(uapi->events);

    if (next == rt_atomic_load(&uapi->read_idx))
    {
        LOG_W("%s: Event (type: %d code: %d value: %d) dropped",
                rt_dm_dev_get_name(&idev->parent),
                event->type, event->code, event->value);
        return;
    }

    uapi_event = &uapi->events[w_idx];

    rt_clock_boottime_get_us(&uapi_event->time);
    uapi_event->type = event->type;
    uapi_event->code = event->code;
    uapi_event->value = event->value;

    rt_atomic_store(&uapi->write_idx, next);

    if (event->type == EV_SYN && event->code == SYN_REPORT)
    {
        rt_atomic_add(&uapi->sync_count, 1);
        rt_wqueue_wakeup(&idev->parent.wait_queue, (void *)(rt_ubase_t)POLLIN);
    }
}
