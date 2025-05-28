#include <rthw.h>
#include <rtdevice.h>
#include <rtthread.h>

#include <board.h>
#include <riscv_timer.h>

/* Use Cycle counter of Data Watchpoint and Trace Register for CPU time */

static uint64_t riscv_cputime_getres(void)
{
    uint64_t ret = 1000UL * 1000 * 1000;

    ret = (ret * (1000UL * 1000)) / riscv_timer_get_frequency();
    return ret;
}

static uint64_t riscv_cputime_gettime(void)
{
    return riscv_timer_rdtime();
}

const static struct rt_clock_cputime_ops _riscv_ops =
{
    riscv_cputime_getres,
    riscv_cputime_gettime
};

int riscv_cputime_init(void)
{
    clock_cpu_setops(&_riscv_ops);
    return 0;
}
INIT_BOARD_EXPORT(riscv_cputime_init);
