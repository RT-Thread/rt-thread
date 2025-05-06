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
    { 0x3C000000, 0x3C00E000 - 1,   0x3C000000, RW_NCNB },     /* 56K SRAM memory */
    { 0xBC000000, 0xBC00E000 - 1,   0xBC000000, RW_NCNB }      /* 56K Shadow memory */
};
#endif

/**
 * This function will initial M487 board.
 */
rt_weak void rt_hw_board_init(void)
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

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_HEAP
    /* Dump heap information */
    rt_kprintf("Heap: Begin@%08x, END@%08x, SIZE:%d\n", BOARD_HEAP_START, BOARD_HEAP_END, (rt_uint32_t)BOARD_HEAP_END - (rt_uint32_t)BOARD_HEAP_START);
#endif
}


void devmem(int argc, char *argv[])
{
    volatile unsigned int u32Addr;
    unsigned int value = 0, mode = 0;

    if (argc < 2 || argc > 3)
    {
        goto exit_devmem;
    }

    if (argc == 3)
    {
        if (rt_sscanf(argv[2], "0x%x", &value) != 1)
            goto exit_devmem;
        mode = 1; //Write
    }

    if (rt_sscanf(argv[1], "0x%x", &u32Addr) != 1)
        goto exit_devmem;
    else if (!u32Addr || u32Addr & (4 - 1))
        goto exit_devmem;

    if (mode)
    {
        *((volatile uint32_t *)u32Addr) = value;
    }
    rt_kprintf("0x%08x\n", *((volatile uint32_t *)u32Addr));

    return;
exit_devmem:
    rt_kprintf("Read: devmem <physical address in hex>\n");
    rt_kprintf("Write: devmem <physical address in hex> <value in hex format>\n");
    return;
}
MSH_CMD_EXPORT(devmem, dump device registers);
