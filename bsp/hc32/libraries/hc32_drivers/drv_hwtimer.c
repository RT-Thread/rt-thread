/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-06-21     CDT               first version
 * 2024-02-20     CDT               support HC32F448
 */

#include <rtdevice.h>
#include "drv_config.h"

// #define DRV_DEBUG
#define LOG_TAG             "drv.hwtimer"
#include <drv_log.h>

#ifdef BSP_USING_HWTIMER

#include "drv_irq.h"

enum
{
#ifdef BSP_USING_TMRA_1
    TMRA_1_INDEX,
#endif
#ifdef BSP_USING_TMRA_2
    TMRA_2_INDEX,
#endif
#ifdef BSP_USING_TMRA_3
    TMRA_3_INDEX,
#endif
#ifdef BSP_USING_TMRA_4
    TMRA_4_INDEX,
#endif
#ifdef BSP_USING_TMRA_5
    TMRA_5_INDEX,
#endif
#ifdef BSP_USING_TMRA_6
    TMRA_6_INDEX,
#endif
#ifdef BSP_USING_TMRA_7
    TMRA_7_INDEX,
#endif
#ifdef BSP_USING_TMRA_8
    TMRA_8_INDEX,
#endif
#ifdef BSP_USING_TMRA_9
    TMRA_9_INDEX,
#endif
#ifdef BSP_USING_TMRA_10
    TMRA_10_INDEX,
#endif
#ifdef BSP_USING_TMRA_11
    TMRA_11_INDEX,
#endif
#ifdef BSP_USING_TMRA_12
    TMRA_12_INDEX,
#endif
};

struct hc32_hwtimer
{
    rt_hwtimer_t time_device;
    CM_TMRA_TypeDef *tmr_handle;
    rt_uint32_t clock_source;
    rt_uint32_t clock;
    rt_uint32_t flag;
    struct
    {
        en_int_src_t enIntSrc;
        IRQn_Type enIRQn;
        rt_uint8_t u8Int_Prio;
        func_ptr_t irq_callback;
    } isr;
    char *name;
};

static struct hc32_hwtimer hc32_hwtimer_obj[] =
{
#ifdef BSP_USING_TMRA_1
    TMRA_1_CONFIG,
#endif
#ifdef BSP_USING_TMRA_2
    TMRA_2_CONFIG,
#endif
#ifdef BSP_USING_TMRA_3
    TMRA_3_CONFIG,
#endif
#ifdef BSP_USING_TMRA_4
    TMRA_4_CONFIG,
#endif
#ifdef BSP_USING_TMRA_5
    TMRA_5_CONFIG,
#endif
#ifdef BSP_USING_TMRA_6
    TMRA_6_CONFIG,
#endif
#ifdef BSP_USING_TMRA_7
    TMRA_7_CONFIG,
#endif
#ifdef BSP_USING_TMRA_8
    TMRA_8_CONFIG,
#endif
#ifdef BSP_USING_TMRA_9
    TMRA_9_CONFIG,
#endif
#ifdef BSP_USING_TMRA_10
    TMRA_10_CONFIG,
#endif
#ifdef BSP_USING_TMRA_11
    TMRA_11_CONFIG,
#endif
#ifdef BSP_USING_TMRA_12
    TMRA_12_CONFIG,
#endif
};

static void _timer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
    stc_tmra_init_t stcTmraInit;
    struct hc32_irq_config irq_config;
    struct hc32_hwtimer *tmr_device = (struct hc32_hwtimer *)timer;

    RT_ASSERT(timer != RT_NULL);

    /* Interrupt configuration */
    irq_config.irq_num = tmr_device->isr.enIRQn;
    irq_config.int_src = tmr_device->isr.enIntSrc;
    irq_config.irq_prio = tmr_device->isr.u8Int_Prio;

    if (state)  /* open */
    {
        /* Counter Frequency Fixed at maxfreq */
        timer->freq = timer->info->maxfreq;

        /* Enable TIMERA clock */
        FCG_Fcg2PeriphClockCmd(tmr_device->clock, ENABLE);

        /* TIMERA configuration */
        (void)TMRA_StructInit(&stcTmraInit);
        stcTmraInit.sw_count.u8ClockDiv = TMRA_CLK_DIV32;
        stcTmraInit.u32PeriodValue      = timer->info->maxcnt;
        (void)TMRA_Init(tmr_device->tmr_handle, &stcTmraInit);

        TMRA_IntCmd(tmr_device->tmr_handle, TMRA_INT_OVF, ENABLE);
#if defined (HC32F460) || defined (HC32F4A0)
        hc32_install_irq_handler(&irq_config, tmr_device->isr.irq_callback, RT_TRUE);
#elif defined (HC32F448)
        hc32_install_independ_irq_handler(&irq_config, RT_TRUE);
#endif
    }
    else    /* close */
    {
        TMRA_DeInit(tmr_device->tmr_handle);
#if defined (HC32F460) || defined (HC32F4A0)
        hc32_install_irq_handler(&irq_config, tmr_device->isr.irq_callback, RT_FALSE);
#elif defined (HC32F448)
        hc32_install_independ_irq_handler(&irq_config, RT_FALSE);
#endif
        FCG_Fcg2PeriphClockCmd(tmr_device->clock, DISABLE);
    }
}

static rt_err_t _timer_start(rt_hwtimer_t *timer, rt_uint32_t t, rt_hwtimer_mode_t opmode)
{
    rt_err_t result = RT_EOK;
    struct hc32_hwtimer *tmr_device = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tmr_device = (struct hc32_hwtimer *)timer;

    /* set timer arr */
    TMRA_SetPeriodValue(tmr_device->tmr_handle, t - 1U);
    /* start timer */
    TMRA_Start(tmr_device->tmr_handle);

    return result;
}

static void _timer_stop(rt_hwtimer_t *timer)
{
    struct hc32_hwtimer *tmr_device = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tmr_device = (struct hc32_hwtimer *)timer;

    /* stop timer */
    TMRA_Stop(tmr_device->tmr_handle);
    /* reset timer cnt */
    TMRA_SetCountValue(tmr_device->tmr_handle, 0U);
}

static rt_err_t _timer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    rt_err_t result = -RT_ERROR;
    uint32_t freq = *(uint32_t *)arg;

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(arg != RT_NULL);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        if (freq != timer->freq)
        {
            LOG_W("Not Support To Set The Counter Frequency! Default is %d Hz", timer->freq);
            result = -RT_EINVAL;
        }
        else
        {
            result = RT_EOK;
        }
    }
    break;
    default:
    {
        result = -RT_EINVAL;
    }
    break;
    }

    return result;
}

static rt_uint32_t _timer_counter_get(rt_hwtimer_t *timer)
{
    struct hc32_hwtimer *tmr_device = RT_NULL;
    rt_uint32_t Counter;

    RT_ASSERT(timer != RT_NULL);

    tmr_device = (struct hc32_hwtimer *)timer;

    Counter = TMRA_GetCountValue(tmr_device->tmr_handle);

    return Counter;
}

#ifdef BSP_USING_TMRA_1
static void TMRA_1_callback(void)
{
    TMRA_ClearStatus(hc32_hwtimer_obj[TMRA_1_INDEX].tmr_handle, hc32_hwtimer_obj[TMRA_1_INDEX].flag);
    rt_device_hwtimer_isr(&hc32_hwtimer_obj[TMRA_1_INDEX].time_device);
}

#if defined (HC32F448)
void TMRA_1_Ovf_Udf_Handler(void)
{
    TMRA_1_callback();
}
#endif /* HC32F448 */
#endif /* BSP_USING_TMRA_1 */

#ifdef BSP_USING_TMRA_2
static void TMRA_2_callback(void)
{
    TMRA_ClearStatus(hc32_hwtimer_obj[TMRA_2_INDEX].tmr_handle, hc32_hwtimer_obj[TMRA_2_INDEX].flag);
    rt_device_hwtimer_isr(&hc32_hwtimer_obj[TMRA_2_INDEX].time_device);
}

#if defined (HC32F448)
void TMRA_2_Ovf_Udf_Handler(void)
{
    TMRA_2_callback();
}
#endif /* HC32F448 */
#endif /* BSP_USING_TMRA_2 */

#ifdef BSP_USING_TMRA_3
static void TMRA_3_callback(void)
{
    TMRA_ClearStatus(hc32_hwtimer_obj[TMRA_3_INDEX].tmr_handle, hc32_hwtimer_obj[TMRA_3_INDEX].flag);
    rt_device_hwtimer_isr(&hc32_hwtimer_obj[TMRA_3_INDEX].time_device);
}

#if defined (HC32F448)
void TMRA_3_Ovf_Udf_Handler(void)
{
    TMRA_3_callback();
}
#endif /* HC32F448 */
#endif /* BSP_USING_TMRA_3 */

#ifdef BSP_USING_TMRA_4
static void TMRA_4_callback(void)
{
    TMRA_ClearStatus(hc32_hwtimer_obj[TMRA_4_INDEX].tmr_handle, hc32_hwtimer_obj[TMRA_4_INDEX].flag);
    rt_device_hwtimer_isr(&hc32_hwtimer_obj[TMRA_4_INDEX].time_device);
}

#if defined (HC32F448)
void TMRA_4_Ovf_Udf_Handler(void)
{
    TMRA_4_callback();
}
#endif /* HC32F448 */
#endif /* BSP_USING_TMRA_4 */

#ifdef BSP_USING_TMRA_5
static void TMRA_5_callback(void)
{
    TMRA_ClearStatus(hc32_hwtimer_obj[TMRA_5_INDEX].tmr_handle, hc32_hwtimer_obj[TMRA_5_INDEX].flag);
    rt_device_hwtimer_isr(&hc32_hwtimer_obj[TMRA_5_INDEX].time_device);
}

#if defined (HC32F448)
void TMRA_5_Ovf_Udf_Handler(void)
{
    TMRA_5_callback();
}
#endif /* HC32F448 */
#endif /* BSP_USING_TMRA_5 */

#ifdef BSP_USING_TMRA_6
static void TMRA_6_callback(void)
{
    TMRA_ClearStatus(hc32_hwtimer_obj[TMRA_6_INDEX].tmr_handle, hc32_hwtimer_obj[TMRA_6_INDEX].flag);
    rt_device_hwtimer_isr(&hc32_hwtimer_obj[TMRA_6_INDEX].time_device);
}
#endif /* BSP_USING_TMRA_6 */

#ifdef BSP_USING_TMRA_7
static void TMRA_7_callback(void)
{
    TMRA_ClearStatus(hc32_hwtimer_obj[TMRA_7_INDEX].tmr_handle, hc32_hwtimer_obj[TMRA_7_INDEX].flag);
    rt_device_hwtimer_isr(&hc32_hwtimer_obj[TMRA_7_INDEX].time_device);
}
#endif /* BSP_USING_TMRA_7 */

#ifdef BSP_USING_TMRA_8
static void TMRA_8_callback(void)
{
    TMRA_ClearStatus(hc32_hwtimer_obj[TMRA_8_INDEX].tmr_handle, hc32_hwtimer_obj[TMRA_8_INDEX].flag);
    rt_device_hwtimer_isr(&hc32_hwtimer_obj[TMRA_8_INDEX].time_device);
}
#endif /* BSP_USING_TMRA_8 */

#ifdef BSP_USING_TMRA_9
static void TMRA_9_callback(void)
{
    TMRA_ClearStatus(hc32_hwtimer_obj[TMRA_9_INDEX].tmr_handle, hc32_hwtimer_obj[TMRA_9_INDEX].flag);
    rt_device_hwtimer_isr(&hc32_hwtimer_obj[TMRA_9_INDEX].time_device);
}
#endif /* BSP_USING_TMRA_9 */

#ifdef BSP_USING_TMRA_10
static void TMRA_10_callback(void)
{
    TMRA_ClearStatus(hc32_hwtimer_obj[TMRA_10_INDEX].tmr_handle, hc32_hwtimer_obj[TMRA_10_INDEX].flag);
    rt_device_hwtimer_isr(&hc32_hwtimer_obj[TMRA_10_INDEX].time_device);
}
#endif /* BSP_USING_TMRA_10 */

#ifdef BSP_USING_TMRA_11
static void TMRA_11_callback(void)
{
    TMRA_ClearStatus(hc32_hwtimer_obj[TMRA_11_INDEX].tmr_handle, hc32_hwtimer_obj[TMRA_11_INDEX].flag);
    rt_device_hwtimer_isr(&hc32_hwtimer_obj[TMRA_11_INDEX].time_device);
}
#endif /* BSP_USING_TMRA_11 */

#ifdef BSP_USING_TMRA_12
static void TMRA_12_callback(void)
{
    TMRA_ClearStatus(hc32_hwtimer_obj[TMRA_12_INDEX].tmr_handle, hc32_hwtimer_obj[TMRA_12_INDEX].flag);
    rt_device_hwtimer_isr(&hc32_hwtimer_obj[TMRA_12_INDEX].time_device);
}
#endif /* BSP_USING_TMRA_12 */

static struct rt_hwtimer_info _info[sizeof(hc32_hwtimer_obj) / sizeof(hc32_hwtimer_obj[0])];

void tmra_get_info_callback(void)
{
    /* Div = 32 */
    for (rt_uint8_t i = 0; i < sizeof(_info) / sizeof(_info[0]); i++)
    {
        _info[i].maxcnt  = CLK_GetBusClockFreq(hc32_hwtimer_obj[i].clock_source) / 32U / 1000U; /* Period = 1ms */
        _info[i].maxfreq = CLK_GetBusClockFreq(hc32_hwtimer_obj[i].clock_source) / 32U;
        _info[i].minfreq = CLK_GetBusClockFreq(hc32_hwtimer_obj[i].clock_source) / 32U / _info[i].maxcnt;
        _info[i].cntmode = HWTIMER_CNTMODE_UP;
    }

#ifdef BSP_USING_TMRA_1
    hc32_hwtimer_obj[TMRA_1_INDEX].isr.irq_callback = TMRA_1_callback;
#endif
#ifdef BSP_USING_TMRA_2
    hc32_hwtimer_obj[TMRA_2_INDEX].isr.irq_callback = TMRA_2_callback;
#endif
#ifdef BSP_USING_TMRA_3
    hc32_hwtimer_obj[TMRA_3_INDEX].isr.irq_callback = TMRA_3_callback;
#endif
#ifdef BSP_USING_TMRA_4
    hc32_hwtimer_obj[TMRA_4_INDEX].isr.irq_callback = TMRA_4_callback;
#endif
#ifdef BSP_USING_TMRA_5
    hc32_hwtimer_obj[TMRA_5_INDEX].isr.irq_callback = TMRA_5_callback;
#endif
#ifdef BSP_USING_TMRA_6
    hc32_hwtimer_obj[TMRA_6_INDEX].isr.irq_callback = TMRA_6_callback;
#endif
#ifdef BSP_USING_TMRA_7
    hc32_hwtimer_obj[TMRA_7_INDEX].isr.irq_callback = TMRA_7_callback;
#endif
#ifdef BSP_USING_TMRA_8
    hc32_hwtimer_obj[TMRA_8_INDEX].isr.irq_callback = TMRA_8_callback;
#endif
#ifdef BSP_USING_TMRA_9
    hc32_hwtimer_obj[TMRA_9_INDEX].isr.irq_callback = TMRA_9_callback;
#endif
#ifdef BSP_USING_TMRA_10
    hc32_hwtimer_obj[TMRA_10_INDEX].isr.irq_callback = TMRA_10_callback;
#endif
#ifdef BSP_USING_TMRA_11
    hc32_hwtimer_obj[TMRA_11_INDEX].isr.irq_callback = TMRA_11_callback;
#endif
#ifdef BSP_USING_TMRA_12
    hc32_hwtimer_obj[TMRA_12_INDEX].isr.irq_callback = TMRA_12_callback;
#endif
}

static const struct rt_hwtimer_ops _ops =
{
    .init = _timer_init,
    .start = _timer_start,
    .stop = _timer_stop,
    .count_get = _timer_counter_get,
    .control = _timer_ctrl,
};

static int rt_hw_hwtimer_init(void)
{
    int i;
    int result = RT_EOK;

    tmra_get_info_callback();
    for (i = 0; i < sizeof(hc32_hwtimer_obj) / sizeof(hc32_hwtimer_obj[0]); i++)
    {
        hc32_hwtimer_obj[i].time_device.info = &_info[i];
        hc32_hwtimer_obj[i].time_device.ops  = &_ops;
        if (rt_device_hwtimer_register(&hc32_hwtimer_obj[i].time_device,
                                       hc32_hwtimer_obj[i].name, &hc32_hwtimer_obj[i].tmr_handle) == RT_EOK)
        {
            LOG_D("%s register success", hc32_hwtimer_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", hc32_hwtimer_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_hwtimer_init);

#endif /* BSP_USING_HWTIMER */
