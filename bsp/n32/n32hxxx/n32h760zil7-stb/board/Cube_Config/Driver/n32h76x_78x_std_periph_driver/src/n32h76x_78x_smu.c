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
 * @file n32h76x_78x_smu.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_smu.h"

/* SMU Driving Functions Declaration */

/* SMU_Private_Defines  */

/**
*\*\name    SMU_GetM4BootAddr.
*\*\fun     Read boot address of CM4
*\*\param   none
*\*\return  CM4 boot address
**/
uint32_t SMU_GetM4BootAddr( void )
{
    return (*(uint32_t (*)(void))GET_M4ADDR)();
}

/**
*\*\name    SMU_SetM4BootAddr.
*\*\fun     Setting boot address of CM4
*\*\param   CM4 boot address
*\*\return  Status flag
*\*\		   -SMU_SUCCESS
*\*\		   -SMU_ERR
**/
uint32_t SMU_SetM4BootAddr( uint32_t addr )
{
    return (*(uint32_t (*)(uint32_t))(SET_M4ADDR))( addr );
}

/**
*\*\name    SMU_GetM7BootAddr.
*\*\fun     Read boot address of CM7
*\*\param   none
*\*\return  CM7 boot address
**/
uint32_t SMU_GetM7BootAddr( void )
{
    return (*(uint32_t (*)(void))GET_M7ADDR)();
}

/**
*\*\name    SMU_SetM4BootAddr.
*\*\fun     Setting boot address of CM7
*\*\param   CM7 boot address
*\*\return  Status flag
*\*\		   -SMU_SUCCESS
*\*\		   -SMU_ERR
**/
uint32_t SMU_SetM7BootAddr( uint32_t addr )
{
    return (*(uint32_t (*)(uint32_t))(SET_M7ADDR))( addr );
}

/**
*\*\name    SMU_EraseFlash.
*\*\fun     Flash erase
*\*\param   Flash start address, erase the 4KB sector where the start address is located
*\*\return  Error flag
*\*\		   -FLASH_SUCCESS
*\*\		   -FLASH_FAILED
*\*\note    Erase in 4KB units
**/
uint32_t SMU_EraseFlash(uint32_t StrAddr)
{
    return (*(uint32_t (*)(uint32_t))(ER_FLASH))( StrAddr );
}

/**
*\*\name    SMU_WriteFlash.
*\*\fun     Write data to internal xSPI flash
*\*\param   Flash start address
*\*\param   The pointer of data buffer
*\*\param   Data lenght
*\*\return  Error flag
*\*\		   -FLASH_SUCCESS
*\*\		   -FLASH_FAILED
**/
uint32_t SMU_WriteFlash(uint32_t StrAddr, uint8_t *SrcBuf, uint32_t Len)
{
    return (*(uint32_t (*)(uint32_t, uint8_t*, uint32_t))(WR_FLASH))( StrAddr, SrcBuf, Len );
}
