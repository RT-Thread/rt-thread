/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SDIO_CONFIG_H__
#define __SDIO_CONFIG_H__

#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BSP_SDIO_CLK_PIN
#define BSP_SDIO_CLK_PIN       "PD6"
#endif
#ifndef BSP_SDIO_CLK_AFIO
#define BSP_SDIO_CLK_AFIO      "AF11"
#endif

#ifndef BSP_SDIO_CMD_PIN
#define BSP_SDIO_CMD_PIN       "PD7"
#endif
#ifndef BSP_SDIO_CMD_AFIO
#define BSP_SDIO_CMD_AFIO      "AF11"
#endif

#ifndef BSP_SDIO_D0_PIN
#define BSP_SDIO_D0_PIN        "PF4"
#endif
#ifndef BSP_SDIO_D0_AFIO
#define BSP_SDIO_D0_AFIO       "AF10"
#endif

#ifndef BSP_SDIO_D1_PIN
#define BSP_SDIO_D1_PIN        "PG10"
#endif
#ifndef BSP_SDIO_D1_AFIO
#define BSP_SDIO_D1_AFIO       "AF11"
#endif

#ifndef BSP_SDIO_D2_PIN
#define BSP_SDIO_D2_PIN        "PG11"
#endif
#ifndef BSP_SDIO_D2_AFIO
#define BSP_SDIO_D2_AFIO       "AF10"
#endif

#ifndef BSP_SDIO_D3_PIN
#define BSP_SDIO_D3_PIN        "PG12"
#endif
#ifndef BSP_SDIO_D3_AFIO
#define BSP_SDIO_D3_AFIO       "AF10"
#endif

#ifdef BSP_SDIO_USING_CARD_DETECT
#ifndef BSP_SDIO_CD_PIN
#define BSP_SDIO_CD_PIN        "PE10"
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* __SDIO_CONFIG_H__ */
