/**
 *******************************************************************************
 * @file  hc32_ll_sdioc.c
 * @brief This file provides firmware functions to manage the Secure Digital
 *        Input and Output Controller(SDIOC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-09-30       CDT             Modify response type of MMC CMD3
                                    Rename function SDMMC_ACMD41_SendOperatCond to SDMMC_ACMD41_SendOperateCond
                                    Rename function SDMMC_CMD1_SendOperatCond to SDMMC_CMD1_SendOperateCond
                                    Optimize SDIOC_GetMode function
                                    Support CMD5/CMD52/CMD53
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
#include "hc32_ll_sdioc.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_SDIOC SDIOC
 * @brief SDIOC Driver Library
 * @{
 */

#if (LL_SDIOC_ENABLE == DDL_ON)

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

/* CMD52 arguments field shift */
#define SDIO_CMD52_ARG_REG_ADDR_SHIFT           (9U)
#define SDIO_CMD52_ARG_FUNC_SHIFT               (28U)

/* CMD53 arguments field shift */
#define SDIO_CMD53_ARG_REG_ADDR_SHIFT           (9U)
#define SDIO_CMD53_ARG_FUNC_SHIFT               (28U)

/* Masks for R6 Response */
#define SDMMC_R6_GEN_UNKNOWN_ERR                (0x00002000UL)
#define SDMMC_R6_ILLEGAL_CMD                    (0x00004000UL)
#define SDMMC_R6_COM_CRC_FAIL                   (0x00008000UL)

/* SDMMC command parameters */
#define SDMMC_CMD8_CHECK_PATTERN                (0x000001AAUL)
/* 3.2V-3.3V */
#define SDMMC_ACMD41_VOLT_WIN                   (0x80100000UL)

/* Command send and response timeout(ms) */
#define SDMMC_CMD_TIMEOUT                       (5000UL)
/* Max erase Timeout 60s */
#define SDMMC_MAX_ERASE_TIMEOUT                 (60000UL)
/* SDIOC software reset timeout(ms) */
#define SDIOC_SW_RST_TIMEOUT                    (50UL)

/* SDIOC NORINTSGEN register Mask */
#define SDIOC_NORINTSGEN_CLR_MASK               (0x01F7U)
/* SDIOC ERRINTSGEN register Mask */
#define SDIOC_ERRINTSGEN_CLR_MASK               (0x017FU)

/*!< Get the specified register address of the specified SDIOC unit */
#define SDIOC_ARG_ADDR(__UNIT__)                (__IO uint32_t*)((uint32_t)(&((__UNIT__)->ARG0)))
#define SDIOC_BUF_ADDR(__UNIT__)                (__IO uint32_t*)((uint32_t)(&((__UNIT__)->BUF0)))
#define SDIOC_RESP_ADDR(__UNIT__, __RESP__)     (__IO uint32_t*)((uint32_t)(&((__UNIT__)->RESP0)) + (__RESP__))

/**
 * @defgroup SDIOC_Check_Parameters_Validity SDIOC Check Parameters Validity
 * @{
 */
#define IS_SDIOC_UNIT(x)                                                       \
(   ((x) == CM_SDIOC1)                          ||                             \
    ((x) == CM_SDIOC2))

#define IS_SDIOC_MD(x)                                                         \
(   ((x) == SDIOC_MD_SD)                        ||                             \
    ((x) == SDIOC_MD_MMC))

#define IS_SDIOC_CARD_DETECT_WAY(x)                                            \
(   ((x) == SDIOC_CARD_DETECT_CD_PIN_LVL)       ||                             \
    ((x) == SDIOC_CARD_DETECT_TEST_SIGNAL))

#define IS_SDIOC_CARD_DETECT_TEST_LEVEL(x)                                     \
(   ((x) == SDIOC_CARD_DETECT_TEST_LVL_LOW)     ||                             \
    ((x) == SDIOC_CARD_DETECT_TEST_LVL_HIGH))

#define IS_SDIOC_SPEED_MD(x)                                                   \
(   ((x) == SDIOC_SPEED_MD_NORMAL)              ||                             \
    ((x) == SDIOC_SPEED_MD_HIGH))

#define IS_SDIOC_BUS_WIDTH(x)                                                  \
(   ((x) == SDIOC_BUS_WIDTH_1BIT)               ||                             \
    ((x) == SDIOC_BUS_WIDTH_4BIT)               ||                             \
    ((x) == SDIOC_BUS_WIDTH_8BIT))

#define IS_SDIOC_CLK_DIV(x)                                                    \
(   ((x) == SDIOC_CLK_DIV1)                     ||                             \
    ((x) == SDIOC_CLK_DIV2)                     ||                             \
    ((x) == SDIOC_CLK_DIV4)                     ||                             \
    ((x) == SDIOC_CLK_DIV8)                     ||                             \
    ((x) == SDIOC_CLK_DIV16)                    ||                             \
    ((x) == SDIOC_CLK_DIV32)                    ||                             \
    ((x) == SDIOC_CLK_DIV64)                    ||                             \
    ((x) == SDIOC_CLK_DIV128)                   ||                             \
    ((x) == SDIOC_CLK_DIV256))

#define IS_SDIOC_CMD_TYPE(x)                                                   \
(   ((x) == SDIOC_CMD_TYPE_NORMAL)              ||                             \
    ((x) == SDIOC_CMD_TYPE_SUSPEND)             ||                             \
    ((x) == SDIOC_CMD_TYPE_RESUME)              ||                             \
    ((x) == SDIOC_CMD_TYPE_ABORT))

#define IS_SDIOC_DATA_LINE(x)                                                  \
(   ((x) == SDIOC_DATA_LINE_DISABLE)            ||                             \
    ((x) == SDIOC_DATA_LINE_ENABLE))

#define IS_SDIOC_TRANS_DIR(x)                                                  \
(   ((x) == SDIOC_TRANS_DIR_TO_CARD)            ||                             \
    ((x) == SDIOC_TRANS_DIR_TO_HOST))

#define IS_SDIOC_AUTO_SEND_CMD12(x)                                            \
(   ((x) == SDIOC_AUTO_SEND_CMD12_DISABLE)      ||                             \
    ((x) == SDIOC_AUTO_SEND_CMD12_ENABLE))

#define IS_SDIOC_TRANS_MD(x)                                                   \
(   ((x) == SDIOC_TRANS_MD_SINGLE)              ||                             \
    ((x) == SDIOC_TRANS_MD_INFINITE)            ||                             \
    ((x) == SDIOC_TRANS_MD_MULTI)               ||                             \
    ((x) == SDIOC_TRANS_MD_STOP_MULTI))

#define IS_SDIOC_DATA_TIMEOUT_TIME(x)           ((x) <= SDIOC_DATA_TIMEOUT_CLK_2E27)

#define IS_SDIOC_RESP_REG(x)                                                   \
(   ((x) == SDIOC_RESP_REG_BIT0_31)             ||                             \
    ((x) == SDIOC_RESP_REG_BIT32_63)            ||                             \
    ((x) == SDIOC_RESP_REG_BIT64_95)            ||                             \
    ((x) == SDIOC_RESP_REG_BIT96_127))

#define IS_SDIOC_SW_RST_TYPE(x)                                                \
(   ((x) == SDIOC_SW_RST_DATA_LINE)             ||                             \
    ((x) == SDIOC_SW_RST_CMD_LINE)              ||                             \
    ((x) == SDIOC_SW_RST_ALL))

#define IS_SDIOC_OUTPUT_CLK_FREQ(x)                                            \
(   ((x) == SDIOC_OUTPUT_CLK_FREQ_400K)         ||                             \
    ((x) == SDIOC_OUTPUT_CLK_FREQ_25M)          ||                             \
    ((x) == SDIOC_OUTPUT_CLK_FREQ_26M)          ||                             \
    ((x) == SDIOC_OUTPUT_CLK_FREQ_50M)          ||                             \
    ((x) == SDIOC_OUTPUT_CLK_FREQ_52M))

#define IS_SDIOC_GET_HOST_FLAG(x)                                              \
(   ((x) != 0UL)                                &&                             \
    (((x) | SDIOC_HOST_FLAG_ALL) == SDIOC_HOST_FLAG_ALL))

#define IS_SDIOC_GET_INT_FLAG(x)                                               \
(   ((x) != 0UL)                                &&                             \
    (((x) | SDIOC_INT_FLAG_ALL) == SDIOC_INT_FLAG_ALL))

#define IS_SDIOC_CLR_INT_FLAG(x)                                               \
(   ((x) != 0UL)                                &&                             \
    (((x) | SDIOC_INT_FLAG_CLR_ALL) == SDIOC_INT_FLAG_CLR_ALL))

#define IS_SDIOC_INT(x)                                                        \
(   ((x) != 0UL)                                &&                             \
    (((x) | SDIOC_INT_ALL) == SDIOC_INT_ALL))

#define IS_SDIOC_AUTO_CMD_ERR_FLAG(x)                                          \
(   ((x) != 0UL)                                &&                             \
    (((x) | SDIOC_AUTO_CMD_ERR_FLAG_ALL) == SDIOC_AUTO_CMD_ERR_FLAG_ALL))

#define IS_SDIOC_FORCE_AUTO_CMD_ERR(x)                                         \
(   ((x) != 0UL)                                &&                             \
    (((x) | SDIOC_FORCE_AUTO_CMD_ERR_ALL) == SDIOC_FORCE_AUTO_CMD_ERR_ALL))

#define IS_SDIOC_FORCE_ERR_INT(x)                                              \
(   ((x) != 0UL)                                &&                             \
    (((x) | SDIOC_FORCE_ERR_INT_ALL) == SDIOC_FORCE_ERR_INT_ALL))

#define IS_SDIOC_RESP_TYPE(x)                                                  \
(   ((x) == SDIOC_RESP_TYPE_NO)                 ||                             \
    ((x) == SDIOC_RESP_TYPE_R2)                 ||                             \
    ((x) == SDIOC_RESP_TYPE_R3_R4)              ||                             \
    ((x) == SDIOC_RESP_TYPE_R1_R5_R6_R7)        ||                             \
    ((x) == SDIOC_RESP_TYPE_R1B_R5B))

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

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup SDIOC_Global_Functions SDIOC Global Functions
 * @{
 */

/**
 * @brief  Wait for command response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32CheckFlag            Check flags
 *         This parameter can be one or any combination the following values:
 *           @arg SDIOC_INT_FLAG_CC:    Command Complete status
 *           @arg SDIOC_INT_FLAG_CIE:   Command Index error status
 *           @arg SDIOC_INT_FLAG_CEBE:  Command End Bit error status
 *           @arg SDIOC_INT_FLAG_CCE:   Command CRC error status
 *           @arg SDIOC_INT_FLAG_CTOE:  Command Timeout error status
 * @param  [in] u32Timeout              Timeout time(ms) for waiting SDIOC
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: The response is normal received
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
static int32_t SDMMC_WaitResponse(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32CheckFlag,
                                  uint32_t u32Timeout, uint32_t *pu32ErrStatus)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;
    uint32_t u32Temp;

    *pu32ErrStatus = 0UL;
    /* The u32Timeout is expressed in ms */
    u32Count = u32Timeout * (HCLK_VALUE / 20000UL);
    while (RESET == SDIOC_GetIntStatus(SDIOCx, u32CheckFlag)) {
        if (0UL == u32Count) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
        u32Count--;
    }

    if (LL_OK == i32Ret) {
        i32Ret = LL_ERR;
        u32Temp = CLR_REG32_BIT(u32CheckFlag, SDIOC_INT_FLAG_CC);
        if (RESET == SDIOC_GetIntStatus(SDIOCx, u32Temp)) {
            /* No error flag set */
            *pu32ErrStatus = SDMMC_ERR_NONE;
            SDIOC_ClearIntStatus(SDIOCx, SDIOC_INT_STATIC_FLAGS);
            i32Ret = LL_OK;
        } else if ((RESET != SDIOC_GetIntStatus(SDIOCx, SDIOC_INT_FLAG_CIE)) &&
                   (SDIOC_INT_FLAG_CIE == (u32CheckFlag & SDIOC_INT_FLAG_CIE))) {
            *pu32ErrStatus = SDMMC_ERR_CMD_INDEX;
            SDIOC_ClearIntStatus(SDIOCx, SDIOC_INT_FLAG_CIE);
        } else if ((RESET != SDIOC_GetIntStatus(SDIOCx, SDIOC_INT_FLAG_CEBE)) &&
                   (SDIOC_INT_FLAG_CEBE == (u32CheckFlag & SDIOC_INT_FLAG_CEBE))) {
            *pu32ErrStatus = SDMMC_ERR_CMD_STOP_BIT;
            SDIOC_ClearIntStatus(SDIOCx, SDIOC_INT_FLAG_CEBE);
        } else if ((RESET != SDIOC_GetIntStatus(SDIOCx, SDIOC_INT_FLAG_CCE)) &&
                   (SDIOC_INT_FLAG_CCE == (u32CheckFlag & SDIOC_INT_FLAG_CCE))) {
            *pu32ErrStatus = SDMMC_ERR_CMD_CRC_FAIL;
            SDIOC_ClearIntStatus(SDIOCx, SDIOC_INT_FLAG_CCE);
        } else {
            *pu32ErrStatus = SDMMC_ERR_CMD_TIMEOUT;
            SDIOC_ClearIntStatus(SDIOCx, SDIOC_INT_FLAG_CTOE);
        }
    }

    return i32Ret;
}

/**
 * @brief  Checks for error conditions for no response command.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
static int32_t SDMMC_GetCmdError(CM_SDIOC_TypeDef *SDIOCx)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;

    /* The SDMMC_CMD_TIMEOUT is expressed in ms */
    u32Count = SDMMC_CMD_TIMEOUT * (HCLK_VALUE / 20000UL);
    while (RESET == SDIOC_GetIntStatus(SDIOCx, SDIOC_INT_FLAG_CC)) {
        if (0UL == u32Count) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
        u32Count--;
    }
    if (LL_OK == i32Ret) {
        SDIOC_ClearIntStatus(SDIOCx, SDIOC_INT_STATIC_FLAGS);
    }

    return i32Ret;
}

/**
 * @brief  Checks for error conditions for R1 response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32Timeout              Timeout time(ms) for waiting SDIOC
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: The response is normal received
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
static int32_t SDMMC_GetCmdResp1(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32Timeout, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    uint32_t u32RespVal;

    i32Ret = SDMMC_WaitResponse(SDIOCx, (SDIOC_INT_FLAG_CC  | SDIOC_INT_FLAG_CIE | SDIOC_INT_FLAG_CEBE |
                                         SDIOC_INT_FLAG_CCE | SDIOC_INT_FLAG_CTOE), u32Timeout, pu32ErrStatus);
    if (LL_OK == i32Ret) {
        /* Fetch has received a response. */
        (void)SDIOC_GetResponse(SDIOCx, SDIOC_RESP_REG_BIT0_31, &u32RespVal);
        if (0UL != (u32RespVal & SDMMC_ERR_BITS_MASK)) {
            *pu32ErrStatus = u32RespVal & SDMMC_ERR_BITS_MASK;
            i32Ret = LL_ERR;
        }
    }

    return i32Ret;
}

/**
 * @brief  Checks for error conditions for R1 response with busy.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32Timeout              Timeout time(ms) for waiting SDIOC
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: The response is normal received
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
static int32_t SDMMC_GetCmdResp1Busy(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32Timeout, uint32_t *pu32ErrStatus)
{
    __IO uint32_t u32Count;
    int32_t i32Ret;
    uint32_t u32RespVal;

    i32Ret = SDMMC_WaitResponse(SDIOCx, (SDIOC_INT_FLAG_CC  | SDIOC_INT_FLAG_CIE | SDIOC_INT_FLAG_CEBE |
                                         SDIOC_INT_FLAG_CCE | SDIOC_INT_FLAG_CTOE), u32Timeout, pu32ErrStatus);
    if (LL_OK == i32Ret) {
        /* Fetch has received a response. */
        (void)SDIOC_GetResponse(SDIOCx, SDIOC_RESP_REG_BIT0_31, &u32RespVal);
        if (0UL != (u32RespVal & SDMMC_ERR_BITS_MASK)) {
            *pu32ErrStatus = u32RespVal & SDMMC_ERR_BITS_MASK;
            i32Ret = LL_ERR;
        } else {
            /* Wait for busy status to release */
            u32Count = u32Timeout * (HCLK_VALUE / 20000UL);
            while (RESET == SDIOC_GetHostStatus(SDIOCx, SDIOC_HOST_FLAG_DATL_D0)) {
                if (0UL == u32Count) {
                    i32Ret = LL_ERR_TIMEOUT;
                    break;
                }
                u32Count--;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Checks for error conditions for R2(CID or CSD) response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: The response is normal received
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
static int32_t SDMMC_GetCmdResp2(CM_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrStatus)
{
    return SDMMC_WaitResponse(SDIOCx, (SDIOC_INT_FLAG_CC | SDIOC_INT_FLAG_CEBE | SDIOC_INT_FLAG_CCE |
                                       SDIOC_INT_FLAG_CTOE), SDMMC_CMD_TIMEOUT, pu32ErrStatus);
}

/**
 * @brief  Checks for error conditions for R3(OCR) response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: The response is normal received
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
static int32_t SDMMC_GetCmdResp3(CM_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrStatus)
{
    return SDMMC_WaitResponse(SDIOCx, (SDIOC_INT_FLAG_CC | SDIOC_INT_FLAG_CEBE | SDIOC_INT_FLAG_CTOE),
                              SDMMC_CMD_TIMEOUT, pu32ErrStatus);
}

/**
 * @brief  Checks for error conditions for R4 response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: The response is normal received
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
static int32_t SDMMC_GetCmdResp4(CM_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrStatus)
{
    return SDMMC_WaitResponse(SDIOCx, (SDIOC_INT_FLAG_CC | SDIOC_INT_FLAG_CEBE | SDIOC_INT_FLAG_CCE |
                                       SDIOC_INT_FLAG_CTOE), SDMMC_CMD_TIMEOUT, pu32ErrStatus);
}

/**
 * @brief  Checks for error conditions for R5 response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: The response is normal received
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
static int32_t SDMMC_GetCmdResp5(CM_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrStatus)
{
    return SDMMC_WaitResponse(SDIOCx, (SDIOC_INT_FLAG_CC | SDIOC_INT_FLAG_CEBE | SDIOC_INT_FLAG_CCE |
                                       SDIOC_INT_FLAG_CTOE), SDMMC_CMD_TIMEOUT, pu32ErrStatus);
}

/**
 * @brief  Checks for error conditions for R6(RCA) response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] pu16RCA                Pointer to a value of device RCA
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: The response is normal received
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
static int32_t SDMMC_GetCmdResp6(CM_SDIOC_TypeDef *SDIOCx, uint16_t *pu16RCA, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    uint32_t u32RespVal;

    i32Ret = SDMMC_WaitResponse(SDIOCx, (SDIOC_INT_FLAG_CC  | SDIOC_INT_FLAG_CIE | SDIOC_INT_FLAG_CEBE |
                                         SDIOC_INT_FLAG_CCE | SDIOC_INT_FLAG_CTOE), SDMMC_CMD_TIMEOUT, pu32ErrStatus);
    if (LL_OK == i32Ret) {
        i32Ret = LL_ERR;
        /* Fetch has received a response. */
        (void)SDIOC_GetResponse(SDIOCx, SDIOC_RESP_REG_BIT0_31, &u32RespVal);
        if (0UL == (u32RespVal & (SDMMC_R6_GEN_UNKNOWN_ERR | SDMMC_R6_ILLEGAL_CMD | SDMMC_R6_COM_CRC_FAIL))) {
            i32Ret = LL_OK;
            *pu16RCA = (uint16_t)(u32RespVal >> 16U);
        } else if (SDMMC_R6_GEN_UNKNOWN_ERR == (u32RespVal & SDMMC_R6_GEN_UNKNOWN_ERR)) {
            *pu32ErrStatus = SDMMC_ERR_GENERAL_UNKNOWN_ERR;
        } else if (SDMMC_R6_ILLEGAL_CMD == (u32RespVal & SDMMC_R6_ILLEGAL_CMD)) {
            *pu32ErrStatus = SDMMC_ERR_ILLEGAL_CMD;
        } else {
            *pu32ErrStatus = SDMMC_ERR_COM_CRC_FAILED;
        }
    }

    return i32Ret;
}

/**
 * @brief  Checks for error conditions for R7 response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: The response is normal received
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
static int32_t SDMMC_GetCmdResp7(CM_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrStatus)
{
    return SDMMC_WaitResponse(SDIOCx, (SDIOC_INT_FLAG_CC  | SDIOC_INT_FLAG_CIE | SDIOC_INT_FLAG_CEBE |
                                       SDIOC_INT_FLAG_CCE | SDIOC_INT_FLAG_CTOE), SDMMC_CMD_TIMEOUT, pu32ErrStatus);
}

/**
 * @brief  De-Initialize SDIOC.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @retval int32_t:
 *           - LL_OK: SDIOC De-Initialize success
 *           - LL_ERR_TIMEOUT: Software reset timeout
 */
int32_t SDIOC_DeInit(CM_SDIOC_TypeDef *SDIOCx)
{
    return SDIOC_SWReset(SDIOCx, SDIOC_SW_RST_ALL);
}

/**
 * @brief  Initialize SDIOC.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] pstcSdiocInit           Pointer to a @ref stc_sdioc_init_t structure
 * @retval int32_t:
 *           - LL_OK: SDIOC Initialize success
 *           - LL_ERR_INVD_PARAM: pstcSdiocInit == NULL
 */
int32_t SDIOC_Init(CM_SDIOC_TypeDef *SDIOCx, const stc_sdioc_init_t *pstcSdiocInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcSdiocInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
        DDL_ASSERT(IS_SDIOC_MD(pstcSdiocInit->u32Mode));
        DDL_ASSERT(IS_SDIOC_CARD_DETECT_WAY(pstcSdiocInit->u8CardDetect));
        DDL_ASSERT(IS_SDIOC_SPEED_MD(pstcSdiocInit->u8SpeedMode));
        DDL_ASSERT(IS_SDIOC_BUS_WIDTH(pstcSdiocInit->u8BusWidth));
        DDL_ASSERT(IS_SDIOC_CLK_DIV(pstcSdiocInit->u16ClockDiv));

        /* Set the SDIOC mode */
        if (CM_SDIOC1 == SDIOCx) {
            WRITE_REG32(bCM_PERIC->SDIOC_SYCTLREG_b.SELMMC1, pstcSdiocInit->u32Mode);
        } else {
            WRITE_REG32(bCM_PERIC->SDIOC_SYCTLREG_b.SELMMC2, pstcSdiocInit->u32Mode);
        }
        /* Set the SDIOC clock control value */
        WRITE_REG16(SDIOCx->CLKCON, (pstcSdiocInit->u16ClockDiv | SDIOC_CLKCON_ICE | SDIOC_CLKCON_CE));
        /* Set the SDIOC host control value */
        WRITE_REG8(SDIOCx->HOSTCON, (pstcSdiocInit->u8CardDetect | pstcSdiocInit->u8BusWidth |
                                     pstcSdiocInit->u8SpeedMode));
        /* Enable normal interrupt status */
        WRITE_REG16(SDIOCx->NORINTSTEN, SDIOC_NORINTSGEN_CLR_MASK);
        /* Enable error interrupt status */
        WRITE_REG16(SDIOCx->ERRINTSTEN, SDIOC_ERRINTSGEN_CLR_MASK);
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_sdioc_init_t to default values.
 * @param  [out] pstcSdiocInit          Pointer to a @ref stc_sdioc_init_t structure
 * @retval int32_t:
 *           - LL_OK: Structure Initialize success
 *           - LL_ERR_INVD_PARAM: pstcSdiocInit == NULL
 */
int32_t SDIOC_StructInit(stc_sdioc_init_t *pstcSdiocInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcSdiocInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcSdiocInit->u32Mode      = SDIOC_MD_SD;
        pstcSdiocInit->u8CardDetect = SDIOC_CARD_DETECT_CD_PIN_LVL;
        pstcSdiocInit->u8SpeedMode  = SDIOC_SPEED_MD_NORMAL;
        pstcSdiocInit->u8BusWidth   = SDIOC_BUS_WIDTH_1BIT;
        pstcSdiocInit->u16ClockDiv  = SDIOC_CLK_DIV1;
    }

    return i32Ret;
}

/**
 * @brief  Set software reset.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u8Type                  Software reset type
 *         This parameter can be one of the following values:
 *           @arg SDIOC_SW_RST_DATA_LINE:   Only part of data circuit is reset
 *           @arg SDIOC_SW_RST_CMD_LINE:    Only part of command circuit is reset
 *           @arg SDIOC_SW_RST_ALL:         Reset the entire Host Controller except for the card detection circuit
 * @retval int32_t:
 *           - LL_OK: Software reset success
 *           - LL_ERR_TIMEOUT: Software reset timeout
 */
int32_t SDIOC_SWReset(CM_SDIOC_TypeDef *SDIOCx, uint8_t u8Type)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32Count;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_SW_RST_TYPE(u8Type));

    WRITE_REG8(SDIOCx->SFTRST, u8Type);
    /* Wait for reset finish */
    u32Count = SDIOC_SW_RST_TIMEOUT * (HCLK_VALUE / 20000UL);
    while (0U != READ_REG8_BIT(SDIOCx->SFTRST, u8Type)) {
        if (0UL == u32Count) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
        u32Count--;
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable power.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void SDIOC_PowerCmd(CM_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        SET_REG8_BIT(SDIOCx->PWRCON, SDIOC_PWRCON_PWON);
    } else {
        CLR_REG8_BIT(SDIOCx->PWRCON, SDIOC_PWRCON_PWON);
    }
}

/**
 * @brief  Get power state.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @retval An @ref en_functional_state_t enumeration value.
 *           - DISABLE: Power off or SDIOCx == NULL
 *           - ENABLE: Power on
 */
en_functional_state_t SDIOC_GetPowerState(const CM_SDIOC_TypeDef *SDIOCx)
{
    en_functional_state_t enPowerSta = DISABLE;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));

    if (0U != (READ_REG8_BIT(SDIOCx->PWRCON, SDIOC_PWRCON_PWON))) {
        enPowerSta = ENABLE;
    }

    return enPowerSta;
}

/**
 * @brief  Get SDIOC work mode.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @retval uint32_t value:
 *           - SDIOC_MD_SD:   SDIOCx selects SD mode
 *           - SDIOC_MD_MMC:  SDIOCx selects MMC mode
 */
uint32_t SDIOC_GetMode(const CM_SDIOC_TypeDef *SDIOCx)
{
    uint32_t u32SdMode;
    uint32_t u32Temp;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));

    if (CM_SDIOC1 == SDIOCx) {
        u32Temp = PERIC_SDIOC_SYCTLREG_SELMMC1;
    } else {
        u32Temp = PERIC_SDIOC_SYCTLREG_SELMMC2;
    }
    u32SdMode = READ_REG32_BIT(CM_PERIC->SDIOC_SYCTLREG, u32Temp);
    if (0UL != u32SdMode) { /* MMC mode */
        u32SdMode = SDIOC_MD_MMC;
    } else {
        u32SdMode = SDIOC_MD_SD;
    }

    return u32SdMode;
}

/**
 * @brief  Enable or disable clock output.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void SDIOC_ClockCmd(CM_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        SET_REG8_BIT(SDIOCx->CLKCON, SDIOC_CLKCON_CE);
    } else {
        CLR_REG8_BIT(SDIOCx->CLKCON, SDIOC_CLKCON_CE);
    }
}

/**
 * @brief  Set clock division.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u16Div                  Clock division
 *         This parameter can be one of the following values:
 *           @arg SDIOC_CLK_DIV1:       CLK1/1
 *           @arg SDIOC_CLK_DIV2:       CLK1/2
 *           @arg SDIOC_CLK_DIV4:       CLK1/4
 *           @arg SDIOC_CLK_DIV8:       CLK1/8
 *           @arg SDIOC_CLK_DIV16:      CLK1/16
 *           @arg SDIOC_CLK_DIV32:      CLK1/32
 *           @arg SDIOC_CLK_DIV64:      CLK1/64
 *           @arg SDIOC_CLK_DIV128:     CLK1/128
 *           @arg SDIOC_CLK_DIV256:     CLK1/256
 * @retval None
 */
void SDIOC_SetClockDiv(CM_SDIOC_TypeDef *SDIOCx, uint16_t u16Div)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_CLK_DIV(u16Div));

    MODIFY_REG16(SDIOCx->CLKCON, SDIOC_CLKCON_FS, u16Div);
}

/**
 * @brief  Find the most suitable clock division for the set clock frequency.
 * @note   More clock values can be set as needed, but the maximum cannot exceed 50MHz.
 * @param  [in] u32ClockFreq            SDIOCx_CK clock frequency
 *         This parameter can be one of the following values:
 *           @arg SDIOC_OUTPUT_CLK_FREQ_400K:   SDIOC clock: 400KHz
 *           @arg SDIOC_OUTPUT_CLK_FREQ_25M:    SDIOC clock: 25MHz
 *           @arg SDIOC_OUTPUT_CLK_FREQ_26M:    SDIOC clock: 26MHz
 *           @arg SDIOC_OUTPUT_CLK_FREQ_50M:    SDIOC clock: 50MHz
 *           @arg SDIOC_OUTPUT_CLK_FREQ_52M:    SDIOC clock: 52MHz
 *           @arg Any other value
 * @param  [out] pu16Div                Pointer to a value of clock division
 * @retval int32_t:
 *           - LL_OK: SDIOC Initialize success
 *           - LL_ERR: The Bus clock frequency is too high
 *           - LL_ERR_INVD_PARAM: pu16Div == NULL or 0UL == u32ClockFreq
 */
int32_t SDIOC_GetOptimumClockDiv(uint32_t u32ClockFreq, uint16_t *pu16Div)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32BusClock;
    uint32_t u32ClockDiv;
    uint32_t u32Temp;

    if ((NULL == pu16Div) || (0UL == u32ClockFreq)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Get BUS frequency */
        u32BusClock = SystemCoreClock / (0x01UL << (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS));
        u32ClockDiv = u32BusClock / u32ClockFreq;
        if (0UL != (u32BusClock % u32ClockFreq)) {
            u32ClockDiv++;
        }
        /* Check the effectiveness of clock division */
        if (u32ClockDiv > 256U) { /* Maximum division is 256 */
            i32Ret = LL_ERR;
        } else {
            if (1U == u32ClockDiv) {
                *pu16Div = SDIOC_CLK_DIV1;
            } else {
                for (u32Temp = SDIOC_CLK_DIV2; u32Temp <= SDIOC_CLK_DIV256; u32Temp <<= 1U) {
                    if (u32ClockDiv <= (u32Temp >> (SDIOC_CLKCON_FS_POS - 1U))) {
                        break;
                    }
                }
                *pu16Div = (uint16_t)u32Temp;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Verify the validity of the clock division.
 * @param  [in] u32Mode                 SDIOC work mode
 *         This parameter can be one of the following values:
 *           @arg SDIOC_MD_SD:          SDIOCx selects SD mode
 *           @arg SDIOC_MD_MMC:         SDIOCx selects MMC mode
 * @param  [in] u8SpeedMode             Speed mode
 *         This parameter can be one of the following values:
 *           @arg SDIOC_SPEED_MD_NORMAL:    Normal speed mode
 *           @arg SDIOC_SPEED_MD_HIGH:      High speed mode
 * @param  [in] u16ClockDiv             Clock division
 *         This parameter can be one of the following values:
 *           @arg SDIOC_CLK_DIV1:       CLK1/1
 *           @arg SDIOC_CLK_DIV2:       CLK1/2
 *           @arg SDIOC_CLK_DIV4:       CLK1/4
 *           @arg SDIOC_CLK_DIV8:       CLK1/8
 *           @arg SDIOC_CLK_DIV16:      CLK1/16
 *           @arg SDIOC_CLK_DIV32:      CLK1/32
 *           @arg SDIOC_CLK_DIV64:      CLK1/64
 *           @arg SDIOC_CLK_DIV128:     CLK1/128
 *           @arg SDIOC_CLK_DIV256:     CLK1/256
 * @retval int32_t:
 *           - LL_OK: The clock division is valid
 *           - LL_ERR: The Bus clock frequency is too high
 */
int32_t SDIOC_VerifyClockDiv(uint32_t u32Mode, uint8_t u8SpeedMode, uint16_t u16ClockDiv)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32BusClock;
    uint32_t u32ClockFreq;
    uint32_t u32MaxFreq;
    uint32_t u32DivValue;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_MD(u32Mode));
    DDL_ASSERT(IS_SDIOC_SPEED_MD(u8SpeedMode));
    DDL_ASSERT(IS_SDIOC_CLK_DIV(u16ClockDiv));

    /* Get Bus frequency */
    u32BusClock = SystemCoreClock / (0x01UL << (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS));
    u32DivValue = ((uint32_t)u16ClockDiv >> (SDIOC_CLKCON_FS_POS - 1U));
    if (0UL == u32DivValue) {
        u32ClockFreq = u32BusClock;
    } else {
        u32ClockFreq = u32BusClock / u32DivValue;
    }

    if (SDIOC_SPEED_MD_NORMAL == u8SpeedMode) {
        if (SDIOC_MD_SD != u32Mode) { /* MMC mode */
            u32MaxFreq = SDIOC_OUTPUT_CLK_FREQ_26M;
        } else {
            u32MaxFreq = SDIOC_OUTPUT_CLK_FREQ_25M;
        }
    } else {
        if (SDIOC_MD_SD != u32Mode) { /* MMC mode */
            u32MaxFreq = SDIOC_OUTPUT_CLK_FREQ_52M;
        } else {
            u32MaxFreq = SDIOC_OUTPUT_CLK_FREQ_50M;
        }
    }
    if (u32ClockFreq > u32MaxFreq) {
        i32Ret = LL_ERR;
    }

    return i32Ret;
}

/**
 * @brief  Get device insert status.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t SDIOC_GetInsertStatus(const CM_SDIOC_TypeDef *SDIOCx)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));

    if (0UL != (READ_REG32_BIT(SDIOCx->PSTAT, SDIOC_PSTAT_CSS))) {
        if (0UL != (READ_REG32_BIT(SDIOCx->PSTAT, SDIOC_PSTAT_CIN))) {
            enFlagSta = SET;
        }
    }

    return enFlagSta;
}

/**
 * @brief  Set speed mode.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u8SpeedMode             Speed mode
 *         This parameter can be one of the following values:
 *           @arg SDIOC_SPEED_MD_NORMAL:    Normal speed mode
 *           @arg SDIOC_SPEED_MD_HIGH:      High speed mode
 * @retval None
 */
void SDIOC_SetSpeedMode(CM_SDIOC_TypeDef *SDIOCx, uint8_t u8SpeedMode)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_SPEED_MD(u8SpeedMode));

    if (SDIOC_SPEED_MD_NORMAL != u8SpeedMode) {
        SET_REG8_BIT(SDIOCx->HOSTCON, SDIOC_HOSTCON_HSEN);
    } else {
        CLR_REG8_BIT(SDIOCx->HOSTCON, SDIOC_HOSTCON_HSEN);
    }
}

/**
 * @brief  Set bus width.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u8BusWidth              Bus width
 *         This parameter can be one of the following values:
 *           @arg SDIOC_BUS_WIDTH_1BIT: The Bus width is 1 bit
 *           @arg SDIOC_BUS_WIDTH_4BIT: The Bus width is 4 bit
 *           @arg SDIOC_BUS_WIDTH_8BIT: The Bus width is 8 bit
 * @retval None
 */
void SDIOC_SetBusWidth(CM_SDIOC_TypeDef *SDIOCx, uint8_t u8BusWidth)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_BUS_WIDTH(u8BusWidth));

    MODIFY_REG8(SDIOCx->HOSTCON, (SDIOC_HOSTCON_DW | SDIOC_HOSTCON_EXDW), u8BusWidth);
}

/**
 * @brief  Set card detect line select.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u8Src                   Card detect source
 *         This parameter can be one of the following values:
 *           @arg SDIOC_CARD_DETECT_CD_PIN_LVL:     SDIOCx_CD(x=1~2) line is selected (for normal use)
 *           @arg SDIOC_CARD_DETECT_TEST_SIGNAL:    The Card Detect Test Level is selected(for test purpose)
 * @retval None
 */
void SDIOC_SetCardDetectSrc(CM_SDIOC_TypeDef *SDIOCx, uint8_t u8Src)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_CARD_DETECT_WAY(u8Src));

    if (SDIOC_CARD_DETECT_CD_PIN_LVL != u8Src) {
        SET_REG8_BIT(SDIOCx->HOSTCON, SDIOC_HOSTCON_CDSS);
    } else {
        CLR_REG8_BIT(SDIOCx->HOSTCON, SDIOC_HOSTCON_CDSS);
    }
}

/**
 * @brief  Set card detect test level.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u8Level                 Card test level
 *         This parameter can be one of the following values:
 *           @arg SDIOC_CARD_DETECT_TEST_LVL_LOW:   Card identification test signal is low level (with device insertion)
 *           @arg SDIOC_CARD_DETECT_TEST_LVL_HIGH:  Card identification test signal is high level (no device insertion)
 * @retval None
 */
void SDIOC_SetCardDetectTestLevel(CM_SDIOC_TypeDef *SDIOCx, uint8_t u8Level)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_CARD_DETECT_TEST_LEVEL(u8Level));

    if (SDIOC_CARD_DETECT_TEST_LVL_LOW != u8Level) {
        SET_REG8_BIT(SDIOCx->HOSTCON, SDIOC_HOSTCON_CDTL);
    } else {
        CLR_REG8_BIT(SDIOCx->HOSTCON, SDIOC_HOSTCON_CDTL);
    }
}

/**
 * @brief  Configure the SDIOCx command parameters.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] pstcCmdConfig           Pointer to a @ref stc_sdioc_cmd_config_t structure
 * @retval int32_t:
 *           - LL_OK: Configure SDIOCx command parameters success
 *           - LL_ERR_INVD_PARAM: pstcCmdConfig == NULL
 */
int32_t SDIOC_SendCommand(CM_SDIOC_TypeDef *SDIOCx, const stc_sdioc_cmd_config_t *pstcCmdConfig)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t *pu32Temp;

    if (NULL == pstcCmdConfig) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
        DDL_ASSERT(IS_SDIOC_CMD_INDEX(pstcCmdConfig->u16CmdIndex));
        DDL_ASSERT(IS_SDIOC_CMD_TYPE(pstcCmdConfig->u16CmdType));
        DDL_ASSERT(IS_SDIOC_DATA_LINE(pstcCmdConfig->u16DataLine));
        DDL_ASSERT(IS_SDIOC_RESP_TYPE(pstcCmdConfig->u16ResponseType));

        /* Set the SDIOC Command parameters value */
        pu32Temp = SDIOC_ARG_ADDR(SDIOCx);
        WRITE_REG32(*pu32Temp, pstcCmdConfig->u32Argument);
        /* Set the SDIOC Command controller value */
        WRITE_REG16(SDIOCx->CMD, ((uint16_t)(pstcCmdConfig->u16CmdIndex << SDIOC_CMD_IDX_POS) |
                                  pstcCmdConfig->u16CmdType | pstcCmdConfig->u16DataLine |
                                  pstcCmdConfig->u16ResponseType));
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_sdioc_cmd_config_t to default values.
 * @param  [out] pstcCmdConfig          Pointer to a @ref stc_sdioc_cmd_config_t structure
 * @retval int32_t:
 *           - LL_OK: Structure Initialize success
 *           - LL_ERR_INVD_PARAM: pstcDataConfig == NULL
 */
int32_t SDIOC_CommandStructInit(stc_sdioc_cmd_config_t *pstcCmdConfig)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcCmdConfig) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcCmdConfig->u32Argument      = 0U;
        pstcCmdConfig->u16CmdIndex      = 0U;
        pstcCmdConfig->u16CmdType       = SDIOC_CMD_TYPE_NORMAL;
        pstcCmdConfig->u16DataLine      = SDIOC_DATA_LINE_DISABLE;
        pstcCmdConfig->u16ResponseType  = SDIOC_RESP_TYPE_NO;
    }

    return i32Ret;
}

/**
 * @brief  Get the response received from the card for the last command
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u8Reg                   SDIOC response register
 *         This parameter can be one of the following values:
 *           @arg SDIOC_RESP_REG_BIT0_31:   Command Response Register 0-31bit
 *           @arg SDIOC_RESP_REG_BIT32_63:  Command Response Register 32-63bit
 *           @arg SDIOC_RESP_REG_BIT64_95:  Command Response Register 64-95bit
 *           @arg SDIOC_RESP_REG_BIT96_127: Command Response Register 96-127bit
 * @param  [out] pu32Value              Pointer to a Response value
 * @retval int32_t:
 *           - LL_OK: Get response success
 *           - LL_ERR_INVD_PARAM: pu32Value == NULL
 */
int32_t SDIOC_GetResponse(CM_SDIOC_TypeDef *SDIOCx, uint8_t u8Reg, uint32_t *pu32Value)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pu32Value) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
        DDL_ASSERT(IS_SDIOC_RESP_REG(u8Reg));

        *pu32Value = READ_REG32(*SDIOC_RESP_ADDR(SDIOCx, u8Reg));
    }

    return i32Ret;
}

/**
 * @brief  Configure the SDIOCx data parameters.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] pstcDataConfig          Pointer to a @ref stc_sdioc_data_config_t structure
 * @retval int32_t:
 *           - LL_OK: Configure SDIOCx data parameters success
 *           - LL_ERR_INVD_PARAM: pstcDataConfig == NULL
 */
int32_t SDIOC_ConfigData(CM_SDIOC_TypeDef *SDIOCx, const stc_sdioc_data_config_t *pstcDataConfig)
{
    int32_t i32Ret = LL_OK;
    uint16_t u16BlkCnt;

    if (NULL == pstcDataConfig) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
        DDL_ASSERT(IS_SDIOC_BLOCK_SIZE(pstcDataConfig->u16BlockSize));
        DDL_ASSERT(IS_SDIOC_TRANS_DIR(pstcDataConfig->u16TransDir));
        DDL_ASSERT(IS_SDIOC_AUTO_SEND_CMD12(pstcDataConfig->u16AutoCmd12));
        DDL_ASSERT(IS_SDIOC_TRANS_MD(pstcDataConfig->u16TransMode));
        DDL_ASSERT(IS_SDIOC_DATA_TIMEOUT_TIME(pstcDataConfig->u16DataTimeout));

        if (SDIOC_TRANS_MD_STOP_MULTI == pstcDataConfig->u16TransMode) {
            u16BlkCnt = 0U;
        } else {
            u16BlkCnt = pstcDataConfig->u16BlockCount;
        }
        /* Set the SDIOC Data Transfer Timeout value */
        WRITE_REG8(SDIOCx->TOUTCON, pstcDataConfig->u16DataTimeout);
        /* Set the SDIOC Block Count value */
        WRITE_REG16(SDIOCx->BLKSIZE, pstcDataConfig->u16BlockSize);
        /* Set the SDIOC Block Size value */
        WRITE_REG16(SDIOCx->BLKCNT, u16BlkCnt);
        /* Set the SDIOC Data Transfer Mode */
        WRITE_REG16(SDIOCx->TRANSMODE, ((pstcDataConfig->u16TransDir | pstcDataConfig->u16AutoCmd12 |
                                         pstcDataConfig->u16TransMode) & 0xFFU));
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_sdioc_data_config_t to default values.
 * @param  [out] pstcDataConfig         Pointer to a @ref stc_sdioc_data_config_t structure
 * @retval int32_t:
 *           - LL_OK: Structure Initialize success
 *           - LL_ERR_INVD_PARAM: pstcDataConfig == NULL
 */
int32_t SDIOC_DataStructInit(stc_sdioc_data_config_t *pstcDataConfig)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcDataConfig) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcDataConfig->u16BlockSize    = 512U;
        pstcDataConfig->u16BlockCount   = 0U;
        pstcDataConfig->u16TransDir     = SDIOC_TRANS_DIR_TO_CARD;
        pstcDataConfig->u16AutoCmd12    = SDIOC_AUTO_SEND_CMD12_DISABLE;
        pstcDataConfig->u16TransMode    = SDIOC_TRANS_MD_SINGLE;
        pstcDataConfig->u16DataTimeout  = SDIOC_DATA_TIMEOUT_CLK_2E13;
    }

    return i32Ret;
}

/**
 * @brief  Read data from SDIOC FIFO.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] au8Data                Pointer to the buffer
 * @param  [in] u32Len                  Data length
 * @retval int32_t:
 *           - LL_OK: Read data success
 *           - LL_ERR_INVD_PARAM: NULL == au8Data or (u32Len % 4U) != 0
 */
int32_t SDIOC_ReadBuffer(CM_SDIOC_TypeDef *SDIOCx, uint8_t au8Data[], uint32_t u32Len)
{
    int32_t i32Ret = LL_OK;
    uint32_t i;
    uint32_t u32Temp;
    __IO uint32_t *BUF_REG;

    if ((NULL == au8Data) || (0U != (u32Len % 4U))) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));

        BUF_REG = SDIOC_BUF_ADDR(SDIOCx);
        for (i = 0U; i < u32Len; i += 4U) {
            u32Temp = READ_REG32(*BUF_REG);
            au8Data[i]      = (uint8_t)(u32Temp & 0xFFUL);
            au8Data[i + 1U] = (uint8_t)((u32Temp >> 8U) & 0xFFUL);
            au8Data[i + 2U] = (uint8_t)((u32Temp >> 16U) & 0xFFUL);
            au8Data[i + 3U] = (uint8_t)((u32Temp >> 24U) & 0xFFUL);
        }
    }

    return i32Ret;
}

/**
 * @brief  Write data to SDIOC FIFO.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] au8Data                 Pointer to the buffer
 * @param  [in] u32Len                  Data length
 * @retval int32_t:
 *           - LL_OK: Write data success
 *           - LL_ERR_INVD_PARAM: NULL == au8Data or (u32Len % 4U) != 0
 */
int32_t SDIOC_WriteBuffer(CM_SDIOC_TypeDef *SDIOCx, const uint8_t au8Data[], uint32_t u32Len)
{
    int32_t i32Ret = LL_OK;
    uint32_t i;
    uint32_t u32Temp;
    __IO uint32_t *BUF_REG;

    if ((NULL == au8Data) || (0U != (u32Len % 4U))) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));

        BUF_REG = SDIOC_BUF_ADDR(SDIOCx);
        for (i = 0U; i < u32Len; i += 4U) {
            u32Temp = ((uint32_t)au8Data[i + 3U] << 24U) | ((uint32_t)au8Data[i + 2U] << 16U) |
                      ((uint32_t)au8Data[i + 1U] << 8U)  | au8Data[i];
            WRITE_REG32(*BUF_REG, u32Temp);
        }
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable block gap stop.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void SDIOC_BlockGapStopCmd(CM_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        SET_REG8_BIT(SDIOCx->BLKGPCON, SDIOC_BLKGPCON_SABGR);
    } else {
        CLR_REG8_BIT(SDIOCx->BLKGPCON, SDIOC_BLKGPCON_SABGR);
    }
}

/**
 * @brief  Restart data transfer.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @retval None
 */
void SDIOC_RestartTrans(CM_SDIOC_TypeDef *SDIOCx)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));

    SET_REG8_BIT(SDIOCx->BLKGPCON, SDIOC_BLKGPCON_CR);
}

/**
 * @brief  Enable or disable read wait.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void SDIOC_ReadWaitCmd(CM_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        SET_REG8_BIT(SDIOCx->BLKGPCON, SDIOC_BLKGPCON_RWC);
    } else {
        CLR_REG8_BIT(SDIOCx->BLKGPCON, SDIOC_BLKGPCON_RWC);
    }
}

/**
 * @brief  Enable or disable data block gap interrupt.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void SDIOC_BlockGapIntCmd(CM_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        SET_REG8_BIT(SDIOCx->BLKGPCON, SDIOC_BLKGPCON_IABG);
    } else {
        CLR_REG8_BIT(SDIOCx->BLKGPCON, SDIOC_BLKGPCON_IABG);
    }
}

/**
 * @brief  Enable or disable interrupt.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32IntType              Normal and error interrupts source
 *         This parameter can be one or any combination of the following values:
 *           @arg SDIOC_INT_CINTSEN:    Card interrupt
 *           @arg SDIOC_INT_CRMSEN:     Card Removal interrupt
 *           @arg SDIOC_INT_CISTSEN:    Card Insertion interrupt
 *           @arg SDIOC_INT_BRRSEN:     Buffer Read Ready interrupt
 *           @arg SDIOC_INT_BWRSEN:     Buffer Write Ready interrupt
 *           @arg SDIOC_INT_BGESEN:     Block Gap Event interrupt
 *           @arg SDIOC_INT_TCSEN:      Transfer Complete interrupt
 *           @arg SDIOC_INT_CCSEN:      Command Complete interrupt
 *           @arg SDIOC_INT_ACESEN:     Auto CMD12 error interrupt
 *           @arg SDIOC_INT_DEBESEN:    Data End Bit error interrupt
 *           @arg SDIOC_INT_DCESEN:     Data CRC error interrupt
 *           @arg SDIOC_INT_DTOESEN:    Data Timeout error interrupt
 *           @arg SDIOC_INT_CIESEN:     Command Index error interrupt
 *           @arg SDIOC_INT_CEBESEN:    Command End Bit error interrupt
 *           @arg SDIOC_INT_CCESEN:     Command CRC error interrupt
 *           @arg SDIOC_INT_CTOESEN:    Command Timeout error interrupt
 *           @arg SDIOC_INT_ALL:        All of the above
 *           @arg SDIOC_NORMAL_INT_ALL: All of the normal interrupt
 *           @arg SDIOC_ERR_INT_ALL:    All of the error interrupt
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void SDIOC_IntCmd(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    uint16_t u16NormalInt;
    uint16_t u16ErrorInt;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u16NormalInt = (uint16_t)(u32IntType & 0xFFFFU);
    u16ErrorInt  = (uint16_t)(u32IntType >> 16U);
    if (DISABLE != enNewState) {
        if (0U != u16NormalInt) {
            SET_REG16_BIT(SDIOCx->NORINTSGEN, u16NormalInt);
        }
        if (0U != u16ErrorInt) {
            SET_REG16_BIT(SDIOCx->ERRINTSGEN, u16ErrorInt);
        }
    } else {
        if (0U != u16NormalInt) {
            CLR_REG16_BIT(SDIOCx->NORINTSGEN, u16NormalInt);
        }
        if (0U != u16ErrorInt) {
            CLR_REG16_BIT(SDIOCx->ERRINTSGEN, u16ErrorInt);
        }
    }
}

/**
 * @brief  Get interrupt enable state.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32IntType              Normal and error interrupts source
 *         This parameter can be one or any combination of the following values:
 *           @arg SDIOC_INT_CINTSEN:    Card interrupt
 *           @arg SDIOC_INT_CRMSEN:     Card Removal interrupt
 *           @arg SDIOC_INT_CISTSEN:    Card Insertion interrupt
 *           @arg SDIOC_INT_BRRSEN:     Buffer Read Ready interrupt
 *           @arg SDIOC_INT_BWRSEN:     Buffer Write Ready interrupt
 *           @arg SDIOC_INT_BGESEN:     Block Gap Event interrupt
 *           @arg SDIOC_INT_TCSEN:      Transfer Complete interrupt
 *           @arg SDIOC_INT_CCSEN:      Command Complete interrupt
 *           @arg SDIOC_INT_ACESEN:     Auto CMD12 error interrupt
 *           @arg SDIOC_INT_DEBESEN:    Data End Bit error interrupt
 *           @arg SDIOC_INT_DCESEN:     Data CRC error interrupt
 *           @arg SDIOC_INT_DTOESEN:    Data Timeout error interrupt
 *           @arg SDIOC_INT_CIESEN:     Command Index error interrupt
 *           @arg SDIOC_INT_CEBESEN:    Command End Bit error interrupt
 *           @arg SDIOC_INT_CCESEN:     Command CRC error interrupt
 *           @arg SDIOC_INT_CTOESEN:    Command Timeout error interrupt
 *           @arg SDIOC_INT_ALL:        All of the above
 *           @arg SDIOC_NORMAL_INT_ALL: All of the normal interrupt
 *           @arg SDIOC_ERR_INT_ALL:    All of the error interrupt
 * @retval An @ref en_functional_state_t enumeration value.
 *           - ENABLE: The interrupt is enable
 *           - DISABLE: The interrupt is disable
 */
en_functional_state_t SDIOC_GetIntEnableState(const CM_SDIOC_TypeDef *SDIOCx, uint32_t u32IntType)
{
    uint16_t u16NormalInt;
    uint16_t u16ErrorInt;
    en_functional_state_t enIntSta = DISABLE;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_INT(u32IntType));

    u16NormalInt = (uint16_t)(u32IntType & 0xFFFFU);
    u16ErrorInt  = (uint16_t)(u32IntType >> 16U);
    if (0U != u16NormalInt) {
        if (0U != (READ_REG16_BIT(SDIOCx->NORINTSGEN, u16NormalInt))) {
            enIntSta = ENABLE;
        }
    }
    if ((0U != u16ErrorInt) && (enIntSta != ENABLE)) {
        if (0U != (READ_REG16_BIT(SDIOCx->ERRINTSGEN, u16ErrorInt))) {
            enIntSta = ENABLE;
        }
    }

    return enIntSta;
}

/**
 * @brief  Get interrupt flag status.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32Flag                 Normal and error interrupts flag
 *         This parameter can be one or any combination the following values:
 *           @arg SDIOC_INT_FLAG_EI:    Error interrupt flag
 *           @arg SDIOC_INT_FLAG_CINT:  Card interrupt flag
 *           @arg SDIOC_INT_FLAG_CRM:   Card Removal flag
 *           @arg SDIOC_INT_FLAG_CIST:  Card Insertion flag
 *           @arg SDIOC_INT_FLAG_BRR:   Buffer Read Ready flag
 *           @arg SDIOC_INT_FLAG_BWR:   Buffer Write Ready flag
 *           @arg SDIOC_INT_FLAG_BGE:   Block Gap Event flag
 *           @arg SDIOC_INT_FLAG_TC:    Transfer Complete flag
 *           @arg SDIOC_INT_FLAG_CC:    Command Complete flag
 *           @arg SDIOC_INT_FLAG_ACE:   Auto CMD12 error flag
 *           @arg SDIOC_INT_FLAG_DEBE:  Data End Bit error flag
 *           @arg SDIOC_INT_FLAG_DCE:   Data CRC error flag
 *           @arg SDIOC_INT_FLAG_DTOE:  Data Timeout error flag
 *           @arg SDIOC_INT_FLAG_CIE:   Command Index error flag
 *           @arg SDIOC_INT_FLAG_CEBE:  Command End Bit error flag
 *           @arg SDIOC_INT_FLAG_CCE:   Command CRC error flag
 *           @arg SDIOC_INT_FLAG_CTOE:  Command Timeout error flag
 *           @arg SDIOC_INT_FLAG_ALL:           All of the above
 *           @arg SDIOC_NORMAL_INT_FLAG_ALL:    All of the normal interrupt flag
 *           @arg SDIOC_ERR_INT_FLAG_ALL:       All of the error interrupt flag
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t SDIOC_GetIntStatus(const CM_SDIOC_TypeDef *SDIOCx, uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;
    uint16_t u16NormalFlag;
    uint16_t u16ErrorFlag;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_GET_INT_FLAG(u32Flag));

    u16NormalFlag = (uint16_t)(u32Flag & 0xFFFFU);
    u16ErrorFlag  = (uint16_t)(u32Flag >> 16U);
    if (0U != u16NormalFlag) {
        if (0U != (READ_REG16_BIT(SDIOCx->NORINTST, u16NormalFlag))) {
            enFlagSta = SET;
        }
    }
    if ((0U != u16ErrorFlag) && (enFlagSta != SET)) {
        if (0U != (READ_REG16_BIT(SDIOCx->ERRINTST, u16ErrorFlag))) {
            enFlagSta = SET;
        }
    }

    return enFlagSta;
}

/**
 * @brief  Clear interrupt flag status.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32Flag                 Normal and error interrupts flag
 *         This parameter can be one or any combination of the following values:
 *           @arg SDIOC_INT_FLAG_CRM:   Card Removal flag
 *           @arg SDIOC_INT_FLAG_CIST:  Card Insertion flag
 *           @arg SDIOC_INT_FLAG_BRR:   Buffer Read Ready flag
 *           @arg SDIOC_INT_FLAG_BWR:   Buffer Write Ready flag
 *           @arg SDIOC_INT_FLAG_BGE:   Block Gap Event flag
 *           @arg SDIOC_INT_FLAG_TC:    Transfer Complete flag
 *           @arg SDIOC_INT_FLAG_CC:    Command Complete flag
 *           @arg SDIOC_INT_FLAG_ACE:   Auto CMD12 error flag
 *           @arg SDIOC_INT_FLAG_DEBE:  Data End Bit error flag
 *           @arg SDIOC_INT_FLAG_DCE:   Data CRC error flag
 *           @arg SDIOC_INT_FLAG_DTOE:  Data Timeout error flag
 *           @arg SDIOC_INT_FLAG_CIE:   Command Index error flag
 *           @arg SDIOC_INT_FLAG_CEBE:  Command End Bit error flag
 *           @arg SDIOC_INT_FLAG_CCE:   Command CRC error flag
 *           @arg SDIOC_INT_FLAG_CTOE:  Command Timeout error flag
 *           @arg SDIOC_INT_FLAG_CLR_ALL:   All of the above
 * @retval None
 */
void SDIOC_ClearIntStatus(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32Flag)
{
    uint16_t u16NormalFlag;
    uint16_t u16ErrorFlag;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_CLR_INT_FLAG(u32Flag));

    u16NormalFlag = (uint16_t)(u32Flag & 0xFFFFU);
    u16ErrorFlag  = (uint16_t)(u32Flag >> 16U);
    if (0U != u16NormalFlag) {
        WRITE_REG16(SDIOCx->NORINTST, u16NormalFlag);
    }
    if (0U != u16ErrorFlag) {
        WRITE_REG16(SDIOCx->ERRINTST, u16ErrorFlag);
    }
}

/**
 * @brief  Enable or disable interrupt status.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32IntType              Normal and error interrupts source
 *         This parameter can be one or any combination of the following values:
 *           @arg SDIOC_INT_CINTSEN:    Card interrupt
 *           @arg SDIOC_INT_CRMSEN:     Card Removal interrupt
 *           @arg SDIOC_INT_CISTSEN:    Card Insertion interrupt
 *           @arg SDIOC_INT_BRRSEN:     Buffer Read Ready interrupt
 *           @arg SDIOC_INT_BWRSEN:     Buffer Write Ready interrupt
 *           @arg SDIOC_INT_BGESEN:     Block Gap Event interrupt
 *           @arg SDIOC_INT_TCSEN:      Transfer Complete interrupt
 *           @arg SDIOC_INT_CCSEN:      Command Complete interrupt
 *           @arg SDIOC_INT_ACESEN:     Auto CMD12 error interrupt
 *           @arg SDIOC_INT_DEBESEN:    Data End Bit error interrupt
 *           @arg SDIOC_INT_DCESEN:     Data CRC error interrupt
 *           @arg SDIOC_INT_DTOESEN:    Data Timeout error interrupt
 *           @arg SDIOC_INT_CIESEN:     Command Index error interrupt
 *           @arg SDIOC_INT_CEBESEN:    Command End Bit error interrupt
 *           @arg SDIOC_INT_CCESEN:     Command CRC error interrupt
 *           @arg SDIOC_INT_CTOESEN:    Command Timeout error interrupt
 *           @arg SDIOC_INT_ALL:        All of the above
 *           @arg SDIOC_NORMAL_INT_ALL: All of the normal interrupt
 *           @arg SDIOC_ERR_INT_ALL:    All of the error interrupt
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void SDIOC_IntStatusCmd(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    uint16_t u16NormalInt;
    uint16_t u16ErrorInt;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u16NormalInt = (uint16_t)(u32IntType & 0xFFFFU);
    u16ErrorInt  = (uint16_t)(u32IntType >> 16U);
    if (DISABLE != enNewState) {
        if (0U != u16NormalInt) {
            SET_REG16_BIT(SDIOCx->NORINTSTEN, u16NormalInt);
        }
        if (0U != u16ErrorInt) {
            SET_REG16_BIT(SDIOCx->ERRINTSTEN, u16ErrorInt);
        }
    } else {
        if (0U != u16NormalInt) {
            CLR_REG16_BIT(SDIOCx->NORINTSTEN, u16NormalInt);
        }
        if (0U != u16ErrorInt) {
            CLR_REG16_BIT(SDIOCx->ERRINTSTEN, u16ErrorInt);
        }
    }
}

/**
 * @brief  Get Host status.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32Flag                 Host flag
 *         This parameter can be one or any combination the following values:
 *           @arg SDIOC_HOST_FLAG_CMDL:     CMD Line Level flag
 *           @arg SDIOC_HOST_FLAG_DATL:     DAT[3:0] Line Level flag
 *           @arg SDIOC_HOST_FLAG_DATL_D0:  DAT[0] Line Level flag
 *           @arg SDIOC_HOST_FLAG_DATL_D1:  DAT[1] Line Level flag
 *           @arg SDIOC_HOST_FLAG_DATL_D2:  DAT[2] Line Level flag
 *           @arg SDIOC_HOST_FLAG_DATL_D3:  DAT[3] Line Level flag
 *           @arg SDIOC_HOST_FLAG_WPL:      Write Protect Line Level flag
 *           @arg SDIOC_HOST_FLAG_CDL:      Card Detect Line Level flag
 *           @arg SDIOC_HOST_FLAG_CSS:      Device Stable flag
 *           @arg SDIOC_HOST_FLAG_CIN:      Device Inserted flag
 *           @arg SDIOC_HOST_FLAG_BRE:      Data buffer full flag
 *           @arg SDIOC_HOST_FLAG_BWE:      Data buffer empty flag
 *           @arg SDIOC_HOST_FLAG_RTA:      Read operation flag
 *           @arg SDIOC_HOST_FLAG_WTA:      Write operation flag
 *           @arg SDIOC_HOST_FLAG_DA:       DAT Line transfer flag
 *           @arg SDIOC_HOST_FLAG_CID:      Command Inhibit with data flag
 *           @arg SDIOC_HOST_FLAG_CIC:      Command Inhibit flag
 *           @arg SDIOC_HOST_FLAG_ALL:      All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t SDIOC_GetHostStatus(const CM_SDIOC_TypeDef *SDIOCx, uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_GET_HOST_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(SDIOCx->PSTAT, u32Flag))) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/**
 * @brief  Get auto CMD12 error status.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u16Flag                 Auto CMD12 error flag
 *         This parameter can be one or any combination the following values:
 *           @arg SDIOC_AUTO_CMD_ERR_FLAG_CMDE: Command Not Issued By Auto CMD12 error flag
 *           @arg SDIOC_AUTO_CMD_ERR_FLAG_IE:   Auto CMD12 Index error flag
 *           @arg SDIOC_AUTO_CMD_ERR_FLAG_EBE:  Auto CMD12 End Bit error flag
 *           @arg SDIOC_AUTO_CMD_ERR_FLAG_CE:   Auto CMD12 CRC error flag
 *           @arg SDIOC_AUTO_CMD_ERR_FLAG_TOE:  Auto CMD12 Timeout error flag
 *           @arg SDIOC_AUTO_CMD_ERR_FLAG_NE:   Auto CMD12 Not Executed flag
 *           @arg SDIOC_AUTO_CMD_ERR_FLAG_ALL:  All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t SDIOC_GetAutoCmdErrorStatus(const CM_SDIOC_TypeDef *SDIOCx, uint16_t u16Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_AUTO_CMD_ERR_FLAG(u16Flag));

    if (0U != (READ_REG16_BIT(SDIOCx->ATCERRST, u16Flag))) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/**
 * @brief  Force the specified auto CMD12 error event.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u16Event                Auto CMD12 error event
 *         This parameter can be one or any combination the following values:
 *           @arg SDIOC_FORCE_AUTO_CMD_ERR_FCMDE:   Force Event for Command Not Issued By Auto CMD12 error
 *           @arg SDIOC_FORCE_AUTO_CMD_ERR_FIE:     Force Event for Auto CMD12 Index error
 *           @arg SDIOC_FORCE_AUTO_CMD_ERR_FEBE:    Force Event for Auto CMD12 End Bit error
 *           @arg SDIOC_FORCE_AUTO_CMD_ERR_FCE:     Force Event for Auto CMD12 CRC error
 *           @arg SDIOC_FORCE_AUTO_CMD_ERR_FTOE:    Force Event for Auto CMD12 Timeout error
 *           @arg SDIOC_FORCE_AUTO_CMD_ERR_FNE:     Force Event for Auto CMD12 Not Executed
 *           @arg SDIOC_FORCE_AUTO_CMD_ERR_ALL:     All of the above
 * @retval None
 */
void SDIOC_ForceAutoCmdErrorEvent(CM_SDIOC_TypeDef *SDIOCx, uint16_t u16Event)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_FORCE_AUTO_CMD_ERR(u16Event));

    WRITE_REG16(SDIOCx->FEA, u16Event);
}

/**
 * @brief  Force the specified error interrupt event.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u16Event                Error interrupt event
 *         This parameter can be one or any combination the following values:
 *           @arg SDIOC_FORCE_ERR_INT_FACE:     Force Event for Auto CMD12 error
 *           @arg SDIOC_FORCE_ERR_INT_FDEBE:    Force Event for Data End Bit error
 *           @arg SDIOC_FORCE_ERR_INT_FDCE:     Force Event for Data CRC error
 *           @arg SDIOC_FORCE_ERR_INT_FDTOE:    Force Event for Data Timeout error
 *           @arg SDIOC_FORCE_ERR_INT_FCIE:     Force Event for Command Index error
 *           @arg SDIOC_FORCE_ERR_INT_FCEBE:    Force Event for Command End Bit error
 *           @arg SDIOC_FORCE_ERR_INT_FCCE:     Force Event for Command CRC error
 *           @arg SDIOC_FORCE_ERR_INT_FCTOE:    Force Event for Command Timeout error
 *           @arg SDIOC_FORCE_ERR_INT_ALL:      All of the above
 * @retval None
 */
void SDIOC_ForceErrorIntEvent(CM_SDIOC_TypeDef *SDIOCx, uint16_t u16Event)
{
    /* Check parameters */
    DDL_ASSERT(IS_SDIOC_UNIT(SDIOCx));
    DDL_ASSERT(IS_SDIOC_FORCE_ERR_INT(u16Event));

    WRITE_REG16(SDIOCx->FEE, u16Event);
}

/**
 * @brief  Send the Go Idle State command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD0_GoIdleState(CM_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        *pu32ErrStatus                  = SDMMC_ERR_NONE;
        stcCmdConfig.u32Argument        = 0UL;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD0_GO_IDLE_STATE;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_NO;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdError(SDIOCx);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Send CID command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD2_AllSendCID(CM_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = 0UL;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD2_ALL_SEND_CID;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R2;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp2(SDIOCx, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the command for asking the card to publish a new relative address(RCA).
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] pu16RCA                Pointer to the new RCA value
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu16RCA == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD3_SendRelativeAddr(CM_SDIOC_TypeDef *SDIOCx, uint16_t *pu16RCA, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;
    uint32_t u32SdMode;

    if ((NULL == pu16RCA) || (NULL == pu32ErrStatus)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = (uint32_t)(*pu16RCA) << 16U;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD3_SEND_RELATIVE_ADDR;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            u32SdMode = SDIOC_GetMode(SDIOCx);
            if (SDIOC_MD_SD != u32SdMode) { /* MMC mode */
                i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
            } else {
                i32Ret = SDMMC_GetCmdResp6(SDIOCx, pu16RCA, pu32ErrStatus);
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Checks switchable function and switch card function.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32Argument             Argument used for the command.
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD6_SwitchFunc(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32Argument, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;
    uint32_t u32SdMode;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument    = u32Argument;
        stcCmdConfig.u16CmdIndex    = SDIOC_CMD6_SWITCH_FUNC;
        stcCmdConfig.u16CmdType     = SDIOC_CMD_TYPE_NORMAL;
        u32SdMode                   = SDIOC_GetMode(SDIOCx);
        if (SDIOC_MD_SD != u32SdMode) { /* MMC mode */
            stcCmdConfig.u16DataLine      = SDIOC_DATA_LINE_DISABLE;
            stcCmdConfig.u16ResponseType  = SDIOC_RESP_TYPE_R1B_R5B;
        } else {
            stcCmdConfig.u16DataLine      = SDIOC_DATA_LINE_ENABLE;
            stcCmdConfig.u16ResponseType  = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        }
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            if (SDIOC_MD_SD != u32SdMode) { /* MMC mode */
                i32Ret = SDMMC_GetCmdResp1Busy(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
            } else {
                i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Select Deselect command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32RCA                  Relative Card Address(RCA)
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD7_SelectDeselectCard(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32RCA, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32RCA;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD7_SELECT_DESELECT_CARD;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1B_R5B;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1Busy(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Interface Condition command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD8_SendInterfaceCond(CM_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;
    uint32_t u32SdMode;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Argument: - [31:12]: Reserved (shall be set to '0')
        - [11:8]: Supply Voltage (VHS) 0x1 (Range: 2.7-3.6 V)
        - [7:0]: Check Pattern (recommended 0xAA) */
        stcCmdConfig.u32Argument        = SDMMC_CMD8_CHECK_PATTERN;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD8_SEND_IF_COND;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        u32SdMode                       = SDIOC_GetMode(SDIOCx);
        if (SDIOC_MD_SD != u32SdMode) { /* MMC mode */
            stcCmdConfig.u16DataLine    = SDIOC_DATA_LINE_ENABLE;
        } else {
            stcCmdConfig.u16DataLine    = SDIOC_DATA_LINE_DISABLE;
        }
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            if (SDIOC_MD_SD != u32SdMode) { /* MMC mode */
                i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
            } else {
                i32Ret = SDMMC_GetCmdResp7(SDIOCx, pu32ErrStatus);
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Send CSD command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32RCA                  Relative Card Address(RCA)
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD9_SendCSD(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32RCA, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32RCA;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD9_SEND_CSD;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R2;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp2(SDIOCx, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Stop Transfer command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD12_StopTrans(CM_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = 0UL;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD12_STOP_TRANSMISSION;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1B_R5B;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1Busy(SDIOCx, SDMMC_CMD_TIMEOUT * 1000UL, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Status command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32RCA                  Relative Card Address(RCA)
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD13_SendStatus(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32RCA, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32RCA;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD13_SEND_STATUS;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Data Block Length command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32BlockLen             Block length
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD16_SetBlockLength(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32BlockLen, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32BlockLen;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD16_SET_BLOCKLEN;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Read Single Block command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32ReadAddr             Data address
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD17_ReadSingleBlock(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32ReadAddr, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32ReadAddr;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD17_READ_SINGLE_BLOCK;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_ENABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Read Multi Block command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32ReadAddr             Data address
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD18_ReadMultipleBlock(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32ReadAddr, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32ReadAddr;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD18_READ_MULTI_BLOCK;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_ENABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Write Single Block command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32WriteAddr            Data address
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD24_WriteSingleBlock(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32WriteAddr, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32WriteAddr;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD24_WRITE_SINGLE_BLOCK;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_ENABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Write Multi Block command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32WriteAddr            Data address
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD25_WriteMultipleBlock(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32WriteAddr, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32WriteAddr;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD25_WRITE_MULTI_BLOCK;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_ENABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Start Address Erase command for SD and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32StartAddr            The start address will be erased
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD32_EraseBlockStartAddr(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32StartAddr, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32StartAddr;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD32_ERASE_WR_BLK_START;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the End Address Erase command for SD and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32EndAddr              The end address will be erased
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD33_EraseBlockEndAddr(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32EndAddr, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32EndAddr;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD33_ERASE_WR_BLK_END;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Erase command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD38_Erase(CM_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = 0UL;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD38_ERASE;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1B_R5B;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1Busy(SDIOCx, SDMMC_MAX_ERASE_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Application command to verify that that the next command
 *         is an application specific command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32Argument             Argument used for the command.
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD55_AppCmd(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32Argument, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32Argument;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD55_APP_CMD;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Bus Width command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32BusWidth             The data bus width
 *         This parameter can be one of the following values:
 *           @arg SDMMC_SCR_BUS_WIDTH_1BIT: 1 bit bus
 *           @arg SDMMC_SCR_BUS_WIDTH_4BIT: 4 bits bus
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_ACMD6_SetBusWidth(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32BusWidth, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32BusWidth;
        stcCmdConfig.u16CmdIndex        = SDIOC_ACMD6_SET_BUS_WIDTH;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Status register command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_ACMD13_SendStatus(CM_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = 0UL;
        stcCmdConfig.u16CmdIndex        = SDIOC_ACMD13_SD_STATUS;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_ENABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the command asking the accessed card to send its operating condition register(OCR).
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32Argument             Argument used for the command.
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_ACMD41_SendOperateCond(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32Argument, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32Argument | SDMMC_ACMD41_VOLT_WIN;
        stcCmdConfig.u16CmdIndex        = SDIOC_ACMD41_SD_APP_OP_COND;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R3_R4;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp3(SDIOCx, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Send SCR command and check the response.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_ACMD51_SendSCR(CM_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = 0UL;
        stcCmdConfig.u16CmdIndex        = SDIOC_ACMD51_SEND_SCR;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_ENABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Sends host capacity support information command.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32Argument             Argument used for the command.
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD1_SendOperateCond(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32Argument, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32Argument;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD1_SEND_OP_COND;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R3_R4;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp3(SDIOCx, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the Start Address Erase command and check the response
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32StartAddr            The start address will be erased
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD35_EraseGroupStartAddr(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32StartAddr, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32StartAddr;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD35_ERASE_GROUP_START;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the End Address Erase command and check the response
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32EndAddr              The end address will be erased
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD36_EraseGroupEndAddr(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32EndAddr, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32EndAddr;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD36_ERASE_GROUP_END;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp1(SDIOCx, SDMMC_CMD_TIMEOUT, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the IO_SEND_OP_COND command for inquiring about the voltage range needed by the I/O card.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] u32Argument             Argument used for the command.
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD5_IOSendOperateCond(CM_SDIOC_TypeDef *SDIOCx, uint32_t u32Argument, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if (NULL == pu32ErrStatus) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        stcCmdConfig.u32Argument        = u32Argument;
        stcCmdConfig.u16CmdIndex        = SDIOC_CMD5_IO_SEND_OP_COND;
        stcCmdConfig.u16CmdType         = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine        = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType    = SDIOC_RESP_TYPE_R3_R4;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        /* Check for error conditions */
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp4(SDIOCx, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the IO_RW_DIRECT command to access a single I/O register.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] pstcCmdArg              Pointer to a @ref stc_sdio_cmd52_arg_t structure
 * @param  [in] u8In                    Data to write
 * @param  [out] pu8Out                 Pointer to buffer to store command response
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error or response(R5) indicate error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pstcCmdArg == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD52_IORwDirect(CM_SDIOC_TypeDef *SDIOCx, const stc_sdio_cmd52_arg_t *pstcCmdArg,
                               uint8_t u8In, uint8_t *pu8Out, uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    uint32_t u32Arg;
    uint32_t u32R5;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if ((NULL == pstcCmdArg) || (NULL == pu32ErrStatus)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Command arguments */
        u32Arg = 0UL;
        u32Arg |= pstcCmdArg->u32RwFlag;
        u32Arg |= ((uint32_t)pstcCmdArg->u8FuncNum << SDIO_CMD52_ARG_FUNC_SHIFT);
        u32Arg |= (pstcCmdArg->u32RegAddr << SDIO_CMD52_ARG_REG_ADDR_SHIFT);
        u32Arg |= pstcCmdArg->u32RawFlag;
        u32Arg |= u8In;

        stcCmdConfig.u32Argument     = u32Arg;
        stcCmdConfig.u16CmdIndex     = SDIOC_CMD52_IO_RW_DIRECT;
        stcCmdConfig.u16CmdType      = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine     = SDIOC_DATA_LINE_DISABLE;
        stcCmdConfig.u16ResponseType = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp5(SDIOCx, pu32ErrStatus);
            if (LL_OK == i32Ret) {
                (void)SDIOC_GetResponse(SDIOCx, SDIOC_RESP_REG_BIT0_31, &u32R5);
                if (NULL != pu8Out) {
                    *pu8Out = (uint8_t)(u32R5 & 0x000000FFUL);
                }
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Send the IO_RW_EXTENDED command to access a large number of I/O registers.
 * @param  [in] SDIOCx                  Pointer to SDIOC unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_SDIOC1:            SDIOC unit 1 instance
 *           @arg CM_SDIOC2:            SDIOC unit 2 instance
 * @param  [in] pstcCmdArg              Pointer to a @ref stc_sdio_cmd53_arg_t structure
 * @param  [out] pu32ErrStatus          Pointer to the error state value
 * @retval int32_t:
 *           - LL_OK: Command send completed
 *           - LL_ERR: Refer to pu32ErrStatus for the reason of error or response(R5) indicate error
 *           - LL_ERR_INVD_PARAM: SDIOCx == NULL or pstcCmdArg == NULL or pu32ErrStatus == NULL
 *           - LL_ERR_TIMEOUT: Wait timeout
 */
int32_t SDMMC_CMD53_IORwExtended(CM_SDIOC_TypeDef *SDIOCx, const stc_sdio_cmd53_arg_t *pstcCmdArg,
                                 uint32_t *pu32ErrStatus)
{
    int32_t i32Ret;
    uint32_t u32Arg;
    stc_sdioc_cmd_config_t stcCmdConfig;

    if ((NULL == pstcCmdArg) || (NULL == pu32ErrStatus)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Command arguments */
        u32Arg = 0UL;
        u32Arg |= pstcCmdArg->u32RwFlag;
        u32Arg |= ((uint32_t)pstcCmdArg->u8FuncNum << SDIO_CMD53_ARG_FUNC_SHIFT);
        u32Arg |= pstcCmdArg->u32BlockMode;
        u32Arg |= pstcCmdArg->u32OperateCode;
        u32Arg |= (pstcCmdArg->u32RegAddr << SDIO_CMD53_ARG_REG_ADDR_SHIFT);

        stcCmdConfig.u32Argument     = u32Arg;
        stcCmdConfig.u16CmdIndex     = SDIOC_CMD53_IO_RW_EXTENDED;
        stcCmdConfig.u16CmdType      = SDIOC_CMD_TYPE_NORMAL;
        stcCmdConfig.u16DataLine     = SDIOC_DATA_LINE_ENABLE;
        stcCmdConfig.u16ResponseType = SDIOC_RESP_TYPE_R1_R5_R6_R7;
        i32Ret = SDIOC_SendCommand(SDIOCx, &stcCmdConfig);
        if (LL_OK == i32Ret) {
            i32Ret = SDMMC_GetCmdResp5(SDIOCx, pu32ErrStatus);
        }
    }

    return i32Ret;
}

/**
 * @}
 */

#endif /* LL_SDIOC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
