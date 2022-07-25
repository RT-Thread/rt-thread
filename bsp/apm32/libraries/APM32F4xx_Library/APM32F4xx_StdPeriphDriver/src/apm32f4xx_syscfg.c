/*!
 * @file        apm32f4xx_syscfg.c
 *
 * @brief       This file provides all the SYSCFG firmware functions
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32f4xx_syscfg.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup SYSCFG_Driver
  * @brief SYSCFG driver modules
  @{
*/

/** @defgroup SYSCFG_Functions
  @{
*/

/*!
 * @brief     Reset the remap and EINT configuration registers to their default values.
 *
 * @param     None
 *
 * @retval    None
 */
void SYSCFG_Reset(void)
{
    RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_SYSCFG);
    RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_SYSCFG);
}

/*!
 * @brief     Changes the mapping of the specified pin.
 *
 * @param     memory: selects the memory remapping.
 *                   The parameter can be one of the following values:
 *                   @arg SYSCFG_REMAP_FLASH        : Memory mapping to Flash
 *                   @arg SYSCFG_REMAP_SYSTEM_FLASH : Memory mapping to SystemFlash
 *                   @arg SYSCFG_REMAP_SMC_BANK1    : Memory mapping to bank1 of SMC (NOR-flash/PSRAM)
 *                   @arg SYSCFG_REMAP_SRAM         : Memory mapping to SRAM
 *
 * @retval    None
 */
void SYSCFG_ConfigMemoryRemap(SYSCFG_REMAP_T memory)
{
    SYSCFG->MMSEL_B.MMSEL = memory;
}

/*!
 * @brief     Config the GPIO pin used as EINT Line.
 *
 * @param     port: select the port
 *                  The parameter can be one of the following values
 *                  @arg SYSCFG_PORT_GPIOA : Port Source GPIOA
 *                  @arg SYSCFG_PORT_GPIOB : Port Source GPIOB
 *                  @arg SYSCFG_PORT_GPIOC : Port Source GPIOC
 *                  @arg SYSCFG_PORT_GPIOD : Port Source GPIOD
 *                  @arg SYSCFG_PORT_GPIOE : Port Source GPIOE
 *                  @arg SYSCFG_PORT_GPIOF : Port Source GPIOF
 *                  @arg SYSCFG_PORT_GPIOG : Port Source GPIOG
 *                  @arg SYSCFG_PORT_GPIOH : Port Source GPIOH
 *                  @arg SYSCFG_PORT_GPIOI : Port Source GPIOI
 *
 * @param     pin:  select the pin
 *                  The parameter can be one of the following values
 *                  @arg SYSCFG_PIN_0 : Pin Source 0
 *                  @arg SYSCFG_PIN_1 : Pin Source 1
 *                  @arg SYSCFG_PIN_2 : Pin Source 2
 *                  @arg SYSCFG_PIN_3 : Pin Source 3
 *                  @arg SYSCFG_PIN_4 : Pin Source 4
 *                  @arg SYSCFG_PIN_5 : Pin Source 5
 *                  @arg SYSCFG_PIN_6 : Pin Source 6
 *                  @arg SYSCFG_PIN_7 : Pin Source 7
 *                  @arg SYSCFG_PIN_8 : Pin Source 8
 *                  @arg SYSCFG_PIN_9 : Pin Source 9
 *                  @arg SYSCFG_PIN_10: Pin Source 10
 *                  @arg SYSCFG_PIN_11: Pin Source 11
 *                  @arg SYSCFG_PIN_12: Pin Source 12
 *                  @arg SYSCFG_PIN_13: Pin Source 13
 *                  @arg SYSCFG_PIN_14: Pin Source 14
 *                  @arg SYSCFG_PIN_15: Pin Source 15
 *
 * @retval    None
 *
 * @note      pin from SYSCFG_PIN_12 to SYSCFG_PIN_15 is not fit for
 *            SYSCFG_PORT_GPIOI of the port.
 */
void SYSCFG_ConfigEINTLine(SYSCFG_PORT_T port, SYSCFG_PIN_T pin)
{
    uint32_t status;

    status = ((uint32_t)(port & 0x0F)) << (0x04 * (pin & 0x03));

    if ((pin >> 2) == 0)
    {
        SYSCFG->EINTCFG1 |= status;
    }
    else if ((pin >> 2) == 1)
    {
        SYSCFG->EINTCFG2 |= status;
    }
    else if ((pin >> 2) == 2)
    {
        SYSCFG->EINTCFG3 |= status;
    }
    else if ((pin >> 2) == 3)
    {
        SYSCFG->EINTCFG4 |= status;
    }
}

/*!
 * @brief     Selects the ETHERNET media interface
 *
 * @param     media: select the media
 *                   The parameter can be combination of folling values
 *                   @arg SYSCFG_INTERFACE_MII  : MII mode selected
 *                   @arg SYSCFG_INTERFACE_RMII : RMII mode selected
 *
 * @retval    None
 */
void SYSCFG_ConfigMediaInterface(SYSCFG_INTERFACE_T media)
{
    SYSCFG->PMC_B.ENETSEL = media;
}

/*!
 * @brief     Enables the I/O Compensation Cell.
 *
 * @param     None
 *
 * @retval    None
 *
 * @note      The I/O compensation cell can be used only when the device supply
 *            voltage ranges from 2.4 to 3.6 V.
 */
void SYSCFG_EnableCompensationCell(void)
{
    SYSCFG->CCCTRL_B.CCPD = BIT_SET;
}

/*!
 * @brief     Disables the I/O Compensation Cell.
 *
 * @param     None
 *
 * @retval    None
 *
 * @note      The I/O compensation cell can be used only when the device supply
 *            voltage ranges from 2.4 to 3.6 V.
 */
void SYSCFG_DisableCompensationCell(void)
{
    SYSCFG->CCCTRL_B.CCPD = BIT_RESET;
}

/*!
 * @brief     Read the I/O Compensation Cell ready flag.
 *
 * @param     None
 *
 * @retval    SET or RESET
 */
uint8_t SYSCFG_ReadCompensationCellStatus(void)
{
    return (SYSCFG->CCCTRL & BIT8) ? SET : RESET;
}

/**@} end of group SYSCFG_Functions */
/**@} end of group SYSCFG_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
