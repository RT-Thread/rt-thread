/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#if defined(RT_USING_DMA) && defined(RT_USING_FINSH)
#include <stdlib.h>

static void test_dma_callback(struct rt_dma_chan *chan, rt_size_t size)
{
    rt_bool_t *done_ptr = chan->priv;

    *done_ptr = RT_TRUE;
    rt_hw_wmb();
}

static int dma_memcpy_test(int argc, char**argv)
{
    rt_bool_t done;
    int dma_sz = 64;
    rt_ubase_t dma_addr;
    char *src_addr, *dst_addr;
    struct rt_device dev = {};
    struct rt_dma_slave_config config;
    struct rt_dma_slave_transfer transfer;
    struct rt_dma_chan *chn = rt_dma_chan_request(&dev, RT_NULL);

    if (rt_is_err_or_null(chn))
    {
        rt_kputs("Alloc DMA channel fail");
        return 0;
    }

    if (argc > 1)
    {
        dma_sz = atoi(argv[1]);
    }

    if (dma_sz % sizeof(rt_uint32_t))
    {
        dma_sz = RT_ALIGN_DOWN(dma_sz, sizeof(rt_uint32_t));
        rt_kprintf("DMA size align to %d\n", dma_sz);
    }

    if (!(src_addr = rt_dma_alloc_coherent(&dev, dma_sz, &dma_addr)))
    {
        rt_kprintf("Alloc DMA %s buffer(size = %d) fail\n", "SRC", dma_sz);
        goto _free_dma_chan;
    }
    config.src_addr = dma_addr;

    if (!(dst_addr = rt_dma_alloc_coherent(&dev, dma_sz, &dma_addr)))
    {
        rt_kprintf("Alloc DMA %s buffer(size = %d) fail\n", "DST", dma_sz);
        goto _free_src_addr;
    }
    config.dst_addr = dma_addr;

    config.direction = RT_DMA_MEM_TO_MEM;
    config.src_addr_width = sizeof(rt_uint32_t);
    config.src_maxburst = sizeof(rt_uint32_t);
    config.dst_addr_width = sizeof(rt_uint32_t);
    config.dst_maxburst = sizeof(rt_uint32_t);

    chn->callback = test_dma_callback;
    chn->priv = &done;
    if (rt_dma_chan_config(chn, &config))
    {
        rt_kprintf("DMA channel %s fail\n", "config");
        goto _free_dst_addr;
    }

    rt_memset(&transfer, 0, sizeof(transfer));
    transfer.src_addr = config.src_addr;
    transfer.dst_addr = config.dst_addr;
    transfer.buffer_len = dma_sz;

    if (rt_dma_prep_memcpy(chn, &transfer))
    {
        rt_kprintf("DMA channel %s fail\n", "prep");
        goto _free_dst_addr;
    }

    rt_memset(src_addr, 0xff, dma_sz);
    rt_memset(dst_addr, 0, dma_sz);

    rt_kprintf("%s %s:\n", "SRC", "start");
    for (int i = 0; i < dma_sz; ++i)
    {
        rt_kprintf("%02x ", src_addr[i]);
    }
    rt_kputs("\n");

    rt_kprintf("%s %s:\n", "DST", "start");
    for (int i = 0; i < dma_sz; ++i)
    {
        rt_kprintf("%02x ", dst_addr[i]);
    }
    rt_kputs("\n");

    done = RT_FALSE;
    if (rt_dma_chan_start(chn))
    {
        rt_kprintf("DMA channel %s fail\n", "start");
        goto _free_dst_addr;
    }

    while (!done)
    {
        rt_hw_cpu_relax();
    }

    rt_kprintf("%s %s:\n", "SRC", "end");
    for (int i = 0; i < dma_sz; ++i)
    {
        rt_kprintf("%02x ", src_addr[i]);
    }
    rt_kputs("\n");

    rt_kprintf("%s %s:\n", "DST", "end");
    for (int i = 0; i < dma_sz; ++i)
    {
        rt_kprintf("%02x ", dst_addr[i]);
    }
    rt_kputs("\n");

_free_dst_addr:
    rt_dma_free_coherent(&dev, dma_sz, dst_addr, config.dst_addr);
_free_src_addr:
    rt_dma_free_coherent(&dev, dma_sz, src_addr, config.src_addr);
_free_dma_chan:
    rt_dma_chan_release(chn);

    return 0;
}
MSH_CMD_EXPORT(dma_memcpy_test, test dma memcpy e.g: dma_memcpy_test(64));
#endif /* RT_USING_DMA && RT_USING_FINSH */
