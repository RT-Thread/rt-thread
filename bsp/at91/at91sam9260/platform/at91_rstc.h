/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 */

#ifndef AT91_RSTC_H
#define AT91_RSTC_H

#ifdef __cplusplus
extern "C" {
#endif

#define AT91_RSTC_CR        (AT91_RSTC + 0x00)  /* Reset Controller Control Register */
#define     AT91_RSTC_PROCRST   (1 << 0)        /* Processor Reset */
#define     AT91_RSTC_PERRST    (1 << 2)        /* Peripheral Reset */
#define     AT91_RSTC_EXTRST    (1 << 3)        /* External Reset */
#define     AT91_RSTC_KEY       (0xa5 << 24)        /* KEY Password */

#define AT91_RSTC_SR        (AT91_RSTC + 0x04)  /* Reset Controller Status Register */
#define     AT91_RSTC_URSTS     (1 << 0)        /* User Reset Status */
#define     AT91_RSTC_RSTTYP    (7 << 8)        /* Reset Type */
#define         AT91_RSTC_RSTTYP_GENERAL    (0 << 8)
#define         AT91_RSTC_RSTTYP_WAKEUP     (1 << 8)
#define         AT91_RSTC_RSTTYP_WATCHDOG   (2 << 8)
#define         AT91_RSTC_RSTTYP_SOFTWARE   (3 << 8)
#define         AT91_RSTC_RSTTYP_USER   (4 << 8)
#define     AT91_RSTC_NRSTL     (1 << 16)       /* NRST Pin Level */
#define     AT91_RSTC_SRCMP     (1 << 17)       /* Software Reset Command in Progress */

#define AT91_RSTC_MR        (AT91_RSTC + 0x08)  /* Reset Controller Mode Register */
#define     AT91_RSTC_URSTEN    (1 << 0)        /* User Reset Enable */
#define     AT91_RSTC_URSTIEN   (1 << 4)        /* User Reset Interrupt Enable */
#define     AT91_RSTC_ERSTL     (0xf << 8)      /* External Reset Length */

#ifdef __cplusplus
}
#endif

#endif

