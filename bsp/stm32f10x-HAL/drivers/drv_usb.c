/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-10-30     ZYH            the first version
 * 2017-11-15     ZYH          update to 3.0.0
 */
#include "drv_usb.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#define USB_DISCONNECT_PIN                  30      //PA9
static PCD_HandleTypeDef _stm_pcd;
static struct udcd _stm_udc;
static struct ep_id _ep_pool[] =
{
    {0x0,  USB_EP_ATTR_CONTROL,     USB_DIR_INOUT,  64, ID_ASSIGNED  },
    {0x1,  USB_EP_ATTR_BULK,        USB_DIR_IN,     64, ID_UNASSIGNED},
    {0x1,  USB_EP_ATTR_BULK,        USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0x2,  USB_EP_ATTR_INT,         USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0x2,  USB_EP_ATTR_INT,         USB_DIR_IN,     64, ID_UNASSIGNED},
    {0x3,  USB_EP_ATTR_INT,         USB_DIR_IN,     64, ID_UNASSIGNED},
    {0xFF, USB_EP_ATTR_TYPE_MASK,   USB_DIR_MASK,   0,  ID_ASSIGNED  },
};

void USB_LP_CAN1_RX0_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_PCD_IRQHandler(&_stm_pcd);
    rt_interrupt_leave();
}

void HAL_PCD_ResetCallback(PCD_HandleTypeDef *pcd)
{
    /* open ep0 OUT and IN */
    HAL_PCD_EP_Open(pcd, 0x00, 0x40, EP_TYPE_CTRL);
    HAL_PCD_EP_Open(pcd, 0x80, 0x40, EP_TYPE_CTRL);
    rt_usbd_reset_handler(&_stm_udc);
}

void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd)
{
    rt_usbd_ep0_setup_handler(&_stm_udc, (struct urequest *)hpcd->Setup);
}

void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
    if (epnum == 0)
    {
        rt_usbd_ep0_in_handler(&_stm_udc);
    }
    else
    {
        rt_usbd_ep_in_handler(&_stm_udc, 0x80 | epnum, hpcd->IN_ep[epnum].xfer_count);
    }
}

void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd)
{
    rt_usbd_connect_handler(&_stm_udc);
}

void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd)
{
//  rt_usbd_sof_handler(&_stm_udc);
}

void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd)
{
    rt_usbd_disconnect_handler(&_stm_udc);
}

void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
    if (epnum != 0)
    {
        rt_usbd_ep_out_handler(&_stm_udc, epnum, hpcd->OUT_ep[epnum].xfer_count);
    }
    else
    {
        rt_usbd_ep0_out_handler(&_stm_udc, hpcd->OUT_ep[0].xfer_count);
    }
}

void HAL_PCDEx_SetConnectionState(PCD_HandleTypeDef *hpcd, uint8_t state)
{
    if (state == 1)
    {
        rt_pin_write(USB_DISCONNECT_PIN, PIN_HIGH);
    }
    else
    {
        rt_pin_write(USB_DISCONNECT_PIN, PIN_LOW);
    }
}

void HAL_PCD_MspInit(PCD_HandleTypeDef *pcdHandle)
{
    if (pcdHandle->Instance == USB)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        rt_pin_mode(USB_DISCONNECT_PIN, PIN_MODE_OUTPUT);
        rt_pin_write(USB_DISCONNECT_PIN, PIN_LOW);
        /* Peripheral clock enable */
        __HAL_RCC_USB_CLK_ENABLE();
        /* Peripheral interrupt init */
        HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    }
}

void HAL_PCD_MspDeInit(PCD_HandleTypeDef *pcdHandle)
{
    if (pcdHandle->Instance == USB)
    {
        /* Peripheral clock disable */
        __HAL_RCC_USB_CLK_DISABLE();
        /* Peripheral interrupt Deinit*/
        HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
    }
}

static rt_err_t _ep_set_stall(rt_uint8_t address)
{
    HAL_PCD_EP_SetStall(&_stm_pcd, address);
    return RT_EOK;
}

static rt_err_t _ep_clear_stall(rt_uint8_t address)
{
    HAL_PCD_EP_ClrStall(&_stm_pcd, address);
    return RT_EOK;
}

static rt_err_t _set_address(rt_uint8_t address)
{
    HAL_PCD_SetAddress(&_stm_pcd, address);
    return RT_EOK;
}

static rt_err_t _set_config(rt_uint8_t address)
{
    return RT_EOK;
}

static rt_err_t _ep_enable(uep_t ep)
{
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);
    HAL_PCD_EP_Open(&_stm_pcd, ep->ep_desc->bEndpointAddress,
                    ep->ep_desc->wMaxPacketSize, ep->ep_desc->bmAttributes);
    return RT_EOK;
}

static rt_err_t _ep_disable(uep_t ep)
{
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);
    HAL_PCD_EP_Close(&_stm_pcd, ep->ep_desc->bEndpointAddress);
    return RT_EOK;
}

static rt_size_t _ep_read(rt_uint8_t address, void *buffer)
{
    rt_size_t size = 0;
    RT_ASSERT(buffer != RT_NULL);
    return size;
}

static rt_size_t _ep_read_prepare(rt_uint8_t address, void *buffer, rt_size_t size)
{
    HAL_PCD_EP_Receive(&_stm_pcd, address, buffer, size);
    return size;
}

static rt_size_t _ep_write(rt_uint8_t address, void *buffer, rt_size_t size)
{
    HAL_PCD_EP_Transmit(&_stm_pcd, address, buffer, size);
    return size;
}

static rt_err_t _ep0_send_status(void)
{
    HAL_PCD_EP_Transmit(&_stm_pcd, 0x00, NULL, 0);
    return RT_EOK;
}

static rt_err_t _suspend(void)
{
    return RT_EOK;
}

static rt_err_t _wakeup(void)
{
    return RT_EOK;
}

static rt_err_t _init(rt_device_t device)
{
    PCD_HandleTypeDef *pcd;
    /* Set LL Driver parameters */
    pcd = (PCD_HandleTypeDef *)device->user_data;
    pcd->Instance = USB;
    pcd->Init.dev_endpoints = 8;
    pcd->Init.speed = PCD_SPEED_FULL;
    pcd->Init.ep0_mps = DEP0CTL_MPS_8;
    pcd->Init.low_power_enable = DISABLE;
    pcd->Init.lpm_enable = DISABLE;
    pcd->Init.battery_charging_enable = DISABLE;
    /* Initialize LL Driver */
    HAL_PCD_Init(pcd);
    HAL_PCDEx_PMAConfig(pcd, 0x00, PCD_SNG_BUF, 0x18);
    HAL_PCDEx_PMAConfig(pcd, 0x80, PCD_SNG_BUF, 0x58);
    HAL_PCDEx_PMAConfig(pcd, 0x81, PCD_SNG_BUF, 0x98);
    HAL_PCDEx_PMAConfig(pcd, 0x01, PCD_SNG_BUF, 0x118);
    HAL_PCDEx_PMAConfig(pcd, 0x82, PCD_SNG_BUF, 0xD8);
    HAL_PCDEx_PMAConfig(pcd, 0x02, PCD_SNG_BUF, 0x158);
    HAL_PCDEx_PMAConfig(pcd, 0x83, PCD_SNG_BUF, 0x198);
    HAL_PCD_Start(pcd);
    return RT_EOK;
}

const static struct udcd_ops _udc_ops =
{
    _set_address,
    _set_config,
    _ep_set_stall,
    _ep_clear_stall,
    _ep_enable,
    _ep_disable,
    _ep_read_prepare,
    _ep_read,
    _ep_write,
    _ep0_send_status,
    _suspend,
    _wakeup,
};

int stm_usbd_register(void)
{
    rt_memset((void *)&_stm_udc, 0, sizeof(struct udcd));
    _stm_udc.parent.type = RT_Device_Class_USBDevice;
    _stm_udc.parent.init = _init;
    _stm_udc.parent.user_data = &_stm_pcd;
    _stm_udc.ops = &_udc_ops;
    /* Register endpoint infomation */
    _stm_udc.ep_pool = _ep_pool;
    _stm_udc.ep0.id = &_ep_pool[0];
    rt_device_register((rt_device_t)&_stm_udc, "usbd", 0);
    rt_usb_device_init();
    return 0;
}

INIT_DEVICE_EXPORT(stm_usbd_register);
