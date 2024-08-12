/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_BPOR_H
#define HPM_BPOR_H

typedef struct {
    __RW uint32_t POR_CONFIG;                  /* 0x0: Power on reset config */
} BPOR_Type;


/* Bitfield definition for register: POR_CONFIG */
/*
 * RETENTION (RW)
 *
 * retention battery domain setting
 * 0: battery reset on reset pin reset happen
 * 1: battery domain retention when reset pin reset happen
 */
#define BPOR_POR_CONFIG_RETENTION_MASK (0x1U)
#define BPOR_POR_CONFIG_RETENTION_SHIFT (0U)
#define BPOR_POR_CONFIG_RETENTION_SET(x) (((uint32_t)(x) << BPOR_POR_CONFIG_RETENTION_SHIFT) & BPOR_POR_CONFIG_RETENTION_MASK)
#define BPOR_POR_CONFIG_RETENTION_GET(x) (((uint32_t)(x) & BPOR_POR_CONFIG_RETENTION_MASK) >> BPOR_POR_CONFIG_RETENTION_SHIFT)




#endif /* HPM_BPOR_H */
