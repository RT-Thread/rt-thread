/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#ifndef __ARMV7_H__
#define __ARMV7_H__

/*
 * CPSR
 * [ref]DDI0406C_d_armv7ar_arm.pdf: B1.3.3 Program Status Registers (PSRs)
 *      Format of the CPSR and SPSRs
 *      Bit     Field       Description
 *      24      J           Jazelle bit
 *      9       E           Endianness execution state bit
 *      8       A           Asynchronous abort mask bit
 *      7       I           IRQ mask bit
 *      6       F           FIQ mask bit
 *      5       T           Thumb execution state bit
 *      4-0     M[4:0]      0b10000(0x10) = User
 *                          0b10001(0x11) = FIQ
 *                          0b10010(0x12) = IRQ
 *                          0b10011(0x13) = Supervisor
 *                          0b10110(0x16) = Monitor
 *                          0b10111(0x17) = Abort
 *                          0b11010(0x1A) = Hyp
 *                          0b11011(0x1B) = Undefined
 *                          0b11111(0x1F) = System
 */
#define J_Bit           (1 << 24)
#define E_Bit           (1 << 9)
#define A_Bit           (1 << 8)
#define I_Bit           (1 << 7)
#define F_Bit           (1 << 6)
#define T_Bit           (1 << 5)
#define Mode_USR		0x10
#define Mode_FIQ		0x11
#define Mode_IRQ		0x12
#define Mode_SVC		0x13
#define Mode_MON		0x16
#define Mode_ABT		0x17
#define Mode_UND		0x1B
#define Mode_SYS		0x1F
#define Mode_MASK		0x1F

#endif
