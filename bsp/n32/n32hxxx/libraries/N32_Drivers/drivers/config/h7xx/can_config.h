/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-22     lin.qi       first version
 */

#ifndef __CAN_CONFIG_H__
#define __CAN_CONFIG_H__

#include <rtthread.h>
#include "n32h7xx_fdcan.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *\*\name   n32_fdcan_config.
 *\*\brief  FDCAN instance configuration structure.
 *\*\note   Clock and GPIO initialization are handled by CubeMX-generated code
 *\*\       in n32h7xx_cfg.c (from Cube.ntfx). NVIC interrupt vector numbers
 *\*\       are hardcoded in drv_fdcan.c per instance.
 */
struct n32_fdcan_config
{
    const char   *name;                   /**< device name */
    FDCAN_Module *Instance;             /**< FDCAN peripheral base address */
};

/*
 * Hardware connection pairs on N32H760ZIL7-STB:
 *   FDCAN1 <-> FDCAN2
 *   FDCAN3 <-> FDCAN4
 *   FDCAN5 <-> FDCAN6
 *   FDCAN7 <-> FDCAN8
 */

#if defined(BSP_USING_FDCAN1)
#ifndef FDCAN1_CONFIG
#define FDCAN1_CONFIG         \
    {                         \
        .name     = "fdcan1", \
        .Instance = FDCAN1,   \
    }
#endif
#endif /* BSP_USING_FDCAN1 */

#if defined(BSP_USING_FDCAN2)
#ifndef FDCAN2_CONFIG
#define FDCAN2_CONFIG         \
    {                         \
        .name     = "fdcan2", \
        .Instance = FDCAN2,   \
    }
#endif
#endif /* BSP_USING_FDCAN2 */

#if defined(BSP_USING_FDCAN3)
#ifndef FDCAN3_CONFIG
#define FDCAN3_CONFIG         \
    {                         \
        .name     = "fdcan3", \
        .Instance = FDCAN3,   \
    }
#endif
#endif /* BSP_USING_FDCAN3 */

#if defined(BSP_USING_FDCAN4)
#ifndef FDCAN4_CONFIG
#define FDCAN4_CONFIG         \
    {                         \
        .name     = "fdcan4", \
        .Instance = FDCAN4,   \
    }
#endif
#endif /* BSP_USING_FDCAN4 */

#if defined(BSP_USING_FDCAN5)
#ifndef FDCAN5_CONFIG
#define FDCAN5_CONFIG         \
    {                         \
        .name     = "fdcan5", \
        .Instance = FDCAN5,   \
    }
#endif
#endif /* BSP_USING_FDCAN5 */

#if defined(BSP_USING_FDCAN6)
#ifndef FDCAN6_CONFIG
#define FDCAN6_CONFIG         \
    {                         \
        .name     = "fdcan6", \
        .Instance = FDCAN6,   \
    }
#endif
#endif /* BSP_USING_FDCAN6 */

#if defined(BSP_USING_FDCAN7)
#ifndef FDCAN7_CONFIG
#define FDCAN7_CONFIG         \
    {                         \
        .name     = "fdcan7", \
        .Instance = FDCAN7,   \
    }
#endif
#endif /* BSP_USING_FDCAN7 */

#if defined(BSP_USING_FDCAN8)
#ifndef FDCAN8_CONFIG
#define FDCAN8_CONFIG         \
    {                         \
        .name     = "fdcan8", \
        .Instance = FDCAN8,   \
    }
#endif
#endif /* BSP_USING_FDCAN8 */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_CONFIG_H__ */
