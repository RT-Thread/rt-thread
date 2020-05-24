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

void stm32_sleep(struct rt_pm *pm, rt_uint8_t mode);
void stm32_run(struct rt_pm *pm, rt_uint8_t mode);

rt_uint32_t stm32_pmtim_get_countfreq(void);
rt_uint32_t stm32_pmtim_get_tick_max(void);
rt_uint32_t stm32_pmtim_get_current_tick(void);
rt_err_t stm32_pmtim_start(rt_uint32_t load);
void stm32_pmtim_stop(void);

void stm32_systemclock_high(void);
void stm32_systemclock_normal(void);
void stm32_systemclock_medium(void);
void stm32_systemclock_low(void);

extern rt_uint16_t stm32_run_freq[PM_RUN_MODE_MAX][2];

#ifdef __cplusplus
}
#endif

#endif /* __DRV_PMHW_H__ */
