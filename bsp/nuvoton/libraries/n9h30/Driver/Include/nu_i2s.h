/**************************************************************************//**
* @file     i2s.h
* @brief    N9H30 I2S driver header file
*
* @note
* SPDX-License-Identifier: Apache-2.0
* Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#ifndef __NU_I2S_H__
#define __NU_I2S_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_I2S_Driver I2S Driver
  @{
*/

/** @addtogroup N9H30_I2S_EXPORTED_CONSTANTS I2S Exported Constants
  @{
*/

#define I2S_ERR_BUSY    -1 /*!< Interface is busy  */
#define I2S_ERR_IO      -2 /*!< IO contril error  */

#define I2S_DISABLE     0  /*!< Enable I2S  */
#define I2S_ENABLE      1  /*!< Disable I2S  */

#define I2S_PLAY        0  /*!< Play I2S audio */
#define I2S_REC         1  /*!< Reocrd I2S audio  */

#define PCM_PLAY        0  /*!< Play PCM audio  */
#define PCM_REC         1  /*!< Record PCM audio  */

#define I2S_SET_PLAY                0   /*!< Start or stop to play  */
#define I2S_START_PLAY  0  /*!< Start to play  */
#define I2S_STOP_PLAY   1  /*!< Stop to play  */

#define I2S_SET_RECORD              1   /*!< Start or stop to record  */
#define I2S_START_REC   0  /*!< Start to record  */
#define I2S_STOP_REC    1  /*!< Stop to record  */

#define I2S_SELECT_BLOCK            2   /*!< Select block function */
#define I2S_BLOCK_I2S   0  /*!< Select I2S function  */
#define I2S_BLOCK_PCM   1  /*!< Select PCM function  */

#define I2S_SELECT_BIT              3  /*!< Select data bit width  */
#define I2S_BIT_WIDTH_8 0  /*!< 8-bit  */
#define I2S_BIT_WIDTH_16    1  /*!< 16-bit  */
#define I2S_BIT_WIDTH_24    2  /*!< 24-bit  */

#define I2S_SET_PLAY_DMA_INT_SEL    4   /*!< Select play DMA interrupt request  */
#define I2S_SET_REC_DMA_INT_SEL     5   /*!< Select record DMA interrupt request  */
#define I2S_DMA_INT_END     0  /*!< End of buffer  */
#define I2S_DMA_INT_HALF       1  /*!< Half of buffer  */
#define I2S_DMA_INT_QUARTER    2  /*!< Quarter of buffer  */
#define I2S_DMA_INT_EIGHTH     3  /*!< Eighth of buffer  */

#define I2S_SET_ZEROCROSS           6  /*!< Enable or disable zero cross function  */
#define I2S_SET_DMACOUNTER          7  /*!< Enable or disable DMA counter function  */

#define I2S_SET_CHANNEL             8   /*!< Set channel number  */
#define I2S_CHANNEL_P_I2S_ONE         2  /*!< I2S one channel  */
#define I2S_CHANNEL_P_I2S_TWO         3  /*!< I2S two channels  */
#define I2S_CHANNEL_P_PCM_TWO         3  /*!< PCM two slots  */
#define I2S_CHANNEL_P_PCM_TWO_SLOT1   0  /*!< PCM two slots with all slot1 data  */
#define I2S_CHANNEL_P_PCM_TWO_SLOT0   1  /*!< PCM two slots with all slot0 data  */
#define I2S_CHANNEL_P_PCM_ONE_SLOT0   2  /*!< PCM one slot with all slot0 data  */

#define I2S_CHANNEL_R_I2S_LEFT_PCM_SLOT0    1 /*!< I2S left channel or PCM slot0  */
#define I2S_CHANNEL_R_I2S_RIGHT_PCM_SLOT1   2 /*!< I2S right channel or PCM slot1  */
#define I2S_CHANNEL_R_I2S_TWO           3 /*!< I2S two channels  */

#define I2S_SET_MODE                9   /*!< Select master or slave mode  */
#define I2S_MODE_MASTER  0  /*!< master mode  */
#define I2S_MODE_SLAVE   1  /*!< slave mode  */

#define I2S_SET_SPLITDATA           10  /*!< Enable or disable split data function */
#define I2S_SET_DMA_ADDRESS         11  /*!< Set DMA address  */
#define I2S_SET_DMA_LENGTH          12  /*!< Set DMA length  */
#define I2S_GET_DMA_CUR_ADDRESS     13  /*!< Get current DMA address  */

#define I2S_SET_I2S_FORMAT          14  /*!< Select I2S format  */
#define I2S_FORMAT_I2S  0  /*!< I2S format  */
#define I2S_FORMAT_MSB  1  /*!< MSB foramt */

#define I2S_SET_I2S_CALLBACKFUN     15  /*!< Install play or record call-back function */

#define I2S_SET_PCMSLOT             16  /*!< Set PCM interface start position of slot */
#define PCM_SLOT1_IN        0  /*!< Slot-1 in position */
#define PCM_SLOT1_OUT       1  /*!< Slot-1 out position */
#define PCM_SLOT2_IN        2  /*!< Slot-2 in position */
#define PCM_SLOT2_OUT       3  /*!< Slot-2 out position */

#define I2S_SET_PCM_FS_PERIOD       17  /*!< Set PCM FS pulse period */

/*@}*/ /* end of group N9H30_I2S_EXPORTED_CONSTANTS */

/** @addtogroup N9H30_I2S_EXPORTED_FUNCTIONS I2S Exported Functions
  @{
*/

int32_t i2sOpen(void);
void i2sClose(void);
void i2sInit(void);
int32_t i2sIoctl(uint32_t cmd, uint32_t arg0, uint32_t arg1);
void i2sSetSampleRate(uint32_t u32SourceClockRate, uint32_t u32SampleRate, uint32_t u32DataBit, uint32_t u32Channel);
void i2sSetMCLKFrequency(uint32_t u32SourceClockRate, uint32_t u32SampleRate);
void i2sSetPCMBCLKFrequency(uint32_t u32SourceClockRate, uint32_t u32Rate);

/*@}*/ /* end of group N9H30_I2S_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_I2S_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__NU_I2S_H__

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
