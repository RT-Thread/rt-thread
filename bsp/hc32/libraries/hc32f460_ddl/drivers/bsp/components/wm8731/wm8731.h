/**
 *******************************************************************************
 * @file  wm8731.h
 * @brief This file contains all the functions prototypes of the codec component
 *        library for wm8731.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __WM8731_H__
#define __WM8731_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/**
 * @addtogroup WM8731
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @brief WM8731 Init structure definition
 */
typedef struct {
    uint8_t  u8InputDevice;             /*!< Specifies the intput device.
                                             This parameter can be a value of @ref WM8731_Input_Device */
    uint8_t  u8OutputDevice;            /*!< Specifies the output device.
                                             This parameter can be a value of @ref WM8731_Output_Device */
    uint8_t  u8OutputSrc;               /*!< Specifies the data source for the output.
                                             This parameter can be a value of @ref WM8731_Output_Source */
    uint32_t u32AudioFreq;              /*!< Specifies the audio frequency of the communication.
                                             This parameter can be a value of @ref WM8731_Audio_Frequency */
    uint8_t  u8Volume;                  /*!< Specifies the volume of input and output.
                                             This parameter can be a value between Min_Data = 0 and Max_Data = 100 */
    uint8_t  u8DataForamt;              /*!< Specifies the data format of the communication.
                                             This parameter can be a value of @ref WM8731_Data_Format */
    uint8_t  u8DataWidth;               /*!< Specifies the data width of the communication.
                                             This parameter can be a value of @ref WM8731_Data_Width */
} stc_wm8731_init_t;

/**
 * @brief WM8731 low layer structure definition
 */
typedef struct {
    /* Methods */
    void (*Delay)(uint32_t);
    void (*Init)(void);
    void (*Write)(const uint8_t *, const uint8_t *, uint32_t);
    void (*Read)(const uint8_t *, uint8_t *, uint32_t);
} stc_wm8731_ll_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup WM8731_Register WM8731 Register
 * @{
 */
#define WM8731_R0_LEFT_LINE_IN                  (0x00U) /* Left Line In                   */
#define WM8731_R1_RIGHT_LINE_IN                 (0x02U) /* Right Line In                  */
#define WM8731_R2_LEFT_HP_OUT                   (0x04U) /* Left Headphone Out             */
#define WM8731_R3_RIGHT_HP_OUT                  (0x06U) /* Right Headphone Out            */
#define WM8731_R4_ANA_AUDIO_PATH                (0x08U) /* Analogue Audio Path Control    */
#define WM8731_R5_DIG_AUDIO_PATH                (0x0AU) /* Digital Audio Path Control     */
#define WM8731_R6_PWR_DOWN                      (0x0CU) /* Power Down Control             */
#define WM8731_R7_DIG_AUDIO_IF                  (0x0EU) /* Digital Audio Interface Format */
#define WM8731_R8_SPL                           (0x10U) /* Sampling Control               */
#define WM8731_R9_ACT                           (0x12U) /* Active Control                 */
#define WM8731_R15_RST                          (0x1EU) /* Reset Register                 */
/**
 * @}
 */

/**
 * @defgroup WM8731_Input_Device WM8731 Input Device
 * @{
 */
#define WM8731_INPUT_DEVICE_NONE                (0x00U)
#define WM8731_INPUT_DEVICE_MICROPHONE          (0x01U)
#define WM8731_INPUT_DEVICE_LINE                (0x02U)
/**
 * @}
 */

/**
 * @defgroup WM8731_Output_Device WM8731 Output Device
 * @{
 */
#define WM8731_OUTPUT_DEVICE_NONE               (0x00U)
#define WM8731_OUTPUT_DEVICE_LINE               (0x01U)
#define WM8731_OUTPUT_DEVICE_HEADPHONE          (0x02U)
#define WM8731_OUTPUT_DEVICE_BOTH               (0x03U)
/**
 * @}
 */

/**
 * @defgroup WM8731_Output_Source WM8731 Output Source
 * @{
 */
#define WM8731_OUTPUT_SRC_LINE                  (0x08U) /* From Line(BYPASS) inputs        */
#define WM8731_OUTPUT_SRC_DAC                   (0x10U) /* From DAC(DACSEL) input          */
#define WM8731_OUTPUT_SRC_MICROPHONE            (0x20U) /* From Microphone(SIDETONE) input */
/**
 * @}
 */

/**
 * @defgroup WM8731_Audio_Frequency WM8731 Audio Frequency
 * @{
 */
#define WM8731_AUDIO_FREQ_8K                    (8000UL)
#define WM8731_AUDIO_FREQ_32K                   (32000UL)
#define WM8731_AUDIO_FREQ_48K                   (48000UL)
#define WM8731_AUDIO_FREQ_96K                   (96000UL)
/**
 * @}
 */

/**
 * @defgroup WM8731_Data_Format WM8731 Data Format
 * @{
 */
#define WM8731_DATA_FORMAT_LSB                  (0x00U) /* Right Justified Mode */
#define WM8731_DATA_FORMAT_MSB                  (0x01U) /* Left Justified Mode  */
#define WM8731_DATA_FORMAT_PHILLIPS             (0x02U) /* I2S Mode             */
#define WM8731_DATA_FORMAT_DSP                  (0x03U) /* DSP/PCM Mode         */
/**
 * @}
 */

/**
 * @defgroup WM8731_Data_Width WM8731 Data Width
 * @{
 */
#define WM8731_DATA_WIDTH_16BIT                 (0x00U)
#define WM8731_DATA_WIDTH_20BIT                 (0x04U)
#define WM8731_DATA_WIDTH_24BIT                 (0x08U)
#define WM8731_DATA_WIDTH_32BIT                 (0x0CU)
/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup WM8731_Global_Functions WM8731 Global Functions
 * @{
 */
int32_t WM8731_Reset(const stc_wm8731_ll_t *pstcWm8731LL);
int32_t WM8731_Init(const stc_wm8731_ll_t *pstcWm8731LL, const stc_wm8731_init_t *pstcWm8731Init);
int32_t WM8731_Play(const stc_wm8731_ll_t *pstcWm8731LL);
int32_t WM8731_Stop(const stc_wm8731_ll_t *pstcWm8731LL);
int32_t WM8731_SetAudioFreq(const stc_wm8731_ll_t *pstcWm8731LL, uint32_t u32Freq);
int32_t WM8731_SetVolume(const stc_wm8731_ll_t *pstcWm8731LL, uint8_t u8Volume);

/**
 * @}
 */

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

#endif /* __WM8731_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
