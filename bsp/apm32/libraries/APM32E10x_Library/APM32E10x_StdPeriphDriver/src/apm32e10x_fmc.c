/*!
 * @file       apm32e10x_fmc.c
 *
 * @brief      This file provides all the FMC firmware functions
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

#include "apm32e10x_fmc.h"
#include "apm32e10x_rcm.h"

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup FMC_Driver
  * @brief FMC driver modules
  @{
*/

/** @defgroup FMC_Functions Functions
  @{
*/

/*!
 * @brief     Configs the code latency value.
 *
 * @param     latency: the FMC Latency value.
 *
 * @retval    None
 */
void FMC_ConfigLatency(FMC_LATENCY_T latency)
{
    FMC->CTRL1_B.WS = latency;
}

/*!
 * @brief     Enables the Half cycle flash access.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_EnableHalfCycleAccess(void)
{
    FMC->CTRL1_B.HCAEN = BIT_SET;
}

/*!
 * @brief     Disable the Half cycle flash access.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_DisableHalfCycleAccess(void)
{
    FMC->CTRL1_B.HCAEN = BIT_RESET;
}

/*!
 * @brief     Enables the Prefetch Buffer.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_EnablePrefetchBuffer(void)
{
    FMC->CTRL1_B.PBEN = ENABLE;
}

/*!
 * @brief     Disables the Prefetch Buffer.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_DisablePrefetchBuffer(void)
{
    FMC->CTRL1_B.PBEN = DISABLE;
}

/*!
 * @brief     Unlocks the FMC Program Erase Controller
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_Unlock(void)
{
    FMC->KEY = 0x45670123;
    FMC->KEY = 0xCDEF89AB;
}

/*!
 * @brief     Locks the FMC Program Erase Controller.
 *
 * @param     None
 *
 * @retval    None
 */
void FMC_Lock(void)
{
    FMC->CTRL2_B.LOCK = BIT_SET;
}

/*!
 * @brief     Erases a specified FMC page.
 *
 * @param     pageAddr: The page address to be erased.
 *
 * @retval    Returns the flash state.It can be one of value:
 *                 @arg FMC_STATUS_BUSY
 *                 @arg FMC_STATUS_ERROR_PG
 *                 @arg FMC_STATUS_ERROR_WRP
 *                 @arg FMC_STATUS_COMPLETE
 *                 @arg FMC_STATUS_TIMEOUT
 */
FMC_STATUS_T FMC_ErasePage(uint32_t pageAddr)
{
    FMC_STATUS_T status = FMC_STATUS_COMPLETE;

    status = FMC_WaitForLastOperation(0x000B0000);
    if(status == FMC_STATUS_COMPLETE)
    {
        FMC->CTRL2_B.PAGEERA = BIT_SET;
        FMC->ADDR = pageAddr;
        FMC->CTRL2_B.STA = BIT_SET;

        status = FMC_WaitForLastOperation(0x000B0000);
        FMC->CTRL2_B.PAGEERA = BIT_RESET;
    }
    return status;
}

/*!
 * @brief     Erases all FMC pages.
 *
 * @param     None
 *
 * @retval    Returns the flash state.It can be one of value:
 *                 @arg FMC_STATUS_ERROR_PG
 *                 @arg FMC_STATUS_ERROR_WRP
 *                 @arg FMC_STATUS_COMPLETE
 *                 @arg FMC_STATUS_TIMEOUT
 */
FMC_STATUS_T FMC_EraseAllPage(void)
{
    FMC_STATUS_T status = FMC_STATUS_COMPLETE;

    status = FMC_WaitForLastOperation(0x000B0000);
    if(status == FMC_STATUS_COMPLETE)
    {
        FMC->CTRL2_B.MASSERA = BIT_SET;
        FMC->CTRL2_B.STA = BIT_SET;

        status = FMC_WaitForLastOperation(0x000B0000);
        FMC->CTRL2_B.MASSERA = BIT_RESET;
    }
    return status;
}

/*!
 * @brief     Erases the FMC option bytes.
 *
 * @param     None
 *
 * @retval    Returns the flash state.It can be one of value:
 *                 @arg FMC_STATUS_ERROR_PG
 *                 @arg FMC_STATUS_ERROR_WRP
 *                 @arg FMC_STATUS_COMPLETE
 *                 @arg FMC_STATUS_TIMEOUT
 */
FMC_STATUS_T FMC_EraseOptionBytes(void)
{
    uint16_t rdtemp = 0x00A5;
    FMC_STATUS_T status = FMC_STATUS_COMPLETE;

    if(FMC_GetReadProtectionStatus() != RESET)
    {
        rdtemp = 0x00;
    }
    status = FMC_WaitForLastOperation(0x000B0000);
    if(status == FMC_STATUS_COMPLETE)
    {
        FMC->OBKEY = 0x45670123;
        FMC->OBKEY = 0xCDEF89AB;

        FMC->CTRL2_B.OBE = BIT_SET;
        FMC->CTRL2_B.STA = BIT_SET;

        status = FMC_WaitForLastOperation(0x000B0000);

        if(status == FMC_STATUS_COMPLETE)
        {
            FMC->CTRL2_B.OBE = BIT_RESET;
            FMC->CTRL2_B.OBP = BIT_SET;
            OB->RDP = rdtemp;
            status = FMC_WaitForLastOperation(0x000B0000);
            if(status != FMC_STATUS_TIMEOUT)
            {
                FMC->CTRL2_B.OBP = BIT_RESET;
            }
        }
        else if(status != FMC_STATUS_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }
    return status;
}

/*!
 * @brief     Programs a word at a specified address.
 *
 * @param     address:the address to be programmed.
 *
 * @param     data: the data to be programmed.
 *
 * @retval    Returns the flash state.It can be one of value:
 *                 @arg FMC_STATUS_ERROR_PG
 *                 @arg FMC_STATUS_ERROR_WRP
 *                 @arg FMC_STATUS_COMPLETE
 *                 @arg FMC_STATUS_TIMEOUT
 */
FMC_STATUS_T FMC_ProgramWord(uint32_t address, uint32_t data)
{
    FMC_STATUS_T status = FMC_STATUS_COMPLETE;
    __IOM uint32_t temp = 0;


    __set_PRIMASK(1);


    status = FMC_WaitForLastOperation(0x000B0000);

    if(status == FMC_STATUS_COMPLETE)
    {
        FMC->CTRL2_B.PG = BIT_SET;

        *(__IOM uint16_t *)address = data;

        status = FMC_WaitForLastOperation(0x000B0000);

        if(status == FMC_STATUS_COMPLETE)
        {
            temp = address + 2;

            *(__IOM uint16_t*) temp = data >> 16;

            status = FMC_WaitForLastOperation(0x000B0000);
            FMC->CTRL2_B.PG = BIT_RESET;
        }
        else
        {
            FMC->CTRL2_B.PG = BIT_RESET;
        }
    }

    
    __set_PRIMASK(0);
    

    return status;
}

/*!
 * @brief     Programs a half word at a specified address.
 *
 * @param     address:the address to be programmed.
 *
 * @param     data: the data to be programmed.
 *
 * @retval    Returns the flash state.It can be one of value:
 *                 @arg FMC_STATUS_ERROR_PG
 *                 @arg FMC_STATUS_ERROR_WRP
 *                 @arg FMC_STATUS_COMPLETE
 *                 @arg FMC_STATUS_TIMEOUT
 */
FMC_STATUS_T FMC_ProgramHalfWord(uint32_t address, uint16_t data)
{
    FMC_STATUS_T status = FMC_STATUS_COMPLETE;

   
    __set_PRIMASK(1);
   

    status = FMC_WaitForLastOperation(0x000B0000);

    if(status == FMC_STATUS_COMPLETE)
    {
        FMC->CTRL2_B.PG = BIT_SET;
        *(__IOM uint16_t *)address = data;
        status = FMC_WaitForLastOperation(0x000B0000);
        FMC->CTRL2_B.PG = BIT_RESET;
    }

   
    __set_PRIMASK(0);
   

    return status;
}

/*!
 * @brief     Programs a half word at a specified Option Byte Data address.
 *
 * @param     address:the address to be programmed.
 *
 * @param     data: the data to be programmed.
 *
 * @retval    Returns the flash state.It can be one of value:
 *                 @arg FMC_STATUS_ERROR_PG
 *                 @arg FMC_STATUS_ERROR_WRP
 *                 @arg FMC_STATUS_COMPLETE
 *                 @arg FMC_STATUS_TIMEOUT
 */
FMC_STATUS_T FMC_ProgramOptionByteData(uint32_t address, uint8_t data)
{
    FMC_STATUS_T status = FMC_STATUS_COMPLETE;

    status = FMC_WaitForLastOperation(0x000B0000);

    if(status == FMC_STATUS_COMPLETE)
    {
        FMC->OBKEY = 0x45670123;
        FMC->OBKEY = 0xCDEF89AB;

        FMC->CTRL2_B.OBP = BIT_SET;
        *(__IOM uint16_t *)address = data;
        status = FMC_WaitForLastOperation(0x000B0000);
        if(status == FMC_STATUS_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }
    return status;
}

/*!
 * @brief     Write protects the desired pages
 *
 * @param     page:the address of the pages to be write protection
 *                This parameter can be any combination of the following values:
 *                 for APM32E10X_LD ：
 *                    @arg FLASH_WRP_PAGE_0_3 to FLASH_WRP_PAGE_28_31
 *                 for APM32E10X_MD ：
 *                    @arg FLASH_WRP_PAGE_0_3 to FLASH_WRP_PAGE_124_127
 *                 for APM32E10X_HD ：
 *                 @arg FLASH_WRP_PAGE_0_1 to FLASH_WRP_PAGE_60_61 or FLASH_WRP_PAGE_62_127
 *                 @arg FMC_WRP_PAGE_ALL
 *
 * @retval    Returns the flash state.It can be one of value:
 *                 @arg FMC_STATUS_ERROR_PG
 *                 @arg FMC_STATUS_ERROR_WRP
 *                 @arg FMC_STATUS_COMPLETE
 *                 @arg FMC_STATUS_TIMEOUT
 */
FMC_STATUS_T FMC_EnableWriteProtection(uint32_t page)
{
    uint16_t WPP0_Data = 0xFFFF, WPP1_Data = 0xFFFF, WPP2_Data = 0xFFFF, WPP3_Data = 0xFFFF;
    FMC_STATUS_T status = FMC_STATUS_COMPLETE;

    page = ~page;
    WPP0_Data = (page & 0x000000FF);
    WPP1_Data = (page & 0x0000FF00) >> 8;
    WPP2_Data = (page & 0x00FF0000) >> 16;
    WPP3_Data = (page & 0xFF000000) >> 24;

    status = FMC_WaitForLastOperation(0x000B0000);

    if(status == FMC_STATUS_COMPLETE)
    {
        FMC->OBKEY = 0x45670123;
        FMC->OBKEY = 0xCDEF89AB;
        FMC->CTRL2_B.OBP = BIT_SET;

        if(WPP0_Data != 0xFF)
        {
            OB->WRP0 = WPP0_Data;
            status = FMC_WaitForLastOperation(0x000B0000);
        }
        if((status == FMC_STATUS_COMPLETE) && (WPP1_Data != 0xFF))
        {
            OB->WRP1 = WPP1_Data;
            status = FMC_WaitForLastOperation(0x000B0000);
        }
        if((status == FMC_STATUS_COMPLETE) && (WPP2_Data != 0xFF))
        {
            OB->WRP2 = WPP2_Data;
            status = FMC_WaitForLastOperation(0x000B0000);
        }
        if((status == FMC_STATUS_COMPLETE) && (WPP3_Data != 0xFF))
        {
            OB->WRP3 = WPP3_Data;
            status = FMC_WaitForLastOperation(0x000B0000);
        }

        if(status != FMC_STATUS_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }
    return status;
}

/*!
 * @brief     Enables the read out protection.
 *
 * @param     None
 *
 * @retval    Returns the flash state.It can be one of value:
 *                 @arg FMC_STATUS_ERROR_PG
 *                 @arg FMC_STATUS_ERROR_WRP
 *                 @arg FMC_STATUS_COMPLETE
 *                 @arg FMC_STATUS_TIMEOUT
 */
FMC_STATUS_T FMC_EnableReadOutProtection(void)
{
    FMC_STATUS_T status = FMC_STATUS_COMPLETE;

    status = FMC_WaitForLastOperation(0x000B0000);

    if(status == FMC_STATUS_COMPLETE)
    {
        FMC->OBKEY = 0x45670123;
        FMC->OBKEY = 0xCDEF89AB;

        FMC->CTRL2_B.OBE = BIT_SET;
        FMC->CTRL2_B.STA = BIT_SET;

        status = FMC_WaitForLastOperation(0x000B0000);

        if(status == FMC_STATUS_COMPLETE)
        {
            FMC->CTRL2_B.OBE = BIT_RESET;
            FMC->CTRL2_B.OBP = BIT_SET;
            OB->RDP = 0x00;

            status = FMC_WaitForLastOperation(0x000B0000);

            if(status != FMC_STATUS_TIMEOUT)
            {
                FMC->CTRL2_B.OBP = BIT_RESET;
            }
        }
        else if(status != FMC_STATUS_TIMEOUT)
        {
            FMC->CTRL2_B.OBE = BIT_RESET;
        }
    }
    return status;
}

/*!
 * @brief     Disables the read out protection.
 *
 * @param     None
 *
 * @retval    Returns the flash state.It can be one of value:
 *                 @arg FMC_STATUS_ERROR_PG
 *                 @arg FMC_STATUS_ERROR_WRP
 *                 @arg FMC_STATUS_COMPLETE
 *                 @arg FMC_STATUS_TIMEOUT
 */
FMC_STATUS_T FMC_DisableReadOutProtection(void)
{
    FMC_STATUS_T status = FMC_STATUS_COMPLETE;

    status = FMC_WaitForLastOperation(0x000B0000);

    if(status == FMC_STATUS_COMPLETE)
    {
        FMC->OBKEY = 0x45670123;
        FMC->OBKEY = 0xCDEF89AB;
        FMC->CTRL2_B.OBE = BIT_SET;
        FMC->CTRL2_B.STA = BIT_SET;

        status = FMC_WaitForLastOperation(0x000B0000);

        if(status == FMC_STATUS_COMPLETE)
        {
            FMC->CTRL2_B.OBE = BIT_RESET;
            FMC->CTRL2_B.OBP = BIT_SET;
            OB->RDP = 0x00A5;

            status = FMC_WaitForLastOperation(0x000B0000);

            if(status != FMC_STATUS_TIMEOUT)
            {
                FMC->CTRL2_B.OBP = BIT_RESET;
            }
        }
        else if(status != FMC_STATUS_TIMEOUT)
        {
            FMC->CTRL2_B.OBE = BIT_RESET;
        }
    }
    return status;
}

/*!
 * @brief     Programs the FMC User Option Byte.
 *
 * @param     userConfig: Point to a FMC_UserConfig_T structure.
 *
 * @retval    Returns the flash state.It can be one of value:
 *                 @arg FMC_STATUS_ERROR_PG
 *                 @arg FMC_STATUS_ERROR_WRP
 *                 @arg FMC_STATUS_COMPLETE
 *                 @arg FMC_STATUS_TIMEOUT
 */
FMC_STATUS_T FMC_ConfigUserOptionByte(FMC_UserConfig_T* userConfig)
{
    FMC_STATUS_T status = FMC_STATUS_COMPLETE;

    FMC->OBKEY = 0x45670123;
    FMC->OBKEY = 0xCDEF89AB;

    status = FMC_WaitForLastOperation(0x000B0000);

    if(status == FMC_STATUS_COMPLETE)
    {
        FMC->CTRL2_B.OBP = BIT_SET;
        OB->USER = (uint32_t)userConfig->iwdtSet | \
                   (uint32_t)userConfig->stopSet | \
                   (uint32_t)userConfig->stdbySet | 0xF8;
        status = FMC_WaitForLastOperation(0x000B0000);
        if(status == FMC_STATUS_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }
    return status;
}

/*!
 * @brief     Read the FMC User Option Bytes values.
 *
 * @param     None
 *
 * @retval    Returns User Option Bytes values
 */
uint32_t FMC_ReadUserOptionByte(void)
{
    return (FMC->OBCS_B.UOB >> 2);
}

/*!
 * @brief     Read the FMC Write Protection Option Bytes Register value.
 *
 * @param     None
 *
 * @retval    Returns the value of Option Bytes Write Protection Register.
 */
uint32_t FMC_ReadOptionByteWriteProtection(void)
{
    return FMC->WRTPROT;
}

/*!
 * @brief     Get the FMC Read Out Protection Status is set or not.
 *
 * @param     None
 *
 * @retval    status : set or reset.
 */
uint8_t FMC_GetReadProtectionStatus(void)
{
    uint8_t flagstatus = RESET;

    if(FMC->OBCS_B.READPROT != RESET)
    {
        flagstatus = SET;
    }
    else
    {
        flagstatus = RESET;
    }
    return flagstatus;
}

/*!
 * @brief     FMC Prefetch Buffer status is set or not.
 *
 * @param     None
 *
 * @retval    status : set or reset.
 */
uint8_t FMC_ReadPrefetchBufferStatus(void)
{
    return FMC->CTRL1_B.PBSF;
}

/*!
 * @brief     Enables the specified FMC interrupts.
 *
 * @param     interrupt: Select the FMC interrupt sources
 *                       This parameter can be one of the following values:
 *                       @arg FMC_INT_ERR :  Error Interrupt
 *                       @arg FMC_INT_OC  :  Operation Complete Interrupt
 *
 * @retval    None
 */
void FMC_EnableInterrupt(FMC_INT_T interrupt)
{
    if(interrupt == FMC_INT_ERR)
    {
        FMC->CTRL2_B.ERRIE = ENABLE;
    }
    else
    {
        FMC->CTRL2_B.OCIE = ENABLE;
    }
}

/*!
 * @brief     Disable the specified FMC interrupts.
 *
 * @param     interrupt: Select the FMC interrupt sources
 *                       This parameter can be one of the following values:
 *                       @arg FMC_INT_ERR :  Error Interrupt
 *                       @arg FMC_INT_OC  :  Operation Complete Interrupt
 *
 * @retval    None
 */
void FMC_DisableInterrupt(FMC_INT_T interrupt)
{
    if(interrupt == FMC_INT_ERR)
    {
        FMC->CTRL2_B.ERRIE = DISABLE;
    }
    else
    {
        FMC->CTRL2_B.OCIE = DISABLE;
    }
}

/*!
 * @brief     Read FMC flag is set or not
 *
 * @param     flag: status flag of FMC
 *                  This parameter can be one of the following values:
 *                  @arg FMC_FLAG_BUSY : FMC Busy flag
 *                  @arg FMC_FLAG_OC   : FMC Operation Complete flag
 *                  @arg FMC_FLAG_PE   : FMC Program error flag
 *                  @arg FMC_FLAG_WPE  : FMC Write protected error flag
 *                  @arg FMC_FLAG_OBE  : FMC Option Byte error flag
 *
 * @retval    flag status : set or reset
 */
uint8_t FMC_ReadStatusFlag(FMC_FLAG_T flag)
{
    if(flag == FMC_FLAG_OBE)
    {
        return FMC->OBCS_B.OBE;
    }
    else if((FMC->STS & flag ) != RESET)
    {
        return SET;
    }
    return RESET;
}

/*!
 * @brief     Clears the FMC's flag.
 *
 * @param     flag: status flag of FMC
 *                  This parameter can be any combination of the following values:
 *                  @arg FMC_FLAG_OC   : FMC Operation Complete flag
 *                  @arg FMC_FLAG_PE   : FMC Program error flag
 *                  @arg FMC_FLAG_WPE  : FMC Write protected error flag
 *
 * @retval    None
 *
 */
void FMC_ClearStatusFlag(uint32_t flag)
{
    FMC->STS = flag;
}

/*!
 * @brief     Read the FMC Status.
 *
 * @param     None
 *
 * @retval    Returns the flash state.It can be one of value:
 *                 @arg FMC_STATUS_BUSY
 *                 @arg FMC_STATUS_ERROR_PG
 *                 @arg FMC_STATUS_ERROR_WRP
 *                 @arg FMC_STATUS_COMPLETE
 */
FMC_STATUS_T  FMC_ReadStatus(void)
{
    FMC_STATUS_T status = FMC_STATUS_COMPLETE;

    if(FMC->STS_B.BUSYF == BIT_SET)
    {
        status = FMC_STATUS_BUSY;
    }
    else if(FMC->STS_B.PEF == BIT_SET)
    {
        status = FMC_STATUS_ERROR_PG;
    }
    else if(FMC->STS_B.WPEF == BIT_SET)
    {
        status = FMC_STATUS_ERROR_WRP;
    }
    else
    {
        status = FMC_STATUS_COMPLETE;
    }
    return status;
}

/*!
 * @brief     Waits for a Flash operation to complete or a TIMEOUT to occur.
 *
 * @param     timeOut:FMC programming timeout value.
 *
 * @retval    Returns the flash state.It can be one of value:
 *                 @arg FMC_STATUS_ERROR_PG
 *                 @arg FMC_STATUS_ERROR_WRP
 *                 @arg FMC_STATUS_COMPLETE
 *                 @arg FMC_STATUS_TIMEOUT
 */
FMC_STATUS_T FMC_WaitForLastOperation(uint32_t timeOut)
{
    FMC_STATUS_T status = FMC_STATUS_COMPLETE;

    /** Check for the Flash Status */
    status = FMC_ReadStatus();

    /** Wait for a Flash operation to complete or a TIMEOUT to occur */
    while((status == FMC_STATUS_BUSY) && (timeOut !=0))
    {
        status = FMC_ReadStatus();
        timeOut--;
    }
    if(timeOut == 0x00)
    {
        status = FMC_STATUS_TIMEOUT;
    }
    return status;
}

/**@} end of group FMC_Functions */
/**@} end of group FMC_Driver */
/**@} end of group APM32E10x_StdPeriphDriver */
