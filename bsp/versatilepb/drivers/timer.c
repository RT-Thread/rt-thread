/* arm timer
 * Marcos Medeiros
 */
#include <rtthread.h>
#include "interrupt.h"
#include "rthw.h"

#define TIMER_IRQ_NUM	5
#define TICKHZ			1000
#define __clk			1000000
#define __iobase		0x101e3000

enum TimerRegisters {
	T1_LOAD		 = 0x00,
	T1_VALUE	 = 0x04,
	T1_CTRL		 = 0x08,
	T1_INTCTRL	 = 0x0c,
	T1_RIS		 = 0x10,
	T1_MIS		 = 0x14,
	T1_BGLOAD	 = 0x18,
	T2_LOAD		 = 0x20,
	T2_VALUE	 = 0x24,
	T2_CTRL		 = 0x28,
	T2_INTCTRL	 = 0x2c,
	T2_RIS		 = 0x30,
	T2_MIS		 = 0x34,
	T2_BGLOAD	 = 0x38,
};

static void timer_irq_handler(int vector, void* param)
{
	writel(__iobase + T1_INTCTRL, 0);
	rt_tick_increase();
}

void rt_hw_timer_init(void)
{
	/* We need to disable timer before writing new values */
	writel(__iobase + T1_CTRL, 0);
	/* Setup timer1 in periodic mode */
	writel(__iobase + T1_BGLOAD, 0);
	writel(__iobase + T1_LOAD, (__clk / TICKHZ) * 10);
	/* enable timer, configure as Periodic, div1, interrupt enable */
	writel(__iobase + T1_CTRL, 0xe2);

	rt_hw_interrupt_install(TIMER_IRQ_NUM, timer_irq_handler, RT_NULL, "timer");
	/* enable interrupt line */
	rt_hw_interrupt_unmask(TIMER_IRQ_NUM);
}

void rt_hw_timer_stop(void)
{
	writel(__iobase + T1_CTRL, 0);
	rt_hw_interrupt_unmask(TIMER_IRQ_NUM);
}
