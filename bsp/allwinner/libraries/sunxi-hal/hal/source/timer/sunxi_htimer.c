/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "sunxi_htimer.h"
#include "aw_common.h"
#include <stdlib.h>
#include <io.h>
#include <interrupt.h>

static struct sunxi_htimer *g_htimer;

static const int sunxi_htimer_irq_num[] =
{
    SUNXI_IRQ_HSTIMER0,
    SUNXI_IRQ_HSTIMER1,
};


static void sunxi_htimer_irq_handle(int dummy, void *data)
{
    struct sunxi_htimer *timer = (struct sunxi_htimer *)data;

    /* clear pending */
    writel((0x1 << timer->timer_id), HTIMER_IRQ_ST_REG);

    /*callback*/
    if (timer->callback != NULL)
    {
        timer->callback(timer->param);
    }
}

static void sunxi_htimer_sync(uint32_t timer)
{
    uint32_t old = readl(HTIMER_CNTVAL_LO_REG(timer));

    while ((old - readl(HTIMER_CNTVAL_LO_REG(timer))) < HTIMER_SYNC_TICKS)
    {
        int i = 10;
        while (i--);
        break;
    }
}

void sunxi_htimer_stop(uint32_t timer)
{
    uint32_t val = readl(HTIMER_CTL_REG(timer));

    writel(val & ~HTIMER_CTL_ENABLE, HTIMER_CTL_REG(timer));

    sunxi_htimer_sync(timer);
}

void sunxi_htimer_start(uint32_t timer, bool periodic)
{
    uint32_t val = readl(HTIMER_CTL_REG(timer));

    if (periodic)
    {
        val &= ~HTIMER_CTL_ONESHOT;
    }
    else
    {
        val |= HTIMER_CTL_ONESHOT;
    }

    val |= HTIMER_CTL_CLK_PRES(1);          //100M

    writel(val | HTIMER_CTL_ENABLE | HTIMER_CTL_RELOAD, HTIMER_CTL_REG(timer));
}

static void sunxi_htimer_setup(uint32_t tick, uint32_t timer)
{
    writel(tick, HTIMER_INTVAL_LO_REG(timer));
}

int sunxi_htimer_set_oneshot(uint32_t delay_us, uint32_t timer, timer_callback callback, void *callback_param)
{
    uint32_t tick = delay_us * 100;

    if (tick < g_htimer[timer].min_delta_ticks || tick > g_htimer[timer].max_delta_ticks)
    {
        HTIMER_INFO("not support!\n");
        return -1;
    }

    if (callback != NULL)
    {
        g_htimer[timer].callback = callback;
        g_htimer[timer].param = callback_param;
    }

    sunxi_htimer_stop(timer);

    sunxi_htimer_setup(tick, timer);

    sunxi_htimer_start(timer, false);
}

int sunxi_htimer_set_periodic(uint32_t delay_us, uint32_t timer, timer_callback callback, void *callback_param)
{
    uint32_t tick = delay_us * 100;

    if (tick < g_htimer[timer].min_delta_ticks || tick > g_htimer[timer].max_delta_ticks)
    {
        HTIMER_INFO("not support!\n");
        return -1;
    }

    if (callback != NULL)
    {
        g_htimer[timer].callback = callback;
        g_htimer[timer].param = callback_param;
    }

    sunxi_htimer_stop(timer);

    sunxi_htimer_setup(tick, timer);

    sunxi_htimer_start(timer, true);

}

void sunxi_htimer_init(void)
{
    int i;
    struct sunxi_htimer *timer = NULL;
    uint32_t val;
    uint32_t size = ARRAY_SIZE(sunxi_htimer_irq_num);

    for (i = 0; i < size; i++)
    {
        /* disable all hrtimer */
        val = readl(HTIMER_CTL_REG(i));
        writel(val & ~HTIMER_CTL_ENABLE, HTIMER_CTL_REG(i));
    }

    /* clear pending */
    writel(0x3, HTIMER_IRQ_ST_REG);

    timer = (struct sunxi_htimer *)malloc(size * sizeof(struct sunxi_htimer));
    if (timer == NULL)
    {
        HTIMER_INFO("alloc memory error!\n");
        return;
    }

    for (i = 0; i < size; i++)
    {
        timer[i].timer_id = i;
        timer[i].clk_rate = 200000000;      //ahb1,should get form clk driver
        timer[i].irq = sunxi_htimer_irq_num[i];
        timer[i].min_delta_ticks = HTIMER_SYNC_TICKS;
        timer[i].max_delta_ticks = 0xffffffff;
        timer[i].callback = NULL;
        timer[i].param = NULL;
        irq_request(timer[i].irq, sunxi_htimer_irq_handle, (void *)&timer[i]);
    }

    /*enable timer irq*/
    for (i = 0; i < size; i++)
    {
        val = readl(HTIMER_IRQ_EN_REG);
        val |= HTIMER_IRQ_EN(i);
        writel(val, HTIMER_IRQ_EN_REG);
    }

    /* enable irq */
    for (i = 0; i < size; i++)
    {
        irq_enable(timer[i].irq);
    }

    g_htimer = timer;

}

