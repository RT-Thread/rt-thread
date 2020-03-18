/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-09     Steven Liu   the first version
 */

#include <rtthread.h>
#include <ymodem.h>
#include <dfs_posix.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct custom_ctx
{
    struct rym_ctx parent;
    int fd;
    int flen;
    char fpath[DFS_PATH_MAX];
};

static enum rym_code _rym_recv_begin(
    struct rym_ctx *ctx,
    rt_uint8_t *buf,
    rt_size_t len)
{
    struct custom_ctx *cctx = (struct custom_ctx *)ctx;

    cctx->fpath[0] = '/';
    rt_strncpy(&(cctx->fpath[1]), (const char *)buf, len - 1);
    cctx->fd = open(cctx->fpath, O_CREAT | O_WRONLY | O_TRUNC, 0);
    if (cctx->fd < 0)
    {
        rt_err_t err = rt_get_errno();
        rt_kprintf("error creating file: %d\n", err);
        return RYM_CODE_CAN;
    }
    cctx->flen = atoi(1 + (const char *)buf + rt_strnlen((const char *)buf, len - 1));
    if (cctx->flen == 0)
        cctx->flen = -1;

    return RYM_CODE_ACK;
}

static enum rym_code _rym_recv_data(
    struct rym_ctx *ctx,
    rt_uint8_t *buf,
    rt_size_t len)
{
    struct custom_ctx *cctx = (struct custom_ctx *)ctx;

    RT_ASSERT(cctx->fd >= 0);
    if (cctx->flen == -1)
    {
        write(cctx->fd, buf, len);
    }
    else
    {
        int wlen = len > cctx->flen ? cctx->flen : len;
        write(cctx->fd, buf, wlen);
        cctx->flen -= wlen;
    }

    return RYM_CODE_ACK;
}

static enum rym_code _rym_recv_end(
    struct rym_ctx *ctx,
    rt_uint8_t *buf,
    rt_size_t len)
{
    struct custom_ctx *cctx = (struct custom_ctx *)ctx;

    RT_ASSERT(cctx->fd >= 0);
    close(cctx->fd);
    cctx->fd = -1;

    return RYM_CODE_ACK;
}

static enum rym_code _rym_send_begin(
    struct rym_ctx *ctx,
    rt_uint8_t *buf,
    rt_size_t len)
{
    struct custom_ctx *cctx = (struct custom_ctx *)ctx;
    struct stat file_buf;
    char insert_0 = '\0';
    rt_err_t err;

    cctx->fd = open(cctx->fpath, O_RDONLY);
    if (cctx->fd < 0)
    {
        err = rt_get_errno();
        rt_kprintf("error open file: %d\n", err);
        return RYM_ERR_FILE;
    }
    rt_memset(buf, 0, len);
    err = stat(cctx->fpath, &file_buf);
    if (err != RT_EOK)
    {
        rt_kprintf("error open file.\n");
        return RYM_ERR_FILE;
    }
    sprintf((char *)buf, "%s%c%ld", (char *) & (cctx->fpath[1]), insert_0, file_buf.st_size);

    return RYM_CODE_SOH;
}

static enum rym_code _rym_send_data(
    struct rym_ctx *ctx,
    rt_uint8_t *buf,
    rt_size_t len)
{
    struct custom_ctx *cctx = (struct custom_ctx *)ctx;
    rt_size_t read_size;
    int retry_read;

    read_size = 0;
    for (retry_read = 0; retry_read < 10; retry_read++)
    {
        read_size += read(cctx->fd, buf + read_size, len - read_size);
        if (read_size == len)
            break;
    }

    if (read_size < len)
    {
        rt_memset(buf + read_size, 0x1A, len - read_size);
        /* stage = RYM_STAGE_FINISHING */
        ctx->stage = 4;
    }

    return RYM_CODE_SOH;
}

static enum rym_code _rym_send_end(
    struct rym_ctx *ctx,
    rt_uint8_t *buf,
    rt_size_t len)
{
    rt_memset(buf, 0, len);

    return RYM_CODE_SOH;
}

static rt_err_t rym_download_file(rt_device_t idev)
{
    rt_err_t res;
    struct custom_ctx *ctx = rt_calloc(1, sizeof(*ctx));

    if (!ctx)
    {
        rt_kprintf("rt_malloc failed\n");
        return RT_ENOMEM;
    }
    ctx->fd = -1;
    RT_ASSERT(idev);
    res = rym_recv_on_device(&ctx->parent, idev, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                             _rym_recv_begin, _rym_recv_data, _rym_recv_end, 1000);
    rt_free(ctx);

    return res;
}

static rt_err_t rym_upload_file(rt_device_t idev, const char *file_path)
{
    rt_err_t res = 0;

    struct custom_ctx *ctx = rt_calloc(1, sizeof(*ctx));
    if (!ctx)
    {
        rt_kprintf("rt_malloc failed\n");
        return RT_ENOMEM;
    }
    ctx->fd = -1;
    rt_strncpy(ctx->fpath, file_path, DFS_PATH_MAX);
    RT_ASSERT(idev);
    res = rym_send_on_device(&ctx->parent, idev,
                             RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                             _rym_send_begin, _rym_send_data, _rym_send_end, 1000);
    rt_free(ctx);

    return res;
}

#ifdef RT_USING_FINSH
#include <finsh.h>

static rt_err_t ry(uint8_t argc, char **argv)
{
    rt_err_t res;
    rt_device_t dev;

    if (argc > 1)
        dev = rt_device_find(argv[1]);
    else
        dev = rt_console_get_device();
    if (!dev)
    {
        rt_kprintf("could not find device.\n");
        return -RT_ERROR;
    }
    res = rym_download_file(dev);

    return res;
}
MSH_CMD_EXPORT(ry, YMODEM Receive e.g: ry [uart0] default by console.);

static rt_err_t sy(uint8_t argc, char **argv)
{
    rt_err_t res;
    /* temporarily support 1 file*/
    const char *file_path;
    rt_device_t dev;

    if (argc > 2)
        dev = rt_device_find(argv[2]);
    else
        dev = rt_console_get_device();
    if (!dev)
    {
        rt_kprintf("could not find device.\n");
        return -RT_ERROR;
    }
    file_path = argv[1];
    res = rym_upload_file(dev, file_path);

    return res;
}
MSH_CMD_EXPORT(sy, YMODEM Send e.g: sy file_path [uart0] default by console.);

#endif /* RT_USING_FINSH */
