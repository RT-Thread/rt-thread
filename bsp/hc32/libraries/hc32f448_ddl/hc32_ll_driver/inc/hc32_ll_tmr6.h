/**
 *******************************************************************************
 * @file  hc32_ll_tmr6.h
 * @brief This file contains all the functions prototypes of the TMR6 driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
   2023-09-30       CDT             Modify macro define for group TMR6_Emb_Ch_Define
   2023-12-15       CDT             Modify for headfile update: CM_TMR6CR -> CM_TMR6_COMMON
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
#ifndef __HC32_LL_TMR6_H__
#define __HC32_LL_TMR6_H__

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
 * @addtogroup LL_TMR6
 * @{
 */

#if (LL_TMR6_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMR6_Global_Types TMR6 Global Types
 * @{
 */

/**
 * @brief Timer6 count function structure definition
 */
typedef struct {
    uint8_t u8CountSrc;             /*!< Specifies the count source @ref TMR6_Count_Src_Define */
    struct {
        uint32_t u32ClockDiv;   /*!< Count clock division select, @ref TMR6_Count_Clock_Define */
        uint32_t u32CountMode;  /*!< Count mode, @ref TMR6_Count_Mode_Define */
        uint32_t u32CountDir;   /*!< Count direction, @ref TMR6_Count_Dir_Define */
    } sw_count;
    struct {
        uint32_t u32CountUpCond;   /*!< Hardware count up condition. @ref TMR6_HW_Count_Up_Cond_Define */
        uint32_t u32CountDownCond; /*!< Hardware count down condition. @ref TMR6_HW_Count_Down_Cond_Define */
    } hw_count;
    uint32_t u32PeriodValue;        /*!< The period reference value. (0x00 ~ 0xFFFF) or (0x00 ~ 0xFFFFFFFF) */
    uint32_t u32CountReload;        /*!< Count reload after overflow @ref TMR6_Count_Reload_Define */
} stc_tmr6_init_t;

/**
 * @brief Timer6 pwm output function structure definition
 */
typedef struct {
    uint32_t u32CompareValue;               /*!< Range (0 ~ 0xFFFF) or (0 ~ 0xFFFFFFFF) */
    uint32_t u32StartPolarity;              /*!< Pin polarity when count start @ref TMR6_Pin_Polarity_Define */
    uint32_t u32StopPolarity;               /*!< Pin polarity when count stop @ref TMR6_Pin_Polarity_Define */
    uint32_t u32CountUpMatchAPolarity;      /*!< Port state when match compare register A(GCMAR) at count-up mode \
                                                 @ref TMR6_Pin_Polarity_Define */
    uint32_t u32CountDownMatchAPolarity;    /*!< Port state when match compare register A(GCMAR) at count-down mode \
                                                 @ref TMR6_Pin_Polarity_Define */
    uint32_t u32CountUpMatchBPolarity;      /*!< Port state when match compare register B(GCMBR) at count-up mode \
                                                 @ref TMR6_Pin_Polarity_Define*/
    uint32_t u32CountDownMatchBPolarity;    /*!< Port state when match compare register B(GCMBR) at count-down mode\
                                                 @ref TMR6_Pin_Polarity_Define */
    uint32_t u32UdfPolarity;                /*!< Pin polarity when underflow @ref TMR6_Pin_Polarity_Define */
    uint32_t u32OvfPolarity;                /*!< Pin polarity when overflow @ref TMR6_Pin_Polarity_Define */
} stc_tmr6_pwm_init_t;

/**
 * @brief Timer6 buffer function configuration structure definition
 */
typedef struct {
    uint32_t u32BufNum;             /*!< The buffer number, and this parameter can be a value of \
                                         @ref TMR6_Buf_Num_Define */
    uint32_t u32BufTransCond;       /*!< The buffer send time, and this parameter can be a value of \
                                         @ref TMR6_Buf_Trans_Cond_Define */
} stc_tmr6_buf_config_t;

/**
 * @brief Timer6 Valid period function configuration structure definition
 */
typedef struct {
    uint32_t u32CountCond;          /*!< The count condition, and this parameter can be a value of \
                                          @ref TMR6_Valid_Period_Count_Cond_Define */
    uint32_t u32PeriodInterval;     /*!< The interval of the valid period @ref TMR6_Valid_Period_Count_Define */
} stc_tmr6_valid_period_config_t;

/**
 * @brief Timer6 EMB configuration structure definition
 */
typedef struct {
    uint32_t u32ValidCh;            /*!< Valid EMB event channel @ref TMR6_Emb_Ch_Define */
    uint32_t u32ReleaseMode;        /*!< Pin release mode when EMB event invalid @ref TMR6_Emb_Release_Mode_Define */
    uint32_t u32PinStatus;          /*!< Pin output status when EMB event valid @ref TMR6_Emb_Pin_Status_Define */
} stc_tmr6_emb_config_t;

/**
 * @brief Timer6 Dead time function configuration structure definition
 */
typedef struct {
    uint32_t u32EqualUpDown;        /*!< Enable down count dead time register equal to up count DT register \
                                         @ref TMR6_Deadtime_Reg_Equal_Func_Define */
    uint32_t u32BufUp;              /*!< Enable buffer transfer for up count dead time register (DTUBR-->DTUAR) \
                                         @ref TMR6_Deadtime_CountUp_Buf_Func_Define*/
    uint32_t u32BufDown;            /*!< Enable buffer transfer for down count dead time register (DTDBR-->DTDAR) \
                                         @ref TMR6_Deadtime_CountDown_Buf_Func_Define*/
    uint32_t u32BufTransCond;       /*!< Buffer transfer condition for triangular wave mode \
                                         @ref TMR6_Deadtime_Buf_Trans_Cond_Define */
} stc_tmr6_deadtime_config_t;

/**
 * @brief Timer6 Dead time function configuration structure definition
 */
typedef struct {
    uint32_t u32ZMaskCycle;         /*!< Z phase input mask periods selection @ref TMR6_Zmask_Cycle_Define */
    uint32_t u32PosCountMaskFunc;   /*!< As position count timer, clear function enable(TRUE) or disable(FALSE) during \
                                         the time of Z phase input mask @ref TMR6_Zmask_Pos_Unit_Clear_Func_Define */
    uint32_t u32RevoCountMaskFunc;  /*!< As revolution count timer, the counter function enable(TRUE) or disable(FALSE) \
                                         during the time of Z phase input mask \
                                         @ref TMR6_Zmask_Revo_Unit_Count_Func_Define*/
} stc_tmr6_zmask_config_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR6_Global_Macros TMR6 Global Macros
 * @{
 */

/**
 * @defgroup TMR6_Count_Src_Define TMR6 Count Source Define
 * @{
 */
#define TMR6_CNT_SRC_SW                     (0U)                    /*!< Timer6 normal count function */
#define TMR6_CNT_SRC_HW                     (1U)                    /*!< Timer6 hardware count function */
/**
 * @}
 */

/**
 * @defgroup TMR6_Stat_Flag_Define TMR6 Status Flag Define
 * @{
 */
#define TMR6_FLAG_MATCH_A                   (TMR6_STFLR_CMAF)       /*!< GCMAR match counter */
#define TMR6_FLAG_MATCH_B                   (TMR6_STFLR_CMBF)       /*!< GCMBR match counter */
#define TMR6_FLAG_MATCH_C                   (TMR6_STFLR_CMCF)       /*!< GCMCR match counter */
#define TMR6_FLAG_MATCH_D                   (TMR6_STFLR_CMDF)       /*!< GCMDR match counter */
#define TMR6_FLAG_MATCH_E                   (TMR6_STFLR_CMEF)       /*!< GCMER match counter */
#define TMR6_FLAG_MATCH_F                   (TMR6_STFLR_CMFF)       /*!< GCMFR match counter */
#define TMR6_FLAG_OVF                       (TMR6_STFLR_OVFF)       /*!< Sawtooth wave counter overflow, \
                                                                         Triangular wave peak point */
#define TMR6_FLAG_UDF                       (TMR6_STFLR_UDFF)       /*!< Sawtooth wave counter underflow, \
                                                                         Triangular wave valley point */
#define TMR6_FLAG_DEAD_TIME_ERR             (TMR6_STFLR_DTEF)       /*!< Dead time error */
#define TMR6_FLAG_UP_CNT_SPECIAL_MATCH_A    (TMR6_STFLR_CMSAUF)     /*!< SCMAR match counter when count-up */
#define TMR6_FLAG_DOWN_CNT_SPECIAL_MATCH_A  (TMR6_STFLR_CMSADF)     /*!< SCMAR match counter when count-down */
#define TMR6_FLAG_UP_CNT_SPECIAL_MATCH_B    (TMR6_STFLR_CMSBUF)     /*!< SCMBR match counter when count-up */
#define TMR6_FLAG_DOWN_CNT_SPECIAL_MATCH_B  (TMR6_STFLR_CMSBDF)     /*!< SCMBR match counter when count-down */
#define TMR6_FLAG_CNT_DIR                   (TMR6_STFLR_DIRF)       /*!< Count direction flag */
#define TMR6_FLAG_CAPT_AGAIN_A              (TMR6_STFLR_CMAF2)       /*!< Capture A again flag */
#define TMR6_FLAG_CAPT_AGAIN_B              (TMR6_STFLR_CMBF2)       /*!< Capture B again flag */

#define TMR6_FLAG_CLR_ALL                   (0x0C001EFFUL)          /*!< Clear all flag */
#define TMR6_FLAG_ALL                       (TMR6_FLAG_MATCH_A | TMR6_FLAG_MATCH_B | TMR6_FLAG_MATCH_C | \
                                            TMR6_FLAG_MATCH_D | TMR6_FLAG_MATCH_E | TMR6_FLAG_MATCH_F | \
                                            TMR6_FLAG_OVF | TMR6_FLAG_UDF | TMR6_FLAG_DEAD_TIME_ERR | \
                                            TMR6_FLAG_UP_CNT_SPECIAL_MATCH_A | TMR6_FLAG_DOWN_CNT_SPECIAL_MATCH_A | \
                                            TMR6_FLAG_UP_CNT_SPECIAL_MATCH_B | TMR6_FLAG_DOWN_CNT_SPECIAL_MATCH_B | \
                                            TMR6_FLAG_CNT_DIR | TMR6_FLAG_CAPT_AGAIN_A | TMR6_FLAG_CAPT_AGAIN_B)
/**
 * @}
 */

/**
 * @defgroup TMR6_Int_Flag_Define TMR6 Interrupt Flag Define
 * @{
 */
#define TMR6_INT_MATCH_A                    (TMR6_ICONR_INTENA)     /*!< GCMAR register matched */
#define TMR6_INT_MATCH_B                    (TMR6_ICONR_INTENB)     /*!< GCMBR register matched */
#define TMR6_INT_MATCH_C                    (TMR6_ICONR_INTENC)     /*!< GCMCR register matched */
#define TMR6_INT_MATCH_D                    (TMR6_ICONR_INTEND)     /*!< GCMDR register matched */
#define TMR6_INT_MATCH_E                    (TMR6_ICONR_INTENE)     /*!< GCMER register matched */
#define TMR6_INT_MATCH_F                    (TMR6_ICONR_INTENF)     /*!< GCMFR register matched */
#define TMR6_INT_OVF                        (TMR6_ICONR_INTENOVF)   /*!< Counter register overflow */
#define TMR6_INT_UDF                        (TMR6_ICONR_INTENUDF)   /*!< Counter register underflow */
#define TMR6_INT_DEAD_TIME_ERR              (TMR6_ICONR_INTENDTE)   /*!< Dead time error */
#define TMR6_INT_UP_CNT_SPECIAL_MATCH_A     (TMR6_ICONR_INTENSAU)   /*!< SCMAR register matched when count-up */
#define TMR6_INT_DOWN_CNT_SPECIAL_MATCH_A   (TMR6_ICONR_INTENSAD)   /*!< SCMAR register matched when count-down */
#define TMR6_INT_UP_CNT_SPECIAL_MATCH_B     (TMR6_ICONR_INTENSBU)   /*!< SCMBR register matched when count-up */
#define TMR6_INT_DOWN_CNT_SPECIAL_MATCH_B   (TMR6_ICONR_INTENSBD)   /*!< SCMBR register matched when count-down */
#define TMR6_INT_ALL                        (TMR6_INT_MATCH_A | TMR6_INT_MATCH_B | TMR6_INT_MATCH_C | TMR6_INT_MATCH_D |\
                                             TMR6_INT_MATCH_E | TMR6_INT_MATCH_F | TMR6_INT_OVF | TMR6_INT_UDF | \
                                             TMR6_INT_DEAD_TIME_ERR | TMR6_INT_UP_CNT_SPECIAL_MATCH_A | \
                                             TMR6_INT_DOWN_CNT_SPECIAL_MATCH_A | TMR6_INT_UP_CNT_SPECIAL_MATCH_B | \
                                             TMR6_INT_DOWN_CNT_SPECIAL_MATCH_B)
/**
 * @}
 */

/**
 * @defgroup TMR6_Period_Reg_Index_Define TMR6 Period Register Index Define
 * @{
 */
#define TMR6_PERIOD_REG_A                   (0x00UL)
#define TMR6_PERIOD_REG_B                   (0x01UL)
#define TMR6_PERIOD_REG_C                   (0x02UL)
/**
 * @}
 */

/**
 * @defgroup TMR6_Compare_Reg_Index_Define TMR6 Compare Register Index Define
 * @{
 */
#define TMR6_CMP_REG_A                      (0x00UL)
#define TMR6_CMP_REG_B                      (0x01UL)
#define TMR6_CMP_REG_C                      (0x02UL)
#define TMR6_CMP_REG_D                      (0x03UL)
#define TMR6_CMP_REG_E                      (0x04UL)
#define TMR6_CMP_REG_F                      (0x05UL)
/**
 * @}
 */

/**
 * @defgroup TMR6_Count_Ch_Define TMR6 General/Special Compare Channel Define
 * @{
 */
#define TMR6_CH_A                           (0x00UL)
#define TMR6_CH_B                           (0x01UL)
/**
 * @}
 */

/**
 * @defgroup TMR6_Buf_Num_Define TMR6 Buffer Number Define
 * @{
 */
#define TMR6_BUF_SINGLE                     (0x00UL)
#define TMR6_BUF_DUAL                       (TMR6_BCONR_BSEA)
/**
 * @}
 */

/**
 * @defgroup TMR6_Buf_Trans_Cond_Define TMR6 Buffer Transfer Time Configuration Define
 * @{
 */
#define TMR6_BUF_TRANS_INVD                 (0x00UL)
#define TMR6_BUF_TRANS_OVF                  (0x00000004UL)
#define TMR6_BUF_TRANS_UDF                  (0x00000008UL)
#define TMR6_BUF_TRANS_OVF_UDF              (0x0000000CUL)

/**
 * @}
 */

/**
 * @defgroup TMR6_Valid_Period_Count_Cond_Define TMR6 Valid Period Function Count Condition Define
 * @{
 */
#define TMR6_VALID_PERIOD_INVD                  (0x00UL)             /*!< Valid period function off */
#define TMR6_VALID_PERIOD_CNT_COND_VALLEY       (TMR6_VPERR_PCNTE_0) /*!< Count when Sawtooth waveform overflow and underflow, \
                                                                        triangular wave valley */
#define TMR6_VALID_PERIOD_CNT_COND_PEAK         (TMR6_VPERR_PCNTE_1) /*!< Count when Sawtooth waveform overflow and underflow, \
                                                                        triangular wave peak */
#define TMR6_VALID_PERIOD_CNT_COND_VALLEY_PEAK  (TMR6_VPERR_PCNTE)   /*!< Count when Sawtooth waveform overflow and underflow, \
                                                                        triangular wave valley and peak */
/**
 * @}
 */

/**
 * @defgroup TMR6_Valid_Period_Count_Define TMR6 Valid Period Function Count Define
 * @{
 */
#define TMR6_VALID_PERIOD_CNT_INVD          (0x00UL)
#define TMR6_VALID_PERIOD_CNT1              (1UL << TMR6_VPERR_PCNTS_POS)
#define TMR6_VALID_PERIOD_CNT2              (2UL << TMR6_VPERR_PCNTS_POS)
#define TMR6_VALID_PERIOD_CNT3              (3UL << TMR6_VPERR_PCNTS_POS)
#define TMR6_VALID_PERIOD_CNT4              (4UL << TMR6_VPERR_PCNTS_POS)
#define TMR6_VALID_PERIOD_CNT5              (5UL << TMR6_VPERR_PCNTS_POS)
#define TMR6_VALID_PERIOD_CNT6              (6UL << TMR6_VPERR_PCNTS_POS)
#define TMR6_VALID_PERIOD_CNT7              (7UL << TMR6_VPERR_PCNTS_POS)
/**
 * @}
 */

/**
 * @defgroup TMR6_DeadTime_Reg_Define TMR6 Dead Time Register Define
 * @{
 */
#define TMR6_DEADTIME_REG_UP_A              (0x00U)         /*!< Register DTUAR */
#define TMR6_DEADTIME_REG_DOWN_A            (0x01U)         /*!< Register DTDAR */
#define TMR6_DEADTIME_REG_UP_B              (0x02U)         /*!< Register DTUBR */
#define TMR6_DEADTIME_REG_DOWN_B            (0x03U)         /*!< Register DTDBR */
/**
 * @}
 */

/**
 * @defgroup TMR6_Pin_Define TMR6 Input And Output Pin Define
 * @{
 */
#define TMR6_IO_PWMA                        (0x00U)         /*!< Pin TIM6_<t>_PWMA */
#define TMR6_IO_PWMB                        (0x01U)         /*!< Pin TIM6_<t>_PWMB */
#define TMR6_INPUT_TRIGA                    (0x02U)         /*!< Input pin TIM6_TRIGA */
#define TMR6_INPUT_TRIGB                    (0x03U)         /*!< Input pin TIM6_TRIGB */
/**
 * @}
 */

/**
 * @defgroup TMR6_Input_Filter_Clock TMR6 Input Pin Filter Clock Divider Define
 * @{
 */
#define TMR6_FILTER_CLK_DIV1                (0x00U)
#define TMR6_FILTER_CLK_DIV4                (0x01U)
#define TMR6_FILTER_CLK_DIV16               (0x02U)
#define TMR6_FILTER_CLK_DIV64               (0x03U)
/**
 * @}
 */

/**
 * @defgroup TMR6_Pin_Mode_Define TMR6 Pin Function Mode Selection
 * @{
 */
#define TMR6_PIN_CMP_OUTPUT                 (0x00UL)
#define TMR6_PIN_CAPT_INPUT                 (TMR6_PCNAR_CAPMDA)
/**
 * @}
 */

/**
 * @defgroup TMR6_Count_State_Define TMR6 Count State
 * @{
 */
#define TMR6_STAT_START                     (0U)    /*!< Count start */
#define TMR6_STAT_STOP                      (1U)    /*!< Count stop */
#define TMR6_STAT_OVF                       (2U)    /*!< Count overflow */
#define TMR6_STAT_UDF                       (3U)    /*!< Count underflow */
#define TMR6_STAT_UP_CNT_MATCH_A            (4U)    /*!< Count up match compare register A */
#define TMR6_STAT_DOWN_CNT_MATCH_A          (5U)    /*!< Count down match compare register A */
#define TMR6_STAT_UP_CNT_MATCH_B            (6U)    /*!< Count up match compare register B */
#define TMR6_STAT_DOWN_CNT_MATCH_B          (7U)    /*!< Count down match compare register B */

/**
 * @}
 */

/**
 * @defgroup TMR6_Pin_Polarity_Define TMR6 Pin Output Polarity
 * @{
 */

#define TMR6_PWM_LOW                        (0x00U)
#define TMR6_PWM_HIGH                       (0x01U)
#define TMR6_PWM_HOLD                       (0x02U)
#define TMR6_PWM_INVT                       (0x03U)
/**
 * @}
 */

/**
 * @defgroup TMR6_Force_Output_Polarity_Define TMR6 Force Output Polarity Next Period
 * @{
 */
#define TMR6_PWM_FORCE_INVD                 (0x00U)
#define TMR6_PWM_FORCE_LOW                  (0x02U)
#define TMR6_PWM_FORCE_HIGH                 (0x03U)
/**
 * @}
 */

/**
 * @defgroup TMR6_Emb_Ch_Define TMR6 EMB Event Channel
 * @{
 */
#define TMR6_EMB_EVT_CH0                    (0x00UL)
/**
 * @}
 */

/**
 * @defgroup TMR6_Emb_Release_Mode_Define TMR6 EMB Function Release Mode When EMB Event Invalid
 * @{
 */
#define TMR6_EMB_RELEASE_IMMED              (0x00UL)
#define TMR6_EMB_RELEASE_OVF                (TMR6_PCNAR_EMBRA_0)
#define TMR6_EMB_RELEASE_UDF                (TMR6_PCNAR_EMBRA_1)
#define TMR6_EMB_RELEASE_OVF_UDF            (TMR6_PCNAR_EMBRA)
/**
 * @}
 */

/**
 * @defgroup TMR6_Emb_Pin_Status_Define TMR6 Pin Output Status When EMB Event Valid
 * @{
 */
#define TMR6_EMB_PIN_NORMAL                 (0x00UL)
#define TMR6_EMB_PIN_HIZ                    (TMR6_PCNAR_EMBCA_0)
#define TMR6_EMB_PIN_LOW                    (TMR6_PCNAR_EMBCA_1)
#define TMR6_EMB_PIN_HIGH                   (TMR6_PCNAR_EMBCA)

/**
 * @}
 */

/**
 * @defgroup TMR6_Deadtime_CountUp_Buf_Func_Define TMR6 Dead Time Buffer Function For Count Up Stage
 * @{
 */
#define TMR6_DEADTIME_CNT_UP_BUF_OFF        (0x00UL)
#define TMR6_DEADTIME_CNT_UP_BUF_ON         (TMR6_DCONR_DTBENU)
/**
 * @}
 */

/**
 * @defgroup TMR6_Deadtime_CountDown_Buf_Func_Define TMR6 Dead Time Buffer Function For Count Down Stage
 * @{
 */
#define TMR6_DEADTIME_CNT_DOWN_BUF_OFF      (0x00UL)
#define TMR6_DEADTIME_CNT_DOWN_BUF_ON       (TMR6_DCONR_DTBEND)
/**
 * @}
 */

/**
 * @defgroup TMR6_Deadtime_Buf_Trans_Cond_Define TMR6 Dead Time Buffer Transfer Condition Define For Triangular Count Mode
 * @{
 */
#define TMR6_DEADTIME_BUF_COND_INVD         (0x00U)
#define TMR6_DEADTIME_BUF_COND_OVF          (TMR6_DCONR_DTBTRU)
#define TMR6_DEADTIME_BUF_COND_UDF          (TMR6_DCONR_DTBTRD)
#define TMR6_DEADTIME_BUF_COND_OVF_UDF      (TMR6_DCONR_DTBTRU | TMR6_DCONR_DTBTRD)
/**
 * @}
 */

/**
 * @defgroup TMR6_Deadtime_Reg_Equal_Func_Define TMR6 Dead Time Function DTDAR Equal DTUAR
 * @{
 */
#define TMR6_DEADTIME_EQUAL_OFF             (0x00UL)
#define TMR6_DEADTIME_EQUAL_ON              (TMR6_DCONR_SEPA)
/**
 * @}
 */

/**
 * @defgroup TMR6_SW_Sync_Unit_define TMR6 Software Synchronization Start/Stop/Clear/Update Unit Number Define
 * @{
 */
#define TMR6_SW_SYNC_U1                     (TMR6_COMMON_SSTAR_SSTA1)
#define TMR6_SW_SYNC_U2                     (TMR6_COMMON_SSTAR_SSTA2)
#define TMR6_SW_SYNC_ALL                    (0x03UL)

/**
 * @}
 */

/**
 * @defgroup TMR6_hardware_start_condition_Define TMR6 Hardware Start Condition Define
 * @{
 */
#define TMR6_START_COND_PWMA_RISING         (TMR6_HSTAR_HSTA0)
#define TMR6_START_COND_PWMA_FALLING        (TMR6_HSTAR_HSTA1)
#define TMR6_START_COND_PWMB_RISING         (TMR6_HSTAR_HSTA2)
#define TMR6_START_COND_PWMB_FALLING        (TMR6_HSTAR_HSTA3)
#define TMR6_START_COND_EVT0                (TMR6_HSTAR_HSTA8)
#define TMR6_START_COND_EVT1                (TMR6_HSTAR_HSTA9)
#define TMR6_START_COND_TRIGA_RISING        (TMR6_HSTAR_HSTA16)
#define TMR6_START_COND_TRIGA_FALLING       (TMR6_HSTAR_HSTA17)
#define TMR6_START_COND_TRIGB_RISING        (TMR6_HSTAR_HSTA18)
#define TMR6_START_COND_TRIGB_FALLING       (TMR6_HSTAR_HSTA19)
#define TMR6_START_COND_ALL                 (0x000F030FUL)
/**
 * @}
 */

/**
 * @defgroup TMR6_hardware_stop_condition_Define TMR6 Hardware Stop Condition Define
 * @{
 */
#define TMR6_STOP_COND_PWMA_RISING          (TMR6_HSTPR_HSTP0)
#define TMR6_STOP_COND_PWMA_FALLING         (TMR6_HSTPR_HSTP1)
#define TMR6_STOP_COND_PWMB_RISING          (TMR6_HSTPR_HSTP2)
#define TMR6_STOP_COND_PWMB_FALLING         (TMR6_HSTPR_HSTP3)
#define TMR6_STOP_COND_EVT0                 (TMR6_HSTPR_HSTP8)
#define TMR6_STOP_COND_EVT1                 (TMR6_HSTPR_HSTP9)
#define TMR6_STOP_COND_TRIGA_RISING         (TMR6_HSTPR_HSTP16)
#define TMR6_STOP_COND_TRIGA_FALLING        (TMR6_HSTPR_HSTP17)
#define TMR6_STOP_COND_TRIGB_RISING         (TMR6_HSTPR_HSTP18)
#define TMR6_STOP_COND_TRIGB_FALLING        (TMR6_HSTPR_HSTP19)
#define TMR6_STOP_COND_ALL                  (0x000F030FUL)
/**
 * @}
 */

/**
 * @defgroup TMR6_hardware_clear_condition_Define TMR6 Hardware Clear Condition Define
 * @{
 */
#define TMR6_CLR_COND_PWMA_RISING           (TMR6_HCLRR_HCLE0)
#define TMR6_CLR_COND_PWMA_FALLING          (TMR6_HCLRR_HCLE1)
#define TMR6_CLR_COND_PWMB_RISING           (TMR6_HCLRR_HCLE2)
#define TMR6_CLR_COND_PWMB_FALLING          (TMR6_HCLRR_HCLE3)
#define TMR6_CLR_COND_EVT0                  (TMR6_HCLRR_HCLE8)
#define TMR6_CLR_COND_EVT1                  (TMR6_HCLRR_HCLE9)
#define TMR6_CLR_COND_TRIGA_RISING          (TMR6_HCLRR_HCLE16)
#define TMR6_CLR_COND_TRIGA_FALLING         (TMR6_HCLRR_HCLE17)
#define TMR6_CLR_COND_TRIGB_RISING          (TMR6_HCLRR_HCLE18)
#define TMR6_CLR_COND_TRIGB_FALLING         (TMR6_HCLRR_HCLE19)
#define TMR6_CLR_COND_ALL                   (0x000F030FUL)
/**
 * @}
 */

/**
 * @defgroup TMR6_hardware_update_condition_Define TMR6 Hardware Update Condition Define
 * @{
 */
#define TMR6_UPD_COND_PWMA_RISING           (TMR6_HUPDR_HUPD0)
#define TMR6_UPD_COND_PWMA_FALLING          (TMR6_HUPDR_HUPD1)
#define TMR6_UPD_COND_PWMB_RISING           (TMR6_HUPDR_HUPD2)
#define TMR6_UPD_COND_PWMB_FALLING          (TMR6_HUPDR_HUPD3)
#define TMR6_UPD_COND_EVT0                  (TMR6_HUPDR_HUPD8)
#define TMR6_UPD_COND_EVT1                  (TMR6_HUPDR_HUPD9)
#define TMR6_UPD_COND_TRIGA_RISING          (TMR6_HUPDR_HUPD16)
#define TMR6_UPD_COND_TRIGA_FALLING         (TMR6_HUPDR_HUPD17)
#define TMR6_UPD_COND_TRIGB_RISING          (TMR6_HUPDR_HUPD18)
#define TMR6_UPD_COND_TRIGB_FALLING         (TMR6_HUPDR_HUPD19)
#define TMR6_UPD_COND_ALL                   (0x000F030FUL)
/**
 * @}
 */

/**
 * @defgroup TMR6_hardware_capture_condition_Define TMR6 Hardware Capture Condition Define
 * @{
 */
#define TMR6_CAPT_COND_PWMA_RISING          (TMR6_HCPAR_HCPA0)
#define TMR6_CAPT_COND_PWMA_FALLING         (TMR6_HCPAR_HCPA1)
#define TMR6_CAPT_COND_PWMB_RISING          (TMR6_HCPAR_HCPA2)
#define TMR6_CAPT_COND_PWMB_FALLING         (TMR6_HCPAR_HCPA3)
#define TMR6_CAPT_COND_EVT0                 (TMR6_HCPAR_HCPA8)
#define TMR6_CAPT_COND_EVT1                 (TMR6_HCPAR_HCPA9)
#define TMR6_CAPT_COND_TRIGA_RISING         (TMR6_HCPAR_HCPA16)
#define TMR6_CAPT_COND_TRIGA_FALLING        (TMR6_HCPAR_HCPA17)
#define TMR6_CAPT_COND_TRIGB_RISING         (TMR6_HCPAR_HCPA18)
#define TMR6_CAPT_COND_TRIGB_FALLING        (TMR6_HCPAR_HCPA19)
#define TMR6_CAPT_COND_XOR_RISING           (TMR6_HCPAR_HCPA24)
#define TMR6_CAPT_COND_XOR_FALLING          (TMR6_HCPAR_HCPA25)
#define TMR6_CAPT_COND_ALL                  (0x030F030FUL)
/**
 * @}
 */

/**
 * @defgroup TMR6_HW_Count_Up_Cond_Define TMR6 Hardware Count Up Condition Define
 * @{
 */
#define TMR6_CNT_UP_COND_INVD                       (0U)
#define TMR6_CNT_UP_COND_PWMA_LOW_PWMB_RISING       (TMR6_HCUPR_HCUP0)
#define TMR6_CNT_UP_COND_PWMA_LOW_PWMB_FALLING      (TMR6_HCUPR_HCUP1)
#define TMR6_CNT_UP_COND_PWMA_HIGH_PWMB_RISING      (TMR6_HCUPR_HCUP2)
#define TMR6_CNT_UP_COND_PWMA_HIGH_PWMB_FALLING     (TMR6_HCUPR_HCUP3)
#define TMR6_CNT_UP_COND_PWMB_LOW_PWMA_RISING       (TMR6_HCUPR_HCUP4)
#define TMR6_CNT_UP_COND_PWMB_LOW_PWMA_FALLING      (TMR6_HCUPR_HCUP5)
#define TMR6_CNT_UP_COND_PWMB_HIGH_PWMA_RISING      (TMR6_HCUPR_HCUP6)
#define TMR6_CNT_UP_COND_PWMB_HIGH_PWMA_FALLING     (TMR6_HCUPR_HCUP7)
#define TMR6_CNT_UP_COND_EVT0                       (TMR6_HCUPR_HCUP8)
#define TMR6_CNT_UP_COND_EVT1                       (TMR6_HCUPR_HCUP9)
#define TMR6_CNT_UP_COND_TRIGA_RISING               (TMR6_HCUPR_HCUP16)
#define TMR6_CNT_UP_COND_TRIGA_FALLING              (TMR6_HCUPR_HCUP17)
#define TMR6_CNT_UP_COND_TRIGB_RISING               (TMR6_HCUPR_HCUP18)
#define TMR6_CNT_UP_COND_TRIGB_FALLING              (TMR6_HCUPR_HCUP19)
#define TMR6_CNT_UP_COND_ALL                        (0x000F03FFUL)
/**
 * @}
 */

/**
 * @defgroup TMR6_HW_Count_Down_Cond_Define TMR6 Hardware Count Down Condition Define
 * @{
 */
#define TMR6_CNT_DOWN_COND_INVD                     (0U)
#define TMR6_CNT_DOWN_COND_PWMA_LOW_PWMB_RISING     (TMR6_HCDOR_HCDO0)
#define TMR6_CNT_DOWN_COND_PWMA_LOW_PWMB_FALLING    (TMR6_HCDOR_HCDO1)
#define TMR6_CNT_DOWN_COND_PWMA_HIGH_PWMB_RISING    (TMR6_HCDOR_HCDO2)
#define TMR6_CNT_DOWN_COND_PWMA_HIGH_PWMB_FALLING   (TMR6_HCDOR_HCDO3)
#define TMR6_CNT_DOWN_COND_PWMB_LOW_PWMA_RISING     (TMR6_HCDOR_HCDO4)
#define TMR6_CNT_DOWN_COND_PWMB_LOW_PWMA_FALLING    (TMR6_HCDOR_HCDO5)
#define TMR6_CNT_DOWN_COND_PWMB_HIGH_PWMA_RISING    (TMR6_HCDOR_HCDO6)
#define TMR6_CNT_DOWN_COND_PWMB_HIGH_PWMA_FALLING   (TMR6_HCDOR_HCDO7)
#define TMR6_CNT_DOWN_COND_EVT0                     (TMR6_HCDOR_HCDO8)
#define TMR6_CNT_DOWN_COND_EVT1                     (TMR6_HCDOR_HCDO9)
#define TMR6_CNT_DOWN_COND_TRIGA_RISING             (TMR6_HCDOR_HCDO16)
#define TMR6_CNT_DOWN_COND_TRIGA_FALLING            (TMR6_HCDOR_HCDO17)
#define TMR6_CNT_DOWN_COND_TRIGB_RISING             (TMR6_HCDOR_HCDO18)
#define TMR6_CNT_DOWN_COND_TRIGB_FALLING            (TMR6_HCDOR_HCDO19)
#define TMR6_CNT_DOWN_COND_ALL                      (0x000F03FFUL)
/**
 * @}
 */

/**
 * @defgroup TMR6_Count_Dir_Define TMR6 Base Counter Function Direction Define
 * @{
 */
#define TMR6_CNT_UP                         (TMR6_GCONR_DIR)
#define TMR6_CNT_DOWN                       (0x00UL)
/**
 * @}
 */

/**
 * @defgroup TMR6_Count_Dir_Status_Define TMR6 Count Direction Status Define
 * @{
 */
#define TMR6_STAT_CNT_UP                    (TMR6_STFLR_DIRF)
#define TMR6_STAT_CNT_DOWN                  (0x00UL)
/**
 * @}
 */

/**
 * @defgroup TMR6_Count_Mode_Define TMR6 Base Counter Function Mode Define
 * @{
 */
#define TMR6_MD_SAWTOOTH                    (0x00UL)
#define TMR6_MD_TRIANGLE                    (TMR6_GCONR_MODE)

/**
 * @}
 */

/**
 * @defgroup TMR6_Count_Clock_Define TMR6 Base Counter Clock Source Define
 * @{
 */
#define TMR6_CLK_DIV1                       (0x00UL)
#define TMR6_CLK_DIV2                       (0x01UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_DIV4                       (0x02UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_DIV8                       (0x03UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_DIV16                      (0x04UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_DIV32                      (0x05UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_DIV64                      (0x06UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_DIV128                     (0x07UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_DIV256                     (0x08UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_DIV512                     (0x09UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_DIV1024                    (0x0AUL << TMR6_GCONR_CKDIV_POS)

/**
 * @}
 */

/**
 * @defgroup TMR6_Count_Reload_Define TMR6 Count Stop After Overflow Function Define
 * @{
 */
#define TMR6_CNT_RELOAD_ON                  (0x00UL)
#define TMR6_CNT_RELOAD_OFF                 (TMR6_GCONR_OVSTP)
/**
 * @}
 */

/**
 * @defgroup TMR6_Zmask_Cycle_Define TMR6 Z Mask Input Function Mask Cycles Number Define
 * @{
 */
#define TMR6_ZMASK_FUNC_INVD                (0x00UL)
#define TMR6_ZMASK_CYCLE_4                  (TMR6_GCONR_ZMSKVAL_0)
#define TMR6_ZMASK_CYCLE_8                  (TMR6_GCONR_ZMSKVAL_1)
#define TMR6_ZMASK_CYCLE_16                 (TMR6_GCONR_ZMSKVAL)
/**
 * @}
 */

/**
 * @defgroup TMR6_Zmask_Pos_Unit_Clear_Func_Define TMR6 Unit As Position Timer, Z Phase Input Mask Function Define For Clear Action
 * @{
 */
#define TMR6_POS_CLR_ZMASK_FUNC_OFF         (0x00UL)
#define TMR6_POS_CLR_ZMASK_FUNC_ON          (TMR6_GCONR_ZMSKPOS)
/**
 * @}
 */

/**
 * @defgroup TMR6_Zmask_Revo_Unit_Count_Func_Define TMR6 Unit As Revolution Timer, Z Phase Input Mask Function Define For Count Action
 * @{
 */
#define TMR6_REVO_CNT_ZMASK_FUNC_OFF        (0x00UL)
#define TMR6_REVO_CNT_ZMASK_FUNC_ON         (TMR6_GCONR_ZMSKREV)
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
 * @addtogroup TMR6_Global_Functions
 * @{
 */
/**
 * @brief  Get Software Sync start status
 * @param  None
 * @retval uint32_t                 Data indicate the read status.
 */
__STATIC_INLINE uint32_t TMR6_GetSWSyncStartStatus(void)
{
    return READ_REG32(CM_TMR6_COMMON->SSTAR);
}

/* Base count */
int32_t TMR6_StructInit(stc_tmr6_init_t *pstcTmr6Init);
int32_t TMR6_Init(CM_TMR6_TypeDef *TMR6x, const stc_tmr6_init_t *pstcTmr6Init);

void TMR6_SetCountMode(CM_TMR6_TypeDef *TMR6x, uint32_t u32Mode);
void TMR6_SetCountDir(CM_TMR6_TypeDef *TMR6x, uint32_t u32Dir);
uint32_t TMR6_GetCountDir(CM_TMR6_TypeDef *TMR6x);
void TMR6_SetClockDiv(CM_TMR6_TypeDef *TMR6x, uint32_t u32Div);
void TMR6_CountReloadCmd(CM_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState);

/* Hardware count */
void TMR6_HWCountUpCondCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Cond, en_functional_state_t enNewState);
void TMR6_HWCountDownCondCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Cond, en_functional_state_t enNewState);

/* PWM output */
int32_t TMR6_PWM_StructInit(stc_tmr6_pwm_init_t *pstcPwmInit);
int32_t TMR6_PWM_Init(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, const stc_tmr6_pwm_init_t *pstcPwmInit);
void TMR6_PWM_OutputCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, en_functional_state_t enNewState);
void TMR6_PWM_SetPolarity(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, uint32_t u32CountState, uint32_t u32Polarity);
void TMR6_PWM_SetForcePolarity(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, uint32_t u32Polarity);

/* Input capture */
void TMR6_HWCaptureCondCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, uint32_t u32Cond, en_functional_state_t enNewState);

/* Pin config */
void TMR6_SetFilterClockDiv(CM_TMR6_TypeDef *TMR6x, uint32_t u32Pin, uint32_t u32Div);
void TMR6_FilterCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Pin, en_functional_state_t enNewState);
void TMR6_SetFunc(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, uint32_t u32Func);

/* Universal */
void TMR6_IntCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32IntType, en_functional_state_t enNewState);
en_flag_status_t TMR6_GetStatus(const CM_TMR6_TypeDef *TMR6x, uint32_t u32Flag);
void TMR6_ClearStatus(CM_TMR6_TypeDef *TMR6x, uint32_t u32Flag);
uint32_t TMR6_GetPeriodNum(const CM_TMR6_TypeDef *TMR6x);
void TMR6_DeInit(CM_TMR6_TypeDef *TMR6x);
void TMR6_Start(CM_TMR6_TypeDef *TMR6x);
void TMR6_Stop(CM_TMR6_TypeDef *TMR6x);

/* Register write */
void TMR6_SetCountValue(CM_TMR6_TypeDef *TMR6x, uint32_t u32Value);
void TMR6_SetUpdateValue(CM_TMR6_TypeDef *TMR6x, uint32_t u32Value);
void TMR6_SetPeriodValue(CM_TMR6_TypeDef *TMR6x, uint32_t u32Index, uint32_t u32Value);
void TMR6_SetCompareValue(CM_TMR6_TypeDef *TMR6x, uint32_t u32Index, uint32_t u32Value);
void TMR6_SetSpecialCompareValue(CM_TMR6_TypeDef *TMR6x, uint32_t u32Index, uint32_t u32Value);
void TMR6_SetDeadTimeValue(CM_TMR6_TypeDef *TMR6x, uint32_t u32Index, uint32_t u32Value);

/* Register read */
uint32_t TMR6_GetCountValue(const CM_TMR6_TypeDef *TMR6x);
uint32_t TMR6_GetUpdateValue(const CM_TMR6_TypeDef *TMR6x);
uint32_t TMR6_GetPeriodValue(const CM_TMR6_TypeDef *TMR6x, uint32_t u32Index);
uint32_t TMR6_GetCompareValue(const CM_TMR6_TypeDef *TMR6x, uint32_t u32Index);
uint32_t TMR6_GetSpecialCompareValue(const CM_TMR6_TypeDef *TMR6x, uint32_t u32Index);
uint32_t TMR6_GetDeadTimeValue(const CM_TMR6_TypeDef *TMR6x, uint32_t u32Index);

/* Buffer function */
int32_t TMR6_GeneralBufConfig(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, const stc_tmr6_buf_config_t *pstcBufConfig);
int32_t TMR6_PeriodBufConfig(CM_TMR6_TypeDef *TMR6x, const stc_tmr6_buf_config_t *pstcBufConfig);

int32_t TMR6_SpecialBufConfig(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, const stc_tmr6_buf_config_t *pstcBufConfig);
void TMR6_GeneralBufCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, en_functional_state_t enNewState);
void TMR6_SpecialBufCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, en_functional_state_t enNewState);
void TMR6_PeriodBufCmd(CM_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState);

/* Extend function */
int32_t TMR6_ValidPeriodConfig(CM_TMR6_TypeDef *TMR6x, const stc_tmr6_valid_period_config_t *pstcValidperiodConfig);
void TMR6_ValidPeriodCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, en_functional_state_t enNewState);
void TMR6_DeadTimeFuncCmd(CM_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState);
int32_t TMR6_DeadTimeConfig(CM_TMR6_TypeDef *TMR6x, const stc_tmr6_deadtime_config_t *pstcDeadTimeConfig);
int32_t TMR6_ZMaskConfig(CM_TMR6_TypeDef *TMR6x, const stc_tmr6_zmask_config_t *pstcZMaskConfig);
int32_t TMR6_EMBConfig(CM_TMR6_TypeDef *TMR6x, uint32_t u32Ch, const stc_tmr6_emb_config_t *pstcEmbConfig);
int32_t TMR6_BufFuncStructInit(stc_tmr6_buf_config_t *pstcBufConfig);
int32_t TMR6_ValidPeriodStructInit(stc_tmr6_valid_period_config_t *pstcValidperiodConfig);
int32_t TMR6_EMBConfigStructInit(stc_tmr6_emb_config_t *pstcEmbConfig);
int32_t TMR6_DeadTimeStructInit(stc_tmr6_deadtime_config_t *pstcDeadTimeConfig);
int32_t TMR6_ZMaskConfigStructInit(stc_tmr6_zmask_config_t *pstcZMaskConfig);

/* Software synchronous control */
void TMR6_SWSyncStart(uint32_t u32Unit);
void TMR6_SWSyncStop(uint32_t u32Unit);
void TMR6_SWSyncClear(uint32_t u32Unit);
void TMR6_SWSyncUpdate(uint32_t u32Unit);

/* Hardware control */
void TMR6_HWStartCondCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Cond, en_functional_state_t enNewState);
void TMR6_HWStartCmd(CM_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState);
void TMR6_HWStopCondCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Cond, en_functional_state_t enNewState);
void TMR6_HWStopCmd(CM_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState);
void TMR6_HWClearCondCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Cond, en_functional_state_t enNewState);
void TMR6_HWClearCmd(CM_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState);
void TMR6_HWUpdateCondCmd(CM_TMR6_TypeDef *TMR6x, uint32_t u32Cond, en_functional_state_t enNewState);
void TMR6_HWUpdateCmd(CM_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState);
/**
 * @}
 */

#endif /* LL_TMR6_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_TMR6_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
