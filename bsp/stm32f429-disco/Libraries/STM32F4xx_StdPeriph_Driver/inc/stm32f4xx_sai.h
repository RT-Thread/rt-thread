/**
  ******************************************************************************
  * @file    stm32f4xx_sai.h
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    08-November-2013
  * @brief   This file contains all the functions prototypes for the SAI 
  *          firmware library.  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_SAI_H
#define __STM32F4xx_SAI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup SAI
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  SAI Block Init structure definition  
  */

typedef struct
{
  uint32_t SAI_AudioMode;           /*!< Specifies the SAI Block Audio Mode.
                                         This parameter can be a value of @ref SAI_Block_Mode */

  uint32_t SAI_Protocol;             /*!< Specifies the SAI Block Protocol.
                                         This parameter can be a value of @ref SAI_Block_Protocol */

  uint32_t SAI_DataSize;            /*!< Specifies the SAI Block data size.
                                         This parameter can be a value of @ref SAI_Block_Data_Size 
                                         @note this value is ignored when AC'97 or SPDIF protocols are selected.*/

  uint32_t SAI_FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref SAI_Block_MSB_LSB_transmission 
                                         @note this value has no meaning when AC'97 or SPDIF protocols are selected.*/

  uint32_t SAI_ClockStrobing;       /*!< Specifies the SAI Block clock strobing edge sensitivity.
                                         This parameter can be a value of @ref SAI_Block_Clock_Strobing */

  uint32_t SAI_Synchro;             /*!< Specifies SAI Block synchronization
                                         This parameter can be a value of @ref SAI_Block_Synchronization */
 
  uint32_t SAI_OUTDRIV;             /*!< Specifies when SAI Block outputs are driven.
                                         This parameter can be a value of @ref SAI_Block_Output_Drive
                                         @note this value has to be set before enabling the audio block  
                                               but after the audio block configuration. */

  uint32_t SAI_NoDivider;            /*!< Specifies whether Master Clock will be divided or not.
                                         This parameter can be a value of @ref SAI_Block_NoDivider */

  uint32_t SAI_MasterDivider;       /*!< Specifies SAI Block Master Clock Divider. 
                                         @note the Master Clock Frequency is calculated accordingly to the  
                                               following formula : MCLK_x = SAI_CK_x/(MCKDIV[3:0]*2)*/
                                               
  uint32_t SAI_FIFOThreshold;      /*!< Specifies SAI Block FIFO Threshold.
                                         This parameter can be a value of @ref SAI_Block_Fifo_Threshold */                                                                                             
}SAI_InitTypeDef;

/** 
  * @brief  SAI Block Frame Init structure definition  
  */

typedef struct
{

  uint32_t SAI_FrameLength;         /*!< Specifies the Frame Length, the number of SCK clocks 
                                         for each audio frame.
                                         This parameter must be a number between 8 and 256.
                                         @note If master Clock MCLK_x pin is declared as an output, the frame length
                                               should be Aligned to a number equal to power of 2 in order to keep 
                                              in an audio frame, an integer number of MCLK pulses by bit Clock.                                                 
                                         @note this value is ignored when AC'97 or SPDIF protocols are selected.*/
                                   
  uint32_t SAI_ActiveFrameLength;   /*!< Specifies the Frame synchronization active level length.
                                         This Parameter specifies the length in number of bit clock (SCK + 1)  
                                         of the active level of FS signal in audio frame.
                                         This parameter must be a number between 1 and 128. 
                                         @note this value is ignored when AC'97 or SPDIF protocols are selected.*/

  uint32_t SAI_FSDefinition;        /*!< Specifies the Frame Synchronization definition.
                                         This parameter can be a value of @ref SAI_Block_FS_Definition 
                                         @note this value is ignored when AC'97 or SPDIF protocols are selected.*/

  uint32_t SAI_FSPolarity;          /*!< Specifies the Frame Synchronization Polarity.
                                         This parameter can be a value of @ref SAI_Block_FS_Polarity 
                                         @note this value is ignored when AC'97 or SPDIF protocols are selected.*/

  uint32_t SAI_FSOffset;            /*!< Specifies the Frame Synchronization Offset.
                                         This parameter can be a value of @ref SAI_Block_FS_Offset 
                                         @note this value is ignored when AC'97 or SPDIF protocols are selected.*/

}SAI_FrameInitTypeDef;

/**
  * @brief   SAI Block Slot Init Structure definition
  */    

typedef struct
{
  uint32_t SAI_FirstBitOffset;      /*!< Specifies the position of first data transfer bit in the slot.
                                         This parameter must be a number between 0 and 24. 
                                         @note this value is ignored when AC'97 or SPDIF protocols are selected.*/

  uint32_t SAI_SlotSize;            /*!< Specifies the Slot Size.
                                         This parameter can be a value of @ref SAI_Block_Slot_Size 
                                         @note this value is ignored when AC'97 or SPDIF protocols are selected.*/

  uint32_t SAI_SlotNumber;          /*!< Specifies the number of slot in the audio frame.
                                         This parameter must be a number between 1 and 16. 
                                         @note this value is ignored when AC'97 or SPDIF protocols are selected.*/

  uint32_t SAI_SlotActive;          /*!< Specifies the slots in audio frame that will be activated.
                                         This parameter can be a value of @ ref SAI_Block_Slot_Active 
                                         @note this value is ignored when AC'97 or SPDIF protocols are selected.*/ 
}SAI_SlotInitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup SAI_Exported_Constants
  * @{
  */

#define IS_SAI_PERIPH(PERIPH) ((PERIPH) == SAI1)

#define IS_SAI_BLOCK_PERIPH(PERIPH) (((PERIPH) == SAI1_Block_A) || \
                                     ((PERIPH) == SAI1_Block_B))


/** @defgroup SAI_Block_Mode 
  * @{
  */
#define SAI_Mode_MasterTx               ((uint32_t)0x00000000)
#define SAI_Mode_MasterRx               ((uint32_t)0x00000001)  
#define SAI_Mode_SlaveTx                ((uint32_t)0x00000002)
#define SAI_Mode_SlaveRx                ((uint32_t)0x00000003)
#define IS_SAI_BLOCK_MODE(MODE) (((MODE) == SAI_Mode_MasterTx) || \
                                 ((MODE) == SAI_Mode_MasterRx) || \
                                 ((MODE) == SAI_Mode_SlaveTx)  || \
                                 ((MODE) == SAI_Mode_SlaveRx))
/**
  * @}
  */

/** @defgroup SAI_Block_Protocol 
  * @{
  */

#define SAI_Free_Protocol                 ((uint32_t)0x00000000)
#define SAI_SPDIF_Protocol                ((uint32_t)SAI_xCR1_PRTCFG_0)
#define SAI_AC97_Protocol                 ((uint32_t)SAI_xCR1_PRTCFG_1)
#define IS_SAI_BLOCK_PROTOCOL(PROTOCOL) (((PROTOCOL) == SAI_Free_Protocol)  || \
                                         ((PROTOCOL) == SAI_SPDIF_Protocol) || \
                                         ((PROTOCOL) == SAI_AC97_Protocol))
/**
  * @}
  */

/** @defgroup SAI_Block_Data_Size 
  * @{
  */

#define SAI_DataSize_8b                   ((uint32_t)0x00000040)
#define SAI_DataSize_10b                  ((uint32_t)0x00000060)
#define SAI_DataSize_16b                  ((uint32_t)0x00000080)
#define SAI_DataSize_20b                  ((uint32_t)0x000000A0)
#define SAI_DataSize_24b                  ((uint32_t)0x000000C0)
#define SAI_DataSize_32b                  ((uint32_t)0x000000E0)
#define IS_SAI_BLOCK_DATASIZE(DATASIZE) (((DATASIZE) == SAI_DataSize_8b)  || \
                                         ((DATASIZE) == SAI_DataSize_10b) || \
                                         ((DATASIZE) == SAI_DataSize_16b) || \
                                         ((DATASIZE) == SAI_DataSize_20b) || \
                                         ((DATASIZE) == SAI_DataSize_24b) || \
                                         ((DATASIZE) == SAI_DataSize_32b))
/**
  * @}
  */ 

/** @defgroup SAI_Block_MSB_LSB_transmission 
  * @{
  */

#define SAI_FirstBit_MSB                  ((uint32_t)0x00000000)
#define SAI_FirstBit_LSB                  ((uint32_t)SAI_xCR1_LSBFIRST)
#define IS_SAI_BLOCK_FIRST_BIT(BIT) (((BIT) == SAI_FirstBit_MSB) || \
                                     ((BIT) == SAI_FirstBit_LSB))
/**
  * @}
  */

/** @defgroup SAI_Block_Clock_Strobing 
  * @{
  */

#define SAI_ClockStrobing_FallingEdge     ((uint32_t)0x00000000)
#define SAI_ClockStrobing_RisingEdge      ((uint32_t)SAI_xCR1_CKSTR)
#define IS_SAI_BLOCK_CLOCK_STROBING(CLOCK) (((CLOCK) == SAI_ClockStrobing_FallingEdge) || \
                                            ((CLOCK) == SAI_ClockStrobing_RisingEdge))
/**
  * @}
  */

/** @defgroup SAI_Block_Synchronization 
  * @{
  */

#define SAI_Asynchronous                   ((uint32_t)0x00000000)
#define SAI_Synchronous                    ((uint32_t)SAI_xCR1_SYNCEN_0)
#define IS_SAI_BLOCK_SYNCHRO(SYNCHRO) (((SYNCHRO) == SAI_Synchronous) || \
                                       ((SYNCHRO) == SAI_Asynchronous))
/**
  * @}
  */ 

/** @defgroup SAI_Block_Output_Drive 
  * @{
  */

#define SAI_OutputDrive_Disabled          ((uint32_t)0x00000000)
#define SAI_OutputDrive_Enabled           ((uint32_t)SAI_xCR1_OUTDRIV)
#define IS_SAI_BLOCK_OUTPUT_DRIVE(DRIVE) (((DRIVE) == SAI_OutputDrive_Disabled) || \
                                          ((DRIVE) == SAI_OutputDrive_Enabled))
/**
  * @}
  */ 



/** @defgroup SAI_Block_NoDivider 
  * @{
  */

#define SAI_MasterDivider_Enabled         ((uint32_t)0x00000000)
#define SAI_MasterDivider_Disabled        ((uint32_t)SAI_xCR1_NODIV)
#define IS_SAI_BLOCK_NODIVIDER(NODIVIDER) (((NODIVIDER) == SAI_MasterDivider_Enabled) || \
                                           ((NODIVIDER) == SAI_MasterDivider_Disabled))
/**
  * @}
  */
  

/** @defgroup SAI_Block_Master_Divider 
  * @{
  */
#define IS_SAI_BLOCK_MASTER_DIVIDER(DIVIDER) ((DIVIDER) <= 15)

/**
  * @}
  */
  
/** @defgroup SAI_Block_Frame_Length 
  * @{
  */
#define IS_SAI_BLOCK_FRAME_LENGTH(LENGTH) ((8 <= (LENGTH)) && ((LENGTH) <= 256))

/**
  * @}
  */
    
/** @defgroup SAI_Block_Active_FrameLength 
  * @{
  */
#define IS_SAI_BLOCK_ACTIVE_FRAME(LENGTH) ((1 <= (LENGTH)) && ((LENGTH) <= 128))

/**
  * @}
  */

/** @defgroup SAI_Block_FS_Definition 
  * @{
  */

#define SAI_FS_StartFrame                 ((uint32_t)0x00000000)
#define I2S_FS_ChannelIdentification      ((uint32_t)SAI_xFRCR_FSDEF)
#define IS_SAI_BLOCK_FS_DEFINITION(DEFINITION) (((DEFINITION) == SAI_FS_StartFrame) || \
                                                ((DEFINITION) == I2S_FS_ChannelIdentification))
/**
  * @}
  */

/** @defgroup SAI_Block_FS_Polarity 
  * @{
  */

#define SAI_FS_ActiveLow                  ((uint32_t)0x00000000)
#define SAI_FS_ActiveHigh                 ((uint32_t)SAI_xFRCR_FSPO)
#define IS_SAI_BLOCK_FS_POLARITY(POLARITY) (((POLARITY) == SAI_FS_ActiveLow) || \
                                            ((POLARITY) == SAI_FS_ActiveHigh))
/**
  * @}
  */
            
/** @defgroup SAI_Block_FS_Offset 
  * @{
  */
  
#define SAI_FS_FirstBit                   ((uint32_t)0x00000000)
#define SAI_FS_BeforeFirstBit             ((uint32_t)SAI_xFRCR_FSOFF)
#define IS_SAI_BLOCK_FS_OFFSET(OFFSET) (((OFFSET) == SAI_FS_FirstBit) || \
                                        ((OFFSET) == SAI_FS_BeforeFirstBit))
/**
  * @}
  */
  
/** @defgroup SAI_Block_Slot_FirstBit_Offset
  * @{
  */
#define IS_SAI_BLOCK_FIRSTBIT_OFFSET(OFFSET) ((OFFSET) <= 24)

/**
  * @}
  */

  /** @defgroup SAI_Block_Slot_Size
  * @{
  */
#define SAI_SlotSize_DataSize             ((uint32_t)0x00000000)  
#define SAI_SlotSize_16b                  ((uint32_t)SAI_xSLOTR_SLOTSZ_0)
#define SAI_SlotSize_32b                  ((uint32_t)SAI_xSLOTR_SLOTSZ_1)
#define IS_SAI_BLOCK_SLOT_SIZE(SIZE) (((SIZE) == SAI_SlotSize_DataSize) || \
                                      ((SIZE) == SAI_SlotSize_16b)      || \
                                      ((SIZE) == SAI_SlotSize_32b))

/**
  * @}
  */

/** @defgroup SAI_Block_Slot_Number
  * @{
  */
#define IS_SAI_BLOCK_SLOT_NUMBER(NUMBER) ((1 <= (NUMBER)) && ((NUMBER) <= 16))

/**
  * @}
  */
  
/** @defgroup SAI_Block_Slot_Active
  * @{
  */
#define SAI_Slot_NotActive           ((uint32_t)0x00000000)  
#define SAI_SlotActive_0             ((uint32_t)0x00010000)  
#define SAI_SlotActive_1             ((uint32_t)0x00020000)
#define SAI_SlotActive_2             ((uint32_t)0x00040000)
#define SAI_SlotActive_3             ((uint32_t)0x00080000)
#define SAI_SlotActive_4             ((uint32_t)0x00100000)
#define SAI_SlotActive_5             ((uint32_t)0x00200000)
#define SAI_SlotActive_6             ((uint32_t)0x00400000)
#define SAI_SlotActive_7             ((uint32_t)0x00800000)
#define SAI_SlotActive_8             ((uint32_t)0x01000000)
#define SAI_SlotActive_9             ((uint32_t)0x02000000)
#define SAI_SlotActive_10            ((uint32_t)0x04000000)
#define SAI_SlotActive_11            ((uint32_t)0x08000000)
#define SAI_SlotActive_12            ((uint32_t)0x10000000)
#define SAI_SlotActive_13            ((uint32_t)0x20000000)
#define SAI_SlotActive_14            ((uint32_t)0x40000000)
#define SAI_SlotActive_15            ((uint32_t)0x80000000)
#define SAI_SlotActive_ALL           ((uint32_t)0xFFFF0000)

#define IS_SAI_SLOT_ACTIVE(ACTIVE) ((ACTIVE) != 0)

/**
  * @}
  */

/** @defgroup SAI_Mono_Streo_Mode
  * @{
  */

#define SAI_MonoMode                      ((uint32_t)SAI_xCR1_MONO)
#define SAI_StreoMode                     ((uint32_t)0x00000000)
#define IS_SAI_BLOCK_MONO_STREO_MODE(MODE) (((MODE) == SAI_MonoMode) ||\
                                            ((MODE) == SAI_StreoMode))
/**
  * @}
  */

/** @defgroup SAI_TRIState_Management
  * @{
  */

#define SAI_Output_NotReleased              ((uint32_t)0x00000000)
#define SAI_Output_Released                 ((uint32_t)SAI_xCR2_TRIS)
#define IS_SAI_BLOCK_TRISTATE_MANAGEMENT(STATE) (((STATE) == SAI_Output_NotReleased) ||\
                                                 ((STATE) == SAI_Output_Released))
/**
  * @}
  */

/** @defgroup SAI_Block_Fifo_Threshold 
  * @{
  */

#define SAI_Threshold_FIFOEmpty           ((uint32_t)0x00000000)
#define SAI_FIFOThreshold_1QuarterFull    ((uint32_t)0x00000001)
#define SAI_FIFOThreshold_HalfFull        ((uint32_t)0x00000002) 
#define SAI_FIFOThreshold_3QuartersFull   ((uint32_t)0x00000003)
#define SAI_FIFOThreshold_Full            ((uint32_t)0x00000004)
#define IS_SAI_BLOCK_FIFO_THRESHOLD(THRESHOLD) (((THRESHOLD) == SAI_Threshold_FIFOEmpty)         || \
                                                ((THRESHOLD) == SAI_FIFOThreshold_1QuarterFull)  || \
                                                ((THRESHOLD) == SAI_FIFOThreshold_HalfFull)      || \
                                                ((THRESHOLD) == SAI_FIFOThreshold_3QuartersFull) || \
                                                ((THRESHOLD) == SAI_FIFOThreshold_Full))
/**
  * @}
  */
  
/** @defgroup SAI_Block_Companding_Mode
  * @{
  */
  
#define SAI_NoCompanding                  ((uint32_t)0x00000000)
#define SAI_ULaw_1CPL_Companding          ((uint32_t)0x00008000)
#define SAI_ALaw_1CPL_Companding          ((uint32_t)0x0000C000)
#define SAI_ULaw_2CPL_Companding          ((uint32_t)0x0000A000)
#define SAI_ALaw_2CPL_Companding          ((uint32_t)0x0000E000)
#define IS_SAI_BLOCK_COMPANDING_MODE(MODE)    (((MODE) == SAI_NoCompanding)        || \
                                              ((MODE) == SAI_ULaw_1CPL_Companding) || \
                                              ((MODE) == SAI_ALaw_1CPL_Companding) || \
                                              ((MODE) == SAI_ULaw_2CPL_Companding) || \
                                              ((MODE) == SAI_ALaw_2CPL_Companding))
/**
  * @}
  */

/** @defgroup SAI_Block_Mute_Value
  * @{
  */
  
#define SAI_ZeroValue                     ((uint32_t)0x00000000)
#define SAI_LastSentValue                 ((uint32_t)SAI_xCR2_MUTEVAL)
#define IS_SAI_BLOCK_MUTE_VALUE(VALUE)    (((VALUE) == SAI_ZeroValue)     || \
                                           ((VALUE) == SAI_LastSentValue))
/**
  * @}
  */

/** @defgroup SAI_Block_Mute_Frame_Counter
  * @{
  */
  
#define IS_SAI_BLOCK_MUTE_COUNTER(COUNTER) ((COUNTER) <= 63)

/**
  * @}
  */

/** @defgroup SAI_Block_Interrupts_Definition 
  * @{
  */

#define SAI_IT_OVRUDR                     ((uint32_t)SAI_xIMR_OVRUDRIE)
#define SAI_IT_MUTEDET                    ((uint32_t)SAI_xIMR_MUTEDETIE)
#define SAI_IT_WCKCFG                     ((uint32_t)SAI_xIMR_WCKCFGIE)
#define SAI_IT_FREQ                       ((uint32_t)SAI_xIMR_FREQIE)
#define SAI_IT_CNRDY                      ((uint32_t)SAI_xIMR_CNRDYIE)
#define SAI_IT_AFSDET                     ((uint32_t)SAI_xIMR_AFSDETIE)
#define SAI_IT_LFSDET                     ((uint32_t)SAI_xIMR_LFSDETIE)

#define IS_SAI_BLOCK_CONFIG_IT(IT) (((IT) == SAI_IT_OVRUDR)  || \
                                    ((IT) == SAI_IT_MUTEDET) || \
                                    ((IT) == SAI_IT_WCKCFG)  || \
                                    ((IT) == SAI_IT_FREQ)    || \
                                    ((IT) == SAI_IT_CNRDY)   || \
                                    ((IT) == SAI_IT_AFSDET)  || \
                                    ((IT) == SAI_IT_LFSDET))
/**
  * @}
  */

/** @defgroup SAI_Block_Flags_Definition 
  * @{
  */

#define SAI_FLAG_OVRUDR                   ((uint32_t)SAI_xSR_OVRUDR)
#define SAI_FLAG_MUTEDET                  ((uint32_t)SAI_xSR_MUTEDET)
#define SAI_FLAG_WCKCFG                   ((uint32_t)SAI_xSR_WCKCFG)
#define SAI_FLAG_FREQ                     ((uint32_t)SAI_xSR_FREQ)
#define SAI_FLAG_CNRDY                    ((uint32_t)SAI_xSR_CNRDY)
#define SAI_FLAG_AFSDET                   ((uint32_t)SAI_xSR_AFSDET)
#define SAI_FLAG_LFSDET                   ((uint32_t)SAI_xSR_LFSDET)

#define IS_SAI_BLOCK_GET_FLAG(FLAG) (((FLAG) == SAI_FLAG_OVRUDR)  || \
                                    ((FLAG) == SAI_FLAG_MUTEDET) || \
                                    ((FLAG) == SAI_FLAG_WCKCFG)  || \
                                    ((FLAG) == SAI_FLAG_FREQ)    || \
                                    ((FLAG) == SAI_FLAG_CNRDY)   || \
                                    ((FLAG) == SAI_FLAG_AFSDET)  || \
                                    ((FLAG) == SAI_FLAG_LFSDET))
                                   
#define IS_SAI_BLOCK_CLEAR_FLAG(FLAG) (((FLAG) == SAI_FLAG_OVRUDR)  || \
                                       ((FLAG) == SAI_FLAG_MUTEDET) || \
                                       ((FLAG) == SAI_FLAG_WCKCFG)  || \
                                       ((FLAG) == SAI_FLAG_FREQ)    || \
                                       ((FLAG) == SAI_FLAG_CNRDY)   || \
                                       ((FLAG) == SAI_FLAG_AFSDET)  || \
                                       ((FLAG) == SAI_FLAG_LFSDET))
/**
  * @}
  */
  
/** @defgroup SAI_Block_Fifo_Status_Level 
  * @{
  */
#define SAI_FIFOStatus_Empty              ((uint32_t)0x00000000)
#define SAI_FIFOStatus_Less1QuarterFull   ((uint32_t)0x00010000)
#define SAI_FIFOStatus_1QuarterFull       ((uint32_t)0x00020000)
#define SAI_FIFOStatus_HalfFull           ((uint32_t)0x00030000) 
#define SAI_FIFOStatus_3QuartersFull      ((uint32_t)0x00040000)
#define SAI_FIFOStatus_Full               ((uint32_t)0x00050000)

#define IS_SAI_BLOCK_FIFO_STATUS(STATUS) (((STATUS) == SAI_FIFOStatus_Less1QuarterFull ) || \
                                          ((STATUS) == SAI_FIFOStatus_HalfFull)          || \
                                          ((STATUS) == SAI_FIFOStatus_1QuarterFull)      || \
                                          ((STATUS) == SAI_FIFOStatus_3QuartersFull)     || \
                                          ((STATUS) == SAI_FIFOStatus_Full)              || \
                                          ((STATUS) == SAI_FIFOStatus_Empty)) 
/**
  * @}
  */

  
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/*  Function used to set the SAI configuration to the default reset state *****/ 
void SAI_DeInit(SAI_TypeDef* SAIx);

/* Initialization and Configuration functions *********************************/
void SAI_Init(SAI_Block_TypeDef* SAI_Block_x, SAI_InitTypeDef* SAI_InitStruct);
void SAI_FrameInit(SAI_Block_TypeDef* SAI_Block_x, SAI_FrameInitTypeDef* SAI_FrameInitStruct);
void SAI_SlotInit(SAI_Block_TypeDef* SAI_Block_x, SAI_SlotInitTypeDef* SAI_SlotInitStruct);
void SAI_StructInit(SAI_InitTypeDef* SAI_InitStruct);
void SAI_FrameStructInit(SAI_FrameInitTypeDef* SAI_FrameInitStruct);
void SAI_SlotStructInit(SAI_SlotInitTypeDef* SAI_SlotInitStruct);

void SAI_Cmd(SAI_Block_TypeDef* SAI_Block_x, FunctionalState NewState);
void SAI_MonoModeConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_Mono_StreoMode);
void SAI_TRIStateConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_TRIState);
void SAI_CompandingModeConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_CompandingMode);
void SAI_MuteModeCmd(SAI_Block_TypeDef* SAI_Block_x, FunctionalState NewState);
void SAI_MuteValueConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_MuteValue);
void SAI_MuteFrameCounterConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_MuteCounter);
void SAI_FlushFIFO(SAI_Block_TypeDef* SAI_Block_x);

/* Data transfers functions ***************************************************/ 
void SAI_SendData(SAI_Block_TypeDef* SAI_Block_x, uint32_t Data);
uint32_t SAI_ReceiveData(SAI_Block_TypeDef* SAI_Block_x);

/* DMA transfers management functions *****************************************/
void SAI_DMACmd(SAI_Block_TypeDef* SAI_Block_x, FunctionalState NewState);

/* Interrupts and flags management functions **********************************/
void SAI_ITConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT, FunctionalState NewState);
FlagStatus SAI_GetFlagStatus(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_FLAG);
void SAI_ClearFlag(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_FLAG);
ITStatus SAI_GetITStatus(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT);
void SAI_ClearITPendingBit(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT);
FunctionalState SAI_GetCmdStatus(SAI_Block_TypeDef* SAI_Block_x);
uint32_t SAI_GetFIFOStatus(SAI_Block_TypeDef* SAI_Block_x);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_SAI_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
