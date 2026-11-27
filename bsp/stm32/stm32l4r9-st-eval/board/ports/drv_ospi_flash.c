/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-20     CliffLL      first version
 */

#include <board.h>
#include <drv_ospi.h>
#include <rtdevice.h>
#include <rthw.h>
#include <finsh.h>

#ifdef BSP_USING_OSPI_FLASH

#include "dev_spi_flash.h"
#include "dev_spi_flash_sfud.h"

static rt_err_t mx25lm51245g_read_configuration_register2_reg1(struct rt_ospi_device *device, rt_uint8_t *reg)
{
    rt_ssize_t ret;

    /* 0x718E read configuration register2 reg1 (address 00000000h) */
    rt_uint8_t instruction = 0x71;
    struct rt_ospi_message message = { 0 };
    rt_uint16_t ospi_instruction = 0x718E;
    uint8_t cr2_reg1[2] = { 0 };
    rt_uint8_t send_buf[5] = { 0 };
    send_buf[0] = instruction;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(reg != RT_NULL);

    if (device->ospi_mode != RT_OSPI_MODE_OFF)
    {
        /* set message struct */
        message.instruction.content = ospi_instruction;
        message.instruction.size = 16;
        message.instruction.ospi_lines = 8;
        message.instruction.dtrmode = (device->ospi_mode == RT_OSPI_MODE_DTR) ? 1 : 0;

        message.address.content = 0;
        message.address.size = 32;
        message.address.ospi_lines = 8;
        message.address.dtrmode = (device->ospi_mode == RT_OSPI_MODE_DTR) ? 1 : 0;

        message.alternate_bytes.content = 0;
        message.alternate_bytes.size = 0;
        message.alternate_bytes.ospi_lines = 0;
        message.alternate_bytes.dtrmode = 0;

        message.dummy_cycles = 6;

        message.parent.send_buf = RT_NULL;
        message.parent.recv_buf = cr2_reg1;
        message.parent.length = (device->ospi_mode == RT_OSPI_MODE_DTR) ? 2 : 1;
        message.parent.cs_release = 1;
        message.parent.cs_take = 1;
        message.ospi_data_lines = 8;
        message.ospi_data_dtrmode = (device->ospi_mode == RT_OSPI_MODE_DTR) ? 1 : 0;
        message.dqs_mode = (device->ospi_mode == RT_OSPI_MODE_DTR) ? 1 : 0;
        message.parent.next = RT_NULL;

        ret = rt_ospi_transfer_message(device, &message);
        if (ret != (rt_ssize_t)message.parent.length)
        {
            return -RT_EIO;
        }

        /* MX25LM51245G returns duplicated register data in OPI-DTR mode */
        if ((device->ospi_mode == RT_OSPI_MODE_DTR) && (cr2_reg1[0] != cr2_reg1[1]))
        {
            return -RT_EIO;
        }
    }
    else
    {
        ret = rt_ospi_send_then_recv(device, send_buf, 5, cr2_reg1, 1);
        if (ret != 1)
        {
            return -RT_EIO;
        }
    }
    *reg = cr2_reg1[0];

    return RT_EOK;
}

static rt_err_t mx25lm51245g_write_enable(struct rt_ospi_device *device)
{
    rt_ssize_t ret;
    struct rt_ospi_message message = { 0 };

    /* 0x06F9 write enable */
    rt_uint8_t instruction = 0x06;
    rt_uint16_t ospi_instruction = 0x06F9;

    if (device->ospi_mode != RT_OSPI_MODE_OFF)
    {
        /* set message struct */
        message.instruction.content = ospi_instruction;
        message.instruction.size = 16;
        message.instruction.ospi_lines = 8;
        message.instruction.dtrmode = (device->ospi_mode == RT_OSPI_MODE_DTR) ? 1 : 0;

        message.address.content = 0;
        message.address.size = 0;
        message.address.ospi_lines = 0;
        message.address.dtrmode = (device->ospi_mode == RT_OSPI_MODE_DTR) ? 1 : 0;

        message.alternate_bytes.content = 0;
        message.alternate_bytes.size = 0;
        message.alternate_bytes.ospi_lines = 0;
        message.alternate_bytes.dtrmode = 0;

        message.dummy_cycles = 0;

        message.parent.send_buf = RT_NULL;
        message.parent.recv_buf = RT_NULL;
        message.parent.length = 0;
        message.parent.cs_release = 1;
        message.parent.cs_take = 1;
        message.ospi_data_lines = 0;
        message.ospi_data_dtrmode = (device->ospi_mode == RT_OSPI_MODE_DTR) ? 1 : 0;
        message.dqs_mode = 0;
        message.parent.next = RT_NULL;

        ret = rt_ospi_transfer_message(device, &message);
    }
    else
    {
        ret = rt_ospi_send(device, &instruction, 1);
    }

    if (ret <= 0)
    {
        return -RT_EIO;
    }

    return RT_EOK;
}

static rt_err_t mx25lm51245g_enter_ospi_str_mode(struct rt_ospi_device *device)
{
    rt_uint8_t reg;
    rt_err_t result;
    rt_ssize_t ret;
    struct rt_ospi_message message = { 0 };

    /* 0x728D write configuration register2 */
    rt_uint8_t instruction = 0x72;
    rt_uint16_t ospi_instruction = 0x728D;

    /* write SOPI mode dummy cycles (0x07 set DC 6 cycles) */
    char write_cr2_reg3_buf[6] = { 0 };
    char dtr_cr2_reg3_buf[2] = { 0 };
    write_cr2_reg3_buf[0] = instruction;
    write_cr2_reg3_buf[3] = 0x03;
    write_cr2_reg3_buf[5] = 0x07;
    dtr_cr2_reg3_buf[0] = 0x07;
    dtr_cr2_reg3_buf[1] = 0x07;

    /* write configuration register2 reg1 enter ospi-str mode*/
    char write_cr2_reg1_buf[6] = { 0 };
    char dtr_cr2_reg1_buf[2] = { 0 };
    write_cr2_reg1_buf[0] = instruction;
    write_cr2_reg1_buf[5] = 0x01;
    dtr_cr2_reg1_buf[0] = 0x01;
    dtr_cr2_reg1_buf[1] = 0x01;

    result = mx25lm51245g_read_configuration_register2_reg1(device, &reg);
    if (result != RT_EOK)
    {
        return result;
    }

    if (reg == 0x02)
    {
        /* ospi-dtr to ospi-str */
        result = mx25lm51245g_write_enable(device);
        if (result != RT_EOK)
        {
            return result;
        }

        /* set message struct */
        message.instruction.content = ospi_instruction;
        message.instruction.size = 16;
        message.instruction.ospi_lines = 8;
        message.instruction.dtrmode = 1;

        message.address.content = 0x00000300;
        message.address.size = 32;
        message.address.ospi_lines = 8;
        message.address.dtrmode = 1;

        message.alternate_bytes.content = 0;
        message.alternate_bytes.size = 0;
        message.alternate_bytes.ospi_lines = 0;
        message.alternate_bytes.dtrmode = 0;

        message.dummy_cycles = 0;

        message.parent.send_buf = dtr_cr2_reg3_buf;
        message.parent.recv_buf = RT_NULL;
        message.parent.length = 2;
        message.parent.cs_release = 1;
        message.parent.cs_take = 1;
        message.ospi_data_lines = 8;
        message.ospi_data_dtrmode = 1;
        message.dqs_mode = 0;
        message.parent.next = RT_NULL;

        ret = rt_ospi_transfer_message(device, &message);
        if (ret != message.parent.length)
        {
            return -RT_EIO;
        }

        result = mx25lm51245g_write_enable(device);
        if (result != RT_EOK)
        {
            return result;
        }

        message.address.content = 0x00000000;
        message.parent.send_buf = dtr_cr2_reg1_buf;
        ret = rt_ospi_transfer_message(device, &message);
        if (ret != message.parent.length)
        {
            return -RT_EIO;
        }

        rt_thread_mdelay(10);
    }
    else if (reg == 0x00)
    {
        /* spi to ospi-str */
        result = mx25lm51245g_write_enable(device);
        if (result != RT_EOK)
        {
            return result;
        }

        ret = rt_ospi_send(device, write_cr2_reg3_buf, 6);
        if (ret != 6)
        {
            return -RT_EIO;
        }

        result = mx25lm51245g_write_enable(device);
        if (result != RT_EOK)
        {
            return result;
        }

        ret = rt_ospi_send(device, write_cr2_reg1_buf, 6);
        if (ret != 6)
        {
            return -RT_EIO;
        }

        rt_thread_mdelay(10);
    }


    device->config.dtr_mode = 0;
    result = rt_ospi_configure(device, &device->config);
    if (result != RT_EOK)
    {
        return result;
    }
    device->ospi_mode = RT_OSPI_MODE_STR;

    /* check if flash enter OPI-STR mode */
    result = mx25lm51245g_read_configuration_register2_reg1(device, &reg);
    if (result != RT_EOK)
    {
        return result;
    }
    if (reg != 0x01)
    {
        return -RT_EIO;
    }

    rt_kprintf("flash already enter ospi str mode\n");
    return RT_EOK;
}

static rt_err_t mx25lm51245g_enter_ospi_dtr_mode(struct rt_ospi_device *device)
{
    rt_uint8_t reg;
    rt_err_t result;
    rt_ssize_t ret;
    struct rt_ospi_message message = { 0 };
    /* 0x728D write configuration register2 */
    rt_uint8_t instruction = 0x72;
    rt_uint16_t ospi_instruction = 0x728D;

    /* write SOPI mode dummy cycles (0x07 set DC 6 cycles) */
    char write_cr2_reg3_buf[6] = { 0 };
    write_cr2_reg3_buf[0] = instruction;
    write_cr2_reg3_buf[3] = 0x03;
    write_cr2_reg3_buf[5] = 0x07;

    /* write configuration register2 reg1 enter ospi-str mode*/
    char write_cr2_reg1_buf[6] = { 0 };
    write_cr2_reg1_buf[0] = instruction;
    write_cr2_reg1_buf[5] = 0x02;

    result = mx25lm51245g_read_configuration_register2_reg1(device, &reg);
    if (result != RT_EOK)
    {
        return result;
    }

    if (reg == 0x01)
    {
        /* ospi-str to ospi-dtr */
        result = mx25lm51245g_write_enable(device);
        if (result != RT_EOK)
        {
            return result;
        }

        /* set message struct */
        message.instruction.content = ospi_instruction;
        message.instruction.size = 16;
        message.instruction.ospi_lines = 8;
        message.instruction.dtrmode = 0;

        message.address.content = 0x00000300;
        message.address.size = 32;
        message.address.ospi_lines = 8;
        message.address.dtrmode = 0;

        message.alternate_bytes.content = 0;
        message.alternate_bytes.size = 0;
        message.alternate_bytes.ospi_lines = 0;
        message.alternate_bytes.dtrmode = 0;

        message.dummy_cycles = 0;

        message.parent.send_buf = write_cr2_reg3_buf + 5;
        message.parent.recv_buf = RT_NULL;
        message.parent.length = 1;
        message.parent.cs_release = 1;
        message.parent.cs_take = 1;
        message.ospi_data_lines = 8;
        message.ospi_data_dtrmode = 0;
        message.dqs_mode = 0;
        message.parent.next = RT_NULL;

        ret = rt_ospi_transfer_message(device, &message);
        if (ret != message.parent.length)
        {
            return -RT_EIO;
        }

        result = mx25lm51245g_write_enable(device);
        if (result != RT_EOK)
        {
            return result;
        }

        message.address.content = 0x00000000;
        message.parent.send_buf = write_cr2_reg1_buf + 5;
        ret = rt_ospi_transfer_message(device, &message);
        if (ret != message.parent.length)
        {
            return -RT_EIO;
        }

        rt_thread_mdelay(10);
    }
    else if (reg == 0x00)
    {
        /* spi to ospi-dtr */
        result = mx25lm51245g_write_enable(device);
        if (result != RT_EOK)
        {
            return result;
        }

        ret = rt_ospi_send(device, write_cr2_reg3_buf, 6);
        if (ret != 6)
        {
            return -RT_EIO;
        }

        result = mx25lm51245g_write_enable(device);
        if (result != RT_EOK)
        {
            return result;
        }

        ret = rt_ospi_send(device, write_cr2_reg1_buf, 6);
        if (ret != 6)
        {
            return -RT_EIO;
        }

        rt_thread_mdelay(10);
    }


    device->config.dtr_mode = 1;
    result = rt_ospi_configure(device, &device->config);
    if (result != RT_EOK)
    {
        return result;
    }
    device->ospi_mode = RT_OSPI_MODE_DTR;

    /* check if flash enter OPI-DTR mode */
    result = mx25lm51245g_read_configuration_register2_reg1(device, &reg);
    if (result != RT_EOK)
    {
        return result;
    }
    if (reg != 0x02)
    {
        return -RT_EIO;
    }

    rt_kprintf("flash already enter ospi dtr mode\n");
    return RT_EOK;
}

static int rt_hw_ospi_flash_with_sfud_init(void)
{
    return rt_hw_ospi_device_attach("ospi1", "ospi10", mx25lm51245g_enter_ospi_str_mode, mx25lm51245g_enter_ospi_dtr_mode, RT_NULL);
}
INIT_DEVICE_EXPORT(rt_hw_ospi_flash_with_sfud_init);

#endif/* BSP_USING_OSPI_FLASH */
