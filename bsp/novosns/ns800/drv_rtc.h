/**
 * @file    drv_rtc.h
 * @brief   NS800RT7P65D RTC driver header file
 */

#ifndef __DRV_RTC_H__
#define __DRV_RTC_H__

#include <rtthread.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif


int rt_hw_rtc_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_RTC_H__ */
