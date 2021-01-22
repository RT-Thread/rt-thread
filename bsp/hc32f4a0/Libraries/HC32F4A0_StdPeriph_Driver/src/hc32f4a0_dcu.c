/**
 *******************************************************************************
 * @file  hc32f4a0_dcu.c
 * @brief This file provides firmware functions to manage the DCU(Data Computing
 *        Unit).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Hongjh          First version
   2020-07-23       Hongjh          1. Modify macro define for interrupt, flag and mode;
                                    2. Rename API: from DCU_IntFuncCmd to DCU_GlobalIntCmd;
                                    3. Refine API: DCU_IntCmd and delete DCU_SetCmpIntMode;
                                    4. Refine API: DCU DATA read/write.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_dcu.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_DCU DCU
 * @brief DCU Driver Library
 * @{
 */

#if (DDL_DCU_ENABLE == DDL_ON)

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

/**
 * @defgroup DCU_Check_Parameters_Validity DCU Check Parameters Validity
 * @{
 */
#define IS_DCU_BASE_FUNC_UNIT(x)                                               \
(   (M4_DCU5 == (x))                            ||                             \
    (M4_DCU6 == (x))                            ||                             \
    (M4_DCU7 == (x))                            ||                             \
    (M4_DCU8 == (x)))

#define IS_DCU_WAVE_FUNC_UNIT(x)                                               \
(   (M4_DCU1 == (x))                            ||                             \
    (M4_DCU2 == (x))                            ||                             \
    (M4_DCU3 == (x))                            ||                             \
    (M4_DCU4 == (x)))

#define IS_DCU_UNIT(x)                                                         \
(   (IS_DCU_BASE_FUNC_UNIT(x))                  ||                             \
    (IS_DCU_WAVE_FUNC_UNIT(x)))

#define IS_DCU_BASE_FUNC_UNIT_MODE(x)                                          \
(   (DCU_CMP == (x))                            ||                             \
    (DCU_ADD == (x))                            ||                             \
    (DCU_SUB == (x))                            ||                             \
    (DCU_HW_ADD == (x))                         ||                             \
    (DCU_HW_SUB == (x)))

#define IS_DCU_WAVE_FUNC_UNIT_MODE(x)                                          \
(   (DCU_CMP == (x))                            ||                             \
    (DCU_ADD == (x))                            ||                             \
    (DCU_SUB == (x))                            ||                             \
    (DCU_HW_ADD == (x))                         ||                             \
    (DCU_HW_SUB == (x))                         ||                             \
    (DCU_TRIANGLE_WAVE == (x))                  ||                             \
    (DCU_SAWTOOTH_WAVE_INC == (x))              ||                             \
    (DCU_SAWTOOTH_WAVE_DEC == (x)))

#define IS_DCU_BASE_FUNC_UNIT_INT(x)                                           \
(   (0UL != (x))                                &&                             \
    (0UL == ((x) & (~DCU_BASE_FUNC_UNIT_INT_MASK))))

#define IS_DCU_WAVE_FUNC_UNIT_INT(x)                                           \
(   (0UL != (x))                                &&                             \
    (0UL == ((x) & (~DCU_WAVE_FUNC_UNIT_INT_MASK))))

#define IS_DCU_BASE_FUNC_UNIT_FLAG(x)                                          \
(   (0UL != (x))                                &&                             \
    (0UL == ((x) & (~DCU_BASE_FUNC_UNIT_FLAG_MASK))))

#define IS_DCU_WAVE_FUNC_UNIT_FLAG(x)                                          \
(   (0UL != (x))                                &&                             \
    (0UL == ((x) & (~DCU_WAVE_FUNC_UNIT_FLAG_MASK))))

#define IS_DCU_INTERRUPT_STATE(x)                                              \
(   (DCU_INT_ENABLE == (x))                     ||                             \
    (DCU_INT_DISABLE == (x)))

#define IS_DCU_CMP_TRIG_MODE(x)                                                \
(   (DCU_CMP_TRIG_DATA0 == (x))                 ||                             \
    (DCU_CMP_TRIG_DATA012 == (x)))

#define IS_DCU_DATA_SIZE(x)                                                    \
(   (DCU_DATA_SIZE_8BIT == (x))                 ||                             \
    (DCU_DATA_SIZE_16BIT == (x))                ||                             \
    (DCU_DATA_SIZE_32BIT == (x)))

#define IS_DCU_INT_CATEGORY(x)                                                 \
(   ((x) == DCU_INT_OP)                         ||                             \
    ((x) == DCU_INT_WAVE_MD)                    ||                             \
    ((x) == DCU_INT_CMP_WIN)                    ||                             \
    ((x) == DCU_INT_CMP_NON_WIN))

#define IS_DCU_INT_OP(x)                        ((x) == DCU_INT_OP_UDF_OVF)

#define IS_DCU_INT_CMP_WIN(x)                                                  \
(   ((x) != 0UL)                                &&                             \
    (((x) | DCU_INT_CMP_WIN_ALL) == DCU_INT_CMP_WIN_ALL))

#define IS_DCU_INT_WAVE_MD(x)                                                  \
(   ((x) != 0UL)                                &&                             \
    (((x) | DCU_INT_WAVE_MD_ALL) == DCU_INT_WAVE_MD_ALL))

#define IS_DCU_INT_CMP_NON_WIN(x)                                              \
(   ((x) != 0UL)                                ||                             \
    (((x) | DCU_INT_CMP_NON_WIN_ALL) == DCU_INT_CMP_NON_WIN_ALL))

#define IS_DCU_DATA_REG(x)                                                     \
(   ((x) == DCU_DATA0_IDX)                      ||                             \
    ((x) == DCU_DATA1_IDX)                      ||                             \
    ((x) == DCU_DATA2_IDX))

#define IS_DCU_COM_TRIG(x)                                                     \
(   (0UL != (x))                                &&                             \
    (0UL == ((x) & (~DCU_COM_TRIG_MASK))))

#define IS_DCU_WAVE_UPPER_LIMIT(x)              ((x) <= 0xFFFUL)

#define IS_DCU_WAVE_LOWER_LIMIT(x)              ((x) <= 0xFFFUL)

#define IS_DCU_WAVE_STEP(x)                     ((x) <= 0xFFFUL)
/**
 * @}
 */

/**
 * @defgroup DCU_Flag_Mask DCU Flag Mask
 * @{
 */
#define DCU_BASE_FUNC_UNIT_FLAG_MASK                                           \
(   DCU_FLAG_DATA0_LS_DATA2                     |                              \
    DCU_FLAG_DATA0_EQ_DATA2                     |                              \
    DCU_FLAG_DATA0_GT_DATA2                     |                              \
    DCU_FLAG_DATA0_LS_DATA1                     |                              \
    DCU_FLAG_DATA0_EQ_DATA1                     |                              \
    DCU_FLAG_DATA0_GT_DATA1)

#define DCU_WAVE_FUNC_UNIT_FLAG_MASK                                           \
(   DCU_FLAG_OPERATION                          |                              \
    DCU_FLAG_DATA0_LS_DATA2                     |                              \
    DCU_FLAG_DATA0_EQ_DATA2                     |                              \
    DCU_FLAG_DATA0_GT_DATA2                     |                              \
    DCU_FLAG_DATA0_LS_DATA1                     |                              \
    DCU_FLAG_DATA0_EQ_DATA1                     |                              \
    DCU_FLAG_DATA0_GT_DATA1                     |                              \
    DCU_FLAG_WAVE_SAWTOOTH_RELOAD               |                              \
    DCU_FLAG_WAVE_TRIANGLE_BOTTOM               |                              \
    DCU_FLAG_WAVE_TRIANGLE_TOP)
/**
 * @}
 */

#define DCU_DATA1_LOWER_LIMIT_POS               (0UL)
#define DCU_DATA1_LOWER_LIMIT                   (0x00000FFFUL)

#define DCU_DATA1_UPPER_LIMIT_POS               (16UL)
#define DCU_DATA1_UPPER_LIMIT                   (0x0FFF0000UL)

/**
 * @defgroup DCU_Register_Address Get DCU register address
 * @{
 */
#define REG_ADDR(__REG__)                       ((uint32_t)(&(__REG__)))
#define DATA_REG_ADDR(__DCUx__, __IDX__)        (REG_ADDR((__DCUx__)->DATA0) + ((__IDX__) << 2UL))
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

/**
 * @addtogroup DCU_Local_Functions
 * @{
 */
static __IO uint32_t* DCU_TRGSELx(const M4_DCU_TypeDef *DCUx);
/**
 * @}
 */

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
 * @brief  Initialize DCU function.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] pstcInit                Pointer to a @ref stc_dcu_init_t structure (DCU function configuration data structure).
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit is NULL pointer
 */
en_result_t DCU_Init(M4_DCU_TypeDef *DCUx, const stc_dcu_init_t *pstcInit)
{
    uint32_t u32RegVal;
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcInit)
    {
        DDL_ASSERT((IS_DCU_WAVE_FUNC_UNIT(DCUx) && IS_DCU_WAVE_FUNC_UNIT_MODE(pstcInit->u32Mode)) || \
                   (IS_DCU_BASE_FUNC_UNIT(DCUx) && IS_DCU_BASE_FUNC_UNIT_MODE(pstcInit->u32Mode)));
        DDL_ASSERT(IS_DCU_DATA_SIZE(pstcInit->u32DataSize));
        DDL_ASSERT(IS_DCU_INTERRUPT_STATE(pstcInit->u32IntEn));
        DDL_ASSERT(IS_DCU_CMP_TRIG_MODE(pstcInit->u32CmpTriggerMode));

        /* De-initialize DCU */
        WRITE_REG32(DCUx->CTL, 0x00000000UL);
        WRITE_REG32(DCUx->INTEVTSEL, 0x00000000UL);
        WRITE_REG32(DCUx->FLAGCLR, (IS_DCU_WAVE_FUNC_UNIT(DCUx)) ? 0x00000E7FUL:0x0000007FUL);

        /* Set register: CTL */
        u32RegVal = (pstcInit->u32Mode | \
                     pstcInit->u32DataSize | \
                     pstcInit->u32CmpTriggerMode | \
                     pstcInit->u32IntEn);
        WRITE_REG32(DCUx->CTL, u32RegVal);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_uart_init_t to default values.
 * @param  [out] pstcInit               Pointer to a @ref stc_dcu_init_t structure (DCU function configuration data structure).
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcInit is NULL pointer
 */
en_result_t DCU_StructInit(stc_dcu_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check parameters */
    if (NULL != pstcInit)
    {
        pstcInit->u32Mode = DCU_SUB;
        pstcInit->u32DataSize = DCU_DATA_SIZE_8BIT;
        pstcInit->u32CmpTriggerMode = DCU_CMP_TRIG_DATA0;
        pstcInit->u32IntEn = DCU_INT_DISABLE;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize DCU function.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @retval None
 */
void DCU_DeInit(M4_DCU_TypeDef *DCUx)
{
    /* Configures the registers to reset value. */
    WRITE_REG32(DCUx->CTL, 0x00000000UL);
    WRITE_REG32(DCUx->INTEVTSEL, 0x00000000UL);
    WRITE_REG32(DCUx->FLAGCLR, 0x0000007FUL);
    WRITE_REG32(DCUx->DATA0, 0x00000000UL);
    WRITE_REG32(DCUx->DATA1, 0x00000000UL);
    WRITE_REG32(DCUx->DATA2, 0x00000000UL);
}

/**
 * @brief  Initialize DCU function.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 * @param  [in] pstcCfg                 Pointer to a @ref stc_dcu_wave_cfg_t structure (DCU wave function configuration data structure).
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcCfg is NULL pointer
 * @note   The DCU sawtooth/triangle wave mode is supported by M4_DCU1/2/3/4.
 */
en_result_t DCU_WaveCfg(M4_DCU_TypeDef *DCUx,
                           const stc_dcu_wave_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcCfg)
    {
        DDL_ASSERT(IS_DCU_WAVE_FUNC_UNIT(DCUx));
        DDL_ASSERT(IS_DCU_WAVE_LOWER_LIMIT(pstcCfg->u32LowerLimit));
        DDL_ASSERT(IS_DCU_WAVE_UPPER_LIMIT(pstcCfg->u32UpperLimit));
        DDL_ASSERT(IS_DCU_WAVE_STEP(pstcCfg->u32Step));

        WRITE_REG32(DCUx->DATA0, 0x00000000UL);
        WRITE_REG32(DCUx->DATA1, ((pstcCfg->u32LowerLimit << DCU_DATA1_LOWER_LIMIT_POS) | \
                                  (pstcCfg->u32UpperLimit << DCU_DATA1_UPPER_LIMIT_POS)));
        WRITE_REG32(DCUx->DATA2, pstcCfg->u32Step);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set DCU operation mode.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] u32Mode                 DCU mode
 *         This parameter can be one of the following values:
 *           @arg DCU_INVALID:          DCU invalid
 *           @arg DCU_ADD:              DCU add operation
 *           @arg DCU_SUB:              DCU sub operation
 *           @arg DCU_HW_ADD:           DCU hardware trigger add
 *           @arg DCU_HW_SUB:           DCU hardware trigger sub
 *           @arg DCU_CMP:              DCU compare
 *           @arg DCU_TRIANGLE_WAVE:    DCU triangle wave output mode
 *           @arg DCU_SAWTOOTH_WAVE_INC:DCU increasing sawtooth wave output mode
 *           @arg DCU_SAWTOOTH_WAVE_DEC:DCU decreasing sawtooth wave output mode
 * @retval None
 * @note   The DCU sawtooth/triangle wave mode is supported by M4_DCU1/2/3/4.
 */
void DCU_SetMode(M4_DCU_TypeDef *DCUx, uint32_t u32Mode)
{
    /* Check for parameters */
    DDL_ASSERT((IS_DCU_WAVE_FUNC_UNIT(DCUx) && IS_DCU_WAVE_FUNC_UNIT_MODE(u32Mode)) || \
               (IS_DCU_BASE_FUNC_UNIT(DCUx) && IS_DCU_BASE_FUNC_UNIT_MODE(u32Mode)));

    MODIFY_REG32(DCUx->CTL, DCU_CTL_MODE, u32Mode);
}

/**
 * @brief  Get DCU operation mode.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg DCU_INVALID:          DCU invalid
 *           @arg DCU_ADD:              DCU add operation
 *           @arg DCU_SUB:              DCU sub operation
 *           @arg DCU_HW_ADD:           DCU hardware trigger add
 *           @arg DCU_HW_SUB:           DCU hardware trigger sub
 *           @arg DCU_CMP:              DCU compare
 *           @arg DCU_TRIANGLE_WAVE:    DCU triangle wave output mode
 *           @arg DCU_SAWTOOTH_WAVE_INC:DCU increasing sawtooth wave output mode
 *           @arg DCU_SAWTOOTH_WAVE_DEC:DCU decreasing sawtooth wave output mode
 * @note   The DCU sawtooth/triangle wave mode is supported by M4_DCU1/2/3/4.
 */
uint32_t DCU_GetMode(const M4_DCU_TypeDef *DCUx)
{
    /* Check for DCUx pointer */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));

    return READ_REG32_BIT(DCUx->CTL, DCU_CTL_MODE);
}

/**
 * @brief  Set DCU data size.
 * @param  [in] DCUx                     Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] u32DataSize             DCU data size
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA_SIZE_8BIT:   DCU data size 8 bits
 *           @arg DCU_DATA_SIZE_16BIT:  DCU data size 16 bits
 *           @arg DCU_DATA_SIZE_32BIT:  DCU data size 32 bits
 * @retval None
 */
void DCU_SetDataSize(M4_DCU_TypeDef *DCUx, uint32_t u32DataSize)
{
    /* Check for DCUx pointer */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_SIZE(u32DataSize));

    MODIFY_REG32(DCUx->CTL, DCU_CTL_DATASIZE, u32DataSize);
}

/**
 * @brief  Get DCU data size.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg DCU_DATA_SIZE_8BIT:   DCU data size 8 bits
 *           @arg DCU_DATA_SIZE_16BIT:  DCU data size 16 bits
 *           @arg DCU_DATA_SIZE_32BIT:  DCU data size 32 bits
 */
uint32_t DCU_GetDataSize(const M4_DCU_TypeDef *DCUx)
{
    /* Check for DCUx pointer */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));

    return READ_REG32_BIT(DCUx->CTL, DCU_CTL_DATASIZE);
}

/**
 * @brief  Get DCU flag.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] u32Flag                 The specified DCU flag
 *         This parameter can be one of the following values:
 *           @arg DCU_FLAG_OPERATION:       DCU addition overflow or subtraction underflow flag
 *           @arg DCU_FLAG_DATA0_LS_DATA2:  DCU DATA0 < DATA2 flag
 *           @arg DCU_FLAG_DATA0_EQ_DATA2:  DCU DATA0 = DATA2 flag
 *           @arg DCU_FLAG_DATA0_GT_DATA2:  DCU DATA0 > DATA2 flag
 *           @arg DCU_FLAG_DATA0_LS_DATA1:  DCU DATA0 < DATA1 flag
 *           @arg DCU_FLAG_DATA0_EQ_DATA1:  DCU DATA0 = DATA1 flag
 *           @arg DCU_FLAG_DATA0_GT_DATA1:  DCU DATA0 > DATA1 flag
 *           @arg DCU_FLAG_SAWTOOTH_WAVE_RELOAD:  DCU sawtooth wave mode reload flag
 *           @arg DCU_FLAG_TRIANGLE_WAVE_BOTTOM:  DCU triangle wave mode bottom flag
 *           @arg DCU_FLAG_TRIANGLE_WAVE_TOP: DCU triangle wave mode top flag
 * @retval Returned value can be one of the following values:
 *           @arg Set                         Flag is set.
 *           @arg Reset                       Flag is reset or enStatus is invalid.
 */
en_flag_status_t DCU_GetStatus(const M4_DCU_TypeDef *DCUx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT((IS_DCU_WAVE_FUNC_UNIT(DCUx) && IS_DCU_WAVE_FUNC_UNIT_FLAG(u32Flag)) || \
               (IS_DCU_BASE_FUNC_UNIT(DCUx) && IS_DCU_BASE_FUNC_UNIT_FLAG(u32Flag)));

    return READ_REG32_BIT(DCUx->FLAG, u32Flag) ? Set : Reset;
}

/**
 * @brief  Clear DCU flag.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] u32Flag                 The specified DCU flag
 *         This parameter can be one of the following values:
 *           @arg DCU_FLAG_OPERATION:       DCU addition overflow or subtraction underflow flag
 *           @arg DCU_FLAG_DATA0_LS_DATA2:  DCU DATA0 < DATA2 flag
 *           @arg DCU_FLAG_DATA0_EQ_DATA2:  DCU DATA0 = DATA2 flag
 *           @arg DCU_FLAG_DATA0_GT_DATA2:  DCU DATA0 > DATA2 flag
 *           @arg DCU_FLAG_DATA0_LS_DATA1:  DCU DATA0 < DATA1 flag
 *           @arg DCU_FLAG_DATA0_EQ_DATA1:  DCU DATA0 = DATA1 flag
 *           @arg DCU_FLAG_DATA0_GT_DATA1:  DCU DATA0 > DATA1 flag
 *           @arg DCU_FLAG_SAWTOOTH_WAVE_RELOAD:  DCU sawtooth wave mode reload flag
 *           @arg DCU_FLAG_TRIANGLE_WAVE_BOTTOM:  DCU triangle wave mode bottom flag
 *           @arg DCU_FLAG_TRIANGLE_WAVE_TOP: DCU triangle wave mode top flag
 * @retval None
 */
void DCU_ClearStatus(M4_DCU_TypeDef *DCUx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT((IS_DCU_WAVE_FUNC_UNIT(DCUx) && IS_DCU_WAVE_FUNC_UNIT_FLAG(u32Flag)) || \
               (IS_DCU_BASE_FUNC_UNIT(DCUx) && IS_DCU_BASE_FUNC_UNIT_FLAG(u32Flag)));

    WRITE_REG32(DCUx->FLAGCLR, u32Flag);
}

/**
 * @brief  Enable/disable DCU the specified interrupt source.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] u32IntCategory          DCU interrupt categorye
 *         This parameter can be one of the following values:
 *           @arg DCU_INT_OP:           DCU operation result(overflow/underflow) interrupt
 *           @arg DCU_INT_WAVE_MD:      DCU wave mode(sawtooth/triangle wave mode) interrupt
 *           @arg DCU_INT_CMP_WIN:      DCU comparison(window) interrupt
 *           @arg DCU_INT_CMP_NON_WIN:  DCU comparison(non-window) interrupt
 * @param  [in] u32IntType              DCU interrupt type
 *         This parameter can be one of the following case:
 *         a. this parameter can be one of the following values when u16IntType = DCU_INT_OP:
 *           @arg DCU_INT_OP_UDF_OVF: DCU addition overflow or subtraction underflow interrupt
 *         b. this parameter can be any composed value of the following values when u16IntType = DCU_INT_CMP_WIN:
 *           @arg DCU_INT_CMP_WIN_INSIDE:DCU comparison(DATA2 <= DATA0 <= DATA1) interrupt
 *           @arg DCU_INT_CMP_WIN_OUTSIDE: DCU comparison(DATA0 < DATA2 & DATA0 > DATA1 ) interrupt
 *           @note Only one of the window inside and outside interrupt is valid.
 *           @note Both of the window inside and outside interrupt is disabled and the window interrupt is invalid.
 *           @note Both of the window inside and outside interrupt is enabled and the compare mode interrupt is invalid.
 *         c. this parameter can be any composed value of the following values when u16IntType = DCU_INT_CMP_NON_WIN:
 *           @arg DCU_INT_CMP_DATA0_LS_DATA2: DCU DATA0 < DATA2 interrupt
 *           @arg DCU_INT_CMP_DATA0_EQ_DATA2: DCU DATA0 = DATA2 interrupt
 *           @arg DCU_INT_CMP_DATA0_GT_DATA2: DCU DATA0 > DATA2 interrupt
 *           @arg DCU_INT_CMP_DATA0_LS_DATA1: DCU DATA0 < DATA1 interrupt
 *           @arg DCU_INT_CMP_DATA0_EQ_DATA1: DCU DATA0 = DATA1 interrupt
 *           @arg DCU_INT_CMP_DATA0_GT_DATA1: DCU DATA0 > DATA1 interrupt
 *           @note Both of the window inside and outside interrupt is disabled and the compare non-window interrupt is valid.
 *         d. this parameter can be any composed value of the following values when u16IntType = DCU_INT_WAVE_MD:
 *           @arg DCU_INT_WAVE_SAWTOOTH_RELOAD: DCU sawtooth wave mode reload interrupt
 *           @arg DCU_INT_WAVE_TRIANGLE_BOTTOM: DCU triangle wave mode bottom interrupt
 *           @arg DCU_INT_WAVE_TRIANGLE_TOP:    DCU triangle wave mode top interrupt
 * @param  [in] enNewState              The function new state.
 *           @arg  This parameter can be: Enable or Disable.
 * @retval None
 * @note   The DCU sawtooth/triangle wave mode is supported by M4_DCU1/2/3/4.
 */
void DCU_IntCmd(M4_DCU_TypeDef *DCUx,
                uint32_t u32IntCategory,
                uint32_t u32IntType,
                en_functional_state_t enNewState)
{
    uint32_t u32Type;

    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_INT_CATEGORY(u32IntCategory));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DCU_INT_OP == u32IntCategory)
    {
        DDL_ASSERT(IS_DCU_INT_OP(u32IntType));
        u32Type = (u32IntType & DCU_INT_OP_UDF_OVF);
    }
    else if (DCU_INT_CMP_WIN == u32IntCategory)
    {
        DDL_ASSERT(IS_DCU_INT_CMP_WIN(u32IntType));
        u32Type = (u32IntType & DCU_INT_CMP_WIN_ALL);
    }
    else if (DCU_INT_CMP_NON_WIN == u32IntCategory)
    {
        DDL_ASSERT(IS_DCU_INT_CMP_NON_WIN(u32IntType));
        u32Type = (u32IntType & DCU_INT_CMP_NON_WIN_ALL);
    }
    else
    {
        DDL_ASSERT(IS_DCU_WAVE_FUNC_UNIT(DCUx));
        DDL_ASSERT(IS_DCU_INT_WAVE_MD(u32IntType));
        u32Type = (u32IntType & DCU_INT_WAVE_MD_ALL);
    }

    if (Enable == enNewState)
    {
        SET_REG32_BIT(DCUx->INTEVTSEL, u32Type);
    }
    else
    {
        CLEAR_REG32_BIT(DCUx->INTEVTSEL, u32Type);
    }
}

/**
 * @brief  Enable or disable DCU interrupt funtion.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] enNewState              The function new state.
 *           @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void DCU_GlobalIntCmd(M4_DCU_TypeDef *DCUx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(DCUx->CTL, DCU_CTL_INTEN);
    }
    else
    {
        CLEAR_REG32_BIT(DCUx->CTL, DCU_CTL_INTEN);
    }
}

/**
 * @brief  AOS common trigger function config for DCU
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] u32ComTrig              Common trigger event.
 *         This parameter can be one of the following values:
 *           @arg  DCU_COM_TRIG1:       Common trigger event 1.
 *           @arg  DCU_COM_TRIG2:       Common trigger event 2.
 * @param  [in] enNewState              New state of common trigger function.
 * @retval None
 * @note This register belongs to AOS module, please ensure enable it in advance.
 */
void DCU_ComTriggerCmd(M4_DCU_TypeDef *DCUx,
                            uint32_t u32ComTrig,
                            en_functional_state_t enNewState)
{
    __IO uint32_t *const TRGSELx = DCU_TRGSELx(DCUx);

    if (NULL != TRGSELx)
    {
        DDL_ASSERT(IS_DCU_COM_TRIG(u32ComTrig));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        if (Enable == enNewState)
        {
            SET_REG32_BIT(*TRGSELx, u32ComTrig);
        }
        else
        {
            CLEAR_REG32_BIT(*TRGSELx, u32ComTrig);
        }
    }
}

/**
 * @brief  Set the specified event trigger source for DCU.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] enEventSrc              The trigger external event source source.
 *           @arg This parameter can be any value of @ref en_event_src_t
 * @retval None
 * @note   This register belongs to AOS module, please ensure enable it in advance.
 */
void DCU_SetTriggerSrc(const M4_DCU_TypeDef *DCUx, en_event_src_t enEventSrc)
{
    __IO uint32_t *const TRGSELx = DCU_TRGSELx(DCUx);

    if (NULL != TRGSELx)
    {
        MODIFY_REG32(*TRGSELx, AOS_DCU_1_TRGSEL_TRGSEL, enEventSrc);
    }
}

/**
 * @brief  Read DCU register DATA for byte.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] u32DataIndex            DCU data register index
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA0_IDX:        DCU DATA0
 *           @arg DCU_DATA1_IDX:        DCU DATA1
 *           @arg DCU_DATA2_IDX:        DCU DATA2
 * @retval DCU register DATA value for byte
 */
uint8_t DCU_ReadData8(const M4_DCU_TypeDef *DCUx, uint32_t u32DataIndex)
{
    __IO uint8_t *DATA;

    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    DATA = (__IO uint8_t *)DATA_REG_ADDR(DCUx, u32DataIndex);
    return READ_REG8(*DATA);
}

/**
 * @brief  Write DCU register DATA for byte.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] u32DataIndex            DCU data register index
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA0_IDX:        DCU DATA0
 *           @arg DCU_DATA1_IDX:        DCU DATA1
 *           @arg DCU_DATA2_IDX:        DCU DATA2
 * @param  [in] u8Data                  The data to write.
 * @retval None
 */
void DCU_WriteData8(M4_DCU_TypeDef *DCUx,
                    uint32_t u32DataIndex,
                    uint8_t u8Data)
{
    __IO uint8_t *DATA;

    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    DATA = (__IO uint8_t *)DATA_REG_ADDR(DCUx, u32DataIndex);
    WRITE_REG8(*DATA, u8Data);
}

/**
 * @brief  Read DCU register DATA for half-word.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] u32DataIndex            DCU data register index
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA0_IDX:        DCU DATA0
 *           @arg DCU_DATA1_IDX:        DCU DATA1
 *           @arg DCU_DATA2_IDX:        DCU DATA2
 * @retval DCU register DATA value for half-word
 */
uint16_t DCU_ReadData16(const M4_DCU_TypeDef *DCUx, uint32_t u32DataIndex)
{
    __IO uint16_t *DATA;

    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    DATA = (__IO uint16_t *)DATA_REG_ADDR(DCUx, u32DataIndex);
    return READ_REG16(*DATA);
}

/**
 * @brief  Write DCU register DATA for half-word.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] u32DataIndex            DCU data register index
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA0_IDX:        DCU DATA0
 *           @arg DCU_DATA1_IDX:        DCU DATA1
 *           @arg DCU_DATA2_IDX:        DCU DATA2
 * @param  [in] u16Data                 The data to write.
 * @retval None
 */
void DCU_WriteData16(M4_DCU_TypeDef *DCUx,
                        uint32_t u32DataIndex,
                        uint16_t u16Data)
{
    __IO uint16_t *DATA;

    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    DATA = (__IO uint16_t *)DATA_REG_ADDR(DCUx, u32DataIndex);
    WRITE_REG16(*DATA, u16Data);
}

/**
 * @brief  Read DCU register DATA for word.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] u32DataIndex            DCU data register index
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA0_IDX:        DCU DATA0
 *           @arg DCU_DATA1_IDX:        DCU DATA1
 *           @arg DCU_DATA2_IDX:        DCU DATA2
 * @retval DCU register DATA value for word
 */
uint32_t DCU_ReadData32(const M4_DCU_TypeDef *DCUx, uint32_t u32DataIndex)
{
    __IO uint32_t *DATA;

    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    DATA = (__IO uint32_t *)DATA_REG_ADDR(DCUx, u32DataIndex);
    return READ_REG32(*DATA);
}

/**
 * @brief  Write DCU register DATA0 for word.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @param  [in] u32DataIndex            DCU data register index
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA0_IDX:        DCU DATA0
 *           @arg DCU_DATA1_IDX:        DCU DATA1
 *           @arg DCU_DATA2_IDX:        DCU DATA2
 * @param  [in] u32Data                 The data to write.
 * @retval None
 */
void DCU_WriteData32(M4_DCU_TypeDef *DCUx,
                        uint32_t u32DataIndex,
                        uint32_t u32Data)
{
    __IO uint32_t *DATA;

    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_REG(u32DataIndex));

    DATA = (__IO uint32_t *)DATA_REG_ADDR(DCUx, u32DataIndex);
    WRITE_REG32(*DATA, u32Data);
}

/**
 * @}
 */

/**
 * @defgroup DCU_Local_Functions DCU Local Functions
 * @{
 */

/**
 * @brief  Get DCU trigger selection register of the specified DCU unit.
 * @param  [in] DCUx                    Pointer to DCU instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_DCU1:              DCU unit 1 instance register base
 *           @arg M4_DCU2:              DCU unit 2 instance register base
 *           @arg M4_DCU3:              DCU unit 3 instance register base
 *           @arg M4_DCU4:              DCU unit 4 instance register base
 *           @arg M4_DCU5:              DCU unit 5 instance register base
 *           @arg M4_DCU6:              DCU unit 6 instance register base
 *           @arg M4_DCU7:              DCU unit 7 instance register base
 *           @arg M4_DCU8:              DCU unit 8 instance register base
 * @retval DCU trigger selection register
 */
static __IO uint32_t* DCU_TRGSELx(const M4_DCU_TypeDef *DCUx)
{
    __IO uint32_t *TRGSELx;

    if ((M4_DCU1 == DCUx) || (M4_DCU5 == DCUx))
    {
        TRGSELx = &M4_AOS->DCU_1_TRGSEL;
    }
    else if ((M4_DCU2 == DCUx) || (M4_DCU6 == DCUx))
    {
        TRGSELx = &M4_AOS->DCU_2_TRGSEL;
    }
    else if ((M4_DCU3 == DCUx) || (M4_DCU7 == DCUx))
    {
        TRGSELx = &M4_AOS->DCU_3_TRGSEL;
    }
    else if ((M4_DCU4 == DCUx) || (M4_DCU8 == DCUx))
    {
        TRGSELx = &M4_AOS->DCU_4_TRGSEL;
    }
    else
    {
        TRGSELx = NULL;
    }

    return TRGSELx;
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
