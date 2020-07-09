/**
******************************************************************************
* @file    HAL_syscfg.c
* @author  AE Team
* @version  V2.0.0
* @date  22/08/2017
* @brief   This file provides firmware functions to manage the following 
*          functionalities of the SYSCFG peripheral:
*           + Remapping the memory mapped at 0x00000000  
*           + Remapping the DMA channels
*           + Enabling I2C fast mode plus driving capability for I2C pins   
*           + Configuring the EXTI lines connection to the GPIO port
*           + Configuring the CFGR2 features (Connecting some internal signal
*             to the break input of TIM1)
*   
*  @verbatim
===============================================================================
##### How to use this driver #####
===============================================================================
[..] 
The SYSCFG registers can be accessed only when the SYSCFG 
interface APB clock is enabled.
To enable SYSCFG APB clock use:
RCC_APBPeriphClockCmd(RCC_APBPeriph_SYSCFG, ENABLE).
*  @endverbatim
*
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT 2017 MindMotion</center></h2>
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "HAL_syscfg.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @defgroup SYSCFG 
* @brief SYSCFG driver modules
* @{
*/ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SYSCFG_Private_Functions
* @{
*/ 

/** @defgroup SYSCFG_Group1 SYSCFG Initialization and Configuration functions
*  @brief   SYSCFG Initialization and Configuration functions 
*
@verbatim
===============================================================================
##### SYSCFG Initialization and Configuration functions #####
===============================================================================

@endverbatim
* @{
*/

/**
* @brief  Deinitializes the SYSCFG registers to their default reset values.
* @param  None
* @retval None
* @note   MEM_MODE bits are not affected by APB reset.
* @note   MEM_MODE bits took the value from the user option bytes.
* @note   CFGR2 register is not affected by APB reset.
* @note   CLABBB configuration bits are locked when set.
* @note   To unlock the configuration, perform a system reset.
*/
void SYSCFG_DeInit(void)
{
    /* Set SYSCFG_CFGR1 register to reset value without affecting MEM_MODE bits */
    SYSCFG->CFGR &= SYSCFG_CFGR_MEM_MODE;
    /* Set EXTICRx registers to reset value */
    SYSCFG->EXTICR[0] = 0;
    SYSCFG->EXTICR[1] = 0;
    SYSCFG->EXTICR[2] = 0;
    SYSCFG->EXTICR[3] = 0;
    
}

/**
* @brief  Configures the memory mapping at address 0x00000000.
* @param  SYSCFG_MemoryRemap: selects the memory remapping.
*          This parameter can be one of the following values:
*            @arg SYSCFG_MemoryRemap_Flash: Main Flash memory mapped at 0x00000000  
*            @arg SYSCFG_MemoryRemap_SystemMemory: System Flash memory mapped at 0x00000000
*            @arg SYSCFG_MemoryRemap_SRAM: Embedded SRAM mapped at 0x00000000
* @retval None
*/
void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap)
{
    uint32_t tmpctrl = 0;
    
    /* Check the parameter */
    assert_param(IS_SYSCFG_MEMORY_REMAP(SYSCFG_MemoryRemap));
    
    /* Get CFGR1 register value */
    tmpctrl = SYSCFG->CFGR;
    
    /* Clear MEM_MODE bits */
    tmpctrl &= (uint32_t) (~SYSCFG_CFGR_MEM_MODE);
    
    /* Set the new MEM_MODE bits value */
    tmpctrl |= (uint32_t) SYSCFG_MemoryRemap;
    
    /* Set CFGR1 register with the new memory remap configuration */
    SYSCFG->CFGR = tmpctrl;
}

/**
* @brief  Configure the DMA channels remapping.
* @param  SYSCFG_DMARemap: selects the DMA channels remap.
*          This parameter can be one of the following values:
*            @arg SYSCFG_DMARemap_TIM17: Remap TIM17 DMA requests from channel1 to channel2
*            @arg SYSCFG_DMARemap_TIM16: Remap TIM16 DMA requests from channel3 to channel4
*            @arg SYSCFG_DMARemap_UART1Rx: Remap UART1 Rx DMA requests from channel3 to channel5
*            @arg SYSCFG_DMARemap_UART1Tx: Remap UART1 Tx DMA requests from channel2 to channel4
*            @arg SYSCFG_DMARemap_ADC1: Remap ADC1 DMA requests from channel1 to channel2
* @param  NewState: new state of the DMA channel remapping. 
*         This parameter can be: ENABLE or DISABLE.
* @note   When enabled, DMA channel of the selected peripheral is remapped
* @note   When disabled, Default DMA channel is mapped to the selected peripheral
* @note   By default TIM17 DMA requests is mapped to channel 1, 
*         use SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM17, Enable) to remap
*         TIM17 DMA requests to channel 2 and use
*         SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM17, Disable) to map
*         TIM17 DMA requests to channel 1 (default mapping)
* @retval None
*/
void SYSCFG_DMAChannelRemapConfig(uint32_t SYSCFG_DMARemap, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SYSCFG_DMA_REMAP(SYSCFG_DMARemap));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        /* Remap the DMA channel */
        SYSCFG->CFGR |= (uint32_t)SYSCFG_DMARemap;
    }
    else
    {
        /* use the default DMA channel mapping */
        SYSCFG->CFGR &= (uint32_t)(~SYSCFG_DMARemap);
    }
}



/**
* @brief  Selects the GPIO pin used as EXTI Line.
* @param  EXTI_PortSourceGPIOx: selects the GPIO port to be used as source 
*                               for EXTI lines where x can be (A, B, C, D, E or F).
* @param  EXTI_PinSourcex: specifies the EXTI line to be configured.
* @note   This parameter can be EXTI_PinSourcex where x can be:
*         For MCU: (0..15) for GPIOA, GPIOB, (13..15) for GPIOC and (0..1, 6..7) for GPIOD.
* @retval None
*/
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex)
{
    uint32_t tmp = 0x00;
    
    /* Check the parameters */
    assert_param(IS_EXTI_PORT_SOURCE(EXTI_PortSourceGPIOx));
    assert_param(IS_EXTI_PIN_SOURCE(EXTI_PinSourcex));
    
    tmp = ((uint32_t)0x0F) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03));
    SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] &= ~tmp;
    SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
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

/**
* @}
*/ 
/*-------------------------(C) COPYRIGHT 2017 MindMotion ----------------------*/
