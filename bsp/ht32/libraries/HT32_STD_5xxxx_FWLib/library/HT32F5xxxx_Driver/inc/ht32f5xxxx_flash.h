/*********************************************************************************************************//**
 * @file    ht32f5xxxx_flash.h
 * @version $Rev:: 5496         $
 * @date    $Date:: 2021-07-19 #$
 * @brief   The header file of the FLASH library.
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
#ifndef __HT32F5XXXX_FLASH_H
#define __HT32F5XXXX_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Types FLASH exported types
  * @{
  */

/**
 * @brief  Enumeration of FLASH return status.
 */
typedef enum
{
  FLASH_COMPLETE              = 0,
  FLASH_ERR_ADDR_OUT_OF_RANGE,
  FLASH_ERR_WRITE_PROTECTED,
  FLASH_TIME_OUT
} FLASH_State;

/**
 * @brief  Enumeration of FLASH boot mode.
 */
typedef enum
{
  FLASH_BOOT_LOADER           = 1,
  FLASH_BOOT_MAIN             = 2
} FLASH_Vector;

typedef struct
{
  u32 WriteProtect[4];
  u32 MainSecurity;
  u32 OptionProtect;
} FLASH_OptionByte;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH exported constants
  * @{
  */

/* Flash Information                                                                                        */
#define FLASH_PAGE_SIZE               (LIBCFG_FLASH_PAGESIZE)   /* Flash page size                          */

#if (LIBCFG_FMC_PREFETCH)

/* Flash Wait State                                                                                         */
#define FLASH_WAITSTATE_0             (0x00000001)   /* FLASH zero wait state                               */
#define FLASH_WAITSTATE_1             (0x00000002)   /* FLASH one wait state                                */
#if (LIBCFG_FMC_WAIT_STATE_2)
#define FLASH_WAITSTATE_2             (0x00000003)   /* FLASH two wait state                                */
#endif

#if (LIBCFG_FMC_WAIT_STATE_2)
#define FLASH_WAITSTATE_MAX           (FLASH_WAITSTATE_2)
#else
#define FLASH_WAITSTATE_MAX           (FLASH_WAITSTATE_1)
#endif

#endif

/* FLASH OISR Flags                                                                                         */
#define FLASH_FLAG_ORFF               (0x00000001)   /* Operation Finished Flag                             */
#define FLASH_FLAG_ITADF              (0x00000002)   /* Invalid Target Address Flag                         */
#define FLASH_FLAG_OBEF               (0x00000004)   /* Option Byte Check Sum Error Flag                    */
#define FLASH_FLAG_IOCMF              (0x00000008)   /* Invalid Operation Command Flag                      */
#define FLASH_FLAG_OREF               (0x00000010)   /* Operation Error Flag                                */
#define FLASH_FLAG_RORFF              (0x00010000)   /* Raw Operation Finished Flag                         */
#define FLASH_FLAG_PPEF               (0x00020000)   /* Page Erase/Program Protected Error Flag             */

/* FLASH OIER                                                                                               */
#define FLASH_INT_ORFIEN              (0x00000001)   /* Flash Operation Finished Interrupt Enable           */
#define FLASH_INT_ITADIEN             (0x00000002)   /* Invalid Target Address Interrupt Enable             */
#define FLASH_INT_OBEIEN              (0x00000004)   /* Option Byte Checksum Error Interrupt Enable         */
#define FLASH_INT_IOCMIEN             (0x00000008)   /* Invalid Operation Command Interrupt Enable          */
#define FLASH_INT_OREIEN              (0x00000010)   /* Operation Error Interrupt Enable                    */
#define FLASH_INT_ALL                 (0x0000001F)   /* Flash all Interrupt Enable                          */

/* Option Bytes Address                                                                                     */
#define OPTION_BYTE_BASE              (0x1FF00000)   /* Option Byte Base Address                            */
#define OB_PP0                        (0x1FF00000)   /* Option Byte: Write Protection 0                     */
#define OB_PP1                        (0x1FF00004)   /* Option Byte: Write Protection 1                     */
#define OB_PP2                        (0x1FF00008)   /* Option Byte: Write Protection 2                     */
#define OB_PP3                        (0x1FF0000C)   /* Option Byte: Write Protection 3                     */
#define OB_CP                         (0x1FF00010)   /* Option Byte: Security Protection                    */
#define OB_CHECKSUM                   (0x1FF00020)   /* Option Byte: Checksum                               */

/* Flash Write Protection Page Mask                                                                         */
#if (LIBCFG_FLASH_2PAGE_PER_WPBIT)
  #define FLASH_WP_PAGE_SET(OP, PAGE)     (OP.WriteProtect[PAGE / 64] |= 1 << ((PAGE % 64) / 2))
  #define FLASH_WP_PAGE_CLEAR(OP, PAGE)   (OP.WriteProtect[PAGE / 64] &= ~(1 << ((PAGE % 64) / 2)))
  #define FLASH_IS_WP_PAGE(OP, PAGE)      (OP.WriteProtect[PAGE / 64] & (1 << ((PAGE % 64) / 2)))
#else
  #define FLASH_WP_PAGE_SET(OP, PAGE)     (OP.WriteProtect[PAGE / 32] |= 1 << (PAGE % 32))
  #define FLASH_WP_PAGE_CLEAR(OP, PAGE)   (OP.WriteProtect[PAGE / 32] &= ~(1 << (PAGE % 32)))
  #define FLASH_IS_WP_PAGE(OP, PAGE)      (OP.WriteProtect[PAGE / 32] & (1 << (PAGE % 32)))
#endif
#define FLASH_WP_ALLPAGE_SET(OP)        {u32 i; for (i = 0; i < 4; i++) { OP.WriteProtect[i] = 0xFFFFFFFF; } }

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Functions FLASH exported functions
  * @{
  */
#if (LIBCFG_FMC_PREFETCH)
void FLASH_SetWaitState(u32 FLASH_WAITSTATE_n);
void FLASH_PrefetchBufferCmd(ControlStatus NewState);
#endif
#if (LIBCFG_FMC_BRANCHCACHE)
void FLASH_BranchCacheCmd(ControlStatus NewState);
#endif
void FLASH_SetRemappingMode(FLASH_Vector RemapMode);
FLASH_State FLASH_ErasePage(u32 PageAddress);
FLASH_State FLASH_EraseOptionByte(void);
FLASH_State FLASH_MassErase(void);
FLASH_State FLASH_ProgramWordData(u32 Address, u32 Data);
FLASH_State FLASH_ProgramOptionByte(FLASH_OptionByte *Option);
void FLASH_GetOptionByteStatus(FLASH_OptionByte *Option);
void FLASH_IntConfig(u32 FLASH_INT, ControlStatus Cmd);
FlagStatus FLASH_GetIntStatus(u32 FLASH_FLAG_x);
void FLASH_ClearIntFlag(u32 FLASH_FLAG_x);
FLASH_State FLASH_WaitForOperationEnd(void);
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
