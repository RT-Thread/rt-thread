#ifndef _BFLB_SEC_IRQ_H
#define _BFLB_SEC_IRQ_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup SEC_IRQ
  * @{
  */

#define BFLB_SEC_ENG_IRQ_TYPE_AES  0
#define BFLB_SEC_ENG_IRQ_TYPE_SHA  1
#define BFLB_SEC_ENG_IRQ_TYPE_PKA  2
#define BFLB_SEC_ENG_IRQ_TYPE_TRNG 3
#define BFLB_SEC_ENG_IRQ_TYPE_GMAC 4
#define BFLB_SEC_ENG_IRQ_TYPE_CDET 5

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 *
 * @param [in] sec_type
 * @param [in] callback
 * @param [in] arg
 */
void bflb_sec_irq_attach(uint8_t sec_type, void (*callback)(void *arg), void *arg);

/**
 * @brief
 *
 * @param [in] sec_type
 */
void bflb_sec_irq_detach(uint8_t sec_type);

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