#ifndef _BFLB_MTIMER_H
#define _BFLB_MTIMER_H

#include "stdint.h"
#include "stdio.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup MTIMER
  * @{
  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Config mtimer interrupt.
 *
 * @param [in] ticks ticks to invoke interrupt.
 * @param [in] interruptfun interrupt callback
 */
void bflb_mtimer_config(uint64_t ticks, void (*interruptfun)(void));

/**
 * @brief Get mtimer current frequence.
 *
 * @return frequence
 */
uint32_t bflb_mtimer_get_freq(void);

/**
 * @brief Mtimer delay with ms.
 *
 * @param [in] time delay time
 */
void bflb_mtimer_delay_ms(uint32_t time);

/**
 * @brief Mtimer delay with us.
 *
 * @param [in] time delay time
 */
void bflb_mtimer_delay_us(uint32_t time);

/**
 * @brief Get current mtimer time with us.
 *
 * @return time with us
 */
uint64_t bflb_mtimer_get_time_us();

/**
 * @brief Get current mtimer time with ms.
 *
 * @return time with ms
 */
uint64_t bflb_mtimer_get_time_ms();

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