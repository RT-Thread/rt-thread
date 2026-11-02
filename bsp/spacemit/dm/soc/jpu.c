/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "soc.spacemit.jpu"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>
#include <jpu.h>
#include <spacemit.h>

#ifndef NIEUPORT_BASE
#define NIEUPORT_BASE                   0x0
#endif

#ifndef MMU_BASE
#define MMU_BASE                        0x500
#endif

#define MJPEG_PIC_START_REG             (NIEUPORT_BASE + 0x0000)
#define MJPEG_PIC_STATUS_REG            (NIEUPORT_BASE + 0x0004)
#define MJPEG_PIC_ERRMB_REG             (NIEUPORT_BASE + 0x0008)
#define MJPEG_PIC_SETMB_REG             (NIEUPORT_BASE + 0x000C)

#define MJPEG_PIC_CTRL_REG              (NIEUPORT_BASE + 0x0010)
#define MJPEG_PIC_SIZE_REG              (NIEUPORT_BASE + 0x0014)
#define MJPEG_MCU_INFO_REG              (NIEUPORT_BASE + 0x0018)
#define MJPEG_ROT_INFO_REG              (NIEUPORT_BASE + 0x001C)

#define MJPEG_SCL_INFO_REG              (NIEUPORT_BASE + 0x0020)
#define MJPEG_IF_INFO_REG               (NIEUPORT_BASE + 0x0024)
#define MJPEG_CLP_INFO_REG              (NIEUPORT_BASE + 0x0028)
#define MJPEG_OP_INFO_REG               (NIEUPORT_BASE + 0x002C)

#define MJPEG_DPB_CONFIG_REG            (NIEUPORT_BASE + 0x0030)
#define MJPEG_DPB_BASE00_REG            (NIEUPORT_BASE + 0x0034)
#define MJPEG_DPB_BASE01_REG            (NIEUPORT_BASE + 0x0038)
#define MJPEG_DPB_BASE02_REG            (NIEUPORT_BASE + 0x003C)
#define MJPEG_DPB_BASE10_REG            (NIEUPORT_BASE + 0x0040)
#define MJPEG_DPB_BASE11_REG            (NIEUPORT_BASE + 0x0044)
#define MJPEG_DPB_BASE12_REG            (NIEUPORT_BASE + 0x0048)
#define MJPEG_DPB_BASE20_REG            (NIEUPORT_BASE + 0x004C)
#define MJPEG_DPB_BASE21_REG            (NIEUPORT_BASE + 0x0050)
#define MJPEG_DPB_BASE22_REG            (NIEUPORT_BASE + 0x0054)
#define MJPEG_DPB_BASE30_REG            (NIEUPORT_BASE + 0x0058)
#define MJPEG_DPB_BASE31_REG            (NIEUPORT_BASE + 0x005C)
#define MJPEG_DPB_BASE32_REG            (NIEUPORT_BASE + 0x0060)
#define MJPEG_DPB_YSTRIDE_REG           (NIEUPORT_BASE + 0x0064)
#define MJPEG_DPB_CSTRIDE_REG           (NIEUPORT_BASE + 0x0068)
#define MJPEG_WRESP_CHECK_REG           (NIEUPORT_BASE + 0x006C)

#define MJPEG_CLP_BASE_REG              (NIEUPORT_BASE + 0x0070)
#define MJPEG_CLP_SIZE_REG              (NIEUPORT_BASE + 0x0074)
#define MJPEG_HUFF_CTRL_REG             (NIEUPORT_BASE + 0x0080)
#define MJPEG_HUFF_ADDR_REG             (NIEUPORT_BASE + 0x0084)
#define MJPEG_HUFF_DATA_REG             (NIEUPORT_BASE + 0x0088)
#define MJPEG_QMAT_CTRL_REG             (NIEUPORT_BASE + 0x0090)
#define MJPEG_QMAT_ADDR_REG             (NIEUPORT_BASE + 0x0094)
#define MJPEG_QMAT_DATA_REG             (NIEUPORT_BASE + 0x0098)
#define MJPEG_COEF_CTRL_REG             (NIEUPORT_BASE + 0x00A0)
#define MJPEG_COEF_ADDR_REG             (NIEUPORT_BASE + 0x00A4)
#define MJPEG_COEF_DATA_REG             (NIEUPORT_BASE + 0x00A8)
#define MJPEG_RST_INTVAL_REG            (NIEUPORT_BASE + 0x00B0)
#define MJPEG_RST_INDEX_REG             (NIEUPORT_BASE + 0x00B4)
#define MJPEG_RST_COUNT_REG             (NIEUPORT_BASE + 0x00B8)
#define MJPEG_INTR_MASK_REG             (NIEUPORT_BASE + 0x00C0)
#define MJPEG_CYCLE_INFO_REG            (NIEUPORT_BASE + 0x00C8)
#define MJPEG_DPCM_DIFF_Y_REG           (NIEUPORT_BASE + 0x00F0)
#define MJPEG_DPCM_DIFF_CB_REG          (NIEUPORT_BASE + 0x00F4)
#define MJPEG_DPCM_DIFF_CR_REG          (NIEUPORT_BASE + 0x00F8)

/* GBU*/
#define MJPEG_GBU_CTRL_REG              (NIEUPORT_BASE + 0x0100)
#define MJPEG_GBU_PBIT_BUSY_REG         (NIEUPORT_BASE + 0x0104)
#define MJPEG_GBU_BT_PTR_REG            (NIEUPORT_BASE + 0x0110)
#define MJPEG_GBU_WD_PTR_REG            (NIEUPORT_BASE + 0x0114)
#define MJPEG_GBU_TT_CNT_REG            (NIEUPORT_BASE + 0x0118)
#define MJPEG_GBU_PBIT_08_REG           (NIEUPORT_BASE + 0x0120)
#define MJPEG_GBU_PBIT_16_REG           (NIEUPORT_BASE + 0x0124)
#define MJPEG_GBU_PBIT_24_REG           (NIEUPORT_BASE + 0x0128)
#define MJPEG_GBU_PBIT_32_REG           (NIEUPORT_BASE + 0x012C)
#define MJPEG_GBU_BBSR_REG              (NIEUPORT_BASE + 0x0140)
#define MJPEG_GBU_BBER_REG              (NIEUPORT_BASE + 0x0144)
#define MJPEG_GBU_BBIR_REG              (NIEUPORT_BASE + 0x0148)
#define MJPEG_GBU_BBHR_REG              (NIEUPORT_BASE + 0x014C)
#define MJPEG_GBU_BCNT_REG              (NIEUPORT_BASE + 0x0158)
#define MJPEG_GBU_FF_RPTR_REG           (NIEUPORT_BASE + 0x0160)
#define MJPEG_GBU_FF_WPTR_REG           (NIEUPORT_BASE + 0x0164)

/* BBC */
#define MJPEG_BBC_END_ADDR_REG          (NIEUPORT_BASE + 0x0208)
#define MJPEG_BBC_WR_PTR_REG            (NIEUPORT_BASE + 0x020C)
#define MJPEG_BBC_RD_PTR_REG            (NIEUPORT_BASE + 0x0210)
#define MJPEG_BBC_EXT_ADDR_REG          (NIEUPORT_BASE + 0x0214)
#define MJPEG_BBC_INT_ADDR_REG          (NIEUPORT_BASE + 0x0218)
#define MJPEG_BBC_DATA_CNT_REG          (NIEUPORT_BASE + 0x021C)
#define MJPEG_BBC_COMMAND_REG           (NIEUPORT_BASE + 0x0220)
#define MJPEG_BBC_BUSY_REG              (NIEUPORT_BASE + 0x0224)
#define MJPEG_BBC_CTRL_REG              (NIEUPORT_BASE + 0x0228)
#define MJPEG_BBC_CUR_POS_REG           (NIEUPORT_BASE + 0x022C)
#define MJPEG_BBC_BAS_ADDR_REG          (NIEUPORT_BASE + 0x0230)
#define MJPEG_BBC_STRM_CTRL_REG         (NIEUPORT_BASE + 0x0234)
#define MJPEG_BBC_FLUSH_CMD_REG         (NIEUPORT_BASE + 0x0238)

#define JPU_MMU_TRI                     (NIEUPORT_BASE +0x400)

#define TBU_NUM                         32
#define MJPEG_MMU_TTBLR_BASE            (MMU_BASE + 0x40)
#define MJPEG_MMU_TTBHR_BASE            (MMU_BASE + 0x44)
#define MJPEG_MMU_TCR0_BASE             (MMU_BASE + 0x48)
#define MJPEG_MMU_TCR1_BASE             (MMU_BASE + 0x4c)
#define MJPEG_MMU_TBU_STATUS_BASE       (MMU_BASE + 0x50)
#define MJPEG_MMU_TBUx_STEP             0x20
#define MJPEG_MMU_BVA_LO                (MMU_BASE + 0x00)
#define MJPEG_MMU_BVA_HI                (MMU_BASE + 0x04)
#define MJPEG_MMU_TIMEOUT_VA_ADDR_LO    (MMU_BASE + 0x08)
#define MJPEG_MMU_TIMEOUT_VA_ADDR_HI    (MMU_BASE + 0x0C)
#define MJPEG_MMU_IRQ_STATUS            (MMU_BASE + 0x10)
#define MJPEG_MMU_IRQ_ENABLE            (MMU_BASE + 0x14)
#define MJPEG_MMU_TIMEOUT_VALUE         (MMU_BASE + 0x18)
#define MJPEG_MMU_ERROR_CLEAR           (MMU_BASE + 0x1C)
#define MJPEG_MMU_LAST_VA_ADDR_LO       (MMU_BASE + 0x20)
#define MJPEG_MMU_LAST_VA_ADDR_HI       (MMU_BASE + 0x24)
#define MJPEG_MMU_LAST_PA_ADDR_LO       (MMU_BASE + 0x28)
#define MJPEG_MMU_LAST_PA_ADDR_HI       (MMU_BASE + 0x2C)
#define MJPEG_MMU_VERSION               (MMU_BASE + 0x3C)

#define MAX_ENTRIES_PER_TTB             8096
#define ENTRY_SIZE                      4
#define MAX_SIZE_PER_TTB                (MAX_ENTRIES_PER_TTB*ENTRY_SIZE)
#define DEFAULT_TIMEOUT_CYCS            0x80000

#define TBU_INSTANCES_NUM               2

#define TTB_ENTRY_SHIFT                 12
#define AQUIRE_TIMEOUT_MS               100

#define JPU_TIMEOUT_MS                  5000
#define JPU_BBC_TIMEOUT_US              10000
#define JPU_ALIGN(value, align)          (((value) + (align) - 1) & ~((align) - 1))
#define JPU_BBC_PAGE_SIZE               256U

#define JPU_TBU_INPUT                   0
#define JPU_TBU_OUTPUT                  1

#define JPU_TBU_BASE_VA                 0x80000000
#define JPU_TBU_VA_STEP                 0x2000000

#define JPU_INT_FATAL_MASK              (RT_BIT(JPU_INT_ERROR) | \
                                         RT_BIT(JPU_INT_OVERFLOW))

#define JPU_DECODE_REG_NUM              ((MJPEG_BBC_STRM_CTRL_REG / sizeof(rt_uint32_t)) + 1)

enum spacemit_jpu_int_reason
{
    JPU_INT_DONE = 0,
    JPU_INT_ERROR,
    JPU_INT_BIT_BUF_EMPTY,
    JPU_INT_OVERFLOW = 3,
};

struct spacemit_jpu_map
{
    rt_ubase_t stream_phys;
    rt_ubase_t frame_phys;
    rt_size_t stream_size;
    rt_size_t frame_size;
    rt_ubase_t stream_iova;
    rt_ubase_t frame_iova;
};

struct spacemit_jpu_tbu
{
    rt_uint32_t *ttb_va;
    rt_ubase_t ttb_pa;
    rt_size_t ttb_size;
    rt_ubase_t va_base;
    rt_ubase_t va_end;
};

struct spacemit_jpu
{
    struct rt_device parent;

    struct rt_device *dev;
    void *regs;
    int irq;

    struct rt_clk *cclk;
    struct rt_clk *aclk;
    struct rt_clk *iclk;

    struct rt_reset_control *jpg_reset;
    struct rt_reset_control *lcd_mclk_reset;
    struct rt_reset_control *isp_ci_reset;
    struct rt_reset_control *freset;
    struct rt_reset_control *sreset;

    struct spacemit_jpu_tbu tbu[TBU_INSTANCES_NUM];
    rt_uint32_t page_size;
    rt_ubase_t va_base;
    rt_uint32_t time_out_cycs;
    rt_bool_t mmu_enable;

    rt_uint32_t irq_reason;
    rt_err_t error;
    struct rt_completion completion;
    struct rt_mutex lock;
    struct rt_spinlock hw_lock;
};

#define raw_to_spacemit_jpu(raw)    rt_container_of(raw, struct spacemit_jpu, parent)

rt_inline rt_uint32_t spacemit_jpu_read(struct spacemit_jpu *jpu, int offset)
{
    return HWREG32(jpu->regs + offset);
}

rt_inline void spacemit_jpu_write(struct spacemit_jpu *jpu, int offset, rt_uint32_t val)
{
    HWREG32(jpu->regs + offset) = val;
}

rt_inline void spacemit_jpu_set_bits(struct spacemit_jpu *jpu, int offset, rt_uint32_t bits)
{
    spacemit_jpu_write(jpu, offset, spacemit_jpu_read(jpu, offset) | bits);
}

rt_inline void spacemit_jpu_clear_bits(struct spacemit_jpu *jpu, int offset, rt_uint32_t bits)
{
    spacemit_jpu_write(jpu, offset, spacemit_jpu_read(jpu, offset) & ~bits);
}

static rt_err_t spacemit_jpu_clk_enable(struct spacemit_jpu *jpu)
{
    rt_err_t err;

    if (!rt_is_err_or_null(jpu->cclk))
    {
        err = rt_clk_prepare_enable(jpu->cclk);
        if (err)
        {
            return err;
        }
    }
    if (!rt_is_err_or_null(jpu->aclk))
    {
        err = rt_clk_prepare_enable(jpu->aclk);
        if (err)
        {
            return err;
        }
    }
    if (!rt_is_err_or_null(jpu->iclk))
    {
        err = rt_clk_prepare_enable(jpu->iclk);
        if (err)
        {
            return err;
        }
    }

    return RT_EOK;
}

static void spacemit_jpu_clk_disable(struct spacemit_jpu *jpu)
{
    if (!rt_is_err_or_null(jpu->iclk))
    {
        rt_clk_disable_unprepare(jpu->iclk);
    }
    if (!rt_is_err_or_null(jpu->aclk))
    {
        rt_clk_disable_unprepare(jpu->aclk);
    }
    if (!rt_is_err_or_null(jpu->cclk))
    {
        rt_clk_disable_unprepare(jpu->cclk);
    }
}

static void spacemit_jpu_reset_assert_all(struct spacemit_jpu *jpu)
{
    if (!rt_is_err_or_null(jpu->jpg_reset))
    {
        rt_reset_control_assert(jpu->jpg_reset);
    }
    if (!rt_is_err_or_null(jpu->lcd_mclk_reset))
    {
        rt_reset_control_assert(jpu->lcd_mclk_reset);
    }
    if (!rt_is_err_or_null(jpu->isp_ci_reset))
    {
        rt_reset_control_assert(jpu->isp_ci_reset);
    }
    if (!rt_is_err_or_null(jpu->freset))
    {
        rt_reset_control_assert(jpu->freset);
    }
    if (!rt_is_err_or_null(jpu->sreset))
    {
        rt_reset_control_assert(jpu->sreset);
    }
}

static void spacemit_jpu_reset_deassert_all(struct spacemit_jpu *jpu)
{
    if (!rt_is_err_or_null(jpu->jpg_reset))
    {
        rt_reset_control_deassert(jpu->jpg_reset);
    }
    if (!rt_is_err_or_null(jpu->lcd_mclk_reset))
    {
        rt_reset_control_deassert(jpu->lcd_mclk_reset);
    }
    if (!rt_is_err_or_null(jpu->isp_ci_reset))
    {
        rt_reset_control_deassert(jpu->isp_ci_reset);
    }
    if (!rt_is_err_or_null(jpu->freset))
    {
        rt_reset_control_deassert(jpu->freset);
    }
    if (!rt_is_err_or_null(jpu->sreset))
    {
        rt_reset_control_deassert(jpu->sreset);
    }
}

static void spacemit_jpu_enable_mmu_hw(struct spacemit_jpu *jpu);
static void spacemit_jpu_disable_mmu_hw(struct spacemit_jpu *jpu);

static void spacemit_jpu_hard_reset(struct spacemit_jpu *jpu)
{
    spacemit_jpu_clk_disable(jpu);
    spacemit_jpu_reset_assert_all(jpu);
    rt_hw_us_delay(5);
    spacemit_jpu_reset_deassert_all(jpu);
    spacemit_jpu_clk_enable(jpu);
    spacemit_jpu_write(jpu, MJPEG_PIC_STATUS_REG, 0);
}

static rt_err_t spacemit_jpu_sw_reset(struct spacemit_jpu *jpu)
{
    int timeout = JPU_BBC_TIMEOUT_US;

    spacemit_jpu_write(jpu, MJPEG_PIC_START_REG, RT_BIT(1));
    while (spacemit_jpu_read(jpu, MJPEG_PIC_START_REG) & RT_BIT(1))
    {
        if (--timeout == 0)
        {
            LOG_E("JPU software reset timeout");
            return -RT_ETIMEOUT;
        }
        rt_hw_us_delay(1);
    }

    return RT_EOK;
}

static void spacemit_jpu_write_tbu_table(struct spacemit_jpu *jpu,
        struct spacemit_jpu_tbu *tbu, rt_ubase_t iova, rt_ubase_t paddr, rt_size_t size)
{
    rt_uint32_t *ttb_entry;
    rt_size_t pages;
    rt_ubase_t mask;
    rt_uint32_t val;

    mask = (jpu->page_size == 4096) ? 0xFFFFFFFFFFFFF000ULL : 0xFFFFFFFFFFFF0000ULL;
    ttb_entry = tbu->ttb_va + (iova - tbu->va_base) / jpu->page_size;

    pages = RT_DIV_ROUND_UP(size, jpu->page_size);
    while (pages-- != 0)
    {
        val = (rt_uint32_t)(((paddr & mask) >> TTB_ENTRY_SHIFT) & 0x1FFFFF);
        *ttb_entry = val;
        ttb_entry++;
        paddr += jpu->page_size;
    }
}

static void spacemit_jpu_mmu_post(struct spacemit_jpu *jpu, int tbu_id)
{
    struct spacemit_jpu_tbu *tbu = &jpu->tbu[tbu_id];
    rt_uint32_t reg;
    int index;

    if (!jpu->mmu_enable)
    {
        return;
    }

    index = (tbu->va_base - jpu->va_base) / JPU_TBU_VA_STEP;

    if (tbu->ttb_size == 0)
    {
        spacemit_jpu_write(jpu, MJPEG_MMU_TCR0_BASE + index * MJPEG_MMU_TBUx_STEP, 0);
        return;
    }

    spacemit_jpu_write(jpu, MJPEG_MMU_TTBLR_BASE + index * MJPEG_MMU_TBUx_STEP,
            (rt_uint32_t)(tbu->ttb_pa & 0xFFFFFFFF));
    spacemit_jpu_write(jpu, MJPEG_MMU_TTBHR_BASE + index * MJPEG_MMU_TBUx_STEP,
            (rt_uint32_t)(tbu->ttb_pa >> 32));

    reg = (rt_uint32_t)((tbu->ttb_size - 1) << 16);
    reg |= RT_BIT(2);
    if (jpu->page_size == 64 * 1024)
    {
        reg |= RT_BIT(1);
    }
    reg |= RT_BIT(0);

    spacemit_jpu_write(jpu, MJPEG_MMU_TCR0_BASE + index * MJPEG_MMU_TBUx_STEP, reg);
}

static rt_err_t spacemit_jpu_mmu_map_one(struct spacemit_jpu *jpu, int tbu_id,
        rt_ubase_t phys, rt_ubase_t iova, rt_size_t size, rt_ubase_t *mapped_iova)
{
    struct spacemit_jpu_tbu *tbu = &jpu->tbu[tbu_id];
    int index;
    rt_ubase_t end;

    if (!size || !phys)
    {
        return -RT_EINVAL;
    }

    if (!jpu->mmu_enable)
    {
        spacemit_jpu_enable_mmu_hw(jpu);
    }

    index = (iova - jpu->va_base) / JPU_TBU_VA_STEP;
    tbu->va_base = jpu->va_base + index * JPU_TBU_VA_STEP;
    tbu->va_end = tbu->va_base + JPU_TBU_VA_STEP;

    if (iova < tbu->va_base || iova >= tbu->va_end)
    {
        return -RT_EINVAL;
    }

    end = iova + size;
    if (end > tbu->va_end)
    {
        return -RT_EINVAL;
    }

    if (!is_aligned(phys, jpu->page_size))
    {
        LOG_E("MMU map phys 0x%llx is not page aligned", (unsigned long long)phys);
        return -RT_EINVAL;
    }

    if (RT_DIV_ROUND_UP(end - tbu->va_base, jpu->page_size) > MAX_ENTRIES_PER_TTB)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&jpu->hw_lock);
    spacemit_jpu_write_tbu_table(jpu, tbu, iova, phys, size);

    if (end > tbu->va_base + jpu->page_size * tbu->ttb_size)
    {
        tbu->ttb_size = RT_DIV_ROUND_UP(end - tbu->va_base, jpu->page_size);
    }

    spacemit_jpu_mmu_post(jpu, tbu_id);
    rt_spin_unlock(&jpu->hw_lock);

    *mapped_iova = iova;
    return RT_EOK;
}

static void spacemit_jpu_enable_mmu_hw(struct spacemit_jpu *jpu)
{
    int i;

    if (jpu->mmu_enable)
    {
        return;
    }

    for (i = 0; i < TBU_INSTANCES_NUM; i++)
    {
        jpu->tbu[i].ttb_size = 0;
    }

    spacemit_jpu_write(jpu, MJPEG_MMU_BVA_LO, (rt_uint32_t)(jpu->va_base & 0xFFFFFFFF));
    spacemit_jpu_write(jpu, MJPEG_MMU_BVA_HI, (rt_uint32_t)(jpu->va_base >> 32));
    spacemit_jpu_write(jpu, MJPEG_MMU_TIMEOUT_VALUE, jpu->time_out_cycs);
    spacemit_jpu_set_bits(jpu, MJPEG_MMU_IRQ_ENABLE, 0);

    jpu->mmu_enable = RT_TRUE;
}

static void spacemit_jpu_disable_mmu_hw(struct spacemit_jpu *jpu)
{
    int i;

    if (!jpu->mmu_enable)
    {
        return;
    }

    rt_spin_lock(&jpu->hw_lock);
    jpu->mmu_enable = RT_FALSE;

    for (i = 0; i < TBU_INSTANCES_NUM; i++)
    {
        jpu->tbu[i].ttb_size = 0;
    }

    for (i = 0; i < TBU_NUM; i++)
    {
        spacemit_jpu_write(jpu, MJPEG_MMU_TCR0_BASE + MJPEG_MMU_TBUx_STEP * i, 0);
    }

    spacemit_jpu_clear_bits(jpu, MJPEG_MMU_IRQ_ENABLE, 0x1FF);
    rt_spin_unlock(&jpu->hw_lock);
}

static rt_err_t spacemit_jpu_mmu_map(struct spacemit_jpu *jpu,
        struct spacemit_jpu_map *map)
{
    rt_err_t err;
    rt_ubase_t stream_iova = JPU_TBU_BASE_VA + JPU_TBU_INPUT * JPU_TBU_VA_STEP;
    rt_ubase_t frame_iova = JPU_TBU_BASE_VA + JPU_TBU_OUTPUT * JPU_TBU_VA_STEP;
    rt_uint64_t stream_end;
    rt_uint64_t frame_end;

    if (!map)
    {
        return -RT_EINVAL;
    }

    stream_end = (rt_uint64_t)map->stream_phys + map->stream_size;
    frame_end = (rt_uint64_t)map->frame_phys + map->frame_size;
    if (stream_end > map->stream_phys && frame_end > map->frame_phys &&
        stream_end <= (rt_uint64_t)UINT32_MAX + 1 &&
        frame_end <= (rt_uint64_t)UINT32_MAX + 1)
    {
        /* Bypasses the JPU MMU for a single contiguous DMA segment. */
        spacemit_jpu_disable_mmu_hw(jpu);
        map->stream_iova = map->stream_phys;
        map->frame_iova = map->frame_phys;
        return RT_EOK;
    }

    err = spacemit_jpu_mmu_map_one(jpu, JPU_TBU_INPUT, map->stream_phys,
            stream_iova, map->stream_size, &stream_iova);
    if (err != RT_EOK)
    {
        spacemit_jpu_disable_mmu_hw(jpu);
        return err;
    }

    err = spacemit_jpu_mmu_map_one(jpu, JPU_TBU_OUTPUT, map->frame_phys,
            frame_iova, map->frame_size, &frame_iova);
    if (err != RT_EOK)
    {
        spacemit_jpu_disable_mmu_hw(jpu);
        return err;
    }

    spacemit_jpu_write(jpu, JPU_MMU_TRI, 0x01);

    map->stream_iova = stream_iova;
    map->frame_iova = frame_iova;

    return RT_EOK;
}

static rt_err_t spacemit_jpu_buffer_alloc(struct spacemit_jpu *jpu, struct jpu_buffer *buf)
{
    rt_ubase_t phys_addr;

    if (!buf || !buf->size)
    {
        return -RT_EINVAL;
    }

    buf->virt_addr = rt_dma_alloc_coherent(jpu->dev, buf->size, &phys_addr);
    if (!buf->virt_addr)
    {
        return -RT_ENOMEM;
    }

    buf->phys_addr = phys_addr;

    return RT_EOK;
}

static rt_err_t spacemit_jpu_buffer_free(struct spacemit_jpu *jpu, struct jpu_buffer *buf)
{
    if (!buf || !buf->virt_addr)
    {
        return -RT_EINVAL;
    }

    rt_dma_free_coherent(jpu->dev, buf->size, buf->virt_addr, buf->phys_addr);
    buf->virt_addr = RT_NULL;
    buf->phys_addr = 0;

    return RT_EOK;
}

static rt_err_t spacemit_jpu_query_frame(struct jpu_frame_info *frame)
{
    rt_uint32_t aligned_width;
    rt_uint32_t aligned_height;
    rt_uint32_t y_stride;
    rt_uint32_t c_stride;
    rt_uint32_t c_height;
    rt_uint64_t size;

    if (!frame || !frame->width || !frame->height)
    {
        return -RT_EINVAL;
    }

    switch (frame->format)
    {
    case JPU_FORMAT_420:
        aligned_width = JPU_ALIGN(frame->width, 16);
        aligned_height = JPU_ALIGN(frame->height, 16);
        y_stride = JPU_ALIGN(aligned_width, 8);
        c_stride = JPU_ALIGN(y_stride / 2, 16);
        c_height = JPU_ALIGN(aligned_height / 2, 8);
        break;
    case JPU_FORMAT_422:
        aligned_width = JPU_ALIGN(frame->width, 16);
        aligned_height = JPU_ALIGN(frame->height, 8);
        y_stride = JPU_ALIGN(aligned_width, 8);
        c_stride = JPU_ALIGN(y_stride / 2, 16);
        c_height = JPU_ALIGN(aligned_height, 8);
        break;
    case JPU_FORMAT_440:
        aligned_width = JPU_ALIGN(frame->width, 8);
        aligned_height = JPU_ALIGN(frame->height, 16);
        y_stride = JPU_ALIGN(aligned_width, 8);
        c_stride = JPU_ALIGN(y_stride, 8);
        c_height = JPU_ALIGN(aligned_height / 2, 8);
        break;
    case JPU_FORMAT_444:
        aligned_width = JPU_ALIGN(frame->width, 8);
        aligned_height = JPU_ALIGN(frame->height, 8);
        y_stride = JPU_ALIGN(aligned_width, 8);
        c_stride = JPU_ALIGN(y_stride, 8);
        c_height = JPU_ALIGN(aligned_height, 8);
        break;
    case JPU_FORMAT_400:
        aligned_width = JPU_ALIGN(frame->width, 8);
        aligned_height = JPU_ALIGN(frame->height, 8);
        y_stride = JPU_ALIGN(aligned_width, 8);
        c_stride = 0;
        c_height = 0;
        break;
    default:
        return -RT_EINVAL;
    }

    if (aligned_width > UINT16_MAX || aligned_height > UINT16_MAX ||
        y_stride > UINT16_MAX || c_stride > UINT16_MAX || c_height > UINT16_MAX)
    {
        return -RT_EINVAL;
    }

    size = (rt_uint64_t)y_stride * aligned_height +
            (rt_uint64_t)c_stride * c_height * 2;
    if (!size || size > JPU_BUFFER_MAX_SIZE)
    {
        return -RT_ENOMEM;
    }

    frame->aligned_width = aligned_width;
    frame->aligned_height = aligned_height;
    frame->y_stride = y_stride;
    frame->c_stride = c_stride;
    frame->c_height = c_height;
    frame->size = size;

    return RT_EOK;
}

static rt_err_t spacemit_jpu_validate_decode(struct jpu_decode_request *req)
{
    int component;
    rt_err_t err;

    if (!req || !req->stream_phys || !req->frame_phys ||
        !req->stream_size || req->entropy_offset >= req->stream_size ||
        req->stream_capacity > JPU_BUFFER_MAX_SIZE ||
        req->frame_capacity > JPU_BUFFER_MAX_SIZE ||
        req->stream_size > req->stream_capacity ||
        JPU_STREAM_PADDING > req->stream_capacity - req->stream_size)
    {
        return -RT_EINVAL;
    }

    if ((req->frame.format == JPU_FORMAT_400 && req->components != 1) ||
        (req->frame.format != JPU_FORMAT_400 && req->components != 3))
    {
        return -RT_EINVAL;
    }

    for (component = 0; component < req->components; ++component)
    {
        if (req->dc_selector[component] > 1 || req->ac_selector[component] > 1)
        {
            return -RT_EINVAL;
        }
    }

    if ((err = spacemit_jpu_query_frame(&req->frame)) != RT_EOK)
    {
        return err;
    }
    if (req->frame_capacity < req->frame.size)
    {
        return -RT_ENOMEM;
    }

    return RT_EOK;
}

static const rt_uint8_t jpu_default_huff_bits[JPU_HUFF_TABLE_NUM][JPU_HUFF_BITS_NUM] =
{
    { 0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01,
      0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03,
      0x05, 0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 0x7d },
    { 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
      0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04,
      0x07, 0x05, 0x04, 0x04, 0x00, 0x01, 0x02, 0x77 },
};

static const rt_uint8_t jpu_default_huff_values[JPU_HUFF_TABLE_NUM][JPU_HUFF_VALUES_NUM] =
{
    {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b,
    },
    {
        0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
        0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
        0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
        0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
        0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
        0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
        0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
        0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
        0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
        0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
        0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
        0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
        0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
        0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
        0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
        0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
        0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
        0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
        0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
        0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
        0xf9, 0xfa,
    },
    {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b,
    },
    {
        0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,
        0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
        0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
        0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
        0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
        0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
        0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38,
        0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
        0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
        0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
        0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
        0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
        0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
        0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
        0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
        0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
        0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2,
        0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
        0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
        0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
        0xf9, 0xfa,
    },
};

static rt_bool_t spacemit_jpu_uses_default_huffman(const struct jpu_decode_request *req)
{
    rt_bool_t checked[JPU_HUFF_TABLE_NUM] = { RT_FALSE };
    int component;

    for (component = 0; component < req->components; ++component)
    {
        int tables[2] =
        {
            req->dc_selector[component] * 2,
            req->ac_selector[component] * 2 + 1,
        };
        int type;

        for (type = 0; type < 2; ++type)
        {
            int index = tables[type];
            int count = 0;
            int i;

            if (checked[index])
            {
                continue;
            }
            checked[index] = RT_TRUE;

            for (i = 0; i < JPU_HUFF_BITS_NUM; ++i)
            {
                count += req->tables.huff_bits[index][i];
            }

            if (rt_memcmp(req->tables.huff_bits[index],
                    jpu_default_huff_bits[index], JPU_HUFF_BITS_NUM) ||
                rt_memcmp(req->tables.huff_values[index],
                    jpu_default_huff_values[index], count))
            {
                return RT_FALSE;
            }
        }
    }

    return RT_TRUE;
}

static void spacemit_jpu_build_decode_regs(const struct jpu_decode_request *req,
        const struct spacemit_jpu_map *map, rt_uint32_t *reg)
{
    const struct jpu_frame_info *frame = &req->frame;
    rt_uint32_t y_size = frame->y_stride * frame->aligned_height;
    rt_uint32_t c_size = frame->c_stride * frame->c_height;
    rt_uint32_t dc = req->dc_selector[0];
    rt_uint32_t ac = req->ac_selector[0];
    rt_uint32_t mcu_width;
    rt_uint32_t mcu_height;
    rt_uint32_t mcu_blocks;
    rt_uint32_t bus_requests;
    rt_uint32_t comp0;
    rt_uint32_t stream_end = (rt_uint32_t)map->stream_iova + req->stream_size;

    switch (frame->format)
    {
    case JPU_FORMAT_420:
        mcu_width = 16;
        mcu_height = 16;
        mcu_blocks = 6;
        bus_requests = 2;
        break;
    case JPU_FORMAT_422:
        mcu_width = 16;
        mcu_height = 8;
        mcu_blocks = 4;
        bus_requests = 3;
        break;
    case JPU_FORMAT_440:
        mcu_width = 8;
        mcu_height = 16;
        mcu_blocks = 4;
        bus_requests = 8;
        break;
    case JPU_FORMAT_444:
        mcu_width = 8;
        mcu_height = 8;
        mcu_blocks = 3;
        bus_requests = 4;
        break;
    default:
        mcu_width = 8;
        mcu_height = 8;
        mcu_blocks = 1;
        bus_requests = 4;
        break;
    }

    if (req->components == 3)
    {
        dc = (dc << 1) | req->dc_selector[1];
        dc = (dc << 1) | req->dc_selector[2];
        ac = (ac << 1) | req->ac_selector[1];
        ac = (ac << 1) | req->ac_selector[2];
    }
    else
    {
        dc <<= 2;
        ac <<= 2;
    }

    comp0 = ((mcu_width >> 3) << 2) | (mcu_height >> 3);
    reg[MJPEG_PIC_START_REG / 4] = 1;
    reg[MJPEG_PIC_CTRL_REG / 4] = (ac << 10) | (dc << 7);
    if (!spacemit_jpu_uses_default_huffman(req))
    {
        reg[MJPEG_PIC_CTRL_REG / 4] |= RT_BIT(6);
    }
    reg[MJPEG_PIC_SIZE_REG / 4] = ((rt_uint32_t)frame->aligned_width << 16) |
            frame->aligned_height;
    reg[MJPEG_MCU_INFO_REG / 4] = (mcu_blocks << 16) |
            ((rt_uint32_t)req->components << 12) | (comp0 << 8) |
            ((req->components == 3 ? 5U : 0U) << 4) |
            (req->components == 3 ? 5U : 0U);
    reg[MJPEG_OP_INFO_REG / 4] = bus_requests;
    reg[MJPEG_DPB_BASE00_REG / 4] = (rt_uint32_t)map->frame_iova;
    reg[MJPEG_DPB_BASE01_REG / 4] = (rt_uint32_t)map->frame_iova + y_size;
    reg[MJPEG_DPB_BASE02_REG / 4] = (rt_uint32_t)map->frame_iova + y_size + c_size;
    reg[MJPEG_DPB_YSTRIDE_REG / 4] = frame->y_stride;
    reg[MJPEG_DPB_CSTRIDE_REG / 4] = frame->c_stride;
    reg[MJPEG_RST_INTVAL_REG / 4] = req->restart_interval;
    reg[MJPEG_INTR_MASK_REG / 4] =
            (~(RT_BIT(JPU_INT_DONE) | RT_BIT(JPU_INT_ERROR) |
               RT_BIT(JPU_INT_BIT_BUF_EMPTY))) & 0x3ff;
    reg[MJPEG_BBC_WR_PTR_REG / 4] = stream_end;
    reg[MJPEG_BBC_END_ADDR_REG / 4] = JPU_ALIGN(stream_end, JPU_BBC_PAGE_SIZE);
    reg[MJPEG_BBC_RD_PTR_REG / 4] = (rt_uint32_t)map->stream_iova;
    reg[MJPEG_BBC_BAS_ADDR_REG / 4] = (rt_uint32_t)map->stream_iova;
    reg[MJPEG_BBC_STRM_CTRL_REG / 4] = RT_BIT(31) |
            RT_DIV_ROUND_UP(req->stream_size, JPU_BBC_PAGE_SIZE);
}

static void spacemit_jpu_make_huffman_table(const struct jpu_dec_tables *tables,
        rt_uint16_t min[JPU_HUFF_TABLE_NUM][JPU_HUFF_BITS_NUM],
        rt_uint16_t max[JPU_HUFF_TABLE_NUM][JPU_HUFF_BITS_NUM],
        rt_uint8_t ptr[JPU_HUFF_TABLE_NUM][JPU_HUFF_BITS_NUM])
{
    int table, length;

    for (table = 0; table < JPU_HUFF_TABLE_NUM; ++table)
    {
        rt_uint32_t code = 0;
        rt_uint32_t value_index = 0;
        rt_bool_t have_code = RT_FALSE;

        for (length = 0; length < JPU_HUFF_BITS_NUM; ++length)
        {
            rt_uint32_t count = tables->huff_bits[table][length];

            if (count)
            {
                ptr[table][length] = value_index;
                min[table][length] = code;
                max[table][length] = code + count - 1;
                value_index += count;
                code = (max[table][length] + 1) << 1;
                have_code = RT_TRUE;
            }
            else
            {
                ptr[table][length] = 0xff;
                min[table][length] = 0xffff;
                max[table][length] = 0xffff;
                if (have_code)
                {
                    code <<= 1;
                }
            }
        }
    }
}

static rt_err_t spacemit_jpu_load_huffman(struct spacemit_jpu *jpu,
        const struct jpu_dec_tables *tables)
{
    static const rt_uint8_t order[JPU_HUFF_TABLE_NUM] = { 0, 2, 1, 3 };
    rt_uint16_t min[JPU_HUFF_TABLE_NUM][JPU_HUFF_BITS_NUM];
    rt_uint16_t max[JPU_HUFF_TABLE_NUM][JPU_HUFF_BITS_NUM];
    rt_uint8_t ptr[JPU_HUFF_TABLE_NUM][JPU_HUFF_BITS_NUM];
    int count[JPU_HUFF_TABLE_NUM] = { 0 };
    int table, i;

    for (table = 0; table < JPU_HUFF_TABLE_NUM; ++table)
    {
        for (i = 0; i < JPU_HUFF_BITS_NUM; ++i)
        {
            count[table] += tables->huff_bits[table][i];
        }

        if (count[table] <= 0 ||
            count[table] > ((table & 1) ? JPU_HUFF_VALUES_NUM : 12))
        {
            return -RT_EINVAL;
        }
    }

    spacemit_jpu_make_huffman_table(tables, min, max, ptr);

    spacemit_jpu_write(jpu, MJPEG_HUFF_CTRL_REG, 0x003);
    for (table = 0; table < JPU_HUFF_TABLE_NUM; ++table)
    {
        int index = order[table];

        for (i = 0; i < JPU_HUFF_BITS_NUM; ++i)
        {
            spacemit_jpu_write(jpu, MJPEG_HUFF_DATA_REG,
                    (rt_uint32_t)(rt_int32_t)(rt_int16_t)min[index][i]);
        }
    }

    spacemit_jpu_write(jpu, MJPEG_HUFF_CTRL_REG, 0x403);
    spacemit_jpu_write(jpu, MJPEG_HUFF_ADDR_REG, 0x440);
    for (table = 0; table < JPU_HUFF_TABLE_NUM; ++table)
    {
        int index = order[table];

        for (i = 0; i < JPU_HUFF_BITS_NUM; ++i)
        {
            spacemit_jpu_write(jpu, MJPEG_HUFF_DATA_REG,
                    (rt_uint32_t)(rt_int32_t)(rt_int16_t)max[index][i]);
        }
    }

    spacemit_jpu_write(jpu, MJPEG_HUFF_CTRL_REG, 0x803);
    spacemit_jpu_write(jpu, MJPEG_HUFF_ADDR_REG, 0x880);
    for (table = 0; table < JPU_HUFF_TABLE_NUM; ++table)
    {
        int index = order[table];

        for (i = 0; i < JPU_HUFF_BITS_NUM; ++i)
        {
            spacemit_jpu_write(jpu, MJPEG_HUFF_DATA_REG,
                    (rt_uint32_t)(rt_int32_t)(rt_int8_t)ptr[index][i]);
        }
    }

    spacemit_jpu_write(jpu, MJPEG_HUFF_CTRL_REG, 0xc03);
    for (table = 0; table < JPU_HUFF_TABLE_NUM; ++table)
    {
        int index = order[table];
        int slots = (index & 1) ? JPU_HUFF_VALUES_NUM : 12;

        for (i = 0; i < count[index]; ++i)
        {
            spacemit_jpu_write(jpu, MJPEG_HUFF_DATA_REG,
                    (rt_uint32_t)(rt_int32_t)(rt_int8_t)tables->huff_values[index][i]);
        }
        for (; i < slots; ++i)
        {
            spacemit_jpu_write(jpu, MJPEG_HUFF_DATA_REG, 0xffffffff);
        }
    }
    spacemit_jpu_write(jpu, MJPEG_HUFF_CTRL_REG, 0);

    return RT_EOK;
}

static void spacemit_jpu_load_quant(struct spacemit_jpu *jpu,
        const struct jpu_dec_tables *tables)
{
    static const rt_uint32_t control[JPU_QUANT_COMPONENT_NUM] = { 0x03, 0x43, 0x83 };
    int component, i;

    for (component = 0; component < JPU_QUANT_COMPONENT_NUM; ++component)
    {
        spacemit_jpu_write(jpu, MJPEG_QMAT_CTRL_REG, control[component]);
        for (i = 0; i < JPU_QUANT_VALUES_NUM; ++i)
        {
            spacemit_jpu_write(jpu, MJPEG_QMAT_DATA_REG,
                    tables->quant[component][i]);
        }
        spacemit_jpu_write(jpu, MJPEG_QMAT_CTRL_REG, 0);
    }
}

static rt_err_t spacemit_jpu_wait_bbc(struct spacemit_jpu *jpu)
{
    int timeout = JPU_BBC_TIMEOUT_US;

    while (spacemit_jpu_read(jpu, MJPEG_BBC_BUSY_REG) & 1)
    {
        if (--timeout == 0)
        {
            LOG_E("JPU BBC preload timeout");
            return -RT_ETIMEOUT;
        }
        rt_hw_us_delay(1);
    }

    return RT_EOK;
}

static rt_err_t spacemit_jpu_prepare_stream(struct spacemit_jpu *jpu,
        rt_uint32_t stream_base, rt_uint32_t entropy_offset)
{
    rt_uint32_t page = entropy_offset >> 8;
    rt_uint32_t word = (entropy_offset & 0xf0) >> 2;
    rt_uint32_t bit = (entropy_offset & 0xf) << 3;
    int i;

    if (page & 1)
    {
        word += 64;
    }
    if (word & 1)
    {
        --word;
    }

    for (i = 0; i < 2; ++i)
    {
        rt_uint32_t current = page + i;

        spacemit_jpu_write(jpu, MJPEG_BBC_CUR_POS_REG, current);
        spacemit_jpu_write(jpu, MJPEG_BBC_EXT_ADDR_REG, stream_base + (current << 8));
        spacemit_jpu_write(jpu, MJPEG_BBC_INT_ADDR_REG, (current & 1) << 6);
        spacemit_jpu_write(jpu, MJPEG_BBC_DATA_CNT_REG, 64);
        spacemit_jpu_write(jpu, MJPEG_BBC_COMMAND_REG, 0);
        if (spacemit_jpu_wait_bbc(jpu) != RT_EOK)
        {
            return -RT_ETIMEOUT;
        }
    }

    spacemit_jpu_write(jpu, MJPEG_BBC_CUR_POS_REG, page + 2);
    spacemit_jpu_write(jpu, MJPEG_BBC_CTRL_REG, 1);
    spacemit_jpu_write(jpu, MJPEG_GBU_WD_PTR_REG, word);
    spacemit_jpu_write(jpu, MJPEG_GBU_BBSR_REG, 0);
    spacemit_jpu_write(jpu, MJPEG_GBU_BBER_REG, 127);
    spacemit_jpu_write(jpu, MJPEG_GBU_BBIR_REG, (page & 1) ? 0 : 64);
    spacemit_jpu_write(jpu, MJPEG_GBU_BBHR_REG, (page & 1) ? 0 : 64);
    spacemit_jpu_write(jpu, MJPEG_GBU_CTRL_REG, 4);
    spacemit_jpu_write(jpu, MJPEG_GBU_FF_RPTR_REG, bit);

    return RT_EOK;
}

static void spacemit_jpu_dump_timeout(struct spacemit_jpu *jpu)
{
    LOG_E("core: start=%08x status=%08x errmb=%08x cycle=%08x",
            spacemit_jpu_read(jpu, MJPEG_PIC_START_REG),
            spacemit_jpu_read(jpu, MJPEG_PIC_STATUS_REG),
            spacemit_jpu_read(jpu, MJPEG_PIC_ERRMB_REG),
            spacemit_jpu_read(jpu, MJPEG_CYCLE_INFO_REG));
    LOG_E("BBC: busy=%08x pos=%08x rd=%08x wr=%08x end=%08x ctrl=%08x",
            spacemit_jpu_read(jpu, MJPEG_BBC_BUSY_REG),
            spacemit_jpu_read(jpu, MJPEG_BBC_CUR_POS_REG),
            spacemit_jpu_read(jpu, MJPEG_BBC_RD_PTR_REG),
            spacemit_jpu_read(jpu, MJPEG_BBC_WR_PTR_REG),
            spacemit_jpu_read(jpu, MJPEG_BBC_END_ADDR_REG),
            spacemit_jpu_read(jpu, MJPEG_BBC_STRM_CTRL_REG));
    LOG_E("GBU: ctrl=%08x word=%08x bit=%08x count=%08x MMU=%08x/%08x/%08x",
            spacemit_jpu_read(jpu, MJPEG_GBU_CTRL_REG),
            spacemit_jpu_read(jpu, MJPEG_GBU_WD_PTR_REG),
            spacemit_jpu_read(jpu, MJPEG_GBU_FF_RPTR_REG),
            spacemit_jpu_read(jpu, MJPEG_GBU_TT_CNT_REG),
            spacemit_jpu_read(jpu, MJPEG_MMU_IRQ_STATUS),
            spacemit_jpu_read(jpu, MJPEG_MMU_TBU_STATUS_BASE),
            spacemit_jpu_read(jpu, MJPEG_MMU_TBU_STATUS_BASE + MJPEG_MMU_TBUx_STEP));
}

#if DBG_LVL >= DBG_LOG
static void spacemit_jpu_dump_config(struct spacemit_jpu *jpu,
        const struct spacemit_jpu_map *map)
{
    LOG_D("DMA: stream=%08x->%08x/%u frame=%08x->%08x/%u MMU=%u",
            (rt_uint32_t)map->stream_phys, (rt_uint32_t)map->stream_iova,
            (unsigned int)map->stream_size, (rt_uint32_t)map->frame_phys,
            (rt_uint32_t)map->frame_iova, (unsigned int)map->frame_size,
            (unsigned int)jpu->mmu_enable);
    LOG_D("core: mask=%08x ctrl=%08x pic=%08x mcu=%08x op=%08x dpbcfg=%08x",
            spacemit_jpu_read(jpu, MJPEG_INTR_MASK_REG),
            spacemit_jpu_read(jpu, MJPEG_PIC_CTRL_REG),
            spacemit_jpu_read(jpu, MJPEG_PIC_SIZE_REG),
            spacemit_jpu_read(jpu, MJPEG_MCU_INFO_REG),
            spacemit_jpu_read(jpu, MJPEG_OP_INFO_REG),
            spacemit_jpu_read(jpu, MJPEG_DPB_CONFIG_REG));
    LOG_D("DPB: y=%08x cb=%08x cr=%08x stride=%08x/%08x",
            spacemit_jpu_read(jpu, MJPEG_DPB_BASE00_REG),
            spacemit_jpu_read(jpu, MJPEG_DPB_BASE01_REG),
            spacemit_jpu_read(jpu, MJPEG_DPB_BASE02_REG),
            spacemit_jpu_read(jpu, MJPEG_DPB_YSTRIDE_REG),
            spacemit_jpu_read(jpu, MJPEG_DPB_CSTRIDE_REG));
    LOG_D("BBC: base=%08x rd=%08x wr=%08x end=%08x pos=%08x ctrl=%08x",
            spacemit_jpu_read(jpu, MJPEG_BBC_BAS_ADDR_REG),
            spacemit_jpu_read(jpu, MJPEG_BBC_RD_PTR_REG),
            spacemit_jpu_read(jpu, MJPEG_BBC_WR_PTR_REG),
            spacemit_jpu_read(jpu, MJPEG_BBC_END_ADDR_REG),
            spacemit_jpu_read(jpu, MJPEG_BBC_CUR_POS_REG),
            spacemit_jpu_read(jpu, MJPEG_BBC_STRM_CTRL_REG));
    LOG_D("GBU: word=%08x bit=%08x range=%08x/%08x/%08x/%08x ctrl=%08x",
            spacemit_jpu_read(jpu, MJPEG_GBU_WD_PTR_REG),
            spacemit_jpu_read(jpu, MJPEG_GBU_FF_RPTR_REG),
            spacemit_jpu_read(jpu, MJPEG_GBU_BBSR_REG),
            spacemit_jpu_read(jpu, MJPEG_GBU_BBER_REG),
            spacemit_jpu_read(jpu, MJPEG_GBU_BBIR_REG),
            spacemit_jpu_read(jpu, MJPEG_GBU_BBHR_REG),
            spacemit_jpu_read(jpu, MJPEG_GBU_CTRL_REG));
}
#endif

static rt_err_t spacemit_jpu_submit(struct spacemit_jpu *jpu,
        struct jpu_decode_request *req)
{
    struct spacemit_jpu_map map;
    rt_uint32_t reg[JPU_DECODE_REG_NUM] = { 0 };
    rt_err_t err;

    if ((err = spacemit_jpu_validate_decode(req)) != RT_EOK)
    {
        return err;
    }

    if (spacemit_jpu_read(jpu, MJPEG_PIC_START_REG) != 0)
    {
        LOG_E("JPU busy");
        return -RT_EBUSY;
    }

    req->irq_status = 0;
    req->picture_status = 0;
    req->error_mcu = 0;
    req->cycles = 0;

    if ((err = spacemit_jpu_sw_reset(jpu)) != RT_EOK)
    {
        return err;
    }
    rt_completion_init(&jpu->completion);
    jpu->error = RT_EOK;
    jpu->irq_reason = 0;

    map.stream_phys = req->stream_phys;
    map.stream_size = req->stream_capacity;
    map.frame_phys = req->frame_phys;
    map.frame_size = req->frame_capacity;
    if ((err = spacemit_jpu_mmu_map(jpu, &map)) != RT_EOK)
    {
        LOG_E("failed to map decode buffers: %d", err);
        goto _fail;
    }

    spacemit_jpu_build_decode_regs(req, &map, reg);

    LOG_D("config: pic=%08x mcu=%08x ctrl=%08x entropy=%u stream=%u",
            reg[MJPEG_PIC_SIZE_REG / sizeof(rt_uint32_t)],
            reg[MJPEG_MCU_INFO_REG / sizeof(rt_uint32_t)],
            reg[MJPEG_PIC_CTRL_REG / sizeof(rt_uint32_t)],
            req->entropy_offset, req->stream_size);

    /* Keep this sequence aligned with JPU_DecSetRdPtrEx() and
     * JPU_DecStartOneFrame() from the vendor library. */
    spacemit_jpu_write(jpu, MJPEG_BBC_RD_PTR_REG,
            reg[MJPEG_BBC_RD_PTR_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_INTR_MASK_REG,
            reg[MJPEG_INTR_MASK_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_BBC_WR_PTR_REG,
            reg[MJPEG_BBC_WR_PTR_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_BBC_END_ADDR_REG,
            reg[MJPEG_BBC_END_ADDR_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_BBC_BAS_ADDR_REG,
            reg[MJPEG_BBC_BAS_ADDR_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_GBU_TT_CNT_REG, 0);
    spacemit_jpu_write(jpu, MJPEG_GBU_TT_CNT_REG + sizeof(rt_uint32_t), 0);
    spacemit_jpu_write(jpu, MJPEG_PIC_ERRMB_REG, 0);
    spacemit_jpu_write(jpu, MJPEG_PIC_CTRL_REG,
            reg[MJPEG_PIC_CTRL_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_PIC_SIZE_REG,
            reg[MJPEG_PIC_SIZE_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_OP_INFO_REG,
            reg[MJPEG_OP_INFO_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_MCU_INFO_REG,
            reg[MJPEG_MCU_INFO_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_DPB_CONFIG_REG, 0);
    spacemit_jpu_write(jpu, MJPEG_RST_INTVAL_REG,
            reg[MJPEG_RST_INTVAL_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_SCL_INFO_REG, 0);

    if ((reg[MJPEG_PIC_CTRL_REG / sizeof(rt_uint32_t)] & RT_BIT(6)) &&
        (err = spacemit_jpu_load_huffman(jpu, &req->tables)) != RT_EOK)
    {
        LOG_E("invalid Huffman tables");
        goto _fail;
    }

    spacemit_jpu_load_quant(jpu, &req->tables);
    if ((err = spacemit_jpu_prepare_stream(jpu,
            map.stream_iova, req->entropy_offset)) != RT_EOK)
    {
        goto _fail;
    }
    if (jpu->error != RT_EOK)
    {
        err = jpu->error;
        goto _fail;
    }

    spacemit_jpu_write(jpu, MJPEG_BBC_STRM_CTRL_REG,
            reg[MJPEG_BBC_STRM_CTRL_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_RST_INDEX_REG, 0);
    spacemit_jpu_write(jpu, MJPEG_RST_COUNT_REG, 0);
    spacemit_jpu_write(jpu, MJPEG_DPCM_DIFF_Y_REG, 0);
    spacemit_jpu_write(jpu, MJPEG_DPCM_DIFF_CB_REG, 0);
    spacemit_jpu_write(jpu, MJPEG_DPCM_DIFF_CR_REG, 0);
    spacemit_jpu_write(jpu, MJPEG_GBU_FF_RPTR_REG,
            (req->entropy_offset & 0xf) << 3);
    spacemit_jpu_write(jpu, MJPEG_GBU_CTRL_REG, 3);

    spacemit_jpu_write(jpu, MJPEG_ROT_INFO_REG, 0);
    spacemit_jpu_write(jpu, MJPEG_DPB_BASE00_REG,
            reg[MJPEG_DPB_BASE00_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_DPB_BASE01_REG,
            reg[MJPEG_DPB_BASE01_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_DPB_BASE02_REG,
            reg[MJPEG_DPB_BASE02_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_DPB_YSTRIDE_REG,
            reg[MJPEG_DPB_YSTRIDE_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_DPB_CSTRIDE_REG,
            reg[MJPEG_DPB_CSTRIDE_REG / sizeof(rt_uint32_t)]);
    spacemit_jpu_write(jpu, MJPEG_CLP_INFO_REG, 0);

    rt_hw_dsb();
#if DBG_LVL >= DBG_LOG
    spacemit_jpu_dump_config(jpu, &map);
#endif

    spacemit_jpu_write(jpu, MJPEG_PIC_START_REG, reg[MJPEG_PIC_START_REG / 4]);

    if (rt_completion_wait(&jpu->completion,
            rt_tick_from_millisecond(JPU_TIMEOUT_MS)) != RT_EOK)
    {
        LOG_E("JPU timeout");
        spacemit_jpu_dump_timeout(jpu);
        err = -RT_ETIMEOUT;
        goto _fail;
    }

    req->irq_status = jpu->irq_reason;
    req->picture_status = spacemit_jpu_read(jpu, MJPEG_PIC_STATUS_REG);
    req->error_mcu = spacemit_jpu_read(jpu, MJPEG_PIC_ERRMB_REG);
    req->cycles = spacemit_jpu_read(jpu, MJPEG_CYCLE_INFO_REG);

    spacemit_jpu_disable_mmu_hw(jpu);

    if (jpu->error != RT_EOK)
    {
        spacemit_jpu_hard_reset(jpu);
    }

    return jpu->error;

_fail:
    req->irq_status = jpu->irq_reason;
    req->picture_status = spacemit_jpu_read(jpu, MJPEG_PIC_STATUS_REG);
    req->error_mcu = spacemit_jpu_read(jpu, MJPEG_PIC_ERRMB_REG);
    req->cycles = spacemit_jpu_read(jpu, MJPEG_CYCLE_INFO_REG);
    spacemit_jpu_hard_reset(jpu);
    spacemit_jpu_disable_mmu_hw(jpu);
    return err;
}

static rt_err_t spacemit_jpu_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct spacemit_jpu *jpu = raw_to_spacemit_jpu(dev);

    rt_mutex_take(&jpu->lock, RT_WAITING_FOREVER);

    switch (cmd)
    {
    case JPU_DECODE:
    {
        struct jpu_decode_request *req = args;

        if (!req)
        {
            err = -RT_EINVAL;
            break;
        }

        err = spacemit_jpu_submit(jpu, req);
        break;
    }
    case JPU_QUERY_FRAME:
    {
        struct jpu_frame_info *frame = args;

        if (!frame)
        {
            err = -RT_EINVAL;
            break;
        }

        err = spacemit_jpu_query_frame(frame);
        break;
    }
    case JPU_ALLOC_BUFFER:
    {
        struct jpu_buffer *buf = args;

        if (!buf)
        {
            err = -RT_EINVAL;
            break;
        }

        err = spacemit_jpu_buffer_alloc(jpu, buf);
        break;
    }
    case JPU_FREE_BUFFER:
    {
        struct jpu_buffer *buf = args;

        if (!buf)
        {
            err = -RT_EINVAL;
            break;
        }

        err = spacemit_jpu_buffer_free(jpu, buf);
        break;
    }
    case JPU_RESET:
        spacemit_jpu_hard_reset(jpu);
        spacemit_jpu_disable_mmu_hw(jpu);
        break;
    case JPU_GET_MMU_VERSION:
    {
        rt_uint32_t *version = args;

        if (!version)
        {
            err = -RT_EINVAL;
            break;
        }

        *version = spacemit_jpu_read(jpu, MJPEG_MMU_VERSION);
        break;
    }
    default:
        err = -RT_ENOSYS;
        break;
    }

    rt_mutex_release(&jpu->lock);

    return err;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops spacemit_jpu_ops =
{
    .control = spacemit_jpu_control,
};
#endif

static void spacemit_jpu_isr(int irqno, void *param)
{
    rt_uint32_t int_reason;
    rt_uint32_t mmu_irq_status;
    rt_bool_t completed = RT_FALSE;
    struct spacemit_jpu *jpu = param;

    int_reason = spacemit_jpu_read(jpu, MJPEG_PIC_STATUS_REG);
    if (int_reason != 0)
    {
        if (int_reason & RT_BIT(JPU_INT_DONE))
        {
            spacemit_jpu_write(jpu, MJPEG_BBC_FLUSH_CMD_REG, 0);
        }

        spacemit_jpu_write(jpu, MJPEG_PIC_STATUS_REG, int_reason);
    }

    mmu_irq_status = spacemit_jpu_read(jpu, MJPEG_MMU_IRQ_STATUS);
    if (mmu_irq_status != 0)
    {
        LOG_E("JPU MMU fault: status 0x%08x", mmu_irq_status);

        if (mmu_irq_status & 0xFF)
        {
            spacemit_jpu_set_bits(jpu, MJPEG_MMU_ERROR_CLEAR, RT_BIT(1));
        }

        spacemit_jpu_write(jpu, MJPEG_MMU_IRQ_STATUS, mmu_irq_status);
        jpu->error = -RT_EIO;
        completed = RT_TRUE;
    }

    if (int_reason != 0)
    {
        jpu->irq_reason |= int_reason;

        if (int_reason & JPU_INT_FATAL_MASK)
        {
            LOG_E("JPU error, status = 0x%08x", int_reason);
            jpu->error = -RT_EIO;
        }

        if (int_reason & (RT_BIT(JPU_INT_DONE) | JPU_INT_FATAL_MASK))
        {
            completed = RT_TRUE;
        }
    }

    if (completed)
    {
        rt_completion_done(&jpu->completion);
    }
}

static struct rt_reset_control *spacemit_jpu_get_reset(struct rt_device *dev, const char *name)
{
    struct rt_reset_control *rstc = rt_reset_control_get_by_name(dev, name);

    if (rt_is_err(rstc))
    {
        LOG_W("no %s reset, err = %d", name, rt_ptr_err(rstc));
        return RT_NULL;
    }

    return rstc;
}

static void spacemit_jpu_free(struct spacemit_jpu *jpu)
{
    void *ttb_va = RT_NULL;
    rt_ubase_t ttb_pa = 0;

    if (jpu->tbu[0].ttb_va)
    {
        ttb_va = jpu->tbu[0].ttb_va;
        ttb_pa = jpu->tbu[0].ttb_pa;
    }

    if (ttb_va && jpu->dev)
    {
        rt_dma_free_coherent(jpu->dev, MAX_SIZE_PER_TTB * TBU_INSTANCES_NUM,
                ttb_va, ttb_pa);
    }

    if (jpu->regs)
    {
        rt_iounmap(jpu->regs);
    }

    spacemit_jpu_clk_disable(jpu);

    if (!rt_is_err_or_null(jpu->cclk))
    {
        rt_clk_put(jpu->cclk);
    }
    if (!rt_is_err_or_null(jpu->aclk))
    {
        rt_clk_put(jpu->aclk);
    }
    if (!rt_is_err_or_null(jpu->iclk))
    {
        rt_clk_put(jpu->iclk);
    }

    if (!rt_is_err_or_null(jpu->jpg_reset))
    {
        rt_reset_control_put(jpu->jpg_reset);
    }
    if (!rt_is_err_or_null(jpu->lcd_mclk_reset))
    {
        rt_reset_control_put(jpu->lcd_mclk_reset);
    }
    if (!rt_is_err_or_null(jpu->isp_ci_reset))
    {
        rt_reset_control_put(jpu->isp_ci_reset);
    }
    if (!rt_is_err_or_null(jpu->freset))
    {
        rt_reset_control_put(jpu->freset);
    }
    if (!rt_is_err_or_null(jpu->sreset))
    {
        rt_reset_control_put(jpu->sreset);
    }

    rt_free(jpu);
}

static rt_err_t spacemit_jpu_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t chip_id = 0;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_jpu *jpu = rt_calloc(1, sizeof(*jpu));
    void *ttb_va = RT_NULL;
    rt_ubase_t ttb_pa = 0;
    int i;

    if (!jpu)
    {
        return -RT_ENOMEM;
    }

    jpu->dev = dev;

    jpu->regs = rt_dm_dev_iomap(dev, 0);
    if (!jpu->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (!rt_dm_dev_prop_read_u32(dev, "page-size", &jpu->page_size))
    {
        jpu->page_size *= 1024;
    }
    else
    {
        jpu->page_size = 4096;
    }

    jpu->cclk = rt_clk_get_by_name(dev, "cclk");
    if (rt_is_err(jpu->cclk))
    {
        err = rt_ptr_err(jpu->cclk);
        goto _fail;
    }

    jpu->aclk = rt_clk_get_by_name(dev, "aclk");
    if (rt_is_err(jpu->aclk))
    {
        err = rt_ptr_err(jpu->aclk);
        goto _fail;
    }

    jpu->iclk = rt_clk_get_by_name(dev, "iclk");
    if (rt_is_err(jpu->iclk))
    {
        err = rt_ptr_err(jpu->iclk);
        goto _fail;
    }

    if ((err = spacemit_jpu_clk_enable(jpu)) != RT_EOK)
    {
        goto _fail;
    }

    jpu->jpg_reset = spacemit_jpu_get_reset(dev, "jpg_reset");
    jpu->lcd_mclk_reset = spacemit_jpu_get_reset(dev, "lcd_mclk_reset");
    jpu->isp_ci_reset = spacemit_jpu_get_reset(dev, "isp_ci_reset");
    jpu->freset = spacemit_jpu_get_reset(dev, "freset");
    jpu->sreset = spacemit_jpu_get_reset(dev, "sreset");
    spacemit_jpu_reset_deassert_all(jpu);

    jpu->irq = rt_dm_dev_get_irq(dev, 0);
    if (jpu->irq < 0)
    {
        err = jpu->irq;
        goto _fail;
    }

    ttb_va = rt_dma_alloc_coherent(dev, MAX_SIZE_PER_TTB * TBU_INSTANCES_NUM, &ttb_pa);
    if (!ttb_va)
    {
        LOG_E("No memory for TBU page tables");
        err = -RT_ENOMEM;
        goto _fail;
    }
    rt_memset(ttb_va, 0, MAX_SIZE_PER_TTB * TBU_INSTANCES_NUM);

    for (i = 0; i < TBU_INSTANCES_NUM; i++)
    {
        jpu->tbu[i].ttb_va = (rt_uint32_t *)((rt_uint8_t *)ttb_va + i * MAX_SIZE_PER_TTB);
        jpu->tbu[i].ttb_pa = ttb_pa + i * MAX_SIZE_PER_TTB;
    }

    jpu->va_base = JPU_TBU_BASE_VA;
    jpu->time_out_cycs = DEFAULT_TIMEOUT_CYCS;
    rt_spin_lock_init(&jpu->hw_lock);

    if (!rt_dm_dev_prop_read_u32(dev, "jpu,chip-id", &chip_id))
    {
        rt_dm_dev_set_name(&jpu->parent, "jpu%u", chip_id);
    }
    else
    {
        rt_dm_dev_set_name_auto(&jpu->parent, "jpu");
    }
    dev_name = rt_dm_dev_get_name(&jpu->parent);

    dev->user_data = jpu;

    jpu->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    jpu->parent.ops = &spacemit_jpu_ops;
#else
    jpu->parent.control = spacemit_jpu_control;
#endif

    if ((err = rt_device_register(&jpu->parent, dev_name, RT_DEVICE_FLAG_DEACTIVATE)))
    {
        goto _fail;
    }

    rt_mutex_init(&jpu->lock, dev_name, RT_IPC_FLAG_PRIO);
    rt_completion_init(&jpu->completion);

    rt_hw_interrupt_install(jpu->irq, spacemit_jpu_isr, jpu, "jpu");
    rt_hw_interrupt_umask(jpu->irq);

    LOG_I("Chip Media JPU probed, MMU version 0x%08x",
            spacemit_jpu_read(jpu, MJPEG_MMU_VERSION));

    return RT_EOK;

_fail:
    spacemit_jpu_free(jpu);

    return err;
}

static rt_err_t spacemit_jpu_remove(struct rt_platform_device *pdev)
{
    struct spacemit_jpu *jpu = pdev->parent.user_data;

    rt_hw_interrupt_mask(jpu->irq);
    rt_pic_detach_irq(jpu->irq, jpu);

    rt_device_unregister(&jpu->parent);

    spacemit_jpu_free(jpu);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_jpu_ofw_ids[] =
{
    { .compatible = "chip-media, jpu" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_jpu_driver =
{
    .name = "spacemit-jpu",
    .ids = spacemit_jpu_ofw_ids,

    .probe = spacemit_jpu_probe,
    .remove = spacemit_jpu_remove,
};
RT_PLATFORM_DRIVER_EXPORT(spacemit_jpu_driver);
