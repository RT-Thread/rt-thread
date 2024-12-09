/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-5-4        CHChen           First version
* 2021-11-5       Wayne            Revise
*
******************************************************************************/
#include <rtconfig.h>



#if defined(BSP_USING_USBH) || defined(BSP_USING_HSUSBH)

#include <rtdevice.h>
#include <rthw.h>
#include "NuMicro.h"

#include "usb.h"
#include "usbh_lib.h"

#define LOG_TAG       "drv.usb.host"
#define DBG_LVL       DBG_INFO
#include <drv_log.h>

#if !defined(NU_USBHOST_HUB_POLLING_INTERVAL)
    #define NU_USBHOST_HUB_POLLING_INTERVAL    (100)
#endif

#define NU_MAX_USBH_PORT    2        //USB1.1 + USB2.0 port
#define NU_MAX_USBH_PIPE    16
#define NU_USBH_THREAD_STACK_SIZE    2048

#define NU_MAX_USBH_HUB_PORT_DEV    USB_HUB_PORT_NUM

#define NU_USBHOST_HUB_POLLING_LOCK
#if defined(NU_USBHOST_HUB_POLLING_LOCK)
#define NU_USBHOST_MUTEX_INIT()      { \
                                s_sUSBHDev.lock = rt_mutex_create("usbhost_lock", RT_IPC_FLAG_PRIO); \
                                RT_ASSERT(s_sUSBHDev.lock != RT_NULL); \
                            }

#define NU_USBHOST_LOCK()      { \
                                rt_err_t result = rt_mutex_take(s_sUSBHDev.lock, RT_WAITING_FOREVER); \
                                RT_ASSERT(result == RT_EOK); \
                            }

#define NU_USBHOST_UNLOCK()    { \
                                rt_err_t result = rt_mutex_release(s_sUSBHDev.lock); \
                                RT_ASSERT(result == RT_EOK); \
                            }
#else
#define NU_USBHOST_MUTEX_INIT()
#define NU_USBHOST_LOCK()
#define NU_USBHOST_UNLOCK()
#endif

/* Private typedef --------------------------------------------------------------*/
typedef struct nu_port_dev
{
    rt_bool_t bRHParent;
    UDEV_T *pUDev;
    EP_INFO_T *apsEPInfo[NU_MAX_USBH_PIPE];
    struct urequest asSetupReq[NU_MAX_USBH_PIPE];
    uint32_t u32SentLength[NU_MAX_USBH_PIPE];
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
    struct uhcd uhcd;
    rt_thread_t polling_thread;
    rt_mutex_t  lock;
    S_NU_RH_PORT_CTRL asPortCtrl[NU_MAX_USBH_PORT];
};

/* Private variables ------------------------------------------------------------*/
static struct nu_usbh_dev s_sUSBHDev;

static S_NU_RH_PORT_CTRL *
GetRHPortControlFromPipe(
    upipe_t pipe)
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
        LOG_D("nu_open_pipe ERROR: port index over NU_MAX_USBH_PORT");
        return RT_NULL;
    }

    return &s_sUSBHDev.asPortCtrl[port - 1];;
}

static S_NU_PORT_DEV *
GetPortDevFromPipe(
    upipe_t pipe)
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
        LOG_D("%s ERROR: port index over NU_MAX_USBH_PORT", __func__);
        return -RT_EIO;
    }

    psPortCtrl = &s_sUSBHDev.asPortCtrl[port - 1];
    if (psPortCtrl->sRHPortDev.pUDev == NULL)
    {
        LOG_D("%s ERROR: udev not found", __func__);
        return -RT_EIO;
    }

    usbh_reset_port(psPortCtrl->sRHPortDev.pUDev);

    return RT_EOK;
}

static EP_INFO_T *GetFreePipe(
    S_NU_RH_PORT_CTRL *psPortCtrl,
    S_NU_PORT_DEV *psPortDev,
    rt_uint8_t *pu8PipeIndex)
{
    if (psPortCtrl != NULL)
    {
        int i;
        /* Find free Pipe */
        for (i = 0; i < NU_MAX_USBH_PIPE; i ++)
        {
            if (psPortDev->apsEPInfo[i] == NULL)
                break;
        }

        if (i < NU_MAX_USBH_PIPE)
        {
            EP_INFO_T *psEPInfo = rt_malloc(sizeof(EP_INFO_T));
            if (psEPInfo != RT_NULL)
            {
                psPortDev->apsEPInfo[i] = psEPInfo;
                *pu8PipeIndex = i;
                return psEPInfo;
            }
        }
    }
    return RT_NULL;
}

static void FreePipe(
    S_NU_RH_PORT_CTRL *psPortCtrl,
    S_NU_PORT_DEV *psPortDev,
    rt_uint8_t u8PipeIndex)
{
    if ((psPortCtrl != RT_NULL) &&
            (u8PipeIndex < NU_MAX_USBH_PIPE) &&
            (psPortDev->apsEPInfo[u8PipeIndex] != RT_NULL))
    {
        rt_free(psPortDev->apsEPInfo[u8PipeIndex]);
        psPortDev->apsEPInfo[u8PipeIndex] = RT_NULL;
    }
}

static  S_NU_PORT_DEV *
AllocateNewUDev(
    S_NU_RH_PORT_CTRL *psRHPortCtrl)
{
    if (psRHPortCtrl != RT_NULL)
    {
        int i;
        /* Find free Dev */
        for (i = 0 ; i < NU_MAX_USBH_HUB_PORT_DEV; i ++)
        {
            if (psRHPortCtrl->asHubPortDev[i].pUDev == NULL)
                break;
        }

        if (i < NU_MAX_USBH_HUB_PORT_DEV)
        {
            psRHPortCtrl->asHubPortDev[i].pUDev = alloc_device();
            if (psRHPortCtrl->asHubPortDev[i].pUDev == NULL)
            {
                return RT_NULL;
            }
            else
            {
                return &psRHPortCtrl->asHubPortDev[i];
            }
        }
    }
    return RT_NULL;
}

static rt_err_t nu_open_pipe(upipe_t pipe)
{
    S_NU_RH_PORT_CTRL *psPortCtrl;
    S_NU_PORT_DEV *psPortDev;

    psPortCtrl = GetRHPortControlFromPipe(pipe);
    if (psPortCtrl == RT_NULL)
    {
        LOG_D("%s ERROR: RHPort not found", __func__);
        goto exit_nu_open_pipe;
    }

    if (psPortCtrl->sRHPortDev.pUDev == NULL)
    {
        LOG_D("%s ERROR: udev not found", __func__);
        goto exit_nu_open_pipe;
    }

    psPortDev = GetPortDevFromPipe(pipe);

    if ((psPortDev == NULL) || (psPortDev->pUDev == NULL))
    {
        //allocate new dev for hub device
        psPortDev = AllocateNewUDev(psPortCtrl);

        if (psPortDev == RT_NULL)
        {
            LOG_D("nu_open_pipe ERROR: udev allocate failed");
            goto exit_nu_open_pipe;
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
    }
    else
    {
        int  pksz;
        EP_INFO_T *psEPInfo = GetFreePipe(psPortCtrl, psPortDev, &pipe->pipe_index);
        if (psEPInfo == RT_NULL)
        {
            LOG_D("%s ERROR: get free pipe failed", __func__);
            goto exit_nu_open_pipe;
        }

        psEPInfo->bEndpointAddress = pipe->ep.bEndpointAddress;
        psEPInfo->bmAttributes = pipe->ep.bmAttributes;

        pksz = pipe->ep.wMaxPacketSize;
        pksz = (pksz & 0x07ff) * (1 + ((pksz >> 11) & 3));
        psEPInfo->wMaxPacketSize = pksz;

        psEPInfo->bInterval = pipe->ep.bInterval;
        psEPInfo->hw_pipe = NULL;
        psEPInfo->bToggle = 0;
    }


    return RT_EOK;

exit_nu_open_pipe:

    return -RT_ERROR;
}

static rt_err_t nu_close_pipe(upipe_t pipe)
{
    S_NU_RH_PORT_CTRL *psPortCtrl;
    S_NU_PORT_DEV *psPortDev;

    psPortCtrl = GetRHPortControlFromPipe(pipe);
    if (psPortCtrl == RT_NULL)
    {
        return -RT_EIO;
    }

    psPortDev = GetPortDevFromPipe(pipe);

    //For ep0 control transfer
    if ((pipe->ep.bEndpointAddress & 0x7F) == 0)
    {
        if ((psPortDev) && (psPortDev->bRHParent == FALSE) && (psPortDev->bEnumDone == TRUE))
        {
            if (psPortDev->pUDev)
            {
                int i;
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
    int timeouts)
{
    uint32_t  xfer_len = 0;
    int    ret;

    ret = usbh_ctrl_xfer(psPortDev->pUDev, psSetup->request_type, psSetup->bRequest, psSetup->wValue, psSetup->wIndex, psSetup->wLength, buffer, &xfer_len, timeouts * 10);
    if (ret < 0)
    {
        LOG_D("nu_ctrl_xfer ERROR: xfer failed %d");
        return ret;
    }

    if (xfer_len != psSetup->wLength)
    {
        LOG_D("nu_ctrl_xfer ERROR: xfer length %d %d", psSetup->wLength, xfer_len);
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
    int timeouts)
{
#define TIMEOUT_RETRY 3

    int retry = TIMEOUT_RETRY;
    int ret = usbh_bulk_xfer(psUTR);
    if (ret < 0)
    {
        rt_kprintf("usbh_bulk_xfer %x\n", ret);
        return ret;
    }

    while (retry > 0)
    {
        if (rt_completion_wait(&(psPortDev->utr_completion), timeouts) != 0)
        {
            rt_uint32_t level;

            rt_kprintf("Request %d Timeout in %d ms!!\n", psUTR->data_len, timeouts);

            rt_completion_init(&(psPortDev->utr_completion));
            rt_thread_mdelay(1);

            // Workaround: To fix timeout case, this way is traveling qh's linking-list again.
            level = rt_hw_interrupt_disable();
            extern void scan_asynchronous_list();
            extern void iaad_remove_qh();
            scan_asynchronous_list();
            iaad_remove_qh();
            rt_hw_interrupt_enable(level);
        }
        else
            break;

        retry--;
    }

    return (retry > 0) ? 0 : -1;
}

static int nu_int_xfer(
    upipe_t pipe,
    S_NU_PORT_DEV *psPortDev,
    UTR_T *psUTR,
    int timeouts)
{
    int ret;

    while (1)
    {
        ret = usbh_int_xfer(psUTR);
        if (ret < 0)
            return ret;

        if (rt_completion_wait(&(psPortDev->utr_completion), timeouts) != 0)
        {
            LOG_D("Request %08x Timeout in %d ms", psUTR, timeouts);
            usbh_quit_utr(psUTR);

            rt_completion_init(&(psPortDev->utr_completion));
            rt_thread_mdelay(1);
        }
        else
        {

            LOG_D("Transferring done %08x", psUTR);
            usbh_quit_utr(psUTR);
            break;
        }
    }

    return 0;
}

static void xfer_done_cb(UTR_T *psUTR)
{
    S_NU_PORT_DEV *psPortDev = (S_NU_PORT_DEV *)psUTR->context;

    //transfer done, signal utr_completion
    rt_completion_done(&(psPortDev->utr_completion));
}

static int nu_pipe_xfer(upipe_t pipe, rt_uint8_t token, void *buffer, int nbytes, int timeouts)
{
    S_NU_RH_PORT_CTRL *psPortCtrl;
    S_NU_PORT_DEV *psPortDev;
    UTR_T *psUTR = NULL;
    int i32XferLen = -1;

    void *buffer_nonch = buffer;

    NU_USBHOST_LOCK();

    psPortCtrl = GetRHPortControlFromPipe(pipe);
    if (psPortCtrl == RT_NULL)
    {
        goto exit_nu_pipe_xfer;
    }

    psPortDev = GetPortDevFromPipe(pipe);
    if (psPortDev->pUDev == NULL)
    {
        LOG_D("nu_pipe_xfer ERROR: udev not found");
        goto exit_nu_pipe_xfer;
    }

    //ctrl xfer
    if (pipe->ep.bmAttributes == USB_EP_ATTR_CONTROL)
    {
        int ret;

        if (token == USBH_PID_SETUP)
        {
            struct urequest *psSetup = (struct urequest *)buffer_nonch;
            RT_ASSERT(buffer_nonch != RT_NULL);
            psPortCtrl->asHubPortDev->u32SentLength[pipe->pipe_index] = 0;

            /* Read data from USB device. */
            if (psSetup->request_type & USB_REQ_TYPE_DIR_IN)
            {
                //Store setup request
                rt_memcpy(&psPortCtrl->asHubPortDev->asSetupReq[pipe->pipe_index], psSetup, sizeof(struct urequest));
            }
            else
            {
                /* Write data to USB device. */
                //Trigger USBHostLib Ctrl_Xfer
                ret = nu_ctrl_xfer(psPortDev, psSetup, NULL, timeouts);
                if (ret != psSetup->wLength)
                    goto exit_nu_pipe_xfer;
            }
        }
        else
        {
            //token == USBH_PID_DATA
            if (buffer_nonch && ((pipe->ep.bEndpointAddress & USB_DIR_MASK) == USB_DIR_IN))
            {
                struct urequest *psSetup = &psPortCtrl->asHubPortDev->asSetupReq[pipe->pipe_index];

                /* Read data from USB device. */
                //Trigger USBHostLib Ctril_Xfer
                /*
                * Workaround: HCD driver can readback all bytes of setup.wLength, but not support single packet transferring.
                */
                if (psPortCtrl->asHubPortDev->u32SentLength[pipe->pipe_index] == 0)
                {
                    ret = nu_ctrl_xfer(psPortDev, psSetup, buffer_nonch, timeouts);
                    psPortCtrl->asHubPortDev->u32SentLength[pipe->pipe_index] = ret;
                }
                else
                {
                    if (psPortCtrl->asHubPortDev->u32SentLength[pipe->pipe_index] < nbytes)
                    {
                        ret = 0;
                    }
                    else
                    {
                        psPortCtrl->asHubPortDev->u32SentLength[pipe->pipe_index] -= nbytes;
                        ret = nbytes;
                    }
                }
                if (ret <= 0)
                    goto exit_nu_pipe_xfer;
            }
            else
            {
                LOG_D("%d == USBH_PID_DATA, nil buf-%d", token, nbytes);
            }

        } //else
        i32XferLen = nbytes;
        goto exit_nu_pipe_xfer;
    } // if ( pipe->ep.bmAttributes == USB_EP_ATTR_CONTROL )
    else
    {

        psUTR = alloc_utr(psPortDev->pUDev);

        if (!psUTR)
        {
            LOG_D("nu_pipe_xfer ERROR: unable alloc UTR");
            goto exit_nu_pipe_xfer;
        }

        psUTR->ep = psPortDev->apsEPInfo[pipe->pipe_index];
        psUTR->buff = buffer_nonch;
        psUTR->data_len = nbytes;
        psUTR->xfer_len = 0;
        psUTR->func = xfer_done_cb;
        psUTR->context = psPortDev;
        psUTR->bIsTransferDone = 0;
        psUTR->status = 0;

        //others xfer
        rt_completion_init(&(psPortDev->utr_completion));

        if (pipe->ep.bmAttributes == USB_EP_ATTR_BULK)
        {
            if (nu_bulk_xfer(psPortDev, psUTR, timeouts) < 0)
            {
                LOG_D("nu_pipe_xfer ERROR: bulk transfer failed");
                goto failreport_nu_pipe_xfer;
            }
        }
        else if (pipe->ep.bmAttributes == USB_EP_ATTR_INT)
        {
            if (nu_int_xfer(pipe, psPortDev, psUTR, timeouts) < 0)
            {
                LOG_D("nu_pipe_xfer ERROR: int transfer failed");
                //goto exit_nu_pipe_xfer;
            }
            else
            {
                i32XferLen = nbytes;
            }
            goto exit_nu_pipe_xfer;
        }
        else if (pipe->ep.bmAttributes == USB_EP_ATTR_ISOC)
        {
            //TODO: ISO transfer
            LOG_D("nu_pipe_xfer ERROR: isoc transfer not support");
            goto exit_nu_pipe_xfer;
        }

    } //else

failreport_nu_pipe_xfer:

    if (psUTR->bIsTransferDone == 0)
    {
        //Timeout
        LOG_D("nu_pipe_xfer ERROR: timeout");
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

exit_nu_pipe_xfer:

    //Call callback
    if (pipe->callback != RT_NULL)
    {
        pipe->callback(pipe);
    }

    if (psUTR)
        free_utr(psUTR);

    NU_USBHOST_UNLOCK();

    return i32XferLen;
}

/* Polling USB root hub status task */
static void nu_usbh_rh_thread_entry(void *parameter)
{
    while (1)
    {
        NU_USBHOST_LOCK();
        usbh_polling_root_hubs();
        NU_USBHOST_UNLOCK();

        rt_thread_mdelay(NU_USBHOST_HUB_POLLING_INTERVAL);
    }
}

static void nu_hcd_connect_callback(
    struct udev_t *udev,
    int param)
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
        LOG_D("ERROR: port connect slot is full");
        return;
    }

    port_index = i + 1;
    psPortCtrl->sRHPortDev.pUDev = udev;
    psPortCtrl->sRHPortDev.bRHParent = TRUE;

    LOG_D("usb connected");

    if (udev->speed == SPEED_HIGH)
        rt_usbh_root_hub_connect_handler(&s_sUSBHDev.uhcd, port_index, RT_TRUE);
    else
        rt_usbh_root_hub_connect_handler(&s_sUSBHDev.uhcd, port_index, RT_FALSE);
}

static void nu_hcd_disconnect_callback(
    struct udev_t *udev,
    int param)
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
        LOG_D("ERROR: udev not found");
        return;
    }

    port_index = i + 1;

    for (i = 0; i < NU_MAX_USBH_PIPE; i++)
    {
        if (psPortCtrl->sRHPortDev.apsEPInfo[i] != NULL)
        {
            usbh_quit_xfer(psPortCtrl->sRHPortDev.pUDev, psPortCtrl->sRHPortDev.apsEPInfo[i]);
        }
    }

    psPortCtrl->sRHPortDev.pUDev = NULL;

    LOG_D("usb disconnect");

    rt_usbh_root_hub_disconnect_handler(&s_sUSBHDev.uhcd, port_index);
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
    struct nu_usbh_dev *pNuUSBHDev = (struct nu_usbh_dev *)device;

    usbh_core_init();

    //install connect/disconnect callback
    usbh_install_conn_callback(nu_hcd_connect_callback, nu_hcd_disconnect_callback);

    //create thread for polling usbh port status
    /* create usb hub thread */
    pNuUSBHDev->polling_thread = rt_thread_create("usbh_drv", nu_usbh_rh_thread_entry, RT_NULL,
                                 NU_USBH_THREAD_STACK_SIZE, 8, 20);
    RT_ASSERT(pNuUSBHDev->polling_thread != RT_NULL);

    /* startup usb host thread */
    rt_thread_startup(pNuUSBHDev->polling_thread);

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

#if defined(RT_USING_PM)

/* device pm suspend() entry. */
static int usbhost_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    rt_err_t result;

    struct nu_usbh_dev *pNuUSBHDev = (struct nu_usbh_dev *)device;

    RT_ASSERT(pNuUSBHDev != RT_NULL);
    switch (mode)
    {
    case PM_SLEEP_MODE_LIGHT:
    case PM_SLEEP_MODE_DEEP:

        RT_SCHED_CTX(pNuUSBHDev->polling_thread).stat = RT_THREAD_READY;
        result = rt_thread_suspend(pNuUSBHDev->polling_thread);
        RT_ASSERT(result == RT_EOK);

        break;

    default:
        break;
    }

    return (int)RT_EOK;
}

/* device pm resume() entry. */
static void usbhost_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    rt_err_t result;
    struct nu_usbh_dev *pNuUSBHDev = (struct nu_usbh_dev *)device;
    RT_ASSERT(pNuUSBHDev != RT_NULL);

    switch (mode)
    {
    case PM_SLEEP_MODE_LIGHT:
    case PM_SLEEP_MODE_DEEP:
        result = rt_thread_resume(pNuUSBHDev->polling_thread);
        RT_ASSERT(result == RT_EOK);
        break;

    default:
        break;
    }
}

static struct rt_device_pm_ops device_pm_ops =
{
    .suspend = usbhost_pm_suspend,
    .resume = usbhost_pm_resume,
    .frequency_change = RT_NULL
};
#endif

int nu_usbh_register(void)
{
    rt_err_t res;
    uhcd_t psUHCD;

    psUHCD = (uhcd_t)&s_sUSBHDev.uhcd;

    psUHCD->parent.type       = RT_Device_Class_USBHost;
    psUHCD->parent.init       = nu_hcd_init;
    psUHCD->parent.user_data  = &s_sUSBHDev;

    psUHCD->ops               = &nu_uhcd_ops;
    psUHCD->num_ports         = NU_MAX_USBH_PORT;

#if !defined(BSP_USING_HSOTG)
    {
        uint32_t u32RegLockBackup;

        u32RegLockBackup = SYS_IsRegLocked();
        if (u32RegLockBackup)
            SYS_UnlockReg();

#if defined(BSP_USING_HSUSBH)
        /* Set USB Host role */
        SYS->USBPHY = (SYS->USBPHY & ~SYS_USBPHY_HSUSBROLE_Msk) | (0x1u << SYS_USBPHY_HSUSBROLE_Pos);
        SYS->USBPHY |= SYS_USBPHY_HSUSBEN_Msk | SYS_USBPHY_SBO_Msk;
        rt_thread_delay(20);
        SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;
#endif

#if defined(BSP_USING_USBH)
        /* Set USB Host role */
        SYS->USBPHY = (SYS->USBPHY & ~SYS_USBPHY_USBROLE_Msk) | (0x1u << SYS_USBPHY_USBROLE_Pos);
        SYS->USBPHY |= SYS_USBPHY_USBEN_Msk | SYS_USBPHY_SBO_Msk ;
#endif

        if (u32RegLockBackup)
            SYS_LockReg();
    }
#endif


    NU_USBHOST_MUTEX_INIT();

    res = rt_device_register(&psUHCD->parent, "usbh", RT_DEVICE_FLAG_DEACTIVATE);
    RT_ASSERT(res == RT_EOK);

    /*initialize the usb host function */
    res = rt_usb_host_init("usbh");
    RT_ASSERT(res == RT_EOK);

#if defined(RT_USING_PM)
    rt_pm_device_register(&psUHCD->parent, &device_pm_ops);
#endif

    return 0;
}
INIT_APP_EXPORT(nu_usbh_register);

#endif
