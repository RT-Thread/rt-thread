/*********************************************************************************************************//**
 * @file    ht32f5xxxx_wdt.h
 * @version $Rev:: 1704         $
 * @date    $Date:: 2017-08-17 #$
 * @brief   The header file of the WDT library.
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
#ifndef __HT32F5XXXX_WDT_H
#define __HT32F5XXXX_WDT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup WDT
  * @{
  */


/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup WDT_Exported_Constants WDT exported constants
  * @{
  */

/* WDT prescaler                                                                                            */
#define WDT_PRESCALER_1                           ((u16)0x0000)
#define WDT_PRESCALER_2                           ((u16)0x1000)
#define WDT_PRESCALER_4                           ((u16)0x2000)
#define WDT_PRESCALER_8                           ((u16)0x3000)
#define WDT_PRESCALER_16                          ((u16)0x4000)
#define WDT_PRESCALER_32                          ((u16)0x5000)
#define WDT_PRESCALER_64                          ((u16)0x6000)
#define WDT_PRESCALER_128                         ((u16)0x7000)

#define IS_WDT_PRESCALER(PRESCALER)               ((PRESCALER == WDT_PRESCALER_1) || \
                                                   (PRESCALER == WDT_PRESCALER_2) || \
                                                   (PRESCALER == WDT_PRESCALER_4) || \
                                                   (PRESCALER == WDT_PRESCALER_8) || \
                                                   (PRESCALER == WDT_PRESCALER_16) || \
                                                   (PRESCALER == WDT_PRESCALER_32) || \
                                                   (PRESCALER == WDT_PRESCALER_64) || \
                                                   (PRESCALER == WDT_PRESCALER_128))


/* WDT runs or halts in sleep and deep sleep1 mode                                                          */
/* WDT WDTSHLT mask                                                                                         */
#define MODE0_WDTSHLT_BOTH                        ((u32)0x00000000)
#define MODE0_WDTSHLT_SLEEP                       ((u32)0x00004000)
#define MODE0_WDTSHLT_HALT                        ((u32)0x00008000)

#define IS_WDT_WDTSHLT_MODE(WDT_Mode)             ((WDT_Mode == MODE0_WDTSHLT_BOTH) || \
                                                   (WDT_Mode == MODE0_WDTSHLT_SLEEP) || \
                                                   (WDT_Mode == MODE0_WDTSHLT_HALT))



/* WDT Flag                                                                                                 */
#define WDT_FLAG_UNDERFLOW                        ((u32)0x00000001)
#define WDT_FLAG_ERROR                            ((u32)0x00000002)


#define IS_WDT_FLAG(WDT_FLAG)                     ((WDT_FLAG == WDT_FLAG_UNDERFLOW) || \
                                                   (WDT_FLAG == WDT_FLAG_ERROR))


#define IS_WDT_RELOAD(WDTV)                       ((WDTV <= 0xFFF))

#define IS_WDT_DELTA(WDTD)                        ((WDTD <= 0xFFF))

#if (LIBCFG_LSE)
/* WDT Source Select                                                                                        */
#define WDT_SOURCE_LSI                            ((u32)0x00000000)
#define WDT_SOURCE_LSE                            ((u32)0x00000001)


#define IS_WDT_SOURCE_SELECT(WDT_SOURCE)          ((WDT_SOURCE == WDT_SOURCE_LSI) || \
                                                   (WDT_SOURCE == WDT_SOURCE_LSE))
#endif
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup WDT_Exported_Functions WDT exported functions
  * @{
  */
void WDT_DeInit(void);
void WDT_Cmd(ControlStatus NewState);
void WDT_HaltConfig(u32 WDT_Mode);
void WDT_ResetCmd(ControlStatus NewState);
void WDT_ProtectCmd(ControlStatus NewState);
void WDT_SetReloadValue(u16 WDTV);
u16 WDT_GetReloadValue(void);
void WDT_SetDeltaValue(u16 WDTD);
u16 WDT_GetDeltaValue(void);
void WDT_SetPrescaler(u16 WDT_PRESCALER);
u8 WDT_GetPrescaler(void);
void WDT_Restart(void);
FlagStatus WDT_GetFlagStatus (u32 WDT_FLAG);
void WDT_LockCmd(ControlStatus NewState);
#if (LIBCFG_LSE)
void WDT_SourceConfig(u32 WDT_SOURCE);
#endif
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
