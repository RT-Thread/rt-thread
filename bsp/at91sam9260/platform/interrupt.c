/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 */

#include <rthw.h>
#include "at91sam926x.h"
#include "interrupt.h"
#define MAX_HANDLERS    (AIC_IRQS + PIN_IRQS)

extern rt_uint32_t rt_interrupt_nest;

/* exception and interrupt handler table */
struct rt_irq_desc irq_desc[MAX_HANDLERS];

rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;


/* --------------------------------------------------------------------
 *  Interrupt initialization
 * -------------------------------------------------------------------- */

rt_uint32_t at91_extern_irq;

#define is_extern_irq(irq) ((1 << (irq)) & at91_extern_irq)

/*
 * The default interrupt priority levels (0 = lowest, 7 = highest).
 */
static rt_uint32_t at91sam9260_default_irq_priority[MAX_HANDLERS] = {
    7,  /* Advanced Interrupt Controller */
    7,  /* System Peripherals */
    1,  /* Parallel IO Controller A */
    1,  /* Parallel IO Controller B */
    1,  /* Parallel IO Controller C */
    0,  /* Analog-to-Digital Converter */
    5,  /* USART 0 */
    5,  /* USART 1 */
    5,  /* USART 2 */
    0,  /* Multimedia Card Interface */
    2,  /* USB Device Port */
    6,  /* Two-Wire Interface */
    5,  /* Serial Peripheral Interface 0 */
    5,  /* Serial Peripheral Interface 1 */
    5,  /* Serial Synchronous Controller */
    0,
    0,
    0,  /* Timer Counter 0 */
    0,  /* Timer Counter 1 */
    0,  /* Timer Counter 2 */
    2,  /* USB Host port */
    3,  /* Ethernet */
    0,  /* Image Sensor Interface */
    5,  /* USART 3 */
    5,  /* USART 4 */
    5,  /* USART 5 */
    0,  /* Timer Counter 3 */
    0,  /* Timer Counter 4 */
    0,  /* Timer Counter 5 */
    0,  /* Advanced Interrupt Controller */
    0,  /* Advanced Interrupt Controller */
    0,  /* Advanced Interrupt Controller */
};

/**
 * @addtogroup AT91SAM926X
 */
/*@{*/

void rt_hw_interrupt_mask(int irq);
void rt_hw_interrupt_umask(int irq);

rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
    return RT_NULL;
}

rt_isr_handler_t at91_gpio_irq_handle(rt_uint32_t vector, void *param)
{
    rt_uint32_t isr, pio, irq_n;
    void *parameter;

    if (vector == AT91SAM9260_ID_PIOA)
    {
        pio = AT91_PIOA;
        irq_n = AIC_IRQS;
    }
    else if (vector == AT91SAM9260_ID_PIOB)
    {
        pio = AT91_PIOB;
        irq_n = AIC_IRQS + 32;
    }
    else if (vector == AT91SAM9260_ID_PIOC)
    {
        pio = AT91_PIOC;
        irq_n = AIC_IRQS + 32*2;
    }
    else
        return RT_NULL;
    isr = at91_sys_read(pio+PIO_ISR) & at91_sys_read(pio+PIO_IMR);
    while (isr)
    {
        if (isr & 1)
        {
            parameter = irq_desc[irq_n].param;
            irq_desc[irq_n].handler(irq_n, parameter);
        }
        isr >>= 1;
        irq_n++;
    }

    return RT_NULL;
}

/*
 * Initialize the AIC interrupt controller.
 */
void at91_aic_init(rt_uint32_t *priority)
{
    rt_uint32_t i;

    /*
     * The IVR is used by macro get_irqnr_and_base to read and verify.
     * The irq number is NR_AIC_IRQS when a spurious interrupt has occurred.
     */
    for (i = 0; i < AIC_IRQS; i++) {
        /* Put irq number in Source Vector Register: */
        at91_sys_write(AT91_AIC_SVR(i), i); // no-used
        /* Active Low interrupt, with the specified priority */
        at91_sys_write(AT91_AIC_SMR(i), AT91_AIC_SRCTYPE_LOW | priority[i]);
        //AT91_AIC_SRCTYPE_FALLING

        /* Perform 8 End Of Interrupt Command to make sure AIC will not Lock out nIRQ */
        if (i < 8)
            at91_sys_write(AT91_AIC_EOICR, 0);
    }

    /*
     * Spurious Interrupt ID in Spurious Vector Register is NR_AIC_IRQS
     * When there is no current interrupt, the IRQ Vector Register reads the value stored in AIC_SPU
     */
    at91_sys_write(AT91_AIC_SPU, AIC_IRQS);

    /* No debugging in AIC: Debug (Protect) Control Register */
    at91_sys_write(AT91_AIC_DCR, 0);

    /* Disable and clear all interrupts initially */
    at91_sys_write(AT91_AIC_IDCR, 0xFFFFFFFF);
    at91_sys_write(AT91_AIC_ICCR, 0xFFFFFFFF);
}


static void at91_gpio_irq_init()
{
    int i, idx;
    char *name[] = {"PIOA", "PIOB", "PIOC"};

    at91_sys_write(AT91_PIOA+PIO_IDR, 0xffffffff);
    at91_sys_write(AT91_PIOB+PIO_IDR, 0xffffffff);
    at91_sys_write(AT91_PIOC+PIO_IDR, 0xffffffff);

    idx = AT91SAM9260_ID_PIOA;
    for (i = 0; i < 3; i++)
    {
        irq_desc[idx].handler = (rt_isr_handler_t)at91_gpio_irq_handle;
        irq_desc[idx].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
        rt_snprintf(irq_desc[idx].name, RT_NAME_MAX - 1, name[i]);
        irq_desc[idx].counter = 0;
#endif
        idx++;
    }

    rt_hw_interrupt_umask(AT91SAM9260_ID_PIOA);
    rt_hw_interrupt_umask(AT91SAM9260_ID_PIOB);
    rt_hw_interrupt_umask(AT91SAM9260_ID_PIOC);
}


/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    register rt_uint32_t idx;
    rt_uint32_t *priority = at91sam9260_default_irq_priority;

    at91_extern_irq = (1UL << AT91SAM9260_ID_IRQ0) | (1UL << AT91SAM9260_ID_IRQ1)
            | (1UL << AT91SAM9260_ID_IRQ2);

    /* Initialize the AIC interrupt controller */
    at91_aic_init(priority);

    /* init exceptions table */
    for(idx=0; idx < MAX_HANDLERS; idx++)
    {
        irq_desc[idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handle;
        irq_desc[idx].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
        rt_snprintf(irq_desc[idx].name, RT_NAME_MAX - 1, "default");
        irq_desc[idx].counter = 0;
#endif
    }

    at91_gpio_irq_init();

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest = 0;
    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = 0;
    rt_thread_switch_interrupt_flag = 0;
}

static void at91_gpio_irq_mask(int irq)
{
    rt_uint32_t pin, pio, bank;

    bank = (irq - AIC_IRQS)>>5;

    if (bank == 0)
    {
        pio = AT91_PIOA;
    }
    else if (bank == 1)
    {
        pio = AT91_PIOB;
    }
    else if (bank == 2)
    {
        pio = AT91_PIOC;
    }
    else
        return;
    pin = 1 << ((irq - AIC_IRQS) & 31);
    at91_sys_write(pio+PIO_IDR, pin);
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int irq)
{
    if (irq >= AIC_IRQS)
    {
        at91_gpio_irq_mask(irq);
    }
    else
    {
        /* Disable interrupt on AIC */
        at91_sys_write(AT91_AIC_IDCR, 1 << irq);
    }
}

static void at91_gpio_irq_umask(int irq)
{
    rt_uint32_t pin, pio, bank;

    bank = (irq - AIC_IRQS)>>5;

    if (bank == 0)
    {
        pio = AT91_PIOA;
    }
    else if (bank == 1)
    {
        pio = AT91_PIOB;
    }
    else if (bank == 2)
    {
        pio = AT91_PIOC;
    }
    else
        return;
    pin = 1 << ((irq - AIC_IRQS) & 31);
    at91_sys_write(pio+PIO_IER, pin);
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int irq)
{
    if (irq >= AIC_IRQS)
    {
        at91_gpio_irq_umask(irq);
    }
    else
    {
        /* Enable interrupt on AIC */
        at91_sys_write(AT91_AIC_IECR, 1 << irq);
    }
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param handler the interrupt service routine to be installed
 * @param param the interrupt service function parameter
 * @param name the interrupt name
 * @return old handler
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
                                    void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if(vector < MAX_HANDLERS)
    {
        old_handler = irq_desc[vector].handler;
        if (handler != RT_NULL)
        {
            irq_desc[vector].handler = (rt_isr_handler_t)handler;
            irq_desc[vector].param = param;
#ifdef RT_USING_INTERRUPT_INFO
            rt_snprintf(irq_desc[vector].name, RT_NAME_MAX - 1, "%s", name);
            irq_desc[vector].counter = 0;
#endif
        }
    }

    return old_handler;
}

/*@}*/

/*
static int at91_aic_set_type(unsigned irq, unsigned type)
{
    unsigned int smr, srctype;

    switch (type) {
    case IRQ_TYPE_LEVEL_HIGH:
        srctype = AT91_AIC_SRCTYPE_HIGH;
        break;
    case IRQ_TYPE_EDGE_RISING:
        srctype = AT91_AIC_SRCTYPE_RISING;
        break;
    case IRQ_TYPE_LEVEL_LOW:
        // only supported on external interrupts
        if ((irq == AT91_ID_FIQ) || is_extern_irq(irq))
            srctype = AT91_AIC_SRCTYPE_LOW;
        else
            return -1;
        break;
    case IRQ_TYPE_EDGE_FALLING:
        // only supported on external interrupts
        if ((irq == AT91_ID_FIQ) || is_extern_irq(irq))
            srctype = AT91_AIC_SRCTYPE_FALLING;
        else
            return -1;
        break;
    default:
        return -1;
    }

    smr = at91_sys_read(AT91_AIC_SMR(irq)) & ~AT91_AIC_SRCTYPE;
    at91_sys_write(AT91_AIC_SMR(irq), smr | srctype);
    return 0;
}
*/
rt_uint32_t rt_hw_interrupt_get_active(rt_uint32_t fiq_irq)
{

    //volatile rt_uint32_t irqstat;
    rt_uint32_t id;
    if (fiq_irq == INT_FIQ)
        return 0;

    //IRQ
    /* AIC need this dummy read */
    at91_sys_read(AT91_AIC_IVR);
    /* clear pending register */
    id = at91_sys_read(AT91_AIC_ISR);

    return id;
}

void rt_hw_interrupt_ack(rt_uint32_t fiq_irq, rt_uint32_t id)
{
    /* new FIQ generation */
    if (fiq_irq == INT_FIQ)
        return;

    /* new IRQ generation */
    // EIOCR must be write any value after interrupt,
    // or else can't response next interrupt
    at91_sys_write(AT91_AIC_EOICR, 0x0);
}

#ifdef RT_USING_FINSH
#ifdef RT_USING_INTERRUPT_INFO
void list_irq(void)
{
    int irq;

    rt_kprintf("number\tcount\tname\n");
    for (irq = 0; irq < MAX_HANDLERS; irq++)
    {
        if (rt_strncmp(irq_desc[irq].name, "default", sizeof("default")))
        {
            rt_kprintf("%02ld: %10ld  %s\n", irq, irq_desc[irq].counter, irq_desc[irq].name);
        }
    }
}

#include <finsh.h>
FINSH_FUNCTION_EXPORT(list_irq, list system irq);

#ifdef FINSH_USING_MSH
int cmd_list_irq(int argc, char** argv)
{
    list_irq();
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_list_irq, __cmd_list_irq, list system irq.);

#endif
#endif
#endif


