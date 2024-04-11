/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-20     wirano       first version
 */


#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>

#ifdef BSP_USING_I2C

#if defined(BSP_USING_I2C0) || defined(BSP_USING_I2C1) || defined(BSP_USING_I2C2) || defined(BSP_USING_I2C3)

#include "drv_i2c.h"
#include "inc/hw_memmap.h"
#include "i2c_config.h"

enum {
#ifdef BSP_USING_I2C0
    I2C0_INDEX,
#endif
#ifdef BSP_USING_I2C1
    I2C1_INDEX,
#endif
#ifdef BSP_USING_I2C2
    I2C2_INDEX,
#endif
#ifdef BSP_USING_I2C3
    I2C3_INDEX,
#endif
};

static struct tm4c123_i2c tm4c123_i2cs[] =
        {
#ifdef BSP_USING_I2C0
                I2C0_BUS_CONFIG,
#endif

#ifdef BSP_USING_I2C1
                I2C1_BUS_CONFIG,
#endif

#ifdef BSP_USING_I2C2
                I2C2_BUS_CONFIG,
#endif

#ifdef BSP_USING_I2C3
                I2C3_BUS_CONFIG,
#endif
        };


static rt_ssize_t tm4c123_i2c_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num);


struct rt_i2c_bus_device_ops tm4c123_i2c_ops =
        {
                tm4c123_i2c_xfer,
                RT_NULL,
                RT_NULL
        };


static rt_ssize_t tm4c123_i2c_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num) {
    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(msgs != RT_NULL);

    struct rt_i2c_msg *msg;
    struct tm4c123_i2c *i2c_info = (struct tm4c123_i2c *) bus;

    rt_err_t ret = -RT_ERROR;
    rt_uint32_t i;

    for (i = 0; i < num; i++) {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_ADDR_10BIT) {
            LOG_E("does not support 10bits address!\n");
        }

        if (msg->flags & RT_I2C_RD) {
            rt_uint8_t *data = msg->buf;

            ROM_I2CMasterSlaveAddrSet(i2c_info->base, msg->addr, true);

            if (msg->flags & RT_I2C_NO_START) {
                ROM_I2CMasterControl(i2c_info->base, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
                while (ROM_I2CMasterBusy(i2c_info->base));
                *data = ROM_I2CMasterDataGet(i2c_info->base);
            } else {
                ROM_I2CMasterControl(i2c_info->base, I2C_MASTER_CMD_BURST_RECEIVE_START);
                while (ROM_I2CMasterBusy(i2c_info->base));
                *data = ROM_I2CMasterDataGet(i2c_info->base);
            }

            if (msg->len > 1) {
                data++;

                for (int j = 1; j < msg->len - 1; ++j) {

                    ROM_I2CMasterControl(i2c_info->base, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
                    while (ROM_I2CMasterBusy(i2c_info->base));
                    *data = ROM_I2CMasterDataGet(i2c_info->base);
                    data++;
                }

                if (msg->flags & RT_I2C_NO_STOP) {
                    ROM_I2CMasterControl(i2c_info->base, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
                    while (ROM_I2CMasterBusy(i2c_info->base));
                    *data = ROM_I2CMasterDataGet(i2c_info->base);
                } else {
                    ROM_I2CMasterControl(i2c_info->base, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
                    while (ROM_I2CMasterBusy(i2c_info->base));
                    *data = ROM_I2CMasterDataGet(i2c_info->base);
                }
            }
        } else {
            rt_uint8_t *data = msg->buf;

            ROM_I2CMasterSlaveAddrSet(i2c_info->base, msg->addr, false);

            // use single send when data len = 1
            if (msg->len == 1) {
                if (msg->flags & RT_I2C_NO_START) {
                    ROM_I2CMasterDataPut(i2c_info->base, *data);
                    ROM_I2CMasterControl(i2c_info->base, I2C_MASTER_CMD_BURST_SEND_CONT);
                } else if (msg->flags & RT_I2C_NO_STOP) {
                    ROM_I2CMasterDataPut(i2c_info->base, *data);
                    ROM_I2CMasterControl(i2c_info->base, I2C_MASTER_CMD_BURST_SEND_CONT);
                } else {
                    ROM_I2CMasterControl(i2c_info->base, I2C_MASTER_CMD_SINGLE_SEND);
                    ROM_I2CMasterDataPut(i2c_info->base, *data);
                }
                while (ROM_I2CMasterBusy(i2c_info->base));
            // otherwise use burst send
            } else {
                if (msg->flags & RT_I2C_NO_START) {
                    ROM_I2CMasterDataPut(i2c_info->base, *data);
                    ROM_I2CMasterControl(i2c_info->base, I2C_MASTER_CMD_BURST_SEND_CONT);
                    while (ROM_I2CMasterBusy(i2c_info->base));
                } else {
                    ROM_I2CMasterDataPut(i2c_info->base, *data);
                    ROM_I2CMasterControl(i2c_info->base, I2C_MASTER_CMD_BURST_SEND_START);
                    while (ROM_I2CMasterBusy(i2c_info->base));
                }

                data++;

                for (int j = 1; j < msg->len - 1; ++j) {
                    ROM_I2CMasterDataPut(i2c_info->base, *data);
                    ROM_I2CMasterControl(i2c_info->base, I2C_MASTER_CMD_BURST_SEND_CONT);
                    while (ROM_I2CMasterBusy(i2c_info->base));
                    data++;
                }

                if (msg->flags & RT_I2C_NO_STOP) {
                    ROM_I2CMasterDataPut(i2c_info->base, *data);
                    ROM_I2CMasterControl(i2c_info->base, I2C_MASTER_CMD_BURST_SEND_CONT);
                } else {
                    ROM_I2CMasterDataPut(i2c_info->base, *data);
                    ROM_I2CMasterControl(i2c_info->base, I2C_MASTER_CMD_BURST_SEND_FINISH);
                }
                while (ROM_I2CMasterBusy(i2c_info->base));
            }

        }
    }
    ret = i;
    return ret;
}

int rt_hw_i2c_init(void) {
    rt_err_t ret = RT_EOK;

    i2c_hw_config();

    for (uint32_t i = 0; i < sizeof(tm4c123_i2cs) / sizeof(tm4c123_i2cs[0]); i++) {
        if (tm4c123_i2cs[i].clk_freq == 400000) {
            ROM_I2CMasterInitExpClk(tm4c123_i2cs[i].base, ROM_SysCtlClockGet(), RT_TRUE);
        } else {
            ROM_I2CMasterInitExpClk(tm4c123_i2cs[i].base, ROM_SysCtlClockGet(), RT_FALSE);
        }
        ROM_I2CMasterEnable(tm4c123_i2cs[i].base);

        tm4c123_i2cs[i].bus.ops = &tm4c123_i2c_ops;
        ret = rt_i2c_bus_device_register(&tm4c123_i2cs[i].bus, tm4c123_i2cs[i].bus_name);
        if (ret != RT_EOK) {
            LOG_E("rt i2c device %s register failed, status=%d\n", tm4c123_i2cs[i].bus_name, ret);
        }
    }

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* BSP_USING_I2C1 || BSP_USING_I2C2 || BSP_USING_I2C3 || BSP_USING_I2C4 */

#endif /* BSP_USING_I2C */

