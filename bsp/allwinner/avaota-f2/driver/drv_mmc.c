/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * MMC0 from board.dtb: clock/pins + minimal SD identify (CMD0/8/ACMD41/2/3).
 * Register bit meanings follow the public Allwinner SMHC map. Not a full
 * block layer — success means card answered identify, not filesystem R/W.
 */

#include <rthw.h>
#include <rtthread.h>
#include <string.h>

#include <libfdt.h>

#include "drv_mmc.h"

extern const unsigned char rt_hw_builtin_fdt[];

#define SUNXI_GPIO_BASE        0x02000000U
#define SUNXI_GPIO_PORT_STRIDE 0x30U

#define SMHC_GCTRL               0x00U
#define SMHC_CLKCR               0x04U
#define SMHC_TIMEOUT             0x08U
#define SMHC_WIDTH               0x0cU
#define SMHC_BLKSZ               0x10U
#define SMHC_BCNTR               0x14U
#define SMHC_CMD                 0x18U
#define SMHC_ARG                 0x1cU
#define SMHC_RESP0               0x20U
#define SMHC_RESP1               0x24U
#define SMHC_RESP2               0x28U
#define SMHC_RESP3               0x2cU
#define SMHC_IMASK               0x30U
#define SMHC_RINT                0x38U
#define SMHC_STATUS              0x3cU
#define SMHC_THLDC               0x100U
#define SMHC_CSDC                0x054U
#define SMHC_DBGC                0x050U
#define SMHC_NTSR                0x05cU
#define SMHC_FIFO                0x200U
#define SMHC_NTSR_2X_MODE        (1U << 31)
#define SMHC_STATUS_FIFO_EMPTY   (1U << 2)
#define SMHC_STATUS_CARD_PRESENT (1U << 8)

/* PIO bank power mode (gpio-v2 / D1-class): withstand select + disable auto. */
#define PIO_POW_MODE_SEL 0x380U
#define PIO_POW_MODE_CTL 0x384U
#define PIO_POW_MODE_VAL 0x388U
#define PIO_PORT_F       5U

#define SMHC_GCTRL_SOFT_RESET (1U << 0)
#define SMHC_GCTRL_FIFO_RESET (1U << 1)
#define SMHC_GCTRL_DMA_RESET  (1U << 2)
#define SMHC_GCTRL_HW_RESET   (SMHC_GCTRL_SOFT_RESET | SMHC_GCTRL_FIFO_RESET | SMHC_GCTRL_DMA_RESET)
#define SMHC_GCTRL_INT_EN     (1U << 4)
#define SMHC_GCTRL_ACCESS_AHB (1U << 31)

#define SMHC_CLKCR_MASK_D0 (1U << 31)
#define SMHC_CLKCR_CARD_ON (1U << 16)
#define SMHC_CLKCR_DIV(n)  (((n) - 1U) & 0xffU)

#define SMHC_CMD_RESP      (1U << 6)
#define SMHC_CMD_LONG_RESP (1U << 7)
#define SMHC_CMD_CHK_CRC   (1U << 8)
#define SMHC_CMD_DATA_EXP  (1U << 9)
#define SMHC_CMD_WRITE     (1U << 10)
#define SMHC_CMD_WAIT_PRE  (1U << 13)
#define SMHC_CMD_INIT      (1U << 15)
#define SMHC_CMD_UPCLK     (1U << 21)
#define SMHC_CMD_START     (1U << 31)

#define SMHC_RINT_CMD_DONE  (1U << 2)
#define SMHC_RINT_DATA_OVER (1U << 3)
#define SMHC_RINT_ERR                                            \
    ((1U << 1) | (1U << 6) | (1U << 7) | (1U << 8) | (1U << 9) | \
     (1U << 11) | (1U << 12) | (1U << 13) | (1U << 15))

#define RSP_NONE 0
#define RSP_R1   (SMHC_CMD_RESP | SMHC_CMD_CHK_CRC)
#define RSP_R2   (SMHC_CMD_RESP | SMHC_CMD_LONG_RESP | SMHC_CMD_CHK_CRC)
#define RSP_R3   (SMHC_CMD_RESP)
#define RSP_R6   (SMHC_CMD_RESP | SMHC_CMD_CHK_CRC)
#define RSP_R7   (SMHC_CMD_RESP | SMHC_CMD_CHK_CRC)

#define MMC_CMD_GO_IDLE      0
#define MMC_CMD_ALL_SEND_CID 2
#define SD_CMD_SEND_REL_ADDR 3
#define MMC_CMD_SELECT_CARD  7
#define SD_CMD_SEND_IF_COND  8
#define MMC_CMD_SET_BLOCKLEN 16
#define MMC_CMD_READ_SINGLE  17
#define MMC_CMD_APP_CMD      55
#define SD_CMD_APP_OP_COND   41

#define OCR_HCS     0x40000000U
#define OCR_BUSY    0x80000000U
#define OCR_VOLTAGE 0x00ff8000U

struct v861_mmc_fdt
{
    uint32_t reg;
    uint32_t bus_width;
    uint32_t max_freq;
    uint32_t gate_reg;
    uint32_t gate_bit;
    uint32_t reset_reg;
    uint32_t reset_bit;
    uint32_t mod_clk_reg;
    uint32_t mod_n_off;
    uint32_t mod_m_off;
    uint32_t mod_default_sel;
    uint32_t src_rates[4];
    uint32_t pin_port[8];
    uint32_t pin_num[8];
    uint32_t pin_func[8];
    uint32_t pin_count;
    char label[16];
};

static void mmio_w(uint32_t addr, uint32_t v)
{
    *(volatile uint32_t *)addr = v;
}

static uint32_t mmio_r(uint32_t addr)
{
    return *(volatile uint32_t *)addr;
}

static void mmio_set_bit(uint32_t addr, uint32_t bit)
{
    mmio_w(addr, mmio_r(addr) | (1U << bit));
}

static void mmio_clr_bit(uint32_t addr, uint32_t bit)
{
    mmio_w(addr, mmio_r(addr) & ~(1U << bit));
}

static void busy_delay(uint32_t loops)
{
    while (loops--)
    {
        __asm__ volatile("nop");
    }
}

/* Rough ms stall without tick (C907 ~GHz: ~1e6 nops ≈ 1ms). */
static void busy_mdelay(uint32_t ms)
{
    while (ms--)
    {
        busy_delay(1000000U);
    }
}

/* D1/V861 bank layout: mux@0, data@0x10, dlevel@0x14 (4bit), pull@0x24 (2bit).
 * Match card0_boot_para in sys_config.fex: PF0-5 <func2><pull-up1><drv2>. */
static void v861_apply_pin(uint32_t port, uint32_t pin, uint32_t func)
{
    uint32_t bank = SUNXI_GPIO_BASE + port * SUNXI_GPIO_PORT_STRIDE;
    uint32_t cfg = bank + (pin / 8U) * 4U;
    uint32_t shift = (pin % 8U) * 4U;
    uint32_t value = mmio_r(cfg);
    uint32_t drv_reg = bank + 0x14U + (pin / 8U) * 4U;
    uint32_t drv_shift = (pin % 8U) * 4U;
    uint32_t pull_reg = bank + 0x24U + (pin / 16U) * 4U;
    uint32_t pull_shift = (pin % 16U) * 2U;

    value = (value & ~(0xFU << shift)) | ((func & 0xFU) << shift);
    mmio_w(cfg, value);

    value = mmio_r(drv_reg);
    value = (value & ~(0xFU << drv_shift)) | (2U << drv_shift);
    mmio_w(drv_reg, value);

    value = mmio_r(pull_reg);
    value = (value & ~(0x3U << pull_shift)) | (1U << pull_shift); /* pull-up */
    mmio_w(pull_reg, value);
}

static uint32_t prop_u32(const void *fdt, int node, const char *name, uint32_t def)
{
    int len = 0;
    const fdt32_t *p = fdt_getprop(fdt, node, name, &len);
    if (!p || len < 4)
    {
        return def;
    }
    return fdt32_to_cpu(p[0]);
}

static int prop_u32_pair(const void *fdt, int node, const char *name, uint32_t *a, uint32_t *b)
{
    int len = 0;
    const fdt32_t *p = fdt_getprop(fdt, node, name, &len);
    if (!p || len < 8)
    {
        return -1;
    }
    *a = fdt32_to_cpu(p[0]);
    *b = fdt32_to_cpu(p[1]);
    return 0;
}

static int load_mmc_fdt(struct v861_mmc_fdt *out)
{
    const void *fdt = rt_hw_builtin_fdt;
    int node, len, i;
    const char *label;
    const fdt32_t *pins;
    const fdt32_t *mod;
    const fdt32_t *rates;

    memset(out, 0, sizeof(*out));
    if (fdt_check_header(fdt) != 0)
    {
        return -1;
    }

    node = fdt_path_offset(fdt, "/soc/mmc@4020000");
    if (node < 0)
    {
        node = fdt_node_offset_by_compatible(fdt, -1, "allwinner,sunxi-mmc");
    }
    if (node < 0)
    {
        return -2;
    }

    out->reg = prop_u32(fdt, node, "reg", 0x04020000U);
    out->bus_width = prop_u32(fdt, node, "bus-width", 4);
    out->max_freq = prop_u32(fdt, node, "max-frequency", 50000000U);
    if (prop_u32_pair(fdt, node, "allwinner,clock-gate", &out->gate_reg, &out->gate_bit) != 0)
    {
        return -3;
    }
    if (prop_u32_pair(fdt, node, "allwinner,reset", &out->reset_reg, &out->reset_bit) != 0)
    {
        return -4;
    }

    mod = fdt_getprop(fdt, node, "allwinner,module-clock", &len);
    if (mod && len >= 16)
    {
        out->mod_clk_reg = fdt32_to_cpu(mod[0]);
        out->mod_n_off = fdt32_to_cpu(mod[1]);
        out->mod_m_off = fdt32_to_cpu(mod[2]);
        out->mod_default_sel = fdt32_to_cpu(mod[3]);
    }

    rates = fdt_getprop(fdt, node, "allwinner,clock-source-rates", &len);
    if (rates && len >= 16)
    {
        for (i = 0; i < 4; i++)
        {
            out->src_rates[i] = fdt32_to_cpu(rates[i]);
        }
    }
    else
    {
        out->src_rates[0] = 24000000U;
        out->src_rates[1] = 400000000U;
        out->src_rates[2] = 300000000U;
    }

    label = fdt_getprop(fdt, node, "label", &len);
    if (label && len > 0)
    {
        rt_strncpy(out->label, label, sizeof(out->label) - 1);
    }
    else
    {
        rt_strncpy(out->label, "mmc0", sizeof(out->label) - 1);
    }

    pins = fdt_getprop(fdt, node, "allwinner,pins", &len);
    if (!pins || len < 12)
    {
        return -5;
    }
    out->pin_count = (uint32_t)(len / 12);
    if (out->pin_count > 8)
    {
        out->pin_count = 8;
    }
    for (i = 0; i < (int)out->pin_count; i++)
    {
        out->pin_port[i] = fdt32_to_cpu(pins[i * 3 + 0]);
        out->pin_num[i] = fdt32_to_cpu(pins[i * 3 + 1]);
        out->pin_func[i] = fdt32_to_cpu(pins[i * 3 + 2]);
    }
    return 0;
}

static void set_module_clock(struct v861_mmc_fdt *cfg, uint32_t hz)
{
    uint32_t source = (hz <= 4000000U) ? 0U : cfg->mod_default_sel;
    uint32_t parent = cfg->src_rates[source];
    uint32_t div;
    uint32_t n = 0, m = 1;
    uint32_t val;

    if (parent == 0)
    {
        parent = 24000000U;
    }
    div = (2U * parent + hz) / (2U * hz);
    if (div == 0)
    {
        div = 1;
    }
    if (div > 64U)
    {
        n = 3;
        m = div >> 3;
    }
    else if (div > 32U)
    {
        n = 2;
        m = div >> 2;
    }
    else if (div > 16U)
    {
        n = 1;
        m = div >> 1;
    }
    else
    {
        n = 0;
        m = div;
    }
    if (m == 0)
    {
        m = 1;
    }

    val = (1U << 31) | (source << 24) | (n << cfg->mod_n_off) | ((m - 1U) << cfg->mod_m_off);
    mmio_w(cfg->mod_clk_reg, val);
}

static int smhc_update_clk(uint32_t base)
{
    uint32_t i;
    uint32_t clkcr = mmio_r(base + SMHC_CLKCR);

    mmio_w(base + SMHC_CLKCR, clkcr | SMHC_CLKCR_MASK_D0);
    mmio_w(base + SMHC_CMD, SMHC_CMD_START | SMHC_CMD_UPCLK | SMHC_CMD_WAIT_PRE);
    for (i = 0; i < 2000000U; i++)
    {
        if ((mmio_r(base + SMHC_CMD) & SMHC_CMD_START) == 0)
        {
            break;
        }
    }
    if (mmio_r(base + SMHC_CMD) & SMHC_CMD_START)
    {
        return -1;
    }
    mmio_w(base + SMHC_CLKCR, mmio_r(base + SMHC_CLKCR) & ~SMHC_CLKCR_MASK_D0);
    mmio_w(base + SMHC_RINT, mmio_r(base + SMHC_RINT));
    return 0;
}

static int smhc_send_cmd(uint32_t base, uint32_t idx, uint32_t arg, uint32_t rsp_flags, uint32_t *resp)
{
    /* SyterKit: WAIT_PRE only with data; command-only uses START (+ INIT for CMD0). */
    uint32_t cmdval = SMHC_CMD_START | rsp_flags | (idx & 0x3fU);
    uint32_t i;
    uint32_t rint;

    if (idx == 0)
    {
        cmdval |= SMHC_CMD_INIT;
    }

    mmio_w(base + SMHC_RINT, 0xffffffffU);
    mmio_w(base + SMHC_ARG, arg);
    mmio_w(base + SMHC_CMD, cmdval);

    for (i = 0; i < 500000U; i++)
    {
        rint = mmio_r(base + SMHC_RINT);
        if (rint & SMHC_RINT_ERR)
        {
            return -1; /* leave RINT for caller log */
        }
        if (rint & SMHC_RINT_CMD_DONE)
        {
            break;
        }
    }
    if ((mmio_r(base + SMHC_RINT) & SMHC_RINT_CMD_DONE) == 0)
    {
        return -2;
    }

    if (resp)
    {
        if (rsp_flags & SMHC_CMD_LONG_RESP)
        {
            resp[0] = mmio_r(base + SMHC_RESP3);
            resp[1] = mmio_r(base + SMHC_RESP2);
            resp[2] = mmio_r(base + SMHC_RESP1);
            resp[3] = mmio_r(base + SMHC_RESP0);
        }
        else
        {
            resp[0] = mmio_r(base + SMHC_RESP0);
        }
    }

    mmio_w(base + SMHC_RINT, 0xffffffffU);
    return 0;
}

/* Board TF is 3V3; tell PIO PF bank to use 3V3 withstand (SyterKit gpio-v2-pow). */
static void v861_pf_io_3v3(void)
{
    uint32_t sel = mmio_r(SUNXI_GPIO_BASE + PIO_POW_MODE_SEL);
    uint32_t ctl = mmio_r(SUNXI_GPIO_BASE + PIO_POW_MODE_CTL);

    /* sun55-style polarity reused by gpio-v2: 1 = 3V3, 0 = 1V8 */
    sel |= (1U << PIO_PORT_F);
    ctl |= (1U << PIO_PORT_F);
    mmio_w(SUNXI_GPIO_BASE + PIO_POW_MODE_SEL, sel);
    mmio_w(SUNXI_GPIO_BASE + PIO_POW_MODE_CTL, ctl);
}

static int smhc_host_init(struct v861_mmc_fdt *cfg)
{
    uint32_t base = cfg->reg;
    uint32_t i;
    uint32_t t;

    mmio_clr_bit(cfg->gate_reg, cfg->gate_bit);
    mmio_clr_bit(cfg->reset_reg, cfg->reset_bit);
    busy_mdelay(1);
    mmio_set_bit(cfg->reset_reg, cfg->reset_bit);
    mmio_set_bit(cfg->gate_reg, cfg->gate_bit);

    v861_pf_io_3v3();
    for (i = 0; i < cfg->pin_count; i++)
    {
        v861_apply_pin(cfg->pin_port[i], cfg->pin_num[i], cfg->pin_func[i]);
    }

    /* Soft-reset first — NTSR is programmed after, or reset clears 2xclk. */
    mmio_w(base + SMHC_GCTRL, SMHC_GCTRL_HW_RESET);
    for (t = 0; t < 100000U; t++)
    {
        if ((mmio_r(base + SMHC_GCTRL) & SMHC_GCTRL_HW_RESET) == 0)
        {
            break;
        }
    }
    mmio_w(base + SMHC_GCTRL, SMHC_GCTRL_INT_EN);
    mmio_w(base + SMHC_TIMEOUT, (0xfffffU << 8) | 0xffU);
    mmio_w(base + SMHC_THLDC, (512U << 16) | (1U << 2) | (1U << 0));
    mmio_w(base + SMHC_CSDC, 0x3U);
    mmio_w(base + SMHC_DBGC, 0xdebU);
    mmio_w(base + SMHC_WIDTH, 0); /* 1-bit */
    mmio_w(base + SMHC_IMASK, 0);
    mmio_w(base + SMHC_RINT, 0xffffffffU);

    /*
     * Module clock must run before UPCLK — otherwise SMHC_CMD_START sticks
     * and we used to fail at the first update (-10) with mclk still cold.
     * Order: mclk + 2x mode → card clk off/update → on/update.
     */
    if (cfg->mod_clk_reg == 0)
    {
        return -9;
    }
    set_module_clock(cfg, 800000U); /* timing mode 1: 2 * 400 kHz card clock */
    busy_mdelay(1);
    mmio_w(base + SMHC_NTSR, mmio_r(base + SMHC_NTSR) | SMHC_NTSR_2X_MODE);

    mmio_w(base + SMHC_CLKCR, mmio_r(base + SMHC_CLKCR) & ~SMHC_CLKCR_CARD_ON);
    if (smhc_update_clk(base) != 0)
    {
        rt_kprintf("DT: mmc0 upclk#1 fail cmd=0x%08x clkcr=0x%08x mclk=0x%08x\n",
                   mmio_r(base + SMHC_CMD), mmio_r(base + SMHC_CLKCR),
                   mmio_r(cfg->mod_clk_reg));
        return -10;
    }

    mmio_w(base + SMHC_CLKCR, SMHC_CLKCR_CARD_ON); /* div field 0 */
    if (smhc_update_clk(base) != 0)
    {
        rt_kprintf("DT: mmc0 upclk#2 fail cmd=0x%08x clkcr=0x%08x mclk=0x%08x\n",
                   mmio_r(base + SMHC_CMD), mmio_r(base + SMHC_CLKCR),
                   mmio_r(cfg->mod_clk_reg));
        return -11;
    }

    return 0;
}

static int smhc_identify(uint32_t base, uint32_t *ocr_out, uint32_t *rca_out)
{
    uint32_t resp[4];
    uint32_t ocr = 0;
    uint32_t acmd41_arg = OCR_VOLTAGE | OCR_HCS;
    uint32_t i;
    int ret;

    ret = smhc_send_cmd(base, MMC_CMD_GO_IDLE, 0, RSP_NONE, RT_NULL);
    if (ret != 0)
    {
        rt_kprintf("DT: mmc0 CMD0 fail %d\n", ret);
        return -20;
    }
    busy_mdelay(2);

    /*
     * CMD8 is SD 2.0+. SD 1.x cards leave it unanswered — that is not a
     * controller fault; continue with ACMD41 without HCS (byte-addressed SDSC).
     */
    ret = smhc_send_cmd(base, SD_CMD_SEND_IF_COND, 0x1aaU, RSP_R7, resp);
    if (ret != 0)
    {
        rt_kprintf("DT: mmc0 CMD8 fail %d — try SDSC (no HCS)\n", ret);
        acmd41_arg = OCR_VOLTAGE;
    }
    else if ((resp[0] & 0xffU) != 0xaaU)
    {
        rt_kprintf("DT: mmc0 CMD8 bad pattern 0x%08x\n", resp[0]);
        return -22;
    }

    for (i = 0; i < 1000U; i++)
    {
        ret = smhc_send_cmd(base, MMC_CMD_APP_CMD, 0, RSP_R1, resp);
        if (ret != 0)
        {
            return -23;
        }
        ret = smhc_send_cmd(base, SD_CMD_APP_OP_COND, acmd41_arg, RSP_R3, resp);
        if (ret != 0)
        {
            return -24;
        }
        ocr = resp[0];
        if (ocr & OCR_BUSY)
        {
            break;
        }
        busy_mdelay(1);
    }
    if ((ocr & OCR_BUSY) == 0)
    {
        rt_kprintf("DT: mmc0 ACMD41 timeout ocr=0x%08x\n", ocr);
        return -25;
    }

    ret = smhc_send_cmd(base, MMC_CMD_ALL_SEND_CID, 0, RSP_R2, resp);
    if (ret != 0)
    {
        return -26;
    }

    ret = smhc_send_cmd(base, SD_CMD_SEND_REL_ADDR, 0, RSP_R6, resp);
    if (ret != 0)
    {
        return -27;
    }

    *ocr_out = ocr;
    *rca_out = resp[0] >> 16;
    return 0;
}

/* PIO/AHB single-block read (CMD17). SDHC uses LBA; SDSC uses byte addr. */
static int smhc_read_sector(uint32_t base, uint32_t ocr, uint32_t rca,
                            uint32_t lba, uint8_t *buf, uint32_t len)
{
    uint32_t resp[4];
    uint32_t arg;
    uint32_t cmdval;
    uint32_t i;
    uint32_t words;
    uint32_t rint;
    int ret;

    if (buf == RT_NULL || len < 512U)
    {
        return -30;
    }

    ret = smhc_send_cmd(base, MMC_CMD_SELECT_CARD, rca << 16, RSP_R1, resp);
    if (ret != 0)
    {
        return -31;
    }

    ret = smhc_send_cmd(base, MMC_CMD_SET_BLOCKLEN, 512U, RSP_R1, resp);
    if (ret != 0)
    {
        return -32;
    }

    arg = (ocr & OCR_HCS) ? lba : (lba * 512U);
    mmio_w(base + SMHC_GCTRL, mmio_r(base + SMHC_GCTRL) | SMHC_GCTRL_ACCESS_AHB);
    mmio_w(base + SMHC_BLKSZ, 512U);
    mmio_w(base + SMHC_BCNTR, 512U);
    mmio_w(base + SMHC_RINT, 0xffffffffU);

    cmdval = SMHC_CMD_START | SMHC_CMD_RESP | SMHC_CMD_CHK_CRC |
             SMHC_CMD_DATA_EXP | SMHC_CMD_WAIT_PRE | MMC_CMD_READ_SINGLE;
    mmio_w(base + SMHC_ARG, arg);
    mmio_w(base + SMHC_CMD, cmdval);

    words = 512U / 4U;
    for (i = 0; i < words; i++)
    {
        uint32_t t;
        for (t = 0; t < 2000000U; t++)
        {
            if ((mmio_r(base + SMHC_STATUS) & SMHC_STATUS_FIFO_EMPTY) == 0)
            {
                break;
            }
            if (mmio_r(base + SMHC_RINT) & SMHC_RINT_ERR)
            {
                return -33;
            }
        }
        if (mmio_r(base + SMHC_STATUS) & SMHC_STATUS_FIFO_EMPTY)
        {
            return -34;
        }
        {
            uint32_t w = mmio_r(base + SMHC_FIFO);
            buf[i * 4U + 0U] = (uint8_t)(w & 0xffU);
            buf[i * 4U + 1U] = (uint8_t)((w >> 8) & 0xffU);
            buf[i * 4U + 2U] = (uint8_t)((w >> 16) & 0xffU);
            buf[i * 4U + 3U] = (uint8_t)((w >> 24) & 0xffU);
        }
    }

    for (i = 0; i < 2000000U; i++)
    {
        rint = mmio_r(base + SMHC_RINT);
        if (rint & SMHC_RINT_ERR)
        {
            return -35;
        }
        if (rint & SMHC_RINT_DATA_OVER)
        {
            break;
        }
    }
    if ((mmio_r(base + SMHC_RINT) & SMHC_RINT_DATA_OVER) == 0)
    {
        return -36;
    }

    mmio_w(base + SMHC_RINT, 0xffffffffU);
    return 0;
}

int rt_hw_mmc0_probe_from_fdt(void)
{
    struct v861_mmc_fdt cfg;
    uint32_t ocr = 0, rca = 0;
    uint8_t sector[512];
    int ret;

    ret = load_mmc_fdt(&cfg);
    if (ret != 0)
    {
        rt_kprintf("DT: mmc0 load FAILED (%d)\n", ret);
        return ret;
    }

    rt_kprintf("DT: mmc0 %s reg=0x%08x bus=%u\n", cfg.label, cfg.reg, cfg.bus_width);

    ret = smhc_host_init(&cfg);
    if (ret != 0)
    {
        rt_kprintf("DT: mmc0 host init FAIL %d gctrl=0x%08x\n",
                   ret, mmio_r(cfg.reg + SMHC_GCTRL));
        return ret;
    }
    rt_kprintf("DT: mmc0 host ready gctrl=0x%08x\n", mmio_r(cfg.reg + SMHC_GCTRL));

    ret = smhc_identify(cfg.reg, &ocr, &rca);
    if (ret != 0)
    {
        rt_kprintf("DT: mmc0 identify FAIL %d\n", ret);
        return ret;
    }

    rt_kprintf("DT: mmc0 card OK ocr=0x%08x rca=0x%04x %s\n",
               ocr, rca, (ocr & OCR_HCS) ? "SDHC/SDXC" : "SDSC");

    memset(sector, 0, sizeof(sector));
    ret = smhc_read_sector(cfg.reg, ocr, rca, 0, sector, sizeof(sector));
    if (ret != 0)
    {
        rt_kprintf("DT: mmc0 read FAIL %d rint=0x%08x status=0x%08x\n",
                   ret, mmio_r(cfg.reg + SMHC_RINT), mmio_r(cfg.reg + SMHC_STATUS));
        return ret;
    }

    rt_kprintf("DT: mmc0 read OK lba0 sig=%02x%02x head=%02x %02x %02x %02x\n",
               sector[510], sector[511],
               sector[0], sector[1], sector[2], sector[3]);
    return 0;
}
