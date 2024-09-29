/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-05-15     lgnq         first version.
 * 2012-05-28     bernard      change interfaces
 * 2013-02-20     bernard      use RT_SERIAL_RB_BUFSZ to define
 *                             the size of ring buffer.
 */

#ifndef __DEV_SERIAL_H__
#define __DEV_SERIAL_H__

#include <rtthread.h>
/**
 * @addtogroup  Drivers          RTTHREAD Driver
 * @defgroup    Serial           Serial
 *
 * @brief       Serial driver api
 *
 * <b>Example</b>
 * @code {.c}
 *
 * #include <rtthread.h>
 *
 * #define SAMPLE_UART_NAME       "uart2"
 * static struct rt_semaphore rx_sem;
 * static rt_device_t serial;
 *
 * static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
 * {
 *
 *     rt_sem_release(&rx_sem);
 *
 *     return RT_EOK;
 * }
 *
 * static void serial_thread_entry(void *parameter)
 * {
 *     char ch;
 *
 *     while (1)
 *     {
 *
 *         while (rt_device_read(serial, -1, &ch, 1) != 1)
 *         {
 *
 *             rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
 *         }
 *
 *         ch = ch + 1;
 *         rt_device_write(serial, 0, &ch, 1);
 *     }
 * }
 *
 * static int uart_sample(int argc, char *argv[])
 * {
 *     rt_err_t ret = RT_EOK;
 *     char uart_name[RT_NAME_MAX];
 *     char str[] = "hello RT-Thread!\r\n";
 *
 *     if (argc == 2)
 *     {
 *         rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
 *     }
 *     else
 *     {
 *         rt_strncpy(uart_name, SAMPLE_UART_NAME, RT_NAME_MAX);
 *     }
 *
 *
 *     serial = rt_device_find(uart_name);
 *     if (!serial)
 *     {
 *         rt_kprintf("find %s failed!\n", uart_name);
 *         return RT_ERROR;
 *     }
 *
 *
 *     rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
 *
 *     rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
 *
 *     rt_device_set_rx_indicate(serial, uart_input);
 *
 *     rt_device_write(serial, 0, str, (sizeof(str) - 1));
 *
 *
 *     rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);
 *
 *     if (thread != RT_NULL)
 *     {
 *         rt_thread_startup(thread);
 *     }
 *     else
 *     {
 *         ret = RT_ERROR;
 *     }
 *
 *     return ret;
 * }
 *
 * MSH_CMD_EXPORT(uart_sample, uart device sample);
 * @endcode
 *
 * @ingroup     Drivers
 */


/*!
 * @addtogroup Serial
 * @{
 */
#define BAUD_RATE_2400                  2400
#define BAUD_RATE_4800                  4800
#define BAUD_RATE_9600                  9600
#define BAUD_RATE_19200                 19200
#define BAUD_RATE_38400                 38400
#define BAUD_RATE_57600                 57600
#define BAUD_RATE_115200                115200
#define BAUD_RATE_230400                230400
#define BAUD_RATE_460800                460800
#define BAUD_RATE_500000                500000
#define BAUD_RATE_576000                576000
#define BAUD_RATE_921600                921600
#define BAUD_RATE_1000000               1000000
#define BAUD_RATE_1152000               1152000
#define BAUD_RATE_1500000               1500000
#define BAUD_RATE_2000000               2000000
#define BAUD_RATE_2500000               2500000
#define BAUD_RATE_3000000               3000000
#define BAUD_RATE_3500000               3500000
#define BAUD_RATE_4000000               4000000

#define DATA_BITS_5                     5
#define DATA_BITS_6                     6
#define DATA_BITS_7                     7
#define DATA_BITS_8                     8
#define DATA_BITS_9                     9

#define STOP_BITS_1                     0
#define STOP_BITS_2                     1
#define STOP_BITS_3                     2
#define STOP_BITS_4                     3

#ifdef _WIN32
#include <windows.h>
#else
#define PARITY_NONE                     0
#define PARITY_ODD                      1
#define PARITY_EVEN                     2
#endif

#define BIT_ORDER_LSB                   0
#define BIT_ORDER_MSB                   1

#define NRZ_NORMAL                      0       /* Non Return to Zero : normal mode */
#define NRZ_INVERTED                    1       /* Non Return to Zero : inverted mode */

#ifndef RT_SERIAL_RB_BUFSZ
#define RT_SERIAL_RB_BUFSZ              64
#endif

#define RT_SERIAL_EVENT_RX_IND          0x01    /* Rx indication */
#define RT_SERIAL_EVENT_TX_DONE         0x02    /* Tx complete   */
#define RT_SERIAL_EVENT_RX_DMADONE      0x03    /* Rx DMA transfer done */
#define RT_SERIAL_EVENT_TX_DMADONE      0x04    /* Tx DMA transfer done */
#define RT_SERIAL_EVENT_RX_TIMEOUT      0x05    /* Rx timeout    */

#define RT_SERIAL_DMA_RX                0x01
#define RT_SERIAL_DMA_TX                0x02

#define RT_SERIAL_RX_INT                0x01
#define RT_SERIAL_TX_INT                0x02

#define RT_SERIAL_ERR_OVERRUN           0x01
#define RT_SERIAL_ERR_FRAMING           0x02
#define RT_SERIAL_ERR_PARITY            0x03

#define RT_SERIAL_TX_DATAQUEUE_SIZE     2048
#define RT_SERIAL_TX_DATAQUEUE_LWM      30

#define RT_SERIAL_FLOWCONTROL_CTSRTS    1
#define RT_SERIAL_FLOWCONTROL_NONE      0

/* Default config for serial_configure structure */
#define RT_SERIAL_CONFIG_DEFAULT           \
{                                          \
    BAUD_RATE_115200, /* 115200 bits/s */  \
    DATA_BITS_8,      /* 8 databits */     \
    STOP_BITS_1,      /* 1 stopbit */      \
    PARITY_NONE,      /* No parity  */     \
    BIT_ORDER_LSB,    /* LSB first sent */ \
    NRZ_NORMAL,       /* Normal mode */    \
    RT_SERIAL_RB_BUFSZ, /* Buffer size */  \
    RT_SERIAL_FLOWCONTROL_NONE, /* Off flowcontrol */ \
    0                                      \
}

/**
 * @brief Sets a hook function when RX indicate is called
 *
 */
typedef void (*rt_hw_serial_rxind_hookproto_t)(rt_device_t dev, rt_size_t size);
RT_OBJECT_HOOKLIST_DECLARE(rt_hw_serial_rxind_hookproto_t, rt_hw_serial_rxind);

struct serial_configure
{
    rt_uint32_t baud_rate;

    rt_uint32_t data_bits               :4;
    rt_uint32_t stop_bits               :2;
    rt_uint32_t parity                  :2;
    rt_uint32_t bit_order               :1;
    rt_uint32_t invert                  :1;
    rt_uint32_t bufsz                   :16;
    rt_uint32_t flowcontrol             :1;
    rt_uint32_t reserved                :5;
};

/*
 * Serial FIFO mode
 */
struct rt_serial_rx_fifo
{
    /* software fifo */
    rt_uint8_t *buffer;

    rt_uint16_t put_index, get_index;

    rt_bool_t is_full;
};

struct rt_serial_tx_fifo
{
    struct rt_completion completion;
};

/*
 * Serial DMA mode
 */
struct rt_serial_rx_dma
{
    rt_bool_t activated;
};

struct rt_serial_tx_dma
{
    rt_bool_t activated;
    struct rt_data_queue data_queue;
};

struct rt_serial_device
{
    struct rt_device          parent;

    const struct rt_uart_ops *ops;
    struct serial_configure   config;

    void *serial_rx;
    void *serial_tx;

    struct rt_spinlock spinlock;

    struct rt_device_notify rx_notify;
};
typedef struct rt_serial_device rt_serial_t;

/**
 * @brief Configure the serial device
 */
struct rt_uart_ops
{
    rt_err_t (*configure)(struct rt_serial_device *serial, struct serial_configure *cfg);
    rt_err_t (*control)(struct rt_serial_device *serial, int cmd, void *arg);

    int (*putc)(struct rt_serial_device *serial, char c);
    int (*getc)(struct rt_serial_device *serial);

    rt_ssize_t (*dma_transmit)(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction);
};

/**
 * @brief Serial interrupt service routine
 * @param serial    serial device
 * @param event     event mask
 * @ingroup  Serial
 */
void rt_hw_serial_isr(struct rt_serial_device *serial, int event);

/**
 * @brief Register a serial device to device list
 *
 * @param serial    serial device
 * @param name      device name
 * @param flag      device flag
 * @param data      device private data
 * @return rt_err_t        error code
 * @note This function will register a serial device to system device list,
 *       and add a device object to system object list.
 * @ingroup  Serial
 */
rt_err_t rt_hw_serial_register(struct rt_serial_device *serial,
                               const char              *name,
                               rt_uint32_t              flag,
                               void                    *data);

/**
 * @brief     register a serial device to system device list and add a device object to system object list
 *
 * @param serial    serial device
 * @return rt_err_t error code
 *
 * @ingroup  Serial
 */
rt_err_t rt_hw_serial_register_tty(struct rt_serial_device *serial);

/*! @}*/

#endif
