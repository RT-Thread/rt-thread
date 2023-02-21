/*
********************************************************************************************************************
*                                              usb host driver
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : Scsi2.c
*
* Author        : javen
*
* Version       : 2.0
*
* Date          : 2010.03.02
*
* Description   : scsi command
*
* History       :
*
********************************************************************************************************************
*/
#include  "usb_os_platform.h"
#include  "error.h"
#include  "usb_msc_i.h"
#include  "Scsi2.h"

static int ScsiGetSenseData(__mscLun_t *mscLun);

void Scsi2_show_command(__ScsiCmnd_t *ScsiCmnd)
{
#if 0
    char *what = NULL;
    int i;
    unsigned char *CB = NULL;
    CB = (unsigned char *)ScsiCmnd->cmnd.CommandBlock;

    switch (CB[0])
    {
        case SCSI_TEST_UNIT_READY:
            what = "TEST_UNIT_READY";
            break;

        case SCSI_REQUEST_SENSE:
            what = "REQUEST_SENSE";
            break;

        case SCSI_READ6:
            what = "READ_6";
            break;

        case SCSI_WRITE6:
            what = "WRITE_6";
            break;

        case SCSI_INQUIRY:
            what = "INQUIRY";
            break;

        case SCSI_MODE_SELECT6:
            what = "MODE_SELECT";
            break;

        case SCSI_MODE_SELECT10:
            what = "MODE_SELECT";
            break;

        case SCSI_MODE_SENSE6:
            what = "MODE_SENSE";
            break;

        case SCSI_MODE_SENSE10:
            what = "MODE_SENSE";
            break;

        case SCSI_START_STOP:
            what = "START_STOP";
            break;

        case SCSI_READ_CAPACITY:
            what = "READ_CAPACITY";
            break;

        case SCSI_READ10:
            what = "READ_10";
            break;

        case SCSI_WRITE10:
            what = "WRITE_10";
            break;

        case SCSI_SYNCHRONIZE_CACHE:
            what = "SYNCHRONIZE_CACHE";
            break;

        /* CD */
        case SCSI_CD_READ_TOC:
            what = "READ HEADER";
            break;

//        case SCSI_CD_PLAY10:
//            what = "PLAY AUDIO (10)";
//            break;

//        case SCSI_CD_PLAY_MSF:
//            what = "PLAY AUDIO MSF";
//            break;

        case SCSI_CD_PAUSE_RESUME:
            what = "GET EVENT/STATUS NOTIFICATION";
            break;

        default:
            what = "(unknown command)";
            break;
    }

    hal_log_info("");
    hal_log_info("Command name =  %s (%d bytes)", what, ScsiCmnd->cmnd.CBLen);

    for (i = 0; i < ScsiCmnd->cmnd.CBLen && i < MAX_CDB; i++)
    {
        hal_log_info(" %x ", CB[i]);
    }

    hal_log_info("allowed   = %d", ScsiCmnd->allowed);
    hal_log_info("TransLen  = %d", ScsiCmnd->DataTransferLength);
    hal_log_info("direction = %s", (ScsiCmnd->cmnd.data_direction == DATA_FROM_DEVICE)
              ? "DATA_FROM_DEVICE" : "DATA_TO_DEVICE");
    hal_log_info("Tag       = %x", ScsiCmnd->cmnd.Tag);
    hal_log_info("Timeout   = %d", ScsiCmnd->cmnd.Timeout);
    hal_log_info("dwLun     = %d", ScsiCmnd->cmnd.dwLun);
    hal_log_info("CB_ADDR   = %x", ScsiCmnd->cmnd.CommandBlock);
    hal_log_info("");
#endif
}

static void ScsiCmndDone(__ScsiCmnd_t *ScsiCmnd)
{
    hal_sem_post(ScsiCmnd->complete);
}

/*
*******************************************************************************
*                     ScsiDoCommand
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
static int ScsiDoCommand(__mscLun_t *mscLun, __ScsiCmnd_t *ScsiCmnd)
{
    unsigned int ret = 0;

    if (mscLun == NULL || ScsiCmnd == NULL)
    {
        hal_log_err("ERR: ScsiDoCommand: input error, mscLun = %x, ScsiCmd == %x", mscLun, ScsiCmnd);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    ScsiCmnd->complete = hal_sem_create(0);

    if (ScsiCmnd->complete == NULL)
    {
        hal_log_err("ERR: ScsiDoCommand: hal_sem_createfailed");
        return USB_STATUS_UNKOWN_ERROR;
    }

    Scsi2_show_command(ScsiCmnd);
    /* do scsi command */
    ret = mscDevQueueCmnd(mscLun, ScsiCmnd);

    if (ret != USB_ERR_SUCCESS)
    {
        hal_log_err("ERR: mscDevQueueCmnd failed");
        goto Next;
    }

scsidone:
    /* wait for complete */
    ret = hal_sem_wait(ScsiCmnd->complete);
    if (ret != 0)
    {
        hal_log_err("wait scsi done again!");
        goto scsidone;
    }

Next:
    hal_sem_delete(ScsiCmnd->complete);
    ScsiCmnd->complete = NULL;

    switch (ScsiCmnd->Result)
    {
        case USB_STOR_TRANSPORT_GOOD:
            ret = USB_STATUS_SUCCESS;
            break;

        case USB_STOR_TRANSPORT_FAILED:
            ret = ScsiGetSenseData(mscLun);
            break;

        case USB_STOR_TRANSPORT_ERROR:
            ret = USB_STATUS_COMMAND_FAILED;
            break;

        default:
            hal_log_err("ERR: ScsiDoCommand: unkown command result %d", ScsiCmnd->Result);
            ret = USB_STATUS_COMMAND_FAILED;
    }

    return ret;
}


/*
*******************************************************************************
*                     ScsiInquery
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
int ScsiInquery(__mscLun_t *mscLun, void *buffer, unsigned int buffer_len)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL || buffer == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x, buffer = %x", mscLun, buffer);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    if (buffer_len == 0)
    {
        hal_log_err("ERR: ScsiInquery: input error, buffer_len == %d", buffer_len);
        return USB_STATUS_BUFFER_TOO_SMALL;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_INQUIRY;                   /* scsi command         */
    CB[1] = ((mscLun->LunNo & 0x7) << 5);   /* lun                  */
    CB[4] = buffer_len;                     /* Allocation Length    */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction = DATA_FROM_DEVICE;
    ScsiCmnd.cmnd.Timeout        = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun          = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen          = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_6 : UFI_CDB;
    ScsiCmnd.cmnd.CommandBlock   = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = buffer_len;
    ScsiCmnd.buffer             = buffer;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}

/*
*******************************************************************************
*                     ScsiReadCapacity
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
int ScsiReadCapacity(__mscLun_t *mscLun)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];
    unsigned char buffer[8];
    int ret = 0;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_READ_CAPACITY;             /* scsi command         */
    CB[1] = ((mscLun->LunNo & 0x7) << 5);   /* lun                  */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_FROM_DEVICE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : UFI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = 8;
    ScsiCmnd.buffer             = buffer;
    ScsiCmnd.Done               = ScsiCmndDone;
    /* parse read capacity data */
    ret = ScsiDoCommand(mscLun, &ScsiCmnd);

    if (ret == USB_STATUS_SUCCESS)
    {
        mscLun->disk_info.capacity    = get_be32(buffer) + 1;
        mscLun->disk_info.sector_size = get_be32(buffer + 4);
    }
    else
    {
        mscLun->disk_info.capacity    = 0;
        mscLun->disk_info.sector_size = 512;
    }

    return ret;
}

/*
*******************************************************************************
*                     ScsiModeSense6
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
int ScsiModeSense6(__mscLun_t *mscLun,
                     unsigned int PageCode,
                     unsigned int DBD,
                     void *buffer,
                     unsigned int buffer_len,
                     unsigned int *ActLen)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];
    int ret = 0;

    if (mscLun == NULL || buffer == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x, buffer = %x", mscLun, buffer);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    if (buffer_len == 0)
    {
        hal_log_err("ERR: ScsiInquery: input error, buffer_len == %d", buffer_len);
        return USB_STATUS_BUFFER_TOO_SMALL;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_MODE_SENSE6;                       /* scsi command         */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                  */
    CB[1] = CB[1] | (DBD << 3);                     /* dbd                  */
    CB[2] = PageCode;                               /* Page Code            */
    CB[4] = buffer_len;                             /* Allocation Length    */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_FROM_DEVICE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_6 : UFI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = buffer_len;
    ScsiCmnd.buffer             = buffer;
    ScsiCmnd.Done               = ScsiCmndDone;
    ret = ScsiDoCommand(mscLun, &ScsiCmnd);

    if (ret == USB_ERR_SUCCESS)
    {
        *ActLen = ScsiCmnd.ActualLength;
    }
    else
    {
        *ActLen = 0;
    }

    return ret;
}

/*
*******************************************************************************
*                     ScsiModeSense10
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
int ScsiModeSense10(__mscLun_t *mscLun,
                      unsigned int PageCode,
                      unsigned int DBD,
                      void *buffer,
                      unsigned int buffer_len,
                      unsigned int *ActLen)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];
    int ret = 0;

    if (mscLun == NULL || buffer == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x, buffer = %x", mscLun, buffer);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    if (buffer_len == 0)
    {
        hal_log_err("ERR: ScsiInquery: input error, buffer_len == %d", buffer_len);
        return USB_STATUS_BUFFER_TOO_SMALL;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_MODE_SENSE10;                      /* scsi command         */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                  */
    CB[1] = CB[1] | (DBD << 3);                     /* dbd                  */
    CB[2] = PageCode;                               /* Page Code            */
    put_be16(&CB[7], buffer_len);                   /* Allocation Length    */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_FROM_DEVICE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : UFI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = buffer_len;
    ScsiCmnd.buffer             = buffer;
    ScsiCmnd.Done               = ScsiCmndDone;
    ret = ScsiDoCommand(mscLun, &ScsiCmnd);

    if (ret == USB_ERR_SUCCESS)
    {
        *ActLen = ScsiCmnd.ActualLength;
    }
    else
    {
        *ActLen = 0;
    }

    return ret;
}

/*
*******************************************************************************
*                     ScsiTestUnitReady
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
int ScsiTestUnitReady(__mscLun_t *mscLun)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];
    int ret = 0;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_TEST_UNIT_READY;                   /* scsi command         */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                  */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_NONE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_6 : UFI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = 0;
    ScsiCmnd.buffer             = NULL;
    ScsiCmnd.Done               = ScsiCmndDone;
    ret = ScsiDoCommand(mscLun, &ScsiCmnd);
    /*
        if((ret == USB_STATUS_SUCCESS && !(mscLun->MediaPresent))){
            DMSG_INFO("mscLun Media not Present, but test unit ready command is successful");
            mscLun->MediaPresent = 1;
        }else if((ret == USB_STATUS_MEDIA_NOT_PRESENT)
                 && (ret == USB_STATUS_UNIT_NOT_READY)
                 && (ret == USB_STATUS_UNRECOGNIZED_MEDIA)
                 && (ret == USB_STATUS_MEDIA_CHANGE)){
            mscLun->MediaPresent = 0;
        }
    */
    return ret;
}

/*
*******************************************************************************
*                     ScsiRequestSense
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
int ScsiRequestSense(__mscLun_t *mscLun, void *buffer, unsigned int buffer_len)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];
    unsigned char err = 0;
    unsigned int ret = 0;

    if (mscLun == NULL || buffer == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x, buffer = %x", mscLun, buffer);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    if (buffer_len == 0)
    {
        hal_log_err("ERR: ScsiInquery: input error, buffer_len == %d", buffer_len);
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
    ScsiCmnd.Done               = ScsiCmndDone;
    /* do command */
    ScsiCmnd.complete = hal_sem_create(0);

    if (ScsiCmnd.complete == NULL)
    {
        hal_log_err("ERR: ScsiDoCommand: hal_sem_createfailed");
        return USB_STATUS_UNKOWN_ERROR;
    }

    ret = mscDevQueueCmnd(mscLun, &ScsiCmnd);

    if (ret != USB_ERR_SUCCESS)
    {
        hal_log_err("ERR: mscDevQueueCmnd failed");
        goto Next;
    }

    /* wait for complete */
    hal_sem_wait(ScsiCmnd.complete);
Next:
    hal_sem_delete(ScsiCmnd.complete);
    ScsiCmnd.complete = NULL;

    switch (ScsiCmnd.Result)
    {
        case USB_STOR_TRANSPORT_GOOD:
            ret = USB_STATUS_SUCCESS;
            break;

        case USB_STOR_TRANSPORT_FAILED:
            ret = USB_STATUS_UNKOWN_ERROR;
            break;

        case USB_STOR_TRANSPORT_ERROR:
            ret = USB_STATUS_COMMAND_FAILED;
            break;

        default:
            hal_log_err("ERR: ScsiDoCommand: unkown command result %d", ScsiCmnd.Result);
            ret = USB_STATUS_COMMAND_FAILED;
    }

    return ret;
}

/*
*******************************************************************************
*                     ScsiGetSenseData
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
static int ScsiGetSenseData(__mscLun_t *mscLun)
{
    __SenseData_t SenseData;
    int ret = 0;
    memset(&SenseData, 0, sizeof(__SenseData_t));
    ret = ScsiRequestSense(mscLun, (void *)&SenseData, sizeof(__SenseData_t));

    if (ret != USB_STATUS_SUCCESS)
    {
        hal_log_err("ERR: ScsiRequestSense failed");
        return USB_STATUS_UNKOWN_ERROR;
    }

    hal_log_info("SenseKey = %x, AdditionalSenseCode = %x", SenseData.SenseKey, SenseData.AdditionalSenseCode);

    switch (SenseData.SenseKey)
    {
        case SENSE_NONE :
            ret = USB_STATUS_SUCCESS;
            break;

        case SENSE_NOT_READY :
            switch (SenseData.AdditionalSenseCode)
            {
                case ASC_LUN:
                    if (0x02 == SenseData.AdditionalSenseCodeQualifier)   // Initialization Required
                    {
                        ScsiStartStopUnit(mscLun, 0, 1);
                    }

                    if (0x01 == SenseData.AdditionalSenseCodeQualifier)   /* not ready to ready */
                    {
                        ret = USB_STATUS_NOT_READY_TO_READY_TRANSITION;
                    }
                    else
                    {
                        ret = USB_STATUS_UNIT_NOT_READY;
                    }

                    break;

                case ASC_MEDIUM_NOT_PRESENT :
                    hal_log_info("ERR: media is not present");
                    mscLun->MediaPresent = 0;
                    ret = USB_STATUS_MEDIA_NOT_PRESENT;
                    break;

                default:
                    hal_log_info("ERR: unkown ASC(%d)", SenseData.AdditionalSenseCode);
                    ret = USB_STATUS_UNIT_NOT_READY;
                    break;
            }

            break;

        case SENSE_MEDIUM_ERROR :
            ret = USB_STATUS_UNRECOGNIZED_MEDIA;
            break;

        case SENSE_HARDWARE_ERROR :
            ret = USB_STATUS_UNRECOGNIZED_MEDIA;
            break;

        case SENSE_ILLEGAL_REQUEST :
            ret = USB_STATUS_INVALID_FIELD_IN_COMMAND;
            break;

        case SENSE_UNIT_ATTENTION :
            switch (SenseData.AdditionalSenseCode)
            {
                case ASC_MEDIA_CHANGED :
                    hal_log_info("ERR: media not ready to ready transition");
                    ret = USB_STATUS_NOT_READY_TO_READY_TRANSITION;
                    break;

                /* 见到sandisk的U盘，竟然在SENSE_UNIT_ATTENTION时, 说ASC_MEDIUM_NOT_PRESENT。
                   为了处理这样的U盘, 这里也检查ASC_MEDIUM_NOT_PRESENT */
                case ASC_MEDIUM_NOT_PRESENT :
                    hal_log_info("ERR: media is not present");
                    mscLun->MediaPresent = 0;
                    ret = USB_STATUS_MEDIA_NOT_PRESENT;
                    break;

                default:
                    hal_log_info("ERR: unkown ASC(%d)", SenseData.AdditionalSenseCode);
                    ret = USB_STATUS_UNKOWN_SENSE;
            }

            break;

        default:
            ret = USB_STATUS_UNKOWN_SENSE;
    }

    return ret;
}

/*
*******************************************************************************
*                     ScsiStartStopUnit
*
* Description:
*    开始 / 停止 设备工作
*
* Parameters:
*    mscLun  : input.  命令发向的设备
*    LoEj    : input.  加载/弹出 媒体介质
*    Start   : input.  开始 / 停止 设备工作
*
* Return value:
*
*
* note:
*
*
*******************************************************************************
*/
int ScsiStartStopUnit(__mscLun_t *mscLun, unsigned int LoEj, unsigned int Start)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_START_STOP;                        /* scsi command         */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                  */
    CB[4] = Start;
    CB[4] = CB[4] | (LoEj << 1);
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_NONE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_6 : UFI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = 0;
    ScsiCmnd.buffer             = NULL;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}

/*
*******************************************************************************
*                     SynchronizeCache
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
int ScsiSynchronizeCache(__mscLun_t *mscLun)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_SYNCHRONIZE_CACHE;                 /* scsi command         */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                  */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_NONE;
    ScsiCmnd.cmnd.Timeout           = SCSI_MEDIA_OP_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : UFI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = 0;
    ScsiCmnd.buffer             = NULL;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}

/*
*******************************************************************************
*                     ScsiRead
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
int ScsiRead(__mscLun_t *mscLun,
               unsigned int Version,
               unsigned int StartSector,
               unsigned int NumSectors,
               void *buffer,
               unsigned int buffer_len)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);

    /* create command block */
    if (Version == 16)
    {
        hal_log_err("ERR: read16 not support");
        ScsiCmnd.cmnd.CBLen = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_16 : UFI_CDB;
        return USB_STATUS_INVALID_COMMAND;
    }
    else if (Version == 10)
    {
        CB[0] = SCSI_READ10;                            /* scsi command         */
        CB[1] = ((mscLun->LunNo & 0x7) << 5);           /* lun                  */
        put_be32(&CB[2], StartSector);                  /* LOGICAL BLOCK ADDRESS */
        put_be16(&CB[7], NumSectors);                   /* TRANSFER LENGTH      */
        ScsiCmnd.cmnd.CBLen = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : UFI_CDB;
    }
    else
    {
        CB[0] = SCSI_READ6;                             /* scsi command         */
        CB[1] = ((mscLun->LunNo & 0x7) << 5);           /* lun                  */
        CB[1] = (unsigned char)(StartSector >> 16) & 0x1f;       /* LOGICAL BLOCK ADDRESS */
        put_be16(&CB[2], (__u16)StartSector);
        CB[4] = NumSectors;                             /* TRANSFER LENGTH      */
        ScsiCmnd.cmnd.CBLen = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_6 : UFI_CDB;
    }

    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_FROM_DEVICE;
    ScsiCmnd.cmnd.Timeout           = SCSI_MEDIA_OP_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = buffer_len;
    ScsiCmnd.buffer             = buffer;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}

/*
*******************************************************************************
*                     ScsiWrite
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
int ScsiWrite(__mscLun_t *mscLun,
                unsigned int Version,
                unsigned int StartSector,
                unsigned int NumSectors,
                void *buffer,
                unsigned int buffer_len)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);

    /* create command block */
    if (Version == 16)
    {
        hal_log_err("ERR: read16 not support");
        ScsiCmnd.cmnd.CBLen = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_16 : UFI_CDB;
        return USB_STATUS_INVALID_COMMAND;
    }
    else if (Version == 10)
    {
        CB[0] = SCSI_WRITE10;                           /* scsi command         */
        CB[1] = ((mscLun->LunNo & 0x7) << 5);           /* lun                  */
        put_be32(&CB[2], StartSector);                  /* LOGICAL BLOCK ADDRESS */
        put_be16(&CB[7], NumSectors);                   /* TRANSFER LENGTH      */
        ScsiCmnd.cmnd.CBLen = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : UFI_CDB;
    }
    else
    {
        CB[0] = SCSI_WRITE6;                            /* scsi command         */
        CB[1] = ((mscLun->LunNo & 0x7) << 5);           /* lun                  */
        CB[1] = (unsigned char)(StartSector >> 16) & 0x1f;       /* LOGICAL BLOCK ADDRESS */
        put_be16(&CB[2], (__u16)StartSector);
        CB[4] = NumSectors;                             /* TRANSFER LENGTH      */
        ScsiCmnd.cmnd.CBLen = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_6 : UFI_CDB;
    }

    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_TO_DEVICE;
    ScsiCmnd.cmnd.Timeout           = SCSI_MEDIA_OP_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = buffer_len;
    ScsiCmnd.buffer             = buffer;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}

/*
*******************************************************************************
*                     ScsiPreventAllowMedium
*
* Description:
*     禁止/允许介质移动
*
* Parameters:
*    mscLun     :  input. 目标设备
*    Persistent :  input. 禁止介质数据传输
*    Prevent    :  input. 禁止介质移动
*
*
* Return value:
*    返回命令的执行结果
*
* note:
*    Persistent只能在设备枚举的时候设置, 在设备操作阶段不要使用。
*
*******************************************************************************
*/
int ScsiPreventAllowMedium(__mscLun_t *mscLun, unsigned int Persistent, unsigned int Prevent)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_DVD_PREVENT_ALLOW_MEDIUM_REMOVAL;  /* scsi command         */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                  */
    CB[4] = CB[4] | (Persistent << 1);              /* persistent           */
    CB[4] = CB[4] | (Prevent << 0);                 /* prevent              */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_NONE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : UFI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = 0;
    ScsiCmnd.buffer             = NULL;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}

/*
*******************************************************************************
*                     ScsiCDPauseResume
*
* Description:
*    停止/恢复播放CD media
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
int ScsiCDPauseResume(__mscLun_t *mscLun, unsigned int Resume)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_CD_PAUSE_RESUME;                   /* scsi command         */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                  */
    CB[8] = Resume & 0x01;                          /* Resume bit           */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_NONE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : ATAPI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = 0;
    ScsiCmnd.buffer             = NULL;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}

/*
*******************************************************************************
*                     ScsiCDPlayAudio10
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
int ScsiCDPlayAudio10(__mscLun_t *mscLun, unsigned int Lba, unsigned int Lenght)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_CD_PLAY_AUDIO10;                   /* scsi command                 */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                          */
    put_be32(&CB[2], Lba);                          /* Start LOGICAL BLOCK ADDRESS  */
    put_be16(&CB[7], Lenght);                       /* TRANSFER LENGTH              */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_NONE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : ATAPI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = 0;
    ScsiCmnd.buffer             = NULL;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}

/*
*******************************************************************************
*                     ScsiCDPlayAudioMSF
*
* Description:
*    播放指定mfs的音乐光碟
*
* Parameters:
*    mscLun         :  input. Logic unit
*    MSF            :  input. 多扇区
*
* Return value:
*    返回命令的执行情况
*
* note:
*
*
*******************************************************************************
*/
int ScsiCDPlayAudioMSF(__mscLun_t *mscLun, CDROM_PlayAudioMsf_t *MSF)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_CD_PLAY_AUDIO_MSF;                 /* scsi command                 */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                          */
    CB[3] = MSF->StartingM;
    CB[4] = MSF->StartingS;
    CB[5] = MSF->StartingF;
    CB[6] = MSF->EndingM;
    CB[7] = MSF->EndingS;
    CB[8] = MSF->EndingF;
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_NONE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : ATAPI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = 0;
    ScsiCmnd.buffer             = NULL;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}

/*
*******************************************************************************
*                     ScsiCDReadToc
*
* Description:
*    读取介质内容的分配表信息
*
* Parameters:
*    mscLun         :  input. Logic unit
*    MSF            :  input. 多扇区
*    Format         :  input. 数据格式化模式
*    StartingNumber :  input. 起始扇区
*    Buffer         :  input. 缓冲区。存放命令执行的结果
*    BufferLen      :  input. 缓冲区大小
*
* Return value:
*    返回命令的执行情况
*
* note:
*
*
*******************************************************************************
*/
int ScsiCDReadToc(__mscLun_t *mscLun,
                    unsigned int MSF,
                    unsigned int Format,
                    unsigned int StartingNumber,
                    void *Buffer,
                    unsigned int BufferLen)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_CD_READ_TOC;                       /* scsi command                     */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                              */
    CB[1] = CB[1] | ((MSF ? 0 : 1) << 1);           /* is Msf?                          */
    CB[2] = CB[2] | (Format & 0x07);                /* Read TOC Data Format             */
    CB[6] = StartingNumber;                         /* Starting Track/Session Number    */
    put_be16(&CB[7], BufferLen);                    /* TRANSFER LENGTH                  */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_FROM_DEVICE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : ATAPI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = BufferLen;
    ScsiCmnd.buffer             = Buffer;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}

/*
*******************************************************************************
*                     ScsiCDStopPlayScan
*
* Description:
*    中止扫描或是播放
*
* Parameters:
*    mscLun         :  input. Logic unit
*
* Return value:
*    返回命令的执行情况
*
* note:
*
*
*******************************************************************************
*/
int ScsiCDStopPlayScan(__mscLun_t *mscLun)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_CD_STOP_PLAY_SCAN;                 /* scsi command                 */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                          */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_NONE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : ATAPI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = 0;
    ScsiCmnd.buffer             = NULL;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}

/*
*******************************************************************************
*                     ScsiCDReadDiskInfo
*
* Description:
*    读取光碟的信息
*
* Parameters:
*    mscLun         :  input. Logic unit
*    Buffer         :  input. 缓冲区。存放disk的信息
*    BufferLen      :  input. 本次打算获得数据的长度
*
* Return value:
*    返回命令的执行情况
*
* note:
*
*
*******************************************************************************
*/
int ScsiCDReadDiscInfo(__mscLun_t *mscLun,
                         unsigned int DataType,
                         void *Buffer,
                         unsigned int BufferLen,
                         unsigned int *ActLen)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];
    int ret = 0;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_DVD_READ_DISC_INFORMATION;         /* scsi command                 */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                          */
    CB[1] = CB[1] | (DataType & 0x07);
    put_be16(&CB[7], BufferLen);                    /* TRANSFER LENGTH              */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_FROM_DEVICE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : ATAPI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = BufferLen;
    ScsiCmnd.buffer             = Buffer;
    ScsiCmnd.Done               = ScsiCmndDone;
    ret = ScsiDoCommand(mscLun, &ScsiCmnd);

    if (ret == USB_ERR_SUCCESS)
    {
        *ActLen = ScsiCmnd.ActualLength;
    }
    else
    {
        *ActLen = 0;
    }

    return ret;
}

/*
*******************************************************************************
*                     ScsiCDReadTrackInfo
*
* Description:
*    读取光碟轨道的信息
*
* Parameters:
*    mscLun             :  input. Logic unit
*    Open               :  input.
*    Address_or_Number  :  input.
*    LogicalBlockAddress:  input.
*    Buffer             :  input. 缓冲区。存放disk的信息
*    BufferLen          :  input. 本次打算获得数据的长度
*    ActLen             :  input. 实际取得的长度
*
* Return value:
*    返回命令的执行情况
*
* note:
*
*
*******************************************************************************
*/
int ScsiCDReadTrackInfo(__mscLun_t *mscLun,
                          unsigned int Open,
                          unsigned int Address_or_Number,
                          unsigned int LogicalBlockAddress,
                          void *Buffer,
                          unsigned int BufferLen,
                          unsigned int *ActLen)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];
    int ret = 0;

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_DVD_READ_TRACK_INFORMATION;        /* scsi command                 */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                          */
    CB[1] = CB[1] | (Open ? 1 : 0);
    CB[1] = CB[1] | (Address_or_Number & 0x03);
    put_be16(&CB[7], BufferLen);                    /* TRANSFER LENGTH              */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_FROM_DEVICE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : ATAPI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = BufferLen;
    ScsiCmnd.buffer             = Buffer;
    ScsiCmnd.Done               = ScsiCmndDone;
    ret = ScsiDoCommand(mscLun, &ScsiCmnd);

    if (ret == USB_ERR_SUCCESS)
    {
        *ActLen = ScsiCmnd.ActualLength;
    }
    else
    {
        *ActLen = 0;
    }

    return ret;
}

/*
*******************************************************************************
*                     ScsiDvdGetEventStatus
*
* Description:
*    获得DVD的事件状态。
*
* Parameters:
*    mscLun         :  input. Logic unit
*    Immed          :  input. 是否立即返回命令的执行结果
*    ClassRequest   :  input. 类请求
*    Buffer         :  input. 存放DVD的事件结果
*    BufferLen      :  input. 本次打算获得数据的长度
*
* Return value:
*    返回命令的执行情况
*
* note:
*
*
*******************************************************************************
*/
int ScsiDvdGetEventStatus(__mscLun_t *mscLun,
                            unsigned int Immed,
                            unsigned int ClassRequest,
                            void *Buffer,
                            unsigned int BufferLen)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_DVD_GET_EVENT_STATUS_NOTIFICATION; /* scsi command                 */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                          */
    CB[1] = CB[1] | (Immed ? 1 : 0);
    CB[4] = ClassRequest;                           /* Notification Class Request   */
    put_be16(&CB[7], BufferLen);                    /* TRANSFER LENGTH              */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_FROM_DEVICE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : ATAPI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = BufferLen;
    ScsiCmnd.buffer             = Buffer;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}

/*
*******************************************************************************
*                     ScsiDvdGetEventStatus
*
* Description:
*    装载或是卸载光碟
*
* Parameters:
*    mscLun :  input. Logic unit
*    Immed  :  input. 是否立即返回命令的执行结果
*    Start  :  input. media就绪或者停止
*    LoUnlo :  input. 装载或是卸载
*    Slot   :  input.
*
* Return value:
*    返回命令的执行情况
*
* note:
*
*
*******************************************************************************
*/
int ScsiDvdLoad(__mscLun_t *mscLun,
                  unsigned int Immed,
                  unsigned int Start,
                  unsigned int LoUnlo,
                  unsigned int Slot)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_DVD_LOAD_UNLOAD;                   /* scsi command                 */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                          */
    CB[1] = CB[1] | (Immed ? 1 : 0);
    CB[4] = CB[4] | (Start ? 1 : 0);
    CB[4] = CB[4] | ((LoUnlo ? 1 : 0) << 1);
    CB[8] = Slot;
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_FROM_DEVICE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : ATAPI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = 0;
    ScsiCmnd.buffer             = NULL;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}

/*
*******************************************************************************
*                     ScsiSetSpeed
*
* Description:
*    设置光驱的读写速度
*
* Parameters:
*    mscLun     :  input. Logic unit
*    ReadSpeed  :  input. 读速度. Kbytes/second
*    WriteSpeed :  input. 写速度. Kbytes/second
*
* Return value:
*    返回命令的执行情况
*
* note:
*
*
*******************************************************************************
*/
int ScsiCDSetSpeed(__mscLun_t *mscLun, unsigned int ReadSpeed, unsigned int WriteSpeed)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_CD_SET_SPEED;                      /* scsi command                 */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                          */
    put_be16(&CB[2], ReadSpeed);
    put_be16(&CB[4], WriteSpeed);
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_NONE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : ATAPI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = 0;
    ScsiCmnd.buffer             = NULL;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}

/*
*******************************************************************************
*                     ScsiGetConfiguration
*
* Description:
*    设置光驱的读写速度
*
* Parameters:
*    mscLun     :  input. Logic unit
*    ReadSpeed  :  input. 读速度. Kbytes/second
*    WriteSpeed :  input. 写速度. Kbytes/second
*
* Return value:
*    返回命令的执行情况
*
* note:
*
*
*******************************************************************************
*/
int ScsiDVDGetConfiguration(__mscLun_t *mscLun,
                              unsigned int RT,
                              unsigned int StartingFeatureNumber,
                              void *Buffer,
                              unsigned int BufferLen)
{
    __ScsiCmnd_t ScsiCmnd;
    unsigned char CB[MAX_CDB];

    if (mscLun == NULL)
    {
        hal_log_err("ERR: ScsiInquery: input error, mscLun = %x", mscLun);
        return USB_STATUS_BAD_ARGUMENTS;
    }

    memset((void *)&ScsiCmnd, 0, sizeof(__ScsiCmnd_t));
    memset(CB, 0, MAX_CDB);
    /* create command block */
    CB[0] = SCSI_DVD_GET_EVENT_STATUS_NOTIFICATION; /* scsi command                 */
    CB[1] = CB[1] | ((mscLun->LunNo & 0x7) << 5);   /* lun                          */
    CB[1] = CB[1] | (RT & 0x03);                    /* Request type                 */
    put_be16(&CB[2], StartingFeatureNumber);        /* Starting Feature Number      */
    put_be16(&CB[7], BufferLen);                    /* TRANSFER LENGTH              */
    /* initialize transport command */
    ScsiCmnd.cmnd.data_direction    = DATA_FROM_DEVICE;
    ScsiCmnd.cmnd.Timeout           = SCSI_COMMAND_TIMEOUT;
    ScsiCmnd.cmnd.dwLun             = mscLun->LunNo;
    ScsiCmnd.cmnd.CBLen             = (USBMSC_SUBCLASS_SCSI == mscLun->DiskSubClass) ? SCSI_CDB_10 : ATAPI_CDB;
    ScsiCmnd.cmnd.CommandBlock      = CB;
    /* initialize scsi_cnmd */
    ScsiCmnd.sc_lun             = mscLun;
    ScsiCmnd.allowed            = SCSI_CMD_RETRY;
    ScsiCmnd.DataTransferLength = BufferLen;
    ScsiCmnd.buffer             = Buffer;
    ScsiCmnd.Done               = ScsiCmndDone;
    return ScsiDoCommand(mscLun, &ScsiCmnd);
}



