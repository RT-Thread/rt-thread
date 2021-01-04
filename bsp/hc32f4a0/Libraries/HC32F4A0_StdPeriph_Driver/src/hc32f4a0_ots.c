/**
 *******************************************************************************
 * @file  hc32f4a0_ots.c
 * @brief This file provides firmware functions to manage the OTS.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-08-11       Wuze            First version
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
#include "hc32f4a0_ots.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_OTS OTS
 * @brief OTS Driver Library
 * @{
 */

#if (DDL_OTS_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup OTS_Configuration_Bit_Mask OTS Configuration Bit Mask
 * @{
 */
#define OTS_CTL_INIT_MSK            (OTS_CTL_OTSCK | OTS_CTL_TSSTP)
#define OTS_COM_TRIG_MSK            (OTS_COM_TRIG1 | OTS_COM_TRIG2)
/**
 * @}
 */

/**
 * @defgroup OTS_Ext_Reg_Address OTS Extension Register Address
 * @{
 */
#define OTS_PDR1_ADDR               (0x40010600UL + 0xE0UL)
#define OTS_PDR2_ADDR               (0x40010600UL + 0xF4UL)
#define OTS_PDR3_ADDR               (0x40010600UL + 0xF8UL)
#define OTS_CR2_ADDR                (0x4004A800UL + 0x10UL)
#define OTS_TMR_ADDR                (0x4004A800UL + 0x12UL)
/**
 * @}
 */

/**
 * @defgroup OTS_Check_Parameters_Validity OTS check parameters validity
 * @{
 */
#define IS_OTS_CLK(x)                                                          \
(   ((x) == OTS_CLK_HRC)                    ||                                 \
    ((x) == OTS_CLK_XTAL))

#define IS_OTS_AUTO_OFF_EN(x)                                                  \
(   ((x) == OTS_AUTO_OFF_DISABLE)           ||                                 \
    ((x) == OTS_AUTO_OFF_ENABLE))

#define IS_OTS_COM_TRIGGER(x)                                                  \
(   ((x) != 0U)                             &&                                 \
    (((x) | OTS_COM_TRIG_MSK) == OTS_COM_TRIG_MSK))

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void OTS_GetDfltPara(const stc_ots_init_t *pstcInit);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static float32_t m_f32SlopeK  = 0.0f;
static float32_t m_f32OffsetM = 0.0f;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup OTS_Global_Functions OTS Global Functions
 * @{
 */

/**
 * @brief  Initializes OTS according to the specified parameters in the structure stc_ots_init_t.
 * @param  [in]  pstcInit               Pointer to a stc_ots_init_t structure value that
 *                                      contains the configuration information for OTS.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       pstcInit == NULL.
 */
en_result_t OTS_Init(const stc_ots_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        DDL_ASSERT(IS_OTS_CLK(pstcInit->u16ClkSrc));
        DDL_ASSERT(IS_OTS_AUTO_OFF_EN(pstcInit->u16AutoOffEn));

        /* Stop OTS sampling. */
        OTS_Stop();

        MODIFY_REG16(M4_OTS->CTL, OTS_CTL_INIT_MSK, (pstcInit->u16ClkSrc|pstcInit->u16AutoOffEn));

        if ((pstcInit->f32SlopeK == 0.0f) && (pstcInit->f32OffsetM == 0.0f))
        {
            OTS_GetDfltPara(pstcInit);
        }
        else
        {
            m_f32SlopeK  = pstcInit->f32SlopeK;
            m_f32OffsetM = pstcInit->f32OffsetM;
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for OTS initialization structure.
 * @param  [in]  pstcInit               Pointer to a stc_ots_init_t structure that
 *                                      contains configuration information.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       pstcInit == NULL.
 */
en_result_t OTS_StructInit(stc_ots_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        pstcInit->u16ClkSrc    = OTS_CLK_HRC;
        pstcInit->f32SlopeK    = 0.0f;
        pstcInit->f32OffsetM   = 0.0f;
        pstcInit->u16AutoOffEn = OTS_AUTO_OFF_ENABLE;

        pstcInit->stcParaCond.u16ClkFreq = 8U;
        pstcInit->stcParaCond.u8T1 = OTS_COND_T25;
        pstcInit->stcParaCond.u8T2 = OTS_COND_T125;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initializes OTS peripheral. Reset the registers of OTS.
 * @param  None
 * @retval None
 */
void OTS_DeInit(void)
{
    /* Stop OTS. */
    OTS_Stop();
    /* Set the value of all registers to the reset value. */
    WRITE_REG16(M4_OTS->CTL, 0U);
    WRITE_REG16(M4_OTS->DR1, 0U);
    WRITE_REG16(M4_OTS->DR2, 0U);
    WRITE_REG16(M4_OTS->ECR, 0U);
}

/**
 * @brief  Get temperature via normal mode.
 * @param  [out] pf32Temp               Pointer to a float32_t type address that the temperature value to be stored.
 * @param  [in]  u32Timeout             Timeout value.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Works timeout.
 *   @arg  ErrorInvalidParameter:       pf32Temp == NULL.
 */
en_result_t OTS_Polling(float32_t *pf32Temp, uint32_t u32Timeout)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pf32Temp != NULL)
    {
        enRet = ErrorTimeout;

        OTS_Start();
        do
        {
            if (READ_REG32(bM4_OTS->CTL_b.OTSST) == 0UL)
            {
                *pf32Temp = OTS_CalculateTemp();
                enRet = Ok;
                break;
            }
        } while (u32Timeout-- != 0UL);
        OTS_Stop();
    }

    return enRet;
}

/**
 * @brief  Enable or disable the OTS interrutp.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg Enable:                       Enable the OTS interrupt.
 *   @arg Disable:                      Disable the OTS interrupt.
 * @retval None
 */
void OTS_IntCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    WRITE_REG32(bM4_OTS->CTL_b.OTSIE, enNewState);
}

/**
 * @brief  Specifies the event which is used to trigger OTS start.
 * @param  [in]  enEvent                An event of other peripheral.
 *                                      This parameter can be a value of @ref en_event_src_t except 'EVT_OTS'.
 * @retval None
 */
void OTS_SetTriggerSrc(en_event_src_t enEvent)
{
    MODIFY_REG32(M4_AOS->OTS_TRG, AOS_OTS_TRG_TRGSEL, enEvent);
}

/**
 * @brief  Enable or disable common trigger event to start OTS.
 * @param  [in]  u32ComTrig             Common trigger event enable bit mask.
 *                                      This parameter can be a value of @ref OTS_Common_Trigger_Sel
 *   @arg  OTS_COM_TRIG1:               Common trigger 1.
 *   @arg  OTS_COM_TRIG2:               Common trigger 2.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg Enable:                       Enable the specified common trigger.
 *   @arg Disable:                      Disable the specified common trigger.
 * @retval None
 */
void OTS_ComTriggerCmd(uint32_t u32ComTrig, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_OTS_COM_TRIGGER(u32ComTrig));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == Enable)
    {
        SET_REG32_BIT(M4_AOS->OTS_TRG, u32ComTrig);
    }
    else
    {
        CLEAR_REG32_BIT(M4_AOS->OTS_TRG, u32ComTrig);
    }
}

/**
 * @brief  OTS scaling experiment. Get the value of the data register at the specified temperature to calculate K and M.
 * @param  [out] pu16Dr1:               Pointer to an address to store the value of data register 1.
 * @param  [out] pu16Dr2:               Pointer to an address to store the value of data register 2.
 * @param  [out] pu16Ecr:               Pointer to an address to store the value of register ECR.
 * @param  [out] pf32A:                 Pointer to an address to store the parameter A.
 * @param  [in]  u32Timeout:            Timeout value.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Works timeout.
 *   @arg  ErrorInvalidParameter:      -pu16Dr1 == NULL.
 *                                     -pu16Dr2 == NULL.
 *                                     -pu16Ecr == NULL.
 *                                     -pf32A == NULL.
 */
en_result_t OTS_ScalingExperiment(uint16_t *pu16Dr1, uint16_t *pu16Dr2, \
                                  uint16_t *pu16Ecr, float32_t *pf32A,  \
                                  uint32_t u32Timeout)
{
    float32_t f32Dr1;
    float32_t f32Dr2;
    float32_t f32Ecr;
    en_result_t enRet = ErrorInvalidParameter;

    if ((NULL != pu16Dr1) && (NULL != pu16Dr2) && \
        (NULL != pu16Ecr) && (NULL != pf32A))
    {
        enRet = ErrorTimeout;
        OTS_Start();
        do
        {
            if (READ_REG32(bM4_OTS->CTL_b.OTSST) == 0UL)
            {
                enRet = Ok;
                break;
            }
        } while (u32Timeout-- != 0UL);
        OTS_Stop();

        if (enRet == Ok)
        {
            *pu16Dr1 = READ_REG16(M4_OTS->DR1);
            *pu16Dr2 = READ_REG16(M4_OTS->DR2);

            f32Dr1 = (float32_t)(*pu16Dr1);
            f32Dr2 = (float32_t)(*pu16Dr2);

            if (READ_REG8_BIT(M4_OTS->CTL, OTS_CTL_OTSCK) == OTS_CLK_HRC)
            {
                *pu16Ecr = READ_REG16(M4_OTS->ECR);
                f32Ecr   = (float32_t)(*pu16Ecr);
            }
            else
            {
                *pu16Ecr = 1U;
                f32Ecr   = 1.0f;
            }

            if ((*pu16Dr1 != 0U) && (*pu16Dr2 != 0U) && (*pu16Ecr != 0U))
            {
                *pf32A = ((1.7f / f32Dr1) - (1.0f / f32Dr2)) * f32Ecr;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Calculate the value of temperature.
 * @param  None
 * @retval A float32_t type value of temperature value.
 */
float OTS_CalculateTemp(void)
{
    float32_t f32Ret = 0.0f;
    uint16_t u16Dr1  = READ_REG16(M4_OTS->DR1);
    uint16_t u16Dr2  = READ_REG16(M4_OTS->DR2);
    uint16_t u16Ecr  = READ_REG16(M4_OTS->ECR);
    float32_t f32Dr1 = (float32_t)u16Dr1;
    float32_t f32Dr2 = (float32_t)u16Dr2;
    float32_t f32Ecr = (float32_t)u16Ecr;

    if (READ_REG8_BIT(M4_OTS->CTL, OTS_CTL_OTSCK) == OTS_CLK_XTAL)
    {
        f32Ecr = 1.0f;
    }

    if ((u16Dr1 != 0U) && (u16Dr2 != 0U) && (u16Ecr != 0U))
    {
        f32Ret = m_f32SlopeK * ((1.7f / f32Dr1) - (1.0f / f32Dr2)) * f32Ecr + m_f32OffsetM;
    }

    return f32Ret;
}

/**
 * @}
 */

/**
 * @addtogroup OTS_Local_Functions OTS Local Functions
 * @{
 */

/**
 * @brief  Get built-in slope K and offset M.
 * @param  [in]  pstcInit               Pointer to a stc_ots_init_t structure value that
 *                                      contains the configuration information for OTS.
 * @retval None
 */
static void OTS_GetDfltPara(const stc_ots_init_t *pstcInit)
{
#define OTS_SCAL_T1         (ai16Temp[pstcInit->stcParaCond.u8T1])
#define OTS_SCAL_T2         (ai16Temp[pstcInit->stcParaCond.u8T2])
#define OTS_SCAL_A1         (af32A[0U])
#define OTS_SCAL_A2         (af32A[1U])

    uint8_t i;
    int16_t ai16Temp[] = {-40, 25, 125};
    uint32_t au32PDRAddr[] = {OTS_PDR3_ADDR, OTS_PDR1_ADDR, OTS_PDR2_ADDR};
    uint32_t au32PDR[2U];
    uint32_t u16D1;
    uint32_t u16D2;
    float32_t f32D1;
    float32_t f32D2;
    float32_t af32A[2U];
    float32_t f32Ehrc = 1.0f;
    float32_t f32ClkFactor = (float32_t)pstcInit->stcParaCond.u16ClkFreq / 8.0f;

    au32PDR[0U] = RW_MEM32(au32PDRAddr[pstcInit->stcParaCond.u8T1]);
    au32PDR[1U] = RW_MEM32(au32PDRAddr[pstcInit->stcParaCond.u8T2]);

    if (pstcInit->u16ClkSrc == OTS_CLK_HRC)
    {
        f32Ehrc = (float32_t)pstcInit->stcParaCond.u16ClkFreq / 0.032768f;
    }

    for (i=0U; i<2U; i++)
    {
        u16D1 = (uint16_t)au32PDR[i];
        u16D2 = (uint16_t)(au32PDR[i] >> 16U);
        f32D1 = ((float32_t)u16D1) * f32ClkFactor;
        f32D2 = ((float32_t)u16D2) * f32ClkFactor;
        af32A[i] = ((1.7f / f32D1) - (1.0f / f32D2)) * f32Ehrc;
    }
    m_f32SlopeK  = ((float32_t)OTS_SCAL_T2 - (float32_t)OTS_SCAL_T1) / (OTS_SCAL_A2 - OTS_SCAL_A1);
    m_f32OffsetM = (float32_t)OTS_SCAL_T2 - (m_f32SlopeK * OTS_SCAL_A2);
}

/**
 * @}
 */

#endif /* DDL_OTS_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
