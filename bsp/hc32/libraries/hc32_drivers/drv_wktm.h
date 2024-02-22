/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-09     CDT          first version
 */

#ifndef  __DRV_WKTM_H__
#define  __DRV_WKTM_H__

#include <rtthread.h>

rt_err_t hc32_wktm_start(rt_uint32_t reload);
void hc32_wktm_stop(void);

rt_uint32_t hc32_wktm_get_countfreq(void);
rt_uint32_t hc32_wktm_get_tick_max(void);
rt_uint32_t hc32_wktm_get_current_tick(void);

#endif /* __DRV_WKTM_H__ */
