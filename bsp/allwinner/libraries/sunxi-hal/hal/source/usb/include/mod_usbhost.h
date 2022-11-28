/*
********************************************************************************************************************
*                                              usb host driver
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : drv_host.h
*
* Author        : javen
*
* Version       : 2.0
*
* Date          : 2009.07.17
*
* Description   :
*
* History       :
*
*
********************************************************************************************************************
*/

#ifndef    __DRV_HOST_H__
#define    __DRV_HOST_H__
#include   <typedef.h>
//---------------------------------------------------------
//    Device Name
//---------------------------------------------------------
#define  USB_DEVICE_INFO_NAME       "USB_DEV_INFO"  /* USB设备信息                  */
#define  USB_STORAGE_DEV_NAME       "SCSI_DISK"     /* USB 存储类设备名           */
#define  USB_CDROM_DEV_NAME         "USB_CDROM"     /* USB 光驱设备                 */

//---------------------------------------------------------
//     USB HOST IOCTRL COMMAND MASK
//---------------------------------------------------------
#define  USB_USER_CTRL_CMD_MASK     0x0f0000

#define  USB_USER_CTRL_CMD_DEVICE_INFO_MASK (USB_USER_CTRL_CMD_MASK | 0x1000)
#define  USB_USER_CTRL_CMD_STORAGE_MASK     (USB_USER_CTRL_CMD_MASK | 0x2000)
#define  USB_USER_CTRL_CMD_HID_MASK         (USB_USER_CTRL_CMD_MASK | 0x3000)

//---------------------------------------------------------
//     USB 存储类设备扩展的控制设备
//---------------------------------------------------------
#define USB_DEVICE_INFO_USER_CMD_GET_DISK_STATUS    (USB_USER_CTRL_CMD_DEVICE_INFO_MASK | 0x00) /* 读取当前所有lun的读写状态         */
#define USB_DEVICE_INFO_USER_CMD_GET_DEVICE_INFO    (USB_USER_CTRL_CMD_DEVICE_INFO_MASK | 0x01) /* 获得设备的信息                    */

#define USB_STORAGE_DEVICE_STATUS_IDLE          0x00 /* USB处于空闲状态   */
#define USB_STORAGE_DEVICE_STATUS_READ          0x01 /* USB处于读状态  */
#define USB_STORAGE_DEVICE_STATUS_WRITE         0x02 /* USB处于写状态  */

/* 设备类型。如移动硬盘、U盘、光驱等 */
typedef  enum _USBStorDevType
{
    USB_STORAGE_DEVICE_TYPE_UNKOWN = 0,     /* 未知设备     */
    USB_STORAGE_DEVICE_TYPE_HDD,            /* 移动磁盘     */
    USB_STORAGE_DEVICE_TYPE_UDISK,          /* U盘、读卡器  */
    USB_STORAGE_DEVICE_TYPE_CDROM           /* USB光驱      */
} USBStorDevType_t;

#define  USB_HOST_MAX_STRING_LEN        128
typedef struct _usbhDeivceInfo
{
    char Vender[USB_HOST_MAX_STRING_LEN];   /* 设备厂商名  */
    char Product[USB_HOST_MAX_STRING_LEN];  /* 设备产品名  */
    char Serial[USB_HOST_MAX_STRING_LEN];   /* 序列号        */

    unsigned int HubPortNo;        /* 设备所在的Hub端口号. 0~7: Hub端口号，8~15: Hub级数，16~31: 保留。
                               Hub级数为0，表示没有hub接入 */
    unsigned int DeviceType;       /* 设备类型。参考USBStorDevType_t */
    unsigned char res[508];
} usbhDeivceInfo_t;

//---------------------------------------------------------
//     USB HOST STORAGE Class Driver IOCTRL COMMAND
//---------------------------------------------------------
#define USB_STORAGE_USER_CTRL_CMD_GET_CDROM_INFO    (USB_USER_CTRL_CMD_STORAGE_MASK | 0x01) /* 获得光驱状态                   */
#define USB_STORAGE_USER_CTRL_CMD_CDROM_PALY        (USB_USER_CTRL_CMD_STORAGE_MASK | 0x02) /* 让光驱从指定的MSF位置开始播放   */
#define USB_STORAGE_USER_CTRL_CMD_CDROM_STOP        (USB_USER_CTRL_CMD_STORAGE_MASK | 0x03) /* 停止播放                         */
#define USB_STORAGE_USER_CTRL_CMD_CDROM_EJECT       (USB_USER_CTRL_CMD_STORAGE_MASK | 0x04) /* 弹出光驱                         */
#define USB_STORAGE_USER_CTRL_CMD_CDROM_LOAD        (USB_USER_CTRL_CMD_STORAGE_MASK | 0x05) /* 装载光碟进光驱                    */
#define USB_STORAGE_USER_CTRL_CMD_CDROM_PREVENT_MEDIUM_REMOVAL  (USB_USER_CTRL_CMD_STORAGE_MASK | 0x06) /* 禁止介质移动           */
#define USB_STORAGE_USER_CTRL_CMD_CDROM_ALLOW_MEDIUM_REMOVAL    (USB_USER_CTRL_CMD_STORAGE_MASK | 0x07) /* 允许介质移动       */
#define USB_STORAGE_USER_CTRL_CMD_CDROM_GET_DRIVE_STATUS        (USB_USER_CTRL_CMD_STORAGE_MASK | 0x08) /* 获得光驱的状态        */

/* 光驱的类型 */
#define  USBH_CDROM_DRIVER_TYPE_UNKOWN          0x00    /* 未知               */
#define  USBH_CDROM_DRIVER_TYPE_CDR_RD          0x01    /* CD-R Read Only       */
#define  USBH_CDROM_DRIVER_TYPE_CDR_WR          0x02    /* CD-R WR              */
#define  USBH_CDROM_DRIVER_TYPE_CDE_RD          0x04    /* CD-E Read Only       */
#define  USBH_CDROM_DRIVER_TYPE_CDE_WR          0x08    /* CD-E WR              */
#define  USBH_CDROM_DRIVER_TYPE_DVD_ROM_RD      0x10    /* DVD-ROM Read Only    */
#define  USBH_CDROM_DRIVER_TYPE_DVDR_RD         0x20    /* DVD-R Read Only      */
#define  USBH_CDROM_DRIVER_TYPE_DVDR_WR         0x40    /* DVD-R WR             */
#define  USBH_CDROM_DRIVER_TYPE_DVD_RAM_RD      0x80    /* DVD-RAM Read Only    */
#define  USBH_CDROM_DRIVER_TYPE_DVD_RAM_WR      0x100   /* DVD-RAM WR           */

/* 光碟的类型 */
#define  USBH_MEDIUM_CD_UNKOWN                  0x00    /* 未知               */
#define  USBH_MEDIUM_CD_DATA_ONLY               0x01    /* 数据光碟             */
#define  USBH_MEDIUM_CD_AUDIO_ONLY              0x02    /* 音乐光碟             */
#define  USBH_MEDIUM_CD_DATA_AUDIO_COMBINED     0x03    /* 数据音乐混合光碟     */
#define  USBH_MEDIUM_CD_PHOTO_CD                0x04    /* 图片光碟             */

/* 光驱的状态 */
#define  USBH_CDROM_DRIVE_STATUS_NO_INFORMATION     0x00    /* 缺省值，未知的光驱状态        */
#define  USBH_CDROM_DRIVE_STATUS_NO_DISC            0x01    /* 光驱关闭，但是没有光碟        */
#define  USBH_CDROM_DRIVE_STATUS_TRAY_OPEN          0x02    /* 光驱已经打开               */
#define  USBH_CDROM_DRIVE_STATUS_NOT_READY          0x03    /* 光碟已经装载，但是介质未就绪   */
#define  USBH_CDROM_DRIVE_STATUS_DISK_OK            0x04    /* 光碟已经装载，并且介质就绪  */

/* USB 光驱和光碟信息 */
typedef struct _usbh_CDROM_Info
{
    __u32 DriveType;    /* 光驱的类型,每个bit都自己的含义 */
    __u32 DiscType;     /* 光碟的类型 */

    __u8 res[504];
} usbh_CDROM_Info_t;


//---------------------------------------------------------
//     USB HOST HID Class Driver IOCTRL COMMAND
//---------------------------------------------------------
typedef s32 (* USBHMouse_CallBack)(void *p_arg);
typedef void (* USBHJoystick_CallBack)(void *arg, __s32 *buttom, __s32 *stickX, __s32 *stickY, __s32 *reserve);

/* USB鼠标测试专用 */
#define  USBH_HID_USER_CTRL_CMD_TEST_START  (USB_USER_CTRL_CMD_HID_MASK | 0x00) /* USB鼠标测试命令. 开始 */
#define  USBH_HID_USER_CTRL_CMD_TEST_STOP   (USB_USER_CTRL_CMD_HID_MASK | 0x01) /* USB鼠标测试命令. 结束 */

typedef struct _USBHMouseTest
{
    void *buffer;
    USBHMouse_CallBack CallBack;
} USBHMouseTest_t;

/* 用户专用 */
#define USBH_HID_USER_CTRL_CMD_REG          (USB_USER_CTRL_CMD_HID_MASK | 0x10) /* 向USB注册回调函数 */
#define USBH_HID_USER_CTRL_CMD_UNREG        (USB_USER_CTRL_CMD_HID_MASK | 0x11) /* 向USB注销回调函数 */
typedef struct _USBHMouseEvent
{
    struct
    {
        __u8 LeftButton     : 1;        /* 鼠标左键 */
        __u8 RightButton    : 1;        /* 鼠标右键 */
        __u8 MiddleButton   : 1;        /* 鼠标中键 */
        __u8 Button4        : 1;
        __u8 Button5        : 1;
        __u8 Button6        : 1;
        __u8 Button7        : 1;
        __u8 Button8        : 1;
    } Button;

    __s8 X;             /* X 坐标, 相对坐标   */
    __s8 Y;             /* Y 坐标, 相对坐标   */
    __s8 Wheel;         /* 鼠标滚轮, >0表示向上滚动, <0表示向下滚动 */

    __u8 res[4];
} USBHMouseEvent_t;

//手柄
#define USBH_HID_USER_CTRL_CMD_JOYSTICK_FUN     (USB_USER_CTRL_CMD_HID_MASK | 0x12) /* 得到手柄键值函数*/
#define USBH_HID_USER_CTRL_CMD_JOYSTICK_ARG     (USB_USER_CTRL_CMD_HID_MASK | 0x13) /* 得到回调函数参数 */

#endif     //__DRV_UDISK_H__


