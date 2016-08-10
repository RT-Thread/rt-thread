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


#ifndef __FSL_SAI_DRIVER_H__
#define __FSL_SAI_DRIVER_H__

#include "fsl_sai_hal.h"
#include "fsl_os_abstraction.h"
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
#include "fsl_edma_driver.h"
#else
#include "fsl_dma_driver.h"
#endif

#if FSL_FEATURE_SOC_I2S_COUNT

/*!
 * @addtogroup sai_driver
 * @{ 
 */

/*! @file */

/*! @brief SAI callback function */
typedef void (*sai_callback_t)(void *parameter);
extern I2S_Type * const g_saiBase[I2S_INSTANCE_COUNT];
extern const IRQn_Type g_saiTxIrqId[I2S_INSTANCE_COUNT];
extern const IRQn_Type g_saiRxIrqId[I2S_INSTANCE_COUNT];

/*! @brief Status structure for SAI */
typedef enum _sai_status
{
    kStatus_SAI_Success = 0U,
    kStatus_SAI_Fail = 1U,
    kStatus_SAI_DeviceBusy = 2U
} sai_status_t;

/*! @brief Defines the PCM data format
 *  @internal gui name="Audio data configuration" id="saiDataCfg"
 */
typedef struct SaiAudioDataFormat
{
    uint32_t sample_rate;/*!< Sample rate of the PCM file. @internal gui name="Sample rate" id="SampleRate" default="48000" */
    uint32_t mclk;/*!< Master clock frequency. @internal gui name="Master clock frequency" id="CfgMclk" */
    uint8_t  bits;/*!< Number of bits in a word. @internal gui name="Bits" id="Bits" default="32" */
    sai_mono_stereo_t  mono_stereo;/*!< Number of words in a frame. @internal gui name="Mode" id="Words" default="1" */
} sai_data_format_t;

/*! @brief SAI internal state 
* Users should allocate and transfer memory to the PD during the initialization function.
* Note: During the SAI execution, users should not free the state. Otherwise, the driver malfunctions.
*/
typedef struct sai_state
{
    sai_data_format_t format;
    uint8_t * address;
    uint32_t len;
    uint32_t count;
    sai_callback_t  callback;
    void * callback_param;
    sai_sync_mode_t sync_mode;
    uint32_t fifo_channel;
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    uint32_t watermark;
#endif
    sai_master_slave_t master_slave;
    sai_protocol_t protocol;
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
    edma_chn_state_t edma_chn;
    edma_software_tcd_t tcd[2];
#else
    dma_channel_t chn;
#endif
    semaphore_t sem;
    bool use_dma;
    uint32_t dma_source;
} sai_state_t;

/*! @brief The description structure for the SAI transmit/receive module.
 *  @internal gui name="Basic configuration" id="saiCfg"
 */
typedef struct SaiUserConfig
{
    sai_mclk_source_t   mclk_source;/*!< Master clock source. @internal gui name="MCLK source" id="CfgMclkSource" */
    uint8_t             channel;/*!< Which FIFO is used to transfer. @internal gui name="Channel" id="Channel" */
    sai_sync_mode_t     sync_mode;/*!< Synchronous or asynchronous. @internal gui name="Mode" id="Mode" */
    sai_protocol_t           protocol;/*!< I2S left, I2S right, or I2S type. @internal gui name="Protocol" id="BusType" default="2" */
    sai_master_slave_t  slave_master;/*!< Master or slave. @internal gui name="Master / Slave mode" id="MasterSlave" */
    sai_bclk_source_t   bclk_source;/*!< Bit clock from master clock or other modules. @internal gui name="Bit clock source" id="BclkSource" default="1" */
#if FSL_FEATURE_SAI_FIFO_COUNT > 1
    uint32_t    watermark;/*!< Time when to send an interrupt or the DMA request. @internal gui name="Watermark" id="Watermark" */
#endif
    uint32_t    dma_source; /*!< The DMA request source. @internal gui name="DMA request value" id="DmaRequest" */
}  sai_user_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the SAI module.
 *
 * This  function  initializes the SAI registers according to the configuration
 * structure. This function also initializes the basic SAI settings including
 * board-relevant settings.
 * Notice: This function does not initialize an entire SAI instance. It
 * only initializes the transmit according to the value in the handler.
 * @param instance SAI module instance.
 * @param config The configuration structure of SAI.
 * @param state Pointer of SAI run state structure.
 * @return Return kStatus_SAI_Success while the initialize success and kStatus_SAI_Fail if failed.
 */
sai_status_t SAI_DRV_TxInit(uint32_t instance, sai_user_config_t * config, sai_state_t *state);

/*!
 * @brief Initializes the SAI receive module.
 *
 * This  function  initializes the SAI registers according to the configuration
 * structure. This function also initializes the basic SAI settings including
 * board-relevant settings.
 * Note that this function does not initialize an entire SAI instance. This function
 * only initializes the transmit according to the value in the handler.
 * @param instance SAI module instance.
 * @param config The configuration structure of SAI.
 * @param state Pointer of SAI run state structure.
 * @return Return kStatus_SAI_Success while the initialize success and kStatus_SAI_Fail if failed.
 */
sai_status_t SAI_DRV_RxInit(uint32_t instance, sai_user_config_t * config, sai_state_t *state);

/*! @brief Gets the default setting of the user configuration.
* 
* The default settings for SAI are:
* - Audio protocol is I2S format
* - Watermark is 4
* - Use SAI0
* - Channel is channel0
* - SAI as master 
* - MCLK from system core clock
* - Transmit is in an asynchronous mode
* @param config Pointer of user configure structure.
*/
void SAI_DRV_TxGetDefaultSetting(sai_user_config_t *config);

/*! @brief Gets the default settings of the user configuration.
* 
* The default settings for SAI are:
* Audio protocol is I2S format
* Watermark is 4
* Use SAI0
* Data channel is channel0
* SAI as master
* MCLK from system core clock
* Receive is in synchronous way
* @param config Pointer of user configure structure.
*/
void SAI_DRV_RxGetDefaultSetting(sai_user_config_t *config);

/*!
 * @brief De-initializes the SAI transmit module.
 *
 * This function  closes the SAI transmit device, but does not close the entire SAI instance.
 * It only closes the clock gate while both transmit and receive are closed in the same instance.
 * @param instance SAI module instance.
 * @return Return kStatus_SAI_Success while the process success and kStatus_SAI_Fail if failed.
 */
sai_status_t SAI_DRV_TxDeinit(uint32_t instance);

/*!
 * @brief Deinitializes the SAI receive module.
 *
 * This function closes the SAI receive device, but does not close the entire SAI instance.
 * It only closes the clock gate while both transmit and receive are closed in the same instance.
 * @param instance SAI module instance.
 * @return Return kStatus_SAI_Success while the process success and kStatus_SAI_Fail if failed.
 */
sai_status_t SAI_DRV_RxDeinit(uint32_t instance);

/*!
 * @brief Configures the audio data format of the transmit.
 *
 * The function  configures  an audio sample rate, data bits, and a channel number.
 * @param instance SAI module instance.
 * @param format PCM data format structure pointer.
 * @return Return kStatus_SAI_Success while the process success and kStatus_SAI_Fail if failed.
 */
sai_status_t SAI_DRV_TxConfigDataFormat(uint32_t instance,sai_data_format_t *format);

/*!
 * @brief Configures the audio data format of the receive.
 *
 * The function  configures  an audio sample rate, data bits, and a channel number.
 * @param instance SAI module instance of the SAI module.
 * @param format PCM data format structure pointer.
 * @return Return kStatus_SAI_Success while the process success and kStatus_SAI_Fail if failed.
 */
sai_status_t SAI_DRV_RxConfigDataFormat(uint32_t instance,sai_data_format_t *format);

/*!
 * @brief Starts the transmit transfer.
 *
 * The function  enables the interrupt/DMA request source and the transmit channel.
 * @param instance SAI module instance.
 */
void SAI_DRV_TxStartModule(uint32_t instance);

/*!
 * @brief Starts the receive process.
 *
 * The function  enables the interrupt/DMA request source and the transmit channel.
 * @param instance SAI module instance of the SAI module.
 */
void SAI_DRV_RxStartModule(uint32_t instance);

/*!
 * @brief Stops writing data to FIFO to disable the DMA or the interrupt request bit.
 *
 * This function provides the method to pause writing data.  
 * @param instance SAI module instance.
 */
void SAI_DRV_TxStopModule(uint32_t instance);

/*!
 * @brief Stops receiving data from FIFO to disable the DMA or the interrupt request bit.
 *
 * This function provides the method to pause writing data.  
 * @param instance SAI module instance.
 */
void SAI_DRV_RxStopModule(uint32_t instance);

/*! @brief Enables or disables the transmit interrupt source.
* @param instance SAI module instance.
* @param enable True means enable interrupt source, false means disable interrupt source.
*/
void SAI_DRV_TxSetIntCmd(uint32_t instance, bool enable);

/*! @brief Enables or disables the receive interrupt source.
* @param instance SAI module instance.
* @param enable True means enable interrupt source, false means disable interrupt source.
*/
void SAI_DRV_RxSetIntCmd(uint32_t instance, bool enable);

/*! @brief Enables or disables the transmit DMA source.
* @param instance SAI module instance.
* @param enable True means enable DMA source, false means disable DMA source.
*/
void SAI_DRV_TxSetDmaCmd(uint32_t instance,  bool enable);

/*! @brief Enables or disables the receive interrupt source.
* @param instance SAI module instance.
* @param enable True means enable DMA source, false means disable DMA source.
*/
void SAI_DRV_RxSetDmaCmd(uint32_t instance, bool enable);

#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
/*! @brief Sets the transmit watermark.
*
* When the data number in FIFO is less or equal to the watermark, an interrupt is generated.
* request or the DMA request.
* @param instance SAI module instance.
* @param watermark Watermark number needs to set.
*/
void SAI_DRV_TxSetWatermark(uint32_t instance,uint32_t watermark);

/*! @brief Sets the receive watermark.
*
* When the data number in FIFO is greater than or equal to the watermark, an interrupt is generated.
* request or the DMA request.
* @param instance SAI module instance.
* @param watermark Watermark number needs to set.
*/
void SAI_DRV_RxSetWatermark(uint32_t instance,uint32_t watermark);

/*! @brief Gets the transmit watermark.
*
* The watermark should be changed according to a different audio sample rate.
* @param instance SAI module instance.
* @return Watermark number in TCR1.
*/
static inline uint32_t SAI_DRV_TxGetWatermark(uint32_t instance)
{
    I2S_Type * reg_base = g_saiBase[instance];
    return SAI_HAL_TxGetWatermark(reg_base);
}

/*! @brief Gets the receive watermark.
*
* The watermark should be changed according to a different audio sample rate.
* @param instance SAI module instance.
* @return Watermark number in RCR1.
*/
static inline uint32_t SAI_DRV_RxGetWatermark(uint32_t instance)
{
    I2S_Type * reg_base = g_saiBase[instance];
    return SAI_HAL_RxGetWatermark(reg_base);
}
#endif

/*!
 * @brief Gets the transmit FIFO address of the data channel.
 *
 * This function is mainly used for the DMA settings which the DMA
 * configuration needs for the SAI source/destination address.
 * @param instance SAI module instance of the SAI module.
 * @param fifo_channel FIFO channel of SAI transmit.
 * @return Returns the address of the data channel FIFO.
 */
static inline uint32_t SAI_DRV_TxGetFifoAddr(uint32_t instance, uint32_t fifo_channel)
{
    I2S_Type * reg_base = g_saiBase[instance];
    return SAI_HAL_TxGetFifoAddr(reg_base, fifo_channel);
}

/*!
 * @brief Gets the receive FIFO address of the data channel.
 *
 * This function is mainly used for the DMA settings which the DMA
 * configuration needs for the SAI source/destination address.
 * @param instance SAI module instance of the SAI module.
 * @param fifo_channel FIFO channel of SAI receive.
 * @return Returns the address of the data channel FIFO.
 */
static inline uint32_t SAI_DRV_RxGetFifoAddr(uint32_t instance, uint32_t fifo_channel)
{
    I2S_Type * reg_base = g_saiBase[instance];
    return SAI_HAL_RxGetFifoAddr(reg_base, fifo_channel);
}

/*!
 * @brief Sends data using interrupts.
 *
 * This function  sends data to the transmit FIFO. This function  
 * starts the transfer, and, while finishing the transfer, calls the callback
 * function registered by users. This function is an un-blocking function.
 * @param instance SAI module instance of the SAI module.
 * @param addr Address of the data which needs to be transferred.
 * @param len The number of bytes which need to be sent.
 * @return Returns the length which was sent.
 */
uint32_t SAI_DRV_SendDataInt(uint32_t instance, uint8_t *addr, uint32_t len);

/*!
 * @brief Receives data a certain length using interrupt way.
 *
 * This function  receives the data from the receive FIFO. This function  
 * starts the transfer, and, while finishing the transfer,  calls the callback
 * function registered by the user. This function is an un-blocking function.
 * @param instance SAI module instance.
 * @param addr Address of the data which needs to be transferred.
 * @param len  The number of bytes to receive.
 * @return Returns the length received.
 */
uint32_t SAI_DRV_ReceiveDataInt(uint32_t instance, uint8_t *addr, uint32_t len);

/*!
 * @brief Sends data of a certain length using the DMA method.
 *
 * This function  sends the data to the transmit FIFO. It  
 * starts the transfer, and, while finishing the transfer, calls the callback
 * function registered by users. This function is an a-sync function.
 * @param instance SAI module instance of the SAI module.
 * @param addr Address of the data which needs to be transferred.
 * @param len The number of bytes which need to be sent.
 * @return Returns the length which was sent.
 */
uint32_t SAI_DRV_SendDataDma(uint32_t instance, uint8_t *addr, uint32_t len);

/*!
 * @brief Receives data using the DMA.
 *
 * This function  receives the data from the receive FIFO. It  
 * starts the transfer, and, while finishing the transfer,  calls the callback
 * function registered by the user. This function is an a-sync function.
 * @param instance SAI module instance.
 * @param addr Address of the data which needs to be transferred.
 * @param len  The number of bytes to receive.
 * @return Returns the length received.
 */
uint32_t SAI_DRV_ReceiveDataDma(uint32_t instance, uint8_t *addr, uint32_t len);

/*!
 * @brief Registers the callback function after completing a send.
 *
 * This function  tells the SAI which function needs to be called after a 
 * period length sending. This callback function is used for non-blocking sending.
 * @param instance SAI module instance.
 * @param callback Callback function defined by users.
 * @param callback_param The parameter of the callback function.
 */
void SAI_DRV_TxRegisterCallback(uint32_t instance, sai_callback_t callback, void *callback_param);

/*!
 * @brief Registers the callback function after completing a receive.
 *
 * This function  tells the SAI which function needs to be called after a 
 * period length receive. This callback function is used for non-blocking receiving.
 * @param instance SAI module instance.
 * @param callback Callback function defined by users.
 * @param callback_param The parameter of the callback function.
 */
void SAI_DRV_RxRegisterCallback(uint32_t instance, sai_callback_t callback, void *callback_param);

/*!
 * @brief Default SAI transmit interrupt handler.
 *
 * This function sends data in the interrupt and checks the FIFO error.
 * @param instance SAI module instance.
 */
void SAI_DRV_TxIRQHandler(uint32_t instance);

/*!
 * @brief Default SAI receive interrupt handler.
 *
 * This function receives data in the interrupt and checks the FIFO error.
 * @param instance SAI module instance.
 */
void SAI_DRV_RxIRQHandler(uint32_t instance);


#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
#endif/* __FSL_SAI_DRIVER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

