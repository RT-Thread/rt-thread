/*
********************************************************************************
*                                USB Hid Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  usbMouse.c
*
* Author        :  Javen
*
* Date          :  2010.06.02
*
* Description   :  USB Mouse
*
* Others        :  NULL
*
* History:
*       <time>      <version >      <author>        <desc>
*      2010.06.02      1.0           Javen          build this file
*
********************************************************************************
*/

//#include  "usb_host_config.h"
//#include  "usb_host_base_types.h"
#include "usb_os_platform.h"
#include "usb_host_common.h"
#include "error.h"
#include "misc_lib.h"
#include "HidSpec.h"
#include "Hid_i.h"
#include "HidFunDrv.h"
#include "UsbMouse.h"
#include "UsbMouse_DriftControl.h"

//---------------------------------------------------------
//   函数定义区
//---------------------------------------------------------
static void usbMouse_StartWork(usbMouse_t *usbMouse);
static void usbMouse_StopWork(usbMouse_t *usbMouse);

/*
*******************************************************************************
*                     usbMouseDone
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
static void usbMouseDone(HidRequest_t *HidReq)
{
    int val = 0;
    usbMouse_t *usbMouse = NULL;

    usbMouse = (usbMouse_t *)HidReq->Extern;
    if(usbMouse == NULL){
        hal_log_err("ERR: usbMouseDone: usbMouse == NULL\n");
        return;
    }

//  UsbThreadWakeUp(usbMouse->MouseThreadSemi);
    if (!hal_sem_getvalue(usbMouse->MouseThreadSemi, &val))
    {
        hal_sem_post(usbMouse->MouseThreadSemi);
    }

    return;
}

/*
*******************************************************************************
*                     usbMouseOpen
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
static USB_OS_HANDLE usbMouseOpen(void *open_arg, uint32_t mode)
{
    usbMouse_t *usbMouse = NULL;

    if(open_arg == NULL){
        hal_log_err("ERR: usbMouseOpen: input error, open_arg = %x\n", open_arg);
        return NULL;
    }

    usbMouse = (usbMouse_t *)open_arg;
    if(usbMouse->Magic != USB_HID_DEV_MAGIC){
        hal_log_err("ERR: usbMouseOpen: BlkDev Magic(%x) is invalid\n", usbMouse->Magic);
        return NULL;
    }

    return (USB_OS_HANDLE)open_arg;
}

/*
*******************************************************************************
*                     usbMouseClose
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    0  ：成功
*   !0  ：失败
*
* note:
*    无
*
*******************************************************************************
*/
static int32_t usbMouseClose(USB_OS_HANDLE hDev)
{
    usbMouse_t *usbMouse = NULL;

    if(hDev == NULL){
        hal_log_err("ERR: usbMouseClose: input error\n");
        return EPDK_FAIL;
    }

    usbMouse = (usbMouse_t *)hDev;
    if(usbMouse->Magic != USB_HID_DEV_MAGIC){
        hal_log_err("ERR: usbMouseClose: BlkDev Magic(%x) is invalid\n", usbMouse->Magic);
        return EPDK_FAIL;
    }

    return EPDK_OK;
}
/*
*******************************************************************************
*                     usbMouseRead
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
static uint32_t usbMouseRead(void * pBuffer, uint32_t blk, uint32_t n, USB_OS_HANDLE hDev)
{
    hal_log_err("ERR: usbMouseRead not support\n");
    return 0;
}

/*
*******************************************************************************
*                     usbMouseWrite
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
static uint32_t usbMouseWrite(const void * pBuffer, uint32_t blk, uint32_t n, USB_OS_HANDLE hDev)
{
    hal_log_err("ERR: usbMouseWrite not support\n");
    return 0;
}

/*
*******************************************************************************
*                     usbMouseIoctl
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
static int32_t usbMouseIoctl(USB_OS_HANDLE hDev, uint32_t Cmd, long Aux, void *pBuffer)
{
    usbMouse_t *usbMouse = NULL;
    HidDev_t *HidDev = NULL;
    unsigned int cup_sr = 0;

    if(hDev == NULL){
        hal_log_err("ERR: usbMouseClose: input error\n");
        return EPDK_FAIL;
    }

    usbMouse = (usbMouse_t *)hDev;
    if(usbMouse->Magic != USB_HID_DEV_MAGIC){
        hal_log_err("ERR: usbMouseClose: BlkDev Magic(%x) is invalid\n", usbMouse->Magic);
        return EPDK_FAIL;
    }

    HidDev = usbMouse->HidDev;
    if(HidDev == NULL){
        hal_log_err("ERR: HidDev == NULL\n");
        return EPDK_FAIL;
    }

    switch(Cmd){
        case USBH_HID_USER_CTRL_CMD_TEST_START:
        {
            hal_log_info("usb mouse test command: start-s\n");
            if(pBuffer == NULL){
                hal_log_err("ERR: Execute usb mouse test cmd START failed, for pBuffer is NULL\n");
                return EPDK_FAIL;
            }

            ENTER_CRITICAL(cup_sr);
            usbMouse->USBHMouseTest = (USBHMouseTest_t *)pBuffer;
            usbMouse->USBMouseTestFlag  = 1;
            EXIT_CRITICAL(cup_sr);

            usbMouse_StartWork(usbMouse);
            hal_log_info("usb mouse test command: start-e\n");
        }
        break;

        case USBH_HID_USER_CTRL_CMD_TEST_STOP:
            hal_log_info("usb mouse test command: stop-s\n");

            if(usbMouse->USBMouseTestFlag){
                ENTER_CRITICAL(cup_sr);
                usbMouse->USBHMouseTest     = NULL;
                usbMouse->USBMouseTestFlag  = 0;
                EXIT_CRITICAL(cup_sr);

                usbMouse_StopWork(usbMouse);
            }else{
                hal_log_err("ERR: usb mouse test, can not stop test, for have not start test\n");
                return EPDK_FAIL;
            }

            hal_log_info("usb mouse test command: stop-e\n");
        break;

        case USBH_HID_USER_CTRL_CMD_REG:
            usbMouse->CallBack = (USBHMouse_CallBack)esKRNL_GetCallBack((__pCBK_t)(pBuffer));
            if(usbMouse->CallBack == NULL){
                hal_log_err("ERR: usb mouse CallBack is NULL\n");
                return EPDK_FAIL;
            }

            usbMouse_StartWork(usbMouse);
        break;

        case USBH_HID_USER_CTRL_CMD_UNREG:
            usbMouse->CallBack = NULL;
            usbMouse_StopWork(usbMouse);
        break;

        default:
            hal_log_err("ERR: unkown cmd(%x)\n", Cmd);
            return EPDK_FAIL;
    }

    return EPDK_OK;
}

/*
*******************************************************************************
*                     usbMouse_StartWork
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
static void usbMouse_StartWork(usbMouse_t *usbMouse)
{
    HidDev_t *HidDev = NULL;
    unsigned int cup_sr = 0;
    int ret = 0, val = 0;

    if(usbMouse == NULL){
        hal_log_err("ERR: input error\n");
        return ;
    }

    HidDev = usbMouse->HidDev;
    if(HidDev == NULL){
        hal_log_err("ERR: HidDev == NULL\n");
        return ;
    }

    if(HidDev->State == HID_DEV_OFFLINE){
        hal_log_err("ERR: device is offline, mouse can not start work\n");
        return ;
    }

    /* 清除鼠标的状态 */
    ret = HidDev->SoftReset(HidDev);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: SoftReset failed\n");
        /* 由于有些鼠标不支持SetIdle命令，SoftReset可能会失败，因此不能直接return */
    }

    ENTER_CRITICAL(cup_sr);
    usbMouse->StopWork       = 0;
    usbMouse->HidReq.Result = USB_HID_TRANSPORT_DEVICE_RESET;
    EXIT_CRITICAL(cup_sr);

    //  UsbThreadWakeUp(usbMouse->MouseThreadSemi);
    if (!hal_sem_getvalue(usbMouse->MouseThreadSemi, &val))
    {
        hal_sem_post(usbMouse->MouseThreadSemi);
    }

    return;
}

/*
*******************************************************************************
*                     usbMouse_StopWork
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
static void usbMouse_StopWork(usbMouse_t *usbMouse)
{
    HidDev_t *HidDev = NULL;
    unsigned int cup_sr = 0;

    if(usbMouse == NULL){
        hal_log_err("ERR: input error\n");
        return ;
    }

    HidDev = usbMouse->HidDev;
    if(HidDev == NULL){
        hal_log_err("ERR: HidDev == NULL\n");
        return ;
    }

    ENTER_CRITICAL(cup_sr);
    usbMouse->StopWork = 1;
    EXIT_CRITICAL(cup_sr);

    HidDev->StopTransport(HidDev);

    return ;
}

/*
*******************************************************************************
*                     usbMouse_StopWork
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
static void usbMouseEvent(usbMouse_t *usbMouse)
{
    HidRequest_t *HidReq = NULL;
    int status = 0;
    USBHMouseEvent_t Event;
    int TempData = 0;

    if(usbMouse == NULL){
        hal_log_err("ERR: input error\n");
        return ;
    }

    HidReq = &(usbMouse->HidReq);
    if(HidReq == NULL){
        hal_log_err("ERR: HidReq == NULL\n");
        return ;
    }

    /* check request result */
    switch(HidReq->Result){
        case USB_HID_TRANSPORT_SUCCESS:
            //nothing to do
        break;

        case USB_HID_TRANSPORT_DEVICE_DISCONNECT:
            hal_log_err("ERR: usbMouseEvent: mouse is disconnect\n");
            return;
        //break;

        case USB_HID_TRANSPORT_CANCEL_CMD:
            hal_log_err("ERR: usbMouseEvent: driver cancel command\n");
            return;
        //break;

        default:
            hal_log_err("ERR: unkown result %x\n", HidReq->Result);
            goto next;
    }

    DMSG_MOUSE_TEST("\n");
    DMSG_MOUSE_TEST("[0]:%x, [1]:%x, [2]:%x, [3]:%x, [4]:%x, [5]:%x, [6]:%x\n",
              usbMouse->Data[0], usbMouse->Data[1], usbMouse->Data[2],
              usbMouse->Data[3], usbMouse->Data[4], usbMouse->Data[5],
              usbMouse->Data[6]);

    /* paser usb mouse event */
    memset(&Event, 0, sizeof(USBHMouseEvent_t));

    /* button */
    if(usbMouse->DataDef.Button.BitCount){
        TempData = 0;
        /*这里可能会有问题，里面操作是否会超过TempData所在内存*/
        xGetDataFromBuffer(usbMouse->Data,
                           usbMouse->DataDef.Button.BitOffset,
                           usbMouse->DataDef.Button.BitCount,
                           &TempData);
        memcpy(&Event.Button, &TempData, sizeof(TempData));
    }

    /* X坐标 */
    if(usbMouse->DataDef.X.BitCount){
        TempData = 0;
        xGetDataFromBuffer(usbMouse->Data,
                           usbMouse->DataDef.X.BitOffset,
                           usbMouse->DataDef.X.BitCount,
                           &TempData);
        if(usb_test_bit((usbMouse->DataDef.X.BitCount - 1), (volatile uint32_t *)&TempData)){
            TempData |= (0xffffffff << (usbMouse->DataDef.X.BitCount - 1));
        }

        /* 根据鼠标原厂的建议, 把超过+127设置为+127, 超过-127设置为-127 */
        if(TempData <= -127){
            Event.X = -127;
        }else if(TempData > 127){
            Event.X = 127;
        }else{
            Event.X = TempData;
        }
    }

    /* Y坐标 */
    if(usbMouse->DataDef.Y.BitCount){
        TempData = 0;
        xGetDataFromBuffer(usbMouse->Data,
                           usbMouse->DataDef.Y.BitOffset,
                           usbMouse->DataDef.Y.BitCount,
                           &TempData);
        if(usb_test_bit((usbMouse->DataDef.Y.BitCount - 1), (volatile uint32_t *)&TempData)){
            TempData |= (0xffffffff << (usbMouse->DataDef.Y.BitCount - 1));
        }

        if(TempData <= -127){
            Event.Y = -127;
        }else if(TempData > 127){
            Event.Y = 127;
        }else{
            Event.Y = TempData;
        }
    }

    /* wheel */
    if(usbMouse->DataDef.Wheel.BitCount){
        TempData = 0;
        xGetDataFromBuffer(usbMouse->Data,
                           usbMouse->DataDef.Wheel.BitOffset,
                           usbMouse->DataDef.Wheel.BitCount,
                           &TempData);
        if(usb_test_bit((usbMouse->DataDef.Wheel.BitCount - 1), (volatile uint32_t *)&TempData)){
            TempData |= (0xffffffff << (usbMouse->DataDef.Wheel.BitCount - 1));
        }

        if(TempData <= -127){
            Event.Wheel = -127;
        }else if(TempData > 127){
            Event.Wheel = 127;
        }else{
            Event.Wheel = TempData;
        }
    }

    DMSG_MOUSE_TEST("Button 1 = %d\n", Event.Button.LeftButton);
    DMSG_MOUSE_TEST("Button 2 = %d\n", Event.Button.RightButton);
    DMSG_MOUSE_TEST("Button 3 = %d\n", Event.Button.MiddleButton);
    DMSG_MOUSE_TEST("Button 4 = %d\n", Event.Button.Button4);
    DMSG_MOUSE_TEST("Button 5 = %d\n", Event.Button.Button5);
    DMSG_MOUSE_TEST("Button 6 = %d\n", Event.Button.Button6);
    DMSG_MOUSE_TEST("Button 7 = %d\n", Event.Button.Button7);
    DMSG_MOUSE_TEST("Button 8 = %d\n", Event.Button.Button8);

    DMSG_MOUSE_TEST("X        = %d\n", Event.X);
    DMSG_MOUSE_TEST("Y        = %d\n", Event.Y);
    DMSG_MOUSE_TEST("Wheel    = %d\n", Event.Wheel);
    DMSG_MOUSE_TEST("\n");

    UsbMouse_AddToDriftArray(usbMouse, &Event);

next:
    /* do next hid request */
    status = HidSentRequest(&(usbMouse->HidReq));
    if(status != USB_ERR_SUCCESS){
        hal_log_err("ERR: HidSentRequest failed\n");
        return ;
    }

    return ;
}

/*
*******************************************************************************
*                     usbMouseThd
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
static void usbMouseThread(void *p_arg)
{
    usbMouse_t *usbMouse = (usbMouse_t *)p_arg;

    hal_sem_post(usbMouse->notify_complete);

    while(1){
        //--<1>--杀死线程
//      TryToKillThreadSelf("usbMouseThread");

//      /* sleep */
//      UsbThreadSleep(usbMouse->MouseThreadSemi);
        kthread_stop(usbMouse->MouseThdId);
        hal_sem_wait(usbMouse->MouseThreadSemi);

        if(usbMouse->HidDev->State == HID_DEV_OFFLINE || usbMouse->StopWork){
            /* nothing to do */
            hal_log_info("WRN: Usb mouse is offline(%d) or stop work(%d)\n",
                      usbMouse->HidDev->State, usbMouse->StopWork);
        }else{
            usbMouseEvent(usbMouse);
        }
    }
}

/*
*******************************************************************************
*                     usbMouseProbe
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
int usbMouseProbe(HidDev_t *HidDev)
{
    usbMouse_t *usbMouse = NULL;
    unsigned char err = 0;
    int ret = 0;

    if(HidDev == NULL){
        hal_log_err("ERR: usbMouseProbe: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* 创建一个mouse设备，并且初始化 */
    usbMouse = (usbMouse_t *)hal_malloc(sizeof(usbMouse_t));
    if(usbMouse == NULL){
        hal_log_err("ERR: hal_malloc failed\n");
        return USB_ERR_MALLOC_FAILED;
    }

    memset(usbMouse, 0, sizeof(usbMouse_t));
    usbMouse->HidDev = HidDev;
    HidDev->Extern = usbMouse;

/*
    if(HidDev->pusb_dev->manufacturer){
        strcpy((char *)usbMouse->Vendor, HidDev->pusb_dev->manufacturer);
    }

    if(HidDev->pusb_dev->product){
        strcpy((char *)usbMouse->Product, HidDev->pusb_dev->product);
    }

    if(HidDev->pusb_dev->serial){
        strcpy((char *)usbMouse->Serial, HidDev->pusb_dev->serial);
    }
*/

    /* init mouse data tansfer */
    if(HidDev->OnceTransferLength > USB_HID_MOUSE_DATA_LEN){
        hal_log_err("ERR: HidDev OnceTransferLength is too big.(%d, %d)\n",
                   HidDev->OnceTransferLength, USB_HID_MOUSE_DATA_LEN);
        goto error0;
    }

    /* get button BitOffset and BitCount */
    ret = HidGetInputReport(HidDev,
                            USB_HID_USAGE_PAGE_BUTTON,
                            USB_HID_GENERIC_DESKTOP_PAGE_UNDEFINED,
                            &usbMouse->DataDef.Button.BitOffset,
                            &usbMouse->DataDef.Button.BitCount);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: Get mouse button bitoffset and bitcount field\n");
        goto error0;
    }

    /* get X BitOffset and BitCount */
    ret = HidGetInputReport(HidDev,
                            USB_HID_USAGE_PAGE_GENERIC_DESKTOP_CONTROLS,
                            USB_HID_GENERIC_DESKTOP_PAGE_X,
                            &usbMouse->DataDef.X.BitOffset,
                            &usbMouse->DataDef.X.BitCount);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: Get mouse button bitoffset and bitcount field\n");
        goto error0;
    }

    /* get Y BitOffset and BitCount */
    ret = HidGetInputReport(HidDev,
                            USB_HID_USAGE_PAGE_GENERIC_DESKTOP_CONTROLS,
                            USB_HID_GENERIC_DESKTOP_PAGE_Y,
                            &usbMouse->DataDef.Y.BitOffset,
                            &usbMouse->DataDef.Y.BitCount);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: Get mouse button bitoffset and bitcount field\n");
        goto error0;
    }

    /* get wheel BitOffset and BitCount */
    ret = HidGetInputReport(HidDev,
                            USB_HID_USAGE_PAGE_GENERIC_DESKTOP_CONTROLS,
                            USB_HID_GENERIC_DESKTOP_PAGE_WHEEL,
                            &usbMouse->DataDef.Wheel.BitOffset,
                            &usbMouse->DataDef.Wheel.BitCount);
    if(ret != USB_ERR_SUCCESS){
        hal_log_err("ERR: Get mouse button bitoffset and bitcount field\n");
        goto error0;
    }

    hal_log_info("Button: BitOffset = %d, BitCount = %d\n",
              usbMouse->DataDef.Button.BitOffset, usbMouse->DataDef.Button.BitCount);
    hal_log_info("X: BitOffset = %d, BitCount = %d\n",
              usbMouse->DataDef.X.BitOffset, usbMouse->DataDef.X.BitCount);
    hal_log_info("Y: BitOffset = %d, BitCount = %d\n",
              usbMouse->DataDef.Y.BitOffset, usbMouse->DataDef.Y.BitCount);
    hal_log_info("Wheel: BitOffset = %d, BitCount = %d\n",
              usbMouse->DataDef.Wheel.BitOffset, usbMouse->DataDef.Wheel.BitCount);

    /* init device operation function */
    usbMouse->MouseOp.Open  = usbMouseOpen;
    usbMouse->MouseOp.Close = usbMouseClose;
    usbMouse->MouseOp.Read  = usbMouseRead;
    usbMouse->MouseOp.Write = usbMouseWrite;
    usbMouse->MouseOp.Ioctl = usbMouseIoctl;

    /* init hid request */
    usbMouse->HidReq.HidDev = HidDev;
    usbMouse->HidReq.DataTransferLength = HidDev->OnceTransferLength;
    usbMouse->HidReq.buffer = usbMouse->Data;
    usbMouse->HidReq.Done = usbMouseDone;

    usbMouse->HidReq.Extern = (void *)usbMouse;
    usbMouse->Magic = USB_HID_DEV_MAGIC;

    /* stop mouse */
    usbMouse->StopWork = 1;

    UsbMouse_DriftControl_Init(usbMouse);

    /* create mouse thread */
    usbMouse->MouseThreadSemi = hal_sem_create(0);
    if(usbMouse->MouseThreadSemi == NULL){
        hal_log_err("ERR: hal_sem_create MouseThreadSemi failed\n");
        goto error1;
    }

    usbMouse->notify_complete = hal_sem_create(0);
    if(usbMouse->notify_complete == NULL){
        hal_log_err("ERR: hal_sem_create notify_complete failed\n");
        goto error2;
    }

    usbMouse->MouseThdId = kthread_create((void *)usbMouseThread,
                                            (void *)usbMouse,
                                            "usbMouseThread");
    if(usbMouse->MouseThdId == OS_NO_ERR){
        hal_log_err("ERR: create usbMouseThd failed\n");
        goto error3;
    }

    hal_sem_wait(usbMouse->notify_complete);

    /* 生成设备名 */
    strcpy((char *)usbMouse->ClassName, "HID");
    strcpy((char *)usbMouse->DevName, "USBMOUSE");

    {
        unsigned char temp_buff[32];
        unsigned int temp = 0;

        strcat((char *)usbMouse->DevName, "_");

        /* usb controler number */
//      temp = usbh_get_usbd_port();
        temp = 0;
        memset(temp_buff, 0, 32);
        Usb_uint2str_dec(temp, (char *)temp_buff);
        strcat((char *)usbMouse->DevName, (const char *)temp_buff);

        /* hid device number */
        memset(temp_buff, 0, 32);
        Usb_uint2str_dec(HidDev->DevNo, (char *)temp_buff);
        strcat((char *)usbMouse->DevName, (const char *)temp_buff);
    }

    /* 向系统注册Hid设备 */
    usbMouse->MouseRegHdle = esDEV_DevReg((const char *)usbMouse->ClassName,
                                            (const char *)usbMouse->DevName,
                                            &(usbMouse->MouseOp),
                                            (void *)usbMouse);
    if(usbMouse->MouseRegHdle == NULL){
        hal_log_err("ERR: Mouse USB_OS_DEV_REG failed\n");
        goto error4;
    }

    hal_log_info("\n");
    hal_log_info("*****************************************************************\n");
    hal_log_info("*                                                               *\n");
    hal_log_info("* USB HOST Regist \"%s\" \"%s\" successful\n",
                 usbMouse->ClassName, usbMouse->DevName);
    hal_log_info("*                                                               *\n");
    hal_log_info("*****************************************************************\n");
    hal_log_info("\n");

    /* Notice: 由于新的设备上来以后，系统的设备管理告知应用程序，因此只能由驱动告知应用程序 */
    esKSRV_SendMsg(KMSG_USR_SYSTEM_MOUSE_PLUGIN, KMSG_PRIO_HIGH);

#ifdef USBH_HID_MOUSE_TEST
    usbMouse->StopWork       = 0;
    usbMouse->HidReq.Result = USB_HID_TRANSPORT_DEVICE_RESET;
    UsbThreadWakeUp(usbMouse->MouseThreadSemi);
#endif

    return USB_ERR_SUCCESS;

error4:
    //UsbKillThread(usbMouse->MouseThdId , usbMouse->MouseThreadSemi);
    kthread_stop(usbMouse->MouseThdId);

error3:
    hal_sem_delete(usbMouse->notify_complete);
    usbMouse->notify_complete = NULL;

error2:
    hal_sem_delete(usbMouse->MouseThreadSemi);
    usbMouse->MouseThreadSemi = NULL;

error1:
error0:
    hal_free(usbMouse);
    usbMouse = NULL;

    return USB_ERR_DEVICE_PROBE_FAILED;
}

/*
*******************************************************************************
*                     usbMouseRemove
*
* Description:
*
*
* Parameters:
*
* misc_lib.h
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
int usbMouseRemove(HidDev_t * HidDev)
{
    usbMouse_t *usbMouse = NULL;
    unsigned int cup_sr = 0;
    unsigned char err = 0;

    if(HidDev == NULL){
        hal_log_err("ERR: usbMouseRemove: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    usbMouse = HidDev->Extern;
    if(usbMouse == NULL){
        hal_log_err("ERR: usbMouseRemove: usbMouse == NULL\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    esKSRV_SendMsg(KMSG_USR_SYSTEM_MOUSE_PLUGOUT, KMSG_PRIO_HIGH);

    usbMouse_StopWork(usbMouse);

    hal_log_info("\n");
    hal_log_info("*****************************************************************\n");
    hal_log_info("*                                                               *\n");
    hal_log_info("* USB HOST UnRegist \"%s\" \"%s\" successful\n",
                 usbMouse->ClassName, usbMouse->DevName);
    hal_log_info("*                                                               *\n");
    hal_log_info("*****************************************************************\n");
    hal_log_info("\n");

    /* unregist device */
    if(usbMouse->MouseRegHdle){
        esDEV_DevUnreg(usbMouse->MouseRegHdle);
    }

    /* kill thread */
//  UsbKillThread(usbMouse->MouseThdId , usbMouse->MouseThreadSemi);
    kthread_stop(usbMouse->MouseThdId);

    if(usbMouse->notify_complete){
        hal_sem_delete(usbMouse->notify_complete);
        usbMouse->notify_complete = NULL;
    }

    if(usbMouse->MouseThreadSemi){
        hal_sem_delete(usbMouse->MouseThreadSemi);
        usbMouse->MouseThreadSemi = NULL;
    }

    UsbMouse_DriftControl_Exit(usbMouse);

    ENTER_CRITICAL(cup_sr);
    HidDev->Extern = NULL;
    EXIT_CRITICAL(cup_sr);

    hal_free(usbMouse);

    return USB_ERR_SUCCESS;
}

