#ifndef _BFLB_L1C_H
#define _BFLB_L1C_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup L1C
  * @{
  */

/**
 * @brief
 *
 */
void bflb_l1c_icache_enable(void);

/**
 * @brief
 *
 */
void bflb_l1c_icache_disable(void);

/**
 * @brief
 *
 */
void bflb_l1c_icache_invalid_all(void);

/**
 * @brief
 *
 */
void bflb_l1c_dcache_enable(void);

/**
 * @brief
 *
 */
void bflb_l1c_dcache_disable(void);

/**
 * @brief
 *
 */
void bflb_l1c_dcache_clean_all(void);

/**
 * @brief
 *
 */
void bflb_l1c_dcache_invalidate_all(void);

/**
 * @brief
 *
 */
void bflb_l1c_dcache_clean_invalidate_all(void);

/**
 * @brief
 *
 * @param [in] addr
 * @param [in] size
 */
void bflb_l1c_dcache_clean_range(void *addr, uint32_t size);

/**
 * @brief
 *
 * @param [in] addr
 * @param [in] size
 */
void bflb_l1c_dcache_invalidate_range(void *addr, uint32_t size);

/**
 * @brief
 *
 * @param [in] addr
 * @param [in] size
 */
void bflb_l1c_dcache_clean_invalidate_range(void *addr, uint32_t size);

void bflb_l1c_hit_count_get(uint32_t *hit_count_low, uint32_t *hit_count_high);
uint32_t bflb_l1c_miss_count_get(void);
void bflb_l1c_cache_write_set(uint8_t wt_en, uint8_t wb_en, uint8_t wa_en);

/**
  * @}
  */

/**
  * @}
  */

#endif