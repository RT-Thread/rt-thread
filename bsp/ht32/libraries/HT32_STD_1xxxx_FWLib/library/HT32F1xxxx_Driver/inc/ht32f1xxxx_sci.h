/*********************************************************************************************************//**
 * @file    ht32f1xxxx_sci.h
 * @version $Rev:: 122          $
 * @date    $Date:: 2017-06-13 #$
 * @brief   The header file of the SCI library.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F1XXXX_SCI_H
#define __HT32F1XXXX_SCI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @addtogroup SCI
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup SCI_Exported_Types SCI exported types
  * @{
  */
typedef struct
{
  u32 SCI_Mode;
  u32 SCI_Retry;
  u32 SCI_Convention;
  u32 SCI_CardPolarity;
  u32 SCI_ClockPrescale;
} SCI_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup SCI_Exported_Constants SCI exported constants
  * @{
  */
#define SCI_MODE_MANUAL                             ((u32)0x00000000)
#define SCI_MODE_SCI                                ((u32)0x00000008)

#define IS_SCI_MODE(MODE)                           ((MODE == SCI_MODE_MANUAL) || \
                                                     (MODE == SCI_MODE_SCI))


#define SCI_RETRY_NO                                ((u32)0x00000000)
#define SCI_RETRY_4                                 ((u32)0x00000012)
#define SCI_RETRY_5                                 ((u32)0x00000002)

#define IS_SCI_RETRY(RETRY)                         ((RETRY == SCI_RETRY_NO) || \
                                                     (RETRY == SCI_RETRY_4) || \
                                                     (RETRY == SCI_RETRY_5))


#define SCI_CONVENTION_DIRECT                       ((u32)0x00000000)
#define SCI_CONVENTION_INVERSE                      ((u32)0x00000001)

#define IS_SCI_CONVENTION(CONVENTION)               ((CONVENTION == SCI_CONVENTION_DIRECT) || \
                                                     (CONVENTION == SCI_CONVENTION_INVERSE))


#define SCI_CARDPOLARITY_LOW                        ((u32)0x00000000)
#define SCI_CARDPOLARITY_HIGH                       ((u32)0x00000040)

#define IS_SCI_CARD_POLARITY(POLARITY)              ((POLARITY == SCI_CARDPOLARITY_LOW) || \
                                                     (POLARITY == SCI_CARDPOLARITY_HIGH))


#define SCI_CLKPRESCALER_1                          ((u32)0x00000000)
#define SCI_CLKPRESCALER_2                          ((u32)0x00000001)
#define SCI_CLKPRESCALER_4                          ((u32)0x00000002)
#define SCI_CLKPRESCALER_6                          ((u32)0x00000003)
#define SCI_CLKPRESCALER_8                          ((u32)0x00000004)
#define SCI_CLKPRESCALER_10                         ((u32)0x00000005)
#define SCI_CLKPRESCALER_12                         ((u32)0x00000006)
#define SCI_CLKPRESCALER_14                         ((u32)0x00000007)
#define SCI_CLKPRESCALER_16                         ((u32)0x00000008)
#define SCI_CLKPRESCALER_18                         ((u32)0x00000009)
#define SCI_CLKPRESCALER_20                         ((u32)0x0000000A)
#define SCI_CLKPRESCALER_22                         ((u32)0x0000000B)
#define SCI_CLKPRESCALER_24                         ((u32)0x0000000C)
#define SCI_CLKPRESCALER_26                         ((u32)0x0000000D)
#define SCI_CLKPRESCALER_28                         ((u32)0x0000000E)
#define SCI_CLKPRESCALER_30                         ((u32)0x0000000F)
#define SCI_CLKPRESCALER_32                         ((u32)0x00000010)
#define SCI_CLKPRESCALER_34                         ((u32)0x00000011)
#define SCI_CLKPRESCALER_36                         ((u32)0x00000012)
#define SCI_CLKPRESCALER_38                         ((u32)0x00000013)
#define SCI_CLKPRESCALER_40                         ((u32)0x00000014)
#define SCI_CLKPRESCALER_42                         ((u32)0x00000015)
#define SCI_CLKPRESCALER_44                         ((u32)0x00000016)
#define SCI_CLKPRESCALER_46                         ((u32)0x00000017)
#define SCI_CLKPRESCALER_48                         ((u32)0x00000018)
#define SCI_CLKPRESCALER_50                         ((u32)0x00000019)
#define SCI_CLKPRESCALER_52                         ((u32)0x0000001A)
#define SCI_CLKPRESCALER_54                         ((u32)0x0000001B)
#define SCI_CLKPRESCALER_56                         ((u32)0x0000001C)
#define SCI_CLKPRESCALER_58                         ((u32)0x0000001D)
#define SCI_CLKPRESCALER_60                         ((u32)0x0000001E)
#define SCI_CLKPRESCALER_62                         ((u32)0x0000001F)
#define SCI_CLKPRESCALER_64                         ((u32)0x00000020)
#define SCI_CLKPRESCALER_66                         ((u32)0x00000021)
#define SCI_CLKPRESCALER_68                         ((u32)0x00000022)
#define SCI_CLKPRESCALER_70                         ((u32)0x00000023)
#define SCI_CLKPRESCALER_72                         ((u32)0x00000024)
#define SCI_CLKPRESCALER_74                         ((u32)0x00000025)
#define SCI_CLKPRESCALER_76                         ((u32)0x00000026)
#define SCI_CLKPRESCALER_78                         ((u32)0x00000027)
#define SCI_CLKPRESCALER_80                         ((u32)0x00000028)
#define SCI_CLKPRESCALER_82                         ((u32)0x00000029)
#define SCI_CLKPRESCALER_84                         ((u32)0x0000002A)
#define SCI_CLKPRESCALER_86                         ((u32)0x0000002B)
#define SCI_CLKPRESCALER_88                         ((u32)0x0000002C)
#define SCI_CLKPRESCALER_90                         ((u32)0x0000002D)
#define SCI_CLKPRESCALER_92                         ((u32)0x0000002E)
#define SCI_CLKPRESCALER_94                         ((u32)0x0000002F)
#define SCI_CLKPRESCALER_96                         ((u32)0x00000030)
#define SCI_CLKPRESCALER_98                         ((u32)0x00000031)
#define SCI_CLKPRESCALER_100                        ((u32)0x00000032)
#define SCI_CLKPRESCALER_102                        ((u32)0x00000033)
#define SCI_CLKPRESCALER_104                        ((u32)0x00000034)
#define SCI_CLKPRESCALER_106                        ((u32)0x00000035)
#define SCI_CLKPRESCALER_108                        ((u32)0x00000036)
#define SCI_CLKPRESCALER_110                        ((u32)0x00000037)
#define SCI_CLKPRESCALER_112                        ((u32)0x00000038)
#define SCI_CLKPRESCALER_114                        ((u32)0x00000039)
#define SCI_CLKPRESCALER_116                        ((u32)0x0000003A)
#define SCI_CLKPRESCALER_118                        ((u32)0x0000003B)
#define SCI_CLKPRESCALER_120                        ((u32)0x0000003C)
#define SCI_CLKPRESCALER_122                        ((u32)0x0000003D)
#define SCI_CLKPRESCALER_124                        ((u32)0x0000003E)
#define SCI_CLKPRESCALER_126                        ((u32)0x0000003F)

#define IS_SCI_CLOCK_PRESCALER(PRESCALER)           (PRESCALER <= 0x3F)


#define SCI_COMPENSATION_ENABLE                     ((u32)0x00008000)
#define SCI_COMPENSATION_DISABLE                    ((u32)0x00000000)

#define IS_SCI_ETU_COMPENSATION(COMPENSATION)       ((COMPENSATION == SCI_COMPENSATION_ENABLE) || \
                                                     (COMPENSATION == SCI_COMPENSATION_DISABLE))


#define SCI_CLK_HARDWARE                            ((u32)0x00000080)
#define SCI_CLK_SOFTWARE                            ((u32)0xFFFFFF7F)

#define IS_SCI_CLK_MODE(MODE)                       ((MODE == SCI_CLK_HARDWARE) || \
                                                     (MODE == SCI_CLK_SOFTWARE))


#define SCI_CLK_HIGH                                ((u32)0x00000004)
#define SCI_CLK_LOW                                 ((u32)0xFFFFFFFB)

#define IS_SCI_CLK(CLK)                             ((CLK == SCI_CLK_HIGH) || \
                                                     (CLK == SCI_CLK_LOW))


#define SCI_DIO_HIGH                                ((u32)0x00000008)
#define SCI_DIO_LOW                                 ((u32)0xFFFFFFF7)

#define IS_SCI_DIO(DIO)                             ((DIO == SCI_DIO_HIGH) || \
                                                     (DIO == SCI_DIO_LOW))


#define SCI_INT_PAR                                ((u32)0x00000001)
#define SCI_INT_RXC                                ((u32)0x00000002)
#define SCI_INT_TXC                                ((u32)0x00000004)
#define SCI_INT_WT                                 ((u32)0x00000008)
#define SCI_INT_CARD                               ((u32)0x00000040)
#define SCI_INT_TXBE                               ((u32)0x00000080)
#define SCI_INT_ALL                                ((u32)0x000000CF)

#define IS_SCI_INT(INT)                            (((INT & 0xFFFFFF30) == 0x0) && (INT != 0))



#define SCI_FLAG_PAR                                ((u32)0x00000001)
#define SCI_FLAG_RXC                                ((u32)0x00000002)
#define SCI_FLAG_TXC                                ((u32)0x00000004)
#define SCI_FLAG_WT                                 ((u32)0x00000008)
#define SCI_FLAG_CARD                               ((u32)0x00000040)
#define SCI_FLAG_TXBE                               ((u32)0x00000080)

#define IS_SCI_FLAG(FLAG)                           ((FLAG == SCI_FLAG_PAR) || \
                                                     (FLAG == SCI_FLAG_RXC) || \
                                                     (FLAG == SCI_FLAG_TXC) || \
                                                     (FLAG == SCI_FLAG_WT) || \
                                                     (FLAG == SCI_FLAG_CARD) || \
                                                     (FLAG == SCI_FLAG_TXBE))

#define IS_SCI_CLEAR_FLAG(FLAG)                     ((FLAG == SCI_FLAG_PAR) || \
                                                     (FLAG == SCI_FLAG_TXC) || \
                                                     (FLAG == SCI_FLAG_WT))


#define SCI_PDMAREQ_TX                              ((u32)0x00000100)
#define SCI_PDMAREQ_RX                              ((u32)0x00000200)

#define IS_SCI_PDMA_REQ(REQ)                        (((REQ & 0xFFFFFCFF) == 0x0) && (REQ != 0))


#define IS_SCI_ETU(ETU)                             ((ETU >= 12) & (ETU <= 2047))

#define IS_SCI_GUARDTIME(GUARDTIME)                 ((GUARDTIME >= 11) & (GUARDTIME <= 511))

#define IS_SCI_WAITING_TIME(TIME)                   ((TIME >= 372) & (TIME <= 16777215))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup SCI_Exported_Functions SCI exported functions
  * @{
  */
void SCI_DeInit(HT_SCI_TypeDef* SCIx);
void SCI_Init(HT_SCI_TypeDef* SCIx, SCI_InitTypeDef* SCI_InitStruct);
void SCI_StructInit(SCI_InitTypeDef* SCI_InitStruct);
void SCI_Cmd(HT_SCI_TypeDef* SCIx, ControlStatus NewState);
void SCI_ETUConfig(HT_SCI_TypeDef* SCIx, u32 SCI_ETU, u32 SCI_Compensation);
void SCI_SetGuardTimeValue(HT_SCI_TypeDef* SCIx, u16 SCI_GuardTime);
void SCI_SetWaitingTimeValue(HT_SCI_TypeDef* SCIx, u32 SCI_WaitingTime);
void SCI_WaitingTimeCounterCmd(HT_SCI_TypeDef* SCIx, ControlStatus NewState);
void SCI_SendData(HT_SCI_TypeDef* SCIx, u8 SCI_Data);
u8 SCI_ReceiveData(HT_SCI_TypeDef* SCIx);
void SCI_ClockModeConfig(HT_SCI_TypeDef* SCIx, u32 SCI_CLKMode);
void SCI_SoftwareClockCmd(HT_SCI_TypeDef* SCIx, u32 SCI_CLK);
void SCI_OutputDIO(HT_SCI_TypeDef* SCIx, u32 SCI_DIO);
void SCI_IntConfig(HT_SCI_TypeDef* SCIx, u32 SCI_Int, ControlStatus NewState);
FlagStatus SCI_GetFlagStatus(HT_SCI_TypeDef* SCIx, u32 SCI_Flag);
void SCI_ClearFlag(HT_SCI_TypeDef* SCIx, u32 SCI_Flag);
void SCI_PDMACmd(HT_SCI_TypeDef* SCIx, u32 SCI_PDMAREQ, ControlStatus NewState);
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

#endif
