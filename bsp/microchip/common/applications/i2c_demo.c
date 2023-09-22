/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date        Author    Email                    Notes
 * 2022-04-16  Kevin.Liu kevin.liu.mchp@gmail.com First Release
 */

#include <rtthread.h>

#include <atmel_start.h>

#include "i2c_demo.h"

#ifdef SAM_I2C_EXAMPLE

#define I2C_AT24MAC_PGMAXSZ  (16+1)
#define CONF_AT24MAC_ADDRESS  0x57

/**
 * @brief    Call this function will run I2C test code.
 *
 * @note     Test code will try to read/write external EEPROM.
 *
 * @param    None.
 *
 * @return   RT_OK or -RT_ERROR.
 */

rt_err_t i2c_demo_run(void)
{
    rt_uint8_t addr = 0x20;
    rt_int32_t len;
    rt_uint8_t i2ctx[I2C_AT24MAC_PGMAXSZ];
    rt_uint8_t i2crx[I2C_AT24MAC_PGMAXSZ];

    for (len = 1; len < I2C_AT24MAC_PGMAXSZ; len++)
    {
        i2ctx[len] = (rt_uint8_t)(len + 0x20);
    }

    /* enable I2C master and set slave address before use I2C driver module */
    i2c_m_sync_enable(&I2C_0);
    i2c_m_sync_set_slaveaddr(&I2C_0, CONF_AT24MAC_ADDRESS, I2C_M_SEVEN);

    /* write 16bytes data to address 0x20 - I2C slave address + random address + write data[0]...[n] */
    i2ctx[0] = addr; /* Refer to AT24MAC data sheet, first byte is page address. */
    io_write(&(I2C_0.io), i2ctx, I2C_AT24MAC_PGMAXSZ);

    /* Refer to data sheet, for random read, should send read address first. */
    io_write(&(I2C_0.io), &addr, 1);

    /* Then start I2C read after send I2C slave address first */
    io_read(&(I2C_0.io), &i2crx[1], 16);
#ifndef RT_USING_FINSH
    rt_kprintf("i2crx[0]=0x%02X i2crx[15]=0x%02X\r\n", i2crx[0], i2crx[15]);
#endif

    return RT_EOK;
}
#endif

/*@}*/
