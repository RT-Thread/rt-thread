/*
********************************************************************************************************************
*                                              usb host driver
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : CD.c
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
#include  "error.h"
#include  "usb_os_platform.h"
#include  "usb_msc_i.h"
#include  "Scsi2.h"
#include  "BlkDev.h"
#include  "LunMgr_i.h"
#include  "CD.h"
#include  "mod_usbhost.h"
/*
*******************************************************************************
*                     PrintCDDriveCapitilities
*
* Description:
*
*
* Parameters:
*
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
static void PrintCDDriveCapitilities(CDROM_Capitilities_t *Capitilities)
{
    if (Capitilities == NULL)
    {
        //DMSG_PANIC("ERR: input error\n");
        return;
    }

    //DMSG_INFO("-----------------CD_ROM Drive Capitilities------------------\n");
    //DMSG_INFO("PageCode                         = %x\n", Capitilities->PageCode);
    //DMSG_INFO("PS                               = %d\n", Capitilities->PS);
    //DMSG_INFO("PageLength                       = %d\n", Capitilities->PageLength);
    //DMSG_INFO("CD_R_Rd                          = %d\n", Capitilities->CD_R_Rd);
    //DMSG_INFO("CD_E_Rd                          = %d\n", Capitilities->CD_E_Rd);
    //DMSG_INFO("Method2                          = %d\n", Capitilities->Method2);
    //DMSG_INFO("DVD_ROM_Read                     = %d\n", Capitilities->DVD_ROM_Read);
    //DMSG_INFO("DVD_R_Read                       = %d\n", Capitilities->DVD_R_Read);
    //DMSG_INFO("DVD_RAM_Read                     = %d\n", Capitilities->DVD_RAM_Read);
    //DMSG_INFO("CD_R_Wr                          = %d\n", Capitilities->CD_R_Wr);
    //DMSG_INFO("CD_E_Wr                          = %d\n", Capitilities->CD_E_Wr);
    //DMSG_INFO("TestWrite                        = %d\n", Capitilities->TestWrite);
    //DMSG_INFO("DVD_R_Write                      = %d\n", Capitilities->DVD_R_Write);
    //DMSG_INFO("DVD_RAM_Wr                       = %d\n", Capitilities->DVD_RAM_Wr);
    //DMSG_INFO("AudioPlay                        = %d\n", Capitilities->AudioPlay);
    //DMSG_INFO("DigitalPort1                     = %d\n", Capitilities->DigitalPort1);
    //DMSG_INFO("DigitalPort2                     = %d\n", Capitilities->DigitalPort2);
    //DMSG_INFO("Mode2_Form1                      = %d\n", Capitilities->Mode2_Form1);
    //DMSG_INFO("Mode2_Form2                      = %d\n", Capitilities->Mode2_Form2);
    //DMSG_INFO("MultiSession                     = %d\n", Capitilities->MultiSession);
    //DMSG_INFO("CD_DA                            = %d\n", Capitilities->CD_DA);
    //DMSG_INFO("DAAccu                           = %d\n", Capitilities->DAAccu);
    //DMSG_INFO("RW_supported                     = %d\n", Capitilities->RW_supported);
    //DMSG_INFO("RW_De_Interleaved                = %d\n", Capitilities->RW_De_Interleaved);
    //DMSG_INFO("C2_Pointers                      = %d\n", Capitilities->C2_Pointers);
    //DMSG_INFO("ISRC                             = %d\n", Capitilities->ISRC);
    //DMSG_INFO("UPC                              = %d\n", Capitilities->UPC);
    //DMSG_INFO("ReadBarCodeCapable               = %d\n", Capitilities->ReadBarCodeCapable);
    //DMSG_INFO("Lock                             = %d\n", Capitilities->Lock);
    //DMSG_INFO("LockState                        = %d\n", Capitilities->LockState);
    //DMSG_INFO("PreventJumper                    = %d\n", Capitilities->PreventJumper);
    //DMSG_INFO("Eject                            = %d\n", Capitilities->Eject);
    //DMSG_INFO("LoadingMechanismType             = %d\n", Capitilities->LoadingMechanismType);
    //DMSG_INFO("SeparateVolume                   = %d\n", Capitilities->SeparateVolume);
    //DMSG_INFO("SeparateChannelMute              = %d\n", Capitilities->SeparateChannelMute);
    //DMSG_INFO("SupportsDiscPresent              = %d\n", Capitilities->SupportsDiscPresent);
    //DMSG_INFO("SW_SlotSelection                 = %d\n", Capitilities->SW_SlotSelection);
    //DMSG_INFO("SideChangeCapable                = %d\n", Capitilities->SideChangeCapable);
    //DMSG_INFO("MaximumSpeedSupport              = %d\n", Capitilities->MaximumSpeedSupport);
    //DMSG_INFO("NumberOfVolumelevelsSupported    = %d\n", Capitilities->NumberOfVolumelevelsSupported);
    //DMSG_INFO("BufferSizeSupportedByLogicUnit   = %d\n", Capitilities->BufferSizeSupportedByLogicUnit);
    //DMSG_INFO("CurrentSpeedSelected             = %d\n", Capitilities->CurrentSpeedSelected);
    //DMSG_INFO("BCK                              = %d\n", Capitilities->BCK);
    //DMSG_INFO("RCK                              = %d\n", Capitilities->RCK);
    //DMSG_INFO("LSBF                             = %d\n", Capitilities->LSBF);
    //DMSG_INFO("Length                           = %d\n", Capitilities->Length);
    //DMSG_INFO("CopyManagementRevisionsupport    = %d\n", Capitilities->CopyManagementRevisionsupport);
    //DMSG_INFO("-----------------------------------------------------\n");
}

#if 0
static void print_CD_Disc_info(CDROM_DiscInfo_t *DiscInfo)
{
    unsigned int i = 0;

    if (DiscInfo == NULL)
    {
        //DMSG_PANIC("ERR: input error\n");
        return;
    }

    //DMSG_INFO("-----------------C/DVD Disc Information------------------\n");
    //DMSG_INFO("DataInformationLength                        = %d\n", DiscInfo->DataInformationLength);
    //DMSG_INFO("DiscStatus                                   = %d\n", DiscInfo->DiscStatus);
    //DMSG_INFO("StatusOfLastSession                          = %d\n", DiscInfo->StatusOfLastSession);
    //DMSG_INFO("Erasable                                     = %d\n", DiscInfo->Erasable);
    //DMSG_INFO("DiscInformationDataType                      = %d\n", DiscInfo->DiscInformationDataType);
    //DMSG_INFO("FirstTrackNumberOnDisc                       = %d\n", DiscInfo->FirstTrackNumberOnDisc);
    //DMSG_INFO("NumberOfSessions_LSB                         = %d\n", DiscInfo->NumberOfSessions_LSB);
    //DMSG_INFO("FirstTrackNumberInLastSession_LSB            = %d\n", DiscInfo->FirstTrackNumberInLastSession_LSB);
    //DMSG_INFO("LastTrackNumberInLastSession_LSB             = %d\n", DiscInfo->LastTrackNumberInLastSession_LSB);
    //DMSG_INFO("BG_FormatStatus                              = %d\n", DiscInfo->BG_FormatStatus);
    //DMSG_INFO("Dbit                                         = %d\n", DiscInfo->Dbit);
    //DMSG_INFO("DAC_V                                        = %d\n", DiscInfo->DAC_V);
    //DMSG_INFO("URU                                          = %d\n", DiscInfo->URU);
    //DMSG_INFO("DBC_V                                        = %d\n", DiscInfo->DBC_V);
    //DMSG_INFO("DID_V                                        = %d\n", DiscInfo->DID_V);
    //DMSG_INFO("DiscType                                     = %d\n", DiscInfo->DiscType);
    //DMSG_INFO("NumberOfSessions_MSB                         = %d\n", DiscInfo->NumberOfSessions_MSB);
    //DMSG_INFO("FirstTrackNumberInLastSession_MSB            = %d\n", DiscInfo->FirstTrackNumberInLastSession_MSB);
    //DMSG_INFO("LastTrackNumberInLastSession_MSB             = %d\n", DiscInfo->LastTrackNumberInLastSession_MSB);
    //DMSG_INFO("DiscIdentification                           = %x\n", DiscInfo->DiscIdentification);
    //DMSG_INFO("LeadInStartTimeOfLastSession_MSF             = %x\n", DiscInfo->LeadInStartTimeOfLastSession_MSF);
    //DMSG_INFO("LastPossibleStartTimeForStartOfLeadOut_MSF   = %x\n", DiscInfo->LastPossibleStartTimeForStartOfLeadOut_MSF);

    for (i = 0; i < 8; i++)
    {
        //DMSG_INFO("DiscBarCode[%d] = %x\n", i, DiscInfo->DiscBarCode[i]);
    }

    //DMSG_INFO("DiscApplicationCode     = %d\n", DiscInfo->DiscApplicationCode);
    //DMSG_INFO("NumberOfOPCTableEntries = %d\n", DiscInfo->NumberOfOPCTableEntries);
    //DMSG_INFO("---------------------------------------------------------\n");
}
#endif

/*
*******************************************************************************
*                     PrintCDInfo
*
* Description:
*
*
* Parameters:
*    CD     : input. 记录光碟的信息
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
static void PrintCDInfo(CD_Rom_t *CD)
{
    if (CD == NULL)
    {
        //DMSG_PANIC("ERR: input error\n");
        return;
    }

    //DMSG_INFO("-----------------CD_ROM Information------------------\n");
    //DMSG_INFO("DriveType                = %d\n", CD->DriveType);
    //DMSG_INFO("MaxSpeed                 = %d\n", CD->MaxSpeed);
    //DMSG_INFO("CurrentSpeed             = %d\n", CD->CurrentSpeed);
    //DMSG_INFO("Readcd_cdda              = %d\n", CD->Readcd_cdda);
    //DMSG_INFO("WriteAble                = %d\n", CD->WriteAble);

    switch (CD->DiscType)
    {
        case USBH_MEDIUM_CD_DATA_ONLY:
            //DMSG_INFO("DiscType is Data Only Disc\n");
            break;

        case USBH_MEDIUM_CD_AUDIO_ONLY:
            //DMSG_INFO("DiscType is Audio Only Disc\n");
            break;

        case USBH_MEDIUM_CD_DATA_AUDIO_COMBINED:
            //DMSG_INFO("DiscType is Data Audio combined Disc\n");
            break;

        case USBH_MEDIUM_CD_PHOTO_CD:
            //DMSG_INFO("DiscType is Photo CD Disc\n");
            break;

        default:
            //DMSG_INFO("DiscType is unkown(%x)\n", CD->DiscType);
            break;
    }

    //DMSG_INFO("DoubleDisc               = %d\n", CD->DoubleDisc);
    //DMSG_INFO("LastWriteSector          = %d\n", CD->LastWriteSector);
    //DMSG_INFO("MultiSession             = %d\n", CD->MultiSession);
    //DMSG_INFO("NumberOfSUinitPerMUnit   = %d\n", CD->NumberOfSUinitPerMUnit);
    //DMSG_INFO("NumberOfFUinitPerSUnit   = %d\n", CD->NumberOfFUinitPerSUnit);
    //DMSG_INFO("InactivityTimeMultiPlier = %d\n", CD->InactivityTimeMultiPlier);
    //DMSG_INFO("-----------------------------------------------------\n");
    PrintCDDriveCapitilities(&(CD->Capitilities));
}

/*
*******************************************************************************
*                     CdLastWriteSector
*
* Description:
*    获得可写光碟的最后写的位置。
*
* Parameters:
*    mscLun  :  input. 目标设备
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
unsigned int CdIOCtrlLastWriteSector(__UsbBlkDev_t *BlkDev)
{
    CD_Rom_t *CD = NULL;

    if (BlkDev == NULL)
    {
        //DMSG_PANIC("ERR: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    CD = (CD_Rom_t *)BlkDev->Extern;

    if (CD == NULL)
    {
        //DMSG_PANIC("ERR: CdIOCtrlLastWriteSector: CD == NULL\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    return CD->LastWriteSector;
}

/*
*******************************************************************************
*                     CdMultiSession
*
* Description:
*    获得光碟多扇区的位置。
*
* Parameters:
*    mscLun  :  input. 目标设备
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
unsigned int CdIOCtrlMultiSession(__UsbBlkDev_t *BlkDev)
{
    return 0;
}

/*
*******************************************************************************
*                     GetCdLastWriteSector
*
* Description:
*    获得可写光碟的最后写的位置。
*
* Parameters:
*    mscLun  :  input. 目标设备
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
#if 0
static int GetCdLastWriteSector(__mscLun_t *mscLun, CD_Rom_t *CD)
{
    CDROM_DiscInfo_t  DiscInfo;
    CDROM_TrackInfo_t TrackInfo;
    CDROM_TrackMSF_t  *TrackMSF;
    __u8 buffer[MAXIMUM_CDROM_SIZE];
    unsigned int ActLen    = 0;
    unsigned int LastTrack = 0;  /* 最后一个扇区 */
    int ret       = 0;

    if (mscLun == NULL || CD == NULL)
    {
        //DMSG_PANIC("ERR: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    if (!mscLun->MediaPresent)
    {
        //DMSG_PANIC("ERR: disc is not present, can not read disc information\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    memset(&DiscInfo,  0, sizeof(CDROM_DiscInfo_t));
    memset(&TrackInfo, 0, sizeof(CDROM_TrackInfo_t));
    memset(buffer,  0, MAXIMUM_CDROM_SIZE);
    /* Read disc information, get last track */
    ret = ScsiCDReadDiscInfo(mscLun,
                             CDROM_DISC_INFO_STANDARD,
                             &DiscInfo,
                             sizeof(CDROM_DiscInfo_t),
                             &ActLen);

    if (ret != USB_STATUS_SUCCESS && ActLen < sizeof(CDROM_DiscInfo_t))
    {
        //DMSG_PANIC("ERR: ScsiCDReadDiscInfo failed\n");
        goto end;
    }

    print_CD_Disc_info(&DiscInfo);
    LastTrack = (DiscInfo.LastTrackNumberInLastSession_MSB << 8) | DiscInfo.LastTrackNumberInLastSession_LSB;
    /* Read last track information, get last track */
    ret = ScsiCDReadTrackInfo(mscLun,
                              0,
                              CDROM_TRACK_INFO_ADDRESS_NUMBER_TYPE_TRACK_NUMBER,
                              LastTrack,
                              &TrackInfo,
                              sizeof(CDROM_TrackInfo_t),
                              &ActLen);

    if (ret != USB_STATUS_SUCCESS && ActLen < sizeof(CDROM_TrackInfo_t))
    {
        //DMSG_PANIC("ERR: ScsiCDReadTrackInfo failed\n");
        goto end;
    }

    /* If the last track is blank, try the previous. */
    if (TrackInfo.Blank)
    {
        //DMSG_PANIC("ERR: LastTrack is blank\n");

        if (LastTrack == 1)
        {
            //DMSG_PANIC("ERR: LastTrack number is 1, but it is blank\n");
            goto end;
        }

        ret = ScsiCDReadTrackInfo(mscLun,
                                  0,
                                  CDROM_TRACK_INFO_ADDRESS_NUMBER_TYPE_TRACK_NUMBER,
                                  (LastTrack - 1),
                                  &TrackInfo,
                                  sizeof(CDROM_TrackInfo_t),
                                  &ActLen);

        if (ret != USB_STATUS_SUCCESS && ActLen < sizeof(CDROM_TrackInfo_t))
        {
            //DMSG_PANIC("ERR: ScsiCDReadTrackInfo failed\n");
            goto end;
        }
    }

    /* get the last write sector */
    if (TrackInfo.LRA_V)
    {
        CD->LastWriteSector = TrackInfo.LastRecordedAddress;
    }
    else   /* last recorded address invalid, then find the first blank block address */
    {
        CD->LastWriteSector = TrackInfo.TrackStartAddress + TrackInfo.TrackSizeEndAddress;

        if (TrackInfo.FreeBlocks)
        {
            CD->LastWriteSector -= (TrackInfo.FreeBlocks + 7);
        }
    }

    return USB_ERR_SUCCESS;
end:
    /* May be disc is MSF Format */
    ret = ScsiCDReadToc(mscLun,
                        1,
                        CDROM_READTOC_FORMAT_CODE_TOC,
                        CDROM_LEADOUT,
                        buffer,
                        sizeof(CDROM_TocHeader_t) + sizeof(CDROM_TrackMSF_t));

    if (ret != USB_STATUS_SUCCESS)
    {
        //DMSG_PANIC("ERR: ScsiCDReadTrackInfo failed\n");
        CD->LastWriteSector = 0;
        return USB_ERR_UNKOWN_ERROR;
    }

    TrackMSF = (CDROM_TrackMSF_t *)(buffer + sizeof(CDROM_TocHeader_t));
    CD->LastWriteSector = msf_to_lba(TrackMSF->MSF.Minute, TrackMSF->MSF.Second, TrackMSF->MSF.Frame);
    return USB_ERR_SUCCESS;
}
#endif

int CDIOCtrl(__UsbBlkDev_t *BlkDev, unsigned int Cmd, int Aux, void *pBuffer)
{
    __mscLun_t *mscLun = NULL;
    CD_Rom_t *CD = NULL;
    unsigned int  cpu_sr;

    /* check input */
    if (BlkDev == NULL)
    {
        //DMSG_PANIC("ERR: input error\n");
        return EPDK_FAIL;
    }

    mscLun = BlkDev->Lun;

    if (mscLun == NULL)
    {
        //DMSG_PANIC("ERR: mscLun == NULL\n");
        return EPDK_FAIL;
    }

    CD = (CD_Rom_t *)BlkDev->Extern;

    if (CD == NULL)
    {
        //DMSG_PANIC("ERR: CD == NULL\n");
        return EPDK_FAIL;
    }

    switch (Cmd)
    {
        case USB_STORAGE_USER_CTRL_CMD_GET_CDROM_INFO:
        {
            usbh_CDROM_Info_t *CDROM_Info = NULL;

            if (pBuffer == NULL)
            {
                //DMSG_PANIC("ERR: USB_STORAGE_USER_CTRL_CMD_GET_CDROM_INFO, pBuffer == NULL\n");
                return EPDK_FAIL;
            }

            CDROM_Info = (usbh_CDROM_Info_t *)pBuffer;
            CDROM_Info->DiscType  = CD->DiscType;
            CDROM_Info->DriveType = CD->DriveType;
            return 0;
        }

        //break;

        case USB_STORAGE_USER_CTRL_CMD_CDROM_EJECT:
            //DMSG_INFO("USB_STORAGE_USER_CTRL_CMD_CDROM_EJECT\n");

            /* 先允许介质移动，再去弹出介质 */
            if (ScsiPreventAllowMedium(mscLun, 0, 0) == USB_STATUS_SUCCESS)
            {
                //DMSG_INFO("[CD_ROM]: Allow medium removal\n");
                ENTER_CRITICAL(cpu_sr);
                CD->IsMeduimPrevent = 0;
                EXIT_CRITICAL(cpu_sr);
            }

            ScsiStartStopUnit(mscLun, 1, 0);
            return EPDK_OK;

        //break;

        case USB_STORAGE_USER_CTRL_CMD_CDROM_LOAD:
            //DMSG_INFO("USB_STORAGE_USER_CTRL_CMD_CDROM_LOCK\n");

            /* 先允许介质移动，再去加载介质 */
            if (ScsiPreventAllowMedium(mscLun, 0, 0) == USB_STATUS_SUCCESS)
            {
                //DMSG_INFO("[CD_ROM]: Allow medium removal\n");
                ENTER_CRITICAL(cpu_sr);
                CD->IsMeduimPrevent = 0;
                EXIT_CRITICAL(cpu_sr);
            }

            ScsiStartStopUnit(mscLun, 1, 1);
            return EPDK_OK;

        //break;

        case USB_STORAGE_USER_CTRL_CMD_CDROM_PREVENT_MEDIUM_REMOVAL:
            if (ScsiPreventAllowMedium(mscLun, 0, 1) == USB_STATUS_SUCCESS)
            {
                //DMSG_INFO("[CD_ROM]: Prevent medium removal\n");
                ENTER_CRITICAL(cpu_sr);
                CD->IsMeduimPrevent = 0;
                EXIT_CRITICAL(cpu_sr);
            }

            return EPDK_OK;

        //break;

        case USB_STORAGE_USER_CTRL_CMD_CDROM_ALLOW_MEDIUM_REMOVAL:
            if (ScsiPreventAllowMedium(mscLun, 0, 0) == USB_STATUS_SUCCESS)
            {
                //DMSG_INFO("[CD_ROM]: Allow medium removal\n");
                ENTER_CRITICAL(cpu_sr);
                CD->IsMeduimPrevent = 0;
                EXIT_CRITICAL(cpu_sr);
            }

            return EPDK_OK;

        //break;

        case USB_STORAGE_USER_CTRL_CMD_CDROM_GET_DRIVE_STATUS:
        {
            unsigned int *Status = (unsigned int *)pBuffer;

            if (pBuffer == NULL)
            {
                //DMSG_PANIC("ERR: USB_STORAGE_USER_CTRL_CMD_CDROM_GET_DRIVE_STATUS, pBuffer == NULL\n");
                return EPDK_FAIL;
            }

            *Status = CD->DriveStatus;
            return 0;
        }

        //break;

        default:
            //DMSG_PANIC("Wrn: unkown Block cmd(%x)\n", Cmd);
            break;
    }

    return EPDK_FAIL;
}

/*
*******************************************************************************
*                     GetCDDriveCapabilites
*
* Description:
*    获得光驱的驱动能力
*
* Parameters:
*    mscLun : input. 目标设备
*    CD     : input. 记录光碟的信息
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
static void GetCDDriveCapabilites(__mscLun_t *mscLun, CD_Rom_t *CD)
{
    CDROM_Capitilities_t *Capitilities = NULL;
    __u8  buffer[SCSI_MODE_SENSE_MAX_DATA_LEN];
    unsigned int ActLen        = 0;
    int ret           = 0;
    unsigned int pageAddr      = 0;   /* Capitilities页起始地址 */
    __ModeSense10Header_t *Header = NULL;
    unsigned int DiscType = 0;

    if (mscLun == NULL || CD == NULL)
    {
        //DMSG_PANIC("ERR: input error\n");
        return ;
    }

    /* send ModeSense command to get cd capabilites page */
    memset(buffer, 0, SCSI_MODE_SENSE_MAX_DATA_LEN);
    hal_sem_wait(mscLun->Lock);
    /* send mode sense command */
    ret = ScsiModeSense10(mscLun,
                          MODE_PAGE_CDROM_CAPS,
                          ((mscLun->DeviceType == SCSI_DEVICE_CDROM) ? 1 : 0),
                          (void *)buffer,
                          (sizeof(__ModeSense10Header_t) + sizeof(CDROM_Capitilities_t)),
                          &ActLen);

    if (ret != USB_STATUS_SUCCESS)
    {
        //DMSG_PANIC("ERR: ScsiModeSense10 failed\n");
        ActLen = 0;
    }

    /* parse mode sense data */
    if (ActLen)
    {
        /* get media type */
        DiscType = buffer[2];

        switch (DiscType)
        {
            case MEDIUM_CD_ROM_UNKNOWN:
            case MEDIUM_CDR_ROM_UNKNOWN:
            case MEDIUM_CDE_ROM_UNKNOWN:
                CD->DiscType = USBH_MEDIUM_CD_UNKOWN;
                break;

            case MEDIUM_CD_ROM_DATA_ONLY_80:
            case MEDIUM_CD_ROM_DATA_ONLY_120:
            case MEDIUM_CDR_ROM_DATA_ONLY_80:
            case MEDIUM_CDR_ROM_DATA_ONLY_120:
            case MEDIUM_CDE_ROM_DATA_ONLY_80:
            case MEDIUM_CDE_ROM_DATA_ONLY_120:
                CD->DiscType = USBH_MEDIUM_CD_DATA_ONLY;
                break;

            case MEDIUM_CD_DA_AUDIO_ONLY_80:
            case MEDIUM_CD_DA_AUDIO_ONLY_120:
            case MEDIUM_CDR_DA_AUDIO_ONLY_80:
            case MEDIUM_CDR_DA_AUDIO_ONLY_120:
            case MEDIUM_CDE_DA_AUDIO_ONLY_80:
            case MEDIUM_CDE_DA_AUDIO_ONLY_120:
                CD->DiscType = USBH_MEDIUM_CD_AUDIO_ONLY;
                break;

            case MEDIUM_CD_ROM_DATA_AUDIO_COMBINED_80:
            case MEDIUM_CD_ROM_DATA_AUDIO_COMBINED_120:
            case MEDIUM_CDR_ROM_DATA_AUDIO_COMBINED_80:
            case MEDIUM_CDR_ROM_DATA_AUDIO_COMBINED_120:
            case MEDIUM_CDE_ROM_DATA_AUDIO_COMBINED_80:
            case MEDIUM_CDE_ROM_DATA_AUDIO_COMBINED_120:
                CD->DiscType = USBH_MEDIUM_CD_DATA_AUDIO_COMBINED;
                break;

            case MEDIUM_CD_PHOTO_CD_80:
            case MEDIUM_CD_PHOTO_CD_120:
            case MEDIUM_CDE_PHOTO_CD_80:
            case MEDIUM_CDE_PHOTO_CD_120:
            case MEDIUM_CDR_PHOTO_CD_80:
            case MEDIUM_CDR_PHOTO_CD_120:
                CD->DiscType = USBH_MEDIUM_CD_PHOTO_CD;
                break;

            default:
                //DMSG_PANIC("ERR: unkown cd type(%d)\n", CD->DiscType);
                CD->DiscType = USBH_MEDIUM_CD_UNKOWN;
        }

        /* header_length is 8, block_descriptor_length is xxx */
        Header = (__ModeSense10Header_t *)buffer;
        pageAddr = sizeof(__ModeSense10Header_t) + Header->BlockDescLength;
        Capitilities = (CDROM_Capitilities_t *)&buffer[pageAddr];
        memcpy(&(CD->Capitilities), Capitilities, sizeof(CDROM_Capitilities_t));

        /* can't eject? */
        if (Capitilities->Eject)
        {
            CD->Eject = 1;
        }

        /* reading audio data using READ_CD */
        if (Capitilities->CD_DA)
        {
            CD->Readcd_cdda = 1;
        }

        /* drive speed */
        CD->MaxSpeed     = Capitilities->MaximumSpeedSupport;
        CD->CurrentSpeed = Capitilities->CurrentSpeedSelected;

        /* CD Driver Type */
        if (CD->Capitilities.CD_R_Rd)
        {
            CD->DriveType |= USBH_CDROM_DRIVER_TYPE_CDR_RD;
        }

        if (CD->Capitilities.CD_R_Wr)
        {
            CD->DriveType |= USBH_CDROM_DRIVER_TYPE_CDR_WR;
            CD->WriteAble = 1;
        }

        if (CD->Capitilities.CD_E_Rd)
        {
            CD->DriveType |= USBH_CDROM_DRIVER_TYPE_CDE_RD;
        }

        if (CD->Capitilities.CD_E_Wr)
        {
            CD->DriveType |= USBH_CDROM_DRIVER_TYPE_CDE_WR;
            CD->WriteAble = 1;
        }

        if (CD->Capitilities.DVD_ROM_Read)
        {
            CD->DriveType |= USBH_CDROM_DRIVER_TYPE_DVD_ROM_RD;
        }

        if (CD->Capitilities.DVD_R_Read)
        {
            CD->DriveType |= USBH_CDROM_DRIVER_TYPE_DVDR_RD;
        }

        if (CD->Capitilities.DVD_RAM_Read)
        {
            CD->DriveType |= USBH_CDROM_DRIVER_TYPE_DVD_RAM_RD;
        }

        if (CD->Capitilities.DVD_R_Write)
        {
            CD->DriveType |= USBH_CDROM_DRIVER_TYPE_DVDR_WR;
            CD->WriteAble = 1;
        }

        if (CD->Capitilities.DVD_RAM_Wr)
        {
            CD->DriveType |= USBH_CDROM_DRIVER_TYPE_DVD_RAM_WR;
            CD->WriteAble = 1;
        }
    }
    else   /* if deivce not have capabilities page, then no mode sense data */
    {
        //DMSG_PANIC("GetCDRomCapabilites: no mode sense data\n");
        CD->DriveType   = 0;
        CD->WriteAble   = 0;
    }

    if (!CD->WriteAble)
    {
        mscLun->WriteProtect = 1;
    }

    hal_sem_post(mscLun->Lock);
    return;
}

/*
*******************************************************************************
*                     GetCDDiscTpye
*
* Description:
*    获得光碟的信息
*
* Parameters:
*    mscLun : input. 目标设备
*    CD     : input. 记录光碟的信息
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
#if 0
static void GetCDDiscTpye(__mscLun_t *mscLun, CD_Rom_t *CD)
{
    __u8  buffer[SCSI_MODE_SENSE_MAX_DATA_LEN];
    unsigned int ActLen        = 0;
    int ret           = 0;
    unsigned int pageAddr      = 0;   /* CDROM page 页起始地址 */
    __ModeSense10Header_t *Header = NULL;

    if (mscLun == NULL || CD == NULL)
    {
        //DMSG_PANIC("ERR: input error\n");
        return ;
    }

    /* send ModeSense command to get cd capabilites page */
    memset(buffer, 0, SCSI_MODE_SENSE_MAX_DATA_LEN);
    hal_sem_wait(mscLun->Lock);
    /* send mode sense command */
    ret = ScsiModeSense10(mscLun,
                          MODE_PAGE_CDROM,
                          ((mscLun->DeviceType == SCSI_DEVICE_CDROM) ? 1 : 0),
                          (void *)buffer,
                          (sizeof(__ModeSense10Header_t) + sizeof(CDROM_ParameterPage_t)),
                          &ActLen);

    if (ret != USB_STATUS_SUCCESS)
    {
        //DMSG_PANIC("ERR: ScsiModeSense10 failed\n");
        ActLen = 0;
    }

    /* parse mode sense data */
    if (ActLen)
    {
        Header = (__ModeSense10Header_t *)buffer;
        pageAddr = sizeof(__ModeSense10Header_t) + Header->BlockDescLength;
        CD->InactivityTimeMultiPlier = buffer[pageAddr + 3] & 0x0f;
        CD->NumberOfSUinitPerMUnit   = get_be16(&buffer[pageAddr + 4]);
        CD->NumberOfFUinitPerSUnit   = get_be16(&buffer[pageAddr + 6]);
    }
    else   /* if deivce not have capabilities page, then no mode sense data */
    {
        //DMSG_PANIC("GetCDDiscTpye: no mode sense data\n");
        CD->InactivityTimeMultiPlier = 0;
        CD->NumberOfSUinitPerMUnit   = 60;
        CD->NumberOfFUinitPerSUnit   = 75;
    }

    hal_sem_post(mscLun->Lock);
    return;
}
#endif

/*
*******************************************************************************
*                     GetCDDiscInfo
*
* Description:
*    获得光碟的信息
*
* Parameters:
*    mscLun : input. 目标设备
*    CD     : input. 记录光碟的信息
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
static void GetCDDiscInfo(__mscLun_t *mscLun, CD_Rom_t *CD)
{
    //GetCDDiscTpye(mscLun, CD);
    //GetCdLastWriteSector(mscLun, CD);
}

/*
*******************************************************************************
*                     GetCDRomInfo
*
* Description:
*    获得光碟的信息
*
* Parameters:
*    mscLun : input. 目标设备
*    CD     : input. 记录光碟的信息
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
static void GetCDRomInfo(__mscLun_t *mscLun, CD_Rom_t *CD)
{
    if (mscLun == NULL || CD == NULL)
    {
        //DMSG_PANIC("ERR: input error\n");
        return ;
    }

    /* 获得光驱的信息 */
    GetCDDriveCapabilites(mscLun, CD);
    /* 获得光碟的信息 */
    GetCDDiscInfo(mscLun, CD);
    PrintCDInfo(CD);
}

/*
*******************************************************************************
*                     GetCDRomPowerEvent
*
* Description:
*    获得光驱电源的信息
*
* Parameters:
*    mscLun : input. 目标设备
*    CD     : input. 记录光碟的信息
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
#if 0
static int GetCDRomPowerEvent(__mscLun_t *mscLun, CD_Rom_t *CD, CDROM_PowerStatus_t *PowerStatus)
{
    __u8  buffer[CDROM_GET_EVENT_CMD_MAX_RETURN_DATA_LEN];
    int ret    = 0;
    CDROM_EventHeader_t *EventHeader = NULL;

    if (mscLun == NULL || CD == NULL)
    {
        //DMSG_PANIC("ERR: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    memset(buffer, 0, CDROM_GET_EVENT_CMD_MAX_RETURN_DATA_LEN);
    hal_sem_wait(mscLun->Lock);
    ret = ScsiDvdGetEventStatus(mscLun,
                                1,
                                CDROM_NOTIFICATION_CLASS_REQUEST_POWER_MANAGEMENT,
                                buffer,
                                sizeof(CDROM_EventHeader_t) + sizeof(CDROM_PowerStatus_t));

    if (ret != USB_STATUS_SUCCESS)
    {
        //DMSG_PANIC("ERR: ScsiDvdGetEventStatus failed\n");
        hal_sem_post(mscLun->Lock);
        return USB_ERR_COMMAND_EXECUTE_FAILED;
    }

    EventHeader = (CDROM_EventHeader_t *)buffer;

    if (EventHeader->NEA
        || EventHeader->NotificationClass != CDROM_NOTIFICATION_CLASS_FIELD_POWER_MANAGEMENT)
    {
        //DMSG_PANIC("ERR: There are no event available in the requested Notification\n");
        hal_sem_post(mscLun->Lock);
        return USB_ERR_UNKOWN_ERROR;
    }

    memcpy(PowerStatus, buffer + sizeof(CDROM_EventHeader_t), sizeof(CDROM_PowerStatus_t));
    hal_sem_post(mscLun->Lock);
    return USB_ERR_SUCCESS;
}
#endif

/*
*******************************************************************************
*                     GetCDRomMediaEvent
*
* Description:
*    获得光驱光碟的信息
*
* Parameters:
*    mscLun : input. 目标设备
*    CD     : input. 记录光碟的信息
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
static int GetCDRomMediaEvent(__mscLun_t *mscLun, CD_Rom_t *CD, CDROM_MediaStatus_t *MediaStatus)
{
    __u8  buffer[CDROM_GET_EVENT_CMD_MAX_RETURN_DATA_LEN];
    int ret    = 0;
    CDROM_EventHeader_t *EventHeader = NULL;

    if (mscLun == NULL || CD == NULL)
    {
        //DMSG_PANIC("ERR: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    memset(buffer, 0, CDROM_GET_EVENT_CMD_MAX_RETURN_DATA_LEN);
    hal_sem_wait(mscLun->Lock);
    ret = ScsiDvdGetEventStatus(mscLun,
                                1,
                                CDROM_NOTIFICATION_CLASS_REQUEST_MEDIA_STATUS,
                                buffer,
                                sizeof(CDROM_EventHeader_t) + sizeof(CDROM_MediaStatus_t));

    if (ret != USB_STATUS_SUCCESS)
    {
        //DMSG_PANIC("ERR: ScsiDvdGetEventStatus failed\n");
        hal_sem_post(mscLun->Lock);
        return USB_ERR_COMMAND_EXECUTE_FAILED;
    }

    EventHeader = (CDROM_EventHeader_t *)buffer;

    if (EventHeader->NEA
        || EventHeader->NotificationClass != CDROM_NOTIFICATION_CLASS_FIELD_MEDIA_STATUS)
    {
        //DMSG_PANIC("ERR: There are no event available in the requested Notification\n");
        hal_sem_post(mscLun->Lock);
        return USB_ERR_UNKOWN_ERROR;
    }

    memcpy(MediaStatus, buffer + sizeof(CDROM_EventHeader_t), sizeof(CDROM_MediaStatus_t));
    hal_sem_post(mscLun->Lock);
    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     GetCDRomMediaEvent
*
* Description:
*    获得光驱的状态
*
* Parameters:
*    mscLun : input. 目标设备
*    CD     : input. 记录光碟的信息
*
* Return value:
*    无
*
* note:
*    发送Test Unit Ready命令获得设备的状态。命令发送成功，直接返回。如果命令失败
* 就去获得光驱的状态。如果发送get MediaEvent命令失败，那么就只能通过Test Unit Ready
* 命令的结果判断设备的状态。
*
*******************************************************************************
*/
static int GetCDRomDriveEvent(__mscLun_t *mscLun, CD_Rom_t *CD)
{
    CDROM_MediaStatus_t MediaStatus;
    int ret = 0;
    int status = 0;

    if (mscLun == NULL || CD == NULL)
    {
        //DMSG_PANIC("ERR: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    memset(&MediaStatus, 0, sizeof(CDROM_MediaStatus_t));
    /* Test Unit Ready */
    hal_sem_wait(mscLun->Lock);
    status = ScsiTestUnitReady(mscLun);
    hal_sem_post(mscLun->Lock);

    if (status == USB_STATUS_SUCCESS)
    {
        CD->DriveStatus = USBH_CDROM_DRIVE_STATUS_DISK_OK;
        return USB_ERR_SUCCESS;
    }

    /* Get Media Event */
    ret = GetCDRomMediaEvent(mscLun, CD, &MediaStatus);

    if (ret == 0)
    {
        if (MediaStatus.DoorOpen)
        {
            CD->DriveStatus = USBH_CDROM_DRIVE_STATUS_TRAY_OPEN;
        }
        else if (MediaStatus.MediaPesent)
        {
            CD->DriveStatus = USBH_CDROM_DRIVE_STATUS_DISK_OK;
        }
        else
        {
            CD->DriveStatus = USBH_CDROM_DRIVE_STATUS_NO_DISC;
        }

        return USB_ERR_SUCCESS;
    }

    switch (status)
    {
        case USB_STATUS_SUCCESS:
            CD->DriveStatus = USBH_CDROM_DRIVE_STATUS_DISK_OK;
            break;

        case USB_STATUS_MEDIA_NOT_PRESENT:
            CD->DriveStatus = USBH_CDROM_DRIVE_STATUS_NO_DISC;
            break;

        case USB_STATUS_NOT_READY_TO_READY_TRANSITION:
            //DMSG_INFO("[USB Disk]: media not ready to ready transition\n");
            CD->DriveStatus = USBH_CDROM_DRIVE_STATUS_NOT_READY;
            break;

        default:
            CD->DriveStatus = USBH_CDROM_DRIVE_STATUS_NO_INFORMATION;
    }

    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     ReadCDDA
*
* Description:
*    读取音乐cd的内容
*
* Parameters:
*    mscLun     : input.  目标设备
*    Lba        : input.  起始扇区
*    nFrames    : input.  帧数
*    Buffer     : input.  存放读取的数据
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
unsigned int ReadCDDA(__mscLun_t *mscLun, unsigned int Lba, unsigned int nFrames, void *Buffer)
{
    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     CDMediaChange
*
* Description:
*    实时检测光驱的变化
*
* Parameters:
*
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
static void __CDMediaChange(__mscLun_t *mscLun)
{
    __UsbBlkDev_t  *BlkDev = NULL;
    CD_Rom_t *CD = NULL;
    int ret = 0;

    if (mscLun == NULL)
    {
        //DMSG_PANIC("ERR: input error\n");
        return ;
    }

    BlkDev = (__UsbBlkDev_t *)mscLun->sdev_data;

    if (BlkDev == NULL)
    {
        //DMSG_PANIC("ERR: CDMediaChange: BlkDev == NULL\n");
        return;
    }

    CD = (CD_Rom_t *)BlkDev->Extern;

    if (CD == NULL)
    {
        //DMSG_PANIC("ERR: CDMediaChange: CD == NULL\n");
        return;
    }

    ret = GetCDRomDriveEvent(mscLun, CD);

    if (ret != 0)
    {
        BlkDev->ErrCmdNr++;

        if (BlkDev->is_RegDisk)
        {
            //DMSG_PANIC("ERR: GetCDRomDriveEvent failed, UsbBlkDevUnReg\n");
            UsbBlkDevUnReg(BlkDev);
            UsbBlkDevReg(BlkDev, DEV_CLASS_USERDEF, 0);
        }

        return;
    }

    switch (CD->DriveStatus)
    {
        case USBH_CDROM_DRIVE_STATUS_NO_INFORMATION:
        case USBH_CDROM_DRIVE_STATUS_NO_DISC:
        case USBH_CDROM_DRIVE_STATUS_TRAY_OPEN:
        case USBH_CDROM_DRIVE_STATUS_NOT_READY:
            //DMSG_PANIC("CDMediaChange: DriveStatus = %d\n", CD->DriveStatus);

            if (BlkDev->is_RegDisk)
            {
                //DMSG_PANIC("ERR: DriveStatus is CDROM_DRIVE_NO_INFORMATION\n");
                UsbBlkDevUnReg(BlkDev);
                UsbBlkDevReg(BlkDev, DEV_CLASS_USERDEF, 0);
            }

            break;

        case USBH_CDROM_DRIVE_STATUS_DISK_OK:

            /* 没有注册disk设备, 就去注册disk设备 */
            if (!BlkDev->is_RegDisk)
            {
                /* 获得磁盘信息 */
                GetDiskInfo(BlkDev);
                GetCDRomInfo(mscLun, CD);

                /* 注册块设备 */
                if (mscLun->MediaPresent && CD->DiscType != USBH_MEDIUM_CD_AUDIO_ONLY)
                {
                    UsbBlkDevUnReg(BlkDev);
                    UsbBlkDevReg(BlkDev, DEV_CLASS_DISK, 1);
                }
                else if (mscLun->MediaPresent && CD->DiscType == USBH_MEDIUM_CD_AUDIO_ONLY)
                {
                    UsbBlkDevUnReg(BlkDev);
                    UsbBlkDevReg(BlkDev, DEV_CLASS_USERDEF, 1);
                }
            }

            break;

        default:
            BlkDev->ErrCmdNr++;
            //DMSG_PANIC("ERR: CDMediaChange\n");
    }

    if (BlkDev->ErrCmdNr > 3)
    {
        //DMSG_PANIC("ERR: too much error during test unit ready\n");
        BlkDev->ErrCmdNr = 0;

        if (BlkDev->is_RegDisk)
        {
            UsbBlkDevUnReg(BlkDev);
            UsbBlkDevReg(BlkDev, DEV_CLASS_USERDEF, 0);
        }
        else
        {
            //DMSG_PANIC("ERR: device is not regist a disk device\n");
        }
    }

    return;
}

static void CDMediaChange(__mscLun_t *mscLun)
{
    __UsbBlkDev_t  *BlkDev = NULL;
    CD_Rom_t *CD = NULL;
    unsigned int  cpu_sr;

    if (mscLun == NULL)
    {
        //DMSG_PANIC("ERR: input error\n");
        return ;
    }

    BlkDev = (__UsbBlkDev_t *)mscLun->sdev_data;

    if (BlkDev == NULL)
    {
        //DMSG_PANIC("ERR: CDMediaChange: BlkDev == NULL\n");
        return;
    }

    CD = (CD_Rom_t *)BlkDev->Extern;

    if (CD == NULL)
    {
        //DMSG_PANIC("ERR: CDMediaChange: CD == NULL\n");
        return;
    }

    /* 如果介质被禁止移动, 并且已经注册Disk设备, 那么就不用实时检测了 */
    if (CD->IsMeduimPrevent && BlkDev->is_RegDisk == 1)
    {
        /* nothing to do */
    }
    else
    {
        if (CD->IsMeduimPrevent)
        {
            //DMSG_PANIC("WRN: Meduim is prevent, but not register disk\n");

            if (ScsiPreventAllowMedium(mscLun, 0, 0) == USB_STATUS_SUCCESS)
            {
                //DMSG_INFO("[CD_ROM]: Allow medium removal\n");
                ENTER_CRITICAL(cpu_sr);
                CD->IsMeduimPrevent = 0;
                EXIT_CRITICAL(cpu_sr);
            }
        }

        __CDMediaChange(mscLun);
    }
}

/*
*******************************************************************************
*                     CDProbe
*
* Description:
*    光驱识别
*
* Parameters:
*    mscLun  :  目标设备
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
int CDProbe(__mscLun_t *mscLun)
{
    __UsbBlkDev_t *BlkDev = NULL;
    CD_Rom_t *CD = NULL;
    unsigned int  cpu_sr;
    int ret = 0;

    if (mscLun == NULL)
    {
        //DMSG_PANIC("ERR: CDProbe: input error\n");
        return USB_ERR_BAD_ARGUMENTS;
    }

    /* 初始化一个块设备 */
    BlkDev = UsbBlkDevAllocInit(mscLun);

    if (BlkDev == NULL)
    {
        //DMSG_PANIC("ERR: CDProbe: alloc blkdev failed\n");
        return USB_ERR_MALLOC_FAILED;
    }

    if (mscLun->LunNo >= mscLun->mscDev->MaxLun - 1)
    {
        BlkDev->last_lun = 1;
        __wrn("cd, send last lun msg.........\n");
    }
    else
    {
        BlkDev->last_lun = 0;
    }

    __wrn("mscLun->LunNo=%d\n", mscLun->LunNo);
    __wrn("mscLun->mscDev->MaxLun=%d\n", mscLun->mscDev->MaxLun);
    __wrn("BlkDev->last_lun=%d\n", BlkDev->last_lun);
    CD = hal_malloc(sizeof(CD_Rom_t));

    if (CD == NULL)
    {
        //DMSG_PANIC("ERR: CDProbe: USB_OS_MALLOC blkdev failed\n");
        UsbBlkDevFree(BlkDev);
        return USB_ERR_MALLOC_FAILED;
    }

    memset(CD, 0, sizeof(CD_Rom_t));
    mscLun->sdev_data = (void *)BlkDev;
    BlkDev->Extern    = CD;
    /* 获得磁盘信息 */
    GetDiskInfo(BlkDev);
    GetCDRomInfo(mscLun, CD);

    /* 注册块设备 */
    if (mscLun->MediaPresent && CD->DiscType != USBH_MEDIUM_CD_AUDIO_ONLY)
    {
        ret = UsbBlkDevReg(BlkDev, DEV_CLASS_DISK, 1);
    }
    else if (mscLun->MediaPresent && CD->DiscType == USBH_MEDIUM_CD_AUDIO_ONLY)
    {
        ret = UsbBlkDevReg(BlkDev, DEV_CLASS_USERDEF, 1);
    }
    else
    {
        ret = UsbBlkDevReg(BlkDev, DEV_CLASS_USERDEF, 0);
    }

    if (ret != 0)
    {
        //DMSG_PANIC("ERR: DiskProbe: UsbBlkDevReg failed\n");
        return USB_ERR_REG_BLK_DEV_FAILED;
    }

    /* 告诉usb_monitor, scsi disk识别设备成功 */
    {
        u32 is_reg = 1;
        //usbm_sendcmd(DEV_IOC_USR_HWSC_USBH_MSC_DEV_REG_SET, &is_reg);
    }
    /* add media change */
    ENTER_CRITICAL(cpu_sr);
    mscLun->MediaChange = CDMediaChange;
    EXIT_CRITICAL(cpu_sr);
    return USB_ERR_SUCCESS;
}

/*
*******************************************************************************
*                     CDRemove
*
* Description:
*    光驱驱动卸载
*
* Parameters:
*    mscLun  :  目标设备
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
int CDRemove(__mscLun_t *mscLun)
{
    __UsbBlkDev_t *BlkDev = NULL;
    unsigned int  cpu_sr;

    if (mscLun == NULL)
    {
        //DMSG_PANIC("ERR: DiskRemove: input error\n");
        return -1;
    }

    BlkDev = (__UsbBlkDev_t *)mscLun->sdev_data;

    if (BlkDev == NULL)
    {
        //DMSG_PANIC("ERR: BlkDev == NULL\n");
        return -1;
    }

    /* 注销块设备 */
    UsbBlkDevUnReg(BlkDev);
    /* 告诉usb_monitor scsi disk设备已经注销 */
    {
        u32 is_reg = 0;
        ////usbm_sendcmd(DEV_IOC_USR_HWSC_USBH_MSC_DEV_REG_SET, &is_reg);
    }
    ShutDown(BlkDev);
    /* media change线程已经停止了, 所以现在可以直接删除MediaChange */
    ENTER_CRITICAL(cpu_sr);
    mscLun->MediaChange = NULL;
    mscLun->sdev_data = NULL;
    EXIT_CRITICAL(cpu_sr);

    if (BlkDev->Extern)
    {
        hal_free(BlkDev->Extern);
        BlkDev->Extern = NULL;
    }

    UsbBlkDevFree(BlkDev);
    mscLun->sdev_data = NULL;
    return USB_ERR_SUCCESS;
}



