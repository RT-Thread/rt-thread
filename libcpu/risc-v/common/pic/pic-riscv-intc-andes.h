/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-30     GuEe-GUI     first version
 */

#ifndef __PIC_RISCV_INTC_ANDES_H__
#define __PIC_RISCV_INTC_ANDES_H__

/* Andes PMU irq number */
#define ANDES_RV_IRQ_PMOVI      18
#define ANDES_RV_IRQ_LAST       ANDES_RV_IRQ_PMOVI
#define ANDES_SLI_CAUSE_BASE    256

/* Andes PMU related registers */
#define ANDES_CSR_SLIE          0x9c4
#define ANDES_CSR_SLIP          0x9c5
#define ANDES_CSR_SCOUNTEROF    0x9d4

#endif /* __PIC_RISCV_INTC_ANDES_H__ */
