/**
 *******************************************************************************
 * @file  hc32_ll_emb.h
 * @brief This file contains all the functions prototypes of the EMB
 *        (Emergency Brake) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-06-30       CDT             Modify structure comments:stc_emb_monitor_tmr_pwm_t
   2023-09-30       CDT             Update EMB_CTL_CMPEN0~2 to EMB_CTL_CMPEN1~3
                                    Update EMB_INTEN_PORTINTEN to EMB_INTEN_PORTININTEN
                                    Update EMB_INTEN_PWMINTEN to EMB_INTEN_PWMSINTEN
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_EMB_H__
#define __HC32_LL_EMB_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_EMB
 * @{
 */

#if (LL_EMB_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EMB_Global_Types EMB Global Types
 * @{
 */

/**
 * @brief EMB monitor OSC failure configuration
 */
typedef struct {
    uint32_t u32OscState;           /*!< Enable or disable EMB detect OSC failure function
                                         This parameter can be a value of @ref EMB_OSC_Selection */
} stc_emb_monitor_osc_t;

/**
 * @brief EMB monitor EMB port configuration
 */
typedef struct {
    uint32_t u32PortState;          /*!< Enable or disable EMB detect port in control function
                                         This parameter can be a value of @ref EMB_Port_Selection */
    uint32_t u32PortLevel;          /*!< EMB detect port level
                                         This parameter can be a value of @ref EMB_Detect_Port_Level */
    uint32_t u32PortFilterDiv;      /*!< EMB port filter division
                                         This parameter can be a value of @ref EMB_Port_Filter_Clock_Division */
    uint32_t u32PortFilterState;    /*!< EMB port filter division
                                         This parameter can be a value of @ref EMB_Port_Filter_Selection */
} stc_emb_monitor_port_config_t;

/**
 * @brief EMB monitor PWM configuration
 */
typedef struct {
    uint32_t u32PwmState;   /*!< Enable or disable EMB detect timer same phase function
                                 This parameter can be a value of @ref EMB_Detect_PWM state. */
    uint32_t u32PwmLevel;   /*!< Detect timer polarity level
                                 This parameter can be a value of @ref EMB_Detect_PWM level */
} stc_emb_monitor_tmr_pwm_t;

/**
 * @brief EMB monitor port in configuration
 */
typedef struct {
    stc_emb_monitor_port_config_t stcPort1; /*!< EMB detect EMB port in function
                                                 This parameter details refer @ref stc_emb_monitor_port_config_t structure */
} stc_emb_monitor_port_t;

/**
 * @brief EMB monitor CMP configuration
 */
typedef struct {
    uint32_t u32Cmp1State;                  /*!< Enable or disable EMB detect CMP1 result function
                                                 This parameter can be a value of @ref EMB_CMP_Selection */
    uint32_t u32Cmp2State;                  /*!< Enable or disable EMB detect CMP2 result function
                                                 This parameter can be a value of @ref EMB_CMP_Selection */
    uint32_t u32Cmp3State;                  /*!< Enable or disable EMB detect CMP3 result function
                                                 This parameter can be a value of @ref EMB_CMP_Selection */
} stc_emb_monitor_cmp_t;

/**
 * @brief EMB monitor TMR4 configuration
 */
typedef struct {
    stc_emb_monitor_tmr_pwm_t stcTmr4PwmU;  /*!< EMB detect TMR4 function
                                                 This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */
    stc_emb_monitor_tmr_pwm_t stcTmr4PwmV;  /*!< EMB detect TMR4 function
                                                 This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */
    stc_emb_monitor_tmr_pwm_t stcTmr4PwmW;  /*!< EMB detect TMR4 function
                                                 This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */
} stc_emb_monitor_tmr4_t;

/**
 * @brief EMB monitor TMR6 configuration
 */
typedef struct {
    stc_emb_monitor_tmr_pwm_t stcTmr6_1;    /*!< EMB detect TMR6 function
                                                 This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */
    stc_emb_monitor_tmr_pwm_t stcTmr6_2;    /*!< EMB detect TMR6 function
                                                 This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */
    stc_emb_monitor_tmr_pwm_t stcTmr6_3;    /*!< EMB detect TMR6 function
                                                 This parameter details refer @ref stc_emb_monitor_tmr_pwm_t structure */
} stc_emb_monitor_tmr6_t;

/**
 * @brief EMB control TMR4 initialization configuration
 */
typedef struct {
    stc_emb_monitor_cmp_t   stcCmp;     /*!< EMB detect CMP function
                                             This parameter details refer @ref stc_emb_monitor_cmp_t structure */
    stc_emb_monitor_osc_t   stcOsc;     /*!< EMB detect OSC function
                                             This parameter details refer @ref stc_emb_monitor_osc_t structure */
    stc_emb_monitor_port_t  stcPort;    /*!< EMB detect EMB port function
                                             This parameter details refer @ref stc_emb_monitor_port_t structure */
    stc_emb_monitor_tmr4_t  stcTmr4;    /*!< EMB detect TMR4 function
                                             This parameter details refer @ref stc_emb_monitor_tmr4_t structure */
} stc_emb_tmr4_init_t;

/**
 * @brief EMB control TMR6 initialization configuration
 */
typedef struct {
    stc_emb_monitor_cmp_t   stcCmp;     /*!< EMB detect CMP function
                                             This parameter details refer @ref stc_emb_monitor_cmp_t structure */
    stc_emb_monitor_osc_t   stcOsc;     /*!< EMB detect OSC function
                                             This parameter details refer @ref stc_emb_monitor_osc_t structure */
    stc_emb_monitor_port_t  stcPort;    /*!< EMB detect EMB port function
                                             This parameter details refer @ref stc_emb_monitor_port_t structure */
    stc_emb_monitor_tmr6_t  stcTmr6;    /*!< EMB detect TMR6 function
                                             This parameter details refer @ref stc_emb_monitor_tmr6_t structure */
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
 * @defgroup EMB_CMP_Selection EMB CMP Selection
 * @{
 */
#define EMB_CMP1_DISABLE                    (0UL)
#define EMB_CMP2_DISABLE                    (0UL)
#define EMB_CMP3_DISABLE                    (0UL)

#define EMB_CMP1_ENABLE                     (EMB_CTL_CMPEN1)
#define EMB_CMP2_ENABLE                     (EMB_CTL_CMPEN2)
#define EMB_CMP3_ENABLE                     (EMB_CTL_CMPEN3)
/**
 * @}
 */

/**
 * @defgroup EMB_OSC_Selection EMB OSC Selection
 * @{
 */
#define EMB_OSC_DISABLE                     (0UL)
#define EMB_OSC_ENABLE                      (EMB_CTL_OSCSTPEN)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_PWM EMB Detect PWM
 * @{
 */
/**
 * @defgroup EMB_TMR4_PWM_Selection EMB TMR4 PWM Selection
 * @{
 */
#define EMB_TMR4_PWM_W_DISABLE              (0UL)
#define EMB_TMR4_PWM_V_DISABLE              (0UL)
#define EMB_TMR4_PWM_U_DISABLE              (0UL)

#define EMB_TMR4_PWM_W_ENABLE               (EMB_CTL_PWMSEN0)
#define EMB_TMR4_PWM_V_ENABLE               (EMB_CTL_PWMSEN1)
#define EMB_TMR4_PWM_U_ENABLE               (EMB_CTL_PWMSEN2)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR4_PWM_Level EMB Detect TMR4 PWM Level
 * @{
 */
#define EMB_DETECT_TMR4_PWM_W_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR4_PWM_V_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR4_PWM_U_BOTH_LOW      (0UL)

#define EMB_DETECT_TMR4_PWM_W_BOTH_HIGH     (EMB_PWMLV_PWMLV0)
#define EMB_DETECT_TMR4_PWM_V_BOTH_HIGH     (EMB_PWMLV_PWMLV1)
#define EMB_DETECT_TMR4_PWM_U_BOTH_HIGH     (EMB_PWMLV_PWMLV2)
/**
 * @}
 */

/**
 * @defgroup EMB_TMR6_PWM_Selection EMB TMR6 PWM Selection
 * @{
 */
#define EMB_TMR6_1_PWM_DISABLE              (0UL)
#define EMB_TMR6_2_PWM_DISABLE              (0UL)
#define EMB_TMR6_3_PWM_DISABLE              (0UL)

#define EMB_TMR6_1_PWM_ENABLE               (EMB_CTL_PWMSEN0)
#define EMB_TMR6_2_PWM_ENABLE               (EMB_CTL_PWMSEN1)
#define EMB_TMR6_3_PWM_ENABLE               (EMB_CTL_PWMSEN2)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_TMR6_PWM_Level EMB Detect TMR6 PWM Level
 * @{
 */
#define EMB_DETECT_TMR6_1_PWM_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR6_2_PWM_BOTH_LOW      (0UL)
#define EMB_DETECT_TMR6_3_PWM_BOTH_LOW      (0UL)

#define EMB_DETECT_TMR6_1_PWM_BOTH_HIGH     (EMB_PWMLV_PWMLV0)
#define EMB_DETECT_TMR6_2_PWM_BOTH_HIGH     (EMB_PWMLV_PWMLV1)
#define EMB_DETECT_TMR6_3_PWM_BOTH_HIGH     (EMB_PWMLV_PWMLV2)
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup EMB_Port_Selection EMB Port Selection
 * @{
 */
#define EMB_PORT1_DISABLE                   (0UL)

#define EMB_PORT1_ENABLE                    (EMB_CTL_PORTINEN)
/**
 * @}
 */

/**
 * @defgroup EMB_Detect_Port_Level EMB Detect Port Level
 * @{
 */
#define EMB_PORT1_DETECT_LVL_HIGH           (0UL)

#define EMB_PORT1_DETECT_LVL_LOW            (EMB_CTL_INVSEL)
/**
 * @}
 */

/**
 * @defgroup EMB_Port_Filter_Selection EMB Port Filter Selection
 * @{
 */
#define EMB_PORT1_FILTER_DISABLE            (0UL)

#define EMB_PORT1_FILTER_ENABLE             (EMB_CTL_NFEN)
/**
 * @}
 */

/**
 * @defgroup EMB_Port_Filter_Clock_Division EMB Port Filter Clock Division
 * @{
 */
#define EMB_PORT1_FILTER_CLK_DIV1           (0UL << EMB_CTL_NFSEL_POS)
#define EMB_PORT1_FILTER_CLK_DIV8           (1UL << EMB_CTL_NFSEL_POS)
#define EMB_PORT1_FILTER_CLK_DIV32          (2UL << EMB_CTL_NFSEL_POS)
#define EMB_PORT1_FILTER_CLK_DIV128         (3UL << EMB_CTL_NFSEL_POS)
/**
 * @}
 */

/**
 * @defgroup EMB_Flag_State EMB Flag State
 * @{
 */
#define EMB_FLAG_PWMS                       (EMB_STAT_PWMSF)
#define EMB_FLAG_CMP                        (EMB_STAT_CMPF)
#define EMB_FLAG_OSC                        (EMB_STAT_OSF)
#define EMB_FLAG_PORT1                      (EMB_STAT_PORTINF)
#define EMB_STAT_PWMS                       (EMB_STAT_PWMST)
#define EMB_STAT_PORT1                      (EMB_STAT_PORTINST)
#define EMB_FLAG_ALL                        (EMB_FLAG_PWMS | EMB_FLAG_CMP | EMB_FLAG_OSC | EMB_FLAG_PORT1 | \
                                             EMB_STAT_PWMS | EMB_STAT_PORT1)
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
#define EMB_INT_PORT1                       (EMB_INTEN_PORTININTEN)
#define EMB_INT_ALL                         (EMB_INT_PWMS | EMB_INT_CMP | EMB_INT_OSC | EMB_INT_PORT1)
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
int32_t EMB_TMR4_StructInit(stc_emb_tmr4_init_t *pstcEmbInit);
int32_t EMB_TMR4_Init(CM_EMB_TypeDef *EMBx, const stc_emb_tmr4_init_t *pstcEmbInit);

int32_t EMB_TMR6_StructInit(stc_emb_tmr6_init_t *pstcEmbInit);
int32_t EMB_TMR6_Init(CM_EMB_TypeDef *EMBx, const stc_emb_tmr6_init_t *pstcEmbInit);

void EMB_DeInit(CM_EMB_TypeDef *EMBx);
void EMB_IntCmd(CM_EMB_TypeDef *EMBx, uint32_t u32IntType, en_functional_state_t enNewState);
void EMB_ClearStatus(CM_EMB_TypeDef *EMBx, uint32_t u32Flag);
en_flag_status_t EMB_GetStatus(const CM_EMB_TypeDef *EMBx, uint32_t u32Flag);
void EMB_SWBrake(CM_EMB_TypeDef *EMBx, en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* LL_EMB_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_EMB_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
