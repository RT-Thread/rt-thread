#include "config.h"

void sw0_isr(void *args)
{
    rt_kprintf("sw_0 is trigger \r\n");
    rt_thread_mdelay(400);
}

void sw1_isr(void *args)
{
    rt_kprintf("sw_1 is trigger \r\n");
    rt_thread_mdelay(400);
}
/* hardware initialization */
void boardInit(void)
{
    /* disable watchdog timer */
    SYSREG->WDOG_CR = 0;
}
INIT_BOARD_EXPORT(boardInit);

/* custom finish command */
extern uint32_t SystemCoreClock;
void sayHello(void)
{
     rt_kprintf("Hello RT-Thread! By Microsemi SmartFusion2 Family FPGA-M2S010.\r\n");
     rt_kprintf("MSS System Core Clock: %d Hz.\r\n", SystemCoreClock);
}
MSH_CMD_EXPORT(sayHello, "say hello to console");
