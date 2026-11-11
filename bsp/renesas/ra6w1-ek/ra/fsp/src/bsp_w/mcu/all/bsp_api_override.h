/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_API_OVERRIDE_H
#define BSP_API_OVERRIDE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#include "./bsp_exceptions.h"

/* BSP Common Includes. */
#include "./bsp_common.h"

#if BSP_MCU_GROUP_RA6B1
 #include "../ra6b1/bsp_tcs.h"
#elif BSP_MCU_GROUP_RA6U1
 #include "../ra6u1/bsp_tcs.h"
#elif BSP_MCU_GROUP_RA6W1
 #include "../ra6w1/bsp_tcs.h"
#endif


/* BSP MCU Specific Includes. */
#include "./bsp_irq.h"
#include "./bsp_io.h"
#include "./bsp_group_irq.h"
#include "./bsp_clocks.h"
#include "./bsp_module_stop.h"
#include "./bsp_security.h"

/* Factory MCU information. */
#include "../../../../inc/fsp_features.h"

/* BSP Common Includes (Other than bsp_common.h) */
#include "./bsp_delay.h"
#include "./bsp_mcu_api.h"

#if __has_include("./internal/bsp_internal.h")
 #include "./internal/bsp_internal.h"
#endif

#endif
