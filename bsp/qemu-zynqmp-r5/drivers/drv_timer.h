/*
 * Copyright (c) 2023, lepustse@gmail.com
 *
 * License-Identifier: MIT
 *
 * Change Logs:
 * Date         Author		Notes
 * 2023-05-03   lepustse	the first version
 */

#ifndef __DRV_TIMER_H__
#define __DRV_TIMER_H__

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TTC_CLK_CNTRL(hw_base)      __REG32(hw_base + 0x00)
#define TTC_CLK_CNTRL_PS_VAL_MASK   0x0000001E      /**< Prescale value */
#define TTC_CLK_CNTRL_PS_EN         (1 << 0)      /**< Prescale enable */

#define TTC_CNT_CNTRL(hw_base)      __REG32(hw_base + 0x0C)
#define TTC_CNT_CNTRL_RESET_VALUE   0x00000021      /**< Reset value */
#define TTC_CNT_CNTRL_DIS           (1 << 0)      /**< Disable the counter */
#define TTC_CNT_CNTRL_INT           (1 << 1)      /**< interval mode */
#define TTC_CNT_CNTRL_DECR          (1 << 2)      /**< Decrement mode */
#define TTC_CNT_CNTRL_RST           (1 << 4)      /**< Reset counter */

#define TTC_COUNT_VALUE(hw_base)    __REG32(hw_base + 0x18)
#define TTC_INTERVAL_VAL(hw_base)   __REG32(hw_base + 0x24)
#define TTC_MATCH_0(hw_base)        __REG32(hw_base + 0x30)
#define TTC_MATCH_1(hw_base)        __REG32(hw_base + 0x3C)
#define TTC_MATCH_2(hw_base)        __REG32(hw_base + 0x48)

#define TTC_ISR(hw_base)            __REG32(hw_base + 0x54)
#define TTC_IXR_INTERVAL            (1 << 0)      /**< interval Interrupt */

#define TTC_IER(hw_base)            __REG32(hw_base + 0x60)

#ifdef __cplusplus
}
#endif

#endif
