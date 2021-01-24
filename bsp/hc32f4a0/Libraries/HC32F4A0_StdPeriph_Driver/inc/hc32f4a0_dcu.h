/**
 *******************************************************************************
 * @file  hc32f4a0_dcu.h
 * @brief This file contains all the functions prototypes of the DCU(Data 
 *        Computing Unit) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Hongjh          First version
   2020-07-23       Hongjh          1. Correct the macro define: DCU_CMP_TRIG_DATA01;
                                    2. Refine the macro define for interrupt, flag and mode;
                                    3. Modify API: from DCU_IntFuncCmd to DCU_GlobalIntCmd;
                                    4. Delete API: DCU_SetCmpIntMode;
                                    5. Modify DCU DATA read/write API.
   2020-09-07       Hongjh          Refine API: DCU_SetTriggerSrc
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
#ifndef __HC32F4A0_DCU_H__
#define __HC32F4A0_DCU_H__

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
 * @addtogroup DDL_DCU
 * @{
 */

#if (DDL_DCU_ENABLE == DDL_ON)

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
typedef struct
{
    uint32_t    u32IntEn;           /*!< Select DCU interrupt function.
                                         This parameter can be a value of @ref DCU_Interrupt_Configure */

    uint32_t    u32DataSize;        /*!< Specifies DCU data size.
                                         This parameter can be a value of @ref DCU_Data_Size */

    uint32_t    u32Mode;            /*!< Specifies DCU operation.
                                         This parameter can be a value of @ref DCU_Mode */

    uint32_t    u32CmpTriggerMode;  /*!< Specifies DCU compare operation trigger mode size.
                                         This parameter can be a value of @ref DCU_Compare_Trigger_Mode */
} stc_dcu_init_t;

/**
 * @brief DCU wave output configure structure definition
 */
typedef struct
{
    uint32_t    u32LowerLimit;      /*!< Defines the wave lower limit of the wave amplitude.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0xFFF */

    uint32_t    u32UpperLimit;      /*!< Defines the upper limit of the wave amplitude.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0xFFF */

    uint32_t    u32Step;            /*!< Defines the increasing/decreasing step.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0xFFF */
} stc_dcu_wave_cfg_t;

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
 * @defgroup DCU_Data_Size DCU Data Size
 * @{
 */
#define DCU_DATA_SIZE_8BIT                      (0UL)                   /*!< DCU data size: 8 bit */
#define DCU_DATA_SIZE_16BIT                     (DCU_CTL_DATASIZE_0)    /*!< DCU data size: 16 bit */
#define DCU_DATA_SIZE_32BIT                     (DCU_CTL_DATASIZE_1)    /*!< DCU data size: 32 bit */
/**
 * @}
 */

/**
 * @defgroup DCU_Compare_Trigger_Mode DCU Compare Trigger Mode
 * @{
 */
#define DCU_CMP_TRIG_DATA0                      (0UL)               /*!< DCU compare triggered by DATA0 */
#define DCU_CMP_TRIG_DATA012                    (DCU_CTL_COMP_TRG)  /*!< DCU compare triggered by DATA0 or DATA1 or DATA2 */
/**
 * @}
 */

/**
 * @defgroup DCU_Mode DCU Mode
 * @{
 */
#define DCU_INVALID                             (0UL)               /*!< DCU invalid */
#define DCU_ADD                                 (DCU_CTL_MODE_0)    /*!< DCU add operation */
#define DCU_SUB                                 (DCU_CTL_MODE_1)    /*!< DCU sub operation */
#define DCU_HW_ADD                              (DCU_CTL_MODE_1 | \
                                                 DCU_CTL_MODE_0)    /*!< Hardware trigger DCU add */
#define DCU_HW_SUB                              (DCU_CTL_MODE_2)    /*!< Hardware trigger DCU sub */
#define DCU_CMP                                 (DCU_CTL_MODE_2 | \
                                                 DCU_CTL_MODE_0)    /*!< DCU compare */
#define DCU_TRIANGLE_WAVE                       (DCU_CTL_MODE_3)    /*!< DCU triangle wave output mode */
#define DCU_SAWTOOTH_WAVE_INC                   (DCU_CTL_MODE_3 | \
                                                 DCU_CTL_MODE_0)    /*!< DCU increasing sawtooth wave output mode */
#define DCU_SAWTOOTH_WAVE_DEC                   (DCU_CTL_MODE_3 | \
                                                 DCU_CTL_MODE_1)    /*!< DCU decreasing sawtooth wave output mode */
/**
 * @}
 */

/**
 * @defgroup DCU_Interrupt_Configure DCU Interrupt Configure
 * @{
 */
#define DCU_INT_DISABLE                         (0UL)               /*!< Disable DCU interrupt */
#define DCU_INT_ENABLE                          (DCU_CTL_INTEN)     /*!< Enable DCU interrupt */
/**
 * @}
 */

/**
 * @defgroup DCU_Flag DCU Flag
 * @{
 */
#define DCU_FLAG_OPERATION                      (DCU_FLAG_FLAG_OP)  /*!< DCU addition overflow or subtraction underflow flag */
#define DCU_FLAG_DATA0_LS_DATA2                 (DCU_FLAG_FLAG_LS2) /*!< DCU DATA0 < DATA2 flag */
#define DCU_FLAG_DATA0_EQ_DATA2                 (DCU_FLAG_FLAG_EQ2) /*!< DCU DATA0 = DATA2 flag */
#define DCU_FLAG_DATA0_GT_DATA2                 (DCU_FLAG_FLAG_GT2) /*!< DCU DATA0 > DATA2 flag */
#define DCU_FLAG_DATA0_LS_DATA1                 (DCU_FLAG_FLAG_LS1) /*!< DCU DATA0 < DATA1 flag */
#define DCU_FLAG_DATA0_EQ_DATA1                 (DCU_FLAG_FLAG_EQ1) /*!< DCU DATA0 = DATA1 flag */
#define DCU_FLAG_DATA0_GT_DATA1                 (DCU_FLAG_FLAG_GT1) /*!< DCU DATA0 > DATA1 flag */
#define DCU_FLAG_WAVE_SAWTOOTH_RELOAD           (DCU_FLAG_FLAG_RLD) /*!< DCU sawtooth wave mode reload interrupt */
#define DCU_FLAG_WAVE_TRIANGLE_BOTTOM           (DCU_FLAG_FLAG_BTM) /*!< DCU triangle wave mode bottom interrupt */
#define DCU_FLAG_WAVE_TRIANGLE_TOP              (DCU_FLAG_FLAG_TOP) /*!< DCU triangle wave mode top interrupt */
/**
 * @}
 */

/**
 * @defgroup DCU_Interrupt_Category DCU Interrupt Category
 * @{
 */
#define DCU_INT_OP                              (0UL)   /*!< DCU operation result(overflow/underflow) interrupt */
#define DCU_INT_WAVE_MD                         (1UL)   /*!< DCU wave mode(sawtooth/triangle wave mode) interrupt */
#define DCU_INT_CMP_WIN                         (2UL)   /*!< DCU comparison(window) interrupt */
#define DCU_INT_CMP_NON_WIN                     (3UL)   /*!< DCU comparison(non-window) interrupt */
/**
 * @}
 */

/**
 * @defgroup DCU_Interrupt_Type DCU Interrupt Type
 * @{
 */
/**
 * @defgroup DCU_Compare_Interrupt DCU Compare(Non-window) Interrupt
 * @{
 * @note Compare interrupt selection is valid only when select DCU comparison(non-window) interrupt(DCU_INTSEL.INT_WIN=0) under DCU compare mode
 */
#define DCU_INT_CMP_DATA0_LS_DATA2              (DCU_INTEVTSEL_SEL_LS2)    /*!< DCU DATA0 < DATA2 interrupt */
#define DCU_INT_CMP_DATA0_EQ_DATA2              (DCU_INTEVTSEL_SEL_EQ2)    /*!< DCU DATA0 = DATA2 interrupt */
#define DCU_INT_CMP_DATA0_GT_DATA2              (DCU_INTEVTSEL_SEL_GT2)    /*!< DCU DATA0 > DATA2 interrupt */
#define DCU_INT_CMP_DATA0_LS_DATA1              (DCU_INTEVTSEL_SEL_LS1)    /*!< DCU DATA0 < DATA1 interrupt */
#define DCU_INT_CMP_DATA0_EQ_DATA1              (DCU_INTEVTSEL_SEL_EQ1)    /*!< DCU DATA0 = DATA1 interrupt */
#define DCU_INT_CMP_DATA0_GT_DATA1              (DCU_INTEVTSEL_SEL_GT1)    /*!< DCU DATA0 > DATA1 interrupt */
#define DCU_INT_CMP_NON_WIN_ALL                 (DCU_INT_CMP_DATA0_LS_DATA2 |  \
                                                 DCU_INT_CMP_DATA0_EQ_DATA2 |  \
                                                 DCU_INT_CMP_DATA0_GT_DATA2 |  \
                                                 DCU_INT_CMP_DATA0_LS_DATA1 |  \
                                                 DCU_INT_CMP_DATA0_EQ_DATA1 |  \
                                                 DCU_INT_CMP_DATA0_GT_DATA1)
/**
 * @}
 */

/**
 * @defgroup DCU_Window_Compare_Interrupt DCU Window Compare Interrupt
 * @{
 */
#define DCU_INT_CMP_WIN_INSIDE                  (DCU_INTEVTSEL_SEL_WIN_0)  /*!< DCU comparison(DATA2 <= DATA0 <= DATA1) interrupt */
#define DCU_INT_CMP_WIN_OUTSIDE                 (DCU_INTEVTSEL_SEL_WIN_1)  /*!< DCU comparison(DATA0 < DATA2 & DATA0 > DATA1 ) interrupt */
#define DCU_INT_CMP_WIN_ALL                     (DCU_INT_CMP_WIN_INSIDE |      \
                                                 DCU_INT_CMP_WIN_OUTSIDE)
/**
 * @}
 */

/**
 * @defgroup DCU_Wave_Mode_Interrupt DCU Wave Mode Interrupt
 * @{
 */
#define DCU_INT_WAVE_SAWTOOTH_RELOAD            (DCU_INTEVTSEL_SEL_RLD) /*!< DCU sawtooth wave mode reload interrupt */
#define DCU_INT_WAVE_TRIANGLE_BOTTOM            (DCU_INTEVTSEL_SEL_BTM) /*!< DCU triangle wave mode bottom interrupt */
#define DCU_INT_WAVE_TRIANGLE_TOP               (DCU_INTEVTSEL_SEL_TOP) /*!< DCU triangle wave mode top interrupt */
#define DCU_INT_WAVE_MD_ALL                     (DCU_INT_WAVE_TRIANGLE_TOP    |\
                                                 DCU_INT_WAVE_TRIANGLE_BOTTOM |\
                                                 DCU_INT_WAVE_SAWTOOTH_RELOAD)
/**
 * @}
 */

/**
 * @defgroup DCU_Operation_Interrupt DCU Operation Interrupt
 * @{
 */
#define DCU_INT_OP_UDF_OVF                      (DCU_INTEVTSEL_SEL_OP)  /*!< DCU addition overflow or subtraction underflow interrupt */
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
#define DCU_DATA0_IDX                           (0UL)   /*!< DCU DATA0 */
#define DCU_DATA1_IDX                           (1UL)   /*!< DCU DATA1 */
#define DCU_DATA2_IDX                           (2UL)   /*!< DCU DATA2 */
/**
 * @}
 */

/**
 * @defgroup DCU_Common_Trigger_Source_Configure DCU common Trigger Source Configure
 * @{
 */
#define DCU_COM_TRIG1                           (AOS_DCU_1_TRGSEL_COMTRG_EN_0)
#define DCU_COM_TRIG2                           (AOS_DCU_1_TRGSEL_COMTRG_EN_1)
#define DCU_COM_TRIG_MASK                       (AOS_DCU_1_TRGSEL_COMTRG_EN)
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

/* Initialization and configuration DCU functions */
en_result_t DCU_Init(M4_DCU_TypeDef *DCUx, const stc_dcu_init_t *pstcInit);
en_result_t DCU_StructInit(stc_dcu_init_t *pstcInit);
void DCU_DeInit(M4_DCU_TypeDef *DCUx);

en_result_t DCU_WaveCfg(M4_DCU_TypeDef *DCUx, const stc_dcu_wave_cfg_t *pstcCfg);
void DCU_SetMode(M4_DCU_TypeDef *DCUx, uint32_t u32Mode);
uint32_t DCU_GetMode(const M4_DCU_TypeDef *DCUx);
void DCU_SetDataSize(M4_DCU_TypeDef *DCUx, uint32_t u32DataSize);
uint32_t DCU_GetDataSize(const M4_DCU_TypeDef *DCUx);
en_flag_status_t DCU_GetStatus(const M4_DCU_TypeDef *DCUx, uint32_t u32Flag);
void DCU_ClearStatus(M4_DCU_TypeDef *DCUx, uint32_t u32Flag);
void DCU_IntCmd(M4_DCU_TypeDef *DCUx,
                uint32_t u32IntCategory,
                uint32_t u32IntType,
                en_functional_state_t enNewState);
void DCU_GlobalIntCmd(M4_DCU_TypeDef *DCUx, en_functional_state_t enNewState);
void DCU_ComTriggerCmd(M4_DCU_TypeDef *DCUx,
                            uint32_t u32ComTrig,
                            en_functional_state_t enNewState);
void DCU_SetTriggerSrc(const M4_DCU_TypeDef *DCUx, en_event_src_t enEventSrc);

uint8_t DCU_ReadData8(const M4_DCU_TypeDef *DCUx, uint32_t u32DataIndex);
void DCU_WriteData8(M4_DCU_TypeDef *DCUx,
                    uint32_t u32DataIndex,
                    uint8_t u8Data);
uint16_t DCU_ReadData16(const M4_DCU_TypeDef *DCUx, uint32_t u32DataIndex);
void DCU_WriteData16(M4_DCU_TypeDef *DCUx,
                        uint32_t u32DataIndex,
                        uint16_t u16Data);
uint32_t DCU_ReadData32(const M4_DCU_TypeDef *DCUx, uint32_t u32DataIndex);
void DCU_WriteData32(M4_DCU_TypeDef *DCUx,
                        uint32_t u32DataIndex,
                        uint32_t u32Data);

/**
 * @}
 */

#endif /* DDL_DCU_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_DCU_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
