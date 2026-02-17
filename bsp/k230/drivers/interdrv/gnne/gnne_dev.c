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

#include <rtthread.h>
#include <rthw.h>
#include "io.h"
#include <ioremap.h>
#include "board.h"
#include "drv_hardlock.h"

#if defined(RT_USING_POSIX_DEVIO)
    #include <dfs_posix.h>
    #include <poll.h>
    #include <termios.h>
#endif

struct gnne_dev_handle
{
    rt_wqueue_t *wait;
    rt_bool_t is_lock;
};

#define gnne_log(s...)    rt_kprintf(s)

#define gnne_err(s...) do { \
    gnne_log("<err>[%s:%d] ", __func__, __LINE__); \
    gnne_log(s); \
    gnne_log("\r\n"); \
} while (0)

#define GNNE_CMD_LOCK       0
#define GNNE_CMD_TRYLOCK    1
#define GNNE_CMD_UNLOCK     2

static struct rt_device g_gnne_device = {0};
static struct rt_event g_gnne_event = {0};
void *gnne_base_addr = RT_NULL;
static hardlock_type g_kpu_lock = HARDLOCK_MAX;

static int gnne_device_open(struct dfs_file *file)
{
    struct gnne_dev_handle *handle;
    rt_device_t device;

    handle = rt_malloc(sizeof(struct gnne_dev_handle));
    if (handle == RT_NULL)
    {
        gnne_err("malloc failed\n");
        return -1;
    }
    device = (rt_device_t)file->vnode->data;
    handle->wait = &device->wait_queue;
    handle->is_lock = RT_FALSE;
    file->data = (void *)handle;
    return RT_EOK;
}

static int gnne_device_close(struct dfs_file *file)
{
    struct gnne_dev_handle *handle;

    handle = (struct gnne_dev_handle *)file->data;
    if (handle == RT_NULL)
    {
        gnne_err("try to close a invalid handle");
        return -RT_EINVAL;
    }
    if (handle->is_lock)
    {
        kd_hardlock_unlock(g_kpu_lock);
    }
    rt_free(handle);
    file->data = RT_NULL;
    return RT_EOK;
}

static int gnne_device_ioctl(struct dfs_file *file, int cmd, void *args)
{
    struct gnne_dev_handle *handle;
    int ret = -1;
    handle = (struct gnne_dev_handle *)file->data;
    if ((g_kpu_lock == HARDLOCK_MAX))
    {
        return ret;
    }
    if (cmd == GNNE_CMD_LOCK)
    {
        if (handle->is_lock == RT_TRUE)
        {
            return 0;
        }
        while (kd_hardlock_lock(g_kpu_lock));
        handle->is_lock = RT_TRUE;
        ret = 0;
    }
    else if (cmd == GNNE_CMD_UNLOCK)
    {
        if (handle->is_lock == RT_FALSE)
        {
            return 0;
        }
        kd_hardlock_unlock(g_kpu_lock);
        handle->is_lock = RT_FALSE;
        ret = 0;
    }
    else if (cmd == GNNE_CMD_TRYLOCK)
    {
        if (handle->is_lock == RT_TRUE)
        {
            return 0;
        }
        if (!kd_hardlock_lock(g_kpu_lock))
        {
            handle->is_lock = RT_TRUE;
            ret = 0;
        }
    }
    return ret;
}

int gnne_device_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    struct gnne_dev_handle *handle;
    unsigned int flags;
    handle = (struct gnne_dev_handle *)file->data;
    if (!handle)
    {
        gnne_err("gnne_dev_handle NULL!");
        return -EINVAL;
    }
    rt_event_recv(&g_gnne_event, 0x01, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, NULL);
    rt_poll_add(handle->wait, req);
    return POLLIN;
}

static const struct dfs_file_ops gnne_input_fops =
{
    .open = gnne_device_open,
    .close = gnne_device_close,
    .ioctl = gnne_device_ioctl,
    .poll = gnne_device_poll,
};

static void irq_callback(int irq, void *data)
{
    rt_wqueue_t *wait = (rt_wqueue_t *)data;
    volatile void *write_addr = (void *)((char *)gnne_base_addr + 0x128);
    if (gnne_base_addr == RT_NULL)
    {
        gnne_err("gnne interrupts while the hardware is not yet initialized\n");
    }
    /*clear kpu intr*/
    __iowmb();
    *(rt_uint64_t *)write_addr = 0x400000004;
    rt_wqueue_wakeup(wait, (void *)POLLIN);
    rt_event_send(&g_gnne_event, 0x1);
}

int gnne_device_init(void)
{
    int ret = 0;
    rt_isr_handler_t old_handler;
    rt_device_t gnne_device = &g_gnne_device;

    ret = rt_event_init(&g_gnne_event, "gnne_event", RT_IPC_FLAG_PRIO);
    if (ret)
    {
        gnne_err("event init failed\n");
        return -ENOMEM;
    }

    ret = rt_device_register(gnne_device, "gnne_device", RT_DEVICE_FLAG_RDWR);
    if (ret)
    {
        gnne_err("gnne_device register fail\n");
        return ret;
    }


    /*rt_ioremap maps the size of at least one page*/
    gnne_base_addr = rt_ioremap((void *)KPU_BASE_ADDR, (KPU_IO_SIZE + FFT_IO_SIZE + AI2D_IO_SIZE));
    if (gnne_base_addr == RT_NULL)
    {
        gnne_err("gnne ioremap error\n");
        return -1;
    }

    rt_wqueue_init(&gnne_device->wait_queue);
    old_handler = rt_hw_interrupt_install(K230_IRQ_GNNE, irq_callback, &gnne_device->wait_queue, "gnne_irq");
    if (old_handler == RT_NULL)
    {
        gnne_err("gnne_device interrupt install fail\n");
        return -RT_ERROR;
    }
    rt_hw_interrupt_umask(K230_IRQ_GNNE);

    gnne_device->fops = &gnne_input_fops;

    if (kd_request_lock(HARDLOCK_KPU))
    {
        gnne_err("fail to request hardlock-%d\n", HARDLOCK_KPU);
    }
    else
    {
        g_kpu_lock  = HARDLOCK_KPU;
    }

    return RT_EOK;
}
