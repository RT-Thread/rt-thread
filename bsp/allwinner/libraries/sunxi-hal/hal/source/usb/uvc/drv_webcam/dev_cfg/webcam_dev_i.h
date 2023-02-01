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

#ifndef _WEBCAM_DEV_I_H
#define _WEBCAM_DEV_I_H

#include "dev_webcam_i.h"


extern __webcam_mode_t webcam_mode;                                 //符合用户设置的当前的webcam_mode
extern __webcam_mode_all_t webcam_mode_all;                         //所有设置的webcam_mode


extern __s32  webcam_dev_init(void);

extern __s32  webcam_dev_exit(void);

extern __s32 webcam_dev_set_mode(__u32 mode);

#endif

