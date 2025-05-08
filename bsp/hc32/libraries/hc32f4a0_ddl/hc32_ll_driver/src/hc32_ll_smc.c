/**
 *******************************************************************************
 * @file  hc32_ll_smc.c
 * @brief This file provides firmware functions to manage the EXMC_SMC
 *        (External Memory Controller: Static Memory Controller).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-06-30       CDT             Modify EXMC_SMC_StructInit, EXMC_SMC_Init, EXMC_SMC_GetChipConfig
                                    Delete function comments: EXMC_SMC_Chipx
   2023-06-30       CDT             Function EXMC_SMC_DeInit add return value
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_smc.h"
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
 * @defgroup LL_SMC SMC
 * @brief Static Memory Controller Driver Library
 * @{
 */

#if (LL_SMC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EXMC_SMC_Local_Macros EXMC_SMC Local Macros
 * @{
 */

/**
 * @defgroup EXMC_SMC_Check_Parameters_Validity EXMC_SMC Check Parameters Validity
 * @{
 */

#define IS_EXMC_SMC_MEMORY_WIDTH(x)                                            \
(   ((x) == EXMC_SMC_MEMORY_WIDTH_16BIT)        ||                             \
    ((x) == EXMC_SMC_MEMORY_WIDTH_32BIT))

#define IS_EXMC_SMC_READ_MD(x)                                                 \
(   ((x) == EXMC_SMC_READ_SYNC)                 ||                             \
    ((x) == EXMC_SMC_READ_ASYNC))

#define IS_EXMC_SMC_WRITE_MD(x)                                                \
(   ((x) == EXMC_SMC_WRITE_SYNC)                ||                             \
    ((x) == EXMC_SMC_WRITE_ASYNC))

#define IS_EXMC_SMC_CHIP(x)                                                    \
(   ((x) == EXMC_SMC_CHIP0)                     ||                             \
    ((x) == EXMC_SMC_CHIP1)                     ||                             \
    ((x) == EXMC_SMC_CHIP2)                     ||                             \
    ((x) == EXMC_SMC_CHIP3))

#define IS_EXMC_SMC_READ_BURST(x)                                              \
(   ((x) == EXMC_SMC_READ_BURST_1BEAT)          ||                             \
    ((x) == EXMC_SMC_READ_BURST_4BEAT)          ||                             \
    ((x) == EXMC_SMC_READ_BURST_8BEAT)          ||                             \
    ((x) == EXMC_SMC_READ_BURST_16BEAT)         ||                             \
    ((x) == EXMC_SMC_READ_BURST_32BEAT)         ||                             \
    ((x) == EXMC_SMC_READ_BURST_CONTINUOUS))

#define IS_EXMC_SMC_WRITE_BURST(x)                                             \
(   ((x) == EXMC_SMC_WRITE_BURST_1BEAT)         ||                             \
    ((x) == EXMC_SMC_WRITE_BURST_4BEAT)         ||                             \
    ((x) == EXMC_SMC_WRITE_BURST_8BEAT)         ||                             \
    ((x) == EXMC_SMC_WRITE_BURST_16BEAT)        ||                             \
    ((x) == EXMC_SMC_WRITE_BURST_32BEAT)        ||                             \
    ((x) == EXMC_SMC_WRITE_BURST_CONTINUOUS))

#define IS_EXMC_SMC_BLS_SYNC(x)                                                \
(   ((x) == EXMC_SMC_BLS_SYNC_CS)               ||                             \
    ((x) == EXMC_SMC_BLS_SYNC_WE))

#define IS_EXMC_SMC_BAA_PORT(x)                                                \
(   ((x) == EXMC_SMC_BAA_PORT_DISABLE)          ||                             \
    ((x) == EXMC_SMC_BAA_PORT_ENABLE))

#define IS_EXMC_SMC_ADV_PORT(x)                                                \
(   ((x) == EXMC_SMC_ADV_PORT_DISABLE)          ||                             \
    ((x) == EXMC_SMC_ADV_PORT_ENABLE))

#define IS_EXMC_SMC_CMD(x)                                                     \
(   ((x) == EXMC_SMC_CMD_MDREGCONFIG)           ||                             \
    ((x) == EXMC_SMC_CMD_UPDATEREGS)            ||                             \
    ((x) == EXMC_SMC_CMD_MDREGCONFIG_AND_UPDATEREGS))

#define IS_EXMC_SMC_CRE_POLARITY(x)                                            \
(   ((x) == EXMC_SMC_CRE_POLARITY_LOW)          ||                             \
    ((x) == EXMC_SMC_CRE_POLARITY_HIGH))

#define IS_EXMC_SMC_SAMPLE_CLK(x)                                              \
(   ((x) == EXMC_SMC_SAMPLE_CLK_INTERNCLK)      ||                             \
    ((x) == EXMC_SMC_SAMPLE_CLK_INTERNCLK_INVT) ||                             \
    ((x) == EXMC_SMC_SAMPLE_CLK_EXTCLK))

#define IS_EXMC_SMC_MAP_ADDR(match, msk)                                       \
(   (EXMC_SMC_MAP_ADDR((match), (msk)) >= EXMC_SMC_ADDR_MIN) &&                \
    (EXMC_SMC_MAP_ADDR((match), (msk)) <= EXMC_SMC_ADDR_MAX))

#define IS_EXMC_SMC_REFRESH_PERIOD(x)           ((x) <= (uint8_t)SMC_RFTR_REFPRD)

#define IS_EXMC_SMC_CMD_ADDR(x)                 ((x) <= 0xFFFFFUL)

#define IS_EXMC_SMC_TIMING_RC_CYCLE(x)          ((x) <= 0x0FUL)

#define IS_EXMC_SMC_TIMING_WC_CYCLE(x)          ((x) <= 0x0FUL)

#define IS_EXMC_SMC_TIMING_CEOE_CYCLE(x)        ((x) <= 7UL)

#define IS_EXMC_SMC_TIMING_WP_CYCLE(x)          ((x) <= 7UL)

#define IS_EXMC_SMC_TIMING_PC_CYCLE(x)          ((x) <= 7UL)

#define IS_EXMC_SMC_TIMING_TR_CYCLE(x)          ((x) <= 7UL)

/**
 * @}
 */

/* EXMC_SMC map address */
#define EXMC_SMC_MAP_ADDR(MATCH, MSK)   ((~((MATCH) ^ (MSK))) << 24U)

/**
 * @defgroup EXMC_SMC_Register EXMC_SMC Register
 * @{
 */
#define EXMC_SMC_CPSRx(__CHIPx__)       ((__IO uint32_t *)(((uint32_t)(&CM_SMC->CPSR0))  + (0x20UL * (__CHIPx__))))
#define EXMC_SMC_TMSRx(__CHIPx__)       ((__IO uint32_t *)(((uint32_t)(&CM_SMC->TMSR0))  + (0x20UL * (__CHIPx__))))
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Register_Bit_Mask EXMC_SMC Register Bit Mask
 * @{
 */
#define SMC_CSCR0_ADDMSKx_POS(__CHIPx__)    (((__CHIPx__) & 0x03UL) << 3U)
#define SMC_CSCR0_ADDMSKx(__CHIPx__)        (SMC_CSCR0_ADDMSK0 << SMC_CSCR0_ADDMSKx_POS((__CHIPx__)))

#define SMC_CSCR1_ADDMATx_POS(__CHIPx__)    (((__CHIPx__) & 0x03UL) << 3U)
#define SMC_CSCR1_ADDMATx(__CHIPx__)        (SMC_CSCR1_ADDMAT0 << SMC_CSCR1_ADDMATx_POS((__CHIPx__)))
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Register_Reset_Value EXMC_SMC Register Reset Value
 * @{
 */
#define EXMC_SMC_BACR_RST_VALUE             (0x00000300UL)
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
 * @defgroup EXMC_SMC_Global_Functions EXMC_SMC Global Functions
 * @{
 */

/**
 * @brief  Set the fields of structure @ref stc_exmc_smc_init_t to default values
 * @param  [out] pstcSmcInit            Pointer to a @ref stc_exmc_smc_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcSmcInit value is NULL.
 */
int32_t EXMC_SMC_StructInit(stc_exmc_smc_init_t *pstcSmcInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcSmcInit) {
        pstcSmcInit->stcChipConfig.u32ReadMode = EXMC_SMC_READ_ASYNC;
        pstcSmcInit->stcChipConfig.u32WriteMode = EXMC_SMC_WRITE_ASYNC;
        pstcSmcInit->stcChipConfig.u32ReadBurstLen = EXMC_SMC_READ_BURST_1BEAT;
        pstcSmcInit->stcChipConfig.u32WriteBurstLen = EXMC_SMC_WRITE_BURST_1BEAT;
        pstcSmcInit->stcChipConfig.u32MemoryWidth = EXMC_SMC_MEMORY_WIDTH_16BIT;
        pstcSmcInit->stcChipConfig.u32BAA = EXMC_SMC_BAA_PORT_DISABLE;
        pstcSmcInit->stcChipConfig.u32ADV = EXMC_SMC_ADV_PORT_DISABLE;
        pstcSmcInit->stcChipConfig.u32BLS = EXMC_SMC_BLS_SYNC_CS;
        pstcSmcInit->stcChipConfig.u32AddrMask = 0xF8UL;        /* Address space 128M: 0x60000000 ~ 0x67FFFFFF */
        pstcSmcInit->stcChipConfig.u32AddrMatch = 0x60UL;

        pstcSmcInit->stcTimingConfig.u8RC = 7U;
        pstcSmcInit->stcTimingConfig.u8WC = 7U;
        pstcSmcInit->stcTimingConfig.u8CEOE = 1U;
        pstcSmcInit->stcTimingConfig.u8WP = 5U;
        pstcSmcInit->stcTimingConfig.u8PC = 0U;
        pstcSmcInit->stcTimingConfig.u8TR = 0U;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize EXMC_SMC function.
 * @param  [in] u32Chip                 The chip number.
 *         This parameter can be one of the macros group @ref EXMC_SMC_Chip
 * @param  [in] pstcSmcInit             Pointer to a @ref stc_exmc_smc_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcSmcInit value is NULL.
 */
int32_t EXMC_SMC_Init(uint32_t u32Chip, const stc_exmc_smc_init_t *pstcSmcInit)
{
    uint32_t u32TMCR;
    uint32_t u32CPCR;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcSmcInit) {
        DDL_ASSERT(IS_EXMC_SMC_CHIP(u32Chip));
        DDL_ASSERT(IS_EXMC_SMC_READ_MD(pstcSmcInit->stcChipConfig.u32ReadMode));
        DDL_ASSERT(IS_EXMC_SMC_WRITE_MD(pstcSmcInit->stcChipConfig.u32WriteMode));
        DDL_ASSERT(IS_EXMC_SMC_READ_BURST(pstcSmcInit->stcChipConfig.u32ReadBurstLen));
        DDL_ASSERT(IS_EXMC_SMC_WRITE_BURST(pstcSmcInit->stcChipConfig.u32WriteBurstLen));
        DDL_ASSERT(IS_EXMC_SMC_MEMORY_WIDTH(pstcSmcInit->stcChipConfig.u32MemoryWidth));
        DDL_ASSERT(IS_EXMC_SMC_BAA_PORT(pstcSmcInit->stcChipConfig.u32BAA));
        DDL_ASSERT(IS_EXMC_SMC_ADV_PORT(pstcSmcInit->stcChipConfig.u32ADV));
        DDL_ASSERT(IS_EXMC_SMC_BLS_SYNC(pstcSmcInit->stcChipConfig.u32BLS));
        DDL_ASSERT(IS_EXMC_SMC_MAP_ADDR(pstcSmcInit->stcChipConfig.u32AddrMatch, pstcSmcInit->stcChipConfig.u32AddrMask));
        DDL_ASSERT(IS_EXMC_SMC_TIMING_RC_CYCLE(pstcSmcInit->stcTimingConfig.u8RC));
        DDL_ASSERT(IS_EXMC_SMC_TIMING_WC_CYCLE(pstcSmcInit->stcTimingConfig.u8WC));
        DDL_ASSERT(IS_EXMC_SMC_TIMING_CEOE_CYCLE(pstcSmcInit->stcTimingConfig.u8CEOE));
        DDL_ASSERT(IS_EXMC_SMC_TIMING_WP_CYCLE(pstcSmcInit->stcTimingConfig.u8WP));
        DDL_ASSERT(IS_EXMC_SMC_TIMING_PC_CYCLE(pstcSmcInit->stcTimingConfig.u8PC));
        DDL_ASSERT(IS_EXMC_SMC_TIMING_TR_CYCLE(pstcSmcInit->stcTimingConfig.u8TR));

        u32TMCR = (((uint32_t)pstcSmcInit->stcTimingConfig.u8RC << SMC_TMCR_T_RC_POS) | \
                   ((uint32_t)pstcSmcInit->stcTimingConfig.u8WC << SMC_TMCR_T_WC_POS) | \
                   ((uint32_t)pstcSmcInit->stcTimingConfig.u8CEOE << SMC_TMCR_T_CEOE_POS) | \
                   ((uint32_t)pstcSmcInit->stcTimingConfig.u8WP << SMC_TMCR_T_WP_POS) | \
                   ((uint32_t)pstcSmcInit->stcTimingConfig.u8PC << SMC_TMCR_T_PC_POS) | \
                   ((uint32_t)pstcSmcInit->stcTimingConfig.u8TR << SMC_TMCR_T_TR_POS));
        u32CPCR = (pstcSmcInit->stcChipConfig.u32ReadMode | \
                   pstcSmcInit->stcChipConfig.u32ReadBurstLen | \
                   pstcSmcInit->stcChipConfig.u32WriteMode | \
                   pstcSmcInit->stcChipConfig.u32WriteBurstLen | \
                   pstcSmcInit->stcChipConfig.u32MemoryWidth | \
                   pstcSmcInit->stcChipConfig.u32BAA | \
                   pstcSmcInit->stcChipConfig.u32ADV | \
                   pstcSmcInit->stcChipConfig.u32BLS);
        WRITE_REG32(CM_SMC->TMCR, u32TMCR); /* Set SMC timing.*/
        WRITE_REG32(CM_SMC->CPCR, u32CPCR); /* Set SMC chip configuration.*/

        /* Set chip selection address match/mask space for SMC.*/
        MODIFY_REG32(CM_SMC->CSCR0, SMC_CSCR0_ADDMSKx(u32Chip), \
                     (pstcSmcInit->stcChipConfig.u32AddrMask << SMC_CSCR0_ADDMSKx_POS(u32Chip)));
        MODIFY_REG32(CM_SMC->CSCR1,  SMC_CSCR1_ADDMATx(u32Chip), \
                     (pstcSmcInit->stcChipConfig.u32AddrMatch << SMC_CSCR1_ADDMATx_POS(u32Chip)));
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  De-Initialize EXMC_SMC function.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:           Reset success.
 */
int32_t EXMC_SMC_DeInit(void)
{
    int32_t i32Ret = LL_OK;

    /* Disable SMC */
    CLR_REG32_BIT(CM_PERIC->SMC_ENAR, PERIC_SMC_ENAR_SMCEN);

    /* Set register CSCR0/CSCR1 to reset value.*/
    WRITE_REG32(CM_SMC->CSCR0, 0xFFFFFFFFUL);
    WRITE_REG32(CM_SMC->CSCR1, 0x00000000UL);

    /* Set register RFTR to reset value.*/
    WRITE_REG32(CM_SMC->RFTR, 0x00000000UL);

    /* Set register BACR to reset value.*/
    WRITE_REG32(CM_SMC->BACR, EXMC_SMC_BACR_RST_VALUE);

    return i32Ret;
}

/**
 * @brief  Enable/Disable SMC.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void EXMC_SMC_Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_PERIC->SMC_ENAR, PERIC_SMC_ENAR_SMCEN);
    } else {
        CLR_REG32_BIT(CM_PERIC->SMC_ENAR, PERIC_SMC_ENAR_SMCEN);
    }
}

/**
 * @brief  Enable or disable SMC pin mux.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void EXMC_SMC_PinMuxCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_SMC->BACR, SMC_BACR_MUXMD);
    } else {
        CLR_REG32_BIT(CM_SMC->BACR, SMC_BACR_MUXMD);
    }
}

/**
 * @brief  Set SMC sample clock.
 * @param  [in] u32SampleClock          Sample clock
 *         This parameter can be one of the macros group @ref EXMC_SMC_Command
 *           @arg EXMC_SMC_SAMPLE_CLK_INTERNCLK:      Internal EXCLK
 *           @arg EXMC_SMC_SAMPLE_CLK_INTERNCLK_INVT: Invert internal EXCLK
 *           @arg EXMC_SMC_SAMPLE_CLK_EXTCLK:         External clock from EXMC_CLK port
 * @retval None
 */
void EXMC_SMC_SetSampleClock(uint32_t u32SampleClock)
{
    DDL_ASSERT(IS_EXMC_SMC_SAMPLE_CLK(u32SampleClock));

    MODIFY_REG32(CM_SMC->BACR, SMC_BACR_CKSEL, u32SampleClock);
}

/**
 * @brief  Set SMC refresh period value
 * @param  [in] u8PeriodVal             The SMC refresh period value
 *           @arg This parameter can be a value between Min_Data = 0 and Max_Data = 0x0F
 * @retval None
 */
void EXMC_SMC_SetRefreshPeriod(uint8_t u8PeriodVal)
{
    DDL_ASSERT(IS_EXMC_SMC_REFRESH_PERIOD(u8PeriodVal));

    WRITE_REG32(CM_SMC->RFTR, u8PeriodVal);
}

/**
 * @brief  Set EXMC_SMC command.
 * @param  [in] u32Chip                 The chip number.
 *         This parameter can be one of the macros group @ref EXMC_SMC_Chip
 * @param  [in] u32Cmd                  The command.
 *         This parameter can be one of the macros group @ref EXMC_SMC_Command
 *           @arg EXMC_SMC_CMD_MDREGCONFIG: Configure mode register
 *           @arg EXMC_SMC_CMD_UPDATEREGS:  Update mode register
 *           @arg EXMC_SMC_CMD_MDREGCONFIG_AND_UPDATEREGS: Configure mode register and update
 * @param  [in] u32CrePolarity          The command.
 *         This parameter can be one of the macros group @ref EXMC_SMC_CRE_Polarity
 *           @arg EXMC_SMC_CRE_POLARITY_LOW:  CRE is LOW
 *           @arg EXMC_SMC_CRE_POLARITY_HIGH: CRE is HIGH when ModeReg write occurs
 * @param  [in] u32Addr                 The address parameter is valid when CMD type is MdRegConfig or MdRegConfig
 *                                      and UpdateRegs only.
 * @retval None
 */
void EXMC_SMC_SetCommand(uint32_t u32Chip, uint32_t u32Cmd, uint32_t u32CrePolarity, uint32_t u32Addr)
{
    uint32_t u32SmcCmdr;

    DDL_ASSERT(IS_EXMC_SMC_CHIP(u32Chip));
    DDL_ASSERT(IS_EXMC_SMC_CMD(u32Cmd));
    DDL_ASSERT(IS_EXMC_SMC_CRE_POLARITY(u32CrePolarity));
    DDL_ASSERT(IS_EXMC_SMC_CMD_ADDR(u32Addr));

    /* Set SMC_CMDR register for SMC.*/
    u32SmcCmdr = (u32Addr | u32CrePolarity | u32Cmd | (u32Chip << SMC_CMDR_CMDCHIP_POS));
    WRITE_REG32(CM_SMC->CMDR, u32SmcCmdr);
}

/**
 * @brief  Get the start address of the specified SMC chip.
 * @param  [in] u32Chip                 The chip number.
 *         This parameter can be one of the macros group @ref EXMC_SMC_Chip
 * @retval The start address of the specified SMC chip.
 */
uint32_t EXMC_SMC_GetChipStartAddr(uint32_t u32Chip)
{
    uint32_t u32Match;

    DDL_ASSERT(IS_EXMC_SMC_CHIP(u32Chip));

    u32Match = READ_REG32_BIT(CM_SMC->CSCR1, SMC_CSCR1_ADDMATx(u32Chip)) >> SMC_CSCR1_ADDMATx_POS(u32Chip);
    return (u32Match << 24U);
}

/**
 * @brief  Get the end address of the specified SMC chip.
 * @param  [in] u32Chip                 The chip number.
 *         This parameter can be one of the macros group @ref EXMC_SMC_Chip
 * @retval The end address of the specified SMC chip
 */
uint32_t EXMC_SMC_GetChipEndAddr(uint32_t u32Chip)
{
    uint32_t u32Mask;
    uint32_t u32Match;

    DDL_ASSERT(IS_EXMC_SMC_CHIP(u32Chip));

    u32Mask = (READ_REG32_BIT(CM_SMC->CSCR0, SMC_CSCR0_ADDMSKx(u32Chip)) >> SMC_CSCR0_ADDMSKx_POS(u32Chip));
    u32Match = (READ_REG32_BIT(CM_SMC->CSCR1, SMC_CSCR1_ADDMATx(u32Chip)) >> SMC_CSCR1_ADDMATx_POS(u32Chip));

    return (~((u32Match ^ u32Mask) << 24U));
}

/**
 * @brief  Get SMC chip configure.
 * @param  [in] u32Chip                 The chip number.
 *         This parameter can be one of the macros group @ref EXMC_SMC_Chip
 * @param  [in] pstcChipConfig          Pointer to a @ref stc_exmc_smc_chip_config_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Get successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcChipConfig value is NULL.
 */
int32_t EXMC_SMC_GetChipConfig(uint32_t u32Chip, stc_exmc_smc_chip_config_t *pstcChipConfig)
{
    __IO uint32_t *SMC_CPSRx;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcChipConfig) {
        DDL_ASSERT(IS_EXMC_SMC_CHIP(u32Chip));

        SMC_CPSRx = EXMC_SMC_CPSRx(u32Chip);
        pstcChipConfig->u32ReadMode = READ_REG32_BIT(*SMC_CPSRx, SMC_CPSR_RSYN);
        pstcChipConfig->u32WriteMode = READ_REG32_BIT(*SMC_CPSRx, SMC_CPSR_WSYN);
        pstcChipConfig->u32ReadBurstLen = READ_REG32_BIT(*SMC_CPSRx, SMC_CPSR_RBL);
        pstcChipConfig->u32WriteBurstLen = READ_REG32_BIT(*SMC_CPSRx, SMC_CPSR_WBL);
        pstcChipConfig->u32MemoryWidth = READ_REG32_BIT(*SMC_CPSRx, SMC_CPSR_MW);
        pstcChipConfig->u32BAA = READ_REG32_BIT(*SMC_CPSRx, SMC_CPSR_BAAS);
        pstcChipConfig->u32ADV = READ_REG32_BIT(*SMC_CPSRx, SMC_CPSR_ADVS);
        pstcChipConfig->u32BLS = READ_REG32_BIT(*SMC_CPSRx, SMC_CPSR_BLSS);
        pstcChipConfig->u32AddrMask = READ_REG32_BIT(*SMC_CPSRx, SMC_CPSR_ADDMSK) >> SMC_CPSR_ADDMSK_POS;
        pstcChipConfig->u32AddrMatch = READ_REG32_BIT(*SMC_CPSRx, SMC_CPSR_ADDMAT) >> SMC_CPSR_ADDMAT_POS;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Get SMC timing configure.
 * @param  [in] u32Chip                 The chip number.
 *         This parameter can be one of the macros group @ref EXMC_SMC_Chip
 * @param  [in] pstcTimingConfig        Pointer to a @ref stc_exmc_smc_timing_config_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Get successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcTimingConfig value is NULL.
 */
int32_t EXMC_SMC_GetTimingConfig(uint32_t u32Chip, stc_exmc_smc_timing_config_t *pstcTimingConfig)
{
    __IO uint32_t *SMC_TMSRx;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcTimingConfig) {
        DDL_ASSERT(IS_EXMC_SMC_CHIP(u32Chip));

        SMC_TMSRx = EXMC_SMC_TMSRx(u32Chip);
        pstcTimingConfig->u8RC = (uint8_t)(READ_REG32_BIT(*SMC_TMSRx, SMC_TMCR_T_RC) >> SMC_TMCR_T_RC_POS);
        pstcTimingConfig->u8WC = (uint8_t)(READ_REG32_BIT(*SMC_TMSRx, SMC_TMCR_T_WC) >> SMC_TMCR_T_WC_POS);
        pstcTimingConfig->u8CEOE = (uint8_t)(READ_REG32_BIT(*SMC_TMSRx, SMC_TMCR_T_CEOE) >> SMC_TMCR_T_CEOE_POS);
        pstcTimingConfig->u8WP = (uint8_t)(READ_REG32_BIT(*SMC_TMSRx, SMC_TMCR_T_WP) >> SMC_TMCR_T_WP_POS);
        pstcTimingConfig->u8PC = (uint8_t)(READ_REG32_BIT(*SMC_TMSRx, SMC_TMCR_T_PC) >> SMC_TMCR_T_PC_POS);
        pstcTimingConfig->u8TR = (uint8_t)(READ_REG32_BIT(*SMC_TMSRx, SMC_TMCR_T_TR) >> SMC_TMCR_T_TR_POS);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
