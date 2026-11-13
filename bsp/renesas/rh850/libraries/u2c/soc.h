/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#ifndef __SOC_U2C_H__
#define __SOC_U2C_H__

#define SOC_INTC1_BASE     0xfffc4000
#define SOC_INTC2_BASE     0xfff80000
#define SOC_INTC1_CHANNELS 32
#define SOC_INTC_CHANNELS  630

#define SOC_OSTM0_BASE 0xffbf0000
#define SOC_IRQ_OSTM0  63

#define SOC_RLIN311_BASE    0xff89bb00
#define SOC_IRQ_RLIN311_UR1 495

/* CLKC_HSB as QEMU rh850-u2c models it; not checked on silicon */
#define SOC_CLK_HSB_HZ 20000000

#define SOC_CKS_RLINC    0xff980140
#define SOC_CKS_RLINS    0xff980148
#define SOC_CLKKCPROT1   0xff980700
#define SOC_CKS_RLIN_HSB 1

#define SOC_SWMRESS_RLIN3 0xff980964
#define SOC_SWMRESS_OSTM  0xff980a84

#define SOC_MSR_RLIN3       0xff981060
#define SOC_MSR_OSTM        0xff981180
#define SOC_MSRKCPROT       0xff981710
#define SOC_MSR_RLIN311_BIT (1 << 11)
#define SOC_MSR_OSTM0_BIT   (1 << 0)

#define SOC_KCPROT_ENABLE  0xa5a5a501
#define SOC_KCPROT_DISABLE 0xa5a5a500

void soc_init(void);

#endif
