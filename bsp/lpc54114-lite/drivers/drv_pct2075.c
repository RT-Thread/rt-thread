/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "drv_pct2075.h" 

#define PCT2075_I2C_NAME "i2c4" 
#define PCT2075_I2C_ADDR (0x4C) 

static struct rt_i2c_bus_device *i2c_bus = RT_NULL; 

float pct2075_read(void)
{
    struct rt_i2c_msg msg = {0};
    rt_uint8_t buf[2] = {0};
    float data = -0.666666f;
    
    if(i2c_bus == RT_NULL)
    {
        return -0.666666f; 
    }
    
    msg.addr  = PCT2075_I2C_ADDR; 
    msg.flags = RT_I2C_RD;
    msg.len   = 2;
    msg.buf   = buf;

    if (rt_i2c_transfer(i2c_bus, &msg, 1) != 1)
    {
        rt_kprintf("I2C write data failed.\n");
        return data;
    }
    
    if((buf[0]&0x80) == 0x00)
    {
        data = ((float)(((buf[0]<<8) + buf[1])>>5) * 0.125f); 
    }
    else
    {
        data = 0x800 - ((buf[0]<<8) + buf[1]>>5 );
        data = -(((float)(data)) * 0.125f); 
    }
    
    return data;
}
MSH_CMD_EXPORT(pct2075_read, read pct2075 oC); 

int rt_hw_pct2075_init(void)
{
    rt_err_t ret = RT_EOK; 
    
    i2c_bus = rt_i2c_bus_device_find(PCT2075_I2C_NAME); 
    if(i2c_bus == RT_NULL)
    {
        rt_kprintf("I2c bus not find.\n"); 
        ret = (-RT_EIO); 
        goto __fail; 
    }
    
    return RT_EOK;

__fail:     
    return ret; 
}
INIT_DEVICE_EXPORT(rt_hw_pct2075_init); 
