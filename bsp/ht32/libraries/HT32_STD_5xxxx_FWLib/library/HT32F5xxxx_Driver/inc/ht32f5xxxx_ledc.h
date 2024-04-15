/*********************************************************************************************************//**
 * @file    ht32f5xxxx_ledc.h
 * @version $Rev:: 6386         $
 * @date    $Date:: 2022-10-27 #$
 * @brief   The header file of the LED Controller library.
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
#ifndef __HT32F5XXXX_LEDC_H
#define __HT32F5XXXX_LEDC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup LEDC
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup LEDC_Exported_Types LEDC exported types
  * @{
  */

/**
 * @brief Selection of LEDC clock source
 */
typedef enum
{
  LEDC_SRC_PCLK = 0,
  LEDC_SRC_LSI,                    /*!< Low speed internal clock, about 32KHz                               */
  LEDC_SRC_LSE                     /*!< Low speed external 32768 Hz clock                                   */
} LEDC_SRC_Enum;

/**
 * @brief Selection of LEDC duty clock numbers
 */
typedef enum
{
  LEDC_DTYNUM_8 = 0,
  LEDC_DTYNUM_16,
  LEDC_DTYNUM_32,
  LEDC_DTYNUM_64
} LEDC_DTYNUM_Enum;

/**
 * @brief Definition of LEDC Init Structure
 */
typedef struct
{
  LEDC_SRC_Enum    LEDC_ClockSource;
  LEDC_DTYNUM_Enum LEDC_DutyClockNumber;
  u32              LEDC_ClockPrescaler;
  u32              LEDC_COMxEN;
  u32              LEDC_DeadTime;
} LEDC_InitTypeDef;

/**
 * @brief Enumeration of LED layout mode.
 */
typedef enum
{
  COMMON_CATHODE,          /*!< LEDC SEG output polarity is non-inverted. */
                           /*!< LEDC COM output polarity is non-inverted.*/
  COMMON_CATHODE_WITH_NPN, /*!< LEDC SEG output polarity is non-inverted. */
                           /*!< LEDC COM output polarity is inverted.*/
  COMMON_ANODE_WITH_PNP,   /*!< LEDC SEG output polarity is inverted. */
                           /*!< LEDC COM output polarity is non-inverted.*/
  COMMON_ANODE_WITH_NPN,   /*!< LEDC SEG output polarity is inverted. */
                           /*!< LEDC COM output polarity is inverted.*/
} LEDC_Mode;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup LEDC_Exported_Constants LEDC exported constants
  * @{
  */

/* Definitions of LEDCER                                                                                    */
#define LEDC_COM0EN       0x0001   /*!< LEDC COM0 enable                                                    */
#define LEDC_COM1EN       0x0002   /*!< LEDC COM1 enable                                                    */
#define LEDC_COM2EN       0x0004   /*!< LEDC COM2 enable                                                    */
#define LEDC_COM3EN       0x0008   /*!< LEDC COM3 enable                                                    */
#define LEDC_COM4EN       0x0010   /*!< LEDC COM4 enable                                                    */
#define LEDC_COM5EN       0x0020   /*!< LEDC COM5 enable                                                    */
#define LEDC_COM6EN       0x0040   /*!< LEDC COM6 enable                                                    */
#define LEDC_COM7EN       0x0080   /*!< LEDC COM7 enable                                                    */
#if (LIBCFG_LEDC_NO_COM_8_11 == 0)
#define LEDC_COM8EN       0x0100   /*!< LEDC COM8 enable                                                    */
#define LEDC_COM9EN       0x0200   /*!< LEDC COM9 enable                                                    */
#define LEDC_COM10EN      0x0400   /*!< LEDC COM10 enable                                                   */
#define LEDC_COM11EN      0x0800   /*!< LEDC COM11 enable                                                   */
#endif

/* Definitions of COMxPOL                                                                                   */
#define LEDC_COM0POL       0x00000001   /*!< LEDC COM0 polarity                                            */
#define LEDC_COM1POL       0x00000002   /*!< LEDC COM1 polarity                                            */
#define LEDC_COM2POL       0x00000004   /*!< LEDC COM2 polarity                                            */
#define LEDC_COM3POL       0x00000008   /*!< LEDC COM3 polarity                                            */
#define LEDC_COM4POL       0x00000010   /*!< LEDC COM4 polarity                                            */
#define LEDC_COM5POL       0x00000020   /*!< LEDC COM5 polarity                                            */
#define LEDC_COM6POL       0x00000040   /*!< LEDC COM6 polarity                                            */
#define LEDC_COM7POL       0x00000080   /*!< LEDC COM7 polarity                                            */
#if (LIBCFG_LEDC_NO_COM_8_11 == 0)
#define LEDC_COM8POL       0x00000100   /*!< LEDC COM8 polarity                                            */
#define LEDC_COM9POL       0x00000200   /*!< LEDC COM9 polarity                                            */
#define LEDC_COM10POL      0x00000400   /*!< LEDC COM10 polarity                                           */
#define LEDC_COM11POL      0x00000800   /*!< LEDC COM11 polarity                                           */
#endif

/* Definitions of SEGxPOL                                                                                   */
#define LEDC_SEG0POL       0x00010000   /*!< LEDC SEG0 polarity                                            */
#define LEDC_SEG1POL       0x00020000   /*!< LEDC SEG1 polarity                                            */
#define LEDC_SEG2POL       0x00040000   /*!< LEDC SEG2 polarity                                            */
#define LEDC_SEG3POL       0x00080000   /*!< LEDC SEG3 polarity                                            */
#define LEDC_SEG4POL       0x00100000   /*!< LEDC SEG4 polarity                                            */
#define LEDC_SEG5POL       0x00200000   /*!< LEDC SEG5 polarity                                            */
#define LEDC_SEG6POL       0x00400000   /*!< LEDC SEG6 polarity                                            */
#define LEDC_SEG7POL       0x00800000   /*!< LEDC SEG7 polarity                                            */

#define LEDC_FLAG_FRAME           (1UL << 0)
#define LEDC_INT_FRAME            (1UL << 0)


/* check parameter of the LEDC mode                                                                         */
#define IS_LEDC_MODE(x)      ((x == COMMON_CATHODE)        || (x == COMMON_CATHODE_WITH_NPN)  || \
                              (x == COMMON_ANODE_WITH_PNP) || (x == COMMON_ANODE_WITH_NPN))

/**
 * @brief Used to check LEDC_SRC_Enum parameter
 */
#define IS_LEDC_SRC(x)       ((x == LEDC_SRC_PCLK) || (x == LEDC_SRC_LSI) || (x == LEDC_SRC_LSE))
#define IS_LEDC_DTYNUM(x)    ((x == LEDC_DTYNUM_8) || (x == LEDC_DTYNUM_16) || (x == LEDC_DTYNUM_32) ||\
                              (x == LEDC_DTYNUM_64))
#define IS_LEDC_PSC(x)        (x < 4096)
#define IS_LEDC_DTCR(x)       (x < 64)
#define IS_LEDC_COMEN(x)    (((x & 0xF000) == 0x0) && (x != 0x0))
#define IS_LEDC_COMPOL(x)   (((x & 0xFFFFF000) == 0x0) && (x != 0x0))
#define IS_LEDC_SEGPOL(x)   (((x & 0xFF00FFFF) == 0x0) && (x != 0x0))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup LEDC_Exported_Functions LEDC exported functions
  * @{
  */
void LEDC_DeInit(void);
void LEDC_Init(LEDC_InitTypeDef* LEDC_InitStruct);
void LEDC_ClockSourceConfig(LEDC_SRC_Enum Source);
void LEDC_Cmd(ControlStatus NewState);
void LEDC_IntConfig(ControlStatus NewState);
FlagStatus LEDC_GetFlagStatus(void);
void LEDC_ClearFlagStatus(void);
void LEDC_COMxConfig(u32 LEDC_COMxEN, ControlStatus Cmd);
void LEDC_SetDeadTimeDuty(u32 LEDC_DeadTimeDuty);
void LEDC_SetPolarityMode(u32 LEDC_COMxPOL, u32 LEDC_SEGxPOL , LEDC_Mode mode);
#define  LEDC_SetData(COMx, data)   HT_LEDC->DR[COMx] = data
#define  LEDC_GetData(COMx)         HT_LEDC->DR[COMx]
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
