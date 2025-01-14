/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-30     CDT          first version
 */

/*
 * 程序清单：这是一个 I2C 设备使用例程
 * 例程导出了 pcf8563 命令到控制终端
 * 命令调用格式：i2c_pcf8563_sample i2c1
 * 命令解释：命令第二个参数是要使用的I2C总线设备名称，为空则使用默认的I2C总线设备
 * 程序功能：通过 I2C 设备读取时间信息并打印
*/

#include <rtthread.h>
#include <rtdevice.h>

#if defined(BSP_USING_I2C)

#define PFC8563_I2C_BUS_NAME            "i2c1"  /* I2C总线设备名称 */
#define PFC8563_ADDR                    0x51    /* 从机地址 */
#define PFC8563_REG_SEC                 0x02    /* 校准命令 */
#define PFC8563_REG_CTRL_SR1            0x00    /* 校准命令 */

#define PFC8563_TIME_LEN                0x7    /* 获取数据长度 */


#define RTC_DEC2BCD(__DATA__)           ((((__DATA__) / 10U) << 4U) + ((__DATA__) % 10U))
#define RTC_BCD2DEC(__DATA__)           ((((__DATA__) >> 4U) * 10U) + ((__DATA__) & 0x0FU))


static struct rt_i2c_bus_device *i2c_bus = RT_NULL;     /* I2C总线设备句柄 */
static rt_bool_t initialized = RT_FALSE;                /* 传感器初始化状态 */

/* 写传感器寄存器 */
static rt_err_t write_regs(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t *data, rt_uint8_t len)
{
    rt_uint8_t buf[16 + 1];
    struct rt_i2c_msg msgs;
    rt_uint32_t buf_size = 1;

    buf[0] = reg;   // cmd
    if (data != RT_NULL)
    {
        memcpy(&buf[1], data, len);
        buf_size += len;
    }

    msgs.addr = PFC8563_ADDR;
    msgs.flags = RT_I2C_WR;
    msgs.buf = buf;
    msgs.len = buf_size;

    /* 调用I2C设备接口传输数据 */
    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        rt_kprintf("write regs failed!\n");
        return -RT_ERROR;
    }
}

/* 读传感器寄存器数据 */
static rt_err_t read_regs(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t *data, rt_uint8_t len)
{
    struct rt_i2c_msg msgs[2];
    rt_uint8_t buf[16 + 1];
    rt_uint32_t buf_size = 1;

    buf[0] = reg;   // cmd
    msgs[0].addr = PFC8563_ADDR;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = buf;
    msgs[0].len = buf_size;

    msgs[1].addr = PFC8563_ADDR;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf = data;
    msgs[1].len = len;

    /* 调用I2C设备接口传输数据 */
    if (rt_i2c_transfer(bus, &msgs[0], 2) == 2)
    {
        return RT_EOK;
    }
    else
    {
        rt_kprintf("read regs failed!\n");
        return -RT_ERROR;
    }
}

static void pcf8563_init(const char *name)
{
    rt_uint8_t temp[16];

    /* 查找I2C总线设备，获取I2C总线设备句柄 */
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(name);

    if (i2c_bus == RT_NULL)
    {
        rt_kprintf("can't find %s device!\n", name);
    }
    else
    {
        rt_thread_mdelay(500);
        temp[0] = 0x28U;
        write_regs(i2c_bus, PFC8563_REG_CTRL_SR1, temp, 1);
        rt_thread_mdelay(100);
        temp[0] = 0x08U;
        write_regs(i2c_bus, PFC8563_REG_CTRL_SR1, temp, 1);
        rt_thread_mdelay(100);

        temp[0] = RTC_DEC2BCD(55);
        temp[1] = RTC_DEC2BCD(59);
        temp[2] = RTC_DEC2BCD(23);
        temp[3] = RTC_DEC2BCD(1);
        temp[4] = RTC_DEC2BCD(3);
        temp[5] = RTC_DEC2BCD(1);
        temp[6] = RTC_DEC2BCD(20);
        write_regs(i2c_bus, PFC8563_REG_SEC, temp, PFC8563_TIME_LEN);
        rt_thread_mdelay(100);
        initialized = RT_TRUE;
    }
}

static void serial_thread_entry(void *parameter)
{
    rt_uint8_t time[16];

    memset(time, 0, 16);
    rt_thread_mdelay(500);
    rt_thread_mdelay(500);

    while (1)
    {
        // if (RT_EOK == read_regs(i2c_bus, PFC8563_REG_SEC, time, PFC8563_TIME_LEN))
        if (RT_EOK == read_regs(i2c_bus, PFC8563_REG_SEC, time, 1))
        {
            time[0] &= 0x7FU;
            time[1] &= 0x7FU;
            time[2] &= 0x3FU;
            time[3] &= 0x3FU;
            time[4] &= 0x7U;
            time[5] &= 0x1FU;
            time[6] &= 0xFFU;
            /* Print current date and time */
            rt_kprintf("Time: 20%02d/%02d/%02d %02d:%02d:%02d\n", RTC_BCD2DEC(time[6]), RTC_BCD2DEC(time[5]),
                       RTC_BCD2DEC(time[3]), RTC_BCD2DEC(time[2]), RTC_BCD2DEC(time[1]), RTC_BCD2DEC(time[0]));
        }
        else
        {
            rt_kprintf("Get time failed!\n");
        }
        rt_thread_mdelay(100);
    }
}

void i2c_pcf8563_sample(int argc, char *argv[])
{
    char bus_name[RT_NAME_MAX];

    if (argc == 2)
    {
        rt_strncpy(bus_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(bus_name, PFC8563_I2C_BUS_NAME, RT_NAME_MAX);
    }

    if (!initialized)
    {
        /* 传感器初始化 */
        pcf8563_init(bus_name);
    }
    if (initialized)
    {
        /* 创建 serial 线程 */
        rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);
        /* 创建成功则启动线程 */
        if (thread != RT_NULL)
        {
            rt_thread_startup(thread);
        }
        else
        {
            rt_kprintf("startup thread failed!\n");
        }
    }
    else
    {
        rt_kprintf("initialize sensor failed!\n");
    }
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(i2c_pcf8563_sample, i2c aht10 sample);

#endif
