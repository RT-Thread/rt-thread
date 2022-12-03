/*
********************************************************************************
*                                USB Hid Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  HidTransport.c
*
* Author        :  Javen
*
* Date          :  2010/06/02
*
* Description   :  Hid 传输
*
* Others        :  NULL
*
* History:
*       <time>          <author>     <version >     <desc>
*      2010.06.02       Javen           1.0         build this file
*
********************************************************************************
*/

//#include  "usb_host_config.h"
//#include  "usb_host_base_types.h"
#include  "usb_os_platform.h"
#include  "error.h"

#include  "usb_host_common.h"
#include  "urb.h"
#include  "usb_gen_hub.h"

#include  "HidSpec.h"
#include  "Hid_i.h"
#include  "HidProtocol.h"
#include  "HidTransport.h"

/*
*******************************************************************************
*                     HidTransportDone
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
static void HidTransportDone(struct urb *urb)
{
    hal_sem_t urb_done = (hal_sem_t)urb->context;

    if(urb_done){
        hal_sem_post(urb_done);
    }else{
        hal_log_err("ERR: mscUrbCallBack: urb_done == NULL\n");
    }
}

/*
*******************************************************************************
*                     HidUsbTransport
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
static int HidUsbTransport(HidDev_t *HidDev)
{
    int ret = 0;
    unsigned char err = 0;

    if(HidDev == NULL){
        hal_log_err("ERR: HidUsbTransport: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    if(HidDev->State != HID_DEV_ONLINE){
        hal_log_err("ERR: mscUSBTransport: Can't transport for device is not online\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* fill URB */
    HidDev->CurrentUrb->context       = (void *)HidDev->UrbWait;
    HidDev->CurrentUrb->actual_length = 0;
    HidDev->CurrentUrb->error_count   = 0;
    HidDev->CurrentUrb->status        = 0;
    HidDev->CurrentUrb->transfer_dma  = 0;
    HidDev->CurrentUrb->setup_dma     = 0;

    /* set HidDev busy */
    HidDev->busy = 1;

    /* submit urb */
    ret = usb_submit_urb(HidDev->CurrentUrb, 0);
    if(ret == 0){
        /* nothing to do */
    }else if(ret == -ENODEV){
        hal_log_err("ERR: device is not present, CurrentUrb = %d\n", HidDev->CurrentUrb);
        HidDev->busy = 0;

        return USB_ERR_IO_DEVICE_OFFLINE;
    }else{
        hal_log_err("ERR: submit urb failed. ret = %d, CurrentUrb = %d\n", ret, HidDev->CurrentUrb);
        HidDev->busy = 0;

        return USB_ERR_COMMAND_SEND_FAILED;
    }

    /* wait urb done */
//  USB_OS_SemPend(HidDev->UrbWait, 0, &err);
    hal_sem_wait(HidDev->UrbWait);

    /* urb is done, then set mscDev free */
    HidDev->busy = 0;

    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     HidSoftReset
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
int HidSoftReset(HidDev_t *HidDev)
{
    if(HidDev == NULL){
        hal_log_err("ERR: HidSoftReset: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* device online? */
    if(HidDev->State == HID_DEV_OFFLINE){
        hal_log_err("ERR: HidPortReset: device is offline\n");
        return USB_ERR_IO_DEVICE_OFFLINE;
    }

    return HidSetIlde(HidDev, HidDev->InterfaceNo, 0, 0);
}

/*
*******************************************************************************
*                     HidPortReset
*
* Description:
*    reset 设备
*
* Parameters:
*    mscDev  :  input. 目标设备
*
* Return value:
*    返回成功或者失败
*
* note:
*
*
*******************************************************************************
*/
static int HidPortReset(HidDev_t *HidDev)
{
    int ret = 0;

    if(HidDev == NULL){
        hal_log_err("ERR: HidPortReset: input error, mscDev = %x\n", HidDev);
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* device online? */
    if(HidDev->State == HID_DEV_OFFLINE){
        hal_log_err("ERR: HidPortReset: device is offline\n");
        return USB_ERR_IO_DEVICE_OFFLINE;
    }

    /* reset a multi-interface device must be wariness */
    if(HidDev->pusb_dev->actconfig->desc.bNumInterfaces != 1){
        hal_log_err("ERR: Refusing to reset a multi-interface device\n");
        return USB_ERR_IO_DEVICE_BUSY;
    }

    /* reset device */
    ret = usb_reset_device(HidDev->pusb_dev);
    if(ret != 0){
        hal_log_err("ERR: reset device failed\n");
        return USB_ERR_RESET_POERT_FAILED;
    }

    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     HidResetRecovery
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
int HidResetRecovery(HidDev_t *HidDev)
{
    int ret = 0;

    ret = HidPortReset(HidDev);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: HidPortReset failed\n");
        return USB_ERR_RESET_POERT_FAILED;
    }

    ret = HidSoftReset(HidDev);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: HidSoftReset failed\n");
        return USB_ERR_RESET_POERT_FAILED;
    }

    return USB_ERR_SUCCESS;
}


/*
*******************************************************************************
*                     HidTransport
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
#if 0 /* reset 多次 */
int HidTransport(HidDev_t *HidDev, HidRequest_t *HidReq)
{
    int ret = 0;
    __u32 retries = 3;

    /* fill urb */
    usb_fill_int_urb( HidDev->CurrentUrb,
                      HidDev->pusb_dev,
                      HidDev->IntIn,
                      HidReq->buffer,
                      HidReq->DataTransferLength,
                      HidTransportDone,
                      NULL,
                      HidDev->EpInterval);

HidRetry:
    /* summit urb */
    ret = HidUsbTransport(HidDev);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: HidUsbTransport failed\n");
        return USB_HID_TRANSPORT_PIPE_HALT;
    }

    if(HidDev->CurrentUrb->status == -ESHUTDOWN){
        hal_log_err("ERR: device is shut down\n");
        return USB_HID_TRANSPORT_CANCEL_CMD;
    }

    if(HidDev->CurrentUrb->status != 0 && retries--){
        hal_log_err("ERR: HidTransport failed(%d), need retry %d\n",
                    HidDev->CurrentUrb->status, retries);
        ret = HidDev->ResetRecovery(HidDev);
        if(ret != USB_ERR_SUCCESS){
            hal_log_err("ERR: HidResetRecovery failed\n");
            return USB_HID_TRANSPORT_DEVICE_DISCONNECT;
        }

        goto HidRetry;
    }

    /* retry的最后一次成功，不算其中 */
    if(retries == 0 && HidDev->CurrentUrb->status != 0){
        hal_log_err("ERR: HidTransport failed\n");
        return USB_HID_TRANSPORT_DEVICE_DISCONNECT;
    }

    return USB_HID_TRANSPORT_SUCCESS;
}
#else  /* 不reset */
int HidTransport(HidDev_t *HidDev, HidRequest_t *HidReq)
{
    int ret = 0;

    /* fill urb */
    usb_fill_int_urb( HidDev->CurrentUrb,
                      HidDev->pusb_dev,
                      HidDev->IntIn,
                      HidReq->buffer,
                      HidReq->DataTransferLength,
                      HidTransportDone,
                      NULL,
                      HidDev->EpInterval);

    /* summit urb */
    ret = HidUsbTransport(HidDev);
    if(ret == USB_ERR_SUCCESS){
        /* nothing to do */
    }else if(ret == USB_ERR_IO_DEVICE_OFFLINE){
        hal_log_err("ERR: deivce is offline\n");
        return USB_HID_TRANSPORT_DEVICE_DISCONNECT;
    }else{
        hal_log_err("ERR: HidUsbTransport failed, ret = %d\n", ret);
        return USB_HID_TRANSPORT_PIPE_HALT;
    }

    /* check urb status */
    if(HidDev->CurrentUrb->status != 0){
        hal_log_err("ERR: HidTransport failed(%d)\n", HidDev->CurrentUrb->status);

        /* driver取消了本次传输 */
        if(HidDev->CurrentUrb->status == -ESHUTDOWN){
            hal_log_err("ERR: HidTransport: device is shut down\n");
            return USB_HID_TRANSPORT_CANCEL_CMD;
        }

        if(HidDev->State == HID_DEV_OFFLINE){
            hal_log_err("ERR: HidTransport: device is offline\n");
            return USB_HID_TRANSPORT_DEVICE_DISCONNECT;
        }

/*
        ret = HidDev->ResetRecovery(HidDev);
        if(ret != USB_ERR_SUCCESS){
            hal_log_err("ERR: HidResetRecovery failed\n");
            return USB_HID_TRANSPORT_DEVICE_DISCONNECT;
        }
*/
    }

    return USB_HID_TRANSPORT_SUCCESS;
}
#endif

/*
*******************************************************************************
*                     HidStopTransport
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
int HidStopTransport(HidDev_t *HidDev)
{
    if(HidDev == NULL){
        hal_log_err("ERR: HidStopTransport: input error, HidDev = %x\n", HidDev);
        return USB_ERR_BAD_ARGUMENTS;
    }

    if(HidDev->busy){
        usb_unlink_urb(HidDev->CurrentUrb);
        HidDev->CurrentUrb->status = -ESHUTDOWN;
    }

    return USB_ERR_SUCCESS;
}


