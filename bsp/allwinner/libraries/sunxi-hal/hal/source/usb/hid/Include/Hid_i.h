/*
********************************************************************************
*                                USB Hid Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  Hid_i.h
*
* Author        :  Javen
*
* Date          :  2010/06/02
*
* Description   :  Hid Driver中对USB接口设备的描述
*
* Others        :  NULL
*
* History:
*       <time>          <author>     <version >     <desc>
*      2010.06.02       Javen           1.0         build this file
*
********************************************************************************
*/
#ifndef  __HID_I_H__
#define  __HID_I_H__
#include <hal_osal.h>

//---------------------------------------------------------
//  预定义
//---------------------------------------------------------
struct _HidRequest;
struct _HidDev;
struct _usbHidReport;

//----------------------------------------------------------------------
//
//
//----------------------------------------------------------------------
/* input, output, feature */
#define USB_HID_MAX_FIELDS      64
typedef struct _usbHidField{
    /* Field用途 */
    unsigned int physical;              /* physical usage for this field                    */
    unsigned int logical;               /* logical usage for this field                     */
    unsigned int application;           /* application usage for this field                 */
    usbHidUsage_t *usage;       /* usage table for this function                    */
    unsigned int maxusage;              /* maximum usage index                              */
    unsigned int flags;             /* main-item flags (i.e. volatile,array,constant)   */
    unsigned int report_offset;     /* bit offset in the report                         */
    unsigned int report_size;           /* size of this field in the report                 */
    unsigned int report_count;          /* number of this field in the report               */
    unsigned int report_type;           /* (input,output,feature)                           */
    unsigned int *value;                /* last known value(s)                              */
    int logical_minimum;        /* 最小逻辑值                                        */
    int logical_maximum;        /* 最大逻辑值                                        */
    int physical_minimum;       /* 最小物理值                                        */
    int physical_maximum;       /* 最大物理值                                        */
    int unit_exponent;      /* 单位指数                                         */
    unsigned int unit;                  /* 单位                                           */

    /* Field属性 */
    unsigned int Index;             /* ndex into report->field[]                        */
    struct _usbHidReport *HidReport; /* field 所属的 HID report                    */
}usbHidField_t;

#define  USB_HID_REPORT_TYPES       3   /* 报告的种类        */
#define  USB_HID_REPORT_MAX_NUM     256 /* 报告的最大个数  */

/* 设备报告定义，有input, output, feature等3种 */
typedef struct _usbHidReport{
    unsigned int Id;                                    /* id of this report            */
    unsigned int Type;                                  /* report type,                 */

    unsigned int Maxfield;                              /* maximum valid field index    */
    usbHidField_t *Field[USB_HID_MAX_FIELDS];   /* fields of the report         */

    unsigned int Size;                                  /* size of the report (bits)    */
}usbHidReport_t;

/* 设备的所有报告 */
typedef struct _usbHidReportEnum{
    unsigned int numbered;   /* reprot是否存在 */

    unsigned int ReportNum;  /* 有效的Report的个数 */
    usbHidReport_t *Report[USB_HID_REPORT_MAX_NUM];
}usbHidReportEnum_t;

#define  USB_HID_GLOBAL_STACK_SIZE          4
#define  USB_HID_COLLECTION_STACK_SIZE      4
typedef struct _usbHidParser {
    usbHidGlobalItems_t global;
    usbHidGlobalItems_t global_stack[USB_HID_GLOBAL_STACK_SIZE];
    unsigned int  global_stack_ptr;

    usbHidLocalItems_t local;

    unsigned int collection_stack[USB_HID_COLLECTION_STACK_SIZE];
    unsigned int collection_stack_ptr;

    struct _HidDev *HidDev;
}usbHidParser_t;


/* hid事件在hid DATA里的偏移量 */
typedef struct _usbHidEvnetExcursion{
    unsigned int BitOffset;
    unsigned int BitCount;
}usbHidEvnetExcursion_t;

//---------------------------------------------------------
//
//---------------------------------------------------------

/* Hid device state */
typedef enum _HidDev_state{
    HID_DEV_OFFLINE= 0,         /* HidDev已经拔出       */
    HID_DEV_ONLINE,             /* HidDev已经添加       */
    HID_DEV_DIED,               /* HidDev不可用        */
    HID_DEV_RESET               /* HidDev正在被reset   */
}HidDev_State_t;

/* USB Hid device type */
//#define  USB_HID_DEVICE_TYPE_UNKOWN       0x00    /* 未知设备 */
//#define  USB_HID_DEVICE_TYPE_KEYBOARD 0x01    /* 键盘   */
//#define  USB_HID_DEVICE_TYPE_MOUSE        0x02    /* 鼠标   */

typedef int (* Hid_SoftReset)(struct _HidDev *HidDev);
typedef int (* Hid_ResetRecovery)(struct _HidDev *HidDev);
typedef int (* Hid_Transport)(struct _HidDev *HidDev, struct _HidRequest *HidReq);
typedef int (* Hid_StopTransport)(struct _HidDev *HidDev);

typedef int (* HidClientProbe)(struct _HidDev *);
typedef int (* HidClientRemove)(struct _HidDev *);

/* 描述USB接口的信息 */
typedef struct _HidDev{
    struct usb_host_virt_dev *pusb_dev;     /* mscDev 对应的Public USB Device  */
    struct usb_interface     *pusb_intf;    /* Public usb interface             */

    /* device information */
    unsigned char InterfaceNo;                      /* 接口号                          */
    unsigned char SubClass;                             /* 子类                           */
    unsigned char Protocol;                             /* 传输协议                         */
    unsigned int DevType;                           /* 设备类型                         */
    unsigned int DevNo;                             /* 设备在 hid 管理中的编号           */

    /* device manager */
    HidDev_State_t State;                   /* Dev当前所处的连接状态             */

    unsigned char *ReportDesc;                      /* 装载这Hid设备的report描述符       */
    unsigned int ReportSize;                        /* report描述符的大小                 */

    usbHidCollectionItems_t *collection;        /* List of HID collections              */
    unsigned collection_size;                   /* Number of allocated hid_collections  */
    unsigned maxcollection;                     /* Number of parsed collections         */
    unsigned maxapplication;                    /* Number of applications               */
    usbHidReportEnum_t HidReportEnum[USB_HID_REPORT_TYPES];     /* 设备的报告信息      */

    /* transport */
    unsigned int CtrlIn;                            /* ctrl in  pipe                    */
    unsigned int CtrlOut;                           /* ctrl out pipe                    */
    unsigned int IntIn;                         /* interrupt in pipe                */
    unsigned char  EpInterval;                      /* int 传输主机查询设备的周期      */
    unsigned int OnceTransferLength;                /* 中断ep的最大传输包大小             */

    unsigned int busy;                              /* 主机是否正在处理命令           */
    struct urb *CurrentUrb;                 /* USB requests                     */
    hal_sem_t UrbWait;          /* wait for Urb done                */
    struct usb_ctrlrequest *CtrlReq;        /* control requests                 */

    /* USB接口操作 */
    Hid_SoftReset     SoftReset;            /* 软复位，只是清除 hid device 的状态 */
    Hid_ResetRecovery ResetRecovery;        /* reset device                     */
    Hid_Transport     Transport;            /* 传输                           */
    Hid_StopTransport StopTransport;        /* 中止传输                         */

    /* Hid设备操作 */
    HidClientProbe  ClientProbe;
    HidClientRemove ClientRemove;

    void *Extern;                           /* 对应具体的hid设备, 如mouse, keyboard */
}HidDev_t;

typedef void (* HidClientDone)(struct _HidRequest *);

/* Hid 传输请求 */
typedef struct _HidRequest{
    HidDev_t *HidDev;

    void *buffer;                           /* Data buffer                  */
    unsigned int DataTransferLength;                /* Size of data buffer          */
    unsigned int ActualLength;                      /* actual transport length      */

    HidClientDone Done;
    unsigned int Result;                            /* 执行结果                     */

    void *Extern;                           /* 对应具体的hid设备, 如mouse, keyboard */
}HidRequest_t;

//-----------------------------------------------------
//  Hid 传输结果
//-----------------------------------------------------
#define  USB_HID_TRANSPORT_SUCCESS              0x00  /* 传输成功           */

#define  USB_HID_TRANSPORT_DEVICE_DISCONNECT    0x01  /* 设备断开           */
#define  USB_HID_TRANSPORT_DEVICE_RESET         0x02  /* 设备复位           */
#define  USB_HID_TRANSPORT_PIPE_HALT            0x03  /* 传输管道异常         */
#define  USB_HID_TRANSPORT_CANCEL_CMD           0x04  /* 软件中止此次传输   */

#define  USB_HID_TRANSPORT_UNKOWN_ERR           0xFF  /* 未知错误           */


//-----------------------------------------------------
//
//-----------------------------------------------------
int HidSentRequest(HidRequest_t *HidReq);
int HidGetInputReport(HidDev_t *HidDev, unsigned int Usagepage, unsigned int Usage, unsigned int *BitOffset, unsigned int *BitCount);


#endif   //__HID_I_H__

