/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-10-15     IronsideZhang     first version
 */

#ifndef IRQ_NUM_H__
#define IRQ_NUM_H__

/*
 * RISC-V PLIC interrupt numbers start from 1. IRQ 0 is reserved.
 * RT-Thread's interrupt framework has an offset, so we define raw hardware IRQ numbers here.
 */

#define K1_IRQ_UART0               (42)

/*
 * TODO-K1:
 * #define K1_IRQ_I2C0                (36)
 * #define K1_IRQ_SPI3                (55)
 * #define K1_IRQ_GPIO                (58)
 */

#endif // IRQ_NUM_H__