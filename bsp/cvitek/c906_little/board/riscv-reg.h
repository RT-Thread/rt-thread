/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/01/11     flyingcys    The first version
 */
#ifndef RISCV_REG_H_
#define RISCV_REG_H_

#if __riscv_xlen == 32
#define REGSIZE     4
#define REGSHIFT    2
#define LOAD        lw
#define STOR        sw
#elif __riscv_xlen == 64
#define REGSIZE     8
#define REGSHIFT    3
#define LOAD        ld
#define STOR        sd
#endif /* __riscv_xlen */

#endif /* RISCV_REG_H_ */
