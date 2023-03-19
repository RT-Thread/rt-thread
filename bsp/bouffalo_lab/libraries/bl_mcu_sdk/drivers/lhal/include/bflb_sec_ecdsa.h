#ifndef _BFLB_SEC_ECDSA_H
#define _BFLB_SEC_ECDSA_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup SEC_ECDSA
  * @{
  */

#define ECP_SECP256R1 0
#define ECP_SECP256K1 1

struct bflb_ecdsa_s {
    uint8_t ecpId;
    uint8_t pad[3];
    uint32_t *privateKey;
    uint32_t *publicKeyx;
    uint32_t *publicKeyy;
};

struct bflb_ecdh_s {
    uint8_t ecpId;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 *
 * @param [in] handle
 * @param [in] id
 * @return int
 */
int bflb_sec_ecdsa_init(struct bflb_ecdsa_s *handle, uint8_t id);

/**
 * @brief
 *
 * @param [in] handle
 * @return int
 */
int bflb_sec_ecdsa_deinit(struct bflb_ecdsa_s *handle);

/**
 * @brief
 *
 * @param [in] handle
 * @param [in] random_k
 * @param [in] hash
 * @param [in] hashLenInWord
 * @param [in] r
 * @param [in] s
 * @return int
 */
int bflb_sec_ecdsa_sign(struct bflb_ecdsa_s *handle, const uint32_t *random_k, const uint32_t *hash, uint32_t hashLenInWord, uint32_t *r, uint32_t *s);

/**
 * @brief
 *
 * @param [in] handle
 * @param [in] hash
 * @param [in] hashLen
 * @param [in] r
 * @param [in] s
 * @return int
 */
int bflb_sec_ecdsa_verify(struct bflb_ecdsa_s *handle, const uint32_t *hash, uint32_t hashLen, const uint32_t *r, const uint32_t *s);

/**
 * @brief
 *
 * @param [in] handle
 * @param [in] private_key
 * @return int
 */
int bflb_sec_ecdsa_get_private_key(struct bflb_ecdsa_s *handle, uint32_t *private_key);

/**
 * @brief
 *
 * @param [in] handle
 * @param [in] private_key
 * @param [in] pRx
 * @param [in] pRy
 * @return int
 */
int bflb_sec_ecdsa_get_public_key(struct bflb_ecdsa_s *handle, const uint32_t *private_key, const uint32_t *pRx, const uint32_t *pRy);

/**
 * @brief
 *
 * @param [in] handle
 * @param [in] id
 * @return int
 */
int bflb_sec_ecdh_init(struct bflb_ecdh_s *handle, uint8_t id);

/**
 * @brief
 *
 * @param [in] handle
 * @return int
 */
int bflb_sec_ecdh_deinit(struct bflb_ecdh_s *handle);

/**
 * @brief
 *
 * @param [in] handle
 * @param [in] pkX
 * @param [in] pkY
 * @param [in] private_key
 * @param [in] pRx
 * @param [in] pRy
 * @return int
 */
int bflb_sec_ecdh_get_encrypt_key(struct bflb_ecdh_s *handle, const uint32_t *pkX, const uint32_t *pkY, const uint32_t *private_key, const uint32_t *pRx, const uint32_t *pRy);

/**
 * @brief
 *
 * @param [in] handle
 * @param [in] private_key
 * @param [in] pRx
 * @param [in] pRy
 * @return int
 */
int bflb_sec_ecdh_get_public_key(struct bflb_ecdh_s *handle, const uint32_t *private_key, const uint32_t *pRx, const uint32_t *pRy);

/**
 * @brief
 *
 * @param [in] data
 * @param [in] max_ref
 * @param [in] size
 * @return int
 */
int bflb_sec_ecc_get_random_value(uint32_t *data, uint32_t *max_ref, uint32_t size);

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