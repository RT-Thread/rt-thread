/**
  ******************************************************************************
  * @file               ft32f4xx_syscfg.c
  * @author             FMD XA
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the SYSCFG peripheral:
  *                 + Remapping the memory mapped at 0x00000000
  *                 + Enabling I2C fast mode plus driving capability for I2C pins
  *                 + Configuring the EXTI lines connection to the GPIO port
  *                 + Configuring the CFGR features (Connecting some internal signal
  *                 to the break input of TIM1/8 and EPWM)
  * @version            V1.0.0
  * @data                   2025-04-08
    ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_syscfg.h"

/**
  * @brief  Deinitializes the SYSCFG registers to their default reset values.
  * @param  None
  * @retval None
  * @note   MEM_MODE bits took the value from bootpin after por_reset.
  */
void SYSCFG_DeInit(void)
{
    /* Set SYSCFG_MEMRMP register to reset value without affecting MEM_MODE bits */
    SYSCFG->MEMRMP &= SYSCFG_MEMRMP_MEM_MODE;
    /* Set PMC registers to reset value */
    SYSCFG->PMC = 0;
    /* Set EXTICRx registers to reset value */
    SYSCFG->EXTICR[0] = 0;
    SYSCFG->EXTICR[1] = 0;
    SYSCFG->EXTICR[2] = 0;
    SYSCFG->EXTICR[3] = 0;
    /* Set CFGR register to reset value */
    SYSCFG->CFGR |= 0;
}

/**
  * @brief  Configures the memory mapping at address 0x00000000.
  * @param  SYSCFG_MemoryRemap: selects the memory remapping.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG_MemoryRemap_Flash: Main Flash memory mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_SystemMemory: System Flash memory mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_SRAM: Embedded SRAM mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_FMC1: Embedded FMC1 mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_FMC2: Embedded FMC2 mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_QSPI: Embedded QSPI mapped at 0x00000000
  * @retval None
  */
void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap)
{
    uint32_t tmpctrl = 0;

    /* Check the parameter */
    assert_param(IS_SYSCFG_MEMORY_REMAP(SYSCFG_MemoryRemap));

    /* Get MEMRMP register value */
    tmpctrl = SYSCFG->MEMRMP;

    /* Clear MEM_MODE bits */
    tmpctrl &= (uint32_t)(~SYSCFG_MEMRMP_MEM_MODE);

    /* Set the new MEM_MODE bits value */
    tmpctrl |= (uint32_t) SYSCFG_MemoryRemap;

    /* Set MEMRMP register with the new memory remap configuration */
    SYSCFG->MEMRMP = tmpctrl;
}

/**
  * @brief  Configure FMC memory mapping swap.
  * @param  SYSCFG_FMCSWPConfig: enable or disable FMC memory mapping swap.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG_FMC_SWP_ENABLE: Configure FMC memory mapping swap enable
  *                                        SDRAM bank1/2 and NAND bank1/2 mapping are swap
  *            @arg SYSCFG_FMC_SWP_DISABLE: Configure FMC memory mapping swap disable
  *
  * @retval None
  */
void SYSCFG_FMCSWPConfig(uint32_t SYSCFG_FMCSWPCFG)
{
    /* Check the parameters */
    assert_param(IS_SYSCFG_FMC_SWP(SYSCFG_FMCSWPCFG));

    if (SYSCFG_FMCSWPCFG != DISABLE)
    {
        /* Enable FMC memory mapping swap */
        SYSCFG->MEMRMP &= (uint32_t)(~SYSCFG_MEMRMP_SWP_FMC);
        SYSCFG->MEMRMP |= (uint32_t)SYSCFG_FMCSWPCFG;
    }
    else
    {
        /* Disable FMC memory mapping swap */
        SYSCFG->MEMRMP &= (uint32_t)(~SYSCFG_FMCSWPCFG);
    }
}


/**
  * @brief  Configure the boost enable for adc.
  * @param  SYSCFG_BoostENConfig: enable or disable boost function.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG_PMC_BoostEN_ENABLE: Configure boost function enable
  *            @arg SYSCFG_PMC_BoostEN_DISABLE: Configure boost function disable
  *
  * @retval None
  */
void SYSCFG_BoostENConfig(uint32_t SYSCFG_BoostENCFG)
{
    /* Check the parameters */
    assert_param(IS_SYSCFG_PMC_BoostEN(SYSCFG_BoostENCFG));

    if (SYSCFG_BoostENCFG != DISABLE)
    {
        /* Enable boost function */
        SYSCFG->PMC |= (uint32_t)SYSCFG_BoostENCFG;
    }
    else
    {
        /* Disable boost function */
        SYSCFG->PMC &= (uint32_t)(~SYSCFG_BoostENCFG);
    }
}


/**
  * @brief  Configure the I2C fast mode plus driving capability.
  * @param  SYSCFG_I2CFastModePlus: selects the pin.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG_I2CFastModePlus_PB6: Configure fast mode plus driving capability for PB6
  *            @arg SYSCFG_I2CFastModePlus_PB7: Configure fast mode plus driving capability for PB7
  *            @arg SYSCFG_I2CFastModePlus_PB8: Configure fast mode plus driving capability for PB8
  *            @arg SYSCFG_I2CFastModePlus_PB9: Configure fast mode plus driving capability for PB9
  *            @arg SYSCFG_I2CFastModePlus_PA9: Configure fast mode plus driving capability for PA9
  *            @arg SYSCFG_I2CFastModePlus_PA10: Configure fast mode plus driving capability for PA10
  *            @arg SYSCFG_I2CFastModePlus_I2C1: Configure fast mode plus driving capability for PB10, PB11, PF6 and PF7
  *            @arg SYSCFG_I2CFastModePlus_I2C2: Configure fast mode plus driving capability for I2C2 pins
  *
  * @param  NewState: new state of the DMA channel remapping.
  *         This parameter can be:  ENABLE or DISABLE.
  * @note   ENABLE: Enable fast mode plus driving capability for selected I2C pin
  * @note   DISABLE: Disable fast mode plus driving capability for selected I2C pin
  * @note  For I2C1, fast mode plus driving capability can be enabled on all selected
  *        I2C1 pins using SYSCFG_I2CFastModePlus_I2C1 parameter or independently
  *        on each one of the following pins PB6, PB7, PB8 and PB9.
  * @note  For remaining I2C1 pins (PA14, PA15...) fast mode plus driving capability
  *        can be enabled only by using SYSCFG_I2CFastModePlus_I2C1 parameter.
  * @note  For all I2C2 pins fast mode plus driving capability can be enabled
  *        only by using SYSCFG_I2CFastModePlus_I2C2 parameter.
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
        SYSCFG->PMC |= (uint32_t)SYSCFG_I2CFastModePlus;
    }
    else
    {
        /* Disable fast mode plus driving capability for selected pin */
        SYSCFG->PMC &= (uint32_t)(~SYSCFG_I2CFastModePlus);
    }
}

/**
  * @brief  Configure the mii function or rmii function for ethernet.
  * @param  SYSCFG_MII_RMIIConfig: select ethernet use mii or rmii.
  *          This parameter can be one of the following values:
  *            @arg SYSCFG_ETH_MII_RMII_SEL_MII: select mii function
  *            @arg SYSCFG_ETH_MII_RMII_SEL_RMII: select rmii function
  *
  * @retval None
  */
void SYSCFG_MII_RMIIConfig(uint32_t SYSCFG_MII_RMIICFG)
{
    /* Check the parameters */
    assert_param(IS_SYSCFG_ETH_MII_RMII_SEL(SYSCFG_MII_RMIICFG));

    if (SYSCFG_MII_RMIICFG != DISABLE)
    {
        /* select rmii function */
        SYSCFG->PMC |= (uint32_t)SYSCFG_MII_RMIICFG;
    }
    else
    {
        /* select mii function */
        SYSCFG->PMC &= (uint32_t)(~SYSCFG_MII_RMIICFG);
    }
}

/**
  * @brief  Selects the GPIO pin used as EXTI Line.
  * @param  EXTI_PortSourceGPIOx: selects the GPIO port to be used as source
  *                               for EXTI lines where x can be (A, B, C, D, E or H).
  * @param  EXTI_PinSourcex: specifies the EXTI line to be configured.
  * @note   This parameter can be EXTI_PinSourcex where x can be:
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, (0,1) for GPIOH.
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
  * @brief  Connect the selected parameter to the break input of TIM.
  * @param  SYSCFG_Break: selects the configuration to be connected to break
  *         input of TIM
  *          This parameter can be any combination of the following values:
  *            @arg SYSCFG_Break_PVD: Connects the PVD event to the Break
  *            @arg SYSCFG_Break_Lockup: Connects Lockup output of CortexM0 to the break input of TIM1/8 or EPWM
  * @retval None
  */
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break)
{
    /* Check the parameter */
    assert_param(IS_SYSCFG_LOCK_CONFIG(SYSCFG_Break));

    SYSCFG->CFGR |= (uint32_t) SYSCFG_Break;
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
/************************ (C) COPYRIGHT FMD *****END OF FILE****/
