/*
********************************************************************************************************************
*                                              usb host driver
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : LunMgr.c
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
#include  "Scsi2.h"
#include  "LunMgr.h"
#include  "LunMgr_i.h"

static void print_inquiry(__InquiryData_t *InquiryData)
{
    //DMSG_INFO("");
    //DMSG_INFO("------------------device infomation----------------------");
    //DMSG_INFO("Device_Type          = %d", InquiryData->Device_Type);
    //DMSG_INFO("Removable_Media      = %d", InquiryData->Removable_Media);
    //DMSG_INFO("ANSI_Version         = %d", InquiryData->ANSI_Version);
    //DMSG_INFO("ECMA_Version         = %d", InquiryData->ECMA_Version);
    //DMSG_INFO("ISO_Version          = %d", InquiryData->ISO_Version);
    //DMSG_INFO("Data_Format          = %d", InquiryData->Data_Format);
    //DMSG_INFO("Additional_Length    = %d", InquiryData->Additional_Length);
    //DMSG_INFO("Vendor_Info          = %s", InquiryData->Vendor_Info);
    //DMSG_INFO("Product_Info         = %s", InquiryData->Product_Info);
    //DMSG_INFO("Product_Revision     = %s", InquiryData->Product_Revision);
    //DMSG_INFO("--------------------------------------------------------");
    //DMSG_INFO("");
}

/*
*******************************************************************************
*                     mscLun_alloc
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
__mscLun_t *mscLun_alloc(void)
{
    __mscLun_t *mscLun = NULL;
    mscLun = hal_malloc(sizeof(__mscLun_t));

    if (mscLun == NULL)
    {
        hal_log_err("ERR: USB_OS_MALLOC failed");
        return NULL;
    }

    memset(mscLun, 0, sizeof(__mscLun_t));
    //--<2>--create lock
    mscLun->Lock = hal_sem_create(1);

    if (mscLun->Lock == NULL)
    {
        hal_log_err("ERR: UsbBlkDevAllocInit: create lock failed");
        hal_free(mscLun);
        return NULL;
    }

    return mscLun;
}

/*
*******************************************************************************
*                     mscLun_free
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
void mscLun_free(__mscLun_t *mscLun)
{
    __u8 err = 0;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: input error");
        return;
    }

    if (mscLun->Lock)
    {
        hal_sem_delete(mscLun->Lock);
        mscLun->Lock = NULL;
    }
    else
    {
        hal_log_err("ERR: BlkDev Lock had already delete");
    }

    hal_free(mscLun);
}


/*
*******************************************************************************
*                     mscLunAdd
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
__s32 mscLunAdd(__mscLun_t *mscLun)
{
    __mscDev_t      *mscDev         = NULL;
    __InquiryData_t *InquiryData    = NULL;
    __s32 ret = 0;
    __u32 i   = 0;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: MscLunAdd: input error");
        return USB_ERR_BAD_ARGUMENTS;
    }

    mscDev = mscLun->mscDev;

    if (mscDev == NULL)
    {
        hal_log_err("ERR: MscLunAdd: mscDev == NULL");
        return -1;
    }

    /* 获得LUN信息 */
    for (i = 0; i < 3; i++)
    {
        hal_sem_wait(mscLun->Lock);
        ret = ScsiInquery(mscLun, mscLun->Inquiry, SCSI_INQUERY_LEN);
        hal_sem_post(mscLun->Lock);

        if (ret == USB_STATUS_SUCCESS)
        {
            break;
        }
    }

    if (i >= 3)
    {
        hal_log_err("ERR: MscLunAdd: ScsiInquery failed");
        return USB_ERR_COMMAND_EXECUTE_FAILED;
    }

    /* 识别LUN */
    InquiryData = (__InquiryData_t *)mscLun->Inquiry;
    print_inquiry(InquiryData);
    mscLun->DeviceType  = InquiryData->Device_Type;
    mscLun->ScsiLevel   = InquiryData->ANSI_Version;
    mscLun->Vendor      = (__u8 *)InquiryData->Vendor_Info;
    mscLun->Product     = (__u8 *)InquiryData->Product_Info;
    mscLun->Revision    = (__u8 *)InquiryData->Product_Revision;
    mscLun->RemoveAble  = InquiryData->Removable_Media;

    switch (mscLun->DeviceType)
    {
        case SCSI_DEVICE_DIRECT_ACCESS:
            mscLun->Probe  = DiskProbe;
            mscLun->Remove = DiskRemove;
            break;

        case SCSI_DEVICE_CDROM:
            mscLun->Probe  = CDProbe;
            mscLun->Remove = CDRemove;
            break;

        default:
            hal_log_err("[Lun]: MscLunAdd: unknown device type %d", mscLun->DeviceType);
            return USB_ERR_UNKOWN_DEVICE;
    }

    /* LUN探测 */
    if (mscLun->Probe)
    {
        ret = mscLun->Probe(mscLun);

        if (ret != 0)
        {
            hal_log_err("[Lun]: MscLunAdd: Lun(%d) Probe fialed", mscLun->LunNo);
            return USB_ERR_DEVICE_PROBE_FAILED;
        }
    }

    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     mscLunDel
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
__s32 mscLunDel(__mscLun_t *mscLun)
{
    __s32 ret = 0;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: MscLunDel: input error");
        return USB_ERR_BAD_ARGUMENTS;
    }

    if (mscLun->Remove)
    {
        ret = mscLun->Remove(mscLun);

        if (ret != 0)
        {
            hal_log_err("[Lun]: MscLunAdd: Lun(%d) Remove fialed", mscLun->LunNo);
            return USB_ERR_DEVICE_REMOVE_FAILED;
        }
    }

    return USB_ERR_SUCCESS;
}




