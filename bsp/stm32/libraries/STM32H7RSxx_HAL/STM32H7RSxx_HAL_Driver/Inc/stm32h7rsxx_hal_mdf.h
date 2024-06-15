/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_mdf.h
  * @author  MCD Application Team
  * @brief   Header file of MDF HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_HAL_MDF_H
#define STM32H7RSxx_HAL_MDF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal_def.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
  * @{
  */

/** @addtogroup MDF
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup MDF_Exported_Types  MDF Exported Types
  * @{
  */

/**
  * @brief  HAL MDF states definition
  */
typedef enum
{
  HAL_MDF_STATE_RESET       = 0x00U, /*!< MDF not initialized */
  HAL_MDF_STATE_READY       = 0x01U, /*!< MDF initialized and ready for use */
  HAL_MDF_STATE_ACQUISITION = 0x02U, /*!< MDF acquisition in progress */
  HAL_MDF_STATE_ERROR       = 0xFFU  /*!< MDF state error */
} HAL_MDF_StateTypeDef;

/**
  * @brief  MDF clock trigger structure definition
  */
typedef struct
{
  FunctionalState Activation;  /*!< Output clock trigger enable/disable */
  uint32_t        Source;      /*!< Output clock trigger source.
                                    This parameter can be a value of @ref MDF_ClockTriggerSource */
  uint32_t        Edge;        /*!< Output clock trigger edge.
                                    This parameter can be a value of @ref MDF_ClockTriggerEdge */
} MDF_ClockTriggerTypeDef;

/**
  * @brief  MDF output clock structure definition
  */
typedef struct
{
  FunctionalState         Activation; /*!< Output clock enable/disable */
  uint32_t                Pins;       /*!< Output clock pins.
                                           This parameter can be a value of @ref MDF_OuputClockPins */
  uint32_t                Divider;    /*!< Output clock divider.
                                           This parameter must be a number between Min_Data = 1 and Max_Data = 16 */
  MDF_ClockTriggerTypeDef Trigger;    /*!< Output clock trigger parameters */
} MDF_OutputClockTypeDef;

/**
  * @brief  MDF common parameters structure definition
  */
typedef struct
{
  uint32_t               ProcClockDivider;   /*!< Processing clock divider.
                                                  This parameter must be a number between Min_Data = 1
                                                  and Max_Data = 128 */
  MDF_OutputClockTypeDef OutputClock;        /*!< Output clock parameters */
} MDF_CommonParamTypeDef;

/**
  * @brief  MDF serial interface structure definition
  */
typedef struct
{
  FunctionalState  Activation;  /*!< Serial interface enable/disable */
  uint32_t         Mode;        /*!< Serial interface mode.
                                     This parameter can be a value of @ref MDF_SitfMode */
  uint32_t         ClockSource; /*!< Serial interface clock source.
                                     This parameter can be a value of @ref MDF_SitfClockSource */
  uint32_t         Threshold;   /*!< SPI threshold for clock absence detection or Manchester symbol threshold.
                                     This parameter must be a number between Min_Data = 4 and Max_Data = 31 */
} MDF_SerialInterfaceTypeDef;

/**
  * @brief  MDF init structure definition
  */
typedef struct
{
  MDF_CommonParamTypeDef      CommonParam;      /*!< MDF common parameters */
  MDF_SerialInterfaceTypeDef  SerialInterface;  /*!< MDF serial interface parameters */
  uint32_t                    FilterBistream;   /*!< MDF filter bitstream selection.
                                                     This parameter can be a value of @ref MDF_FilterBitstream */
} MDF_InitTypeDef;

/**
  * @brief  MDF handle structure definition
  */
#if (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
typedef struct __MDF_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
{
  MDF_Filter_TypeDef        *Instance;  /*!< MDF instance */
  MDF_InitTypeDef            Init;      /*!< MDF init parameters */
  DMA_HandleTypeDef         *hdma;      /*!< Pointer on DMA handler for acquisitions */
  __IO HAL_MDF_StateTypeDef  State;     /*!< MDF state */
  __IO uint32_t              ErrorCode; /*!< MDF error code */
#if (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
  void (*AcqCpltCallback)(struct __MDF_HandleTypeDef *hmdf);      /*!< MDF acquisition complete callback */
  void (*AcqHalfCpltCallback)(struct __MDF_HandleTypeDef *hmdf);  /*!< MDF acquisition half complete callback */
  void (*SndLvCallback)(struct __MDF_HandleTypeDef *hmdf,
                        uint32_t SoundLevel,
                        uint32_t AmbientNoise);                   /*!< MDF sound level callback */
  void (*SadCallback)(struct __MDF_HandleTypeDef *hmdf);          /*!< MDF sound activity detector callback */
  void (*ErrorCallback)(struct __MDF_HandleTypeDef *hmdf);        /*!< MDF error callback */
  void (*MspInitCallback)(struct __MDF_HandleTypeDef *hmdf);      /*!< MDF MSP init callback */
  void (*MspDeInitCallback)(struct __MDF_HandleTypeDef *hmdf);    /*!< MDF MSP de-init callback */
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
} MDF_HandleTypeDef;

#if (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
/**
  * @brief  MDF callback ID enumeration definition
  */
typedef enum
{
  HAL_MDF_ACQ_COMPLETE_CB_ID     = 0x01U, /*!< MDF acquisition complete callback ID */
  HAL_MDF_ACQ_HALFCOMPLETE_CB_ID = 0x02U, /*!< MDF acquisition half complete callback ID */
  HAL_MDF_SNDLVL_CB_ID           = 0x03U, /*!< MDF sound level callback ID */
  HAL_MDF_SAD_CB_ID              = 0x04U, /*!< MDF sound activity detector callback ID */
  HAL_MDF_ERROR_CB_ID            = 0x05U, /*!< MDF error callback ID */
  HAL_MDF_MSPINIT_CB_ID          = 0x06U, /*!< MDF MSP init callback ID */
  HAL_MDF_MSPDEINIT_CB_ID        = 0x07U  /*!< MDF MSP de-init callback ID */
} HAL_MDF_CallbackIDTypeDef;

/**
  * @brief  MDF callback pointers definition
  */
typedef void (*pMDF_CallbackTypeDef)(MDF_HandleTypeDef *hmdf);
typedef void (*pMDF_SndLvlCallbackTypeDef)(MDF_HandleTypeDef *hmdf, uint32_t SoundLevel, uint32_t AmbientNoise);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */

/**
  * @brief  MDF reshape filter structure definition
  */
typedef struct
{
  FunctionalState  Activation;       /*!< Reshape filter enable/disable */
  uint32_t         DecimationRatio;  /*!< Reshape filter decimation ratio.
                                          This parameter can be a value of @ref MDF_ReshapeDecimationRatio */
} MDF_ReshapeFilterTypeDef;

/**
  * @brief  MDF high pass filter structure definition
  */
typedef struct
{
  FunctionalState  Activation;       /*!< High pass filter enable/disable */
  uint32_t         CutOffFrequency;  /*!< High pass filter cut-off frequency.
                                          This parameter can be a value of @ref MDF_HighPassCutOffFreq */
} MDF_HighPassFilterTypeDef;

/**
  * @brief  MDF sound activity structure definition
  */
typedef struct
{
  FunctionalState  Activation;            /*!< Sound activity detector enable/disable */
  uint32_t         Mode;                  /*!< Sound activity detector mode.
                                               This parameter can be a value of @ref MDF_SadMode */
  uint32_t         FrameSize;             /*!< Size of one frame to compute short-term signal level.
                                               This parameter can be a value of @ref MDF_SadFrameSize */
  FunctionalState  Hysteresis;            /*!< Hysteresis enable/disable.
                                               @note This parameter is not used if Mode is set
                                                     to MDF_SAD_AMBIENT_NOISE_ESTIMATOR */
  uint32_t         SoundTriggerEvent;     /*!< Sound trigger event configuration.
                                               This parameter can be a value of @ref MDF_SadSoundTriggerEvent */
  uint32_t         DataMemoryTransfer;    /*!< Data memory transfer mode.
                                               This parameter can be a value of @ref MDF_SadDataMemoryTransfer */
  uint32_t         MinNoiseLevel;         /*!< Minimum noise level.
                                               This parameter must be a number between Min_Data = 0
                                               and Max_Data = 8191 */
  uint32_t         HangoverWindow;        /*!< Hangover time window in frames.
                                               This parameter can be a value of @ref MDF_SadHangoverWindow */
  uint32_t         LearningFrames;        /*!< Number of learning frames for the first estimation of noise level.
                                               This parameter can be a value of @ref MDF_SadLearningFrames */
  uint32_t         AmbientNoiseSlope;     /*!< Ambient noise slope control.
                                               This parameter must be a number between Min_Data = 0 and Max_Data = 7.
                                               @note This parameter is not used if Mode is set
                                                     to MDF_SAD_SOUND_DETECTOR */
  uint32_t         SignalNoiseThreshold;  /*!< Signal to noise threshold.
                                               This parameter can be a value of @ref MDF_SadSignalNoiseThreshold */
  FunctionalState  SoundLevelInterrupt;   /*!< Sound level interrupt enable/disable.
                                               @note This interrupt is mainly used for debug purpose */
} MDF_SoundActivityTypeDef;

/**
  * @brief  MDF filter trigger structure definition
  */
typedef struct
{
  uint32_t  Source;  /*!< Filter trigger source.
                          This parameter can be a value of @ref MDF_FilterTriggerSource */
  uint32_t  Edge;    /*!< Filter trigger edge.
                          This parameter can be a value of @ref MDF_FilterTriggerEdge */
} MDF_FilterTriggerTypeDef;

/**
  * @brief  MDF filter configuration structure definition
  */
typedef struct
{
  uint32_t                  DataSource;      /*!< Filter data source.
                                                  This parameter can be a value of @ref MDF_DataSource */
  uint32_t                  Delay;           /*!< Delay to apply on data source in number of samples.
                                                  This parameter must be a number between Min_Data = 0
                                                  and Max_Data = 127 */
  uint32_t                  CicMode;         /*!< CIC filter mode.
                                                  This parameter can be a value of @ref MDF_CicMode */
  uint32_t                  DecimationRatio; /*!< Filter decimation ratio.
                                                  This parameter must be a number between Min_Data = 2
                                                  and Max_Data = 512 */
  int32_t                   Gain;            /*!< Filter gain in step of around 3db (from -48db to 72dB).
                                                  This parameter must be a number between Min_Data = -16
                                                  and Max_Data = 24 */
  MDF_ReshapeFilterTypeDef  ReshapeFilter;   /*!< Reshape filter configuration */
  MDF_HighPassFilterTypeDef HighPassFilter;  /*!< High pass filter configuration */
  MDF_SoundActivityTypeDef  SoundActivity;   /*!< Sound activity detector configuration */
  uint32_t                  AcquisitionMode; /*!< Filter acquisition mode.
                                                  This parameter can be a value of @ref MDF_AcquisitionMode */
  uint32_t                  FifoThreshold;   /*!< Filter RXFIFO threshold.
                                                  This parameter can be a value of @ref MDF_FifoThreshold */
  uint32_t                  DiscardSamples;  /*!< Number of samples to discard after filter enable.
                                                  This parameter must be a number between Min_Data = 0
                                                  and Max_Data = 255 */
  MDF_FilterTriggerTypeDef  Trigger;         /*!< Filter trigger configuration.
                                                  @note This parameter is not used if AcquisitionMode is set
                                                        to MDF_MODE_ASYNC_CONT or MDF_MODE_ASYNC_SINGLE */
} MDF_FilterConfigTypeDef;

/**
  * @brief  MDF DMA configuration structure definition
  */
typedef struct
{
  uint32_t         Address;     /*!< DMA destination address */
  uint32_t         DataLength;  /*!< Length of data to transfer in bytes */
  FunctionalState  MsbOnly;     /*!< Transfer only the 16MSB of the acquistion data */
} MDF_DmaConfigTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup MDF_Exported_Constants  MDF Exported Constants
  * @{
  */

/** @defgroup MDF_ErrorCode MDF error code
  * @{
  */
#define MDF_ERROR_NONE                  0x00000000U /*!< No error */
#define MDF_ERROR_ACQUISITION_OVERFLOW  0x00000001U /*!< Overflow occurs during acquisition */
#define MDF_ERROR_RSF_OVERRUN           0x00000002U /*!< Overrun occurs on reshape filter */
#define MDF_ERROR_CLOCK_ABSENCE         0x00000004U /*!< Clock absence detection occurs */
#define MDF_ERROR_SATURATION            0x00000010U /*!< Saturation detection occurs */
#define MDF_ERROR_DMA                   0x00000040U /*!< DMA error occurs */
#if (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
#define MDF_ERROR_INVALID_CALLBACK      0x00000080U /*!< Invalid callback error occurs */
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup MDF_ClockTriggerSource MDF output clock trigger source
  * @{
  */
#define MDF_CLOCK_TRIG_TRGO    0x00000000U
#define MDF_CLOCK_TRIG_EXTI15  MDF_CKGCR_TRGSRC_1
/**
  * @}
  */

/** @defgroup MDF_ClockTriggerEdge MDF output clock trigger edge
  * @{
  */
#define MDF_CLOCK_TRIG_RISING_EDGE   0x00000000U        /*!< Rising edge */
#define MDF_CLOCK_TRIG_FALLING_EDGE  MDF_CKGCR_TRGSENS  /*!< Falling edge */
/**
  * @}
  */

/** @defgroup MDF_OuputClockPins MDF output clock pins
  * @{
  */
#define MDF_OUTPUT_CLOCK_0    MDF_CKGCR_CCK0DIR      /*!< MDF_CCK0 is used as output clock */
#define MDF_OUTPUT_CLOCK_1    MDF_CKGCR_CCK1DIR      /*!< MDF_CCK1 is used as output clock */
#define MDF_OUTPUT_CLOCK_ALL (MDF_CKGCR_CCK0DIR | \
                              MDF_CKGCR_CCK1DIR)     /*!< MDF_CCK0 and MDF_CCK1 are used as output clock */
/**
  * @}
  */

/** @defgroup MDF_SitfMode MDF serial interface mode
  * @{
  */
#define MDF_SITF_LF_MASTER_SPI_MODE       0x00000000U           /*!< Low frequency master SPI mode */
#define MDF_SITF_NORMAL_SPI_MODE          MDF_SITFCR_SITFMOD_0  /*!< Normal SPI mode */
#define MDF_SITF_MANCHESTER_FALLING_MODE  MDF_SITFCR_SITFMOD_1  /*!< Manchester mode rising edge logic 0
                                                                     and falling edge logic 1 */
#define MDF_SITF_MANCHESTER_RISING_MODE   MDF_SITFCR_SITFMOD    /*!< Manchester mode rising edge logic 1
                                                                     and falling edge logic 0 */
/**
  * @}
  */

/** @defgroup MDF_SitfClockSource MDF serial interface clock source
  * @{
  */
#define MDF_SITF_CCK0_SOURCE  0x00000000U          /*!< Common clock 0 source */
#define MDF_SITF_CCK1_SOURCE  MDF_SITFCR_SCKSRC_0  /*!< Common clock 1 source */
/**
  * @}
  */

/** @defgroup MDF_FilterBitstream MDF filter bitstream
  * @{
  */
#define MDF_BITSTREAM0_RISING   0x00000000U
#define MDF_BITSTREAM0_FALLING  MDF_BSMXCR_BSSEL_0
/**
  * @}
  */

/** @defgroup MDF_ReshapeDecimationRatio MDF reshape filter decimation ratio
  * @{
  */
#define MDF_RSF_DECIMATION_RATIO_4  0x00000000U          /*!< Reshape filter decimation ratio is 4 */
#define MDF_RSF_DECIMATION_RATIO_1  MDF_DFLTRSFR_RSFLTD  /*!< Reshape filter decimation ratio is 1 */
/**
  * @}
  */

/** @defgroup MDF_HighPassCutOffFreq MDF high pass filter cut-off frequency
  * @{
  */
#define MDF_HPF_CUTOFF_0_000625FPCM  0x00000000U          /*!< Cut-off frequency of 0.000625xFpcm */
#define MDF_HPF_CUTOFF_0_00125FPCM   MDF_DFLTRSFR_HPFC_0  /*!< Cut-off frequency of 0.00125xFpcm */
#define MDF_HPF_CUTOFF_0_0025FPCM    MDF_DFLTRSFR_HPFC_1  /*!< Cut-off frequency of 0.0025xFpcm */
#define MDF_HPF_CUTOFF_0_0095FPCM    MDF_DFLTRSFR_HPFC    /*!< Cut-off frequency of 0.0095xFpcm */
/**
  * @}
  */

/** @defgroup MDF_SadMode MDF sound activity detector mode
  * @{
  */
#define MDF_SAD_VOICE_ACTIVITY_DETECTOR  0x00000000U         /*!< Voice activity detector */
#define MDF_SAD_SOUND_DETECTOR           MDF_SADCR_SADMOD_0  /*!< Sound detector */
#define MDF_SAD_AMBIENT_NOISE_DETECTOR   MDF_SADCR_SADMOD    /*!< Ambient noise detector */
/**
  * @}
  */

/** @defgroup MDF_SadFrameSize MDF sound activity detector frame size
  * @{
  */
#define MDF_SAD_8_PCM_SAMPLES    0x00000000U                               /*!< Frame size of 8 PCM samples */
#define MDF_SAD_16_PCM_SAMPLES   MDF_SADCR_FRSIZE_0                        /*!< Frame size of 16 PCM samples */
#define MDF_SAD_32_PCM_SAMPLES   MDF_SADCR_FRSIZE_1                        /*!< Frame size of 32 PCM samples */
#define MDF_SAD_64_PCM_SAMPLES  (MDF_SADCR_FRSIZE_0 | MDF_SADCR_FRSIZE_1)  /*!< Frame size of 64 PCM samples */
#define MDF_SAD_128_PCM_SAMPLES  MDF_SADCR_FRSIZE_2                        /*!< Frame size of 128 PCM samples */
#define MDF_SAD_256_PCM_SAMPLES (MDF_SADCR_FRSIZE_0 | MDF_SADCR_FRSIZE_2)  /*!< Frame size of 256 PCM samples */
#define MDF_SAD_512_PCM_SAMPLES  MDF_SADCR_FRSIZE                          /*!< Frame size of 512 PCM samples */
/**
  * @}
  */

/** @defgroup MDF_SadSoundTriggerEvent MDF sound activity detector trigger event
  * @{
  */
#define MDF_SAD_ENTER_DETECT       0x00000000U       /*!< Event when SAD enters in detect state */
#define MDF_SAD_ENTER_EXIT_DETECT  MDF_SADCR_DETCFG  /*!< Event when SAD enters or exits from detect state */
/**
  * @}
  */

/** @defgroup MDF_SadDataMemoryTransfer MDF sound activity detector data memory transfer mode
  * @{
  */
#define MDF_SAD_NO_MEMORY_TRANSFER         0x00000000U         /*!< No memory transfer */
#define MDF_SAD_MEMORY_TRANSFER_IN_DETECT  MDF_SADCR_DATCAP_0  /*!< Memory transfer only in detect state */
#define MDF_SAD_MEMORY_TRANSFER_ALWAYS     MDF_SADCR_DATCAP    /*!< Memory transfer always */
/**
  * @}
  */

/** @defgroup MDF_SadHangoverWindow MDF sound activity detector data hangover time window
  * @{
  */
#define MDF_SAD_HANGOVER_4_FRAMES    0x00000000U              /*!< Hangover window of 4 frames */
#define MDF_SAD_HANGOVER_8_FRAMES    MDF_SADCFGR_HGOVR_0      /*!< Hangover window of 8 frames */
#define MDF_SAD_HANGOVER_16_FRAMES   MDF_SADCFGR_HGOVR_1      /*!< Hangover window of 16 frames */
#define MDF_SAD_HANGOVER_32_FRAMES  (MDF_SADCFGR_HGOVR_0 | \
                                     MDF_SADCFGR_HGOVR_1)     /*!< Hangover window of 32 frames */
#define MDF_SAD_HANGOVER_64_FRAMES   MDF_SADCFGR_HGOVR_2      /*!< Hangover window of 64 frames */
#define MDF_SAD_HANGOVER_128_FRAMES (MDF_SADCFGR_HGOVR_0 | \
                                     MDF_SADCFGR_HGOVR_2)     /*!< Hangover window of 128 frames */
#define MDF_SAD_HANGOVER_256_FRAMES (MDF_SADCFGR_HGOVR_1 | \
                                     MDF_SADCFGR_HGOVR_2)     /*!< Hangover window of 256 frames */
#define MDF_SAD_HANGOVER_512_FRAMES (MDF_SADCFGR_HGOVR_0 | \
                                     MDF_SADCFGR_HGOVR_1 | \
                                     MDF_SADCFGR_HGOVR_2)     /*!< Hangover window of 512 frames */
/**
  * @}
  */

/** @defgroup MDF_SadLearningFrames MDF sound activity detector data learning frames
  * @{
  */
#define MDF_SAD_LEARNING_2_FRAMES   0x00000000U                                 /*!< 2 learning frames */
#define MDF_SAD_LEARNING_4_FRAMES   MDF_SADCFGR_LFRNB_0                         /*!< 4 learning frames */
#define MDF_SAD_LEARNING_8_FRAMES   MDF_SADCFGR_LFRNB_1                         /*!< 8 learning frames */
#define MDF_SAD_LEARNING_16_FRAMES (MDF_SADCFGR_LFRNB_0 | MDF_SADCFGR_LFRNB_1)  /*!< 16 learning frames */
#define MDF_SAD_LEARNING_32_FRAMES  MDF_SADCFGR_LFRNB                           /*!< 32 learning frames */
/**
  * @}
  */

/** @defgroup MDF_SadSignalNoiseThreshold MDF sound activity detector data signal to noise threshold
  * @{
  */
#define MDF_SAD_SIGNAL_NOISE_3_5DB   0x00000000U              /*!< Signal to noise threshold is 3.5dB */
#define MDF_SAD_SIGNAL_NOISE_6DB     MDF_SADCFGR_SNTHR_0      /*!< Signal to noise threshold is 6dB */
#define MDF_SAD_SIGNAL_NOISE_9_5DB   MDF_SADCFGR_SNTHR_1      /*!< Signal to noise threshold is 9.5dB */
#define MDF_SAD_SIGNAL_NOISE_12DB   (MDF_SADCFGR_SNTHR_0 | \
                                     MDF_SADCFGR_SNTHR_1)     /*!< Signal to noise threshold is 12dB */
#define MDF_SAD_SIGNAL_NOISE_15_6DB  MDF_SADCFGR_SNTHR_2      /*!< Signal to noise threshold is 15.6dB */
#define MDF_SAD_SIGNAL_NOISE_18DB   (MDF_SADCFGR_SNTHR_0 | \
                                     MDF_SADCFGR_SNTHR_2)     /*!< Signal to noise threshold is 18dB */
#define MDF_SAD_SIGNAL_NOISE_21_6DB (MDF_SADCFGR_SNTHR_1 | \
                                     MDF_SADCFGR_SNTHR_2)     /*!< Signal to noise threshold is 21.6dB */
#define MDF_SAD_SIGNAL_NOISE_24_1DB (MDF_SADCFGR_SNTHR_0 | \
                                     MDF_SADCFGR_SNTHR_1 | \
                                     MDF_SADCFGR_SNTHR_2)     /*!< Signal to noise threshold is 24.1dB */
#define MDF_SAD_SIGNAL_NOISE_27_6DB  MDF_SADCFGR_SNTHR_3      /*!< Signal to noise threshold is 27.6dB */
#define MDF_SAD_SIGNAL_NOISE_30_1DB (MDF_SADCFGR_SNTHR_0 | \
                                     MDF_SADCFGR_SNTHR_3)     /*!< Signal to noise threshold is 30.1dB */
/**
  * @}
  */

/** @defgroup MDF_FilterTriggerSource MDF filter trigger source
  * @{
  */
#define MDF_FILTER_TRIG_TRGO    0x00000000U
#define MDF_FILTER_TRIG_EXTI15  MDF_DFLTCR_TRGSRC_1
/**
  * @}
  */

/** @defgroup MDF_FilterTriggerEdge MDF filter trigger edge
  * @{
  */
#define MDF_FILTER_TRIG_RISING_EDGE   0x00000000U         /*!< Rising edge */
#define MDF_FILTER_TRIG_FALLING_EDGE  MDF_DFLTCR_TRGSENS  /*!< Falling edge */
/**
  * @}
  */

/** @defgroup MDF_DataSource MDF data source
  * @{
  */
#define MDF_DATA_SOURCE_BSMX     0x00000000U            /*!< Data from bitstream matrix */
#define MDF_DATA_SOURCE_ADCITF1  MDF_DFLTCICR_DATSRC_1  /*!< Data from ADC interface 1 */
#define MDF_DATA_SOURCE_ADCITF2  MDF_DFLTCICR_DATSRC    /*!< Data from ADC interface 2 */
/**
  * @}
  */

/** @defgroup MDF_CicMode MDF CIC mode
  * @{
  */
#define MDF_ONE_FILTER_SINC4  MDF_DFLTCICR_CICMOD_2      /*!< One filter in Sinc4 order */
#define MDF_ONE_FILTER_SINC5 (MDF_DFLTCICR_CICMOD_0 | \
                              MDF_DFLTCICR_CICMOD_2)     /*!< One filter in Sinc5 order */
/**
  * @}
  */

/** @defgroup MDF_AcquisitionMode MDF acquisition mode
  * @{
  */
#define MDF_MODE_ASYNC_CONT     0x00000000U              /*!< Asynchronous, continuous acquisition mode */
#define MDF_MODE_ASYNC_SINGLE   MDF_DFLTCR_ACQMOD_0      /*!< Asynchronous, single-shot acquisition mode.
                                                              @note Not available with SAD usage */
#define MDF_MODE_SYNC_CONT      MDF_DFLTCR_ACQMOD_1      /*!< Synchronous, continuous acquisition mode */
#define MDF_MODE_SYNC_SINGLE   (MDF_DFLTCR_ACQMOD_0 | \
                                MDF_DFLTCR_ACQMOD_1)     /*!< Synchronous, single-shot acquisition mode.
                                                              @note Not available with SAD usage */
#define MDF_MODE_WINDOW_CONT    MDF_DFLTCR_ACQMOD_2      /*!< Window, continuous acquisition mode.
                                                              @note Not available with SAD usage */
/**
  * @}
  */

/** @defgroup MDF_FifoThreshold MDF RXFIFO threshold
  * @{
  */
#define MDF_FIFO_THRESHOLD_NOT_EMPTY  0x00000000U     /*!< Event generated when RXFIFO is not empty */
#define MDF_FIFO_THRESHOLD_HALF_FULL  MDF_DFLTCR_FTH  /*!< Event generated when RXFIFO is half_full */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup MDF_Exported_Macros  MDF Exported Macros
  * @{
  */

/** @brief  Reset MDF handle state.
  * @param  __HANDLE__ MDF handle.
  * @retval None
  */
#if (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
#define __HAL_MDF_RESET_HANDLE_STATE(__HANDLE__) do{                                             \
                                                      (__HANDLE__)->State = HAL_MDF_STATE_RESET; \
                                                      (__HANDLE__)->MspInitCallback = NULL;      \
                                                      (__HANDLE__)->MspDeInitCallback = NULL;    \
                                                    } while(0)
#else /* USE_HAL_MDF_REGISTER_CALLBACKS */
#define __HAL_MDF_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_MDF_STATE_RESET)
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup MDF_Exported_Functions
  * @{
  */

/* Initialization and de-initialization functions  ****************************/
/** @addtogroup MDF_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_MDF_Init(MDF_HandleTypeDef *hmdf);
HAL_StatusTypeDef HAL_MDF_DeInit(MDF_HandleTypeDef *hmdf);
void              HAL_MDF_MspInit(MDF_HandleTypeDef *hmdf);
void              HAL_MDF_MspDeInit(MDF_HandleTypeDef *hmdf);
#if (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_MDF_RegisterCallback(MDF_HandleTypeDef        *hmdf,
                                           HAL_MDF_CallbackIDTypeDef CallbackID,
                                           pMDF_CallbackTypeDef      pCallback);
HAL_StatusTypeDef HAL_MDF_UnRegisterCallback(MDF_HandleTypeDef        *hmdf,
                                             HAL_MDF_CallbackIDTypeDef CallbackID);
HAL_StatusTypeDef HAL_MDF_RegisterSndLvlCallback(MDF_HandleTypeDef         *hmdf,
                                                 pMDF_SndLvlCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_MDF_UnRegisterSndLvlCallback(MDF_HandleTypeDef *hmdf);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
/**
  * @}
  */

/* Acquisition functions  *****************************************************/
/** @addtogroup MDF_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_MDF_AcqStart(MDF_HandleTypeDef *hmdf, const MDF_FilterConfigTypeDef *pFilterConfig);
HAL_StatusTypeDef HAL_MDF_PollForAcq(MDF_HandleTypeDef *hmdf, uint32_t Timeout);
HAL_StatusTypeDef HAL_MDF_GetAcqValue(const MDF_HandleTypeDef *hmdf, int32_t *pValue);
HAL_StatusTypeDef HAL_MDF_AcqStop(MDF_HandleTypeDef *hmdf);
HAL_StatusTypeDef HAL_MDF_AcqStart_IT(MDF_HandleTypeDef *hmdf, const MDF_FilterConfigTypeDef *pFilterConfig);
HAL_StatusTypeDef HAL_MDF_AcqStop_IT(MDF_HandleTypeDef *hmdf);
HAL_StatusTypeDef HAL_MDF_AcqStart_DMA(MDF_HandleTypeDef *hmdf, const MDF_FilterConfigTypeDef *pFilterConfig,
                                       const MDF_DmaConfigTypeDef *pDmaConfig);
HAL_StatusTypeDef HAL_MDF_AcqStop_DMA(MDF_HandleTypeDef *hmdf);
HAL_StatusTypeDef HAL_MDF_GenerateTrgo(const MDF_HandleTypeDef *hmdf);
HAL_StatusTypeDef HAL_MDF_SetDelay(MDF_HandleTypeDef *hmdf, uint32_t Delay);
HAL_StatusTypeDef HAL_MDF_GetDelay(const MDF_HandleTypeDef *hmdf, uint32_t *pDelay);
HAL_StatusTypeDef HAL_MDF_SetGain(MDF_HandleTypeDef *hmdf, int32_t Gain);
HAL_StatusTypeDef HAL_MDF_GetGain(const MDF_HandleTypeDef *hmdf, int32_t *pGain);
HAL_StatusTypeDef HAL_MDF_PollForSndLvl(MDF_HandleTypeDef *hmdf, uint32_t Timeout, uint32_t *pSoundLevel,
                                        uint32_t *pAmbientNoise);
HAL_StatusTypeDef HAL_MDF_PollForSad(MDF_HandleTypeDef *hmdf, uint32_t Timeout);
void              HAL_MDF_AcqCpltCallback(MDF_HandleTypeDef *hmdf);
void              HAL_MDF_AcqHalfCpltCallback(MDF_HandleTypeDef *hmdf);
void              HAL_MDF_SndLvlCallback(MDF_HandleTypeDef *hmdf, uint32_t SoundLevel, uint32_t AmbientNoise);
void              HAL_MDF_SadCallback(MDF_HandleTypeDef *hmdf);
/**
  * @}
  */

/* Clock absence detection functions  *****************************************/
/** @addtogroup MDF_Exported_Functions_Group3
  * @{
  */
HAL_StatusTypeDef HAL_MDF_PollForCkab(MDF_HandleTypeDef *hmdf, uint32_t Timeout);
HAL_StatusTypeDef HAL_MDF_CkabStart_IT(MDF_HandleTypeDef *hmdf);
HAL_StatusTypeDef HAL_MDF_CkabStop_IT(MDF_HandleTypeDef *hmdf);
/**
  * @}
  */

/* Generic functions  *********************************************************/
/** @addtogroup MDF_Exported_Functions_Group4
  * @{
  */
void                 HAL_MDF_IRQHandler(MDF_HandleTypeDef *hmdf);
void                 HAL_MDF_ErrorCallback(MDF_HandleTypeDef *hmdf);
HAL_MDF_StateTypeDef HAL_MDF_GetState(const MDF_HandleTypeDef *hmdf);
uint32_t             HAL_MDF_GetError(const MDF_HandleTypeDef *hmdf);
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup MDF_Private_Macros  MDF Private Macros
  * @{
  */
#define IS_MDF_FILTER_BITSTREAM(PARAM) (((PARAM) == MDF_BITSTREAM0_RISING) || \
                                        ((PARAM) == MDF_BITSTREAM0_FALLING))

#define IS_MDF_PROC_CLOCK_DIVIDER(PARAM) ((1U <= (PARAM)) && ((PARAM) <= 128U))

#define IS_MDF_OUTPUT_CLOCK_PINS(PARAM) (((PARAM) == MDF_OUTPUT_CLOCK_0) || \
                                         ((PARAM) == MDF_OUTPUT_CLOCK_1) || \
                                         ((PARAM) == MDF_OUTPUT_CLOCK_ALL))

#define IS_MDF_OUTPUT_CLOCK_DIVIDER(PARAM) ((1U <= (PARAM)) && ((PARAM) <= 16U))

#define IS_MDF_OUTPUT_CLOCK_TRIGGER_SOURCE(PARAM) (((PARAM) == MDF_CLOCK_TRIG_TRGO) || \
                                                   ((PARAM) == MDF_CLOCK_TRIG_EXTI15))

#define IS_MDF_OUTPUT_CLOCK_TRIGGER_EDGE(PARAM) (((PARAM) == MDF_CLOCK_TRIG_RISING_EDGE) || \
                                                 ((PARAM) == MDF_CLOCK_TRIG_FALLING_EDGE))

#define IS_MDF_SITF_MODE(PARAM) (((PARAM) == MDF_SITF_LF_MASTER_SPI_MODE)      || \
                                 ((PARAM) == MDF_SITF_NORMAL_SPI_MODE)         || \
                                 ((PARAM) == MDF_SITF_MANCHESTER_FALLING_MODE) || \
                                 ((PARAM) == MDF_SITF_MANCHESTER_RISING_MODE))

#define IS_MDF_SITF_CLOCK_SOURCE(PARAM) (((PARAM) == MDF_SITF_CCK0_SOURCE) || \
                                         ((PARAM) == MDF_SITF_CCK1_SOURCE))

#define IS_MDF_SITF_THRESHOLD(PARAM) ((4U <= (PARAM)) && ((PARAM) <= 31U))

#define IS_MDF_CIC_MODE(PARAM) (((PARAM) == MDF_ONE_FILTER_SINC4) || \
                                ((PARAM) == MDF_ONE_FILTER_SINC5))

#define IS_MDF_ACQUISITION_MODE(PARAM) (((PARAM) == MDF_MODE_ASYNC_CONT)   || \
                                        ((PARAM) == MDF_MODE_ASYNC_SINGLE) || \
                                        ((PARAM) == MDF_MODE_SYNC_CONT)    || \
                                        ((PARAM) == MDF_MODE_SYNC_SINGLE)  || \
                                        ((PARAM) == MDF_MODE_WINDOW_CONT))

#define IS_MDF_DISCARD_SAMPLES(PARAM) ((PARAM) <= 255U)

#define IS_MDF_FIFO_THRESHOLD(PARAM) (((PARAM) == MDF_FIFO_THRESHOLD_NOT_EMPTY) || \
                                      ((PARAM) == MDF_FIFO_THRESHOLD_HALF_FULL))

#define IS_MDF_TRIGGER_SOURCE(PARAM) (((PARAM) == MDF_FILTER_TRIG_TRGO) || \
                                      ((PARAM) == MDF_FILTER_TRIG_EXTI15))

#define IS_MDF_TRIGGER_EDGE(PARAM) (((PARAM) == MDF_FILTER_TRIG_RISING_EDGE) || \
                                    ((PARAM) == MDF_FILTER_TRIG_FALLING_EDGE))

#define IS_MDF_DATA_SOURCE(PARAM) (((PARAM) == MDF_DATA_SOURCE_BSMX)    || \
                                   ((PARAM) == MDF_DATA_SOURCE_ADCITF1) || \
                                   ((PARAM) == MDF_DATA_SOURCE_ADCITF2))

#define IS_MDF_DECIMATION_RATIO(PARAM) ((2U <= (PARAM)) && ((PARAM) <= 512U))

#define IS_MDF_GAIN(PARAM) ((-16 <= (PARAM)) && ((PARAM) <= 24))

#define IS_MDF_DELAY(PARAM) ((PARAM) <= 127U)

#define IS_MDF_RSF_DECIMATION_RATIO(PARAM) (((PARAM) == MDF_RSF_DECIMATION_RATIO_4) || \
                                            ((PARAM) == MDF_RSF_DECIMATION_RATIO_1))

#define IS_MDF_HPF_CUTOFF_FREQ(PARAM) (((PARAM) == MDF_HPF_CUTOFF_0_000625FPCM) || \
                                       ((PARAM) == MDF_HPF_CUTOFF_0_00125FPCM)  || \
                                       ((PARAM) == MDF_HPF_CUTOFF_0_0025FPCM)   || \
                                       ((PARAM) == MDF_HPF_CUTOFF_0_0095FPCM))

#define IS_MDF_SAD_MODE(PARAM) (((PARAM) == MDF_SAD_VOICE_ACTIVITY_DETECTOR) || \
                                ((PARAM) == MDF_SAD_SOUND_DETECTOR)          || \
                                ((PARAM) == MDF_SAD_AMBIENT_NOISE_DETECTOR))

#define IS_MDF_SAD_FRAME_SIZE(PARAM) (((PARAM) == MDF_SAD_8_PCM_SAMPLES)   || \
                                      ((PARAM) == MDF_SAD_16_PCM_SAMPLES)  || \
                                      ((PARAM) == MDF_SAD_32_PCM_SAMPLES)  || \
                                      ((PARAM) == MDF_SAD_64_PCM_SAMPLES)  || \
                                      ((PARAM) == MDF_SAD_128_PCM_SAMPLES) || \
                                      ((PARAM) == MDF_SAD_256_PCM_SAMPLES) || \
                                      ((PARAM) == MDF_SAD_512_PCM_SAMPLES))

#define IS_MDF_SAD_SOUND_TRIGGER(PARAM) (((PARAM) == MDF_SAD_ENTER_DETECT) || \
                                         ((PARAM) == MDF_SAD_ENTER_EXIT_DETECT))

#define IS_MDF_SAD_DATA_MEMORY_TRANSFER(PARAM) (((PARAM) == MDF_SAD_NO_MEMORY_TRANSFER)        || \
                                                ((PARAM) == MDF_SAD_MEMORY_TRANSFER_IN_DETECT) || \
                                                ((PARAM) == MDF_SAD_MEMORY_TRANSFER_ALWAYS))

#define IS_MDF_SAD_MIN_NOISE_LEVEL(PARAM) ((PARAM) <= 8191U)

#define IS_MDF_SAD_HANGOVER_WINDOW(PARAM) (((PARAM) == MDF_SAD_HANGOVER_4_FRAMES)   || \
                                           ((PARAM) == MDF_SAD_HANGOVER_8_FRAMES)   || \
                                           ((PARAM) == MDF_SAD_HANGOVER_16_FRAMES)  || \
                                           ((PARAM) == MDF_SAD_HANGOVER_32_FRAMES)  || \
                                           ((PARAM) == MDF_SAD_HANGOVER_64_FRAMES)  || \
                                           ((PARAM) == MDF_SAD_HANGOVER_128_FRAMES) || \
                                           ((PARAM) == MDF_SAD_HANGOVER_256_FRAMES) || \
                                           ((PARAM) == MDF_SAD_HANGOVER_512_FRAMES))

#define IS_MDF_SAD_LEARNING_FRAMES(PARAM) (((PARAM) == MDF_SAD_LEARNING_2_FRAMES)  || \
                                           ((PARAM) == MDF_SAD_LEARNING_4_FRAMES)  || \
                                           ((PARAM) == MDF_SAD_LEARNING_8_FRAMES)  || \
                                           ((PARAM) == MDF_SAD_LEARNING_16_FRAMES) || \
                                           ((PARAM) == MDF_SAD_LEARNING_32_FRAMES))

#define IS_MDF_SAD_AMBIENT_NOISE_SLOPE(PARAM) ((PARAM) <= 7U)

#define IS_MDF_SAD_SIGNAL_NOISE_THRESHOLD(PARAM) (((PARAM) == MDF_SAD_SIGNAL_NOISE_3_5DB)  || \
                                                  ((PARAM) == MDF_SAD_SIGNAL_NOISE_6DB)    || \
                                                  ((PARAM) == MDF_SAD_SIGNAL_NOISE_9_5DB)  || \
                                                  ((PARAM) == MDF_SAD_SIGNAL_NOISE_12DB)   || \
                                                  ((PARAM) == MDF_SAD_SIGNAL_NOISE_15_6DB) || \
                                                  ((PARAM) == MDF_SAD_SIGNAL_NOISE_18DB)   || \
                                                  ((PARAM) == MDF_SAD_SIGNAL_NOISE_21_6DB) || \
                                                  ((PARAM) == MDF_SAD_SIGNAL_NOISE_24_1DB) || \
                                                  ((PARAM) == MDF_SAD_SIGNAL_NOISE_27_6DB) || \
                                                  ((PARAM) == MDF_SAD_SIGNAL_NOISE_30_1DB))
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7RSxx_HAL_MDF_H */
