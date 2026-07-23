/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-4-30      IceBear003   the first version adapted from CherryUSB
 */

#include "board.h"
#include "drv_usbd.h"

#ifdef BSP_USING_USBD

#define LOG_TAG "drv.usbd"
#include "drv_log.h"

#define UEP_MPS_64          64
#define UEP_MPS_512         512

#define _get_ep_idx(address)    ((address) & USB_EPNO_MASK)
#define _get_ep_dir(address)    ((address) & USB_DIR_MASK)
#define _is_dir_in(address)     (_get_ep_dir(address) == USB_DIR_IN)
#define _is_dir_out(address)    (_get_ep_dir(address) == USB_DIR_OUT)

#define _get_dma(ep_idx)          (*(volatile uint32_t *)((uint32_t)(USBFSD->UEP0_DMA) + 4 * ep_idx))
#define _set_dma(ep_idx, addr)    (*(volatile uint32_t *)((uint32_t)(USBFSD->UEP0_DMA) + 4 * ep_idx) = addr)
#define _set_tx_len(ep_idx, len)  (*(volatile uint16_t *)((uint32_t)(USBFSD->UEP0_TX_LEN) + 4 * ep_idx) = len)
#define _get_tx_len(ep_idx)       (*(volatile uint16_t *)((uint32_t)(USBFSD->UEP0_TX_LEN) + 4 * ep_idx))
#define _set_tx_ctrl(ep_idx, val) (*(volatile uint8_t *)((uint32_t)(USBFSD->UEP0_TX_CTRL) + 4 * ep_idx) = val)
#define _get_tx_ctrl(ep_idx)      (*(volatile uint8_t *)((uint32_t)(USBFSD->UEP0_TX_CTRL) + 4 * ep_idx))
#define _set_rx_ctrl(ep_idx, val) (*(volatile uint8_t *)((uint32_t)(USBFSD->UEP0_RX_CTRL) + 4 * ep_idx) = val)
#define _get_rx_ctrl(ep_idx)      (*(volatile uint8_t *)((uint32_t)(USBFSD->UEP0_RX_CTRL) + 4 * ep_idx))

static struct udcd udcd;

USBOTG_FS_TypeDef *USBFSD = USBOTG_FS;

static struct ep_id endpoint_pool[] =
{
    {0x0,  USB_EP_ATTR_CONTROL,   USB_DIR_INOUT, 64,  ID_ASSIGNED  },
    {0x1,  USB_EP_ATTR_BULK,      USB_DIR_IN,    512, ID_UNASSIGNED},
    {0x1,  USB_EP_ATTR_BULK,      USB_DIR_OUT,   512, ID_UNASSIGNED},
    {0x2,  USB_EP_ATTR_INT,       USB_DIR_IN,    512, ID_UNASSIGNED},
    {0x2,  USB_EP_ATTR_INT,       USB_DIR_OUT,   512, ID_UNASSIGNED},
    {0x3,  USB_EP_ATTR_ISOC,      USB_DIR_IN,    512, ID_UNASSIGNED},
    {0x3,  USB_EP_ATTR_ISOC,      USB_DIR_OUT,   512, ID_UNASSIGNED},
    {0xFF, USB_EP_ATTR_TYPE_MASK, USB_DIR_MASK,  0,   ID_ASSIGNED  },
};

uint8_t _uep_mod_get(uint8_t ep_idx)
{
    switch(ep_idx)
    {
        case 1:
        case 4: return USBFSD->UEP4_1_MOD;
        case 2:
        case 3: return USBFSD->UEP2_3_MOD;
        case 5:
        case 6: return USBFSD->UEP5_6_MOD;
        case 7: return USBFSD->UEP7_MOD;
        default: return 0;
    }
}

rt_err_t _uep_mod_set(uint8_t ep_idx, uint8_t value)
{
    switch(ep_idx)
    {
        case 1:
        case 4: USBFSD->UEP4_1_MOD = value; break;
        case 2:
        case 3: USBFSD->UEP2_3_MOD = value; break;
        case 5:
        case 6: USBFSD->UEP5_6_MOD = value; break;
        case 7: USBFSD->UEP7_MOD = value; break;
        default: return -RT_ERROR;
    }
    return RT_EOK;
}

uint8_t _uep_tx_en(uint8_t ep_idx)
{
    switch(ep_idx)
    {
        case 1: return USBFS_UEP1_TX_EN;
        case 4: return USBFS_UEP4_TX_EN;
        case 2: return USBFS_UEP2_TX_EN;
        case 3: return USBFS_UEP3_TX_EN;
        case 5: return USBFS_UEP5_TX_EN;
        case 6: return USBFS_UEP6_TX_EN;
        case 7: return USBFS_UEP7_TX_EN;
        default: return 0;
    }
}

uint8_t _uep_rx_en(uint8_t ep_idx)
{
    switch(ep_idx)
    {
        case 1: return USBFS_UEP1_TX_EN;
        case 4: return USBFS_UEP4_TX_EN;
        case 2: return USBFS_UEP2_TX_EN;
        case 3: return USBFS_UEP3_TX_EN;
        case 5: return USBFS_UEP5_TX_EN;
        case 6: return USBFS_UEP6_TX_EN;
        case 7: return USBFS_UEP7_TX_EN;
        default: return 0;
    }
}

rt_err_t usbd_set_address(rt_uint8_t address)
{
    if(address > 0x7f)
        return -RT_ERROR;
    USBFSD->DEV_ADDR = (USBFSD->DEV_ADDR & USBFS_UDA_GP_BIT) | address;
    return RT_EOK;
}

rt_err_t usbd_set_config(rt_uint8_t address)
{  //Nonsense?
    return RT_EOK;
}

rt_err_t usbd_ep_set_stall(rt_uint8_t address)
{
    uint8_t ep_idx = _get_ep_idx(address);

    if (_is_dir_out(address))
        if (ep_idx == 0)
            _set_rx_ctrl(0, USBFS_UEP_R_TOG | USBFS_UEP_R_RES_STALL);
        else
            _set_rx_ctrl(ep_idx, (_get_rx_ctrl(ep_idx) & ~USBFS_UEP_R_RES_MASK) | USBFS_UEP_R_RES_STALL);
    else
    if (ep_idx == 0)
        _set_tx_ctrl(0, USBFS_UEP_T_TOG | USBFS_UEP_T_RES_STALL);
    else
        _set_tx_ctrl(ep_idx, (_get_tx_ctrl(ep_idx) & ~USBFS_UEP_T_RES_MASK) | USBFS_UEP_T_RES_STALL);

    return RT_EOK;
}

rt_err_t usbd_ep_clear_stall(rt_uint8_t address)
{
    uint8_t ep_idx = _get_ep_idx(address);

    if (_is_dir_in(address))
        _set_tx_ctrl(ep_idx, (_get_tx_ctrl(ep_idx) & ~(USBFS_UEP_T_TOG | USBFS_UEP_T_RES_MASK)) | USBFS_UEP_T_RES_NAK);
    else
        _set_rx_ctrl(ep_idx, (_get_rx_ctrl(ep_idx) & ~(USBFS_UEP_R_TOG | USBFS_UEP_R_RES_MASK)) | USBFS_UEP_R_RES_ACK);

    return RT_EOK;
}

rt_err_t usbd_ep_enable(struct uendpoint* ep)
{
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);

    uint8_t address = EP_ADDRESS(ep);
    uint8_t ep_idx = _get_ep_idx(address);

    if (ep_idx != 0)
    {
        uint8_t mod = _is_dir_in(address) ? _uep_tx_en(ep_idx) : _uep_rx_en(ep_idx);
        mod = _uep_mod_get(ep_idx) | mod;
        _uep_mod_set(ep_idx, mod);
    } else return -RT_ERROR;

    return RT_EOK;
}

rt_err_t usbd_ep_disable(struct uendpoint* ep)
{
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);

    uint8_t address = EP_ADDRESS(ep);
    uint8_t ep_idx = _get_ep_idx(address);

    if (ep_idx != 0)
    {
        uint8_t mod = _is_dir_in(address) ? _uep_tx_en(ep_idx) : _uep_rx_en(ep_idx);
        mod = _uep_mod_get(ep_idx) & ~mod;
        _uep_mod_set(ep_idx, mod);
    } else return -RT_ERROR;

    return RT_EOK;
}

rt_size_t usbd_ep_read_prepare(rt_uint8_t address, void *buffer, rt_size_t size)
{
    uint8_t ep_idx = _get_ep_idx(address);

    if (_is_dir_in(address))
        return 0;

    if (size > (ep_idx ? UEP_MPS_512 : UEP_MPS_64))
        size = (ep_idx ? UEP_MPS_512 : UEP_MPS_64);

    _set_dma(ep_idx, (uint32_t)buffer);

    if (ep_idx == 0)
        if(size == 0) _set_rx_ctrl(0, USBFS_UEP_R_RES_ACK | USBFS_UEP_R_TOG);
        else _set_rx_ctrl(ep_idx, USBFS_UEP_R_RES_ACK);
    else _set_rx_ctrl(0, (_get_rx_ctrl(ep_idx) & ~USBFS_UEP_R_RES_MASK) | USBFS_UEP_R_RES_ACK | USBFS_UEP_R_TOG);

    return size;
}

rt_size_t usbd_ep_read(rt_uint8_t address, void *buffer)
{
    uint8_t ep_idx = _get_ep_idx(address);

    if (_is_dir_out(address))
        return -2;
    if ((uint32_t)buffer & 0x03)
        return -3;

    uint32_t dmabuf = _get_dma(ep_idx);
    rt_size_t size = USBFSD->RX_LEN;

    if (size > 0 && (uint32_t)buffer != dmabuf)
        rt_memcpy(buffer, (void *)dmabuf, size);

    return size;
}

rt_size_t usbd_ep_write(rt_uint8_t address, void *buffer, rt_size_t size)
{
    uint8_t ep_idx = _get_ep_idx(address);

    if (_is_dir_in(address))
        return -2;
    if ((uint32_t)buffer & 0x03)
        return -3;

    uint32_t dmabuf = _get_dma(ep_idx);

    if (size > (ep_idx ? UEP_MPS_512 : UEP_MPS_64))
        size = (ep_idx ? UEP_MPS_512 : UEP_MPS_64);

    _set_tx_len(ep_idx, size);
    if(ep_idx == 0)
    {
        if(size != 0)
            _set_dma(0, (uint32_t)buffer);
        _set_tx_ctrl(0, USBFS_UEP_T_TOG | USBFS_UEP_T_RES_ACK);
    }
    else
    {
        if(size != 0)
            rt_memcpy((void *)dmabuf, buffer, size);
        _set_tx_ctrl(ep_idx, (_get_tx_ctrl(ep_idx) & ~USBFS_UEP_T_RES_MASK) | USBFS_UEP_T_RES_ACK);
    }

    return size;
}

rt_err_t usbd_ep0_send_status(void)
{
    _set_tx_len(0, 0);
    _set_tx_ctrl(0, USBFS_UEP_T_RES_ACK | USBFS_UEP_T_TOG);
    _set_dma(0, 0);
    return RT_EOK;
}

rt_err_t usbd_suspend(void)
{
    return RT_EOK;
}

rt_err_t usbd_wakeup(void)
{
    return RT_EOK;
}

const struct udcd_ops udcd_ops =
{
    .set_address = usbd_set_address,
    .set_config = usbd_set_config,
    .ep_set_stall = usbd_ep_set_stall,
    .ep_clear_stall = usbd_ep_clear_stall,
    .ep_enable = usbd_ep_enable,
    .ep_disable = usbd_ep_disable,
    .ep_read_prepare = usbd_ep_read_prepare,
    .ep_read = usbd_ep_read,
    .ep_write = usbd_ep_write,
    .ep0_send_status = usbd_ep0_send_status,
    .suspend = usbd_suspend,
    .wakeup = usbd_wakeup,
};

rt_err_t dcd_init(rt_device_t dev)
{
    USBFSD->BASE_CTRL = 0x00;

    USBFSD->UEP4_1_MOD = USBFS_UEP4_RX_EN | USBFS_UEP4_TX_EN | USBFS_UEP1_RX_EN | USBFS_UEP1_TX_EN;
    USBFSD->UEP2_3_MOD = USBFS_UEP2_RX_EN | USBFS_UEP2_TX_EN | USBFS_UEP3_RX_EN | USBFS_UEP3_TX_EN;
    USBFSD->UEP5_6_MOD = USBFS_UEP5_RX_EN | USBFS_UEP5_TX_EN | USBFS_UEP6_RX_EN | USBFS_UEP6_TX_EN;
    USBFSD->UEP7_MOD = USBFS_UEP7_RX_EN | USBFS_UEP7_TX_EN;

    USBFSD->INT_FG = 0xFF;
    USBFSD->INT_EN = USBFS_UIE_SUSPEND | USBFS_UIE_BUS_RST | USBFS_UIE_TRANSFER;
    USBFSD->DEV_ADDR = 0x00;

    USBFSD->BASE_CTRL = USBFS_UC_DEV_PU_EN | USBFS_UC_INT_BUSY | USBFS_UC_DMA_EN;
    USBFSD->UDEV_CTRL = USBFS_UD_PD_DIS | USBFS_UD_PORT_EN;

    NVIC_EnableIRQ(OTG_FS_IRQn);

    return RT_EOK;
}

void USBD_IRQHandler(void) __attribute__((interrupt()));
void USBD_IRQHandler()
{
    rt_interrupt_enter();
    uint8_t int_fg = USBFSD->INT_FG;

    if (int_fg & USBFS_UIF_TRANSFER) {
        uint8_t ep_idx = USBFSD->INT_ST & USBFS_UIS_ENDP_MASK;
        uint8_t tog;
        switch (USBFSD->INT_ST & USBFS_UIS_TOKEN_MASK) {
            case USBFS_UIS_TOKEN_SETUP:
                _set_rx_ctrl(ep_idx, USBFS_UEP_R_RES_NAK);
                break;

            case USBFS_UIS_TOKEN_IN:
                if (ep_idx == 0x00)
                {
                    tog = _get_tx_ctrl(ep_idx) & USBFS_UEP_T_TOG;
                    _set_tx_ctrl(ep_idx, (_get_tx_ctrl(ep_idx) & 0b11111000) | ~tog | USBFS_UEP_T_RES_NAK);
                    if (_get_dma(ep_idx) != 0)
                    {
                        rt_usbd_ep0_in_handler(&udcd);
                    }
                }
                else
                {
                    _set_tx_ctrl(ep_idx, (_get_tx_ctrl(ep_idx) & ~USBFS_UEP_T_RES_MASK) | USBFS_UEP_T_RES_NAK);
                    rt_usbd_ep_in_handler(&udcd, ep_idx | USB_DIR_IN, _get_tx_len(ep_idx));
                }
                break;
            case USBFS_UIS_TOKEN_OUT:
                if (ep_idx == 0x00)
                {
                    if(USBFSD->INT_ST & USBFS_UIS_TOG_OK)
                    {
                        tog = _get_rx_ctrl(ep_idx) & USBFS_UEP_R_TOG;
                        _set_rx_ctrl(ep_idx, (_get_rx_ctrl(ep_idx) & 0b11111000) | ~tog | USBFS_UEP_R_RES_NAK);
                    }
                    else
                    {
                        _set_rx_ctrl(ep_idx, (_get_rx_ctrl(ep_idx) & ~USBFS_UEP_R_RES_MASK) | USBFS_UEP_R_RES_NAK);
                    }
                }
                else
                {
                    _set_rx_ctrl(ep_idx, (_get_rx_ctrl(ep_idx) & ~USBFS_UEP_R_RES_MASK) | USBFS_UEP_R_RES_NAK);
                    if (USBFSD->INT_ST & USBFS_UIS_TOG_OK) {
                        _set_rx_ctrl(ep_idx, (_get_rx_ctrl(ep_idx) & ~USBFS_UEP_R_RES_MASK) | USBFS_UEP_R_RES_NAK);
                        rt_usbd_ep_out_handler(&udcd, ep_idx | USB_DIR_OUT, 0);
                    }
                }
                break;
            default:
                break;
        }

        USBFSD->INT_FG = USBFS_UIF_TRANSFER;
    } else if (int_fg & USBFS_UIF_BUS_RST) {
        USBFSD->UEP0_TX_LEN = 0;
        USBFSD->UEP0_TX_CTRL = USBFS_UEP_T_RES_NAK;
        USBFSD->UEP0_RX_CTRL = USBFS_UEP_R_RES_NAK;

        for (uint8_t i = 1; i < 8; i++) {
            _set_tx_len(i, 0);
            _set_tx_ctrl(i, USBFS_UEP_T_RES_NAK | USBFS_UEP_T_AUTO_TOG);
            _set_rx_ctrl(i, USBFS_UEP_R_RES_NAK | USBFS_UEP_R_AUTO_TOG);
        }

        _set_rx_ctrl(0, USBFS_UEP_R_RES_ACK);
        rt_usbd_reset_handler(&udcd);

        USBFSD->INT_FG |= USBFS_UIF_BUS_RST;
    } else if (int_fg & USBFS_UIF_SUSPEND) {
        USBFSD->INT_FG = USBFS_UIF_SUSPEND;
    } else {
        USBFSD->INT_FG = int_fg;
    }

    rt_interrupt_leave();
}

int rt_hw_usbd_init()
{
    rt_err_t res = -RT_ERROR;

    rt_memset((void *)&udcd, 0, sizeof(struct uhcd));
    udcd.parent.type = RT_Device_Class_USBDevice;
    udcd.parent.user_data = (void *)USBFS_BASE;
    udcd.parent.init = dcd_init;
    udcd.ops = &udcd_ops;
    udcd.ep_pool = endpoint_pool;
    udcd.ep0.id = &endpoint_pool[0];
    udcd.device_is_hs = RT_FALSE;

    res = rt_device_register(&udcd.parent, "usbd", RT_DEVICE_FLAG_DEACTIVATE);

    if (res != RT_EOK)
    {
        rt_kprintf("register usb device failed res = %d\r\n", res);
        return -RT_ERROR;
    }

    rt_usb_device_init();

    return RT_EOK;
}
#endif //BSP_USING_USBD
