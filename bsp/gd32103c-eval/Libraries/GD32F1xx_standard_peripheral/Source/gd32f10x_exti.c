/**
  ******************************************************************************
  * @brief   EXTI functions of the firmware library.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_exti.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup EXTI
  * @brief EXTI driver modules
  * @{
  */

/** @defgroup EXTI_Private_Defines
  * @{
  */
/* No interrupt line is selected */
#define EXTI_LINE_NULL     ((uint32_t)0x00000000)

/* -----------------  EXTI Reset Configuration Registers  ------------------ */
/* The reset value of EXTI_IER */
#define EXTI_IER_RST       ((uint32_t)0x00000000)

/* The reset value of EXTI_EER */
#define EXTI_EER_RST       ((uint32_t)0x00000000)

/* The reset value of EXTI_RTE */
#define EXTI_RTE_RST       ((uint32_t)0x00000000)

/* The reset value of EXTI_FTE */
#define EXTI_FTE_RST       ((uint32_t)0x00000000)

/* The reset value of EXTI_PD */
#define EXTI_PD_RST        ((uint32_t)0x000FFFFF)

/**
  * @}
  */

/** @defgroup EXTI_Private_Functions
  * @{
  */

/**
  * @brief  Reset the EXTI peripheral registers and the struct EXTI_InitPara.
  * @param  EXTI_InitParaStruct: the struct EXTI_InitPara pointer.
  * @retval None
  */
void EXTI_DeInit(EXTI_InitPara *EXTI_InitParaStruct)
{
    /* Reset the EXTI peripheral registers */
    EXTI->IER = EXTI_IER_RST;
    EXTI->EER = EXTI_EER_RST;
    EXTI->RTE = EXTI_RTE_RST;
    EXTI->FTE = EXTI_FTE_RST;
    EXTI->PD = EXTI_PD_RST;

    /* Reset the struct EXTI_InitPara */
    EXTI_InitParaStruct->EXTI_LINE = EXTI_LINE_NULL;
    EXTI_InitParaStruct->EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitParaStruct->EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitParaStruct->EXTI_LINEEnable = DISABLE;
}

/**
  * @brief  Initialize the EXTI peripheral registers.
  * @param  EXTI_InitParaStruct: the struct EXTI_InitPara pointer.
  * @retval None
  */
void EXTI_Init(EXTI_InitPara *EXTI_InitParaStruct)
{
    uint32_t temp = 0;

    temp = (uint32_t)EXTI_BASE;

    if (EXTI_InitParaStruct->EXTI_LINEEnable != DISABLE) {
        /* Clear Interrupt and Event from EXTI Lines */
        EXTI->IER &= ~EXTI_InitParaStruct->EXTI_LINE;
        EXTI->EER &= ~EXTI_InitParaStruct->EXTI_LINE;

        temp += EXTI_InitParaStruct->EXTI_Mode;

        *(__IO uint32_t *) temp |= EXTI_InitParaStruct->EXTI_LINE;

        /* Clear the Rising and Falling edge trigger enable registers */
        EXTI->RTE &= ~EXTI_InitParaStruct->EXTI_LINE;
        EXTI->FTE &= ~EXTI_InitParaStruct->EXTI_LINE;

        /* Select the trigger type for the selected EXTI Lines */
        if (EXTI_InitParaStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling) {
            /* Rising and Falling edge trigger are both selected */
            EXTI->RTE |= EXTI_InitParaStruct->EXTI_LINE;
            EXTI->FTE |= EXTI_InitParaStruct->EXTI_LINE;
        } else {
            temp = (uint32_t)EXTI_BASE;
            temp += EXTI_InitParaStruct->EXTI_Trigger;

            *(__IO uint32_t *) temp |= EXTI_InitParaStruct->EXTI_LINE;
        }
    } else {
        temp += EXTI_InitParaStruct->EXTI_Mode;

        /* Disable the selected EXTI lines */
        *(__IO uint32_t *) temp &= ~EXTI_InitParaStruct->EXTI_LINE;
    }
}

/**
  * @brief  Activate the software interrupt or event request of the selected EXTI Lines.
  * @param  EXTI_LINE: the selected EXTI lines.
  *   This parameter can be any combination of EXTI_LINEx where x can be (0..19).
  * @retval None
  */
void EXTI_SWINT_Enable(uint32_t EXTI_LINE)
{
    /* Enable the software interrupt or event request of the selected EXTI Lines */
    EXTI->SIE |= EXTI_LINE;
}

/**
  * @brief  Get the bit flag of the selected EXTI lines.
  * @param  EXTI_LINE: the selected EXTI lines.
  *   This parameter can be any combination of EXTI_LINEx where x can be (0..19).
  * @retval The new value of EXTI_LINE (SET or RESET).
  */
TypeState EXTI_GetBitState(uint32_t EXTI_LINE)
{
    /* Check and get the selected EXTI lines flag */
    if ((EXTI->PD & EXTI_LINE) != (uint32_t)RESET) {
        /* EXTI_LINE bit is SET */
        return SET;
    } else {
        /* EXTI_LINE bit is RESET */
        return RESET;
    }
}

/**
  * @brief  Clear the bit flag of the selected EXTI lines.
  * @param  EXTI_LINE: the selected EXTI lines.
  *   This parameter can be any combination of EXTI_LINEx where x can be (0..19).
  * @retval None
  */
void EXTI_ClearBitState(uint32_t EXTI_LINE)
{
    /* Clear the bit flag of the selected EXTI lines */
    EXTI->PD = EXTI_LINE;
}

/**
  * @brief  Get the interrupt bit flag of the selected EXTI lines..
  * @param  EXTI_LINE: the selected EXTI lines.
  *   This parameter can be any combination of EXTI_LINEx where x can be (0..19).
  * @retval The new value of EXTI_LINE (SET or RESET).
  */
TypeState EXTI_GetIntBitState(uint32_t EXTI_LINE)
{
    /* Check and get the interrupt source is set or not */
    if (((EXTI->PD & EXTI_LINE) != (uint32_t)RESET) && ((EXTI->IER & EXTI_LINE) != (uint32_t)RESET)) {
        /* The interrupt bit of EXTI_LINE is SET */
        return SET;
    } else {
        /* The interrupt bit of EXTI_LINE is RESET */
        return RESET;
    }
}

/**
  * @brief  Clear the interrupt bit flag of the selected EXTI lines.
  * @param  EXTI_LINE: the selected EXTI lines.
  *   This parameter can be any combination of EXTI_LINEx where x can be (0..19).
  * @retval None
  */
void EXTI_ClearIntBitState(uint32_t EXTI_LINE)
{
    /* Clear the interrupt bit flag of the selected EXTI lines */
    EXTI->PD = EXTI_LINE;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

