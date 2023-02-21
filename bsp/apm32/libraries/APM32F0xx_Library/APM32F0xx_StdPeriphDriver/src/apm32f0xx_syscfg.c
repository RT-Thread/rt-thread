/*!
 * @file        apm32f0xx_syscfg.c
 *
 * @brief       This file contains all the functions for the SYSCFG peripheral
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32f0xx_syscfg.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup SYSCFG_Driver SYSCFG Driver
  @{
*/

/** @defgroup SYSCFG_Macros Macros
  @{
*/

/**@} end of group SYSCFG_Macros */

/** @defgroup SYSCFG_Enumerations Enumerations
  @{
*/

/**@} end of group SYSCFG_Enumerations */

/** @defgroup SYSCFG_Structures Structures
  @{
*/

/**@} end of group SYSCFG_Structures */

/** @defgroup SYSCFG_Variables Variables
  @{
*/

/**@} end of group SYSCFG_Variables */

/** @defgroup SYSCFG_Functions Functions
  @{
*/

/*!
 * @brief        Set SYSCFG CFG0/1 EINTCFG1/2/3/4 register to reset value
 *
 * @param        None
 *
 * @retval       None
 */
void SYSCFG_Reset(void)
{
    SYSCFG->CFG1 &= (uint32_t) SYSCFG_CFG1_MEMMODE;
    SYSCFG->EINTCFG1 = 0;
    SYSCFG->EINTCFG2 = 0;
    SYSCFG->EINTCFG3 = 0;
    SYSCFG->EINTCFG4 = 0;
    SYSCFG->CFG2 |= (uint32_t) SYSCFG_CFG2_SRAMPEF;
}

/*!
 * @brief       SYSCFG Memory Remap selects
 *
 * @param       memory: selects the memory remapping
 *                      The parameter can be one of following values:
 *                      @arg SYSCFG_MEMORY_REMAP_FMC:      SYSCFG MemoryRemap Flash
 *                      @arg SYSCFG_MEMORY_REMAP_SYSTEM:   SYSCFG MemoryRemap SystemMemory
 *                      @arg SYSCFG_MEMORY_REMAP_SRAM:     SYSCFG MemoryRemap SRAM
 *
 * @retval      None
 */
void SYSCFG_MemoryRemapSelect(uint8_t memory)
{
    SYSCFG->CFG1_B.MMSEL = (uint8_t)memory;
}

/*!
 * @brief       Enables SYSCFG DMA Channel Remap
 *
 * @param       channel: selects the DMA channels remap.
 *                       The parameter can be any combination of following values:
 *                       @arg SYSCFG_DAM_REMAP_ADC:      ADC DMA remap
 *                       @arg SYSCFG_DAM_REMAP_USART1TX: USART1 TX DMA remap
 *                       @arg SYSCFG_DAM_REMAP_USART1RX: USART1 RX DMA remap
 *                       @arg SYSCFG_DAM_REMAP_TMR16:    Timer 16 DMA remap
 *                       @arg SYSCFG_DAM_REMAP_TMR17:    Timer 17 DMA remap
 *                       @arg SYSCFG_DAM_REMAP_TMR16_2£º Timer 16 DMA remap2(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_TMR17_2£º Timer 17 DMA remap2(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_SPI2£º    SPI2 DMA remap(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_USART2£º  USART1 TX DMA remap(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_USART3£º  USART1 RX DMA remap(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_I2C1£º    I2C1 DMA remap(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_TMR1£º    Timer 1 DMA remap(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_TMR2£º    Timer 2 DMA remap(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_TMR3£º    Timer 3 DMA remap(only for APM32F072)
 *
 * @retval      None
 */
void SYSCFG_EnableDMAChannelRemap(uint32_t channel)
{
    SYSCFG->CFG1 |= (uint32_t)channel;
}

/*!
 * @brief       Disables SYSCFG DMA Channel Remap
 *
 * @param       channel: selects the DMA channels remap.
 *                       The parameter can be any combination of following values:
 *                       @arg SYSCFG_DAM_REMAP_ADC:      ADC DMA remap
 *                       @arg SYSCFG_DAM_REMAP_USART1TX: USART1 TX DMA remap
 *                       @arg SYSCFG_DAM_REMAP_USART1RX: USART1 RX DMA remap
 *                       @arg SYSCFG_DAM_REMAP_TMR16:    Timer 16 DMA remap
 *                       @arg SYSCFG_DAM_REMAP_TMR17:    Timer 17 DMA remap
 *                       @arg SYSCFG_DAM_REMAP_TMR16_2£º Timer 16 DMA remap2(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_TMR17_2£º Timer 17 DMA remap2(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_SPI2£º    SPI2 DMA remap(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_USART2£º  USART1 TX DMA remap(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_USART3£º  USART1 RX DMA remap(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_I2C1£º    I2C1 DMA remap(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_TMR1£º    Timer 1 DMA remap(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_TMR2£º    Timer 2 DMA remap(only for APM32F072)
 *                       @arg SYSCFG_DAM_REMAP_TMR3£º    Timer 3 DMA remap(only for APM32F072)
 *
 * @retval      None
 */
void SYSCFG_DisableDMAChannelRemap(uint32_t channel)
{
    SYSCFG->CFG1 &= (uint32_t)~channel;
}

/*!
 * @brief       Enables SYSCFG I2C Fast Mode Plus
 *
 * @param       pin:     selects the pin.
 *                       The parameter can be combination of following values:
 *                       @arg SYSCFG_I2C_FMP_PB6:    I2C PB6 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PB7:    I2C PB7 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PB8:    I2C PB8 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PB9:    I2C PB9 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PA9:    I2C PA9 Fast mode plus(only for APM32F030 and APM32F091)
 *                       @arg SYSCFG_I2C_FMP_PA10:   I2C PA10 Fast mode plus(only for APM32F030 and APM32F091)
 *                       @arg SYSCFG_I2C_FMP_I2C1:   PB10, PB11, PF6 and PF7
 *                       @arg SYSCFG_I2C_FMP_I2C2:   I2C2 Fast mode plus(only for APM32F072 and APM32F091)
 *
 * @retval      None
 */
void SYSCFG_EnableI2CFastModePlus(uint32_t pin)
{
    SYSCFG->CFG1 |= (uint32_t)pin;
}

/*!
 * @brief       Disables SYSCFG I2C Fast Mode Plus
 *
 * @param       pin:     selects the pin.
 *                       The parameter can be combination of following values:
 *                       @arg SYSCFG_I2C_FMP_PB6:    I2C PB6 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PB7:    I2C PB7 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PB8:    I2C PB8 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PB9:    I2C PB9 Fast mode plus
 *                       @arg SYSCFG_I2C_FMP_PA9:    I2C PA9 Fast mode plus(only for APM32F030 and APM32F091)
 *                       @arg SYSCFG_I2C_FMP_PA10:   I2C PA10 Fast mode plus(only for APM32F030 and APM32F091)
 *                       @arg SYSCFG_I2C_FMP_I2C1:   PB10, PB11, PF6 and PF7
 *                       @arg SYSCFG_I2C_FMP_I2C2:   I2C2 Fast mode plus(only for APM32F072 and APM32F091)
 *
 * @retval      None
 */
void SYSCFG_DisableI2CFastModePlus(uint32_t pin)
{
    SYSCFG->CFG1 &= (uint32_t)~pin;
}

/*!
 * @brief       Select the modulation envelope source
 *
 * @param       IRDAEnv: selects the envelope source
 *                       The parameter can be one of following values:
 *                       @arg SYSCFG_IRDA_ENV_TMR16:     Timer16 as IRDA Modulation envelope source
 *                       @arg SYSCFG_IRDA_ENV_USART1:    USART1 as IRDA Modulation envelope source
 *                       @arg SYSCFG_IRDA_ENV_USART2:    USART4 as IRDA Modulation envelope source
 *
 * @retval      None
 *
 * @note        It's only for APM32F091 devices.
 */
void SYSCFG_SelectIRDAEnv(SYSCFG_IRDA_ENV_T IRDAEnv)
{
    SYSCFG->CFG1 &= ~(0x000000C0);
    SYSCFG->CFG1 |= (IRDAEnv);
}

/*!
 * @brief       Selects the GPIO pin used as EINT Line.
 *
 * @param       port:   selects the port can be GPIOA/B/C/D/E/F
 *
 * @param       pin:    selects the pin can be SYSCFG_PIN_(0..15)
 *
 * @retval      None
 *
 * @note        GPIOE only for APM32F072 and APM32F091
 */

void SYSCFG_EINTLine(SYSCFG_PORT_T port, SYSCFG_PIN_T pin)
{
    uint32_t status;

    status = (((uint32_t)0x0F) & port) << (0x04 * (pin & (uint8_t)0x03));

    if (pin <= 0x03)
    {
        SYSCFG->EINTCFG1 |= status;
    }
    else if ((0x04 <= pin) & (pin <= 0x07))
    {
        SYSCFG->EINTCFG2 |= status;
    }
    else if ((0x08 <= pin) & (pin <= 0x0B))
    {
        SYSCFG->EINTCFG3 |= status;
    }
    else if ((0x0C <= pin) & (pin <= 0x0F))
    {
        SYSCFG->EINTCFG4 |= status;
    }
}

/*!
 * @brief       Selected parameter to the break input of TMR1.
 *
 * @param       lock:   selects the configuration to break
 *                      The parameter can be one of following values:
 *                      @arg SYSCFG_LOCK_LOCKUP: Cortex-M0 LOCKUP bit
 *                      @arg SYSCFG_LOCK_SRAM:  SRAM parity lock bit
 *                      @arg SYSCFG_LOCK_PVD:  PVD lock enable bit
 *
 * @retval      None
 */
void SYSCFG_BreakLock(uint32_t lock)
{
    SYSCFG->CFG2_B.LOCK = 0;
    SYSCFG->CFG2_B.SRAMLOCK = 0;
    SYSCFG->CFG2_B.PVDLOCK = 0;

    if (lock == SYSCFG_LOCK_LOCKUP)
    {
        SYSCFG->CFG2_B.LOCK = BIT_SET;
    }
    if (lock == SYSCFG_LOCK_SRAM)
    {
        SYSCFG->CFG2_B.SRAMLOCK = BIT_SET;
    }
    if (lock == SYSCFG_LOCK_PVD)
    {
        SYSCFG->CFG2_B.PVDLOCK = BIT_SET;
    }
}

/*!
 * @brief       Read the specified SYSCFG flag
 *
 * @param       flag:   SRAM Parity error flag
 *                      @arg SYSCFG_CFG2_SRAMPEF
 *
 * @retval      None
 */
uint8_t SYSCFG_ReadStatusFlag(uint32_t flag)
{
    uint32_t status;

    status = (uint32_t)(SYSCFG->CFG2 & flag);

    if (status == flag)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear the specified SYSCFG flag
 *
 * @param       flag:   SRAM Parity error flag
 *                      @arg SYSCFG_CFG2_SRAMPEF
 *
 * @retval      None
 */
void SYSCFG_ClearStatusFlag(uint8_t flag)
{
    SYSCFG->CFG2 |= (uint32_t) flag;
}

/**@} end of group SYSCFG_Functions*/
/**@} end of group SYSCFG_Driver*/
/**@} end of group APM32F0xx_StdPeriphDriver*/
