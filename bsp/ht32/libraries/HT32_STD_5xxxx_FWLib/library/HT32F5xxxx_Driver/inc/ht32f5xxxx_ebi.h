/*********************************************************************************************************//**
 * @file    ht32f5xxxx_ebi.h
 * @version $Rev:: 2772         $
 * @date    $Date:: 2018-05-15 #$
 * @brief   The header file of the EBI library.
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
#ifndef __HT32F5XXXX_EBI_H
#define __HT32F5XXXX_EBI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup EBI
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup EBI_Exported_Types EBI exported types
  * @{
  */
typedef struct
{
  u32 EBI_Bank;
  u32 EBI_Mode;
  u32 EBI_IdleCycle;
  u32 EBI_ChipSelectPolarity;
  u32 EBI_AddressLatchPolarity;
  u32 EBI_WriteEnablePolarity;
  u32 EBI_ReadEnablePolarity;
  u32 EBI_IdleCycleTime;
  u32 EBI_AddressSetupTime;
  u32 EBI_AddressHoldTime;
  u32 EBI_WriteSetupTime;
  u32 EBI_WriteStrobeTime;
  u32 EBI_WriteHoldTime;
  u32 EBI_ReadSetupTime;
  u32 EBI_ReadStrobeTime;
  u32 EBI_ReadHoldTime;
} EBI_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup EBI_Exported_Constants EBI exported constants
  * @{
  */
#define EBI_BANK_0                                  ((u32)0x00000000)
#define EBI_BANK_1                                  ((u32)0x00000001)
#define EBI_BANK_2                                  ((u32)0x00000002)
#define EBI_BANK_3                                  ((u32)0x00000003)

#define IS_EBI_BANK(BANK)                           ((BANK == EBI_BANK_0) || \
                                                     (BANK == EBI_BANK_1) || \
                                                     (BANK == EBI_BANK_2) || \
                                                     (BANK == EBI_BANK_3))


#define EBI_MODE_D8A8                               ((u32)0x00000000)
#define EBI_MODE_D16A16ALE                          ((u32)0x00000001)
#define EBI_MODE_D8A24ALE                           ((u32)0x00000002)
#define EBI_MODE_D16                                ((u32)0x00000003)

#define IS_EBI_MODE(MODE)                           ((MODE == EBI_MODE_D8A8)      || \
                                                     (MODE == EBI_MODE_D16A16ALE) || \
                                                     (MODE == EBI_MODE_D8A24ALE)  || \
                                                     (MODE == EBI_MODE_D16))


#define EBI_IDLECYCLE_ENABLE                        ((u32)0x00000000)
#define EBI_IDLECYCLE_DISABLE                       ((u32)0x00001000)

#define IS_EBI_IDLECYCLE(IDLECYCLE)                 ((IDLECYCLE == EBI_IDLECYCLE_ENABLE) || \
                                                     (IDLECYCLE == EBI_IDLECYCLE_DISABLE))


#define EBI_CHIPSELECTPOLARITY_LOW                  ((u32)0x00000000)
#define EBI_CHIPSELECTPOLARITY_HIGH                 ((u32)0x00000001)

#define IS_EBI_CS_POLARITY(POLARITY)                ((POLARITY == EBI_CHIPSELECTPOLARITY_LOW) || \
                                                     (POLARITY == EBI_CHIPSELECTPOLARITY_HIGH))


#define EBI_ADDRESSLATCHPOLARITY_LOW                ((u32)0x00000000)
#define EBI_ADDRESSLATCHPOLARITY_HIGH               ((u32)0x00000001)

#define IS_EBI_ALE_POLARITY(POLARITY)               ((POLARITY == EBI_ADDRESSLATCHPOLARITY_LOW) || \
                                                     (POLARITY == EBI_ADDRESSLATCHPOLARITY_HIGH))


#define EBI_WRITEENABLEPOLARITY_LOW                 ((u32)0x00000000)
#define EBI_WRITEENABLEPOLARITY_HIGH                ((u32)0x00000001)

#define IS_EBI_WE_POLARITY(POLARITY)                ((POLARITY == EBI_WRITEENABLEPOLARITY_LOW) || \
                                                     (POLARITY == EBI_WRITEENABLEPOLARITY_HIGH))


#define EBI_READENABLEPOLARITY_LOW                  ((u32)0x00000000)
#define EBI_READENABLEPOLARITY_HIGH                 ((u32)0x00000001)

#define IS_EBI_RE_POLARITY(POLARITY)                ((POLARITY == EBI_READENABLEPOLARITY_LOW) || \
                                                     (POLARITY == EBI_READENABLEPOLARITY_HIGH))


#define IS_EBI_IDLE_CYCLE_TIME(TIME)                (TIME < 0x10)

#define IS_EBI_ADDRESS_SETUP_TIME(TIME)             (TIME < 0x10)

#define IS_EBI_ADDRESS_HOLD_TIME(TIME)              (TIME < 0x10)

#define IS_EBI_WRITE_SETUP_TIME(TIME)               (TIME < 0x10)

#define IS_EBI_WRITE_STROBE_TIME(TIME)              (TIME < 0x40)

#define IS_EBI_WRITE_HOLD_TIME(TIME)                (TIME < 0x10)

#define IS_EBI_READ_SETUP_TIME(TIME)                (TIME < 0x10)

#define IS_EBI_READ_STROBE_TIME(TIME)               (TIME < 0x40)

#define IS_EBI_READ_HOLD_TIME(TIME)                 (TIME < 0x10)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup EBI_Exported_Functions EBI exported functions
  * @{
  */
void EBI_DeInit(void);
void EBI_Init(EBI_InitTypeDef* EBI_InitStruct);
void EBI_StructInit(EBI_InitTypeDef* EBI_InitStruct);
void EBI_Cmd(u32 EBI_Bank, ControlStatus NewState);
FlagStatus EBI_GetBusyStatus(void);
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
