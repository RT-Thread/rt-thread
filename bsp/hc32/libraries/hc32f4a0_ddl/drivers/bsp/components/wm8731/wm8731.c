/**
 *******************************************************************************
 * @file  wm8731.c
 * @brief This midware file provides firmware functions to manage the codec
 *        component library for wm8731.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "wm8731.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/**
 * @defgroup WM8731 Codec WM8731
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup WM8731_Local_Macros WM8731 Local Macros
 * @{
 */

/* WM8731 volume convert */
#define WM8731_INPUT_VOL_CONV(__VOL__)  (((__VOL__) >= 100U) ? 31U : ((uint8_t)((((uint32_t)__VOL__) * 31U) / 100U)))
#define WM8731_OUTPUT_VOL_CONV(__VOL__) (((__VOL__) >= 100U) ? 80U : ((uint8_t)((((uint32_t)__VOL__) * 80U) / 100U)))

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t u8InputDevice  = 0U;
static uint8_t u8OutputDevice = 0U;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup WM8731_Global_Functions WM8731 Global Functions
 * @{
 */

/**
 * @brief  Reset WM8731.
 * @param  [in] pstcWm8731LL            Pointer to a @ref stc_wm8731_ll_t structure
 * @retval int32_t:
 *           - LL_OK: Reset success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t WM8731_Reset(const stc_wm8731_ll_t *pstcWm8731LL)
{
    int32_t i32Ret = LL_OK;
    uint8_t u8WriteData[2];

    if (pstcWm8731LL == NULL) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Writing 00000000 to register resets device */
        u8WriteData[0] = WM8731_R15_RST;
        u8WriteData[1] = 0U;
        pstcWm8731LL->Write(&u8WriteData[0], &u8WriteData[1], 1U);
        u8InputDevice  = 0U;
        u8OutputDevice = 0U;
    }

    return i32Ret;
}

/**
 * @brief  Initialize WM8731.
 * @param  [in] pstcWm8731LL            Pointer to a @ref stc_wm8731_ll_t structure.
 * @param  [in] pstcWm8731Init          Pointer to a @ref stc_wm8731_init_t structure
 * @retval int32_t:
 *           - LL_OK: Initialize success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t WM8731_Init(const stc_wm8731_ll_t *pstcWm8731LL, const stc_wm8731_init_t *pstcWm8731Init)
{
    int32_t i32Ret = LL_OK;
    uint16_t u16AudioPath;
    uint16_t u16PowerControl;
    uint8_t u8WriteData[2];

    if ((pstcWm8731LL == NULL) || (NULL == pstcWm8731Init)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Initialize the control interface of the codec */
        pstcWm8731LL->Init();
        /* Writing 00000000 to register resets device */
        u8WriteData[0] = WM8731_R15_RST;
        u8WriteData[1] = 0U;
        pstcWm8731LL->Write(&u8WriteData[0], &u8WriteData[1], 1U);
        pstcWm8731LL->Delay(50U);

        u8InputDevice  = pstcWm8731Init->u8InputDevice;
        u8OutputDevice = pstcWm8731Init->u8OutputDevice;
        /* Path Configurations for input */
        if (WM8731_INPUT_DEVICE_NONE != u8InputDevice) {
            switch (u8InputDevice) {
                case WM8731_INPUT_DEVICE_MICROPHONE:
                    u16AudioPath    = 0x05U;
                    u16PowerControl = 0x01U;
                    break;
                case WM8731_INPUT_DEVICE_LINE:
                    u16AudioPath    = 0x02U;
                    u16PowerControl = 0x02U;
                    break;
                default:
                    /* Invalid input device */
                    u16AudioPath    = 0x02U;
                    u16PowerControl = 0x07U;
                    break;
            }
        } else {
            u16AudioPath    = 0x02U;
            u16PowerControl = 0x07U;
        }

        u16AudioPath |= pstcWm8731Init->u8OutputSrc;
        /* Path Configurations for output */
        if (WM8731_OUTPUT_DEVICE_NONE != u8OutputDevice) {
            switch (u8OutputDevice) {
                case WM8731_OUTPUT_DEVICE_LINE:
                case WM8731_OUTPUT_DEVICE_HEADPHONE:
                case WM8731_OUTPUT_DEVICE_BOTH:
                    break;
                default:
                    u16PowerControl |= 0x08U;
                    break;
            }
        } else {
            u16PowerControl |= 0x08U;
        }
        /* Power down control */
        u8WriteData[0] = WM8731_R6_PWR_DOWN;
        u8WriteData[1] = (uint8_t)(u16PowerControl | 0x10U);
        pstcWm8731LL->Write(&u8WriteData[0], &u8WriteData[1], 1U);
        /* Analogue audio path control */
        u8WriteData[0] = WM8731_R4_ANA_AUDIO_PATH;
        u8WriteData[1] = (uint8_t)u16AudioPath;
        pstcWm8731LL->Write(&u8WriteData[0], &u8WriteData[1], 1U);
        /* Set audio frequency and volume */
        (void)WM8731_SetAudioFreq(pstcWm8731LL, pstcWm8731Init->u32AudioFreq);
        (void)WM8731_SetVolume(pstcWm8731LL, pstcWm8731Init->u8Volume);
        /* Configure digital audio interface format, Slave mode */
        u8WriteData[0] = WM8731_R7_DIG_AUDIO_IF;
        u8WriteData[1] = pstcWm8731Init->u8DataForamt | pstcWm8731Init->u8DataWidth;
        pstcWm8731LL->Write(&u8WriteData[0], &u8WriteData[1], 1U);

        /* Active Control */
        u8WriteData[0] = WM8731_R9_ACT;
        u8WriteData[1] = 0x01U;
        pstcWm8731LL->Write(&u8WriteData[0], &u8WriteData[1], 1U);
        /* Enable the DAC signal path */
        u8WriteData[0] = WM8731_R6_PWR_DOWN;
        u8WriteData[1] = (uint8_t)u16PowerControl;
        pstcWm8731LL->Write(&u8WriteData[0], &u8WriteData[1], 1U);
    }

    return i32Ret;
}

/**
 * @brief  Start the audio codec play.
 * @param  [in] pstcWm8731LL            Pointer to a @ref stc_wm8731_ll_t structure.
 * @retval int32_t:
 *           - LL_OK: Operation success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t WM8731_Play(const stc_wm8731_ll_t *pstcWm8731LL)
{
    int32_t i32Ret = LL_OK;
    uint8_t u8WriteData[2];

    /* Unmute the output */
    if (pstcWm8731LL == NULL) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        if (WM8731_OUTPUT_DEVICE_NONE != u8OutputDevice) {
            /* Disable DAC soft mute */
            u8WriteData[0] = WM8731_R5_DIG_AUDIO_PATH;
            u8WriteData[1] = 0x00U;
            pstcWm8731LL->Write(&u8WriteData[0], &u8WriteData[1], 1U);
        }
    }

    return i32Ret;
}

/**
 * @brief  Stop the audio codec play.
 * @param  [in] pstcWm8731LL            Pointer to a @ref stc_wm8731_ll_t structure.
 * @retval int32_t:
 *           - LL_OK: Operation success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t WM8731_Stop(const stc_wm8731_ll_t *pstcWm8731LL)
{
    int32_t i32Ret = LL_OK;
    uint8_t u8WriteData[2];

    /* Mute the output */
    if (pstcWm8731LL == NULL) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        if (WM8731_INPUT_DEVICE_NONE != u8OutputDevice) {
            /* Enable DAC soft mute */
            u8WriteData[0] = WM8731_R5_DIG_AUDIO_PATH;
            u8WriteData[1] = 0x08U;
            pstcWm8731LL->Write(&u8WriteData[0], &u8WriteData[1], 1U);
        }
    }

    return i32Ret;
}

/**
 * @brief  Set the new audio frequency.
 * @param  [in] pstcWm8731LL            Pointer to a @ref stc_wm8731_ll_t structure.
 * @param  [in] u32Freq                 The audio frequency
 *         This parameter can be one of the following values:
 *           @arg WM8731_AUDIO_FREQ_8K
 *           @arg WM8731_AUDIO_FREQ_32K
 *           @arg WM8731_AUDIO_FREQ_48K
 *           @arg WM8731_AUDIO_FREQ_96K
 * @retval int32_t:
 *           - LL_OK: Operation success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t WM8731_SetAudioFreq(const stc_wm8731_ll_t *pstcWm8731LL, uint32_t u32Freq)
{
    int32_t i32Ret = LL_OK;
    uint8_t u8WriteData[2];

    if (pstcWm8731LL == NULL) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Base Over-Sampling Rate = 256fs */
        switch (u32Freq) {
            case WM8731_AUDIO_FREQ_8K:
                u8WriteData[1] = 0x0CU;
                break;
            case WM8731_AUDIO_FREQ_32K:
                u8WriteData[1] = 0x18U;
                break;
            case WM8731_AUDIO_FREQ_48K:
                u8WriteData[1] = 0x00U;
                break;
            case WM8731_AUDIO_FREQ_96K:
                u8WriteData[1] = 0x1CU;
                break;
            default:
                /* Sample Rate = 48 (KHz) */
                u8WriteData[1] = 0x18U;
                break;
        }
        u8WriteData[0] = WM8731_R8_SPL;
        pstcWm8731LL->Write(&u8WriteData[0], &u8WriteData[1], 1U);
    }

    return i32Ret;
}

/**
 * @brief  Set the codec volume level.
 * @param  [in] pstcWm8731LL            Pointer to a @ref stc_wm8731_ll_t structure.
 * @param  [in] u8Volume                The codec volume level
 *         This parameter can be a value between Min_Data = 0 and Max_Data = 100
 * @retval int32_t:
 *           - LL_OK: Operation success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t WM8731_SetVolume(const stc_wm8731_ll_t *pstcWm8731LL, uint8_t u8Volume)
{
    int32_t i32Ret = LL_OK;
    uint8_t u8ConvVolume;
    uint8_t u8WriteData[2];

    if (pstcWm8731LL == NULL) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Input volume */
        if (WM8731_INPUT_DEVICE_LINE == u8InputDevice) {
            u8ConvVolume = WM8731_INPUT_VOL_CONV(u8Volume);
            /* Mute line input */
            if (0U == u8ConvVolume) {
                u8WriteData[1] = 0x80U;
            } else {
                u8WriteData[1] = u8ConvVolume;
            }
            u8WriteData[0] = WM8731_R0_LEFT_LINE_IN;
            pstcWm8731LL->Write(&u8WriteData[0], &u8WriteData[1], 1U);
            u8WriteData[0] = WM8731_R1_RIGHT_LINE_IN;
            pstcWm8731LL->Write(&u8WriteData[0], &u8WriteData[1], 1U);
        }

        /* Output volume */
        if (WM8731_OUTPUT_DEVICE_HEADPHONE == (u8OutputDevice & WM8731_OUTPUT_DEVICE_HEADPHONE)) {
            u8ConvVolume = WM8731_OUTPUT_VOL_CONV(u8Volume) + 0x2FU;
            if (u8ConvVolume > 0x2FU) {
                u8WriteData[1] = u8ConvVolume;
            } else {
                /* Mute headphone output  */
                u8WriteData[1] = 0x00U;
            }
            u8WriteData[0] = WM8731_R2_LEFT_HP_OUT;
            pstcWm8731LL->Write(&u8WriteData[0], &u8WriteData[1], 1U);
            u8WriteData[0] = WM8731_R3_RIGHT_HP_OUT;
            pstcWm8731LL->Write(&u8WriteData[0], &u8WriteData[1], 1U);
        }
    }

    return i32Ret;
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
