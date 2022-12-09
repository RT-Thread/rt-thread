/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/01     Bernard      The first version
 */

#include <rthw.h>
#include <stdint.h>
#include <rtthread.h>
<<<<<<< HEAD
//#include <board.h>
//#include <RV32M1_ri5cy.h>
=======
>>>>>>> 1185482745fa76c9094f8cf9227f85d55ed8e2bd

typedef void (*irq_handler_t)(void);
extern const irq_handler_t isr_table[];

<<<<<<< HEAD

=======
>>>>>>> 1185482745fa76c9094f8cf9227f85d55ed8e2bd
extern void vSystemIrqHandler(uint32_t mcause);
