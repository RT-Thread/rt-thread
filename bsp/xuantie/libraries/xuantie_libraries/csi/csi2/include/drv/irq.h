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
 * @file     drv/irq.h
 * @brief    header File for IRQ Driver
 * @version  V1.0
 * @date     16. Mar 2020
 * @model    irq
 ******************************************************************************/

#ifndef _DRV_IRQ_H_
#define _DRV_IRQ_H_

#include <stdint.h>
#include <drv/common.h>
#include <soc.h>
#include <csi_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief       Enable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
__ALWAYS_STATIC_INLINE void csi_irq_enable(uint32_t irq_num)
{
    extern void soc_irq_enable(uint32_t irq_num);
    soc_irq_enable(irq_num);
}

/**
  \brief       Disable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
__ALWAYS_STATIC_INLINE void csi_irq_disable(uint32_t irq_num)
{
    extern void soc_irq_disable(uint32_t irq_num);
    soc_irq_disable(irq_num);
}

/**
  \brief       Attach irq handler.
  \param[in]   irq_num     Number of IRQ.
  \param[in]   irq_handler IRQ Handler.
  \param[in]   dev         The dev to operate
  \return      None.
*/
void csi_irq_attach(uint32_t irq_num, void *irq_handler, csi_dev_t *dev);

/**
  \brief       Attach irq handler2 for compatible.
  \param[in]   irq_num      Number of IRQ.
  \param[in]   irq_handler2 IRQ Handler.
  \param[in]   dev          The dev to operate
  \param[in]   arg          user data of irq_handler2
  \return      None.
*/
void csi_irq_attach2(uint32_t irq_num, void *irq_handler2, csi_dev_t *dev, void *arg);

/**
  \brief       detach irq handler.
  \param[in]   irq_num Number of IRQ.
  \param[in]   irq_handler IRQ Handler.
  \return      None.
*/
void csi_irq_detach(uint32_t irq_num);

/**
  \brief       Set irq priority
  \param[in]   irq_num Number of IRQ.
  \param[in]   priority IRQ Priority.
  \return      None.
*/
__ALWAYS_STATIC_INLINE void csi_irq_priority(uint32_t irq_num, uint32_t priority)
{
    extern void soc_irq_priority(uint32_t irq_num, uint32_t priority);
    soc_irq_priority(irq_num, priority);
}

/**
  \brief       Gets whether the interrupt is enabled
  \param[in]   irq_num Number of IRQ.
  \return      true or false.
*/
static inline bool csi_irq_is_enabled(uint32_t irq_num)
{
    extern bool soc_irq_is_enabled(uint32_t irq_num);
    return soc_irq_is_enabled(irq_num);
}

/**
  \brief       Enable the interrupt wakeup attribution
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
__ALWAYS_STATIC_INLINE void csi_irq_enable_wakeup(uint32_t irq_num)
{
    extern void soc_irq_enable_wakeup(uint32_t irq_num);
    soc_irq_enable_wakeup(irq_num);
}

/**
  \brief       Disable the interrupt wakeup attribution
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
__ALWAYS_STATIC_INLINE void csi_irq_disable_wakeup(uint32_t irq_num)
{
    extern void soc_irq_disable_wakeup(uint32_t irq_num);
    soc_irq_disable_wakeup(irq_num);
}

/**
  \brief       Gets whether in irq context
  \return      true or false.
*/
bool csi_irq_context(void);

/**
  \brief       Dispatching irq handlers
  \return      None.
*/
void do_irq(void);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_IRQ_H_ */
