/*********************************************************************************************************//**
 * @file    ht32f1xxxx_pwrcu.h
 * @version $Rev:: 2971         $
 * @date    $Date:: 2023-10-25 #$
 * @brief   The header file of the Power Control Unit library.
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
#ifndef __HT32F1XXXX_PWRCU_H
#define __HT32F1XXXX_PWRCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @addtogroup PWRCU
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup PWRCU_Exported_Types PWRCU exported types
  * @{
  */

/**
 * @brief Status of Power control unit
 */
typedef enum
{
  PWRCU_OK = 0,                     /*!< Ready for access or backup domain power-on reset is released       */
  PWRCU_TIMEOUT,                    /*!< Time out                                                           */
  PWRCU_ERROR                       /*!< Error                                                              */
} PWRCU_Status;
/**
 * @brief DMOS status
 */
typedef enum
{
  PWRCU_DMOS_STS_ON = 0,            /*!< DMOS on                                                            */
  PWRCU_DMOS_STS_OFF,               /*!< DMOS off                                                           */
  PWRCU_DMOS_STS_OFF_BY_BODRESET    /*!< DMOS off caused by brow out reset                                  */
} PWRCU_DMOSStatus;
/**
 * @brief LVD level selection
 */
typedef enum
{
  PWRCU_LVDS_LV1 = 0x00000000,      /*!< LVD level 1                                                        */
  PWRCU_LVDS_LV2 = 0x00020000,      /*!< LVD level 2                                                        */
  PWRCU_LVDS_LV3 = 0x00040000,      /*!< LVD level 3                                                        */
  PWRCU_LVDS_LV4 = 0x00060000,      /*!< LVD level 4                                                        */
  PWRCU_LVDS_LV5 = 0x00400000,      /*!< LVD level 5                                                        */
  PWRCU_LVDS_LV6 = 0x00420000,      /*!< LVD level 6                                                        */
  PWRCU_LVDS_LV7 = 0x00440000,      /*!< LVD level 7                                                        */
  PWRCU_LVDS_LV8 = 0x00460000       /*!< LVD level 8                                                        */
} PWRCU_LVDS_Enum;
#if (LIBCFG_PWRCU_LVDS_27_35)
  #define PWRCU_LVDS_2V7            PWRCU_LVDS_LV1
  #define PWRCU_LVDS_2V8            PWRCU_LVDS_LV2
  #define PWRCU_LVDS_2V9            PWRCU_LVDS_LV3
  #define PWRCU_LVDS_3V             PWRCU_LVDS_LV4
  #define PWRCU_LVDS_3V1            PWRCU_LVDS_LV5
  #define PWRCU_LVDS_3V2            PWRCU_LVDS_LV6
  #define PWRCU_LVDS_3V4            PWRCU_LVDS_LV7
  #define PWRCU_LVDS_3V5            PWRCU_LVDS_LV8
#elif (LIBCFG_PWRCU_LVDS_17_31)
  #define PWRCU_LVDS_1V75           PWRCU_LVDS_LV1
  #define PWRCU_LVDS_1V95           PWRCU_LVDS_LV2
  #define PWRCU_LVDS_2V15           PWRCU_LVDS_LV3
  #define PWRCU_LVDS_2V35           PWRCU_LVDS_LV4
  #define PWRCU_LVDS_2V55           PWRCU_LVDS_LV5
  #define PWRCU_LVDS_2V75           PWRCU_LVDS_LV6
  #define PWRCU_LVDS_2V95           PWRCU_LVDS_LV7
  #define PWRCU_LVDS_3V15           PWRCU_LVDS_LV8
#else
  #define PWRCU_LVDS_2V25           PWRCU_LVDS_LV1
  #define PWRCU_LVDS_2V4            PWRCU_LVDS_LV2
  #define PWRCU_LVDS_2V55           PWRCU_LVDS_LV3
  #define PWRCU_LVDS_2V7            PWRCU_LVDS_LV4
  #define PWRCU_LVDS_2V85           PWRCU_LVDS_LV5
  #define PWRCU_LVDS_3V             PWRCU_LVDS_LV6
  #define PWRCU_LVDS_3V15           PWRCU_LVDS_LV7
  #define PWRCU_LVDS_3V3            PWRCU_LVDS_LV8
#endif
/**
 * @brief BOD reset or interrupt selection
 */
typedef enum
{
  PWRCU_BODRIS_RESET = 0,  /*!< Reset the whole chip                                                        */
  PWRCU_BODRIS_INT   = 1,  /*!< Assert interrupt                                                            */
} PWRCU_BODRIS_Enum;
/**
 * @brief Sleep entry instruction selection
 */
typedef enum
{
  PWRCU_SLEEP_ENTRY_WFE = 0,          /*!< Sleep then wait for event                                        */
  PWRCU_SLEEP_ENTRY_WFI               /*!< Sleep then wait for interrupt                                    */
} PWRCU_SLEEP_ENTRY_Enum;
#if (!LIBCFG_NO_BACK_DOMAIN)
/**
 * @brief Backup register selection
 */
typedef enum
{
  PWRCU_BAKREG_0 = 0,
  PWRCU_BAKREG_1,
  PWRCU_BAKREG_2,
  PWRCU_BAKREG_3,
  PWRCU_BAKREG_4,
  PWRCU_BAKREG_5,
  PWRCU_BAKREG_6,
  PWRCU_BAKREG_7,
  PWRCU_BAKREG_8,
  PWRCU_BAKREG_9
} PWRCU_BAKREG_Enum;
#endif
/**
 * @brief Vdd18/Vdd15 power good source selection
 */
typedef enum
{
  PWRCU_VRDYSC_BKISO = 0, /*!< Vdd18/Vdd15 power good source come from BK_ISO bit in CKCU unit              */
  PWRCU_VRDYSC_VPOR       /*!< Vdd18/Vdd15 power good source come from Vdd18 power on reset                 */
} PWRCU_VRDYSC_Enum;
#if (!LIBCFG_PWRCU_LDO_LEGACY)
/**
 * @brief LDO operation mode selection
 */
typedef enum
{
  PWRCU_LDO_NORMAL = 0,     /*!< The LDO is operated in normal current mode                                 */
  PWRCU_LDO_LOWCURRENT      /*!< The LDO is operated in low current mode                                    */
} PWRCU_LDOMODE_Enum;
/**
 * @brief LDO output offset selection
 */
typedef enum
{
  PWRCU_LDO_DEFAULT      = 0x00000000,  /*!< The LDO default output voltage                                 */
  PWRCU_LDO_OFFSET_DEC5P = 0x00000010,  /*!< The LDO default output voltage offset -5%                      */
  PWRCU_LDO_OFFSET_ADD3P = 0x00000020,  /*!< The LDO default output voltage offset +3%                      */
  PWRCU_LDO_OFFSET_ADD7P = 0x00000030,  /*!< The LDO default output voltage offset +7%                      */
} PWRCU_LDOFTRM_Enum;
#endif
/**
 * @brief HSI ready counter bit length selection
 */
typedef enum
{
  PWRCU_HSIRCBL_4 = 0,  /*!< 4 bits                                                                         */
  PWRCU_HSIRCBL_5,      /*!< 5 bits                                                                         */
  PWRCU_HSIRCBL_6,      /*!< 5 bits                                                                         */
  PWRCU_HSIRCBL_7       /*!< 7 bits (Default)                                                               */
} PWRCU_HSIRCBL_Enum;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup PWRCU_Exported_Constants PWRCU exported constants
  * @{
  */

/* Definitions of PWRCU_FLAG                                                                                */
#define PWRCU_FLAG_PWRPOR       0x0001  /*!< Backup domain power-on reset flag                              */
#define PWRCU_FLAG_PD           0x0002  /*!< Power-Down flag                                                */
#define PWRCU_FLAG_WUP          0x0100  /*!< External WAKEUP pin flag                                       */

#define PWRCU_FLAG_BAKPOR       PWRCU_FLAG_PWRPOR

/* check PWRCU_LVDS parameter                                                                               */
#define IS_PWRCU_LVDS(x)        ((x == PWRCU_LVDS_LV1) || (x == PWRCU_LVDS_LV2) || \
                                 (x == PWRCU_LVDS_LV3) || (x == PWRCU_LVDS_LV4) || \
                                 (x == PWRCU_LVDS_LV5) || (x == PWRCU_LVDS_LV6) || \
                                 (x == PWRCU_LVDS_LV7) || (x == PWRCU_LVDS_LV8))

/* check PWRCU_BODRIS parameter                                                                             */
#define IS_PWRCU_BODRIS(x)      ((x == PWRCU_BODRIS_RESET) || (x == PWRCU_BODRIS_INT))

/* check PWRCU_HSIRCBL parameter                                                                            */
#define IS_PWRCU_HSIRCBL(x)     (x <= 3)

/* check PWRCU_SLEEP_ENTRY parameter                                                                        */
#define IS_PWRCU_SLEEP_ENTRY(x) ((x == PWRCU_SLEEP_ENTRY_WFI) || (x == PWRCU_SLEEP_ENTRY_WFE))

/* check PWRCU_BAKREG parameter                                                                             */
#define IS_PWRCU_BAKREG(x)      (x < 10)

/* check PWRCU_VRDY_SRC parameter                                                                           */
#define IS_PWRCU_VRDYSC(x)    ((x == PWRCU_VRDYSC_BKISO) || (x == PWRCU_VRDYSC_VPOR))

#if (!LIBCFG_PWRCU_LDO_LEGACY)
/* check PWRCU_LDOMODE parameter                                                                            */
#define IS_PWRCU_LDOMODE(x)     ((x == PWRCU_LDO_NORMAL) || (x == PWRCU_LDO_LOWCURRENT))
#if (!LIBCFG_NO_PWRCU_LDO_CFG_VOLTAGE)
/* check PWRCU_LDOFTRM parameter                                                                            */
#define IS_PWRCU_LDOFTRM(x)     ((x == PWRCU_LDO_DEFAULT)      || (x == PWRCU_LDO_OFFSET_DEC5P) || \
                                 (x == PWRCU_LDO_OFFSET_ADD3P) || (x == PWRCU_LDO_OFFSET_ADD7P))
#endif
#endif
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup PWRCU_Exported_Functions PWRCU exported functions
  * @{
  */
void PWRCU_DeInit(void);
PWRCU_Status PWRCU_CheckReadyAccessed(void);
u16 PWRCU_GetFlagStatus(void);
#if (!LIBCFG_NO_BACK_DOMAIN)
u32 PWRCU_ReadBackupRegister(PWRCU_BAKREG_Enum BAKREGx);
void PWRCU_WriteBackupRegister(PWRCU_BAKREG_Enum BAKREGx, u32 DATA);
#endif
void PWRCU_Sleep(PWRCU_SLEEP_ENTRY_Enum SleepEntry);
void PWRCU_DeepSleep1(PWRCU_SLEEP_ENTRY_Enum SleepEntry);
void PWRCU_DeepSleep2(PWRCU_SLEEP_ENTRY_Enum SleepEntry);
void PWRCU_PowerDown(void);
void PWRCU_SetLVDS(PWRCU_LVDS_Enum Level);
#if (!LIBCFG_PWRCU_LDO_LEGACY)
void PWRCU_SetLDOFTRM(PWRCU_LDOFTRM_Enum VolOffset);
void PWRCU_LDOConfig(PWRCU_LDOMODE_Enum Sel);
#endif
void PWRCU_LVDCmd(ControlStatus NewState);
void PWRCU_BODCmd(ControlStatus NewState);
void PWRCU_BODRISConfig(PWRCU_BODRIS_Enum Selection);
FlagStatus PWRCU_GetLVDFlagStatus(void);
FlagStatus PWRCU_GetBODFlagStatus(void);
PWRCU_DMOSStatus PWRCU_GetDMOSStatus(void);
void PWRCU_DMOSCmd(ControlStatus NewState);
void PWRCU_VRDYSourceConfig(PWRCU_VRDYSC_Enum Sel);
void PWRCU_LVDIntWakeupConfig(ControlStatus NewState);
void PWRCU_LVDEventWakeupConfig(ControlStatus NewState);
void PWRCU_WakeupPinCmd(ControlStatus NewState);
void PWRCU_WakeupPinIntConfig(ControlStatus NewState);
void PWRCU_HSIReadyCounterBitLengthConfig(PWRCU_HSIRCBL_Enum BitLength);
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
