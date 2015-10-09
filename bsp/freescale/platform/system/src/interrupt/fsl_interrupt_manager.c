/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <assert.h>
#include "fsl_interrupt_manager.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Counter to manage the nested callings of global disable/enable interrupt.
 */
uint32_t g_interruptDisableCount = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_InstallHandler
 * Description   : Install an interrupt handler routine for a given IRQ number
 * This function will let application to register/replace the interrupt 
 * handler for specified IRQ number. IRQ number is different with Vector
 * number. IRQ 0 will start from Vector 16 address. Refer to reference
 * manual for details. Also refer to startup_MKxxxx.s file for each chip
 * family to find out the default interrut handler for each device. This
 * function will convert the IRQ number to vector number by adding 16 to
 * it. 
 * 
 *END**************************************************************************/
void * INT_SYS_InstallHandler(IRQn_Type irqNumber, void (*handler)(void))
{
#if (defined(__CC_ARM))
    extern uint32_t Image$$VECTOR_RAM$$Base[];
    #define __VECTOR_RAM Image$$VECTOR_RAM$$Base
#else
    extern uint32_t __VECTOR_RAM[];
#endif

    /* Check IRQ number */
    assert(FSL_FEATURE_INTERRUPT_IRQ_MIN <= irqNumber);
    assert(irqNumber <= FSL_FEATURE_INTERRUPT_IRQ_MAX);

    /* Check whether there is vector table in RAM */
    assert(__VECTOR_RAM != 0U);
    
    /* Save the former handler pointer */
    void * retVal = (void *)__VECTOR_RAM[irqNumber + 16];

    /* Set handler into vector table */
    __VECTOR_RAM[irqNumber + 16] = (uint32_t)handler;

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_EnableIRQGlobal
 * Description   : Enable system interrupt
 * This function will enable the global interrupt by calling the core API
 * 
 *END**************************************************************************/
void INT_SYS_EnableIRQGlobal(void)
{
    /* check and update */
    if (g_interruptDisableCount > 0)
    {
        g_interruptDisableCount--;

        if (g_interruptDisableCount > 0)
        {
            return;
        }

        /* call core API to enable the global interrupt*/
        __enable_irq();
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : INT_SYS_DisableIRQGlobal
 * Description   : Disnable system interrupt
 * This function will disable the global interrupt by calling the core API
 * 
 *END**************************************************************************/
void INT_SYS_DisableIRQGlobal(void)
{
    /* call core API to disable the global interrupt*/
    __disable_irq();

    /* update counter*/
    g_interruptDisableCount++;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

