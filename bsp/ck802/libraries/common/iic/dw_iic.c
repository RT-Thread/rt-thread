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
 * @file     dw_iic.c
 * @brief    CSI Source File for IIC Driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#include "csi_core.h"
#include "drv_iic.h"
#include "dw_iic.h"
#include "soc.h"
#include "string.h"

#define ERR_IIC(errno) (CSI_DRV_ERRNO_I2C_BASE | errno)

#define IIC_NULL_PARAM_CHK(para)                  \
    do {                                        \
        if (para == NULL) {                     \
            return ERR_IIC(EDRV_PARAMETER);   \
        }                                       \
    } while (0)

typedef struct  {
    uint32_t base;
    uint32_t irq;
    iic_event_cb_t cb_event;
    void *cb_arg;
    uint32_t rx_total_num;
    uint32_t tx_total_num;
    void *rx_buf;
    void *tx_buf;
    volatile uint32_t rx_cnt;
    volatile uint32_t tx_cnt;
    uint32_t status;             ///< status of iic transfer
} dw_iic_priv_t;

static dw_iic_priv_t iic_instance[CONFIG_IIC_NUM];

static const iic_capabilities_t iic_capabilities = {
    .address_10_bit = 0  /* supports 10-bit addressing */
};

static inline void dw_iic_disable(dw_iic_reg_t *addr)
{
    /* First clear ACTIVITY, then Disable IIC */
    addr->IC_CLR_ACTIVITY;
    addr->IC_ENABLE = DW_IIC_DISABLE;

}

static inline void dw_iic_enable(dw_iic_reg_t *addr)
{
    addr->IC_ENABLE = DW_IIC_ENABLE;

}

static inline void dw_iic_set_transfer_speed(dw_iic_reg_t *addr, DWENUM_IIC_SPEED speed)
{
    uint16_t temp = addr->IC_CON;
    temp &= ~((1 << 1) + (1 << 2));
    temp |= speed << 1;
    addr->IC_CON = temp;
}

static inline void dw_iic_set_target_address(dw_iic_reg_t *addr, uint16_t address)
{
    uint16_t temp = addr->IC_TAR;
    temp &= 0xfc00;
    temp |= address;
    addr->IC_TAR = temp;
}
static inline void dw_iic_set_addr_mode(dw_iic_reg_t *addr, iic_address_mode_e addr_mode)
{
    uint16_t temp = addr->IC_TAR;
    temp &= 0xefff;
    temp |= addr_mode << 12;
    addr->IC_TAR = temp;
}

static void dw_i2c_int_clear(dw_iic_reg_t *addr, DWENUM_IIC_INTERRUPT_TYPE type)
{
    uint32_t  temp = 0;

    switch (type) {
        case DW_IIC_RX_UNDER:
            temp = addr->IC_CLR_RX_UNDER;
            break;

        case DW_IIC_RX_OVER:
            temp = addr->IC_CLR_RX_OVER;
            break;

        case DW_IIC_TX_OVER:
            temp = addr->IC_CLR_TX_OVER;
            break;

        case DW_IIC_RD_REQ:
            temp = addr->IC_CLR_RD_REQ;
            break;

        case DW_IIC_TX_ABRT:
            temp = addr->IC_CLR_TX_ABRT;
            break;

        case DW_IIC_RX_DONE:
            temp = addr->IC_CLR_RX_DONE;
            break;

        case DW_IIC_ACTIVITY:
            temp = addr->IC_CLR_ACTIVITY;
            break;

        case DW_IIC_STOP_DET:
            temp = addr->IC_CLR_STOP_DET;
            break;

        case DW_IIC_START_DET:
            temp = addr->IC_CLR_START_DET;
            break;

        case DW_IIC_GEN_CALL:
            temp = addr->IC_CLR_GEN_CALL;
            break;

        default:
            temp = addr->IC_CLR_INTR;
    }
}

/**
  \brief       interrupt service function for transmit FIFO empty interrupt.
  \param[in]   iic_priv pointer to iic private.
*/
static void dw_iic_intr_tx_empty(dw_iic_priv_t *iic_priv)
{
    dw_iic_reg_t *addr = (dw_iic_reg_t *)(iic_priv->base);

    if (addr->IC_INTR_STAT & (1 << DW_IIC_TX_EMPTY)) {

        uint32_t remain_txfifo = iic_priv->tx_total_num - iic_priv->tx_cnt;
        uint8_t emptyfifo = (remain_txfifo > (DW_IIC_FIFO_MAX_LV - addr->IC_TXFLR)) ? DW_IIC_FIFO_MAX_LV - addr->IC_TXFLR : remain_txfifo;
        uint32_t i = 0u;

        for (i = 0; i < emptyfifo; i++) {
            addr->IC_DATA_CMD = *((uint8_t *)(iic_priv->tx_buf)++);
        }

        iic_priv->tx_cnt += emptyfifo;

        if (iic_priv->tx_cnt == iic_priv->tx_total_num) {
            addr->IC_INTR_MASK &= ~(1 << DW_IIC_TX_EMPTY);
        }
    }

    if (addr->IC_INTR_STAT & (1 << DW_IIC_TX_OVER)) {
        dw_i2c_int_clear(addr, DW_IIC_TX_OVER);
        iic_priv->status = IIC_STATE_ERROR;
        dw_iic_disable(addr);

        if (iic_priv->cb_event) {
            iic_priv->cb_event(I2C_EVENT_BUS_ERROR, iic_priv->cb_arg);
        }
    }

    if (addr->IC_INTR_STAT & (1 << DW_IIC_TX_ABRT)) {
        dw_i2c_int_clear(addr, DW_IIC_TX_ABRT);
        iic_priv->status = IIC_STATE_ERROR;
        dw_iic_disable(addr);

        if (iic_priv->cb_event) {
            iic_priv->cb_event(I2C_EVENT_BUS_ERROR, iic_priv->cb_arg);
        }

    }

    if (addr->IC_INTR_STAT & (1 << DW_IIC_STOP_DET)) {
        iic_priv->status  = IIC_STATE_DONE;
        dw_i2c_int_clear(addr, DW_IIC_STOP_DET);

        if (iic_priv->cb_event) {
            dw_iic_disable(addr);
            addr->IC_CLR_INTR;
            iic_priv->cb_event(I2C_EVENT_TRANSFER_DONE, iic_priv->cb_arg);
        }
    }

}
/**
  \brief       interrupt service function for receive FIFO full interrupt .
  \param[in]   iic_priv pointer to iic private.
*/
static void dw_iic_intr_rx_full(dw_iic_priv_t *iic_priv)
{
    dw_iic_reg_t *addr = (dw_iic_reg_t *)(iic_priv->base);

    if (addr->IC_INTR_STAT & (1 << DW_IIC_RX_FULL)) {
        uint8_t emptyfifo = addr->IC_RXFLR;
        uint32_t i = 0u;

        for (i = 0; i < emptyfifo ; i++) {
            *((uint8_t *)(iic_priv->rx_buf++)) = ((addr->IC_DATA_CMD) & 0xff);
        }

        iic_priv->rx_cnt += emptyfifo;

        if (iic_priv->rx_cnt != iic_priv->rx_total_num) {
            addr->IC_DATA_CMD = 1 << 8;
        }
    }

    if (addr->IC_INTR_STAT & (1 << DW_IIC_RX_OVER)) {
        dw_i2c_int_clear(addr, DW_IIC_RX_OVER);
        iic_priv->status = IIC_STATE_ERROR;
        dw_iic_disable(addr);

        if (iic_priv->cb_event) {
            iic_priv->cb_event(I2C_EVENT_BUS_ERROR, iic_priv->cb_arg);
        }
    }

    if (addr->IC_INTR_STAT & (1 << DW_IIC_RX_FULL)) {
        dw_i2c_int_clear(addr, DW_IIC_RX_FULL);
        iic_priv->status = IIC_STATE_ERROR;
        dw_iic_disable(addr);

        if (iic_priv->cb_event) {
            iic_priv->cb_event(I2C_EVENT_BUS_ERROR, iic_priv->cb_arg);
        }

    }

    if (addr->IC_INTR_STAT & (1 << DW_IIC_STOP_DET)) {
        dw_i2c_int_clear(addr, DW_IIC_STOP_DET);

        if (iic_priv->rx_cnt == iic_priv->rx_total_num) {
            iic_priv->status  = IIC_STATE_DONE;
            dw_iic_disable(addr);
            addr->IC_CLR_INTR;

            if (iic_priv->cb_event) {
                iic_priv->cb_event(I2C_EVENT_TRANSFER_DONE, iic_priv->cb_arg);
            }
        }
    }

}
void dw_iic_irqhandler(int32_t idx)
{
    dw_iic_priv_t *iic_priv = &iic_instance[idx];
    dw_iic_reg_t *addr = (dw_iic_reg_t *)(iic_priv->base);

    if (addr->IC_INTR_STAT & (1 << DW_IIC_TX_ABRT)) {
        /* If arbitration fault, it indicates either a slave device not
        * responding as expected, or other master which is not supported
        * by this SW.
        */
        dw_i2c_int_clear(addr, DW_IIC_TX_ABRT);
        iic_priv->status    = IIC_STATE_DONE;

        if (iic_priv->cb_event) {
            dw_iic_disable(addr);
            iic_priv->cb_event(I2C_EVENT_BUS_ERROR, iic_priv->cb_arg);
            return;
        }
    }

    switch (iic_priv->status) {
            /* send data to slave */
        case IIC_STATE_DATASEND: {
            dw_iic_intr_tx_empty(iic_priv);
            break;
        }

        /* wait for data from slave */
        case IIC_STATE_WFDATA: {
            dw_iic_intr_rx_full(iic_priv);
            break;
        }

        /* unexpected state,SW fault */
        default: {
            dw_iic_disable(addr);

            if (iic_priv->cb_event) {
                iic_priv->cb_event(I2C_EVENT_BUS_ERROR, iic_priv->cb_arg);
            }
        }
    }
}

int32_t __attribute__((weak)) target_iic_init(pin_t scl, pin_t sda, uint32_t *base, uint32_t *irq)
{
    return -1;
}

/**
  \brief       Initialize IIC Interface. 1. Initializes the resources needed for the IIC interface 2.registers event callback function
  \param[in]   handle  iic handle to operate.
  \param[in]   cb_event  Pointer to \ref iic_event_cb_t
  \return      error code
*/
iic_handle_t csi_iic_initialize(pin_t scl, pin_t sda, iic_event_cb_t cb_event, void *cb_arg)
{
    uint32_t base = 0u;
    uint32_t irq = 0u;

    int32_t idx = target_iic_init(scl, sda, &base, &irq);

    if (idx < 0 || idx >= CONFIG_IIC_NUM) {
        return NULL;
    }

    dw_iic_priv_t *iic_priv = &iic_instance[idx];
    iic_priv->base = base;
    iic_priv->irq  = irq;


    iic_priv->cb_event = cb_event;
    iic_priv->cb_arg = cb_arg;
    iic_priv->rx_total_num = 0;
    iic_priv->tx_total_num = 0;
    iic_priv->rx_buf = NULL;
    iic_priv->tx_buf = NULL;
    iic_priv->rx_cnt = 0;
    iic_priv->tx_cnt = 0;
    iic_priv->status = 0;

    dw_iic_reg_t *addr = (dw_iic_reg_t *)(iic_priv->base);

    /* mask all interrupts */
    addr->IC_INTR_MASK  = 0x00;
    addr->IC_CON        = DW_IIC_CON_DEFAUL;
    addr->IC_INTR_MASK |= 1 << DW_IIC_TX_ABRT;
    addr->IC_INTR_MASK |= 1 << DW_IIC_TX_OVER;
    addr->IC_INTR_MASK |= 1 << DW_IIC_RX_OVER;
    addr->IC_INTR_MASK |= 1 << DW_IIC_RX_FULL;
    addr->IC_INTR_MASK |= 1 << DW_IIC_STOP_DET;

    drv_nvic_enable_irq(iic_priv->irq);

    return iic_priv;
}

/**
  \brief       De-initialize IIC Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  iic handle to operate.
  \return      error code
*/
int32_t csi_iic_uninitialize(iic_handle_t handle)
{
    IIC_NULL_PARAM_CHK(handle);

    /* First clear ACTIVITY, then Disable IIC */
    dw_iic_priv_t *iic_priv = handle;
    dw_iic_reg_t *addr = (dw_iic_reg_t *)(iic_priv->base);

    addr->IC_CLR_ACTIVITY;
    addr->IC_INTR_MASK  = 0x00;
    addr->IC_ENABLE = DW_IIC_DISABLE;

    iic_priv->cb_event = NULL;
    iic_priv->rx_total_num = 0;
    iic_priv->tx_total_num = 0;
    iic_priv->rx_buf = NULL;
    iic_priv->tx_buf = NULL;
    iic_priv->rx_cnt = 0;
    iic_priv->tx_cnt = 0;
    iic_priv->status = 0;

    drv_nvic_disable_irq(iic_priv->irq);

    return 0;
}

/**
  \brief       Get driver capabilities.
  \return      \ref iic_capabilities_t
*/
iic_capabilities_t csi_iic_get_capabilities(iic_handle_t handle)
{
    return iic_capabilities;
}

/**
  \brief       config iic.
  \param[in]   handle  iic handle to operate.
  \param[in]   mode      \ref iic_mode_e.if negative, then this attribute not changed
  \param[in]   speed     \ref iic_speed_e.if negative, then this attribute not changed
  \param[in]   addr_mode \ref iic_address_mode_e.if negative, then this attribute not changed
  \param[in]   slave_addr slave address.if negative, then this attribute not changed
  \return      error code
*/
int32_t csi_iic_config(iic_handle_t handle,
                       iic_mode_e mode,
                       iic_speed_e speed,
                       iic_address_mode_e addr_mode,
                       int32_t slave_addr)
{
    IIC_NULL_PARAM_CHK(handle);

    if (mode >= 0) {
        switch (mode) {
            case IIC_MODE_MASTER:
                break;

            case IIC_MODE_SLAVE:
                return ERR_IIC(EDRV_UNSUPPORTED);
                break;

            default:
                return ERR_IIC(EDRV_PARAMETER);
        }
    }

    dw_iic_reg_t *addr = (dw_iic_reg_t *)(((dw_iic_priv_t *)handle)->base);

    if (speed >= 0) {
        switch (speed) {
            case I2C_BUS_SPEED_STANDARD:
                dw_iic_set_transfer_speed(addr, DW_IIC_STANDARDSPEED);
                break;

            case I2C_BUS_SPEED_FAST:
                dw_iic_set_transfer_speed(addr, DW_IIC_FASTSPEED);
                break;

            case I2C_BUS_SPEED_FAST_PLUS:
                return ERR_IIC(EDRV_UNSUPPORTED);

            case I2C_BUS_SPEED_HIGH:
                dw_iic_set_transfer_speed(addr, DW_IIC_HIGHSPEED);
                break;

            default:
                return ERR_IIC(EDRV_PARAMETER);
        }
    }

    if (addr_mode >= 0) {
        switch (addr_mode) {
            case I2C_ADDRESS_10BIT:
            case I2C_ADDRESS_7BIT:
                dw_iic_set_addr_mode(addr, addr_mode);
                break;

            default:
                return ERR_IIC(EDRV_PARAMETER);
        }
    }

    if (slave_addr >= 0) {
        dw_iic_set_target_address(addr, slave_addr);
    }

    return 0;
}

/**
  \brief       Start transmitting data as I2C Master.
  \param[in]   handle       iic handle to operate.
  \param[in]   data           Pointer to buffer with data to transmit to I2C Slave
  \param[in]   num            Number of data items to send
  \param[in]   xfer_pending   Transfer operation is pending - Stop condition will not be generated
  \return      error code
*/
int32_t csi_iic_master_send(iic_handle_t handle, const void *data, uint32_t num, bool xfer_pending)
{
    IIC_NULL_PARAM_CHK(handle);

    if (data == NULL || num == 0) {
        return ERR_IIC(EDRV_PARAMETER);
    }

    dw_iic_priv_t *iic_priv = handle;
    dw_iic_reg_t *addr = (dw_iic_reg_t *)(iic_priv->base);

    iic_priv->tx_buf          = (uint8_t *)data;
    iic_priv->tx_total_num    = num;
    iic_priv->tx_cnt          = 0;
    iic_priv->status          = IIC_STATE_DATASEND;

    dw_iic_disable(addr);
    addr->IC_CLR_INTR;

    uint32_t length = (num > DW_IIC_FIFO_MAX_LV) ?  DW_IIC_FIFO_MAX_LV : num;
    addr->IC_TX_TL = DW_IIC_TXFIFO_LV;

    dw_iic_enable(addr);
    uint32_t i = 0u;

    for (i = 0; i < length; i++) {
        addr->IC_DATA_CMD = *((uint8_t *)(iic_priv->tx_buf)++);
    }

    iic_priv->tx_cnt += length;

    /* open corresponding interrupts */
    addr->IC_INTR_MASK |= 1 << DW_IIC_TX_EMPTY;

    return 0;

}

/**
  \fn          int32_t csi_iic_master_receive (iic_handle_t handle,const void *data, uint32_t num, bool xfer_pending)
  \brief       Start receiving data as I2C Master.
  \param[in]   handle  iic handle to operate.
  \param[out]  data  Pointer to buffer for data to receive from IIC receiver
  \param[in]   num   Number of data items to receive
  \param[in]   xfer_pending   Transfer operation is pending - Stop condition will not be generated
  \return      error code
*/
int32_t csi_iic_master_receive(iic_handle_t handle, const void *data, uint32_t num, bool xfer_pending)
{
    IIC_NULL_PARAM_CHK(handle);

    if (data == NULL || num == 0) {
        return ERR_IIC(EDRV_PARAMETER);
    }

    dw_iic_priv_t *iic_priv = handle;

    iic_priv->rx_buf          = (uint8_t *)data;
    iic_priv->rx_total_num      = num;
    iic_priv->rx_cnt          = 0;
    iic_priv->status          = IIC_STATE_WFDATA;

    dw_iic_reg_t *addr = (dw_iic_reg_t *)(iic_priv->base);
    dw_iic_disable(addr);

    int32_t  tmp = addr->IC_CLR_INTR;
    addr->IC_RX_TL = DW_IIC_FIFO_MAX_LV; /* Sets receive FIFO threshold */

    tmp = addr->IC_CLR_INTR;
    addr->IC_RX_TL        = DW_IIC_RXFIFO_LV;    /* Sets receive FIFO threshold */
    dw_iic_enable(addr);
    addr->IC_DATA_CMD = 1 << 8;

    return 0;

}

/**
  \brief       Start transmitting data as I2C Slave.
  \param[in]   handle  iic handle to operate.
  \param[in]   data  Pointer to buffer with data to transmit to I2C Master
  \param[in]   num   Number of data items to send
  \return      error code
*/
int32_t csi_iic_slave_send(iic_handle_t handle, const void *data, uint32_t num)
{
    return ERR_IIC(EDRV_UNSUPPORTED);
}

/**
  \fn          int32_t  csi_iic_slave_receive (iic_handle_t handle, const void *data, uint32_t num)
  \brief       Start receiving data as I2C Slave.
  \param[in]   handle  iic handle to operate.
  \param[out]  data  Pointer to buffer for data to receive from I2C Master
  \param[in]   num   Number of data items to receive
  \return      error code
*/
int32_t csi_iic_slave_receive(iic_handle_t handle, const void *data, uint32_t num)
{
    return ERR_IIC(EDRV_UNSUPPORTED);
}

/**
  \brief       abort transfer.
  \param[in]   handle  iic handle to operate.
  \return      error code
*/
int32_t csi_iic_abort_transfer(iic_handle_t handle)
{
    IIC_NULL_PARAM_CHK(handle);

    dw_iic_priv_t *iic_priv = handle;
    dw_iic_reg_t *addr = (dw_iic_reg_t *)(iic_priv->base);

    dw_iic_disable(addr);
    iic_priv->rx_cnt          = 0;
    iic_priv->tx_cnt          = 0;
    iic_priv->rx_buf          = NULL;
    iic_priv->tx_buf          = NULL;
    return 0;
}


/**
  \brief       Get IIC status.
  \param[in]   handle  iic handle to operate.
  \return      IIC status \ref iic_status_t
*/
iic_status_t csi_iic_get_status(iic_handle_t handle)
{
    iic_status_t iic_status = {0};

    if (handle == NULL) {
        return iic_status;
    }

    dw_iic_priv_t *iic_priv = handle;
    dw_iic_reg_t *addr = (dw_iic_reg_t *)(iic_priv->base);

    int32_t tmp = addr->IC_STATUS;

    if (tmp & 0x1) {
        iic_status.busy = 1;

        if (tmp & 0x40) {
            iic_status.mode = 0;
        } else {
            iic_status.mode = 1;
        }
    }

    if (iic_priv->status == IIC_STATE_WFDATA) {
        iic_status.direction = 1;
    }

    if (addr->IC_RAW_INTR_STAT & 0x800) {
        iic_status.general_call = 1;
    }

    if (iic_priv->status == IIC_STATE_ERROR) {
        iic_status.bus_error = 1;
    }

    return iic_status;
}

