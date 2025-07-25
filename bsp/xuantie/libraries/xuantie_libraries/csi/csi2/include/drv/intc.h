 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     drv/intc.h
 * @brief    Header File for INTC Driver
 * @version  V1.0
 * @date     02. June 2020
 * @model    intc
 ******************************************************************************/

#ifndef _DRV_INTC_H_
#define _DRV_INTC_H_

#include <stdint.h>
#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef enum int_trigger_mode_t {
    INT_MODE_LOW_LEVEL,
    INT_MODE_HIGH_LEVEL,
    INT_MODE_RISING_EDGE,
    INT_MODE_FALLING_EDGE,
    INT_MODE_DOUBLE_EDGE,
} int_trigger_mode_t;

/**
  \brief    Initialize the INTC interrupt controller
 */
void csi_intc_init(void);

/**
  \brief        Enable External Interrupt
  \details      Enables a device-specific interrupt in the INTC interrupt controller.
  \param[in]    IRQn  External interrupt number. Value cannot be negative.
 */
void csi_intc_enable_irq(int32_t IRQn);

/**
  \brief        Disable External Interrupt
  \details      Disables a device-specific interrupt in the INTC interrupt controller.
  \param[in]    IRQn  External interrupt number. Value cannot be negative.
 */
void csi_intc_disable_irq(int32_t IRQn);

/**
  \brief        Get Pending Interrupt
  \details      Reads the pending register in the INTC and returns the pending bit for the specified interrupt.
  \param[in]    IRQn  Interrupt number.
  \return       0  Interrupt status is not pending.
  \return       1  Interrupt status is pending.
 */
uint32_t csi_intc_get_pending_irq(int32_t IRQn);

/**
  \brief        Set Pending Interrupt
  \details      Sets the pending bit of an external interrupt.
  \param[in]    IRQn  Interrupt number. Value cannot be negative.
 */
void csi_intc_set_pending_irq(int32_t IRQn);

/**
  \brief        Clear Pending Interrupt
  \details      Clears the pending bit of an external interrupt.
  \param[in]    IRQn  External interrupt number. Value cannot be negative.
 */
void csi_intc_clear_pending_irq(int32_t IRQn);

/**
  \brief        Get Wake up Interrupt
  \details      Reads the wake up register in the INTC and returns the pending bit for the specified interrupt.
  \param[in]    IRQn  Interrupt number.
  \return       0  Interrupt is not set as wake up interrupt.
  \return       1  Interrupt is set as wake up interrupt.
 */
uint32_t csi_intc_get_wakeup_irq(int32_t IRQn);

/**
  \brief        Set Wake up Interrupt
  \details      Sets the wake up bit of an external interrupt.
  \param[in]    IRQn  Interrupt number. Value cannot be negative.
 */
void csi_intc_set_wakeup_irq(int32_t IRQn);

/**
  \brief        Clear Wake up Interrupt
  \details      Clears the wake up bit of an external interrupt.
  \param[in]    IRQn  External interrupt number. Value cannot be negative.
 */
void csi_intc_clear_wakeup_irq(int32_t IRQn);

/**
  \brief        Get Active Interrupt
  \details      Reads the active register in the INTC and returns the active bit for the device specific interrupt.
  \param[in]    IRQn  Device specific interrupt number.
  \return       0  Interrupt status is not active.
  \return       1  Interrupt status is active.
  \note    IRQn must not be negative.
 */
uint32_t csi_intc_get_active(int32_t IRQn);

/**
  \brief        Set Threshold register
  \details      set the threshold register in the INTC.
  \param[in]    VectThreshold  specific vecter threshold.
  \param[in]    PrioThreshold  specific priority threshold.
 */
void csi_intc_set_threshold(uint32_t VectThreshold, uint32_t PrioThreshold);

/**
  \brief        Set Interrupt Priority
  \details      Sets the priority of an interrupt.
  \note         The priority cannot be set for every core interrupt.
  \param[in]    IRQn  Interrupt number.
  \param[in]    priority  Priority to set.
 */
void csi_intc_set_prio(int32_t IRQn, uint32_t priority);

/**
  \brief        Get Interrupt Priority
  \details      Reads the priority of an interrupt.
                The interrupt number can be positive to specify an external (device specific) interrupt,
                or negative to specify an internal (core) interrupt.
  \param[in]    IRQn  Interrupt number.
  \return       Interrupt Priority.
                Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
uint32_t csi_intc_get_prio(int32_t IRQn);

/**
  \brief        funciton is acknowledge the IRQ. this interface is internally used by irq system
  \param[in]    irq  irq number to operate
  \return       0 on success; -1 on failure
 */
int csi_intc_ack_irq(int32_t IRQn);

/**
  \brief        This function is set the attributes of an IRQ.
  \param[in]    irq    irq number to operate
  \param[in]    priority    interrupt priority
  \param[in]    trigger_mode    interrupt trigger_mode
  \return       0 on success; -1 on failure
*/
int csi_intc_set_attribute(int32_t IRQn, uint32_t priority, int_trigger_mode_t trigger_mode);

/**
  \brief        Set interrupt handler
  \details      Set the interrupt handler according to the interrupt num, the handler will be filled in g_irqvector[].
  \param[in]    IRQn  Interrupt number.
  \param[in]    handler  Interrupt handler.
 */
void csi_intc_set_vector(int32_t IRQn, uint32_t handler);

/**
  \brief        Get interrupt handler
  \details      Get the address of interrupt handler function.
  \param[in]    IRQn  Interrupt number.
 */
uint32_t csi_intc_get_vector(int32_t IRQn);

#endif /* _DRV_INTC_H_ */
