#include <sunxi_hal_common.h>
#include <hal_hwspinlock.h>
#include <hal_clk.h>

#include "hwspinlock.h"

void hal_hwspinlock_init(void)
{
    /*
     * the clk and gate should init in kernel
     */

    /* hal_clock_enable(HAL_CLK_PERIPH_SPINLOCK); */
}

int hal_hwspinlock_check_taken(int num)
{
    return !!(readl(SPINLOCK_STATUS_REG) & (1 << num));
}

void hal_hwspinlock_get(int num)
{
    unsigned long addr = SPINLOCK_LOCK_REG(num);

    while (readl(addr) != 0);

}

void hal_hwspinlock_put(int num)
{
    unsigned long addr = SPINLOCK_LOCK_REG(num);

    writel(0, addr);
}
