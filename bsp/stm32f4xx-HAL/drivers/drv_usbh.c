/*
 * File      : stm32_usbh.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-10-30     ZYH            the first version
 */
#include "drv_usbh.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#define OTG_FS_PORT 1
static HCD_HandleTypeDef _stm_hhcd_fs;
static struct rt_completion urb_completion;
void HAL_HCD_MspInit(HCD_HandleTypeDef *hcdHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if (hcdHandle->Instance == USB_OTG_FS)
    {
        /**USB_OTG_FS GPIO Configuration
        PA9     ------> USB_OTG_FS_VBUS
        PA10     ------> USB_OTG_FS_ID
        PA11     ------> USB_OTG_FS_DM
        PA12     ------> USB_OTG_FS_DP
        */
        __HAL_RCC_GPIOA_CLK_ENABLE();
#ifdef USBH_USING_VBUS
        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif
        GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_11;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* Peripheral clock enable */
        __HAL_RCC_USB_OTG_FS_CLK_ENABLE();

        /* Peripheral interrupt init */
        HAL_NVIC_SetPriority(OTG_FS_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
    }
}

void HAL_HCD_MspDeInit(HCD_HandleTypeDef *hcdHandle)
{
    if (hcdHandle->Instance == USB_OTG_FS)
    {
        /* Peripheral clock disable */
        __HAL_RCC_USB_OTG_FS_CLK_DISABLE();

        /**USB_OTG_FS GPIO Configuration
        PA9     ------> USB_OTG_FS_VBUS
        PA10     ------> USB_OTG_FS_ID
        PA11     ------> USB_OTG_FS_DM
        PA12     ------> USB_OTG_FS_DP
        */
#ifdef USBH_USING_VBUS
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9);
#endif
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_12 | GPIO_PIN_11);

        /* Peripheral interrupt Deinit*/
        HAL_NVIC_DisableIRQ(OTG_FS_IRQn);
    }
}
void OTG_FS_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_HCD_IRQHandler(&_stm_hhcd_fs);
    rt_interrupt_leave();
}
void HAL_HCD_SOF_Callback(HCD_HandleTypeDef *hhcd)//提供定时器
{
    //rt_kprintf("sof callback\n");
}
static __IO rt_bool_t connect_status = RT_FALSE;
void HAL_HCD_Connect_Callback(HCD_HandleTypeDef *hhcd)
{
    uhcd_t hcd = (uhcd_t)hhcd->pData;
    if (!connect_status)
    {
        connect_status = RT_TRUE;
        RT_DEBUG_LOG(RT_DEBUG_USB, ("connected\n"));
        rt_usbh_root_hub_connect_handler(hcd, OTG_FS_PORT, RT_FALSE);
    }
}
void HAL_HCD_Disconnect_Callback(HCD_HandleTypeDef *hhcd)
{
    uhcd_t hcd = (uhcd_t)hhcd->pData;
    if (connect_status)
    {
        connect_status = RT_FALSE;
        RT_DEBUG_LOG(RT_DEBUG_USB, ("disconnnect\n"));
        rt_usbh_root_hub_disconnect_handler(hcd, OTG_FS_PORT);
    }
}
void HAL_HCD_HC_NotifyURBChange_Callback(HCD_HandleTypeDef *hhcd, uint8_t chnum, HCD_URBStateTypeDef urb_state)
{
    //rt_kprintf("NotifyURBChange_Callback\n");
    rt_completion_done(&urb_completion);
}
static rt_err_t drv_reset_port(rt_uint8_t port)
{
    RT_DEBUG_LOG(RT_DEBUG_USB, ("reset port\n"));
    HAL_HCD_ResetPort(&_stm_hhcd_fs);
    return RT_EOK;
}

static int drv_pipe_xfer(upipe_t pipe, rt_uint8_t token, void *buffer, int nbytes, int timeout)
{
    while (1)
    {
        if(!connect_status)
        {
            return -1;
        }
        rt_completion_init(&urb_completion);
        HAL_HCD_HC_SubmitRequest(&_stm_hhcd_fs,
                                 pipe->pipe_index,
                                 (pipe->ep.bEndpointAddress & 0x80) >> 7,
                                 pipe->ep.bmAttributes,
                                 token,
                                 buffer,
                                 nbytes,
                                 0);
        rt_completion_wait(&urb_completion, timeout);
        if (HAL_HCD_HC_GetState(&_stm_hhcd_fs, pipe->pipe_index) == HC_NAK)
        {
            RT_DEBUG_LOG(RT_DEBUG_USB, ("nak\n"));
            if (pipe->ep.bmAttributes == USB_EP_ATTR_INT)
            {
                rt_thread_delay((pipe->ep.bInterval * RT_TICK_PER_SECOND / 1000) > 0 ? (pipe->ep.bInterval * RT_TICK_PER_SECOND / 1000) : 1);
            }
            HAL_HCD_HC_Halt(&_stm_hhcd_fs, pipe->pipe_index);
            HAL_HCD_HC_Init(&_stm_hhcd_fs,
                    pipe->pipe_index,
                    pipe->ep.bEndpointAddress,
                    pipe->inst->address,
                    USB_OTG_SPEED_FULL,
                    pipe->ep.bmAttributes,
                    pipe->ep.wMaxPacketSize);
            continue;
        }
        else if(HAL_HCD_HC_GetState(&_stm_hhcd_fs, pipe->pipe_index) == HC_STALL)
        {
            RT_DEBUG_LOG(RT_DEBUG_USB, ("stall\n"));
            pipe->status = UPIPE_STATUS_STALL;
            if (pipe->callback != RT_NULL)
            {
                pipe->callback(pipe);
            }
            return -1;
        }
        else if(HAL_HCD_HC_GetState(&_stm_hhcd_fs, pipe->pipe_index) == URB_ERROR)
        {
            RT_DEBUG_LOG(RT_DEBUG_USB, ("error\n"));
            pipe->status = UPIPE_STATUS_ERROR;
            if (pipe->callback != RT_NULL)
            {
                pipe->callback(pipe);
            }
            return -1;
        }
        else if (HAL_HCD_HC_GetURBState(&_stm_hhcd_fs, pipe->pipe_index) != URB_NOTREADY && 
                HAL_HCD_HC_GetURBState(&_stm_hhcd_fs, pipe->pipe_index) != URB_NYET)
        {
            RT_DEBUG_LOG(RT_DEBUG_USB, ("ok\n"));
            pipe->status = UPIPE_STATUS_OK;
            if (pipe->callback != RT_NULL)
            {
                pipe->callback(pipe);
            }
            return nbytes;
        }
        return -1;
    }
}
static rt_uint16_t pipe_index = 0;
static rt_uint8_t  drv_get_free_pipe_index()
{
    rt_uint8_t idx;
    for (idx = 1; idx < 16; idx++)
    {
        if (!(pipe_index & (0x01 << idx)))
        {
            pipe_index |= (0x01 << idx);
            return idx;
        }
    }
    return 0xff;
}
static void drv_free_pipe_index(rt_uint8_t index)
{
    pipe_index &= ~(0x01 << index);
}
static rt_err_t drv_open_pipe(upipe_t pipe)
{
    pipe->pipe_index = drv_get_free_pipe_index();

    HAL_HCD_HC_Init(&_stm_hhcd_fs,
                    pipe->pipe_index,
                    pipe->ep.bEndpointAddress,
                    pipe->inst->address,
                    USB_OTG_SPEED_FULL,
                    pipe->ep.bmAttributes,
                    pipe->ep.wMaxPacketSize);
    /* Set DATA0 PID token*/
    if(_stm_hhcd_fs.hc[pipe->pipe_index].ep_is_in)
    {
        _stm_hhcd_fs.hc[pipe->pipe_index].toggle_in = 0;
    }
    else
    {
        _stm_hhcd_fs.hc[pipe->pipe_index].toggle_out = 0;
    }
    return RT_EOK;
}
static rt_err_t drv_close_pipe(upipe_t pipe)
{
    HAL_HCD_HC_Halt(&_stm_hhcd_fs, pipe->pipe_index);
    drv_free_pipe_index(pipe->pipe_index);
    return RT_EOK;
}

struct uhcd_ops _uhcd_ops =
{
    drv_reset_port,
    drv_pipe_xfer,
    drv_open_pipe,
    drv_close_pipe,
};

static rt_err_t _init(rt_device_t device)
{
    HCD_HandleTypeDef *hhcd = (HCD_HandleTypeDef *)device->user_data;
    hhcd->Instance = USB_OTG_FS;
    hhcd->Init.Host_channels = 8;
    hhcd->Init.speed = HCD_SPEED_FULL;
    hhcd->Init.dma_enable = DISABLE;
    hhcd->Init.phy_itface = HCD_PHY_EMBEDDED;
    hhcd->Init.Sof_enable = DISABLE;
    RT_ASSERT(HAL_HCD_Init(hhcd) == HAL_OK);
    HAL_HCD_Start(hhcd);
#ifdef USBH_USING_CONTROLLABLE_POWER
    rt_pin_mode(USBH_POWER_PIN, PIN_MODE_OUTPUT);

    rt_pin_write(USBH_POWER_PIN, PIN_LOW);
#endif
    return RT_EOK;
}
int stm_usbh_register(void)
{
    uhcd_t uhcd = (uhcd_t)rt_malloc(sizeof(struct uhcd));
    RT_ASSERT(uhcd != RT_NULL);
    rt_memset((void *)uhcd, 0, sizeof(struct uhcd));

    uhcd->parent.type = RT_Device_Class_USBHost;
    uhcd->parent.init = _init;
    uhcd->parent.user_data = &_stm_hhcd_fs;
    uhcd->ops = &_uhcd_ops;
    uhcd->num_ports = 1;
    _stm_hhcd_fs.pData = uhcd;

    rt_device_register((rt_device_t)uhcd, "usbh", 0);
    rt_usb_host_init();
    return RT_EOK;
}
INIT_DEVICE_EXPORT(stm_usbh_register);
