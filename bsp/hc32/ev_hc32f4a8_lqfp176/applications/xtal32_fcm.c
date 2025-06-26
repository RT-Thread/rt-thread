/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-10-27     CDT          first version
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#if defined(BSP_RTC_USING_XTAL32) || defined(RT_USING_PM)

#define XTAL32_FCM_THREAD_STACK_SIZE    (1024)

/**
 * @brief This thread is used to monitor whether XTAL32 is stable.
 *        This thread only runs once after the system starts.
 *        When stability is detected or 2s times out, the thread will end.
 *       (When a timeout occurs it will be prompted via rt_kprintf)
 */
void xtal32_fcm_thread_entry(void *parameter)
{
    stc_fcm_init_t stcFcmInit;
    uint32_t u32TimeOut = 0UL;
    uint32_t u32Time = 200UL; /* 200*10ms = 2s */

    /* FCM config */
    FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_FCM, ENABLE);
    (void)FCM_StructInit(&stcFcmInit);
    stcFcmInit.u32RefClock       = FCM_REF_CLK_MRC;
    stcFcmInit.u32RefClockDiv    = FCM_REF_CLK_DIV8192; /* ~1ms cycle */
    stcFcmInit.u32RefClockEdge   = FCM_REF_CLK_RISING;
    stcFcmInit.u32TargetClock    = FCM_TARGET_CLK_XTAL32;
    stcFcmInit.u32TargetClockDiv = FCM_TARGET_CLK_DIV1;
    stcFcmInit.u16LowerLimit     = (uint16_t)((XTAL32_VALUE / (MRC_VALUE / 8192U)) * 96UL / 100UL);
    stcFcmInit.u16UpperLimit     = (uint16_t)((XTAL32_VALUE / (MRC_VALUE / 8192U)) * 104UL / 100UL);
    (void)FCM_Init(&stcFcmInit);
    /* Enable FCM, to ensure xtal32 stable */
    FCM_Cmd(ENABLE);

    while (1)
    {
        if (SET == FCM_GetStatus(FCM_FLAG_END))
        {
            FCM_ClearStatus(FCM_FLAG_END);
            if ((SET == FCM_GetStatus(FCM_FLAG_ERR)) || (SET == FCM_GetStatus(FCM_FLAG_OVF)))
            {
                FCM_ClearStatus(FCM_FLAG_ERR | FCM_FLAG_OVF);
            }
            else
            {
                (void)FCM_DeInit();
                FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_FCM, DISABLE);
                /* XTAL32 stabled */
                break;
            }
        }
        u32TimeOut++;
        if (u32TimeOut > u32Time)
        {
            (void)FCM_DeInit();
            FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_FCM, DISABLE);
            rt_kprintf("Error: XTAL32 still unstable, timeout.\n");
            break;
        }
        rt_thread_mdelay(10);
    }
}

int xtal32_fcm_thread_create(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("xtal32_fcm", xtal32_fcm_thread_entry, RT_NULL,
                           XTAL32_FCM_THREAD_STACK_SIZE, RT_THREAD_PRIORITY_MAX - 2, 10);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        rt_kprintf("create xtal32_fcm thread err!");
    }
    return RT_EOK;
}
INIT_APP_EXPORT(xtal32_fcm_thread_create);

#endif


