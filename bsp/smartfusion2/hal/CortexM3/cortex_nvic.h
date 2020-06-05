/*******************************************************************************
 * (c) Copyright 2007-2013 Microsemi SoC Products Group.  All rights reserved.
 * 
 * Legacy Actel HAL Cortex NVIC control functions.
 * The use of these functions should be replaced by calls to the equivalent
 * CMSIS function in your application code.
 *
 * SVN $Revision: 5257 $
 * SVN $Date: 2013-03-21 17:54:10 +0530 (Thu, 21 Mar 2013) $
 */
#ifndef CORTEX_NVIC_H_
#define CORTEX_NVIC_H_

#include <stdint.h>

typedef void (*hal_nvic_irq_handler_t)(void);

/*------------------------------------------------------------------------------
 * 
 */
void NVIC_init( void );

/*------------------------------------------------------------------------------
 * 
 */
void NVIC_set_handler
(
    uint32_t interrupt_number,
    hal_nvic_irq_handler_t handler
);

/*------------------------------------------------------------------------------
 * 
 */
void NVIC_set_priority
(
    uint32_t interrupt_number,
    uint8_t priority_level
);

/*------------------------------------------------------------------------------
 * 
 */
void NVIC_enable_interrupt( uint32_t interrupt_number );

/*------------------------------------------------------------------------------
 * 
 */
void NVIC_disable_interrupt( uint32_t interrupt_number );

/*------------------------------------------------------------------------------
 * 
 */
void NVIC_clear_interrupt( uint32_t interrupt_number );

#endif /*CORTEX_NVIC_H_*/
