/*!
*******************************************************************************
**
** \file      gh_sdio_all.h
**
** \brief     SDIO Host Controller.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef _GH_SDIO_ALL_H
#define _GH_SDIO_ALL_H

#include "gtypes.h" /* global type definitions */
#include "gh_sdio0.h"
#include "gh_sdio1.h"

#define GH_SDIO0 0
#define GH_SDIO1 1

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* SDIO_TranModeReg */
    U16 all;
    struct {
        U16 blkcounten                  : 1;
        U16 autocmd12en                 : 1;
        U16 dmaen                       : 1;
        U16                             : 1;
        U16 msblkselect                 : 1;
        U16 datatradirselect            : 1;
        U16                             : 10;
    } bitc;
} GH_SDIO_TRANMODEREG_S;

typedef union { /* SDIO_NorIntSigEnReg */
    U16 all;
    struct {
        U16 cmdcompletesigen            : 1;
        U16 tracompletesigen            : 1;
        U16 blkgapevesigen              : 1;
        U16 dmaintsigen                 : 1;
        U16 bufwreadysigen              : 1;
        U16 bufrreadysigen              : 1;
        U16 cardinsertionsigen          : 1;
        U16 cardremsigen                : 1;
        U16 cardintsigen                : 1;
        U16                             : 6;
        U16 fixedto0                    : 1;
    } bitc;
} GH_SDIO_NORINTSIGENREG_S;

typedef union { /* SDIO_ErrIntSigEnReg */
    U16 all;
    struct {
        U16 cmdtimeouterrsigen          : 1;
        U16 cmdendbiterrsigen           : 1;
        U16 cmdindexerrsigen            : 1;
        U16 datatimeouterrsigen         : 1;
        U16 cmdcrcerrsigen              : 1;
        U16 datacrcerrsigen             : 1;
        U16 dataendbiterrsigen          : 1;
        U16 curlimiterrsigen            : 1;
        U16 autocmd12errsigen           : 1;
        U16                             : 5;
        U16 vendorspecificerrsigen      : 2;
    } bitc;
} GH_SDIO_ERRINTSIGENREG_S;

typedef union { /* SDIO_BlkCouReg */
    U16 all;
    struct {
        U16 blkcountforcurtra           : 16;
    } bitc;
} GH_SDIO_BLKCOUREG_S;

typedef union { /* SDIO_BlkSizeReg */
    U16 all;
    struct {
        U16 trablksize                  : 12;
        U16 hostsdmabufsize             : 3;
        U16                             : 1;
    } bitc;
} GH_SDIO_BLKSIZEREG_S;

typedef union { /* SDIO_NorIntStaEnReg */
    U16 all;
    struct {
        U16 cmdcompletestatusen         : 1;
        U16 tracompletestatusen         : 1;
        U16 blkgapevestatusen           : 1;
        U16 dmaintstatusen              : 1;
        U16 bufwreadystatusen           : 1;
        U16 bufrreadystatusen           : 1;
        U16 cardinsertionstatusen       : 1;
        U16 cardremstatusen             : 1;
        U16 cardintstatusen             : 1;
        U16                             : 6;
        U16 fixedto0                    : 1;
    } bitc;
} GH_SDIO_NORINTSTAENREG_S;

typedef union { /* SDIO_ErrIntStaEnReg */
    U16 all;
    struct {
        U16 cmdtimeouterrstatusen       : 1;
        U16 cmdendbiterrstatusen        : 1;
        U16 cmdcrcerrstatusen           : 1;
        U16 cmdindexerrstatusen         : 1;
        U16 datacrcerrstatusen          : 1;
        U16 datatimeouterrstatusen      : 1;
        U16 dataendbiterrstatusen       : 1;
        U16 curlimiterrstatusen         : 1;
        U16 autocmd12errstatusen        : 1;
        U16                             : 5;
        U16 vendorspecificerrstatusen   : 2;
    } bitc;
} GH_SDIO_ERRINTSTAENREG_S;

typedef union { /* SDIO_NorIntStaReg */
    U16 all;
    struct {
        U16 cmdcomplete                 : 1;
        U16 blkgapevent                 : 1;
        U16 dmaint                      : 1;
        U16 tracomplete                 : 1;
        U16 bufwready                   : 1;
        U16 cardinsertion               : 1;
        U16 bufrready                   : 1;
        U16 cardremoval                 : 1;
        U16 cardint                     : 1;
        U16 bootackrcv                  : 1;
        U16                             : 5;
        U16 errint                      : 1;
    } bitc;
} GH_SDIO_NORINTSTAREG_S;

typedef union { /* SDIO_ErrIntStatusReg */
    U16 all;
    struct {
        U16 cmdtimeouterr               : 1;
        U16 cmdcrcerr                   : 1;
        U16 cmdendbiterr                : 1;
        U16 cmdindexerr                 : 1;
        U16 datatimeouterr              : 1;
        U16 datacrcerr                  : 1;
        U16 dataendbiterr               : 1;
        U16 curlimiterr                 : 1;
        U16 autocmd12err                : 1;
        U16                             : 5;
        U16 vendorspecificerrstatus     : 2;
    } bitc;
} GH_SDIO_ERRINTSTATUSREG_S;

typedef union { /* SDIO_CommondReg */
    U16 all;
    struct {
        U16 reptypeselect               : 2;
        U16                             : 1;
        U16 cmdcrcchecken               : 1;
        U16 datapreselect               : 1;
        U16 cmdindexchecken             : 1;
        U16 cmdtype                     : 2;
        U16 cmdindex                    : 6;
        U16                             : 2;
    } bitc;
} GH_SDIO_COMMONDREG_S;

typedef union { /* SDIO_SoftResetReg */
    U16 all;
    struct {
        U16 datatimeoutcountervalue     : 4;
        U16                             : 4;
        U16 softwareresetcmdline        : 1;
        U16 softwareresetall            : 1;
        U16 softwareresetdatline        : 1;
        U16                             : 5;
    } bitc;
} GH_SDIO_SOFTRESETREG_S;

typedef union { /* SDIO_ClkControlReg */
    U16 all;
    struct {
        U16 internalclken               : 1;
        U16 internalclkstable           : 1;
        U16 sdclken                     : 1;
        U16                             : 5;
        U16 sdclkfreselect              : 8;
    } bitc;
} GH_SDIO_CLKCONTROLREG_S;

typedef union { /* SDIO_Control00Reg */
    U32 all;
    struct {
        U32 ledcontrol                  : 1;
        U32 datatrawidth                : 1;
        U32 sd8bitmode                  : 1;
        U32 hostspeeden                 : 1;
        U32                             : 2;
        U32 carddetecttestlevel         : 1;
        U32 carddetectsigdet            : 1;
        U32 sdbuspower                  : 1;
        U32 sdbusvoltageselect          : 3;
        U32                             : 4;
        U32 stopatblkgapreq             : 1;
        U32 rwaitcontrol                : 1;
        U32 continuereq                 : 1;
        U32 intatblkgap                 : 1;
        U32 driveccsd                   : 1;
        U32 spimode                     : 1;
        U32 booten                      : 1;
        U32 altbooten                   : 1;
        U32 wakeupevetenoncardins       : 1;
        U32 wakeupevetenoncardint       : 1;
        U32 wakeupevetenoncardrem       : 1;
        U32                             : 5;
    } bitc;
} GH_SDIO_CONTROL00REG_S;

typedef union { /* SDIO_PresentStateReg */
    U32 all;
    struct {
        U32 cmdinhibitcmd               : 1;
        U32 datalineactive              : 1;
        U32 cmdinhibitdata              : 1;
        U32                             : 5;
        U32 rtraactive                  : 1;
        U32 bufwen                      : 1;
        U32 wtraactive                  : 1;
        U32 bufren                      : 1;
        U32                             : 4;
        U32 cardinserted                : 1;
        U32 carddetectpinlevel          : 1;
        U32 cardstatestable             : 1;
        U32 wproswipinlevel             : 1;
        U32 data03linesiglevel          : 4;
        U32 cmdlinesiglevel             : 1;
        U32 data47linesiglevel          : 4;
        U32                             : 3;
    } bitc;
} GH_SDIO_PRESENTSTATEREG_S;

typedef union { /* SDIO_CapReg */
    U32 all;
    struct {
        U32 timeoutclkfre               : 6;
        U32                             : 1;
        U32 timeoutclkunit              : 1;
        U32 baseclkfreforsdclk          : 6;
        U32                             : 2;
        U32 maxblklen                   : 2;
        U32 extendedmediabussup         : 1;
        U32                             : 2;
        U32 highspeedsup                : 1;
        U32 susressup                   : 1;
        U32 sdmasup                     : 1;
        U32 voltagesup33v               : 1;
        U32 voltagesup30v               : 1;
        U32 voltagesup18v               : 1;
        U32 intmode                     : 1;
        U32                             : 4;
    } bitc;
} GH_SDIO_CAPREG_S;

typedef union { /* SDIO_AutoCmd12ErrStatusReg */
    U32 all;
    struct {
        U32 autocmd12timeouterr         : 1;
        U32 autocmd12crcerr             : 1;
        U32 autocmd12endbiterr          : 1;
        U32 autocmd12notexe             : 1;
        U32 autocmd12indexerr           : 1;
        U32                             : 2;
        U32 cmdnotissuedbyautocmd12err  : 1;
        U32                             : 24;
    } bitc;
} GH_SDIO_AUTOCMD12ERRSTATUSREG_S;

typedef union { /* SDIO_MaxCurCapReg */
    U32 all;
    struct {
        U32 maxcurfor33v                : 8;
        U32 maxcurfor30v                : 8;
        U32 maxcurfor18v                : 8;
        U32                             : 8;
    } bitc;
} GH_SDIO_MAXCURCAPREG_S;

typedef union { /* SDIO_SlotIntStatusReg */
    U32 all;
    struct {
        U32 intsigforeachslot           : 8;
        U32                             : 8;
        U32 specifivernum               : 8;
        U32 vendorvernum                : 8;
    } bitc;
} GH_SDIO_SLOTINTSTATUSREG_S;

/*---------------------------------------------------------------------------*/
/* function prototypes                                                       */
/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
void GH_SDIO_set_SysAddrReg(U32 sdio, U32 data);
U32  GH_SDIO_get_SysAddrReg(U32 sdio);

void GH_SDIO_set_TranModeReg(U32 sdio, U16 data);
U16  GH_SDIO_get_TranModeReg(U32 sdio);
void GH_SDIO_set_TranModeReg_BlkCountEn(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeReg_BlkCountEn(U32 sdio);
void GH_SDIO_set_TranModeReg_AutoCmd12En(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeReg_AutoCmd12En(U32 sdio);
void GH_SDIO_set_TranModeReg_DmaEn(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeReg_DmaEn(U32 sdio);
void GH_SDIO_set_TranModeReg_MSBlkSelect(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeReg_MSBlkSelect(U32 sdio);
void GH_SDIO_set_TranModeReg_DataTraDirSelect(U32 sdio, U8 data);
U8   GH_SDIO_get_TranModeReg_DataTraDirSelect(U32 sdio);

void GH_SDIO_set_NorIntSigEnReg(U32 sdio, U16 data);
U16  GH_SDIO_get_NorIntSigEnReg(U32 sdio);
void GH_SDIO_set_NorIntSigEnReg_CmdCompleteSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntSigEnReg_CmdCompleteSigEn(U32 sdio);
void GH_SDIO_set_NorIntSigEnReg_TraCompleteSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntSigEnReg_TraCompleteSigEn(U32 sdio);
void GH_SDIO_set_NorIntSigEnReg_BlkGapEveSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntSigEnReg_BlkGapEveSigEn(U32 sdio);
void GH_SDIO_set_NorIntSigEnReg_DmaIntSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntSigEnReg_DmaIntSigEn(U32 sdio);
void GH_SDIO_set_NorIntSigEnReg_BufWReadySigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntSigEnReg_BufWReadySigEn(U32 sdio);
void GH_SDIO_set_NorIntSigEnReg_BufRReadySigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntSigEnReg_BufRReadySigEn(U32 sdio);
void GH_SDIO_set_NorIntSigEnReg_CardInsertionSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntSigEnReg_CardInsertionSigEn(U32 sdio);
void GH_SDIO_set_NorIntSigEnReg_CardRemSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntSigEnReg_CardRemSigEn(U32 sdio);
void GH_SDIO_set_NorIntSigEnReg_CardIntSigEN(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntSigEnReg_CardIntSigEN(U32 sdio);
void GH_SDIO_set_NorIntSigEnReg_FixedTo0(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntSigEnReg_FixedTo0(U32 sdio);

void GH_SDIO_set_ErrIntSigEnReg(U32 sdio, U16 data);
U16  GH_SDIO_get_ErrIntSigEnReg(U32 sdio);
void GH_SDIO_set_ErrIntSigEnReg_CmdTimeoutErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnReg_CmdTimeoutErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnReg_CmdEndBitErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnReg_CmdEndBitErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnReg_CmdIndexErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnReg_CmdIndexErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnReg_DataTimeoutErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnReg_DataTimeoutErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnReg_CmdCrcErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnReg_CmdCrcErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnReg_DataCrcErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnReg_DataCrcErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnReg_DataEndBitErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnReg_DataEndBitErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnReg_CurLimitErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnReg_CurLimitErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnReg_AutoCmd12ErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnReg_AutoCmd12ErrSigEn(U32 sdio);
void GH_SDIO_set_ErrIntSigEnReg_VendorSpecificErrSigEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntSigEnReg_VendorSpecificErrSigEn(U32 sdio);

void GH_SDIO_set_BlkCouReg(U32 sdio, U16 data);
U16  GH_SDIO_get_BlkCouReg(U32 sdio);
void GH_SDIO_set_BlkCouReg_BlkCountForCurTra(U32 sdio, U16 data);
U16  GH_SDIO_get_BlkCouReg_BlkCountForCurTra(U32 sdio);

void GH_SDIO_set_BlkSizeReg(U32 sdio, U16 data);
U16  GH_SDIO_get_BlkSizeReg(U32 sdio);
void GH_SDIO_set_BlkSizeReg_TraBlkSize(U32 sdio, U16 data);
U16  GH_SDIO_get_BlkSizeReg_TraBlkSize(U32 sdio);
void GH_SDIO_set_BlkSizeReg_HostSdmaBufSize(U32 sdio, U8 data);
U8   GH_SDIO_get_BlkSizeReg_HostSdmaBufSize(U32 sdio);

void GH_SDIO_set_NorIntStaEnReg(U32 sdio, U16 data);
U16  GH_SDIO_get_NorIntStaEnReg(U32 sdio);
void GH_SDIO_set_NorIntStaEnReg_CmdCompleteStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaEnReg_CmdCompleteStatusEn(U32 sdio);
void GH_SDIO_set_NorIntStaEnReg_TraCompleteStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaEnReg_TraCompleteStatusEn(U32 sdio);
void GH_SDIO_set_NorIntStaEnReg_BlkGapEveStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaEnReg_BlkGapEveStatusEn(U32 sdio);
void GH_SDIO_set_NorIntStaEnReg_DmaIntStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaEnReg_DmaIntStatusEn(U32 sdio);
void GH_SDIO_set_NorIntStaEnReg_BufWReadyStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaEnReg_BufWReadyStatusEn(U32 sdio);
void GH_SDIO_set_NorIntStaEnReg_BufRReadyStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaEnReg_BufRReadyStatusEn(U32 sdio);
void GH_SDIO_set_NorIntStaEnReg_CardInsertionStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaEnReg_CardInsertionStatusEn(U32 sdio);
void GH_SDIO_set_NorIntStaEnReg_CardRemStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaEnReg_CardRemStatusEn(U32 sdio);
void GH_SDIO_set_NorIntStaEnReg_CardIntStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaEnReg_CardIntStatusEn(U32 sdio);
void GH_SDIO_set_NorIntStaEnReg_FixedTo0(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaEnReg_FixedTo0(U32 sdio);

void GH_SDIO_set_ErrIntStaEnReg(U32 sdio, U16 data);
U16  GH_SDIO_get_ErrIntStaEnReg(U32 sdio);
void GH_SDIO_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnReg_CmdEndBitErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnReg_CmdEndBitErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnReg_CmdCrcErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnReg_CmdCrcErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnReg_CmdIndexErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnReg_CmdIndexErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnReg_DataCrcErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnReg_DataCrcErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnReg_DataTimeoutErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnReg_DataTimeoutErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnReg_DataEndBitErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnReg_DataEndBitErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnReg_CurLimitErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnReg_CurLimitErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn(U32 sdio);
void GH_SDIO_set_ErrIntStaEnReg_VendorSpecificErrStatusEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStaEnReg_VendorSpecificErrStatusEn(U32 sdio);

void GH_SDIO_set_NorIntStaReg(U32 sdio, U16 data);
U16  GH_SDIO_get_NorIntStaReg(U32 sdio);
void GH_SDIO_set_NorIntStaReg_CmdComplete(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaReg_CmdComplete(U32 sdio);
void GH_SDIO_set_NorIntStaReg_BlkGapEvent(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaReg_BlkGapEvent(U32 sdio);
void GH_SDIO_set_NorIntStaReg_DmaInt(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaReg_DmaInt(U32 sdio);
void GH_SDIO_set_NorIntStaReg_TraComplete(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaReg_TraComplete(U32 sdio);
void GH_SDIO_set_NorIntStaReg_BufWReady(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaReg_BufWReady(U32 sdio);
void GH_SDIO_set_NorIntStaReg_CardInsertion(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaReg_CardInsertion(U32 sdio);
void GH_SDIO_set_NorIntStaReg_BufRReady(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaReg_BufRReady(U32 sdio);
void GH_SDIO_set_NorIntStaReg_CardRemoval(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaReg_CardRemoval(U32 sdio);
void GH_SDIO_set_NorIntStaReg_CardInt(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaReg_CardInt(U32 sdio);
void GH_SDIO_set_NorIntStaReg_BootAckRcv(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaReg_BootAckRcv(U32 sdio);
void GH_SDIO_set_NorIntStaReg_ErrInt(U32 sdio, U8 data);
U8   GH_SDIO_get_NorIntStaReg_ErrInt(U32 sdio);

void GH_SDIO_set_ErrIntStatusReg(U32 sdio, U16 data);
U16  GH_SDIO_get_ErrIntStatusReg(U32 sdio);
void GH_SDIO_set_ErrIntStatusReg_CmdTimeoutErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusReg_CmdTimeoutErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusReg_CmdCrcErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusReg_CmdCrcErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusReg_CmdEndBitErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusReg_CmdEndBitErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusReg_CmdIndexErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusReg_CmdIndexErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusReg_DataTimeoutErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusReg_DataTimeoutErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusReg_DataCrcErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusReg_DataCrcErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusReg_DataEndBitErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusReg_DataEndBitErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusReg_CurLimitErr(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusReg_CurLimitErr(U32 sdio);
void GH_SDIO_set_ErrIntStatusReg_AutoCmd12Err(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusReg_AutoCmd12Err(U32 sdio);
void GH_SDIO_set_ErrIntStatusReg_VendorSpecificErrStatus(U32 sdio, U8 data);
U8   GH_SDIO_get_ErrIntStatusReg_VendorSpecificErrStatus(U32 sdio);

void GH_SDIO_set_CommondReg(U32 sdio, U16 data);
U16  GH_SDIO_get_CommondReg(U32 sdio);
void GH_SDIO_set_CommondReg_RepTypeSelect(U32 sdio, U8 data);
U8   GH_SDIO_get_CommondReg_RepTypeSelect(U32 sdio);
void GH_SDIO_set_CommondReg_CmdCrcCheckEn(U32 sdio, U8 data);
U8   GH_SDIO_get_CommondReg_CmdCrcCheckEn(U32 sdio);
void GH_SDIO_set_CommondReg_DataPreSelect(U32 sdio, U8 data);
U8   GH_SDIO_get_CommondReg_DataPreSelect(U32 sdio);
void GH_SDIO_set_CommondReg_CmdIndexCheckEn(U32 sdio, U8 data);
U8   GH_SDIO_get_CommondReg_CmdIndexCheckEn(U32 sdio);
void GH_SDIO_set_CommondReg_CmdType(U32 sdio, U8 data);
U8   GH_SDIO_get_CommondReg_CmdType(U32 sdio);
void GH_SDIO_set_CommondReg_CmdIndex(U32 sdio, U8 data);
U8   GH_SDIO_get_CommondReg_CmdIndex(U32 sdio);

void GH_SDIO_set_SoftResetReg(U32 sdio, U16 data);
U16  GH_SDIO_get_SoftResetReg(U32 sdio);
void GH_SDIO_set_SoftResetReg_DataTimeoutCounterValue(U32 sdio, U8 data);
U8   GH_SDIO_get_SoftResetReg_DataTimeoutCounterValue(U32 sdio);
void GH_SDIO_set_SoftResetReg_SoftwareResetCmdLine(U32 sdio, U8 data);
U8   GH_SDIO_get_SoftResetReg_SoftwareResetCmdLine(U32 sdio);
void GH_SDIO_set_SoftResetReg_SoftwareResetAll(U32 sdio, U8 data);
U8   GH_SDIO_get_SoftResetReg_SoftwareResetAll(U32 sdio);
void GH_SDIO_set_SoftResetReg_SoftwareResetDatLine(U32 sdio, U8 data);
U8   GH_SDIO_get_SoftResetReg_SoftwareResetDatLine(U32 sdio);

void GH_SDIO_set_ClkControlReg(U32 sdio, U16 data);
U16  GH_SDIO_get_ClkControlReg(U32 sdio);
void GH_SDIO_set_ClkControlReg_InternalClkEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ClkControlReg_InternalClkEn(U32 sdio);
void GH_SDIO_set_ClkControlReg_InternalClkStable(U32 sdio, U8 data);
U8   GH_SDIO_get_ClkControlReg_InternalClkStable(U32 sdio);
void GH_SDIO_set_ClkControlReg_SdClkEn(U32 sdio, U8 data);
U8   GH_SDIO_get_ClkControlReg_SdClkEn(U32 sdio);
void GH_SDIO_set_ClkControlReg_SdclkFreSelect(U32 sdio, U8 data);
U8   GH_SDIO_get_ClkControlReg_SdclkFreSelect(U32 sdio);

U32  GH_SDIO_get_Resp0Reg(U32 sdio);

U32  GH_SDIO_get_Resp1Reg(U32 sdio);

U32  GH_SDIO_get_Resp2Reg(U32 sdio);

U32  GH_SDIO_get_Resp3Reg(U32 sdio);

void GH_SDIO_set_Control00Reg(U32 sdio, U32 data);
U32  GH_SDIO_get_Control00Reg(U32 sdio);
void GH_SDIO_set_Control00Reg_LedControl(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_LedControl(U32 sdio);
void GH_SDIO_set_Control00Reg_DataTraWidth(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_DataTraWidth(U32 sdio);
void GH_SDIO_set_Control00Reg_HostSpeedEn(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_HostSpeedEn(U32 sdio);
void GH_SDIO_set_Control00Reg_Sd8BitMode(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_Sd8BitMode(U32 sdio);
void GH_SDIO_set_Control00Reg_CardDetectTestLevel(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_CardDetectTestLevel(U32 sdio);
void GH_SDIO_set_Control00Reg_CardDetectSigDet(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_CardDetectSigDet(U32 sdio);
void GH_SDIO_set_Control00Reg_SdBusPower(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_SdBusPower(U32 sdio);
void GH_SDIO_set_Control00Reg_SdBusVoltageSelect(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_SdBusVoltageSelect(U32 sdio);
void GH_SDIO_set_Control00Reg_StopAtBlkGapReq(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_StopAtBlkGapReq(U32 sdio);
void GH_SDIO_set_Control00Reg_ContinueReq(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_ContinueReq(U32 sdio);
void GH_SDIO_set_Control00Reg_RWaitControl(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_RWaitControl(U32 sdio);
void GH_SDIO_set_Control00Reg_IntAtBlkGap(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_IntAtBlkGap(U32 sdio);
void GH_SDIO_set_Control00Reg_DriveCcsd(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_DriveCcsd(U32 sdio);
void GH_SDIO_set_Control00Reg_SpiMode(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_SpiMode(U32 sdio);
void GH_SDIO_set_Control00Reg_BootEn(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_BootEn(U32 sdio);
void GH_SDIO_set_Control00Reg_AltBootEn(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_AltBootEn(U32 sdio);
void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardInt(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardInt(U32 sdio);
void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardIns(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardIns(U32 sdio);
void GH_SDIO_set_Control00Reg_WakeupEvetEnOnCardRem(U32 sdio, U8 data);
U8   GH_SDIO_get_Control00Reg_WakeupEvetEnOnCardRem(U32 sdio);

U32  GH_SDIO_get_PresentStateReg(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_CmdInhibitCmd(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_CmdInhibitData(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_DataLineActive(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_WTraActive(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_RTraActive(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_BufWEn(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_BufREn(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_CardInserted(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_CardStateStable(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_CardDetectPinLevel(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_WProSwiPinLevel(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_Data03LineSigLevel(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_CmdLineSigLevel(U32 sdio);
U8   GH_SDIO_get_PresentStateReg_Data47LineSigLevel(U32 sdio);

void GH_SDIO_set_ArgReg(U32 sdio, U32 data);
U32  GH_SDIO_get_ArgReg(U32 sdio);

U32  GH_SDIO_get_CapReg(U32 sdio);
U8   GH_SDIO_get_CapReg_TimeoutClkFre(U32 sdio);
U8   GH_SDIO_get_CapReg_TimeoutClkUnit(U32 sdio);
U8   GH_SDIO_get_CapReg_BaseClkFreForSdClk(U32 sdio);
U8   GH_SDIO_get_CapReg_MaxBlkLen(U32 sdio);
U8   GH_SDIO_get_CapReg_ExtendedMediaBusSup(U32 sdio);
U8   GH_SDIO_get_CapReg_HighSpeedSup(U32 sdio);
U8   GH_SDIO_get_CapReg_SdmaSup(U32 sdio);
U8   GH_SDIO_get_CapReg_SusResSup(U32 sdio);
U8   GH_SDIO_get_CapReg_VoltageSup33v(U32 sdio);
U8   GH_SDIO_get_CapReg_VoltageSup30v(U32 sdio);
U8   GH_SDIO_get_CapReg_VoltageSup18v(U32 sdio);
U8   GH_SDIO_get_CapReg_IntMode(U32 sdio);

U32  GH_SDIO_get_AutoCmd12ErrStatusReg(U32 sdio);
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe(U32 sdio);
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr(U32 sdio);
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr(U32 sdio);
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr(U32 sdio);
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr(U32 sdio);
U8   GH_SDIO_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err(U32 sdio);

void GH_SDIO_set_BufferDataPortReg(U32 sdio, U32 data);
U32  GH_SDIO_get_BufferDataPortReg(U32 sdio);

void GH_SDIO_set_MaxCurCapReg(U32 sdio, U32 data);
U32  GH_SDIO_get_MaxCurCapReg(U32 sdio);
void GH_SDIO_set_MaxCurCapReg_MaxCurFor33v(U32 sdio, U8 data);
U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor33v(U32 sdio);
void GH_SDIO_set_MaxCurCapReg_MaxCurFor30v(U32 sdio, U8 data);
U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor30v(U32 sdio);
void GH_SDIO_set_MaxCurCapReg_MaxCurFor18v(U32 sdio, U8 data);
U8   GH_SDIO_get_MaxCurCapReg_MaxCurFor18v(U32 sdio);

U32  GH_SDIO_get_SlotIntStatusReg(U32 sdio);
U8   GH_SDIO_get_SlotIntStatusReg_IntSigForEachSlot(U32 sdio);
U8   GH_SDIO_get_SlotIntStatusReg_SpecifiVerNum(U32 sdio);
U8   GH_SDIO_get_SlotIntStatusReg_VendorVerNum(U32 sdio);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_SDIO_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_SDIO_ALL_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

