/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PMON_DRV_H
#define HPM_PMON_DRV_H
#include "hpm_common.h"
#include "hpm_pmon_regs.h"

#define PMON_EVENT_GLITCH0 (1U << 0)
#define PMON_EVENT_GLITCH1 (1U << 1)
#define PMON_EVENT_CLOCK0 (1U << 2)
#define PMON_EVENT_CLOCK1 (1U << 3)

#ifdef __cplusplus
extern "C" {
#endif

static inline void pmon_enable(PMON_Type *ptr,
                                   uint8_t monitor_index,
                                   bool enable)
{
    ptr->MONITOR[monitor_index].CONTROL = (ptr->MONITOR[monitor_index].CONTROL
                                & ~PMON_MONITOR_CONTROL_ENABLE_MASK)
                        | PMON_MONITOR_CONTROL_ENABLE_SET(enable);
}

static inline void pmon_select_glitch_mode(PMON_Type *ptr,
                                               uint8_t monitor_index,
                                               bool active_mode)
{
    ptr->MONITOR[monitor_index].CONTROL = (ptr->MONITOR[monitor_index].CONTROL
                                & ~PMON_MONITOR_CONTROL_ACTIVE_MASK)
                        | PMON_MONITOR_CONTROL_ACTIVE_SET(active_mode);
}

static inline bool pmon_glich_detected(PMON_Type *ptr, uint8_t monitor_index)
{
    return ptr->MONITOR[monitor_index].STATUS;
}

static inline void pmon_test_mode_enable(PMON_Type *ptr, bool enable)
{
    ptr->TEST_MODE = (ptr->TEST_MODE & ~PMON_TEST_MODE_DISABLE_MASK)
                        | PMON_TEST_MODE_DISABLE_SET(!enable);
}

static inline void pmon_irq_enable(PMON_Type *ptr, uint32_t mask, bool enable)
{
    ptr->IRQ_ENABLE = (ptr->IRQ_ENABLE & ~mask) | (enable ? mask : 0);
}

static inline uint32_t pmon_irq_get_status(PMON_Type *ptr)
{
    return ptr->IRQ_FLAG;
}

#ifdef __cplusplus
}
#endif

#endif /* HPM_PMON_DRV_H */
