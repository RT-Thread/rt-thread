/**
 *******************************************************************************
 * @file  hc32f4a0_nfc.c
 * @brief This file provides firmware functions to manage the EXMC NFC
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
   2020-08-25       Hongjh          Modify the pointer type cast
   2020-10-12       Hongjh          The function EXMC_NFC_ReadId add timeout
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_nfc.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_EXMC_NFC EXMC_NFC
 * @brief NAND Flash Controller Driver Library
 * @{
 */

#if (DDL_NFC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EXMC_NFC_Local_Macros NAND Flash Controller Local Macros
 * @{
 */

/**
 * @defgroup EXMC_SMC_Check_Parameters_Validity EXMC SMC Check Parameters Validity
 * @{
 */

#define IS_EXMC_NFC_BANK(x)                                                    \
(   (EXMC_NFC_BANK_0 == (x))                    ||                             \
    (EXMC_NFC_BANK_1 == (x))                    ||                             \
    (EXMC_NFC_BANK_2 == (x))                    ||                             \
    (EXMC_NFC_BANK_3 == (x))                    ||                             \
    (EXMC_NFC_BANK_4 == (x))                    ||                             \
    (EXMC_NFC_BANK_5 == (x))                    ||                             \
    (EXMC_NFC_BANK_6 == (x))                    ||                             \
    (EXMC_NFC_BANK_7 == (x)))

#define IS_EXMC_NFC_MEM_WIDTH(x)                                               \
(   (EXMC_NFC_MEMORY_WIDTH_8BIT == (x))         ||                             \
    (EXMC_NFC_MEMORY_WIDTH_16BIT == (x)))

#define IS_EXMC_NFC_BANK_CAPACITY(x)                                           \
(   (EXMC_NFC_BANK_CAPACITY_512MBIT == (x))     ||                             \
    (EXMC_NFC_BANK_CAPACITY_1GBIT == (x))       ||                             \
    (EXMC_NFC_BANK_CAPACITY_2GBIT == (x))       ||                             \
    (EXMC_NFC_BANK_CAPACITY_4GBIT == (x))       ||                             \
    (EXMC_NFC_BANK_CAPACITY_8GBIT == (x))       ||                             \
    (EXMC_NFC_BANK_CAPACITY_16GBIT == (x))      ||                             \
    (EXMC_NFC_BANK_CAPACITY_32GBIT == (x))      ||                             \
    (EXMC_NFC_BANK_CAPACITY_64GBIT == (x)))

#define IS_EXMC_NFC_PAGE_SIZE(x)                                               \
(   (EXMC_NFC_PAGE_SIZE_2KBYTES == (x))         ||                             \
    (EXMC_NFC_PAGE_SIZE_4KBYTES == (x))         ||                             \
    (EXMC_NFC_PAGE_SIZE_8KBYTES == (x)))

#define IS_EXMC_NFC_BANK_NUM(x)                                                \
(   (EXMC_NFC_1_BANK == (x))                    ||                             \
    (EXMC_NFC_2_BANKS == (x))                   ||                             \
    (EXMC_NFC_4_BANKS == (x))                   ||                             \
    (EXMC_NFC_8_BANKS == (x)))

#define IS_EXMC_NFC_WR_PROTECT(x)                                              \
(   (EXMC_NFC_WR_PROTECT_ENABLE == (x))         ||                             \
    (EXMC_NFC_WR_PROTECT_DISABLE == (x)))

#define IS_EXMC_NFC_ECC_MODE(x)                                                \
(   (EXMC_NFC_ECC_1BIT == (x))                  ||                             \
    (EXMC_NFC_ECC_4BITS == (x)))

#define IS_EXMC_NFC_ROW_ADDRESS_CYCLES(x)                                      \
(   (EXMC_NFC_2_ROW_ADDRESS_CYCLES == (x))      ||                             \
    (EXMC_NFC_3_ROW_ADDRESS_CYCLES == (x)))

#define IS_EXMC_NFC_SECTION(x)                  ((x) <= EXMC_NFC_ECC_SECTION15)

#define IS_EXMC_NFC_INT(x)                                                     \
(   (0UL != (x))                                 &&                            \
    (0UL == ((x) & (~EXMC_NFC_INT_MASK))))


#define IS_EXMC_NFC_FLAG(x)                                                    \
(   (0UL != (x))                                 &&                            \
    (0UL == ((x) & (~EXMC_NFC_FLAG_MASK))))

#define IS_EXMC_NFC_COLUMN(x)                   ((x) <= NFC_COLUMN_MAX)

#define IS_EXMC_NFC_PAGE(page, capacity_index)  ((page) <= NFC_PAGE_MAX((capacity_index)))

#define IS_EXMC_NFC_TIMING_TS(x)                ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TWP(x)               ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TRP(x)               ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TH(x)                ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TWH(x)               ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TRH(x)               ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TRR(x)               ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TWB(x)               ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TCCS(x)              ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TWTR(x)              ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TRTW(x)              ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TADL(x)              ((x) <= 0xFFUL)
/**
 * @}
 */

/**
 * @defgroup NFC flag mask
 * @{
 */
#define EXMC_NFC_INT_MASK                                                      \
(   EXMC_NFC_INT_RB_BANK0                       |                              \
    EXMC_NFC_INT_RB_BANK1                       |                              \
    EXMC_NFC_INT_RB_BANK2                       |                              \
    EXMC_NFC_INT_RB_BANK3                       |                              \
    EXMC_NFC_INT_RB_BANK4                       |                              \
    EXMC_NFC_INT_RB_BANK5                       |                              \
    EXMC_NFC_INT_RB_BANK6                       |                              \
    EXMC_NFC_INT_RB_BANK7                       |                              \
    EXMC_NFC_INT_ECC_ERROR                      |                              \
    EXMC_NFC_INT_ECC_CALC_COMPLETION            |                              \
    EXMC_NFC_INT_ECC_CORRECTABLE_ERROR          |                              \
    EXMC_NFC_INT_ECC_UNCORRECTABLE_ERROR)
/**
 * @}
 */

/**
 * @defgroup NFC flag mask
 * @{
 */
#define EXMC_NFC_FLAG_MASK                                                     \
(   EXMC_NFC_FLAG_RB_BANK0                      |                              \
    EXMC_NFC_FLAG_RB_BANK1                      |                              \
    EXMC_NFC_FLAG_RB_BANK2                      |                              \
    EXMC_NFC_FLAG_RB_BANK3                      |                              \
    EXMC_NFC_FLAG_RB_BANK4                      |                              \
    EXMC_NFC_FLAG_RB_BANK5                      |                              \
    EXMC_NFC_FLAG_RB_BANK6                      |                              \
    EXMC_NFC_FLAG_RB_BANK7                      |                              \
    EXMC_NFC_FLAG_ECC_ERROR                     |                              \
    EXMC_NFC_FLAG_ECC_CALCULATING               |                              \
    EXMC_NFC_FLAG_ECC_CALC_COMPLETION           |                              \
    EXMC_NFC_FLAG_ECC_CORRECTABLE_ERROR         |                              \
    EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERROR)
/**
 * @}
 */

/**
 * @defgroup NFC_Memory_Capacity_Index NFC Memory Capacity Index
 * @{
 */
#define NFC_CAPACITY_INDEX_512MBIT              (0UL)
#define NFC_CAPACITY_INDEX_1GBIT                (1UL)
#define NFC_CAPACITY_INDEX_2GBIT                (2UL)
#define NFC_CAPACITY_INDEX_4GBIT                (3UL)
#define NFC_CAPACITY_INDEX_8GBIT                (4UL)
#define NFC_CAPACITY_INDEX_16GBIT               (5UL)
#define NFC_CAPACITY_INDEX_32GBIT               (6UL)
#define NFC_CAPACITY_INDEX_64GBIT               (7UL)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Command_Regster_Value EXMC NFC Command Regster Value
 * @{
 */
/*!< Command value */
#define NFC_CMD_VALUE(arg, bank, cmd)           ((arg) | ((bank) << 8UL) | (cmd))

/*!< Command: Read status */
#define NFC_ADDR_VALUE(bank, addr)              (0x40000000UL | ((bank) << 8UL) | (addr))

/*!< Command: Read status */
#define CMD_RESET(bank)                         (NFC_CMD_VALUE(0UL, (bank), EXMC_NFC_CMD_RESET))

/*!< Command: Read status */
#define CMD_ASYNC_RESET(bank)                   (NFC_CMD_VALUE(0x82000000UL, (bank), EXMC_NFC_CMD_ASYNCHRONOUS_RESSET))

/*!< Command: Read status */
#define CMD_RESET_LUN(bank)                     (NFC_CMD_VALUE(0x82000000UL, (bank), EXMC_NFC_CMD_RESET_LUN))

/*!< Command: Read status */
#define CMD_READ_STATUS(bank)                   (NFC_CMD_VALUE(0x81000000UL, (bank), EXMC_NFC_CMD_READ_STATUS))

/*!< Command: Read status */
#define CMD_READ_STATUS_ENHANCED(bank)          (NFC_CMD_VALUE(0x80000000UL, (bank), EXMC_NFC_CMD_READ_STATUS_ENHANCED))

/*!< Command: Read ID */
#define CMD_READ_ID(bank)                       (NFC_CMD_VALUE(0x81000000UL, (bank), EXMC_NFC_CMD_READ_ID))
#define CMD_READ_ID_ADDR(bank, addr)            (NFC_ADDR_VALUE((bank), (addr)))

/*!< Command: Read unique ID */
#define CMD_READ_UNIQUEID(bank)                 (NFC_CMD_VALUE(0x83000000UL, (bank), EXMC_NFC_CMD_READ_UNIQUE_ID))
#define CMD_READ_UNIQUEID_ADDR(bank)            (NFC_ADDR_VALUE((bank), 0UL))

/*!< Command: Erase block */
#define CMD_ERASE_BLOCK_1ST_CYCLE(bank)         (NFC_CMD_VALUE(0x81000000UL, (bank), EXMC_NFC_CMD_BLK_ERASE_1ST))
#define CMD_ERASE_BLOCK_2ND_CYCLE(bank)         (NFC_CMD_VALUE(0x81000000UL, (bank), EXMC_NFC_CMD_BLK_ERASE_2ND))

/*!< Command: Read parameter page */
#define CMD_READ_PARAMETER_PAGE(bank)           (NFC_CMD_VALUE(0x83000000UL, (bank), EXMC_NFC_CMD_READ_PARAMETER_PAGE))
#define CMD_READ_PARAMETER_PAGE_ADDR(bank)      (NFC_ADDR_VALUE((bank), 0UL))

/*!< Command: Set feature */
#define CMD_SET_FEATURE(bank)                   (NFC_CMD_VALUE(0x83000000UL, (bank), EXMC_NFC_CMD_SET_FEATURES))
#define CMD_SET_FEATURE_ADDR(bank, addr)        (NFC_ADDR_VALUE((bank), (addr)))

/*!< Command: Get feature */
#define CMD_GET_FEATURE(bank)                   (NFC_CMD_VALUE(0x83000000UL, (bank), EXMC_NFC_CMD_GET_FEATURES))
#define CMD_GET_FEATURE_ADDR(bank, addr)        (NFC_ADDR_VALUE((bank), (addr)))

/*!< Command: Address cycle */
#define CMD_ADDR_1ST_CYCLE(bank, ras)           (NFC_ADDR_VALUE((bank), ((ras) & 0xFFUL)))
#define CMD_ADDR_2ND_CYCLE(bank, ras)           (NFC_ADDR_VALUE((bank), (((ras) & 0xFF00UL) >> 8UL)))
#define CMD_ADDR_3RD_CYCLE(bank, ras)           (NFC_ADDR_VALUE((bank), (((ras) & 0xFF0000UL) >> 16UL)))

/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_IDXR_Bit_Position EXMC NFC IDXR Bit Position
 * @{
 */
#define EXMC_NFC_IDXR_COL_POS                   (0UL)
#define EXMC_NFC_IDXR_2KPAGE_POS                (12UL)
#define EXMC_NFC_IDXR_512MBIT_BANK_POS          (27UL)
/**
 * @}
 */

/*!< NFC BACR regsiter: page field value */
#define NFC_BACR_PAGE_VAL                       ((READ_REG32_BIT(M4_NFC->BACR, NFC_BACR_PAGE) >> NFC_BACR_PAGE_POS))

/*!< NFC Page Size */
#define NFC_PAGE_SIZE                           (1024UL << (NFC_BACR_PAGE_VAL & 0x3UL))

/*!< NFC Spare Size for user data */
#define NFC_SPARE_SIZE_FOR_USER_DATA            ((READ_REG32_BIT(M4_NFC->BACR, NFC_BACR_SCS) >> NFC_BACR_SCS_POS) << 2UL)

/*!< IDX register mask for 64bit */
#define NFC_IDXR_MASK                           (0x1FFFFFFFFFULL)

/*!< NFC_ISTR register RBST bit mask */
#define NFC_FLAG_RB_BANKx_MASK(bank)            (EXMC_NFC_FLAG_RB_BANK0 << (EXMC_NFC_BANK_7 & (bank)))

/*!< IDX register mask for 64bit */
#define NFC_NFC_ISTR_MASK                       (0xFF53UL)

/*!< NFC_DATR for 32bit */
#define NFC_DATR_REG32(x)                       (M4_NFC->DATR_BASE)

/*!< NFC_ID_DATR for 32bit */
#define NFC_ID_REG32(x)                         (*((__IO uint32_t *)((uint32_t)(&(M4_NFC->DATR_BASE)) + 0x8010UL + ((x) << 2UL))))

/*!< NFC_SYND_REG for 32bit */
#define NFC_SYND_REG32(sect, reg)               (*((__IO uint32_t *)((uint32_t)(&(M4_NFC->ECC_SYND0_0)) + (((uint32_t)(sect)) << 4UL) + (((uint32_t)(reg)) << 2UL))))

/*!< NFC_ECCR_REG for 32bit */
#define NFC_ECCR_REG32(sect)                    (*((__IO uint32_t *)((uint32_t)(&(M4_NFC->ECCR0))   + (((uint32_t)(sect)) << 2UL))))

/*!< NFC_SYND_MAX_Length (Unit: half-word ) */
#define NFC_SYND_MAX_LEN                        (8U)

/**
 * @defgroup Parameter_Align Parameter Align
 * @{
 */
#define IS_PARAM_ALIGN_WORD(x)                  (IS_ADDRESS_ALIGN_WORD((x)))
/**
 * @}
 */

/*!< NFC column max */
#define NFC_COLUMN_MAX                          ((1UL << (12UL + ((0x03UL & NFC_BACR_PAGE_VAL) - 1UL))) - 1UL)

/*!< NFC page max for the specified capacity */
#define NFC_PAGE_MAX(capacity_index)            ((1UL << (14UL + capacity_index - ((0x03UL & NFC_BACR_PAGE_VAL) - 1UL))) - 1UL)

/**
 * @brief  Calculate NFC_IDXR register(64bits) value.
 * @param  [in]bank             The specified bank
 *   @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *   @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *   @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *   @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *   @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *   @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *   @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *   @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in]page             The page address
 * @param  [in]col              The column address
 * @param  [in]capacity_index   The number of bank capacity bits
 *   @arg NFC_CAPACITY_INDEX_512MBIT: NFC device bank size:512M bits
 *   @arg NFC_CAPACITY_INDEX_1GBIT: NFC device bank size:1G bits
 *   @arg NFC_CAPACITY_INDEX_2GBIT: NFC device bank size:2G bits
 *   @arg NFC_CAPACITY_INDEX_4GBIT: NFC device bank size:4G bits
 *   @arg NFC_CAPACITY_INDEX_8GBIT: NFC device bank size:8G bits
 *   @arg NFC_CAPACITY_INDEX_16GBIT: NFC device bank size:16G bits
 *   @arg NFC_CAPACITY_INDEX_32BIT: NFC device bank size:32G bits
 *   @arg NFC_CAPACITY_INDEX_64BIT: NFC device bank size:64G bits
 * @retval NFC Index value
 */
#define NFC_IDXR_VAL(bank, page, col, capacity_index)                          \
(   (((uint64_t)(col)) << EXMC_NFC_IDXR_COL_POS)     |                         \
    (((uint64_t)(page)) << (EXMC_NFC_IDXR_2KPAGE_POS + ((0x03UL & NFC_BACR_PAGE_VAL) - 1UL))) | \
    (((uint64_t)(bank)) << (EXMC_NFC_IDXR_512MBIT_BANK_POS + (0x07UL & (capacity_index)))))
/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/**
 * @addtogroup EXMC_NFC_Local_Functions
 * @{
 */

static en_result_t EXMC_NFC_Read(uint32_t u32Bank,
                                    uint32_t u32Page,
                                    uint32_t u32Col,
                                    uint32_t au32Data[],
                                    uint32_t u32NumWords,
                                    en_functional_state_t enEccState,
                                    uint32_t u32Timeout);
static en_result_t EXMC_NFC_Write(uint32_t u32Bank,
                                    uint32_t u32Page,
                                    uint32_t u32Col,
                                    const uint32_t au32Data[],
                                    uint32_t u32NumWords,
                                    en_functional_state_t enEccState,
                                    uint32_t u32Timeout);
static uint32_t EXMC_NFC_GetCapacityIndex(void);
static en_result_t EXMC_NFC_WaitFlagUntilTo(uint32_t u32Flag,
                                                    en_flag_status_t enStatus,
                                                    uint32_t u32Timeout);

/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup EXMC_NFC_Global_Functions NAND Flash Controller Global Functions
 * @{
 */

/**
 * @brief  Initialize EXMC NFC function.
 * @param  [in] pstcInit                Pointer to a @ref stc_exmc_nfc_init_t structure (EXMC NFC function configuration structure).
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t EXMC_NFC_Init(const stc_exmc_nfc_init_t *pstcInit)
{
    uint32_t u32RegVal;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check the pointer pstcInit */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_NFC_BANK_CAPACITY(pstcInit->stcBaseCfg.u32CapacitySize));
        DDL_ASSERT(IS_EXMC_NFC_MEM_WIDTH(pstcInit->stcBaseCfg.u32MemWidth));
        DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(pstcInit->stcBaseCfg.u32BankNum));
        DDL_ASSERT(IS_EXMC_NFC_PAGE_SIZE(pstcInit->stcBaseCfg.u32PageSize));
        DDL_ASSERT(IS_EXMC_NFC_WR_PROTECT(pstcInit->stcBaseCfg.u32WrProtect));
        DDL_ASSERT(IS_EXMC_NFC_ECC_MODE(pstcInit->stcBaseCfg.u32EccMode));
        DDL_ASSERT(IS_EXMC_NFC_ROW_ADDRESS_CYCLES(pstcInit->stcBaseCfg.u32RowAddrCycle));

        DDL_ASSERT(IS_EXMC_NFC_TIMING_TS(pstcInit->stcTimingReg0.u32TS));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TWP(pstcInit->stcTimingReg0.u32TWP));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TRP(pstcInit->stcTimingReg0.u32TRP));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TH(pstcInit->stcTimingReg0.u32TH));

        DDL_ASSERT(IS_EXMC_NFC_TIMING_TWH(pstcInit->stcTimingReg1.u32TWH));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TRH(pstcInit->stcTimingReg1.u32TRH));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TRR(pstcInit->stcTimingReg1.u32TRR));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TWB(pstcInit->stcTimingReg1.u32TWB));

        DDL_ASSERT(IS_EXMC_NFC_TIMING_TCCS(pstcInit->stcTimingReg2.u32TCCS));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TWTR(pstcInit->stcTimingReg2.u32TWTR));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TRTW(pstcInit->stcTimingReg2.u32TRTW));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TADL(pstcInit->stcTimingReg2.u32TADL));

        /* Set NFC open-page.*/
        WRITE_REG32(M4_PERIC->NFC_SYCTLREG, pstcInit->u32OpenPage);

        /* Disable hardware ECC.*/
        WRITE_REG32(M4_NFC->IENR, 0x00000080UL);

        /* Clear flag.*/
        WRITE_REG32(M4_NFC->ISTR, 0x00000000UL);

        /* Set NFC base configure.*/
        u32RegVal = (pstcInit->stcBaseCfg.u32CapacitySize | \
                     pstcInit->stcBaseCfg.u32MemWidth | \
                     pstcInit->stcBaseCfg.u32BankNum | \
                     pstcInit->stcBaseCfg.u32PageSize | \
                     pstcInit->stcBaseCfg.u32WrProtect | \
                     pstcInit->stcBaseCfg.u32EccMode | \
                     pstcInit->stcBaseCfg.u32RowAddrCycle | \
                     (((uint32_t)pstcInit->stcBaseCfg.u8SpareSizeForUserData) << NFC_BACR_SCS_POS));
        WRITE_REG32(M4_NFC->BACR, u32RegVal);

        /* Set NFC timing register 0.*/
        u32RegVal = ((pstcInit->stcTimingReg0.u32TS << NFC_TMCR0_TS_POS)   | \
                     (pstcInit->stcTimingReg0.u32TWP << NFC_TMCR0_TWP_POS) | \
                     (pstcInit->stcTimingReg0.u32TRP << NFC_TMCR0_TRP_POS) | \
                     (pstcInit->stcTimingReg0.u32TH << NFC_TMCR0_TH_POS));
        WRITE_REG32(M4_NFC->TMCR0, u32RegVal);

        /* Set NFC timing register 1.*/
        u32RegVal = ((pstcInit->stcTimingReg1.u32TWH << NFC_TMCR1_TWH_POS) | \
                     (pstcInit->stcTimingReg1.u32TRH << NFC_TMCR1_TRH_POS) | \
                     (pstcInit->stcTimingReg1.u32TRR << NFC_TMCR1_TRR_POS) | \
                     (pstcInit->stcTimingReg1.u32TWB << NFC_TMCR1_TWB_POS));
        WRITE_REG32(M4_NFC->TMCR1, u32RegVal);

        /* Set NFC timing register 2.*/
        u32RegVal = ((pstcInit->stcTimingReg2.u32TCCS << NFC_TMCR2_TCCS_POS) | \
                     (pstcInit->stcTimingReg2.u32TWTR << NFC_TMCR2_TWTR_POS) | \
                     (pstcInit->stcTimingReg2.u32TRTW << NFC_TMCR2_TRTW_POS) | \
                     (pstcInit->stcTimingReg2.u32TADL << NFC_TMCR2_TADL_POS));
        WRITE_REG32(M4_NFC->TMCR2, u32RegVal);

        /* De-select NFC bank */
        WRITE_REG32(M4_NFC->CMDR, EXMC_NFC_CMD_DESELECT_CHIP);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize EXMC NFC function.
 * @param  None
 * @retval None
 */
void EXMC_NFC_DeInit(void)
{
    WRITE_REG32(M4_NFC->BACR, 0x00002187UL);
    WRITE_REG32(M4_NFC->IENR, 0x00000080UL);
    WRITE_REG32(M4_NFC->ISTR, 0x00000000UL);
    WRITE_REG32(M4_NFC->TMCR0, 0x03030202UL);
    WRITE_REG32(M4_NFC->TMCR1, 0x28080303UL);
    WRITE_REG32(M4_NFC->TMCR2, 0x03050D03UL);
}

/**
 * @brief  Set the fields of structure stc_exmc_nfc_init_t to default values
 * @param  [out] pstcInit               Pointer to a @ref stc_exmc_nfc_init_t structure (EXMC NFC function configuration structure)
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t EXMC_NFC_StructInit(stc_exmc_nfc_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcInit)
    {
        pstcInit->stcBaseCfg.u32CapacitySize = EXMC_NFC_BANK_CAPACITY_8GBIT;
        pstcInit->stcBaseCfg.u32MemWidth = EXMC_NFC_MEMORY_WIDTH_8BIT;
        pstcInit->stcBaseCfg.u32BankNum = EXMC_NFC_4_BANKS;
        pstcInit->stcBaseCfg.u32PageSize = EXMC_NFC_PAGE_SIZE_2KBYTES;
        pstcInit->stcBaseCfg.u32WrProtect = EXMC_NFC_WR_PROTECT_ENABLE;
        pstcInit->stcBaseCfg.u32EccMode = EXMC_NFC_ECC_1BIT;
        pstcInit->stcBaseCfg.u32RowAddrCycle = EXMC_NFC_3_ROW_ADDRESS_CYCLES;
        pstcInit->stcBaseCfg.u8SpareSizeForUserData = 0U;

        pstcInit->stcTimingReg0.u32TS = 0x02UL;
        pstcInit->stcTimingReg0.u32TWP = 0x02UL;
        pstcInit->stcTimingReg0.u32TRP = 0x03UL;
        pstcInit->stcTimingReg0.u32TH = 0x03UL;

        pstcInit->stcTimingReg1.u32TWH = 0x03UL;
        pstcInit->stcTimingReg1.u32TRH = 0x03UL;
        pstcInit->stcTimingReg1.u32TRR = 0x02UL;
        pstcInit->stcTimingReg1.u32TWB = 0x28UL;

        pstcInit->stcTimingReg2.u32TCCS = 0x03UL;
        pstcInit->stcTimingReg2.u32TWTR = 0x0DUL;
        pstcInit->stcTimingReg2.u32TRTW = 0x05UL;
        pstcInit->stcTimingReg2.u32TADL = 0x03UL;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable/disable NFC.
 * @param  [in]  enNewState                 An en_functional_state_t enumeration value.
 *         This parameter can be one of the following values:
 *           @arg Enable:                   Enable function.
 *           @arg Disable:                  Disable function.
 * @retval None
 */
void EXMC_NFC_Cmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bM4_PERIC->EXMC_ENAR_b.NFCEN, enNewState);
}

/**
 * @brief  Enable/disable NFC ECC function.
 * @param  [in]  enNewState                 An en_functional_state_t enumeration value.
 *         This parameter can be one of the following values:
 *           @arg Enable:                   Enable function.
 *           @arg Disable:                  Disable function.
 * @retval None
 */
void EXMC_NFC_EccCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        CLEAR_REG32_BIT(M4_NFC->IENR, NFC_IENR_ECCDIS);
    }
    else
    {
        SET_REG32_BIT(M4_NFC->IENR, NFC_IENR_ECCDIS);
    }
}

/**
 * @brief  Enable/disable NFC write protection function.
 * @param  [in]  enNewState                 An en_functional_state_t enumeration value.
 *         This parameter can be one of the following values:
 *           @arg Enable:                   Enable function.
 *           @arg Disable:                  Disable function.
 * @retval None
 */
void EXMC_NFC_WriteProtectCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        CLEAR_REG32_BIT(M4_NFC->BACR, NFC_BACR_WP);
    }
    else
    {
        SET_REG32_BIT(M4_NFC->BACR, NFC_BACR_WP);
    }
}

/**
 * @brief  Enable or disable the specified NFC interrupt
 * @param  [in] u16IntSource            The specified interrupt
 *         This parameter can be any composed value of the following values:
 *           @arg EXMC_NFC_INT_ECC_UNCORRECTABLE_ERROR: ECC uncorrectable error interrupt
 *           @arg EXMC_NFC_INT_ECC_CORRECTABLE_ERROR: ECC correctable error interrupt
 *           @arg EXMC_NFC_INT_ECC_CALC_COMPLETION: Calculating ECC completely interrupt
 *           @arg EXMC_NFC_INT_ECC_ERROR: ECC error interrupt
 *           @arg EXMC_NFC_INT_RB_BANK0: NFC bank 0 device ready interrupt
 *           @arg EXMC_NFC_INT_RB_BANK1: NFC bank 1 device ready interrupt
 *           @arg EXMC_NFC_INT_RB_BANK2: NFC bank 2 device ready interrupt
 *           @arg EXMC_NFC_INT_RB_BANK3: NFC bank 3 device ready interrupt
 *           @arg EXMC_NFC_INT_RB_BANK4: NFC bank 4 device ready flag
 *           @arg EXMC_NFC_INT_RB_BANK5: NFC bank 5 device ready interrupt
 *           @arg EXMC_NFC_INT_RB_BANK6: NFC bank 6 device ready interrupt
 *           @arg EXMC_NFC_INT_RB_BANK7: NFC bank 7 device ready interrupt
 * @param  [in] enNewState              The function new state
 *           @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void EXMC_NFC_IntCmd(uint16_t u16IntSource, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_EXMC_NFC_INT(u16IntSource));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(M4_NFC->IENR, u16IntSource);
    }
    else
    {
        CLEAR_REG16_BIT(M4_NFC->IENR, u16IntSource);
    }
}

/**
 * @brief  Get the flag.
 * @param  [in] u32Flag                 The specified flag
 *         This parameter can be any composed value of the following values:
 *           @arg EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERROR: ECC uncorrectable error
 *           @arg EXMC_NFC_FLAG_ECC_CORRECTABLE_ERROR: ECC correctable error
 *           @arg EXMC_NFC_FLAG_ECC_CALC_COMPLETION: Calculate ECC completely
 *           @arg EXMC_NFC_FLAG_ECC_ERROR: ECC error
 *           @arg EXMC_NFC_FLAG_RB_BANK0: NFC bank 0 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK1: NFC bank 1 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK2: NFC bank 2 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK3: NFC bank 3 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK4: NFC bank 4 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK5: NFC bank 5 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK6: NFC bank 6 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK7: NFC bank 7 device ready flag
 *           @arg EXMC_NFC_FLAG_ECC_CALCULATING: Calculating ECC
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t EXMC_NFC_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enStatus1 = Set;
    en_flag_status_t enStatus2 = Set;

    /* Check parameters */
    DDL_ASSERT(IS_EXMC_NFC_FLAG(u32Flag));

    if ((u32Flag & NFC_NFC_ISTR_MASK) != 0UL)
    {
        if (0UL == READ_REG32_BIT(M4_NFC->ISTR, (u32Flag & NFC_NFC_ISTR_MASK)))
        {
            enStatus1 = Reset;
        }
    }

    if ((u32Flag & EXMC_NFC_FLAG_ECC_CALCULATING) != 0UL)
    {
        if (0UL == READ_REG32(bM4_PERIC->NFC_SYSTATREG_b.PECC))
        {
            enStatus2 = Reset;
        }
    }

    return (((Set == enStatus1) && (Set == enStatus2)) ? Set : Reset);
}

/**
 * @brief  Get the flag.
 * @param  [in] u32Flag                 The specified flag
 *         This parameter can be any composed value of the following values:
 *           @arg EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERROR: ECC uncorrectable error
 *           @arg EXMC_NFC_FLAG_ECC_CORRECTABLE_ERROR: ECC correctable error
 *           @arg EXMC_NFC_FLAG_ECC_CALC_COMPLETION: Calculating ECC completely
 *           @arg EXMC_NFC_FLAG_ECC_ERROR: ECC error
 *           @arg EXMC_NFC_FLAG_RB_BANK0: NFC bank 0 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK1: NFC bank 1 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK2: NFC bank 2 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK3: NFC bank 3 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK4: NFC bank 4 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK5: NFC bank 5 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK6: NFC bank 6 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK7: NFC bank 7 device ready flag
 * @retval None
 */
void EXMC_NFC_ClearStatus(uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_EXMC_NFC_FLAG(u32Flag));

    CLEAR_REG32_BIT(M4_NFC->ISTR, u32Flag);
}

/**
 * @brief  Get the interrupt result.
 * @param  [in] u32Flag                 The specified flag
 *         This parameter can be any composed value of the following values:
 *           @arg EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERROR: ECC uncorrectable error
 *           @arg EXMC_NFC_FLAG_ECC_CORRECTABLE_ERROR: ECC correctable error
 *           @arg EXMC_NFC_FLAG_ECC_CALC_COMPLETION: Calculating ECC completely
 *           @arg EXMC_NFC_FLAG_ECC_ERROR: ECC error
 *           @arg EXMC_NFC_FLAG_RB_BANK0: NFC bank 0 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK1: NFC bank 1 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK2: NFC bank 2 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK3: NFC bank 3 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK4: NFC bank 4 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK5: NFC bank 5 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK6: NFC bank 6 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK7: NFC bank 7 device ready flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t EXMC_NFC_GetIntResultStatus(uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_EXMC_NFC_FLAG(u32Flag));

    return (READ_REG32_BIT(M4_NFC->IRSR, u32Flag) ? Set : Reset);
}

/**
 * @brief  Get the 1BIT ECC result of the specified section.
 * @param  [in] u32Section              The specified section
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_ECC_SECTION0: ECC section 0
 *           @arg EXMC_NFC_ECC_SECTION1: ECC section 1
 *           @arg EXMC_NFC_ECC_SECTION2: ECC section 2
 *           @arg EXMC_NFC_ECC_SECTION3: ECC section 3
 *           @arg EXMC_NFC_ECC_SECTION4: ECC section 4
 *           @arg EXMC_NFC_ECC_SECTION5: ECC section 5
 *           @arg EXMC_NFC_ECC_SECTION6: ECC section 6
 *           @arg EXMC_NFC_ECC_SECTION7: ECC section 7
 *           @arg EXMC_NFC_ECC_SECTION8: ECC section 8
 *           @arg EXMC_NFC_ECC_SECTION9: ECC section 9
 *           @arg EXMC_NFC_ECC_SECTION10: ECC section 10
 *           @arg EXMC_NFC_ECC_SECTION11: ECC section 11
 *           @arg EXMC_NFC_ECC_SECTION12: ECC section 12
 *           @arg EXMC_NFC_ECC_SECTION13: ECC section 13
 *           @arg EXMC_NFC_ECC_SECTION14: ECC section 14
 *           @arg EXMC_NFC_ECC_SECTION15: ECC section 15
 * @retval The register value
 */
uint32_t EXMC_NFC_GetEcc1BitResult(uint32_t u32Section)
{
    /* Check parameters */
    DDL_ASSERT(IS_EXMC_NFC_SECTION(u32Section));

    return READ_REG32(NFC_ECCR_REG32(u32Section));
}

/**
 * @brief  Set NFC spare area size.
 * @param  [in] u8SpareSizeForUserData      NFC spare area size for user data
 * @retval None
 */
void EXMC_NFC_SetSpareAreaSize(uint8_t u8SpareSizeForUserData)
{
    MODIFY_REG32(M4_NFC ->BACR, NFC_BACR_SCS, ((((uint32_t)u8SpareSizeForUserData) << NFC_BACR_SCS_POS) & NFC_BACR_SCS));
}

/**
 * @brief  Set NFC ECC mode.
 * @param  [in] u32EccMode              ECC mode
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_ECC_1BIT: ECC 1 bit
 *           @arg EXMC_NFC_ECC_4BITS: ECC 4 bits
 * @retval None
 */
void EXMC_NFC_SetEccMode(uint32_t u32EccMode)
{
    DDL_ASSERT(IS_EXMC_NFC_ECC_MODE(u32EccMode));

    MODIFY_REG32(M4_NFC ->BACR, NFC_BACR_ECCM, u32EccMode);
}

/**
 * @brief  Get the 4 bits ECC syndrome register value.
 * @param  [in] u32Section          The syndrome section
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_SYND0: ECC syndrome section 0
 *           @arg EXMC_NFC_SYND1: ECC syndrome section 1
 *           @arg EXMC_NFC_SYND2: ECC syndrome section 2
 *           @arg EXMC_NFC_SYND3: ECC syndrome section 3
 *           @arg EXMC_NFC_SYND4: ECC syndrome section 4
 *           @arg EXMC_NFC_SYND5: ECC syndrome section 5
 *           @arg EXMC_NFC_SYND6: ECC syndrome section 6
 *           @arg EXMC_NFC_SYND7: ECC syndrome section 7
 *           @arg EXMC_NFC_SYND8: ECC syndrome section 8
 *           @arg EXMC_NFC_SYND9: ECC syndrome section 9
 *           @arg EXMC_NFC_SYND10: ECC syndrome section 10
 *           @arg EXMC_NFC_SYND11: ECC syndrome section 11
 *           @arg EXMC_NFC_SYND12: ECC syndrome section 12
 *           @arg EXMC_NFC_SYND13: ECC syndrome section 13
 *           @arg EXMC_NFC_SYND14: ECC syndrome section 14
 *           @arg EXMC_NFC_SYND15: ECC syndrome section 15
 * @param  [out] au16Synd       The syndrome value
 * @param  [in] u8Length        The length to be read(unit: half-word)
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: au16Synd = NULL or u8Length is out of range
 * @note  u8Length value don't be greater than 8
 */
en_result_t EXMC_NFC_GetSyndrome(uint32_t u32Section,
                                        uint16_t au16Synd[],
                                        uint8_t u8Length)
{
    uint8_t i;
    uint32_t u32SyndVal;
    uint8_t u8LoopWords;
    en_result_t enRet = ErrorInvalidParameter;

    if ((NULL != au16Synd) && (u8Length <= NFC_SYND_MAX_LEN))
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_NFC_SECTION(u32Section));

        u8LoopWords = (u8Length >> 1U);

        for (i = 0U; i < u8LoopWords; i++)
        {
            u32SyndVal = READ_REG32(NFC_SYND_REG32(u32Section, i));
            RW_MEM16(&au16Synd[i * 2U]) = (uint16_t)(u32SyndVal);
            RW_MEM16(&au16Synd[i * 2U + 1U ]) = (uint16_t)(u32SyndVal >> 16UL);
        }

        if ((u8Length % 2U) != 0U)
        {
            u32SyndVal = READ_REG32(NFC_SYND_REG32(u32Section, i));
            RW_MEM16(&au16Synd[i * 2U]) = (uint16_t)(u32SyndVal);
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Read NFC device status
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @retval NFC device status
 */
uint32_t EXMC_NFC_ReadStatus(uint32_t u32Bank)
{
    uint32_t u32Status;

    /* Check parameters */
    DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));

    /* Write 0x81000M70 to NFC_CMDR, M = bank number */
    WRITE_REG32(M4_NFC->CMDR, CMD_READ_STATUS(u32Bank));

    u32Status = READ_REG32(M4_NFC->DATR_BASE);

    EXMC_NFC_DeselectChip();

    return u32Status;
}

/**
 * @brief  Read status enhanced
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u32RowAddress           The row address
 * @retval NFC device status enhanced
 */
uint32_t EXMC_NFC_ReadStatusEnhanced(uint32_t u32Bank,
                                            uint32_t u32RowAddress)
{
    uint32_t u32Status;

    /* Check parameters */
    DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));

    /* Erase block step:
        1. Write 0x81000M78 to NFC_CMDR, M = bank number
        2. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the lowest bytes of Row address
        3. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the middle bytes of Row address
        4. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the highest bytes of Row address
        5. Read Data Register */
    WRITE_REG32(M4_NFC->CMDR, CMD_READ_STATUS_ENHANCED(u32Bank));
    WRITE_REG32(M4_NFC->CMDR, CMD_ADDR_1ST_CYCLE(u32Bank, u32RowAddress));
    WRITE_REG32(M4_NFC->CMDR, CMD_ADDR_2ND_CYCLE(u32Bank, u32RowAddress));
    WRITE_REG32(M4_NFC->CMDR, CMD_ADDR_3RD_CYCLE(u32Bank, u32RowAddress));

    u32Status = READ_REG32(M4_NFC->DATR_BASE);

    EXMC_NFC_DeselectChip();

    return u32Status;
}

/**
 * @brief  Reset NFC device
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Reset timeout.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
en_result_t EXMC_NFC_Reset(uint32_t u32Bank, uint32_t u32Timeout)
{
    en_result_t enRet;

    /* Check parameters */
    DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));

    /* Clear Flag */
    EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

    /* Reset step:
        1. Write 0x00000MFF to NFC_CMDR, M = bank number
        2. Wait RB signal until high level */
    WRITE_REG32(M4_NFC->CMDR, CMD_RESET(u32Bank));

    enRet = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), \
                                     Set, \
                                     u32Timeout);

    EXMC_NFC_DeselectChip();

    return enRet;
}

/**
 * @brief  Asynchronous reset
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Reset timeout.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
en_result_t EXMC_NFC_AsyncReset(uint32_t u32Bank, uint32_t u32Timeout)
{
    en_result_t enRet;

    /* Clear Flag */
    EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

    /* Reset step:
        1. Write 0x00000MFC to NFC_CMDR, M = bank number
        2. Wait RB signal until high level */
    WRITE_REG32(M4_NFC->CMDR, CMD_ASYNC_RESET(u32Bank));

    enRet = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), \
                                     Set, \
                                     u32Timeout);
    EXMC_NFC_DeselectChip();
    return enRet;
}

/**
 * @brief  Reset lun of NFC device
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u32RowAddress           The row address
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Reset timeout.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
en_result_t EXMC_NFC_ResetLun(uint32_t u32Bank,
                                    uint32_t u32RowAddress,
                                    uint32_t u32Timeout)
{
    en_result_t enRet;

    /* Clear Flag */
    EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

    /* Reset lun step:
        1. Write 0x82000MFA to NFC_CMDR, M = bank number
        2. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the lowest bytes of Row address
        3. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the middle bytes of Row address
        4. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the highest bytes of Row address
        5. Wait RB signal until high level */
    WRITE_REG32(M4_NFC->CMDR, CMD_RESET_LUN(u32Bank));
    WRITE_REG32(M4_NFC->CMDR, CMD_ADDR_1ST_CYCLE(u32Bank, u32RowAddress));
    WRITE_REG32(M4_NFC->CMDR, CMD_ADDR_2ND_CYCLE(u32Bank, u32RowAddress));
    WRITE_REG32(M4_NFC->CMDR, CMD_ADDR_3RD_CYCLE(u32Bank, u32RowAddress));

    enRet = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), \
                                     Set, \
                                     u32Timeout);
    return enRet;
}

/**
 * @brief  Read ID
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u32IdAddr               The address
 * @param  [in] au8DevId                The id buffer
 * @param  [in] u32NumBytes             The number of bytes to read
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  Error:                       au8DevId == NULL.
 */
en_result_t EXMC_NFC_ReadId(uint32_t u32Bank,
                                uint32_t u32IdAddr,
                                uint8_t au8DevId[],
                                uint32_t u32NumBytes,
                                uint32_t u32Timeout)
{
    uint32_t i;
    uint64_t u64Val;
    const uint32_t u32LoopWords = u32NumBytes/4UL;
    const uint32_t u32RemainBytes = u32NumBytes%4UL;
    uint32_t u32TmpId;
    uint32_t u32CapacityIndex;
    en_result_t enRet = Error;

    if ((NULL != au8DevId) && (u32NumBytes > 0UL))
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));
        DDL_ASSERT(u32IdAddr <= 0xFFUL);

        /* Clear Flag */
        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank) | \
                           EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERROR | \
                           EXMC_NFC_FLAG_ECC_CORRECTABLE_ERROR | \
                           EXMC_NFC_FLAG_ECC_CALC_COMPLETION | \
                           EXMC_NFC_FLAG_ECC_ERROR);

        u32CapacityIndex = EXMC_NFC_GetCapacityIndex();
        u64Val = (NFC_IDXR_VAL(u32Bank, 0UL, 0UL, u32CapacityIndex) & NFC_IDXR_MASK);

        /* 1. Write 0x00000000 to NFC_CMDR */
        WRITE_REG32(M4_NFC->CMDR, EXMC_NFC_CMD_READ_1ST);

        /* 2. Write NAND Flash address to NFC_IDXR0/1 */
        WRITE_REG32(M4_NFC->IDXR0, (uint32_t)(u64Val & 0xFFFFFFFFUL));
        WRITE_REG32(M4_NFC->IDXR1, (uint32_t)(u64Val >> 32UL));

        /* 3. Write 0x000000E0 to NFC_CMDR */
        WRITE_REG32(M4_NFC->CMDR, EXMC_NFC_CMD_READ_2ND);

        /* 4. Wait RB signal until high level */
        enRet = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), \
                                         Set, \
                                         u32Timeout);
        if (Ok == enRet)
        {
            /* Read Id step:
                1. Write 0x81000M90 to NFC_CMDR, M = bank number
                2. Write 0x40000MAB to NFC_CMDR, M = bank number, AB=ID address
                3. Read NFC_DATR
                4. Write 0x000000FE to NFC_CMDR, and invalidate CE */
            WRITE_REG32(M4_NFC->CMDR, CMD_READ_ID(u32Bank));
            WRITE_REG32(M4_NFC->CMDR, CMD_READ_ID_ADDR(u32Bank, u32IdAddr));
            for (i = 0UL; i < u32LoopWords; i++)
            {
                u32TmpId = NFC_DATR_REG32(i);
                (void)memcpy (&au8DevId[i * 4UL], &u32TmpId, 4UL);
            }

            if (u32RemainBytes > 0UL)
            {
                u32TmpId = NFC_DATR_REG32(i);
                (void)memcpy (&au8DevId[i * 4UL], &u32TmpId, u32RemainBytes);
            }

            enRet = Ok;
        }

        EXMC_NFC_DeselectChip();
    }

    return enRet;
}

/**
 * @brief  Read Unique ID
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u32IdAddr               The address
 * @param  [in] au32UniqueId            The id buffer
 * @param  [in] u8NumWords              The number of words to read
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  Error:                       au8DevId == NULL.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
en_result_t EXMC_NFC_ReadUniqueId(uint32_t u32Bank,
                                        uint32_t u32IdAddr,
                                        uint32_t au32UniqueId[],
                                        uint8_t u8NumWords,
                                        uint32_t u32Timeout)
{
    uint8_t i;
    en_result_t enRet = Error;

    if ((NULL != au32UniqueId) && (u8NumWords > 0U))
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));

        /* Clear Flag */
        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

        /* Read Id step:
            1. Write 0x81000M90 to NFC_CMDR, M = bank number
            2. Write 0x40000M00 to NFC_CMDR, M = bank number, AB=ID address
            3. Read NFC_DATR
            4. Write 0x000000FE to NFC_CMDR, and invalidate CE */
        WRITE_REG32(M4_NFC->CMDR, CMD_READ_UNIQUEID(u32Bank));
        WRITE_REG32(M4_NFC->CMDR, CMD_READ_UNIQUEID_ADDR(u32Bank));

        enRet = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), \
                                         Set, \
                                         u32Timeout);
        if (Ok == enRet)
        {
            for (i = 0U; i < u8NumWords; i++)
            {
                au32UniqueId[i] = NFC_DATR_REG32(i);
            }
        }

        EXMC_NFC_DeselectChip();
    }

    return enRet;
}

/**
 * @brief  Read parameter page
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] au32Data                The data buffer
 * @param  [in] u16NumWords             The number of words to read
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  Error:                       au8Data == NULL.
 *   @arg  ErrorTimeout:                Read timeout
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
en_result_t EXMC_NFC_ReadParameterPage(uint32_t u32Bank,
                                        uint32_t au32Data[],
                                        uint16_t u16NumWords,
                                        uint32_t u32Timeout)
{
    uint16_t i;
    en_result_t enRet = Error;

    if ((NULL != au32Data) && (u16NumWords > 0U))
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));

        /* Clear Flag */
        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

        /* Read parameter page step:
            1. Write 0x81000MEC to NFC_CMDR, M = bank number
            2. Write 0x40000M00 to NFC_CMDR, M = bank number
            3. Read NFC_DATR
            4. Write 0x000000FE to NFC_CMDR, and invalidate CE */
        WRITE_REG32(M4_NFC->CMDR, CMD_READ_PARAMETER_PAGE(u32Bank));
        WRITE_REG32(M4_NFC->CMDR, CMD_READ_PARAMETER_PAGE_ADDR(u32Bank));

        enRet = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), \
                                         Set, \
                                         u32Timeout);
        if (Ok == enRet)
        {
            for (i = 0U; i < u16NumWords; i++)
            {
                au32Data[i] =  NFC_DATR_REG32(i);
            }
        }

        EXMC_NFC_DeselectChip();
    }

    return enRet;
}

/**
 * @brief  Set feature
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u8FeatrueAddr           The featrue address
 * @param  [in] au32Data                The data buffer
 * @param  [in] u8NumWords              The number of words to set
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  Error:                       au8Data == NULL.
 *   @arg  ErrorTimeout:                Read timeout
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
en_result_t EXMC_NFC_SetFeature(uint32_t u32Bank,
                                    uint8_t u8FeatrueAddr,
                                    const uint32_t au32Data[],
                                    uint8_t u8NumWords,
                                    uint32_t u32Timeout)
{
    uint8_t i;
    en_result_t enRet = Error;

    if ((NULL != au32Data) && (u8NumWords > 0U))
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));

        /* Clear Flag */
        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

        WRITE_REG32(M4_NFC->CMDR, CMD_SET_FEATURE(u32Bank));
        WRITE_REG32(M4_NFC->CMDR, CMD_SET_FEATURE_ADDR(u32Bank, u8FeatrueAddr));

        for (i = 0U; i < u8NumWords; i++)
        {
            NFC_DATR_REG32(i) = au32Data[i];
        }

        enRet = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), \
                                         Set, \
                                         u32Timeout);

        EXMC_NFC_DeselectChip();
    }

    return enRet;
}

/**
 * @brief  Get feature
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u8FeatrueAddr           The featrue address
 * @param  [out] au32Data               The data buffer
 * @param  [in] u8NumWords              The number of words to get
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  Error:                       au8Data == NULL.
 *   @arg  ErrorTimeout:                Read timeout
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
en_result_t EXMC_NFC_GetFeature(uint32_t u32Bank,
                                    uint8_t u8FeatrueAddr,
                                    uint32_t au32Data[],
                                    uint8_t u8NumWords,
                                    uint32_t u32Timeout)
{
    uint8_t i;
    en_result_t enRet = Error;

    if ((NULL != au32Data) && (u8NumWords > 0U))
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));

        /* Clear Flag */
        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

        WRITE_REG32(M4_NFC->CMDR, CMD_GET_FEATURE(u32Bank));
        WRITE_REG32(M4_NFC->CMDR, CMD_GET_FEATURE_ADDR(u32Bank, u8FeatrueAddr));

        enRet = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), \
                                         Set, \
                                         u32Timeout);
        if (Ok == enRet)
        {
            for (i = 0U; i < u8NumWords; i++)
            {
                au32Data[i] = NFC_DATR_REG32(i);
            }
        }

        EXMC_NFC_DeselectChip();
    }

    return enRet;
}

/**
 * @brief  Erase NFC device block
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u32RowAddress           The row address
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Erase timeout.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
en_result_t EXMC_NFC_EraseBlock(uint32_t u32Bank,
                                    uint32_t u32RowAddress,
                                    uint32_t u32Timeout)
{
    en_result_t enRet;

    /* Check parameters */
    DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));

    /* Clear Flag */
    EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

    /* Erase block step:
        1. Write 0x81000M60 to NFC_CMDR, M = bank number
        2. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the lowest bytes of Row address
        3. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the middle bytes of Row address
        4. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the highest bytes of Row address
        5. Write 0x00000MD0 to NFC_CMDR, M = bank number
        6. Wait RB signal until high level */
    WRITE_REG32(M4_NFC->CMDR, CMD_ERASE_BLOCK_1ST_CYCLE(u32Bank));
    WRITE_REG32(M4_NFC->CMDR, CMD_ADDR_1ST_CYCLE(u32Bank, u32RowAddress));
    WRITE_REG32(M4_NFC->CMDR, CMD_ADDR_2ND_CYCLE(u32Bank, u32RowAddress));
    WRITE_REG32(M4_NFC->CMDR, CMD_ADDR_3RD_CYCLE(u32Bank, u32RowAddress));
    WRITE_REG32(M4_NFC->CMDR, CMD_ERASE_BLOCK_2ND_CYCLE(u32Bank));

    enRet = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), \
                                     Set, \
                                     u32Timeout);
    return enRet;
}

/**
 * @brief  NFC page read
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u32Page                 The specified page
 * @param  [out] pu8Data                The buffer for reading
 * @param  [in] u32NumBytes             The buffer size for bytes
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Write timeout.
 *   @arg  ErrorInvalidParameter:       The pointer au8Buf value is NULL.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
en_result_t EXMC_NFC_ReadPageMeta(uint32_t u32Bank,
                                    uint32_t u32Page,
                                    uint8_t *pu8Data,
                                    uint32_t u32NumBytes,
                                    uint32_t u32Timeout)
{
    en_result_t enRet = ErrorInvalidParameter;

    if ((NULL != pu8Data) && (u32NumBytes > 0UL))
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));
        DDL_ASSERT(IS_PARAM_ALIGN_WORD(u32NumBytes));
        DDL_ASSERT(IS_ADDRESS_ALIGN_WORD(pu8Data));

        enRet = EXMC_NFC_Read(u32Bank, u32Page, 0UL, (uint32_t *)((uint32_t)pu8Data), \
                              (u32NumBytes/4UL), Disable, u32Timeout);
    }

    return enRet;
}

/**
 * @brief  NFC page write
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u32Page                 The specified page
 * @param  [in] pu8Data                 The buffer for writing
 * @param  [in] u32NumBytes             The buffer size for bytes
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Write timeout.
 *   @arg  ErrorInvalidParameter:       The pointer au8Buf value is NULL.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
en_result_t EXMC_NFC_WritePageMeta(uint32_t u32Bank,
                                    uint32_t u32Page,
                                    const uint8_t *pu8Data,
                                    uint32_t u32NumBytes,
                                    uint32_t u32Timeout)
{
    en_result_t enRet = ErrorInvalidParameter;

    if ((NULL != pu8Data) && (u32NumBytes > 0UL))
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));
        DDL_ASSERT(IS_PARAM_ALIGN_WORD(u32NumBytes));
        DDL_ASSERT(IS_ADDRESS_ALIGN_WORD(pu8Data));

        enRet = EXMC_NFC_Write(u32Bank, u32Page, 0UL, (uint32_t *)((uint32_t)pu8Data), \
                                (u32NumBytes/4UL), Disable, u32Timeout);
    }

    return enRet;
}

/**
 * @brief  NFC page read by hardware ECC
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u32Page                 The specified page
 * @param  [out] pu8Data                The buffer for reading
 * @param  [in] u32NumBytes             The buffer size for bytes
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Write timeout.
 *   @arg  ErrorInvalidParameter:       The pointer au8Buf value is NULL.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
en_result_t EXMC_NFC_ReadPageHwEcc(uint32_t u32Bank,
                                    uint32_t u32Page,
                                    uint8_t *pu8Data,
                                    uint32_t u32NumBytes,
                                    uint32_t u32Timeout)
{
    const uint32_t u32PageSize = NFC_PAGE_SIZE;
    const uint32_t u32SpareSizeUserData = NFC_SPARE_SIZE_FOR_USER_DATA;
    en_result_t enRet = ErrorInvalidParameter;

    if ((NULL != pu8Data) && (u32NumBytes > 0UL))
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));
        DDL_ASSERT(IS_PARAM_ALIGN_WORD(u32NumBytes));
        DDL_ASSERT(IS_ADDRESS_ALIGN_WORD(pu8Data));
        DDL_ASSERT(u32NumBytes <= (u32PageSize + u32SpareSizeUserData));

        enRet = EXMC_NFC_Read(u32Bank, u32Page, 0UL, (uint32_t *)((uint32_t)pu8Data), \
                                (u32NumBytes/4UL), Enable, u32Timeout);
    }

    return enRet;
}

/**
 * @brief  NFC page  write by hardware ECC
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u32Page                 The specified page
 * @param  [in] pu8Data                 The buffer for writing
 * @param  [in] u32NumBytes             The buffer size for bytes
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Write timeout.
 *   @arg  ErrorInvalidParameter:       The pointer au8Buf value is NULL.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
en_result_t EXMC_NFC_WritePageHwEcc(uint32_t u32Bank,
                                    uint32_t u32Page,
                                    const uint8_t *pu8Data,
                                    uint32_t u32NumBytes,
                                    uint32_t u32Timeout)
{
    const uint32_t u32PageSize = NFC_PAGE_SIZE;
    const uint32_t u32SpareSizeUserData = NFC_SPARE_SIZE_FOR_USER_DATA;
    en_result_t enRet = ErrorInvalidParameter;

    if ((NULL != pu8Data) && (u32NumBytes > 0UL))
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));
        DDL_ASSERT(IS_PARAM_ALIGN_WORD(u32NumBytes));
        DDL_ASSERT(IS_ADDRESS_ALIGN_WORD((uint32_t)pu8Data));
        DDL_ASSERT(u32NumBytes <= (u32PageSize + u32SpareSizeUserData));

        enRet = EXMC_NFC_Write(u32Bank, u32Page, 0UL, (uint32_t *)((uint32_t)pu8Data), \
                                (u32NumBytes/4UL), Enable, u32Timeout);
    }

    return enRet;
}

/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Local_Functions NAND Flash Controller Local Functions
 * @{
 */

/**
 * @brief  NFC read operation
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u32Page                 The specified page
 * @param  [in] u32Col                  The column address
 * @param  [out] au32Data               The buffer for reading
 * @param  [in] u32NumWords             The buffer size for words
 * @param  [in] enEccState              Disable/enable ECC function
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Write timeout.
 *   @arg  ErrorInvalidParameter:       The pointer au8Buf value is NULL.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
static en_result_t EXMC_NFC_Read(uint32_t u32Bank,
                                    uint32_t u32Page,
                                    uint32_t u32Col,
                                    uint32_t au32Data[],
                                    uint32_t u32NumWords,
                                    en_functional_state_t enEccState,
                                    uint32_t u32Timeout)
{
    uint32_t i;
    uint64_t u64Val;
    en_result_t enRet = ErrorInvalidParameter;
    const uint32_t u32CapacityIndex = EXMC_NFC_GetCapacityIndex();

    if ((NULL != au32Data) && (u32NumWords > 0UL))
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));
        DDL_ASSERT(IS_EXMC_NFC_PAGE(u32Page, u32CapacityIndex));
        DDL_ASSERT(IS_EXMC_NFC_COLUMN(u32Col));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enEccState));

        /* Clear Flag */
        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank) | \
                           EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERROR | \
                           EXMC_NFC_FLAG_ECC_CORRECTABLE_ERROR | \
                           EXMC_NFC_FLAG_ECC_CALC_COMPLETION | \
                           EXMC_NFC_FLAG_ECC_ERROR);

        if (Enable == enEccState)
        {
            EXMC_NFC_EccCmd(Enable);
        }
        else
        {
            EXMC_NFC_EccCmd(Disable);
        }

        u64Val = (NFC_IDXR_VAL(u32Bank, u32Page, u32Col, u32CapacityIndex) & NFC_IDXR_MASK);

        /* Read page step:
            1. Write 0x00000000 to NFC_CMDR
            2. Write NAND Flash address to NFC_IDXR0/1
            3. Write 0x000000E0 to NFC_CMDR
            4. Wait RB signal until high level
            5. Read NFC_DATR
            6. Write 0x000000FE to NFC_CMDR, and invalidate CE */

        /* 1. Write 0x00000000 to NFC_CMDR */
        WRITE_REG32(M4_NFC->CMDR, EXMC_NFC_CMD_READ_1ST);

        /* 2. Write NAND Flash address to NFC_IDXR0/1 */
        WRITE_REG32(M4_NFC->IDXR0, (uint32_t)(u64Val & 0xFFFFFFFFUL));
        WRITE_REG32(M4_NFC->IDXR1, (uint32_t)(u64Val >> 32UL));

        /* 3. Write 0x000000E0 to NFC_CMDR */
        WRITE_REG32(M4_NFC->CMDR, EXMC_NFC_CMD_READ_2ND);

        /* 4. Wait RB signal until high level */
        enRet = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), \
                                         Set, \
                                         u32Timeout);
        if (Ok == enRet)
        {
            /* 5. Read NFC_DATR */
            for (i = 0UL; i < u32NumWords; i++)
            {
                au32Data[i] = NFC_DATR_REG32(i);
            }

            /* Clear Flag */
            EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

            if (Enable == enEccState)
            {
                /* Write 0x00000023 to NFC_CMDR */
                WRITE_REG32(M4_NFC->CMDR, EXMC_NFC_CMD_CALCULATE_ECC);

                /* 4. Wait RB signal until high level */
                enRet = EXMC_NFC_WaitFlagUntilTo(EXMC_NFC_FLAG_ECC_CALCULATING, \
                                                 Reset, \
                                                 u32Timeout);
                EXMC_NFC_EccCmd(Disable);
            }
        }

        /* 6. Write 0x000000FE to NFC_CMDR, and invalidate CE */
        EXMC_NFC_DeselectChip();
    }

    return enRet;
}

/**
 * @brief  NFC write operation
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *           @arg EXMC_NFC_BANK_0:      NFC device bank 0
 *           @arg EXMC_NFC_BANK_1:      NFC device bank 1
 *           @arg EXMC_NFC_BANK_2:      NFC device bank 2
 *           @arg EXMC_NFC_BANK_3:      NFC device bank 3
 *           @arg EXMC_NFC_BANK_4:      NFC device bank 4
 *           @arg EXMC_NFC_BANK_5:      NFC device bank 5
 *           @arg EXMC_NFC_BANK_6:      NFC device bank 6
 *           @arg EXMC_NFC_BANK_7:      NFC device bank 7
 * @param  [in] u32Page                 The specified page
 * @param  [in] u32Col                  The column address
 * @param  [in] au32Data                The buffer for writing
 * @param  [in] u32NumWords             The buffer size for words
 * @param  [in] enEccState              Disable/enable ECC function
 * @param  [in] u32Timeout              The operation timeout value
 * @retval An en_result_t enumeration value:
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorTimeout:                Write timeout.
 *   @arg  ErrorInvalidParameter:       The pointer au8Buf value is NULL.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
static en_result_t EXMC_NFC_Write(uint32_t u32Bank,
                                    uint32_t u32Page,
                                    uint32_t u32Col,
                                    const uint32_t au32Data[],
                                    uint32_t u32NumWords,
                                    en_functional_state_t enEccState,
                                    uint32_t u32Timeout)
{
    uint32_t i;
    uint64_t u64Val;
    en_result_t enRet = Error;
    const uint32_t u32CapacityIndex = EXMC_NFC_GetCapacityIndex();

    if ((NULL != au32Data) && (u32NumWords > 0UL))
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(u32Bank));
        DDL_ASSERT(IS_EXMC_NFC_PAGE(u32Page, u32CapacityIndex));
        DDL_ASSERT(IS_EXMC_NFC_COLUMN(u32Col));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enEccState));

        /* Check parameters */
        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank) | \
                           EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERROR | \
                           EXMC_NFC_FLAG_ECC_CORRECTABLE_ERROR | \
                           EXMC_NFC_FLAG_ECC_CALC_COMPLETION | \
                           EXMC_NFC_FLAG_ECC_ERROR);

        /* Clear Flag */
        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

        if (Enable == enEccState)
        {
            EXMC_NFC_EccCmd(Enable);
        }
        else
        {
            EXMC_NFC_EccCmd(Disable);
        }

        u64Val = (NFC_IDXR_VAL(u32Bank, u32Page, u32Col, u32CapacityIndex) & NFC_IDXR_MASK);

        /* Write page step:
            1. Write 0x00000080 to NFC_CMDR
            2. Write NAND Flash address to NFC_IDXR0/1
            3. Write NFC_DATR
            4. Write 0x00000010 to NFC_CMDR
            5. Wait RB signal until high level
            6. Write 0x000000FE to NFC_CMDR, and invalidate CE */

        /* 1. Write 0x00000080 to NFC_CMDR */
        WRITE_REG32(M4_NFC->CMDR, EXMC_NFC_CMD_PAGE_PROGRAM_1ST);

        /* 2. Write NAND Flash address to NFC_IDXR0/1 */
        WRITE_REG32(M4_NFC->IDXR0, (uint32_t)(u64Val & 0xFFFFFFFFUL));
        WRITE_REG32(M4_NFC->IDXR1, (uint32_t)(u64Val >> 32UL));

        /* 3. Write NFC_DATR */
        for (i = 0UL; i < u32NumWords; i++)
        {
            NFC_DATR_REG32(i) = au32Data[i];
        }

        /* 4. Write 0x00000010 to NFC_CMDR */
        WRITE_REG32(M4_NFC->CMDR, EXMC_NFC_CMD_PAGE_PROGRAM_2ND);

        /* 5. Wait RB signal until high level */
        enRet = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), \
                                         Set, \
                                         u32Timeout);

        /* Write 0x000000FE to NFC_CMDR, and invalidate CE */
        EXMC_NFC_DeselectChip();

        if (Enable == enEccState)
        {
            EXMC_NFC_EccCmd(Disable);
        }
    }

    return enRet;
}

/**
 * @brief  Get capacity size.
 * @param  None
 * @retval Capacity index
 *   @arg NFC_CAPACITY_INDEX_512MBIT: NFC device capacity 512MBit
 *   @arg NFC_CAPACITY_INDEX_1GBIT: NFC device capacity 1GBit
 *   @arg NFC_CAPACITY_INDEX_2GBIT: NFC device capacity 2GBit
 *   @arg NFC_CAPACITY_INDEX_4GBIT: NFC device capacity 4GBit
 *   @arg NFC_CAPACITY_INDEX_8GBIT: NFC device capacity 8GBit
 *   @arg NFC_CAPACITY_INDEX_16GBIT: NFC device capacity 16GBit
 *   @arg NFC_CAPACITY_INDEX_32GBIT: NFC device capacity 32GBit
 *   @arg NFC_CAPACITY_INDEX_64GBIT: NFC device capacity 64GBit
 */
static uint32_t EXMC_NFC_GetCapacityIndex(void)
{
    uint32_t u32Index;
    const uint32_t u32BacrSize = READ_REG32_BIT(M4_NFC->BACR, NFC_BACR_SIZE);

    switch (u32BacrSize)
    {
        case EXMC_NFC_BANK_CAPACITY_512MBIT:
            u32Index = NFC_CAPACITY_INDEX_512MBIT;
            break;
        case EXMC_NFC_BANK_CAPACITY_1GBIT:
            u32Index = NFC_CAPACITY_INDEX_1GBIT;
            break;
        case EXMC_NFC_BANK_CAPACITY_2GBIT:
            u32Index = NFC_CAPACITY_INDEX_2GBIT;
            break;
        case EXMC_NFC_BANK_CAPACITY_4GBIT:
            u32Index = NFC_CAPACITY_INDEX_4GBIT;
            break;
        case EXMC_NFC_BANK_CAPACITY_8GBIT:
            u32Index = NFC_CAPACITY_INDEX_8GBIT;
            break;
        case EXMC_NFC_BANK_CAPACITY_16GBIT:
            u32Index = NFC_CAPACITY_INDEX_16GBIT;
            break;
        case EXMC_NFC_BANK_CAPACITY_32GBIT:
            u32Index = NFC_CAPACITY_INDEX_32GBIT;
            break;
        default:
            u32Index = NFC_CAPACITY_INDEX_64GBIT;
            break;
    }

    return u32Index;
}

/**
 * @brief  Wait the specified flag with timeout.
 * @param  [in] u32Flag                 The specified flag
 *   @arg EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERROR: ECC uncorrectable error
 *   @arg EXMC_NFC_FLAG_ECC_CORRECTABLE_ERROR: ECC correctable error
 *   @arg EXMC_NFC_FLAG_ECC_CALC_COMPLETION: Calculating ECC completely
 *   @arg EXMC_NFC_FLAG_ECC_ERROR: ECC error
 *   @arg EXMC_NFC_FLAG_RB_BANK0: NFC device bank 0 busy flag
 *   @arg EXMC_NFC_FLAG_RB_BANK1: NFC device bank 1 busy flag
 *   @arg EXMC_NFC_FLAG_RB_BANK2: NFC device bank 2 busy flag
 *   @arg EXMC_NFC_FLAG_RB_BANK3: NFC device bank 3 busy flag
 *   @arg EXMC_NFC_FLAG_RB_BANK4: NFC device bank 4 busy flag
 *   @arg EXMC_NFC_FLAG_RB_BANK5: NFC device bank 5 busy flag
 *   @arg EXMC_NFC_FLAG_RB_BANK6: NFC device bank 6 busy flag
 *   @arg EXMC_NFC_FLAG_RB_BANK7: NFC device bank 7 busy flag
 * @param  enStatus                     The waiting flag status (SET or RESET).
 * @param  u32Timeout                   Timeout duration
 * @retval An en_result_t enumeration value:
 *   @arg  Ok: Flag is right
 *   @arg  ErrorTimeout: Wait timeout
 * @note Block checking flag if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
static en_result_t EXMC_NFC_WaitFlagUntilTo(uint32_t u32Flag,
                                                    en_flag_status_t enStatus,
                                                    uint32_t u32Timeout)
{
    en_result_t enRet = Ok;
    __IO uint32_t u32To = 0UL;

    /* Check parameters */
    DDL_ASSERT(IS_EXMC_NFC_FLAG(u32Flag));

    while (EXMC_NFC_GetStatus(u32Flag) != enStatus)
    {
        /* Block checking flag if timeout value is EXMC_NFC_MAX_TIMEOUT */
        if ((u32To++ > u32Timeout) && (u32Timeout < EXMC_NFC_MAX_TIMEOUT))
        {
            enRet = ErrorTimeout;
            break;
        }
    }

    return enRet;
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
