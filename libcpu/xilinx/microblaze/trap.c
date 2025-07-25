/*
 * File      : trap.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-23     Bernard      first version
 * 2011-12-17     nl1031       for MicroBlaze
 *
 */

#include    <rtthread.h>
#include    "xparameters.h"
#include    "xintc.h"
#include    "xintc_i.h"
#include    "xintc_l.h"


#define MAX_HANDLERS  XPAR_INTC_MAX_NUM_INTR_INPUTS
extern XIntc int_ctl; /* The instance of the Interrupt Controller */


extern rt_atomic_t rt_interrupt_nest;

rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;


void rt_hw_interrupt_handler(int vector)
{
    rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init()
{
    rt_base_t index;

    XIntc_Config           *CfgPtr;


    CfgPtr = &XIntc_ConfigTable[0];


    for (index = 0; index < MAX_HANDLERS; index ++)
    {
        CfgPtr->HandlerTable[index].Handler = (XInterruptHandler)rt_hw_interrupt_handler;
    }

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest = 0;
    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = 0;
    rt_thread_switch_interrupt_flag = 0;
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
    /* disable interrupt */
    XIntc_Disable(&int_ctl,vector);
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    XIntc_Enable(&int_ctl,vector);
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
void rt_hw_interrupt_install(int vector, rt_isr_handler_t new_handler, rt_isr_handler_t *old_handler)
{
    XIntc_Config           *CfgPtr;

    CfgPtr = &XIntc_ConfigTable[0];

    if(vector >= 0 && vector < MAX_HANDLERS)
    {
        if (*old_handler != RT_NULL) *old_handler = (rt_isr_handler_t)CfgPtr->HandlerTable[vector].Handler;
        if (new_handler != RT_NULL) CfgPtr->HandlerTable[vector].Handler = (XInterruptHandler)new_handler;
    }
}

/*****************************************************************************/
/** copy from XIntc_DeviceInterruptHandler in xintc_l.c nl1031
*
* This function is the primary interrupt handler for the driver. It must be
* connected to the interrupt source such that is called when an interrupt of
* the interrupt controller is active. It will resolve which interrupts are
* active and enabled and call the appropriate interrupt handler. It uses
* the AckBeforeService flag in the configuration data to determine when to
* acknowledge the interrupt. Highest priority interrupts are serviced first.
* The driver can be configured to service only the highest priority interrupt
* or all pending interrupts using the {XIntc_SetOptions()} function or
* the {XIntc_SetIntrSrvOption()} function.
*
* This function assumes that an interrupt vector table has been previously
* initialized.  It does not verify that entries in the table are valid before
* calling an interrupt handler.
*
*
* @return   None.
*
* @note
*
* The constant XPAR_INTC_MAX_NUM_INTR_INPUTS must be setup for this to compile.
* Interrupt IDs range from 0 - 31 and correspond to the interrupt input signals
* for the interrupt controller. XPAR_INTC_MAX_NUM_INTR_INPUTS specifies the
* highest numbered interrupt input signal that is used.
*
******************************************************************************/


void rt_hw_trap_irq(void )
{
    u32 intr_status;
    u32 intr_mask = 1;
    int intr_number;
    volatile u32 reg;           /* used as bit bucket */
    XIntc_Config *cfg_ptr;


    /* Get the configuration data using the device ID */
    cfg_ptr = &XIntc_ConfigTable[0];

    /* Get the interrupts that are waiting to be serviced */
    intr_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);

    /* Service each interrupt that is active and enabled by checking each
     * bit in the register from LSB to MSB which corresponds to an interrupt
     * intput signal
     */
    for (intr_number = 0; intr_number < XPAR_INTC_MAX_NUM_INTR_INPUTS; intr_number++)
    {
        if (intr_status & 1)
        {
            XIntc_VectorTableEntry *table_ptr;

            /* If the interrupt has been setup to acknowledge it
             * before servicing the interrupt, then ack it
             */
            if (cfg_ptr->AckBeforeService & intr_mask)
            {
                XIntc_AckIntr(cfg_ptr->BaseAddress, intr_mask);
            }

            /* The interrupt is active and enabled, call the
             * interrupt handler that was setup with the specified
             * parameter
             */
            table_ptr = &(cfg_ptr->HandlerTable[intr_number]);
            table_ptr->Handler(table_ptr->CallBackRef);

            /* If the interrupt has been setup to acknowledge it
             * after it has been serviced then ack it
             */
            if ((cfg_ptr->AckBeforeService & intr_mask) == 0)
            {
                XIntc_AckIntr(cfg_ptr->BaseAddress, intr_mask);
            }

            /*
             * Read the ISR again to handle architectures with posted write
             * bus access issues.
             */
            reg = XIntc_GetIntrStatus(cfg_ptr->BaseAddress);

            /*
             * If only the highest priority interrupt is to be
             * serviced, exit loop and return after servicing
             * the interrupt
             */
            if (cfg_ptr->Options == XIN_SVC_SGL_ISR_OPTION)
            {
                return;
            }
        }

        /* Move to the next interrupt to check */
        intr_mask <<= 1;
        intr_status >>= 1;

        /* If there are no other bits set indicating that all interrupts
         * have been serviced, then exit the loop
         */
        if (intr_status == 0)
        {
            break;
        }
    }
}


