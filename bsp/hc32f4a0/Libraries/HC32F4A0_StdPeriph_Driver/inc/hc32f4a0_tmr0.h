/**
 *******************************************************************************
 * @file  hc32f4a0_tmr0.h
 * @brief This file contains all the functions prototypes of the TMR0 driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Heqb          First version
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
#ifndef __HC32F4A0_TMR0_H__
#define __HC32F4A0_TMR0_H__

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
 * @addtogroup DDL_TMR0
 * @{
 */

#if (DDL_TMR0_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMR0_Global_Types TMR0 Global Types
 * @{
 */

/**
 * @brief Tmr0 base counter function init structrue definition
 */
typedef struct
{
    uint32_t       u32ClockDivision;  /*!< Specifies the TMR0 clock division,
                                         and this parameter can be a value of
                                         @ref TMR0_Clock_Division_define */

    uint32_t       u32ClockSource;    /*!< Specifies the TMR0 clock source,
                                         and this parameter can be a value of
                                         @ref TMR0_Clock_Source_define*/

    uint32_t       u32Tmr0Func;       /*!< Specifies the TMR0 function,
                                         compare output or capture input
                                         @ref TMR0_Function_define */

    uint32_t       u32HwTrigFunc;     /*!< Specifies the TMR0 compare
                                         function hardware trigger function, and
                                         this parameter can be a value of @ref
                                         TMR0_HardwareTrigger_Func_define */

    uint16_t       u16CmpValue;       /*!< Specifies the TMR0 compare value
                                         This value can be set 0-0xFFFF */

    uint16_t       u16CntValue;       /*!< Specifies the TMR0 count value
                                         This value can be set 0-0xFFFF */
}stc_tmr0_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR0_Global_Macros TMR0 Global Macros
 * @{
 */

/** @defgroup TMR0_Clock_Division_define TMR0 clock division define
 * @{
 */
#define TMR0_CLK_DIV1                (0UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV2                (1UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV4                (2UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV8                (3UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV16               (4UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV32               (5UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV64               (6UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV128              (7UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV256              (8UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV512              (9UL<<TMR0_BCONR_CKDIVA_POS)
#define TMR0_CLK_DIV1024             (10UL<<TMR0_BCONR_CKDIVA_POS)
/**
 * @}
 */

/**
 * @defgroup TMR0_Channel_Index TMR0 Channel Index
 * @{
 */
#define TMR0_CH_A                    (0U)
#define TMR0_CH_B                    (1U)
/**
 * @}
 */

/** @defgroup TMR0_Clock_Source_define TMR0 clock source define
 * @{
 */
#define TMR0_CLK_SRC_PCLK1           (0x00000000UL)
#define TMR0_CLK_SRC_INTHWTRIG       (TMR0_BCONR_SYNCLKA)
#define TMR0_CLK_SRC_LRC             (TMR0_BCONR_SYNSA)
#define TMR0_CLK_SRC_XTAL32          (TMR0_BCONR_ASYNCLKA | TMR0_BCONR_SYNSA)
/**
 * @}
 */

/** @defgroup TMR0_Function_define TMR0 Function define
 * @{
 */
#define TMR0_FUNC_CMP                (0x00000000UL)
#define TMR0_FUNC_CAP                (TMR0_BCONR_CAPMDA | TMR0_BCONR_HICPA)
/**
 * @}
 */

/** @defgroup TMR0_HardwareTrigger_Func_define TMR0 hardware trigger function define
 * @{
 */
#define TMR0_BT_HWTRG_FUNC_START     (TMR0_BCONR_HSTAA)
#define TMR0_BT_HWTRG_FUNC_CLEAR     (TMR0_BCONR_HCLEA)
#define TMR0_BT_HWTRG_FUNC_STOP      (TMR0_BCONR_HSTPA)
#define TMR0_BT_HWTRG_FUNC_NONE      (0x00000000UL)
#define TMR0_BT_HETRG_FUNC_MASK      (TMR0_BT_HWTRG_FUNC_START | \
                                      TMR0_BT_HWTRG_FUNC_CLEAR | \
                                      TMR0_BT_HWTRG_FUNC_STOP)
/**
 * @}
 */

/**
 * @defgroup TMR0_CAMPAR_FLAG TMR0 Compare Status
 * @{
 */
#define TMR0_FLAG_CMP_A             (TMR0_STFLR_CMFA)
#define TMR0_FLAG_CMP_B             (TMR0_STFLR_CMFB)
/**
 * @}
 */

/**
 * @defgroup TMR0_Common_Trigger_Sel TMR0 common Trigger source select
 * @{
 */
#define TMR0_COM_TRIG1              (AOS_TMR0_HTSSR_COMTRG_EN_0)
#define TMR0_COM_TRIG2              (AOS_TMR0_HTSSR_COMTRG_EN_1)
#define TMR0_COM_TRIG_MASk          (AOS_TMR0_HTSSR_COMTRG_EN)

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
 * @addtogroup TMR0_Global_Functions
 * @{
 */
en_result_t TMR0_StructInit(stc_tmr0_init_t* pstcInitStruct);
en_result_t TMR0_Init(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, \
                      const stc_tmr0_init_t* pstcTmr0Init);
void TMR0_DeInit(M4_TMR0_TypeDef* TMR0x);
void TMR0_Cmd(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, \
              en_functional_state_t enNewState);
void TMR0_IntCmd(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, \
                 en_functional_state_t enNewState);
void TMR0_SetClkSrc(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32ClkSrc);
void TMR0_SetClkDiv(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32ClkDiv);
void TMR0_HWTrigCmd(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, \
                    uint32_t u32HWFunc, en_functional_state_t enNewState);
void TMR0_SetFunc(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32Func);
void TMR0_SetCntVal(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, uint16_t u16Value);
void TMR0_SetCmpVal(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, uint16_t u16Value);
void TMR0_ClearStatus(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel);
void TMR0_SetTriggerSrc(en_event_src_t enEvent);
void TMR0_ComTriggerCmd(uint32_t u32ComTrig, en_functional_state_t enNewState);

en_flag_status_t TMR0_GetStatus(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel);

uint16_t TMR0_GetCntVal(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel);
uint16_t TMR0_GetCmpVal(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel);


/**
 * @}
 */

#endif /* DDL_TMR0_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_TMR0_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
