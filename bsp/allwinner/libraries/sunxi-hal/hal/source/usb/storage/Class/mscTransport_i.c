/*
********************************************************************************************************************
*                                              usb host driver
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : mscTransport_i.c
*
* Author        : javen
*
* Version       : 2.0
*
* Date          : 2010.7.12
*
* Description   :
*     USB Mass Storage Class传输容错辅助处理部分。
*
*     这部分主要是为了解决USB光驱中光盘突然弹出时，USB容错时间过长。其原因是Lun中media已经不存在，但是lun本身还在，
* 虽不可读/写数据，但是可以操作Lun。因此现在增加了在读写操作超时后，先去test_unit_ready，判断Lun的状态后，
* 再决定下一步的操作。
*
* History       :
*
********************************************************************************************************************
*/
#include  "usb_os_platform.h"
#include  "error.h"
#include  "usb_host_common.h"
#include  "urb.h"
#include  "usb_gen_hub.h"
#include  "usb_msc_i.h"
#include  "mscTransport.h"
#include  "Scsi2.h"

/*
*******************************************************************************
*                     mscTransportRequestSense
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
static int mscTransportRequestSense(__mscLun_t *mscLun, void *buffer, unsigned int buffer_len)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];
    unsigned int ret = 0;

    if (mscLun == NULL || buffer == NULL)
    {
//        printf("ERR: ScsiInquery: input error, mscLun = %x, buffer = %x\n", (unsigned int)mscLun, (unsigned int)buffer);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    if (buffer_len == 0)
    {
        printf("ERR: ScsiInquery: input error, buffer_len == %d\n", buffer_len);
        return USB_STATUS_BUFFER_TOO_SMALL;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_REQUEST_SENSE;             /* scsi command         */
    CB[1] = ((mscLun->LunNo & 0x7) << 5);   /* lun                  */
    CB[4] = buffer_len;                     /* Allocation Length    */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_FROM_DEVICE;
    ScsiCmnd.cmnd.Timeout       = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun         = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen         = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_6 : UFI_CDB;
    ScsiCmnd.cmnd.CommandBlock  = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = buffer_len;
    ScsiCmnd.buffer             = buffer;
    ret = mscBoTransport(mscLun->mscDev, &ScsiCmnd);
    return ret;
}

/*
*******************************************************************************
*                     mscTransportGetSenseData
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
static int mscTransportGetSenseData(__mscLun_t *mscLun)
{
    __SenseData_t SenseData;
    int ret = 0;
    memset(&SenseData, 0, sizeof(__SenseData_t));
    ret = mscTransportRequestSense(mscLun, (void *)&SenseData, sizeof(__SenseData_t));

    if (ret != USB_STOR_TRANSPORT_GOOD)
    {
        printf("ERR: mscTransportGetSenseData failed\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    printf("mscReason:SenseKey = %x, AdditionalSenseCode = %x\n",
               SenseData.SenseKey, SenseData.AdditionalSenseCode);

    switch (SenseData.SenseKey)
    {
        case SENSE_NONE :
            ret = USB_ERR_SUCCESS;
            break;

        case SENSE_NOT_READY :
            switch (SenseData.AdditionalSenseCode)
            {
                case ASC_MEDIUM_NOT_PRESENT :
                    printf("ERR: media is not present\n");
                    mscLun->MediaPresent = 0;
                    ret = USB_ERR_MEDIA_NOT_PRESENT;
                    break;

                default:
                    printf("ERR: unkown ASC(%d)\n", SenseData.AdditionalSenseCode);
                    ret = USB_ERR_UNKOWN_ERROR;
                    break;
            }

            break;

        case SENSE_ILLEGAL_REQUEST :
            ret = USB_ERR_NOT_SUPPORT_COMMAND;
            break;

        case SENSE_UNIT_ATTENTION :
            switch (SenseData.AdditionalSenseCode)
            {
                case ASC_MEDIUM_NOT_PRESENT :
                    printf("ERR: media is not present\n");
                    mscLun->MediaPresent = 0;
                    ret = USB_ERR_MEDIA_NOT_PRESENT;
                    break;

                default:
                    printf("ERR: unkown ASC(%d)\n", SenseData.AdditionalSenseCode);
                    ret = USB_ERR_UNKOWN_ERROR;
            }

            break;

        default:
            ret = USB_ERR_UNKOWN_ERROR;
    }

    return ret;
}

/*
*******************************************************************************
*                     mscGetDataTransportReason
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
int mscGetDataTransportReason(__mscLun_t *mscLun, __ScsiCmnd_t *ScsiCmnd)
{
    int ret = USB_ERR_COMMAND_NEED_RETRY;
    unsigned char  Command = 0;
    int status = 0;

    if (mscLun == NULL || ScsiCmnd == NULL)
    {
        printf("ERR: input error\n");
        return USB_ERR_COMMAND_NEED_RETRY;
    }

    status = mscTransportGetSenseData(mscLun);

    if (status == USB_ERR_MEDIA_NOT_PRESENT || status == USB_ERR_NOT_SUPPORT_COMMAND)
    {
        Command = ((unsigned char *)(ScsiCmnd->cmnd.CommandBlock))[0];

        if (Command == SCSI_READ6 || Command == SCSI_READ10 || Command == SCSI_READ16
            || Command == SCSI_WRITE6 || Command == SCSI_WRITE10 || Command == SCSI_WRITE16)
        {
            printf("ERR: Command(%x) execute failed, for media is not present\n", Command);
            ret = USB_ERR_COMMAND_EXECUTE_FAILED;
        }
    }

    return ret;
}

