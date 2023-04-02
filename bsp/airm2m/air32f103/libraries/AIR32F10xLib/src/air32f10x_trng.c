/************************ (C) COPYRIGHT Megahuntmicro *************************
 * @file                : air32f10x_trng.c
 * @author              : Megahuntmicro
 * @version             : V1.0.0
 * @date                :
 * @brief               :
 *****************************************************************************/

/* Includes -----------------------------------------------------------------*/
#include "air32f10x_trng.h"

/**
  * @method TRNG_Get
  * @brief
  * @param  rand
  * @retval
  */
uint32_t TRNG_Get(uint32_t TRNG_Data[4])
{
    uint32_t ret = 1;

    if (TRNG->RNG_CSR & TRNG_RNG_CSR_S128_TRNG0_Mask)
    {
        TRNG_Data[0] = TRNG->RNG_DATA;
        TRNG_Data[1] = TRNG->RNG_DATA;
        TRNG_Data[2] = TRNG->RNG_DATA;
        TRNG_Data[3] = TRNG->RNG_DATA;
        ret = 0;
    }
    return ret;
}

/**
  * @method TRNG_SetPseudoRandom
  * @brief
  * @param  PseudoRandom
  * @retval
  */
void TRNG_SetPseudoRandom(uint32_t TRNG_PseudoRandom)
{
    TRNG->RNG_PN = TRNG_PseudoRandom;
}

/**
  * @method TRNG_DirectOutANA
  * @brief
  * @param  NewState
  * @retval
  */
void TRNG_DirectOutANA(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        TRNG->RNG_AMA |= TRNG_RNG_AMA_OUT_TRNG0_Mask;
    }
    else
    {
        TRNG->RNG_AMA &= ~TRNG_RNG_AMA_OUT_TRNG0_Mask;
    }
}

/**
  * @method TRNG_SelectPDSource
  * @brief
  * @param  sourcex
  * @retval
  */
void TRNG_SelectPDSource(TRNG_PDSourceTypeDef TRNG_Source)
{
    assert_param(IS_TRNG_PDSource(TRNG_Source));
    TRNG->RNG_AMA = (TRNG->RNG_AMA & ~(0xF << 12)) | (TRNG_Source << 12);
}


/**
  * @method TRNG_ITConfig
  * @brief
  * @param  NewState
  * @retval
  */
void TRNG_ITConfig(FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        TRNG->RNG_CSR |= TRNG_RNG_CSR_INTP_EN_Mask;
    }
    else
    {
        TRNG->RNG_CSR &= ~TRNG_RNG_CSR_INTP_EN_Mask;
    }
}

/**
  * @brief  TRNG_GetITStatus
  * @param  TRNG_IT:
  *         TRNG_IT_RNG0_S128
  *         TRNG_IT_RNG1_S128
  *         TRNG_IT_RNG0_ATTACK
  *         TRNG_IT_RNG1_ATTACK
  * @retval None
  */
ITStatus TRNG_GetITStatus(uint32_t TRNG_IT)
{
    assert_param(IS_TRNG_GET_IT(TRNG_IT));

    if (((TRNG->RNG_CSR) & TRNG_IT) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
  * @brief  设置TRNG中断标志位
  * @param  TRNG_IT:
  *         TRNG_IT_RNG0_S128
  *         TRNG_IT_RNG1_S128
  *         TRNG_IT_RNG0_ATTACK
  *         TRNG_IT_RNG1_ATTACK
  * @retval None
  */
void TRNG_ClearITPendingBit(uint32_t TRNG_IT)
{
    assert_param(IS_TRNG_GET_IT(TRNG_IT));

    TRNG->RNG_CSR &= ~TRNG_IT;
}

/**
  * @brief  TRNG_Start
  * @param
  * @retval None
  */
void TRNG_Start(void)
{
    TRNG->RNG_AMA &= ~TRNG_RNG_AMA_PD_ALL_Mask;
    TRNG->RNG_CSR &= ~TRNG_RNG_CSR_S128_TRNG0_Mask;
}

/**
  * @brief  TRNG_Stop
  * @param
  * @retval None
  */
void TRNG_Stop(void)
{
    TRNG->RNG_AMA |= TRNG_RNG_AMA_PD_ALL_Mask;
}


/**
  * @brief  TRNG_Stop
  * @param
  * @retval None
  */
void TRNG_Out(FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        RCC->RCC_SYSCFG_CONFIG = 0x01;
        SYSCFG->SYSCFG_LOCK = 0xCDED3526;
        SYSCFG->SSC_CLK_EN |= TRNG_RNG_ENABLE;
    }
    else
    {
        RCC->RCC_SYSCFG_CONFIG = 0x00;
        SYSCFG->SSC_CLK_EN &= ~TRNG_RNG_ENABLE;
    }
}
/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
