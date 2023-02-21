/*
********************************************************************************************************************
*                                              usb host driver
*
*                              (c) Copyright 2007-2010, javen.China
*                                       All Rights Reserved
*
* File Name     : CD.h
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
#ifndef  __CD_H__
#define  __CD_H__

/* CD-ROM address types */
#define CDROM_LBA 0x01  /* data-related.  "logical block": first frame is #0            */
#define CDROM_MSF 0x02  /* audio-related. "minute-second-frame": binary, not bcd here!  */

/* Some generally useful CD-ROM information -- mostly based on the above */
#define CD_MINS              74 /* max. minutes per CD, not really a limit  */
#define CD_SECS              60 /* seconds per minute                       */
#define CD_FRAMES            75 /* frames per second                        */
#define CD_SYNC_SIZE         12 /* 12 sync bytes per raw data frame         */
#define CD_MSF_OFFSET       150 /* MSF numbering offset of first frame      */
#define CD_CHUNK_SIZE        24 /* lowest-level "data bytes piece"          */
#define CD_NUM_OF_CHUNKS     98 /* chunks per frame                         */
#define CD_FRAMESIZE_SUB     96 /* subchannel data "frame" size             */
#define CD_HEAD_SIZE          4 /* header (address) bytes per raw data frame */
#define CD_SUBHEAD_SIZE       8 /* subheader bytes per raw XA data frame    */
#define CD_EDC_SIZE           4 /* bytes EDC per most raw data frame types  */
#define CD_ZERO_SIZE          8 /* bytes zero per yellow book mode 1 frame  */
#define CD_ECC_SIZE         276 /* bytes ECC per most raw data frame types  */
#define CD_FRAMESIZE       2048 /* bytes per frame, "cooked" mode           */
#define CD_FRAMESIZE_RAW   2352 /* bytes per frame, "raw" mode              */
#define CD_FRAMESIZE_RAWER 2646 /* The maximum possible returned bytes      */

/* most drives don't deliver everything: */
#define CD_FRAMESIZE_RAW1 (CD_FRAMESIZE_RAW - CD_SYNC_SIZE)                 /*2340*/
#define CD_FRAMESIZE_RAW0 (CD_FRAMESIZE_RAW - CD_SYNC_SIZE - CD_HEAD_SIZE)  /*2336*/

#define CD_XA_HEAD        (CD_HEAD_SIZE + CD_SUBHEAD_SIZE)  /* "before data" part of raw XA frame */
#define CD_XA_TAIL        (CD_EDC_SIZE + CD_ECC_SIZE)       /* "after data" part of raw XA frame */
#define CD_XA_SYNC_HEAD   (CD_SYNC_SIZE + CD_XA_HEAD)       /* sync bytes + header of XA frame */


/* capability flags used with the uniform CD-ROM driver */
#define CDROM_CLOSE_TRAY        0x1         /* caddy systems _can't_ close          */
#define CDROM_OPEN_TRAY         0x2         /* but _can_ eject.                     */
#define CDROM_LOCK              0x4         /* disable manual eject                 */
#define CDROM_SELECT_SPEED      0x8         /* programmable speed                   */
#define CDROM_SELECT_DISC       0x10        /* select disc from juke-box            */
#define CDROM_MULTI_SESSION     0x20        /* read sessions>1                      */
#define CDROM_MCN               0x40        /* Medium Catalog Number                */
#define CDROM_MEDIA_CHANGED     0x80        /* media changed                        */
#define CDROM_PLAY_AUDIO        0x100       /* audio functions                      */
#define CDROM_RESET             0x200       /* hard reset device                    */
#define CDROM_DRIVE_STATUS      0x800       /* drive implements drive status        */
#define CDROM_GENERIC_PACKET    0x1000      /* drive implements generic packets     */
#define CDROM_CD_R              0x2000      /* drive is a CD-R                      */
#define CDROM_CD_RW             0x4000      /* drive is a CD-RW                     */
#define CDROM_DVD               0x8000      /* drive is a DVD                       */
#define CDROM_DVD_R             0x10000     /* drive can write DVD-R                */
#define CDROM_DVD_RAM           0x20000     /* drive can write DVD-RAM              */
#define CDROM_MO_DRIVE          0x40000     /* drive is an MO device                */
#define CDROM_MRW               0x80000     /* drive can read MRW                   */
#define CDROM_MRW_W             0x100000    /* drive can write MRW                  */
#define CDROM_RAM               0x200000    /* ok to open for WRITE                 */

/* bit to tell whether track is data or audio (cdrom_tocentry.cdte_ctrl) */
#define  CDROM_DATA_TRACK       0x04

/* The leadout track is always 0xAA, regardless of # of tracks on disc */
#define  CDROM_LEADOUT          0xAA

/* frame address */
typedef struct _MSF_LBA
{
    CDROM_MSF_ADDR_t msf;
    unsigned int lba;
} __attribute__((packed)) MSF_LBA_t;

/* 某个 track 的 Toc entry */
typedef struct _CDROM_TocEntry
{
    unsigned int TrackNumber;      /* Toc 所属的 track     */
    unsigned int Format;           /* CD-ROM address types */
    unsigned int Adr   : 4;        /* The type of information encode in the Q sub-channel of this blocks */
    unsigned int Ctrl  : 4;        /* attributes of the track */

    MSF_LBA_t Address;      /* Toc entry address    */
    unsigned int DataMode;         /* is a data track?     */
} CDROM_TocEntry_t;

typedef struct _CD_Rom
{
    /* 光驱的信息 */
    unsigned int DriveType;                    /* 光驱的型号               */
    unsigned int MaxSpeed;                     /* 光驱最大的速度           */
    unsigned int CurrentSpeed;                 /* 光驱当前的速度           */
    unsigned int Readcd_cdda;                  /* reading audio data using READ_CD */
    unsigned int WriteAble;                    /* 光驱是否支持写操作       */
    CDROM_Capitilities_t Capitilities;  /* 光驱的驱动能力           */
    unsigned int Eject;                        /* 是否支持光驱退出         */
    unsigned int PowerStatus;                  /* 光驱电源状态. Active, Idle, Standby ? */

    /* 光碟信息 */
    unsigned int DiscType;                     /* 光碟的型号               */
    unsigned int DoubleDisc;                   /* 是否是双面光碟?          */
    unsigned int LastWriteSector;              /* 但前已经写的最后一个扇区 */
    unsigned int MultiSession;                 /* 多区段                   */
    unsigned int NumberOfSUinitPerMUnit;       /* MSF中每M保护的s个数      */
    unsigned int NumberOfFUinitPerSUnit;       /* MSF中每S保护的F个数      */
    unsigned int InactivityTimeMultiPlier;     /*                          */

    /* 光驱管理 */
    unsigned int DriveStatus;                  /* 光驱状态                 */
    unsigned int IsMeduimPrevent;              /* 是否设置禁止介质移动     */
} CD_Rom_t;

/*
*******************************************************************************
*                     lba_to_msf
*
* Description:
*    LBA转换为msf
*
* Parameters:
*    lba    :  input.
*    m      :  input.
*    s      :  input.
*    f      :  input.
*
* Return value:
*    无
*
* note:
*    无
*
*******************************************************************************
*/
static inline void lba_to_msf(int lba, u8 *m, u8 *s, u8 *f)
{
    lba += CD_MSF_OFFSET;
    lba &= 0xffffff;        /* negative lbas use only 24 bits */
    *m  = lba / (CD_SECS * CD_FRAMES);
    lba %= (CD_SECS * CD_FRAMES);
    *s  = lba / CD_FRAMES;
    *f  = lba % CD_FRAMES;
}

/*
*******************************************************************************
*                     msf_to_lba
*
* Description:
*    msf转换为LBA
*
* Parameters:
*    m      :  input.
*    s      :  input.
*    f      :  input.
*
* Return value:
*
* note:
*    无
*
*******************************************************************************
*/
static inline int msf_to_lba(u8 m, u8 s, u8 f)
{
    return (((m * CD_SECS) + s) * CD_FRAMES + f) - CD_MSF_OFFSET;
}

int CDIOCtrl(__UsbBlkDev_t *BlkDev, unsigned int Cmd, int Aux, void *pBuffer);

#endif   //__CD_H__


