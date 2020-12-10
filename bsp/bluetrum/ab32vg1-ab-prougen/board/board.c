/*
 * Copyright (c) 2006-2020, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-11-18     greedyhao         first version
 */

#include <rthw.h>
#include "board.h"

int rt_hw_usart_init(void);
void my_printf(const char *format, ...);
void timer0_cfg(uint32_t ticks);
void rt_soft_isr(int vector, void *param);
void cpu_irq_comm(void);
void set_cpu_irq_comm(void (*irq_hook)(void));
extern uint32_t __aram_start, __eram_end;

void hal_printf(const char *format, ...)
{
    va_list param;
    va_start(param, format);
    rt_kprintf(format, param);
    va_end(param);
}

void timer0_isr(int vector, void *param)
{
    rt_interrupt_enter();
    TMR0CPND = BIT(9);
    rt_tick_increase();
    rt_interrupt_leave();
}

void timer0_init(void)
{
	TMR0CON =  BIT(7); //TIE
	TMR0CNT = 0;

	rt_hw_interrupt_install(IRQ_TMR0_VECTOR, timer0_isr, RT_NULL, "tick");
}

void timer0_cfg(uint32_t ticks)
{
	TMR0PR  = (uint32_t)(ticks - 1UL);       //1ms interrupt
	TMR0CON |= BIT(0); // EN
}

void hal_mdelay(uint32_t ms)
{
    rt_thread_mdelay(ms);
}

void rt_hw_systick_init(void)
{
    CLKCON2 &= 0x00ffffff;
    CLKCON2 |= (25 << 24);                                  //配置x26m_div_clk = 1M (timer, ir, fmam ...用到)
    CLKCON0 &= ~(7 << 23);
    CLKCON0 |= BIT(24);                                     //tmr_inc select x26m_div_clk = 1M

    set_sysclk(SYSCLK_48M);

    /* Setting software interrupt */
    set_cpu_irq_comm(cpu_irq_comm);
    rt_hw_interrupt_install(IRQ_SW_VECTOR, rt_soft_isr, RT_NULL, "sw_irq");

    timer0_init();
    hal_set_tick_hook(timer0_cfg);
    hal_set_ticks(get_sysclk_nhz()/RT_TICK_PER_SECOND);

    PICCON |= 0x10002;
}

void rt_hw_board_init(void)
{
    WDT_DIS();
    rt_hw_systick_init();

#ifdef RT_USING_HEAP
    rt_system_heap_init(&__aram_start, &__eram_end);
#endif

#ifdef RT_USING_PIN
    rt_hw_pin_init();
#endif // RT_USING_PIN

#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif // RT_USING_SERIAL

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif // RT_USING_CONSOLE

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
