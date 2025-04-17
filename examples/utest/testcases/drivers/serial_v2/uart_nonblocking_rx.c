#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#ifdef UTEST_SERIAL_TC

static rt_bool_t nonblock_read(rt_device_t uart_dev)
{
    rt_size_t total_length, recv_length;
    char      uart_read_buffer[1024], log_buffer[64];

    /* make sure device is closed and reopen it */
    while (rt_device_close(uart_dev) != -RT_ERROR);
    rt_device_open(uart_dev, RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING);

    rt_sprintf(log_buffer, "\nNONBLOCKING READ BEGIN, PLEASE SEND SOME DATAS\n");
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    total_length = 0;
    rt_device_write(uart_dev, 0, "5\n", 2);
    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 256);
    rt_device_write(uart_dev, 0, uart_read_buffer, 256);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nnonblock : %d bytes read, total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    rt_device_write(uart_dev, 0, "4\n", 2);
    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 256);
    rt_device_write(uart_dev, 0, uart_read_buffer, 256);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nnonblock : %d bytes read , total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    rt_device_write(uart_dev, 0, "3\n", 2);
    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 256);
    rt_device_write(uart_dev, 0, uart_read_buffer, 256);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nnonblock : %d bytes read, total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    rt_device_write(uart_dev, 0, "2\n", 2);
    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 128);
    rt_device_write(uart_dev, 0, uart_read_buffer, 128);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nnonblock : %d bytes read , total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    rt_device_write(uart_dev, 0, "1\n", 2);
    recv_length = 0;
    recv_length = rt_device_read(uart_dev, -1, uart_read_buffer, 128);
    rt_device_write(uart_dev, 0, uart_read_buffer, 128);
    total_length += recv_length;

    rt_sprintf(log_buffer, "\nnonblock : %d bytes read , total: %d \n", recv_length, total_length);
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    rt_sprintf(log_buffer, "BLOCKING READ END");
    rt_device_write(uart_dev, 0, log_buffer, rt_strlen(log_buffer));

    return RT_TRUE;
}

static void uart_test_nonblocking_rx(void)
{
    rt_device_t uart_dev;
    uart_dev = rt_device_find(RT_SERIAL_TC_DEVICE_NAME);
    uassert_not_null(uart_dev);

    uassert_true(nonblock_read(uart_dev));
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_device_t uart_dev = rt_device_find(RT_SERIAL_TC_DEVICE_NAME);
    while (rt_device_close(uart_dev) != -RT_ERROR);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(uart_test_nonblocking_rx);
}
UTEST_TC_EXPORT(testcase, "uart_nonblocking_rx", utest_tc_init, utest_tc_cleanup, 10);

#endif
