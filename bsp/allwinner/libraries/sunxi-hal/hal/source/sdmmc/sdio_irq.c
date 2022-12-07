/*
 * linux/drivers/mmc/core/sdio_irq.c
 *
 * Author:      Nicolas Pitre
 * Created:     June 18, 2007
 * Copyright:   MontaVista Software Inc.
 *
 * Copyright 2008 Pierre Ossman
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 */

#include "sys/param.h"

#include "hal_sdhost.h"
#include "sdmmc.h"
#include "sdio.h"
#include "sched.h"

#include "_sd_define.h"
#include "_core.h"
#include "_sdio.h"
//#define CONFIG_SDIO_IRQ_SUPPORT

#ifndef portMAX_DELAY
#define portMAX_DELAY 0xffffffffUL
#endif

#ifndef LONG_MAX
#define LONG_MAX        ((long)(~0UL>>1))
#endif
#define MAX_SCHEDULE_TIMEOUT    LONG_MAX

static int process_sdio_pending_irqs(struct mmc_host *host)
{
    struct mmc_card *card = host->card;
    int i, ret, count;
    unsigned char pending;
    struct sdio_func *func;

    /*
     * Optimization, if there is only 1 function interrupt registered
     * and we know an IRQ was signaled then call irq handler directly.
     * Otherwise do the full probe.
     */
#if 1
    func = card->sdio_single_irq;
    if (func && host->sdio_irq_pending) {
    //if (func) {
        //HAL_MSleep(2);
#ifdef SD_PERF_TRACE_ON
        if(!(host->sdio_irq_count%3000))
            SD_LOGN("d1 wait time %lld ns\n", HAL_PR_SZ_L(host->sdio_irq_times_ns = HAL_GetTimeNs()- host->start_sdio_irq_times_ns));
#endif
        func->irq_handler(func);
        return 1;
    }
#endif
    ret = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_INTx, 0, &pending);
    if (ret) {
        //SD_LOGE("%s: error %d reading SDIO_CCCR_INTx\n",
         //      mmc_card_id(card), ret);
        SD_LOGE("error %d reading SDIO_CCCR_INTx\n", ret);
        return ret;
    }

#if 0
    if (pending && mmc_card_broken_irq_polling(card) &&
        !(host->caps & MMC_CAP_SDIO_IRQ)) {
#endif
    if (pending &&
        !(host->caps & MMC_CAP_SDIO_IRQ)) {
    unsigned char dummy;

        /* A fake interrupt could be created when we poll SDIO_CCCR_INTx
         * register with a Marvell SD8797 card. A dummy CMD52 read to
         * function 0 register 0xff can avoid this.
         */
        mmc_io_rw_direct(card, 0, 0, 0xff, 0, &dummy);
    }
    count = 0;
    for (i = 1; i <= 7; i++) {
        if (pending & (1 << i)) {
            func = card->sdio_func[i - 1];
            if (!func) {
                /*pr_warn("%s: pending IRQ for non-existent function\n",
                    mmc_card_id(card));*/
                    SD_LOGW("pending IRQ for non-existent function\n");
                ret = -EINVAL;
            } else if (func->irq_handler) {
                func->irq_handler(func);
                count++;
            } else {
                /*SD_LOGW("%s: pending IRQ with no handler\n",
                    sdio_func_id(func));*/
                SD_LOGW("pending IRQ with no handler\n");
                ret = -EINVAL;
            }
        }
    }

    if (count)
        return count;

    return ret;
}

void sdio_run_irqs(struct mmc_host *host)
{
    mmc_claim_host(host);
    host->sdio_irq_pending = true;
    process_sdio_pending_irqs(host);
    mmc_release_host(host);
}
//EXPORT_SYMBOL_GPL(sdio_run_irqs);

static int sdio_irq_thread(void *_host)
{
    struct mmc_host *host = _host;
    struct mmc_card *card = host->card;
    struct sched_param param = { .sched_priority = 1 };
    unsigned long period, idle_period;
    int ret = 0;


    /*
     * We want to allow for SDIO cards to work even on non SDIO
     * aware hosts.  One thing that non SDIO host cannot do is
     * asynchronous notification of pending SDIO card interrupts
     * hence we poll for them in that case.
     */
    idle_period = 10;
    period = (host->caps & MMC_CAP_SDIO_IRQ) ?
        200 : idle_period;

    SD_LOGD("%s: IRQ thread started (poll period = %lu jiffies)\n", __func__,period);

    do {
        /*
         * We claim the host here on drivers behalf for a couple
         * reasons:
         *
         * 1) it is already needed to retrieve the CCCR_INTx;
         * 2) we want the driver(s) to clear the IRQ condition ASAP;
         * 3) we need to control the abort condition locally.
         *
         * Just like traditional hard IRQ handlers, we expect SDIO
         * IRQ handlers to be quick and to the point, so that the
         * holding of the host lock does not cover too much work
         * that doesn't require that lock to be held.
         */
        mmc_claim_host(host);
        ret = process_sdio_pending_irqs(host);
        host->sdio_irq_pending = false;
        mmc_release_host(host);

        /*
         * Give other threads a chance to run in the presence of
         * errors.
         */
        if (ret < 0) {
            if (!HAL_Thread_Should_Stop(host->sdio_irq_thread_stop))
                HAL_MSleep(1000);
        }

        /*
         * Adaptive polling frequency based on the assumption
         * that an interrupt will be closely followed by more.
         * This has a substantial benefit for network devices.
         */
#if 0
        if (!(host->caps & MMC_CAP_SDIO_IRQ)) {
            if (ret > 0)
                period /= 2;
            else {
                period++;
                if (period > idle_period)
                    period = idle_period;
            }
        }
#endif
        //set_current_state(TASK_INTERRUPTIBLE);
        if (host->caps & MMC_CAP_SDIO_IRQ){
            HAL_SDC_Enable_Sdio_Irq(host, 1);
            OS_SemaphoreWait(&host->sdio_irq_signal,portMAX_DELAY);
            /*
            while(1){
                #define readl(addr)     (*((volatile unsigned long  *)(addr)))
                ret = OS_SemaphoreWait(&host->sdio_irq_signal,period);
                if(ret == OS_E_TIMEOUT){
                    printf("Imask %x\n",readl(0x4021000+0x30));
                    printf("rint %x\n",readl(0x4021000+0x38));
                }else if(ret ==OS_OK){
                    break;
                }
            }
            */
        } else if (!HAL_Thread_Should_Stop(host->sdio_irq_thread_stop)){
            HAL_MSleep(period);
        }
    } while (!HAL_Thread_Should_Stop(host->sdio_irq_thread_stop));

    if (host->caps & MMC_CAP_SDIO_IRQ)
        HAL_SDC_Enable_Sdio_Irq(host, 0);

    SD_LOGD("IRQ thread exiting with code %d\n",ret);
    HAL_ThreadEnd(host->sdio_irq_thread_stop);
    printf("%s,%d\n",__func__,__LINE__);
    printf("IRQ thread exiting with code %d\n",ret);
    HAL_ThreadDelete();
    return ret;
}
static int irq_thread_pri = 20;

void sdio_set_irq_thread_pri(int pri)
{
       irq_thread_pri = pri;
}

static int sdio_card_irq_get(struct mmc_card *card)
{
    struct mmc_host *host = card->host;

//  WARN_ON(!host->claimed);

    if (!host->sdio_irqs++) {
        if (!(host->caps2 & MMC_CAP2_SDIO_IRQ_NOTHREAD)) {
            int ret = 0;
            //atomic_set(&host->sdio_irq_thread_abort, 0);
            HAL_ATMOTIC_SET(host->sdio_irq_thread_abort, 0);
            //host->sdio_irq_thread =
            //  kthread_run(sdio_irq_thread, host,
                //      "ksdioirqd/%s", mmc_hostname(host));
            OS_ThreadSetInvalid(&host->sdio_irq_thread);
            ret = OS_ThreadCreate(&host->sdio_irq_thread, "ksdioirqd", \
                (void *)sdio_irq_thread, host,irq_thread_pri, 16*1024);
            if (ret != OS_OK) {
                //int err = PTR_ERR(host->sdio_irq_thread);
                host->sdio_irqs--;
                return ret;
            }
        } else if (host->caps & MMC_CAP_SDIO_IRQ) {
            //host->ops->enable_sdio_irq(host, 1);
            HAL_SDC_Enable_Sdio_Irq(host, 1);
        }
    }

    return 0;
}

static int sdio_card_irq_put(struct mmc_card *card)
{
    struct mmc_host *host = card->host;

    /*WARN_ON(!host->claimed);*/
    SD_BUG_ON(host->sdio_irqs < 1);

    if (!--host->sdio_irqs) {
        if (!(host->caps2 & MMC_CAP2_SDIO_IRQ_NOTHREAD)) {
            //atomic_set(&host->sdio_irq_thread_abort, 1);
            HAL_ATMOTIC_SET(host->sdio_irq_thread_abort, 1);
            HAL_ThreadStop(host->sdio_irq_thread_stop);
            OS_SemaphoreRelease(&host->sdio_irq_signal);
            //kthread_stop(host->sdio_irq_thread);
        } else if (host->caps & MMC_CAP_SDIO_IRQ) {
            //host->ops->enable_sdio_irq(host, 0);
            HAL_SDC_Enable_Sdio_Irq(host, 0);
        }
    }

    return 0;
}

/* If there is only 1 function registered set sdio_single_irq */
static void sdio_single_irq_set(struct mmc_card *card)
{
    struct sdio_func *func;
    int i;


    card->sdio_single_irq = NULL;
    if ((card->host->caps & MMC_CAP_SDIO_IRQ) &&
        card->host->sdio_irqs == 1)
        for (i = 0; i < card->sdio_funcs; i++) {
               func = card->sdio_func[i];
               if (func && func->irq_handler) {
                   card->sdio_single_irq = func;
                   break;
               }
           }
}

/**
 *  sdio_claim_irq - claim the IRQ for a SDIO function
 *  @func: SDIO function
 *  @handler: IRQ handler callback
 *
 *  Claim and activate the IRQ for the given SDIO function. The provided
 *  handler will be called when that IRQ is asserted.  The host is always
 *  claimed already when the handler is called so the handler must not
 *  call sdio_claim_host() nor sdio_release_host().
 */
int sdio_claim_irq(struct sdio_func *func, sdio_irq_handler_t *handler)
{
    int ret;
    unsigned char reg;
    struct mmc_card *card = func->card;

    SD_BUG_ON(!func);
    SD_BUG_ON(!func->card);

    SD_LOGD("SDIO: Enabling IRQ for %ld...\n", HAL_PR_SZ_L(func->num));

    if (func->irq_handler) {
        //SD_LOGD("SDIO: IRQ for %s already in use.\n", sdio_func_id(func));
        SD_LOGD("SDIO: IRQ for %ld already in use.\n", HAL_PR_SZ_L(func->num));
        return -EBUSY;
    }
    ret = mmc_io_rw_direct(func->card, 0, 0, SDIO_CCCR_IENx, 0, &reg);
    if (ret)
        return ret;

    reg |= 1 << func->num;

    reg |= 1; /* Master interrupt enable */

    ret = mmc_io_rw_direct(func->card, 1, 0, SDIO_CCCR_IENx, reg, NULL);
    if (ret)
        return ret;

    func->irq_handler = handler;
    ret = sdio_card_irq_get(func->card);
    if (ret)
        func->irq_handler = NULL;
    sdio_single_irq_set(func->card);

    return ret;
}
//XPORT_SYMBOL_GPL(sdio_claim_irq);

/**
 *  sdio_release_irq - release the IRQ for a SDIO function
 *  @func: SDIO function
 *
 *  Disable and release the IRQ for the given SDIO function.
 */
int sdio_release_irq(struct sdio_func *func)
{
    int ret;
    unsigned char reg;
    struct mmc_card *card = func->card;

    SD_BUG_ON(!func);
    SD_BUG_ON(!func->card);

    //SDC_LOGD("SDIO: Disabling IRQ for %s...\n", sdio_func_id(func));
    SD_LOGD("SDIO: Disabling IRQ for %ld...\n", HAL_PR_SZ_L(func->num));

    if (func->irq_handler) {
        func->irq_handler = NULL;
        sdio_card_irq_put(func->card);
        sdio_single_irq_set(func->card);
    }

    ret = mmc_io_rw_direct(func->card, 0, 0, SDIO_CCCR_IENx, 0, &reg);
    if (ret)
        return ret;

    reg &= ~(1 << func->num);

    /* Disable master interrupt with the last function interrupt */
    if (!(reg & 0xFE))
        reg = 0;

    ret = mmc_io_rw_direct(func->card, 1, 0, SDIO_CCCR_IENx, reg, NULL);
    if (ret)
        return ret;

    return 0;
}
//EXPORT_SYMBOL_GPL(sdio_release_irq);
