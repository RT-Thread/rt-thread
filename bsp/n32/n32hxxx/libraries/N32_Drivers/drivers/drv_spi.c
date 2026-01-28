/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#ifdef BSP_USING_SPI

#if defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3) || defined(BSP_USING_SPI4) || defined(BSP_USING_SPI5) || defined(BSP_USING_SPI6) || defined(BSP_USING_SPI7)


#include "drv_spi.h"
#include "drv_config.h"
#include <string.h>

//#define DRV_DEBUG
#define LOG_TAG              "drv.spi"
#include <drv_log.h>

enum
{
#ifdef BSP_USING_SPI1
    SPI1_INDEX,
#endif
#ifdef BSP_USING_SPI2
    SPI2_INDEX,
#endif
#ifdef BSP_USING_SPI3
    SPI3_INDEX,
#endif
#ifdef BSP_USING_SPI4
    SPI4_INDEX,
#endif
#ifdef BSP_USING_SPI5
    SPI5_INDEX,
#endif
#ifdef BSP_USING_SPI6
    SPI6_INDEX,
#endif
#ifdef BSP_USING_SPI7
    SPI7_INDEX,
#endif
};


static struct n32_spi_config spi_config[] =
{
#ifdef BSP_USING_SPI1
    SPI1_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI2
    SPI2_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI3
    SPI3_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI4
    SPI4_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI5
    SPI5_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI6
    SPI6_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI7
    SPI7_BUS_CONFIG,
#endif
};

static struct n32_spi spi_bus_obj[sizeof(spi_config) / sizeof(spi_config[0])] = { 0 };


static rt_err_t SPI_DMA_TransmitReceive(struct n32_spi *spi_drv, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
    RT_ASSERT(spi_drv != RT_NULL);
    RT_ASSERT((spi_drv->cfg->mode & RT_SPI_3WIRE) != RT_SPI_3WIRE);

    if (spi_drv->dma.DMA_Rx_Init != RT_TRUE || spi_drv->dma.DMA_Tx_Init != RT_TRUE)
    {
        LOG_E("In full-duplex mode, both TX DMA and RX DMA did not complete initialization.");
        return -RT_ERROR;
    }

    if (spi_drv->dma.DMA_Rx_Init == RT_TRUE)
    {
#if defined(SOC_SERIES_N32H7xx)
        /* SPI RX DMA Receive Data */
        DMA_ChannelCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DISABLE);

        if (!DMA_ControllerIsEnabled(spi_drv->config->dma_rx->Instance))
            DMA_ControllerCmd(spi_drv->config->dma_rx->Instance, ENABLE);

        spi_drv->dma.RX_DMA_ChInitStr.IntEn      = 1U;
        spi_drv->dma.RX_DMA_ChInitStr.DstAddr    = (uint32_t)pRxData;
        spi_drv->dma.RX_DMA_ChInitStr.BlkTfrSize = Size;

        DMA_ControllerCmd(spi_drv->config->dma_rx->Instance, ENABLE);
        if (DMA_ChannelInit(spi_drv->config->dma_rx->Instance, &spi_drv->dma.RX_DMA_ChInitStr, spi_drv->config->dma_rx->dma_channel) == 0U)
        {
            /* Enable transaction complete interrupt event */
            DMA_ChannelEventCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, ENABLE);

            /* Enable the specified DMA channel */
            DMA_ChannelCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, ENABLE);

            SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_RX, ENABLE);
        }
#endif
    }
    else
    {
        LOG_E("In full-duplex mode, RX DMA did not complete initialization.");
        return -RT_ERROR;
    }

    if (spi_drv->dma.DMA_Tx_Init == RT_TRUE)
    {
#if defined(SOC_SERIES_N32H7xx)
        /* SPI TX DMA Send Data */
        DMA_ChannelCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DISABLE);

        if (!DMA_ControllerIsEnabled(spi_drv->config->dma_tx->Instance))
            DMA_ControllerCmd(spi_drv->config->dma_tx->Instance, ENABLE);

        spi_drv->dma.TX_DMA_ChInitStr.IntEn      = 1U;
        spi_drv->dma.TX_DMA_ChInitStr.SrcAddr    = (uint32_t)pTxData;
        spi_drv->dma.TX_DMA_ChInitStr.BlkTfrSize = Size;

        DMA_ControllerCmd(spi_drv->config->dma_tx->Instance, ENABLE);
        if (DMA_ChannelInit(spi_drv->config->dma_tx->Instance, &spi_drv->dma.TX_DMA_ChInitStr, spi_drv->config->dma_tx->dma_channel) == 0U)
        {
            /* Enable transaction complete interrupt event */
            DMA_ChannelEventCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, ENABLE);

            /* Enable the specified DMA channel */
            DMA_ChannelCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, ENABLE);

            SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_TX, ENABLE);
        }
#endif
    }
    else
    {
        LOG_E("In full-duplex mode, TX DMA did not complete initialization.");
        return -RT_ERROR;
    }

    /* Clear Over Flag */
    SPI_I2S_ReceiveData(spi_drv->config->SPIx);
    SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);

    /* Enable Error Interrupt */
    SPI_I2S_EnableInt(spi_drv->config->SPIx, SPI_I2S_INT_ERR, ENABLE);

    /* Set SPI Direction */
    spi_drv->Direct = SPI_Tx_Rx;

    /* Check if the SPI is already enabled */
    if ((spi_drv->config->SPIx->CTRL2 & SPI_CTRL2_SPIEN) != SPI_CTRL2_SPIEN)
        SPI_Enable(spi_drv->config->SPIx, ENABLE);

    return RT_EOK;
}

static rt_err_t SPI_DMA_Transmit(struct n32_spi *spi_drv, uint8_t *pData, uint16_t Size)
{
    RT_ASSERT(spi_drv != RT_NULL);

    if (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_RX ||
            spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_TX)
    {
        /* Disable the sFLASH_SPI  */
        SPI_Enable(spi_drv->config->SPIx, DISABLE);
        /* DeInitializes the sFLASH_SPI */
        SPI_I2S_DeInit(spi_drv->config->SPIx);
        /* Set the sFLASH_SPI SendOnly*/
        spi_drv->SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_TX;
        SPI_Init(spi_drv->config->SPIx, &spi_drv->SPI_InitStructure);
    }

    if (spi_drv->dma.DMA_Rx_Init == RT_TRUE)
    {
#if defined(SOC_SERIES_N32H7xx)
        DMA_ChannelCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DISABLE);

        if (!DMA_ControllerIsEnabled(spi_drv->config->dma_rx->Instance))
            DMA_ControllerCmd(spi_drv->config->dma_rx->Instance, ENABLE);

        spi_drv->dma.RX_DMA_ChInitStr.IntEn      = 0U;
        spi_drv->dma.RX_DMA_ChInitStr.DstAddr    = NULL;
        spi_drv->dma.RX_DMA_ChInitStr.BlkTfrSize = 0U;

        DMA_ControllerCmd(spi_drv->config->dma_rx->Instance, ENABLE);
        if (DMA_ChannelInit(spi_drv->config->dma_rx->Instance, &spi_drv->dma.RX_DMA_ChInitStr, spi_drv->config->dma_rx->dma_channel) != 0U)
        {
            LOG_E("Master DMA Rx channel initialization failed.");
            return -RT_ERROR;
        }
#endif
    }

    if (spi_drv->dma.DMA_Tx_Init == RT_TRUE)
    {
#if defined(SOC_SERIES_N32H7xx)
        DMA_ChannelCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DISABLE);

        if (!DMA_ControllerIsEnabled(spi_drv->config->dma_tx->Instance))
            DMA_ControllerCmd(spi_drv->config->dma_tx->Instance, ENABLE);

        spi_drv->dma.TX_DMA_ChInitStr.IntEn      = 1U;
        spi_drv->dma.TX_DMA_ChInitStr.SrcAddr    = (uint32_t)pData;
        spi_drv->dma.TX_DMA_ChInitStr.BlkTfrSize = Size;

        DMA_ControllerCmd(spi_drv->config->dma_tx->Instance, ENABLE);
        if (DMA_ChannelInit(spi_drv->config->dma_tx->Instance, &spi_drv->dma.TX_DMA_ChInitStr, spi_drv->config->dma_tx->dma_channel) == 0U)
        {
            /* Enable transaction complete interrupt event */
            DMA_ChannelEventCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, ENABLE);

            /* Enable the specified DMA channel */
            DMA_ChannelCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, ENABLE);

            SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_TX, ENABLE);
        }
#endif
    }
    else
    {
        LOG_E("SPI DMA TX Mode, TX DMA did not complete initialization.");
        return -RT_ERROR;
    }

    /* Set SPI Direction */
    spi_drv->Direct = SPI_Tx;

    /* Check if the SPI is already enabled */
    if ((spi_drv->config->SPIx->CTRL2 & SPI_CTRL2_SPIEN) != SPI_CTRL2_SPIEN)
        SPI_Enable(spi_drv->config->SPIx, ENABLE);

    return RT_EOK;
}

static rt_err_t SPI_DMA_Receive(struct n32_spi *spi_drv, uint8_t *pData, uint16_t Size)
{
    RT_ASSERT(spi_drv != RT_NULL);

    if (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_DOUBLELINE_FULLDUPLEX && spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_MASTER)
    {
        return SPI_DMA_TransmitReceive(spi_drv, pData, pData, Size);
    }

    if (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_RX ||
            spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_TX)
    {
        /* Disable the sFLASH_SPI  */
        SPI_Enable(spi_drv->config->SPIx, DISABLE);
        /* DeInitializes the sFLASH_SPI */
        SPI_I2S_DeInit(spi_drv->config->SPIx);
        /* Set the sFLASH_SPI SendOnly*/
        spi_drv->SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_RX;
        SPI_Init(spi_drv->config->SPIx, &spi_drv->SPI_InitStructure);
    }

    if (spi_drv->dma.DMA_Rx_Init == RT_TRUE)
    {
#if defined(SOC_SERIES_N32H7xx)
        DMA_ChannelCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DISABLE);

        if (!DMA_ControllerIsEnabled(spi_drv->config->dma_rx->Instance))
            DMA_ControllerCmd(spi_drv->config->dma_rx->Instance, ENABLE);

        spi_drv->dma.RX_DMA_ChInitStr.IntEn      = 1U;
        spi_drv->dma.RX_DMA_ChInitStr.DstAddr    = (uint32_t)pData;
        spi_drv->dma.RX_DMA_ChInitStr.BlkTfrSize = Size;

        DMA_ControllerCmd(spi_drv->config->dma_rx->Instance, ENABLE);
        if (DMA_ChannelInit(spi_drv->config->dma_rx->Instance, &spi_drv->dma.RX_DMA_ChInitStr, spi_drv->config->dma_rx->dma_channel) == 0U)
        {
            /* Enable transaction complete interrupt event */
            DMA_ChannelEventCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, ENABLE);

            /* Enable the specified DMA channel */
            DMA_ChannelCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, ENABLE);

            SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_RX, ENABLE);
        }
#endif
    }
    else
    {
        LOG_E("SPI DMA RX Mode, RX DMA did not complete initialization.");
        return -RT_ERROR;
    }

    if (spi_drv->dma.DMA_Tx_Init == RT_TRUE)
    {
#if defined(SOC_SERIES_N32H7xx)
        DMA_ChannelCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DISABLE);

        if (!DMA_ControllerIsEnabled(spi_drv->config->dma_tx->Instance))
            DMA_ControllerCmd(spi_drv->config->dma_tx->Instance, ENABLE);

        spi_drv->dma.TX_DMA_ChInitStr.IntEn      = 0U;
        spi_drv->dma.TX_DMA_ChInitStr.SrcAddr    = NULL;
        spi_drv->dma.TX_DMA_ChInitStr.BlkTfrSize = 0U;

        DMA_ControllerCmd(spi_drv->config->dma_tx->Instance, ENABLE);
        if (DMA_ChannelInit(spi_drv->config->dma_tx->Instance, &spi_drv->dma.TX_DMA_ChInitStr, spi_drv->config->dma_tx->dma_channel) != 0U)
        {
            LOG_E("Master DMA Tx channel initialization failed.");
            return -RT_ERROR;
        }
#endif
    }

    /* Clear Over Flag */
    SPI_I2S_ReceiveData(spi_drv->config->SPIx);
    SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);

    /* Enable Error Interrupt */
    SPI_I2S_EnableInt(spi_drv->config->SPIx, SPI_I2S_INT_ERR, ENABLE);

    /* Set SPI Direction */
    spi_drv->Direct = SPI_Rx;

    /* Check if the SPI is already enabled */
    if ((spi_drv->config->SPIx->CTRL2 & SPI_CTRL2_SPIEN) != SPI_CTRL2_SPIEN)
        SPI_Enable(spi_drv->config->SPIx, ENABLE);

    return RT_EOK;
}

static rt_err_t SPI_Transmit_Receive(struct n32_spi *spi_drv, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
    uint16_t Tx_Size_Const = Size;
    uint16_t Tx_Size = Size;
    uint16_t Rx_Size = Size;
    uint32_t tickstart;

    RT_ASSERT(spi_drv != RT_NULL);

    if (!((spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_MASTER) && (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_DOUBLELINE_FULLDUPLEX)))
    {
        return -RT_EIO;
    }

    if ((spi_drv->config->SPIx->CTRL2 & SPI_CTRL2_SPIEN) != SPI_CTRL2_SPIEN)
        SPI_Enable(spi_drv->config->SPIx, ENABLE);

    if (spi_drv->SPI_InitStructure.DataLen == SPI_DATA_SIZE_16BITS)
    {
        if ((spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE) || (Tx_Size_Const == 1U))
        {
            spi_drv->config->SPIx->DAT = *((const uint16_t *)pTxData);
            pTxData += sizeof(uint16_t);
            Tx_Size--;
        }

        while ((Tx_Size > 0U) || (Rx_Size > 0U))
        {
            if (Tx_Size > 0U)
            {
                tickstart = rt_tick_get();
                /*  Loop while DAT register in not emplty */
                while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
                {
                    if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                    {
                        LOG_E("Checking TE flag timeout befor send data in full-duplex mode.");
                        return -RT_ETIMEOUT;
                    }
                }

                /* Send byte through the SPI1 peripheral */
                SPI_I2S_TransmitData(spi_drv->config->SPIx, *(const uint16_t *)pTxData);
                pTxData += sizeof(uint16_t);

                Tx_Size--;
            }

            tickstart = rt_tick_get();
            /* Wait for DATA send has complete */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking TE flag timeout after send data in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            tickstart = rt_tick_get();
            /* Wait for SPI bus idle */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_BUSY_FLAG) != RESET)
            {
                if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking BUSY flag timeout in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            tickstart = rt_tick_get();
            /* Wait to receive a byte */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking RNE flag timeout after send data in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            /* Return the byte read from the SPI bus */
            *((uint16_t *)pRxData) = (uint16_t)SPI_I2S_ReceiveData(spi_drv->config->SPIx);
            pRxData += sizeof(uint16_t);

            Rx_Size--;
        }
    }
    else if (spi_drv->SPI_InitStructure.DataLen == SPI_DATA_SIZE_8BITS)
    {
        if ((spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE) || (Tx_Size_Const == 1U))
        {
            spi_drv->config->SPIx->DAT = *((const uint8_t *)pTxData);
            pTxData += sizeof(uint8_t);
            Tx_Size--;
        }

        while ((Tx_Size > 0U) || (Rx_Size > 0U))
        {
            if (Tx_Size > 0U)
            {
                tickstart = rt_tick_get();
                /*  Loop while DAT register in not emplty */
                while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
                {
                    if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                    {
                        LOG_E("Checking TE flag timeout befor send data in full-duplex mode.");
                        return -RT_ETIMEOUT;
                    }
                }

                /* Send byte through the SPI1 peripheral */
                SPI_I2S_TransmitData(spi_drv->config->SPIx, *(const uint8_t *)pTxData);
                pTxData += sizeof(uint8_t);

                Tx_Size--;
            }

            tickstart = rt_tick_get();
            /* Wait for DATA send has complete */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking TE flag timeout after send data in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            tickstart = rt_tick_get();
            /* Wait for SPI bus idle */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_BUSY_FLAG) != RESET)
            {
                if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking BUSY flag timeout in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            tickstart = rt_tick_get();
            /* Wait to receive a byte */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking RNE flag timeout after send data in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            /*!< Return the byte read from the SPI bus */
            *((uint8_t *)pRxData) = (uint8_t)SPI_I2S_ReceiveData(spi_drv->config->SPIx);
            pRxData += sizeof(uint8_t);

            Rx_Size--;
        }
    }
    else
    {
        return -RT_EINVAL;
    }

    if (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG) != RESET)
    {
        volatile uint32_t reg_tmp;
        reg_tmp = spi_drv->config->SPIx->DAT;
        reg_tmp = spi_drv->config->SPIx->STS;
        (void)reg_tmp;
    }

    return RT_EOK;
}

static rt_err_t SPI_Transmit(struct n32_spi *spi_drv, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint16_t Tx_Size_Const = Size;
    uint16_t Transfer_Size = Size;
    uint32_t tickstart;

    RT_ASSERT(spi_drv != RT_NULL);

    if (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_RX ||
            spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_TX)
    {
        /* Disable the sFLASH_SPI  */
        SPI_Enable(spi_drv->config->SPIx, DISABLE);
        /* DeInitializes the sFLASH_SPI */
        SPI_I2S_DeInit(spi_drv->config->SPIx);
        /* Set the sFLASH_SPI SendOnly*/
        spi_drv->SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_TX;
        SPI_Init(spi_drv->config->SPIx, &spi_drv->SPI_InitStructure);
    }

    if ((spi_drv->config->SPIx->CTRL2 & SPI_CTRL2_SPIEN) != SPI_CTRL2_SPIEN)
        SPI_Enable(spi_drv->config->SPIx, ENABLE);


    if (spi_drv->SPI_InitStructure.DataLen == SPI_DATA_SIZE_16BITS)
    {
        if ((spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE) || (Tx_Size_Const == 1U))
        {
            spi_drv->config->SPIx->DAT = *((const uint16_t *)pData);
            pData += sizeof(uint16_t);
            Transfer_Size--;
        }

        while ((Transfer_Size > 0U))
        {
            tickstart = rt_tick_get();
            /*  Loop while DAT register in not emplty */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking TE flag timeout.");
                    return -RT_ETIMEOUT;
                }
            }


            /* Send byte through the SPI1 peripheral */
            SPI_I2S_TransmitData(spi_drv->config->SPIx, *(const uint16_t *)pData);
            pData += sizeof(uint16_t);

            Transfer_Size--;
        }
    }
    else if (spi_drv->SPI_InitStructure.DataLen == SPI_DATA_SIZE_8BITS)
    {
        if ((spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE) || (Tx_Size_Const == 1U))
        {
            spi_drv->config->SPIx->DAT = *((const uint8_t *)pData);
            pData += sizeof(uint8_t);
            Transfer_Size--;
        }

        while ((Transfer_Size > 0U))
        {
            tickstart = rt_tick_get();
            /*  Loop while DAT register in not emplty */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking TE flag timeout.");
                    return -RT_ETIMEOUT;
                }
            }


            /* Send byte through the SPI1 peripheral */
            SPI_I2S_TransmitData(spi_drv->config->SPIx, *(const uint8_t *)pData);
            pData += sizeof(uint8_t);

            Transfer_Size--;
        }
    }
    else
    {

    }

    tickstart = rt_tick_get();
    /* Wait for DATA send has complete */
    while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
    {
        if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
        {
            LOG_E("After sending the data, check the TE flag for timeout.");
            return -RT_ETIMEOUT;
        }
    }

    tickstart = rt_tick_get();
    /* Wait for SPI bus idle */
    while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_BUSY_FLAG) != RESET)
    {
        if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
        {
            LOG_E("After sending the data, check the BUSY flag for timeout.");
            return -RT_ETIMEOUT;
        }
    }

    if (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG) != RESET)
    {
        volatile uint32_t reg_tmp;
        reg_tmp = spi_drv->config->SPIx->DAT;
        reg_tmp = spi_drv->config->SPIx->STS;
        (void)reg_tmp;
    }

    return RT_EOK;
}


static rt_err_t SP_Receive(struct n32_spi *spi_drv, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint16_t Transfer_Size = Size;
    uint32_t tickstart;

    RT_ASSERT(spi_drv != RT_NULL);

    tickstart = rt_tick_get();
    while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) != RESET || SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG) != RESET)
    {
        volatile uint32_t reg_tmp;
        reg_tmp = spi_drv->config->SPIx->DAT;
        reg_tmp = spi_drv->config->SPIx->STS;
        (void)reg_tmp;

        if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
        {
            LOG_E("Before receiving data, check the OVER and RNE flags for timeout.");
            return -RT_ETIMEOUT;
        }
    }

    if (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_DOUBLELINE_FULLDUPLEX && spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_MASTER)
    {
        return SPI_Transmit_Receive(spi_drv, pData, pData, Size, Timeout);
    }

    if (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_RX ||
            spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_TX)
    {
        /* Disable the sFLASH_SPI  */
        SPI_Enable(spi_drv->config->SPIx, DISABLE);
        /* DeInitializes the sFLASH_SPI */
        SPI_I2S_DeInit(spi_drv->config->SPIx);
        /* Set the sFLASH_SPI SendOnly*/
        spi_drv->SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_RX;
        SPI_Init(spi_drv->config->SPIx, &spi_drv->SPI_InitStructure);
    }

    if ((spi_drv->config->SPIx->CTRL2 & SPI_CTRL2_SPIEN) != SPI_CTRL2_SPIEN)
        SPI_Enable(spi_drv->config->SPIx, ENABLE);

    if (spi_drv->SPI_InitStructure.DataLen == SPI_DATA_SIZE_16BITS)
    {
        while ((Transfer_Size > 0U))
        {
            tickstart = rt_tick_get();
            /* Wait to receive a byte */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("During receiving data, check the RNE flags for timeout.");
                    return -RT_ETIMEOUT;
                }
            }

            /*!< Return the byte read from the SPI bus */
            *((uint16_t *)pData) = (uint16_t)SPI_I2S_ReceiveData(spi_drv->config->SPIx);
            pData += sizeof(uint16_t);

            Transfer_Size--;
        }
    }
    else if (spi_drv->SPI_InitStructure.DataLen == SPI_DATA_SIZE_8BITS)
    {
        while ((Transfer_Size > 0U))
        {
            tickstart = rt_tick_get();
            /* Wait to receive a byte */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("During receiving data, check the RNE flags for timeout.");
                    return -RT_ETIMEOUT;
                }
            }

            /*!< Return the byte read from the SPI bus */
            *((uint8_t *)pData) = (uint8_t)SPI_I2S_ReceiveData(spi_drv->config->SPIx);
            pData += sizeof(uint8_t);

            Transfer_Size--;
        }
    }
    else
    {

    }

    if ((spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_DOUBLELINE_RONLY ||
            spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_RX)   &&
            spi_drv->SPI_InitStructure.SpiMode       == SPI_MODE_MASTER)
    {
        /* Disable the sFLASH_SPI  */
        SPI_Enable(spi_drv->config->SPIx, DISABLE);
    }

    tickstart = rt_tick_get();
    /* Wait to receive a byte */
    while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) == RESET)
    {
        spi_drv->config->SPIx->DAT;

        if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
        {
            LOG_E("After receiving data, check the RNE flags for timeout.");
            return -RT_ETIMEOUT;
        }
    }

    tickstart = rt_tick_get();
    /* Wait for SPI bus idle */
    while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_BUSY_FLAG) != RESET)
    {
        if ((((rt_tick_get() - tickstart) >=  Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
        {
            LOG_E("After receiving data, check the BUSY flags for timeout.");
            return -RT_ETIMEOUT;
        }
    }

    if (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG) != RESET)
    {
        volatile uint32_t reg_tmp;
        reg_tmp = spi_drv->config->SPIx->DAT;
        reg_tmp = spi_drv->config->SPIx->STS;
        (void)reg_tmp;
    }

    return RT_EOK;
}


static rt_err_t n32_spi_init(struct n32_spi *spi_drv, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(spi_drv != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    SPI_InitStruct(&spi_drv->SPI_InitStructure);

    if (cfg->mode & RT_SPI_SLAVE)
    {
        spi_drv->SPI_InitStructure.SpiMode = SPI_MODE_SLAVE;
    }
    else
    {
        spi_drv->SPI_InitStructure.SpiMode = SPI_MODE_MASTER;
    }

    if (cfg->mode & RT_SPI_3WIRE)
    {
        /* Switch TX/RX direction dynamically according to the application */
        spi_drv->SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_RX;
    }
    else
    {
        spi_drv->SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    }

    if (cfg->data_width == 8)
    {
        spi_drv->SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
    }
    else if (cfg->data_width == 16)
    {
        spi_drv->SPI_InitStructure.DataLen       = SPI_DATA_SIZE_16BITS;
    }
    else
    {
        return -RT_EIO;
    }

    if (cfg->mode & RT_SPI_CPHA)
    {
        spi_drv->SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    }
    else
    {
        spi_drv->SPI_InitStructure.CLKPHA        = SPI_CLKPHA_FIRST_EDGE;
    }

    if (cfg->mode & RT_SPI_CPOL)
    {
        spi_drv->SPI_InitStructure.CLKPOL        = SPI_CLKPOL_HIGH;
    }
    else
    {
        spi_drv->SPI_InitStructure.CLKPOL        = SPI_CLKPOL_LOW;
    }

    spi_drv->SPI_InitStructure.NSS               = SPI_NSS_SOFT;
    spi_drv->SPI_InitStructure.CRCPoly           = 7;

    uint32_t SPI_CLOCK = 0UL;

#if defined(SOC_SERIES_N32H7xx)
    RCC_ClocksTypeDef RCC_Clocks = { 0 };

    RCC_GetClocksFreqValue(&RCC_Clocks);

    if ((spi_drv->config->SPIx == SPI1) || (spi_drv->config->SPIx == SPI2))
    {
        SPI_CLOCK = RCC_Clocks.APB2ClkFreq;
    }
    else if (spi_drv->config->SPIx == SPI3)
    {
        SPI_CLOCK = RCC_Clocks.APB1ClkFreq;
    }
    else if ((spi_drv->config->SPIx == SPI4) || (spi_drv->config->SPIx == SPI5) || (spi_drv->config->SPIx == SPI6) || (spi_drv->config->SPIx == SPI7))
    {
        SPI_CLOCK = RCC_Clocks.APB5ClkFreq;
    }
    else
    {
        return -RT_EIO;
    }
#endif

    if (cfg->max_hz >= SPI_CLOCK / 2)
    {
        spi_drv->SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_2;
    }
    else if (cfg->max_hz >= SPI_CLOCK / 4)
    {
        spi_drv->SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_4;
    }
    else if (cfg->max_hz >= SPI_CLOCK / 8)
    {
        spi_drv->SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_8;
    }
    else if (cfg->max_hz >= SPI_CLOCK / 16)
    {
        spi_drv->SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_16;
    }
    else if (cfg->max_hz >= SPI_CLOCK / 32)
    {
        spi_drv->SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_32;
    }
    else if (cfg->max_hz >= SPI_CLOCK / 64)
    {
        spi_drv->SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_64;
    }
    else if (cfg->max_hz >= SPI_CLOCK / 128)
    {
        spi_drv->SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_128;
    }
    else
    {
        /*  min prescaler 256 */
        spi_drv->SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_256;
    }

    if (cfg->mode & RT_SPI_MSB)
    {
        spi_drv->SPI_InitStructure.FirstBit      = SPI_FB_MSB;
    }
    else
    {
        spi_drv->SPI_InitStructure.FirstBit      = SPI_FB_LSB;
    }

    /* Initializes the SPIx peripheral */
    SPI_Init(spi_drv->config->SPIx, &spi_drv->SPI_InitStructure);

    /* DMA configuration */
    if (spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG)
    {
        if (cfg->data_width == 8)
        {
#if defined(SOC_SERIES_N32H7xx)
            spi_drv->dma.RX_DMA_ChInitStr.SrcTfrWidth = DMA_CH_TRANSFER_WIDTH_8;
            spi_drv->dma.RX_DMA_ChInitStr.DstTfrWidth = DMA_CH_TRANSFER_WIDTH_8;
#endif
        }
        else if (cfg->data_width == 16)
        {
#if defined(SOC_SERIES_N32H7xx)
            spi_drv->dma.RX_DMA_ChInitStr.SrcTfrWidth = DMA_CH_TRANSFER_WIDTH_16;
            spi_drv->dma.RX_DMA_ChInitStr.DstTfrWidth = DMA_CH_TRANSFER_WIDTH_16;
#endif
        }

        /* enable dma irq */
        NVIC_SetPriority(spi_drv->config->dma_rx->dma_irq, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
        NVIC_EnableIRQ(spi_drv->config->dma_rx->dma_irq);
    }

    if (spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG)
    {
        if (cfg->data_width == 8)
        {
#if defined(SOC_SERIES_N32H7xx)
            spi_drv->dma.TX_DMA_ChInitStr.SrcTfrWidth = DMA_CH_TRANSFER_WIDTH_8;
            spi_drv->dma.TX_DMA_ChInitStr.DstTfrWidth = DMA_CH_TRANSFER_WIDTH_8;
#endif
        }
        else if (cfg->data_width == 16)
        {
#if defined(SOC_SERIES_N32H7xx)
            spi_drv->dma.TX_DMA_ChInitStr.SrcTfrWidth = DMA_CH_TRANSFER_WIDTH_16;
            spi_drv->dma.TX_DMA_ChInitStr.DstTfrWidth = DMA_CH_TRANSFER_WIDTH_16;
#endif
        }

        /* enable dma irq */
        NVIC_SetPriority(spi_drv->config->dma_tx->dma_irq, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
        NVIC_EnableIRQ(spi_drv->config->dma_tx->dma_irq);
    }

    if (spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG || spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG)
    {
        /* enable dma irq */
        NVIC_SetPriority(spi_drv->config->irq_type, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
        NVIC_EnableIRQ(spi_drv->config->irq_type);
    }

    LOG_D("%s init done", spi_drv->config->bus_name);
    return RT_EOK;
}


static rt_err_t spi_configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    struct n32_spi *spi_drv =  rt_container_of(device->bus, struct n32_spi, spi_bus);
    spi_drv->cfg = configuration;

    return n32_spi_init(spi_drv, configuration);
}


static rt_ssize_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
#define DMA_TRANS_MIN_LEN  10 /* only buffer length >= DMA_TRANS_MIN_LEN will use DMA mode */

    rt_err_t state = RT_EOK;
    uint32_t tickstart;
    rt_size_t message_length, already_send_length;
    rt_uint16_t send_length;
    rt_uint8_t *recv_buf;
    const rt_uint8_t *send_buf;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    struct n32_spi *spi_drv =  rt_container_of(device->bus, struct n32_spi, spi_bus);

    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
        {
            rt_pin_write(device->cs_pin, PIN_HIGH);
        }
        else
        {
            rt_pin_write(device->cs_pin, PIN_LOW);
        }
    }

    LOG_D("%s transfer prepare and start", spi_drv->config->bus_name);
    LOG_D("%s sendbuf: %X, recvbuf: %X, length: %d",
          spi_drv->config->bus_name,
          (uint32_t)message->send_buf,
          (uint32_t)message->recv_buf, message->length);

    message_length = message->length;
    recv_buf = message->recv_buf;
    send_buf = message->send_buf;

    while (message_length)
    {
#if defined(SOC_SERIES_N32H7xx)
        /* DMA uses a single block, with a maximum of 4095 per block */
        if (message_length > 4095)
        {
            send_length = 4095;
            message_length = message_length - 4095;
        }
        else
        {
            send_length = message_length;
            message_length = 0;
        }
#endif

        /* calculate the start address */
        already_send_length = message->length - send_length - message_length;
        /* avoid null pointer problems */
        if (message->send_buf)
        {
            send_buf = (rt_uint8_t *)message->send_buf + already_send_length;
        }
        if (message->recv_buf)
        {
            recv_buf = (rt_uint8_t *)message->recv_buf + already_send_length;
        }

        rt_uint32_t *dma_aligned_buffer = RT_NULL;
        rt_uint32_t *p_txrx_buffer = RT_NULL;

        if ((spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG) && (send_length >= DMA_TRANS_MIN_LEN))
        {
#if defined(SOC_SERIES_N32H7xx)
            if (RT_IS_ALIGN((rt_uint32_t)send_buf, 32) && send_buf != RT_NULL) /* aligned with 32 bytes? */
            {
                p_txrx_buffer = (rt_uint32_t *)send_buf; /* send_buf aligns with 32 bytes, no more operations */
            }
            else
            {
                /* send_buf doesn't align with 32 bytes, so creat a cache buffer with 32 bytes aligned */
                dma_aligned_buffer = (rt_uint32_t *)rt_malloc_align(send_length, 32);
                rt_memcpy(dma_aligned_buffer, send_buf, send_length);
                p_txrx_buffer = dma_aligned_buffer;
            }
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, dma_aligned_buffer, send_length);
#else
            if (RT_IS_ALIGN((rt_uint32_t)send_buf, 4) && send_buf != RT_NULL) /* aligned with 4 bytes? */
            {
                p_txrx_buffer = (rt_uint32_t *)send_buf; /* send_buf aligns with 4 bytes, no more operations */
            }
            else
            {
                /* send_buf doesn't align with 4 bytes, so creat a cache buffer with 4 bytes aligned */
                dma_aligned_buffer = (rt_uint32_t *)rt_malloc(send_length); /* aligned with RT_ALIGN_SIZE (8 bytes by default) */
                rt_memcpy(dma_aligned_buffer, send_buf, send_length);
                p_txrx_buffer = dma_aligned_buffer;
            }
#endif
        }

        tickstart = rt_tick_get();
        /* Check the SPI RNE Flag */
        while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) != RESET)
        {
            /*clear RX buff*/
            spi_drv->config->SPIx->DAT;

            if ((rt_tick_get() - tickstart) > 1000U)
            {
                state = -RT_ERROR;
                LOG_E("Checking the RNE flag timeout before transmission begins!");
                break;
            }
        }

        tickstart = rt_tick_get();
        /* Check the SPI OVER Flag */
        while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG) != RESET)
        {
            /*clear RX buff*/
            spi_drv->config->SPIx->DAT;
            SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);

            if ((rt_tick_get() - tickstart) > 1000U)
            {
                state = -RT_ERROR;
                LOG_E("Checking the OVER flag timeout before transmission begins!");
                break;
            }
        }

        /* start once data exchange in DMA mode */
        if (message->send_buf && message->recv_buf)
        {
            if ((spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG) && (spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG) && (send_length >= DMA_TRANS_MIN_LEN))
            {
                state = SPI_DMA_TransmitReceive(spi_drv, (uint8_t *)p_txrx_buffer, (uint8_t *)p_txrx_buffer, send_length);
            }
            else if ((spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG) && (send_length >= DMA_TRANS_MIN_LEN))
            {
                state = SPI_DMA_Transmit(spi_drv, (uint8_t *)p_txrx_buffer, send_length);
            }
            else if ((spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG) && (send_length >= DMA_TRANS_MIN_LEN))
            {
                state = -RT_ERROR;
                LOG_E("It shoule be enabled both BSP_SPIx_TX_USING_DMA and BSP_SPIx_TX_USING_DMA flag, if wants to use SPI DMA Rx singly.");
                break;
            }
            else
            {
                state = SPI_Transmit_Receive(spi_drv, (uint8_t *)send_buf, (uint8_t *)recv_buf, send_length, 1000);
            }
        }
        else if (message->send_buf)
        {
            if ((spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG) && (send_length >= DMA_TRANS_MIN_LEN))
            {
                state = SPI_DMA_Transmit(spi_drv, (uint8_t *)p_txrx_buffer, send_length);
            }
            else
            {
                state = SPI_Transmit(spi_drv, (uint8_t *)send_buf, send_length, 1000);
            }

            if (message->cs_release && (device->config.mode & RT_SPI_3WIRE))
            {
                /* release the CS by disable SPI when using 3 wires SPI */
                SPI_Enable(spi_drv->config->SPIx, DISABLE);
            }
        }
        else if (message->recv_buf)
        {
            rt_memset((uint8_t *)recv_buf, 0xff, send_length);
            if ((spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG) && (send_length >= DMA_TRANS_MIN_LEN))
            {
                state = SPI_DMA_Receive(spi_drv, (uint8_t *)p_txrx_buffer, send_length);
            }
            else
            {
                /* clear the old error flag */
                __IO uint32_t tmpreg = 0x00U;
                tmpreg = spi_drv->config->SPIx->DAT;
                tmpreg = spi_drv->config->SPIx->STS;
                (void)tmpreg;

                state = SP_Receive(spi_drv, (uint8_t *)recv_buf, send_length, 1000);
            }
        }
        else
        {
            state = -RT_ERROR;
            LOG_E("message->send_buf and message->recv_buf are both NULL!");
        }

        if (state != RT_EOK)
        {
            LOG_E("SPI transfer error: %d", state);
            message->length = 0;
            break;
        }
        else
        {
            LOG_D("%s transfer done", spi_drv->config->bus_name);
        }

        /* For simplicity reasons, this example is just waiting till the end of the
           transfer, but application may perform other tasks while transfer operation
           is ongoing. */
        if ((spi_drv->spi_dma_flag & (SPI_USING_TX_DMA_FLAG | SPI_USING_RX_DMA_FLAG)) && (send_length >= DMA_TRANS_MIN_LEN))
        {
            /* blocking the thread,and the other tasks can run */
            if (rt_completion_wait(&spi_drv->cpt, 1000) != RT_EOK)
            {
                state = -RT_ERROR;
                LOG_E("wait for DMA interrupt overtime!");
                break;
            }
        }

        tickstart = rt_tick_get();
        while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_BUSY_FLAG) != RESET)
        {
            if ((rt_tick_get() - tickstart) > 1000U)
            {
                state = -RT_ERROR;
                LOG_E("Wait SPI BUSY Flag Timeout!");
                break;
            }
        }

        if (dma_aligned_buffer != RT_NULL) /* re-aligned, so need to copy the data to recv_buf */
        {
            if (recv_buf != RT_NULL)
            {
#if defined(SOC_SERIES_N32H7xx)
                rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, p_txrx_buffer, send_length);
#endif /* SOC_SERIES_N32H7xx */
                rt_memcpy(recv_buf, p_txrx_buffer, send_length);
            }
#if defined(SOC_SERIES_N32H7xx)
            rt_free_align(dma_aligned_buffer);
#else
            rt_free(dma_aligned_buffer);
#endif /* SOC_SERIES_N32H7xx */
        }
    }

    if (message->cs_release && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
            rt_pin_write(device->cs_pin, PIN_LOW);
        else
            rt_pin_write(device->cs_pin, PIN_HIGH);
    }

    if (state != RT_EOK)
    {
        return -RT_ERROR;
    }
    return message->length;
}

static const struct rt_spi_ops n32_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};



static int rt_hw_spi_bus_init(void)
{
    rt_err_t result;

    for (rt_size_t i = 0; i < sizeof(spi_config) / sizeof(spi_config[0]); i++)
    {
        spi_bus_obj[i].config = &spi_config[i];
        spi_bus_obj[i].spi_bus.parent.user_data = &spi_config[i];


        if (spi_bus_obj[i].spi_dma_flag & SPI_USING_RX_DMA_FLAG)
        {
#if defined(SOC_SERIES_N32H7xx)
            /* Configure the SPI RX DMA for Transmission process */
            /* Enable DMA clock */
            RCC_EnableAHB1PeriphClk3(spi_bus_obj[i].config->dma_rx->dma_rcc, ENABLE);
            /* Enable DMA MUXclock  */
            RCC_EnableAHB1PeriphClk1(RCC_AHB1_PERIPHEN_M7_DMAMUX1, ENABLE);

            /* Receive DMA Config */
            DMA_ChannelStructInit(&spi_bus_obj[i].dma.RX_DMA_ChInitStr);
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.IntEn              = 0x1U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcAddr            = (uint32_t)&spi_bus_obj[i].config->SPIx->DAT;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstAddr            = NULL;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcTfrWidth        = DMA_CH_TRANSFER_WIDTH_8;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstTfrWidth        = DMA_CH_TRANSFER_WIDTH_8;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstAddrCountMode   = DMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcAddrCountMode   = DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstBurstLen        = DMA_CH_BURST_LENGTH_1;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcBurstLen        = DMA_CH_BURST_LENGTH_1;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcGatherEn        = 0x0U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstScatterEn       = 0x0U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.TfrTypeFlowCtrl    = DMA_CH_TRANSFER_FLOW_P2M_DMA;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.BlkTfrSize         = 0U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.pLinkListItem      = NULL;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcGatherInterval  = 0x0U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcGatherCount     = 0x0U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstScatterInterval = 0x0U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstScatterCount    = 0x0U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.TfrType            = DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.ChannelPriority    = DMA_CH_PRIORITY_7;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcHandshaking     = DMA_CH_SRC_HANDSHAKING_HARDWARE;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstHandshaking     = DMA_CH_DST_HANDSHAKING_SOFTWARE;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcHsInterface     = spi_bus_obj[i].config->dma_rx->HsInterface;

            /* DMA controller must be enabled before initializing the channel */
            DMA_ControllerCmd(spi_bus_obj[i].config->dma_rx->Instance, ENABLE);

            /* Initialize the specified DMA channel and Whether the specified channel was successfully initialized */
            if (DMA_ChannelInit(spi_bus_obj[i].config->dma_rx->Instance, &spi_bus_obj[i].dma.RX_DMA_ChInitStr, spi_bus_obj[i].config->dma_rx->dma_channel) == 0U)
            {
                /* Configure DMAMUX */
                DMAMUX_SetRequestID(DMAMUX1_ID, spi_bus_obj[i].config->dma_rx->dmamux_channel, spi_bus_obj[i].config->dma_rx->dmamux_request);

                spi_bus_obj[i].dma.DMA_Rx_Init = RT_TRUE;
            }
            else
            {
                LOG_E("SPI RX DMA channel initialization failed!");
                return -RT_ERROR;
            }
#endif
        }

        if (spi_bus_obj[i].spi_dma_flag & SPI_USING_TX_DMA_FLAG)
        {
#if defined(SOC_SERIES_N32H7xx)
            /* Configure the SPI TX DMA for Transmission process */
            /* Enable DMA clock */
            RCC_EnableAHB1PeriphClk3(spi_bus_obj[i].config->dma_tx->dma_rcc, ENABLE);
            /* Enable DMA MUXclock  */
            RCC_EnableAHB1PeriphClk1(RCC_AHB1_PERIPHEN_M7_DMAMUX1, ENABLE);

            /* SPI_MASTER_Tx_DMA_Channel DMA1 Channel1 configuration ---------------------------------------------*/
            DMA_ChannelStructInit(&spi_bus_obj[i].dma.TX_DMA_ChInitStr);
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.IntEn              = 0x1U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstAddr            = (uint32_t)&spi_bus_obj[i].config->SPIx->DAT;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcAddr            = NULL;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcTfrWidth        = DMA_CH_TRANSFER_WIDTH_8;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstTfrWidth        = DMA_CH_TRANSFER_WIDTH_8;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstAddrCountMode   = DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcAddrCountMode   = DMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstBurstLen        = DMA_CH_BURST_LENGTH_1;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcBurstLen        = DMA_CH_BURST_LENGTH_1;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcGatherEn        = 0x0U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstScatterEn       = 0x0U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.TfrTypeFlowCtrl    = DMA_CH_TRANSFER_FLOW_M2P_DMA;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.BlkTfrSize         = 0U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.pLinkListItem      = NULL;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcGatherInterval  = 0x0U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcGatherCount     = 0x0U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstScatterInterval = 0x0U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstScatterCount    = 0x0U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.TfrType            = DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.ChannelPriority    = DMA_CH_PRIORITY_7;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcHandshaking     = DMA_CH_SRC_HANDSHAKING_SOFTWARE;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstHandshaking     = DMA_CH_DST_HANDSHAKING_HARDWARE;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstHsInterface     = spi_bus_obj[i].config->dma_tx->HsInterface;

            /* DMA controller must be enabled before initializing the channel */
            DMA_ControllerCmd(spi_bus_obj[i].config->dma_tx->Instance, ENABLE);

            /* Initialize the specified DMA channel and Whether the specified channel was successfully initialized */
            if (DMA_ChannelInit(spi_bus_obj[i].config->dma_tx->Instance, &spi_bus_obj[i].dma.TX_DMA_ChInitStr, spi_bus_obj[i].config->dma_tx->dma_channel) == 0U)
            {
                /* Configure DMAMUX */
                DMAMUX_SetRequestID(DMAMUX1_ID, spi_bus_obj[i].config->dma_tx->dmamux_channel, spi_bus_obj[i].config->dma_tx->dmamux_request);

                spi_bus_obj[i].dma.DMA_Tx_Init = RT_TRUE;
            }
            else
            {
                LOG_E("SPI TX DMA channel initialization failed!");
                return -RT_ERROR;
            }
#endif
        }


        /* initialize completion object */
        rt_completion_init(&spi_bus_obj[i].cpt);

        result = rt_spi_bus_register(&spi_bus_obj[i].spi_bus, spi_config[i].bus_name, &n32_spi_ops);
        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init done", spi_config[i].bus_name);
    }

    return result;
}


/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    result = rt_spi_bus_attach_device_cspin(spi_device, device_name, bus_name, cs_pin, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    RT_ASSERT(result == RT_EOK);

    LOG_D("%s attach to %s done", device_name, bus_name);

    return result;
}


#if defined(BSP_SPI1_RX_USING_DMA) || defined(BSP_SPI1_TX_USING_DMA) ||  \
    defined(BSP_SPI2_RX_USING_DMA) || defined(BSP_SPI2_TX_USING_DMA) ||  \
    defined(BSP_SPI3_RX_USING_DMA) || defined(BSP_SPI3_TX_USING_DMA) ||  \
    defined(BSP_SPI4_RX_USING_DMA) || defined(BSP_SPI4_TX_USING_DMA) ||  \
    defined(BSP_SPI5_RX_USING_DMA) || defined(BSP_SPI5_TX_USING_DMA) ||  \
    defined(BSP_SPI6_RX_USING_DMA) || defined(BSP_SPI6_TX_USING_DMA) ||  \
    defined(BSP_SPI7_RX_USING_DMA) || defined(BSP_SPI7_TX_USING_DMA)
static void spi_isr(struct n32_spi *spi_drv)
{
    if (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG) == SET)
    {
        SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_TX | SPI_I2S_DMA_RX, DISABLE);

        if (spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG)
        {
#if defined(SOC_SERIES_N32H7xx)
            DMA_ChannelEventCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, DISABLE);
#endif
        }

        if (spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG)
        {
#if defined(SOC_SERIES_N32H7xx)
            DMA_ChannelEventCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, DISABLE);
#endif
        }

        SPI_I2S_EnableInt(spi_drv->config->SPIx, SPI_I2S_INT_ERR, DISABLE);

        SPI_I2S_ReceiveData(spi_drv->config->SPIx);
        SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);
    }
}

#if defined(BSP_SPI1_RX_USING_DMA)  || \
    defined(BSP_SPI2_RX_USING_DMA)  || \
    defined(BSP_SPI3_RX_USING_DMA)  || \
    defined(BSP_SPI4_RX_USING_DMA)  || \
    defined(BSP_SPI5_RX_USING_DMA)  || \
    defined(BSP_SPI6_RX_USING_DMA)  || \
    defined(BSP_SPI7_RX_USING_DMA)
static void spi_rx_dma_isr(struct n32_spi *spi_drv)
{
#if defined(SOC_SERIES_N32H7xx)
    if (DMA_GetCombinedStatus(spi_drv->config->dma_rx->Instance))
    {
        if (DMA_GetChannelIntTfrStatus(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel) == SET)
        {
#endif
            if (spi_drv->Direct == SPI_Tx_Rx)
            {
                SPI_I2S_EnableInt(spi_drv->config->SPIx, SPI_I2S_INT_ERR, DISABLE);

#if defined(SOC_SERIES_N32H7xx)
                DMA_ChannelEventCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, DISABLE);
                DMA_ChannelEventCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, DISABLE);
#endif

                if (spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_MASTER && spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_DOUBLELINE_FULLDUPLEX)
                {
                    SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_TX | SPI_I2S_DMA_RX, DISABLE);
                }

                SPI_I2S_ReceiveData(spi_drv->config->SPIx);
                SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);

                spi_drv->Direct = SPI_Idle;
                rt_completion_done(&spi_drv->cpt);
            }
            else if (spi_drv->Direct == SPI_Rx)
            {
                if (spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_MASTER && (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_RX ||
                        spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_DOUBLELINE_RONLY))
                {
                    SPI_Enable(spi_drv->config->SPIx, DISABLE);
                }

                SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_RX, DISABLE);

                SPI_I2S_EnableInt(spi_drv->config->SPIx, SPI_I2S_INT_ERR, DISABLE);

#if defined(SOC_SERIES_N32H7xx)
                DMA_ChannelEventCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, DISABLE);
#endif

                SPI_I2S_ReceiveData(spi_drv->config->SPIx);
                SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);

                spi_drv->Direct = SPI_Idle;
                rt_completion_done(&spi_drv->cpt);
            }

#if defined(SOC_SERIES_N32H7xx)
            /* Clear interrupt event status */
            DMA_ClearChannelEventStatus(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE);
#endif
        }
    }
}
#endif

static void spi_tx_dma_isr(struct n32_spi *spi_drv)
{
#if defined(SOC_SERIES_N32H7xx)
    if (DMA_GetCombinedStatus(spi_drv->config->dma_tx->Instance))
    {
        if (DMA_GetChannelIntTfrStatus(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel) == SET)
        {
#endif
            if (spi_drv->Direct == SPI_Tx)
            {
                DMA_ChannelEventCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, DISABLE);

                SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_TX, DISABLE);

                SPI_I2S_ReceiveData(spi_drv->config->SPIx);
                SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);

                spi_drv->Direct = SPI_Idle;
                rt_completion_done(&spi_drv->cpt);
            }

            /* Clear interrupt event status */
            DMA_ClearChannelEventStatus(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE);
        }
    }
}
#endif

#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI1_RX_USING_DMA)
void SPI1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(&spi_bus_obj[SPI1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI1_RX_USING_DMA) */
#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_RX_USING_DMA)
void SPI1_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_rx_dma_isr(&spi_bus_obj[SPI1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI1) && defined(BSP_SPI1_RX_USING_DMA) */
#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_TX_USING_DMA)
void SPI1_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_tx_dma_isr(&spi_bus_obj[SPI1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI1) && defined(BSP_SPI1_TX_USING_DMA) */


#if defined(BSP_SPI2_TX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA)
void SPI2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(&spi_bus_obj[SPI2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI2_TX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA) */
#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_RX_USING_DMA)
void SPI2_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_rx_dma_isr(&spi_bus_obj[SPI2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI2) && defined(BSP_SPI2_RX_USING_DMA) */
#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_TX_USING_DMA)
void SPI2_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_tx_dma_isr(&spi_bus_obj[SPI2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI2) && defined(BSP_SPI2_TX_USING_DMA) */



#if defined(BSP_SPI3_TX_USING_DMA) || defined(BSP_SPI3_RX_USING_DMA)
void SPI3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(&spi_bus_obj[SPI3_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI3_TX_USING_DMA) || defined(BSP_SPI3_RX_USING_DMA) */
#if defined(BSP_USING_SPI3) && defined(BSP_SPI3_RX_USING_DMA)
void SPI3_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_rx_dma_isr(&spi_bus_obj[SPI3_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI3) && defined(BSP_SPI3_RX_USING_DMA) */
#if defined(BSP_USING_SPI3) && defined(BSP_SPI3_TX_USING_DMA)
void SPI3_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_tx_dma_isr(&spi_bus_obj[SPI3_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI3) && defined(BSP_SPI3_TX_USING_DMA) */



#if defined(BSP_SPI4_TX_USING_DMA) || defined(BSP_SPI4_RX_USING_DMA)
void SPI4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(&spi_bus_obj[SPI4_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI4_TX_USING_DMA) || defined(BSP_SPI4_RX_USING_DMA) */
#if defined(BSP_USING_SPI4) && defined(BSP_SPI4_RX_USING_DMA)
void SPI4_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_rx_dma_isr(&spi_bus_obj[SPI4_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI4) && defined(BSP_SPI4_RX_USING_DMA) */
#if defined(BSP_USING_SPI4) && defined(BSP_SPI4_TX_USING_DMA)
void SPI4_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_tx_dma_isr(&spi_bus_obj[SPI4_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI4) && defined(BSP_SPI4_TX_USING_DMA) */




#if defined(BSP_SPI5_TX_USING_DMA) || defined(BSP_SPI5_RX_USING_DMA)
void SPI5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(&spi_bus_obj[SPI5_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI5_TX_USING_DMA) || defined(BSP_SPI5_RX_USING_DMA) */
#if defined(BSP_USING_SPI5) && defined(BSP_SPI5_RX_USING_DMA)
void SPI5_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_rx_dma_isr(&spi_bus_obj[SPI5_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI5) && defined(BSP_SPI5_RX_USING_DMA) */
#if defined(BSP_USING_SPI5) && defined(BSP_SPI5_TX_USING_DMA)
void SPI5_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_tx_dma_isr(&spi_bus_obj[SPI5_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI5) && defined(BSP_SPI5_TX_USING_DMA) */




#if defined(BSP_SPI6_TX_USING_DMA) || defined(BSP_SPI6_RX_USING_DMA)
void SPI6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(&spi_bus_obj[SPI6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI6_TX_USING_DMA) || defined(BSP_SPI6_RX_USING_DMA) */
#if defined(BSP_USING_SPI6) && defined(BSP_SPI6_RX_USING_DMA)
void SPI6_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_rx_dma_isr(&spi_bus_obj[SPI6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI6) && defined(BSP_SPI6_RX_USING_DMA) */
#if defined(BSP_USING_SPI6) && defined(BSP_SPI6_TX_USING_DMA)
void SPI6_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_tx_dma_isr(&spi_bus_obj[SPI6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI6) && defined(BSP_SPI6_TX_USING_DMA) */



#if defined(BSP_SPI7_TX_USING_DMA) || defined(BSP_SPI7_RX_USING_DMA)
void SPI7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(&spi_bus_obj[SPI7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI7_TX_USING_DMA) || defined(BSP_SPI7_RX_USING_DMA) */
#if defined(BSP_USING_SPI7) && defined(BSP_SPI7_RX_USING_DMA)
void SPI7_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_rx_dma_isr(&spi_bus_obj[SPI7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI7) && defined(BSP_SPI7_RX_USING_DMA) */
#if defined(BSP_USING_SPI7) && defined(BSP_SPI7_TX_USING_DMA)
void SPI7_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_tx_dma_isr(&spi_bus_obj[SPI7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI7) && defined(BSP_SPI7_TX_USING_DMA) */

static void n32_spi_get_dma_config(void)
{
#ifdef BSP_USING_SPI1
    spi_bus_obj[SPI1_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI1_RX_USING_DMA
    spi_bus_obj[SPI1_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi1_dma_rx = SPI1_RX_DMA_CONFIG;
    spi_config[SPI1_INDEX].dma_rx = &spi1_dma_rx;
#endif /* BSP_SPI1_RX_USING_DMA */
#ifdef BSP_SPI1_TX_USING_DMA
    spi_bus_obj[SPI1_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi1_dma_tx = SPI1_TX_DMA_CONFIG;
    spi_config[SPI1_INDEX].dma_tx = &spi1_dma_tx;
#endif /* BSP_SPI1_TX_USING_DMA */
#endif /* BSP_USING_SPI1 */

#ifdef BSP_USING_SPI2
    spi_bus_obj[SPI2_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI2_RX_USING_DMA
    spi_bus_obj[SPI2_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi2_dma_rx = SPI2_RX_DMA_CONFIG;
    spi_config[SPI2_INDEX].dma_rx = &spi2_dma_rx;
#endif /* BSP_SPI2_RX_USING_DMA */
#ifdef BSP_SPI2_TX_USING_DMA
    spi_bus_obj[SPI2_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi2_dma_tx = SPI2_TX_DMA_CONFIG;
    spi_config[SPI2_INDEX].dma_tx = &spi2_dma_tx;
#endif /* BSP_SPI2_TX_USING_DMA */
#endif /* BSP_USING_SPI2 */

#ifdef BSP_USING_SPI3
    spi_bus_obj[SPI3_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI3_RX_USING_DMA
    spi_bus_obj[SPI3_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi3_dma_rx = SPI3_RX_DMA_CONFIG;
    spi_config[SPI3_INDEX].dma_rx = &spi3_dma_rx;
#endif /* BSP_SPI3_RX_USING_DMA */
#ifdef BSP_SPI3_TX_USING_DMA
    spi_bus_obj[SPI3_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi3_dma_tx = SPI3_TX_DMA_CONFIG;
    spi_config[SPI3_INDEX].dma_tx = &spi3_dma_tx;
#endif /* BSP_SPI3_TX_USING_DMA */
#endif /* BSP_USING_SPI3 */

#ifdef BSP_USING_SPI4
    spi_bus_obj[SPI4_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI4_RX_USING_DMA
    spi_bus_obj[SPI4_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi4_dma_rx = SPI4_RX_DMA_CONFIG;
    spi_config[SPI4_INDEX].dma_rx = &spi4_dma_rx;
#endif /* BSP_SPI4_RX_USING_DMA */
#ifdef BSP_SPI4_TX_USING_DMA
    spi_bus_obj[SPI4_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi4_dma_tx = SPI4_TX_DMA_CONFIG;
    spi_config[SPI4_INDEX].dma_tx = &spi4_dma_tx;
#endif /* BSP_SPI4_TX_USING_DMA */
#endif /* BSP_USING_SPI4 */

#ifdef BSP_USING_SPI5
    spi_bus_obj[SPI5_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI5_RX_USING_DMA
    spi_bus_obj[SPI5_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi5_dma_rx = SPI5_RX_DMA_CONFIG;
    spi_config[SPI5_INDEX].dma_rx = &spi5_dma_rx;
#endif /* BSP_SPI5_RX_USING_DMA */
#ifdef BSP_SPI5_TX_USING_DMA
    spi_bus_obj[SPI5_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi5_dma_tx = SPI5_TX_DMA_CONFIG;
    spi_config[SPI5_INDEX].dma_tx = &spi5_dma_tx;
#endif /* BSP_SPI5_TX_USING_DMA */
#endif /* BSP_USING_SPI5 */

#ifdef BSP_USING_SPI6
    spi_bus_obj[SPI6_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI6_RX_USING_DMA
    spi_bus_obj[SPI6_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi6_dma_rx = SPI6_RX_DMA_CONFIG;
    spi_config[SPI6_INDEX].dma_rx = &spi6_dma_rx;
#endif /* BSP_SPI6_RX_USING_DMA */
#ifdef BSP_SPI6_TX_USING_DMA
    spi_bus_obj[SPI6_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi6_dma_tx = SPI6_TX_DMA_CONFIG;
    spi_config[SPI6_INDEX].dma_tx = &spi6_dma_tx;
#endif /* BSP_SPI6_TX_USING_DMA */
#endif /* BSP_USING_SPI6 */

#ifdef BSP_USING_SPI7
    spi_bus_obj[SPI7_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI7_RX_USING_DMA
    spi_bus_obj[SPI7_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi7_dma_rx = SPI7_RX_DMA_CONFIG;
    spi_config[SPI7_INDEX].dma_rx = &spi7_dma_rx;
#endif /* BSP_SPI7_RX_USING_DMA */
#ifdef BSP_SPI7_TX_USING_DMA
    spi_bus_obj[SPI7_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi7_dma_tx = SPI7_TX_DMA_CONFIG;
    spi_config[SPI7_INDEX].dma_tx = &spi7_dma_tx;
#endif /* BSP_SPI7_TX_USING_DMA */
#endif /* BSP_USING_SPI7 */
}


int rt_hw_spi_init(void)
{
    n32_spi_get_dma_config();
    return rt_hw_spi_bus_init();
}
INIT_BOARD_EXPORT(rt_hw_spi_init);


#endif /* BSP_USING_SPI1 || BSP_USING_SPI2 || BSP_USING_SPI3 || BSP_USING_SPI4 || BSP_USING_SPI5 || BSP_USING_SPI6 || BSP_USING_SPI7 */
#endif /* BSP_USING_SPI */

