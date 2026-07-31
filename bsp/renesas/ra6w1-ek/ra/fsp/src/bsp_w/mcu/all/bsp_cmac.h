/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_CMAC_H
#define BSP_CMAC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define CMAC2SYS_IRQn     ((IRQn_Type) 59)
#define TCM_SHARED_MEM    (0x33200000U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef struct st_cmac_callback_args_t
{
    void const * data;                 ///< Placeholder for user data.
    uint32_t     err_code;             ///< CMAC error code returned.
} cmac_callback_args_t;

typedef void (* p_callback)(cmac_callback_args_t * cb_data);

typedef struct st_cmac_irq_ctx
{
    IRQn_Type  irq;
    uint8_t    ipl;
    p_callback callback;
    void     * cb_data;
} cmac_irq_ctx_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

void bsp_cmac_start(void);
void bsp_cmac_stop(void);
bool bsp_cmac_is_active(void);
void bsp_cmac_cmac2sys_enable(cmac_irq_ctx_t * const ctx);
void bsp_cmac_cmac2sys_disable(cmac_irq_ctx_t * const ctx);
void cmac2sys_isr(void);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
