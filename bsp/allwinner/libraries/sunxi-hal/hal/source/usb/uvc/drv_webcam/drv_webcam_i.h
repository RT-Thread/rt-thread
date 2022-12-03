/*
*********************************************************************************************************
*                                                    MELIS
*                                    the Easy Portable/Player Develop Kits
*                                                 WEBCAM Driver
*
*                                    (c) Copyright 2012-2016, Kingvan.Tong China
*                                             All Rights Reserved
*
* File    : drv_webcam.h
* By      : Kingvan
* Version : v1.0
* Date    : 2012-9-27
* Descript:
* Update  : date                auther         ver     notes
*           2012-9-27 11:09:13  Kingvan.Tong   2.0     build the file.
*********************************************************************************************************
*/
#ifndef  __DRV_WEBCAM_I_H__
#define  __DRV_WEBCAM_I_H__
#include "typedef.h"
#include "sys_device.h"
#include "hal_log.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "string.h"
#include <hal_osal.h>
#include <rtthread.h>

typedef struct tag_WEBCAM_DRV
{
    __u32           mid;
    __u32           used;               //表示向drv注册了多少个设备节点
    __hdle          hReg_WebcamDevHdl;     //hReg;   //webcam_dev_hdl
    __dev_devop_t   webcam_dev_entry;
}__webcam_drv_t;


__s32 DRV_WEBCAM_MInit(void);
//extern __s32   DRV_WEBCAM_MExit(void);
//extern __mp*   DRV_WEBCAM_MOpen(__u32 mid, __u32 mode);
//extern __s32   DRV_WEBCAM_MClose(__mp *mp);
//extern __u32   DRV_WEBCAM_MRead(void *pdata, __u32 size, __u32 n, __mp *mp);
//extern __u32   DRV_WEBCAM_MWrite(const void *pdata, __u32 size, __u32 n, __mp *mp);
//extern __s32   DRV_WEBCAM_MIoctrl(__mp *mp, __u32 cmd, __s32 aux, void *pbuffer);

#endif /*__DRV_WEBCAM_I_H__*/


