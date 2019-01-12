/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#ifndef __SCU_H__
#define __SCU_H__

#include <stdint.h>

typedef struct {
    // SCU(Snoop Control Unit) registers            // Offset       Secure  Non-secure  Name
    volatile uint32_t control;                      // [0x00]       RW      RW          SCU Control Register                 
    volatile uint32_t config;                       // [0x04]       RO      RO          SCU Configuration Register           
    volatile uint32_t cpuPowerStatus;               // [0x08]       RW      RW          SCU CPU Power Status Register        
    volatile uint32_t invalidAllRegsInSecureState;  // [0x0C]       WO      -           SCU Invalidate All Registers in Secure
    volatile uint32_t rev1[(0x40 - 0x10) / 4];      // [0x3C-0x10]
    volatile uint32_t filteringStartAdr;            // [0x40]       RW      RW          Filtering Start Address Register
    volatile uint32_t filteringEndAdr;              // [0x44]       RW      RW          Filtering End Address Register
    volatile uint32_t rev2[(0x50 - 0x48) / 4];      // [0x4C-0x48]
    volatile uint32_t accessControl;                // [0x50]       RW      RW          SCU Access Control (SAC)Register
    volatile uint32_t nsAccessControl;              // [0x54]       RW      RO          SCU Non-secure Access Control(SNSAC) Register
} SCU;

#ifdef __cplusplus
extern "C" {
#endif

    void scu_enable(void);
    uint32_t scu_get_cpu_nums(void);
    uint32_t scu_get_tag_ram_size_encoding(uint32_t cpuIdx);
    uint32_t scu_get_cpus_in_smp(void);
    void scu_secure_invalidate(uint32_t cpuIdx, uint32_t wayMask);

#ifdef __cplusplus
}
#endif

#endif // __SCU_H__
