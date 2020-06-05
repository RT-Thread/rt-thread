/*******************************************************************************
 * (c) Copyright 2007-2013 Microsemi SoC Products Group.  All rights reserved.
 * 
 * Legacy Actel HAL Cortex NVIC control functions.
 * The use of these functions should be replaced by calls to the equivalent
 * CMSIS function in your application code.
 *
 * SVN $Revision: 7375 $
 * SVN $Date: 2015-05-01 19:27:40 +0530 (Fri, 01 May 2015) $
 */
#include "cortex_nvic.h"
#ifdef MSCC_NO_RELATIVE_PATHS
#include "mss_assert.h"
#else
#include "../../CMSIS/mss_assert.h"
#endif


/***************************************************************************//**
 * 
 */
void NVIC_init( void )
{
    /*
     * Please use the NVIC control functions provided by the SmartFusion2 CMSIS
     * Hardware Abstraction Layer. The use of the Actel HAL NVIC control
     * functions is obsolete on SmartFusion2 devices.
     *
     * Simply remove the call to NVIC_init() from your application code.
     */
    ASSERT(0);
}

/***************************************************************************//**
 * 
 */
void NVIC_set_handler
(
    uint32_t interrupt_number,
    hal_nvic_irq_handler_t handler
)
{
    /*
     * Please use the NVIC control functions provided by the SmartFusion2 CMSIS
     * Hardware Abstraction Layer. The use of the Actel HAL NVIC control
     * functions is obsolete on SmartFusion2 devices.
     *
     * Please remove the call to NVIC_set_handler() from your application code
     * and provide a function using one of the following function prototypes to
     * handle interrupts from peripherals implemeted in the SmartFusion2 FPGA
     * fabric:
     *      - void FabricIrq0_IRQHandler(void)
     *      - void FabricIrq1_IRQHandler(void)
     *      - void FabricIrq2_IRQHandler(void)
     *      - void FabricIrq3_IRQHandler(void)
     *      - void FabricIrq4_IRQHandler(void)
     *      - void FabricIrq5_IRQHandler(void)
     *      - void FabricIrq6_IRQHandler(void)
     *      - void FabricIrq7_IRQHandler(void)
     *      - void FabricIrq8_IRQHandler(void)
     *      - void FabricIrq9_IRQHandler(void)
     *      - void FabricIrq10_IRQHandler(void)
     *      - void FabricIrq11_IRQHandler(void)
     *      - void FabricIrq12_IRQHandler(void)
     *      - void FabricIrq13_IRQHandler(void)
     *      - void FabricIrq14_IRQHandler(void)
     *      - void FabricIrq15_IRQHandler(void)
     * The function to implement depends on which MSS_INT_F2M[n] signal is used
     * in your Libero design to connect the interrupt signal of the peripheral
     * generating the interrupt.
     */
    ASSERT(0);
}

/***************************************************************************//**
 * 
 */
void NVIC_set_priority
(
    uint32_t interrupt_number,
    uint8_t priority_level
)
{
    /*
     * Please use the NVIC control functions provided by the SmartFusion2 CMSIS
     * Hardware Abstraction Layer. The use of the Actel HAL NVIC control
     * functions is obsolete on SmartFusion2 devices.
     *
     * Please replace calls to NVIC_set_priority() with a call to the CMSIS
     * void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority) function where
     * IRQn is one of the following values:
     *      - FabricIrq0_IRQn
     *      - FabricIrq1_IRQn
     *      - FabricIrq2_IRQn
     *      - FabricIrq3_IRQn
     *      - FabricIrq4_IRQn
     *      - FabricIrq5_IRQn
     *      - FabricIrq6_IRQn
     *      - FabricIrq7_IRQn
     *      - FabricIrq8_IRQn
     *      - FabricIrq9_IRQn
     *      - FabricIrq10_IRQn
     *      - FabricIrq11_IRQn
     *      - FabricIrq12_IRQn
     *      - FabricIrq13_IRQn
     *      - FabricIrq14_IRQn
     *      - FabricIrq15_IRQn
     */
    ASSERT(0);
}

/***************************************************************************//**
 * 
 */
void NVIC_enable_interrupt( uint32_t interrupt_number )
{
    /*
     * Please use the NVIC control functions provided by the SmartFusion2 CMSIS
     * Hardware Abstraction Layer. The use of the Actel HAL NVIC control
     * functions is obsolete on SmartFusion2 devices.
     *
     * Please replace calls to NVIC_enable_interrupt() with a call to the CMSIS
     * void NVIC_EnableIRQ(IRQn_Type IRQn) function where IRQn is one of the
     * following values:
     *      - FabricIrq0_IRQn
     *      - FabricIrq1_IRQn
     *      - FabricIrq2_IRQn
     *      - FabricIrq3_IRQn
     *      - FabricIrq4_IRQn
     *      - FabricIrq5_IRQn
     *      - FabricIrq6_IRQn
     *      - FabricIrq7_IRQn
     *      - FabricIrq8_IRQn
     *      - FabricIrq9_IRQn
     *      - FabricIrq10_IRQn
     *      - FabricIrq11_IRQn
     *      - FabricIrq12_IRQn
     *      - FabricIrq13_IRQn
     *      - FabricIrq14_IRQn
     *      - FabricIrq15_IRQn
     */
    ASSERT(0);
}

/***************************************************************************//**
 * 
 */
void NVIC_disable_interrupt( uint32_t interrupt_number )
{
    /*
     * Please use the NVIC control functions provided by the SmartFusion2 CMSIS
     * Hardware Abstraction Layer. The use of the Actel HAL NVIC control
     * functions is obsolete on SmartFusion2 devices.
     *
     * Please replace calls to NVIC_disable_interrupt() with a call to the CMSIS
     * void NVIC_DisableIRQ(IRQn_Type IRQn) function where IRQn is one of the
     * following values:
     *      - FabricIrq0_IRQn
     *      - FabricIrq1_IRQn
     *      - FabricIrq2_IRQn
     *      - FabricIrq3_IRQn
     *      - FabricIrq4_IRQn
     *      - FabricIrq5_IRQn
     *      - FabricIrq6_IRQn
     *      - FabricIrq7_IRQn
     *      - FabricIrq8_IRQn
     *      - FabricIrq9_IRQn
     *      - FabricIrq10_IRQn
     *      - FabricIrq11_IRQn
     *      - FabricIrq12_IRQn
     *      - FabricIrq13_IRQn
     *      - FabricIrq14_IRQn
     *      - FabricIrq15_IRQn
     */
    ASSERT(0);
}

/***************************************************************************//**
 * 
 */
void NVIC_clear_interrupt( uint32_t interrupt_number )
{
    /*
     * Please use the NVIC control functions provided by the SmartFusion2 CMSIS
     * Hardware Abstraction Layer. The use of the Actel HAL NVIC control
     * functions is obsolete on SmartFusion2 devices.
     *
     * Please replace calls to NVIC_clear_interrupt() with a call to the CMSIS
     * void NVIC_ClearPendingIRQ(IRQn_Type IRQn) function where IRQn is one of the
     * following values:
     *      - FabricIrq0_IRQn
     *      - FabricIrq1_IRQn
     *      - FabricIrq2_IRQn
     *      - FabricIrq3_IRQn
     *      - FabricIrq4_IRQn
     *      - FabricIrq5_IRQn
     *      - FabricIrq6_IRQn
     *      - FabricIrq7_IRQn
     *      - FabricIrq8_IRQn
     *      - FabricIrq9_IRQn
     *      - FabricIrq10_IRQn
     *      - FabricIrq11_IRQn
     *      - FabricIrq12_IRQn
     *      - FabricIrq13_IRQn
     *      - FabricIrq14_IRQn
     *      - FabricIrq15_IRQn
     */
    ASSERT(0);
}
