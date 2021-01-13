/**
  ******************************************************************************
  * @brief   MISC functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_misc.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup MISC
  * @brief MISC driver modules
  * @{
  */

/** @defgroup MISC_Private_Defines
  * @{
  */
#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)

/**
  * @}
  */

/** @defgroup MISC_Private_Functions
  * @{
  */

/**
  * @brief  By the PRIGROUP[10:8] bits of the AIRCR register, Setting the priority grouping:
  *         pre-emption priority and subpriority.
  * @param  NVIC_PriGroup: NVIC_PRIGROUP_0, NVIC_PRIGROUP_1,...NVIC_PRIGROUP_4.
  * @retval None
  */
void NVIC_PRIGroup_Enable(uint32_t NVIC_PRIGroup)
{
    /* Set the priority grouping value */
    SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PRIGroup;
}

/**
  * @brief  The NVIC peripheral Initialization.
  * @param  NVIC_InitStruct: a NVIC_InitPara structure pointer.
  * @retval None
  */
void NVIC_Init(NVIC_InitPara *NVIC_InitStruct)
{
    uint32_t temppriority = 0x00, temppreempt = 0x00, tempsub = 0x00;

    if (NVIC_InitStruct->NVIC_IRQEnable != DISABLE) {
        if (((SCB->AIRCR) & (uint32_t)0x700) == NVIC_PRIGROUP_0) {
            temppreempt = 0;
            tempsub = 0x4;
        } else if (((SCB->AIRCR) & (uint32_t)0x700) == NVIC_PRIGROUP_1) {
            temppreempt = 1;
            tempsub = 0x3;
        } else if (((SCB->AIRCR) & (uint32_t)0x700) == NVIC_PRIGROUP_2) {
            temppreempt = 2;
            tempsub = 0x2;
        } else if (((SCB->AIRCR) & (uint32_t)0x700) == NVIC_PRIGROUP_3) {
            temppreempt = 3;
            tempsub = 0x1;
        } else if (((SCB->AIRCR) & (uint32_t)0x700) == NVIC_PRIGROUP_4) {
            temppreempt = 4;
            tempsub = 0x0;
        }

        temppriority = (uint32_t)NVIC_InitStruct->NVIC_IRQPreemptPriority << (0x4 - temppreempt);
        temppriority |=  NVIC_InitStruct->NVIC_IRQSubPriority & (0x0F >> (0x4 - tempsub));
        temppriority = temppriority << 0x04;

        NVIC->IP[NVIC_InitStruct->NVIC_IRQ] = temppriority;

        /* Enable the Selected IRQ Channels */
        NVIC->ISER[NVIC_InitStruct->NVIC_IRQ >> 0x05] = (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQ & (uint8_t)0x1F);
    } else {
        /* Disable the Selected IRQ Channels */
        NVIC->ICER[NVIC_InitStruct->NVIC_IRQ >> 0x05] = (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQ & (uint8_t)0x1F);
    }
}

/**
  * @brief  Specify the vector table in RAM or FLASH memory and its Offset.
  * @param  NVIC_VectTab: NVIC_VECTTAB_RAM,NVIC_VECTTAB_FLASH
  * @param  Offset: Vector Table start address.
  * @retval None
  */
void NVIC_VectTableSet(uint32_t NVIC_VectTab, uint32_t Offset)
{
    SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

/**
  * @brief  Specify the state of the system to enter low power mode.
  * @param  LowPowerMode: NVIC_LOWPOWER_SEVONPEND,NVIC_LOWPOWER_SLEEPDEEP,NVIC_LOWPOWER_SLEEPONEXIT.
  * @param  NewValue: new value of Low Power state. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void NVIC_SystemLowPowerConfig(uint8_t LowPowerMode, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        SCB->SCR |= LowPowerMode;
    } else {
        SCB->SCR &= (~(uint32_t)LowPowerMode);
    }
}

/**
  * @brief  Specify the SysTick clock source.
  * @param  SysTick_CKSource: SYSTICK_CKSOURCE_HCLK_DIV8,SYSTICK_CKSOURCE_HCLK.
  * @retval None
  */
void SysTick_CKSource_Enable(uint32_t SysTick_CKSource)
{
    if (SysTick_CKSource == SYSTICK_CKSOURCE_HCLK) {
        SysTick->CTRL |= SYSTICK_CKSOURCE_HCLK;
    } else {
        SysTick->CTRL &= SYSTICK_CKSOURCE_HCLK_DIV8;
    }
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

