/**
 *******************************************************************************
 * @file  hc32_ll_dmc.h
 * @brief This file contains all the functions prototypes of the EXMC_DMC
 *        (External Memory Controller: Dynamic Memory Controller) driver library.
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
#ifndef __HC32_LL_DMC_H__
#define __HC32_LL_DMC_H__

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
 * @addtogroup LL_DMC
 * @{
 */

#if (LL_DMC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EXMC_DMC_Global_Types EXMC_DMC Global Types
 * @{
 */

/**
 * @brief  EXMC_DMC Chip Configuration Structure definition
 */
typedef struct {
    uint32_t u32AddrMask;           /*!< Defines the address mask.
                                         This parameter can be a value of @ref EXMC_DMC_Mask_Address. */
    uint32_t u32AddrMatch;          /*!< Defines the address match.
                                         This parameter can be a value between Min_Data = 0x80 and Max_Data = 0x87 */
    uint32_t u32AddrDecodeMode;     /*!< Defines the address decode mode.
                                         This parameter can be a value of @ref EXMC_DMC_Address_Decode_Mode. */
} stc_exmc_dmc_chip_config_t;

/**
 * @brief  EXMC_DMC Initialization Structure definition
 */
typedef struct {
    uint32_t u32SampleClock;        /*!< DMC sample clock.
                                         This parameter can be a value of @ref EXMC_DMC_Sample_Clock. */
    uint32_t u32MemoryWidth;        /*!< DMC memory width.
                                         This parameter can be a value of @ref EXMC_DMC_Memory_Width. */
    uint32_t u32RefreshPeriod;      /*!< DMC memory refresh period.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0x7FFF */
    uint32_t u32ColumnBitsNumber;   /*!< Defines the number of bits of column address.
                                         This parameter can be a value of @ref EXMC_DMC_Column_Bits_Number. */
    uint32_t u32RowBitsNumber;      /*!< Defines the number of bits of row address.
                                         This parameter can be a value of @ref EXMC_DMC_Row_Bits_Number. */
    uint32_t u32AutoPrechargePin;   /*!< Defines the auto-precharge pin.
                                         This parameter can be a value of @ref EXMC_DMC_Auto_Precharge_Pin. */
    uint32_t u32MemClockSel;        /*!< Defines the memory clock selection.
                                         This parameter can be a value of @ref EXMC_DMC_Clock_Selection */
    uint32_t u32CkeOutputSel;       /*!< Defines the CKE output selection.
                                         This parameter can be a value of @ref EXMC_DMC_CKE_Output_Selection */
    uint32_t u32CkeDisablePeriod;   /*!< Defines the CKE disable period.
                                         This parameter can be a value between Min_Data = 0x00 and Max_Data = 0x3F */
    uint32_t u32MemBurst;           /*!< Defines the number of data accesses.
                                         This parameter can be a value of @ref EXMC_DMC_Memory_Burst. */
    uint32_t u32AutoRefreshChips;   /*!< Defines the refresh command generation for the number of memory chips.
                                         This parameter can be a value of @ref EXMC_DMC_Auto_Refresh_Chips. */
    struct {
        uint8_t u8CASL;             /*!< Defines the CAS latency in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
        uint8_t u8DQSS;             /*!< Defines the DQSS in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 3 */
        uint8_t u8MRD;              /*!< Defines the the mode register command time in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0x7F */
        uint8_t u8RAS;              /*!< Defines the RAS in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0x0F */
        uint8_t u8RC;               /*!< Defines the RC in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0x0F */
        uint8_t u8RCD_B;            /*!< Defines the RCD base value in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
        uint8_t u8RCD_P;            /*!< Defines the RCD append value in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
        uint8_t u8RFC_B;            /*!< Defines the RFC base value in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0x1F */
        uint8_t u8RFC_P;            /*!< Defines the RFC append value in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0x1F */
        uint8_t u8RP_B;             /*!< Defines the RP base value in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
        uint8_t u8RP_P;             /*!< Defines the RP append value in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
        uint8_t u8RRD;              /*!< Defines the RRD in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0x0F */
        uint8_t u8WR;               /*!< Defines the WR in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
        uint8_t u8WTR;              /*!< Defines the WTR in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
        uint8_t u8XP;               /*!< Defines the XP in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */
        uint8_t u8XSR;              /*!< Defines the XSR in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */
        uint8_t u8ESR;              /*!< Defines the ESR in memory clock cycles.
                                         This parameter can be a value between Min_Data = 0 and Max_Data = 0xFF */
    } stcTimingConfig;
} stc_exmc_dmc_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EXMC_DMC_Global_Macros EXMC_DMC Global Macros
 * @{
 */

/**
 * @defgroup EXMC_DMC_Memory_Width EXMC_DMC Memory Width
 * @{
 */
#define EXMC_DMC_MEMORY_WIDTH_16BIT         (0UL)
#define EXMC_DMC_MEMORY_WIDTH_32BIT         (DMC_BACR_DMCMW_0)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Chip EXMC_DMC Chip
 * @{
 */
#define EXMC_DMC_CHIP0                      (0UL)     /*!< Chip 0 */
#define EXMC_DMC_CHIP1                      (1UL)     /*!< Chip 1 */
#define EXMC_DMC_CHIP2                      (2UL)     /*!< Chip 2 */
#define EXMC_DMC_CHIP3                      (3UL)     /*!< Chip 3 */
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Bank EXMC_DMC Bank
 * @{
 */
#define EXMC_DMC_BANK0                      (0UL)     /*!< Bank 0 */
#define EXMC_DMC_BANK1                      (1UL)     /*!< Bank 1 */
#define EXMC_DMC_BANK2                      (2UL)     /*!< Bank 2 */
#define EXMC_DMC_BANK3                      (3UL)     /*!< Bank 3 */
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Current_Status EXMC_DMC Current Status
 * @{
 */
#define EXMC_DMC_CURR_STATUS_CONFIG         (0UL)
#define EXMC_DMC_CURR_STATUS_RDY            (DMC_STSR_STATUS_0)
#define EXMC_DMC_CURR_STATUS_PAUSED         (DMC_STSR_STATUS_1)
#define EXMC_DMC_CURR_STATUS_LOWPOWER       (DMC_STSR_STATUS)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Control_State EXMC_DMC Control State
 * @{
 */
#define EXMC_DMC_CTRL_STATE_GO              (0UL)
#define EXMC_DMC_CTRL_STATE_SLEEP           (1UL)
#define EXMC_DMC_CTRL_STATE_WAKEUP          (2UL)
#define EXMC_DMC_CTRL_STATE_PAUSE           (3UL)
#define EXMC_DMC_CTRL_STATE_CONFIG          (4UL)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Command EXMC_DMC Command
 * @{
 */
#define EXMC_DMC_CMD_PRECHARGE_ALL          (0UL)               /*!< Precharge all */
#define EXMC_DMC_CMD_AUTO_REFRESH           (DMC_CMDR_CMD_0)    /*!< Auto refresh */
#define EXMC_DMC_CMD_MDREG_CONFIG           (DMC_CMDR_CMD_1)    /*!< Set memory device mode register */
#define EXMC_DMC_CMD_NOP                    (DMC_CMDR_CMD)      /*!< NOP */
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Address_Decode_Mode EXMC_DMC Address Decode Mode
 * @{
 */
#define EXMC_DMC_CS_DECODE_ROWBANKCOL       (0UL)           /*!< Row -> Bank -> Column */
#define EXMC_DMC_CS_DECODE_BANKROWCOL       (DMC_CSCR_BRC)  /*!< Bank -> Row -> Column */
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Column_Bits_Number EXMC_DMC Column Bits Number
 * @{
 */
#define EXMC_DMC_COLUMN_BITS_NUM8           (0UL)
#define EXMC_DMC_COLUMN_BITS_NUM9           (1UL << DMC_CPCR_COLBS_POS)
#define EXMC_DMC_COLUMN_BITS_NUM10          (2UL << DMC_CPCR_COLBS_POS)
#define EXMC_DMC_COLUMN_BITS_NUM11          (3UL << DMC_CPCR_COLBS_POS)
#define EXMC_DMC_COLUMN_BITS_NUM12          (4UL << DMC_CPCR_COLBS_POS)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Row_Bits_Number EXMC_DMC Row Bits Number
 * @{
 */
#define EXMC_DMC_ROW_BITS_NUM11             (0UL)
#define EXMC_DMC_ROW_BITS_NUM12             (1UL << DMC_CPCR_ROWBS_POS)
#define EXMC_DMC_ROW_BITS_NUM13             (2UL << DMC_CPCR_ROWBS_POS)
#define EXMC_DMC_ROW_BITS_NUM14             (3UL << DMC_CPCR_ROWBS_POS)
#define EXMC_DMC_ROW_BITS_NUM15             (4UL << DMC_CPCR_ROWBS_POS)
#define EXMC_DMC_ROW_BITS_NUM16             (5UL << DMC_CPCR_ROWBS_POS)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Auto_Precharge_Pin EXMC_DMC Auto Pre-charge Pin
 * @{
 */
#define EXMC_DMC_AUTO_PRECHARGE_A8          (DMC_CPCR_APBS)
#define EXMC_DMC_AUTO_PRECHARGE_A10         (0UL)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_CKE_Output_Selection EXMC_DMC CKE Output Selection
 * @{
 */
#define EXMC_DMC_CKE_OUTPUT_ENABLE          (0UL)
#define EXMC_DMC_CKE_OUTPUT_DISABLE         (DMC_CPCR_CKEDIS)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Clock_Selection EXMC_DMC Clock Selection
 * @{
 */
#define EXMC_DMC_CLK_NORMAL_OUTPUT          (0UL)
#define EXMC_DMC_CLK_NOP_STOP_OUTPUT        (DMC_CPCR_CKSTOP)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Memory_Burst EXMC_DMC Memory Burst
 * @{
 */
#define EXMC_DMC_BURST_1BEAT                (0UL)
#define EXMC_DMC_BURST_2BEAT                (1UL << DMC_CPCR_BURST_POS)
#define EXMC_DMC_BURST_4BEAT                (2UL << DMC_CPCR_BURST_POS)
#define EXMC_DMC_BURST_8BEAT                (3UL << DMC_CPCR_BURST_POS)
#define EXMC_DMC_BURST_16BEAT               (4UL << DMC_CPCR_BURST_POS)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Auto_Refresh_Chips EXMC_DMC Auto Refresh
 * @{
 */
#define EXMC_DMC_AUTO_REFRESH_1CHIP         (0UL)
#define EXMC_DMC_AUTO_REFRESH_2CHIPS        (DMC_CPCR_ACTCP_0)
#define EXMC_DMC_AUTO_REFRESH_3CHIPS        (DMC_CPCR_ACTCP_1)
#define EXMC_DMC_AUTO_REFRESH_4CHIPS        (DMC_CPCR_ACTCP)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Mask_Address EXMC_DMC Mask Address
 * @{
 */
#define EXMC_DMC_ADDR_MASK_16MB             (0xFFUL)
#define EXMC_DMC_ADDR_MASK_32MB             (0xFEUL)
#define EXMC_DMC_ADDR_MASK_64MB             (0xFCUL)
#define EXMC_DMC_ADDR_MASK_128MB            (0xF8UL)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Address_Space EXMC_DMC Address Space
 * @{
 */
#define EXMC_DMC_ADDR_MIN                   (0x80000000UL)
#define EXMC_DMC_ADDR_MAX                   (0x87FFFFFFUL)
/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Sample_Clock EXMC_DMC Sample Clock
 * @{
 */
#define EXMC_DMC_SAMPLE_CLK_INTERNCLK       (0UL)
#define EXMC_DMC_SAMPLE_CLK_INTERNCLK_INVT  (DMC_BACR_CKSEL_0)
#define EXMC_DMC_SAMPLE_CLK_EXTCLK          (DMC_BACR_CKSEL_1)
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
 * @retval Returned value can be one of the macros group @ref EXMC_DMC_Current_Status
 *           - EXMC_DMC_CURR_STATUS_CONFIG:   Configure status
 *           - EXMC_DMC_CURR_STATUS_RDY:      Ready status
 *           - EXMC_DMC_CURR_STATUS_PAUSED:   Pause status
 *           - EXMC_DMC_CURR_STATUS_LOWPOWER: Sleep for low power status
 */
__STATIC_INLINE uint32_t EXMC_DMC_GetStatus(void)
{
    return READ_REG32_BIT(CM_DMC->STSR, DMC_STSR_STATUS);
}

/* Initialization and configuration EXMC_DMC functions */
int32_t EXMC_DMC_StructInit(stc_exmc_dmc_init_t *pstcDmcInit);
int32_t EXMC_DMC_Init(const stc_exmc_dmc_init_t *pstcDmcInit);
void EXMC_DMC_DeInit(void);

void EXMC_DMC_Cmd(en_functional_state_t enNewState);
void EXMC_DMC_SetState(uint32_t u32State);

int32_t EXMC_DMC_ChipConfig(uint32_t u32Chip, const stc_exmc_dmc_chip_config_t *pstcChipConfig);
uint32_t EXMC_DMC_GetChipStartAddr(uint32_t u32Chip);
uint32_t EXMC_DMC_GetChipEndAddr(uint32_t u32Chip);
void EXMC_DMC_SetCommand(uint32_t u32Chip, uint32_t u32Bank, uint32_t u32Cmd, uint32_t u32Addr);

/**
 * @}
 */

#endif /* LL_DMC_ENABLE */

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

#endif /* __HC32_LL_DMC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
