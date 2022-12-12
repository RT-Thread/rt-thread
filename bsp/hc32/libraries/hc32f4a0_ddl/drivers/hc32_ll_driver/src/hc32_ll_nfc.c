/**
 *******************************************************************************
 * @file  hc32_ll_nfc.c
 * @brief This file provides firmware functions to manage the EXMC NFC
 *        (External Memory Controller: NAND Flash Controller) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <string.h>
#include "hc32_ll_nfc.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_EXMC EXMC
 * @brief External Memory Controller Driver Library
 * @{
 */

/**
 * @defgroup LL_NFC NFC
 * @brief NAND Flash Controller Driver Library
 * @{
 */

#if (LL_NFC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EXMC_NFC_Local_Macros EXMC_NFC Local Macros
 * @{
 */

/**
 * @defgroup EXMC_NFC_Check_Parameters_Validity EXMC_NFC Check Parameters Validity
 * @{
 */

#define IS_EXMC_NFC_BANK(x)                 ((x) <= EXMC_NFC_BANK7)

#define IS_EXMC_NFC_MEMORY_WIDTH(x)                                            \
(   ((x) == EXMC_NFC_MEMORY_WIDTH_8BIT)     ||                                 \
    ((x) == EXMC_NFC_MEMORY_WIDTH_16BIT))

#define IS_EXMC_NFC_BANK_CAPACITY(x)                                           \
(   ((x) == EXMC_NFC_BANK_CAPACITY_1GBIT)   ||                                 \
    ((x) == EXMC_NFC_BANK_CAPACITY_2GBIT)   ||                                 \
    ((x) == EXMC_NFC_BANK_CAPACITY_4GBIT)   ||                                 \
    ((x) == EXMC_NFC_BANK_CAPACITY_8GBIT)   ||                                 \
    ((x) == EXMC_NFC_BANK_CAPACITY_16GBIT)  ||                                 \
    ((x) == EXMC_NFC_BANK_CAPACITY_32GBIT)  ||                                 \
    ((x) == EXMC_NFC_BANK_CAPACITY_64GBIT)  ||                                 \
    ((x) == EXMC_NFC_BANK_CAPACITY_512MBIT))

#define IS_EXMC_NFC_PAGE_SIZE(x)                                               \
(   ((x) == EXMC_NFC_PAGE_SIZE_2KBYTE)      ||                                 \
    ((x) == EXMC_NFC_PAGE_SIZE_4KBYTE)      ||                                 \
    ((x) == EXMC_NFC_PAGE_SIZE_8KBYTE))

#define IS_EXMC_NFC_BANK_NUM(x)                                                \
(   ((x) == EXMC_NFC_1BANK)                 ||                                 \
    ((x) == EXMC_NFC_2BANKS)                ||                                 \
    ((x) == EXMC_NFC_4BANKS)                ||                                 \
    ((x) == EXMC_NFC_8BANKS))

#define IS_EXMC_NFC_WR_PROTECT(x)                                              \
(   ((x) == EXMC_NFC_WR_PROTECT_ENABLE)     ||                                 \
    ((x) == EXMC_NFC_WR_PROTECT_DISABLE))

#define IS_EXMC_NFC_ECC_MD(x)                                                  \
(   ((x) == EXMC_NFC_1BIT_ECC)              ||                                 \
    ((x) == EXMC_NFC_4BIT_ECC))

#define IS_EXMC_NFC_ROW_ADDR_CYCLES(x)                                         \
(   ((x) == EXMC_NFC_2_ROW_ADDR_CYCLE)      ||                                 \
    ((x) == EXMC_NFC_3_ROW_ADDR_CYCLE))

#define IS_EXMC_NFC_SECTION(x)              ((x) <= EXMC_NFC_ECC_SECTION15)

#define IS_EXMC_NFC_INT(x)                                                     \
(   ((x) != 0UL)                            &&                                 \
    (((x) | EXMC_NFC_INT_MASK) == EXMC_NFC_INT_MASK))

#define IS_EXMC_NFC_FLAG(x)                                                    \
(   ((x) != 0UL)                            &&                                 \
    (((x) | EXMC_NFC_FLAG_MASK) == EXMC_NFC_FLAG_MASK))

#define IS_EXMC_NFC_TIMING_TS(x)            ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TWP(x)           ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TRP(x)           ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TH(x)            ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TWH(x)           ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TRH(x)           ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TRR(x)           ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TWB(x)           ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TCCS(x)          ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TWTR(x)          ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TRTW(x)          ((x) <= 0xFFUL)

#define IS_EXMC_NFC_TIMING_TADL(x)          ((x) <= 0xFFUL)

#define IS_EXMC_NFC_COLUMN(x)               ((x) <= NFC_COLUMN_MAX)

#define IS_EXMC_NFC_PAGE(page, capacity_index)  ((page) <= NFC_PAGE_MAX((capacity_index)))

#define IS_PARAM_ALIGN_WORD(x)              (IS_ADDR_ALIGN_WORD((x)))
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Interrupt_Mask EXMC_NFC Interrupt Mask
 * @{
 */
#define EXMC_NFC_INT_MASK                                                      \
(   EXMC_NFC_INT_RB_BANK0                   |                                  \
    EXMC_NFC_INT_RB_BANK1                   |                                  \
    EXMC_NFC_INT_RB_BANK2                   |                                  \
    EXMC_NFC_INT_RB_BANK3                   |                                  \
    EXMC_NFC_INT_RB_BANK4                   |                                  \
    EXMC_NFC_INT_RB_BANK5                   |                                  \
    EXMC_NFC_INT_RB_BANK6                   |                                  \
    EXMC_NFC_INT_RB_BANK7                   |                                  \
    EXMC_NFC_INT_ECC_ERROR                  |                                  \
    EXMC_NFC_INT_ECC_CALC_COMPLETION        |                                  \
    EXMC_NFC_INT_ECC_CORRECTABLE_ERR        |                                  \
    EXMC_NFC_INT_ECC_UNCORRECTABLE_ERR)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Flag_Mask EXMC_NFC Flag Mask
 * @{
 */
#define EXMC_NFC_FLAG_MASK                                                     \
(   EXMC_NFC_FLAG_RB_BANK0                  |                                  \
    EXMC_NFC_FLAG_RB_BANK1                  |                                  \
    EXMC_NFC_FLAG_RB_BANK2                  |                                  \
    EXMC_NFC_FLAG_RB_BANK3                  |                                  \
    EXMC_NFC_FLAG_RB_BANK4                  |                                  \
    EXMC_NFC_FLAG_RB_BANK5                  |                                  \
    EXMC_NFC_FLAG_RB_BANK6                  |                                  \
    EXMC_NFC_FLAG_RB_BANK7                  |                                  \
    EXMC_NFC_FLAG_ECC_ERR                   |                                  \
    EXMC_NFC_FLAG_ECC_CALCULATING           |                                  \
    EXMC_NFC_FLAG_ECC_CALC_COMPLETION       |                                  \
    EXMC_NFC_FLAG_ECC_CORRECTABLE_ERR       |                                  \
    EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERR)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Memory_Capacity_Index EXMC_NFC Memory Capacity Index
 * @{
 */
#define NFC_CAPACITY_INDEX_512MBIT          (0UL)
#define NFC_CAPACITY_INDEX_1GBIT            (1UL)
#define NFC_CAPACITY_INDEX_2GBIT            (2UL)
#define NFC_CAPACITY_INDEX_4GBIT            (3UL)
#define NFC_CAPACITY_INDEX_8GBIT            (4UL)
#define NFC_CAPACITY_INDEX_16GBIT           (5UL)
#define NFC_CAPACITY_INDEX_32GBIT           (6UL)
#define NFC_CAPACITY_INDEX_64GBIT           (7UL)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Command_Regster_Value EXMC_NFC Command Regster Value
 * @{
 */
/*!< Command value */
#define NFC_CMD_VALUE(arg, bank, cmd)       ((arg) | ((bank) << 8U) | (cmd))

/*!< Command: Read status */
#define NFC_ADDR_VALUE(bank, addr)          (0x40000000UL | ((bank) << 8U) | (addr))

/*!< Command: Read status */
#define CMD_RESET(bank)                     (NFC_CMD_VALUE(0UL, (bank), EXMC_NFC_CMD_RESET))

/*!< Command: Read status */
#define CMD_ASYNC_RESET(bank)               (NFC_CMD_VALUE(0x82000000UL, (bank), EXMC_NFC_CMD_ASYNCHRONOUS_RST))

/*!< Command: Read status */
#define CMD_RESET_LUN(bank)                 (NFC_CMD_VALUE(0x82000000UL, (bank), EXMC_NFC_CMD_RST_LUN))

/*!< Command: Read status */
#define CMD_READ_STATUS(bank)               (NFC_CMD_VALUE(0x81000000UL, (bank), EXMC_NFC_CMD_RD_STATUS))

/*!< Command: Read status */
#define CMD_READ_STATUS_ENHANCED(bank)      (NFC_CMD_VALUE(0x80000000UL, (bank), EXMC_NFC_CMD_RD_STATUS_ENHANCED))

/*!< Command: Read ID */
#define CMD_READ_ID(bank)                   (NFC_CMD_VALUE(0x81000000UL, (bank), EXMC_NFC_CMD_RD_ID))
#define CMD_READ_ID_ADDR(bank, addr)        (NFC_ADDR_VALUE((bank), (addr)))

/*!< Command: Read unique ID */
#define CMD_READ_UNIQUEID(bank)             (NFC_CMD_VALUE(0x83000000UL, (bank), EXMC_NFC_CMD_RD_UNIQUE_ID))
#define CMD_READ_UNIQUEID_ADDR(bank)        (NFC_ADDR_VALUE((bank), 0UL))

/*!< Command: Erase block */
#define CMD_ERASE_BLOCK_1ST_CYCLE(bank)     (NFC_CMD_VALUE(0x81000000UL, (bank), EXMC_NFC_CMD_BLK_ERASE_1ST))
#define CMD_ERASE_BLOCK_2ND_CYCLE(bank)     (NFC_CMD_VALUE(0x81000000UL, (bank), EXMC_NFC_CMD_BLK_ERASE_2ND))

/*!< Command: Read parameter page */
#define CMD_READ_PARAMETER_PAGE(bank)       (NFC_CMD_VALUE(0x83000000UL, (bank), EXMC_NFC_CMD_RD_PARAMETER_PAGE))
#define CMD_READ_PARAMETER_PAGE_ADDR(bank)  (NFC_ADDR_VALUE((bank), 0UL))

/*!< Command: Set feature */
#define CMD_SET_FEATURE(bank)               (NFC_CMD_VALUE(0x83000000UL, (bank), EXMC_NFC_CMD_SET_FEATURES))
#define CMD_SET_FEATURE_ADDR(bank, addr)    (NFC_ADDR_VALUE((bank), (addr)))

/*!< Command: Get feature */
#define CMD_GET_FEATURE(bank)               (NFC_CMD_VALUE(0x83000000UL, (bank), EXMC_NFC_CMD_GET_FEATURES))
#define CMD_GET_FEATURE_ADDR(bank, addr)    (NFC_ADDR_VALUE((bank), (addr)))

/*!< Command: Address cycle */
#define CMD_ADDR_1ST_CYCLE(bank, ras)       (NFC_ADDR_VALUE((bank), ((ras) & 0xFFUL)))
#define CMD_ADDR_2ND_CYCLE(bank, ras)       (NFC_ADDR_VALUE((bank), (((ras) & 0xFF00UL) >> 8UL)))
#define CMD_ADDR_3RD_CYCLE(bank, ras)       (NFC_ADDR_VALUE((bank), (((ras) & 0xFF0000UL) >> 16UL)))

/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_IDXR_Bit_Position EXMC_NFC IDXR Bit Position
 * @{
 */
#define EXMC_NFC_IDXR_COL_POS               (0U)
#define EXMC_NFC_IDXR_2KPAGE_POS            (12U)
#define EXMC_NFC_IDXR_512MBIT_BANK_POS      (27U)
/**
 * @}
 */

/*!< NFC BACR regsiter: page field value */
#define NFC_BACR_PAGE_VAL                   ((uint8_t)((READ_REG32_BIT(CM_NFC->BACR, NFC_BACR_PAGE) >> NFC_BACR_PAGE_POS) & 0x3UL))

/*!< NFC Page Size */
#define NFC_PAGE_SIZE                       (1024UL << NFC_BACR_PAGE_VAL)

/*!< NFC page max for the specified capacity */
#define NFC_PAGE_MAX(capacity_index)        ((1UL << (19U + (uint8_t)(capacity_index) - NFC_BACR_PAGE_VAL)) - 1UL)

/*!< NFC column max */
#define NFC_COLUMN_MAX                      ((1UL << (EXMC_NFC_IDXR_2KPAGE_POS + NFC_BACR_PAGE_VAL - 1U)) - 1UL)

/*!< NFC Spare Size for user data */
#define NFC_SPARE_SIZE_FOR_USER_DATA        ((READ_REG32_BIT(CM_NFC->BACR, NFC_BACR_SCS) >> NFC_BACR_SCS_POS) << 2UL)

/*!< NFC_ISTR register RBST bit mask */
#define NFC_FLAG_RB_BANKx_MASK(bank)        (EXMC_NFC_FLAG_RB_BANK0 << (EXMC_NFC_BANK7 & (bank)))

/*!< IDX register mask for 64bit */
#define NFC_NFC_ISTR_MASK                   (0xFF53UL)

/*!< NFC_DATR for 32bit */
#define NFC_DATR_REG32(x)                   (CM_NFC->DATR_BASE)

/**
 * @defgroup EXMC_NFC_ECC_Reference EXMC_NFC ECC Reference
 * @{
 */
/*!< NFC_SYND_REG for 32bit */
#define NFC_SYND_REG32(sect, reg)           (*((__IO uint32_t *)((uint32_t)(&(CM_NFC->ECC_SYND0_0)) + (((uint32_t)(sect)) << 4UL) + (((uint32_t)(reg)) << 2UL))))

/*!< NFC_ECCR_REG for 32bit */
#define NFC_ECCR_REG32(sect)                (*((__IO uint32_t *)((uint32_t)(&(CM_NFC->ECCR0))   + (((uint32_t)(sect)) << 2UL))))

/*!< NFC_SYND_MAX_Length (Unit: half-word ) */
#define NFC_SYND_MAX_LEN                    (8U)

/*!< NFC 1Bit ECC Error Bit Mask */
#define NFC_1BIT_ECC_ERR_BIT_MASK           (0x7U)

/*!< NFC 1Bit ECC Error Byte Position */
#define NFC_1BIT_ECC_ERR_BYTE_POS           (3U)
/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_IDXR_Register_Reference EXMC_NFC IDXR Register Reference
 * @note capacity_index @ref EXMC_NFC_Memory_Capacity_Index
 * @{
 */
/*!< IDX register value for 64bit */
#define NFC_IDXR_VAL(bank, page, col, capacity_index)                          \
(   (((uint64_t)(col)) << EXMC_NFC_IDXR_COL_POS) |                             \
    (((uint64_t)(page)) << (EXMC_NFC_IDXR_2KPAGE_POS + NFC_BACR_PAGE_VAL - 1U)) | \
    (((uint64_t)(bank)) << (EXMC_NFC_IDXR_512MBIT_BANK_POS + (uint8_t)(capacity_index))))

/*!< IDX register mask for 64bit */
#define NFC_IDXR_MASK                       (0x1FFFFFFFFFULL)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup EXMC_NFC_Local_Functions EXMC_NFC Local Functions
 * @{
 */

/**
 * @brief  Get capacity size.
 * @param  None
 * @retval Capacity index @ref EXMC_NFC_Memory_Capacity_Index
 *           - NFC_CAPACITY_INDEX_512MBIT:  NFC device capacity 512MBit
 *           - NFC_CAPACITY_INDEX_1GBIT:    NFC device capacity 1GBit
 *           - NFC_CAPACITY_INDEX_2GBIT:    NFC device capacity 2GBit
 *           - NFC_CAPACITY_INDEX_4GBIT:    NFC device capacity 4GBit
 *           - NFC_CAPACITY_INDEX_8GBIT:    NFC device capacity 8GBit
 *           - NFC_CAPACITY_INDEX_16GBIT:   NFC device capacity 16GBit
 *           - NFC_CAPACITY_INDEX_32GBIT:   NFC device capacity 32GBit
 *           - NFC_CAPACITY_INDEX_64GBIT:   NFC device capacity 64GBit
 */
static uint32_t EXMC_NFC_GetCapacityIndex(void)
{
    uint32_t u32Index;
    const uint32_t u32BacrSize = READ_REG32_BIT(CM_NFC->BACR, NFC_BACR_SIZE);

    switch (u32BacrSize) {
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
 *   @arg EXMC_NFC_FLAG_RB_BANK0:       NFC device bank 0 busy flag
 *   @arg EXMC_NFC_FLAG_RB_BANK1:       NFC device bank 1 busy flag
 *   @arg EXMC_NFC_FLAG_RB_BANK2:       NFC device bank 2 busy flag
 *   @arg EXMC_NFC_FLAG_RB_BANK3:       NFC device bank 3 busy flag
 *   @arg EXMC_NFC_FLAG_RB_BANK4:       NFC device bank 4 busy flag
 *   @arg EXMC_NFC_FLAG_RB_BANK5:       NFC device bank 5 busy flag
 *   @arg EXMC_NFC_FLAG_RB_BANK6:       NFC device bank 6 busy flag
 *   @arg EXMC_NFC_FLAG_RB_BANK7:       NFC device bank 7 busy flag
 *   @arg EXMC_NFC_FLAG_ECC_ERR:        ECC error
 *   @arg EXMC_NFC_FLAG_ECC_CALC_COMPLETION: Calculating ECC completely
 *   @arg EXMC_NFC_FLAG_ECC_CORRECTABLE_ERR: ECC correctable error
 *   @arg EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERR: ECC uncorrectable error
 * @param  enStatus                     The waiting flag status (SET or RESET).
 * @param  u32Timeout                   Timeout duration(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   Complete wait the expected status of the specified flags.
 *           - LL_ERR_TIMEOUT:          Wait timeout.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT.
 */
static int32_t EXMC_NFC_WaitFlagUntilTo(uint32_t u32Flag, en_flag_status_t enStatus, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32To = 0UL;

    DDL_ASSERT(IS_EXMC_NFC_FLAG(u32Flag));

    while (EXMC_NFC_GetStatus(u32Flag) != enStatus) {
        /* Block checking flag if timeout value is EXMC_NFC_MAX_TIMEOUT */
        if ((u32To > u32Timeout) && (u32Timeout < EXMC_NFC_MAX_TIMEOUT)) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }

        u32To++;
    }

    return i32Ret;
}

/**
 * @brief  NFC read operation
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u32Page                 The specified page
 * @param  [in] u32Col                  The column address
 * @param  [out] au32Data               The buffer for reading
 * @param  [in] u32NumWords             The buffer size for words
 * @param  [in] enEccState              Disable/enable ECC function
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Write timeout.
 *           - LL_ERR_INVD_PARAM:       The pointer au32Data value is NULL or u32NumWords is 0.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT.
 */
static int32_t EXMC_NFC_Read(uint32_t u32Bank, uint32_t u32Page, uint32_t u32Col,
                             uint32_t au32Data[], uint32_t u32NumWords,
                             en_functional_state_t enEccState, uint32_t u32Timeout)
{
    uint32_t i;
    uint64_t u64Value;
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    const uint32_t u32CapacityIndex = EXMC_NFC_GetCapacityIndex();

    if ((NULL != au32Data) && (u32NumWords > 0UL)) {
        DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));
        DDL_ASSERT(IS_EXMC_NFC_PAGE(u32Page, u32CapacityIndex));
        DDL_ASSERT(IS_EXMC_NFC_COLUMN(u32Col));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enEccState));

        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank) | EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERR | \
                             EXMC_NFC_FLAG_ECC_CORRECTABLE_ERR | EXMC_NFC_FLAG_ECC_CALC_COMPLETION | EXMC_NFC_FLAG_ECC_ERR);

        EXMC_NFC_EccCmd(enEccState);

        /* Read page step:
            1. Write 0x00000000 to NFC_CMDR
            2. Write NAND Flash address to NFC_IDXR0/1
            3. Write 0x000000E0 to NFC_CMDR
            4. Wait RB signal until high level
            5. Read NFC_DATR
            6. Write 0x000000FE to NFC_CMDR, and invalidate CE */

        /* 1. Write 0x00000000 to NFC_CMDR */
        WRITE_REG32(CM_NFC->CMDR, EXMC_NFC_CMD_RD_1ST);

        /* 2. Write NAND Flash address to NFC_IDXR0/1 */
        u64Value = (NFC_IDXR_VAL(u32Bank, u32Page, u32Col, u32CapacityIndex) & NFC_IDXR_MASK);
        WRITE_REG32(CM_NFC->IDXR0, (uint32_t)(u64Value & 0xFFFFFFFFUL));
        WRITE_REG32(CM_NFC->IDXR1, (uint32_t)(u64Value >> 32UL));

        /* 3. Write 0x000000E0 to NFC_CMDR */
        WRITE_REG32(CM_NFC->CMDR, EXMC_NFC_CMD_RD_2ND);

        /* 4. Wait RB signal until high level */
        i32Ret = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), SET, u32Timeout);
        if (LL_OK == i32Ret) {
            /* 5. Read NFC_DATR */
            for (i = 0UL; i < u32NumWords; i++) {
                au32Data[i] = NFC_DATR_REG32(i);
            }

            /* Clear Flag */
            EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

            if (ENABLE == enEccState) {
                /* Write 0x00000023 to NFC_CMDR */
                WRITE_REG32(CM_NFC->CMDR, EXMC_NFC_CMD_CALCULATE_ECC);

                /* 4. Wait RB signal until high level */
                i32Ret = EXMC_NFC_WaitFlagUntilTo(EXMC_NFC_FLAG_ECC_CALCULATING, RESET, u32Timeout);
                EXMC_NFC_EccCmd(DISABLE);
            }
        }

        /* 6. Write 0x000000FE to NFC_CMDR, and invalidate CE */
        EXMC_NFC_DeselectChip();
    }

    return i32Ret;
}

/**
 * @brief  NFC write operation
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u32Page                 The specified page
 * @param  [in] u32Col                  The column address
 * @param  [in] au32Data                The buffer for writing
 * @param  [in] u32NumWords             The buffer size for words
 * @param  [in] enEccState              Disable/enable ECC function
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Write timeout.
 *           - LL_ERR_INVD_PARAM:       The pointer au32Data value is NULL or u32NumWords is 0.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT.
 */
static int32_t EXMC_NFC_Write(uint32_t u32Bank, uint32_t u32Page, uint32_t u32Col,
                              const uint32_t au32Data[], uint32_t u32NumWords,
                              en_functional_state_t enEccState, uint32_t u32Timeout)
{
    uint32_t i;
    uint64_t u64Value;
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    const uint32_t u32CapacityIndex = EXMC_NFC_GetCapacityIndex();

    if ((NULL != au32Data) && (u32NumWords > 0UL)) {
        DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));
        DDL_ASSERT(IS_EXMC_NFC_PAGE(u32Page, u32CapacityIndex));
        DDL_ASSERT(IS_EXMC_NFC_COLUMN(u32Col));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enEccState));

        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank) | EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERR | \
                             EXMC_NFC_FLAG_ECC_CORRECTABLE_ERR | EXMC_NFC_FLAG_ECC_CALC_COMPLETION | EXMC_NFC_FLAG_ECC_ERR);

        EXMC_NFC_EccCmd(enEccState);

        /* Write page step:
            1. Write 0x00000080 to NFC_CMDR
            2. Write NAND Flash address to NFC_IDXR0/1
            3. Write NFC_DATR
            4. Write 0x00000010 to NFC_CMDR
            5. Wait RB signal until high level
            6. Write 0x000000FE to NFC_CMDR, and invalidate CE */

        /* 1. Write 0x00000080 to NFC_CMDR */
        WRITE_REG32(CM_NFC->CMDR, EXMC_NFC_CMD_PAGE_PROGRAM_1ST);

        /* 2. Write NAND Flash address to NFC_IDXR0/1 */
        u64Value = (NFC_IDXR_VAL(u32Bank, u32Page, u32Col, u32CapacityIndex) & NFC_IDXR_MASK);
        WRITE_REG32(CM_NFC->IDXR0, (uint32_t)(u64Value & 0xFFFFFFFFUL));
        WRITE_REG32(CM_NFC->IDXR1, (uint32_t)(u64Value >> 32UL));

        /* 3. Write NFC_DATR */
        for (i = 0UL; i < u32NumWords; i++) {
            NFC_DATR_REG32(i) = au32Data[i];
        }

        /* 4. Write 0x00000010 to NFC_CMDR */
        WRITE_REG32(CM_NFC->CMDR, EXMC_NFC_CMD_PAGE_PROGRAM_2ND);

        /* 5. Wait RB signal until high level */
        i32Ret = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), SET, u32Timeout);

        /* Write 0x000000FE to NFC_CMDR, and invalidate CE */
        EXMC_NFC_DeselectChip();

        if (ENABLE == enEccState) {
            EXMC_NFC_EccCmd(DISABLE);
        }
    }

    return i32Ret;
}

/**
 * @}
 */

/**
 * @defgroup EXMC_NFC_Global_Functions EXMC_NFC Global Functions
 * @{
 */

/**
 * @brief  Set the fields of structure stc_exmc_nfc_init_t to default values
 * @param  [out] pstcNfcInit            Pointer to a @ref stc_exmc_nfc_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcNfcInit value is NULL.
 */
int32_t EXMC_NFC_StructInit(stc_exmc_nfc_init_t *pstcNfcInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcNfcInit) {
        pstcNfcInit->stcBaseConfig.u32CapacitySize = EXMC_NFC_BANK_CAPACITY_8GBIT;
        pstcNfcInit->stcBaseConfig.u32MemoryWidth = EXMC_NFC_MEMORY_WIDTH_8BIT;
        pstcNfcInit->stcBaseConfig.u32BankNum = EXMC_NFC_4BANKS;
        pstcNfcInit->stcBaseConfig.u32PageSize = EXMC_NFC_PAGE_SIZE_2KBYTE;
        pstcNfcInit->stcBaseConfig.u32WriteProtect = EXMC_NFC_WR_PROTECT_ENABLE;
        pstcNfcInit->stcBaseConfig.u32EccMode = EXMC_NFC_1BIT_ECC;
        pstcNfcInit->stcBaseConfig.u32RowAddrCycle = EXMC_NFC_3_ROW_ADDR_CYCLE;
        pstcNfcInit->stcBaseConfig.u8SpareSizeForUserData = 0U;

        pstcNfcInit->stcTimingReg0.u32TS = 0x02UL;
        pstcNfcInit->stcTimingReg0.u32TWP = 0x02UL;
        pstcNfcInit->stcTimingReg0.u32TRP = 0x03UL;
        pstcNfcInit->stcTimingReg0.u32TH = 0x03UL;

        pstcNfcInit->stcTimingReg1.u32TWH = 0x03UL;
        pstcNfcInit->stcTimingReg1.u32TRH = 0x03UL;
        pstcNfcInit->stcTimingReg1.u32TRR = 0x02UL;
        pstcNfcInit->stcTimingReg1.u32TWB = 0x28UL;

        pstcNfcInit->stcTimingReg2.u32TCCS = 0x03UL;
        pstcNfcInit->stcTimingReg2.u32TWTR = 0x0DUL;
        pstcNfcInit->stcTimingReg2.u32TRTW = 0x05UL;
        pstcNfcInit->stcTimingReg2.u32TADL = 0x03UL;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize EXMC_NFC function.
 * @param  [in] pstcNfcInit             Pointer to a @ref stc_exmc_nfc_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcNfcInit value is NULL.
 */
int32_t EXMC_NFC_Init(const stc_exmc_nfc_init_t *pstcNfcInit)
{
    uint32_t u32RegVal;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcNfcInit) {
        DDL_ASSERT(IS_EXMC_NFC_BANK_CAPACITY(pstcNfcInit->stcBaseConfig.u32CapacitySize));
        DDL_ASSERT(IS_EXMC_NFC_MEMORY_WIDTH(pstcNfcInit->stcBaseConfig.u32MemoryWidth));
        DDL_ASSERT(IS_EXMC_NFC_BANK_NUM(pstcNfcInit->stcBaseConfig.u32BankNum));
        DDL_ASSERT(IS_EXMC_NFC_PAGE_SIZE(pstcNfcInit->stcBaseConfig.u32PageSize));
        DDL_ASSERT(IS_EXMC_NFC_WR_PROTECT(pstcNfcInit->stcBaseConfig.u32WriteProtect));
        DDL_ASSERT(IS_EXMC_NFC_ECC_MD(pstcNfcInit->stcBaseConfig.u32EccMode));
        DDL_ASSERT(IS_EXMC_NFC_ROW_ADDR_CYCLES(pstcNfcInit->stcBaseConfig.u32RowAddrCycle));

        DDL_ASSERT(IS_EXMC_NFC_TIMING_TS(pstcNfcInit->stcTimingReg0.u32TS));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TWP(pstcNfcInit->stcTimingReg0.u32TWP));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TRP(pstcNfcInit->stcTimingReg0.u32TRP));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TH(pstcNfcInit->stcTimingReg0.u32TH));

        DDL_ASSERT(IS_EXMC_NFC_TIMING_TWH(pstcNfcInit->stcTimingReg1.u32TWH));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TRH(pstcNfcInit->stcTimingReg1.u32TRH));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TRR(pstcNfcInit->stcTimingReg1.u32TRR));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TWB(pstcNfcInit->stcTimingReg1.u32TWB));

        DDL_ASSERT(IS_EXMC_NFC_TIMING_TCCS(pstcNfcInit->stcTimingReg2.u32TCCS));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TWTR(pstcNfcInit->stcTimingReg2.u32TWTR));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TRTW(pstcNfcInit->stcTimingReg2.u32TRTW));
        DDL_ASSERT(IS_EXMC_NFC_TIMING_TADL(pstcNfcInit->stcTimingReg2.u32TADL));

        /* Set NFC open-page.*/
        WRITE_REG32(CM_PERIC->NFC_STCR, pstcNfcInit->u32OpenPage);

        /* Disable hardware ECC.*/
        WRITE_REG32(CM_NFC->IENR, 0x00000080UL);

        /* Clear flag.*/
        WRITE_REG32(CM_NFC->ISTR, 0x00000000UL);

        /* Set NFC base configure.*/
        u32RegVal = (pstcNfcInit->stcBaseConfig.u32CapacitySize | pstcNfcInit->stcBaseConfig.u32MemoryWidth | \
                     pstcNfcInit->stcBaseConfig.u32BankNum      | pstcNfcInit->stcBaseConfig.u32PageSize | \
                     pstcNfcInit->stcBaseConfig.u32WriteProtect | pstcNfcInit->stcBaseConfig.u32EccMode | \
                     pstcNfcInit->stcBaseConfig.u32RowAddrCycle | \
                     (((uint32_t)pstcNfcInit->stcBaseConfig.u8SpareSizeForUserData) << NFC_BACR_SCS_POS));
        WRITE_REG32(CM_NFC->BACR, u32RegVal);

        /* Set NFC timing register 0.*/
        u32RegVal = ((pstcNfcInit->stcTimingReg0.u32TS << NFC_TMCR0_TS_POS)   | \
                     (pstcNfcInit->stcTimingReg0.u32TWP << NFC_TMCR0_TWP_POS) | \
                     (pstcNfcInit->stcTimingReg0.u32TRP << NFC_TMCR0_TRP_POS) | \
                     (pstcNfcInit->stcTimingReg0.u32TH << NFC_TMCR0_TH_POS));
        WRITE_REG32(CM_NFC->TMCR0, u32RegVal);

        /* Set NFC timing register 1.*/
        u32RegVal = ((pstcNfcInit->stcTimingReg1.u32TWH << NFC_TMCR1_TWH_POS) | \
                     (pstcNfcInit->stcTimingReg1.u32TRH << NFC_TMCR1_TRH_POS) | \
                     (pstcNfcInit->stcTimingReg1.u32TRR << NFC_TMCR1_TRR_POS) | \
                     (pstcNfcInit->stcTimingReg1.u32TWB << NFC_TMCR1_TWB_POS));
        WRITE_REG32(CM_NFC->TMCR1, u32RegVal);

        /* Set NFC timing register 2.*/
        u32RegVal = ((pstcNfcInit->stcTimingReg2.u32TCCS << NFC_TMCR2_TCCS_POS) | \
                     (pstcNfcInit->stcTimingReg2.u32TWTR << NFC_TMCR2_TWTR_POS) | \
                     (pstcNfcInit->stcTimingReg2.u32TRTW << NFC_TMCR2_TRTW_POS) | \
                     (pstcNfcInit->stcTimingReg2.u32TADL << NFC_TMCR2_TADL_POS));
        WRITE_REG32(CM_NFC->TMCR2, u32RegVal);

        /* De-select NFC bank */
        WRITE_REG32(CM_NFC->CMDR, EXMC_NFC_CMD_DESELECT_CHIP);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  De-Initialize EXMC_NFC function.
 * @param  None
 * @retval None
 */
void EXMC_NFC_DeInit(void)
{
    WRITE_REG32(CM_NFC->BACR, 0x00002187UL);
    WRITE_REG32(CM_NFC->IENR, 0x00000080UL);
    WRITE_REG32(CM_NFC->ISTR, 0x00000000UL);
    WRITE_REG32(CM_NFC->TMCR0, 0x03030202UL);
    WRITE_REG32(CM_NFC->TMCR1, 0x28080303UL);
    WRITE_REG32(CM_NFC->TMCR2, 0x03050D03UL);
}

/**
 * @brief  Enable/disable NFC.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void EXMC_NFC_Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_PERIC->NFC_ENAR, PERIC_NFC_ENAR_NFCEN);
    } else {
        CLR_REG32_BIT(CM_PERIC->NFC_ENAR, PERIC_NFC_ENAR_NFCEN);
    }
}

/**
 * @brief  Enable/disable NFC ECC function.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void EXMC_NFC_EccCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        CLR_REG32_BIT(CM_NFC->IENR, NFC_IENR_ECCDIS);
    } else {
        SET_REG32_BIT(CM_NFC->IENR, NFC_IENR_ECCDIS);
    }
}

/**
 * @brief  Enable/disable NFC write protection function.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void EXMC_NFC_WriteProtectCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        CLR_REG32_BIT(CM_NFC->BACR, NFC_BACR_WP);
    } else {
        SET_REG32_BIT(CM_NFC->BACR, NFC_BACR_WP);
    }
}

/**
 * @brief  Enable or disable the specified NFC interrupt
 * @param  [in] u16IntType                The specified interrupt
 *         This parameter can be any composed value of the macros group @ref EXMC_NFC_Interrupt
 *           @arg EXMC_NFC_INT_RB_BANK0:  NFC bank 0 device ready interrupt
 *           @arg EXMC_NFC_INT_RB_BANK1:  NFC bank 1 device ready interrupt
 *           @arg EXMC_NFC_INT_RB_BANK2:  NFC bank 2 device ready interrupt
 *           @arg EXMC_NFC_INT_RB_BANK3:  NFC bank 3 device ready interrupt
 *           @arg EXMC_NFC_INT_RB_BANK4:  NFC bank 4 device ready flag
 *           @arg EXMC_NFC_INT_RB_BANK5:  NFC bank 5 device ready interrupt
 *           @arg EXMC_NFC_INT_RB_BANK6:  NFC bank 6 device ready interrupt
 *           @arg EXMC_NFC_INT_RB_BANK7:  NFC bank 7 device ready interrupt
 *           @arg EXMC_NFC_INT_ECC_ERROR: ECC error interrupt
 *           @arg EXMC_NFC_INT_ECC_CALC_COMPLETION: Calculating ECC completely interrupt
 *           @arg EXMC_NFC_INT_ECC_CORRECTABLE_ERR: ECC correctable error interrupt
 *           @arg EXMC_NFC_INT_ECC_UNCORRECTABLE_ERR: ECC uncorrectable error interrupt
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void EXMC_NFC_IntCmd(uint16_t u16IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_EXMC_NFC_INT(u16IntType));

    if (ENABLE == enNewState) {
        SET_REG16_BIT(CM_NFC->IENR, u16IntType);
    } else {
        CLR_REG16_BIT(CM_NFC->IENR, u16IntType);
    }
}

/**
 * @brief  Get the specified flag status.
 * @param  [in] u32Flag                 The specified flag
 *         This parameter can be any composed value of the macros group @ref EXMC_NFC_Flag
 *           @arg EXMC_NFC_FLAG_RB_BANK0:  NFC bank 0 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK1:  NFC bank 1 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK2:  NFC bank 2 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK3:  NFC bank 3 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK4:  NFC bank 4 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK5:  NFC bank 5 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK6:  NFC bank 6 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK7:  NFC bank 7 device ready flag
 *           @arg EXMC_NFC_FLAG_ECC_ERR:   ECC error
 *           @arg EXMC_NFC_FLAG_ECC_CALC_COMPLETION: Calculate ECC completely
 *           @arg EXMC_NFC_FLAG_ECC_CORRECTABLE_ERR: ECC correctable error
 *           @arg EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERR: ECC uncorrectable error
 *           @arg EXMC_NFC_FLAG_ECC_CALCULATING: Calculating ECC
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t EXMC_NFC_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enStatus1 = RESET;
    en_flag_status_t enStatus2 = RESET;

    DDL_ASSERT(IS_EXMC_NFC_FLAG(u32Flag));

    if (0UL != (u32Flag & NFC_NFC_ISTR_MASK)) {
        if (0UL != READ_REG32_BIT(CM_NFC->ISTR, (u32Flag & NFC_NFC_ISTR_MASK))) {
            enStatus1 = SET;
        }
    }

    if (0UL != (u32Flag & EXMC_NFC_FLAG_ECC_CALCULATING)) {
        if (0UL != READ_REG32_BIT(CM_PERIC->NFC_STSR, PERIC_NFC_STSR_PECC)) {
            enStatus2 = SET;
        }
    }

    return (((SET == enStatus1) || (SET == enStatus2)) ? SET : RESET);
}

/**
 * @brief  Clear the specified flag.
 * @param  [in] u32Flag                 The specified flag
 *         This parameter can be any composed value of the following values:
 *           @arg EXMC_NFC_FLAG_RB_BANK0:  NFC bank 0 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK1:  NFC bank 1 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK2:  NFC bank 2 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK3:  NFC bank 3 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK4:  NFC bank 4 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK5:  NFC bank 5 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK6:  NFC bank 6 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK7:  NFC bank 7 device ready flag
 *           @arg EXMC_NFC_FLAG_ECC_ERR:   ECC error
 *           @arg EXMC_NFC_FLAG_ECC_CALC_COMPLETION: Calculating ECC completely
 *           @arg EXMC_NFC_FLAG_ECC_CORRECTABLE_ERR: ECC correctable error
 *           @arg EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERR: ECC uncorrectable error
 * @retval None
 */
void EXMC_NFC_ClearStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_EXMC_NFC_FLAG(u32Flag));

    CLR_REG32_BIT(CM_NFC->ISTR, u32Flag);
}

/**
 * @brief  Get the interrupt result status.
 * @param  [in] u32Flag                 The specified flag
 *         This parameter can be any composed value of the following values:
 *           @arg EXMC_NFC_FLAG_RB_BANK0:  NFC bank 0 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK1:  NFC bank 1 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK2:  NFC bank 2 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK3:  NFC bank 3 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK4:  NFC bank 4 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK5:  NFC bank 5 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK6:  NFC bank 6 device ready flag
 *           @arg EXMC_NFC_FLAG_RB_BANK7:  NFC bank 7 device ready flag
 *           @arg EXMC_NFC_FLAG_ECC_ERR:   ECC error
 *           @arg EXMC_NFC_FLAG_ECC_CALC_COMPLETION: Calculating ECC completely
 *           @arg EXMC_NFC_FLAG_ECC_CORRECTABLE_ERR: ECC correctable error
 *           @arg EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERR: ECC uncorrectable error
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t EXMC_NFC_GetIntResultStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_EXMC_NFC_FLAG(u32Flag));

    return ((READ_REG32_BIT(CM_NFC->IRSR, u32Flag) > 0UL) ? SET : RESET);
}

/**
 * @brief  Get the 1BIT ECC result of the specified section.
 * @param  [in] u32Section              The specified section
 *         This parameter can be one of the macros group @ref EXMC_NFC_ECC_Section
 *           @arg EXMC_NFC_ECC_SECTION0:  ECC section 0
 *           @arg EXMC_NFC_ECC_SECTION1:  ECC section 1
 *           @arg EXMC_NFC_ECC_SECTION2:  ECC section 2
 *           @arg EXMC_NFC_ECC_SECTION3:  ECC section 3
 *           @arg EXMC_NFC_ECC_SECTION4:  ECC section 4
 *           @arg EXMC_NFC_ECC_SECTION5:  ECC section 5
 *           @arg EXMC_NFC_ECC_SECTION6:  ECC section 6
 *           @arg EXMC_NFC_ECC_SECTION7:  ECC section 7
 *           @arg EXMC_NFC_ECC_SECTION8:  ECC section 8
 *           @arg EXMC_NFC_ECC_SECTION9:  ECC section 9
 *           @arg EXMC_NFC_ECC_SECTION10: ECC section 10
 *           @arg EXMC_NFC_ECC_SECTION11: ECC section 11
 *           @arg EXMC_NFC_ECC_SECTION12: ECC section 12
 *           @arg EXMC_NFC_ECC_SECTION13: ECC section 13
 *           @arg EXMC_NFC_ECC_SECTION14: ECC section 14
 *           @arg EXMC_NFC_ECC_SECTION15: ECC section 15
 * @retval Return one of the macros group @ref EXMC_NFC_1Bit_ECC_Result
 *           - EXMC_NFC_1BIT_ECC_NONE_ERR:          None error
 *           - EXMC_NFC_1BIT_ECC_SINGLE_BIT_ERR:    Single bit error
 *           - EXMC_NFC_1BIT_ECC_MULTIPLE_BITS_ERR: Multiple bit error
 */
uint32_t EXMC_NFC_Get1BitEccResult(uint32_t u32Section)
{
    DDL_ASSERT(IS_EXMC_NFC_SECTION(u32Section));

    return READ_REG32_BIT(NFC_ECCR_REG32(u32Section), (NFC_ECCR_SE | NFC_ECCR_ME));
}

/**
 * @brief  Get the 1BIT ECC error bit of the specified section.
 * @param  [in] u32Section              The specified section
 *         This parameter can be one of the macros group @ref EXMC_NFC_ECC_Section
 *           @arg EXMC_NFC_ECC_SECTION0:  ECC section 0
 *           @arg EXMC_NFC_ECC_SECTION1:  ECC section 1
 *           @arg EXMC_NFC_ECC_SECTION2:  ECC section 2
 *           @arg EXMC_NFC_ECC_SECTION3:  ECC section 3
 *           @arg EXMC_NFC_ECC_SECTION4:  ECC section 4
 *           @arg EXMC_NFC_ECC_SECTION5:  ECC section 5
 *           @arg EXMC_NFC_ECC_SECTION6:  ECC section 6
 *           @arg EXMC_NFC_ECC_SECTION7:  ECC section 7
 *           @arg EXMC_NFC_ECC_SECTION8:  ECC section 8
 *           @arg EXMC_NFC_ECC_SECTION9:  ECC section 9
 *           @arg EXMC_NFC_ECC_SECTION10: ECC section 10
 *           @arg EXMC_NFC_ECC_SECTION11: ECC section 11
 *           @arg EXMC_NFC_ECC_SECTION12: ECC section 12
 *           @arg EXMC_NFC_ECC_SECTION13: ECC section 13
 *           @arg EXMC_NFC_ECC_SECTION14: ECC section 14
 *           @arg EXMC_NFC_ECC_SECTION15: ECC section 15
 * @retval Return one of the macros group @ref EXMC_NFC_1Bit_ECC_Error_Bit_Location
 *           - EXMC_NFC_1BIT_ECC_ERR_BIT0: Bit0 error
 *           - EXMC_NFC_1BIT_ECC_ERR_BIT1: Bit1 error
 *           - EXMC_NFC_1BIT_ECC_ERR_BIT2: Bit2 error
 *           - EXMC_NFC_1BIT_ECC_ERR_BIT3: Bit3 error
 *           - EXMC_NFC_1BIT_ECC_ERR_BIT4: Bit4 error
 *           - EXMC_NFC_1BIT_ECC_ERR_BIT5: Bit5 error
 *           - EXMC_NFC_1BIT_ECC_ERR_BIT6: Bit6 error
 *           - EXMC_NFC_1BIT_ECC_ERR_BIT7: Bit7 error
 */
uint32_t EXMC_NFC_Get1BitEccErrBitLocation(uint32_t u32Section)
{
    DDL_ASSERT(IS_EXMC_NFC_SECTION(u32Section));

    return READ_REG32_BIT(NFC_ECCR_REG32(u32Section), NFC_1BIT_ECC_ERR_BIT_MASK);
}

/**
 * @brief  Get the 1BIT ECC error byte of the specified section.
 * @param  [in] u32Section              The specified section
 *         This parameter can be one of the macros group @ref EXMC_NFC_ECC_Section
 *           @arg EXMC_NFC_ECC_SECTION0:  ECC section 0
 *           @arg EXMC_NFC_ECC_SECTION1:  ECC section 1
 *           @arg EXMC_NFC_ECC_SECTION2:  ECC section 2
 *           @arg EXMC_NFC_ECC_SECTION3:  ECC section 3
 *           @arg EXMC_NFC_ECC_SECTION4:  ECC section 4
 *           @arg EXMC_NFC_ECC_SECTION5:  ECC section 5
 *           @arg EXMC_NFC_ECC_SECTION6:  ECC section 6
 *           @arg EXMC_NFC_ECC_SECTION7:  ECC section 7
 *           @arg EXMC_NFC_ECC_SECTION8:  ECC section 8
 *           @arg EXMC_NFC_ECC_SECTION9:  ECC section 9
 *           @arg EXMC_NFC_ECC_SECTION10: ECC section 10
 *           @arg EXMC_NFC_ECC_SECTION11: ECC section 11
 *           @arg EXMC_NFC_ECC_SECTION12: ECC section 12
 *           @arg EXMC_NFC_ECC_SECTION13: ECC section 13
 *           @arg EXMC_NFC_ECC_SECTION14: ECC section 14
 *           @arg EXMC_NFC_ECC_SECTION15: ECC section 15
 * @retval Return the 1BIT ECC error byte.
 */
uint32_t EXMC_NFC_Get1BitEccErrByteLocation(uint32_t u32Section)
{
    DDL_ASSERT(IS_EXMC_NFC_SECTION(u32Section));

    return (READ_REG32_BIT(NFC_ECCR_REG32(u32Section), NFC_ECCR_ERRLOC) >> NFC_1BIT_ECC_ERR_BYTE_POS);
}

/**
 * @brief  Set NFC spare area size.
 * @param  [in] u8SpareSizeForUserData  NFC spare area size for user data
 * @retval None
 */
void EXMC_NFC_SetSpareAreaSize(uint8_t u8SpareSizeForUserData)
{
    MODIFY_REG32(CM_NFC->BACR, NFC_BACR_SCS, ((((uint32_t)u8SpareSizeForUserData) << NFC_BACR_SCS_POS) & NFC_BACR_SCS));
}

/**
 * @brief  Set NFC ECC mode.
 * @param  [in] u32EccMode              ECC mode
 *         This parameter can be one of the macros group @ref EXMC_NFC_ECC_Mode
 *           @arg EXMC_NFC_1BIT_ECC:    1 bit ECC
 *           @arg EXMC_NFC_4BIT_ECCS:   4 bit ECC
 * @retval None
 */
void EXMC_NFC_SetEccMode(uint32_t u32EccMode)
{
    DDL_ASSERT(IS_EXMC_NFC_ECC_MD(u32EccMode));

    MODIFY_REG32(CM_NFC->BACR, NFC_BACR_ECCM, u32EccMode);
}

/**
 * @brief  Get the 4 bits ECC syndrome register value.
 * @param  [in] u32Section              The syndrome section
 *         This parameter can be one of the macros group @ref EXMC_NFC_ECC_Section
 *           @arg EXMC_NFC_ECC_SECTION0:  ECC section 0
 *           @arg EXMC_NFC_ECC_SECTION1:  ECC section 1
 *           @arg EXMC_NFC_ECC_SECTION2:  ECC section 2
 *           @arg EXMC_NFC_ECC_SECTION3:  ECC section 3
 *           @arg EXMC_NFC_ECC_SECTION4:  ECC section 4
 *           @arg EXMC_NFC_ECC_SECTION5:  ECC section 5
 *           @arg EXMC_NFC_ECC_SECTION6:  ECC section 6
 *           @arg EXMC_NFC_ECC_SECTION7:  ECC section 7
 *           @arg EXMC_NFC_ECC_SECTION8:  ECC section 8
 *           @arg EXMC_NFC_ECC_SECTION9:  ECC section 9
 *           @arg EXMC_NFC_ECC_SECTION10: ECC section 10
 *           @arg EXMC_NFC_ECC_SECTION11: ECC section 11
 *           @arg EXMC_NFC_ECC_SECTION12: ECC section 12
 *           @arg EXMC_NFC_ECC_SECTION13: ECC section 13
 *           @arg EXMC_NFC_ECC_SECTION14: ECC section 14
 *           @arg EXMC_NFC_ECC_SECTION15: ECC section 15
 * @param  [out] au16Synd               The syndrome value
 * @param  [in] u8Len                   The length to be read(unit: half-word)
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer au16Synd value is NULL or u8Len is out of range.
 * @note  u8Len value don't be greater than 8
 */
int32_t EXMC_NFC_GetSyndrome(uint32_t u32Section, uint16_t au16Synd[], uint8_t u8Len)
{
    uint8_t i;
    uint32_t u32SyndVal;
    uint8_t u8LoopWords;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != au16Synd) && (u8Len <= NFC_SYND_MAX_LEN)) {
        DDL_ASSERT(IS_EXMC_NFC_SECTION(u32Section));

        u8LoopWords = (u8Len >> 1U);
        for (i = 0U; i < u8LoopWords; i++) {
            u32SyndVal = READ_REG32(NFC_SYND_REG32(u32Section, i));
            RW_MEM16(&au16Synd[i * 2U]) = (uint16_t)(u32SyndVal);
            RW_MEM16(&au16Synd[i * 2U + 1U ]) = (uint16_t)(u32SyndVal >> 16U);
        }

        if ((u8Len % 2U) != 0U) {
            u32SyndVal = READ_REG32(NFC_SYND_REG32(u32Section, i));
            RW_MEM16(&au16Synd[i * 2U]) = (uint16_t)(u32SyndVal);
        }
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Read NFC device status
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @retval NFC device status
 */
uint32_t EXMC_NFC_ReadStatus(uint32_t u32Bank)
{
    uint32_t u32Status;

    DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));

    /* Write 0x81000M70 to NFC_CMDR, M = bank number */
    WRITE_REG32(CM_NFC->CMDR, CMD_READ_STATUS(u32Bank));

    u32Status = READ_REG32(CM_NFC->DATR_BASE);

    EXMC_NFC_DeselectChip();

    return u32Status;
}

/**
 * @brief  Read status enhanced
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u32RowAddr              The row address
 * @retval NFC device status enhanced
 */
uint32_t EXMC_NFC_ReadStatusEnhanced(uint32_t u32Bank, uint32_t u32RowAddr)
{
    uint32_t u32Status;

    DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));

    /* Erase block step:
        1. Write 0x81000M78 to NFC_CMDR, M = bank number
        2. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the lowest bytes of Row address
        3. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the middle bytes of Row address
        4. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the highest bytes of Row address
        5. Read Data Register */
    WRITE_REG32(CM_NFC->CMDR, CMD_READ_STATUS_ENHANCED(u32Bank));
    WRITE_REG32(CM_NFC->CMDR, CMD_ADDR_1ST_CYCLE(u32Bank, u32RowAddr));
    WRITE_REG32(CM_NFC->CMDR, CMD_ADDR_2ND_CYCLE(u32Bank, u32RowAddr));
    WRITE_REG32(CM_NFC->CMDR, CMD_ADDR_3RD_CYCLE(u32Bank, u32RowAddr));

    u32Status = READ_REG32(CM_NFC->DATR_BASE);

    EXMC_NFC_DeselectChip();

    return u32Status;
}

/**
 * @brief  Reset NFC device
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Reset timeout.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT.
 */
int32_t EXMC_NFC_Reset(uint32_t u32Bank, uint32_t u32Timeout)
{
    int32_t i32Ret;

    DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));

    EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

    /* Reset step:
        1. Write 0x00000MFF to NFC_CMDR, M = bank number
        2. Wait RB signal until high level */
    WRITE_REG32(CM_NFC->CMDR, CMD_RESET(u32Bank));

    i32Ret = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), SET, u32Timeout);

    EXMC_NFC_DeselectChip();

    return i32Ret;
}

/**
 * @brief  Asynchronous reset
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Reset timeout.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT.
 */
int32_t EXMC_NFC_AsyncReset(uint32_t u32Bank, uint32_t u32Timeout)
{
    int32_t i32Ret;

    DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));

    EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

    /* Reset step:
        1. Write 0x00000MFC to NFC_CMDR, M = bank number
        2. Wait RB signal until high level */
    WRITE_REG32(CM_NFC->CMDR, CMD_ASYNC_RESET(u32Bank));

    i32Ret = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), SET, u32Timeout);
    EXMC_NFC_DeselectChip();
    return i32Ret;
}

/**
 * @brief  Reset lun of NFC device
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u32RowAddr              The row address
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Reset timeout.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT.
 */
int32_t EXMC_NFC_ResetLun(uint32_t u32Bank, uint32_t u32RowAddr, uint32_t u32Timeout)
{
    int32_t i32Ret;

    DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));

    EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

    /* Reset lun step:
        1. Write 0x82000MFA to NFC_CMDR, M = bank number
        2. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the lowest bytes of Row address
        3. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the middle bytes of Row address
        4. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the highest bytes of Row address
        5. Wait RB signal until high level */
    WRITE_REG32(CM_NFC->CMDR, CMD_RESET_LUN(u32Bank));
    WRITE_REG32(CM_NFC->CMDR, CMD_ADDR_1ST_CYCLE(u32Bank, u32RowAddr));
    WRITE_REG32(CM_NFC->CMDR, CMD_ADDR_2ND_CYCLE(u32Bank, u32RowAddr));
    WRITE_REG32(CM_NFC->CMDR, CMD_ADDR_3RD_CYCLE(u32Bank, u32RowAddr));

    i32Ret = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), SET, u32Timeout);
    return i32Ret;
}

/**
 * @brief  Read ID
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u32IdAddr               The address
 * @param  [in] au8DevId                The id buffer
 * @param  [in] u32NumBytes             The number of bytes to read
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Read timeout.
 *           - LL_ERR_INVD_PARAM:       The pointer au8DevId value is NULL or u32NumBytes value is 0.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT.
 */
int32_t EXMC_NFC_ReadId(uint32_t u32Bank, uint32_t u32IdAddr,
                        uint8_t au8DevId[], uint32_t u32NumBytes, uint32_t u32Timeout)
{
    uint32_t i;
    uint64_t u64Value;
    const uint32_t u32LoopWords = u32NumBytes / 4UL;
    const uint32_t u32RemainBytes = u32NumBytes % 4UL;
    uint32_t u32TmpId;
    uint32_t u32CapacityIndex;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != au8DevId) && (u32NumBytes > 0UL)) {
        DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));
        DDL_ASSERT(u32IdAddr <= 0xFFUL);

        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank)   | EXMC_NFC_FLAG_ECC_UNCORRECTABLE_ERR | \
                             EXMC_NFC_FLAG_ECC_CORRECTABLE_ERR | EXMC_NFC_FLAG_ECC_CALC_COMPLETION | \
                             EXMC_NFC_FLAG_ECC_ERR);

        /* 1. Write 0x00000000 to NFC_CMDR */
        WRITE_REG32(CM_NFC->CMDR, EXMC_NFC_CMD_RD_1ST);

        /* 2. Write NAND Flash address to NFC_IDXR0/1 */
        u32CapacityIndex = EXMC_NFC_GetCapacityIndex();
        u64Value = (NFC_IDXR_VAL(u32Bank, 0UL, 0UL, u32CapacityIndex) & NFC_IDXR_MASK);
        WRITE_REG32(CM_NFC->IDXR0, (uint32_t)(u64Value & 0xFFFFFFFFUL));
        WRITE_REG32(CM_NFC->IDXR1, (uint32_t)(u64Value >> 32U));

        /* 3. Write 0x000000E0 to NFC_CMDR */
        WRITE_REG32(CM_NFC->CMDR, EXMC_NFC_CMD_RD_2ND);

        /* 4. Wait RB signal until high level */
        i32Ret = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), SET, u32Timeout);
        if (LL_OK == i32Ret) {
            /* Read Id step:
                1. Write 0x81000M90 to NFC_CMDR, M = bank number
                2. Write 0x40000MAB to NFC_CMDR, M = bank number, AB=ID address
                3. Read NFC_DATR
                4. Write 0x000000FE to NFC_CMDR, and invalidate CE */
            WRITE_REG32(CM_NFC->CMDR, CMD_READ_ID(u32Bank));
            WRITE_REG32(CM_NFC->CMDR, CMD_READ_ID_ADDR(u32Bank, u32IdAddr));
            for (i = 0UL; i < u32LoopWords; i++) {
                u32TmpId = NFC_DATR_REG32(i);
                (void)memcpy(&au8DevId[i * 4UL], &u32TmpId, 4UL);
            }

            if (u32RemainBytes > 0UL) {
                u32TmpId = NFC_DATR_REG32(i);
                (void)memcpy(&au8DevId[i * 4UL], &u32TmpId, u32RemainBytes);
            }

            i32Ret = LL_OK;
        }

        EXMC_NFC_DeselectChip();
    }

    return i32Ret;
}

/**
 * @brief  Read Unique ID
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the following values:
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] au32UniqueId            The id buffer
 * @param  [in] u8NumWords              The number of words to read
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Read timeout.
 *           - LL_ERR_INVD_PARAM:       The pointer au32UniqueId value is NULL or u8NumWords value is 0.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
int32_t EXMC_NFC_ReadUniqueId(uint32_t u32Bank, uint32_t au32UniqueId[], uint8_t u8NumWords, uint32_t u32Timeout)
{
    uint8_t i;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != au32UniqueId) && (u8NumWords > 0U)) {
        DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));

        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

        /* Read Id step:
            1. Write 0x81000M90 to NFC_CMDR, M = bank number
            2. Write 0x40000M00 to NFC_CMDR, M = bank number, AB=ID address
            3. Read NFC_DATR
            4. Write 0x000000FE to NFC_CMDR, and invalidate CE */
        WRITE_REG32(CM_NFC->CMDR, CMD_READ_UNIQUEID(u32Bank));
        WRITE_REG32(CM_NFC->CMDR, CMD_READ_UNIQUEID_ADDR(u32Bank));

        i32Ret = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), SET, u32Timeout);
        if (LL_OK == i32Ret) {
            for (i = 0U; i < u8NumWords; i++) {
                au32UniqueId[i] = NFC_DATR_REG32(i);
            }
        }

        EXMC_NFC_DeselectChip();
    }

    return i32Ret;
}

/**
 * @brief  Read parameter page
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] au32Data                The data buffer
 * @param  [in] u16NumWords             The number of words to read
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Read timeout.
 *           - LL_ERR_INVD_PARAM:       The pointer au32Data value is NULL or u16NumWords value is 0.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT.
 */
int32_t EXMC_NFC_ReadParameterPage(uint32_t u32Bank,
                                   uint32_t au32Data[], uint16_t u16NumWords, uint32_t u32Timeout)
{
    uint16_t i;
    int32_t i32Ret = LL_ERR;

    if ((NULL != au32Data) && (u16NumWords > 0U)) {
        DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));

        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

        /* Read parameter page step:
            1. Write 0x81000MEC to NFC_CMDR, M = bank number
            2. Write 0x40000M00 to NFC_CMDR, M = bank number
            3. Read NFC_DATR
            4. Write 0x000000FE to NFC_CMDR, and invalidate CE */
        WRITE_REG32(CM_NFC->CMDR, CMD_READ_PARAMETER_PAGE(u32Bank));
        WRITE_REG32(CM_NFC->CMDR, CMD_READ_PARAMETER_PAGE_ADDR(u32Bank));

        i32Ret = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), SET, u32Timeout);
        if (LL_OK == i32Ret) {
            for (i = 0U; i < u16NumWords; i++) {
                au32Data[i] =  NFC_DATR_REG32(i);
            }
        }

        EXMC_NFC_DeselectChip();
    }

    return i32Ret;
}

/**
 * @brief  Set feature
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u8FeatrueAddr           The featrue address
 * @param  [in] au32Data                The data buffer
 * @param  [in] u8NumWords              The number of words to set
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Set timeout.
 *           - LL_ERR_INVD_PARAM:       The pointer au32Data value is NULL or u8NumWords value is 0.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT.
 */
int32_t EXMC_NFC_SetFeature(uint32_t u32Bank, uint8_t u8FeatrueAddr,
                            const uint32_t au32Data[], uint8_t u8NumWords, uint32_t u32Timeout)
{
    uint8_t i;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != au32Data) && (u8NumWords > 0U)) {
        DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));

        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

        WRITE_REG32(CM_NFC->CMDR, CMD_SET_FEATURE(u32Bank));
        WRITE_REG32(CM_NFC->CMDR, CMD_SET_FEATURE_ADDR(u32Bank, u8FeatrueAddr));

        for (i = 0U; i < u8NumWords; i++) {
            NFC_DATR_REG32(i) = au32Data[i];
        }

        i32Ret = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), SET, u32Timeout);

        EXMC_NFC_DeselectChip();
    }

    return i32Ret;
}

/**
 * @brief  Get feature
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u8FeatrueAddr           The featrue address
 * @param  [out] au32Data               The data buffer
 * @param  [in] u8NumWords              The number of words to get
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Get timeout.
 *           - LL_ERR_INVD_PARAM:       The pointer au32Data value is NULL or u8NumWords value is 0.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT.
 */
int32_t EXMC_NFC_GetFeature(uint32_t u32Bank, uint8_t u8FeatrueAddr,
                            uint32_t au32Data[], uint8_t u8NumWords, uint32_t u32Timeout)
{
    uint8_t i;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != au32Data) && (u8NumWords > 0U)) {
        DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));

        EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

        WRITE_REG32(CM_NFC->CMDR, CMD_GET_FEATURE(u32Bank));
        WRITE_REG32(CM_NFC->CMDR, CMD_GET_FEATURE_ADDR(u32Bank, u8FeatrueAddr));

        i32Ret = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), SET, u32Timeout);
        if (LL_OK == i32Ret) {
            for (i = 0U; i < u8NumWords; i++) {
                au32Data[i] = NFC_DATR_REG32(i);
            }
        }

        EXMC_NFC_DeselectChip();
    }

    return i32Ret;
}

/**
 * @brief  Erase NFC device block
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u32RowAddr              The row address
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Erase timeout.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT.
 */
int32_t EXMC_NFC_EraseBlock(uint32_t u32Bank, uint32_t u32RowAddr, uint32_t u32Timeout)
{
    int32_t i32Ret;

    DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));

    EXMC_NFC_ClearStatus(NFC_FLAG_RB_BANKx_MASK(u32Bank));

    /* Erase block step:
        1. Write 0x81000M60 to NFC_CMDR, M = bank number
        2. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the lowest bytes of Row address
        3. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the middle bytes of Row address
        4. Write 0x40000MAB to NFC_CMDR, M = bank number, AB= the highest bytes of Row address
        5. Write 0x00000MD0 to NFC_CMDR, M = bank number
        6. Wait RB signal until high level */
    WRITE_REG32(CM_NFC->CMDR, CMD_ERASE_BLOCK_1ST_CYCLE(u32Bank));
    WRITE_REG32(CM_NFC->CMDR, CMD_ADDR_1ST_CYCLE(u32Bank, u32RowAddr));
    WRITE_REG32(CM_NFC->CMDR, CMD_ADDR_2ND_CYCLE(u32Bank, u32RowAddr));
    WRITE_REG32(CM_NFC->CMDR, CMD_ADDR_3RD_CYCLE(u32Bank, u32RowAddr));
    WRITE_REG32(CM_NFC->CMDR, CMD_ERASE_BLOCK_2ND_CYCLE(u32Bank));

    i32Ret = EXMC_NFC_WaitFlagUntilTo(NFC_FLAG_RB_BANKx_MASK(u32Bank), SET, u32Timeout);
    return i32Ret;
}

/**
 * @brief  NFC page read
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u32Page                 The specified page
 * @param  [out] pu8Data                The buffer for reading
 * @param  [in] u32NumBytes             The buffer size for bytes
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Write timeout.
 *           - LL_ERR_INVD_PARAM:       The pointer pu8Data value value is NULL or u32NumBytes is 0.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
int32_t EXMC_NFC_ReadPageMeta(uint32_t u32Bank, uint32_t u32Page, uint8_t *pu8Data,
                              uint32_t u32NumBytes, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != pu8Data) && (u32NumBytes > 0UL)) {
        DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));
        DDL_ASSERT(IS_PARAM_ALIGN_WORD(u32NumBytes));
        DDL_ASSERT(IS_ADDR_ALIGN_WORD(pu8Data));

        i32Ret = EXMC_NFC_Read(u32Bank, u32Page, 0UL, (uint32_t *)((uint32_t)pu8Data), \
                               (u32NumBytes / 4UL), DISABLE, u32Timeout);
    }

    return i32Ret;
}

/**
 * @brief  NFC page write
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u32Page                 The specified page
 * @param  [in] pu8Data                 The buffer for writing
 * @param  [in] u32NumBytes             The buffer size for bytes
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Write timeout.
 *           - LL_ERR_INVD_PARAM:       The pointer pu8Data value is NULL or u32NumBytes is 0.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
int32_t EXMC_NFC_WritePageMeta(uint32_t u32Bank, uint32_t u32Page,
                               const uint8_t *pu8Data, uint32_t u32NumBytes, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != pu8Data) && (u32NumBytes > 0UL)) {
        DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));
        DDL_ASSERT(IS_PARAM_ALIGN_WORD(u32NumBytes));
        DDL_ASSERT(IS_ADDR_ALIGN_WORD(pu8Data));

        i32Ret = EXMC_NFC_Write(u32Bank, u32Page, 0UL, (uint32_t *)((uint32_t)pu8Data), \
                                (u32NumBytes / 4UL), DISABLE, u32Timeout);
    }

    return i32Ret;
}

/**
 * @brief  NFC page read by hardware ECC
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u32Page                 The specified page
 * @param  [out] pu8Data                The buffer for reading
 * @param  [in] u32NumBytes             The buffer size for bytes
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Write timeout.
 *           - LL_ERR_INVD_PARAM:       The pointer pu8Data value is NULL or u32NumBytes is 0.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
int32_t EXMC_NFC_ReadPageHwEcc(uint32_t u32Bank, uint32_t u32Page,
                               uint8_t *pu8Data, uint32_t u32NumBytes, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
#ifdef __DEBUG
    const uint32_t u32PageSize = NFC_PAGE_SIZE;
    const uint32_t u32SpareSizeUserData = NFC_SPARE_SIZE_FOR_USER_DATA;
#endif

    if ((NULL != pu8Data) && (u32NumBytes > 0UL)) {
        DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));
        DDL_ASSERT(IS_PARAM_ALIGN_WORD(u32NumBytes));
        DDL_ASSERT(IS_ADDR_ALIGN_WORD(pu8Data));
        DDL_ASSERT(u32NumBytes <= (u32PageSize + u32SpareSizeUserData));

        i32Ret = EXMC_NFC_Read(u32Bank, u32Page, 0UL, (uint32_t *)((uint32_t)pu8Data), \
                               (u32NumBytes / 4UL), ENABLE, u32Timeout);
    }

    return i32Ret;
}

/**
 * @brief  NFC page  write by hardware ECC
 * @param  [in] u32Bank                 The specified bank
 *         This parameter can be one of the macros group @ref EXMC_NFC_Bank
 *           @arg EXMC_NFC_BANK0:       NFC device bank 0
 *           @arg EXMC_NFC_BANK1:       NFC device bank 1
 *           @arg EXMC_NFC_BANK2:       NFC device bank 2
 *           @arg EXMC_NFC_BANK3:       NFC device bank 3
 *           @arg EXMC_NFC_BANK4:       NFC device bank 4
 *           @arg EXMC_NFC_BANK5:       NFC device bank 5
 *           @arg EXMC_NFC_BANK6:       NFC device bank 6
 *           @arg EXMC_NFC_BANK7:       NFC device bank 7
 * @param  [in] u32Page                 The specified page
 * @param  [in] pu8Data                 The buffer for writing
 * @param  [in] u32NumBytes             The buffer size for bytes
 * @param  [in] u32Timeout              The operation timeout value(Max value @ref EXMC_NFC_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Write timeout.
 *           - LL_ERR_INVD_PARAM:       The pointer pu8Data value is NULL or u32NumBytes is 0.
 * @note Block waiting until operation complete if u32Timeout value is EXMC_NFC_MAX_TIMEOUT
 */
int32_t EXMC_NFC_WritePageHwEcc(uint32_t u32Bank, uint32_t u32Page,
                                const uint8_t *pu8Data, uint32_t u32NumBytes, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
#ifdef __DEBUG
    const uint32_t u32PageSize = NFC_PAGE_SIZE;
    const uint32_t u32SpareSizeUserData = NFC_SPARE_SIZE_FOR_USER_DATA;
#endif

    if ((NULL != pu8Data) && (u32NumBytes > 0UL)) {
        DDL_ASSERT(IS_EXMC_NFC_BANK(u32Bank));
        DDL_ASSERT(IS_PARAM_ALIGN_WORD(u32NumBytes));
        DDL_ASSERT(IS_ADDR_ALIGN_WORD((uint32_t)pu8Data));
        DDL_ASSERT(u32NumBytes <= (u32PageSize + u32SpareSizeUserData));

        i32Ret = EXMC_NFC_Write(u32Bank, u32Page, 0UL, (uint32_t *)((uint32_t)pu8Data), \
                                (u32NumBytes / 4UL), ENABLE, u32Timeout);
    }

    return i32Ret;
}

/**
 * @}
 */

#endif /* LL_NFC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
