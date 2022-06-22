/**
 *******************************************************************************
 * @file  hc32_ll_dmc.c
 * @brief This file provides firmware functions to manage the EXMC_DMC
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_dmc.h"
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
 * @defgroup LL_DMC DMC
 * @brief Dynamic Memory Controller Driver Library
 * @{
 */

#if (LL_DMC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EXMC_DMC_Local_Macros EXMC_DMC Local Macros
 * @{
 */

/**
 * @defgroup EXMC_DMC_Check_Parameters_Validity EXMC_DMC Check Parameters Validity
 * @{
 */

#define IS_EXMC_DMC_MEM_WIDTH(x)                                               \
(   ((x) == EXMC_DMC_MEMORY_WIDTH_16BIT)        ||                             \
    ((x) == EXMC_DMC_MEMORY_WIDTH_32BIT))

#define IS_EXMC_DMC_CHIP(x)                                                    \
(   ((x) == EXMC_DMC_CHIP0)                     ||                             \
    ((x) == EXMC_DMC_CHIP1)                     ||                             \
    ((x) == EXMC_DMC_CHIP2)                     ||                             \
    ((x) == EXMC_DMC_CHIP3))

#define IS_EXMC_DMC_BANK(x)                                                    \
(   ((x) == EXMC_DMC_BANK0)                     ||                             \
    ((x) == EXMC_DMC_BANK1)                     ||                             \
    ((x) == EXMC_DMC_BANK2)                     ||                             \
    ((x) == EXMC_DMC_BANK3))

#define IS_EXMC_DMC_CMD(x)                                                     \
(   ((x) == EXMC_DMC_CMD_PRECHARGE_ALL)         ||                             \
    ((x) == EXMC_DMC_CMD_AUTO_REFRESH)          ||                             \
    ((x) == EXMC_DMC_CMD_MDREG_CONFIG)          ||                             \
    ((x) == EXMC_DMC_CMD_NOP))

#define IS_EXMC_DMC_CS_DECODE_MD(x)                                            \
(   ((x) == EXMC_DMC_CS_DECODE_ROWBANKCOL)      ||                             \
    ((x) == EXMC_DMC_CS_DECODE_BANKROWCOL))

#define IS_EXMC_DMC_COLUMN_BITS_NUM(x)                                         \
(   ((x) == EXMC_DMC_COLUMN_BITS_NUM8)          ||                             \
    ((x) == EXMC_DMC_COLUMN_BITS_NUM9)          ||                             \
    ((x) == EXMC_DMC_COLUMN_BITS_NUM10)         ||                             \
    ((x) == EXMC_DMC_COLUMN_BITS_NUM11)         ||                             \
    ((x) == EXMC_DMC_COLUMN_BITS_NUM12))

#define IS_EXMC_DMC_ROW_BITS_NUM(x)                                            \
(   ((x) == EXMC_DMC_ROW_BITS_NUM11)            ||                             \
    ((x) == EXMC_DMC_ROW_BITS_NUM12)            ||                             \
    ((x) == EXMC_DMC_ROW_BITS_NUM13)            ||                             \
    ((x) == EXMC_DMC_ROW_BITS_NUM14)            ||                             \
    ((x) == EXMC_DMC_ROW_BITS_NUM15)            ||                             \
    ((x) == EXMC_DMC_ROW_BITS_NUM16))

#define IS_EXMC_DMC_AUTO_PRECHARGE_PIN(x)                                      \
(   ((x) == EXMC_DMC_AUTO_PRECHARGE_A8)         ||                             \
    ((x) == EXMC_DMC_AUTO_PRECHARGE_A10))

#define IS_EXMC_DMC_CKE_OUTPUT_SEL(x)                                          \
(   ((x) == EXMC_DMC_CKE_OUTPUT_ENABLE)         ||                             \
    ((x) == EXMC_DMC_CKE_OUTPUT_DISABLE))

#define EXMC_DMC_CLK_SEL(x)                                                    \
(   ((x) == EXMC_DMC_CLK_NORMAL_OUTPUT)         ||                             \
    ((x) == EXMC_DMC_CLK_NOP_STOP_OUTPUT))

#define IS_EXMC_DMC_BURST(x)                                                   \
(   ((x) == EXMC_DMC_BURST_1BEAT)               ||                             \
    ((x) == EXMC_DMC_BURST_2BEAT)               ||                             \
    ((x) == EXMC_DMC_BURST_4BEAT)               ||                             \
    ((x) == EXMC_DMC_BURST_8BEAT)               ||                             \
    ((x) == EXMC_DMC_BURST_16BEAT))

#define IS_EXMC_DMC_AUTO_REFRESH_CHIPS(x)                                      \
(   ((x) == EXMC_DMC_AUTO_REFRESH_1CHIP)        ||                             \
    ((x) == EXMC_DMC_AUTO_REFRESH_2CHIPS)       ||                             \
    ((x) == EXMC_DMC_AUTO_REFRESH_3CHIPS)       ||                             \
    ((x) == EXMC_DMC_AUTO_REFRESH_4CHIPS))

#define IS_EXMC_DMC_MAP_ADDR(match, msk)                                       \
(   (EXMC_DMC_MAP_ADDR((match), (msk)) >= EXMC_DMC_ADDR_MIN) &&                \
    (EXMC_DMC_MAP_ADDR((match), (msk)) <= EXMC_DMC_ADDR_MAX))

#define IS_EXMC_DMC_STATE(x)                                                   \
(   ((x) == EXMC_DMC_CTRL_STATE_GO)             ||                             \
    ((x) == EXMC_DMC_CTRL_STATE_SLEEP)          ||                             \
    ((x) == EXMC_DMC_CTRL_STATE_WAKEUP)         ||                             \
    ((x) == EXMC_DMC_CTRL_STATE_PAUSE)          ||                             \
    ((x) == EXMC_DMC_CTRL_STATE_CONFIG))

#define IS_EXMC_DMC_SAMPLE_CLK(x)                                              \
(   ((x) == EXMC_DMC_SAMPLE_CLK_EXTCLK)         ||                             \
    ((x) == EXMC_DMC_SAMPLE_CLK_INTERNCLK)      ||                             \
    ((x) == EXMC_DMC_SAMPLE_CLK_INTERNCLK_INVT))

#define IS_EXMC_DMC_TIMING_CASL_CYCLE(x)        ((x) <= 7UL)

#define IS_EXMC_DMC_TIMING_DQSS_CYCLE(x)        ((x) <= 3UL)

#define IS_EXMC_DMC_TIMING_MRD_CYCLE(x)         ((x) <= 0x7FUL)

#define IS_EXMC_DMC_TIMING_RAS_CYCLE(x)         ((x) <= 0x0FUL)

#define IS_EXMC_DMC_TIMING_RC_CYCLE(x)          ((x) <= 0x0FUL)

#define IS_EXMC_DMC_TIMING_RCD_B_CYCLE(x)       ((x) <= 7UL)

#define IS_EXMC_DMC_TIMING_RCD_P_CYCLE(x)       ((x) <= 7UL)

#define IS_EXMC_DMC_TIMING_RFC_B_CYCLE(x)       ((x) <= 0x1FUL)

#define IS_EXMC_DMC_TIMING_RFC_P_CYCLE(x)       ((x) <= 0x1FUL)

#define IS_EXMC_DMC_TIMING_RP_B_CYCLE(x)        ((x) <= 7UL)

#define IS_EXMC_DMC_TIMING_RP_P_CYCLE(x)        ((x) <= 7UL)

#define IS_EXMC_DMC_TIMING_RRD_CYCLE(x)         ((x) <= 0x0FUL)

#define IS_EXMC_DMC_TIMING_WR_CYCLE(x)          ((x) <= 7UL)

#define IS_EXMC_DMC_TIMING_WTR_CYCLE(x)         ((x) <= 7UL)

#define IS_EXMC_DMC_CKE_DISABLE_PERIOD(x)       ((x) <= 0x3FUL)

#define IS_EXMC_DMC_CMD_ADDR(x)                 ((x) <= 0x7FFFUL)

#define IS_EXMC_DMC_REFRESH_PERIOD(x)           ((x) <= 0x7FFFUL)

/**
 * @}
 */

/**
 * @defgroup EXMC_DMC_Register EXMC_DMC Register
 * @{
 */
#define EXMC_DMC_CSCRx(__CHIPx__)       ((__IO uint32_t *)(((uint32_t)(&CM_DMC->CSCR0))  + (4UL * (__CHIPx__))))
/**
 * @}
 */

/* EXMC_DMC map address */
#define EXMC_DMC_MAP_ADDR(MATCH, MSK)   ((~((MATCH) ^ (MSK))) << 24U)

/**
 * @defgroup EXMC_DMC_Timing EXMC_DMC Timing
 * @{
 */
#define DMC_TMCR_RP_MASK                (DMC_TMCR_T_RP_T_RP_B   | DMC_TMCR_T_RP_T_RP_P)
#define DMC_TMCR_RCD_MASK               (DMC_TMCR_T_RCD_T_RCD_B | DMC_TMCR_T_RCD_T_RCD_P)
#define DMC_TMCR_RFC_MASK               (DMC_TMCR_T_RFC_T_RFC_B | DMC_TMCR_T_RFC_T_RFC_P)

#define DMC_TMCR_RP(x)                                                             \
((uint32_t)(x)->stcTimingConfig.u8RP_B | ((uint32_t)(x)->stcTimingConfig.u8RP_P << DMC_TMCR_T_RP_T_RP_P_POS))

#define DMC_TMCR_RCD(x)                                                            \
((uint32_t)(x)->stcTimingConfig.u8RCD_B | ((uint32_t)(x)->stcTimingConfig.u8RCD_P << DMC_TMCR_T_RCD_T_RCD_P_POS))

#define DMC_TMCR_RFC(x)                                                            \
((uint32_t)(x)->stcTimingConfig.u8RFC_B | ((uint32_t)(x)->stcTimingConfig.u8RFC_P << DMC_TMCR_T_RFC_T_RFC_P_POS))
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
 * @defgroup EXMC_DMC_Global_Functions EXMC_DMC Global Functions
 * @{
 */

/**
 * @brief  Set the fields of structure stc_exmc_dmc_init_t to default values
 * @param  [out] pstcDmcInit            Pointer to a @ref stc_exmc_dmc_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcDmcInit value is NULL.
 */
int32_t EXMC_DMC_StructInit(stc_exmc_dmc_init_t *pstcDmcInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcDmcInit) {
        pstcDmcInit->u32SampleClock = EXMC_DMC_SAMPLE_CLK_INTERNCLK;
        pstcDmcInit->u32MemoryWidth = EXMC_DMC_MEMORY_WIDTH_16BIT;
        pstcDmcInit->u32RefreshPeriod = 0xA60UL;
        pstcDmcInit->u32ColumnBitsNumber = EXMC_DMC_COLUMN_BITS_NUM8;
        pstcDmcInit->u32RowBitsNumber = EXMC_DMC_ROW_BITS_NUM15;
        pstcDmcInit->u32AutoPrechargePin = EXMC_DMC_AUTO_PRECHARGE_A10;
        pstcDmcInit->u32CkeOutputSel = EXMC_DMC_CKE_OUTPUT_ENABLE;
        pstcDmcInit->u32MemClockSel = EXMC_DMC_CLK_NORMAL_OUTPUT;
        pstcDmcInit->u32CkeDisablePeriod = 0UL;
        pstcDmcInit->u32MemBurst = EXMC_DMC_BURST_4BEAT;
        pstcDmcInit->u32AutoRefreshChips = EXMC_DMC_AUTO_REFRESH_1CHIP;

        pstcDmcInit->stcTimingConfig.u8CASL = 0x3U;
        pstcDmcInit->stcTimingConfig.u8DQSS = 0x1U;
        pstcDmcInit->stcTimingConfig.u8MRD = 0x02U;
        pstcDmcInit->stcTimingConfig.u8RAS = 0x07U;
        pstcDmcInit->stcTimingConfig.u8RC = 0x0BU;
        pstcDmcInit->stcTimingConfig.u8RCD_B = 0x05U;
        pstcDmcInit->stcTimingConfig.u8RCD_P = 0x00U;
        pstcDmcInit->stcTimingConfig.u8RFC_B = 0x12U;
        pstcDmcInit->stcTimingConfig.u8RFC_P = 0x0U;
        pstcDmcInit->stcTimingConfig.u8RP_B = 0x05U;
        pstcDmcInit->stcTimingConfig.u8RP_P = 0x00U;
        pstcDmcInit->stcTimingConfig.u8RRD = 0x02U;
        pstcDmcInit->stcTimingConfig.u8WR = 0x03U;
        pstcDmcInit->stcTimingConfig.u8WTR = 0x02U;
        pstcDmcInit->stcTimingConfig.u8XP = 0x01U;
        pstcDmcInit->stcTimingConfig.u8XSR = 0x0AU;
        pstcDmcInit->stcTimingConfig.u8ESR = 0x14U;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize EXMC_DMC function.
 * @param  [in] pstcDmcInit             Pointer to a @ref stc_exmc_dmc_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcDmcInit value is NULL.
 */
int32_t EXMC_DMC_Init(const stc_exmc_dmc_init_t *pstcDmcInit)
{
    uint32_t u32RegVal;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcDmcInit) {
        DDL_ASSERT(IS_EXMC_DMC_SAMPLE_CLK(pstcDmcInit->u32SampleClock));
        DDL_ASSERT(IS_EXMC_DMC_MEM_WIDTH(pstcDmcInit->u32MemoryWidth));
        DDL_ASSERT(IS_EXMC_DMC_REFRESH_PERIOD(pstcDmcInit->u32RefreshPeriod));
        DDL_ASSERT(IS_EXMC_DMC_COLUMN_BITS_NUM(pstcDmcInit->u32ColumnBitsNumber));
        DDL_ASSERT(IS_EXMC_DMC_ROW_BITS_NUM(pstcDmcInit->u32RowBitsNumber));
        DDL_ASSERT(IS_EXMC_DMC_AUTO_PRECHARGE_PIN(pstcDmcInit->u32AutoPrechargePin));
        DDL_ASSERT(IS_EXMC_DMC_CKE_OUTPUT_SEL(pstcDmcInit->u32CkeOutputSel));
        DDL_ASSERT(EXMC_DMC_CLK_SEL(pstcDmcInit->u32MemClockSel));
        DDL_ASSERT(IS_EXMC_DMC_CKE_DISABLE_PERIOD(pstcDmcInit->u32CkeDisablePeriod));
        DDL_ASSERT(IS_EXMC_DMC_BURST(pstcDmcInit->u32MemBurst));
        DDL_ASSERT(IS_EXMC_DMC_AUTO_REFRESH_CHIPS(pstcDmcInit->u32AutoRefreshChips));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_CASL_CYCLE(pstcDmcInit->stcTimingConfig.u8CASL));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_DQSS_CYCLE(pstcDmcInit->stcTimingConfig.u8DQSS));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_MRD_CYCLE(pstcDmcInit->stcTimingConfig.u8MRD));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RAS_CYCLE(pstcDmcInit->stcTimingConfig.u8RAS));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RC_CYCLE(pstcDmcInit->stcTimingConfig.u8RC));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RCD_B_CYCLE(pstcDmcInit->stcTimingConfig.u8RCD_B));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RCD_P_CYCLE(pstcDmcInit->stcTimingConfig.u8RCD_P));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RFC_B_CYCLE(pstcDmcInit->stcTimingConfig.u8RFC_B));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RFC_P_CYCLE(pstcDmcInit->stcTimingConfig.u8RFC_P));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RP_B_CYCLE(pstcDmcInit->stcTimingConfig.u8RP_B));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RP_P_CYCLE(pstcDmcInit->stcTimingConfig.u8RP_P));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_RRD_CYCLE(pstcDmcInit->stcTimingConfig.u8RRD));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_WR_CYCLE(pstcDmcInit->stcTimingConfig.u8WR));
        DDL_ASSERT(IS_EXMC_DMC_TIMING_WTR_CYCLE(pstcDmcInit->stcTimingConfig.u8WTR));

        /* Set sample clock for DMC.*/
        MODIFY_REG32(CM_DMC->BACR, DMC_BACR_CKSEL, pstcDmcInit->u32SampleClock);

        /* Set memrory width(16bit or 32bit) for DMC.*/
        MODIFY_REG32(CM_DMC->BACR, DMC_BACR_DMCMW, pstcDmcInit->u32MemoryWidth);

        /* set auto refresh period*/
        WRITE_REG32(CM_DMC->RFTR, pstcDmcInit->u32RefreshPeriod);

        /* Set timing parameters for DMC.*/
        WRITE_REG32(CM_DMC->TMCR_T_CASL, pstcDmcInit->stcTimingConfig.u8CASL);
        WRITE_REG32(CM_DMC->TMCR_T_DQSS, pstcDmcInit->stcTimingConfig.u8DQSS);
        WRITE_REG32(CM_DMC->TMCR_T_MRD, pstcDmcInit->stcTimingConfig.u8MRD);
        WRITE_REG32(CM_DMC->TMCR_T_RAS, pstcDmcInit->stcTimingConfig.u8RAS);
        WRITE_REG32(CM_DMC->TMCR_T_RC, pstcDmcInit->stcTimingConfig.u8RC);
        WRITE_REG32(CM_DMC->TMCR_T_RRD, pstcDmcInit->stcTimingConfig.u8RRD);
        WRITE_REG32(CM_DMC->TMCR_T_WR, pstcDmcInit->stcTimingConfig.u8WR);
        WRITE_REG32(CM_DMC->TMCR_T_WTR, pstcDmcInit->stcTimingConfig.u8WTR);
        WRITE_REG32(CM_DMC->TMCR_T_XP, pstcDmcInit->stcTimingConfig.u8XP);
        WRITE_REG32(CM_DMC->TMCR_T_XSR, pstcDmcInit->stcTimingConfig.u8XSR);
        WRITE_REG32(CM_DMC->TMCR_T_ESR, pstcDmcInit->stcTimingConfig.u8ESR);
        MODIFY_REG32(CM_DMC->TMCR_T_RP, DMC_TMCR_RP_MASK, DMC_TMCR_RP(pstcDmcInit));
        MODIFY_REG32(CM_DMC->TMCR_T_RCD, DMC_TMCR_RCD_MASK, DMC_TMCR_RCD(pstcDmcInit));
        MODIFY_REG32(CM_DMC->TMCR_T_RFC, DMC_TMCR_RFC_MASK, DMC_TMCR_RFC(pstcDmcInit));

        /* Set base parameters for DMC: burst length, Rowbitwidth,ColbitWidth etc.*/
        u32RegVal = (pstcDmcInit->u32ColumnBitsNumber | pstcDmcInit->u32RowBitsNumber | \
                     pstcDmcInit->u32AutoPrechargePin | pstcDmcInit->u32CkeOutputSel | \
                     pstcDmcInit->u32AutoRefreshChips | pstcDmcInit->u32MemClockSel | \
                     (pstcDmcInit->u32CkeDisablePeriod << DMC_CPCR_CKEDISPRD_POS) | \
                     pstcDmcInit->u32MemBurst);
        WRITE_REG32(CM_DMC->CPCR, u32RegVal);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  De-Initialize EXMC_DMC function.
 * @param  None
 * @retval None
 */
void EXMC_DMC_DeInit(void)
{
    /* Disable */
    CLR_REG32_BIT(CM_PERIC->DMC_ENAR, PERIC_DMC_ENAR_DMCEN);

    /* Configures the registers to reset value. */
    WRITE_REG32(CM_DMC->CPCR, 0x00020040UL);

    WRITE_REG32(CM_DMC->TMCR_T_CASL, 0x00000003UL);
    WRITE_REG32(CM_DMC->TMCR_T_DQSS, 0x00000001UL);
    WRITE_REG32(CM_DMC->TMCR_T_MRD, 0x00000002UL);
    WRITE_REG32(CM_DMC->TMCR_T_RAS, 0x00000007UL);
    WRITE_REG32(CM_DMC->TMCR_T_RC, 0x0000000BUL);
    WRITE_REG32(CM_DMC->TMCR_T_RCD, 0x00000035UL);
    WRITE_REG32(CM_DMC->TMCR_T_RFC, 0x00001012UL);
    WRITE_REG32(CM_DMC->TMCR_T_RP, 0x00000035UL);
    WRITE_REG32(CM_DMC->TMCR_T_RRD, 0x00000002UL);
    WRITE_REG32(CM_DMC->TMCR_T_WR, 0x00000003UL);
    WRITE_REG32(CM_DMC->TMCR_T_WTR, 0x00000002UL);
    WRITE_REG32(CM_DMC->TMCR_T_XP, 0x00000001UL);
    WRITE_REG32(CM_DMC->TMCR_T_XSR, 0x0000000AUL);
    WRITE_REG32(CM_DMC->TMCR_T_ESR, 0x00000014UL);
}

/**
 * @brief  Enable/disable DMC.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void EXMC_DMC_Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_PERIC->DMC_ENAR, PERIC_DMC_ENAR_DMCEN);
    } else {
        CLR_REG32_BIT(CM_PERIC->DMC_ENAR, PERIC_DMC_ENAR_DMCEN);
    }
}

/**
 * @brief  Set EXMC_DMC state.
 * @param  [in] u32State                    The command chip number.
 *         This parameter can be one of the macros group @ref EXMC_DMC_Control_State
 *           @arg EXMC_DMC_CTRL_STATE_GO:     Go
 *           @arg EXMC_DMC_CTRL_STATE_SLEEP:  Sleep for low power
 *           @arg EXMC_DMC_CTRL_STATE_WAKEUP: Wake up
 *           @arg EXMC_DMC_CTRL_STATE_PAUSE:  Pause
 *           @arg EXMC_DMC_CTRL_STATE_CONFIG: Configure
 * @retval None
 */
void EXMC_DMC_SetState(uint32_t u32State)
{
    DDL_ASSERT(IS_EXMC_DMC_STATE(u32State));

    WRITE_REG32(CM_DMC->STCR, u32State);
}

/**
 * @brief  Configure EXMC_DMC CS function.
 * @param  [in] u32Chip                 The command chip number.
 *         This parameter can be one of the macros group @ref EXMC_DMC_Chip
 *           @arg EXMC_DMC_CHIP0:       Chip 0
 *           @arg EXMC_DMC_CHIP1:       Chip 1
 *           @arg EXMC_DMC_CHIP2:       Chip 2
 *           @arg EXMC_DMC_CHIP3:       Chip 3
 * @param  [in] pstcChipConfig          Pointer to a @ref stc_exmc_dmc_chip_config_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcConfig value is NULL.
 */
int32_t EXMC_DMC_ChipConfig(uint32_t u32Chip, const stc_exmc_dmc_chip_config_t *pstcChipConfig)
{
    uint32_t u32RegVal;
    __IO uint32_t *DMC_CSCRx;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcChipConfig) {
        DDL_ASSERT(IS_EXMC_DMC_CHIP(u32Chip));
        DDL_ASSERT(IS_EXMC_DMC_CS_DECODE_MD(pstcChipConfig->u32AddrDecodeMode));
        DDL_ASSERT(IS_EXMC_DMC_MAP_ADDR(pstcChipConfig->u32AddrMatch, pstcChipConfig->u32AddrMask));

        /* Set chip selection for DMC.*/
        DMC_CSCRx = EXMC_DMC_CSCRx(u32Chip);
        u32RegVal = ((pstcChipConfig->u32AddrMask << DMC_CSCR_ADDMSK_POS)  | \
                     (pstcChipConfig->u32AddrMatch << DMC_CSCR_ADDMAT_POS) | \
                     pstcChipConfig->u32AddrDecodeMode);
        WRITE_REG32(*DMC_CSCRx, u32RegVal);

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Get the start address of the specified DMC chip.
 * @param  [in] u32Chip                 The chip number.
 *         This parameter can be one of the macros group @ref EXMC_DMC_Chip
 *           @arg EXMC_DMC_CHIP0:       Chip 0
 *           @arg EXMC_DMC_CHIP1:       Chip 1
 *           @arg EXMC_DMC_CHIP2:       Chip 2
 *           @arg EXMC_DMC_CHIP3:       Chip 3
 * @retval The start address of the specified DMC chip.
 */
uint32_t EXMC_DMC_GetChipStartAddr(uint32_t u32Chip)
{
    __IO uint32_t *DMC_CSCRx;

    DDL_ASSERT(IS_EXMC_DMC_CHIP(u32Chip));

    DMC_CSCRx = EXMC_DMC_CSCRx(u32Chip);
    return (READ_REG32_BIT(*DMC_CSCRx, DMC_CSCR_ADDMAT) << 16U);
}

/**
 * @brief  Get the end address of the specified DMC chip.
 * @param  [in] u32Chip                 The chip number.
 *         This parameter can be one of the macros group @ref EXMC_DMC_Chip
 *           @arg EXMC_DMC_CHIP0:       Chip 0
 *           @arg EXMC_DMC_CHIP1:       Chip 1
 *           @arg EXMC_DMC_CHIP2:       Chip 2
 *           @arg EXMC_DMC_CHIP3:       Chip 3
 * @retval The end address of the specified DMC chip
 */
uint32_t EXMC_DMC_GetChipEndAddr(uint32_t u32Chip)
{
    uint32_t u32Mask;
    uint32_t u32Match;
    __IO uint32_t *DMC_CSCRx;

    DDL_ASSERT(IS_EXMC_DMC_CHIP(u32Chip));

    DMC_CSCRx = EXMC_DMC_CSCRx(u32Chip);
    u32Mask = (READ_REG32_BIT(*DMC_CSCRx, DMC_CSCR_ADDMSK) >> DMC_CSCR_ADDMSK_POS);
    u32Match = (READ_REG32_BIT(*DMC_CSCRx, DMC_CSCR_ADDMAT) >> DMC_CSCR_ADDMAT_POS);
    return EXMC_DMC_MAP_ADDR(u32Match, u32Mask);
}

/**
 * @brief  Set EXMC_SMC command.
 * @param  [in] u32Chip                 The command chip number.
 *         This parameter can be one of the macros group @ref EXMC_DMC_Chip
 *           @arg EXMC_DMC_CHIP0:       Chip 0
 *           @arg EXMC_DMC_CHIP1:       Chip 1
 *           @arg EXMC_DMC_CHIP2:       Chip 2
 *           @arg EXMC_DMC_CHIP3:       Chip 3
 * @param  [in] u32Bank                 The command bank.
 *         This parameter can be one of the macros group @ref EXMC_DMC_Bank
 *           @arg EXMC_DMC_BANK0:       Bank 0
 *           @arg EXMC_DMC_BANK1:       Bank 1
 *           @arg EXMC_DMC_BANK2:       Bank 2
 *           @arg EXMC_DMC_BANK3:       Bank 3
 * @param  [in] u32Cmd                  The command.
 *         This parameter can be one of the macros group @ref EXMC_DMC_Command
 *           @arg EXMC_DMC_CMD_PRECHARGE_ALL:Precharge all
 *           @arg EXMC_DMC_CMD_AUTO_REFRESH: Auto refresh
 *           @arg EXMC_DMC_CMD_MDREG_CONFIG: Set memory device mode register
 *           @arg EXMC_DMC_CMD_NOP:          NOP
 * @param  [in] u32Addr                 The address parameter for CMD MdRegConfig only.
 *         This parameter can be a value between Min_Data = 0 and Max_Data = 0x7FFFUL
 * @retval None
 */
void EXMC_DMC_SetCommand(uint32_t u32Chip, uint32_t u32Bank, uint32_t u32Cmd, uint32_t u32Addr)
{
    uint32_t u32RegVal;

    DDL_ASSERT(IS_EXMC_DMC_CHIP(u32Chip));
    DDL_ASSERT(IS_EXMC_DMC_BANK(u32Bank));
    DDL_ASSERT(IS_EXMC_DMC_CMD(u32Cmd));
    DDL_ASSERT(IS_EXMC_DMC_CMD_ADDR(u32Addr));

    u32RegVal = (u32Addr | (u32Bank << DMC_CMDR_CMDBA_POS) | u32Cmd | (u32Chip << DMC_CMDR_CMDCHIP_POS));
    WRITE_REG32(CM_DMC->CMDR, u32RegVal);
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
