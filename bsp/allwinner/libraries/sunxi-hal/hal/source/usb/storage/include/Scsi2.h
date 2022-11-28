/*
********************************************************************************************************************
*                                              usb host driver
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : Scsi2.h
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
#ifndef  __SCSI2_H__
#define  __SCSI2_H__

//----------------------------------------------------------------------------
// scsi-2
//----------------------------------------------------------------------------

// timeout values (milliseconds)
#define  SCSI_MEDIA_POLL_INTERVAL    1250   /* 1.25s, 查询media change间隔时间  */
#define  SCSI_MEDIA_OP_TIMEOUT       40000  /* 10s, 读/写等介质操作超时时间     */
#define  SCSI_COMMAND_TIMEOUT        20000   /* 2s, 普通命令超时时间             */

#define  SCSI_CMD_RETRY              3

/* CDB size */
#define SCSI_CDB_6                  6
#define SCSI_CDB_10                 10
#define SCSI_CDB_16                 16
#define UFI_CDB                     12
#define ATAPI_CDB                   12
#define MAX_CDB                     SCSI_CDB_16

// SCSI-2 device types
#define SCSI_DEVICE_DIRECT_ACCESS     0x00
#define SCSI_DEVICE_SEQUENTIAL_ACCESS 0x01
#define SCSI_DEVICE_PRINTER           0x02
#define SCSI_DEVICE_PROCESSOR         0x03
#define SCSI_DEVICE_WRITE_ONCE        0x04
#define SCSI_DEVICE_CDROM             0x05
#define SCSI_DEVICE_SCANNER           0x06
#define SCSI_DEVICE_OPTICAL           0x07
#define SCSI_DEVICE_MEDIUM_CHANGER    0x08
#define SCSI_DEVICE_COMM              0x09
#define SCSI_DEVICE_UNKNOWN           0x1F

// SCSI-2 medium types
#define SCSI_MEDIUM_UNKNOWN           0xFF

// CD-ROM medium types
#define MEDIUM_CD_ROM_UNKNOWN                       0x00
#define MEDIUM_CD_ROM_DATA_ONLY_120                 0x01
#define MEDIUM_CD_DA_AUDIO_ONLY_120                 0x02
#define MEDIUM_CD_ROM_DATA_AUDIO_COMBINED_120       0x03
#define MEDIUM_CD_PHOTO_CD_120                      0x04
#define MEDIUM_CD_ROM_DATA_ONLY_80                  0x05
#define MEDIUM_CD_DA_AUDIO_ONLY_80                  0x06
#define MEDIUM_CD_ROM_DATA_AUDIO_COMBINED_80        0x07
#define MEDIUM_CD_PHOTO_CD_80                       0x08

#define MEDIUM_CDR_ROM_UNKNOWN                      0x10
#define MEDIUM_CDR_ROM_DATA_ONLY_120                0x11
#define MEDIUM_CDR_DA_AUDIO_ONLY_120                0x12
#define MEDIUM_CDR_ROM_DATA_AUDIO_COMBINED_120      0x13
#define MEDIUM_CDR_PHOTO_CD_120                     0x14
#define MEDIUM_CDR_ROM_DATA_ONLY_80                 0x15
#define MEDIUM_CDR_DA_AUDIO_ONLY_80                 0x16
#define MEDIUM_CDR_ROM_DATA_AUDIO_COMBINED_80       0x17
#define MEDIUM_CDR_PHOTO_CD_80                      0x18

#define MEDIUM_CDE_ROM_UNKNOWN                      0x20
#define MEDIUM_CDE_ROM_DATA_ONLY_120                0x21
#define MEDIUM_CDE_DA_AUDIO_ONLY_120                0x22
#define MEDIUM_CDE_ROM_DATA_AUDIO_COMBINED_120      0x23
#define MEDIUM_CDE_PHOTO_CD_120                     0x24
#define MEDIUM_CDE_ROM_DATA_ONLY_80                 0x25
#define MEDIUM_CDE_DA_AUDIO_ONLY_80                 0x26
#define MEDIUM_CDE_ROM_DATA_AUDIO_COMBINED_80       0x27
#define MEDIUM_CDE_PHOTO_CD_80                      0x28


// mandatory SCSI-2 commands
#define SCSI_TEST_UNIT_READY      0x00
#define SCSI_REQUEST_SENSE        0x03
#define SCSI_INQUIRY              0x12
#define SCSI_SEND_DIAGNOSTIC      0x1D

// mandatory device-specific SCSI-2 commands
#define SCSI_READ6                0x08
#define SCSI_READ10               0x28
#define SCSI_READ16               0x88
#define SCSI_READ_CAPACITY        0x25

// optional device-specific SCSI-2 commands
#define SCSI_MODE_SELECT6         0x15
#define SCSI_MODE_SENSE6          0x1A
#define SCSI_START_STOP           0x1B
#define SCSI_WRITE6               0x0A
#define SCSI_WRITE10              0x2A
#define SCSI_WRITE16              0x8A
#define SCSI_SYNCHRONIZE_CACHE    0x35
#define SCSI_MODE_SELECT10        0x55
#define SCSI_MODE_SENSE10         0x5A

// ATAPI (CD-ROM) commands
#define SCSI_CD_PAUSE_RESUME                    0x4B
#define SCSI_CD_PLAY_AUDIO10                    0x45
#define SCSI_CD_PLAY_AUDIO_MSF                  0x47
#define SCSI_CD_PLAY_CD                         0xBC
#define SCSI_CD_READ_TOC                        0x43
#define SCSI_CD_STOP_PLAY_SCAN                  0x4E
#define SCSI_CD_SET_SPEED                       0xBB

// ATAPI (DVD) commands
#define SCSI_DVD_GET_EVENT_STATUS_NOTIFICATION  0x4A
#define SCSI_DVD_LOAD_UNLOAD                    0xA6
#define SCSI_DVD_PREVENT_ALLOW_MEDIUM_REMOVAL   0x1E
#define SCSI_DVD_READ_DISC_INFORMATION          0x51
#define SCSI_DVD_READ_TRACK_INFORMATION         0x52

// mode pages
#define MODE_PAGE_FLEXIBLE_DISK     0x05
#define MODE_PAGE_WCACHING_PAGE     0x08
#define MODE_PAGE_CDROM             0x0D
#define MODE_PAGE_CDROM_AUDIO       0x0E
#define MODE_PAGE_POWER_CONDITION   0x1A
#define MODE_PAGE_CDROM_CAPS        0x2A
#define MODE_PAGE_ALL_PAGES         0x3F

// SCSI-2 sense keys
#define SENSE_NONE                0x00
#define SENSE_RECOVERED_ERROR     0x01
#define SENSE_NOT_READY           0x02
#define SENSE_MEDIUM_ERROR        0x03
#define SENSE_HARDWARE_ERROR      0x04
#define SENSE_ILLEGAL_REQUEST     0x05
#define SENSE_UNIT_ATTENTION      0x06
#define SENSE_DATA_PROTECT        0x07
#define SENSE_BLANK_CHECK         0x08

// SCSI-2 ASC
#define ASC_LUN                   0x04
#define ASC_INVALID_COMMAND_FIELD 0x24
#define ASC_MEDIA_CHANGED         0x28
#define ASC_RESET                 0x29
#define ASC_COMMANDS_CLEARED      0x2F
#define ASC_MEDIUM_NOT_PRESENT    0x3A



//----------------------------------------------------------------------------
// 命令执行的结果
//----------------------------------------------------------------------------
#define  USB_STATUS_SUCCESS                                 0   /* 命令执行成功                 */

/* 输入参数 */
#define  USB_STATUS_BAD_ARGUMENTS                           1   /* 参数错误                     */
#define  USB_STATUS_BUFFER_TOO_SMALL                        2   /* 输入buffer太小               */

/* 设备相关 */
#define  USB_STATUS_DEVICE_DISCONNECTED                     30  /* 设备已经断开连接             */
#define  USB_STATUS_IO_TIMEOUT                              31  /* IO操作超时                   */
#define  USB_STATUS_IO_DEVICE_ERROR                         32  /* 设备错误                     */
#define  USB_STATUS_DEVICE_BUSY                             33  /* 设备忙                       */

/* 命令相关 */
#define  USB_STATUS_INVALID_COMMAND                         60  /* 不支持的命令                 */
#define  USB_STATUS_INVALID_FIELD_IN_COMMAND                61  /* 命令中有不支持的字段         */
#define  USB_STATUS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE      62  /* 超过最大逻辑块               */
#define  USB_STATUS_COMMAND_FAILED                          63  /* 命令执行失败                 */

/* 命令结果相关 */
#define  USB_STATUS_UNIT_NOT_READY                          91  /* 介质单元没有就绪             */
#define  USB_STATUS_MEDIA_NOT_PRESENT                       92  /* 媒体介质不存在               */
#define  USB_STATUS_NOT_READY_TO_READY_TRANSITION           93  /* Media从没有准备就绪到就绪    */
#define  USB_STATUS_UNRECOGNIZED_MEDIA                      94  /* 不支持的Media                */
#define  USB_STATUS_MEDIA_CHANGE                            95  /* Media发生变化                */
#define  USB_STATUS_UNKOWN_SENSE                            96  /* 未知sense                    */

#define  USB_STATUS_UNKOWN_ERROR                            255 /* 未知错误                     */



//----------------------------------------------------------------------------
// Inquiry返回的数据
//----------------------------------------------------------------------------
typedef struct __InquiryData
{
    unsigned char Device_Type : 5;           /* 设备类型                     */
    unsigned char Qualifier   : 3;           /* 外围标识符                   */

    unsigned char scsi_1             : 7;    /* 命令集版本                   */
    unsigned char Removable_Media    : 1;    /* 可移动位                     */

    unsigned char ANSI_Version   : 4;        /* 设备支持的命令集版本         */
    unsigned char ECMA_Version   : 2;        /* 设备支持的ECMA-111版本       */
    unsigned char ISO_Version    : 2;        /* 设备支持的ISO IS-9316版本    */

    unsigned char Data_Format;               /* 标准INQUIRY数据的响应格式    */
    unsigned char Additional_Length;         /* 附加长度                     */
    unsigned char res[3];

    unsigned char Vendor_Info[8];            /* 设备制造商                   */
    unsigned char Product_Info[16];          /* 产品信息                     */
    unsigned char Product_Revision[4];       /* 产品修订版                   */
} __attribute__((packed)) __InquiryData_t;


//----------------------------------------------------------------------------
// request sense 返回的数据
//----------------------------------------------------------------------------
typedef struct __SenseData
{
    unsigned char ErrorCode: 7;
    unsigned char Valid: 1;
    unsigned char SegmentNumber;
    unsigned char SenseKey: 4;
    unsigned char Reserved: 1;
    unsigned char IncorrectLength: 1;
    unsigned char EndOfMedia: 1;
    unsigned char FileMark: 1;
    unsigned char Information[4];
    unsigned char AdditionalSenseLength;
    unsigned char CommandSpecificInformation[4];
    unsigned char AdditionalSenseCode;
    unsigned char AdditionalSenseCodeQualifier;
    unsigned char FieldReplaceableUnitCode;
    unsigned char SenseKeySpecific[3];
} __attribute__((packed))  __SenseData_t;

//----------------------------------------------------------------------------
// mode sense 返回的数据
//----------------------------------------------------------------------------
#define  SCSI_MODE_SENSE_MAX_DATA_LEN       192

typedef struct __BlockDevSpecPara
{
    unsigned char res_1 : 4;
    unsigned char DpoFua : 1;    /* 是否支持禁止页输出和强迫单元存取 */
    unsigned char res_2 : 2;
    unsigned char WP: 1;         /* write protect */
} __attribute__((packed))  __BlockDevSpecPara_t;

typedef struct __ModeSense6Header
{
    unsigned char ModeDataLength;
    unsigned char MediumType;
    unsigned char DevSpecPara;
    unsigned char BlockDescLength;
} __attribute__((packed)) __ModeSense6Header_t;

typedef struct __ModeSense10Header
{
    unsigned short ModeDataLength;
    unsigned char  MediumType;
    unsigned char  DeviceSpecPara;
    unsigned char  res[2];
    unsigned short BlockDescLength;
} __attribute__((packed)) __ModeSense10Header_t;

//----------------------------------------------------------------------------
// CD_Rom
//----------------------------------------------------------------------------

/* Play audio starting at MSF and ending at MSF */
typedef struct _CDROM_PlayAudioMsf
{
    unsigned char StartingM;
    unsigned char StartingS;
    unsigned char StartingF;
    unsigned char EndingM;
    unsigned char EndingS;
    unsigned char EndingF;
} CDROM_PlayAudioMsf_t;

/*
 *
 * C/DVD Read TOC
 *
 */

/* Format code definitions for readtoc command */
#define  CDROM_READTOC_FORMAT_CODE_TOC          0x00
#define  CDROM_READTOC_FORMAT_CODE_Session      0x01
#define  CDROM_READTOC_FORMAT_CODE_FULL_TOC     0x02
#define  CDROM_READTOC_FORMAT_CODE_PMA          0x03
#define  CDROM_READTOC_FORMAT_CODE_ATIP         0x04
#define  CDROM_READTOC_FORMAT_CODE_CD_TEXT      0x05

/* Maximum CD Rom size */
#define  MAXIMUM_NUMBER_TRACKS          100
#define  MAXIMUM_CDROM_SIZE             804

#define MAXIMUM_NUMBER_TRACKS_LARGE     0xAA

/* toc header */
typedef struct _CDROM_TocHeader
{
    unsigned short TocDataLength;
    unsigned char  FirstTrack;
    unsigned char  LastTrack;
} __attribute__((packed)) CDROM_TocHeader_t;

/* data track */
typedef struct _CDROM_TrackData
{
    unsigned char Reserved1;
    unsigned char Control : 4;
    unsigned char Adr     : 4;
    unsigned char TrackNumber;
    unsigned char Reserved2;

    unsigned int Address;
} __attribute__((packed)) CDROM_TrackData_t;

/* MSF address Format. see SFF-8020i page78 Table27 */
typedef struct _CDROM_MSF_ADDR
{
    unsigned char Reserved1;
    unsigned char Minute;
    unsigned char Second;
    unsigned char Frame;
} __attribute__((packed)) CDROM_MSF_ADDR_t;

/* MSF track */
typedef struct _CDROM_TrackMSF
{
    unsigned char Reserved1;
    unsigned char Control : 4;
    unsigned char Adr     : 4;
    unsigned char TrackNumber;
    unsigned char Reserved2;

    CDROM_MSF_ADDR_t MSF;
} __attribute__((packed)) CDROM_TrackMSF_t;

/*
 *
 * C/DVD mode sense
 *
 */
/* PageCode 1Ah. c/dvd power condition mode page format */
typedef struct _CDROM_PowerConditionPage
{
    unsigned char PageCode  : 6;
    unsigned char reserved1 : 1;
    unsigned char PS        : 1;

    unsigned char PageLength;

    unsigned char Standby   : 1;
    unsigned char Idle      : 1;
    unsigned char reserved2 : 6;

    unsigned int IdleTimer;
    unsigned int StandbyTimer;
} __attribute__((packed)) CDROM_PowerConditionPage_t;

/* PageCode 0Eh. cd audio control mode page format */
typedef struct _CDROM_ParameterPage
{
    unsigned char PageCode  : 6;
    unsigned char reserved1 : 1;
    unsigned char PS        : 1;

    unsigned char PageLength;

    unsigned char reserved2;
    unsigned char InactivityTimeMultiplier   : 4;
    unsigned char reserved3                  : 4;
    unsigned short NumberOfMSF_SUnitPerMUnit;
    unsigned short NumberOfMSF_FUnitPerSUnit;
} __attribute__((packed)) CDROM_ParameterPage_t;

/* PageCode 0Eh. cd audio control mode page format */
typedef  struct _CDROM_AudioControlPage
{
    unsigned char PageCode  : 6;
    unsigned char reserved1 : 1;
    unsigned char PS        : 1;

    unsigned char PageLength;

    unsigned char reserved2 : 1;
    unsigned char SOTC      : 1;
    unsigned char Immed     : 1;
    unsigned char reserved3 : 5;

    unsigned char reserved4[3];
    unsigned char Obsolete;

    unsigned char Port0Selection : 4;
    unsigned char reserved5      : 4;
    unsigned char Port0Volume;

    unsigned char Port1Selection : 4;
    unsigned char reserved6      : 4;
    unsigned char Port1Volume;

    unsigned char Port2Selection : 4;
    unsigned char reserved7      : 4;
    unsigned char Port2Volume;

    unsigned char Port3Selection : 4;
    unsigned char reserved8      : 4;
    unsigned char Port3Volume;
} __attribute__((packed)) CDROM_AudioControlPage_t;

/* PageCode 2Ah. c/dvd capabilities and mechanical status page. see SFF-8020i & SFF-8090 */
typedef struct _CDROM_Capitilities
{
    unsigned char PageCode  : 6;
    unsigned char reserved1 : 1;
    unsigned char PS        : 1;

    unsigned char PageLength;

    /* Byte2. see SFF-8090 */
    unsigned char CD_R_Rd      : 1;
    unsigned char CD_E_Rd      : 1;
    unsigned char Method2      : 1;
    unsigned char DVD_ROM_Read : 1;
    unsigned char DVD_R_Read   : 1;
    unsigned char DVD_RAM_Read : 1;
    unsigned char reserved2    : 2;

    /* Byte3. see SFF-8090 */
    unsigned char CD_R_Wr      : 1;
    unsigned char CD_E_Wr      : 1;
    unsigned char TestWrite    : 1;
    unsigned char reserved3    : 1;
    unsigned char DVD_R_Write  : 1;
    unsigned char DVD_RAM_Wr   : 1;
    unsigned char reserved4    : 2;

    /* Byte4 */
    unsigned char AudioPlay      : 1;
    unsigned char Composite      : 1;
    unsigned char DigitalPort1   : 1;
    unsigned char DigitalPort2   : 1;
    unsigned char Mode2_Form1    : 1;
    unsigned char Mode2_Form2    : 1;
    unsigned char MultiSession   : 1;
    unsigned char reserved5      : 1;

    /* Byte5 */
    unsigned char CD_DA              : 1;
    unsigned char DAAccu             : 1;
    unsigned char RW_supported       : 1;
    unsigned char RW_De_Interleaved  : 1;
    unsigned char C2_Pointers        : 1;
    unsigned char ISRC               : 1;
    unsigned char UPC                : 1;
    unsigned char ReadBarCodeCapable : 1;

    /* Byte6 */
    unsigned char Lock                   : 1;
    unsigned char LockState              : 1;
    unsigned char PreventJumper          : 1;
    unsigned char Eject                  : 1;
    unsigned char reserved6              : 1;
    unsigned char LoadingMechanismType   : 3;

    /* Byte7 */
    unsigned char SeparateVolume         : 1;
    unsigned char SeparateChannelMute    : 1;
    unsigned char SupportsDiscPresent    : 1;
    unsigned char SW_SlotSelection       : 1;
    unsigned char SideChangeCapable      : 1;
    unsigned char reserved7              : 3;

    unsigned short MaximumSpeedSupport;              /* Byte8-9. see SFF-8020i   */
    unsigned short NumberOfVolumelevelsSupported;    /* Byte10-11                */
    unsigned short BufferSizeSupportedByLogicUnit;   /* Byte12-13                */
    unsigned short CurrentSpeedSelected;             /* Byte14-15 see SFF-8020i  */

    unsigned char  ObsoleteReserved3;                /* Byte16                   */

    /* Byte17 */
    unsigned char reserved8  : 1;
    unsigned char BCK        : 1;
    unsigned char RCK        : 1;
    unsigned char LSBF       : 1;
    unsigned char Length     : 2;
    unsigned char reserved9  : 2;

    unsigned short ObsoleteReserved4;                /* Byte18-19    */
    unsigned short CopyManagementRevisionsupport;    /* Byte20-21    */
    unsigned char  reserved10;
    unsigned char  reserved11;
} __attribute__((packed)) CDROM_Capitilities_t;

/*
 *
 * C/DVD envent status
 *
 */
#define  CDROM_GET_EVENT_CMD_MAX_RETURN_DATA_LEN        0xff /* 通常都是8个byte */

/* Notification class request */
#define  CDROM_NOTIFICATION_CLASS_REQUEST_POWER_MANAGEMENT  0x04
#define  CDROM_NOTIFICATION_CLASS_REQUEST_MEDIA_STATUS      0x10
#define  CDROM_NOTIFICATION_CLASS_REQUEST_DEVICE_BUSY       0x40

/* Notification class field */
#define  CDROM_NOTIFICATION_CLASS_FIELD_POWER_MANAGEMENT    0x02
#define  CDROM_NOTIFICATION_CLASS_FIELD_MEDIA_STATUS        0x04
#define  CDROM_NOTIFICATION_CLASS_FIELD_DEVICE_BUSY         0x06

/* Event Status Header */
typedef struct _CDROM_EventHeader
{
    unsigned short EventDataLength;

    unsigned char NotificationClass  : 3;
    unsigned char reserved1          : 4;
    unsigned char NEA                : 1;

    unsigned char SupportEventClass;
} __attribute__((packed)) CDROM_EventHeader_t;

/* Power Management Status Class Returned Data */
#define  CDROM_POWER_EVENT_NOCHG            0x00
#define  CDROM_POWER_EVENT_PWRCHG_SUCC      0x01
#define  CDROM_POWER_EVENT_PWRCHG_FAIL      0x02

#define  CDROM_POWER_STATUS_ACTIVE          0x01
#define  CDROM_POWER_STATUS_IDLE            0x02
#define  CDROM_POWER_STATUS_STANDBY         0x03

typedef struct _CDROM_PowerStatus
{
    unsigned char PowerEvent : 4;
    unsigned char reserved1  : 4;

    unsigned char PowerStatus;
    unsigned char reserved2;
    unsigned char reserved3;
} __attribute__((packed)) CDROM_PowerStatus_t;

/* Media Status Class Returned Data */
#define  CDROM_MEDIA_STATUS_EJECT_REQUEST   0x01
#define  CDROM_MEDIA_STATUS_NEW_MEDIA       0x02
#define  CDROM_MEDIA_STATUS_MEDIA_REMOVAL   0x03

typedef struct _CDROM_MediaStatus
{
    unsigned char MediaStatus : 4;
    unsigned char reserved1   : 4;

    unsigned char DoorOpen    : 1;
    unsigned char MediaPesent : 1;
    unsigned char reserved    : 6;

    unsigned char StartSlot;
    unsigned char EndSlot;
} __attribute__((packed)) CDROM_MediaStatus_t;

/* Device Busy Status Class Returned Data */
#define  CDROM_DEVICE_BUSY_EVENT_TIMEOUT_OCCURED    0x03

#define  CDROM_DEVICE_BUSY_STATUS_NOEVENT           0x00
#define  CDROM_DEVICE_BUSY_STATUS_POWER             0x01
#define  CDROM_DEVICE_BUSY_STATUS_IMMEDIATE         0x02
#define  CDROM_DEVICE_BUSY_STATUS_DEFERED           0x03

typedef struct _CDROM_DeviceBusyStatus
{
    unsigned char  DeviceBusyEvent   : 4;
    unsigned char  reserved1         : 4;

    unsigned char  DeviceBusyStatus;
    unsigned short Time;
} __attribute__((packed)) CDROM_DeviceBusyStatus_t;

/*
 *
 * C/DVD Get Configuration
 *
 */
#define  CDROM_FEATURE_LIST_PROFILE_LIST                        0x00
#define  CDROM_FEATURE_LIST_CORE                                0x01
#define  CDROM_FEATURE_LIST_MORPHING                            0x02
#define  CDROM_FEATURE_LIST_REMOVABLE_MEDIUM                    0x03
#define  CDROM_FEATURE_LIST_WRITE_PROTECT                       0x04
#define  CDROM_FEATURE_LIST_RANDOM_READABLE                     0x10
#define  CDROM_FEATURE_LIST_MULTIREAD                           0x1D
#define  CDROM_FEATURE_LIST_CD_READ                             0x1E
#define  CDROM_FEATURE_LIST_DVD_READ                            0x1F
#define  CDROM_FEATURE_LIST_RANDOM_WRITABLE                     0x20
#define  CDROM_FEATURE_LIST_INCREMENTAL_STREAMING_WRITABLE      0x21
#define  CDROM_FEATURE_LIST_FORMATTABLE                         0x23
#define  CDROM_FEATURE_LIST_HARDWARE_DEFECT_MANAGEMENT          0x24
#define  CDROM_FEATURE_LIST_WRITE_ONCE                          0x25
#define  CDROM_FEATURE_LIST_RESTRICTED_OVERWRITE                0x26
#define  CDROM_FEATURE_LIST_CD_RW_CAV_WRITE                     0x27
#define  CDROM_FEATURE_LIST_MRW                                 0x28
#define  CDROM_FEATURE_LIST_ENHABCED_DEFECT_REPORTING           0x29
#define  CDROM_FEATURE_LIST_DVD_RW                              0x2A
#define  CDROM_FEATURE_LIST_DVD_R                               0x2B
#define  CDROM_FEATURE_LIST_RIGID_RESTRICTED_OVERWRITE          0x2C
#define  CDROM_FEATURE_LIST_CD_TRACK_AT_ONCE                    0x2D
#define  CDROM_FEATURE_LIST_CD_MASTERING                        0x2E
#define  CDROM_FEATURE_LIST_DVD_R_RW_WRITE                      0x2F
#define  CDROM_FEATURE_LIST_LAYER_JUMP_RECORDING                0x33
#define  CDROM_FEATURE_LIST_LJ_RIGID_RESTRICTED_OVERWRITE       0x34
#define  CDROM_FEATURE_LIST_STOP_LONG_OPERATION                 0x35
#define  CDROM_FEATURE_LIST_CD_RW_MEDIA_WRITE_SUPPORT           0x37
#define  CDROM_FEATURE_LIST_BD_R_PSEUDO_OVERWRITE_FEATURE       0x38
#define  CDROM_FEATURE_LIST_DVD_RW_DUAL_LAYER                   0x3A
#define  CDROM_FEATURE_LIST_DVD_R_DUAL_LAYER                    0x3B
#define  CDROM_FEATURE_LIST_BD_READ                             0x40
#define  CDROM_FEATURE_LIST_BD_WRITE                            0x41
#define  CDROM_FEATURE_LIST_TSR                                 0x42
#define  CDROM_FEATURE_LIST_HD_DVD_READ                         0x50
#define  CDROM_FEATURE_LIST_HD_DVD_WRITE                        0x51
#define  CDROM_FEATURE_LIST_HD_DVD_RW_FRAGMENT_RECORDING        0x52
#define  CDROM_FEATURE_LIST_HYBRID_DISC                         0x80
#define  CDROM_FEATURE_LIST_POWER_MANAGEMENT                    0x100
#define  CDROM_FEATURE_LIST_SMART                               0x101
#define  CDROM_FEATURE_LIST_EMBEDDED_CHANGER                    0x102
#define  CDROM_FEATURE_LIST_CD_AUDIO_ANALOG_PLAY                0x103
#define  CDROM_FEATURE_LIST_MICROCODE_UPGRADE                   0x104
#define  CDROM_FEATURE_LIST_TIMEOUT                             0x105
#define  CDROM_FEATURE_LIST_DVD_CSS                             0x106
#define  CDROM_FEATURE_LIST_REAL_TIME_STREAMING                 0x107
#define  CDROM_FEATURE_LIST_LOGICAL_UNIT_SERIAL_NUMBER          0x108
#define  CDROM_FEATURE_LIST_MEDIA_SERIAL_NUMBER                 0x109
#define  CDROM_FEATURE_LIST_DISC_CONTROL_BLOCKS                 0x10A
#define  CDROM_FEATURE_LIST_DVD_CPRM                            0x10B
#define  CDROM_FEATURE_LIST_FIRMWARE_INFORMATION                0x10C
#define  CDROM_FEATURE_LIST_AACS                                0x10D
#define  CDROM_FEATURE_LIST_DVD_CSS_MANAGED_RECORDING           0x10E
#define  CDROM_FEATURE_LIST_VCPS                                0x110
#define  CDROM_FEATURE_LIST_SECUR_DISC                          0x113

/*
 *
 * C/DVD Read Disc Information
 *
 */

/* Data Type Field definition */
#define  CDROM_DISC_INFO_STANDARD               0x00
#define  CDROM_DISC_INFO_TRACK_RESOURCES        0x00
#define  CDROM_DISC_INFO_POW_RESOURCES          0x00

/* C/DVD Disc Information Block Data */
typedef struct _CDROM_DiscInfo
{
    unsigned short DataInformationLength;

    unsigned char  DiscStatus                : 2;
    unsigned char  StatusOfLastSession       : 2;
    unsigned char  Erasable                  : 1;
    unsigned char  DiscInformationDataType   : 3;

    unsigned char  FirstTrackNumberOnDisc;
    unsigned char  NumberOfSessions_LSB;
    unsigned char  FirstTrackNumberInLastSession_LSB;
    unsigned char  LastTrackNumberInLastSession_LSB;

    unsigned char  BG_FormatStatus   : 2;
    unsigned char  Dbit              : 1;
    unsigned char  reserved1         : 1;
    unsigned char  DAC_V             : 1;
    unsigned char  URU               : 1;
    unsigned char  DBC_V             : 1;
    unsigned char  DID_V             : 1;

    unsigned char  DiscType;
    unsigned char  NumberOfSessions_MSB;
    unsigned char  FirstTrackNumberInLastSession_MSB;
    unsigned char  LastTrackNumberInLastSession_MSB;

    unsigned int DiscIdentification;
    unsigned int LeadInStartTimeOfLastSession_MSF;
    unsigned int LastPossibleStartTimeForStartOfLeadOut_MSF;
    unsigned char  DiscBarCode[8];
    unsigned char  DiscApplicationCode;
    unsigned char  NumberOfOPCTableEntries;

    /* OPCTableEntries */
} __attribute__((packed)) CDROM_DiscInfo_t;

/* Status of last session field definition */
#define  CDROM_DISC_INFO_STATUS_OF_LAST_SESSION_EMPTY           0x00
#define  CDROM_DISC_INFO_STATUS_OF_LAST_SESSION_IMCOMPLETE      0x01
#define  CDROM_DISC_INFO_STATUS_OF_LAST_SESSION_DAMAGED_BOARDER 0x02
#define  CDROM_DISC_INFO_STATUS_OF_LAST_SESSION_COMPLETE        0x03

/* Disc status field definition */
#define  CDROM_DISC_INFO_DISC_STATUS_EMPTY                      0x00
#define  CDROM_DISC_INFO_DISC_STATUS_IMCOMPLETE                 0x01
#define  CDROM_DISC_INFO_DISC_STATUS_COMPLETE                   0x02
#define  CDROM_DISC_INFO_DISC_STATUS_FINALIZATION               0x03

/* BG foramt status field definition */
#define  CDROM_DISC_INFO_BG_FORMAT_STATUS_EMPTY                 0x00
#define  CDROM_DISC_INFO_BG_FORMAT_STATUS_NOT_RUNNING           0x01
#define  CDROM_DISC_INFO_BG_FORMAT_STATUS_RUNNING               0x02
#define  CDROM_DISC_INFO_BG_FORMAT_STATUS_COMPLETE              0x03

/* Disk type field definition */
#define  CDROM_DISC_INFO_DISC_TYPE_CDDA_CDROM                   0x00
#define  CDROM_DISC_INFO_DISC_TYPE_CDI                          0x10
#define  CDROM_DISC_INFO_DISC_TYPE_CD_XA                        0x20


/*
 *
 * C/DVD Read Track Information
 *
 */
#define  CDROM_TRACK_INFO_ADDRESS_NUMBER_TYPE_LBA               0x00
#define  CDROM_TRACK_INFO_ADDRESS_NUMBER_TYPE_TRACK_NUMBER      0x01
#define  CDROM_TRACK_INFO_ADDRESS_NUMBER_TYPE_BORDER_NUMBER     0x02

typedef struct _CDROM_TrackInfo
{
    unsigned short TrackInformationlength;
    unsigned char  TrackNumber_LSB;
    unsigned char  SessionNumber_LSB;
    unsigned char  reserved1;

    unsigned char  TrackMode : 4;
    unsigned char  Copy      : 1;
    unsigned char  Damage    : 1;
    unsigned char  LJRS      : 2;

    unsigned char  DataMode  : 4;
    unsigned char  FP        : 1;
    unsigned char  Packet    : 1;
    unsigned char  Blank     : 1;
    unsigned char  RT        : 1;

    unsigned char  NWA_V     : 1;        /* next write address valid     */
    unsigned char  LRA_V     : 1;        /* last recorded address valid  */
    unsigned char  reserved2 : 6;

    unsigned int TrackStartAddress;
    unsigned int NextWritableAddress;
    unsigned int FreeBlocks;
    unsigned int FixedPacketSize;
    unsigned int TrackSizeEndAddress;
    unsigned int LastRecordedAddress;
    unsigned char  TrackNumber_MSB;
    unsigned char  SessionNumber_MSB;
    unsigned char  reserved3;
    unsigned int ReadCompatibilityLBA;
    unsigned int NextLayerJumpAddress;
    unsigned int LastLayerJumpAddress;
} __attribute__((packed)) CDROM_TrackInfo_t;









//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
int ScsiInquery(__mscLun_t *mscLun, void *buffer, unsigned int buffer_len);
int ScsiReadCapacity(__mscLun_t *mscLun);
int ScsiModeSense6(__mscLun_t *mscLun,
                     unsigned int PageCode,
                     unsigned int DBD,
                     void *buffer,
                     unsigned int buffer_len,
                     unsigned int *ActLen);
int ScsiModeSense10(__mscLun_t *mscLun,
                      unsigned int PageCode,
                      unsigned int DBD,
                      void *buffer,
                      unsigned int buffer_len,
                      unsigned int *ActLen);
int ScsiTestUnitReady(__mscLun_t *mscLun);
int ScsiRequestSense(__mscLun_t *mscLun, void *buffer, unsigned int buffer_len);
static int ScsiGetSenseData(__mscLun_t *mscLun);
int ScsiStartStopUnit(__mscLun_t *mscLun, unsigned int LoEj, unsigned int Start);
int ScsiSynchronizeCache(__mscLun_t *mscLun);
int ScsiRead(__mscLun_t *mscLun,
               unsigned int Version,
               unsigned int StartSector,
               unsigned int NumSectors,
               void *buffer,
               unsigned int buffer_len);
int ScsiWrite(__mscLun_t *mscLun,
                unsigned int Version,
                unsigned int StartSector,
                unsigned int NumSectors,
                void *buffer,
                unsigned int buffer_len);
int ScsiPreventAllowMedium(__mscLun_t *mscLun, unsigned int Persistent, unsigned int Prevent);

/* C/DVD */
int ScsiCDPauseResume(__mscLun_t *mscLun, unsigned int Resume);
int ScsiCDPlayAudio10(__mscLun_t *mscLun, unsigned int Lba, unsigned int Lenght);
int ScsiCDPlayAudioMSF(__mscLun_t *mscLun, CDROM_PlayAudioMsf_t *msf);
int ScsiCDReadToc(__mscLun_t *mscLun,
                    unsigned int MSF,
                    unsigned int Format,
                    unsigned int StartingNumber,
                    void *Buffer,
                    unsigned int BufferLen);
int ScsiCDStopPlayScan(__mscLun_t *mscLun);
int ScsiCDReadDiscInfo(__mscLun_t *mscLun,
                         unsigned int DataType,
                         void *Buffer,
                         unsigned int BufferLen,
                         unsigned int *ActLen);
int ScsiCDReadTrackInfo(__mscLun_t *mscLun,
                          unsigned int Open,
                          unsigned int Address_or_Number,
                          unsigned int LogicalBlockAddress,
                          void *Buffer,
                          unsigned int BufferLen,
                          unsigned int *ActLen);
int ScsiDvdGetEventStatus(__mscLun_t *mscLun,
                            unsigned int Immed,
                            unsigned int ClassRequest,
                            void *Buffer,
                            unsigned int BufferLen);
int ScsiDvdLoad(__mscLun_t *mscLun,
                  unsigned int Immed,
                  unsigned int Start,
                  unsigned int LoUnlo,
                  unsigned int Slot);
int ScsiCDSetSpeed(__mscLun_t *mscLun, unsigned int ReadSpeed, unsigned int WriteSpeed);
int ScsiDVDGetConfiguration(__mscLun_t *mscLun,
                              unsigned int RT,
                              unsigned int StartingFeatureNumber,
                              void *Buffer,
                              unsigned int BufferLen);


#endif   //__SCSI2_H__





