/*********************************************************************************************************//**
 * @file    ht32f5xxxx_pwrcu.h
 * @version $Rev:: 7054         $
 * @date    $Date:: 2023-07-24 #$
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
#ifndef __HT32F5XXXX_PWRCU_H
#define __HT32F5XXXX_PWRCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
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

/**
 * @brief Wakeup pin selection
 */
typedef enum
{
  PWRCU_WAKEUP_PIN_0 = 0,
  #if (LIBCFG_PWRCU_WAKEUP1)
  PWRCU_WAKEUP_PIN_1
  #endif
} PWRCU_WUP_Enum;
/**
 * @brief Wakeup pin trigger type selection
 */
#if (LIBCFG_PWRCU_WAKEUP_V01)
typedef enum
{
  PWRCU_WUP_POSITIVE_EDGE = 0,      /*!< Wakeup pin positive_edge triggered                                 */
  PWRCU_WUP_NEGATIVE_EDGE,          /*!< Wakeup pin negative_edge triggered                                 */
  PWRCU_WUP_HIGH_LEVEL,             /*!< Wakeup pin high-level sensitive                                    */
  PWRCU_WUP_LOW_LEVEL,              /*!< Wakeup pin low-level sensitive                                     */
} PWRCU_WUPTYPE_Enum;
#endif
typedef enum
{
  PWRCU_OK = 0,                     /*!< Ready for access or VDD power domain power-on reset is released    */
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
#if (LIBCFG_PWRCU_VDD_5V)
  #define PWRCU_LVDS_2V65           PWRCU_LVDS_LV1
  #define PWRCU_LVDS_2V85           PWRCU_LVDS_LV2
  #define PWRCU_LVDS_3V05           PWRCU_LVDS_LV3
  #define PWRCU_LVDS_3V25           PWRCU_LVDS_LV4
  #define PWRCU_LVDS_3V45           PWRCU_LVDS_LV5
  #define PWRCU_LVDS_4V25           PWRCU_LVDS_LV6
  #define PWRCU_LVDS_4V45           PWRCU_LVDS_LV7
  #define PWRCU_LVDS_4V65           PWRCU_LVDS_LV8
#elif (LIBCFG_PWRCU_VDD_2V0_3V6)
  #define PWRCU_LVDS_2V25           PWRCU_LVDS_LV1
  #define PWRCU_LVDS_2V4            PWRCU_LVDS_LV2
  #define PWRCU_LVDS_2V55           PWRCU_LVDS_LV3
  #define PWRCU_LVDS_2V7            PWRCU_LVDS_LV4
  #define PWRCU_LVDS_2V85           PWRCU_LVDS_LV5
  #define PWRCU_LVDS_3V             PWRCU_LVDS_LV6
  #define PWRCU_LVDS_3V15           PWRCU_LVDS_LV7
  #define PWRCU_LVDS_3V3            PWRCU_LVDS_LV8
#else
  #define PWRCU_LVDS_1V75           PWRCU_LVDS_LV1
  #define PWRCU_LVDS_1V95           PWRCU_LVDS_LV2
  #define PWRCU_LVDS_2V15           PWRCU_LVDS_LV3
  #define PWRCU_LVDS_2V35           PWRCU_LVDS_LV4
  #define PWRCU_LVDS_2V55           PWRCU_LVDS_LV5
  #define PWRCU_LVDS_2V75           PWRCU_LVDS_LV6
  #define PWRCU_LVDS_2V95           PWRCU_LVDS_LV7
  #define PWRCU_LVDS_3V15           PWRCU_LVDS_LV8
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
#if (LIBCFG_BAKREG)
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
 * @brief Vdd15 power good source selection
 */
typedef enum
{
  PWRCU_V15RDYSC_V33ISO = 0, /*!< Vdd15 power good source come from BK_ISO bit in CKCU unit                 */
  PWRCU_V15RDYSC_V15POR      /*!< Vdd15 power good source come from Vdd15 power on reset                    */
} PWRCU_V15RDYSC_Enum;
/**
 * @brief LDO operation mode selection
 */
typedef enum
{
  PWRCU_LDO_NORMAL = 0,     /*!< The LDO is operated in normal current mode                                 */
  PWRCU_LDO_LOWCURRENT      /*!< The LDO is operated in low current mode                                    */
} PWRCU_LDOMODE_Enum;
#if defined(USE_HT32F52342_52) || defined(USE_HT32F5826)
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
#endif
#if (LIBCFG_PWRCU_VREG)
/**
 * @brief VREG output voltage selection
 */
typedef enum
{
  #if (LIBCFG_PWRCU_VREG_2V5)
  PWRCU_VREG_2V5 = 0x08000000,      /*!< VREG output voltage is 2.5 V                                       */
  #else
  PWRCU_VREG_4V0 = 0x08000000,      /*!< VREG output voltage is 4.0 V                                       */
  #endif
  PWRCU_VREG_3V3 = 0x00000000,      /*!< VREG output voltage is 3.3 V                                       */
  PWRCU_VREG_3V0 = 0x04000000,      /*!< VREG output voltage is 3.0 V                                       */
  PWRCU_VREG_1V8 = 0x0C000000,      /*!< VREG output voltage is 1.8 V                                       */
} PWRCU_VREG_VOLT_Enum;
/**
 * @brief VREG operation mode
 */
typedef enum
{
  PWRCU_VREG_DISABLE = 0x00000000,  /*!< VREG is disabled                                                   */
  PWRCU_VREG_ENABLE  = 0x01000000,  /*!< VREG is enabled                                                    */
  PWRCU_VREG_BYPASS  = 0x02000000,  /*!< VREG is bypassed                                                   */
} PWRCU_VREG_MODE_Enum;
#endif
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup PWRCU_Exported_Constants PWRCU exported constants
  * @{
  */

/* Definitions of PWRCU_FLAG                                                                                */
#if (!LIBCFG_PWRCU_NO_VDDPORF)
#define PWRCU_FLAG_PWRPOR       0x0001  /*!< VDD power domain power-on reset flag                           */
#endif
#if (!LIBCFG_PWRCU_NO_PDF)
#define PWRCU_FLAG_PD           0x0002  /*!< Power-Down flag                                                */
#endif
#if (LIBCFG_PWRCU_PORF)
#define PWRCU_FLAG_POR          0x0010  /*!< Power-on reset flag                                            */
#endif
#define PWRCU_FLAG_WUP          0x0100  /*!< External WAKEUP pin flag                                       */
#define PWRCU_FLAG_WUP0         0x0100  /*!< External WAKEUP0 pin flag                                      */
#if (LIBCFG_PWRCU_WAKEUP1)
#define PWRCU_FLAG_WUP1         0x0200  /*!< External WAKEUP1 pin flag                                      */
#endif

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

/* check PWRCU_V15RDY_SRC parameter                                                                         */
#define IS_PWRCU_V15RDYSC(x)    ((x == PWRCU_V15RDYSC_V33ISO) || (x == PWRCU_V15RDYSC_V15POR))

/* check PWRCU_LDOMODE parameter                                                                            */
#define IS_PWRCU_LDOMODE(x)     ((x == PWRCU_LDO_NORMAL) || (x == PWRCU_LDO_LOWCURRENT))

/* check PWRCU_WUP parameter                                                                                */
#define IS_PWRCU_WAKEUPPIN(x)   (IS_PWRCU_WAKE0(x) || IS_PWRCU_WAKE1(x))

#define IS_PWRCU_WAKE0(x)       (x == PWRCU_WAKEUP_PIN_0)

#if (LIBCFG_PWRCU_WAKEUP1)
#define IS_PWRCU_WAKE1(x)       (x == PWRCU_WAKEUP_PIN_1)
#else
#define IS_PWRCU_WAKE1(x)       (0)
#endif

/* check PWRCU_WUPTYPE parameter                                                                            */
#define IS_PWRCU_TRIGGERTYPE(x)  ((x == PWRCU_WUP_POSITIVE_EDGE) || \
                                  (x == PWRCU_WUP_NEGATIVE_EDGE) || \
                                  (x == PWRCU_WUP_HIGH_LEVEL)    || \
                                  (x == PWRCU_WUP_LOW_LEVEL))

#if (LIBCFG_PWRCU_VREG)
#define IS_PWRCU_VREG_VOLT(x)   ((IS_PWRCU_VREG_VOLT_L2(x)) || \
                                 (x == PWRCU_VREG_3V3) || \
                                 (x == PWRCU_VREG_3V0) || \
                                 (x == PWRCU_VREG_1V8))

#if (LIBCFG_PWRCU_VREG_2V5)
#define IS_PWRCU_VREG_VOLT_L2(x) (x == PWRCU_VREG_2V5)
#else
#define IS_PWRCU_VREG_VOLT_L2(x) (x == PWRCU_VREG_4V0)
#endif

#define IS_PWRCU_VREG_MODE(x)   ((x == PWRCU_VREG_DISABLE) || \
                                 (x == PWRCU_VREG_ENABLE) || \
                                 (x == PWRCU_VREG_BYPASS))


#endif

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup PWRCU_Exported_Functions PWRCU exported functions
  * @{
  */
void PWRCU_DeInit(void);
#if (!LIBCFG_NO_PWRCU_TEST_REG)
PWRCU_Status PWRCU_CheckReadyAccessed(void);
#endif
u16 PWRCU_GetFlagStatus(void);
#if (LIBCFG_BAKREG)
u32 PWRCU_ReadBackupRegister(PWRCU_BAKREG_Enum BAKREGx);
void PWRCU_WriteBackupRegister(PWRCU_BAKREG_Enum BAKREGx, u32 DATA);
#endif
void PWRCU_Sleep(PWRCU_SLEEP_ENTRY_Enum SleepEntry);
void PWRCU_DeepSleep1(PWRCU_SLEEP_ENTRY_Enum SleepEntry);
void PWRCU_DeepSleep2(PWRCU_SLEEP_ENTRY_Enum SleepEntry);
#if !defined(USE_HT32F52220_30)
void PWRCU_DeepSleep2Ex(PWRCU_SLEEP_ENTRY_Enum SleepEntry);
#endif
#if (!LIBCFG_PWRCU_NO_PD_MODE)
void PWRCU_PowerDown(void);
#endif
void PWRCU_SetLVDS(PWRCU_LVDS_Enum Level);
void PWRCU_LDOConfig(PWRCU_LDOMODE_Enum Sel);
void PWRCU_LVDCmd(ControlStatus NewState);
void PWRCU_BODCmd(ControlStatus NewState);
void PWRCU_BODRISConfig(PWRCU_BODRIS_Enum Selection);
FlagStatus PWRCU_GetLVDFlagStatus(void);
FlagStatus PWRCU_GetBODFlagStatus(void);
PWRCU_DMOSStatus PWRCU_GetDMOSStatus(void);
void PWRCU_DMOSCmd(ControlStatus NewState);
#if (LIBCFG_PWRCU_V15_READY_SOURCE)
void PWRCU_V15RDYSourceConfig(PWRCU_V15RDYSC_Enum Sel);
#endif
void PWRCU_LVDIntWakeupConfig(ControlStatus NewState);
void PWRCU_LVDEventWakeupConfig(ControlStatus NewState);
#if (LIBCFG_PWRCU_VREG)
void PWRCU_SetVREG(PWRCU_VREG_VOLT_Enum Volt);
void PWRCU_VREGConfig(PWRCU_VREG_MODE_Enum Mode);
#endif
void PWRCU_WakeupPinCmd(ControlStatus NewState);
#if (LIBCFG_PWRCU_WAKEUP_V01)
void PWRCU_WakeupMultiPinCmd(PWRCU_WUP_Enum Pin, PWRCU_WUPTYPE_Enum Type, ControlStatus NewState);
#endif
#if defined(USE_HT32F52342_52) || defined(USE_HT32F5826)
void PWRCU_HSIReadyCounterBitLengthConfig(PWRCU_HSIRCBL_Enum BitLength);
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
