/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *2023-03-28      Zxy          first version
 */

#include "drv_hw_i2c.h"
#include "driver/i2c.h"//bsp/ESP32_C3/packages/ESP-IDF-latest/components/driver/include/driver/i2c.h
#include "hal/i2c_types.h"//bsp/ESP32_C3/packages/ESP-IDF-latest/tools/mocks/hal/include/hal/i2c_types.h
#include "esp_err.h"
//#include "portmacro.h"//bsp/ESP32_C3/packages/FreeRTOS_Wrapper-latest/FreeRTOS/portable/rt-thread/portmacro.h
#ifdef BSP_USING_HW_I2C
struct esp32_i2c
{
    struct rt_i2c_bus_device bus;

    i2c_config_t *base;

    char *device_name;
};

// #if defined(BSP_USING_I2C0)
static struct esp32_i2c i2c0 = {0};
// #endif

static rt_size_t _master_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    i2c_cmd_handle_t cmd;//创建流程
    rt_size_t ret = (0);
    rt_uint32_t index = 0;
    // struct esp32_i2c *esp32_i2c = RT_NULL;
    struct rt_i2c_msg *msg = RT_NULL;
    i2c_rw_t direction;//w-0 r-1
    esp_err_t result = ESP_OK;

    RT_ASSERT(bus != RT_NULL);

    // esp32_i2c = (struct esp32_i2c *)bus;

    for(index = 0; index < num; index++)
    {
        msg = &msgs[index];
        direction = ((msg->flags & RT_I2C_RD) ? I2C_MASTER_READ : I2C_MASTER_WRITE);

        if (!(msg->flags & RT_I2C_NO_START))
        {
            /* Start condition and slave address. */
            cmd = i2c_cmd_link_create();//创建流程
            i2c_master_start(cmd);//启动流程录入
            result = i2c_master_write_byte(cmd, msg->addr << 1 | WRITE_BIT, ACK_CHECK_EN);//发送起始信号和从设备地址
            i2c_master_stop(cmd);//流程录入完毕
            ret = i2c_master_cmd_begin(I2C_NUMBER(0), cmd, 1000 / portTICK_PERIOD_MS);//执行流程
            i2c_cmd_link_delete(cmd);//删除流程任务
            if (ret != ESP_OK) return ret;
        }

        if (result == ESP_OK)
        {
            if (direction == I2C_MASTER_WRITE)
            {
                /* Transmit data. */
                cmd = i2c_cmd_link_create();//创建流程
                i2c_master_start(cmd);//启动流程录入
                result = i2c_master_write_byte(cmd, msg->buf, ACK_CHECK_EN);
                i2c_master_stop(cmd);//流程录入完毕
                ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);//执行流程
                i2c_cmd_link_delete(cmd);//删除流程任务
            }
            else
            {
                /* Receive Data. */
                cmd = i2c_cmd_link_create();//创建流程
                i2c_master_start(cmd);//启动流程录入
                result = i2c_master_read_byte(cmd, msg->buf, ACK_VAL);
                i2c_master_stop(cmd);//流程录入完毕
                ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);//执行流程
                i2c_cmd_link_delete(cmd);//删除流程任务
            }
        }
    }

    if (result == ESP_OK)
    {
        ret = index;
    }

    return ret;
}

static rt_size_t _slave_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    return -RT_ENOSYS;
}

static rt_err_t _i2c_bus_control(struct rt_i2c_bus_device *bus, int cmd, void *args)
{
    return -RT_EINVAL;
}

static const struct rt_i2c_bus_device_ops i2c_ops =
{
    _master_xfer,
    _slave_xfer,
    _i2c_bus_control,
};

int rt_hw_i2c_init(void)
{
    i2c0.base = &i2c0;
    i2c0.device_name = "i2c0";
    i2c0.bus.ops = &i2c_ops;
    int i2c_master_port = I2C_MASTER_NUM;//iic0
        i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
        // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
    };

    i2c_param_config(i2c_master_port, &conf);//配置完成
    i2c_driver_install(i2c_master_port, conf.mode, 0, 0, 0);// I2C 设备的初始化
    rt_i2c_bus_device_register(&i2c0.bus, i2c0.device_name);
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);
#endif /* RT_USING_I2C */
