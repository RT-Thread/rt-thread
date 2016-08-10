/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <assert.h>
#include <string.h>
#include "fsl_mpu_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_MPU_COUNT

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 *******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_DRV_Init
 * Description   : MPU module init.
 * This function is used to initialize MPU regions.
 *
 *END**************************************************************************/
mpu_status_t MPU_DRV_Init(uint32_t instance, const mpu_user_config_t *userConfigPtr)
{
    assert(instance < MPU_INSTANCE_COUNT);
    MPU_Type * base = g_mpuBase[instance];
    if(!userConfigPtr)
    {
        return kStatus_MPU_NullArgument;
    }
    CLOCK_SYS_EnableMpuClock(instance); 
    MPU_HAL_Init(base);
    while(userConfigPtr)
    {
        MPU_DRV_SetRegionConfig(instance, &(userConfigPtr->regionConfig));
        userConfigPtr = userConfigPtr->next;
    }
    MPU_HAL_Enable(base);
    return kStatus_MPU_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_DRV_Deinit
 * Description   : MPU module deinit.
 * This function is used to deinit MPU module---disable MPU and disable each region.
 *
 *END**************************************************************************/
void MPU_DRV_Deinit(uint32_t instance)
{
    assert(instance < MPU_INSTANCE_COUNT);
    MPU_Type * base = g_mpuBase[instance];
    MPU_HAL_Init(base);
    CLOCK_SYS_DisableMpuClock(instance);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_DRV_SetRegionConfig
 * Description   : MPU region init.
 * This function is used to initialize a MPU region.
 * Note: when writing to a region's word0~word3 will caused the region invalid
 * so the region must be set valid by manual.
 *END**************************************************************************/
mpu_status_t MPU_DRV_SetRegionConfig(uint32_t instance, const mpu_region_config_t *regionConfigPtr)
{
    assert(instance < MPU_INSTANCE_COUNT);
    MPU_Type * base = g_mpuBase[instance];
    
    MPU_HAL_SetRegionConfig(base, regionConfigPtr);
    
    return kStatus_MPU_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_DRV_SetLowMasterAccessRights
 * Description   : Set low master access permission.
 * This function is used to set low master access permission.
 *
 *END**************************************************************************/
mpu_status_t MPU_DRV_SetLowMasterAccessRights(uint32_t instance, mpu_region_num_t regionNum, mpu_master_t masterNum, const mpu_low_masters_access_rights_t *accessRightsPtr)
{
    assert(instance < MPU_INSTANCE_COUNT);
    MPU_Type * base = g_mpuBase[instance];
    if(!accessRightsPtr)
    {
	return kStatus_MPU_NullArgument;
    }
    MPU_HAL_SetLowMasterAccessRightsByAlternateReg(base, regionNum, masterNum, accessRightsPtr);
    
    return kStatus_MPU_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_DRV_SetHighMasterAccessRights
 * Description   : Set high master access permission.
 * This function is used to set high master access permission.
 *
 *END**************************************************************************/
mpu_status_t MPU_DRV_SetHighMasterAccessRights(uint32_t instance, mpu_region_num_t regionNum, mpu_master_t masterNum, const mpu_high_masters_access_rights_t *accessRightsPtr)
{
    assert(instance < MPU_INSTANCE_COUNT);
    MPU_Type * base = g_mpuBase[instance];
    if(!accessRightsPtr)
    {
	return kStatus_MPU_NullArgument;
    }
    MPU_HAL_SetHighMasterAccessRightsByAlternateReg(base, regionNum, masterNum, accessRightsPtr);
    
    return kStatus_MPU_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_DRV_SetRegionAddr
 * Description   : Set region start address.
 * This function is used to set region start address.
 *
 *END**************************************************************************/
void MPU_DRV_SetRegionAddr(uint32_t instance, mpu_region_num_t regionNum, uint32_t startAddr, uint32_t endAddr)
{
    assert(instance < MPU_INSTANCE_COUNT);
    MPU_Type * base = g_mpuBase[instance];
    MPU_HAL_SetRegionAddr(base, regionNum, startAddr, endAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_DRV_SetRegionValidCmd
 * Description   : set a region valid or invalid.
 * This function is used to set a region valid or invalid.
 *
 *END**************************************************************************/
void MPU_DRV_SetRegionValidCmd(uint32_t instance, mpu_region_num_t regionNum, bool enable)
{
    assert(instance < MPU_INSTANCE_COUNT);
    MPU_Type * base = g_mpuBase[instance];
    MPU_HAL_SetRegionValidCmd(base, regionNum, enable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_DRV_GetDetailErrorAccessInfo
 * Description   : Gets error access detail information.
 * Attention: It is possible for two masters access error in same cycle, so a array pointer is needed.
 *
 *END**************************************************************************/
mpu_status_t MPU_DRV_GetDetailErrorAccessInfo(uint32_t instance,  mpu_access_err_info_t *errInfoArrayPtr)
{
    assert(instance < MPU_INSTANCE_COUNT);
    MPU_Type * base = g_mpuBase[instance];    
    if(!errInfoArrayPtr)
    {
        return kStatus_MPU_NullArgument;
    }
    MPU_HAL_GetDetailErrorAccessInfo(base, errInfoArrayPtr);
    
    return kStatus_MPU_Success;
}
#endif

/*******************************************************************************
 * EOF
 *******************************************************************************/

