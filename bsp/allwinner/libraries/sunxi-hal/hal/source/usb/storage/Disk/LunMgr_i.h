/*
********************************************************************************************************************
*                                              usb host driver
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : LunMgr_i.h
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
#ifndef  __LUNMGR_I_H__
#define  __LUNMGR_I_H__

int DiskProbe(__mscLun_t *mscLun);
int DiskRemove(__mscLun_t *mscLun);

int CDProbe(__mscLun_t *mscLun);
int CDRemove(__mscLun_t *mscLun);


#endif   //__LUNMGR_I_H__


