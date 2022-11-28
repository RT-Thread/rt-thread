/*
********************************************************************************************************************
*                                              usb host driver
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : usb_msc_i.h
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
#ifndef  __USB_MSC_I_H__
#define  __USB_MSC_I_H_

#include "usb_host_common.h"

/* Sub Classes */
#define USBMSC_SUBCLASS_RBC             0x01        /* Typically, flash devices */
#define USBMSC_SUBCLASS_8020            0x02        /* CD-ROM                   */
#define USBMSC_SUBCLASS_QIC             0x03        /* QIC-157 Tapes            */
#define USBMSC_SUBCLASS_UFI             0x04        /* Floppy                   */
#define USBMSC_SUBCLASS_8070            0x05        /* Removable media          */
#define USBMSC_SUBCLASS_SCSI            0x06        /* Transparent              */
#define USBMSC_SUBCLASS_ISD200          0x07        /* ISD200 ATA               */

#define USBMSC_SUBCLASS_MIN             USBMSC_SUBCLASS_RBC
#define USBMSC_SUBCLASS_MAX             USBMSC_SUBCLASS_ISD200

/* Protocol */
#define USBMSC_INTERFACE_PROTOCOL_CBIT  0x00    /* Control/Bulk/Interrupt       */
#define USBMSC_INTERFACE_PROTOCOL_CBT   0x01    /* Control/Bulk w/o interrupt   */
#define USBMSC_INTERFACE_PROTOCOL_BOT   0x50    /* bulk only                    */

/* 预定义 */
struct __mscDev;
struct __ScsiCmnd;
struct __mscLun;


#define  MSC_MAX_LUN            15      /* msc协议规定最大支持15个Lun       */
#define  SCSI_INQUERY_LEN       36      /* 标准inquery命令返回的都是36字节  */
#define  SCSI_MAX_INQUERY_LEN   44      /* 标准inquery命令返回的都是36字节  */
#define  MSC_IOBUF_SIZE         64


/* mscDev状态 */
typedef enum __mscDev_state
{
    MSC_DEV_OFFLINE = 0,        /* mscDev已经拔出       */
    MSC_DEV_ONLINE,             /* mscDev已经添加       */
    MSC_DEV_DIED,               /* mscDev不可用         */
    MSC_DEV_RESET               /* mscDev正在被reset    */
} mscDev_state_t;

typedef int(* msc_ResetRecovery)(struct __mscDev *mscDev);
typedef int(* msc_Transport)(struct __mscDev *mscDev, struct __ScsiCmnd *ScsiCmnd);
typedef int(* msc_StopTransport)(struct __mscDev *mscDev);
typedef int(* msc_ProtocolHandler)(struct __mscDev *mscDev, struct __ScsiCmnd *ScsiCmnd);


/* mscDev的抽象, 描述了一个mscDev拥有的资源 */
typedef struct __mscDev
{
    struct usb_host_virt_dev *pusb_dev; /* mscDev 对应的Public USB Device   */
    struct usb_interface    *pusb_intf; /* Public usb interface             */

    /* device information */
    unsigned char InterfaceNo;           /* 接口号                               */
    unsigned char *transport_name;       /* 传输协议的名称                       */
    unsigned char *Protocol_name;        /* 命令集版本                           */
    unsigned char SubClass;              /* 子类                                 */
    unsigned char Protocol;              /* 传输协议                             */
    unsigned char MaxLun;                /* 最大Lun个数                          */
    unsigned int mscDevNo;             /* mscDev的编号                         */
    unsigned int lun_num;              /* mscDev拥有的lun的个数                */

    /* device manager */
    struct __mscLun *Lun[MSC_MAX_LUN];      /* 存放所有的Lun                */
    struct usb_list_head cmd_list;              /* 命令队列                     */
    hal_sem_t scan_lock;         /* 用来实现scan 和remove的互斥  */
    hal_sem_t DevLock;           /* 同一时间只允许一个人访问mscDev*/
    hal_sem_t ThreadSemi;        /* 线程信号量                   */
    hal_sem_t notify_complete;   /* 同步thread创建/删除          */
    mscDev_state_t state;                   /* mscDev当前所处的连接状态     */

    struct rt_thread *MainThreadId;                     /* 主线程ID                     */
    struct rt_thread *MediaChangeId;                        /* media change处理线程ID       */

    unsigned int SuspendTime;                      /* Suspend设备所需的时间        */

    /* command transport */
    unsigned int BulkIn;                           /* bulk in  pipe                */
    unsigned int BulkOut;                          /* bulk out pipe                */
    unsigned int CtrlIn;                           /* ctrl in  pipe                */
    unsigned int CtrlOut;                          /* ctrl out pipe                */
    unsigned int IntIn;                            /* interrupt in pipe            */
    unsigned char  EpInterval;                       /* int 传输主机查询设备的周期，Bulk传输忽略此值 */

    unsigned int Tag;                              /* SCSI-II queued command tag   */
    unsigned int busy;                             /* 主机是否正在处理命令         */
    struct __ScsiCmnd *ScsiCmnd;            /* current srb                  */
    struct urb *CurrentUrb;                 /* USB requests                 */
    hal_sem_t UrbWait;           /* wait for Urb done            */
    struct usb_ctrlrequest *CtrlReq;        /* control requests             */
    unsigned char *iobuf;                            /* mscDev缓冲区, CBW和CSW都用得到*/

    osal_timer_t TimerHdle;    /* timer 句柄                   */

    msc_ResetRecovery   ResetRecovery;      /* USB Controller reset         */
    msc_Transport       Transport;          /* msc设备支持的传输方式        */
    msc_StopTransport   StopTransport;      /* 中止msc传输                  */
    msc_ProtocolHandler ProtocolHandler;    /* msc传输                      */
} __mscDev_t;

typedef struct __disk_info_t
{
    unsigned int capacity;             /* 设备的容量，以扇区为单位         */
    unsigned int sector_size;          /* 扇区的大小                       */
} disk_info_t;

typedef enum __mscLun_state
{
    MSC_LUN_DEL = 0,        /* mscDev不可用     */
    MSC_LUN_ADD,            /* mscDev已经添加   */
    MSC_LUN_CANCEL          /* mscDev已经拔出   */
} mscLun_state_t;


typedef int(* LunProbe)(struct __mscLun *);       /* lun识别  */
typedef int(* LunRemove)(struct __mscLun *);      /* lun卸载  */
typedef void (* LunMediaChange)(struct __mscLun *); /* media change后的处理 */


/* Lun的抽象, 描述了一个Lun拥有的资源 */
typedef struct __mscLun
{
    __mscDev_t *mscDev;             /* Lun所属的mscDev                      */
    unsigned int LunNo;                    /* lun的编号                            */

    /* device information */
    unsigned int DeviceType;               /* 设备的类型                           */
    unsigned int MediumType;               /* 介质类型，CD_ROM枚举时有用           */
    unsigned char  DiskSubClass;             /* 命令类型                             */
    unsigned int ScsiLevel;                /* scsi命令集版本                       */
    unsigned char Inquiry[SCSI_MAX_INQUERY_LEN]; /* 存放inquire命令获得的设备信息        */
    unsigned char *Vendor;                   /* 供应商                               */
    unsigned char *Product;                  /* 产品信息                             */
    unsigned char *Revision;                 /* 产品序列号                           */

    /* Lun管理 */
    disk_info_t disk_info;          /* 磁盘信息                             */

    unsigned int WriteProtect: 1;          /* 是否是可写设备                       */
    unsigned int RemoveAble: 1;            /* 是否是可移动设备                     */
    unsigned int Changed: 1;               /* 设备是否改变过                       */
    unsigned int MediaPresent: 1;          /* 设备介质是否存在                     */
    unsigned int WCE: 1;                   /* cache写允许                          */
    unsigned int RCD: 1;                   /* cache读允许                          */
    unsigned int use_10_for_rw: 1;         /* first try 10-byte read / write       */
    unsigned int use_10_for_ms: 1;         /* first try 10-byte mode sense/select  */
    unsigned int skip_ms_page_8: 1;        /* do not use MODE SENSE page 0x08      */
    unsigned int skip_ms_page_3f: 1;       /* do not use MODE SENSE page 0x3f      */
    unsigned int use_192_bytes_for_3f: 1;  /* ask for 192 bytes from page 0x3f     */

    hal_sem_t Lock;      /* 信号量，每次值保证一个用在读或写 */

    LunProbe        Probe;
    LunRemove       Remove;
    LunMediaChange  MediaChange;

    void *sdev_data;                /* 指向top level的scsi disk等数据结构   */
} __mscLun_t;

/* 命令数据的方向 */
typedef enum scsi_data_direction
{
    DATA_NONE = 0,          /* No Data                  */
    DATA_TO_DEVICE,         /* Data Out. host->device   */
    DATA_FROM_DEVICE,       /* Data in. device->host    */
} scsi_data_direction_t;

/* command block的抽象 */
typedef struct __scsi_transport_cmd
{
    scsi_data_direction_t data_direction;   /* IN - DATA_IN or DATA_OUT         */
    unsigned int Tag;                      /* SCSI-II queued command tag               */
    unsigned int Timeout;                  /* IN - Timeout for this command Block      */
    unsigned int dwLun;                    /* IN - Logical Number for Logic Device.    */
    unsigned int CBLen;                    /* The length of command block              */
    void *CommandBlock;             /* IN - Pointer to the command block buffer.*/
} __scsi_transport_cmd_t;

typedef void (*LunDone)(struct __ScsiCmnd *);   /* mscDev调用，Lun cmd处理完毕  */

/* ScsiCmnd的抽象, 描述了一个ScsiCmnd拥有的资源 */
typedef struct __ScsiCmnd
{
    __mscLun_t *sc_lun;                     /* 命令所属的设备                       */
    //  struct list_head list;                  /* 此命令在device的cmd_list中的位置     */

    __scsi_transport_cmd_t cmnd;            /* Command Block                */
    unsigned int retries;                          /* 当前retry的次数              */
    unsigned int allowed;                          /* 允许retry的次数              */

    void *buffer;                           /* Data buffer                  */
    unsigned int DataTransferLength;               /* Size of data buffer          */
    unsigned int ActualLength;                     /* actual transport length      */

    hal_sem_t complete;          /* 等待Lun cmd处理完毕          */
    LunDone Done;

    unsigned int Result;                           /* 命令的执行结果               */
} __ScsiCmnd_t;

//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
#define  USB_STOR_TRANSPORT_GOOD        0   /* 没有错误                 */
#define  USB_STOR_TRANSPORT_FAILED      1   /* 传输成功，命令执行失败   */
#define  USB_STOR_TRANSPORT_ERROR       2   /* 传输失败                 */


//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
int mscDevQueueCmnd(__mscLun_t *mscLun, __ScsiCmnd_t *ScsiCmnd);
unsigned int mscDevOnline(__mscDev_t *mscDev);

#endif   //__USB_MSC_I_H__




