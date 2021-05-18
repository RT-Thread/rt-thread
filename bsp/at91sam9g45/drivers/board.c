/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 */

#include <rtthread.h>
#include <rthw.h>

#include "board.h"
#include <mmu.h>

/**
 * @addtogroup at91sam9g45
 */
/*@{*/
#if defined(__CC_ARM)
extern int Image$$ER_ZI$$ZI$$Limit;
#define HEAP_BEGIN  (&Image$$ER_ZI$$ZI$$Limit)
#elif (defined (__GNUC__))
extern unsigned char __bss_end;
#define HEAP_BEGIN  (&__bss_end)
#elif (defined (__ICCARM__))
#pragma section=".noinit"
#define HEAP_BEGIN  (__section_end(".noinit"))
#endif

#define HEAP_END    (((rt_uint32_t)HEAP_BEGIN & 0xF0000000) + 0x04000000)

extern void rt_hw_interrupt_init(void);
extern void rt_hw_clock_init(void);

extern void rt_hw_get_clock(void);
extern void rt_hw_set_dividor(rt_uint8_t hdivn, rt_uint8_t pdivn);
extern void rt_hw_set_clock(rt_uint8_t sdiv, rt_uint8_t pdiv, rt_uint8_t mdiv);
extern void rt_dbgu_isr(void);

#define SAM9G45_BLOCK_SIZE  0x10000000      // 256M
#define MMU_SECTION_SIZE    0x100000        // 1M
#define PERIPHERALS_ADDR            // 1M

#define SECTION_END(sa)     ((sa) + MMU_SECTION_SIZE - 1)   // sa: start address
#define BLOCK_END(ba)       ((ba) + SAM9G45_BLOCK_SIZE - 1) // ba: block address

static struct mem_desc at91_mem_desc[] = {  /* FIXME, hornby, to confirm MMU and memory */
      { 0x00000000,             0xFFFFFFFF , 0x00000000, RW_NCNB }, /* None cached for 4G memory */
    //{ 0x00000000, SECTION_END(0x00000000), 0x00000000, RW_CNB  }, /* TLB for ITCM, ITCM map to address zero, 32KB */
    //{ 0x00200000, SECTION_END(0x00200000), 0x00200000, RW_CNB  }, /* TLB for DTCM, 32KB */
    //{ 0x00300000, SECTION_END(0x00300000), 0x00300000, RW_CNB  }, /* TLB for internal RAM, 64KB, we use it as global variable area */
    //{ 0x00600000, SECTION_END(0x00600000), 0x00600000, RW_NCNB }, /* TLB for UDPHS(DMA) */
    //{ 0x00700000, SECTION_END(0x00700000), 0x00700000, RW_NCNB }, /* TLB for UHP OHCI */
    //{ 0x00800000, SECTION_END(0x00800000), 0x00800000, RW_NCNB }, /* TLB for UHP EHCI */
    //{ 0x30000000, 0x30000000+0x00100000-1, 0x30000000, RW_CB   }, /* 1M external SRAM for program code and stack */
    //{ 0x40000000,   BLOCK_END(0x40000000), 0x40000000, RW_NCNB }, /* 256M for nand-flash controller */
    //{ 0x60000000,   BLOCK_END(0x60000000), 0x60000000, RW_NCNB }, /* 256M for FPGA */
    //{ 0x70000000, 0x70000000+0x08000000-1, 0x70000000, RW_NCNB }, /* 128M for main DDR-SDRAM for print data */
      { 0x00000000, SECTION_END(0x00000000), 0x70000000, RW_CB   }, /* isr */
      { 0x70000000, 0x70000000+0x08000000-1, 0x70000000, RW_CB   }, /* 128M for main DDR-SDRAM for print data */
    //{ 0xFFF00000, SECTION_END(0xFFF00000), 0xFFF00000, RW_NCNB }, /* Internal Peripherals, 1MB */
};


#define PIT_CPIV(x)     ((x) & AT91C_PITC_CPIV)
#define PIT_PICNT(x)    (((x) & AT91C_PITC_PICNT) >> 20)

static rt_uint32_t pit_cycle;   /* write-once */
static rt_uint32_t pit_cnt;     /* access only w/system irq blocked */

/**
 * This function will handle rtos timer
 */
void rt_timer_handler(int vector, void *param)
{
#ifdef RT_USING_DBGU
    if (readl(AT91C_DBGU_CSR) & AT91C_US_RXRDY)
    {
        rt_dbgu_isr();
    }
#endif
    if (readl(AT91C_PITC_PISR) & AT91C_PITC_PITS)
    {
        unsigned nr_ticks;

        /* Get number of ticks performed before irq, and ack it */
        nr_ticks = PIT_PICNT(readl(AT91C_PITC_PIVR));
        while (nr_ticks--)
            rt_tick_increase();
    }
}

static void at91sam9g45_pit_reset(void)
{
    /* Disable timer and irqs */
    AT91C_BASE_PITC->PITC_PIMR = 0;

    /* Clear any pending interrupts, wait for PIT to stop counting */
    while (PIT_CPIV(readl(AT91C_PITC_PIVR)) != 0)
        ;

    /* Start PIT but don't enable IRQ */
    //AT91C_BASE_PITC->PITC_PIMR = (pit_cycle - 1) | AT91C_PITC_PITEN;
    pit_cnt += pit_cycle * PIT_PICNT(readl(AT91C_PITC_PIVR));
    AT91C_BASE_PITC->PITC_PIMR =
            (pit_cycle - 1) | AT91C_PITC_PITEN | AT91C_PITC_PITIEN;
    rt_kprintf("PIT_MR=0x%08x\n", readl(AT91C_PITC_PIMR));
}

/*
 * Set up both clocksource and clockevent support.
 */
static void at91sam9g45_pit_init(void)
{
    rt_uint32_t pit_rate;
    //rt_uint32_t   bits;

    /*
     * Use our actual MCK to figure out how many MCK/16 ticks per
     * 1/HZ period (instead of a compile-time constant LATCH).
     */
    pit_rate = clk_get_rate(clk_get("mck")) / 16;
    rt_kprintf("pit_rate=%dHZ\n", pit_rate);
    pit_cycle = (pit_rate + RT_TICK_PER_SECOND/2) / RT_TICK_PER_SECOND;

    /* Initialize and enable the timer */
    at91sam9g45_pit_reset();
}

/**
 * This function will init pit for system ticks
 */
void rt_hw_timer_init()
{
    at91sam9g45_pit_init();

    /* install interrupt handler */
    rt_hw_interrupt_install(AT91C_ID_SYS, rt_timer_handler,
                            RT_NULL, "system");
    rt_hw_interrupt_umask(AT91C_ID_SYS);
}

void at91_tc1_init()
{
    AT91C_BASE_PMC->PMC_PCER = 1<<AT91C_ID_TC;
    writel(AT91C_TCB_TC0XC0S_NONE | AT91C_TCB_TC1XC1S_NONE | AT91C_TCB_TC2XC2S_NONE, AT91C_TCB0_BMR);
    writel(AT91C_TC_CLKDIS, AT91C_TC0_CCR);
    writel(AT91C_TC_CLKS_TIMER_DIV4_CLOCK, AT91C_TC0_CMR);
    writel(0xffff, AT91C_TC0_CV);
}

#define BPS         115200  /* serial console port baudrate */

static void at91_usart_putc(char c)
{
    while (!(AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_TXRDY))
        ;
    AT91C_BASE_DBGU->DBGU_THR = c;
}

/**
 * This function is used to display a string on console, normally, it's
 * invoked by rt_kprintf
 *
 * @param str the displayed string
 */
void rt_hw_console_output(const char* str)
{
    while (*str)
    {
        if (*str=='\n')
        {
            at91_usart_putc('\r');
        }

        at91_usart_putc(*str++);
    }
}

static void rt_hw_console_init(void)
{
    int div;
    int mode = 0;

    AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RSTTX | AT91C_US_RSTRX |
           AT91C_US_RXDIS | AT91C_US_TXDIS;
    mode |= AT91C_US_USMODE_NORMAL | AT91C_US_CLKS_CLOCK |
           AT91C_US_CHMODE_NORMAL;
    mode |= AT91C_US_CHRL_8_BITS;
    mode |= AT91C_US_NBSTOP_1_BIT;
    mode |= AT91C_US_PAR_NONE;
    AT91C_BASE_DBGU->DBGU_MR = mode;
    div = (clk_get_rate(clk_get("mck")) / 16 + BPS/2) / BPS;
    AT91C_BASE_DBGU->DBGU_BRGR = div;
    AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RXEN | AT91C_US_TXEN;
}


/**
 * This function will init at91sam9g45 board
 */
void rt_hw_board_init()
{
    /* initialize the system clock */
    rt_hw_clock_init();

    /* initialize console */
    rt_hw_console_init();

    /* initialize mmu */
    rt_hw_mmu_init(at91_mem_desc, sizeof(at91_mem_desc)/sizeof(at91_mem_desc[0]));

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize early device */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    /* initialize timer0 */
    rt_hw_timer_init();

/* initialize board */
#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
}

/*@}*/
