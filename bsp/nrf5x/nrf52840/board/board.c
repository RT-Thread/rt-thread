#include <rtthread.h>
#include <rthw.h>
#include <nrfx_systick.h>

#include "board.h"
#include "drv_uart.h"

void SysTick_Configuration(void)
{
    /* Set interrupt priority */
    NVIC_SetPriority(SysTick_IRQn, 0xf);
    
    /* Configure SysTick to interrupt at the requested rate. */   
    nrf_systick_load_set(SystemCoreClock / RT_TICK_PER_SECOND);
    nrf_systick_val_clear();
    nrf_systick_csr_set(NRF_SYSTICK_CSR_CLKSOURCE_CPU | NRF_SYSTICK_CSR_TICKINT_ENABLE
                        | NRF_SYSTICK_CSR_ENABLE);
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}



void rt_hw_board_init(void)
{
    // sd_power_dcdc_mode_set(NRF_POWER_DCDC_ENABLE);
    /* Activate deep sleep mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;


    SysTick_Configuration();
    
#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
    
#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

}

