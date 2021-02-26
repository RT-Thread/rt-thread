/**
 *******************************************************************************
 * @file  hc32f4a0_nfc.h
 * @brief This file contains all the functions prototypes of the EXMC NFC
 *        (External Memory Controller: NAND Flash Controller) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Hongjh          First version
   2020-07-14       Hongjh          1. Merge API from EXMC_NFC_Enable/Disable to EXMC_NFC_Cmd
                                    2. Merge API from EXMC_NFC_Enable/DisableEcc
                                       to EXMC_NFC_EccCmd
                                    3. Merge API from EXMC_NFC_Enable/DisableWriteProtect
                                       to EXMC_NFC_WriteProtectCmd
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
#ifndef __HC32F4A0_NFC_H__
#define __HC32F4A0_NFC_H__

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
 * @addtogroup DDL_EXMC_NFC
 * @{
 */

#if (DDL_NFC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EXMC_NFC_Global_Types NAND Flash Controller Global Types
 * @{
 */

/**
 * @brief  EXMC SMC Chip Configuration Structure definition
 */
typedef struct
{
    uint32_t    u32CapacitySize;            /*!< Defines the capacity size.
                                                 This parameter can be a value of @ref EXMC_NFC_BANK_Memory_Capacity. */

    uint32_t    u32MemWidth;                /*!< Defines the memory width.
                                                 This parameter can be a value of @ref EXMC_NFC_Memory_Width. */

    uint32_t    u32BankNum;                 /*!< Defines the bank number.
                                                 This parameter can be a value of @ref EXMC_NFC_Bank_Number */

    uint32_t    u32PageSize;                /*!< Defines the page size.
                                                 This parameter can be a value of @ref EXMC_NFC_Page_Size. */

    uint32_t    u32WrProtect;               /*!< Defines the write protect.
                                                 This parameter can be a value of @ref EXMC_NFC_Write_Protect. */

    uint32_t    u32EccMode;                 /*!< Defines the ECC mode.
                                                 This parameter can be a value of @ref EXMC_NFC_ECC_Mode. */

    uint32_t    u32RowAddrCycle;            /*!< Defines the row address cycle.
                                                 This parameter can be a value of @ref EXMC_NFC_Row_Address_Cycle. */

    uint8_t     u8SpareSizeForUserData;     /*!< Defines the spare column size for user data.
                                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */
}stc_exmc_nfc_base_cfg_t;

/**
 * @brief  EXMC NFC Timing Register 0 Configuration Structure definition
 */
typedef struct
{
    uint32_t    u32TS;      /*!< Defines the CLE/ALE/CE setup time in memory clock cycles(tALS/tCS/tCLS).
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */

    uint32_t    u32TWP;     /*!< Defines the WE# pulse width time in memory clock cycles(tWP).
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */

    uint32_t    u32TRP;     /*!< Defines the RE# pulse width time in memory clock cycles(tRP).
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */

    uint32_t    u32TH;      /*!< Defines the CLE/ALE/CE hold time in memory clock cycles(tALH/tCH/tCLH).
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */
} stc_exmc_nfc_cfg_timing_reg0_t;

/**
 * @brief  EXMC NFC Timing Register 1 Configuration Structure definition
 */
typedef struct
{
    uint32_t    u32TWH;     /*!< Defines the WE# pulse width HIGH time in memory clock cycles(tWH).
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */

    uint32_t    u32TRH;     /*!< Defines the RE# HIGH hold time in memory clock cycles(tREH).
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */

    uint32_t    u32TRR;     /*!< Defines the Ready to RE# LOW time in memory clock cycles(tRR).
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */

    uint32_t    u32TWB;     /*!< Defines the WE# HIGH to busy time in memory clock cycles(tWB).
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */
} stc_exmc_nfc_cfg_timing_reg1_t;

/**
 * @brief  EXMC NFC Timing Register 2 Configuration Structure definition
 */
typedef struct
{
    uint32_t    u32TCCS;    /*!< Defines the command(change read/write column) delay time in memory clock cycles.
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */

    uint32_t    u32TWTR;    /*!< Defines the WE# HIGH to RE# LOW time in memory clock cycles(tWHR).
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */

    uint32_t    u32TRTW;    /*!< Defines the RE# HIGH to WE# LOW time in memory clock cycles(tRHW).
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */

    uint32_t    u32TADL;    /*!< Defines the Address to Data Loading time in memory clock cycles(tADL).
                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */
} stc_exmc_nfc_cfg_timing_reg2_t;

/**
 * @brief  EXMC NFC Initialization Structure definition
 */
typedef struct
{
    uint32_t                        u32OpenPage;    /*!< NFC memory open-page selection.
                                                         This structure details refer @ref EXMC_NFC_Open_Page. */

    stc_exmc_nfc_base_cfg_t         stcBaseCfg;     /*!< NFC memory base configure.
                                                         This structure details refer @ref stc_exmc_nfc_base_cfg_t. */

    stc_exmc_nfc_cfg_timing_reg0_t  stcTimingReg0;  /*!< NFC memory timing configure 0.
                                                         This structure details refer @ref stc_exmc_nfc_cfg_timing_reg0_t. */

    stc_exmc_nfc_cfg_timing_reg1_t  stcTimingReg1;  /*!< NFC memory timing configure 1.
                                                         This structure details refer @ref stc_exmc_nfc_cfg_timing_reg1_t. */

    stc_exmc_nfc_cfg_timing_reg2_t  stcTimingReg2;  /*!< NFC memory timing configure 2.
                                                         This structure details refer @ref stc_exmc_nfc_cfg_timing_reg2_t. */
} stc_exmc_nfc_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EXMC_NFC_Global_Macros NAND Flash Controller Global Macros
 * @{
 */

/**
 * @defgroup EXMC_NFC_Bank EXMC NFC Bank
 * @{
 */
#define EXMC_NFC_BANK_0                         (0UL)     /*!< Bank 0 */
#define EXMC_NFC_BANK_1                         (1UL)     /*!< Bank 1 */
#define EXMC_NFC_BANK_2                         (2UL)     /*!< Bank 2 */
#define EXMC_NFC_BANK_3                         (3UL)     /*!< Bank 3 */
#define EXMC_NFC_BANK_4                         (4UL)     /*!< Bank 4 */
#define EXMC_NFC_BANK_5                         (5UL)     /*!< Bank 5 */
#define EXMC_NFC_BANK_6                         (6UL)     /*!< Bank 6 */
#define EXMC_NFC_BANK_7                         (7UL)     /*!< Bank 7 */
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Memory_Command EXMC NFC Memory Command
 * @{
 */
#define EXMC_NFC_CMD_READ_1ST                           (0x00UL)
#define EXMC_NFC_CMD_READ_2ND                           (0xE0UL)

#define EXMC_NFC_CMD_COPYBACK_READ_1ST                  (0x00UL)
#define EXMC_NFC_CMD_COPYBACK_READ_2ND                  (0x35UL)

#define EXMC_NFC_CMD_CHANGE_RD_COL_1ST                  (0x05UL)
#define EXMC_NFC_CMD_CHANGE_RD_COL_2ND                  (0xE0UL)

#define EXMC_NFC_CMD_CHANGE_RD_COL_ENHANCED_1ST         (0x06UL)
#define EXMC_NFC_CMD_CHANGE_RD_COL_ENHANCED_2ND         (0xE0UL)

#define EXMC_NFC_CMD_READ_CACHE_RANDOM_1ST              (0x00UL)
#define EXMC_NFC_CMD_READ_CACHE_RANDOM_2ND              (0x31UL)

#define EXMC_NFC_CMD_CALCULATE_ECC                      (0x23UL)

#define EXMC_NFC_CMD_READ_CACHE_SEQ                     (0x31UL)

#define EXMC_NFC_CMD_READ_CACHE_END                     (0x3FUL)

#define EXMC_NFC_CMD_BLK_ERASE_1ST                      (0x60UL)
#define EXMC_NFC_CMD_BLK_ERASE_2ND                      (0xD0UL)

#define EXMC_NFC_CMD_BLK_ERASE_INTERLEAVED_1ST          (0x60UL)
#define EXMC_NFC_CMD_BLK_ERASE_INTERLEAVED_2ND          (0xD1UL)

#define EXMC_NFC_CMD_READ_STATUS                        (0x70UL)

#define EXMC_NFC_CMD_READ_STATUS_ENHANCED               (0x78UL)

#define EXMC_NFC_CMD_PAGE_PROGRAM_1ST                   (0x80UL)
#define EXMC_NFC_CMD_PAGE_PROGRAM_2ND                   (0x10UL)

#define EXMC_NFC_CMD_PAGE_PROGRAM_INTERLEAVED_1ST       (0x80UL)
#define EXMC_NFC_CMD_PAGE_PROGRAM_INTERLEAVED_2ND       (0x11UL)

#define EXMC_NFC_CMD_PAGE_CACHE_PROGRAM_1ST             (0x80UL)
#define EXMC_NFC_CMD_PAGE_CACHE_PROGRAM_2ND             (0x15UL)

#define EXMC_NFC_CMD_COPYBACK_PROGRAM_1ST               (0x85UL)
#define EXMC_NFC_CMD_COPYBACK_PROGRAM_2ND               (0x10UL)

#define EXMC_NFC_CMD_COPYBACK_PROGRAM_INTERLEAVED_1ST   (0x85UL)
#define EXMC_NFC_CMD_COPYBACK_PROGRAM_INTERLEAVED_2ND   (0x11UL)

#define EXMC_NFC_CMD_CHANGE_WR_COL                      (0x85UL)

#define EXMC_NFC_CMD_CHANGE_ROW_ADDRESS                 (0x85UL)

#define EXMC_NFC_CMD_READ_ID                            (0x90UL)

#define EXMC_NFC_CMD_READ_PARAMETER_PAGE                (0xECUL)

#define EXMC_NFC_CMD_READ_UNIQUE_ID                     (0xEDUL)

#define EXMC_NFC_CMD_GET_FEATURES                       (0xEEUL)

#define EXMC_NFC_CMD_SET_FEATURES                       (0xEFUL)

#define EXMC_NFC_CMD_RESET_LUN                          (0xFAUL)

#define EXMC_NFC_CMD_ASYNCHRONOUS_RESSET                (0xFCUL)

#define EXMC_NFC_CMD_DESELECT_CHIP                      (0xFEUL)

#define EXMC_NFC_CMD_RESET                              (0xFFUL)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Page_Size EXMC NFC Page Size
 * @{
 */
#define EXMC_NFC_PAGE_SIZE_2KBYTES              (NFC_BACR_PAGE_0)
#define EXMC_NFC_PAGE_SIZE_4KBYTES              (NFC_BACR_PAGE_1)
#define EXMC_NFC_PAGE_SIZE_8KBYTES              (NFC_BACR_PAGE)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_BANK_Memory_Capacity EXMC NFC BANK Memory Capacity
 * @{
 */
#define EXMC_NFC_BANK_CAPACITY_512MBIT          (NFC_BACR_SIZE_1 | NFC_BACR_SIZE_0)
#define EXMC_NFC_BANK_CAPACITY_1GBIT            (NFC_BACR_SIZE_2)
#define EXMC_NFC_BANK_CAPACITY_2GBIT            (NFC_BACR_SIZE_2 | NFC_BACR_SIZE_0)
#define EXMC_NFC_BANK_CAPACITY_4GBIT            (NFC_BACR_SIZE_2 | NFC_BACR_SIZE_1)
#define EXMC_NFC_BANK_CAPACITY_8GBIT            (NFC_BACR_SIZE)
#define EXMC_NFC_BANK_CAPACITY_16GBIT           (0UL)
#define EXMC_NFC_BANK_CAPACITY_32GBIT           (NFC_BACR_SIZE_0)
#define EXMC_NFC_BANK_CAPACITY_64GBIT           (NFC_BACR_SIZE_1)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Memory_Width EXMC NFC Memory Width
 * @{
 */
#define EXMC_NFC_MEMORY_WIDTH_8BIT              (0UL)
#define EXMC_NFC_MEMORY_WIDTH_16BIT             (NFC_BACR_B16BIT)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Bank_Number EXMC NFC Bank Number
 * @{
 */
#define EXMC_NFC_1_BANK                         (0UL)
#define EXMC_NFC_2_BANKS                        (NFC_BACR_BANK_0)
#define EXMC_NFC_4_BANKS                        (NFC_BACR_BANK_1)
#define EXMC_NFC_8_BANKS                        (NFC_BACR_BANK)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Open_Page EXMC NFC Open Page
 * @{
 */
#define EXMC_NFC_OPEN_PAGE_DISABLE              (0UL)
#define EXMC_NFC_OPEN_PAGE_ENABLE               (PERIC_NFC_SYCTLREG_OPO)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Write_Protect EXMC NFC Write Protect
 * @{
 */
#define EXMC_NFC_WR_PROTECT_ENABLE              (0UL)
#define EXMC_NFC_WR_PROTECT_DISABLE             (NFC_BACR_WP)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_ECC_Mode EXMC NFC ECC Mode
 * @{
 */
#define EXMC_NFC_ECC_1BIT                       (0UL)
#define EXMC_NFC_ECC_4BITS                      (NFC_BACR_ECCM_0)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Row_Address_Cycle EXMC NFC Row Address Cycle
 * @{
 */
#define EXMC_NFC_2_ROW_ADDRESS_CYCLES           (0UL)
#define EXMC_NFC_3_ROW_ADDRESS_CYCLES           (NFC_BACR_RAC)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Interrupt EXMC NFC Interrupt
 * @{
 */
#define EXMC_NFC_INT_ECC_UNCORRECTABLE_ERROR    (NFC_IENR_ECCEUEN)
#define EXMC_NFC_INT_ECC_CORRECTABLE_ERROR      (NFC_IENR_ECCECEN)
#define EXMC_NFC_INT_ECC_CALC_COMPLETION        (NFC_IENR_ECCCEN)
#define EXMC_NFC_INT_ECC_ERROR                  (NFC_IENR_ECCEEN)
#define EXMC_NFC_INT_RB_BANK0                   (NFC_IENR_RBEN_0)
#define EXMC_NFC_INT_RB_BANK1                   (NFC_IENR_RBEN_1)
#define EXMC_NFC_INT_RB_BANK2                   (NFC_IENR_RBEN_2)
#define EXMC_NFC_INT_RB_BANK3                   (NFC_IENR_RBEN_3)
#define EXMC_NFC_INT_RB_BANK4                   (NFC_IENR_RBEN_4)
#define EXMC_NFC_INT_RB_BANK5                   (NFC_IENR_RBEN_5)
#define EXMC_NFC_INT_RB_BANK6                   (NFC_IENR_RBEN_6)
#define EXMC_NFC_INT_RB_BANK7                   (NFC_IENR_RBEN_7)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Flag EXMC NFC Flag
 * @{
 */
#define EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERROR   (NFC_ISTR_ECCEUST)
#define EXMC_NFC_FLAG_ECC_CORRECTABLE_ERROR     (NFC_ISTR_ECCECST)
#define EXMC_NFC_FLAG_ECC_CALC_COMPLETION       (NFC_ISTR_ECCCST)
#define EXMC_NFC_FLAG_ECC_ERROR                 (NFC_ISTR_ECCEST)
#define EXMC_NFC_FLAG_RB_BANK0                  (NFC_ISTR_RBST_0)
#define EXMC_NFC_FLAG_RB_BANK1                  (NFC_ISTR_RBST_1)
#define EXMC_NFC_FLAG_RB_BANK2                  (NFC_ISTR_RBST_2)
#define EXMC_NFC_FLAG_RB_BANK3                  (NFC_ISTR_RBST_3)
#define EXMC_NFC_FLAG_RB_BANK4                  (NFC_ISTR_RBST_4)
#define EXMC_NFC_FLAG_RB_BANK5                  (NFC_ISTR_RBST_5)
#define EXMC_NFC_FLAG_RB_BANK6                  (NFC_ISTR_RBST_6)
#define EXMC_NFC_FLAG_RB_BANK7                  (NFC_ISTR_RBST_7)
#define EXMC_NFC_FLAG_ECC_CALCULATING           (NFC_ISTR_RESV)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_ECC_Calculate_Bytes EXMC NFC ECC Calculate Bytes
 * @{
 */
#define EXMC_NFC_ECC_CALCULATE_BLOCK_BYTES      (512UL)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_ECC_Value_Bytes EXMC NFC ECC Value Bytes
 * @{
 */
#define EXMC_NFC_1BIT_ECC_VALUE_BYTES           (0x03UL)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_1Bit_ECC_Result EXMC NFC 1Bit ECC Result
 * @{
 */
#define EXMC_NFC_1BIT_ECC_SINGLE_BIT_ERR        (NFC_ECCR_SE)
#define EXMC_NFC_1BIT_ECC_MULTIPLE_BITS_ERR     (NFC_ECCR_ME)
#define EXMC_NFC_1BIT_ECC_ERR_LOCATION          (NFC_ECCR_ERRLOC)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_1Bit_ECC_Error_Location_Position EXMC NFC 1Bit ECC Error Location Position
 * @{
 */
#define EXMC_NFC_1BIT_ECC_ERR_BIT_POS           (NFC_ECCR_ERRLOC_POS)
#define EXMC_NFC_1BIT_ECC_ERR_BYTE_POS          (NFC_ECCR_ERRLOC_POS + 3UL)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_ECC_Section EXMC NFC ECC Section
 * @{
 */
#define EXMC_NFC_ECC_SECTION0                   (0UL)
#define EXMC_NFC_ECC_SECTION1                   (1UL)
#define EXMC_NFC_ECC_SECTION2                   (2UL)
#define EXMC_NFC_ECC_SECTION3                   (3UL)
#define EXMC_NFC_ECC_SECTION4                   (4UL)
#define EXMC_NFC_ECC_SECTION5                   (5UL)
#define EXMC_NFC_ECC_SECTION6                   (6UL)
#define EXMC_NFC_ECC_SECTION7                   (7UL)
#define EXMC_NFC_ECC_SECTION8                   (8UL)
#define EXMC_NFC_ECC_SECTION9                   (9UL)
#define EXMC_NFC_ECC_SECTION10                  (10UL)
#define EXMC_NFC_ECC_SECTION11                  (11UL)
#define EXMC_NFC_ECC_SECTION12                  (12UL)
#define EXMC_NFC_ECC_SECTION13                  (13UL)
#define EXMC_NFC_ECC_SECTION14                  (14UL)
#define EXMC_NFC_ECC_SECTION15                  (15UL)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Operation_Timeout EXMC NFC Operation Timeout
 * @{
 */
#define EXMC_NFC_MAX_TIMEOUT                    (0xFFFFFFFFUL)
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
 * @addtogroup EXMC_NFC_Global_Functions
 * @{
 */

/**
 * @brief  Set EXMC NFC command register value.
 * @param  [in] u32Val                      The combination value of command and arguments.
 * @retval None
 */
__STATIC_INLINE void EXMC_NFC_WriteCmdReg(uint32_t u32Val)
{
    WRITE_REG32(M4_NFC->CMDR, u32Val);
}

/**
 * @brief  Set EXMC NFC Index register value.
 * @param  [in] u32Val                      The value of NFC_IDXR0.
 *         This parameter can be a value between Min_Data = 0 and Max_Data = 0xFFFFFFFF
 * @retval None
 */
__STATIC_INLINE void EXMC_NFC_WriteIDXR0(uint32_t u32Val)
{
    WRITE_REG32(M4_NFC->IDXR0, u32Val);
}

/**
 * @brief  Set EXMC NFC Index register value.
 * @param  [in] u32Val                      The value of NFC_IDXR1.
 *         This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF
 * @retval None
 */
__STATIC_INLINE void EXMC_NFC_WriteIDXR1(uint32_t u32Val)
{
    WRITE_REG32(M4_NFC->IDXR1, u32Val);
}

/**
 * @brief  De-select NFC bank.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void EXMC_NFC_DeselectChip(void)
{
    WRITE_REG32(M4_NFC->CMDR, EXMC_NFC_CMD_DESELECT_CHIP);
}

/**
 * @brief  Get the 4BIT ECC error section.
 * @param  None
 * @retval The register value
 */
__STATIC_INLINE uint32_t EXMC_NFC_GetEcc4BitsErrSection(void)
{
    return READ_REG32(M4_NFC->ECC_STAT);
}

/* Initialization and configuration EXMC NFC functions */
en_result_t EXMC_NFC_Init(const stc_exmc_nfc_init_t *pstcInit);
void EXMC_NFC_DeInit(void);
en_result_t EXMC_NFC_StructInit(stc_exmc_nfc_init_t *pstcInit);
void EXMC_NFC_Cmd(en_functional_state_t enNewState);
void EXMC_NFC_EccCmd(en_functional_state_t enNewState);
void EXMC_NFC_WriteProtectCmd(en_functional_state_t enNewState);
void EXMC_NFC_IntCmd(uint16_t u16IntSource, en_functional_state_t enNewState);
en_flag_status_t EXMC_NFC_GetStatus(uint32_t u32Flag);
void EXMC_NFC_ClearStatus(uint32_t u32Flag);
en_flag_status_t EXMC_NFC_GetIntResultStatus(uint32_t u32Flag);
uint32_t EXMC_NFC_GetEcc1BitResult(uint32_t u32Section);
en_result_t EXMC_NFC_GetSyndrome(uint32_t u32Section,
                                        uint16_t au16Synd[],
                                        uint8_t u8Length);
void EXMC_NFC_SetSpareAreaSize(uint8_t u8SpareSizeForUserData);
void EXMC_NFC_SetEccMode(uint32_t u32EccMode);

/* EXMC NFC command functions */
uint32_t EXMC_NFC_ReadStatus(uint32_t u32Bank);
uint32_t EXMC_NFC_ReadStatusEnhanced(uint32_t u32Bank,
                                            uint32_t u32RowAddress);
en_result_t EXMC_NFC_Reset(uint32_t u32Bank, uint32_t u32Timeout);
en_result_t EXMC_NFC_AsyncReset(uint32_t u32Bank, uint32_t u32Timeout);
en_result_t EXMC_NFC_ResetLun(uint32_t u32Bank,
                                    uint32_t u32RowAddress,
                                    uint32_t u32Timeout);
en_result_t EXMC_NFC_ReadId(uint32_t u32Bank,
                                uint32_t u32IdAddr,
                                uint8_t au8DevId[],
                                uint32_t u32NumBytes,
                                uint32_t u32Timeout);
en_result_t EXMC_NFC_ReadUniqueId(uint32_t u32Bank,
                                        uint32_t u32IdAddr,
                                        uint32_t au32UniqueId[],
                                        uint8_t u8NumWords,
                                        uint32_t u32Timeout);
en_result_t EXMC_NFC_ReadParameterPage(uint32_t u32Bank,
                                        uint32_t au32Data[],
                                        uint16_t u16NumWords,
                                        uint32_t u32Timeout);
en_result_t EXMC_NFC_SetFeature(uint32_t u32Bank,
                                    uint8_t u8FeatrueAddr,
                                    const uint32_t au32Data[],
                                    uint8_t u8NumWords,
                                    uint32_t u32Timeout);
en_result_t EXMC_NFC_GetFeature(uint32_t u32Bank,
                                    uint8_t u8FeatrueAddr,
                                    uint32_t au32Data[],
                                    uint8_t u8NumWords,
                                    uint32_t u32Timeout);
en_result_t EXMC_NFC_EraseBlock(uint32_t u32Bank,
                                    uint32_t u32RowAddress,
                                    uint32_t u32Timeout);
en_result_t EXMC_NFC_ReadPageMeta(uint32_t u32Bank,
                                    uint32_t u32Page,
                                    uint8_t *pu8Data,
                                    uint32_t u32NumBytes,
                                    uint32_t u32Timeout);
en_result_t EXMC_NFC_WritePageMeta(uint32_t u32Bank,
                                    uint32_t u32Page,
                                    const uint8_t *pu8Data,
                                    uint32_t u32NumBytes,
                                    uint32_t u32Timeout);
en_result_t EXMC_NFC_ReadPageHwEcc(uint32_t u32Bank,
                                    uint32_t u32Page,
                                    uint8_t *pu8Data,
                                    uint32_t u32NumBytes,
                                    uint32_t u32Timeout);
en_result_t EXMC_NFC_WritePageHwEcc(uint32_t u32Bank,
                                    uint32_t u32Page,
                                    const uint8_t *pu8Data,
                                    uint32_t u32NumBytes,
                                    uint32_t u32Timeout);
/**
 * @}
 */

#endif /* DDL_NFC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_NFC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
