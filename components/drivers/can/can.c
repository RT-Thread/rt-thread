/*
 * File      : can.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       		Notes
 * 2015-05-14     aubrcool@qq.com 	first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

static rt_err_t rt_can_init(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    struct rt_can_device *can;

    RT_ASSERT(dev != RT_NULL);
    can = (struct rt_can_device *)dev;

    /* initialize rx/tx */
    can->can_rx = RT_NULL;
    can->can_tx = RT_NULL;

    /* apply configuration */
    if (can->ops->configure)
        result = can->ops->configure(can, &can->config);

    return result;
}
/*
 * can interrupt routines
 */
rt_inline int _can_int_rx(struct rt_can_device *can, struct rt_can_msg *data, int msgs)
{
    int size;
    struct rt_can_rx_fifo* rx_fifo;

    RT_ASSERT(can != RT_NULL);
    size = msgs; 
    
    rx_fifo = (struct rt_can_rx_fifo*) can->can_rx;
    RT_ASSERT(rx_fifo != RT_NULL);

    /* read from software FIFO */
    while (msgs)
    {
        rt_base_t level;
        struct rt_can_msg_list *listmsg=RT_NULL;
        /* disable interrupt */
        level = rt_hw_interrupt_disable();
#ifdef RT_CAN_USING_HDR
        rt_int32_t hdr = data->hdr;
        if (hdr >=0 && can->hdr && hdr < can->config.maxhdr && !rt_list_isempty(&can->hdr[hdr].list))
        {
             listmsg=rt_list_entry(can->hdr[hdr].list.next, struct rt_can_msg_list, hdrlist);
             rt_list_remove(&listmsg->list);
             rt_list_remove(&listmsg->hdrlist);
             if(can->hdr[hdr].msgs) {
               can->hdr[hdr].msgs--;                     
             }
             listmsg->owner = RT_NULL;
        } else
#endif /*RT_CAN_USING_HDR*/
        if (!rt_list_isempty(&rx_fifo->uselist))
        {
             listmsg=rt_list_entry(rx_fifo->uselist.next, struct rt_can_msg_list, list);
             rt_list_remove(&listmsg->list);
#ifdef RT_CAN_USING_HDR
             rt_list_remove(&listmsg->hdrlist);
             if(listmsg->owner != RT_NULL && listmsg->owner->msgs) {
                listmsg->owner->msgs--;                     
              }
              listmsg->owner = RT_NULL;
#endif
        }
        else
        {
            /* no data, enable interrupt and break out */
            rt_hw_interrupt_enable(level);
            break;
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);
        if(listmsg!=RT_NULL)
        {
            rt_memcpy(data,&listmsg->data,sizeof(struct rt_can_msg));
            level = rt_hw_interrupt_disable();
            rt_list_insert_before(&rx_fifo->freelist,&listmsg->list);
            rx_fifo->freenumbers++;
            RT_ASSERT(rx_fifo->freenumbers <= can->config.msgboxsz);
            rt_hw_interrupt_enable(level);
            listmsg = RT_NULL;
        }
        data ++; msgs -= sizeof(struct rt_can_msg);
    }

    return (size - msgs);
}

rt_inline int _can_int_tx(struct rt_can_device *can, const struct rt_can_msg *data, int msgs)
{
    int size;
    struct rt_can_tx_fifo *tx_fifo;
    
    RT_ASSERT(can != RT_NULL);

    size = msgs;
    tx_fifo = (struct rt_can_tx_fifo*) can->can_tx;
    RT_ASSERT(tx_fifo != RT_NULL);

    while (msgs)
    {      
        rt_base_t level;
        rt_uint32_t no;
        struct rt_can_sndbxinx_list* tx_tosnd = RT_NULL;
        level = rt_hw_interrupt_disable();
        if(!rt_list_isempty(&tx_fifo->freelist))
        {
            tx_tosnd = rt_list_entry(tx_fifo->freelist.next, struct rt_can_sndbxinx_list, list);
            RT_ASSERT(tx_tosnd != RT_NULL);
            rt_list_remove(&tx_tosnd->list);
        } else {
            rt_hw_interrupt_enable(level);
            rt_completion_wait(&(tx_fifo->completion), RT_WAITING_FOREVER);
            continue;
        }
        rt_hw_interrupt_enable(level);
        no=((rt_uint32_t)tx_tosnd-(rt_uint32_t)tx_fifo->buffer)/sizeof(struct rt_can_sndbxinx_list);
        tx_tosnd->result = RT_CAN__SND_RESUTL_WAIT;
        if (can->ops->sendmsg(can, data ,no))
        {
            level = rt_hw_interrupt_disable();
            rt_list_insert_after(&tx_fifo->freelist,&tx_tosnd->list);
            rt_hw_interrupt_enable(level);
            continue;
        }
        can->status.sndchange = 1;
        rt_completion_wait(&(tx_tosnd->completion), RT_WAITING_FOREVER);
        level = rt_hw_interrupt_disable();
        rt_uint32_t result = tx_tosnd->result;
        if(!rt_list_isempty(&tx_tosnd->list)) {
                rt_list_remove(&tx_tosnd->list);
        }
        rt_list_insert_before(&tx_fifo->freelist,&tx_tosnd->list);
        rt_hw_interrupt_enable(level);
        
        if(result == RT_CAN__SND_RESUTL_OK)
        {
            level = rt_hw_interrupt_disable();
            can->status.sndpkg++;
            rt_hw_interrupt_enable(level);
            data ++; msgs -= sizeof(struct rt_can_msg);
            if(!msgs) break;
        }
        else
        {
            level = rt_hw_interrupt_disable();
            can->status.dropedsndpkg++;
            rt_hw_interrupt_enable(level);
            break;
        }

        level = rt_hw_interrupt_disable();
        if(rt_list_isempty(&tx_fifo->freelist))
        {
              rt_hw_interrupt_enable(level);
              rt_completion_done(&(tx_fifo->completion));
        }
        else
        {
              rt_hw_interrupt_enable(level);
        }
    }

    return (size - msgs);
}
rt_inline int _can_int_tx_priv(struct rt_can_device *can, const struct rt_can_msg *data, int msgs)
{
    int size;
    struct rt_can_tx_fifo *tx_fifo;
    
    RT_ASSERT(can != RT_NULL);

    size = msgs;
    tx_fifo = (struct rt_can_tx_fifo*) can->can_tx;
    RT_ASSERT(tx_fifo != RT_NULL);

    rt_base_t level;
    rt_uint32_t no;
    rt_uint32_t result;
    while (msgs)
    {      
        no = data->priv;
        if(no >= can->config.sndboxnumber) {
           break;
        }
        level = rt_hw_interrupt_disable();
        if((tx_fifo->buffer[no].result != RT_CAN__SND_RESUTL_OK)) {
           rt_hw_interrupt_enable(level);
           rt_completion_wait(&(tx_fifo->buffer[no].completion), RT_WAITING_FOREVER);
           continue;
        }
        tx_fifo->buffer[no].result = RT_CAN__SND_RESUTL_WAIT;
        rt_hw_interrupt_enable(level);
        if (can->ops->sendmsg(can, data ,no) != RT_EOK)
        {
            continue;
        }
        can->status.sndchange = 1;
        rt_completion_wait(&(tx_fifo->buffer[no].completion), RT_WAITING_FOREVER);
        result = tx_fifo->buffer[no].result;
        if(result == RT_CAN__SND_RESUTL_OK)
        {
            level = rt_hw_interrupt_disable();
            can->status.sndpkg++;
            rt_hw_interrupt_enable(level);
            data ++; msgs -= sizeof(struct rt_can_msg);
            if(!msgs) break;
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

    RT_ASSERT(dev != RT_NULL);
    can = (struct rt_can_device *)dev;

    /* get open flags */
    dev->open_flag = oflag & 0xff;
    rt_enter_critical();
    if (can->can_rx == RT_NULL)
    {
        if (oflag & RT_DEVICE_FLAG_INT_RX)
        {
            struct rt_can_rx_fifo* rx_fifo;

            rx_fifo = (struct rt_can_rx_fifo*) rt_malloc (sizeof(struct rt_can_rx_fifo) + 
                can->config.msgboxsz * sizeof(struct rt_can_msg_list));
            RT_ASSERT(rx_fifo != RT_NULL);
            rx_fifo->buffer = (struct rt_can_msg_list*) (rx_fifo + 1);
            rt_memset(rx_fifo->buffer, 0, can->config.msgboxsz * sizeof(struct rt_can_msg_list));
            rt_list_init(&rx_fifo->freelist);
            rt_list_init(&rx_fifo->uselist);
            rx_fifo->freenumbers=can->config.msgboxsz;
            int i = 0;
            for(i = 0;  i< can->config.msgboxsz; i++)
            {
                  rt_list_insert_before(&rx_fifo->freelist,&rx_fifo->buffer[i].list);
#ifdef RT_CAN_USING_HDR
                  rt_list_init(&rx_fifo->buffer[i].hdrlist);
                  rx_fifo->buffer[i].owner = RT_NULL;
#endif
            }
            can->can_rx = rx_fifo;
            rt_exit_critical();
            dev->open_flag |= RT_DEVICE_FLAG_INT_RX;
            /* configure low level device */
            can->ops->control(can, RT_DEVICE_CTRL_SET_INT, (void *)RT_DEVICE_FLAG_INT_RX);
        }
        else
        {
            can->can_rx = RT_NULL;
            rt_exit_critical();
        }
    } else {
        rt_exit_critical();
    }
    rt_enter_critical();
    if (can->can_tx == RT_NULL)
    {
        if (oflag & RT_DEVICE_FLAG_INT_TX)
        {
            struct rt_can_tx_fifo *tx_fifo;

            tx_fifo = (struct rt_can_tx_fifo*) rt_malloc(sizeof(struct rt_can_tx_fifo)+
                                can->config.sndboxnumber*sizeof(struct rt_can_sndbxinx_list));
            RT_ASSERT(tx_fifo != RT_NULL);
            tx_fifo->buffer = (struct rt_can_sndbxinx_list *) (tx_fifo + 1);
            rt_memset(tx_fifo->buffer, 0, 
                      can->config.sndboxnumber*sizeof(struct rt_can_sndbxinx_list));
            rt_list_init(&tx_fifo->freelist);
            int i = 0;
            for(i = 0;  i< can->config.sndboxnumber; i++)
            {
                  rt_list_insert_before(&tx_fifo->freelist,&tx_fifo->buffer[i].list);
                  rt_completion_init(&(tx_fifo->buffer[i].completion));
                  tx_fifo->buffer[i].result = RT_CAN__SND_RESUTL_OK;
            }
            rt_completion_init(&(tx_fifo->completion));
            can->can_tx = tx_fifo;
            rt_exit_critical();
            dev->open_flag |= RT_DEVICE_FLAG_INT_TX;
            /* configure low level device */
            can->ops->control(can, RT_DEVICE_CTRL_SET_INT, (void *)RT_DEVICE_FLAG_INT_TX);
        }
        else
        {
            can->can_tx = RT_NULL;
            rt_exit_critical();
        }
    } else {
        rt_exit_critical();
    }
    can->ops->control(can, RT_DEVICE_CTRL_SET_INT, (void *)RT_DEVICE_CAN_INT_ERR);
#ifdef RT_CAN_USING_HDR
    rt_enter_critical();
    if(can->hdr == RT_NULL) {
        struct rt_can_hdr * phdr;
        phdr = (struct rt_can_hdr *) rt_malloc(can->config.maxhdr*sizeof(struct rt_can_hdr));
        RT_ASSERT(phdr != RT_NULL);
        rt_memset(phdr, 0,can->config.maxhdr*sizeof(struct rt_can_hdr));
        int i = 0;
        for(i = 0;  i< can->config.maxhdr; i++)
        {
              rt_list_init(&phdr[i].list);
        }
        can->hdr = phdr;
        rt_exit_critical();
    } else {
        rt_exit_critical();
    }
#endif
    rt_enter_critical();
    if(!can->timerinitflag) {
        can->timerinitflag = 1;
        rt_exit_critical();
        #ifdef RT_CAN_USING_LED
        if(can->config.rcvled != RT_NULL) {
            rt_pin_mode(can->config.rcvled->pin,can->config.rcvled->mode);
            rt_pin_write(can->config.rcvled->pin,can->config.rcvled->init);
        }
        if(can->config.sndled != RT_NULL) {
            rt_pin_mode(can->config.sndled->pin,can->config.sndled->mode);
            rt_pin_write(can->config.sndled->pin,can->config.sndled->init);
        }
        if(can->config.errled != RT_NULL) {
            rt_pin_mode(can->config.errled->pin,can->config.errled->mode);
            rt_pin_write(can->config.errled->pin,can->config.errled->init);
        }
        #endif
        rt_timer_start(&can->timer);
    } else {
        rt_exit_critical();
    }
    return RT_EOK;
}

static rt_err_t rt_can_close(struct rt_device *dev)
{
    struct rt_can_device *can;

    RT_ASSERT(dev != RT_NULL);
    can = (struct rt_can_device *)dev;

    /* this device has more reference count */
    if (dev->ref_count > 1) return RT_EOK;
    rt_enter_critical();
    if(can->timerinitflag) {
        can->timerinitflag = 0;
        rt_exit_critical();
        rt_timer_stop(&can->timer);
        #ifdef RT_CAN_USING_LED
        rt_pin_write(can->config.rcvled->pin,can->config.rcvled->init);
        rt_pin_write(can->config.rcvled->pin,can->config.sndled->init);
        rt_pin_write(can->config.rcvled->pin,can->config.errled->init);
        #endif
    } else {
        rt_exit_critical();
    }
    rt_enter_critical();
    can->status_indicate.ind = RT_NULL;
    can->status_indicate.args = RT_NULL;
    rt_exit_critical();
#ifdef RT_CAN_USING_HDR
    rt_enter_critical();
    if(can->hdr != RT_NULL) {
        rt_free(can->hdr);
        can->hdr = RT_NULL;
        rt_exit_critical();
    } else {
        rt_exit_critical();
    }
#endif
    if (dev->open_flag & RT_DEVICE_FLAG_INT_RX)
    {
        struct rt_can_rx_fifo* rx_fifo;

        rx_fifo = (struct rt_can_rx_fifo*)can->can_rx;
        RT_ASSERT(rx_fifo != RT_NULL);

        rt_free(rx_fifo);
        dev->open_flag &= ~RT_DEVICE_FLAG_INT_RX;
        /* configure low level device */
        can->ops->control(can, RT_DEVICE_CTRL_CLR_INT, (void*)RT_DEVICE_FLAG_INT_TX);
    }
    if (dev->open_flag & RT_DEVICE_FLAG_INT_TX)
    {
        struct rt_can_tx_fifo* tx_fifo;

        tx_fifo = (struct rt_can_tx_fifo*)can->can_rx;
        RT_ASSERT(tx_fifo != RT_NULL);

        rt_free(tx_fifo);
        dev->open_flag &= ~RT_DEVICE_FLAG_INT_TX;
        /* configure low level device */
        can->ops->control(can, RT_DEVICE_CTRL_CLR_INT, (void*)RT_DEVICE_FLAG_INT_TX);
    }
    can->ops->control(can, RT_DEVICE_CTRL_CLR_INT, (void *)RT_DEVICE_CAN_INT_ERR);
    return RT_EOK;
}

static rt_size_t rt_can_read(struct rt_device *dev,
                                rt_off_t          pos,
                                void             *buffer,
                                rt_size_t         size)
{
    struct rt_can_device *can;

    RT_ASSERT(dev != RT_NULL);
    if (size == 0) return 0;

    can = (struct rt_can_device *)dev;

    if (dev->open_flag & RT_DEVICE_FLAG_INT_RX)
    {
          return _can_int_rx(can, buffer, size);
    }
    return 0;
}

static rt_size_t rt_can_write(struct rt_device *dev,
                                 rt_off_t          pos,
                                 const void       *buffer,
                                 rt_size_t         size)
{
    struct rt_can_device *can;

    RT_ASSERT(dev != RT_NULL);
    if (size == 0) return 0;

    can = (struct rt_can_device *)dev;

    if (dev->open_flag & RT_DEVICE_FLAG_INT_TX)
    {
      if(can->config.privmode) {
         return _can_int_tx_priv(can, buffer, size);
      } else {
         return _can_int_tx(can, buffer, size);
      }
    }
    return 0;
}

static rt_err_t rt_can_control(struct rt_device *dev,
                                  rt_uint8_t        cmd,
                                  void             *args)
{
    struct rt_can_device *can;
    rt_err_t res;

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
            can->ops->configure(can, (struct can_configure *)args);
            break;
        case RT_CAN_CMD_SET_PRIV:
            /* configure device */
            if((rt_uint32_t)args != can->config.privmode) {
              if(res = can->ops->control(can, cmd, args) != RT_EOK) {
                return res;
              }
              struct rt_can_tx_fifo* tx_fifo;
              tx_fifo = (struct rt_can_tx_fifo*) can->can_tx;
              int i;
              rt_base_t level; 
              if(can->config.privmode) {
                  rt_completion_done(&(tx_fifo->completion));
                  level = rt_hw_interrupt_disable();
                   for(i = 0;  i< can->config.sndboxnumber; i++)
                   {
                       rt_list_remove(&tx_fifo->buffer[i].list);
                   }
                   rt_hw_interrupt_enable(level);
              } else {
                    for(i = 0;  i< can->config.sndboxnumber; i++)
                    {
                        rt_base_t level;
                        level = rt_hw_interrupt_disable();
                        if(tx_fifo->buffer[i].result == RT_CAN__SND_RESUTL_OK) {
                            rt_list_insert_before(&tx_fifo->freelist,&tx_fifo->buffer[i].list);
                        }
                        rt_hw_interrupt_enable(level);
                    }
              }
              return RT_EOK;
            }
            break;
      case RT_CAN_CMD_SET_STATUS_IND:
            can->status_indicate.ind = ((rt_can_status_ind_type_t)args)->ind;
            can->status_indicate.args = ((rt_can_status_ind_type_t)args)->args;
      break;
#ifdef RT_CAN_USING_HDR
        case RT_CAN_CMD_SET_FILTER:
            res = can->ops->control(can, cmd, args);
            if(res != RT_EOK || can->hdr == RT_NULL) {
              return res;
            }
            {
                  struct rt_can_filter_config* pfilter;
                  struct rt_can_filter_item* pitem;
                  rt_uint32_t count;
                  rt_base_t level; 
                  pfilter = (struct rt_can_filter_config*)args;
                  count = pfilter->count;
                  pitem = pfilter->items;
                  if(pfilter->actived) {
                        while(count) {
                          if(pitem->hdr >= can->config.maxhdr || pitem->hdr < 0) {
                            count--;
                            pitem++;
                            continue;
                          }
                          level = rt_hw_interrupt_disable();
                          if(!can->hdr[pitem->hdr].connected) {
                              rt_memcpy(&can->hdr[pitem->hdr].filter,pitem,
                                        sizeof(struct rt_can_filter_item));
                              can->hdr[pitem->hdr].connected = 1;
                              can->hdr[pitem->hdr].msgs = 0;
                              rt_list_init(&can->hdr[pitem->hdr].list);
                          }
                          rt_hw_interrupt_enable(level);
                          count--;
                          pitem++;
                        }
                  } else {
                       while(count) {
                          if(pitem->hdr >= can->config.maxhdr || pitem->hdr < 0) {
                            count--;
                            pitem++;
                            continue;
                          }
                          level = rt_hw_interrupt_disable();
                          if(can->hdr[pitem->hdr].connected) {
                              rt_memset(&can->hdr[pitem->hdr].filter,0,
                                        sizeof(struct rt_can_filter_item));
                              can->hdr[pitem->hdr].connected = 0;
                              can->hdr[pitem->hdr].msgs = 0;
                              if(!rt_list_isempty(&can->hdr[pitem->hdr].list))
                              {
                                  rt_list_remove(can->hdr[pitem->hdr].list.next);
                              }
                          }
                          rt_hw_interrupt_enable(level);
                          count--;
                          pitem++;
                        }
                  }
            }
            break;
#endif /*RT_CAN_USING_HDR*/
        default :
            /* control device */
            if(can->ops->control != RT_NULL)
            {
                can->ops->control(can, cmd, args);
            }
            break;
    }

    return RT_EOK;
}
/*
 * can timer
 */
static void cantimeout(void* arg)
{
     rt_uint32_t ledonflag = 0;
     rt_can_t can = (rt_can_t)arg;
     rt_device_control((rt_device_t)can,RT_CAN_CMD_GET_STATUS,(void* )&can->status);
     if(can->timerinitflag == 1) {
         ledonflag = 1;
         can->timerinitflag = 0xFF;
     }
     #ifdef RT_CAN_USING_LED
     if(can->config.rcvled != RT_NULL && can->config.sndled == RT_NULL) {
         if(ledonflag == 1) {
              rt_pin_write(can->config.rcvled->pin,can->config.rcvled->init?0:1);
         } else {
             if(can->status.rcvchange == 1 || can->status.sndchange == 1)
             {
                 can->status.rcvchange = 0;
                 can->status.sndchange = 0;
                 rt_pin_write(can->config.rcvled->pin,rt_pin_read(can->config.rcvled->pin)?0:1);
             } else {
                 rt_pin_write(can->config.rcvled->pin,can->config.rcvled->init);
             }
         }
     } else if(can->config.rcvled != RT_NULL && can->config.sndled != RT_NULL) {
         if(ledonflag == 1) {
               rt_pin_write(can->config.rcvled->pin,can->config.rcvled->init?0:1);
               rt_pin_write(can->config.sndled->pin,can->config.sndled->init?0:1);
         } else {
               if(can->status.rcvchange == 1)
               {
                   can->status.rcvchange = 0;
                   rt_pin_write(can->config.rcvled->pin,rt_pin_read(can->config.rcvled->pin)?0:1);
               } else {
                   rt_pin_write(can->config.rcvled->pin,can->config.rcvled->init);
               }
               if(can->status.sndchange == 1)
               {
                   can->status.sndchange = 0;
                   rt_pin_write(can->config.sndled->pin,rt_pin_read(can->config.sndled->pin)?0:1);
               } else {
                   rt_pin_write(can->config.sndled->pin,can->config.sndled->init);
               }
         }
     } else if(can->config.rcvled == RT_NULL && can->config.sndled != RT_NULL) {
         if(ledonflag == 1) {
               rt_pin_write(can->config.sndled->pin,can->config.sndled->init?0:1);
         } else {
               if(can->status.rcvchange == 1 || can->status.sndchange == 1)
               {
                   can->status.rcvchange = 0;
                   can->status.sndchange = 0;
                   rt_pin_write(can->config.sndled->pin,rt_pin_read(can->config.sndled->pin)?0:1);
               } else {
                   rt_pin_write(can->config.sndled->pin,can->config.sndled->init);
               }
         }
     }
     if(ledonflag == 1) {
           rt_pin_write(can->config.errled->pin,can->config.errled->init?0:1);
     } else {
           if(can->status.errcode) {
               rt_pin_write(can->config.errled->pin,can->config.errled->init?0:1);
           } else {
               rt_pin_write(can->config.errled->pin,can->config.errled->init);
           }
     }
     #endif
     if(can->status_indicate.ind != RT_NULL)
     {
         can->status_indicate.ind(can,can->status_indicate.args);
     }
}

/*
 * can register
 */
rt_err_t rt_hw_can_register(struct rt_can_device *can,
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
    device->init        = rt_can_init;
    device->open        = rt_can_open;
    device->close       = rt_can_close;
    device->read        = rt_can_read;
    device->write       = rt_can_write;
    device->control     = rt_can_control;
    can->ops            = ops;

    can->status_indicate.ind  = RT_NULL;
    can->status_indicate.args = RT_NULL;
    rt_memset(&can->status,0,sizeof(can->status));

    device->user_data   = data;
    can->timerinitflag = 0;
    if(can->config.rcvled != RT_NULL ||
       can->config.sndled != RT_NULL ||
       can->config.errled != RT_NULL)
    {
        rt_timer_init(&can->timer,
                  name,
                  cantimeout,
                  (void*)can,
                  can->config.ticks,
                  RT_TIMER_FLAG_PERIODIC);
    }
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
            struct rt_can_rx_fifo* rx_fifo;
            struct rt_can_msg_list* listmsg=RT_NULL;
#ifdef RT_CAN_USING_HDR
            rt_int32_t hdr;
#endif
            int ch = -1;
            rt_base_t level; 
            rx_fifo = (struct rt_can_rx_fifo*)can->can_rx;
            RT_ASSERT(rx_fifo != RT_NULL);
            /* interrupt mode receive */
            RT_ASSERT(can->parent.open_flag & RT_DEVICE_FLAG_INT_RX);
            
            rt_uint32_t no;
            no = event >> 8;
            ch = can->ops->recvmsg(can,&tmpmsg,no);
            if (ch == -1) break;
            /* disable interrupt */
            level = rt_hw_interrupt_disable();
            can->status.rcvpkg++;
            can->status.rcvchange = 1;
            if(!rt_list_isempty(&rx_fifo->freelist))
            {
                   listmsg = rt_list_entry(rx_fifo->freelist.next, struct rt_can_msg_list, list);
                   rt_list_remove(&listmsg->list);
#ifdef RT_CAN_USING_HDR
                   rt_list_remove(&listmsg->hdrlist);
                   if(listmsg->owner != RT_NULL && listmsg->owner->msgs) {
                     listmsg->owner->msgs--;                     
                   }
                   listmsg->owner = RT_NULL;
#endif /*RT_CAN_USING_HDR*/
                   RT_ASSERT(rx_fifo->freenumbers >0);
                   rx_fifo->freenumbers--;
            } else if(!rt_list_isempty(&rx_fifo->uselist)) {
                   listmsg = rt_list_entry(rx_fifo->uselist.next, struct rt_can_msg_list, list);
                   can->status.dropedrcvpkg++;
                   rt_list_remove(&listmsg->list);
#ifdef RT_CAN_USING_HDR
                   rt_list_remove(&listmsg->hdrlist);
                   if(listmsg->owner != RT_NULL && listmsg->owner->msgs) {
                     listmsg->owner->msgs--;                     
                   }
                   listmsg->owner = RT_NULL;
#endif
            }                  
            /* enable interrupt */
            rt_hw_interrupt_enable(level);
            if(listmsg != RT_NULL) {
                  rt_memcpy(&listmsg->data,&tmpmsg,sizeof(struct rt_can_msg));
                  level = rt_hw_interrupt_disable();
                  rt_list_insert_before(&rx_fifo->uselist,&listmsg->list);
#ifdef RT_CAN_USING_HDR
                  hdr = tmpmsg.hdr;
                  if(can->hdr != RT_NULL) {
                        RT_ASSERT(hdr < can->config.maxhdr && hdr >= 0);
                        if(can->hdr[hdr].connected) {
                            rt_list_insert_before(&can->hdr[hdr].list,&listmsg->hdrlist);
                            listmsg->owner = &can->hdr[hdr];
                            can->hdr[hdr].msgs++;
                        }
                        
                  }
#endif
                  rt_hw_interrupt_enable(level);
            }
            
            /* invoke callback */
#ifdef RT_CAN_USING_HDR
            if(can->hdr != RT_NULL && can->hdr[hdr].connected && can->hdr[hdr].filter.ind) {
                  RT_ASSERT(hdr < can->config.maxhdr && hdr >= 0);
                  rt_size_t rx_length;
                  level = rt_hw_interrupt_disable();
                  rx_length = can->hdr[hdr].msgs * sizeof(struct rt_can_msg);
                  rt_hw_interrupt_enable(level);
                  can->hdr[hdr].filter.ind(&can->parent, can->hdr[hdr].filter.args, hdr, rx_length);
                  
            } else
#endif
              if (can->parent.rx_indicate != RT_NULL) {
                rt_size_t rx_length;
                /* get rx length */
                level = rt_hw_interrupt_disable();
                rx_length = rx_fifo->freenumbers*sizeof(struct rt_can_msg);
                rt_hw_interrupt_enable(level);

                can->parent.rx_indicate(&can->parent, rx_length);
            }
            break;
        }
        case RT_CAN_EVENT_TX_DONE:
        case RT_CAN_EVENT_TX_FAIL:
        {
            struct rt_can_tx_fifo* tx_fifo;
            rt_uint32_t no;
            no = event >> 8;
            tx_fifo = (struct rt_can_tx_fifo*) can->can_tx;
            RT_ASSERT(tx_fifo != RT_NULL);
            if((event & 0xff) == RT_CAN_EVENT_TX_DONE) {
                tx_fifo->buffer[no].result = RT_CAN__SND_RESUTL_OK;
            } else {
                tx_fifo->buffer[no].result = RT_CAN__SND_RESUTL_ERR;
            }
            rt_completion_done(&(tx_fifo->buffer[no].completion));
            break;
        }
    }
}
#ifdef RT_USING_FINSH
#include <finsh.h>
int cmd_canstat(int argc,void** argv)
{
    static const char* ErrCode[] = {
      "No Error!",
      "Warning !",
      "Passive !",
      "Bus Off !"
    };
    if(argc >= 2) {
        rt_device_t candev = rt_device_find(argv[1]);
        if(!candev) {
            rt_kprintf(" Can't find can device %s\n",argv[1]);
            return -1;
        }
        rt_kprintf(" Finded can device: %s...",argv[1]);
        struct rt_can_status status;
        rt_device_control(candev,RT_CAN_CMD_GET_STATUS,&status);
        rt_kprintf("\n Receive...error..count: %010ld. Send.....error....count: %010ld.",
                   status.rcverrcnt,status.snderrcnt);
        rt_kprintf("\n Bit..pad..error..count: %010ld. Format...error....count: %010ld",
                   status.bitpaderrcnt,status.formaterrcnt);
        rt_kprintf("\n Ack.......error..count: %010ld. Bit......error....count: %010ld.",
                   status.ackerrcnt,status.biterrcnt);
        rt_kprintf("\n CRC.......error..count: %010ld. Error.code.[%010ld]: ",
                   status.crcerrcnt,status.errcode);
        switch(status.errcode) {
        case 0:
            rt_kprintf("%s.",ErrCode[0]);
        break;
        case 1:
            rt_kprintf("%s.",ErrCode[1]);
        break;
        case 2:
        case 3:
            rt_kprintf("%s.",ErrCode[2]);
        break;
        case 4:
        case 5:
        case 6:
        case 7:
            rt_kprintf("%s.",ErrCode[3]);
        break;
        }
        rt_kprintf("\n Total.receive.packages: %010ld. Droped.receive.packages: %010ld.",
                   status.rcvpkg,status.dropedrcvpkg);
        rt_kprintf("\n Total..send...packages: %010ld. Droped...send..packages: %010ld.\n",
           status.sndpkg + status.dropedsndpkg,status.dropedsndpkg);
    } else {
        rt_kprintf(" Invalid Call %s\n",argv[0]);
        rt_kprintf(" Please using %s cannamex .Here canname is driver name and x is candrive number.\n",argv[0]);
    }
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_canstat, __cmd_canstat, Stat Can Device Status.);
#endif
