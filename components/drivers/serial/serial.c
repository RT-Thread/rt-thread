/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-13     bernard      first version
 * 2012-05-15     lgnq         modified according bernard's implementation.
 * 2012-05-28     bernard      code cleanup
 * 2012-11-23     bernard      fix compiler warning.
 * 2013-02-20     bernard      use RT_SERIAL_RB_BUFSZ to define
 *                             the size of ring buffer.
 * 2014-07-10     bernard      rewrite serial framework
 * 2014-12-31     bernard      use open_flag for poll_tx stream mode.
 * 2015-05-19     Quintin      fix DMA tx mod tx_dma->activated flag !=RT_FALSE BUG
 *                             in open function.
 * 2015-11-10     bernard      fix the poll rx issue when there is no data.
 * 2016-05-10     armink       add fifo mode to DMA rx when serial->config.bufsz != 0.
 * 2017-01-19     aubr.cool    prevent change serial rx bufsz when serial is opened.
 * 2017-11-07     JasonJia     fix data bits error issue when using tcsetattr.
 * 2017-11-15     JasonJia     fix poll rx issue when data is full.
 *                             add TCFLSH and FIONREAD support.
 * 2018-12-08     Ernest Chen  add DMA choice
 * 2020-09-14     WillianChan  add a line feed to the carriage return character
 *                             when using interrupt tx
 * 2020-12-14     Meco Man     implement function of setting window's size(TIOCSWINSZ)
 * 2021-08-22     Meco Man     implement function of getting window's size(TIOCGWINSZ)
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG    "UART"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_POSIX_STDIO
#include <dfs_file.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <sys/ioctl.h>

#ifdef RT_USING_POSIX_TERMIOS
#include <termios.h>
#endif

/* it's possible the 'getc/putc' is defined by stdio.h in gcc/newlib. */
#ifdef getc
#undef getc
#endif

#ifdef putc
#undef putc
#endif

static rt_err_t serial_fops_rx_ind(rt_device_t dev, rt_size_t size)
{
    rt_wqueue_wakeup(&(dev->wait_queue), (void*)POLLIN);

    return RT_EOK;
}

/* fops for serial */
static int serial_fops_open(struct dfs_file *fd)
{
    rt_err_t ret = 0;
    rt_uint16_t flags = 0;
    rt_device_t device;

    device = (rt_device_t)fd->vnode->data;
    RT_ASSERT(device != RT_NULL);

    switch (fd->flags & O_ACCMODE)
    {
        case O_RDONLY:
            LOG_D("fops open: O_RDONLY!");
            flags = RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_RDONLY;
            break;
        case O_WRONLY:
            LOG_D("fops open: O_WRONLY!");
            flags = RT_DEVICE_FLAG_WRONLY;
            break;
        case O_RDWR:
            LOG_D("fops open: O_RDWR!");
            flags = RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_RDWR;
            break;
        default:
            LOG_E("fops open: unknown mode - %d!", fd->flags & O_ACCMODE);
            break;
    }

    if ((fd->flags & O_ACCMODE) != O_WRONLY)
        rt_device_set_rx_indicate(device, serial_fops_rx_ind);
    ret = rt_device_open(device, flags);
    if (ret == RT_EOK) return 0;

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
    int flags = (int)(rt_base_t)args;
    int mask  = O_NONBLOCK | O_APPEND;

    device = (rt_device_t)fd->vnode->data;
    switch (cmd)
    {
    case FIONREAD:
        break;
    case FIONWRITE:
        break;
    case F_SETFL:
        flags &= mask;
        fd->flags &= ~mask;
        fd->flags |= flags;
        break;
    }

    return rt_device_control(device, cmd, args);
}

static int serial_fops_read(struct dfs_file *fd, void *buf, size_t count)
{
    int size = 0;
    rt_device_t device;
    int wait_ret;

    device = (rt_device_t)fd->vnode->data;

    do
    {
        size = rt_device_read(device, -1,  buf, count);
        if (size <= 0)
        {
            if (fd->flags & O_NONBLOCK)
            {
                size = -EAGAIN;
                break;
            }

            wait_ret = rt_wqueue_wait_interruptible(&(device->wait_queue), 0, RT_WAITING_FOREVER);
            if (wait_ret != RT_EOK)
            {
                break;
            }
        }
    }while (size <= 0);

    if (size < 0)
    {
        size = 0;
    }
    return size;
}

static int serial_fops_write(struct dfs_file *fd, const void *buf, size_t count)
{
    rt_device_t device;

    device = (rt_device_t)fd->vnode->data;
    return rt_device_write(device, -1, buf, count);
}

static int serial_fops_poll(struct dfs_file *fd, struct rt_pollreq *req)
{
    int mask = 0;
    int flags = 0;
    rt_device_t device;
    struct rt_serial_device *serial;

    device = (rt_device_t)fd->vnode->data;
    RT_ASSERT(device != RT_NULL);

    serial = (struct rt_serial_device *)device;

    /* only support POLLIN */
    flags = fd->flags & O_ACCMODE;
    if (flags == O_RDONLY || flags == O_RDWR)
    {
        rt_base_t level;
        struct rt_serial_rx_fifo* rx_fifo;

        rt_poll_add(&(device->wait_queue), req);

        rx_fifo = (struct rt_serial_rx_fifo*) serial->serial_rx;

        level = rt_hw_interrupt_disable();
        if ((rx_fifo->get_index != rx_fifo->put_index) || (rx_fifo->get_index == rx_fifo->put_index && rx_fifo->is_full == RT_TRUE))
            mask |= POLLIN;
        rt_hw_interrupt_enable(level);
    }

    return mask;
}

static const struct dfs_file_ops _serial_fops =
{
    serial_fops_open,
    serial_fops_close,
    serial_fops_ioctl,
    serial_fops_read,
    serial_fops_write,
    RT_NULL, /* flush */
    RT_NULL, /* lseek */
    RT_NULL, /* getdents */
    serial_fops_poll,
};
#endif /* RT_USING_POSIX_STDIO */

/*
 * Serial poll routines
 */
rt_inline int _serial_poll_rx(struct rt_serial_device *serial, rt_uint8_t *data, int length)
{
    int ch;
    int size;

    RT_ASSERT(serial != RT_NULL);
    size = length;

    while (length)
    {
        ch = serial->ops->getc(serial);
        if (ch == -1) break;

        *data = ch;
        data ++; length --;

        if(serial->parent.open_flag & RT_DEVICE_FLAG_STREAM)
        {
            if (ch == '\n') break;
        }
    }

    return size - length;
}

rt_inline int _serial_poll_tx(struct rt_serial_device *serial, const rt_uint8_t *data, int length)
{
    int size;
    RT_ASSERT(serial != RT_NULL);

    size = length;
    while (length)
    {
        /*
         * to be polite with serial console add a line feed
         * to the carriage return character
         */
        if (*data == '\n' && (serial->parent.open_flag & RT_DEVICE_FLAG_STREAM))
        {
            serial->ops->putc(serial, '\r');
        }

        serial->ops->putc(serial, *data);

        ++ data;
        -- length;
    }

    return size - length;
}

/*
 * Serial interrupt routines
 */
rt_inline int _serial_int_rx(struct rt_serial_device *serial, rt_uint8_t *data, int length)
{
    int size;
    struct rt_serial_rx_fifo* rx_fifo;

    RT_ASSERT(serial != RT_NULL);
    size = length;

    rx_fifo = (struct rt_serial_rx_fifo*) serial->serial_rx;
    RT_ASSERT(rx_fifo != RT_NULL);

    /* read from software FIFO */
    while (length)
    {
        int ch;
        rt_base_t level;

        /* disable interrupt */
        level = rt_hw_interrupt_disable();

        /* there's no data: */
        if ((rx_fifo->get_index == rx_fifo->put_index) && (rx_fifo->is_full == RT_FALSE))
        {
            /* no data, enable interrupt and break out */
            rt_hw_interrupt_enable(level);
            break;
        }

        /* otherwise there's the data: */
        ch = rx_fifo->buffer[rx_fifo->get_index];
        rx_fifo->get_index += 1;
        if (rx_fifo->get_index >= serial->config.bufsz) rx_fifo->get_index = 0;

        if (rx_fifo->is_full == RT_TRUE)
        {
            rx_fifo->is_full = RT_FALSE;
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        *data = ch & 0xff;
        data ++; length --;
    }

    return size - length;
}

rt_inline int _serial_int_tx(struct rt_serial_device *serial, const rt_uint8_t *data, int length)
{
    int size;
    struct rt_serial_tx_fifo *tx;

    RT_ASSERT(serial != RT_NULL);

    size = length;
    tx = (struct rt_serial_tx_fifo*) serial->serial_tx;
    RT_ASSERT(tx != RT_NULL);

    while (length)
    {
        /*
         * to be polite with serial console add a line feed
         * to the carriage return character
         */
        if (*data == '\n' && (serial->parent.open_flag & RT_DEVICE_FLAG_STREAM))
        {
            if (serial->ops->putc(serial, '\r') == -1)
            {
                rt_completion_wait(&(tx->completion), RT_WAITING_FOREVER);
                continue;
            }
        }

        if (serial->ops->putc(serial, *(char*)data) == -1)
        {
            rt_completion_wait(&(tx->completion), RT_WAITING_FOREVER);
            continue;
        }

        data ++; length --;
    }

    return size - length;
}

static void _serial_check_buffer_size(void)
{
    static rt_bool_t already_output = RT_FALSE;

    if (already_output == RT_FALSE)
    {
#if !defined(RT_USING_ULOG) || defined(ULOG_USING_ISR_LOG)
        LOG_W("Warning: There is no enough buffer for saving data,"
              " please increase the RT_SERIAL_RB_BUFSZ option.");
#endif
        already_output = RT_TRUE;
    }
}

#if defined(RT_USING_POSIX_STDIO) || defined(RT_SERIAL_USING_DMA)
static rt_ssize_t _serial_fifo_calc_recved_len(struct rt_serial_device *serial)
{
    struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *) serial->serial_rx;

    RT_ASSERT(rx_fifo != RT_NULL);

    if (rx_fifo->put_index == rx_fifo->get_index)
    {
        return (rx_fifo->is_full == RT_FALSE ? 0 : serial->config.bufsz);
    }
    else
    {
        if (rx_fifo->put_index > rx_fifo->get_index)
        {
            return rx_fifo->put_index - rx_fifo->get_index;
        }
        else
        {
            return serial->config.bufsz - (rx_fifo->get_index - rx_fifo->put_index);
        }
    }
}
#endif /* RT_USING_POSIX_STDIO || RT_SERIAL_USING_DMA */

#ifdef RT_SERIAL_USING_DMA
/**
 * Calculate DMA received data length.
 *
 * @param serial serial device
 *
 * @return length
 */
static rt_ssize_t rt_dma_calc_recved_len(struct rt_serial_device *serial)
{
    return _serial_fifo_calc_recved_len(serial);
}

/**
 * Read data finish by DMA mode then update the get index for receive fifo.
 *
 * @param serial serial device
 * @param len get data length for this operate
 */
static void rt_dma_recv_update_get_index(struct rt_serial_device *serial, rt_size_t len)
{
    struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *) serial->serial_rx;

    RT_ASSERT(rx_fifo != RT_NULL);
    RT_ASSERT(len <= rt_dma_calc_recved_len(serial));

    if (rx_fifo->is_full && len != 0) rx_fifo->is_full = RT_FALSE;

    rx_fifo->get_index += (rt_uint16_t)len;
    if (rx_fifo->get_index >= serial->config.bufsz)
    {
        rx_fifo->get_index %= serial->config.bufsz;
    }
}

/**
 * DMA received finish then update put index for receive fifo.
 *
 * @param serial serial device
 * @param len received length for this transmit
 */
static void rt_dma_recv_update_put_index(struct rt_serial_device *serial, rt_size_t len)
{
    struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

    RT_ASSERT(rx_fifo != RT_NULL);

    if (rx_fifo->get_index <= rx_fifo->put_index)
    {
        rx_fifo->put_index += (rt_uint16_t)len;
        /* beyond the fifo end */
        if (rx_fifo->put_index >= serial->config.bufsz)
        {
            rx_fifo->put_index %= serial->config.bufsz;
            /* force overwrite get index */
            if (rx_fifo->put_index >= rx_fifo->get_index)
            {
                rx_fifo->is_full = RT_TRUE;
            }
        }
    }
    else
    {
        rx_fifo->put_index += (rt_uint16_t)len;
        if (rx_fifo->put_index >= rx_fifo->get_index)
        {
            /* beyond the fifo end */
            if (rx_fifo->put_index >= serial->config.bufsz)
            {
                rx_fifo->put_index %= serial->config.bufsz;
            }
            /* force overwrite get index */
            rx_fifo->is_full = RT_TRUE;
        }
    }

    if(rx_fifo->is_full == RT_TRUE)
    {
        _serial_check_buffer_size();
        rx_fifo->get_index = rx_fifo->put_index;
    }
}

/*
 * Serial DMA routines
 */
rt_inline int _serial_dma_rx(struct rt_serial_device *serial, rt_uint8_t *data, int length)
{
    rt_base_t level;

    RT_ASSERT((serial != RT_NULL) && (data != RT_NULL));

    level = rt_hw_interrupt_disable();

    if (serial->config.bufsz == 0)
    {
        int result = RT_EOK;
        struct rt_serial_rx_dma *rx_dma;

        rx_dma = (struct rt_serial_rx_dma*)serial->serial_rx;
        RT_ASSERT(rx_dma != RT_NULL);

        if (rx_dma->activated != RT_TRUE)
        {
            rx_dma->activated = RT_TRUE;
            RT_ASSERT(serial->ops->dma_transmit != RT_NULL);
            serial->ops->dma_transmit(serial, data, length, RT_SERIAL_DMA_RX);
        }
        else result = -RT_EBUSY;
        rt_hw_interrupt_enable(level);

        if (result == RT_EOK) return length;

        rt_set_errno(result);
        return 0;
    }
    else
    {
        struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *) serial->serial_rx;
        rt_size_t recv_len = 0, fifo_recved_len = rt_dma_calc_recved_len(serial);

        RT_ASSERT(rx_fifo != RT_NULL);

        if (length < (int)fifo_recved_len)
            recv_len = length;
        else
            recv_len = fifo_recved_len;

        if (rx_fifo->get_index + recv_len < serial->config.bufsz)
            rt_memcpy(data, rx_fifo->buffer + rx_fifo->get_index, recv_len);
        else
        {
            rt_memcpy(data, rx_fifo->buffer + rx_fifo->get_index,
                    serial->config.bufsz - rx_fifo->get_index);
            rt_memcpy(data + serial->config.bufsz - rx_fifo->get_index, rx_fifo->buffer,
                    recv_len + rx_fifo->get_index - serial->config.bufsz);
        }
        rt_dma_recv_update_get_index(serial, recv_len);
        rt_hw_interrupt_enable(level);
        return recv_len;
    }
}

rt_inline int _serial_dma_tx(struct rt_serial_device *serial, const rt_uint8_t *data, int length)
{
    rt_base_t level;
    rt_err_t result;
    struct rt_serial_tx_dma *tx_dma;

    tx_dma = (struct rt_serial_tx_dma*)(serial->serial_tx);

    result = rt_data_queue_push(&(tx_dma->data_queue), data, length, RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        level = rt_hw_interrupt_disable();
        if (tx_dma->activated != RT_TRUE)
        {
            tx_dma->activated = RT_TRUE;
            rt_hw_interrupt_enable(level);

            /* make a DMA transfer */
            serial->ops->dma_transmit(serial, (rt_uint8_t *)data, length, RT_SERIAL_DMA_TX);
        }
        else
        {
            rt_hw_interrupt_enable(level);
        }

        return length;
    }
    else
    {
        rt_set_errno(result);
        return 0;
    }
}
#endif /* RT_SERIAL_USING_DMA */

/* RT-Thread Device Interface */
/*
 * This function initializes serial device.
 */
static rt_err_t rt_serial_init(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

    /* initialize rx/tx */
    serial->serial_rx = RT_NULL;
    serial->serial_tx = RT_NULL;

    rt_memset(&serial->rx_notify, 0, sizeof(struct rt_device_notify));

    /* apply configuration */
    if (serial->ops->configure)
        result = serial->ops->configure(serial, &serial->config);

    return result;
}

static rt_err_t rt_serial_open(struct rt_device *dev, rt_uint16_t oflag)
{
    rt_uint16_t stream_flag = 0;
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

    LOG_D("open serial device: 0x%08x with open flag: 0x%04x",
        dev, oflag);
    /* check device flag with the open flag */
    if ((oflag & RT_DEVICE_FLAG_DMA_RX) && !(dev->flag & RT_DEVICE_FLAG_DMA_RX))
        return -RT_EIO;
    if ((oflag & RT_DEVICE_FLAG_DMA_TX) && !(dev->flag & RT_DEVICE_FLAG_DMA_TX))
        return -RT_EIO;
    if ((oflag & RT_DEVICE_FLAG_INT_RX) && !(dev->flag & RT_DEVICE_FLAG_INT_RX))
        return -RT_EIO;
    if ((oflag & RT_DEVICE_FLAG_INT_TX) && !(dev->flag & RT_DEVICE_FLAG_INT_TX))
        return -RT_EIO;

    /* keep steam flag */
    if ((oflag & RT_DEVICE_FLAG_STREAM) || (dev->open_flag & RT_DEVICE_FLAG_STREAM))
        stream_flag = RT_DEVICE_FLAG_STREAM;

    /* get open flags */
    dev->open_flag = oflag & 0xff;

    /* initialize the Rx/Tx structure according to open flag */
    if (serial->serial_rx == RT_NULL)
    {
        if (oflag & RT_DEVICE_FLAG_INT_RX)
        {
            struct rt_serial_rx_fifo* rx_fifo;

            rx_fifo = (struct rt_serial_rx_fifo*) rt_malloc (sizeof(struct rt_serial_rx_fifo) +
                serial->config.bufsz);
            RT_ASSERT(rx_fifo != RT_NULL);
            rx_fifo->buffer = (rt_uint8_t*) (rx_fifo + 1);
            rt_memset(rx_fifo->buffer, 0, serial->config.bufsz);
            rx_fifo->put_index = 0;
            rx_fifo->get_index = 0;
            rx_fifo->is_full = RT_FALSE;

            serial->serial_rx = rx_fifo;
            dev->open_flag |= RT_DEVICE_FLAG_INT_RX;
            /* configure low level device */
            serial->ops->control(serial, RT_DEVICE_CTRL_SET_INT, (void *)RT_DEVICE_FLAG_INT_RX);
        }
#ifdef RT_SERIAL_USING_DMA
        else if (oflag & RT_DEVICE_FLAG_DMA_RX)
        {
            if (serial->config.bufsz == 0) {
                struct rt_serial_rx_dma* rx_dma;

                rx_dma = (struct rt_serial_rx_dma*) rt_malloc (sizeof(struct rt_serial_rx_dma));
                RT_ASSERT(rx_dma != RT_NULL);
                rx_dma->activated = RT_FALSE;

                serial->serial_rx = rx_dma;
            } else {
                struct rt_serial_rx_fifo* rx_fifo;

                rx_fifo = (struct rt_serial_rx_fifo*) rt_malloc (sizeof(struct rt_serial_rx_fifo) +
                    serial->config.bufsz);
                RT_ASSERT(rx_fifo != RT_NULL);
                rx_fifo->buffer = (rt_uint8_t*) (rx_fifo + 1);
                rt_memset(rx_fifo->buffer, 0, serial->config.bufsz);
                rx_fifo->put_index = 0;
                rx_fifo->get_index = 0;
                rx_fifo->is_full = RT_FALSE;
                serial->serial_rx = rx_fifo;
                /* configure fifo address and length to low level device */
                serial->ops->control(serial, RT_DEVICE_CTRL_CONFIG, (void *) RT_DEVICE_FLAG_DMA_RX);
            }
            dev->open_flag |= RT_DEVICE_FLAG_DMA_RX;
        }
#endif /* RT_SERIAL_USING_DMA */
        else
        {
            serial->serial_rx = RT_NULL;
        }
    }
    else
    {
        if (oflag & RT_DEVICE_FLAG_INT_RX)
            dev->open_flag |= RT_DEVICE_FLAG_INT_RX;
#ifdef RT_SERIAL_USING_DMA
        else if (oflag & RT_DEVICE_FLAG_DMA_RX)
            dev->open_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif /* RT_SERIAL_USING_DMA */
    }

    if (serial->serial_tx == RT_NULL)
    {
        if (oflag & RT_DEVICE_FLAG_INT_TX)
        {
            struct rt_serial_tx_fifo *tx_fifo;

            tx_fifo = (struct rt_serial_tx_fifo*) rt_malloc(sizeof(struct rt_serial_tx_fifo));
            RT_ASSERT(tx_fifo != RT_NULL);

            rt_completion_init(&(tx_fifo->completion));
            serial->serial_tx = tx_fifo;

            dev->open_flag |= RT_DEVICE_FLAG_INT_TX;
            /* configure low level device */
            serial->ops->control(serial, RT_DEVICE_CTRL_SET_INT, (void *)RT_DEVICE_FLAG_INT_TX);
        }
#ifdef RT_SERIAL_USING_DMA
        else if (oflag & RT_DEVICE_FLAG_DMA_TX)
        {
            struct rt_serial_tx_dma* tx_dma;

            tx_dma = (struct rt_serial_tx_dma*) rt_malloc (sizeof(struct rt_serial_tx_dma));
            RT_ASSERT(tx_dma != RT_NULL);
            tx_dma->activated = RT_FALSE;

            rt_data_queue_init(&(tx_dma->data_queue), 8, 4, RT_NULL);
            serial->serial_tx = tx_dma;

            dev->open_flag |= RT_DEVICE_FLAG_DMA_TX;
            /* configure low level device */
            serial->ops->control(serial, RT_DEVICE_CTRL_CONFIG, (void *)RT_DEVICE_FLAG_DMA_TX);
        }
#endif /* RT_SERIAL_USING_DMA */
        else
        {
            serial->serial_tx = RT_NULL;
        }
    }
    else
    {
        if (oflag & RT_DEVICE_FLAG_INT_TX)
            dev->open_flag |= RT_DEVICE_FLAG_INT_TX;
#ifdef RT_SERIAL_USING_DMA
        else if (oflag & RT_DEVICE_FLAG_DMA_TX)
            dev->open_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif /* RT_SERIAL_USING_DMA */
    }

    /* set stream flag */
    dev->open_flag |= stream_flag;

    return RT_EOK;
}

static rt_err_t rt_serial_close(struct rt_device *dev)
{
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

    /* this device has more reference count */
    if (dev->ref_count > 1) return RT_EOK;

    if (dev->open_flag & RT_DEVICE_FLAG_INT_RX)
    {
        struct rt_serial_rx_fifo* rx_fifo;

        /* configure low level device */
        serial->ops->control(serial, RT_DEVICE_CTRL_CLR_INT, (void*)RT_DEVICE_FLAG_INT_RX);
        dev->open_flag &= ~RT_DEVICE_FLAG_INT_RX;

        rx_fifo = (struct rt_serial_rx_fifo*)serial->serial_rx;
        RT_ASSERT(rx_fifo != RT_NULL);

        rt_free(rx_fifo);
        serial->serial_rx = RT_NULL;

    }
#ifdef RT_SERIAL_USING_DMA
    else if (dev->open_flag & RT_DEVICE_FLAG_DMA_RX)
    {
        /* configure low level device */
        serial->ops->control(serial, RT_DEVICE_CTRL_CLR_INT, (void *) RT_DEVICE_FLAG_DMA_RX);
        dev->open_flag &= ~RT_DEVICE_FLAG_DMA_RX;

        if (serial->config.bufsz == 0)
        {
            struct rt_serial_rx_dma* rx_dma;

            rx_dma = (struct rt_serial_rx_dma*)serial->serial_rx;
            RT_ASSERT(rx_dma != RT_NULL);

            rt_free(rx_dma);
        }
        else
        {
            struct rt_serial_rx_fifo* rx_fifo;

            rx_fifo = (struct rt_serial_rx_fifo*)serial->serial_rx;
            RT_ASSERT(rx_fifo != RT_NULL);

            rt_free(rx_fifo);
        }
        serial->serial_rx = RT_NULL;

    }
#endif /* RT_SERIAL_USING_DMA */

    if (dev->open_flag & RT_DEVICE_FLAG_INT_TX)
    {
        struct rt_serial_tx_fifo* tx_fifo;

        serial->ops->control(serial, RT_DEVICE_CTRL_CLR_INT, (void*)RT_DEVICE_FLAG_INT_TX);
        dev->open_flag &= ~RT_DEVICE_FLAG_INT_TX;

        tx_fifo = (struct rt_serial_tx_fifo*)serial->serial_tx;
        RT_ASSERT(tx_fifo != RT_NULL);

        rt_free(tx_fifo);
        serial->serial_tx = RT_NULL;

        /* configure low level device */
    }
#ifdef RT_SERIAL_USING_DMA
    else if (dev->open_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        struct rt_serial_tx_dma* tx_dma;

        /* configure low level device */
        serial->ops->control(serial, RT_DEVICE_CTRL_CLR_INT, (void *) RT_DEVICE_FLAG_DMA_TX);
        dev->open_flag &= ~RT_DEVICE_FLAG_DMA_TX;

        tx_dma = (struct rt_serial_tx_dma*)serial->serial_tx;
        RT_ASSERT(tx_dma != RT_NULL);

        rt_data_queue_deinit(&(tx_dma->data_queue));

        rt_free(tx_dma);
        serial->serial_tx = RT_NULL;

    }
#endif /* RT_SERIAL_USING_DMA */

    serial->ops->control(serial, RT_DEVICE_CTRL_CLOSE, RT_NULL);
    dev->flag &= ~RT_DEVICE_FLAG_ACTIVATED;

    return RT_EOK;
}

static rt_ssize_t rt_serial_read(struct rt_device *dev,
                                rt_off_t          pos,
                                void             *buffer,
                                rt_size_t         size)
{
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);
    if (size == 0) return 0;

    serial = (struct rt_serial_device *)dev;

    if (dev->open_flag & RT_DEVICE_FLAG_INT_RX)
    {
        return _serial_int_rx(serial, (rt_uint8_t *)buffer, size);
    }
#ifdef RT_SERIAL_USING_DMA
    else if (dev->open_flag & RT_DEVICE_FLAG_DMA_RX)
    {
        return _serial_dma_rx(serial, (rt_uint8_t *)buffer, size);
    }
#endif /* RT_SERIAL_USING_DMA */

    return _serial_poll_rx(serial, (rt_uint8_t *)buffer, size);
}

static rt_ssize_t rt_serial_write(struct rt_device *dev,
                                 rt_off_t          pos,
                                 const void       *buffer,
                                 rt_size_t         size)
{
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);
    if (size == 0) return 0;

    serial = (struct rt_serial_device *)dev;

    if (dev->open_flag & RT_DEVICE_FLAG_INT_TX)
    {
        return _serial_int_tx(serial, (const rt_uint8_t *)buffer, size);
    }
#ifdef RT_SERIAL_USING_DMA
    else if (dev->open_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        return _serial_dma_tx(serial, (const rt_uint8_t *)buffer, size);
    }
#endif /* RT_SERIAL_USING_DMA */
    else
    {
        return _serial_poll_tx(serial, (const rt_uint8_t *)buffer, size);
    }
}

#if defined(RT_USING_POSIX_TERMIOS) && !defined(RT_USING_TTY)
struct speed_baudrate_item
{
    speed_t speed;
    int baudrate;
};

static const struct speed_baudrate_item _tbl[] =
{
    {B2400, BAUD_RATE_2400},
    {B4800, BAUD_RATE_4800},
    {B9600, BAUD_RATE_9600},
    {B19200, BAUD_RATE_19200},
    {B38400, BAUD_RATE_38400},
    {B57600, BAUD_RATE_57600},
    {B115200, BAUD_RATE_115200},
    {B230400, BAUD_RATE_230400},
    {B460800, BAUD_RATE_460800},
    {B500000, BAUD_RATE_500000},
    {B921600, BAUD_RATE_921600},
    {B2000000, BAUD_RATE_2000000},
    {B3000000, BAUD_RATE_3000000},
};

static speed_t _get_speed(int baudrate)
{
    size_t index;

    for (index = 0; index < sizeof(_tbl)/sizeof(_tbl[0]); index ++)
    {
        if (_tbl[index].baudrate == baudrate)
            return _tbl[index].speed;
    }

    return B0;
}

static int _get_baudrate(speed_t speed)
{
    size_t index;

    for (index = 0; index < sizeof(_tbl)/sizeof(_tbl[0]); index ++)
    {
        if (_tbl[index].speed == speed)
            return _tbl[index].baudrate;
    }

    return 0;
}

static void _tc_flush(struct rt_serial_device *serial, int queue)
{
    rt_base_t level;
    int ch = -1;
    struct rt_serial_rx_fifo *rx_fifo = RT_NULL;
    struct rt_device *device = RT_NULL;

    RT_ASSERT(serial != RT_NULL);

    device = &(serial->parent);
    rx_fifo = (struct rt_serial_rx_fifo *) serial->serial_rx;

    switch(queue)
    {
        case TCIFLUSH:
        case TCIOFLUSH:

            RT_ASSERT(rx_fifo != RT_NULL);

            if((device->open_flag & RT_DEVICE_FLAG_INT_RX) || (device->open_flag & RT_DEVICE_FLAG_DMA_RX))
            {
                RT_ASSERT(RT_NULL != rx_fifo);
                level = rt_hw_interrupt_disable();
                rx_fifo->get_index = rx_fifo->put_index;
                rx_fifo->is_full = RT_FALSE;
                rt_hw_interrupt_enable(level);
            }
            else
            {
                while (1)
                {
                    ch = serial->ops->getc(serial);
                    if (ch == -1) break;
                }
            }

            break;

         case TCOFLUSH:
            break;
    }

}
#endif /* RT_USING_POSIX_TERMIOS */

static rt_err_t rt_serial_control(struct rt_device *dev,
                                  int              cmd,
                                  void             *args)
{
    rt_err_t ret = RT_EOK;
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

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
            if (args)
            {
                struct serial_configure *pconfig = (struct serial_configure *) args;
                if (pconfig->bufsz != serial->config.bufsz && serial->parent.ref_count)
                {
                    /*can not change buffer size*/
                    return -RT_EBUSY;
                }
                /* set serial configure */
                serial->config = *pconfig;
                if (serial->parent.ref_count)
                {
                    /* serial device has been opened, to configure it */
                    serial->ops->configure(serial, (struct serial_configure *) args);
                }
            }
            break;
        case RT_DEVICE_CTRL_NOTIFY_SET:
            if (args)
            {
                rt_memcpy(&serial->rx_notify, args, sizeof(struct rt_device_notify));
            }
            break;

        case RT_DEVICE_CTRL_CONSOLE_OFLAG:
            if (args)
            {
                *(rt_uint16_t*)args = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM;
            }
            break;
#ifdef RT_USING_POSIX_STDIO
#if defined(RT_USING_POSIX_TERMIOS) && !defined(RT_USING_TTY)
        case TCGETA:
            {
                struct termios *tio = (struct termios*)args;
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

                cfsetospeed(tio, _get_speed(serial->config.baud_rate));
            }
            break;

        case TCSETAW:
        case TCSETAF:
        case TCSETA:
            {
                int baudrate;
                struct serial_configure config;

                struct termios *tio = (struct termios*)args;
                if (tio == RT_NULL) return -RT_EINVAL;

                config = serial->config;

                baudrate = _get_baudrate(cfgetospeed(tio));
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

                if (tio->c_cflag & CSTOPB) config.stop_bits = STOP_BITS_2;
                else config.stop_bits = STOP_BITS_1;

                if (tio->c_cflag & PARENB)
                {
                    if (tio->c_cflag & PARODD) config.parity = PARITY_ODD;
                    else config.parity = PARITY_EVEN;
                }
                else config.parity = PARITY_NONE;

                serial->ops->configure(serial, &config);
            }
            break;
        case TCFLSH:
            {
                int queue = (int)(rt_ubase_t)args;

                _tc_flush(serial, queue);
            }

            break;
        case TCXONC:
            break;
#endif /*RT_USING_POSIX_TERMIOS*/
        case TIOCSWINSZ:
            {
                struct winsize* p_winsize;

                p_winsize = (struct winsize*)args;
                rt_kprintf("\x1b[8;%d;%dt", p_winsize->ws_col, p_winsize->ws_row);
            }
            break;
        case TIOCGWINSZ:
            {
                struct winsize* p_winsize;
                p_winsize = (struct winsize*)args;

                if(rt_thread_self() != rt_thread_find("tshell"))
                {
                    /* only can be used in tshell thread; otherwise, return default size */
                    p_winsize->ws_col = 80;
                    p_winsize->ws_row = 24;
                }
                else
                {
                    #include <shell.h>
                    #define _TIO_BUFLEN 20
                    char _tio_buf[_TIO_BUFLEN];
                    unsigned char cnt1, cnt2, cnt3, i;
                    char row_s[4], col_s[4];
                    char *p;

                    rt_memset(_tio_buf, 0, _TIO_BUFLEN);

                    /* send the command to terminal for getting the window size of the terminal */
                    rt_kprintf("\033[18t");

                    /* waiting for the response from the terminal */
                    i = 0;
                    while(i < _TIO_BUFLEN)
                    {
                        _tio_buf[i] = finsh_getchar();
                        if(_tio_buf[i] != 't')
                        {
                            i ++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    if(i == _TIO_BUFLEN)
                    {
                        /* buffer overloaded, and return default size */
                        p_winsize->ws_col = 80;
                        p_winsize->ws_row = 24;
                        break;
                    }

                    /* interpreting data eg: "\033[8;1;15t" which means row is 1 and col is 15 (unit: size of ONE character) */
                    rt_memset(row_s,0,4);
                    rt_memset(col_s,0,4);
                    cnt1 = 0;
                    while(_tio_buf[cnt1] != ';' && cnt1 < _TIO_BUFLEN)
                    {
                        cnt1++;
                    }
                    cnt2 = ++cnt1;
                    while(_tio_buf[cnt2] != ';' && cnt2 < _TIO_BUFLEN)
                    {
                        cnt2++;
                    }
                    p = row_s;
                    while(cnt1 < cnt2)
                    {
                        *p++ = _tio_buf[cnt1++];
                    }
                    p = col_s;
                    cnt2++;
                    cnt3 = rt_strlen(_tio_buf) - 1;
                    while(cnt2 < cnt3)
                    {
                        *p++ = _tio_buf[cnt2++];
                    }

                    /* load the window size date */
                    p_winsize->ws_col = atoi(col_s);
                    p_winsize->ws_row = atoi(row_s);
                #undef _TIO_BUFLEN
                }

                p_winsize->ws_xpixel = 0;/* unused */
                p_winsize->ws_ypixel = 0;/* unused */
            }
            break;
        case FIONREAD:
            {
                rt_size_t recved = 0;
                rt_base_t level;

                level = rt_hw_interrupt_disable();
                recved = _serial_fifo_calc_recved_len(serial);
                rt_hw_interrupt_enable(level);

                *(rt_size_t *)args = recved;
            }
            break;
#endif /* RT_USING_POSIX_STDIO */
        default :
            /* control device */
            ret = serial->ops->control(serial, cmd, args);
            break;
    }

    return ret;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops serial_ops =
{
    rt_serial_init,
    rt_serial_open,
    rt_serial_close,
    rt_serial_read,
    rt_serial_write,
    rt_serial_control
};
#endif

/*
 * serial register
 */
rt_err_t rt_hw_serial_register(struct rt_serial_device *serial,
                               const char              *name,
                               rt_uint32_t              flag,
                               void                    *data)
{
    rt_err_t ret;
    struct rt_device *device;
    RT_ASSERT(serial != RT_NULL);

    device = &(serial->parent);

    device->type        = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &serial_ops;
#else
    device->init        = rt_serial_init;
    device->open        = rt_serial_open;
    device->close       = rt_serial_close;
    device->read        = rt_serial_read;
    device->write       = rt_serial_write;
    device->control     = rt_serial_control;
#endif
    device->user_data   = data;

    /* register a character device */
    ret = rt_device_register(device, name, flag);

#ifdef RT_USING_POSIX_STDIO
    /* set fops */
    device->fops        = &_serial_fops;
#endif

    return ret;
}

/* ISR for serial interrupt */
void rt_hw_serial_isr(struct rt_serial_device *serial, int event)
{
    switch (event & 0xff)
    {
        case RT_SERIAL_EVENT_RX_IND:
        {
            int ch = -1;
            rt_base_t level;
            struct rt_serial_rx_fifo* rx_fifo;

            /* interrupt mode receive */
            rx_fifo = (struct rt_serial_rx_fifo*)serial->serial_rx;
            RT_ASSERT(rx_fifo != RT_NULL);

            while (1)
            {
                ch = serial->ops->getc(serial);
                if (ch == -1) break;


                /* disable interrupt */
                level = rt_hw_interrupt_disable();

                rx_fifo->buffer[rx_fifo->put_index] = ch;
                rx_fifo->put_index += 1;
                if (rx_fifo->put_index >= serial->config.bufsz) rx_fifo->put_index = 0;

                /* if the next position is read index, discard this 'read char' */
                if (rx_fifo->put_index == rx_fifo->get_index)
                {
                    rx_fifo->get_index += 1;
                    rx_fifo->is_full = RT_TRUE;
                    if (rx_fifo->get_index >= serial->config.bufsz) rx_fifo->get_index = 0;

                    _serial_check_buffer_size();
                }

                /* enable interrupt */
                rt_hw_interrupt_enable(level);
            }

            /* invoke callback */
            if (serial->parent.rx_indicate != RT_NULL)
            {
                rt_size_t rx_length;

                /* get rx length */
                level = rt_hw_interrupt_disable();
                rx_length = (rx_fifo->put_index >= rx_fifo->get_index)? (rx_fifo->put_index - rx_fifo->get_index):
                    (serial->config.bufsz - (rx_fifo->get_index - rx_fifo->put_index));
                rt_hw_interrupt_enable(level);

                if (rx_length)
                {
                    serial->parent.rx_indicate(&serial->parent, rx_length);
                }
            }
            if (serial->rx_notify.notify)
            {
                serial->rx_notify.notify(serial->rx_notify.dev);
            }
            break;
        }
        case RT_SERIAL_EVENT_TX_DONE:
        {
            struct rt_serial_tx_fifo* tx_fifo;

            tx_fifo = (struct rt_serial_tx_fifo*)serial->serial_tx;
            rt_completion_done(&(tx_fifo->completion));
            break;
        }
#ifdef RT_SERIAL_USING_DMA
        case RT_SERIAL_EVENT_TX_DMADONE:
        {
            const void *data_ptr;
            rt_size_t data_size;
            const void *last_data_ptr;
            struct rt_serial_tx_dma *tx_dma;

            tx_dma = (struct rt_serial_tx_dma*) serial->serial_tx;

            rt_data_queue_pop(&(tx_dma->data_queue), &last_data_ptr, &data_size, 0);
            if (rt_data_queue_peek(&(tx_dma->data_queue), &data_ptr, &data_size) == RT_EOK)
            {
                /* transmit next data node */
                tx_dma->activated = RT_TRUE;
                serial->ops->dma_transmit(serial, (rt_uint8_t *)data_ptr, data_size, RT_SERIAL_DMA_TX);
            }
            else
            {
                tx_dma->activated = RT_FALSE;
            }

            /* invoke callback */
            if (serial->parent.tx_complete != RT_NULL)
            {
                serial->parent.tx_complete(&serial->parent, (void*)last_data_ptr);
            }
            break;
        }
        case RT_SERIAL_EVENT_RX_DMADONE:
        {
            int length;
            rt_base_t level;

            /* get DMA rx length */
            length = (event & (~0xff)) >> 8;

            if (serial->config.bufsz == 0)
            {
                struct rt_serial_rx_dma* rx_dma;

                rx_dma = (struct rt_serial_rx_dma*) serial->serial_rx;
                RT_ASSERT(rx_dma != RT_NULL);

                RT_ASSERT(serial->parent.rx_indicate != RT_NULL);
                serial->parent.rx_indicate(&(serial->parent), length);
                rx_dma->activated = RT_FALSE;
            }
            else
            {
                /* disable interrupt */
                level = rt_hw_interrupt_disable();
                /* update fifo put index */
                rt_dma_recv_update_put_index(serial, length);
                /* calculate received total length */
                length = rt_dma_calc_recved_len(serial);
                /* enable interrupt */
                rt_hw_interrupt_enable(level);
                /* invoke callback */
                if (serial->parent.rx_indicate != RT_NULL)
                {
                    serial->parent.rx_indicate(&(serial->parent), length);
                }
            }
            break;
        }
#endif /* RT_SERIAL_USING_DMA */
    }
}
