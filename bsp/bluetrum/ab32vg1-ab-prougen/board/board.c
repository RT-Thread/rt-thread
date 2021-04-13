/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
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
void my_print_r(const void *buf, uint16_t cnt);
void timer0_cfg(uint32_t ticks);
void rt_soft_isr(int vector, void *param);
void cpu_irq_comm(void);
void set_cpu_irq_comm(void (*irq_hook)(void));
void load_cache();
void sys_error_hook(uint8_t err_no);

typedef void (*os_cache_setfunc_func)(void *load_cache_func, void *io_read);
typedef void (*spiflash_init_func)(uint8_t sf_read, uint8_t dummy);

#define os_cache_setfunc        ((os_cache_setfunc_func) 0x84024)

static struct rt_mutex mutex_spiflash = {0};
extern volatile rt_uint8_t rt_interrupt_nest;
extern uint32_t __heap_start, __heap_end;

void hal_printf(const char *fmt, ...)
{
    rt_device_t console = rt_console_get_device();

    va_list args;
    rt_size_t length;
    static char rt_log_buf[RT_CONSOLEBUF_SIZE];

    va_start(args, fmt);
    /* the return value of vsnprintf is the number of bytes that would be
     * written to buffer had if the size of the buffer been sufficiently
     * large excluding the terminating null byte. If the output string
     * would be larger than the rt_log_buf, we have to adjust the output
     * length. */
    length = rt_vsnprintf(rt_log_buf, sizeof(rt_log_buf) - 1, fmt, args);
    if (length > RT_CONSOLEBUF_SIZE - 1)
        length = RT_CONSOLEBUF_SIZE - 1;
#ifdef RT_USING_DEVICE
    if (console == RT_NULL)
    {
        rt_hw_console_output(rt_log_buf);
    }
    else
    {
        rt_uint16_t old_flag = console->open_flag;

        console->open_flag |= RT_DEVICE_FLAG_STREAM;
        rt_device_write(console, 0, rt_log_buf, length);
        console->open_flag = old_flag;
    }
#else
    rt_hw_console_output(rt_log_buf);
#endif
    va_end(args);
}

RT_SECTION(".irq.timer")
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
    rt_system_heap_init(&__heap_start, &__heap_end);
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

void rt_hw_us_delay(rt_uint32_t us)
{

}

RT_SECTION(".irq.cache")
void cache_init(void)
{
    os_cache_setfunc(load_cache, NULL);
    rt_mutex_init(&mutex_spiflash, "flash_mutex", RT_IPC_FLAG_FIFO);
}

RT_SECTION(".irq.cache")
void os_spiflash_lock(void)
{
    // if (rt_thread_self()->stat == RT_THREAD_RUNNING) {
    if ((rt_thread_self() != RT_NULL) && (rt_interrupt_nest == 0)) {
        rt_mutex_take(&mutex_spiflash, RT_WAITING_FOREVER);
    }
}

RT_SECTION(".irq.cache")
void os_spiflash_unlock(void)
{
    // if (rt_thread_self()->stat == RT_THREAD_RUNNING) {
    if ((rt_thread_self() != RT_NULL) && (rt_interrupt_nest == 0)) {
        rt_mutex_release(&mutex_spiflash);
    }
}

RT_SECTION(".irq.err.str")
static const char stack_info[] = "thread sp=0x%x name=%s";

void rt_hw_console_output(const char *str)
{
    my_printf(str);
}

/**
 * @brief print exception error
 * @note Every message needed to print, must put in .comm exction.
 */
RT_SECTION(".irq.err")
void exception_isr(void)
{
    extern long list_thread(void);
    sys_error_hook(1);

    rt_console_set_device(RT_NULL);
    rt_kprintf(stack_info, rt_thread_self()->sp, rt_thread_self()->name);

    while(1);
}
