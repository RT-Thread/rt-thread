/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2020-04-08     Sunwancn        first version
 */

#ifndef  __DRV_PMHW_H__
#define  __DRV_PMHW_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(LPTIM1) && !defined(RT_PM_TIM_USING_RTC_ALARM)
  #define RT_PM_TIM_USING_LPTIM
#elif defined(SOC_SERIES_STM32F1)
  #define RT_PM_TIM_USING_RTC_ALARM_F1
  #define RT_PM_TIM_USING_RTC_ALARM
#elif (defined(RT_PM_TIM_USING_RTC_ALARM) || !defined(RTC_CR_WUTIE)) && defined(RTC_SSR_SS)
  #define RT_PM_TIM_USING_RTC_ALARM_SSR
  #ifndef RT_PM_TIM_USING_RTC_ALARM
    #define RT_PM_TIM_USING_RTC_ALARM
  #endif
#elif defined(RTC_SSR_SS)
  #define RT_PM_TIM_USING_RTC_WAKEUPTIM
  #define RT_PM_TIM_USING_RTC_WAKEUPTIM_SSR
#elif defined(RT_PM_USING_INTERNAL_WAKEUP)
  #define RT_PM_TIM_USING_RTC_WAKEUPTIM
  #define RT_PM_TIM_USING_RTC_WAKEUPTIM_NOREAD
#else
  #define RT_PM_TIM_USING_RTC_WAKEUPTIM
  #define RT_PM_TIM_USING_RTC_WAKEUPTIM_NOSSR
#endif

extern rt_uint32_t pm_hwtim_get_countfreq(void);
extern rt_uint32_t pm_hwtim_get_tick_max(void);
extern rt_uint32_t pm_hwtim_get_current_tick(void);
extern rt_err_t pm_hwtim_start(rt_uint32_t load);
extern void pm_hwtim_stop(void);

extern void pm_hw_sleep(struct rt_pm *pm, rt_uint8_t mode);
extern void pm_hw_run(struct rt_pm *pm, rt_uint8_t mode);

extern void pm_system_clock_high(void);
extern void pm_system_clock_normal(void);
extern void pm_system_clock_medium(void);
extern void pm_system_clock_low(void);
extern rt_uint16_t pm_run_freq[PM_RUN_MODE_MAX][2];

#ifdef __cplusplus
}
#endif

#endif /* __DRV_PMHW_H__ */
