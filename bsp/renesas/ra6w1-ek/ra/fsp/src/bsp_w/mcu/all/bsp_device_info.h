/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_DEVICE_INFO_H
#define BSP_DEVICE_INFO_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#if BSP_MCU_GROUP_RA6B1
 #include "../ra6b1/bsp_device_info.h"
#elif BSP_MCU_GROUP_RA6U1
 #include "../ra6u1/bsp_device_info.h"
#elif BSP_MCU_GROUP_RA6B2
 #include "../ra6b2/bsp_device_info.h"
#elif BSP_MCU_GROUP_RA6W1
 #include "../ra6w1/bsp_device_info.h"
#elif BSP_MCU_GROUP_RA6W3
 #include "../ra6w3/bsp_device_info.h"
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

/* The following functions are defined in the device-specific source files. */
bool     bsp_device_info_init(void);
bool     bsp_device_variant_detect(void);
bool     bsp_device_info_check(uint32_t mask, uint32_t attribute);
uint32_t bsp_device_info_get(void);
bool     bsp_device_info_compatibility_check(void);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* BSP_DEVICE_INFO_H */
