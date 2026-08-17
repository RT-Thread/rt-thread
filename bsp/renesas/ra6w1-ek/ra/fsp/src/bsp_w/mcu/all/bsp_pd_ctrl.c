/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#include "bsp_pd_ctrl.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define BSP_PRV_DMA_CTRL_REG_OFFSET               (8)
#define BSP_PRV_SENSE_REACT_TIMEOUT_ITERATIONS    (1000)

#if defined(BSP_MCU_GROUP_RA6B1) || defined(BSP_MCU_GROUP_RA6U1) || defined(BSP_MCU_GROUP_RA6W3)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static uint32_t bsp_pd_ctrl_prv_entry_translate(bsp_pd_ctrl_entry_t entry);
static bool     bsp_prv_pd_ctrl_entry_match(bsp_pd_ctrl_entry_t entry, uint8_t idx);
static void     bsp_pd_ctrl_prv_entry_reset(void);

/***********************************************************************************************************************
 * Exported global variables and functions (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Read value of a specific PDC LUT entry.
 *
 * @param[in]  idx     Index of the entry that is to be read. Valid range: 0 - (BSP_FEATURE_PD_CTRL_VALID_ENTRIES-1)
 * @param[out] p_value Pointer to value that was read from the PDC LUT at the given index.
 **********************************************************************************************************************/
void bsp_pd_ctrl_entry_read (uint32_t idx, uint32_t * p_value)
{
    *p_value = PDC->PDC_CTRL_REG[idx];
}

/*******************************************************************************************************************//**
 * @brief Add a PDC LUT entry dynamically. Scans all LUT entries until it finds an unused one. A LUT entry shall be
 *        considered unused if it equals BSP_PD_CTRL_UNUSED_LUT_ENTRY_VALUE.
 *
 * @param[in]  entry   Value to be written to the PDC look-up table entry.
 * @param[out] p_idx   Pointer to variable where index of entry written to the PDC LUT is stored.
 *
 * @retval  BSP_PD_CTRL_SUCCESS              Operation was successful and entry was written to the PDC LUT.
 * @retval  BSP_PD_CTRL_ERROR_PDC_LUT_FULL   All PDC LUT entries are used. New entry cannot be added.
 **********************************************************************************************************************/
bsp_pd_ctrl_error_t bsp_pd_ctrl_entry_write (bsp_pd_ctrl_entry_t entry, uint32_t * p_idx)
{
    bool entry_found = false;

    for (uint32_t i = 0; i < BSP_FEATURE_PD_CTRL_VALID_ENTRIES; ++i)
    {
        if (BSP_PD_CTRL_UNUSED_LUT_ENTRY_VALUE == PDC->PDC_CTRL_REG[i])
        {
            *p_idx               = i;
            PDC->PDC_CTRL_REG[i] = bsp_pd_ctrl_prv_entry_translate(entry);
            entry_found          = true;
            break;
        }
    }

    return entry_found ? BSP_PD_CTRL_SUCCESS : BSP_PD_CTRL_ERROR_PDC_LUT_FULL;
}

/*******************************************************************************************************************//**
 * @brief Get the first PDC LUT entry index matching specific criteria.
 *
 * @param[in]  entry  Search options provided in the form of a PDC LUT entry. Fields that should not be used to
 *                    filter out potential candidates, must be set to BSP_PD_CTRL_FILTER_DONT_CARE.
 * @param[in]  start  Index of starting search point in the PDC LUT.
 * @param[out] p_idx  Pointer to variable where index of found entry is stored.
 *
 *
 * @retval     BSP_PD_CTRL_SUCCESS                Operation was successful, entry was found at index idx.
 * @retval     BSP_PD_CTRL_ERROR_ENTRY_NOT_FOUND  Entry was not found in PDC LUT.
 **********************************************************************************************************************/
bsp_pd_ctrl_error_t bsp_pd_ctrl_entry_find (bsp_pd_ctrl_entry_t entry, uint32_t start, uint32_t * p_idx)
{
    for (uint32_t curr_idx = start; curr_idx < BSP_FEATURE_PD_CTRL_VALID_ENTRIES; ++curr_idx)
    {
        if (bsp_prv_pd_ctrl_entry_match(entry, (uint8_t) curr_idx))
        {
            *p_idx = curr_idx;

            return BSP_PD_CTRL_SUCCESS;
        }
    }

    return BSP_PD_CTRL_ERROR_ENTRY_NOT_FOUND;
}

/*******************************************************************************************************************//**
 * @brief Remove a PDC LUT entry located in a specific index. Entry will contain BSP_PD_CTRL_UNUSED_LUT_ENTRY_VALUE
 *        after the operation is complete.
 *
 * @param[in]  idx      Index of the entry that is to be removed. Valid range: 0 - (BSP_FEATURE_PD_CTRL_VALID_ENTRIES-1)
 * @param[out] p_value  The value of the entry that was removed from the provided index of the PDC LUT.
 **********************************************************************************************************************/
void bsp_pd_ctrl_entry_remove (uint32_t idx, uint32_t * p_value)
{
    bsp_pd_ctrl_entry_read(idx, p_value);

    PDC->PDC_CTRL_REG[idx] = BSP_PD_CTRL_UNUSED_LUT_ENTRY_VALUE;
}

/*******************************************************************************************************************//**
 * @brief Reset the PDC look-up table. Keeps only the selected PDC LUT entries. All other entries are set to
 *        BSP_PD_CTRL_UNUSED_LUT_ENTRY_VALUE.
 *
 * @param[in]  p_keep    Pointer to list of entries that should be kept. These entries are
 *                       compared to the ones present in the PDC LUT. Fields that should not be used to
 *                       filter out potential kept entries, must be set to BSP_PD_CTRL_FILTER_DONT_CARE. If
 *                       pointer is null, then all entries are reset.
 * @param[in]  keep_len  Number of entries in the list.
 * @param[out] p_kept    Pointer to bitmask of entries contained in p_keep that were found in PDC LUT and therefore
 *                       were not removed.
 **********************************************************************************************************************/
void bsp_pd_ctrl_entry_reset (bsp_pd_ctrl_entry_t * p_keep, uint32_t keep_len, uint32_t * p_kept)
{
    uint32_t old_value;

    if (!p_keep)
    {
        /* keep list is empty */
        bsp_pd_ctrl_prv_entry_reset();

        /* p_kept is ignored, as all entries are reset and therefore the mask of kept entries is 0. */
        return;
    }

    if (p_kept)
    {
        *p_kept = 0;
    }

    for (uint8_t idx = 0; idx < BSP_FEATURE_PD_CTRL_VALID_ENTRIES; idx++)
    {
        uint8_t keep_idx;
        for (keep_idx = 0; keep_idx < keep_len; keep_idx++)
        {
            if (bsp_prv_pd_ctrl_entry_match(p_keep[keep_idx], idx))
            {
                if (p_kept)
                {
                    *p_kept |= (1 << keep_idx);
                }

                break;
            }
        }

        /* Keep-list exhausted without a match, remove unmatched entry */
        if (keep_len == keep_idx)
        {
            bsp_pd_ctrl_entry_remove(idx, &old_value);
        }
    }
}

/*******************************************************************************************************************//**
 * @brief Set a PDC LUT entry as pending.
 *
 * @param[in]  idx Index of the entry. Valid range: 0 - (BSP_FEATURE_PD_CTRL_VALID_ENTRIES-1)
 *
 * @retval     BSP_PD_CTRL_SUCCESS                  Operation was successful.
 * @retval     BSP_PD_CTRL_ERROR_INVALID_LUT_ENTRY  Entry contains invalid master and cannot be set pending.
 **********************************************************************************************************************/
bsp_pd_ctrl_error_t bsp_pd_ctrl_pending_set (uint32_t idx)
{
    uint32_t entry;

    bsp_pd_ctrl_entry_read(idx, &entry);

    if (0 == (entry & PDC_PDC_CTRL_REG_PDC_MASTER_Msk))
    {
        return BSP_PD_CTRL_ERROR_INVALID_LUT_ENTRY;
    }

    PDC->PDC_SET_PENDING_REG = idx;

    return BSP_PD_CTRL_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get all pending PDC LUT entries.
 *
 * @param[out] p_status   Pointer to a 16-bit value, where each bit indicates whether the corresponding
 *                        PDC LUT entry is pending.
 **********************************************************************************************************************/
void bsp_pd_ctrl_pending_get (uint32_t * p_status)
{
    *p_status = PDC->PDC_PENDING_REG & PDC_PDC_PENDING_REG_PDC_PENDING_Msk;
}

/*******************************************************************************************************************//**
 * @brief Acknowledge a PDC LUT entry.
 *
 * @param[in]  idx Index of the entry that is to be acknowledged. Valid range: 0 - (BSP_FEATURE_PD_CTRL_VALID_ENTRIES-1)
 **********************************************************************************************************************/
void bsp_pd_ctrl_acknowledge (uint32_t idx)
{
    PDC->PDC_ACKNOWLEDGE_REG = idx;
}

/** @} (end addtogroup BSP_MCU) */

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Helper function that translates the look-up entry structure to the actual 32-bit value
 * that is to be written.
 **********************************************************************************************************************/
static uint32_t bsp_pd_ctrl_prv_entry_translate (bsp_pd_ctrl_entry_t entry)
{
    uint32_t reg_value;

    reg_value = (((entry.trig_select) << PDC_PDC_CTRL_REG_TRIG_SELECT_Pos) & PDC_PDC_CTRL_REG_TRIG_SELECT_Msk) | \
                (((entry.trig_id) << PDC_PDC_CTRL_REG_TRIG_ID_Pos) & PDC_PDC_CTRL_REG_TRIG_ID_Msk) |             \
                entry.wakeup_options |                                                                           \
                (((entry.wakeup_master) << PDC_PDC_CTRL_REG_PDC_MASTER_Pos) & PDC_PDC_CTRL_REG_PDC_MASTER_Msk);

    return reg_value;
}

/*******************************************************************************************************************//**
 * Helper function that checks if PDC LUT entry at index idx matches the one provided.
 **********************************************************************************************************************/
static bool bsp_prv_pd_ctrl_entry_match (bsp_pd_ctrl_entry_t entry, uint8_t idx)
{
    uint32_t mask    = 0;
    uint32_t pattern = 0;
    uint32_t val;

    mask |= (entry.trig_select == BSP_PD_CTRL_FILTER_DONT_CARE) ? mask : PDC_PDC_CTRL_REG_TRIG_SELECT_Msk;
    mask |= (entry.trig_id == BSP_PD_CTRL_FILTER_DONT_CARE) ? mask : PDC_PDC_CTRL_REG_TRIG_ID_Msk;
    mask |= ((entry.wakeup_options == BSP_PD_CTRL_FILTER_DONT_CARE) ? mask : entry.wakeup_options);
    mask |= (entry.wakeup_master == BSP_PD_CTRL_FILTER_DONT_CARE) ? mask : PDC_PDC_CTRL_REG_PDC_MASTER_Msk;

    entry.wakeup_options =
        (entry.wakeup_options == BSP_PD_CTRL_FILTER_DONT_CARE) ? (bsp_pd_ctrl_options_t) 0 : entry.wakeup_options;

    pattern = bsp_pd_ctrl_prv_entry_translate(entry);

    bsp_pd_ctrl_entry_read(idx, &val);

    return (val & mask) == (pattern & mask);
}

/*******************************************************************************************************************//**
 * Reset PDC look-up table. All entries are set to BSP_PD_CTRL_UNUSED_LUT_ENTRY_VALUE.
 **********************************************************************************************************************/
static void bsp_pd_ctrl_prv_entry_reset (void)
{
    for (uint32_t idx = 0; idx < BSP_FEATURE_PD_CTRL_VALID_ENTRIES; ++idx)
    {
        bsp_pd_ctrl_acknowledge(idx);
        PDC->PDC_CTRL_REG[idx] = BSP_PD_CTRL_UNUSED_LUT_ENTRY_VALUE;
    }
}

#endif
