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

/* Private define ---------------------------------------------------------------*/
#define NU_TIMER_DEVICE(etimer) (nu_etimer_t)(etimer)

enum
{
    ETIMER_START = -1,
#if defined(BSP_USING_TIMER0)
    ETIMER0_IDX,
#endif
#if defined(BSP_USING_TIMER1)
    ETIMER1_IDX,
#endif
#if defined(BSP_USING_TIMER2)
    ETIMER2_IDX,
#endif
#if defined(BSP_USING_TIMER3)
    ETIMER3_IDX,
#endif
#if defined(BSP_USING_TIMER4)
    ETIMER4_IDX,
#endif
    /* BSP_USING_TIMER5 is reserved for Systick usage. */
    ETIMER_CNT
};

/* Private typedef --------------------------------------------------------------*/
struct nu_etimer
{
    rt_hwtimer_t  parent;
    char         *name;
    uint32_t      idx;
    IRQn_Type     irqn;
    E_SYS_IPRST   rstidx;
    E_SYS_IPCLK   clkidx;
};
typedef struct nu_etimer *nu_etimer_t;

/* Private functions ------------------------------------------------------------*/
static void nu_etimer_init(rt_hwtimer_t *timer, rt_uint32_t state);
static rt_err_t nu_etimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t opmode);
static void nu_etimer_stop(rt_hwtimer_t *timer);
static rt_uint32_t nu_etimer_count_get(rt_hwtimer_t *timer);
static rt_err_t nu_etimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args);

/* Public functions -------------------------------------------------------------*/


/* Private variables ------------------------------------------------------------*/
static struct nu_etimer nu_etimer_arr [] =
{
#if defined(BSP_USING_TIMER0)
    {
        .name = "etimer0",
        .idx  = 0,
        .irqn = IRQ_TIMER0,
        .rstidx = TIMER0RST,
        .clkidx = TIMER0CKEN,
    },
#endif
#if defined(BSP_USING_TIMER1)
    {
        .name = "etimer1",
        .idx  = 1,
        .irqn = IRQ_TIMER1,
        .rstidx = TIMER1RST,
        .clkidx = TIMER1CKEN,
    },
#endif
#if defined(BSP_USING_TIMER2)
    {
        .name = "etimer2",
        .idx  = 2,
        .irqn = IRQ_TIMER2,
        .rstidx = TIMER2RST,
        .clkidx = TIMER2CKEN,
    },
#endif
#if defined(BSP_USING_TIMER3)
    {
        .name = "etimer3",
        .idx  = 3,
        .irqn = IRQ_TIMER3,
        .rstidx = TIMER3RST,
        .clkidx = TIMER3CKEN,
    },
#endif
#if defined(BSP_USING_TIMER4)
    {
        .name = "etimer4",
        .idx  = 4,
        .irqn = IRQ_TIMER4,
        .rstidx = TIMER4RST,
        .clkidx = TIMER4CKEN,
    },
#endif
    /* BSP_USING_TIMER5 is reserved for Systick usage. */
};

static struct rt_hwtimer_info nu_etimer_info =
{
    12000000,            /* maximum count frequency */
    46875,               /* minimum count frequency */
    0xFFFFFF,            /* the maximum counter value */
    HWTIMER_CNTMODE_UP,  /* Increment or Decreasing count mode */
};

static struct rt_hwtimer_ops nu_etimer_ops =
{
    nu_etimer_init,
    nu_etimer_start,
    nu_etimer_stop,
    nu_etimer_count_get,
    nu_etimer_control
};

/* Functions define ------------------------------------------------------------*/
static void nu_etimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    nu_etimer_t psNuETmr = NU_TIMER_DEVICE(timer);
    RT_ASSERT(psNuETmr != RT_NULL);

    if (1 == state)
    {
        uint32_t timer_clk;
        struct rt_hwtimer_info *info = &nu_etimer_info;

        timer_clk = ETIMER_GetModuleClock(psNuETmr->idx);
        info->maxfreq = timer_clk;
        info->minfreq = timer_clk / 256;
        ETIMER_Open(psNuETmr->idx, ETIMER_ONESHOT_MODE, 1);
        ETIMER_EnableInt(psNuETmr->idx);
        rt_hw_interrupt_umask(psNuETmr->irqn);
    }
    else
    {
        rt_hw_interrupt_mask(psNuETmr->irqn);
        ETIMER_DisableInt(psNuETmr->idx);
        ETIMER_Close(psNuETmr->idx);
    }
}

static rt_err_t nu_etimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t opmode)
{
    rt_err_t ret = RT_EINVAL;
    rt_uint32_t u32OpMode;

    nu_etimer_t psNuETmr = NU_TIMER_DEVICE(timer);
    RT_ASSERT(psNuETmr != RT_NULL);

    if (cnt <= 1 || cnt > 0xFFFFFF)
    {
        goto exit_nu_etimer_start;
    }

    switch (opmode)
    {
    case HWTIMER_MODE_PERIOD:
        u32OpMode = ETIMER_PERIODIC_MODE;
        break;

    case HWTIMER_MODE_ONESHOT:
        u32OpMode = ETIMER_ONESHOT_MODE;
        break;

    default:
        goto exit_nu_etimer_start;
    }

    ETIMER_SET_CMP_VALUE(psNuETmr->idx, cnt);
    ETIMER_SET_OPMODE(psNuETmr->idx, u32OpMode);
    ETIMER_EnableInt(psNuETmr->idx);
    rt_hw_interrupt_umask(psNuETmr->irqn);

    ETIMER_Start(psNuETmr->idx);

    ret = RT_EOK;

exit_nu_etimer_start:

    return -(ret);
}

static void nu_etimer_stop(rt_hwtimer_t *timer)
{
    nu_etimer_t psNuETmr = NU_TIMER_DEVICE(timer);
    RT_ASSERT(psNuETmr != RT_NULL);

    rt_hw_interrupt_mask(psNuETmr->irqn);
    ETIMER_DisableInt(psNuETmr->idx);
    ETIMER_Stop(psNuETmr->idx);
    ETIMER_ClearCounter(psNuETmr->idx);
}

static rt_uint32_t nu_etimer_count_get(rt_hwtimer_t *timer)
{
    nu_etimer_t psNuETmr = NU_TIMER_DEVICE(timer);
    RT_ASSERT(psNuETmr != RT_NULL);

    return ETIMER_GetCounter(psNuETmr->idx);
}

static rt_err_t nu_etimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t ret = RT_EOK;
    nu_etimer_t psNuETmr = NU_TIMER_DEVICE(timer);
    RT_ASSERT(psNuETmr != RT_NULL);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        uint32_t clk;
        uint32_t pre;

        clk = ETIMER_GetModuleClock(psNuETmr->idx);
        pre = clk / *((uint32_t *)args) - 1;
        ETIMER_SET_PRESCALE_VALUE(psNuETmr->idx, pre);
        *((uint32_t *)args) = clk / (pre + 1) ;
    }
    break;

    case HWTIMER_CTRL_STOP:
        ETIMER_Stop(psNuETmr->idx);
        break;

    default:
        ret = RT_EINVAL;
        break;
    }

    return -(ret);
}

/**
 * All UART interrupt service routine
 */
static void nu_etimer_isr(int vector, void *param)
{
    nu_etimer_t psNuETmr = NU_TIMER_DEVICE(param);
    RT_ASSERT(psNuETmr != RT_NULL);

    if (ETIMER_GetIntFlag(psNuETmr->idx))
    {
        ETIMER_ClearIntFlag(psNuETmr->idx);
        rt_device_hwtimer_isr(&psNuETmr->parent);
    }
}

int rt_hw_etimer_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;
    for (i = (ETIMER_START + 1); i < ETIMER_CNT; i++)
    {
        nu_sys_ipclk_enable(nu_etimer_arr[i].clkidx);

        nu_sys_ip_reset(nu_etimer_arr[i].rstidx);

        /* Register Etimer information. */
        nu_etimer_arr[i].parent.info = &nu_etimer_info;

        /* Register Etimer operation. */
        nu_etimer_arr[i].parent.ops = &nu_etimer_ops;

        /* Register Etimer interrupt service routine. */
        rt_hw_interrupt_install(nu_etimer_arr[i].irqn, nu_etimer_isr, &nu_etimer_arr[i], nu_etimer_arr[i].name);

        /* Register RT hwtimer device. */
        ret = rt_device_hwtimer_register(&nu_etimer_arr[i].parent, nu_etimer_arr[i].name, &nu_etimer_arr[i]);
        RT_ASSERT(ret == RT_EOK);
    }
    return 0;
}

INIT_BOARD_EXPORT(rt_hw_etimer_init);

#endif //#if defined(BSP_USING_TIMER) && defined(RT_USING_HWTIMER)
