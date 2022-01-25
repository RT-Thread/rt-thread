/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32VG1_HAL_TIM_H__
#define AB32VG1_HAL_TIM_H__

#include "ab32vg1_hal_def.h"

enum
{
    TMRxCON,
    TMRxCPND,
    TMRxCNT,
    TMRxPR,
    TMRxCPT,
    TMRxDUTY0,
    TMRxDUTY1,
    TMRxDUTY2
};

#define TIM0_BASE   ((hal_sfr_t)&TMR0CON)
#define TIM1_BASE   ((hal_sfr_t)&TMR1CON)
#define TIM2_BASE   ((hal_sfr_t)&TMR2CON)
#define TIM3_BASE   ((hal_sfr_t)&TMR3CON)
#define TIM4_BASE   ((hal_sfr_t)&TMR4CON)
#define TIM5_BASE   ((hal_sfr_t)&TMR5CON)

#endif
