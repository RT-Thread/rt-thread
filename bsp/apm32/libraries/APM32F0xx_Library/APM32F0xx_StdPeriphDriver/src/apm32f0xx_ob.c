/*!
 * @file        apm32f0xx_ob.c
 *
 * @brief       This file contains all the functions for the OB peripheral
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

#include "apm32f0xx_ob.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup OB_Driver
  @{
*/

/** @defgroup OB_Macros Macros
  @{
*/

/**@} end of group OB_Macros*/

/** @defgroup OB_Enumerations Enumerations
  @{
*/

/**@} end of group OB_Enumerations*/

/** @defgroup OB_Structures Structures
  @{
*/

/**@} end of group OB_Structures*/

/** @defgroup OB_Variables Variables
  @{
*/

/**@} end of group OB_Variables*/

/** @defgroup OB_Functions Functions
  @{
*/

/*!
 * @brief     Read Flash Protection Level
 *
 * @param     readProtection:   Specifies the read protection level.
 *                              The parameter can be one of following values:
 *                              @arg OB_READ_PRO_LEVEL0:  No protection
 *                              @arg OB_READ_PRO_LEVEL1:  Read protection of the memory
 * @retval    None
 */
void OB_ReadProtectionOptionByte(OB_READ_PRO_T readProtection)
{
    OB->READPORT_B.READPROT = readProtection;
}

/*!
 * @brief     Option Bytes Watchdog
 *
 * @param     wdt: Select Watchdog SW/HW
 *
 * @retval    None
 */
void OB_OptionBytesWatchdog(OB_WDT_T wdt)
{
    OB->USER_B.WDTSEL = wdt;
}

/*!
 * @brief     Option Bytes nRST STOP
 *
 * @param     stop: Select nRST STOP RST/SET
 *
 * @retval    None
 */
void OB_OptionBytesStop(OB_STOP_T stop)
{
    OB->USER_B.RSTSTOP = stop;
}

/*!
 * @brief     Option Bytes nRST STDBY
 *
 * @param     standby: Select nRST STDBY RST/SET
 *
 * @retval    None
 */
void OB_OptionBytesStandby(OB_STANDBY_T standby)
{
    OB->USER_B.RSTSTDBY = standby;
}

/*!
 * @brief     Option Bytes nBOOT1
 *
 * @param     boot: Select nRST BOOT1 RST/SET
 *
 * @retval    None
 */
void OB_OptionBytesBoot1(OB_BOOT1_T boot)
{
    OB->USER_B.BOT1 = boot;
}

/*!
 * @brief     Option Bytes VDDA_Analog_Monitoring
 *
 * @param     vdda: Select VDDA ANALOG OFF/ON
 *
 * @retval    None
 */
void OB_OptionBytesVddaAnalog(OB_VDDA_T vdda)
{
    OB->USER_B.VDDAMON = vdda;
}

/*!
 * @brief     Option Bytes RAM PARITY CHECK
 *
 * @param     rpc: Select RAM PARITY OFF/ON
 *
 * @retval    None
 */
void OB_OptionBytesRamParity(OB_RAM_PARITY_CHECK_T ramParityCheck)
{
    OB->USER_B.RPC = ramParityCheck;
}

/**@} end of group OB_Functions */
/**@} end of group OB_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
