/**
 *******************************************************************************
 * @file  hc32f4a0_sdioc.c
 * @brief This file provides firmware functions to manage the Secure Digital
 *        Input and Output Controller(SDIOC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
   2020-08-11       Yangjp          Fix a known potential risk in SDIOC_VerifyClockDiv function
   2020-09-04       Yangjp          Optimize timeout handling in functions
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
#include "hc32f4a0_sdioc.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_SDIOC SDIOC
 * @brief SDIOC Driver Library
 * @{
 */

#if (DDL_SDIOC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SDIOC_Local_Macros SDIOC Local Macros
 * @{
 */

/* Masks for R6 Response */
#define SDMMC_R6_GENERAL_UNKNOWN_ERROR          (0x00002000UL)
#define SDMMC_R6_ILLEGAL_CMD                    (0x00004000UL)
#define SDMMC_R6_COM_CRC_FAILED                 (0x00008000UL)

/* SDMMC command parameters */
#define SDMMC_CMD8_CHECK_PATTERN                (0x000001AAUL)
/* 3.2V-3.3V */
#define SDMMC_ACMD41_VOLTAGE_WINDOW             (0x80100000UL)

/* Command send and response timeout(ms) */
#define SDMMC_CMD_TIMEOUT                       (5000UL)
/* Max erase Timeout 60s */
#define SDMMC_MAX_ERASE_TIMEOUT                 (60000UL)

/* SDIOC software reset timeout(ms) */
#define SDIOC_SW_RESET_TIMEOUT                  (50UL)

/* SDIOC NORINTSGEN register Mask */
#define SDIOC_NORINTSGEN_CLEAR_MASK             (0x01F7U)
/* SDIOC ERRINTSGEN register Mask */
#define SDIOC_ERRINTSGEN_CLEAR_MASK             (0x017FU)

/*!< Get the specified register address of the specified SDIOC unit */
#define SDIOC_ARG(__UNIT__)                     ((uint32_t)(&((__UNIT__)->ARG0)))
#define SDIOC_BUF(__UNIT__)                     ((uint32_t)(&((__UNIT__)->BUF0)))
#define SDIOC_RESPx(__UNIT__, RESP_REG)         ((uint32_t)(&((__UNIT__)->RESP0)) + (uint32_t)(RESP_REG))

/**
 * @defgroup SDIOC_Check_Parameters_Validity SDIOC Check Parameters Validity
 * @{
 */
#define IS_SDIOC_UNIT(x)                                                       \
(   ((x) == M4_SDIOC1)                          ||                             \
    ((x) == M4_SDIOC2))

#define IS_SDIOC_MODE(x)                                                       \
(   ((x) == SDIOC_MODE_SD)                      ||                             \
    ((x) == SDIOC_MODE_MMC))

#define IS_SDIOC_CARD_DETECT_SELECT(x)                                         \
(   ((x) == SDIOC_CARD_DETECT_CD_PIN_LEVEL)     ||                             \
    ((x) == SDIOC_CARD_DETECT_TEST_SIGNAL))

#define IS_SDIOC_CARD_DETECT_TEST_LEVEL(x)                                     \
(   ((x) == SDIOC_CARD_DETECT_TEST_LEVEL_LOW)   ||                             \
    ((x) == SDIOC_CARD_DETECT_TEST_LEVEL_HIGH))

#define IS_SDIOC_SPEED_MODE(x)                                                 \
(   ((x) == SDIOC_SPEED_MODE_NORMAL)            ||                             \
    ((x) == SDIOC_SPEED_MODE_HIGH))

#define IS_SDIOC_BUS_WIDTH(x)                                                  \
(   ((x) == SDIOC_BUS_WIDTH_1BIT)               ||                             \
    ((x) == SDIOC_BUS_WIDTH_4BIT)               ||                             \
    ((x) == SDIOC_BUS_WIDTH_8BIT))

#define IS_SDIOC_CLOCK_DIV(x)                                                  \
(   ((x) == SDIOC_CLOCK_DIV_1)                  ||                             \
    ((x) == SDIOC_CLOCK_DIV_2)                  ||                             \
    ((x) == SDIOC_CLOCK_DIV_4)                  ||                             \
    ((x) == SDIOC_CLOCK_DIV_8)                  ||                             \
    ((x) == SDIOC_CLOCK_DIV_16)                 ||                             \
    ((x) == SDIOC_CLOCK_DIV_32)                 ||                             \
    ((x) == SDIOC_CLOCK_DIV_64)                 ||                             \
    ((x) == SDIOC_CLOCK_DIV_128)                ||                             \
    ((x) == SDIOC_CLOCK_DIV_256))

#define IS_SDIOC_CMD_TYPE(x)                                                   \
(   ((x) == SDIOC_CMD_TYPE_NORMAL)              ||                             \
    ((x) == SDIOC_CMD_TYPE_SUSPEND)             ||                             \
    ((x) == SDIOC_CMD_TYPE_RESUME)              ||                             \
    ((x) == SDIOC_CMD_TYPE_ABORT))

#define IS_SDIOC_DATA_LINE(x)                                                  \
(   ((x) == SDIOC_DATA_LINE_DISABLE)            ||                             \
    ((x) == SDIOC_DATA_LINE_ENABLE))

#define IS_SDIOC_TRANSFER_DIR(x)                                               \
(   ((x) == SDIOC_TRANSFER_DIR_TO_CARD)         ||                             \
    ((x) == SDIOC_TRANSFER_DIR_TO_HOST))

#define IS_SDIOC_AUTO_SEND_CMD12(x)                                            \
(   ((x) == SDIOC_AUTO_SEND_CMD12_DISABLE)      ||                             \
    ((x) == SDIOC_AUTO_SEND_CMD12_ENABLE))

#define IS_SDIOC_TRANSFER_MODE(x)                                              \
(   ((x) == SDIOC_TRANSFER_MODE_SINGLE)         ||                             \
    ((x) == SDIOC_TRANSFER_MODE_INFINITE)       ||                             \
    ((x) == SDIOC_TRANSFER_MODE_MULTIPLE)       ||                             \
    ((x) == SDIOC_TRANSFER_MODE_STOP_MULTIPLE))

#define IS_SDIOC_DATA_TIMEOUT_TIME(x)                                          \
(   ((x) == SDIOC_DATA_TIMEOUT_CLK_2_13)        ||                             \
    ((x) == SDIOC_DATA_TIMEOUT_CLK_2_14)        ||                             \
    ((x) == SDIOC_DATA_TIMEOUT_CLK_2_15)        ||                             \
    ((x) == SDIOC_DATA_TIMEOUT_CLK_2_16)        ||                             \
    ((x) == SDIOC_DATA_TIMEOUT_CLK_2_17)        ||                             \
    ((x) == SDIOC_DATA_TIMEOUT_CLK_2_18)        ||                             \
    ((x) == SDIOC_DATA_TIMEOUT_CLK_2_19)        ||                             \
    ((x) == SDIOC_DATA_TIMEOUT_CLK_2_20)        ||                             \
    ((x) == SDIOC_DATA_TIMEOUT_CLK_2_21)        ||                             \
    ((x) == SDIOC_DATA_TIMEOUT_CLK_2_22)        ||                             \
    ((x) == SDIOC_DATA_TIMEOUT_CLK_2_23)        ||                             \
    ((x) == SDIOC_DATA_TIMEOUT_CLK_2_24)        ||                             \
    ((x) == SDIOC_DATA_TIMEOUT_CLK_2_25)        ||                             \
    ((x) == SDIOC_DATA_TIMEOUT_CLK_2_26)        ||                             \
    ((x) == SDIOC_DATA_TIMEOUT_CLK_2_27))

#define IS_SDIOC_RESPONSE_REG(x)                                               \
(   ((x) == SDIOC_RESPONSE_REG_BIT0_31)         ||                             \
    ((x) == SDIOC_RESPONSE_REG_BIT32_63)        ||                             \
    ((x) == SDIOC_RESPONSE_REG_BIT64_95)        ||                             \
    ((x) == SDIOC_RESPONSE_REG_BIT96_127))

#define IS_SDIOC_SW_RESET_TYPE(x)                                              \
(   ((x) == SDIOC_SW_RESET_DATA_LINE)           ||                             \
    ((x) == SDIOC_SW_RESET_CMD_LINE)            ||                             \
    ((x) == SDIOC_SW_RESET_ALL))

#define IS_SDIOC_OUTPUT_CLK_FREQ(x)                                            \
(   ((x) == SDIOC_OUTPUT_CLK_FREQ_400K)         ||                             \
    ((x) == SDIOC_OUTPUT_CLK_FREQ_25M)          ||                             \
    ((x) == SDIOC_OUTPUT_CLK_FREQ_26M)          ||                             \
    ((x) == SDIOC_OUTPUT_CLK_FREQ_50M)          ||                             \
    ((x) == SDIOC_OUTPUT_CLK_FREQ_52M))

#define IS_SDIOC_GET_HOST_FLAG(x)                                              \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(SDIOC_HOST_FLAG_CMDL       |                  \
                                 SDIOC_HOST_FLAG_DATL       |                  \
                                 SDIOC_HOST_FLAG_DATL_D0    |                  \
                                 SDIOC_HOST_FLAG_DATL_D1    |                  \
                                 SDIOC_HOST_FLAG_DATL_D2    |                  \
                                 SDIOC_HOST_FLAG_DATL_D3    |                  \
                                 SDIOC_HOST_FLAG_WPL        |                  \
                                 SDIOC_HOST_FLAG_CDL        |                  \
                                 SDIOC_HOST_FLAG_CSS        |                  \
                                 SDIOC_HOST_FLAG_CIN        |                  \
                                 SDIOC_HOST_FLAG_BRE        |                  \
                                 SDIOC_HOST_FLAG_BWE        |                  \
                                 SDIOC_HOST_FLAG_RTA        |                  \
                                 SDIOC_HOST_FLAG_WTA        |                  \
                                 SDIOC_HOST_FLAG_DA         |                  \
                                 SDIOC_HOST_FLAG_CID        |                  \
                                 SDIOC_HOST_FLAG_CIC))))))

#define IS_SDIOC_GET_NORMAL_ERROR_INT_FLAG(x)                                  \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(SDIOC_NORMAL_INT_FLAG_EI   |                  \
                                 SDIOC_NORMAL_INT_FLAG_CINT |                  \
                                 SDIOC_NORMAL_INT_FLAG_CRM  |                  \
                                 SDIOC_NORMAL_INT_FLAG_CIST |                  \
                                 SDIOC_NORMAL_INT_FLAG_BRR  |                  \
                                 SDIOC_NORMAL_INT_FLAG_BWR  |                  \
                                 SDIOC_NORMAL_INT_FLAG_BGE  |                  \
                                 SDIOC_NORMAL_INT_FLAG_TC   |                  \
                                 SDIOC_NORMAL_INT_FLAG_CC   |                  \
                                 SDIOC_ERROR_INT_FLAG_ACE   |                  \
                                 SDIOC_ERROR_INT_FLAG_DEBE  |                  \
                                 SDIOC_ERROR_INT_FLAG_DCE   |                  \
                                 SDIOC_ERROR_INT_FLAG_DTOE  |                  \
                                 SDIOC_ERROR_INT_FLAG_CIE   |                  \
                                 SDIOC_ERROR_INT_FLAG_CEBE  |                  \
                                 SDIOC_ERROR_INT_FLAG_CCE   |                  \
                                 SDIOC_ERROR_INT_FLAG_CTOE))))))

#define IS_SDIOC_CLEAR_NORMAL_ERROR_INT_FLAG(x)                                \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(SDIOC_NORMAL_INT_FLAG_CRM  |                  \
                                 SDIOC_NORMAL_INT_FLAG_CIST |                  \
                                 SDIOC_NORMAL_INT_FLAG_BRR  |                  \
                                 SDIOC_NORMAL_INT_FLAG_BWR  |                  \
                                 SDIOC_NORMAL_INT_FLAG_BGE  |                  \
                                 SDIOC_NORMAL_INT_FLAG_TC   |                  \
                                 SDIOC_NORMAL_INT_FLAG_CC   |                  \
                                 SDIOC_ERROR_INT_FLAG_ACE   |                  \
                                 SDIOC_ERROR_INT_FLAG_DEBE  |                  \
                                 SDIOC_ERROR_INT_FLAG_DCE   |                  \
                                 SDIOC_ERROR_INT_FLAG_DTOE  |                  \
                                 SDIOC_ERROR_INT_FLAG_CIE   |                  \
                                 SDIOC_ERROR_INT_FLAG_CEBE  |                  \
                                 SDIOC_ERROR_INT_FLAG_CCE   |                  \
                                 SDIOC_ERROR_INT_FLAG_CTOE))))))

#define IS_SDIOC_NORMAL_ERROR_INT(x)                                           \
(   (0UL != (x))                                            &&                 \
    (0UL == ((x) & ((uint32_t)(~(SDIOC_NORMAL_INT_CINTSEN   |                  \
                                 SDIOC_NORMAL_INT_CRMSEN    |                  \
                                 SDIOC_NORMAL_INT_CISTSEN   |                  \
                                 SDIOC_NORMAL_INT_BRRSEN    |                  \
                                 SDIOC_NORMAL_INT_BWRSEN    |                  \
                                 SDIOC_NORMAL_INT_BGESEN    |                  \
                                 SDIOC_NORMAL_INT_TCSEN     |                  \
                                 SDIOC_NORMAL_INT_CCSEN     |                  \
                                 SDIOC_ERROR_INT_ACESEN     |                  \
                                 SDIOC_ERROR_INT_DEBESEN    |                  \
                                 SDIOC_ERROR_INT_DCESEN     |                  \
                                 SDIOC_ERROR_INT_DTOESEN    |                  \
                                 SDIOC_ERROR_INT_CIESEN     |                  \
                                 SDIOC_ERROR_INT_CEBESEN    |                  \
                                 SDIOC_ERROR_INT_CCESEN     |                  \
                                 SDIOC_ERROR_INT_CTOESEN))))))

#define IS_SDIOC_AUTO_CMD_ERROR_FLAG(x)                                        \
(   (0U != (x))                                                             && \
    (0U == ((x) & ((uint16_t)(~(uint16_t)(SDIOC_AUTO_CMD_ERROR_FLAG_CMDE    |  \
                                          SDIOC_AUTO_CMD_ERROR_FLAG_IE      |  \
                                          SDIOC_AUTO_CMD_ERROR_FLAG_EBE     |  \
                                          SDIOC_AUTO_CMD_ERROR_FLAG_CE      |  \
                                          SDIOC_AUTO_CMD_ERROR_FLAG_TOE     |  \
                                          SDIOC_AUTO_CMD_ERROR_FLAG_NE))))))

#define IS_SDIOC_FORCE_AUTO_CMD_FLAG(x)                                        \
(   (0U != (x))                                                             && \
    (0U == ((x) & ((uint16_t)(~(uint16_t)(SDIOC_FORCE_AUTO_CMD_ERROR_FCMDE  |  \
                                          SDIOC_FORCE_AUTO_CMD_ERROR_FIE    |  \
                                          SDIOC_FORCE_AUTO_CMD_ERROR_FEBE   |  \
                                          SDIOC_FORCE_AUTO_CMD_ERROR_FCE    |  \
                                          SDIOC_FORCE_AUTO_CMD_ERROR_FTOE   |  \
                                          SDIOC_FORCE_AUTO_CMD_ERROR_FNE))))))

#define IS_SDIOC_FORCE_ERROR_INT_FLAG(x)                                       \
(   (0U != (x))                                                             && \
    (0U == ((x) & ((uint16_t)(~(uint16_t)(SDIOC_FORCE_ERROR_INT_FACE        |  \
                                          SDIOC_FORCE_ERROR_INT_FDEBE       |  \
                                          SDIOC_FORCE_ERROR_INT_FDCE        |  \
                                          SDIOC_FORCE_ERROR_INT_FDTOE       |  \
                                          SDIOC_FORCE_ERROR_INT_FCIE        |  \
                                          SDIOC_FORCE_ERROR_INT_FCEBE       |  \
                                          SDIOC_FORCE_ERROR_INT_FCCE        |  \
                                          SDIOC_FORCE_ERROR_INT_FCTOE))))))

#define IS_SDIOC_RESOPNE_TYPE(x)                                               \
(   ((x) == SDIOC_RESOPNE_TYPE_NO)              ||                             \
    ((x) == SDIOC_RESOPNE_TYPE_R2)              ||                             \
    ((x) == SDIOC_RESOPNE_TYPE_R3_R4)           ||                             \
    ((x) == SDIOC_RESOPNE_TYPE_R1_R5_R6_R7)     ||                             \
    ((x) == SDIOC_RESOPNE_TYPE_R1B_R5B))

#define IS_SDIOC_CMD_INDEX(x)                   ((x) < 0x40U)

#define IS_SDIOC_BLOCK_SIZE(x)                  (((x) >= 1U) && ((x) <= 512U))

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
static en_result_t SDMMC_WaitResponse(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32CheckFlag, uint32_t u32Timeout, uint32_t *pu32ErrSta);
static en_result_t SDMMC_GetCmdError(M4_SDIOC_TypeDef *SDIOCx);
static en_result_t SDMMC_GetCmdResp1(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Timeout, uint32_t *pu32ErrSta);
static en_result_t SDMMC_GetCmdResp1Busy(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Timeout, uint32_t *pu32ErrSta);
static en_result_t SDMMC_GetCmdResp2(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta);
static en_result_t SDMMC_GetCmdResp3(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta);
static en_result_t SDMMC_GetCmdResp6(M4_SDIOC_TypeDef *SDIOCx, uint16_t *pu16RCA, uint32_t *pu32ErrSta);
static en_result_t SDMMC_GetCmdResp7(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta);

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup SDIOC_Global_Functions SDIOC Global Functions
 * @{
 */
/**
 * @brief  De-Initialize SDIOC.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @retval An en_result_t enumeration value:
 *           - Ok: SDIOC De-Initialize success
 *           - ErrorTimeout: Software reset timeout
 */
en_result_t SDIOC_DeInit(M4_SDIOC_TypeDef *SDIOCx)
{
    return SDIOC_SoftwareReset(SDIOCx, SDIOC_SW_RESET_ALL);
}

/**
 * @brief  Initialize SDIOC.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] pstcSdiocInit           Pointer to a @ref stc_sdioc_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: SDIOC Initialize success
 *           - ErrorInvalidParameter: pstcSdiocInit == NULL
 */
en_result_t SDIOC_Init(M4_SDIOC_TypeDef *SDIOCx, const stc_sdioc_init_t *pstcSdiocInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcSdiocInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
        DDL_ASSERT(IS_SDIOC_MODE(pstcSdiocInit->u32Mode));
        DDL_ASSERT(IS_SDIOC_CARD_DETECT_SELECT(pstcSdiocInit->u8CardDetectSelect));
        DDL_ASSERT(IS_SDIOC_SPEED_MODE(pstcSdiocInit->u8SpeedMode));
        DDL_ASSERT(IS_SDIOC_BUS_WIDTH(pstcSdiocInit->u8BusWidth));
        DDL_ASSERT(IS_SDIOC_CLOCK_DIV(pstcSdiocInit->u16ClockDiv));

        /* Set the SDIOC mode */
        if (M4_SDIOC1 == SDIOCx)
        {
            WRITE_REG32(bM4_PERIC->SDIOC_SYCTLREG_b.SELMMC1, pstcSdiocInit->u32Mode);
        }
        else
        {
            WRITE_REG32(bM4_PERIC->SDIOC_SYCTLREG_b.SELMMC2, pstcSdiocInit->u32Mode);
        }

        /* Set the SDIOC clock control value */
        WRITE_REG16(SDIOCx->CLKCON, (pstcSdiocInit->u16ClockDiv | SDIOC_CLKCON_ICE | SDIOC_CLKCON_CE));
        /* Set the SDIOC host control value */
        WRITE_REG8(SDIOCx->HOSTCON, (pstcSdiocInit->u8CardDetectSelect |
                                     pstcSdiocInit->u8BusWidth | pstcSdiocInit->u8SpeedMode));
        /* Enable normal interrupt status */
        WRITE_REG16(SDIOCx->NORINTSTEN, SDIOC_NORINTSGEN_CLEAR_MASK);
        /* Enable error interrupt status */
        WRITE_REG16(SDIOCx->ERRINTSTEN, SDIOC_ERRINTSGEN_CLEAR_MASK);
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_sdioc_init_t to default values.
 * @param  [out] pstcSdiocInit          Pointer to a @ref stc_sdioc_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Structure Initialize success
 *           - ErrorInvalidParameter: pstcSdiocInit == NULL
 */
en_result_t SDIOC_StructInit(stc_sdioc_init_t *pstcSdiocInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcSdiocInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcSdiocInit->u32Mode            = SDIOC_MODE_SD;
        pstcSdiocInit->u8CardDetectSelect = SDIOC_CARD_DETECT_CD_PIN_LEVEL;
        pstcSdiocInit->u8SpeedMode        = SDIOC_SPEED_MODE_NORMAL;
        pstcSdiocInit->u8BusWidth         = SDIOC_BUS_WIDTH_1BIT;
        pstcSdiocInit->u16ClockDiv        = SDIOC_CLOCK_DIV_1;
    }

    return enRet;
}

/**
 * @brief  Set software reset.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u8ResetType             Software reset type
 *         This parameter can be one of the following values:
 *           @arg SDIOC_SW_RESET_DATA_LINE: Only part of data circuit is reset
 *           @arg SDIOC_SW_RESET_CMD_LINE:  Only part of command circuit is reset
 *           @arg SDIOC_SW_RESET_ALL:       Reset the entire Host Controller except for the card detection circuit
 * @retval An en_result_t enumeration value:
 *           - Ok: Software reset success
 *           - ErrorTimeout: Software reset timeout
 */
en_result_t SDIOC_SoftwareReset(M4_SDIOC_TypeDef *SDIOCx, uint8_t u8ResetType)
{
    en_result_t enRet = Ok;
    __IO uint32_t u32Count;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_SW_RESET_TYPE(u8ResetType));

    WRITE_REG8(SDIOCx->SFTRST, u8ResetType);
    /* Wait for reset finish */
    u32Count = SDIOC_SW_RESET_TIMEOUT * (HCLK_VALUE / 20000UL);
    while (0U != READ_REG8_BIT(SDIOCx->SFTRST, u8ResetType))
    {
        if (0UL == u32Count)
        {
            enRet = ErrorTimeout;
            break;
        }
        u32Count--;
    }

    return enRet;
}

/**
 * @brief  Enable or disable power.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] enNewSta                The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void SDIOC_PowerCmd(M4_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (Disable != enNewSta)
    {
        SET_REG8_BIT(SDIOCx->PWRCON, SDIOC_PWRCON_PWON);
    }
    else
    {
        CLEAR_REG8_BIT(SDIOCx->PWRCON, SDIOC_PWRCON_PWON);
    }
}

/**
 * @brief  Get power state.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @retval An en_result_t enumeration value:
 *           - Disable: Power off or SDIOCx == NULL
 *           - Enable: Power on
 */
en_functional_state_t SDIOC_GetPowerState(const M4_SDIOC_TypeDef *SDIOCx)
{
    en_functional_state_t enPowerSta = Disable;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));

    if (0U != (READ_REG8_BIT(SDIOCx->PWRCON, SDIOC_PWRCON_PWON)))
    {
        enPowerSta = Enable;
    }

    return enPowerSta;
}

/**
 * @brief  Get SDIOC work mode.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @retval uint32_t value:
 *           - SDIOC_MODE_SD:   SDIOCx selects SD mode
 *           - SDIOC_MODE_MMC:  SDIOCx selects MMC mode
 */
uint32_t SDIOC_GetMode(const M4_SDIOC_TypeDef *SDIOCx)
{
    uint32_t u32SdMode;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));

    u32SdMode = READ_REG32_BIT(M4_PERIC->SDIOC_SYCTLREG, ((M4_SDIOC1 == SDIOCx) ?
                                                          PERIC_SDIOC_SYCTLREG_SELMMC1 : PERIC_SDIOC_SYCTLREG_SELMMC2));
    if (0UL != u32SdMode)   /* MMC mode */
    {
        u32SdMode = SDIOC_MODE_MMC;
    }

    return u32SdMode;
}

/**
 * @brief  Enable or disable clock output.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] enNewSta                The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void SDIOC_ClockCmd(M4_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (Disable != enNewSta)
    {
        SET_REG8_BIT(SDIOCx->CLKCON, SDIOC_CLKCON_CE);
    }
    else
    {
        CLEAR_REG8_BIT(SDIOCx->CLKCON, SDIOC_CLKCON_CE);
    }
}

/**
 * @brief  Set clock division.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u16ClkDiv               Clock division
 *         This parameter can be one of the following values:
 *           @arg SDIOC_CLOCK_DIV_1:    PCLK1/1
 *           @arg SDIOC_CLOCK_DIV_2:    PCLK1/2
 *           @arg SDIOC_CLOCK_DIV_4:    PCLK1/4
 *           @arg SDIOC_CLOCK_DIV_8:    PCLK1/8
 *           @arg SDIOC_CLOCK_DIV_16:   PCLK1/16
 *           @arg SDIOC_CLOCK_DIV_32:   PCLK1/32
 *           @arg SDIOC_CLOCK_DIV_64:   PCLK1/64
 *           @arg SDIOC_CLOCK_DIV_128:  PCLK1/128
 *           @arg SDIOC_CLOCK_DIV_256:  PCLK1/256
 * @retval None
 */
void SDIOC_SetClockDiv(M4_SDIOC_TypeDef *SDIOCx, uint16_t u16ClkDiv)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_CLOCK_DIV(u16ClkDiv));

    MODIFY_REG16(SDIOCx->CLKCON, SDIOC_CLKCON_FS, u16ClkDiv);
}

/**
 * @brief  Find the most suitable clock division for the set clock frequency.
 * @note   More clock values can be set as needed, but the maximum cannot exceed 50MHz.
 * @param  [in] u32ClkFreq              SDIOCx_CK clock frequency
 *         This parameter can be one of the following values:
 *           @arg SDIOC_OUTPUT_CLK_FREQ_400K:   SDIOC clock: 400KHz
 *           @arg SDIOC_OUTPUT_CLK_FREQ_25M:    SDIOC clock: 25MHz
 *           @arg SDIOC_OUTPUT_CLK_FREQ_26M:    SDIOC clock: 26MHz
 *           @arg SDIOC_OUTPUT_CLK_FREQ_50M:    SDIOC clock: 50MHz
 *           @arg SDIOC_OUTPUT_CLK_FREQ_52M:    SDIOC clock: 52MHz
 *           @arg Any other value
 * @param  [out] pu16ClkDiv             Pointer to a value of clock division
 * @retval An en_result_t enumeration value:
 *           - Ok: SDIOC Initialize success
 *           - Error: The Bus clock frequency is too high
 *           - ErrorInvalidParameter: pu16ClkDiv == NULL or 0UL == u32ClkFreq
 */
en_result_t SDIOC_GetOptimumClockDiv(uint32_t u32ClkFreq, uint16_t *pu16ClkDiv)
{
    en_result_t enRet = Ok;
    uint32_t u32BusClk;
    uint32_t u32ClkDiv;
    uint32_t u32Temp;

    if ((NULL == pu16ClkDiv) || (0UL == u32ClkFreq))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Get PCLK1 frequency */
        u32BusClk = SystemCoreClock / (0x01UL << (READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS));
        u32ClkDiv = u32BusClk / u32ClkFreq;
        if (0UL != (u32BusClk % u32ClkFreq))
        {
            u32ClkDiv++;
        }

        /* Check the effectiveness of clock division */
        if (u32ClkDiv > 256U)   /* Maximum division is 256 */
        {
            enRet = Error;
        }
        else
        {
            if (1U == u32ClkDiv)
            {
                *pu16ClkDiv = SDIOC_CLOCK_DIV_1;
            }
            else
            {
                for (u32Temp=SDIOC_CLOCK_DIV_2; u32Temp<=SDIOC_CLOCK_DIV_256; u32Temp<<=1U)
                {
                    if (u32ClkDiv <= (u32Temp >> (SDIOC_CLKCON_FS_POS - 1U)))
                    {
                        break;
                    }
                }
                *pu16ClkDiv = (uint16_t)u32Temp;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Verify the validity of the clock division.
 * @param  [in] u32Mode                 SDIOC work mode
 *         This parameter can be one of the following values:
 *           @arg SDIOC_MODE_SD:        SDIOCx selects SD mode
 *           @arg SDIOC_MODE_MMC:       SDIOCx selects MMC mode
 * @param  [in] u8SpeedMode             Speed mode
 *         This parameter can be one of the following values:
 *           @arg SDIOC_SPEED_MODE_NORMAL:  Normal speed mode
 *           @arg SDIOC_SPEED_MODE_HIGH:    High speed mode
 * @param  [in] u16ClkDiv               Clock division
 *         This parameter can be one of the following values:
 *           @arg SDIOC_CLOCK_DIV_1:    PCLK1/1
 *           @arg SDIOC_CLOCK_DIV_2:    PCLK1/2
 *           @arg SDIOC_CLOCK_DIV_4:    PCLK1/4
 *           @arg SDIOC_CLOCK_DIV_8:    PCLK1/8
 *           @arg SDIOC_CLOCK_DIV_16:   PCLK1/16
 *           @arg SDIOC_CLOCK_DIV_32:   PCLK1/32
 *           @arg SDIOC_CLOCK_DIV_64:   PCLK1/64
 *           @arg SDIOC_CLOCK_DIV_128:  PCLK1/128
 *           @arg SDIOC_CLOCK_DIV_256:  PCLK1/256
 * @retval An en_result_t enumeration value:
 *           - Ok: The clock division is valid
 *           - Error: The Bus clock frequency is too high
 */
en_result_t SDIOC_VerifyClockDiv(uint32_t u32Mode, uint8_t u8SpeedMode, uint16_t u16ClkDiv)
{
    en_result_t enRet = Ok;
    uint32_t u32BusClk;
    uint32_t u32ClkFreq;
    uint32_t u32MaxFreq;
    uint32_t u32DivValue;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_MODE(u32Mode));
    DDL_ASSERT(IS_SDIOC_SPEED_MODE(u8SpeedMode));
    DDL_ASSERT(IS_SDIOC_CLOCK_DIV(u16ClkDiv));

    /* Get PCLK1 frequency */
    u32BusClk = SystemCoreClock / (0x01UL << (READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS));
    u32DivValue = ((uint32_t)u16ClkDiv >> (SDIOC_CLKCON_FS_POS - 1U));
    if (0UL == u32DivValue)
    {
        u32ClkFreq = u32BusClk;
    }
    else
    {
        u32ClkFreq = u32BusClk / u32DivValue;
    }

    if (SDIOC_SPEED_MODE_NORMAL == u8SpeedMode)
    {
        if (SDIOC_MODE_SD != u32Mode)   /* MMC mode */
        {
            u32MaxFreq = SDIOC_OUTPUT_CLK_FREQ_26M;
        }
        else
        {
            u32MaxFreq = SDIOC_OUTPUT_CLK_FREQ_25M;
        }
    }
    else
    {
        if (SDIOC_MODE_SD != u32Mode)   /* MMC mode */
        {
            u32MaxFreq = SDIOC_OUTPUT_CLK_FREQ_52M;
        }
        else
        {
            u32MaxFreq = SDIOC_OUTPUT_CLK_FREQ_50M;
        }
    }

    if (u32ClkFreq > u32MaxFreq)
    {
        enRet = Error;
    }

    return enRet;
}

/**
 * @brief  Get device insert state.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @retval An en_result_t enumeration value:
 *           - Disable: No device inserted
 *           - Enable:  The device inserted
 */
en_functional_state_t SDIOC_GetDeviceInsertState(const M4_SDIOC_TypeDef *SDIOCx)
{
    en_functional_state_t enInsertSta = Disable;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));

    if (0UL != (READ_REG32_BIT(SDIOCx->PSTAT, SDIOC_PSTAT_CSS)))
    {
        if (0UL != (READ_REG32_BIT(SDIOCx->PSTAT, SDIOC_PSTAT_CIN)))
        {
            enInsertSta = Enable;
        }
    }

    return enInsertSta;
}

/**
 * @brief  Set speed mode.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u8SpeedMode             Speed mode
 *         This parameter can be one of the following values:
 *           @arg SDIOC_SPEED_MODE_NORMAL:  Normal speed mode
 *           @arg SDIOC_SPEED_MODE_HIGH:    High speed mode
 * @retval None
 */
void SDIOC_SetSpeedMode(M4_SDIOC_TypeDef *SDIOCx, uint8_t u8SpeedMode)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_SPEED_MODE(u8SpeedMode));

    if (SDIOC_SPEED_MODE_NORMAL != u8SpeedMode)
    {
        SET_REG8_BIT(SDIOCx->HOSTCON, SDIOC_HOSTCON_HSEN);
    }
    else
    {
        CLEAR_REG8_BIT(SDIOCx->HOSTCON, SDIOC_HOSTCON_HSEN);
    }
}

/**
 * @brief  Set bus width.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u8BusWidth              Bus width
 *         This parameter can be one of the following values:
 *           @arg SDIOC_BUS_WIDTH_1BIT: The Bus width is 1 bit
 *           @arg SDIOC_BUS_WIDTH_4BIT: The Bus width is 4 bit
 *           @arg SDIOC_BUS_WIDTH_8BIT: The Bus width is 8 bit
 * @retval None
 */
void SDIOC_SetBusWidth(M4_SDIOC_TypeDef *SDIOCx, uint8_t u8BusWidth)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_BUS_WIDTH(u8BusWidth));

    MODIFY_REG8(SDIOCx->HOSTCON, (SDIOC_HOSTCON_DW | SDIOC_HOSTCON_EXDW), u8BusWidth);
}

/**
 * @brief  Set card detect line select.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u8Src                   Card detect source
 *         This parameter can be one of the following values:
 *           @arg SDIOC_CARD_DETECT_CD_PIN_LEVEL:   SDIOCx_CD(x=1~2) line is selected (for normal use)
 *           @arg SDIOC_CARD_DETECT_TEST_SIGNAL:    The Card Detect Test Level is selected(for test purpose)
 * @retval None
 */
void SDIOC_SetCardDetectSource(M4_SDIOC_TypeDef *SDIOCx, uint8_t u8Src)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_CARD_DETECT_SELECT(u8Src));

    if (SDIOC_CARD_DETECT_CD_PIN_LEVEL != u8Src)
    {
        SET_REG8_BIT(SDIOCx->HOSTCON, SDIOC_HOSTCON_CDSS);
    }
    else
    {
        CLEAR_REG8_BIT(SDIOCx->HOSTCON, SDIOC_HOSTCON_CDSS);
    }
}

/**
 * @brief  Set card detect test level.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u8Level                 Card test level
 *         This parameter can be one of the following values:
 *           @arg SDIOC_CARD_DETECT_TEST_LEVEL_LOW:     Card identification test signal is low level (with device insertion)
 *           @arg SDIOC_CARD_DETECT_TEST_LEVEL_HIGH:    Card identification test signal is high level (no device insertion)
 * @retval None
 */
void SDIOC_SetCardDetectTestLevel(M4_SDIOC_TypeDef *SDIOCx, uint8_t u8Level)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_CARD_DETECT_TEST_LEVEL(u8Level));

    if (SDIOC_CARD_DETECT_TEST_LEVEL_LOW != u8Level)
    {
        SET_REG8_BIT(SDIOCx->HOSTCON, SDIOC_HOSTCON_CDTL);
    }
    else
    {
        CLEAR_REG8_BIT(SDIOCx->HOSTCON, SDIOC_HOSTCON_CDTL);
    }
}

/**
 * @brief  Configure the SDIOCx command parameters.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] pstcCmd                 Pointer to a @ref stc_sdioc_cmd_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Configure SDIOCx command parameters success
 *           - ErrorInvalidParameter: pstcCmd == NULL
 */
en_result_t SDIOC_SendCommand(M4_SDIOC_TypeDef *SDIOCx, const stc_sdioc_cmd_init_t *pstcCmd)
{
    en_result_t enRet = Ok;
    __IO uint32_t *pu32Temp;

    if (NULL == pstcCmd)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
        DDL_ASSERT(IS_SDIOC_CMD_INDEX(pstcCmd->u16CmdIndex));
        DDL_ASSERT(IS_SDIOC_CMD_TYPE(pstcCmd->u16CmdType));
        DDL_ASSERT(IS_SDIOC_DATA_LINE(pstcCmd->u16DataLineEn));
        DDL_ASSERT(IS_SDIOC_RESOPNE_TYPE(pstcCmd->u16RespType));

        /* Set the SDIOC Command parameters value */
        pu32Temp = (__IO uint32_t *)SDIOC_ARG(SDIOCx);
        WRITE_REG32(*pu32Temp, pstcCmd->u32Argument);
        /* Set the SDIOC Command controller value */
        WRITE_REG16(SDIOCx->CMD, ((uint16_t)(pstcCmd->u16CmdIndex << SDIOC_CMD_IDX_POS) |
                                  pstcCmd->u16CmdType | pstcCmd->u16DataLineEn | pstcCmd->u16RespType));
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_sdioc_cmd_init_t to default values.
 * @param  [out] pstcCmd                Pointer to a @ref stc_sdioc_cmd_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Structure Initialize success
 *           - ErrorInvalidParameter: pstcData == NULL
 */
en_result_t SDIOC_CmdStructInit(stc_sdioc_cmd_init_t *pstcCmd)
{
    en_result_t enRet = Ok;

    if (NULL == pstcCmd)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcCmd->u32Argument   = 0U;
        pstcCmd->u16CmdIndex   = 0U;
        pstcCmd->u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        pstcCmd->u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        pstcCmd->u16RespType   = SDIOC_RESOPNE_TYPE_NO;
    }

    return enRet;
}

/**
 * @brief  Get the response received from the card for the last command
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u8RespReg               SDIOC response register
 *         This parameter can be one of the following values:
 *           @arg SDIOC_RESPONSE_REG_BIT0_31:   Command Response Register 0-31bit
 *           @arg SDIOC_RESPONSE_REG_BIT32_63:  Command Response Register 32-63bit
 *           @arg SDIOC_RESPONSE_REG_BIT64_95:  Command Response Register 64-95bit
 *           @arg SDIOC_RESPONSE_REG_BIT96_127: Command Response Register 96-127bit
 * @param  [out] pu32RespVal            Pointer to a Response value
 * @retval An en_result_t enumeration value:
 *           - Ok: Get response success
 *           - ErrorInvalidParameter: pu32RespVal == NULL
 */
en_result_t SDIOC_GetResponse(M4_SDIOC_TypeDef *SDIOCx, uint8_t u8RespReg, uint32_t *pu32RespVal)
{
    en_result_t enRet = Ok;

    if (NULL == pu32RespVal)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
        DDL_ASSERT(IS_SDIOC_RESPONSE_REG(u8RespReg));

        *pu32RespVal = READ_REG32(*(__IO uint32_t *)SDIOC_RESPx(SDIOCx, u8RespReg));
    }

    return enRet;
}

/**
 * @brief  Configure the SDIOCx data parameters.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] pstcData                Pointer to a @ref stc_sdioc_data_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Configure SDIOCx data parameters success
 *           - ErrorInvalidParameter: pstcData == NULL
 */
en_result_t SDIOC_ConfigData(M4_SDIOC_TypeDef *SDIOCx, const stc_sdioc_data_init_t *pstcData)
{
    en_result_t enRet = Ok;
    uint16_t u16BlkCnt;

    if (NULL == pstcData)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
        DDL_ASSERT(IS_SDIOC_BLOCK_SIZE(pstcData->u16BlockSize));
        DDL_ASSERT(IS_SDIOC_TRANSFER_DIR(pstcData->u16TransferDir));
        DDL_ASSERT(IS_SDIOC_AUTO_SEND_CMD12(pstcData->u16AutoCMD12En));
        DDL_ASSERT(IS_SDIOC_TRANSFER_MODE(pstcData->u16TransferMode));
        DDL_ASSERT(IS_SDIOC_DATA_TIMEOUT_TIME(pstcData->u16DataTimeout));

        if (SDIOC_TRANSFER_MODE_STOP_MULTIPLE == pstcData->u16TransferMode)
        {
            u16BlkCnt = 0U;
        }
        else
        {
            u16BlkCnt = pstcData->u16BlockCount;
        }

        /* Set the SDIOC Data Transfer Timeout value */
        WRITE_REG8(SDIOCx->TOUTCON, pstcData->u16DataTimeout);
        /* Set the SDIOC Block Count value */
        WRITE_REG16(SDIOCx->BLKSIZE, pstcData->u16BlockSize);
        /* Set the SDIOC Block Size value */
        WRITE_REG16(SDIOCx->BLKCNT,u16BlkCnt);
        /* Set the SDIOC Data Transfer Mode */
        WRITE_REG16(SDIOCx->TRANSMODE, ((pstcData->u16TransferDir |
                                        pstcData->u16AutoCMD12En | pstcData->u16TransferMode) & 0x00FFU));
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_sdioc_data_init_t to default values.
 * @param  [out] pstcData               Pointer to a @ref stc_sdioc_data_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Structure Initialize success
 *           - ErrorInvalidParameter: pstcData == NULL
 */
en_result_t SDIOC_DataStructInit(stc_sdioc_data_init_t *pstcData)
{
    en_result_t enRet = Ok;

    if (NULL == pstcData)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcData->u16BlockSize    = 512U;
        pstcData->u16BlockCount   = 0U;
        pstcData->u16TransferDir  = SDIOC_TRANSFER_DIR_TO_CARD;
        pstcData->u16AutoCMD12En  = SDIOC_AUTO_SEND_CMD12_DISABLE;
        pstcData->u16TransferMode = SDIOC_TRANSFER_MODE_SINGLE;
        pstcData->u16DataTimeout  = SDIOC_DATA_TIMEOUT_CLK_2_13;
    }

    return enRet;
}

/**
 * @brief  Read data from SDIOC FIFO.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [out] au8Data                Pointer to the buffer
 * @param  [in] u32Len                  Data length
 * @retval An en_result_t enumeration value:
 *           - Ok: Read data success
 *           - ErrorInvalidParameter: NULL == au8Data or (u32Len % 4U) != 0
 */
en_result_t SDIOC_ReadBuffer(M4_SDIOC_TypeDef *SDIOCx, uint8_t au8Data[], uint32_t u32Len)
{
    en_result_t enRet = Ok;
    uint32_t i;
    uint32_t u32Temp;
    __IO uint32_t *BUF_REG;

    if ((NULL == au8Data) || (0U != (u32Len % 4U)))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));

        BUF_REG = (__IO uint32_t *)SDIOC_BUF(SDIOCx);
        for (i = 0U; i < u32Len; i += 4U)
        {
            u32Temp = READ_REG32(*BUF_REG);
            au8Data[i]    = (uint8_t)(u32Temp & 0x000000FFUL);
            au8Data[i+1U] = (uint8_t)((u32Temp >> 8U) & 0x000000FFUL);
            au8Data[i+2U] = (uint8_t)((u32Temp >> 16U) & 0x000000FFUL);
            au8Data[i+3U] = (uint8_t)((u32Temp >> 24U) & 0x000000FFUL);
        }
    }

    return enRet;
}

/**
 * @brief  Write data to SDIOC FIFO.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] au8Data                 Pointer to the buffer
 * @param  [in] u32Len                  Data length
 * @retval An en_result_t enumeration value:
 *           - Ok: Write data success
 *           - ErrorInvalidParameter: NULL == au8Data or (u32Len % 4U) != 0
 */
en_result_t SDIOC_WriteBuffer(M4_SDIOC_TypeDef *SDIOCx, const uint8_t au8Data[], uint32_t u32Len)
{
    en_result_t enRet = Ok;
    uint32_t i;
    uint32_t u32Temp;
    __IO uint32_t *BUF_REG;

    if ((NULL == au8Data) || (0U != (u32Len % 4U)))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));

        BUF_REG = (__IO uint32_t *)SDIOC_BUF(SDIOCx);
        for (i = 0U; i < u32Len; i += 4U)
        {
            u32Temp = (uint32_t)au8Data[i]             | ((uint32_t)au8Data[i+1U] << 8U) |
                      ((uint32_t)au8Data[i+2U] << 16U) | ((uint32_t)au8Data[i+3U] << 24U);
            WRITE_REG32(*BUF_REG, u32Temp);
        }
    }

    return enRet;
}

/**
 * @brief  Enable or disable block gap stop.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] enNewSta                The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void SDIOC_BlockGapStopCmd(M4_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (Disable != enNewSta)
    {
        SET_REG8_BIT(SDIOCx->BLKGPCON, SDIOC_BLKGPCON_SABGR);
    }
    else
    {
        CLEAR_REG8_BIT(SDIOCx->BLKGPCON, SDIOC_BLKGPCON_SABGR);
    }
}

/**
 * @brief  Restart data transfer.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @retval None
 */
void SDIOC_RestartTransfer(M4_SDIOC_TypeDef *SDIOCx)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));

    SET_REG8_BIT(SDIOCx->BLKGPCON, SDIOC_BLKGPCON_CR);
}

/**
 * @brief  Enable or disable read wait.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] enNewSta                The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void SDIOC_ReadWaitCmd(M4_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (Disable != enNewSta)
    {
        SET_REG8_BIT(SDIOCx->BLKGPCON, SDIOC_BLKGPCON_RWC);
    }
    else
    {
        CLEAR_REG8_BIT(SDIOCx->BLKGPCON, SDIOC_BLKGPCON_RWC);
    }
}

/**
 * @brief  Enable or disable data block gap interrupt.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] enNewSta                The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void SDIOC_BlockGapInterruptCmd(M4_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (Disable != enNewSta)
    {
        SET_REG8_BIT(SDIOCx->BLKGPCON, SDIOC_BLKGPCON_IABG);
    }
    else
    {
        CLEAR_REG8_BIT(SDIOCx->BLKGPCON, SDIOC_BLKGPCON_IABG);
    }
}

/**
 * @brief  Enable or disable interrupt.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32IntSrc               Normal and error interrupts source
 *         This parameter can be one or any combination of the following values:
 *           @arg SDIOC_NORMAL_INT_CINTSEN:     Card Interrupt
 *           @arg SDIOC_NORMAL_INT_CRMSEN:      Card Removal Interrupt
 *           @arg SDIOC_NORMAL_INT_CISTSEN:     Card Insertion Interrupt
 *           @arg SDIOC_NORMAL_INT_BRRSEN:      Buffer Read Ready Interrupt
 *           @arg SDIOC_NORMAL_INT_BWRSEN:      Buffer Write Ready Interrupt
 *           @arg SDIOC_NORMAL_INT_BGESEN:      Block Gap Event Interrupt
 *           @arg SDIOC_NORMAL_INT_TCSEN:       Transfer Complete Interrupt
 *           @arg SDIOC_NORMAL_INT_CCSEN:       Command Complete Interrupt
 *           @arg SDIOC_ERROR_INT_ACESEN:       Auto CMD12 Error Interrupt
 *           @arg SDIOC_ERROR_INT_DEBESEN:      Data End Bit Error Interrupt
 *           @arg SDIOC_ERROR_INT_DCESEN:       Data CRC Error Interrupt
 *           @arg SDIOC_ERROR_INT_DTOESEN:      Data Timeout Error Interrupt
 *           @arg SDIOC_ERROR_INT_CIESEN:       Command Index Error Interrupt
 *           @arg SDIOC_ERROR_INT_CEBESEN:      Command End Bit Error Interrupt
 *           @arg SDIOC_ERROR_INT_CCESEN:       Command CRC Error Interrupt
 *           @arg SDIOC_ERROR_INT_CTOESEN:      Command Timeout Error Interrupt
 * @param  [in] enNewSta                The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void SDIOC_IntCmd(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32IntSrc, en_functional_state_t enNewSta)
{
    uint16_t u16NormalInt;
    uint16_t u16ErrorInt;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_NORMAL_ERROR_INT(u32IntSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    u16NormalInt = (uint16_t)(u32IntSrc & 0xFFFFU);
    u16ErrorInt  = (uint16_t)((u32IntSrc >> 16U) & 0xFFFFU);

    if (Disable != enNewSta)
    {
        if (0U != u16NormalInt)
        {
            SET_REG16_BIT(SDIOCx->NORINTSGEN, u16NormalInt);
        }
        if (0U != u16ErrorInt)
        {
            SET_REG16_BIT(SDIOCx->ERRINTSGEN, u16ErrorInt);
        }
    }
    else
    {
        if (0U != u16NormalInt)
        {
            CLEAR_REG16_BIT(SDIOCx->NORINTSGEN, u16NormalInt);
        }
        if (0U != u16ErrorInt)
        {
            CLEAR_REG16_BIT(SDIOCx->ERRINTSGEN, u16ErrorInt);
        }
    }
}

/**
 * @brief  Get interrupt enable state.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32IntSrc               Normal and error interrupts source
 *         This parameter can be one or any combination of the following values:
 *           @arg SDIOC_NORMAL_INT_CINTSEN:     Card Interrupt
 *           @arg SDIOC_NORMAL_INT_CRMSEN:      Card Removal Interrupt
 *           @arg SDIOC_NORMAL_INT_CISTSEN:     Card Insertion Interrupt
 *           @arg SDIOC_NORMAL_INT_BRRSEN:      Buffer Read Ready Interrupt
 *           @arg SDIOC_NORMAL_INT_BWRSEN:      Buffer Write Ready Interrupt
 *           @arg SDIOC_NORMAL_INT_BGESEN:      Block Gap Event Interrupt
 *           @arg SDIOC_NORMAL_INT_TCSEN:       Transfer Complete Interrupt
 *           @arg SDIOC_NORMAL_INT_CCSEN:       Command Complete Interrupt
 *           @arg SDIOC_ERROR_INT_ACESEN:       Auto CMD12 Error Interrupt
 *           @arg SDIOC_ERROR_INT_DEBESEN:      Data End Bit Error Interrupt
 *           @arg SDIOC_ERROR_INT_DCESEN:       Data CRC Error Interrupt
 *           @arg SDIOC_ERROR_INT_DTOESEN:      Data Timeout Error Interrupt
 *           @arg SDIOC_ERROR_INT_CIESEN:       Command Index Error Interrupt
 *           @arg SDIOC_ERROR_INT_CEBESEN:      Command End Bit Error Interrupt
 *           @arg SDIOC_ERROR_INT_CCESEN:       Command CRC Error Interrupt
 *           @arg SDIOC_ERROR_INT_CTOESEN:      Command Timeout Error Interrupt
 * @retval An en_functional_state_t enumeration value:
 *           - Enable: The interrupt is enable
 *           - Disable: The interrupt is disable
 */
en_functional_state_t SDIOC_GetIntEnableState(const M4_SDIOC_TypeDef *SDIOCx, uint32_t u32IntSrc)
{
    uint16_t u16NormalInt;
    uint16_t u16ErrorInt;
    en_functional_state_t enIntSta = Disable;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_NORMAL_ERROR_INT(u32IntSrc));

    u16NormalInt = (uint16_t)(u32IntSrc & 0xFFFFU);
    u16ErrorInt  = (uint16_t)((u32IntSrc >> 16U) & 0xFFFFU);

    if (0U != u16NormalInt)
    {
        if (0U != (READ_REG16_BIT(SDIOCx->NORINTSGEN, u16NormalInt)))
        {
            enIntSta = Enable;
        }
    }
    if (0U != u16ErrorInt)
    {
        if (0U != (READ_REG16_BIT(SDIOCx->ERRINTSGEN, u16ErrorInt)))
        {
            enIntSta = Enable;
        }
    }

    return enIntSta;
}

/**
 * @brief  Get interrupt flag status.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32Flag                 Normal and error interrupts flag
 *         This parameter can be one or any combination the following values:
 *           @arg SDIOC_NORMAL_INT_FLAG_EI:     Error Interrupt Status
 *           @arg SDIOC_NORMAL_INT_FLAG_CINT:   Card Interrupt status
 *           @arg SDIOC_NORMAL_INT_FLAG_CRM:    Card Removal status
 *           @arg SDIOC_NORMAL_INT_FLAG_CIST:   Card Insertion status
 *           @arg SDIOC_NORMAL_INT_FLAG_BRR:    Buffer Read Ready status
 *           @arg SDIOC_NORMAL_INT_FLAG_BWR:    Buffer Write Ready status
 *           @arg SDIOC_NORMAL_INT_FLAG_BGE:    Block Gap Event status
 *           @arg SDIOC_NORMAL_INT_FLAG_TC:     Transfer Complete status
 *           @arg SDIOC_NORMAL_INT_FLAG_CC:     Command Complete status
 *           @arg SDIOC_ERROR_INT_FLAG_ACE:     Auto CMD12 Error Status
 *           @arg SDIOC_ERROR_INT_FLAG_DEBE:    Data End Bit Error status
 *           @arg SDIOC_ERROR_INT_FLAG_DCE:     Data CRC Error status
 *           @arg SDIOC_ERROR_INT_FLAG_DTOE:    Data Timeout Error status
 *           @arg SDIOC_ERROR_INT_FLAG_CIE:     Command Index Error status
 *           @arg SDIOC_ERROR_INT_FLAG_CEBE:    Command End Bit Error status
 *           @arg SDIOC_ERROR_INT_FLAG_CCE:     Command CRC Error status
 *           @arg SDIOC_ERROR_INT_FLAG_CTOE:    Command Timeout Error status
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t SDIOC_GetIntStatus(const M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;
    uint16_t u16NormalFlag;
    uint16_t u16ErrorFlag;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_GET_NORMAL_ERROR_INT_FLAG(u32Flag));

    u16NormalFlag = (uint16_t)(u32Flag & 0xFFFFU);
    u16ErrorFlag  = (uint16_t)((u32Flag >> 16U) & 0xFFFFU);

    if (0U != u16NormalFlag)
    {
        if (0U != (READ_REG16_BIT(SDIOCx->NORINTST, u16NormalFlag)))
        {
            enFlagSta = Set;
        }
    }
    if (0U != u16ErrorFlag)
    {
        if (0U != (READ_REG16_BIT(SDIOCx->ERRINTST, u16ErrorFlag)))
        {
            enFlagSta = Set;
        }
    }

    return enFlagSta;
}

/**
 * @brief  Clear interrupt flag status.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32Flag                 Normal and error interrupts flag
 *         This parameter can be one or any combination of the following values:
 *           @arg SDIOC_NORMAL_INT_FLAG_CRM:    Card Removal status
 *           @arg SDIOC_NORMAL_INT_FLAG_CIST:   Card Insertion status
 *           @arg SDIOC_NORMAL_INT_FLAG_BRR:    Buffer Read Ready status
 *           @arg SDIOC_NORMAL_INT_FLAG_BWR:    Buffer Write Ready status
 *           @arg SDIOC_NORMAL_INT_FLAG_BGE:    Block Gap Event status
 *           @arg SDIOC_NORMAL_INT_FLAG_TC:     Transfer Complete status
 *           @arg SDIOC_NORMAL_INT_FLAG_CC:     Command Complete status
 *           @arg SDIOC_ERROR_INT_FLAG_ACE:     Auto CMD12 Error Status
 *           @arg SDIOC_ERROR_INT_FLAG_DEBE:    Data End Bit Error status
 *           @arg SDIOC_ERROR_INT_FLAG_DCE:     Data CRC Error status
 *           @arg SDIOC_ERROR_INT_FLAG_DTOE:    Data Timeout Error status
 *           @arg SDIOC_ERROR_INT_FLAG_CIE:     Command Index Error status
 *           @arg SDIOC_ERROR_INT_FLAG_CEBE:    Command End Bit Error status
 *           @arg SDIOC_ERROR_INT_FLAG_CCE:     Command CRC Error status
 *           @arg SDIOC_ERROR_INT_FLAG_CTOE:    Command Timeout Error status
 * @retval None
 */
void SDIOC_ClearIntStatus(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Flag)
{
    uint16_t u16NormalFlag;
    uint16_t u16ErrorFlag;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_CLEAR_NORMAL_ERROR_INT_FLAG(u32Flag));

    u16NormalFlag = (uint16_t)(u32Flag & 0xFFFFU);
    u16ErrorFlag  = (uint16_t)((u32Flag >> 16U) & 0xFFFFU);
    if (0U != u16NormalFlag)
    {
        WRITE_REG16(SDIOCx->NORINTST, u16NormalFlag);
    }
    if (0U != u16ErrorFlag)
    {
        WRITE_REG16(SDIOCx->ERRINTST, u16ErrorFlag);
    }
}

/**
 * @brief  Enable or disable interrupt status.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32IntSrc               Normal and error interrupts source
 *         This parameter can be one or any combination of the following values:
 *           @arg SDIOC_NORMAL_INT_CINTSEN:     Card Interrupt
 *           @arg SDIOC_NORMAL_INT_CRMSEN:      Card Removal Interrupt
 *           @arg SDIOC_NORMAL_INT_CISTSEN:     Card Insertion Interrupt
 *           @arg SDIOC_NORMAL_INT_BRRSEN:      Buffer Read Ready Interrupt
 *           @arg SDIOC_NORMAL_INT_BWRSEN:      Buffer Write Ready Interrupt
 *           @arg SDIOC_NORMAL_INT_BGESEN:      Block Gap Event Interrupt
 *           @arg SDIOC_NORMAL_INT_TCSEN:       Transfer Complete Interrupt
 *           @arg SDIOC_NORMAL_INT_CCSEN:       Command Complete Interrupt
 *           @arg SDIOC_ERROR_INT_ACESEN:       Auto CMD12 Error Interrupt
 *           @arg SDIOC_ERROR_INT_DEBESEN:      Data End Bit Error Interrupt
 *           @arg SDIOC_ERROR_INT_DCESEN:       Data CRC Error Interrupt
 *           @arg SDIOC_ERROR_INT_DTOESEN:      Data Timeout Error Interrupt
 *           @arg SDIOC_ERROR_INT_CIESEN:       Command Index Error Interrupt
 *           @arg SDIOC_ERROR_INT_CEBESEN:      Command End Bit Error Interrupt
 *           @arg SDIOC_ERROR_INT_CCESEN:       Command CRC Error Interrupt
 *           @arg SDIOC_ERROR_INT_CTOESEN:      Command Timeout Error Interrupt
 * @param  [in] enNewSta                The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void SDIOC_IntStatusCmd(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32IntSrc, en_functional_state_t enNewSta)
{
    uint16_t u16NormalInt;
    uint16_t u16ErrorInt;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_NORMAL_ERROR_INT(u32IntSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    u16NormalInt = (uint16_t)(u32IntSrc & 0xFFFFU);
    u16ErrorInt  = (uint16_t)((u32IntSrc >> 16U) & 0xFFFFU);

    if (Disable != enNewSta)
    {
        if (0U != u16NormalInt)
        {
            SET_REG16_BIT(SDIOCx->NORINTSTEN, u16NormalInt);
        }
        if (0U != u16ErrorInt)
        {
            SET_REG16_BIT(SDIOCx->ERRINTSTEN, u16ErrorInt);
        }
    }
    else
    {
        if (0U != u16NormalInt)
        {
            CLEAR_REG16_BIT(SDIOCx->NORINTSTEN, u16NormalInt);
        }
        if (0U != u16ErrorInt)
        {
            CLEAR_REG16_BIT(SDIOCx->ERRINTSTEN, u16ErrorInt);
        }
    }
}

/**
 * @brief  Get Host status.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32Flag                 Host flag
 *         This parameter can be one or any combination the following values:
 *           @arg SDIOC_HOST_FLAG_CMDL:     CMD Line Level status
 *           @arg SDIOC_HOST_FLAG_DATL:     DAT[3:0] Line Level status
 *           @arg SDIOC_HOST_FLAG_DATL_D0:  DAT[0] Line Level status
 *           @arg SDIOC_HOST_FLAG_DATL_D1:  DAT[1] Line Level status
 *           @arg SDIOC_HOST_FLAG_DATL_D2:  DAT[2] Line Level status
 *           @arg SDIOC_HOST_FLAG_DATL_D3:  DAT[3] Line Level status
 *           @arg SDIOC_HOST_FLAG_WPL:      Write Protect Line Level status
 *           @arg SDIOC_HOST_FLAG_CDL:      Card Detect Line Level status
 *           @arg SDIOC_HOST_FLAG_CSS:      Device Stable Status
 *           @arg SDIOC_HOST_FLAG_CIN:      Device Inserted status
 *           @arg SDIOC_HOST_FLAG_BRE:      Data buffer full status
 *           @arg SDIOC_HOST_FLAG_BWE:      Data buffer empty status
 *           @arg SDIOC_HOST_FLAG_RTA:      Read operation status
 *           @arg SDIOC_HOST_FLAG_WTA:      Write operation status
 *           @arg SDIOC_HOST_FLAG_DA:       DAT Line transfer status
 *           @arg SDIOC_HOST_FLAG_CID:      Command Inhibit with data status
 *           @arg SDIOC_HOST_FLAG_CIC:      Command Inhibit status
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t SDIOC_GetHostStatus(const M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_GET_HOST_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(SDIOCx->PSTAT, u32Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/**
 * @brief  Get auto CMD12 error status.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u16Flag                 Auto CMD12 error flag
 *         This parameter can be one or any combination the following values:
 *           @arg SDIOC_AUTO_CMD_ERROR_FLAG_CMDE:   Command Not Issued By Auto CMD12 Error Status
 *           @arg SDIOC_AUTO_CMD_ERROR_FLAG_IE:     Auto CMD12 Index Error status
 *           @arg SDIOC_AUTO_CMD_ERROR_FLAG_EBE:    Auto CMD12 End Bit Error status
 *           @arg SDIOC_AUTO_CMD_ERROR_FLAG_CE:     Auto CMD12 CRC Error status
 *           @arg SDIOC_AUTO_CMD_ERROR_FLAG_TOE:    Auto CMD12 Timeout Error status
 *           @arg SDIOC_AUTO_CMD_ERROR_FLAG_NE:     Auto CMD12 Not Executed status
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t SDIOC_GetAutoCmdErrorStatus(const M4_SDIOC_TypeDef *SDIOCx, uint16_t u16Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_AUTO_CMD_ERROR_FLAG(u16Flag));

    if (0U != (READ_REG16_BIT(SDIOCx->ATCERRST, u16Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/**
 * @brief  Force the specified auto CMD12 error event flag.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u16CmdFlag              Auto CMD12 error flag
 *         This parameter can be one or any combination the following values:
 *           @arg SDIOC_FORCE_AUTO_CMD_ERROR_FCMDE: Force Event for Command Not Issued By Auto CMD12 Error
 *           @arg SDIOC_FORCE_AUTO_CMD_ERROR_FIE:   Force Event for Auto CMD12 Index Error
 *           @arg SDIOC_FORCE_AUTO_CMD_ERROR_FEBE:  Force Event for Auto CMD12 End Bit Error
 *           @arg SDIOC_FORCE_AUTO_CMD_ERROR_FCE:   Force Event for Auto CMD12 CRC Error
 *           @arg SDIOC_FORCE_AUTO_CMD_ERROR_FTOE:  Force Event for Auto CMD12 Timeout Error
 *           @arg SDIOC_FORCE_AUTO_CMD_ERROR_FNE:   Force Event for Auto CMD12 Not Executed
 * @retval None
 */
void SDIOC_ForceAutoCmdErrorEvent(M4_SDIOC_TypeDef *SDIOCx, uint16_t u16CmdFlag)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_FORCE_AUTO_CMD_FLAG(u16CmdFlag));

    WRITE_REG16(SDIOCx->FEA, u16CmdFlag);
}

/**
 * @brief  Force the specified error interrupt event flag.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u16IntFlag              Error interrupt flag
 *         This parameter can be one or any combination the following values:
 *           @arg SDIOC_FORCE_ERROR_INT_FACE:   Force Event for Auto CMD12 Error
 *           @arg SDIOC_FORCE_ERROR_INT_FDEBE:  Force Event for Data End Bit Error
 *           @arg SDIOC_FORCE_ERROR_INT_FDCE:   Force Event for Data CRC Error
 *           @arg SDIOC_FORCE_ERROR_INT_FDTOE:  Force Event for Data Timeout Error
 *           @arg SDIOC_FORCE_ERROR_INT_FCIE:   Force Event for Command Index Error
 *           @arg SDIOC_FORCE_ERROR_INT_FCEBE:  Force Event for Command End Bit Error
 *           @arg SDIOC_FORCE_ERROR_INT_FCCE:   Force Event for Command CRC Error
 *           @arg SDIOC_FORCE_ERROR_INT_FCTOE:  Force Event for Command Timeout Error
 * @retval None
 */
void SDIOC_ForceErrorInterruptEvent(M4_SDIOC_TypeDef *SDIOCx, uint16_t u16IntFlag)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_FORCE_ERROR_INT_FLAG(u16IntFlag));

    WRITE_REG16(SDIOCx->FEE, u16IntFlag);
}

/**
 * @brief  Send the Go Idle State command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD0_GoIdleState(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        *pu32ErrSta              = SDMMC_ERROR_NONE;
        stcCmdInit.u32Argument   = 0UL;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD0_GO_IDLE_STATE;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_NO;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdError(SDIOCx);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Send CID command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD2_AllSendCID(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = 0UL;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD2_ALL_SEND_CID;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R2;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
         if (Ok == enRet)
         {
             enRet = SDMMC_GetCmdResp2(SDIOCx, pu32ErrSta);
         }
    }

    return enRet;
}

/**
 * @brief  Send the command for asking the card to publish a new relative address(RCA).
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [out] pu16RCA                Pointer to the new RCA value
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu16RCA == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD3_SendRelativeAddr(M4_SDIOC_TypeDef *SDIOCx, uint16_t *pu16RCA, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if ((NULL == pu16RCA) || (NULL == pu32ErrSta))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = 0UL;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD3_SEND_RELATIVE_ADDR;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp6(SDIOCx, pu16RCA, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Checks switchable function and switch card function.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32Argument             Argument used for the command.
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD6_SwitchFunc(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Argument, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;
    uint32_t u32SdMode;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument = u32Argument;
        stcCmdInit.u16CmdIndex = SDIOC_CMD6_SWITCH_FUNC;
        stcCmdInit.u16CmdType  = SDIOC_CMD_TYPE_NORMAL;
        u32SdMode              = SDIOC_GetMode(SDIOCx);
        if (SDIOC_MODE_SD != u32SdMode)   /* MMC mode */
        {
            stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
            stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1B_R5B;
        }
        else
        {
            stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_ENABLE;
            stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        }
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            if (SDIOC_MODE_SD != u32SdMode)   /* MMC mode */
            {
                enRet = SDMMC_GetCmdResp1Busy(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
            }
            else
            {
                enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
            }
        }
    }

    return enRet;
}

/**
 * @brief  Send the Select Deselect command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32RCA                  Relative Card Address(RCA)
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD7_SelectDeselectCard(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32RCA, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32RCA;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD7_SELECT_DESELECT_CARD;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1B_R5B;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1Busy(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Interface Condition command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD8_SendInterfaceCond(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;
    uint32_t u32SdMode;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Argument: - [31:12]: Reserved (shall be set to '0')
        - [11:8]: Supply Voltage (VHS) 0x1 (Range: 2.7-3.6 V)
        - [7:0]: Check Pattern (recommended 0xAA) */
        stcCmdInit.u32Argument = SDMMC_CMD8_CHECK_PATTERN;
        stcCmdInit.u16CmdIndex = SDIOC_CMD8_SEND_IF_COND;
        stcCmdInit.u16CmdType  = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16RespType = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        u32SdMode              = SDIOC_GetMode(SDIOCx);
        if (SDIOC_MODE_SD != u32SdMode)   /* MMC mode */
        {
            stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_ENABLE;
        }
        else
        {
            stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        }
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            if (SDIOC_MODE_SD != u32SdMode)   /* MMC mode */
            {
                enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
            }
            else
            {
                enRet = SDMMC_GetCmdResp7(SDIOCx, pu32ErrSta);
            }
        }
    }

    return enRet;
}

/**
 * @brief  Send the Send CSD command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32RCA                  Relative Card Address(RCA)
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD9_SendCSD(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32RCA, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32RCA;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD9_SEND_CSD;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R2;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
         if (Ok == enRet)
         {
             enRet = SDMMC_GetCmdResp2(SDIOCx, pu32ErrSta);
         }
    }

    return enRet;
}

/**
 * @brief  Send the Stop Transfer command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD12_StopTransmission(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = 0UL;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD12_STOP_TRANSMISSION;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1B_R5B;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1Busy(SDIOCx, SDMMC_CMD_TIMEOUT * 1000UL, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Status command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32RCA                  Relative Card Address(RCA)
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD13_SendStatus(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32RCA, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32RCA;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD13_SEND_STATUS;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Data Block Lenght command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32BlockLen             Block length
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD16_SetBlockLength(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32BlockLen, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32BlockLen;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD16_SET_BLOCKLEN;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Read Single Block command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32ReadAddr             Data address
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD17_ReadSingleBlock(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32ReadAddr, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32ReadAddr;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD17_READ_SINGLE_BLOCK;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_ENABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Read Multi Block command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32ReadAddr             Data address
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD18_ReadMultipleBlock(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32ReadAddr, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32ReadAddr;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD18_READ_MULTIPLE_BLOCK;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_ENABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Write Single Block command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32WriteAddr            Data address
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD24_WriteSingleBlock(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32WriteAddr, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32WriteAddr;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD24_WRITE_SINGLE_BLOCK;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_ENABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Write Multi Block command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32WriteAddr            Data address
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD25_WriteMultipleBlock(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32WriteAddr, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32WriteAddr;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD25_WRITE_MULTIPLE_BLOCK;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_ENABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Start Address Erase command for SD and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32StartAddr            The start address will be erased
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD32_EraseBlockStartAddr(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32StartAddr, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32StartAddr;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD32_ERASE_WR_BLK_START;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the End Address Erase command for SD and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32EndAddr              The end address will be erased
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD33_EraseBlockEndAddr(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32EndAddr, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32EndAddr;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD33_ERASE_WR_BLK_END;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Erase command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD38_Erase(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = 0UL;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD38_ERASE;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1B_R5B;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1Busy(SDIOCx, SDMMC_MAX_ERASE_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Application command to verify that that the next command
 *         is an application specific command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32Argument             Argument used for the command.
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD55_AppCmd(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Argument, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32Argument;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD55_APP_CMD;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Bus Width command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32BusWidth             The data bus width
 *         This parameter can be one of the following values:
 *           @arg SDMMC_SCR_BUS_WIDTH_1BIT: 1 bit bus
 *           @arg SDMMC_SCR_BUS_WIDTH_4BIT: 4 bits bus
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_ACMD6_SetBusWidth(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32BusWidth, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32BusWidth;
        stcCmdInit.u16CmdIndex   = SDIOC_ACMD6_SET_BUS_WIDTH;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Status register command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_ACMD13_SendStatus(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = 0UL;
        stcCmdInit.u16CmdIndex   = SDIOC_ACMD13_SD_STATUS;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_ENABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the command asking the accessed card to send its operating condition register(OCR).
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32Argument             Argument used for the command.
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_ACMD41_SendOperatCond(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Argument, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32Argument | SDMMC_ACMD41_VOLTAGE_WINDOW;
        stcCmdInit.u16CmdIndex   = SDIOC_ACMD41_SD_APP_OP_COND;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R3_R4;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp3(SDIOCx, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Send SCR command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_ACMD51_SendSCR(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = 0UL;
        stcCmdInit.u16CmdIndex   = SDIOC_ACMD51_SEND_SCR;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_ENABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Sends host capacity support information command.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32Argument             Argument used for the command.
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD1_SendOperatCond(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Argument, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32Argument;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD1_SEND_OP_COND;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R3_R4;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp3(SDIOCx, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the Start Address Erase command and check the response
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32StartAddr            The start address will be erased
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD35_EraseGroupStartAddr(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32StartAddr, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32StartAddr;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD35_ERASE_GRP_START;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Send the End Address Erase command and check the response
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32EndAddr              The end address will be erased
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorInvalidParameter: SDIOCx == NULL or pu32ErrSta == NULL
 *           - ErrorTimeout: Wait timeout
 */
en_result_t SDMMC_CMD36_EraseGroupEndAddr(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32EndAddr, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    stc_sdioc_cmd_init_t stcCmdInit;

    if (NULL == pu32ErrSta)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        stcCmdInit.u32Argument   = u32EndAddr;
        stcCmdInit.u16CmdIndex   = SDIOC_CMD36_ERASE_GRP_END;
        stcCmdInit.u16CmdType    = SDIOC_CMD_TYPE_NORMAL;
        stcCmdInit.u16DataLineEn = SDIOC_DATA_LINE_DISABLE;
        stcCmdInit.u16RespType   = SDIOC_RESOPNE_TYPE_R1_R5_R6_R7;
        enRet = SDIOC_SendCommand(SDIOCx, &stcCmdInit);
        /* Check for error conditions */
        if (Ok == enRet)
        {
            enRet = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrSta);
        }
    }

    return enRet;
}

/**
 * @brief  Wait for command response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32CheckFlag            Check flags
 *         This parameter can be one or any combination the following values:
 *           @arg SDIOC_NORMAL_INT_FLAG_CC:     Command Complete status
 *           @arg SDIOC_ERROR_INT_FLAG_CIE:     Command Index Error status
 *           @arg SDIOC_ERROR_INT_FLAG_CEBE:    Command End Bit Error status
 *           @arg SDIOC_ERROR_INT_FLAG_CCE:     Command CRC Error status
 *           @arg SDIOC_ERROR_INT_FLAG_CTOE:    Command Timeout Error status
 * @param  [in] u32Timeout              Timeout time(ms) for waiting SDIOC
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: The response is normal received
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorTimeout: Wait timeout
 */
static en_result_t SDMMC_WaitResponse(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32CheckFlag, uint32_t u32Timeout, uint32_t *pu32ErrSta)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;
    uint32_t u32Temp;

    *pu32ErrSta = 0UL;
    /* The u32Timeout is expressed in ms */
    u32Count = u32Timeout * (HCLK_VALUE / 20000UL);
    while (Reset == SDIOC_GetIntStatus(SDIOCx, u32CheckFlag))
    {
        if (0UL == u32Count)
        {
            enRet = ErrorTimeout;
            break;
        }
        u32Count--;
    }

    if (Ok == enRet)
    {
        enRet = Error;
        u32Temp = CLEAR_REG32_BIT(u32CheckFlag, SDIOC_NORMAL_INT_FLAG_CC);
        if (Reset == SDIOC_GetIntStatus(SDIOCx, u32Temp))
        {
            /* No error flag set */
            *pu32ErrSta = SDMMC_ERROR_NONE;
            SDIOC_ClearIntStatus(SDIOCx, SDIOC_ERROR_INT_STATIC_FLAGS);
            enRet = Ok;
        }
        else if ((Reset != SDIOC_GetIntStatus(SDIOCx, SDIOC_ERROR_INT_FLAG_CIE)) &&
                 (SDIOC_ERROR_INT_FLAG_CIE == (u32CheckFlag & SDIOC_ERROR_INT_FLAG_CIE)))
        {
            *pu32ErrSta = SDMMC_ERROR_CMD_INDEX;
            SDIOC_ClearIntStatus(SDIOCx, SDIOC_ERROR_INT_FLAG_CIE);
        }
        else if ((Reset != SDIOC_GetIntStatus(SDIOCx, SDIOC_ERROR_INT_FLAG_CEBE)) &&
                 (SDIOC_ERROR_INT_FLAG_CEBE == (u32CheckFlag & SDIOC_ERROR_INT_FLAG_CEBE)))
        {
            *pu32ErrSta = SDMMC_ERROR_CMD_STOP_BIT;
            SDIOC_ClearIntStatus(SDIOCx, SDIOC_ERROR_INT_FLAG_CEBE);
        }
        else if ((Reset != SDIOC_GetIntStatus(SDIOCx, SDIOC_ERROR_INT_FLAG_CCE)) &&
                 (SDIOC_ERROR_INT_FLAG_CCE == (u32CheckFlag & SDIOC_ERROR_INT_FLAG_CCE)))
        {
            *pu32ErrSta = SDMMC_ERROR_CMD_CRC_FAIL;
            SDIOC_ClearIntStatus(SDIOCx, SDIOC_ERROR_INT_FLAG_CCE);
        }
        else
        {
            *pu32ErrSta = SDMMC_ERROR_CMD_TIMEOUT;
            SDIOC_ClearIntStatus(SDIOCx, SDIOC_ERROR_INT_FLAG_CTOE);
        }
    }

    return enRet;
}

/**
 * @brief  Checks for error conditions for no response command.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @retval An en_result_t enumeration value:
 *           - Ok: Command send completed
 *           - ErrorTimeout: Wait timeout
 */
static en_result_t SDMMC_GetCmdError(M4_SDIOC_TypeDef *SDIOCx)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;

    /* The SDMMC_CMD_TIMEOUT is expressed in ms */
    u32Count = SDMMC_CMD_TIMEOUT * (HCLK_VALUE / 20000UL);
    while (Reset == SDIOC_GetIntStatus(SDIOCx, SDIOC_NORMAL_INT_FLAG_CC))
    {
        if (0UL == u32Count)
        {
            enRet = ErrorTimeout;
            break;
        }
        u32Count--;
    }

    if (Ok == enRet)
    {
        SDIOC_ClearIntStatus(SDIOCx, SDIOC_ERROR_INT_STATIC_FLAGS);
    }

    return enRet;
}

/**
 * @brief  Checks for error conditions for R1 response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32Timeout              Timeout time(ms) for waiting SDIOC
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: The response is normal received
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorTimeout: Wait timeout
 */
static en_result_t SDMMC_GetCmdResp1(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Timeout, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    uint32_t u32RespVal;

    enRet = SDMMC_WaitResponse(SDIOCx,
                               (SDIOC_NORMAL_INT_FLAG_CC  | SDIOC_ERROR_INT_FLAG_CIE | SDIOC_ERROR_INT_FLAG_CEBE |
                                SDIOC_ERROR_INT_FLAG_CCE  | SDIOC_ERROR_INT_FLAG_CTOE), u32Timeout, pu32ErrSta);

    if (Ok == enRet)
    {
        /* Fetch has received a response. */
        (void)SDIOC_GetResponse(SDIOCx, SDIOC_RESPONSE_REG_BIT0_31, &u32RespVal);
        if (0UL != (u32RespVal & SDMMC_CARD_ERROR_BITS_MASK))
        {
            *pu32ErrSta = u32RespVal & SDMMC_CARD_ERROR_BITS_MASK;
            enRet = Error;
        }
    }

    return enRet;
}

/**
 * @brief  Checks for error conditions for R1 response with busy.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [in] u32Timeout              Timeout time(ms) for waiting SDIOC
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: The response is normal received
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorTimeout: Wait timeout
 */
static en_result_t SDMMC_GetCmdResp1Busy(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Timeout, uint32_t *pu32ErrSta)
{
    __IO uint32_t u32Count;
    en_result_t enRet;
    uint32_t u32RespVal;

    enRet = SDMMC_WaitResponse(SDIOCx,
                               (SDIOC_NORMAL_INT_FLAG_CC  | SDIOC_ERROR_INT_FLAG_CIE | SDIOC_ERROR_INT_FLAG_CEBE |
                                SDIOC_ERROR_INT_FLAG_CCE  | SDIOC_ERROR_INT_FLAG_CTOE), u32Timeout, pu32ErrSta);

    if (Ok == enRet)
    {
        /* Fetch has received a response. */
        (void)SDIOC_GetResponse(SDIOCx, SDIOC_RESPONSE_REG_BIT0_31, &u32RespVal);
        if (0UL != (u32RespVal & SDMMC_CARD_ERROR_BITS_MASK))
        {
            *pu32ErrSta = u32RespVal & SDMMC_CARD_ERROR_BITS_MASK;
            enRet = Error;
        }
        else
        {
            /* Wait for busy status to release */
            u32Count = u32Timeout * (HCLK_VALUE / 20000UL);
            while (Reset == SDIOC_GetHostStatus(SDIOCx, SDIOC_HOST_FLAG_DATL_D0))
            {
                if (0UL == u32Count)
                {
                    enRet = ErrorTimeout;
                    break;
                }
                u32Count--;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Checks for error conditions for R2(CID or CSD) response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: The response is normal received
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorTimeout: Wait timeout
 */
static en_result_t SDMMC_GetCmdResp2(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta)
{
    return SDMMC_WaitResponse(SDIOCx,
                              (SDIOC_NORMAL_INT_FLAG_CC | SDIOC_ERROR_INT_FLAG_CEBE | SDIOC_ERROR_INT_FLAG_CCE |
                               SDIOC_ERROR_INT_FLAG_CTOE), SDMMC_CMD_TIMEOUT, pu32ErrSta);
}

/**
 * @brief  Checks for error conditions for R3(OCR) response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: The response is normal received
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorTimeout: Wait timeout
 */
static en_result_t SDMMC_GetCmdResp3(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta)
{
    return SDMMC_WaitResponse(SDIOCx,
                              (SDIOC_NORMAL_INT_FLAG_CC | SDIOC_ERROR_INT_FLAG_CEBE | SDIOC_ERROR_INT_FLAG_CTOE),
                              SDMMC_CMD_TIMEOUT, pu32ErrSta);
}

/**
 * @brief  Checks for error conditions for R6(RCA) response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [out] pu16RCA                Pointer to a value of device RCA
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: The response is normal received
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorTimeout: Wait timeout
 */
static en_result_t SDMMC_GetCmdResp6(M4_SDIOC_TypeDef *SDIOCx, uint16_t *pu16RCA, uint32_t *pu32ErrSta)
{
    en_result_t enRet;
    uint32_t u32RespVal;

    enRet = SDMMC_WaitResponse(SDIOCx,
                               (SDIOC_NORMAL_INT_FLAG_CC  | SDIOC_ERROR_INT_FLAG_CIE | SDIOC_ERROR_INT_FLAG_CEBE |
                                SDIOC_ERROR_INT_FLAG_CCE  | SDIOC_ERROR_INT_FLAG_CTOE), SDMMC_CMD_TIMEOUT, pu32ErrSta);

    if (Ok == enRet)
    {
        enRet = Error;
        /* Fetch has received a response. */
        (void)SDIOC_GetResponse(SDIOCx, SDIOC_RESPONSE_REG_BIT0_31, &u32RespVal);
        if (0UL == (u32RespVal & (SDMMC_R6_GENERAL_UNKNOWN_ERROR | SDMMC_R6_ILLEGAL_CMD | SDMMC_R6_COM_CRC_FAILED)))
        {
            enRet = Ok;
            *pu16RCA = (uint16_t)((u32RespVal >> 16U) & 0xFFFFUL);
        }
        else if (SDMMC_R6_GENERAL_UNKNOWN_ERROR == (u32RespVal & SDMMC_R6_GENERAL_UNKNOWN_ERROR))
        {
            *pu32ErrSta = SDMMC_ERROR_GENERAL_UNKNOWN_ERR;
        }
        else if (SDMMC_R6_ILLEGAL_CMD == (u32RespVal & SDMMC_R6_ILLEGAL_CMD))
        {
            *pu32ErrSta = SDMMC_ERROR_ILLEGAL_CMD;
        }
        else
        {
            *pu32ErrSta = SDMMC_ERROR_COM_CRC_FAILED;
        }
    }

    return enRet;
}

/**
 * @brief  Checks for error conditions for R7 response.
 * @param  [in] SDIOCx                  Pointer to SDIOC instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_SDIOC1:            SDIOC unit 1 instance register base
 *           @arg M4_SDIOC2:            SDIOC unit 2 instance register base
 * @param  [out] pu32ErrSta             Pointer to the error state value
 * @retval An en_result_t enumeration value:
 *           - Ok: The response is normal received
 *           - Error: Refer to pu32ErrSta for the reason of error
 *           - ErrorTimeout: Wait timeout
 */
static en_result_t SDMMC_GetCmdResp7(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta)
{
    return SDMMC_WaitResponse(SDIOCx,
                              (SDIOC_NORMAL_INT_FLAG_CC  | SDIOC_ERROR_INT_FLAG_CIE | SDIOC_ERROR_INT_FLAG_CEBE |
                               SDIOC_ERROR_INT_FLAG_CCE  | SDIOC_ERROR_INT_FLAG_CTOE), SDMMC_CMD_TIMEOUT, pu32ErrSta);
}

/**
 * @}
 */

#endif /* DDL_SDIOC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
