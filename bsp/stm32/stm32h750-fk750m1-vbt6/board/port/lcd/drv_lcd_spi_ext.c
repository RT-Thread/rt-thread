/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-03-24     spaceman          the first version
 */

#include "drv_lcd_spi_ext.h"
#include "stm32h7xx_hal.h"

static SPI_HandleTypeDef* spi_handle;

void Set_SPI_Handle_Ext(SPI_HandleTypeDef *handle)
{
    spi_handle = handle;
}

/**
 * @brief Handle SPI Communication Timeout.
 * @param hspi: pointer to a SPI_HandleTypeDef structure that contains
 *              the configuration information for SPI module.
 * @param Flag: SPI flag to check
 * @param Status: flag state to check
 * @param Timeout: Timeout duration
 * @param Tickstart: Tick start value
 * @retval HAL status
 */
HAL_StatusTypeDef LCD_SPI_WaitOnFlagUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Flag, FlagStatus Status,
                                                 uint32_t Tickstart, uint32_t Timeout)
{
    /* Wait until flag is set */
    while ((__HAL_SPI_GET_FLAG(hspi, Flag) ? SET : RESET) == Status) {
        /* Check for the Timeout */
        if ((((HAL_GetTick() - Tickstart) >= Timeout) && (Timeout != HAL_MAX_DELAY)) || (Timeout == 0U)) {
            return HAL_TIMEOUT;
        }
    }
    return HAL_OK;
}

/**
 * @brief  Close Transfer and clear flags.
 * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
 *               the configuration information for SPI module.
 * @retval HAL_ERROR: if any error detected
 *         HAL_OK: if nothing detected
 */
void LCD_SPI_CloseTransfer(SPI_HandleTypeDef *hspi)
{
    uint32_t itflag = hspi->Instance->SR;

    __HAL_SPI_CLEAR_EOTFLAG(hspi);
    __HAL_SPI_CLEAR_TXTFFLAG(hspi);

    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);

    /* Disable ITs */
    __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_EOT | SPI_IT_TXP | SPI_IT_RXP | SPI_IT_DXP | SPI_IT_UDR | SPI_IT_OVR | SPI_IT_FRE | SPI_IT_MODF));

    /* Disable Tx DMA Request */
    CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);

    /* Report UnderRun error for non RX Only communication */
    if (hspi->State != HAL_SPI_STATE_BUSY_RX) {
        if ((itflag & SPI_FLAG_UDR) != 0UL) {
            SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_UDR);
            __HAL_SPI_CLEAR_UDRFLAG(hspi);
        }
    }

    /* Report OverRun error for non TX Only communication */
    if (hspi->State != HAL_SPI_STATE_BUSY_TX) {
        if ((itflag & SPI_FLAG_OVR) != 0UL) {
            SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_OVR);
            __HAL_SPI_CLEAR_OVRFLAG(hspi);
        }
    }

    /* SPI Mode Fault error interrupt occurred -------------------------------*/
    if ((itflag & SPI_FLAG_MODF) != 0UL) {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_MODF);
        __HAL_SPI_CLEAR_MODFFLAG(hspi);
    }

    /* SPI Frame error interrupt occurred ------------------------------------*/
    if ((itflag & SPI_FLAG_FRE) != 0UL) {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FRE);
        __HAL_SPI_CLEAR_FREFLAG(hspi);
    }

    hspi->TxXferCount = (uint16_t)0UL;
    hspi->RxXferCount = (uint16_t)0UL;
}

/**
 * @brief  专为屏幕清屏而修改，将需要清屏的颜色批量传输
 * @param  pData  : 要写入的数据
 * @param  Size   : 数据大小
 * @retval status
 */

rt_err_t SPI_Transmit_Ext(uint16_t pData, uint32_t Size)
{
    uint32_t tickstart;
    uint32_t Timeout = 1000;  // 超时判断
    uint32_t LCD_pData_32bit; // 按32位传输时的数据
    uint32_t LCD_TxDataCount; // 传输计数
    rt_err_t errorcode = RT_EOK;
    SPI_HandleTypeDef *hspi = spi_handle;

    /* Check Direction parameter */
    assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE_2LINES_TXONLY(hspi->Init.Direction));

    /* Process Locked */
    __HAL_LOCK(hspi);

    /* Init tickstart for timeout management*/
    tickstart = HAL_GetTick();

    if (hspi->State != HAL_SPI_STATE_READY) {
        errorcode = -RT_EBUSY;
        __HAL_UNLOCK(hspi);
        return errorcode;
    }

    if (Size == 0UL) {
        errorcode = -RT_ERROR;
        __HAL_UNLOCK(hspi);
        return errorcode;
    }

    /* Set the transaction information */
    hspi->State     = HAL_SPI_STATE_BUSY_TX;
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;

    LCD_TxDataCount = Size;                  // 传输的数据长度
    LCD_pData_32bit = (pData << 16) | pData; // 按32位传输时，合并2个像素点的颜色

    /*Init field not used in handle to zero */
    hspi->pRxBuffPtr  = NULL;
    hspi->RxXferSize  = (uint16_t)0UL;
    hspi->RxXferCount = (uint16_t)0UL;
    hspi->TxISR       = NULL;
    hspi->RxISR       = NULL;

    /* Configure communication direction : 1Line */
    if (hspi->Init.Direction == SPI_DIRECTION_1LINE) {
        SPI_1LINE_TX(hspi);
    }

    // 不使用硬件 TSIZE 控制，此处设置为0，即不限制传输的数据长度
    MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, 0);

    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);

    if (hspi->Init.Mode == SPI_MODE_MASTER) {
        /* Master transfer start */
        SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
    }

    /* Transmit data in 16 Bit mode */
    while (LCD_TxDataCount > 0UL) {
        /* Wait until TXP flag is set to send data */
        if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXP)) {
            if ((hspi->TxXferCount > 1UL) && (hspi->Init.FifoThreshold > SPI_FIFO_THRESHOLD_01DATA)) {
                *((__IO uint32_t *)&hspi->Instance->TXDR) = (uint32_t)LCD_pData_32bit;
                LCD_TxDataCount -= (uint16_t)2UL;
            } else {
                *((__IO uint16_t *)&hspi->Instance->TXDR) = (uint16_t)pData;
                LCD_TxDataCount--;
            }
        } else {
            /* Timeout management */
            if ((((HAL_GetTick() - tickstart) >= Timeout) && (Timeout != HAL_MAX_DELAY)) || (Timeout == 0U)) {
                /* Call standard close procedure with error check */
                LCD_SPI_CloseTransfer(hspi);

                /* Process Unlocked */
                __HAL_UNLOCK(hspi);

                SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
                hspi->State = HAL_SPI_STATE_READY;
                return -RT_ERROR;
            }
        }
    }

    if (LCD_SPI_WaitOnFlagUntilTimeout(hspi, SPI_SR_TXC, RESET, tickstart, Timeout) != HAL_OK) {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
    }

    SET_BIT((hspi)->Instance->CR1, SPI_CR1_CSUSP); // 请求挂起SPI传输
    /* 等待SPI挂起 */
    if (LCD_SPI_WaitOnFlagUntilTimeout(hspi, SPI_FLAG_SUSP, RESET, tickstart, Timeout) != HAL_OK) {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
    }
    LCD_SPI_CloseTransfer(hspi); /* Call standard close procedure with error check */

    SET_BIT((hspi)->Instance->IFCR, SPI_IFCR_SUSPC); // 清除挂起标志位

    /* Process Unlocked */
    __HAL_UNLOCK(hspi);

    hspi->State = HAL_SPI_STATE_READY;

    if (hspi->ErrorCode != HAL_SPI_ERROR_NONE) {
        return -RT_ERROR;
    }
    return errorcode;
}

/**
 * @brief  专为批量写入数据修改，使之不限长度的传输数据
 * @param  pData  : 要写入的数据
 * @param  Size   : 数据大小
 * @retval status
 */
rt_err_t SPI_TransmitBuffer_Ext(uint16_t *pData, uint32_t Size)
{
    uint32_t tickstart;
    uint32_t Timeout = 1000;  // 超时判断
    uint32_t LCD_TxDataCount; // 传输计数
    rt_err_t errorcode = RT_EOK;
    SPI_HandleTypeDef *hspi = spi_handle;

    /* Check Direction parameter */
    assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE_2LINES_TXONLY(hspi->Init.Direction));

    /* Process Locked */
    __HAL_LOCK(hspi);

    /* Init tickstart for timeout management*/
    tickstart = HAL_GetTick();

    if (hspi->State != HAL_SPI_STATE_READY) {
        errorcode = -RT_EBUSY;
        __HAL_UNLOCK(hspi);
        return errorcode;
    }

    if (Size == 0UL) {
        errorcode = -RT_ERROR;
        __HAL_UNLOCK(hspi);
        return errorcode;
    }

    /* Set the transaction information */
    hspi->State     = HAL_SPI_STATE_BUSY_TX;
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;

    LCD_TxDataCount = Size; // 传输的数据长度

    /*Init field not used in handle to zero */
    hspi->pRxBuffPtr  = NULL;
    hspi->RxXferSize  = (uint16_t)0UL;
    hspi->RxXferCount = (uint16_t)0UL;
    hspi->TxISR       = NULL;
    hspi->RxISR       = NULL;

    /* Configure communication direction : 1Line */
    if (hspi->Init.Direction == SPI_DIRECTION_1LINE) {
        SPI_1LINE_TX(hspi);
    }

    // 不使用硬件 TSIZE 控制，此处设置为0，即不限制传输的数据长度
    MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, 0);

    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);

    if (hspi->Init.Mode == SPI_MODE_MASTER) {
        /* Master transfer start */
        SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
    }

    /* Transmit data in 16 Bit mode */
    while (LCD_TxDataCount > 0UL) {
        /* Wait until TXP flag is set to send data */
        if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXP)) {
            if ((LCD_TxDataCount > 1UL) && (hspi->Init.FifoThreshold > SPI_FIFO_THRESHOLD_01DATA)) {
                *((__IO uint32_t *)&hspi->Instance->TXDR) = *((uint32_t *)pData);
                pData += 2;
                LCD_TxDataCount -= 2;
            } else {
                *((__IO uint16_t *)&hspi->Instance->TXDR) = *((uint16_t *)pData);
                pData += 1;
                LCD_TxDataCount--;
            }
        } else {
            /* Timeout management */
            if ((((HAL_GetTick() - tickstart) >= Timeout) && (Timeout != HAL_MAX_DELAY)) || (Timeout == 0U)) {
                /* Call standard close procedure with error check */
                LCD_SPI_CloseTransfer(hspi);

                /* Process Unlocked */
                __HAL_UNLOCK(hspi);

                SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
                hspi->State = HAL_SPI_STATE_READY;
                return -RT_ERROR;
            }
        }
    }

    if (LCD_SPI_WaitOnFlagUntilTimeout(hspi, SPI_SR_TXC, RESET, tickstart, Timeout) != HAL_OK) {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
    }

    SET_BIT((hspi)->Instance->CR1, SPI_CR1_CSUSP); // 请求挂起SPI传输
    /* 等待SPI挂起 */
    if (LCD_SPI_WaitOnFlagUntilTimeout(hspi, SPI_FLAG_SUSP, RESET, tickstart, Timeout) != HAL_OK) {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
    }
    LCD_SPI_CloseTransfer(hspi); /* Call standard close procedure with error check */

    SET_BIT((hspi)->Instance->IFCR, SPI_IFCR_SUSPC); // 清除挂起标志位

    /* Process Unlocked */
    __HAL_UNLOCK(hspi);

    hspi->State = HAL_SPI_STATE_READY;

    if (hspi->ErrorCode != HAL_SPI_ERROR_NONE) {
        return -RT_ERROR;
    }
    return errorcode;
}
