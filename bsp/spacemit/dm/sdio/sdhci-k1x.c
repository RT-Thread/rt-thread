/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include "dev_sdio_dm.h"
#include "dev_sdhci_dm.h"

#define DBG_TAG "sdhci.k1x"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define CANDIDATE_WIN_NUM           3
#define SELECT_DELAY_NUM            9
#define WINDOW_1ST                  0
#define WINDOW_2ND                  1
#define WINDOW_3RD                  2

#define RX_TUNING_WINDOW_THRESHOLD  80
#define RX_TUNING_DLINE_REG         0x09
#define TX_TUNING_DLINE_REG         0x00
#define TX_TUNING_DELAYCODE         127

#define BOOTPART_NOACC_DEFAULT      0

/* SDH registers define */
#define SDHC_OP_EXT_REG             0x108
#define OVRRD_CLK_OEN               0x0800
#define FORCE_CLK_ON                0x1000

#define SDHC_LEGACY_CTRL_REG        0x10c
#define GEN_PAD_CLK_ON              0x0040

#define SDHC_MMC_CTRL_REG           0x114
#define MISC_INT_EN                 0x0002
#define MISC_INT                    0x0004
#define ENHANCE_STROBE_EN           0x0100
#define MMC_HS400                   0x0200
#define MMC_HS200                   0x0400
#define MMC_CARD_MODE               0x1000

#define SDHC_TX_CFG_REG             0x11c
#define TX_INT_CLK_SEL              0x40000000
#define TX_MUX_SEL                  0x80000000

#define SDHC_PHY_CTRL_REG           0x160
#define PHY_FUNC_EN                 0x0001
#define PHY_PLL_LOCK                0x0002
#define HOST_LEGACY_MODE            0x80000000

#define SDHC_PHY_FUNC_REG           0x164
#define PHY_TEST_EN                 0x0080
#define HS200_USE_RFIFO             0x8000

#define SDHC_PHY_DLLCFG             0x168
#define DLL_PREDLY_NUM              0x04
#define DLL_FULLDLY_RANGE           0x10
#define DLL_VREG_CTRL               0x40
#define DLL_ENABLE                  0x80000000
#define DLL_REFRESH_SWEN_SHIFT      0x1c
#define DLL_REFRESH_SW_SHIFT        0x1d

#define SDHC_PHY_DLLCFG1            0x16c
#define DLL_REG2_CTRL               0x0c
#define DLL_REG3_CTRL_MASK          0xff
#define DLL_REG3_CTRL_SHIFT         0x10
#define DLL_REG2_CTRL_MASK          0xff
#define DLL_REG2_CTRL_SHIFT         0x08
#define DLL_REG1_CTRL               0x92
#define DLL_REG1_CTRL_MASK          0xff
#define DLL_REG1_CTRL_SHIFT         0x00

#define SDHC_PHY_DLLSTS             0x170
#define DLL_LOCK_STATE              0x01

#define SDHC_PHY_DLLSTS1            0x174
#define DLL_MASTER_DELAY_MASK       0xff
#define DLL_MASTER_DELAY_SHIFT      0x10

#define SDHC_PHY_PADCFG_REG         0x178
#define RX_BIAS_CTRL_SHIFT          0x5
#define PHY_DRIVE_SEL_SHIFT         0x0
#define PHY_DRIVE_SEL_MASK          0x7
#define PHY_DRIVE_SEL_DEFAULT       0x4

#define RPM_DELAY                   50
#define MAX_74CLK_WAIT_COUNT        100

#define MMC1_IO_V18EN               0x04
#define AKEY_ASFAR                  0xbaba
#define AKEY_ASSAR                  0xeb10

/* Spacemit private quirk, shared with the DT binding. */
#define RT_SDHCI_QUIRK2_SET_AIB_MMC RT_BIT(27)

#define SDHC_RX_CFG_REG             0x118
#define RX_SDCLK_SEL0_MASK          0x03
#define RX_SDCLK_SEL0_SHIFT         0x00
#define RX_SDCLK_SEL0               0x02
#define RX_SDCLK_SEL1_MASK          0x03
#define RX_SDCLK_SEL1_SHIFT         0x02
#define RX_SDCLK_SEL1               0x01

#define SDHC_DLINE_CTRL_REG         0x130
#define DLINE_PU                    0x01
#define RX_DLINE_CODE_MASK          0xff
#define RX_DLINE_CODE_SHIFT         0x10
#define TX_DLINE_CODE_MASK          0xff
#define TX_DLINE_CODE_SHIFT         0x18

#define SDHC_DLINE_CFG_REG          0x134
#define RX_DLINE_REG_MASK           0xff
#define RX_DLINE_REG_SHIFT          0x00
#define RX_DLINE_GAIN_MASK          0x1
#define RX_DLINE_GAIN_SHIFT         0x8
#define RX_DLINE_GAIN               0x1
#define TX_DLINE_REG_MASK           0xff
#define TX_DLINE_REG_SHIFT          0x10

#define SDHC_RX_TUNE_DELAY_MIN      0x0
#define SDHC_RX_TUNE_DELAY_MAX      0xff
#define SDHC_RX_TUNE_DELAY_STEP     0x1

#define MMC_CAP2_QUIRK_BREAK_SDR104 RT_BIT(30)

enum window_type
{
    LEFT_WINDOW = 0,
    MIDDLE_WINDOW = 1,
    RIGHT_WINDOW = 2,
};

struct tuning_window
{
    rt_uint8_t type;
    rt_uint8_t min_delay;
    rt_uint8_t max_delay;
};

struct rx_tuning
{
    rt_uint8_t rx_dline_reg;
    rt_uint8_t select_delay_num;
    rt_uint8_t current_delay_index;
    /* 0: biggest window, 1: bigger, 2:  small */
    struct tuning_window windows[CANDIDATE_WIN_NUM];
    rt_uint8_t select_delay[SELECT_DELAY_NUM];

    rt_uint32_t card_cid[4];
    rt_uint8_t window_limit;
    rt_uint8_t tuning_fail;
    rt_uint8_t window_type;
};

struct k1x_sdhci_data
{
    rt_uint32_t host_freq;
    rt_uint32_t flags;
    rt_uint32_t host_caps;
    rt_uint32_t host_caps2;
    rt_uint32_t host_caps_disable;
    rt_uint32_t host_caps2_disable;
    rt_uint32_t quirks;
    rt_uint32_t quirks2;
    rt_uint32_t pm_caps;

    rt_uint32_t aib_mmc1_io_reg;
    rt_uint32_t apbc_asfar_reg;
    rt_uint32_t apbc_assar_reg;

    rt_uint8_t tx_dline_reg;
    rt_uint8_t tx_delaycode;
    rt_uint8_t tx_delaycode_cnt;
    rt_uint8_t tx_delaycode_array[2];
    rt_uint8_t phy_driver_sel;
    struct rx_tuning rxtuning;
    rt_uint8_t need_reset_dllcfg1;
    rt_uint32_t prev_dllcfg1;
    rt_uint32_t curr_dllcfg1;
    rt_uint32_t new_dllcfg1;
    rt_uint8_t dllcfg1_odd_reset;
    rt_uint32_t rx_tuning_freq;
};

struct k1x_sdhci
{
    struct rt_sdhci_host *host;

    struct rt_clk *clk_core;
    struct rt_clk *clk_io;
    struct rt_clk *clk_aib;
    struct rt_reset_control *rstc;
    unsigned char power_mode;

    rt_bool_t pinctrl;
    struct k1x_sdhci_data pdata;
};

static const rt_uint32_t tuning_patten4[16] =
{
    0x00ff0fff, 0xccc3ccff, 0xffcc3cc3, 0xeffefffe,
    0xddffdfff, 0xfbfffbff, 0xff7fffbf, 0xefbdf777,
    0xf0fff0ff, 0x3cccfc0f, 0xcfcc33cc, 0xeeffefff,
    0xfdfffdff, 0xffbfffdf, 0xfff7ffbb, 0xde7b7ff7,
};

static const rt_uint32_t tuning_patten8[32] =
{
    0xff00ffff, 0x0000ffff, 0xccccffff, 0xcccc33cc,
    0xcc3333cc, 0xffffcccc, 0xffffeeff, 0xffeeeeff,
    0xffddffff, 0xddddffff, 0xbbffffff, 0xbbffffff,
    0xffffffbb, 0xffffff77, 0x77ff7777, 0xffeeddbb,
    0x00ffffff, 0x00ffffff, 0xccffff00, 0xcc33cccc,
    0x3333cccc, 0xffcccccc, 0xffeeffff, 0xeeeeffff,
    0xddffffff, 0xddffffff, 0xffffffdd, 0xffffffbb,
    0xffffbbbb, 0xffff77ff, 0xff7777ff, 0xeeddbb77,
};

static void k1x_sdhci_set_clk_gate(struct rt_sdhci_host *host, rt_bool_t auto_gate)
{
    unsigned int reg;

    reg = rt_sdhci_readl(host, SDHC_OP_EXT_REG);
    if (auto_gate)
    {
        reg &= ~(OVRRD_CLK_OEN | FORCE_CLK_ON);
    }
    else
    {
        reg |= OVRRD_CLK_OEN | FORCE_CLK_ON;
    }
    rt_sdhci_writel(host, reg, SDHC_OP_EXT_REG);
}

static rt_bool_t k1x_sdhci_card_busy(struct rt_mmc_host *mmc)
{
    rt_bool_t res;
    rt_uint32_t cmd, present_state;
    struct rt_sdhci_host *host = rt_mmc_priv(mmc);

    /* Check whether DAT[0] is 0 */
    present_state = rt_sdhci_readl(host, RT_SDHCI_PRESENT_STATE);
    res = !(present_state & RT_SDHCI_DATA_0_LVL_MASK);

    if (host->mmc->caps2 & MMC_CAP2_NO_MMC)
    {
        cmd = RT_SDHCI_GET_CMD(rt_sdhci_readw(host, RT_SDHCI_COMMAND));
        if (cmd == VOLTAGE_SWITCH && host->mmc->ios.signal_voltage == MMC_SIGNAL_VOLTAGE_180)
        {
            /* Recover the auto clock */
            k1x_sdhci_set_clk_gate(host, RT_TRUE);
        }
    }

    return res;
}

static void k1x_sdhci_enable_sdio_irq_nolock(struct rt_sdhci_host *host, rt_bool_t enable)
{
    if (!(host->flags & RT_SDHCI_DEVICE_DEAD))
    {
        if (enable)
        {
            host->ier |= RT_SDHCI_INT_CARD_INT;
        }
        else
        {
            host->ier &= ~RT_SDHCI_INT_CARD_INT;
        }

        rt_sdhci_writel(host, host->ier, RT_SDHCI_INT_ENABLE);
        rt_sdhci_writel(host, host->ier, RT_SDHCI_SIGNAL_ENABLE);
    }
}

static void k1x_sdhci_enable_sdio_irq(struct rt_mmc_host *mmc, rt_bool_t enable)
{
    rt_ubase_t level;
    struct rt_sdhci_host *host = rt_mmc_priv(mmc);

    level = rt_spin_lock_irqsave(&host->lock);
    k1x_sdhci_enable_sdio_irq_nolock(host, enable);
    rt_spin_unlock_irqrestore(&host->lock, level);
}

static void k1x_enable_sdio_irq(struct rt_mmc_host *mmc, int enable)
{
    rt_ubase_t level;
    struct rt_sdhci_host *host = rt_mmc_priv(mmc);

    k1x_sdhci_enable_sdio_irq(mmc, enable);

    /* Avoid to read the SDIO_CCCR_INTx */
    level = rt_spin_lock_irqsave(&host->lock);
    mmc->sdio_irq_pending = RT_TRUE;
    rt_spin_unlock_irqrestore(&host->lock, level);
}

static void k1x_sdhci_set_clock(struct rt_sdhci_host *host, unsigned int clock)
{
    rt_uint32_t reg, cmd;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct k1x_sdhci *k1x = rt_sdhci_pltfm_priv(pltfm_host);
    struct rt_mmc_host *mmc = host->mmc;

    /*
     * According to the SDHC_TX_CFG_REG(0x11c<bit>),
     * set TX_INT_CLK_SEL to gurantee the hold time
     * at default speed mode or HS/SDR12/SDR25/SDR50 mode.
     */
    reg = rt_sdhci_readl(host, SDHC_TX_CFG_REG);
    if (mmc->ios.timing == MMCSD_TIMING_LEGACY ||
        mmc->ios.timing == MMCSD_TIMING_SD_HS ||
        mmc->ios.timing == MMCSD_TIMING_UHS_SDR12 ||
        mmc->ios.timing == MMCSD_TIMING_UHS_SDR25 ||
        mmc->ios.timing == MMCSD_TIMING_UHS_SDR50 ||
        mmc->ios.timing == MMCSD_TIMING_MMC_HS)
    {
        reg |= TX_INT_CLK_SEL;
    }
    else
    {
        reg &= ~TX_INT_CLK_SEL;
    }
    rt_sdhci_writel(host, reg, SDHC_TX_CFG_REG);

    /* set pinctrl state */
    if (k1x->pinctrl)
    {
        if (clock >= 200000000)
        {
            rt_pin_ctrl_confs_apply_by_name(mmc->parent, "fast");
        }
        else if (clock == 0 || host->mmc->ios.bus_width < MMC_BUS_WIDTH_4)
        {
            rt_pin_ctrl_confs_apply_by_name(mmc->parent, "debug");
        }
        else
        {
            rt_pin_ctrl_confs_apply_by_name(mmc->parent, "default");
        }
    }

    rt_sdhci_set_clock(host, clock);

    if (host->mmc->caps2 & MMC_CAP2_NO_MMC)
    {
        /*
        * According to the SD spec, during a signal voltage level switch,
        * the clock must be closed for 5 ms.
        * then, the host starts providing clk at 1.8 and the host checks whether
        * DAT[3:0] is high after 1ms clk.
        *
        * For the above goal, temporarily disable the auto clk
        * and keep clk always on for 1ms.
        */
        cmd = RT_SDHCI_GET_CMD(rt_sdhci_readw(host, RT_SDHCI_COMMAND));

        if (cmd == VOLTAGE_SWITCH && host->mmc->ios.signal_voltage == MMC_SIGNAL_VOLTAGE_180)
        {
            /* Disable auto clock */
            k1x_sdhci_set_clk_gate(host, 0);
        }
    }
};

static void k1x_sdhci_phy_dll_init(struct rt_sdhci_host *host)
{
    rt_uint32_t reg;

    /* Config dll_reg1 & dll_reg2 */
    reg = rt_sdhci_readl(host, SDHC_PHY_DLLCFG);
    reg |= DLL_PREDLY_NUM | DLL_FULLDLY_RANGE | DLL_VREG_CTRL;
    rt_sdhci_writel(host, reg, SDHC_PHY_DLLCFG);

    reg = rt_sdhci_readl(host, SDHC_PHY_DLLCFG1);
    reg |= DLL_REG1_CTRL & DLL_REG1_CTRL_MASK;
    rt_sdhci_writel(host, reg, SDHC_PHY_DLLCFG1);

    /* Dll enable */
    reg = rt_sdhci_readl(host, SDHC_PHY_DLLCFG);
    reg |= DLL_ENABLE;
    rt_sdhci_writel(host, reg, SDHC_PHY_DLLCFG);

    /* Wait dll lock */
    for (int i = 0; i < 100; ++i)
    {
        if (rt_sdhci_readl(host, SDHC_PHY_DLLSTS) & DLL_LOCK_STATE)
        {
            break;
        }

        rt_hw_us_delay(10);
    }
}

static void k1x_sdhci_hs400_enhanced_strobe(struct rt_mmc_host *mmc, struct rt_mmcsd_io_cfg *ios)
{
    rt_uint32_t reg;
    struct rt_sdhci_host *host = rt_mmc_priv(mmc);

    reg = rt_sdhci_readl(host, SDHC_MMC_CTRL_REG);
    if (ios->enhanced_strobe)
    {
        reg |= ENHANCE_STROBE_EN;
    }
    else
    {
        reg &= ~ENHANCE_STROBE_EN;
    }
    rt_sdhci_writel(host, reg, SDHC_MMC_CTRL_REG);

    if (ios->enhanced_strobe)
    {
        k1x_sdhci_phy_dll_init(host);
    }
}

static int k1x_sdhci_start_signal_voltage_switch(struct rt_mmc_host *mmc, struct rt_mmcsd_io_cfg *ios)
{
    return rt_sdhci_start_signal_voltage_switch(mmc, ios);
}

static void k1x_sw_rx_tuning_prepare(struct rt_sdhci_host *host, rt_uint8_t dline_reg)
{
    rt_uint32_t reg;
    struct rt_mmc_host *mmc = host->mmc;
    struct rt_mmcsd_io_cfg ios = mmc->ios;

    reg = rt_sdhci_readl(host, SDHC_DLINE_CFG_REG);
    reg &= ~(RX_DLINE_REG_MASK << RX_DLINE_REG_SHIFT);
    reg |= dline_reg << RX_DLINE_REG_SHIFT;
    reg &= ~(RX_DLINE_GAIN_MASK << RX_DLINE_GAIN_SHIFT);
    if (ios.timing == MMC_TIMING_UHS_SDR50 && (reg & 0x40))
    {
        reg |= RX_DLINE_GAIN << RX_DLINE_GAIN_SHIFT;
    }
    rt_sdhci_writel(host, reg, SDHC_DLINE_CFG_REG);

    reg = rt_sdhci_readl(host, SDHC_DLINE_CTRL_REG);
    reg |= DLINE_PU;
    rt_sdhci_writel(host, reg, SDHC_DLINE_CTRL_REG);
    rt_hw_us_delay(5);

    reg = rt_sdhci_readl(host, SDHC_RX_CFG_REG);
    reg &= ~(RX_SDCLK_SEL1_MASK << RX_SDCLK_SEL1_SHIFT);
    reg |= RX_SDCLK_SEL1 << RX_SDCLK_SEL1_SHIFT;
    rt_sdhci_writel(host, reg, SDHC_RX_CFG_REG);

    if (mmc->ios.timing == MMC_TIMING_MMC_HS200)
    {
        reg = rt_sdhci_readl(host, SDHC_PHY_FUNC_REG);
        reg |= HS200_USE_RFIFO;
        rt_sdhci_writel(host, reg, SDHC_PHY_FUNC_REG);
    }
}

static void k1x_sw_rx_set_delaycode(struct rt_sdhci_host *host, rt_uint32_t delay)
{
    rt_uint32_t reg;

    reg = rt_sdhci_readl(host, SDHC_DLINE_CTRL_REG);
    reg &= ~(RX_DLINE_CODE_MASK << RX_DLINE_CODE_SHIFT);
    reg |= (delay & RX_DLINE_CODE_MASK) << RX_DLINE_CODE_SHIFT;
    rt_sdhci_writel(host, reg, SDHC_DLINE_CTRL_REG);
}

static void k1x_sw_tx_tuning_prepare(struct rt_sdhci_host *host)
{
    rt_uint32_t reg;

    /* Set TX_MUX_SEL */
    reg = rt_sdhci_readl(host, SDHC_TX_CFG_REG);
    reg |= TX_MUX_SEL;
    rt_sdhci_writel(host, reg, SDHC_TX_CFG_REG);

    reg = rt_sdhci_readl(host, SDHC_DLINE_CTRL_REG);
    reg |= DLINE_PU;
    rt_sdhci_writel(host, reg, SDHC_DLINE_CTRL_REG);

    rt_hw_us_delay(5);
}

static void k1x_sw_tx_set_dlinereg(struct rt_sdhci_host *host, rt_uint8_t dline_reg)
{
    rt_uint32_t reg;

    reg = rt_sdhci_readl(host, SDHC_DLINE_CFG_REG);
    reg &= ~(TX_DLINE_REG_MASK << TX_DLINE_REG_SHIFT);
    reg |= dline_reg << TX_DLINE_REG_SHIFT;
    rt_sdhci_writel(host, reg, SDHC_DLINE_CFG_REG);
}

static void k1x_sw_tx_set_delaycode(struct rt_sdhci_host *host, rt_uint32_t delay)
{
    rt_uint32_t reg;

    reg = rt_sdhci_readl(host, SDHC_DLINE_CTRL_REG);
    reg &= ~(TX_DLINE_CODE_MASK << TX_DLINE_CODE_SHIFT);
    reg |= (delay & TX_DLINE_CODE_MASK) << TX_DLINE_CODE_SHIFT;
    rt_sdhci_writel(host, reg, SDHC_DLINE_CTRL_REG);
}

static void k1x_sdhci_clear_set_irqs(struct rt_sdhci_host *host, rt_uint32_t clr, rt_uint32_t set)
{
    rt_uint32_t ier;

    ier = rt_sdhci_readl(host, RT_SDHCI_INT_ENABLE);
    ier &= ~clr;
    ier |= set;
    rt_sdhci_writel(host, ier, RT_SDHCI_INT_ENABLE);
    rt_sdhci_writel(host, ier, RT_SDHCI_SIGNAL_ENABLE);
}

static int k1x_tuning_patten_check(struct rt_sdhci_host *host, int point)
{
    int patten_len, err = 0;
    rt_uint32_t read_patten, *tuning_patten;

    if (host->mmc->ios.bus_width == MMC_BUS_WIDTH_8)
    {
        tuning_patten = (rt_uint32_t *)tuning_patten8;
        patten_len = RT_ARRAY_SIZE(tuning_patten8);
    }
    else
    {
        tuning_patten = (rt_uint32_t *)tuning_patten4;
        patten_len = RT_ARRAY_SIZE(tuning_patten4);
    }

    for (int i = 0; i < patten_len; ++i)
    {
        read_patten = rt_sdhci_readl(host, RT_SDHCI_BUFFER);
        if (read_patten != tuning_patten[i])
        {
            ++err;
        }
    }

    return err;
}

static int k1x_send_tuning_cmd(struct rt_sdhci_host *host, rt_uint32_t opcode,
        int point, rt_ubase_t level)
{
    int err = 0;

    rt_spin_unlock_irqrestore(&host->lock, level);

    rt_sdhci_send_tuning(host, opcode);

    level = rt_spin_lock_irqsave(&host->lock);

    if (!host->tuning_done)
    {
        LOG_E("Timeout waiting for Buffer Read Ready interrupt "
              "during tuning procedure, resetting CMD and DATA");
        rt_sdhci_reset(host, RT_SDHCI_RESET_CMD | RT_SDHCI_RESET_DATA);
    }
    else
    {
        err = k1x_tuning_patten_check(host, point);
    }

    host->tuning_done = 0;

    return err;
}

static int k1x_sw_rx_select_window(struct rt_sdhci_host *host, rt_uint32_t opcode)
{
    int err = 0, min, max;
    rt_uint16_t ctrl;
    rt_uint32_t ier;
    rt_ubase_t level = 0;
    struct tuning_window tmp;
    struct rt_mmc_host *mmc = host->mmc;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct k1x_sdhci *k1x = rt_sdhci_pltfm_priv(pltfm_host);
    struct k1x_sdhci_data *pdata = &k1x->pdata;
    struct rx_tuning *rxtuning = &pdata->rxtuning;

    /* Change to pio mode during the tuning stage */
    level = rt_spin_lock_irqsave(&host->lock);

    ier = rt_sdhci_readl(host, RT_SDHCI_INT_ENABLE);
    k1x_sdhci_clear_set_irqs(host, ier, RT_SDHCI_INT_DATA_AVAIL);

    min = SDHC_RX_TUNE_DELAY_MIN;
    do {
        /* Find the mininum delay first which can pass tuning */
        while (min < SDHC_RX_TUNE_DELAY_MAX)
        {
            k1x_sw_rx_set_delaycode(host, min);

            if (!mmc->ops->get_cd(mmc))
            {
                rt_spin_unlock_irqrestore(&host->lock, level);
                return -RT_EIO;
            }

            err = k1x_send_tuning_cmd(host, opcode, min, level);

            if (err == -RT_EIO)
            {
                rt_spin_unlock_irqrestore(&host->lock, level);
                return -RT_EIO;
            }

            if (!err)
            {
                break;
            }

            ctrl = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);
            ctrl &= ~(RT_SDHCI_CTRL_TUNED_CLK | RT_SDHCI_CTRL_EXEC_TUNING);
            rt_sdhci_writew(host, ctrl, RT_SDHCI_HOST_CONTROL2);
            min += SDHC_RX_TUNE_DELAY_STEP;
        }

        /* find the maxinum delay which can not pass tuning */
        max = min + SDHC_RX_TUNE_DELAY_STEP;

        while (max < SDHC_RX_TUNE_DELAY_MAX)
        {
            k1x_sw_rx_set_delaycode(host, max);
            if (!mmc->ops->get_cd(mmc))
            {
                rt_spin_unlock_irqrestore(&host->lock, level);
                return -RT_EIO;
            }

            if ((err = k1x_send_tuning_cmd(host, opcode, max, level)))
            {
                ctrl = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);
                ctrl &= ~(RT_SDHCI_CTRL_TUNED_CLK | RT_SDHCI_CTRL_EXEC_TUNING);
                rt_sdhci_writew(host, ctrl, RT_SDHCI_HOST_CONTROL2);

                if (err == -RT_EIO)
                {
                    rt_spin_unlock_irqrestore(&host->lock, level);
                    return -RT_EIO;
                }

                break;
            }
            max += SDHC_RX_TUNE_DELAY_STEP;
        }

        /* Store the top 3 window */
        if ((max - min) >= rxtuning->window_limit)
        {
            tmp.max_delay = max;
            tmp.min_delay = min;
            tmp.type = pdata->rxtuning.window_type;
            for (int i = 0; i < CANDIDATE_WIN_NUM; i++)
            {
                int len = rxtuning->windows[i].max_delay - rxtuning->windows[i].min_delay;

                if ((tmp.max_delay - tmp.min_delay) > len)
                {
                    for (int j = CANDIDATE_WIN_NUM - 1; j > i; j--)
                    {
                        rxtuning->windows[j] = rxtuning->windows[j-1];
                    }

                    rxtuning->windows[i] = tmp;
                    break;
                }
            }
        }

        min = max + SDHC_RX_TUNE_DELAY_STEP;
    } while (min < SDHC_RX_TUNE_DELAY_MAX);

    k1x_sdhci_clear_set_irqs(host, RT_SDHCI_INT_DATA_AVAIL, ier);
    rt_spin_unlock_irqrestore(&host->lock, level);

    return RT_EOK;
}

static int k1x_sw_rx_select_delay(struct rt_sdhci_host *host)
{
    int win_len, min, max, mid;
    struct tuning_window *window;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct k1x_sdhci *k1x = rt_sdhci_pltfm_priv(pltfm_host);
    struct k1x_sdhci_data *pdata = &k1x->pdata;
    struct rx_tuning *tuning = &pdata->rxtuning;

    for (int i = 0; i < CANDIDATE_WIN_NUM; ++i)
    {
        window = &tuning->windows[i];
        min = window->min_delay;
        max = window->max_delay;
        mid = (min + max - 1) / 2;
        win_len = max - min;

        if (win_len < tuning->window_limit)
        {
            continue;
        }

        if (window->type == LEFT_WINDOW)
        {
            tuning->select_delay[tuning->select_delay_num++] = min + win_len / 4;
            tuning->select_delay[tuning->select_delay_num++] = min + win_len / 3;
        }
        else if (window->type == RIGHT_WINDOW)
        {
            tuning->select_delay[tuning->select_delay_num++] = max - win_len / 4;
            tuning->select_delay[tuning->select_delay_num++] = max - win_len / 3;
        }
        else
        {
            tuning->select_delay[tuning->select_delay_num++] = mid;
            tuning->select_delay[tuning->select_delay_num++] = mid + win_len / 4;
            tuning->select_delay[tuning->select_delay_num++] = mid - win_len / 4;
        }
    }

    return tuning->select_delay_num;
}

static unsigned int k1x_sdhci_clk_get_max_clock(struct rt_sdhci_host *host)
{
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);

    return rt_clk_get_rate(pltfm_host->clk);
}

static unsigned int k1x_get_max_timeout_count(struct rt_sdhci_host *host)
{
    /*
     * The default sdhci code use the 1 << 27 as the max timeout counter
     * to calculate the max_busy_timeout.
     * aquilac sdhci support 1 << 29 as the timeout counter.
     */
    return 1 << 29;
}

static void k1x_sdhci_reset(struct rt_sdhci_host *host, rt_uint8_t mask)
{
    rt_uint32_t reg;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct k1x_sdhci *k1x = rt_sdhci_pltfm_priv(pltfm_host);
    struct k1x_sdhci_data *pdata = &k1x->pdata;

    rt_sdhci_reset(host, mask);

    if (mask != RT_SDHCI_RESET_ALL)
    {
        return;
    }

    reg = rt_sdhci_readl(host, SDHC_PHY_CTRL_REG);
    reg |= (PHY_FUNC_EN | PHY_PLL_LOCK);
    rt_sdhci_writel(host, reg, SDHC_PHY_CTRL_REG);

    reg = rt_sdhci_readl(host, SDHC_PHY_PADCFG_REG);
    reg |= (1 << RX_BIAS_CTRL_SHIFT);

    reg &= ~(PHY_DRIVE_SEL_MASK);
    reg |= (pdata->phy_driver_sel & PHY_DRIVE_SEL_MASK) << PHY_DRIVE_SEL_SHIFT;
    rt_sdhci_writel(host, reg, SDHC_PHY_PADCFG_REG);

    /* For EMMC */
    if (!(host->mmc->caps2 & MMC_CAP2_NO_MMC))
    {
        /* MMC card mode */
        reg = rt_sdhci_readl(host, SDHC_MMC_CTRL_REG);
        reg |= MMC_CARD_MODE;
        rt_sdhci_writel(host, reg, SDHC_MMC_CTRL_REG);
    }
}

static void k1x_sdhci_set_uhs_signaling(struct rt_sdhci_host *host, unsigned timing)
{
    rt_uint16_t reg;

    if (timing == MMC_TIMING_MMC_HS200 || timing == MMC_TIMING_MMC_HS400)
    {
        reg = rt_sdhci_readw(host, SDHC_MMC_CTRL_REG);
        reg |= (timing == MMC_TIMING_MMC_HS200) ? MMC_HS200 : MMC_HS400;
        rt_sdhci_writew(host, reg, SDHC_MMC_CTRL_REG);
    }

    rt_sdhci_set_uhs(host, timing);

    if (!(host->mmc->caps2 & MMC_CAP2_NO_SDIO))
    {
        reg = rt_sdhci_readw(host, RT_SDHCI_HOST_CONTROL2);
        rt_sdhci_writew(host, reg | RT_SDHCI_CTRL_VDD_180, RT_SDHCI_HOST_CONTROL2);
    }
}

static int k1x_sdhci_execute_sw_tuning(struct rt_sdhci_host *host, rt_uint32_t opcode)
{
    struct rt_mmc_host *mmc = host->mmc;
    struct rt_mmcsd_io_cfg ios = mmc->ios;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct k1x_sdhci *k1x = rt_sdhci_pltfm_priv(pltfm_host);
    struct k1x_sdhci_data *pdata = &k1x->pdata;
    struct rx_tuning *rxtuning = &pdata->rxtuning;

    /*
     * Tuning is required for SDR50/SDR104, HS200/HS400 cards and
     * if clock frequency is greater than 100MHz in these modes.
     */
    if (host->clock < 100 * 1000 * 1000 ||
        !((ios.timing == MMC_TIMING_MMC_HS200) ||
          (ios.timing == MMC_TIMING_UHS_SDR50) ||
          (ios.timing == MMC_TIMING_UHS_SDR104)))
    {
        return 0;
    }

    if (!(mmc->caps2 & MMC_CAP2_NO_SD) && !mmc->ops->get_cd(mmc))
    {
        return 0;
    }

    /* TX tuning config */
    if (host->mmc->caps2 & MMC_CAP2_NO_MMC)
    {
        k1x_sw_tx_set_dlinereg(host, pdata->tx_dline_reg);
        k1x_sw_tx_set_delaycode(host, pdata->tx_delaycode);
        k1x_sw_tx_tuning_prepare(host);
    }

    rxtuning->select_delay_num = 0;
    rxtuning->current_delay_index = 0;
    rt_memset(rxtuning->windows, 0, sizeof(rxtuning->windows));
    rt_memset(rxtuning->select_delay, 0xFF, sizeof(rxtuning->select_delay));
    rt_memset(rxtuning->card_cid, 0, sizeof(rxtuning->card_cid));

    /* Get pass window and caculate the select_delay */
    k1x_sw_rx_tuning_prepare(host, rxtuning->rx_dline_reg);

    if (k1x_sw_rx_select_window(host, opcode))
    {
        rxtuning->tuning_fail = 1;
        return -RT_EIO;
    }

    if (!k1x_sw_rx_select_delay(host))
    {
        rxtuning->tuning_fail = 1;
        return -RT_EIO;
    }

    /* Set the delay code and store card cid */
    k1x_sw_rx_set_delaycode(host, rxtuning->select_delay[0]);
    rxtuning->tuning_fail = 0;

    return 0;
}

static rt_uint32_t k1x_handle_interrupt(struct rt_sdhci_host *host, rt_uint32_t intmask)
{
    /* Handle sdio RT_SDHCI_INT_CARD_INT */
    if ((intmask & RT_SDHCI_INT_CARD_INT) && (host->ier & RT_SDHCI_INT_CARD_INT))
    {
        if (!(host->flags & RT_SDHCI_DEVICE_DEAD))
        {
            host->ier &= ~RT_SDHCI_INT_CARD_INT;
            rt_sdhci_writel(host, host->ier, RT_SDHCI_INT_ENABLE);
            rt_sdhci_writel(host, host->ier, RT_SDHCI_SIGNAL_ENABLE);
        }

        /* Wakeup ksdioirqd thread */
        host->mmc->sdio_irq_pending = RT_TRUE;
        if (host->mmc->rthost.sdio_irq_thread)
        {
            rt_thread_resume(host->mmc->rthost.sdio_irq_thread);
        }
    }

    /* Handle error interrupts */
    if (intmask & RT_SDHCI_INT_ERROR)
    {
        if (intmask & (RT_SDHCI_INT_CRC | RT_SDHCI_INT_DATA_CRC | RT_SDHCI_INT_DATA_END_BIT | RT_SDHCI_INT_AUTO_CMD_ERR))
        {
            /* Handle crc error for sd device */
            if (host->mmc->caps2 & MMC_CAP2_NO_MMC)
            {
                host->mmc->caps2 |= MMC_CAP2_QUIRK_BREAK_SDR104;
            }
        }
    }

    return intmask;
}

static void k1x_set_aib_mmc1_io(struct rt_sdhci_host *host, int signal_voltage)
{
    void *aib_mmc1_io = RT_NULL;
    void *apbc_asfar = RT_NULL;
    void *apbc_assar = RT_NULL;
    rt_uint32_t reg;
    struct rt_sdhci_pltfm_host *pltfm_host = rt_sdhci_priv(host);
    struct k1x_sdhci *k1x = rt_sdhci_pltfm_priv(pltfm_host);
    struct k1x_sdhci_data *pdata = &k1x->pdata;

    if (!pdata->aib_mmc1_io_reg || !pdata->apbc_asfar_reg ||
            !pdata->apbc_assar_reg)
    {
        return;
    }

    aib_mmc1_io = rt_ioremap((void *)(rt_ubase_t)pdata->aib_mmc1_io_reg, 4);
    apbc_asfar = rt_ioremap((void *)(rt_ubase_t)pdata->apbc_asfar_reg, 4);
    apbc_assar = rt_ioremap((void *)(rt_ubase_t)pdata->apbc_assar_reg, 4);
    if (!aib_mmc1_io || !apbc_asfar || !apbc_assar)
    {
        LOG_E("Map AIB voltage control registers failed");
        goto _unmap;
    }

    HWREG32(apbc_asfar) = AKEY_ASFAR;
    HWREG32(apbc_assar) = AKEY_ASSAR;
    reg = HWREG32(aib_mmc1_io);

    if (signal_voltage == MMC_SIGNAL_VOLTAGE_180)
    {
        reg |= MMC1_IO_V18EN;
    }
    else
    {
        reg &= ~MMC1_IO_V18EN;
    }

    HWREG32(apbc_asfar) = AKEY_ASFAR;
    HWREG32(apbc_assar) = AKEY_ASSAR;
    HWREG32(aib_mmc1_io) = reg;
    rt_hw_dsb();

_unmap:
    if (apbc_assar)
    {
        rt_iounmap(apbc_assar);
    }
    if (apbc_asfar)
    {
        rt_iounmap(apbc_asfar);
    }
    if (aib_mmc1_io)
    {
        rt_iounmap(aib_mmc1_io);
    }
}

static void k1x_sdhci_voltage_switch(struct rt_sdhci_host *host)
{
    if (host->quirks2 & RT_SDHCI_QUIRK2_SET_AIB_MMC)
    {
        k1x_set_aib_mmc1_io(host, host->mmc->rthost.io_cfg.signal_voltage);
    }
}

static const struct rt_sdhci_ops k1x_sdhci_ops =
{
    .set_clock = k1x_sdhci_set_clock,
    .get_max_clock = k1x_sdhci_clk_get_max_clock,
    .get_max_timeout_count = k1x_get_max_timeout_count,
    .set_bus_width = rt_sdhci_set_bus_width,
    .reset = k1x_sdhci_reset,
    .set_uhs_signaling = k1x_sdhci_set_uhs_signaling,
    .platform_execute_tuning = k1x_sdhci_execute_sw_tuning,
    .irq = k1x_handle_interrupt,
    .set_power = rt_sdhci_set_power_and_bus_voltage,
    .voltage_switch = k1x_sdhci_voltage_switch,
};

static int k1x_sdhci_pre_select_hs400(struct rt_mmc_host *mmc)
{
    rt_uint32_t reg;
    struct rt_sdhci_host *host = rt_mmc_priv(mmc);

    reg = rt_sdhci_readl(host, SDHC_MMC_CTRL_REG);
    reg |= MMC_HS400;
    rt_sdhci_writel(host, reg, SDHC_MMC_CTRL_REG);

    return RT_EOK;
}

static void k1x_sdhci_post_select_hs400(struct rt_mmc_host *mmc)
{
    struct rt_sdhci_host *host = rt_mmc_priv(mmc);

    k1x_sdhci_phy_dll_init(host);
}

static void k1x_sdhci_pre_hs400_to_hs200(struct rt_mmc_host *mmc)
{
    rt_uint32_t reg;
    struct rt_sdhci_host *host = rt_mmc_priv(mmc);

    reg = rt_sdhci_readl(host, SDHC_PHY_CTRL_REG);
    reg &= ~(PHY_FUNC_EN | PHY_PLL_LOCK);
    rt_sdhci_writel(host, reg, SDHC_PHY_CTRL_REG);

    reg = rt_sdhci_readl(host, SDHC_MMC_CTRL_REG);
    reg &= ~(MMC_HS400 | MMC_HS200 | ENHANCE_STROBE_EN);
    rt_sdhci_writel(host, reg, SDHC_MMC_CTRL_REG);

    reg = rt_sdhci_readl(host, SDHC_PHY_FUNC_REG);
    reg &= ~HS200_USE_RFIFO;
    rt_sdhci_writel(host, reg, SDHC_PHY_FUNC_REG);

    rt_hw_us_delay(5);

    reg = rt_sdhci_readl(host, SDHC_PHY_CTRL_REG);
    reg |= PHY_FUNC_EN | PHY_PLL_LOCK;
    rt_sdhci_writel(host, reg, SDHC_PHY_CTRL_REG);
}

static struct rt_sdhci_pltfm_data sdhci_k1x_pdata =
{
    .ops = &k1x_sdhci_ops,
    .quirks = RT_SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK
            | RT_SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC
            | RT_SDHCI_QUIRK_32BIT_ADMA_SIZE
            | RT_SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
    .quirks2 = RT_SDHCI_QUIRK2_BROKEN_64_BIT_DMA,
};

static void k1x_sdhci_request(struct rt_mmc_host *mmc,
        struct rt_mmcsd_req *mrq)
{
    struct rt_mmcsd_data *data = mrq->data;
    void *original, *bounce;
    rt_size_t length, alloc_length;

    if (!data || !data->buf)
    {
        rt_sdhci_start_request(mmc, mrq);
        return;
    }

    length = data->blks * data->blksize;
    if (!(((rt_ubase_t)data->buf | length) & (RT_CPU_CACHE_LINE_SZ - 1)))
    {
        rt_sdhci_start_request(mmc, mrq);
        return;
    }

    alloc_length = RT_ALIGN(length, RT_CPU_CACHE_LINE_SZ);
    bounce = rt_malloc_align(alloc_length, RT_CPU_CACHE_LINE_SZ);
    if (!bounce)
    {
        mrq->cmd->err = -RT_ENOMEM;
        data->err = -RT_ENOMEM;
        rt_mmc_request_done(mmc, mrq);
        return;
    }

    original = data->buf;
    if (data->flags & DATA_DIR_WRITE)
    {
        rt_memcpy(bounce, original, length);
    }
    else
    {
        rt_memset(bounce, 0, alloc_length);
    }

    data->buf = bounce;
    rt_sdhci_start_request(mmc, mrq);
    rt_sem_take(&mmc->rthost.sem_ack, RT_WAITING_FOREVER);

    if ((data->flags & DATA_DIR_READ) && !mrq->cmd->err && !data->err)
    {
        rt_memcpy(original, bounce, length);
    }

    data->buf = original;
    rt_free_align(bounce);

    /* Pass the completion consumed above back to mmcsd_send_request(). */
    rt_sem_release(&mmc->rthost.sem_ack);
}

#ifdef RT_USING_PM
static rt_err_t k1x_sdhci_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    rt_uint32_t reg;
    rt_ubase_t level;
    struct k1x_sdhci *k1x = device->user_data;
    struct rt_sdhci_host *host = k1x->host;

    level = rt_spin_lock_irqsave(&host->lock);
    host->runtime_suspended = RT_TRUE;
    if (!(host->mmc->caps2 & MMC_CAP2_NO_MMC))
    {
        reg = rt_sdhci_readl(host, SDHC_PHY_CTRL_REG);
        reg &= ~PHY_FUNC_EN;
        rt_sdhci_writel(host, reg, SDHC_PHY_CTRL_REG);
    }
    rt_spin_unlock_irqrestore(&host->lock, level);

    rt_clk_disable_unprepare(k1x->clk_io);

    if (!rt_is_err(k1x->clk_aib))
    {
        rt_clk_disable_unprepare(k1x->clk_aib);
    }

    if (!rt_is_err(k1x->clk_core))
    {
        rt_clk_disable_unprepare(k1x->clk_core);
    }

    return RT_EOK;
}

static void k1x_sdhci_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    rt_uint32_t reg;
    rt_ubase_t level;
    struct k1x_sdhci *k1x = device->user_data;
    struct rt_sdhci_host *host = k1x->host;

    rt_clk_prepare_enable(k1x->clk_io);

    if (!rt_is_err(k1x->clk_aib))
    {
        rt_clk_prepare_enable(k1x->clk_aib);
    }
    if (!rt_is_err(k1x->clk_core))
    {
        rt_clk_prepare_enable(k1x->clk_core);
    }

    level = rt_spin_lock_irqsave(&host->lock);
    if (!(host->mmc->caps2 & MMC_CAP2_NO_MMC))
    {
        reg = rt_sdhci_readl(host, SDHC_PHY_CTRL_REG);
        reg |= PHY_FUNC_EN;
        rt_sdhci_writel(host, reg, SDHC_PHY_CTRL_REG);
    }
    host->runtime_suspended = RT_FALSE;
    rt_spin_unlock_irqrestore(&host->lock, level);
}

static const struct rt_device_pm_ops k1x_sdhci_pm_ops =
{
    .suspend = k1x_sdhci_pm_suspend,
    .resume = k1x_sdhci_pm_resume,
};
#endif /* RT_USING_PM */

static rt_err_t k1x_sdhci_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t val;
    struct k1x_sdhci *k1x;
    struct k1x_sdhci_data *pdata;
    struct rt_sdhci_host *host;
    struct rt_sdhci_pltfm_host *pltfm_host;
    struct rt_device *dev = &pdev->parent;

    host = rt_sdhci_pltfm_init(pdev, &sdhci_k1x_pdata, sizeof(*k1x));
    if (!host)
    {
        return -RT_ERROR;
    }

    pltfm_host = rt_sdhci_priv(host);
    k1x = rt_sdhci_pltfm_priv(pltfm_host);
    pdata = &k1x->pdata;

    k1x->clk_io = rt_clk_get_by_name(dev, "sdh-io");
    if (rt_is_err(k1x->clk_io))
    {
        k1x->clk_io = rt_clk_get_by_index(dev, 0);
    }
    if (rt_is_err(k1x->clk_io))
    {
        err = rt_ptr_err(k1x->clk_io);
        goto _fail;
    }
    pltfm_host->clk = k1x->clk_io;

    if ((err = rt_clk_prepare_enable(k1x->clk_io)))
    {
        goto _free_clk_io;
    }

    k1x->clk_core = rt_clk_get_by_name(dev, "sdh-core");
    if (!rt_is_err(k1x->clk_core))
    {
        if ((err = rt_clk_prepare_enable(k1x->clk_core)))
        {
            goto _free_clk_core;
        }
    }

    k1x->clk_aib = rt_clk_get_by_name(dev, "aib-clk");
    if (!rt_is_err(k1x->clk_aib))
    {
        if ((err = rt_clk_prepare_enable(k1x->clk_aib)))
        {
            goto _free_clk_aib;
        }
    }

    k1x->rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(k1x->rstc))
    {
        err = rt_ptr_err(k1x->rstc);
        goto _free_clk_aib;
    }

    if ((err = rt_reset_control_deassert(k1x->rstc)))
    {
        goto _err_rst_get;
    }

    if ((err = rt_mmc_of_parse(host->mmc)))
    {
        goto _err_rst_deassert;
    }

    /* rt_mmc_of_parse() does not currently import this standard property. */
    if (rt_dm_dev_prop_read_bool(dev, "no-mmc"))
    {
        host->mmc->caps2 |= MMC_CAP2_NO_MMC;
    }

    rt_sdhci_get_property(pdev);

    /* SDH io clk */
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,sdh-freq", &val))
    {
        pdata->host_freq = val;
    }
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,sdh-flags", &val))
    {
        pdata->flags |= val;
    }
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,sdh-host-caps", &val))
    {
        pdata->host_caps |= val;
    }
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,sdh-host-caps2", &val))
    {
        pdata->host_caps2 |= val;
    }
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,sdh-host-caps-disable", &val))
    {
        pdata->host_caps_disable |= val;
    }
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,sdh-host-caps2-disable", &val))
    {
        pdata->host_caps2_disable |= val;
    }
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,sdh-quirks", &val))
    {
        pdata->quirks |= val;
    }
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,sdh-quirks2", &val))
    {
        pdata->quirks2 |= val;
    }
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,aib_mmc1_io_reg", &val))
    {
        pdata->aib_mmc1_io_reg = val;
    }
    else
    {
        pdata->aib_mmc1_io_reg = 0x0;
    }
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,apbc_asfar_reg", &val))
    {
        pdata->apbc_asfar_reg = val;
    }
    else
    {
        pdata->apbc_asfar_reg = 0x0;
    }
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,apbc_assar_reg", &val))
    {
        pdata->apbc_assar_reg = val;
    }
    else
    {
        pdata->apbc_assar_reg = 0x0;
    }
    /* Read rx tuning dline_reg */
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,rx_dline_reg", &val))
    {
        pdata->rxtuning.rx_dline_reg = (rt_uint8_t)val;
    }
    else
    {
        pdata->rxtuning.rx_dline_reg = RX_TUNING_DLINE_REG;
    }
    /* Read rx tuning window limit */
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,rx_tuning_limit", &val))
    {
        pdata->rxtuning.window_limit = (rt_uint8_t)val;
    }
    else
    {
        pdata->rxtuning.window_limit = RX_TUNING_WINDOW_THRESHOLD;
    }
    /* Read rx tuning window type */
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,rx_tuning_type", &val))
    {
        pdata->rxtuning.window_type = (rt_uint8_t)val;
    }
    else
    {
        pdata->rxtuning.window_type = MIDDLE_WINDOW;
    }
    /* TX tuning dline_reg */
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,tx_dline_reg", &val))
    {
        pdata->tx_dline_reg = (rt_uint8_t)val;
    }
    else
    {
        pdata->tx_dline_reg = TX_TUNING_DLINE_REG;
    }
    rt_uint32_t tx_delaycode_array[RT_ARRAY_SIZE(pdata->tx_delaycode_array)];
    int tx_delaycode_cnt = rt_dm_dev_prop_count_of_size(dev,
            "spacemit,tx_delaycode", sizeof(rt_uint32_t));

    if (tx_delaycode_cnt > 0)
    {
        if (tx_delaycode_cnt > RT_ARRAY_SIZE(pdata->tx_delaycode_array))
        {
            tx_delaycode_cnt = RT_ARRAY_SIZE(pdata->tx_delaycode_array);
        }

        if (rt_dm_dev_prop_read_u32_array_index(dev, "spacemit,tx_delaycode",
                0, tx_delaycode_cnt, tx_delaycode_array) == tx_delaycode_cnt)
        {
            for (int i = 0; i < tx_delaycode_cnt; ++i)
            {
                pdata->tx_delaycode_array[i] = tx_delaycode_array[i];
            }
            pdata->tx_delaycode_cnt = tx_delaycode_cnt;
            pdata->tx_delaycode = pdata->tx_delaycode_array[0];
        }
        else
        {
            pdata->tx_delaycode_array[0] = TX_TUNING_DELAYCODE;
            pdata->tx_delaycode_cnt = 1;
            pdata->tx_delaycode = pdata->tx_delaycode_array[0];
        }
    }
    else
    {
        pdata->tx_delaycode_array[0] = TX_TUNING_DELAYCODE;
        pdata->tx_delaycode_cnt = 1;
        pdata->tx_delaycode = pdata->tx_delaycode_array[0];
    }
    /* PHY driver select */
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,phy_driver_sel", &val))
    {
        pdata->phy_driver_sel = (rt_uint8_t)val;
    }
    else
    {
        pdata->phy_driver_sel = PHY_DRIVE_SEL_DEFAULT;
    }
    /* Read rx tuning cpufreq, unit 1000Hz */
    if (!rt_dm_dev_prop_read_u32(dev, "spacemit,rx_tuning_freq", &val))
    {
        pdata->rx_tuning_freq = val;
    }

    if (pdata->quirks)
    {
        host->quirks |= pdata->quirks;
    }
    if (pdata->quirks2)
    {
        host->quirks2 |= pdata->quirks2;
    }
    if (pdata->host_caps)
    {
        host->mmc->caps |= pdata->host_caps;
    }
    if (pdata->host_caps2)
    {
        host->mmc->caps2 |= pdata->host_caps2;
    }
    if (pdata->pm_caps)
    {
        host->mmc->pm_caps |= pdata->pm_caps;
    }

    if (!(host->mmc->caps2 & MMC_CAP2_NO_MMC))
    {
        host->mmc_host_ops.hs400_prepare_ddr = k1x_sdhci_pre_select_hs400;
        host->mmc_host_ops.hs400_complete = k1x_sdhci_post_select_hs400;
        host->mmc_host_ops.hs400_downgrade = k1x_sdhci_pre_hs400_to_hs200;
        if (host->mmc->caps2 & MMC_CAP2_HS400_ES)
        {
            host->mmc_host_ops.hs400_enhanced_strobe = k1x_sdhci_hs400_enhanced_strobe;
        }
    }

    if (host->mmc->caps2 & MMC_CAP2_NO_MMC)
    {
        /* Break sdr104 */
        if (host->mmc->caps2 & MMC_CAP2_QUIRK_BREAK_SDR104)
        {
            host->mmc->caps &= ~MMC_CAP_UHS_SDR104;
            host->mmc->caps2 &= ~MMC_CAP2_QUIRK_BREAK_SDR104;
        }
        else
        {
            if (pdata->rxtuning.tuning_fail)
            {
                /* Fallback bus speed */
                host->mmc->caps &= ~MMC_CAP_UHS_SDR104;
                pdata->rxtuning.tuning_fail = 0;
            }
            else if (!(pdata->host_caps_disable & MMC_CAP_UHS_SDR104) &&
                    !(host->quirks2 & RT_SDHCI_QUIRK2_NO_1_8_V))
            {
                /* Recovery sdr104 capability */
                host->mmc->caps |= MMC_CAP_UHS_SDR104;
            }
        }
    }

    if (!(host->mmc->caps2 & MMC_CAP2_NO_SDIO))
    {
        /* Disable MMC_CAP2_SDIO_IRQ_NOTHREAD */
        host->mmc->caps2 &= ~MMC_CAP2_SDIO_IRQ_NOTHREAD;

        /*
         * Use the fake irq pending to avoid to read the SDIO_CCCR_INTx
         * which sometimes return an abnormal value.
         */
        host->mmc->sdio_irq_pending = RT_TRUE;
    }

    host->mmc_host_ops.request = k1x_sdhci_request;
    host->mmc_host_ops.start_signal_voltage_switch = k1x_sdhci_start_signal_voltage_switch;
    host->mmc_host_ops.card_busy = k1x_sdhci_card_busy;
    host->mmc_host_ops.enable_sdio_irq = k1x_enable_sdio_irq;

    /* Set IO clock rate */
    if (pdata->host_freq)
    {
        if ((err = rt_clk_set_rate(k1x->clk_io, pdata->host_freq)))
        {
            goto _fail;
        }
    }
    else
    {
        goto _fail;
    }

    if ((err = rt_sdhci_set_and_add_host(host)))
    {
        goto _fail;
    }

    if (pdata->host_caps_disable)
    {
        host->mmc->caps &= ~pdata->host_caps_disable;
    }
    if (pdata->host_caps2_disable)
    {
        host->mmc->caps2 &= ~pdata->host_caps2_disable;
    }

    if (host->mmc->caps2 & MMC_CAP2_NO_MMC)
    {
        k1x->pinctrl = RT_TRUE;
    }

    dev->user_data = k1x;

#ifdef RT_USING_PM
    rt_pm_device_register(dev, &k1x_sdhci_pm_ops);
#endif

    return RT_EOK;

_err_rst_deassert:
    rt_reset_control_assert(k1x->rstc);

_err_rst_get:
    rt_reset_control_put(k1x->rstc);
    k1x->rstc = RT_NULL;

    if (!rt_is_err(k1x->clk_aib))
    {
        rt_clk_disable_unprepare(k1x->clk_aib);
    }

_free_clk_aib:
    if (!rt_is_err(k1x->clk_aib))
    {
        rt_clk_put(k1x->clk_aib);
    }
    k1x->clk_aib = RT_NULL;

    if (!rt_is_err(k1x->clk_core))
    {
        rt_clk_disable_unprepare(k1x->clk_core);
    }

_free_clk_core:
    if (!rt_is_err(k1x->clk_core))
    {
        rt_clk_put(k1x->clk_core);
    }
    k1x->clk_core = RT_NULL;

    rt_clk_disable_unprepare(k1x->clk_io);

_free_clk_io:
    rt_clk_put(k1x->clk_io);
    k1x->clk_io = RT_NULL;

_fail:
    rt_sdhci_pltfm_free(pdev);

    return err;
}

static rt_err_t k1x_sdhci_remove(struct rt_platform_device *pdev)
{
    struct rt_sdhci_pltfm_host *pltfm_host;
    struct k1x_sdhci *k1x = pdev->parent.user_data;

#ifdef RT_USING_PM
    rt_pm_device_unregister(&pdev->parent);
#endif

    pltfm_host = rt_sdhci_priv(k1x->host);
    pltfm_host->clk = RT_NULL;

    rt_reset_control_assert(k1x->rstc);

    rt_clk_disable_unprepare(k1x->clk_aib);
    rt_clk_disable_unprepare(k1x->clk_io);
    rt_clk_disable_unprepare(k1x->clk_core);

    rt_reset_control_put(k1x->rstc);
    rt_clk_put(k1x->clk_aib);
    rt_clk_put(k1x->clk_io);
    rt_clk_put(k1x->clk_core);

    return rt_sdhci_pltfm_remove(pdev);
}

static const struct rt_ofw_node_id k1x_sdhci_ofw_ids[] =
{
    { .compatible = "spacemit,k1-x-sdhci" },
    { /* sentinel */ }
};

static struct rt_platform_driver k1x_sdhci_driver =
{
    .name = "sdhci-iproc",
    .ids = k1x_sdhci_ofw_ids,

    .probe = k1x_sdhci_probe,
    .remove = k1x_sdhci_remove,
};
RT_PLATFORM_DRIVER_EXPORT(k1x_sdhci_driver);
