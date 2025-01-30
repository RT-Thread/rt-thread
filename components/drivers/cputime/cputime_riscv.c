/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-11-23     Guozhanxin        first version
 * 2023-04-12     xqyjlj            fix cpu timer in multithreading
 * 2025-01-30     wumingzi          add doxygen comment
 */

#include <rthw.h>
#include <rtdevice.h>
#include <rtthread.h>

#include <board.h>

/**
 * @addtogroup  Drivers                 RTTHREAD Driver
 * @defgroup    cputimer                cputimer
 * @brief       cputimer driver api
 * @ingroup     Drivers
 * @addtogroup  cputimer
 * @{
 */

/**
 * @brief   Get nanoseconds per tick
 *
 * @return  the number of nanoseconds per tick multiplied by 1 000 000
 */
static uint64_t riscv_cputime_getres(void)
{
    uint64_t ret = 1000UL * 1000 * 1000;

    ret = (ret * (1000UL * 1000)) / CPUTIME_TIMER_FREQ;
    return ret;
}

/**
 * @brief   Read time counter
 *
 * @return  value of ticks
 */
static uint64_t riscv_cputime_gettime(void)
{
    uint64_t time_elapsed;
    __asm__ __volatile__(
        "rdtime %0"
        : "=r"(time_elapsed));
    return time_elapsed;
}

const static struct rt_clock_cputime_ops _riscv_ops =
{
    riscv_cputime_getres,
    riscv_cputime_gettime
};

/**
 * @brief   Init cputimer operation of riscv architecture
 *
 * @return  return 0 forever
 */
int riscv_cputime_init(void)
{
    clock_cpu_setops(&_riscv_ops);
    return 0;
}
INIT_BOARD_EXPORT(riscv_cputime_init);

/*! @}*/