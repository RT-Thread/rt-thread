/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-15     Jonne        first version for s3c2440 mmc controller
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/mmcsd_core.h>
#include <s3c24x0.h>

#define S3C_PCLK	50000000


static void s3c_mmc_set_clk(struct rt_mmcsd_host *host, rt_uint32_t clock)
{
    rt_uint32_t prescale;
    rt_uint32_t realClk;

    for(prescale = 0; prescale < 256; ++prescale) 
    {
        realClk = S3C_PCLK / (1 + prescale);
        if(realClk <= clock) 
        {
            break;
        }
    }

    SDIPRE = prescale;
    host->io_cfg.clock = realClk;
}

static rt_uint32_t s3c_mmc_send_cmd(struct rt_mmcsd_host *host, struct rt_mmcsd_cmd *cmd)
{
    rt_uint32_t ccon;
    rt_uint32_t cmdSta;

    SDICARG = cmd->arg;

    ccon = cmd->cmd_code & 0x3f;
    ccon |= (0 << 7) | (1 << 6); /* two start bits*/
    ccon |= (1 << 8);/* command start*/

    if(cmd->flags & 0xF)
    {
        // Need response
        ccon |= (1 << 9);
    }

    if((cmd->flags & 0xF) == RESP_R2)
    {
        // R2 need 136bit response
        ccon |= (1 << 10);
    }

    SDICCON = ccon; /* start cmd */

    if(cmd->flags & 0xF) 
    {
        cmdSta = SDICSTA;
        while((cmdSta & 0x200) != 0x200 && (cmdSta & 0x400) != 0x400) 
        {
            cmdSta = SDICSTA;
        }

        if((cmdSta & 0x1000) == 0x1000 && (cmd->flags & 0xF) != RESP_R3 && (cmd->flags & 0xF) != RESP_R4) 
        {
            // crc error, but R3 R4 ignore it
            SDICSTA = cmdSta;
            return -RT_ERROR;
        }

        if((cmdSta & 0xF00) != 0xa00)
        {
            SDICSTA = cmdSta;
            return -RT_ERROR;
        }

        cmd->resp[0] = SDIRSP0;
        if((cmd->flags & 0xF) == RESP_R2) 
        {
            cmd->resp[1] = SDIRSP1;
            cmd->resp[2] = SDIRSP2;
            cmd->resp[3] = SDIRSP3;
        }
    }
    else
    {
        cmdSta = SDICSTA;
        while((cmdSta & 0x800) != 0x800)
        {
            cmdSta = SDICSTA;
        } 
    }

    SDICSTA = cmdSta; // clear current status

    return RT_EOK;

}

static rt_uint32_t s3c_mmc_xfer_data(struct rt_mmcsd_data *data)
{
    rt_uint32_t status;
    rt_uint32_t xfer_size;
    rt_uint32_t handled_size = 0;
    rt_uint32_t *pBuf = RT_NULL;


    if(data == RT_NULL)
    {
        return -RT_ERROR;
    }

    xfer_size = data->blks * data->blksize;

    pBuf = data->buf;
    if(data->flags & DATA_DIR_READ)
    {
        while(handled_size < xfer_size)
        {
            if ((SDIDSTA & 0x20) == 0x20)
            {
                SDIDSTA = (0x1 << 0x5);
                break; 
            }

            status = SDIFSTA;
            if ((status & 0x1000) == 0x1000)
            {
                *pBuf++ = SDIDAT;
                handled_size += 4;
            }
        }
    }
    else 
    {
        while(handled_size < xfer_size)
        {
            status = SDIFSTA;
            if ((status & 0x2000) == 0x2000)
            {
                SDIDAT = *pBuf++;
                handled_size += 4;
            }
        }
    }

    // wait for end
    status = SDIDSTA;
    while((status & 0x30) == 0)
    {
        status = SDIDSTA;
    }
    SDIDSTA = status;

    if ((status & 0xfc) != 0x10)
    {
        return -RT_ERROR;
    }

    SDIDCON = SDIDCON & ~(7<<12);
    SDIFSTA = SDIFSTA & 0x200;
    SDIDSTA = 0x10;

    return RT_EOK;
}
static void mmc_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    rt_uint32_t ret;
    struct rt_mmcsd_cmd *cmd;
    struct rt_mmcsd_data *data;
    rt_uint32_t val;
    rt_uint32_t tryCnt = 0;

    if(req->cmd == RT_NULL)
    {
        goto out;
    }
    cmd = req->cmd;

    /* prepare for data transfer*/
    if(req->data != RT_NULL) 
    {
        SDIFSTA = SDIFSTA | (1<<16); // reset fifo 

        while(SDIDSTA & 0x03)
        {
            if(tryCnt++ > 500)
            {
                break;
                SDIDSTA = SDIDSTA;
            }
        }

        data = req->data;

        if((data->blksize & 0x3) != 0)
        {
            goto out;
        }

        val = (2 << 22)  //word transfer
                  | (1 << 20) // transmet after response
                  | (1 << 19) // reciveve after command sent
                  | (1 << 17) // block data transfer
                  | (1 << 14); // data start

        if(host->io_cfg.bus_width == MMCSD_BUS_WIDTH_4)
        {
            val |= (1 << 16); // wide bus mode(4bit data)
        }

        if(data->flags & DATA_DIR_READ) 
        {
            // for data read 
            val |= (2 << 12);
        }
        else 
        {
            val |= (3 << 12);
        }

        val |= (data->blks & 0xFFF);

        SDIDCON = val;

        SDIBSIZE = data->blksize;
        SDIDTIMER = 0x7fffff;
    }

    ret = s3c_mmc_send_cmd(host,req->cmd);
    if(ret != RT_EOK) {
        cmd->err = ret;
        goto out;
    }

    if(req->data != RT_NULL)
    {
        /*do transfer data*/
        ret = s3c_mmc_xfer_data(data);
        if(ret != RT_EOK)
        {
            data->err = ret;
            goto out;
        }
    }

out:
    mmcsd_req_complete(host);
}
static void mmc_set_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    switch (io_cfg->power_mode) {
    case MMCSD_POWER_ON:
    case MMCSD_POWER_UP:
        /* Enable PCLK into SDI Block */
        CLKCON |= 1 << 9;
        
        /* Setup GPIO as SD and SDCMD, SDDAT[3:0] Pull up En */
        GPEUP  = GPEUP  & (~(0x3f << 5))   | (0x01 << 5);
        GPECON = GPECON & (~(0xfff << 10)) | (0xaaa << 10);
        break;

    case MMCSD_POWER_OFF:
    default:
        break;                 
    }

    s3c_mmc_set_clk(host, io_cfg->clock);

    SDICON =  1;
}

static rt_int32_t mmc_get_card_status(struct rt_mmcsd_host *host)
{
    return RT_EOK;
}
static void mmc_enable_sdio_irq(struct rt_mmcsd_host *host, rt_int32_t en)
{
}

static const struct rt_mmcsd_host_ops ops = 
{
    mmc_request,
    mmc_set_iocfg,
    mmc_get_card_status,
    mmc_enable_sdio_irq
};

int s3c_sdio_init(void)
{
    struct rt_mmcsd_host * host = RT_NULL;


    host = mmcsd_alloc_host();
    if (!host)
    {
        goto err;
    }

    host->ops = &ops;
    host->freq_min = 300000;
    host->freq_max = 50000000;
    host->valid_ocr = VDD_32_33 | VDD_33_34;
    host->flags = MMCSD_MUTBLKWRITE | MMCSD_SUP_HIGHSPEED | MMCSD_SUP_SDIO_IRQ | MMCSD_BUSWIDTH_4;
    host->max_seg_size = 2048;
    host->max_dma_segs = 10;
    host->max_blk_size = 512;
    host->max_blk_count = 4096;


    mmcsd_change(host);

    return RT_EOK;

err:
    if(host)  rt_free(host);

    return -RT_EIO;
}

INIT_DEVICE_EXPORT(s3c_sdio_init);
