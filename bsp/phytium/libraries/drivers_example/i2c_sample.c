#include "rtconfig.h"
#if defined(BSP_USING_I2C) || defined(BSP_USING_I2C_MSG)
#include "drv_log.h"
#include "drv_i2c.h"
#define TEST_DEVICE_ADDR 0x57
static struct rt_i2c_bus_device *i2c_test_bus = RT_NULL;

rt_err_t i2c_sample(void)
{
    rt_uint8_t write_content[] = {"write successfully"};
    rt_uint8_t write_addr[2] = {0x0, 0x0};
    rt_uint8_t write_buf[2 + sizeof(write_content)];
    rt_memcpy(write_buf, write_addr, 2);
    rt_memcpy(write_buf + 2, write_content, sizeof(write_content));

    rt_uint8_t read_buf[sizeof(write_content)];

    char name[RT_NAME_MAX];
#if defined(PHYTIUMPI_FIREFLY_BOARD)
    rt_strncpy(name, "MIO1", RT_NAME_MAX);
#endif
#if defined(E2000D_DEMO_BOARD)||defined(E2000Q_DEMO_BOARD)
    rt_strncpy(name, "MIO15", RT_NAME_MAX);
#endif
#if defined(TARGET_PD2408)
    rt_strncpy(name, "I2C3_MSG", RT_NAME_MAX);
#endif
    i2c_test_bus = (struct rt_i2c_bus_device *)rt_device_find(name);
    if (i2c_test_bus == RT_NULL)
    {
        rt_kprintf("can't find %s device!\n", name);
    }
    else
    {
        rt_kprintf("find %s device!!!!\n", name);
    }

    struct rt_i2c_msg write_msgs;
    write_msgs.addr = TEST_DEVICE_ADDR;
    write_msgs.flags = RT_I2C_WR;
    write_msgs.buf = write_buf;
    write_msgs.len = sizeof(write_buf);
    rt_i2c_transfer(i2c_test_bus, &write_msgs, 1);

    write_msgs.addr = TEST_DEVICE_ADDR;
    write_msgs.flags = RT_I2C_WR;
    write_msgs.buf = write_addr;
    write_msgs.len = 2;
    rt_i2c_transfer(i2c_test_bus, &write_msgs, 1);

    struct rt_i2c_msg read_msgs;
    read_msgs.addr = TEST_DEVICE_ADDR;
    read_msgs.flags = RT_I2C_RD;
    read_msgs.buf = read_buf;
    read_msgs.len = sizeof(read_buf);
    rt_i2c_transfer(i2c_test_bus, &read_msgs, 1);

    for (rt_uint8_t i = 0; i < sizeof(write_content); i++)
    {
        if (read_buf[i] != write_content[i])
        {
            rt_kprintf("[i2c] compare failed at index %d: read=0x%02X expect=0x%02X\n",
                       i,
                       read_buf[i],
                       write_content[i]);

            return -RT_ERROR;
        }
    }
    rt_kprintf("%s\n", read_buf);
    return RT_EOK;
}
MSH_CMD_EXPORT(i2c_sample, i2c device sample);

#endif