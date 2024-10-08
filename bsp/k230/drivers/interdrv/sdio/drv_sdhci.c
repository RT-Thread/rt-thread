/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-10     Tanek        first version
 * 2021-07-07     linzhenxing  add sd card drivers in mmu
 * 2021-07-14     linzhenxing  add emmc
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_sdhci.h"
#include "riscv_io.h"
#include <string.h>
#include <ioremap.h>
#include <cache.h>

#ifdef RT_USING_SDIO

#define DBG_TAG "drv_sdhci"
#ifdef RT_SDIO_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_WARNING
#endif /* RT_SDIO_DEBUG */
#include <rtdbg.h>

#if defined(BSP_USING_SDIO0) || defined(BSP_USING_SDIO1)

#define SDHCI_SDMA_ENABLE
#define CACHE_LINESIZE (64)

#define BIT(x) (1 << x)
#define DWC_MSHC_PTR_VENDOR1 0x500
#define MSHC_CTRL_R (DWC_MSHC_PTR_VENDOR1 + 0x08)
#define EMMC_CTRL_R (DWC_MSHC_PTR_VENDOR1 + 0x2c)
#define SDHCI_VENDER_AT_CTRL_REG (DWC_MSHC_PTR_VENDOR1 + 0x40)
#define SDHCI_VENDER_AT_STAT_REG (DWC_MSHC_PTR_VENDOR1 + 0x44)
#define SDHCI_TUNE_CLK_STOP_EN_MASK BIT(16)
#define SDHCI_TUNE_SWIN_TH_VAL_LSB (24)
#define SDHCI_TUNE_SWIN_TH_VAL_MASK (0xFF)
#define CARD_IS_EMMC 0
#define EMMC_RST_N 2
#define EMMC_RST_N_OE 3

#define DWC_MSHC_PTR_PHY_REGS 0x300
#define DWC_MSHC_PHY_CNFG (DWC_MSHC_PTR_PHY_REGS + 0x0)
#define PAD_SN_LSB 20
#define PAD_SN_MASK 0xF
#define PAD_SN_DEFAULT ((0x8 & PAD_SN_MASK) << PAD_SN_LSB)
#define PAD_SP_LSB 16
#define PAD_SP_MASK 0xF
#define PAD_SP_DEFAULT ((0x9 & PAD_SP_MASK) << PAD_SP_LSB)
#define PHY_PWRGOOD BIT(1)
#define PHY_RSTN BIT(0)

#define DWC_MSHC_CMDPAD_CNFG (DWC_MSHC_PTR_PHY_REGS + 0x4)
#define DWC_MSHC_DATPAD_CNFG (DWC_MSHC_PTR_PHY_REGS + 0x6)
#define DWC_MSHC_CLKPAD_CNFG (DWC_MSHC_PTR_PHY_REGS + 0x8)
#define DWC_MSHC_STBPAD_CNFG (DWC_MSHC_PTR_PHY_REGS + 0xA)
#define DWC_MSHC_RSTNPAD_CNFG (DWC_MSHC_PTR_PHY_REGS + 0xC)
#define TXSLEW_N_LSB 9
#define TXSLEW_N_MASK 0xF
#define TXSLEW_P_LSB 5
#define TXSLEW_P_MASK 0xF
#define WEAKPULL_EN_LSB 3
#define WEAKPULL_EN_MASK 0x3
#define RXSEL_LSB 0
#define RXSEL_MASK 0x3

#define DWC_MSHC_COMMDL_CNFG (DWC_MSHC_PTR_PHY_REGS + 0x1C)
#define DWC_MSHC_SDCLKDL_CNFG (DWC_MSHC_PTR_PHY_REGS + 0x1D)
#define DWC_MSHC_SDCLKDL_DC (DWC_MSHC_PTR_PHY_REGS + 0x1E)
#define DWC_MSHC_SMPLDL_CNFG (DWC_MSHC_PTR_PHY_REGS + 0x20)
#define DWC_MSHC_ATDL_CNFG (DWC_MSHC_PTR_PHY_REGS + 0x21)

#define DWC_MSHC_PHY_PAD_SD_CLK \
    ((1 << TXSLEW_N_LSB) | (3 << TXSLEW_P_LSB) | (0 << WEAKPULL_EN_LSB) | (2 << RXSEL_LSB))
#define DWC_MSHC_PHY_PAD_SD_DAT \
    ((1 << TXSLEW_N_LSB) | (3 << TXSLEW_P_LSB) | (1 << WEAKPULL_EN_LSB) | (2 << RXSEL_LSB))
#define DWC_MSHC_PHY_PAD_SD_STB \
    ((1 << TXSLEW_N_LSB) | (3 << TXSLEW_P_LSB) | (2 << WEAKPULL_EN_LSB) | (2 << RXSEL_LSB))
#define DWC_MSHC_PHY_PAD_EMMC_CLK \
    ((2 << TXSLEW_N_LSB) | (2 << TXSLEW_P_LSB) | (0 << WEAKPULL_EN_LSB) | (1 << RXSEL_LSB))
#define DWC_MSHC_PHY_PAD_EMMC_DAT \
    ((2 << TXSLEW_N_LSB) | (2 << TXSLEW_P_LSB) | (1 << WEAKPULL_EN_LSB) | (1 << RXSEL_LSB))
#define DWC_MSHC_PHY_PAD_EMMC_STB \
    ((2 << TXSLEW_N_LSB) | (2 << TXSLEW_P_LSB) | (2 << WEAKPULL_EN_LSB) | (1 << RXSEL_LSB))

static struct sdhci_host* sdhci_host0;
static struct sdhci_host* sdhci_host1;

static inline void sdhci_writel(struct sdhci_host* host, uint32_t val, int reg)
{
    writel(val, (void*)host->mapbase + reg);
}

static inline void sdhci_writew(struct sdhci_host* host, uint16_t val, int reg)
{
    writew((uint16_t)val, (void*)host->mapbase + reg);
}

static inline void sdhci_writeb(struct sdhci_host* host, uint8_t val, int reg)
{
    writeb((uint8_t)val, (void*)host->mapbase + reg);
}

static inline uint32_t sdhci_readl(struct sdhci_host* host, int reg)
{
    return (uint32_t)readl((void*)host->mapbase + reg);
}

static inline uint16_t sdhci_readw(struct sdhci_host* host, int reg)
{
    return (uint16_t)readw((void*)host->mapbase + reg);
}

static inline uint8_t sdhci_readb(struct sdhci_host* host, int reg)
{
    return (uint8_t)readb((void*)host->mapbase + reg);
}

static void emmc_reg_display(struct sdhci_host* host)
{
    rt_kprintf("SD_MASA_R:%x\n", sdhci_readl(host, SDHCI_DMA_ADDRESS));
    rt_kprintf("BLCOKSIZE_R:%x\n", sdhci_readw(host, SDHCI_BLOCK_SIZE));
    rt_kprintf("BLOCKCOUNT_R:%x\n", sdhci_readw(host, SDHCI_BLOCK_COUNT));
    rt_kprintf("ARGUMENT_R:%x\n", sdhci_readl(host, SDHCI_ARGUMENT));
    rt_kprintf("XFER_MODE_R:%x\n", sdhci_readw(host, SDHCI_TRANSFER_MODE));
    rt_kprintf("CMD_R:%x\n", sdhci_readw(host, SDHCI_COMMAND));
    rt_kprintf("RESP0_R:%x\n", sdhci_readl(host, SDHCI_RESPONSE));
    rt_kprintf("RESP1_R:%x\n", sdhci_readl(host, SDHCI_RESPONSE + 4));
    rt_kprintf("RESP2_R:%x\n", sdhci_readl(host, SDHCI_RESPONSE + 8));
    rt_kprintf("RESP3_R:%x\n", sdhci_readl(host, SDHCI_RESPONSE + 12));
    rt_kprintf("BUF_DATA_R:%x\n", sdhci_readl(host, SDHCI_BUFFER));
    rt_kprintf("PSTATE_REG_R:%x\n", sdhci_readl(host, SDHCI_PRESENT_STATE));
    rt_kprintf("HOST_CTL_R:%x\n", sdhci_readb(host, SDHCI_HOST_CONTROL));
    rt_kprintf("PWR_CTRL_R:%x\n", sdhci_readb(host, SDHCI_POWER_CONTROL));
    rt_kprintf("BGAP_CTRL_R:%x\n", sdhci_readb(host, SDHCI_BLOCK_GAP_CONTROL));
    rt_kprintf("WUP_CTRL_R:%x\n", sdhci_readb(host, SDHCI_WAKE_UP_CONTROL));
    rt_kprintf("CLK_CTRL_R:%x\n", sdhci_readw(host, SDHCI_CLOCK_CONTROL));
    rt_kprintf("TOUT_CTRL_R:%x\n", sdhci_readb(host, SDHCI_TIMEOUT_CONTROL));
    rt_kprintf("SW_RSR_R:%x\n", sdhci_readb(host, SDHCI_SOFTWARE_RESET));
    rt_kprintf("NORMAL_INT_STAT_R:%x\n", sdhci_readw(host, SDHCI_INT_STATUS));
    rt_kprintf("ERROR_INT_STAT_R:%x\n", sdhci_readw(host, SDHCI_INT_STATUS + 2));
    rt_kprintf("NORMAL_INT_STAT_EN_R:%x\n", sdhci_readw(host, SDHCI_INT_ENABLE));
    rt_kprintf("ERROR_INT_STAT_EN_R:%x\n", sdhci_readw(host, SDHCI_INT_ENABLE + 2));
    rt_kprintf("NORNAL_INT_SIGNAL_EN_R:%x\n", sdhci_readw(host, SDHCI_SIGNAL_ENABLE));
    rt_kprintf("ERROR_INT_SIGNAL_EN_R:%x\n", sdhci_readw(host, SDHCI_SIGNAL_ENABLE + 2));
    rt_kprintf("AUTO_CMD_STAT_R:%x\n", sdhci_readw(host, SDHCI_AUTO_CMD_STATUS));
    rt_kprintf("HOST_CTRL2_R:%x\n", sdhci_readw(host, SDHCI_HOST_CONTROL2));
    rt_kprintf("CAPABILITIES1_R:%x\n", sdhci_readl(host, SDHCI_CAPABILITIES));
    rt_kprintf("CAPABILITIES2_R:%x\n", sdhci_readl(host, SDHCI_CAPABILITIES_1));
    rt_kprintf("FORCE_AUTO_CMD_STAT_R:%x\n", sdhci_readw(host, SDHCI_MAX_CURRENT));
    rt_kprintf("FORCE_ERROR_INT_STAT_R:%x\n", sdhci_readw(host, SDHCI_SET_ACMD12_ERROR));
    rt_kprintf("AMDA_ERR_STAT_STAT_R:%x\n", sdhci_readl(host, SDHCI_ADMA_ERROR));
    rt_kprintf("AMDA_SA_LOW_STAT_R:%x\n", sdhci_readl(host, SDHCI_ADMA_ADDRESS));
    rt_kprintf("AMDA_SA_HIGH_STAT_R:%x\n", sdhci_readl(host, SDHCI_ADMA_ADDRESS_HI));
}

static inline void delay_1k(unsigned int uicnt)
{
    int i, j;

    for (i = 0; i < uicnt; i++)
        for (j = 0; j < 1000; j++)
            asm("nop");
}

static void dwcmshc_phy_1_8v_init(struct sdhci_host* host)
{
    sdhci_writew(host, DWC_MSHC_PHY_PAD_EMMC_DAT, DWC_MSHC_CMDPAD_CNFG);
    sdhci_writew(host, DWC_MSHC_PHY_PAD_EMMC_DAT, DWC_MSHC_DATPAD_CNFG);
    sdhci_writew(host, DWC_MSHC_PHY_PAD_EMMC_CLK, DWC_MSHC_CLKPAD_CNFG);
    sdhci_writew(host, DWC_MSHC_PHY_PAD_EMMC_STB, DWC_MSHC_STBPAD_CNFG);
    sdhci_writew(host, DWC_MSHC_PHY_PAD_EMMC_DAT, DWC_MSHC_RSTNPAD_CNFG);
}

static void dwcmshc_phy_3_3v_init(struct sdhci_host* host)
{
    sdhci_writew(host, DWC_MSHC_PHY_PAD_SD_DAT, DWC_MSHC_CMDPAD_CNFG);
    sdhci_writew(host, DWC_MSHC_PHY_PAD_SD_DAT, DWC_MSHC_DATPAD_CNFG);
    sdhci_writew(host, DWC_MSHC_PHY_PAD_SD_CLK, DWC_MSHC_CLKPAD_CNFG);
    sdhci_writew(host, DWC_MSHC_PHY_PAD_SD_STB, DWC_MSHC_STBPAD_CNFG);
    sdhci_writew(host, DWC_MSHC_PHY_PAD_SD_DAT, DWC_MSHC_RSTNPAD_CNFG);
}

static void dwcmshc_phy_delay_config(struct sdhci_host* host)
{
    sdhci_writeb(host, 1, DWC_MSHC_COMMDL_CNFG);
    if (host->tx_delay_line > 256) {
        LOG_E("host%d: tx_delay_line err\n", host->index);
    } else if (host->tx_delay_line > 128) {
        sdhci_writeb(host, 0x1, DWC_MSHC_SDCLKDL_CNFG);
        sdhci_writeb(host, host->tx_delay_line - 128, DWC_MSHC_SDCLKDL_DC);
    } else {
        sdhci_writeb(host, 0x0, DWC_MSHC_SDCLKDL_CNFG);
        sdhci_writeb(host, host->tx_delay_line, DWC_MSHC_SDCLKDL_DC);
    }
    sdhci_writeb(host, host->rx_delay_line, DWC_MSHC_SMPLDL_CNFG);
    sdhci_writeb(host, 0xc, DWC_MSHC_ATDL_CNFG);
    sdhci_writel(host, (sdhci_readl(host, SDHCI_VENDER_AT_CTRL_REG) | BIT(16) | BIT(17) | BIT(19) | BIT(20)), SDHCI_VENDER_AT_CTRL_REG);
    sdhci_writel(host, 0x0, SDHCI_VENDER_AT_STAT_REG);
}

static int dwcmshc_phy_init(struct sdhci_host* host)
{
    uint32_t reg;
    uint32_t timeout = 15000;
    /* reset phy */
    sdhci_writew(host, 0, DWC_MSHC_PHY_CNFG);

    /* Disable the clock */
    sdhci_writew(host, 0, SDHCI_CLOCK_CONTROL);

    if (host->io_fixed_1v8) {
        uint32_t data = sdhci_readw(host, SDHCI_HOST_CONTROL2);
        data |= SDHCI_CTRL_VDD_180;
        sdhci_writew(host, data, SDHCI_HOST_CONTROL2);
        dwcmshc_phy_1_8v_init(host);
    } else {
        dwcmshc_phy_3_3v_init(host);
    }

    dwcmshc_phy_delay_config(host);

    /* Wait max 150 ms */
    while (1) {
        reg = sdhci_readl(host, DWC_MSHC_PHY_CNFG);
        if (reg & PHY_PWRGOOD)
            break;
        if (!timeout) {
            return -1;
        }
        timeout--;

        delay_1k(1);
    }

    reg = PAD_SN_DEFAULT | PAD_SP_DEFAULT;
    sdhci_writel(host, reg, DWC_MSHC_PHY_CNFG);

    /* de-assert the phy */
    reg |= PHY_RSTN;
    sdhci_writel(host, reg, DWC_MSHC_PHY_CNFG);

    return 0;
}

static void sdhci_reset(struct sdhci_host* host, uint8_t mask)
{
    unsigned long timeout;

    /* Wait max 100 ms */
    timeout = 100;
    sdhci_writeb(host, mask, SDHCI_SOFTWARE_RESET);
    while (sdhci_readb(host, SDHCI_SOFTWARE_RESET) & mask) {
        if (timeout == 0) {
            LOG_E("%s: Reset 0x%x never completed.\n",
                __func__, (int)mask);
            return;
        }
        timeout--;
        delay_1k(1);
    }
    if (mask == SDHCI_RESET_ALL) {
        if (host->index == 0) {
            uint16_t emmc_ctl = sdhci_readw(host, EMMC_CTRL_R);
            if (host->is_emmc_card)
                emmc_ctl |= (1 << CARD_IS_EMMC);
            else
                emmc_ctl &= ~(1 << CARD_IS_EMMC);
            sdhci_writeb(host, emmc_ctl, EMMC_CTRL_R);
        }
        if (host->have_phy)
            dwcmshc_phy_init(host);
        else
            sdhci_writeb(host, host->mshc_ctrl_r, MSHC_CTRL_R);
    }
}

static uint32_t sdhci_get_present_status_flag(struct sdhci_host* sdhci_host)
{
    return sdhci_readl(sdhci_host, SDHCI_PRESENT_STATE);
}

static uint32_t sdhci_get_int_status_flag(struct sdhci_host* sdhci_host)
{
    return sdhci_readl(sdhci_host, SDHCI_INT_STATUS);
}

static void sdhci_clear_int_status_flag(struct sdhci_host* sdhci_host, uint32_t mask)
{
    sdhci_writel(sdhci_host, mask, SDHCI_INT_STATUS);
}

static void sdhic_error_recovery(struct sdhci_host* sdhci_host)
{
    uint32_t status;
    /* get host present status */
    status = sdhci_get_present_status_flag(sdhci_host);
    /* check command inhibit status flag */
    if ((status & SDHCI_CMD_INHIBIT) != 0U) {
        /* reset command line */
        sdhci_reset(sdhci_host, SDHCI_RESET_CMD);
    }
    /* check data inhibit status flag */
    if ((status & SDHCI_DATA_INHIBIT) != 0U) {
        /* reset data line */
        sdhci_reset(sdhci_host, SDHCI_RESET_DATA);
    }
}

static rt_err_t sdhci_receive_command_response(struct sdhci_host* sdhci_host, struct sdhci_command* command)
{
    if (command->responseType == card_response_type_r2) {
        /* CRC is stripped so we need to do some shifting. */
        for (int i = 0; i < 4; i++) {
            command->response[3 - i] = sdhci_readl(sdhci_host, SDHCI_RESPONSE + (3 - i) * 4) << 8;
            if (i != 3)
                command->response[3 - i] |= sdhci_readb(sdhci_host, SDHCI_RESPONSE + (3 - i) * 4 - 1);
        }
    } else {
        command->response[0] = sdhci_readl(sdhci_host, SDHCI_RESPONSE);
    }
    /* check response error flag */
    if ((command->responseErrorFlags != 0U) && ((command->responseType == card_response_type_r1) || (command->responseType == card_response_type_r1b) || (command->responseType == card_response_type_r6) || (command->responseType == card_response_type_r5))) {
        if (((command->responseErrorFlags) & (command->response[0U])) != 0U)
            return -1; // kStatus_USDHC_SendCommandFailed;
    }

    return 0;
}

static void sdhci_send_command(struct sdhci_host* sdhci_host, struct sdhci_command* command, rt_bool_t enDMA)
{
    RT_ASSERT(RT_NULL != command);

    uint32_t cmd_r, xfer_mode;
    struct sdhci_data* sdhci_data = sdhci_host->sdhci_data;

    cmd_r = SDHCI_MAKE_CMD(command->index, command->flags);

    if (sdhci_data != RT_NULL) {
#ifdef SDHCI_SDMA_ENABLE
        rt_ubase_t start_addr, dma_addr;
        if (sdhci_data->rxData)
            start_addr = (rt_ubase_t)((uint8_t*)sdhci_data->rxData);
        else
            start_addr = (rt_ubase_t)((uint8_t*)sdhci_data->txData);
        rt_hw_cpu_dcache_clean((void*)start_addr, sdhci_data->blockSize * sdhci_data->blockCount);
        command->flags2 |= sdhci_enable_dma_flag;
        dma_addr = rt_kmem_v2p((void*)start_addr);
        sdhci_writel(sdhci_host, dma_addr, SDHCI_DMA_ADDRESS);
#endif
        sdhci_writew(sdhci_host, SDHCI_MAKE_BLKSZ(7, sdhci_data->blockSize), SDHCI_BLOCK_SIZE);
        sdhci_writew(sdhci_host, sdhci_data->blockCount, SDHCI_BLOCK_COUNT);
    }
    xfer_mode = command->flags2 & 0x1ff;
    sdhci_writew(sdhci_host, xfer_mode, SDHCI_TRANSFER_MODE);
    sdhci_writel(sdhci_host, command->argument, SDHCI_ARGUMENT);
    sdhci_writew(sdhci_host, cmd_r, SDHCI_COMMAND);
}

static rt_err_t sdhci_wait_command_done(struct sdhci_host* sdhci_host, struct sdhci_command* command, rt_bool_t executeTuning)
{
    RT_ASSERT(RT_NULL != command);
    rt_uint32_t event;
    /* tuning cmd do not need to wait command done */
    if (executeTuning)
        return 0;
    /* Wait command complete or USDHC encounters error. */
    rt_event_recv(&sdhci_host->event, SDHCI_INT_ERROR | SDHCI_INT_RESPONSE,
        RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &event);
    if (event & SDHCI_INT_ERROR) {
        LOG_D("%s: Error detected in status(0x%X)!\n", __func__, sdhci_host->error_code);
        return -1;
    }
    return sdhci_receive_command_response(sdhci_host, command);
}

static rt_err_t sdhci_transfer_data_blocking(struct sdhci_host* sdhci_host, struct sdhci_data* data, rt_bool_t enDMA)
{
#ifdef SDHCI_SDMA_ENABLE
    rt_err_t err;
    rt_uint32_t event;

    while (1) {
        err = rt_event_recv(&sdhci_host->event, SDHCI_INT_ERROR | SDHCI_INT_DATA_END | SDHCI_INT_DMA_END,
            RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, 1000, &event);
        if (err == -RT_ETIMEOUT) {
            rt_kprintf("%s: Transfer data timeout\n", __func__);
            return -1;
        }
        if (event & SDHCI_INT_ERROR) {
            LOG_D("%s: Error detected in status(0x%X)!\n", __func__, sdhci_host->error_code);
            emmc_reg_display(sdhci_host);
            return -1;
        }
        if (event & SDHCI_INT_DMA_END) {
            sdhci_writel(sdhci_host, SDHCI_INT_DMA_END, SDHCI_INT_STATUS);
            sdhci_writel(sdhci_host, sdhci_readl(sdhci_host, SDHCI_DMA_ADDRESS), SDHCI_DMA_ADDRESS);
        }
        if (event & SDHCI_INT_DATA_END) {
            if (data && data->rxData)
                rt_hw_cpu_dcache_invalidate((void*)data->rxData, data->blockSize * data->blockCount);
            return 0;
        }
    }
#else
    uint32_t stat, rdy, mask, timeout, block;

    block = 0;
    timeout = 1000000;
    rdy = SDHCI_INT_SPACE_AVAIL | SDHCI_INT_DATA_AVAIL;
    mask = SDHCI_DATA_AVAILABLE | SDHCI_SPACE_AVAILABLE;

    while (1) {
        stat = sdhci_get_int_status_flag(sdhci_host);
        if (stat & SDHCI_INT_ERROR) {
            LOG_D("%s: Error detected in status(0x%X)!\n", __func__, stat);
            emmc_reg_display(sdhci_host);
            return -1;
        }
        if (stat & rdy) {
            if (!(sdhci_readl(sdhci_host, SDHCI_PRESENT_STATE) & mask)) {
                continue;
            }
            sdhci_clear_int_status_flag(sdhci_host, rdy);
            if (data->rxData) {
                for (int i = 0; i < data->blockSize / 4; i++)
                    data->rxData[i + block * data->blockSize] = sdhci_readl(sdhci_host, SDHCI_BUFFER);
            } else {
                for (int i = 0; i < data->blockSize / 4; i++)
                    sdhci_writel(sdhci_host, data->txData[i + block * data->blockSize], SDHCI_BUFFER);
            }
            block++;
            if (block >= data->blockCount)
                return 0;
        }
        if (timeout == 0) {
            rt_kprintf("%s: Transfer data timeout\n", __func__);
            return -1;
        }
        timeout--;
        delay_1k(1);
    }
#endif
}

static rt_err_t sdhci_set_transfer_config(struct sdhci_host* sdhci_host, struct sdhci_command* sdhci_command, struct sdhci_data* sdhci_data)
{
    RT_ASSERT(sdhci_command);
    /* Define the flag corresponding to each response type. */
    switch (sdhci_command->responseType) {
    case card_response_type_none:
        break;
    case card_response_type_r1: /* Response 1 */
    case card_response_type_r5: /* Response 5 */
    case card_response_type_r6: /* Response 6 */
    case card_response_type_r7: /* Response 7 */

        sdhci_command->flags |= (sdhci_cmd_resp_short | sdhci_enable_cmd_crc_flag | sdhci_enable_cmd_index_chk_flag);
        break;

    case card_response_type_r1b: /* Response 1 with busy */
    case card_response_type_r5b: /* Response 5 with busy */
        sdhci_command->flags |= (sdhci_cmd_resp_short_busy | sdhci_enable_cmd_crc_flag | sdhci_enable_cmd_index_chk_flag);
        break;

    case card_response_type_r2: /* Response 2 */
        sdhci_command->flags |= (sdhci_cmd_resp_long | sdhci_enable_cmd_crc_flag);
        break;

    case card_response_type_r3: /* Response 3 */
    case card_response_type_r4: /* Response 4 */
        sdhci_command->flags |= (sdhci_cmd_resp_short);
        break;

    default:
        break;
    }

    if (sdhci_command->type == card_command_type_abort) {
        sdhci_command->flags |= sdhci_enable_command_type_abort;
    } else if (sdhci_command->type == card_command_type_resume) {
        sdhci_command->flags |= sdhci_enable_command_type_resume;
    } else if (sdhci_command->type == card_command_type_suspend) {
        sdhci_command->flags |= sdhci_enable_command_type_suspend;
    } else if (sdhci_command->type == card_command_type_normal) {
        sdhci_command->flags |= sdhci_enable_command_type_normal;
    }

    if (sdhci_data) {
        sdhci_command->flags |= sdhci_enable_cmd_data_present_flag;
        sdhci_command->flags2 |= sdhci_enable_block_count_flag;

        if (sdhci_data->rxData) {
            sdhci_command->flags2 |= sdhci_data_read_flag;
        }
        if (sdhci_data->blockCount > 1U) {
            sdhci_command->flags2 |= (sdhci_multiple_block_flag);
            /* auto command 12 */
            if (sdhci_data->enableAutoCommand12) {
                /* Enable Auto command 12. */
                sdhci_command->flags2 |= sdhci_enable_auto_command12_flag;
            }
            /* auto command 23 */
            if (sdhci_data->enableAutoCommand23) {
                sdhci_command->flags2 |= sdhci_enable_auto_command23_flag;
            }
        }
    }
    return 0;
}

static rt_err_t sdhci_transfer_blocking(struct sdhci_host* sdhci_host)
{
    RT_ASSERT(sdhci_host);
    struct sdhci_command* sdhci_command = sdhci_host->sdhci_command;
    struct sdhci_data* sdhci_data = sdhci_host->sdhci_data;
    rt_bool_t enDMA = false;
    int ret = RT_EOK;

    /* Wait until command/data bus out of busy status. */
    while (sdhci_get_present_status_flag(sdhci_host) & sdhci_command_inhibit_flag) {
    }
    while (sdhci_data && (sdhci_get_present_status_flag(sdhci_host) & sdhci_data_inhibit_flag)) {
    }
    sdhci_writel(sdhci_host, SDHCI_INT_ALL_MASK, SDHCI_INT_STATUS);

    ret = sdhci_set_transfer_config(sdhci_host, sdhci_command, sdhci_data);
    if (ret != 0) {
        return ret;
    }
    sdhci_writel(sdhci_host, sdhci_readl(sdhci_host, SDHCI_SIGNAL_ENABLE) |
        SDHCI_INT_DATA_MASK | SDHCI_INT_CMD_MASK, SDHCI_SIGNAL_ENABLE);
    rt_event_control(&sdhci_host->event, RT_IPC_CMD_RESET, 0);
    sdhci_send_command(sdhci_host, sdhci_command, enDMA);
    /* wait command done */
    ret = sdhci_wait_command_done(sdhci_host, sdhci_command, ((sdhci_data == RT_NULL) ? false : sdhci_data->executeTuning));
    /* transfer data */
    if ((sdhci_data != RT_NULL) && (ret == 0)) {
        ret = sdhci_transfer_data_blocking(sdhci_host, sdhci_data, enDMA);
    }
    sdhci_writel(sdhci_host, sdhci_readl(sdhci_host, SDHCI_SIGNAL_ENABLE) &
        ~(SDHCI_INT_DATA_MASK | SDHCI_INT_CMD_MASK), SDHCI_SIGNAL_ENABLE);
    sdhci_writel(sdhci_host, SDHCI_INT_ALL_MASK, SDHCI_INT_STATUS);
    sdhci_reset(sdhci_host, SDHCI_RESET_CMD);
    sdhci_reset(sdhci_host, SDHCI_RESET_DATA);
    return ret;
}

static void sdhci_init(struct sdhci_host* host)
{
    sdhci_reset(host, SDHCI_RESET_ALL);
    sdhci_writeb(host, SDHCI_CTRL_HISPD, SDHCI_HOST_CONTROL);
    sdhci_writeb(host, 0x7, SDHCI_TIMEOUT_CONTROL);
    sdhci_writeb(host, SDHCI_POWER_ON | SDHCI_POWER_330, SDHCI_POWER_CONTROL);
    sdhci_writew(host, SDHCI_CLOCK_INT_EN, SDHCI_CLOCK_CONTROL);
    while ((sdhci_readw(host, SDHCI_CLOCK_CONTROL) & SDHCI_CLOCK_INT_STABLE) == 0)
        ;
    sdhci_writel(host, SDHCI_INT_DATA_MASK | SDHCI_INT_CMD_MASK, SDHCI_INT_ENABLE);
    sdhci_writel(host, SDHCI_INT_CARD_INT, SDHCI_SIGNAL_ENABLE);
}

static void sdhci_irq(int vector, void* param)
{
    struct sdhci_host* host = param;
    uint32_t status = sdhci_get_int_status_flag(host);

    if (status & (SDHCI_INT_ERROR | SDHCI_INT_DATA_END | SDHCI_INT_DMA_END | SDHCI_INT_RESPONSE)) {
        host->error_code = (status >> 16) & 0xffff;
        rt_event_send(&host->event, status & (SDHCI_INT_ERROR | SDHCI_INT_DATA_END | SDHCI_INT_DMA_END | SDHCI_INT_RESPONSE));
    }
    if (status & SDHCI_INT_CARD_INT)
        sdio_irq_wakeup(host->host);
    sdhci_clear_int_status_flag(host, status);
}

static void kd_mmc_request(struct rt_mmcsd_host* host, struct rt_mmcsd_req* req)
{
    struct sdhci_host* mmcsd;
    struct rt_mmcsd_cmd* cmd;
    struct rt_mmcsd_data* data;
    rt_err_t error;
    struct sdhci_data sdhci_data = { 0 };
    struct sdhci_command sdhci_command = { 0 };

    RT_ASSERT(host != RT_NULL);
    RT_ASSERT(req != RT_NULL);

    mmcsd = (struct sdhci_host*)host->private_data;
    RT_ASSERT(mmcsd != RT_NULL);

    cmd = req->cmd;
    RT_ASSERT(cmd != RT_NULL);

    LOG_D("\tcmd->cmd_code: %02d, cmd->arg: %08x, cmd->flags: %08x --> ", cmd->cmd_code, cmd->arg, cmd->flags);

    data = cmd->data;

    sdhci_command.index = cmd->cmd_code;
    sdhci_command.argument = cmd->arg;

    if (cmd->cmd_code == STOP_TRANSMISSION)
        sdhci_command.type = card_command_type_abort;
    else
        sdhci_command.type = card_command_type_normal;

    switch (cmd->flags & RESP_MASK) {
    case RESP_NONE:
        sdhci_command.responseType = card_response_type_none;
        break;
    case RESP_R1:
        sdhci_command.responseType = card_response_type_r1;
        break;
    case RESP_R1B:
        sdhci_command.responseType = card_response_type_r1b;
        break;
    case RESP_R2:
        sdhci_command.responseType = card_response_type_r2;
        break;
    case RESP_R3:
        sdhci_command.responseType = card_response_type_r3;
        break;
    case RESP_R4:
        sdhci_command.responseType = card_response_type_r4;
        break;
    case RESP_R6:
        sdhci_command.responseType = card_response_type_r6;
        break;
    case RESP_R7:
        sdhci_command.responseType = card_response_type_r7;
        break;
    case RESP_R5:
        sdhci_command.responseType = card_response_type_r5;
        break;
    default:
        RT_ASSERT(RT_NULL);
    }

    sdhci_command.flags = 0;
    sdhci_command.flags2 = 0;
    sdhci_command.responseErrorFlags = 0;
    mmcsd->sdhci_command = &sdhci_command;

    if (data) {
        if (req->stop != RT_NULL)
            sdhci_data.enableAutoCommand12 = true;
        else
            sdhci_data.enableAutoCommand12 = false;

        sdhci_data.enableAutoCommand23 = false;

        sdhci_data.blockSize = data->blksize;
        sdhci_data.blockCount = data->blks;

        if (data->flags == DATA_DIR_WRITE) {
            sdhci_data.txData = data->buf;
            sdhci_data.rxData = RT_NULL;
        } else {
            sdhci_data.rxData = data->buf;
            sdhci_data.txData = RT_NULL;
        }
#ifdef SDHCI_SDMA_ENABLE
        uint32_t sz = sdhci_data.blockSize * sdhci_data.blockCount;
        uint32_t pad = 0;
        if (sz & (CACHE_LINESIZE - 1))
            pad = (sz + (CACHE_LINESIZE - 1)) & ~(CACHE_LINESIZE - 1);
        if (sdhci_data.rxData && (((uint64_t)(sdhci_data.rxData) & (CACHE_LINESIZE - 1)) || pad)) {
            sdhci_data.rxData = rt_malloc_align(pad ? pad : sz, CACHE_LINESIZE);
        } else if (((uint64_t)(sdhci_data.txData) & (CACHE_LINESIZE - 1)) || pad) {
            sdhci_data.txData = rt_malloc_align(pad ? pad : sz, CACHE_LINESIZE);
            rt_memcpy(sdhci_data.txData, data->buf, sz);
        }
#endif
        mmcsd->sdhci_data = &sdhci_data;
    } else {
        mmcsd->sdhci_data = RT_NULL;
    }
    error = sdhci_transfer_blocking(mmcsd);
#ifdef SDHCI_SDMA_ENABLE
    if (data && sdhci_data.rxData && sdhci_data.rxData != data->buf) {
        rt_memcpy(data->buf, sdhci_data.rxData, sdhci_data.blockSize * sdhci_data.blockCount);
        rt_free_align(sdhci_data.rxData);
    } else if (data && sdhci_data.txData && sdhci_data.txData != data->buf) {
        rt_free_align(sdhci_data.txData);
    }
#endif
    if (error == -1) {
        LOG_D(" ***USDHC_TransferBlocking error: %d*** --> \n", error);
        cmd->err = -RT_ERROR;
    }

    if ((cmd->flags & RESP_MASK) == RESP_R2) {
        cmd->resp[3] = sdhci_command.response[0];
        cmd->resp[2] = sdhci_command.response[1];
        cmd->resp[1] = sdhci_command.response[2];
        cmd->resp[0] = sdhci_command.response[3];
        LOG_D(" resp 0x%08X 0x%08X 0x%08X 0x%08X\n",
            cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3]);
    } else {
        cmd->resp[0] = sdhci_command.response[0];
        LOG_D(" resp 0x%08X\n", cmd->resp[0]);
    }
    mmcsd_req_complete(host);
}

static void kd_mmc_clock_freq_change(struct sdhci_host* host, uint32_t clock)
{
    uint32_t div, val;

    val = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
    val &= ~(SDHCI_CLOCK_CARD_EN | SDHCI_PROG_CLOCK_MODE);
    sdhci_writew(host, val, SDHCI_CLOCK_CONTROL);

    if (clock == 0)
        return;

    if (host->max_clk <= clock) {
        div = 1;
    } else {
        for (div = 2; div < SDHCI_MAX_DIV_SPEC_300; div += 2) {
            if ((host->max_clk / div) <= clock)
                break;
        }
    }
    div >>= 1;
    val &= ~((SDHCI_DIV_MASK << SDHCI_DIVIDER_SHIFT) | SDHCI_DIV_HI_MASK);
    val |= (div & SDHCI_DIV_MASK) << SDHCI_DIVIDER_SHIFT;
    val |= ((div & SDHCI_DIV_HI_MASK) >> SDHCI_DIV_MASK_LEN)
        << SDHCI_DIVIDER_HI_SHIFT;
    val |= SDHCI_CLOCK_CARD_EN | SDHCI_PROG_CLOCK_MODE;
    sdhci_writew(host, val, SDHCI_CLOCK_CONTROL);
    while ((sdhci_readw(host, SDHCI_CLOCK_CONTROL) & SDHCI_CLOCK_INT_STABLE) == 0)
        ;
}

static void kd_set_iocfg(struct rt_mmcsd_host* host, struct rt_mmcsd_io_cfg* io_cfg)
{
    struct sdhci_host* mmcsd;
    unsigned int sdhci_clk;
    unsigned int bus_width;
    uint8_t ctrl;
    RT_ASSERT(host != RT_NULL);
    RT_ASSERT(host->private_data != RT_NULL);
    RT_ASSERT(io_cfg != RT_NULL);

    mmcsd = (struct sdhci_host*)host->private_data;
    sdhci_clk = io_cfg->clock;
    bus_width = io_cfg->bus_width;

    LOG_D("%s: sdhci_clk=%d, bus_width:%d\n", __func__, sdhci_clk, bus_width);

    kd_mmc_clock_freq_change(mmcsd, sdhci_clk);
    ctrl = sdhci_readb(mmcsd, SDHCI_HOST_CONTROL);
    ctrl &= ~(SDHCI_CTRL_4BITBUS | SDHCI_CTRL_8BITBUS);
    if (bus_width == 3)
        ctrl |= SDHCI_CTRL_8BITBUS;
    else if (bus_width == 2)
        ctrl |= SDHCI_CTRL_4BITBUS;
    sdhci_writeb(mmcsd, ctrl, SDHCI_HOST_CONTROL);
}

static void kd_enable_sdio_irq(struct rt_mmcsd_host* mmcsd_host, rt_int32_t en)
{
    struct sdhci_host* host = (struct sdhci_host*)mmcsd_host->private_data;
    uint32_t val;

    val = sdhci_readw(host, SDHCI_INT_ENABLE);
    if (en)
        val |= SDHCI_INT_CARD_INT;
    else
        val &= ~SDHCI_INT_CARD_INT;
    sdhci_writew(host, val, SDHCI_INT_ENABLE);
}

static const struct rt_mmcsd_host_ops ops = {
    kd_mmc_request,
    kd_set_iocfg,
    RT_NULL,
    kd_enable_sdio_irq,
    RT_NULL,
};

void kd_sdhci0_reset(int value)
{
    struct sdhci_host* host = sdhci_host0;

    uint16_t emmc_ctl = sdhci_readw(host, EMMC_CTRL_R);
    emmc_ctl |= (1 << EMMC_RST_N_OE);
    if (value)
        emmc_ctl |= (1 << EMMC_RST_N);
    else
        emmc_ctl &= ~(1 << EMMC_RST_N);
    sdhci_writeb(host, emmc_ctl, EMMC_CTRL_R);
}

void kd_sdhci_change(int id)
{
    if (id == 0)
        mmcsd_change(sdhci_host0->host);
    else if (id == 1)
        mmcsd_change(sdhci_host1->host);
}

rt_int32_t kd_sdhci_init(void)
{
    uint32_t val;
    void* hi_sys_virt_addr = rt_ioremap((void*)0x91585000, 0x10);
#ifdef BSP_USING_SDIO0
    val = readl(hi_sys_virt_addr + 0);
    val |= 1 << 6 | 1 << 4;
    writel(val, hi_sys_virt_addr + 0);
    sdhci_host0 = rt_malloc(sizeof(struct sdhci_host));
    if (!sdhci_host0)
        return -1;

    rt_memset(sdhci_host0, 0, sizeof(struct sdhci_host));
    sdhci_host0->mapbase = (void*)rt_ioremap((void*)SDEMMC0_BASE, 0x1000);
    sdhci_host0->index = 0;
    sdhci_host0->have_phy = 1;
    sdhci_host0->mshc_ctrl_r = 0;
    sdhci_host0->rx_delay_line = 0x0d;
    sdhci_host0->tx_delay_line = 0xc0;
#ifdef BSP_SDIO0_EMMC
    sdhci_host0->is_emmc_card = 1;
#else
    sdhci_host0->is_emmc_card = 0;
#endif
#ifdef BSP_SDIO0_1V8
    sdhci_host0->io_fixed_1v8 = 1;
#else
    sdhci_host0->io_fixed_1v8 = 0;
#endif
    sdhci_host0->sdhci_data = RT_NULL;
    sdhci_host0->sdhci_command = RT_NULL;
    sdhci_host0->max_clk = 200000000;
    sdhci_init(sdhci_host0);

    rt_event_init(&sdhci_host0->event, "sd0_event", RT_IPC_FLAG_PRIO);
    rt_hw_interrupt_install(IRQN_SD0, sdhci_irq, sdhci_host0, "sd0");
    rt_hw_interrupt_umask(IRQN_SD0);

    struct rt_mmcsd_host* mmcsd_host0 = mmcsd_alloc_host();
    if (!mmcsd_host0) {
        rt_free(sdhci_host0);
        return -1;
    }
    mmcsd_host0->ops = &ops;
    mmcsd_host0->freq_min = 400000;
    mmcsd_host0->freq_max = 50000000;
#ifdef BSP_SDIO0_EMMC
    strncpy(mmcsd_host0->name, "emmc", sizeof(mmcsd_host0->name) - 1);
    mmcsd_host0->flags = MMCSD_BUSWIDTH_8 | MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ;
#else
    strncpy(mmcsd_host0->name, "sd0", sizeof(mmcsd_host0->name) - 1);
    mmcsd_host0->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ;
#endif
    mmcsd_host0->valid_ocr = sdhci_host0->io_fixed_1v8 ? VDD_165_195 : VDD_32_33 | VDD_33_34;
#ifdef BSP_USING_CYW43XX
    mmcsd_host0->valid_ocr = VDD_32_33 | VDD_33_34;
#endif
    mmcsd_host0->max_seg_size = 512 * 512;
    mmcsd_host0->max_dma_segs = 1;
    mmcsd_host0->max_blk_size = 512;
    mmcsd_host0->max_blk_count = 4096;
    mmcsd_host0->private_data = sdhci_host0;
    sdhci_host0->host = mmcsd_host0;
#endif
#ifdef BSP_USING_SDIO1
    val = readl(hi_sys_virt_addr + 8);
    val |= 1 << 2 | 1 << 0;
    writel(val, hi_sys_virt_addr + 8);
    sdhci_host1 = rt_malloc(sizeof(struct sdhci_host));
    if (!sdhci_host1)
        return -2;

    rt_memset(sdhci_host1, 0, sizeof(struct sdhci_host));
    sdhci_host1->mapbase = (void*)rt_ioremap((void*)SDEMMC1_BASE, 0x1000);
    sdhci_host1->index = 1;
    sdhci_host1->have_phy = 0;
    sdhci_host1->mshc_ctrl_r = 0;
    sdhci_host1->rx_delay_line = 0;
    sdhci_host1->tx_delay_line = 0;
    sdhci_host1->sdhci_data = RT_NULL;
    sdhci_host1->sdhci_command = RT_NULL;
    sdhci_host1->max_clk = 100000000;
    sdhci_init(sdhci_host1);

    rt_event_init(&sdhci_host1->event, "sd1_event", RT_IPC_FLAG_PRIO);
    rt_hw_interrupt_install(IRQN_SD1, sdhci_irq, sdhci_host1, "sd1");
    rt_hw_interrupt_umask(IRQN_SD1);

    struct rt_mmcsd_host* mmcsd_host1 = mmcsd_alloc_host();
    if (!mmcsd_host1) {
        rt_free(sdhci_host1);
        return -2;
    }
    strncpy(mmcsd_host1->name, "sd1", sizeof(mmcsd_host1->name) - 1);
    mmcsd_host1->ops = &ops;
    mmcsd_host1->freq_min = 400000;
    mmcsd_host1->freq_max = 50000000;
    mmcsd_host1->valid_ocr = VDD_32_33 | VDD_33_34;
    mmcsd_host1->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ;
    mmcsd_host1->max_seg_size = 512 * 512;
    mmcsd_host1->max_dma_segs = 1;
    mmcsd_host1->max_blk_size = 512;
    mmcsd_host1->max_blk_count = 4096;
    mmcsd_host1->private_data = sdhci_host1;
    sdhci_host1->host = mmcsd_host1;
#endif
#ifdef BSP_SD_SDIO_DEV
    kd_sdhci_change(BSP_SD_SDIO_DEV);
#endif
    rt_iounmap(hi_sys_virt_addr);
    return 0;
}
INIT_DEVICE_EXPORT(kd_sdhci_init);

#endif /*defined(BSP_USING_SDIO0) || defined(BSP_USING_SDIO1)*/

#endif /*defined(RT_USING_SDIO)*/
