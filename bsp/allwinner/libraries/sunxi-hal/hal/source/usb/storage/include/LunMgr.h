/*
********************************************************************************************************************
*                                              usb host driver
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : LunMgr.h
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
#ifndef  __LUNMGR_H__
#define  __LUNMGR_H__

__mscLun_t *mscLun_alloc(void);
void  mscLun_free(__mscLun_t *mscLun);
__s32 mscLunAdd(__mscLun_t *mscLun);
__s32 mscLunDel(__mscLun_t *mscLun);


#endif   //__LUNMGR_H__



