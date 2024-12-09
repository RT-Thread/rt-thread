/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_MISC_H
#define HPM_MISC_H

#define ILM_LOCAL_BASE (0x0U)
#define ILM_SIZE_IN_BYTE (0x40000U)
#define DLM_LOCAL_BASE (0x80000U)
#define DLM_SIZE_IN_BYTE (0x40000U)
#define CORE0_ILM_SYSTEM_BASE (0x1000000U)
#define CORE0_DLM_SYSTEM_BASE (0x1040000U)
#define CORE1_ILM_SYSTEM_BASE (0x1180000U)
#define CORE1_DLM_SYSTEM_BASE (0x11C0000U)

#define ADDRESS_IN_ILM(address) \
    ((ILM_LOCAL_BASE + ILM_SIZE_IN_BYTE) > (address))
#define ADDRESS_IN_DLM(address) \
    (((DLM_LOCAL_BASE) <= (address)) && \
     ((DLM_LOCAL_BASE + DLM_SIZE_IN_BYTE) > (address)))

#define ADDRESS_IN_CORE0_ILM_SYSTEM(address) \
    (((CORE0_ILM_SYSTEM_BASE) <= (address)) && \
     ((CORE0_ILM_SYSTEM_BASE + ILM_SIZE_IN_BYTE) > (address)))
#define ADDRESS_IN_CORE0_DLM_SYSTEM(address) \
    (((CORE0_DLM_SYSTEM_BASE) <= (address)) && \
     ((CORE0_DLM_SYSTEM_BASE + DLM_SIZE_IN_BYTE) > (address)))

#define ADDRESS_IN_CORE1_ILM_SYSTEM(address) \
    (((CORE1_ILM_SYSTEM_BASE) <= (address)) && \
     ((CORE1_ILM_SYSTEM_BASE + ILM_SIZE_IN_BYTE) > (address)))
#define ADDRESS_IN_CORE1_DLM_SYSTEM(address) \
    (((CORE1_DLM_SYSTEM_BASE) <= (address)) && \
     ((CORE1_DLM_SYSTEM_BASE + DLM_SIZE_IN_BYTE) > (address)))

#define DLM_TO_SYSTEM(address) \
    (CORE0_DLM_SYSTEM_BASE + (address) - (DLM_LOCAL_BASE))
#define ILM_TO_SYSTEM(address) \
    (CORE0_ILM_SYSTEM_BASE + (address) - (ILM_LOCAL_BASE))
#define SYSTEM_TO_DLM(address) \
    ((address) - CORE0_DLM_SYSTEM_BASE + (DLM_LOCAL_BASE))

#define HPM_CORE0 (0U)
#define HPM_CORE1 (1U)

/* map core local memory(DLM/ILM) to system address */
static inline uint32_t core_local_mem_to_sys_address(uint8_t core_id, uint32_t addr)
{
    uint32_t sys_addr;
    if (ADDRESS_IN_ILM(addr)) {
        sys_addr = ILM_TO_SYSTEM(addr);
    } else if (ADDRESS_IN_DLM(addr)) {
        sys_addr = DLM_TO_SYSTEM(addr);
    } else {
        return addr;
    }
    if (core_id == HPM_CORE1) {
        sys_addr += CORE1_ILM_SYSTEM_BASE - CORE0_ILM_SYSTEM_BASE;
    }

    return sys_addr;
}

/* map system address to core local memory(DLM/ILM) */
static inline uint32_t sys_address_to_core_local_mem(uint8_t core_id, uint32_t addr)
{
    if (core_id == HPM_CORE1) {
        if (ADDRESS_IN_CORE1_DLM_SYSTEM(addr)) {
            addr = (addr - CORE1_DLM_SYSTEM_BASE) + DLM_LOCAL_BASE;
        } else if (ADDRESS_IN_CORE1_ILM_SYSTEM(addr)) {
            addr = (addr - CORE1_ILM_SYSTEM_BASE) + ILM_LOCAL_BASE;
        }
    } else {
        if (ADDRESS_IN_CORE0_DLM_SYSTEM(addr)) {
            addr = (addr - CORE0_DLM_SYSTEM_BASE) + DLM_LOCAL_BASE;
        } else if (ADDRESS_IN_CORE0_ILM_SYSTEM(addr)) {
            addr = (addr - CORE0_ILM_SYSTEM_BASE) + ILM_LOCAL_BASE;
        }
    }

    return addr;
}
#endif /* HPM_MISC_H */
