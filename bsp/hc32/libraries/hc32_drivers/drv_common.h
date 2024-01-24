/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-21     CDT          first version
 */

#ifndef __DRV_COMMON_H__
#define __DRV_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

void _Error_Handler(char *s, int num);

#ifndef Error_Handler
#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#endif
void  SysTick_Configuration(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_COMMON_H__ */
