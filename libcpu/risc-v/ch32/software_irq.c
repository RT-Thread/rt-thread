#include "ch32v30x.h"
void rt_trigger_software_interrupt(void)
{
    SysTick->CTLR |= (1<<31);
}

__attribute__((naked)) void rt_hw_do_before_save_above(void)
{
    __asm volatile ("li t0, %0" : : "i" (0x20) );
    __asm volatile ("csrs 0x804," "t0");
}

void rt_hw_do_after_save_above(void)
{
    SysTick->CTLR &= ~(1<<31);
}