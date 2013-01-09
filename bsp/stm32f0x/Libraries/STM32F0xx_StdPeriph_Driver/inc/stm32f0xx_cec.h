/**
  ******************************************************************************
  * @file    stm32f0xx_cec.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   This file contains all the functions prototypes for the CEC firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
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
#ifndef __STM32F0XX_CEC_H
#define __STM32F0XX_CEC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup CEC
  * @{
  */
/* Exported types ------------------------------------------------------------*/
  
/** 
  * @brief CEC Init structure definition 
  */
typedef struct
{
  uint32_t CEC_SignalFreeTime;     /*!< Specifies the CEC Signal Free Time configuration.
                                   This parameter can be a value of @ref CEC_Signal_Free_Time */
  uint32_t CEC_RxTolerance;        /*!< Specifies the CEC Reception Tolerance.
                                   This parameter can be a value of @ref CEC_RxTolerance */
  uint32_t CEC_StopReception;      /*!< Specifies the CEC Stop Reception.
                                   This parameter can be a value of @ref CEC_Stop_Reception */
  uint32_t CEC_BitRisingError;     /*!< Specifies the CEC Bit Rising Error generation.
                                   This parameter can be a value of @ref CEC_Bit_Rising_Error_Generation */
  uint32_t CEC_LongBitPeriodError; /*!< Specifies the CEC Long Bit Error generation.
                                   This parameter can be a value of @ref CEC_Long_Bit_Error_Generation */
  uint32_t CEC_BRDNoGen;           /*!< Specifies the CEC Broadcast Error generation.
                                   This parameter can be a value of @ref CEC_BDR_No_Gen */
  uint32_t CEC_SFTOption;          /*!< Specifies the CEC Signal Free Time option.
                                   This parameter can be a value of @ref CEC_SFT_Option */

}CEC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup CEC_Exported_Constants
  * @{
  */

/** @defgroup CEC_Signal_Free_Time
  * @{
  */
#define CEC_SignalFreeTime_Standard     ((uint32_t)0x00000000) /*!< CEC Signal Free Time Standard         */
#define CEC_SignalFreeTime_1T           ((uint32_t)0x00000001) /*!< CEC  1.5 nominal data bit periods     */
#define CEC_SignalFreeTime_2T           ((uint32_t)0x00000002) /*!< CEC  2.5 nominal data bit periods     */
#define CEC_SignalFreeTime_3T           ((uint32_t)0x00000003) /*!< CEC  3.5 nominal data bit periods     */
#define CEC_SignalFreeTime_4T           ((uint32_t)0x00000004) /*!< CEC  4.5 nominal data bit periods     */
#define CEC_SignalFreeTime_5T           ((uint32_t)0x00000005) /*!< CEC  5.5 nominal data bit periods     */
#define CEC_SignalFreeTime_6T           ((uint32_t)0x00000006) /*!< CEC  6.5 nominal data bit periods     */
#define CEC_SignalFreeTime_7T           ((uint32_t)0x00000007) /*!< CEC  7.5 nominal data bit periods     */

#define IS_CEC_SIGNAL_FREE_TIME(TIME) (((TIME) == CEC_SignalFreeTime_Standard) || \
                                       ((TIME) == CEC_SignalFreeTime_1T)|| \
                                       ((TIME) == CEC_SignalFreeTime_2T)|| \
                                       ((TIME) == CEC_SignalFreeTime_3T)|| \
                                       ((TIME) == CEC_SignalFreeTime_4T)|| \
                                       ((TIME) == CEC_SignalFreeTime_5T)|| \
                                       ((TIME) == CEC_SignalFreeTime_6T)|| \
                                       ((TIME) == CEC_SignalFreeTime_7T))
/**
  * @}
  */

/** @defgroup CEC_RxTolerance
  * @{
  */
#define CEC_RxTolerance_Standard        ((uint32_t)0x00000000) /*!< Standard Tolerance Margin            */
#define CEC_RxTolerance_Extended        CEC_CFGR_RXTOL         /*!< Extended Tolerance Margin            */

#define IS_CEC_RX_TOLERANCE(TOLERANCE) (((TOLERANCE) == CEC_RxTolerance_Standard) || \
                                        ((TOLERANCE) == CEC_RxTolerance_Extended))
/**
  * @}
  */

/** @defgroup CEC_Stop_Reception
  * @{
  */
#define CEC_StopReception_Off           ((uint32_t)0x00000000) /*!< No RX Stop on bit Rising Error (BRE) */
#define CEC_StopReception_On            CEC_CFGR_BRESTP        /*!< RX Stop on bit Rising Error (BRE)    */

#define IS_CEC_STOP_RECEPTION(RECEPTION) (((RECEPTION) == CEC_StopReception_On) || \
                                          ((RECEPTION) == CEC_StopReception_Off))
/**
  * @}
  */

/** @defgroup CEC_Bit_Rising_Error_Generation
  * @{
  */
#define CEC_BitRisingError_Off          ((uint32_t)0x00000000) /*!< Bit Rising Error generation turned Off */
#define CEC_BitRisingError_On           CEC_CFGR_BREGEN        /*!< Bit Rising Error generation turned On  */

#define IS_CEC_BIT_RISING_ERROR(ERROR) (((ERROR) == CEC_BitRisingError_Off) || \
                                        ((ERROR) == CEC_BitRisingError_On))
/**
  * @}
  */

/** @defgroup CEC_Long_Bit_Error_Generation
  * @{
  */
#define CEC_LongBitPeriodError_Off      ((uint32_t)0x00000000)  /*!< Long Bit Period Error generation turned Off */
#define CEC_LongBitPeriodError_On       CEC_CFGR_LREGEN         /*!< Long Bit Period Error generation turned On  */

#define IS_CEC_LONG_BIT_PERIOD_ERROR(ERROR) (((ERROR) == CEC_LongBitPeriodError_Off) || \
                                             ((ERROR) == CEC_LongBitPeriodError_On))
/**
  * @}
  */

/** @defgroup CEC_BDR_No_Gen
  * @{
  */

#define CEC_BRDNoGen_Off      ((uint32_t)0x00000000)  /*!< Broadcast Bit Rising Error generation turned Off */
#define CEC_BRDNoGen_On       CEC_CFGR_BRDNOGEN       /*!< Broadcast Bit Rising Error generation turned On  */

#define IS_CEC_BDR_NO_GEN_ERROR(ERROR) (((ERROR) == CEC_BRDNoGen_Off) || \
                                        ((ERROR) == CEC_BRDNoGen_On))
/**
  * @}
  */

/** @defgroup CEC_SFT_Option
  * @{
  */
#define CEC_SFTOption_Off              ((uint32_t)0x00000000)  /*!< SFT option turned Off                   */
#define CEC_SFTOption_On               CEC_CFGR_SFTOPT         /*!< SFT option turned On                    */

#define IS_CEC_SFT_OPTION(OPTION) (((OPTION) == CEC_SFTOption_Off) || \
                                  ((OPTION) == CEC_SFTOption_On))
/**
  * @}
  */

/** @defgroup CEC_Own_Address
  * @{
  */
#define IS_CEC_ADDRESS(ADDRESS)         ((ADDRESS) < 0x10)

/**
  * @}
  */

/** @defgroup CEC_Interrupt_Configuration_definition
  * @{
  */
#define CEC_IT_TXACKE                   CEC_IER_TXACKEIE
#define CEC_IT_TXERR                    CEC_IER_TXERRIE
#define CEC_IT_TXUDR                    CEC_IER_TXUDRIE
#define CEC_IT_TXEND                    CEC_IER_TXENDIE
#define CEC_IT_TXBR                     CEC_IER_TXBRIE
#define CEC_IT_ARBLST                   CEC_IER_ARBLSTIE
#define CEC_IT_RXACKE                   CEC_IER_RXACKEIE
#define CEC_IT_LBPE                     CEC_IER_LBPEIE
#define CEC_IT_SBPE                     CEC_IER_SBPEIE
#define CEC_IT_BRE                      CEC_IER_BREIEIE
#define CEC_IT_RXOVR                    CEC_IER_RXOVRIE
#define CEC_IT_RXEND                    CEC_IER_RXENDIE
#define CEC_IT_RXBR                     CEC_IER_RXBRIE

#define IS_CEC_IT(IT) ((((IT) & (uint32_t)0xFFFFE000) == 0x00) && ((IT) != 0x00))

#define IS_CEC_GET_IT(IT) (((IT) == CEC_IT_TXACKE) || \
                           ((IT) == CEC_IT_TXERR)|| \
                           ((IT) == CEC_IT_TXUDR)|| \
                           ((IT) == CEC_IT_TXEND)|| \
                           ((IT) == CEC_IT_TXBR)|| \
                           ((IT) == CEC_IT_ARBLST)|| \
                           ((IT) == CEC_IT_RXACKE)|| \
                           ((IT) == CEC_IT_LBPE)|| \
                           ((IT) == CEC_IT_SBPE)|| \
                           ((IT) == CEC_IT_BRE)|| \
                           ((IT) == CEC_IT_RXOVR)|| \
                           ((IT) == CEC_IT_RXEND)|| \
                           ((IT) == CEC_IT_RXBR))
/**
  * @}
  */

/** @defgroup CEC_ISR_register_flags_definition
  * @{
  */
#define CEC_FLAG_TXACKE                 CEC_ISR_TXACKE
#define CEC_FLAG_TXERR                  CEC_ISR_TXERR
#define CEC_FLAG_TXUDR                  CEC_ISR_TXUDR
#define CEC_FLAG_TXEND                  CEC_ISR_TXEND
#define CEC_FLAG_TXBR                   CEC_ISR_TXBR
#define CEC_FLAG_ARBLST                 CEC_ISR_ARBLST
#define CEC_FLAG_RXACKE                 CEC_ISR_RXACKE
#define CEC_FLAG_LBPE                   CEC_ISR_LBPE
#define CEC_FLAG_SBPE                   CEC_ISR_SBPE
#define CEC_FLAG_BRE                    CEC_ISR_BRE
#define CEC_FLAG_RXOVR                  CEC_ISR_RXOVR
#define CEC_FLAG_RXEND                  CEC_ISR_RXEND
#define CEC_FLAG_RXBR                   CEC_ISR_RXBR

#define IS_CEC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFE000) == 0x00) && ((FLAG) != 0x00))

#define IS_CEC_GET_FLAG(FLAG) (((FLAG) == CEC_FLAG_TXACKE) || \
                               ((FLAG) == CEC_FLAG_TXERR)|| \
                               ((FLAG) == CEC_FLAG_TXUDR)|| \
                               ((FLAG) == CEC_FLAG_TXEND)|| \
                               ((FLAG) == CEC_FLAG_TXBR)|| \
                               ((FLAG) == CEC_FLAG_ARBLST)|| \
                               ((FLAG) == CEC_FLAG_RXACKE)|| \
                               ((FLAG) == CEC_FLAG_LBPE)|| \
                               ((FLAG) == CEC_FLAG_SBPE)|| \
                               ((FLAG) == CEC_FLAG_BRE)|| \
                               ((FLAG) == CEC_FLAG_RXOVR)|| \
                               ((FLAG) == CEC_FLAG_RXEND)|| \
                               ((FLAG) == CEC_FLAG_RXBR))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the CEC configuration to the default reset state *****/
void CEC_DeInit(void);

/* CEC_Initialization and Configuration functions *****************************/
void CEC_Init(CEC_InitTypeDef* CEC_InitStruct);
void CEC_StructInit(CEC_InitTypeDef* CEC_InitStruct);
void CEC_Cmd(FunctionalState NewState);
void CEC_ListenModeCmd(FunctionalState NewState);
void CEC_OwnAddressConfig(uint8_t CEC_OwnAddress);
void CEC_OwnAddressClear(void);

/* CEC_Data transfers functions ***********************************************/
void CEC_SendData(uint8_t Data);
uint8_t CEC_ReceiveData(void);
void CEC_StartOfMessage(void);
void CEC_EndOfMessage(void);

/* CEC_Interrupts and flags management functions ******************************/
void CEC_ITConfig(uint16_t CEC_IT, FunctionalState NewState);
FlagStatus CEC_GetFlagStatus(uint16_t CEC_FLAG);
void CEC_ClearFlag(uint32_t CEC_FLAG);
ITStatus CEC_GetITStatus(uint16_t CEC_IT);
void CEC_ClearITPendingBit(uint16_t CEC_IT);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_CEC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
