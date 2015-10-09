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

#if !defined(__FSL_XBAR_DRIVER_H__)
#define __FSL_XBAR_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_xbar_signals.h"
#include "fsl_xbar_hal.h"
#if FSL_FEATURE_SOC_XBAR_COUNT

/*!
 * @addtogroup xbar_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Table of base addresses for XBAR instances. */
extern XBARA_Type * const g_xbaraBase[];
#if !defined(FSL_FEATURE_XBAR_HAS_SINGLE_MODULE)
extern XBARB_Type * const g_xbarbBase[]; 
#endif

/*! @brief Table to save XBAR IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_xbarIrqId[];

/*!
 * @brief Defines the type of the user-defined callback function.
 *
 * A prototype for the callback function registered into the XBAR driver.
 */
typedef void (*xbar_callback_t)(void * param);

/*! 
 * @brief Defines the XBAR DMA and interrupt configurations.
 */
/*! 
 * @brief Defines the XBAR DMA and interrupt configurations.
 */
typedef enum _xbar_ien_den_req
{
    kXbarReqDis = 0U, /*!< Interrupt and DMA are disabled. */
    kXbarReqIen = 1U, /*!< Interrupt enabled, DMA disabled. */
    kXbarReqDen = 2U  /*!< DMA enabled, interrupt disabled. */   
} xbar_ien_den_req_t;

/*!
 * @brief Defines the configuration structure of the XBAR control register.
 *
 * This structure keeps the configuration of XBAR control register for one output. 
 * Control registers are available only for a few outputs. Not every XBAR module has 
 *  control registers.
 */
typedef struct XbarControlConfig
{
    xbar_active_edge_t   activeEdge; /*!< Active edge to be detected. */
    xbar_ien_den_req_t   intDmaReq;  /*!< Selects DMA/Interrupt request. */
} xbar_control_config_t;

/*!
 * @brief Internal driver state information.
 *
 * The contents of this structure are internal to the driver and should not be
 * modified by users.
 */
typedef struct XbarState
{
    xbar_callback_t userCallbackFunct[FSL_FEATURE_XBARA_INTERRUPT_COUNT]; /*!< Keep the user-defined callback function. */
    void * xbarCallbackParam[FSL_FEATURE_XBARA_INTERRUPT_COUNT];          /*!< XBAR callback parameter pointer.*/    
} xbar_state_t;

/*! 
 * @brief Macro defines XBARA module number. 
 */
#define XBARA_MODULE    0U

/*! 
 * @brief Macro defines XBARB module number. 
 */
#define XBARB_MODULE    1U

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the XBAR modules.
 * 
 * This function initializes the XBAR module to a reset state. 
 * 
 * @param xbarStatePtr XBAR input signal.
 * @return An error code or kStatus_XBAR_Success.
 */
xbar_status_t XBAR_DRV_Init(xbar_state_t * xbarStatePtr);

/*!
 * @brief Deinitializes the XBAR module.
 * 
 * This function clears all configurations and shuts down the XBAR by disabling interrupt 
 * and the clock signal to the modules.
 */
void XBAR_DRV_Deinit(void);

/*!
 * @brief Configures connection between the selected XBAR_IN[*] input and the XBAR_OUT[*] output signal.
 * 
 * This function configures which XBAR input is connected to the selected XBAR output. 
 * If more than one XBAR module is available, only the inputs and outputs from the same module 
 * can be connected. 
 *
 * Example:
   @code
   xbar_status_t status;

   // Configure connection between XBARA_OUT16(CMP0) output and XBARA_IN1(VDD) input.
   status = XBARA_HAL_ConfigSignalConnection(kXbaraInputVDD, kXbaraOutputCMP0);
   switch (status)
   {
       //... 
   }
   @endcode
 *
 * @param input XBAR input signal.
 * @param output XBAR output signal.
 * @return An error code or kStatus_XBAR_Success.
 */
xbar_status_t XBAR_DRV_ConfigSignalConnection(xbar_input_signal_t input, xbar_output_signal_t output);

/*!
 * @brief Configures the XBAR control register.
 * 
 * This function configures an XBAR control register. The active edge detection 
 * and the DMA/IRQ function on the corresponding XBAR output can be set. 
 *
 * Example:
   @code
   xbar_status_t status;

   // Set the DMA function on XBAR_OUT2 to rising and falling active edges.
   xbar_control_config_t controlOut2;

   controlOut2.activeEdge = kXbarEdgeRisingAndFalling;
   controlOut2.intDmaReq  = kXbarReqDen;

   status = XBAR_DRV_ConfigOutControl(2, controlOut2);
   switch (status)
   {
       //... 
   }
   @endcode
 *
 * @param outIndex XBAR output number.
 * @param controlConfigPtr Pointer to structure that keeps configuration of control register.
 * @return An error code or kStatus_XBAR_Success.
 */
xbar_status_t XBAR_DRV_ConfigOutControl(uint32_t outIndex, const xbar_control_config_t * controlConfigPtr);

/*!
 * @brief Gets the active edge detection status.
 *
 * This function gets the active edge detect status of the desired XBAR_OUT. If the 
 * active edge occurs, the return value is asserted. When the interrupt or the DMA 
 * functionality is enabled for the XBAR_OUTx, this field is 1 when the interrupt 
 * or DMA request is asserted and 0 when the interrupt or DMA request has been 
 * cleared.
 *
 * @param outIndex XBAR output number.
 * @return Assertion of edge detection status.
 */
bool XBAR_DRV_GetEdgeDetectionStatus(uint32_t outIndex);

/*!
 * @brief Clears the status flag of the edge detection status flag for a desired XBAR_OUT.
 *
 * This function clears the status flag of edge detection status flag of the XBAR_OUTx.
 *
 * @param outIndex XBAR output number.
 * @return An error code or kStatus_XBAR_Success.
 */
xbar_status_t XBAR_DRV_ClearEdgeDetectionStatus(uint32_t outIndex);

/*!
 * @brief Installs the callback function for the XBAR module.
 *
 * This function installs the user-defined callback.
 * When the XBAR interrupt request is configured, the callback is executed
 * inside the ISR. 
 *
 * @param outIndex XBAR output number.
 * @param userCallback User-defined callback function.
 * @param callbackParam The XBAR callback parameter pointer.
 * @return An error code or kStatus_XBAR_Success.
 */
xbar_status_t XBAR_DRV_InstallCallback(uint32_t outIndex, xbar_callback_t userCallback, void * callbackParam);

/*!
 * @brief Driver-defined ISR in the XBAR module.
 *
 * This function is the driver-defined ISR in the XBAR module.
 * It includes the process for interrupt mode defined by the driver. Currently, it
 * is called inside the system-defined ISR.
 *
 */
void XBAR_DRV_IRQHandler(void);

#if defined(__cplusplus)
}
#endif

/*
 * @}
 */

#endif
#endif /* __FSL_XBAR_DRIVER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
