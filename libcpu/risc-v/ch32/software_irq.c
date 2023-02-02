#include "ch32v30x.h"
void rt_trigger_software_interrupt(void)
{
    SysTick->CTLR |= (1<<31);
}

void rt_hw_do_after_save_above(void)
{
    SysTick->CTLR &= ~(1<<31);
}