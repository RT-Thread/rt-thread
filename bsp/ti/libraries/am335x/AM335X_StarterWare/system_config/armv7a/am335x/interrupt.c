/**
 *  \file   interrupt.c
 *
 *  \brief  Interrupt related APIs.
 *
 *   This file contains the APIs for configuring AINTC
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#include "hw_intc.h"
#include "interrupt.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "cpu.h"

/******************************************************************************
**                INTERNAL MACRO DEFINITIONS
******************************************************************************/
#define REG_IDX_SHIFT                  (0x05)
#define REG_BIT_MASK                   (0x1F)
#define NUM_INTERRUPTS                 (128u)

/**************** *************************************************************
**                 STATIC VARIABLE DEFINITIONS
******************************************************************************/
void (*fnRAMVectors[NUM_INTERRUPTS])(void);

/******************************************************************************
**                STATIC FUNCTION DECLARATIONS
******************************************************************************/
static void IntDefaultHandler(void);

/******************************************************************************
**                     API FUNCTION DEFINITIONS
******************************************************************************/

/**
 * The Default Interrupt Handler.
 *
 * This is the default interrupt handler for all interrupts. It simply returns
 * without performing any operation.
 **/
static void IntDefaultHandler(void)
{
    /* Go Back. Nothing to be done */
    ;
}

/**
 * \brief    Registers an interrupt Handler in the interrupt vector table for
 *           system interrupts. 
 * 
 * \param    intrNum - Interrupt Number
 * \param    fnHandler - Function pointer to the ISR
 * 
 * Note: When the interrupt occurs for the sytem interrupt number indicated,
 * the control goes to the ISR given as the parameter.
 * 
 * \return      None.
 **/
void IntRegister(unsigned int intrNum, void (*fnHandler)(void))
{
    /* Assign ISR */
    fnRAMVectors[intrNum] = fnHandler;
}

/**
 * \brief   Unregisters an interrupt
 * 
 * \param   intrNum - Interrupt Number
 * 
 * Note: Once an interrupt is unregistered it will enter infinite loop once
 * an interrupt occurs
 * 
 * \return      None.
 **/
void IntUnRegister(unsigned int intrNum)
{
    /* Assign default ISR */
    fnRAMVectors[intrNum] = IntDefaultHandler;
}

/**
 * \brief   This API is used to initialize the interrupt controller. This API  
 *          shall be called before using the interrupt controller. 
 *
 * \param   None
 * 
 * \return  None.
 *
 **/
void IntAINTCInit(void)
{
    unsigned int intrNum;

    /* Reset the ARM interrupt controller */
    HWREG(SOC_AINTC_REGS + INTC_SYSCONFIG) = INTC_SYSCONFIG_SOFTRESET;
 
    /* Wait for the reset to complete */
    while((HWREG(SOC_AINTC_REGS + INTC_SYSSTATUS) 
          & INTC_SYSSTATUS_RESETDONE) != INTC_SYSSTATUS_RESETDONE);    
  
    /* Enable any interrupt generation by setting priority threshold */ 
    HWREG(SOC_AINTC_REGS + INTC_THRESHOLD) = 
                                       INTC_THRESHOLD_PRIORITYTHRESHOLD;

    /* Register the default handler for all interrupts */
    for(intrNum = 0; intrNum < NUM_INTERRUPTS; intrNum++)
    {
        fnRAMVectors[intrNum] = IntDefaultHandler;
    }
}

/**
 * \brief   This API assigns a priority to an interrupt and routes it to
 *          either IRQ or to FIQ. Priority 0 is the highest priority level
 *          Among the host interrupts, FIQ has more priority than IRQ.
 *
 * \param   intrNum  - Interrupt number
 * \param   priority - Interrupt priority level
 * \param   hostIntRoute - The host interrupt IRQ/FIQ to which the interrupt
 *                         is to be routed.
 *     'priority' can take any value from 0 to 127, 0 being the highest and
 *     127 being the lowest priority.              
 *
 *     'hostIntRoute' can take one of the following values \n
 *             AINTC_HOSTINT_ROUTE_IRQ - To route the interrupt to IRQ \n
 *             AINTC_HOSTINT_ROUTE_FIQ - To route the interrupt to FIQ
 *
 * \return  None.
 *
 **/
void IntPrioritySet(unsigned int intrNum, unsigned int priority,
                    unsigned int hostIntRoute)
{
    HWREG(SOC_AINTC_REGS + INTC_ILR(intrNum)) =
                                 ((priority << INTC_ILR_PRIORITY_SHIFT)
                                   & INTC_ILR_PRIORITY)
                                 | hostIntRoute ;
}

/**
 * \brief   This API enables the system interrupt in AINTC. However, for 
 *          the interrupt generation, make sure that the interrupt is 
 *          enabled at the peripheral level also. 
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void IntSystemEnable(unsigned int intrNum)
{
    __asm(" dsb");
    
    /* Disable the system interrupt in the corresponding MIR_CLEAR register */
    HWREG(SOC_AINTC_REGS + INTC_MIR_CLEAR(intrNum >> REG_IDX_SHIFT))
                                   = (0x01 << (intrNum & REG_BIT_MASK));
}

/**
 * \brief   This API disables the system interrupt in AINTC. 
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void IntSystemDisable(unsigned int intrNum)
{

    __asm(" dsb");
    
    /* Enable the system interrupt in the corresponding MIR_SET register */
    HWREG(SOC_AINTC_REGS + INTC_MIR_SET(intrNum >> REG_IDX_SHIFT)) 
                                   = (0x01 << (intrNum & REG_BIT_MASK));
}

/**
 * \brief   Sets the interface clock to be free running
 *
 * \param   None.
 *
 * \return  None.
 *
 **/
void IntIfClkFreeRunSet(void)
{
    HWREG(SOC_AINTC_REGS + INTC_SYSCONFIG)&= ~INTC_SYSCONFIG_AUTOIDLE; 
}

/**
 * \brief   When this API is called,  automatic clock gating strategy is applied
 *          based on the interface bus activity. 
 *
 * \param   None.
 *
 * \return  None.
 *
 **/
void IntIfClkAutoGateSet(void)
{
    HWREG(SOC_AINTC_REGS + INTC_SYSCONFIG)|= INTC_SYSCONFIG_AUTOIDLE; 
}

/**
 * \brief   Reads the active IRQ number.
 *
 * \param   None
 *
 * \return  Active IRQ number.
 *
 **/
unsigned int IntActiveIrqNumGet(void)
{
    return (HWREG(SOC_AINTC_REGS + INTC_SIR_IRQ) &  INTC_SIR_IRQ_ACTIVEIRQ);
}

/**
 * \brief   Reads the spurious IRQ Flag. Spurious IRQ flag is reflected in both
 *          SIR_IRQ and IRQ_PRIORITY registers of the interrupt controller.
 *
 * \param   None
 *
 * \return  Spurious IRQ Flag.
 *
 **/
unsigned int IntSpurIrqFlagGet(void)
{
    return ((HWREG(SOC_AINTC_REGS + INTC_SIR_IRQ) 
             & INTC_SIR_IRQ_SPURIOUSIRQ) 
            >> INTC_SIR_IRQ_SPURIOUSIRQ_SHIFT);
}

/**
 * \brief   Enables protection mode for the interrupt controller register access.
 *          When the protection is enabled, the registers will be accessible only
 *          in privileged mode of the CPU.
 *
 * \param   None
 *
 * \return  None
 *
 **/
void IntProtectionEnable(void)
{
    HWREG(SOC_AINTC_REGS + INTC_PROTECTION) = INTC_PROTECTION_PROTECTION;
}

/**
 * \brief   Disables protection mode for the interrupt controller register access.
 *          When the protection is disabled, the registers will be accessible 
 *          in both unprivileged and privileged mode of the CPU.
 *
 * \param   None
 *
 * \return  None
 *
 **/
void IntProtectionDisable(void)
{
    HWREG(SOC_AINTC_REGS + INTC_PROTECTION) &= ~INTC_PROTECTION_PROTECTION;
}

/**
 * \brief   Enables the free running of input synchronizer clock
 *
 * \param   None
 *
 * \return  None
 *
 **/
void IntSyncClkFreeRunSet(void)
{
    HWREG(SOC_AINTC_REGS + INTC_IDLE) &= ~INTC_IDLE_TURBO;
}

/**
 * \brief   When this API is called, Input synchronizer clock is auto-gated 
 *          based on interrupt input activity
 *
 * \param   None
 *
 * \return  None
 *
 **/
void IntSyncClkAutoGateSet(void)
{
    HWREG(SOC_AINTC_REGS + INTC_IDLE) |= INTC_IDLE_TURBO;
}

/**
 * \brief   Enables the free running of functional clock
 *
 * \param   None
 *
 * \return  None
 *
 **/
void IntFuncClkFreeRunSet(void)
{
    HWREG(SOC_AINTC_REGS + INTC_IDLE) |= INTC_IDLE_FUNCIDLE;
}

/**
 * \brief   When this API is called, functional clock gating strategy
 *          is applied.
 *
 * \param   None
 *
 * \return  None
 *
 **/
void IntFuncClkAutoGateSet(void)
{
    HWREG(SOC_AINTC_REGS + INTC_IDLE) &= ~INTC_IDLE_FUNCIDLE;
}

/**
 * \brief   Returns the currently active IRQ priority level.
 *
 * \param   None
 *
 * \return  Current IRQ priority 
 *
 **/
unsigned int IntCurrIrqPriorityGet(void)
{
    return (HWREG(SOC_AINTC_REGS + INTC_IRQ_PRIORITY) 
            & INTC_IRQ_PRIORITY_IRQPRIORITY);
}

/**
 * \brief   Returns the priority threshold.
 *
 * \param   None
 *
 * \return  Priority threshold value.
 *
 **/
unsigned int IntPriorityThresholdGet(void)
{
    return (HWREG(SOC_AINTC_REGS + INTC_THRESHOLD) 
            & INTC_THRESHOLD_PRIORITYTHRESHOLD);
}

/**
 * \brief   Sets the given priority threshold value. 
 *
 * \param   threshold - Priority threshold value
 *
 *      'threshold' can take any value from 0x00 to 0x7F. To disable
 *      priority threshold, write 0xFF.
 *             
 * \return  None.
 *
 **/
void IntPriorityThresholdSet(unsigned int threshold)
{
    HWREG(SOC_AINTC_REGS + INTC_THRESHOLD) = 
                     threshold & INTC_THRESHOLD_PRIORITYTHRESHOLD;
}

/**
 * \brief   Returns the raw interrupt status before masking.
 *
 * \param   intrNum - the system interrupt number.
 *
 * \return  TRUE - if the raw status is set \n
 *          FALSE - if the raw status is not set.   
 *
 **/
unsigned int IntRawStatusGet(unsigned int intrNum)
{
    return ((0 == ((HWREG(SOC_AINTC_REGS + INTC_ITR(intrNum >> REG_IDX_SHIFT))
                    >> (intrNum & REG_BIT_MASK))& 0x01)) ? FALSE : TRUE);
}

/**
 * \brief   Sets software interrupt for the given interrupt number.
 *
 * \param   intrNum - the system interrupt number, for which software interrupt
 *                    to be generated
 *
 * \return  None
 *
 **/
void IntSoftwareIntSet(unsigned int intrNum)
{
    /* Enable the software interrupt in the corresponding ISR_SET register */
    HWREG(SOC_AINTC_REGS + INTC_ISR_SET(intrNum >> REG_IDX_SHIFT))
                                   = (0x01 << (intrNum & REG_BIT_MASK));

}

/**
 * \brief   Clears the software interrupt for the given interrupt number.
 *
 * \param   intrNum - the system interrupt number, for which software interrupt
 *                    to be cleared.
 *
 * \return  None
 *
 **/
void IntSoftwareIntClear(unsigned int intrNum)
{
    /* Disable the software interrupt in the corresponding ISR_CLEAR register */
    HWREG(SOC_AINTC_REGS + INTC_ISR_CLEAR(intrNum >> REG_IDX_SHIFT))
                                   = (0x01 << (intrNum & REG_BIT_MASK));

}

/**
 * \brief   Returns the IRQ status after masking.
 *
 * \param   intrNum - the system interrupt number
 *
 * \return  TRUE - if interrupt is pending \n
 *          FALSE - in no interrupt is pending
 *
 **/
unsigned int IntPendingIrqMaskedStatusGet(unsigned int intrNum)
{
    return ((0 ==(HWREG(SOC_AINTC_REGS + INTC_PENDING_IRQ(intrNum >> REG_IDX_SHIFT))
                  >> (((intrNum & REG_BIT_MASK)) & 0x01))) ? FALSE : TRUE);
}

/**
 * \brief  Enables the processor IRQ only in CPSR. Makes the processor to 
 *         respond to IRQs.  This does not affect the set of interrupts 
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void IntMasterIRQEnable(void)
{
    /* Enable IRQ in CPSR.*/
    CPUirqe();

}

/**
 * \brief  Disables the processor IRQ only in CPSR.Prevents the processor to 
 *         respond to IRQs.  This does not affect the set of interrupts 
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void IntMasterIRQDisable(void)
{
    /* Disable IRQ in CPSR.*/
    CPUirqd();
}

/**
 * \brief  Enables the processor FIQ only in CPSR. Makes the processor to 
 *         respond to FIQs.  This does not affect the set of interrupts 
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void IntMasterFIQEnable(void)
{
    /* Enable FIQ in CPSR.*/
    CPUfiqe();
}

/**
 * \brief  Disables the processor FIQ only in CPSR.Prevents the processor to 
 *         respond to FIQs.  This does not affect the set of interrupts 
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void IntMasterFIQDisable(void)
{
    /* Disable FIQ in CPSR.*/
    CPUfiqd();
}

/**
 * \brief   Returns the status of the interrupts FIQ and IRQ.
 *
 * \param    None
 *
 * \return   Status of interrupt as in CPSR.
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
unsigned int IntMasterStatusGet(void)
{
    return CPUIntStatus();
}

/**
 * \brief  Read and save the stasus and Disables the processor IRQ .
 *         Prevents the processor to respond to IRQs.  
 *
 * \param    None
 *
 * \return   Current status of IRQ
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
unsigned char IntDisable(void)
{
    unsigned char status;

    /* Reads the current status.*/
    status = (IntMasterStatusGet() & 0xFF);

    /* Disable the Interrupts.*/
    IntMasterIRQDisable();

    return status;
}

/**
 * \brief  Restore the processor IRQ only status. This does not affect 
 *          the set of interrupts enabled/disabled in the AINTC.
 *
 * \param    The status returned by the IntDisable fundtion.
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void IntEnable(unsigned char  status)
{
    if((status & 0x80) == 0) 
    {
        IntMasterIRQEnable();
    } 
}

/********************************** End Of File ******************************/


