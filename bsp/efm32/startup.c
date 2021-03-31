/***************************************************************************//**
 * @file    startup.c
 * @brief   This file is part of RT-Thread RTOS
 *  COPYRIGHT (C) 2012, RT-Thread Development Team
 * @author  Bernard, onelife
 * @version 1.0
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 * LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date         Author      Notes
 * 2006-08-31   Bernard     first implementation
 * 2010-12-29   onelife     Modify for EFM32
 * 2011-12-20   onelife     Add RTGUI initialization routine
 * 2012-02-21   onelife     Add energy management initialization routine
 * 2012-05-15   onelife     Modified to compatible with CMSIS v3
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#elif __ICCARM__
#pragma section="HEAP"
#else
extern int __bss_end__;
#endif

/* Private variables ---------------------------------------------------------*/
/* External function prototypes ----------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#ifdef RT_DEBUG
/***************************************************************************//**
 * @brief
 *  Reports the name of the source file and the source line number where the
 *  assert error has occurred.
 *
 * @details
 *
 * @note
 *
 * @param[in] file
 *  Pointer to the source file name
 *
 * @param[in] line
 *  Assert error line source number
 ******************************************************************************/
void assert_failed(uint8_t * file, uint32_t line)
{
    rt_kprintf("\n\r Wrong parameter value detected on\r\n");
    rt_kprintf("       file  %s\r\n", file);
    rt_kprintf("       line  %d\r\n", line);

    while (1) ;
}
#endif

/***************************************************************************//**
 * @brief
 *  Startup RT-Thread
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
void rtthread_startup(void)
{
    /* init board */
    rt_hw_board_init();

#ifdef RT_USING_HEAP
    #ifdef __CC_ARM
    rt_system_heap_init((void*)&Image$$RW_IRAM1$$ZI$$Limit, (void*)EFM32_SRAM_END);
    #elif __ICCARM__
    rt_system_heap_init(__segment_end("HEAP"), (void*)EFM32_SRAM_END);
    #else
    /* init memory system */
    rt_system_heap_init((void*)&__bss_end__, (void*)EFM32_SRAM_END);
    #endif
#endif

    /* enable interrupt */
    rt_hw_interrupt_enable(0x0UL);

    /* init drivers */
    rt_hw_driver_init();

    /* show version */
    rt_show_version();

    /* init timer system */
    rt_system_timer_init();

    /* init scheduler system */
    rt_system_scheduler_init();

    /* init finsh */
#ifdef RT_USING_FINSH
    finsh_system_init();
    finsh_set_device(CONSOLE_DEVICE);
#endif

    /* Initialize gui server */
#ifdef RT_USING_RTGUI
    rtgui_system_server_init();
#endif

    /* init timer thread */
    rt_system_timer_thread_init();

    /* init idle thread */
    rt_thread_idle_init();

    /* init energy mode thread */
    efm32_emu_init();

    /* init application */
    rt_application_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return ;
}

/***************************************************************************//**
 * @brief
 *  Program entry point
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
int main(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* init system setting */
    SystemInit();

    /* startup RT-Thread RTOS */
    rtthread_startup();

    return 0;
}

/***************************************************************************//**
 * @}
 ******************************************************************************/
