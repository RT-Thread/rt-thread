/*!
 * @file        apm32e10x_dmc.c
 *
 * @brief       This file contains all the functions for the DMC controler peripheral
 *
 * @version     V1.0.2
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2021-2023 Geehy Semiconductor
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

#include "apm32e10x_dmc.h"

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup DMC_Driver
  * @brief DMC driver modules
  @{
*/

/** @defgroup  DMC_Functions Functions
  @{
*/

/*!
 * @brief       DMC controler configuration
 *
 * @param       dmcConfig: pointer to a DMC_Config_T structure
 *
 * @retval      None
 */
void DMC_Config(DMC_Config_T * dmcConfig)
{
    DMC->SW_B.MCSW = 1;
    while(!DMC->CTRL1_B.INIT);

    DMC->CFG_B.BAWCFG = dmcConfig->bankWidth;
    DMC->CFG_B.RAWCFG = dmcConfig->rowWidth;
    DMC->CFG_B.CAWCFG = dmcConfig->colWidth;

    DMC->MASK_B.MSIZESEL = dmcConfig->memorySize;
    DMC->CTRL2_B.CPHACFG = dmcConfig->clkPhase;

    DMC_ConfigTiming(&dmcConfig->timing);

    DMC->CTRL1_B.MODESET = 1;
    while(!DMC->CTRL1_B.MODESET);

    DMC->CTRL2_B.RDDEN = 1;
    DMC->CTRL2_B.RDDCFG = 7;
}

/*!
 * @brief       Fills each dmcConfig member with its default value
 *
 * @param       dmcConfig: pointer to a DMC_Config_T structure
 *
 * @retval      None
 */
void DMC_ConfigStructInit(DMC_Config_T * dmcConfig)
{
    dmcConfig->bankWidth   = DMC_BANK_WIDTH_2;
    dmcConfig->clkPhase    = DMC_CLK_PHASE_REVERSE;
    dmcConfig->colWidth    = DMC_COL_WIDTH_10;
    dmcConfig->rowWidth    = DMC_ROW_WIDTH_13;
    dmcConfig->memorySize  = DMC_MEMORY_SIZE_8MB;

    DMC_ConfigTimingStructInit(&dmcConfig->timing);
}

/*!
 * @brief       Timing configuration
 *
 * @param       timingConfig: pointer to a DMC_TimingConfig_T structure
 *
 * @retval      None
 */
void DMC_ConfigTiming(DMC_TimingConfig_T * timingConfig)
{
    DMC->TIM0_B.RASMINTSEL = timingConfig->tRAS;
    DMC->TIM0_B.DTIMSEL    = timingConfig->tRCD;
    DMC->TIM0_B.PCPSEL     = timingConfig->tRP;
    DMC->TIM0_B.WRTIMSEL   = timingConfig->tWR;
    DMC->TIM0_B.ARPSEL     = timingConfig->tARP;
    DMC->TIM0_B.ATACP      = timingConfig->tCMD;

    DMC->TIM0_B.CASLSEL0  =  timingConfig->latencyCAS & 0x03;
    DMC->TIM0_B.ECASLSEL1 = (timingConfig->latencyCAS >> 2) & 0x01;

    DMC->TIM0_B.XSR0  =  timingConfig->tXSR & 0X0F;
    DMC->TIM0_B.EXSR1 = (timingConfig->tXSR >> 4) & 0X1F;

    DMC->REF_B.RCYCCFG = timingConfig->tRFP;
}

/*!
 * @brief       Fills each config member with its default value
 *
 * @param       timingConfig: pointer to a DMC_TimingConfig_T structure
 *
 * @retval      None
 */
void DMC_ConfigTimingStructInit(DMC_TimingConfig_T * timingConfig)
{
    timingConfig->latencyCAS = DMC_CAS_LATENCY_3;
    timingConfig->tARP = DMC_AUTO_REFRESH_10;
    timingConfig->tRAS = DMC_RAS_MINIMUM_5;
    timingConfig->tCMD = DMC_ATA_CMD_7;
    timingConfig->tRCD = DMC_DELAY_TIME_2;
    timingConfig->tRP  = DMC_PRECHARGE_2;
    timingConfig->tWR  = DMC_NEXT_PRECHARGE_2;
    timingConfig->tXSR = 6;
    timingConfig->tRFP = 0xC3;
}

/*!
 * @brief       Set number of bank bits
 *
 * @param       bankWidth: Specifies the bank bits number
 *                         This parameter can be one of the following values:
 *                         @arg DMC_BANK_WIDTH_1
 *                         @arg DMC_BANK_WIDTH_2
 * @retval      None
 */
void DMC_ConfigBankWidth(DMC_BANK_WIDTH_T bankWidth)
{
    DMC->CFG_B.BAWCFG = bankWidth;
}

/*!
 * @brief       Set address bus width
 *
 * @param       rowWidth: Specifies the row address bits number
 *                        This parameter can be one of the following values:
 *                        @arg DMC_ROW_WIDTH_11
 *                        @arg DMC_ROW_WIDTH_12
 *                        @arg DMC_ROW_WIDTH_13
 *                        @arg DMC_ROW_WIDTH_14
 *                        @arg DMC_ROW_WIDTH_15
 *                        @arg DMC_ROW_WIDTH_16
 * @param       colWidth: Specifies the column address bits number
 *                        This parameter can be one of the following values:
 *                        @arg DMC_COL_WIDTH_8
 *                        @arg DMC_COL_WIDTH_9
 *                        @arg DMC_COL_WIDTH_10
 *                        @arg DMC_COL_WIDTH_11
 *                        @arg DMC_COL_WIDTH_12
 *                        @arg DMC_COL_WIDTH_13
 *                        @arg DMC_COL_WIDTH_14
 *                        @arg DMC_COL_WIDTH_15
 * @retval      None
 */
void DMC_ConfigAddrWidth(DMC_ROW_WIDTH_T rowWidth, DMC_COL_WIDTH_T colWidth)
{
    DMC->CFG_B.RAWCFG = rowWidth;
    DMC->CFG_B.CAWCFG = colWidth;
}

/*!
 * @brief       Set stable time after power up
 *
 * @param       stableTime: Numper of the clock, can be 0x0000 to 0xFFFF
 *
 * @retval      None
 */
void DMC_ConfigStableTimePowerup(uint16_t stableTime)
{
    DMC->TIM1_B.STBTIM = stableTime;
}

/*!
 * @brief       Number of auto-refreshes during initialization
 *
 * @param       num: Number of auto-refreshes can 1 to 16
 *                   This parameter can be one of the following values:
 *                        @arg DMC_AUTO_REFRESH_1
 *                        @arg DMC_AUTO_REFRESH_2
 *                             ......
 *                        @arg DMC_AUTO_REFRESH_15
 *                        @arg DMC_AUTO_REFRESH_16
 *
 * @retval      None
 */
void DMC_ConfigAutoRefreshNumDuringInit(DMC_AUTO_REFRESH_T num)
{
    DMC->TIM1_B.ARNUMCFG = num;
}

/*!
 * @brief       Number of DMC internal banks to be open at any time;
 *
 * @param       num:  Number of banks can 1 to 16
 *                   This parameter can be one of the following values:
 *                        @arg DMC_BANK_NUMBER_1
 *                        @arg DMC_BANK_NUMBER_2
 *                             ......
 *                        @arg DMC_BANK_NUMBER_15
 *                        @arg DMC_BANK_NUMBER_16
 * @retval      None
 */
void DMC_ConfigOpenBank(DMC_BANK_NUMBER_T num)
{
    DMC->CTRL1_B.BANKNUMCFG = num;
}

/*!
 * @brief       Read self-refresh status
 *
 * @param       None
 *
 * @retval      The status of self-refresh (SET or RESET)
 */
uint8_t DMC_ReadSelfRefreshStatus(void)
{
    uint8_t ret;

    ret = DMC->CTRL1_B.SRMFLG ? SET : RESET;

    return ret;
}

/*!
 * @brief       Set update mode bit
 *
 * @param       None
 *
 * @retval      None
 */
void DMC_EnableUpdateMode(void)
{
    DMC->CTRL1_B.MODESET = 1;
}

/*!
 * @brief       Enter power down mode
 *
 * @param       None
 *
 * @retval      None
 */
void DMC_EnterPowerdownMode(void)
{
    DMC->CTRL1_B.PDMEN = 1;
}

/*!
 * @brief       Exit self-refresh mode
 *
 * @param       None
 *
 * @retval      None
 */
void DMC_EixtSlefRefreshMode(void)
{
    DMC->CTRL1_B.SRMEN = 0;
}

/*!
 * @brief       Enter self-refresh mode
 *
 * @param       None
 *
 * @retval      None
 */
void DMC_EnterSlefRefreshMode(void)
{
    DMC->CTRL1_B.SRMEN = 1;
}

/*!
 * @brief     Enable Accelerate Module
 *
 * @param     None
 *
 * @retval    None
 */
void DMC_EnableAccelerateModule(void)
{
    DMC->CTRL2_B.BUFFEN = BIT_SET;
}
/*!
 * @brief     Disable Accelerate Module
 *
 * @param     None
 *
 * @retval    None
 */
void DMC_DisableAccelerateModule(void)
{
    DMC->CTRL2_B.BUFFEN = BIT_RESET;
}
/*!
 * @brief       Init DMC
 *
 * @param       None
 *
 * @retval      None
 */
void DMC_EnableInit(void)
{
    DMC->CTRL1_B.INIT = 1;
}

/*!
 * @brief       Set refresh type before enter self-refresh
 *
 * @param       refresh: Specifies the refresh type
 *                The parameter can be one of following values:
 *                @arg DMC_REFRESH_ROW_ONE: Refresh one row
 *                @arg DMC_REFRESH_ROW_ALL: Refresh all row
 *
 * @retval      None
 */
void DMC_ConfigFullRefreshBeforeSR(DMC_REFRESH_T refresh)
{
    DMC->CTRL1_B.FRBSREN = refresh;
}

/*!
 * @brief       Set refresh type after exit self-refresh
 *
 * @param       refresh: Specifies the refresh type
 *                The parameter can be one of following values:
 *                @arg DMC_REFRESH_ROW_ONE: Refresh one row
 *                @arg DMC_REFRESH_ROW_ALL: Refresh all row
 *
 * @retval      None
 */
void DMC_ConfigFullRefreshAfterSR(DMC_REFRESH_T refresh)
{
    DMC->CTRL1_B.FRASREN = refresh;
}

/*!
 * @brief       Config precharge type
 *
 * @param       precharge: Specifies the precharge type
 *                The parameter can be one of following values:
 *                @arg DMC_PRECHARGE_IM:    Immediate precharge
 *                @arg DMC_PRECHARGE_DELAY: Delayed precharge
 *
 * @retval      None
 */
void DMC_ConfigPrechargeType(DMC_PRECHARE_T precharge)
{
    DMC->CTRL1_B.PCACFG = precharge;
}

/*!
 * @brief       Config refresh period
 *
 * @param       period:   Specifies the refresh period, can be 0x0000 to 0xFFFF
 *
 * @retval      None
 */
void DMC_ConfigRefreshPeriod(uint16_t period)
{
    DMC->REF_B.RCYCCFG = period;
}

/*!
 * @brief       Config memory size
 *
 * @param       memorySize: Specifies memory size
 *                The parameter can be one of following values:
 *                @arg DMC_MEMORY_SIZE_0:     Memory size is no link
 *                @arg DMC_MEMORY_SIZE_64KB:  Memory size is 64KB
 *                @arg DMC_MEMORY_SIZE_128KB: Memory size is 128KB
 *                @arg DMC_MEMORY_SIZE_256KB: Memory size is 256KB
 *                @arg DMC_MEMORY_SIZE_512KB: Memory size is 512KB
 *                @arg DMC_MEMORY_SIZE_1MB:   Memory size is 1MB
 *                @arg DMC_MEMORY_SIZE_2MB:   Memory size is 2MB
 *                @arg DMC_MEMORY_SIZE_4MB:   Memory size is 4MB
 *                @arg DMC_MEMORY_SIZE_8MB:   Memory size is 8MB
 *                @arg DMC_MEMORY_SIZE_16MB:  Memory size is 16MB
 *                @arg DMC_MEMORY_SIZE_32MB:  Memory size is 32MB
 *                @arg DMC_MEMORY_SIZE_64MB:  Memory size is 64MB
 *                @arg DMC_MEMORY_SIZE_128MB: Memory size is 128MB
 *                @arg DMC_MEMORY_SIZE_256MB: Memory size is 256MB
 *
 * @retval      None
 */
void DMC_ConfigMemorySize(DMC_MEMORY_SIZE_T memorySize)
{
    DMC->MASK_B.MSIZESEL = memorySize;
}

/*!
 * @brief       Enable DMC controler
 *
 * @param       None
 *
 * @retval      None
 */
void DMC_Enable(void)
{
    DMC->SW_B.MCSW = 1;
}

/*!
 * @brief       Disable DMC controler
 *
 * @param       None
 *
 * @retval      None
 */
void DMC_Disable(void)
{
    DMC->SW_B.MCSW = 0;
}

/*!
 * @brief       Set DMC clock phase
 *
 * @param       clkPhase: Specifies clock phase
 *                The parameter can be one of following values:
 *                @arg DMC_CLK_PHASE_NORMAL: Clock phase is normal
 *                @arg DMC_CLK_PHASE_REVERSE: Clock phase is reverse
 *
 * @retval      None
 *
 */
void DMC_ConfigClockPhase(DMC_CLK_PHASE_T clkPhase)
{
    DMC->CTRL2_B.CPHACFG = clkPhase;
}

/*!
 * @brief       Set DMC WRAP burst
 *
 * @param       burst: WRAP burst Type Selection
 *                The parameter can be one of following values:
 *                @arg DMC_WRAPB_4: wrap4 burst transfer
 *                @arg DMC_WRAPB_8: wrap8 burst transfer
 *
 * @retval      None
 */
void DMC_ConfigWRAPB(DMC_WRPB_T burst)
{
    DMC->CTRL2_B.WRPBSEL = burst;
}


/**@} end of group DMC_Functions */
/**@} end of group DMC_Driver */
/**@} end of group APM32E10x_StdPeriphDriver*/

