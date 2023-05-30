/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 */

#ifndef AT91_SHDWC_H
#define AT91_SHDWC_H

#ifdef __cplusplus
extern "C" {
#endif

#define AT91_SHDW_CR        (AT91_SHDWC + 0x00) /* Shut Down Control Register */
#define     AT91_SHDW_SHDW      (1    << 0)     /* Shut Down command */
#define     AT91_SHDW_KEY       (0xa5 << 24)        /* KEY Password */

#define AT91_SHDW_MR        (AT91_SHDWC + 0x04) /* Shut Down Mode Register */
#define     AT91_SHDW_WKMODE0   (3 << 0)        /* Wake-up 0 Mode Selection */
#define         AT91_SHDW_WKMODE0_NONE      0
#define         AT91_SHDW_WKMODE0_HIGH      1
#define         AT91_SHDW_WKMODE0_LOW       2
#define         AT91_SHDW_WKMODE0_ANYLEVEL  3
#define     AT91_SHDW_CPTWK0    (0xf << 4)      /* Counter On Wake Up 0 */
#define         AT91_SHDW_CPTWK0_(x)    ((x) << 4)
#define     AT91_SHDW_RTTWKEN   (1   << 16)     /* Real Time Timer Wake-up Enable */

#define AT91_SHDW_SR        (AT91_SHDWC + 0x08) /* Shut Down Status Register */
#define     AT91_SHDW_WAKEUP0   (1 <<  0)       /* Wake-up 0 Status */
#define     AT91_SHDW_RTTWK     (1 << 16)       /* Real-time Timer Wake-up */
#define     AT91_SHDW_RTCWK     (1 << 17)       /* Real-time Clock Wake-up [SAM9RL] */

#ifdef __cplusplus
}
#endif

#endif

