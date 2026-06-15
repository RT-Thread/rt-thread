/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 * 2023-02-25     GuEe-GUI     using virtio dm
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "virtio.dev.console"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>

#include "virtio_internal.h"
#include "virtio_config/virtio-console.h"

#define QUEUE_PORT_RX   0
#define QUEUE_PORT_TX   1
#define QUEUE_CTRL_RX   2
#define QUEUE_CTRL_TX   3

struct virtio_console;

struct console_port
{
    struct rt_serial_device parent;
    char name[64];

    char *stream;
    char *rx_stream;
    char *tx_stream;
    rt_bool_t irq_enabled;
    rt_bool_t host_connected;
    struct rt_spinlock lock;
    struct virtio_console *vconsole;

    struct rt_virtqueue *rx_vq;
    struct rt_virtqueue *tx_vq;
};

#define raw_to_console_port(raw) rt_container_of(raw, struct console_port, parent)

struct virtio_console
{
    struct rt_virtio_device *vdev;

    rt_uint32_t uid;
    rt_size_t stream_rx_size;
    rt_size_t stream_tx_size;

    struct rt_spinlock lock;
    struct rt_virtqueue *ctrl_rx_vq;
    struct rt_virtqueue *ctrl_tx_vq;

    rt_size_t ctrl_packet_size;
    struct virtio_console_control_ext *ctrl_packet;

    struct rt_work ctrl_work;
    struct rt_work config_work;

    rt_size_t max_port_nr;
    struct rt_virtqueue **vqs;
    struct console_port *ports;
};

static struct rt_dm_ida virtio_console_ida = RT_DM_IDA_INIT(CUSTOM);

rt_inline rt_bool_t console_multiport(struct virtio_console *vconsole)
{
    return rt_virtio_has_feature(vconsole->vdev, VIRTIO_CONSOLE_F_MULTIPORT);
}

static rt_ssize_t console_send_ctrl_msg(struct virtio_console *vconsole,
        rt_uint32_t port_id, rt_uint16_t event, rt_uint16_t value)
{
    struct rt_virtqueue *vq;
    struct virtio_console_control ctrl_packet;

    if (!vconsole || vconsole->max_port_nr <= 1)
    {
        return RT_EOK;
    }

    vq = vconsole->ctrl_tx_vq;
    rt_spin_lock(&vconsole->lock);

    ctrl_packet.id = cpu_to_virtio32(vconsole->vdev, port_id);
    ctrl_packet.event = cpu_to_virtio16(vconsole->vdev, event);
    ctrl_packet.value = cpu_to_virtio16(vconsole->vdev, value);

    rt_virtqueue_add_outbuf(vq, &ctrl_packet, sizeof(ctrl_packet));
    rt_virtqueue_kick(vq);

    while (!rt_virtqueue_read_buf(vq, RT_NULL))
    {
        rt_hw_cpu_relax();
    }

    rt_spin_unlock(&vconsole->lock);

    return RT_EOK;
}

static void console_emergency_write(struct virtio_console *vconsole,
        rt_uint32_t emerg_wr)
{
    rt_virtio_write_config(vconsole->vdev, struct virtio_console_config,
            emerg_wr, emerg_wr);
}

static rt_err_t console_port_configure(struct rt_serial_device *serial,
        struct serial_configure *cfg)
{
    return RT_EOK;
}

static rt_err_t console_port_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct console_port *port = raw_to_console_port(serial);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        port->irq_enabled = RT_FALSE;
        break;

    case RT_DEVICE_CTRL_SET_INT:
        port->irq_enabled = RT_TRUE;
        break;
    }

    return RT_EOK;
}

static int console_port_putc(struct rt_serial_device *serial, char c)
{
    rt_base_t level;
    char *tx_stream;
    struct rt_virtqueue *vq;
    struct console_port *port = raw_to_console_port(serial);

    if (!port->host_connected)
    {
        if (rt_virtio_has_feature(port->vconsole->vdev, VIRTIO_CONSOLE_F_EMERG_WRITE))
        {
            console_emergency_write(port->vconsole, c);

            if (port->parent.parent.open_flag & RT_DEVICE_FLAG_INT_TX)
            {
                rt_hw_serial_isr(&port->parent, RT_SERIAL_EVENT_TX_DONE);
            }
        }

        return 1;
    }

    vq = port->tx_vq;
    rt_virtqueue_wait_prepare(vq, 1);

    level = rt_spin_lock_irqsave(&port->lock);

    tx_stream = &port->tx_stream[rt_virtqueue_next_buf_index(vq)];
    *tx_stream = c;
    rt_virtqueue_add_outbuf(vq, tx_stream, sizeof(*tx_stream));
    rt_virtqueue_kick(vq);

    if (port->parent.parent.open_flag & ~RT_DEVICE_FLAG_INT_TX)
    {
        while (!rt_virtqueue_read_buf(vq, RT_NULL))
        {
            rt_hw_cpu_relax();
        }
    }

    rt_spin_unlock_irqrestore(&port->lock, level);

    return 1;
}

static int console_port_getc(struct rt_serial_device *serial)
{
    rt_base_t level;
    int ch = -1;
    char *rx_stream;
    struct rt_virtqueue *vq;
    struct console_port *port = raw_to_console_port(serial);

    level = rt_spin_lock_irqsave(&port->lock);

    vq = port->rx_vq;
    if ((rx_stream = rt_virtqueue_read_buf(vq, RT_NULL)))
    {
        ch = *rx_stream;

        rt_virtqueue_add_inbuf(vq, rx_stream, sizeof(char));

        rt_virtqueue_kick(vq);
    }

    rt_spin_unlock_irqrestore(&port->lock, level);

    return ch;
}

static const struct rt_uart_ops console_port_ops =
{
    .configure = console_port_configure,
    .control = console_port_control,
    .putc = console_port_putc,
    .getc = console_port_getc,
};

static rt_err_t console_port_add(struct virtio_console *vconsole,
        struct console_port *port)
{
    char *stream;
    const char *name;
    rt_uint32_t id = port - vconsole->ports;

    rt_memset(port, 0, sizeof(*port));

    if (!(stream = rt_malloc(sizeof(char) * (vconsole->stream_rx_size + vconsole->stream_tx_size))))
    {
        return -RT_ENOMEM;
    }

    port->stream = stream;
    port->tx_stream = stream;
    port->rx_stream = stream + vconsole->stream_tx_size;
    port->vconsole = vconsole;
    rt_spin_lock_init(&port->lock);

    if (!port->rx_vq || !port->tx_vq)
    {
        if (id != 0)
        {
            port->rx_vq = vconsole->vqs[4 + (id - 1) * 2 + QUEUE_PORT_RX];
            port->tx_vq = vconsole->vqs[4 + (id - 1) * 2 + QUEUE_PORT_TX];
        }
        else
        {
            port->rx_vq = vconsole->vqs[QUEUE_PORT_RX];
            port->tx_vq = vconsole->vqs[QUEUE_PORT_TX];
        }

        for (int idx = 0; idx < vconsole->stream_rx_size; ++idx)
        {
            rt_virtqueue_add_inbuf(port->rx_vq, &port->rx_stream[idx], sizeof(char));

            rt_virtqueue_submit(port->rx_vq);
        }

        rt_virtqueue_notify(port->rx_vq);
    }

    console_send_ctrl_msg(vconsole, VIRTIO_CONSOLE_BAD_ID,
            VIRTIO_CONSOLE_DEVICE_READY, 1);

    if (!console_multiport(port->vconsole))
    {
        port->host_connected = RT_TRUE;
    }

    port->parent.ops = &console_port_ops;
    port->parent.config = (struct serial_configure)RT_SERIAL_CONFIG_DEFAULT;
    rt_dm_dev_set_name(&port->parent.parent, "vport%up%u", vconsole->uid, id);
    name = rt_dm_dev_get_name(&port->parent.parent);

    return rt_hw_serial_register(&port->parent, name,
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE |
            RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX, vconsole);
}

static void console_port_remove(struct console_port *port, rt_bool_t sync)
{
    rt_uint32_t port_id;

    if (!port->vconsole)
    {
        return;
    }

    /* Make sure pending buffer is empty */
    while (rt_virtqueue_read_buf(port->tx_vq, RT_NULL) ||
        rt_virtqueue_read_buf(port->rx_vq, RT_NULL))
    {
        rt_thread_yield();
    }

    port_id = port - port->vconsole->ports;

    if (sync && port_id != 0)
    {
        console_send_ctrl_msg(port->vconsole, port_id, VIRTIO_CONSOLE_PORT_OPEN, 0);
    }

    rt_device_unregister(&port->parent.parent);

    rt_free(port->stream);
    port->vconsole = RT_NULL;
}

static struct console_port *console_find_port_by_vq(struct virtio_console *vconsole,
        struct rt_virtqueue *vq)
{
    for (int i = 0; i < vconsole->max_port_nr; ++i)
    {
        struct console_port *port = &vconsole->ports[i];

        if (port->tx_vq == vq || port->rx_vq == vq)
        {
            return port;
        }
    }

    return RT_NULL;
}

static struct console_port *console_find_port_by_id(struct virtio_console *vconsole,
        rt_uint32_t id)
{
    return id < vconsole->max_port_nr ? &vconsole->ports[id] : RT_NULL;
}

static void console_resize(struct virtio_console *vconsole,
        rt_uint16_t cols, rt_uint16_t rows)
{
    LOG_D("%s: [cols, rows] resize [%u, %u]",
            rt_dm_dev_get_name(&vconsole->vdev.parent), cols, rows);

    /* Port to TTY */
}

static void console_ctrl_work(struct rt_work *work, void *work_data)
{
    rt_uint32_t port_id;
    struct console_port *port;
    struct virtio_console_control *ctrl_packet;
    struct virtio_console_control_ext *ctrl_packet_ext;
    struct virtio_console *vconsole = work_data;
    struct rt_virtio_device *vdev = vconsole->vdev;

_next_ctrl:
    if (!(ctrl_packet_ext = rt_virtqueue_read_buf(vconsole->ctrl_rx_vq, RT_NULL)))
    {
        return;
    }

    ctrl_packet = &ctrl_packet_ext->ctrl;
    port = console_find_port_by_id(vconsole, virtio32_to_cpu(vdev, ctrl_packet->id));
    port_id = virtio32_to_cpu(vdev, ctrl_packet->id);

    if (!port->vconsole &&
        cpu_to_virtio16(vdev, ctrl_packet->event) != VIRTIO_CONSOLE_PORT_ADD)
    {
        LOG_D("%s: Port%d in control is invalid", rt_dm_dev_get_name(&vdev->parent),
                port_id);

        goto _prepare_next_ctrl;
    }

    switch (virtio16_to_cpu(vdev, ctrl_packet->event))
    {
    case VIRTIO_CONSOLE_PORT_ADD:
        if (port->vconsole)
        {
            LOG_D("%s: Port%u already added", rt_dm_dev_get_name(&vdev->parent),
                    port_id);

            console_send_ctrl_msg(vconsole, port_id, VIRTIO_CONSOLE_PORT_READY, 1);
            break;
        }
        if (port_id >= vconsole->max_port_nr)
        {
            LOG_W("%s: Port%u is out of %u max supported",
                    rt_dm_dev_get_name(&vdev->parent), port_id, vconsole->max_port_nr);
            break;
        }
        console_port_add(vconsole, port);
        break;

    case VIRTIO_CONSOLE_PORT_REMOVE:
        console_port_remove(port, RT_FALSE);
        break;

    case VIRTIO_CONSOLE_CONSOLE_PORT:
        console_send_ctrl_msg(vconsole, port_id, VIRTIO_CONSOLE_PORT_OPEN, 1);
        break;

    case VIRTIO_CONSOLE_RESIZE:
        console_resize(vconsole,
                virtio16_to_cpu(vdev, ctrl_packet_ext->resize.cols),
                virtio16_to_cpu(vdev, ctrl_packet_ext->resize.rows));
        break;

    case VIRTIO_CONSOLE_PORT_OPEN:
        port->host_connected = !!virtio16_to_cpu(vdev, ctrl_packet->value);
        console_send_ctrl_msg(vconsole, port_id, VIRTIO_CONSOLE_PORT_OPEN, 1);
        break;

    case VIRTIO_CONSOLE_PORT_NAME:
        rt_strncpy(port->name, (const char *)ctrl_packet_ext->data, sizeof(port->name));
        break;

    default:
        break;
    }

_prepare_next_ctrl:
    rt_virtqueue_add_inbuf(vconsole->ctrl_rx_vq,
            ctrl_packet_ext, sizeof(*ctrl_packet_ext));

    rt_virtqueue_kick(vconsole->ctrl_rx_vq);

    goto _next_ctrl;
}

static void console_config_work(struct rt_work *work, void *work_data)
{
    rt_uint16_t cols, rows;
    struct virtio_console *vconsole = work_data;
    struct rt_virtio_device *vdev = vconsole->vdev;

    rt_virtio_read_config(vdev, struct virtio_console_config, cols, &cols);
    rt_virtio_read_config(vdev, struct virtio_console_config, rows, &rows);

    console_resize(vconsole, cols, rows);
}

static void virtio_console_rx_done(struct rt_virtqueue *vq)
{
    struct virtio_console *vconsole = vq->vdev->priv;
    struct console_port *port = console_find_port_by_vq(vconsole, vq);

    if (!port)
    {
        return;
    }

    if (port->irq_enabled)
    {
        rt_hw_serial_isr(&port->parent, RT_SERIAL_EVENT_RX_IND);
    }
    else
    {
        /* Give up */
        console_port_getc(&port->parent);
    }
}

static void virtio_console_tx_done(struct rt_virtqueue *vq)
{
    struct virtio_console *vconsole = vq->vdev->priv;
    struct console_port *port = console_find_port_by_vq(vconsole, vq);

    if (!port)
    {
        return;
    }

    if (port->parent.parent.open_flag & RT_DEVICE_FLAG_INT_TX)
    {
        if (rt_virtqueue_read_buf(vq, RT_NULL))
        {
            rt_hw_serial_isr(&port->parent, RT_SERIAL_EVENT_TX_DONE);
        }
    }
}

static void virtio_console_ctrl_done(struct rt_virtqueue *vq)
{
    struct virtio_console *vconsole = vq->vdev->priv;

    rt_work_submit(&vconsole->ctrl_work, 0);
}

static void virtio_console_config_changed(struct rt_virtio_device *vdev)
{
    struct virtio_console *vconsole = vdev->priv;

    if (!console_multiport(vconsole))
    {
        rt_work_submit(&vconsole->config_work, 0);
    }
}

static rt_err_t virtio_console_vq_init(struct virtio_console *vconsole)
{
    rt_err_t err;
    const char **names;
    rt_size_t vqs_nr = 2;
    rt_virtqueue_callback *cbs;

    if (vconsole->max_port_nr > 1)
    {
        vqs_nr = 2 * vconsole->max_port_nr + 2;
    }

    vconsole->vqs = rt_calloc(vqs_nr, sizeof(*vconsole->vqs));

    if (!vconsole->vqs)
    {
        return -RT_ENOMEM;
    }

    if (!(names = rt_malloc(sizeof(*names) * vqs_nr)))
    {
        return -RT_ENOMEM;
    }

    if (!(cbs = rt_malloc(sizeof(*cbs) * vqs_nr)))
    {
        rt_free(names);

        return -RT_ENOMEM;
    }

    names[QUEUE_PORT_RX] = "ch-rx";
    names[QUEUE_PORT_TX] = "ch-tx";
    cbs[QUEUE_PORT_RX] = &virtio_console_rx_done;
    cbs[QUEUE_PORT_TX] = &virtio_console_tx_done;

    if (vqs_nr > 2)
    {
        names[QUEUE_CTRL_RX] = "ctl-rx";
        names[QUEUE_CTRL_TX] = "ctl-tx";
        cbs[QUEUE_CTRL_RX] = &virtio_console_ctrl_done;
        cbs[QUEUE_CTRL_TX] = RT_NULL;
    }

    for (int i = 4; i < vqs_nr; i += 2)
    {
        names[i + QUEUE_PORT_RX] = "ch-rx";
        names[i + QUEUE_PORT_TX] = "ch-tx";
        cbs[i + QUEUE_PORT_RX] = &virtio_console_rx_done;
        cbs[i + QUEUE_PORT_TX] = &virtio_console_tx_done;
    }

    if ((err = rt_virtio_virtqueue_install(vconsole->vdev, vqs_nr,
            vconsole->vqs, names, cbs)))
    {
        goto _out_free;
    }

    vconsole->stream_rx_size = rt_virtqueue_get_virtq_size(vconsole->vqs[QUEUE_PORT_RX]);
    vconsole->stream_tx_size = rt_virtqueue_get_virtq_size(vconsole->vqs[QUEUE_PORT_TX]);

    if (vqs_nr > 2)
    {
        struct rt_virtqueue *ctrl_rx_vq, *ctrl_tx_vq;

        ctrl_rx_vq = vconsole->vqs[QUEUE_CTRL_RX];
        ctrl_tx_vq = vconsole->vqs[QUEUE_CTRL_TX];

        vconsole->ctrl_packet_size = rt_virtqueue_get_virtq_size(ctrl_rx_vq);
        vconsole->ctrl_packet = rt_malloc(sizeof(*vconsole->ctrl_packet) *
                vconsole->ctrl_packet_size);

        if (!vconsole->ctrl_packet)
        {
            goto _out_free;
        }

        for (int idx = 0; idx < vconsole->ctrl_packet_size; ++idx)
        {
            rt_virtqueue_add_inbuf(ctrl_rx_vq, &vconsole->ctrl_packet[idx],
                    sizeof(vconsole->ctrl_packet[idx]));

            rt_virtqueue_submit(ctrl_rx_vq);
        }

        rt_virtqueue_notify(ctrl_rx_vq);

        vconsole->ctrl_rx_vq = ctrl_rx_vq;
        vconsole->ctrl_tx_vq = ctrl_tx_vq;

        rt_virtqueue_disable_callback(ctrl_tx_vq);
    }

_out_free:
    rt_free(names);
    rt_free(cbs);

    return err;
}

static void virtio_console_vq_finit(struct virtio_console *vconsole)
{
    if (vconsole->ports)
    {
        rt_free(vconsole->ports);
    }

    if (vconsole->vqs)
    {
        if (vconsole->vqs[0])
        {
            rt_virtio_virtqueue_release(vconsole->vdev);
        }

        rt_free(vconsole->vqs);
    }

    if (vconsole->ctrl_packet)
    {
        rt_free(vconsole->ctrl_packet);
    }
}

static rt_err_t virtio_console_probe(struct rt_virtio_device *vdev)
{
    rt_err_t err;
    struct virtio_console *vconsole = rt_calloc(1, sizeof(*vconsole));

    if (!vconsole)
    {
        return -RT_ENOMEM;
    }

    vdev->priv = vconsole;
    vconsole->vdev = vdev;
    vdev->parent.user_data = vconsole;

    rt_virtio_read_config(vdev, struct virtio_console_config,
            max_nr_ports, &vconsole->max_port_nr);
    vconsole->max_port_nr = rt_max_t(rt_size_t, 1, vconsole->max_port_nr);

    vconsole->ports = rt_malloc(sizeof(*vconsole->ports) * vconsole->max_port_nr);

    if (!vconsole->ports)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    if ((err = virtio_console_vq_init(vconsole)))
    {
        goto _fail;
    }

    if ((vconsole->uid = rt_dm_ida_alloc(&virtio_console_ida)) < 0)
    {
        return -RT_EFULL;
    }

    if (vconsole->ctrl_rx_vq && vconsole->ctrl_tx_vq)
    {
        rt_work_init(&vconsole->ctrl_work, console_ctrl_work, vconsole);
    }

    rt_work_init(&vconsole->config_work, console_config_work, vconsole);

    for (int i = 0; i < vconsole->max_port_nr; ++i)
    {
        vconsole->ports[i].vconsole = RT_NULL;
    }

    if ((err = console_port_add(vconsole, &vconsole->ports[0])))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_dm_ida_free(&virtio_console_ida, vconsole->uid);
    virtio_console_vq_finit(vconsole);
    rt_free(vconsole);

    return err;
}

static rt_err_t virtio_console_remove(struct rt_virtio_device *vdev)
{
    struct virtio_console *vconsole = vdev->parent.user_data;

    for (int i = 0; i < vconsole->max_port_nr; ++i)
    {
        console_port_remove(&vconsole->ports[i], RT_TRUE);
    }

    rt_dm_ida_free(&virtio_console_ida, vconsole->uid);

    virtio_console_vq_finit(vconsole);
    rt_free(vconsole);

    return RT_EOK;
}

static const struct rt_virtio_device_id virtio_console_ids[] =
{
    { VIRTIO_DEVICE_ID_CONSOLE, VIRTIO_DEVICE_ANY_ID },
    { /* sentinel */ }
};

static struct rt_virtio_driver virtio_console_driver =
{
    .ids = virtio_console_ids,
    .features =
        RT_BIT(VIRTIO_CONSOLE_F_SIZE)
      | RT_BIT(VIRTIO_CONSOLE_F_MULTIPORT)
      | RT_BIT(VIRTIO_CONSOLE_F_EMERG_WRITE),

    .probe = virtio_console_probe,
    .remove = virtio_console_remove,
    .config_changed = virtio_console_config_changed,
};
RT_VIRTIO_DRIVER_EXPORT(virtio_console_driver);

static const struct rt_virtio_device_id virtio_rproc_serial_ids[] =
{
#ifdef RT_VIRTIO_RPROC_SERIAL
    { VIRTIO_DEVICE_ID_RPROC_SERIAL, VIRTIO_DEVICE_ANY_ID },
#endif
    { /* sentinel */ }
};

static struct rt_virtio_driver virtio_rproc_serial_driver =
{
    .ids = virtio_rproc_serial_ids,
    .probe = virtio_console_probe,
    .remove = virtio_console_remove,
};
RT_VIRTIO_DRIVER_EXPORT(virtio_rproc_serial_driver);
