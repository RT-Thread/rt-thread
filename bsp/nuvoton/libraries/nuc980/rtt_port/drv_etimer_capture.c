/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-1-28       Wayne            First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_TIMER_CAPTURE)

#include <rtdevice.h>
#include "NuMicro.h"
#include <drv_sys.h>

/* Private define ---------------------------------------------------------------*/

/* Timer prescale setting. Since it will affect the pulse width of measure, it is recommended to set to 2. */
#define PSC_DIV     (2)

#define NU_TCAP_DEVICE(etimer) (nu_capture_t*)(etimer)
enum
{
    TCAP_START = -1,
#if defined(BSP_USING_TIMER0_CAPTURE)
    TCAP0_IDX,
#endif
#if defined(BSP_USING_TIMER1_CAPTURE)
    TCAP1_IDX,
#endif
#if defined(BSP_USING_TIMER2_CAPTURE)
    TCAP2_IDX,
#endif
#if defined(BSP_USING_TIMER3_CAPTURE)
    TCAP3_IDX,
#endif
#if defined(BSP_USING_TIMER4_CAPTURE)
    TCAP4_IDX,
#endif
    /* BSP_USING_TIMER5 is reserved for Systick usage. */
    TCAP_CNT
};

/* Private typedef --------------------------------------------------------------*/
typedef struct _timer
{
    struct rt_inputcapture_device parent;
    char          *name;
    uint32_t       idx;
    IRQn_Type      irqn;
    E_SYS_IPRST    rstidx;
    E_SYS_IPCLK    clkidx;

    uint32_t       u32CurrentCnt;
} nu_capture_t;

/* Private functions ------------------------------------------------------------*/
static  rt_err_t nu_capture_init(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_open(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_close(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us);

/* Public functions -------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/
static nu_capture_t nu_etcap_arr [] =
{
#if defined(BSP_USING_TIMER0_CAPTURE)
    {
        .name = "timer0i0",
        .idx  = 0,
        .irqn = IRQ_TIMER0,
        .rstidx = TIMER0RST,
        .clkidx = TIMER0CKEN,
    },
#endif
#if defined(BSP_USING_TIMER1_CAPTURE)
    {
        .name = "timer1i0",
        .idx  = 1,
        .irqn = IRQ_TIMER1,
        .rstidx = TIMER1RST,
        .clkidx = TIMER1CKEN,
    },
#endif
#if defined(BSP_USING_TIMER2_CAPTURE)
    {
        .name = "timer2i0",
        .idx  = 2,
        .irqn = IRQ_TIMER2,
        .rstidx = TIMER2RST,
        .clkidx = TIMER2CKEN,
    },
#endif
#if defined(BSP_USING_TIMER3_CAPTURE)
    {
        .name = "timer3i0",
        .idx  = 3,
        .irqn = IRQ_TIMER3,
        .rstidx = TIMER3RST,
        .clkidx = TIMER3CKEN,
    },
#endif
#if defined(BSP_USING_TIMER4_CAPTURE)
    {
        .name = "timer4i0",
        .idx  = 4,
        .irqn = IRQ_TIMER4,
        .rstidx = TIMER4RST,
        .clkidx = TIMER4CKEN,
    },
#endif
    /* BSP_USING_TIMER5 is reserved for Systick usage. */
};

static struct rt_inputcapture_ops nu_capture_ops =
{
    .init   =   nu_capture_init,
    .open   =   nu_capture_open,
    .close  =   nu_capture_close,
    .get_pulsewidth =   nu_capture_get_pulsewidth,
};

/* Functions define ------------------------------------------------------------*/
static void nu_tcap_isr(int vector, void *param)
{
    nu_capture_t *psNuTCap = NU_TCAP_DEVICE(param);

    RT_ASSERT(psNuTCap != RT_NULL);

    ETIMER_ClearCaptureIntFlag(psNuTCap->idx);

    /* Report caputring data and level. */
    psNuTCap->u32CurrentCnt = ETIMER_GetCaptureData(psNuTCap->idx);
    rt_hw_inputcapture_isr(&psNuTCap->parent, ETIMER_GetCaptureFallingEdgeFlag(psNuTCap->idx));
}

static rt_err_t nu_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us)
{
    nu_capture_t *psNuTCap = NU_TCAP_DEVICE(inputcapture);

    RT_ASSERT(inputcapture != RT_NULL);
    RT_ASSERT(pulsewidth_us != RT_NULL);

    *pulsewidth_us = psNuTCap->u32CurrentCnt / PSC_DIV;

    return RT_EOK;
}

static rt_err_t nu_capture_init(struct rt_inputcapture_device *inputcapture)
{
    nu_capture_t *psNuTCap = NU_TCAP_DEVICE(inputcapture);

    RT_ASSERT(inputcapture != RT_NULL);

    nu_sys_ipclk_enable(psNuTCap->clkidx);
    nu_sys_ip_reset(psNuTCap->rstidx);

    return RT_EOK;
}

static uint8_t cal_time_prescale(nu_capture_t *psNuTCap)
{
    uint32_t u32Clk = ETIMER_GetModuleClock(psNuTCap->idx);

    /* 1 tick = 1/PSC_DIV us */
    return (u32Clk / 1000000 / PSC_DIV) - 1;
}

static rt_err_t nu_capture_open(struct rt_inputcapture_device *inputcapture)
{
    nu_capture_t *psNuTCap = NU_TCAP_DEVICE(inputcapture);

    RT_ASSERT(inputcapture != RT_NULL);

    /* Enable Timer Interrupt */
    rt_hw_interrupt_umask(psNuTCap->irqn);

    /* Clear counter before openning. */
    ETIMER_ClearCounter(psNuTCap->idx);

    ETIMER_Open(psNuTCap->idx, ETIMER_CONTINUOUS_MODE, 1);

    ETIMER_SET_PRESCALE_VALUE(psNuTCap->idx, cal_time_prescale(psNuTCap));

    ETIMER_SET_CMP_VALUE(psNuTCap->idx, 0xFFFFFF);

    ETIMER_EnableCapture(psNuTCap->idx, ETIMER_CAPTURE_COUNTER_RESET_MODE, ETIMER_CAPTURE_RISING_THEN_FALLING_EDGE);

    ETIMER_EnableCaptureInt(psNuTCap->idx);

    ETIMER_Start(psNuTCap->idx);

    return RT_EOK;
}

static rt_err_t nu_capture_close(struct rt_inputcapture_device *inputcapture)
{
    nu_capture_t *psNuTCap = NU_TCAP_DEVICE(inputcapture);

    RT_ASSERT(inputcapture != RT_NULL);

    ETIMER_Stop(psNuTCap->idx);

    ETIMER_DisableCaptureInt(psNuTCap->idx);

    ETIMER_Close(psNuTCap->idx);

    rt_hw_interrupt_mask(psNuTCap->irqn);

    return RT_EOK;
}

/* Init and register timer capture */
static int nu_timer_capture_device_init(void)
{
    int i;

    for (i = (TCAP_START + 1); i < TCAP_CNT; i++)
    {
        /* Register operations */
        nu_etcap_arr[i].parent.ops = &nu_capture_ops;

        /* Install ISR */
        rt_hw_interrupt_install(nu_etcap_arr[i].irqn, nu_tcap_isr, &nu_etcap_arr[i], nu_etcap_arr[i].name);

        /* Register inputcapture device */
        rt_device_inputcapture_register(&nu_etcap_arr[i].parent, nu_etcap_arr[i].name, &nu_etcap_arr[i]);
    }

    return 0;
}
INIT_DEVICE_EXPORT(nu_timer_capture_device_init);

#endif //#if defined(BSP_USING_TIMER_CAPTURE)
