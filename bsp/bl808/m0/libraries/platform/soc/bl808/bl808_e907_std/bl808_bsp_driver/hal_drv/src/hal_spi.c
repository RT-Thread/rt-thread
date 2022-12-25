/**
 * @file hal_spi.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "hal_spi.h"
#include "hal_dma.h"
#include "bl808_glb.h"
#include "bl808_spi.h"

#ifdef BSP_USING_SPI0
static void SPI0_IRQ_Function(void);
#endif
#ifdef BSP_USING_SPI1
static void SPI1_IRQ_Function(void);
#endif

static spi_device_t spix_device[SPI_MAX_INDEX] = {
#ifdef BSP_USING_SPI0
    SPI0_CONFIG,
#endif
#ifdef BSP_USING_SPI1
    SPI1_CONFIG,
#endif
};

// static uint8_t SPI_IRQ_NumList[SPI_ID_MAX] = {SPI0_IRQn, SPI1_IRQn};
extern const uint32_t spiAddr[];

/**
 * @brief
 *
 * @param dev
 * @param oflag
 * @return int
 */
int spi_open(struct device *dev, uint16_t oflag)
{
    spi_device_t *spi_device = (spi_device_t *)dev;
    SPI_CFG_Type spiCfg = { 0 };
    SPI_FifoCfg_Type fifoCfg = { 0 };
    SPI_ClockCfg_Type clockCfg;
    uint32_t spi_clk;

    /* reset SPI (close SPI)*/
    SPI_DeInit(spi_device->id);

    switch (spi_device->id)
    {
    case 0:
        GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_SPI);
        GLB_Set_SPI_CLK(ENABLE, GLB_SPI_CLK_MCU_MUXPLL_160M, 0);
        CPU_Interrupt_Disable(SPI0_IRQn);
        GLB_Swap_MCU_SPI_0_MOSI_With_MISO(spi_device->pin_swap_enable);
        GLB_Set_MCU_SPI_0_ACT_MOD_Sel(spi_device->mode);
        break;
    case 1:
        GLB_Set_DSP_SPI_CLK(ENABLE, GLB_DSP_SPI_CLK_DSP_MUXPLL_160M, 0);
        CPU_Interrupt_Disable(SPI1_IRQn);
        GLB_Swap_DSP_SPI_0_MOSI_With_MISO(spi_device->pin_swap_enable);
        GLB_Set_DSP_SPI_0_ACT_MOD_Sel(spi_device->mode);
        break;
    default:
        break;
    }

    /* get spi peripheral clock */
    spi_clk = Clock_Peripheral_Clock_Get(BL_PERIPHERAL_CLOCK_SPI0 + spi_device->id);

    /* Out of maximum clock */
    if((spi_clk >> 1) < spi_device->clk ){
        return -1;
    }
    uint8_t div = spi_clk / spi_device->clk;

    clockCfg.dataPhase0Len = (div >> 1);
    clockCfg.dataPhase1Len = (div >> 1);
    clockCfg.startLen = (div >> 1);
    clockCfg.stopLen = (div >> 1);
    clockCfg.intervalLen = (div >> 1);

    if(div % 2){
        /* When Phase0 and Phase1 are not equal, increase the high level time */
        if((uint8_t)spi_device->clk_polaraity == (uint8_t)spi_device->clk_phase){
            clockCfg.dataPhase0Len += 1;
        }else{
            clockCfg.dataPhase1Len += 1;
        }
    }

    SPI_ClockConfig(spi_device->id, &clockCfg);

    /* Continuous transmission is enabled by default */
    spiCfg.continuousEnable = 1;

    if (spi_device->direction == SPI_LSB_BYTE0_DIRECTION_FIRST) {
        spiCfg.bitSequence = SPI_BIT_INVERSE_LSB_FIRST;
        spiCfg.byteSequence = SPI_BYTE_INVERSE_BYTE0_FIRST;
    } else if (spi_device->direction == SPI_LSB_BYTE3_DIRECTION_FIRST) {
        spiCfg.bitSequence = SPI_BIT_INVERSE_LSB_FIRST;
        spiCfg.byteSequence = SPI_BYTE_INVERSE_BYTE3_FIRST;
    } else if (spi_device->direction == SPI_MSB_BYTE0_DIRECTION_FIRST) {
        spiCfg.bitSequence = SPI_BIT_INVERSE_MSB_FIRST;
        spiCfg.byteSequence = SPI_BYTE_INVERSE_BYTE0_FIRST;
    } else if (spi_device->direction == SPI_MSB_BYTE3_DIRECTION_FIRST) {
        spiCfg.bitSequence = SPI_BIT_INVERSE_MSB_FIRST;
        spiCfg.byteSequence = SPI_BYTE_INVERSE_BYTE3_FIRST;
    }

    spiCfg.clkPolarity = spi_device->clk_polaraity;
    spiCfg.clkPhaseInv = spi_device->clk_phase;
    spiCfg.frameSize = spi_device->datasize;

    if (spi_device->delitch_cnt) {
        spiCfg.deglitchEnable = 1;
        SPI_SetDeglitchCount(spi_device->id, spi_device->delitch_cnt - 1);
    }else{
        spiCfg.deglitchEnable = 0;
    }

    /* SPI config */
    SPI_Init(spi_device->id, &spiCfg);

    if(fifoCfg.txFifoThreshold){
        fifoCfg.txFifoThreshold = spi_device->fifo_threshold - 1;
        fifoCfg.rxFifoThreshold = spi_device->fifo_threshold - 1;
    }else{
        fifoCfg.txFifoThreshold = spi_device->fifo_threshold;
        fifoCfg.rxFifoThreshold = spi_device->fifo_threshold;
    }
    fifoCfg.txFifoDmaEnable = DISABLE;
    fifoCfg.rxFifoDmaEnable = DISABLE;

    if (oflag & DEVICE_OFLAG_INT_TX || oflag & DEVICE_OFLAG_INT_RX) {
#ifdef BSP_USING_SPI0
        if(spi_device->id == 0){
            Interrupt_Handler_Register(SPI0_IRQn, SPI0_IRQ_Function);
        }
#endif
#ifdef BSP_USING_SPI1
        if(spi_device->id == 1){
            Interrupt_Handler_Register(SPI1_IRQn, SPI1_IRQ_Function);
        }
#endif
    }

    if (oflag & DEVICE_OFLAG_DMA_TX) {
        fifoCfg.txFifoDmaEnable = ENABLE;
    }

    if (oflag & DEVICE_OFLAG_DMA_RX) {
        fifoCfg.rxFifoDmaEnable = ENABLE;
    }

    SPI_FifoConfig(spi_device->id, &fifoCfg);
    /* Enable spi master mode */
    SPI_Enable(spi_device->id, spi_device->mode);

    return 0;
}
/**
 * @brief
 *
 * @param dev
 * @return int
 */
int spi_close(struct device *dev)
{
    spi_device_t *spi_device = (spi_device_t *)dev;

    SPI_DeInit(spi_device->id);

    return 0;
}
/**
 * @brief
 *
 * @param dev
 * @param cmd
 * @param args
 * @return int
 */
int spi_control(struct device *dev, int cmd, void *args)
{
    spi_device_t *spi_device = (spi_device_t *)dev;

    switch (cmd) {
        case DEVICE_CTRL_SET_INT /* constant-expression */:

            break;

        case DEVICE_CTRL_CLR_INT /* constant-expression */:
            /* code */
            break;

        case DEVICE_CTRL_GET_INT /* constant-expression */:
            /* code */
            break;

        case DEVICE_CTRL_RESUME:
            /* code */
            SPI_Enable(spi_device->id, spi_device->mode);
            break;

        case DEVICE_CTRL_SUSPEND:
            SPI_Disable(spi_device->id, spi_device->mode);
            break;

        case DEVICE_CTRL_ATTACH_TX_DMA:
            spi_device->tx_dma = (struct device *)args;
            break;

        case DEVICE_CTRL_ATTACH_RX_DMA:
            spi_device->rx_dma = (struct device *)args;
            break;

        case DEVICE_CTRL_SPI_CONFIG_CLOCK:
            SPI_SetClock(spi_device->id, (uint32_t)(uintptr_t)args);
            break;

        case DEVICE_CTRL_TX_DMA_SUSPEND: {
            uint32_t tmpVal = BL_RD_REG(spiAddr[spi_device->id], SPI_FIFO_CONFIG_0);
            tmpVal = BL_CLR_REG_BIT(tmpVal, SPI_DMA_TX_EN);
            BL_WR_REG(spiAddr[spi_device->id], SPI_FIFO_CONFIG_0, tmpVal);
            dev->oflag &= ~DEVICE_OFLAG_DMA_TX;
            break;
        }

        case DEVICE_CTRL_RX_DMA_SUSPEND: {
            uint32_t tmpVal = BL_RD_REG(spiAddr[spi_device->id], SPI_FIFO_CONFIG_0);
            tmpVal = BL_CLR_REG_BIT(tmpVal, SPI_DMA_RX_EN);
            BL_WR_REG(spiAddr[spi_device->id], SPI_FIFO_CONFIG_0, tmpVal);
            dev->oflag &= ~DEVICE_OFLAG_DMA_RX;
            break;
        }

        case DEVICE_CTRL_TX_DMA_RESUME: {
            uint32_t tmpVal = BL_RD_REG(spiAddr[spi_device->id], SPI_FIFO_CONFIG_0);
            tmpVal = BL_SET_REG_BIT(tmpVal, SPI_DMA_TX_EN);
            BL_WR_REG(spiAddr[spi_device->id], SPI_FIFO_CONFIG_0, tmpVal);
            dev->oflag |= DEVICE_OFLAG_DMA_TX;
            break;
        }

        case DEVICE_CTRL_RX_DMA_RESUME: {
            uint32_t tmpVal = BL_RD_REG(spiAddr[spi_device->id], SPI_FIFO_CONFIG_0);
            tmpVal = BL_SET_REG_BIT(tmpVal, SPI_DMA_RX_EN);
            BL_WR_REG(spiAddr[spi_device->id], SPI_FIFO_CONFIG_0, tmpVal);
            dev->oflag |= DEVICE_OFLAG_DMA_RX;
            break;
        }
        case DEVICE_CTRL_SPI_GET_TX_FIFO :
            return SPI_GetTxFifoCount(spi_device->id);

        case DEVICE_CTRL_SPI_GET_RX_FIFO :
            return SPI_GetRxFifoCount(spi_device->id);

        case DEVICE_CTRL_SPI_CLEAR_TX_FIFO :
            return SPI_ClrTxFifo(spi_device->id);

        case DEVICE_CTRL_SPI_CLEAR_RX_FIFO :
            return SPI_ClrRxFifo(spi_device->id);

        case DEVICE_CTRL_SPI_GET_BUS_BUSY_STATUS :
            return SPI_GetBusyStatus(spi_device->id);

        case DEVICE_CTRL_SPI_SET_FRAME_SIZE:
            SPI_SetFrameSize(spi_device->id, (uint32_t)(uintptr_t)args);
            spi_device->datasize = (uint32_t)(uintptr_t)args;
            break;
        default:
            break;
    }

    return 0;
}
/**
 * @brief
 *
 * @param dev
 * @param pos
 * @param buffer
 * @param size
 * @return int
 */
int spi_write(struct device *dev, uint32_t pos, const void *buffer, uint32_t size)
{
    int ret = 0;
    spi_device_t *spi_device = (spi_device_t *)dev;

    if (dev->oflag & DEVICE_OFLAG_DMA_TX) {
        struct device *dma_ch = (struct device *)spi_device->tx_dma;
        if (!dma_ch) {
            return -1;
        }
        /* Set valid width for each fifo entry */
        if(spi_device->datasize != DMA_DEV(dma_ch)->dst_width){
            switch (DMA_DEV(dma_ch)->dst_width) {
                case DMA_TRANSFER_WIDTH_8BIT:
                    SPI_SetFrameSize(spi_device->id, SPI_FRAME_SIZE_8);
                    break;
                case DMA_TRANSFER_WIDTH_16BIT:
                    SPI_SetFrameSize(spi_device->id, SPI_FRAME_SIZE_16);
                    break;

                case DMA_TRANSFER_WIDTH_32BIT:
                    SPI_SetFrameSize(spi_device->id, SPI_FRAME_SIZE_32);
                    break;
                default:
                    break;
            }
            spi_device->datasize = DMA_DEV(dma_ch)->dst_width;
        }

        if(spi_device->id == 0){
            ret = dma_reload(dma_ch, (uint32_t)(uintptr_t)buffer, (uint32_t)DMA_ADDR_SPI0_TDR, size);
        }else if(spi_device->id == 1){
            ret = dma_reload(dma_ch, (uint32_t)(uintptr_t)buffer, (uint32_t)DMA_ADDR_SPI1_TDR, size);
        }
        dma_channel_start(dma_ch);

        return ret;

    } else if (dev->oflag & DEVICE_OFLAG_INT_TX) {
        return -2;
    } else {
        SPI_ClrRxFifo(spi_device->id);
        ret = SPI_SendData(spi_device->id, (void *)buffer, size, SPI_TIMEOUT_DISABLE);
        return 0;
    }
}
/**
 * @brief
 *
 * @param dev
 * @param pos
 * @param buffer
 * @param size
 * @return int
 */
int spi_read(struct device *dev, uint32_t pos, void *buffer, uint32_t size)
{
    int ret = 0;
    spi_device_t *spi_device = (spi_device_t *)dev;

    if (dev->oflag & DEVICE_OFLAG_DMA_RX) {
        struct device *dma_ch = (struct device *)spi_device->rx_dma;
        if (!dma_ch) {
            return -1;
        }

        /* Set valid width for each fifo entry */
        uint32_t tmpVal = BL_RD_REG(spiAddr[spi_device->id], SPI_CONFIG);
        switch (DMA_DEV(dma_ch)->dst_width) {
            case DMA_TRANSFER_WIDTH_8BIT:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_FRAME_SIZE, 0);
                break;
            case DMA_TRANSFER_WIDTH_16BIT:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_FRAME_SIZE, 1);
                break;

            case DMA_TRANSFER_WIDTH_32BIT:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SPI_CR_SPI_FRAME_SIZE, 3);
                break;
            default:
                break;
        }
        BL_WR_REG(spiAddr[spi_device->id], SPI_CONFIG,tmpVal);

        if(spi_device->id == 0){
            ret = dma_reload(dma_ch, (uint32_t)DMA_ADDR_SPI0_RDR, (uint32_t)(uintptr_t)buffer, size);
        }else if(spi_device->id == 1){
            ret = dma_reload(dma_ch, (uint32_t)DMA_ADDR_SPI1_RDR, (uint32_t)(uintptr_t)buffer, size);
        }
        dma_channel_start(dma_ch);
        return ret;

    } else if (dev->oflag & DEVICE_OFLAG_INT_TX) {
        return -2;
    } else {
        ret = SPI_ReceiveData(spi_device->id, buffer, size, SPI_TIMEOUT_DISABLE);
        return 0;
    }
}
/**
 * @brief
 *
 * @param index
 * @param name
 * @param flag
 * @return int
 */
int spi_register(enum spi_index_type index, const char *name)
{
    struct device *dev;

    if (SPI_MAX_INDEX == 0) {
        return -DEVICE_EINVAL;
    }

    dev = &(spix_device[index].parent);

    dev->open = spi_open;
    dev->close = spi_close;
    dev->control = spi_control;
    dev->write = spi_write;
    dev->read = spi_read;

    dev->type = DEVICE_CLASS_SPI;
    dev->handle = NULL;

    return device_register(dev, name);
}

/**
 * @brief
 *
 * @param handle
 */
void spi_isr(spi_device_t *handle)
{
    uint32_t tmpVal;
    uint32_t spix_base = spiAddr[handle->id];

    tmpVal = BL_RD_REG(spix_base, SPI_INT_STS);

    if (!handle->parent.callback) {
        return;
    }

    /* Transfer end interrupt,shared by both master and slave mode */
    if (BL_IS_REG_BIT_SET(tmpVal, SPI_END_INT) && !BL_IS_REG_BIT_SET(tmpVal, SPI_CR_SPI_END_MASK)) {
        BL_WR_REG(spix_base, SPI_INT_STS, BL_SET_REG_BIT(tmpVal, SPI_CR_SPI_END_CLR));
        handle->parent.callback(&handle->parent, NULL, 0, SPI_INT_END);
    }

    /* TX fifo ready interrupt(fifo count > fifo threshold) */
    if (BL_IS_REG_BIT_SET(tmpVal, SPI_TXF_INT) && !BL_IS_REG_BIT_SET(tmpVal, SPI_CR_SPI_TXF_MASK)) {
        handle->parent.callback(&handle->parent, NULL, 0, SPI_INT_TX_FIFO_REQ);
    }

    /*  RX fifo ready interrupt(fifo count > fifo threshold) */
    if (BL_IS_REG_BIT_SET(tmpVal, SPI_RXF_INT) && !BL_IS_REG_BIT_SET(tmpVal, SPI_CR_SPI_RXF_MASK)) {
        handle->parent.callback(&handle->parent, NULL, 0, SPI_INT_RX_FIFO_REQ);
    }

    /* Slave mode transfer time-out interrupt,triggered when bus is idle for the given value */
    if (BL_IS_REG_BIT_SET(tmpVal, SPI_STO_INT) && !BL_IS_REG_BIT_SET(tmpVal, SPI_CR_SPI_STO_MASK)) {
        BL_WR_REG(spix_base, SPI_INT_STS, BL_SET_REG_BIT(tmpVal, SPI_CR_SPI_STO_CLR));
        handle->parent.callback(&handle->parent, NULL, 0, SPI_INT_SLAVE_TIMEOUT);
    }

    /* Slave mode tx underrun error interrupt,trigged when tx is not ready during transfer */
    if (BL_IS_REG_BIT_SET(tmpVal, SPI_TXU_INT) && !BL_IS_REG_BIT_SET(tmpVal, SPI_CR_SPI_TXU_MASK)) {
        BL_WR_REG(spix_base, SPI_INT_STS, BL_SET_REG_BIT(tmpVal, SPI_CR_SPI_TXU_CLR));
        handle->parent.callback(&handle->parent, NULL, 0, SPI_INT_SLAVE_UNDERRUN);
    }

    /* TX/RX fifo overflow/underflow interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, SPI_FER_INT) && !BL_IS_REG_BIT_SET(tmpVal, SPI_CR_SPI_FER_MASK)) {
        handle->parent.callback(&handle->parent, NULL, 0, SPI_INT_FIFO_ERROR);
    }
}

#ifdef BSP_USING_SPI0
void SPI0_IRQ_Function()
{
    spi_isr(&spix_device[SPI0_INDEX]);
}
#endif

#ifdef BSP_USING_SPI1
void SPI1_IRQ_Function()
{
    spi_isr(&spix_device[SPI1_INDEX]);
}
#endif