/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-5-4        CHChen           First version
*
******************************************************************************/
#include <rtconfig.h>



#if defined(BSP_USING_USBH) || defined(BSP_USING_HSUSBH)

#include <rtdevice.h>
#include <rthw.h>
#include <NuMicro.h>

#include "usb.h"
#include "usbh_lib.h"

#define NU_MAX_USBH_PORT    2        //USB1.1 + USB2.0 port
#define NU_MAX_USBH_PIPE    16
#define NU_USBH_THREAD_STACK_SIZE    2048

#define NU_MAX_USBH_HUB_PORT_DEV    USB_HUB_PORT_NUM

/* Private typedef --------------------------------------------------------------*/
typedef struct nu_port_dev
{
    rt_bool_t bRHParent;
    UDEV_T *pUDev;
    EP_INFO_T *apsEPInfo[NU_MAX_USBH_PIPE];
    struct urequest asSetupReq[NU_MAX_USBH_PIPE];
    struct rt_completion utr_completion;
    int port_num;
    rt_bool_t bEnumDone;
} S_NU_PORT_DEV;


typedef struct nu_port_ctrl
{
    S_NU_PORT_DEV sRHPortDev;
    S_NU_PORT_DEV asHubPortDev[NU_MAX_USBH_HUB_PORT_DEV];
} S_NU_RH_PORT_CTRL;


struct nu_usbh_dev
{
    uhcd_t uhcd;
    S_NU_RH_PORT_CTRL asPortCtrl[NU_MAX_USBH_PORT];
};

/* Private variables ------------------------------------------------------------*/
static struct nu_usbh_dev s_sUSBHDev =
{
    .uhcd = RT_NULL,
};

static S_NU_RH_PORT_CTRL *
GetRHPortControlFromPipe(
    upipe_t pipe
)
{
    uinst_t inst;
    int port;
    if (pipe->inst->parent_hub->is_roothub)
    {
        //case: device ---> root hub
        inst = pipe->inst;
        port = inst->port;
    }
    else
    {
        //case: device ---> hub ---> root hub
        inst = pipe->inst->parent_hub->self;
        port = inst->port;
    }

    if (port > NU_MAX_USBH_PORT)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_open_pipe ERROR: port index over NU_MAX_USBH_PORT\n"));
        return RT_NULL;
    }

    return &s_sUSBHDev.asPortCtrl[port - 1];;
}

static S_NU_PORT_DEV *
GetPortDevFromPipe(
    upipe_t pipe
)
{
    S_NU_RH_PORT_CTRL *psRHPortCtrl = GetRHPortControlFromPipe(pipe);
    int i;

    if (psRHPortCtrl == RT_NULL)
        return RT_NULL;

    if (pipe->inst->parent_hub->is_roothub)
    {
        //case: device ---> root hub
        return &psRHPortCtrl->sRHPortDev;
    }

    //case: device ---> hub ---> root hub
    for (i = 0 ; i < NU_MAX_USBH_HUB_PORT_DEV; i ++)
    {
        if (psRHPortCtrl->asHubPortDev[i].port_num == pipe->inst->port)
            break;
    }

    if (i >= NU_MAX_USBH_HUB_PORT_DEV)
        return RT_NULL;
    return &psRHPortCtrl->asHubPortDev[i];
}



static rt_err_t nu_reset_port(rt_uint8_t port)
{
    S_NU_RH_PORT_CTRL *psPortCtrl;

    if (port > NU_MAX_USBH_PORT)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_reset_port ERROR: port index over NU_MAX_USBH_PORT\n"));
        return RT_EIO;
    }

    psPortCtrl = &s_sUSBHDev.asPortCtrl[port - 1];
    if (psPortCtrl->sRHPortDev.pUDev == NULL)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_reset_port ERROR: udev not found\n"));
        return RT_EIO;
    }

    usbh_reset_port(psPortCtrl->sRHPortDev.pUDev);

    return RT_EOK;
}

static EP_INFO_T *GetFreePipe(
    S_NU_RH_PORT_CTRL *psPortCtrl,
    S_NU_PORT_DEV *psPortDev,
    rt_uint8_t *pu8PipeIndex
)
{
    rt_uint8_t i;
    if (psPortCtrl == NULL)
        return NULL;

    for (i = 1; i < NU_MAX_USBH_PIPE; i ++)
    {
        if (psPortDev->apsEPInfo[i] == NULL)
            break;
    }

    if (i >= NU_MAX_USBH_PIPE)
        return RT_NULL;

    EP_INFO_T *psEPInfo = rt_malloc(sizeof(EP_INFO_T));

    psPortDev->apsEPInfo[i] = psEPInfo;
    *pu8PipeIndex = i;
    return psEPInfo;
}

static void FreePipe(
    S_NU_RH_PORT_CTRL *psPortCtrl,
    S_NU_PORT_DEV *psPortDev,
    rt_uint8_t u8PipeIndex
)
{
    if (psPortCtrl == NULL)
        return;

    if (u8PipeIndex >= NU_MAX_USBH_PIPE)
        return;

    if (psPortDev->apsEPInfo[u8PipeIndex])
    {
        rt_free(psPortDev->apsEPInfo[u8PipeIndex]);
        psPortDev->apsEPInfo[u8PipeIndex] = RT_NULL;
    }
}

static  S_NU_PORT_DEV *
AllocateNewUDev(
    S_NU_RH_PORT_CTRL *psRHPortCtrl
)
{
    int i;
    for (i = 0 ; i < NU_MAX_USBH_HUB_PORT_DEV; i ++)
    {
        if (psRHPortCtrl->asHubPortDev[i].pUDev == NULL)
            break;
    }

    if (i >= NU_MAX_USBH_HUB_PORT_DEV)
        return RT_NULL;

    psRHPortCtrl->asHubPortDev[i].pUDev = alloc_device();

    if (psRHPortCtrl->asHubPortDev[i].pUDev == NULL)
        return RT_NULL;

    return &psRHPortCtrl->asHubPortDev[i];
}


static rt_err_t nu_open_pipe(upipe_t pipe)
{
    S_NU_RH_PORT_CTRL *psPortCtrl;
    S_NU_PORT_DEV *psPortDev;

    psPortCtrl = GetRHPortControlFromPipe(pipe);
    if (psPortCtrl == RT_NULL)
    {
        return RT_EIO;
    }

    if (psPortCtrl->sRHPortDev.pUDev == NULL)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_open_pipe ERROR: udev not found\n"));
        return RT_EIO;
    }

    psPortDev = GetPortDevFromPipe(pipe);

    if ((psPortDev == NULL) || (psPortDev->pUDev == NULL))
    {
        //allocate new dev for hub device
        psPortDev = AllocateNewUDev(psPortCtrl);

        if (psPortDev == RT_NULL)
        {
            RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_open_pipe ERROR: udev allocate failed\n"));
            return RT_EIO;
        }

        if (pipe->inst->speed)
        {
            psPortDev->pUDev->speed = SPEED_FULL;
        }
        else
        {
            psPortDev->pUDev->speed = SPEED_HIGH;
        }

        psPortDev->pUDev->parent = NULL;
        psPortDev->pUDev->hc_driver = psPortCtrl->sRHPortDev.pUDev->hc_driver;
        psPortDev->port_num = pipe->inst->port;
        psPortDev->pUDev->port_num = pipe->inst->port;
        psPortDev->bEnumDone = FALSE;
    }

    //For ep0 control transfer
    if ((pipe->ep.bEndpointAddress & 0x7F) == 0)
    {
        pipe->pipe_index = 0;
        return RT_EOK;
    }

    EP_INFO_T *psEPInfo = GetFreePipe(psPortCtrl, psPortDev, &pipe->pipe_index);

    if (psEPInfo == RT_NULL)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_open_pipe ERROR: get free pipe failed\n"));
        return RT_ENOMEM;
    }

    int  pksz;

    psEPInfo->bEndpointAddress = pipe->ep.bEndpointAddress;
    psEPInfo->bmAttributes = pipe->ep.bmAttributes;

    pksz = pipe->ep.wMaxPacketSize;
    pksz = (pksz & 0x07ff) * (1 + ((pksz >> 11) & 3));
    psEPInfo->wMaxPacketSize = pksz;

    psEPInfo->bInterval = pipe->ep.bInterval;
    psEPInfo->hw_pipe = NULL;
    psEPInfo->bToggle = 0;

    return RT_EOK;
}

static rt_err_t nu_close_pipe(upipe_t pipe)
{
    int i;
    S_NU_RH_PORT_CTRL *psPortCtrl;
    S_NU_PORT_DEV *psPortDev;

    psPortCtrl = GetRHPortControlFromPipe(pipe);
    if (psPortCtrl == RT_NULL)
    {
        return RT_EIO;
    }

    psPortDev = GetPortDevFromPipe(pipe);

    //For ep0 control transfer
    if ((pipe->ep.bEndpointAddress & 0x7F) == 0)
    {
        if ((psPortDev) && (psPortDev->bRHParent == FALSE) && (psPortDev->bEnumDone == TRUE))
        {
            if (psPortDev->pUDev)
            {
                for (i = 0; i < NU_MAX_USBH_PIPE; i++)
                {
                    if (psPortDev->apsEPInfo[i] != NULL)
                    {
                        usbh_quit_xfer(psPortDev->pUDev, psPortDev->apsEPInfo[i]);
                    }
                }

                free_device(psPortDev->pUDev);
                psPortDev->pUDev = NULL;
            }
            psPortDev->port_num = 0;
        }
    }

    if (psPortDev != NULL)
    {
        FreePipe(psPortCtrl, psPortDev, pipe->pipe_index);
    }
    return RT_EOK;
}

static int nu_ctrl_xfer(
    S_NU_PORT_DEV *psPortDev,
    struct urequest *psSetup,
    void *buffer,
    int timeouts
)
{
    uint32_t  xfer_len;
    int    ret;

    ret = usbh_ctrl_xfer(psPortDev->pUDev, psSetup->request_type, psSetup->bRequest, psSetup->wValue, psSetup->wIndex, psSetup->wLength, buffer, &xfer_len, timeouts * 10);

    if (ret < 0)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_ctrl_xfer ERROR: xfer failed %d\n", ret));
        return ret;
    }

    if (xfer_len != psSetup->wLength)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_ctrl_xfer ERROR: xfer length %d %d\n", psSetup->wLength, xfer_len));
    }

    if ((psSetup->bRequest == USB_REQ_SET_ADDRESS) && ((psSetup->request_type & 0x60) == REQ_TYPE_STD_DEV))
        psPortDev->pUDev->dev_num = psSetup->wValue;

    if ((psSetup->bRequest == USB_REQ_SET_CONFIGURATION) && ((psSetup->request_type & 0x60) == REQ_TYPE_STD_DEV))
    {
        psPortDev->pUDev->cur_conf = psSetup->wValue;
        psPortDev->bEnumDone = TRUE;
    }

    return xfer_len;
}

static int nu_bulk_xfer(
    S_NU_PORT_DEV *psPortDev,
    UTR_T *psUTR,
    int timeouts
)
{
    int ret;

    ret = usbh_bulk_xfer(psUTR);

    if (ret < 0)
        return ret;

    //wait transfer done
    rt_completion_wait(&(psPortDev->utr_completion), timeouts);
    return 0;
}

static int nu_int_xfer(
    upipe_t pipe,
    S_NU_PORT_DEV *psPortDev,
    UTR_T *psUTR,
    int timeouts
)
{
    int ret;
    int retry = 3;

    while (retry > 0)
    {
        ret = usbh_int_xfer(psUTR);
        if (ret == 0)
            break;

        RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_int_xfer ERROR: failed to submit interrupt request\n"));
        rt_thread_delay((pipe->ep.bInterval * RT_TICK_PER_SECOND / 1000) > 0 ? (pipe->ep.bInterval * RT_TICK_PER_SECOND / 1000) : 1);
        retry --;
    }

    if (ret < 0)
        return ret;

    return 0;
}

static void xfer_done_cb(UTR_T *psUTR)
{
    S_NU_PORT_DEV *psPortDev = (S_NU_PORT_DEV *)psUTR->context;

    //transfer done, signal utr_completion
    rt_completion_done(&(psPortDev->utr_completion));
}

static void int_xfer_done_cb(UTR_T *psUTR)
{
    upipe_t pipe = (upipe_t)psUTR->context;

    if (psUTR->status != 0)
    {
        rt_kprintf("Interrupt xfer failed %d\n", psUTR->status);
        free_utr(psUTR);
        return;
    }

    if (pipe->callback != RT_NULL)
    {
        struct uhost_msg msg;
        msg.type = USB_MSG_CALLBACK;
        msg.content.cb.function = pipe->callback;
        msg.content.cb.context = pipe;
        rt_usbh_event_signal(&msg);
    }

    free_utr(psUTR);
}


static int nu_pipe_xfer(upipe_t pipe, rt_uint8_t token, void *buffer, int nbytes, int timeouts)
{
    S_NU_RH_PORT_CTRL *psPortCtrl;
    S_NU_PORT_DEV *psPortDev;

    psPortCtrl = GetRHPortControlFromPipe(pipe);
    if (psPortCtrl == RT_NULL)
    {
        return RT_EIO;
    }

    psPortDev = GetPortDevFromPipe(pipe);

    if (psPortDev->pUDev == NULL)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_pipe_xfer ERROR: udev not found\n"));
        return -RT_ERROR;
    }

    //ctrl xfer
    if (pipe->ep.bmAttributes == USB_EP_ATTR_CONTROL)
    {
        if (token == USBH_PID_SETUP)
        {
            struct urequest *psSetup;
            psSetup = (struct urequest *)buffer;

            if (psSetup->request_type & USB_REQ_TYPE_DIR_IN)
            {
                //Store setup request
                rt_memcpy(&psPortCtrl->asHubPortDev->asSetupReq[pipe->pipe_index], psSetup, sizeof(struct urequest));
            }
            else
            {
                //Trigger USBHostLib Ctril_Xfer
                nu_ctrl_xfer(psPortDev, psSetup, NULL, timeouts);
            }
            return nbytes;
        }
        else
        {
            //token == USBH_PID_DATA
            if (buffer == RT_NULL)
                return nbytes;

            if ((pipe->ep.bEndpointAddress & USB_DIR_MASK) == USB_DIR_IN)
            {
                //Trigger USBHostLib Ctril_Xfer
                nu_ctrl_xfer(psPortDev, &psPortCtrl->asHubPortDev->asSetupReq[pipe->pipe_index], buffer, timeouts);
            }
            else
            {
                RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_pipe_xfer ERROR: can not handle ctrl xfer case: buffer!=NULL and USB_DIR_OUT\n"));
            }
            return nbytes;
        }
    }


    //others xfer
    rt_completion_init(&(psPortDev->utr_completion));

    //setup UTR
    UTR_T *psUTR;
    int i32XferLen;

    psUTR = alloc_utr(psPortDev->pUDev);
    if (!psUTR)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_pipe_xfer ERROR: unable alloc UTR\n"));
        return -(RT_ERROR);
    }

    psUTR->ep = psPortDev->apsEPInfo[pipe->pipe_index];
    psUTR->buff = buffer;
    psUTR->data_len = nbytes;
    psUTR->xfer_len = 0;
    psUTR->func = xfer_done_cb;
    psUTR->context = psPortDev;
    psUTR->bIsTransferDone = 0;
    psUTR->status = 0;

    if (pipe->ep.bmAttributes == USB_EP_ATTR_BULK)
    {
        if (nu_bulk_xfer(psPortDev, psUTR, timeouts) < 0)
        {
            free_utr(psUTR);
            RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_pipe_xfer ERROR: bulk transfer failed\n"));
            return -(RT_ERROR);
        }
    }

    if (pipe->ep.bmAttributes == USB_EP_ATTR_INT)
    {
        psUTR->func = int_xfer_done_cb;
        psUTR->context = pipe;

        if (nu_int_xfer(pipe, psPortDev, psUTR, timeouts) < 0)
        {
            free_utr(psUTR);
            RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_pipe_xfer ERROR: int transfer failed\n"));
            return -(RT_ERROR);
        }

        return nbytes;
    }

    //TODO: ISO transfer
    if (pipe->ep.bmAttributes == USB_EP_ATTR_ISOC)
    {
        free_utr(psUTR);
        RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_pipe_xfer ERROR: isoc transfer not support\n"));
        return -1;
    }

    if (psUTR->bIsTransferDone == 0)
    {
        //Timeout
        RT_DEBUG_LOG(RT_DEBUG_USB, ("nu_pipe_xfer ERROR: timeout\n"));
        pipe->status = UPIPE_STATUS_ERROR;
        usbh_quit_utr(psUTR);
    }
    else
    {
        // Transfer Done. Get status
        if (psUTR->status == 0)
        {
            pipe->status = UPIPE_STATUS_OK;
        }
        else if (psUTR->status == USBH_ERR_STALL)
        {
            pipe->status = UPIPE_STATUS_STALL;
        }
        else
        {
            pipe->status = UPIPE_STATUS_ERROR;
        }
    }

    i32XferLen = psUTR->xfer_len;
    free_utr(psUTR);

    //Call callback
    if (pipe->callback != RT_NULL)
    {
        struct uhost_msg msg;
        msg.type = USB_MSG_CALLBACK;
        msg.content.cb.function = pipe->callback;
        msg.content.cb.context = pipe->user_data;
        rt_usbh_event_signal(&msg);
    }

    if (pipe->status != UPIPE_STATUS_OK)
        return -(RT_ERROR);

    if ((pipe->ep.bEndpointAddress & USB_DIR_MASK) == USB_DIR_IN)
    {
        return i32XferLen;
    }
    else if ((pipe->ep.bEndpointAddress & USB_DIR_MASK) == USB_DIR_OUT)
    {
        return i32XferLen;
    }

    return nbytes;
}

//Pooling USB root hub status task
static void nu_usbh_rh_thread_entry(void *parameter)
{
    while (1)
    {
        usbh_pooling_root_hubs();
        rt_thread_delay(10);
    }
}

static void nu_hcd_connect_callback(
    struct udev_t *udev,
    int param
)
{
    int i;
    int port_index;
    S_NU_RH_PORT_CTRL *psPortCtrl;

    for (i = 0; i < NU_MAX_USBH_PORT; i++)
    {
        psPortCtrl = &s_sUSBHDev.asPortCtrl[i];
        if (psPortCtrl->sRHPortDev.pUDev == NULL)
            break;
    }

    if (i >= NU_MAX_USBH_PORT)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("ERROR: port connect slot is full\n"));
        return;
    }

    port_index = i + 1;
    psPortCtrl->sRHPortDev.pUDev = udev;
    psPortCtrl->sRHPortDev.bRHParent = TRUE;
    RT_DEBUG_LOG(RT_DEBUG_USB, ("usb connected\n"));
    if (udev->speed == SPEED_HIGH)
        rt_usbh_root_hub_connect_handler(s_sUSBHDev.uhcd, port_index, RT_TRUE);
    else
        rt_usbh_root_hub_connect_handler(s_sUSBHDev.uhcd, port_index, RT_FALSE);
}

static void nu_hcd_disconnect_callback(
    struct udev_t *udev,
    int param
)
{
    int i;
    int port_index;
    S_NU_RH_PORT_CTRL *psPortCtrl;

    for (i = 0; i < NU_MAX_USBH_PORT; i++)
    {
        psPortCtrl = &s_sUSBHDev.asPortCtrl[i];
        if (psPortCtrl->sRHPortDev.pUDev == udev)
            break;
    }

    if (i >= NU_MAX_USBH_PORT)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("ERROR: udev not found\n"));
        return;
    }

    for (i = 0; i < NU_MAX_USBH_PIPE; i++)
    {
        if (psPortCtrl->sRHPortDev.apsEPInfo[i] != NULL)
        {
            usbh_quit_xfer(psPortCtrl->sRHPortDev.pUDev, psPortCtrl->sRHPortDev.apsEPInfo[i]);
        }
    }

    port_index = i + 1;
    psPortCtrl->sRHPortDev.pUDev = NULL;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("usb disconnnect\n"));
    rt_usbh_root_hub_disconnect_handler(s_sUSBHDev.uhcd, port_index);
}


/* USB host operations -----------------------------------------------------------*/
static struct uhcd_ops nu_uhcd_ops =
{
    nu_reset_port,
    nu_pipe_xfer,
    nu_open_pipe,
    nu_close_pipe,
};

static rt_err_t nu_hcd_init(rt_device_t device)
{
    rt_thread_t thread;

    usbh_core_init();

    //install connect/disconnect callback
    usbh_install_conn_callback(nu_hcd_connect_callback, nu_hcd_disconnect_callback);
    usbh_pooling_root_hubs();

    //create thread for polling usbh port status
    /* create usb hub thread */
    thread = rt_thread_create("usbh_drv", nu_usbh_rh_thread_entry, RT_NULL,
                              NU_USBH_THREAD_STACK_SIZE, 8, 20);
    if (thread != RT_NULL)
    {
        /* startup usb host thread */
        rt_thread_startup(thread);
    }
    else
    {
        return -(RT_EEMPTY);
    }

    return RT_EOK;
}

/* global function for USB host library -----------------------------*/
uint32_t usbh_get_ticks(void)
{
    return rt_tick_get();
}

void usbh_delay_ms(int msec)
{
    rt_thread_mdelay(msec);
}

uint32_t usbh_tick_from_millisecond(uint32_t msec)
{
    return rt_tick_from_millisecond(msec);
}


int nu_usbh_register(void)
{
    rt_err_t res = -RT_ERROR;

#if !defined(BSP_USING_HSOTG)
    SYS_UnlockReg();

#if defined(BSP_USING_HSUSBH)
    /* Set USB Host role */
    SYS->USBPHY = (SYS->USBPHY & ~SYS_USBPHY_HSUSBROLE_Msk) | (0x1u << SYS_USBPHY_HSUSBROLE_Pos);
    SYS->USBPHY |= SYS_USBPHY_HSUSBEN_Msk | SYS_USBPHY_SBO_Msk;
    rt_thread_delay(20);
    SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;

#endif

#if defined(BSP_USING_USBH)
    /* Enable USBD and OTG clock */
    CLK_EnableModuleClock(USBD_MODULE);
    CLK_EnableModuleClock(OTG_MODULE);
    /* Set USB Host role */
    SYS->USBPHY = (SYS->USBPHY & ~SYS_USBPHY_USBROLE_Msk) | (0x1u << SYS_USBPHY_USBROLE_Pos);
    SYS->USBPHY |= SYS_USBPHY_USBEN_Msk | SYS_USBPHY_SBO_Msk ;
#endif

    SYS_LockReg();
#endif


    rt_memset(&s_sUSBHDev, 0x0, sizeof(struct nu_usbh_dev));

    uhcd_t uhcd = (uhcd_t)rt_malloc(sizeof(struct uhcd));
    if (uhcd == RT_NULL)
    {
        rt_kprintf("uhcd malloc failed\r\n");
        return -RT_ERROR;
    }

    rt_memset((void *)uhcd, 0, sizeof(struct uhcd));

    uhcd->parent.type = RT_Device_Class_USBHost;
    uhcd->parent.init = nu_hcd_init;
    uhcd->parent.user_data = &s_sUSBHDev;

    uhcd->ops = &nu_uhcd_ops;
    uhcd->num_ports = NU_MAX_USBH_PORT;
    s_sUSBHDev.uhcd = uhcd;

    res = rt_device_register(&uhcd->parent, "usbh", RT_DEVICE_FLAG_DEACTIVATE);
    if (res != RT_EOK)
    {
        rt_kprintf("register usb host failed res = %d\r\n", res);
        return -RT_ERROR;
    }

    /*initialize the usb host functin */
    res = rt_usb_host_init();

    return RT_EOK;
}
INIT_DEVICE_EXPORT(nu_usbh_register);

#endif






