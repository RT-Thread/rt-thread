/*
********************************************************************************************************************
*                                              usb_host
*
*                              (c) Copyright 2007-2009, javen.China
*                                       All Rights Reserved
*
* File Name     : usbh_disk_remove_time.h
*
* Author        : javen
*
* Version       : 1.0
*
* Date          : 2010.05.03
*
* Description   :
*
* History       :
*
********************************************************************************************************************
*/
#ifndef  __USBH_DISK_REMOVE_TIME_H__
#define  __USBH_DISK_REMOVE_TIME_H__

#define  USBH_DISK_REMOVE_TIME_UNIT         100

void usbh_disk_save_time(unsigned int time);
void usbh_disk_del_time(unsigned int time);
unsigned int get_max_disk_time(void);

void usbh_disk_time_init(void);
void usbh_disk_time_exit(void);


#endif   //__USBH_DISK_REMOVE_TIME_H__



