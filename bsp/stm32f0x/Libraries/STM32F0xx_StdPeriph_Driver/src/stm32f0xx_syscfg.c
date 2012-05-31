/**
  ******************************************************************************
  * @file    stm32f0xx_syscfg.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
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
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_syscfg.h"

/** @addtogroup STM32F0xx_StdPeriph_Driver
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
  *         MEM_MODE bits took the value from the user option bytes.
  * @note   CFGR2 register is not affected by APB reset.
  *         CLABBB configuration bits are locked when set.
  *         To unlock the configuration, perform a system reset.
  */
void SYSCFG_DeInit(void)
{
  /* Set SYSCFG_CFGR1 register to reset value without affecting MEM_MODE bits */
  SYSCFG->CFGR1 &= SYSCFG_CFGR1_MEM_MODE;
  /* Set EXTICRx registers to reset value */
  SYSCFG->EXTICR[0] = 0;
  SYSCFG->EXTICR[1] = 0;
  SYSCFG->EXTICR[2] = 0;
  SYSCFG->EXTICR[3] = 0;
  /* Set CFGR2 register to reset value: clear SRAM parity error flag */
  SYSCFG->CFGR2 |= (uint32_t) SYSCFG_CFGR2_SRAM_PE;
}

/**
  * @brief  Configures the memory mapping at address 0x00000000.
  * @param  SYSCFG_MemoryRemap: selects the memory remapping.
  *   This parameter can be one of the following values:
  *     @arg SYSCFG_MemoryRemap_Flash: Main Flash memory mapped at 0x00000000  
  *     @arg SYSCFG_MemoryRemap_SystemMemory: System Flash memory mapped at 0x00000000
  *     @arg SYSCFG_MemoryRemap_SRAM: Embedded SRAM mapped at 0x00000000
  * @retval None
  */
void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap)
{
  uint32_t tmpctrl = 0;

  /* Check the parameter */
  assert_param(IS_SYSCFG_MEMORY_REMAP(SYSCFG_MemoryRemap));

  /* Get CFGR1 register value */
  tmpctrl = SYSCFG->CFGR1;

  /* Clear MEM_MODE bits */
  tmpctrl &= (uint32_t) (~SYSCFG_CFGR1_MEM_MODE);

  /* Set the new MEM_MODE bits value */
  tmpctrl |= (uint32_t) SYSCFG_MemoryRemap;

  /* Set CFGR1 register with the new memory remap configuration */
  SYSCFG->CFGR1 = tmpctrl;
}

/**
  * @brief  Configure the DMA channels remapping.
  * @param  SYSCFG_DMARemap: selects the DMA channels remap.
  *   This parameter can be one of the following values:
  *     @arg SYSCFG_DMARemap_TIM17: Remap TIM17 DMA requests from channel1 to channel2
  *     @arg SYSCFG_DMARemap_TIM16: Remap TIM16 DMA requests from channel3 to channel4
  *     @arg SYSCFG_DMARemap_USART1Rx: Remap USART1 Rx DMA requests from channel3 to channel5
  *     @arg SYSCFG_DMARemap_USART1Tx: Remap USART1 Tx DMA requests from channel2 to channel4
  *     @arg SYSCFG_DMARemap_ADC1: Remap ADC1 DMA requests from channel1 to channel2
  * @param  NewState: new state of the DMA channel remapping. 
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When enabled, DMA channel of the selected peripheral is remapped
  * @note   When disabled, Default DMA channel is mapped to the selected peripheral
  * @note 
  *           By default TIM17 DMA requests is mapped to channel 1
  *           use SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM17, Enable)
  *           to remap TIM17 DMA requests to channel 2
  *           use SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM17, Disable)
  *           to map TIM17 DMA requests to channel 1 (default mapping)
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
    SYSCFG->CFGR1 |= (uint32_t)SYSCFG_DMARemap;
  }
  else
  {
    /* use the default DMA channel mapping */
    SYSCFG->CFGR1 &= (uint32_t)(~SYSCFG_DMARemap);
  }
}

/**
  * @brief  Configure the I2C fast mode plus driving capability.
  * @param  SYSCFG_I2CFastModePlus: selects the pin.
  *   This parameter can be one of the following values:
  *     @arg SYSCFG_I2CFastModePlus_PB6: Configure fast mode plus driving capability for PB6
  *     @arg SYSCFG_I2CFastModePlus_PB7: Configure fast mode plus driving capability for PB7
  *     @arg SYSCFG_I2CFastModePlus_PB8: Configure fast mode plus driving capability for PB8
  *     @arg SYSCFG_I2CFastModePlus_PB9: Configure fast mode plus driving capability for PB9
  * @param  NewState: new state of the DMA channel remapping. 
  *         This parameter can be: ENABLE or DISABLE.
  * @note   ENABLE:  Enable fast mode plus driving capability for selected pin
  * @note   DISABLE: Disable fast mode plus driving capability for selected pin
  * @retval None
  */
void SYSCFG_I2CFastModePlusConfig(uint32_t SYSCFG_I2CFastModePlus, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SYSCFG_I2C_FMP(SYSCFG_I2CFastModePlus));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable fast mode plus driving capability for selected pin */
    SYSCFG->CFGR1 |= (uint32_t)SYSCFG_I2CFastModePlus;
  }
  else
  {
    /* Disable fast mode plus driving capability for selected pin */
    SYSCFG->CFGR1 &= (uint32_t)(~SYSCFG_I2CFastModePlus);
  }
}

/**
  * @brief  Selects the GPIO pin used as EXTI Line.
  * @param  EXTI_PortSourceGPIOx : selects the GPIO port to be used as source 
  *                                for EXTI lines where x can be (A, B, C, D or F).
  * @param  EXTI_PinSourcex: specifies the EXTI line to be configured.
  *         This parameter can be EXTI_PinSourcex where x can be (0..15)
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
  * @brief  Connect the selected parameter to the break input of TIM1.
  * @note   The selected configuration is locked and can be unlocked by system reset
  * @param  SYSCFG_Break: selects the configuration to be connected to break
  *         input of TIM1
  *   This parameter can be any combination of the following values:
  *     @arg SYSCFG_Break_PVD: Connects the PVD event to the Break Input of TIM1.
  *     @arg SYSCFG_Break_SRAMParity: Connects the SRAM_PARITY error signal to the Break Input of TIM1 .
  *     @arg SYSCFG_Break_Lockup: Connects Lockup output of CortexM0 to the break input of TIM1.
  * @retval None
  */
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break)
{
  /* Check the parameter */
  assert_param(IS_SYSCFG_LOCK_CONFIG(SYSCFG_Break));

  SYSCFG->CFGR2 |= (uint32_t) SYSCFG_Break;
}

/**
  * @brief  Checks whether the specified SYSCFG flag is set or not.
  * @param  SYSCFG_Flag: specifies the SYSCFG flag to check. 
  *   This parameter can be one of the following values:
  *     @arg SYSCFG_FLAG_PE: SRAM parity error flag.
  * @retval The new state of SYSCFG_Flag (SET or RESET).
  */
FlagStatus SYSCFG_GetFlagStatus(uint32_t SYSCFG_Flag)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameter */
  assert_param(IS_SYSCFG_FLAG(SYSCFG_Flag));

  /* Check the status of the specified SPI flag */
  if ((SYSCFG->CFGR2 & SYSCFG_CFGR2_SRAM_PE) != (uint32_t)RESET)
  {
    /* SYSCFG_Flag is set */
    bitstatus = SET;
  }
  else
  {
    /* SYSCFG_Flag is reset */
    bitstatus = RESET;
  }
  /* Return the SYSCFG_Flag status */
  return  bitstatus;
}

/**
  * @brief  Clear the selected SYSCFG flag.
  * @param  SYSCFG_Flag: selects the flag to be cleared.
  *   This parameter can be any combination of the following values:
  *     @arg SYSCFG_FLAG_PE: SRAM parity error flag.
  * @retval None
  */
void SYSCFG_ClearFlag(uint32_t SYSCFG_Flag)
{
  /* Check the parameter */
  assert_param(IS_SYSCFG_FLAG(SYSCFG_Flag));

  SYSCFG->CFGR2 |= (uint32_t) SYSCFG_Flag;
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
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
