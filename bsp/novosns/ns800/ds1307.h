/**
 * @file    ds1307.h
 * @brief   DS1307 RTC driver header
 *
 * Hardware: DS1307 RTC module, I2C address 0x68
 * Interface kept as ds1307_* for compatibility with drv_rtc.c
 */

#ifndef __DS1307_H__
#define __DS1307_H__

#include <rtthread.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

rt_err_t ds1307_init(void);
rt_err_t ds1307_get_time(struct tm *time);
rt_err_t ds1307_set_time(struct tm *time);

#ifdef __cplusplus
}
#endif

#endif /* __DS1307_H__ */
