#ifndef _BFLB_COMMON_H
#define _BFLB_COMMON_H

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 *
 * @param [in] dst
 * @param [in] src
 * @param [in] n
 * @return void*
 */
void *arch_memcpy(void *dst, const void *src, uint32_t n);

/**
 * @brief
 *
 * @param [in] s
 * @param [in] c
 * @param [in] n
 * @return void*
 */
void *arch_memset(void *s, uint8_t c, uint32_t n);

/**
 * @brief
 *
 * @param [in] s1
 * @param [in] s2
 * @param [in] n
 * @return int
 */
int arch_memcmp(const void *s1, const void *s2, uint32_t n);

/**
 * @brief
 *
 * @param [in] dst
 * @param [in] src
 * @param [in] n
 * @return uint32_t*
 */
uint32_t *arch_memcpy4(uint32_t *dst, const uint32_t *src, uint32_t n);

/**
 * @brief
 *
 * @param [in] pdst
 * @param [in] psrc
 * @param [in] n
 * @return void*
 */
void *arch_memcpy_fast(void *pdst, const void *psrc, uint32_t n);

/**
 * @brief
 *
 * @param [in] dst
 * @param [in] val
 * @param [in] n
 * @return uint32_t*
 */
uint32_t *arch_memset4(uint32_t *dst, const uint32_t val, uint32_t n);

/**
 * @brief
 *
 * @param [in] cnt
 */
void arch_delay_us(uint32_t cnt);

/**
 * @brief
 *
 * @param [in] cnt
 */
void arch_delay_ms(uint32_t cnt);

/**
 * @brief
 * 
 * @param [in] in
 * @param [in] len
 * @return [in] uint16_t
 */
uint16_t bflb_soft_crc16(void *in, uint32_t len);

/**
 * @brief
 *
 * @param [in] in
 * @param [in] len
 * @return [in] uint32_t
 */
uint32_t bflb_soft_crc32(void *in, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif