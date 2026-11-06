/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * RT-Thread Device Model services for the Sun252i video engine.
 *
 * This file owns VE clocks, reset, interrupt and DMA buffers directly through
 * DM for the in-tree codec implementations.
 */

#include <errno.h>
#include <stdint.h>
#include <string.h>

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <vdec/vdec.h>

#include "vdec-sun252i.h"

#define DBG_TAG "vdec.sun252i"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define VDEC_CLK_VE                  27
#define VDEC_CLK_BUS_VE              28
#define VDEC_CLK_BUS_VE_M            40

#define SUN252I_VE_TOP_MODE          0x000U
#define SUN252I_VE_TOP_CTRL          0x004U
#define SUN252I_VE_TOP_FLAGS         0x01cU
#define SUN252I_VE_DECODER_OFF       7U
#define SUN252I_VE_DECODER_H264      9U

#define SUN252I_VE_CV_SIZE           0xa00U
#define SUN252I_VE_CV_STRIDE         0xa04U
#define SUN252I_VE_CV_ENABLE         0xa08U
#define SUN252I_VE_CV_MODE           0xa0cU
#define SUN252I_VE_CV_STATUS         0xa10U
#define SUN252I_VE_CV_LINE           0xa14U
#define SUN252I_VE_CV_CONFIG         0xa2cU
#define SUN252I_VE_CV_OUT_LUMA       0xa70U
#define SUN252I_VE_CV_OUT_CHROMA     0xa74U
#define SUN252I_VE_CV_IN_LUMA        0xa78U
#define SUN252I_VE_CV_IN_CHROMA      0xa7cU

struct sunxi_vdec_dma_buffer
{
    rt_list_t list;
    void *virt;
    rt_ubase_t dma;
    rt_size_t size;
};

struct sunxi_vdec_dm
{
    struct rt_device *dev;
    void *base;
    struct rt_clk *mod_clk;
    struct rt_clk *ahb_clk;
    struct rt_clk *ram_clk;
    struct rt_reset_control *reset;
    int irq;

    sunxi_vdec_irq_handler_t irq_handler;
    void *irq_data;
    struct rt_completion convert_done;
    rt_list_t dma_buffers;
    rt_uint16_t clock_users[3];
    rt_bool_t irq_installed;
    struct rt_semaphore available;
    struct rt_mutex dma_lock;
    struct rt_spinlock irq_lock;
    void *owner;
    rt_bool_t converting;
    rt_bool_t ipc_initialized;
    rt_bool_t faulted;
};

static struct sunxi_vdec_dm *vdec_dm;

rt_uint32_t sunxi_vdec_hw_readl(rt_size_t offset)
{
    return vdec_dm && vdec_dm->base ? HWREG32(vdec_dm->base + offset) : 0;
}

void sunxi_vdec_hw_writel(rt_size_t offset, rt_uint32_t value)
{
    if (vdec_dm && vdec_dm->base)
    {
        HWREG32(vdec_dm->base + offset) = value;
    }
}

int sunxi_vdec_hw_convert_tiled(rt_ubase_t input_luma, rt_ubase_t input_chroma,
                                rt_ubase_t output_luma, rt_uint16_t width,
                                rt_uint16_t height)
{
    rt_uint32_t macroblocks_width;
    rt_uint32_t macroblocks_height;
    rt_err_t err;
    rt_base_t level;

    if (!vdec_dm || !vdec_dm->base || !input_luma || !input_chroma ||
        !output_luma || !width || !height || width % 16 || height % 16)
    {
        return -EINVAL;
    }

    macroblocks_width = width / 16U;
    macroblocks_height = height / 16U;
    rt_completion_init(&vdec_dm->convert_done);

    /* The conversion block turns a decoded tiled 4:2:0 frame into NV12. */
    sunxi_vdec_hw_writel(SUN252I_VE_TOP_CTRL, 1);
    sunxi_vdec_hw_writel(SUN252I_VE_TOP_CTRL, 0);
    sunxi_vdec_hw_writel(SUN252I_VE_TOP_MODE, 2);
    sunxi_vdec_hw_writel(SUN252I_VE_CV_STATUS, 1);
    sunxi_vdec_hw_writel(SUN252I_VE_CV_SIZE,
                         (macroblocks_width << 16) | macroblocks_height);
    sunxi_vdec_hw_writel(SUN252I_VE_CV_STRIDE,
                         (macroblocks_width << 16) | macroblocks_width);
    sunxi_vdec_hw_writel(SUN252I_VE_CV_LINE, macroblocks_width);
    sunxi_vdec_hw_writel(SUN252I_VE_CV_ENABLE, 0x50080001U);
    sunxi_vdec_hw_writel(SUN252I_VE_CV_CONFIG,
                         (macroblocks_height << 16) | macroblocks_width);
    sunxi_vdec_hw_writel(0xa30U, 0);
    sunxi_vdec_hw_writel(0xa34U, 0);
    sunxi_vdec_hw_writel(0xa38U, 0);
    sunxi_vdec_hw_writel(SUN252I_VE_CV_OUT_LUMA, output_luma);
    sunxi_vdec_hw_writel(SUN252I_VE_CV_OUT_CHROMA,
                         output_luma + (rt_ubase_t)width * height);
    sunxi_vdec_hw_writel(SUN252I_VE_CV_IN_LUMA, input_luma);
    sunxi_vdec_hw_writel(SUN252I_VE_CV_IN_CHROMA, input_chroma);
    level = rt_spin_lock_irqsave(&vdec_dm->irq_lock);
    vdec_dm->converting = RT_TRUE;
    sunxi_vdec_hw_writel(SUN252I_VE_CV_MODE, 1);
    rt_hw_dsb();
    rt_spin_unlock_irqrestore(&vdec_dm->irq_lock, level);

    err = rt_completion_wait(&vdec_dm->convert_done,
                             rt_tick_from_millisecond(100));
    level = rt_spin_lock_irqsave(&vdec_dm->irq_lock);
    vdec_dm->converting = RT_FALSE;
    sunxi_vdec_hw_writel(SUN252I_VE_CV_ENABLE,
                        sunxi_vdec_hw_readl(SUN252I_VE_CV_ENABLE) & ~1U);
    rt_spin_unlock_irqrestore(&vdec_dm->irq_lock, level);
    if (err == RT_EOK)
    {
        sunxi_vdec_hw_writel(SUN252I_VE_CV_STATUS, 1);
        return 0;
    }

    LOG_E("tiled conversion timeout: enable=%08x status=%08x mode=%08x",
          sunxi_vdec_hw_readl(SUN252I_VE_CV_ENABLE),
          sunxi_vdec_hw_readl(SUN252I_VE_CV_STATUS),
          sunxi_vdec_hw_readl(SUN252I_VE_CV_MODE));
    return -ETIMEDOUT;
}

static int vdec_clock_index(unsigned int id)
{
    switch (id)
    {
    case VDEC_CLK_VE:
        return 0;
    case VDEC_CLK_BUS_VE:
        return 1;
    case VDEC_CLK_BUS_VE_M:
        return 2;
    default:
        return -1;
    }
}

static struct rt_clk *sunxi_vdec_hw_clock(unsigned int id)
{
    if (!vdec_dm)
    {
        return RT_NULL;
    }

    switch (id)
    {
    case VDEC_CLK_VE:
        return vdec_dm->mod_clk;
    case VDEC_CLK_BUS_VE:
        return vdec_dm->ahb_clk;
    case VDEC_CLK_BUS_VE_M:
        return vdec_dm->ram_clk;
    default:
        return RT_NULL;
    }
}

static rt_err_t sunxi_vdec_hw_claim_sram(void)
{
    struct rt_ofw_node *section_np;
    struct rt_ofw_node *sram_np;
    struct rt_ofw_node *syscon_np;
    struct rt_syscon *syscon;
    rt_err_t err = -RT_EINVAL;

    if (!vdec_dm || !vdec_dm->dev)
    {
        return -RT_EIO;
    }

    section_np = rt_ofw_parse_phandle(vdec_dm->dev->ofw_node,
                                      "allwinner,sram", 0);
    if (!section_np)
    {
        return -RT_EINVAL;
    }
    if (!rt_ofw_node_is_compatible(section_np,
            "allwinner,sun252i-f101-sram-ve"))
    {
        goto out_section;
    }

    sram_np = rt_ofw_get_parent(section_np);
    syscon_np = sram_np ? rt_ofw_get_parent(sram_np) : RT_NULL;
    if (!syscon_np)
    {
        goto out_parent;
    }

    /*
     * The reference initialization first opens the system SRAM gates,
     * then switches SRAM section 1 from the CPU to VE.  Both writes are
     * required before the H.264 block can fetch its decoder buffers.
     */
    syscon = rt_syscon_find_by_ofw_node(syscon_np);
    if (syscon)
    {
        err = rt_syscon_update_bits(syscon, 0x0, 0x7fffffffU,
                                   0x7fffffffU);
        if (err == RT_EOK)
        {
            err = rt_syscon_update_bits(syscon, 0x4, RT_BIT(24), 0);
        }
    }
    rt_ofw_node_put(syscon_np);
out_parent:
    if (sram_np)
    {
        rt_ofw_node_put(sram_np);
    }
out_section:
    rt_ofw_node_put(section_np);

    return err;
}

static void sunxi_vdec_dma_release(struct sunxi_vdec_dm *dm)
{
    struct sunxi_vdec_dma_buffer *buffer;
    struct sunxi_vdec_dma_buffer *next;

    rt_list_for_each_entry_safe(buffer, next, &dm->dma_buffers, list)
    {
        rt_list_remove(&buffer->list);
        rt_dma_free_coherent(dm->dev, buffer->size, buffer->virt, buffer->dma);
        rt_free(buffer);
    }
}

static void sunxi_vdec_hw_destroy(struct sunxi_vdec_dm *dm)
{
    int i;

    if (!dm)
    {
        return;
    }
    if (dm->irq_installed)
    {
        rt_hw_interrupt_mask(dm->irq);
        rt_pic_detach_irq(dm->irq, dm);
    }
    sunxi_vdec_dma_release(dm);
    for (i = 0; i < 3; i++)
    {
        struct rt_clk *clk = i == 0 ? dm->mod_clk :
                             (i == 1 ? dm->ahb_clk : dm->ram_clk);

        while (dm->clock_users[i] != 0)
        {
            rt_clk_disable_unprepare(clk);
            dm->clock_users[i]--;
        }
    }
    if (!rt_is_err_or_null(dm->reset))
    {
        rt_reset_control_assert(dm->reset);
        rt_reset_control_put(dm->reset);
    }
    if (!rt_is_err_or_null(dm->ram_clk))
    {
        rt_clk_put(dm->ram_clk);
    }
    if (!rt_is_err_or_null(dm->ahb_clk))
    {
        rt_clk_put(dm->ahb_clk);
    }
    if (!rt_is_err_or_null(dm->mod_clk))
    {
        rt_clk_put(dm->mod_clk);
    }
    if (dm->base)
    {
        rt_iounmap(dm->base);
    }
    if (dm->ipc_initialized)
    {
        rt_mutex_detach(&dm->dma_lock);
        rt_sem_detach(&dm->available);
    }
    rt_free(dm);
}

static rt_err_t sunxi_vdec_hw_probe(struct rt_device *dev)
{
    struct sunxi_vdec_dm *dm;
    rt_err_t err;

    if (!dev)
    {
        return -RT_EINVAL;
    }
    if (vdec_dm)
    {
        return -RT_EBUSY;
    }

    dm = rt_calloc(1, sizeof(*dm));
    if (!dm)
    {
        return -RT_ENOMEM;
    }
    dm->dev = dev;
    dm->irq = -1;
    rt_list_init(&dm->dma_buffers);
    rt_spin_lock_init(&dm->irq_lock);
    err = rt_sem_init(&dm->available, "ve", 1, RT_IPC_FLAG_FIFO);
    if (err != RT_EOK)
    {
        rt_free(dm);
        return err;
    }
    err = rt_mutex_init(&dm->dma_lock, "ve.dma", RT_IPC_FLAG_PRIO);
    if (err != RT_EOK)
    {
        rt_sem_detach(&dm->available);
        rt_free(dm);
        return err;
    }
    dm->ipc_initialized = RT_TRUE;

    dm->base = rt_dm_dev_iomap(dev, 0);
    if (!dm->base)
    {
        err = -RT_EIO;
        goto fail;
    }

    dm->mod_clk = rt_clk_get_by_name(dev, "mod");
    if (rt_is_err_or_null(dm->mod_clk))
    {
        err = rt_is_err(dm->mod_clk) ? rt_ptr_err(dm->mod_clk) : -RT_ENOENT;
        goto fail;
    }
    dm->ahb_clk = rt_clk_get_by_name(dev, "ahb");
    if (rt_is_err_or_null(dm->ahb_clk))
    {
        err = rt_is_err(dm->ahb_clk) ? rt_ptr_err(dm->ahb_clk) : -RT_ENOENT;
        goto fail;
    }
    dm->ram_clk = rt_clk_get_by_name(dev, "ram");
    if (rt_is_err_or_null(dm->ram_clk))
    {
        err = rt_is_err(dm->ram_clk) ? rt_ptr_err(dm->ram_clk) : -RT_ENOENT;
        goto fail;
    }

    /* Keep the VE at the rate requested by its Linux Cedrus driver. */
    err = rt_clk_set_rate(dm->mod_clk, 512000000U);
    if (err != RT_EOK)
    {
        goto fail;
    }
    dm->reset = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err_or_null(dm->reset))
    {
        err = rt_is_err(dm->reset) ? rt_ptr_err(dm->reset) : -RT_ENOENT;
        goto fail;
    }
    dm->irq = rt_dm_dev_get_irq(dev, 0);
    if (dm->irq < 0)
    {
        err = dm->irq;
        goto fail;
    }
    vdec_dm = dm;
    dev->user_data = dm;
    return RT_EOK;

fail:
    sunxi_vdec_hw_destroy(dm);
    return err;
}

static void sunxi_vdec_hw_remove(struct rt_device *dev)
{
    struct sunxi_vdec_dm *dm = vdec_dm;

    if (!dm || (dev && dm->dev != dev))
    {
        return;
    }
    vdec_dm = RT_NULL;
    dm->dev->user_data = RT_NULL;
    sunxi_vdec_hw_destroy(dm);
}

static void sunxi_vdec_isr(int vector, void *arg)
{
    struct sunxi_vdec_dm *dm = arg;
    rt_base_t level;

    RT_UNUSED(vector);
    level = rt_spin_lock_irqsave(&dm->irq_lock);
    if (!dm->owner)
    {
        rt_spin_unlock_irqrestore(&dm->irq_lock, level);
        return;
    }
    if (dm->converting && (sunxi_vdec_hw_readl(SUN252I_VE_CV_ENABLE) & 1U) &&
        (sunxi_vdec_hw_readl(SUN252I_VE_CV_STATUS) & 1U))
    {
        sunxi_vdec_hw_writel(SUN252I_VE_CV_ENABLE,
                             sunxi_vdec_hw_readl(SUN252I_VE_CV_ENABLE) & ~1U);
        rt_completion_done(&dm->convert_done);
    }
    else if (dm && dm->irq_handler)
    {
        (void)dm->irq_handler(dm->irq_data);
    }
    rt_spin_unlock_irqrestore(&dm->irq_lock, level);
}

static int sunxi_vdec_hw_clock_enable(unsigned int id)
{
    struct rt_clk *clk;
    int index;
    rt_err_t err;

    index = vdec_clock_index(id);
    clk = sunxi_vdec_hw_clock(id);
    if (index < 0 || !clk)
    {
        return -ENODEV;
    }
    err = rt_clk_prepare_enable(clk);
    if (err != RT_EOK)
    {
        return -EIO;
    }
    vdec_dm->clock_users[index]++;
    return 0;
}

static int sunxi_vdec_hw_clock_disable(unsigned int id)
{
    struct rt_clk *clk;
    int index;

    index = vdec_clock_index(id);
    clk = sunxi_vdec_hw_clock(id);
    if (index < 0 || !clk)
    {
        return -ENODEV;
    }
    if (vdec_dm->clock_users[index] != 0)
    {
        rt_clk_disable_unprepare(clk);
        vdec_dm->clock_users[index]--;
    }
    return 0;
}

static int sunxi_vdec_hw_reset_assert(void)
{
    if (!vdec_dm)
    {
        return -ENODEV;
    }
    return rt_reset_control_assert(vdec_dm->reset) == RT_EOK ? 0 : -EIO;
}

static int sunxi_vdec_hw_reset_deassert(void)
{
    if (!vdec_dm)
    {
        return -ENODEV;
    }
    return rt_reset_control_deassert(vdec_dm->reset) == RT_EOK ? 0 : -EIO;
}

int sunxi_vdec_hw_reset(void)
{
    if (!vdec_dm)
    {
        return -ENODEV;
    }

    return rt_reset_control_reset(vdec_dm->reset) == RT_EOK ? 0 : -EIO;
}

int sunxi_vdec_hw_reset_decoder(void)
{
    rt_uint32_t value;

    if (!vdec_dm || rt_is_err_or_null(vdec_dm->reset))
    {
        return -ENODEV;
    }

    if (rt_reset_control_reset(vdec_dm->reset) != RT_EOK)
    {
        return -EIO;
    }

    /* Sun252i inverts top-level decoder select bit 3: H.264 is selector 9. */
    value = sunxi_vdec_hw_readl(SUN252I_VE_TOP_MODE);
    sunxi_vdec_hw_writel(SUN252I_VE_TOP_MODE,
                         (value & ~0x0fU) | SUN252I_VE_DECODER_OFF);
    value = sunxi_vdec_hw_readl(SUN252I_VE_TOP_CTRL);
    sunxi_vdec_hw_writel(SUN252I_VE_TOP_CTRL, value | RT_BIT(16));
    sunxi_vdec_hw_writel(SUN252I_VE_TOP_CTRL, value & ~RT_BIT(16));
    value = sunxi_vdec_hw_readl(SUN252I_VE_TOP_MODE);
    sunxi_vdec_hw_writel(SUN252I_VE_TOP_MODE,
                         (value & ~(0x0fU | RT_BIT(21) | RT_BIT(22))) |
                         SUN252I_VE_DECODER_H264);
    value = sunxi_vdec_hw_readl(SUN252I_VE_TOP_FLAGS);
    sunxi_vdec_hw_writel(SUN252I_VE_TOP_FLAGS,
                         value & ~(RT_BIT(8) | RT_BIT(10)));
    rt_hw_dsb();

    return 0;
}

static struct sunxi_vdec_dma_buffer *sunxi_vdec_dma_find_virt(void *virt)
{
    struct sunxi_vdec_dma_buffer *buffer;
    uintptr_t address = (uintptr_t)virt;

    if (!vdec_dm)
    {
        return RT_NULL;
    }
    rt_list_for_each_entry(buffer, &vdec_dm->dma_buffers, list)
    {
        uintptr_t start = (uintptr_t)buffer->virt;

        if (address >= start && address - start < buffer->size)
        {
            return buffer;
        }
    }
    return RT_NULL;
}

static void *sunxi_vdec_dma_alloc(rt_size_t size)
{
    struct sunxi_vdec_dma_buffer *buffer;
    rt_size_t aligned;

    if (!vdec_dm || !size)
    {
        return RT_NULL;
    }
    aligned = RT_ALIGN((rt_size_t)size, 64);
    buffer = rt_calloc(1, sizeof(*buffer));
    if (!buffer)
    {
        return RT_NULL;
    }
    buffer->virt = rt_dma_alloc_coherent(vdec_dm->dev, aligned, &buffer->dma);
    if (!buffer->virt)
    {
        rt_free(buffer);
        LOG_E("out of DMA memory for %u bytes", (rt_uint32_t)size);
        return RT_NULL;
    }
    buffer->size = aligned;
    rt_list_insert_before(&vdec_dm->dma_buffers, &buffer->list);
    return buffer->virt;
}

static void sunxi_vdec_dma_free(void *virt)
{
    struct sunxi_vdec_dma_buffer *buffer;

    buffer = sunxi_vdec_dma_find_virt(virt);
    if (!buffer || buffer->virt != virt)
    {
        LOG_E("unknown DMA buffer %p", virt);
        return;
    }
    rt_list_remove(&buffer->list);
    rt_dma_free_coherent(vdec_dm->dev, buffer->size, buffer->virt, buffer->dma);
    rt_free(buffer);
}

void *sunxi_vdec_hw_dma_alloc(rt_size_t size, rt_ubase_t *dma)
{
    struct sunxi_vdec_dma_buffer *buffer;
    void *virt;

    if (!vdec_dm || !size || size > (rt_size_t)-1 - 63)
    {
        return RT_NULL;
    }
    rt_mutex_take(&vdec_dm->dma_lock, RT_WAITING_FOREVER);
    virt = sunxi_vdec_dma_alloc(size);
    if (!virt)
    {
        rt_mutex_release(&vdec_dm->dma_lock);
        return RT_NULL;
    }
    buffer = sunxi_vdec_dma_find_virt(virt);
    if (!buffer)
    {
        sunxi_vdec_dma_free(virt);
        rt_mutex_release(&vdec_dm->dma_lock);
        return RT_NULL;
    }
    if (dma)
    {
        *dma = buffer->dma;
    }
    rt_mutex_release(&vdec_dm->dma_lock);
    return virt;
}

void sunxi_vdec_hw_dma_free(void *virt)
{
    if (!vdec_dm || !virt)
    {
        return;
    }
    rt_mutex_take(&vdec_dm->dma_lock, RT_WAITING_FOREVER);
    sunxi_vdec_dma_free(virt);
    rt_mutex_release(&vdec_dm->dma_lock);
}

static int sunxi_vdec_power_off(struct sunxi_vdec_dm *dm)
{
    int result;

    /* Stop bus mastering before any codec buffers can be freed. */
    result = sunxi_vdec_hw_reset_assert();
    sunxi_vdec_hw_clock_disable(VDEC_CLK_VE);
    sunxi_vdec_hw_clock_disable(VDEC_CLK_BUS_VE_M);
    sunxi_vdec_hw_clock_disable(VDEC_CLK_BUS_VE);
    if (result)
    {
        dm->faulted = RT_TRUE;
        LOG_E("VE reset failed; further submissions disabled");
    }
    return result;
}

int sunxi_vdec_hw_acquire(void *owner, sunxi_vdec_irq_handler_t handler,
                        rt_int32_t timeout)
{
    struct sunxi_vdec_dm *dm = vdec_dm;
    rt_base_t level;
    int result;

    if (!dm)
    {
        return -ENODEV;
    }
    if (!owner || !handler || timeout < RT_WAITING_FOREVER)
    {
        return -EINVAL;
    }
    level = rt_spin_lock_irqsave(&dm->irq_lock);
    if (dm->owner == owner)
    {
        rt_spin_unlock_irqrestore(&dm->irq_lock, level);
        return -EBUSY;
    }
    rt_spin_unlock_irqrestore(&dm->irq_lock, level);
    result = rt_sem_take(&dm->available, timeout);
    if (result)
    {
        return timeout == 0 ? -EBUSY : result;
    }
    if (dm->faulted)
    {
        rt_sem_release(&dm->available);
        return -EIO;
    }

    /* Preserve the validated CedarX power/SRAM bring-up order. */
    result = sunxi_vdec_hw_reset_deassert();
    result = result ? result : sunxi_vdec_hw_clock_enable(VDEC_CLK_VE);
    result = result ? result : sunxi_vdec_hw_claim_sram();
    result = result ? result : sunxi_vdec_hw_clock_enable(VDEC_CLK_BUS_VE);
    result = result ? result : sunxi_vdec_hw_clock_enable(VDEC_CLK_BUS_VE_M);
    result = result ? result : sunxi_vdec_hw_reset();
    if (result)
    {
        sunxi_vdec_power_off(dm);
        rt_sem_release(&dm->available);
        return result;
    }
    level = rt_spin_lock_irqsave(&dm->irq_lock);
    dm->owner = owner;
    dm->irq_data = owner;
    dm->irq_handler = handler;
    dm->converting = RT_FALSE;
    rt_spin_unlock_irqrestore(&dm->irq_lock, level);
    rt_hw_interrupt_umask(dm->irq);
    return 0;
}

int sunxi_vdec_hw_release(void *owner)
{
    struct sunxi_vdec_dm *dm = vdec_dm;
    rt_base_t level;
    int result;

    if (!dm || !owner)
    {
        return -EINVAL;
    }
    level = rt_spin_lock_irqsave(&dm->irq_lock);
    if (dm->owner != owner)
    {
        rt_spin_unlock_irqrestore(&dm->irq_lock, level);
        return -EPERM;
    }
    rt_hw_interrupt_mask(dm->irq);
    dm->irq_handler = RT_NULL;
    dm->irq_data = RT_NULL;
    dm->owner = RT_NULL;
    dm->converting = RT_FALSE;
    rt_spin_unlock_irqrestore(&dm->irq_lock, level);
    result = sunxi_vdec_power_off(dm);
    rt_sem_release(&dm->available);
    return result;
}

int vdec_set_clock_hz(uint32_t hz)
{
    struct sunxi_vdec_dm *dm = vdec_dm;
    int result;

    if (!dm || !hz)
    {
        return !dm ? -ENODEV : -EINVAL;
    }
    if (rt_sem_take(&dm->available, 0) != RT_EOK)
    {
        return -EBUSY;
    }
    result = rt_clk_set_rate(dm->mod_clk, hz);
    if (result == RT_EOK)
    {
        result = (int)rt_clk_get_rate(dm->mod_clk);
    }
    rt_sem_release(&dm->available);
    return result;
}

uint32_t vdec_clock_hz(void)
{
    return vdec_dm ? (uint32_t)rt_clk_get_rate(vdec_dm->mod_clk) : 0;
}

static rt_err_t vdec_probe(struct rt_platform_device *pdev)
{
    rt_err_t error = sunxi_vdec_hw_probe(&pdev->parent);

    if (error != RT_EOK)
    {
        return error;
    }
    rt_hw_interrupt_mask(vdec_dm->irq);
    error = rt_pic_attach_irq(vdec_dm->irq, sunxi_vdec_isr, vdec_dm,
                             "ve", RT_IRQ_F_NONE);
    if (error == RT_EOK)
    {
        vdec_dm->irq_installed = RT_TRUE;
#if defined(RT_SOC_SUNXI_JPEG_DEC) || defined(RT_SOC_SUNXI_JPEG_ENC) || defined(RT_SOC_SUNXI_PNG_DEC)
        error = sunxi_vdec_images_register(&pdev->parent);
#endif
    }
    if (error != RT_EOK)
    {
        sunxi_vdec_hw_remove(&pdev->parent);
    }
    return error;
}

static rt_err_t vdec_remove(struct rt_platform_device *pdev)
{
    /* Codec handles and DMA buffers may outlive a submission. No hot-unbind. */
    RT_UNUSED(pdev);
    return -RT_EBUSY;
}

static const struct rt_ofw_node_id vdec_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-video-engine" },
    { .compatible = "allwinner,sunxi-ve" },
    { /* sentinel */ }
};

static struct rt_platform_driver vdec_driver =
{
    .name = "vdec-sun252i",
    .ids = vdec_ofw_ids,
    .probe = vdec_probe,
    .remove = vdec_remove,
};
RT_PLATFORM_DRIVER_EXPORT(vdec_driver);
