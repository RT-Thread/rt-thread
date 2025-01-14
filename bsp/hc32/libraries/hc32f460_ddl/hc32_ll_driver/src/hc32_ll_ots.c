/**
 *******************************************************************************
 * @file  hc32_ll_ots.c
 * @brief This file provides firmware functions to manage the OTS.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             API fixed: OTS_CalculateTemp()
   2023-06-30       CDT             Modify typo
                                    Modify API OTS_DeInit()
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
#include "hc32_ll_ots.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_OTS OTS
 * @brief OTS Driver Library
 * @{
 */

#if (LL_OTS_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup OTS_Local_Macros OTS Local Macros
 * @{
 */

/**
 * @defgroup OTS_Configuration_Bit_Mask OTS Configuration Bit Mask
 * @{
 */
#define OTS_CTL_INIT_MSK            (OTS_CTL_OTSCK | OTS_CTL_TSSTP)
/**
 * @}
 */

/**
 * @defgroup OTS_Factor OTS Factor
 * @{
 */
#define OTS_DR1_FACTOR              (1.0F)

#define OTS_DR2_FACTOR              (1.0F)
#define OTS_ECR_XTAL_FACTOR         (1.0F)
/**
 * @}
 */

/**
 * @defgroup OTS_Check_Parameters_Validity OTS check parameters validity
 * @{
 */
#define IS_OTS_CLK(x)               (((x) == OTS_CLK_HRC) || ((x) == OTS_CLK_XTAL))

#define IS_OTS_AUTO_OFF_EN(x)       (((x) == OTS_AUTO_OFF_DISABLE) || ((x) == OTS_AUTO_OFF_ENABLE))
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
/**
 * @defgroup OTS_Local_Variables OTS Local Variables
 * @{
 */
static float32_t m_f32SlopeK  = 0.0F;
static float32_t m_f32OffsetM = 0.0F;
/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup OTS_Global_Functions OTS Global Functions
 * @{
 */

/**
 * @brief  Initializes OTS according to the specified parameters in the structure stc_ots_init_t.
 * @param  [in]  pstcOTSInit            Pointer to a stc_ots_init_t structure value that
 *                                      contains the configuration information for OTS.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_INVD_PARAM:       pstcOTSInit == NULL.
 */
int32_t OTS_Init(const stc_ots_init_t *pstcOTSInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcOTSInit != NULL) {
        DDL_ASSERT(IS_OTS_CLK(pstcOTSInit->u16ClockSrc));
        DDL_ASSERT(IS_OTS_AUTO_OFF_EN(pstcOTSInit->u16AutoOffEn));

        /* Stop OTS sampling. */
        OTS_Stop();
        WRITE_REG16(CM_OTS->CTL, (pstcOTSInit->u16ClockSrc | pstcOTSInit->u16AutoOffEn));
        m_f32SlopeK  = pstcOTSInit->f32SlopeK;
        m_f32OffsetM = pstcOTSInit->f32OffsetM;

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Set a default value for OTS initialization structure.
 * @param  [in]  pstcOTSInit            Pointer to a stc_ots_init_t structure that
 *                                      contains configuration information.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_INVD_PARAM:       pstcOTSInit == NULL.
 */
int32_t OTS_StructInit(stc_ots_init_t *pstcOTSInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcOTSInit != NULL) {
        pstcOTSInit->u16ClockSrc  = OTS_CLK_HRC;
        pstcOTSInit->f32SlopeK    = 0.0F;
        pstcOTSInit->f32OffsetM   = 0.0F;
        pstcOTSInit->u16AutoOffEn = OTS_AUTO_OFF_ENABLE;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  De-initializes OTS peripheral. Reset the registers of OTS.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   De-Initialize success.
 */
int32_t OTS_DeInit(void)
{
    /* Stop OTS. */
    OTS_Stop();
    /* Set the value of all registers to the reset value. */
    WRITE_REG16(CM_OTS->CTL, 0U);
    WRITE_REG16(CM_OTS->DR1, 0U);
    WRITE_REG16(CM_OTS->DR2, 0U);
    WRITE_REG16(CM_OTS->ECR, 0U);
    return LL_OK;
}

/**
 * @brief  Get temperature via normal mode.
 * @param  [out] pf32Temp               Pointer to a float32_t type address that the temperature value to be stored.
 * @param  [in]  u32Timeout             Timeout value.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Works timeout.
 *           - LL_ERR_INVD_PARAM:       pf32Temp == NULL.
 */
int32_t OTS_Polling(float32_t *pf32Temp, uint32_t u32Timeout)
{
    __IO uint32_t u32TimeCount = u32Timeout;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pf32Temp != NULL) {
        i32Ret = LL_ERR_TIMEOUT;
        OTS_Start();
        while (u32TimeCount-- != 0U) {
            if (READ_REG32(bCM_OTS->CTL_b.OTSST) == 0UL) {
                *pf32Temp = OTS_CalculateTemp();
                i32Ret = LL_OK;
                break;
            }
        }
        OTS_Stop();
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable the OTS interrupt.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void OTS_IntCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    WRITE_REG32(bCM_OTS->CTL_b.OTSIE, enNewState);
}

/**
 * @brief  OTS scaling experiment. Get the value of the data register at the specified temperature to calculate K and M.
 * @param  [out] pu16Dr1:               Pointer to an address to store the value of data register 1.
 * @param  [out] pu16Dr2:               Pointer to an address to store the value of data register 2.
 * @param  [out] pu16Ecr:               Pointer to an address to store the value of register ECR.
 * @param  [out] pf32A:                 Pointer to an address to store the parameter A.
 * @param  [in]  u32Timeout:            Timeout value.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Works timeout.
 *           - LL_ERR_INVD_PARAM:       If one the following cases matches:
 *                                      - pu16Dr1 == NULL.
 *                                      - pu16Dr2 == NULL.
 *                                      - pu16Ecr == NULL.
 *                                      - pf32A == NULL.
 */
int32_t OTS_ScalingExperiment(uint16_t *pu16Dr1, uint16_t *pu16Dr2,
                              uint16_t *pu16Ecr, float32_t *pf32A,
                              uint32_t u32Timeout)
{
    float32_t f32Dr1;
    float32_t f32Dr2;
    float32_t f32Ecr;
    __IO uint32_t u32TimeCount = u32Timeout;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != pu16Dr1) && (NULL != pu16Dr2) && \
        (NULL != pu16Ecr) && (NULL != pf32A)) {
        i32Ret = LL_ERR_TIMEOUT;
        OTS_Start();
        while (u32TimeCount-- != 0U) {
            if (READ_REG32(bCM_OTS->CTL_b.OTSST) == 0UL) {
                i32Ret = LL_OK;
                break;
            }
        }
        OTS_Stop();

        if (i32Ret == LL_OK) {
            *pu16Dr1 = READ_REG16(CM_OTS->DR1);
            *pu16Dr2 = READ_REG16(CM_OTS->DR2);

            f32Dr1 = (float32_t)(*pu16Dr1);
            f32Dr2 = (float32_t)(*pu16Dr2);

            if (READ_REG8_BIT(CM_OTS->CTL, OTS_CTL_OTSCK) == OTS_CLK_HRC) {
                *pu16Ecr = READ_REG16(CM_OTS->ECR);
                f32Ecr   = (float32_t)(*pu16Ecr);
            } else {
                *pu16Ecr = 1U;
                f32Ecr   = OTS_ECR_XTAL_FACTOR;
            }

            if ((f32Dr1 != 0.0F) && (f32Dr2 != 0.0F) && (f32Ecr != 0.0F)) {
                *pf32A = ((OTS_DR1_FACTOR / f32Dr1) - (OTS_DR2_FACTOR / f32Dr2)) * f32Ecr;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Calculate the temperature value.
 * @param  None
 * @retval A float32_t type value of temperature.
 */
float32_t OTS_CalculateTemp(void)
{
    float32_t f32Ret = -300.0F;
    uint16_t u16Dr1  = READ_REG16(CM_OTS->DR1);
    uint16_t u16Dr2  = READ_REG16(CM_OTS->DR2);
    uint16_t u16Ecr  = READ_REG16(CM_OTS->ECR);
    float32_t f32Dr1 = (float32_t)u16Dr1;
    float32_t f32Dr2 = (float32_t)u16Dr2;
    float32_t f32Ecr = (float32_t)u16Ecr;

    if (READ_REG8_BIT(CM_OTS->CTL, OTS_CTL_OTSCK) == OTS_CLK_XTAL) {
        f32Ecr = OTS_ECR_XTAL_FACTOR;
    }

    if ((f32Dr1 != 0.0F) && (f32Dr2 != 0.0F) && (f32Ecr != 0.0F)) {
        f32Ret = m_f32SlopeK * ((OTS_DR1_FACTOR / f32Dr1) - (OTS_DR2_FACTOR / f32Dr2)) * f32Ecr + m_f32OffsetM;
    }

    return f32Ret;
}

/**
 * @}
 */

#endif /* LL_OTS_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
