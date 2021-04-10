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
#include "at91sam9g45.h"
#include "interrupt.h"

#define AIC_IRQS    32
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
static rt_uint32_t at91sam9g45_default_irq_priority[MAX_HANDLERS] = {
    7,  /* Advanced Interrupt Controller - FIQ    */
    7,  /* System Controller Interrupt            */
    1,  /* Parallel I/O Controller A,             */
    1,  /* Parallel I/O Controller B              */
    1,  /* Parallel I/O Controller C              */
    0,  /* Parallel I/O Controller D/E            */
    5,  /* True Random Number Generator           */
    5,  /* USART 0                                */
    5,  /* USART 1                                */
    0,  /* USART 2                                */
    2,  /* USART 3                                */
    6,  /* High Speed Multimedia Card Interface 0 */
    5,  /* Two-Wire Interface 0                   */
    5,  /* Two-Wire Interface 1                   */
    5,  /* Serial Peripheral Interface            */
    0,  /* Serial Peripheral Interface            */
    0,  /* Synchronous Serial Controller 0        */
    0,  /* Synchronous Serial Controller 1        */
    0,  /* Timer Counter 0,1,2,3,4,5              */
    0,  /* Pulse Width Modulation Controller      */
    2,  /* Touch Screen ADC Controller            */
    3,  /* DMA Controller                         */
    0,  /* USB Host High Speed                    */
    5,  /* LCD Controller                         */
    5,  /* AC97 Controller                        */
    5,  /* Ethernet MAC                           */
    0,  /* Image Sensor Interface                 */
    0,  /* USB Device High Speed                  */
    0,  /* N/A                                    */
    0,  /* High Speed Multimedia Card Interface 1 */
    0,  /* Reserved                               */
    0,  /* Advanced Interrupt Controller - IRQ    */
};

/**
 * @addtogroup AT91SAM9G45
 */
/*@{*/

void rt_hw_interrupt_mask(int irq);
void rt_hw_interrupt_umask(int irq);

rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
    return RT_NULL;
}

rt_isr_handler_t at91_gpio_irq_handle(rt_uint32_t bank, void *param)
{
    rt_uint32_t isr, irq_n;
    AT91PS_PIO pio;
    void *parameter;

    switch (bank)
    {
    case 0: pio = AT91C_BASE_PIOA; break;
    case 1: pio = AT91C_BASE_PIOB; break;
    case 2: pio = AT91C_BASE_PIOC; break;
    case 3: pio = AT91C_BASE_PIOD; break;
    case 4: pio = AT91C_BASE_PIOE; break;
    default: return RT_NULL;
    }
    irq_n = AIC_IRQS + 32*bank;
    isr = readl(pio->PIO_ISR);
    isr &= readl(pio->PIO_IMR);
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

unsigned int SpuriousCount = 0;
static void DefaultSpuriousHandler( void )
{
    SpuriousCount++;
    rt_kprintf("Spurious interrupt %d occured!!!\n", SpuriousCount);
    return ;
}

static void DefaultFiqHandler(void)
{
    rt_kprintf("Unhandled FIQ occured!!!\n");
    while (1);
}

static void DefaultIrqHandler(void)
{
    rt_kprintf("Unhandled IRQ %d occured!!!\n", AT91C_BASE_AIC->AIC_ISR);
    while (1);
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
    AT91C_BASE_AIC->AIC_SVR[0] = (rt_uint32_t)DefaultFiqHandler;
    for (i = 1; i < AIC_IRQS; i++) {
        /* Put irq number in Source Vector Register: */
        AT91C_BASE_AIC->AIC_SVR[i] = (rt_uint32_t)DefaultIrqHandler; // no-used
        /* Active Low interrupt, with the specified priority */
        AT91C_BASE_AIC->AIC_SMR[i] = AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE | priority[i];
        //AT91C_AIC_SRCTYPE_FALLING
    }

    /*
     * Spurious Interrupt ID in Spurious Vector Register is NR_AIC_IRQS
     * When there is no current interrupt, the IRQ Vector Register reads the value stored in AIC_SPU
     */
    AT91C_BASE_AIC->AIC_SPU = (rt_uint32_t)DefaultSpuriousHandler;

    /* Perform 8 End Of Interrupt Command to make sure AIC will not Lock out nIRQ */
    for (i = 0; i < 8; i++)
        AT91C_BASE_AIC->AIC_EOICR = 0;

    /* No debugging in AIC: Debug (Protect) Control Register */
    AT91C_BASE_AIC->AIC_DCR = 0;

    /* Disable and clear all interrupts initially */
    AT91C_BASE_AIC->AIC_IDCR = 0xFFFFFFFF;
    AT91C_BASE_AIC->AIC_ICCR = 0xFFFFFFFF;
}


static void at91_gpio_irq_init()
{
    int i, idx;
    char *name[] = {"PIOA", "PIOB", "PIOC", "PIODE"};
    rt_uint32_t aic_pids[] = { AT91C_ID_PIOA, AT91C_ID_PIOB, AT91C_ID_PIOC, AT91C_ID_PIOD_E };

    AT91C_BASE_PIOA->PIO_IDR = 0xffffffff;
    AT91C_BASE_PIOB->PIO_IDR = 0xffffffff;
    AT91C_BASE_PIOC->PIO_IDR = 0xffffffff;
    AT91C_BASE_PIOD->PIO_IDR = 0xffffffff;
    AT91C_BASE_PIOE->PIO_IDR = 0xffffffff;

    for (i = 0; i < 4; i++)
    {
        idx = aic_pids[i];
        irq_desc[idx].handler = (rt_isr_handler_t)at91_gpio_irq_handle;
        irq_desc[idx].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
        rt_snprintf(irq_desc[idx].name, RT_NAME_MAX - 1, name[i]);
        irq_desc[idx].counter = 0;
#endif

        rt_hw_interrupt_umask(idx);
    }
}


/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    register rt_uint32_t idx;
    rt_uint32_t *priority = at91sam9g45_default_irq_priority;

    at91_extern_irq = (1UL << AT91C_ID_IRQ0);

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
    rt_uint32_t pin, bank;
    AT91PS_PIO pio;

    bank = (irq - AIC_IRQS)>>5;

    switch (bank)
    {
    case 0: pio = AT91C_BASE_PIOA; break;
    case 1: pio = AT91C_BASE_PIOB; break;
    case 2: pio = AT91C_BASE_PIOC; break;
    case 3: pio = AT91C_BASE_PIOD; break;
    case 4: pio = AT91C_BASE_PIOE; break;
    default: return;
    }
    pin = 1 << ((irq - AIC_IRQS) & 31);
    pio->PIO_IDR = pin;
}

/**
 * This function will mask a interrupt.
 * @param irq   the interrupt number
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
        AT91C_BASE_AIC->AIC_IDCR = 1 << irq;
    }
}

static void at91_gpio_irq_umask(int irq)
{
    rt_uint32_t pin, bank;
    AT91PS_PIO pio;

    bank = (irq - AIC_IRQS)>>5;

    switch (bank)
    {
    case 0: pio = AT91C_BASE_PIOA; break;
    case 1: pio = AT91C_BASE_PIOB; break;
    case 2: pio = AT91C_BASE_PIOC; break;
    case 3: pio = AT91C_BASE_PIOD; break;
    case 4: pio = AT91C_BASE_PIOE; break;
    default: return;
    }
    pin = 1 << ((irq - AIC_IRQS) & 31);
    pio->PIO_IER = pin;
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
        AT91C_BASE_AIC->AIC_IECR = 1 << irq;
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

    if (vector < MAX_HANDLERS)
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
    case AT91C_AIC_SRCTYPE_EXT_HIGH_LEVEL:
        srctype = AT91C_AIC_SRCTYPE_HIGH;
        break;
    case AT91C_AIC_SRCTYPE_EXT_POSITIVE_EDGE:
        srctype = AT91C_AIC_SRCTYPE_RISING;
        break;
    case AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE:
        // only supported on external interrupts
        if ((irq == AT91C_ID_FIQ) || is_extern_irq(irq))
            srctype = AT91C_AIC_SRCTYPE_LOW;
        else
            return -1;
        break;
    case AT91C_AIC_SRCTYPE_INT_EDGE_TRIGGERED:
        // only supported on external interrupts
        if ((irq == AT91C_ID_FIQ) || is_extern_irq(irq))
            srctype = AT91C_AIC_SRCTYPE_FALLING;
        else
            return -1;
        break;
    default:
        return -1;
    }

    smr = readl(AT91C_AIC_SMR(irq)) & ~AT91C_AIC_SRCTYPE;
    AT91C_BASE_AIC->AIC_SMR[irq] = smr | srctype;
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
    readl(AT91C_AIC_IVR);
    /* clear pending register */
    id = readl(AT91C_AIC_ISR);

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
    AT91C_BASE_AIC->AIC_EOICR = 0x0;
}

void rt_interrupt_dispatch(rt_uint32_t fiq_irq)
{
    rt_isr_handler_t isr_func;
    rt_uint32_t irq;
    void *param;

    /* get irq number */
    irq = rt_hw_interrupt_get_active(fiq_irq);

    /* get interrupt service routine */
    isr_func = irq_desc[irq].handler;
    param = irq_desc[irq].param;

    /* turn to interrupt service routine */
    isr_func(irq, param);

    rt_hw_interrupt_ack(fiq_irq, irq);
#ifdef RT_USING_INTERRUPT_INFO
    irq_desc[irq].counter ++;
#endif
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


