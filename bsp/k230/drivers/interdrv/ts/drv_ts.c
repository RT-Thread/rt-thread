/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "drv_ts.h"
#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#ifdef RT_USING_POSIX
#include <dfs_posix.h>
#include <dfs_poll.h>
#include <posix_termios.h>
#endif

#include "math.h"
#include "rtdbg.h"
#include "board.h"
#include <riscv_io.h>
#include "ioremap.h"

// Register offsets
#define REG_TSENW_OFFSET          0x000
#define REG_TSENR_OFFSET          0x004

// Bit positions for REG_TSENW
#define TSENW_TS_TEST_EN_POS      6
#define TSENW_TS_TRIM_POS         2
#define TSENW_TS_CONV_MODE_POS    1
#define TSENW_TS_EN_POS           0

// Bit positions for REG_TSENR
#define TSENR_TS_DOUT_VALID_POS   12
#define TSENR_TS_DOUT_MASK        0xFFF

static struct rt_mutex ts_mutex;
static uint8_t ts_trim = 8;
static uint8_t ts_mode = RT_DEVICE_TS_CTRL_MODE_CONTINUUOS;
static void *ts_base_addr = RT_NULL;

static rt_err_t tsensor_start(void)
{
    uint32_t reg_val;

    if (ts_base_addr == RT_NULL)
        return -RT_ERROR;

    reg_val = readl(ts_base_addr + REG_TSENW_OFFSET);

    if (RT_DEVICE_TS_CTRL_MODE_CONTINUUOS == ts_mode)
        reg_val |= (1 << TSENW_TS_CONV_MODE_POS);
    else
        reg_val &= ~(1 << TSENW_TS_CONV_MODE_POS);

    reg_val |= (1 << TSENW_TS_EN_POS);

    writel(reg_val, ts_base_addr + REG_TSENW_OFFSET);

    return RT_EOK;
}

static rt_err_t tsensor_stop(void)
{
    if (ts_base_addr == RT_NULL)
        return -RT_ERROR;

    uint32_t reg_val = readl(ts_base_addr + REG_TSENW_OFFSET);
    reg_val &= ~(1 << TSENW_TS_EN_POS);
    writel(reg_val, ts_base_addr + REG_TSENW_OFFSET);

    return RT_EOK;
}

static int tsensor_read_data(uint16_t *data, uint32_t timeout_ms)
{
    if (ts_base_addr == RT_NULL || data == RT_NULL) // Ensure base address is set
        return -RT_ERROR;

    uint32_t max_attempts = timeout_ms; // Max attempts for the given timeout in ms

    for (uint32_t attempt = 0; attempt < max_attempts; attempt++)
    {
        // Check if the data is valid
        if ((readl(ts_base_addr + REG_TSENR_OFFSET) >> TSENR_TS_DOUT_VALID_POS) & 0x1)
        {
            // Read the 12-bit temperature data
            *data = readl(ts_base_addr + REG_TSENR_OFFSET) & TSENR_TS_DOUT_MASK;
            return RT_EOK; // Success
        }

        // Delay before next polling attempt
        rt_thread_mdelay(1); // Delay in microseconds
    }

    return -RT_ETIMEOUT; // Timeout error
}

static double tsensor_calculate_temperature(uint16_t data)
{
    return (1e-10 * pow(data, 4) * 1.01472
            - 1e-6 * pow(data, 3) * 1.10063
            + 4.36150 * 1e-3 * pow(data, 2)
            - 7.10128 * data
            + 3565.87);
}

static rt_err_t tsensor_init(void)
{
    if (ts_base_addr == RT_NULL)
    {
        return -RT_ERROR;
    }

    if (RT_EOK != rt_mutex_take(&ts_mutex, rt_tick_from_millisecond(500)))
    {
        LOG_E("%s mutex take timeout.\n", __func__);
        return -RT_ETIMEOUT;
    }

    uint32_t reg_val = readl(ts_base_addr + REG_TSENW_OFFSET);
    reg_val &= ~(0xF << TSENW_TS_TRIM_POS);
    reg_val |= (ts_trim << TSENW_TS_TRIM_POS);
    writel(reg_val, ts_base_addr + REG_TSENW_OFFSET);

    rt_mutex_release(&ts_mutex);

    return RT_EOK;
}


static rt_err_t k230_tsensor_set_trim(uint8_t trim)
{
    if(RT_EOK != rt_mutex_take(&ts_mutex, rt_tick_from_millisecond(500)))
    {
        LOG_E("%s mutex take timeout.\n");
        return -RT_ETIMEOUT;
    }

    // Ensure the trim_value is within range (4 bits)
    ts_trim = trim & 0xF;
    rt_mutex_release(&ts_mutex);
    tsensor_init();
    return RT_EOK;
}

static uint8_t k230_tsensor_get_trim(void)
{
    uint8_t temp;

    if(RT_EOK != rt_mutex_take(&ts_mutex, rt_tick_from_millisecond(500)))
    {
        LOG_E("%s mutex take timeout.\n");
        return -RT_ETIMEOUT;
    }

    temp = ts_trim;

    rt_mutex_release(&ts_mutex);

    return temp;
}

static rt_err_t k230_tsensor_set_mode(uint8_t mode)
{
    if(RT_EOK != rt_mutex_take(&ts_mutex, rt_tick_from_millisecond(500)))
    {
        LOG_E("%s mutex take timeout.\n");
        return -RT_ETIMEOUT;
    }
    ts_mode = mode;
    rt_mutex_release(&ts_mutex);
    return RT_EOK;
}

static uint8_t k230_tsensor_get_mode(void)
{
    uint8_t temp;

    if(RT_EOK != rt_mutex_take(&ts_mutex, rt_tick_from_millisecond(500)))
    {
        LOG_E("%s mutex take timeout.\n");
        return -RT_ETIMEOUT;
    }

    temp = ts_mode;
    rt_mutex_release(&ts_mutex);
    return temp;
}

static rt_err_t k230_tsensor_read_temp(double *temp)
{
    uint16_t data;
    rt_err_t ret = RT_EOK;
    if (RT_EOK != rt_mutex_take(&ts_mutex, rt_tick_from_millisecond(500)))
    {
        LOG_E("%s mutex take timeout.\n");
        return -RT_ETIMEOUT;
    }

    ret = tsensor_start();
    if (ret != RT_EOK)
    {
        return ret;
    }

    rt_thread_mdelay(10);

    if (0x00 == tsensor_read_data(&data, 100))
    {
        *((double *)temp) = tsensor_calculate_temperature(data);
        tsensor_stop();
        rt_mutex_release(&ts_mutex);
        return RT_EOK;
    }
    else
    {
        tsensor_stop();
        rt_mutex_release(&ts_mutex);
        return -RT_ERROR;
    }
}

static rt_err_t ts_device_open(rt_device_t dev, rt_uint16_t oflag)
{
    rt_err_t ret;

    ret = tsensor_init();
    return ret;
}

static rt_err_t ts_device_close(rt_device_t dev)
{
    rt_err_t ret;
    ret = tsensor_stop();
    return ret;
}

static rt_ssize_t ts_device_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_err_t ret;

    if (sizeof(double) != size)
    {
        LOG_E("%s invalid buffer size %u\n", __func__, size);
        return -RT_ERROR;
    }

    ret = k230_tsensor_read_temp((double *)buffer);
    if (ret != 0x00)
    {
        return -RT_ERROR;
    }
    return sizeof(double);
}

static rt_err_t ts_device_control(rt_device_t dev, int cmd, void *args)
{
    uint8_t trim_val = k230_tsensor_get_trim();
    uint8_t work_mode = k230_tsensor_get_mode();
    rt_err_t ret = RT_EOK;

    switch(cmd)
    {
        case RT_DEVICE_TS_CTRL_SET_MODE:
            work_mode = *(uint8_t *)args;
            ret = k230_tsensor_set_mode(work_mode);
            break;
        case RT_DEVICE_TS_CTRL_GET_MODE:
            *(uint8_t *)args = work_mode;
            break;
        case RT_DEVICE_TS_CTRL_SET_TRIM:
            trim_val = *(uint8_t *)args;
            ret = k230_tsensor_set_trim(trim_val);
            break;
        case RT_DEVICE_TS_CTRL_GET_TRIM:
            *(uint8_t *)args = trim_val;
            break;
        default:
            LOG_E("%s unsupported cmd 0x%x\n", __func__, cmd);
            ret = -RT_ERROR;
            break;
    }

    return ret;
}

static struct rt_device ts_device;

static const struct rt_device_ops ts_ops =
{
    .open    = ts_device_open,
    .close   = ts_device_close,
    .read    = ts_device_read,
    .control = ts_device_control
};

static rt_err_t register_ts_device(void)
{
    rt_device_t device;
    rt_err_t ret = RT_EOK;

    device = &ts_device;

#ifdef RT_USING_DEVICE_OPS
    device->ops = &ts_ops;
#else
    device->init       =     RT_NULL;
    device->open       =     ts_device_open;
    device->close      =     ts_device_close;
    device->read       =     ts_device_read;
    device->write      =     RT_NULL;
    device->control    =     ts_device_control;
#endif

    ret = rt_device_register(device, "ts", RT_DEVICE_FLAG_RDWR);
    if(ret != RT_EOK)
    {
        LOG_E("ts device register fail\n");
        return -RT_ERROR;
    }
    return ret;
}

static int rt_hw_ts_init(void)
{
    ts_base_addr = rt_ioremap((void *)TS_BASE_ADDR, TS_IO_SIZE);
    if (ts_base_addr == RT_NULL)
    {
        LOG_E("ts ioremap error\n");
        return -RT_ERROR;
    }
    if (RT_EOK != register_ts_device())
    {
        LOG_E("ts device register error\n");
        return -RT_ERROR;
    }
    if (RT_EOK != rt_mutex_init(&ts_mutex, "dev_ts", RT_IPC_FLAG_PRIO))
    {
        LOG_E("ts mutex init error\n");
        return -RT_ERROR;
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_ts_init);