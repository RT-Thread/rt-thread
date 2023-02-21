/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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
 * 2022-04-10     THEWON       serialX first version
 * 2022-06-08     THEWON       add No TX Empty interrupt support
 * 2023-02-15     THEWON       add init ops
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_SERIAL

#define DBG_TAG    "UART"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_POSIX_STDIO
#if RTTHREAD_VERSION <= RT_VERSION_CHECK(4, 0, 3)
#include <dfs_posix.h>
#include <dfs_poll.h>
#else
#include <dfs_file.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#endif

#ifdef RT_USING_POSIX_TERMIOS
#if RTTHREAD_VERSION <= RT_VERSION_CHECK(4, 0, 3)
#include <posix_termios.h>
#else
#include <termios.h>
#endif
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
static int serial_fops_open(struct dfs_fd *fd)
{
    rt_err_t ret = 0;
    rt_uint16_t flags = 0;
    rt_device_t device;

    device = (rt_device_t)fd->data;
    RT_ASSERT(device != RT_NULL);

    switch (fd->flags & O_ACCMODE)
    {
        case O_RDONLY:
            LOG_D("fops open: O_RDONLY!");
            flags = RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_RDONLY;
            break;
        case O_WRONLY:
            LOG_D("fops open: O_WRONLY!");
            flags = RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_WRONLY;
            break;
        case O_RDWR:
            LOG_D("fops open: O_RDWR!");
            flags =  RT_DEVICE_FLAG_RDWR
                   | RT_DEVICE_FLAG_INT_RX
                   | RT_DEVICE_FLAG_INT_TX;
            break;
        default:
            LOG_E("fops open: unknown mode - %d!", fd->flags & O_ACCMODE);
            break;
    }

    if ((fd->flags & O_NONBLOCK) != 0) {
        flags |=  RT_DEVICE_OFLAG_NONBLOCKING;
    }

    ret = rt_device_open(device, flags);
    if (ret == RT_EOK) {
        if ((fd->flags & O_ACCMODE) != O_WRONLY) {
            rt_device_set_rx_indicate(device, serial_fops_rx_ind);
        }
        return 0;
    }

    return ret;
}

static int serial_fops_close(struct dfs_fd *fd)
{
    rt_device_t device;

    device = (rt_device_t)fd->data;

    rt_device_close(device);

    return 0;
}

static int serial_fops_ioctl(struct dfs_fd *fd, int cmd, void *args)
{
    rt_device_t device;

    device = (rt_device_t)fd->data;
    switch (cmd)
    {
    case FIONREAD:
        break;
    case FIONWRITE:
        break;
    }

    return rt_device_control(device, cmd, args);
}

static int serial_fops_read(struct dfs_fd *fd, void *buf, size_t count)
{
    int size = 0;
    int flags = 0;
    rt_device_t device;

    flags = fd->flags & O_ACCMODE;
    if (flags == O_WRONLY) {
        return -EIO;
    }

    device = (rt_device_t)fd->data;

    do
    {
        size = rt_device_read(device, -1, buf, count);
        if (size <= 0)
        {
            if (fd->flags & O_NONBLOCK)
            {
                size = -EAGAIN;
                break;
            }

            rt_wqueue_wait(&(device->wait_queue), 0, RT_WAITING_FOREVER);
        }
    }while (size <= 0);

    return size;
}

static int serial_fops_write(struct dfs_fd *fd, const void *buf, size_t count)
{
    int flags = 0;
    rt_device_t device;

    flags = fd->flags & O_ACCMODE;
    if (flags == O_RDONLY) {
        return -EIO;
    }

    device = (rt_device_t)fd->data;
    return rt_device_write(device, -1, buf, count);
}

static int serial_fops_flush(struct dfs_fd *fd)
{
    rt_device_t device;

    device = (rt_device_t)fd->data;
    return rt_device_flush(device);
}

static int serial_fops_poll(struct dfs_fd *fd, struct rt_pollreq *req)
{
    int mask = 0;
    int flags = 0;
    rt_device_t device;
    struct rt_serial_device *serial;

    device = (rt_device_t)fd->data;
    RT_ASSERT(device != RT_NULL);

    serial = (struct rt_serial_device *)device;

    /* only support POLLIN */
    flags = fd->flags & O_ACCMODE;
    if (flags == O_RDONLY || flags == O_RDWR)
    {
        rt_base_t level;
        struct rt_serial_fifo* rx_fifo;

        rt_poll_add(&(device->wait_queue), req);

        rx_fifo = (struct rt_serial_fifo*) serial->serial_rx;

        level = rt_hw_interrupt_disable();
        if ((rx_fifo->get_index != rx_fifo->put_index) || (rx_fifo->get_index == rx_fifo->put_index && rx_fifo->is_full == RT_TRUE))
        {
            mask |= POLLIN;
        }
        rt_hw_interrupt_enable(level);
    }

    return mask;
}

const static struct dfs_file_ops _serial_fops =
{
    serial_fops_open,
    serial_fops_close,
    serial_fops_ioctl,
    serial_fops_read,
    serial_fops_write,
    serial_fops_flush, /* flush */
    RT_NULL, /* lseek */
    RT_NULL, /* getdents */
    serial_fops_poll,
};
#endif

/**
 * Calculate fifo data length.
 *
 * @param fifo the data fifo of serial device
 *
 * @return length
 */
rt_inline rt_ssize_t _serial_fifo_calc_data_len(struct rt_serial_fifo *fifo)
{
    rt_ssize_t size;
    if (fifo->put_index == fifo->get_index) {
        size = (fifo->is_full == RT_FALSE) ? 0 : fifo->buf_sz;
    } else if (fifo->put_index > fifo->get_index) {
        size = fifo->put_index - fifo->get_index;
    } else {
        size = fifo->buf_sz - (fifo->get_index - fifo->put_index);
    }

    return size;
}

rt_inline void _serial_fifo_push_data(struct rt_serial_fifo *fifo, rt_uint8_t ch)
{
    fifo->buffer[fifo->put_index] = ch;
    fifo->put_index += 1;
    if (fifo->put_index >= fifo->buf_sz) fifo->put_index = 0;
}

rt_inline rt_uint8_t _serial_fifo_pop_data(struct rt_serial_fifo *fifo)
{
    rt_uint8_t ch;

    ch = fifo->buffer[fifo->get_index];
    fifo->get_index += 1;
    if (fifo->get_index >= fifo->buf_sz) fifo->get_index = 0;

    return ch;
}

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
        data++; length--;
    }

    return size - length;
}

rt_inline int _serial_poll_tx(struct rt_serial_device *serial, const rt_uint8_t *data, int length)
{
    int size;
    rt_uint8_t last_char = 0;

    RT_ASSERT(serial != RT_NULL);

    size = length;
    while (length)
    {
        /*
         * to be polite with serial console add a line feed
         * to the carriage return character
         */
        if (*data == '\n' &&
            (serial->parent.open_flag & RT_DEVICE_FLAG_STREAM) == RT_DEVICE_FLAG_STREAM &&
            last_char != '\r')
        {
            serial->ops->putc(serial, '\r');

            last_char = 0;
        } else if (*data == '\r') {
            last_char = '\r';
        } else {
            last_char = 0;
        }

        serial->ops->putc(serial, *data);

        data++; length--;
    }

    return size - length;
}

/*
 * Serial interrupt routines
 */
rt_inline int _serial_fifo_rx(struct rt_serial_device *serial, rt_uint8_t *data, int length)
{
    rt_size_t len, size;
    struct rt_serial_fifo* rx_fifo;
    rt_base_t level;

    RT_ASSERT(serial != RT_NULL);

    if (length == 0) return 0;

    rx_fifo = (struct rt_serial_fifo*) serial->serial_rx;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();
//    serial->ops->disable_interrupt(serial);

    len = _serial_fifo_calc_data_len(rx_fifo);

    if ((len == 0) &&                // non-blocking io mode
        (serial->parent.open_flag & RT_DEVICE_OFLAG_NONBLOCKING) == RT_DEVICE_OFLAG_NONBLOCKING) {
        /* enable interrupt */
        rt_hw_interrupt_enable(level);
//        serial->ops->enable_interrupt(serial);
        return 0;
    }
    if ((len == 0) &&                // blocking io mode
        (serial->parent.open_flag & RT_DEVICE_OFLAG_NONBLOCKING) != RT_DEVICE_OFLAG_NONBLOCKING) {
        rt_err_t ret;
        do {
            /* enable interrupt */
            rt_hw_interrupt_enable(level);
//            serial->ops->enable_interrupt(serial);

#ifndef RT_SERIAL_USE_EVENT
            ret = rt_completion_wait(&(serial->completion_rx), RT_WAITING_FOREVER);
#else
            ret = rt_event_recv(serial->rx_done, RT_SERIAL_EVENT_RXDONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, RT_NULL);
#endif
            if (ret == RT_EOK || ret == -RT_ETIMEOUT) {
            } else {
                return 0;
            }

            /* disable interrupt */
            level = rt_hw_interrupt_disable();
//            serial->ops->disable_interrupt(serial);

            len = _serial_fifo_calc_data_len(rx_fifo);
        } while(len == 0);
    }

    if (len > length) {
        len = length;
    }

    /* read from software FIFO */
    for (size = 0; size < len; size++) {
        /* otherwise there's the data: */
        *data = _serial_fifo_pop_data(rx_fifo);
        data++;
    }

    rx_fifo->is_full = RT_FALSE;

    /* enable interrupt */
    rt_hw_interrupt_enable(level);
//    serial->ops->enable_interrupt(serial);

    return size;
}

rt_inline int _serial_int_tx(struct rt_serial_device *serial, const rt_uint8_t *data, int length)
{
    rt_size_t len, length_t, size;
    struct rt_serial_fifo *tx_fifo;
    rt_base_t level;
    rt_uint8_t ch = 0;
    static rt_uint8_t last_char = 0;

    RT_ASSERT(serial != RT_NULL);

    if (length == 0) return 0;

    tx_fifo = (struct rt_serial_fifo*) serial->serial_tx;

    size = 0;
    do {
        length_t = length - size;
        /* disable interrupt */
        level = rt_hw_interrupt_disable();
//        serial->ops->disable_interrupt(serial);

        len = tx_fifo->buf_sz - _serial_fifo_calc_data_len(tx_fifo);

        if ((len == 0) &&                // non-blocking io mode
            (serial->parent.open_flag & RT_DEVICE_OFLAG_NONBLOCKING) == RT_DEVICE_OFLAG_NONBLOCKING) {
            /* enable interrupt */
            rt_hw_interrupt_enable(level);
//            serial->ops->enable_interrupt(serial);
            break;
        }

        if ((len == 0) &&                // blocking io mode
            (serial->parent.open_flag & RT_DEVICE_OFLAG_NONBLOCKING) != RT_DEVICE_OFLAG_NONBLOCKING) {
            rt_err_t ret;
            /* enable interrupt */
            rt_hw_interrupt_enable(level);
//            serial->ops->enable_interrupt(serial);
#ifndef RT_SERIAL_USE_EVENT
            ret = rt_completion_wait(&(serial->completion_tx), RT_WAITING_FOREVER);
#else
            ret = rt_event_recv(serial->tx_done, RT_SERIAL_EVENT_TXDONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, RT_NULL);
#endif
            if (ret == RT_EOK || ret == -RT_ETIMEOUT) {
                continue;
            } else {
                return size;
            }
        }

        if (len > length_t) {
            len = length_t;
        }
        /* copy to software FIFO */
        while (len > 0) {
            /*
             * to be polite with serial console add a line feed
             * to the carriage return character
             */
            if (*data == '\n' &&
                (serial->parent.open_flag & RT_DEVICE_FLAG_STREAM) == RT_DEVICE_FLAG_STREAM &&
                last_char != '\r') {
                _serial_fifo_push_data(tx_fifo, '\r');

                last_char = '\r';
                if (len == 1) {
                    break;
                } else {
                    len--;
                }
            } else if (*data == '\r') {
                last_char = '\r';
            } else {
                last_char = 0;
            }

            _serial_fifo_push_data(tx_fifo, *data);

            data++; len--; size++;
        }

        /* if the next position is read index, discard this 'read char' */
        if (tx_fifo->put_index == tx_fifo->get_index) {
            tx_fifo->is_full = RT_TRUE;
        }

        // TODO: start tx
#if defined (RT_SERIAL_NO_TXEIT)
        if (serial->ops->is_int_txing != RT_NULL && serial->ops->is_int_txing(serial) == RT_FALSE) {
            ch = _serial_fifo_pop_data(tx_fifo);
            serial->ops->start_tx(serial, ch);
        }
#else
        serial->ops->start_tx(serial);
#endif

        /* enable interrupt */
        rt_hw_interrupt_enable(level);
//        serial->ops->enable_interrupt(serial);
    } while(size < length);

    return size;
}

#ifdef RT_SERIAL_USING_DMA
/*
 * Serial DMA routines
 */
rt_inline int _serial_dma_tx(struct rt_serial_device *serial, const rt_uint8_t *data, int length)
{
    rt_size_t len, length_t, size, i;
    struct rt_serial_fifo *tx_fifo;
    rt_base_t level;
    rt_uint8_t ch;
    static rt_uint8_t last_char = 0;

    RT_ASSERT(serial != RT_NULL);

    if (length == 0) return 0;

    tx_fifo = (struct rt_serial_fifo*) serial->serial_tx;

    size = 0;
    do {
        length_t = length - size;
        /* disable interrupt */
        level = rt_hw_interrupt_disable();
//        serial->ops->disable_interrupt(serial);

        len = tx_fifo->buf_sz - _serial_fifo_calc_data_len(tx_fifo);

        if ((len == 0) &&                // non-blocking io mode
            (serial->parent.open_flag & RT_DEVICE_OFLAG_NONBLOCKING) == RT_DEVICE_OFLAG_NONBLOCKING) {
            /* enable interrupt */
            rt_hw_interrupt_enable(level);
//            serial->ops->enable_interrupt(serial);
            break;
        }

        if ((len == 0) &&                // blocking io mode
            (serial->parent.open_flag & RT_DEVICE_OFLAG_NONBLOCKING) != RT_DEVICE_OFLAG_NONBLOCKING) {
            rt_err_t ret;
            /* enable interrupt */
            rt_hw_interrupt_enable(level);
//            serial->ops->enable_interrupt(serial);

#ifndef RT_SERIAL_USE_EVENT
            ret = rt_completion_wait(&(serial->completion_tx), RT_WAITING_FOREVER);
#else
            ret = rt_event_recv(serial->tx_done, RT_SERIAL_EVENT_TXDONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, RT_NULL);
#endif
            if (ret == RT_EOK || ret == -RT_ETIMEOUT) {
                continue;
            } else {
                return size;
            }
        }

        if (len > length_t) {
            len = length_t;
        }
        /* copy to software FIFO */
        while (len > 0) {
            /*
             * to be polite with serial console add a line feed
             * to the carriage return character
             */
            if (*data == '\n' &&
                (serial->parent.open_flag & RT_DEVICE_FLAG_STREAM) == RT_DEVICE_FLAG_STREAM &&
                last_char != '\r') {
                _serial_fifo_push_data(tx_fifo, '\r');

                last_char = '\r';
                if (len == 1) {
                    break;
                } else {
                    len--;
                }
            } else if (*data == '\r') {
                last_char = '\r';
            } else {
                last_char = 0;
            }

            _serial_fifo_push_data(tx_fifo, *data);

            data++; len--; size++;
        }

        /* if the next position is read index, discard this 'read char' */
        if (tx_fifo->put_index == tx_fifo->get_index) {
            tx_fifo->is_full = RT_TRUE;
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);
//        serial->ops->enable_interrupt(serial);

        // TODO: start tx
            /* disable interrupt */
            level = rt_hw_interrupt_disable();
//            serial->ops->disable_interrupt(serial);
        if (serial->ops->is_dma_txing(serial) == RT_FALSE) {
            /* calucate fifo data size */
            len = _serial_fifo_calc_data_len(tx_fifo);

            if (len > RT_SERIAL_DMA_BUFSZ) {
                len = RT_SERIAL_DMA_BUFSZ;
            }
            /* read from software FIFO */
            for (i = 0; i < len; i++) {
                /* pop one byte data */
                ch = _serial_fifo_pop_data(tx_fifo);

                serial->serial_dma_tx[i] = ch;
            }
            tx_fifo->is_full = RT_FALSE;
            serial->ops->start_dma_tx(serial, serial->serial_dma_tx, len);

        }
            /* enable interrupt */
            rt_hw_interrupt_enable(level);
//            serial->ops->enable_interrupt(serial);
    } while(size < length);

    return size;
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

    /* initialize hardware */
    if (serial->ops->init)
        result = serial->ops->init(serial);

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

    if (oflag & RT_DEVICE_FLAG_INT_RX)
    {
        /* initialize the Rx/Tx structure according to open flag */
        if (serial->serial_rx == RT_NULL)
        {
            struct rt_serial_fifo* rx_fifo;

            rx_fifo = (struct rt_serial_fifo*)rt_malloc(sizeof(struct rt_serial_fifo) +
                                                            serial->bufsz);
            RT_ASSERT(rx_fifo != RT_NULL);
            rx_fifo->buf_sz = serial->bufsz;
            rx_fifo->buffer = (rt_uint8_t*) (rx_fifo + 1);
            rt_memset(rx_fifo->buffer, 0, rx_fifo->buf_sz);
            rx_fifo->put_index = 0;
            rx_fifo->get_index = 0;
            rx_fifo->is_full = RT_FALSE;

            serial->serial_rx = rx_fifo;
        }
        dev->open_flag |= RT_DEVICE_FLAG_INT_RX;

        serial->_cb_rx = _serial_fifo_rx;
#ifndef RT_SERIAL_USE_EVENT
        rt_completion_init(&(serial->completion_rx));
#else
        serial->rx_done = rt_event_create("rx_done", RT_IPC_FLAG_PRIO);
#endif
        /* configure low level device */
        serial->ops->control(serial, RT_DEVICE_CTRL_SET_INT, (void *)RT_DEVICE_FLAG_INT_RX);
    }
#ifdef RT_SERIAL_USING_DMA
    else if (oflag & RT_DEVICE_FLAG_DMA_RX)
    {
        /* initialize the Rx/Tx structure according to open flag */
        if (serial->serial_rx == RT_NULL)
        {
            struct rt_serial_fifo* rx_fifo;

            rx_fifo = (struct rt_serial_fifo*)rt_malloc(sizeof(struct rt_serial_fifo) +
                                                            serial->bufsz);
            RT_ASSERT(rx_fifo != RT_NULL);
            rx_fifo->buf_sz = serial->bufsz;
            rx_fifo->buffer = (rt_uint8_t*) (rx_fifo + 1);
            rt_memset(rx_fifo->buffer, 0, rx_fifo->buf_sz);
            rx_fifo->put_index = 0;
            rx_fifo->get_index = 0;
            rx_fifo->is_full = RT_FALSE;

            serial->serial_rx = rx_fifo;
        }
        dev->open_flag |= RT_DEVICE_FLAG_DMA_RX;

        serial->dma_idx_rx = 0;
        serial->_cb_rx = _serial_fifo_rx;

#ifndef RT_SERIAL_USE_EVENT
        rt_completion_init(&(serial->completion_rx));
#else
        serial->rx_done = rt_event_create("rx_done", RT_IPC_FLAG_PRIO);
#endif
        /* configure fifo address and length to low level device */
        serial->ops->control(serial, RT_DEVICE_CTRL_CONFIG, (void *) RT_DEVICE_FLAG_DMA_RX);
    }
#endif /* RT_SERIAL_USING_DMA */
    else
    {
        serial->serial_rx = RT_NULL;
        serial->_cb_rx = _serial_poll_rx;
    }

    if (oflag & RT_DEVICE_FLAG_INT_TX)
    {
        if (serial->serial_tx == RT_NULL)
        {
            struct rt_serial_fifo *tx_fifo;

            tx_fifo = (struct rt_serial_fifo*)rt_malloc(sizeof(struct rt_serial_fifo) +
                                                            serial->bufsz);
            RT_ASSERT(tx_fifo != RT_NULL);
            tx_fifo->buf_sz = serial->bufsz;
            tx_fifo->buffer = (rt_uint8_t*) (tx_fifo + 1);
            rt_memset(tx_fifo->buffer, 0, tx_fifo->buf_sz);
            tx_fifo->put_index = 0;
            tx_fifo->get_index = 0;
            tx_fifo->is_full = RT_FALSE;
#ifndef RT_SERIAL_USE_EVENT
            rt_completion_init(&(serial->completion_tx));
#else
            serial->tx_done = rt_event_create("tx_done", RT_IPC_FLAG_PRIO);
#endif
            serial->serial_tx = tx_fifo;
        }
        dev->open_flag |= RT_DEVICE_FLAG_INT_TX;
        /* configure low level device */
//        serial->ops->control(serial, RT_DEVICE_CTRL_SET_INT, (void *)RT_DEVICE_FLAG_INT_TX);

        serial->_cb_tx = _serial_int_tx;
    }
#ifdef RT_SERIAL_USING_DMA
    else if (oflag & RT_DEVICE_FLAG_DMA_TX)
    {
        if (serial->serial_tx == RT_NULL)
        {
            struct rt_serial_fifo *tx_fifo;

            tx_fifo = (struct rt_serial_fifo*)rt_malloc(sizeof(struct rt_serial_fifo) +
                                                            serial->bufsz);
            RT_ASSERT(tx_fifo != RT_NULL);
            tx_fifo->buf_sz = serial->bufsz;
            tx_fifo->buffer = (rt_uint8_t*) (tx_fifo + 1);
            rt_memset(tx_fifo->buffer, 0, tx_fifo->buf_sz);
            tx_fifo->put_index = 0;
            tx_fifo->get_index = 0;
            tx_fifo->is_full = RT_FALSE;

#ifndef RT_SERIAL_USE_EVENT
            rt_completion_init(&(serial->completion_tx));
#else
            serial->tx_done = rt_event_create("tx_done", RT_IPC_FLAG_PRIO);
#endif

            serial->serial_tx = tx_fifo;
        }
        dev->open_flag |= RT_DEVICE_FLAG_DMA_TX;

        serial->_cb_tx = _serial_dma_tx;
        /* configure low level device */
        serial->ops->control(serial, RT_DEVICE_CTRL_CONFIG, (void *)RT_DEVICE_FLAG_DMA_TX);
    }
#endif /* RT_SERIAL_USING_DMA */
    else
    {
        serial->serial_tx = RT_NULL;
        serial->_cb_tx = _serial_poll_tx;
    }

    serial->ops->control(serial, RT_DEVICE_CTRL_OPEN, (void *)0);

    /* set stream flag */
    dev->open_flag |= stream_flag;

    return RT_EOK;
}

static rt_err_t rt_serial_close(struct rt_device *dev)
{
    struct rt_serial_device *serial;

    RT_ASSERT(dev != RT_NULL);
    serial = (struct rt_serial_device *)dev;

    serial->ops->control(serial, RT_DEVICE_CTRL_CLOSE, RT_NULL);

    if (dev->open_flag & RT_DEVICE_FLAG_INT_RX)
    {
        struct rt_serial_fifo *rx_fifo;

        /* configure low level device */
        serial->ops->control(serial, RT_DEVICE_CTRL_CLR_INT, (void *)RT_DEVICE_FLAG_INT_RX);

        dev->open_flag &= ~RT_DEVICE_FLAG_INT_RX;

        rx_fifo = (struct rt_serial_fifo *)serial->serial_rx;
        rt_free(rx_fifo);

        serial->serial_rx = RT_NULL;
#ifndef RT_SERIAL_USE_EVENT
        rt_completion_init(&(serial->completion_rx));
#else
        rt_event_delete(serial->rx_done);
#endif
    }
#ifdef RT_SERIAL_USING_DMA
    else if (dev->open_flag & RT_DEVICE_FLAG_DMA_RX)
    {
        struct rt_serial_fifo *rx_fifo;

        /* configure low level device */
        serial->ops->control(serial, RT_DEVICE_CTRL_CLR_INT, (void *) RT_DEVICE_FLAG_DMA_RX);

        dev->open_flag &= ~RT_DEVICE_FLAG_DMA_RX;

        rx_fifo = (struct rt_serial_fifo *)serial->serial_rx;
        rt_free(rx_fifo);

        serial->serial_rx = RT_NULL;
#ifndef RT_SERIAL_USE_EVENT
        rt_completion_init(&(serial->completion_rx));
#else
        rt_event_delete(serial->rx_done);
#endif
    }
#endif /* RT_SERIAL_USING_DMA */

    if (dev->open_flag & RT_DEVICE_FLAG_INT_TX)
    {
        struct rt_serial_fifo *tx_fifo;

        /* configure low level device */
        serial->ops->control(serial, RT_DEVICE_CTRL_CLR_INT, (void *)RT_DEVICE_FLAG_INT_TX);

        dev->open_flag &= ~RT_DEVICE_FLAG_INT_TX;

        tx_fifo = (struct rt_serial_fifo *)serial->serial_tx;
        rt_free(tx_fifo);

        serial->serial_tx = RT_NULL;
#ifndef RT_SERIAL_USE_EVENT
        rt_completion_init(&(serial->completion_tx));
#else
        rt_event_delete(serial->tx_done);
#endif
    }
#ifdef RT_SERIAL_USING_DMA
    else if (dev->open_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        struct rt_serial_fifo *tx_fifo;

        /* configure low level device */
        serial->ops->control(serial, RT_DEVICE_CTRL_CLR_INT, (void *) RT_DEVICE_FLAG_DMA_TX);

        dev->open_flag &= ~RT_DEVICE_FLAG_DMA_TX;

        tx_fifo = (struct rt_serial_fifo *)serial->serial_tx;
        rt_free(tx_fifo);

        serial->serial_tx = RT_NULL;
#ifndef RT_SERIAL_USE_EVENT
        rt_completion_init(&(serial->completion_tx));
#else
        rt_event_delete(serial->tx_done);
#endif
    }
#endif /* RT_SERIAL_USING_DMA */

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

    return serial->_cb_rx(serial, (rt_uint8_t *)buffer, size);
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

    return serial->_cb_tx(serial, (const rt_uint8_t *)buffer, size);
}

static rt_err_t rt_serial_flush(struct rt_device *dev)
{
    struct rt_serial_device *serial;
    rt_size_t len;
    struct rt_serial_fifo *tx_fifo, *rx_fifo;
    rt_base_t level;

    RT_ASSERT(dev != RT_NULL);

    serial = (struct rt_serial_device *)dev;

    if((dev->open_flag & RT_DEVICE_FLAG_INT_RX)
#ifdef RT_SERIAL_USING_DMA
        || (dev->open_flag & RT_DEVICE_FLAG_DMA_RX)
#endif /* RT_SERIAL_USING_DMA */
        ) {
        rx_fifo = (struct rt_serial_fifo*) serial->serial_rx;
        level = rt_hw_interrupt_disable();
        rx_fifo->get_index = rx_fifo->put_index = 0;
        rx_fifo->is_full = RT_FALSE;
        rt_hw_interrupt_enable(level);
    }

    if ((dev->open_flag & RT_DEVICE_FLAG_INT_TX)
#ifdef RT_SERIAL_USING_DMA
     || (dev->open_flag & RT_DEVICE_FLAG_DMA_TX)
#endif /* RT_SERIAL_USING_DMA */
    ) {
        tx_fifo = (struct rt_serial_fifo*) serial->serial_tx;

        while(1) {
            /* disable interrupt */
            level = rt_hw_interrupt_disable();
    //        serial->ops->disable_interrupt(serial);

            len = _serial_fifo_calc_data_len(tx_fifo);

            if (len == 0) {
                /* enable interrupt */
                rt_hw_interrupt_enable(level);
    //            serial->ops->enable_interrupt(serial);
                break;
            } else {
                /* enable interrupt */
                rt_hw_interrupt_enable(level);
    //            serial->ops->enable_interrupt(serial);
#ifndef RT_SERIAL_USE_EVENT
                rt_completion_wait(&(serial->completion_tx), RT_WAITING_FOREVER);
#else
                rt_event_recv(serial->tx_done, RT_SERIAL_EVENT_TXDONE, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, RT_NULL);
#endif
            }
        }

    if (dev->open_flag & RT_DEVICE_FLAG_INT_TX) {
        serial->ops->flush(serial);
    }
#ifdef RT_SERIAL_USING_DMA
    else if (dev->open_flag & RT_DEVICE_FLAG_DMA_TX) {
        while (serial->ops->is_dma_txing(serial) == RT_TRUE);
    }
#endif /* RT_SERIAL_USING_DMA */
    } else {
        serial->ops->flush(serial);
    }

    return RT_EOK;
}

#ifdef RT_USING_POSIX_TERMIOS
struct speed_baudrate_item
{
    speed_t speed;
    int baudrate;
};

const static struct speed_baudrate_item _tbl[] =
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
    {B921600, BAUD_RATE_921600},
    {B2000000, BAUD_RATE_2000000},
    {B3000000, BAUD_RATE_3000000},
};

static speed_t _get_speed(int baudrate)
{
    int index;

    for (index = 0; index < sizeof(_tbl)/sizeof(_tbl[0]); index ++)
    {
        if (_tbl[index].baudrate == baudrate)
            return _tbl[index].speed;
    }

    return B0;
}

static int _get_baudrate(speed_t speed)
{
    int index;

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
    struct rt_serial_fifo *rx_fifo = RT_NULL;
    struct rt_device *device = RT_NULL;

    RT_ASSERT(serial != RT_NULL);

    device = &(serial->parent);
    rx_fifo = (struct rt_serial_fifo *) serial->serial_rx;

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

#endif

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
    case RT_DEVICE_CTRL_BLOCKING:
        if (((rt_uint32_t)args & RT_DEVICE_OFLAG_NONBLOCKING) == RT_DEVICE_OFLAG_NONBLOCKING) {
            dev->open_flag |= RT_DEVICE_OFLAG_NONBLOCKING;
        } else {
            dev->open_flag &= ~RT_DEVICE_OFLAG_NONBLOCKING;
        }
    break;
    case RT_DEVICE_CTRL_CONFIG:
        if (args)
        {
            struct serial_configure *pconfig = (struct serial_configure *) args;

            /* serial device has been opened, to configure it */
            ret = serial->ops->configure(serial, pconfig);
            if (ret == RT_EOK) {
                /* set serial configure */
                serial->config = *pconfig;
            }
        }
    break;
#ifdef RT_USING_POSIX_STDIO
#ifdef RT_USING_POSIX_TERMIOS
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
                int queue = (int)args;

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
                        _tio_buf[i] = getchar();
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
                recved = _serial_fifo_calc_data_len(serial->serial_rx);
                rt_hw_interrupt_enable(level);

                *(rt_size_t *)args = recved;
            }
            break;
#endif /*RT_USING_POSIX_STDIO*/
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
    .init = rt_serial_init,
    .open = rt_serial_open,
    .close = rt_serial_close,
    .read = rt_serial_read,
    .write = rt_serial_write,
    .flush = rt_serial_flush,
    .control = rt_serial_control
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

    serial->config = RT_SERIAL_CONFIG_DEFAULT;
    serial->bufsz = RT_SERIAL_FIFO_BUFSZ;

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
    device->flush       = rt_serial_flush;
    device->control     = rt_serial_control;
#endif
    device->user_data   = data;

    /* register a character device */
    ret = rt_device_register(device, name, flag);

#if defined(RT_USING_POSIX_STDIO)
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
        struct rt_serial_fifo* rx_fifo;

        /* interrupt mode receive */
        rx_fifo = (struct rt_serial_fifo*)serial->serial_rx;

#if defined(RT_SERIAL_HARD_FIFO)
        while (1)
#endif
        {
            ch = serial->ops->getc(serial);
#if defined(RT_SERIAL_HARD_FIFO)
            if (ch == -1) break;
#endif

            /* if fifo is full, discard one byte first */
            if (rx_fifo->is_full == RT_TRUE) {
                rx_fifo->get_index += 1;
                if (rx_fifo->get_index >= rx_fifo->buf_sz) rx_fifo->get_index = 0;
            }
            /* push a new data */
            _serial_fifo_push_data(rx_fifo, ch);

            /* if put index equal to read index, fifo is full */
            if (rx_fifo->put_index == rx_fifo->get_index)
            {
                rx_fifo->is_full = RT_TRUE;
            }
        }
#ifndef RT_SERIAL_USE_EVENT
        rt_completion_done(&(serial->completion_rx));
#else
        rt_event_send(serial->rx_done, RT_SERIAL_EVENT_RXDONE);
#endif
        /* invoke callback */
        if (serial->parent.rx_indicate != RT_NULL) {
            rt_size_t rx_length;

            /* get rx length */
            rx_length = _serial_fifo_calc_data_len(rx_fifo);
            if (rx_length) {
                serial->parent.rx_indicate(&serial->parent, rx_length);
            }
        }
    }
    break;
    case RT_SERIAL_EVENT_TX_DONE:
    {
#if defined(RT_SERIAL_HARD_FIFO)
        rt_size_t fifo_sz;
#endif
        rt_size_t len;
        rt_uint8_t ch = 0;
        struct rt_serial_fifo *tx_fifo;

        tx_fifo = (struct rt_serial_fifo*) serial->serial_tx;

        /* calucate fifo data size */
        len = _serial_fifo_calc_data_len(tx_fifo);
        if (len == 0) {
            // TODO: stop tx
            serial->ops->stop_tx(serial);
#ifndef RT_SERIAL_USE_EVENT
            rt_completion_done(&(serial->completion_tx));
#else
            rt_event_send(serial->tx_done, RT_SERIAL_EVENT_TXDONE);
#endif
            /* invoke callback */
            if (serial->parent.tx_complete != RT_NULL) {
                serial->parent.tx_complete(&serial->parent, (void*)len);
            }
            break;
        }
#if defined(RT_SERIAL_HARD_FIFO)
        fifo_sz = event >> 8;
        if (len > fifo_sz) {
            len = fifo_sz;
        }
        /* read from software FIFO */
        while (len > 0) {
            /* pop one byte data */
            ch = _serial_fifo_pop_data(tx_fifo);

            serial->ops->putc(serial, ch);
            len--;
        }
#else
        /* pop one byte data */
        ch = _serial_fifo_pop_data(tx_fifo);

        serial->ops->putc(serial, ch);
#endif
        tx_fifo->is_full = RT_FALSE;
    }
    break;
#ifdef RT_SERIAL_USING_DMA
    case RT_SERIAL_EVENT_RX_DMADONE:
    {
        int dma_idx, ch = -1;
        struct rt_serial_fifo* rx_fifo;

        dma_idx = event >> 8;

        if (serial->dma_idx_rx == dma_idx) break;

        rx_fifo = (struct rt_serial_fifo*)serial->serial_rx;

        while (serial->dma_idx_rx != dma_idx) {
            ch = serial->serial_dma_rx[serial->dma_idx_rx];

            /* if fifo is full, discard one byte first */
            if (rx_fifo->is_full == RT_TRUE) {
                rx_fifo->get_index += 1;
                if (rx_fifo->get_index >= rx_fifo->buf_sz) rx_fifo->get_index = 0;
            }
            /* push a new data */
            _serial_fifo_push_data(rx_fifo, ch);

            /* if put index equal to read index, fifo is full */
            if (rx_fifo->put_index == rx_fifo->get_index)
            {
                rx_fifo->is_full = RT_TRUE;
            }
            serial->dma_idx_rx++;
            if (serial->dma_idx_rx == RT_SERIAL_DMA_BUFSZ) {
                serial->dma_idx_rx = 0;
            }
        }
        serial->dma_idx_rx = dma_idx;
#ifndef RT_SERIAL_USE_EVENT
        rt_completion_done(&(serial->completion_rx));
#else
        rt_event_send(serial->rx_done, RT_SERIAL_EVENT_RXDONE);
#endif

        /* invoke callback */
        if (serial->parent.rx_indicate != RT_NULL) {
            rt_size_t rx_length;

            /* get rx length */
            rx_length = _serial_fifo_calc_data_len(rx_fifo);
            if (rx_length) {
                serial->parent.rx_indicate(&serial->parent, rx_length);
            }
        }
    }
    break;
    case RT_SERIAL_EVENT_TX_DMADONE:
    {
        int i;
        rt_size_t len;
        rt_uint8_t ch = 0;
        struct rt_serial_fifo *tx_fifo;

        tx_fifo = (struct rt_serial_fifo*) serial->serial_tx;

        /* calucate fifo data size */
        len = _serial_fifo_calc_data_len(tx_fifo);
        if (len == 0) {
            // TODO: stop tx
            serial->ops->stop_dma_tx(serial);
#ifndef RT_SERIAL_USE_EVENT
            rt_completion_done(&(serial->completion_tx));
#else
            rt_event_send(serial->tx_done, RT_SERIAL_EVENT_TXDONE);
#endif
            /* invoke callback */
            if (serial->parent.tx_complete != RT_NULL) {
                serial->parent.tx_complete(&serial->parent, (void*)len);
            }
            break;
        }

        if (len > RT_SERIAL_DMA_BUFSZ) {
            len = RT_SERIAL_DMA_BUFSZ;
        }
        /* read from software FIFO */
        for (i = 0; i < len; i++) {
            /* pop one byte data */
            ch = _serial_fifo_pop_data(tx_fifo);

            serial->serial_dma_tx[i] = ch;
        }
        tx_fifo->is_full = RT_FALSE;
        serial->ops->start_dma_tx(serial, serial->serial_dma_tx, len);
    }
    break;
#endif /* RT_SERIAL_USING_DMA */
    }
}
#endif /* RT_USING_SERIAL */
