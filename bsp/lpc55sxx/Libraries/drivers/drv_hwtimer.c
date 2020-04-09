/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-04-17     WangBing     the first version.
 * 2019-04-22     tyustli      add imxrt series support
 * 2019-07-15     Magicoe      The first version for LPC55S6x
 *
*/
#include <rtthread.h>

#ifdef BSP_USING_HWTIMER

#define LOG_TAG             "drv.hwtimer"
#include <drv_log.h>

#include <rtdevice.h>
#include "drv_hwtimer.h"
#include "fsl_ctimer.h"


static void NVIC_Configuration(void)
{
#ifdef BSP_USING_CTIMER0
    EnableIRQ(CTIMER0_IRQn);
#endif

#ifdef BSP_USING_CTIMER1
    EnableIRQ(CTIMER1_IRQn);
#endif
    
#ifdef BSP_USING_CTIMER2
    EnableIRQ(CTIMER2_IRQn);
#endif
    
#ifdef BSP_USING_CTIMER3
    EnableIRQ(CTIMER3_IRQn);
#endif
    
#ifdef BSP_USING_CTIMER4
    EnableIRQ(CTIMER4_IRQn);
#endif
}

static rt_err_t lpc_ctimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    CTIMER_Type *hwtimer_dev;
    hwtimer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        uint32_t clk;
        uint32_t pre;
        if(hwtimer_dev == CTIMER0) clk = CLOCK_GetFreq(kCLOCK_CTimer0);
        if(hwtimer_dev == CTIMER1) clk = CLOCK_GetFreq(kCLOCK_CTimer1);
        if(hwtimer_dev == CTIMER2) clk = CLOCK_GetFreq(kCLOCK_CTimer2);
        if(hwtimer_dev == CTIMER3) clk = CLOCK_GetFreq(kCLOCK_CTimer3);
        if(hwtimer_dev == CTIMER4) clk = CLOCK_GetFreq(kCLOCK_CTimer4);
        
        pre = clk / *((uint32_t *)args) - 1;
        
        hwtimer_dev->PR = pre;
    }
    break;
    default:
        err = -RT_ENOSYS;
        break;
    }
    return err;
}

static rt_uint32_t lpc_ctimer_count_get(rt_hwtimer_t *timer)
{
    rt_uint32_t CurrentTimer_Count;
    CTIMER_Type *hwtimer_dev;
    hwtimer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    CurrentTimer_Count = hwtimer_dev->TC;

    return CurrentTimer_Count;
}

static void lpc_ctimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    CTIMER_Type *hwtimer_dev;
    ctimer_config_t cfg;
    hwtimer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);
    
    /* Use Main clock for some of the Ctimers */
    if(hwtimer_dev == CTIMER0) CLOCK_AttachClk(kMAIN_CLK_to_CTIMER0);
    if(hwtimer_dev == CTIMER1) CLOCK_AttachClk(kMAIN_CLK_to_CTIMER1);
    if(hwtimer_dev == CTIMER2) CLOCK_AttachClk(kMAIN_CLK_to_CTIMER2);
    if(hwtimer_dev == CTIMER3) CLOCK_AttachClk(kMAIN_CLK_to_CTIMER3);
    if(hwtimer_dev == CTIMER4) CLOCK_AttachClk(kMAIN_CLK_to_CTIMER4);
    
    CTIMER_Deinit(hwtimer_dev);
    
    if (state == 1)
    {
        NVIC_Configuration();
        CTIMER_GetDefaultConfig(&cfg);
        CTIMER_Init(hwtimer_dev, &cfg);
    }
}

static rt_err_t lpc_ctimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    CTIMER_Type *hwtimer_dev;
    hwtimer_dev = (CTIMER_Type *)timer->parent.user_data;
    /* Match Configuration for Channel 0 */
    ctimer_match_config_t matchCfg;
    
    RT_ASSERT(timer != RT_NULL);

    /* Configuration*/
    matchCfg.enableCounterReset = true;
    matchCfg.enableCounterStop  = (mode == HWTIMER_MODE_ONESHOT) ? true : false;;
    matchCfg.matchValue         = cnt;
    matchCfg.outControl         = kCTIMER_Output_NoAction;
    matchCfg.outPinInitState    = false;
    matchCfg.enableInterrupt    = true;
    
    CTIMER_SetupMatch(hwtimer_dev, kCTIMER_Match_1, &matchCfg);
    
    NVIC_Configuration();

    CTIMER_StartTimer(hwtimer_dev);
    
    return RT_EOK;
}

static void lpc_ctimer_stop(rt_hwtimer_t *timer)
{
    CTIMER_Type *hwtimer_dev;
    hwtimer_dev = (CTIMER_Type *)timer->parent.user_data;

    RT_ASSERT(timer != RT_NULL);

    CTIMER_StopTimer(hwtimer_dev);
}

static const struct rt_hwtimer_ops lpc_hwtimer_ops =
{
    .init  = lpc_ctimer_init,
    .start = lpc_ctimer_start,
    .stop  = lpc_ctimer_stop,
    .count_get = lpc_ctimer_count_get,
    .control = lpc_ctimer_control,
};

static const struct rt_hwtimer_info lpc_hwtimer_info =
{
    25000000,           /* the maximum count frequency can be set */
    6103,               /* the minimum count frequency can be set */
    0xFFFFFFFF,
    HWTIMER_CNTMODE_UP,
};

#ifdef BSP_USING_CTIMER0
static rt_hwtimer_t CTimer0;
#endif /* BSP_USING_HWTIMER0 */

#ifdef BSP_USING_CTIMER1
static rt_hwtimer_t CTimer1;
#endif /* BSP_USING_HWTIMER1 */

#ifdef BSP_USING_CTIMER2
static rt_hwtimer_t CTimer2;
#endif /* BSP_USING_HWTIMER2 */

#ifdef BSP_USING_CTIMER3
static rt_hwtimer_t CTimer3;
#endif /* BSP_USING_HWTIMER3 */

#ifdef BSP_USING_CTIMER4
static rt_hwtimer_t CTimer4;
#endif /* BSP_USING_HWTIMER4 */

int rt_hw_hwtimer_init(void)
{
    int ret = RT_EOK;

#ifdef BSP_USING_CTIMER0
    CTimer0.info = &lpc_hwtimer_info;
    CTimer0.ops  = &lpc_hwtimer_ops;
    ret = rt_device_hwtimer_register(&CTimer0, "ctimer0", CTIMER0);

    if (ret != RT_EOK)
    {
        LOG_E("CTIMER0 register failed\n");
    }
#endif

#ifdef BSP_USING_CTIMER1
    CTimer1.info = &lpc_hwtimer_info;
    CTimer1.ops  = &lpc_hwtimer_ops;
    ret = rt_device_hwtimer_register(&CTimer1, "ctimer1", CTIMER1);

    if (ret != RT_EOK)
    {
        LOG_E("CTIMER1 register failed\n");
    }
#endif
    
#ifdef BSP_USING_CTIMER2
    CTimer2.info = &lpc_hwtimer_info;
    CTimer2.ops  = &lpc_hwtimer_ops;
    ret = rt_device_hwtimer_register(&CTimer2, "ctimer2", CTIMER2);

    if (ret != RT_EOK)
    {
        LOG_E("CTIMER2 register failed\n");
    }
#endif
    
#ifdef BSP_USING_CTIMER3
    CTimer3.info = &lpc_hwtimer_info;
    CTimer3.ops  = &lpc_hwtimer_ops;
    ret = rt_device_hwtimer_register(&CTimer3, "ctimer3", CTIMER3);

    if (ret != RT_EOK)
    {
        LOG_E("CTIMER3 register failed\n");
    }
#endif
    
#ifdef BSP_USING_CTIMER4
    CTimer4.info = &lpc_hwtimer_info;
    CTimer4.ops  = &lpc_hwtimer_ops;
    ret = rt_device_hwtimer_register(&CTimer4, "ctimer4", CTIMER4);

    if (ret != RT_EOK)
    {
        LOG_E("CTIMER4 register failed\n");
    }
#endif
    
    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_hwtimer_init);

#ifdef BSP_USING_CTIMER0
void CTIMER0_IRQHandler(void)
{
    uint32_t int_stat;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(CTIMER0);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(CTIMER0, int_stat);
    rt_device_hwtimer_isr(&CTimer0);

}
#endif /* BSP_USING_HWTIMER0 */

#ifdef BSP_USING_CTIMER1
void CTIMER1_IRQHandler(void)
{
    uint32_t int_stat;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(CTIMER1);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(CTIMER1, int_stat);
    rt_device_hwtimer_isr(&CTimer1);

}
#endif /* BSP_USING_HWTIMER1 */

#ifdef BSP_USING_CTIMER2
void CTIMER2_IRQHandler(void)
{
    uint32_t int_stat;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(CTIMER2);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(CTIMER2, int_stat);
    rt_device_hwtimer_isr(&CTimer2);

}
#endif /* BSP_USING_HWTIMER2 */

#ifdef BSP_USING_CTIMER3
void CTIMER3_IRQHandler(void)
{
    uint32_t int_stat;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(CTIMER3);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(CTIMER3, int_stat);
    rt_device_hwtimer_isr(&CTimer3);

}
#endif /* BSP_USING_HWTIMER3 */

#ifdef BSP_USING_CTIMER4
void CTIMER4_IRQHandler(void)
{
    uint32_t int_stat;
    /* Get Interrupt status flags */
    int_stat = CTIMER_GetStatusFlags(CTIMER4);
    /* Clear the status flags that were set */
    CTIMER_ClearStatusFlags(CTIMER4, int_stat);
    rt_device_hwtimer_isr(&CTimer4);

}
#endif /* BSP_USING_HWTIMER4 */


#endif /* BSP_USING_HWTIMER */
