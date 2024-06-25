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
void i2c_thread(void *parameter)
{
    int times = 0;
    char name[RT_NAME_MAX];
    rt_strncpy(name, (char *)parameter, RT_NAME_MAX);
    i2c_test_bus = (struct rt_i2c_bus_device *)rt_device_find(name);
    if (i2c_test_bus == RT_NULL)
    {
        rt_kprintf("can't find %s device!\n", name);
    }
    else
    {
        rt_kprintf("find %s device!!!!\n", name);
    }

    struct rt_i2c_msg read_msgs;
    struct rt_i2c_msg write_msgs;

    rt_uint8_t read_buf[18];
    rt_uint8_t write_buf[18];

    for (int i = 2; i < 18; i++)
    {
        write_buf[i] = i; 
    }
    
    while (1)
    {
        read_buf[0] = 0x0;
        read_buf[1] = 0x0;
        write_buf[0] = 0x0;
        write_buf[1] = 0x0;

        write_msgs.addr = 0x50;
        write_msgs.flags = RT_I2C_WR;
        write_msgs.buf = write_buf;
        write_msgs.len = 18;
        rt_i2c_transfer(i2c_test_bus, &write_msgs, 1);

        read_msgs.addr = 0x50;
        read_msgs.flags = RT_I2C_RD;
        read_msgs.buf = read_buf;
        read_msgs.len = 18;
        rt_i2c_transfer(i2c_test_bus, &read_msgs, 1);

        for (int i = 0; i < 16; i++)
        {
            if (read_buf[i] != write_buf[i + 2])
            {
                RT_ASSERT(0);
            }
        }
    }
}

int i2c_sample(int argc, char *argv[])
{
    rt_err_t res = RT_EOK;
    rt_thread_t thread;

    /* Create data receiving thread */
    thread = rt_thread_create("i2c_thread", i2c_thread, "MIO1", 4096, 25, 10);
    if (thread != RT_NULL)
    {
        res = rt_thread_startup(thread);
        RT_ASSERT(res == RT_EOK);
    }
    else
    {
        rt_kprintf("Create can_tx thread failed.\n");
    }

}
MSH_CMD_EXPORT(i2c_sample, i2c device sample);
#endif