/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-25     RT-Thread    the first version
 */

#include <rtthread.h>
#include <rthw.h>
#include "drv_pl041.h"
#include "drv_ac97.h"
#include "realview.h"

#define DBG_TAG  "PL041"
// #define DBG_LVL         DBG_LOG
// #define DBG_LVL         DBG_INFO
#define DBG_LVL  DBG_WARNING
// #define DBG_LVL         DBG_ERROR
#include <rtdbg.h>

#define FRAME_PERIOD_US    (50)
#define PL041_CHANNEL_NUM  (4)

#define PL041_READ(_a)        (*(volatile rt_uint32_t *)(_a))
#define PL041_WRITE(_a, _v)   (*(volatile rt_uint32_t *)(_a) = (_v))

struct pl041_irq_def
{
    pl041_irq_fun_t fun;
    void *user_data;
};

static struct pl041_irq_def irq_tbl[PL041_CHANNEL_NUM];

static void aaci_pl041_delay(rt_uint32_t us)
{
    volatile int i;

    for (i = us * 10; i != 0; i--);
}

static void aaci_ac97_select_codec(void)
{
    rt_uint32_t v, maincr;

    maincr = AACI_MAINCR_SCRA(0) | AACI_MAINCR_IE | AACI_MAINCR_SL1RXEN | \
             AACI_MAINCR_SL1TXEN | AACI_MAINCR_SL2RXEN | AACI_MAINCR_SL2TXEN;

    v = PL041_READ(&PL041->slfr);
    if (v & AACI_SLFR_2RXV)
    {
        PL041_READ(&PL041->sl2rx);
    }
    if (v & AACI_SLFR_1RXV)
    {
        PL041_READ(&PL041->sl1rx);
    }

    if (maincr != PL041_READ(&PL041->maincr))
    {
        PL041_WRITE(&PL041->maincr, maincr);
        aaci_pl041_delay(1);
    }
}

void aaci_ac97_write(rt_uint16_t reg, rt_uint16_t val)
{
    rt_uint32_t v, timeout;

    aaci_ac97_select_codec();

    PL041_WRITE(&PL041->sl2tx, val << 4);
    PL041_WRITE(&PL041->sl1tx, reg << 12);

    aaci_pl041_delay(FRAME_PERIOD_US);

    timeout = FRAME_PERIOD_US * 8;
    do
    {
        aaci_pl041_delay(1);
        v = PL041_READ(&PL041->slfr);
    }
    while ((v & (AACI_SLFR_1TXB | AACI_SLFR_2TXB)) && --timeout);

    if (v & (AACI_SLFR_1TXB | AACI_SLFR_2TXB))
    {
        LOG_E("timeout waiting for write to complete");
    }
}

rt_uint16_t aaci_ac97_read(rt_uint16_t reg)
{
    rt_uint32_t v, timeout, retries = 10;

    aaci_ac97_select_codec();

    PL041_WRITE(&PL041->sl1tx, (reg << 12) | (1 << 19));
    aaci_pl041_delay(FRAME_PERIOD_US);

    timeout = FRAME_PERIOD_US * 8;
    do
    {
        aaci_pl041_delay(1);
        v = PL041_READ(&PL041->slfr);
    }
    while ((v & AACI_SLFR_1TXB) && --timeout);

    if (v & AACI_SLFR_1TXB)
    {
        LOG_E("timeout on slot 1 TX busy");
        v = ~0x0;
        return v;
    }

    aaci_pl041_delay(FRAME_PERIOD_US);
    timeout = FRAME_PERIOD_US * 8;
    do
    {
        aaci_pl041_delay(1);
        v = PL041_READ(&PL041->slfr) & (AACI_SLFR_1RXV | AACI_SLFR_2RXV);
    }
    while ((v != (AACI_SLFR_1RXV | AACI_SLFR_2RXV)) && --timeout);

    if (v != (AACI_SLFR_1RXV | AACI_SLFR_2RXV))
    {
        LOG_E("timeout on RX valid");
        v = ~0x0;
        return v;
    }

    do
    {
        v = PL041_READ(&PL041->sl1rx) >> 12;
        if (v == reg)
        {
            v = PL041_READ(&PL041->sl2rx) >> 4;
            break;
        }
        else if (--retries)
        {
            LOG_E("ac97 read back fail. retry");
            continue;
        }
        else
        {
            LOG_E("wrong ac97 register read back (%x != %x)", v, reg);
            v = ~0x0;
        }
    }
    while (retries);

    return v;
}

int aaci_pl041_channel_disable(int channel)
{
    rt_uint32_t v;
    void *p_rx, *p_tx;

    p_rx = (void *)((rt_uint32_t)(&PL041->rxcr1) + channel * 0x14);
    p_tx = (void *)((rt_uint32_t)(&PL041->txcr1) + channel * 0x14);
    v = PL041_READ(p_rx);
    v &= ~AACI_CR_EN;
    PL041_WRITE(p_rx, v);
    v = PL041_READ(p_tx);
    v &= ~AACI_CR_EN;
    PL041_WRITE(p_tx, v);
    return 0;
}

int aaci_pl041_channel_enable(int channel)
{
    rt_uint32_t v;
    void *p_rx, *p_tx;

    p_rx = (void *)((rt_uint32_t)(&PL041->rxcr1) + channel * 0x14);
    p_tx = (void *)((rt_uint32_t)(&PL041->txcr1) + channel * 0x14);
    v = PL041_READ(p_rx);
    v |= AACI_CR_EN;
    PL041_WRITE(p_rx, v);
    v = PL041_READ(p_tx);
    v |= AACI_CR_EN;
    PL041_WRITE(p_tx, v);
    return 0;
}

int aaci_pl041_channel_read(int channel, rt_uint16_t *buff, int count)
{
    void *p_data, *p_status;
    int i = 0;

    p_status = (void *)((rt_uint32_t)(&PL041->sr1) + channel * 0x14);
    p_data = (void *)((rt_uint32_t)(&(PL041->dr1[0])) + channel * 0x20);
    for (i = 0; (!(PL041_READ(p_status) & AACI_SR_RXFE)) && (i < count); i++)
    {
        buff[i] = (rt_uint16_t)PL041_READ(p_data);
    }
    return i;
}

int aaci_pl041_channel_write(int channel, rt_uint16_t *buff, int count)
{
    void *p_data, *p_status;
    int i = 0;

    p_status = (void *)((rt_uint32_t)(&PL041->sr1) + channel * 0x14);
    p_data = (void *)((rt_uint32_t)(&(PL041->dr1[0])) + channel * 0x20);
    for (i = 0; (!(PL041_READ(p_status) & AACI_SR_TXFF)) && (i < count); i++)
    {
        PL041_WRITE(p_data, buff[i]);
    }
    return i;
}

int aaci_pl041_channel_cfg(int channel, pl041_cfg_t cgf)
{
    rt_uint32_t v;
    void *p_rx, *p_tx;

    p_rx = (void *)((rt_uint32_t)(&PL041->rxcr1) + channel * 0x14);
    p_tx = (void *)((rt_uint32_t)(&PL041->txcr1) + channel * 0x14);
    v = AACI_CR_FEN | AACI_CR_SZ16 | cgf->itype;
    PL041_WRITE(p_rx, v);
    v = AACI_CR_FEN | AACI_CR_SZ16 | cgf->otype;
    PL041_WRITE(p_tx, v);

    ac97_set_vol(cgf->vol);
    ac97_set_rate(cgf->rate);

    return 0;
}

void aaci_pl041_irq_enable(int channel, rt_uint32_t vector)
{
    rt_uint32_t v;
    void *p_irq;

    vector &= vector & 0x7f;
    p_irq = (void *)((rt_uint32_t)(&PL041->iie1) + channel * 0x14);
    v = PL041_READ(p_irq);
    v |= vector;
    PL041_WRITE(p_irq, v);
}

void aaci_pl041_irq_disable(int channel, rt_uint32_t vector)
{
    rt_uint32_t v;
    void *p_irq;

    vector &= vector & 0x7f;
    p_irq = (void *)((rt_uint32_t)(&PL041->iie1) + channel * 0x14);
    v = PL041_READ(p_irq);
    v &= ~vector;
    PL041_WRITE(p_irq, v);
}

rt_err_t aaci_pl041_irq_register(int channel, pl041_irq_fun_t fun, void *user_data)
{
    if (channel < 0 || channel >= PL041_CHANNEL_NUM)
    {
        LOG_E("%s channel:%d err.", __FUNCTION__, channel);
        return -RT_ERROR;
    }
    irq_tbl[channel].fun = fun;
    irq_tbl[channel].user_data = user_data;
    return RT_EOK;
}

rt_err_t aaci_pl041_irq_unregister(int channel)
{
    if (channel < 0 || channel >= PL041_CHANNEL_NUM)
    {
        LOG_E("%s channel:%d err.", __FUNCTION__, channel);
        return -RT_ERROR;
    }
    irq_tbl[channel].fun = RT_NULL;
    irq_tbl[channel].user_data = RT_NULL;
    return RT_EOK;
}

static void aaci_pl041_irq_handle(int irqno, void *param)
{
    rt_uint32_t mask, channel, m;
    struct pl041_irq_def *_irq = param;
    void *p_status;

    mask = PL041_READ(&PL041->allints);
    PL041_WRITE(&PL041->intclr, mask);

    for (channel = 0; (channel < PL041_CHANNEL_NUM) && (mask); channel++)
    {
        mask = mask >> 7;
        m = mask & 0x7f;
        if (m & AACI_ISR_ORINTR)
        {
            LOG_W("RX overrun on chan %d", channel);
        }

        if (m & AACI_ISR_RXTOINTR)
        {
            LOG_W("RX timeout on chan %d", channel);
        }

        if (mask & AACI_ISR_URINTR)
        {
            LOG_W("TX underrun on chan %d", channel);
        }

        p_status = (void *)((rt_uint32_t)(&PL041->sr1) + channel * 0x14);
        if (_irq[channel].fun != RT_NULL)
        {
            _irq[channel].fun(PL041_READ(p_status), _irq[channel].user_data);
        }
    }
}

rt_err_t aaci_pl041_init(void)
{
    rt_uint32_t i, maincr;

    maincr  = AACI_MAINCR_SCRA(0) | AACI_MAINCR_IE | AACI_MAINCR_SL1RXEN | \
              AACI_MAINCR_SL1TXEN | AACI_MAINCR_SL2RXEN | AACI_MAINCR_SL2TXEN;

    for (i = 0; i < 4; i++)
    {
        void *base = (void *)((rt_uint32_t)(&PL041->rxcr1) + i * 0x14);

        PL041_WRITE(base + AACI_IE, 0);
        PL041_WRITE(base + AACI_TXCR, 0);
        PL041_WRITE(base + AACI_RXCR, 0);
    }

    PL041_WRITE(&PL041->intclr, 0x1fff);
    PL041_WRITE(&PL041->maincr, maincr);

    PL041_WRITE(&PL041->reset, 0);
    aaci_pl041_delay(2);
    PL041_WRITE(&PL041->reset, RESET_NRST);

    rt_hw_interrupt_install(43, aaci_pl041_irq_handle, &irq_tbl, "aaci_pl041");
    rt_hw_interrupt_umask(43);

    return 0;
}

#if 0
#define PL041_DUMP(_v)    rt_kprintf("%32s:addr:0x%08x data:0x%08x\n", #_v, &(_v), (_v))
int _aaci_pl041_reg_dump(int argc, char **argv)
{
    PL041_DUMP(PL041->rxcr1);
    PL041_DUMP(PL041->txcr1);
    PL041_DUMP(PL041->sr1);
    PL041_DUMP(PL041->isr1);
    PL041_DUMP(PL041->iie1);
    PL041_DUMP(PL041->rxcr2);
    PL041_DUMP(PL041->txcr2);
    PL041_DUMP(PL041->sr2);
    PL041_DUMP(PL041->isr2);
    PL041_DUMP(PL041->iie2);
    PL041_DUMP(PL041->rxcr3);
    PL041_DUMP(PL041->txcr3);
    PL041_DUMP(PL041->sr3);
    PL041_DUMP(PL041->isr3);
    PL041_DUMP(PL041->iie3);
    PL041_DUMP(PL041->rxcr4);
    PL041_DUMP(PL041->txcr4);
    PL041_DUMP(PL041->sr4);
    PL041_DUMP(PL041->isr4);
    PL041_DUMP(PL041->iie4);
    PL041_DUMP(PL041->sl1rx);
    PL041_DUMP(PL041->sl1tx);
    PL041_DUMP(PL041->sl2rx);
    PL041_DUMP(PL041->sl2tx);
    PL041_DUMP(PL041->sl12rx);
    PL041_DUMP(PL041->sl12tx);
    PL041_DUMP(PL041->slfr);
    PL041_DUMP(PL041->slistat);
    PL041_DUMP(PL041->slien);
    PL041_DUMP(PL041->intclr);
    PL041_DUMP(PL041->maincr);
    PL041_DUMP(PL041->reset);
    PL041_DUMP(PL041->sync);
    PL041_DUMP(PL041->allints);
    PL041_DUMP(PL041->mainfr);
    PL041_DUMP(PL041->dr1[0]);
    PL041_DUMP(PL041->dr2[0]);
    PL041_DUMP(PL041->dr3[0]);
    PL041_DUMP(PL041->dr4[0]);
    return 0;
}
MSH_CMD_EXPORT_ALIAS(_aaci_pl041_reg_dump, pl041_dump, aaci pl041 dump reg);

#endif
