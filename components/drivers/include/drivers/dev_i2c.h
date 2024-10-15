/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2012-04-25     weety         first version
 * 2021-04-20     RiceChen      added support for bus control api
 */

#ifndef __DEV_I2C_H__
#define __DEV_I2C_H__

#include <rtthread.h>
/**
 * @addtogroup  Drivers          RTTHREAD Driver
 * @defgroup    I2C              I2C
 *
 * @brief       I2C driver api
 *
 * <b>Example</b>
 * @code {.c}
 * #include <rtthread.h>
 * #include <rtdevice.h>
 *
 * #define AHT10_I2C_BUS_NAME          "i2c1"  // 传感器连接的I2C总线设备名称
 * #define AHT10_ADDR                  0x38    // 从机地址
 * #define AHT10_CALIBRATION_CMD       0xE1    // 校准命令
 * #define AHT10_NORMAL_CMD            0xA8    // 一般命令
 * #define AHT10_GET_DATA              0xAC    // 获取数据命令
 *
 * static struct rt_i2c_bus_device *i2c_bus = RT_NULL;     // I2C总线设备句柄
 * static rt_bool_t initialized = RT_FALSE;                // 传感器初始化状态
 *
 * // 写传感器寄存器
 * static rt_err_t write_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t *data)
 * {
 *     rt_uint8_t buf[3];
 *     struct rt_i2c_msg msgs;
 *     rt_uint32_t buf_size = 1;
 *
 *     buf[0] = reg; //cmd
 *     if (data != RT_NULL)
 *     {
 *         buf[1] = data[0];
 *         buf[2] = data[1];
 *         buf_size = 3;
 *     }
 *
 *     msgs.addr = AHT10_ADDR;
 *     msgs.flags = RT_I2C_WR;
 *     msgs.buf = buf;
 *     msgs.len = buf_size;
 *
 *     // 调用I2C设备接口传输数据
 *     if (rt_i2c_transfer(bus, &msgs, 1) == 1)
 *     {
 *         return RT_EOK;
 *     }
 *     else
 *     {
 *         return -RT_ERROR;
 *     }
 * }
 *
 * // 读传感器寄存器数据
 * static rt_err_t read_regs(struct rt_i2c_bus_device *bus, rt_uint8_t len, rt_uint8_t *buf)
 * {
 *     struct rt_i2c_msg msgs;
 *
 *     msgs.addr = AHT10_ADDR;
 *     msgs.flags = RT_I2C_RD;
 *     msgs.buf = buf;
 *     msgs.len = len;
 *
 *     // 调用I2C设备接口传输数据
 *     if (rt_i2c_transfer(bus, &msgs, 1) == 1)
 *     {
 *         return RT_EOK;
 *     }
 *     else
 *     {
 *         return -RT_ERROR;
 *     }
 * }
 *
 * static void read_temp_humi(float *cur_temp, float *cur_humi)
 * {
 *     rt_uint8_t temp[6];
 *
 *     write_reg(i2c_bus, AHT10_GET_DATA, RT_NULL);      // 发送命令
 *     rt_thread_mdelay(400);
 *     read_regs(i2c_bus, 6, temp);                // 获取传感器数据
 *
 *     // 湿度数据转换
 *     *cur_humi = (temp[1] << 12 | temp[2] << 4 | (temp[3] & 0xf0) >> 4) * 100.0 / (1 << 20);
 *     // 温度数据转换
 *     *cur_temp = ((temp[3] & 0xf) << 16 | temp[4] << 8 | temp[5]) * 200.0 / (1 << 20) - 50;
 * }
 *
 * static void aht10_init(const char *name)
 * {
 *     rt_uint8_t temp[2] = {0, 0};
 *
 *     // 查找I2C总线设备，获取I2C总线设备句柄
 *     i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(name);
 *
 *     if (i2c_bus == RT_NULL)
 *     {
 *         rt_kprintf("can't find %s device!\n", name);
 *     }
 *     else
 *     {
 *         write_reg(i2c_bus, AHT10_NORMAL_CMD, temp);
 *         rt_thread_mdelay(400);
 *
 *         temp[0] = 0x08;
 *         temp[1] = 0x00;
 *         write_reg(i2c_bus, AHT10_CALIBRATION_CMD, temp);
 *         rt_thread_mdelay(400);
 *         initialized = RT_TRUE;
 *     }
 * }
 *
 * static void i2c_aht10_sample(int argc, char *argv[])
 * {
 *     float humidity, temperature;
 *     char name[RT_NAME_MAX];
 *
 *     humidity = 0.0;
 *     temperature = 0.0;
 *
 *     if (argc == 2)
 *     {
 *         rt_strncpy(name, argv[1], RT_NAME_MAX);
 *     }
 *     else
 *     {
 *         rt_strncpy(name, AHT10_I2C_BUS_NAME, RT_NAME_MAX);
 *     }
 *
 *     if (!initialized)
 *     {
 *         // 传感器初始化
 *         aht10_init(name);
 *     }
 *     if (initialized)
 *     {
 *         // 读取温湿度数据
 *         read_temp_humi(&temperature, &humidity);
 *
 *         rt_kprintf("read aht10 sensor humidity   : %d.%d %%\n", (int)humidity, (int)(humidity * 10) % 10);
 *         if( temperature >= 0 )
 *         {
 *             rt_kprintf("read aht10 sensor temperature: %d.%d°C\n", (int)temperature, (int)(temperature * 10) % 10);
 *         }
 *         else
 *         {
 *             rt_kprintf("read aht10 sensor temperature: %d.%d°C\n", (int)temperature, (int)(-temperature * 10) % 10);
 *         }
 *     }
 *     else
 *     {
 *         rt_kprintf("initialize sensor failed!\n");
 *     }
 * }
 * // 导出到 msh 命令列表中
 * MSH_CMD_EXPORT(i2c_aht10_sample, i2c aht10 sample);
 * @endcode
 *
 * @ingroup     Drivers
 */

/*!
 * @addtogroup I2C
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

#define RT_I2C_WR                0x0000    /*!< i2c wirte flag */
#define RT_I2C_RD               (1u << 0)  /*!< i2c read flag  */
#define RT_I2C_ADDR_10BIT       (1u << 2)  /*!< this is a ten bit chip address */
#define RT_I2C_NO_START         (1u << 4)  /*!< do not generate START condition */
#define RT_I2C_IGNORE_NACK      (1u << 5)  /*!< ignore NACK from slave */
#define RT_I2C_NO_READ_ACK      (1u << 6)  /* when I2C reading, we do not ACK */
#define RT_I2C_NO_STOP          (1u << 7)  /*!< do not generate STOP condition */

#define RT_I2C_DEV_CTRL_10BIT        (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x01)
#define RT_I2C_DEV_CTRL_ADDR         (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x02)
#define RT_I2C_DEV_CTRL_TIMEOUT      (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x03)
#define RT_I2C_DEV_CTRL_RW           (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x04)
#define RT_I2C_DEV_CTRL_CLK          (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x05)
#define RT_I2C_DEV_CTRL_UNLOCK       (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x06)
#define RT_I2C_DEV_CTRL_GET_STATE    (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x07)
#define RT_I2C_DEV_CTRL_GET_MODE     (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x08)
#define RT_I2C_DEV_CTRL_GET_ERROR    (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x09)

/**
 * @brief I2C Private Data
 */
struct rt_i2c_priv_data
{
    struct rt_i2c_msg  *msgs;
    rt_size_t  number;
};

/**
 * @brief I2C Message
 */
struct rt_i2c_msg
{
    rt_uint16_t addr;
    rt_uint16_t flags;
    rt_uint16_t len;
    rt_uint8_t  *buf;
};

struct rt_i2c_bus_device;

/**
 * @brief I2C Bus Device Operations
 */
struct rt_i2c_bus_device_ops
{
    rt_ssize_t (*master_xfer)(struct rt_i2c_bus_device *bus,
                             struct rt_i2c_msg msgs[],
                             rt_uint32_t num);
    rt_ssize_t (*slave_xfer)(struct rt_i2c_bus_device *bus,
                            struct rt_i2c_msg msgs[],
                            rt_uint32_t num);
    rt_err_t (*i2c_bus_control)(struct rt_i2c_bus_device *bus,
                                int cmd,
                                void *args);
};

/**
 * @brief I2C Bus Device
 */
struct rt_i2c_bus_device
{
    struct rt_device parent;
    const struct rt_i2c_bus_device_ops *ops;
    rt_uint16_t  flags;
    struct rt_mutex lock;
    rt_uint32_t  timeout;
    rt_uint32_t  retries;
    void *priv;
};

/**
 * @brief I2C Client
 */
struct rt_i2c_client
{
#ifdef RT_USING_DM
    struct rt_device parent;

    const char *name;
    const struct rt_i2c_device_id *id;
    const struct rt_ofw_node_id *ofw_id;
#endif
    struct rt_i2c_bus_device       *bus;
    rt_uint16_t                    client_addr;
};

#ifdef RT_USING_DM
struct rt_i2c_device_id
{
    char name[20];
    void *data;
};

struct rt_i2c_driver
{
    struct rt_driver parent;

    const struct rt_i2c_device_id *ids;
    const struct rt_ofw_node_id *ofw_ids;

    rt_err_t (*probe)(struct rt_i2c_client *client);
    rt_err_t (*remove)(struct rt_i2c_client *client);
    rt_err_t (*shutdown)(struct rt_i2c_client *client);
};

rt_err_t rt_i2c_driver_register(struct rt_i2c_driver *driver);
rt_err_t rt_i2c_device_register(struct rt_i2c_client *client);

#define RT_I2C_DRIVER_EXPORT(driver)  RT_DRIVER_EXPORT(driver, i2c, BUILIN)
#endif /* RT_USING_DM */

/**
 * @brief I2C Bus Device Initialization
 *
 * @param bus the I2C bus device
 * @param name the name of I2C bus device
 *
 * @return rt_err_t error code
 */
rt_err_t rt_i2c_bus_device_device_init(struct rt_i2c_bus_device *bus,
                                       const char               *name);

/**
 * @brief I2C Bus Device Register
 *
 * @param bus the I2C bus device
 * @param bus_name the name of I2C bus device
 *
 * @return rt_err_t error code
 */
rt_err_t rt_i2c_bus_device_register(struct rt_i2c_bus_device *bus,
                                    const char               *bus_name);

/**
 * @brief I2C Bus Device Find
 *
 * @param bus_name the name of I2C bus device
 *
 * @return rt_i2c_bus_device the I2C bus device
 */
struct rt_i2c_bus_device *rt_i2c_bus_device_find(const char *bus_name);

/**
 * @brief I2C data transmission.
 *
 * @param bus the I2C bus device
 * @param msgs the I2C message list
 * @param num the number of I2C message
 *
 * @return rt_ssize_t the actual length of transmitted
 */
rt_ssize_t rt_i2c_transfer(struct rt_i2c_bus_device *bus,
                          struct rt_i2c_msg         msgs[],
                          rt_uint32_t               num);

/**
 * @brief I2C Control
 *
 * @param bus the I2C bus device
 * @param cmd the I2C control command
 * @param args the I2C control arguments
 *
 * @return rt_err_t error code
 */
rt_err_t rt_i2c_control(struct rt_i2c_bus_device *bus,
                        int cmd,
                        void *args);

/**
 * @brief I2C Master Send
 *
 * @param bus the I2C bus device
 * @param addr the I2C slave address
 * @param flags the I2C flags
 * @param buf the I2C send buffer
 * @param count the I2C send buffer length
 *
 * @return rt_ssize_t the actual length of transmitted
 */
rt_ssize_t rt_i2c_master_send(struct rt_i2c_bus_device *bus,
                             rt_uint16_t               addr,
                             rt_uint16_t               flags,
                             const rt_uint8_t         *buf,
                             rt_uint32_t               count);

/**
 * @brief I2C Master Receive
 *
 * @param bus the I2C bus device
 * @param addr the I2C slave address
 * @param flags the I2C flags
 * @param buf the I2C receive buffer
 * @param count the I2C receive buffer length
 *
 * @return rt_ssize_t the actual length of received
 */
rt_ssize_t rt_i2c_master_recv(struct rt_i2c_bus_device *bus,
                             rt_uint16_t               addr,
                             rt_uint16_t               flags,
                             rt_uint8_t               *buf,
                             rt_uint32_t               count);

rt_inline rt_err_t rt_i2c_bus_lock(struct rt_i2c_bus_device *bus, rt_tick_t timeout)
{
    return rt_mutex_take(&bus->lock, timeout);
}

rt_inline rt_err_t rt_i2c_bus_unlock(struct rt_i2c_bus_device *bus)
{
    return rt_mutex_release(&bus->lock);
}

#ifdef __cplusplus
}
#endif

/*! @}*/

#endif
