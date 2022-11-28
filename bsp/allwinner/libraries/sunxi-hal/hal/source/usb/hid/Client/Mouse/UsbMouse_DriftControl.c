/*
********************************************************************************
*                                USB Hid Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  UsbMouse_DriftControl.c
*
* Author        :  Javen
*
* Date          :  2010.06.02
*
* Description   :  USB Mouse 去抖动算法.
*     1、所有鼠标事件信息添加到队列中
*     2、每隔5ms处理队列中的所事件有信息。
*     3、
*
* Others        :  NULL
*
* History:
*       <time>      <version >      <author>        <desc>
*      2010.07.16      1.0           Javen          build this file
*
********************************************************************************
*/

//#include  "usb_host_config.h"
//#include  "usb_host_base_types.h"
#include "usb_os_platform.h"
#include "usb_host_common.h"
#include "error.h"
#include "HidSpec.h"
#include "Hid_i.h"
#include "HidFunDrv.h"
#include "UsbMouse.h"
#include "UsbMouse_DriftControl.h"

/*
*******************************************************************************
*                     UsbMouse_AddToDriftArray
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
static void UsbMouse_DriftTimeOut(void *parg)
{
    UsbMouseDriftControl_t *Drift = (UsbMouseDriftControl_t *)parg;
    unsigned int cup_sr = 0;

    if(Drift == NULL){
        hal_log_err("ERR: input error\n");
        return ;
    }

    /* 如果有可疑的点存在，就把可疑的点发出去 */
    if(Drift->WaitEvent && Drift->DubiousMouseEvent.vaild) {
        int val = 0;
        ENTER_CRITICAL(cup_sr);
        DMSG_MOUSE_TEST("TimeOut: DubiousCoordinate = %x\n", Drift->DubiousCoordinate);
        memcpy(&Drift->CurrentMouseEvent, &Drift->DubiousMouseEvent, sizeof(UsbMouseEventUnit_t));
        Drift->CurrentMouseEvent.vaild = 1;
        EXIT_CRITICAL(cup_sr);

//      UsbThreadWakeUp(Drift->ThreadSemi);
        if (!hal_sem_getvalue(Drift->ThreadSemi, &val))
        {
            hal_sem_post(Drift->ThreadSemi);
        }
    }

    return;
}

/*
*******************************************************************************
*                     UsbMouse_IsButtonEvent
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
static unsigned int UsbMouse_IsButtonEvent(USBHMouseEvent_t *MouseEvent)
{
    return (MouseEvent->Button.LeftButton
            || MouseEvent->Button.RightButton
            || MouseEvent->Button.MiddleButton
            || MouseEvent->Wheel);
}

/*
*******************************************************************************
*                     UsbMouse_IsDubiousEvent
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
static unsigned int UsbMouse_IsDubiousEvent(USBHMouseEvent_t *Event, UsbMouseDriftControl_t *Drift)
{
    unsigned int Dubious = 0;

    /* 如果参考点PreMouseEvent不存在, 那么就不用怀疑本次的点 */
    if(Drift->PreMouseEvent.vaild == 0){
        return 0;
    }

    /* 如果前后两次 X 坐标差值大于127, 那么就认为本次的坐标为可疑的坐标 */
    if(absolute(Event->X - Drift->PreMouseEvent.MouseEvent.X) > USB_HID_MOUSE_DITHER_AREA){
        usb_set_bit(1, (volatile uint32_t *)&Drift->DubiousCoordinate);
        Dubious = 1;
    }

    /* 如果前后两次 Y 坐标差值大于127, 那么就认为本次的坐标为可疑的坐标 */
    if(absolute(Event->Y - Drift->PreMouseEvent.MouseEvent.Y) > USB_HID_MOUSE_DITHER_AREA){
        usb_set_bit(2, (volatile uint32_t *)&Drift->DubiousCoordinate);
        Dubious = 1;
    }

    if(Dubious){
        DMSG_MOUSE_TEST("DubiousCoordinate = %x\n", Drift->DubiousCoordinate);
    }

    return Dubious;
}

/* 判断X和Y是否都是正数或者是否都是负数 */
static __u32 UsbMouse_IsAccord8(__s8 x, __s8 y)
{
    /* 是否都是负数 */
    if(x <= 0 && y <= 0){
        return 1;
    }

    /* 是否都是正数 */
    if(x >= 0 && y >= 0){
        return 1;
    }

    return 0;
}

/*
*******************************************************************************
*                     UsbMouse_AddToDriftArray
*
* Description:
*     从3个鼠标数据中找出轨迹相同的两个, 然后取平均值。
*
* Parameters:
*
*
* Return value:
*
*
* note:
*
*******************************************************************************
*/
static int UsbMouse_AdjustCoordinate(USBHMouseEvent_t *Event1,
                                       USBHMouseEvent_t *Event2,
                                       USBHMouseEvent_t *Event3,
                                       USBHMouseEvent_t *OutEvent)
{
    /* 寻找 X 坐标上方向一致的点 */
    if(UsbMouse_IsAccord8(Event1->X, Event2->X)
       && UsbMouse_IsAccord8(Event1->X, Event3->X)){ /* 1,2,3都一致 */
        OutEvent->X = (Event1->X / 3) + (Event2->X / 3) + (Event3->X / 3);
    }else if(UsbMouse_IsAccord8(Event1->X, Event2->X)){  /* 1,2都是一致的 */
        OutEvent->X = Event2->X;
    }else if(UsbMouse_IsAccord8(Event1->X, Event3->X)){  /* 1,3都是一致的 */
        OutEvent->X = Event3->X;
    }else if(UsbMouse_IsAccord8(Event2->X, Event3->X)){  /* 2,3都是一致的 */
        OutEvent->X = (Event2->X / 2) + (Event3->X / 2);
    }else{  /* 1,2,3都不是一致的 */
        OutEvent->X = (Event1->X / 3) + (Event2->X / 3) + (Event3->X / 3);
    }

    /* 寻找 Y 坐标上方向一致的点 */
    if(UsbMouse_IsAccord8(Event1->Y, Event2->Y)
       && UsbMouse_IsAccord8(Event1->Y, Event3->Y)){ /* 1,2,3都一致 */
        OutEvent->Y = (Event1->Y / 3) + (Event2->Y / 3) + (Event3->Y / 3);
    }else if(UsbMouse_IsAccord8(Event1->Y, Event2->Y)){  /* 1,2都是一致的 */
        OutEvent->Y = Event2->Y;
    }else if(UsbMouse_IsAccord8(Event1->Y, Event3->Y)){  /* 1,3都是一致的 */
        OutEvent->Y = Event3->Y;
    }else if(UsbMouse_IsAccord8(Event2->Y, Event3->Y)){  /* 2,3都是一致的 */
        OutEvent->Y = (Event2->Y / 2) + (Event3->Y / 2);
    }else{  /* 1,2,3都不是一致的 */
        OutEvent->Y = (Event1->Y / 3) + (Event2->Y / 3) + (Event3->Y / 3);
    }

    return 0;
}

/*
*******************************************************************************
*                     UsbMouse_AddToDriftArray
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
*   1、只有按键消息，直接发送给app。
*
*   2、只有wheel消息，直接发送给app。
*
*   3、只有坐标，就预测鼠标的轨迹，
*      如果本次的点A和上一次的点B相差太大，在规定时间内取下一次的点C作参考，
*      如果A和C相近，就丢掉B点，发送A点和C点给app；如果规定时间内没有鼠标事件,就把A点和B点给发给app。
*
*   4、如果按键、wheel、坐标参杂在一起，遇到按键或者wheel事件后，
*      把当前所有的点全部发给app，并且把下一次的按键抬起消息，也及时的发送出去。
*
*******************************************************************************
*/void UsbMouse_AddToDriftArray(usbMouse_t *usbMouse, USBHMouseEvent_t *Event)
{
    int val = 0;
    UsbMouseDriftControl_t *Drift = NULL;
    unsigned int cup_sr = 0;

    if(usbMouse == NULL){
        hal_log_err("ERR: input error\n");
        return ;
    }

    Drift = usbMouse->Extern;
    if(Drift == NULL){
        hal_log_err("ERR: Drift == NULL\n");
        return ;
    }

    /* 先前有按键按下, 这里遇到抬起键, 就给把本次消息发送给APP */
    if(Drift->ButtonDown){
        /* 如果本次还有按键消息, 就记录下来 */
        if(UsbMouse_IsButtonEvent(Event)){
            DMSG_MOUSE_TEST("Had send a button down event, then a new button event come\n");
            Drift->ButtonDown = 1;
        }else{
            DMSG_MOUSE_TEST("Had send a button down event, then wait for button rise\n");
            Drift->ButtonDown = 0;
        }

        goto SendMsg;
    }

    /* 有按键事件或者滚轮事件，就唤醒线程 */
    if(UsbMouse_IsButtonEvent(Event)){
        DMSG_MOUSE_TEST("have a button event\n");

        Drift->ButtonDown = 1;
        goto SendMsg;
    }

    /* 如果PreMouseEvent和dubiousMouseEvent都有效, 那么就直接比较 */
    if(Drift->PreMouseEvent.vaild && Drift->DubiousMouseEvent.vaild){
        ENTER_CRITICAL(cup_sr);
        DMSG_MOUSE_TEST("------Pre------\n");
        DMSG_MOUSE_TEST("DubiousCoordinate = %x\n", Drift->DubiousCoordinate);

        DMSG_MOUSE_TEST("Pre Button 1 = %d\n", Drift->PreMouseEvent.MouseEvent.Button.LeftButton);
        DMSG_MOUSE_TEST("Pre Button 2 = %d\n", Drift->PreMouseEvent.MouseEvent.Button.RightButton);
        DMSG_MOUSE_TEST("Pre Button 3 = %d\n", Drift->PreMouseEvent.MouseEvent.Button.MiddleButton);
        DMSG_MOUSE_TEST("Pre Button 4 = %d\n", Drift->PreMouseEvent.MouseEvent.Button.Button4);
        DMSG_MOUSE_TEST("Pre Button 5 = %d\n", Drift->PreMouseEvent.MouseEvent.Button.Button5);
        DMSG_MOUSE_TEST("Pre Button 6 = %d\n", Drift->PreMouseEvent.MouseEvent.Button.Button6);
        DMSG_MOUSE_TEST("Pre Button 7 = %d\n", Drift->PreMouseEvent.MouseEvent.Button.Button7);
        DMSG_MOUSE_TEST("Pre Button 8 = %d\n", Drift->PreMouseEvent.MouseEvent.Button.Button8);

        DMSG_MOUSE_TEST("Pre X        = %d\n", Drift->PreMouseEvent.MouseEvent.X);
        DMSG_MOUSE_TEST("Pre Y        = %d\n", Drift->PreMouseEvent.MouseEvent.Y);
        DMSG_MOUSE_TEST("Pre Wheel    = %d\n", Drift->PreMouseEvent.MouseEvent.Wheel);
        DMSG_MOUSE_TEST("\n");

        DMSG_MOUSE_TEST("\n");
        DMSG_MOUSE_TEST("dubious Button 1 = %d\n", Drift->DubiousMouseEvent.MouseEvent.Button.LeftButton);
        DMSG_MOUSE_TEST("dubious Button 2 = %d\n", Drift->DubiousMouseEvent.MouseEvent.Button.RightButton);
        DMSG_MOUSE_TEST("dubious Button 3 = %d\n", Drift->DubiousMouseEvent.MouseEvent.Button.MiddleButton);
        DMSG_MOUSE_TEST("dubious Button 4 = %d\n", Drift->DubiousMouseEvent.MouseEvent.Button.Button4);
        DMSG_MOUSE_TEST("dubious Button 5 = %d\n", Drift->DubiousMouseEvent.MouseEvent.Button.Button5);
        DMSG_MOUSE_TEST("dubious Button 6 = %d\n", Drift->DubiousMouseEvent.MouseEvent.Button.Button6);
        DMSG_MOUSE_TEST("dubious Button 7 = %d\n", Drift->DubiousMouseEvent.MouseEvent.Button.Button7);
        DMSG_MOUSE_TEST("dubious Button 8 = %d\n", Drift->DubiousMouseEvent.MouseEvent.Button.Button8);

        DMSG_MOUSE_TEST("dubious X        = %d\n", Drift->DubiousMouseEvent.MouseEvent.X);
        DMSG_MOUSE_TEST("dubious Y        = %d\n", Drift->DubiousMouseEvent.MouseEvent.Y);
        DMSG_MOUSE_TEST("dubious Wheel    = %d\n", Drift->DubiousMouseEvent.MouseEvent.Wheel);
        DMSG_MOUSE_TEST("\n");

        DMSG_MOUSE_TEST("\n");
        DMSG_MOUSE_TEST("Event Button 1 = %d\n", Event->Button.LeftButton);
        DMSG_MOUSE_TEST("Event Button 2 = %d\n", Event->Button.RightButton);
        DMSG_MOUSE_TEST("Event Button 3 = %d\n", Event->Button.MiddleButton);
        DMSG_MOUSE_TEST("Event Button 4 = %d\n", Event->Button.Button4);
        DMSG_MOUSE_TEST("Event Button 5 = %d\n", Event->Button.Button5);
        DMSG_MOUSE_TEST("Event Button 6 = %d\n", Event->Button.Button6);
        DMSG_MOUSE_TEST("Event Button 7 = %d\n", Event->Button.Button7);
        DMSG_MOUSE_TEST("Event Button 8 = %d\n", Event->Button.Button8);

        DMSG_MOUSE_TEST("Event X        = %d\n", Event->X);
        DMSG_MOUSE_TEST("Event Y        = %d\n", Event->Y);
        DMSG_MOUSE_TEST("Event Wheel    = %d\n", Event->Wheel);
        DMSG_MOUSE_TEST("------Pre------\n");

        EXIT_CRITICAL(cup_sr);

        /* 寻找同方向的两个点 */
        /* X坐标可疑 */
        UsbMouse_AdjustCoordinate(&Drift->PreMouseEvent.MouseEvent,
                                  &Drift->DubiousMouseEvent.MouseEvent,
                                  Event,
                                  Event);

        Drift->DubiousMouseEvent.vaild = 0;
        Drift->PreMouseEvent.vaild     = 0;

        goto SendMsg;
    }else{
        /* 判断本次坐标是否可疑? */
        if(UsbMouse_IsDubiousEvent(Event, Drift) == 0){
            goto SendMsg;
        }else{
            hal_log_info("a Dubious event\n");

            ENTER_CRITICAL(cup_sr);
            memcpy(&Drift->DubiousMouseEvent.MouseEvent, Event, sizeof(USBHMouseEvent_t));
            Drift->DubiousMouseEvent.vaild = 1;
            Drift->WaitEvent = 1;
            EXIT_CRITICAL(cup_sr);
        }
    }

    return;

SendMsg:
    ENTER_CRITICAL(cup_sr);
    memcpy(&Drift->CurrentMouseEvent.MouseEvent, Event, sizeof(USBHMouseEvent_t));
    Drift->CurrentMouseEvent.vaild = 1;
    EXIT_CRITICAL(cup_sr);

//  UsbThreadWakeUp(Drift->ThreadSemi);
    if (!hal_sem_getvalue(Drift->ThreadSemi, &val))
    {
        hal_sem_post(Drift->ThreadSemi);
    }
//  UsbThreadSleep(Drift->notify_complete);
    hal_sem_wait(Drift->notify_complete);

    return;
}

/*
*******************************************************************************
*                     UsbMouse_DriftControl
*
* Description:
*    鼠标去抖动
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
static int UsbMouse_DriftControl(UsbMouseDriftControl_t *Drift)
{
    int val = 0;
    unsigned int cup_sr = 0;

    /* 清除等待标志 */
    ENTER_CRITICAL(cup_sr);
    Drift->WaitEvent = 0;
    EXIT_CRITICAL(cup_sr);

    /* sent mouse event to system */
    if(Drift->CurrentMouseEvent.vaild){
        ENTER_CRITICAL(cup_sr);

        memcpy(&Drift->usbMouse->MouseEvent, &Drift->CurrentMouseEvent.MouseEvent, sizeof(USBHMouseEvent_t));
        memcpy(&Drift->PreMouseEvent, &Drift->CurrentMouseEvent, sizeof(UsbMouseEventUnit_t));

        Drift->PreMouseEvent.vaild     = 1;
        Drift->CurrentMouseEvent.vaild = 0;
        Drift->DubiousMouseEvent.vaild = 0;

        DMSG_MOUSE_TEST("\n");
        DMSG_MOUSE_TEST("msg Button 1 = %d\n", Drift->usbMouse->MouseEvent.Button.LeftButton);
        DMSG_MOUSE_TEST("msg Button 2 = %d\n", Drift->usbMouse->MouseEvent.Button.RightButton);
        DMSG_MOUSE_TEST("msg Button 3 = %d\n", Drift->usbMouse->MouseEvent.Button.MiddleButton);
        DMSG_MOUSE_TEST("msg Button 4 = %d\n", Drift->usbMouse->MouseEvent.Button.Button4);
        DMSG_MOUSE_TEST("msg Button 5 = %d\n", Drift->usbMouse->MouseEvent.Button.Button5);
        DMSG_MOUSE_TEST("msg Button 6 = %d\n", Drift->usbMouse->MouseEvent.Button.Button6);
        DMSG_MOUSE_TEST("msg Button 7 = %d\n", Drift->usbMouse->MouseEvent.Button.Button7);
        DMSG_MOUSE_TEST("msg Button 8 = %d\n", Drift->usbMouse->MouseEvent.Button.Button8);

        DMSG_MOUSE_TEST("msg X        = %d\n", Drift->usbMouse->MouseEvent.X);
        DMSG_MOUSE_TEST("msg Y        = %d\n", Drift->usbMouse->MouseEvent.Y);
        DMSG_MOUSE_TEST("msg Wheel    = %d\n", Drift->usbMouse->MouseEvent.Wheel);
        DMSG_MOUSE_TEST("\n");

        EXIT_CRITICAL(cup_sr);

        if(Drift->usbMouse->CallBack){
            esKRNL_CallBack((__pCBK_t)Drift->usbMouse->CallBack, (void *)&Drift->usbMouse->MouseEvent);
        }
    }

//  UsbThreadWakeUp(Drift->notify_complete);
    if (!hal_sem_getvalue(Drift->ThreadSemi, &val))
    {
        hal_sem_post(Drift->ThreadSemi);
    }

    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     UsbMouse_DriftThread
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
static void UsbMouse_DriftThread(void *p_arg)
{
    UsbMouseDriftControl_t *Drift = (UsbMouseDriftControl_t *)p_arg;

    if(Drift == NULL){
        hal_log_err("ERR: input error\n");
        return ;
    }


    hal_sem_post(Drift->notify_complete);

    while(1){
        //--<1>--杀死线程
//      TryToKillThreadSelf("UsbMouse_DriftThread");

//      /* sleep */
//      UsbThreadSleep(Drift->ThreadSemi);
        kthread_stop(Drift->ThreadId);
        hal_sem_wait(Drift->ThreadSemi);

        UsbMouse_DriftControl(Drift);
    }
}

/*
*******************************************************************************
*                     UsbMouse_DriftControl_Init
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
int UsbMouse_DriftControl_Init(usbMouse_t *usbMouse)
{
    int status = 0;
    UsbMouseDriftControl_t *Drift;
    unsigned int err = 0;

    Drift = hal_malloc(sizeof(UsbMouseDriftControl_t));
    if(Drift == NULL){
        hal_log_err("ERR: hal_malloc failed\n");
        return USB_ERR_MALLOC_FAILED;
    }

    memset(Drift, 0, sizeof(UsbMouseDriftControl_t));

    /* create thread */
    Drift->ThreadSemi = hal_sem_create(0);
    if(Drift->ThreadSemi == NULL){
        hal_log_err("ERR: USB_OS_SemCreate ThreadSemi failed\n");
        status = USB_ERR_CREATE_SIME_FAILED;
        goto err0;
    }

    Drift->notify_complete = hal_sem_create(0);
    if(Drift->notify_complete == NULL){
        hal_log_err("ERR: USB_OS_SemCreate notify_complete failed\n");
        status = USB_ERR_CREATE_SIME_FAILED;
        goto err1;
    }

    /* Mouse Drift thread */
    Drift->ThreadId = kthread_create((void *)UsbMouse_DriftThread,
                                      (void *)Drift,
                                      "UsbMouse_DriftThread");
    if(Drift->ThreadId == OS_NO_ERR){
        hal_log_err("ERR: create MainThreadId failed\n");
        status = USB_ERR_CREATE_THREAD_FAILED;
        goto err2;
    }

    hal_sem_wait(Drift->notify_complete);

    /* create timer */
    Drift->TimerHdle = osal_timer_create("UsbMouse_DriftControl", UsbMouse_DriftTimeOut, (void*)Drift,
                    400, OSAL_TIMER_FLAG_PERIODIC);

    if(Drift->TimerHdle == NULL){
        hal_log_err("ERR: create timer failed\n");
        status = USB_ERR_CREATE_TIMER_FAILED;
        goto err3;
    }

    osal_timer_start(Drift->TimerHdle);

    /*  */
    Drift->usbMouse = usbMouse;
    usbMouse->Extern = Drift;

    return USB_ERR_SUCCESS;


err3:
//  UsbKillThread(Drift->ThreadId, NULL);
    kthread_stop(Drift->ThreadId);
err2:
    hal_sem_delete(Drift->notify_complete);
    Drift->notify_complete = NULL;

err1:
    hal_sem_delete(Drift->ThreadSemi);
    Drift->ThreadSemi = NULL;

err0:
    hal_free(Drift);

    return status;
}

/*
*******************************************************************************
*                     UsbMouse_DriftControl_Exit
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
int UsbMouse_DriftControl_Exit(usbMouse_t *usbMouse)
{
    UsbMouseDriftControl_t *Drift = NULL;
    unsigned int err = 0;

    if(usbMouse == NULL){
        hal_log_err("ERR: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    Drift = usbMouse->Extern;
    if(Drift == NULL){
        hal_log_err("ERR: Drift == NULL\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* stop and kill timer */
    osal_timer_stop(Drift->TimerHdle);
    osal_timer_delete(Drift->TimerHdle);
    Drift->TimerHdle = NULL;

    /* kill thread */
//  UsbKillThread(Drift->ThreadId, Drift->ThreadSemi);
    kthread_stop(Drift->ThreadId);

    hal_sem_delete(Drift->ThreadSemi);
    Drift->ThreadSemi = NULL;

    hal_sem_delete(Drift->notify_complete);
    Drift->notify_complete = NULL;

    usbMouse->Extern = NULL;
    hal_free(Drift);

    return USB_ERR_SUCCESS;
}

