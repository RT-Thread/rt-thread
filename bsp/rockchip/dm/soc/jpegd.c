/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "soc.rockchip.jpegd"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>
#include <jpegd.h>

#ifdef RT_USING_IOMMU
#include <drivers/iommu.h>
#endif

#define JPGDEC_REG_NUM                  JPEGD_REG_NUM
#define JPGDEC_REG_INT_EN_INDEX         1
#define JPGDEC_REG_SYS_INDEX            2

#define JPGDEC_FORCE_SOFTRESET_VALID    RT_BIT(17)

#define JPGDEC_SOFT_RSET_READY          RT_BIT(14)
#define JPGDEC_BUF_EMPTY_STA            RT_BIT(13)
#define JPGDEC_TIMEOUT_STA              RT_BIT(12)
#define JPGDEC_ERROR_STA                RT_BIT(11)
#define JPGDEC_BUS_STA                  RT_BIT(10)
#define JPGDEC_IRQ_RAW                  RT_BIT(6)
#define JPGDEC_SOFT_REST_EN             RT_BIT(5)
#define JPGDEC_START_EN                 RT_BIT(0)

#define JPGDEC_ERROR_MASK               (JPGDEC_BUS_STA | JPGDEC_ERROR_STA | JPGDEC_TIMEOUT_STA | JPGDEC_BUF_EMPTY_STA)

#define JPGDEC_TIMEOUT_MS               500

struct rockchip_jpegd
{
    struct rt_device parent;

    struct rt_device *dev;
    void *regs;
    int irq;

    struct rt_clk_array *clk_arr;
    struct rt_reset_control *rst_a;
    struct rt_reset_control *rst_h;

    rt_uint32_t hw_id;
    rt_uint32_t irq_status;
    rt_err_t error;
    rt_bool_t done;
    struct rt_mutex lock;
};

#define raw_to_rockchip_jpegd(raw) rt_container_of(raw, struct rockchip_jpegd, parent)

rt_inline rt_uint32_t rockchip_jpegd_read(struct rockchip_jpegd *jpegd, int index)
{
    return HWREG32(jpegd->regs + index * sizeof(rt_uint32_t));
}

rt_inline void rockchip_jpegd_write(struct rockchip_jpegd *jpegd, int index, rt_uint32_t val)
{
    HWREG32(jpegd->regs + index * sizeof(rt_uint32_t)) = val;
}

static rt_err_t rockchip_jpegd_soft_reset(struct rockchip_jpegd *jpegd)
{
    rt_uint32_t int_status = rockchip_jpegd_read(jpegd, JPGDEC_REG_INT_EN_INDEX);
    rt_uint32_t dec_en = int_status & JPGDEC_START_EN;
    int timeout = 1000;

    if (!dec_en)
    {
        rockchip_jpegd_write(jpegd, JPGDEC_REG_SYS_INDEX, JPGDEC_FORCE_SOFTRESET_VALID);
    }

    rockchip_jpegd_write(jpegd, JPGDEC_REG_INT_EN_INDEX, int_status | JPGDEC_SOFT_REST_EN);

    while (timeout-- > 0)
    {
        int_status = rockchip_jpegd_read(jpegd, JPGDEC_REG_INT_EN_INDEX);
        if (int_status & JPGDEC_SOFT_RSET_READY)
        {
            return RT_EOK;
        }

        rt_hw_us_delay(1);
    }

    LOG_E("soft reset timeout");

    return -RT_ETIMEOUT;
}

static void rockchip_jpegd_hard_reset(struct rockchip_jpegd *jpegd)
{
    if (jpegd->rst_a && jpegd->rst_h)
    {
        rt_reset_control_assert(jpegd->rst_a);
        rt_reset_control_assert(jpegd->rst_h);
        rt_hw_us_delay(5);
        rt_reset_control_deassert(jpegd->rst_a);
        rt_reset_control_deassert(jpegd->rst_h);
    }

    rockchip_jpegd_write(jpegd, JPGDEC_REG_INT_EN_INDEX, 0);
}

static rt_err_t rockchip_jpegd_submit(struct rockchip_jpegd *jpegd, struct jpegd_req *req)
{
    int i;
    rt_uint32_t int_status;
    rt_tick_t deadline = rt_tick_get() + rt_tick_from_millisecond(JPGDEC_TIMEOUT_MS);

    int_status = rockchip_jpegd_read(jpegd, JPGDEC_REG_INT_EN_INDEX);
    if (int_status & JPGDEC_START_EN)
    {
        LOG_E("JPEG decoder busy");
        return -RT_EBUSY;
    }

    if (rockchip_jpegd_soft_reset(jpegd) != RT_EOK)
    {
        rockchip_jpegd_hard_reset(jpegd);
    }

    for (i = 0; i < JPGDEC_REG_NUM; ++i)
    {
        if (i != JPGDEC_REG_INT_EN_INDEX)
        {
            rockchip_jpegd_write(jpegd, i, req->reg[i]);
        }
    }

#ifdef RT_USING_IOMMU
    if (jpegd->dev->iommu_domain)
    {
        rt_iommu_iotlb_flush(jpegd->dev);
    }
#endif

    rt_hw_dsb();

    jpegd->done = RT_FALSE;
    jpegd->error = RT_EOK;
    jpegd->irq_status = 0;

    rockchip_jpegd_write(jpegd, JPGDEC_REG_INT_EN_INDEX,
            req->reg[JPGDEC_REG_INT_EN_INDEX] | JPGDEC_START_EN);

    while (!jpegd->done && rt_tick_get() < deadline)
    {
        rt_hw_cpu_relax();
    }

    if (!jpegd->done)
    {
        LOG_E("JPEG decode timeout");
        rockchip_jpegd_hard_reset(jpegd);
        return -RT_ETIMEOUT;
    }

    req->irq_status = jpegd->irq_status;

    for (i = 0; i < JPGDEC_REG_NUM; ++i)
    {
        req->reg[i] = rockchip_jpegd_read(jpegd, i);
    }

    if (jpegd->error != RT_EOK)
    {
        if (rockchip_jpegd_soft_reset(jpegd) != RT_EOK)
        {
            rockchip_jpegd_hard_reset(jpegd);
        }
    }

    return jpegd->error;
}

static rt_err_t rockchip_jpegd_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct rockchip_jpegd *jpegd = raw_to_rockchip_jpegd(dev);

    rt_mutex_take(&jpegd->lock, RT_WAITING_FOREVER);

    switch (cmd)
    {
    case JPEGD_RUN:
    {
        struct jpegd_req *req = args;

        if (!req)
        {
            err = -RT_EINVAL;
            break;
        }

        err = rockchip_jpegd_submit(jpegd, req);
        break;
    }
    case JPEGD_GET_HW_ID:
    {
        rt_uint32_t *hw_id = args;

        if (!hw_id)
        {
            err = -RT_EINVAL;
            break;
        }

        *hw_id = jpegd->hw_id;
        break;
    }
    default:
        err = -RT_ENOSYS;
        break;
    }

    rt_mutex_release(&jpegd->lock);

    return err;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops rockchip_jpegd_ops =
{
    .control = rockchip_jpegd_control,
};
#endif

static void rockchip_jpegd_isr(int irqno, void *param)
{
    rt_uint32_t irq_status;
    struct rockchip_jpegd *jpegd = param;

    irq_status = rockchip_jpegd_read(jpegd, JPGDEC_REG_INT_EN_INDEX);

    if (!(irq_status & JPGDEC_IRQ_RAW))
    {
        return;
    }

    rockchip_jpegd_write(jpegd, JPGDEC_REG_INT_EN_INDEX, 0);

    jpegd->irq_status = irq_status;

    if (irq_status & JPGDEC_ERROR_MASK)
    {
        LOG_E("JPEG decode error, irq_status = 0x%08x", irq_status);
        jpegd->error = -RT_EIO;
    }

    jpegd->done = RT_TRUE;
}

static void rockchip_jpegd_free(struct rockchip_jpegd *jpegd)
{
    if (jpegd->regs)
    {
        rt_iounmap(jpegd->regs);
    }

    if (!rt_is_err_or_null(jpegd->clk_arr))
    {
        rt_clk_array_disable_unprepare(jpegd->clk_arr);
        rt_clk_array_put(jpegd->clk_arr);
    }

    if (!rt_is_err_or_null(jpegd->rst_a))
    {
        rt_reset_control_put(jpegd->rst_a);
    }

    if (!rt_is_err_or_null(jpegd->rst_h))
    {
        rt_reset_control_put(jpegd->rst_h);
    }

    rt_free(jpegd);
}

static rt_err_t rockchip_jpegd_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct rockchip_jpegd *jpegd = rt_calloc(1, sizeof(*jpegd));

    if (!jpegd)
    {
        return -RT_ENOMEM;
    }

    jpegd->dev = dev;

    jpegd->regs = rt_dm_dev_iomap(dev, 0);
    if (!jpegd->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    jpegd->clk_arr = rt_clk_get_array(dev);
    if (rt_is_err(jpegd->clk_arr))
    {
        err = rt_ptr_err(jpegd->clk_arr);
        goto _fail;
    }

    if ((err = rt_clk_array_prepare_enable(jpegd->clk_arr)))
    {
        goto _fail;
    }

    jpegd->rst_a = rt_reset_control_get_by_name(dev, "video_a");
    if (rt_is_err(jpegd->rst_a))
    {
        LOG_W("no video_a reset, err = %d", rt_ptr_err(jpegd->rst_a));
        jpegd->rst_a = RT_NULL;
    }

    jpegd->rst_h = rt_reset_control_get_by_name(dev, "video_h");
    if (rt_is_err(jpegd->rst_h))
    {
        LOG_W("no video_h reset, err = %d", rt_ptr_err(jpegd->rst_h));
        jpegd->rst_h = RT_NULL;
    }

    jpegd->irq = rt_dm_dev_get_irq(dev, 0);
    if (jpegd->irq < 0)
    {
        err = jpegd->irq;
        goto _fail;
    }

    jpegd->hw_id = rockchip_jpegd_read(jpegd, 0);
    LOG_D("Hardware ID = 0x%08x", jpegd->hw_id);

    dev->user_data = jpegd;

    rt_dm_dev_set_name_auto(&jpegd->parent, "jpegd");
    dev_name = rt_dm_dev_get_name(&jpegd->parent);

    jpegd->parent.type = RT_Device_Class_Char;
    /* Let clients allocate buffers in the JPEG decoder's DMA/IOMMU domain. */
    jpegd->parent.bus = dev->bus;
    jpegd->parent.ofw_node = dev->ofw_node;
#ifdef RT_USING_DEVICE_OPS
    jpegd->parent.ops = &rockchip_jpegd_ops;
#else
    jpegd->parent.control = rockchip_jpegd_control;
#endif

    if ((err = rt_device_register(&jpegd->parent, dev_name, RT_DEVICE_FLAG_DEACTIVATE)))
    {
        goto _fail;
    }

    rt_mutex_init(&jpegd->lock, dev_name, RT_IPC_FLAG_PRIO);

    rt_hw_interrupt_install(jpegd->irq, rockchip_jpegd_isr, jpegd, "jpegd");
    rt_hw_interrupt_umask(jpegd->irq);

    return RT_EOK;

_fail:
    rockchip_jpegd_free(jpegd);

    return err;
}

static rt_err_t rockchip_jpegd_remove(struct rt_platform_device *pdev)
{
    struct rockchip_jpegd *jpegd = pdev->parent.user_data;

    rt_hw_interrupt_mask(jpegd->irq);
    rt_pic_detach_irq(jpegd->irq, jpegd);

    rt_device_unregister(&jpegd->parent);

    rockchip_jpegd_free(jpegd);

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_jpegd_ofw_ids[] =
{
    { .compatible = "rockchip,rkv-jpeg-decoder-v1" },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_jpegd_driver =
{
    .name = "rockchip-jpegd",
    .ids = rockchip_jpegd_ofw_ids,

    .probe = rockchip_jpegd_probe,
    .remove = rockchip_jpegd_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_jpegd_driver);
