#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#define SERIAL_UART_NAME "uart2"

#ifdef UTEST_SERIAL_TC

static rt_bool_t block_read(rt_device_t uart_dev)
{
    rt_size_t total_length, recv_length;
    rt_uint8_t uart_read_buffer[1024], log_buffer[64];

    /* make sure device is closed and reopen it */
    while(rt_device_close(uart_dev) != -RT_ERROR);
    rt_device_open(uart_dev, RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_RX_BLOCKING);

    rt_sprintf(log_buffer, "\nBLOCKING READ BEGIN, PLEASE SEND SOME DATAS\n");
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    total_length = 0;
    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 256);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nblock : %d bytes read, total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 256);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nblock : %d bytes read , total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 256);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nblock : %d bytes read , total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 128);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nblock : %d bytes read , total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 128);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nblock : %d bytes read , total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));
    rt_thread_mdelay(1000);

    rt_sprintf(log_buffer, "BLOCKING READ END");
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    return RT_TRUE;
}

static void uart_test_blocking_rx(void)
{
    rt_device_t uart_dev;
    uart_dev = rt_device_find(SERIAL_UART_NAME);
    uassert_not_null(uart_dev);

    uassert_true (block_read(uart_dev));
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_device_t uart_dev;
    uart_dev = rt_device_find(SERIAL_UART_NAME);
    while(rt_device_close(uart_dev) != -RT_ERROR);
    rt_device_open(uart_dev, RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(uart_test_blocking_rx);
}
UTEST_TC_EXPORT(testcase, "uart_blocking_rx", utest_tc_init, utest_tc_cleanup, 10);

#endif
