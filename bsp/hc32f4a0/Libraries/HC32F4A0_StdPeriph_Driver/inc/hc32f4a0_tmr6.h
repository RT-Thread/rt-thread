/**
 *******************************************************************************
 * @file  hc32f4a0_tmr6.h
 * @brief Head file for TMR6 module.
 *
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Wangmin         First version
   2020-07-15       Wangmin         Refine macro define
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
#ifndef __HC32F4A0_TMR6_H__
#define __HC32F4A0_TMR6_H__

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
 * @addtogroup DDL_TMR6
 * @{
 */

#if (DDL_TMR6_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMR6_Global_Types TMR6 Global Types
 * @{
 */

/**
 * @brief Timer6 base counter function structure definition
 */
typedef struct
{
    uint32_t u32CntMode;            /*!< Count mode, @ref TMR6_Count_Mode_define */
    uint32_t u32CntDir;             /*!< Count direction, @ref TMR6_Count_Direction_define */
    uint32_t u32CntClkDiv;          /*!< Count clock division select, @ref TMR6_Count_Clock_define */
    uint32_t u32CntStpAftOvf;       /*!< Count stop after overflow @ref TMR6_Count_Stop_After_Overflow_define*/
}stc_tmr6_basecnt_cfg_t;

/**
 * @brief Timer6 buffer function configuration structure definition
 */
typedef struct
{
    uint32_t u32BufFunCmd;         /*!< specifies the buffer function status,
                                         and this parameter can be a value of
                                         @ref TMR6_Buffer_Function_sta_Define */
    uint32_t u32BufNum;            /*!< specifies the buffer number,
                                         and this parameter can be a value of
                                         @ref TMR6_Buffer_Number_Chose_Define */
    uint32_t u32BufTransTim;       /*!< specifies the buffer send time,
                                         and this parameter can be a value of
                                         @ref TMR6_Buffer_Transfer_Time_Cfg_Define */
}stc_tmr6_buf_func_cfg_t;

/**
 * @brief Timer6 Valid period function configuration structure definition
 */
typedef struct
{
    uint32_t u32StatChA;           /*!< specifies the valid period function status for channel A,
                                         and this parameter can be a value of
                                         @ref TMR6_Valid_Period_CHA_STAT_Define */
    uint32_t u32StatChB;           /*!< specifies the valid period function status for channel B,
                                         and this parameter can be a value of
                                         @ref TMR6_Valid_Period_CHB_STAT_Define */
    uint32_t u32CntCond;           /*!< specifies the count condition,
                                         and this parameter can be a value of
                                         @ref TMR6_Valid_Period_Count_Condition_Define */
    uint32_t u32PeriodInterval;    /*!< specifies the interval of the valid period,
                                         @ref TMR6_Valid_Period_Count_Define */
}stc_tmr6_valid_period_func_cfg_t;

/**
 * @brief Timer6 port input configuration structure definition
 */
typedef struct
{
    uint32_t u32PortMode;           /*!< Port function mode @ref TMR6_Port_Mode_Func */
    uint32_t u32FilterSta;          /*!< trig source capture input filter status
                                         @ref TMR6_Port_Input_Filter_Sta*/
    uint32_t u32FltClk;             /*!< Filter clock @ref TMR6_Input_Port_Filter_Clk*/
}stc_tmr6_port_input_cfg_t;

/**
 * @brief Timer6 port output configuration structure definition
 */
typedef struct
{
    uint32_t u32PortMode;           /*!< Port function mode @ref TMR6_Port_Mode_Func */
    uint32_t u32NextPeriodForceSta; /*!< Port State Next period @ref TMR6_Force_Port_Output_Sta */
    uint32_t u32DownCntMatchAnotherCmpRegSta; /*!< Port state when counter match another compare register
                                                    (CHA matched GCMBR, CHB matched GCMAR) in count-down mode
                                                    @ref TMR6_Port_Output_Sta */
    uint32_t u32UpCntMatchAnotherCmpRegSta;   /*!< Port state when counter match another compare register
                                                    (CHA matched GCMBR, CHB matched GCMAR) in count-up mode
                                                    @ref TMR6_Port_Output_Sta*/
    uint32_t u32DownCntMatchCmpRegSta;        /*!< Port state when counter match compare register
                                                    (CHA matched GCMAR, CHB matched GCMBR) in count-down mode
                                                    @ref TMR6_Port_Output_Sta */
    uint32_t u32UpCntMatchCmpRegSta;          /*!< Port state when counter match compare register
                                                    (CHA matched GCMAR, CHB matched GCMBR) in count-up mode
                                                    @ref TMR6_Port_Output_Sta */
    uint32_t u32UnderflowSta;       /*!< Port State when counter underflow @ref TMR6_Port_Output_Sta */
    uint32_t u32OverflowSta;        /*!< Port State when counter overflow @ref TMR6_Port_Output_Sta */
    uint32_t u32StopSta;            /*!< Port State when count stop @ref TMR6_Port_Output_Sta */
    uint32_t u32StartSta;           /*!< Port State when count start @ref TMR6_Port_Output_Sta */
}stc_tmr6_port_output_cfg_t;

/**
 * @brief Timer6 EMB configuration structure definition
 */
typedef struct
{
    uint32_t u32ValidCh;            /*!< Valid EMB event channel @ref TMR6_Emb_channel */
    uint32_t u32ReleaseMode;        /*!< Port release mode when EMB event invalid @ref TMR6_Emb_Release_Mode */
    uint32_t u32PortSta;            /*!< Port Output status when EMB event valid @ref TMR6_Emb_Port_Sta */
}stc_tmr6_emb_cfg_t;

/**
 * @brief Timer6 Dead time function configuration structure definition
 */
typedef struct
{
    uint32_t u32DtEqualUpDwn;       /*!< Enable down count dead time register equal to up count DT register
                                         @ref TMR6_Deadtime_Reg_Equal_Func_define */
    uint32_t u32EnDtBufUp;          /*!< Enable buffer transfer for up count dead time register
                                         (DTUBR-->DTUAR) @ref TMR6_Deadtime_CountUp_Buf_Func_define*/
    uint32_t u32EnDtBufDwn;         /*!< Enable buffer transfer for down count dead time register
                                         (DTDBR-->DTDAR) @ref TMR6_Deadtime_CountDown_Buf_Func_define*/
    uint32_t u32DtUpdCond;          /*!< Buffer transfer condition for triangular wave mode
                                          @ref TMR6_Deadtime_Buf_Transfer_Condition_define */
}stc_tmr6_deadtime_cfg_t;

/**
 * @brief Timer6 Dead time function configuration structure definition
 */
typedef struct
{
    uint32_t u32ZMaskCycle;         /*!< Z phase input mask periods selection @ref TMR6_Zmask_Cycle_define*/
    uint32_t u32PosCntMaskEn;       /*!< As position count timer, clear function enable(TRUE) or disable(FALSE)
                                         during the time of Z phase input mask @ref TMR6_Zmask_Position_Unit_Clear_Func_define*/
    uint32_t u32RevCntMaskEn;       /*!< As revolution count timer, the counter function enable(TRUE) or
                                         disable(FALSE) during the time of Z phase input mask @ref TMR6_Zmask_Revolution_Unit_Count_Func_define*/
}stc_tmr6_zmask_cfg_t;


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


/** @defgroup TMR6_Sta_Bit_Get_Define TMR6 status bit define
 * @{
 */
/* Status bit indicate that GCMAR register matched with counter register */
#define TMR6_STAT_CNT_MATCH_A          (TMR6_STFLR_CMAF)
/* Status bit indicate that GCMBR register matched with counter register */
#define TMR6_STAT_CNT_MATCH_B          (TMR6_STFLR_CMBF)
/* Status bit indicate that GCMCR register matched with counter register */
#define TMR6_STAT_CNT_MATCH_C          (TMR6_STFLR_CMCF)
/* Status bit indicate that GCMDR register matched with counter register */
#define TMR6_STAT_CNT_MATCH_D          (TMR6_STFLR_CMDF)
/* Status bit indicate that GCMER register matched with counter register */
#define TMR6_STAT_CNT_MATCH_E          (TMR6_STFLR_CMEF)
/* Status bit indicate that GCMFR register matched with counter register */
#define TMR6_STAT_CNT_MATCH_F          (TMR6_STFLR_CMFF)
/* Status bit indicate that counter register overflow */
#define TMR6_STAT_OVERFLOW             (TMR6_STFLR_OVFF)
/* Status bit indicate that counter register underflow */
#define TMR6_STAT_UNDERFLOW            (TMR6_STFLR_UDFF)
/* Status bit indicate that dead time error */
#define TMR6_STAT_DEAD_TIME_ERR        (TMR6_STFLR_DTEF)
/* Status bit indicate that SCMAR register matched with counter register during count-up */
#define TMR6_STAT_UPCNT_SP_MATCH_A     (TMR6_STFLR_CMSAUF)
/* Status bit indicate that SCMAR register matched with counter register during count-down */
#define TMR6_STAT_DOWNCNT_SP_MATCH_A   (TMR6_STFLR_CMSADF)
/* Status bit indicate that SCMBR register matched with counter register during count-up */
#define TMR6_STAT_UPCNT_SP_MATCH_B     (TMR6_STFLR_CMSBUF)
/* Status bit indicate that SCMBR register matched with counter register during count-down */
#define TMR6_STAT_DOWNCNT_SP_MATCH_B   (TMR6_STFLR_CMSBDF)
/* Counter direction flag */
#define TMR6_STAT_CNT_DIR              (TMR6_STFLR_DIRF)
/**
 * @}
 */

/** @defgroup TMR6_Interrupt_Enable_Bit_Define TMR6 interrupt configuration bit define
 * @{
 */
/* Interrupt enable bit for GCMAR register matched */
#define TMR6_IRQ_EN_CNT_MATCH_A           (TMR6_ICONR_INTENA)
/* Interrupt enable bit for GCMBR register matched */
#define TMR6_IRQ_EN_CNT_MATCH_B           (TMR6_ICONR_INTENB)
/* Interrupt enable bit for GCMCR register matched */
#define TMR6_IRQ_EN_CNT_MATCH_C           (TMR6_ICONR_INTENC)
/* Interrupt enable bit for GCMDR register matched */
#define TMR6_IRQ_EN_CNT_MATCH_D           (TMR6_ICONR_INTEND)
/* Interrupt enable bit for GCMER register matched */
#define TMR6_IRQ_EN_CNT_MATCH_E           (TMR6_ICONR_INTENE)
/* Interrupt enable bit for GCMFR register matched */
#define TMR6_IRQ_EN_CNT_MATCH_F           (TMR6_ICONR_INTENF)
/* Interrupt enable bit for counter register overflow */
#define TMR6_IRQ_EN_OVERFLOW              (TMR6_ICONR_INTENOVF)
/* Interrupt enable bit for counter register underflow */
#define TMR6_IRQ_EN_UNDERFLOW             (TMR6_ICONR_INTENUDF)
/* Interrupt enable bit for dead time */
#define TMR6_IRQ_EN_DEAD_TIME_ERR         (TMR6_ICONR_INTENDTE)
/* Interrupt enable bit for SCMAR register matched during count-up*/
#define TMR6_IRQ_EN_UPCNT_SP_MATCH_A      (TMR6_ICONR_INTENSAU)
/* Interrupt enable bit for SCMAR register matched during count-down*/
#define TMR6_IRQ_EN_DOWNCNT_SP_MATCH_A    (TMR6_ICONR_INTENSAD)
/* Interrupt enable bit for SCMBR register matched during count-up*/
#define TMR6_IRQ_EN_UPCNT_SP_MATCH_B      (TMR6_ICONR_INTENSBU)
/* Interrupt enable bit for SCMBR register matched during count-down*/
#define TMR6_IRQ_EN_DOWNCNT_SP_MATCH_B    (TMR6_ICONR_INTENSBD)
/**
 * @}
 */

/** @defgroup TMR6_Period_Register_Index_Define TMR6 period register Index define
 * @{
 */
#define TMR6_PERIOD_REG_A   (0x00UL)
#define TMR6_PERIOD_REG_B   (0x01UL)
#define TMR6_PERIOD_REG_C   (0x02UL)
/**
 * @}
 */

/** @defgroup TMR6_Compare_Register_Index_Define TMR6 compare register Index define
 * @{
 */
#define TMR6_CMP_REG_A      (0x00UL)
#define TMR6_CMP_REG_B      (0x01UL)
#define TMR6_CMP_REG_C      (0x02UL)
#define TMR6_CMP_REG_D      (0x03UL)
#define TMR6_CMP_REG_E      (0x04UL)
#define TMR6_CMP_REG_F      (0x05UL)
/**
 * @}
 */

/** @defgroup TMR6_Compare_channel_Define TMR6 general/special compare channel index define
 * @{
 */
#define TMR6_CH_A           (0x00UL)
#define TMR6_CH_B           (0x01UL)
/**
 * @}
 */

/** @defgroup TMR6_Buffer_Function_sta_Define TMR6 buffer function status define
 * @{
 */
#define TMR6_BUF_FUNC_OFF   (0x00000000UL)
#define TMR6_BUF_FUNC_ON    (TMR6_BCONR_BENA)
/**
 * @}
 */

/** @defgroup TMR6_Buffer_Number_Chose_Define TMR6 buffer number configuration define
 * @{
 */
#define TMR6_BUF_FUNC_SINGLE   (0x00000000UL)
#define TMR6_BUF_FUNC_DOUBLE   (TMR6_BCONR_BSEA)
/**
 * @}
 */

/** @defgroup TMR6_Buffer_Transfer_Time_Cfg_Define TMR6 buffer transfer time configuration define
 * @{
 */
#define TMR6_BUF_TRANS_TIM_NONE        (0x00000000UL)
#define TMR6_BUF_TRANS_TIM_OVERFLOW    (TMR6_BCONR_BTRUA)
#define TMR6_BUF_TRANS_TIM_UNDERFLOW   (TMR6_BCONR_BTRDA)
#define TMR6_BUF_TRANS_TIM_BOTH        (TMR6_BCONR_BTRUA | TMR6_BCONR_BTRDA)
/**
 * @}
 */

/** @defgroup TMR6_Valid_Period_Count_Condition_Define TMR6 valid period function count condition define
 * @{
 */
/* Valid period function off */
#define TMR6_VALID_PERIOD_FUNC_OFF             (0x00000000UL)
/* Counted when Sawtooth waveform overflow and underflow, triangular wave underflow */
#define TMR6_VALID_PERIOD_CNT_COND_UNDERFLOW   (TMR6_VPERR_PCNTE_0)
/* Counted when Sawtooth waveform overflow and underflow, triangular wave overflow */
#define TMR6_VALID_PERIOD_CNT_COND_OVERFLOW    (TMR6_VPERR_PCNTE_1)
/* Counted when Sawtooth waveform overflow and underflow, triangular wave overflow and underflow */
#define TMR6_VALID_PERIOD_CNT_COND_BOTH        (TMR6_VPERR_PCNTE_0 | TMR6_VPERR_PCNTE_1)
/**
 * @}
 */

/** @defgroup TMR6_Valid_Period_Count_Define TMR6 valid period function count define
 * @{
 */
/* Valid period count function invalid */
#define TMR6_VALID_PERIOD_CNT_INVALID          (0x00000000UL)
/* Interrupt and event valid every other 1 period */
#define TMR6_VALID_PERIOD_CNT_1                (TMR6_VPERR_PCNTS_0)
/* Interrupt and event valid every other 2 period */
#define TMR6_VALID_PERIOD_CNT_2                (TMR6_VPERR_PCNTS_1)
/* Interrupt and event valid every other 3 period */
#define TMR6_VALID_PERIOD_CNT_3                (TMR6_VPERR_PCNTS_0 | TMR6_VPERR_PCNTS_1)
/* Interrupt and event valid every other 4 period */
#define TMR6_VALID_PERIOD_CNT_4                (TMR6_VPERR_PCNTS_2)
/* Interrupt and event valid every other 5 period */
#define TMR6_VALID_PERIOD_CNT_5                (TMR6_VPERR_PCNTS_2 | TMR6_VPERR_PCNTS_0)
/* Interrupt and event valid every other 6 period */
#define TMR6_VALID_PERIOD_CNT_6                (TMR6_VPERR_PCNTS_2 | TMR6_VPERR_PCNTS_1)
/* Interrupt and event valid every other 7 period */
#define TMR6_VALID_PERIOD_CNT_7                (TMR6_VPERR_PCNTS_2 | TMR6_VPERR_PCNTS_1 | TMR6_VPERR_PCNTS_0)
/**
 * @}
 */

/** @defgroup TMR6_Valid_Period_CHA_STAT_Define TMR6 valid period function channel A status define
 * @{
 */
#define TMR6_VALID_PERIOD_FUNC_CHA_OFF         (0x00000000UL)
#define TMR6_VALID_PERIOD_FUNC_CHA_ON          (TMR6_VPERR_SPPERIA)
/**
 * @}
 */

/** @defgroup TMR6_Valid_Period_CHB_STAT_Define TMR6 valid period function channel B status define
 * @{
 */
#define TMR6_VALID_PERIOD_FUNC_CHB_OFF         (0x00000000UL)
#define TMR6_VALID_PERIOD_FUNC_CHB_ON          (TMR6_VPERR_SPPERIB)
/**
 * @}
 */

/** @defgroup TMR6_DeadTime_Reg_Define TMR6 dead time register define
 * @{
 */
/* Register DTUAR */
#define TMR6_DEADTIME_REG_UP_A                 (0x00U)
/* Register DTDAR */
#define TMR6_DEADTIME_REG_DOWN_A               (0x01U)
/* Register DTUBR */
#define TMR6_DEADTIME_REG_UP_B                 (0x02U)
/* Register DTDBR */
#define TMR6_DEADTIME_REG_DOWN_B               (0x03U)
/**
 * @}
 */

/** @defgroup TMR6_Port_Define TMR6 input and output port define
 * @{
 */
/* port TIM6_<t>_PWMA */
#define TMR6_IO_PWMA                            (0x00U)
/* port TIM6_<t>_PWMB */
#define TMR6_IO_PWMB                            (0x01U)
/* Input port TIM6_TRIGA */
#define TMR6_INPUT_TRIGA                        (0x02U)
/* Input port TIM6_TRIGB */
#define TMR6_INPUT_TRIGB                        (0x03U)
/* Input port TIM6_TRIGC */
#define TMR6_INPUT_TRIGC                        (0x04U)
/* Input port TIM6_TRIGD */
#define TMR6_INPUT_TRIGD                        (0x05U)
/**
 * @}
 */

/** @defgroup TMR6_Input_Port_Filter_Clk TMR6 input port define
 * @{
 */
#define TMR6_INPUT_FILTER_PCLK0_DIV1            (0x00U)
#define TMR6_INPUT_FILTER_PCLK0_DIV4            (0x01U)
#define TMR6_INPUT_FILTER_PCLK0_DIV16           (0x02U)
#define TMR6_INPUT_FILTER_PCLK0_DIV64           (0x03U)
/**
 * @}
 */

/** @defgroup TMR6_Port_Mode_Func TMR6 port function mode selection
 * @{
 */
#define TMR6_PORT_COMPARE_OUTPUT                 (0x00U)
#define TMR6_PORT_CAPTURE_INPUT                  (TMR6_PCNAR_CAPMDA)
/**
 * @}
 */

/** @defgroup TMR6_Port_Input_Filter_Sta TMR6 port input filter function status
 * @{
 */
#define TMR6_PORT_INPUT_FILTER_OFF               (0x00U)
#define TMR6_PORT_INPUT_FILTER_ON                (0x01U)
/**
 * @}
 */

/** @defgroup TMR6_Port_Output_Sta TMR6 port output status
 * @{
 */
#define TMR6_PORT_OUTPUT_STA_LOW                 (0x00U)
#define TMR6_PORT_OUTPUT_STA_HIGH                (0x01U)
#define TMR6_PORT_OUTPUT_STA_HOLD                (0x02U)
#define TMR6_PORT_OUTPUT_STA_REVERSE             (0x03U)
/**
 * @}
 */

/** @defgroup TMR6_Force_Port_Output_Sta TMR6 force port output status next period
 * @{
 */
#define TMR6_FORCE_PORT_OUTPUT_INVALID          (0x00U)
#define TMR6_FORCE_PORT_OUTPUT_STA_LOW          (0x02U)
#define TMR6_FORCE_PORT_OUTPUT_STA_HIGH         (0x03U)
/**
 * @}
 */

/** @defgroup TMR6_Emb_channel TMR6 EMB event valid channel
 * @{
 */
#define TMR6_EMB_EVENT_VALID_CH0            (0x00U)
#define TMR6_EMB_EVENT_VALID_CH1            (TMR6_PCNAR_EMBSA_0)
#define TMR6_EMB_EVENT_VALID_CH2            (TMR6_PCNAR_EMBSA_1)
#define TMR6_EMB_EVENT_VALID_CH3            (TMR6_PCNAR_EMBSA_0 | TMR6_PCNAR_EMBSA_1)
/**
 * @}
 */

/** @defgroup TMR6_Emb_Release_Mode TMR6 EMB function release mode when EMB event invalid
 * @{
 */
#define TMR6_EMB_RELEASE_IMMEDIATE           (0x00U)
#define TMR6_EMB_RELEASE_OVERFLOW            (TMR6_PCNAR_EMBRA_0)
#define TMR6_EMB_RELEASE_UNDERFLOW           (TMR6_PCNAR_EMBRA_1)
#define TMR6_EMB_RELEASE_OVERFLOW_UNDERFLOW  (TMR6_PCNAR_EMBRA_0 | TMR6_PCNAR_EMBRA_1)
/**
 * @}
 */

/** @defgroup TMR6_Emb_Port_Sta TMR6 EMB port output status when EMB event valid
 * @{
 */
#define TMR6_EMB_PORTSTA_NORMAL              (0x00U)
#define TMR6_EMB_PORTSTA_HIZ                 (TMR6_PCNAR_EMBCA_0)
#define TMR6_EMB_PORTSTA_LOW                 (TMR6_PCNAR_EMBCA_1)
#define TMR6_EMB_PORTSTA_HIGH                (TMR6_PCNAR_EMBCA_0 | TMR6_PCNAR_EMBCA_1)
/**
 * @}
 */

/** @defgroup TMR6_Deadtime_CountUp_Buf_Func_define TMR6 Dead time buffer function for count up stage
 * @{
 */
#define TMR6_DEADTIME_CNT_UP_BUF_OFF              (0x00U)
#define TMR6_DEADTIME_CNT_UP_BUF_ON               (TMR6_DCONR_DTBENU)
/**
 * @}
 */

/** @defgroup TMR6_Deadtime_CountDown_Buf_Func_define TMR6 Dead time buffer function for count down stage
 * @{
 */
#define TMR6_DEADTIME_CNT_DOWN_BUF_OFF              (0x00U)
#define TMR6_DEADTIME_CNT_DOWN_BUF_ON               (TMR6_DCONR_DTBEND)
/**
 * @}
 */

/** @defgroup TMR6_Deadtime_Buf_Transfer_Condition_define TMR6 Dead time buffer transfer condition define for triangular count mode
 * @{
 */
#define TMR6_DEADTIME_TRANS_COND_NONE                (0x00U)
#define TMR6_DEADTIME_TRANS_COND_OVERFLOW            (TMR6_DCONR_DTBTRU)
#define TMR6_DEADTIME_TRANS_COND_UNDERFLOW           (TMR6_DCONR_DTBTRD)
#define TMR6_DEADTIME_TRANS_COND_BOTH                (TMR6_DCONR_DTBTRU | TMR6_DCONR_DTBTRD)
/**
 * @}
 */

/** @defgroup TMR6_Deadtime_Reg_Equal_Func_define TMR6 Dead time function DTDAR equal DTUAR
 * @{
 */
#define TMR6_DEADTIME_EQUAL_OFF                     (0x00U)
#define TMR6_DEADTIME_EQUAL_ON                      (TMR6_DCONR_SEPA)
/**
 * @}
 */

/** @defgroup TMR6_Soft_Sync_Ctrl_Unit_Number_define TMR6 Software synchronization start/stop/clear/update unit number define
 * @{
 */
#define TMR6_SOFT_SYNC_CTRL_U1              (TMR6_SSTAR_SSTA1)
#define TMR6_SOFT_SYNC_CTRL_U2              (TMR6_SSTAR_SSTA2)
#define TMR6_SOFT_SYNC_CTRL_U3              (TMR6_SSTAR_SSTA3)
#define TMR6_SOFT_SYNC_CTRL_U4              (TMR6_SSTAR_SSTA4)
#define TMR6_SOFT_SYNC_CTRL_U5              (TMR6_SSTAR_SSTA5)
#define TMR6_SOFT_SYNC_CTRL_U6              (TMR6_SSTAR_SSTA6)
#define TMR6_SOFT_SYNC_CTRL_U7              (TMR6_SSTAR_SSTA7)
#define TMR6_SOFT_SYNC_CTRL_U8              (TMR6_SSTAR_SSTA8)
/**
 * @}
 */

/** @defgroup TMR6_hardware_control_event_define TMR6 hardware start/stop/clear/update/capture events define
 * @{
 */
#define TMR6_HW_CTRL_PWMA_RISING             (TMR6_HSTAR_HSTA0)
#define TMR6_HW_CTRL_PWMA_FAILLING           (TMR6_HSTAR_HSTA1)
#define TMR6_HW_CTRL_PWMB_RISING             (TMR6_HSTAR_HSTA2)
#define TMR6_HW_CTRL_PWMB_FAILLING           (TMR6_HSTAR_HSTA3)
#define TMR6_HW_CTRL_INTER_EVENT0            (TMR6_HSTAR_HSTA8)
#define TMR6_HW_CTRL_INTER_EVENT1            (TMR6_HSTAR_HSTA9)
#define TMR6_HW_CTRL_INTER_EVENT2            (TMR6_HSTAR_HSTA10)
#define TMR6_HW_CTRL_INTER_EVENT3            (TMR6_HSTAR_HSTA11)
#define TMR6_HW_CTRL_TRIGEA_RISING           (TMR6_HSTAR_HSTA16)
#define TMR6_HW_CTRL_TRIGEA_FAILLING         (TMR6_HSTAR_HSTA17)
#define TMR6_HW_CTRL_TRIGEB_RISING           (TMR6_HSTAR_HSTA18)
#define TMR6_HW_CTRL_TRIGEB_FAILLING         (TMR6_HSTAR_HSTA19)
#define TMR6_HW_CTRL_TRIGEC_RISING           (TMR6_HSTAR_HSTA20)
#define TMR6_HW_CTRL_TRIGEC_FAILLING         (TMR6_HSTAR_HSTA21)
#define TMR6_HW_CTRL_TRIGED_RISING           (TMR6_HSTAR_HSTA22)
#define TMR6_HW_CTRL_TRIGED_FAILLING         (TMR6_HSTAR_HSTA23)
/**
 * @}
 */

/** @defgroup TMR6_hardware_count_event_define TMR6 hardware increase/decrease events define
 * @{
 */
#define TMR6_HW_CNT_PWMAL_PWMBRISING        (TMR6_HCUPR_HCUP0)
#define TMR6_HW_CNT_PWMAL_PWMBFAILLING      (TMR6_HCUPR_HCUP1)
#define TMR6_HW_CNT_PWMAH_PWMBRISING        (TMR6_HCUPR_HCUP2)
#define TMR6_HW_CNT_PWMAH_PWMBFAILLING      (TMR6_HCUPR_HCUP3)
#define TMR6_HW_CNT_PWMBL_PWMARISING        (TMR6_HCUPR_HCUP4)
#define TMR6_HW_CNT_PWMBL_PWMAFAILLING      (TMR6_HCUPR_HCUP5)
#define TMR6_HW_CNT_PWMBH_PWMARISING        (TMR6_HCUPR_HCUP6)
#define TMR6_HW_CNT_PWMBH_PWMAFAILLING      (TMR6_HCUPR_HCUP7)
#define TMR6_HW_CNT_INTER_EVENT0            (TMR6_HCUPR_HCUP8)
#define TMR6_HW_CNT_INTER_EVENT1            (TMR6_HCUPR_HCUP9)
#define TMR6_HW_CNT_INTER_EVENT2            (TMR6_HCUPR_HCUP10)
#define TMR6_HW_CNT_INTER_EVENT3            (TMR6_HCUPR_HCUP11)
#define TMR6_HW_CNT_TRIGEA_RISING           (TMR6_HCUPR_HCUP16)
#define TMR6_HW_CNT_TRIGEA_FAILLING         (TMR6_HCUPR_HCUP17)
#define TMR6_HW_CNT_TRIGEB_RISING           (TMR6_HCUPR_HCUP18)
#define TMR6_HW_CNT_TRIGEB_FAILLING         (TMR6_HCUPR_HCUP19)
#define TMR6_HW_CNT_TRIGEC_RISING           (TMR6_HCUPR_HCUP20)
#define TMR6_HW_CNT_TRIGEC_FAILLING         (TMR6_HCUPR_HCUP21)
#define TMR6_HW_CNT_TRIGED_RISING           (TMR6_HCUPR_HCUP22)
#define TMR6_HW_CNT_TRIGED_FAILLING         (TMR6_HCUPR_HCUP23)
/**
 * @}
 */

/** @defgroup TMR6_Count_Direction_define TMR6 base counter function direction define
 * @{
 */
#define TMR6_CNT_INCREASE                   (TMR6_GCONR_DIR)
#define TMR6_CNT_DECREASE                   (0x00U)
/**
 * @}
 */

/** @defgroup TMR6_Count_Mode_define TMR6 base counter function mode define
 * @{
 */
#define TMR6_MODE_SAWTOOTH                   (0x00U)
#define TMR6_MODE_TRIANGLE                   (TMR6_GCONR_MODE)
/**
 * @}
 */

/** @defgroup TMR6_Count_Clock_define TMR6 base counter clock source define
 * @{
 */
#define TMR6_CLK_PCLK0_DIV1                  (0x00UL)
#define TMR6_CLK_PCLK0_DIV2                  (0x01UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_PCLK0_DIV4                  (0x02UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_PCLK0_DIV8                  (0x03UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_PCLK0_DIV16                 (0x04UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_PCLK0_DIV32                 (0x05UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_PCLK0_DIV64                 (0x06UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_PCLK0_DIV128                (0x07UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_PCLK0_DIV256                (0x08UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_PCLK0_DIV512                (0x09UL << TMR6_GCONR_CKDIV_POS)
#define TMR6_CLK_PCLK0_DIV1024               (0x0AUL << TMR6_GCONR_CKDIV_POS)
/**
 * @}
 */

/** @defgroup TMR6_Count_Stop_After_Overflow_define TMR6 count stop after overflow function define
 * @{
 */
#define TMR6_CNT_CONTINUOUS                   (0x00U)
#define TMR6_STOP_AFTER_OVF                   (TMR6_GCONR_OVSTP)
/**
 * @}
 */

/** @defgroup TMR6_Zmask_Cycle_define TMR6 Z Mask input function mask cycles number define
 * @{
 */
#define TMR6_ZMASK_CYCLE_FUNC_INVALID         (0x00U)
#define TMR6_ZMASK_CYCLE_4                    (TMR6_GCONR_ZMSKVAL_0)
#define TMR6_ZMASK_CYCLE_8                    (TMR6_GCONR_ZMSKVAL_1)
#define TMR6_ZMASK_CYCLE_16                   (TMR6_GCONR_ZMSKVAL_0 | TMR6_GCONR_ZMSKVAL_1)
/**
 * @}
 */

/** @defgroup TMR6_Zmask_Position_Unit_Clear_Func_define TMR6 unit as position timer, z phase input mask function define for clear action
 * @{
 */
#define TMR6_POS_CLR_ZMASK_FUNC_INVALID       (0x00U)
#define TMR6_POS_CLR_ZMASK_FUNC_VALID         (TMR6_GCONR_ZMSKPOS)
/**
 * @}
 */

/** @defgroup TMR6_Zmask_Revolution_Unit_Count_Func_define TMR6 unit as revolution timer, z phase input mask function define for count action
 * @{
 */
#define TMR6_REVO_CNT_ZMASK_FUNC_INVALID       (0x00U)
#define TMR6_REVO_CNT_ZMASK_FUNC_VALID         (TMR6_GCONR_ZMSKREV)
/**
 * @}
 */

/** @defgroup TMR6_Hardware_Trigger_Index_define TMR6 hardware trigger index define
 * @{
 */
#define TMR6_HW_TRIG_0                         (0x00U)
#define TMR6_HW_TRIG_1                         (0x01U)
#define TMR6_HW_TRIG_2                         (0x02U)
#define TMR6_HW_TRIG_3                         (0x03U)
/**
 * @}
 */

/** @defgroup TMR6_Common_Trigger_Source_Cfg_define TMR6 common Trigger Source Config
 * @{
 */
#define TMR6_COM_TRIG1                         (AOS_TMR6_HTSSR_COMTRG_EN_0)
#define TMR6_COM_TRIG2                         (AOS_TMR6_HTSSR_COMTRG_EN_1)
#define TMR6_COM_TRIG_MASK                     (AOS_TMR6_HTSSR_COMTRG_EN)
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
 * @retval An uint32_t data indicate the read status.
 */
__STATIC_INLINE uint32_t TMR6_GetSwSyncStaState(void)
{
    return READ_REG32(M4_TMR6_1->SSTAR);
}

/* TMR6 interrupt request enable or disable */
void TMR6_IntCmd(M4_TMR6_TypeDef *TMR6x, uint32_t u32Tmr6Irq, en_functional_state_t enNewState);
/* Get Timer6 status flag */
en_flag_status_t TMR6_GetSta(const M4_TMR6_TypeDef *TMR6x, uint32_t u32StaBit);
/* Get Timer6 period number when valid period function enable */
uint32_t TMR6_GetPeriodNum(const M4_TMR6_TypeDef *TMR6x);
/* De-initialize the timer6 unit */
void TMR6_DeInit(M4_TMR6_TypeDef *TMR6x);
/* Initialize the timer6 unit */
en_result_t TMR6_Init(M4_TMR6_TypeDef *TMR6x, const stc_tmr6_basecnt_cfg_t* pstcTmr6BaseCntCfg);
/* Timer6 counter function command */
void TMR6_CountCmd(M4_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState);

/* Timer6 counter register set */
void TMR6_SetCntReg(M4_TMR6_TypeDef *TMR6x, uint32_t u32Value);
/* Timer6 update register set */
void TMR6_SetUpdateReg(M4_TMR6_TypeDef *TMR6x, uint32_t u32Value);
/* Timer6 set period register(A~C) */
void TMR6_SetPeriodReg(M4_TMR6_TypeDef *TMR6x, uint32_t u32PeriodReg, uint32_t u32PeriodVal);
/* Timer6 set general compare register(A~F) */
void TMR6_SetGenCmpReg(M4_TMR6_TypeDef *TMR6x, uint32_t u32GenCmpReg, uint32_t u32CmpVal);
/* Timer6 set special compare register(A~F) */
void TMR6_SetSpecialCmpReg(M4_TMR6_TypeDef *TMR6x, uint32_t u32SpecialCmpReg, uint32_t u32CmpVal);
/* Timer6 set dead time registerr */
void TMR6_SetDeadTimeReg(M4_TMR6_TypeDef *TMR6x, uint32_t u32DeadTimeReg, uint32_t u32CmpVal);

/* Timer6 get counter register value */
uint32_t TMR6_GetCntReg(const M4_TMR6_TypeDef *TMR6x);
/* Timer6 get update register value */
uint32_t TMR6_GetUpdateReg(const M4_TMR6_TypeDef *TMR6x);
/* Timer6 Get period register(A~C) */
uint32_t TMR6_GetPeriodReg(const M4_TMR6_TypeDef *TMR6x, uint32_t u32PeriodReg);
/* Timer6 get general compare registers value(A~F) */
uint32_t TMR6_GetGenCmpReg(const M4_TMR6_TypeDef *TMR6x, uint32_t u32GenCmpReg);
/* Timer6 get special compare registers value(A~F) */
uint32_t TMR6_GetSpecialCmpReg(const M4_TMR6_TypeDef *TMR6x, uint32_t u32SpecialCmpReg);
/* Timer6 get dead time register */
uint32_t TMR6_GetDeadTimeReg(const M4_TMR6_TypeDef *TMR6x, uint32_t u32DeadTimeReg);

/* Timer6 general compare buffer function configuration */
en_result_t TMR6_GenCmpBufCfg(M4_TMR6_TypeDef *TMR6x, uint32_t u32CmpChIdx, const stc_tmr6_buf_func_cfg_t* pstcGenBufCfg);
/* Timer6 special compare buffer function configuration */
en_result_t TMR6_SpecialCmpBufCfg(M4_TMR6_TypeDef *TMR6x, uint32_t u32CmpChIdx, const stc_tmr6_buf_func_cfg_t* pstcSpecialBufCfg);
/* Timer6 period buffer function configuration */
en_result_t TMR6_PeriodBufCfg(M4_TMR6_TypeDef *TMR6x, const stc_tmr6_buf_func_cfg_t* pstcPeriodBufCfg);

/* Timer6 valid period function configuration for special compare function */
en_result_t TMR6_ValidPeriodCfg(M4_TMR6_TypeDef *TMR6x, const stc_tmr6_valid_period_func_cfg_t* pstcValidPeriodCfg);
/* Port input configuration(Trig) */
en_result_t TMR6_PortInputConfig(M4_TMR6_TypeDef *TMR6x,
                                    uint32_t u32PortSel,
                                    const stc_tmr6_port_input_cfg_t* pstcTmr6PortInputCfg);
/* Port output configuration(Trig) */
en_result_t TMR6_PortOutputConfig(M4_TMR6_TypeDef *TMR6x,
                                    uint32_t u32PortSel,
                                    const stc_tmr6_port_output_cfg_t* pstcTmr6PortOutputCfg);
/* EMB function configuration */
en_result_t TMR6_EMBConfig(M4_TMR6_TypeDef *TMR6x,
                                    uint32_t u32PortSel,
                                    const stc_tmr6_emb_cfg_t* pstcTmr6EmbCfg);

/* Timer6 dead time function command */
void TMR6_DeadTimeFuncCmd(M4_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState);
/* DeadTime function configuration */
en_result_t TMR6_DeadTimeCfg(M4_TMR6_TypeDef *TMR6x, const stc_tmr6_deadtime_cfg_t* pstcTmr6DTCfg);

/* Timer6 unit Z phase input mask config */
en_result_t TMR6_ZMaskCfg(M4_TMR6_TypeDef *TMR6x, const stc_tmr6_zmask_cfg_t* pstcTmr6ZMaskCfg);

/* Software Sync Start */
void TMR6_SwSyncStart(uint32_t u32UnitCombine);
/* Software Sync Stop */
void TMR6_SwSyncStop(uint32_t u32UnitCombine);
/* Software Sync clear */
void TMR6_SwSyncClr(uint32_t u32UnitCombine);
/* Software Sync update */
void TMR6_SwSyncUpdate(uint32_t u32UnitCombine);

/* Hardware start function command */
void TMR6_HwStartFuncCmd(M4_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState);
/* Hardware stop function command */
void TMR6_HwStopFuncCmd(M4_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState);
/* Hardware clear function command */
void TMR6_HwClrFuncCmd(M4_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState);
/* Hardware update function command */
void TMR6_HwUpdateFuncCmd(M4_TMR6_TypeDef *TMR6x, en_functional_state_t enNewState);

/* Hardware start condtion command */
void TMR6_HwStartCondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState);
/* Hardware stop condtion command */
void TMR6_HwStopCondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState);
/* Hardware clear condtion command */
void TMR6_HwClrCondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState);
/* Hardware update condtion command */
void TMR6_HwUpdCondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState);
/* Hardware capture condtion command for channel A */
void TMR6_HwCaptureChACondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState);
/* Hardware capture condtion command for channel B */
void TMR6_HwCaptureChBCondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState);
/* Hardware increase conditon command */
void TMR6_HwIncreaseCondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState);
/* Hardware decrease conditon command */
void TMR6_HwDecreaseCondCmd(M4_TMR6_TypeDef *TMR6x,
                            uint32_t u32CondSrc,
                            en_functional_state_t enNewState);

/* Hardware start function condition clear */
void TMR6_HwStartCondClr(M4_TMR6_TypeDef *TMR6x);
/* Hardware stop function condition clear */
void TMR6_HwStopCondClr(M4_TMR6_TypeDef *TMR6x);
/* Hardware clear function condition clear */
void TMR6_HwClrCondClr(M4_TMR6_TypeDef *TMR6x);
/* Hardware update function condition clear */
void TMR6_HwUpdCondClr(M4_TMR6_TypeDef *TMR6x);
/* Hardware capture condition clear for channel A */
void TMR6_HwCaptureChACondClr(M4_TMR6_TypeDef *TMR6x);
/* Hardware capture condition clear for channel B */
void TMR6_HwCaptureChBCondClr(M4_TMR6_TypeDef *TMR6x);
/* Hardware increase condition clear */
void TMR6_HwIncreaseCondClr(M4_TMR6_TypeDef *TMR6x);
/* Hardware decrease condition clear */
void TMR6_HwDecreaseCondClr(M4_TMR6_TypeDef *TMR6x);

/* Timer6 Hardware trigger event configuration for(trigger0~trigger3) */
void TMR6_SetTriggerSrc(uint32_t u32TrigIndex, en_event_src_t enEvent);
/* Timer6 Hardware trigger common event function command for(trigger0~trigger3) */
void TMR6_ComTriggerCmd(uint32_t u32TrigIndex, uint32_t u32ComTrig, en_functional_state_t enNewState);

/* Set the fields of structure stc_timer4_pwm_init_t to default values */
en_result_t TMR6_BaseCntStructInit(stc_tmr6_basecnt_cfg_t *pstcInit);
/* Set the fields of structure stc_tmr6_buf_func_cfg_t to default values */
en_result_t TMR6_BufFuncStructInit(stc_tmr6_buf_func_cfg_t *pstcInit);
/* Set the fields of structure stc_tmr6_valid_period_func_cfg_t to default values */
en_result_t TMR6_ValidPeriodStructInit(stc_tmr6_valid_period_func_cfg_t *pstcInit);
/* Set the fields of structure stc_tmr6_port_input_cfg_t to default values */
en_result_t TMR6_PortInputStructInit(stc_tmr6_port_input_cfg_t *pstcInit);
/* Set the fields of structure stc_tmr6_port_output_cfg_t to default values */
en_result_t TMR6_PortOutputStructInit(stc_tmr6_port_output_cfg_t *pstcInit);
/* Set the fields of structure stc_tmr6_emb_cfg_t to default values */
en_result_t TMR6_EMBCfgStructInit(stc_tmr6_emb_cfg_t *pstcInit);
/* Set the fields of structure stc_tmr6_deadtime_cfg_t to default values */
en_result_t TMR6_DeadTimeCfgStructInit(stc_tmr6_deadtime_cfg_t *pstcInit);
/* Set the fields of structure stc_tmr6_zmask_cfg_t to default values */
en_result_t TMR6_ZMaskCfgStructInit(stc_tmr6_zmask_cfg_t *pstcInit);

/**
 * @}
 */

#endif /* DDL_TMR6_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_TMR6_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
