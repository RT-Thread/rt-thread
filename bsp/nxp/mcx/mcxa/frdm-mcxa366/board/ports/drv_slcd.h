/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 * Copyright 2024-2025 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * FRDM-MCXA366 onboard segment LCD helper (wraps NXP fsl_slcd).
 * Digit layout (left -> right): digit6 digit5 digit4 digit3 digit2 digit1
 * Points: P1/P2/P3 (upper) and P4/P5/P6 (lower).
 */

#ifndef __DRV_SLCD_H__
#define __DRV_SLCD_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SLCD_P1 0x01u
#define SLCD_P2 0x02u
#define SLCD_P3 0x04u
#define SLCD_P4 0x08u
#define SLCD_P5 0x10u
#define SLCD_P6 0x20u

/* Colon between digit5 and digit4 (HH:MM / MM:SS). */
#define SLCD_COLON (SLCD_P1 | SLCD_P4)
/* Decimal point between digit3 and digit2. */
#define SLCD_DOT (SLCD_P6)

int rt_hw_slcd_init(void);
void rt_hw_slcd_clear(void);
void rt_hw_slcd_display_all(void);
void rt_hw_slcd_display_num(uint8_t digit, uint8_t num);
void rt_hw_slcd_display_string(const char *str);
void rt_hw_slcd_display_point(uint8_t point);
/* Show HH:MM, e.g. rt_hw_slcd_display_time(12, 30) -> 12:30 */
void rt_hw_slcd_display_time(uint8_t hour, uint8_t minute);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_SLCD_H__ */
