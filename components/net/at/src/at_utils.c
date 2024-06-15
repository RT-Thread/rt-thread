/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-04-14     chenyong     first version
 * 2023-06-09     CX           optimize at_vprintfln interface
 */

#include <at.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * dump hex format data to console device
 *
 * @param name name for hex object, it will show on log header
 * @param buf hex buffer
 * @param size buffer size
 */
void at_print_raw_cmd(const char *name, const char *buf, rt_size_t size)
{
#define __is_print(ch)       ((unsigned int)((ch) - ' ') < 127u - ' ')
#define WIDTH_SIZE           32

    rt_size_t i, j;

    for (i = 0; i < size; i += WIDTH_SIZE)
    {
        rt_kprintf("[D/AT] %s: %04X-%04X: ", name, i, i + WIDTH_SIZE);
        for (j = 0; j < WIDTH_SIZE; j++)
        {
            if (i + j < size)
            {
                rt_kprintf("%02X ", (unsigned char)buf[i + j]);
            }
            else
            {
                rt_kprintf("   ");
            }
            if ((j + 1) % 8 == 0)
            {
                rt_kprintf(" ");
            }
        }
        rt_kprintf("  ");
        for (j = 0; j < WIDTH_SIZE; j++)
        {
            if (i + j < size)
            {
                rt_kprintf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
            }
        }
        rt_kprintf("\n");
    }
}

rt_weak rt_size_t at_utils_send(rt_device_t dev,
                                rt_off_t    pos,
                                const void *buffer,
                                rt_size_t   size)
{
    return rt_device_write(dev, pos, buffer, size);
}

rt_size_t at_vprintf(rt_device_t device, char *send_buf, rt_size_t buf_size, const char *format, va_list args)
{
    rt_size_t len = vsnprintf(send_buf, buf_size, format, args);
    if (len == 0)
    {
        return 0;
    }

#ifdef AT_PRINT_RAW_CMD
    at_print_raw_cmd("sendline", send_buf, len);
#endif

    return at_utils_send(device, 0, send_buf, len);
}

rt_size_t at_vprintfln(rt_device_t device, char *send_buf, rt_size_t buf_size, const char *format, va_list args)
{
    rt_size_t len = vsnprintf(send_buf, buf_size - 2, format, args);
    if (len == 0)
    {
        return 0;
    }

    send_buf[len++] = '\r';
    send_buf[len++] = '\n';

#ifdef AT_PRINT_RAW_CMD
    at_print_raw_cmd("sendline", send_buf, len);
#endif

    return at_utils_send(device, 0, send_buf, len);
}
