/**************************************************************************//**
 * @file     fmc.c
 * @version  V3.00
 * $Revision: 11 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series FMC driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

//* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "M051Series.h"

/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_FMC_Driver FMC Driver
  @{
*/


/** @addtogroup M051_FMC_EXPORTED_FUNCTIONS FMC Exported Functions
  @{
*/


/**
  * @brief    Set boot source from LDROM or APROM after next software reset.
  *
  * @param    i32BootSrc[in]
  *                             1: Boot from LDROM
  *                             0: Boot from APROM
  *
  * @details  This function is used to switch APROM boot or LDROM boot. User need to call
  *           FMC_SetBootSource to select boot source first, then use CPU reset or
  *           System Reset Request to reset system.
  *
  */
void FMC_SetBootSource(int32_t i32BootSrc)
{
    if(i32BootSrc)
        FMC->ISPCON |= FMC_ISPCON_BS_Msk; /* Boot from LDROM */
    else
        FMC->ISPCON &= ~FMC_ISPCON_BS_Msk;/* Boot from APROM */
}


/**
  * @brief    Disable ISP Functions
  */
void FMC_Close(void)
{
    FMC->ISPCON &= ~FMC_ISPCON_ISPEN_Msk;
}


/**
  * @brief    Disable APROM update function
  *
  * @details  Disable APROM update function will forbid APROM programming when boot form APROM.
  *           APROM update is default to be disable.
  *
  */
void FMC_DisableAPUpdate(void)
{
    FMC->ISPCON &= ~FMC_ISPCON_APUEN_Msk;
}


/**
  * @brief    Disable User Configuration update function
  *
  * @details  Disable User Configuration update function will forbid User Configuration programming.
  *           User Configuration update is default to be disable.
  */
void FMC_DisableConfigUpdate(void)
{
    FMC->ISPCON &= ~FMC_ISPCON_CFGUEN_Msk;
}


/**
  * @brief    Disable LDROM update function
  *
  * @details  Disable LDROM update function will forbid LDROM programming.
  *           LDROM update is default to be disable.
  */
void FMC_DisableLDUpdate(void)
{
    FMC->ISPCON &= ~FMC_ISPCON_LDUEN_Msk;
}


/**
  * @brief    Enable APROM update function
  *
  * @details  Enable APROM to be able to program when boot from APROM.
  *
  */
void FMC_EnableAPUpdate(void)
{
    FMC->ISPCON |= FMC_ISPCON_APUEN_Msk;
}


/**
  * @brief    Enable User Configuration update function
  *
  * @details  Enable User Configuration to be able to program.
  *
  */
void FMC_EnableConfigUpdate(void)
{
    FMC->ISPCON |= FMC_ISPCON_CFGUEN_Msk;
}


/**
  * @brief    Enable LDROM update function
  *
  * @details  Enable LDROM to be able to program.
  *
  */
void FMC_EnableLDUpdate(void)
{
    FMC->ISPCON |= FMC_ISPCON_LDUEN_Msk;
}


/**
  * @brief    Get the current boot source
  *
  * @retval   0: This chip is currently booting from APROM
  * @retval   1: This chip is currently booting from LDROM
  *
  * @note     This function only show the boot source.
  *           User need to read ISPSTA register to know if IAP mode supported or not in relative boot.
  */
int32_t FMC_GetBootSource(void)
{
    if(FMC->ISPCON & FMC_ISPCON_BS_Msk)
        return 1;
    else
        return 0;
}


/**
  * @brief    Enable FMC ISP function
  *
  * @details  ISPEN bit of ISPCON must be set before we can use ISP commands.
  *
  */
void FMC_Open(void)
{
    FMC->ISPCON |=  FMC_ISPCON_ISPEN_Msk;
}

/**
  * @brief    Get the base address of Data Flash if enabled.
  * @retval   The base address of Data Flash
  */
uint32_t FMC_ReadDataFlashBaseAddr(void)
{
    return FMC->DFBADR;
}


/**
  * @brief       Read the User Configuration words.
  * @param[out]  u32Config  The word buffer to store the User Configuration data.
  * @param[in]   u32Count   The word count to be read.
  * @retval       0: Success
  * @retval      -1: Failed
  */
int32_t FMC_ReadConfig(uint32_t *u32Config, uint32_t u32Count)
{
    int32_t i;

    for(i = 0; i < u32Count; i++)
        u32Config[i] = FMC_Read(FMC_CONFIG_BASE + i * 4);

    return 0;
}


/**
  * @brief    Write User Configuration
  *
  * @param    u32Config: The word buffer to store the User Configuration data.
  * @param    u32Count:  The word count to program to User Configuration.
  *
  * @retval    0:  Success
  * @retval   -1: Failed
  *
  * @details  User must enable User Configuration update before writing it.
  *           User must erase User Configuration before writing it.
  *           User Configuration is also be page erase. User needs to backup necessary data
  *           before erase User Configuration.
  */
int32_t FMC_WriteConfig(uint32_t *u32Config, uint32_t u32Count)
{
    int32_t i;

    for(i = 0; i < u32Count; i++)
    {
        FMC_Write(FMC_CONFIG_BASE + i * 4, u32Config[i]);
        if(FMC_Read(FMC_CONFIG_BASE + i * 4) != u32Config[i])
            return -1;
    }

    return 0;
}


/*@}*/ /* end of group M051_FMC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_FMC_Driver */

/*@}*/ /* end of group M051_Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/


