/*
********************************************************************************************************************
*                                              usb host driver
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : mscTransport.c
*
* Author        : javen
*
* Version       : 2.0
*
* Date          : 2010.03.02
*
* Description   :
*
* History       :
*
********************************************************************************************************************
*/
#include  "usb_os_platform.h"
#include  "error.h"
#include  "usb_host_common.h"
#include  "urb.h"
#include  "usb_gen_hub.h"
#include  "usb_msc_i.h"
#include  "mscTransport.h"
#include  "Scsi2.h"

/*
*******************************************************************************
*                     mscUrbCallBack
*
* Description:
*    urb call back函数
*
* Parameters:
*    urb : input. 需要提交的URB
*
* Return value:
*    无
*
* note:
*
*
*******************************************************************************
*/
static void mscUrbCallBack(struct urb *urb)
{
    hal_sem_t urb_done = (hal_sem_t)urb->context;

    if (urb_done != NULL)
    {
        hal_sem_post(urb_done);
    }
    else
    {
        hal_log_err("ERR: mscUrbCallBack: urb_done == NULL");
    }
}

/*
*******************************************************************************
*                     mscTimeOut
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
*
*
*******************************************************************************
*/
static void mscTimeOut(void *parg)
{
    __mscDev_t *mscDev = (__mscDev_t *)parg;

    if (mscDev == NULL)
    {
        hal_log_err("ERR: mscTimeOut: mscDev == NULL");
        return;
    }

    hal_log_info("ERR: mscTimeOut: CurrentUrb = %x", (unsigned int)mscDev->CurrentUrb);

    if (mscDev->ScsiCmnd)
    {
        hal_log_err("ERR: mscTimeOut, Cmnd = %x, Timeout = %dms, retries = %d, allowed = %d",
                   ((__u8 *)(mscDev->ScsiCmnd->cmnd.CommandBlock))[0],
                   mscDev->ScsiCmnd->cmnd.Timeout,
                   mscDev->ScsiCmnd->retries,
                   mscDev->ScsiCmnd->allowed);
    }

    if (mscDev->busy)
    {
        usb_unlink_urb(mscDev->CurrentUrb);
        mscDev->CurrentUrb->status = -ETIMEDOUT;
    }

    return;
}

/*
*******************************************************************************
*                     mscUsbTransport
*
* Description:
*    发送URB
*
* Parameters:
*    mscDev   :  input. 目标设备
*    TimeOut  :  input. 超时时间
*
* Return value:
*    返回URB状态
*
* note:
*
*
*******************************************************************************
*/
static int mscUsbTransport(__mscDev_t *mscDev, unsigned int TimeOut)
{
    int ret = 0;
    __u8 err = 0;

    if (mscDev == NULL)
    {
        hal_log_err("ERR: mscUSBTransport: input error, mscDev = %x", mscDev);
        return -EINVAL;
    }

    if (mscDev->state != MSC_DEV_ONLINE)
    {
        hal_log_err("ERR: mscUSBTransport: Can't transport for device is not online");
        return -EINVAL;
    }

    /* fill URB */
        mscDev->CurrentUrb->context       = (void *)mscDev->UrbWait;
        mscDev->CurrentUrb->actual_length = 0;
        mscDev->CurrentUrb->error_count   = 0;
        mscDev->CurrentUrb->status        = 0;
        /* 设置buffer传输方式, 如果使用msc的buff，则不使用DMA，需要palloc分配内存 */
        mscDev->CurrentUrb->transfer_flags = URB_ASYNC_UNLINK;
    //    mscDev->CurrentUrb->transfer_flags = URB_ASYNC_UNLINK | URB_NO_SETUP_DMA_MAP;
    
    //    if (mscDev->CurrentUrb->transfer_buffer == mscDev->iobuf)
    //    {
    //        mscDev->CurrentUrb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
    //    }
    

    mscDev->CurrentUrb->transfer_dma = 0;
    mscDev->CurrentUrb->setup_dma    = 0;

    /* create timer */
    if (TimeOut)
    {
        // unsigned long time_interval = rt_tick_from_millisecond(TimeOut);
        mscDev->TimerHdle = osal_timer_create("mscTime_timer",
                               (timeout_func)mscTimeOut,
                               (void *)mscDev,
                               TimeOut / (1000 / CONFIG_HZ),
                               OSAL_TIMER_FLAG_ONE_SHOT);
        if (mscDev->TimerHdle == NULL)
        {
            hal_log_err("PANIC : create timer for urb false\n");
            return -1;
        }
    }
    /* set mscDev busy */
    mscDev->busy = 1;
    /* submit urb */
    ret = usb_submit_urb(mscDev->CurrentUrb, 0);
    if (ret != 0)
    {
        hal_log_err("ERR: submit urb failed. ret = %d", ret);
        if (mscDev->TimerHdle)
        {
            osal_timer_delete(mscDev->TimerHdle);
            mscDev->TimerHdle = NULL;
        }

        mscDev->busy = 0;
        return -EINVAL;
    }

    /* start timer */
    if (mscDev->TimerHdle)
    {
        osal_timer_start(mscDev->TimerHdle);
    }

    /* wait urb done */
    hal_sem_timedwait(mscDev->UrbWait, TimeOut / (1000 / CONFIG_HZ));
    /* urb is done, then set mscDev free */
    mscDev->busy = 0;

    /* kill timer */
    if (mscDev->TimerHdle)
    {
        osal_timer_stop(mscDev->TimerHdle);
        osal_timer_delete(mscDev->TimerHdle);
        mscDev->TimerHdle = NULL;
    }

    return mscDev->CurrentUrb->status;
}

/*
*******************************************************************************
*                     mscCtrlMsg
*
* Description:
*    USB控制消息函数
*
* Parameters:
*    mscDev         :  input.  目标设备
*    Pipe           :  input.  URB通道
*    Request        :  input.  请求类型
*    RequestType    :  input.  请求方向(读/写)和请求类型
*    Value          :  input.  值
*    Index          :  input.  索引
*    Buffer         :  input.  输入/输出缓存区
*    BufferLen      :  input.  输入/输出缓存区大小
*    TimeOut        :  input.  URB超时时间
*
* Return value:
*    返回URB状态
*
* note:
*
*
*******************************************************************************
*/
static int mscSendCtrlReq(__mscDev_t *mscDev,
                            int Pipe,
                            __u8  Request,
                            __u8  RequestType,
                            __u16 Value,
                            __u16 Index,
                            void *Buffer,
                            __u16 BufferLen,
                            unsigned int TimeOut)
{
    if (mscDev == NULL)
    {
        hal_log_err("ERR: USBStorageCtrlMsg : mscDev = %x", mscDev);
        return USB_ERR_BAD_ARGUMENTS;
    }

      /* 填充控制请求结构体 */
      mscDev->CtrlReq->bRequest     = Request;                 // 请求类型
      mscDev->CtrlReq->bRequestType = RequestType;             // 请求方向(读/写)和请求类型
      mscDev->CtrlReq->wValue       = cpu_to_le16(Value);       // 值, 使用小端字节序
      mscDev->CtrlReq->wIndex       = cpu_to_le16(Index);       // 索引, 使用小端字节序
      mscDev->CtrlReq->wLength      = cpu_to_le16(BufferLen);   // 缓冲区大小, 使用小端字节序
      /* 填充并提交Urb */
      memset(mscDev->CurrentUrb, 0x00, sizeof(struct urb));
      usb_fill_control_urb(mscDev->CurrentUrb,
                           mscDev->pusb_dev,
                           Pipe,
                           (unsigned char *)mscDev->CtrlReq,
                           Buffer,
                           BufferLen,
                           mscUrbCallBack,
                           NULL);
      /* 发送请求并等待响应 */
      return mscUsbTransport(mscDev, TimeOut);
}

/*
*******************************************************************************
*                     mscClearHalt
*
* Description:
*    清除端点状态
*
* Parameters:
*    mscDev     :  input. 目标设备
*    Pipe       :  input. urb的pipe
*
* Return value:
*    返回URB执行结果
*
* note:
*
*
*******************************************************************************
*/
static int mscClearHalt(__mscDev_t *mscDev, unsigned int Pipe)
{
    int Result = 0;
    unsigned int endp = usb_pipeendpoint(Pipe);

    if (usb_pipein(Pipe))
    {
        endp |= USB_DIR_IN;
    }

    Result = mscSendCtrlReq(mscDev,
                            mscDev->CtrlOut,
                            USB_REQ_CLEAR_FEATURE,
                            USB_RECIP_ENDPOINT,
                            USB_ENDPOINT_HALT,
                            (__u16)endp,
                            NULL,
                            0,
                            USB_STOR_CTRL_MSG_TIME);

    /* reset the endpoint toggle */
    if (Result >= 0)
    {
        usb_settoggle(mscDev->pusb_dev, usb_pipeendpoint(Pipe), usb_pipeout(Pipe), 0);
    }

    if (Result == 0)
    {
        Result = USB_ERR_SUCCESS;
    }
    else
    {
        Result = USB_ERR_UNKOWN_ERROR;
    }

    return Result;
}

/*
*******************************************************************************
*                     AnalyseBlukUrbState
*
* Description:
*    分析Bulk Urb状态
*
* Parameters:
*    mscDev     :  input. 目标设备
*    UrbState   :  input. URB执行状态
*    Pipe       :  input. urb的pipe
*    WantLen    :  input. 原始要求传输数据长度
*    ActLen     :  input. 实际传输数据长度
*
* Return value:
*    返回USB操作结果
*
* note:
*
*
*******************************************************************************
*/
static int AnalyseBulkUrbState(__mscDev_t *mscDev,
                                 int UrbState,
                                 int Pipe,
                                 unsigned int WantLen,
                                 unsigned int ActLen)
{
    switch (UrbState)
    {
        case 0:     /* no error code; did we send all the data? */
            if (WantLen != ActLen)
            {
                hal_log_err("Wrn: short transfer, urb_state(%d), want_len(%d), real_len(%d)",
                           UrbState, WantLen, ActLen);
                return USB_STOR_XFER_SHORT;
            }

            return USB_STOR_XFER_GOOD;

        case -EPIPE:    /* stalled */
            hal_log_err("ERR: ep stalled, need clear feature");

            /* for control endpoints, (used by CB[I]) a stall indicates a failed command */
            if (usb_pipecontrol(Pipe))
            {
                hal_log_err("stall on control pipe, urb_state(%d), want_len(%d), real_len(%d)",
                           UrbState, WantLen, ActLen);
                return USB_STOR_XFER_STALLED;
            }

            /* for other sorts of endpoint, clear the stall */
            if (mscClearHalt(mscDev, Pipe) != USB_ERR_SUCCESS)
            {
                hal_log_err("ERR: mscClearHalt ep failed, urb_state(%d), want_len(%d), real_len(%d)",
                           UrbState, WantLen, ActLen);
                return USB_STOR_XFER_ERROR;
            }

            return USB_STOR_XFER_STALLED;

        /* timeout or excessively long NAK */
        case -ETIMEDOUT:
            hal_log_err("ERR: timeout or NAK, urb_state(%d), want_len(%d), real_len(%d)",
                       UrbState, WantLen, ActLen);
            return USB_STOR_XFER_TIME_OUT;

        /* babble - the device tried to send more than we wanted to read */
        case -EOVERFLOW:
            hal_log_err("ERR: babble, data overflow, urb_state(%d), want_len(%d), real_len(%d)",
                       UrbState, WantLen, ActLen);
            return USB_STOR_XFER_LONG;

        /* the transfer was cancelled by abort, disconnect, or timeout */
        case -ECONNRESET:
            hal_log_err("ERR: transfer cancelled, urb_state(%d), want_len(%d), real_len(%d)",
                       UrbState, WantLen, ActLen);
            return USB_STOR_XFER_ERROR;

        /* short scatter-gather read transfer */
        case -EREMOTEIO:
            hal_log_err("ERR: short read transfer, urb_state(%d), want_len(%d), real_len(%d)",
                       UrbState, WantLen, ActLen);
            return USB_STOR_XFER_SHORT;

        /* abort or disconnect in progress */
        case -EIO:
            hal_log_err("ERR: abort or disconnect in progress, urb_state(%d), want_len(%d), real_len(%d)",
                       UrbState, WantLen, ActLen);
            return USB_STOR_XFER_ERROR;

        default:
            hal_log_err("ERR: unkown urb state, urb_state(%d), want_len(%d), real_len(%d)",
                       UrbState, WantLen, ActLen);
            return USB_STOR_XFER_ERROR;
    }
}

/*
*******************************************************************************
*                     mscSendBlukReq
*
* Description:
*    发送bulk请求
*
* Parameters:
*    mscDev     :  input. 目标设备
*    Pipe       :  input. urb的pipe
*    Buffer     :  input. 数据缓冲区
*    BufferLen  :  input. 数据缓冲区大小
*    ActLen     :  input. 实际传输数据长度
*    TimeOut    :  input. URB超时时间
*
* Return value:
*    返回USB操作结果
*
* note:
*
*
*******************************************************************************
*/
static int mscSendBulkReq(__mscDev_t *mscDev,
                            int Pipe,
                            void *Buffer,
                            unsigned int BufferLen,
                            unsigned int *ActLen,
                            unsigned int TimeOut)
{
    /* fill urb */
    memset(mscDev->CurrentUrb, 0x00, sizeof(struct urb));
    usb_fill_bulk_urb(mscDev->CurrentUrb,
                      mscDev->pusb_dev,
                      Pipe,
                      Buffer,
                      BufferLen,
                      mscUrbCallBack,
                      NULL);
    /* submit urb */
    mscUsbTransport(mscDev, TimeOut);

    if (ActLen)
    {
        *ActLen = (unsigned int)(mscDev->CurrentUrb->actual_length);
    }

    return AnalyseBulkUrbState(mscDev,
                               mscDev->CurrentUrb->status,
                               Pipe,
                               BufferLen,
                               (unsigned int)(mscDev->CurrentUrb->actual_length));
}

/*
*******************************************************************************
*                     GetMaxLun
*
* Description:
*    获取当前设备的最大Lun编号，如果获取失败，则默认设备只有1个Lun
*
* Parameters:
*    mscDev  :  input. 目标设备
*
* Return value:
*    Lun 编号
*
* note:
*
*
*******************************************************************************
*/
unsigned int mscGetMaxLun(__mscDev_t *mscDev)
{
    int ret = 0;
    unsigned int MaxLun = 0;

    if (mscDev == NULL)
    {
        hal_log_err("ERR: GetMaxLun: input error, mscDev = %x", mscDev);
        return 0;
    }

    hal_sem_wait(mscDev->DevLock);
    /* issue the command */
    ret = mscSendCtrlReq(mscDev,
                         mscDev->CtrlIn,
                         USB_BULK_GET_MAX_LUN,
                         USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
                         0,
                         mscDev->InterfaceNo,
                         mscDev->iobuf,
                         1,
                         USB_STOR_CTRL_MSG_TIME);

    if (ret == 0)
    {
        hal_log_info("[msc]: GetMaxLUN successful, max lun is %d", mscDev->iobuf[0]);
        MaxLun = mscDev->iobuf[0];
    }
    else
    {
        hal_log_info("[msc]: GetMaxLUN failed, max lun is zero");
        MaxLun = 0;

        if (ret == -EPIPE)
        {
            mscClearHalt(mscDev, mscDev->BulkIn);
            mscClearHalt(mscDev, mscDev->BulkOut);
        }
    }

    hal_sem_post(mscDev->DevLock);
    return MaxLun;
}

/*
*******************************************************************************
*                     mscBoReset
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
*
*
*******************************************************************************
*/
#if 0
static int mscBoReset(__mscDev_t *mscDev)
{
    int ret = 0;

    if (mscDev == NULL)
    {
        printf("ERR: mscBoReset: input error, mscDev = %x", mscDev);
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* send reset request */
    ret = mscSendCtrlReq(mscDev,
                         mscDev->CtrlOut,
                         USB_BULK_RESET_REQUEST,
                         USB_TYPE_CLASS | USB_RECIP_INTERFACE,
                         0,
                         mscDev->InterfaceNo,
                         NULL,
                         0,
                         USB_STOR_CTRL_MSG_TIME);

    if (ret != USB_ERR_SUCCESS)
    {
        printf("ERR: Soft reset failed 1");
        return ret;
    }

    /* clear ep status */
    ret = mscClearHalt(mscDev, mscDev->BulkIn);

    if (ret != USB_ERR_SUCCESS)
    {
        printf("ERR: Soft reset failed 2");
        return ret;
    }

    ret = mscClearHalt(mscDev, mscDev->BulkOut);

    if (ret != USB_ERR_SUCCESS)
    {
        printf("ERR: Soft reset failed 3");
        return ret;
    }

    return ret;
}
#endif

/*
*******************************************************************************
*                     mscPortReset
*
* Description:
*    重置设备
*
* Parameters:
*    mscDev  :  input. 目标设备
*
* Return value:
*    返回成功或失败
*
* note:
*
*
*******************************************************************************
*/
static int mscPortReset(__mscDev_t *mscDev)
{
    int ret = 0;

    if (mscDev == NULL)
    {
        hal_log_err("ERR: mscPortReset: input error, mscDev = %x", mscDev);
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* device online? */
    if (mscDev->state == MSC_DEV_OFFLINE)
    {
        hal_log_err("ERR: mscPortReset: device is offline");
        return USB_ERR_IO_DEVICE_OFFLINE;
    }

    /* reset a multi-interface device must be wariness */
    if (mscDev->pusb_dev->actconfig->desc.bNumInterfaces != 1)
    {
        hal_log_err("ERR: Refusing to reset a multi-interface device");
        return USB_ERR_IO_DEVICE_BUSY;
    }

    /* reset device */
    ret = usb_reset_device(mscDev->pusb_dev);

    if (ret != 0)
    {
        hal_log_err("ERR: reset device failed");
        return USB_ERR_RESET_POERT_FAILED;
    }

    return USB_ERR_SUCCESS;
}

int mscResetRecovery(__mscDev_t *mscDev)
{
    return mscPortReset(mscDev);
}

/*
*******************************************************************************
*                     mscBoTransport
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
*
*
*******************************************************************************
*/
int mscBoTransport(__mscDev_t *mscDev, __ScsiCmnd_t *ScsiCmnd)
{
    __CBW_t *CBW  = NULL;
    __CSW_t *CSW  = NULL;
    unsigned int ActLen  = 0;
    unsigned int TimeOut = 0;
    unsigned int CSWRepeat = 0;
    int Pipe    = 0;
    int ret     = 0;

    if (mscDev == NULL || ScsiCmnd == NULL)
    {
        hal_log_err("ERR: mscBoTransport: input error, mscDev = %x,ScsiCmnd = %x", mscDev, ScsiCmnd);
        return USB_STOR_TRANSPORT_ERROR;
    }

    /* is scsi command valid */
    if (ScsiCmnd->DataTransferLength)
    {
        switch (ScsiCmnd->cmnd.data_direction)
        {
            case DATA_FROM_DEVICE:
                Pipe = mscDev->BulkIn;
                break;

            case DATA_TO_DEVICE:
                Pipe = mscDev->BulkOut;
                break;

            default:
                Pipe = 0;
                hal_log_err("ERR: data phase do not kwon data direction");
                return USB_STOR_TRANSPORT_ERROR;
        }
    }

    hal_sem_wait(mscDev->DevLock);
    mscDev->ScsiCmnd = ScsiCmnd;
    //----------------------------------------------------
    //  Command Block Transport  (CBW)
    //----------------------------------------------------
    /* build the active CBW */
    CBW = (__CBW_t *)mscDev->iobuf;
    memset(CBW, 0, sizeof(__CBW_t));
    mscDev->Tag++;
    TimeOut = USB_STOR_CBW_CSW_TIME;
    CBW->dCBWSignature          = CBW_SIGNATURE;
    CBW->dCBWTag                = mscDev->Tag;
    CBW->dCBWDataTransferLength = ScsiCmnd->DataTransferLength;
    CBW->bmCBWFlags             = (ScsiCmnd->cmnd.data_direction == DATA_FROM_DEVICE)
                                  ? CBW_FLAGS_DATA_IN : CBW_FLAGS_DATA_OUT;
    CBW->bCBWLUN                = ScsiCmnd->cmnd.dwLun;
    CBW->bCBWCBLength           = ScsiCmnd->cmnd.CBLen;
    memcpy((void *)CBW->CBWCB, ScsiCmnd->cmnd.CommandBlock, CBW->bCBWCBLength);
    /* Command Block Transport */
    ret = mscSendBulkReq(mscDev,
                         mscDev->BulkOut,
                         CBW,
                         sizeof(__CBW_t),
                         NULL,
                         TimeOut);

    if (ret != USB_STOR_XFER_GOOD)
    {
        hal_log_err("ERR: mscBoTransport: Command Block Transport failed, reset");
        mscDev->ResetRecovery(mscDev);
        ret = USB_STOR_TRANSPORT_ERROR;
        goto TransportDone;
    }

    //----------------------------------------------------
    //  Data Transport
    //----------------------------------------------------
    if (ScsiCmnd->DataTransferLength)
    {
        TimeOut = ScsiCmnd->cmnd.Timeout;
        ret = mscSendBulkReq(mscDev,
                             Pipe,
                             ScsiCmnd->buffer,
                             ScsiCmnd->DataTransferLength,
                             &ActLen,
                             TimeOut);

        /* 有些设备在read/write数据时会发生endpoint stall的情况，
        解除stall可能需要进行clear feature操作，所以需要进行重试
        */
        if (ret == USB_STOR_XFER_STALLED)
        {
            __u8  Command = 0;
            Command = ((__u8 *)(ScsiCmnd->cmnd.CommandBlock))[0];

            if (Command == SCSI_READ6 || Command == SCSI_READ10 || Command == SCSI_READ16
                || Command == SCSI_WRITE6 || Command == SCSI_WRITE10 || Command == SCSI_WRITE16)
            {
                hal_log_err("ERR: Command(%x) execute failed, for ep stall, need retry", Command);
                mscDev->ResetRecovery(mscDev);
                ret = USB_STOR_TRANSPORT_ERROR;
                goto TransportDone;
            }
        }

        if (ret == USB_STOR_XFER_ERROR)
        {
            hal_log_err("ERR: mscBoTransport: Data Transport failed, reset");
            mscDev->ResetRecovery(mscDev);
            ret = USB_STOR_TRANSPORT_ERROR;
            goto TransportDone;
        }

        ScsiCmnd->ActualLength = ActLen;
    }

    //----------------------------------------------------
    //  Command Status Transport (CSW)
    //----------------------------------------------------
RETRY_CSW:

    if (ScsiCmnd->DataTransferLength)
    {
        TimeOut = USB_STOR_CBW_CSW_TIME;
    }
    else
    {
        TimeOut = ScsiCmnd->cmnd.Timeout;
    }

    CSW = (__CSW_t *)mscDev->iobuf;
    memset(CSW, 0, sizeof(__CSW_t));
    ret = mscSendBulkReq(mscDev,
                         mscDev->BulkIn,
                         CSW,
                         sizeof(__CSW_t),
                         &ActLen,
                         TimeOut);

    if (ret == USB_STOR_XFER_SHORT && ActLen == 0 && ++CSWRepeat < MAX_BOT_CSW_REPEAT)
    {
        hal_log_err("ERR: Received 0-length CSW, must Receive the CSW again");
        goto RETRY_CSW;
    }

    if (ret == USB_STOR_XFER_STALLED && ++CSWRepeat < MAX_BOT_CSW_REPEAT)
    {
        hal_log_err("ERR: EP stall, must Receive the CSW again");
        goto RETRY_CSW;
    }

    if (ret != USB_STOR_XFER_GOOD)
    {
        hal_log_err("ERR: unkown error happen during receive cmd(%x)'s CSW, must reset",
                   ((__u8 *)(ScsiCmnd->cmnd.CommandBlock))[0]);
        mscDev->ResetRecovery(mscDev);
        ret = USB_STOR_TRANSPORT_ERROR;
        goto TransportDone;
    }

    /* check CSW size */
    if (sizeof(__CSW_t) != ActLen)
    {
        hal_log_err("ERR: Invalid Csw size: (%d, %d), must reset", sizeof(__CSW_t), ActLen);
        mscDev->ResetRecovery(mscDev);
        ret = USB_STOR_TRANSPORT_ERROR;
        goto TransportDone;
    }

    /* check CSW Signature */
    if (CSW->dCSWSignature != CSW_SIGNATURE)
    {
        hal_log_err("ERR: Invalid Csw Signature: %x, must reset", CSW->dCSWSignature);
        mscDev->ResetRecovery(mscDev);
        ret = USB_STOR_TRANSPORT_ERROR;
        goto TransportDone;
    }

    /* check CSW Tags */
    if (CSW->dCSWTag != mscDev->Tag)
    {
        hal_log_err("ERR: Invalid Csw Tags: (%x, %x), must reset", mscDev->Tag, CSW->dCSWTag);
        mscDev->ResetRecovery(mscDev);
        ret = USB_STOR_TRANSPORT_ERROR;
        goto TransportDone;
    }

    /* check CSW Status, command failed, need sense */
    if (CSW->bCSWStatus == 1)
    {
        hal_log_err("WRN: command(%x) failed, need sense", ((__u8 *)(ScsiCmnd->cmnd.CommandBlock))[0]);
        ret = USB_STOR_TRANSPORT_FAILED;
        goto TransportDone;
    }

    /* check CSW Status, Phase Error */
    if (CSW->bCSWStatus == 2)
    {
        hal_log_err("ERR: command Phase Error, must reset");
        ret = USB_STOR_TRANSPORT_ERROR;
        goto TransportDone;
    }

    mscDev->ScsiCmnd = NULL;
    hal_sem_post(mscDev->DevLock);
    return USB_STOR_TRANSPORT_GOOD;
TransportDone:
    mscDev->ScsiCmnd = NULL;
    hal_sem_post(mscDev->DevLock);
    return ret;
}


/*
*******************************************************************************
*                     mscBoStopTransport
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
*
*
*******************************************************************************
*/
int mscBoStopTransport(__mscDev_t *mscDev)
{
    if (mscDev == NULL)
    {
        hal_log_err("ERR: mscBoStopTransport: input error, mscDev = %x", mscDev);
        return USB_ERR_BAD_ARGUMENTS;
    }

    if (mscDev->TimerHdle)
    {
        osal_timer_stop(mscDev->TimerHdle);
        osal_timer_delete(mscDev->TimerHdle);
        mscDev->TimerHdle = NULL;
    }

    if (mscDev->busy)
    {
        usb_unlink_urb(mscDev->CurrentUrb);
        mscDev->CurrentUrb->status = -ESHUTDOWN;
    }

    return USB_ERR_SUCCESS;
}



