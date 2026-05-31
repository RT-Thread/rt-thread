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
#include <utest.h>

/*
 * S100 CAN utest 说明
 *
 * 1. 本测试面向当前 rdk/s100 BSP 的 RT-Thread CAN 设备驱动，覆盖设备发现、
 *    open、配置、模式切换、发送、接收、状态读取和 close 的基础路径。
 * 2. 为避免依赖外部 CAN 对端，本测试使用驱动支持的 RT_CAN_MODE_LOOPBACK 内部回环模式。
 *    因此测试默认不要求外部收发器回环或两节点组网。
 * 3. 测试对象仅包含当前配置中启用的 can5/can6/can7/can8/can9。
 * 4. 发送内容使用一帧标准数据帧（11-bit ID，8 字节 payload），接收后逐字段校验：
 *    - IDE/RTR
 *    - 标准 ID
 *    - DLC
 *    - data[0..7]
 * 5. 若需要改成外部总线联调，请把 loopback 模式切回 normal，并去掉本用例的回环假设。
 */

static const struct rt_can_msg s100_can_test_msg =
{
    .id = 0x123,
    .ide = RT_CAN_STDID,
    .rtr = RT_CAN_DTR,
    .len = 8,
    .priv = 0,
    .hdr_index = -1,
    .rxfifo = 0,
    .reserved = 0,
    .nonblocking = 0,
    .data = {0x55, 0xAA, 0x00, 0xFF, 0x11, 0x22, 0x33, 0x44},
};

struct s100_can_test_port
{
    const char *name;
};

#if defined(BSP_USING_CAN5) || defined(BSP_USING_CAN6) || defined(BSP_USING_CAN7) || defined(BSP_USING_CAN8) || defined(BSP_USING_CAN9)
static const struct s100_can_test_port s100_can_test_ports[] =
{
#ifdef BSP_USING_CAN5
    { "can5" },
#endif
#ifdef BSP_USING_CAN6
    { "can6" },
#endif
#ifdef BSP_USING_CAN7
    { "can7" },
#endif
#ifdef BSP_USING_CAN8
    { "can8" },
#endif
#ifdef BSP_USING_CAN9
    { "can9" },
#endif
};

#define S100_CAN_TEST_PORT_COUNT \
    (sizeof(s100_can_test_ports) / sizeof(s100_can_test_ports[0]))
#else
static const struct s100_can_test_port s100_can_test_ports[] =
{
    { RT_NULL },
};

#define S100_CAN_TEST_PORT_COUNT 0u
#endif

static void s100_can_prepare_config(struct can_configure *cfg)
{
    RT_ASSERT(cfg != RT_NULL);

    cfg->baud_rate = CAN1MBaud;
    cfg->mode = RT_CAN_MODE_LOOPBACK;
    cfg->privmode = RT_CAN_MODE_NOPRIV;
}

static void s100_can_check_port_basic(const char *name)
{
    rt_device_t can_dev;
    struct can_configure cfg = CANDEFAULTCONFIG;
    struct rt_can_status status;
    rt_err_t ret;

    can_dev = rt_device_find(name);
    uassert_not_null(can_dev);

    s100_can_prepare_config(&cfg);

    ret = rt_device_control(can_dev, RT_DEVICE_CTRL_CONFIG, &cfg);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_device_open(can_dev, RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_device_control(can_dev, RT_CAN_CMD_SET_MODE, (void *)RT_CAN_MODE_LOOPBACK);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_device_control(can_dev, RT_CAN_CMD_SET_BAUD, (void *)CAN1MBaud);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_device_control(can_dev, RT_CAN_CMD_GET_STATUS, &status);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_device_close(can_dev);
    uassert_int_equal(ret, RT_EOK);
}

static void s100_can_check_port_loopback(const char *name)
{
    rt_device_t can_dev;
    struct can_configure cfg = CANDEFAULTCONFIG;
    struct rt_can_msg rx_msg;
    rt_err_t ret;
    rt_ssize_t wr_len;
    rt_ssize_t rd_len;
    rt_size_t i;

    can_dev = rt_device_find(name);
    uassert_not_null(can_dev);

    s100_can_prepare_config(&cfg);

    ret = rt_device_control(can_dev, RT_DEVICE_CTRL_CONFIG, &cfg);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_device_open(can_dev, RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_device_control(can_dev, RT_CAN_CMD_SET_MODE, (void *)RT_CAN_MODE_LOOPBACK);
    uassert_int_equal(ret, RT_EOK);

    ret = rt_device_control(can_dev, RT_CAN_CMD_SET_BAUD, (void *)CAN1MBaud);
    uassert_int_equal(ret, RT_EOK);

    rt_memset(&rx_msg, 0, sizeof(rx_msg));

    rt_kprintf("%s tx can id=0x%03X len=%d\n", name, (unsigned int)s100_can_test_msg.id, (int)s100_can_test_msg.len);
    LOG_HEX("can.tx", 16, s100_can_test_msg.data, s100_can_test_msg.len);

    wr_len = rt_device_write(can_dev, 0, &s100_can_test_msg, sizeof(s100_can_test_msg));
    uassert_int_equal((int)wr_len, (int)sizeof(s100_can_test_msg));

    rd_len = rt_device_read(can_dev, 0, &rx_msg, sizeof(rx_msg));
    uassert_int_equal((int)rd_len, (int)sizeof(rx_msg));

    rt_kprintf("%s rx can id=0x%03X len=%d\n", name, (unsigned int)rx_msg.id, (int)rx_msg.len);
    LOG_HEX("can.rx", 16, rx_msg.data, rx_msg.len);

    uassert_int_equal((int)rx_msg.ide, (int)s100_can_test_msg.ide);
    uassert_int_equal((int)rx_msg.rtr, (int)s100_can_test_msg.rtr);
    uassert_int_equal((int)rx_msg.id, (int)s100_can_test_msg.id);
    uassert_int_equal((int)rx_msg.len, (int)s100_can_test_msg.len);

    for (i = 0; i < s100_can_test_msg.len; i++)
    {
        rt_kprintf("%s compare[%d]: tx=0x%02X rx=0x%02X\n",
                   name,
                   (int)i,
                   s100_can_test_msg.data[i],
                   rx_msg.data[i]);
        uassert_int_equal((int)rx_msg.data[i], (int)s100_can_test_msg.data[i]);
    }

    ret = rt_device_close(can_dev);
    uassert_int_equal(ret, RT_EOK);
}

static void can_basic_demo(void)
{
    rt_size_t i;

    if (S100_CAN_TEST_PORT_COUNT == 0)
    {
        return;
    }

    for (i = 0; i < S100_CAN_TEST_PORT_COUNT; i++)
    {
        s100_can_check_port_basic(s100_can_test_ports[i].name);
    }
}

static void can_loopback_demo(void)
{
    rt_size_t i;

    if (S100_CAN_TEST_PORT_COUNT == 0)
    {
        return;
    }

    for (i = 0; i < S100_CAN_TEST_PORT_COUNT; i++)
    {
        s100_can_check_port_loopback(s100_can_test_ports[i].name);
    }
}

static void can_testcase(void)
{
    UTEST_UNIT_RUN(can_basic_demo);
    UTEST_UNIT_RUN(can_loopback_demo);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

UTEST_TC_EXPORT(can_testcase, "rdk.s100.drivers.can", utest_tc_init, utest_tc_cleanup, 20);

