/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_BKEY_DRV_H
#define HPM_BKEY_DRV_H

#include "hpm_common.h"
#include "hpm_bkey_regs.h"

/**
 *
 * @brief BKEY driver APIs
 * @defgroup bkey_interface BKEY driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief Lock type
 */
typedef enum bkey_lock_type {
    bkey_lock_write = BKEY_ECC_WLOCK_MASK,
    bkey_lock_read = BKEY_ECC_RLOCK_MASK,
    bkey_lock_both = BKEY_ECC_RLOCK_MASK | BKEY_ECC_WLOCK_MASK,
} bkey_lock_type_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief bkey set key content
 *
 * Program key content
 *
 * @param[in] ptr BKEY base address
 * @param[in] key Key index
 * @param[in] start Key content data start index
 * @param[in] data pointer of actual data to be programmed
 * @param[in] size data total size in 32-bit
 */
static inline void bkey_set_key_data(BKEY_Type *ptr, uint8_t key, uint8_t start, uint32_t *data, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++) {
        ptr->KEY[key].DATA[start + i] = *(data + i);
    }
}

/**
 * @brief bkey fetch key content
 *
 * Fetch key content
 *
 * @param[in] ptr BKEY base address
 * @param[in] key key index
 * @param[in] start key content data start index
 * @param[in] data pointer of buffer to received key content
 * @param[in] size data total size in 32-bit
 */
static inline void bkey_get_key_data(BKEY_Type *ptr, uint8_t key, uint8_t start, uint32_t *data, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++) {
        *(data + i) = ptr->KEY[key].DATA[start + i];
    }
}

/**
 * @brief bkey lock key
 *
 * Feed correct ecc data of current key content and lock it
 *
 * @param[in] ptr BKEY base address
 * @param[in] key key index
 * @param[in] lock lock type
 * @param[in] ecc ecc value of current key content
 */
static inline void bkey_lock(BKEY_Type *ptr, uint8_t key, bkey_lock_type_t lock, uint16_t ecc)
{
    ptr->ECC[key] = BKEY_ECC_ECC_SET(ecc) | lock;
}

/**
 * @brief bkey select key
 *
 * Select which key to use
 *
 * @param[in] ptr BKEY base address
 * @param[in] key key index
 *   @arg 0 select key0 in secure mode, key1 in non-secure mode
 *   @arg 1 select key1 in secure or non-secure mode
 */
static inline void bkey_select_key(BKEY_Type *ptr, uint8_t key)
{
    ptr->SELECT = BKEY_SELECT_SELECT_SET(key);
}

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_BKEY_DRV_H */
