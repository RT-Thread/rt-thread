/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-01-01     Urey      first version
 */
#ifndef _BOARD_CORETIMER_H_
#define _BOARD_CORETIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define CK_TIMER_BASE     (0xE000E000)

#define CORET_CSR         (volatile unsigned int *)(CK_TIMER_BASE + 0x10)
#define CORET_RVR         (volatile unsigned int *)(CK_TIMER_BASE + 0x14)
#define CORET_CVR         (volatile unsigned int *)(CK_TIMER_BASE + 0x18)
#define CORET_CALIB       (volatile unsigned int *)(CK_TIMER_BASE + 0x1c)

/*
 *  define the bits for TxControl
 */
#define CORETIM_TXCONTROL_ENABLE      (1UL << 0)
#define CORETIM_TXCONTROL_INTMASK     (1UL << 1)
#define CORETIM_TXCONTROL_MODE        (1UL << 16)


#ifdef __cplusplus
}
#endif

#endif /* _BOARD_CORETIMER_H_ */
