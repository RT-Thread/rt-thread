
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include "cy_device_headers.h"
#include "board.h"
#include "uart.h"
#include "cy_systick.h"
#include "cycfg.h"

#define configTOTAL_HEAP_SIZE           (24*1024)
/* Allocate the memory for the heap. */
rt_align(RT_ALIGN_SIZE)
static uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler_CB(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}


void rt_hw_board_init()
{
    /* init systick */
    init_cycfg_all();

    SystemCoreClockUpdate();

    Cy_SysTick_Init(CY_SYSTICK_CLOCK_SOURCE_CLK_CPU, SystemCoreClock/RT_TICK_PER_SECOND);
    Cy_SysTick_SetCallback(0, SysTick_Handler_CB);
    Cy_SysTick_EnableInterrupt();

    rt_system_heap_init((void*)ucHeap, (void*)(ucHeap+configTOTAL_HEAP_SIZE));
    /* initialize UART device */
    rt_hw_uart_init();

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}

/*@}*/
