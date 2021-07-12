/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 15:27:27
 * @Description:  This files is for generic timer functions
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FT_GENERIC_TIMER_H
#define FT_GENERIC_TIMER_H

#include "ft_types.h"

/* GenericTimer  */

#define ARMV7_GEN_TIMER_NAME "armv7GenTimer"
#define ARMV7_GEN_TIMER_MAX_COUNT 0x7fffffff
#define ARMV7_GEN_TIMER_DEFAULT_TPS 60
#define ARMV7_GEN_TIMER_DEFAULT_MIN_FREQ 10
#define ARMV7_GEN_TIMER_DEFAULT_MAX_FREQ 5000
#define ARMV7_GEN_TIMER_MAX_CLK_FREQ 50000000
#define ARMV7_GEN_TIMER_MIN_CLK_FREQ 1000000

#define GEN_TIMER_REG_CTL 0  //<! Control register for the Hyp mode physical timer.
#define GEN_TIMER_REG_TVAL 1 //<! Holds the timer value for the Hyp mode physical timer.

#define GEN_TIMER_CTRL_ENABLE (1 << 0)
#define GEN_TIMER_CTRL_IMASK (1 << 1)
#define GEN_TIMER_CTRL_ISTATUS (1 << 2)

#define GEN_TIMER_SECURE_PHY_PPI (0)
#define GEN_TIMER_NON_SECURE_PHY_PPI (1)
#define GEN_TIMER_VIRTURE_PPI (2)
#define GEN_TIMER_HYP_PPI (3)
#define GEN_TIMER_MAX_PPI (4)

#define GEN_TIMER_VIRTUAL_IRQN 27 /**<  Virtual Timer Interrupt */
#define GEN_TIMER_VIRTUAL_NOSECURE_IRQN 28
#define GEN_TIMER_PHYSICAL_IRQn 29
#define GEN_TIMER_PHYSICAL_NOSECURE_IRQN 30 /**< Secure Physical Timer Interrupt */

typedef void (*Ft_GenericTimer_Isr_Callback)(void *args);

void Ft_GenericTimer_Init(FT_IN u8 UseVirtual, FT_IN Ft_GenericTimer_Isr_Callback Callback);
int32_t Ft_GenericTimer_IsrSet(FT_IN u32 HzRate, FT_IN u32 Cmd);
void Ft_GenericTimer_IrqHandler(void *param);
int32_t Ft_GenericTimer_UsDelay(FT_IN u32 DelayUs);
u32 Ft_GenericTimer_GetTick(void);
u32 Ft_GenericTimer_Msec(void);

#endif // !
