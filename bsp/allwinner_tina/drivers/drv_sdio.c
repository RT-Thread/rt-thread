/*
 * File      : drv_sdio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */
#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <string.h>

#include "drv_sdio.h"
#include "interrupt.h"
#include "mmu.h"
#include "drv_gpio.h"
#include "drv_clock.h"


#define DBG_TAG  "MMC"
// #define DBG_LVL DBG_LOG    
// #define DBG_LVL DBG_INFO   
#define DBG_LVL DBG_WARNING
// #define DBG_LVL DBG_ERROR  
#include <rtdbg.h>

#ifdef RT_USING_SDIO
#define CONFIG_MMC_USE_DMA
#define DMA_ALIGN       (32U)

struct mmc_xfe_des
{
    rt_uint32_t size;    /* block size  */
	rt_uint32_t num;     /* block num   */
	rt_uint8_t *buff;    /* buff addr   */
	rt_uint32_t flag;    /* write or read or stream */
#define MMC_DATA_WRITE	(1 << 0)
#define MMC_DATA_READ	(1 << 1)
#define MMC_DATA_STREAM	(1 << 2)
};

struct mmc_flag
{
    volatile rt_uint32_t risr;
    volatile rt_uint32_t idst;
};

struct sdio_drv
{
    struct rt_mmcsd_host *host;
    struct rt_mmcsd_req  *req;
    struct rt_semaphore rt_sem;
    struct mmc_xfe_des xfe;
    struct mmc_flag flag;
    tina_mmc_t mmc_des;
    rt_uint8_t *mmc_buf;
    rt_uint8_t usedma;
    
};

#ifdef CONFIG_MMC_USE_DMA
#ifdef TINA_USING_SDIO0
ALIGN(32) static rt_uint8_t dma_buffer[64 * 1024];
#endif
#endif

static void mmc_request_end(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req);

static void mmc_delay_us(int us)
{
    volatile unsigned int temp;

    while (us--)
    {
        temp = 0x2f;
        while (temp--)
        {
            temp = temp;
        };
    }
}

static void mmc_dump_errinfo(unsigned int err)
{
    LOG_E("[err]:0x%08x, %s%s%s%s%s%s%s%s%s%s%s",
               err,
               err & SDXC_RespErr     ? " RE"     : "",
               err & SDXC_RespCRCErr  ? " RCE"    : "",
               err & SDXC_DataCRCErr  ? " DCE"    : "",
               err & SDXC_RespTimeout ? " RTO"    : "",
               err & SDXC_DataTimeout ? " DTO"    : "",
               err & SDXC_DataStarve  ? " DS"     : "",
               err & SDXC_FIFORunErr  ? " FE"     : "",
               err & SDXC_HardWLocked ? " HL"     : "",
               err & SDXC_StartBitErr ? " SBE"    : "",
               err & SDXC_EndBitErr   ? " EBE"    : "",
               err == 0  ? " STO"    : ""
              );
}

static int mmc_update_clk(tina_mmc_t mmc)
{
    rt_uint32_t cmd;
    rt_uint32_t timeout = 2000000;

    /* cmd load */
    cmd = SDXC_LOAD_CMD | SDXC_UPDATE_CLOCK_CMD | SDXC_WAIT_OVER_CMD;
    mmc->cmdr_reg = cmd;
    /* while load success */
    while ((mmc->cmdr_reg & SDXC_LOAD_CMD) && (--timeout))
    {
        mmc_delay_us(1);
    }
    if (!timeout)
    {
        LOG_E("mmc update clk failed");
        return -RT_ERROR;
    }
    /* clean interrupt */
    mmc->risr_reg = mmc->risr_reg;
    return RT_EOK;
}
    
static rt_err_t mmc_trans_data_by_dma(tina_mmc_t mmc, struct mmc_xfe_des *xfe)
{
    ALIGN(32) static struct mmc_des_v4p1 pdes[128];  // mast ALIGN(32)
    unsigned i, rval;
    unsigned des_idx;
    unsigned length = xfe->size * xfe->num;
    unsigned buff_frag_num = length >> SDXC_DES_NUM_SHIFT;
    unsigned remain = length & (SDXC_DES_BUFFER_MAX_LEN - 1);
    
    if (remain)
    {
        buff_frag_num ++;
    }
    else
    {
        remain = SDXC_DES_BUFFER_MAX_LEN;
    }
    memset(pdes, 0, sizeof(pdes));
    mmu_clean_dcache((rt_uint32_t)(xfe->buff), length);
    for (i = 0, des_idx = 0; i < buff_frag_num; i++, des_idx++) 
    {
        // memset((void*)&pdes[des_idx], 0, sizeof(struct mmc_v4p1));
        pdes[des_idx].des_chain = 1;
        pdes[des_idx].own = 1;
        pdes[des_idx].dic = 1;
        if ((buff_frag_num > 1) && (i != buff_frag_num - 1))
        {
            pdes[des_idx].data_buf1_sz = SDXC_DES_BUFFER_MAX_LEN;
        }
        else
        {
            pdes[des_idx].data_buf1_sz = remain;
        }
        pdes[des_idx].buf_addr_ptr1 = (unsigned long)(xfe->buff) + i * SDXC_DES_BUFFER_MAX_LEN;
        if (i == 0)
        {
            pdes[des_idx].first_des = 1;
        }

        if (i == (buff_frag_num - 1))
        {
            pdes[des_idx].dic = 0;
            pdes[des_idx].last_des = 1;
            pdes[des_idx].end_of_ring = 1;
            pdes[des_idx].buf_addr_ptr2 = 0;
        } 
        else 
        {
            pdes[des_idx].buf_addr_ptr2 = (unsigned long)&pdes[des_idx+1];
        }

        LOG_D("frag %d, remain %d, des[%d](%08x): " \
            "[0] = %08x, [1] = %08x, [2] = %08x, [3] = %08x", \
            i, remain, des_idx, (unsigned int)&pdes[des_idx],
            (unsigned int)((unsigned int*)&pdes[des_idx])[0], (unsigned int)((unsigned int*)&pdes[des_idx])[1],
            (unsigned int)((unsigned int*)&pdes[des_idx])[2], (unsigned int)((unsigned int*)&pdes[des_idx])[3]);
    }
    mmu_clean_dcache((rt_uint32_t)pdes, sizeof(struct mmc_des_v4p1) * (des_idx + 1));

    /*
     * GCTRLREG
     * GCTRL[2] : DMA reset
     * GCTRL[5] : DMA enable
     *
     * IDMACREG
     * IDMAC[0] : IDMA soft reset
     * IDMAC[1] : IDMA fix burst flag
     * IDMAC[7] : IDMA on
     *
     * IDIECREG
     * IDIE[0]  : IDMA transmit interrupt flag
     * IDIE[1]  : IDMA receive interrupt flag
     */
    rval = mmc->gctl_reg;
    mmc->gctl_reg = rval | (1 << 5) | (1 << 2); /* dma enable           */
    mmc->dmac_reg = (1 << 0);                   /* idma reset           */
    while(mmc->dmac_reg & 0x1) {};              /* wait idma reset done */
    mmc->dmac_reg = (1 << 1) | (1 << 7);        /* idma on              */
    rval = mmc->idie_reg & (~3);
    if (xfe->flag == MMC_DATA_WRITE)
        rval |= (1 << 0);        
    else
        rval |= (1 << 1);
    mmc->idie_reg = rval;
    mmc->dlba_reg = (unsigned long)pdes;
    mmc->fwlr_reg = (2U << 28) | (7U << 16) | 8;

    return 0;
}

static rt_err_t mmc_trans_data_by_cpu(tina_mmc_t mmc, struct mmc_xfe_des *xfe)
{
    unsigned i;
    unsigned byte_cnt = xfe->size * xfe->num;
    unsigned *buff = (unsigned *)(xfe->buff);
    volatile unsigned timeout = 2000000;

    if (xfe->flag == MMC_DATA_WRITE)
    {
        for (i = 0; i < (byte_cnt >> 2); i++) 
        {
            while(--timeout && (mmc->star_reg & (1 << 3)));

            if (timeout <= 0)
            {
                LOG_E("write data by cpu failed status:0x%08x", mmc->star_reg);
                return -RT_ERROR;
            }
            mmc->fifo_reg = buff[i];
            timeout = 2000000;
        }
    }
    else
    {
        for (i = 0; i < (byte_cnt >> 2); i++) 
        {
            while(--timeout && (mmc->star_reg & (1 << 2)));

            if (timeout <= 0)
            {
                LOG_E("read data by cpu failed status:0x%08x", mmc->star_reg);
                return -RT_ERROR;
            }
            buff[i] = mmc->fifo_reg;
            timeout = 2000000;
        }
    }

    return RT_EOK;
}

static rt_err_t mmc_config_clock(tina_mmc_t mmc, int clk)
{
    rt_uint32_t rval = 0;

    /* disable card clock */
    rval = mmc->ckcr_reg;
    rval &= ~(1 << 16);
    mmc->ckcr_reg = rval;
    if (mmc_update_clk(mmc) != RT_EOK)
    {
        LOG_E("clk update fail line:%d", __LINE__);
        return -RT_ERROR;
    }

    if (mmc == MMC0)
    {
        mmc_set_clk(SDMMC0, clk);
    }
    else
    {
        mmc_set_clk(SDMMC1, clk);
    }
    
    /* Re-enable card clock */
    rval = mmc->ckcr_reg;
    rval |=  (0x1 << 16); //(3 << 16);
    mmc->ckcr_reg = rval;
    if(mmc_update_clk(mmc) != RT_EOK)
    {
        LOG_E("clk update fail line:%d", __LINE__);
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t mmc_set_ios(tina_mmc_t mmc, int clk, int bus_width)
{
    LOG_D("mmc set io bus width:%d clock:%d", \
        (bus_width == MMCSD_BUS_WIDTH_8 ? 8 : (bus_width == MMCSD_BUS_WIDTH_4 ? 4 : 1)), clk);
    /* change clock */
    if (clk && (mmc_config_clock(mmc, clk) != RT_EOK))
    {
        LOG_E("update clock failed");
        return -RT_ERROR;
    }

    /* Change bus width */
    if (bus_width == MMCSD_BUS_WIDTH_8)
    {
        mmc->bwdr_reg = 2;
    }
    else if (bus_width == MMCSD_BUS_WIDTH_4)
    {
        mmc->bwdr_reg = 1;
    }
    else
    {
        mmc->bwdr_reg = 0;
    }

    return RT_EOK;
}

static int mmc_send_cmd(struct rt_mmcsd_host *host, struct rt_mmcsd_cmd *cmd)
{

    unsigned int cmdval  = 0x80000000;
    signed int timeout   = 0;
    int err              = 0;
    unsigned int status  = 0;
    struct rt_mmcsd_data *data = cmd->data;
    unsigned int bytecnt = 0;
    struct sdio_drv *sdio_des = (struct sdio_drv *)host->private_data;
    tina_mmc_t mmc = sdio_des->mmc_des;

    timeout = 5000 * 1000;
    status = mmc->star_reg;
    while (status & (1 << 9))
    {
        LOG_D("note: check card busy");

        status = mmc->star_reg;
        if (!timeout--)
        {
            err = -1;
            LOG_E("mmc cmd12 busy timeout data:0x%08x", status);
            return err;
        }
        mmc_delay_us(1);
    }
    /*
     * CMDREG
     * CMD[5:0] : Command index
     * CMD[6]   : Has response
     * CMD[7]   : Long response
     * CMD[8]   : Check response CRC
     * CMD[9]   : Has data
     * CMD[10]  : Write
     * CMD[11]  : Steam mode
     * CMD[12]  : Auto stop
     * CMD[13]  : Wait previous over
     * CMD[14]  : About cmd
     * CMD[15]  : Send initialization
     * CMD[21]  : Update clock
     * CMD[31]  : Load cmd
     */
    if (!cmd->cmd_code)
        cmdval |= (1 << 15);
    if (resp_type(cmd) != RESP_NONE)
        cmdval |= (1 << 6);
    if (resp_type(cmd) == RESP_R2)
        cmdval |= (1 << 7);
    if ((resp_type(cmd) != RESP_R3) && (resp_type(cmd) != RESP_R4))
        cmdval |= (1 << 8);
    
    if (data)
    {
        cmdval |= (1 << 9) | (1 << 13);
        if (data->flags & DATA_DIR_WRITE)
            cmdval |= (1 << 10);
        if (data->blks > 1)
            cmdval |= (1 << 12);
        mmc->bksr_reg = data->blksize;
        bytecnt = data->blksize * data->blks;
        mmc->bycr_reg = bytecnt;
    }

    LOG_D("cmd %d(0x%08x), arg 0x%08x", cmd->cmd_code, cmdval | cmd->cmd_code, cmd->arg);
    mmc->cagr_reg = cmd->arg;
    if (!data)
    {
        mmc->cmdr_reg = cmdval | cmd->cmd_code;
        mmc->imkr_reg |= 0x1 << 2;
    }

    /*
     * transfer data and check status
     * STATREG[2] : FIFO empty
     * STATREG[3] : FIFO full
     */
    if (data)
    {
        LOG_D("mmc trans data %d bytes addr:0x%08x", bytecnt, data);
#ifdef CONFIG_MMC_USE_DMA
        if (bytecnt > 64)
        {
#else
        if (0)
        {
#endif
            sdio_des->usedma = 1;
            mmc->gctl_reg = mmc->gctl_reg & (~0x80000000);
            mmc_trans_data_by_dma(mmc, &sdio_des->xfe);
            mmc->cmdr_reg = cmdval | cmd->cmd_code;
        }
        else
        {
            sdio_des->usedma = 0;
            mmc->gctl_reg = mmc->gctl_reg | 0x80000000;
            mmc->cmdr_reg = cmdval | cmd->cmd_code;
            mmc_trans_data_by_cpu(mmc, &sdio_des->xfe);
        }

        if (data->blks > 1)
        {
            mmc->imkr_reg |= (0x1 << 14);
        }
        else
        {
            mmc->imkr_reg |= (0x1 << 3);
        }
    }

    mmc->imkr_reg |= 0xbfc2;

    if (data)
    {
        //TODO:2 * bytecnt * 4?
        timeout = sdio_des->usedma ? (2 * bytecnt * 4) : 100; //0.04us(25M)*2(4bit width)*25()
        if (timeout < 10)
        {
            timeout = 10;
        }
    }
    else
    {
        timeout = 200;
    }

    if (rt_sem_take(&sdio_des->rt_sem, timeout) != RT_EOK)
    {
        err = (mmc->risr_reg | sdio_des->flag.risr) & 0xbfc2;
        goto out;
    }

    err = (mmc->risr_reg | sdio_des->flag.risr) & 0xbfc2;
    if (err)
    {
        cmd->err = -RT_ETIMEOUT;
        goto out;
    }

    if (resp_type(cmd) == RESP_R2)
    {
        cmd->resp[3] = mmc->resp0_reg;
        cmd->resp[2] = mmc->resp1_reg;
        cmd->resp[1] = mmc->resp2_reg;
        cmd->resp[0] = mmc->resp3_reg;
        LOG_D("mmc resp 0x%08x 0x%08x 0x%08x 0x%08x",
                  cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3]);
    }
    else
    {
        cmd->resp[0] = mmc->resp0_reg;
        LOG_D("mmc resp 0x%08x", cmd->resp[0]);
    }

out:
    if (err)
    {
        mmc_dump_errinfo(err & 0xbfc2);
    }
    if (data && sdio_des->usedma)
    {
        /* IDMASTAREG
         * IDST[0] : idma tx int
         * IDST[1] : idma rx int
         * IDST[2] : idma fatal bus error
         * IDST[4] : idma descriptor invalid
         * IDST[5] : idma error summary
         * IDST[8] : idma normal interrupt sumary
         * IDST[9] : idma abnormal interrupt sumary
         */
        status = mmc->idst_reg;
        mmc->idst_reg = status;
        mmc->idie_reg = 0;
        mmc->dmac_reg = 0;
        mmc->gctl_reg = mmc->gctl_reg & (~(1 << 5));
    }
    if (err)
    {
        if (data && (data->flags & DATA_DIR_READ) && (bytecnt == 512))
        {
            mmc->gctl_reg = mmc->gctl_reg | 0x80000000;
            mmc->dbgc_reg = 0xdeb;
            timeout = 1000;
            LOG_D("Read remain data");
            while (mmc->bbcr_reg < 512)
            {
                unsigned int tmp = mmc->fifo_reg;
                tmp = tmp;
                LOG_D("Read data 0x%08x, bbcr 0x%04x", tmp, mmc->bbcr_reg);
                mmc_delay_us(1);
                if (!(timeout--))
                {
                    LOG_E("Read remain data timeout");
                    break;
                }
            }
        }

        mmc->gctl_reg = 0x7;
        while (mmc->gctl_reg & 0x7) { };

        mmc_update_clk(mmc);
        cmd->err = -RT_ETIMEOUT;
        LOG_E("mmc cmd %d err", cmd->cmd_code);
    }

    mmc->gctl_reg &= ~(0x1 << 4);
    mmc->imkr_reg &= ~0xffff;
    mmc->risr_reg = 0xffffffff;
    mmc->gctl_reg |= 0x1 << 4;
    while (!rt_sem_take(&sdio_des->rt_sem, 0)) {}
    mmc_request_end(sdio_des->host, sdio_des->req);

    return err;
}

static void mmc_request_end(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct rt_mmcsd_data *data;
    unsigned byte_cnt;
    struct sdio_drv *sdio = (struct sdio_drv *)host->private_data;

#ifdef CONFIG_MMC_USE_DMA
    data = req->cmd->data;
    if (data)
    {
        byte_cnt = data->blksize * data->blks;
        if ((byte_cnt > 64) && (data->flags & DATA_DIR_READ))
        {
            mmu_invalidate_dcache((rt_uint32_t)sdio->xfe.buff, (rt_uint32_t)byte_cnt);

            if (((rt_uint32_t)data->buf) & (DMA_ALIGN - 1))
            {
                memcpy(data->buf, sdio->xfe.buff, byte_cnt);
            }
        }
    }
#endif
    mmcsd_req_complete(host);
}

static void sdio_request_send(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct rt_mmcsd_data *data;
    int byte_cnt;
    struct sdio_drv *sdio;

    sdio = (struct sdio_drv *)host->private_data;
    sdio->req = req;
    data = req->cmd->data;

    if (data)
    {
        sdio->xfe.size = data->blksize;
        sdio->xfe.num  = data->blks;
        sdio->xfe.buff = (rt_uint8_t *)data->buf;
        sdio->xfe.flag = (data->flags & DATA_DIR_WRITE) ? \
            MMC_DATA_WRITE : MMC_DATA_READ;
#ifdef CONFIG_MMC_USE_DMA
        byte_cnt = data->blksize * data->blks;
        if ((byte_cnt > 64) && (((rt_uint32_t)data->buf) & (DMA_ALIGN - 1)))
        {
            sdio->xfe.buff = (rt_uint8_t *)sdio->mmc_buf;
            if (data->flags & DATA_DIR_WRITE)
            {
                memcpy(sdio->mmc_buf, data->buf, byte_cnt);
                mmu_clean_dcache((rt_uint32_t)sdio->mmc_buf, (rt_uint32_t)byte_cnt);
            }
        }
#endif
    }

    memset(&sdio->flag, 0, sizeof(struct mmc_flag));
    mmc_send_cmd(host, req->cmd);
    
    return;
}

static void sdio_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    int clk = io_cfg->clock;
    int width = io_cfg->bus_width;
    struct sdio_drv *sdio_des = (struct sdio_drv *)host->private_data;
    tina_mmc_t mmc = sdio_des->mmc_des;

    mmc_set_ios(mmc, clk, width);
}

static const struct rt_mmcsd_host_ops ops =
{
    sdio_request_send,
    sdio_set_iocfg,
    RT_NULL,
    RT_NULL,
};

static void sdio_interrupt_handle(int irqno, void *param)
{
    rt_uint32_t risr, idst;
    rt_uint32_t status;
    struct sdio_drv *sdio_des = (struct sdio_drv *)param;
    struct rt_mmcsd_data *data = sdio_des->req->cmd->data;
    tina_mmc_t mmc = sdio_des->mmc_des;

    risr = mmc->risr_reg;
    idst = mmc->idst_reg;

    mmc->risr_reg = risr & mmc->imkr_reg;
    mmc->idst_reg = idst & mmc->idie_reg;

    sdio_des->flag.risr |= risr;
    sdio_des->flag.idst |= idst;

    if (data)
    {
        int done = 0;

        status = sdio_des->flag.risr | mmc->risr_reg;
        if (data->blks > 1)//not wait auto stop when MMC_CMD_MANUAL is set
        {
            if (sdio_des->usedma)
                done = ((status & (1 << 14)) && (sdio_des->flag.idst & 0x3)) ? 1 : 0;
            else
                done = status & (1 << 14);
        }
        else
        {
            if (sdio_des->usedma)
                done = ((status & (1 << 3)) && (sdio_des->flag.idst & 0x3)) ? 1 : 0;
            else
                done = status & (1 << 3);
        }

        if (done)
        {
            rt_sem_release(&sdio_des->rt_sem);
        }
    }
    else
    {
        rt_sem_release(&sdio_des->rt_sem);
    }
}

static void sdio_gpio_init(struct sdio_drv *sdio_des)
{
    int pin;

    if ((rt_uint32_t)sdio_des->mmc_des == MMC0_BASE_ADDR)
    {
        /* SDC0: PF0-PF5 */
        for (pin = GPIO_PIN_0; pin <= GPIO_PIN_5; pin++)
        {
            gpio_set_func(GPIO_PORT_F, pin, IO_FUN_1);
            gpio_set_pull_mode(GPIO_PORT_F, pin, PULL_UP);
            gpio_set_drive_level(GPIO_PORT_F, pin, DRV_LEVEL_2);
        }
    }
    else if ((rt_uint32_t)sdio_des->mmc_des == MMC1_BASE_ADDR)
    {
        //todo: config gpio port
        RT_ASSERT(0);
    }

}

static void sdio_clk_io_on(struct sdio_drv *sdio_des)
{
    if ((rt_uint32_t)sdio_des->mmc_des == MMC0_BASE_ADDR)
    {
        CCU->bus_clk_gating0 |= 0x1 << 8;
        CCU->bus_soft_rst0 |= 0x1 << 8;
    }
    else if ((rt_uint32_t)sdio_des->mmc_des == MMC1_BASE_ADDR)
    {
        CCU->bus_clk_gating0 |= 0x1 << 9;
        CCU->bus_soft_rst0 |= 0x1 << 9;
    }

    mmc_set_clk(SDMMC0, 24000000);
}

static void sdio_irq_init(void *param)
{
    struct sdio_drv *sdio_des = (struct sdio_drv *)param;

    if ((rt_uint32_t)sdio_des->mmc_des == MMC0_BASE_ADDR)
    {
        rt_hw_interrupt_install(SDC0_INTERRUPT, sdio_interrupt_handle, param, "mmc0_irq");
        rt_hw_interrupt_umask(SDC0_INTERRUPT);
    }
    else if ((rt_uint32_t)sdio_des->mmc_des == MMC1_BASE_ADDR)
    {
        rt_hw_interrupt_install(SDC1_INTERRUPT, sdio_interrupt_handle, param, "mmc1_irq");
        rt_hw_interrupt_umask(SDC1_INTERRUPT);
    }

    sdio_des->mmc_des->gctl_reg |= (0x1 << 4);
}

int tina_sdio_init(void)
{
    struct rt_mmcsd_host *host;

#ifdef TINA_USING_SDIO0
    {
        static struct sdio_drv _sdio_drv;

        host = mmcsd_alloc_host();
        if (!host)
        {
            LOG_E("alloc host failed");
            goto err;
        }

        if (rt_sem_init(&_sdio_drv.rt_sem, "sdio_sem", RT_NULL, RT_IPC_FLAG_FIFO))
        {
            LOG_E("sem init failed");
            goto err;
        }
        _sdio_drv.mmc_des = (tina_mmc_t)MMC0_BASE_ADDR;
        _sdio_drv.mmc_buf = dma_buffer;
        //init gpio pin
        sdio_gpio_init(&_sdio_drv);
        //clk is on
        sdio_clk_io_on(&_sdio_drv);
        //irq init
        sdio_irq_init(&_sdio_drv);

        host->ops = &ops;
        host->freq_min = 400 * 1000;
        host->freq_max = 50 * 1000 * 1000;
        host->valid_ocr = VDD_26_27 | VDD_27_28 | VDD_28_29 | VDD_29_30 | VDD_30_31 | VDD_31_32 |
        VDD_32_33 | VDD_33_34 | VDD_34_35 | VDD_35_36;
        host->flags = MMCSD_BUSWIDTH_4 | MMCSD_MUTBLKWRITE | MMCSD_SUP_SDIO_IRQ | MMCSD_SUP_HIGHSPEED;
        host->max_seg_size = 2048;
        host->max_dma_segs = 10;
        host->max_blk_size = 512;
        host->max_blk_count = 4096;

        host->private_data = &_sdio_drv;

        _sdio_drv.host = host;

        mmcsd_change(host);
    }
#endif

    return RT_EOK;

err:
    if (host)
    {
        rt_free(host);
    }

    return RT_ERROR;
}
INIT_APP_EXPORT(tina_sdio_init);
#endif
