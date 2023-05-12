/*
 * Copyright (C) 2022 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-02-10     Lisq          the first version
 */

#include "board.h"

/**
 * @addtogroup es32
 */

/*@{*/

/*******************************************************************************
 * Function Name  : SystemClock_Configuration
 * Description    : Configures the System Clock.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void  SystemClock_Config(void)
{
    /* Configure system clock */
    ald_cmu_pll_config(ALD_CMU_PLL_INPUT_HOSC8M, ALD_CMU_PLL_OUTPUT_72M);
    ald_cmu_clock_config(ALD_CMU_CLOCK_PLL, 72000000);

    /* Enable all peripherals */
    ald_cmu_perh_clock_config(ALD_CMU_PERH_ALL, ENABLE);

    __enable_irq();
}

/*******************************************************************************
 * Function Name  : SysTick_Configuration
 * Description    : Configures the SysTick for OS tick.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void SysTick_Configuration(void)
{
    ald_cmu_init();
}

/**
 * This is the timer interrupt service routine.
 *
 */
void __attribute__((interrupt)) CLINT_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    csi_coret_clr(ald_cmu_get_clock() / RT_TICK_PER_SECOND, CLINT_IRQn);
    ald_inc_tick();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

void __attribute__((interrupt)) DMA_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    ald_dma_irq_handler();

    /* leave interrupt */
    rt_interrupt_leave();
}

/*@}*/
/**
 * This function will initial ES32F0 board.
 */
void rt_hw_board_init(void)
{
    csi_vic_set_prio(MACHINE_MODE_SOFT_IRQn, 0);
    csi_vic_enable_sirq(MACHINE_MODE_SOFT_IRQn);
    CLIC->CLICINT[MACHINE_MODE_SOFT_IRQn].ATTR |= (3);

    csi_vic_set_prio(DMA_IRQn, 4);
    csi_vic_enable_sirq(DMA_IRQn);

    csi_cpu_sleep_wfi(MEXSTATUS_SLEEP_DEEP);

    /*System Clock Configuration */
    SystemClock_Config();

    /* Configure the SysTick */
    SysTick_Configuration();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}

/**
 * This function will delay for some us.
 *
 * @param us the delay time of us
 */
void rt_hw_us_delay(rt_uint32_t us)
{
    unsigned int start, now, delta, reload, us_tick;
    start = CORET->MTIME;
    reload = CORET->MTIMECMP;
    us_tick = ald_cmu_get_clock() / 1000000UL;
    do
    {
        now = CORET->MTIME;
        delta = start > now ? start - now : reload + start - now;
    }
    while (delta <  us_tick * us);
}

void rt_trigger_software_interrupt(void)
{
    *((uint8_t*)0xE080100C) = 0x1;
}

void rt_hw_do_after_save_above(void)
{
}
