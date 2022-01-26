/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU) */

#ifndef BSP_ARM_EXCEPTIONS_H
#define BSP_ARM_EXCEPTIONS_H

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* This list includes only Arm standard exceptions. Renesas interrupts are defined in vector_data.h. */
typedef enum IRQn
{
    Reset_IRQn            = -15,       /*  1 Reset Vector invoked on Power up and warm reset */
    NonMaskableInt_IRQn   = -14,       /*  2 Non maskable Interrupt cannot be stopped or preempted */
    HardFault_IRQn        = -13,       /*  3 Hard Fault all classes of Fault */
    MemoryManagement_IRQn = -12,       /*  4 Memory Management MPU mismatch, including Access Violation and No Match */
    BusFault_IRQn         = -11,       /*  5 Bus Fault Pre-Fetch-, Memory Access, other address/memory Fault */
    UsageFault_IRQn       = -10,       /*  6 Usage Fault i.e. Undef Instruction, Illegal State Transition */
    SecureFault_IRQn      = -9,        /*  7 Secure Fault Interrupt */
    SVCall_IRQn           = -5,        /* 11 System Service Call via SVC instruction */
    DebugMonitor_IRQn     = -4,        /* 12 Debug Monitor */
    PendSV_IRQn           = -2,        /* 14 Pendable request for system service */
    SysTick_IRQn          = -1,        /* 15 System Tick Timer */
} IRQn_Type;

#endif
