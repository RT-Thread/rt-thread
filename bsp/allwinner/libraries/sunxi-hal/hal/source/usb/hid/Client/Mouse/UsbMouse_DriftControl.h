/*
********************************************************************************
*                                USB Hid Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  UsbMouse_DriftControl.h
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
*      2010.07.16      1.0           Javen          build this file
*
********************************************************************************
*/
#ifndef  __USBMOUSE_DRIFTCONTROL_H__
#define  __USBMOUSE_DRIFTCONTROL_H__

//--------------------------------------------------------
//
//--------------------------------------------------------
typedef struct _UsbMouseEventUnit{
    unsigned int vaild;                 /* 是否有效 */
    USBHMouseEvent_t MouseEvent;    /* 鼠标事件 */
}UsbMouseEventUnit_t;

typedef struct _UsbMouseDriftControl{
    usbMouse_t *usbMouse;

    osal_timer_t TimerHdle; /* timer 句柄             */
    hal_sem_t ThreadSemi;       /* 线程信号量            */
    hal_sem_t notify_complete;  /* 线程同步信号量      */
    void *ThreadId;                         /* 线程ID                 */

    unsigned int ButtonDown;                        /* 按键按下             */

    UsbMouseEventUnit_t PreMouseEvent;      /* 上一次的鼠标事件     */
    UsbMouseEventUnit_t DubiousMouseEvent;  /* 可以的鼠标事件      */
    UsbMouseEventUnit_t CurrentMouseEvent;  /* 当前的鼠标事件      */
    unsigned int DubiousCoordinate;             /* 可疑坐标, bit1:X, bit2:Y, bit3: X & Y */
    unsigned int WaitEvent;                     /* 等待下一次的事件     */
}UsbMouseDriftControl_t;


//--------------------------------------------------------
//
//--------------------------------------------------------
void UsbMouse_AddToDriftArray(usbMouse_t *usbMouse, USBHMouseEvent_t *Event);
int UsbMouse_DriftControl_Init(usbMouse_t *usbMouse);
int UsbMouse_DriftControl_Exit(usbMouse_t *usbMouse);

#endif   //__USBMOUSE_DRIFTCONTROL_H__

