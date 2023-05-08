/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-12-3       Wayne            First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_TIMER) && defined(RT_USING_HWTIMER)

#include <rtdevice.h>
#include "NuMicro.h"
#include <drv_sys.h>
#include "nu_timer.h"

/* Private define ---------------------------------------------------------------*/
#define NU_TIMER_DEVICE(timer) (nu_timer_t)(timer)

enum
{
    TIMER_START = -1,
#if defined(BSP_USING_TIMER0)
    TIMER0_IDX,
#endif
#if defined(BSP_USING_TIMER1)
    TIMER1_IDX,
#endif
#if defined(BSP_USING_TIMER2)
    TIMER2_IDX,
#endif
#if defined(BSP_USING_TIMER3)
    TIMER3_IDX,
#endif
    /* BSP_USING_TIMER4 is reserved for Systick usage. */
    TIMER_CNT
};

/* Private typedef --------------------------------------------------------------*/
struct nu_timer
{
    rt_hwtimer_t  parent;
    char         *name;
    uint32_t      idx;
    IRQn_Type     irqn;
    E_SYS_IPRST   rstidx;
    E_SYS_IPCLK   clkidx;
};
typedef struct nu_timer *nu_timer_t;

/* Private functions ------------------------------------------------------------*/
static void nu_timer_init(rt_hwtimer_t *timer, rt_uint32_t state);
static rt_err_t nu_timer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t opmode);
static void nu_timer_stop(rt_hwtimer_t *timer);
static rt_uint32_t nu_timer_count_get(rt_hwtimer_t *timer);
static rt_err_t nu_timer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args);

/* Public functions -------------------------------------------------------------*/


/* Private variables ------------------------------------------------------------*/
static struct nu_timer nu_timer_arr [] =
{
#if defined(BSP_USING_TIMER0)
    {
        .name = "timer0",
        .idx  = 0,
        .irqn = IRQ_TMR0,
        .rstidx = TIMER0RST,
        .clkidx = TIMER0CKEN,
    },
#endif
#if defined(BSP_USING_TIMER1)
    {
        .name = "timer1",
        .idx  = 1,
        .irqn = IRQ_TMR1,
        .rstidx = TIMER1RST,
        .clkidx = TIMER1CKEN,
    },
#endif
#if defined(BSP_USING_TIMER2)
    {
        .name = "timer2",
        .idx  = 2,
        .irqn = IRQ_TMR2,
        .rstidx = TIMER2RST,
        .clkidx = TIMER2CKEN,
    },
#endif
#if defined(BSP_USING_TIMER3)
    {
        .name = "timer3",
        .idx  = 3,
        .irqn = IRQ_TMR3,
        .rstidx = TIMER3RST,
        .clkidx = TIMER3CKEN,
    },
#endif
    /* BSP_USING_TIMER4 is reserved for Systick usage. */
};

static struct rt_hwtimer_info nu_timer_info =
{
    12000000,            /* maximum count frequency */
    46875,               /* minimum count frequency */
    0xFFFFFF,            /* the maximum counter value */
    HWTIMER_CNTMODE_UP,  /* Increment or Decreasing count mode */
};

static struct rt_hwtimer_ops nu_timer_ops =
{
    nu_timer_init,
    nu_timer_start,
    nu_timer_stop,
    nu_timer_count_get,
    nu_timer_control
};

/* Functions define ------------------------------------------------------------*/
static void nu_timer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    nu_timer_t psNuTmr = NU_TIMER_DEVICE(timer);
    RT_ASSERT(psNuTmr != RT_NULL);

    if (1 == state)
    {
        uint32_t timer_clk;
        struct rt_hwtimer_info *info = &nu_timer_info;

        timer_clk = TIMER_GetModuleClock(psNuTmr->idx);
        info->maxfreq = timer_clk;
        info->minfreq = timer_clk / 256;
        TIMER_Open(psNuTmr->idx, TIMER_ONESHOT_MODE, 1);
        TIMER_EnableInt(psNuTmr->idx);
        rt_hw_interrupt_umask(psNuTmr->irqn);
    }
    else
    {
        rt_hw_interrupt_mask(psNuTmr->irqn);
        TIMER_DisableInt(psNuTmr->idx);
        TIMER_Close(psNuTmr->idx);
    }
}

static rt_err_t nu_timer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t opmode)
{
    rt_err_t ret = -RT_EINVAL;
    rt_uint32_t u32OpMode;

    nu_timer_t psNuTmr = NU_TIMER_DEVICE(timer);
    RT_ASSERT(psNuTmr != RT_NULL);

    if (cnt <= 1 || cnt > 0xFFFFFF)
    {
        goto exit_nu_timer_start;
    }

    switch (opmode)
    {
    case HWTIMER_MODE_PERIOD:
        u32OpMode = TIMER_PERIODIC_MODE;
        break;

    case HWTIMER_MODE_ONESHOT:
        u32OpMode = TIMER_ONESHOT_MODE;
        break;

    default:
        goto exit_nu_timer_start;
    }

    TIMER_SET_CMP_VALUE(psNuTmr->idx, cnt);
    TIMER_SET_OPMODE(psNuTmr->idx, u32OpMode);
    TIMER_EnableInt(psNuTmr->idx);
    rt_hw_interrupt_umask(psNuTmr->irqn);

    TIMER_Start(psNuTmr->idx);

    ret = RT_EOK;

exit_nu_timer_start:

    return -(ret);
}

static void nu_timer_stop(rt_hwtimer_t *timer)
{
    nu_timer_t psNuTmr = NU_TIMER_DEVICE(timer);
    RT_ASSERT(psNuTmr != RT_NULL);

    rt_hw_interrupt_mask(psNuTmr->irqn);
    TIMER_DisableInt(psNuTmr->idx);
    TIMER_Stop(psNuTmr->idx);
    TIMER_ClearCounter(psNuTmr->idx);
}

static rt_uint32_t nu_timer_count_get(rt_hwtimer_t *timer)
{
    nu_timer_t psNuTmr = NU_TIMER_DEVICE(timer);
    RT_ASSERT(psNuTmr != RT_NULL);

    return TIMER_GetCounter(psNuTmr->idx);
}

static rt_err_t nu_timer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t ret = RT_EOK;
    nu_timer_t psNuTmr = NU_TIMER_DEVICE(timer);
    RT_ASSERT(psNuTmr != RT_NULL);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        uint32_t clk;
        uint32_t pre;

        clk = TIMER_GetModuleClock(psNuTmr->idx);
        pre = clk / *((uint32_t *)args) - 1;
        TIMER_SET_PRESCALE_VALUE(psNuTmr->idx, pre);
        *((uint32_t *)args) = clk / (pre + 1) ;
    }
    break;

    case HWTIMER_CTRL_STOP:
        TIMER_Stop(psNuTmr->idx);
        break;

    default:
        ret = -RT_EINVAL;
        break;
    }

    return -(ret);
}

/**
 * All UART interrupt service routine
 */
static void nu_timer_isr(int vector, void *param)
{
    nu_timer_t psNuTmr = NU_TIMER_DEVICE(param);
    RT_ASSERT(psNuTmr != RT_NULL);

    if (TIMER_GetIntFlag(psNuTmr->idx))
    {
        TIMER_ClearIntFlag(psNuTmr->idx);
        rt_device_hwtimer_isr(&psNuTmr->parent);
    }
}

int rt_hw_timer_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;
    for (i = (TIMER_START + 1); i < TIMER_CNT; i++)
    {
        nu_sys_ipclk_enable(nu_timer_arr[i].clkidx);

        nu_sys_ip_reset(nu_timer_arr[i].rstidx);

        /* Register Etimer information. */
        nu_timer_arr[i].parent.info = &nu_timer_info;

        /* Register Etimer operation. */
        nu_timer_arr[i].parent.ops = &nu_timer_ops;

        /* Register Etimer interrupt service routine. */
        rt_hw_interrupt_install(nu_timer_arr[i].irqn, nu_timer_isr, &nu_timer_arr[i], nu_timer_arr[i].name);

        /* Register RT hwtimer device. */
        ret = rt_device_hwtimer_register(&nu_timer_arr[i].parent, nu_timer_arr[i].name, &nu_timer_arr[i]);
        RT_ASSERT(ret == RT_EOK);
    }
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);

#endif //#if defined(BSP_USING_TIMER) && defined(RT_USING_HWTIMER)
