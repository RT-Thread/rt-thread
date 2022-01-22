/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-22     Magicoe      The first version for LPC55S6x
 */

#include <rthw.h>
#include <rtdevice.h>
#include <rtthread.h>

#include "rtconfig.h"
#include "drv_mma8562.h"

enum _mma8562_i2c_constants
{
    kMMA8562_ADDR = 0x1D,
    kMMA8562_ADDR_With_SAO_Set = kMMA8562_ADDR | 1
};

#define MMA8562_I2CBUS_NAME  "i2c4"

static struct rt_i2c_bus_device *mma8562_i2c_bus;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////


rt_err_t mma8562_read_reg(rt_uint8_t reg, rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = kMMA8562_ADDR;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = &reg;
    msgs[0].len   = 1;

    msgs[1].addr  = kMMA8562_ADDR;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf   = buf;
    msgs[1].len   = len;

    if (rt_i2c_transfer(mma8562_i2c_bus, msgs, 2) == 2)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

rt_err_t mma8562_write_reg(rt_uint8_t reg, rt_uint8_t data)
{
    rt_uint8_t buf[2];

    buf[0] = reg;
    buf[1] = data;

    if (rt_i2c_master_send(mma8562_i2c_bus, kMMA8562_ADDR, 0, buf ,2) == 2)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <rtdevice.h>

void get_mma8562(uint8_t data)
{
    volatile acceleration_t accel;

    uint8_t ucVal1 = 0;
    uint8_t ucVal2 = 0;
    uint8_t ucStatus = 0;

    do {
       mma8562_read_reg(kMMA8562_STATUS, 1, &ucStatus);
    } while (!(ucStatus & 0x08));

    mma8562_read_reg(kMMA8562_OUT_X_MSB, 1, &ucVal1);
    mma8562_read_reg(kMMA8562_OUT_X_LSB, 1, &ucVal2);

    accel.x = ucVal1*256 +ucVal2;

    mma8562_read_reg(kMMA8562_OUT_Y_MSB, 1, &ucVal1);
    mma8562_read_reg(kMMA8562_OUT_Y_LSB, 1, &ucVal2);
    accel.y = ucVal1*256 +ucVal2;

    mma8562_read_reg(kMMA8562_OUT_Z_MSB, 1, &ucVal1);
    mma8562_read_reg(kMMA8562_OUT_Z_LSB, 1, &ucVal2);
    accel.z = ucVal1*256 +ucVal2;

    rt_kprintf("*** MMA8562 X %d, Y %d, Z %d\r\n", (accel.x), (accel.y), (accel.z) );
}
FINSH_FUNCTION_EXPORT(get_mma8562, get mma8562. e.g: get_mma8562(0))
#endif

int mma8562_hw_init(void)
{
    // Init the I2C port.
    // Should be init in startup
    uint8_t val = 0;

    mma8562_i2c_bus = rt_i2c_bus_device_find(MMA8562_I2CBUS_NAME);  /*  */

    // Read WHO_AM_I register.
    mma8562_read_reg(kMMA8562_WHO_AM_I, 1, &val);
    if (val != kMMA8562_WHO_AM_I_Device_ID)
    {
        rt_kprintf("MMA8562: Unexpected result from WHO_AM_I (0x%02x)\n", val);
        return RT_ERROR;
    }

    /*  please refer to the "example FXOS8700CQ Driver Code" in FXOS8700 datasheet. */
    /*  write 0000 0000 = 0x00 to accelerometer control register 1 */
    /*  standby */
    /*  [7-1] = 0000 000 */
    /*  [0]: active=0 */
    val = 0;
    mma8562_write_reg( kMMA8562_CTRL_REG1, val);

    /*  write 0000 0001= 0x01 to XYZ_DATA_CFG register */
    /*  [7]: reserved */
    /*  [6]: reserved */
    /*  [5]: reserved */
    /*  [4]: hpf_out=0 */
    /*  [3]: reserved */
    /*  [2]: reserved */
    /*  [1-0]: fs=01 for accelerometer range of +/-4g range with 0.488mg/LSB */
    /*  databyte = 0x01; */
    val = 0x01;
    mma8562_write_reg(kMMA8562_XYZ_DATA_CFG, val);

    /*  write 0000 1101 = 0x0D to accelerometer control register 1 */
    /*  [7-6]: aslp_rate=00 */
    /*  [5-3]: dr=001 for 200Hz data rate (when in hybrid mode) */
    /*  [2]: lnoise=1 for low noise mode */
    /*  [1]: f_read=0 for normal 16 bit reads */
    /*  [0]: active=1 to take the part out of standby and enable sampling */
    /*   databyte = 0x0D; */
    val = 0x0D;
    mma8562_write_reg(kMMA8562_CTRL_REG1, val);

    return 0;
}

INIT_DEVICE_EXPORT(mma8562_hw_init);


////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
