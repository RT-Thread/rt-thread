/**
 *******************************************************************************
 * @file  hc32_ll_qspi.c
 * @brief This file provides firmware functions to manage the QSPI.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Optimize QSPI_DeInit function
   2023-09-30       CDT             Optimize QSPI_ClearStatus function
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
#include "hc32_ll_qspi.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_QSPI QSPI
 * @brief QSPI Driver Library
 * @{
 */

#if (LL_QSPI_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup QSPI_Local_Macros QSPI Local Macros
 * @{
 */

/* QSPI registers Mask */
#define QSPI_CR_CLR_MASK                (QSPI_CR_DIV    | QSPI_CR_SPIMD3    | QSPI_CR_PFSAE  | \
                                         QSPI_CR_PFE    | QSPI_CR_MDSEL)
#define QSPI_FCR_CLR_MASK               (QSPI_FCR_DUTY  | QSPI_FCR_DMCYCN   | QSPI_FCR_SSNLD | \
                                         QSPI_FCR_SSNHD | QSPI_FCR_FOUR_BIC | QSPI_FCR_AWSL)
#define QSPI_CUSTOM_MD_CLR_MASK         (QSPI_CR_IPRSL  | QSPI_CR_APRSL     | QSPI_CR_DPRSL)

/**
 * @defgroup QSPI_Check_Parameters_Validity QSPI check parameters validity
 * @{
 */

#define IS_QSPI_CLK_DIV(x)                                                     \
(   ((x) != 0U)                                             &&                 \
    (((x) | QSPI_CLK_DIV64) == QSPI_CLK_DIV64))

#define IS_QSPI_SPI_MD(x)                                                      \
(   ((x) == QSPI_SPI_MD0)                                   ||                 \
    ((x) == QSPI_SPI_MD3))

#define IS_QSPI_PREFETCH_MD(x)                                                 \
(   ((x) == QSPI_PREFETCH_MD_INVD)                          ||                 \
    ((x) == QSPI_PREFETCH_MD_EDGE_STOP)                     ||                 \
    ((x) == QSPI_PREFETCH_MD_IMMED_STOP))

#define IS_QSPI_READ_MD(x)                                                     \
(   ((x) == QSPI_RD_MD_STD_RD)                              ||                 \
    ((x) == QSPI_RD_MD_FAST_RD)                             ||                 \
    ((x) == QSPI_RD_MD_DUAL_OUTPUT_FAST_RD)                 ||                 \
    ((x) == QSPI_RD_MD_DUAL_IO_FAST_RD)                     ||                 \
    ((x) == QSPI_RD_MD_QUAD_OUTPUT_FAST_RD)                 ||                 \
    ((x) == QSPI_RD_MD_QUAD_IO_FAST_RD)                     ||                 \
    ((x) == QSPI_RD_MD_CUSTOM_STANDARD_RD)                  ||                 \
    ((x) == QSPI_RD_MD_CUSTOM_FAST_RD))

#define IS_QSPI_DUMMY_CYCLE(x)                              (((x) | QSPI_DUMMY_CYCLE18) == QSPI_DUMMY_CYCLE18)

#define IS_QSPI_ADDR_WIDTH(x)                                                  \
(   ((x) == QSPI_ADDR_WIDTH_8BIT)                           ||                 \
    ((x) == QSPI_ADDR_WIDTH_16BIT)                          ||                 \
    ((x) == QSPI_ADDR_WIDTH_24BIT)                          ||                 \
    ((x) == QSPI_ADDR_WIDTH_32BIT_INSTR_24BIT)              ||                 \
    ((x) == QSPI_ADDR_WIDTH_32BIT_INSTR_32BIT))

#define IS_QSPI_QSSN_SETUP_TIME(x)                                             \
(   ((x) == QSPI_QSSN_SETUP_ADVANCE_QSCK0P5)                ||                 \
    ((x) == QSPI_QSSN_SETUP_ADVANCE_QSCK1P5))

#define IS_QSPI_QSSN_RELEASE_TIME(x)                                           \
(   ((x) == QSPI_QSSN_RELEASE_DELAY_QSCK0P5)                ||                 \
    ((x) == QSPI_QSSN_RELEASE_DELAY_QSCK1P5)                ||                 \
    ((x) == QSPI_QSSN_RELEASE_DELAY_QSCK32)                 ||                 \
    ((x) == QSPI_QSSN_RELEASE_DELAY_QSCK128)                ||                 \
    ((x) == QSPI_QSSN_RELEASE_DELAY_INFINITE))

#define IS_QSPI_QSSN_INTERVAL_TIME(x)                       ((x) <= QSPI_QSSN_INTERVAL_QSCK16)

#define IS_QSPI_INSTR_PROTOCOL(x)                                              \
(   ((x) == QSPI_INSTR_PROTOCOL_1LINE)                      ||                 \
    ((x) == QSPI_INSTR_PROTOCOL_2LINE)                      ||                 \
    ((x) == QSPI_INSTR_PROTOCOL_4LINE))

#define IS_QSPI_ADDR_PROTOCOL(x)                                               \
(   ((x) == QSPI_ADDR_PROTOCOL_1LINE)                       ||                 \
    ((x) == QSPI_ADDR_PROTOCOL_2LINE)                       ||                 \
    ((x) == QSPI_ADDR_PROTOCOL_4LINE))

#define IS_QSPI_DATA_PROTOCOL(x)                                               \
(   ((x) == QSPI_DATA_PROTOCOL_1LINE)                       ||                 \
    ((x) == QSPI_DATA_PROTOCOL_2LINE)                       ||                 \
    ((x) == QSPI_DATA_PROTOCOL_4LINE))

#define IS_QSPI_WP_PIN_LVL(x)                                                  \
(   ((x) == QSPI_WP_PIN_LOW)                                ||                 \
    ((x) == QSPI_WP_PIN_HIGH))

#define IS_QSPI_FLAG(x)                                                        \
(   ((x) != 0U)                                             &&                 \
    (((x) | QSPI_FLAG_ALL) == QSPI_FLAG_ALL))

#define IS_QSPI_CLR_FLAG(x)                                                    \
(   ((x) != 0U)                                             &&                 \
    (((x) | QSPI_FLAG_CLR_ALL) == QSPI_FLAG_CLR_ALL))

#define IS_QSPI_BLOCK_SIZE(x)                               ((x) <= (QSPI_EXAR_EXADR >> QSPI_EXAR_EXADR_POS))

#define IS_QSPI_PWC_UNLOCKED()          ((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1)

/* QSPI reset timeout */
#define QSPI_RMU_TIMEOUT                (100UL)

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
/**
 * @defgroup QSPI_Local_Variable QSPI Local Variable
 * @{
 */

/* Current read mode */
static uint32_t m_u32ReadMode = 0U;

/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup QSPI_Global_Functions QSPI Global Functions
 * @{
 */

/**
 * @brief  De-initializes QSPI.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          Works timeout.
 */
int32_t QSPI_DeInit(void)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32TimeOut = 0U;

    /* Check parameters */
    DDL_ASSERT(IS_QSPI_PWC_UNLOCKED());

    CLR_REG32_BIT(CM_RMU->FRST1, RMU_FRST1_QSPI);
    /* Ensure reset procedure is completed */
    while (RMU_FRST1_QSPI != READ_REG32_BIT(CM_RMU->FRST1, RMU_FRST1_QSPI)) {
        u32TimeOut++;
        if (u32TimeOut > QSPI_RMU_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    return i32Ret;
}

/**
 * @brief  Initialize QSPI.
 * @param  [in] pstcQspiInit            Pointer to a @ref stc_qspi_init_t structure
 * @retval int32_t:
 *           - LL_OK: Initialize success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t QSPI_Init(const stc_qspi_init_t *pstcQspiInit)
{
    int32_t i32Ret  = LL_OK;
    uint32_t u32Duty = 0UL;

    if (NULL == pstcQspiInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_QSPI_CLK_DIV(pstcQspiInit->u32ClockDiv));
        DDL_ASSERT(IS_QSPI_SPI_MD(pstcQspiInit->u32SpiMode));
        DDL_ASSERT(IS_QSPI_PREFETCH_MD(pstcQspiInit->u32PrefetchMode));
        DDL_ASSERT(IS_QSPI_READ_MD(pstcQspiInit->u32ReadMode));
        DDL_ASSERT(IS_QSPI_DUMMY_CYCLE(pstcQspiInit->u32DummyCycle));
        DDL_ASSERT(IS_QSPI_ADDR_WIDTH(pstcQspiInit->u32AddrWidth));
        DDL_ASSERT(IS_QSPI_QSSN_SETUP_TIME(pstcQspiInit->u32SetupTime));
        DDL_ASSERT(IS_QSPI_QSSN_RELEASE_TIME(pstcQspiInit->u32ReleaseTime));
        DDL_ASSERT(IS_QSPI_QSSN_INTERVAL_TIME(pstcQspiInit->u32IntervalTime));

        /* Duty cycle compensation */
        if (0UL == (pstcQspiInit->u32ClockDiv & QSPI_CLK_DIV2)) {
            u32Duty = QSPI_FCR_DUTY;
        }
        MODIFY_REG32(CM_QSPI->CR, QSPI_CR_CLR_MASK, (pstcQspiInit->u32ClockDiv | pstcQspiInit->u32SpiMode |
                                                     pstcQspiInit->u32PrefetchMode | pstcQspiInit->u32ReadMode));
        WRITE_REG32(CM_QSPI->CSCR, ((pstcQspiInit->u32ReleaseTime >> 8U) | pstcQspiInit->u32IntervalTime));
        MODIFY_REG32(CM_QSPI->FCR, QSPI_FCR_CLR_MASK, (pstcQspiInit->u32DummyCycle | pstcQspiInit->u32AddrWidth |
                                                       pstcQspiInit->u32SetupTime | (pstcQspiInit->u32ReleaseTime & 0xFFU) | u32Duty));
    }

    return i32Ret;
}

/**
 * @brief  Fills each stc_qspi_init_t member with default value.
 * @param  [out] pstcQspiInit           Pointer to a @ref stc_qspi_init_t structure
 * @retval int32_t:
 *           - LL_OK: stc_qspi_init_t member initialize success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t QSPI_StructInit(stc_qspi_init_t *pstcQspiInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcQspiInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcQspiInit->u32ClockDiv       = QSPI_CLK_DIV2;
        pstcQspiInit->u32SpiMode        = QSPI_SPI_MD0;
        pstcQspiInit->u32PrefetchMode   = QSPI_PREFETCH_MD_INVD;
        pstcQspiInit->u32ReadMode       = QSPI_RD_MD_STD_RD;
        pstcQspiInit->u32DummyCycle     = QSPI_DUMMY_CYCLE3;
        pstcQspiInit->u32AddrWidth      = QSPI_ADDR_WIDTH_24BIT;
        pstcQspiInit->u32SetupTime      = QSPI_QSSN_SETUP_ADVANCE_QSCK0P5;
        pstcQspiInit->u32ReleaseTime    = QSPI_QSSN_RELEASE_DELAY_QSCK0P5;
        pstcQspiInit->u32IntervalTime   = QSPI_QSSN_INTERVAL_QSCK1;
    }

    return i32Ret;
}

/**
 * @brief  Set the level of WP pin.
 * @param  [in] u32Level                The level value.
 *         This parameter can be one of the following values:
 *           @arg QSPI_WP_PIN_LOW:      WP(QSIO2) pin output low
 *           @arg QSPI_WP_PIN_HIGH:     WP(QSIO2) pin output high
 * @retval None
 */
void QSPI_SetWpPinLevel(uint32_t u32Level)
{
    /* Check parameters */
    DDL_ASSERT(IS_QSPI_WP_PIN_LVL(u32Level));

    MODIFY_REG32(CM_QSPI->FCR, QSPI_FCR_WPOL, u32Level);
}

/**
 * @brief  Set the prefetch mode.
 * @param  [in] u32Mode                 The prefetch mode.
 *         This parameter can be one of the following values:
 *           @arg QSPI_PREFETCH_MD_INVD:        Disable prefetch
 *           @arg QSPI_PREFETCH_MD_EDGE_STOP:   Stop prefetch at the edge of byte
 *           @arg QSPI_PREFETCH_MD_IMMED_STOP:  Stop prefetch at current position immediately
 * @retval None
 */
void QSPI_SetPrefetchMode(uint32_t u32Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_QSPI_PREFETCH_MD(u32Mode));

    MODIFY_REG32(CM_QSPI->CR, (QSPI_CR_PFE | QSPI_CR_PFSAE), u32Mode);
}

/**
 * @brief  Selects the block to access.
 * @param  [in] u8Block                 Memory block number (range is 0 to 63)
 * @retval None
 */
void QSPI_SelectMemoryBlock(uint8_t u8Block)
{
    /* Check parameters */
    DDL_ASSERT(IS_QSPI_BLOCK_SIZE(u8Block));

    WRITE_REG32(CM_QSPI->EXAR, ((uint32_t)u8Block << QSPI_EXAR_EXADR_POS));
}

/**
 * @brief  Set the read mode.
 * @param  [in] u32Mode                 Read mode.
 *         This parameter can be one of the following values:
 *           @arg QSPI_RD_MD_STD_RD:                Standard read mode (no dummy cycles)
 *           @arg QSPI_RD_MD_FAST_RD:               Fast read mode (dummy cycles between address and data)
 *           @arg QSPI_RD_MD_DUAL_OUTPUT_FAST_RD:   Fast read dual output mode (data on 2 lines)
 *           @arg QSPI_RD_MD_DUAL_IO_FAST_RD:       Fast read dual I/O mode (address and data on 2 lines)
 *           @arg QSPI_RD_MD_QUAD_OUTPUT_FAST_RD:   Fast read quad output mode (data on 4 lines)
 *           @arg QSPI_RD_MD_QUAD_IO_FAST_RD:       Fast read quad I/O mode (address and data on 4 lines)
 *           @arg QSPI_RD_MD_CUSTOM_STANDARD_RD:    Custom standard read mode
 *           @arg QSPI_RD_MD_CUSTOM_FAST_RD:        Custom fast read mode
 * @retval None
 */
void QSPI_SetReadMode(uint32_t u32Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_QSPI_READ_MD(u32Mode));

    MODIFY_REG32(CM_QSPI->CR, QSPI_CR_MDSEL, u32Mode);
}

/**
 * @brief  Configure the custom read.
 * @param  [in] pstcCustomMode          Pointer to a @ref stc_qspi_custom_mode_t structure
 * @retval int32_t:
 *           - LL_OK: Initialize success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t QSPI_CustomReadConfig(const stc_qspi_custom_mode_t *pstcCustomMode)
{
    int32_t i32Ret  = LL_OK;

    if (NULL == pstcCustomMode) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_QSPI_INSTR_PROTOCOL(pstcCustomMode->u32InstrProtocol));
        DDL_ASSERT(IS_QSPI_ADDR_PROTOCOL(pstcCustomMode->u32AddrProtocol));
        DDL_ASSERT(IS_QSPI_DATA_PROTOCOL(pstcCustomMode->u32DataProtocol));

        MODIFY_REG32(CM_QSPI->CR, QSPI_CUSTOM_MD_CLR_MASK, (pstcCustomMode->u32InstrProtocol |
                                                            pstcCustomMode->u32AddrProtocol | pstcCustomMode->u32DataProtocol));
        WRITE_REG32(CM_QSPI->CCMD, pstcCustomMode->u8InstrCode);
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable XIP mode.
 * @param  [in] u8ModeCode              Enter or exit XIP mode code
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void QSPI_XipModeCmd(uint8_t u8ModeCode, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(CM_QSPI->XCMD, u8ModeCode);
    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_QSPI->CR, QSPI_CR_XIPE);
    } else {
        CLR_REG32_BIT(CM_QSPI->CR, QSPI_CR_XIPE);
    }
}

/**
 * @brief  Enter direct communication mode.
 * @param  None
 * @retval None
 */
void QSPI_EnterDirectCommMode(void)
{
    /* Backup the read mode */
    m_u32ReadMode = READ_REG32_BIT(CM_QSPI->CR, QSPI_CR_MDSEL);
    if (m_u32ReadMode <= QSPI_RD_MD_QUAD_IO_FAST_RD) {
        /* Set standard read mode */
        CLR_REG32_BIT(CM_QSPI->CR, QSPI_CR_MDSEL);
    }
    /* Enter direct communication mode */
    SET_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
}

/**
 * @brief  Exit direct communication mode.
 * @param  None
 * @retval None
 */
void QSPI_ExitDirectCommMode(void)
{
    /* Exit direct communication mode */
    CLR_REG32_BIT(CM_QSPI->CR, QSPI_CR_DCOME);
    if (m_u32ReadMode <= QSPI_RD_MD_QUAD_IO_FAST_RD) {
        /* Recovery the read mode */
        SET_REG32_BIT(CM_QSPI->CR, m_u32ReadMode);
    }
}

/**
 * @brief  Get the size of prefetched buffer.
 * @param  None
 * @retval uint8_t                      Prefetched buffer size.
 */
uint8_t QSPI_GetPrefetchBufSize(void)
{
    return (uint8_t)(READ_REG32_BIT(CM_QSPI->SR, QSPI_SR_PFNUM) >> QSPI_SR_PFNUM_POS);
}

/**
 * @brief  Get QSPI flag.
 * @param  [in] u32Flag                 QSPI flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg QSPI_FLAG_DIRECT_COMM_BUSY:   Serial transfer being processed
 *           @arg QSPI_FLAG_XIP_MD:             XIP mode
 *           @arg QSPI_FLAG_ROM_ACCESS_ERR:     ROM access detection status in direct communication mode
 *           @arg QSPI_FLAG_PREFETCH_BUF_FULL:  Prefetch buffer is full
 *           @arg QSPI_FLAG_PREFETCH_STOP:      Prefetch function operating
 *           @arg QSPI_FLAG_ALL:                All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t QSPI_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_QSPI_FLAG(u32Flag));

    if (0UL != READ_REG32_BIT(CM_QSPI->SR, u32Flag)) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/**
 * @brief  Clear QSPI flag.
 * @param  [in] u32Flag                 QSPI flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg QSPI_FLAG_ROM_ACCESS_ERR: ROM access detection status in direct communication mode
 *           @arg QSPI_FLAG_CLR_ALL:        All of the above
 * @retval None
 */
void QSPI_ClearStatus(uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_QSPI_CLR_FLAG(u32Flag));

    WRITE_REG32(CM_QSPI->SR2, u32Flag);
}

/**
 * @}
 */

#endif /* LL_QSPI_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
