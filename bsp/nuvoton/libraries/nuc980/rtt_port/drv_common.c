/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-11-11      Wayne            First version
*
******************************************************************************/

#include <rtthread.h>
#include <rthw.h>
#include "board.h"
#include "drv_uart.h"
#include "drv_sys.h"

#if defined(BSP_USING_MMU)
static struct mem_desc hw_mem_desc[] =
{
    { 0x00000000, 0xFFFFFFFF,     0x00000000, RW_NCNB },     /* None cached for 4G memory */
    { 0x00000000, BOARD_SDRAM_SIZE - 1,   0x00000000, RW_CB   }, /* 64M cached DDR memory */
    { BIT31, (BIT31 | BOARD_SDRAM_SIZE) - 1,   BIT31, RW_NCNB }, /* Shadow DDR Map */
    { 0x3C000000, 0x3C004000 - 1,   0x3C000000, RW_NCNB },     /* 16K SRAM memory */
    { 0xBC000000, 0xBC004000 - 1,   0xBC000000, RW_NCNB }      /* 16K Shadow memory */
};
#endif

/**
 * This function will initial M487 board.
 */
RT_WEAK void rt_hw_board_init(void)
{
    /* initialize base clock */
    nu_clock_base_init();

    /* initialize peripheral pin function */
    nu_pin_init();

#if defined(BSP_USING_MMU)
    /* initialize mmu */
    rt_hw_mmu_init(&hw_mem_desc[0], sizeof(hw_mem_desc) / sizeof(hw_mem_desc[0]));
#else
    /* disable I/D cache */
    mmu_disable_dcache();
    mmu_disable_icache();
    mmu_disable();
    mmu_invalidate_tlb();
#endif

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize systick */
    rt_hw_systick_init();

#ifdef RT_USING_HEAP
    /* init memory system */
    rt_system_heap_init((void *)BOARD_HEAP_START, (void *)BOARD_HEAP_END);
#endif

    /* initialize uart */
    rt_hw_uart_init();

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
