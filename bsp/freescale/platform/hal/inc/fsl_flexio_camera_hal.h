/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
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

#ifndef __FSL_FLEXIO_CAMERA_HAL_H__
#define __FSL_FLEXIO_CAMERA_HAL_H__

#include "fsl_flexio_hal.h"
#if FSL_FEATURE_SOC_FLEXIO_COUNT

#if FSL_FEATURE_FLEXIO_HAS_PARALLEL_WIDTH
/* The flexio_camera's function are all build on the parallel mode. */

/*!
 * @addtogroup flexio_camera_hal
 * @{
 */

/* Define the camera CPI interface is constantly 8-bit width. */
#define FLEXIO_CAMERA_PARALLEL_DATA_WIDTH    (8U)

/*!
 * @brief Define structure of configuring the FlexIO camera device. 
 */
typedef struct
{
    FLEXIO_Type * flexioBase; /*!< FlexIO module base address. */
    uint32_t datPinStartIdx;  /*!< First data pin (D0) index for flexio_camera.
                                   Then the successive following FLEXIO_CAMERA_DATA_WIDTH-1 pins
                                   would be used as D1-D7.*/
    uint32_t pclkPinIdx;      /*!< Pixel clock pin (PCLK) index for flexio_camera. */
    uint32_t hrefPinIdx;      /*!< Horizontal sync pin (HREF) index for flexio_camera. */

    uint32_t shifterStartIdx; /*!< First shifter index used for flexio_camera data FIFO. */
    uint32_t shifterCount;    /*!< The count of shifters that are used as flexio_camera data FIFO. */
    uint32_t timerIdx;        /*!< Timer index used for flexio_camera in FlexIO. */
} flexio_camera_dev_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Configures the FlexIO as a flexio_camera device.
 *
 * @param devPtr Pointer to the device.
 * @param configPtr Pointer to configuration structure.
 * @return Execution status.
 */
flexio_status_t FLEXIO_Camera_HAL_Configure(flexio_camera_dev_t *devPtr);

/*!
 * @brief Gets the flag that indicates whether the receive buffer is full.
 *
 * @param devPtr Pointer to the device.
 * @return The mask of shifters that have been filled.
 *
 * Description for mask for the flags:
 *  The mask value: [..., bit2, bit1, bit0] is for 
 *  [... shifterStartIdx+2, shifterStartIdx+1, shifterStartIdx]
 */
uint32_t FLEXIO_Camera_HAL_GetRxBufferFullFlag(flexio_camera_dev_t *devPtr);

/*!
 * @brief Clears the receive buffer full flag manually.
 *
 * @param devPtr Pointer to the device.
 */
void FLEXIO_Camera_HAL_ClearRxBufferFullFlag(flexio_camera_dev_t *devPtr);

/*!
 * @brief Switches on/off the interrupt for receive buffer full event.
 *
 * @param devPtr Pointer to the device.
 * @param syncMsk Mask of trigger for shifters in buffer.
 * @param enable Switcher to the event.
 *
 * Description for syncMask:
 *  The mask value: [..., bit2, bit1, bit0] is for
 *  [... shifterStartIdx+2, shifterStartIdx+1, shifterStartIdx]
 */
void FLEXIO_Camera_HAL_SetRxBufferFullIntCmd(
	flexio_camera_dev_t *devPtr, uint32_t syncMsk, bool enable);

/*!
 * @brief Gets the data from the receive buffer.
 *
 * @param devPtr Pointer to the device.
 * @return datPtr Pointer to the buffer that would keep the data with count of devPtr->shifterCount .
 */
void FLEXIO_Camera_HAL_GetRxBufferData(flexio_camera_dev_t *devPtr, uint32_t *datPtr);

/*!
 * @brief Switches on/off the receive DMA support.
 *
 * @param devPtr Pointer to the device.
 * @param syncMsk Mask of trigger for shifters in buffer.
 * @param enable Switcher to the event.
 *
 * Description for syncMask:
 *  The mask value: [..., bit2, bit1, bit0] is for
 *  [... shifterStartIdx+2, shifterStartIdx+1, shifterStartIdx]
 */
void FLEXIO_Camera_HAL_SetRxBufferDmaCmd(
    flexio_camera_dev_t *devPtr, uint32_t syncMsk, bool enable);

/*!
 * @brief Gets the receive buffer's address for the DMA use.
 *
 * @param devPtr Pointer to the device.
 * @return receive buffer's address.
 */
uint32_t FLEXIO_Camera_HAL_GetRxBufferAddr(flexio_camera_dev_t *devPtr);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_FEATURE_FLEXIO_HAS_PARALLEL_WIDTH */

#endif /* FSL_FEATURE_SOC_FLEXIO_COUNT */
#endif /* __FSL_FLEXIO_CAMERA_HAL_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

