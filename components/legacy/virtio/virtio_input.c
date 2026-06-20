/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <cpuport.h>

#ifdef RT_USING_VIRTIO_INPUT

#include <virtio_input.h>

static void _set_bit(rt_uint32_t nr, volatile rt_ubase_t *addr)
{
    rt_ubase_t mask = BIT_MASK(nr);
    rt_ubase_t *p = ((rt_ubase_t *)addr) + BIT_WORD(nr);

    *p  |= mask;
}

static rt_ssize_t virtio_input_cfg_select(struct virtio_input_device *virtio_input_dev,
        rt_uint8_t select, rt_uint8_t subsel)
{
    struct virtio_input_config *config = virtio_input_dev->config;

    rt_hw_dsb();
    config->select = select;
    config->subsel = subsel;
    rt_hw_dsb();

    return config->size;
}

static void virtio_input_cfg_bits(struct virtio_input_device *virtio_input_dev,
        rt_uint8_t select, rt_uint8_t subsel, rt_ubase_t *bits, rt_uint32_t bitcount)
{
    int i;
    rt_uint32_t bit;
    rt_uint8_t bytes;
    rt_uint8_t *virtio_bits;
    void *config_base = virtio_input_dev->config;
    rt_off_t offset = (rt_size_t)&((struct virtio_input_config *)0)->bitmap;

    bytes = virtio_input_cfg_select(virtio_input_dev, select, subsel);

    if (bytes == 0)
    {
        return;
    }

    if (bitcount > bytes * 8)
    {
        bitcount = bytes * 8;
    }

    /*
     * Bitmap in virtio config space is a simple stream of bytes,
     * with the first byte carrying bits 0-7, second bits 8-15 and
     * so on.
     */
    virtio_bits = rt_malloc(bytes);

    if (virtio_bits == RT_NULL)
    {
        return;
    }

    for (i = 0; i < bytes; ++i)
    {
        void *buffer = (void *)virtio_bits + i;

        if (virtio_input_dev->virtio_dev.mmio_config->version == 1)
        {
            HWREG8(config_base + offset + i) = *((rt_uint8_t *)buffer);
        }
        else
        {
            rt_memcpy(config_base + offset + i, buffer, sizeof(rt_uint8_t));
        }
    }

    for (bit = 0; bit < bitcount; ++bit)
    {
        if (virtio_bits[bit / 8] & (1 << (bit % 8)))
        {
            _set_bit(bit, bits);
        }
    }

    rt_free(virtio_bits);

    if (select == VIRTIO_INPUT_CFG_EV_BITS)
    {
        _set_bit(subsel, virtio_input_dev->ev_bit);
    }
}

static rt_err_t virtio_input_init(rt_device_t dev)
{
    int i;
    rt_uint16_t idx[VIRTIO_INPUT_QUEUE_MAX_SIZE];
    struct virtio_input_device *virtio_input_dev = (struct virtio_input_device *)dev;
    struct virtio_device *virtio_dev = &virtio_input_dev->virtio_dev;
    struct virtq *queue_event, *queue_status;

    virtio_input_cfg_bits(virtio_input_dev, VIRTIO_INPUT_CFG_EV_BITS, EV_KEY, virtio_input_dev->key_bit, KEY_CNT);
    virtio_input_cfg_bits(virtio_input_dev, VIRTIO_INPUT_CFG_EV_BITS, EV_REL, virtio_input_dev->rel_bit, REL_CNT);
    virtio_input_cfg_bits(virtio_input_dev, VIRTIO_INPUT_CFG_EV_BITS, EV_ABS, virtio_input_dev->abs_bit, ABS_CNT);

    queue_event = &virtio_dev->queues[VIRTIO_INPUT_QUEUE_EVENT];
    queue_status = &virtio_dev->queues[VIRTIO_INPUT_QUEUE_STATUS];

    virtio_alloc_desc_chain(virtio_dev, VIRTIO_INPUT_QUEUE_EVENT, queue_event->num, idx);
    virtio_alloc_desc_chain(virtio_dev, VIRTIO_INPUT_QUEUE_STATUS, queue_status->num, idx);

    for (i = 0; i < queue_event->num; ++i)
    {
        rt_uint16_t id = i;
        void *addr = &virtio_input_dev->recv_events[i];

        virtio_fill_desc(virtio_dev, VIRTIO_INPUT_QUEUE_EVENT, id,
                VIRTIO_VA2PA(addr), sizeof(struct virtio_input_event), VIRTQ_DESC_F_WRITE, 0);

        virtio_submit_chain(virtio_dev, VIRTIO_INPUT_QUEUE_EVENT, id);
    }
    rt_hw_dsb();

    queue_event->avail->flags = 0;
    queue_status->avail->flags = VIRTQ_AVAIL_F_NO_INTERRUPT;

    virtio_queue_notify(virtio_dev, VIRTIO_INPUT_QUEUE_EVENT);

    return RT_EOK;
}

static rt_ssize_t virtio_input_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct virtio_input_device *virtio_input_dev = (struct virtio_input_device *)dev;

    if (buffer == RT_NULL || pos + size >= virtio_input_dev->virtio_dev.queues[VIRTIO_INPUT_QUEUE_EVENT].num)
    {
        return 0;
    }

    rt_mutex_take(&virtio_input_dev->rw_mutex, RT_WAITING_FOREVER);

    rt_memcpy(buffer, &virtio_input_dev->bcst_events[pos], size);

    rt_mutex_release(&virtio_input_dev->rw_mutex);

    return size;
}

static rt_ssize_t virtio_input_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct virtio_input_device *virtio_input_dev = (struct virtio_input_device *)dev;

    if (buffer == RT_NULL || pos + size >= virtio_input_dev->virtio_dev.queues[VIRTIO_INPUT_QUEUE_EVENT].num)
    {
        return 0;
    }

    rt_mutex_take(&virtio_input_dev->rw_mutex, RT_WAITING_FOREVER);

    rt_memcpy(&virtio_input_dev->bcst_events[pos], buffer, size);

    rt_mutex_release(&virtio_input_dev->rw_mutex);

    return size;
}

static rt_err_t virtio_input_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t status = RT_EOK;
    struct virtio_input_device *virtio_input_dev = (struct virtio_input_device *)dev;
    struct virtio_device *virtio_dev = &virtio_input_dev->virtio_dev;
    struct virtio_input_config *config = virtio_input_dev->config;

    if (args == RT_NULL)
    {
        return -RT_ERROR;
    }

    switch (cmd)
    {
    case VIRTIO_DEVICE_CTRL_INPUT_GET_TYPE:

        *(enum virtio_input_type *)args = virtio_input_dev->type;

        break;
    case VIRTIO_DEVICE_CTRL_INPUT_BIND_BSCT_HANDLER:

        virtio_input_dev->bsct_handler = args;

        break;
    case VIRTIO_DEVICE_CTRL_INPUT_GET_ABS_X_INFO:

        virtio_input_cfg_select(virtio_input_dev, VIRTIO_INPUT_CFG_ABS_INFO, VIRTIO_INPUT_ABS_AXIS_X);
        rt_memcpy(args, config, sizeof(struct virtio_input_config));

        break;
    case VIRTIO_DEVICE_CTRL_INPUT_GET_ABS_Y_INFO:

        virtio_input_cfg_select(virtio_input_dev, VIRTIO_INPUT_CFG_ABS_INFO, VIRTIO_INPUT_ABS_AXIS_Y);
        rt_memcpy(args, config, sizeof(struct virtio_input_config));

        break;
    case VIRTIO_DEVICE_CTRL_INPUT_SET_STATUS:
        {
            rt_uint16_t id;
            void *addr;
            struct virtq *queue_status = &virtio_dev->queues[VIRTIO_INPUT_QUEUE_STATUS];

#ifdef RT_USING_SMP
            rt_base_t level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif
            id = queue_status->avail->idx % queue_status->num;
            addr = &virtio_input_dev->xmit_events[id];

            rt_memcpy(addr, args, sizeof(struct virtio_input_event));

            virtio_free_desc(virtio_dev, VIRTIO_INPUT_QUEUE_STATUS, id);

            virtio_fill_desc(virtio_dev, VIRTIO_INPUT_QUEUE_STATUS, id,
                    VIRTIO_VA2PA(addr), sizeof(struct virtio_input_event), 0, 0);

            virtio_submit_chain(virtio_dev, VIRTIO_INPUT_QUEUE_STATUS, id);

            virtio_queue_notify(virtio_dev, VIRTIO_INPUT_QUEUE_STATUS);

            virtio_alloc_desc(virtio_dev, VIRTIO_INPUT_QUEUE_STATUS);

#ifdef RT_USING_SMP
            rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif
        }
        break;
    case VIRTIO_DEVICE_CTRL_INPUT_GET_EV_BIT:

        rt_memcpy(args, virtio_input_dev->ev_bit, sizeof(virtio_input_dev->ev_bit));

        break;
    case VIRTIO_DEVICE_CTRL_INPUT_GET_KEY_BIT:

        rt_memcpy(args, virtio_input_dev->key_bit, sizeof(virtio_input_dev->key_bit));

        break;
    case VIRTIO_DEVICE_CTRL_INPUT_GET_REL_BIT:

        rt_memcpy(args, virtio_input_dev->rel_bit, sizeof(virtio_input_dev->rel_bit));

        break;
    case VIRTIO_DEVICE_CTRL_INPUT_GET_ABS_BIT:

        rt_memcpy(args, virtio_input_dev->abs_bit, sizeof(virtio_input_dev->abs_bit));

        break;
    default:
        status = -RT_EINVAL;
        break;
    }

    return status;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops virtio_input_ops =
{
    virtio_input_init,
    RT_NULL,
    RT_NULL,
    virtio_input_read,
    virtio_input_write,
    virtio_input_control
};
#endif

static void virtio_input_isr(int irqno, void *param)
{
    struct virtio_input_device *virtio_input_dev = (struct virtio_input_device *)param;
    struct virtio_device *virtio_dev = &virtio_input_dev->virtio_dev;
    struct virtq *event_queue = &virtio_dev->queues[VIRTIO_INPUT_QUEUE_EVENT];
    const char *dev_name = virtio_input_dev->parent.parent.name;

#ifdef RT_USING_SMP
    rt_base_t level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif

    virtio_interrupt_ack(virtio_dev);
    rt_hw_dsb();

    while (event_queue->used_idx != event_queue->used->idx)
    {
        rt_uint16_t id = event_queue->used->ring[event_queue->used_idx % event_queue->num].id;
        rt_uint32_t len = event_queue->used->ring[event_queue->used_idx % event_queue->num].len;

        if (len == sizeof(struct virtio_input_event))
        {
            struct virtio_input_event *recv_events = &virtio_input_dev->recv_events[id];
            struct virtio_input_event *bcst_events = &virtio_input_dev->bcst_events[id];

            if (recv_events->type >= EV_SYN && recv_events->type <= EV_ABS)
            {
                bcst_events->type = recv_events->type;
                bcst_events->code = recv_events->code;
                bcst_events->value = recv_events->value;

                if (virtio_input_dev->bsct_handler != RT_NULL)
                {
                    virtio_input_dev->bsct_handler(*bcst_events);
                }
            }
            else
            {
                rt_kprintf("%s: Unsupport event[type: %02x, code: %02x, value: %08x]!\n",
                        dev_name, recv_events->type, recv_events->code, recv_events->value);
            }
        }
        else
        {
            rt_kprintf("%s: Invalid event!\n", dev_name);
        }

        event_queue->used_idx++;

        virtio_submit_chain(virtio_dev, VIRTIO_INPUT_QUEUE_EVENT, id);

        virtio_queue_notify(virtio_dev, VIRTIO_INPUT_QUEUE_EVENT);
    }

#ifdef RT_USING_SMP
    rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif
}

rt_err_t rt_virtio_input_init(rt_ubase_t *mmio_base, rt_uint32_t irq)
{
    rt_uint32_t flag;
    static int dev_no = 0;
    char dev_name[RT_NAME_MAX];
    struct virtio_device *virtio_dev;
    struct virtio_input_device *virtio_input_dev;

    virtio_input_dev = rt_malloc(sizeof(struct virtio_input_device));

    if (virtio_input_dev == RT_NULL)
    {
        goto _alloc_fail;
    }

    virtio_dev = &virtio_input_dev->virtio_dev;
    virtio_dev->irq = irq;
    virtio_dev->mmio_base = mmio_base;

    virtio_input_dev->config = (struct virtio_input_config *)virtio_dev->mmio_config->config;
    virtio_input_dev->bsct_handler = RT_NULL;

#ifdef RT_USING_SMP
    rt_spin_lock_init(&virtio_dev->spinlock);
#endif

    virtio_reset_device(virtio_dev);
    virtio_status_acknowledge_driver(virtio_dev);

    virtio_dev->mmio_config->driver_features = virtio_dev->mmio_config->device_features & ~(
            (1 << VIRTIO_F_RING_EVENT_IDX) |
            (1 << VIRTIO_F_RING_INDIRECT_DESC));

    virtio_status_driver_ok(virtio_dev);

    if (virtio_queues_alloc(virtio_dev, 2) != RT_EOK)
    {
        goto _alloc_fail;
    }

    if (virtio_queue_init(virtio_dev, VIRTIO_INPUT_QUEUE_EVENT, VIRTIO_INPUT_EVENT_QUEUE_SIZE) != RT_EOK)
    {
        goto _alloc_fail;
    }

    if (virtio_queue_init(virtio_dev, VIRTIO_INPUT_QUEUE_STATUS, VIRTIO_INPUT_STATUS_QUEUE_SIZE) != RT_EOK)
    {
        virtio_queue_destroy(virtio_dev, VIRTIO_INPUT_QUEUE_EVENT);

        goto _alloc_fail;
    }

    virtio_input_cfg_select(virtio_input_dev, VIRTIO_INPUT_CFG_ID_DEVIDS, 0);

    if (virtio_input_dev->config->ids.product == EV_ABS)
    {
        virtio_input_dev->type = VIRTIO_INPUT_TYPE_TABLET;

        virtio_input_dev->parent.type = RT_Device_Class_Touch;

        flag = RT_DEVICE_FLAG_STANDALONE | RT_DEVICE_FLAG_INT_RX;
    }
    else
    {
        if (virtio_input_dev->config->ids.product == EV_KEY)
        {
            virtio_input_dev->type = VIRTIO_INPUT_TYPE_KEYBOARD;
        }
        else
        {
            virtio_input_dev->type = VIRTIO_INPUT_TYPE_MOUSE;
        }

        /* Replace it to "KeyBoard" or "Mouse" if support in the future */
        virtio_input_dev->parent.type = RT_Device_Class_Miscellaneous;

        flag = RT_DEVICE_FLAG_RDWR;
    }
#ifdef RT_USING_DEVICE_OPS
    virtio_input_dev->parent.ops = &virtio_input_ops;
#else
    virtio_input_dev->parent.init     = virtio_input_init;
    virtio_input_dev->parent.open     = RT_NULL;
    virtio_input_dev->parent.close    = RT_NULL;
    virtio_input_dev->parent.read     = virtio_input_read;
    virtio_input_dev->parent.write    = virtio_input_write;
    virtio_input_dev->parent.control  = virtio_input_control;
#endif

    rt_snprintf(dev_name, RT_NAME_MAX, "virtio-input%d", dev_no++);

    rt_mutex_init(&virtio_input_dev->rw_mutex, dev_name, RT_IPC_FLAG_PRIO);

    rt_hw_interrupt_install(irq, virtio_input_isr, virtio_input_dev, dev_name);
    rt_hw_interrupt_umask(irq);

    return rt_device_register((rt_device_t)virtio_input_dev, dev_name, flag);

_alloc_fail:

    if (virtio_input_dev != RT_NULL)
    {
        virtio_queues_free(virtio_dev);
        rt_free(virtio_input_dev);
    }
    return -RT_ENOMEM;
}
#endif /* RT_USING_VIRTIO_INPUT */
