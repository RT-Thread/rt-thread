#include <rtthread.h>
#include <rthw.h>
#include <platform.h>
#include <encoding.h>
#include "interrupt.h"
extern struct rt_irq_desc irq_desc[];
extern rt_uint32_t rt_hw_interrupt_get_active(rt_uint32_t fiq_irq);
void rt_hw_trap_irq()
{
    rt_isr_handler_t isr_func;
    rt_uint32_t irq;
    void *param;

    /* get irq number */
    irq = rt_hw_interrupt_get_active(0);

    /* get interrupt service routine */
    isr_func = irq_desc[irq].handler;
    param = irq_desc[irq].param;

    /* turn to interrupt service routine */
    isr_func(irq, param);
    rt_hw_interrupt_ack(0, irq);

#ifdef RT_USING_INTERRUPT_INFO
    irq_desc[irq].counter ++;
#endif
}
void handle_m_ext_interrupt()
{
}
void rt_systick_handler(void)
{
    clear_csr(mie, MIP_MTIP);

    // Reset the timer for 3s in the future.
    // This also clears the existing timer interrupt.

    volatile uint64_t * mtime       = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
    uint64_t now = *mtime;
    uint64_t then = now + 2 * RTC_FREQ/RT_TICK_PER_SECOND;
    *mtimecmp = then;
    rt_tick_increase();

    // read the current value of the LEDS and invert them.
/*
    GPIO_REG(GPIO_OUTPUT_VAL) ^= ((0x1 << RED_LED_OFFSET)   |
		    (0x1 << GREEN_LED_OFFSET) |
		    (0x1 << BLUE_LED_OFFSET));
		    */

    // Re-enable the timer interrupt.
    set_csr(mie, MIP_MTIP);
}
