/**
 *******************************************************************************
 * @file  hc32_ll_dcu.h
 * @brief This file contains all the functions prototypes of the DCU(Data
 *        Computing Unit) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-06-30       CDT             Modify macro group comments: DCU_Interrupt_Type
   2023-06-30       CDT             Modify typo
                                    Delete macro definition: DCU_INT_SAWTOOTH_WAVE_RELOAD
                                    Modify macro-definition according to RM:DCU_CTL_COMP_TRG->DCU_CTL_COMPTRG
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
#ifndef __HC32_LL_DCU_H__
#define __HC32_LL_DCU_H__

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
 * @addtogroup LL_DCU
 * @{
 */

#if (LL_DCU_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup DCU_Global_Types DCU Global Types
 * @{
 */

/**
 * @brief DCU initialization structure definition
 */
typedef struct {
    uint32_t u32Mode;         /*!< Specifies DCU operation.
                                   This parameter can be a value of @ref DCU_Mode */
    uint32_t u32DataWidth;    /*!< Specifies DCU data width.
                                   This parameter can be a value of @ref DCU_Data_Width */
} stc_dcu_init_t;

/**
 * @brief DCU wave output configure structure definition
 */
typedef struct {
    uint32_t u32LowerLimit;   /*!< Defines the wave lower limit of the wave amplitude.
                                   This parameter can be a value between Min_Data = 0 and Max_Data = 0xFFF */
    uint32_t u32UpperLimit;   /*!< Defines the upper limit of the wave amplitude.
                                   This parameter can be a value between Min_Data = 0 and Max_Data = 0xFFF */
    uint32_t u32Step;         /*!< Defines the increasing/decreasing step.
                                   This parameter can be a value between Min_Data = 0 and Max_Data = 0xFFF */
} stc_dcu_wave_config_t;
/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DCU_Global_Macros DCU Global Macros
 * @{
 */

/**
 * @defgroup DCU_Data_Width DCU Data Width
 * @{
 */
#define DCU_DATA_WIDTH_8BIT                 (0UL)                   /*!< DCU data width: 8 bit */
#define DCU_DATA_WIDTH_16BIT                (DCU_CTL_DATASIZE_0)    /*!< DCU data width: 16 bit */
#define DCU_DATA_WIDTH_32BIT                (DCU_CTL_DATASIZE_1)    /*!< DCU data width: 32 bit */
/**
 * @}
 */

/**
 * @defgroup DCU_Compare_Trigger_Condition DCU Compare Trigger Condition
 * @{
 */
#define DCU_CMP_TRIG_DATA0                  (0UL)               /*!< DCU compare triggered by DATA0 */
#define DCU_CMP_TRIG_DATA0_DATA1_DATA2      (DCU_CTL_COMPTRG)   /*!< DCU compare triggered by DATA0 or DATA1 or DATA2 */
/**
 * @}
 */

/**
 * @defgroup DCU_Mode DCU Mode
 * @{
 */
#define DCU_MD_INVD                         (0UL)   /*!< DCU invalid */
#define DCU_MD_ADD                          (1UL)   /*!< DCU add operation */
#define DCU_MD_SUB                          (2UL)   /*!< DCU sub operation */
#define DCU_MD_HW_ADD                       (3UL)   /*!< DCU hardware trigger add */
#define DCU_MD_HW_SUB                       (4UL)   /*!< DCU hardware trigger sub */
#define DCU_MD_CMP                          (5UL)   /*!< DCU compare */
#define DCU_MD_TRIANGLE_WAVE                (8UL)   /*!< DCU triangle wave output mode */
#define DCU_MD_SAWTOOTH_WAVE_INC            (9UL)   /*!< DCU increasing sawtooth wave output mode */
#define DCU_MD_SAWTOOTH_WAVE_DEC            (10UL)  /*!< DCU decreasing sawtooth wave output mode */
/**
 * @}
 */

/**
 * @defgroup DCU_Flag DCU Flag
 * @{
 */
#define DCU_FLAG_CARRY                      (DCU_FLAG_FLAG_OP)  /*!< DCU addition overflow or subtraction underflow flag */
#define DCU_FLAG_DATA0_LT_DATA2             (DCU_FLAG_FLAG_LS2) /*!< DCU DATA0 < DATA2 flag */
#define DCU_FLAG_DATA0_EQ_DATA2             (DCU_FLAG_FLAG_EQ2) /*!< DCU DATA0 = DATA2 flag */
#define DCU_FLAG_DATA0_GT_DATA2             (DCU_FLAG_FLAG_GT2) /*!< DCU DATA0 > DATA2 flag */
#define DCU_FLAG_DATA0_LT_DATA1             (DCU_FLAG_FLAG_LS1) /*!< DCU DATA0 < DATA1 flag */
#define DCU_FLAG_DATA0_EQ_DATA1             (DCU_FLAG_FLAG_EQ1) /*!< DCU DATA0 = DATA1 flag */
#define DCU_FLAG_DATA0_GT_DATA1             (DCU_FLAG_FLAG_GT1) /*!< DCU DATA0 > DATA1 flag */
#define DCU_FLAG_SAWTOOTH_WAVE_RELOAD       (DCU_FLAG_FLAG_RLD) /*!< DCU sawtooth wave mode reload interrupt */
#define DCU_FLAG_TRIANGLE_WAVE_BOTTOM       (DCU_FLAG_FLAG_BTM) /*!< DCU triangle wave mode bottom interrupt */
#define DCU_FLAG_TRIANGLE_WAVE_TOP          (DCU_FLAG_FLAG_TOP) /*!< DCU triangle wave mode top interrupt */

#define DCU_FLAG_ALL                        (0x00000E7FUL)
/**
 * @}
 */

/**
 * @defgroup DCU_Category DCU Category
 * @{
 */
#define DCU_CATEGORY_OP                     (0UL)   /*!< DCU operation result(overflow/underflow) */
#define DCU_CATEGORY_CMP_WIN                (1UL)   /*!< DCU comparison(window) */
#define DCU_CATEGORY_CMP_NON_WIN            (2UL)   /*!< DCU comparison(non-window) */
#define DCU_CATEGORY_WAVE                   (3UL)   /*!< DCU wave mode(sawtooth/triangle wave) */
/**
 * @}
 */

/**
 * @defgroup DCU_Interrupt_Type DCU Interrupt Type
 * @{
 */
/**
 * @defgroup DCU_Compare_Interrupt DCU Compare(Non-window) Interrupt
 * @note Interrupt type DCU_Compare_Interrupt is valid when only select DCU_CATEGORY_CMP_NON_WIN
 * @{
 */
#define DCU_INT_CMP_DATA0_LT_DATA2          (DCU_INTEVTSEL_SEL_LS2)   /*!< DCU DATA0 < DATA2 interrupt */
#define DCU_INT_CMP_DATA0_EQ_DATA2          (DCU_INTEVTSEL_SEL_EQ2)   /*!< DCU DATA0 = DATA2 interrupt */
#define DCU_INT_CMP_DATA0_GT_DATA2          (DCU_INTEVTSEL_SEL_GT2)   /*!< DCU DATA0 > DATA2 interrupt */
#define DCU_INT_CMP_DATA0_LT_DATA1          (DCU_INTEVTSEL_SEL_LS1)   /*!< DCU DATA0 < DATA1 interrupt */
#define DCU_INT_CMP_DATA0_EQ_DATA1          (DCU_INTEVTSEL_SEL_EQ1)   /*!< DCU DATA0 = DATA1 interrupt */
#define DCU_INT_CMP_DATA0_GT_DATA1          (DCU_INTEVTSEL_SEL_GT1)   /*!< DCU DATA0 > DATA1 interrupt */
#define DCU_INT_CMP_NON_WIN_ALL             (DCU_INT_CMP_DATA0_LT_DATA2 |  \
                                             DCU_INT_CMP_DATA0_EQ_DATA2 |  \
                                             DCU_INT_CMP_DATA0_GT_DATA2 |  \
                                             DCU_INT_CMP_DATA0_LT_DATA1 |  \
                                             DCU_INT_CMP_DATA0_EQ_DATA1 |  \
                                             DCU_INT_CMP_DATA0_GT_DATA1)
/**
 * @}
 */

/**
 * @defgroup DCU_Window_Compare_Interrupt DCU Window Compare Interrupt
 * @note Interrupt type DCU_Window_Compare_Interrupt is valid when only select DCU_CATEGORY_CMP_WIN
 * @{
 */
#define DCU_INT_CMP_WIN_INSIDE              (DCU_INTEVTSEL_SEL_WIN_0)  /*!< DCU comparison(DATA2 <= DATA0 <= DATA1) interrupt */
#define DCU_INT_CMP_WIN_OUTSIDE             (DCU_INTEVTSEL_SEL_WIN_1)  /*!< DCU comparison(DATA0 < DATA2 & DATA0 > DATA1 ) interrupt */
#define DCU_INT_CMP_WIN_ALL                 (DCU_INT_CMP_WIN_INSIDE | DCU_INT_CMP_WIN_OUTSIDE)
/**
 * @}
 */

/**
 * @defgroup DCU_Operation_Interrupt DCU Operation Interrupt
 * @note DCU_Window_Compare_Interrupt selection is valid when only select DCU_CATEGORY_OP
 * @{
 */
#define DCU_INT_OP_CARRY                    (DCU_INTEVTSEL_SEL_OP) /*!< DCU addition overflow or subtraction underflow interrupt */
/**
 * @}
 */

/**
 * @defgroup DCU_Wave_Mode_Interrupt DCU Wave Mode Interrupt
 * @note Interrupt type DCU_Wave_Mode_Interrupt is valid when only select DCU_CATEGORY_WAVE
 * @{
 */
#define DCU_INT_TRIANGLE_WAVE_BOTTOM        (DCU_INTEVTSEL_SEL_BTM) /*!< DCU triangle wave mode bottom interrupt */
#define DCU_INT_TRIANGLE_WAVE_TOP           (DCU_INTEVTSEL_SEL_TOP) /*!< DCU triangle wave mode top interrupt */
#define DCU_INT_WAVE_MD_ALL                 (DCU_INT_TRIANGLE_WAVE_TOP    | \
                                             DCU_INT_TRIANGLE_WAVE_BOTTOM)
/**
 * @}
 */
/**
 * @}
 */

/**
 * @defgroup DCU_Data_Register_Index DCU Data Register Index
 * @{
 */
#define DCU_DATA0_IDX                       (0UL)   /*!< DCU DATA0 */
#define DCU_DATA1_IDX                       (1UL)   /*!< DCU DATA1 */
#define DCU_DATA2_IDX                       (2UL)   /*!< DCU DATA2 */
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
 * @addtogroup DCU_Global_Functions
 * @{
 */

/* Initialization and configuration functions */
int32_t DCU_Init(CM_DCU_TypeDef *DCUx, const stc_dcu_init_t *pstcDcuInit);
int32_t DCU_StructInit(stc_dcu_init_t *pstcDcuInit);
int32_t DCU_DeInit(CM_DCU_TypeDef *DCUx);

int32_t DCU_WaveConfig(CM_DCU_TypeDef *DCUx, const stc_dcu_wave_config_t *pstcWaveConfig);

void DCU_SetMode(CM_DCU_TypeDef *DCUx, uint32_t u32Mode);
void DCU_SetDataWidth(CM_DCU_TypeDef *DCUx, uint32_t u32DataWidth);
void DCU_SetCompareCond(CM_DCU_TypeDef *DCUx, uint32_t u32Cond);

/* Interrupt and flag management functions */
en_flag_status_t DCU_GetStatus(const CM_DCU_TypeDef *DCUx, uint32_t u32Flag);
void DCU_ClearStatus(CM_DCU_TypeDef *DCUx, uint32_t u32Flag);
void DCU_GlobalIntCmd(CM_DCU_TypeDef *DCUx, en_functional_state_t enNewState);
void DCU_IntCmd(CM_DCU_TypeDef *DCUx, uint32_t u32IntCategory, uint32_t u32IntType, en_functional_state_t enNewState);

/* Read and write functions */
uint8_t DCU_ReadData8(const CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex);
void DCU_WriteData8(CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex, uint8_t u8Data);
uint16_t DCU_ReadData16(const CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex);
void DCU_WriteData16(CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex, uint16_t u16Data);
uint32_t DCU_ReadData32(const CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex);
void DCU_WriteData32(CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex, uint32_t u32Data);

/**
 * @}
 */

#endif /* LL_DCU_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_DCU_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
