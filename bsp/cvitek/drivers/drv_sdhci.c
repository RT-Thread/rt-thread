/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/04/05     flyingcys    first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <mmu.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "board.h"
#include "cache.h"

#define DBG_TAG     "drv.sdio"
#define DBG_LEVEL   DBG_INFO
#include <rtdbg.h>

#include <drivers/dev_mmcsd_core.h>
#include <drivers/dev_sdio.h>

#include "drv_sdhci.h"

#define SDMMC_DMA_ALIGN_CACHE 64

struct rthw_sdhci
{
    struct rt_mmcsd_host *host;
    rt_ubase_t base;
    rt_uint32_t irq;
    volatile rt_err_t cmd_error;
    volatile rt_err_t data_error;
    rt_uint32_t response_type;
    volatile rt_uint32_t response[4];
    char name[RT_NAME_MAX];
    rt_sem_t sem_cmd;
    rt_sem_t sem_data;
};

static uint32_t sdhci_set_card_clock(rt_ubase_t base, uint32_t srcClock_Hz, uint32_t target_HZ)
{
    uintptr_t BASE = (uintptr_t)base;
    uint32_t divider = 1U;
    uint32_t i;

    RT_ASSERT(target_HZ > 0);

    if (srcClock_Hz <= target_HZ )
    {
        divider = 0;
    }
    else
    {
        for (divider = 0x1; divider < 0x3FF; divider++)
        {
            if(srcClock_Hz / (2*divider) <= target_HZ)
                break;
        }

        if(divider == 0x3FF)
        {
            LOG_D("Warning: Can't set the freq to %d, divider is filled!!!", target_HZ);
        }
    }

    RT_ASSERT(divider <= 0x3FF);

    if (mmio_read_16(BASE + SDIF_HOST_CONTROL2) & 1<<15)
    {
        LOG_D("Use SDCLK Preset Value.");
    }
    else
    {
        mmio_write_16(BASE + SDIF_CLK_CTRL,
                mmio_read_16(BASE + SDIF_CLK_CTRL) & ~0x9); // disable INTERNAL_CLK_EN and PLL_ENABLE
        mmio_write_16(BASE + SDIF_CLK_CTRL,
                (mmio_read_16(BASE + SDIF_CLK_CTRL) & 0x3F) | ((divider & 0xff) << 8) | ((divider & 0x300) >> 2)); // set clk div

        mmio_write_16(BASE + SDIF_CLK_CTRL,
                mmio_read_16(BASE + SDIF_CLK_CTRL) | 0x1); // set INTERNAL_CLK_EN

        for (i = 0; i <= 150000; i += 100)
        {
            if (mmio_read_16(BASE + SDIF_CLK_CTRL) & 0x2)
            {
                break;
            }

            rt_hw_us_delay(100);
        }

        if (i > 150000)
        {
            LOG_D("SD INTERNAL_CLK_EN seting FAILED!");
            RT_ASSERT(0);
        }

        mmio_write_16(BASE + SDIF_CLK_CTRL,
                mmio_read_16(BASE + SDIF_CLK_CTRL) | 0x8); // set PLL_ENABLE

        for (i = 0; i <= 150000; i += 100)
        {
            if (mmio_read_16(BASE + SDIF_CLK_CTRL) & 0x2)
            {
                return target_HZ;
            }

            rt_hw_us_delay(100);
        }
    }

    LOG_E("SD PLL seting FAILED!\n");
    return -1;
}

static uint32_t SDIF_ChangeCardClock(rt_ubase_t base, uint32_t srcClock_Hz, uint32_t target_HZ)
{
    uintptr_t BASE = (uintptr_t)base;
    uint32_t divider = 1U;
    uint32_t i;

    if (target_HZ <= 0)
    {
        mmio_write_16(BASE + SDIF_CLK_CTRL, mmio_read_32(BASE + SDIF_CLK_CTRL) & ~(0x1<<2)); // stop SD clock
//      mmio_write_16(BASE + 0x31e, 0x00);
        return -1;
    }

    if (srcClock_Hz <= target_HZ )
    {
        divider = 0;
    }
    else
    {
        for (divider = 0x1; divider < 0x3FF; divider++)
        {
            if(srcClock_Hz / (2*divider) <= target_HZ)
                break;
        }

        if(divider == 0x3FF)
        {
            LOG_D("Warning: Can't set the freq to %d, divider is filled!!!", target_HZ);
        }
    }

    RT_ASSERT(divider <= 0x3FF);

    mmio_write_16(BASE + SDIF_CLK_CTRL, mmio_read_16(BASE + SDIF_CLK_CTRL) & ~(0x1<<2)); // stop SD clock

//  mmio_write_16(BASE + 0x31e, 0x10);
    mmio_write_16(BASE + SDIF_CLK_CTRL, mmio_read_16(BASE + SDIF_CLK_CTRL) & ~0x8); // disable  PLL_ENABLE

    if (mmio_read_16(BASE + SDIF_HOST_CONTROL2) & 1<<15)
    {
        LOG_D("Use SDCLK Preset Value.");
        // 4 need recheck?
        mmio_write_16(BASE + SDIF_HOST_CONTROL2, mmio_read_16(BASE + SDIF_HOST_CONTROL2) & ~0x7); // clr UHS_MODE_SEL
    }
    else
    {
        mmio_write_16(BASE + SDIF_CLK_CTRL, (mmio_read_16(BASE + SDIF_CLK_CTRL) & 0x3F) | ((divider & 0xff) << 8) | ((divider & 0x300) >> 2)); // set clk div
        mmio_write_16(BASE + SDIF_CLK_CTRL, mmio_read_16(BASE + SDIF_CLK_CTRL) & ~(0x1 << 5)); // CLK_GEN_SELECT
    }

    mmio_write_16(BASE + SDIF_CLK_CTRL, mmio_read_16(BASE + SDIF_CLK_CTRL) | 0xc); // enable  PLL_ENABLE

    //LOG_D("mmio_read_16(BASE + SDIF_CLK_CTRL) = 0x%x", mmio_read_16(BASE + SDIF_CLK_CTRL));

    for (i = 0; i <= 150000; i += 100)
    {
        if (mmio_read_16(BASE + SDIF_CLK_CTRL) & 0x2)
        {
            return target_HZ;
        }

        rt_hw_us_delay(100);
    }

    LOG_E("SD PLL seting FAILED!\n");

    return -1;
}

static void sdhci_wait_cmd_complete(struct rthw_sdhci *sdhci)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t intmask;
    uintptr_t BASE = (uintptr_t)sdhci->base;

    ret = rt_sem_take(sdhci->sem_cmd, rt_tick_from_millisecond(3000));
    if (ret != RT_EOK)
    {
        LOG_E("wait cmd complete timeout ...");
        sdhci->cmd_error = -RT_ETIMEOUT;
        return;
    }
}

static void sdhci_wait_data_complete(struct rthw_sdhci *sdhci)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t intmask;
    uintptr_t BASE = (uintptr_t)sdhci->base;

    ret = rt_sem_take(sdhci->sem_data, rt_tick_from_millisecond(3000));
    if (ret != RT_EOK)
    {
        LOG_E("wait data complete timeout ...");
        sdhci->data_error = -RT_ETIMEOUT;
        return;
    }
}

static uint32_t sdhci_prepare_data(struct rthw_sdhci *sdhci, struct rt_mmcsd_cmd *cmd, struct rt_mmcsd_data *data, rt_ubase_t start_addr, rt_uint32_t load_len)
{
    uintptr_t BASE = (uintptr_t)sdhci->base;

    uint32_t block_cnt, blksz;
    uint8_t tmp;
    rt_ubase_t dma_addr;

    blksz = data->blksize;
    block_cnt = data->blks;

    rt_hw_cpu_dcache_clean((void *)start_addr, load_len);
#ifdef RT_USING_SMART
        dma_addr = (rt_ubase_t)rt_kmem_v2p((void *)start_addr);
#else
        dma_addr = start_addr;
#endif

    mmio_write_32(BASE + SDIF_ADMA_SA_LOW, dma_addr);
    mmio_write_32(BASE + SDIF_ADMA_SA_HIGH, (dma_addr >> 32));

    mmio_write_32(BASE + SDIF_DMA_ADDRESS, block_cnt);
    mmio_write_16(BASE + SDIF_BLOCK_COUNT, 0);

    mmio_write_16(BASE + SDIF_BLOCK_SIZE, SDIF_MAKE_BLKSZ(7, blksz));

    // select SDMA
    tmp = mmio_read_8(BASE + SDIF_HOST_CONTROL);
    tmp &= ~SDIF_CTRL_DMA_MASK;
    tmp |= SDIF_CTRL_SDMA;

    mmio_write_8(BASE + SDIF_HOST_CONTROL, tmp);

    return 0;
}

static inline void *align_alloc(uint64_t align, uint32_t size, void **mem_unalign)
{
    void *mem;
    uint64_t offset;
    size+=2*align;

    *mem_unalign = (void *)rt_malloc(size);

    if (!*mem_unalign)
    {
        LOG_E("sdio memalign error!\n");
        return NULL;
    }

    offset = (uint64_t)*mem_unalign % align;

    if (offset == 0)
        mem = (void *)*mem_unalign;
    else
        mem = (void *)(*mem_unalign + (align - offset));

    return mem;
}

static rt_err_t sdhci_send_data_cmd(struct rthw_sdhci *sdhci, struct rt_mmcsd_cmd *cmd, struct rt_mmcsd_data *data)
{
    uintptr_t BASE = (uintptr_t)sdhci->base;
    uint32_t mode = 0;
    uint32_t flags = 0;
    int end_time = 0;
    int start_time = rt_tick_get_millisecond();
    sdhci_dma_config_t dma_config;

    while(1)
    {
        if (!(mmio_read_32(BASE + SDIF_PRESENT_STATE) & SDIF_CMD_INHIBIT))
            break;
        end_time = rt_tick_get_millisecond();
        if (end_time - start_time >= 2000)
            return -RT_ETIMEOUT;
    }

    rt_ubase_t start_addr;
    void *src_unalign = NULL;

    if (data)
    {
        dma_config.dma_des_buffer_len = data->blksize * data->blks;
        if (data->flags & DATA_DIR_READ)
        {
            if ((uint64_t)data->buf & (SDMMC_DMA_ALIGN_CACHE - 1))
            {
                start_addr = (rt_ubase_t)align_alloc(SDMMC_DMA_ALIGN_CACHE, dma_config.dma_des_buffer_len, (void **)&src_unalign);
            }
            else
            {
                start_addr = (rt_ubase_t)data->buf;
            }
        }
        else
        {
            start_addr = (rt_ubase_t)data->buf;
        }

        sdhci_prepare_data(sdhci, cmd, data, start_addr, dma_config.dma_des_buffer_len);

        mode = SDIF_TRNS_DMA;
        if (mmc_op_multi(cmd->cmd_code) || data->blks > 1)
            mode |= SDIF_TRNS_MULTI | SDIF_TRNS_BLK_CNT_EN;

        if (data->flags & DATA_DIR_READ)
            mode |= SDIF_TRNS_READ;
        else
            mode &= ~SDIF_TRNS_READ;

        mmio_write_16(BASE + SDIF_TRANSFER_MODE, mode);
    }

    // set cmd flags
    if (resp_type(cmd) == RESP_NONE)
            flags |= SDIF_CMD_RESP_NONE;
    else if (resp_type(cmd) == RESP_R2)
        flags |= SDIF_CMD_RESP_LONG;
    else if (resp_type(cmd) == RESP_R1B)
        flags |= SDIF_CMD_RESP_SHORT_BUSY;
   else
        flags |= SDIF_CMD_RESP_SHORT;

    if (data)
    {
        flags |= SDIF_CMD_CRC;
        flags |= SDIF_CMD_INDEX;
        flags |= SDIF_CMD_DATA;
    }

    mmio_write_32(BASE + SDIF_ARGUMENT, cmd->arg);
    // issue the cmd
    mmio_write_16(BASE + SDIF_COMMAND, SDIF_MAKE_CMD(cmd->cmd_code, flags));

    sdhci_wait_cmd_complete(sdhci);
    if (sdhci->cmd_error != RT_EOK)
    {
        LOG_E("cmd error: %d\n", sdhci->cmd_error);
        return sdhci->cmd_error;
    }

    memcpy((void *)cmd->resp, (void *)sdhci->response, sizeof(sdhci->response));

    if (data)
    {
        sdhci_wait_data_complete(sdhci);
        if (sdhci->data_error != RT_EOK)
        {
            LOG_E("sdio data error!\n");
            return sdhci->data_error;
        }

        if (data->flags & DATA_DIR_READ)
        {
            rt_hw_cpu_dcache_invalidate((void *)start_addr, dma_config.dma_des_buffer_len);
            if (src_unalign)
            {
                memcpy((void *)data->buf, (void *)start_addr, dma_config.dma_des_buffer_len);
                rt_free(src_unalign);
                src_unalign = NULL;
            }
        }
    }

    return RT_EOK;
}

static void sdhci_cmd_irq(struct rthw_sdhci *sdhci, uint32_t intmask)
{
    int i;
    uintptr_t BASE = (uintptr_t)sdhci->base;

    if (intmask & (SDIF_INT_TIMEOUT | SDIF_INT_CRC |
               SDIF_INT_END_BIT | SDIF_INT_INDEX))
    {
        if (intmask & SDIF_INT_TIMEOUT)
        {
            sdhci->cmd_error = -RT_ETIMEOUT;
            LOG_E("SDIF_INT_TIMEOUT");
        }

        return;
    }

    if (intmask & SDIF_INT_RESPONSE)
    {
        if (sdhci->response_type == RESP_R2)
        {
            /* CRC is stripped so we need to do some shifting. */
            for (i = 0; i < 4; i++) {
                sdhci->response[i] = mmio_read_32(BASE + SDIF_RESPONSE_01 + (3-i)*4) << 8;
                if (i != 3)
                    sdhci->response[i] |= mmio_read_8(BASE + SDIF_RESPONSE_01 + (3-i)*4-1);
            }
            LOG_D("sdhci->response: [%08x %08x %08x %08x]", sdhci->response[0], sdhci->response[1], sdhci->response[2], sdhci->response[3]);
        }
        else
        {
            sdhci->response[0] = mmio_read_32(BASE + SDIF_RESPONSE_01);
            LOG_D("sdhci->response: [%08x]", sdhci->response[0]);
        }

        rt_sem_release(sdhci->sem_cmd);
    }
}

static void sdhci_data_irq(struct rthw_sdhci *sdhci, uint32_t intmask)
{
    uintptr_t BASE = (uintptr_t)sdhci->base;
    uint32_t command;

    /* CMD19 generates _only_ Buffer Read Ready interrupt */
    if (intmask & SDIF_INT_DATA_AVAIL)
    {
        command = SDIF_GET_CMD(mmio_read_16(BASE + SDIF_COMMAND));
        if (command == MMC_CMD19 ||
            command == MMC_CMD21) {
            //host->tuning_done = 1;
            return;
        }
    }

    if ((intmask & SDIF_INT_DATA_TIMEOUT) || (intmask & SDIF_INT_DATA_END_BIT) || (intmask & SDIF_INT_DATA_CRC) || (intmask & SDIF_INT_ADMA_ERROR))
    {
        sdhci->data_error = -RT_ERROR;
        return;
    }

    if (intmask & SDIF_INT_DATA_END)
    {
        sdhci->data_error = RT_EOK;
        return;
    }

    if (intmask & SDIF_INT_DMA_END)
    {
        uint64_t dma_addr;
        dma_addr = mmio_read_32(BASE + SDIF_ADMA_SA_LOW);
        mmio_write_32(BASE + SDIF_ADMA_SA_LOW, dma_addr);
        mmio_write_32(BASE + SDIF_ADMA_SA_HIGH, 0);
    }

    return;
}

static void sdhci_transfer_handle_irq(int irqno, void *param)
{
    struct rthw_sdhci *sdhci = (struct rthw_sdhci *)param;
    uintptr_t BASE = (uintptr_t)sdhci->base;
    int max_loop = 16;
    uint32_t intmask;
    uint32_t mask;
    uint32_t unexpected;

    intmask = mmio_read_32(BASE + SDIF_INT_STATUS);

    if (!intmask || intmask == 0xffffffff)
    {
        LOG_E("never be here!\n");
        return;
    }

    do
    {
        mask = intmask & (SDIF_INT_CMD_MASK | SDIF_INT_DATA_MASK | SDIF_INT_BUS_POWER);
        mmio_write_32(BASE + SDIF_INT_STATUS, mask);

        if (intmask & SDIF_INT_CMD_MASK)
        {
            sdhci_cmd_irq(sdhci, intmask & SDIF_INT_CMD_MASK);
        }

        if (intmask & SDIF_INT_DMA_END)
        {
            uint64_t dma_addr;
            dma_addr = mmio_read_32(BASE + SDIF_ADMA_SA_LOW);
            mmio_write_32(BASE + SDIF_ADMA_SA_LOW, dma_addr);
            mmio_write_32(BASE + SDIF_ADMA_SA_HIGH, 0);
            return;
        }

        if (intmask & SDIF_INT_DATA_MASK)
        {
            sdhci_data_irq(sdhci, intmask & SDIF_INT_DATA_MASK);
            rt_sem_release(sdhci->sem_data);
        }

        if (intmask & SDIF_INT_CARD_INT)
        {
            LOG_D("init_card_init");
        }

        intmask &= ~(SDIF_INT_CARD_INSERT | SDIF_INT_CARD_REMOVE |
                SDIF_INT_CMD_MASK | SDIF_INT_DATA_MASK |
                SDIF_INT_ERROR | SDIF_INT_BUS_POWER |
                SDIF_INT_RETUNE | SDIF_INT_CARD_INT);

        if (intmask)
        {
            unexpected = intmask;
            mmio_write_32(BASE + SDIF_INT_STATUS, intmask);
            LOG_D("unexpected interrupt: 0x%08x.", unexpected);
        }

        intmask = mmio_read_32(BASE + SDIF_INT_STATUS);
    } while (intmask && --max_loop);
}

static uint32_t sdhci_set_clock(rt_ubase_t base, uint32_t target_hz)
{
    uint32_t source_clock_hz;
    uint32_t ret;

    source_clock_hz = 375 * 1000 * 1000;
    if (target_hz <= 400000)
        ret = sdhci_set_card_clock(base, source_clock_hz, target_hz);
    else
        ret = SDIF_ChangeCardClock(base, source_clock_hz, target_hz);

    return ret;
}

static void sdhci_set_bus_width(rt_ubase_t base, uint8_t bus_width)
{
    uintptr_t BASE = (uintptr_t)base;
    uint32_t ctrl;
    uint16_t ctrl_2;

    ctrl = mmio_read_8(BASE + SDIF_HOST_CONTROL);
    if (bus_width == MMCSD_BUS_WIDTH_1)
        ctrl &= ~SDIF_DAT_XFER_WIDTH;
    else if (bus_width == MMCSD_BUS_WIDTH_4)
        ctrl |= SDIF_DAT_XFER_WIDTH;
    ctrl |= SDIF_CTRL_HISPD;

    ctrl_2 = mmio_read_16(BASE + SDIF_HOST_CONTROL2);
    ctrl_2 &= ~SDIF_CTRL_UHS_MASK;
    ctrl_2 |= SDIF_CTRL_UHS_SDR25;
    mmio_write_16(BASE + SDIF_HOST_CONTROL2, ctrl_2);

    rt_thread_mdelay(1);

    mmio_write_8(BASE + SDIF_HOST_CONTROL, ctrl);
}

static void sdhci_enable_card_power(rt_ubase_t base, bool enable)
{
    uintptr_t BASE = (uintptr_t)base;

    if (enable)
    {
        mmio_write_8(BASE + SDIF_PWR_CONTROL,mmio_read_8(BASE + SDIF_PWR_CONTROL) | 0x1);
    }
    else
    {
        mmio_write_8(BASE + SDIF_PWR_CONTROL,mmio_read_8(BASE+ SDIF_PWR_CONTROL) & ~0x1);
    }
}

static uint32_t sdhci_detect_card_insert(rt_ubase_t base, bool data3)
{
    uintptr_t BASE = (uintptr_t)base;
    if (data3)
    {
        return (mmio_read_32(BASE+SDIF_PRESENT_STATE) & SDIF_CARD_STABLE) == SDIF_CARD_STABLE ? 0U : 1U;
    }
    else
    {
        return (mmio_read_32(BASE+SDIF_PRESENT_STATE) & SDIF_CARD_INSERTED) == SDIF_CARD_INSERTED ? 1U : 0U;
    }
}

static void sdhci_enable_card_clock(rt_ubase_t base, bool enable)
{
    uintptr_t BASE = (uintptr_t)base;
    if (enable)
    {
         mmio_write_16(BASE + SDIF_CLK_CTRL, mmio_read_32(BASE + SDIF_CLK_CTRL) | (0x1<<2)); // stop SD clock
    }
    else
    {
        mmio_write_16(BASE + SDIF_CLK_CTRL, mmio_read_32(BASE + SDIF_CLK_CTRL) & ~(0x1<<2)); // stop SD clock
    }
}

static void sdhci_hw_reset(rt_ubase_t base)
{
    uintptr_t BASE = (uintptr_t)base;

    mmio_write_16(BASE + SDIF_CLK_CTRL, (mmio_read_16(BASE + SDIF_CLK_CTRL) & 0x3F) | DEFAULT_DIV_SD_INIT_CLOCK << 8);

    rt_thread_mdelay(1);

    mmio_write_8(BASE + SDIF_SOFTWARE_RESET, 0x7);
    while (mmio_read_8(BASE + SDIF_SOFTWARE_RESET));
}

#define REG_TOP_SD_PWRSW_CTRL       (0x1F4)

static void sdhci_pad_setting(rt_ubase_t base)
{
    uintptr_t BASE = (uintptr_t)base;

    if (BASE == (rt_ubase_t)SDIO0_BASE)
    {
        //set power for sd0
        mmio_write_32(TOP_BASE + REG_TOP_SD_PWRSW_CTRL, 0x9);
        rt_thread_mdelay(1);

        //set pu/down
        mmio_write_32(REG_SDIO0_CD_PAD_REG, (mmio_read_32(REG_SDIO0_CD_PAD_REG) & REG_SDIO0_PAD_MASK) | REG_SDIO0_CD_PAD_VALUE << REG_SDIO0_PAD_SHIFT);
        mmio_write_32(REG_SDIO0_PWR_EN_PAD_REG, (mmio_read_32(REG_SDIO0_PWR_EN_PAD_REG) & REG_SDIO0_PAD_MASK) | REG_SDIO0_PWR_EN_PAD_VALUE << REG_SDIO0_PAD_SHIFT);
        mmio_write_32(REG_SDIO0_CLK_PAD_REG, (mmio_read_32(REG_SDIO0_CLK_PAD_REG) & REG_SDIO0_PAD_MASK) | REG_SDIO0_CLK_PAD_VALUE << REG_SDIO0_PAD_SHIFT);
        mmio_write_32(REG_SDIO0_CMD_PAD_REG, (mmio_read_32(REG_SDIO0_CMD_PAD_REG) & REG_SDIO0_PAD_MASK) | REG_SDIO0_CMD_PAD_VALUE << REG_SDIO0_PAD_SHIFT);
        mmio_write_32(REG_SDIO0_DAT1_PAD_REG, (mmio_read_32(REG_SDIO0_DAT1_PAD_REG) & REG_SDIO0_PAD_MASK) | REG_SDIO0_DAT1_PAD_VALUE << REG_SDIO0_PAD_SHIFT);
        mmio_write_32(REG_SDIO0_DAT0_PAD_REG, (mmio_read_32(REG_SDIO0_DAT0_PAD_REG) & REG_SDIO0_PAD_MASK) | REG_SDIO0_DAT0_PAD_VALUE << REG_SDIO0_PAD_SHIFT);
        mmio_write_32(REG_SDIO0_DAT2_PAD_REG, (mmio_read_32(REG_SDIO0_DAT2_PAD_REG) & REG_SDIO0_PAD_MASK) | REG_SDIO0_DAT2_PAD_VALUE << REG_SDIO0_PAD_SHIFT);
        mmio_write_32(REG_SDIO0_DAT3_PAD_REG, (mmio_read_32(REG_SDIO0_DAT3_PAD_REG) & REG_SDIO0_PAD_MASK) | REG_SDIO0_DAT3_PAD_VALUE << REG_SDIO0_PAD_SHIFT);

        //set pinmux
        mmio_write_8(REG_SDIO0_CD_PIO_REG, REG_SDIO0_CD_PIO_VALUE);
        mmio_write_8(REG_SDIO0_PWR_EN_PIO_REG, REG_SDIO0_PWR_EN_PIO_VALUE);
        mmio_write_8(REG_SDIO0_CLK_PIO_REG, REG_SDIO0_CLK_PIO_VALUE);
        mmio_write_8(REG_SDIO0_CMD_PIO_REG, REG_SDIO0_CMD_PIO_VALUE);
        mmio_write_8(REG_SDIO0_DAT0_PIO_REG, REG_SDIO0_DAT0_PIO_VALUE);
        mmio_write_8(REG_SDIO0_DAT1_PIO_REG, REG_SDIO0_DAT1_PIO_VALUE);
        mmio_write_8(REG_SDIO0_DAT2_PIO_REG, REG_SDIO0_DAT2_PIO_VALUE);
        mmio_write_8(REG_SDIO0_DAT3_PIO_REG, REG_SDIO0_DAT3_PIO_VALUE);
    }
    else if(BASE == (rt_ubase_t)SDIO1_BASE)
    {
        // set rtc sdio1 related register
        mmio_write_32(RTCSYS_CTRL, 0x1);
        mmio_write_32(RTCSYS_CLKMUX, 0x10);
        mmio_write_32(RTCSYS_CLKBYP, 0xfffffffc);
        //mmio_write_32(RTCSYS_MCU51_ICTRL1, 0x0);

        mmio_write_32(REG_SDIO1_CLK_PAD_REG, (mmio_read_32(REG_SDIO1_CLK_PAD_REG) & REG_SDIO1_PAD_MASK) | REG_SDIO1_CLK_PAD_VALUE << REG_SDIO1_PAD_SHIFT);
        mmio_write_32(REG_SDIO1_CMD_PAD_REG, (mmio_read_32(REG_SDIO1_CMD_PAD_REG) & REG_SDIO1_PAD_MASK) | REG_SDIO1_CMD_PAD_VALUE << REG_SDIO1_PAD_SHIFT);
        mmio_write_32(REG_SDIO1_DAT1_PAD_REG, (mmio_read_32(REG_SDIO1_DAT1_PAD_REG) & REG_SDIO1_PAD_MASK) | REG_SDIO1_DAT1_PAD_VALUE << REG_SDIO1_PAD_SHIFT);
        mmio_write_32(REG_SDIO1_DAT0_PAD_REG, (mmio_read_32(REG_SDIO1_DAT0_PAD_REG) & REG_SDIO1_PAD_MASK) | REG_SDIO1_DAT0_PAD_VALUE << REG_SDIO1_PAD_SHIFT);
        mmio_write_32(REG_SDIO1_DAT2_PAD_REG, (mmio_read_32(REG_SDIO1_DAT2_PAD_REG) & REG_SDIO1_PAD_MASK) | REG_SDIO1_DAT2_PAD_VALUE << REG_SDIO1_PAD_SHIFT);
        mmio_write_32(REG_SDIO1_DAT3_PAD_REG, (mmio_read_32(REG_SDIO1_DAT3_PAD_REG) & REG_SDIO1_PAD_MASK) | REG_SDIO1_DAT3_PAD_VALUE << REG_SDIO1_PAD_SHIFT);
        mmio_write_32(RTCSYS_CTRL, 0x1);                                    // enable rtc2ap_ahb;

        //set pinmux
        mmio_write_32(TOP_BASE + 0x294, (mmio_read_32(TOP_BASE + 0x294) & 0xFFFFFBFF));
        mmio_write_8(REG_SDIO1_CLK_PIO_REG, REG_SDIO1_CLK_PIO_VALUE);
        mmio_write_8(REG_SDIO1_CMD_PIO_REG, REG_SDIO1_CMD_PIO_VALUE);
        mmio_write_8(REG_SDIO1_DAT0_PIO_REG, REG_SDIO1_DAT0_PIO_VALUE);
        mmio_write_8(REG_SDIO1_DAT1_PIO_REG, REG_SDIO1_DAT1_PIO_VALUE);
        mmio_write_8(REG_SDIO1_DAT2_PIO_REG, REG_SDIO1_DAT2_PIO_VALUE);
        mmio_write_8(REG_SDIO1_DAT3_PIO_REG, REG_SDIO1_DAT3_PIO_VALUE);
    }
    else if(BASE == (rt_ubase_t)SDIO2_BASE)
    {
        //set pu/down
        mmio_write_32(REG_SDIO2_RSTN_PAD_REG, (mmio_read_32(REG_SDIO2_RSTN_PAD_REG) & REG_SDIO2_PAD_MASK) | REG_SDIO2_RSTN_PAD_VALUE << REG_SDIO2_PAD_SHIFT);
        mmio_write_32(REG_SDIO2_CLK_PAD_REG, (mmio_read_32(REG_SDIO2_CLK_PAD_REG) & REG_SDIO2_PAD_MASK) | REG_SDIO2_CLK_PAD_VALUE << REG_SDIO2_PAD_SHIFT);
        mmio_write_32(REG_SDIO2_CMD_PAD_REG, (mmio_read_32(REG_SDIO2_CMD_PAD_REG) & REG_SDIO2_PAD_MASK) | REG_SDIO2_CMD_PAD_VALUE << REG_SDIO2_PAD_SHIFT);
        mmio_write_32(REG_SDIO2_DAT0_PAD_REG, (mmio_read_32(REG_SDIO2_DAT0_PAD_REG) & REG_SDIO2_PAD_MASK) | REG_SDIO2_DAT0_PAD_VALUE << REG_SDIO2_PAD_SHIFT);
        mmio_write_32(REG_SDIO2_DAT1_PAD_REG, (mmio_read_32(REG_SDIO2_DAT1_PAD_REG) & REG_SDIO2_PAD_MASK) | REG_SDIO2_DAT1_PAD_VALUE << REG_SDIO2_PAD_SHIFT);
        mmio_write_32(REG_SDIO2_DAT2_PAD_REG, (mmio_read_32(REG_SDIO2_DAT2_PAD_REG) & REG_SDIO2_PAD_MASK) | REG_SDIO2_DAT2_PAD_VALUE << REG_SDIO2_PAD_SHIFT);
        mmio_write_32(REG_SDIO2_DAT3_PAD_REG, (mmio_read_32(REG_SDIO2_DAT3_PAD_REG) & REG_SDIO2_PAD_MASK) | REG_SDIO2_DAT3_PAD_VALUE << REG_SDIO2_PAD_SHIFT);

        //set pinmux
        mmio_write_8(REG_SDIO2_RSTN_PIO_REG, REG_SDIO2_RSTN_PIO_VALUE);
        mmio_write_8(REG_SDIO2_CLK_PIO_REG, REG_SDIO2_CLK_PIO_VALUE);
        mmio_write_8(REG_SDIO2_CMD_PIO_REG, REG_SDIO2_CMD_PIO_VALUE);
        mmio_write_8(REG_SDIO2_DAT0_PIO_REG, REG_SDIO2_DAT0_PIO_VALUE);
        mmio_write_8(REG_SDIO2_DAT1_PIO_REG, REG_SDIO2_DAT1_PIO_VALUE);
        mmio_write_8(REG_SDIO2_DAT2_PIO_REG, REG_SDIO2_DAT2_PIO_VALUE);
        mmio_write_8(REG_SDIO2_DAT3_PIO_REG, REG_SDIO2_DAT3_PIO_VALUE);
    }
}

static void sdhci_phy_init(rt_ubase_t base)
{
    uintptr_t BASE = (uintptr_t)base;

    uintptr_t vendor_base = BASE + (mmio_read_16(BASE + P_VENDOR_SPECIFIC_AREA) & ((1<<12)-1));

    sdhci_hw_reset(base);

    rt_thread_mdelay(3);

    sdhci_pad_setting(base);

    if (BASE == (rt_ubase_t)SDIO2_BASE)
    {
        //reg_0x200[0] = 1 for sd2
        mmio_write_32(vendor_base, mmio_read_32(vendor_base) | BIT(0));
    }

    //reg_0x200[1] = 1
    mmio_write_32(vendor_base, mmio_read_32(vendor_base) | BIT(1));

    if (BASE == (rt_ubase_t)SDIO1_BASE)
    {
        //reg_0x200[16] = 1 for sd1
        mmio_write_32(vendor_base, mmio_read_32(vendor_base) | BIT(16));
    }

    mmio_write_32(vendor_base + SDIF_PHY_CONFIG, mmio_read_32(vendor_base + SDIF_PHY_CONFIG) | BIT(0));

    mmio_write_32(vendor_base + SDIF_PHY_TX_RX_DLY, 0x1000100);
}

static void sdhci_init(rt_ubase_t base)
{
    uintptr_t BASE = (uintptr_t)base;

    mmio_write_8(BASE + SDIF_SOFTWARE_RESET, 0x6);

    mmio_write_8(BASE + SDIF_PWR_CONTROL, (0x7 << 1));
    mmio_write_8(BASE + SDIF_TOUT_CTRL, 0xe);
    mmio_write_16(BASE + SDIF_HOST_CONTROL2, mmio_read_16(BASE + SDIF_HOST_CONTROL2) | 1<<11);
    mmio_write_16(BASE + SDIF_CLK_CTRL, mmio_read_16(BASE + SDIF_CLK_CTRL) & ~(0x1 << 5));
    mmio_write_16(BASE + SDIF_HOST_CONTROL2, mmio_read_16(BASE + SDIF_HOST_CONTROL2) | SDIF_HOST_VER4_ENABLE);

    mmio_write_16(BASE + SDIF_HOST_CONTROL2, mmio_read_16(BASE + SDIF_HOST_CONTROL2) | 0x1<<13);

    if (mmio_read_32(BASE + SDIF_CAPABILITIES1) & (0x1<<29))
    {
        mmio_write_16(BASE + SDIF_HOST_CONTROL2, mmio_read_16(BASE + SDIF_HOST_CONTROL2) | (0x1<<14)); // enable async int
    }

    rt_thread_mdelay(20);

    mmio_write_16(BASE + SDIF_HOST_CONTROL2, mmio_read_16(BASE + SDIF_HOST_CONTROL2) & ~(0x1<<8)); // clr UHS2_IF_ENABLE
    mmio_write_8(BASE + SDIF_PWR_CONTROL, mmio_read_8(BASE + SDIF_PWR_CONTROL) | 0x1); // set SD_BUS_PWR_VDD1
    mmio_write_16(BASE + SDIF_HOST_CONTROL2, mmio_read_16(BASE + SDIF_HOST_CONTROL2) & ~0x7); // clr UHS_MODE_SEL

    rt_thread_mdelay(50);

    mmio_write_16(BASE + SDIF_CLK_CTRL, mmio_read_16(BASE + SDIF_CLK_CTRL) | (0x1<<2)); // supply SD clock

    rt_hw_us_delay(400); // wait for voltage ramp up time at least 74 cycle, 400us is 80 cycles for 200Khz

    mmio_write_16(BASE + SDIF_INT_STATUS, mmio_read_16(BASE + SDIF_INT_STATUS) | (0x1 << 6));

    mmio_write_16(BASE + SDIF_INT_STATUS_EN, mmio_read_16(BASE + SDIF_INT_STATUS_EN) | 0xFFFF);
    mmio_write_16(BASE + SDIF_ERR_INT_STATUS_EN, mmio_read_16(BASE + SDIF_ERR_INT_STATUS_EN) | 0xFFFF);

}

void rthw_sdhci_set_config(struct rthw_sdhci *sdhci)
{
    uint32_t pio_irqs = SDIF_INT_DATA_AVAIL | SDIF_INT_SPACE_AVAIL;
    uint32_t dma_irqs = SDIF_INT_DMA_END | SDIF_INT_ADMA_ERROR;
    uint32_t int_status;
    uintptr_t BASE = (uintptr_t)sdhci->base;

    static bool sd0_clock_state = false;
    static bool sd1_clock_state = false;
    static bool sd2_clock_state = false;

    if (BASE == (rt_ubase_t)SDIO0_BASE)
    {
        LOG_D("MMC_FLAG_SDCARD.");
        if (sd0_clock_state == false)
        {
            mmio_write_32(MMC_SDIO0_PLL_REGISTER, MMC_MAX_CLOCK_DIV_VALUE);
            mmio_clrbits_32(CLOCK_BYPASS_SELECT_REGISTER, BIT(6));
            sd0_clock_state = true;
        }
    }
    else if (BASE == (rt_ubase_t)SDIO1_BASE)
    {
        LOG_D("MMC_FLAG_SDIO.");
        if (sd1_clock_state == false)
        {
            mmio_write_32(MMC_SDIO1_PLL_REGISTER, MMC_MAX_CLOCK_DIV_VALUE);
            mmio_clrbits_32(CLOCK_BYPASS_SELECT_REGISTER, BIT(7));
            sd1_clock_state = true;
        }
    }
    else if (BASE == (rt_ubase_t)SDIO2_BASE)
    {
        LOG_D("MMC_FLAG_EMMC.");
        if (sd2_clock_state == false)
        {
            mmio_write_32(MMC_SDIO2_PLL_REGISTER, MMC_MAX_CLOCK_DIV_VALUE);
            mmio_clrbits_32(CLOCK_BYPASS_SELECT_REGISTER, BIT(5));
            sd2_clock_state = true;
        }
    }

    sdhci_phy_init(sdhci->base);
    sdhci_init(sdhci->base);

    int_status = SDIF_INT_BUS_POWER | SDIF_INT_DATA_END_BIT |
        SDIF_INT_DATA_CRC | SDIF_INT_DATA_TIMEOUT |
        SDIF_INT_INDEX | SDIF_INT_END_BIT | SDIF_INT_CRC |
        SDIF_INT_TIMEOUT | SDIF_INT_DATA_END | SDIF_INT_RESPONSE;

    int_status = (int_status & ~pio_irqs) | dma_irqs;

    if (int_status)
    {
        rt_hw_interrupt_install(sdhci->irq, sdhci_transfer_handle_irq, sdhci, sdhci->name);
        rt_hw_interrupt_umask(sdhci->irq);

        mmio_write_32(BASE + SDIF_SIGNAL_ENABLE, int_status);
    }
    else
    {
        mmio_write_32(BASE + SDIF_SIGNAL_ENABLE, 0);
    }

}

static void rthw_sdhci_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    RT_ASSERT(host != RT_NULL);
    RT_ASSERT(req != RT_NULL);

    rt_err_t ret = RT_EOK;
    struct rthw_sdhci *sdhci = (struct rthw_sdhci *)host->private_data;

    if (req->cmd != RT_NULL)
    {
        struct rt_mmcsd_cmd *cmd = req->cmd;
        struct rt_mmcsd_data *data = req->data;

        LOG_D("[%s%s%s%s%s]REQ: CMD:%d ARG:0x%08x RES:%s%s%s%s%s%s%s%s%s rw:%c addr:%p, blks:%d, blksize:%d datalen:%d",
                (host->card == RT_NULL) ? "Unknown" : "",
                (host->card) && (host->card->card_type == CARD_TYPE_MMC) ? "MMC" : "",
                (host->card) && (host->card->card_type == CARD_TYPE_SD) ? "SD" : "",
                (host->card) && (host->card->card_type == CARD_TYPE_SDIO) ? "SDIO" : "",
                (host->card) && (host->card->card_type == CARD_TYPE_SDIO_COMBO) ? "SDIO_COMBO" : "",
                cmd->cmd_code,
                cmd->arg,
                resp_type(cmd) == RESP_NONE ? "NONE"  : "",
                resp_type(cmd) == RESP_R1  ? "R1"  : "",
                resp_type(cmd) == RESP_R1B ? "R1B"  : "",
                resp_type(cmd) == RESP_R2  ? "R2"  : "",
                resp_type(cmd) == RESP_R3  ? "R3"  : "",
                resp_type(cmd) == RESP_R4  ? "R4"  : "",
                resp_type(cmd) == RESP_R5  ? "R5"  : "",
                resp_type(cmd) == RESP_R6  ? "R6"  : "",
                resp_type(cmd) == RESP_R7  ? "R7"  : "",
                data ? (data->flags & DATA_DIR_WRITE ?  'w' : 'r') : '-',
                data ? data->buf : 0,
                data ? data->blks : 0,
                data ? data->blksize : 0,
                data ? data->blks * data->blksize : 0);

        if (cmd->cmd_code == SD_IO_SEND_OP_COND)
        {
            cmd->err = -RT_ERROR;

            mmcsd_req_complete(host);
            return;
        }

        sdhci->response_type = resp_type(cmd);
        sdhci->cmd_error = RT_EOK;
        sdhci->data_error = RT_EOK;
        memset((void *)sdhci->response, 0, sizeof(sdhci->response));
        memset(cmd->resp, 0, sizeof(cmd->resp));

        ret = sdhci_send_data_cmd(sdhci, cmd, data);
        if (ret != RT_EOK)
        {
            memset(cmd->resp, 0, sizeof(cmd->resp));
        }
        cmd->err = ret;
    }

    if (req->stop != RT_NULL)
    {
        struct rt_mmcsd_cmd *stop = req->stop;

        stop->err = sdhci_send_data_cmd(sdhci, stop, RT_NULL);
    }

    mmcsd_req_complete(host);
}

static void rthw_sdhci_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    RT_ASSERT(host != RT_NULL);
    RT_ASSERT(io_cfg != RT_NULL);

    struct rthw_sdhci *sdhci = (struct rthw_sdhci *)host->private_data;
    rt_uint32_t clk = io_cfg->clock;

    LOG_D("clk:%d width:%s%s%s power:%s%s%s",
          clk,
          io_cfg->bus_width == MMCSD_BUS_WIDTH_8 ? "8" : "",
          io_cfg->bus_width == MMCSD_BUS_WIDTH_4 ? "4" : "",
          io_cfg->bus_width == MMCSD_BUS_WIDTH_1 ? "1" : "",
          io_cfg->power_mode == MMCSD_POWER_OFF ? "OFF" : "",
          io_cfg->power_mode == MMCSD_POWER_UP ? "UP" : "",
          io_cfg->power_mode == MMCSD_POWER_ON ? "ON" : ""
         );

    if (clk > host->freq_max)
        clk = host->freq_max;

    if (clk < host->freq_min)
        clk = host->freq_min;

    sdhci_set_clock(sdhci->base, clk);

    /* power mode */
    switch (io_cfg->power_mode)
    {
        case MMCSD_POWER_UP:
        case MMCSD_POWER_ON:
            sdhci_enable_card_power(sdhci->base, true);
            break;

        case MMCSD_POWER_OFF:
            sdhci_enable_card_power(sdhci->base, false);
            break;

        default:
            break;
    }

    /* bus width */
    switch (io_cfg->bus_width)
    {
        case MMCSD_BUS_WIDTH_1:
        case MMCSD_BUS_WIDTH_4:
            sdhci_set_bus_width(sdhci->base, io_cfg->bus_width);
            break;

        case MMCSD_BUS_WIDTH_8:
        default:
            LOG_E("invalid bus_width: %d", io_cfg->bus_width);
            break;
    }
}


static const struct rt_mmcsd_host_ops ops = {
    rthw_sdhci_request,
    rthw_sdhci_iocfg,
    RT_NULL,
    RT_NULL,
};

static int rthw_sdhci_init(void)
{
    rt_err_t ret = RT_EOK;

    struct rt_mmcsd_host *host;
    struct rthw_sdhci *sdhci = RT_NULL;

    sdhci = rt_malloc(sizeof(struct rthw_sdhci));
    if (sdhci == RT_NULL)
    {
        LOG_E("malloc rthw_sdhci faile...");
    }
    rt_memset(sdhci, 0, sizeof(struct rthw_sdhci));

    sdhci->sem_cmd = rt_sem_create("sem_cmd", 0, RT_IPC_FLAG_FIFO);
    if (sdhci->sem_cmd == RT_NULL)
    {
        LOG_E("rt_sem_create sdhci event failed...");
        rt_free(sdhci);
        sdhci = RT_NULL;
        return ret;
    }

    sdhci->sem_data = rt_sem_create("sem_data", 0, RT_IPC_FLAG_FIFO);
    if (sdhci->sem_data == RT_NULL)
    {
        LOG_E("rt_sem_create sdhci event failed...");
        rt_sem_delete(sdhci->sem_cmd);
        rt_free(sdhci);
        sdhci = RT_NULL;
        return ret;
    }

    sdhci->base = (rt_ubase_t)SDIO0_BASE;
    sdhci->irq = SDIO0_IRQ;
    strcpy(sdhci->name, "sdio0");
    rthw_sdhci_set_config(sdhci);

    host = mmcsd_alloc_host();
    RT_ASSERT(host != RT_NULL);

    /* set host default attributes */
    host->ops = &ops;
    host->freq_min = 400000;
    host->freq_max = 50 * 1000 * 1000;
    host->valid_ocr = VDD_31_32 | VDD_32_33 | VDD_33_34;
    host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED;
    host->max_seg_size = 512;
    host->max_dma_segs = 1;
    host->max_blk_size= 512;
    host->max_blk_count = 512;

    sdhci->host = host;
    host->private_data = sdhci;

    /* ready to change */
    mmcsd_change(host);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rthw_sdhci_init);

void sdhci_reg_dump(uint8_t argc, char **argv)
{
    rt_ubase_t base;
    if (argc < 2)
    {
        rt_kprintf("Usage: sdhci_reg_dump 0/1/2\n");
        return;
    }

    if (0 == atoi(argv[1]))
        base = (rt_ubase_t)SDIO0_BASE;
    else if (1 == atoi(argv[1]))
        base = (rt_ubase_t)SDIO1_BASE;
    else
        base = (rt_ubase_t)SDIO2_BASE;

    uintptr_t BASE = (uintptr_t)base;

    rt_kprintf("============ SDHCI REGISTER DUMP ===========\n");

    rt_kprintf("Sys addr:  0x%08x | Version:  0x%08x\n",
           mmio_read_32(BASE + SDIF_DMA_ADDRESS),
           mmio_read_16(BASE + SDIF_HOST_VERSION));
    rt_kprintf("Blk size:  0x%08x | Blk cnt:  0x%08x\n",
           mmio_read_16(BASE + SDIF_BLOCK_SIZE),
           mmio_read_16(BASE + SDIF_BLOCK_COUNT));
    rt_kprintf("Argument:  0x%08x | Trn mode: 0x%08x\n",
           mmio_read_32(BASE + SDIF_ARGUMENT),
           mmio_read_16(BASE + SDIF_TRANSFER_MODE));
    rt_kprintf("Present:   0x%08x | Host ctl: 0x%08x\n",
           mmio_read_32(BASE + SDIF_PRESENT_STATE),
           mmio_read_8(BASE + SDIF_HOST_CONTROL));
    rt_kprintf("Power:     0x%08x | Blk gap:  0x%08x\n",
           mmio_read_8(BASE + SDIF_PWR_CONTROL),
           mmio_read_8(BASE + SDIF_BLOCK_GAP_CONTROL));
    rt_kprintf("Wake-up:   0x%08x | Clock:    0x%08x\n",
           mmio_read_8(BASE + SDIF_WAKE_UP_CONTROL),
           mmio_read_16(BASE + SDIF_CLK_CTRL));
    rt_kprintf("Timeout:   0x%08x | Int stat: 0x%08x\n",
           mmio_read_8(BASE + SDIF_TOUT_CTRL),
           mmio_read_32(BASE + SDIF_INT_STATUS));
    rt_kprintf("Int enab:  0x%08x | Sig enab: 0x%08x\n",
           mmio_read_32(BASE + SDIF_INT_ENABLE),
           mmio_read_32(BASE + SDIF_SIGNAL_ENABLE));
    rt_kprintf("ACmd stat: 0x%08x | Slot int: 0x%08x\n",
           mmio_read_16(BASE + SDIF_AUTO_CMD_STATUS),
           mmio_read_16(BASE + SDIF_SLOT_INT_STATUS));
    rt_kprintf("Caps:      0x%08x | Caps_1:   0x%08x\n",
           mmio_read_32(BASE + SDIF_CAPABILITIES),
           mmio_read_32(BASE + SDIF_CAPABILITIES_1));
    rt_kprintf("Cmd:       0x%08x | Max curr: 0x%08x\n",
           mmio_read_16(BASE + SDIF_COMMAND),
           mmio_read_32(BASE + SDIF_MAX_CURRENT));
    rt_kprintf("Resp[0]:   0x%08x | Resp[1]:  0x%08x\n",
           mmio_read_32(BASE + SDIF_RESPONSE),
           mmio_read_32(BASE + SDIF_RESPONSE + 4));
    rt_kprintf("Resp[2]:   0x%08x | Resp[3]:  0x%08x\n",
           mmio_read_32(BASE + SDIF_RESPONSE + 8),
           mmio_read_32(BASE + SDIF_RESPONSE + 12));
    rt_kprintf("Host ctl2: 0x%08x\n",
           mmio_read_16(BASE + SDIF_HOST_CONTROL2));
    rt_kprintf("ADMA Err:  0x%08x | ADMA Ptr: 0x%08x%08x\n",
           mmio_read_32(BASE + SDIF_ADMA_ERROR),
           mmio_read_32(BASE + SDIF_ADMA_ADDRESS_HI),
           mmio_read_32(BASE + SDIF_ADMA_ADDRESS));
    rt_kprintf("============================================\n");
}
MSH_CMD_EXPORT(sdhci_reg_dump, dump sdhci register);
