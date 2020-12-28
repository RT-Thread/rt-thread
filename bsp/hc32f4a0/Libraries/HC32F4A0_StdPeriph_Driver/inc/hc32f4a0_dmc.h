/**
 *******************************************************************************
 * @file  hc32f4a0_dmc.h
 * @brief This file contains all the functions prototypes of the EXMC DMC
 *        (External Memory Controller: Dynamic Memory Controller) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Hongjh          First version
   2020-07-14       Hongjh          Merge API from EXMC_DMC_Enable/Disable to EXMC_DMC_Cmd
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
#ifndef __HC32F4A0_DMC_H__
#define __HC32F4A0_DMC_H__

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
 * @addtogroup DDL_EXMC_DMC
 * @{
 */

#if (DDL_DMC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EXMC_DMC_Global_Types Dynamic Memory Controller Global Types
 * @{
 */

/**
 * @brief  EXMC DMC CS Configuration Structure definition 
 */
typedef struct
{
    uint32_t    u32AddrMask;                /*!< Defines the address mask.
                                                 This parameter can be a value of @ref EXMC_DMC_Mask_Address.   */

    uint32_t    u32AddrMatch;               /*!< Defines the address match.
                                                 This parameter can be a value of @ref EXMC_DMC_Match_Address.  */

    uint32_t    u32AddrDecodeMode;          /*!< Defines the address decode mode.
                                                 This parameter can be a value of @ref EXMC_DMC_CS_Decode_Mode. */
} stc_exmc_dmc_cs_cfg_t;

/**
 * @brief  EXMC DMC Chip Configuration Structure definition
 */
typedef struct
{

    uint32_t    u32ColumnBitsNumber;        /*!< Defines the number of bits of column address.
                                                 This parameter can be a value of @ref EXMC_DMC_Column_Bits_Number. */

    uint32_t    u32RowBitsNumber;           /*!< Defines the number of bits of row address.
                                                 This parameter can be a value of @ref EXMC_DMC_Row_Bits_Number.    */

    uint32_t    u32AutoPrechargePin;        /*!< Defines the auto-precharge pin.
                                                 This parameter can be a value of @ref EXMC_DMC_Auto_Precharge_Pin.    */

    uint32_t    u32MemClkSel;               /*!< Defines the memory clock selection.
                                                 This parameter can be a value of @ref EXMC_DMC_MemClock_Selection */

    uint32_t    u32CkeOutputSel;            /*!< Defines the CKE output selection.
                                                 This parameter can be a value of @ref EXMC_DMC_CKE_Output_Selection */

    uint32_t    u32CkeDisablePeriod;        /*!< Defines the CKE disable period.
                                                 This parameter can be a value between Min_Data = 0 and Max_Data = 0x3F */

    uint32_t    u32MemBurst;                /*!< Defines the number of data accesses.
                                                 This parameter can be a value of @ref EXMC_DMC_Memory_Burst.    */

    uint32_t    u32AutoRefreshChips;        /*!< Defines the refresh command generation for the number of memory chips.
                                                 This parameter can be a value of @ref EXMC_DMC_Auto_Refresh_Chips.    */
}stc_exmc_dmc_chip_cfg_t;

/**
 * @brief  EXMC DMC Timing Configuration Structure definition
 */
typedef struct
{
    uint32_t    u32CASL;        /*!< Defines the CAS latency in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 7    */
    uint32_t    u32DQSS;        /*!< Defines the DQSS in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 3    */
    uint32_t    u32MRD;         /*!< Defines the the mode register command time in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 0x7F */
    uint32_t    u32RAS;         /*!< Defines the RAS in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 0x0F */
    uint32_t    u32RC;          /*!< Defines the RC in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 0x0F */
    uint32_t    u32RCD;         /*!< Defines the RCD in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
    uint32_t    u32RFC;         /*!< Defines the RFC in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 0x1F */
    uint32_t    u32RP;          /*!< Defines the RP in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
    uint32_t    u32RRD;         /*!< Defines the RRD in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 0x0F */
    uint32_t    u32WR;          /*!< Defines the WR in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
    uint32_t    u32WTR;         /*!< Defines the WTR in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
    uint32_t    u32XP;          /*!< Defines the XP in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */
    uint32_t    u32XSR;         /*!< Defines the XSR in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */
    uint32_t    u32ESR;         /*!< Defines the ESR in memory clock cycles.
                                     This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */
} stc_exmc_dmc_timing_cfg_t;

/**
 * @brief  EXMC DMC Initialization Structure definition
 */
typedef struct
{
    uint32_t                    u32DmcMemWidth;     /*!< DMC memory width.
                                                         This parameter can be a value of @ref EXMC_DMC_Memory_Width.    */

    uint32_t                    u32RefreshPeriod;   /*!< DMC memory refresh period.
                                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0x7FFF */

    stc_exmc_dmc_chip_cfg_t     stcChipCfg;         /*!< DMC memory chip configure.
                                                         This structure details refer @ref stc_exmc_dmc_chip_cfg_t.    */

    stc_exmc_dmc_timing_cfg_t   stcTimingCfg;       /*!< DMC memory timing configure.
                                                         This structure details refer @ref stc_exmc_dmc_timing_cfg_t.    */
} stc_exmc_dmc_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EXMC_DMC_Global_Macros Dynamic Memory Controller Global Macros
 * @{
 */

/**
 * @defgroup EXMC_DMC_Memory_Width EXMC DMC Memory Width
 * @{
 */
#define EXMC_DMC_MEMORY_WIDTH_16BIT             (0UL)
#define EXMC_DMC_MEMORY_WIDTH_32BIT             (DMC_BACR_DMCMW_0)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Chip EXMC DMC Chip
 * @{
 */
#define EXMC_DMC_CHIP_0                         (0UL)     /*!< Chip 0 */
#define EXMC_DMC_CHIP_1                         (1UL)     /*!< Chip 1 */
#define EXMC_DMC_CHIP_2                         (2UL)     /*!< Chip 2 */
#define EXMC_DMC_CHIP_3                         (3UL)     /*!< Chip 3 */
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Bank EXMC DMC Bank
 * @{
 */
#define EXMC_DMC_BANK_0                         (0UL)     /*!< Bank 0 */
#define EXMC_DMC_BANK_1                         (1UL)     /*!< Bank 1 */
#define EXMC_DMC_BANK_2                         (2UL)     /*!< Bank 2 */
#define EXMC_DMC_BANK_3                         (3UL)     /*!< Bank 3 */
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Current_Status EXMC DMC Current Status
 * @{
 */
#define EXMC_DMC_CURR_STATUS_CONFIGURE          (0UL)
#define EXMC_DMC_CURR_STATUS_READY              (DMC_STSR_STATUS_0)
#define EXMC_DMC_CURR_STATUS_PAUSED             (DMC_STSR_STATUS_1)
#define EXMC_DMC_CURR_STATUS_LOWPOWER           (DMC_STSR_STATUS)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Control_State EXMC DMC Control State
 * @{
 */
#define EXMC_DMC_CTL_STATE_GO                   (0UL)
#define EXMC_DMC_CTL_STATE_SLEEP                (1UL)
#define EXMC_DMC_CTL_STATE_WAKEUP               (2UL)
#define EXMC_DMC_CTL_STATE_PAUSE                (3UL)
#define EXMC_DMC_CTL_STATE_CONFIGURE            (4UL)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Command EXMC DMC Command
 * @{
 */
#define EXMC_DMC_CMD_PRECHARGEALL               (0UL)               /*!< Precharge all */
#define EXMC_DMC_CMD_AUTOREFRESH                (DMC_CMDR_CMD_0)    /*!< Auto refresh */
#define EXMC_DMC_CMD_MDREGCONFIG                (DMC_CMDR_CMD_1)    /*!< Set memory device mode register */
#define EXMC_DMC_CMD_NOP                        (DMC_CMDR_CMD)      /*!< NOP */
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Refresh_Period_Max EXMC DMC Refresh Period Max
 * @{
 */
#define EXMC_DMC_REFRESH_PERIOD_MAX             (0x00007FFFUL)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_CS_Decode_Mode EXMC DMC CS Decode Mode
 * @{
 */
#define EXMC_DMC_CS_DECODE_ROWBANKCOL           (0UL)           /*!< Row -> Bank -> Column */
#define EXMC_DMC_CS_DECODE_BANKROWCOL           (DMC_CSCR_BRC)  /*!< Bank -> Row -> Column */
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Column_Bits_Number EXMC DMC Column Bits Number
 * @{
 */
#define EXMC_DMC_COLUMN_BITS_NUM_8              (0UL)
#define EXMC_DMC_COLUMN_BITS_NUM_9              (DMC_CPCR_COLBS_0)
#define EXMC_DMC_COLUMN_BITS_NUM_10             (DMC_CPCR_COLBS_1)
#define EXMC_DMC_COLUMN_BITS_NUM_11             (DMC_CPCR_COLBS_1 | \
                                                 DMC_CPCR_COLBS_0)
#define EXMC_DMC_COLUMN_BITS_NUM_12             (DMC_CPCR_COLBS_2)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Row_Bits_Number EXMC DMC Row Bits Number
 * @{
 */
#define EXMC_DMC_ROW_BITS_NUM_11                (0UL)
#define EXMC_DMC_ROW_BITS_NUM_12                (DMC_CPCR_ROWBS_0)
#define EXMC_DMC_ROW_BITS_NUM_13                (DMC_CPCR_ROWBS_1)
#define EXMC_DMC_ROW_BITS_NUM_14                (DMC_CPCR_ROWBS_1 | \
                                                 DMC_CPCR_ROWBS_0)
#define EXMC_DMC_ROW_BITS_NUM_15                (DMC_CPCR_ROWBS_2)
#define EXMC_DMC_ROW_BITS_NUM_16                (DMC_CPCR_ROWBS_2 | \
                                                 DMC_CPCR_ROWBS_0)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Auto_Precharge_Pin EXMC DMC Auto Pre-charge Pin
 * @{
 */
#define EXMC_DMC_AUTO_PRECHARGE_A8              (DMC_CPCR_APBS)
#define EXMC_DMC_AUTO_PRECHARGE_A10             (0UL)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_CKE_Output_Selection EXMC DMC CKE Output Selection
 * @{
 */
#define EXMC_DMC_CKE_OUTPUT_ENABLE              (0UL)
#define EXMC_DMC_CKE_OUTPUT_DISABLE             (DMC_CPCR_CKEDIS)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_MemClock_Selection EXMC DMC MemClock Selection
 * @{
 */
#define EXMC_DMC_MEMCLK_NORMAL_OUTPUT           (0UL)
#define EXMC_DMC_MEMCLK_NOP_STOP_OUTPUT         (DMC_CPCR_CKSTOP)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Memory_Burst EXMC DMC Memory Burst
 * @{
 */
#define EXMC_DMC_MEM_BURST_1                    (0UL)
#define EXMC_DMC_MEM_BURST_2                    (DMC_CPCR_BURST_0)
#define EXMC_DMC_MEM_BURST_4                    (DMC_CPCR_BURST_1)
#define EXMC_DMC_MEM_BURST_8                    (DMC_CPCR_BURST_1 | \
                                                 DMC_CPCR_BURST_0)
#define EXMC_DMC_MEM_BURST_16                   (DMC_CPCR_BURST_2)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Auto_Refresh_Chips EXMC DMC Auto Refresh
 * @{
 */
#define EXMC_DMC_AUTO_REFRESH_CHIP_0            (0UL)
#define EXMC_DMC_AUTO_REFRESH_CHIPS_01          (DMC_CPCR_ACTCP_0)
#define EXMC_DMC_AUTO_REFRESH_CHIPS_012         (DMC_CPCR_ACTCP_1)
#define EXMC_DMC_AUTO_REFRESH_CHIPS_0123        (DMC_CPCR_ACTCP)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Match_Address EXMC DMC Match Address
 * @{
 */
#define EXMC_DMC_ADDR_MATCH_0X80000000          (0x80UL << DMC_CSCR_ADDMAT_POS)
#define EXMC_DMC_ADDR_MATCH_0X81000000          (0x81UL << DMC_CSCR_ADDMAT_POS)
#define EXMC_DMC_ADDR_MATCH_0X82000000          (0x82UL << DMC_CSCR_ADDMAT_POS)
#define EXMC_DMC_ADDR_MATCH_0X83000000          (0x83UL << DMC_CSCR_ADDMAT_POS)
#define EXMC_DMC_ADDR_MATCH_0X84000000          (0x84UL << DMC_CSCR_ADDMAT_POS)
#define EXMC_DMC_ADDR_MATCH_0X85000000          (0x85UL << DMC_CSCR_ADDMAT_POS)
#define EXMC_DMC_ADDR_MATCH_0X86000000          (0x86UL << DMC_CSCR_ADDMAT_POS)
#define EXMC_DMC_ADDR_MATCH_0X87000000          (0x87UL << DMC_CSCR_ADDMAT_POS)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Mask_Address EXMC DMC Mask Address
 * @{
 */
#define EXMC_DMC_ADDR_MASK_16MB                 (0xFFUL)
#define EXMC_DMC_ADDR_MASK_32MB                 (0xFEUL)
#define EXMC_DMC_ADDR_MASK_64MB                 (0xFCUL)
#define EXMC_DMC_ADDR_MASK_128MB                (0xF8UL)
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
 * @addtogroup EXMC_DMC_Global_Functions
 * @{
 */

/**
 * @brief  Get DMC status.
 * @param  None
 * @retval Returned value can be one of the following values:
 *           @arg EXMC_DMC_CURR_STATUS_CONFIGURE: Configure status
 *           @arg EXMC_DMC_CURR_STATUS_READY:     Ready status
 *           @arg EXMC_DMC_CURR_STATUS_PAUSED:    Pause status
 *           @arg EXMC_DMC_CURR_STATUS_LOWPOWER:  Sleep for low power status
 */
__STATIC_INLINE uint32_t EXMC_DMC_GetStatus(void)
{
    return READ_REG32_BIT(M4_DMC->STSR, DMC_STSR_STATUS);
}

/* Initialization and configuration EXMC DMC functions */
en_result_t EXMC_DMC_Init(const stc_exmc_dmc_init_t *pstcInit);
void EXMC_DMC_DeInit(void);
en_result_t EXMC_DMC_StructInit(stc_exmc_dmc_init_t *pstcInit);
void EXMC_DMC_Cmd(en_functional_state_t enNewState);
en_result_t EXMC_DMC_CsConfig(uint32_t u32Chip,
                                const stc_exmc_dmc_cs_cfg_t *pstcCfg);
uint32_t EXMC_DMC_ChipStartAddress(uint32_t u32Chip);
uint32_t EXMC_DMC_ChipEndAddress(uint32_t u32Chip);
en_result_t EXMC_DMC_SetCommand(uint32_t u32Chip,
                                    uint32_t u32Bank,
                                    uint32_t u32Cmd,
                                    uint32_t u32Address);
void EXMC_DMC_SetState(uint32_t u32State);

/**
 * @}
 */

#endif /* DDL_DMC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_DMC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
