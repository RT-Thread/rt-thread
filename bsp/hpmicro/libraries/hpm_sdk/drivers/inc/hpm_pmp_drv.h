/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_PMP_DRV_H
#define HPM_PMP_DRV_H

#include "hpm_common.h"
#include "hpm_soc_feature.h"

/**
 * @brief PMP Entry structure
 */
typedef struct pmp_entry_struct {
    union {
        struct {
            uint8_t read_access_ctrl: 1;
            uint8_t write_access_ctrl: 1;
            uint8_t execution_ctrl: 1;
            uint8_t addr_matching_mode: 2;
            uint8_t reserved: 2;
            uint8_t lock: 1;
        };
        uint8_t val;
    } pmp_cfg;
    uint8_t reserved0[3];
    uint32_t pmp_addr;
#if (!defined(PMP_SUPPORT_PMA)) || (defined(PMP_SUPPORT_PMA) && (PMP_SUPPORT_PMA == 1))
    union {
        struct {
            uint8_t entry_addr_matching_mode: 2;
            uint8_t mem_type_attribute: 4;
            uint8_t automic_mem_operation_ctrl: 1;
            uint8_t reserved: 1;
        };
        uint8_t val;
    } pma_cfg;
    uint8_t reserved1[3];
    uint32_t pma_addr;
#endif
} pmp_entry_t;

/**
 * @brief PMP Configuration definitions
 */
#define READ_EN (1U)
#define READ_DIS (0U)
#define WRITE_EN (1U)
#define WRITE_DIS (0U)
#define EXECUTE_EN (1U)
#define EXECUTE_DIS (0U)
#define ADDR_MATCH_MODE_OFF (0U)
#define ADDR_MATCH_TOR (1U)
#define ADDR_MATCH_NAPOT (3U)
#define REG_LOCK (1U)
#define REG_UNLOCK (0U)

/**
 * @brief PMA Configuration definitions
 */
#define MEM_TYPE_DEV_NON_BUF (0U)
#define MEM_TYPE_DEV_BUF (1U)
#define MEM_TYPE_MEM_NON_CACHE_NON_BUF (2U)
#define MEM_TYPE_MEM_NON_CACHE_BUF (3U)
#define MEM_TYPE_MEM_WT_NO_ALLOC (4U)
#define MEM_TYPE_MEM_WT_READ_ALLOC (5U)
#define MEM_TYPE_MEM_WB_NO_ALLOC (8U)
#define MEM_TYPE_MEM_WB_READ_ALLOC (9U)
#define MEM_TYPE_MEM_WB_WRITE_ALLOC (10U)
#define MEM_TYPE_MEM_WB_READ_WRITE_ALLOC (11U)
#define MEM_TYPE_EMPTY_HOLE (15U)

#define AMO_EN (0U)
#define AMO_DIS (1U)

/**
 * @brief PMP Configuration
 * @param r - READ Access control, valid value: READ_EN, READ_DIS
 * @param w - Write access control, valid value: WRITE_EN, WRITE_DIS
 * @param x - Instruction Execution control, valid value: EXECUTE_EN, EXECUTE_DIS
 * @param m - Address matching mode, valid value:
 *            ADDR_MATCH_MODE_OFF - Null region
 *            ADDR_MATCH_TOR - Top of range. For pmp_addr0, any address < pmp_addr0 matches, for other regions,
 *                             any address which meets ( pmp_addr[i-1]  <= addr < pmp_addr) matches.
 *            ADDR_MATCH_NAPOT - Naturally aligned power-of-2 region, minimal size must be 8 bytes
 * @param l - Write lock and permission enforcement bit for Machine mode, valid value: REG_LOCK, REG_UNLOCK
 */
#define PMP_CFG(r, w, x, m, l) ((r) | ((w) << 1) | ((x) << 2) | ((m) << 3) | ((l) << 7))
/**
 * @brief PMA Configuration
 * @param m - Entry address matching mode, valid value:
 *            ADDR_MATCH_MODE_OFF - This PMA entry is disabled
 *            ADDR_MATCH_NAPOT - Naturally aligned power-of-2 region， the granularity is 4K bytes
 * @param t - Memory type attributes, valid value:
 *            MEM_TYPE_DEV_NON_BUF - Device, Non-bufferable
 *            MEM_TYPE_DEV_BUF - Device, bufferable
 *            MEM_TYPE_MEM_NON_CACHE_NON_BUF - Memory, Non-cacheable, Non-bufferable
 *            MEM_TYPE_MEM_NON_CACHE_BUF - Memory, Non-cacheable, bufferable
 *            MEM_TYPE_MEM_WT_NO_ALLOC - Memory, Write-through, No-allocate
 *            MEM_TYPE_MEM_WT_READ_ALLOC - Memory, Write-through, read-allocate
 *            MEM_TYPE_MEM_WB_NO_ALLOC - Memory, Write-back, No-allocate
 *            MEM_TYPE_MEM_WB_READ_ALLOC - Memory, Write-back, Read-allocate
 *            MEM_TYPE_MEM_WB_READ_WRITE_ALLOC - Memory, Write-back, Write-Allocate, Read-Allocate
 *            MEM_TYPE_EMPTY_HOLE - Empty hole, nothing exists
 *
 * @param n - Indicate Whether Atomic Memory Operation instructions are not supported in this region, valid value:
 *            AMO_EN - Atomic Memory Operations are supported
 *            AMO_DIS - Atomic Memory Operations are not supported
 */
#define PMA_CFG(m, t, n) ((m) | ((t) << 2) | ((n) << 6))
/**
 * @brief Format Top Address Region
 */
#define PMP_TOR_ADDR(addr) ((addr) >> 2)
/**
 * @brief Format PMP Natural Aligned Region
 * @param x - start address
 * @param n - power-of-2 aligned length
 */
#define PMP_NAPOT_ADDR(x, n) (((uint32_t)(x) >> 2) | (((uint32_t)(n)-1U) >> 3))
/**
 * @brief Format PMA Natural Aligned Region
 * @param x - start address
 * @param n - power-of-2 aligned length
 */
#define PMA_NAPOT_ADDR(x, n) (((uint32_t)(x) >> 2) | ((((uint32_t)(n)-1U) >> 3)))

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Write PMP Configuration to corresponding PMP_CFG register
 * @param value PMP configuration
 * @param idx  PMP entry index, valid value is 0-15
 */
void write_pmp_cfg(uint32_t value, uint32_t idx);

/**
 * @brief Read PMP configuration
 * @param idx PMP entry index
 * @return PMP configuration
 */
uint32_t read_pmp_cfg(uint32_t idx);


/**
 * @brief Write PMP address to corresponding PMP_ADDR register
 * @param value PMP address
 * @param idx PMP address entry index, valid value is 0-15
 */
void write_pmp_addr(uint32_t value, uint32_t idx);

/**
 * @brief Read PMP address entry
 * @param idx PMP address entry index
 * @return PMP address
 */
uint32_t read_pmp_addr(uint32_t idx);

#if (!defined(PMP_SUPPORT_PMA)) || (defined(PMP_SUPPORT_PMA) && (PMP_SUPPORT_PMA == 1))
/**
 * @brief Read PMA configuration
 * @param idx PMA entry index
 * @return PMA configuration
 */
uint32_t read_pma_cfg(uint32_t idx);

/**
 * @brief Write PMA Configuration to corresponding PMA_CFG register
 * @param value PMA configuration
 * @param idx PMA entry index, valid value is 0-15
 */
void write_pma_cfg(uint32_t value, uint32_t idx);

/**
 * @brief Write PMA address to corresponding PMA_ADDR register
 * @param value PMA address
 * @param idx PMA address entry index, valid value is 0-15
 */
void write_pma_addr(uint32_t value, uint32_t idx);

/**
 * @brief Read PMA address entry
 * @param idx PMA address entry index, valid value is 0-15
 * @return PMA address
 */
uint32_t read_pma_addr(uint32_t idx);
#endif /* #if (!defined(PMP_SUPPORT_PMA)) || (defined(PMP_SUPPORT_PMA) && (PMP_SUPPORT_PMA == 1)) */

/**
 * @brief Configure PMP and PMA for specified PMP/PMA entry
 *
 * @param[in] entry PMP entry
 * @param entry_index PMP/PMA entry index
 * @retval status_invalid_argument  Invalid Arguments were detected
 * @retval status_success           Configuration completed without errors
 */
hpm_stat_t pmp_config_entry(const pmp_entry_t *entry, uint32_t entry_index);

/**
 * @brief Configure PMP and PMA based on the PMP entry list
 * @param entry start of the PMP entry list
 * @param num_of_entries Number of entries in the PMP entry list
 * @retval status_invalid_argument  Invalid Arguments were detected
 * @retval status_success           Configuration completed without errors
 */
hpm_stat_t pmp_config(const pmp_entry_t *entry, uint32_t num_of_entries);

/**
 * @brief Disable PMP and PMA
 */
void pmp_disable(void);

#ifdef __cplusplus
}
#endif


#endif /* HPM_PMP_DRV_H */
