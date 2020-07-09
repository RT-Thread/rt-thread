/*
 * drv_sfc.c
 *
 *  Created on: 2016Äê4ÔÂ5ÈÕ
 *      Author: Urey
 */

/*********************************************************************************************************
**   Include Files
*********************************************************************************************************/
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <cache.h>
#include <sys/types.h>

#include "board.h"
#include "drv_clock.h"
#include "drv_gpio.h"
#include "drv_sfc.h"

//#define SFC_DEBUG
#if defined(SFC_DEBUG)
#define SFC_DBG(...)     rt_kprintf("[SFC]"),rt_kprintf(__VA_ARGS__)
#else
#define SFC_DBG(...)
#endif

#define L2CACHE_ALIGN_SIZE  256
#define THRESHOLD           32
#define PAGE_SIZE           4096

/* Max time can take up to 3 seconds! */
#define MAX_READY_WAIT_TIME 3000    /* the time of erase BE(64KB) */

#define STATUS_SUSPND       (1<<0)


#define tCHSH       5   //hold
#define tSLCH       5   //setup
#define tSHSL_RD    20  //interval
#define tSHSL_WR    30

static void sfc_writel(struct sfc *sfc, uint16_t offset, u32 value)
{
    writel(value, (uint32_t)sfc->iomem + offset);
}

static uint32_t sfc_readl(struct sfc *sfc, uint16_t offset)
{
    return readl((uint32_t)sfc->iomem + offset);
}

static void sfc_init(struct sfc *sfc)
{
    uint32_t n;
    for (n = 0; n < N_MAX; n++)
    {
        sfc_writel(sfc, SFC_TRAN_CONF(n), 0);
        sfc_writel(sfc, SFC_DEV_ADDR(n), 0);
        sfc_writel(sfc, SFC_DEV_ADDR_PLUS(n), 0);
    }

    //sfc_writel(sfc, SFC_GLB, ((1 << 7) | (1 << 3)));
    sfc_writel(sfc, SFC_DEV_CONF, 0);
    sfc_writel(sfc, SFC_DEV_STA_EXP, 0);
    sfc_writel(sfc, SFC_DEV_STA_MSK, 0);
    sfc_writel(sfc, SFC_TRAN_LEN, 0);
    sfc_writel(sfc, SFC_MEM_ADDR, 0);
    sfc_writel(sfc, SFC_TRIG, 0);
    sfc_writel(sfc, SFC_SCR, 0);
    sfc_writel(sfc, SFC_INTC, 0);
    sfc_writel(sfc, SFC_CGE, 0);
    sfc_writel(sfc, SFC_RM_DR, 0);
}

static void sfc_stop(struct sfc*sfc)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_TRIG);
    tmp |= TRIG_STOP;
    sfc_writel(sfc, SFC_TRIG, tmp);
}

static void sfc_start(struct sfc *sfc)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_TRIG);
    tmp |= TRIG_START;
    sfc_writel(sfc, SFC_TRIG, tmp);
}

static void sfc_flush_fifo(struct sfc *sfc)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_TRIG);
    tmp |= TRIG_FLUSH;
    sfc_writel(sfc, SFC_TRIG, tmp);
}

static void sfc_ce_invalid_value(struct sfc *sfc, uint32_t value)
{
    if (value == 0)
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_DEV_CONF);
        tmp &= ~DEV_CONF_CEDL;
        sfc_writel(sfc, SFC_DEV_CONF, tmp);
    }
    else
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_DEV_CONF);
        tmp |= DEV_CONF_CEDL;
        sfc_writel(sfc, SFC_DEV_CONF, tmp);
    }
}

static void sfc_hold_invalid_value(struct sfc *sfc, uint32_t value)
{
    if (value == 0)
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_DEV_CONF);
        tmp &= ~DEV_CONF_HOLDDL;
        sfc_writel(sfc, SFC_DEV_CONF, tmp);
    }
    else
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_DEV_CONF);
        tmp |= DEV_CONF_HOLDDL;
        sfc_writel(sfc, SFC_DEV_CONF, tmp);
    }
}

static void sfc_wp_invalid_value(struct sfc *sfc, uint32_t value)
{
    if (value == 0)
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_DEV_CONF);
        tmp &= ~DEV_CONF_WPDL;
        sfc_writel(sfc, SFC_DEV_CONF, tmp);
    }
    else
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_DEV_CONF);
        tmp |= DEV_CONF_WPDL;
        sfc_writel(sfc, SFC_DEV_CONF, tmp);
    }
}

static void sfc_clear_end_intc(struct sfc *sfc)
{
    uint32_t tmp = 0;
    tmp = sfc_readl(sfc, SFC_SCR);
    tmp |= CLR_END;
    sfc_writel(sfc, SFC_SCR, tmp);
    tmp = sfc_readl(sfc, SFC_SCR);
}

static void sfc_clear_treq_intc(struct sfc *sfc)
{
    uint32_t tmp = 0;
    tmp = sfc_readl(sfc, SFC_SCR);
    tmp |= CLR_TREQ;
    sfc_writel(sfc, SFC_SCR, tmp);
}

static void sfc_clear_rreq_intc(struct sfc *sfc)
{
    uint32_t tmp = 0;
    tmp = sfc_readl(sfc, SFC_SCR);
    tmp |= CLR_RREQ;
    sfc_writel(sfc, SFC_SCR, tmp);
}

static void sfc_clear_over_intc(struct sfc *sfc)
{
    uint32_t tmp = 0;
    tmp = sfc_readl(sfc, SFC_SCR);
    tmp |= CLR_OVER;
    sfc_writel(sfc, SFC_SCR, tmp);
}

static void sfc_clear_under_intc(struct sfc *sfc)
{
    uint32_t tmp = 0;
    tmp = sfc_readl(sfc, SFC_SCR);
    tmp |= CLR_UNDER;
    sfc_writel(sfc, SFC_SCR, tmp);
}

static void sfc_clear_all_intc(struct sfc *sfc)
{
    sfc_writel(sfc, SFC_SCR, 0x1f);
}

static void sfc_mask_all_intc(struct sfc *sfc)
{
    sfc_writel(sfc, SFC_INTC, 0x1f);
}

static void sfc_mode(struct sfc *sfc, uint32_t channel, uint32_t value)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_TRAN_CONF(channel));
    tmp &= ~(TRAN_CONF_TRAN_MODE_MSK << TRAN_CONF_TRAN_MODE_OFFSET);
    tmp |= (value << TRAN_CONF_TRAN_MODE_OFFSET);
    sfc_writel(sfc, SFC_TRAN_CONF(channel), tmp);
}

static void sfc_set_phase_num(struct sfc *sfc,uint32_t num)
{
    uint32_t tmp;

    tmp = sfc_readl(sfc, SFC_GLB);
    tmp &= ~GLB_PHASE_NUM_MSK;
    tmp |= num << GLB_PHASE_NUM_OFFSET;
    sfc_writel(sfc, SFC_GLB, tmp);
}

static void sfc_clock_phase(struct sfc *sfc, uint32_t value)
{
    if (value == 0)
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_DEV_CONF);
        tmp &= ~DEV_CONF_CPHA;
        sfc_writel(sfc, SFC_DEV_CONF, tmp);
    }
    else
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_DEV_CONF);
        tmp |= DEV_CONF_CPHA;
        sfc_writel(sfc, SFC_DEV_CONF, tmp);
    }
}

static void sfc_clock_polarity(struct sfc *sfc, uint32_t value)
{
    if (value == 0)
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_DEV_CONF);
        tmp &= ~DEV_CONF_CPOL;
        sfc_writel(sfc, SFC_DEV_CONF, tmp);
    }
    else
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_DEV_CONF);
        tmp |= DEV_CONF_CPOL;
        sfc_writel(sfc, SFC_DEV_CONF, tmp);
    }
}

static void sfc_threshold(struct sfc *sfc, uint32_t value)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_GLB);
    tmp &= ~GLB_THRESHOLD_MSK;
    tmp |= value << GLB_THRESHOLD_OFFSET;
    sfc_writel(sfc, SFC_GLB, tmp);
}


static void sfc_smp_delay(struct sfc *sfc, uint32_t value)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_DEV_CONF);
    tmp &= ~DEV_CONF_SMP_DELAY_MSK;
    tmp |= value << DEV_CONF_SMP_DELAY_OFFSET;
    sfc_writel(sfc, SFC_DEV_CONF, tmp);
}

static void sfc_hold_delay(struct sfc *sfc, uint32_t value)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_DEV_CONF);
    tmp &= ~DEV_CONF_THOLD_MSK;
    tmp |= value << DEV_CONF_THOLD_OFFSET;
    sfc_writel(sfc, SFC_DEV_CONF, tmp);
}

static void sfc_setup_delay(struct sfc *sfc, uint32_t value)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_DEV_CONF);
    tmp &= ~DEV_CONF_TSETUP_MSK;
    tmp |= value << DEV_CONF_TSETUP_OFFSET;
    sfc_writel(sfc, SFC_DEV_CONF, tmp);
}

static void sfc_interval_delay(struct sfc *sfc, uint32_t value)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_DEV_CONF);
    tmp &= ~DEV_CONF_TSH_MSK;
    tmp |= value << DEV_CONF_TSH_OFFSET;
    sfc_writel(sfc, SFC_DEV_CONF, tmp);
}

static void sfc_set_cmd_length(struct sfc *sfc, uint32_t value)
{
    if (value == 1)
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_DEV_CONF);
        tmp &= ~TRAN_CONF_CMD_LEN;
        sfc_writel(sfc, SFC_DEV_CONF, tmp);
    }
    else
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_DEV_CONF);
        tmp |= TRAN_CONF_CMD_LEN;
        sfc_writel(sfc, SFC_DEV_CONF, tmp);
    }
}

static void sfc_transfer_direction(struct sfc *sfc, uint32_t value)
{
    if (value == GLB_TRAN_DIR_READ)
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_GLB);
        tmp &= ~GLB_TRAN_DIR;
        sfc_writel(sfc, SFC_GLB, tmp);
    }
    else
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_GLB);
        tmp |= GLB_TRAN_DIR;
        sfc_writel(sfc, SFC_GLB, tmp);
    }
}


static int set_flash_timing(struct sfc *sfc, uint32_t t_hold, uint32_t t_setup, uint32_t t_shslrd, uint32_t t_shslwr)
{
    uint32_t c_hold;
    uint32_t c_setup;
    uint32_t t_in, c_in, val;
    uint64_t cycle;

    cycle = 1000000000UL / sfc->src_clk;

    c_hold = t_hold / cycle;
    if (c_hold > 0)
        val = c_hold - 1;
    sfc_hold_delay(sfc, val);

    c_setup = t_setup / cycle;
    if(c_setup > 0)
        val = c_setup - 1;
    sfc_setup_delay(sfc, val);

    t_in = max(t_shslrd, t_shslwr);
    c_in = t_in / cycle;
    if(c_in > 0)
        val = c_in - 1;
    sfc_interval_delay(sfc, val);

    return 0;
}

static void sfc_set_length(struct sfc *sfc, uint32_t value)
{
    sfc_writel(sfc, SFC_TRAN_LEN, value);
}

static void sfc_transfer_mode(struct sfc *sfc, uint32_t value)
{
    if (value == 0)
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_GLB);
        tmp &= ~GLB_OP_MODE;
        sfc_writel(sfc, SFC_GLB, tmp);
    }
    else
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_GLB);
        tmp |= GLB_OP_MODE;
        sfc_writel(sfc, SFC_GLB, tmp);
    }
}

static void sfc_read_data(struct sfc *sfc, uint32_t *value)
{
    *value = sfc_readl(sfc, SFC_RM_DR);
}

static void sfc_write_data(struct sfc *sfc, const uint32_t value)
{
    sfc_writel(sfc, SFC_RM_DR, value);
}

uint32_t sfc_fifo_num(struct sfc *sfc)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_SR);
    tmp &= (0x7f << 16);
    tmp = tmp >> 16;
    return tmp;
}

static uint32_t cpu_read_rxfifo(struct sfc *sfc)
{
    uint32_t i;
    uint32_t align_len = 0;
    uint32_t fifo_num = 0;
    uint32_t data[1] = {0};
    uint32_t last_word = 0;

    align_len = RT_ALIGN(sfc->transfer->len, 4);

    if (((align_len - sfc->transfer->cur_len) / 4) > THRESHOLD)
    {
        fifo_num = THRESHOLD;
        last_word = 0;
    }
    else
    {
        /* last aligned THRESHOLD data*/
        if (sfc->transfer->len % 4)
        {
            fifo_num = (align_len - sfc->transfer->cur_len) / 4 - 1;
            last_word = 1;
        }
        else
        {
            fifo_num = (align_len - sfc->transfer->cur_len) / 4;
            last_word = 0;
        }
    }

    for (i = 0; i < fifo_num; i++)
    {
        sfc_read_data(sfc, (uint32_t *) sfc->transfer->data);
        sfc->transfer->data += 4;
        sfc->transfer->cur_len += 4;
    }

    /* last word */
    if (last_word == 1)
    {
        sfc_read_data(sfc, data);
        rt_memcpy((void *) sfc->transfer->data, data, sfc->transfer->len % 4);

        sfc->transfer->data += sfc->transfer->len % 4;
        sfc->transfer->cur_len += 4;
    }

    return 0;
}

static uint32_t cpu_write_txfifo(struct sfc *sfc)
{
    uint32_t i;
    uint32_t align_len = 0;
    uint32_t fifo_num = 0;


    align_len = RT_ALIGN(sfc->transfer->len , 4);

    if (((align_len - sfc->transfer->cur_len) / 4) > THRESHOLD){
        fifo_num = THRESHOLD;
    } else {
        fifo_num = (align_len - sfc->transfer->cur_len) / 4;
    }

    for(i = 0; i < fifo_num; i++) {
        sfc_write_data(sfc, *(uint32_t *)sfc->transfer->data);
        sfc->transfer->data += 4;
        sfc->transfer->cur_len += 4;
    }

    return 0;
}


static int ssi_underrun(struct sfc *sfc)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_SR);
    if(tmp & CLR_UNDER)
        return 1;
    else
        return 0;
}

static int ssi_overrun(struct sfc *sfc)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_SR);
    if(tmp & CLR_OVER)
        return 1;
    else
        return 0;
}

static int rxfifo_rreq(struct sfc *sfc)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_SR);
    if(tmp & CLR_RREQ)
        return 1;
    else
        return 0;
}

static int txfifo_treq(struct sfc *sfc)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_SR);
    if(tmp & CLR_TREQ)
        return 1;
    else
        return 0;
}

static int sfc_end(struct sfc *sfc)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_SR);
    if(tmp & CLR_END)
        return 1;
    else
        return 0;
}
static uint32_t sfc_get_sta_rt(struct sfc *sfc)
{
    return sfc_readl(sfc,SFC_DEV_STA_RT);
}
static uint32_t sfc_get_fsm(struct sfc *sfc)
{
    return sfc_readl(sfc,SFC_FSM);
}
static void sfc_set_addr_length(struct sfc *sfc, uint32_t channel, uint32_t value)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_TRAN_CONF(channel));
    tmp &= ~(ADDR_WIDTH_MSK);
    tmp |= (value << ADDR_WIDTH_OFFSET);
    sfc_writel(sfc, SFC_TRAN_CONF(channel), tmp);
}

static void sfc_cmd_enble(struct sfc *sfc, uint32_t channel, uint32_t value)
{
    if (value == ENABLE)
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_TRAN_CONF(channel));
        tmp |= TRAN_CONF_CMDEN;
        sfc_writel(sfc, SFC_TRAN_CONF(channel), tmp);
    }
    else
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_TRAN_CONF(channel));
        tmp &= ~TRAN_CONF_CMDEN;
        sfc_writel(sfc, SFC_TRAN_CONF(channel), tmp);
    }
}

static void sfc_data_en(struct sfc *sfc, uint32_t channel, uint32_t value)
{
    if (value == 1)
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_TRAN_CONF(channel));
        tmp |= TRAN_CONF_DATEEN;
        sfc_writel(sfc, SFC_TRAN_CONF(channel), tmp);
    }
    else
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_TRAN_CONF(channel));
        tmp &= ~TRAN_CONF_DATEEN;
        sfc_writel(sfc, SFC_TRAN_CONF(channel), tmp);
    }
}

static void sfc_phase_format(struct sfc *sfc, uint32_t channel, uint32_t value)
{
    if (value == 1)
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_TRAN_CONF(channel));
        tmp |= TRAN_CONF_FMAT;
        sfc_writel(sfc, SFC_TRAN_CONF(channel), tmp);
    }
    else
    {
        uint32_t tmp;
        tmp = sfc_readl(sfc, SFC_TRAN_CONF(channel));
        tmp &= ~TRAN_CONF_FMAT;
        sfc_writel(sfc, SFC_TRAN_CONF(channel), tmp);
    }
}

static void sfc_write_cmd(struct sfc *sfc, uint32_t channel, uint32_t value)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_TRAN_CONF(channel));
    tmp &= ~TRAN_CONF_CMD_MSK;
    tmp |= value;
    sfc_writel(sfc, SFC_TRAN_CONF(channel), tmp);
}

static void sfc_dev_addr(struct sfc *sfc, uint32_t channel, uint32_t value)
{
    sfc_writel(sfc, SFC_DEV_ADDR(channel), value);
}


static void sfc_dev_data_dummy_bytes(struct sfc *sfc, uint32_t channel, uint32_t value)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_TRAN_CONF(channel));
    tmp &= ~TRAN_CONF_DMYBITS_MSK;
    tmp |= value << DMYBITS_OFFSET;
    sfc_writel(sfc, SFC_TRAN_CONF(channel), tmp);
}

static void sfc_dev_addr_plus(struct sfc *sfc, uint32_t channel, uint32_t value)
{
    sfc_writel(sfc, SFC_DEV_ADDR_PLUS(channel), value);
}

static void sfc_dev_pollen(struct sfc *sfc, uint32_t channel, uint32_t value)
{
    uint32_t tmp;
    tmp = sfc_readl(sfc, SFC_TRAN_CONF(channel));
    if(value == 1)
        tmp |= TRAN_CONF_POLLEN;
    else
        tmp &= ~(TRAN_CONF_POLLEN);

    sfc_writel(sfc, SFC_TRAN_CONF(channel), tmp);
}

static void sfc_dev_sta_exp(struct sfc *sfc, uint32_t value)
{
    sfc_writel(sfc, SFC_DEV_STA_EXP, value);
}

static void sfc_dev_sta_msk(struct sfc *sfc, uint32_t value)
{
    sfc_writel(sfc, SFC_DEV_STA_MSK, value);
}

static void sfc_enable_all_intc(struct sfc *sfc)
{
    sfc_writel(sfc, SFC_INTC, 0);
}

static void sfc_set_mem_addr(struct sfc *sfc,uint32_t addr )
{
    sfc_writel(sfc, SFC_MEM_ADDR, addr);
}

static int sfc_start_transfer(struct sfc *sfc)
{
    int err;
    sfc_clear_all_intc(sfc);
    sfc_enable_all_intc(sfc);
    sfc_start(sfc);
    err = rt_completion_wait(&sfc->done,RT_TICK_PER_SECOND * 10);
    if (RT_EOK != err)
    {
        sfc_mask_all_intc(sfc);
        sfc_clear_all_intc(sfc);
        SFC_DBG("line:%d Timeout for ACK from SFC device\n", __LINE__);
        return -RT_ETIMEOUT;
    }
    return 0;
}

static void sfc_phase_transfer(struct sfc *sfc,struct sfc_transfer * transfer,uint32_t channel)
{
    sfc_flush_fifo(sfc);
    sfc_set_addr_length(sfc,channel,transfer->addr_len);
    sfc_cmd_enble(sfc,channel,ENABLE);
    sfc_write_cmd(sfc,channel,transfer->cmd_info->cmd);
    sfc_dev_data_dummy_bytes(sfc,channel,transfer->data_dummy_bits);
    sfc_data_en(sfc,channel,transfer->cmd_info->dataen);
    sfc_dev_addr(sfc, channel,transfer->addr);
    sfc_dev_addr_plus(sfc,channel,transfer->addr_plus);
    sfc_mode(sfc,channel,transfer->sfc_mode);
    sfc_phase_format(sfc,channel,0);/*default 0,dummy bits is blow the addr*/
}
static void common_cmd_request_transfer(struct sfc *sfc,struct sfc_transfer *transfer,uint32_t channel)
{
    sfc_phase_transfer(sfc,transfer,channel);
    sfc_dev_sta_exp(sfc,0);
    sfc_dev_sta_msk(sfc,0);
    sfc_dev_pollen(sfc,channel,DISABLE);
}

static void poll_cmd_request_transfer(struct sfc *sfc,struct sfc_transfer *transfer,uint32_t channel)
{
    struct cmd_info *cmd = transfer->cmd_info;
    sfc_phase_transfer(sfc,transfer,channel);
    sfc_dev_sta_exp(sfc,cmd->sta_exp);
    sfc_dev_sta_msk(sfc,cmd->sta_msk);
    sfc_dev_pollen(sfc,channel,ENABLE);
}
static void sfc_glb_info_config(struct sfc *sfc,struct sfc_transfer *transfer)
{
    sfc_transfer_direction(sfc, transfer->direction);
    if ((transfer->ops_mode == DMA_OPS))
    {
        sfc_set_length(sfc, transfer->len);
        if (transfer->direction == GLB_TRAN_DIR_READ)
            r4k_dma_cache_sync((uint32_t) transfer->data, transfer->len,
                               DMA_FROM_DEVICE);
        else
            r4k_dma_cache_sync((uint32_t) transfer->data, transfer->len,
                                DMA_TO_DEVICE);
        sfc_set_mem_addr(sfc, PHYS(transfer->data));
        sfc_transfer_mode(sfc, DMA_MODE);
    }
    else
    {
        sfc_set_length(sfc, transfer->len);
        sfc_set_mem_addr(sfc, 0);
        sfc_transfer_mode(sfc, SLAVE_MODE);
    }
}

#ifdef DEBUG
static void  dump_transfer(struct sfc_transfer *xfer,uint32_t num)
{
    rt_kprintf("\n");
    rt_kprintf("cmd[%d].cmd = 0x%02x\n",num,xfer->cmd_info->cmd);
    rt_kprintf("cmd[%d].addr_len = %d\n",num,xfer->addr_len);
    rt_kprintf("cmd[%d].dummy_byte = %d\n",num,xfer->data_dummy_bits);
    rt_kprintf("cmd[%d].dataen = %d\n",num,xfer->cmd_info->dataen);
    rt_kprintf("cmd[%d].sta_exp = %d\n",num,xfer->cmd_info->sta_exp);
    rt_kprintf("cmd[%d].sta_msk = %d\n",num,xfer->cmd_info->sta_msk);


    rt_kprintf("transfer[%d].addr = 0x%08x\n",num,xfer->addr);
    rt_kprintf("transfer[%d].len = %d\n",num,xfer->len);
    rt_kprintf("transfer[%d].data = 0x%p\n",num,xfer->data);
    rt_kprintf("transfer[%d].direction = %d\n",num,xfer->direction);
    rt_kprintf("transfer[%d].sfc_mode = %d\n",num,xfer->sfc_mode);
    rt_kprintf("transfer[%d].ops_mode = %d\n",num,xfer->ops_mode);
}
#endif

static int sfc_sync(struct sfc *sfc, struct sfc_message *message)
{
    struct sfc_transfer *xfer;
    int phase_num = 0,ret = 0;

    sfc_set_length(sfc, 0);
    
    rt_list_for_each_entry(xfer, &message->transfers, transfer_list)
    {
        if (xfer->cmd_info->sta_msk == 0)
        {
            common_cmd_request_transfer(sfc, xfer, phase_num);
        }
        else
        {
            poll_cmd_request_transfer(sfc, xfer, phase_num);
        }
        if (xfer->addr_len || xfer->len)
            sfc_glb_info_config(sfc, xfer);
        phase_num++;
        message->actual_length += xfer->len;
        if (xfer->len > 0)
            sfc->transfer = xfer;
    }
    sfc_set_phase_num(sfc,phase_num);
    ret = sfc_start_transfer(sfc);
    rt_list_remove(&message->transfers);
    return ret;
}

static void sfc_transfer_del(struct sfc_transfer *t)
{
    rt_list_remove(&t->transfer_list);
}

static void sfc_message_add_tail(struct sfc_transfer *t, struct sfc_message *m)
{
    rt_list_insert_before(&m->transfers, &t->transfer_list);
}

static void sfc_message_init(struct sfc_message *m)
{
    rt_memset(m, 0, sizeof *m);
    rt_list_init(&m->transfers);
}

static void jz_sfc_pio_irq(int vector,void *param)
{
    struct sfc *sfc = (struct sfc *)param;
    if (ssi_underrun(sfc))
    {
        sfc_clear_under_intc(sfc);
        rt_completion_done(&sfc->done);
        return ;
    }

    if (ssi_overrun(sfc))
    {
        sfc_clear_over_intc(sfc);
        rt_completion_done(&sfc->done);
        return ;
    }

    if (rxfifo_rreq(sfc))
    {
        sfc_clear_rreq_intc(sfc);
        cpu_read_rxfifo(sfc);
        return ;
    }

    if (txfifo_treq(sfc))
    {
        sfc_clear_treq_intc(sfc);
        cpu_write_txfifo(sfc);
        return ;
    }

    if (sfc_end(sfc))
    {
        sfc_mask_all_intc(sfc);
        sfc_clear_end_intc(sfc);
        rt_completion_done(&sfc->done);
        return ;
    }
}


static int jz_sfc_init_setup(struct sfc *sfc)
{
    sfc_init(sfc);
    sfc_stop(sfc);

    /*set hold high*/
    sfc_hold_invalid_value(sfc, 1);
    /*set wp high*/
    sfc_wp_invalid_value(sfc, 1);

    sfc_clear_all_intc(sfc);
    sfc_mask_all_intc(sfc);

    sfc_threshold(sfc, sfc->threshold);
    /*config the sfc pin init state*/
    sfc_clock_phase(sfc, 0);
    sfc_clock_polarity(sfc, 0);
    sfc_ce_invalid_value(sfc, 1);


    sfc_transfer_mode(sfc, SLAVE_MODE);
    if (sfc->src_clk >= 100000000)
    {
        sfc_smp_delay(sfc, DEV_CONF_HALF_CYCLE_DELAY);
    }
    return 0;
}

static struct sfc* jz_sfc_init(void)
{
    struct sfc *sfc = (struct sfc *)rt_malloc(sizeof(struct sfc));
    if(sfc == RT_NULL)
        return RT_NULL;

    sfc->iomem = (void *)SFC_BASE;
    sfc->irq  = IRQ_SFC;
    sfc->clk = clk_get("cgu_ssi");
    sfc->clk_gate =  clk_get("sfc");
    sfc->src_clk = 100000000L;
    if(clk_get_rate(sfc->clk) >= sfc->src_clk)
        clk_set_rate(sfc->clk, sfc->src_clk);
    else
        clk_set_rate(sfc->clk, sfc->src_clk);

    clk_enable(sfc->clk);
    clk_enable(sfc->clk_gate);

    sfc->threshold = THRESHOLD;

    /* Init IPC */
    rt_completion_init(&(sfc->done));

    /* Request SFC IRQ */
    rt_hw_interrupt_install(sfc->irq,jz_sfc_pio_irq,sfc,"SFC");
    rt_hw_interrupt_umask(sfc->irq);

    /* SFC controller initializations for SFC */
    jz_sfc_init_setup(sfc);
    rt_completion_init(&sfc->done);

    return sfc;
}



static int sfc_flash_read_id(struct sfc_flash *flash, uint8_t command, uint32_t addr, uint32_t addr_len, size_t len, uint32_t dummy_byte)
{

    struct sfc_transfer transfer;
    struct sfc_message message;
    struct cmd_info cmd;
    int ret;
    uint32_t chip_id = 0;

    sfc_message_init(&message);
    rt_memset(&transfer, 0, sizeof(transfer));
    rt_memset(&cmd, 0, sizeof(cmd));

    cmd.cmd = command;
    cmd.dataen = ENABLE;

    transfer.addr_len = addr_len;
    transfer.data_dummy_bits = dummy_byte;
    transfer.addr = addr;
    transfer.len = len;
    transfer.data =(uint8_t *)&chip_id;
    transfer.ops_mode = CPU_OPS;
    transfer.sfc_mode = TM_STD_SPI;
    transfer.direction = GLB_TRAN_DIR_READ;
    transfer.cmd_info = &cmd;
    sfc_message_add_tail(&transfer, &message);


    ret = sfc_sync(flash->sfc, &message);
    if (ret)
    {
        SFC_DBG("sfc_sync error ! %s %s %d\n", __FILE__, __func__, __LINE__);
        ret = -RT_EIO;
    }

    return chip_id & 0x00ffffff;
}


static uint32_t sfc_flash_do_read(struct sfc_flash *flash,uint8_t command,uint32_t addr,uint32_t addr_len,uint8_t *buf,size_t len,uint32_t dummy_byte)
{
    struct sfc_transfer transfer;
    struct sfc_message message;
    struct cmd_info cmd;
    int ret;

    sfc_message_init(&message);
    rt_memset(&transfer, 0, sizeof(transfer));
    rt_memset(&cmd, 0, sizeof(cmd));

    cmd.cmd = command;
    cmd.dataen = ENABLE;

    transfer.addr_len = addr_len;
    transfer.data_dummy_bits = dummy_byte;
    transfer.addr = addr;
    transfer.len = len;
    transfer.data = buf;
    transfer.cur_len = 0;
    if(len >= L2CACHE_ALIGN_SIZE)
        transfer.ops_mode = DMA_OPS;
    else
        transfer.ops_mode = CPU_OPS;

    transfer.sfc_mode = flash->sfc_mode;
    transfer.direction = GLB_TRAN_DIR_READ;
    transfer.cmd_info = &cmd;
    sfc_message_add_tail(&transfer, &message);

    ret = sfc_sync(flash->sfc, &message);
    if (ret)
    {
        SFC_DBG("sfc_sync error ! %s %s %d\n", __FILE__, __func__, __LINE__);
        ret = -RT_EIO;
    }
    /*fix the cache line problem,when use jffs2 filesystem must be flush cache twice*/
    if(transfer.ops_mode == DMA_OPS)
        r4k_dma_cache_sync((rt_base_t)buf, len, DMA_FROM_DEVICE);

    return message.actual_length;
}

static unsigned  int sfc_flash_do_write(struct sfc_flash *flash,uint8_t command,uint32_t addr,uint32_t addr_len,const uint8_t *buf,size_t len,uint32_t dummy_byte)
{
    struct sfc_transfer transfer[3];
    struct sfc_message message;
    struct cmd_info cmd[3];
    int ret;

    sfc_message_init(&message);
    rt_memset(&transfer, 0, sizeof(transfer));
    rt_memset(&cmd, 0, sizeof(cmd));

    /* write enable */
    cmd[0].cmd = CMD_WREN;
    cmd[0].dataen = DISABLE;

    transfer[0].cmd_info = &cmd[0];
    transfer[0].sfc_mode = flash->sfc_mode;
    sfc_message_add_tail(&transfer[0], &message);

    /* write ops */
    cmd[1].cmd = command;
    cmd[1].dataen = ENABLE;

    transfer[1].addr = addr;
    transfer[1].addr_len = addr_len;
    transfer[1].len = len;
    transfer[1].cur_len = 0;
    transfer[1].data_dummy_bits = dummy_byte;
    transfer[1].data = buf;
    if(len >= L2CACHE_ALIGN_SIZE)
        transfer[1].ops_mode = DMA_OPS;
    else
        transfer[1].ops_mode = CPU_OPS;
    transfer[1].sfc_mode = flash->sfc_mode;
    transfer[1].direction = GLB_TRAN_DIR_WRITE;
    transfer[1].cmd_info = &cmd[1];
    sfc_message_add_tail(&transfer[1], &message);

    cmd[2].cmd = CMD_RDSR;
    cmd[2].dataen = DISABLE;
    cmd[2].sta_exp = 0;
    cmd[2].sta_msk = 0x1;

    transfer[2].cmd_info = &cmd[2];
    sfc_message_add_tail(&transfer[2], &message);

    ret = sfc_sync(flash->sfc, &message);
    if (ret)
    {
        SFC_DBG("sfc_sync error ! %s %s %d\n", __FILE__, __func__, __LINE__);
        ret = -RT_EIO;
    }

    return message.actual_length;
}

#ifdef SFC_USE_QUAD
static int sfc_flash_set_quad_mode(struct sfc_flash *flash)
{
    uint8_t command;
    uint32_t sent_data,len,dummy_byte;
    int ret;

    struct sfc_transfer transfer[3];
    struct sfc_message message;
    struct cmd_info cmd[3];


    if (flash->quad_mode == NULL)
    {
        SFC_DBG("quad info is null, use standard spi mode\n");
        flash->sfc_mode = TM_STD_SPI;
        return -1;
    }

    command     = flash->quad_mode->WRSR_CMD;
    sent_data   = flash->quad_mode->WRSR_DATE;
    len         = flash->quad_mode->WD_DATE_SIZE;
    dummy_byte  = flash->quad_mode->dummy_byte;

    sfc_message_init(&message);
    rt_memset(&transfer, 0, sizeof(transfer));
    rt_memset(&cmd, 0, sizeof(cmd));

    /* write enable */
    cmd[0].cmd = CMD_WREN;
    cmd[0].dataen = DISABLE;

    transfer[0].cmd_info = &cmd[0];
    transfer[0].sfc_mode = TM_STD_SPI;
    sfc_message_add_tail(&transfer[0], &message);

    /* write ops */
    cmd[1].cmd = command;
    cmd[1].dataen = ENABLE;

    transfer[1].len = len;
    transfer[1].data = (const uint8_t *)&sent_data;
    transfer[1].data_dummy_bits = dummy_byte;
    transfer[1].ops_mode = CPU_OPS;
    transfer[1].sfc_mode = TM_STD_SPI;
    transfer[1].direction = GLB_TRAN_DIR_WRITE;
    transfer[1].cmd_info = &cmd[1];
    sfc_message_add_tail(&transfer[1], &message);

    cmd[2].cmd = flash->quad_mode->RDSR_CMD;
    cmd[2].dataen = DISABLE;
    cmd[2].sta_exp = 0x2;
    cmd[2].sta_msk = 0x2;

    transfer[2].data_dummy_bits = 0;
    transfer[2].cmd_info = &cmd[2];
    sfc_message_add_tail(&transfer[2], &message);

    ret = sfc_sync(flash->sfc, &message);
    if (ret)
    {
        flash->sfc_mode = TM_STD_SPI;
        SFC_DBG("sfc_sync error ! %s %s %d\n", __FILE__, __func__, __LINE__);
        ret = -RT_EIO;
    }
    else
    {
        flash->sfc_mode = flash->quad_mode->sfc_mode;
    }
    return 0;
}
#endif

static int sfc_flash_write(struct sfc_flash *flash, rt_off_t to, size_t len, const uint8_t *buf)
{
    uint8_t command;
    int dummy_byte = 0;
    uint32_t s_len = 0, f_len = 0, a_len = 0;

#ifdef SFC_USE_QUAD
    if((flash->sfc_mode == TM_QI_QO_SPI) || (flash->sfc_mode == TM_QIO_SPI) || (flash->sfc_mode == TM_FULL_QIO_SPI))
    {
        command = CMD_PP;
    }
    else
    {
        command = CMD_PP;
    }
#else
    command = CMD_PP;
#endif

    if (len > L2CACHE_ALIGN_SIZE)
    {
        s_len = RT_ALIGN((uint32_t )buf, L2CACHE_ALIGN_SIZE) - (uint32_t)buf;
        if (s_len)
        {
            sfc_flash_do_write(flash, command, (uint32_t) to, flash->addrsize, buf, s_len, dummy_byte);
        }

        a_len = (len - s_len) - (len - s_len) % L2CACHE_ALIGN_SIZE;
        if (a_len)
        {
            sfc_flash_do_write(flash, command, (uint32_t) to + s_len,
                         flash->addrsize, &buf[s_len], a_len, dummy_byte);
        }

        f_len = len - s_len - a_len;
        if (f_len)
        {
            sfc_flash_do_write(flash, command, (uint32_t) to + s_len + a_len,
                         flash->addrsize, &buf[s_len + a_len], f_len,
                         dummy_byte);
        }
    }
    else
    {
        sfc_flash_do_write(flash, command, (uint32_t) to, flash->addrsize,
                     buf, len, dummy_byte);
    }

    return len;
}

static int sfc_flash_read_cacheline_align(struct sfc_flash *flash,uint8_t command,uint32_t addr,int addr_len,uint8_t *buf,size_t len,int dummy_byte)
{
    uint32_t ret = 0;
    uint32_t s_len = 0, f_len = 0, a_len = 0;

    /**
     * s_len : start not align length
     * a_len : middle align length
     * f_len : end not align length
     */
    if (len > L2CACHE_ALIGN_SIZE)
    {
        s_len = RT_ALIGN((uint32_t )buf, L2CACHE_ALIGN_SIZE) - (uint32_t)buf;
        if (s_len)
        {
            ret += sfc_flash_do_read(flash, command, (uint32_t) addr,
                               flash->addrsize, buf, s_len, dummy_byte);
        }

        a_len = (len - s_len) - (len - s_len) % L2CACHE_ALIGN_SIZE;
        if (a_len)
        {
            ret += sfc_flash_do_read(flash, command, (uint32_t) addr + s_len,
                               flash->addrsize, &buf[s_len], a_len,
                               dummy_byte);
        }

        f_len = len - s_len - a_len;
        if (f_len)
        {
            ret += sfc_flash_do_read(flash, command,
                               (uint32_t) addr + s_len + a_len,
                               flash->addrsize, &buf[s_len + a_len], f_len,
                               dummy_byte);
        }
    } else {
        ret = sfc_flash_do_read(flash, command, (uint32_t)addr, flash->addrsize, buf, len, dummy_byte);
    }

    return ret;
}

static int sfc_flash_read(struct sfc_flash *flash, rt_off_t from, size_t len, uint8_t *buf)
{
   uint8_t command;
   int dummy_byte;
   int tmp_len = 0, current_len = 0;

#ifdef SFC_USE_QUAD
    if((flash->sfc_mode == TM_QI_QO_SPI) || (flash->sfc_mode == TM_QIO_SPI) || (flash->sfc_mode == TM_FULL_QIO_SPI))
    {
        command = flash->quad_mode->cmd_read;
        dummy_byte = flash->quad_mode->dummy_byte;
    }
    else
    {
        command = CMD_READ;
        dummy_byte = 0;
    }
#else
   command = CMD_READ;
   dummy_byte = 0;
#endif

    while (len)
    {
        tmp_len = sfc_flash_read_cacheline_align(flash, command,
                                           (uint32_t) from + current_len,
                                           flash->addrsize,
                                           &buf[current_len], len, dummy_byte);
        current_len += tmp_len;
        len -= tmp_len;
    }

   return current_len;
}

int sfc_norflash_set_addr_width_4byte(struct sfc_flash *flash,int on)
{
    struct sfc_transfer transfer;
    struct sfc_message message;
    struct cmd_info cmd;
    int ret;

    sfc_message_init(&message);
    rt_memset(&transfer, 0, sizeof(transfer));
    rt_memset(&cmd, 0, sizeof(cmd));

    cmd.cmd = CMD_EN4B;
    cmd.dataen = DISABLE;

    transfer.data_dummy_bits = 0;
    transfer.cmd_info = &cmd;
    sfc_message_add_tail(&transfer, &message);

    ret = sfc_sync(flash->sfc, &message);
    if (ret)
    {
        SFC_DBG("sfc_sync error ! %s %s %d\n", __FILE__, __func__, __LINE__);

        ret = -RT_EIO;
    }
    return 0;
}

size_t sfc_norflash_read(struct sfc_flash *flash, rt_off_t from, uint8_t *buf, size_t len)
{
    size_t retlen;
    rt_mutex_take(&flash->lock,RT_WAITING_FOREVER);
    retlen = sfc_flash_read(flash, from, len, buf);
    rt_mutex_release(&flash->lock);

    return retlen;
}

int sfc_norflash_read_params(struct sfc_flash *flash, rt_off_t from, size_t len, uint8_t *buf)
{
    struct sfc_transfer transfer;
    struct sfc_message message;
    struct cmd_info cmd;
    uint8_t command;
    int dummy_byte = 0,ret;


    command = CMD_READ;
    rt_mutex_take(&flash->lock,RT_WAITING_FOREVER);

    sfc_message_init(&message);
    rt_memset(&transfer, 0, sizeof(transfer));
    rt_memset(&cmd, 0, sizeof(cmd));

    cmd.cmd = command;
    cmd.dataen = ENABLE;

    transfer.addr = (uint32_t)from;
    transfer.len = len;
    transfer.data = buf;
    transfer.addr_len = DEFAULT_ADDRSIZE;
    transfer.data_dummy_bits = dummy_byte;
    transfer.ops_mode = CPU_OPS;
    transfer.direction = GLB_TRAN_DIR_READ;
    transfer.sfc_mode = TM_STD_SPI;
    transfer.cmd_info = &cmd;
    sfc_message_add_tail(&transfer, &message);

    ret = sfc_sync(flash->sfc, &message);
    if (ret)
    {
        SFC_DBG("sfc_sync error ! %s %s %d\n", __FILE__, __func__, __LINE__);
        ret = -RT_EIO;
    }

    /*fix the cache line problem,when use jffs2 filesystem must be flush cache twice*/
    if(transfer.ops_mode == DMA_OPS)
        r4k_dma_cache_sync((rt_ubase_t)buf,len, DMA_FROM_DEVICE);
    rt_mutex_release(&flash->lock);
    return 0;
}

int sfc_norflash_erase_sector(struct sfc_flash *flash, uint32_t addr)
{
    uint8_t command;
    struct sfc_transfer transfer[3];
    struct sfc_message message;
    struct cmd_info cmd[3];
    int ret;

    rt_mutex_take(&flash->lock,RT_WAITING_FOREVER);

    sfc_message_init(&message);
    rt_memset(&transfer, 0, sizeof(transfer));
    rt_memset(&cmd, 0, sizeof(cmd));

    /* write enable */
    cmd[0].cmd = CMD_WREN;
    cmd[0].dataen = DISABLE;

    transfer[0].sfc_mode = TM_STD_SPI;
    transfer[0].cmd_info = &cmd[0];
    sfc_message_add_tail(&transfer[0], &message);

    switch (flash->erasesize)
    {
        case 0x1000:
            command = CMD_BE_4K;
        break;
        case 0x8000:
            command = CMD_BE_32K;
        break;
        case 0x10000:
            command = CMD_BE_64K;
        break;
    }

    /* erase ops */
    cmd[1].cmd = command;
    cmd[1].dataen = DISABLE;

    transfer[1].addr_len = flash->addrsize;
    transfer[1].data_dummy_bits = 0;
    transfer[1].addr = addr;
    transfer[1].sfc_mode = TM_STD_SPI;
    transfer[1].direction = GLB_TRAN_DIR_WRITE;
    transfer[1].cmd_info = &cmd[1];
    sfc_message_add_tail(&transfer[1], &message);

    cmd[2].cmd = CMD_RDSR;
    cmd[2].dataen = DISABLE;
    cmd[2].sta_exp = 0;
    cmd[2].sta_msk = 0x1;

    transfer[2].cmd_info = &cmd[2];
    sfc_message_add_tail(&transfer[2], &message);

    ret = sfc_sync(flash->sfc, &message);
    if (ret)
    {
        SFC_DBG("sfc_sync error ! %s %s %d\n", __FILE__, __func__, __LINE__);
        ret = -RT_EIO;
    }

    rt_mutex_release(&flash->lock);
    return 0;
}

size_t sfc_norflash_write(struct sfc_flash *flash, rt_off_t to,  const uint8_t *buf, size_t len)
{
    size_t retlen;
    u32 page_offset, actual_len;
    int ret;

    rt_mutex_take(&flash->lock,RT_WAITING_FOREVER);

    page_offset = to & (flash->pagesize - 1);
    /* do all the bytes fit onto one page? */
    if (page_offset + len <= flash->pagesize)
    {
        ret = sfc_flash_write(flash, to, len, buf);
        retlen = ret;
    }
    else
    {
        u32 i;

        /* the size of data remaining on the first page */
        actual_len = flash->pagesize - page_offset;
        ret = sfc_flash_write(flash,to,actual_len,buf);
        retlen += ret;

        /* write everything in flash->page_size chunks */
        for (i = actual_len; i < len; i += flash->writesize)
        {
            actual_len = len - i;
            if (actual_len >= flash->writesize)
                actual_len = flash->writesize;

            ret = sfc_flash_write(flash, to + i, actual_len, buf + i);
            retlen += ret;
        }
    }
    rt_mutex_release(&flash->lock);
    return retlen;
}

int sfc_norflash_probe(struct sfc_flash *flash)
{
    struct sfc *sfc;

    sfc = flash->sfc = jz_sfc_init();
    if(sfc == RT_NULL)
        return -RT_EIO;

    /* GPIO Initialize (SFC FUNC1) */
    gpio_set_func(GPIO_PORT_A,GPIO_Pin_26,GPIO_FUNC_1);     //CLK
    gpio_set_func(GPIO_PORT_A,GPIO_Pin_27,GPIO_FUNC_1);     //CE
    gpio_set_func(GPIO_PORT_A,GPIO_Pin_28,GPIO_FUNC_1);     //DR
    gpio_set_func(GPIO_PORT_A,GPIO_Pin_29,GPIO_FUNC_1);     //DT
    gpio_set_func(GPIO_PORT_A,GPIO_Pin_30,GPIO_FUNC_1);     //WP
    gpio_set_func(GPIO_PORT_A,GPIO_Pin_31,GPIO_FUNC_1);     //HOLD

    /* init mutex */
    if(rt_mutex_init(&(flash->lock),"norLock",RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        SFC_DBG("Init mutex error\n");
        RT_ASSERT(0);
    }

    rt_mutex_take(&(flash->lock),RT_WAITING_FOREVER);

    //get ID
    {
        uint8_t command;
        int dummy_byte = 0;
        int addr_len = 0;
        int len = 3;
        int addr = 0;
        int id;
        int i;
        struct spi_nor_platform_data *flash_info;
        struct spi_board_info *binfo;

        command = CMD_RDID;

        SFC_DBG("Get ID:\n");
        id = sfc_flash_read_id(flash, command, addr, addr_len, len, dummy_byte);
        id = ((id & 0xff) << 16) | (((id >> 8) & 0xff) << 8) | ((id >> 16) & 0xff);
        SFC_DBG("id = %06x\n",id);

        flash->id = id;
    }

#if 0
    //get UID
    {
        int i;
        sfc_flash_do_read(flash,CMD_RUID,0,3,flash->uid,8,8);
        SFC_DBG("uid = ");
        for (i = 0; i < 8; ++i) {
            SFC_DBG("%02x ",flash->uid[i]);
        }
        SFC_DBG("\n");
    }
#endif

    rt_mutex_release(&(flash->lock));

    return 0;
}
