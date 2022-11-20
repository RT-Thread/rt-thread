/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-07-19      Wayne            First version
*
******************************************************************************/

#include <rthw.h>
#include "interrupt.h"

#define NVIC_INT_OFFSET          (16)
#define SYS_MAX_INT_SOURCE       (IRQn_Max)

static struct rt_irq_desc irq_desc[SYS_MAX_INT_SOURCE] = {0};

void rt_hw_interrupt_dummy_handler(int vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occurred!!!\n", vector);

    RT_ASSERT(0);
}

static uint32_t rt_hw_interrupt_current_irq(void)
{
    return ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) >> SCB_ICSR_VECTACTIVE_Pos);
}

void ISR_Trapper(void)
{
    int irq;

    /* Enter interrupt */
    rt_interrupt_enter();

    /* Get irq number */
    irq = rt_hw_interrupt_current_irq();
    if (irq >= SYS_MAX_INT_SOURCE)
    {
        rt_kprintf("Over interrupt range - %d!!!\n", irq);
        goto exit_rt_interrupt_trap;
    }
    else if (irq_desc[irq].handler == RT_NULL)
    {
        rt_kprintf("Unhandled interrupt %d occurred!!!\n", irq);
        goto exit_rt_interrupt_trap;
    }
    else
    {
        void *param;
        rt_isr_handler_t isr_func;

        /* get interrupt service routine */
        isr_func = irq_desc[irq].handler;
        param = irq_desc[irq].param;

        /* turn to interrupt service routine */
        isr_func(irq, param);
    }

#ifdef RT_USING_INTERRUPT_INFO
    irq_desc[irq].counter ++;
#endif

exit_rt_interrupt_trap:

    /* Enter interrupt */
    rt_interrupt_leave();
}

void rt_hw_interrupt_init(void)
{
    int i;
    vu32 *vpu32Vector;

    /* Enter interrupt */
    rt_interrupt_enter();

    /* Replace user-handler in RAM to ISR_Trapper */
    vpu32Vector = (vu32 *)SCB->VTOR;
    for (i = NVIC_INT_OFFSET; i < IRQn_Max; i++)
    {
        vpu32Vector[i] = (uint32_t)ISR_Trapper;
    }

    /* Initial all interrupt handler */
    for (i = 0; i < SYS_MAX_INT_SOURCE; i++)
    {
        rt_hw_interrupt_install(i, RT_NULL, RT_NULL, (char *)"dummy");
        rt_hw_interrupt_mask(i);
    }

    NVIC_SetPriorityGrouping(7);

    /* Enter interrupt */
    rt_interrupt_leave();
}

rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler, void *param, const char *name)
{
    rt_isr_handler_t    old_handler = RT_NULL;

    if (vector > SYS_MAX_INT_SOURCE)
        return RT_NULL;

    /* Set default priority IRQ_LEVEL_7 */
    //rt_hw_interrupt_set_priority(vector, IRQ_LEVEL_7);

    old_handler = irq_desc[vector + NVIC_INT_OFFSET].handler;
    if (handler != RT_NULL)
    {
        irq_desc[vector + NVIC_INT_OFFSET].handler = (rt_isr_handler_t)handler;
        irq_desc[vector + NVIC_INT_OFFSET].param = param;
#ifdef RT_USING_INTERRUPT_INFO
        rt_snprintf(irq_desc[vector + NVIC_INT_OFFSET].name, RT_NAME_MAX - 1, "%s", name);
        irq_desc[vector + NVIC_INT_OFFSET].counter = 0;
#endif
    }

    return old_handler;
}

/* Disable interrupt */
void rt_hw_interrupt_mask(int vector)
{
    NVIC_DisableIRQ((IRQn_Type)vector);
    NVIC_ClearPendingIRQ((IRQn_Type)vector);
}

/* Enable interrupt */
void rt_hw_interrupt_umask(int vector)
{
    NVIC_EnableIRQ((IRQn_Type)vector);
}

#ifdef RT_USING_INTERRUPT_INFO
int list_interrupt(int argc, char **argv)
{
    int i;

    for (i = 0; i <= SYS_MAX_INT_SOURCE; i++)
    {
        if (irq_desc[i].handler != rt_hw_interrupt_dummy_handler)
        {
            rt_kprintf("[%d] %s: %d\n", i, irq_desc[i].name, irq_desc[i].counter);
        }
    }

    return 0;
}
MSH_CMD_EXPORT(list_interrupt, list registered interrupts);
#endif
