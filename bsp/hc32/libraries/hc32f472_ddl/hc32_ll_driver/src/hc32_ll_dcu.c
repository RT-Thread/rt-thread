/**
 *******************************************************************************
 * @file  hc32_ll_dcu.c
 * @brief This file provides firmware functions to manage the DCU(Data Computing
 *        Unit).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Modify typo
                                    Modify API DCU_DeInit()
                                    Delete wave mode
                                    Modify function DCU_IntCmd() for misra
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_dcu.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_DCU DCU
 * @brief DCU Driver Library
 * @{
 */

#if (LL_DCU_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DCU_Local_Macros DCU Local Macros
 * @{
 */

#define DCU_RMU_TIMEOUT             (100U)

/**
 * @defgroup DCU_Check_Parameters_Validity DCU Check Parameters Validity
 * @{
 */

#define IS_DCU_BASE_FUNC_UNIT(x)                                               \
(   ((x) == CM_DCU1)                    ||                                     \
    ((x) == CM_DCU2)                    ||                                     \
    ((x) == CM_DCU3))

#define IS_DCU_UNIT(x)                  (IS_DCU_BASE_FUNC_UNIT(x))

#define IS_DCU_BASE_FUNC_UNIT_MD(x)                                            \
(   ((x) == DCU_MD_CMP)                 ||                                     \
    ((x) == DCU_MD_ADD)                 ||                                     \
    ((x) == DCU_MD_SUB)                 ||                                     \
    ((x) == DCU_MD_HW_ADD)              ||                                     \
    ((x) == DCU_MD_HW_SUB)              ||                                     \
    ((x) == DCU_MD_INVD))

#define IS_DCU_BASE_FUNC_UNIT_FLAG(x)                                          \
(   (0UL != (x))                        &&                                     \
    (0UL == ((x) & (~DCU_BASE_FUNC_UNIT_FLAG_MASK))))

#define IS_DCU_CMP_COND(x)                                                     \
(   ((x) == DCU_CMP_TRIG_DATA0)         ||                                     \
    ((x) == DCU_CMP_TRIG_DATA0_DATA1_DATA2))

#define IS_DCU_DATA_WIDTH(x)                                                   \
(   ((x) == DCU_DATA_WIDTH_8BIT)        ||                                     \
    ((x) == DCU_DATA_WIDTH_16BIT)       ||                                     \
    ((x) == DCU_DATA_WIDTH_32BIT))

#define IS_DCU_INT_CATEGORY(x)                                                 \
(   ((x) == DCU_CATEGORY_OP)            ||                                     \
    ((x) == DCU_CATEGORY_CMP_WIN)       ||                                     \
    ((x) == DCU_CATEGORY_CMP_NON_WIN))

#define IS_DCU_INT_OP(x)                ((x) == DCU_INT_OP_CARRY)

#define IS_DCU_INT_CMP_WIN(x)                                                  \
(   ((x) == DCU_INT_CMP_WIN_INSIDE)     ||                                     \
    ((x) == DCU_INT_CMP_WIN_OUTSIDE))

#define IS_DCU_INT_CMP_NON_WIN(x)                                              \
(   ((x) != 0UL)                        ||                                     \
    (((x) | DCU_INT_CMP_NON_WIN_ALL) == DCU_INT_CMP_NON_WIN_ALL))

#define IS_DCU_INT_WAVE_MD(x)                                                  \
(   ((x) != 0UL)                        &&                                     \
    (((x) | DCU_INT_WAVE_MD_ALL) == DCU_INT_WAVE_MD_ALL))

#define IS_DCU_DATA_REG(x)                                                     \
(   ((x) == DCU_DATA0_IDX)              ||                                     \
    ((x) == DCU_DATA1_IDX)              ||                                     \
    ((x) == DCU_DATA2_IDX))

#define IS_DCU_WAVE_UPPER_LIMIT(x)      ((x) <= 0xFFFUL)

#define IS_DCU_WAVE_LOWER_LIMIT(x)      ((x) <= 0xFFFUL)

#define IS_DCU_WAVE_STEP(x)             ((x) <= 0xFFFUL)
/**
 * @}
 */

/**
 * @defgroup DCU_Flag_Mask DCU Flag Mask
 * @{
 */
#define DCU_BASE_FUNC_UNIT_FLAG_MASK    (0x0E7FUL)
/**
 * @}
 */

/**
 * @defgroup DCU_Register_Address DCU Register Address
 * @{
 */
#define DCU_REG_ADDR(_REG_)                 ((uint32_t)(&(_REG_)))
#define DCU_DATA_REG_ADDR(_UNITx_, _IDX_)   (DCU_REG_ADDR((_UNITx_)->DATA0) + ((_IDX_) << 2UL))

#define DCU_DATA_REG8(_UNITx_, _IDX_)       (*(__IO uint8_t *)DCU_DATA_REG_ADDR(_UNITx_, _IDX_))
#define DCU_DATA_REG16(_UNITx_, _IDX_)      (*(__IO uint16_t *)DCU_DATA_REG_ADDR(_UNITx_, _IDX_))
#define DCU_DATA_REG32(_UNITx_, _IDX_)      (*(__IO uint32_t *)DCU_DATA_REG_ADDR(_UNITx_, _IDX_))
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup DCU_Global_Functions DCU Global Functions
 * @{
 */

/**
 * @brief  Set the fields of structure stc_dcu_init_t to default values.
 * @param  [out] pstcDcuInit            Pointer to a @ref stc_dcu_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcDcuInit value is NULL.
 */
int32_t DCU_StructInit(stc_dcu_init_t *pstcDcuInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcDcuInit) {
        pstcDcuInit->u32Mode = DCU_MD_INVD;
        pstcDcuInit->u32DataWidth = DCU_DATA_WIDTH_8BIT;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize DCU function.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx:    DCU instance register base
 * @param  [in] pstcDcuInit             Pointer to a @ref stc_dcu_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcDcuInit value is NULL.
 */
int32_t DCU_Init(CM_DCU_TypeDef *DCUx, const stc_dcu_init_t *pstcDcuInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcDcuInit) {
        DDL_ASSERT(IS_DCU_UNIT(DCUx) && IS_DCU_BASE_FUNC_UNIT_MD(pstcDcuInit->u32Mode));
        DDL_ASSERT(IS_DCU_DATA_WIDTH(pstcDcuInit->u32DataWidth));

        /* Set register: CTL */
        WRITE_REG32(DCUx->CTL, (pstcDcuInit->u32Mode | pstcDcuInit->u32DataWidth));

        /* Disable interrupt */
        WRITE_REG32(DCUx->INTEVTSEL, 0x00000000UL);

        /* Clear Flag */
        WRITE_REG32(DCUx->FLAGCLR, 0x0000007FUL);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  De-Initialize DCU function.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx:    DCU instance register base
 * @retval int32_t:
 *           - LL_OK:                   De-Initialize success.
 *           - LL_ERR_TIMEOUT:          Timeout.
 */
int32_t DCU_DeInit(CM_DCU_TypeDef *DCUx)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32UnitShift;
    uint32_t u32UnitBase;
    __IO uint8_t u8TimeOut = 0U;

    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    /* Check FRST register protect */
    DDL_ASSERT((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1);

    /* Reset */
    u32UnitBase = (uint32_t)DCUx;
    u32UnitShift = (u32UnitBase - CM_DCU1_BASE) / (CM_DCU2_BASE - CM_DCU1_BASE);
    CLR_REG32_BIT(CM_RMU->FRST0, RMU_FRST0_DCU1 << u32UnitShift);
    /* Ensure reset procedure is completed */
    while (0UL == READ_REG32_BIT(CM_RMU->FRST0, RMU_FRST0_DCU1 << u32UnitShift)) {
        u8TimeOut++;
        if (u8TimeOut > DCU_RMU_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }
    return i32Ret;
}

/**
 * @brief  Set DCU operation mode.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx:    DCU instance register base
 * @param  [in] u32Mode                 DCU mode
 *         This parameter can be one of the macros group @ref DCU_Mode.
 * @retval None
 */
void DCU_SetMode(CM_DCU_TypeDef *DCUx, uint32_t u32Mode)
{
    DDL_ASSERT(IS_DCU_UNIT(DCUx) && IS_DCU_BASE_FUNC_UNIT_MD(u32Mode));

    MODIFY_REG32(DCUx->CTL, DCU_CTL_MODE, u32Mode);
}

/**
 * @brief  Set DCU data size.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx:    DCU instance register base
 * @param  [in] u32DataWidth            DCU data width
 *         This parameter can be one of the macros group @ref DCU_Data_Width
 *           @arg DCU_DATA_WIDTH_8BIT:  DCU data size 8 bit
 *           @arg DCU_DATA_WIDTH_16BIT: DCU data size 16 bit
 *           @arg DCU_DATA_WIDTH_32BIT: DCU data size 32 bit
 * @retval None
 */
void DCU_SetDataWidth(CM_DCU_TypeDef *DCUx, uint32_t u32DataWidth)
{
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_WIDTH(u32DataWidth));

    MODIFY_REG32(DCUx->CTL, DCU_CTL_DATASIZE, u32DataWidth);
}

/**
 * @brief  Set DCU compare trigger condition.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx:    DCU instance register base
 * @param  [in] u32Cond                 DCU compare trigger condition
 *         This parameter can be one of the macros group @ref DCU_Compare_Trigger_Condition
 *           @arg DCU_CMP_TRIG_DATA0:               DCU compare triggered by DATA0.
 *           @arg DCU_CMP_TRIG_DATA0_DATA1_DATA2:   DCU compare triggered by DATA0 or DATA1 or DATA2.
 * @retval None
 */
void DCU_SetCompareCond(CM_DCU_TypeDef *DCUx, uint32_t u32Cond)
{
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_CMP_COND(u32Cond));

    MODIFY_REG32(DCUx->CTL, DCU_CTL_COMPTRG, u32Cond);
}

/**
 * @brief  Get DCU flag.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx:    DCU instance register base
 * @param  [in] u32Flag                 The specified DCU flag
 *         This parameter can be any composed value of the macros group @ref DCU_Flag.
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t DCU_GetStatus(const CM_DCU_TypeDef *DCUx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_DCU_UNIT(DCUx) && IS_DCU_BASE_FUNC_UNIT_FLAG(u32Flag));

    return (0UL == READ_REG32_BIT(DCUx->FLAG, u32Flag)) ? RESET : SET;
}

/**
 * @brief  Clear DCU flag.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx:    DCU instance register base
 * @param  [in] u32Flag                 The specified DCU flag
 *         This parameter can be any composed value of the macros group @ref DCU_Mode.
 * @retval None
 */
void DCU_ClearStatus(CM_DCU_TypeDef *DCUx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_DCU_UNIT(DCUx) && IS_DCU_BASE_FUNC_UNIT_FLAG(u32Flag));

    WRITE_REG32(DCUx->FLAGCLR, u32Flag);
}

/**
 * @brief  Enable or disable DCU interrupt function.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx: DCU instance register base
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DCU_GlobalIntCmd(CM_DCU_TypeDef *DCUx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(DCUx->CTL, DCU_CTL_INTEN);
    } else {
        CLR_REG32_BIT(DCUx->CTL, DCU_CTL_INTEN);
    }
}

/**
 * @brief  Enable/disable DCU the specified interrupt source.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx:    DCU instance register base
 * @param  [in] u32IntCategory          DCU interrupt category
 *         This parameter can be one of the macros group @ref DCU_Category.
 * @param  [in] u32IntType              DCU interrupt type
 *         This parameter can be one of the macros group @ref DCU_Interrupt_Type.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DCU_IntCmd(CM_DCU_TypeDef *DCUx, uint32_t u32IntCategory, uint32_t u32IntType, en_functional_state_t enNewState)
{
    uint32_t u32Type;

    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_INT_CATEGORY(u32IntCategory));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DCU_CATEGORY_OP == u32IntCategory) {
        DDL_ASSERT(IS_DCU_INT_OP(u32IntType));
        u32Type = (u32IntType & DCU_INT_OP_CARRY);
    } else if (DCU_CATEGORY_CMP_WIN == u32IntCategory) {
        DDL_ASSERT(IS_DCU_INT_CMP_WIN(u32IntType));
        u32Type = (u32IntType & DCU_INT_CMP_WIN_ALL);
    } else {
        DDL_ASSERT(IS_DCU_INT_CMP_NON_WIN(u32IntType));
        u32Type = (u32IntType & DCU_INT_CMP_NON_WIN_ALL);
    }

    if (ENABLE == enNewState) {
        SET_REG32_BIT(DCUx->INTEVTSEL, u32Type);
    } else {
        CLR_REG32_BIT(DCUx->INTEVTSEL, u32Type);
    }
}

/**
 * @brief  Read DCU register DATA for byte.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx:    DCU instance register base
 * @param  [in] u32DataIndex            DCU data register index
 *         This parameter can be one of the macros group @ref DCU_Data_Register_Index
 *           @arg DCU_DATA0_IDX:        DCU DATA0
 *           @arg DCU_DATA1_IDX:        DCU DATA1
 *           @arg DCU_DATA2_IDX:        DCU DATA2
 * @retval DCU register DATA value for byte
 */
uint8_t DCU_ReadData8(const CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex)
{
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    return READ_REG8(DCU_DATA_REG8(DCUx, u32DataIndex));
}

/**
 * @brief  Write DCU register DATA for byte.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx:    DCU instance register base
 * @param  [in] u32DataIndex            DCU data register index
 *         This parameter can be one of the macros group @ref DCU_Data_Register_Index
 *           @arg DCU_DATA0_IDX:        DCU DATA0
 *           @arg DCU_DATA1_IDX:        DCU DATA1
 *           @arg DCU_DATA2_IDX:        DCU DATA2
 * @param  [in] u8Data                  The data to write.
 * @retval None
 */
void DCU_WriteData8(CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex, uint8_t u8Data)
{
    __IO uint8_t *DATA;

    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    DATA = &DCU_DATA_REG8(DCUx, u32DataIndex);
    WRITE_REG8(*DATA, u8Data);
}

/**
 * @brief  Read DCU register DATA for half-word.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx:    DCU instance register base
 * @param  [in] u32DataIndex            DCU data register index
 *         This parameter can be one of the macros group @ref DCU_Data_Register_Index
 *           @arg DCU_DATA0_IDX:        DCU DATA0
 *           @arg DCU_DATA1_IDX:        DCU DATA1
 *           @arg DCU_DATA2_IDX:        DCU DATA2
 * @retval DCU register DATA value for half-word
 */
uint16_t DCU_ReadData16(const CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex)
{
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    return READ_REG16(DCU_DATA_REG16(DCUx, u32DataIndex));
}

/**
 * @brief  Write DCU register DATA for half-word.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx:    DCU instance register base
 * @param  [in] u32DataIndex            DCU data register index
 *         This parameter can be one of the macros group @ref DCU_Data_Register_Index
 *           @arg DCU_DATA0_IDX:        DCU DATA0
 *           @arg DCU_DATA1_IDX:        DCU DATA1
 *           @arg DCU_DATA2_IDX:        DCU DATA2
 * @param  [in] u16Data                 The data to write.
 * @retval None
 */
void DCU_WriteData16(CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex, uint16_t u16Data)
{
    __IO uint16_t *DATA;

    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    DATA = &DCU_DATA_REG16(DCUx, u32DataIndex);
    WRITE_REG16(*DATA, u16Data);
}

/**
 * @brief  Read DCU register DATA for word.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx:    DCU instance register base
 * @param  [in] u32DataIndex            DCU data register index
 *         This parameter can be one of the macros group @ref DCU_Data_Register_Index
 *           @arg DCU_DATA0_IDX:        DCU DATA0
 *           @arg DCU_DATA1_IDX:        DCU DATA1
 *           @arg DCU_DATA2_IDX:        DCU DATA2
 * @retval DCU register DATA value for word
 */
uint32_t DCU_ReadData32(const CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex)
{
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    return READ_REG32(DCU_DATA_REG32(DCUx, u32DataIndex));
}

/**
 * @brief  Write DCU register DATA0 for word.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_DCU or CM_DCUx:    DCU instance register base
 * @param  [in] u32DataIndex            DCU data register index
 *         This parameter can be one of the macros group @ref DCU_Data_Register_Index
 *           @arg DCU_DATA0_IDX:        DCU DATA0
 *           @arg DCU_DATA1_IDX:        DCU DATA1
 *           @arg DCU_DATA2_IDX:        DCU DATA2
 * @param  [in] u32Data                 The data to write.
 * @retval None
 */
void DCU_WriteData32(CM_DCU_TypeDef *DCUx, uint32_t u32DataIndex, uint32_t u32Data)
{
    __IO uint32_t *DATA;

    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    DATA = &DCU_DATA_REG32(DCUx, u32DataIndex);
    WRITE_REG32(*DATA, u32Data);
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
