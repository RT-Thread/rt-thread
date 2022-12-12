/*
 * ===========================================================================================
 *
 *       Filename:  hal_atomic.c
 *
 *    Description:  atomic impl. for hal layer.
 *
 *        Version:  Melis3.0
 *         Create:  2019-11-26 15:16:41
 *       Revision:  none
 *       Compiler:  GCC:version 7.2.1 20170904 (release),ARM/embedded-7-branch revision 255204
 *
 *         Author:  caozilong@allwinnertech.com
 *   Organization:  BU1-PSW
 *  Last Modified:  2020-04-02 17:10:48
 *
 * ===========================================================================================
 */

#include <hal_atomic.h>
#include <rthw.h>
#include <rtthread.h>

/* TODO: handle lock */
void hal_spin_lock(hal_spinlock_t *lock)
{
    rt_enter_critical();
    return;
}

/* TODO: handle lock */
void hal_spin_unlock(hal_spinlock_t *lock)
{
    rt_exit_critical();
    return;
}

/* TODO: handle lock */
uint32_t hal_spin_lock_irqsave(hal_spinlock_t *lock)
{
    uint32_t ret;
    // CPSR_ALLOC();

    // MELIS_CPU_CRITICAL_ENTER();
    rt_enter_critical();
    ret = rt_hw_interrupt_disable();

    return ret;
}

/* TODO: handle lock */
void hal_spin_unlock_irqrestore(hal_spinlock_t *lock, uint32_t __cpsr)
{
    rt_hw_interrupt_enable(__cpsr);
    rt_exit_critical();

    // MELIS_CPU_CRITICAL_LEAVE();
}
