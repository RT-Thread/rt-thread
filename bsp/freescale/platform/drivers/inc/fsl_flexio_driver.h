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

#ifndef __FSL_FLEXIO_DRIVER_H__
#define __FSL_FLEXIO_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>

#include "fsl_flexio_hal.h"
#if FSL_FEATURE_SOC_FLEXIO_COUNT

/*!
 * @addtogroup flexio_driver
 * @{
 */

/*******************************************************************************
* Definitions
******************************************************************************/
/*!
* @brief Defines the structure to configure the FlexIO module.
* @internal gui name="Common configuration" id="commonCfg"
*/
typedef struct
{
    bool useInt;           /*!< Enables supporting interrupts. @internal gui name="Interrupt" */
    bool onDozeEnable;     /*!< Controls the FlexIO operation in doze modes. @internal gui name="Operation in Doze modes" */
    bool onDebugEnable;    /*!< Enables FlexIO operation when in debug mode. @internal gui name="Operation in Debug modes" */
    bool fastAccessEnable; /*!< Enables fast register accesses to FlexIO registers. @internal gui name="Fast register access" */
} flexio_user_config_t;
/*! @brief Shifter interrupt handler function type */
typedef void (* flexio_shifter_int_handler_t)(void * param);
/*!
* @brief Defines the structure to register the shifter callback and parameter.
*/
typedef struct
{
    flexio_shifter_int_handler_t shifterIntHandler;
    void *param;

}flexio_shifter_callback_t;
/*!
 * @brief Table of base addresses for FlexIO instances.
 */
extern FLEXIO_Type * const g_flexioBase[];

/*!
 * @brief Table to save FlexIO IRQ enumeration numbers defined in the CMSIS header file.
 */
extern const IRQn_Type g_flexioIrqId[];

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name FlexIO Driver
 * @{
 */
 
/*!
 * @brief Initializes the FlexIO module before using the FlexIO module.
 *
 * @param instance FlexIO instance ID.
 * @param userConfigPtr Pointer to the configuration structure.
 * @return Execution status.
 */
flexio_status_t FLEXIO_DRV_Init(uint32_t instance, const flexio_user_config_t *userConfigPtr);

/*!
 * @brief Enables the FlexIO after configuring the FlexIO devices. 
 *
 * @param instance FlexIO instance ID.
 */
void FLEXIO_DRV_Start(uint32_t instance);

/*!
 * @brief Disables the FlexIO during FlexIO device configuration.
 *
 * @param instance FlexIO instance ID.
 */
void FLEXIO_DRV_Pause(uint32_t instance);

/*!
 * @brief Registers the callback function into a shifter interrupt.
 *
 * @param instance FlexIO instance ID.
 * @param shifterId Index of shifter.
 * @param shifterIntHandler Callback function to be registered.
 * @param param Parameter for callback function.
 */
void FLEXIO_DRV_RegisterCallback(uint32_t instance, uint32_t shifterId,
                           flexio_shifter_int_handler_t shifterIntHandler,
                           void *param);

/*!
 * @brief Deinitializes the FlexIO module.
 *
 * @param instance FlexIO instance ID.
 * @return Execution status.
 */
flexio_status_t FLEXIO_DRV_Deinit(uint32_t instance);

/*!
 * @brief IRQ handler for FlexIO.
 *
 * @param instance FlexIO instance ID.
 */
void FLEXIO_DRV_IRQHandler(uint32_t instance);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_FLEXIO_DRIVER_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/

