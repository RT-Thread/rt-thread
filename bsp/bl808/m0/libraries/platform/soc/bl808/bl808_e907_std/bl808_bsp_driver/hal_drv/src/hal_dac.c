/**
 * @file hal_dac.c
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
#include "hal_dac.h"
#include "hal_dma.h"
#include "bl808_dac.h"
#include "bl808_glb.h"
#include "dac_config.h"

static dac_device_t dacx_device[] = {
#ifdef BSP_USING_DAC0
    DAC_CONFIG,
#endif
};

static uint8_t dac_channel_enable_check = 0;
/**
 * @brief
 *
 * @param dev
 * @param oflag
 * @return int
 */
int dac_open(struct device *dev, uint16_t oflag)
{
    dac_device_t *dac_device = (dac_device_t *)dev;
    uint8_t dac_div = 0;
    uint32_t tmpVal;

    uint32_t dac_clk = Clock_Peripheral_Clock_Get(BL_PERIPHERAL_CLOCK_DAC);

    if ((GLB_GPIO_Get_Fun(GLB_GPIO_PIN_11) == GPIO_FUN_ANALOG) && (dac_device->channels & DAC_CHANNEL_0)) {
        dac_channel_enable_check |= DAC_CHANNEL_0;
    }
    if ((GLB_GPIO_Get_Fun(GLB_GPIO_PIN_17) == GPIO_FUN_ANALOG) && (dac_device->channels & DAC_CHANNEL_1)) {
        dac_channel_enable_check |= DAC_CHANNEL_1;
    }

    if (dac_channel_enable_check == 0) {
        return -1;
    }

    switch (dac_device->sample_freq) {
        case DAC_SAMPLE_FREQ_500KHZ:
            dac_div = dac_clk / 500000;
            break;

        case DAC_SAMPLE_FREQ_8KHZ:
            dac_div = dac_clk / 8000;
            break;

        case DAC_SAMPLE_FREQ_16KHZ:
            dac_div = dac_clk / 16000;
            break;

        case DAC_SAMPLE_FREQ_44P1KHZ:
            dac_div = dac_clk / 441000;
            break;

        default:
            break;
    }

    if (dac_div == 1) {
        dac_div = DAC_CLK_DIV_1;
    } else if (dac_div == 16) {
        dac_div = DAC_CLK_DIV_16;
    } else if (dac_div == 32) {
        dac_div = DAC_CLK_DIV_32;
    } else if (dac_div == 64) {
        dac_div = DAC_CLK_DIV_64;
    } else
        return -2;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_DAC_CFG0);
    /*dac vref select*/
    if (dac_device->vref == DAC_VREF_EXTERNAL) {
        if (GLB_GPIO_Get_Fun(GLB_GPIO_PIN_7) != GPIO_FUN_ANALOG)
            return -1;
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPDAC_REF_SEL);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_GPDAC_REF_SEL);
    }
    BL_WR_REG(GLB_BASE, GLB_DAC_CFG0, tmpVal);

    /*dac reset*/
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_GPDACA_RSTN_ANA);
    BL_WR_REG(GLB_BASE, GLB_DAC_CFG0, tmpVal);
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_GPDACB_RSTN_ANA);
    BL_WR_REG(GLB_BASE, GLB_DAC_CFG0, tmpVal);
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    /* dac clear reset */
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPDACA_RSTN_ANA);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPDACB_RSTN_ANA);
    BL_WR_REG(GLB_BASE, GLB_DAC_CFG0, tmpVal);

    /* Set DAC div */
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_MODE, dac_div);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);

    /* select source */
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_CH_A_SEL, GPIP_DAC_ChanA_SRC_REG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_CH_B_SEL, GPIP_DAC_ChanB_SRC_REG);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);

    /* GPIP enable or disable channel */
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPDAC_EN);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);

    /* GLB enable or disable channel */
    if (dac_channel_enable_check & DAC_CHANNEL_0) {
        /* a channel */
        tmpVal = BL_RD_REG(GLB_BASE, GLB_DAC_CFG1);
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPDAC_IOA_EN);
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPDAC_A_EN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_A_RNG, DAC_REF_RNG_DEFAULT_SELECT);
        tmpVal = BL_WR_REG(GLB_BASE, GLB_DAC_CFG1, tmpVal);
    }
    if (dac_channel_enable_check & DAC_CHANNEL_1) {
        /* b channel */
        tmpVal = BL_RD_REG(GLB_BASE, GLB_DAC_CFG2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_GPDAC_B_RNG, DAC_REF_RNG_DEFAULT_SELECT);
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPDAC_IOB_EN);
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_GPDAC_B_EN);
        tmpVal = BL_WR_REG(GLB_BASE, GLB_DAC_CFG2, tmpVal);
    }

    /* GPIP disable DMA */
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_DMA_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPDAC_DMA_TX_EN);
    BL_WR_REG(GPIP_BASE, GPIP_GPDAC_DMA_CONFIG, tmpVal);

    if (oflag & DEVICE_OFLAG_DMA_TX) {
        /* GPIP select source */
        tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_CONFIG);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_CH_A_SEL, GPIP_DAC_ChanA_SRC_DMA);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_CH_B_SEL, GPIP_DAC_ChanB_SRC_DMA);
        BL_WR_REG(GPIP_BASE, GPIP_GPDAC_CONFIG, tmpVal);

        /* GPIP enable DMA */
        tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPDAC_DMA_CONFIG);
        if (dac_channel_enable_check == 2) {
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_DMA_FORMAT, GPIP_DAC_DMA_FORMAT_1);
        } else {
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPDAC_DMA_FORMAT, GPIP_DAC_DMA_FORMAT_0);
        }
        tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPDAC_DMA_TX_EN);
        BL_WR_REG(GPIP_BASE, GPIP_GPDAC_DMA_CONFIG, tmpVal);
    }

    return 0;
}
/**
 * @brief
 *
 * @param dev
 * @return int
 */
int dac_close(struct device *dev)
{
    GLB_GPIP_DAC_ChanA_Cfg_Type chCfg = { 0 };
    GLB_GPIP_DAC_Cfg_Type dacCfg = { 0 };
    GLB_GPIP_DAC_Init(&dacCfg);
    GLB_GPIP_DAC_Set_ChanA_Config(&chCfg);
    GLB_GPIP_DAC_Set_ChanB_Config((GLB_GPIP_DAC_ChanB_Cfg_Type *)&chCfg);
    GPIP_Set_DAC_DMA_TX_Disable();
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
int dac_control(struct device *dev, int cmd, void *args)
{
    dac_device_t *dac_device = (dac_device_t *)dev;

    switch (cmd) {
        case DEVICE_CTRL_SET_INT:

            break;

        case DEVICE_CTRL_CLR_INT:

            break;

        case DEVICE_CTRL_GET_INT:

            break;

        case DEVICE_CTRL_CONFIG:

            break;

        case DEVICE_CTRL_RESUME:

            break;

        case DEVICE_CTRL_SUSPEND:

            break;

        case DEVICE_CTRL_ATTACH_TX_DMA:
            dac_device->tx_dma = (struct device *)args;
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
int dac_write(struct device *dev, uint32_t pos, const void *buffer, uint32_t size)
{
    int ret = 0;
    enum dac_sample_frequence channel = (enum dac_sample_frequence)pos;
    dac_device_t *dac_device = (dac_device_t *)dev;
    uint32_t i = 0;

    if (dev->oflag & DEVICE_OFLAG_DMA_TX) {
        struct device *dma_ch = (struct device *)dac_device->tx_dma;

        if (!dma_ch) {
            return -1;
        }

        ret = dma_reload(dma_ch, (uint32_t)(uintptr_t)buffer, (uint32_t)DMA_ADDR_DAC_TDR, size);
        dma_channel_start(dma_ch);
        return ret;
    } else if (dev->oflag & DEVICE_OFLAG_STREAM_TX) {
        if (channel & DAC_CHANNEL_ALL) {
            for (i = 0; i < size; i++) {
                GLB_DAC_Set_ChanA_Value(*((uint16_t *)buffer + i));
                GLB_DAC_Set_ChanB_Value(*((uint16_t *)buffer + i));
            }
        } else if (channel & DAC_CHANNEL_0) {
            for (i = 0; i < size; i++) {
                GLB_DAC_Set_ChanA_Value(*((uint16_t *)buffer + i));
            }
        } else if (channel & DAC_CHANNEL_1) {
            for (i = 0; i < size; i++) {
                GLB_DAC_Set_ChanB_Value(*((uint16_t *)buffer + i));
            }
        } else {
            return -1;
        }
        return 0;
    }

    return -1;
}

/**
 * @brief
 *
 * @param index
 * @param name
 * @return int
 */
int dac_register(enum dac_index_type index, const char *name)
{
    struct device *dev;

    if (DAC_MAX_INDEX == 0) {
        return -DEVICE_EINVAL;
    }

    dev = &(dacx_device[index].parent);

    dev->open = dac_open;
    dev->close = dac_close;
    dev->control = dac_control;
    dev->write = dac_write;
    dev->read = NULL;

    dev->type = DEVICE_CLASS_DAC;
    dev->handle = NULL;

    device_register(dev, name);

    return 0;
}
