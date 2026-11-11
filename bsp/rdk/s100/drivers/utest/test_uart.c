/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-20     rcitach      first version
 */

#include <rtdevice.h>
#include <rtdbg.h>
#include <utest.h>

/*
 * S100 UART utest 说明
 *
 * 1. 本测试面向当前 BSP 的 UART v2 驱动实现，覆盖非控制台串口的基础访问流程。
 * 2. 根据 BSP 约定，uart4 默认为 msh 控制台，本测试不会对 uart4 做 open/read/write
 *    覆盖，避免干扰交互终端。
 * 3. 测试对象仅包含启用的 uart5 和 uart6；若两者都未使能，测试会打印跳过提示。
 * 4. 测试分为两部分：
 *    - basic：验证 rt_device_find/open/control(close) 这条基础控制路径；
 *    - txrx smoke：验证配置成功后能够执行一次 write，并检查 read 接口可调用。
 * 5. 当前 S100 UART BSP 不支持 DMA，因此这里不覆盖 DMA 模式。
 * 6. txrx smoke 现在要求被测串口具备回环条件（硬件短接 TX/RX 或外部回环），测试会校验
 *    接收到的数据内容与发送 payload 完全一致。
 */

#define S100_UART_TEST_BAUD_RATE      115200
#define S100_UART_READ_BUF_SIZE       16
#define S100_UART_RX_TIMEOUT_TICKS    (RT_TICK_PER_SECOND / 2)

static const rt_uint8_t s100_uart_test_frame[] =
{
    0x55, 0xAA, 0x00, 0xFF, 0x31, 0x32, 0x33, 0x0D, 0x0A,
};

struct s100_uart_test_port
{
    const char *name;
};

#if defined(BSP_USING_UART5) || defined(BSP_USING_UART6)
static const struct s100_uart_test_port s100_uart_test_ports[] =
{
#ifdef BSP_USING_UART5
    { "uart5" },
#endif
#ifdef BSP_USING_UART6
    { "uart6" },
#endif
};

#define S100_UART_TEST_PORT_COUNT \
    (sizeof(s100_uart_test_ports) / sizeof(s100_uart_test_ports[0]))
#else
static const struct s100_uart_test_port s100_uart_test_ports[] =
{
    { RT_NULL },
};

#define S100_UART_TEST_PORT_COUNT 0u
#endif

static void s100_uart_prepare_config(struct serial_configure *config)
{
    RT_ASSERT(config != RT_NULL);

    config->baud_rate = S100_UART_TEST_BAUD_RATE;
    config->data_bits = DATA_BITS_8;
    config->stop_bits = STOP_BITS_1;
    config->parity = PARITY_NONE;
    config->flowcontrol = RT_SERIAL_FLOWCONTROL_NONE;
}

static void s100_uart_check_port_basic(const char *name)
{
    rt_device_t uart_dev;
    struct serial_configure config;
    rt_err_t ret;

    uart_dev = rt_device_find(name);
    uassert_not_null(uart_dev);

    ret = rt_device_control(uart_dev, RT_SERIAL_CTRL_GET_CONFIG, &config);
    uassert_int_equal(ret, RT_EOK);

    s100_uart_prepare_config(&config);

    ret = rt_device_open(uart_dev, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_device_control(uart_dev, RT_DEVICE_CTRL_CONFIG, &config);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_device_close(uart_dev);
    uassert_int_equal(ret, RT_EOK);
}

static void s100_uart_check_port_txrx_smoke(const char *name)
{
    rt_uint8_t rx_buf[sizeof(s100_uart_test_frame)];
    rt_device_t uart_dev;
    struct serial_configure config;
    rt_err_t ret;
    rt_ssize_t len;
    rt_size_t rx_total;
    rt_size_t i;
    rt_tick_t deadline;

    uart_dev = rt_device_find(name);
    uassert_not_null(uart_dev);

    ret = rt_device_control(uart_dev, RT_SERIAL_CTRL_GET_CONFIG, &config);
    uassert_int_equal(ret, RT_EOK);

    s100_uart_prepare_config(&config);

    ret = rt_device_open(uart_dev, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_device_control(uart_dev, RT_DEVICE_CTRL_CONFIG, &config);
    uassert_int_equal(ret, RT_EOK);

    LOG_HEX("uart.tx", 16, s100_uart_test_frame, sizeof(s100_uart_test_frame));
    len = rt_device_write(uart_dev, 0, s100_uart_test_frame, sizeof(s100_uart_test_frame));
    uassert_int_equal(len, (rt_ssize_t)sizeof(s100_uart_test_frame));

    rx_total = 0;
    deadline = rt_tick_get() + S100_UART_RX_TIMEOUT_TICKS;
    while ((rx_total < sizeof(s100_uart_test_frame)) && (rt_tick_get() < deadline))
    {
        len = rt_device_read(uart_dev, 0, rx_buf + rx_total, sizeof(s100_uart_test_frame) - rx_total);
        uassert_true(len >= 0);

        if (len == 0)
        {
            rt_thread_mdelay(10);
            continue;
        }

        LOG_HEX("uart.rx.chunk", 16, rx_buf + rx_total, (rt_size_t)len);
        rx_total += (rt_size_t)len;
    }

    if (rx_total > 0)
    {
        LOG_HEX("uart.rx.total", 16, rx_buf, rx_total);
    }

    uassert_int_equal((int)rx_total, (int)sizeof(s100_uart_test_frame));
    for (i = 0; i < sizeof(s100_uart_test_frame); i++)
    {
        rt_kprintf("%s compare[%d]: tx=0x%02X rx=0x%02X\n",
                   name,
                   (int)i,
                   s100_uart_test_frame[i],
                   rx_buf[i]);
        uassert_int_equal((int)rx_buf[i], (int)s100_uart_test_frame[i]);
    }

    ret = rt_device_close(uart_dev);
    uassert_int_equal(ret, RT_EOK);
}

static void uart_non_console_basic_demo(void)
{
    rt_size_t i;

    if (S100_UART_TEST_PORT_COUNT == 0)
    {
        return;
    }

    for (i = 0; i < S100_UART_TEST_PORT_COUNT; i++)
    {
        s100_uart_check_port_basic(s100_uart_test_ports[i].name);
    }
}

static void uart_non_console_txrx_demo(void)
{
    rt_size_t i;

    if (S100_UART_TEST_PORT_COUNT == 0)
    {
        return;
    }

    for (i = 0; i < S100_UART_TEST_PORT_COUNT; i++)
    {
        s100_uart_check_port_txrx_smoke(s100_uart_test_ports[i].name);
    }
}

static void uart_testcase(void)
{
    UTEST_UNIT_RUN(uart_non_console_basic_demo);
    UTEST_UNIT_RUN(uart_non_console_txrx_demo);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

UTEST_TC_EXPORT(uart_testcase, "rdk.s100.drivers.uart", utest_tc_init, utest_tc_cleanup, 10);

