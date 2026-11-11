/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @defgroup BSP_OSPI_B BSP OSPI_B support
 * @ingroup RENESAS_COMMON
 * @brief Code that initializes the OSPI_B device memory.
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

#if 0 != BSP_FEATURE_OSPI_B_IS_AVAILABLE

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief   Initializes OSPI_B.
 * @param   p_startup_fn         Function pointer to the method which starts the OSPI and transitions it to the
 *                               appropriate mode.
 * @param   init_from_sip_memory If true, this function will initialize internal memory regions sourced from SiP Flash.
 *
 * This function initializes an attached OSPI_B memory device.
 *
 * @note This function must only be called once after reset.
 **********************************************************************************************************************/
void R_BSP_OspiBInit (bsp_ospi_b_startup_fn_t p_startup_fn, bool init_from_sip_memory)
{
    /* Call the startup function to open the OSPI_B peripheral and put it into the correct mode. */
    if (FSP_SUCCESS != p_startup_fn())
    {
        /* If startup fails memory cannot be initialized so return. */
        return;
    }

    if (init_from_sip_memory)
    {
        /* Initialize internal memory regions sourced from SiP Flash. */
        for (uint32_t i = 0; i < g_init_info.copy_count; i++)
        {
            const bsp_init_copy_info_t * const p_copy = &g_init_info.p_copy_list[i];
            if ((INIT_MEM_SIP_FLASH == p_copy->type.source_type) && !p_copy->type.external)
            {
                memcpy(p_copy->p_base, p_copy->p_load, ((uint32_t) p_copy->p_limit - (uint32_t) p_copy->p_base));
            }
        }
    }
}

#endif

/** @} (end addtogroup BSP_OSPI_B) */
