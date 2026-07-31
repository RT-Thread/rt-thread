/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_PD_H
#define BSP_PD_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#if BSP_MCU_GROUP_RA6B1
 #include "../ra6b1/bsp_pd.h"
#elif BSP_MCU_GROUP_RA6U1
 #include "../ra6u1/bsp_pd.h"
#elif BSP_MCU_GROUP_RA6B2
 #include "../ra6b2/bsp_pd.h"
#elif BSP_MCU_GROUP_RA6W1
 #include "../ra6w1/bsp_pd.h"
#elif BSP_MCU_GROUP_RA6W3
 #include "../ra6w3/bsp_pd.h"
#endif

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

void bsp_pd_init(void);

BSP_PLACE_CODE_IN_RAM void bsp_pd_use(uint32_t pd_id);

BSP_PLACE_CODE_IN_RAM void bsp_pd_unuse(uint32_t pd_id);

BSP_PLACE_CODE_IN_RAM bool bsp_pd_used_check(uint32_t pd_id);

bool bsp_pd_is_up_check(uint32_t pd_id);

BSP_PLACE_CODE_IN_RAM void bsp_pd_enable(uint32_t pd_id);

BSP_PLACE_CODE_IN_RAM void bsp_pd_disable(uint32_t pd_id);

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
