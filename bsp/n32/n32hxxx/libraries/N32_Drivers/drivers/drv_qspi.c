/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"


#if defined(BSP_USING_QSPI2)

#include "drv_qspi.h"
#include "n32h7xx_xspi_v2.h"
#include "drv_config.h"
#include <string.h>

#define LOG_TAG "drv.qspi"
#include <drv_log.h>

#define XSPI_TIMEOUT_TICKS (1000U)
#define DMA_TRANS_MIN_LEN  (10U)

#define XSPI_XIP_BASE_ADDR 0x90000000

static struct rt_spi_bus _xspi_bus;
static struct n32_xspi _n32_xspi;


static rt_err_t xspi_wait_flag(XSPI_Module *xspi, uint32_t flag, uint32_t timeout)
{
    uint32_t tickstart = rt_tick_get();

    while (XSPI_GetFlagStatus(xspi, flag) == RESET)
    {
        if (((rt_tick_get() - tickstart) >= timeout) && (timeout != 0xFFFFFFFFU))
        {
            return -RT_ETIMEOUT;
        }
    }

    return RT_EOK;
}

static void XSPI_Wait_Tx_Compelete(void)
{
    while (XSPI_GetFlagStatus(xSPI2, XSPI_TXFE_FLAG) != SET)
    {
    }

    while (XSPI_GetFlagStatus(xSPI2, XSPI_BUSY_FLAG) != RESET)
    {
    }
}


static rt_err_t xspi_wait_flag_clear(XSPI_Module *xspi, uint32_t flag, uint32_t timeout)
{
    uint32_t tickstart = rt_tick_get();

    while (XSPI_GetFlagStatus(xspi, flag) != RESET)
    {
        if (((rt_tick_get() - tickstart) >= timeout) && (timeout != 0xFFFFFFFFU))
        {
            return -RT_ETIMEOUT;
        }
    }

    return RT_EOK;
}

static rt_err_t xspi_wait_busy(XSPI_Module *xspi, uint32_t timeout)
{
    return xspi_wait_flag_clear(xspi, XSPI_BUSY_FLAG, timeout);
}

/* ---- multi-line helpers ---- */

static uint32_t xspi_get_transfer_type(uint8_t instr_lines, uint8_t addr_lines)
{
    if (instr_lines == 1 && addr_lines == 1)
    {
        return XSPI_INST_ADDR_SINGLE_LINE;
    }

    if (addr_lines > 1 && instr_lines == 1)
    {
        return XSPI_INST_SINGLE_LINE_ADDR_MULTI_LINE;
    }

    if (instr_lines > 1 && addr_lines > 1)
    {
        return XSPI_INST_ADDR_MULTI_LINE;
    }

    return XSPI_INST_ADDR_SINGLE_LINE;
}

static uint32_t xspi_get_frame_format(uint8_t lines)
{
    switch (lines)
    {
    case 2:
        return XSPI_DUAL_LINE_MODE;

    case 4:
        return XSPI_QUAD_LINE_MODE;

    case 8:
        return XSPI_OCTAL_LINE_MODE;

    default:

        return XSPI_STANDARD_MODE;
    }
}
static void xspi_config_enhanced_for_msg(struct n32_xspi *xspi_config,
                                         struct rt_qspi_message *qspi_msg,
                                         uint32_t transfer_mode, rt_uint8_t ddr_enabled)
{
    xspi_config->EnhInitStructure.SCPH = xspi_config->InitStructure.SCPH;
    xspi_config->EnhInitStructure.SCPOL = xspi_config->InitStructure.SCPOL;

    xspi_config->EnhInitStructure.DataFrameSize = xspi_config->InitStructure.DataFrameSize;
    xspi_config->EnhInitStructure.Baudr = xspi_config->InitStructure.Baudr;

    xspi_config->EnhInitStructure.RxdSamplingEdge = xspi_config->InitStructure.RxdSamplingEdge;
    xspi_config->EnhInitStructure.RxdSampleDelay = xspi_config->InitStructure.RxdSampleDelay;


    if (qspi_msg->instruction.qspi_lines == 1)
    {
        xspi_config->EnhInitStructure.InstructLen = XSPI_INST_LEN_8BIT;
    }
    else if (qspi_msg->instruction.qspi_lines == 2)
    {
        xspi_config->EnhInitStructure.InstructLen = XSPI_INST_LEN_16BIT;
    }
    else
    {
        xspi_config->EnhInitStructure.InstructLen = XSPI_NO_INST_PHASE;
    }

    if (qspi_msg->address.size == 8)
    {
        xspi_config->EnhInitStructure.AddrLen = XSPI_ADDR_LEN_8BIT;
    }
    else if (qspi_msg->address.size == 16)
    {
        xspi_config->EnhInitStructure.AddrLen = XSPI_ADDR_LEN_16BIT;
    }
    else if (qspi_msg->address.size == 24)
    {
        xspi_config->EnhInitStructure.AddrLen = XSPI_ADDR_LEN_24BIT;
    }
    else if (qspi_msg->address.size == 32)
    {
        xspi_config->EnhInitStructure.AddrLen = XSPI_ADDR_LEN_32BIT;
    }
    else
    {
        xspi_config->EnhInitStructure.AddrLen = XSPI_NO_ADDR_PHASE;
    }

    xspi_config->EnhInitStructure.TransferMode = transfer_mode;

    xspi_config->EnhInitStructure.WaitCycles = qspi_msg->dummy_cycles;

    xspi_config->EnhInitStructure.FrameFormat = xspi_get_frame_format(qspi_msg->qspi_data_lines);

    xspi_config->EnhInitStructure.TransferType = xspi_get_transfer_type(qspi_msg->instruction.qspi_lines, qspi_msg->address.qspi_lines);

    xspi_config->EnhInitStructure.ClockStrech = xspi_config->InitStructure.EnhSlave_ClockStrech;

    xspi_config->EnhInitStructure.DDREable = ddr_enabled;

    XSPI_Slave_Select(_n32_xspi.xSPIx, xspi_config->slave_sel);
}


static rt_err_t xspi_qspi_transmit(struct n32_xspi *xspi_drv, struct rt_qspi_message *qspi_msg,
                                   uint32_t timeout)
{
    XSPI_Module *xspi = xspi_drv->xSPIx;

    uint8_t *buf = (uint8_t *)qspi_msg->parent.send_buf;
    uint32_t len = qspi_msg->parent.length, i = 0;
    rt_uint8_t ddr = xspi_drv->qspi_cfg ? xspi_drv->qspi_cfg->ddr_mode : 0;
    rt_err_t ret = RT_EOK;
    XSPI_Enable(xspi, DISABLE);

    xspi_config_enhanced_for_msg(xspi_drv, qspi_msg, XSPI_TX_ONLY_MODE, ddr);

    xspi_drv->EnhInitStructure.ClockStrech = XSPI_CLOCK_STRETCH_ENABLE;

    XSPI_InitEnhanced(xspi, &xspi_drv->EnhInitStructure);

    XSPI_SetNumberOfDataFrame(xspi, len);

    XSPI_Enable(xspi, ENABLE);

    if (len >= 16)
    {
        XSPI_SetTXStartFIFOThreshold(xspi, XSPI_FIFO_THRESHOLD_LEVEL15);
    }
    else if (len == 0)
    {
        XSPI_SetTXStartFIFOThreshold(xspi, XSPI_FIFO_THRESHOLD_LEVEL0);
    }
    else
    {
        XSPI_SetTXStartFIFOThreshold(xspi, (len - 1));
    }

    XSPI_SendData(xspi, qspi_msg->instruction.content);
    XSPI_SendData(xspi, qspi_msg->address.content);

    while (i < len)
    {
        if (XSPI_GetFlagStatus(xspi, XSPI_TXFNF_FLAG) == SET)
        {
            XSPI_SendData(xspi, buf[i++]);
        }
    }

    ret = xspi_wait_busy(xspi, timeout);

    XSPI_Enable(xspi, DISABLE);

    return ret;
}

static rt_err_t xspi_qspi_receive(struct n32_xspi *xspi_drv, struct rt_qspi_message *qspi_msg,
                                  uint32_t timeout)
{
    XSPI_Module *xspi = xspi_drv->xSPIx;
    uint8_t *buf = (uint8_t *)qspi_msg->parent.recv_buf;
    uint32_t len = qspi_msg->parent.length;

    rt_uint8_t ddr = xspi_drv->qspi_cfg ? xspi_drv->qspi_cfg->ddr_mode : 0;
    rt_err_t ret = RT_EOK;

    xspi_config_enhanced_for_msg(xspi_drv, qspi_msg, XSPI_RX_ONLY_MODE, ddr);

    xspi_drv->EnhInitStructure.ClockStrech = XSPI_CLOCK_STRETCH_ENABLE;

    XSPI_Enable(xspi, DISABLE);

    XSPI_InitEnhanced(xspi, &xspi_drv->EnhInitStructure);
    XSPI_SetNumberOfDataFrame(xspi, len);
    XSPI_ClearRxFIFO(xspi);
    XSPI_Enable(xspi, ENABLE);

    XSPI_SetRXFIFOFullThreshold(xspi, XSPI_FIFO_THRESHOLD_LEVEL1);
    XSPI_SetTXStartFIFOThreshold(xspi, XSPI_FIFO_THRESHOLD_LEVEL1);

    XSPI_SendData(xspi, qspi_msg->instruction.content);

    XSPI_SendData(xspi, qspi_msg->address.content);

    for (uint32_t i = 0; i < len; i++)
    {
        if (xspi_wait_flag(xspi, XSPI_RXFNE_FLAG, timeout) != RT_EOK)
        {
            ret = -RT_ETIMEOUT;
            goto exit;
        }

        buf[i] = XSPI_ReceiveData(xspi);
    }


    while (XSPI_GetFlagStatus(xspi, XSPI_BUSY_FLAG) != RESET)
    {
    }

    XSPI_ClearRxFIFO(xspi);

exit:

    XSPI_Enable(xspi, DISABLE);

    return ret;
}


/* ---- standard SPI (base mode) ---- */

static rt_err_t xspi_spi_transmit(struct n32_xspi *xspi_drv, struct rt_qspi_message *qspi_msg, uint32_t timeout)
{
    uint16_t i = 0, rindex = 0;

    uint8_t *send_buf = (uint8_t *)qspi_msg->parent.send_buf;
    uint8_t *recv_buf = (uint8_t *)qspi_msg->parent.recv_buf;

    XSPI_Module *xspi = xspi_drv->xSPIx;

    xspi_drv->InitStructure.FrameFormat = XSPI_STANDARD_MODE;

    XSPI_Slave_Select(_n32_xspi.xSPIx, xspi_drv->slave_sel);

    XSPI_Enable(xspi, DISABLE);

    XSPI_InitBase(xspi, &xspi_drv->InitStructure);

    XSPI_SetNumberOfDataFrame(xspi, qspi_msg->parent.length);

    XSPI_Wait_Tx_Compelete();

    XSPI_Enable(xspi, ENABLE);

    if (qspi_msg->parent.length > 16)
    {
        XSPI_SetTXStartFIFOThreshold(xspi, XSPI_FIFO_THRESHOLD_LEVEL15);
    }
    else if (qspi_msg->parent.length == 0)
    {
        XSPI_SetTXStartFIFOThreshold(xspi, XSPI_FIFO_THRESHOLD_LEVEL0);
    }
    else
    {
        XSPI_SetTXStartFIFOThreshold(xspi, (qspi_msg->parent.length - 1));
    }

    if (qspi_msg->parent.length <= 16)
    {
        while (i < qspi_msg->parent.length)
        {
            if (XSPI_GetFlagStatus(xspi, XSPI_TXFNF_FLAG) != RESET)
            {
                uint8_t tx = send_buf ? send_buf[i++] : 0xFF;

                XSPI_SendData(xspi, tx);
            }
        }

        XSPI_Wait_Tx_Compelete();

        if (recv_buf)
        {
            while (XSPI_GetFlagStatus(xspi, XSPI_RXFNE_FLAG) == SET)
            {
                if (rindex < qspi_msg->parent.length)
                {
                    recv_buf[rindex++] = XSPI_ReceiveData(xspi);
                }
                else
                {
                    XSPI_ReceiveData(xspi);
                }
            }
        }
    }
    else if (qspi_msg->parent.length > 16)
    {
        for (i = 0; i < qspi_msg->parent.length; i++)
        {
            uint8_t tx = send_buf ? send_buf[i] : 0xFF;

            if (xspi_wait_flag(xspi, XSPI_TXFNF_FLAG, timeout) != RT_EOK)
            {
                return -RT_ETIMEOUT;
            }

            XSPI_SendData(xspi, tx);

            if (recv_buf)
            {
                if (xspi_wait_flag(xspi, XSPI_RXFNE_FLAG, timeout) != RT_EOK)
                {
                    return -RT_ETIMEOUT;
                }

                recv_buf[i] = (uint8_t)XSPI_ReceiveData(xspi);
            }
        }
    }

    XSPI_Enable(xspi, DISABLE);

    return RT_EOK;
}


static rt_err_t xspi_spi_send(struct n32_xspi *xspi_drv, struct rt_qspi_message *qspi_msg, uint32_t timeout)
{
    uint16_t number = 0;

    uint8_t *buf = (uint8_t *)qspi_msg->parent.send_buf;

    XSPI_Module *xspi = xspi_drv->xSPIx;

    if (qspi_msg->instruction.content == 0)
    {
        return RT_ERROR;
    }

    XSPI_Enable(xspi, DISABLE);

    xspi_drv->InitStructure.FrameFormat = XSPI_STANDARD_MODE;

    XSPI_Slave_Select(_n32_xspi.xSPIx, xspi_drv->slave_sel);


    XSPI_InitBase(xspi, &xspi_drv->InitStructure);

    XSPI_SetNumberOfDataFrame(xspi, qspi_msg->parent.length);

    XSPI_Enable(xspi, ENABLE);

    XSPI_Wait_Tx_Compelete();

    XSPI_ClearRxFIFO(xspi);

    if (qspi_msg->parent.length > 16)
    {
        XSPI_SetTXStartFIFOThreshold(xspi, XSPI_FIFO_THRESHOLD_LEVEL15);
    }
    else if (qspi_msg->parent.length == 0)
    {
        XSPI_SetTXStartFIFOThreshold(xspi, XSPI_FIFO_THRESHOLD_LEVEL0);
    }
    else
    {
        XSPI_SetTXStartFIFOThreshold(xspi, (qspi_msg->parent.length));
    }

    XSPI_SendData(xspi, qspi_msg->instruction.content);

    XSPI_SendData(xspi, (qspi_msg->address.content & 0xff0000) >> 16);
    XSPI_SendData(xspi, (qspi_msg->address.content & 0xff00) >> 8);
    XSPI_SendData(xspi, qspi_msg->address.content & 0xff);


    while (number < qspi_msg->parent.length)
    {
        if (XSPI_GetFlagStatus(xspi, XSPI_TXFNF_FLAG) != RESET)
        {
            XSPI_SendData(xspi, buf[number++]);
        }
    }

    XSPI_Wait_Tx_Compelete();

    XSPI_Enable(xspi, DISABLE);

    return RT_EOK;
}


static rt_err_t xspi_spi_receive(struct n32_xspi *xspi_drv, struct rt_qspi_message *qspi_msg, uint32_t timeout)
{
    uint16_t i = 0, j = 0;
    uint8_t *buf = (uint8_t *)qspi_msg->parent.recv_buf;

    uint8_t s_data[5] = { 0 };

    if (qspi_msg->instruction.content == 0)
    {
        return RT_ERROR;
    }

    XSPI_Module *xspi = xspi_drv->xSPIx;

    xspi_drv->InitStructure.FrameFormat = XSPI_STANDARD_MODE;

    XSPI_Enable(xspi, DISABLE);

    XSPI_InitBase(xspi, &xspi_drv->InitStructure);

    XSPI_Slave_Select(_n32_xspi.xSPIx, xspi_drv->slave_sel);

    XSPI_SetNumberOfDataFrame(xspi, qspi_msg->parent.length);

    s_data[0] = qspi_msg->instruction.content;
    s_data[1] = (qspi_msg->address.content & 0xff0000) >> 16;
    s_data[2] = (qspi_msg->address.content & 0xff00) >> 8;
    s_data[3] = (qspi_msg->address.content & 0xff);

    XSPI_Enable(xspi, ENABLE);

    if (qspi_msg->parent.length > 16)
    {
        XSPI_SetTXStartFIFOThreshold(xspi, XSPI_FIFO_THRESHOLD_LEVEL15);
    }
    else if (qspi_msg->parent.length == 0)
    {
        XSPI_SetTXStartFIFOThreshold(xspi, XSPI_FIFO_THRESHOLD_LEVEL0);
    }
    else
    {
        XSPI_SetTXStartFIFOThreshold(xspi, (qspi_msg->parent.length - 1));
    }

    while (i < qspi_msg->parent.length + 4)                      /*Tx Fifo not full*/
    {
        while ((xspi->STS & XSPI_TXFNF_FLAG) != XSPI_TXFNF_FLAG); /*wait tx FIFO not full flag set*/

        if (i < 4)
        {
            xspi->DAT0 = s_data[i];       /*write data register*/
        }
        else
        {
            xspi->DAT0 = 0xFF;
        }

        if ((xspi->STS & XSPI_RXFNE_FLAG))   /*Rx Fifo not empty set*/
        {
            if (j < 4)
            {
                buf[0] = xspi->DAT0;
            }
            else if (j >= 4)
            {
                *(buf++) = xspi->DAT0; /*read data register*/
            }

            j++;
        }

        i++;
    }

    do
    {
        if ((xspi->STS & XSPI_RXFNE_FLAG))   /*Rx Fifo not empty set*/
        {
            *(buf++) = xspi->DAT0;     /*read data register*/
        }

    } while ((xspi->STS & XSPI_BUSY_FLAG) == SET);

    XSPI_Enable(xspi, DISABLE);

    return RT_EOK;
}

/* ---- rt_spi_ops ---- */

static rt_err_t xspi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    struct n32_xspi *xspi_drv = device->bus->parent.user_data;
    struct rt_qspi_device *qspi_dev = (struct rt_qspi_device *)device;

    xspi_drv->qspi_cfg = &qspi_dev->config;
    xspi_drv->cfg = configuration;

#if defined(SOC_SERIES_N32H7xx)
    /* set scpol/scph value */
    switch (xspi_drv->qspi_cfg->parent.mode & 0x03)
    {
    case RT_SPI_MODE_0:
    {
        xspi_drv->InitStructure.SCPH = XSPI_SCPH_FIRST_EDGE;
        xspi_drv->InitStructure.SCPOL = XSPI_SCPOL_LOW_LEVEL;
        break;
    }

    case RT_SPI_MODE_1:
    {
        xspi_drv->InitStructure.SCPH = XSPI_SCPH_SECOND_EDGE;
        xspi_drv->InitStructure.SCPOL = XSPI_SCPOL_LOW_LEVEL;
        break;
    }

    case RT_SPI_MODE_2:
    {
        xspi_drv->InitStructure.SCPH = XSPI_SCPH_FIRST_EDGE;
        xspi_drv->InitStructure.SCPOL = XSPI_SCPOL_HIGH_LEVEL;
        break;
    }

    case RT_SPI_MODE_3:
    {
        xspi_drv->InitStructure.SCPH = XSPI_SCPH_SECOND_EDGE;
        xspi_drv->InitStructure.SCPOL = XSPI_SCPOL_HIGH_LEVEL;
        break;
    }

    default:
    {
        xspi_drv->InitStructure.SCPH = XSPI_SCPH_FIRST_EDGE;
        xspi_drv->InitStructure.SCPOL = XSPI_SCPOL_LOW_LEVEL;
        break;
    }
    }

    /* dl_width = 1/2/4 */
    if (xspi_drv->qspi_cfg->qspi_dl_width == 1)
    {
        xspi_drv->InitStructure.FrameFormat = XSPI_STANDARD_MODE;
    }
    else if (xspi_drv->qspi_cfg->qspi_dl_width == 2)
    {
        xspi_drv->InitStructure.FrameFormat = XSPI_DUAL_LINE_MODE;
    }
    else if (xspi_drv->qspi_cfg->qspi_dl_width == 4)
    {
        xspi_drv->InitStructure.FrameFormat = XSPI_QUAD_LINE_MODE;
    }

    if (xspi_drv->qspi_cfg->parent.data_width == 8)
    {
        xspi_drv->InitStructure.DataFrameSize = XSPI_FRAME_SIZE_8_BIT;
    }
    else if (xspi_drv->qspi_cfg->parent.data_width == 16)
    {
        xspi_drv->InitStructure.DataFrameSize = XSPI_FRAME_SIZE_16_BIT;
    }
    else if (xspi_drv->qspi_cfg->parent.data_width == 24)
    {
        xspi_drv->InitStructure.DataFrameSize = XSPI_FRAME_SIZE_24_BIT;
    }
    else if (xspi_drv->qspi_cfg->parent.data_width == 32)
    {
        xspi_drv->InitStructure.DataFrameSize = XSPI_FRAME_SIZE_32_BIT;
    }


#endif

    return RT_EOK;
}

static rt_ssize_t xspixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL && device->bus != RT_NULL && message != RT_NULL);
    rt_err_t state = RT_EOK;
    struct n32_xspi *xspi_drv = device->bus->parent.user_data;
    struct rt_qspi_message *qmsg = (struct rt_qspi_message *)message;

    if (device->bus->mode & RT_SPI_BUS_MODE_QSPI)
    {
        if (qmsg->qspi_data_lines == 1)
        {
            if (message->send_buf && (qmsg->address.qspi_lines == 1))
            {
                state = xspi_spi_send(xspi_drv, qmsg, XSPI_TIMEOUT_TICKS);
            }
            else if (message->recv_buf && (qmsg->address.qspi_lines == 1))
            {
                state = xspi_spi_receive(xspi_drv, qmsg, XSPI_TIMEOUT_TICKS);
            }
            else if ((message->send_buf != NULL) || (message->recv_buf != NULL))
            {
                state = xspi_spi_transmit(xspi_drv, qmsg, XSPI_TIMEOUT_TICKS);
            }
        }
        else if (qmsg->qspi_data_lines == 4)
        {
            if (message->send_buf)
            {
                state = xspi_qspi_transmit(xspi_drv, qmsg, XSPI_TIMEOUT_TICKS);
            }
            else if (message->recv_buf)
            {
                state = xspi_qspi_receive(xspi_drv, qmsg, XSPI_TIMEOUT_TICKS);
            }
        }
    }
    else
    {
        state = xspi_spi_transmit(xspi_drv, qmsg, XSPI_TIMEOUT_TICKS);
    }

    if (state != RT_EOK)
    {
        LOG_E("xspi transfer error: %d", state);
        return -RT_ERROR;
    }

    return message->length;
}

static const struct rt_spi_ops n32_xspi_ops = {
    .configure = xspi_configure,
    .xfer = xspixfer,
};


/* XSPI XIP */
static rt_err_t xspi_control(rt_device_t dev, int cmd, void *args)
{
    struct rt_spi_device *spi_dev = (struct rt_spi_device *)dev;
    struct n32_xspi *xspi_drv = spi_dev->bus->parent.user_data;


    switch (cmd)
    {
    case XSPI_CTRL_ENTER_XIP:
    {
        static const struct xspi_xip_config _xip_default = {
            .XipInstructLen = XSPI_INST_LEN_8BIT,
            .XipInstrctEnable = XSPI_XIP_INSTRUCT_ENABLE,
            .XipDFSHC = XSPI_XIP_DFSHC_ENABLE,
            .XipPrefetch = XSPI_XIP_PREFETCH_DISABLE,
            .XipModeBit = XSPI_XIP_MODE_BIT_ENABLE,
            .XipModeBitLen = XSPI_XIP_MODE_BIT_LEN_8_BIT,
            .XipModeBit_Data = 0x00,
            .XipContinousTransfer = XSPI_XIP_INSTRUCT_DISABLE,
            .XipWatchDogTimeout = 100U,
            .XipIncrOpcode = 0x00,
            .XipWrapOpcode = 0x00,
        };

        const struct xspi_xip_config *cfg = args ? args : &_xip_default;

        XSPI_Module *xspi = xspi_drv->xSPIx;

        XSPI_Enable(xspi, DISABLE);
        XSPI_XIPInitType XSPI_XIPInit;

        XSPI_InitXIPStruct(&XSPI_XIPInit);

        XSPI_XIPInit.SCPH = xspi_drv->InitStructure.SCPH;
        XSPI_XIPInit.SCPOL = xspi_drv->InitStructure.SCPOL;
        XSPI_XIPInit.DataFrameSize = xspi_drv->InitStructure.DataFrameSize;
        XSPI_XIPInit.Baudr = xspi_drv->InitStructure.Baudr;
        XSPI_XIPInit.XipFrameFormat = xspi_drv->InitStructure.FrameFormat;

        XSPI_XIPInit.XipTransferType = xspi_drv->EnhInitStructure.TransferType;
        XSPI_XIPInit.XipAddrLen = xspi_drv->EnhInitStructure.AddrLen;
        XSPI_XIPInit.XipWaitCycles = xspi_drv->EnhInitStructure.WaitCycles;
        XSPI_XIPInit.XipDDREable = xspi_drv->EnhInitStructure.DDREable;

        XSPI_XIPInit.TransferMode = XSPI_RX_ONLY_MODE;

        XSPI_XIPInit.XIP_Info.Read_XIPInitType.XipInstructLen = cfg->XipInstructLen;
        XSPI_XIPInit.XIP_Info.Read_XIPInitType.XipInstrctEnable = cfg->XipInstrctEnable;
        XSPI_XIPInit.XIP_Info.Read_XIPInitType.XipDFSHC = cfg->XipDFSHC;
        XSPI_XIPInit.XIP_Info.Read_XIPInitType.XipPrefetch = cfg->XipPrefetch;
        XSPI_XIPInit.XIP_Info.Read_XIPInitType.XipModeBit = cfg->XipModeBit;
        XSPI_XIPInit.XIP_Info.Read_XIPInitType.XipModeBitLen = cfg->XipModeBitLen;

        XSPI_XIPInit.XIP_Info.Read_XIPInitType.ContinueTransfer.XipContinueTransfer = cfg->XipContinousTransfer;
        XSPI_XIPInit.XIP_Info.Read_XIPInitType.ContinueTransfer.XipWatchDogTimeout = cfg->XipWatchDogTimeout;

        XSPI_XIPInit.XIP_Info.Read_XIPInitType.Info.Rxds_InitType.RxdSamplingEdge = xspi_drv->InitStructure.RxdSamplingEdge;
        XSPI_XIPInit.XIP_Info.Read_XIPInitType.Info.Rxds_InitType.RxdSampleDelay = xspi_drv->InitStructure.RxdSampleDelay;

        xspi_drv->xip_enabled = 1;

        xspi_drv->Direct = XSPI_Idle;

        XSPI_InitXIP(xspi, &XSPI_XIPInit);

        XSPI_XIP_Slave_Select(xspi, xspi_drv->slave_sel);

        XSPI_SetXIPModeBit(xspi, cfg->XipModeBit_Data);

        XSPI_SetXIPReadIncrOpcode(xspi, cfg->XipIncrOpcode);
        XSPI_SetXIPReadWrapOpcode(xspi, cfg->XipWrapOpcode);

        XSPI_Enable(xspi, ENABLE);


        return RT_EOK;
    }


    case XSPI_CTRL_EXIT_XIP:
    {
        XSPI_Enable(xspi_drv->xSPIx, DISABLE);

        xspi_drv->xip_enabled = 0;
        xspi_drv->Direct = XSPI_Idle;
        LOG_D("%s XIP exit via ioctl", xspi_drv->bus_name);
        return RT_EOK;
    }

    case XSPI_CTRL_GET_XIP_ADDR:
    {
        if (args)
        {
            *(void **)args = (void *)XSPI_XIP_BASE_ADDR;
        }

        return RT_EOK;
    }


    default:

        return -RT_EINVAL;
    }
}

/* ---- bus register + device attach ---- */
static int n32_xspi_register_bus(struct n32_xspi *xspi_drv, const char *name)
{
    RT_ASSERT(xspi_drv != RT_NULL && name != RT_NULL);
    _xspi_bus.parent.user_data = xspi_drv;

    int ret = rt_qspi_bus_register(&_xspi_bus, name, &n32_xspi_ops);

    return ret;
}

rt_err_t rt_hw_xspi_device_attach(const char *bus_name, const char *device_name,
                                  rt_uint8_t data_line_width,
                                  void (*enter_qspi_mode)(struct rt_qspi_device *),
                                  void (*exit_qspi_mode)(struct rt_qspi_device *),
                                  struct n32_xspi_config *cfg)
{
    RT_ASSERT(bus_name != RT_NULL && device_name != RT_NULL);

    struct rt_qspi_device *qspi_device;
    rt_err_t result;

    if (cfg != RT_NULL)
    {
        _n32_xspi.InitStructure.Role = cfg->role;
        _n32_xspi.InitStructure.NssToggle = cfg->nss_toggle;

        _n32_xspi.InitStructure.DataFrameSize = cfg->data_frame_size;
        _n32_xspi.InitStructure.SCPH = cfg->scph;
        _n32_xspi.InitStructure.SCPOL = cfg->scpol;
        _n32_xspi.InitStructure.TransferMode = cfg->transfer_mode;
        _n32_xspi.InitStructure.Baudr = cfg->baudr;
        _n32_xspi.InitStructure.FrameFormat = cfg->frame_format;
        _n32_xspi.InitStructure.RxdSamplingEdge = cfg->rxd_sampling_edge;
        _n32_xspi.InitStructure.RxdSampleDelay = cfg->rxd_sample_delay;
        _n32_xspi.slave_sel = cfg->slave_sel;

        _n32_xspi.InitStructure.EnhSlave_ClockStrech = cfg->Enhance_clock_strech;

        if (data_line_width != 1)
        {
            _n32_xspi.EnhInitStructure.TransferType = cfg->Enhance_TransferType;
            _n32_xspi.EnhInitStructure.AddrLen = cfg->Enhance_AddrLen;
            _n32_xspi.EnhInitStructure.InstructLen = cfg->Enhance_InstructLen;
            _n32_xspi.EnhInitStructure.WaitCycles = cfg->Enhance_WaitCycles;
            _n32_xspi.EnhInitStructure.DDREable = cfg->Enhance_DDR;
        }
    }

    qspi_device = (struct rt_qspi_device *)rt_malloc(sizeof(struct rt_qspi_device));
    if (qspi_device == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    qspi_device->enter_qspi_mode = enter_qspi_mode;
    qspi_device->exit_qspi_mode = exit_qspi_mode;

    qspi_device->config.qspi_dl_width = data_line_width;

    result = rt_spi_bus_attach_device(&qspi_device->parent, device_name,
                                      bus_name, RT_NULL);

    if (result != RT_EOK)
    {
        rt_free(qspi_device);
        return result;
    }

    qspi_device->parent.parent.control = xspi_control;

    return result;
}


/* ---- board-level init ---- */

static int rt_hw_xspi_bus_init(void)
{
#if defined(SOC_SERIES_N32H7xx)
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_PWR, ENABLE);

    RCC_EnableAXIPeriphReset4(RCC_AXI_PERIPHRST_XSPI2);
    RCC_EnableAXIPeriphClk4(RCC_AXI_PERIPHEN_M7_XSPI2, ENABLE);

#endif

    _n32_xspi.xSPIx = xSPI2;
    _n32_xspi.bus_name = "qspi2";


    rt_completion_init(&_n32_xspi.cpt);
    return n32_xspi_register_bus(&_n32_xspi, "qspi2");
}

INIT_BOARD_EXPORT(rt_hw_xspi_bus_init);

#endif
