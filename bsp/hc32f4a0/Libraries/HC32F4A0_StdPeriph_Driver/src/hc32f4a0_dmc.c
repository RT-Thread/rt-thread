/**
 *******************************************************************************
 * @file  hc32f4a0_dmc.c
 * @brief This file provides firmware functions to manage the EXMC DMC
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_dmc.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_EXMC_DMC EXMC_DMC
 * @brief Dynamic Memory Controller Driver Library
 * @{
 */

#if (DDL_DMC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EXMC_DMC_Local_Macros Dynamic Memory Controller Local Macros
 * @{
 */

/**
 * @defgroup EXMC_DMC_Check_Parameters_Validity EXMC DMC Check Parameters Validity
 * @{
 */

#define IS_EXMC_DMC_MEM_WIDTH(x)                                               \
(   (EXMC_DMC_MEMORY_WIDTH_16BIT == (x))        ||                             \
    (EXMC_DMC_MEMORY_WIDTH_32BIT == (x)))

#define IS_EXMC_DMC_CHIP(x)                                                    \
(   (EXMC_DMC_CHIP_0 == (x))                    ||                             \
    (EXMC_DMC_CHIP_1 == (x))                    ||                             \
    (EXMC_DMC_CHIP_2 == (x))                    ||                             \
    (EXMC_DMC_CHIP_3 == (x)))

#define IS_EXMC_DMC_BANK(x)                                                    \
(   (EXMC_DMC_BANK_0 == (x))                    ||                             \
    (EXMC_DMC_BANK_1 == (x))                    ||                             \
    (EXMC_DMC_BANK_2 == (x))                    ||                             \
    (EXMC_DMC_BANK_3 == (x)))

#define IS_EXMC_DMC_CMD(x)                                                     \
(   (EXMC_DMC_CMD_PRECHARGEALL == (x))          ||                             \
    (EXMC_DMC_CMD_AUTOREFRESH == (x))           ||                             \
    (EXMC_DMC_CMD_MDREGCONFIG == (x))           ||                             \
    (EXMC_DMC_CMD_NOP == (x)))

#define IS_EXMC_DMC_CS_DECODE_MODE(x)                                          \
(   (EXMC_DMC_CS_DECODE_ROWBANKCOL == (x))      ||                             \
    (EXMC_DMC_CS_DECODE_BANKROWCOL == (x)))

#define IS_EXMC_DMC_COLUMN_BITS_NUM(x)                                         \
(   (EXMC_DMC_COLUMN_BITS_NUM_8 == (x))         ||                             \
    (EXMC_DMC_COLUMN_BITS_NUM_9 == (x))         ||                             \
    (EXMC_DMC_COLUMN_BITS_NUM_10 == (x))        ||                             \
    (EXMC_DMC_COLUMN_BITS_NUM_11 == (x))        ||                             \
    (EXMC_DMC_COLUMN_BITS_NUM_12 == (x)))

#define IS_EXMC_DMC_ROW_BITS_NUM(x)                                            \
(   (EXMC_DMC_ROW_BITS_NUM_11 == (x))           ||                             \
    (EXMC_DMC_ROW_BITS_NUM_12 == (x))           ||                             \
    (EXMC_DMC_ROW_BITS_NUM_13 == (x))           ||                             \
    (EXMC_DMC_ROW_BITS_NUM_14 == (x))           ||                             \
    (EXMC_DMC_ROW_BITS_NUM_15 == (x))           ||                             \
    (EXMC_DMC_ROW_BITS_NUM_16 == (x)))

#define IS_EXMC_DMC_AUTO_PRECHARGE_PIN(x)                                      \
(   (EXMC_DMC_AUTO_PRECHARGE_A8 == (x))         ||                             \
    (EXMC_DMC_AUTO_PRECHARGE_A10 == (x)))

#define IS_EXMC_DMC_CKE_OUTPUT_SEL(x)                                          \
(   (EXMC_DMC_CKE_OUTPUT_ENABLE == (x))         ||                             \
    (EXMC_DMC_CKE_OUTPUT_DISABLE == (x)))

#define EXMC_DMC_MEMCLK_SEL(x)                                                 \
(   (EXMC_DMC_MEMCLK_NORMAL_OUTPUT == (x))      ||                             \
    (EXMC_DMC_MEMCLK_NOP_STOP_OUTPUT == (x)))

#define IS_EXMC_DMC_MEM_BURST(x)                                               \
(   (EXMC_DMC_MEM_BURST_1 == (x))               ||                             \
    (EXMC_DMC_MEM_BURST_2 == (x))               ||                             \
    (EXMC_DMC_MEM_BURST_4 == (x))               ||                             \
    (EXMC_DMC_MEM_BURST_8 == (x))               ||                             \
    (EXMC_DMC_MEM_BURST_16 == (x)))

#define IS_EXMC_DMC_AUTO_REFRESH_CHIPS(x)                                      \
(   (EXMC_DMC_AUTO_REFRESH_CHIP_0 == (x))       ||                             \
    (EXMC_DMC_AUTO_REFRESH_CHIPS_01 == (x))     ||                             \
    (EXMC_DMC_AUTO_REFRESH_CHIPS_012 == (x))    ||                             \
    (EXMC_DMC_AUTO_REFRESH_CHIPS_0123 == (x)))

#define IS_EXMC_DMC_CS_ADDRESS_MASK(x)                                         \
(   (EXMC_DMC_ADDR_MASK_16MB == (x))            ||                             \
    (EXMC_DMC_ADDR_MASK_32MB == (x))            ||                             \
    (EXMC_DMC_ADDR_MASK_64MB == (x))            ||                             \
    (EXMC_DMC_ADDR_MASK_128MB == (x)))

#define IS_EXMC_DMC_CS_ADDRESS_MATCH(x)                                         \
(   (EXMC_DMC_ADDR_MATCH_0X80000000 == (x))     ||                             \
    (EXMC_DMC_ADDR_MATCH_0X81000000 == (x))     ||                             \
    (EXMC_DMC_ADDR_MATCH_0X82000000 == (x))     ||                             \
    (EXMC_DMC_ADDR_MATCH_0X83000000 == (x))     ||                             \
    (EXMC_DMC_ADDR_MATCH_0X84000000 == (x))     ||                             \
    (EXMC_DMC_ADDR_MATCH_0X85000000 == (x))     ||                             \
    (EXMC_DMC_ADDR_MATCH_0X86000000 == (x))     ||                             \
    (EXMC_DMC_ADDR_MATCH_0X87000000 == (x)))

#define IS_EXMC_DMC_ADDRESS(match, mask)                                       \
(   (~((((mask) >> DMC_CSCR_ADDMSK_POS) ^ ((match) >> DMC_CSCR_ADDMAT_POS)) << 24UL)) <= 0x87FFFFFFUL)

#define IS_EXMC_DMC_STATE(x)                                                   \
(   (EXMC_DMC_CTL_STATE_GO == (x))              ||                             \
    (EXMC_DMC_CTL_STATE_SLEEP == (x))           ||                             \
    (EXMC_DMC_CTL_STATE_WAKEUP == (x))          ||                             \
    (EXMC_DMC_CTL_STATE_PAUSE == (x))           ||                             \
    (EXMC_DMC_CTL_STATE_CONFIGURE == (x)))

#define IS_EXMC_DMC_TIMING_CASL_CYCLE(x)        ((x) <= 7UL)

#define IS_EXMC_DMC_TIMING_DQSS_CYCLE(x)        ((x) <= 3UL)

#define IS_EXMC_DMC_TIMING_MRD_CYCLE(x)         ((x) <= 0x7FUL)

#define IS_EXMC_DMC_TIMING_RAS_CYCLE(x)         ((x) <= 0x0FUL)

#define IS_EXMC_DMC_TIMING_RC_CYCLE(x)          ((x) <= 0x0FUL)

#define IS_EXMC_DMC_TIMING_RCD_CYCLE(x)         ((x) <= 7UL)

#define IS_EXMC_DMC_TIMING_RFC_CYCLE(x)         ((x) <= 0x1FUL)

#define IS_EXMC_DMC_TIMING_RP_CYCLE(x)          ((x) <= 7UL)

#define IS_EXMC_DMC_TIMING_RRD_CYCLE(x)         ((x) <= 0x0FUL)

#define IS_EXMC_DMC_TIMING_WR_CYCLE(x)          ((x) <= 7UL)

#define IS_EXMC_DMC_TIMING_WTR_CYCLE(x)         ((x) <= 7UL)

#define IS_EXMC_DMC_TIMING_XP_CYCLE(x)          ((x) <= 0xFFUL)

#define IS_EXMC_DMC_TIMING_XSR_CYCLE(x)         ((x) <= 0xFFUL)

#define IS_EXMC_DMC_TIMING_ESR_CYCLE(x)         ((x) <= 0xFFUL)

#define IS_EXMC_DMC_CKE_DISABLE_PERIOD(x)       ((x) <= 0x3FUL)

#define IS_EXMC_DMC_CMDADD(x)                   ((x) <= 0x7FFFUL)

#define IS_EXMC_DMC_REFRESH_PERIOD(x)           ((x) <= 0x7FFFUL)

/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Register EXMC DMC Register
 * @{
 */
#define EXMC_DMC_CSCRx(__CHIPx__)       ((__IO uint32_t *)(((uint32_t)(&M4_DMC->CSCR0))  + (4UL * (__CHIPx__))))
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
 * @defgroup EXMC_DMC_Global_Functions Dynamic Memory Controller Global Functions
 * @{
 */

/**
 * @brief  Initialize EXMC DMC function.
 * @param  [in] pstcInit                Pointer to a @ref stc_exmc_dmc_init_t structure (EXMC DMC function configuration structure).
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t EXMC_DMC_Init(const stc_exmc_dmc_init_t *pstcInit)
{
    uint32_t u32RegVal;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check the pointer pstcInit */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_DMC_MEM_WIDTH(pstcInit->u32DmcMemWidth));
        DDL_ASSERT(IS_EXMC_DMC_REFRESH_PERIOD(pstcInit->u32RefreshPeriod));
        DDL_ASSERT(IS_EXMC_DMC_COLUMN_BITS_NUM(pstcInit->stcChipCfg.u32ColumnBitsNumber));
        DDL_ASSERT(IS_EXMC_DMC_ROW_BITS_NUM(pstcInit->stcChipCfg.u32RowBitsNumber));
        DDL_ASSERT(IS_EXMC_DMC_AUTO_PRECHARGE_PIN(pstcInit->stcChipCfg.u32AutoPrechargePin));
        DDL_ASSERT(IS_EXMC_DMC_CKE_OUTPUT_SEL(pstcInit->stcChipCfg.u32CkeOutputSel));
        DDL_ASSERT(EXMC_DMC_MEMCLK_SEL(pstcInit->stcChipCfg.u32MemClkSel));
        DDL_ASSERT(IS_EXMC_DMC_CKE_DISABLE_PERIOD(pstcInit->stcChipCfg.u32CkeDisablePeriod));
        DDL_ASSERT(IS_EXMC_DMC_MEM_BURST(pstcInit->stcChipCfg.u32MemBurst));
        DDL_ASSERT(IS_EXMC_DMC_AUTO_REFRESH_CHIPS(pstcInit->stcChipCfg.u32AutoRefreshChips));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_CASL_CYCLE(pstcInit->stcTimingCfg.u32CASL));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_DQSS_CYCLE(pstcInit->stcTimingCfg.u32DQSS));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_MRD_CYCLE(pstcInit->stcTimingCfg.u32MRD));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RAS_CYCLE(pstcInit->stcTimingCfg.u32RAS));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RC_CYCLE(pstcInit->stcTimingCfg.u32RC));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RCD_CYCLE(pstcInit->stcTimingCfg.u32RCD));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RFC_CYCLE(pstcInit->stcTimingCfg.u32RFC));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RP_CYCLE(pstcInit->stcTimingCfg.u32RP));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RRD_CYCLE(pstcInit->stcTimingCfg.u32RRD));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_WR_CYCLE(pstcInit->stcTimingCfg.u32WR));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_WTR_CYCLE(pstcInit->stcTimingCfg.u32WTR));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_XP_CYCLE(pstcInit->stcTimingCfg.u32XP));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_XSR_CYCLE(pstcInit->stcTimingCfg.u32XSR));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_ESR_CYCLE(pstcInit->stcTimingCfg.u32ESR));

        /* Set memrory width(16bit or 32bit) for DMC.*/
        MODIFY_REG32(M4_DMC->BACR, DMC_BACR_DMCMW, pstcInit->u32DmcMemWidth);

        /* set auto refresh period*/
        WRITE_REG32(M4_DMC->RFTR, pstcInit->u32RefreshPeriod);

        /* Set timing parameters for DMC.*/
        WRITE_REG32(M4_DMC->TMCR_T_CASL, pstcInit->stcTimingCfg.u32CASL);
        WRITE_REG32(M4_DMC->TMCR_T_DQSS, pstcInit->stcTimingCfg.u32DQSS);
        WRITE_REG32(M4_DMC->TMCR_T_MRD, pstcInit->stcTimingCfg.u32MRD);
        WRITE_REG32(M4_DMC->TMCR_T_RAS, pstcInit->stcTimingCfg.u32RAS);
        WRITE_REG32(M4_DMC->TMCR_T_RC, pstcInit->stcTimingCfg.u32RC);
        WRITE_REG32(M4_DMC->TMCR_T_RRD, pstcInit->stcTimingCfg.u32RRD);
        WRITE_REG32(M4_DMC->TMCR_T_WR, pstcInit->stcTimingCfg.u32WR);
        WRITE_REG32(M4_DMC->TMCR_T_WTR, pstcInit->stcTimingCfg.u32WTR);
        WRITE_REG32(M4_DMC->TMCR_T_XP, pstcInit->stcTimingCfg.u32XP);
        WRITE_REG32(M4_DMC->TMCR_T_XSR, pstcInit->stcTimingCfg.u32XSR);
        WRITE_REG32(M4_DMC->TMCR_T_ESR, pstcInit->stcTimingCfg.u32ESR);
        MODIFY_REG32(M4_DMC->TMCR_T_RP, DMC_TMCR_T_RP_T_RP, pstcInit->stcTimingCfg.u32RP);
        MODIFY_REG32(M4_DMC->TMCR_T_RCD, DMC_TMCR_T_RCD_T_RCD, pstcInit->stcTimingCfg.u32RCD);
        MODIFY_REG32(M4_DMC->TMCR_T_RFC, DMC_TMCR_T_RFC_T_RFC, pstcInit->stcTimingCfg.u32RFC);

        /* Set base parameters for DMC: burst lenth, Rowbitwidth,ColbitWidth etc.*/
        u32RegVal = (pstcInit->stcChipCfg.u32ColumnBitsNumber | \
                     pstcInit->stcChipCfg.u32RowBitsNumber | \
                     pstcInit->stcChipCfg.u32AutoPrechargePin | \
                     pstcInit->stcChipCfg.u32CkeOutputSel | \
                     pstcInit->stcChipCfg.u32MemClkSel | \
                     (pstcInit->stcChipCfg.u32CkeDisablePeriod << DMC_CPCR_CKEDISPRD_POS) | \
                     pstcInit->stcChipCfg.u32MemBurst | \
                     pstcInit->stcChipCfg.u32AutoRefreshChips);
        WRITE_REG32(M4_DMC->CPCR, u32RegVal);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize EXMC DMC function.
 * @param  None
 * @retval None
 */
void EXMC_DMC_DeInit(void)
{
    /* Disable */
    WRITE_REG32(bM4_PERIC->EXMC_ENAR_b.DMCEN, 0UL);

    /* Configures the registers to reset value. */
    WRITE_REG32(M4_DMC->CPCR, 0x00020040UL);

    WRITE_REG32(M4_DMC->TMCR_T_CASL, 0x00000003UL);
    WRITE_REG32(M4_DMC->TMCR_T_DQSS, 0x00000001UL);
    WRITE_REG32(M4_DMC->TMCR_T_MRD, 0x00000002UL);
    WRITE_REG32(M4_DMC->TMCR_T_RAS, 0x00000007UL);
    WRITE_REG32(M4_DMC->TMCR_T_RC, 0x0000000BUL);
    WRITE_REG32(M4_DMC->TMCR_T_RCD, 0x00000035UL);
    WRITE_REG32(M4_DMC->TMCR_T_RFC, 0x00001012UL);
    WRITE_REG32(M4_DMC->TMCR_T_RP, 0x00000035UL);
    WRITE_REG32(M4_DMC->TMCR_T_RRD, 0x00000002UL);
    WRITE_REG32(M4_DMC->TMCR_T_WR, 0x00000003UL);
    WRITE_REG32(M4_DMC->TMCR_T_WTR, 0x00000002UL);
    WRITE_REG32(M4_DMC->TMCR_T_XP, 0x00000001UL);
    WRITE_REG32(M4_DMC->TMCR_T_XSR, 0x0000000AUL);
    WRITE_REG32(M4_DMC->TMCR_T_ESR, 0x00000014UL);
}

/**
 * @brief  Set the fields of structure stc_exmc_dmc_init_t to default values
 * @param  [out] pstcInit               Pointer to a @ref stc_exmc_dmc_init_t structure (EXMC DMC function configuration structure)
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t EXMC_DMC_StructInit(stc_exmc_dmc_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcInit)
    {
        pstcInit->u32DmcMemWidth = EXMC_DMC_MEMORY_WIDTH_16BIT;
        pstcInit->u32RefreshPeriod = 0xA60UL;
        pstcInit->stcChipCfg.u32ColumnBitsNumber = EXMC_DMC_COLUMN_BITS_NUM_8;
        pstcInit->stcChipCfg.u32RowBitsNumber = EXMC_DMC_ROW_BITS_NUM_15;
        pstcInit->stcChipCfg.u32AutoPrechargePin = EXMC_DMC_AUTO_PRECHARGE_A10;
        pstcInit->stcChipCfg.u32CkeOutputSel = EXMC_DMC_CKE_OUTPUT_ENABLE;
        pstcInit->stcChipCfg.u32MemClkSel = EXMC_DMC_MEMCLK_NORMAL_OUTPUT;
        pstcInit->stcChipCfg.u32CkeDisablePeriod = 0UL;
        pstcInit->stcChipCfg.u32MemBurst = EXMC_DMC_MEM_BURST_4;
        pstcInit->stcChipCfg.u32AutoRefreshChips = EXMC_DMC_AUTO_REFRESH_CHIP_0;

        pstcInit->stcTimingCfg.u32CASL = 0x3UL;
        pstcInit->stcTimingCfg.u32DQSS = 0x1UL;
        pstcInit->stcTimingCfg.u32MRD = 0x02UL;
        pstcInit->stcTimingCfg.u32RAS = 0x07UL;
        pstcInit->stcTimingCfg.u32RC = 0x0BUL;
        pstcInit->stcTimingCfg.u32RCD = 0x05UL;
        pstcInit->stcTimingCfg.u32RFC = 0x12UL;
        pstcInit->stcTimingCfg.u32RP = 0x05UL;
        pstcInit->stcTimingCfg.u32RRD = 0x02UL;
        pstcInit->stcTimingCfg.u32WR = 0x03UL;
        pstcInit->stcTimingCfg.u32WTR = 0x02UL;
        pstcInit->stcTimingCfg.u32XP = 0x01UL;
        pstcInit->stcTimingCfg.u32XSR = 0x0AUL;
        pstcInit->stcTimingCfg.u32ESR = 0x14UL;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable/disable DMC.
 * @param  [in]  enNewState                 An en_functional_state_t enumeration value.
 *         This parameter can be one of the following values:
 *           @arg Enable:                   Enable function.
 *           @arg Disable:                  Disable function.
 * @retval None
 */
void EXMC_DMC_Cmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bM4_PERIC->EXMC_ENAR_b.DMCEN, enNewState);
}

/**
 * @brief  Configure EXMC DMC CS function.
 * @param  [in] u32Chip                     The command chip number.
 *         This parameter can be one of the following values:
 *           @arg EXMC_DMC_CHIP_0:          Chip 0
 *           @arg EXMC_DMC_CHIP_1:          Chip 1
 *           @arg EXMC_DMC_CHIP_2:          Chip 2
 *           @arg EXMC_DMC_CHIP_3:          Chip 3
 * @param  [in] pstcCfg                 Pointer to a @ref stc_exmc_dmc_cs_cfg_t structure (EXMC DMC CS function configuration structure).
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcCfg = NULL
 */
en_result_t EXMC_DMC_CsConfig(uint32_t u32Chip,
                                const stc_exmc_dmc_cs_cfg_t *pstcCfg)
{
    uint32_t u32RegVal;
    __IO uint32_t *DMC_CSCRx;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check the pointer pstcInit */
    if (NULL != pstcCfg)
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_DMC_CHIP(u32Chip));
        DDL_ASSERT(IS_EXMC_DMC_CS_ADDRESS_MASK(pstcCfg->u32AddrMask));
        DDL_ASSERT(IS_EXMC_DMC_CS_ADDRESS_MATCH(pstcCfg->u32AddrMatch));
        DDL_ASSERT(IS_EXMC_DMC_CS_DECODE_MODE(pstcCfg->u32AddrDecodeMode));
        DDL_ASSERT(IS_EXMC_DMC_ADDRESS(pstcCfg->u32AddrMatch, pstcCfg->u32AddrMask));

        /* Set chip selection for DMC.*/
        DMC_CSCRx = EXMC_DMC_CSCRx(u32Chip);
        u32RegVal = (pstcCfg->u32AddrMask | pstcCfg->u32AddrMatch | pstcCfg->u32AddrDecodeMode);
        WRITE_REG32(*DMC_CSCRx, u32RegVal);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get the start address of the specified DMC chip.
 * @param  [in] u32Chip                     The chip number.
 *         This parameter can be one of the following values:
 *           @arg EXMC_DMC_CHIP_0:          Chip 0
 *           @arg EXMC_DMC_CHIP_1:          Chip 1
 *           @arg EXMC_DMC_CHIP_2:          Chip 2
 *           @arg EXMC_DMC_CHIP_3:          Chip 3
 * @retval The start address of the specified DMC chip.
 */
uint32_t EXMC_DMC_ChipStartAddress(uint32_t u32Chip)
{
    __IO uint32_t *DMC_CSCRx;

    /* Check parameters */
    DDL_ASSERT(IS_EXMC_DMC_CHIP(u32Chip));

    DMC_CSCRx = EXMC_DMC_CSCRx(u32Chip);
    return (READ_REG32_BIT(*DMC_CSCRx, DMC_CSCR_ADDMAT) << 16UL);
}

/**
 * @brief  Get the end address of the specified DMC chip.
 * @param  [in] u32Chip                     The chip number.
 *         This parameter can be one of the following values:
 *           @arg EXMC_DMC_CHIP_0:          Chip 0
 *           @arg EXMC_DMC_CHIP_1:          Chip 1
 *           @arg EXMC_DMC_CHIP_2:          Chip 2
 *           @arg EXMC_DMC_CHIP_3:          Chip 3
 * @retval The end address of the specified DMC chip
 */
uint32_t EXMC_DMC_ChipEndAddress(uint32_t u32Chip)
{
    uint32_t u32Mask;
    uint32_t u32Match;
    __IO uint32_t *DMC_CSCRx;

    /* Check parameters */
    DDL_ASSERT(IS_EXMC_DMC_CHIP(u32Chip));

    DMC_CSCRx = EXMC_DMC_CSCRx(u32Chip);
    u32Mask =   (READ_REG32_BIT(*DMC_CSCRx, DMC_CSCR_ADDMSK) >> DMC_CSCR_ADDMSK_POS);
    u32Match =  (READ_REG32_BIT(*DMC_CSCRx, DMC_CSCR_ADDMAT) >> DMC_CSCR_ADDMAT_POS);

    return (~((u32Match ^ u32Mask) << 24UL));
}

/**
 * @brief  Set EXMC SMC command.
 * @param  [in] u32Chip                     The command chip number.
 *         This parameter can be one of the following values:
 *           @arg EXMC_DMC_CHIP_0:          Chip 0
 *           @arg EXMC_DMC_CHIP_1:          Chip 1
 *           @arg EXMC_DMC_CHIP_2:          Chip 2
 *           @arg EXMC_DMC_CHIP_3:          Chip 3
 * @param  [in] u32Bank                     The command bank.
 *         This parameter can be one of the following values:
 *           @arg EXMC_DMC_BANK_0:          Bank 0
 *           @arg EXMC_DMC_BANK_1:          Bank 1
 *           @arg EXMC_DMC_BANK_2:          Bank 2
 *           @arg EXMC_DMC_BANK_3:          Bank 3
 * @param  [in] u32Cmd                      The command.
 *         This parameter can be one of the following values:
 *           @arg EXMC_DMC_CMD_PRECHARGEALL:Precharge all
 *           @arg EXMC_DMC_CMD_AUTOREFRESH: Auto refresh
 *           @arg EXMC_DMC_CMD_MDREGCONFIG: Set memory device mode register
 *           @arg EXMC_DMC_CMD_NOP:         NOP
 * @param  [in] u32Address                  The address parameter for CMD MdRegConfig only.
 *         This parameter can be a value between Min_Data = 0 and Max_Data = 0x7FFFUL
 * @retval An en_result_t enumeration value:
 *           - Ok: Command success
 */
en_result_t EXMC_DMC_SetCommand(uint32_t u32Chip,
                                    uint32_t u32Bank,
                                    uint32_t u32Cmd,
                                    uint32_t u32Address)
{
    uint32_t u32DmcCmdr;

    /* Check parameters */
    DDL_ASSERT(IS_EXMC_DMC_CHIP(u32Chip));
    DDL_ASSERT(IS_EXMC_DMC_BANK(u32Bank));
    DDL_ASSERT(IS_EXMC_DMC_CMD(u32Cmd));
    DDL_ASSERT(IS_EXMC_DMC_CMDADD(u32Address));

    /* Set DMC_CMDR register for DMC.*/
    u32DmcCmdr = (u32Address | \
                  (u32Bank << DMC_CMDR_CMDBA_POS) | \
                  u32Cmd | \
                  (u32Chip << DMC_CMDR_CMDCHIP_POS));
    WRITE_REG32(M4_DMC->CMDR, u32DmcCmdr);

    return Ok;
}

/**
 * @brief  Set EXMC DMC state.
 * @param  [in] u32State                    The command chip number.
 *           @arg EXMC_DMC_CTL_STATE_GO:        Go
 *           @arg EXMC_DMC_CTL_STATE_SLEEP:     Sleep for low power
 *           @arg EXMC_DMC_CTL_STATE_WAKEUP:    Wake up
 *           @arg EXMC_DMC_CTL_STATE_PAUSE:     Pause
 *           @arg EXMC_DMC_CTL_STATE_CONFIGURE: Configure
 * @retval None
 */
void EXMC_DMC_SetState(uint32_t u32State)
{
    DDL_ASSERT(IS_EXMC_DMC_STATE(u32State));

    WRITE_REG32(M4_DMC->STCR, u32State);
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
