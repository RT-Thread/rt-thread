/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Sun252i video-engine services for codec implementations. */

#ifndef __VDEC_SUN252I_H__
#define __VDEC_SUN252I_H__

#include <rtthread.h>
#include <rtdevice.h>

/* Register access and reset are only valid while holding a VE lease. */
int sunxi_vdec_hw_reset(void);
int sunxi_vdec_hw_reset_decoder(void);

typedef int (*sunxi_vdec_irq_handler_t)(void *data);

/* Non-preemptive lease. Timeout is in ticks; zero returns busy immediately.
 * The owner must finish all register accesses before releasing its lease.
 */
int sunxi_vdec_hw_acquire(void *owner, sunxi_vdec_irq_handler_t handler,
                        rt_int32_t timeout);
int sunxi_vdec_hw_release(void *owner);
rt_err_t sunxi_vdec_images_register(struct rt_device *dev);

rt_uint32_t sunxi_vdec_hw_readl(rt_size_t offset);
void sunxi_vdec_hw_writel(rt_size_t offset, rt_uint32_t value);
int sunxi_vdec_hw_convert_tiled(rt_ubase_t input_luma, rt_ubase_t input_chroma,
                                rt_ubase_t output_luma, rt_uint16_t width,
                                rt_uint16_t height);

void *sunxi_vdec_hw_dma_alloc(rt_size_t size, rt_ubase_t *dma);
void sunxi_vdec_hw_dma_free(void *virt);

#endif /* __VDEC_SUN252I_H__ */
