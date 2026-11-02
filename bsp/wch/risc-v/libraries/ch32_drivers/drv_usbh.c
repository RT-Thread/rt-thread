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
#include "drv_usbh.h"

#ifdef BSP_USING_USBH

#define LOG_TAG "drv.usbh"
#include "drv_log.h"

static struct uhcd uhcd;

static struct rt_completion urb_completion;

__attribute__((aligned(4))) int8_t usb_rx_buf[ MAX_PACKET_SIZE ];
__attribute__((aligned(4))) int8_t usb_tx_buf[ MAX_PACKET_SIZE ];

USBOTGH_FS_TypeDef *USBFSH = USBOTG_H_FS;

rt_err_t usbh_reset_port(rt_uint8_t port)
{
    //Disable interrupt
    USBFSH->INT_EN &= (~USBFS_UIE_DETECT);
    USBFSH->HOST_CTRL &= ~USBFS_UH_SOF_EN;

    //Set address
    USBFSH->DEV_ADDR = (USBFS_UDA_GP_BIT & USBFSH->DEV_ADDR) | (0x00 & USBFS_USB_ADDR_MASK);

    //Close port
    USBFSH->HOST_CTRL &= ~USBFS_UH_PORT_EN;

    //Reset
    USBFSH->HOST_CTRL |= USBFS_UH_BUS_RESET;
    rt_thread_mdelay(30);
    USBFSH->HOST_CTRL &= ~USBFS_UH_BUS_RESET;
    rt_thread_mdelay(20);

    //Set speed
    if ((USBFSH->HOST_CTRL & USBFS_UH_PORT_EN) == 0) { //Set speed only when port is closed
        if(USBFSH->MIS_ST & USBFS_UMS_DM_LEVEL)        //RB_UMS_DM_LEVEL: 1/Low 0/Full
        {   //Low speed
            USBFSH->BASE_CTRL |= USBFS_UC_LOW_SPEED;
            USBFSH->HOST_CTRL |= USBFS_UH_LOW_SPEED;
            USBFSH->HOST_SETUP |= USBFS_UH_PRE_PID_EN;
        }
        else
        {   //Full speed
            USBFSH->BASE_CTRL &= ~USBFS_UC_LOW_SPEED;
            USBFSH->HOST_CTRL &= ~USBFS_UH_LOW_SPEED;
            USBFSH->HOST_SETUP &= ~USBFS_UH_PRE_PID_EN;
        }
    }

    //Enable port
    USBFSH->HOST_CTRL |= USBFS_UH_PORT_EN;
    USBFSH->HOST_SETUP |= USBFS_UH_SOF_EN;

    //Enable interrupt
    USBFSH->INT_EN |= USBFS_UIE_DETECT;

    if(USBFSH->INT_FG & USBFS_UIF_DETECT)
        if(USBFSH->MIS_ST & USBFS_UMS_DEV_ATTACH)
            USBFSH->INT_FG = USBFS_UIF_DETECT;

    return RT_EOK;
}

int usbh_pipe_xfer(upipe_t pipe, rt_uint8_t token, void *buffer, int nbytes, int timeouts)
{
    rt_uint8_t usb_pid;
    rt_uint8_t *tog = (rt_uint8_t *)pipe->user_data;

    USBFSH->DEV_ADDR = (USBFS_UDA_GP_BIT & USBFSH->DEV_ADDR) | (pipe->pipe_index & USBFS_USB_ADDR_MASK);

    if(pipe->ep.bEndpointAddress & USB_DIR_IN)
    {
        usb_pid = USB_PID_IN;
        USBFSH->HOST_TX_LEN = 0x00;
    }
    else
    {
        usb_pid = (token == USBH_PID_SETUP) ? USB_PID_SETUP : USB_PID_OUT;
        rt_memcpy(usb_tx_buf, buffer, nbytes);
        USBFSH->HOST_TX_LEN = nbytes;
    }

    switch(usb_pid)
    {
    case USB_PID_IN:
        if (nbytes == 0) *tog = USB_PID_DATA1;
        USBFSH->HOST_RX_CTRL = (*tog == USB_PID_DATA1) ? USBFS_UH_R_TOG : 0x00;
        break;
    case USB_PID_OUT:
        if (nbytes == 0) *tog = USB_PID_DATA1;
        USBFSH->HOST_TX_CTRL = (*tog == USB_PID_DATA1) ? USBFS_UH_T_TOG : 0x00;
        break;
    case USB_PID_SETUP:
        *(rt_uint8_t *)pipe->inst->pipe_ep0_out->user_data = USB_PID_DATA0;
        *(rt_uint8_t *)pipe->inst->pipe_ep0_in->user_data = USB_PID_DATA1;
        USBFSH->HOST_TX_CTRL = (*tog == USB_PID_DATA1) ? USBFS_UH_T_TOG : 0x00;
        break;
    }

    rt_uint16_t try = 3;
    if ((pipe->ep.bmAttributes & USB_EP_ATTR_TYPE_MASK) == USB_EP_ATTR_CONTROL)
        try = 1000;

    while(try--)
    {
        USBFSH->HOST_EP_PID = (usb_pid << 4) | (pipe->ep.bEndpointAddress & 0x0F);
        if (rt_completion_wait(&urb_completion, timeouts) != RT_EOK)
            continue;

        if (USBFSH->INT_ST & USBHS_UIS_TOG_OK)
            *tog = (*tog == USB_PID_DATA0) ? USB_PID_DATA1 : USB_PID_DATA0;

        switch(USBFSH->INT_ST & USBHS_UIS_H_RES_MASK)
        {
        case USB_PID_DATA0:
        case USB_PID_DATA1:
            pipe->status = UPIPE_STATUS_OK;
            if (pipe->callback != RT_NULL)
                pipe->callback(pipe);
            if (usb_pid == USB_PID_IN)
            {
                rt_memcpy(buffer, usb_rx_buf, USBFSH->RX_LEN);
                return USBFSH->RX_LEN;
            }
            return nbytes;

        case USB_PID_ACK:
            pipe->status = UPIPE_STATUS_OK;
            if (pipe->callback != RT_NULL)
                pipe->callback(pipe);
            return nbytes;
        case USB_PID_NAK:
            if (pipe->ep.bmAttributes == USB_EP_ATTR_INT)
                rt_thread_delay((pipe->ep.bInterval * RT_TICK_PER_SECOND / 1000) > 0 ? (pipe->ep.bInterval * RT_TICK_PER_SECOND / 1000) : 1);
            rt_thread_mdelay(1);
            continue;

        case USB_PID_STALL:
            pipe->status = UPIPE_STATUS_STALL;
            if (pipe->callback != RT_NULL)
                pipe->callback(pipe);
            return 0;

        default:
            break;
        }
    }

    pipe->status = UPIPE_STATUS_ERROR;
    if (pipe->callback != RT_NULL)
        pipe->callback(pipe);

    return -RT_ERROR;
}

rt_err_t usbh_open_pipe(upipe_t pipe)
{
    pipe->pipe_index = pipe->inst->address & USBFS_USB_ADDR_MASK;
    pipe->user_data = rt_malloc(sizeof(rt_uint8_t));
    *(rt_uint8_t *)pipe->user_data = (pipe->ep.bEndpointAddress & USB_DIR_IN) ? USB_PID_DATA0 : USB_PID_DATA0;
    return RT_EOK;
}

rt_err_t usbh_close_pipe(upipe_t pipe)
{
    rt_free(pipe->user_data);
    return RT_EOK;
}

rt_err_t hcd_init(rt_device_t dev)
{
    //Force                  reset handler        clear FIFO & interrupt flags
    USBFSH->BASE_CTRL = USBFS_UC_RESET_SIE | USBFS_UC_CLR_ALL;
    rt_thread_mdelay(20);
    USBFSH->BASE_CTRL = 0;     //Set SIE to 0 manually

    USBFSH->BASE_CTRL = USBFS_UC_HOST_MODE;
    USBFSH->HOST_CTRL = 0;
    USBFSH->DEV_ADDR = 0;
    USBFSH->HOST_EP_MOD = USBFS_UH_EP_TX_EN | USBFS_UH_EP_RX_EN; //SETUP/OUT/IN

    USBFSH->HOST_RX_DMA = (uint32_t)usb_rx_buf;
    USBFSH->HOST_TX_DMA = (uint32_t)usb_tx_buf;

    USBFSH->HOST_RX_CTRL = 0;
    USBFSH->HOST_TX_CTRL = 0;
    USBFSH->BASE_CTRL = USBFS_UC_HOST_MODE | USBFS_UC_INT_BUSY | USBFS_UC_DMA_EN;

    USBFSH->INT_FG = 0xFF;
    USBFSH->INT_EN = USBFS_UIE_TRANSFER | USBFS_UIE_DETECT;

    if( SystemCoreClock == 144000000 )
        RCC_OTGFSCLKConfig( RCC_OTGFSCLKSource_PLLCLK_Div3 );
    else if( SystemCoreClock == 96000000 )
        RCC_OTGFSCLKConfig( RCC_OTGFSCLKSource_PLLCLK_Div2 );
    else if( SystemCoreClock == 48000000 )
        RCC_OTGFSCLKConfig( RCC_OTGFSCLKSource_PLLCLK_Div1 );
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_OTG_FS, ENABLE );

    NVIC_EnableIRQ(OTG_FS_IRQn);

    rt_completion_init(&urb_completion);

    return RT_EOK;
}

static struct uhcd_ops uhcd_ops =
{
    .reset_port = usbh_reset_port,
    .pipe_xfer = usbh_pipe_xfer,
    .open_pipe = usbh_open_pipe,
    .close_pipe = usbh_close_pipe,
};

void OTG_HS_IRQHandler() __attribute__((interrupt("WCH-Interrupt-fast")));
void OTG_HS_IRQHandler()
{
    rt_interrupt_enter();

    if (USBFSH->INT_FG & USBFS_UIF_TRANSFER)
    {
        USBFSH->HOST_EP_PID = 0x00;
        USBFSH->INT_FG = USBFS_UIF_TRANSFER;
        rt_completion_done(&urb_completion);                            //本应在此处理的中断在传输函数里进行枚举
        rt_kprintf("USB: Transfer finished\n");
    }
    else if (USBFSH->INT_FG & USBFS_UIF_DETECT)
    {
        if (USBFSH->MIS_ST & USBFS_UMS_DEV_ATTACH)
        {
            rt_usbh_root_hub_connect_handler(&uhcd, 1, RT_FALSE);
            rt_kprintf("USB: Connect\n");
        }
        else
        {
            USBFSH->HOST_SETUP &= ~USBFS_UH_SOF_EN;
            USBFSH->HOST_CTRL &= ~USBFS_UH_PORT_EN;

            rt_usbh_root_hub_disconnect_handler(&uhcd, 1);
            rt_kprintf("USB: Disconnect\n");
        }
        USBFSH->INT_FG = USBFS_UIF_DETECT;
    }
    else
    {
        rt_kprintf("USB: Unknown\n");
    }

    rt_interrupt_leave();
}

int rt_hw_usbh_init()
{
    rt_err_t res = -RT_ERROR;

    rt_memset((void *)&uhcd, 0, sizeof(struct uhcd));
    uhcd.parent.type = RT_Device_Class_USBHost;
    uhcd.parent.init = hcd_init;
    uhcd.ops = &uhcd_ops;
    uhcd.num_ports = 1;

    res = rt_device_register(&uhcd.parent, "usbh", RT_DEVICE_FLAG_DEACTIVATE);

    if (res != RT_EOK)
    {
        rt_kprintf("register usb host failed res = %d\r\n", res);
        return -RT_ERROR;
    }

    rt_usb_host_init();

    return RT_EOK;
}
#endif //BSP_USING_USBH