/*******************************************************************************
*
* Copyright [2014-]2014 Freescale Semiconductor, Inc.

*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale License
* distributed with this Material.
* See the LICENSE file distributed for more details.
* 
*
*******************************************************************************/

#include "fsl_device_registers.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Table of base addresses for ENC instances. */
ENC_Type* const g_encBase[] = ENC_BASE_PTRS;

/* Table to save ENC IRQ enum numbers defined in CMSIS header file. */
const IRQn_Type g_encCmpIrqId[ENC_INSTANCE_COUNT] = {ENC_COMPARE_IRQn};
const IRQn_Type g_encHomeIrqId[ENC_INSTANCE_COUNT] = {ENC_HOME_IRQn};
const IRQn_Type g_encWdtIrqId[ENC_INSTANCE_COUNT] = {ENC_WDOG_SAB_IRQn};
const IRQn_Type g_encIndexIrqId[ENC_INSTANCE_COUNT] = {ENC_INDEX_IRQn};

/*******************************************************************************
 * EOF
 ******************************************************************************/
