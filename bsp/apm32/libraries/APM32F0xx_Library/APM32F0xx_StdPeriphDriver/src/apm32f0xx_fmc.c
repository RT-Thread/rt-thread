/*!
 * @file        apm32f0xx_fmc.c
 *
 * @brief       This file provides all the FMC firmware functions
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

#include "apm32f0xx_fmc.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup FMC_Driver
  @{
*/

/** @defgroup FMC_Macros Macros
  @{
  */

/**@} end of group FMC_Macros */

/** @defgroup FMC_Enumerates Enumerates
  @{
  */

/**@} end of group FMC_Enumerates */

/** @defgroup FMC_Structures Structures
  @{
  */

/**@} end of group FMC_Structures */

/** @defgroup FMC_Variables Variables
  @{
  */

/**@} end of group FMC_Variables */

/** @defgroup FMC_Functions Functions
  @{
  */

/*!
 * @brief     Sets the code latency value.
 *
 * @param     latency: the flash latency value.
 *                     The parameter can be one of following values:
 *                       @arg FMC_LATENCY_0
 *                       @arg FMC_LATENCY_1
 * @retval    None
 */
void FMC_SetLatency(FMC_LATENCY_T latency)
{
    FMC->CTRL1_B.WS = latency;
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
 * @brief       Checks whether the flash Prefetch Buffer status is set or not
 *
 * @param       None
 *
 * @retval      flash Prefetch Buffer Status (SET or RESET)
 */
uint8_t FMC_ReadPrefetchBufferStatus(void)
{
    if (FMC->CTRL1_B.PBSF)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Unlocks the flash Program Erase Controller
 *
 * @param       None
 *
 * @retval      None
 */
void FMC_Unlock(void)
{
    FMC->KEY = FMC_KEY_1;
    FMC->KEY = FMC_KEY_2;
}

/*!
 * @brief       Locks the flash Program Erase Controller
 *
 * @param       None
 *
 * @retval      None
 */
void FMC_Lock(void)
{
    FMC->CTRL2_B.LOCK = BIT_SET;
}

/*!
 * @brief       Read flash state
 *
 * @param       None
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_BUSY
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 */
FMC_STATE_T FMC_ReadState(void)
{
    uint32_t status;
    FMC_STATE_T state = FMC_STATE_COMPLETE;

    status = FMC->STS;

    if (status & FMC_FLAG_PE)
    {
        state = FMC_STATE_PG_ERR;
    }
    else if (status & FMC_FLAG_WPE)
    {
        state = FMC_STATE_WRP_ERR;
    }
    else if (status & FMC_FLAG_BUSY)
    {
        state = FMC_STATE_BUSY;
    }

    return state;
}

/*!
 * @brief       Wait for flash controler ready
 *
 * @param       timeOut:    Specifies the time to wait
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_BUSY
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 *                 @arg FMC_STATE_TIMEOUT
 */
FMC_STATE_T FMC_WaitForReady(uint32_t timeOut)
{
    FMC_STATE_T state;

    do
    {
        state = FMC_ReadState();
        timeOut--;
    }
    while ((state == FMC_STATE_BUSY) && (timeOut));

    if (!timeOut)
    {
        state = FMC_STATE_TIMEOUT;
    }

    return state;
}

/*!
 * @brief       Erases a specified flash page
 *
 * @param       pageAddr:   Specifies the page address
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 *                 @arg FMC_STATE_TIMEOUT
 */
FMC_STATE_T FMC_ErasePage(uint32_t pageAddr)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.PAGEERA = BIT_SET;

        FMC->ADDR = pageAddr;

        FMC->CTRL2_B.STA = BIT_SET;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        FMC->CTRL2_B.PAGEERA = BIT_RESET;
    }

    return state;
}

/*!
 * @brief       Erases all flash pages
 *
 * @param       None
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 *                 @arg FMC_STATE_TIMEOUT
 * @note
 */
FMC_STATE_T FMC_EraseAllPages(void)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.MASSERA = BIT_SET;
        FMC->CTRL2_B.STA = BIT_SET;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        FMC->CTRL2_B.MASSERA = BIT_RESET;
    }

    return state;
}

/*!
 * @brief       Program a word at a specified address
 *
 * @param       addr:   Specifies the address to be programmed
 *
 * @param       data:   Specifies the data to be programmed
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 *                 @arg FMC_STATE_TIMEOUT
 */
FMC_STATE_T FMC_ProgramWord(uint32_t addr, uint32_t data)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.PG = BIT_SET;

        *(__IO uint16_t*)addr = (uint16_t)data;

        state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

        if (state == FMC_STATE_COMPLETE)
        {
            *(__IO uint16_t*)(addr + 2) = (uint16_t)(data >> 16);

            state = FMC_WaitForReady(FMC_DELAY_PROGRAM);
        }

        FMC->CTRL2_B.PG = BIT_RESET;
    }

    return state;
}

/*!
 * @brief       Programs a half word at a specified address
 *
 * @param       addr:   Specifies the address to be programmed
 *
 * @param       data:   Specifies the data to be programmed
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 *                 @arg FMC_STATE_TIMEOUT
 */
FMC_STATE_T FMC_ProgramHalfWord(uint32_t addr, uint16_t data)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.PG = BIT_SET;

        *(__IO uint16_t*)addr = data;

        state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

        FMC->CTRL2_B.PG = BIT_RESET;
    }

    return state;
}

/*!
 * @brief       Unlocks the option bytes block access
 *
 * @param       None
 *
 * @retval      None
 */
void FMC_UnlockOptionByte(void)
{
    FMC->OBKEY = FMC_OB_KEY_1;
    FMC->OBKEY = FMC_OB_KEY_2;
}

/*!
 * @brief       Locks the option bytes block access
 *
 * @param       None
 *
 * @retval      None
 */
void FMC_LockOptionByte(void)
{
    FMC->CTRL2_B.OBWEN = BIT_RESET;
}

/*!
 * @brief       Launch the option byte loading
 *
 * @param       None
 *
 * @retval      None
 */
void FMC_LaunchOptionByte(void)
{
    FMC->CTRL2_B.OBLOAD = BIT_SET;
}

/*!
 * @brief       Erase the flash option bytes
 *
 * @param       None
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 *                 @arg FMC_STATE_TIMEOUT
 */
FMC_STATE_T FMC_EraseOptionByte(void)
{
    uint16_t rpKey;
    FMC_STATE_T state;

    rpKey = FMC->OBCS_B.READPROT ? 0 : FMC_RP_KEY;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->OBKEY = FMC_KEY_1;
        FMC->OBKEY = FMC_KEY_2;

        FMC->CTRL2_B.OBE = BIT_SET;
        FMC->CTRL2_B.STA = BIT_SET;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        if (state == FMC_STATE_COMPLETE)
        {
            FMC->CTRL2_B.OBE = BIT_RESET;

            FMC->CTRL2_B.OBP = BIT_SET;

            OB->READPROT = rpKey;

            state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

            if (state != FMC_STATE_TIMEOUT)
            {
                FMC->CTRL2_B.OBP = BIT_RESET;
            }
        }
        else if (state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBE = BIT_RESET;
        }
    }

    return state;
}

/*!
 * @brief       Enable the specified page write protection
 *
 * @param       page:   Specifies the address of the pages to be write protected
 *                      This parameter can be any combination of the flowing values:
 *                      @arg FMC_WRP_PAGE_0_1 ... FMC_WRP_PAGE_60_61
 *                      @arg FMC_WRP_PAGE_ALL
 *
 * @retval      Returns the flash state.It can be one of value:
 *                      @arg FMC_STATE_COMPLETE
 *                      @arg FMC_STATE_PG_ERR
 *                      @arg FMC_STATE_WRP_ERR
 *                      @arg FMC_STATE_TIMEOU
 */
FMC_STATE_T FMC_EnableWriteProtection(uint32_t page)
{
    uint8_t i;
    uint16_t temp;
    __IO uint16_t* WRPT;
    FMC_STATE_T state;

    WRPT = &OB->WRTPROT0;

    state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->OBKEY = FMC_KEY_1;
        FMC->OBKEY = FMC_KEY_2;

        FMC->CTRL2_B.OBP = BIT_SET;

        for (i = 0; i < 4; i++)
        {
            temp = (uint16_t)~(page & 0xff);

            if ((temp != 0xff) && (state == FMC_STATE_COMPLETE))
            {
                WRPT[i] = temp;

                state = FMC_WaitForReady(FMC_DELAY_PROGRAM);
            }

            page >>= 8;
        }

        if (state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;
}

/*!
 * @brief       Read out protection configuration.
 *
 * @param       rdp:   specifies the read protection level
 *                     This parameter can be any combination of the flowing values:
 *                     @arg FMC_RDP_LEVEL_0
 *                     @arg FMC_RDP_LEVEL_1
 *
 * @retval      Returns the flash state.It can be one of value:
 *                     @arg FMC_STATE_COMPLETE
 *                     @arg FMC_STATE_PG_ERR
 *                     @arg FMC_STATE_WRP_ERR
 *                     @arg FMC_STATE_TIMEOU
 */
FMC_STATE_T FMC_ConfigReadOutProtection(FMC_RDP_T rdp)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->OBKEY = FMC_KEY_1;
        FMC->OBKEY = FMC_KEY_2;

        FMC->CTRL2_B.OBE = BIT_SET;
        FMC->CTRL2_B.STA = BIT_SET;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        if (state == FMC_STATE_COMPLETE)
        {
            FMC->CTRL2_B.OBE = BIT_RESET;

            FMC->CTRL2_B.OBP = BIT_SET;

            OB->READPROT = rdp;

            state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

            if (state != FMC_STATE_TIMEOUT)
            {
                FMC->CTRL2_B.OBP = BIT_RESET;
            }
        }
        else if (state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBE = BIT_SET;
        }
    }

    return state;
}

/*!
 * @brief       User option byte configuration
 *
 * @param       userConfig: Pointer to a FMC_UserConfig_T structure that
 *                          contains the configuration information for User option byte
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 *                 @arg FMC_STATE_TIMEOU
 */
FMC_STATE_T FMC_ConfigOptionByteUser(FMC_UserConfig_T* userConfig)
{
    FMC_STATE_T state;
    uint16_t temp;

    state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->OBKEY = FMC_OB_KEY_1;
        FMC->OBKEY = FMC_OB_KEY_2;

        FMC->CTRL2_B.OBP = BIT_SET;

        temp = (uint32_t)userConfig->iwdtSw | \
               (uint32_t)userConfig->stopce | \
               (uint32_t)userConfig->stdbyce | 0xF8;

        OB->USER = temp;

        state = FMC_WaitForReady(FMC_DELAY_PROGRAM);

        if (state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;
}

/*!
 * @brief       Enable the BOOT1 option bit
 *
 * @param       None
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 *                 @arg FMC_STATE_TIMEOU
 */
FMC_STATE_T FMC_EnableOptionByteBOOT(void)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.OBP = BIT_SET;

        OB->USER_B.BOT1 = BIT_SET;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        if (state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;
}

/*!
 * @brief       Disable the BOOT1 option bit
 *
 * @param       None
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 *                 @arg FMC_STATE_TIMEOU
 */
FMC_STATE_T FMC_DisableOptionByteBOOT(void)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.OBP = BIT_SET;

        OB->USER_B.BOT1 = BIT_RESET;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        if (state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;

}

/*!
 * @brief       Enable the analogue monitoring on VDDA Power source
 *
 * @param       None
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 *                 @arg FMC_STATE_TIMEOU
 */
FMC_STATE_T FMC_EnableOptionByteVDDA(void)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.OBP = BIT_SET;

        OB->USER_B.VDDAMON = BIT_SET;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        if (state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;

}

/*!
 * @brief       Disable the analogue monitoring on VDDA Power source
 *
 * @param       None
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 *                 @arg FMC_STATE_TIMEOU
 */
FMC_STATE_T FMC_DisableOptionByteVDDA(void)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.OBP = BIT_SET;

        OB->USER_B.VDDAMON = BIT_RESET;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        if (state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;

}

/*!
 * @brief       Enable the SRAM parity
 *
 * @param       None
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 *                 @arg FMC_STATE_TIMEOU
 */
FMC_STATE_T FMC_EnableOptionByteSRAMParity(void)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.OBP = BIT_SET;

        OB->USER_B.RPC = BIT_SET;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        if (state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;

}

/*!
 * @brief    Disable the SRAM parity
 *
 * @param    None
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 *                 @arg FMC_STATE_TIMEOU
 */
FMC_STATE_T FMC_DisableOptionByteSRAMParity(void)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.OBP = BIT_SET;

        OB->USER_B.RPC = BIT_RESET;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        if (state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;

}
/*!
 * @brief     Programs the FMC User Option Byte: WDT, STOP, STDBY,
 *            BOOT1 and VDDA ANALOG monitoring
 *
 * @param     ob_user: Selects all user option bytes
 *                     This parameter is a combination of the following values:
 *                     @arg FMC_OB_IWDT_HW / FMC_OB_IWDT_SW
 *                     @arg FMC_OB_STOP_RESET / FMC_OB_STOP_NRST
 *                     @arg FMC_OB_STDBY_RESET / FMC_OB_STDBY_NRST
 *                     @arg FMC_OB_BOOT0_RESET / FMC_OB_BOOT0_SET
 *                     @arg FMC_OB_BOOT1_RESET / FMC_OB_BOOT1_SET
 *                     @arg FMC_OB_VDDA_ANALOG_OFF / FMC_OB_VDDA_ANALOG_ON
 *                     @arg FMC_OB_SRAM_PARITY_SET / FMC_OB_SRAM_PARITY_RESET
 *                     @arg FMC_OB_BOOT0_SW / FMC_OB_BOOT0_HW
 *
 * @retval      Returns the flash state.It can be one of value:
 *                     @arg FMC_STATE_COMPLETE
 *                     @arg FMC_STATE_PG_ERR
 *                     @arg FMC_STATE_WRP_ERR
 *                     @arg FMC_STATE_TIMEOU
 */
FMC_STATE_T FMC_WriteOptionByteUser(uint8_t ob_user)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.OBP = BIT_SET;

        OB->USER = ob_user;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        if (state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;

}

/*!
 * @brief       Programs a half word at a specified Option Byte Data address
 *
 * @param       addr: specifies the address to be programmed.
 *              This parameter can be 0x1FFFF804 or 0x1FFFF806.
 * @param       data: specifies the data to be programmed.
 *
 * @retval      Returns the flash state.It can be one of value:
 *                 @arg FMC_STATE_COMPLETE
 *                 @arg FMC_STATE_PG_ERR
 *                 @arg FMC_STATE_WRP_ERR
 *                 @arg FMC_STATE_TIMEOU
 */
FMC_STATE_T FMC_ProgramOptionByteData(uint32_t addr, uint8_t data)
{
    FMC_STATE_T state;

    state = FMC_WaitForReady(FMC_DELAY_ERASE);

    if (state == FMC_STATE_COMPLETE)
    {
        FMC->CTRL2_B.OBP = BIT_SET;

        *(__IO uint16_t*)addr = data;

        state = FMC_WaitForReady(FMC_DELAY_ERASE);

        if (state != FMC_STATE_TIMEOUT)
        {
            FMC->CTRL2_B.OBP = BIT_RESET;
        }
    }

    return state;

}

/*!
 * @brief       Returns the Flash User Option Bytes values
 *
 * @param       None
 *
 * @retval      The flash User Option Bytes
 */
uint8_t FMC_ReadOptionByteUser(void)
{
    return (uint8_t)(FMC->OBCS >> 8);
}

/*!
 * @brief       Returns the flash Write Protection Option Bytes value:
 *
 * @param       None
 *
 * @retval      The Flash Write Protection Option Bytes value:
 */
uint32_t FMC_ReadOptionByteWriteProtection(void)
{
    return (uint32_t)(FMC->WRTPROT);
}

/*!
 * @brief       Checks whether the Flash Read Protection Status is set or not
 *
 * @param       None
 *
 * @retval      Flash ReadOut Protection Status(SET or RESET)
 */
uint8_t FMC_GetReadProtectionStatus(void)
{
    if (FMC->OBCS_B.READPROT)
    {
        return SET;
    }

    return RESET;
}
/*!
 * @brief       Enable the specified flash interrupts
 *
 * @param       interrupt:  Specifies the flash interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg FMC_INT_ERROR:       Error interruption
 *                          @arg FMC_INT_COMPLETE:    operation complete interruption
 *
 * @retval      None
 */
void FMC_EnableInterrupt(uint32_t interrupt)
{
    FMC->CTRL2 |= interrupt;
}

/*!
 * @brief       Disable the specified flash interrupts
 *
 * @param       interrupt:  Specifies the flash interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg FMC_INT_ERROR:       Error interruption
 *                          @arg FMC_INT_COMPLETE:    operation complete interruption
 *
 * @retval      None
 */
void FMC_DisableInterrupt(uint32_t interrupt)
{
    FMC->CTRL2 &= ~interrupt;
}

/*!
 * @brief       Checks whether the specified flash flag is set or not
 *

 * @param       flag:   Specifies the flash flag to check
 *                      The parameter can be one of following values:
 *                      @arg FMC_FLAG_BUSY: Busy flag
 *                      @arg FMC_FLAG_PE:   Program error flag
 *                      @arg FMC_FLAG_WPE:  Write protection flag
 *                      @arg FMC_FLAG_OC:   Operation complete flag
 *
 * @retval      None
 */
uint8_t FMC_ReadStatusFlag(FMC_FLAG_T flag)
{
    uint8_t status;

    if (flag & 0xff)
    {
        status = FMC->STS & flag;
    }
    else
    {
        status = FMC->OBCS & flag;
    }

    if (status)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear the specified flash flag
 *
 * @param       flag:   Specifies the flash flag to clear
 *                      This parameter can be any combination of the following values:
 *                      @arg FMC_FLAG_BUSY:   Busy flag
 *                      @arg FMC_FLAG_PE:     Program error flag
 *                      @arg FMC_FLAG_WPE:    Write protection error flag
 *                      @arg FMC_FLAG_OC:     Operation complete flag
 *
 * @retval      None
 */
void FMC_ClearStatusFlag(uint8_t flag)
{
    if (flag & 0xff)
    {
        FMC->STS = flag;
    }
}

/**@} end of group FMC_Functions*/
/**@} end of group FMC_Driver*/
/**@} end of group APM32F0xx_StdPeriphDriver*/
