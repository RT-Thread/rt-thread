/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_DAC_H__
#define __HAL_DAC_H__

#include "hal_common.h"

/*!
 * @addtogroup DAC
 * @{
 */

/*!
 * @brief DAC driver version number.
 */
#define DAC_DRIVER_VERSION 0u /*!< dac_0. */

/*!
 * @addtogroup DAC_CHANNEL_SELECTION
 * @{
 */
#define DAC_CHN_NUM    (2u) /*!< The total number of DAC channel. */
#define DAC_CHN_1      (0u) /*!< The selection of DAC Channel 1. */
#define DAC_CHN_2      (1u) /*!< The selection of DAC Channel 2. */
/*!
 *@}
 */

/*!
 * @brief DAC align type.
 */
typedef enum
{
    DAC_Align_8b_Dual        = 0u,  /*!< The selection of dual channel data alignment of 8b right. */
    DAC_Align_8b_Right       = 1u,  /*!< The selection of single channel data alignment of 8b right. */
    DAC_Align_12b_Left       = 2u,  /*!< The selection of single channel data alignment of 12b left. */
    DAC_Align_12b_Right      = 3u,  /*!< The selection of single channel data alignment of 12b right. */
    DAC_Align_12b_Dual_Left  = 4u,  /*!< The selection of dual channel data alignment of 12b left. */
    DAC_Align_12b_Dual_Right = 5u,  /*!< The selection of dual channel data alignment of 12b right. */
} DAC_Align_Type;

/*!
 * @brief DAC trigger source selection.
 */
typedef enum
{
    DAC_TrgSource_Alt0        = 0u, /*!< The selection of the documented trigger of value 0. */
    DAC_TrgSource_Alt1        = 1u, /*!< The selection of the documented trigger of value 1. */
    DAC_TrgSource_Alt2        = 2u, /*!< The selection of the documented trigger of value 2. */
    DAC_TrgSource_Alt3        = 3u, /*!< The selection of the documented trigger of value 3. */
    DAC_TrgSource_Alt4        = 4u, /*!< The selection of the documented trigger of value 4. */
    DAC_TrgSource_Alt5        = 5u, /*!< The selection of the documented trigger of value 5. */
    DAC_TrgSource_Alt6        = 6u, /*!< The selection of the documented trigger of value 6. */
    DAC_TrgSource_Alt7        = 7u, /*!< The selection of the documented software trigger. */
    DAC_TrgSource_None        = 16u, /*!< No trigger to be used. */
} DAC_TrgSource_Type;

/*!
 * @brief DAC LFSR unmask bit selector type for adding noise wave.
 */
typedef enum
{
    DAC_AddNoise_LFSRUnMask_0  = 0u,  /*!< Unmask DAC channel LFSR bit0. */
    DAC_AddNoise_LFSRUnMask_1  = 1u,  /*!< Unmask DAC channel LFSR bit[1:0]. */
    DAC_AddNoise_LFSRUnMask_2  = 2u,  /*!< Unmask DAC channel LFSR bit[2:0]. */
    DAC_AddNoise_LFSRUnMask_3  = 3u,  /*!< Unmask DAC channel LFSR bit[3:0]. */
    DAC_AddNoise_LFSRUnMask_4  = 4u,  /*!< Unmask DAC channel LFSR bit[4:0]. */
    DAC_AddNoise_LFSRUnMask_5  = 5u,  /*!< Unmask DAC channel LFSR bit[5:0]. */
    DAC_AddNoise_LFSRUnMask_6  = 6u,  /*!< Unmask DAC channel LFSR bit[6:0]. */
    DAC_AddNoise_LFSRUnMask_7  = 7u,  /*!< Unmask DAC channel LFSR bit[7:0]. */
    DAC_AddNoise_LFSRUnMask_8  = 8u,  /*!< Unmask DAC channel LFSR bit[8:0]. */
    DAC_AddNoise_LFSRUnMask_9  = 9u,  /*!< Unmask DAC channel LFSR bit[9:0]. */
    DAC_AddNoise_LFSRUnMask_10 = 10u, /*!< Unmask DAC channel LFSR bit[10:0]. */
    DAC_AddNoise_LFSRUnMask_11 = 11u, /*!< Unmask DAC channel LFSR bit[11:0]. */
} DAC_AddNoise_Type;

/*!
 * @brief DAC triangle amplitude selector type for adding triangle wave.
 */
typedef enum
{
    DAC_AddTriangle_LFSRAmplitude_1    = 0u,  /*!< Max triangle amplitude of 1. */
    DAC_AddTriangle_LFSRAmplitude_3    = 1u,  /*!< Max triangle amplitude of 3. */
    DAC_AddTriangle_LFSRAmplitude_7    = 2u,  /*!< Max triangle amplitude of 7. */
    DAC_AddTriangle_LFSRAmplitude_15   = 3u,  /*!< Max triangle amplitude of 15. */
    DAC_AddTriangle_LFSRAmplitude_31   = 4u,  /*!< Max triangle amplitude of 31. */
    DAC_AddTriangle_LFSRAmplitude_63   = 5u,  /*!< Max triangle amplitude of 63. */
    DAC_AddTriangle_LFSRAmplitude_127  = 6u,  /*!< Max triangle amplitude of 127. */
    DAC_AddTriangle_LFSRAmplitude_255  = 7u,  /*!< Max triangle amplitude of 255. */
    DAC_AddTriangle_LFSRAmplitude_511  = 8u,  /*!< Max triangle amplitude of 511. */
    DAC_AddTriangle_LFSRAmplitude_1023 = 9u,  /*!< Max triangle amplitude of 1023. */
    DAC_AddTriangle_LFSRAmplitude_2047 = 10u, /*!< Max triangle amplitude of 2047. */
    DAC_AddTriangle_LFSRAmplitude_4095 = 11u, /*!< Max triangle amplitude of 4095. */
} DAC_AddTriangle_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref DAC_EnableAddNoise() to initialize the DAC noise wave generation.
 */
typedef struct
{
    DAC_AddNoise_Type AddNoise; /*!< Specify the noise wave pattern. */
} DAC_AddNoise_Init_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref DAC_EnableAddTriangle() to initialize the DAC triangle wave generation.
 */
typedef struct
{
    DAC_AddTriangle_Type AddTriangle; /*!< Specify the triangle wave pattern. */
} DAC_AddTriangle_Init_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref DAC_Init() to initialize the DAC module.
 */
typedef struct
{
    DAC_TrgSource_Type TrgSource; /*!< Specify whether to use the trigger and the trigger type. */
    bool EnableOutBuf; /*!< Specify whether output buffer is enabled. */
} DAC_Init_Type;

/*!
 * @brief Initialize the DAC module.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @param init Pointer to the initialization structure. See to @ref DAC_Init_Type.
 * @return None.
 */
void DAC_Init(DAC_Type * DACx, uint32_t channel, DAC_Init_Type * init);

/*!
 * @brief Enable the DAC module.
 *
 * The DAC module should be enabled before outputting voltage.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @param enable 'true' to enable the module, 'false' to disable the module.
 * @return None.
 */
void DAC_Enable(DAC_Type * DACx, uint32_t channel, bool enable);

/*!
 * @brief Get the echo data from the output of the indicated DAC channel.
 *
 * The value in DAC_DORx register takes effect on the actual output of DAC.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @return The indicated DAC channel data output value.
 */
uint32_t DAC_GetData(DAC_Type * DACx, uint32_t channel);

/*!
 * @brief Put the value into the indicated channel of the DAC module with the alignment.
 *
 * The value in DAC_DORx register takes effect on the actual output of DAC.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @param value Data value to be put in indicated DAC channel for conversion.
 * @param align Alignment the value expected to be put into the conversion. See to @ref DAC_Align_Type.
 * @return The current converted value of the indicated DAC channel.
 */
uint32_t DAC_PutData(DAC_Type * DACx, uint32_t channel, uint32_t value, DAC_Align_Type align);

/*!
 * @brief Enable the feature of generating noise wave from the DAC module.
 *
 * If enable additional noise wave, the output value will depend on the the unmask LFSR bit and input of the indicated channel.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @param init Pointer to the initialization structure. See to @ref DAC_AddNoise_Init_Type. If null, disable the wave generation.
 * @return None.
 */
void DAC_EnableAddNoise(DAC_Type * DACx, uint32_t channel, DAC_AddNoise_Init_Type * init);

/*!
 * @brief Enable the feature of generating triangle wave from the DAC module.
 *
 * Defaultedly, DAC does not generate any wave.
 * If enable additional triangle wave, the output value will depend on the the indicated amplitude and input of the indicated channel.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @param init Pointer to the initialization structure. See to @ref DAC_AddTriangle_Init_Type. If null, disable the wave generation.
 * @return None.
 */
void DAC_EnableAddTriangle(DAC_Type * DACx, uint32_t channel, DAC_AddTriangle_Init_Type * init);

/*!
 * @brief Enable the DMA trigger from the DAC module.
 *
 * The DMA trigger events are the same as the intertupts.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @param enable 'true' to enable the DMA trigger, 'false' to disable the DMA trigger.
 * @return None.
 */
void DAC_EnableDMA(DAC_Type * DACx, uint32_t channel, bool enable);

/*!
 * @brief Do trigger the indicated DAC channel with software trigger.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @return None.
 */
void DAC_DoSwTrigger(DAC_Type * DACx, uint32_t channel);

/*!
 * @brief Do trigger the dual DAC channels with software trigger simultaneously.
 *
 * @param DACx DAC instance.
 * @return None.
 */
void DAC_DoDualChannelSwTrigger(DAC_Type * DACx);

/*!
 * @brief Get the indicated register address of the DAC module.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @param align Alignment that the data expects to br transferred. See to @ref DAC_Align_Type.
 * @return The value of the address for indicated align type of the DAC channel.
 */
uint32_t DAC_GetDataRegAddr(DAC_Type * DACx, uint32_t channel, DAC_Align_Type align);

/*!
 * @brief Put 8-bit value into the indicated channel of the DAC module.
 *
 * The low 8-bit of the setting value here will be output with 4-bit left shift.
 * If the value is 0x1f, the output will be 0x1f0.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @param value Data value to be put in indicated DAC channel for conversion.
 * @return None.
 */
void DAC_PutData8bRightAlign(DAC_Type * DACx, uint32_t channel, uint32_t value);

/*!
 * @brief Put the 12-bit value into indicated channel of the DAC module.
 *
 * The low 12-bit of the setting value here will be output after 4-bit right shift.
 * If the value is 0x1ff, the output will be 0x1f.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @param value Data value to be put in indicated DAC channel for conversion.
 * @return None.
 */
void DAC_PutData12bLeftAlign(DAC_Type * DACx, uint32_t channel, uint32_t value);

/*!
 * @brief Put the current data into indicated channel of the DAC module.
 *
 * The low 12-bit of the setting value here will output with the original value.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @param value Data value to be put in indicated DAC channel for conversion.
 * @return None.
 */
void DAC_PutData12bRightAlign(DAC_Type * DACx, uint32_t channel, uint32_t value);

/*!
 * @brief Respectively put the value into the dual channels of the DAC module 8b right aligned.
 *
 * Simultaneously output the low 8-bit of the low 16-bit and high 16-bit of the 32-bit value seperately with a 4-bit left shift.
 * If value is 0x011f01ff, the output of each channel will be 0xff0 ( channel 1 ) and 0x1f0 ( channel 2 ).
 *
 * @param DACx DAC instance.
 * @param value Data value to be put in DAC channel 1 and DAC channel 2 for conversion.
 * @return None.
 */
void DAC_PutDualChannelData8bRightAlign(DAC_Type * DACx, uint32_t value);

/*!
 * @brief Put the data into the dual channel of the DAC module 12b left aligned.
 *
 * Simultaneously output the high 12-bit of the low 16-bit and high 16-bit of the 32-bit value seperately after 4-bit right shift.
 * If value is 0x011f01ff, the output of each channel will be 0x01f ( channel 1 ) and 0x011 ( channel 2 ).
 *
 * @param DACx DAC instance.
 * @param value Data value to be put in DAC channel 1 and DAC channel 2 for conversion.
 * @return None.
 */
void DAC_PutDualChannelData12bLeftAlign(DAC_Type * DACx, uint32_t value);

/*!
 * @brief Put the data into the dual channel of the DAC module 12b right aligned.
 *
 * Simultaneously output the low 12-bit of the low 16-bit and high 16-bit of the 32-bit value seperately.
 *
 * @param DACx DAC instance.
 * @param value Data value to be put in DAC channel 1 and DAC channel 2 for conversion.
 * @return None.
 */
void DAC_PutDualChannelData12bRightAlign(DAC_Type * DACx, uint32_t value);

/*!
 * @brief Get the 8-bit data register address of the DAC module.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @return The value of the address for DAC module's 8-bit data register .
 */
uint32_t DAC_GetData8bRegAddr(DAC_Type * DACx, uint32_t channel);

/*!
 * @brief Get the 12-bit left-aligned data register address of the DAC module.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @return The value of the address for DAC module's 12-bit left-aligned data register .
 */
uint32_t DAC_GetData12bLeftRegAddr(DAC_Type * DACx, uint32_t channel);

/*!
 * @brief Get the 12-bit right-aligned data register address of the DAC module.
 *
 * @param DACx DAC instance.
 * @param channel Indicated DAC channel. See to @ref DAC_CHANNEL_SELECTION.
 * @return The value of the address for DAC module's 12-bit right-aligned data register .
 */
uint32_t DAC_GetData12bRightRegAddr(DAC_Type * DACx, uint32_t channel);

/*!
 * @brief Get the dual channel 8-bit data register address of the DAC module.
 *
 * @param DACx DAC instance.
 * @return The value of the address for DAC module's dual channel 8-bit data register .
 */
uint32_t DAC_GetDualChannelData8bRegAddr(DAC_Type * DACx);

/*!
 * @brief Get the dual channel 12-bit left-aligned data register address of the DAC module.
 *
 * @param DACx DAC instance.
 * @return The value of the address for DAC module's 12-bit dual channel left-aligned data register .
 */
uint32_t DAC_GetDualChannelData12bLeftRegAddr(DAC_Type * DACx);

/*!
 * @brief Get the dual channel 12-bit right-aligned data register address of the DAC module.
 *
 * @param DACx DAC instance.
 * @return The value of the address for DAC module's 12-bit dual channel right-aligned data register .
 */
uint32_t DAC_GetDualChannelData12bRightRegAddr(DAC_Type * DACx);

/*!
 *@}
 */

#endif /* __HAL_DAC_H__ */

