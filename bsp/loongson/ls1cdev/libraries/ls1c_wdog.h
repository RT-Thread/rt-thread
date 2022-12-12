/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-06     sundm75       first version
 */

#ifndef _LS1C_WDOG_H_
#define _LS1C_WDOG_H_

#ifdef __cplusplus
extern "C" {
#endif

unsigned int Wdog_Init(void);                   // 暂时为空
unsigned int Wdog_Enable(void);                 // 看门狗使能寄存器（WDT_EN）
unsigned int Wdog_Disable(void);                // 看门狗失能寄存器（WDT_EN）
unsigned int Wdog_Set(void);                    // 看门狗设置寄存器 (WDT_SET)
unsigned int Wdog_Reset(void);                  // 看门狗设置寄存器 (WDT_SET)
unsigned int Wdog_GetValue(void);               // 获得看门狗计数器（WDT_timer）
unsigned int Wdog_LoadValue(unsigned int cnt);  // 设置看门狗计数器（WDT_timer）
unsigned int Wdog_GetPreValue(void);            // 获得看门狗计数器设定值

#ifdef __cplusplus
}
#endif

#endif /* _LS1C_WDOG_H_ */

