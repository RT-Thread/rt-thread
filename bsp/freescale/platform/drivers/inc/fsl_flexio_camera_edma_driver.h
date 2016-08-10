/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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

#ifndef __FSL_FLEXIO_CAMERA_EDMA_DRIVER_H__
#define __FSL_FLEXIO_CAMERA_EDMA_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>

#include "fsl_flexio_camera_hal.h"
#include "fsl_flexio_driver.h"
#include "fsl_edma_hal.h"
#include "fsl_edma_driver.h"

#if FSL_FEATURE_SOC_FLEXIO_COUNT && FSL_FEATURE_SOC_EDMA_COUNT && FSL_FEATURE_FLEXIO_HAS_PARALLEL_WIDTH

/*!
 * @addtogroup flexio_camera_edma_driver
 * @{
 */

/*!
 * @brief Defines the count of FlexIO shifters in use.
 */
#define FSL_FLEXIO_CAMERA_USING_SHIFTER_COUNT  8U

/*******************************************************************************
 * Enumeration.
 ******************************************************************************/

/*!
 * @brief Flexio_Camera status return codes.
 */
typedef enum _flexio_camera_status
{
    kStatus_FlexIO_Camera_Success         = 0U, /*!< Success. */
    kStatus_FlexIO_Camera_InvalidArgument = 1U, /*!< Invalid argument exists. */
    kStatus_FlexIO_Camera_Failed          = 2U  /*!< Execution failed. */
} flexio_camera_status_t;

/*******************************************************************************
 * Structure.
 ******************************************************************************/
/*!
* @brief Defines the structure to configure the FlexIO for flexio_camera.
*/
typedef struct FlexioCameraHwConfig
{
    uint32_t flexioInstance; /*!< Instance of FlexIO device. */
    
    /* Pins. */
    uint32_t datPinStartIdx;  /*!< First data pin (D0) index for flexio_camera.
                                   Then the successive following FLEXIO_CAMERA_DATA_WIDTH-1 pins
                                   is used as D1-D7.*/
    uint32_t pclkPinIdx;      /*!< Pixel clock pin (PCLK) index for flexio_camera. */
    uint32_t hrefPinIdx;      /*!< Horizontal sync pin (HREF) index for flexio_camera. */

    /* Shifters. */
    uint32_t shifterStartIdx; /*!< First shifter index used for flexio_camera data FIFO. */
    
    /* Timers. */
    uint32_t timerIdx;        /*!< Timer index used for flexio_camera in FlexIO. */
} flexio_camera_user_config_t;

/*!
* @brief Defines the structure to configure the eDMA for flexio_camera.
*/
typedef struct CameraEdmaConfig
{
    edma_channel_indicator_t userEdmaChn;    /*!< Indicated eDMA channel for flexio_camera.  */
    uint32_t                 userBufAddr;    /*!< Pointer to the user buffer. */
    uint32_t                 userBufLenByte; /*!< Length of the user buffer in bytes. */
} camera_edma_user_config_t;

/*!
 * @brief Defines the structure to handle the flexio_camera device.
 *
 * Users do not have to be familiar with every field in this structure,
 * because the driver maintains them. However, users must
 * allocate memory for the handler structure. 
 */
typedef struct FlexioCameraEdmaHandler
{
    /* flexio_camera_interface. */
    flexio_camera_dev_t     flexioCameraHwConfig; /*!< Keeps the original configuration for flexio_camera interface. */
    
    /* edma configure. */
    edma_chn_state_t         rxEdmaChnState; /*!< Keeps the run-time parameter. */
    edma_channel_indicator_t userEdmaChn;    /*!< Indicates the eDMA channel for FlexIO.  */
    uint32_t                 userBufAddr;    /*!< Pointer to the user buffer. */
    uint32_t                 userBufLenByte; /*!< Length of the user buffer in bytes. */
} flexio_camera_edma_handler_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API.
 ******************************************************************************/

/*!
 * @brief Initializes the flexio_camera_edma device.
 *
 * This function configures the FLEXIO as a CPI interface with the indicated
 * eDMA channel moving data from the FlexIO interface to the user defined memory.
 * With this function, an image of the camera sensor can be mapped into the user-defined
 * memory. Then, the user can read the mapped memory any time in the application.
 * Note: 
 *     The selection of the eDMA channel is limited to a specific range for each chip.
 *     Ensure that the channel can be used by checking the reference
 *     manual. Usually, channels 16 - 31 are available.
 *     
 *
 * @param handler A pointer to the structure that handles the flexio_camera_edma device.
 * @param userFlexioCameraConfigPtr A pointer to the configuration structure for the FlexIO interface.
 * @param userEdmaConfigPtr A pointer to the configuration structure for eDMA.
 * @return Execution status.
 */
flexio_camera_status_t FLEXIO_Camera_DRV_InitEdmaRx(
                flexio_camera_edma_handler_t *handler,                   /* Output. */
                flexio_camera_user_config_t  *userFlexioCameraConfigPtr, /* Input. */
                camera_edma_user_config_t    *userEdmaConfigPtr );       /* Input. */

/*!
 * @brief Deinitializes the flexio_camera_edma device.
 *
 * This function shuts down the flexio_camera_edma device. It  releases
 * the EDMA channel used in the flexio_camera_edma device and stops generating the
 * DMA trigger from the flexio_camera interface.
 *
 * @param handler A pointer to the structure that keeps all the information of device.
 * @return Execution status.
 */
flexio_camera_status_t FLEXIO_Camera_DRV_DeinitEdmaRx(
                flexio_camera_edma_handler_t *handler );

/*!
 * @brief Resets the eDMA transfer loop when moving data.
 *
 * This function resets the eDMA transfer loop's destination address and the loop
 * counter, which means that the eDMA transfer is reset to its initialized state.
 * This API is called when VSYNC event occurs to make sure that the data
 * from the camera is not lost. However, if an application
 * configuration accomplishes the same task, this API is not necessary.
 *
 * @param handler A pointer to the structure that keeps all  information from the device.
 * @return Execution status.
 */
flexio_camera_status_t FLEXIO_Camera_DRV_ResetEdmaRx(
                flexio_camera_edma_handler_t *handler ) ;

/*!
 * @brief Starts the flexio_camera_edma device.
 *
 * This function starts the flexio_camera_edma device. After initialization,
 * the eDMA is triggered and starts the transfer by calling this API. Then,
 * the memory mapping can be executed.
 *
 * @param handler A pointer to the structure that keeps all  information for the device.
 * @return Execution status.
 */
flexio_camera_status_t FLEXIO_Camera_DRV_StartEdmaRx(
                flexio_camera_edma_handler_t *handler );

/*!
 * @brief Sets the flexio_camera's DMA trigger if more DMA triggers are needed in the application.
 *
 * This function  sets the flexio_camera's DMA trigger if
 * more DMA triggers are needed in the application. In some situations, another DMA channel is needed
 * to move data from the user-defined memory to a different
 * device, such as the LCD screen. This function  provides a method to generate asynchronous
 * trigger from the flexio_camera interface's buffer.
 *
 * @param handler A pointer to the structure that keeps all information for the device.
 * @param syncMsk The mask for flexio_camera's buffer's shifter to generate the DMA trigger.
 * @param enable true if enable the trigger or not.
 */
void FLEXIO_Camera_DRV_SetBufferTriggerForExtEdma(
                flexio_camera_edma_handler_t *handler, uint32_t syncMsk, bool enable );

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_FLEXIO_COUNT && FSL_FEATURE_SOC_EDMA_COUNT*/

#endif /* __FSL_FLEXIO_CAMERA_DRIVER_H__*/

