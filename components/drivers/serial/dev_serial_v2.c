/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-01     KyleChan     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "Serial"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_SERIAL_BUF_STRATEGY_DROP
#define RT_SERIAL_FIFO_LOCK(spinlock) ((rt_base_t)0)
#define RT_SERIAL_FIFO_UNLOCK(spinlock, level) \
    do {                                       \
        RT_UNUSED(spinlock);                   \
        RT_UNUSED(level);                      \
    } while (0)
#else
#define RT_SERIAL_FIFO_LOCK(spinlock)          rt_spin_lock_irqsave(spinlock)
#define RT_SERIAL_FIFO_UNLOCK(spinlock, level) rt_spin_unlock_irqrestore(spinlock, level)
#endif /* RT_SERIAL_BUF_STRATEGY_DROP */

#ifdef RT_USING_POSIX_STDIO
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <dfs_file.h>

#ifdef RT_USING_POSIX_TERMIOS
#include <termios.h>
#endif

#ifdef getc
#undef getc
#endif

#ifdef putc
#undef putc
#endif

RT_OBJECT_HOOKLIST_DEFINE(rt_hw_serial_rxind);

static rt_err_t serial_fops_rx_ind(rt_device_t dev, rt_size_t size)
{
    rt_wqueue_wakeup(&dev->wait_queue, (void *)POLLIN);

    RT_OBJECT_HOOKLIST_CALL(rt_hw_serial_rxind, (dev, size));

    return RT_EOK;
}

/* fops for serial */
static int serial_fops_open(struct dfs_file *fd)
{
    rt_err_t                 ret   = 0;
    rt_uint16_t              flags = 0;
    rt_device_t              device;
    struct rt_serial_device *serial;

    device = (rt_device_t)fd->vnode->data;
    RT_ASSERT(device != RT_NULL);

    switch (fd->flags & O_ACCMODE)
    {
    case O_RDONLY:
        LOG_D("fops open: O_RDONLY!");
        flags = RT_DEVICE_FLAG_RDONLY;
        break;
    case O_WRONLY:
        LOG_D("fops open: O_WRONLY!");
        flags = RT_DEVICE_FLAG_WRONLY;
        break;
    case O_RDWR:
        LOG_D("fops open: O_RDWR!");
        flags = RT_DEVICE_FLAG_RDWR;
        break;
    default:
        LOG_E("fops open: unknown mode - %d!", fd->flags & O_ACCMODE);
        break;
    }

    if ((fd->flags & O_ACCMODE) != O_WRONLY)
        rt_device_set_rx_indicate(device, serial_fops_rx_ind);

    rt_device_close(device);
    ret = rt_device_open(device, flags | RT_SERIAL_RX_BLOCKING | RT_SERIAL_TX_BLOCKING);
    if (ret == RT_EOK)
    {
        serial                = (struct rt_serial_device *)device;
        serial->is_posix_mode = RT_TRUE;
    }

    return ret;
}

static int serial_fops_close(struct dfs_file *fd)
{
    rt_device_t device;

    device = (rt_device_t)fd->vnode->data;

    rt_device_set_rx_indicate(device, RT_NULL);
    rt_device_close(device);

    return 0;
}

static int serial_fops_ioctl(struct dfs_file *fd, int cmd, void *args)
{
    rt_device_t device;
    int         flags = (int)(rt_base_t)args;
    int         mask  = O_NONBLOCK | O_APPEND;

    device = (rt_device_t)fd->vnode->data;
    switch ((rt_ubase_t)cmd)
    {
    case FIONREAD:
        break;
    case FIONWRITE:
        break;
    case F_SETFL:
        flags     &= mask;
        fd->flags &= ~mask;
        fd->flags |= flags;
        break;
    default:
        break;
    }

    return rt_device_control(device, cmd, args);
}

#ifdef RT_USING_DFS_V2
static ssize_t serial_fops_read(struct dfs_file *fd, void *buf, size_t count, off_t *pos)
#else
static ssize_t serial_fops_read(struct dfs_file *fd, void *buf, size_t count)
#endif
{
    ssize_t     size = 0;
    rt_device_t device;
    rt_int32_t  rx_timout;

    if (count == 0) return 0;
    RT_ASSERT(fd != RT_NULL && buf != RT_NULL);

    device = (rt_device_t)fd->vnode->data;
    RT_ASSERT(device != RT_NULL);

    /* nonblock mode */
    if (fd->flags & O_NONBLOCK)
    {
        rx_timout = RT_WAITING_NO;
        rt_device_control(device, RT_SERIAL_CTRL_SET_RX_TIMEOUT, (void *)&rx_timout);
        size = rt_device_read(device, -1, buf, count);
        if (size <= 0)
        {
            size = -1;
            rt_set_errno(EAGAIN);
        }
    }
    else
    {
        rx_timout = RT_WAITING_FOREVER;
        rt_device_control(device, RT_SERIAL_CTRL_SET_RX_TIMEOUT, (void *)&rx_timout);
        size = rt_device_read(device, -1, buf, count);
    }


    return size;
}

#ifdef RT_USING_DFS_V2
static ssize_t serial_fops_write(struct dfs_file *fd, const void *buf, size_t count, off_t *pos)
#else
static ssize_t serial_fops_write(struct dfs_file *fd, const void *buf, size_t count)
#endif
{
    ssize_t     size = 0;
    rt_device_t device;
    rt_int32_t  tx_timeout;

    device = (rt_device_t)fd->vnode->data;

    if (fd->flags & O_NONBLOCK)
    {
        tx_timeout = RT_WAITING_NO;
        rt_device_control(device, RT_SERIAL_CTRL_SET_TX_TIMEOUT, (void *)&tx_timeout);
        size = rt_device_write(device, -1, buf, count);
        if (size <= 0)
        {
            size = -1;
            rt_set_errno(EAGAIN);
        }
    }
    else
    {
        tx_timeout = RT_WAITING_FOREVER;
        rt_device_control(device, RT_SERIAL_CTRL_SET_TX_TIMEOUT, (void *)&tx_timeout);
        size = rt_device_write(device, -1, buf, count);
    }

    return size;
}

static int serial_fops_flush(struct dfs_file *fd)
{
    rt_device_t device;
    device = (rt_device_t)fd->vnode->data;
    RT_ASSERT(device != RT_NULL);

    rt_device_control(device, RT_SERIAL_CTRL_TX_FLUSH, (void *)RT_NULL);
    rt_device_control(device, RT_SERIAL_CTRL_RX_FLUSH, (void *)RT_NULL);

    return 0;
}

static int serial_fops_poll(struct dfs_file *fd, struct rt_pollreq *req)
{
    int                      mask  = 0;
    int                      flags = 0;
    rt_device_t              device;
    struct rt_serial_device *serial;

    device = (rt_device_t)fd->vnode->data;
    RT_ASSERT(device != RT_NULL);

    serial = (struct rt_serial_device *)device;

    /* only support POLLIN */
    flags = fd->flags & O_ACCMODE;
    if (flags == O_RDONLY || flags == O_RDWR)
    {
        rt_base_t                 level;
        struct rt_serial_rx_fifo *rx_fifo;

        rt_poll_add(&device->wait_queue, req);

        rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

        level = RT_SERIAL_FIFO_LOCK(&serial->spinlock);
        if (rt_ringbuffer_data_len(&rx_fifo->rb))
            mask |= POLLIN;
        RT_SERIAL_FIFO_UNLOCK(&serial->spinlock, level);
    }
    /* mask|=POLLOUT; */
    return mask;
}

const static struct dfs_file_ops _serial_fops =
    {
        .open  = serial_fops_open,
        .close = serial_fops_close,
        .ioctl = serial_fops_ioctl,
        .read  = serial_fops_read,
        .write = serial_fops_write,
        .flush = serial_fops_flush,
        .poll  = serial_fops_poll,
};
#endif /* RT_USING_POSIX_STDIO */

static rt_ssize_t rt_serial_get_linear_buffer(struct rt_ringbuffer *rb,
                                              rt_uint8_t          **ptr)
{
    rt_size_t size;

    RT_ASSERT(rb != RT_NULL);

    /* whether has enough data  */
    size = rt_ringbuffer_data_len(rb);

    /* no data */
    if (size == 0)
        return 0;

    *ptr = &rb->buffer_ptr[rb->read_index];

    if (rb->buffer_size - rb->read_index > size)
    {
        return size;
    }

    return rb->buffer_size - rb->read_index;
}

#ifdef RT_SERIAL_USING_DMA
static void rt_serial_update_read_index(struct rt_ringbuffer *rb,
                                        rt_uint16_t           length)
{
    rt_size_t size;

    RT_ASSERT(rb != RT_NULL);

    /* whether has enough data  */
    size = rt_ringbuffer_data_len(rb);

    /* no data */
    if (size == 0)
        return;

    /* less data */
    if (size < length)
        length = size;

    if (rb->buffer_size - rb->read_index > length)
    {
        rb->read_index += length;
        return;
    }

    /* we are going into the other side of the mirror */
    rb->read_mirror = ~rb->read_mirror;
    rb->read_index  = length - (rb->buffer_size - rb->read_index);

    return;
}

static void rt_serial_update_write_index(struct rt_ringbuffer *rb,
                                         rt_uint16_t           length)
{
    rt_uint16_t space_length;
    RT_ASSERT(rb != RT_NULL);

    /* whether has enough space */
    space_length = rt_ringbuffer_space_len(rb);

    if (length > rb->buffer_size)
    {
        length = rb->buffer_size;
#if !defined(RT_USING_ULOG) || defined(ULOG_USING_ISR_LOG)
        LOG_W("The serial buffer (len %d) is overflow.", rb->buffer_size);
#endif
    }

    if (rb->buffer_size - rb->write_index > length)
    {
        /* this should not cause overflow because there is enough space for
         * length of data in current mirror */
        rb->write_index += length;

        if (length > space_length)
            rb->read_index = rb->write_index;

        return;
    }

    /* we are going into the other side of the mirror */
    rb->write_mirror = ~rb->write_mirror;
    rb->write_index  = length - (rb->buffer_size - rb->write_index);

    if (length > space_length)
    {
        if (rb->write_index <= rb->read_index)
            rb->read_mirror = ~rb->read_mirror;
        rb->read_index = rb->write_index;
    }
    return;
}
#endif /* RT_SERIAL_USING_DMA */

/**
  * @brief Serial polling receive data routine, This function will receive data
  *        in a continuous loop by one by one byte.
  * @param dev The pointer of device driver structure
  * @param pos Empty parameter.
  * @param buffer Receive data buffer.
  * @param size Receive data buffer length.
  * @return Return the final length of data received.
  */
rt_ssize_t _serial_poll_rx(struct rt_device *dev,
                           rt_off_t          pos,
                           void             *buffer,
                           rt_size_t         size)
{
    struct rt_serial_device *serial;
    rt_size_t                getc_size;
    int                      getc_element; /* Gets one byte of data received */
    rt_uint8_t              *getc_buffer;  /* Pointer to the receive data buffer */

    RT_ASSERT(dev != RT_NULL && buffer != RT_NULL);
    if (size == 0) return 0;

    serial      = (struct rt_serial_device *)dev;
    getc_buffer = (rt_uint8_t *)buffer;
    getc_size   = size;

    while (size)
    {
        getc_element = serial->ops->getc(serial);
        if (getc_element < 0) break;

        *getc_buffer = getc_element;

        ++getc_buffer;
        --size;

        if (serial->parent.open_flag & RT_DEVICE_FLAG_STREAM)
        {
            /* If open_flag satisfies RT_DEVICE_FLAG_STREAM
             * and the received character is '\n', exit the loop directly */
            if (getc_element == '\n') break;
        }
    }

    return getc_size - size;
}

/**
  * @brief Serial polling transmit data routines, This function will transmit
  *        data in a continuous loop by one by one byte.
  * @param dev The pointer of device driver structure
  * @param pos Empty parameter.
  * @param buffer Transmit data buffer.
  * @param size Transmit data buffer length.
  * @return Return the final length of data transmit.
  */
rt_ssize_t _serial_poll_tx(struct rt_device *dev,
                           rt_off_t          pos,
                           const void       *buffer,
                           rt_size_t         size)
{
    struct rt_serial_device *serial;
    rt_size_t                putc_size;
    rt_uint8_t              *putc_buffer; /* Pointer to the transmit data buffer */
    int                      putc_result;

    if (size == 0) return 0;
    RT_ASSERT(dev != RT_NULL && buffer != RT_NULL);

    serial      = (struct rt_serial_device *)dev;
    putc_buffer = (rt_uint8_t *)buffer;
    putc_size   = size;

    while (size)
    {
        if (serial->parent.open_flag & RT_DEVICE_FLAG_STREAM || (dev == rt_console_get_device()))
        {
            /* If open_flag satisfies RT_DEVICE_FLAG_STREAM and the received character is '\n',
             * inserts '\r' character before '\n' character for the effect of carriage return newline */
            if (*putc_buffer == '\n')
                serial->ops->putc(serial, '\r');
        }
        putc_result = serial->ops->putc(serial, *putc_buffer);
        if (putc_result < 0) break;

        ++putc_buffer;
        --size;
    }

    return putc_size - size;
}

/**
  * @brief Serial receive data routines, This function will receive
  *        data by using fifo
  *
  * @note In blocking mode, the function will wait until the specified amount of data is received or until a timeout occurs.
  *       In non-blocking mode, the function will immediately attempt to retrieve as much data as possible from the ring buffer and return.
  *
  * @param dev The pointer of device driver structure
  * @param pos Empty parameter.
  * @param buffer Receive data buffer.
  * @param size Receive data buffer length.
  * @return Returns the actual length of data received.
  */
static rt_ssize_t _serial_fifo_rx(struct rt_device *dev,
                                  rt_off_t          pos,
                                  void             *buffer,
                                  rt_size_t         size)
{
    struct rt_serial_device  *serial;
    struct rt_serial_rx_fifo *rx_fifo;
    rt_base_t                 level;
    rt_size_t                 recv_size = 0;

    if (size == 0) return 0;
    RT_ASSERT(dev != RT_NULL && buffer != RT_NULL);

    serial  = (struct rt_serial_device *)dev;
    rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

    if (dev->open_flag & RT_SERIAL_RX_BLOCKING)
    {
        rt_size_t  data_len;
        rt_tick_t  delta_tick;
        rt_size_t  rx_bufsz_third  = serial->config.rx_bufsz / 2;
        rt_int32_t base_rx_timeout = rt_atomic_load(&rx_fifo->rx_timeout);
        rt_int32_t rx_timeout_left = base_rx_timeout;
        rt_tick_t  begin_tick      = rt_tick_get();

        while (1)
        {
            if (rx_timeout_left != RT_WAITING_NO)
            {
                level    = rt_spin_lock_irqsave(&serial->spinlock);
                data_len = rt_ringbuffer_data_len(&rx_fifo->rb);
                if (data_len < size - recv_size)
                {
                    if (size - (recv_size + data_len) >= rx_bufsz_third)
                    {
                        rx_fifo->rx_cpt_index = rx_bufsz_third;
                    }
                    else
                    {
                        rx_fifo->rx_cpt_index = size - (recv_size + data_len);
                    }
                    rt_completion_wait(&rx_fifo->rx_cpt, 0);
                }
                rt_spin_unlock_irqrestore(&serial->spinlock, level);
            }

            level      = RT_SERIAL_FIFO_LOCK(&serial->spinlock);
            recv_size += rt_ringbuffer_get(&rx_fifo->rb, (rt_uint8_t *)buffer + recv_size, size - recv_size);
            RT_SERIAL_FIFO_UNLOCK(&serial->spinlock, level);
            if (recv_size == size || rx_timeout_left == RT_WAITING_NO)
            {
                break;
            }

            rt_completion_wait(&rx_fifo->rx_cpt, rx_timeout_left);
            if (rx_timeout_left != RT_WAITING_FOREVER)
            {
                delta_tick = rt_tick_get_delta(begin_tick);
                if (delta_tick >= base_rx_timeout)
                {
                    level      = RT_SERIAL_FIFO_LOCK(&serial->spinlock);
                    recv_size += rt_ringbuffer_get(&rx_fifo->rb, (rt_uint8_t *)buffer + recv_size, size - recv_size);
                    RT_SERIAL_FIFO_UNLOCK(&serial->spinlock, level);
                    return recv_size;
                }

                rx_timeout_left = base_rx_timeout - delta_tick;
            }
        }
    }
    else if (dev->open_flag & RT_SERIAL_RX_NON_BLOCKING)
    {
        /* When open_flag is RT_SERIAL_RX_NON_BLOCKING,
         * the data is retrieved directly from the ringbuffer and returned */
        level     = RT_SERIAL_FIFO_LOCK(&serial->spinlock);
        recv_size = rt_ringbuffer_get(&rx_fifo->rb, buffer, size);
        RT_SERIAL_FIFO_UNLOCK(&serial->spinlock, level);
    }

    return recv_size;
}

/**
  * @brief Serial transmit data routines, This function will transmit
  *        data by using blocking_nbuf.
  * @param dev The pointer of device driver structure
  * @param pos Empty parameter.
  * @param buffer Transmit data buffer.
  * @param size Transmit data buffer length.
  * @return Returns the actual length of data transmitted.
  */
static rt_ssize_t _serial_fifo_tx_blocking_nbuf(struct rt_device *dev,
                                                rt_off_t          pos,
                                                const void       *buffer,
                                                rt_size_t         size)
{
    struct rt_serial_device  *serial;
    struct rt_serial_tx_fifo *tx_fifo;
    rt_ssize_t                send_size;
    rt_err_t                  ret;

    if (size == 0) return 0;
    RT_ASSERT(dev != RT_NULL && buffer != RT_NULL);

    serial  = (struct rt_serial_device *)dev;
    tx_fifo = (struct rt_serial_tx_fifo *)serial->serial_tx;
    RT_ASSERT(tx_fifo != RT_NULL);

    if (rt_thread_self() == RT_NULL || (serial->parent.open_flag & RT_DEVICE_FLAG_STREAM) || (dev == rt_console_get_device()))
    {
        /* using poll tx when the scheduler not startup or in stream mode */
        return _serial_poll_tx(dev, pos, buffer, size);
    }

    /* When serial transmit in tx_blocking mode,
     * if the activated mode is RT_TRUE, it will return directly */
    if (rt_atomic_flag_test_and_set(&tx_fifo->activated))
    {
        return 0;
    }

    /* clear tx_cpt flag */
    rt_completion_wait(&tx_fifo->tx_cpt, 0);

    /* Call the transmit interface for transmission */
    send_size = serial->ops->transmit(serial,
                                      (rt_uint8_t *)buffer,
                                      size,
                                      RT_SERIAL_TX_BLOCKING);
    if (send_size <= 0)
    {
        return 0;
    }

    if (rt_atomic_load(&tx_fifo->tx_timeout) == RT_WAITING_NO)
    {
        /* The implementation of POSIX nonblock mode is to set tx_timeout to RT_WAITING_NO */
#ifdef RT_USING_POSIX_STDIO
        if (serial->is_posix_mode)
            return send_size;
#endif
        return 0;
    }

    /* Waiting for the transmission to complete */
    ret = rt_completion_wait(&tx_fifo->tx_cpt, rt_atomic_load(&tx_fifo->tx_timeout));
    if (ret != RT_EOK)
    {
        /* Cannot get the number of bytes sent under DMA, so returns 0 directly */
        return 0;
    }

    return send_size;
}

/**
  * @brief Serial transmit data routines, This function will transmit
  *        data by using blocking_buf.
  * @param dev The pointer of device driver structure
  * @param pos Empty parameter.
  * @param buffer Transmit data buffer.
  * @param size Transmit data buffer length.
  * @return Returns the final length of data transmitted.
  */
static rt_ssize_t _serial_fifo_tx_blocking_buf(struct rt_device *dev,
                                               rt_off_t          pos,
                                               const void       *buffer,
                                               rt_size_t         size)
{
    struct rt_serial_device  *serial;
    struct rt_serial_tx_fifo *tx_fifo;
    rt_base_t                 level;

    if (size == 0) return 0;
    RT_ASSERT(dev != RT_NULL && buffer != RT_NULL);

    serial  = (struct rt_serial_device *)dev;
    tx_fifo = (struct rt_serial_tx_fifo *)serial->serial_tx;
    RT_ASSERT(tx_fifo != RT_NULL);

    if (rt_thread_self() == RT_NULL || (serial->parent.open_flag & RT_DEVICE_FLAG_STREAM) || (dev == rt_console_get_device()))
    {
        /* using poll tx when the scheduler not startup or in stream mode */
        return _serial_poll_tx(dev, pos, buffer, size);
    }

    /* When serial transmit in tx_blocking mode,
     * if the activated mode is RT_TRUE, it will return directly */
    if (rt_atomic_flag_test_and_set(&tx_fifo->activated))
    {
        return 0;
    }

    rt_tick_t  delta_tick;
    rt_int32_t base_tx_timeout = rt_atomic_load(&tx_fifo->tx_timeout);
    rt_int32_t tx_timeout_left = base_tx_timeout;
    rt_tick_t  begin_tick      = rt_tick_get();
    rt_size_t  send_size       = 0;
    rt_size_t  rb_size;
    rt_ssize_t transmit_size;

    while (send_size != size)
    {
        /* Copy one piece of data into the ringbuffer at a time
         * until the length of the data is equal to size */
        level             = RT_SERIAL_FIFO_LOCK(&serial->spinlock);
        tx_fifo->put_size = rt_ringbuffer_put(&tx_fifo->rb,
                                              (rt_uint8_t *)buffer + send_size,
                                              size - send_size);
        rb_size           = rt_ringbuffer_data_len(&tx_fifo->rb);
        RT_SERIAL_FIFO_UNLOCK(&serial->spinlock, level);

        /* clear tx_cpt flag */
        rt_completion_wait(&tx_fifo->tx_cpt, 0);

        /* Call the transmit interface for transmission again */
        /* Note that in interrupt mode, buffer and tx_fifo->put_size
         * are inactive parameters */
        transmit_size = serial->ops->transmit(serial,
                                              (rt_uint8_t *)buffer + send_size,
                                              tx_fifo->put_size,
                                              RT_SERIAL_TX_BLOCKING);
        if (transmit_size <= 0)
        {
            return send_size;
        }

        if (tx_timeout_left == RT_WAITING_NO)
        {
            /* The implementation of POSIX nonblock mode is to set tx_timeout to RT_WAITING_NO */
#ifdef RT_USING_POSIX_STDIO
            if (serial->is_posix_mode)
                send_size += tx_fifo->put_size;
#endif
            break;
        }

        /* Waiting for the transmission to complete */
        rt_completion_wait(&tx_fifo->tx_cpt, tx_timeout_left);
        if (tx_timeout_left != RT_WAITING_FOREVER)
        {
            delta_tick = rt_tick_get_delta(begin_tick);
            if (delta_tick >= base_tx_timeout)
            {
                level      = RT_SERIAL_FIFO_LOCK(&serial->spinlock);
                send_size += rb_size - rt_ringbuffer_data_len(&tx_fifo->rb);
                RT_SERIAL_FIFO_UNLOCK(&serial->spinlock, level);
                return send_size;
            }

            tx_timeout_left = base_tx_timeout - delta_tick;
        }

        send_size += tx_fifo->put_size;
    }


    return send_size;
}

/**
  * @brief Serial transmit data routines, This function will transmit
  *        data by using nonblocking.
  * @param dev The pointer of device driver structure
  * @param pos Empty parameter.
  * @param buffer Transmit data buffer.
  * @param size Transmit data buffer length.
  * @return Return the final length of data transmit.
  */
static rt_ssize_t _serial_fifo_tx_nonblocking(struct rt_device *dev,
                                              rt_off_t          pos,
                                              const void       *buffer,
                                              rt_size_t         size)
{
    struct rt_serial_device  *serial;
    struct rt_serial_tx_fifo *tx_fifo;
    rt_uint8_t               *put_ptr = RT_NULL;
    rt_base_t                 level;
    rt_size_t                 send_size;
    rt_ssize_t                transmit_size;

    if (size == 0) return 0;
    RT_ASSERT(dev != RT_NULL && buffer != RT_NULL);

    serial  = (struct rt_serial_device *)dev;
    tx_fifo = (struct rt_serial_tx_fifo *)serial->serial_tx;
    RT_ASSERT(tx_fifo != RT_NULL);

    /* When serial transmit in tx_non_blocking mode, if the activated mode is RT_FALSE,
         * start copying data into the ringbuffer */
    if (!rt_atomic_flag_test_and_set(&tx_fifo->activated))
    {
        level = RT_SERIAL_FIFO_LOCK(&serial->spinlock);
        /* Copying data into the ringbuffer */
        send_size = rt_ringbuffer_put(&tx_fifo->rb, buffer, size);

        /* Get the linear length buffer from ringbuffer */
        tx_fifo->put_size = rt_serial_get_linear_buffer(&tx_fifo->rb, &put_ptr);
        RT_SERIAL_FIFO_UNLOCK(&serial->spinlock, level);

        /* clear tx_cpt flag */
        rt_completion_wait(&tx_fifo->tx_cpt, 0);

        /* Call the transmit interface for transmission again */
        /* Note that in interrupt mode, put_ptr and tx_fifo->put_size
         * are inactive parameters */
        transmit_size = serial->ops->transmit(serial,
                                              put_ptr,
                                              tx_fifo->put_size,
                                              RT_SERIAL_TX_NON_BLOCKING);
        if (transmit_size <= 0)
        {
            return 0;
        }
        /* In tx_nonblocking mode, there is no need to call rt_completion_wait() APIs to wait
         * for the rt_current_thread to resume */
        return send_size;
    }

    /* If the activated mode is RT_TRUE, it means that serial device is transmitting,
     * where only the data in the ringbuffer and there is no need to call the transmit() API.
     * Note that this part of the code requires disable interrupts
     * to prevent multi thread reentrant */

    level = RT_SERIAL_FIFO_LOCK(&serial->spinlock);
    /* Copying data into the ringbuffer */
    send_size = rt_ringbuffer_put(&tx_fifo->rb, buffer, size);
    RT_SERIAL_FIFO_UNLOCK(&serial->spinlock, level);

    return send_size;
}


/**
  * @brief Enable serial transmit mode.
  * @param dev The pointer of device driver structure
  * @param rx_oflag The flag of that the serial port opens.
  * @return Return the status of the operation.
  */
static rt_err_t rt_serial_tx_enable(struct rt_device *dev,
                                    rt_uint16_t       tx_oflag)
{
    struct rt_serial_device  *serial;
    struct rt_serial_tx_fifo *tx_fifo        = RT_NULL;
    rt_err_t                  control_result = RT_EOK;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

    if (serial->config.tx_bufsz == 0)
    {
        /* Cannot use RT_SERIAL_TX_NON_BLOCKING when tx_bufsz is 0 */
        if (tx_oflag == RT_SERIAL_TX_NON_BLOCKING)
        {
            LOG_E("(%s) serial device with misconfigure: tx_bufsz = 0",
                  dev->parent.name);
            return -RT_EINVAL;
        }

#ifndef RT_USING_DEVICE_OPS
        dev->write = _serial_poll_tx;
#endif

        dev->open_flag |= RT_SERIAL_TX_BLOCKING;
        return RT_EOK;
    }
    /* Limits the minimum value of tx_bufsz */
    if (serial->config.tx_bufsz < RT_SERIAL_TX_MINBUFSZ)
        serial->config.tx_bufsz = RT_SERIAL_TX_MINBUFSZ;

    if (tx_oflag == RT_SERIAL_TX_BLOCKING)
    {
        /* When using RT_SERIAL_TX_BLOCKING, it is necessary to determine
         * whether serial device needs to use buffer */
        /* Call the Control() API to get the operating mode */
        control_result = serial->ops->control(serial,
                                              RT_DEVICE_CHECK_OPTMODE,
                                              (void *)RT_DEVICE_FLAG_TX_BLOCKING);
        if (control_result < 0)
        {
            return control_result;
        }

        rt_err_t optmode = control_result;
        if (optmode == RT_SERIAL_TX_BLOCKING_BUFFER)
        {
            /* If use RT_SERIAL_TX_BLOCKING_BUFFER, the ringbuffer is initialized */
            tx_fifo = (struct rt_serial_tx_fifo *)rt_malloc(sizeof(struct rt_serial_tx_fifo) + serial->config.tx_bufsz);
            RT_ASSERT(tx_fifo != RT_NULL);
            rt_memset(tx_fifo, RT_NULL, sizeof(struct rt_serial_tx_fifo) + serial->config.tx_bufsz);
            rt_ringbuffer_init(&tx_fifo->rb,
                               (rt_uint8_t *)tx_fifo + sizeof(struct rt_serial_tx_fifo),
                               serial->config.tx_bufsz);
            serial->serial_tx = tx_fifo;

#ifndef RT_USING_DEVICE_OPS
            dev->write = _serial_fifo_tx_blocking_buf;
#endif
        }
        else if (optmode == RT_SERIAL_TX_BLOCKING_NO_BUFFER)
        {
            /* If not use RT_SERIAL_TX_BLOCKING_BUFFER,
             * the control() API is called to configure the serial device */
            tx_fifo = (struct rt_serial_tx_fifo *)rt_malloc(sizeof(struct rt_serial_tx_fifo));
            RT_ASSERT(tx_fifo != RT_NULL);
            rt_memset(tx_fifo, RT_NULL, sizeof(struct rt_serial_tx_fifo));
            /* Init rb.buffer_ptr to RT_NULL, in rt_serial_write() need check it
             * otherwise buffer_ptr maybe a random value, as rt_malloc not init memory */
            serial->serial_tx = tx_fifo;

#ifndef RT_USING_DEVICE_OPS
            dev->write = _serial_fifo_tx_blocking_nbuf;
#endif

            /* Call the control() API to configure the serial device by RT_SERIAL_TX_BLOCKING*/
            control_result = serial->ops->control(serial,
                                                  RT_DEVICE_CTRL_CONFIG,
                                                  (void *)RT_SERIAL_TX_BLOCKING);
            if (control_result < 0)
            {
                goto __exit;
            }
        }
        else
        {
            return -RT_EIO;
        }
        rt_atomic_flag_clear(&tx_fifo->activated);
        tx_fifo->put_size = 0;
        rt_atomic_store(&tx_fifo->tx_timeout, RT_WAITING_FOREVER);

        rt_completion_init(&tx_fifo->tx_cpt);
        dev->open_flag |= RT_SERIAL_TX_BLOCKING;

        return RT_EOK;
    }

    /* When using RT_SERIAL_TX_NON_BLOCKING, ringbuffer needs to be initialized,
     * and initialize the tx_fifo->activated value is RT_FALSE.
     */
    tx_fifo = (struct rt_serial_tx_fifo *)rt_malloc(sizeof(struct rt_serial_tx_fifo) + serial->config.tx_bufsz);
    RT_ASSERT(tx_fifo != RT_NULL);
    rt_memset(tx_fifo, RT_NULL, sizeof(struct rt_serial_tx_fifo) + serial->config.tx_bufsz);

    rt_ringbuffer_init(&tx_fifo->rb,
                       (rt_uint8_t *)tx_fifo + sizeof(struct rt_serial_tx_fifo),
                       serial->config.tx_bufsz);
    serial->serial_tx = tx_fifo;

    rt_atomic_flag_clear(&tx_fifo->activated);
    tx_fifo->put_size = 0;

#ifndef RT_USING_DEVICE_OPS
    dev->write = _serial_fifo_tx_nonblocking;
#endif

    rt_completion_init(&tx_fifo->tx_cpt);
    dev->open_flag |= RT_SERIAL_TX_NON_BLOCKING;

    /* Call the control() API to configure the serial device by RT_SERIAL_TX_NON_BLOCKING*/
    control_result = serial->ops->control(serial,
                                          RT_DEVICE_CTRL_CONFIG,
                                          (void *)RT_SERIAL_TX_NON_BLOCKING);

__exit:
    return control_result;
}


/**
  * @brief Enable serial receive mode.
  * @param dev The pointer of device driver structure
  * @param rx_oflag The flag of that the serial port opens.
  * @return Return the status of the operation.
  */
static rt_err_t rt_serial_rx_enable(struct rt_device *dev,
                                    rt_uint16_t       rx_oflag)
{
    struct rt_serial_device  *serial;
    struct rt_serial_rx_fifo *rx_fifo      = RT_NULL;
    rt_size_t                 rx_fifo_size = 0;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

    if (serial->config.rx_bufsz == 0)
    {
        /* Cannot use RT_SERIAL_RX_NON_BLOCKING when rx_bufsz is 0 */
        if (rx_oflag == RT_SERIAL_RX_NON_BLOCKING)
        {
            LOG_E("(%s) serial device with misconfigure: rx_bufsz = 0",
                  dev->parent.name);
            return -RT_EINVAL;
        }

#ifndef RT_USING_DEVICE_OPS
        dev->read = _serial_poll_rx;
#endif

        dev->open_flag |= RT_SERIAL_RX_BLOCKING;
        return RT_EOK;
    }
    /* Limits the minimum value of rx_bufsz */
    if (serial->config.rx_bufsz < RT_SERIAL_RX_MINBUFSZ)
        serial->config.rx_bufsz = RT_SERIAL_RX_MINBUFSZ;

#ifdef RT_SERIAL_USING_DMA
    if (serial->config.dma_ping_bufsz < RT_SERIAL_RX_MINBUFSZ / 2)
        serial->config.dma_ping_bufsz = RT_SERIAL_RX_MINBUFSZ / 2;
    rx_fifo_size = sizeof(struct rt_serial_rx_fifo) + serial->config.rx_bufsz + serial->config.dma_ping_bufsz;
#else
    rx_fifo_size = sizeof(struct rt_serial_rx_fifo) + serial->config.rx_bufsz;
#endif

    rx_fifo = (struct rt_serial_rx_fifo *)rt_malloc(rx_fifo_size);
    RT_ASSERT(rx_fifo != RT_NULL);
    rt_memset(rx_fifo, RT_NULL, rx_fifo_size);

    rt_ringbuffer_init(&rx_fifo->rb,
                       (rt_uint8_t *)rx_fifo + sizeof(struct rt_serial_rx_fifo),
                       serial->config.rx_bufsz);

#ifdef RT_SERIAL_USING_DMA
    rt_ringbuffer_init(&rx_fifo->dma_ping_rb,
                       (rt_uint8_t *)rx_fifo + sizeof(struct rt_serial_rx_fifo) + serial->config.rx_bufsz,
                       serial->config.dma_ping_bufsz);
#endif

    serial->serial_rx = rx_fifo;

#ifndef RT_USING_DEVICE_OPS
    dev->read = _serial_fifo_rx;
#endif

    if (rx_oflag == RT_SERIAL_RX_NON_BLOCKING)
    {
        dev->open_flag |= RT_SERIAL_RX_NON_BLOCKING;
        /* Call the control() API to configure the serial device by RT_SERIAL_RX_NON_BLOCKING*/
        return serial->ops->control(serial, RT_DEVICE_CTRL_CONFIG, (void *)RT_SERIAL_RX_NON_BLOCKING);
    }

    /* When using RT_SERIAL_RX_BLOCKING, rt_completion_init() and rx_cpt_index are initialized */
    rx_fifo->rx_cpt_index = 0;
    rt_atomic_store(&rx_fifo->rx_timeout, RT_WAITING_FOREVER);

    rt_completion_init(&rx_fifo->rx_cpt);
    dev->open_flag |= RT_SERIAL_RX_BLOCKING;
    /* Call the control() API to configure the serial device by RT_SERIAL_RX_BLOCKING*/
    return serial->ops->control(serial, RT_DEVICE_CTRL_CONFIG, (void *)RT_SERIAL_RX_BLOCKING);
}

/**
  * @brief Disable serial receive mode.
  * @param dev The pointer of device driver structure
  * @param rx_oflag The flag of that the serial port opens.
  * @return Return the status of the operation.
  */
static rt_err_t rt_serial_rx_disable(struct rt_device *dev,
                                     rt_uint16_t       rx_oflag)
{
    struct rt_serial_device  *serial;
    struct rt_serial_rx_fifo *rx_fifo;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

#ifndef RT_USING_DEVICE_OPS
    dev->read = RT_NULL;
#endif

    if (serial->serial_rx == RT_NULL) return RT_EOK;

    rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
    RT_ASSERT(rx_fifo != RT_NULL);

    if (rx_oflag == RT_SERIAL_RX_NON_BLOCKING)
    {
        dev->open_flag &= ~RT_SERIAL_RX_NON_BLOCKING;
        /* disable ignore return value */
        serial->ops->control(serial,
                             RT_DEVICE_CTRL_CLR_INT,
                             (void *)RT_SERIAL_RX_NON_BLOCKING);
    }
    else
    {
        rt_completion_done(&rx_fifo->rx_cpt);
        dev->open_flag &= ~RT_SERIAL_RX_BLOCKING;
        /* disable ignore return value */
        serial->ops->control(serial,
                             RT_DEVICE_CTRL_CLR_INT,
                             (void *)RT_SERIAL_RX_BLOCKING);
    }

    rt_free(rx_fifo);
    serial->serial_rx = RT_NULL;

    return RT_EOK;
}

/**
  * @brief Disable serial tranmit mode.
  * @param dev The pointer of device driver structure
  * @param rx_oflag The flag of that the serial port opens.
  * @return Return the status of the operation.
  */
static rt_err_t rt_serial_tx_disable(struct rt_device *dev,
                                     rt_uint16_t       tx_oflag)
{
    struct rt_serial_device  *serial;
    struct rt_serial_tx_fifo *tx_fifo;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

#ifndef RT_USING_DEVICE_OPS
    dev->write = RT_NULL;
#endif

    if (serial->serial_tx == RT_NULL) return RT_EOK;

    tx_fifo = (struct rt_serial_tx_fifo *)serial->serial_tx;
    RT_ASSERT(tx_fifo != RT_NULL);

    if (tx_oflag == RT_SERIAL_TX_NON_BLOCKING)
    {
        dev->open_flag &= ~RT_SERIAL_TX_NON_BLOCKING;
        /* disable ignore return value */
        serial->ops->control(serial,
                             RT_DEVICE_CTRL_CLR_INT,
                             (void *)RT_SERIAL_TX_NON_BLOCKING);
    }
    else
    {
        rt_completion_done(&tx_fifo->tx_cpt);
        dev->open_flag &= ~RT_SERIAL_TX_BLOCKING;
        /* disable ignore return value */
        serial->ops->control(serial,
                             RT_DEVICE_CTRL_CLR_INT,
                             (void *)RT_SERIAL_TX_BLOCKING);
    }


    rt_free(tx_fifo);
    serial->serial_tx = RT_NULL;
    return RT_EOK;
}

/**
  * @brief Initialize the serial device.
  * @param dev The pointer of device driver structure
  * @return Return the status of the operation.
  */
static rt_err_t rt_serial_init(struct rt_device *dev)
{
    rt_err_t                 result = RT_EOK;
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;
    RT_ASSERT(serial->ops->transmit != RT_NULL);

    /* initialize rx/tx */
    serial->serial_rx = RT_NULL;
    serial->serial_tx = RT_NULL;

    /* apply configuration */
    if (serial->ops->configure)
        result = serial->ops->configure(serial, &serial->config);

    return result;
}

/**
  * @brief Close the serial device.
  * @param dev The pointer of device driver structure
  * @return Return the status of the operation.
  */
static rt_err_t rt_serial_close(struct rt_device *dev)
{
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

    /* Disable serial receive mode. */
    rt_serial_rx_disable(dev, dev->open_flag & (RT_SERIAL_RX_BLOCKING | RT_SERIAL_RX_NON_BLOCKING));
    /* Disable serial tranmit mode. */
    rt_serial_tx_disable(dev, dev->open_flag & (RT_SERIAL_TX_BLOCKING | RT_SERIAL_TX_NON_BLOCKING));

    /* Clear the callback function */
    serial->parent.rx_indicate = RT_NULL;
    serial->parent.tx_complete = RT_NULL;

    rt_memset(&serial->rx_notify, RT_NULL, sizeof(struct rt_device_notify));

    /* Call the control() API to close the serial device. disable ignore return value */
    serial->ops->control(serial, RT_DEVICE_CTRL_CLOSE, RT_NULL);
    dev->flag &= ~RT_DEVICE_FLAG_ACTIVATED;

    return RT_EOK;
}

/**
  * @brief Open the serial device.
  * @param dev The pointer of device driver structure
  * @param oflag The flag of that the serial port opens.
  * @return Return the status of the operation.
  */
static rt_err_t rt_serial_open(struct rt_device *dev, rt_uint16_t oflag)
{
    struct rt_serial_device *serial;
    rt_err_t                 result = RT_EOK;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

    LOG_D("open serial device: 0x%08x with open flag: 0x%04x", dev, oflag);

    /* By default, the receive mode of a serial devide is RT_SERIAL_RX_NON_BLOCKING */
    if ((oflag & RT_SERIAL_RX_BLOCKING) == RT_SERIAL_RX_BLOCKING)
        dev->open_flag |= RT_SERIAL_RX_BLOCKING;
    else
        dev->open_flag |= RT_SERIAL_RX_NON_BLOCKING;

    /* By default, the transmit mode of a serial devide is RT_SERIAL_TX_BLOCKING */
    if ((oflag & RT_SERIAL_TX_NON_BLOCKING) == RT_SERIAL_TX_NON_BLOCKING)
        dev->open_flag |= RT_SERIAL_TX_NON_BLOCKING;
    else
        dev->open_flag |= RT_SERIAL_TX_BLOCKING;

    /* set steam flag */
    if ((oflag & RT_DEVICE_FLAG_STREAM) || (dev->open_flag & RT_DEVICE_FLAG_STREAM))
        dev->open_flag |= RT_DEVICE_FLAG_STREAM;

    /* initialize the Rx structure according to open flag */
    if (serial->serial_rx == RT_NULL)
    {
        result = rt_serial_rx_enable(dev, dev->open_flag & (RT_SERIAL_RX_BLOCKING | RT_SERIAL_RX_NON_BLOCKING));
        if (result != RT_EOK)
        {
            rt_serial_close(dev);
            goto __exit;
        }
    }

    /* initialize the Tx structure according to open flag */
    if (serial->serial_tx == RT_NULL)
    {
        result = rt_serial_tx_enable(dev, dev->open_flag & (RT_SERIAL_TX_BLOCKING | RT_SERIAL_TX_NON_BLOCKING));
        if (result != RT_EOK)
        {
            rt_serial_close(dev);
            goto __exit;
        }
    }

__exit:
    return result;
}


static void _serial_rx_flush(struct rt_serial_device *serial)
{
    rt_base_t                 level;
    struct rt_serial_rx_fifo *rx_fifo;
    RT_ASSERT(serial != RT_NULL);

    if (serial->config.rx_bufsz == 0)
    {
        rt_uint32_t rx_flush_limit = 0xFFFFFFF;
        while (serial->ops->getc(serial) != -1 && rx_flush_limit > 0)
        {
            rx_flush_limit--;
        }
    }
    else
    {
        rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
        RT_ASSERT(rx_fifo != RT_NULL);

        level = rt_spin_lock_irqsave(&serial->spinlock);
        rt_completion_wait(&rx_fifo->rx_cpt, 0);
        rt_ringbuffer_reset(&rx_fifo->rb);
        rx_fifo->rx_cpt_index = 0;
#ifdef RT_SERIAL_USING_DMA
        rt_serial_update_read_index(&rx_fifo->dma_ping_rb, rt_ringbuffer_get_size(&rx_fifo->dma_ping_rb));
#endif
        rt_spin_unlock_irqrestore(&serial->spinlock, level);
    }
}

static void _serial_tx_flush(struct rt_serial_device *serial)
{
    struct rt_serial_tx_fifo *tx_fifo;
    RT_ASSERT(serial != RT_NULL);

    if (serial->config.tx_bufsz != 0)
    {
        tx_fifo = (struct rt_serial_tx_fifo *)serial->serial_tx;
        RT_ASSERT(tx_fifo != RT_NULL);

        if (rt_atomic_load(&tx_fifo->activated))
        {
            rt_completion_wait(&tx_fifo->tx_cpt, RT_WAITING_FOREVER);
        }
    }
}

static rt_err_t _serial_get_unread_bytes_count(struct rt_serial_device *serial, rt_ssize_t *unread_bytes)
{
    rt_base_t                 level;
    struct rt_serial_rx_fifo *rx_fifo;
    RT_ASSERT(serial != RT_NULL);

    if (serial->config.rx_bufsz == 0)
    {
        LOG_W("get unread bytes count not support in poll mode.");
        *unread_bytes = -1;
        return -RT_EPERM;
    }

    rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
    RT_ASSERT(rx_fifo != RT_NULL);

    level         = RT_SERIAL_FIFO_LOCK(&serial->spinlock);
    *unread_bytes = rt_ringbuffer_data_len(&rx_fifo->rb);
    RT_SERIAL_FIFO_UNLOCK(&serial->spinlock, level);

    return RT_EOK;
}

#ifdef RT_USING_POSIX_TERMIOS
struct speed_baudrate_item
{
    speed_t speed;
    int     baudrate;
};

const static struct speed_baudrate_item _tbl[] =
    {
        {   B2400,    BAUD_RATE_2400},
        {   B4800,    BAUD_RATE_4800},
        {   B9600,    BAUD_RATE_9600},
        {  B19200,   BAUD_RATE_19200},
        {  B38400,   BAUD_RATE_38400},
        {  B57600,   BAUD_RATE_57600},
        { B115200,  BAUD_RATE_115200},
        { B230400,  BAUD_RATE_230400},
        { B460800,  BAUD_RATE_460800},
        { B500000,  BAUD_RATE_500000},
        { B921600,  BAUD_RATE_921600},
        {B2000000, BAUD_RATE_2000000},
        {B3000000, BAUD_RATE_3000000},
};

static speed_t _get_speed(int baudrate)
{
    int index;

    for (index = 0; index < sizeof(_tbl) / sizeof(_tbl[0]); index++)
    {
        if (_tbl[index].baudrate == baudrate)
            return _tbl[index].speed;
    }

    return B0;
}

static int _get_baudrate(speed_t speed)
{
    int index;

    for (index = 0; index < sizeof(_tbl) / sizeof(_tbl[0]); index++)
    {
        if (_tbl[index].speed == speed)
            return _tbl[index].baudrate;
    }

    return 0;
}

static void _tc_flush(struct rt_serial_device *serial, int queue)
{
    RT_ASSERT(serial != RT_NULL);

    if (queue == TCIFLUSH || queue == TCIOFLUSH)
    {
        _serial_rx_flush(serial);
    }

    if (queue == TCOFLUSH || queue == TCIOFLUSH)
    {
        _serial_tx_flush(serial);
    }
}
#endif /* RT_USING_POSIX_TERMIOS */

/**
  * @brief Control the serial device.
  * @param dev The pointer of device driver structure
  * @param cmd The command value that controls the serial device
  * @param args The parameter value that controls the serial device
  * @return Return the status of the operation.
  */
static rt_err_t rt_serial_control(struct rt_device *dev,
                                  int               cmd,
                                  void             *args)
{
    rt_err_t                 ret = RT_EOK;
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

    switch ((rt_ubase_t)cmd)
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
        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
        }
        else
        {
            struct serial_configure *pconfig = (struct serial_configure *)args;
            if (((pconfig->rx_bufsz != serial->config.rx_bufsz)
                 || (pconfig->tx_bufsz != serial->config.tx_bufsz)
#ifdef RT_SERIAL_USING_DMA
                 || (pconfig->dma_ping_bufsz != serial->config.dma_ping_bufsz)
#endif
                     )
                && serial->parent.ref_count != 0)
            {
                /*can not change buffer size*/
                ret = -RT_EBUSY;
                break;
            }
            /* set serial configure */
            serial->config = *pconfig;
            serial->ops->configure(serial, (struct serial_configure *)args);
        }
        break;
    case RT_SERIAL_CTRL_GET_CONFIG:
        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
        }
        else
        {
            struct serial_configure *pconfig = (struct serial_configure *)args;
            *pconfig                         = serial->config;
        }
        break;
    case RT_DEVICE_CTRL_NOTIFY_SET:
        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
        }
        else
        {
            rt_memcpy(&serial->rx_notify, args, sizeof(struct rt_device_notify));
        }
        break;

    case RT_DEVICE_CTRL_CONSOLE_OFLAG:
        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
        }
        else
        {
            *(rt_uint16_t *)args = RT_DEVICE_FLAG_RDWR | RT_SERIAL_RX_BLOCKING | RT_SERIAL_TX_BLOCKING | RT_DEVICE_FLAG_STREAM;
        }
        break;

    /* Call before rt_device_read */
    case RT_SERIAL_CTRL_SET_RX_TIMEOUT:
        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
        }
        else
        {
            if (serial->config.rx_bufsz == 0)
            {
                ret = -RT_EPERM;
            }

            struct rt_serial_rx_fifo *rx_fifo = RT_NULL;
            rx_fifo                           = (struct rt_serial_rx_fifo *)serial->serial_rx;
            RT_ASSERT(rx_fifo != RT_NULL);

            rt_atomic_store(&rx_fifo->rx_timeout, *(rt_int32_t *)args);
        }
        break;

    /* Call before rt_device_write */
    case RT_SERIAL_CTRL_SET_TX_TIMEOUT:
        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
        }
        else
        {
            if (serial->config.tx_bufsz == 0)
            {
                ret = -RT_EPERM;
            }

            struct rt_serial_tx_fifo *tx_fifo = RT_NULL;
            tx_fifo                           = (struct rt_serial_tx_fifo *)serial->serial_tx;
            RT_ASSERT(tx_fifo != RT_NULL);

            rt_atomic_store(&tx_fifo->tx_timeout, *(rt_int32_t *)args);
        }
        break;

    case RT_SERIAL_CTRL_GET_RX_TIMEOUT:
        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
        }
        else
        {
            if (serial->config.rx_bufsz == 0)
            {
                ret = -RT_EPERM;
            }

            struct rt_serial_rx_fifo *rx_fifo = RT_NULL;
            rx_fifo                           = (struct rt_serial_rx_fifo *)serial->serial_rx;
            RT_ASSERT(rx_fifo != RT_NULL);

            *(rt_int32_t *)args = rt_atomic_load(&rx_fifo->rx_timeout);
        }
        break;

    case RT_SERIAL_CTRL_GET_TX_TIMEOUT:
        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
        }
        else
        {
            if (serial->config.tx_bufsz == 0)
            {
                ret = -RT_EPERM;
            }

            struct rt_serial_tx_fifo *tx_fifo = RT_NULL;
            tx_fifo                           = (struct rt_serial_tx_fifo *)serial->serial_tx;
            RT_ASSERT(tx_fifo != RT_NULL);

            *(rt_int32_t *)args = rt_atomic_load(&tx_fifo->tx_timeout);
        }
        break;

    /* Discard all data */
    case RT_SERIAL_CTRL_RX_FLUSH:
        _serial_rx_flush(serial);
        break;

    /* Blocking and wait for the send buffer data to be sent. */
    case RT_SERIAL_CTRL_TX_FLUSH:
        _serial_tx_flush(serial);
        break;

    /* get unread bytes count. */
    case RT_SERIAL_CTRL_GET_UNREAD_BYTES_COUNT:
        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
        }
        else
        {
            ret = _serial_get_unread_bytes_count(serial, (rt_ssize_t *)args);
        }
        break;

#ifdef RT_USING_POSIX_STDIO
#ifdef RT_USING_POSIX_TERMIOS
    case TCGETA: {
        struct termios *tio = (struct termios *)args;
        if (tio == RT_NULL) return -RT_EINVAL;

        tio->c_iflag = 0;
        tio->c_oflag = 0;
        tio->c_lflag = 0;

        /* update oflag for console device */
        if (rt_console_get_device() == dev)
            tio->c_oflag = OPOST | ONLCR;

        /* set cflag */
        tio->c_cflag = 0;
        if (serial->config.data_bits == DATA_BITS_5)
            tio->c_cflag = CS5;
        else if (serial->config.data_bits == DATA_BITS_6)
            tio->c_cflag = CS6;
        else if (serial->config.data_bits == DATA_BITS_7)
            tio->c_cflag = CS7;
        else if (serial->config.data_bits == DATA_BITS_8)
            tio->c_cflag = CS8;

        if (serial->config.stop_bits == STOP_BITS_2)
            tio->c_cflag |= CSTOPB;

        if (serial->config.parity == PARITY_EVEN)
            tio->c_cflag |= PARENB;
        else if (serial->config.parity == PARITY_ODD)
            tio->c_cflag |= (PARODD | PARENB);

        if (serial->config.flowcontrol == RT_SERIAL_FLOWCONTROL_CTSRTS)
            tio->c_cflag |= CRTSCTS;

        cfsetospeed(tio, _get_speed(serial->config.baud_rate));
    }
    break;

    case TCSETAW:
    case TCSETAF:
    case TCSETA: {
        int                     baudrate;
        struct serial_configure config;

        struct termios *tio = (struct termios *)args;
        if (tio == RT_NULL) return -RT_EINVAL;

        config = serial->config;

        baudrate         = _get_baudrate(cfgetospeed(tio));
        config.baud_rate = baudrate;

        switch (tio->c_cflag & CSIZE)
        {
        case CS5:
            config.data_bits = DATA_BITS_5;
            break;
        case CS6:
            config.data_bits = DATA_BITS_6;
            break;
        case CS7:
            config.data_bits = DATA_BITS_7;
            break;
        default:
            config.data_bits = DATA_BITS_8;
            break;
        }

        if (tio->c_cflag & CSTOPB)
            config.stop_bits = STOP_BITS_2;
        else
            config.stop_bits = STOP_BITS_1;

        if (tio->c_cflag & PARENB)
        {
            if (tio->c_cflag & PARODD)
                config.parity = PARITY_ODD;
            else
                config.parity = PARITY_EVEN;
        }
        else
            config.parity = PARITY_NONE;

        if (tio->c_cflag & CRTSCTS)
            config.flowcontrol = RT_SERIAL_FLOWCONTROL_CTSRTS;
        else
            config.flowcontrol = RT_SERIAL_FLOWCONTROL_NONE;

        /* set serial configure */
        serial->config = config;
        serial->ops->configure(serial, &config);
    }
    break;
    case TCFLSH: {
        int queue = (int)args;

        _tc_flush(serial, queue);
    }

    break;
    case TCXONC:
        break;
#endif /*RT_USING_POSIX_TERMIOS*/
    case TIOCSWINSZ: {
        struct winsize *p_winsize;

        p_winsize = (struct winsize *)args;
        rt_kprintf("\x1b[8;%d;%dt", p_winsize->ws_col, p_winsize->ws_row);
    }
    break;
    case TIOCGWINSZ: {
        struct winsize *p_winsize;
        p_winsize = (struct winsize *)args;

        if (rt_thread_self() != rt_thread_find(FINSH_THREAD_NAME))
        {
            /* only can be used in tshell thread; otherwise, return default size */
            p_winsize->ws_col = 80;
            p_winsize->ws_row = 24;
        }
        else
        {
#include <shell.h>
#define _TIO_BUFLEN 20
            char          _tio_buf[_TIO_BUFLEN];
            unsigned char cnt1, cnt2, cnt3, i;
            char          row_s[4], col_s[4];
            char         *p;

            rt_memset(_tio_buf, 0, _TIO_BUFLEN);

            /* send the command to terminal for getting the window size of the terminal */
            rt_kprintf("\033[18t");

            /* waiting for the response from the terminal */
            i = 0;
            while (i < _TIO_BUFLEN)
            {
                _tio_buf[i] = finsh_getchar();
                if (_tio_buf[i] != 't')
                {
                    i++;
                }
                else
                {
                    break;
                }
            }
            if (i == _TIO_BUFLEN)
            {
                /* buffer overloaded, and return default size */
                p_winsize->ws_col = 80;
                p_winsize->ws_row = 24;
                break;
            }

            /* interpreting data eg: "\033[8;1;15t" which means row is 1 and col is 15 (unit: size of ONE character) */
            rt_memset(row_s, 0, 4);
            rt_memset(col_s, 0, 4);
            cnt1 = 0;
            while (cnt1 < _TIO_BUFLEN && _tio_buf[cnt1] != ';')
            {
                cnt1++;
            }
            cnt2 = ++cnt1;
            while (cnt2 < _TIO_BUFLEN && _tio_buf[cnt2] != ';')
            {
                cnt2++;
            }
            p = row_s;
            while (cnt1 < cnt2)
            {
                *p++ = _tio_buf[cnt1++];
            }
            p = col_s;
            cnt2++;
            cnt3 = rt_strlen(_tio_buf) - 1;
            while (cnt2 < cnt3)
            {
                *p++ = _tio_buf[cnt2++];
            }

            /* load the window size date */
            p_winsize->ws_col = atoi(col_s);
            p_winsize->ws_row = atoi(row_s);
#undef _TIO_BUFLEN
        }

        p_winsize->ws_xpixel = 0; /* unused */
        p_winsize->ws_ypixel = 0; /* unused */
    }
    break;
    case FIONREAD:
        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
        }
        else
        {
            rt_ssize_t unread_bytes = 0;
            ret                     = _serial_get_unread_bytes_count(serial, &unread_bytes);
            if (ret == RT_EOK)
                *(rt_size_t *)args = (rt_size_t)unread_bytes;
            else
                *(rt_size_t *)args = 0;
        }
        break;
#endif /* RT_USING_POSIX_STDIO */
    default:
        /* control device */
        ret = serial->ops->control(serial, cmd, args);
        break;
    }

    return ret;
}

#ifdef RT_USING_DEVICE_OPS
static rt_ssize_t rt_serial_read(struct rt_device *dev,
                                 rt_off_t          pos,
                                 void             *buffer,
                                 rt_size_t         size)
{
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);
    if (size == 0) return 0;

    serial = (struct rt_serial_device *)dev;

    if (serial->config.rx_bufsz)
    {
        return _serial_fifo_rx(dev, pos, buffer, size);
    }

    return _serial_poll_rx(dev, pos, buffer, size);
}


static rt_ssize_t rt_serial_write(struct rt_device *dev,
                                  rt_off_t          pos,
                                  const void       *buffer,
                                  rt_size_t         size)
{
    struct rt_serial_device  *serial;
    struct rt_serial_tx_fifo *tx_fifo;

    RT_ASSERT(dev != RT_NULL);
    if (size == 0) return 0;

    serial = (struct rt_serial_device *)dev;
    RT_ASSERT((serial != RT_NULL) && (buffer != RT_NULL));
    tx_fifo = (struct rt_serial_tx_fifo *)serial->serial_tx;

    if (serial->config.tx_bufsz == 0)
    {
        return _serial_poll_tx(dev, pos, buffer, size);
    }

    if (dev->open_flag & RT_SERIAL_TX_BLOCKING)
    {
        RT_ASSERT(tx_fifo != RT_NULL);
        if ((tx_fifo->rb.buffer_ptr) == RT_NULL)
        {
            return _serial_fifo_tx_blocking_nbuf(dev, pos, buffer, size);
        }

        return _serial_fifo_tx_blocking_buf(dev, pos, buffer, size);
    }

    return _serial_fifo_tx_nonblocking(dev, pos, buffer, size);
}

const static struct rt_device_ops serial_ops =
    {
        rt_serial_init,
        rt_serial_open,
        rt_serial_close,
        rt_serial_read,
        rt_serial_write,
        rt_serial_control};
#endif

/**
  * @brief Register the serial device.
  * @param serial RT-thread serial device.
  * @param name The device driver's name
  * @param flag The capabilities flag of device.
  * @param data The device driver's data.
  * @return Return the status of the operation.
  */
rt_err_t rt_hw_serial_register(struct rt_serial_device *serial,
                               const char              *name,
                               rt_uint32_t              flag,
                               void                    *data)
{
    rt_err_t          ret;
    struct rt_device *device;
    RT_ASSERT(serial != RT_NULL);

    rt_spin_lock_init(&serial->spinlock);

    device = &serial->parent;

    device->type        = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops = &serial_ops;
#else
    device->init    = rt_serial_init;
    device->open    = rt_serial_open;
    device->close   = rt_serial_close;
    device->read    = RT_NULL;
    device->write   = RT_NULL;
    device->control = rt_serial_control;
#endif
    device->user_data = data;

    /* register a character device */
    ret = rt_device_register(device, name, flag);

#ifdef RT_USING_POSIX_STDIO
    /* set fops */
    device->fops = &_serial_fops;
#endif
    return ret;
}

/**
  * @brief ISR for serial interrupt
  * @param serial RT-thread serial device.
  * @param event ISR event type.
  */
rt_err_t rt_hw_serial_control_isr(struct rt_serial_device *serial, int cmd, void *args)
{
    RT_ASSERT(serial != RT_NULL);
    rt_err_t ret = RT_EOK;

    switch (cmd)
    {
    case RT_HW_SERIAL_CTRL_PUTC:
        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
        }
        else
        {
            struct rt_serial_rx_fifo *rx_fifo = RT_NULL;
            rx_fifo                           = (struct rt_serial_rx_fifo *)serial->serial_rx;
            RT_ASSERT(rx_fifo != RT_NULL);

#ifdef RT_SERIAL_BUF_STRATEGY_DROP
            rt_ringbuffer_putchar(&rx_fifo->rb, *(rt_uint8_t *)args);
#else
            rt_ringbuffer_putchar_force(&rx_fifo->rb, *(rt_uint8_t *)args);
#endif /* RT_SERIAL_BUF_STRATEGY_DROP */
        }
        break;

    case RT_HW_SERIAL_CTRL_GETC:
        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
        }
        else
        {
            struct rt_serial_tx_fifo *tx_fifo = RT_NULL;
            tx_fifo                           = (struct rt_serial_tx_fifo *)serial->serial_tx;
            RT_ASSERT(tx_fifo != RT_NULL);
            if (rt_ringbuffer_getchar(&tx_fifo->rb, (rt_uint8_t *)args) == 0)
            {
                ret = -RT_EEMPTY;
            }
        }
        break;

#ifdef RT_SERIAL_USING_DMA
    case RT_HW_SERIAL_CTRL_GET_DMA_PING_BUF:
        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
        }
        else
        {
            struct rt_serial_rx_fifo *rx_fifo = RT_NULL;
            rx_fifo                           = (struct rt_serial_rx_fifo *)serial->serial_rx;
            RT_ASSERT(rx_fifo != RT_NULL);
            *(rt_uint8_t **)args = rx_fifo->dma_ping_rb.buffer_ptr;
        }
        break;
#endif

    default:
        ret = -RT_EINVAL;
        break;
    }

    return ret;
}

/**
  * @brief ISR for serial interrupt
  * @param serial RT-thread serial device.
  * @param event ISR event type.
  */
void rt_hw_serial_isr(struct rt_serial_device *serial, int event)
{
    RT_ASSERT(serial != RT_NULL);

    switch (event & 0xff)
    {
    /* Interrupt receive event */
    case RT_SERIAL_EVENT_RX_IND:
    case RT_SERIAL_EVENT_RX_DMADONE: {
        struct rt_serial_rx_fifo *rx_fifo;
        rt_size_t                 rx_length;
        rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
        RT_ASSERT(rx_fifo != RT_NULL);

#ifdef RT_SERIAL_USING_DMA
        rt_base_t level;
        /* If the event is RT_SERIAL_EVENT_RX_IND, rx_length is equal to 0 */
        rx_length = event >> 8;

        /* RT_SERIAL_EVENT_RX_DMADONE MODE */
        if (rx_length != 0)
        {
#ifdef RT_SERIAL_BUF_STRATEGY_DROP
            rt_uint8_t *ptr;
            rt_size_t   size;
            rt_size_t   put_len;
            /* UART_IT_IDLE and dma isr */
            level = rt_spin_lock_irqsave(&serial->spinlock);
            do
            {
                rt_serial_update_write_index(&rx_fifo->dma_ping_rb, rx_length);

                size = rt_ringbuffer_peek(&rx_fifo->dma_ping_rb, &ptr);

                put_len = rt_ringbuffer_put(&rx_fifo->rb, ptr, size);
                if (put_len != size)
                    break;

                size = rt_ringbuffer_peek(&rx_fifo->dma_ping_rb, &ptr);
                if (size == 0)
                    break;

                rt_ringbuffer_put(&rx_fifo->rb, ptr, size);
            } while (0);
            rt_spin_unlock_irqrestore(&serial->spinlock, level);
#else
            rt_uint8_t *ptr;
            rt_size_t   size;
            /* UART_IT_IDLE and dma isr */
            level = rt_spin_lock_irqsave(&serial->spinlock);
            do
            {
                rt_serial_update_write_index(&rx_fifo->dma_ping_rb, rx_length);

                size = rt_ringbuffer_peek(&rx_fifo->dma_ping_rb, &ptr);

                rt_ringbuffer_put_force(&rx_fifo->rb, ptr, size);

                size = rt_ringbuffer_peek(&rx_fifo->dma_ping_rb, &ptr);
                if (size == 0)
                    break;

                rt_ringbuffer_put_force(&rx_fifo->rb, ptr, size);
            } while (0);
            rt_spin_unlock_irqrestore(&serial->spinlock, level);
#endif /* RT_SERIAL_BUF_STRATEGY_DROP */
        }
#endif /* RT_SERIAL_USING_DMA */

        rx_length = rt_ringbuffer_data_len(&rx_fifo->rb);
        if (rx_length == 0)
        {
            break;
        }

        if (serial->parent.open_flag & RT_SERIAL_RX_BLOCKING)
        {
            if (rx_fifo->rx_cpt_index && rx_length >= rx_fifo->rx_cpt_index)
            {
                rx_fifo->rx_cpt_index = 0;
                rt_completion_done(&rx_fifo->rx_cpt);
            }
        }

        /* Trigger the receiving completion callback */
        if (serial->parent.rx_indicate != RT_NULL)
        {
            serial->parent.rx_indicate(&serial->parent, rx_length);
        }

        if (serial->rx_notify.notify != RT_NULL)
        {
            serial->rx_notify.notify(serial->rx_notify.dev);
        }
        break;
    }

    /* Interrupt transmit event */
    case RT_SERIAL_EVENT_TX_DONE: {
        struct rt_serial_tx_fifo *tx_fifo;
        rt_size_t                 tx_length;
        rt_ssize_t                transmit_size;
        tx_fifo = (struct rt_serial_tx_fifo *)serial->serial_tx;
        RT_ASSERT(tx_fifo != RT_NULL);

        /* Get the length of the data from the ringbuffer */
        tx_length = rt_ringbuffer_data_len(&tx_fifo->rb);

        /* If there is no data in tx_ringbuffer,
         * then the transmit completion callback is triggered*/
        if (tx_length == 0)
        {
            rt_completion_done(&tx_fifo->tx_cpt);

            /* Trigger the transmit completion callback */
            if (serial->parent.tx_complete != RT_NULL)
            {
                serial->parent.tx_complete(&serial->parent, RT_NULL);
            }

            rt_atomic_flag_clear(&tx_fifo->activated);
            break;
        }

        rt_atomic_flag_test_and_set(&tx_fifo->activated);
        /* Call the transmit interface for transmission again */
        /* Note that in interrupt mode, tx_fifo->buffer and tx_length
         * are inactive parameters */
        transmit_size = serial->ops->transmit(serial,
                                              tx_fifo->rb.buffer_ptr,
                                              tx_length,
                                              serial->parent.open_flag & (RT_SERIAL_TX_BLOCKING | RT_SERIAL_TX_NON_BLOCKING));
        if (transmit_size <= 0)
        {
            rt_atomic_flag_clear(&tx_fifo->activated);
        }
        break;
    }

#ifdef RT_SERIAL_USING_DMA
    case RT_SERIAL_EVENT_TX_DMADONE: {
        struct rt_serial_tx_fifo *tx_fifo;
        rt_size_t                 tx_length;
        rt_ssize_t                transmit_size;
        tx_fifo = (struct rt_serial_tx_fifo *)serial->serial_tx;
        RT_ASSERT(tx_fifo != RT_NULL);
        /* nonblock */
        if ((serial->parent.open_flag & RT_SERIAL_TX_BLOCKING) != RT_SERIAL_TX_BLOCKING)
        {
            /* Each interruption upon entry indicates that the previous `put_size` has already been sent completely */
            rt_serial_update_read_index(&tx_fifo->rb, tx_fifo->put_size);

            /* Get the length of the data from the ringbuffer */
            tx_length = rt_ringbuffer_data_len(&tx_fifo->rb);

            if (tx_length != 0)
            {
                /* If there is some data in tx_ringbuffer,
                 * then call the transmit interface for transmission again */
                rt_atomic_flag_test_and_set(&tx_fifo->activated);

                rt_uint8_t *put_ptr;
                /* Get the linear length buffer from ringbuffer */
                tx_fifo->put_size = rt_serial_get_linear_buffer(&tx_fifo->rb, &put_ptr);

                /* Call the transmit interface for transmission again */
                transmit_size = serial->ops->transmit(serial,
                                                      put_ptr,
                                                      tx_fifo->put_size,
                                                      RT_SERIAL_TX_NON_BLOCKING);
                if (transmit_size <= 0)
                {
                    rt_atomic_flag_clear(&tx_fifo->activated);
                }
                break;
            }
        }

        rt_completion_done(&tx_fifo->tx_cpt);

        /* Trigger the transmit completion callback */
        if (serial->parent.tx_complete != RT_NULL)
        {
            serial->parent.tx_complete(&serial->parent, RT_NULL);
        }

        rt_atomic_flag_clear(&tx_fifo->activated);
        break;
    }
#endif /* RT_SERIAL_USING_DMA */
    default:
        break;
    }
}
