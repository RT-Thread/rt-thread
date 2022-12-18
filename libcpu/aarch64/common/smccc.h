/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __SMCCC_H__
#define __SMCCC_H__

/**
 * result from SMC/HVC call
 * ARM DEN0028E chapter 5,
 */
typedef struct arm_smccc_res_t
{
    unsigned long a0;
    // reserved for ARM SMC and HVC Fast Call services
    unsigned long a1;
    unsigned long a2;
    unsigned long a3;
} arm_smccc_res_t;

/**
 * quirk is a structure contains vendor specified information,
 * it just a placeholder currently
 */
struct arm_smccc_quirk_t
{
};

/* smccc version 0.2 */

void arm_smccc_smc(unsigned long a0, unsigned long a1, unsigned long a2,
                   unsigned long a3, unsigned long a4, unsigned long a5,
                   unsigned long a6, unsigned long a7, struct arm_smccc_res_t *res,
                   struct arm_smccc_quirk_t *quirk);

void arm_smccc_hvc(unsigned long a0, unsigned long a1, unsigned long a2,
                   unsigned long a3, unsigned long a4, unsigned long a5,
                   unsigned long a6, unsigned long a7, struct arm_smccc_res_t *res,
                   struct arm_smccc_quirk_t *quirk);

#endif /* __SMCCC_H__ */
