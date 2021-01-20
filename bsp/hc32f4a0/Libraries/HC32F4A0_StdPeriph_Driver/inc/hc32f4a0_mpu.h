/**
 *******************************************************************************
 * @file  hc32f4a0_mpu.h
 * @brief This file contains all the functions prototypes of the MPU driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_MPU_H__
#define __HC32F4A0_MPU_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_MPU
 * @{
 */

#if (DDL_MPU_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup MPU_Global_Types MPU Global Types
 * @{
 */

/**
 * @brief MPU Unit configure structure definition
 */
typedef struct
{
    uint32_t u32ExceptionType;                  /*!< Specifies the type of exception that occurs when the unit accesses a protected region.
                                                     This parameter can be a value of @ref MPU_Exception_Type           */
    uint32_t u32BackgroundWriteProtect;         /*!< Specifies the unit's write protection for the background space.
                                                     This parameter can be a value of @ref MPU_Background_Write_Protect */
    uint32_t u32BackgroundReadProtect;          /*!< Specifies the unit's read protection for the background space
                                                     This parameter can be a value of @ref MPU_Background_Read_Protect  */
} stc_mpu_unit_config_t;

/**
 * @brief MPU Init structure definition
 */
typedef struct
{
    stc_mpu_unit_config_t stcDma1;              /*!< Configure storage protection unit of DMA1      */
    stc_mpu_unit_config_t stcDma2;              /*!< Configure storage protection unit of DMA2      */
    stc_mpu_unit_config_t stcUsbFSDma;          /*!< Configure storage protection unit of USBFS_DMA */
    stc_mpu_unit_config_t stcUsbHSDma;          /*!< Configure storage protection unit of USBHS_DMA */
    stc_mpu_unit_config_t stcEthDma;            /*!< Configure storage protection unit of ETH_DMA   */
} stc_mpu_init_t;

/**
 * @brief MPU Region Permission structure definition
 */
typedef struct
{
    uint32_t u32WriteProtect;                   /*!< Specifies the unit's write protection for the region.
                                                     This parameter can be a value of @ref MPU_Region_Write_Protect */
    uint32_t u32ReadProtect;                    /*!< Specifies the unit's read protection  for the region.
                                                     This parameter can be a value of @ref MPU_Region_Read_Protect */
} stc_mpu_region_permission_t;

/**
 * @brief MPU region initialization structure definition
 * @note  The effective bits of the 'u32BaseAddr' are related to the 'u32Size' of the region,
 *        and the low 'u32Size+1' bits are fixed at 0.
 */
typedef struct
{
    uint32_t u32BaseAddr;                       /*!< Specifies the base address of the region.
                                                     This parameter can be a number between 0UL and 0xFFFFFFE0UL */
    uint32_t u32Size;                           /*!< Specifies the size of the region.
                                                     This parameter can be a value of @ref MPU_Region_Size       */
    stc_mpu_region_permission_t stcDma1;        /*!< Specifies the DMA1 access permission for the region         */
    stc_mpu_region_permission_t stcDma2;        /*!< Specifies the DMA2 access permission for the region         */
    stc_mpu_region_permission_t stcUsbFSDma;    /*!< Specifies the USBFS_DMA access permission for the region    */
    stc_mpu_region_permission_t stcUsbHSDma;    /*!< Specifies the USBHS_DMA access permission for the region    */
    stc_mpu_region_permission_t stcEthDma;      /*!< Specifies the ETH_DMA access permission for the region      */
} stc_mpu_region_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup MPU_Global_Macros MPU Global Macros
 * @{
 */

/**
 * @defgroup MPU_Unit_Type MPU Unit Type
 * @{
 */
#define MPU_UNIT_DMA1                           (0x01UL)  /*!< System DMA_1 MPU */
#define MPU_UNIT_DMA2                           (0x02UL)  /*!< System DMA_2 MPU */
#define MPU_UNIT_USBFS_DMA                      (0x04UL)  /*!< USBFS_DMA MPU    */
#define MPU_UNIT_USBHS_DMA                      (0x08UL)  /*!< USBHS_DMA MPU    */
#define MPU_UNIT_ETH_DMA                        (0x10UL)  /*!< ETH_DMA MPU      */
#define MPU_UNIT_ALL                            (0x1FUL)
/**
 * @}
 */

/**
 * @defgroup MPU_Region_Number MPU Region Number
 * @note     'MPU_REGION_NUM8' to 'MPU_REGION_NUM15' are only valid when the MPU unit is 'MPU_UNIT_DMA1' or 'MPU_UNIT_DMA2'.
 * @{
 */
#define MPU_REGION_NUM0                         (0x00UL)  /*!< MPU region number 0  */
#define MPU_REGION_NUM1                         (0x01UL)  /*!< MPU region number 1  */
#define MPU_REGION_NUM2                         (0x02UL)  /*!< MPU region number 2  */
#define MPU_REGION_NUM3                         (0x03UL)  /*!< MPU region number 3  */
#define MPU_REGION_NUM4                         (0x04UL)  /*!< MPU region number 4  */
#define MPU_REGION_NUM5                         (0x05UL)  /*!< MPU region number 5  */
#define MPU_REGION_NUM6                         (0x06UL)  /*!< MPU region number 6  */
#define MPU_REGION_NUM7                         (0x07UL)  /*!< MPU region number 7  */
#define MPU_REGION_NUM8                         (0x08UL)  /*!< MPU region number 8  */
#define MPU_REGION_NUM9                         (0x09UL)  /*!< MPU region number 9  */
#define MPU_REGION_NUM10                        (0x0AUL)  /*!< MPU region number 10 */
#define MPU_REGION_NUM11                        (0x0BUL)  /*!< MPU region number 11 */
#define MPU_REGION_NUM12                        (0x0CUL)  /*!< MPU region number 12 */
#define MPU_REGION_NUM13                        (0x0DUL)  /*!< MPU region number 13 */
#define MPU_REGION_NUM14                        (0x0EUL)  /*!< MPU region number 14 */
#define MPU_REGION_NUM15                        (0x0FUL)  /*!< MPU region number 15 */
/**
 * @}
 */

/**
 * @defgroup MPU_Background_Write_Protect MPU Background Write Protect
 * @{
 */
#define MPU_BKGRD_WR_PROTECT_DISABLE            (0UL)                 /*!< Disable write protection of background space */
#define MPU_BKGRD_WR_PROTECT_ENABLE             (MPU_S1CR_SMPU1BWP)   /*!< Enable write protection of background space  */
/**
 * @}
 */

/**
 * @defgroup MPU_Background_Read_Protect MPU Background Read Protect
 * @{
 */
#define MPU_BKGRD_RD_PROTECT_DISABLE            (0UL)                 /*!< Disable read protection of background space */
#define MPU_BKGRD_RD_PROTECT_ENABLE             (MPU_S1CR_SMPU1BRP)   /*!< Enable read protection of background space  */
/**
 * @}
 */

/**
 * @defgroup MPU_Exception_Type MPU Exception Type
 * @{
 */
#define MPU_EXP_TYPE_NONE                       (0UL)                   /*!< The host unit access protection regions will be ignored                                       */
#define MPU_EXP_TYPE_BUS_ERR                    (MPU_S1CR_SMPU1ACT_0)   /*!< The host unit access protection regions will be ignored and a bus error will be triggered     */
#define MPU_EXP_TYPE_NMI                        (MPU_S1CR_SMPU1ACT_1)   /*!< The host unit access protection regions will be ignored and a NMI interrupt will be triggered */
#define MPU_EXP_TYPE_RST                        (MPU_S1CR_SMPU1ACT)     /*!< The host unit access protection regions will trigger the reset                                */
/**
 * @}
 */

/**
 * @defgroup MPU_Region_Write_Protect MPU Region Write Protect
 * @{
 */
#define MPU_REGION_WR_PROTECT_DISABLE           (0UL)                 /*!< Disable write protection of the region */
#define MPU_REGION_WR_PROTECT_ENABLE            (MPU_S1RGWP_S1RG0WP)  /*!< Enable write protection of the region  */
/**
 * @}
 */

/**
 * @defgroup MPU_Region_Read_Protect MPU Region Read Protect
 * @{
 */
#define MPU_REGION_RD_PROTECT_DISABLE           (0UL)                 /*!< Disable read protection of the region */
#define MPU_REGION_RD_PROTECT_ENABLE            (MPU_S1RGRP_S1RG0RP)  /*!< Enable read protection of the region  */
/**
 * @}
 */

/**
 * @defgroup MPU_Region_Size MPU Region Size
 * @{
 */
#define MPU_REGION_SIZE_32BYTE                  (0x04UL)  /*!< 32 Byte   */
#define MPU_REGION_SIZE_64BYTE                  (0x05UL)  /*!< 64 Byte   */
#define MPU_REGION_SIZE_128BYTE                 (0x06UL)  /*!< 126 Byte  */
#define MPU_REGION_SIZE_256BYTE                 (0x07UL)  /*!< 256 Byte  */
#define MPU_REGION_SIZE_512BYTE                 (0x08UL)  /*!< 512 Byte  */
#define MPU_REGION_SIZE_1KBYTE                  (0x09UL)  /*!< 1K Byte   */
#define MPU_REGION_SIZE_2KBYTE                  (0x0AUL)  /*!< 2K Byte   */
#define MPU_REGION_SIZE_4KBYTE                  (0x0BUL)  /*!< 4K Byte   */
#define MPU_REGION_SIZE_8KBYTE                  (0x0CUL)  /*!< 8K Byte   */
#define MPU_REGION_SIZE_16KBYTE                 (0x0DUL)  /*!< 16K Byte  */
#define MPU_REGION_SIZE_32KBYTE                 (0x0EUL)  /*!< 32K Byte  */
#define MPU_REGION_SIZE_64KBYTE                 (0x0FUL)  /*!< 64K Byte  */
#define MPU_REGION_SIZE_128KBYTE                (0x10UL)  /*!< 128K Byte */
#define MPU_REGION_SIZE_256KBYTE                (0x11UL)  /*!< 256K Byte */
#define MPU_REGION_SIZE_512KBYTE                (0x12UL)  /*!< 512K Byte */
#define MPU_REGION_SIZE_1MBYTE                  (0x13UL)  /*!< 1M Byte   */
#define MPU_REGION_SIZE_2MBYTE                  (0x14UL)  /*!< 2M Byte   */
#define MPU_REGION_SIZE_4MBYTE                  (0x15UL)  /*!< 4M Byte   */
#define MPU_REGION_SIZE_8MBYTE                  (0x16UL)  /*!< 8M Byte   */
#define MPU_REGION_SIZE_16MBYTE                 (0x17UL)  /*!< 16M Byte  */
#define MPU_REGION_SIZE_32MBYTE                 (0x18UL)  /*!< 32M Byte  */
#define MPU_REGION_SIZE_64MBYTE                 (0x19UL)  /*!< 64M Byte  */
#define MPU_REGION_SIZE_128MBYTE                (0x1AUL)  /*!< 128M Byte */
#define MPU_REGION_SIZE_256MBYTE                (0x1BUL)  /*!< 256M Byte */
#define MPU_REGION_SIZE_512MBYTE                (0x1CUL)  /*!< 512M Byte */
#define MPU_REGION_SIZE_1GBYTE                  (0x1DUL)  /*!< 1G Byte   */
#define MPU_REGION_SIZE_2GBYTE                  (0x1EUL)  /*!< 2G Byte   */
#define MPU_REGION_SIZE_4GBYTE                  (0x1FUL)  /*!< 4G Byte   */
/**
 * @}
 */

/**
 * @defgroup MPU_Flag MPU Flag
 * @{
 */
#define MPU_FLAG_SMPU1EAF                       (MPU_SR_SMPU1EAF)   /*!< System DMA_1 error flag */
#define MPU_FLAG_SMPU2EAF                       (MPU_SR_SMPU2EAF)   /*!< System DMA_2 error flag */
#define MPU_FLAG_FMPUEAF                        (MPU_SR_FMPUEAF)    /*!< USBFS_DMA error flag    */
#define MPU_FLAG_HMPUEAF                        (MPU_SR_HMPUEAF)    /*!< USBHS_DMA error flag    */
#define MPU_FLAG_EMPUEAF                        (MPU_SR_EMPUEAF)    /*!< ETH_DMA error flag      */
#define MPU_FLAG_ALL                            (0x0000001FUL)
/**
 * @}
 */

/**
 * @defgroup MPU_IP_Type MPU IP Type
 * @note     IP access protection is not available in privileged mode.
 * @{
 */
#define MPU_IP_AES                              (MPU_IPPR_AESRDP)     /*!< AES module    */
#define MPU_IP_HASH                             (MPU_IPPR_HASHRDP)    /*!< HASH module   */
#define MPU_IP_TRNG                             (MPU_IPPR_TRNGRDP)    /*!< TRNG module   */
#define MPU_IP_CRC                              (MPU_IPPR_CRCRDP)     /*!< CRC module    */
#define MPU_IP_FMC                              (MPU_IPPR_FMCRDP)     /*!< FMC module    */
#define MPU_IP_WDT                              (MPU_IPPR_WDTRDP)     /*!< WDT module    */
#define MPU_IP_SWDT                             (MPU_IPPR_SWDTRDP)    /*!< SWDT module   */
#define MPU_IP_BKSRAM                           (MPU_IPPR_BKSRAMRDP)  /*!< BKSRAM module */
#define MPU_IP_RTC                              (MPU_IPPR_RTCRDP)     /*!< RTC module    */
#define MPU_IP_DMPU                             (MPU_IPPR_DMPURDP)    /*!< DMPU module   */
#define MPU_IP_SRAMC                            (MPU_IPPR_SRAMCRDP)   /*!< SRAMC module  */
#define MPU_IP_INTC                             (MPU_IPPR_INTCRDP)    /*!< INTC module   */
#define MPU_IP_SYSC                             (MPU_IPPR_SYSCRDP)    /*!< SYSC module   */
#define MPU_IP_MSTP                             (MPU_IPPR_MSTPRDP)    /*!< MSTP module   */
#define MPU_IP_ALL                              (0x15555155UL)
/**
 * @}
 */

/**
 * @defgroup MPU_IP_Exception_Type MPU IP Exception Type
 * @{
 */
#define MPU_IP_EXP_TYPE_NONE                    (0UL)               /*!< Access to the protected IP will be ignored          */
#define MPU_IP_EXP_TYPE_BUS_ERR                 (MPU_IPPR_BUSERRE)  /*!< Access to the protected IP will trigger a bus error */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup MPU_Global_Functions
 * @{
 */

/**
 * @brief  MPU write protect unlock.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void MPU_Unlock(void)
{
    WRITE_REG32(M4_MPU->WP, 0x96A5UL);
}

/**
 * @brief  MPU write protect lock.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void MPU_Lock(void)
{
    WRITE_REG32(M4_MPU->WP, 0x96A4UL);
}

void MPU_Unlock(void);
void MPU_Lock(void);

void MPU_DeInit(void);
en_result_t MPU_Init(const stc_mpu_init_t *pstcMpuInit);
en_result_t MPU_StructInit(stc_mpu_init_t *pstcMpuInit);
void MPU_SetExceptionType(uint32_t u32Unit, uint32_t u32ExceptionType);
void MPU_BackgroundWriteProtectCmd(uint32_t u32Unit, en_functional_state_t enNewState);
void MPU_BackgroundReadProtectCmd(uint32_t u32Unit, en_functional_state_t enNewState);
void MPU_UnitCmd(uint32_t u32Unit, en_functional_state_t enNewState);
en_flag_status_t MPU_GetStatus(uint32_t u32Flag);
void MPU_ClearStatus(uint32_t u32Flag);

en_result_t MPU_RegionInit(uint32_t u32Num, const stc_mpu_region_init_t *pstcRegionInit);
en_result_t MPU_RegionStructInit(stc_mpu_region_init_t *pstcRegionInit);
void MPU_SetRegionBaseAddr(uint32_t u32Num, uint32_t u32Addr);
void MPU_SetRegionSize(uint32_t u32Num, uint32_t u32Size);
void MPU_RegionWriteProtectCmd(uint32_t u32Num, uint32_t u32Unit, en_functional_state_t enNewState);
void MPU_RegionReadProtectCmd(uint32_t u32Num, uint32_t u32Unit, en_functional_state_t enNewState);
void MPU_RegionCmd(uint32_t u32Num, uint32_t u32Unit, en_functional_state_t enNewState);

void MPU_IP_SetExceptionType(uint32_t u32ExceptionType);
void MPU_IP_WriteProtectCmd(uint32_t u32Peripheral, en_functional_state_t enNewState);
void MPU_IP_ReadProtectCmd(uint32_t u32Peripheral, en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* DDL_MPU_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_MPU_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
