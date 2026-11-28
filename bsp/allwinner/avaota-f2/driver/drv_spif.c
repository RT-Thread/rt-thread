/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Minimal sun252iw1 SPIF v2 bring-up: clock/pins + DMA RDID/READ.
 * Register/descriptor layout follows SyterKit drivers/spif (SPIF_V2).
 */

#include <rthw.h>
#include <rtthread.h>
#include <string.h>

#include "amp_mbox.h"
#include "clint.h"
#include "drv_spif.h"

#define SPIF_BASE       0x04F00000U
#define SPIF_CLK_REG    0x02001950U
#define SPIF_BGR_REG    0x0200196cU
#define SPIF_GATE_BIT   4U
#define SPIF_RST_BIT    20U
#define SPIF_CLK_PARENT 400000000U
#define SPIF_CLK_SRC    1U /* PERI 400M */
#define SPIF_CLK_N_OFF  8U

#define SUNXI_GPIO_BASE        0x02000000U
#define SUNXI_GPIO_PORT_STRIDE 0x30U
#define PIO_PORT_C             2U

#define SPIF_VER_REG     0x00U
#define SPIF_GC_REG      0x04U
#define SPIF_GCA_REG     0x08U
#define SPIF_TC_REG      0x0cU
#define SPIF_INT_STA_REG 0x18U
#define SPIF_CSD_REG     0x1cU
#define SPIF_DMA_CTL_REG 0x40U
#define SPIF_DSC_REG     0x44U

#define SPIF_GC_CFG_MODE BIT(0)
#define SPIF_GC_NMODE_EN BIT(2)
#define SPIF_GC_PMODE_EN BIT(3)
#define SPIF_GC_CS_POL   BIT(8)
#define SPIF_GC_DTR_EN   BIT(16)
#define SPIF_GC_HOLD_EN  BIT(13)
#define SPIF_GC_WP_EN    BIT(15)
#define SPIF_GC_SS_MASK  (3U << 6)

#define SPIF_GCA_RF_SRST   BIT(0)
#define SPIF_GCA_WF_SRST   BIT(1)
#define SPIF_GCA_SOFT_SRST BIT(3)
#define SPIF_GCA_DMA_END   BIT(4)

#define SPIF_TRANS_RX_EN    BIT(8)
#define SPIF_TRANS_DUMMY_EN BIT(16)
#define SPIF_TRANS_ADDR_EN  BIT(24)
#define SPIF_TRANS_CMD_EN   BIT(28)
#define SPIF_DUMMY_NUM_POS  16U

#define SPIF_DMA_START         BIT(0)
#define SPIF_DMA_DESCRIPTOR_LEN (32U << 4)
#define SPIF_DMA_FINISH_FLAG   BIT(0)
#define SPIF_DMA_RW_PROCESS    BIT(1)
#define SPIF_DMA_HBURST_INCR16 (7U << 4)
#define SPIF_DMA_BLOCK_LEN_64B (3U << 24)
#define SPIF_DMA_DATA_LEN_V1   0x1ffffU
#define SPIF_DMA_TRANS_NUM     0xffffU
#define SPIF_DMA_DONE_INT      BIT(24)
#define SPIF_DES_NORMAL_EN     BIT(28)
#define SPIF_CMD_OPCODE_POS    24U
#define SPIF_CMD_TRANS_POS_V1  6U
#define SPIF_DATA_TRANS_POS    0U
#define SPIF_CSD_DEFAULT       ((5U << 16) | (6U << 8) | 6U)

#define NOR_CMD_RDID      0x9FU
#define NOR_CMD_READ      0x03U
#define NOR_CMD_FAST_READ 0x0BU
#define PY25_MFR          0x85U
#define PY25_CAP          0x18U

#ifndef BIT
#define BIT(n) (1U << (n))
#endif

struct spif_desc
{
    uint32_t hburst_rw_flag;
    uint32_t block_data_len;
    uint32_t data_addr;
    uint32_t next_des_addr;
    uint32_t trans_phase;
    uint32_t flash_addr;
    uint32_t cmd_mode_buswidth;
    uint32_t addr_dummy_data_count;
};

/* DMA buffers must stay 4-byte aligned (SPIF encodes addr>>2). */
static struct spif_desc g_spif_desc __attribute__((aligned(64)));
static uint8_t g_spif_rx[16] __attribute__((aligned(64)));
static uint8_t g_spif_blk[4096] __attribute__((aligned(64)));

static void mmio_w(uint32_t addr, uint32_t v)
{
    *(volatile uint32_t *)addr = v;
}

static uint32_t mmio_r(uint32_t addr)
{
    return *(volatile uint32_t *)addr;
}

static void busy_delay(volatile uint32_t n)
{
    while (n--)
    {
        __asm__ volatile("nop");
    }
}

static void cache_clean_range(void *addr, uint32_t len)
{
    uint32_t a = (uint32_t)(uintptr_t)addr;
    uint32_t end = a + len;

    a &= ~63U;
    while (a < end)
    {
        amp_dcache_clean_va(a);
        a += 64U;
    }
    amp_coherent_begin();
}

static void cache_inv_range(void *addr, uint32_t len)
{
    uint32_t a = (uint32_t)(uintptr_t)addr;
    uint32_t end = a + len;

    a &= ~63U;
    while (a < end)
    {
        amp_dcache_inv_va(a);
        a += 64U;
    }
    amp_coherent_begin();
}

static void pc_set_func(uint32_t pin, uint32_t func)
{
    uint32_t bank = SUNXI_GPIO_BASE + PIO_PORT_C * SUNXI_GPIO_PORT_STRIDE;
    uint32_t cfg = bank + (pin / 8U) * 4U;
    uint32_t shift = (pin % 8U) * 4U;
    uint32_t v = mmio_r(cfg);

    v = (v & ~(0xFU << shift)) | ((func & 0xFU) << shift);
    mmio_w(cfg, v);
}

static void pc_set_pull(uint32_t pin, uint32_t pull)
{
    uint32_t bank = SUNXI_GPIO_BASE + PIO_PORT_C * SUNXI_GPIO_PORT_STRIDE;
    uint32_t reg = bank + 0x24U + (pin / 16U) * 4U;
    uint32_t shift = (pin % 16U) * 2U;
    uint32_t v = mmio_r(reg);

    v = (v & ~(0x3U << shift)) | ((pull & 0x3U) << shift);
    mmio_w(reg, v);
}

static void spif_pins_init(void)
{
    /* SyterKit: PC1 CS, PC0 SCK, PC2 MOSI, PC3 MISO, PC4 WP, PC5 HOLD — func2. */
    static const uint8_t pins[] = {1, 0, 2, 3, 4, 5};
    uint32_t i;

    for (i = 0; i < sizeof(pins); i++)
    {
        pc_set_func(pins[i], 2U);
        pc_set_pull(pins[i], 1U); /* pull-up; WP/HOLD stay inactive-high */
    }
}

static int spif_wait_clear(uint32_t reg, uint32_t mask)
{
    uint32_t t = 0x100000U;

    while (mmio_r(SPIF_BASE + reg) & mask)
    {
        if (--t == 0U)
        {
            return -1;
        }
    }
    return 0;
}

static int spif_soft_reset(void)
{
    uint32_t v = mmio_r(SPIF_BASE + SPIF_GCA_REG);

    mmio_w(SPIF_BASE + SPIF_GCA_REG, v | SPIF_GCA_DMA_END);
    if (spif_wait_clear(SPIF_GCA_REG, SPIF_GCA_DMA_END) != 0)
    {
        return -1;
    }
    mmio_w(SPIF_BASE + SPIF_GCA_REG, v | SPIF_GCA_SOFT_SRST);
    return spif_wait_clear(SPIF_GCA_REG, SPIF_GCA_SOFT_SRST);
}

static int spif_fifo_reset(void)
{
    uint32_t v = mmio_r(SPIF_BASE + SPIF_GCA_REG);

    mmio_w(SPIF_BASE + SPIF_GCA_REG, v | SPIF_GCA_RF_SRST | SPIF_GCA_WF_SRST);
    return spif_wait_clear(SPIF_GCA_REG, SPIF_GCA_RF_SRST | SPIF_GCA_WF_SRST);
}

static void spif_clock_enable(uint32_t speed_hz)
{
    uint32_t n = 0, m = 1;
    uint32_t best_n = 0, best_m = 1, best = 0;
    uint32_t rate;

    mmio_w(SPIF_BGR_REG, mmio_r(SPIF_BGR_REG) & ~((1U << SPIF_GATE_BIT) | (1U << SPIF_RST_BIT)));
    busy_delay(10000U);
    mmio_w(SPIF_BGR_REG, mmio_r(SPIF_BGR_REG) | (1U << SPIF_RST_BIT) | (1U << SPIF_GATE_BIT));

    for (n = 0; n < 4U; n++)
    {
        for (m = 1; m <= 16U; m++)
        {
            rate = SPIF_CLK_PARENT / ((1U << n) * m);
            if (rate == 0U || rate > speed_hz)
            {
                continue;
            }
            if (rate > best)
            {
                best = rate;
                best_n = n;
                best_m = m;
            }
        }
    }
    if (best == 0U)
    {
        best_n = 2;
        best_m = 5; /* 400M/4/5 = 20 MHz fallback */
        best = SPIF_CLK_PARENT / ((1U << best_n) * best_m);
    }

    mmio_w(SPIF_CLK_REG,
           (1U << 31) | (SPIF_CLK_SRC << 24) | (best_n << SPIF_CLK_N_OFF) | (best_m - 1U));
    rt_kprintf("DT: spif clk want=%u got=%u n=%u m=%u mclk=0x%08x\n",
               speed_hz, best, best_n, best_m, mmio_r(SPIF_CLK_REG));
}

static int spif_claim_bus(void)
{
    uint32_t v;

    if (spif_soft_reset() != 0 || spif_fifo_reset() != 0)
    {
        return -1;
    }

    v = mmio_r(SPIF_BASE + SPIF_GC_REG);
    v &= ~(SPIF_GC_NMODE_EN | SPIF_GC_PMODE_EN | SPIF_GC_CFG_MODE | SPIF_GC_DTR_EN |
           SPIF_GC_WP_EN | SPIF_GC_HOLD_EN | SPIF_GC_SS_MASK);
    v |= SPIF_GC_CS_POL; /* CS0 */
    mmio_w(SPIF_BASE + SPIF_GC_REG, v);

    v = mmio_r(SPIF_BASE + SPIF_TC_REG);
    v &= ~(1U << 26); /* normal (non-DTR) SCK */
    mmio_w(SPIF_BASE + SPIF_TC_REG, v);

    v = mmio_r(SPIF_BASE + SPIF_CSD_REG);
    mmio_w(SPIF_BASE + SPIF_CSD_REG, (v & ~0x00ffffffU) | SPIF_CSD_DEFAULT);
    return 0;
}

static int spif_dma_xfer(uint8_t opcode, uint32_t flash_addr, uint32_t addr_en,
                         uint32_t dummy_nbytes, uint8_t *rx, uint32_t rx_len)
{
    uint32_t t = 0x1000000U;
    uint32_t v;

    if (rx == RT_NULL || rx_len == 0U || (((uint32_t)(uintptr_t)rx) & 3U) != 0U)
    {
        return -1;
    }
    if (spif_fifo_reset() != 0)
    {
        return -2;
    }

    memset(&g_spif_desc, 0, sizeof(g_spif_desc));
    memset(rx, 0, rx_len);

    g_spif_desc.hburst_rw_flag = SPIF_DMA_HBURST_INCR16 | SPIF_DMA_RW_PROCESS | SPIF_DMA_FINISH_FLAG;
    g_spif_desc.block_data_len = SPIF_DMA_BLOCK_LEN_64B;
    g_spif_desc.block_data_len =
        (g_spif_desc.block_data_len & ~SPIF_DMA_DATA_LEN_V1) | (rx_len & SPIF_DMA_DATA_LEN_V1);
    g_spif_desc.data_addr = ((uint32_t)(uintptr_t)rx) >> 2;
    g_spif_desc.next_des_addr = 0;
    g_spif_desc.trans_phase = SPIF_TRANS_CMD_EN | SPIF_TRANS_RX_EN | addr_en;
    if (dummy_nbytes != 0U)
    {
        g_spif_desc.trans_phase |= SPIF_TRANS_DUMMY_EN;
    }
    g_spif_desc.flash_addr = flash_addr;
    /* single-IO buswidth encoding = 0 for cmd and data */
    g_spif_desc.cmd_mode_buswidth =
        ((uint32_t)opcode << SPIF_CMD_OPCODE_POS) | (0U << SPIF_CMD_TRANS_POS_V1) | (0U << SPIF_DATA_TRANS_POS);
    g_spif_desc.addr_dummy_data_count = SPIF_DES_NORMAL_EN | (rx_len & SPIF_DMA_TRANS_NUM) |
                                        ((dummy_nbytes & 0xffU) << SPIF_DUMMY_NUM_POS);
    if (addr_en)
    {
        /* 24-bit address (v2 encoding 2 << 24) */
        g_spif_desc.addr_dummy_data_count |= (2U << 24);
    }

    cache_clean_range(rx, rx_len);
    cache_clean_range(&g_spif_desc, sizeof(g_spif_desc));

    v = mmio_r(SPIF_BASE + SPIF_GC_REG);
    mmio_w(SPIF_BASE + SPIF_GC_REG, v | SPIF_GC_CFG_MODE);
    mmio_w(SPIF_BASE + SPIF_DMA_CTL_REG,
           (mmio_r(SPIF_BASE + SPIF_DMA_CTL_REG) & ~0x000003f0U) | SPIF_DMA_DESCRIPTOR_LEN);
    mmio_w(SPIF_BASE + SPIF_DSC_REG, ((uint32_t)(uintptr_t)&g_spif_desc) >> 2);
    mmio_w(SPIF_BASE + SPIF_INT_STA_REG, SPIF_DMA_DONE_INT);
    mmio_w(SPIF_BASE + SPIF_DMA_CTL_REG, mmio_r(SPIF_BASE + SPIF_DMA_CTL_REG) | SPIF_DMA_START);

    while ((mmio_r(SPIF_BASE + SPIF_INT_STA_REG) & SPIF_DMA_DONE_INT) == 0U)
    {
        if (--t == 0U)
        {
            return -3;
        }
    }
    cache_inv_range(rx, rx_len);
    mmio_w(SPIF_BASE + SPIF_INT_STA_REG, SPIF_DMA_DONE_INT);
    return 0;
}

int rt_hw_spif_probe(void)
{
    uint32_t ver;
    int ret;

    rt_kprintf("DT: spif0 controller probe @0x%08x\n", SPIF_BASE);

    /* Board-proven: 50 MHz + Fast Read 0x0B with 8 dummy clocks (TNM cycles). */
    spif_pins_init();
    spif_clock_enable(50000000U);

    ver = mmio_r(SPIF_BASE + SPIF_VER_REG);
    rt_kprintf("DT: spif0 ver=0x%08x\n", ver);
    if (ver == 0U || ver == 0xffffffffU)
    {
        rt_kprintf("DT: spif0 FAIL bad version\n");
        return -1;
    }

    if (spif_claim_bus() != 0)
    {
        rt_kprintf("DT: spif0 FAIL claim/reset\n");
        return -2;
    }

    ret = spif_dma_xfer(NOR_CMD_RDID, 0, 0, 0, g_spif_rx, 8U);
    if (ret != 0)
    {
        rt_kprintf("DT: spif0 RDID xfer FAIL %d\n", ret);
        return -3;
    }

    rt_kprintf("DT: spif0 RDID %02x %02x %02x\n", g_spif_rx[0], g_spif_rx[1], g_spif_rx[2]);
    if (g_spif_rx[0] != PY25_MFR || g_spif_rx[2] != PY25_CAP)
    {
        rt_kprintf("DT: spif0 FAIL unexpected JEDEC\n");
        return -4;
    }
    rt_kprintf("DT: spif0 OK PY25Q128-class\n");

    ret = spif_dma_xfer(NOR_CMD_FAST_READ, 0, SPIF_TRANS_ADDR_EN, 8U, g_spif_rx, 16U);
    if (ret != 0)
    {
        rt_kprintf("DT: spif0 FAST 16B FAIL %d\n", ret);
        return -5;
    }
    rt_kprintf("DT: spif0 @0: %02x %02x %02x %02x %02x %02x %02x %02x\n",
               g_spif_rx[0], g_spif_rx[1], g_spif_rx[2], g_spif_rx[3],
               g_spif_rx[4], g_spif_rx[5], g_spif_rx[6], g_spif_rx[7]);

    {
        uint32_t i;
        uint32_t sum = 0;
        uint64_t t0, t1;

        t0 = v861_clint_mtime();
        ret = spif_dma_xfer(NOR_CMD_FAST_READ, 0, SPIF_TRANS_ADDR_EN, 8U, g_spif_blk, sizeof(g_spif_blk));
        t1 = v861_clint_mtime();
        if (ret != 0)
        {
            rt_kprintf("DT: spif0 4K FAST FAIL %d\n", ret);
            return -6;
        }
        for (i = 0; i < sizeof(g_spif_blk); i++)
        {
            sum += g_spif_blk[i];
        }
        if (g_spif_blk[0] != g_spif_rx[0] || g_spif_blk[1] != g_spif_rx[1] ||
            g_spif_blk[2] != g_spif_rx[2] || g_spif_blk[3] != g_spif_rx[3])
        {
            rt_kprintf("DT: spif0 4K head mismatch\n");
            return -7;
        }
        rt_kprintf("DT: spif0 4K@50M FAST OK sum=0x%08x ~%u us\n",
                   sum, (uint32_t)((t1 - t0) / 24U));
    }
    return 0;
}
