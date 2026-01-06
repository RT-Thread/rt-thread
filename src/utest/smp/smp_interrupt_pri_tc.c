/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-10     RV           the first version
 */

#include <rtthread.h>
#include "utest.h"
#include <interrupt.h>

/**
 * @brief   Setting the Interrupt Priority Test.
 *
 * @note    Without turning off interrupts, interrupts respond in the order in which they are triggered.
 *          With interrupts turned off, low and high priority interrupts are triggered sequentially,
 *          and when interrupts are turned on, high priority interrupts respond first.
 *
 * Test Case Name: [smp_interrupt_pri_tc]
 *
 * Test Objectives:
 * - Test the correctness of the interrupt triggering order under two scenarios. Scenario 1: When interrupts
 * - are not masked, the interrupt handling order shall depend on the triggering sequence. Scenario 2: When
 * - interrupts are first masked, triggered, and then enabled, the interrupt handling order shall depend on
 * - the interrupt priority.
 *
 * Test Scenarios:
 * - First, two interrupts are registered, namely the low-priority interrupt RT_SPI_1 and the high-priority
 * - interrupt RT_SPI_2.
 * - Scenario 1 (int_pri1_tc, mode=0): RT_SPI_1 and RT_SPI_2 are triggered sequentially without interrupt masking.
 * - At this point, the interrupt service routine (ISR) of RT_SPI_1 executes first to set ipi_val[0] = SET_VAL;
 * - since the RT_SPI_2 interrupt has not been triggered yet, ipi_val[1] remains at the initial value RES_VAL,
 * - making the judgment ipi_val[0] > ipi_val[1] hold true. When the RT_SPI_2 interrupt is triggered, both ipi_val[0]
 * - and ipi_val[1] are reset to the initial value RES_VAL.
 * - Scenario 2 (int_pri2_tc, mode=1): RT_SPI_1 and RT_SPI_2 are triggered under interrupt masking, and the interrupt
 * - mask is lifted afterward. In this case, the interrupts are handled in the order of their priorities: the RT_SPI_2
 * - interrupt is triggered first, followed by the RT_SPI_1 interrupt. At this point, the ISR of RT_SPI_2 first sets
 * - ipi_val[1] = SET_VAL, and the judgment that ipi_val[1] is greater than ipi_val[0] (which remains RES_VAL) is
 * - successfully validated. Subsequently, the ISR of RT_SPI_1 resets both ipi_val[0] and ipi_val[1] to the initial
 * - value RES_VAL.
 *
 * Verification Metrics:
 * - Output message: [ PASSED ] [ result ] testcase (core.smp_interrupt_pri_tc)
 *
 * Dependencies:
 * - RT_USING_SMP needs to be enabled.
 *
 * Expected Results:
 * - You will see the pass information of int_pri1_tc and int_pri2_tc, as well as the PASS message of smp_interrupt_pri_tc.
 */

#define RES_VAL         0X0
#define SET_VAL         0XA
#define RT_SPI_1        1
#define RT_SPI_2        2
#define RT_SPI_PRI_HIGH 120
#define RT_SPI_PRI_LOW  140

static int mode       = 0;
static int ipi_val[2] = {0, 0};

/* Software Interrupt 1 Service Functions */
static void rt_scheduler_ipi1_handler(int vector, void *param)
{
    ipi_val[0] = SET_VAL;
    if (mode == 0)
    {
        uassert_true(ipi_val[0] > ipi_val[1]);
    }
    else
    {
        ipi_val[0] = RES_VAL;
        ipi_val[1] = RES_VAL;
    }
}

/* Software Interrupt 2 Service Functions */
static void rt_scheduler_ipi2_handler(int vector, void *param)
{
    ipi_val[1] = SET_VAL;
    if (mode == 0)
    {
        ipi_val[0] = RES_VAL;
        ipi_val[1] = RES_VAL;
    }
    else
    {
        uassert_true(ipi_val[0] < ipi_val[1]);
    }
}

/* Interrupt priority testcases 1 */
static void int_pri1_tc(void)
{
    mode = 0;
    unsigned int pri1, pri2;
    pri1 = rt_hw_interrupt_get_priority(RT_SPI_1);
    pri2 = rt_hw_interrupt_get_priority(RT_SPI_2);

    if (pri1 < pri2)
        uassert_true(pri1 < pri2);

    /* Trigger interrupt */
    rt_hw_ipi_send(RT_SPI_1, 0x1);
    rt_hw_ipi_send(RT_SPI_2, 0x1);
    rt_thread_delay(5);
}

/* Interrupt priority testcases 2 */
static void int_pri2_tc(void)
{
    mode = 1;
    unsigned int pri1, pri2;
    pri1 = rt_hw_interrupt_get_priority(RT_SPI_1);
    pri2 = rt_hw_interrupt_get_priority(RT_SPI_2);

    if (pri1 < pri2)
        uassert_true(pri1 < pri2);

    rt_base_t level = rt_hw_local_irq_disable();
    /* Trigger interrupt */
    rt_hw_ipi_send(RT_SPI_1, 0x1);
    rt_hw_ipi_send(RT_SPI_2, 0x1);
    rt_hw_local_irq_enable(level);
    rt_thread_delay(5);
}

static rt_err_t utest_tc_init(void)
{
    /* Setting the priority of software interrupts */
    rt_hw_interrupt_set_priority(RT_SPI_1, RT_SPI_PRI_LOW);
    rt_hw_interrupt_set_priority(RT_SPI_2, RT_SPI_PRI_HIGH);
    /* Register software interrupt service functions */
    rt_hw_ipi_handler_install(RT_SPI_1, rt_scheduler_ipi1_handler);
    rt_hw_ipi_handler_install(RT_SPI_2, rt_scheduler_ipi2_handler);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(int_pri1_tc);
    UTEST_UNIT_RUN(int_pri2_tc);
}
UTEST_TC_EXPORT(testcase, "core.smp_interrupt_pri_tc", utest_tc_init, utest_tc_cleanup, 10);
