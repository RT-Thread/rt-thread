/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     dw_spi.c
 * @brief    CSI Source File for SPI Driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#include "csi_core.h"
#include "drv_spi.h"
#include "dw_spi.h"
#include "drv_gpio.h"
#ifdef CONFIG_SPI_DMA
#include "ck_dmac.h"
#include <string.h>
#endif
#include "soc.h"   /*CONFIG_SPI_NUM*/

#define ERR_SPI(errno) (CSI_DRV_ERRNO_SPI_BASE | errno)

#define SPI_NULL_PARAM_CHK(para)                  \
    do {                                        \
        if (para == NULL) {                     \
            return ERR_SPI(EDRV_PARAMETER);   \
        }                                       \
    } while (0)

typedef struct {
    uint32_t base;
    uint32_t irq;
    pin_t ssel;
    spi_event_cb_t cb_event;
    void *cb_arg;
    uint32_t send_num;
    uint32_t recv_num;
    uint8_t *send_buf;
    uint8_t *recv_buf;
    uint8_t enable_slave;
    uint32_t transfer_num;
    uint32_t clk_num;            //clock number with a process of communication
    uint8_t state;              //Current SPI state
    uint32_t mode;               //Current SPI mode
    uint8_t ss_mode;
    spi_status_t status;
#ifdef CONFIG_SPI_DMA
    dmac_handle_t dma_handle;
    int32_t dma_tx_id;
    int32_t dma_rx_id;
#endif
} dw_spi_priv_t;

static dw_spi_priv_t spi_instance[CONFIG_SPI_NUM];
static gpio_pin_handle_t   pgpio_pin_handle;

static const spi_capabilities_t spi_capabilities = {
    .simplex = 1,           /* Simplex Mode (Master and Slave) */
    .ti_ssi = 1,            /* TI Synchronous Serial Interface */
    .microwire = 1,         /* Microwire Interface */
    .event_mode_fault = 0   /* Signal Mode Fault event: \ref CSKY_SPI_EVENT_MODE_FAULT */
};

static int32_t dw_spi_set_datawidth(dw_spi_reg_t *addr, DWENUM_SPI_DATAWIDTH datawidth);
static int32_t dw_spi_set_mode(spi_handle_t handle, DWENUM_SPI_MODE mode);

/**
  \brief use phobos gpio pin to simulate ss line for hardware controlled Output mode.
*/
static int32_t dw_spi_ss_init(dw_spi_priv_t *spi_priv)
{
    csi_gpio_port_initialize(0, NULL);
    pgpio_pin_handle = csi_gpio_pin_initialize(spi_priv->ssel);
    csi_gpio_pin_config(pgpio_pin_handle, GPIO_MODE_PULLNONE, GPIO_DIRECTION_OUTPUT);
    csi_gpio_pin_write(pgpio_pin_handle, true);
    spi_priv->ss_mode = SPI_SS_MASTER_HW_OUTPUT;
    return 0;
}

/**
  \brief control ss line depend on controlled Output mode.
*/
static int32_t dw_spi_ss_control(dw_spi_priv_t *spi_priv, spi_ss_stat_e stat)
{
    if (spi_priv->ss_mode == SPI_SS_MASTER_HW_OUTPUT) {
        if (stat == SPI_SS_INACTIVE) {
            csi_gpio_pin_write(pgpio_pin_handle, true);
        } else if (stat == SPI_SS_ACTIVE) {
            csi_gpio_pin_write(pgpio_pin_handle, false);
        } else {
            return -1;
        }
    }

    return 0;
}

#ifdef CONFIG_SPI_DMA
void dw_spi_dma_event_cb(dma_event_e event, int32_t ch)
{
    dw_spi_priv_t *spi_priv = NULL;

    uint8_t i = 0u;

    for (i = 0; i < CONFIG_SPI_NUM; i++) { /* find the SPI id */
        spi_priv = &spi_instance[i];

        if ((spi_priv->dma_tx_id == ch) || (spi_priv->dma_rx_id == ch)) {
            break;
        }
    }


    if (spi_priv->dma_tx_id == ch) {
        spi_priv->dma_tx_id = -1;
    } else {
        spi_priv->dma_rx_id = -1;
    }

    if (event == DMA_EVENT_TRANSFER_ERROR) {           /* DMA transfer ERROR */

        if (spi_priv->cb_event) {
            spi_priv->cb_event(SPI_EVENT_DATA_LOST, NULL);
        }
    } else if (event == DMA_EVENT_TRANSFER_DONE) {  /* DMA transfer complete */

        if (spi_priv->mode == DWENUM_SPI_TXRX) {
            if (spi_priv->cb_event) {
                spi_priv->cb_event(SPI_EVENT_TRANSFER_COMPLETE, spi_priv->cb_arg);
            }
        } else if (spi_priv->mode == DWENUM_SPI_TX) {
            dw_spi_reg_t *addr = (dw_spi_reg_t *)(spi_priv->base);

            while (addr->SR & DW_SPI_DISABLE);

            if (spi_priv->cb_event) {
                spi_priv->cb_event(SPI_EVENT_TX_COMPLETE, spi_priv->cb_arg);
            }
        } else {
            if (spi_priv->cb_event) {
                spi_priv->cb_event(SPI_EVENT_RX_COMPLETE, spi_priv->cb_arg);
            }
        }
    }

    spi_priv->status.busy = 0U;
}

/**
  \brief sending data to SPI transmitter with DMA,(received data is ignored).
*/
static int32_t dw_spi_dma_send(dw_spi_priv_t *spi_priv, const void *data, uint32_t num)
{
    int32_t ch = csi_dma_alloc_channel(spi_priv->dma_handle, -1);
    spi_priv->dma_tx_id = ch;

    dma_config_t config;
    config.src_inc  = DMA_ADDR_INC;
    config.dst_inc  = DMA_ADDR_CONSTANT;
    config.src_tw   = DMA_DATAWIDTH_SIZE8;
    config.dst_tw   = DMA_DATAWIDTH_SIZE8;
    config.hs_if    = CKENUM_DMA_SPI1_TX;
    config.type     = DMA_MEM2PERH;

    dw_spi_ss_control(spi_priv, SPI_SS_ACTIVE);

    dw_spi_reg_t *addr = (dw_spi_reg_t *)(spi_priv->base);
    uint8_t *ptxbuffer = (uint8_t *)data;

    int32_t ret = csi_dma_config(spi_priv->dma_handle, ch, ptxbuffer, (uint8_t *) & (addr->DR), num, &config, dw_spi_dma_event_cb);

    if (ret < 0) {
        return ret;
    }

    addr->SPIENR    = DW_SPI_DISABLE; /* enable SPI */
    dw_spi_set_mode(spi_priv, DWENUM_SPI_TX);

    addr->DMATDLR   = 0;
    addr->DMACR     = DW_SPI_TDMAE;
    addr->SER       = spi_priv->enable_slave;
    addr->SPIENR  = DW_SPI_ENABLE;
    csi_dma_start(spi_priv->dma_handle, ch);

    while (csi_dma_get_status(spi_priv->dma_handle, ch) != DMA_STATE_DONE);

    while (addr->SR & DW_SPI_BUSY);

    csi_dma_stop(spi_priv->dma_handle, ch);
    csi_dma_release_channel(spi_priv->dma_handle, ch);
    addr->SPIENR = DW_SPI_DISABLE;
    addr->SER = 0;

    dw_spi_ss_control(spi_priv, SPI_SS_INACTIVE);
    spi_priv->status.busy = 0U;
    return 0;

}

/**
  \brief receiving data from SPI receiver with DMA.
*/
static int32_t dw_spi_dma_receive(dw_spi_priv_t *spi_priv, void *data, uint32_t num)
{
    int32_t ch;
    ch = csi_dma_alloc_channel(spi_priv->dma_handle, -1);
    spi_priv->dma_tx_id = ch;

    dma_config_t config;

    config.src_inc  = DMA_ADDR_CONSTANT;
    config.dst_inc  = DMA_ADDR_INC;
    config.src_tw   = DMA_DATAWIDTH_SIZE8;
    config.dst_tw   = DMA_DATAWIDTH_SIZE8;
    config.hs_if    = CKENUM_DMA_SPI1_RX;
    config.type     = DMA_PERH2MEM;

    dw_spi_ss_control(spi_priv, SPI_SS_ACTIVE);
    uint8_t *prx_buffer = (uint8_t *)data;

    spi_priv->recv_buf      = prx_buffer;
    spi_priv->clk_num       = num;
    spi_priv->recv_num      = num;

    dw_spi_reg_t *addr = (dw_spi_reg_t *)(spi_priv->base);
    int32_t ret;

    while (spi_priv->clk_num) {
        if (spi_priv->clk_num >= DW_SPI_FIFO_MAX_LV / 2) {
            spi_priv->recv_num = DW_SPI_FIFO_MAX_LV / 2;
        }

        ret = csi_dma_config(spi_priv->dma_handle, ch, (uint8_t *) & (addr->DR), spi_priv->recv_buf, spi_priv->recv_num, &config, dw_spi_dma_event_cb);

        if (ret < 0) {
            return ret;
        }

        addr->SPIENR    = DW_SPI_DISABLE; /* enable SPI */
        dw_spi_set_mode(spi_priv, DWENUM_SPI_RX);
        addr->DMARDLR = spi_priv->recv_num - 1;
        addr->CTRLR1 = spi_priv->recv_num - 1;

        addr->DMACR = DW_SPI_RDMAE;
        addr->SER = spi_priv->enable_slave;
        csi_dma_start(spi_priv->dma_handle, ch);
        addr->SPIENR  = DW_SPI_ENABLE;
        addr->DR = DW_SPI_START_RX;

        while (csi_dma_get_status(spi_priv->dma_handle, ch) != DMA_STATE_DONE);

        csi_dma_stop(spi_priv->dma_handle, ch);
        spi_priv->clk_num -= spi_priv->recv_num;
        spi_priv->recv_buf += spi_priv->recv_num;


    }

    addr->SPIENR = DW_SPI_DISABLE;
    addr->SER = 0;
    csi_dma_release_channel(spi_priv->dma_handle, ch);
    dw_spi_ss_control(spi_priv, SPI_SS_INACTIVE);
    spi_priv->status.busy = 0U;
    return 0;

}

/**
  \brief sending/receiving data to/from SPI transmitter/receiver with DMA.
*/
static int32_t dw_spi_dma_transfer(dw_spi_priv_t *spi_priv, const void *data_out, void *data_in, uint32_t num_out, uint32_t num_in)
{
    int32_t tx_ch = csi_dma_alloc_channel(spi_priv->dma_handle, -1);

    if (tx_ch < 0) {
        return tx_ch;
    }

    spi_priv->dma_tx_id = tx_ch;

    int32_t rx_ch = csi_dma_alloc_channel(spi_priv->dma_handle, -1);

    if (rx_ch < 0) {
        return rx_ch;
    }

    spi_priv->dma_rx_id = rx_ch;

    dma_config_t tx_config, rx_config;

    tx_config.src_inc  = DMA_ADDR_INC;
    tx_config.dst_inc  = DMA_ADDR_CONSTANT;
    tx_config.src_tw   = DMA_DATAWIDTH_SIZE8;
    tx_config.dst_tw   = DMA_DATAWIDTH_SIZE8;
    tx_config.hs_if    = CKENUM_DMA_SPI1_TX;
    tx_config.type     = DMA_MEM2PERH;

    rx_config.src_inc  = DMA_ADDR_CONSTANT;
    rx_config.dst_inc  = DMA_ADDR_INC;
    rx_config.src_tw   = DMA_DATAWIDTH_SIZE8;
    rx_config.dst_tw   = DMA_DATAWIDTH_SIZE8;
    rx_config.hs_if    = CKENUM_DMA_SPI1_RX;
    rx_config.type     = DMA_PERH2MEM;

    dw_spi_ss_control(spi_priv, SPI_SS_ACTIVE);

    uint8_t *ptx_buffer = (uint8_t *)data_out;
    uint8_t *prx_buffer = (uint8_t *)data_in;
    spi_priv->send_buf      = ptx_buffer;
    spi_priv->recv_buf      = prx_buffer;
    spi_priv->send_num      = num_out;
    spi_priv->recv_num      = num_in;
    spi_priv->clk_num       = num_in;

    dw_spi_reg_t *addr = (dw_spi_reg_t *)(spi_priv->base);
    int32_t ret;
    uint8_t dma_send_buf[DW_SPI_FIFO_MAX_LV];

    while (spi_priv->clk_num) {
        if (spi_priv->clk_num >= DW_SPI_FIFO_MAX_LV) {
            spi_priv->transfer_num = DW_SPI_FIFO_MAX_LV;
        } else {
            spi_priv->transfer_num = spi_priv->clk_num;
        }

        if (spi_priv->send_num >= spi_priv->transfer_num) {
            memcpy(dma_send_buf, spi_priv->send_buf, spi_priv->transfer_num);
            spi_priv->send_num -= spi_priv->transfer_num;
            spi_priv->send_buf += spi_priv->transfer_num;
        } else {
            if (spi_priv->send_num > 0) {
                memcpy(dma_send_buf, spi_priv->send_buf, spi_priv->send_num);
                spi_priv->send_buf = NULL;
            }

            memset(&dma_send_buf[spi_priv->send_num], 0, spi_priv->transfer_num - spi_priv->send_num);
            spi_priv->send_num = 0;
        }

        ret = csi_dma_config(spi_priv->dma_handle, tx_ch, dma_send_buf, (uint8_t *) & (addr->DR), spi_priv->transfer_num, &tx_config, dw_spi_dma_event_cb);

        if (ret < 0) {
            return ret;
        }

        ret = csi_dma_config(spi_priv->dma_handle, rx_ch, (uint8_t *) & (addr->DR), spi_priv->recv_buf, spi_priv->transfer_num, &rx_config, dw_spi_dma_event_cb);

        if (ret < 0) {
            return ret;
        }

        addr->SPIENR    = DW_SPI_DISABLE;   /* disable SPI */
        addr->DMARDLR = (spi_priv->transfer_num - 1) % 16;          /* set dma receive data level */
        addr->DMATDLR = (spi_priv->transfer_num - 1) % 16 + 1;      /* set dma transmit data level */
        addr->DMACR   = DW_SPI_RDMAE | DW_SPI_TDMAE;
        dw_spi_set_mode(spi_priv, DWENUM_SPI_TXRX);
        addr->SER = spi_priv->enable_slave;
        addr->SPIENR    = DW_SPI_ENABLE;    /* enable SPI */

        ret = csi_dma_start(spi_priv->dma_handle, tx_ch);

        if (ret < 0) {
            return ret;
        }

        while (csi_dma_get_status(spi_priv->dma_handle, tx_ch) != DMA_STATE_DONE);

        ret = csi_dma_start(spi_priv->dma_handle, rx_ch);

        if (ret < 0) {
            return ret;
        }

        while (csi_dma_get_status(spi_priv->dma_handle, rx_ch) != DMA_STATE_DONE);

        spi_priv->recv_buf      += spi_priv->transfer_num;
        spi_priv->recv_num      -= spi_priv->transfer_num;
        spi_priv->clk_num       -= spi_priv->transfer_num;
        addr->SPIENR            = DW_SPI_DISABLE;
        csi_dma_stop(spi_priv->dma_handle, tx_ch);
        csi_dma_stop(spi_priv->dma_handle, rx_ch);
    }

    dw_spi_ss_control(spi_priv, SPI_SS_INACTIVE);
    addr->SER = 0;

    csi_dma_release_channel(spi_priv->dma_handle, tx_ch);
    csi_dma_release_channel(spi_priv->dma_handle, rx_ch);
    spi_priv->status.busy = 0U;

    return 0;

}
#endif


/**
  \brief       Set the SPI datawidth.
  \param[in]   addr pointer to register address
  \param[in]   datawidth  date frame size
  \return      error code
*/
static int32_t dw_spi_set_datawidth(dw_spi_reg_t *addr, DWENUM_SPI_DATAWIDTH datawidth)
{
    if ((datawidth >= DWENUM_SPI_DATASIZE_4) && (datawidth <= DWENUM_SPI_DATASIZE_16)) {
        uint16_t temp = addr->CTRLR0;
        temp &= 0xfff0;         /* temp has the value of CTRLR0 with DFS being cleared.*/
        temp |= (datawidth);    /* get the final CTRLR0 after datawidth config. */
        addr->CTRLR0 = temp;    /* write CTRLR0 */
        return 0;
    }

    return -1;
}

/**
  \brief       Set the SPI clock divider.
  \param[in]   addr     pointer to register address
  \param[in]   baud     spi baud rate
  \param[in]   apbfreq  sysclk for spi module.
  \return      error code
*/
static int32_t dw_spi_set_baudrate(dw_spi_reg_t *addr, int32_t baud, int32_t apbfreq)
{
    int32_t sckdv = apbfreq / baud;

    if (sckdv < 0x10000) {
        addr->BAUDR =  sckdv;
    } else {
        return -1;
    }

    return 0;
}

/**
  \brief       Set the SPI polarity.
  \param[in]   addr  pointer to register address
  \param[in]   polarity spi polarity
  \return      error code
*/
static int32_t dw_spi_set_polarity(dw_spi_reg_t *addr, DWENUM_SPI_POLARITY polarity)
{
    /* To config the polarity, we can set the SCPOL bit(CTRLR0[7]) as below:
     *     0 - inactive state of serial clock is low
     *     1 - inactive state of serial clock is high
     */
    switch (polarity) {
        case DWENUM_SPI_CLOCK_POLARITY_LOW:
            addr->CTRLR0 &= (~DW_SPI_POLARITY);
            break;

        case DWENUM_SPI_CLOCK_POLARITY_HIGH:
            addr->CTRLR0 |= DW_SPI_POLARITY;
            break;

        default:
            return -1;
    }

    return 0;
}

/**
  \brief       Set the SPI Phase.
  \param[in]   addr  pointer to register address
  \param[in]   phase    Serial clock phase
  \return      error code
*/
static int32_t dw_spi_set_phase(dw_spi_reg_t *addr, DWENUM_SPI_PHASE phase)
{
    switch (phase) {
        case DWENUM_SPI_CLOCK_PHASE_MIDDLE:
            addr->CTRLR0 &= (~DW_SPI_PHASE);
            break;

        case DWENUM_SPI_CLOCK_PHASE_START:
            addr->CTRLR0 |= DW_SPI_PHASE;
            break;

        default:
            return -1;
    }

    return 0;
}

/**
  \brief       Set the SPI mode.
  \param[in]   addr  pointer to register address
  \param[in]   mode     SPI_Mode
  \return      error code
*/
static int32_t dw_spi_set_mode(spi_handle_t handle, DWENUM_SPI_MODE mode)
{
    dw_spi_priv_t *spi_priv = handle;
    dw_spi_reg_t *addr = (dw_spi_reg_t *)(spi_priv->base);

    /* It is impossible to write to this register when the SSI is enabled.*/
    /* we can set the TMOD to config transfer mode as below:
     *     TMOD_BIT9  TMOD_BIT8      transfer mode
     *         0          0         transmit & receive
     *         0          1           transmit only
     *         1          0           receive only
     *         1          1             reserved
     */
    switch (mode) {
        case DWENUM_SPI_TXRX:
            addr->CTRLR0 &= (~DW_SPI_TMOD_BIT8);
            addr->CTRLR0 &= (~DW_SPI_TMOD_BIT9);
            break;

        case DWENUM_SPI_TX:
            addr->CTRLR0 |= DW_SPI_TMOD_BIT8;
            addr->CTRLR0 &= (~DW_SPI_TMOD_BIT9);
            break;

        case DWENUM_SPI_RX:
            addr->CTRLR0 &= (~DW_SPI_TMOD_BIT8);
            addr->CTRLR0 |= DW_SPI_TMOD_BIT9;
            break;

        default:
            addr->CTRLR0 |= DW_SPI_TMOD_BIT8;
            addr->CTRLR0 |= DW_SPI_TMOD_BIT9;
            break;
    }

    spi_priv->mode = mode;
    return 0;
}

/**
  \brief       interrupt service function for receive FIFO full interrupt .
  \param[in]   spi_priv pointer to spi private.
*/
static void dw_spi_intr_rx_full(dw_spi_priv_t *spi_priv)
{
    dw_spi_reg_t *addr = (dw_spi_reg_t *)(spi_priv->base);

    uint8_t temp = addr->ICR;
    uint8_t *pbuffer = spi_priv->recv_buf;
    uint32_t length = spi_priv->recv_num;


    uint8_t rxnum;
    rxnum = addr->RXFLR;
    uint32_t i = 0u;

    for (i = 0; i < rxnum; i++) {
        *pbuffer = addr->DR;
        pbuffer++;
    }

    length -= rxnum;

    if (length < DW_SPI_FIFO_MAX_LV) {
        addr->RXFTLR = length - 1;
    }

    if (length <= 0) {
        temp = addr->IMR;
        temp &= 0x2f;
        addr->IMR = temp;

        addr->SER = 0;
        addr->SPIENR = DW_SPI_DISABLE;
        spi_priv->status.busy = 0U;

        dw_spi_ss_control(spi_priv, SPI_SS_INACTIVE);

        if (spi_priv->cb_event) {
            spi_priv->cb_event(SPI_EVENT_RX_COMPLETE, spi_priv->cb_arg);
            return;
        }
    } else {
        addr->SPIENR    = DW_SPI_DISABLE;   /* disable SPI */
        dw_spi_set_mode(spi_priv, DWENUM_SPI_RX);
        addr->SER = spi_priv->enable_slave; /* enable all cs */
        spi_priv->recv_buf = pbuffer;
        spi_priv->recv_num = length;

        if (spi_priv->recv_num > DW_SPI_FIFO_MAX_LV) {
            addr->RXFTLR = DW_SPI_FIFO_MAX_LV - 1;
            addr->CTRLR1 = DW_SPI_FIFO_MAX_LV - 1;
        } else {
            addr->RXFTLR = spi_priv->recv_num - 1;
            addr->CTRLR1 = spi_priv->recv_num - 1;
        }

        addr->SPIENR = DW_SPI_ENABLE; /* enable SPI */
        addr->DR = DW_SPI_START_RX ;
    }

}

/**
  \brief       interrupt service function for transmit FIFO empty interrupt.
  \param[in]   spi_priv pointer to spi private.
*/
static void dw_spi_intr_tx_empty(dw_spi_priv_t *spi_priv)
{
    dw_spi_reg_t *addr = (dw_spi_reg_t *)(spi_priv->base);
    uint8_t temp = addr->ICR;

    /* transfer mode:transmit & receive */
    uint32_t i = 0u;

    if (spi_priv->
        mode == DWENUM_SPI_TXRX) {
        /* read data out from rx FIFO */
        while (spi_priv->transfer_num) {
            *spi_priv->recv_buf = addr->DR;
            spi_priv->recv_buf++;
            spi_priv->transfer_num--;
        }

        if (spi_priv->clk_num >= DW_SPI_FIFO_MAX_LV) {
            spi_priv->transfer_num = DW_SPI_FIFO_MAX_LV;
        } else {
            spi_priv->transfer_num = spi_priv->clk_num;
        }

        for (i = 0; i < spi_priv->transfer_num; i++) {
            if (spi_priv->send_num == 0) {
                addr->DR = 0x0;
            } else {
                addr->DR = *spi_priv->send_buf;
                spi_priv->send_buf++;
            }

            spi_priv->send_num--;
        }
    } else {    //transfer mode :transmit only
        if (spi_priv->clk_num >= DW_SPI_FIFO_MAX_LV) {
            spi_priv->transfer_num = DW_SPI_FIFO_MAX_LV;
        } else {
            spi_priv->transfer_num = spi_priv->clk_num;
        }

        for (i = 0; i < spi_priv->transfer_num; i++) {
            addr->DR = *spi_priv->send_buf;
            spi_priv->send_buf++;
            spi_priv->send_num--;
        }

    }

    if (spi_priv->clk_num == 0) {

        temp = addr->IMR;
        temp &= ~DW_SPI_IMR_TXEIM;
        addr->IMR = temp;

        addr->SER = 0;
        addr->SPIENR = DW_SPI_DISABLE;
        spi_priv->status.busy = 0U;

        dw_spi_ss_control(spi_priv, SPI_SS_INACTIVE);

        if (spi_priv->mode == DWENUM_SPI_TXRX) {
            if (spi_priv->cb_event) {
                spi_priv->cb_event(SPI_EVENT_TRANSFER_COMPLETE, spi_priv->cb_arg);
                return;
            }
        } else {
            if (spi_priv->cb_event) {
                spi_priv->cb_event(SPI_EVENT_TX_COMPLETE, spi_priv->cb_arg);
                return;
            }
        }
    }

    spi_priv->clk_num -= spi_priv->transfer_num;

}
/**
  \brief       handler the interrupt.
  \param[in]   spi      Pointer to \ref SPI_RESOURCES
*/
void dw_spi_irqhandler(int32_t idx)
{
    dw_spi_priv_t *spi_priv = &spi_instance[idx];
    dw_spi_reg_t *addr = (dw_spi_reg_t *)(spi_priv->base);

    uint32_t intr = addr->ISR;

    /* deal with receive FIFO full interrupt */
    if (intr & DW_SPI_RXFIFO_FULL) {
        dw_spi_intr_rx_full(spi_priv);
    }
    /* deal with transmit FIFO empty interrupt */
    else if (intr & DW_SPI_TXFIFO_EMPTY) {
        dw_spi_intr_tx_empty(spi_priv);
    }
}

int32_t __attribute__((weak)) target_spi_init(pin_t mosi, pin_t miso, pin_t sclk, pin_t ssel, uint32_t *base, uint32_t *irq)
{
    return -1;
}

/**
  \brief       Initialize SPI Interface. 1. Initializes the resources needed for the SPI interface 2.registers event callback function
  \param[in]   spi pin of mosi
  \param[in]   spi pin of miso
  \param[in]   spi pin of sclk
  \param[in]   spi pin of ssel
  \param[in]   cb_event  event call back function \ref spi_event_cb_t
  \return      return spi handle if success
*/
spi_handle_t csi_spi_initialize(pin_t mosi, pin_t miso, pin_t sclk, pin_t ssel, spi_event_cb_t cb_event, void *cb_arg)
{
    uint32_t base = 0u;
    uint32_t irq = 0u;

    int32_t idx = target_spi_init(mosi, miso, sclk, ssel, &base, &irq);

    if (idx < 0 || idx >= CONFIG_SPI_NUM) {
        return NULL;
    }

    dw_spi_priv_t *spi_priv = &spi_instance[idx];

    spi_priv->base = base;
    spi_priv->irq  = irq;
    spi_priv->ssel = ssel;

    spi_priv->cb_event          = cb_event;
    spi_priv->cb_arg            = cb_arg;
    spi_priv->status.busy       = 0U;
    spi_priv->status.data_lost  = 0U;
    spi_priv->status.mode_fault = 0U;
    spi_priv->enable_slave      = 1U;
    spi_priv->state             = SPI_INITIALIZED;

    drv_nvic_enable_irq(spi_priv->irq);
#ifdef CONFIG_SPI_DMA
    spi_priv->dma_handle = csi_dma_initialize(0);
#endif

    return (spi_handle_t)spi_priv;
}

/**
  \brief       De-initialize SPI Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle spi handle to operate.
  \return      error code
*/
int32_t csi_spi_uninitialize(spi_handle_t handle)
{
    SPI_NULL_PARAM_CHK(handle);

    dw_spi_priv_t *spi_priv = handle;
    drv_nvic_disable_irq(spi_priv->irq);

    spi_priv->cb_event          = NULL;
    spi_priv->state             = 0U;
    spi_priv->status.busy       = 0U;
    spi_priv->status.data_lost  = 0U;
    spi_priv->status.mode_fault = 0U;

#ifdef CONFIG_SPI_DMA
    csi_dma_uninitialize(spi_priv->dma_handle);
#endif
    return 0;
}

/**
  \brief       Get driver capabilities.
  \param[in]   spi instance to operate.
  \return      \ref spi_capabilities_t
*/
spi_capabilities_t csi_spi_get_capabilities(spi_handle_t handle)
{
    return spi_capabilities;
}

/**
  \brief       config spi mode.
  \param[in]   handle spi handle to operate.
  \param[in]   sysclk    sysclk for spi module.
  \param[in]   baud      spi baud rate. if negative, then this attribute not changed
  \param[in]   mode      \ref spi_mode_e . if negative, then this attribute not changed
  \param[in]   format    \ref spi_format_e . if negative, then this attribute not changed
  \param[in]   order     \ref spi_bit_order_e . if negative, then this attribute not changed
  \param[in]   ss_mode   \ref spi_ss_mode_e . if negative, then this attribute not changed
  \param[in]   bit_width spi data bitwidth: (1 ~ SPI_DATAWIDTH_MAX) . if negative, then this attribute not changed
  \return      error code
*/
int32_t csi_spi_config(spi_handle_t handle,
                       int32_t          sysclk,
                       int32_t          baud,
                       spi_mode_e       mode,
                       spi_format_e     format,
                       spi_bit_order_e  order,
                       spi_ss_mode_e    ss_mode,
                       int32_t          bit_width)
{
    SPI_NULL_PARAM_CHK(handle);

    dw_spi_priv_t *spi_priv = handle;
    dw_spi_reg_t *addr = (dw_spi_reg_t *)(spi_priv->base);

    if ((spi_priv->state & SPI_INITIALIZED) == 0U) {
        return ERR_SPI(EDRV_UNSUPPORTED);
    }

    if (spi_priv->status.busy) {
        return ERR_SPI(EDRV_BUSY);
    }

    spi_priv->status.busy       = 0U;
    spi_priv->status.data_lost  = 0U;
    spi_priv->status.mode_fault = 0U;

    addr->SPIENR    = DW_SPI_DISABLE;
    addr->IMR       = DW_SPI_INT_DISABLE;

    int32_t ret = 0;

    if (baud >= 0) {
        ret = dw_spi_set_baudrate(addr, baud, sysclk);

        if (ret < 0) {
            return ERR_SPI(EDRV_PARAMETER);
        }
    }

    if (mode >= 0) {
        switch (mode) {
            case SPI_MODE_MASTER:
                break;

            default:
                return ERR_SPI(EDRV_UNSUPPORTED);
        }
    }

    if (format >= 0) {
        switch (format) {
            case SPI_FORMAT_CPOL0_CPHA0:
                dw_spi_set_polarity(addr, DWENUM_SPI_CLOCK_POLARITY_LOW);
                dw_spi_set_phase(addr, DWENUM_SPI_CLOCK_PHASE_MIDDLE);
                break;

            case SPI_FORMAT_CPOL0_CPHA1:
                dw_spi_set_polarity(addr, DWENUM_SPI_CLOCK_POLARITY_LOW);
                dw_spi_set_phase(addr, DWENUM_SPI_CLOCK_PHASE_START);
                break;

            case SPI_FORMAT_CPOL1_CPHA0:
                dw_spi_set_polarity(addr, DWENUM_SPI_CLOCK_POLARITY_HIGH);
                dw_spi_set_phase(addr, DWENUM_SPI_CLOCK_PHASE_MIDDLE);
                break;

            case SPI_FORMAT_CPOL1_CPHA1:
                dw_spi_set_polarity(addr, DWENUM_SPI_CLOCK_POLARITY_HIGH);
                dw_spi_set_phase(addr, DWENUM_SPI_CLOCK_PHASE_START);
                break;

            default:
                return ERR_SPI(EDRV_PARAMETER);
        }
    }

    if (order >= 0) {
        //TD:
    }

    if (ss_mode >= 0) {
        switch (ss_mode) {
            case SPI_SS_MASTER_SW:
                spi_priv->ss_mode = SPI_SS_MASTER_SW;
                break;

            case SPI_SS_MASTER_HW_OUTPUT:
                dw_spi_ss_init(spi_priv);
                break;

            default:
                return ERR_SPI(EDRV_UNSUPPORTED);
        }
    }

    if (bit_width >= 0) {
        ret = dw_spi_set_datawidth(addr, bit_width);

        if (ret < 0) {
            return ERR_SPI(EDRV_PARAMETER);
        }
    }

    spi_priv->state |= SPI_CONFIGURED;

    return 0;
}

/**
  \brief       config spi default tx value.
  \param[in]   handle spi handle to operate.
  \param[in]   value     default tx value
  \return      error code
*/
int32_t csi_spi_set_default_tx_value(spi_handle_t handle, uint32_t value)
{
    SPI_NULL_PARAM_CHK(handle);

    return ERR_SPI(EDRV_UNSUPPORTED);
}

/**
  \brief       sending data to SPI transmitter,(received data is ignored).
               if non-blocking mode, this function only start the sending,
               \ref spi_event_e is signaled when operation completes or error happens.
               \ref csi_spi_get_status can indicates operation status.
               if blocking mode, this function return after operation completes or error happens.
  \param[in]   handle spi handle to operate.
  \param[in]   data  Pointer to buffer with data to send to SPI transmitter. data_type is : uint8_t for 1..8 data bits, uint16_t for 9..16 data bits,uint32_t for 17..32 data bits,
  \param[in]   num   Number of data items to send.
  \param[in]   block_mode   blocking and non_blocking to selcect
  \return      error code
*/
int32_t csi_spi_send(spi_handle_t handle, const void *data, uint32_t num, uint8_t block_mode)

{
    if (handle == NULL || data == NULL || num == 0) {
        return ERR_SPI(EDRV_PARAMETER);
    }

    dw_spi_priv_t *spi_priv = handle;

    if ((spi_priv->state & SPI_CONFIGURED) == 0U) {
        return ERR_SPI(EDRV_UNSUPPORTED);
    }

    if (spi_priv->status.busy) {
        return ERR_SPI(EDRV_BUSY);
    }

    spi_priv->status.busy       = 1U;
    spi_priv->status.data_lost  = 0U;
    spi_priv->status.mode_fault = 0U;


#ifdef CONFIG_SPI_DMA
    return dw_spi_dma_send(spi_priv, data, num);
#endif

    dw_spi_ss_control(spi_priv, SPI_SS_ACTIVE);
    dw_spi_reg_t *addr = (dw_spi_reg_t *)(spi_priv->base);
    addr->SPIENR    = DW_SPI_DISABLE; /* disable SPI */
    dw_spi_set_mode(spi_priv, DWENUM_SPI_TX);
    addr->SPIENR = DW_SPI_ENABLE; /* enable SPI */
    uint8_t *ptxbuffer = (uint8_t *)data;

    if (block_mode) {
        addr->SER = spi_priv->enable_slave;
        addr->TXFTLR            = DW_SPI_TXFIFO_LV;

        dw_spi_ss_control(spi_priv, SPI_SS_ACTIVE);
        spi_priv->send_num      = num;

        uint32_t once_len , i;

        while (spi_priv->send_num) {
            once_len = (spi_priv->send_num >= DW_SPI_FIFO_MAX_LV) ?
                       DW_SPI_FIFO_MAX_LV : spi_priv->send_num;

            for (i = 0; i < once_len; i++) {
                addr->DR = *ptxbuffer++;
            }

            while (!(addr->SR & DW_SPI_TFE));

            while (addr->SR & DW_SPI_BUSY);

            spi_priv->send_num -= once_len;
        }

        dw_spi_ss_control(spi_priv, SPI_SS_INACTIVE);
        spi_priv->status.busy   = 0U;
    } else {

        spi_priv->send_num      = num;
        spi_priv->clk_num       = num;
        spi_priv->send_buf      = ptxbuffer;
        spi_priv->transfer_num  = 0;
        addr->SPIENR            = DW_SPI_ENABLE; /* enable SPI */
        addr->TXFTLR            = DW_SPI_TXFIFO_LV;
        addr->SER               = spi_priv->enable_slave;
        addr->IMR               = DW_SPI_IMR_TXEIM;
    }

    return 0;
}

/**
\brief      receiving data from SPI receiver.transmits the default value as specified by csi_spi_set_default_tx_value
            if non-blocking mode, this function only start the receiving,
            \ref spi_event_e is signaled when operation completes or error happens.
            \ref csi_spi_get_status can indicates operation status.
            if blocking mode, this function return after operation completes or error happens.
\param[in]  handle spi handle to operate.
\param[out] data  Pointer to buffer for data to receive from SPI receiver
\param[in]  num   Number of data items to receive
\param[in]  block_mode   blocking and non_blocking to selcect
\return     error code
*/
int32_t csi_spi_receive(spi_handle_t handle, void *data, uint32_t num, uint8_t block_mode)
{

    if (handle == NULL || data == NULL || num == 0) {
        return ERR_SPI(EDRV_PARAMETER);
    }

    dw_spi_priv_t *spi_priv = handle;

    if ((spi_priv->state & SPI_CONFIGURED) == 0U) {
        return ERR_SPI(EDRV_UNSUPPORTED);
    }

    if (spi_priv->status.busy) {
        return ERR_SPI(EDRV_BUSY);
    }

    spi_priv->status.busy = 1U;
    spi_priv->status.data_lost = 0U;
    spi_priv->status.mode_fault = 0U;

#ifdef CONFIG_SPI_DMA
    return dw_spi_dma_receive(spi_priv, data, num);
#endif
    dw_spi_reg_t *addr = (dw_spi_reg_t *)(spi_priv->base);
    uint8_t *prx_buffer = data;

    if (block_mode) {
        dw_spi_ss_control(spi_priv, SPI_SS_ACTIVE);

        spi_priv->recv_buf = prx_buffer;
        spi_priv->recv_num = num;


        while (spi_priv->recv_num) {
            addr->SPIENR    = DW_SPI_DISABLE;   /* disable SPI */
            dw_spi_set_mode(spi_priv, DWENUM_SPI_RX);
            addr->SER = spi_priv->enable_slave;   /* enable all cs */

            uint32_t once_len = (spi_priv->recv_num >= DW_SPI_FIFO_MAX_LV) ?
                                DW_SPI_FIFO_MAX_LV : spi_priv->recv_num;
            addr->CTRLR1 = once_len - 1;
            addr->RXFTLR = once_len - 1;
            addr->SPIENR    = DW_SPI_ENABLE;
            addr->DR     = 0;

            while (addr->RXFLR < once_len);

            int i = 0;

            for (i = 0; i < once_len; i++) {
                *spi_priv->recv_buf++ = addr->DR;
            }

            spi_priv->recv_num -= once_len;
        }

        dw_spi_ss_control(spi_priv, SPI_SS_INACTIVE);
        spi_priv->status.busy   = 0U;
    } else {
        dw_spi_ss_control(spi_priv, SPI_SS_ACTIVE);

        addr->SPIENR    = DW_SPI_DISABLE;   /* disable SPI */
        spi_priv->recv_buf = prx_buffer;
        spi_priv->recv_num = num;
        dw_spi_set_mode(spi_priv, DWENUM_SPI_RX);
        addr->SER = spi_priv->enable_slave;   /* enable all cs */

        if (num > DW_SPI_FIFO_MAX_LV) {
            addr->RXFTLR = DW_SPI_FIFO_MAX_LV - 1;
            addr->CTRLR1 = DW_SPI_FIFO_MAX_LV - 1;
        } else {
            addr->RXFTLR = num - 1;
            addr->CTRLR1 = num - 1;
        }

        addr->IMR    = DW_SPI_IMR_RXFIM;
        addr->SPIENR = DW_SPI_ENABLE; /* enable SPI */
        addr->DR     = DW_SPI_START_RX ;

    }

    return 0;
}

/**
  \brief       sending/receiving data to/from SPI transmitter/receiver.
               if non-blocking mode, this function only start the transfer,
               \ref spi_event_e is signaled when operation completes or error happens.
               \ref csi_spi_get_status can indicates operation status.
               if blocking mode, this function return after operation completes or error happens.
  \param[in]   handle spi handle to operate.
  \param[in]   data_out  Pointer to buffer with data to send to SPI transmitter
  \param[out]  data_in   Pointer to buffer for data to receive from SPI receiver
  \param[in]   num_out      Number of data items to send
  \param[in]   num_in       Number of data items to receive
  \param[in]   block_mode   blocking and non_blocking to selcect
  \return      error code
*/
int32_t csi_spi_transfer(spi_handle_t handle, const void *data_out, void *data_in, uint32_t num_out, uint32_t num_in, uint8_t block_mode)
{
    if (handle == NULL || data_in == NULL || num_out == 0 || num_in == 0 || data_out == NULL) {
        return ERR_SPI(EDRV_PARAMETER);
    }

    dw_spi_priv_t *spi_priv = handle;

    if ((spi_priv->state & SPI_CONFIGURED) == 0U) {
        return ERR_SPI(EDRV_UNSUPPORTED);
    }

    if (spi_priv->status.busy) {
        return ERR_SPI(EDRV_BUSY);
    }

    spi_priv->status.busy = 1U;
    spi_priv->status.data_lost = 0U;
    spi_priv->status.mode_fault = 0U;

#ifdef CONFIG_SPI_DMA
    return dw_spi_dma_transfer(spi_priv, data_out, data_in, num_out, num_in);
#endif
    dw_spi_ss_control(spi_priv, SPI_SS_ACTIVE);
    dw_spi_reg_t *addr = (dw_spi_reg_t *)(spi_priv->base);

    addr->SPIENR    = DW_SPI_DISABLE;   /* disable SPI */
    dw_spi_set_mode(spi_priv, DWENUM_SPI_TXRX);
    addr->SER = spi_priv->enable_slave;   /* enable all cs */
    uint8_t *ptx_buffer = (uint8_t *)data_out;
    uint8_t *prx_buffer = (uint8_t *)data_in;
    uint32_t i = 0u;

    if (block_mode) {
        for (i = 0; i < num_out; i++) { /* transmit datas in transmit-buffer */
            addr->DR = *ptx_buffer;
            ptx_buffer++;
        }

        while ((addr->SR & DW_SPI_BUSY));

        while ((addr->SR & DW_SPI_TFE) == 0);

        while ((addr->SR & DW_SPI_RFNE) == 0);

        addr->SPIENR    = DW_SPI_DISABLE; /* disable SPI */

        dw_spi_set_mode(addr, DWENUM_SPI_RX);
        addr->SPIENR  = DW_SPI_ENABLE;
        addr->DR    = DW_SPI_START_RX;

        for (i = 0; i < num_in; i++) {
            *prx_buffer = addr->DR;
            prx_buffer++;
        }

        addr->SER = 0;

        dw_spi_ss_control(spi_priv, SPI_SS_INACTIVE);
        addr->SPIENR = DW_SPI_DISABLE;
        spi_priv->status.busy = 0U;
    } else {
        spi_priv->send_buf      = ptx_buffer;
        spi_priv->recv_buf      = prx_buffer;
        spi_priv->send_num      = num_out;
        spi_priv->recv_num      = num_in;
        spi_priv->clk_num       = num_in;
        spi_priv->transfer_num  = 0;

        addr->TXFTLR            = DW_SPI_TXFIFO_LV;
        addr->SPIENR            = DW_SPI_ENABLE;
        /* enable transmit FIFO empty interrupt */
        addr->IMR               |= DW_SPI_IMR_TXEIM;
    }

    return 0;

}

/**
  \brief       abort spi transfer.
  \param[in]   handle spi handle to operate.
  \return      error code
*/
int32_t csi_spi_abort_transfer(spi_handle_t handle)
{
    SPI_NULL_PARAM_CHK(handle);

    dw_spi_priv_t *spi_priv = handle;
    dw_spi_reg_t *addr = (dw_spi_reg_t *)(spi_priv->base);

    addr->SPIENR = DW_SPI_DISABLE;
    spi_priv->status.busy = 0U;
    spi_priv->recv_buf = NULL;
    spi_priv->recv_num = 0;

    return 0;
}

/**
  \brief       Get SPI status.
  \param[in]   handle spi handle to operate.
  \return      SPI status \ref ARM_SPI_STATUS
*/
spi_status_t csi_spi_get_status(spi_handle_t handle)
{
    spi_status_t spi_status = {0};

    if (handle == NULL) {
        return spi_status;
    }

    dw_spi_priv_t *spi_priv = handle;

    return spi_priv->status;
}

