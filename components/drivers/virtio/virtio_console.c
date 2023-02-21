/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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

#ifdef RT_USING_VIRTIO_CONSOLE

#include <virtio_console.h>

struct port_device
{
    struct rt_device parent;

    rt_list_t node;
    rt_uint32_t port_id;
    rt_bool_t rx_notify;
    rt_bool_t need_destroy;

    struct virtio_console_device *console;

    struct virtq *queue_rx, *queue_tx;
    rt_uint32_t queue_rx_index, queue_tx_index;

#ifdef RT_USING_SMP
    struct rt_spinlock spinlock_rx, spinlock_tx;
#endif

    struct rt_device_notify rx_notify_helper;

    struct
    {
        char rx_char, tx_char;
    } info[VIRTIO_CONSOLE_QUEUE_SIZE];
};

static void virtio_console_send_ctrl(struct virtio_console_device *virtio_console_dev,
        struct virtio_console_control *ctrl)
{
    rt_uint16_t id;
    struct virtio_device *virtio_dev = &virtio_console_dev->virtio_dev;
    struct virtq *queue_ctrl_tx;

#ifdef RT_USING_SMP
    rt_base_t level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif

    queue_ctrl_tx = &virtio_dev->queues[VIRTIO_CONSOLE_QUEUE_CTRL_TX];

    id = queue_ctrl_tx->avail->idx % queue_ctrl_tx->num;

    rt_memcpy(&virtio_console_dev->info[id].tx_ctrl, ctrl, sizeof(struct virtio_console_control));

    virtio_free_desc(virtio_dev, VIRTIO_CONSOLE_QUEUE_CTRL_TX, id);

    virtio_fill_desc(virtio_dev, VIRTIO_CONSOLE_QUEUE_CTRL_TX, id,
            virtio_console_dev->info[id].tx_ctrl_paddr, sizeof(struct virtio_console_control), 0, 0);

    virtio_submit_chain(virtio_dev, VIRTIO_CONSOLE_QUEUE_CTRL_TX, id);

    virtio_queue_notify(virtio_dev, VIRTIO_CONSOLE_QUEUE_CTRL_TX);

    virtio_alloc_desc(virtio_dev, VIRTIO_CONSOLE_QUEUE_CTRL_TX);

#ifdef RT_USING_SMP
    rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif
}

static rt_err_t virtio_console_port_init(rt_device_t dev);
static rt_err_t virtio_console_port_open(rt_device_t dev, rt_uint16_t oflag);
static rt_err_t virtio_console_port_close(rt_device_t dev);
static rt_ssize_t virtio_console_port_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
static rt_ssize_t virtio_console_port_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
static rt_err_t virtio_console_port_control(rt_device_t dev, int cmd, void *args);

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops virtio_console_port_ops =
{
    virtio_console_port_init,
    virtio_console_port_open,
    virtio_console_port_close,
    virtio_console_port_read,
    virtio_console_port_write,
    virtio_console_port_control
};
#endif

static rt_err_t virtio_console_port_create(struct virtio_console_device *virtio_console_dev)
{
    rt_uint32_t port_id;
    char dev_name[RT_NAME_MAX];
    struct port_device *port_dev, *prev_port_dev = RT_NULL;
    struct virtio_device *virtio_dev = &virtio_console_dev->virtio_dev;

    if (virtio_console_dev->port_nr > 0 && !virtio_has_feature(virtio_dev, VIRTIO_CONSOLE_F_MULTIPORT))
    {
        return -RT_ENOSYS;
    }

    if (virtio_console_dev->port_nr >= virtio_console_dev->max_port_nr)
    {
        return -RT_EFULL;
    }

    port_id = 0;

    /* The port device list is always ordered, so just find next number for id */
    rt_list_for_each_entry(port_dev, &virtio_console_dev->port_head, node)
    {
        if (port_dev->port_id != port_id)
        {
            break;
        }
        ++port_id;
        prev_port_dev = port_dev;
    }

    port_dev = rt_malloc(sizeof(struct port_device));

    if (port_dev == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    port_dev->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    port_dev->parent.ops  = &virtio_console_port_ops;
#else
    port_dev->parent.init     = virtio_console_port_init;
    port_dev->parent.open     = virtio_console_port_open;
    port_dev->parent.close    = virtio_console_port_close;
    port_dev->parent.read     = virtio_console_port_read;
    port_dev->parent.write    = virtio_console_port_write;
    port_dev->parent.control  = virtio_console_port_control;
#endif

    port_dev->parent.rx_indicate = RT_NULL;
    port_dev->parent.tx_complete = RT_NULL;

    rt_list_init(&port_dev->node);
    port_dev->port_id = port_id;
    port_dev->need_destroy = RT_FALSE;
    port_dev->rx_notify = RT_TRUE;
    port_dev->console = virtio_console_dev;
    port_dev->queue_rx_index = VIRTIO_CONSOLE_PORT_QUEUE_INDEX(port_dev->port_id, VIRTIO_CONSOLE_QUEUE_DATA_RX);
    port_dev->queue_tx_index = VIRTIO_CONSOLE_PORT_QUEUE_INDEX(port_dev->port_id, VIRTIO_CONSOLE_QUEUE_DATA_TX);
    port_dev->queue_rx = &virtio_dev->queues[port_dev->queue_rx_index];
    port_dev->queue_tx = &virtio_dev->queues[port_dev->queue_tx_index];

#ifdef RT_USING_SMP
    rt_spin_lock_init(&port_dev->spinlock_rx);
    rt_spin_lock_init(&port_dev->spinlock_tx);
#endif

    rt_snprintf(dev_name, RT_NAME_MAX, "vport%dp%d", virtio_console_dev->console_id, port_id);

    if (rt_device_register((rt_device_t)port_dev, dev_name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX) != RT_EOK)
    {
        rt_free(port_dev);

        return -RT_ERROR;
    }

    if (prev_port_dev != RT_NULL)
    {
        rt_list_insert_after(&prev_port_dev->node, &port_dev->node);
    }
    else
    {
        /* Port0 */
        rt_list_insert_after(&virtio_console_dev->port_head, &port_dev->node);
    }

    virtio_console_dev->port_nr++;

    return RT_EOK;
}

static void virtio_console_port_destroy(struct virtio_console_device *virtio_console_dev,
        struct port_device *port_dev)
{
    struct virtio_console_control set_ctrl;

    set_ctrl.id = port_dev->port_id;
    set_ctrl.event = VIRTIO_CONSOLE_PORT_OPEN;
    set_ctrl.value = 0;

    virtio_console_send_ctrl(virtio_console_dev, &set_ctrl);

    virtio_console_dev->port_nr--;

    rt_list_remove(&port_dev->node);

    rt_device_unregister((rt_device_t)port_dev);

    rt_free(port_dev);
}

static rt_err_t virtio_console_port_init(rt_device_t dev)
{
    rt_uint16_t id;
    rt_uint16_t idx[VIRTIO_CONSOLE_QUEUE_SIZE];
    rt_uint16_t rx_queue_index, tx_queue_index;
    struct port_device *port_dev = (struct port_device *)dev;
    struct virtio_console_device *virtio_console_dev = port_dev->console;
    struct virtio_device *virtio_dev = &virtio_console_dev->virtio_dev;
    struct virtq *queue_rx, *queue_tx;

    rx_queue_index = VIRTIO_CONSOLE_PORT_QUEUE_INDEX(port_dev->port_id, VIRTIO_CONSOLE_QUEUE_DATA_RX);
    tx_queue_index = VIRTIO_CONSOLE_PORT_QUEUE_INDEX(port_dev->port_id, VIRTIO_CONSOLE_QUEUE_DATA_TX);

    queue_rx = &virtio_dev->queues[rx_queue_index];
    queue_tx = &virtio_dev->queues[tx_queue_index];

    virtio_alloc_desc_chain(virtio_dev, rx_queue_index, queue_rx->num, idx);
    virtio_alloc_desc_chain(virtio_dev, tx_queue_index, queue_tx->num, idx);

    for (id = 0; id < queue_rx->num; ++id)
    {
        void *addr = &port_dev->info[id].rx_char;

        virtio_fill_desc(virtio_dev, rx_queue_index, id,
                VIRTIO_VA2PA(addr), sizeof(char), VIRTQ_DESC_F_WRITE, 0);

        queue_rx->avail->ring[id] = id;
    }
    rt_hw_dsb();

    queue_rx->avail->flags = 0;
    queue_rx->avail->idx = queue_rx->num;

    queue_rx->used_idx = queue_rx->used->idx;

    queue_tx->avail->flags = VIRTQ_AVAIL_F_NO_INTERRUPT;
    queue_tx->avail->idx = 0;

    virtio_queue_notify(virtio_dev, rx_queue_index);

    if (virtio_has_feature(virtio_dev, VIRTIO_CONSOLE_F_MULTIPORT))
    {
        struct virtio_console_control set_ctrl;

        set_ctrl.id = VIRTIO_CONSOLE_PORT_BAD_ID;
        set_ctrl.event = VIRTIO_CONSOLE_DEVICE_READY;
        set_ctrl.value = 1;

        virtio_console_send_ctrl(virtio_console_dev, &set_ctrl);
    }

    return RT_EOK;
}

static rt_err_t virtio_console_port_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct port_device *port_dev = (struct port_device *)dev;

    if (port_dev->port_id == 0 && virtio_has_feature(&port_dev->console->virtio_dev, VIRTIO_CONSOLE_F_MULTIPORT))
    {
        /* Port0 is reserve in multiport */
        return -RT_ERROR;
    }

    port_dev->rx_notify = RT_TRUE;

    return RT_EOK;
}

static rt_err_t virtio_console_port_close(rt_device_t dev)
{
    struct port_device *port_dev = (struct port_device *)dev;

    if (port_dev->need_destroy)
    {
        virtio_console_port_destroy(port_dev->console, port_dev);

        /*
         * We released the device memory in virtio_console_port_destroy,
         * rt_device_close has not finished yet, make the return value
         * to empty so that rt_device_close will not access the device memory.
         */
        return -RT_EEMPTY;
    }

    port_dev->rx_notify = RT_FALSE;

    return RT_EOK;
}

static rt_ssize_t virtio_console_port_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_off_t i = 0;
    rt_uint16_t id;
    rt_uint32_t len;
    struct port_device *port_dev = (struct port_device *)dev;
    struct virtio_device *virtio_dev = &port_dev->console->virtio_dev;
    rt_uint32_t queue_rx_index = port_dev->queue_rx_index;
    struct virtq *queue_rx = port_dev->queue_rx;

#ifdef RT_USING_SMP
    rt_base_t level = rt_spin_lock_irqsave(&port_dev->spinlock_rx);
#endif

    while (i < size)
    {
        if (queue_rx->used_idx == queue_rx->used->idx)
        {
            break;
        }
        rt_hw_dsb();

        id = queue_rx->used->ring[queue_rx->used_idx % queue_rx->num].id;
        len = queue_rx->used->ring[queue_rx->used_idx % queue_rx->num].len;

        if (len > sizeof(char))
        {
            rt_kprintf("%s: Receive buffer's size = %u is too big!\n", port_dev->parent.parent.name, len);
            len = sizeof(char);
        }

        *((char *)buffer + i) = port_dev->info[id].rx_char;

        queue_rx->used_idx++;

        virtio_submit_chain(virtio_dev, queue_rx_index, id);

        virtio_queue_notify(virtio_dev, queue_rx_index);

        i += len;
    }

#ifdef RT_USING_SMP
    rt_spin_unlock_irqrestore(&port_dev->spinlock_rx, level);
#endif

    size = i;

    return size;
}

static rt_ssize_t virtio_console_port_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    char ch = 0;
    rt_off_t i = 0;
    rt_uint16_t id;
    struct port_device *port_dev = (struct port_device *)dev;
    struct virtio_device *virtio_dev = &port_dev->console->virtio_dev;
    rt_uint32_t queue_tx_index = port_dev->queue_tx_index;
    struct virtq *queue_tx = port_dev->queue_tx;

#ifdef RT_USING_SMP
    rt_base_t level = rt_spin_lock_irqsave(&port_dev->spinlock_tx);
#endif

    while (i < size || ch == '\r')
    {
        id = queue_tx->avail->idx % queue_tx->num;

        /* Keep the way until 'new line' are unified */
        if (ch != '\r')
        {
            ch = *((const char *)buffer + i);
        }
        else
        {
            i -= sizeof(char);
        }

        port_dev->info[id].tx_char = ch;

        ch = (ch == '\n' ? '\r' : 0);

        virtio_free_desc(virtio_dev, queue_tx_index, id);

        virtio_fill_desc(virtio_dev, queue_tx_index, id,
                VIRTIO_VA2PA(&port_dev->info[id].tx_char), sizeof(char), 0, 0);

        virtio_submit_chain(virtio_dev, queue_tx_index, id);

        virtio_queue_notify(virtio_dev, queue_tx_index);

        virtio_alloc_desc(virtio_dev, queue_tx_index);

        i += sizeof(char);
    }

#ifdef RT_USING_SMP
    rt_spin_unlock_irqrestore(&port_dev->spinlock_tx, level);
#endif

    return size;
}

static rt_err_t virtio_console_port_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t status = RT_EOK;
    struct port_device *port_dev = (struct port_device *)dev;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_NOTIFY_SET:
        if (args == RT_NULL)
        {
            status = -RT_ERROR;
            break;
        }
        rt_memcpy(&port_dev->rx_notify_helper, args, sizeof(port_dev->rx_notify_helper));
        break;
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable RX */
        port_dev->rx_notify = RT_FALSE;
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* Enable RX */
        port_dev->rx_notify = RT_TRUE;
        break;
    case VIRTIO_DEVICE_CTRL_CONSOLE_PORT_DESTROY:
        {
            port_dev->need_destroy = RT_TRUE;
            port_dev->rx_notify = RT_FALSE;
        }
        break;
    default:
        status = -RT_EINVAL;
        break;
    }

    return status;
}

static rt_err_t virtio_console_init(rt_device_t dev)
{
    struct virtio_console_device *virtio_console_dev = (struct virtio_console_device *)dev;
    struct virtio_device *virtio_dev = &virtio_console_dev->virtio_dev;

    if (virtio_has_feature(virtio_dev, VIRTIO_CONSOLE_F_MULTIPORT))
    {
        rt_uint16_t id;
        rt_uint16_t idx[VIRTIO_CONSOLE_QUEUE_SIZE];
        struct virtq *queue_ctrl_rx, *queue_ctrl_tx;

        queue_ctrl_rx = &virtio_dev->queues[VIRTIO_CONSOLE_QUEUE_CTRL_RX];
        queue_ctrl_tx = &virtio_dev->queues[VIRTIO_CONSOLE_QUEUE_CTRL_TX];

        virtio_alloc_desc_chain(virtio_dev, VIRTIO_CONSOLE_QUEUE_CTRL_RX, queue_ctrl_rx->num, idx);
        virtio_alloc_desc_chain(virtio_dev, VIRTIO_CONSOLE_QUEUE_CTRL_TX, queue_ctrl_tx->num, idx);

        for (id = 0; id < queue_ctrl_rx->num; ++id)
        {
            void *addr = &virtio_console_dev->info[id].rx_ctrl;

            virtio_fill_desc(virtio_dev, VIRTIO_CONSOLE_QUEUE_CTRL_RX, id,
                    VIRTIO_VA2PA(addr), sizeof(struct virtio_console_control), VIRTQ_DESC_F_WRITE, 0);

            queue_ctrl_rx->avail->ring[id] = id;
        }
        rt_hw_dsb();

        for (id = 0; id < queue_ctrl_tx->num; ++id)
        {
            virtio_console_dev->info[id].tx_ctrl_paddr = VIRTIO_VA2PA(&virtio_console_dev->info[id].tx_ctrl);
        }

        queue_ctrl_rx->avail->flags = 0;
        queue_ctrl_rx->avail->idx = queue_ctrl_rx->num;

        queue_ctrl_rx->used_idx = queue_ctrl_rx->used->idx;

        queue_ctrl_tx->avail->flags = VIRTQ_AVAIL_F_NO_INTERRUPT;
        queue_ctrl_tx->avail->idx = 0;

        virtio_queue_notify(virtio_dev, VIRTIO_CONSOLE_QUEUE_CTRL_RX);
    }

    return virtio_console_port_create(virtio_console_dev);
}

static rt_err_t virtio_console_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t status = RT_EOK;
    struct virtio_console_device *virtio_console_dev = (struct virtio_console_device *)dev;

    switch (cmd)
    {
    case VIRTIO_DEVICE_CTRL_CONSOLE_PORT_CREATE:
        status = virtio_console_port_create(virtio_console_dev);
        break;
    default:
        status = -RT_EINVAL;
        break;
    }

    return status;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops virtio_console_ops =
{
    virtio_console_init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    virtio_console_control
};
#endif

static void virtio_console_isr(int irqno, void *param)
{
    rt_uint32_t id;
    rt_uint32_t len;
    struct port_device *port_dev;
    struct virtio_console_device *virtio_console_dev = (struct virtio_console_device *)param;
    struct virtio_device *virtio_dev = &virtio_console_dev->virtio_dev;
    const char *dev_name = virtio_console_dev->parent.parent.name;

#ifdef RT_USING_SMP
    rt_base_t level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif

    virtio_interrupt_ack(virtio_dev);
    rt_hw_dsb();

    do {
        struct virtq *queue_rx;
        struct virtio_console_control *ctrl, set_ctrl;

        if (!virtio_has_feature(virtio_dev, VIRTIO_CONSOLE_F_MULTIPORT))
        {
            break;
        }

        queue_rx = &virtio_dev->queues[VIRTIO_CONSOLE_QUEUE_CTRL_RX];

        if (queue_rx->used_idx == queue_rx->used->idx)
        {
            break;
        }
        rt_hw_dsb();

        id = queue_rx->used->ring[queue_rx->used_idx % queue_rx->num].id;
        len = queue_rx->used->ring[queue_rx->used_idx % queue_rx->num].len;

        queue_rx->used_idx++;

        if (len != sizeof(struct virtio_console_control))
        {
            rt_kprintf("%s: Invalid ctrl!\n", dev_name);
            break;
        }

        ctrl = &virtio_console_dev->info[id].rx_ctrl;

        switch (ctrl->event)
        {
        case VIRTIO_CONSOLE_PORT_ADD:
            {
                set_ctrl.id = ctrl->id;
                set_ctrl.event = VIRTIO_CONSOLE_PORT_READY;
                set_ctrl.value = 1;

            #ifdef RT_USING_SMP
                rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
            #endif

                virtio_console_send_ctrl(virtio_console_dev, &set_ctrl);

            #ifdef RT_USING_SMP
                level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
            #endif
            }
            break;
        case VIRTIO_CONSOLE_PORT_REMOVE:
            break;
        case VIRTIO_CONSOLE_RESIZE:
            break;
        case VIRTIO_CONSOLE_PORT_OPEN:
            {
                set_ctrl.id = ctrl->id;
                set_ctrl.event = VIRTIO_CONSOLE_PORT_OPEN;
                set_ctrl.value = 1;

            #ifdef RT_USING_SMP
                rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
            #endif

                virtio_console_send_ctrl(virtio_console_dev, &set_ctrl);

            #ifdef RT_USING_SMP
                level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
            #endif
            }
            break;
        case VIRTIO_CONSOLE_PORT_NAME:
            break;
        default:
            rt_kprintf("%s: Unsupport ctrl[id: %d, event: %d, value: %d]!\n",
                    dev_name, ctrl->id, ctrl->event, ctrl->value);
            break;
        }

    } while (0);

#ifdef RT_USING_SMP
    rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif

    rt_list_for_each_entry(port_dev, &virtio_console_dev->port_head, node)
    {
        rt_uint32_t queue_rx_index = port_dev->queue_rx_index;
        struct virtq *queue_rx = port_dev->queue_rx;

#ifdef RT_USING_SMP
        rt_base_t level = rt_spin_lock_irqsave(&port_dev->spinlock_rx);
#endif

        if (queue_rx->used_idx != queue_rx->used->idx)
        {
            rt_hw_dsb();

            id = queue_rx->used->ring[queue_rx->used_idx % queue_rx->num].id;
            len = queue_rx->used->ring[queue_rx->used_idx % queue_rx->num].len;

            if (port_dev->rx_notify)
            {
            #ifdef RT_USING_SMP
                rt_spin_unlock_irqrestore(&port_dev->spinlock_rx, level);
            #endif
                /* Will call virtio_console_port_read to inc used_idx */

                if (port_dev->parent.rx_indicate != RT_NULL)
                {
                    port_dev->parent.rx_indicate(&port_dev->parent, len);
                }

                if (port_dev->rx_notify_helper.notify != RT_NULL)
                {
                    port_dev->rx_notify_helper.notify(port_dev->rx_notify_helper.dev);
                }

            #ifdef RT_USING_SMP
                level = rt_spin_lock_irqsave(&port_dev->spinlock_rx);
            #endif
            }
            else
            {
                queue_rx->used_idx++;

                virtio_submit_chain(virtio_dev, queue_rx_index, id);

                virtio_queue_notify(virtio_dev, queue_rx_index);
            }
        }

#ifdef RT_USING_SMP
        rt_spin_unlock_irqrestore(&port_dev->spinlock_rx, level);
#endif
    }
}

rt_err_t rt_virtio_console_init(rt_ubase_t *mmio_base, rt_uint32_t irq)
{
    int i;
    rt_size_t queues_num;
    static int dev_no = 0;
    char dev_name[RT_NAME_MAX];
    struct virtio_device *virtio_dev;
    struct virtio_console_device *virtio_console_dev;

    RT_ASSERT(RT_USING_VIRTIO_CONSOLE_PORT_MAX_NR > 0);

    virtio_console_dev = rt_malloc(sizeof(struct virtio_console_device));

    if (virtio_console_dev == RT_NULL)
    {
        goto _alloc_fail;
    }

    virtio_dev = &virtio_console_dev->virtio_dev;
    virtio_dev->irq = irq;
    virtio_dev->mmio_base = mmio_base;

    virtio_console_dev->config = (struct virtio_console_config *)virtio_dev->mmio_config->config;

#ifdef RT_USING_SMP
    rt_spin_lock_init(&virtio_dev->spinlock);
#endif

    virtio_reset_device(virtio_dev);
    virtio_status_acknowledge_driver(virtio_dev);

    virtio_dev->mmio_config->driver_features = virtio_dev->mmio_config->device_features & ~(
            (1 << VIRTIO_F_RING_EVENT_IDX) |
            (1 << VIRTIO_F_RING_INDIRECT_DESC));

    virtio_status_driver_ok(virtio_dev);

    if (!virtio_has_feature(virtio_dev, VIRTIO_CONSOLE_F_MULTIPORT))
    {
        virtio_console_dev->max_port_nr = 1;
        queues_num = 2;
    }
    else
    {
        if (virtio_console_dev->config->max_nr_ports > RT_USING_VIRTIO_CONSOLE_PORT_MAX_NR)
        {
            virtio_console_dev->max_port_nr = RT_USING_VIRTIO_CONSOLE_PORT_MAX_NR;
            virtio_console_dev->config->max_nr_ports = virtio_console_dev->max_port_nr;
        }
        else
        {
            virtio_console_dev->max_port_nr = virtio_console_dev->config->max_nr_ports;
        }

        queues_num = VIRTIO_CONSOLE_PORT_QUEUE_INDEX(virtio_console_dev->max_port_nr, VIRTIO_CONSOLE_QUEUE_DATA_RX);
    }

    if (virtio_queues_alloc(virtio_dev, queues_num) != RT_EOK)
    {
        goto _alloc_fail;
    }

    for (i = 0; i < virtio_dev->queues_num; ++i)
    {
        if (virtio_queue_init(virtio_dev, i, VIRTIO_CONSOLE_QUEUE_SIZE) != RT_EOK)
        {
            for (; i >= 0; --i)
            {
                virtio_queue_destroy(virtio_dev, i);
            }
            goto _alloc_fail;
        }
    }

    virtio_console_dev->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    virtio_console_dev->parent.ops  = &virtio_console_ops;
#else
    virtio_console_dev->parent.init     = virtio_console_init;
    virtio_console_dev->parent.open     = RT_NULL;
    virtio_console_dev->parent.close    = RT_NULL;
    virtio_console_dev->parent.read     = RT_NULL;
    virtio_console_dev->parent.write    = RT_NULL;
    virtio_console_dev->parent.control  = virtio_console_control;
#endif

    virtio_console_dev->parent.rx_indicate = RT_NULL;
    virtio_console_dev->parent.tx_complete = RT_NULL;

    virtio_console_dev->console_id = dev_no;
    virtio_console_dev->port_nr = 0;
    rt_list_init(&virtio_console_dev->port_head);

    rt_snprintf(dev_name, RT_NAME_MAX, "virtio-console%d", dev_no++);

    rt_hw_interrupt_install(irq, virtio_console_isr, virtio_console_dev, dev_name);
    rt_hw_interrupt_umask(irq);

    return rt_device_register((rt_device_t)virtio_console_dev, dev_name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);

_alloc_fail:

    if (virtio_console_dev != RT_NULL)
    {
        virtio_queues_free(virtio_dev);
        rt_free(virtio_console_dev);
    }
    return -RT_ENOMEM;
}
#endif /* RT_USING_VIRTIO_CONSOLE */
