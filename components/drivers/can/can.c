/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2015-05-14     aubrcool@qq.com   first version
 * 2015-07-06     Bernard           code cleanup and remove RT_CAN_USING_LED;
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define CAN_LOCK(can)   rt_mutex_take(&(can->lock), RT_WAITING_FOREVER)
#define CAN_UNLOCK(can) rt_mutex_release(&(can->lock))

static rt_err_t rt_can_init(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    struct rt_can_device *can;

    RT_ASSERT(dev != RT_NULL);
    can = (struct rt_can_device *)dev;

    /* initialize rx/tx */
    can->can_rx = RT_NULL;
    can->can_tx = RT_NULL;
#ifdef RT_CAN_USING_HDR
    can->hdr = RT_NULL;
#endif

    /* apply configuration */
    if (can->ops->configure)
        result = can->ops->configure(can, &can->config);
    else
        result = -RT_ENOSYS;

    return result;
}

/*
 * can interrupt routines
 */
rt_inline int _can_int_rx(struct rt_can_device *can, struct rt_can_msg *data, int msgs)
{
    int size;
    struct rt_can_rx_fifo *rx_fifo;
    RT_ASSERT(can != RT_NULL);
    size = msgs;

    rx_fifo = (struct rt_can_rx_fifo *) can->can_rx;
    RT_ASSERT(rx_fifo != RT_NULL);

    /* read from software FIFO */
    while (msgs)
    {
        rt_base_t level;
#ifdef RT_CAN_USING_HDR
        rt_int8_t hdr;
#endif /*RT_CAN_USING_HDR*/
        struct rt_can_msg_list *listmsg = RT_NULL;

        /* disable interrupt */
        level = rt_hw_interrupt_disable();
#ifdef RT_CAN_USING_HDR
        hdr = data->hdr_index;

        if (hdr >= 0 && can->hdr && hdr < can->config.maxhdr && !rt_list_isempty(&can->hdr[hdr].list))
        {
            listmsg = rt_list_entry(can->hdr[hdr].list.next, struct rt_can_msg_list, hdrlist);
            rt_list_remove(&listmsg->list);
            rt_list_remove(&listmsg->hdrlist);
            if (can->hdr[hdr].msgs)
            {
                can->hdr[hdr].msgs--;
            }
            listmsg->owner = RT_NULL;
        }
        else if (hdr == -1)
#endif /*RT_CAN_USING_HDR*/
        {
            if (!rt_list_isempty(&rx_fifo->uselist))
            {
                listmsg = rt_list_entry(rx_fifo->uselist.next, struct rt_can_msg_list, list);
                rt_list_remove(&listmsg->list);
#ifdef RT_CAN_USING_HDR
                rt_list_remove(&listmsg->hdrlist);
                if (listmsg->owner != RT_NULL && listmsg->owner->msgs)
                {
                    listmsg->owner->msgs--;
                }
                listmsg->owner = RT_NULL;
#endif /*RT_CAN_USING_HDR*/
            }
            else
            {
                /* no data, enable interrupt and break out */
                rt_hw_interrupt_enable(level);
                break;
            }
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);
        if (listmsg != RT_NULL)
        {
            rt_memcpy(data, &listmsg->data, sizeof(struct rt_can_msg));

            level = rt_hw_interrupt_disable();
            rt_list_insert_before(&rx_fifo->freelist, &listmsg->list);
            rx_fifo->freenumbers++;
            RT_ASSERT(rx_fifo->freenumbers <= can->config.msgboxsz);
            rt_hw_interrupt_enable(level);

            listmsg = RT_NULL;
        }
        else
        {
            break;
        }
        data ++;
        msgs -= sizeof(struct rt_can_msg);
    }

    return (size - msgs);
}

rt_inline int _can_int_tx(struct rt_can_device *can, const struct rt_can_msg *data, int msgs)
{
    int size;
    struct rt_can_tx_fifo *tx_fifo;

    RT_ASSERT(can != RT_NULL);

    size = msgs;
    tx_fifo = (struct rt_can_tx_fifo *) can->can_tx;
    RT_ASSERT(tx_fifo != RT_NULL);

    while (msgs)
    {
        rt_base_t level;
        rt_uint32_t no;
        rt_uint32_t result;
        struct rt_can_sndbxinx_list *tx_tosnd = RT_NULL;

        rt_sem_take(&(tx_fifo->sem), RT_WAITING_FOREVER);
        level = rt_hw_interrupt_disable();
        tx_tosnd = rt_list_entry(tx_fifo->freelist.next, struct rt_can_sndbxinx_list, list);
        RT_ASSERT(tx_tosnd != RT_NULL);
        rt_list_remove(&tx_tosnd->list);
        rt_hw_interrupt_enable(level);

        no = ((rt_ubase_t)tx_tosnd - (rt_ubase_t)tx_fifo->buffer) / sizeof(struct rt_can_sndbxinx_list);
        tx_tosnd->result = RT_CAN_SND_RESULT_WAIT;
        rt_completion_init(&tx_tosnd->completion);
        if (can->ops->sendmsg(can, data, no) != RT_EOK)
        {
            /* send failed. */
            level = rt_hw_interrupt_disable();
            rt_list_insert_before(&tx_fifo->freelist, &tx_tosnd->list);
            rt_hw_interrupt_enable(level);
            rt_sem_release(&(tx_fifo->sem));
            goto err_ret;
        }

        can->status.sndchange = 1;
        rt_completion_wait(&(tx_tosnd->completion), RT_WAITING_FOREVER);

        level = rt_hw_interrupt_disable();
        result = tx_tosnd->result;
        if (!rt_list_isempty(&tx_tosnd->list))
        {
            rt_list_remove(&tx_tosnd->list);
        }
        rt_list_insert_before(&tx_fifo->freelist, &tx_tosnd->list);
        rt_hw_interrupt_enable(level);
        rt_sem_release(&(tx_fifo->sem));

        if (result == RT_CAN_SND_RESULT_OK)
        {
            level = rt_hw_interrupt_disable();
            can->status.sndpkg++;
            rt_hw_interrupt_enable(level);

            data ++;
            msgs -= sizeof(struct rt_can_msg);
            if (!msgs) break;
        }
        else
        {
err_ret:
            level = rt_hw_interrupt_disable();
            can->status.dropedsndpkg++;
            rt_hw_interrupt_enable(level);
            break;
        }
    }

    return (size - msgs);
}

rt_inline int _can_int_tx_priv(struct rt_can_device *can, const struct rt_can_msg *data, int msgs)
{
    int size;
    rt_base_t level;
    rt_uint32_t no, result;
    struct rt_can_tx_fifo *tx_fifo;

    RT_ASSERT(can != RT_NULL);

    size = msgs;
    tx_fifo = (struct rt_can_tx_fifo *) can->can_tx;
    RT_ASSERT(tx_fifo != RT_NULL);

    while (msgs)
    {
        no = data->priv;
        if (no >= can->config.sndboxnumber)
        {
            break;
        }

        level = rt_hw_interrupt_disable();
        if ((tx_fifo->buffer[no].result != RT_CAN_SND_RESULT_OK))
        {
            rt_hw_interrupt_enable(level);

            rt_completion_wait(&(tx_fifo->buffer[no].completion), RT_WAITING_FOREVER);
            continue;
        }
        tx_fifo->buffer[no].result = RT_CAN_SND_RESULT_WAIT;
        rt_hw_interrupt_enable(level);

        if (can->ops->sendmsg(can, data, no) != RT_EOK)
        {
            continue;
        }
        can->status.sndchange = 1;
        rt_completion_wait(&(tx_fifo->buffer[no].completion), RT_WAITING_FOREVER);

        result = tx_fifo->buffer[no].result;
        if (result == RT_CAN_SND_RESULT_OK)
        {
            level = rt_hw_interrupt_disable();
            can->status.sndpkg++;
            rt_hw_interrupt_enable(level);
            data ++;
            msgs -= sizeof(struct rt_can_msg);
            if (!msgs) break;
        }
        else
        {
            level = rt_hw_interrupt_disable();
            can->status.dropedsndpkg++;
            rt_hw_interrupt_enable(level);
            break;
        }
    }

    return (size - msgs);
}

static rt_err_t rt_can_open(struct rt_device *dev, rt_uint16_t oflag)
{
    struct rt_can_device *can;
    char tmpname[16];
    RT_ASSERT(dev != RT_NULL);
    can = (struct rt_can_device *)dev;

    CAN_LOCK(can);

    /* get open flags */
    dev->open_flag = oflag & 0xff;
    if (can->can_rx == RT_NULL)
    {
        if (oflag & RT_DEVICE_FLAG_INT_RX)
        {
            int i = 0;
            struct rt_can_rx_fifo *rx_fifo;

            rx_fifo = (struct rt_can_rx_fifo *) rt_malloc(sizeof(struct rt_can_rx_fifo) +
                      can->config.msgboxsz * sizeof(struct rt_can_msg_list));
            RT_ASSERT(rx_fifo != RT_NULL);

            rx_fifo->buffer = (struct rt_can_msg_list *)(rx_fifo + 1);
            rt_memset(rx_fifo->buffer, 0, can->config.msgboxsz * sizeof(struct rt_can_msg_list));
            rt_list_init(&rx_fifo->freelist);
            rt_list_init(&rx_fifo->uselist);
            rx_fifo->freenumbers = can->config.msgboxsz;
            for (i = 0;  i < can->config.msgboxsz; i++)
            {
                rt_list_insert_before(&rx_fifo->freelist, &rx_fifo->buffer[i].list);
#ifdef RT_CAN_USING_HDR
                rt_list_init(&rx_fifo->buffer[i].hdrlist);
                rx_fifo->buffer[i].owner = RT_NULL;
#endif
            }
            can->can_rx = rx_fifo;

            dev->open_flag |= RT_DEVICE_FLAG_INT_RX;
            /* open can rx interrupt */
            can->ops->control(can, RT_DEVICE_CTRL_SET_INT, (void *)RT_DEVICE_FLAG_INT_RX);
        }
    }

    if (can->can_tx == RT_NULL)
    {
        if (oflag & RT_DEVICE_FLAG_INT_TX)
        {
            int i = 0;
            struct rt_can_tx_fifo *tx_fifo;

            tx_fifo = (struct rt_can_tx_fifo *) rt_malloc(sizeof(struct rt_can_tx_fifo) +
                      can->config.sndboxnumber * sizeof(struct rt_can_sndbxinx_list));
            RT_ASSERT(tx_fifo != RT_NULL);

            tx_fifo->buffer = (struct rt_can_sndbxinx_list *)(tx_fifo + 1);
            rt_memset(tx_fifo->buffer, 0,
                    can->config.sndboxnumber * sizeof(struct rt_can_sndbxinx_list));
            rt_list_init(&tx_fifo->freelist);
            for (i = 0;  i < can->config.sndboxnumber; i++)
            {
                rt_list_insert_before(&tx_fifo->freelist, &tx_fifo->buffer[i].list);
                rt_completion_init(&(tx_fifo->buffer[i].completion));
                tx_fifo->buffer[i].result = RT_CAN_SND_RESULT_OK;
            }

            rt_sprintf(tmpname, "%stl", dev->parent.name);
            rt_sem_init(&(tx_fifo->sem), tmpname, can->config.sndboxnumber, RT_IPC_FLAG_FIFO);
            can->can_tx = tx_fifo;

            dev->open_flag |= RT_DEVICE_FLAG_INT_TX;
            /* open can tx interrupt */
            can->ops->control(can, RT_DEVICE_CTRL_SET_INT, (void *)RT_DEVICE_FLAG_INT_TX);
        }
    }

    can->ops->control(can, RT_DEVICE_CTRL_SET_INT, (void *)RT_DEVICE_CAN_INT_ERR);

#ifdef RT_CAN_USING_HDR
    if (can->hdr == RT_NULL)
    {
        int i = 0;
        struct rt_can_hdr *phdr;

        phdr = (struct rt_can_hdr *) rt_malloc(can->config.maxhdr * sizeof(struct rt_can_hdr));
        RT_ASSERT(phdr != RT_NULL);
        rt_memset(phdr, 0, can->config.maxhdr * sizeof(struct rt_can_hdr));
        for (i = 0;  i < can->config.maxhdr; i++)
        {
            rt_list_init(&phdr[i].list);
        }

        can->hdr = phdr;
    }
#endif

    if (!can->timerinitflag)
    {
        can->timerinitflag = 1;

        rt_timer_start(&can->timer);
    }

    CAN_UNLOCK(can);

    return RT_EOK;
}

static rt_err_t rt_can_close(struct rt_device *dev)
{
    struct rt_can_device *can;

    RT_ASSERT(dev != RT_NULL);
    can = (struct rt_can_device *)dev;

    CAN_LOCK(can);

    /* this device has more reference count */
    if (dev->ref_count > 1)
    {
        CAN_UNLOCK(can);
        return RT_EOK;
    }

    if (can->timerinitflag)
    {
        can->timerinitflag = 0;

        rt_timer_stop(&can->timer);
    }

    can->status_indicate.ind = RT_NULL;
    can->status_indicate.args = RT_NULL;

#ifdef RT_CAN_USING_HDR
    if (can->hdr != RT_NULL)
    {
        rt_free(can->hdr);
        can->hdr = RT_NULL;
    }
#endif

    if (dev->open_flag & RT_DEVICE_FLAG_INT_RX)
    {
        struct rt_can_rx_fifo *rx_fifo;

        /* clear can rx interrupt */
        can->ops->control(can, RT_DEVICE_CTRL_CLR_INT, (void *)RT_DEVICE_FLAG_INT_RX);

        rx_fifo = (struct rt_can_rx_fifo *)can->can_rx;
        RT_ASSERT(rx_fifo != RT_NULL);

        rt_free(rx_fifo);
        dev->open_flag &= ~RT_DEVICE_FLAG_INT_RX;
        can->can_rx = RT_NULL;
    }

    if (dev->open_flag & RT_DEVICE_FLAG_INT_TX)
    {
        struct rt_can_tx_fifo *tx_fifo;

        /* clear can tx interrupt */
        can->ops->control(can, RT_DEVICE_CTRL_CLR_INT, (void *)RT_DEVICE_FLAG_INT_TX);

        tx_fifo = (struct rt_can_tx_fifo *)can->can_tx;
        RT_ASSERT(tx_fifo != RT_NULL);

        rt_sem_detach(&(tx_fifo->sem));
        rt_free(tx_fifo);
        dev->open_flag &= ~RT_DEVICE_FLAG_INT_TX;
        can->can_tx = RT_NULL;
    }

    can->ops->control(can, RT_DEVICE_CTRL_CLR_INT, (void *)RT_DEVICE_CAN_INT_ERR);

    CAN_UNLOCK(can);

    return RT_EOK;
}

static rt_ssize_t rt_can_read(struct rt_device *dev,
                             rt_off_t          pos,
                             void             *buffer,
                             rt_size_t         size)
{
    struct rt_can_device *can;

    RT_ASSERT(dev != RT_NULL);
    if (size == 0) return 0;

    can = (struct rt_can_device *)dev;

    if ((dev->open_flag & RT_DEVICE_FLAG_INT_RX) && (dev->ref_count > 0))
    {
        return _can_int_rx(can, buffer, size);
    }

    return 0;
}

static rt_ssize_t rt_can_write(struct rt_device *dev,
                              rt_off_t          pos,
                              const void       *buffer,
                              rt_size_t         size)
{
    struct rt_can_device *can;

    RT_ASSERT(dev != RT_NULL);
    if (size == 0) return 0;

    can = (struct rt_can_device *)dev;

    if ((dev->open_flag & RT_DEVICE_FLAG_INT_TX) && (dev->ref_count > 0))
    {
        if (can->config.privmode)
        {
            return _can_int_tx_priv(can, buffer, size);
        }
        else
        {
            return _can_int_tx(can, buffer, size);
        }
    }
    return 0;
}

static rt_err_t rt_can_control(struct rt_device *dev,
                               int              cmd,
                               void             *args)
{
    struct rt_can_device *can;
    rt_err_t res;

    res = RT_EOK;
    RT_ASSERT(dev != RT_NULL);
    can = (struct rt_can_device *)dev;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SUSPEND:
        /* suspend device */
        dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
        break;

    case RT_DEVICE_CTRL_RESUME:
        /* resume device */
        dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
        break;

    case RT_DEVICE_CTRL_CONFIG:
        /* configure device */
        res = can->ops->configure(can, (struct can_configure *)args);
        break;

    case RT_CAN_CMD_SET_PRIV:
        /* configure device */
        if ((rt_uint32_t)(rt_ubase_t)args != can->config.privmode)
        {
            int i;
            rt_base_t level;
            struct rt_can_tx_fifo *tx_fifo;

            res = can->ops->control(can, cmd, args);
            if (res != RT_EOK) return res;
            tx_fifo = (struct rt_can_tx_fifo *) can->can_tx;
            if (can->config.privmode)
            {
                for (i = 0;  i < can->config.sndboxnumber; i++)
                {
                    level = rt_hw_interrupt_disable();
                    if(rt_list_isempty(&tx_fifo->buffer[i].list))
                    {
                        rt_sem_release(&(tx_fifo->sem));
                    }
                    else
                    {
                        rt_list_remove(&tx_fifo->buffer[i].list);
                    }
                    rt_hw_interrupt_enable(level);
                }

            }
            else
            {
                for (i = 0;  i < can->config.sndboxnumber; i++)
                {
                    level = rt_hw_interrupt_disable();
                    if (tx_fifo->buffer[i].result == RT_CAN_SND_RESULT_OK)
                    {
                        rt_list_insert_before(&tx_fifo->freelist, &tx_fifo->buffer[i].list);
                    }
                    rt_hw_interrupt_enable(level);
                }
            }
        }
        break;

    case RT_CAN_CMD_SET_STATUS_IND:
        can->status_indicate.ind = ((rt_can_status_ind_type_t)args)->ind;
        can->status_indicate.args = ((rt_can_status_ind_type_t)args)->args;
        break;

#ifdef RT_CAN_USING_HDR
    case RT_CAN_CMD_SET_FILTER:
        res = can->ops->control(can, cmd, args);
        if (res != RT_EOK || can->hdr == RT_NULL)
        {
            return res;
        }

        struct rt_can_filter_config *pfilter;
        struct rt_can_filter_item *pitem;
        rt_uint32_t count;
        rt_base_t level;

        pfilter = (struct rt_can_filter_config *)args;
        RT_ASSERT(pfilter);
        count = pfilter->count;
        pitem = pfilter->items;
        if (pfilter->actived)
        {
            while (count)
            {
                if (pitem->hdr_bank >= can->config.maxhdr || pitem->hdr_bank < 0)
                {
                    count--;
                    pitem++;
                    continue;
                }

                level = rt_hw_interrupt_disable();
                if (!can->hdr[pitem->hdr_bank].connected)
                {
                    rt_hw_interrupt_enable(level);
                    rt_memcpy(&can->hdr[pitem->hdr_bank].filter, pitem,
                              sizeof(struct rt_can_filter_item));
                    level = rt_hw_interrupt_disable();
                    can->hdr[pitem->hdr_bank].connected = 1;
                    can->hdr[pitem->hdr_bank].msgs = 0;
                    rt_list_init(&can->hdr[pitem->hdr_bank].list);
                }
                rt_hw_interrupt_enable(level);

                count--;
                pitem++;
            }
        }
        else
        {
            while (count)
            {
                if (pitem->hdr_bank >= can->config.maxhdr || pitem->hdr_bank < 0)
                {
                    count--;
                    pitem++;
                    continue;
                }
                level = rt_hw_interrupt_disable();

                if (can->hdr[pitem->hdr_bank].connected)
                {
                    can->hdr[pitem->hdr_bank].connected = 0;
                    can->hdr[pitem->hdr_bank].msgs = 0;
                    if (!rt_list_isempty(&can->hdr[pitem->hdr_bank].list))
                    {
                        rt_list_remove(can->hdr[pitem->hdr_bank].list.next);
                    }
                    rt_hw_interrupt_enable(level);
                    rt_memset(&can->hdr[pitem->hdr_bank].filter, 0,
                              sizeof(struct rt_can_filter_item));
                }
                else
                {
                    rt_hw_interrupt_enable(level);
                }
                count--;
                pitem++;
            }
        }
        break;
#endif /*RT_CAN_USING_HDR*/
#ifdef RT_CAN_USING_BUS_HOOK
    case RT_CAN_CMD_SET_BUS_HOOK:
        can->bus_hook = (rt_can_bus_hook) args;
        break;
#endif /*RT_CAN_USING_BUS_HOOK*/
    default :
        /* control device */
        if (can->ops->control != RT_NULL)
        {
            res = can->ops->control(can, cmd, args);
        }
        else
        {
            res = -RT_ENOSYS;
        }
        break;
    }

    return res;
}

/*
 * can timer
 */
static void cantimeout(void *arg)
{
    rt_can_t can;

    can = (rt_can_t)arg;
    RT_ASSERT(can);
    rt_device_control((rt_device_t)can, RT_CAN_CMD_GET_STATUS, (void *)&can->status);

    if (can->status_indicate.ind != RT_NULL)
    {
        can->status_indicate.ind(can, can->status_indicate.args);
    }
#ifdef RT_CAN_USING_BUS_HOOK
    if(can->bus_hook)
    {
        can->bus_hook(can);
    }
#endif /*RT_CAN_USING_BUS_HOOK*/
    if (can->timerinitflag == 1)
    {
        can->timerinitflag = 0xFF;
    }
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops can_device_ops =
{
    rt_can_init,
    rt_can_open,
    rt_can_close,
    rt_can_read,
    rt_can_write,
    rt_can_control
};
#endif

/*
 * can register
 */
rt_err_t rt_hw_can_register(struct rt_can_device    *can,
                            const char              *name,
                            const struct rt_can_ops *ops,
                            void                    *data)
{
    struct rt_device *device;
    RT_ASSERT(can != RT_NULL);

    device = &(can->parent);

    device->type        = RT_Device_Class_CAN;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
#ifdef RT_CAN_USING_HDR
    can->hdr            = RT_NULL;
#endif
    can->can_rx         = RT_NULL;
    can->can_tx         = RT_NULL;
    rt_mutex_init(&(can->lock), "can", RT_IPC_FLAG_PRIO);
#ifdef RT_CAN_USING_BUS_HOOK
    can->bus_hook       = RT_NULL;
#endif /*RT_CAN_USING_BUS_HOOK*/

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &can_device_ops;
#else
    device->init        = rt_can_init;
    device->open        = rt_can_open;
    device->close       = rt_can_close;
    device->read        = rt_can_read;
    device->write       = rt_can_write;
    device->control     = rt_can_control;
#endif
    can->ops            = ops;

    can->status_indicate.ind  = RT_NULL;
    can->status_indicate.args = RT_NULL;
    rt_memset(&can->status, 0, sizeof(can->status));

    device->user_data   = data;

    can->timerinitflag  = 0;
    rt_timer_init(&can->timer,
                  name,
                  cantimeout,
                  (void *)can,
                  can->config.ticks,
                  RT_TIMER_FLAG_PERIODIC);
    /* register a character device */
    return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR);
}

/* ISR for can interrupt */
void rt_hw_can_isr(struct rt_can_device *can, int event)
{
    switch (event & 0xff)
    {
    case RT_CAN_EVENT_RXOF_IND:
    {
        rt_base_t level;
        level = rt_hw_interrupt_disable();
        can->status.dropedrcvpkg++;
        rt_hw_interrupt_enable(level);
    }
    case RT_CAN_EVENT_RX_IND:
    {
        struct rt_can_msg tmpmsg;
        struct rt_can_rx_fifo *rx_fifo;
        struct rt_can_msg_list *listmsg = RT_NULL;
#ifdef RT_CAN_USING_HDR
        rt_int8_t hdr;
#endif
        int ch = -1;
        rt_base_t level;
        rt_uint32_t no;

        rx_fifo = (struct rt_can_rx_fifo *)can->can_rx;
        RT_ASSERT(rx_fifo != RT_NULL);
        /* interrupt mode receive */
        RT_ASSERT(can->parent.open_flag & RT_DEVICE_FLAG_INT_RX);

        no = event >> 8;
        ch = can->ops->recvmsg(can, &tmpmsg, no);
        if (ch == -1) break;

        /* disable interrupt */
        level = rt_hw_interrupt_disable();
        can->status.rcvpkg++;
        can->status.rcvchange = 1;
        if (!rt_list_isempty(&rx_fifo->freelist))
        {
            listmsg = rt_list_entry(rx_fifo->freelist.next, struct rt_can_msg_list, list);
            rt_list_remove(&listmsg->list);
#ifdef RT_CAN_USING_HDR
            rt_list_remove(&listmsg->hdrlist);
            if (listmsg->owner != RT_NULL && listmsg->owner->msgs)
            {
                listmsg->owner->msgs--;
            }
            listmsg->owner = RT_NULL;
#endif /*RT_CAN_USING_HDR*/
            RT_ASSERT(rx_fifo->freenumbers > 0);
            rx_fifo->freenumbers--;
        }
        else if (!rt_list_isempty(&rx_fifo->uselist))
        {
            listmsg = rt_list_entry(rx_fifo->uselist.next, struct rt_can_msg_list, list);
            can->status.dropedrcvpkg++;
            rt_list_remove(&listmsg->list);
#ifdef RT_CAN_USING_HDR
            rt_list_remove(&listmsg->hdrlist);
            if (listmsg->owner != RT_NULL && listmsg->owner->msgs)
            {
                listmsg->owner->msgs--;
            }
            listmsg->owner = RT_NULL;
#endif
        }
        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        if (listmsg != RT_NULL)
        {
            rt_memcpy(&listmsg->data, &tmpmsg, sizeof(struct rt_can_msg));
            level = rt_hw_interrupt_disable();
            rt_list_insert_before(&rx_fifo->uselist, &listmsg->list);
#ifdef RT_CAN_USING_HDR
            hdr = tmpmsg.hdr_index;
            if (can->hdr != RT_NULL)
            {
                RT_ASSERT(hdr < can->config.maxhdr && hdr >= 0);
                if (can->hdr[hdr].connected)
                {
                    rt_list_insert_before(&can->hdr[hdr].list, &listmsg->hdrlist);
                    listmsg->owner = &can->hdr[hdr];
                    can->hdr[hdr].msgs++;
                }

            }
#endif
            rt_hw_interrupt_enable(level);
        }

        /* invoke callback */
#ifdef RT_CAN_USING_HDR
        if (can->hdr != RT_NULL && can->hdr[hdr].connected && can->hdr[hdr].filter.ind)
        {
            rt_size_t rx_length;
            RT_ASSERT(hdr < can->config.maxhdr && hdr >= 0);

            level = rt_hw_interrupt_disable();
            rx_length = can->hdr[hdr].msgs * sizeof(struct rt_can_msg);
            rt_hw_interrupt_enable(level);
            if (rx_length)
            {
                can->hdr[hdr].filter.ind(&can->parent, can->hdr[hdr].filter.args, hdr, rx_length);
            }
        }
        else
#endif
        {
            if (can->parent.rx_indicate != RT_NULL)
            {
                rt_size_t rx_length;

                level = rt_hw_interrupt_disable();
                /* get rx length */
                rx_length = rt_list_len(&rx_fifo->uselist)* sizeof(struct rt_can_msg);
                rt_hw_interrupt_enable(level);

                if (rx_length)
                {
                    can->parent.rx_indicate(&can->parent, rx_length);
                }
            }
        }
        break;
    }

    case RT_CAN_EVENT_TX_DONE:
    case RT_CAN_EVENT_TX_FAIL:
    {
        struct rt_can_tx_fifo *tx_fifo;
        rt_uint32_t no;
        no = event >> 8;
        tx_fifo = (struct rt_can_tx_fifo *) can->can_tx;
        RT_ASSERT(tx_fifo != RT_NULL);

        if ((event & 0xff) == RT_CAN_EVENT_TX_DONE)
        {
            tx_fifo->buffer[no].result = RT_CAN_SND_RESULT_OK;
        }
        else
        {
            tx_fifo->buffer[no].result = RT_CAN_SND_RESULT_ERR;
        }
        rt_completion_done(&(tx_fifo->buffer[no].completion));
        break;
    }
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>
int cmd_canstat(int argc, void **argv)
{
    static const char *ErrCode[] =
    {
        "No Error!",
        "Warning !",
        "Passive !",
        "Bus Off !"
    };

    if (argc >= 2)
    {
        struct rt_can_status status;
        rt_device_t candev = rt_device_find(argv[1]);
        if (!candev)
        {
            rt_kprintf(" Can't find can device %s\n", argv[1]);
            return -1;
        }
        rt_kprintf(" Found can device: %s...", argv[1]);

        rt_device_control(candev, RT_CAN_CMD_GET_STATUS, &status);
        rt_kprintf("\n Receive...error..count: %010ld. Send.....error....count: %010ld.",
                   status.rcverrcnt, status.snderrcnt);
        rt_kprintf("\n Bit..pad..error..count: %010ld. Format...error....count: %010ld",
                   status.bitpaderrcnt, status.formaterrcnt);
        rt_kprintf("\n Ack.......error..count: %010ld. Bit......error....count: %010ld.",
                   status.ackerrcnt, status.biterrcnt);
        rt_kprintf("\n CRC.......error..count: %010ld. Error.code.[%010ld]: ",
                   status.crcerrcnt, status.errcode);
        switch (status.errcode)
        {
        case 0:
            rt_kprintf("%s.", ErrCode[0]);
            break;
        case 1:
            rt_kprintf("%s.", ErrCode[1]);
            break;
        case 2:
        case 3:
            rt_kprintf("%s.", ErrCode[2]);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            rt_kprintf("%s.", ErrCode[3]);
            break;
        }
        rt_kprintf("\n Total.receive.packages: %010ld. Dropped.receive.packages: %010ld.",
                   status.rcvpkg, status.dropedrcvpkg);
        rt_kprintf("\n Total..send...packages: %010ld. Dropped...send..packages: %010ld.\n",
                   status.sndpkg + status.dropedsndpkg, status.dropedsndpkg);
    }
    else
    {
        rt_kprintf(" Invalid Call %s\n", argv[0]);
        rt_kprintf(" Please using %s cannamex .Here canname is driver name and x is candrive number.\n", argv[0]);
    }
    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_canstat, canstat, stat can device status);
#endif
