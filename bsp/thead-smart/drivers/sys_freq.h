/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     sys_freq.h
 * @brief    header file for setting system frequency.
 * @version  V1.0
 * @date     18. July 2018
 ******************************************************************************/
#ifndef _SYS_FREQ_H_
#define _SYS_FREQ_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int32_t drv_get_i2s_freq(int32_t idx);
int32_t drv_get_pwm_freq(int32_t idx);
int32_t drv_get_usart_freq(int32_t idx);
int32_t drv_get_usi_freq(int32_t idx);
int32_t drv_get_sys_freq(void);
int32_t drv_get_apb_freq(void);
int32_t drv_get_rtc_freq(int32_t idx);
int32_t drv_get_timer_freq(int32_t idx);

int32_t drv_get_cpu_freq(int32_t idx);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_FREQ_H_ */

