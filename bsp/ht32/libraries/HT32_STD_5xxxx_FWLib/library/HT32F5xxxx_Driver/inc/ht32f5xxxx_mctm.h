/*********************************************************************************************************//**
 * @file    ht32f5xxxx_mctm.h
 * @version $Rev:: 8260         $
 * @date    $Date:: 2024-11-05 #$
 * @brief   The header file of the MCTM library.
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
#ifndef __HT32F5XXXX_MCTM_H
#define __HT32F5XXXX_MCTM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f5xxxx_tm.h"
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup MCTM
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup MCTM_Exported_Types MCTM exported types
  * @{
  */
/**
 * @brief Enumeration of MCTM channel output idle state.
 */
/**
 * @brief Definition of Break & DeadTime init structure.
 */
typedef struct
{
  u32 OSSRState;
  u32 OSSIState;
  u32 LockLevel;
  u32 Break0;
  u32 Break0Polarity;
  u32 AutomaticOutput;
  u8 DeadTime;
  u8 BreakFilter;
} MCTM_CHBRKCTRInitTypeDef;

typedef union
{
  struct
  {
    /* Definitions of CHBRKCTR                                                                              */
    unsigned long Break0           :1; // BK0E
    unsigned long Break0Polarity   :1; // BK0P
    #if (LIBCFG_TM_65X_66X_V1)
    unsigned long Break1           :1; // BK1E
    unsigned long Break1Polarity   :1; // BK1E
    #else
    unsigned long                  :1;
    unsigned long                  :1;
    #endif
    unsigned long                  :1; // CHMOE
    unsigned long AutomaticOutput  :1; // CHAOE
    #if (LIBCFG_TM_BK_FROM_CMP)
    unsigned long Break0FromCMP0   :1; // BK0CMP0
    unsigned long Break0FromCMP1   :1; // BK0CMP1
    #else
    unsigned long                  :1;
    unsigned long                  :1;
    #endif

    #if (LIBCFG_TM_65X_66X_V1)
    unsigned long Break0EventCount :2; // BK0FN
    unsigned long Break0FDiv       :2; // BK0FF
    unsigned long Break1EventCount :2; // BK1FN
    unsigned long Break1FDiv       :2; // BK1FF
    #else
    unsigned long Break0Filter     :4; // BK0F
    unsigned long                  :4;
    #endif

    unsigned long LockLevel        :2; // LOCKLV
    unsigned long DeglitchFilter   :1; // GFSEL
    unsigned long                  :1;
    unsigned long OSSIState        :1; // CHOSSI
    unsigned long OSSRState        :1; // CHOSSR
    #if (LIBCFG_TM_BK_FROM_CMP)
    unsigned long Break1FromCMP0   :1; // BK1CMP0
    unsigned long Break1FromCMP1   :1; // BK1CMP1
    #else
    unsigned long                  :1;
    unsigned long                  :1;
    #endif

    unsigned long DeadTime         :8; // CHDTG
  } Bit;
  u32 Reg;
} MCTM_CHBRKCTRTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup MCTM_Exported_Constants MCTM exported constants
  * @{
  */

/** @defgroup MCTM_BKE Definitions of MCTM break control
  * @{
  */
#define MCTM_BREAK_ENABLE           0x00000001 /*!< Break enable                                            */
#define MCTM_BREAK_DISABLE          0x00000000 /*!< Break disable                                           */
/**
  * @}
  */

/** @defgroup MCTM_BKP Definitions of MCTM break polarity
  * @{
  */
#define MCTM_BREAK_POLARITY_LOW     0x00000000 /*!< Break input pin active low level                        */
#define MCTM_BREAK_POLARITY_HIGH    0x00000002 /*!< Break input pin active high level                       */
/**
  * @}
  */

/** @defgroup MCTM_CHMOE Definitions of MCTM main output enable function state
  * @{
  */
#define MCTM_CHMOE_DISABLE          0x00000000 /*!< main output disable                                     */
#define MCTM_CHMOE_ENABLE           0x00000010 /*!< Main output enable                                      */
/**
  * @}
  */

/** @defgroup MCTM_CHAOE Definitions of MCTM automatic output enable function state
  * @{
  */
#define MCTM_CHAOE_DISABLE          0x00000000 /*!< Automatic output enable function disable                */
#define MCTM_CHAOE_ENABLE           0x00000020 /*!< Automatic output enable function enable                 */
/**
  * @}
  */

/** @defgroup MCTM_LOCK_LEVEL Definitions of MCTM lock level selection
  * @{
  */
#define MCTM_LOCK_LEVEL_OFF                 0x00000000 /*!< Lock Off                                        */
#define MCTM_LOCK_LEVEL_1                   0x00010000 /*!< Lock level 1                                    */
#define MCTM_LOCK_LEVEL_2                   0x00020000 /*!< Lock level 2                                    */
#define MCTM_LOCK_LEVEL_3                   0x00030000 /*!< Lock level 3                                    */
/**
  * @}
  */

/** @defgroup MCTM_OSSI Definitions of Off-State Selection for Idle mode states
  * @{
  */
#define MCTM_OSSI_STATE_ENABLE              0x00100000
#define MCTM_OSSI_STATE_DISABLE             0x00000000
/**
  * @}
  */

/** @defgroup MCTM_OSSR Definitions of Off-State Selection for Run mode states
  * @{
  */
#define MCTM_OSSR_STATE_ENABLE              0x00200000
#define MCTM_OSSR_STATE_DISABLE             0x00000000
/**
  * @}
  */

/** @defgroup MCTM_Check_Parameter Check parameter
  * @{
  */

/**
 * @brief Used to check parameter of the MCTMx.
 */
#define IS_MCTM(x)          (IS_MCTM0(x))

#if (LIBCFG_MCTM0)
#define IS_MCTM0(x)         (x == HT_MCTM0)
#else
#define IS_MCTM0(x)         (0)
#endif

/**
 * @brief Used to check parameter of the complementary output channel.
 */
#define IS_MCTM_COMPLEMENTARY_CH(x) (((x) == TM_CH_0) || ((x) == TM_CH_1) || \
                                     ((x) == TM_CH_2))
/**
 * @brief Used to check parameter of the COMUS.
 */
#define IS_MCTM_COMUS(x)  ((x == MCTM_COMUS_STIOFF) || (x == MCTM_COMUS_STION))
/**
 * @brief Used to check parameter of the channel output idle state.
 */
#define IS_MCTM_OIS(x)  ((x == MCTM_OIS_LOW) || (x == MCTM_OIS_HIGH))
/**
 * @brief Used to check value of MCTM break control state.
 */
#define IS_MCTM_BREAK_STATE(STATE)  (((STATE) == MCTM_BREAK_ENABLE) || \
                                     ((STATE) == MCTM_BREAK_DISABLE))
/**
 * @brief Used to check value of MCTM break polarity.
 */
#define IS_MCTM_BREAK_POLARITY(POLARITY)    (((POLARITY) == MCTM_BREAK_POLARITY_LOW) || \
                                             ((POLARITY) == MCTM_BREAK_POLARITY_HIGH))
/**
 * @brief Used to check value of MCTM automatic output enable control state.
 */
#define IS_MCTM_CHAOE_STATE(STATE)  (((STATE) == MCTM_CHAOE_ENABLE) || \
                                     ((STATE) == MCTM_CHAOE_DISABLE))
/**
 * @brief Used to check value of MCTM lock level.
 */
#define IS_MCTM_LOCK_LEVEL(LEVEL)   (((LEVEL) == MCTM_LOCK_LEVEL_OFF) || \
                                     ((LEVEL) == MCTM_LOCK_LEVEL_1) || \
                                     ((LEVEL) == MCTM_LOCK_LEVEL_2) || \
                                     ((LEVEL) == MCTM_LOCK_LEVEL_3))
/**
 * @brief Used to check value of MCTM OSSI state.
 */
#define IS_MCTM_OSSI_STATE(STATE)   (((STATE) == MCTM_OSSI_STATE_ENABLE) || \
                                     ((STATE) == MCTM_OSSI_STATE_DISABLE))
/**
 * @brief Used to check value of MCTM OSSR state.
 */
#define IS_MCTM_OSSR_STATE(STATE)   (((STATE) == MCTM_OSSR_STATE_ENABLE) || \
                                     ((STATE) == MCTM_OSSR_STATE_DISABLE))
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup MCTM_Exported_Functions MCTM exported functions
  * @{
  */
void MCTM_ChNPolarityConfig(HT_TM_TypeDef* MCTMx, TM_CH_Enum Channel, TM_CHP_Enum Pol);
void MCTM_ChannelNConfig(HT_TM_TypeDef* MCTMx, TM_CH_Enum Channel, TM_CHCTL_Enum Control);

void MCTM_CHMOECmd(HT_TM_TypeDef* MCTMx, ControlStatus NewState);
void MCTM_CHBRKCTRConfig(HT_TM_TypeDef* MCTMx, MCTM_CHBRKCTRInitTypeDef *CHBRKCTRInit);
void MCTM_CHBRKCTRConfig2(HT_TM_TypeDef* MCTMx, MCTM_CHBRKCTRTypeDef *CHBRKCTRInit);
void MCTM_CHBRKCTRStructInit(MCTM_CHBRKCTRInitTypeDef* CHBRKCTRInit);
void MCTM_COMPRECmd(HT_TM_TypeDef* MCTMx, ControlStatus NewState);
void MCTM_COMUSConfig(HT_TM_TypeDef* MCTMx, MCTM_COMUS_Enum Sel);

#if (LIBCFG_MCTM_UEV1DIS)
void MCTM_UpdateEventDisable(HT_TM_TypeDef* MCTMx, MCTM_UEV1DIS_Enum MCTM_UEV1x, FlagStatus NewState);
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
