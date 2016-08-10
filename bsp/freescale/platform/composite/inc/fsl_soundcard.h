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

#ifndef __FSL_SOUNDCARD_H__
#define __FSL_SOUNDCARD_H__

#include "fsl_os_abstraction.h"
#include "fsl_edma_driver.h"
#include "fsl_sai_driver.h"
#include "fsl_sgtl5000_driver.h"

/*!
 * @addtogroup soundcard
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define USEDMA 1/*!< Use DMA mode or interrupt mode. */
#define SOUNDCARD_USE_STATIC_MEM 1 /*!< This macro controls using static memory or dynamic allocate. */

#define AUDIO_CONTROLLER    AUDIO_CONTROLLER_SAI /*!< Define audio controller sai */
#define AUDIO_CONTROLLER_SAI    1
#define AUDIO_CONTROLLER_NUM  I2S_INSTANCE_COUNT

#define AUDIO_CODEC AUDIO_CODEC_SGTL5000 /*!< Define audio codec sgtl5000 */
#define AUDIO_CODEC_SGTL5000    1

#define AUDIO_BUFFER_BLOCK_SIZE     1024 /*!< Buffer block size setting */
#define AUDIO_BUFFER_BLOCK              2 /*!< Buffer block number setting */
#define AUDIO_BUFFER_SIZE         (AUDIO_BUFFER_BLOCK * AUDIO_BUFFER_BLOCK_SIZE)

#define AUDIO_TX    1 /*!< Audio transfer direction Tx */
#define AUDIO_RX    0 /*!< Audio transfer direction Rx */

#if AUDIO_CONTROLLER == AUDIO_CONTROLLER_SAI
typedef sai_user_config_t ctrl_config_t;
typedef sai_data_format_t ctrl_data_format_t;
typedef sai_callback_t ctrl_callback_t;
typedef sai_status_t ctrl_status_t;
typedef sai_state_t ctrl_state_t;
#define AUDIO_FIFO_LEN FSL_FEATURE_SAI_FIFO_COUNT
#endif

#if AUDIO_CODEC == AUDIO_CODEC_SGTL5000
typedef sgtl_handler_t codec_handler_t;
typedef sgtl_status_t codec_status_t;
typedef sgtl_init_t codec_init_t;
#endif

/*! @brief Soundcard return status */
typedef enum _snd_status
{
    kStatus_SND_Success = 0U, /*!< Execute successfully*/
    kStatus_SND_Fail = 1U, /*!< Execute fail */
    kStatus_SND_DmaFail = 2U, /*!< DMA operation fail */
    kStatus_SND_CtrlFail = 3U, /*!< Audio controller operation fail */
    kStatus_SND_CodecFail = 4U, /*!< Audio codec operation fail */
    kStatus_SND_BufferAllocateFail = 5U /*!< Buffer allocate failure */
} snd_status_t;

/*!
 * @brief Soundcard status includes the information which the application can see.
 * This structure is the interface between the driver and the application. The application can get the 
 * information where and when to input/output data.
 */
 typedef struct SoundcardState
{
    uint32_t size; /*!< The size of a block */
    uint32_t empty_block; /*!< How many blocks are empty */
    uint32_t full_block; /*!< How many blocks are full */
    uint8_t *input_address; /*!< The input address */
    uint8_t *output_address; /*!< The output address */
} snd_state_t;

/*!
 * @brief The operations of an audio controller, for example SAI, SSI and so on. 
 * The operation includes the basic initialize, configure, send, receive and so on.
 */
typedef struct AudioControllerOperation
{
    ctrl_status_t (*Ctrl_TxInit)(uint32_t instance,ctrl_config_t * config, ctrl_state_t *state);/*!< Initializes Tx. */
    ctrl_status_t (*Ctrl_RxInit)(uint32_t instance,ctrl_config_t * config, ctrl_state_t *state);/*!< Initializes Rx. */ 
    ctrl_status_t (*Ctrl_TxDeinit)(uint32_t instance);/*!< Deinitializes Tx. */
    ctrl_status_t (*Ctrl_RxDeinit)(uint32_t instance);/*!< Deinitializes Rx. */
    ctrl_status_t (*Ctrl_TxConfigDataFormat)(uint32_t instance,  
        ctrl_data_format_t *format);/*!< Configures Tx audio data format. */
    ctrl_status_t (*Ctrl_RxConfigDataFormat)(uint32_t instance,  
        ctrl_data_format_t *format);/*!< Configures Rx audio data format. */    
    void (*Ctrl_TxStart)(uint32_t instance);/*!< Used in a start transfer or a resume transfer*/
    void (*Ctrl_RxStart)(uint32_t instance);/*!< Used in a start receive or a resume receive*/
    void (*Ctrl_TxStop)(uint32_t instance);/*!< Used to stop transfer. */
    void (*Ctrl_RxStop)(uint32_t instance);/*!< Used to stop receive. */
    void (*Ctrl_TxRegisterCallback)(uint32_t instance, ctrl_callback_t callback, 
        void *callback_param); /*!< Registers a tx callback function. */
    void (*Ctrl_RxRegisterCallback)(uint32_t instance, ctrl_callback_t callback, 
        void *callback_param); /*!< Registers an rx callback function. */
    void (*Ctrl_TxSetIntCmd)(uint32_t instance, bool enable); /*!< Enable/disable Tx interrupt. */
    void (*Ctrl_RxSetIntCmd)(uint32_t instance, bool enable); /*!< Enable/disable Rx interrupt. */
    void (*Ctrl_TxSetDmaCmd)(uint32_t instance, bool enable); /*!< Enable/disable Tx DMA. */
    void (*Ctrl_RxSetDmaCmd)(uint32_t instance, bool enable); /*!< Enable/disable Rx DMA. */
    uint32_t (*Ctrl_TxGetWatermark)(uint32_t instance); /*!< Get watermark of T. */
    uint32_t (*Ctrl_RxGetWatermark)(uint32_t instance); /*!< Get watermark of Rx. */
    uint32_t (*Ctrl_TxGetFifoAddr)(uint32_t instance,uint32_t fifo_channel); /*!< Gets Tx FIFO address */
    uint32_t (*Ctrl_RxGetFifoAddr)(uint32_t instance,uint32_t fifo_channel); /*!< Gets Rx FIFO address */
    uint32_t (*Ctrl_SendData)(uint32_t instance, uint8_t *addr, uint32_t len); /*!< Sends data function*/
    uint32_t (*Ctrl_ReceiveData)(uint32_t instance, uint8_t *addr, uint32_t len); /*!< Receives data*/
} audio_ctrl_operation_t;

/*! @brief Audio codec operation structure. */
typedef struct AudioCodecOperation
{
    codec_status_t (*Codec_Init)(codec_handler_t *param, codec_init_t *config); /*!< Codec initialize function*/
    codec_status_t (*Codec_Deinit)(codec_handler_t  *param); /*!< Codec deinitialize function */
    codec_status_t (*Codec_ConfigDataFormat)(codec_handler_t  *param, 
        uint32_t mclk, uint32_t sample_rate, uint8_t bits ); /*!< Configures data format. */
    codec_status_t (*Codec_SetMuteCmd)(codec_handler_t *param,  bool enable);/*!< Mute and unmute. */
    codec_status_t (*Codec_SetVolume)(codec_handler_t *param, uint32_t volume); /*!< Set volume. */
    uint32_t (*Codec_GetVolume)(codec_handler_t *param);/*!< Get volume. */
} audio_codec_operation_t;


/*! @brief The definition of the audio device which may be a controller. */
typedef struct AudioController
{
    uint32_t instance;
    uint32_t fifo_channel;
#if USEDMA
    edma_chn_state_t       dma_channel;/*!< Which DMA channel it uses */
    dma_request_source_t dma_source; /*!< DMA request source */
    edma_software_tcd_t  stcd[AUDIO_BUFFER_BLOCK + 1];    /*!< TCDs for eDMA configuration. */
#endif
    audio_ctrl_operation_t *ops;/*!< Operations including initialization, configuration, etc.*/
} audio_controller_t;

/*! @brief The Codec structure. */
typedef struct AudioCodec
{  
    void *handler;/*!< Codec instance */
    audio_codec_operation_t *ops;/*!< Operations. */
}audio_codec_t;

/*! @brief  Audio buffer structure */
typedef struct Audio_Buffer{
    /* Buffer resources */
    uint8_t*   buff;/*!< Buffer address */
    /* Buffer configuration information */
    uint8_t    blocks;/*!< Block number of the buffer. */
    uint16_t   size;/*!< The size of a block */
    /* Buffer status information */
    uint32_t   requested;/*!< The request data number to transfer */
    uint32_t   queued;/*!< Data which is in buffer, but not processed. */
    uint32_t   processed;/*!< Data which is  put into the FIFO.
                             This is used to judge if the SAI is under run. */
    uint8_t    input_index; /*!< Buffer input block index. */
    uint8_t    output_index; /*!< Buffer output block index. */
    uint8_t*   input_curbuff; /*!< Buffer input address. */
    uint8_t*   output_curbuff; /*!< Buffer output address. */
    uint32_t   empty_block; /*!< Empty block number. */
    uint32_t   full_block; /*!< Full block numbers. */
    uint32_t   fifo_error; /*!< FIFO error numbers. */
    uint32_t   buffer_error; /*!< Buffer error numbers. */
    semaphore_t sem; /*!<  Semaphores to control the data flow. */
    bool       first_io;/*!< Means the first time the transfer */
}audio_buffer_t;

/*!
 * @brief A sound card includes the audio controller and a Codec. 
 */
typedef struct Soundcard
{
    audio_controller_t controller;/*!< Controller */ 
    audio_codec_t codec;/*!< Codec */
    audio_buffer_t buffer; /*!< Audio buffer managed by the Soundcard. */
} sound_card_t;

extern audio_ctrl_operation_t g_sai_ops;
extern audio_codec_operation_t g_sgtl_ops;
/*******************************************************************************
 * APIs
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the Playback Soundcard. The function  initializes the controller and the codec.
 *
 * The function  initializes the generic layer structure, for example the buffer and the
 * status structure. Then, the function  calls the initialize functions of the controller and the codec.
 * @param card Soundcard pointer
 * @param ctrl_config The configuration structure of the audio controller
 * @param codec_config The configuration structure of the audio Codec
 * @param state The audio controller state structure needed in transfer.
 * @return Return kStatus_SND_Success while the initialize success and kStatus_SND_fail if failed.
 */
snd_status_t SND_TxInit(
   sound_card_t *card, void * ctrl_config, void * codec_config, ctrl_state_t *state);

/*!
* @brief Initializes the record Soundcard. The function  initializes the controller and the codec.
*
* The function  initializes the generic layer structure, for example the buffer and the
* status structure. Then, the function  calls the initialize functions of the controller and the codec.
* @param card Soundcard pointer
* @param ctrl_config The configuration structure of the audio controller
* @param codec_config The configuration structure of the audio Codec
* @param state The audio controller state structure needed in transfer.
* @return Return kStatus_SND_Success while the initialize success and kStatus_SND_fail if failed.
*/
snd_status_t SND_RxInit(
    sound_card_t *card, void * ctrl_config, void * codec_config, ctrl_state_t *state);

/*!
 * @brief Deinitializes the playback Soundcard.
 *
 * The function  calls the codec and controller deinitialization function and frees the buffer controlled by
 * the Soundcard. The function should be used at the end of the application. If the
 * playback/record is paused, do not use the function. Instead, use the snd_stop_tx/snd_stop_rx.
 * 
 * @param card Soundcard pointer
 * @return Return kStatus_SND_Success while the initialize success and kStatus_SND_fail if failed.
 */
snd_status_t SND_TxDeinit(sound_card_t *card);

/*!
 * @brief Deinitializes the playback Soundcard.
 *
 * The function  calls the codec and the controller deinitialization function and frees the buffer controlled by
 * the Soundcard. The function should be used at the end of the application. If the
 * playback/record is paused, do not use the function. Instead, use the snd_stop_tx/snd_stop_rx.
 *
 * @param card Soundcard pointer
 * @return Return kStatus_SND_Success while the initialize success and kStatus_SND_fail if failed.
 */
snd_status_t SND_RxDeinit(sound_card_t *card);

/*!
 * @brief Configures the audio data format running in the Soundcard.
 *
 * This function can make the application change the data format during  run time.
 * This function cannot be called while either the TCSR.TE or RCSR.RE are enabled.
 * This function can change the sample rate, bit depth, such as the 16-bit. 
 * @param card Soundcard pointer
 * @param format Data format used in the sound card
 * @return Return kStatus_SND_Success while the initialize success and kStatus_SND_fail if failed.
 */
snd_status_t SND_TxConfigDataFormat(sound_card_t *card, ctrl_data_format_t *format);

/*!
 * @brief Configures the audio data format running in the Soundcard.
 *
 * This function can make the application change the data format during the run time.
 * This function cannot be called while either the TCSR.TE or the RCSR.RE are enabled.
 * This function can change the sample rate, bit depth(i.e. 16-bit).
 * @param card Soundcard pointer
 * @param format Data format used in the sound card
 * @return Return kStatus_SND_Success while the initialize success and kStatus_SND_fail if failed.
 */
snd_status_t SND_RxConfigDataFormat(sound_card_t *card, ctrl_data_format_t *format);

/*!
 * @brief Updates the status of the TX.
 *
 * This function should be called after the application copied data into the buffer provided
 * by the Soundcard. The Soundcard does not copy data to the internal buffer. This
 * operation should be done by the applications. The Soundcard  provides an interface
 * ,snd_get_status(), for an application to get the information about the internal buffer
 * status, including the starting address and empty blocks.
 * @param card Soundcard pointer
 * @param len Data size of the data to write
 * @return The size which has been written.
 */
uint32_t SND_TxUpdateStatus(sound_card_t *card, uint32_t len);

/*!
 * @brief Updates the status of the Rx.
 *
 * This function should be called after the application copied data into the buffer provided
 * by the Soundcard. The Soundcard does not help users  copy data to the internal buffer. This
 * operation should be done by the applications. The Soundcard  provides an interface
 * ,snd_get_status(), for an application to get the information about the internal buffer
 * status, including the starting address and empty blocks and so on.
 * @param card Soundcard pointer
 * @param len Data size of the data to write
 * @return The size which has been written.
 */
uint32_t SND_RxUpdateStatus(sound_card_t *card, uint32_t len);


/*!
 * @brief Gets the status of the Soundcard.
 *
 * Each time the application wants to write/read data from the internal buffer, it
 * should call this function to get the status of the internal buffer. This function 
 * copies data to the @param status from the structure. The user can get the information
 * about where to write/read data and how much data can be read/written.
 * @param card Soundcard pointer
 * @param status Pointer of the audio_status_t structure
 * @param card Soundcard pointer
 */
void SND_GetStatus(sound_card_t *card, snd_state_t *status);

/*!
 * @brief Starts the Soundcard Tx process.
 *
 * This function starts the Tx process of the Soundcard. This function  enables the
 * DMA/interrupt request source and enables the Tx and the bit clock of the Tx. Note that this
 * function can be used both in the beginning of the SAI transfer and also resume the transfer.
 * @param card Soundcard pointer
 */
void SND_TxStart(sound_card_t *card);

/*!
 * @brief Starts the Soundcard Rx process.
 *
 * This function starts the Rx process of the Soundcard. This function  enables the
 * DMA/interrupt request source and enables the Tx and the bit clock of the Tx. Note that this
 * function can be used both in the beginning of the SAI transfer and also resume the transfer.
 * @param card Soundcard pointer
 */
void SND_RxStart(sound_card_t *card);


/*!
 * @brief Stops the Soundcard Tx process.
 *
 * This function stops the transfer of the Soundcard Tx. Note that this function
 * does not close the audio controller. It  disables the DMA/interrupt request source.
 * Therefore, this function can be used to  pause the audio play.
 * @param card Soundcard pointer
 */
static inline void SND_TxStop(sound_card_t *card)
{
    audio_controller_t *ctrl = &card->controller;
#if USEDMA
    EDMA_DRV_StopChannel(&card->controller.dma_channel);
#endif
    ctrl->ops->Ctrl_TxStop(ctrl->instance); 
}

/*!
 * @brief Stops Soundcard RX process.
 *
 * This function stops the transfer of the Soundcard Rx. Note that this function
 * does not close the audio controller. It  disables the DMA/interrupt request source.
 * Therefore, this function can be used to  pause the audio record.
 * @param card Soundcard pointer
 */
static inline void SND_RxStop(sound_card_t *card)
{
    audio_controller_t *ctrl = &card->controller;
#if USEDMA
    EDMA_DRV_StopChannel(&card->controller.dma_channel);
#endif
    ctrl->ops->Ctrl_RxStop(ctrl->instance); 
}

/*!
 * @brief Waits for the semaphore of the write/read data from the internal buffer.
 *
 * The application should call this function before write/read data from the Soundcard buffer.
 * Before the application writes data to the Soundcard buffer, the buffer must have free space
 * for the new data. Otherwise, data loss occurs. This function  waits for the
 * semaphore which represents the  free space in the Soundcard buffer.
 * Similarly to the  reading data from the Soundcard buffer, effective data must be in the
 * buffer. This function  waits for that semaphore.
 * @param card Soundcard pointer
 */
void SND_WaitEvent(sound_card_t *card);

/*!
* @brief Mutes the Soundcard.
*
* This interface sets the mute option for the Soundcard.
* @param card Soundcard pointer
* @param enable Mute or unmute. True means mute, false means unmute.
*/
snd_status_t SND_SetMuteCmd(sound_card_t *card, bool enable);

/*!
* @brief Sets the volume of the Soundcard.
*
* This interface sets the volume of Soundcard.
* @param card Soundcard pointer.
* @param volume Volume of the Soundcard.
*/
snd_status_t SND_SetVolume(sound_card_t *card, uint32_t volume);

/*!
* @brief Gets the volume of the Soundcard.
*
* @param card Soundcard pointer.
* @return Voulme number of Soundcard.
*/
uint32_t SND_GetVolume(sound_card_t *card);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif  /* __FSL_SOUNDCARD_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/

