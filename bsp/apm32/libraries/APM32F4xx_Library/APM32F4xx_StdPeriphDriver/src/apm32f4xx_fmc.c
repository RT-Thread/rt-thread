/*!
 * @file        apm32f4xx_fmc.c
 *
 * @brief       This file provides all the FMC firmware functions
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

#include "apm32f4xx_fmc.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup FMC_Driver
  * @brief FMC driver modules
  @{
*/

/** @defgroup FMC_Functions
  @{
*/

/*!
 * @brief     Configs the code latency value.
 *
 * @param     latency: the FMC Latency value.
 *            This parameter can be one of the following values:
 *            @arg FMC_LTNCY_0: FMC 0 Latency cycle
 *            @arg FMC_LTNCY_1: FMC 1 Latency cycle
 *            @arg FMC_LTNCY_2: FMC 2 Latency cycles
 *            @arg FMC_LTNCY_3: FMC 3 Latency cycles
 *            @arg FMC_LTNCY_4: FMC 4 Latency cycles
 *            @arg FMC_LTNCY_5: FMC 5 Latency cycles
 *            @arg FMC_LTNCY_6: FMC 6 Latency cycles
 *            @arg FMC_LTNCY_7: FMC 7 Latency cycles
 *
 * @retval    None
 */
void FMC_ConfigLatency(FMC_LATENCY_T latency)
{
    *(__IO uint8_t *)ACCTRL_BYTE0_ADDRESS = (uint8_t)latency;
}

/*!
 * @brief     Enable the Prefetch Buffer.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_EnablePrefetchBuffer(void)
{
    FMC->ACCTRL |= FMC_ACCTRL_PREFEN;
}

/*!
 * @brief     Disable the Prefetch Buffer.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_DisablePrefetchBuffer(void)
{
    FMC->ACCTRL &= (~FMC_ACCTRL_PREFEN);
}

/*!
 * @brief     Enable the Instruction Cache feature.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_EnableInstructionCache(void)
{
    FMC->ACCTRL |= FMC_ACCTRL_ICACHEEN;
}

/*!
 * @brief     Disable the Instruction Cache feature.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_DisableInstructionCache(void)
{
    FMC->ACCTRL &= (~FMC_ACCTRL_ICACHEEN);
}

/*!
 * @brief     Enable the Data Cache feature.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_EnableDataCache(void)
{
    FMC->ACCTRL |= FMC_ACCTRL_DCACHEEN;
}

/*!
 * @brief     Disable the Data Cache feature.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_DisableDataCache(void)
{
    FMC->ACCTRL &= (~FMC_ACCTRL_DCACHEEN);
}

/*!
 * @brief     Reset the Instruction Cache feature.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_ResetInstructionCache(void)
{
    FMC->ACCTRL |= FMC_ACCTRL_ICACHERST;
}

/*!
 * @brief     Reset the Data Cache feature.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_ResetDataCache(void)
{
    FMC->ACCTRL |= FMC_ACCTRL_DCACHERST;
}

/*!
 * @brief     Unlocks the FMC control register access.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_Unlock(void)
{
    if ((FMC->CTRL & FMC_CTRL_LOCK) != RESET)
    {
        FMC->KEY = FMC_KEY1;
        FMC->KEY = FMC_KEY2;
    }
}

/*!
 * @brief     Locks the FMC control register access.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_Lock(void)
{
    FMC->CTRL |= FMC_CTRL_LOCK;
}

/*!
 * @brief     Erases a specified FMC Sector.
 *
 * @param     sector: The Sector number to be erased.
 *            This parameter can be a value between FMC_SECTOR_0 and FMC_SECTOR_11.
 *
 * @param     voltageRange: The device voltage range which defines the erase parallelism.
 *            This parameter can be one of the following values:
 *              @arg FMC_VOLTAGE_1: when the device voltage range is 1.8V to 2.1V,
 *                                  the operation will be done by byte (8-bit)
 *              @arg FMC_VOLTAGE_2: when the device voltage range is 2.1V to 2.7V,
 *                                  the operation will be done by half word (16-bit)
 *              @arg FMC_VOLTAGE_3: when the device voltage range is 2.7V to 3.6V,
 *                                  the operation will be done by word (32-bit)
 *              @arg FMC_VOLTAGE_4: when the device voltage range is 2.7V to 3.6V + External Vpp,
 *                                  the operation will be done by double word (64-bit)
 *
 * @retval    FMC_STATUS_T: The returned value can be:
 *            FMC_BUSY, FMC_ERROR_PROGRAM, FMC_ERROR_WRP, FMC_ERROR_OPERATION or FMC_COMPLETE.
 */
FMC_STATUS_T FMC_EraseSector(FMC_SECTOR_T sector, FMC_VOLTAGE_T voltageRange)
{
    uint32_t tmp_psize = 0x00;
    FMC_STATUS_T status = FMC_COMPLETE;

    if (voltageRange == FMC_VOLTAGE_1)
    {
        tmp_psize = FMC_PSIZE_BYTE;
    }
    else if (voltageRange == FMC_VOLTAGE_2)
    {
        tmp_psize = FMC_PSIZE_HALF_WORD;
    }
    else if (voltageRange == FMC_VOLTAGE_3)
    {
        tmp_psize = FMC_PSIZE_WORD;
    }
    else if (voltageRange == FMC_VOLTAGE_4)
    {
        tmp_psize = FMC_PSIZE_DOUBLE_WORD;
    }

    status = FMC_WaitForLastOperation();

    if (status == FMC_COMPLETE)
    {
        FMC->CTRL &= 0xFFFFFCFF;
        FMC->CTRL |= tmp_psize;
        FMC->CTRL &= 0xFFFFFF07;
        FMC->CTRL |= FMC_CTRL_SERS | sector;
        FMC->CTRL |= FMC_CTRL_START;
        status = FMC_WaitForLastOperation();
        FMC->CTRL &= (~FMC_CTRL_SERS);
        FMC->CTRL &= 0xFFFFFF07;
    }

    return status;
}

/*!
 * @brief     Clears all FMC Sectors.
 *
 * @param     voltageRange: The device voltage range which defines the erase parallelism.
 *            This parameter can be one of the following values:
 *              @arg FMC_VOLTAGE_1: when the device voltage range is 1.8V to 2.1V,
 *                                  the operation will be done by byte (8-bit)
 *              @arg FMC_VOLTAGE_2: when the device voltage range is 2.1V to 2.7V,
 *                                  the operation will be done by half word (16-bit)
 *              @arg FMC_VOLTAGE_3: when the device voltage range is 2.7V to 3.6V,
 *                                  the operation will be done by word (32-bit)
 *              @arg FMC_VOLTAGE_4: when the device voltage range is 2.7V to 3.6V + External Vpp,
 *                                  the operation will be done by double word (64-bit)
 *
 * @retval    FMC_STATUS_T: The returned value can be:
 *            FMC_BUSY, FMC_ERROR_PROGRAM, FMC_ERROR_WRP, FMC_ERROR_OPERATION or FMC_COMPLETE.
 */
FMC_STATUS_T FMC_EraseAllSectors(FMC_VOLTAGE_T voltageRange)
{
    uint32_t tmp_psize = 0x00;
    FMC_STATUS_T status = FMC_COMPLETE;
    status = FMC_WaitForLastOperation();

    if (voltageRange == FMC_VOLTAGE_1)
    {
        tmp_psize = FMC_PSIZE_BYTE;
    }
    else if (voltageRange == FMC_VOLTAGE_2)
    {
        tmp_psize = FMC_PSIZE_HALF_WORD;
    }
    else if (voltageRange == FMC_VOLTAGE_3)
    {
        tmp_psize = FMC_PSIZE_WORD;
    }
    else if (voltageRange == FMC_VOLTAGE_4)
    {
        tmp_psize = FMC_PSIZE_DOUBLE_WORD;
    }

    if (status == FMC_COMPLETE)
    {
        FMC->CTRL &= 0xFFFFFCFF;
        FMC->CTRL |= tmp_psize;
        FMC->CTRL |= FMC_CTRL_MERS;
        FMC->CTRL |= FMC_CTRL_START;
        status = FMC_WaitForLastOperation();
        FMC->CTRL &= (~FMC_CTRL_MERS);
    }

    return status;
}

/*!
 * @brief     Programs a double word (64-bit) at a specified address.
 *
 * @param     address:the address to be programmed.
 *            ((address) >= 0x08000000) && ((address) <= 0x080FFFFF))
 *            ((address) >= 0x1FFF7800) && ((address) <= 0x1FFF7A0F)))
 *
 * @param     data: the data to be programmed.
 *
 * @retval    FMC_STATUS_T: The returned value can be:
 *            FMC_BUSY, FMC_ERROR_PROGRAM, FMC_ERROR_WRP, FMC_ERROR_OPERATION or FMC_COMPLETE.
 */
FMC_STATUS_T FMC_ProgramDoubleWord(uint32_t address, uint64_t data)
{
    FMC_STATUS_T status = FMC_COMPLETE;
    status = FMC_WaitForLastOperation();

    if (status == FMC_COMPLETE)
    {
        FMC->CTRL &= 0xFFFFFCFF;
        FMC->CTRL |= FMC_PSIZE_DOUBLE_WORD;
        FMC->CTRL |= FMC_CTRL_PG;
        *(__IO uint64_t *)address = data;
        status = FMC_WaitForLastOperation();
        FMC->CTRL &= (~FMC_CTRL_PG);
    }

    return status;
}

/*!
 * @brief     Programs a word (32-bit) at a specified address.
 *
 * @param     address:the address to be programmed.
 *            ((address) >= 0x08000000) && ((address) <= 0x080FFFFF))
 *            ((address) >= 0x1FFF7800) && ((address) <= 0x1FFF7A0F)))
 *
 * @param     data: the data to be programmed.
 *
 * @retval    FMC_STATUS_T: The returned value can be:
 *            FMC_BUSY, FMC_ERROR_PROGRAM, FMC_ERROR_WRP, FMC_ERROR_OPERATION or FMC_COMPLETE.
 */

FMC_STATUS_T FMC_ProgramWord(uint32_t address, uint32_t data)
{
    FMC_STATUS_T status = FMC_COMPLETE;
    status = FMC_WaitForLastOperation();

    if (status == FMC_COMPLETE)
    {
        FMC->CTRL &= 0xFFFFFCFF;
        FMC->CTRL |= FMC_PSIZE_WORD;
        FMC->CTRL |= FMC_CTRL_PG;
        *(__IO uint32_t *)address = data;
        status = FMC_WaitForLastOperation();
        FMC->CTRL &= (~FMC_CTRL_PG);
    }

    return status;
}

/*!
 * @brief     Programs a half word (16-bit) at a specified address.
 *
 * @param     address:the address to be programmed.
 *            ((address) >= 0x08000000) && ((address) <= 0x080FFFFF))
 *            ((address) >= 0x1FFF7800) && ((address) <= 0x1FFF7A0F)))
 *
 * @param     data: the data to be programmed.
 *
 * @retval    FMC_STATUS_T: The returned value can be:
 *            FMC_BUSY, FMC_ERROR_PROGRAM, FMC_ERROR_WRP, FMC_ERROR_OPERATION or FMC_COMPLETE.
 */
FMC_STATUS_T FMC_ProgramHalfWord(uint32_t address, uint16_t data)
{
    FMC_STATUS_T status = FMC_COMPLETE;
    status = FMC_WaitForLastOperation();

    if (status == FMC_COMPLETE)
    {
        FMC->CTRL &= 0xFFFFFCFF;
        FMC->CTRL |= FMC_PSIZE_HALF_WORD;
        FMC->CTRL |= FMC_CTRL_PG;
        *(__IO uint16_t *)address = data;
        status = FMC_WaitForLastOperation();
        FMC->CTRL &= (~FMC_CTRL_PG);
    }

    return status;
}

/*!
 * @brief     Programs a byte (8-bit) at a specified address.
 *
 * @param     address:the address to be programmed.
 *            ((address) >= 0x08000000) && ((address) <= 0x080FFFFF))
 *            ((address) >= 0x1FFF7800) && ((address) <= 0x1FFF7A0F)))
 *
 * @param     data: the data to be programmed.
 *
 * @retval    FMC_STATUS_T: The returned value can be:
 *            FMC_BUSY, FMC_ERROR_PROGRAM, FMC_ERROR_WRP, FMC_ERROR_OPERATION or FMC_COMPLETE.
 */
FMC_STATUS_T FMC_ProgramByte(uint32_t address, uint8_t data)
{
    FMC_STATUS_T status = FMC_COMPLETE;
    status = FMC_WaitForLastOperation();

    if (status == FMC_COMPLETE)
    {
        FMC->CTRL &= 0xFFFFFCFF;
        FMC->CTRL |= FMC_PSIZE_BYTE;
        FMC->CTRL |= FMC_CTRL_PG;
        *(__IO uint8_t *)address = data;
        status = FMC_WaitForLastOperation();
        FMC->CTRL &= (~FMC_CTRL_PG);
    }

    return status;
}

/*!
 * @brief     Unlocks the option bytes block access
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_UnlockOptionByte(void)
{
    if ((FMC->OPTCTRL & FMC_OPTCTRL_OPTLOCK) != RESET)
    {
        FMC->OPTKEY = FMC_OPT_KEY1;
        FMC->OPTKEY = FMC_OPT_KEY2;
    }
}

/*!
 * @brief     Locks the option bytes block access
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_LockOptionByte(void)
{
    FMC->OPTCTRL |= FMC_OPTCTRL_OPTLOCK;
}

/*!
 * @brief     Enable the write protection of the desired sectors,
 *            for the first 1 Mb of the FMC
 *
 * @param     wrp: specifies the sector(s) to be write protected or unprotected.
 *            This parameter can be one of the following values:
 *              @arg wrp: The value between FMC_OPT_WRP_SECTOR_0 and FMC_OPT_WRP_SECTOR_11
 *              @arg FMC_OPT_WRP_SECTOR_All
 *
 * @retval    None
 */
void FMC_OPT_EnableWriteProtect(FMC_OPT_WRP_T wrp)
{
    FMC_STATUS_T status = FMC_COMPLETE;
    status = FMC_WaitForLastOperation();

    if (status == FMC_COMPLETE)
    {
        *(__IO uint16_t *)(OPTCTRL_BYTE2_ADDRESS) &= (~(uint16_t)wrp);
    }
}

/*!
 * @brief     Disable the write protection of the desired sectors,
 *            for the first 1 Mb of the FMC
 *
 * @param     wrp: Specifies the sector(s) to be write protected or unprotected.
 *            This parameter can be one of the following values:
 *              @arg wrp: The value between FMC_OPT_WRP_SECTOR_0 and FMC_OPT_WRP_SECTOR_11
 *              @arg FMC_OPT_WRP_SECTOR_All
 *
 * @retval    None
 */
void FMC_OPT_DisableWriteProtect(FMC_OPT_WRP_T wrp)
{
    FMC_STATUS_T status = FMC_COMPLETE;
    status = FMC_WaitForLastOperation();

    if (status == FMC_COMPLETE)
    {
        *(__IO uint16_t *)(OPTCTRL_BYTE2_ADDRESS) |= (uint16_t)wrp;
    }
}
/*!
 * @brief     Sets the read protection level.
 *
 * @param     rdp: Specifies the read protection level.
 *            This parameter can be one of the following values:
 *              @arg FMC_OPT_RDP_LV0: No protection
 *              @arg FMC_OPT_RDP_LV1: Read protection of the memory
 *
 * @retval    None
 */
void FMC_OPT_ConfigReadProtect(FMC_OPT_RDP_T rdp)
{
    FMC_STATUS_T status = FMC_COMPLETE;
    status = FMC_WaitForLastOperation();

    if (status == FMC_COMPLETE)
    {
        *(__IO uint8_t *)OPTCTRL_BYTE1_ADDRESS = rdp;
    }
}

/*!
 * @brief     Programs the FMC User Option Byte: WDTSEL / RSTSTOP / RSTSTDB.
 *
 * @param     iwdt: Selects the IWDT mode
 *            This parameter can be one of the following values:
 *              @arg FMC_OPT_IWDT_SOFT: Software IWDT selected
 *              @arg FMC_OPT_IWDT_HARD: Hardware IWDT selected
 * @param     stop: Reset event when entering STOP mode.
 *            This parameter  can be one of the following values:
 *              @arg FMC_OPT_STOP_NORST: No reset generated when entering in STOP
 *              @arg FMC_OPT_STOP_RST: Reset generated when entering in STOP
 * @param     stdby: Reset event when entering Standby mode.
 *            This parameter  can be one of the following values:
 *              @arg FMC_OPT_STDBY_NORST: No reset generated when entering in STANDBY
 *              @arg FMC_OPT_STDBY_RST: Reset generated when entering in STANDBY
 *
 * @retval    None
 */
void FMC_OPT_ConfigUser(FMC_OPT_IWDT_T iwdt, FMC_OPT_STOP_T stop, FMC_OPT_STDBY_T stdby)
{
    uint8_t option = 0xFF;
    FMC_STATUS_T status = FMC_COMPLETE;
    status = FMC_WaitForLastOperation();

    if (status == FMC_COMPLETE)
    {
        option = (uint8_t)((*(__IO uint8_t *)OPTCTRL_BYTE0_ADDRESS) & 0x0F);
        *(__IO uint8_t *)OPTCTRL_BYTE0_ADDRESS = ((uint8_t)iwdt | stop | stdby | option);
    }
}

/*!
 * @brief     Sets the Brownout Reset Level.
 *
 * @param     bor: specifies the Option Bytes BOR Reset Level.
 *            This parameter can be one of the following values:
 *              @arg FMC_OPT_BOR_LV3: Supply voltage ranges from 2.7 to 3.6 V
 *              @arg FMC_OPT_BOR_LV2: Supply voltage ranges from 2.4 to 2.7 V
 *              @arg FMC_OPT_BOR_LV1: Supply voltage ranges from 2.1 to 2.4 V
 *              @arg FMC_OPT_BOR_OFF: Supply voltage ranges from 1.62 to 2.1 V
 *
 * @retval    None
 */
void FMC_OPT_ConfigBrownoutReset(FMC_OPT_BOR_T bor)
{
    *(__IO uint8_t *)(OPTCTRL_BYTE0_ADDRESS) &= (~(FMC_OPTCTRL_BORLVL));
    *(__IO uint8_t *)(OPTCTRL_BYTE0_ADDRESS) |= bor;
}

/*!
 * @brief     Launch the option byte loading.
 *
 * @param     None
 *
 * @retval    FMC_STATUS_T: The returned value can be:
 *            FMC_BUSY, FMC_ERROR_PROGRAM, FMC_ERROR_WRP, FMC_ERROR_OPERATION or FMC_COMPLETE.
 */
FMC_STATUS_T FMC_OPT_Launch(void)
{
    FMC_STATUS_T status = FMC_COMPLETE;

    *(__IO uint8_t *)(OPTCTRL_BYTE0_ADDRESS) |= (uint32_t)FMC_OPTCTRL_OPTSTART;
    status = FMC_WaitForLastOperation();

    return status;
}

/*!
 * @brief     Returns the FMC User Option Bytes values.
 *
 * @param     None
 *
 * @retval    The FMC User Option Bytes values: WDTSEL(Bit0), RSTSTOP(Bit1)
 *            and RSTSTDBY(Bit2).
 */
uint8_t FMC_OPT_ReadUser(void)
{
    return (uint8_t)(FMC->OPTCTRL >> 5);
}

/*!
 * @brief     Returns the FMC Write Protection Option Bytes value.
 *
 * @param     None
 *
 * @retval    The FMC Write Protection Option Bytes value
 */
uint16_t FMC_OPT_ReadWriteProtect(void)
{
    return (*(__IO uint16_t *)(OPTCTRL_BYTE2_ADDRESS));
}

/*!
 * @brief     Returns the FMC Read Protection level.
 *
 * @param     None
 *
 * @retval    tmp: ReadOut Protection Status:
 *                 - SET, when FMC_OPT_RDP_LV1 is set
 *                 - RESET, when FMC_OPT_RDP_LV0 is set
 */
uint8_t FMC_OPT_ReadProtectLevel(void)
{
    uint8_t tmp = RESET;

    if ((*(__IO uint8_t *)((OPTCTRL_BYTE1_ADDRESS)) != (uint8_t)FMC_OPT_RDP_LV0))
    {
        tmp = SET;
    }

    return tmp;
}

/*!
 * @brief     Returns the FMC BOR level.
 *
 * @param     None
 *
 * @retval    The FMC BOR level:
 *              - FMC_OPT_BOR_LV1: Supply voltage ranges from 2.7 to 3.6 V
 *              - FMC_OPT_BOR_LV1: Supply voltage ranges from 2.4 to 2.7 V
 *              - FMC_OPT_BOR_LV1: Supply voltage ranges from 2.1 to 2.4 V
 *              - FMC_OPT_BOR_OFF   : Supply voltage ranges from 1.62 to 2.1 V
 */
uint8_t FMC_OPT_ReadBrownoutReset(void)
{
    return (uint8_t)(*(__IO uint8_t *)((OPTCTRL_BYTE0_ADDRESS)) & FMC_OPT_BOR_OFF);
}

/*!
 * @brief     Enables the specified FMC interrupts.
 *
 * @param     interrupt: Select the FMC interrupt sources
 *                       This parameter can be any combination of the following values:
 *                       @arg FMC_INT_ERR :  Error Interrupt
 *                       @arg FMC_INT_OC  :  Operation Complete Interrupt
 *
 * @retval    None
 */
void FMC_EnableInterrupt(uint32_t interrupt)
{
    if (interrupt == FMC_INT_ERR)
    {
        FMC->CTRL |= FMC_INT_ERR;
    }
    else
    {
        FMC->CTRL |= FMC_INT_OC;
    }
}

/*!
 * @brief     Disable the specified FMC interrupts.
 *
 * @param     interrupt: Select the FMC interrupt sources
 *                       This parameter can be any combination of the following values:
 *                       @arg FMC_INT_ERR :  Error Interrupt
 *                       @arg FMC_INT_OC  :  Operation Complete Interrupt
 *
 * @retval    None
 */
void FMC_DisableInterrupt(uint32_t interrupt)
{
    if (interrupt == FMC_INT_ERR)
    {
        FMC->CTRL &= ~(uint32_t)FMC_INT_ERR;
    }
    else
    {
        FMC->CTRL &= ~(uint32_t)FMC_INT_OC;
    }
}

/*!
 * @brief     Read the FMC flag
 *
 * @param     flag: specifies the FMC flag to check.
 *            This parameter can be one of the following values:
 *              @arg FMC_FLAG_ENDOP  : FMC End of Operation flag
 *              @arg FMC_FLAG_ERROP  : FMC operation Error flag
 *              @arg FMC_FLAG_ERRWRP : FMC Write protected error flag
 *              @arg FMC_FLAG_ERRPGA : FMC Programming Alignment error flag
 *              @arg FMC_FLAG_ERRPGP : FMC Programming Parallelism error flag
 *              @arg FMC_FLAG_ERRPGS : FMC Programming Sequence error flag
 *              @arg FMC_FLAG_BUSY   : FMC Busy flag
 *
 * @retval    SET or RESET.
 */
uint8_t FMC_ReadStatusFlag(FMC_FLAG_T flag)
{
    uint8_t temp = RESET;

    if ((FMC->STS & flag) != (uint32_t)RESET)
    {
        temp = SET;
    }

    return temp;
}

/*!
 * @brief     Clears the FMC flag.
 *
 * @param     flag: specifies the FMC flags to clear.
 *            This parameter can be any combination of the following values:
 *              @arg FMC_FLAG_ENDOP  : FMC End of Operation flag
 *              @arg FMC_FLAG_ERROP  : FMC operation Error flag
 *              @arg FMC_FLAG_ERRWRP : FMC Write protected error flag
 *              @arg FMC_FLAG_ERRPGA : FMC Programming Alignment error flag
 *              @arg FMC_FLAG_ERRPGP : FMC Programming Parallelism error flag
 *              @arg FMC_FLAG_ERRPGS : FMC Programming Sequence error flag
 *
 * @retval    None
 */
void FMC_ClearStatusFlag(uint32_t flag)
{
    FMC->STS = flag;
}

/*!
 * @brief     Returns the FMC Status.
 *
 * @param     None
 *
 * @retval    FMC_STATUS_T: The returned value can be:
 *            FMC_BUSY, FMC_ERROR_PROGRAM, FMC_ERROR_WRP, FMC_ERROR_OPERATION or FMC_COMPLETE.
 */
FMC_STATUS_T FMC_ReadStatus(void)
{
    FMC_STATUS_T status = FMC_COMPLETE;

    if ((FMC->STS & FMC_FLAG_BUSY) == FMC_FLAG_BUSY)
    {
        status = FMC_BUSY;
    }
    else if ((FMC->STS & FMC_FLAG_ERRWRP) != RESET)
    {
        status = FMC_ERROR_WRP;
    }
    else if ((FMC->STS & (uint32_t)0xE0) != RESET)
    {
        status = FMC_ERROR_PROGRAM;
    }
    else if ((FMC->STS & FMC_FLAG_ERROP) != RESET)
    {
        status = FMC_ERROR_OPERATION;
    }
    else
    {
        status = FMC_COMPLETE;
    }

    return status;
}

/*!
 * @brief     Waits for a FMC operation to complete.
 *
 * @param     None
 *
 * @retval    FMC_STATUS_T: The returned value can be:
 *            FMC_BUSY, FMC_ERROR_PROGRAM, FMC_ERROR_WRP, FMC_ERROR_OPERATION or FMC_COMPLETE.
 */
FMC_STATUS_T FMC_WaitForLastOperation(void)
{
    __IO FMC_STATUS_T status = FMC_COMPLETE;

    status = FMC_ReadStatus();

    while (status == FMC_BUSY)
    {
        status = FMC_ReadStatus();
    }

    return status;
}

/**@} end of group FMC_Functions */
/**@} end of group FMC_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
