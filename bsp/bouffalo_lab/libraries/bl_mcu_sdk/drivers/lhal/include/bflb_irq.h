#ifndef _BFLB_IRQ_H
#define _BFLB_IRQ_H

#include "stdint.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup IRQ
  * @{
  */

typedef void (*irq_callback)(int irq, void *arg);

/**
 * @brief IRQ configuration structure
 *
 * @param handler      Address of the interrupt handler
 * @param arg          The argument provided to the interrupt handler
 */
struct bflb_irq_info_s {
    irq_callback handler;
    void *arg;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Interrupt initialize.
 *
 */
void bflb_irq_initialize(void);

/**
 * @brief Disable global irq and save the previous status.
 *
 * @return last status
 */
uintptr_t bflb_irq_save(void);

/**
 * @brief Enable global irq by the previous status.
 *
 * @param [in] flags previous status by bflb_irq_save
 */
void bflb_irq_restore(uintptr_t flags);

/**
 * @brief Attach interrupt with callback.
 *
 * @param [in] irq irq number
 * @param [in] isr interrupt callback
 * @param [in] arg user data
 * @return A negated errno value on failure.
 */
int bflb_irq_attach(int irq, irq_callback isr, void *arg);

/**
 * @brief Detach interrupt, reset interrupt callback.
 *
 * @param [in] irq irq number
 * @return A negated errno value on failure.
 */
int bflb_irq_detach(int irq);

/**
 * @brief Enable interrupt.
 *
 * @param [in] irq irq number
 */
void bflb_irq_enable(int irq);

/**
 * @brief Disable interrupt.
 *
 * @param [in] irq irq number
 */
void bflb_irq_disable(int irq);

/**
 * @brief Set interrupt with pending.
 *
 * @param [in] irq irq number
 */
void bflb_irq_set_pending(int irq);

/**
 * @brief Clear interrupt pending status.
 *
 * @param [in] irq irq number
 */
void bflb_irq_clear_pending(int irq);

/**
 * @brief Set interrupt group.
 *
 * @param [in] nlbits
 */
void bflb_irq_set_nlbits(uint8_t nlbits);

/**
 * @brief Set interrupt priority.
 *
 * @param [in] irq irq number
 * @param [in] preemptprio preempt priority
 * @param [in] subprio sub priority
 */
void bflb_irq_set_priority(int irq, uint8_t preemptprio, uint8_t subprio);

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