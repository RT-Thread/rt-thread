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

#include <csi_config.h>
#include <stdbool.h>
#include <csi_core.h>
#include <soc.h>

void soc_irq_enable(uint32_t irq_num)
{
    csi_vic_enable_irq((int32_t)irq_num);
}

void soc_irq_disable(uint32_t irq_num)
{
    csi_vic_disable_irq((int32_t)irq_num);
}

bool soc_irq_is_enabled(uint32_t irq_num)
{
    bool ret;

    if (csi_vic_get_enabled_irq((int32_t)irq_num)) {
        ret = true;
    } else {
        ret = false;
    }

    return ret;
}

void soc_irq_priority(uint32_t irq_num, uint32_t priority)
{
    csi_vic_set_prio((int32_t)irq_num, priority);
}

/**
 * @brief get external irq number only
 * @return irq no
 */
uint32_t soc_irq_get_irq_num(void)
{
#if CONFIG_CPU_XUANTIE_E9XX
    return (__get_MCAUSE() & 0x3FFU);
#else
    uint32_t num;
#if CONFIG_INTC_CLIC_PLIC
    uint32_t irqn = __get_MCAUSE() & 0x3FFU;
    if (irqn == Machine_External_IRQn) {
        num = PLIC_Hn_MSCLAIM_VAL(&PLIC->PLIC_H0_MCLAIM, csi_get_cpu_id());
        num += PLIC_IRQ_OFFSET;
    } else {
        num = irqn;
    }
#else
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    num = PLIC_Hn_MSCLAIM_VAL(&PLIC->PLIC_H0_SCLAIM, csi_get_cpu_id());
#else
    num = PLIC_Hn_MSCLAIM_VAL(&PLIC->PLIC_H0_MCLAIM, csi_get_cpu_id());
#endif
#endif
    return num;
#endif /* end exx */
}

void soc_irq_end(uint32_t irq_num)
{
#if CONFIG_CPU_XUANTIE_E9XX
    //TODO:
#else
#if CONFIG_INTC_CLIC_PLIC
    if (irq_num <= PLIC_IRQ_OFFSET) {
        return;
    }
    irq_num -= PLIC_IRQ_OFFSET;
#endif
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    PLIC_Hn_MSCLAIM_VAL(&PLIC->PLIC_H0_SCLAIM, csi_get_cpu_id()) = irq_num;
#else
    PLIC_Hn_MSCLAIM_VAL(&PLIC->PLIC_H0_MCLAIM, csi_get_cpu_id()) = irq_num;
#endif
#endif /* end exx */
}
