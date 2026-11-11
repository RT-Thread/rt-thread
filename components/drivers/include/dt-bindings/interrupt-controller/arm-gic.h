/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DT_BINDINGS_INTERRUPT_CONTROLLER_ARM_GIC_H__
#define __DT_BINDINGS_INTERRUPT_CONTROLLER_ARM_GIC_H__

#include <dt-bindings/interrupt-controller/irq.h>

/* interrupt specifier cell 0 */

#define GIC_SPI 0
#define GIC_PPI 1

/*
 * Interrupt specifier cell 2.
 * The flags in irq.h are valid, plus those below.
 */
#define GIC_CPU_MASK_RAW(x) ((x) << 8)
#define GIC_CPU_MASK_SIMPLE(num) GIC_CPU_MASK_RAW((1 << (num)) - 1)

#endif /* __DT_BINDINGS_INTERRUPT_CONTROLLER_ARM_GIC_H__ */
