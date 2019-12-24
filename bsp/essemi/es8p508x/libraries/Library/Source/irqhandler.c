#include "irqhandler.h"

void NMI_IRQHandler(void)
{

}

void HardFault_IRQHandler(void)
{
    while(1)
    {
    }
}

void SVC_IRQHandler(void)
{

}

void PendSV_IRQHandler(void)
{

}
void SysTick_Handler(void)
{
    systick_irq_cbk();
}
