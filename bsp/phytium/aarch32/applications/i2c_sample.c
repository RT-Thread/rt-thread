
#include "rtconfig.h"
#if defined BSP_USING_I2C
#include "drv_log.h"
#include "drv_i2c.h"
#include "fi2c.h"
#include "fi2c_hw.h"
#include "fio_mux.h"
#include "fmio_hw.h"
#include "fmio.h"
#include "drivers/i2c.h"
#include "fparameters.h"

static struct rt_i2c_bus_device *i2c_test_bus = RT_NULL; 
int i2c_sample(int argc, char *argv[])
{
    char name[RT_NAME_MAX];
#if defined(FIREFLY_DEMO_BOARD)
    rt_strncpy(name, "MIO1", RT_NAME_MAX);
#endif
#if defined(E2000D_DEMO_BOARD)||defined(E2000Q_DEMO_BOARD)

    rt_strncpy(name, "MIO15", RT_NAME_MAX);
#endif
    i2c_test_bus = (struct rt_i2c_bus_device *)rt_device_find(name);

    rt_uint8_t read_buf[2] = {0x02, 0x0};
    rt_uint8_t write_buf[2] = {0x02, 0x01};
    if (i2c_test_bus == RT_NULL)
    {
        rt_kprintf("can't find %s device!\n", name);
    }
    else
    {
        rt_kprintf("find %s device!!!!\n", name);
    }

    struct rt_i2c_msg read_msgs;
    read_msgs.addr = 0x6B;
    read_msgs.flags = RT_I2C_RD;
    read_msgs.buf = read_buf;
    read_msgs.len = 1;
    rt_i2c_transfer(i2c_test_bus, &read_msgs, 1);
    rt_kprintf("read_buf = %x\n", *read_msgs.buf);

    struct rt_i2c_msg write_msgs;
    write_msgs.addr = 0x6B;
    write_msgs.flags = RT_I2C_WR;
    write_msgs.buf = write_buf;
    write_msgs.len = 1;
    rt_i2c_transfer(i2c_test_bus, &write_msgs, 1);
    read_buf[0] = 0x02;
    rt_i2c_transfer(i2c_test_bus, &read_msgs, 1);
    rt_kprintf("read_buf = %x\n", *read_msgs.buf);

    return RT_EOK;
}
MSH_CMD_EXPORT(i2c_sample, i2c device sample);

#endif