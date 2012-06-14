#ifndef __I2C_DEV_H__
#define __I2C_DEV_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RT_I2C_DEV_CTRL_10BIT        0x20
#define RT_I2C_DEV_CTRL_ADDR         0x21
#define RT_I2C_DEV_CTRL_TIMEOUT      0x22
#define RT_I2C_DEV_CTRL_RW           0x23

struct rt_i2c_priv_data
{
    struct rt_i2c_msg  *msgs;
    rt_size_t  number;
};

rt_err_t rt_i2c_bus_device_device_init(struct rt_i2c_bus_device* bus,
                                       const char* name);


#ifdef __cplusplus
}
#endif

#endif
