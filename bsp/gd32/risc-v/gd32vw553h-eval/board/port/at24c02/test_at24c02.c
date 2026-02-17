#include "rtconfig.h"

#ifdef BSP_USING_AT24C02

#include "utest.h"
#include "at24c02.h"

#define TEST_DATA  "WELCOME TO RTT"

static at24cxx_device_t dev = RT_NULL;

static rt_err_t test_at24c02_init(void)
{
    rt_err_t result = RT_EOK;
    uint8_t AddrInput = 0x0;

    dev = at24cxx_init(AT24C02_I2C_NAME, AddrInput);
    if (dev == RT_NULL)
    {
       LOG_E("AT24C02 initialization failed\n");
       result = -RT_ERROR;
    }

    return result;
}

static void test_at24c02_example(void)
{
    uint8_t write_buffer[] = TEST_DATA;
    int data_size = sizeof(write_buffer);
    rt_err_t result = RT_EOK;

    uint8_t read_buffer[50] = {0};

    /* 写入数据 */
    result = at24cxx_write(dev, 0, write_buffer, data_size);

    if (result != RT_EOK)
    {
        LOG_E("Failed to write data to AT24C02\n");
        uassert_true(RT_FALSE);
        return;
    }

    LOG_I("Successfully wrote to AT24C02: %s\n", write_buffer);

    /* 读取数据 */
    result = at24cxx_read(dev, 0, read_buffer, data_size);

    if (result != RT_EOK)
    {
        LOG_E("Failed to read data from AT24C02\n");
        uassert_true(RT_FALSE);
        return;
    }

    LOG_I("Successfully read from AT24C02: %s\n", read_buffer);

    uassert_str_equal(write_buffer, read_buffer);

    /* 检查数据 */
    result =  at24cxx_check(dev);

    uassert_true(result == RT_EOK);

    return;
}

static rt_err_t test_at24c02_deinit(void)
{

    if (dev != RT_NULL)
    {
        at24cxx_deinit(dev);
        dev = RT_NULL;
        return RT_EOK;
    }

    return -RT_ERROR;
}

static void test_case(void)
{
    UTEST_UNIT_RUN(test_at24c02_example);
}

UTEST_TC_EXPORT(test_case, "bsp.gd32.port.at24c02" , test_at24c02_init, test_at24c02_deinit, 100);

#endif