#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#define UART_SEND_TIMES  100
#define UART_TEST_NUMBER 6


#ifdef UTEST_SERIAL_TC
#define echo_test_buffer_size (1024)

static rt_device_t u1serial;
static rt_device_t u2serial;

static rt_uint32_t u2rx_length = 0;
static rt_uint32_t u2tx_length = 0;

static rt_uint32_t u1rx_length = 0;
static rt_uint32_t u1tx_length = 0;

static rt_uint8_t uart_over_flag = RT_FALSE;

static void echo_test_u2_thread_entry(void *parameter)
{
    char *uart_name = "uart2";

    u2serial = rt_device_find(uart_name);
    if (!u2serial)
    {
        LOG_I("find %s failed!\n", uart_name);
        return;
    }

    rt_uint8_t *rx_buffer = rt_malloc(echo_test_buffer_size);

    rt_device_open(u2serial, RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);

    rt_ssize_t buf_datalen = 0;
    while (1)
    {
        rt_device_control(u2serial, RT_SERIAL_CTRL_GET_UNREAD_BYTES_COUNT, (void *)&buf_datalen);
        int32_t recbLen = rt_device_read(u2serial, 0, rx_buffer, buf_datalen > 0 ? buf_datalen : 1);
        if (recbLen > 0)
        {
            u2rx_length += recbLen;
            u2tx_length += rt_device_write(u2serial, 0, rx_buffer, recbLen);

            if (uart_over_flag)
                break;
        }
    }
    rt_free(rx_buffer);
}

static void echo_test_u1_thread_entry(void *parameter)
{
    rt_uint8_t *rx_buffer   = rt_malloc(echo_test_buffer_size);
    rt_ssize_t  buf_datalen = 0;
    while (1)
    {
        rt_device_control(u1serial, RT_SERIAL_CTRL_GET_UNREAD_BYTES_COUNT, (void *)&buf_datalen);
        int32_t recbLen = rt_device_read(u1serial, 0, rx_buffer, buf_datalen > 0 ? buf_datalen : 1);
        if (recbLen > 0)
        {
            u1rx_length += recbLen;
            if (uart_over_flag)
                break;
        }
    }

    rt_free(rx_buffer);
}


static rt_bool_t echo_test()
{
    rt_bool_t result    = RT_TRUE;
    char     *uart_name = "uart1";
    u1serial            = rt_device_find(uart_name);
    if (!u1serial)
    {
        LOG_I("find %s failed!\n", uart_name);
        return RT_FALSE;
    }

    rt_uint8_t *tx_buffer = rt_malloc(echo_test_buffer_size);

    rt_device_open(u1serial, RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);
    rt_thread_startup(rt_thread_create("serial2", echo_test_u2_thread_entry, RT_NULL, 2048, RT_THREAD_PRIORITY_MAX - 4, 5));
    rt_thread_startup(rt_thread_create("serial1", echo_test_u1_thread_entry, RT_NULL, 2048, RT_THREAD_PRIORITY_MAX - 5, 5));

    uint32_t sendTotalCount = 0;
    srand(rt_tick_get());
    for (uint32_t count = 0; count < 1000; count++)
    {
        // Indefinite length of data is sent
        uint32_t sendCount = rand() % echo_test_buffer_size;


        u1tx_length    += rt_device_write(u1serial, 0, tx_buffer, sendCount);
        sendTotalCount += sendCount;

        // Wait for the cross-send to complete
        rt_thread_mdelay(UART_SEND_TIMES);

        if (count % 50 == 0)
        {
            LOG_I("echo, uart2: tx: %ld, rx: %ld", u2tx_length, u2rx_length);
            LOG_I("echo, uart1: tx: %ld, rx: %ld", u1tx_length, u1rx_length);
            if (u2tx_length != u2rx_length || u1tx_length != u1rx_length || u2tx_length != u1tx_length)
            {
                LOG_I("echo test error!!!");
                result = RT_FALSE;
                break;
            }

            if (u2tx_length != sendTotalCount)
            {
                LOG_I("u2tx_length != sendTotalCount echo test error!!!");
                result = RT_FALSE;
                break;
            }
        }
    }

    uart_over_flag = RT_TRUE;
    // Notify the thread to exit
    rt_device_write(u1serial, 0, tx_buffer, echo_test_buffer_size);
    rt_thread_mdelay(30);

    {
        rt_device_t uart_dev = rt_device_find("uart2");
        while (rt_device_close(uart_dev) != -RT_ERROR);
    }
    {
        rt_device_t uart_dev = rt_device_find("uart1");
        while (rt_device_close(uart_dev) != -RT_ERROR);
    }
    rt_free(tx_buffer);
    return result;
}

static void uart_test_nonblocking_tx(void)
{
    uassert_true(echo_test());
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    u1serial       = RT_NULL;
    u2serial       = RT_NULL;
    u2rx_length    = 0;
    u2tx_length    = 0;
    u1rx_length    = 0;
    u1tx_length    = 0;
    uart_over_flag = RT_FALSE;
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(uart_test_nonblocking_tx);
}
UTEST_TC_EXPORT(testcase, "testcases.drivers.uart_qemu_echo", utest_tc_init, utest_tc_cleanup, 10);

#endif
