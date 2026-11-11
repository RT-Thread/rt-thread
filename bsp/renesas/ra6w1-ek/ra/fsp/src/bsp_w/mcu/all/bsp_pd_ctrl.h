/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_PD_CTRL_H
#define BSP_PD_CTRL_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

#if BSP_MCU_GROUP_RA6B1
 #include "../ra6b1/bsp_pd_ctrl_ra6b1.h"
#elif BSP_MCU_GROUP_RA6U1
 #include "../ra6u1/bsp_pd_ctrl_ra6u1.h"
#elif BSP_MCU_GROUP_RA6W3
 #include "../ra6w3/bsp_pd_ctrl_ra6w3.h"
#endif

#if defined(BSP_MCU_GROUP_RA6B1) || defined(BSP_MCU_GROUP_RA6U1) || defined(BSP_MCU_GROUP_RA6W3)

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Used as an indication of an invalid index of the PDC look-up table. */
 #define BSP_PD_CTRL_INVALID_LUT_INDEX         (0xFFFF)

/** Used as an indication of an unused entry of the PDC look-up table. */
 #define BSP_PD_CTRL_UNUSED_LUT_ENTRY_VALUE    (0UL)

/*******************************************************************************************************************//**
 * Used when searching for entries in the PDC look-up table, to indicate that a particular
 * field will not be used to filter out potential candidates.
 **********************************************************************************************************************/
 #define BSP_PD_CTRL_FILTER_DONT_CARE          (0xFF)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Available wakeup source banks to be selected as a trigger in a PDC LUT entry.
 **********************************************************************************************************************/
typedef enum e_bsp_pd_ctrl_trig_select
{
    BSP_PD_CTRL_TRIG_SELECT_P0_GPIO    = 0x0, ///< Trigger from GPIO Port 0 through WAKEUP block */
    BSP_PD_CTRL_TRIG_SELECT_P1_GPIO    = 0x1, ///< Trigger from GPIO Port 1 through WAKEUP block */
    BSP_PD_CTRL_TRIG_SELECT_P2_GPIO    = 0x2, ///< Trigger from GPIO Port 2 through WAKEUP block */
    BSP_PD_CTRL_TRIG_SELECT_PERIPHERAL = 0x3, ///< Trigger from peripheral IRQ, table from device header files */
} bsp_pd_ctrl_trig_select_t;

/*******************************************************************************************************************//**
 * @brief Error codes specific to the PDC.
 **********************************************************************************************************************/
typedef enum e_bsp_pd_ctrl_error
{
    BSP_PD_CTRL_SUCCESS                 = 0x0,
    BSP_PD_CTRL_ERROR_INVALID_LUT_ENTRY = 0x1, ///< LUT entry contains an invalid master.
    BSP_PD_CTRL_ERROR_PDC_LUT_FULL      = 0x2, ///< All PDC LUT entries are occupied.
    BSP_PD_CTRL_ERROR_ENTRY_NOT_FOUND   = 0x3, ///< Entry is not present in the PDC LUT.
} bsp_pd_ctrl_error_t;

/*******************************************************************************************************************//**
 * @brief PDC look-up entry structure.
 **********************************************************************************************************************/
typedef struct st_bsp_pd_ctrl_entry
{
    bsp_pd_ctrl_trig_select_t trig_select; ///< Triggering types.
    uint8_t               trig_id;         ///< Trigger ID.
    bsp_pd_ctrl_options_t wakeup_options;  ///< Additional wakeup options.
    bsp_pd_ctrl_master_t  wakeup_master;   ///< Wakeup Master ID.
} bsp_pd_ctrl_entry_t;

/** @} (end addtogroup BSP_MCU) */

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

void                bsp_pd_ctrl_entry_read(uint32_t idx, uint32_t * p_value);
bsp_pd_ctrl_error_t bsp_pd_ctrl_entry_write(bsp_pd_ctrl_entry_t entry, uint32_t * p_idx);
bsp_pd_ctrl_error_t bsp_pd_ctrl_entry_find(bsp_pd_ctrl_entry_t entry, uint32_t start, uint32_t * p_idx);
void                bsp_pd_ctrl_entry_remove(uint32_t idx, uint32_t * p_value);
void                bsp_pd_ctrl_entry_reset(bsp_pd_ctrl_entry_t * p_keep, uint32_t keep_len, uint32_t * p_kept);
bsp_pd_ctrl_error_t bsp_pd_ctrl_pending_set(uint32_t idx);
void                bsp_pd_ctrl_pending_get(uint32_t * p_status);
void                bsp_pd_ctrl_acknowledge(uint32_t idx);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

#endif
