#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#define SERIAL_UART_NAME "uart2"
#define UART_SEND_TIMES 400
#define UART_TEST_NUMBER 6

#ifdef UTEST_SERIAL_TC

static rt_bool_t block_write(rt_device_t uart_dev)
{
    rt_size_t i, wr_sz, index, write_num_array[UART_TEST_NUMBER], total_write_num[UART_TEST_NUMBER];
    rt_tick_t tick1, tick2, tick_array[UART_TEST_NUMBER];
    rt_uint8_t uart_write_buffer[1024];

    for (i = 0; i < 1024; i++)
        uart_write_buffer[i] = '0' + (i % 49);

    /* make sure device is closed and reopen it */
    while(rt_device_close(uart_dev) != -RT_ERROR);
    rt_device_open(uart_dev, RT_DEVICE_FLAG_TX_BLOCKING);

    LOG_D("\nBLOCKING WRITE BEGIN\n");
    rt_thread_mdelay(2000);

    index = 0;
    wr_sz = 0;
    tick1 = rt_tick_get();
    for(i = 0; i < UART_SEND_TIMES; i++)
        wr_sz += rt_device_write(uart_dev, 0, uart_write_buffer, 1024);

    tick2 = rt_tick_get();
    total_write_num[index] = UART_SEND_TIMES * 1024;
    tick_array[index] = tick2 - tick1;
    write_num_array[index++] = wr_sz;

    wr_sz = 0;
    tick1 = rt_tick_get();
    wr_sz += rt_device_write(uart_dev, 0, uart_write_buffer, 8);
    tick2 = rt_tick_get();
    total_write_num[index] = 8;
    tick_array[index] = tick2 - tick1;
    write_num_array[index++] = wr_sz;

    wr_sz = 0;
    tick1 = rt_tick_get();
    wr_sz += rt_device_write(uart_dev, 0, uart_write_buffer, 32);
    tick2 = rt_tick_get();
    total_write_num[index] = 32;
    tick_array[index] = tick2 - tick1;
    write_num_array[index++] = wr_sz;

    wr_sz = 0;
    tick1 = rt_tick_get();
    wr_sz += rt_device_write(uart_dev, 0, uart_write_buffer, 128);
    tick2 = rt_tick_get();
    total_write_num[index] = 128;
    tick_array[index] = tick2 - tick1;
    write_num_array[index++] = wr_sz;

    wr_sz = 0;
    tick1 = rt_tick_get();
    wr_sz += rt_device_write(uart_dev, 0, uart_write_buffer, 512);
    tick2 = rt_tick_get();
    total_write_num[index] = 512;
    tick_array[index] = tick2 - tick1;
    write_num_array[index++] = wr_sz;

    wr_sz = 0;
    tick1 = rt_tick_get();
    wr_sz += rt_device_write(uart_dev, 0, uart_write_buffer, 1024);
    tick2 = rt_tick_get();
    total_write_num[index] = 1024;
    tick_array[index] = tick2 - tick1;
    write_num_array[index++] = wr_sz;

    rt_thread_mdelay(1000);
    LOG_D("\nBLOCKING_TX END\n");
    for(i = 0; i < index; i++)
    {
        LOG_D("\nBLOCKING_MODE : write %d / %d bytes in %d ticks\n", write_num_array[i], total_write_num[i], tick_array[i]);
        rt_thread_mdelay(1000);
    }

    return RT_TRUE;
}

static void uart_test_blocking_tx(void)
{
    rt_device_t uart_dev;
    uart_dev = rt_device_find(SERIAL_UART_NAME);
    uassert_not_null(uart_dev);

    uassert_true (block_write(uart_dev));
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
    UTEST_UNIT_RUN(uart_test_blocking_tx);
}
UTEST_TC_EXPORT(testcase, "uart_blocking_tx", utest_tc_init, utest_tc_cleanup, 10);

#endif
