/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_MISC_H
#define HPM_MISC_H

#define CORE0_ILM_LOCAL_BASE   (0x00000000U)
#define CORE0_ILM_SIZE_IN_BYTE (0x00040000U)
#define CORE0_DLM_LOCAL_BASE   (0x00200000U)
#define CORE0_DLM_SIZE_IN_BYTE (0x00040000U)
#define CORE1_ILM_LOCAL_BASE   (0x00040000U)
#define CORE1_ILM_SIZE_IN_BYTE (0x00040000U)
#define CORE1_DLM_LOCAL_BASE   (0x00240000U)
#define CORE1_DLM_SIZE_IN_BYTE (0x00040000U)

#define CORE0_ILM_SYSTEM_BASE  (0x00000000U)
#define CORE0_DLM_SYSTEM_BASE  (0x00200000U)
#define CORE1_ILM_SYSTEM_BASE  (0x00040000U)
#define CORE1_DLM_SYSTEM_BASE  (0x00240000U)

#define HPM_CORE0 (0U)
#define HPM_CORE1 (1U)

/* map core local memory(DLM/ILM) to system address */
static inline uint32_t core_local_mem_to_sys_address(uint8_t core_id, uint32_t addr)
{
    (void) core_id;
    return addr;
}

/* map system address to core local memory(DLM/ILM) */
static inline uint32_t sys_address_to_core_local_mem(uint8_t core_id, uint32_t addr)
{
    (void) core_id;
    return addr;
}
#endif /* HPM_MISC_H */
