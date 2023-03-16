/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-18     Carl      the first version
 */

#include "drv_sdctrl.h"
#include "ft_sdctrl_hw.h"
#include "ft_sdctrl.h"
#include "ft_debug.h"
#include "ft_types.h"
#include "ft_generic_timer.h"
#include <drivers/mmcsd_core.h>
#include "interrupt.h"
#include "rtconfig.h"
#include "ft_cache.h"

#ifdef BSP_USING_SDC

#define LOG_TAG "drv.sdmmc"
#include <drv_log.h>

#define RTHW_SDCTRL_LOCK(_sdctrl) rt_mutex_take(&_sdctrl->mutex, RT_WAITING_FOREVER)
#define RTHW_SDCTRL_UNLOCK(_sdctrl) rt_mutex_release(&_sdctrl->mutex);

struct mmcsd_pkg
{
    struct rt_mmcsd_cmd *cmd;
    void *buff;
    rt_uint32_t flag;
};

typedef struct
{
    FtsdCtrl_t ft_sdctrl;
    struct rt_mmcsd_host *host;
    struct rt_event event;
    struct rt_mutex mutex;
    struct mmcsd_pkg *pkg;
} ft_sdctrl_class_t;

ft_sdctrl_class_t sdctrl_class;

rt_align(SDCTR_ALIGN_LEN)
static rt_uint8_t cache_buf[SDCTR_BUFF_SIZE];

static void rthw_sdctrl_send_command(ft_sdctrl_class_t *class_p, struct mmcsd_pkg *pkg);

static void demo_dump_sdc(void)
{
    Ft_DumpHexWord((const rt_uint32_t *)(0x28207C00), 256);
}
MSH_CMD_EXPORT_ALIAS(demo_dump_sdc, dump_sdc, output all dump_sdc);

static void rthw_sdctrl_delay(u32 delayCnt)
{
    Ft_GenericTimer_UsDelay(delayCnt);
}

static u32 rthw_sdctrl_rasp2type(u32 rasp)
{

    switch (rasp)
    {
    case RESP_NONE:
        return FTSDCTRL_CMD_RES_NONE;
    case RESP_R2:
        return FTSDCTRL_CMD_RES_LONG;
    default:
        return FTSDCTRL_CMD_RES_SHORT;
    }

    return FTSDCTRL_CMD_RES_SHORT;
}

static void rthw_sdctrl_transfer_by_dma(ft_sdctrl_class_t *class_p, struct mmcsd_pkg *pkg)
{
    struct rt_mmcsd_data *data;
    struct rt_mmcsd_cmd *cmd;
    u32 rasp;
    u32 *buff;
    FtsdCtrl_t *ft_sdctrl_p;

    if ((RT_NULL == class_p))
    {
        LOG_E("rthw_sdctrl_transfer_by_dma invalid class_p");
        return;
    }
    ft_sdctrl_p = &class_p->ft_sdctrl;

    if ((RT_NULL == pkg))
    {
        LOG_E("rthw_sdctrl_transfer_by_dma invalid args");
        return;
    }

    data = pkg->cmd->data;
    if (RT_NULL == data)
    {
        LOG_E("rthw_sdctrl_transfer_by_dma invalid args");
        return;
    }

    buff = pkg->buff;
    if (RT_NULL == buff)
    {
        LOG_E("rthw_sdctrl_transfer_by_dma invalid args");
        return;
    }

    cmd = pkg->cmd;
    rasp = resp_type(pkg->cmd);
    rasp = rthw_sdctrl_rasp2type(rasp);

    if (data->flags & DATA_DIR_WRITE)
    {
#ifdef BSP_SDC_DEBUG_PRINT
        rt_kprintf("DATA_DIR_WRITE %x \r\n", cmd->arg);
#endif
        FCache_cpuDcacheClean(buff, data->blks * data->blksize);

        /* data, card, blk:  card : data + blk */
        FSdCtrl_WriteData(ft_sdctrl_p, (UINTPTR)buff, cmd->arg, data->blks);
        cmd->err = FSdCtrl_WaitCmdEnd(ft_sdctrl_p, (pFtsdCtrl_delayTimer_t)rthw_sdctrl_delay, rasp, cmd->resp);

#ifdef BSP_SDC_DEBUG_PRINT
        for (int i = 0; i < 4; i++)
        {
            rt_kprintf("cmdRsp[%d] %x \r\n", i, cmd->resp[i]);
        }
        Ft_DumpHexWord(buff, 256);
#endif
        FSdCtrl_WaitWriteDataEnd(ft_sdctrl_p, (pFtsdCtrl_delayTimer_t)rthw_sdctrl_delay, data->blks);
        FCache_cpuDcacheInvalidate(buff, data->blks * data->blksize);
    }
    else if (data->flags & DATA_DIR_READ)
    {
#ifdef BSP_SDC_DEBUG_PRINT
        rt_kprintf("DATA_DIR_READ %x \r\n", cmd->arg);
#endif
        if ((cmd->flags & CMD_ADTC) && (data->blksize < 512))
        {
#ifdef BSP_SDC_DEBUG_PRINT
            LOG_E("CMD_ADTC \r\n");
#endif
            FSdCtrl_DoACmd(ft_sdctrl_p, cmd->cmd_code, rasp, cmd->arg);
            rt_thread_mdelay(10);
        }

        FCache_cpuDcacheInvalidate(buff, data->blks * data->blksize);
        FSdCtrl_ReadData(ft_sdctrl_p, (UINTPTR)buff, cmd->arg, data->blks);
        cmd->err = FSdCtrl_WaitCmdEnd(ft_sdctrl_p, (pFtsdCtrl_delayTimer_t)rthw_sdctrl_delay, rasp, cmd->resp);
#ifdef BSP_SDC_DEBUG_PRINT
        for (int i = 0; i < 4; i++)
        {
            rt_kprintf("cmdRsp[%d] %x \r\n", i, cmd->resp[i]);
        }
#endif
        FSdCtrl_WaitReadDataEnd(ft_sdctrl_p, (pFtsdCtrl_delayTimer_t)rthw_sdctrl_delay, data->blks);
        FCache_cpuDcacheClean(buff, data->blks * data->blksize);
#ifdef BSP_SDC_DEBUG_PRINT
        Ft_DumpHexWord(buff, data->blks * data->blksize);
#endif
    }
}

static void rthw_sdctrl_docmd(ft_sdctrl_class_t *class_p, struct mmcsd_pkg *pkg)
{
    struct rt_mmcsd_cmd *cmd;
    u32 rasp;
    FtsdCtrl_t *ft_sdctrl_p;

    if ((RT_NULL == class_p))
    {
        LOG_E("rthw_sdctrl_docmd invalid class_p");
        return;
    }

    ft_sdctrl_p = &class_p->ft_sdctrl;

    if ((RT_NULL == pkg))
    {
        LOG_E("rthw_sdctrl_docmd invalid args");
        return;
    }

    cmd = pkg->cmd;
    rasp = resp_type(pkg->cmd);
    rasp = rthw_sdctrl_rasp2type(rasp);
    FSdCtrl_DoCmd(ft_sdctrl_p, pkg->cmd->cmd_code, rasp, cmd->arg);
    cmd->err = FSdCtrl_WaitCmdEnd(ft_sdctrl_p, (pFtsdCtrl_delayTimer_t)rthw_sdctrl_delay, rasp, cmd->resp);

#ifdef BSP_SDC_DEBUG_PRINT
    for (int i = 0; i < 4; i++)
    {
        rt_kprintf("cmdRsp[%d] %x \r\n", i, cmd->resp[i]);
    }
#endif
}

static void rthw_sdctrl_send_command(ft_sdctrl_class_t *class_p, struct mmcsd_pkg *pkg)
{
    struct rt_mmcsd_cmd *cmd = pkg->cmd;
    struct rt_mmcsd_data *data = cmd->data;
    /* save pkg */
    class_p->pkg = pkg;

    /* config data reg */
    if (data != RT_NULL && data->blks)
    {
        /* transfer config */
        rthw_sdctrl_transfer_by_dma(class_p, pkg);
    }
    else
    {
        rthw_sdctrl_docmd(class_p, pkg);
    }
}

/**
  * @brief  This function send sdio request.
  * @param  host  rt_mmcsd_host
  * @param  req   request
  * @retval None
  */
static void rthw_sdctrl_request(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req)
{
    struct mmcsd_pkg pkg;
    ft_sdctrl_class_t *class_p = host->private_data;
    struct rt_mmcsd_data *data;

    RTHW_SDCTRL_LOCK(class_p);
    if (req->cmd != RT_NULL)
    {
        rt_memset(&pkg, 0, sizeof(pkg));
        data = req->cmd->data;
        pkg.cmd = req->cmd;

        if (pkg.cmd->cmd_code == 5 || pkg.cmd->cmd_code == 1)
        {
            rt_kprintf("cmd_code is not vaild %x \r\n", pkg.cmd->cmd_code);
            pkg.cmd->err = -RT_EINVAL;
            goto _exit;
        }

#ifdef BSP_SDC_DEBUG_PRINT
        struct rt_mmcsd_cmd *cmd;
        cmd = req->cmd;
        LOG_E("CMD:%d ARG:0x%08x RES:%s%s%s%s%s%s%s%s%s rw:%c len:%d blksize:%d",
              cmd->cmd_code,
              cmd->arg,
              resp_type(cmd) == RESP_NONE ? "NONE" : "",
              resp_type(cmd) == RESP_R1 ? "R1" : "",
              resp_type(cmd) == RESP_R1B ? "R1B" : "",
              resp_type(cmd) == RESP_R2 ? "R2" : "",
              resp_type(cmd) == RESP_R3 ? "R3" : "",
              resp_type(cmd) == RESP_R4 ? "R4" : "",
              resp_type(cmd) == RESP_R5 ? "R5" : "",
              resp_type(cmd) == RESP_R6 ? "R6" : "",
              resp_type(cmd) == RESP_R7 ? "R7" : "",
              data ? (data->flags & DATA_DIR_WRITE ? 'w' : 'r') : '-',
              data ? data->blks * data->blksize : 0,
              data ? data->blksize : 0);
#endif

        if (data != RT_NULL)
        {
            rt_uint32_t size = data->blks * data->blksize;

            RT_ASSERT(size <= SDCTR_BUFF_SIZE);
            pkg.buff = data->buf;
            if ((rt_uint32_t)data->buf & (SDCTR_ALIGN_LEN - 1))
            {
                pkg.buff = cache_buf;
                if (data->flags & DATA_DIR_WRITE)
                {
                    rt_memcpy(cache_buf, data->buf, size);
                }
            }
        }

        rthw_sdctrl_send_command(class_p, &pkg);

        if ((data != RT_NULL) && (data->flags & DATA_DIR_READ) && ((rt_uint32_t)data->buf & (SDCTR_ALIGN_LEN - 1)))
        {
            rt_memcpy(data->buf, cache_buf, data->blksize * data->blks);
        }
    }

    if (req->stop != RT_NULL)
    {
        rt_memset(&pkg, 0, sizeof(pkg));
        pkg.cmd = req->stop;
        rthw_sdctrl_send_command(class_p, &pkg);
    }

_exit:

    RTHW_SDCTRL_UNLOCK(class_p);
    mmcsd_req_complete(class_p->host);
}

static void rthw_sdctrl_clk_divider(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    ft_sdctrl_class_t *class_p = host->private_data;
    FtsdCtrl_t *sd_ctrl = &(class_p->ft_sdctrl);

    /* bus mode is pull push */
    FSdCtrl_ClkFreqSetup(sd_ctrl, io_cfg->clock);
    return;
}

static void rthw_sdctrl_iocfg(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg)
{
    ft_sdctrl_class_t *class_p = host->private_data;
    RTHW_SDCTRL_LOCK(class_p);

    /* calculate and set clk divider */
    rthw_sdctrl_clk_divider(host, io_cfg);

    RTHW_SDCTRL_UNLOCK(class_p);
}

rt_int32_t rthw_sdctrl_detect(struct rt_mmcsd_host *host)
{
    ft_sdctrl_class_t *class_p = host->private_data;

    return FSdCtrl_CardDetect(&class_p->ft_sdctrl);
}

static const struct rt_mmcsd_host_ops ops =
    {
        rthw_sdctrl_request,
        rthw_sdctrl_iocfg,
        rthw_sdctrl_detect,
        RT_NULL,
};

void rthw_sdctrl_nomarl_callback(void *args)
{
    FtsdCtrl_t *pFtsdCtrl = (FtsdCtrl_t *)args;
    rt_uint32_t status;
    ft_sdctrl_class_t *class_p;
    if (RT_NULL == pFtsdCtrl)
    {
        return;
    }

    class_p = rt_container_of(pFtsdCtrl, ft_sdctrl_class_t, ft_sdctrl);

    status = FSdCtrl_GetNormalIrqStatus(pFtsdCtrl);

    if (status & NORMAL_INT_STATUS_CR)
    {
        rt_event_send(&class_p->event, SDCTR_CARD_REMOVE_FLG);
    }
    else if (status & NORMAL_INT_STATUS_CC)
    {
        rt_event_send(&class_p->event, SDCTR_CMD_IS_COMPLETE_FLG);
    }
    else if (status & NORMAL_INT_STATUS_EI)
    {
        rt_event_send(&class_p->event, SDCTR_CMD_IS_ERROR_FLG);
    }

    return;
}

void rthw_sdctrl_dma_callback(void *args)
{
    FtsdCtrl_t *pFtsdCtrl = (FtsdCtrl_t *)args;
    rt_uint32_t status;
    ft_sdctrl_class_t *class_p;

    if (RT_NULL == pFtsdCtrl)
    {
        return;
    }

    class_p = rt_container_of(pFtsdCtrl, ft_sdctrl_class_t, ft_sdctrl);

    status = FSdCtrl_GetDataIrqStatus(pFtsdCtrl);

    if (status & BD_ISR_REG_TRS)
    {
        /* send write complete event */
        rt_event_send(&class_p->event, SDCTR_WRITE_IS_COMPLETE_FLG);
    }

    if (status & BD_ISR_REG_RESPE)
    {
        /* send read complete event */
        rt_event_send(&class_p->event, SDCTR_READ_IS_COMPLETE_FLG);
    }

    if (status & BD_ISR_REG_DAIS)
    {
        /* send dma errror event */
        rt_event_send(&class_p->event, SDCTR_DMA_IS_ERROR_FLG);
    }
}

void rthw_sdctrl_error_callback(void *args)
{
    FtsdCtrl_t *pFtsdCtrl = (FtsdCtrl_t *)args;
    rt_uint32_t status;
    ft_sdctrl_class_t *class_p;

    if (RT_NULL == pFtsdCtrl)
    {
        return;
    }

    class_p = rt_container_of(pFtsdCtrl, ft_sdctrl_class_t, ft_sdctrl);

    status = FSdCtrl_GetErrorIrqStatus(pFtsdCtrl);

    if (status & SDCTR_CMD_TIMEOUT_FLG)
    {
        rt_event_send(&class_p->event, SDCTR_CMD_TIMEOUT_FLG);
    }

    if (status & ERROR_INT_EN_CNR)
    {
        rt_event_send(&class_p->event, SDCTR_CMD_RECEIVE_IS_ERROR_FLG);
    }

    if (status & ERROR_INT_EN_CCRCE)
    {
        rt_event_send(&class_p->event, SDCTR_CMD_CRC_IS_ERROR_FLG);
    }
}

void rthw_sdctrl_normal_irq(int vector, void *param)
{
    FtsdCtrl_t *pFtsdCtrl = (FtsdCtrl_t *)param;
    FSdCtrl_NormalIrq(pFtsdCtrl);
}

void rthw_sdctrl_dma_irq(int vector, void *param)
{
    FtsdCtrl_t *pFtsdCtrl = (FtsdCtrl_t *)param;
    FSdCtrl_DmaIrq(pFtsdCtrl);
}

void rthw_sdctrl_err_irq(int vector, void *param)
{
    FtsdCtrl_t *pFtsdCtrl = (FtsdCtrl_t *)param;
    FSdCtrl_ErrIrq(pFtsdCtrl);
}

ft_error_t rthw_sdctrl_cmd_wait(FtsdCtrl_t *pFtsdCtrl)
{
    rt_uint32_t status;
    ft_sdctrl_class_t *class_p;

    if (RT_NULL == pFtsdCtrl)
    {
        return FTSDC_INVALID_PARAM;
    }

    class_p = rt_container_of(pFtsdCtrl, ft_sdctrl_class_t, ft_sdctrl);

    if (rt_event_recv(&class_p->event, SDCTR_CMD_IS_COMPLETE_FLG | SDCTR_CMD_IS_ERROR_FLG | SDCTR_CMD_CRC_IS_ERROR_FLG, RT_EVENT_FLAG_CLEAR | RT_EVENT_FLAG_OR,
                      rt_tick_from_millisecond(50000), &status) != RT_EOK)
    {
        /* wait cmd completed timeout */
        LOG_E("wait cmd completed timeout");
        return FTSDC_TIMEOUT;
    }

    if (SDCTR_CMD_IS_COMPLETE_FLG == (status & SDCTR_CMD_IS_COMPLETE_FLG))
    {
        return FTSDC_SUCCESS;
    }
    else
    {
        LOG_E("wait cmd is error %x ", status);
        return FTSDC_FAILURE;
    }
}

ft_error_t rthw_sdctrl_read_wait(FtsdCtrl_t *pFtsdCtrl)
{
    rt_uint32_t status;
    ft_sdctrl_class_t *class_p;

    if (RT_NULL == pFtsdCtrl)
    {
        return FTSDC_INVALID_PARAM;
    }

    class_p = rt_container_of(pFtsdCtrl, ft_sdctrl_class_t, ft_sdctrl);

    if (rt_event_recv(&class_p->event, SDCTR_READ_IS_COMPLETE_FLG | SDCTR_CMD_RECEIVE_IS_ERROR_FLG,
                      RT_EVENT_FLAG_CLEAR | RT_EVENT_FLAG_OR,
                      rt_tick_from_millisecond(50000), &status) != RT_EOK)
    {
        /* wait read completed timeout */
        LOG_E("wait read completed timeout");
        return FTSDC_TIMEOUT;
    }

    if (SDCTR_READ_IS_COMPLETE_FLG == (status & SDCTR_READ_IS_COMPLETE_FLG))
    {
        return FTSDC_SUCCESS;
    }
    else
    {
        LOG_E("wait read is error %x ", status);
        return FTSDC_FAILURE;
    }
}

ft_error_t rthw_sdctrl_write_wait(FtsdCtrl_t *pFtsdCtrl)
{
    rt_uint32_t status;
    ft_sdctrl_class_t *class_p;

    if (RT_NULL == pFtsdCtrl)
    {
        return FTSDC_INVALID_PARAM;
    }

    class_p = rt_container_of(pFtsdCtrl, ft_sdctrl_class_t, ft_sdctrl);

    if (rt_event_recv(&class_p->event, SDCTR_WRITE_IS_COMPLETE_FLG, RT_EVENT_FLAG_CLEAR | RT_EVENT_FLAG_OR,
                      rt_tick_from_millisecond(50000), &status) != RT_EOK)
    {
        /* wait write completed timeout */
        LOG_E("wait write completed timeout");
        return FTSDC_TIMEOUT;
    }

    if (SDCTR_WRITE_IS_COMPLETE_FLG == (status & SDCTR_WRITE_IS_COMPLETE_FLG))
    {
        return FTSDC_SUCCESS;
    }
    else
    {
        LOG_E("wait write is error %x ", status);
        return FTSDC_FAILURE;
    }
}

static rt_err_t rthw_sdctrl_create(ft_sdctrl_class_t *class_p)
{
    struct rt_mmcsd_host *host;

    host = mmcsd_alloc_host();
    if (host == RT_NULL)
    {
        LOG_E("L:%d F:%s mmcsd alloc host fail");
        return RT_ENOMEM;
    }

    class_p->ft_sdctrl.config = *(FSdCtrl_Config_t *)FSdCtrl_LookupConfig(0);
    rt_event_init(&class_p->event, "sdctrl", RT_IPC_FLAG_FIFO);
    rt_mutex_init(&class_p->mutex, "sdctrl", RT_IPC_FLAG_PRIO);

    class_p->host = host;
    host->ops = &ops;
    /* range of sd work speed */
    host->freq_min = 400 * 1000;
    host->freq_max = 48 * 1000000;
    host->valid_ocr = 0X00FFFF80; /* The voltage range supported is 1.65v-3.6v */
    host->flags = MMCSD_BUSWIDTH_4;
    host->private_data = class_p;
    /* ready to change */

    return RT_EOK;
}

int rthw_sdctrl_init(void)
{

    FtsdCtrl_t *ft_sdctrl_p;
#ifdef BSP_SDC_USE_IRQ
    FSdCtrl_Config_t *config_p;
    FSdCtrl_NormalIrqSelect_t normalIrqFlgs = 0;
#endif

    rt_kprintf("rthw_sdctrl_init \r\n");
    RT_ASSERT(rthw_sdctrl_create(&sdctrl_class) == RT_EOK);
    ft_sdctrl_p = &sdctrl_class.ft_sdctrl;

    FSdCtrl_Reset(ft_sdctrl_p, (pFtsdCtrl_delayTimer_t)rthw_sdctrl_delay);
    FsdCtrl_Init(ft_sdctrl_p);

#ifdef BSP_SDC_USE_IRQ
    config_p = &ft_sdctrl_p->config;
#ifdef BSP_SDC_IRQ_CARD_REMOVE
    normalIrqFlgs |= NORMAL_IRQ_CR;

#endif
    normalIrqFlgs |= NORMAL_IRQ_CC;
    /* register handler、irq enable bit and wait callback */
    FSdCtrl_SetHandler(ft_sdctrl_p, FTSDCTRL_CMDIRQID, rthw_sdctrl_nomarl_callback, ft_sdctrl_p);
    FSdCtrl_NormalIrqSet(ft_sdctrl_p, normalIrqFlgs);
    FSdCtrl_CmdWaitRegister(ft_sdctrl_p, rthw_sdctrl_cmd_wait);

    FSdCtrl_SetHandler(ft_sdctrl_p, FTSDCTRL_DMADATAIRQID, rthw_sdctrl_dma_callback, ft_sdctrl_p);
    FSdCtrl_BdIrqSet(ft_sdctrl_p, BD_IRQ_TRS | BD_IRQ_RESPE);
    FSdCtrl_WriteWaitRegister(ft_sdctrl_p, rthw_sdctrl_write_wait);
    FSdCtrl_ReadWaitRegister(ft_sdctrl_p, rthw_sdctrl_read_wait);

    config_p->workMode = FTSDCTRL_CMD_IRQ_MASK | FTSDCTRL_DATA_WRITE_IRQ_MASK | FTSDCTRL_DATA_READ_IRQ_MASK;

#else

#endif

    /* install normal irq */

    rt_hw_interrupt_install(ft_sdctrl_p->config.normalIrqNum, rthw_sdctrl_normal_irq,
                            &sdctrl_class.ft_sdctrl, "normalIrq");
    rt_hw_interrupt_umask(ft_sdctrl_p->config.normalIrqNum);

    rt_hw_interrupt_install(ft_sdctrl_p->config.dmaIrqNum, rthw_sdctrl_dma_irq,
                            &sdctrl_class.ft_sdctrl, "dmaIrq");
    rt_hw_interrupt_umask(ft_sdctrl_p->config.dmaIrqNum);

    return 0;
}

INIT_DEVICE_EXPORT(rthw_sdctrl_init);

void ft2004_mmcsd_change(void)
{
    mmcsd_change(sdctrl_class.host);
}

rt_bool_t ft2004_card_status(void)
{
    return FSdCtrl_CardDetect(&sdctrl_class.ft_sdctrl);
}

rt_err_t ft2004_card_remove_check(rt_int32_t timeout, rt_uint32_t *status)
{
    return rt_event_recv(&sdctrl_class.event, SDCTR_CARD_REMOVE_FLG, RT_EVENT_FLAG_CLEAR | RT_EVENT_FLAG_OR,
                         timeout, status);
}

void ft2004_sdctrl_reset(void)
{
    FSdCtrl_Reset(&sdctrl_class.ft_sdctrl, (pFtsdCtrl_delayTimer_t)rthw_sdctrl_delay);
    FsdCtrl_Init(&sdctrl_class.ft_sdctrl);

#ifdef BSP_SDC_USE_IRQ
    FSdCtrl_NormalIrqSet(&sdctrl_class.ft_sdctrl, NORMAL_IRQ_CC | NORMAL_IRQ_CR | NORMAL_IRQ_EI);
    FSdCtrl_BdIrqSet(&sdctrl_class.ft_sdctrl, BD_IRQ_TRS | BD_IRQ_RESPE);
#endif
}

#endif
