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
#ifndef __FSL_MPU_HAL_H__
#define __FSL_MPU_HAL_H__

#define FSL_FEATURE_MPU_SLAVEPORT                  5U
#define FSL_FEATURE_MPU_MASTER                     8U

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_MPU_COUNT

/*!
 * @addtogroup mpu_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/
 
/* Macro should be in MK64F12.h */
#define MPU_WORD_LOW_MASTER_SHIFT(n)             (n*6)
#define MPU_WORD_LOW_MASTER_MASK(n)              (0x1Fu<<MPU_WORD_LOW_MASTER_SHIFT(n))
#define MPU_WORD_LOW_MASTER_WIDTH                5
#define MPU_WORD_LOW_MASTER(n, x)                (((uint32_t)(((uint32_t)(x))<<MPU_WORD_LOW_MASTER_SHIFT(n)))&MPU_WORD_LOW_MASTER_MASK(n))

#define MPU_LOW_MASTER_PE_SHIFT(n)               (n*6+5)  
#define MPU_LOW_MASTER_PE_MASK(n)                (0x1u << MPU_LOW_MASTER_PE_SHIFT(n))
#define MPU_WORD_MASTER_PE_WIDTH                 1
#define MPU_WORD_MASTER_PE(n, x)                 (((uint32_t)(((uint32_t)(x))<<MPU_LOW_MASTER_PE_SHIFT(n)))&MPU_LOW_MASTER_PE_MASK(n))

#define MPU_WORD_HIGH_MASTER_SHIFT(n)            (n*2+23)
#define MPU_WORD_HIGH_MASTER_MASK(n)             (0x03u << MPU_WORD_HIGH_MASTER_SHIFT(n))
#define MPU_WORD_HIGH_MASTER_WIDTH               2
#define MPU_WORD_HIGH_MASTER(n, x)               (((uint32_t)(((uint32_t)(x))<<MPU_WORD_HIGH_MASTER_SHIFT(n)))&MPU_WORD_HIGH_MASTER_MASK(n))

/* Macro should be in MK64F12_extension.h */
#define MPU_WR_WORD_LOW_MASTER(base, index, index2, n, value) (MPU_WR_WORD(base, index, index2, (MPU_RD_WORD(base, index, index2) & ~MPU_WORD_LOW_MASTER_MASK(n)) | MPU_WORD_LOW_MASTER(n, value)))
#define MPU_WR_WORD_PE(base, index, index2, n, value) (MPU_WR_WORD(base, index, index2, (MPU_RD_WORD(base, index, index2) & ~MPU_LOW_MASTER_PE_MASK(n)) | MPU_WORD_MASTER_PE(n, value)))
#define MPU_WR_WORD_HIGH_MASTER(base, index, index2, n, value) (MPU_WR_WORD(base, index, index2, (MPU_RD_WORD(base, index, index2) & ~MPU_WORD_HIGH_MASTER_MASK(n)) | MPU_WORD_HIGH_MASTER(n, value)))

#define MPU_WR_WORD_RGDAAC_LOW_MASTER(base, index, n, value) (MPU_WR_RGDAAC(base, index, (MPU_RD_RGDAAC(base, index) & ~MPU_WORD_LOW_MASTER_MASK(n)) | MPU_WORD_LOW_MASTER(n, value)))
#define MPU_WR_WORD_RGDAAC_PE(base, index, n, value) (MPU_WR_RGDAAC(base, index, (MPU_RD_RGDAAC(base, index) & ~MPU_LOW_MASTER_PE_MASK(n)) | MPU_WORD_MASTER_PE(n, value)))
#define MPU_WR_WORD_RGDAAC_HIGH_MASTER(base, index, n, value) (MPU_WR_RGDAAC(base, index, (MPU_RD_RGDAAC(base, index) & ~MPU_WORD_HIGH_MASTER_MASK(n)) | MPU_WORD_HIGH_MASTER(n, value)))

/*! @brief MPU region number region0~region11. */
typedef enum _mpu_region_num{
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 0U
    kMPURegionNum00 = 0U,  /*!< MPU region number 0*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 1U
    kMPURegionNum01 = 1U,  /*!< MPU region number 1*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 2U
    kMPURegionNum02 = 2U,  /*!< MPU region number 2*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 3U
    kMPURegionNum03 = 3U,  /*!< MPU region number 3*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 4U
    kMPURegionNum04 = 4U,  /*!< MPU region number 4*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 5U
    kMPURegionNum05 = 5U,  /*!< MPU region number 5*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 6U
    kMPURegionNum06 = 6U,  /*!< MPU region number 6*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 7U
    kMPURegionNum07 = 7U,  /*!< MPU region number 7*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 8U
    kMPURegionNum08 = 8U,  /*!< MPU region number 8*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 9U
    kMPURegionNum09 = 9U,  /*!< MPU region number 9*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 10U
    kMPURegionNum10 = 10U, /*!< MPU region number 10*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 11U
    kMPURegionNum11 = 11U, /*!< MPU region number 11*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 12U
    kMPURegionNum12 = 12U, /*!< MPU region number 12*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 13U
    kMPURegionNum13 = 13U, /*!< MPU region number 13*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 14U
    kMPURegionNum14 = 14U, /*!< MPU region number 14*/
#endif
#if FSL_FEATURE_MPU_DESCRIPTOR_COUNT > 15U
    kMPURegionNum15 = 15U, /*!< MPU region number 15*/
#endif
}mpu_region_num_t;

/*! @brief Descripts the number of MPU regions. */
typedef enum _mpu_region_total_num
{
    kMPU8Regions  = 0x0U,    /*!< MPU supports 8 regions  */
    kMPU12Regions = 0x1U,    /*!< MPU supports 12 regions */
    kMPU16Regions = 0x2U     /*!< MPU supports 16 regions */
}mpu_region_total_num_t;

/*! @brief MPU hardware basic information. */
typedef struct _mpu_hardware_info
{
    uint8_t                kMPUHardwareRevisionLevel;   /*!< Specifies the MPU's hardware and definition reversion level */
    uint8_t                kMPUSupportSlavePortsNum;    /*!< Specifies the number of slave ports connnected to MPU       */
    mpu_region_total_num_t kMPUSupportRegionsNum;       /*!< Indicates the number of region descriptors implemented      */
}mpu_hardware_info_t;

/*! @brief MPU access error. */
typedef enum _mpu_err_access_type{
    kMPUErrTypeRead  = 0U,     /*!< MPU error type---read  */
    kMPUErrTypeWrite = 1U      /*!< MPU error type---write */
}mpu_err_access_type_t;

/*! @brief MPU access error attributes.*/
typedef enum _mpu_err_attributes{
    kMPUInstructionAccessInUserMode       = 0U,  /*!< access instruction error in user mode       */
    kMPUDataAccessInUserMode              = 1U,  /*!< access data error in user mode              */
    kMPUInstructionAccessInSupervisorMode = 2U,  /*!< access instruction error in supervisor mode */
    kMPUDataAccessInSupervisorMode        = 3U   /*!< access data error in supervisor mode        */
}mpu_err_attributes_t;

/*! @brief access MPU in which mode. */
typedef enum _mpu_access_mode{
    kMPUAccessInUserMode       = 0U, /*!< access data or instruction in user mode*/
    kMPUAccessInSupervisorMode = 1U  /*!< access data or instruction in supervisor mode*/
}mpu_access_mode_t;

/*! @brief MPU master number. */
typedef enum _mpu_master{
#if FSL_FEATURE_MPU_MASTER > 1U
    kMPUMaster0  = 0U, /*!< MPU master core           */
#endif
#if FSL_FEATURE_MPU_MASTER > 2U
    kMPUMaster1  = 1U, /*!< MPU master defined in SOC */
#endif
#if FSL_FEATURE_MPU_MASTER > 3U
    kMPUMaster2  = 2U, /*!< MPU master defined in SOC */
#endif
#if FSL_FEATURE_MPU_MASTER > 4U
    kMPUMaster3  = 3U, /*!< MPU master defined in SOC */
#endif
#if FSL_FEATURE_MPU_MASTER > 5U
    kMPUMaster4  = 4U, /*!< MPU master defined in SOC */
#endif
#if FSL_FEATURE_MPU_MASTER > 6U
    kMPUMaster5  = 5U, /*!< MPU master defined in SOC */
#endif
#if FSL_FEATURE_MPU_MASTER > 7U
    kMPUMaster6  = 6U, /*!< MPU master defined in SOC */
#endif
#if FSL_FEATURE_MPU_MASTER > 8U
    kMPUMaster7  = 7U  /*!< MPU master defined in SOC */
#endif
}mpu_master_t;

/*! @brief MPU error access control detail. */
typedef enum _mpu_err_access_ctr{
    kMPUNoRegionHit        = 0U,   /*!< no region hit error             */
    kMPUNoneOverlappRegion = 1U,   /*!< access single region error      */
    kMPUOverlappRegion     = 2U    /*!< access overlapping region error */
}mpu_err_access_ctr_t;

/*! @brief Descripts MPU detail error access info. */
typedef struct _mpu_access_err_info
{
    mpu_master_t           master;                    /*!< Access error master                   */
    mpu_err_attributes_t   attributes;                /*!< Access error attribues                */
    mpu_err_access_type_t  accessType;                /*!< Access error type                     */
    mpu_err_access_ctr_t   accessCtr;                 /*!< Access error control                  */
    uint32_t               addr;                      /*!< Access error address                  */
    uint8_t                slavePort;                 /*!< Access error slave port               */
#if FSL_FEATURE_MPU_HAS_PROCESS_IDENTIFIER
    uint8_t                processorIdentification;   /*!< Access error processor identification */
#endif
}mpu_access_err_info_t;

/*! @brief MPU access rights in supervisor mode for master0~master3. */
typedef enum _mpu_supervisor_access_rights{
    kMPUSupervisorReadWriteExecute = 0U,   /*!< Read write and execute operations are allowed in supervisor mode */
    kMPUSupervisorReadExecute      = 1U,   /*!< Read and execute operations are allowed in supervisor mode       */
    kMPUSupervisorReadWrite        = 2U,   /*!< Read write operations are allowed in supervisor mode             */
    kMPUSupervisorEqualToUsermode  = 3U    /*!< Access permission equal to user mode                             */
}mpu_supervisor_access_rights_t;

/*! @brief MPU access rights in user mode for master0~master3. */
typedef enum _mpu_user_access_rights{
    kMPUUserNoAccessRights   = 0U,   /*!< no access allowed in user mode                             */
    kMPUUserExecute          = 1U,   /*!< execute operation is allowed in user mode                  */
    kMPUUserWrite            = 2U,   /*!< Write operation is allowed in user mode                    */
    kMPUUserWriteExecute     = 3U,   /*!< Write and execute operations are allowed in user mode      */
    kMPUUserRead             = 4U,   /*!< Read is allowed in user mode                               */
    kMPUUserReadExecute      = 5U,   /*!< Read and execute operations are allowed in user mode       */
    kMPUUserReadWrite        = 6U,   /*!< Read and write operations are allowed in user mode         */
    kMPUUserReadWriteExecute = 7U    /*!< Read write and execute operations are allowed in user mode */
}mpu_user_access_rights_t;

/*! @brief MPU access rights for low master0~master3. */
typedef struct _mpu_low_masters_access_rights
{
    mpu_supervisor_access_rights_t superAccessRights;  	      /*!< master access rights in supervisor mode */
    mpu_user_access_rights_t       userAccessRights;          /*!< master access rights in user mode       */
#if FSL_FEATURE_MPU_HAS_PROCESS_IDENTIFIER
    bool                           processIdentifierEnable;   /*!< Enables or disables process identifier  */
#endif
}mpu_low_masters_access_rights_t;

/*! @brief MPU access rights mode for high master4~master7. */
typedef struct _mpu_high_masters_access_rights
{
    bool kMPUWriteEnable;    /*!< Enables or disables write permission */
    bool kMPUReadEnable;     /*!< Enables or disables read permission  */
}mpu_high_masters_access_rights_t;

/*! 
 * @brief Data v for MPU region initialize
 *
 * This structure is used when calling the MPU_DRV_Init function.
 * 
 */
typedef struct MpuRegionConfig{
    mpu_region_num_t                 regionNum;         /*!< MPU region number             */
    uint32_t                         startAddr;         /*!< Memory region start address   */
    uint32_t                         endAddr;           /*!< Memory region end address     */
    mpu_low_masters_access_rights_t  accessRights1[4];  /*!< Low masters access permission */
    mpu_high_masters_access_rights_t accessRights2[4];  /*!< Low masters access permission */
    bool                             regionEnable;      /*!< Enables or disables region    */
}mpu_region_config_t;

/*! @brief MPU status return codes.*/
typedef enum _MPU_status {
    kStatus_MPU_Success          = 0x0U,  /*!< MPU Succeed.                */
    kStatus_MPU_Fail             = 0x1U,  /*!< MPU failed.                 */
    kStatus_MPU_NotInitlialized  = 0x2U,  /*!< MPU is not initialized yet. */
    kStatus_MPU_NullArgument     = 0x3U,  /*!< Argument is NULL.           */
 } mpu_status_t;

/*******************************************************************************
 ** Variables
 *******************************************************************************/

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name MPU HAL.
 * @{
 */

/*!
 * @brief Enables the MPU module operation.
 *
 * @param base Base address of MPU peripheral instance.
 */
static inline void MPU_HAL_Enable(MPU_Type * base)
{
    MPU_BWR_CESR_VLD(base, 1U);
}

/*!
 * @brief Disables the MPU module operation.
 *
 * @param base Base address of MPU peripheral instance.
 */
static inline void MPU_HAL_Disable(MPU_Type * base)
{
    MPU_BWR_CESR_VLD(base, 0U);
}

/*!
 * @brief Checks whether the MPU module is enabled
 *
 * @param base Base address of MPU peripheral instance.
 * @return State of the module
 * @retval true MPU module is enabled.
 * @retval false MPU module is disabled.
 */
static inline bool MPU_HAL_IsEnable(MPU_Type * base)
{
   return MPU_BRD_CESR_VLD(base);
}

/*!
 * @brief Gets MPU basic hardware info.
 *
 * @param base Base address of MPU peripheral instance.
 * @param infoPtr The pointer to the hardware information structure see #mpu_hardware_info_t.
 */
void MPU_HAL_GetHardwareInfo(MPU_Type *base, mpu_hardware_info_t *infoPtr);

/*!
 * @brief Gets MPU derail error access info.
 *
 * @param base Base address of MPU peripheral instance.
 * @param errInfoArrayPtr The pointer to array of structure mpu_access_err_info_t.
 */
void MPU_HAL_GetDetailErrorAccessInfo(MPU_Type *base, mpu_access_err_info_t *errInfoArrayPtr);

/*!
 * @brief Sets region start and end address.
 *
 * @param base Base address of MPU peripheral instance..
 * @param regionNum MPU region number.
 * @param startAddr Region start address.
 * @param endAddr Region end address.
 */
void MPU_HAL_SetRegionAddr(MPU_Type * base, mpu_region_num_t regionNum, uint32_t startAddr, uint32_t endAddr);

/*!
 * @brief Configures low master0~3 access permission for a specific region.
 *
 * @param base Base address of MPU peripheral instance.
 * @param regionNum MPU region number.
 * @param masterNum MPU master number.
 * @param accessRightsPtr The pointer of master access rights see #mpu_low_masters_access_rights_t.
 */
void MPU_HAL_SetLowMasterAccessRights(MPU_Type * base, mpu_region_num_t regionNum, mpu_master_t masterNum, const mpu_low_masters_access_rights_t *accessRightsPtr);

/*!
 * @brief Sets high master access permission for a specific region.
 *
 * @param base Base address of MPU peripheral instance.
 * @param regionNum MPU region number.
 * @param masterNum MPU master number.
 * @param accessRightsPtr The pointer of master access rights see #mpu_low_masters_access_rights_t.
 */
void MPU_HAL_SetHighMasterAccessRights(MPU_Type * base, mpu_region_num_t regionNum, mpu_master_t masterNum, const mpu_high_masters_access_rights_t *accessRightsPtr);

/*!
 * @brief Sets the region valid value.
 * When a region changed not by alternating registers should set the valid again.
 *
 * @param base Base address of MPU peripheral instance.
 * @param regionNum MPU region number.
 * @param enable Enables or disables region.
 */
static inline void MPU_HAL_SetRegionValidCmd(MPU_Type * base, mpu_region_num_t regionNum, bool enable)
{
    assert(regionNum < FSL_FEATURE_MPU_DESCRIPTOR_COUNT);
    MPU_BWR_WORD_VLD(base, regionNum, 3U, enable);
}

#if FSL_FEATURE_MPU_HAS_PROCESS_IDENTIFIER
/*!
 * @brief Sets the process identifier mask.
 *
 * @param base The MPU peripheral base address.
 * @param regionNum MPU region number.
 * @param processIdentifierMask Process identifier mask value.
 */
static inline void MPU_HAL_SetProcessIdentifierMask(MPU_Type * base, mpu_region_num_t regionNum, uint8_t processIdentifierMask)
{
    assert(regionNum < FSL_FEATURE_MPU_DESCRIPTOR_COUNT);
    MPU_BWR_WORD_PIDMASK(base, regionNum, 3U, processIdentifierMask);
}

/*!
 * @brief Sets the process identifier.
 *
 * @param base The MPU peripheral base address.
 * @param regionNum MPU region number.
 * @param processIdentifier Process identifier.
 */
static inline void MPU_HAL_SetProcessIdentifier(MPU_Type * base, mpu_region_num_t regionNum, uint8_t processIdentifier)
{
    assert(regionNum < FSL_FEATURE_MPU_DESCRIPTOR_COUNT);
    MPU_BWR_WORD_PID(base, regionNum, 3U, processIdentifier);
}
#endif

/*!
 * @brief Configures low master0~3 access permission for a specific region.
 *
 * @param base Base address of MPU peripheral instance.
 * @param regionNum MPU region number.
 * @param masterNum MPU master number.
 * @param accessRightsPtr The pointer of master access rights see #mpu_low_masters_access_rights_t.
 */
void MPU_HAL_SetLowMasterAccessRightsByAlternateReg(MPU_Type * base, mpu_region_num_t regionNum, mpu_master_t masterNum, const mpu_low_masters_access_rights_t *accessRightsPtr);

/*!
 * @brief Sets high master access permission for a specific region.
 *
 * @param base Base address of MPU peripheral instance.
 * @param regionNum MPU region number.
 * @param masterNum MPU master number.
 * @param accessRightsPtr The pointer of master access rights see #mpu_low_masters_access_rights_t.
 */
void MPU_HAL_SetHighMasterAccessRightsByAlternateReg(MPU_Type * base, mpu_region_num_t regionNum, mpu_master_t masterNum, const mpu_high_masters_access_rights_t *accessRightsPtr);


/*!
 * @brief Configures the MPU region.
 *
 * @param base The MPU peripheral base address.
 * @param regionConfigPtr The pointer to the MPU user configure structure, see #mpu_region_config_t.
 * 
 */
void MPU_HAL_SetRegionConfig(MPU_Type * base, const mpu_region_config_t *regionConfigPtr);

/*!
 * @brief Initializes the MPU module.
 *
 * @param base The MPU peripheral base address.
 */
void MPU_HAL_Init(MPU_Type * base);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_MPU_HAL_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

