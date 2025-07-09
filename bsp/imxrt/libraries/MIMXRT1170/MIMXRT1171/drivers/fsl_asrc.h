/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_ASRC_H_
#define FSL_ASRC_H_

#include "fsl_common.h"

/*!
 * @addtogroup asrc_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
#define FSL_ASRC_DRIVER_VERSION (MAKE_VERSION(2, 1, 3)) /*!< Version 2.1.3 */
/*! @} */

#ifndef ASRC_XFER_QUEUE_SIZE
/*!@brief ASRC transfer queue size, user can refine it according to use case. */
#define ASRC_XFER_QUEUE_SIZE (4U)
#endif
/*!@brief ASRC channel pair count */
#define FSL_ASRC_CHANNEL_PAIR_COUNT (4U)
/*! @brief ASRC FIFO depth */
#define FSL_ASRC_CHANNEL_PAIR_FIFO_DEPTH (64U)

/*! @brief ASRC register access macro */
#define ASRC_ASRCTR_AT_MASK(index)    ((uint32_t)1U << (ASRC_ASRCTR_ATSA_SHIFT + (uint32_t)(index)))
#define ASRC_ASRCTR_RATIO_MASK(index) ((uint32_t)3U << (ASRC_ASRCTR_IDRA_SHIFT + (uint32_t)(index)*2U))
#define ASRC_ASRCTR_RATIO(ratio, index) \
    (((uint32_t)((uint32_t)(ratio) << (ASRC_ASRCTR_IDRA_SHIFT + (uint32_t)(index)*2U))) & ASRC_ASRCTR_RATIO_MASK(index))
#define ASRC_ASRIER_INPUT_INTERRUPT_MASK(index)     ((uint32_t)1U << (ASRC_ASRIER_ADIEA_SHIFT + (uint32_t)(index)))
#define ASRC_ASRIER_OUTPUTPUT_INTERRUPT_MASK(index) ((uint32_t)1U << (ASRC_ASRIER_ADOEA_SHIFT + (uint32_t)(index)))
#define ASRC_ASRCNCR_CHANNEL_COUNTER_MASK(index)    ((uint32_t)0xFU << (ASRC_ASRCNCR_ANCA_SHIFT + (uint32_t)(index)*4U))
#define ASRC_ASRCNCR_CHANNEL_COUNTER(counter, index)                                       \
    ((uint32_t)((uint32_t)(counter) << (ASRC_ASRCNCR_ANCA_SHIFT + (uint32_t)(index)*4U)) & \
     ASRC_ASRCNCR_CHANNEL_COUNTER_MASK(index))
#define ASRC_ASRCFG_PRE_MODE_MASK(index) ((uint32_t)3U << (ASRC_ASRCFG_PREMODA_SHIFT + (uint32_t)(index)*4U))
#define ASRC_ASRCFG_PRE_MODE(mode, index)                                                 \
    ((uint32_t)((uint32_t)(mode) << (ASRC_ASRCFG_PREMODA_SHIFT + (uint32_t)(index)*4U)) & \
     ASRC_ASRCFG_PRE_MODE_MASK(index))
#define ASRC_ASRCFG_POST_MODE_MASK(index) ((uint32_t)3U << (ASRC_ASRCFG_POSTMODA_SHIFT + (uint32_t)(index)*4U))
#define ASRC_ASRCFG_POST_MODE(mode, index)                                                 \
    ((uint32_t)((uint32_t)(mode) << (ASRC_ASRCFG_POSTMODA_SHIFT + (uint32_t)(index)*4U)) & \
     ASRC_ASRCFG_POST_MODE_MASK(index))
#define ASRC_ASRCFG_INIT_DONE_MASK(index)          ((uint32_t)1U << (ASRC_ASRCFG_INIRQA_SHIFT + (uint32_t)(index)))
#define ASRC_ASRCSR_INPUT_CLOCK_SOURCE_MASK(index) ((uint32_t)0xFU << (ASRC_ASRCSR_AICSA_SHIFT + (uint32_t)(index)*4U))
#define ASRC_ASRCSR_INPUT_CLOCK_SOURCE(source, index)                                     \
    ((uint32_t)((uint32_t)(source) << (ASRC_ASRCSR_AICSA_SHIFT + (uint32_t)(index)*4U)) & \
     ASRC_ASRCSR_INPUT_CLOCK_SOURCE_MASK(index))
#define ASRC_ASRCSR_OUTPUT_CLOCK_SOURCE_MASK(index) ((uint32_t)0xFU << (ASRC_ASRCSR_AOCSA_SHIFT + (uint32_t)(index)*4U))
#define ASRC_ASRCSR_OUTPUT_CLOCK_SOURCE(source, index)                                    \
    ((uint32_t)((uint32_t)(source) << (ASRC_ASRCSR_AOCSA_SHIFT + (uint32_t)(index)*4U)) & \
     ASRC_ASRCSR_OUTPUT_CLOCK_SOURCE_MASK(index))

#define ASRC_ASRCDR_INPUT_PRESCALER_MASK(index) \
    ((uint32_t)(index) < 2U ? ((uint32_t)7U << (ASRC_ASRCDR1_AICPA_SHIFT + (uint32_t)(index)*6U)) : 7U)
#define ASRC_ASRCDR_INPUT_PRESCALER(prescaler, index)                                                              \
    (((index) < 2U ? ((uint32_t)(prescaler) << (ASRC_ASRCDR1_AICPA_SHIFT + (uint32_t)(index)*6U)) : (prescaler)) & \
     ASRC_ASRCDR1_INPUT_PRESCALER_MASK(index))
#define ASRC_ASRCDR_INPUT_DIVIDER_MASK(index)                                                       \
    ((uint32_t)(index) < 2U ? ((uint32_t)7U << (ASRC_ASRCDR1_AICDA_SHIFT + (uint32_t)(index)*6U)) : \
                              (7U << ASRC_ASRCDR1_AICDA_SHIFT))
#define ASRC_ASRCDR_INPUT_DIVIDER(divider, index)                                                           \
    (((uint32_t)(index) < 2U ? ((uint32_t)(divider) << (ASRC_ASRCDR1_AICDA_SHIFT + (uint32_t)(index)*6U)) : \
                               ((uint32_t)(divider) << ASRC_ASRCDR1_AICDA_SHIFT)) &                         \
     ASRC_ASRCDR_INPUT_DIVIDER_MASK(index))
#define ASRC_ASRCDR_OUTPUT_PRESCALER_MASK(index) \
    ((uint32_t)(index) < 2U ? ((uint32_t)7U << (ASRC_ASRCDR1_AOCPA_SHIFT + (uint32_t)(index)*6U)) : (7U << 6U))
#define ASRC_ASRCDR_OUTPUT_PRESCALER(prescaler, index)                                                        \
    (((uint32_t)(index) < 2U ? ((uint32_t)(prescaler) << (ASRC_ASRCDR1_AOCPA_SHIFT + (uint32_t)(index)*6U)) : \
                               ((uint32_t)(prescaler) << 6U)) &                                               \
     ASRC_ASRCDR_OUTPUT_PRESCALER_MASK(index))
#define ASRC_ASRCDR_OUTPUT_DIVIDER_MASK(index) \
    ((uint32_t)(index) < 2U ? ((uint32_t)7U << (ASRC_ASRCDR1_AOCDA_SHIFT + (uint32_t)(index)*6U)) : (7UL << 9U))
#define ASRC_ASRCDR_OUTPUT_DIVIDER(divider, index)                                                          \
    (((uint32_t)(index) < 2U ? ((uint32_t)(divider) << (ASRC_ASRCDR1_AOCDA_SHIFT + (uint32_t)(index)*6U)) : \
                               ((uint32_t)(divider) << 9U)) &                                               \
     ASRC_ASRCDR_OUTPUT_DIVIDER_MASK(index))

#define ASCR_ASRCDR_OUTPUT_CLOCK_DIVIDER_PRESCALER(value, index)                                          \
    (((uint32_t)(index) < 2U ? ((uint32_t)(value) << (ASRC_ASRCDR1_AOCPA_SHIFT + (uint32_t)(index)*6U)) : \
                               ((uint32_t)(value) << 6U)))
#define ASCR_ASRCDR_INPUT_CLOCK_DIVIDER_PRESCALER(value, index) \
    (((uint32_t)(index) < 2U ? ((uint32_t)(value) << ((uint32_t)(index)*6U)) : ((uint32_t)(value))))

#define ASRC_IDEAL_RATIO_HIGH(base, index)    *(volatile uint32_t *)((uint32_t)(&(base)->ASRIDRHA) + (uint32_t)(index)*8U)
#define ASRC_IDEAL_RATIO_LOW(base, index)     *(volatile uint32_t *)((uint32_t)(&(base)->ASRIDRLA) + (uint32_t)(index)*8U)
#define ASRC_ASRMCR(base, index)              *(volatile uint32_t *)((uint32_t)(&(base)->ASRMCRA) + (uint32_t)(index)*8U)
#define ASRC_ASRMCR1(base, index)             *(volatile uint32_t *)((uint32_t)(&((base)->ASRMCR1[(index)])))
#define ASRC_ASRDI(base, index)               *(volatile uint32_t *)((uint32_t)(&(base)->ASRDIA) + (uint32_t)(index)*8U)
#define ASRC_ASRDO(base, index)               *(volatile uint32_t *)((uint32_t)(&(base)->ASRDOA) + (uint32_t)(index)*8U)
#define ASRC_ASRDI_ADDR(base, index)          (volatile uint32_t *)((uint32_t)(&(base)->ASRDIA) + (uint32_t)(index)*8U)
#define ASRC_ASRDO_ADDR(base, index)          (volatile uint32_t *)((uint32_t)(&(base)->ASRDOA) + (uint32_t)(index)*8U)
#define ASRC_ASRFST_ADDR(base, index)         (*(volatile uint32_t *)((uint32_t)(&(base)->ASRFSTA) + (uint32_t)(index)*8U))
#define ASRC_GET_CHANNEL_COUNTER(base, index) (((base)->ASRCNCR >> ((uint32_t)(index)*4U)) & 0xFU)

/*! @brief ASRC return status
 * @anchor _asrc_status_t
 */
enum
{
    kStatus_ASRCIdle                       = MAKE_STATUS(kStatusGroup_ASRC, 0),  /*!< ASRC is idle. */
    kStatus_ASRCInIdle                     = MAKE_STATUS(kStatusGroup_ASRC, 1),  /*!< ASRC in is idle. */
    kStatus_ASRCOutIdle                    = MAKE_STATUS(kStatusGroup_ASRC, 2),  /*!< ASRC out is idle. */
    kStatus_ASRCBusy                       = MAKE_STATUS(kStatusGroup_ASRC, 3),  /*!< ASRC  is busy. */
    kStatus_ASRCInvalidArgument            = MAKE_STATUS(kStatusGroup_ASRC, 4),  /*!< ASRC invalid argument. */
    kStatus_ASRCClockConfigureFailed       = MAKE_STATUS(kStatusGroup_ASRC, 5),  /*!< ASRC clock configure failed */
    kStatus_ASRCChannelPairConfigureFailed = MAKE_STATUS(kStatusGroup_ASRC, 6),  /*!< ASRC clock configure failed */
    kStatus_ASRCConvertError               = MAKE_STATUS(kStatusGroup_ASRC, 7),  /*!< ASRC clock configure failed */
    kStatus_ASRCNotSupport                 = MAKE_STATUS(kStatusGroup_ASRC, 8),  /*!< ASRC not support */
    kStatus_ASRCQueueFull                  = MAKE_STATUS(kStatusGroup_ASRC, 9),  /*!< ASRC queue is full */
    kStatus_ASRCOutQueueIdle               = MAKE_STATUS(kStatusGroup_ASRC, 10), /*!< ASRC out queue is idle */
    kStatus_ASRCInQueueIdle                = MAKE_STATUS(kStatusGroup_ASRC, 11), /*!< ASRC in queue is idle */
};

/*! @brief ASRC channel pair mask */
typedef enum _asrc_channel_pair
{
    kASRC_ChannelPairA = 0, /*!< channel pair A value */
    kASRC_ChannelPairB = 1, /*!< channel pair B value */
    kASRC_ChannelPairC = 2, /*!< channel pair C value */
} asrc_channel_pair_t;

/*! @brief ASRC support sample rate
 * @anchor _asrc_sample_rate
 */
enum
{
    kASRC_SampleRate_8000HZ   = 8000U,   /*!< asrc sample rate 8KHZ */
    kASRC_SampleRate_11025HZ  = 11025U,  /*!< asrc sample rate 11.025KHZ */
    kASRC_SampleRate_12000HZ  = 12000U,  /*!< asrc sample rate 12KHZ */
    kASRC_SampleRate_16000HZ  = 16000U,  /*!< asrc sample rate 16KHZ */
    kASRC_SampleRate_22050HZ  = 22050U,  /*!< asrc sample rate 22.05KHZ */
    kASRC_SampleRate_24000HZ  = 24000U,  /*!< asrc sample rate 24KHZ */
    kASRC_SampleRate_30000HZ  = 30000U,  /*!< asrc sample rate 30KHZ */
    kASRC_SampleRate_32000HZ  = 32000U,  /*!< asrc sample rate 32KHZ */
    kASRC_SampleRate_44100HZ  = 44100U,  /*!< asrc sample rate 44.1KHZ */
    kASRC_SampleRate_48000HZ  = 48000U,  /*!< asrc sample rate 48KHZ */
    kASRC_SampleRate_64000HZ  = 64000U,  /*!< asrc sample rate 64KHZ */
    kASRC_SampleRate_88200HZ  = 88200U,  /*!< asrc sample rate 88.2KHZ */
    kASRC_SampleRate_96000HZ  = 96000U,  /*!< asrc sample rate 96KHZ */
    kASRC_SampleRate_128000HZ = 128000U, /*!< asrc sample rate 128KHZ */
    kASRC_SampleRate_176400HZ = 176400U, /*!< asrc sample rate 176.4KHZ */
    kASRC_SampleRate_192000HZ = 192000U, /*!< asrc sample rate 192KHZ */
};

/*! @brief The ASRC interrupt enable flag
 * @anchor _asrc_interrupt_mask
 */
enum
{
    kASRC_FPInWaitStateInterruptEnable = ASRC_ASRIER_AFPWE_MASK, /*!< FP in wait state mask */
    kASRC_OverLoadInterruptMask        = ASRC_ASRIER_AOLIE_MASK, /*!< overload interrupt mask */
    kASRC_DataOutputCInterruptMask     = ASRC_ASRIER_ADOEC_MASK, /*!< data output c interrupt mask */
    kASRC_DataOutputBInterruptMask     = ASRC_ASRIER_ADOEB_MASK, /*!< data output b interrupt mask */
    kASRC_DataOutputAInterruptMask     = ASRC_ASRIER_ADOEA_MASK, /*!< data output a interrupt mask */
    kASRC_DataInputCInterruptMask      = ASRC_ASRIER_ADIEC_MASK, /*!< data input c interrupt mask */
    kASRC_DataInputBInterruptMask      = ASRC_ASRIER_ADIEB_MASK, /*!< data input b interrupt mask */
    kASRC_DataInputAInterruptMask      = ASRC_ASRIER_ADIEA_MASK, /*!< data input a interrupt mask */
};

/*! @brief The ASRC interrupt status
 * @anchor _asrc_interrupt_status
 */
enum
{
    kASRC_StatusDSLCounterReady     = ASRC_ASRSTR_DSLCNT_MASK, /*!< DSL counter   */
    kASRC_StatusTaskQueueOverLoad   = ASRC_ASRSTR_ATQOL_MASK,  /*!< task queue overload */
    kASRC_StatusPairCOutputOverLoad = ASRC_ASRSTR_AOOLC_MASK,  /*!< pair c output overload  */
    kASRC_StatusPairBOutputOverLoad = ASRC_ASRSTR_AOOLB_MASK,  /*!< pair b output overload  */
    kASRC_StatusPairAOutputOverLoad = ASRC_ASRSTR_AOOLA_MASK,  /*!< pair a output overload */
    kASRC_StatusPairCInputOverLoad  = ASRC_ASRSTR_AIOLC_MASK,  /*!< pair c input overload */
    kASRC_StatusPairBInputOverLoad  = ASRC_ASRSTR_AIOLB_MASK,  /*!<pair b input overload */
    kASRC_StatusPairAInputOverLoad  = ASRC_ASRSTR_AIOLA_MASK,  /*!< pair a input overload */
    kASRC_StatusPairCOutputOverflow = ASRC_ASRSTR_AODOC_MASK,  /*!< pair c output overflow */
    kASRC_StatusPairBOutputOverflow = ASRC_ASRSTR_AODOB_MASK,  /*!< pair b output overflow */
    kASRC_StatusPairAOutputOverflow = ASRC_ASRSTR_AODOA_MASK,  /*!< pair a output overflow */
    kASRC_StatusPairCInputUnderflow = ASRC_ASRSTR_AIDUC_MASK,  /*!< pair c input underflow*/
    kASRC_StatusPairBInputUnderflow = ASRC_ASRSTR_AIDUB_MASK,  /*!< pair b input under flow */
    kASRC_StatusPairAInputUnderflow = ASRC_ASRSTR_AIDUA_MASK,  /*!< pair a input underflow*/
    kASRC_StatusFPInWaitState       = ASRC_ASRSTR_FPWT_MASK,   /*!< FP in wait state */
    kASRC_StatusOverloadError       = ASRC_ASRSTR_AOLE_MASK,   /*!< overload error */

    kASRC_StatusInputError = kASRC_StatusPairCInputOverLoad | kASRC_StatusPairBInputOverLoad |
                             kASRC_StatusPairAInputOverLoad | kASRC_StatusPairCInputUnderflow |
                             kASRC_StatusPairBInputUnderflow |
                             kASRC_StatusPairAInputUnderflow, /*!< input error status */

    kASRC_StatusOutputError = kASRC_StatusPairCOutputOverLoad | kASRC_StatusPairBOutputOverLoad |
                              kASRC_StatusPairAOutputOverLoad | kASRC_StatusPairCOutputOverflow |
                              kASRC_StatusPairBOutputOverflow |
                              kASRC_StatusPairAOutputOverflow, /*!< output error status */

    kASRC_StatusPairCOutputReady = ASRC_ASRSTR_AODFC_MASK, /*!< pair c output ready */
    kASRC_StatusPairBOutputReady = ASRC_ASRSTR_AODFB_MASK, /*!< pair b output ready */
    kASRC_StatusPairAOutputReady = ASRC_ASRSTR_AODFA_MASK, /*!< pair a output ready */
    kASRC_StatusPairCInputReady  = ASRC_ASRSTR_AIDEC_MASK, /*!< pair c input ready */
    kASRC_StatusPairBInputReady  = ASRC_ASRSTR_AIDEB_MASK, /*!< pair b input ready */
    kASRC_StatusPairAInputReady  = ASRC_ASRSTR_AIDEA_MASK, /*!< pair a input ready */
    kASRC_StatusPairAInterrupt   = kASRC_StatusPairAInputReady | kASRC_StatusPairAOutputReady, /*!< pair A interrupt */
    kASRC_StatusPairBInterrupt   = kASRC_StatusPairBInputReady | kASRC_StatusPairBOutputReady, /*!< pair B interrupt */
    kASRC_StatusPairCInterrupt   = kASRC_StatusPairCInputReady | kASRC_StatusPairCOutputReady, /*!< pair C interrupt */

};

/*! @brief ASRC channel pair status
 * @anchor _asrc_channel_pair_status
 */
enum
{
    kASRC_OutputFifoNearFull = ASRC_ASRFSTA_OAFA_MASK, /*!< channel pair output fifo near full */
    kASRC_InputFifoNearEmpty = ASRC_ASRFSTA_IAEA_MASK, /*!< channel pair input fifo near empty */
};

/*! @brief ASRC ideal ratio */
typedef enum _asrc_ratio
{
    kASRC_RatioNotUsed = 0U, /*!< ideal ratio not used */
    kASRC_RatioUseInternalMeasured =
        2U, /*!< ideal ratio use internal measure ratio, can be used for real time streaming audio */
    kASRC_RatioUseIdealRatio =
        3U, /*!< ideal ratio use manual configure ratio, can be used for the non-real time streaming audio */
} asrc_ratio_t;

/*! @brief Number of channels in audio data */
typedef enum _asrc_audio_channel
{
    kASRC_ChannelsNumber1  = 1U,  /*!< channel number is 1 */
    kASRC_ChannelsNumber2  = 2U,  /*!< channel number is 2 */
    kASRC_ChannelsNumber3  = 3U,  /*!< channel number is 3 */
    kASRC_ChannelsNumber4  = 4U,  /*!< channel number is 4 */
    kASRC_ChannelsNumber5  = 5U,  /*!< channel number is 5 */
    kASRC_ChannelsNumber6  = 6U,  /*!< channel number is 6 */
    kASRC_ChannelsNumber7  = 7U,  /*!< channel number is 7 */
    kASRC_ChannelsNumber8  = 8U,  /*!< channel number is 8 */
    kASRC_ChannelsNumber9  = 9U,  /*!< channel number is 9 */
    kASRC_ChannelsNumber10 = 10U, /*!< channel number is 10 */
} asrc_audio_channel_t;

/*! @brief data width */
typedef enum _asrc_data_width
{
    kASRC_DataWidth24Bit = 0U, /*!< data width 24bit */
    kASRC_DataWidth16Bit = 1U, /*!< data width 16bit */
    kASRC_DataWidth8Bit  = 2U, /*!< data width 8bit */
} asrc_data_width_t;

/*! @brief data alignment */
typedef enum _asrc_data_align
{
    kASRC_DataAlignMSB = 1U, /*!< data alignment MSB */
    kASRC_DataAlignLSB = 0U, /*!< data alignment LSB */
} asrc_data_align_t;

/*! @brief sign extension */
typedef enum _asrc_sign_extension
{
    kASRC_NoSignExtension = 0U, /*!< no sign extension */
    kASRC_SignExtension   = 1U, /*!< sign extension */
} asrc_sign_extension_t;

/*! @brief asrc channel pair configuation */
typedef struct _asrc_channel_pair_config
{
    asrc_audio_channel_t audioDataChannels; /*!< audio data channel numbers */
    asrc_clock_source_t
        inClockSource;         /*!< input clock source, reference the clock source definition in SOC header file */
    uint32_t inSourceClock_Hz; /*!< input source clock frequency */

    asrc_clock_source_t
        outClockSource;         /*!< output clock source, reference the clock source definition in SOC header file */
    uint32_t outSourceClock_Hz; /*!< output source clock frequency */

    asrc_ratio_t sampleRateRatio; /*!< sample rate ratio type */

    asrc_data_width_t inDataWidth; /*!< input data width */
    asrc_data_align_t inDataAlign; /*!< input data alignment */

    asrc_data_width_t outDataWidth;         /*!< output data width */
    asrc_data_align_t outDataAlign;         /*!< output data alignment */
    asrc_sign_extension_t outSignExtension; /*!< output extension */

    uint8_t outFifoThreshold; /*!< output fifo threshold */
    uint8_t inFifoThreshold;  /*!< input fifo threshold */

    bool bufStallWhenFifoEmptyFull; /*!< stall Pair A conversion in case of Buffer near empty full condition */

} asrc_channel_pair_config_t;

/*! @brief SAI transfer structure */
typedef struct _asrc_transfer
{
    void *inData;       /*!< Data address to convert.*/
    size_t inDataSize;  /*!< input data size. */
    void *outData;      /*!< Data address to store converted data */
    size_t outDataSize; /*!< output data size. */
} asrc_transfer_t;

/*! @brief asrc handler */
typedef struct _asrc_handle asrc_handle_t;

/*! @brief ASRC transfer callback prototype */
typedef void (*asrc_transfer_callback_t)(ASRC_Type *base, asrc_handle_t *handle, status_t status, void *userData);

/*! @brief asrc in handler */
typedef struct _asrc_in_handle
{
    asrc_transfer_callback_t callback;            /*!< Callback function called at convert complete */
    uint32_t sampleWidth;                         /*!< data width */
    uint32_t sampleMask;                          /*!< data mask */
    uint32_t fifoThreshold;                       /*!< fifo threshold */
    uint8_t *asrcQueue[ASRC_XFER_QUEUE_SIZE];     /*!< Transfer queue storing queued transfer */
    size_t transferSamples[ASRC_XFER_QUEUE_SIZE]; /*!< Data bytes need to convert */
    volatile uint8_t queueUser;                   /*!< Index for user to queue transfer */
    volatile uint8_t queueDriver;                 /*!< Index for driver to get the transfer data and size */
} asrc_in_handle_t;

/*! @brief output handler */
typedef struct _asrc_out_handle
{
    asrc_transfer_callback_t callback;            /*!< Callback function called at convert complete */
    uint32_t sampleWidth;                         /*!< data width */
    uint32_t fifoThreshold;                       /*!< fifo threshold */
    uint8_t *asrcQueue[ASRC_XFER_QUEUE_SIZE];     /*!< Transfer queue storing queued transfer */
    size_t transferSamples[ASRC_XFER_QUEUE_SIZE]; /*!< Data bytes need to convert */
    volatile uint8_t queueUser;                   /*!< Index for user to queue transfer */
    volatile uint8_t queueDriver;                 /*!< Index for driver to get the transfer data and size */
} asrc_out_handle_t;

/*! @brief ASRC handle structure */
struct _asrc_handle
{
    ASRC_Type *base; /*!< base address */

    uint32_t state; /*!< Transfer status */
    void *userData; /*!< Callback parameter passed to callback function*/

    asrc_audio_channel_t audioDataChannels; /*!< audio channel number */
    asrc_channel_pair_t channelPair;        /*!< channel pair mask */

    asrc_in_handle_t in;   /*!< asrc input handler */
    asrc_out_handle_t out; /*!< asrc output handler */
};
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /*_cplusplus*/

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Get instance number of the ASRC peripheral.
 *
 * @param base ASRC base pointer.
 */
uint32_t ASRC_GetInstance(ASRC_Type *base);

/*!
 * brief Initializes the asrc peripheral.
 *
 * This API gates the asrc clock. The asrc module can't operate unless ASRC_Init is called to enable the clock.
 *
 * param base asrc base pointer.
 * param asrcPeripheralClock_Hz peripheral clock of ASRC.
 */
void ASRC_Init(ASRC_Type *base, uint32_t asrcPeripheralClock_Hz);

/*!
 * @brief De-initializes the ASRC peripheral.
 *
 * This API gates the ASRC clock and disable ASRC module. The ASRC module can't operate unless ASRC_Init
 *
 * @param base ASRC base pointer.
 */
void ASRC_Deinit(ASRC_Type *base);

/*!
 * @brief Do software reset .
 *
 * This software reset bit is self-clear bit, it will generate a software reset signal inside ASRC.
 * After 9 cycles of the ASRC processing clock, this reset process will stop and this bit will cleared
 * automatically.
 *
 * @param base ASRC base pointer
 */
void ASRC_SoftwareReset(ASRC_Type *base);

/*!
 * @brief ASRC configure channel pair.
 *
 * @param base ASRC base pointer.
 * @param channelPair index of channel pair, reference _asrc_channel_pair.
 * @param config ASRC channel pair configuration pointer.
 * @param inputSampleRate input audio data sample rate.
 * @param outputSampleRate output audio data sample rate.
 */
status_t ASRC_SetChannelPairConfig(ASRC_Type *base,
                                   asrc_channel_pair_t channelPair,
                                   asrc_channel_pair_config_t *config,
                                   uint32_t inputSampleRate,
                                   uint32_t outputSampleRate);

/*!
 * @brief Get output sample buffer size.
 *
 * @note This API is depends on the ASRC output configuration, should be called after the ASRC_SetChannelPairConfig.
 *
 * @param base asrc base pointer.
 * @param channelPair ASRC channel pair number.
 * @param inSampleRate input sample rate.
 * @param outSampleRate output sample rate.
 * @param inSamplesize input sampleS size.
 * @retval output buffer size in byte.
 */
uint32_t ASRC_GetOutSamplesSize(ASRC_Type *base,
                                asrc_channel_pair_t channelPair,
                                uint32_t inSampleRate,
                                uint32_t outSampleRate,
                                uint32_t inSamplesize);

/*!
 * @brief Map register sample width to real sample width.
 *
 * @note This API is depends on the ASRC configuration, should be called after the ASRC_SetChannelPairConfig.
 * @param base asrc base pointer.
 * @param channelPair asrc channel pair index.
 * @param inWidth ASRC channel pair number.
 * @param outWidth input sample rate.
 * @retval input sample mask value.
 */
uint32_t ASRC_MapSamplesWidth(ASRC_Type *base, asrc_channel_pair_t channelPair, uint32_t *inWidth, uint32_t *outWidth);

/*!
 * @brief Get left samples in fifo.
 *
 * @param base asrc base pointer.
 * @param channelPair ASRC channel pair number.
 * @param buffer input sample numbers.
 * @param outSampleWidth output sample width.
 * @param remainSamples output sample rate.
 * @retval remain samples number.
 */
uint32_t ASRC_GetRemainFifoSamples(ASRC_Type *base,
                                   asrc_channel_pair_t channelPair,
                                   uint32_t *buffer,
                                   uint32_t outSampleWidth,
                                   uint32_t remainSamples);

/*!
 * @brief ASRC module enable.
 *
 * @param base ASRC base pointer.
 * @param enable true is enable, false is disable
 */
static inline void ASRC_ModuleEnable(ASRC_Type *base, bool enable)
{
    if (enable)
    {
        base->ASRCTR |= ASRC_ASRCTR_ASRCEN_MASK;
    }
    else
    {
        base->ASRCTR &= ~ASRC_ASRCTR_ASRCEN_MASK;
    }
}

/*!
 * @brief ASRC enable channel pair.
 *
 * @param base ASRC base pointer.
 * @param channelPair channel pair mask value, reference _asrc_channel_pair_mask.
 * @param enable true is enable, false is disable.
 */
static inline void ASRC_ChannelPairEnable(ASRC_Type *base, asrc_channel_pair_t channelPair, bool enable)
{
    if (enable)
    {
        base->ASRCTR |= 1UL << ((uint32_t)channelPair + 1U);
    }
    else
    {
        base->ASRCTR &= ~(1UL << ((uint32_t)channelPair + 1U));
    }
}
/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief ASRC interrupt enable
 * This function enable the ASRC interrupt with the provided mask.
 *
 * @param base ASRC peripheral base address.
 * @param mask The interrupts to enable. Logical OR of @ref _asrc_interrupt_mask.
 */
static inline void ASRC_EnableInterrupt(ASRC_Type *base, uint32_t mask)
{
    base->ASRIER |= mask;
}

/*!
 * @brief ASRC interrupt disable
 * This function disable the ASRC interrupt with the provided mask.
 *
 * @param base ASRC peripheral base address.
 * @param mask The interrupts to disable. Logical OR of @ref _asrc_interrupt_mask.
 */
static inline void ASRC_DisableInterrupt(ASRC_Type *base, uint32_t mask)
{
    base->ASRIER &= ~mask;
}

/*! @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the ASRC status flag state.
 *
 * @param base ASRC base pointer
 * @return ASRC Tx status flag value. Use the Status Mask to get the status value needed.
 */
static inline uint32_t ASRC_GetStatus(ASRC_Type *base)
{
    return base->ASRSTR;
}

/*!
 * @brief Gets the ASRC channel pair initialization state.
 *
 * @param base ASRC base pointer
 * @param channel ASRC channel pair.
 * @return ASRC Tx status flag value. Use the Status Mask to get the status value needed.
 */
static inline bool ASRC_GetChannelPairInitialStatus(ASRC_Type *base, asrc_channel_pair_t channel)
{
    return ((base->ASRCFG >> ASRC_ASRCFG_INIRQA_SHIFT) & (1U << (uint32_t)channel)) == 0U ? false : true;
}

/*!
 * @brief Gets the ASRC channel A fifo a status flag state.
 *
 * @param base ASRC base pointer
 * @param channelPair ASRC channel pair.
 * @return ASRC channel pair a fifo status flag value. Use the Status Mask to get the status value needed.
 */
static inline uint32_t ASRC_GetChannelPairFifoStatus(ASRC_Type *base, asrc_channel_pair_t channelPair)
{
    return ASRC_ASRMCR(base, channelPair) & ((uint32_t)kASRC_OutputFifoNearFull | (uint32_t)kASRC_InputFifoNearEmpty);
}

/*! @} */

/*!
 * @name Bus Operations
 * @{
 */

/*!
 * @brief Writes data into ASRC channel pair FIFO.
 * Note: ASRC fifo width is 24bit.
 * @param base ASRC base pointer.
 * @param channelPair ASRC channel pair.
 * @param data Data needs to be written.
 */
static inline void ASRC_ChannelPairWriteData(ASRC_Type *base, asrc_channel_pair_t channelPair, uint32_t data)
{
    ASRC_ASRDI(base, channelPair) = data;
}

/*!
 * @brief Read data from ASRC channel pair FIFO.
 * Note: ASRC fifo width is 24bit.
 *
 * @param base ASRC base pointer.
 * @param channelPair ASRC channel pair.
 * @retval value read from fifo.
 */
static inline uint32_t ASRC_ChannelPairReadData(ASRC_Type *base, asrc_channel_pair_t channelPair)
{
    return ASRC_ASRDO(base, channelPair);
}

/*!
 * @brief Get input data fifo address.
 * Note: ASRC fifo width is 24bit.
 *
 * @param base ASRC base pointer.
 * @param channelPair ASRC channel pair.
 */
static inline uint32_t ASRC_GetInputDataRegisterAddress(ASRC_Type *base, asrc_channel_pair_t channelPair)
{
    return (uint32_t)ASRC_ASRDI_ADDR(base, channelPair);
}

/*!
 * @brief Get output data fifo address.
 * Note: ASRC fifo width is 24bit.
 *
 * @param base ASRC base pointer.
 * @param channelPair ASRC channel pair.
 */
static inline uint32_t ASRC_GetOutputDataRegisterAddress(ASRC_Type *base, asrc_channel_pair_t channelPair)
{
    return (uint32_t)ASRC_ASRDO_ADDR(base, channelPair);
}

/*!
 * @brief ASRC configure ideal ratio.
 * The ideal ratio should be used when input clock source is not avalible.
 *
 * @param base ASRC base pointer.
 * @param channelPair ASRC channel pair.
 * @param inputSampleRate input audio data sample rate.
 * @param outputSampleRate output audio data sample rate.
 */
status_t ASRC_SetIdealRatioConfig(ASRC_Type *base,
                                  asrc_channel_pair_t channelPair,
                                  uint32_t inputSampleRate,
                                  uint32_t outputSampleRate);

/*! @} */

/*!
 * @name Transactional
 * @{
 */

/*!
 * @brief ASRC configure channel pair.
 *
 * @param base ASRC base pointer.
 * @param handle ASRC transactional handle pointer.
 * @param config ASRC channel pair configuration pointer.
 * @param inputSampleRate input audio data sample rate.
 * @param outputSampleRate output audio data sample rate.
 */
status_t ASRC_TransferSetChannelPairConfig(ASRC_Type *base,
                                           asrc_handle_t *handle,
                                           asrc_channel_pair_config_t *config,
                                           uint32_t inputSampleRate,
                                           uint32_t outputSampleRate);

/*!
 * @brief Initializes the ASRC handle.
 *
 * This function initializes the handle for the ASRC transactional APIs. Call
 * this function once to get the handle initialized.
 *
 * @param base ASRC base pointer
 * @param handle ASRC handle pointer.
 * @param channelPair ASRC channel pair.
 * @param inCallback Pointer to the user callback function.
 * @param outCallback Pointer to the user callback function.
 * @param userData User parameter passed to the callback function
 */
void ASRC_TransferCreateHandle(ASRC_Type *base,
                               asrc_handle_t *handle,
                               asrc_channel_pair_t channelPair,
                               asrc_transfer_callback_t inCallback,
                               asrc_transfer_callback_t outCallback,
                               void *userData);

/*!
 * @brief Performs an interrupt non-blocking convert on asrc.
 *
 * @note This API returns immediately after the transfer initiates, application should check the wait and check the
 * callback status.
 *
 * @param base asrc base pointer.
 * @param handle Pointer to the asrc_handle_t structure which stores the transfer state.
 * @param xfer Pointer to the ASRC_transfer_t structure.
 * @retval kStatus_Success Successfully started the data receive.
 * @retval kStatus_ASRCBusy Previous receive still not finished.
 */
status_t ASRC_TransferNonBlocking(ASRC_Type *base, asrc_handle_t *handle, asrc_transfer_t *xfer);

/*!
 * @brief Performs an blocking convert on asrc.
 *
 * @note This API returns immediately after the convert finished.
 *
 * @param base asrc base pointer.
 * @param channelPair channel pair index.
 * @param xfer Pointer to the ASRC_transfer_t structure.
 * @retval kStatus_Success Successfully started the data receive.
 */
status_t ASRC_TransferBlocking(ASRC_Type *base, asrc_channel_pair_t channelPair, asrc_transfer_t *xfer);

/*!
 * @brief Get converted byte count.
 *
 * @param base ASRC base pointer.
 * @param handle Pointer to the asrc_handle_t structure which stores the transfer state.
 * @param count Bytes count sent.
 * @retval kStatus_Success Succeed get the transfer count.
 * @retval kStatus_ASRCIdle There is not a non-blocking transaction currently in progress.
 */
status_t ASRC_TransferGetConvertedCount(ASRC_Type *base, asrc_handle_t *handle, size_t *count);

/*!
 * @brief Aborts the current convert.
 *
 * @note This API can be called any time when an interrupt non-blocking transfer initiates
 * to abort the transfer early.
 *
 * @param base ASRC base pointer.
 * @param handle Pointer to the asrc_handle_t structure which stores the transfer state.
 */
void ASRC_TransferAbortConvert(ASRC_Type *base, asrc_handle_t *handle);

/*!
 * @brief Terminate all ASRC convert.
 *
 * This function will clear all transfer slots buffered in the asrc queue. If users only want to abort the
 * current transfer slot, please call ASRC_TransferAbortConvert.
 *
 * @param base ASRC base pointer.
 * @param handle ASRC eDMA handle pointer.
 */
void ASRC_TransferTerminateConvert(ASRC_Type *base, asrc_handle_t *handle);

/*!
 * @brief ASRC convert interrupt handler.
 *
 * @param base ASRC base pointer.
 * @param handle Pointer to the asrc_handle_t structure.
 */
void ASRC_TransferHandleIRQ(ASRC_Type *base, asrc_handle_t *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif /*_cplusplus*/

/*! @} */

#endif /* FSL_ASRC_H_ */
