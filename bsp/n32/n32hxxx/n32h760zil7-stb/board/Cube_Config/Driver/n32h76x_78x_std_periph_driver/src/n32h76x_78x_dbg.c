/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_dbg.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */

#include "n32h76x_78x_dbg.h"


/**
*\*\name    DBG_GetRevNum.
*\*\fun     get the revision number.
*\*\param   none
*\*\return  revision number
**/
uint32_t DBG_GetRevNum(void)
{
    return (uint32_t)((DBG->ID & DBG_REV_NUM_MASK) >> 24);
}

/**
*\*\name    DBG_GetDevNum.
*\*\fun     get the device identifer.
*\*\param   none
*\*\return  Device identifier
*\*\        - 0x760     : N32H760 Series
*\*\        - 0x762     : N32H762 Series
*\*\        - 0x765     : N32H765 Series
*\*\        - 0x785     : N32H785 Series
*\*\        - 0x787     : N32H787 Series
*\*\        - 0x788     : N32H788 Series
**/
uint32_t DBG_GetDevNum(void)
{
    return (uint32_t)((DBG->ID & DBG_DEV_NUM_MASK) >> 12);
}


/**
*\*\name    DBG_SetExternalTriggerPinDirection.
*\*\fun     Set the direction of the bi-directional trigger pin TRGIO.
*\*\param   PinDirection :
              - DBG_TRGIO_INPUT_DIRECTION
              - DBG_TRGIO_OUTPUT_DIRECTION
*\*\return  none
**/
void DBG_SetExternalTriggerPinDirection(uint32_t PinDirection)
{
    if(PinDirection == DBG_TRGIO_OUTPUT_DIRECTION)
    {
        DBG->CTRL |= DBG_TRGIO_OUTPUT_DIRECTION;
    }
    else
    {
        DBG->CTRL &= (~DBG_TRGIO_OUTPUT_DIRECTION) ;
    }
}

/**
*\*\name    DBG_M7ConfigPeriph.
*\*\fun     Configures the specified peripheral run or stop when the M7 MCU under Debug mode.
*\*\param   DBG_Periph :
              - DBG_M7SLEEP               * Keep debugger connection during M7 SLEEP mode *
              - DBG_M7STOP                * Keep debugger connection during M7 STOP mode *
              - DBG_M7STANDBY             * Keep debugger connection during M7 STANDBY mode *
              - DBG_WWDG1_STOP            * WWDG1 stopped when Core is halted. *
              - DBG_WWDG2_STOP            * WWDG2 stopped when Core is halted. *
              - DBG_ATIM3_STOP            * ATIM3 counter stopped when core is halted *
              - DBG_ATIM4_STOP            * ATIM4 counter stopped when core is halted *
              - DBG_I2C7SMBUS_TIMEOUT     * I2C7 counter stopped when core is halted *
              - DBG_I2C8SMBUS_TIMEOUT     * I2C8 counter stopped when core is halted *
              - DBG_I2C9SMBUS_TIMEOUT     * I2C9 counter stopped when core is halted *
              - DBG_I2C10SMBUS_TIMEOUT    * I2C10 counter stopped when core is halted *
              - DBG_IWDG1_STOP            * IWDG1 counter stopped when core is halted *
              - DBG_IWDG2_STOP            * IWDG2 counter stopped when core is halted *
              - DBG_LPTIM1_STOP           * LPTIM1 counter stopped when core is halted *
              - DBG_LPTIM2_STOP           * LPTIM2 counter stopped when core is halted *
              - DBG_LPTIM3_STOP           * LPTIM3 counter stopped when core is halted *
              - DBG_LPTIM4_STOP           * LPTIM4 counter stopped when core is halted *
              - DBG_LPTIM5_STOP           * LPTIM5 counter stopped when core is halted *
              - DBG_RTC_STOP              * RTC counter stopped when core is halted *
              - DBG_CANFD3_STOP           * CANFD3 counter stopped when core is halted *
              - DBG_CANFD4_STOP           * CANFD4 counter stopped when core is halted *
              - DBG_CANFD7_STOP           * CANFD7 counter stopped when core is halted *
              - DBG_CANFD8_STOP           * CANFD8 counter stopped when core is halted *
              - DBG_I2C4SMBUS_TIMEOUT     * I2C4 counter stopped when core is halted *
              - DBG_I2C5SMBUS_TIMEOUT     * I2C5 counter stopped when core is halted *
              - DBG_I2C6SMBUS_TIMEOUT     * I2C6 counter stopped when core is halted *
              - DBG_ATIM1_STOP            * ATIM1 counter stopped when core is halted *
              - DBG_ATIM2_STOP            * ATIM2 counter stopped when core is halted *
              - DBG_GTIMA1_STOP           * GTIMA1 counter stopped when core is halted *
              - DBG_GTIMA2_STOP           * GTIMA2 counter stopped when core is halted *
              - DBG_GTIMA3_STOP           * GTIMA3 counter stopped when core is halted *
              - DBG_SHRTIM1_STOP          * SHRTIM1 counter stopped when core is halted *
              - DBG_SHRTIM2_STOP          * SHRTIM2 counter stopped when core is halted *
              - DBG_BTIM1_STOP            * BTIM1 counter stopped when core is halted *
              - DBG_BTIM2_STOP            * BTIM2 counter stopped when core is halted *
              - DBG_BTIM3_STOP            * BTIM3 counter stopped when core is halted *
              - DBG_BTIM4_STOP            * BTIM4 counter stopped when core is halted *
              - DBG_GTIMA4_STOP           * GTIMA4 counter stopped when core is halted *
              - DBG_GTIMA5_STOP           * GTIMA5 counter stopped when core is halted *
              - DBG_GTIMA6_STOP           * GTIMA6 counter stopped when core is halted *
              - DBG_GTIMA7_STOP           * GTIMA7 counter stopped when core is halted *
              - DBG_GTIMB1_STOP           * GTIMB1 counter stopped when core is halted *
              - DBG_GTIMB2_STOP           * GTIMB2 counter stopped when core is halted *
              - DBG_GTIMB3_STOP           * GTIMB3 counter stopped when core is halted *
              - DBG_I2C1SMBUS_TIMEOUT     * I2C1 counter stopped when core is halted *
              - DBG_I2C2SMBUS_TIMEOUT     * I2C2 counter stopped when core is halted *
              - DBG_I2C3SMBUS_TIMEOUT     * I2C3 counter stopped when core is halted *
              - DBG_CANFD1_STOP           * CANFD1 counter stopped when core is halted *
              - DBG_CANFD2_STOP           * CANFD2 counter stopped when core is halted *
              - DBG_CANFD5_STOP           * CANFD5 counter stopped when core is halted *
              - DBG_CANFD6_STOP           * CANFD6 counter stopped when core is halted *
*\*\return  none
**/
void DBG_M7ConfigPeriph(uint32_t DBG_Periph, FunctionalState Cmd)
{
    uint32_t Offset = ( (DBG_Periph & REGISTER_OFFSET_MASK) >> REGISTER_OFFSET_POS);
    __IO uint32_t  Register_Base = DBGMCU_BASE;

    Register_Base += Offset;

    if (Cmd != DISABLE)
    {
        *(uint32_t *)Register_Base |= DBG_Periph;
    }
    else
    {
        *(uint32_t *)Register_Base &= ~DBG_Periph;
    }
}

/**
*\*\name    DBG_M4ConfigPeriph.
*\*\fun     Configures the specified peripheral run or stop when the M4 MCU under Debug mode.
*\*\param   DBG_Periph :
              - DBG_M4SLEEP               * Keep debugger connection during M4 SLEEP mode *
              - DBG_M4STOP                * Keep debugger connection during M4 STOP mode *
              - DBG_M4STANDBY             * Keep debugger connection during M4 STANDBY mode *
              - DBG_WWDG1_STOP            * WWDG1 stopped when Core is halted. *
              - DBG_WWDG2_STOP            * WWDG2 stopped when Core is halted. *
              - DBG_ATIM3_STOP            * ATIM3 counter stopped when core is halted *
              - DBG_ATIM4_STOP            * ATIM4 counter stopped when core is halted *
              - DBG_I2C7SMBUS_TIMEOUT     * I2C7 counter stopped when core is halted *
              - DBG_I2C8SMBUS_TIMEOUT     * I2C8 counter stopped when core is halted *
              - DBG_I2C9SMBUS_TIMEOUT     * I2C9 counter stopped when core is halted *
              - DBG_I2C10SMBUS_TIMEOUT    * I2C10 counter stopped when core is halted *
              - DBG_IWDG1_STOP            * IWDG1 counter stopped when core is halted *
              - DBG_IWDG2_STOP            * IWDG2 counter stopped when core is halted *
              - DBG_LPTIM1_STOP           * LPTIM1 counter stopped when core is halted *
              - DBG_LPTIM2_STOP           * LPTIM2 counter stopped when core is halted *
              - DBG_LPTIM3_STOP           * LPTIM3 counter stopped when core is halted *
              - DBG_LPTIM4_STOP           * LPTIM4 counter stopped when core is halted *
              - DBG_LPTIM5_STOP           * LPTIM5 counter stopped when core is halted *
              - DBG_RTC_STOP              * RTC counter stopped when core is halted *
              - DBG_CANFD3_STOP           * CANFD3 counter stopped when core is halted *
              - DBG_CANFD4_STOP           * CANFD4 counter stopped when core is halted *
              - DBG_CANFD7_STOP           * CANFD7 counter stopped when core is halted *
              - DBG_CANFD8_STOP           * CANFD8 counter stopped when core is halted *
              - DBG_I2C4SMBUS_TIMEOUT     * I2C4 counter stopped when core is halted *
              - DBG_I2C5SMBUS_TIMEOUT     * I2C5 counter stopped when core is halted *
              - DBG_I2C6SMBUS_TIMEOUT     * I2C6 counter stopped when core is halted *
              - DBG_ATIM1_STOP            * ATIM1 counter stopped when core is halted *
              - DBG_ATIM2_STOP            * ATIM2 counter stopped when core is halted *
              - DBG_GTIMA1_STOP           * GTIMA1 counter stopped when core is halted *
              - DBG_GTIMA2_STOP           * GTIMA2 counter stopped when core is halted *
              - DBG_GTIMA3_STOP           * GTIMA3 counter stopped when core is halted *
              - DBG_SHRTIM1_STOP          * SHRTIM1 counter stopped when core is halted *
              - DBG_SHRTIM2_STOP          * SHRTIM2 counter stopped when core is halted *
              - DBG_BTIM1_STOP            * BTIM1 counter stopped when core is halted *
              - DBG_BTIM2_STOP            * BTIM2 counter stopped when core is halted *
              - DBG_BTIM3_STOP            * BTIM3 counter stopped when core is halted *
              - DBG_BTIM4_STOP            * BTIM4 counter stopped when core is halted *
              - DBG_GTIMA4_STOP           * GTIMA4 counter stopped when core is halted *
              - DBG_GTIMA5_STOP           * GTIMA5 counter stopped when core is halted *
              - DBG_GTIMA6_STOP           * GTIMA6 counter stopped when core is halted *
              - DBG_GTIMA7_STOP           * GTIMA7 counter stopped when core is halted *
              - DBG_GTIMB1_STOP           * GTIMB1 counter stopped when core is halted *
              - DBG_GTIMB2_STOP           * GTIMB2 counter stopped when core is halted *
              - DBG_GTIMB3_STOP           * GTIMB3 counter stopped when core is halted *
              - DBG_I2C1SMBUS_TIMEOUT     * I2C1 counter stopped when core is halted *
              - DBG_I2C2SMBUS_TIMEOUT     * I2C2 counter stopped when core is halted *
              - DBG_I2C3SMBUS_TIMEOUT     * I2C3 counter stopped when core is halted *
              - DBG_CANFD1_STOP           * CANFD1 counter stopped when core is halted *
              - DBG_CANFD2_STOP           * CANFD2 counter stopped when core is halted *
              - DBG_CANFD5_STOP           * CANFD5 counter stopped when core is halted *
              - DBG_CANFD6_STOP           * CANFD6 counter stopped when core is halted *
*\*\return  none
**/
void DBG_M4ConfigPeriph(uint32_t DBG_Periph, FunctionalState Cmd)
{
    uint32_t Offset = ( (DBG_Periph & REGISTER_OFFSET_MASK) >> REGISTER_OFFSET_POS);
    __IO uint32_t  Register_Base = DBGMCU_BASE;

    Register_Base += (Offset + 0x04u);

    if (Cmd != DISABLE)
    {
        *(uint32_t *)Register_Base |= DBG_Periph;
    }
    else
    {
        *(uint32_t *)Register_Base &= ~DBG_Periph;
    }
}
/**
*\*\name    DBG_GetFlashSize.
*\*\fun     Get FLASH size of this chip.
*\*\param   none
*\*\return  FLASH size in bytes.
**/
uint32_t DBG_GetFlashSize(void)
{
    uint32_t Flash_size = (DBG->ID & DBG_FLASH_SIZE_MASK);

    if(Flash_size != DBG_FLASH_SIZE_MASK)
    {
        Flash_size = (uint32_t)(Flash_size << 15);
    }
    else
    {
        Flash_size = 0;
    }

    return Flash_size;
}

