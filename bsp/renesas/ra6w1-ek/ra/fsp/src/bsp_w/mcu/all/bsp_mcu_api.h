/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_MCU_API_H
#define BSP_MCU_API_H

#include "bsp_pd.h"
#include "bsp_pd_ctrl.h"
#include "bsp_device_info.h"
#include "bsp_linker_info.h"
#include "bsp_assert.h"

#if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1
 #include "bsp_rsip.h"
#endif

#include "bsp_freeze.h"
#if BSP_MCU_GROUP_RA6W1
 #include "bsp_otp.h"
 #include "../ra6w1/bsp_io_isolation.h"
#endif

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

fsp_err_t R_BSP_GroupIrqWrite(bsp_grp_irq_t irq, void (* p_callback)(bsp_grp_irq_t irq));
fsp_err_t R_BSP_GroupNmiWrite(void (* p_callback)(const uint32_t * p_exception_args));

BSP_PLACE_CODE_IN_RAM void R_BSP_SoftwareDelay(uint32_t delay, bsp_delay_units_t units);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
