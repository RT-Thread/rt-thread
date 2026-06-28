/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-03     CoreBoxer    support IMXRT1180-EVK
 */

#ifndef __DRV_FLEXSPI_H__
#define __DRV_FLEXSPI_H__

#include <rtthread.h>
#include "fsl_flexspi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Put critical transfer code into ITCM (Code TCM) */
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define FLEXSPI_RAM_CODE  __attribute__((section("CodeQuickAccess"), noinline))
#elif defined(__GNUC__)
#define FLEXSPI_RAM_CODE  __attribute__((section("CodeQuickAccess"), noinline))
#elif defined(__ICCARM__)
#define FLEXSPI_RAM_CODE  __ramfunc
#else
#define FLEXSPI_RAM_CODE
#endif

typedef struct
{
    FLEXSPI_Type   *base;
    flexspi_port_t  port;
    uint32_t        ahb_base;
} imxrt_flexspi_handle_t;

/* Get initialized FlexSPI handle (FlexSPI1 or FlexSPI2 decided by BSP config) */
imxrt_flexspi_handle_t *imxrt_flexspi_get_handle(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_FLEXSPI_H__ */
