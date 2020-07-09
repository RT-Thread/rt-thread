/*
 * File      : drv_i2c.c
 * This file is part of gkipc BSP for RT-Thread distribution.
 *
 * Copyright (c) 2016 Shanghai goke Microelectronics Co., Ltd.
 * All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Visit http://www.goke.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtdevice.h>
#include <rthw.h>
#include "drv_i2c.h"

#include "gtypes.h"

#include "platform.h"

#include "gd_i2c.h"

/*---------------------------------------------------------------------------*/
/* local defines                                                             */
/*---------------------------------------------------------------------------*/


//#define GK_I2C_DEBUG
#ifndef GK_I2C_DEBUG
#define I2C_PRINT_DBG(fmt, args...)
#define I2C_PRINT_ERR(fmt, args...) rt_kprintf(fmt, ##args);
#else
#define I2C_PRINT_DBG(fmt, args...) rt_kprintf(fmt, ##args);
#define I2C_PRINT_ERR(fmt, args...) rt_kprintf(fmt, ##args);
#endif


//*****************************************************************************
//*****************************************************************************
//** Local structures
//*****************************************************************************
//*****************************************************************************




//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************


//*****************************************************************************
//*****************************************************************************
//** Local Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local Functions Declaration
//*****************************************************************************
//*****************************************************************************





//*****************************************************************************
//*****************************************************************************
//** Local Functions
//*****************************************************************************
//*****************************************************************************

static int gk_i2c_init(struct gk_i2c_obj *i2c_obj)
{
    int ret = RT_EOK;

    ret = GD_I2C_Init((GD_I2C_INIT_PARAMS_S*)&i2c_obj->config.i2cInitParams);

    return ret;
}

static rt_size_t gk_i2c_xfer(struct rt_i2c_bus_device *dev,
                             struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    int ret;
    U8 address    = 0;
    U8* buffer    = NULL;
    U8* regbuffer = NULL;
    U32 regbytes  = 0;
    U32 bytes     = 0;

    struct gk_i2c_obj *i2c_obj = (struct gk_i2c_obj *)dev->priv;

    if (num < 2)
    {
        if (msgs[0].flags == RT_I2C_WR)
        {
            address = msgs[0].addr;
            buffer  = msgs[0].buf;
            bytes   = msgs[0].len;
            ret = GD_I2C_Write( (GD_HANDLE *)&i2c_obj->handle,address,buffer,bytes );
            if (ret != RT_EOK)
            {
                I2C_PRINT_ERR("[%s:%d]I2C Write error!\n",__func__,__LINE__);
                return RT_ERROR;
            }

        }
    }
    else
    {
        if ((msgs[0].flags == RT_I2C_WR) && (msgs[1].flags == RT_I2C_RD))
        {
            address    = msgs[0].addr;
            regbuffer  = msgs[0].buf;
            regbytes   = msgs[0].len;

            buffer     = msgs[1].buf;
            bytes      = msgs[1].len;
        }
        else if ((msgs[0].flags == RT_I2C_RD ) && (msgs[1].flags == RT_I2C_WR))
        {
            address    = msgs[1].addr;
            regbuffer  = msgs[1].buf;
            regbytes   = msgs[1].len;

            buffer     = msgs[0].buf;
            bytes      = msgs[0].len;
        }
        ret = GD_I2C_Read( (GD_HANDLE *)&i2c_obj->handle,(U8)address, (U8*)regbuffer,(U32)regbytes,(U8*) buffer, (U32)bytes );
        if (ret != RT_EOK)
        {
            I2C_PRINT_ERR("[%s:%d]I2C_Read error!\n",__func__,__LINE__);
            return RT_ERROR;
        }

    }

    return ret;
}


static const struct rt_i2c_bus_device_ops gk_i2c_ops = {
    .master_xfer = gk_i2c_xfer,
};

int gk_i2c_probe(void *priv_data)
{
    int ret;
    struct rt_i2c_bus_device *i2c_bus_dev;
    struct gk_i2c_obj *i2c_obj = (struct gk_i2c_obj *)priv_data;
    char i2c_dev_name[5]       = {0};

    i2c_bus_dev = (struct rt_i2c_bus_device *)rt_malloc(sizeof(struct rt_i2c_bus_device));
    rt_memset(i2c_bus_dev, 0, sizeof(struct rt_i2c_bus_device));
    i2c_bus_dev->ops = &gk_i2c_ops;

    rt_sprintf(i2c_dev_name, "%s%d", "i2c", i2c_obj->id);
    ret = rt_i2c_bus_device_register(i2c_bus_dev, i2c_dev_name);
    if (ret != RT_EOK)
    {
        I2C_PRINT_ERR("ERROR:rt_spi_bus_register failed, ret=%d\n", ret);
        return -RT_ENOMEM;
    }

    // priv struct init
    i2c_obj->lock = rt_mutex_create("i2c_mux", RT_IPC_FLAG_FIFO);

    gk_i2c_init(i2c_obj);

    return ret;
}


int gk_i2c_exit(void *priv_data)
{
    struct gk_i2c_obj *i2c_obj = (struct gk_i2c_obj *)priv_data;

    GD_I2C_Close((GD_HANDLE *)&i2c_obj->handle);
    GD_I2C_Exit();
    return 0;
}

struct gk_platform_driver i2c_driver_ops = {
    .name = "i2c", .probe = gk_i2c_probe, .remove = gk_i2c_exit,
};

void rt_hw_i2c_init(void)
{
    I2C_PRINT_DBG("%s start\n", __func__);
    gk_platform_driver_init(&i2c_driver_ops);
    I2C_PRINT_DBG("%s end\n", __func__);
    // fixme: never release?
}


//#define GK_TEST_I2C
#ifdef GK_TEST_I2C
static rt_err_t gk_i2c_test_read_reg(struct rt_i2c_bus_device *gk_i2c,
                                rt_uint16_t reg, rt_uint8_t *data)
{
    struct rt_i2c_msg msg[2];
    rt_uint8_t send_buf[2];
    rt_uint8_t recv_buf[1] = {0};

    I2C_PRINT_DBG("%s start\n", __func__);

    send_buf[0] = (reg & 0xFF);

    msg[0].addr  = 0x51;
    msg[0].flags = RT_I2C_WR;
    msg[0].len   = 1;
    msg[0].buf   = send_buf;

    msg[1].addr  = 0x51;
    msg[1].flags = RT_I2C_RD;
    msg[1].len   = 1;
    msg[1].buf   = recv_buf;

    rt_i2c_transfer(gk_i2c, msg, 2);
    *data = recv_buf[0];
    return RT_EOK;
}
static rt_err_t gk_i2c_test_write_reg(struct rt_i2c_bus_device *gk_i2c,
                                 rt_uint16_t reg, rt_uint8_t data)
{
    struct rt_i2c_msg msg;
    rt_uint8_t send_buf[3];

    I2C_PRINT_DBG("%s start\n", __func__);

    // send_buf[0] = ((reg >> 8) & 0xff);
    send_buf[1] = (reg & 0xFF);
    send_buf[2] = data;

    msg.addr  = 0x51;
    msg.flags = RT_I2C_WR;
    msg.len   = 2;
    msg.buf   = send_buf;

    rt_i2c_transfer(gk_i2c, &msg, 1);
    I2C_PRINT_DBG("%s end\n", __func__);
    return RT_EOK;
}

void i2c_test_sensor()
{
    struct rt_i2c_bus_device *gk_i2c;
    gk_i2c_obj_s i2c_obj;

    rt_uint8_t data[1] = {0x00};
    int ret = 0;
    gk_i2c = rt_i2c_bus_device_find("i2c1");

    GD_I2C_OPEN_PARAMS_S i2c_param;
    i2c_param.channel = GADI_I2C_CHANNEL_ONE;
    i2c_param.speed   = GADI_I2C_100KBPS;
    i2c_param.mode    = GADI_I2C_INTERRUPT;//GADI_I2C_NORMAL;

    i2c_obj.handle = 0;
    ret = GD_I2C_Open((GD_I2C_OPEN_PARAMS_S*)&i2c_param, &i2c_obj.handle);
    if (ret != 0)
    {
        I2C_PRINT_DBG("GD_I2C_Open error!\n");
        return -1;
    }
    gk_i2c.priv = &i2c_obj;

    gk_i2c_test_write_reg(gk_i2c, 0x04, 0x02);

    gk_i2c_test_read_reg(gk_i2c, 0x02, data);

    I2C_PRINT_DBG("data read from 0x3038 is 0x%x\r\n", data[0]);
    I2C_PRINT_DBG("%s end\n", __func__);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(i2c_test_sensor, sensor i2c test);
#endif


#endif /*GK_TEST_I2C end*/

