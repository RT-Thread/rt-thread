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
* @file     ck_dmac.c
* @brief    CSI Source File for DMAC Driver
* @version  V1.0
* @date     02. June 2017
******************************************************************************/
#include <stdbool.h>
#include "ck_dmac.h"
#include "csi_core.h"
#include "drv_dmac.h"
#include "soc.h"

#define ERR_DMA(errno) (CSI_DRV_ERRNO_DMA_BASE | errno)

typedef struct {
    uint32_t base;
    uint32_t irq;
    dma_event_cb_t cb_event;
    uint8_t ch_num;
} ck_dma_priv_t;

static ck_dma_priv_t dma_instance[CONFIG_DMAC_NUM];

static const dma_capabilities_t dma_capabilities = {
    .unalign_addr = 1,          ///< support for unalign address transfer when memory is source
};

static volatile dma_status_e status[CK_DMA_MAXCHANNEL] = {DMA_STATE_FREE, DMA_STATE_FREE};
static volatile uint8_t ch_opened[CK_DMA_MAXCHANNEL] = {0, 0};

static int32_t ck_dma_set_channel(ck_dma_reg_t *addr, uint32_t source, uint32_t dest, uint32_t size)
{
    uint32_t temp = addr->CHCTRLA;
    temp &= 0xff000fff;
    temp |= (size << 12);
    addr->SAR = source;
    addr->DAR = dest ;
    addr->CHCTRLA = temp;

    return 0;
}

static int32_t ck_dma_set_transfertype(ck_dma_reg_t *addr, dma_trans_type_e transtype)
{
    uint32_t temp = addr->CHCTRLB;
    temp &= 0xffffff7f;

    if (transtype >= DMA_PERH2PERH) {
        return ERR_DMA(EDRV_PARAMETER);
    }

    if (transtype == DMA_MEM2MEM) {
        temp |= (transtype << 7);
    } else {
        temp |= (1 << 7);
    }

    addr->CHCTRLB = temp;

    return 0;
}

static int32_t ck_dma_set_addrinc(ck_dma_reg_t *addr, enum_addr_state_e src_addrinc, enum_addr_state_e dst_addrinc)
{
    if ((src_addrinc != DMA_ADDR_INCREMENT && src_addrinc != DMA_ADDR_DECREMENT && src_addrinc != DMA_ADDR_NOCHANGE) ||
        (dst_addrinc != DMA_ADDR_INCREMENT && dst_addrinc != DMA_ADDR_DECREMENT && dst_addrinc != DMA_ADDR_NOCHANGE)) {
        return ERR_DMA(EDRV_PARAMETER);
    }

    uint32_t  temp = addr->CHCTRLA;
    temp &= 0xffffff0f;
    temp |= (src_addrinc << 6);
    temp |= (dst_addrinc << 4);
    addr->CHCTRLA = temp;

    return 0;
}

static int32_t ck_dma_set_transferwidth(ck_dma_reg_t *addr, dma_datawidth_e src_width, dma_datawidth_e dst_width)
{
    if ((src_width != DMA_DATAWIDTH_SIZE8 && src_width != DMA_DATAWIDTH_SIZE16 && src_width != DMA_DATAWIDTH_SIZE32) ||
        (dst_width != DMA_DATAWIDTH_SIZE8 && dst_width != DMA_DATAWIDTH_SIZE16 && dst_width != DMA_DATAWIDTH_SIZE32)) {
        return ERR_DMA(EDRV_PARAMETER);
    }

    uint32_t temp = addr->CHCTRLA;
    temp &= 0xfffffff0;
    temp |= (src_width - 1) << 2;
    temp |= dst_width - 1;
    addr->CHCTRLA = temp;

    return 0;
}

static int32_t ck_dma_set_burstlength(ck_dma_reg_t *addr, uint8_t burstlength)
{
    uint32_t temp = addr->CHCTRLA;
    temp &= 0xfffff0ff;
    temp |= (burstlength << 8);
    addr->CHCTRLA = temp;

    return 0;

}

/**
  \brief       Set software or hardware handshaking.
  \param[in]   addr pointer to dma register.
  \return      error code
*/
static int32_t ck_dma_set_handshaking(ck_dma_reg_t *addr, dma_handshaking_select_e handshaking)
{
    uint32_t  temp = addr->CHCTRLB;
    temp &= 0xfffffeff;
    temp |= (handshaking << 8);
    addr->CHCTRLB = temp;

    return 0;
}

static int ck_dma_assign_hdhs_interface(ck_dma_reg_t *addr, ckenum_dma_device_e device)
{
    if (device < 0 || device >= CKENUM_DMA_MEMORY) {
        return ERR_DMA(EDRV_PARAMETER);
    }

    addr->CHCTRLB &= 0xffffe1ff;
    addr->CHCTRLB |= (device << 9);

    return 0;
}


void ck_dma_irqhandler(int32_t idx)
{
    ck_dma_priv_t *dma_priv = &dma_instance[idx];
    ck_dma_reg_t *addr = (ck_dma_reg_t *)(dma_priv->base);

    /*
     * StatusInt_temp contain the information that which types of interrupr are
     * requested.
     */
    int32_t count = 0;
    uint32_t temp = 0;

    for (count = 0; count < dma_priv->ch_num; count++) {
        addr = (ck_dma_reg_t *)(dma_priv->base + count * 0x30);

        temp = addr->CHINTS;

        if (temp != 0) {
            break;
        }
    }

    /* If Tfr interrupt is requested */
    if (temp == CK_DMA_TFR) {
        status[count] = DMA_STATE_DONE;
        addr->CHINTC = temp;

        if (dma_priv->cb_event) {
            dma_priv->cb_event(DMA_EVENT_TRANSFER_DONE, count);
        }
    }

    /* If Err interrput is requested */
    if (temp == CK_DMA_ERR) {
        status[count] =  DMA_STATE_ERROR;
        addr->CHINTC = temp;

        if (dma_priv->cb_event) {
            dma_priv->cb_event(DMA_EVENT_TRANSFER_ERROR, count);
        }
    }
}

int32_t __attribute__((weak)) target_get_dmac_count(void)
{
    return 0;
}

int32_t __attribute__((weak)) target_get_dmac(uint32_t idx, uint32_t *base, uint32_t *irq)
{
    return NULL;
}

/**
  \brief       get dma instance count.
  \return      dma instance count
*/
int32_t csi_dma_get_instance_count(void)
{
    return target_get_dmac_count();
}

/**
  \brief       Initialize DMA Interface. 1. Initializes the resources needed for the DMA interface 2.registers event callback function
  \param[in]   idx must not exceed return value of csi_dma_get_instance_count()
  \return      pointer to dma instances
*/
dmac_handle_t csi_dma_initialize(int32_t idx)
{

    if (idx < 0 || idx >= CONFIG_DMAC_NUM) {
        return NULL;
    }

    uint32_t base = 0u;
    uint32_t irq = 0u;

    int32_t real_idx = target_get_dmac(idx, &base, &irq);

    if (real_idx != idx) {
        return NULL;
    }

    ck_dma_priv_t *dma_priv = &dma_instance[idx];

    dma_priv->base = base;
    dma_priv->irq  = irq;
    dma_priv->ch_num = CK_DMA_MAXCHANNEL;
    drv_nvic_enable_irq(dma_priv->irq);
    uint8_t count = 0u;

    for (count = 0; count < dma_priv->ch_num; count++) {
        ck_dma_reg_t *addr = (ck_dma_reg_t *)(dma_priv->base + count * 0x30);
        addr->CHINTM = CK_DMA_MASK;
        addr->CHINTC = CK_DMA_INTC;
    }

    return (dmac_handle_t)dma_priv;
}

/**
  \brief       De-initialize DMA Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle damc handle to operate.
  \return      error code
*/
int32_t csi_dma_uninitialize(dmac_handle_t handle)
{
    if (handle == NULL) {
        return ERR_DMA(EDRV_PARAMETER);
    }

    ck_dma_priv_t *dma_priv = handle;
    ck_dma_reg_t *addr = (ck_dma_reg_t *)(dma_priv->base);

    uint8_t count;

    for (count = 0; count < dma_priv->ch_num; count++) {
        addr = (ck_dma_reg_t *)(dma_priv->base + count * 0x30);
        addr->CHINTM = CK_DMA_MASK;
        addr->CHINTC = CK_DMA_INTC;
    }

    drv_nvic_disable_irq(dma_priv->irq);

    return 0;
}

/**
  \brief       Get driver capabilities.
  \param[in]   handle damc handle to operate.
  \return      \ref dma_capabilities_t
*/
dma_capabilities_t csi_dma_get_capabilities(dmac_handle_t handle)
{
    return dma_capabilities;
}

/**
  \brief     get one free dma channel
  \param[in] handle damc handle to operate.
  \param[in] ch channel num. if -1 then allocate a free channal in this dma
  \return    -1 - no channel can be used, other - channel index
 */
int32_t csi_dma_alloc_channel(dmac_handle_t handle, int32_t ch)
{
    ck_dma_priv_t *dma_priv = handle;

    if (handle == NULL || ch > dma_priv->ch_num) {
        return ERR_DMA(EDRV_PARAMETER);
    }

    uint8_t ch_num = 0;
    ck_dma_reg_t *addr = NULL;

    if (ch == -1) {     // alloc a free channal
        for (ch_num = 0; ch_num < dma_priv->ch_num; ch_num++) {
            addr = (ck_dma_reg_t *)(dma_priv->base + ch_num * 0x30);

            if (ch_opened[ch_num] != 0x1) {
                ch_opened[ch_num] = 1;
                break;
            }
        }

        if (ch_num >= dma_priv->ch_num) {
            return -1;
        }
    } else {    //alloc a fixed channel
        addr = (ck_dma_reg_t *)(dma_priv->base + ch * 0x30);

        if (ch_opened[ch] == 0x1) {
            return ERR_DMA(EDRV_BUSY);
        }

        ch_opened[ch] = 1;
        ch_num = ch;
    }

    addr->CHINTC = CK_DMA_INTC;
    addr->CHINTM &= ~CK_DMA_MASK;
    status[ch_num] = DMA_STATE_READY;

    return ch_num;
}

/**
  \brief        release dma channel and related resources
  \param[in]    handle damc handle to operate.
  \param[in]    ch  channel num.
  \return       error code
 */
int32_t csi_dma_release_channel(dmac_handle_t handle, int32_t ch)
{
    ck_dma_priv_t *dma_priv = handle;

    if (handle == NULL || ch >= dma_priv->ch_num || ch < 0) {
        return ERR_DMA(EDRV_PARAMETER);
    }

    ck_dma_reg_t *addr = (ck_dma_reg_t *)(dma_priv->base + ch * 0x30);
    status[ch] = DMA_STATE_FREE;
    ch_opened[ch] = 0;

    addr->CHINTC = CK_DMA_INTC;
    addr->CHINTM = CK_DMA_MASK;
    return 0;
}

/**
  \brief
  \param[in]    handle damc handle to operate.
  \param[in]    ch          channel num. if -1 then allocate a free channal in this dma
  \param[in]    psrcaddr    dma transfer source address
  \param[in]    pstdaddr    dma transfer source address
  \param[in]    length      dma transfer length
  \param[in]    config      dma transfer configure
  \param[in]    cb_event    Pointer to \ref dma_event_cb_t
  \return       error code
 */
int32_t csi_dma_config(dmac_handle_t handle, int32_t ch,
                       void *psrcaddr, void *pstdaddr,
                       uint32_t length, dma_config_t *config, dma_event_cb_t cb_event)
{
    ck_dma_priv_t *dma_priv = handle;

    if (handle == NULL || ch >= dma_priv->ch_num || config == NULL) {
        return ERR_DMA(EDRV_PARAMETER);
    }

    if (ch == -1) { //alloc a free channel
        ch = csi_dma_alloc_channel(handle, -1);

        if (ch < 0) {
            return ERR_DMA(EDRV_BUSY);
        }
    }

    dma_priv->cb_event = cb_event;

    ck_dma_reg_t *addr = (ck_dma_reg_t *)(dma_priv->base + ch * 0x30);

    /* Initializes corresponding channel registers */

    if ((length * config->src_tw) % config->dst_tw != 0) {
        return ERR_DMA(EDRV_PARAMETER);
    }

    int32_t ret = ck_dma_set_transferwidth(addr, config->src_tw, config->dst_tw);

    if (ret) {
        return ret;
    }

    int32_t grouplen = ((length * config->src_tw / config->dst_tw) - 1) % 16;
    ck_dma_set_burstlength(addr, grouplen);

    ret = ck_dma_set_transfertype(addr, config->type);

    if (ret < 0) {
        return ret;
    }

    if (config->type == DMA_MEM2MEM) {
        ck_dma_set_handshaking(addr, DMA_HANDSHAKING_SOFTWARE);
        ret = ck_dma_set_addrinc(addr , config->src_inc, config->dst_inc);
    } else if (config->type == DMA_MEM2PERH) {
        ck_dma_set_handshaking(addr, DMA_HANDSHAKING_HARDWARE);
        ret = ck_dma_set_addrinc(addr , config->src_inc, config->dst_inc);

        if (ret) {
            return ret;
        }

        ret = ck_dma_assign_hdhs_interface(addr, config->hs_if);

        if (ret) {
            return ret;
        }

    } else if (config->type == DMA_PERH2MEM) {
        ck_dma_set_handshaking(addr, DMA_HANDSHAKING_HARDWARE);
        ret = ck_dma_set_addrinc(addr , config->src_inc, config->dst_inc);

        if (ret) {
            return ret;
        }

        ret = ck_dma_assign_hdhs_interface(addr, config->hs_if);

        if (ret) {
            return ret;
        }
    }

    ck_dma_set_channel(addr, (uint32_t)psrcaddr, (uint32_t)pstdaddr, length);
    status[ch] = DMA_STATE_READY;

    return 0;
}

/**
  \brief       start generate dma signal.
  \param[in]   handle damc handle to operate.
  \param[in]   ch  channel num.
  \return      error code
*/
int32_t csi_dma_start(dmac_handle_t handle, int32_t ch)
{
    ck_dma_priv_t *dma_priv = handle;

    if (handle == NULL || ch >= dma_priv->ch_num || ch < 0) {
        return ERR_DMA(EDRV_PARAMETER);
    }

    status[ch] = DMA_STATE_BUSY;
    ck_dma_reg_t *addr = (ck_dma_reg_t *)(dma_priv->base + ch * 0x30);
    addr->CHCTRLB |= CK_DMA_INT_EN;      // interrupt enable
    addr->CHEN    |= CK_DMA_CH_EN;

    return 0;
}

/**
  \brief       Stop generate dma signal.
  \param[in]   handle damc handle to operate.
  \param[in]   ch  channel num.
  \return      error code
*/
int32_t csi_dma_stop(dmac_handle_t handle, int32_t ch)
{
    if (handle == NULL) {
        return ERR_DMA(EDRV_PARAMETER);
    }

    ck_dma_priv_t *dma_priv = handle;

    if (ch >= dma_priv->ch_num || ch < 0) {
        return ERR_DMA(EDRV_PARAMETER);
    }

    status[ch] = DMA_STATE_DONE;

    ck_dma_reg_t *addr = (ck_dma_reg_t *)(dma_priv->base + ch * 0x30);
    addr->CHCTRLB &= ~CK_DMA_INT_EN;      // interrupt disable
    addr->CHEN    &= ~CK_DMA_CH_EN;
    return 0;
}

/**
  \brief       Get DMA status.
  \param[in]   handle damc handle to operate.
  \param[in]   ch  channel num.
  \return      DMA status \ref dma_status_t
*/
dma_status_e csi_dma_get_status(dmac_handle_t handle, int32_t ch)
{
    if (handle == NULL) {
        return ERR_DMA(EDRV_PARAMETER);
    }

    ck_dma_priv_t *dma_priv = handle;

    if (ch >= dma_priv->ch_num || ch < 0) {
        return ERR_DMA(EDRV_PARAMETER);
    }

    return status[ch];
}

