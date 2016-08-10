/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#include "fsl_mpu_hal.h"
#if FSL_FEATURE_SOC_MPU_COUNT

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*******************************************************************************
 * Variables
 *******************************************************************************/

/*******************************************************************************
 * Code
 *******************************************************************************/
#endif

/*******************************************************************************
 * EOF
 *******************************************************************************/
 
/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_HAL_GetHardwareInfo
 * Description   : Returns MPU Hardware information.
 *
 *END**************************************************************************/
void MPU_HAL_GetHardwareInfo(MPU_Type *base, mpu_hardware_info_t *infoPtr)
{
   uint32_t value;
   assert(infoPtr);
   value                              = MPU_RD_CESR(base);
   infoPtr->kMPUHardwareRevisionLevel = (value & MPU_CESR_HRL_MASK) >> MPU_CESR_HRL_SHIFT;
   infoPtr->kMPUSupportSlavePortsNum  = (value & MPU_CESR_NSP_MASK) >> MPU_CESR_NSP_SHIFT;
   infoPtr->kMPUSupportRegionsNum     = (mpu_region_total_num_t)((value & MPU_CESR_NRGD_MASK) >> MPU_CESR_NRGD_SHIFT);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_HAL_GetDetailErrorAccessInfo
 * Description   : Returns MPU error access detail information.
 * Attention : There is a possibility for more than one master to access different slaves at one CPU cycle,
 * so a array pointer is passed.
 *END**************************************************************************/
void MPU_HAL_GetDetailErrorAccessInfo(MPU_Type *base, mpu_access_err_info_t *errInfoArrayPtr)
{
    assert(errInfoArrayPtr);
    uint32_t value = MPU_BRD_CESR_SPERR(base);
    uint32_t value1;
    uint8_t i;
    uint8_t slavePort = 0x10;
    for(i = 0; i < FSL_FEATURE_MPU_SLAVEPORT; i++)
    {
       if(value & slavePort)
       {
          value1 = MPU_BRD_EDR_EACD(base, i);
          if(0 == value1)
          {
            errInfoArrayPtr[i].accessCtr = kMPUNoRegionHit;
          }
          else if(!(value1 & (value1-1)))
          {
            errInfoArrayPtr[i].accessCtr = kMPUNoneOverlappRegion;
          }
          else
          {
            errInfoArrayPtr[i].accessCtr = kMPUOverlappRegion;
          }
          value1 = MPU_RD_EDR(base, i);
          errInfoArrayPtr[i].master     = (mpu_master_t)((value1 & MPU_EDR_EMN_MASK) >> MPU_EDR_EMN_SHIFT);
          errInfoArrayPtr[i].attributes = (mpu_err_attributes_t)((value1 & MPU_EDR_EATTR_MASK) >> MPU_EDR_EATTR_SHIFT);
          errInfoArrayPtr[i].accessType = (mpu_err_access_type_t)((value1 & MPU_EDR_ERW_MASK) >> MPU_EDR_ERW_SHIFT);
          errInfoArrayPtr[i].addr       = MPU_RD_EAR(base, i);
          errInfoArrayPtr[i].slavePort  = i;
#if FSL_FEATURE_MPU_HAS_PROCESS_IDENTIFIER
          errInfoArrayPtr[i].processorIdentification = (uint8_t)((value1 & MPU_EDR_EPID_MASK) >> MPU_EDR_EPID_SHIFT);
#endif
       }
       slavePort = slavePort >> 1U;
    }
    MPU_BWR_CESR_SPERR(base, 1U); /*!< Clears error slave port bit */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_HAL_SetRegionAddr
 * Description   : Configures region start and end address.
 *
 *END**************************************************************************/
void MPU_HAL_SetRegionAddr(MPU_Type * base, mpu_region_num_t regionNum, uint32_t startAddr, uint32_t endAddr)
{
    assert(regionNum < FSL_FEATURE_MPU_DESCRIPTOR_COUNT);
    startAddr >>= MPU_WORD_SRTADDR_SHIFT;
    endAddr   >>= MPU_WORD_SRTADDR_SHIFT;
    MPU_BWR_WORD_SRTADDR(base, regionNum, 0U, startAddr);
    MPU_BWR_WORD_ENDADDR(base, regionNum, 1U, endAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_HAL_SetLowMasterAccessRights
 * Description   : Configures low master access permission.
 *
 *END**************************************************************************/
void MPU_HAL_SetLowMasterAccessRights(MPU_Type * base, mpu_region_num_t regionNum, mpu_master_t masterNum, const mpu_low_masters_access_rights_t *accessRightsPtr)
{
   assert(accessRightsPtr);
   uint32_t value = 0;
   
   value = ((uint32_t)accessRightsPtr->superAccessRights<<3) | accessRightsPtr->userAccessRights;
   MPU_WR_WORD_LOW_MASTER(base, regionNum, 2u, masterNum, value);
#if FSL_FEATURE_MPU_HAS_PROCESS_IDENTIFIER
   MPU_WR_WORD_PE(base, regionNum, 2U, masterNum, accessRightsPtr->processIdentifierEnable);
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_HAL_SetHighMasterAccessRights
 * Description   : Configures high master access permission.
 *
 *END**************************************************************************/
void MPU_HAL_SetHighMasterAccessRights(MPU_Type * base, mpu_region_num_t regionNum, mpu_master_t masterNum, const mpu_high_masters_access_rights_t *accessRightsPtr)
{
    assert(accessRightsPtr);
    uint32_t value = 0;
    
    value = ((uint32_t)accessRightsPtr->kMPUReadEnable << 1) | accessRightsPtr->kMPUWriteEnable;
    MPU_WR_WORD_HIGH_MASTER(base, regionNum, 2U, masterNum - 4, value);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_HAL_SetLowMasterAccessRightsByAlternateReg
 * Description   : Configures low master access permission by alternate register.
 *
 *END**************************************************************************/
void MPU_HAL_SetLowMasterAccessRightsByAlternateReg(MPU_Type * base, mpu_region_num_t regionNum, mpu_master_t masterNum, const mpu_low_masters_access_rights_t *accessRightsPtr)
{
    assert(accessRightsPtr);
    uint32_t value = 0;
    
    value = ((uint32_t)accessRightsPtr->superAccessRights<<3) | accessRightsPtr->userAccessRights;
    
    MPU_WR_WORD_RGDAAC_LOW_MASTER(base, regionNum, masterNum, value);
#if FSL_FEATURE_MPU_HAS_PROCESS_IDENTIFIER
    value = 0;
    value = accessRightsPtr->processIdentifierEnable;
    MPU_WR_WORD_RGDAAC_PE(base, regionNum, masterNum, value);
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_HAL_SetHighMasterAccessRightsByALternateReg
 * Description   : Configures high master access permission by alternate register.
 *
 *END**************************************************************************/
void MPU_HAL_SetHighMasterAccessRightsByAlternateReg(MPU_Type * base, mpu_region_num_t regionNum, mpu_master_t masterNum, const mpu_high_masters_access_rights_t *accessRightsPtr)
{
    assert(accessRightsPtr);
    uint32_t value = 0;
    
    value = ((uint32_t)accessRightsPtr->kMPUReadEnable << 1) | accessRightsPtr->kMPUWriteEnable;
    MPU_WR_WORD_RGDAAC_HIGH_MASTER(base, regionNum, masterNum - 4, value);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_HAL_SetRegionConfig
 * Description   : Configures a region.
 *
 *END**************************************************************************/
void MPU_HAL_SetRegionConfig(MPU_Type * base, const mpu_region_config_t *regionConfigPtr)
{
    assert(regionConfigPtr);
    uint32_t value = 0;
    uint32_t i;
    
    MPU_HAL_SetRegionAddr(base, regionConfigPtr->regionNum,
            regionConfigPtr->startAddr, regionConfigPtr->endAddr);

    for(i = 0; i < 4; i++)
    {
      value = value | MPU_WORD_LOW_MASTER(i ,((uint32_t)regionConfigPtr->accessRights1[i].superAccessRights << 3) | regionConfigPtr->accessRights1[i].userAccessRights);
#if FSL_FEATURE_MPU_HAS_PROCESS_IDENTIFIER
      value = value | MPU_WORD_MASTER_PE(i, regionConfigPtr->accessRights1[i].processIdentifierEnable);
#endif
      value = value | MPU_WORD_HIGH_MASTER(i, ((uint32_t)regionConfigPtr->accessRights2[i].kMPUWriteEnable<<1) | regionConfigPtr->accessRights2[i].kMPUReadEnable);
    }
    MPU_WR_WORD(base, regionConfigPtr->regionNum, 2U, value);
    MPU_BWR_WORD_VLD(base, regionConfigPtr->regionNum, 3U, regionConfigPtr->regionEnable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : MPU_HAL_Init
 * Description   : Initialize MPU module and all regoins will be invalid after cleared access permission.
 *
 *END**************************************************************************/
void MPU_HAL_Init(MPU_Type * base)
{
    uint32_t i;
    
    MPU_HAL_Disable(base);
    for(i = 1; i < FSL_FEATURE_MPU_DESCRIPTOR_COUNT; i++)
    {
        MPU_HAL_SetRegionAddr(base, (mpu_region_num_t)i, 0, 0);
        MPU_WR_WORD(base, (mpu_region_num_t)i, 2U, 0U);
        MPU_WR_RGDAAC(base, (mpu_region_num_t)i, 0U);
        MPU_HAL_SetRegionValidCmd(base, (mpu_region_num_t)i, 0U);
    }
}
