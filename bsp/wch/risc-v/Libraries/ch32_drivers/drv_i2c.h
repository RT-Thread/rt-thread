//
// Created by 12942 on 2024/3/15.
//

#ifndef __DRV_I2C_H_
#define __DRV_I2C_H_

#include <rtthread.h>
#include <rtdevice.h>

struct i2c_bus_device
{
    struct rt_i2c_bus_device parent;
    I2C_TypeDef *periph;
};

int rt_hw_i2c_init(void);

#endif