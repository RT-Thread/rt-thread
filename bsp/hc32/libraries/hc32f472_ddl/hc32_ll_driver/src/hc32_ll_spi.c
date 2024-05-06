/**
 *******************************************************************************
 * @file  hc32_ll_spi.c
 * @brief This file provides firmware functions to manage the Serial Peripheral
 *        Interface(SPI).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Add SPI_SetSckPolarity,SPI_SetSckPhase functions
                                    Modify return type of function SPI_DeInit
   2023-12-15       CDT             Modify some assert
                                    Rename some API SPI_xxxConfig as SPI_Setxxx
                                    Add Send restriction in SPI_TxRx function
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
#include "hc32_ll_spi.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_SPI SPI
 * @brief Serial Peripheral Interface Driver Library
 * @{
 */

#if (LL_SPI_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SPI_Local_Macros SPI Local Macros
 * @{
 */
#define SPI_CFG1_DEFAULT        (0x00000010UL)
#define SPI_CFG2_DEFAULT        (0x00000F1DUL)

#define SPI_SS0_VALID_CFG       (0UL)
#define SPI_SS1_VALID_CFG       (SPI_CFG2_SSA_0)
#define SPI_SS2_VALID_CFG       (SPI_CFG2_SSA_1)
#define SPI_SS3_VALID_CFG       (SPI_CFG2_SSA_0 | SPI_CFG2_SSA_1)

#define SPI_SR_DEFAULT          (0x00000020UL)

#define SPI_RMU_TIMEOUT         (100U)

/**
 * @defgroup SPI_Check_Parameters_Validity SPI Check Parameters Validity
 * @{
 */

/*! Parameter valid check for SPI peripheral */
#define IS_VALID_SPI_UNIT(x)                                                   \
(   ((x) == CM_SPI1)                        ||                                 \
    ((x) == CM_SPI2)                        ||                                 \
    ((x) == CM_SPI3)                        ||                                 \
    ((x) == CM_SPI4))

/*! Parameter valid check for SPI wire mode */
#define IS_SPI_WIRE_MD(x)                                                      \
(   ((x) == SPI_4_WIRE)                     ||                                 \
    ((x) == SPI_3_WIRE))

/*! Parameter valid check for SPI transfer mode */
#define IS_SPI_TRANS_MD(x)                                                     \
(   ((x) == SPI_FULL_DUPLEX)                ||                                 \
    ((x) == SPI_SEND_ONLY))

/*! Parameter valid check for SPI master slave mode */
#define IS_SPI_MASTER_SLAVE(x)                                                 \
(   ((x) == SPI_SLAVE)                      ||                                 \
    ((x) == SPI_MASTER))

/*! Parameter valid check for SPI loopback mode */
#define IS_SPI_SPLPBK(x)                                                       \
(   ((x) == SPI_LOOPBACK_INVD)              ||                                 \
    ((x) == SPI_LOOPBACK_MOSI_INVT)         ||                                 \
    ((x) == SPI_LOOPBACK_MOSI))

/*! Parameter valid check for SPI communication suspend function status */
#define IS_SPI_SUSPD_MD_STAT(x)                                                \
(   ((x) == SPI_COM_SUSP_FUNC_OFF)          ||                                 \
    ((x) == SPI_COM_SUSP_FUNC_ON))

/*! Parameter valid check for SPI data frame level */
#define IS_SPI_DATA_FRAME(x)                                                   \
(   ((x) == SPI_1_FRAME)                     ||                                \
    ((x) == SPI_2_FRAME)                     ||                                \
    ((x) == SPI_3_FRAME)                     ||                                \
    ((x) == SPI_4_FRAME))

/*! Parameter valid check for SPI fault detect function status */
#define IS_SPI_MD_FAULT_DETECT_CMD(x)                                          \
(   ((x) == SPI_MD_FAULT_DETECT_DISABLE)    ||                                 \
    ((x) == SPI_MD_FAULT_DETECT_ENABLE))

/*! Parameter valid check for SPI parity check mode */
#define IS_SPI_PARITY_CHECK(x)                                                 \
(   ((x) == SPI_PARITY_INVD)                ||                                 \
    ((x) == SPI_PARITY_EVEN)                ||                                 \
    ((x) == SPI_PARITY_ODD))

/*! Parameter valid check for SPI interval time delay */
#define IS_SPI_INTERVAL_DELAY(x)                                               \
(   ((x) == SPI_INTERVAL_TIME_1SCK)         ||                                 \
    ((x) == SPI_INTERVAL_TIME_2SCK)         ||                                 \
    ((x) == SPI_INTERVAL_TIME_3SCK)         ||                                 \
    ((x) == SPI_INTERVAL_TIME_4SCK)         ||                                 \
    ((x) == SPI_INTERVAL_TIME_5SCK)         ||                                 \
    ((x) == SPI_INTERVAL_TIME_6SCK)         ||                                 \
    ((x) == SPI_INTERVAL_TIME_7SCK)         ||                                 \
    ((x) == SPI_INTERVAL_TIME_8SCK))

/*! Parameter valid check for SPI release time delay */
#define IS_SPI_RELEASE_DELAY(x)                                                \
(   ((x) == SPI_RELEASE_TIME_1SCK)          ||                                 \
    ((x) == SPI_RELEASE_TIME_2SCK)          ||                                 \
    ((x) == SPI_RELEASE_TIME_3SCK)          ||                                 \
    ((x) == SPI_RELEASE_TIME_4SCK)          ||                                 \
    ((x) == SPI_RELEASE_TIME_5SCK)          ||                                 \
    ((x) == SPI_RELEASE_TIME_6SCK)          ||                                 \
    ((x) == SPI_RELEASE_TIME_7SCK)          ||                                 \
    ((x) == SPI_RELEASE_TIME_8SCK))

/*! Parameter valid check for SPI Setup time delay delay */
#define IS_SPI_SETUP_DELAY(x)                                                  \
(   ((x) == SPI_SETUP_TIME_1SCK)            ||                                 \
    ((x) == SPI_SETUP_TIME_2SCK)            ||                                 \
    ((x) == SPI_SETUP_TIME_3SCK)            ||                                 \
    ((x) == SPI_SETUP_TIME_4SCK)            ||                                 \
    ((x) == SPI_SETUP_TIME_5SCK)            ||                                 \
    ((x) == SPI_SETUP_TIME_6SCK)            ||                                 \
    ((x) == SPI_SETUP_TIME_7SCK)            ||                                 \
    ((x) == SPI_SETUP_TIME_8SCK))

/*! Parameter valid check for SPI read data register target buffer */
#define IS_SPI_RD_TARGET_BUFF(x)                                               \
(   ((x) == SPI_RD_TARGET_RD_BUF)           ||                                 \
    ((x) == SPI_RD_TARGET_WR_BUF))

/*! Parameter valid check for SPI mode */
#define IS_SPI_SPI_MD(x)                                                       \
(   ((x) == SPI_MD_0)                       ||                                 \
    ((x) == SPI_MD_1)                       ||                                 \
    ((x) == SPI_MD_2)                       ||                                 \
    ((x) == SPI_MD_3))

/*! Parameter valid check for SPI SCK Polarity */
#define IS_SPI_SCK_POLARITY(x)                                                 \
(   ((x) == SPI_SCK_POLARITY_LOW)           ||                                 \
    ((x) == SPI_SCK_POLARITY_HIGH))

/*! Parameter valid check for SPI SCK Phase */
#define IS_SPI_SCK_PHASE(x)                                                    \
(   ((x) == SPI_SCK_PHASE_ODD_EDGE_SAMPLE)  ||                                 \
    ((x) == SPI_SCK_PHASE_EVEN_EDGE_SAMPLE))

/*! Parameter valid check for SPI SS signal */
#define IS_SPI_SS_PIN(x)                                                       \
(   ((x) == SPI_PIN_SS0)                    ||                                 \
    ((x) == SPI_PIN_SS1)                    ||                                 \
    ((x) == SPI_PIN_SS2)                    ||                                 \
    ((x) == SPI_PIN_SS3))

/*! Parameter valid check for SPI SS valid level */
#define IS_SPI_SS_VALID_LVL(x)                                                 \
(   ((x) == SPI_SS_VALID_LVL_HIGH)          ||                                 \
    ((x) == SPI_SS_VALID_LVL_LOW))

/*! Parameter valid check for SPI baudrate prescaler */
#define IS_SPI_CLK_DIV(x)                                                      \
(   ((x) == SPI_BR_CLK_DIV2)                ||                                 \
    ((x) == SPI_BR_CLK_DIV4)                ||                                 \
    ((x) == SPI_BR_CLK_DIV6)                ||                                 \
    ((x) == SPI_BR_CLK_DIV8)                ||                                 \
    ((x) == SPI_BR_CLK_DIV10)               ||                                 \
    ((x) == SPI_BR_CLK_DIV12)               ||                                 \
    ((x) == SPI_BR_CLK_DIV14)               ||                                 \
    ((x) == SPI_BR_CLK_DIV16)               ||                                 \
    ((x) == SPI_BR_CLK_DIV18)               ||                                 \
    ((x) == SPI_BR_CLK_DIV20)               ||                                 \
    ((x) == SPI_BR_CLK_DIV22)               ||                                 \
    ((x) == SPI_BR_CLK_DIV24)               ||                                 \
    ((x) == SPI_BR_CLK_DIV26)               ||                                 \
    ((x) == SPI_BR_CLK_DIV28)               ||                                 \
    ((x) == SPI_BR_CLK_DIV30)               ||                                 \
    ((x) == SPI_BR_CLK_DIV32)               ||                                 \
    ((x) == SPI_BR_CLK_DIV36)               ||                                 \
    ((x) == SPI_BR_CLK_DIV40)               ||                                 \
    ((x) == SPI_BR_CLK_DIV44)               ||                                 \
    ((x) == SPI_BR_CLK_DIV48)               ||                                 \
    ((x) == SPI_BR_CLK_DIV52)               ||                                 \
    ((x) == SPI_BR_CLK_DIV56)               ||                                 \
    ((x) == SPI_BR_CLK_DIV60)               ||                                 \
    ((x) == SPI_BR_CLK_DIV64)               ||                                 \
    ((x) == SPI_BR_CLK_DIV72)               ||                                 \
    ((x) == SPI_BR_CLK_DIV80)               ||                                 \
    ((x) == SPI_BR_CLK_DIV88)               ||                                 \
    ((x) == SPI_BR_CLK_DIV96)               ||                                 \
    ((x) == SPI_BR_CLK_DIV104)              ||                                 \
    ((x) == SPI_BR_CLK_DIV112)              ||                                 \
    ((x) == SPI_BR_CLK_DIV120)              ||                                 \
    ((x) == SPI_BR_CLK_DIV128)              ||                                 \
    ((x) == SPI_BR_CLK_DIV144)              ||                                 \
    ((x) == SPI_BR_CLK_DIV160)              ||                                 \
    ((x) == SPI_BR_CLK_DIV176)              ||                                 \
    ((x) == SPI_BR_CLK_DIV192)              ||                                 \
    ((x) == SPI_BR_CLK_DIV208)              ||                                 \
    ((x) == SPI_BR_CLK_DIV224)              ||                                 \
    ((x) == SPI_BR_CLK_DIV240)              ||                                 \
    ((x) == SPI_BR_CLK_DIV256))

/*! Parameter valid check for SPI data bits */
#define IS_SPI_DATA_SIZE(x)                                                    \
(   ((x) == SPI_DATA_SIZE_4BIT)             ||                                 \
    ((x) == SPI_DATA_SIZE_5BIT)             ||                                 \
    ((x) == SPI_DATA_SIZE_6BIT)             ||                                 \
    ((x) == SPI_DATA_SIZE_7BIT)             ||                                 \
    ((x) == SPI_DATA_SIZE_8BIT)             ||                                 \
    ((x) == SPI_DATA_SIZE_9BIT)             ||                                 \
    ((x) == SPI_DATA_SIZE_10BIT)            ||                                 \
    ((x) == SPI_DATA_SIZE_11BIT)            ||                                 \
    ((x) == SPI_DATA_SIZE_12BIT)            ||                                 \
    ((x) == SPI_DATA_SIZE_13BIT)            ||                                 \
    ((x) == SPI_DATA_SIZE_14BIT)            ||                                 \
    ((x) == SPI_DATA_SIZE_15BIT)            ||                                 \
    ((x) == SPI_DATA_SIZE_16BIT)            ||                                 \
    ((x) == SPI_DATA_SIZE_20BIT)            ||                                 \
    ((x) == SPI_DATA_SIZE_24BIT)            ||                                 \
    ((x) == SPI_DATA_SIZE_32BIT))

/*! Parameter valid check for SPI LSB MSB mode */
#define IS_SPI_FIRST_BIT(x)                                                    \
(   ((x) == SPI_FIRST_MSB)                  ||                                 \
    ((x) == SPI_FIRST_LSB))

/*! Parameter valid check for SPI Communication mode */
#define IS_SPI_COMM_MD(x)                                                      \
(   ((x) == SPI_COMM_MD_NORMAL)             ||                                 \
    ((x) == SPI_COMM_MD_CONT))

/*! Parameter valid check for interrupt flag */
#define IS_SPI_INT(x)                                                          \
(   ((x) != 0UL)                            &&                                 \
    (((x) | SPI_INT_ALL) == SPI_INT_ALL))

/*! Parameter valid check for SPI status flag */
#define IS_SPI_FLAG(x)                                                         \
(   ((x) != 0UL)                            &&                                 \
    (((x) | SPI_FLAG_ALL) == SPI_FLAG_ALL))

/*! Parameter valid check for SPI status flag for clear */
#define IS_SPI_CLR_FLAG(x)                                                     \
(   ((x) != 0UL)                            &&                                 \
    (((x) | SPI_FLAG_CLR_ALL) == SPI_FLAG_CLR_ALL))

/*! Parameter valid check for SPI command*/
#define IS_SPI_CMD_ALLOWED(x)                                                  \
(   (READ_REG32_BIT(SPIx->SR, SPI_FLAG_MD_FAULT) == 0UL)    ||                 \
    ((x) == DISABLE))

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
 * @defgroup SPI_Local_Func SPI Local Functions
 * @{
 */

/**
 * @brief  SPI check status.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  u32FlagMask        Bit mask of status flag.
 * @param  [in]  u32Value           Valid value of the status.
 * @param  [in]  u32Timeout         Timeout value.
 * @retval int32_t:
 *         - LL_OK:                 No errors occurred.
 *         - LL_ERR_TIMEOUT:        SPI transmit timeout.
 */
static int32_t SPI_WaitStatus(const CM_SPI_TypeDef *SPIx, uint32_t u32FlagMask, uint32_t u32Value, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_OK;

    while (READ_REG32_BIT(SPIx->SR, u32FlagMask) != u32Value) {
        if (u32Timeout == 0UL) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
        u32Timeout--;
    }
    return i32Ret;
}

/**
 * @brief  SPI master release delay.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  u32TransMode       SPI transfer mode @ref SPI_Trans_Mode_Define
 * @retval None
 * @note   The delay while CPHA = 0 and full duplex mode in continue communication mode(1 SCK).
 * @note   The delay while send only mode in continue communication mode(x SCK).
 */
static void SPI_MasterReleaseDelay(CM_SPI_TypeDef *SPIx, uint32_t u32TransMode)
{
    uint32_t u32BusFreq, u32SpiDiv, u32DataBits;
    uint32_t u32Speed, u32Temp;
    uint32_t u32DelayTime = 1U;

    u32BusFreq = SystemCoreClock >> (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS);
    u32SpiDiv = (((READ_REG32_BIT(SPIx->CFG1, SPI_CFG1_CLKDIV) >> SPI_CFG1_CLKDIV_POS) + 1U) << 1U);
    u32SpiDiv *= (1UL << (READ_REG32_BIT(SPIx->CFG2, SPI_CFG2_MBR) >> SPI_CFG2_MBR_POS));
    u32Speed = u32BusFreq / u32SpiDiv;
    if (SPI_FULL_DUPLEX == u32TransMode) {
        /* Communication speed below 1Mhz */
        if ((u32Speed < 1000000UL) && (u32Speed > 0U)) {
            u32DelayTime = 1000000UL / u32Speed;
            if (0U != (1000000UL % u32Speed)) {
                u32DelayTime += 1U;
            }
        }
    } else {
        if (SPI_CFG2_MSSIE == READ_REG32_BIT(SPIx->CFG2, SPI_CFG2_MSSIE)) {
            u32Temp = (READ_REG32_BIT(SPIx->CFG1, SPI_CFG1_MSSI) >> SPI_CFG1_MSSI_POS);
        } else {
            u32Temp = 0U;
        }
        if (0U == READ_REG32_BIT(SPIx->CFG2, SPI_CFG2_CPHA)) {
            u32Temp += 1U;
        }
        u32DataBits = READ_REG32_BIT(SPIx->CFG2, SPI_CFG2_DSIZE);
        if (u32DataBits <= SPI_DATA_SIZE_16BIT) {
            u32Temp += (u32DataBits >> SPI_CFG2_DSIZE_POS) + 4U;
        } else if (u32DataBits == SPI_DATA_SIZE_20BIT) {
            u32Temp += 20U;
        } else if (u32DataBits == SPI_DATA_SIZE_24BIT) {
            u32Temp += 24U;
        } else {
            u32Temp += 32U;
        }
        /* Total wait time below 1us */
        u32Speed = u32Speed / u32Temp;
        if ((u32Speed < 1000000UL) && (u32Speed > 0U)) {
            u32DelayTime = 1000000UL / u32Speed;
            if (0U != (1000000UL % u32Speed)) {
                u32DelayTime += 1U;
            }
        }
    }
    DDL_DelayUS(u32DelayTime);
}

/**
 * @brief  SPI transmit and receive data in full duplex mode.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  pvTxBuf            The pointer to the buffer which contains the data to be sent.
 * @param  [out] pvRxBuf            The pointer to the buffer which the received data will be stored.
 * @param  [in]  u32Len             The length of the data in byte or half word.
 * @param  [in]  u32Timeout         Timeout value.
 * @retval int32_t:
 *         - LL_OK:                 No errors occurred
 *         - LL_ERR_TIMEOUT:        SPI transmit and receive timeout.
 */
static int32_t SPI_TxRx(CM_SPI_TypeDef *SPIx, const void *pvTxBuf, void *pvRxBuf, uint32_t u32Len, uint32_t u32Timeout)
{
    uint32_t u32BitSize;
    __IO uint32_t u32TxCnt = 0U, u32RxCnt = 0U;
    __IO uint32_t u32Count = 0U;
    int32_t i32Ret = LL_OK;
    uint32_t u32Tmp;
    __UNUSED __IO uint32_t u32Read;
    __IO uint32_t u32TxAllow = 1U;
    uint32_t u32MSMode;
    __IO uint32_t u32FrameCnt;
    uint32_t u32FrameNum = READ_REG32_BIT(SPIx->CFG1, SPI_CFG1_FTHLV) + 1UL;
    DDL_ASSERT(0UL == (u32Len % u32FrameNum));

    u32MSMode = READ_REG32_BIT(SPIx->CR, SPI_CR_MSTR);
    /* Get data bit size, SPI_DATA_SIZE_4BIT ~ SPI_DATA_SIZE_32BIT */
    u32BitSize = READ_REG32_BIT(SPIx->CFG2, SPI_CFG2_DSIZE);
    while (u32RxCnt < u32Len) {
        /* Tx data */
        if (u32TxCnt < u32Len) {
            /* Wait TX buffer empty. */
            i32Ret = SPI_WaitStatus(SPIx, SPI_FLAG_TX_BUF_EMPTY, SPI_FLAG_TX_BUF_EMPTY, 0U);
            if ((i32Ret == LL_OK) && (((u32MSMode == SPI_MASTER) && (u32TxAllow == 1U)) || (u32MSMode == SPI_SLAVE))) {
                if (pvTxBuf != NULL) {
                    u32FrameCnt = 0UL;
                    while (u32FrameCnt < u32FrameNum) {
                        if (u32BitSize <= SPI_DATA_SIZE_8BIT) {
                            /* SPI_DATA_SIZE_4BIT ~ SPI_DATA_SIZE_8BIT */
                            WRITE_REG32(SPIx->DR, ((const uint8_t *)pvTxBuf)[u32TxCnt]);
                        } else if (u32BitSize <= SPI_DATA_SIZE_16BIT) {
                            /* SPI_DATA_SIZE_9BIT ~ SPI_DATA_SIZE_16BIT */
                            WRITE_REG32(SPIx->DR, ((const uint16_t *)pvTxBuf)[u32TxCnt]);
                        } else {
                            /* SPI_DATA_SIZE_20BIT ~ SPI_DATA_SIZE_32BIT */
                            WRITE_REG32(SPIx->DR, ((const uint32_t *)pvTxBuf)[u32TxCnt]);
                        }
                        u32FrameCnt++;
                        u32TxCnt++;
                    }
                } else {
                    u32FrameCnt = 0UL;
                    while (u32FrameCnt < u32FrameNum) {
                        WRITE_REG32(SPIx->DR, 0xFFFFFFFFUL);
                        u32FrameCnt++;
                        u32TxCnt++;
                    }
                }
                u32TxAllow = 0U;
            }
        }

        /* RX data */
        i32Ret = SPI_WaitStatus(SPIx, SPI_FLAG_RX_BUF_FULL, SPI_FLAG_RX_BUF_FULL, 0U);
        if (i32Ret == LL_OK) {
            if (pvRxBuf != NULL) {
                u32FrameCnt = 0UL;
                while (u32FrameCnt < u32FrameNum) {
                    u32Tmp = READ_REG32(SPIx->DR);
                    if (u32BitSize <= SPI_DATA_SIZE_8BIT) {
                        /* SPI_DATA_SIZE_4BIT ~ SPI_DATA_SIZE_8BIT */
                        ((uint8_t *)pvRxBuf)[u32RxCnt] = (uint8_t)u32Tmp;
                    } else if (u32BitSize <= SPI_DATA_SIZE_16BIT) {
                        /* SPI_DATA_SIZE_9BIT ~ SPI_DATA_SIZE_16BIT */
                        ((uint16_t *)pvRxBuf)[u32RxCnt] = (uint16_t)u32Tmp;
                    } else {
                        /* SPI_DATA_SIZE_20BIT ~ SPI_DATA_SIZE_32BIT */
                        ((uint32_t *)pvRxBuf)[u32RxCnt] = (uint32_t)u32Tmp;
                    }
                    u32FrameCnt++;
                    u32RxCnt++;
                }
            } else {
                /* Dummy read */
                u32FrameCnt = 0UL;
                while (u32FrameCnt < u32FrameNum) {
                    u32Read = READ_REG32(SPIx->DR);
                    u32FrameCnt++;
                    u32RxCnt++;
                }
            }
            u32TxAllow = 1U;
            u32Count = 0U;
        }

        /* check timeout */
        if (u32Count > u32Timeout) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
        u32Count++;
    }

    if ((SPI_MASTER == READ_REG32_BIT(SPIx->CR, SPI_CR_MSTR)) && (i32Ret == LL_OK)) {
        if (SPI_COMM_MD_NORMAL == READ_REG32_BIT(SPIx->CFG1, SPI_CFG1_CTMDS)) {
            i32Ret = SPI_WaitStatus(SPIx, SPI_FLAG_IDLE, 0UL, u32Timeout);
        } else {
            if (0U == READ_REG32_BIT(SPIx->CFG2, SPI_CFG2_CPHA)) {
                SPI_MasterReleaseDelay(SPIx, SPI_FULL_DUPLEX);
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  SPI send data only.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  pvTxBuf            The pointer to the buffer which contains the data to be sent.
 * @param  [in]  u32Len             The length of the data in byte or half word or word.
 * @param  [in]  u32Timeout         Timeout value.
 * @retval int32_t:
 *         - LL_OK:                 No errors occurred.
 *         - LL_ERR_TIMEOUT:        SPI transmit timeout.
 */
static int32_t SPI_Tx(CM_SPI_TypeDef *SPIx, const void *pvTxBuf, uint32_t u32Len, uint32_t u32Timeout)
{
    __IO uint32_t u32TxCnt = 0U;
    uint32_t u32BitSize;
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32FrameCnt;
    uint32_t u32FrameNum = READ_REG32_BIT(SPIx->CFG1, SPI_CFG1_FTHLV) + 1UL;
    DDL_ASSERT(0UL == (u32Len % u32FrameNum));

    /* Get data bit size, SPI_DATA_SIZE_4BIT ~ SPI_DATA_SIZE_32BIT */
    u32BitSize = READ_REG32_BIT(SPIx->CFG2, SPI_CFG2_DSIZE);
    while (u32TxCnt < u32Len) {
        u32FrameCnt = 0UL;
        while (u32FrameCnt < u32FrameNum) {
            if (u32BitSize <= SPI_DATA_SIZE_8BIT) {
                /* SPI_DATA_SIZE_4BIT ~ SPI_DATA_SIZE_8BIT */
                WRITE_REG32(SPIx->DR, ((const uint8_t *)pvTxBuf)[u32TxCnt]);
            } else if (u32BitSize <= SPI_DATA_SIZE_16BIT) {
                /* SPI_DATA_SIZE_9BIT ~ SPI_DATA_SIZE_16BIT */
                WRITE_REG32(SPIx->DR, ((const uint16_t *)pvTxBuf)[u32TxCnt]);
            } else {
                /* SPI_DATA_SIZE_20BIT ~ SPI_DATA_SIZE_32BIT */
                WRITE_REG32(SPIx->DR, ((const uint32_t *)pvTxBuf)[u32TxCnt]);
            }
            u32FrameCnt++;
            u32TxCnt++;
        }
        /* Wait TX buffer empty. */
        i32Ret = SPI_WaitStatus(SPIx, SPI_FLAG_TX_BUF_EMPTY, SPI_FLAG_TX_BUF_EMPTY, u32Timeout);
        if (i32Ret != LL_OK) {
            break;
        }
    }

    if ((SPI_MASTER == READ_REG32_BIT(SPIx->CR, SPI_CR_MSTR)) && (i32Ret == LL_OK)) {
        if (SPI_COMM_MD_NORMAL == READ_REG32_BIT(SPIx->CFG1, SPI_CFG1_CTMDS)) {
            i32Ret = SPI_WaitStatus(SPIx, SPI_FLAG_IDLE, 0UL, u32Timeout);
        } else {
            SPI_MasterReleaseDelay(SPIx, SPI_SEND_ONLY);
        }
    }

    return i32Ret;
}

/**
 * @}
 */

/**
 * @defgroup SPI_Global_Functions SPI Global Functions
 * @{
 */

/**
 * @brief  Initializes the SPI peripheral according to the specified parameters
 *         in the structure stc_spi_init.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  pstcSpiInit        Pointer to a stc_spi_init_t structure that contains
 *                                  the configuration information for the SPI.
 * @retval int32_t:
 *         - LL_OK:                 No errors occurred
 *         - LL_ERR_INVD_PARAM:     pstcSpiInit == NULL or configuration parameter error.
 * @note   -In the 3-Wire slave mode and CHPA = 0, the function needs to cooperate with other processes to communicate properly.
 * @note   -The parameter u32BaudRatePrescaler is invalid while slave mode
 */
int32_t SPI_Init(CM_SPI_TypeDef *SPIx, const stc_spi_init_t *pstcSpiInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));

    if (NULL != pstcSpiInit) {
        DDL_ASSERT(IS_SPI_WIRE_MD(pstcSpiInit->u32WireMode));
        DDL_ASSERT(IS_SPI_TRANS_MD(pstcSpiInit->u32TransMode));
        DDL_ASSERT(IS_SPI_MASTER_SLAVE(pstcSpiInit->u32MasterSlave));
        DDL_ASSERT(IS_SPI_MD_FAULT_DETECT_CMD(pstcSpiInit->u32ModeFaultDetect));
        DDL_ASSERT(IS_SPI_PARITY_CHECK(pstcSpiInit->u32Parity));
        DDL_ASSERT(IS_SPI_SPI_MD(pstcSpiInit->u32SpiMode));
        DDL_ASSERT(IS_SPI_CLK_DIV(pstcSpiInit->u32BaudRatePrescaler));
        DDL_ASSERT(IS_SPI_DATA_SIZE(pstcSpiInit->u32DataBits));
        DDL_ASSERT(IS_SPI_FIRST_BIT(pstcSpiInit->u32FirstBit));
        DDL_ASSERT(IS_SPI_SUSPD_MD_STAT(pstcSpiInit->u32SuspendMode));
        DDL_ASSERT(IS_SPI_DATA_FRAME(pstcSpiInit->u32FrameLevel));

        /* Configuration parameter check */
        if ((SPI_MASTER == pstcSpiInit->u32MasterSlave) && (SPI_MD_FAULT_DETECT_ENABLE == pstcSpiInit->u32ModeFaultDetect)) {
            /* pstcSpiInit->u32ModeFaultDetect can not be SPI_MD_FAULT_DETECT_ENABLE in master mode */
        } else {
            WRITE_REG32(SPIx->CR, pstcSpiInit->u32WireMode | pstcSpiInit->u32TransMode | pstcSpiInit->u32MasterSlave | \
                        pstcSpiInit->u32SuspendMode | pstcSpiInit->u32ModeFaultDetect | pstcSpiInit->u32Parity);
            if (SPI_MASTER == pstcSpiInit->u32MasterSlave) {
                MODIFY_REG32(SPIx->CFG1, (SPI_CFG1_FTHLV | SPI_CFG1_CLKDIV),
                             (pstcSpiInit->u32FrameLevel | (pstcSpiInit->u32BaudRatePrescaler & SPI_CFG1_CLKDIV)));
                WRITE_REG32(SPIx->CFG2, pstcSpiInit->u32SpiMode | pstcSpiInit->u32FirstBit | pstcSpiInit->u32DataBits | \
                            (pstcSpiInit->u32BaudRatePrescaler & SPI_CFG2_MBR));
            } else {
                MODIFY_REG32(SPIx->CFG1, SPI_CFG1_FTHLV, pstcSpiInit->u32FrameLevel);
                WRITE_REG32(SPIx->CFG2, pstcSpiInit->u32SpiMode | pstcSpiInit->u32FirstBit | pstcSpiInit->u32DataBits);
            }

            i32Ret = LL_OK;
        }
    }
    return i32Ret;
}

/**
 * @brief  De-initializes the SPI peripheral.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          Works timeout.
 */
int32_t SPI_DeInit(CM_SPI_TypeDef *SPIx)
{
    uint32_t i;
    int32_t i32Ret = LL_OK;
    __IO uint8_t u8TimeOut = 0U;
    __IO uint32_t *bCM_RMU_FRST1_SPIx = NULL;
    const uint32_t au32SPIx[] = {CM_SPI1_BASE, CM_SPI2_BASE, CM_SPI3_BASE, CM_SPI4_BASE};

    /* Check RMU_FRST register protect */
    DDL_ASSERT((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1);
    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));

    for (i = 0UL; i < ARRAY_SZ(au32SPIx); i++) {
        if ((uint32_t)SPIx == au32SPIx[i]) {
            bCM_RMU_FRST1_SPIx = (__IO uint32_t *)((uint32_t)&bCM_RMU->FRST1_b.SPI1 + (i << 2));
            break;
        }
    }

    /* Reset SPI */
    WRITE_REG32(*bCM_RMU_FRST1_SPIx, 0UL);

    /* Ensure reset procedure is completed */
    while (READ_REG32(*bCM_RMU_FRST1_SPIx) != 1UL) {
        u8TimeOut++;
        if (u8TimeOut > SPI_RMU_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }
    return i32Ret;
}

/**
 * @brief  Set a default value for the SPI initialization structure.
 * @param  [in]  pstcSpiInit        Pointer to a stc_spi_init_t structure that
 *                                  contains configuration information.
 * @retval int32_t:
 *         - LL_OK:                 No errors occurred.
 *         - LL_ERR_INVD_PARAM:     pstcSpiInit == NULL.
 */
int32_t SPI_StructInit(stc_spi_init_t *pstcSpiInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcSpiInit) {
        pstcSpiInit->u32WireMode          = SPI_4_WIRE;
        pstcSpiInit->u32TransMode         = SPI_FULL_DUPLEX;
        pstcSpiInit->u32MasterSlave       = SPI_MASTER;
        pstcSpiInit->u32ModeFaultDetect   = SPI_MD_FAULT_DETECT_DISABLE;
        pstcSpiInit->u32Parity            = SPI_PARITY_INVD;
        pstcSpiInit->u32SpiMode           = SPI_MD_0;
        pstcSpiInit->u32BaudRatePrescaler = SPI_BR_CLK_DIV8;
        pstcSpiInit->u32DataBits          = SPI_DATA_SIZE_8BIT;
        pstcSpiInit->u32FirstBit          = SPI_FIRST_MSB;
        pstcSpiInit->u32SuspendMode       = SPI_COM_SUSP_FUNC_OFF;
        pstcSpiInit->u32FrameLevel        = SPI_1_FRAME;
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Enable or disable SPI interrupt.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  u32IntType         SPI interrupt type. Can be one or any
 *                                  combination of the parameter @ref SPI_Int_Type_Define
 * @param  [in]  enNewState         An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void SPI_IntCmd(CM_SPI_TypeDef *SPIx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_SPI_INT(u32IntType));

    if (enNewState == ENABLE) {
        SET_REG32_BIT(SPIx->CR, u32IntType);
    } else {
        CLR_REG32_BIT(SPIx->CR, u32IntType);
    }
}

/**
 * @brief  SPI function enable or disable.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  enNewState         An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void SPI_Cmd(CM_SPI_TypeDef *SPIx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_SPI_CMD_ALLOWED(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(SPIx->CR, SPI_CR_SPE);
    } else {
        CLR_REG32_BIT(SPIx->CR, SPI_CR_SPE);
    }
}

/**
 * @brief  Write SPI data register.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  u32Data            The data will be written to the data register.
 * @retval None.
 */
void SPI_WriteData(CM_SPI_TypeDef *SPIx, uint32_t u32Data)
{
    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));
    WRITE_REG32(SPIx->DR, u32Data);
}

/**
 * @brief  Read SPI data register.
 * @param  [in]  SPIx               SPI unit
 *   @arg  CM_SPIx or CM_SPI
 * @retval uint32_t                 A 32-bit data of SPI data register.
 */
uint32_t SPI_ReadData(const CM_SPI_TypeDef *SPIx)
{
    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));

    return READ_REG32(SPIx->DR);
}

/**
 * @brief  SPI get status flag.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  u32Flag            SPI state flag. Can be one or any
 *                                  combination of the parameter of @ref SPI_State_Flag_Define
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t SPI_GetStatus(const CM_SPI_TypeDef *SPIx, uint32_t u32Flag)
{
    en_flag_status_t enFlag = RESET;
    uint32_t u32Status;

    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_SPI_FLAG(u32Flag));

    u32Status = READ_REG32(SPIx->SR);
    if (SPI_FLAG_IDLE == (SPI_FLAG_IDLE & u32Flag)) {
        CLR_REG32_BIT(u32Flag, SPI_FLAG_IDLE);
        if (0U == (u32Status & SPI_FLAG_IDLE)) {
            enFlag = SET;
        }
    }
    if (0U != READ_REG32_BIT(u32Status, u32Flag)) {
        enFlag = SET;
    }

    return enFlag;
}

/**
 * @brief  SPI clear state flag.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  u32Flag            SPI state flag. Can be one or any combination of the parameter below
 *   @arg  SPI_FLAG_OVERRUN
 *   @arg  SPI_FLAG_MD_FAULT
 *   @arg  SPI_FLAG_PARITY_ERR
 *   @arg  SPI_FLAG_UNDERRUN
 * @retval None
 */
void SPI_ClearStatus(CM_SPI_TypeDef *SPIx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_SPI_CLR_FLAG(u32Flag));

    CLR_REG32_BIT(SPIx->SR, u32Flag);
}

/**
 * @brief  SPI loopback function configuration.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  u32Mode            Loopback mode. Can be one parameter @ref SPI_Loopback_Selection_Define
 * @retval None
 */
void SPI_SetLoopbackMode(CM_SPI_TypeDef *SPIx, uint32_t u32Mode)
{
    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_SPI_SPLPBK(u32Mode));

    MODIFY_REG32(SPIx->CR, SPI_CR_SPLPBK | SPI_CR_SPLPBK2, u32Mode);
}

/**
 * @brief  SPI parity check error self diagnosis function enable or disable.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  enNewState         An @ref en_functional_state_t enumeration value.
 * @retval None
 */

void SPI_ParityCheckCmd(CM_SPI_TypeDef *SPIx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(SPIx->CR, SPI_CR_PATE);
    } else {
        CLR_REG32_BIT(SPIx->CR, SPI_CR_PATE);
    }
}

/**
 * @brief  SPI signals delay time configuration
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  pstcDelayConfig    Pointer to a stc_spi_delay_t structure that contains
 *                                  the configuration information for the SPI delay time.
 * @retval int32_t:
 *         - LL_OK:                 No errors occurred
 *         - LL_ERR_INVD_PARAM:     pstcDelayConfig == NULL
 */
int32_t SPI_DelayTimeConfig(CM_SPI_TypeDef *SPIx, const stc_spi_delay_t *pstcDelayConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));

    if (NULL != pstcDelayConfig) {
        DDL_ASSERT(IS_SPI_INTERVAL_DELAY(pstcDelayConfig->u32IntervalDelay));
        DDL_ASSERT(IS_SPI_RELEASE_DELAY(pstcDelayConfig->u32ReleaseDelay));
        DDL_ASSERT(IS_SPI_SETUP_DELAY(pstcDelayConfig->u32SetupDelay));

        /* Interval delay */
        if (SPI_INTERVAL_TIME_1SCK == pstcDelayConfig->u32IntervalDelay) {
            CLR_REG32_BIT(SPIx->CFG2, SPI_CFG2_MIDIE);
            CLR_REG32_BIT(SPIx->CFG1, SPI_CFG1_MIDI);
        } else {
            MODIFY_REG32(SPIx->CFG1, SPI_CFG1_MIDI, pstcDelayConfig->u32IntervalDelay);
            SET_REG32_BIT(SPIx->CFG2, SPI_CFG2_MIDIE);
        }

        /* SCK release delay */
        if (SPI_RELEASE_TIME_1SCK == pstcDelayConfig->u32ReleaseDelay) {
            CLR_REG32_BIT(SPIx->CFG2, SPI_CFG2_MSSDLE);
            CLR_REG32_BIT(SPIx->CFG1, SPI_CFG1_MSSDL);
        } else {
            SET_REG32_BIT(SPIx->CFG2, SPI_CFG2_MSSDLE);
            MODIFY_REG32(SPIx->CFG1, SPI_CFG1_MSSDL, pstcDelayConfig->u32ReleaseDelay);
        }

        /* Setup delay */
        if (SPI_SETUP_TIME_1SCK == pstcDelayConfig->u32SetupDelay) {
            CLR_REG32_BIT(SPIx->CFG2, SPI_CFG2_MSSIE);
            CLR_REG32_BIT(SPIx->CFG1, SPI_CFG1_MSSI);
        } else {
            SET_REG32_BIT(SPIx->CFG2, SPI_CFG2_MSSIE);
            MODIFY_REG32(SPIx->CFG1, SPI_CFG1_MSSI, pstcDelayConfig->u32SetupDelay);
        }

        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Set a default value for the SPI delay time configuration structure.
 * @param  [in]  pstcDelayConfig    Pointer to a stc_spi_delay_t structure that
 *                                  contains configuration information.
 * @retval int32_t:
 *         - LL_OK:                 No errors occurred.
 *         - LL_ERR_INVD_PARAM:     pstcDelayConfig == NULL.
 */
int32_t SPI_DelayStructInit(stc_spi_delay_t *pstcDelayConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcDelayConfig) {
        pstcDelayConfig->u32IntervalDelay = SPI_INTERVAL_TIME_1SCK;
        pstcDelayConfig->u32ReleaseDelay = SPI_RELEASE_TIME_1SCK;
        pstcDelayConfig->u32SetupDelay = SPI_SETUP_TIME_1SCK;
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Set the communication mode.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  u32Mode            Specify the communication mode @ref SPI_Comm_Mode_Define
 * @retval None
 */
void SPI_SetCommMode(CM_SPI_TypeDef *SPIx, uint32_t u32Mode)
{
    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_SPI_COMM_MD(u32Mode));

    MODIFY_REG32(SPIx->CFG1, SPI_CFG1_CTMDS, u32Mode);
}

/**
 * @brief  SPI SS signal valid level configuration
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  u32SSPin           Specify the SS pin @ref SPI_SS_Pin_Define
 * @param  [in]  u32SSLevel         Specify the SS valid level @ref SPI_SS_Level
 *   @arg  SPI_SS_VALID_LVL_HIGH:   SS high level valid
 *   @arg  SPI_SS_VALID_LVL_LOW:    SS low level valid
 * @retval None
 */
void SPI_SetSSValidLevel(CM_SPI_TypeDef *SPIx, uint32_t u32SSPin, uint32_t u32SSLevel)
{
    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_SPI_SS_PIN(u32SSPin));
    DDL_ASSERT(IS_SPI_SS_VALID_LVL(u32SSLevel));

    if (SPI_SS_VALID_LVL_HIGH == u32SSLevel) {
        SET_REG32_BIT(SPIx->CFG1, u32SSPin);
    } else {
        CLR_REG32_BIT(SPIx->CFG1, u32SSPin);
    }
}

/**
 * @brief  Set the SPI SCK polarity.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  u32Polarity        Specify the SPI SCK polarity @ref SPI_SCK_Polarity_Define
 * @retval None
 */
void SPI_SetSckPolarity(CM_SPI_TypeDef *SPIx, uint32_t u32Polarity)
{
    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_SPI_SCK_POLARITY(u32Polarity));

    if (SPI_SCK_POLARITY_LOW == u32Polarity) {
        CLR_REG32_BIT(SPIx->CFG2, SPI_CFG2_CPOL);
    } else {
        SET_REG32_BIT(SPIx->CFG2, SPI_CFG2_CPOL);
    }
}

/**
 * @brief  Set the SPI SCK phase.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  u32Phase           Specify the SPI SCK phase @ref SPI_SCK_Phase_Define
 * @retval None
 */
void SPI_SetSckPhase(CM_SPI_TypeDef *SPIx, uint32_t u32Phase)
{
    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_SPI_SCK_PHASE(u32Phase));

    if (SPI_SCK_PHASE_ODD_EDGE_SAMPLE == u32Phase) {
        CLR_REG32_BIT(SPIx->CFG2, SPI_CFG2_CPHA);
    } else {
        SET_REG32_BIT(SPIx->CFG2, SPI_CFG2_CPHA);
    }
}

/**
 * @brief  SPI valid SS signal configuration
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  u32SSPin           Specify the SS pin @ref SPI_SS_Pin_Define
 * @retval None
 */
void SPI_SSPinSelect(CM_SPI_TypeDef *SPIx, uint32_t u32SSPin)
{
    uint32_t    u32RegConfig;
    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_SPI_SS_PIN(u32SSPin));

    switch (u32SSPin) {
        case SPI_PIN_SS0:
            u32RegConfig = SPI_SS0_VALID_CFG;
            break;
        case SPI_PIN_SS1:
            u32RegConfig = SPI_SS1_VALID_CFG;
            break;
        case SPI_PIN_SS2:
            u32RegConfig = SPI_SS2_VALID_CFG;
            break;
        case SPI_PIN_SS3:
            u32RegConfig = SPI_SS3_VALID_CFG;
            break;
        default:
            u32RegConfig = SPI_SS0_VALID_CFG;
            break;
    }
    MODIFY_REG32(SPIx->CFG2, SPI_CFG2_SSA, u32RegConfig);
}

/**
 * @brief  SPI read buffer configuration
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  u32ReadBuf         Target buffer for read operation @ref SPI_Read_Target_Buf_Define
 * @retval None
 */
void SPI_SetReadBuf(CM_SPI_TypeDef *SPIx, uint32_t u32ReadBuf)
{
    DDL_ASSERT(IS_VALID_SPI_UNIT(SPIx));
    DDL_ASSERT(IS_SPI_RD_TARGET_BUFF(u32ReadBuf));

    MODIFY_REG32(SPIx->CFG1, SPI_CFG1_SPRDTD, u32ReadBuf);
}

/**
 * @brief  SPI transmit data.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  pvTxBuf            The pointer to the buffer which contains the data to be sent.
 * @param  [in]  u32TxLen           The length of the data to be sent.
 * @param  [in]  u32Timeout         Timeout value.
 * @retval int32_t:
 *         - LL_OK:                 No errors occurred
 *         - LL_ERR_TIMEOUT:        SPI transmit timeout.
 *         - LL_ERR_INVD_PARAM:     pvTxBuf == NULL or u32TxLen == 0U
 * @note   -No SS pin active and inactive operation in 3-wire mode. Add operations of SS pin depending on your application.
 *         -In the send only slave mode, the function needs to increase an appropriate delay after calling to ensure the
 *          integrity of data transmission.
 */
int32_t SPI_Trans(CM_SPI_TypeDef *SPIx, const void *pvTxBuf, uint32_t u32TxLen, uint32_t u32Timeout)
{
    uint32_t u32Flags;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pvTxBuf != NULL) && (u32TxLen != 0U)) {
        u32Flags = READ_REG32_BIT(SPIx->CR, SPI_CR_TXMDS);
        if (u32Flags == SPI_SEND_ONLY) {
            /* Transmit data in send only mode. */
            i32Ret = SPI_Tx(SPIx, pvTxBuf, u32TxLen, u32Timeout);
        } else {
            /* Transmit data in full duplex mode. */
            i32Ret = SPI_TxRx(SPIx, pvTxBuf, NULL, u32TxLen, u32Timeout);
        }
    }
    return i32Ret;
}

/**
 * @brief  SPI receive data.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  pvRxBuf            The pointer to the buffer which the received data to be stored.
 * @param  [in]  u32RxLen           The length of the data to be received.
 * @param  [in]  u32Timeout         Timeout value.
 * @retval int32_t:
 *         - LL_OK:                 No errors occurred
 *         - LL_ERR_TIMEOUT:        SPI receive timeout.
 *         - LL_ERR_INVD_PARAM:     pvRxBuf == NULL or u32RxLen == 0U
 * @note   -No SS pin active and inactive operation in 3-wire mode. Add operations of SS pin depending on your application.
 */
int32_t SPI_Receive(CM_SPI_TypeDef *SPIx, void *pvRxBuf, uint32_t u32RxLen, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pvRxBuf != NULL) && (u32RxLen != 0U)) {
        /* Receives data in full duplex master mode. */
        i32Ret = SPI_TxRx(SPIx, NULL, pvRxBuf, u32RxLen, u32Timeout);
    }
    return i32Ret;
}

/**
 * @brief  SPI transmit and receive data.
 * @param  [in]  SPIx               SPI unit
 *   @arg CM_SPIx or CM_SPI
 * @param  [in]  pvTxBuf            The pointer to the buffer which contains the data to be sent.
 *                                  If this pointer is NULL and the pvRxBuf is NOT NULL, the MOSI output high
 *                                  and the the received data will be stored in the buffer pointed by pvRxBuf.
 * @param  [out] pvRxBuf            The pointer to the buffer which the received data will be stored.
 *                                  This for full duplex transfer.
 * @param  [in]  u32Len             The length of the data(in byte or half word) to be sent and received.
 * @param  [in]  u32Timeout         Timeout value.
 * @retval int32_t:
 *         - LL_OK:                 No errors occurred
 *         - LL_ERR_TIMEOUT:        SPI transmit and receive timeout.
 *         - LL_ERR_INVD_PARAM:     pvRxBuf == NULL or pvRxBuf == NULL or u32Len == 0U
 * @note   SPI receives data while sending data.
 */
int32_t SPI_TransReceive(CM_SPI_TypeDef *SPIx, const void *pvTxBuf, void *pvRxBuf, uint32_t u32Len, uint32_t u32Timeout)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pvTxBuf != NULL) && (pvRxBuf != NULL) && (u32Len != 0U)) {
        /* Transmit and receive data in full duplex master mode. */
        i32Ret = SPI_TxRx(SPIx, pvTxBuf, pvRxBuf, u32Len, u32Timeout);
    }
    return i32Ret;
}
/**
 * @}
 */

#endif /* LL_SPI_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
