/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-02-16     Tuber             first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_usbh.h"

#ifdef BSP_USING_USBH

static struct rt_completion urb_completion;

//USB接收缓存区
__align(4) UINT8 usb_rx_buf[MAX_PACKET_SIZE];   // IN, must even address
__align(4) UINT8 usb_tx_buf[MAX_PACKET_SIZE];   // OUT, must even address

static struct uhcd uhcd;

static rt_err_t drv_reset_port(rt_uint8_t port)
{
    //关闭中断
    R8_USB_INT_EN = 0x00;

    R8_USB_DEV_AD = (R8_USB_DEV_AD & RB_UDA_GP_BIT) | (0x00 & MASK_USB_ADDR);   //设置地址
    R8_UHOST_CTRL &= ~RB_UH_PORT_EN;    // 关掉端口

    //判断设备速度
    if (R8_USB_MIS_ST & RB_UMS_DM_LEVEL)
    {
        //低速
        R8_USB_CTRL |= RB_UC_LOW_SPEED; // 默认为低速
        R8_UHOST_CTRL = (R8_UHOST_CTRL | RB_UH_LOW_SPEED) | RB_UH_BUS_RESET;    // 默认为低速,开始复位
    }
    else
    {
        //全速
        R8_USB_CTRL &= ~ RB_UC_LOW_SPEED;   // 默认为全速
        R8_UHOST_CTRL = (R8_UHOST_CTRL & ~RB_UH_LOW_SPEED) | RB_UH_BUS_RESET;   // 默认为全速,开始复位
    }

    rt_thread_mdelay(15); // 复位时间10mS到20mS
    R8_UHOST_CTRL = R8_UHOST_CTRL & ~ RB_UH_BUS_RESET;  // 结束复位
    rt_thread_mdelay(1);
    R8_UHOST_CTRL |= RB_UH_PORT_EN; //打开端口
    R8_USB_INT_FG = RB_UIF_DETECT;  // 清中断标志
    //打开中断
    R8_USB_INT_EN = RB_UIF_TRANSFER | RB_UIE_DETECT;

    return RT_EOK;
}

static int drv_pipe_xfer(upipe_t pipe, rt_uint8_t token, void *buffer, int nbytes, int timeouts)
{
    rt_err_t res;
    UINT16 i;
    UINT16 retry_count = 3;
    rt_uint8_t usb_pid, res_pid;
    UINT8 *tog = (UINT8 *)pipe->user_data;

    //设置目标usb地址
    R8_USB_DEV_AD = (R8_USB_DEV_AD & RB_UDA_GP_BIT) | (pipe->inst->address & MASK_USB_ADDR);

    //判断是in还是out操作
    if (pipe->ep.bEndpointAddress & USB_DIR_IN)
    {
        usb_pid = USB_PID_IN; //in
        R8_UH_TX_LEN = 0x00;
    }
    else
    {
        usb_pid = (token == USBH_PID_SETUP) ? USB_PID_SETUP : USB_PID_OUT; //setup/out
        rt_memcpy(usb_tx_buf, buffer, nbytes);
        R8_UH_TX_LEN = nbytes;
    }

    //设置数据TOG
    switch (usb_pid)
    {
    case USB_PID_IN:
        if (nbytes == 0) *tog = USB_PID_DATA1; //状态反馈
        R8_UH_RX_CTRL = (*tog == USB_PID_DATA1) ? RB_UH_R_TOG : 0x00;
        break;

    case USB_PID_OUT:
        if (nbytes == 0) *tog = USB_PID_DATA1; //状态反馈
        R8_UH_TX_CTRL = (*tog == USB_PID_DATA1) ? RB_UH_T_TOG : 0x00;
        break;

    case USB_PID_SETUP:
        *(UINT8 *)pipe->inst->pipe_ep0_out->user_data = USB_PID_DATA0;
        *(UINT8 *)pipe->inst->pipe_ep0_in->user_data = USB_PID_DATA1;
        R8_UH_TX_CTRL = (*tog == USB_PID_DATA1) ? RB_UH_T_TOG : 0x00;
        break;
    }

    //usb枚举的时候加大重试次数，提高usb设备枚举成功率
    if ((pipe->ep.bmAttributes & USB_EP_ATTR_TYPE_MASK) == USB_EP_ATTR_CONTROL)
    {
        retry_count = 1000;
    }

    for (i = 0; i < retry_count; i++)
    {
        //传输
        R8_UH_EP_PID = (usb_pid << 4) | (pipe->ep.bEndpointAddress & 0x0F);
        res = rt_completion_wait(&urb_completion, timeouts);
        if (res != RT_EOK)
        {
            return res;
        }

        //判断是否需要反转数据
        if (R8_USB_INT_ST & RB_UIS_TOG_OK)
        {
            *tog = (*tog == USB_PID_DATA0) ? USB_PID_DATA1 : USB_PID_DATA0;//翻转
        }

        res_pid = R8_USB_INT_ST & MASK_UIS_H_RES;

        switch (res_pid)
        {
        case USB_PID_ACK://发送成功
            pipe->status = UPIPE_STATUS_OK;
            if (pipe->callback != RT_NULL) pipe->callback(pipe);
            return nbytes;
        case USB_PID_DATA0: //收到数据
        case USB_PID_DATA1: //收到数据
            pipe->status = UPIPE_STATUS_OK;
            if (pipe->callback != RT_NULL) pipe->callback(pipe);
            //拷贝数据到buffer
            if (usb_pid == USB_PID_IN)
            {
                rt_memcpy(buffer, usb_rx_buf, R8_USB_RX_LEN);
                return R8_USB_RX_LEN;
            }
            return nbytes;
        case USB_PID_NAK: //数据未就绪
            if (pipe->ep.bmAttributes == USB_EP_ATTR_INT)
            {
                rt_thread_delay((pipe->ep.bInterval * RT_TICK_PER_SECOND / 1000) > 0 ? (pipe->ep.bInterval * RT_TICK_PER_SECOND / 1000) : 1);
            }
            rt_thread_mdelay(1);
            continue;//重试
        case USB_PID_STALL: //传输停止
            pipe->status = UPIPE_STATUS_STALL;
            if (pipe->callback != RT_NULL) pipe->callback(pipe);
            return 0;
        default:
            break;
        }
    }

    pipe->status = UPIPE_STATUS_ERROR;

    if (pipe->callback != RT_NULL) pipe->callback(pipe);
    return -RT_ERROR;
}

static rt_err_t drv_open_pipe(upipe_t pipe)
{
    pipe->pipe_index = pipe->inst->address & MASK_USB_ADDR;
    pipe->user_data = rt_malloc(sizeof(UINT8));

    //默认发送DATA0
    if (pipe->ep.bEndpointAddress & USB_DIR_IN)
    {
        *(UINT8 *)pipe->user_data = USB_PID_DATA0;
    }
    else
    {
        *(UINT8 *)pipe->user_data = USB_PID_DATA0;
    }


    return RT_EOK;
}

static rt_err_t drv_close_pipe(upipe_t pipe)
{
    rt_free(pipe->user_data);

    return RT_EOK;
}

static struct uhcd_ops uhcd_ops =
{
    drv_reset_port,
    drv_pipe_xfer,
    drv_open_pipe,
    drv_close_pipe,
};

static rt_err_t hcd_init(rt_device_t dev)
{
    R16_PIN_ANALOG_IE |= RB_PIN_USB_IE;

    R8_USB_CTRL = RB_UC_HOST_MODE;
    R8_UHOST_CTRL = 0;
    R8_USB_DEV_AD = 0x00;

    R8_UH_EP_MOD = RB_UH_EP_TX_EN | RB_UH_EP_RX_EN;
    R16_UH_RX_DMA = (UINT16)(UINT32)usb_rx_buf;
    R16_UH_TX_DMA = (UINT16)(UINT32)usb_tx_buf;

    R8_USB_CTRL =  RB_UC_HOST_MODE | RB_UC_INT_BUSY | RB_UC_DMA_EN;
    R8_UH_SETUP = RB_UH_SOF_EN;
    R8_USB_INT_FG = 0xFF;

    R8_USB_INT_EN = RB_UIF_TRANSFER | RB_UIE_DETECT;

    //开启中断
    NVIC_EnableIRQ(USB_IRQn);

    rt_completion_init(&urb_completion);

    return RT_EOK;
}

void USB_IRQHandler()
{
    rt_interrupt_enter();

    //USB连接断开中断
    if (R8_USB_INT_FG & RB_UIF_DETECT)
    {
        R8_USB_INT_FG = RB_UIF_DETECT;//清除中断

        //检查USB设备连接状态
        if ((R8_USB_MIS_ST & RB_UMS_DEV_ATTACH) != 0)
        {
            rt_usbh_root_hub_connect_handler(&uhcd, 1, RT_FALSE);
            rt_kprintf("usb: up\n");
        }
        else
        {
            rt_usbh_root_hub_disconnect_handler(&uhcd, 1);
            rt_kprintf("usb: down\n");
        }
    }

    if (R8_USB_INT_FG & RB_UIF_TRANSFER)
    {
        R8_UH_EP_PID = 0x00; //停止发送

        R8_USB_INT_FG = RB_UIF_TRANSFER;//清除中断

        rt_completion_done(&urb_completion);
    }

    if (R8_USB_INT_FG & RB_UIF_SUSPEND)
    {
        R8_USB_INT_FG = RB_UIF_SUSPEND;//清除中断
    }

    if (R8_USB_INT_FG & RB_UIF_HST_SOF)
    {
        R8_USB_INT_FG = RB_UIF_HST_SOF;//清除中断
    }

    if (R8_USB_INT_FG & RB_UIF_FIFO_OV)
    {
        R8_USB_INT_FG = RB_UIF_FIFO_OV;//清除中断
    }

    rt_interrupt_leave();
}

int rt_hw_usbh_init(void)
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

    rt_usb_host_init("usbh");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_usbh_init);
#endif /* BSP_USING_USBH */

