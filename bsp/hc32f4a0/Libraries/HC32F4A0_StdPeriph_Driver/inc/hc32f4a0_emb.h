/**
 *******************************************************************************
 * @file  hc32f4a0_emb.h
 * @brief This file contains all the functions prototypes of the EMB
 *        (Emergency Brake) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Hongjh          First version
   2020-07-07       Hongjh          1. Modify structure member comments for 
                                       stc_emb_monitor_port_t/stc_emb_monitor_tmr_pwm_t
                                    2. Replace the word Timer with TMR abbreviation
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_EMB_H__
#define __HC32F4A0_EMB_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_EMB
 * @{
 */

#if (DDL_EMB_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EMB_Global_Types EMB Global Types
 * @{
 */

/**
 * @brief EMB monitor EMB port configuration
 */
typedef struct
{
    uint32_t    u32PortSel;         /*!< Enable or disable EMB detect port in control function
                                         This parameter can be a value of EMB_Portx_Selection(x=1~4) */

    uint32_t    u32PortLevel;       /*!< EMB detect port level
                                         This parameter can be a value of EMB_Detect_Portx_Level(x=1~4) */

    uint32_t    u32PortFilterDiv;   /*!< EMB port filter division
                                         This parameter can be a value of EMB_Portx_Filter_Clock_Division(x=1~4) */
} stc_emb_monitor_port_t;

/**
 * @brief EMB monitor TMR4 or TMR6 PWM configuration
 */
typedef struct
{
    uint32_t    u32PwmSel;      /*!< Enable or disable EMB detect TMR4/6 PWM x channel same phase function
                                     This parameter can be a value of EMB_TMR4_PWM_x_Selection(x=U/V/W) or
                                     EMB_TMR6_x_PWM_Selection(x=1~8) */

    uint32_t    u32PwmLevel;    /*!< Detect TMR4/6 PWM x channel polarity level
                                     This parameter can be a value of EMB_Detect_TMR4_PWM_x_Level(x=U/V/W) or 
                                     EMB_Detect_TMR6_x_PWM_Level(x=1~8) */
} stc_emb_monitor_tmr_pwm_t;

/**
 * @brief EMB control TMR4 initialization configuration
 */
typedef struct
{
    uint32_t    u32Cmp1;                        /*!< Enable or disable EMB detect CMP1 result function
                                                     This parameter can be a value of @ref EMB_CMP1_Selection */

    uint32_t    u32Cmp2;                        /*!< Enable or disable EMB detect CMP2 result function
                                                     This parameter can be a value of @ref EMB_CMP2_Selection */

    uint32_t    u32Cmp3;                        /*!< Enable or disable EMB detect CMP3 result function
                                                     This parameter can be a value of @ref EMB_CMP3_Selection */

    uint32_t    u32Cmp4;                        /*!< Enable or disable EMB detect CMP4 result function
                                                     This parameter can be a value of @ref EMB_CMP4_Selection */

    uint32_t    u32Osc;                         /*!< EMB detect OSC failure function
                                                     This parameter can be a value of @ref EMB_OSC_Stop_Selection */

    stc_emb_monitor_port_t      stcPort1;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_port_t      stcPort2;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_port_t      stcPort3;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_port_t      stcPort4;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_tmr_pwm_t   stcTmr4PwmU;    /*!< EMB detect TMR4 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */

    stc_emb_monitor_tmr_pwm_t   stcTmr4PwmV;    /*!< EMB detect TMR4 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */

    stc_emb_monitor_tmr_pwm_t   stcTmr4PwmW;    /*!< EMB detect TMR4 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */
} stc_emb_tmr4_init_t;

/**
 * @brief EMB control TMR6 initialization configuration
 */
typedef struct
{
    uint32_t    u32Cmp1;                        /*!< Enable or disable EMB detect CMP1 result function
                                                     This parameter can be a value of @ref EMB_CMP1_Selection */

    uint32_t    u32Cmp2;                        /*!< Enable or disable EMB detect CMP2 result function
                                                     This parameter can be a value of @ref EMB_CMP2_Selection */

    uint32_t    u32Cmp3;                        /*!< Enable or disable EMB detect CMP3 result function
                                                     This parameter can be a value of @ref EMB_CMP3_Selection */

    uint32_t    u32Cmp4;                        /*!< Enable or disable EMB detect CMP4 result function
                                                     This parameter can be a value of @ref EMB_CMP4_Selection */

    uint32_t    u32Osc;                         /*!< EMB detect OSC failure function
                                                     This parameter can be a value of @ref EMB_OSC_Stop_Selection */

    stc_emb_monitor_port_t      stcPort1;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_port_t      stcPort2;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_port_t      stcPort3;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_port_t      stcPort4;       /*!< EMB detect port EMBIN1 function
                                                     This parameter details refer @ref stc_emb_monitor_port_t structure */

    stc_emb_monitor_tmr_pwm_t   stcTmr6_1;      /*!< EMB detect TMR6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */

    stc_emb_monitor_tmr_pwm_t   stcTmr6_2;      /*!< EMB detect TMR6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */

    stc_emb_monitor_tmr_pwm_t   stcTmr6_3;      /*!< EMB detect TMR6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */

    stc_emb_monitor_tmr_pwm_t   stcTmr6_4;      /*!< EMB detect TMR6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */

    stc_emb_monitor_tmr_pwm_t   stcTmr6_5;      /*!< EMB detect TMR6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */

    stc_emb_monitor_tmr_pwm_t   stcTmr6_6;      /*!< EMB detect TMR6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */

    stc_emb_monitor_tmr_pwm_t   stcTmr6_7;      /*!< EMB detect TMR6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */

    stc_emb_monitor_tmr_pwm_t   stcTmr6_8;      /*!< EMB detect TMR6 function
                                                     This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */
} stc_emb_tmr6_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EMB_Global_Macros EMB Global Macros
 * @{
 */

/**
 * @defgroup EMB_CMP1_Selection EMB CMP1 Selection
 * @{
 */
#define EMB_CMP1_DISABLE                    (0UL)
#define EMB_CMP1_ENABLE                     (EMB_CTL1_CMPEN_0)
/**
 * @}
 */

/**
 * @defgroup EMB_CMP2_Selection EMB CMP2 Selection
 * @{
 */
#define EMB_CMP2_DISABLE                    (0UL)
#define EMB_CMP2_ENABLE                     (EMB_CTL1_CMPEN_1)
/**
 * @}
 */

/**
 * @defgroup EMB_CMP3_Selection EMB CMP3 Selection
 * @{
 */
#define EMB_CMP3_DISABLE                    (0UL)
#define EMB_CMP3_ENABLE                     (EMB_CTL1_CMPEN_2)
/**
 * @}
 */

/**
 * @defgroup EMB_CMP4_Selection EMB CMP4 Selection
 * @{
 */
#define EMB_CMP4_DISABLE                    (0UL)
#define EMB_CMP4_ENABLE                     (EMB_CTL1_CMPEN_3)
/**
 * @}
 */

/**
 * @defgroup EMB_OSC_Stop_Selection EMB OSC Stop Selection
 * @{
 */
#define EMB_OSC_DISABLE                     (0UL)
#define EMB_OSC_ENABLE                      (EMB_CTL1_OSCSTPEN)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR4_PWM_W_Selection EMB TMR4 PWM W Selection
 * @{
 */
#define EMB_TMR4_PWM_W_DISABLE              (0UL)
#define EMB_TMR4_PWM_W_ENABLE               (EMB_CTL1_PWMSEN_0)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR4_PWM_V_Selection EMB TMR4 PWM V Selection
 * @{
 */
#define EMB_TMR4_PWM_V_DISABLE              (0UL)
#define EMB_TMR4_PWM_V_ENABLE               (EMB_CTL1_PWMSEN_1)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR4_PWM_U_Selection EMB TMR4 PWM U Selection
 * @{
 */
#define EMB_TMR4_PWM_U_DISABLE              (0UL)
#define EMB_TMR4_PWM_U_ENABLE               (EMB_CTL1_PWMSEN_2)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR6_1_PWM_Selection EMB TMR6_1 PWM Selection
 * @{
 */
#define EMB_TMR6_1_PWM_DISABLE              (0UL)
#define EMB_TMR6_1_PWM_ENABLE               (EMB_CTL1_PWMSEN_0)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR6_2_PWM_Selection EMB TMR6_2 PWM Selection
 * @{
 */
#define EMB_TMR6_2_PWM_DISABLE              (0UL)
#define EMB_TMR6_2_PWM_ENABLE               (EMB_CTL1_PWMSEN_1)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR6_3_PWM_Selection EMB TMR6_3 PWM Selection
 * @{
 */
#define EMB_TMR6_3_PWM_DISABLE              (0UL)
#define EMB_TMR6_3_PWM_ENABLE               (EMB_CTL1_PWMSEN_2)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR6_4_PWM_Selection EMB TMR6_4 PWM Selection
 * @{
 */
#define EMB_TMR6_4_PWM_DISABLE              (0UL)
#define EMB_TMR6_4_PWM_ENABLE               (EMB_CTL1_PWMSEN_3)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR6_5_PWM_Selection EMB TMR6_5 PWM Selection
 * @{
 */
#define EMB_TMR6_5_PWM_DISABLE              (0UL)
#define EMB_TMR6_5_PWM_ENABLE               (EMB_CTL1_PWMSEN_4)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR6_6_PWM_Selection EMB TMR6_6 PWM Selection
 * @{
 */
#define EMB_TMR6_6_PWM_DISABLE              (0UL)
#define EMB_TMR6_6_PWM_ENABLE               (EMB_CTL1_PWMSEN_5)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR6_7_PWM_Selection EMB TMR6_7 PWM Selection
 * @{
 */
#define EMB_TMR6_7_PWM_DISABLE              (0UL)
#define EMB_TMR6_7_PWM_ENABLE               (EMB_CTL1_PWMSEN_6)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR6_8_PWM_Selection EMB TMR6_8 PWM Selection
 * @{
 */
#define EMB_TMR6_8_PWM_DISABLE              (0UL)
#define EMB_TMR6_8_PWM_ENABLE               (EMB_CTL1_PWMSEN_7)
/**
 * @}
 */

/**
 * @defgroup EMB_Port1_Selection EMB Port1 Selection
 * @{
 */
#define EMB_PORT1_ENABLE                    (EMB_CTL1_PORTINEN1)
#define EMB_PORT1_DISABLE                   (0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Port2_Selection EMB Port2 Selection
 * @{
 */
#define EMB_PORT2_ENABLE                    (EMB_CTL1_PORTINEN2)
#define EMB_PORT2_DISABLE                   (0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Port3_Selection EMB Port3 Selection
 * @{
 */
#define EMB_PORT3_ENABLE                    (EMB_CTL1_PORTINEN3)
#define EMB_PORT3_DISABLE                   (0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Port4_Selection EMB Port4 Selection
 * @{
 */
#define EMB_PORT4_ENABLE                    (EMB_CTL1_PORTINEN2)
#define EMB_PORT4_DISABLE                   (0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Port1_Level EMB Detect Port1 Level
 * @{
 */
#define EMB_DETECT_PORT1_LEVEL_HIGH         (0UL)
#define EMB_DETECT_PORT1_LEVEL_LOW          (EMB_CTL1_INVSEL1)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Port2_Level EMB Detect Port2 Level
 * @{
 */
#define EMB_DETECT_PORT2_LEVEL_HIGH         (0UL)
#define EMB_DETECT_PORT2_LEVEL_LOW          (EMB_CTL1_INVSEL2)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Port3_Level EMB Detect Port3 Level
 * @{
 */
#define EMB_DETECT_PORT3_LEVEL_HIGH         (0UL)
#define EMB_DETECT_PORT3_LEVEL_LOW          (EMB_CTL1_INVSEL3)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Port4_Level EMB Detect Port4 Level
 * @{
 */
#define EMB_DETECT_PORT4_LEVEL_HIGH         (0UL)
#define EMB_DETECT_PORT4_LEVEL_LOW          (EMB_CTL1_INVSEL4)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR4_PWM_W_Level EMB Detect TMR4 PWM W Level
 * @{
 */
#define EMB_DETECT_TMR4_PWM_W_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR4_PWM_W_BOTH_HIGH     (EMB_CTL2_PWMLV_0)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR4_PWM_V_Level EMB Detect TMR4 PWM V Level
 * @{
 */
#define EMB_DETECT_TMR4_PWM_V_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR4_PWM_V_BOTH_HIGH     (EMB_CTL2_PWMLV_1)
/**
 * @}
 */
/**
 * @defgroup EMB_Detect_TMR4_PWM_U_Level EMB Detect TMR4 PWM U Level
 * @{
 */
#define EMB_DETECT_TMR4_PWM_U_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR4_PWM_U_BOTH_HIGH     (EMB_CTL2_PWMLV_2)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR6_1_PWM_Level EMB Detect TMR6_1 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_1_PWM_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR6_1_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_0)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR6_2_PWM_Level EMB Detect TMR6_2 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_2_PWM_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR6_2_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_1)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR6_3_PWM_Level EMB Detect TMR6_3 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_3_PWM_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR6_3_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_2)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR6_4_PWM_Level EMB Detect TMR6_4 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_4_PWM_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR6_4_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_3)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR6_5_PWM_Level EMB Detect TMR6_5 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_5_PWM_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR6_5_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_4)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR6_6_PWM_Level EMB Detect TMR6_6 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_6_PWM_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR6_6_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_5)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR6_7_PWM_Level EMB Detect TMR6_7 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_7_PWM_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR6_7_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_6)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR6_8_PWM_Level EMB Detect TMR6_8 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_8_PWM_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR6_8_PWM_BOTH_HIGH     (EMB_CTL2_PWMLV_7)
/**
 * @}
 */

/** @defgroup EMB_Port1_Filter_Clock_Division EMB Port1 Filter Clock Division
 * @{
 */
#define EMB_PORT1_FILTER_NONE               (0UL)
#define EMB_PORT1_FILTER_CLK_DIV1           (EMB_CTL2_NFEN1)
#define EMB_PORT1_FILTER_CLK_DIV8           (EMB_CTL2_NFEN1 | EMB_CTL2_NFSEL1_0)
#define EMB_PORT1_FILTER_CLK_DIV32          (EMB_CTL2_NFEN1 | EMB_CTL2_NFSEL1_1)
#define EMB_PORT1_FILTER_CLK_DIV128         (EMB_CTL2_NFEN1 | EMB_CTL2_NFSEL1)
/**
 * @}
 */

/** @defgroup EMB_Port2_Filter_Clock_Division EMB Port2 Filter Clock Division
 * @{
 */
#define EMB_PORT2_FILTER_NONE               (0UL)
#define EMB_PORT2_FILTER_CLK_DIV1           (EMB_CTL2_NFEN2)
#define EMB_PORT2_FILTER_CLK_DIV8           (EMB_CTL2_NFEN2 | EMB_CTL2_NFSEL2_0)
#define EMB_PORT2_FILTER_CLK_DIV32          (EMB_CTL2_NFEN2 | EMB_CTL2_NFSEL2_1)
#define EMB_PORT2_FILTER_CLK_DIV128         (EMB_CTL2_NFEN2 | EMB_CTL2_NFSEL2)
/**
 * @}
 */

/** @defgroup EMB_Port3_Filter_Clock_Division EMB Port3 Filter Clock Division
 * @{
 */
#define EMB_PORT3_FILTER_NONE               (0UL)
#define EMB_PORT3_FILTER_CLK_DIV1           (EMB_CTL2_NFEN3)
#define EMB_PORT3_FILTER_CLK_DIV8           (EMB_CTL2_NFEN3 | EMB_CTL2_NFSEL3_0)
#define EMB_PORT3_FILTER_CLK_DIV32          (EMB_CTL2_NFEN3 | EMB_CTL2_NFSEL3_1)
#define EMB_PORT3_FILTER_CLK_DIV128         (EMB_CTL2_NFEN3 | EMB_CTL2_NFSEL3)
/**
 * @}
 */

/** @defgroup EMB_Port4_Filter_Clock_Division EMB Port4 Filter Clock Division
 * @{
 */
#define EMB_PORT4_FILTER_NONE               (0UL)
#define EMB_PORT4_FILTER_CLK_DIV1           (EMB_CTL2_NFEN4)
#define EMB_PORT4_FILTER_CLK_DIV8           (EMB_CTL2_NFEN4 | EMB_CTL2_NFSEL4_0)
#define EMB_PORT4_FILTER_CLK_DIV32          (EMB_CTL2_NFEN4 | EMB_CTL2_NFSEL4_1)
#define EMB_PORT4_FILTER_CLK_DIV128         (EMB_CTL2_NFEN4 | EMB_CTL2_NFSEL4)
/**
 * @}
 */

/**
 * @defgroup EMB_Flag EMB Flag
 * @{
 */
#define EMB_FLAG_PWMS                       (EMB_STAT_PWMSF)
#define EMB_FLAG_CMP                        (EMB_STAT_CMPF)
#define EMB_FLAG_OSC                        (EMB_STAT_OSF)
#define EMB_FLAG_PORT1                      (EMB_STAT_PORTINF1)
#define EMB_FLAG_PORT2                      (EMB_STAT_PORTINF2)
#define EMB_FLAG_PORT3                      (EMB_STAT_PORTINF3)
#define EMB_FLAG_PORT4                      (EMB_STAT_PORTINF4)
/**
 * @}
 */

/**
 * @defgroup EMB_State EMB State
 * @{
 */
#define EMB_STATE_PWMS                      (EMB_STAT_PWMST)
#define EMB_STATE_CMP                       (EMB_STAT_CMPST)
#define EMB_STATE_OSC                       (EMB_STAT_OSST)
#define EMB_STATE_PORT1                     (EMB_STAT_PORTINST1)
#define EMB_STATE_PORT2                     (EMB_STAT_PORTINST2)
#define EMB_STATE_PORT3                     (EMB_STAT_PORTINST3)
#define EMB_STATE_PORT4                     (EMB_STAT_PORTINST4)
/**
 * @}
 */

/**
 * @defgroup EMB_Interrupt EMB Interrupt
 * @{
 */
#define EMB_INT_PWMS                        (EMB_INTEN_PWMSINTEN)
#define EMB_INT_CMP                         (EMB_INTEN_CMPINTEN)
#define EMB_INT_OSC                         (EMB_INTEN_OSINTEN)
#define EMB_INT_PORT1                       (EMB_INTEN_PORTINTEN1)
#define EMB_INT_PORT2                       (EMB_INTEN_PORTINTEN2)
#define EMB_INT_PORT3                       (EMB_INTEN_PORTINTEN3)
#define EMB_INT_PORT4                       (EMB_INTEN_PORTINTEN4)
/**
 * @}
 */

/**
 * @defgroup EMB_Release_TMR_PWM_Selection EMB Release TMR PWM Selection
 * @{
 */
#define EMB_RELEASE_PWM_SEL_FLAG_ZERO       (0UL)
#define EMB_RELEASE_PWM_SEL_STATE_ZERO      (1UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Monitor_Event EMB Monitor Event
 * @{
 */
#define EMB_EVENT_PWMS                      (EMB_RLSSEL_PWMRSEL)
#define EMB_EVENT_CMP                       (EMB_RLSSEL_CMPRSEL)
#define EMB_EVENT_OSC                       (EMB_RLSSEL_OSRSEL)
#define EMB_EVENT_PORT1                     (EMB_RLSSEL_PORTINRSEL1)
#define EMB_EVENT_PORT2                     (EMB_RLSSEL_PORTINRSEL2)
#define EMB_EVENT_PORT3                     (EMB_RLSSEL_PORTINRSEL3)
#define EMB_EVENT_PORT4                     (EMB_RLSSEL_PORTINRSEL4)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup EMB_Global_Functions
 * @{
 */
en_result_t EMB_Tmr4Init(M4_EMB_TypeDef *EMBx,
                            const stc_emb_tmr4_init_t *pstcInit);
en_result_t EMB_Tmr4StructInit(stc_emb_tmr4_init_t *pstcInit);
en_result_t EMB_Tmr6Init(M4_EMB_TypeDef *EMBx,
                            const stc_emb_tmr6_init_t *pstcInit);
en_result_t EMB_Tmr6StructInit(stc_emb_tmr6_init_t *pstcInit);
void EMB_DeInit(M4_EMB_TypeDef *EMBx);
void EMB_IntCmd(M4_EMB_TypeDef *EMBx,
                    uint32_t u32IntSource,
                    en_functional_state_t enNewState);
void EMB_SetReleasePwmMode(M4_EMB_TypeDef *EMBx,
                                uint32_t u32Event,
                                uint32_t u32Mode);
en_flag_status_t EMB_GetFlag(const M4_EMB_TypeDef *EMBx, uint32_t u32Flag);
void EMB_ClearFlag(M4_EMB_TypeDef *EMBx, uint32_t u32Flag);
en_flag_status_t EMB_GetStatus(const M4_EMB_TypeDef *EMBx,
                                    uint32_t u32Status);
void EMB_SwBrake(M4_EMB_TypeDef *EMBx, en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* DDL_EMB_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_EMB_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
