/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-13     Ran          FXL8974 accelerometer sample for RT1180 CM33 EVK
 *
 * The FXL8974 is connected to LPI2C2 (GPIO_AON_15/16) on the RT1180 EVK.
 * 7-bit I2C address: 0x18 (SA0=0) or 0x19 (SA0=1).
 *
 * Usage (MSH):
 *   fxl8974_sample          -- scan i2c2 and read 10 accel samples
 *   fxl8974_scan i2c2       -- scan a bus for any device
 */

#include <rtthread.h>
#include <rtdevice.h>

#define FXL8974_BUS_NAME "i2c2"
#define FXL8974_ADDR     0x19U   /* 7-bit address, SA0 pin = VCC */

/* DMA on RT1180 CM33 cannot access DTCM (stack/heap).
 * A static global array is placed in SRAM/OCRAM by the linker,
 * which is accessible by DMA3. */
#define FXL8974_DMA_BUF_LEN 8U
static rt_uint8_t fxl8974_dma_rx[FXL8974_DMA_BUF_LEN];

/* Register map */
#define FXL8974_REG_STATUS  0x00U
#define FXL8974_REG_OUT_X_L 0x04U
#define FXL8974_REG_WHOAMI  0x13U
#define FXL8974_REG_CTRL1   0x15U
#define FXL8974_REG_CTRL2   0x16U
#define FXL8974_REG_CTRL3   0x17U
#define FXL8974_REG_CTRL4   0x18U

#define FXL8974_WHOAMI_VAL 0x86U

/* Read one or more registers using two separate transfers (set ptr then read). */
static rt_err_t fxl8974_read(struct rt_i2c_bus_device *bus,
                             rt_uint8_t reg, rt_uint8_t *buf, rt_uint8_t len)
{
    struct rt_i2c_msg msg;

    /* Step 1: write register address to set internal pointer */
    msg.addr = FXL8974_ADDR;
    msg.flags = RT_I2C_WR;
    msg.buf = &reg;
    msg.len = 1;
    if (rt_i2c_transfer(bus, &msg, 1) != 1)
    {
        return -RT_ERROR;
    }

    /* Step 2: read data */
    msg.addr = FXL8974_ADDR;
    msg.flags = RT_I2C_RD;
    msg.buf = buf;
    msg.len = len;
    if (rt_i2c_transfer(bus, &msg, 1) != 1)
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}

static rt_err_t fxl8974_write(struct rt_i2c_bus_device *bus,
                              rt_uint8_t reg, rt_uint8_t val)
{
    rt_uint8_t tmp[2] = { reg, val };
    struct rt_i2c_msg msg;

    msg.addr = FXL8974_ADDR;
    msg.flags = RT_I2C_WR;
    msg.buf = tmp;
    msg.len = 2;
    if (rt_i2c_transfer(bus, &msg, 1) != 1)
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}

static void fxl8974_sample(int argc, char *argv[])
{
    struct rt_i2c_bus_device *bus;
    rt_uint8_t whoami = 0;
    rt_uint8_t status = 0;
    rt_uint8_t data[6];
    rt_int16_t x, y, z;
    int i;

    bus = rt_i2c_bus_device_find(FXL8974_BUS_NAME);
    if (bus == RT_NULL)
    {
        rt_kprintf("[fxl8974] bus %s not found\n", FXL8974_BUS_NAME);
        return;
    }

    /* Put sensor in standby before configuring */
    fxl8974_write(bus, FXL8974_REG_CTRL1, 0x00);
    rt_thread_mdelay(2);

    /* ODR 6.25 Hz, low-noise */
    fxl8974_write(bus, FXL8974_REG_CTRL3, 0x90);
    fxl8974_write(bus, FXL8974_REG_CTRL2, 0x00);
    fxl8974_write(bus, FXL8974_REG_CTRL4, 0x01);

    /* Activate */
    fxl8974_write(bus, FXL8974_REG_CTRL1, 0x01);
    rt_thread_mdelay(10);

    /* Verify WHOAMI */
    if (fxl8974_read(bus, FXL8974_REG_WHOAMI, &whoami, 1) != RT_EOK)
    {
        rt_kprintf("[fxl8974] WHOAMI read failed -- check wiring and address\n");
        return;
    }
    rt_kprintf("[fxl8974] WHOAMI = 0x%02X (expected 0x%02X) -- %s\n",
               whoami, FXL8974_WHOAMI_VAL,
               (whoami == FXL8974_WHOAMI_VAL) ? "OK" : "MISMATCH");
    if (whoami != FXL8974_WHOAMI_VAL)
    {
        return;
    }

    rt_kprintf("[fxl8974] reading 10 samples...\n");
    for (i = 0; i < 10; i++)
    {
        fxl8974_read(bus, FXL8974_REG_STATUS, &status, 1);
        /* Use the non-cacheable buffer for the 6-byte DMA read so that
         * DMA3 can access the buffer (DTCM is not accessible by DMA3). */
        rt_memset(fxl8974_dma_rx, 0, FXL8974_DMA_BUF_LEN);
        fxl8974_read(bus, FXL8974_REG_OUT_X_L, fxl8974_dma_rx, 6);

        x = (rt_int16_t)((fxl8974_dma_rx[1] << 8) | fxl8974_dma_rx[0]);
        y = (rt_int16_t)((fxl8974_dma_rx[3] << 8) | fxl8974_dma_rx[2]);
        z = (rt_int16_t)((fxl8974_dma_rx[5] << 8) | fxl8974_dma_rx[4]);

        rt_kprintf("[fxl8974] [%2d] status=0x%02X  x=%6d  y=%6d  z=%6d\n",
                   i, status, x, y, z);
        rt_thread_mdelay(160);  /* ~6.25 Hz ODR = 160 ms per sample */
    }
}
MSH_CMD_EXPORT(fxl8974_sample, FXL8974 accelerometer sample on i2c2);

/* Bus scanner utility */
static void fxl8974_scan(int argc, char *argv[])
{
    const char *bus_name = FXL8974_BUS_NAME;
    struct rt_i2c_bus_device *bus;
    rt_uint8_t addr;
    rt_uint8_t dummy;
    struct rt_i2c_msg msg;
    int found = 0;

    if (argc >= 2)
    {
        bus_name = argv[1];
    }

    bus = rt_i2c_bus_device_find(bus_name);
    if (bus == RT_NULL)
    {
        rt_kprintf("[scan] bus %s not found\n", bus_name);
        return;
    }

    rt_kprintf("[scan] scanning %s (0x08..0x77):\n", bus_name);
    for (addr = 0x08; addr < 0x78; addr++)
    {
        msg.addr = addr;
        msg.flags = RT_I2C_WR;
        msg.buf = &dummy;
        msg.len = 0;
        if (rt_i2c_transfer(bus, &msg, 1) == 1)
        {
            rt_kprintf("[scan]   0x%02X\n", addr);
            found++;
        }
    }
    if (found == 0)
    {
        rt_kprintf("[scan]   no devices found\n");
    }
    else
    {
        rt_kprintf("[scan]   %d device(s) found\n", found);
    }
}
MSH_CMD_EXPORT(fxl8974_scan, I2C bus scanner : fxl8974_scan[bus]);
