/**
 *******************************************************************************
 * @file  hc32_ll_smc.h
 * @brief This file contains all the functions prototypes of the EXMC_SMC
 *        (External Memory Controller: Static Memory Controller) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_SMC_H__
#define __HC32_LL_SMC_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_EXMC
 * @{
 */

/**
 * @addtogroup LL_SMC
 * @{
 */

#if (LL_SMC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EXMC_SMC_Global_Types EXMC_SMC Global Types
 * @{
 */

/**
 * @brief  EXMC_SMC Chip Configuration Structure definition
 */
typedef struct {
    uint32_t u32ReadMode;       /*!< Defines the read sync enable.
                                     This parameter can be a value of @ref EXMC_SMC_Memory_Read_Mode */
    uint32_t u32WriteMode;      /*!< Defines the write sync enable.
                                     This parameter can be a value of @ref EXMC_SMC_Memory_Write_Mode */
    uint32_t u32MemoryWidth;    /*!< Defines the SMC memory width.
                                     This parameter can be a value of @ref EXMC_SMC_Memory_Width. */
    uint32_t u32BAA;            /*!< Defines the SMC BAA signal enable.
                                     This parameter can be a value of @ref EXMC_SMC_BAA_Port_Selection. */
    uint32_t u32ADV;            /*!< Defines the SMC ADVS signal enable.
                                     This parameter can be a value of @ref EXMC_SMC_ADV_Port_Selection. */
    uint32_t u32BLS;            /*!< Defines the SMC BLS signal selection.
                                     This parameter can be a value of @ref EXMC_SMC_BLS_Synchronization_Selection. */
    uint32_t u32AddrMatch;      /*!< Defines the address match.
                                     This parameter can be a value between Min_Data = 0x60 and Max_Data = 0x7F */
    uint32_t u32AddrMask;       /*!< Defines the address mask.
                                     This parameter can be a value of @ref EXMC_SMC_Mask_Address. */
} stc_exmc_smc_chip_config_t;

/**
 * @brief  EXMC_SMC Timing Configuration Structure definition
 */
typedef struct {
    uint8_t u8RC;               /*!< Defines the RC in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 0x0F */
    uint8_t u8WC;               /*!< Defines the WC in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 0x0F */
    uint8_t u8CEOE;             /*!< Defines the CEOE in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
    uint8_t u8WP;               /*!< Defines the WP in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
    uint8_t u8TR;               /*!< Defines the TR in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
    uint8_t u8ADV;              /*!< Defines the ADV in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
} stc_exmc_smc_timing_config_t;

/**
 * @brief  EXMC_SMC Initialization Structure definition
 */
typedef struct {
    stc_exmc_smc_chip_config_t   stcChipConfig;     /*!< SMC memory chip configure.
                                                         This structure details refer @ref stc_exmc_smc_chip_config_t. */
    stc_exmc_smc_timing_config_t stcTimingConfig;   /*!< SMC memory timing configure.
                                                         This structure details refer @ref stc_exmc_smc_timing_config_t. */
} stc_exmc_smc_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EXMC_SMC_Global_Macros EXMC_SMC Global Macros
 * @{
 */

/**
 * @defgroup EXMC_SMC_Chip EXMC_SMC Chip
 * @{
 */
#define EXMC_SMC_CHIP0                          (0UL)     /*!< Chip 0 */
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Memory_Read_Mode EXMC_SMC Memory Read Mode
 * @{
 */
#define EXMC_SMC_READ_ASYNC                     (0UL)
#define EXMC_SMC_READ_SYNC                      (SMC_CPCR_RSYN)
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Memory_Write_Mode EXMC_SMC Memory Write Mode
 * @{
 */
#define EXMC_SMC_WRITE_ASYNC                    (0UL)
#define EXMC_SMC_WRITE_SYNC                     (SMC_CPCR_WSYN)
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Memory_Width EXMC_SMC Memory Width
 * @{
 */
#define EXMC_SMC_MEMORY_WIDTH_8BIT              (0UL)
#define EXMC_SMC_MEMORY_WIDTH_16BIT             (SMC_CPCR_MW_0)
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_BAA_Port_Selection EXMC_SMC BAA Port Selection
 * @{
 */
#define EXMC_SMC_BAA_PORT_DISABLE               (0UL)
#define EXMC_SMC_BAA_PORT_ENABLE                (SMC_CPCR_BAAS)
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_ADV_Port_Selection EXMC_SMC ADV Port Selection
 * @{
 */
#define EXMC_SMC_ADV_PORT_DISABLE               (0UL)
#define EXMC_SMC_ADV_PORT_ENABLE                (SMC_CPCR_ADVS)
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_BLS_Synchronization_Selection EXMC_SMC BLS Synchronization Selection
 * @{
 */
#define EXMC_SMC_BLS_SYNC_CS                    (0UL)
#define EXMC_SMC_BLS_SYNC_WE                    (SMC_CPCR_BLSS)
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Command EXMC_SMC Command
 * @{
 */
#define EXMC_SMC_CMD_MDREGCONFIG                (SMC_CMDR_CMD_0)    /*!< Command: MdRetConfig */
#define EXMC_SMC_CMD_UPDATEREGS                 (SMC_CMDR_CMD_1)    /*!< Command: UpdateRegs */
#define EXMC_SMC_CMD_MDREGCONFIG_AND_UPDATEREGS (SMC_CMDR_CMD)      /*!< Command: MdRetConfig & UpdateRegs */
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_CRE_Polarity EXMC_SMC CRE Polarity
 * @{
 */
#define EXMC_SMC_CRE_POLARITY_LOW               (0UL)           /*!< CRE is LOW */
#define EXMC_SMC_CRE_POLARITY_HIGH              (SMC_CMDR_CRES) /*!< CRE is HIGH when ModeReg write occurs */
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Status EXMC_SMC Status
 * @{
 */
#define EXMC_SMC_READY                          (0UL)               /*!< SMC is ready */
#define EXMC_SMC_LOWPOWER                       (SMC_STSR_STATUS)   /*!< SMC is low power */
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Sample_Clock EXMC_SMC Sample Clock
 * @{
 */
#define EXMC_SMC_SAMPLE_CLK_INTERNCLK           (0UL)               /*!< Internal EXCLK */
#define EXMC_SMC_SAMPLE_CLK_INTERNCLK_INVT      (SMC_BACR_CKSEL_0)  /*!< Invert internal EXCLK */
#define EXMC_SMC_SAMPLE_CLK_EXTCLK              (SMC_BACR_CKSEL_1)  /*!< External clock from EXMC_CLK port */
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Mask_Address EXMC_SMC Mask Address
 * @{
 */
#define EXMC_SMC_ADDR_MASK_16MB                 (0xFFUL)
#define EXMC_SMC_ADDR_MASK_32MB                 (0xFEUL)
#define EXMC_SMC_ADDR_MASK_64MB                 (0xFCUL)
#define EXMC_SMC_ADDR_MASK_128MB                (0xF8UL)
#define EXMC_SMC_ADDR_MASK_256MB                (0xF0UL)
#define EXMC_SMC_ADDR_MASK_512MB                (0xE0UL)
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Address_Space EXMC_SMC Address Space
 * @{
 */
#define EXMC_SMC_ADDR_MIN                       (0x60000000UL)
#define EXMC_SMC_ADDR_MAX                       (0x7FFFFFFFUL)
/**
 * @}
 */

/**
  * @brief  SMC device memory address shifting.
  * @param  [in] mem_base_addr          SMC base address
  * @param  [in] mem_width              SMC memory width
  * @param  [in] addr                   SMC device memory address
  * @retval SMC device shifted address value
  */
#define SMC_ADDR_SHIFT(mem_base_addr, mem_width, addr)                  \
(    ((EXMC_SMC_MEMORY_WIDTH_16BIT == (mem_width))? (((mem_base_addr) + ((addr) << 1U))) : \
                                (((mem_base_addr) + ((addr) << 2U)))))

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
 * @addtogroup EXMC_SMC_Global_Functions
 * @{
 */

/**
 * @brief  SMC entry low power state
 * @param  None
 * @retval None
 */
__STATIC_INLINE void EXMC_SMC_EntryLowPower(void)
{
    WRITE_REG32(CM_SMC->STCR0, SMC_STCR0_LPWIR);
}

/**
 * @brief  SMC exit low power state
 * @param  None
 * @retval None
 */
__STATIC_INLINE void EXMC_SMC_ExitLowPower(void)
{
    WRITE_REG32(CM_SMC->STCR1, SMC_STCR1_LPWOR);
}

/**
 * @brief  Get SMC status
 * @param  None
 * @retval Returned value can be one of the macros group @ref EXMC_SMC_Status
 *           - EXMC_SMC_READY: SMC is ready
 *           - EXMC_SMC_LOWPOWER: SMC is low power
 */
__STATIC_INLINE uint32_t EXMC_SMC_GetStatus(void)
{
    return READ_REG32_BIT(CM_SMC->STSR, SMC_STSR_STATUS);
}

/* Initialization and configuration EXMC_SMC functions */
int32_t EXMC_SMC_StructInit(stc_exmc_smc_init_t *pstcSmcInit);
int32_t EXMC_SMC_Init(uint32_t u32Chip, const stc_exmc_smc_init_t *pstcSmcInit);
int32_t EXMC_SMC_DeInit(void);

void EXMC_SMC_Cmd(en_functional_state_t enNewState);
void EXMC_SMC_PinMuxCmd(en_functional_state_t enNewState);
void EXMC_SMC_SetSampleClock(uint32_t u32SampleClock);
void EXMC_SMC_SetRefreshPeriod(uint8_t u8PeriodVal);

void EXMC_SMC_SetCommand(uint32_t u32Chip, uint32_t u32Cmd, uint32_t u32CrePolarity, uint32_t u32Addr);
uint32_t EXMC_SMC_GetChipStartAddr(uint32_t u32Chip);
uint32_t EXMC_SMC_GetChipEndAddr(uint32_t u32Chip);
int32_t EXMC_SMC_GetChipConfig(uint32_t u32Chip, stc_exmc_smc_chip_config_t *pstcChipConfig);
int32_t EXMC_SMC_GetTimingConfig(uint32_t u32Chip, stc_exmc_smc_timing_config_t *pstcTimingConfig);

/**
 * @}
 */

#endif /* LL_SMC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_SMC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
