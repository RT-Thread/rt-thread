/**
 *******************************************************************************
 * @file  hc32f4a0_smc.c
 * @brief This file provides firmware functions to manage the EXMC SMC
 *        (External Memory Controller: Static Memory Controller).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Hongjh          First version
   2020-07-14       Hongjh          Merge API from EXMC_SMC_Enable/Disable to EXMC_SMC_Cmd
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
#include "hc32f4a0_smc.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_EXMC_SMC EXMC_SMC
 * @brief Static Memory Controller Driver Library
 * @{
 */

#if (DDL_SMC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EXMC_SMC_Local_Macros Static Memory Controller Local Macros
 * @{
 */

/**
 * @defgroup EXMC_SMC_Check_Parameters_Validity EXMC SMC Check Parameters Validity
 * @{
 */

#define IS_EXMC_SMC_MEM_WIDTH(x)                                               \
(   (EXMC_SMC_MEMORY_WIDTH_16BIT == (x))              ||                             \
    (EXMC_SMC_MEMORY_WIDTH_32BIT == (x)))

#define IS_EXMC_SMC_MEM_READ_MODE(x)                                           \
(   (EXMC_SMC_MEM_READ_SYNC == (x))             ||                             \
    (EXMC_SMC_MEM_READ_ASYNC == (x)))

#define IS_EXMC_SMC_MEM_WRITE_MODE(x)                                          \
(   (EXMC_SMC_MEM_WRITE_SYNC == (x))            ||                             \
    (EXMC_SMC_MEM_WRITE_ASYNC == (x)))

#define IS_EXMC_SMC_CHIP(x)                                                    \
(   (EXMC_SMC_CHIP_0 == (x))                    ||                             \
    (EXMC_SMC_CHIP_1 == (x))                    ||                             \
    (EXMC_SMC_CHIP_2 == (x))                    ||                             \
    (EXMC_SMC_CHIP_3 == (x)))

#define IS_EXMC_SMC_MEM_READ_BURST(x)                                          \
(   (EXMC_SMC_MEM_READ_BURST_1 == (x))          ||                             \
    (EXMC_SMC_MEM_READ_BURST_4 == (x))          ||                             \
    (EXMC_SMC_MEM_READ_BURST_8 == (x))          ||                             \
    (EXMC_SMC_MEM_READ_BURST_16 == (x))         ||                             \
    (EXMC_SMC_MEM_READ_BURST_32 == (x))         ||                             \
    (EXMC_SMC_MEM_READ_BURST_CONTINUOUS == (x)))

#define IS_EXMC_SMC_MEM_WRITE_BURST(x)                                         \
(   (EXMC_SMC_MEM_WRITE_BURST_1 == (x))         ||                             \
    (EXMC_SMC_MEM_WRITE_BURST_4 == (x))         ||                             \
    (EXMC_SMC_MEM_WRITE_BURST_8 == (x))         ||                             \
    (EXMC_SMC_MEM_WRITE_BURST_16 == (x))        ||                             \
    (EXMC_SMC_MEM_WRITE_BURST_32 == (x))        ||                             \
    (EXMC_SMC_MEM_WRITE_BURST_CONTINUOUS == (x)))

#define IS_EXMC_SMC_BLS_SYNC(x)                                                \
(   (EXMC_SMC_BLS_SYNC_CS == (x))               ||                             \
    (EXMC_SMC_BLS_SYNC_WE == (x)))

#define IS_EXMC_SMC_BAA_PORT(x)                                                \
(   (EXMC_SMC_BAA_PORT_DISABLE == (x))          ||                             \
    (EXMC_SMC_BAA_PORT_ENABLE == (x)))

#define IS_EXMC_SMC_ADV_PORT(x)                                                \
(   (EXMC_SMC_ADV_PORT_DISABLE == (x))          ||                             \
    (EXMC_SMC_ADV_PORT_ENABLE == (x)))

#define IS_EXMC_SMC_CMD(x)                                                     \
(   (EXMC_SMC_CMD_MDREGCONFIG == (x))           ||                             \
    (EXMC_SMC_CMD_UPDATEREGS == (x))            ||                             \
    (EXMC_SMC_CMD_MDREGCONFIG_AND_UPDATEREGS == (x)))

#define IS_EXMC_SMC_CRE_POLARITY(x)                                            \
(   (EXMC_SMC_CRE_POLARITY_LOW == (x))          ||                             \
    (EXMC_SMC_CRE_POLARITY_HIGH == (x)))

#define IS_EXMC_SMC_ADDRESS(match, mask)        ((~(((mask) ^ (match)) << 24UL)) <= 0x7FFFFFFFUL)

#define IS_EXMC_SMC_CS_ADDRESS_MASK(x)          (((x) >= 0xE0UL) && ((x) <= 0XFFUL))

#define IS_EXMC_SMC_CS_ADDRESS_MATCH(x)         (((x) >= 0x60UL) && ((x) <= 0x7FUL))

#define IS_EXMC_SMC_REFRESH_PERIOD(x)           ((x) <= SMC_RFTR_REFPRD)

#define IS_EXMC_SMC_CMDADD(x)                   ((x) <= 0xFFFFFUL)

#define IS_EXMC_SMC_TIMING_RC_CYCLE(x)          ((x) <= 0x0FUL)

#define IS_EXMC_SMC_TIMING_WC_CYCLE(x)          ((x) <= 0x0FUL)

#define IS_EXMC_SMC_TIMING_CEOE_CYCLE(x)        ((x) <= 7UL)

#define IS_EXMC_SMC_TIMING_WP_CYCLE(x)          ((x) <= 7UL)

#define IS_EXMC_SMC_TIMING_PC_CYCLE(x)          ((x) <= 7UL)

#define IS_EXMC_SMC_TIMING_TR_CYCLE(x)          ((x) <= 7UL)

/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Register EXMC sMC Register
 * @{
 */
#define EXMC_SMC_CPSRx(__CHIPx__)       ((__IO uint32_t *)(((uint32_t)(&M4_SMC->CPSR0))  + (0x20UL * (__CHIPx__))))
#define EXMC_SMC_TMSRx(__CHIPx__)       ((__IO uint32_t *)(((uint32_t)(&M4_SMC->TMSR0))  + (0x20UL * (__CHIPx__))))
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_Register_Bit_Mask EXMC SMC Register Bit Mask
 * @{
 */
#define SMC_CSCR0_ADDMSKx_POS(__CHIPx__)    ((__CHIPx__) << 3UL)
#define SMC_CSCR0_ADDMSKx(__CHIPx__)        (SMC_CSCR0_ADDMSK0 << SMC_CSCR0_ADDMSKx_POS((__CHIPx__)))

#define SMC_CSCR1_ADDMATx_POS(__CHIPx__)    ((__CHIPx__) << 3UL)
#define SMC_CSCR1_ADDMATx(__CHIPx__)        (SMC_CSCR1_ADDMAT0 << SMC_CSCR1_ADDMATx_POS((__CHIPx__)))
/**
 * @}
 */

/**
 * @defgroup EXMC_SMC_MUX_Selection EXMC SMC MUX Selection
 * @{
 */
#define EXMC_SMC_MUX_DISABLE                (0x00000300UL)
#define EXMC_SMC_MUX_ENABLE                 (0x00000300UL | SMC_BACR_MUXMD)
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
 * @defgroup EXMC_SMC_Global_Functions Static Memory Controller Global Functions
 * @{
 */

/**
 * @brief  Initialize EXMC SMC function.
 * @param  [in] u32Chip                     The chip number.
 *         This parameter can be one of the following values:
 *           @arg EXMC_SMC_CHIP_0:          Chip 0
 *           @arg EXMC_SMC_CHIP_1:          Chip 1
 *           @arg EXMC_SMC_CHIP_2:          Chip 2
 *           @arg EXMC_SMC_CHIP_3:          Chip 3
 * @param  [in] pstcInit                Pointer to a @ref stc_exmc_smc_init_t structure (EXMC SMC function configuration structure).
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t EXMC_SMC_Init(uint32_t u32Chip, const stc_exmc_smc_init_t *pstcInit)
{
    uint32_t u32RegVal;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check the pointer pstcInit */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_EXMC_SMC_CHIP(u32Chip));

        DDL_ASSERT(IS_EXMC_SMC_MEM_READ_MODE(pstcInit->stcChipCfg.u32ReadMode));
        DDL_ASSERT(IS_EXMC_SMC_MEM_WRITE_MODE(pstcInit->stcChipCfg.u32WriteMode));
        DDL_ASSERT(IS_EXMC_SMC_MEM_READ_BURST(pstcInit->stcChipCfg.u32ReadBurstLen));
        DDL_ASSERT(IS_EXMC_SMC_MEM_WRITE_BURST(pstcInit->stcChipCfg.u32WriteBurstLen));
        DDL_ASSERT(IS_EXMC_SMC_MEM_WIDTH(pstcInit->stcChipCfg.u32SmcMemWidth));
        DDL_ASSERT(IS_EXMC_SMC_BAA_PORT(pstcInit->stcChipCfg.u32BAA));
        DDL_ASSERT(IS_EXMC_SMC_ADV_PORT(pstcInit->stcChipCfg.u32ADV));
        DDL_ASSERT(IS_EXMC_SMC_BLS_SYNC(pstcInit->stcChipCfg.u32BLS));
        DDL_ASSERT(IS_EXMC_SMC_CS_ADDRESS_MATCH(pstcInit->stcChipCfg.u32AddressMatch));
        DDL_ASSERT(IS_EXMC_SMC_CS_ADDRESS_MASK(pstcInit->stcChipCfg.u32AddressMask));
        DDL_ASSERT(IS_EXMC_SMC_ADDRESS(pstcInit->stcChipCfg.u32AddressMatch, pstcInit->stcChipCfg.u32AddressMask));

        DDL_ASSERT(IS_EXMC_SMC_TIMING_RC_CYCLE(pstcInit->stcTimingCfg.u32RC));
        DDL_ASSERT(IS_EXMC_SMC_TIMING_WC_CYCLE(pstcInit->stcTimingCfg.u32WC));
        DDL_ASSERT(IS_EXMC_SMC_TIMING_CEOE_CYCLE(pstcInit->stcTimingCfg.u32CEOE));
        DDL_ASSERT(IS_EXMC_SMC_TIMING_WP_CYCLE(pstcInit->stcTimingCfg.u32WP));
        DDL_ASSERT(IS_EXMC_SMC_TIMING_RC_CYCLE(pstcInit->stcTimingCfg.u32RC));
        DDL_ASSERT(IS_EXMC_SMC_TIMING_TR_CYCLE(pstcInit->stcTimingCfg.u32TR));

        /* Set SMC timing.*/
        u32RegVal = ((pstcInit->stcTimingCfg.u32RC << SMC_TMCR_T_RC_POS) | \
                     (pstcInit->stcTimingCfg.u32WC << SMC_TMCR_T_WC_POS) | \
                     (pstcInit->stcTimingCfg.u32CEOE << SMC_TMCR_T_CEOE_POS) | \
                     (pstcInit->stcTimingCfg.u32WP << SMC_TMCR_T_WP_POS) | \
                     (pstcInit->stcTimingCfg.u32PC << SMC_TMCR_T_PC_POS) | \
                     (pstcInit->stcTimingCfg.u32TR << SMC_TMCR_T_TR_POS) | \
                     0xFF000000UL);
        WRITE_REG32(M4_SMC->TMCR, u32RegVal);

        /* Set SMC chip configuration.*/
        u32RegVal = (pstcInit->stcChipCfg.u32ReadMode | \
                     pstcInit->stcChipCfg.u32ReadBurstLen | \
                     pstcInit->stcChipCfg.u32WriteMode | \
                     pstcInit->stcChipCfg.u32WriteBurstLen | \
                     pstcInit->stcChipCfg.u32SmcMemWidth | \
                     pstcInit->stcChipCfg.u32BAA | \
                     pstcInit->stcChipCfg.u32ADV | \
                     pstcInit->stcChipCfg.u32BLS | \
                     0xFFFF0000UL);
        WRITE_REG32(M4_SMC->CPCR, u32RegVal);

        /* Set chip selection address match/mask spacefor SMC.*/
        MODIFY_REG32(M4_SMC->CSCR0, \
                     SMC_CSCR0_ADDMSKx(u32Chip), \
                     (pstcInit->stcChipCfg.u32AddressMask << SMC_CSCR0_ADDMSKx_POS(u32Chip)));
        MODIFY_REG32(M4_SMC->CSCR1, \
                     SMC_CSCR0_ADDMSKx(u32Chip), \
                     (pstcInit->stcChipCfg.u32AddressMatch << SMC_CSCR1_ADDMATx_POS(u32Chip)));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize EXMC SMC function.
 * @param  None
 * @retval None
 */
void EXMC_SMC_DeInit(void)
{
    /* Disable SMC */
    WRITE_REG32(bM4_PERIC->EXMC_ENAR_b.SMCEN, 0UL);

    /* Set SMC timing.*/
    WRITE_REG32(M4_SMC->TMCR, 0UL);

    /* Set SMC chip configuration.*/
    WRITE_REG32(M4_SMC->CPCR, 0UL);
}

/**
 * @brief  Set the fields of structure @ref stc_exmc_smc_init_t to default values
 * @param  [out] pstcInit               Pointer to a @ref stc_exmc_smc_init_t structure (EXMC SMC function configuration structure)
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t EXMC_SMC_StructInit(stc_exmc_smc_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcInit)
    {
        pstcInit->stcChipCfg.u32ReadMode = EXMC_SMC_MEM_READ_ASYNC;
        pstcInit->stcChipCfg.u32ReadBurstLen = EXMC_SMC_MEM_READ_BURST_1;
        pstcInit->stcChipCfg.u32WriteMode = EXMC_SMC_MEM_WRITE_ASYNC;
        pstcInit->stcChipCfg.u32WriteBurstLen = EXMC_SMC_MEM_WRITE_BURST_1;
        pstcInit->stcChipCfg.u32SmcMemWidth = EXMC_SMC_MEMORY_WIDTH_16BIT;
        pstcInit->stcChipCfg.u32BAA = EXMC_SMC_BAA_PORT_DISABLE;
        pstcInit->stcChipCfg.u32ADV = EXMC_SMC_ADV_PORT_DISABLE;
        pstcInit->stcChipCfg.u32BLS = EXMC_SMC_BLS_SYNC_CS;
        pstcInit->stcChipCfg.u32AddressMask = 0xF8UL;        /* Address space 128M: 0x60000000 ~ 0X67FFFFFF */
        pstcInit->stcChipCfg.u32AddressMatch = 0X60UL;

        pstcInit->stcTimingCfg.u32RC = 7UL;
        pstcInit->stcTimingCfg.u32WC = 7UL;
        pstcInit->stcTimingCfg.u32CEOE = 1UL;
        pstcInit->stcTimingCfg.u32WP = 5UL;
        pstcInit->stcTimingCfg.u32PC = 0UL;
        pstcInit->stcTimingCfg.u32TR = 0UL;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable/Disable SMC.
 * @param  [in]  enNewState                 An en_functional_state_t enumeration value.
 *         This parameter can be one of the following values:
 *           @arg Enable:                   Enable function.
 *           @arg Disable:                  Disable function.
 * @retval None
 */
void EXMC_SMC_Cmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bM4_PERIC->EXMC_ENAR_b.SMCEN, enNewState);
}

/**
 * @brief  Set EXMC SMC command.
 * @param  [in] u32Chip                     The chip number.
 *         This parameter can be one of the following values:
 *           @arg EXMC_SMC_CHIP_0:          Chip 0
 *           @arg EXMC_SMC_CHIP_1:          Chip 1
 *           @arg EXMC_SMC_CHIP_2:          Chip 2
 *           @arg EXMC_SMC_CHIP_3:          Chip 3
 * @param  [in] u32Cmd                      The command.
 *         This parameter can be one of the following values:
 *           @arg EXMC_SMC_CMD_MDREGCONFIG: Configure mode register
 *           @arg EXMC_SMC_CMD_UPDATEREGS:  Update mode register
 *           @arg EXMC_SMC_CMD_MDREGCONFIG_AND_UPDATEREGS: Configure mode register and update
 * @param  [in] u32CrePolarity              The command.
 *         This parameter can be one of the following values:
 *           @arg EXMC_SMC_CRE_POLARITY_LOW:  CRE is LOW
 *           @arg EXMC_SMC_CRE_POLARITY_HIGH: CRE is HIGH when ModeReg write occurs
 * @param  [in] u32Address                  The address parameter is valid when CMD type is
 *                                          MdRegConfig or MdRegConfig and UpdateRegs only.
 * @retval None
 */
void EXMC_SMC_SetCommand(uint32_t u32Chip,
                                uint32_t u32Cmd,
                                uint32_t u32CrePolarity,
                                uint32_t u32Address)
{
    uint32_t u32SmcCmdr;

    /* Check parameters */
    DDL_ASSERT(IS_EXMC_SMC_CHIP(u32Chip));
    DDL_ASSERT(IS_EXMC_SMC_CMD(u32Cmd));
    DDL_ASSERT(IS_EXMC_SMC_CRE_POLARITY(u32CrePolarity));
    DDL_ASSERT(IS_EXMC_SMC_CMDADD(u32Address));

    /* Set SMC_CMDR register for SMC.*/
    u32SmcCmdr = (u32Address | u32CrePolarity | u32Cmd | (u32Chip << SMC_CMDR_CMDCHIP_POS));
    WRITE_REG32(M4_SMC->CMDR, u32SmcCmdr);
}

/**
 * @brief  Get the start address of the specified SMC chip.
 * @param  [in] u32Chip                     The chip number.
 *         This parameter can be one of the following values:
 *           @arg EXMC_SMC_CHIP_0:          Chip 0
 *           @arg EXMC_SMC_CHIP_1:          Chip 1
 *           @arg EXMC_SMC_CHIP_2:          Chip 2
 *           @arg EXMC_SMC_CHIP_3:          Chip 3
 * @retval The start address of the specified SMC chip.
 */
uint32_t EXMC_SMC_ChipStartAddress(uint32_t u32Chip)
{
    uint32_t u32StartAddress;

    /* Check parameters */
    DDL_ASSERT(IS_EXMC_SMC_CHIP(u32Chip));

    u32StartAddress = (READ_REG32_BIT(M4_SMC->CSCR1, SMC_CSCR1_ADDMATx(u32Chip)) << (24UL - SMC_CSCR1_ADDMATx_POS(u32Chip)));
    return u32StartAddress;
}

/**
 * @brief  Get the end address of the specified SMC chip.
 * @param  [in] u32Chip                     The chip number.
 *         This parameter can be one of the following values:
 *           @arg EXMC_SMC_CHIP_0:          Chip 0
 *           @arg EXMC_SMC_CHIP_1:          Chip 1
 *           @arg EXMC_SMC_CHIP_2:          Chip 2
 *           @arg EXMC_SMC_CHIP_3:          Chip 3
 * @retval The end address of the specified SMC chip
 */
uint32_t EXMC_SMC_ChipEndAddress(uint32_t u32Chip)
{
    uint32_t u32Mask;
    uint32_t u32Match;

    /* Check parameters */
    DDL_ASSERT(IS_EXMC_SMC_CHIP(u32Chip));

    u32Mask =  (READ_REG32_BIT(M4_SMC->CSCR0, SMC_CSCR0_ADDMSKx(u32Chip)) >> SMC_CSCR0_ADDMSKx_POS(u32Chip));
    u32Match = (READ_REG32_BIT(M4_SMC->CSCR1, SMC_CSCR1_ADDMATx(u32Chip)) >> SMC_CSCR1_ADDMATx_POS(u32Chip));

    return (~((u32Match ^ u32Mask) << 24UL));
}

/**
 * @brief  Check SMC chip status register value
 * @param  [in] u32Chip                     The chip number.
 *         This parameter can be one of the following values:
 *           @arg EXMC_SMC_CHIP_0:          Chip 0
 *           @arg EXMC_SMC_CHIP_1:          Chip 1
 *           @arg EXMC_SMC_CHIP_2:          Chip 2
 *           @arg EXMC_SMC_CHIP_3:          Chip 3
 * @param  [in] pstcChipCfg                 Pointer to a @ref stc_exmc_smc_chip_cfg_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Status is right
 *           - Error: Status is error
 */
en_result_t EXMC_SMC_CheckChipStatus(uint32_t u32Chip,
                                    const stc_exmc_smc_chip_cfg_t *pstcChipCfg)
{
    uint32_t u32ChipCfg;
    __IO uint32_t *SMC_CPSRx;

    /* Check parameters */
    DDL_ASSERT(IS_EXMC_SMC_CHIP(u32Chip));
    DDL_ASSERT(IS_EXMC_SMC_MEM_READ_MODE(pstcChipCfg->u32ReadMode));
    DDL_ASSERT(IS_EXMC_SMC_MEM_WRITE_MODE(pstcChipCfg->u32WriteMode));
    DDL_ASSERT(IS_EXMC_SMC_MEM_READ_BURST(pstcChipCfg->u32ReadBurstLen));
    DDL_ASSERT(IS_EXMC_SMC_MEM_WRITE_BURST(pstcChipCfg->u32WriteBurstLen));
    DDL_ASSERT(IS_EXMC_SMC_MEM_WIDTH(pstcChipCfg->u32SmcMemWidth));
    DDL_ASSERT(IS_EXMC_SMC_BAA_PORT(pstcChipCfg->u32BAA));
    DDL_ASSERT(IS_EXMC_SMC_ADV_PORT(pstcChipCfg->u32ADV));
    DDL_ASSERT(IS_EXMC_SMC_BLS_SYNC(pstcChipCfg->u32BLS));
    DDL_ASSERT(IS_EXMC_SMC_CS_ADDRESS_MATCH(pstcChipCfg->u32AddressMatch));
    DDL_ASSERT(IS_EXMC_SMC_CS_ADDRESS_MASK(pstcChipCfg->u32AddressMask));

    u32ChipCfg = (pstcChipCfg->u32ReadMode | \
                  pstcChipCfg->u32WriteMode | \
                  pstcChipCfg->u32ReadBurstLen | \
                  pstcChipCfg->u32WriteBurstLen | \
                  pstcChipCfg->u32SmcMemWidth | \
                  pstcChipCfg->u32BAA | \
                  pstcChipCfg->u32ADV | \
                  pstcChipCfg->u32BLS | \
                  (pstcChipCfg->u32AddressMask << SMC_CPSR_ADDMSK_POS) | \
                  (pstcChipCfg->u32AddressMatch << SMC_CPSR_ADDMAT_POS));
    SMC_CPSRx = EXMC_SMC_CPSRx(u32Chip);
    return (u32ChipCfg == READ_REG32(*SMC_CPSRx)) ? Ok : Error;
}

/**
 * @brief  Check SMC timing status register value
 * @param  [in] u32Chip                     The chip number.
 *         This parameter can be one of the following values:
 *           @arg EXMC_SMC_CHIP_0:          Chip 0
 *           @arg EXMC_SMC_CHIP_1:          Chip 1
 *           @arg EXMC_SMC_CHIP_2:          Chip 2
 *           @arg EXMC_SMC_CHIP_3:          Chip 3
 * @param  [in] pstcTimingCfg               Pointer to a @ref stc_exmc_smc_timing_cfg_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Status is right
 *           - Error: Status is error
 */
en_result_t EXMC_SMC_CheckTimingStatus(uint32_t u32Chip,
                                const stc_exmc_smc_timing_cfg_t *pstcTimingCfg)
{
    uint32_t u32TimingCfg;
    __IO uint32_t *SMC_TMSRx;

    /* Check parameters */
    DDL_ASSERT(IS_EXMC_SMC_CHIP(u32Chip));
    DDL_ASSERT(IS_EXMC_SMC_TIMING_RC_CYCLE(pstcTimingCfg->u32RC));
    DDL_ASSERT(IS_EXMC_SMC_TIMING_WC_CYCLE(pstcTimingCfg->u32WC));
    DDL_ASSERT(IS_EXMC_SMC_TIMING_CEOE_CYCLE(pstcTimingCfg->u32CEOE));
    DDL_ASSERT(IS_EXMC_SMC_TIMING_WP_CYCLE(pstcTimingCfg->u32WP));
    DDL_ASSERT(IS_EXMC_SMC_TIMING_RC_CYCLE(pstcTimingCfg->u32RC));
    DDL_ASSERT(IS_EXMC_SMC_TIMING_TR_CYCLE(pstcTimingCfg->u32TR));

    u32TimingCfg = ((pstcTimingCfg->u32RC << SMC_TMCR_T_RC_POS) | \
                    (pstcTimingCfg->u32WC << SMC_TMCR_T_WC_POS) | \
                    (pstcTimingCfg->u32CEOE << SMC_TMCR_T_CEOE_POS) | \
                    (pstcTimingCfg->u32WP << SMC_TMCR_T_WP_POS) | \
                    (pstcTimingCfg->u32PC << SMC_TMCR_T_PC_POS) | \
                    (pstcTimingCfg->u32TR << SMC_TMCR_T_TR_POS));
    SMC_TMSRx = EXMC_SMC_TMSRx(u32Chip);
    return (u32TimingCfg == READ_REG32(*SMC_TMSRx)) ? Ok : Error;
}

/**
 * @brief  Enable SMC MUX.
 * @param  [in] enNewState          The function new state
 *           @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void EXMC_SMC_PinMuxCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(M4_SMC->BACR, (Enable == enNewState) ? EXMC_SMC_MUX_ENABLE: EXMC_SMC_MUX_DISABLE);
}

/**
 * @brief  Set SMC refresh period value
 * @param  [in] u32PeriodVal            The SMC refresh period value
 *           @arg number of 16bit
 * @retval None
 */
void EXMC_SMC_SetRefreshPeriod(uint32_t u32PeriodVal)
{
    /* Check parameters */
    DDL_ASSERT(IS_EXMC_SMC_REFRESH_PERIOD(u32PeriodVal));

    WRITE_REG16(M4_SMC->RFTR, u32PeriodVal);
}

/**
 * @}
 */

#endif /* DDL_SMC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
