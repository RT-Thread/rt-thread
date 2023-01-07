/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//FIXME no BL808/BL606p header file including is Allowed here
#ifdef BL808
#include <bl808_spi.h>
#include <bl808_glb.h>
#elif defined(BL606P)
#include <bl606p_spi.h>
#include <bl606p_glb.h>
#else
#error "Use CHIP BL808/BL606P for this module"
#endif

#include "bl808_glb_gpio.h"
#include "hosal_spi.h"
#include "blog.h"

static void spi_basic_init(hosal_spi_dev_t *arg)
{
    hosal_spi_dev_t *hw_arg = arg;
    SPI_CFG_Type spicfg;
    SPI_FifoCfg_Type fifocfg;
    SPI_ID_Type spi_id;

    spi_id = hw_arg->port;

    /* clock config */
    SPI_SetClock(spi_id, hw_arg->config.freq);

    /* spi config */
    spicfg.deglitchEnable = DISABLE;
    spicfg.slavePin = SPI_SLAVE_PIN_4;
    spicfg.continuousEnable = ENABLE;
    spicfg.byteSequence = SPI_BYTE_INVERSE_BYTE0_FIRST;
    spicfg.bitSequence = SPI_BIT_INVERSE_MSB_FIRST;
    if (hw_arg->config.polar_phase == 0) {
        spicfg.clkPhaseInv = SPI_CLK_PHASE_INVERSE_0;
        spicfg.clkPolarity = SPI_CLK_POLARITY_LOW;
    } else if (hw_arg->config.polar_phase == 1) {
        spicfg.clkPhaseInv = SPI_CLK_PHASE_INVERSE_1;
        spicfg.clkPolarity = SPI_CLK_POLARITY_LOW;
    } else if (hw_arg->config.polar_phase == 2) {
        spicfg.clkPhaseInv = SPI_CLK_PHASE_INVERSE_0;
        spicfg.clkPolarity = SPI_CLK_POLARITY_HIGH;
    } else if (hw_arg->config.polar_phase == 3) {
        spicfg.clkPhaseInv = SPI_CLK_PHASE_INVERSE_1;
        spicfg.clkPolarity = SPI_CLK_POLARITY_HIGH;
    } else {
        blog_error("node support polar_phase \r\n");
    }
    spicfg.frameSize = SPI_FRAME_SIZE_8;
    SPI_Init(spi_id, &spicfg);

    if (hw_arg->config.mode == 0) {
        SPI_Disable(spi_id, SPI_WORK_MODE_MASTER);
    } else {
        SPI_Disable(spi_id, SPI_WORK_MODE_SLAVE);
    }
    SPI_IntMask(spi_id, SPI_INT_ALL, MASK);

    /* fifo */
    fifocfg.txFifoThreshold = 1;
    fifocfg.rxFifoThreshold = 1;
    if (hw_arg->config.dma_enable) {
        fifocfg.txFifoDmaEnable = ENABLE;
        fifocfg.rxFifoDmaEnable = ENABLE;
        SPI_FifoConfig(spi_id,&fifocfg);
    } else {
        fifocfg.txFifoDmaEnable = DISABLE;
        fifocfg.rxFifoDmaEnable = DISABLE;
        SPI_FifoConfig(spi_id,&fifocfg);
        blog_info("spi no dma mode\r\n");
    }
}

static int hosal_spi_trans(hosal_spi_dev_t *spi, uint8_t *tx_data, uint8_t *rx_data, uint32_t length, uint32_t timeout)
{
    int ret = -1;

    /* Clear tx and rx fifo */
    SPI_ClrTxFifo(spi->port);
    SPI_ClrRxFifo(spi->port);

    if (spi->config.mode == 0) {
        SPI_Enable(spi->port, SPI_WORK_MODE_MASTER);
    } else {
        SPI_Enable(spi->port, SPI_WORK_MODE_SLAVE);
    }

    if (tx_data && rx_data)
        ret = SPI_SendRecvData(spi->port, tx_data, rx_data, length, SPI_TIMEOUT_DISABLE);
    else if (tx_data)
        ret = SPI_SendData(spi->port, tx_data, length, SPI_TIMEOUT_DISABLE);
    else if (rx_data)
        ret = SPI_ReceiveData(spi->port, rx_data, length, SPI_TIMEOUT_DISABLE);

    if (spi->config.mode == 0) {
        SPI_Disable(spi->port, SPI_WORK_MODE_MASTER);
    } else {
        SPI_Disable(spi->port, SPI_WORK_MODE_SLAVE);
    }
    return ret;
}

static void hosal_spi_gpio_init(hosal_spi_dev_t *arg)
{
    if (!arg) {
        blog_error("arg err.\r\n");
        return;
    }

    GLB_GPIO_Type gpiopins[3];
    gpiopins[0] = arg->config.pin_clk;
    gpiopins[1] = arg->config.pin_mosi;
    gpiopins[2] = arg->config.pin_miso;
    GLB_GPIO_Func_Init(GPIO_FUN_SPI0, gpiopins, sizeof(gpiopins)/sizeof(gpiopins[0]));

    if (arg->config.mode == 0) {
        if(arg->port == SPI0_ID) {       
            GLB_Set_MCU_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_MASTER);  
        } else {      
            GLB_Set_DSP_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_MASTER);  
        }
    } else {
        if(arg->port == SPI0_ID) {       
            GLB_Set_MCU_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_SLAVE);  
        } else {      
            GLB_Set_DSP_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_SLAVE);  
        }
    }

    return;
}

int hosal_spi_init(hosal_spi_dev_t *spi)
{
    hosal_spi_dev_t *dev = spi;
    if (NULL == spi ) {
        blog_error("arg err.\r\n");
    }

    hosal_spi_gpio_init(dev);
    spi_basic_init(dev);
    if (dev->config.dma_enable) {
        blog_error("unsupport.\r\n");
        return -1;
    }
    return 0;
}

int hosal_spi_set_cs(uint8_t pin, uint8_t value)
{
    GLB_GPIO_Cfg_Type cfg;
    cfg.gpioPin = pin;
    cfg.gpioFun = GPIO_FUN_GPIO;
    cfg.gpioMode = GPIO_MODE_OUTPUT;
    cfg.pullType = GPIO_PULL_UP;
    cfg.drive = 0;
    cfg.smtCtrl = 1;

    if (GLB_GPIO_Get_Fun(pin) != GPIO_FUN_GPIO)
        GLB_GPIO_Init(&cfg);
    GLB_GPIO_Write(pin, value);
    return 0;
}

int hosal_spi_irq_callback_set(hosal_spi_dev_t *spi, hosal_spi_irq_t pfn, void *p_arg)
{
    if (NULL == spi ) {
        blog_error("not init.\r\n");
        return -1;
    }

    spi->cb = pfn;
    spi->p_arg = p_arg;
    return 0;
}

int hosal_spi_finalize(hosal_spi_dev_t *spi)
{
    if (NULL == spi ) {
        blog_error("not init.\r\n");
        return -1;
    }

    if (spi->config.dma_enable) {
        blog_error("unsupport.\r\n");
        return -1;
    }
    SPI_DeInit(spi->port);
    return 0;
}

int hosal_spi_send(hosal_spi_dev_t *spi, const uint8_t *data, uint32_t size, uint32_t timeout)
{
    int ret;

    if (NULL == spi || data == NULL) {
        blog_error("not init.\r\n");
        return -1;
    }

    if (spi->config.dma_enable) {
        blog_error("unsupport.\r\n");
        ret = -1;
    } else {
        ret = hosal_spi_trans(spi, (uint8_t *)data, NULL, size, timeout);
    }
    return ret;
}

int hosal_spi_recv(hosal_spi_dev_t *spi, uint8_t *data, uint16_t size, uint32_t timeout)
{
    int ret;

    if (NULL == spi || data == NULL) {
        blog_error("not init.\r\n");
        return -1;
    }

    if (spi->config.dma_enable) {
        blog_error("unsupport.\r\n");
        ret = -1;
    } else {
        ret = hosal_spi_trans(spi, NULL, data, size, timeout);
    }
    return ret;
}

int hosal_spi_send_recv(hosal_spi_dev_t *spi, uint8_t *tx_data, uint8_t *rx_data, uint16_t size, uint32_t timeout)
{
    int ret;

    if (NULL == spi || tx_data == NULL || rx_data == NULL) {
        blog_error("not init.\r\n");
        return -1;
    }

    if (spi->config.dma_enable) {
        blog_error("unsupport.\r\n");
        ret = -1;
    } else {
        ret = hosal_spi_trans(spi, tx_data, rx_data, size, timeout);
    }
    return ret;
}

