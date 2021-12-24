/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-17     armink       first version.
 */


#include <rtthread.h>
#include <dfs_posix.h>
#include <lwip/apps/tftp_server.h>

static struct tftp_context ctx;

static void* tftp_open(const char* fname, const char* mode, u8_t write)
{
    int fd = -1;

    if (!rt_strcmp(mode, "octet"))
    {
        if (write)
        {
            fd = open(fname, O_WRONLY | O_CREAT, 0);
        }
        else
        {
            fd = open(fname, O_RDONLY, 0);
        }
    }
    else
    {
        rt_kprintf("tftp: No support this mode(%s).", mode);
    }

    return (void *) fd;
}

static int tftp_write(void* handle, struct pbuf* p)
{
    int fd = (int) handle;

    return write(fd, p->payload, p->len);
}

#if defined(RT_USING_FINSH)
#include <finsh.h>

static void tftp_server(uint8_t argc, char **argv)
{
    ctx.open = tftp_open;
    ctx.close = (void (*)(void *)) close;
    ctx.read = (int (*)(void *, void *, int)) read;
    ctx.write = tftp_write;

    if (tftp_init(&ctx) == ERR_OK)
    {
        rt_kprintf("TFTP server start successfully.\n");
    }
    else
    {
        rt_kprintf("TFTP server start failed.\n");
    }
}
FINSH_FUNCTION_EXPORT(tftp_server, start tftp server.);

MSH_CMD_EXPORT(tftp_server, start tftp server.);

#endif /* defined(RT_USING_FINSH) */
