/*
********************************************************************************************************************
*                                              usb host driver
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : mscProtocol.c
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
#include  "usb_os_platform.h"
#include  "error.h"
#include  "usb_msc_i.h"
#include  "mscTransport.h"
#include  "mscProtocol.h"

/*
*******************************************************************************
*                     mscQIC157Command
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
int mscQIC157Command(__mscDev_t *mscDev, __ScsiCmnd_t *ScsiCmnd)
{
    if (mscDev == NULL || ScsiCmnd == NULL)
    {
        ////DMSG_PANIC("ERR: mscQIC157Command: mscDev = %x, ScsiCmnd = %x\n", mscDev, ScsiCmnd);
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* ÐÞÕýÃüÁî */
    //not support
    /* ´«Êä */
    return mscDev->Transport(mscDev, ScsiCmnd);
}


/*
*******************************************************************************
*                     mscATAPICommand
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
int mscATAPICommand(__mscDev_t *mscDev, __ScsiCmnd_t *ScsiCmnd)
{
    if (mscDev == NULL || ScsiCmnd == NULL)
    {
        ////DMSG_PANIC("ERR: mscATAPICommand: mscDev = %x, ScsiCmnd = %x\n", mscDev, ScsiCmnd);
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* ÐÞÕýÃüÁî */
    //not support
    /* ´«Êä */
    return mscDev->Transport(mscDev, ScsiCmnd);
}


/*
*******************************************************************************
*                     mscUFICommand
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
int mscUFICommand(__mscDev_t *mscDev, __ScsiCmnd_t *ScsiCmnd)
{
    if (mscDev == NULL || ScsiCmnd == NULL)
    {
        //DMSG_PANIC("ERR: mscUFICommand: mscDev = %x, ScsiCmnd = %x\n", mscDev, ScsiCmnd);
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* ÐÞÕýÃüÁî */
    //not support
    /* ´«Êä */
    return mscDev->Transport(mscDev, ScsiCmnd);
}


/*
*******************************************************************************
*                     mscScsiCommand
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
int mscScsiCommand(__mscDev_t *mscDev, __ScsiCmnd_t *ScsiCmnd)
{
    if (mscDev == NULL || ScsiCmnd == NULL)
    {
        //DMSG_PANIC("ERR: mscScsiCommand: mscDev = %x, ScsiCmnd = %x\n", mscDev, ScsiCmnd);
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* ÐÞÕýÃüÁî */
    //not support
    /* ´«Êä */
    return mscDev->Transport(mscDev, ScsiCmnd);
}


