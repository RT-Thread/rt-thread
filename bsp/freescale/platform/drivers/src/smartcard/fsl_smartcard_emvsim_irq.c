/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#include "board.h"
#include "fsl_smartcard_driver.h"
#include "fsl_smartcard_emvsim_driver.h"
#if USING_NCN8025_INTERFACE
#include "fsl_smartcard_ncn8025_driver.h"
#endif
#if USING_DIRECT_INTERFACE
#include "fsl_smartcard_direct_driver.h"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
extern smartcard_state_t smartcardState;
bool gCardPresent = false;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void SMARTCARD_EMVSIM_DRV_IRQHandler(uint32_t instance);
extern void SMARTCARD_UART_DRV_ErrIRQHandler(uint32_t instance);
/*******************************************************************************
 * Code
 ******************************************************************************/

#if (FSL_FEATURE_SOC_EMVSIM_COUNT > 0)
/* Implementation of EMVSIM handler named in startup code. */
#if (FSL_RTOS_MQX)
void MQX_EMVSIM0_IRQHandler(void)
#else
void EMVSIM0_IRQHandler(void)
#endif
{
    SMARTCARD_EMVSIM_DRV_IRQHandler(0);
}

#if (EMVSIM_INSTANCE_COUNT > 1)
/* Implementation of EMVSIM1 handler named in startup code. */
#if (FSL_RTOS_MQX)
void MQX_EMVSIM1_IRQHandler(void)
#else
void EMVSIM1_IRQHandler(void)
#endif
{
    SMARTCARD_EMVSIM_DRV_IRQHandler(1);
}
#endif
#endif /* FSL_FEATURE_SOC_EMVSIM_COUNT > 0 */


#if USING_NCN8025_INTERFACE
/* gpio IRQ handler with the same name in startup code. */
#if (FSL_RTOS_MQX)
void MQX_PORTA_IRQHandler(void)
#else
void PORTA_IRQHandler(void)
#endif
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTA_BASE_PTR);
    
    /* Invoke PHY IRQ handler specific function */
    SMARTCARD_DRV_NCN8025IRQHandler(BOARD_SMARTCARD_MODULE_INSTANCE);
}

/* gpio IRQ handler with the same name in startup code. */
#if (FSL_RTOS_MQX)
void MQX_PORTB_IRQHandler(void)
#else
void PORTB_IRQHandler(void)
#endif
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTB_BASE_PTR);
    
    /* Invoke PHY IRQ handler specific function */
    SMARTCARD_DRV_NCN8025IRQHandler(BOARD_SMARTCARD_MODULE_INSTANCE);
}

/* gpio IRQ handler with the same name in startup code. */
#if (FSL_RTOS_MQX)
void MQX_PORTC_IRQHandler(void)
#else
void PORTC_IRQHandler(void)
#endif
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTC_BASE_PTR);
    
    /* Invoke PHY IRQ handler specific function */
    SMARTCARD_DRV_NCN8025IRQHandler(BOARD_SMARTCARD_MODULE_INSTANCE);
}

/* gpio IRQ handler with the same name in startup code. */
#if (FSL_RTOS_MQX)
void MQX_PORTD_IRQHandler(void)
#else
void PORTD_IRQHandler(void)
#endif
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTD_BASE_PTR);
    
    /* Invoke PHY IRQ handler specific function */
    SMARTCARD_DRV_NCN8025IRQHandler(BOARD_SMARTCARD_MODULE_INSTANCE);
}

/* gpio IRQ handler with the same name in startup code. */
#if (FSL_RTOS_MQX)
void MQX_PORTE_IRQHandler(void)
#else
void PORTE_IRQHandler(void)
#endif
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTE_BASE_PTR);
    
    /* Invoke PHY IRQ handler specific function */
    SMARTCARD_DRV_NCN8025IRQHandler(BOARD_SMARTCARD_MODULE_INSTANCE);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

