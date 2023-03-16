/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-9-17       Wayne            First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_TIMER) && defined(RT_USING_HWTIMER)

#include <rtdevice.h>
#include "NuMicro.h"
#include <drv_sys.h>

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
#if defined(BSP_USING_TIMER4)
    TIMER4_IDX,
#endif
#if defined(BSP_USING_TIMER5)
    TIMER5_IDX,
#endif
#if defined(BSP_USING_TIMER6)
    TIMER6_IDX,
#endif
#if defined(BSP_USING_TIMER7)
    TIMER7_IDX,
#endif
#if defined(BSP_USING_TIMER8)
    TIMER8_IDX,
#endif
#if defined(BSP_USING_TIMER9)
    TIMER9_IDX,
#endif
#if defined(BSP_USING_TIMER10)
    TIMER10_IDX,
#endif
#if defined(BSP_USING_TIMER11)
    TIMER11_IDX,
#endif
    TIMER_CNT
};

/* Private typedef --------------------------------------------------------------*/
struct nu_timer
{
    rt_hwtimer_t  parent;
    char         *name;
    TIMER_T      *base;
    IRQn_Type     irqn;
    uint32_t      rstidx;
    uint32_t      modid;
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
    { .name = "timer0", .base  = TIMER0, .irqn = TMR0_IRQn, .rstidx = TMR0_RST, .modid = TMR0_MODULE  },
#endif
#if defined(BSP_USING_TIMER1)
    { .name = "timer1", .base  = TIMER1, .irqn = TMR1_IRQn, .rstidx = TMR1_RST, .modid = TMR1_MODULE  },
#endif
#if defined(BSP_USING_TIMER2)
    { .name = "timer2", .base  = TIMER2, .irqn = TMR2_IRQn, .rstidx = TMR2_RST, .modid = TMR2_MODULE  },
#endif
#if defined(BSP_USING_TIMER3)
    { .name = "timer3", .base  = TIMER3, .irqn = TMR3_IRQn, .rstidx = TMR3_RST, .modid = TMR3_MODULE  },
#endif
#if defined(BSP_USING_TIMER4)
    { .name = "timer4", .base  = TIMER4, .irqn = TMR4_IRQn, .rstidx = TMR4_RST, .modid = TMR4_MODULE  },
#endif
#if defined(BSP_USING_TIMER5)
    { .name = "timer5", .base  = TIMER5, .irqn = TMR5_IRQn, .rstidx = TMR5_RST, .modid = TMR5_MODULE  },
#endif
#if defined(BSP_USING_TIMER6)
    { .name = "timer6", .base  = TIMER6, .irqn = TMR6_IRQn, .rstidx = TMR6_RST, .modid = TMR6_MODULE  },
#endif
#if defined(BSP_USING_TIMER7)
    { .name = "timer7", .base  = TIMER7, .irqn = TMR7_IRQn, .rstidx = TMR7_RST, .modid = TMR7_MODULE  },
#endif
#if defined(BSP_USING_TIMER8)
    { .name = "timer8", .base  = TIMER8, .irqn = TMR8_IRQn, .rstidx = TMR8_RST, .modid = TMR8_MODULE  },
#endif
#if defined(BSP_USING_TIMER9)
    { .name = "timer9", .base  = TIMER9, .irqn = TMR9_IRQn, .rstidx = TMR9_RST, .modid = TMR9_MODULE  },
#endif
#if defined(BSP_USING_TIMER10)
    { .name = "timer10", .base  = TIMER10, .irqn = TMR10_IRQn, .rstidx = TMR10_RST, .modid = TMR10_MODULE  },
#endif
#if defined(BSP_USING_TIMER11)
    { .name = "timer11", .base  = TIMER11, .irqn = TMR11_IRQn, .rstidx = TMR11_RST, .modid = TMR11_MODULE  },
#endif
};

static struct rt_hwtimer_info nu_timer_info =
{
    __HXT,               /* maximum count frequency */
    (__HXT / 256),       /* minimum count frequency */
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

        timer_clk = TIMER_GetModuleClock(psNuTmr->base);
        info->maxfreq = timer_clk;
        info->minfreq = timer_clk / 256;
        TIMER_Open(psNuTmr->base, TIMER_ONESHOT_MODE, 1);
        TIMER_EnableInt(psNuTmr->base);
        rt_hw_interrupt_umask(psNuTmr->irqn);
    }
    else
    {
        rt_hw_interrupt_mask(psNuTmr->irqn);
        TIMER_DisableInt(psNuTmr->base);
        TIMER_Close(psNuTmr->base);
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

    TIMER_SET_CMP_VALUE(psNuTmr->base, cnt);
    TIMER_SET_OPMODE(psNuTmr->base, u32OpMode);
    TIMER_EnableInt(psNuTmr->base);
    rt_hw_interrupt_umask(psNuTmr->irqn);

    TIMER_Start(psNuTmr->base);

    ret = RT_EOK;

exit_nu_timer_start:

    return -(ret);
}

static void nu_timer_stop(rt_hwtimer_t *timer)
{
    nu_timer_t psNuTmr = NU_TIMER_DEVICE(timer);
    RT_ASSERT(psNuTmr != RT_NULL);

    rt_hw_interrupt_mask(psNuTmr->irqn);
    TIMER_DisableInt(psNuTmr->base);
    TIMER_Stop(psNuTmr->base);
    TIMER_ResetCounter(psNuTmr->base);
}

static rt_uint32_t nu_timer_count_get(rt_hwtimer_t *timer)
{
    nu_timer_t psNuTmr = NU_TIMER_DEVICE(timer);
    RT_ASSERT(psNuTmr != RT_NULL);

    return TIMER_GetCounter(psNuTmr->base);
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

        clk = TIMER_GetModuleClock(psNuTmr->base);
        pre = clk / *((uint32_t *)args) - 1;
        TIMER_SET_PRESCALE_VALUE(psNuTmr->base, pre);
        *((uint32_t *)args) = clk / (pre + 1) ;
    }
    break;

    case HWTIMER_CTRL_STOP:
        TIMER_Stop(psNuTmr->base);
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

    if (TIMER_GetIntFlag(psNuTmr->base))
    {
        TIMER_ClearIntFlag(psNuTmr->base);
        rt_device_hwtimer_isr(&psNuTmr->parent);
    }
}

int rt_hw_timer_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;
    for (i = (TIMER_START + 1); i < TIMER_CNT; i++)
    {
        CLK_EnableModuleClock(nu_timer_arr[i].modid);

        SYS_ResetModule(nu_timer_arr[i].rstidx);

        /* Register Timer information. */
        nu_timer_arr[i].parent.info = &nu_timer_info;

        /* Register Timer operation. */
        nu_timer_arr[i].parent.ops = &nu_timer_ops;

        /* Register Timer interrupt service routine. */
        rt_hw_interrupt_install(nu_timer_arr[i].irqn, nu_timer_isr, &nu_timer_arr[i], nu_timer_arr[i].name);

        /* Register RT hwtimer device. */
        ret = rt_device_hwtimer_register(&nu_timer_arr[i].parent, nu_timer_arr[i].name, &nu_timer_arr[i]);
        RT_ASSERT(ret == RT_EOK);
    }
    return 0;
}

INIT_BOARD_EXPORT(rt_hw_timer_init);

#endif //#if defined(BSP_USING_TIMER) && defined(RT_USING_HWTIMER)
