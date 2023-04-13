#ifndef _BFLB_SEC_TRNG_H
#define _BFLB_SEC_TRNG_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup TRNG
  * @{
  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Read trng data.
 *
 * @param [in] dev device handle
 * @param [in] data pointer to trng data
 * @return A negated errno value on failure.
 */
int bflb_trng_read(struct bflb_device_s *dev, uint8_t data[32]);

/**
 * @brief Read trng data with custom length.
 *
 * @param [in] data pointer to trng data
 * @param [in] len length to read
 * @return A negated errno value on failure.
 */
int bflb_trng_readlen(uint8_t *data, uint32_t len);

/**
 * @brief Get trng data.
 *
 * @return trng data with word
 */
long random(void);

/**
 * @brief Enable trng in group0.
 *
 * @param [in] dev device handle
 */
void bflb_group0_request_trng_access(struct bflb_device_s *dev);

/**
 * @brief Disable trng in group0.
 *
 * @param [in] dev device handle
 */
void bflb_group0_release_trng_access(struct bflb_device_s *dev);

#ifdef __cplusplus
}
#endif

/**
  * @}
  */

/**
  * @}
  */

#endif