/*!
*******************************************************************************
**
** \file      gh_sdio0.h
**
** \brief     SDIO0 Host Controller.
**
**            Copyright:   2012 - 2016 (C) GoKe Microelectronics
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef _GH_SDIO0_H
#define _GH_SDIO0_H

#ifdef __LINUX__
#include "reg4linux.h"
#else
#define FIO_ADDRESS(block,address) (address)
#define FIO_MOFFSET(block,moffset) (moffset)
#endif

#ifndef __LINUX__
#include "gtypes.h" /* global type definitions */
#include "gh_lib_cfg.h" /* configuration */
#endif

#define GH_SDIO0_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_SDIO0_DEBUG_PRINT_FUNCTION printk
#else
#define GH_SDIO0_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_SDIO0_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_SDIO0_SYSADDRREG                                FIO_ADDRESS(SDIO0,0x90000000) /* read/write */
#define REG_SDIO0_TRANMODEREG                               FIO_ADDRESS(SDIO0,0x90000004) /* read/write */
#define REG_SDIO0_NORINTSIGENREG                            FIO_ADDRESS(SDIO0,0x90000006) /* read/write */
#define REG_SDIO0_ERRINTSIGEN                               FIO_ADDRESS(SDIO0,0x90000008) /* read/write */
#define REG_SDIO0_BLKCOUREG                                 FIO_ADDRESS(SDIO0,0x9000000A) /* read/write */
#define REG_SDIO0_BLKSIZEREG                                FIO_ADDRESS(SDIO0,0x9000000C) /* read/write */
#define REG_SDIO0_NORINTSTAENREG                            FIO_ADDRESS(SDIO0,0x9000000E) /* read/write */
#define REG_SDIO0_ERRINTSTAENREG                            FIO_ADDRESS(SDIO0,0x90000010) /* read/write */
#define REG_SDIO0_NORINTSTAREG                              FIO_ADDRESS(SDIO0,0x90000012) /* read/write */
#define REG_SDIO0_ERRINTSTAREG                              FIO_ADDRESS(SDIO0,0x90000014) /* read/write */
#define REG_SDIO0_CMDREG                                    FIO_ADDRESS(SDIO0,0x90000016) /* read/write */
#define REG_SDIO0_CONTROL01REG                              FIO_ADDRESS(SDIO0,0x90000018) /* read/write */
#define REG_SDIO0_RESP0REG                                  FIO_ADDRESS(SDIO0,0x9000001C) /* read */
#define REG_SDIO0_RESP1REG                                  FIO_ADDRESS(SDIO0,0x90000020) /* read */
#define REG_SDIO0_RESP2REG                                  FIO_ADDRESS(SDIO0,0x90000024) /* read */
#define REG_SDIO0_RESP3REG                                  FIO_ADDRESS(SDIO0,0x90000028) /* read */
#define REG_SDIO0_CONTROL00REG                              FIO_ADDRESS(SDIO0,0x9000002C) /* read/write */
#define REG_SDIO0_PRESENTSTATEREG                           FIO_ADDRESS(SDIO0,0x90000030) /* read */
#define REG_SDIO0_ARGREG                                    FIO_ADDRESS(SDIO0,0x90000034) /* read/write */
#define REG_SDIO0_CAPREG                                    FIO_ADDRESS(SDIO0,0x90000038) /* read */
#define REG_SDIO0_AUTOCMD12ERRSTATUSREG                     FIO_ADDRESS(SDIO0,0x9000003C) /* read */
#define REG_SDIO0_BUFFERDATAPORTREG                         FIO_ADDRESS(SDIO0,0x90000040) /* read/write */
#define REG_SDIO0_MAXCURCAPREG                              FIO_ADDRESS(SDIO0,0x90000048) /* read/write */
#define REG_SDIO0_SLOTINTSTATUSREG                          FIO_ADDRESS(SDIO0,0x900000FC) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* SDIO0_TranModeReg */
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
} GH_SDIO0_TRANMODEREG_S;

typedef union { /* SDIO0_NorIntSigEnReg */
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
        U16                             : 5;
        U16 fixedto0                    : 2;
    } bitc;
} GH_SDIO0_NORINTSIGENREG_S;

typedef union { /* SDIO0_ErrIntSigEn */
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
} GH_SDIO0_ERRINTSIGEN_S;

typedef union { /* SDIO0_BlkCouReg */
    U16 all;
    struct {
        U16 blkcountforcurtra           : 16;
    } bitc;
} GH_SDIO0_BLKCOUREG_S;

typedef union { /* SDIO0_BlkSizeReg */
    U16 all;
    struct {
        U16 trablksize                  : 12;
        U16 hostsdmabufsize             : 3;
        U32                             : 1;
    } bitc;
} GH_SDIO0_BLKSIZEREG_S;

typedef union { /* SDIO0_NorIntStaEnReg */
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
} GH_SDIO0_NORINTSTAENREG_S;

typedef union { /* SDIO0_ErrIntStaEnReg */
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
} GH_SDIO0_ERRINTSTAENREG_S;

typedef union { /* SDIO0_NorIntStaReg */
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
} GH_SDIO0_NORINTSTAREG_S;

typedef union { /* SDIO0_ErrIntStaReg */
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
} GH_SDIO0_ERRINTSTAREG_S;

typedef union { /* SDIO0_CmdReg */
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
} GH_SDIO0_CMDREG_S;

typedef union { /* SDIO0_Control01Reg */
    U32 all;
    struct {
        U32 datatimeoutcountervalue     : 4;
        U32                             : 4;
        U32 softwareresetcmdline        : 1;
        U32 softwareresetall            : 1;
        U32 softwareresetdatline        : 1;
        U32                             : 5;
        U32 internalclken               : 1;
        U32 internalclkstable           : 1;
        U32 sdclken                     : 1;
        U32                             : 5;
        U32 sdclkfreselect              : 8;
    } bitc;
} GH_SDIO0_CONTROL01REG_S;

typedef union { /* SDIO0_Control00Reg */
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
} GH_SDIO0_CONTROL00REG_S;

typedef union { /* SDIO0_PresentStateReg */
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
} GH_SDIO0_PRESENTSTATEREG_S;

typedef union { /* SDIO0_CapReg */
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
} GH_SDIO0_CAPREG_S;

typedef union { /* SDIO0_AutoCmd12ErrStatusReg */
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
} GH_SDIO0_AUTOCMD12ERRSTATUSREG_S;

typedef union { /* SDIO0_MaxCurCapReg */
    U32 all;
    struct {
        U32 maxcurfor33v                : 8;
        U32 maxcurfor30v                : 8;
        U32 maxcurfor18v                : 8;
        U32                             : 8;
    } bitc;
} GH_SDIO0_MAXCURCAPREG_S;

typedef union { /* SDIO0_SlotIntStatusReg */
    U32 all;
    struct {
        U32 intsigforeachslot           : 8;
        U32                             : 8;
        U32 specifivernum               : 8;
        U32 vendorvernum                : 8;
    } bitc;
} GH_SDIO0_SLOTINTSTATUSREG_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register SDIO0_SysAddrReg (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_SysAddrReg'. */
void GH_SDIO0_set_SysAddrReg(U32 data);
/*! \brief Reads the register 'SDIO0_SysAddrReg'. */
U32  GH_SDIO0_get_SysAddrReg(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_TranModeReg (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_TranModeReg'. */
void GH_SDIO0_set_TranModeReg(U16 data);
/*! \brief Reads the register 'SDIO0_TranModeReg'. */
U16  GH_SDIO0_get_TranModeReg(void);
/*! \brief Writes the bit group 'BlkCountEn' of register 'SDIO0_TranModeReg'. */
void GH_SDIO0_set_TranModeReg_BlkCountEn(U8 data);
/*! \brief Reads the bit group 'BlkCountEn' of register 'SDIO0_TranModeReg'. */
U8   GH_SDIO0_get_TranModeReg_BlkCountEn(void);
/*! \brief Writes the bit group 'AutoCmd12En' of register 'SDIO0_TranModeReg'. */
void GH_SDIO0_set_TranModeReg_AutoCmd12En(U8 data);
/*! \brief Reads the bit group 'AutoCmd12En' of register 'SDIO0_TranModeReg'. */
U8   GH_SDIO0_get_TranModeReg_AutoCmd12En(void);
/*! \brief Writes the bit group 'DmaEn' of register 'SDIO0_TranModeReg'. */
void GH_SDIO0_set_TranModeReg_DmaEn(U8 data);
/*! \brief Reads the bit group 'DmaEn' of register 'SDIO0_TranModeReg'. */
U8   GH_SDIO0_get_TranModeReg_DmaEn(void);
/*! \brief Writes the bit group 'MSBlkSelect' of register 'SDIO0_TranModeReg'. */
void GH_SDIO0_set_TranModeReg_MSBlkSelect(U8 data);
/*! \brief Reads the bit group 'MSBlkSelect' of register 'SDIO0_TranModeReg'. */
U8   GH_SDIO0_get_TranModeReg_MSBlkSelect(void);
/*! \brief Writes the bit group 'DataTraDirSelect' of register 'SDIO0_TranModeReg'. */
void GH_SDIO0_set_TranModeReg_DataTraDirSelect(U8 data);
/*! \brief Reads the bit group 'DataTraDirSelect' of register 'SDIO0_TranModeReg'. */
U8   GH_SDIO0_get_TranModeReg_DataTraDirSelect(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_NorIntSigEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_NorIntSigEnReg'. */
void GH_SDIO0_set_NorIntSigEnReg(U16 data);
/*! \brief Reads the register 'SDIO0_NorIntSigEnReg'. */
U16  GH_SDIO0_get_NorIntSigEnReg(void);
/*! \brief Writes the bit group 'CmdCompleteSigEn' of register 'SDIO0_NorIntSigEnReg'. */
void GH_SDIO0_set_NorIntSigEnReg_CmdCompleteSigEn(U8 data);
/*! \brief Reads the bit group 'CmdCompleteSigEn' of register 'SDIO0_NorIntSigEnReg'. */
U8   GH_SDIO0_get_NorIntSigEnReg_CmdCompleteSigEn(void);
/*! \brief Writes the bit group 'TraCompleteSigEn' of register 'SDIO0_NorIntSigEnReg'. */
void GH_SDIO0_set_NorIntSigEnReg_TraCompleteSigEn(U8 data);
/*! \brief Reads the bit group 'TraCompleteSigEn' of register 'SDIO0_NorIntSigEnReg'. */
U8   GH_SDIO0_get_NorIntSigEnReg_TraCompleteSigEn(void);
/*! \brief Writes the bit group 'BlkGapEveSigEn' of register 'SDIO0_NorIntSigEnReg'. */
void GH_SDIO0_set_NorIntSigEnReg_BlkGapEveSigEn(U8 data);
/*! \brief Reads the bit group 'BlkGapEveSigEn' of register 'SDIO0_NorIntSigEnReg'. */
U8   GH_SDIO0_get_NorIntSigEnReg_BlkGapEveSigEn(void);
/*! \brief Writes the bit group 'DmaIntSigEn' of register 'SDIO0_NorIntSigEnReg'. */
void GH_SDIO0_set_NorIntSigEnReg_DmaIntSigEn(U8 data);
/*! \brief Reads the bit group 'DmaIntSigEn' of register 'SDIO0_NorIntSigEnReg'. */
U8   GH_SDIO0_get_NorIntSigEnReg_DmaIntSigEn(void);
/*! \brief Writes the bit group 'BufWReadySigEn' of register 'SDIO0_NorIntSigEnReg'. */
void GH_SDIO0_set_NorIntSigEnReg_BufWReadySigEn(U8 data);
/*! \brief Reads the bit group 'BufWReadySigEn' of register 'SDIO0_NorIntSigEnReg'. */
U8   GH_SDIO0_get_NorIntSigEnReg_BufWReadySigEn(void);
/*! \brief Writes the bit group 'BufRReadySigEn' of register 'SDIO0_NorIntSigEnReg'. */
void GH_SDIO0_set_NorIntSigEnReg_BufRReadySigEn(U8 data);
/*! \brief Reads the bit group 'BufRReadySigEn' of register 'SDIO0_NorIntSigEnReg'. */
U8   GH_SDIO0_get_NorIntSigEnReg_BufRReadySigEn(void);
/*! \brief Writes the bit group 'CardInsertionSigEn' of register 'SDIO0_NorIntSigEnReg'. */
void GH_SDIO0_set_NorIntSigEnReg_CardInsertionSigEn(U8 data);
/*! \brief Reads the bit group 'CardInsertionSigEn' of register 'SDIO0_NorIntSigEnReg'. */
U8   GH_SDIO0_get_NorIntSigEnReg_CardInsertionSigEn(void);
/*! \brief Writes the bit group 'CardRemSigEn' of register 'SDIO0_NorIntSigEnReg'. */
void GH_SDIO0_set_NorIntSigEnReg_CardRemSigEn(U8 data);
/*! \brief Reads the bit group 'CardRemSigEn' of register 'SDIO0_NorIntSigEnReg'. */
U8   GH_SDIO0_get_NorIntSigEnReg_CardRemSigEn(void);
/*! \brief Writes the bit group 'CardIntSigEN' of register 'SDIO0_NorIntSigEnReg'. */
void GH_SDIO0_set_NorIntSigEnReg_CardIntSigEN(U8 data);
/*! \brief Reads the bit group 'CardIntSigEN' of register 'SDIO0_NorIntSigEnReg'. */
U8   GH_SDIO0_get_NorIntSigEnReg_CardIntSigEN(void);
/*! \brief Writes the bit group 'FixedTo0' of register 'SDIO0_NorIntSigEnReg'. */
void GH_SDIO0_set_NorIntSigEnReg_FixedTo0(U8 data);
/*! \brief Reads the bit group 'FixedTo0' of register 'SDIO0_NorIntSigEnReg'. */
U8   GH_SDIO0_get_NorIntSigEnReg_FixedTo0(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntSigEn (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_ErrIntSigEn'. */
void GH_SDIO0_set_ErrIntSigEn(U16 data);
/*! \brief Reads the register 'SDIO0_ErrIntSigEn'. */
U16  GH_SDIO0_get_ErrIntSigEn(void);
/*! \brief Writes the bit group 'CmdTimeoutErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
void GH_SDIO0_set_ErrIntSigEn_CmdTimeoutErrSigEn(U8 data);
/*! \brief Reads the bit group 'CmdTimeoutErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
U8   GH_SDIO0_get_ErrIntSigEn_CmdTimeoutErrSigEn(void);
/*! \brief Writes the bit group 'CmdEndBitErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
void GH_SDIO0_set_ErrIntSigEn_CmdEndBitErrSigEn(U8 data);
/*! \brief Reads the bit group 'CmdEndBitErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
U8   GH_SDIO0_get_ErrIntSigEn_CmdEndBitErrSigEn(void);
/*! \brief Writes the bit group 'CmdIndexErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
void GH_SDIO0_set_ErrIntSigEn_CmdIndexErrSigEn(U8 data);
/*! \brief Reads the bit group 'CmdIndexErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
U8   GH_SDIO0_get_ErrIntSigEn_CmdIndexErrSigEn(void);
/*! \brief Writes the bit group 'DataTimeoutErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
void GH_SDIO0_set_ErrIntSigEn_DataTimeoutErrSigEn(U8 data);
/*! \brief Reads the bit group 'DataTimeoutErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
U8   GH_SDIO0_get_ErrIntSigEn_DataTimeoutErrSigEn(void);
/*! \brief Writes the bit group 'CmdCrcErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
void GH_SDIO0_set_ErrIntSigEn_CmdCrcErrSigEn(U8 data);
/*! \brief Reads the bit group 'CmdCrcErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
U8   GH_SDIO0_get_ErrIntSigEn_CmdCrcErrSigEn(void);
/*! \brief Writes the bit group 'DataCrcErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
void GH_SDIO0_set_ErrIntSigEn_DataCrcErrSigEn(U8 data);
/*! \brief Reads the bit group 'DataCrcErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
U8   GH_SDIO0_get_ErrIntSigEn_DataCrcErrSigEn(void);
/*! \brief Writes the bit group 'DataEndBitErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
void GH_SDIO0_set_ErrIntSigEn_DataEndBitErrSigEn(U8 data);
/*! \brief Reads the bit group 'DataEndBitErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
U8   GH_SDIO0_get_ErrIntSigEn_DataEndBitErrSigEn(void);
/*! \brief Writes the bit group 'CurLimitErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
void GH_SDIO0_set_ErrIntSigEn_CurLimitErrSigEn(U8 data);
/*! \brief Reads the bit group 'CurLimitErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
U8   GH_SDIO0_get_ErrIntSigEn_CurLimitErrSigEn(void);
/*! \brief Writes the bit group 'AutoCmd12ErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
void GH_SDIO0_set_ErrIntSigEn_AutoCmd12ErrSigEn(U8 data);
/*! \brief Reads the bit group 'AutoCmd12ErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
U8   GH_SDIO0_get_ErrIntSigEn_AutoCmd12ErrSigEn(void);
/*! \brief Writes the bit group 'VendorSpecificErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
void GH_SDIO0_set_ErrIntSigEn_VendorSpecificErrSigEn(U8 data);
/*! \brief Reads the bit group 'VendorSpecificErrSigEn' of register 'SDIO0_ErrIntSigEn'. */
U8   GH_SDIO0_get_ErrIntSigEn_VendorSpecificErrSigEn(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_BlkCouReg (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_BlkCouReg'. */
void GH_SDIO0_set_BlkCouReg(U16 data);
/*! \brief Reads the register 'SDIO0_BlkCouReg'. */
U16  GH_SDIO0_get_BlkCouReg(void);
/*! \brief Writes the bit group 'BlkCountForCurTra' of register 'SDIO0_BlkCouReg'. */
void GH_SDIO0_set_BlkCouReg_BlkCountForCurTra(U16 data);
/*! \brief Reads the bit group 'BlkCountForCurTra' of register 'SDIO0_BlkCouReg'. */
U16  GH_SDIO0_get_BlkCouReg_BlkCountForCurTra(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_BlkSizeReg (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_BlkSizeReg'. */
void GH_SDIO0_set_BlkSizeReg(U16 data);
/*! \brief Reads the register 'SDIO0_BlkSizeReg'. */
U16  GH_SDIO0_get_BlkSizeReg(void);
/*! \brief Writes the bit group 'TraBlkSize' of register 'SDIO0_BlkSizeReg'. */
void GH_SDIO0_set_BlkSizeReg_TraBlkSize(U16 data);
/*! \brief Reads the bit group 'TraBlkSize' of register 'SDIO0_BlkSizeReg'. */
U16  GH_SDIO0_get_BlkSizeReg_TraBlkSize(void);
/*! \brief Writes the bit group 'HostSdmaBufSize' of register 'SDIO0_BlkSizeReg'. */
void GH_SDIO0_set_BlkSizeReg_HostSdmaBufSize(U8 data);
/*! \brief Reads the bit group 'HostSdmaBufSize' of register 'SDIO0_BlkSizeReg'. */
U8   GH_SDIO0_get_BlkSizeReg_HostSdmaBufSize(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_NorIntStaEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_NorIntStaEnReg'. */
void GH_SDIO0_set_NorIntStaEnReg(U16 data);
/*! \brief Reads the register 'SDIO0_NorIntStaEnReg'. */
U16  GH_SDIO0_get_NorIntStaEnReg(void);
/*! \brief Writes the bit group 'CmdCompleteStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
void GH_SDIO0_set_NorIntStaEnReg_CmdCompleteStatusEn(U8 data);
/*! \brief Reads the bit group 'CmdCompleteStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
U8   GH_SDIO0_get_NorIntStaEnReg_CmdCompleteStatusEn(void);
/*! \brief Writes the bit group 'TraCompleteStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
void GH_SDIO0_set_NorIntStaEnReg_TraCompleteStatusEn(U8 data);
/*! \brief Reads the bit group 'TraCompleteStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
U8   GH_SDIO0_get_NorIntStaEnReg_TraCompleteStatusEn(void);
/*! \brief Writes the bit group 'BlkGapEveStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
void GH_SDIO0_set_NorIntStaEnReg_BlkGapEveStatusEn(U8 data);
/*! \brief Reads the bit group 'BlkGapEveStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
U8   GH_SDIO0_get_NorIntStaEnReg_BlkGapEveStatusEn(void);
/*! \brief Writes the bit group 'DmaIntStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
void GH_SDIO0_set_NorIntStaEnReg_DmaIntStatusEn(U8 data);
/*! \brief Reads the bit group 'DmaIntStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
U8   GH_SDIO0_get_NorIntStaEnReg_DmaIntStatusEn(void);
/*! \brief Writes the bit group 'BufWReadyStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
void GH_SDIO0_set_NorIntStaEnReg_BufWReadyStatusEn(U8 data);
/*! \brief Reads the bit group 'BufWReadyStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
U8   GH_SDIO0_get_NorIntStaEnReg_BufWReadyStatusEn(void);
/*! \brief Writes the bit group 'BufRReadyStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
void GH_SDIO0_set_NorIntStaEnReg_BufRReadyStatusEn(U8 data);
/*! \brief Reads the bit group 'BufRReadyStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
U8   GH_SDIO0_get_NorIntStaEnReg_BufRReadyStatusEn(void);
/*! \brief Writes the bit group 'CardInsertionStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
void GH_SDIO0_set_NorIntStaEnReg_CardInsertionStatusEn(U8 data);
/*! \brief Reads the bit group 'CardInsertionStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
U8   GH_SDIO0_get_NorIntStaEnReg_CardInsertionStatusEn(void);
/*! \brief Writes the bit group 'CardRemStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
void GH_SDIO0_set_NorIntStaEnReg_CardRemStatusEn(U8 data);
/*! \brief Reads the bit group 'CardRemStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
U8   GH_SDIO0_get_NorIntStaEnReg_CardRemStatusEn(void);
/*! \brief Writes the bit group 'CardIntStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
void GH_SDIO0_set_NorIntStaEnReg_CardIntStatusEn(U8 data);
/*! \brief Reads the bit group 'CardIntStatusEn' of register 'SDIO0_NorIntStaEnReg'. */
U8   GH_SDIO0_get_NorIntStaEnReg_CardIntStatusEn(void);
/*! \brief Writes the bit group 'FixedTo0' of register 'SDIO0_NorIntStaEnReg'. */
void GH_SDIO0_set_NorIntStaEnReg_FixedTo0(U8 data);
/*! \brief Reads the bit group 'FixedTo0' of register 'SDIO0_NorIntStaEnReg'. */
U8   GH_SDIO0_get_NorIntStaEnReg_FixedTo0(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntStaEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_ErrIntStaEnReg'. */
void GH_SDIO0_set_ErrIntStaEnReg(U16 data);
/*! \brief Reads the register 'SDIO0_ErrIntStaEnReg'. */
U16  GH_SDIO0_get_ErrIntStaEnReg(void);
/*! \brief Writes the bit group 'CmdTimeoutErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
void GH_SDIO0_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn(U8 data);
/*! \brief Reads the bit group 'CmdTimeoutErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
U8   GH_SDIO0_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn(void);
/*! \brief Writes the bit group 'CmdEndBitErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
void GH_SDIO0_set_ErrIntStaEnReg_CmdEndBitErrStatusEn(U8 data);
/*! \brief Reads the bit group 'CmdEndBitErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
U8   GH_SDIO0_get_ErrIntStaEnReg_CmdEndBitErrStatusEn(void);
/*! \brief Writes the bit group 'CmdCrcErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
void GH_SDIO0_set_ErrIntStaEnReg_CmdCrcErrStatusEn(U8 data);
/*! \brief Reads the bit group 'CmdCrcErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
U8   GH_SDIO0_get_ErrIntStaEnReg_CmdCrcErrStatusEn(void);
/*! \brief Writes the bit group 'CmdIndexErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
void GH_SDIO0_set_ErrIntStaEnReg_CmdIndexErrStatusEn(U8 data);
/*! \brief Reads the bit group 'CmdIndexErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
U8   GH_SDIO0_get_ErrIntStaEnReg_CmdIndexErrStatusEn(void);
/*! \brief Writes the bit group 'DataCrcErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
void GH_SDIO0_set_ErrIntStaEnReg_DataCrcErrStatusEn(U8 data);
/*! \brief Reads the bit group 'DataCrcErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
U8   GH_SDIO0_get_ErrIntStaEnReg_DataCrcErrStatusEn(void);
/*! \brief Writes the bit group 'DataTimeoutErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
void GH_SDIO0_set_ErrIntStaEnReg_DataTimeoutErrStatusEn(U8 data);
/*! \brief Reads the bit group 'DataTimeoutErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
U8   GH_SDIO0_get_ErrIntStaEnReg_DataTimeoutErrStatusEn(void);
/*! \brief Writes the bit group 'DataEndBitErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
void GH_SDIO0_set_ErrIntStaEnReg_DataEndBitErrStatusEn(U8 data);
/*! \brief Reads the bit group 'DataEndBitErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
U8   GH_SDIO0_get_ErrIntStaEnReg_DataEndBitErrStatusEn(void);
/*! \brief Writes the bit group 'CurLimitErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
void GH_SDIO0_set_ErrIntStaEnReg_CurLimitErrStatusEn(U8 data);
/*! \brief Reads the bit group 'CurLimitErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
U8   GH_SDIO0_get_ErrIntStaEnReg_CurLimitErrStatusEn(void);
/*! \brief Writes the bit group 'AutoCmd12ErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
void GH_SDIO0_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn(U8 data);
/*! \brief Reads the bit group 'AutoCmd12ErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
U8   GH_SDIO0_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn(void);
/*! \brief Writes the bit group 'VendorSpecificErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
void GH_SDIO0_set_ErrIntStaEnReg_VendorSpecificErrStatusEn(U8 data);
/*! \brief Reads the bit group 'VendorSpecificErrStatusEn' of register 'SDIO0_ErrIntStaEnReg'. */
U8   GH_SDIO0_get_ErrIntStaEnReg_VendorSpecificErrStatusEn(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_NorIntStaReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_NorIntStaReg'. */
void GH_SDIO0_set_NorIntStaReg(U16 data);
/*! \brief Reads the register 'SDIO0_NorIntStaReg'. */
U16  GH_SDIO0_get_NorIntStaReg(void);
/*! \brief Writes the bit group 'CmdComplete' of register 'SDIO0_NorIntStaReg'. */
void GH_SDIO0_set_NorIntStaReg_CmdComplete(U8 data);
/*! \brief Reads the bit group 'CmdComplete' of register 'SDIO0_NorIntStaReg'. */
U8   GH_SDIO0_get_NorIntStaReg_CmdComplete(void);
/*! \brief Writes the bit group 'BlkGapEvent' of register 'SDIO0_NorIntStaReg'. */
void GH_SDIO0_set_NorIntStaReg_BlkGapEvent(U8 data);
/*! \brief Reads the bit group 'BlkGapEvent' of register 'SDIO0_NorIntStaReg'. */
U8   GH_SDIO0_get_NorIntStaReg_BlkGapEvent(void);
/*! \brief Writes the bit group 'DmaInt' of register 'SDIO0_NorIntStaReg'. */
void GH_SDIO0_set_NorIntStaReg_DmaInt(U8 data);
/*! \brief Reads the bit group 'DmaInt' of register 'SDIO0_NorIntStaReg'. */
U8   GH_SDIO0_get_NorIntStaReg_DmaInt(void);
/*! \brief Writes the bit group 'TraComplete' of register 'SDIO0_NorIntStaReg'. */
void GH_SDIO0_set_NorIntStaReg_TraComplete(U8 data);
/*! \brief Reads the bit group 'TraComplete' of register 'SDIO0_NorIntStaReg'. */
U8   GH_SDIO0_get_NorIntStaReg_TraComplete(void);
/*! \brief Writes the bit group 'BufWReady' of register 'SDIO0_NorIntStaReg'. */
void GH_SDIO0_set_NorIntStaReg_BufWReady(U8 data);
/*! \brief Reads the bit group 'BufWReady' of register 'SDIO0_NorIntStaReg'. */
U8   GH_SDIO0_get_NorIntStaReg_BufWReady(void);
/*! \brief Writes the bit group 'CardInsertion' of register 'SDIO0_NorIntStaReg'. */
void GH_SDIO0_set_NorIntStaReg_CardInsertion(U8 data);
/*! \brief Reads the bit group 'CardInsertion' of register 'SDIO0_NorIntStaReg'. */
U8   GH_SDIO0_get_NorIntStaReg_CardInsertion(void);
/*! \brief Writes the bit group 'BufRReady' of register 'SDIO0_NorIntStaReg'. */
void GH_SDIO0_set_NorIntStaReg_BufRReady(U8 data);
/*! \brief Reads the bit group 'BufRReady' of register 'SDIO0_NorIntStaReg'. */
U8   GH_SDIO0_get_NorIntStaReg_BufRReady(void);
/*! \brief Writes the bit group 'CardRemoval' of register 'SDIO0_NorIntStaReg'. */
void GH_SDIO0_set_NorIntStaReg_CardRemoval(U8 data);
/*! \brief Reads the bit group 'CardRemoval' of register 'SDIO0_NorIntStaReg'. */
U8   GH_SDIO0_get_NorIntStaReg_CardRemoval(void);
/*! \brief Writes the bit group 'CardInt' of register 'SDIO0_NorIntStaReg'. */
void GH_SDIO0_set_NorIntStaReg_CardInt(U8 data);
/*! \brief Reads the bit group 'CardInt' of register 'SDIO0_NorIntStaReg'. */
U8   GH_SDIO0_get_NorIntStaReg_CardInt(void);
/*! \brief Writes the bit group 'BootAckRcv' of register 'SDIO0_NorIntStaReg'. */
void GH_SDIO0_set_NorIntStaReg_BootAckRcv(U8 data);
/*! \brief Reads the bit group 'BootAckRcv' of register 'SDIO0_NorIntStaReg'. */
U8   GH_SDIO0_get_NorIntStaReg_BootAckRcv(void);
/*! \brief Writes the bit group 'ErrInt' of register 'SDIO0_NorIntStaReg'. */
void GH_SDIO0_set_NorIntStaReg_ErrInt(U8 data);
/*! \brief Reads the bit group 'ErrInt' of register 'SDIO0_NorIntStaReg'. */
U8   GH_SDIO0_get_NorIntStaReg_ErrInt(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntStaReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_ErrIntStaReg'. */
void GH_SDIO0_set_ErrIntStaReg(U16 data);
/*! \brief Reads the register 'SDIO0_ErrIntStaReg'. */
U16  GH_SDIO0_get_ErrIntStaReg(void);
/*! \brief Writes the bit group 'CmdTimeoutErr' of register 'SDIO0_ErrIntStaReg'. */
void GH_SDIO0_set_ErrIntStaReg_CmdTimeoutErr(U8 data);
/*! \brief Reads the bit group 'CmdTimeoutErr' of register 'SDIO0_ErrIntStaReg'. */
U8   GH_SDIO0_get_ErrIntStaReg_CmdTimeoutErr(void);
/*! \brief Writes the bit group 'CmdCrcErr' of register 'SDIO0_ErrIntStaReg'. */
void GH_SDIO0_set_ErrIntStaReg_CmdCrcErr(U8 data);
/*! \brief Reads the bit group 'CmdCrcErr' of register 'SDIO0_ErrIntStaReg'. */
U8   GH_SDIO0_get_ErrIntStaReg_CmdCrcErr(void);
/*! \brief Writes the bit group 'CmdEndBitErr' of register 'SDIO0_ErrIntStaReg'. */
void GH_SDIO0_set_ErrIntStaReg_CmdEndBitErr(U8 data);
/*! \brief Reads the bit group 'CmdEndBitErr' of register 'SDIO0_ErrIntStaReg'. */
U8   GH_SDIO0_get_ErrIntStaReg_CmdEndBitErr(void);
/*! \brief Writes the bit group 'CmdIndexErr' of register 'SDIO0_ErrIntStaReg'. */
void GH_SDIO0_set_ErrIntStaReg_CmdIndexErr(U8 data);
/*! \brief Reads the bit group 'CmdIndexErr' of register 'SDIO0_ErrIntStaReg'. */
U8   GH_SDIO0_get_ErrIntStaReg_CmdIndexErr(void);
/*! \brief Writes the bit group 'DataTimeoutErr' of register 'SDIO0_ErrIntStaReg'. */
void GH_SDIO0_set_ErrIntStaReg_DataTimeoutErr(U8 data);
/*! \brief Reads the bit group 'DataTimeoutErr' of register 'SDIO0_ErrIntStaReg'. */
U8   GH_SDIO0_get_ErrIntStaReg_DataTimeoutErr(void);
/*! \brief Writes the bit group 'DataCrcErr' of register 'SDIO0_ErrIntStaReg'. */
void GH_SDIO0_set_ErrIntStaReg_DataCrcErr(U8 data);
/*! \brief Reads the bit group 'DataCrcErr' of register 'SDIO0_ErrIntStaReg'. */
U8   GH_SDIO0_get_ErrIntStaReg_DataCrcErr(void);
/*! \brief Writes the bit group 'DataEndBitErr' of register 'SDIO0_ErrIntStaReg'. */
void GH_SDIO0_set_ErrIntStaReg_DataEndBitErr(U8 data);
/*! \brief Reads the bit group 'DataEndBitErr' of register 'SDIO0_ErrIntStaReg'. */
U8   GH_SDIO0_get_ErrIntStaReg_DataEndBitErr(void);
/*! \brief Writes the bit group 'CurLimitErr' of register 'SDIO0_ErrIntStaReg'. */
void GH_SDIO0_set_ErrIntStaReg_CurLimitErr(U8 data);
/*! \brief Reads the bit group 'CurLimitErr' of register 'SDIO0_ErrIntStaReg'. */
U8   GH_SDIO0_get_ErrIntStaReg_CurLimitErr(void);
/*! \brief Writes the bit group 'AutoCmd12Err' of register 'SDIO0_ErrIntStaReg'. */
void GH_SDIO0_set_ErrIntStaReg_AutoCmd12Err(U8 data);
/*! \brief Reads the bit group 'AutoCmd12Err' of register 'SDIO0_ErrIntStaReg'. */
U8   GH_SDIO0_get_ErrIntStaReg_AutoCmd12Err(void);
/*! \brief Writes the bit group 'VendorSpecificErrStatus' of register 'SDIO0_ErrIntStaReg'. */
void GH_SDIO0_set_ErrIntStaReg_VendorSpecificErrStatus(U8 data);
/*! \brief Reads the bit group 'VendorSpecificErrStatus' of register 'SDIO0_ErrIntStaReg'. */
U8   GH_SDIO0_get_ErrIntStaReg_VendorSpecificErrStatus(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_CmdReg (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_CmdReg'. */
void GH_SDIO0_set_CmdReg(U16 data);
/*! \brief Reads the register 'SDIO0_CmdReg'. */
U16  GH_SDIO0_get_CmdReg(void);
/*! \brief Writes the bit group 'RepTypeSelect' of register 'SDIO0_CmdReg'. */
void GH_SDIO0_set_CmdReg_RepTypeSelect(U8 data);
/*! \brief Reads the bit group 'RepTypeSelect' of register 'SDIO0_CmdReg'. */
U8   GH_SDIO0_get_CmdReg_RepTypeSelect(void);
/*! \brief Writes the bit group 'CmdCrcCheckEn' of register 'SDIO0_CmdReg'. */
void GH_SDIO0_set_CmdReg_CmdCrcCheckEn(U8 data);
/*! \brief Reads the bit group 'CmdCrcCheckEn' of register 'SDIO0_CmdReg'. */
U8   GH_SDIO0_get_CmdReg_CmdCrcCheckEn(void);
/*! \brief Writes the bit group 'DataPreSelect' of register 'SDIO0_CmdReg'. */
void GH_SDIO0_set_CmdReg_DataPreSelect(U8 data);
/*! \brief Reads the bit group 'DataPreSelect' of register 'SDIO0_CmdReg'. */
U8   GH_SDIO0_get_CmdReg_DataPreSelect(void);
/*! \brief Writes the bit group 'CmdIndexCheckEn' of register 'SDIO0_CmdReg'. */
void GH_SDIO0_set_CmdReg_CmdIndexCheckEn(U8 data);
/*! \brief Reads the bit group 'CmdIndexCheckEn' of register 'SDIO0_CmdReg'. */
U8   GH_SDIO0_get_CmdReg_CmdIndexCheckEn(void);
/*! \brief Writes the bit group 'CmdType' of register 'SDIO0_CmdReg'. */
void GH_SDIO0_set_CmdReg_CmdType(U8 data);
/*! \brief Reads the bit group 'CmdType' of register 'SDIO0_CmdReg'. */
U8   GH_SDIO0_get_CmdReg_CmdType(void);
/*! \brief Writes the bit group 'CmdIndex' of register 'SDIO0_CmdReg'. */
void GH_SDIO0_set_CmdReg_CmdIndex(U8 data);
/*! \brief Reads the bit group 'CmdIndex' of register 'SDIO0_CmdReg'. */
U8   GH_SDIO0_get_CmdReg_CmdIndex(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_Control01Reg (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_Control01Reg'. */
void GH_SDIO0_set_Control01Reg(U32 data);
/*! \brief Reads the register 'SDIO0_Control01Reg'. */
U32  GH_SDIO0_get_Control01Reg(void);
/*! \brief Writes the bit group 'DataTimeoutCounterValue' of register 'SDIO0_Control01Reg'. */
void GH_SDIO0_set_Control01Reg_DataTimeoutCounterValue(U8 data);
/*! \brief Reads the bit group 'DataTimeoutCounterValue' of register 'SDIO0_Control01Reg'. */
U8   GH_SDIO0_get_Control01Reg_DataTimeoutCounterValue(void);
/*! \brief Writes the bit group 'SoftwareResetCmdLine' of register 'SDIO0_Control01Reg'. */
void GH_SDIO0_set_Control01Reg_SoftwareResetCmdLine(U8 data);
/*! \brief Reads the bit group 'SoftwareResetCmdLine' of register 'SDIO0_Control01Reg'. */
U8   GH_SDIO0_get_Control01Reg_SoftwareResetCmdLine(void);
/*! \brief Writes the bit group 'SoftwareResetAll' of register 'SDIO0_Control01Reg'. */
void GH_SDIO0_set_Control01Reg_SoftwareResetAll(U8 data);
/*! \brief Reads the bit group 'SoftwareResetAll' of register 'SDIO0_Control01Reg'. */
U8   GH_SDIO0_get_Control01Reg_SoftwareResetAll(void);
/*! \brief Writes the bit group 'SoftwareResetDatLine' of register 'SDIO0_Control01Reg'. */
void GH_SDIO0_set_Control01Reg_SoftwareResetDatLine(U8 data);
/*! \brief Reads the bit group 'SoftwareResetDatLine' of register 'SDIO0_Control01Reg'. */
U8   GH_SDIO0_get_Control01Reg_SoftwareResetDatLine(void);
/*! \brief Writes the bit group 'InternalClkEn' of register 'SDIO0_Control01Reg'. */
void GH_SDIO0_set_Control01Reg_InternalClkEn(U8 data);
/*! \brief Reads the bit group 'InternalClkEn' of register 'SDIO0_Control01Reg'. */
U8   GH_SDIO0_get_Control01Reg_InternalClkEn(void);
/*! \brief Writes the bit group 'InternalClkStable' of register 'SDIO0_Control01Reg'. */
void GH_SDIO0_set_Control01Reg_InternalClkStable(U8 data);
/*! \brief Reads the bit group 'InternalClkStable' of register 'SDIO0_Control01Reg'. */
U8   GH_SDIO0_get_Control01Reg_InternalClkStable(void);
/*! \brief Writes the bit group 'SdClkEn' of register 'SDIO0_Control01Reg'. */
void GH_SDIO0_set_Control01Reg_SdClkEn(U8 data);
/*! \brief Reads the bit group 'SdClkEn' of register 'SDIO0_Control01Reg'. */
U8   GH_SDIO0_get_Control01Reg_SdClkEn(void);
/*! \brief Writes the bit group 'SdclkFreSelect' of register 'SDIO0_Control01Reg'. */
void GH_SDIO0_set_Control01Reg_SdclkFreSelect(U8 data);
/*! \brief Reads the bit group 'SdclkFreSelect' of register 'SDIO0_Control01Reg'. */
U8   GH_SDIO0_get_Control01Reg_SdclkFreSelect(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp0Reg (read)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SDIO0_Resp0Reg'. */
U32  GH_SDIO0_get_Resp0Reg(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp1Reg (read)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SDIO0_Resp1Reg'. */
U32  GH_SDIO0_get_Resp1Reg(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp2Reg (read)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SDIO0_Resp2Reg'. */
U32  GH_SDIO0_get_Resp2Reg(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp3Reg (read)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SDIO0_Resp3Reg'. */
U32  GH_SDIO0_get_Resp3Reg(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_Control00Reg (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg(U32 data);
/*! \brief Reads the register 'SDIO0_Control00Reg'. */
U32  GH_SDIO0_get_Control00Reg(void);
/*! \brief Writes the bit group 'LedControl' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_LedControl(U8 data);
/*! \brief Reads the bit group 'LedControl' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_LedControl(void);
/*! \brief Writes the bit group 'DataTraWidth' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_DataTraWidth(U8 data);
/*! \brief Reads the bit group 'DataTraWidth' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_DataTraWidth(void);
/*! \brief Writes the bit group 'Sd8BitMode' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_Sd8BitMode(U8 data);
/*! \brief Reads the bit group 'Sd8BitMode' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_Sd8BitMode(void);
/*! \brief Writes the bit group 'HostSpeedEn' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_HostSpeedEn(U8 data);
/*! \brief Reads the bit group 'HostSpeedEn' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_HostSpeedEn(void);
/*! \brief Writes the bit group 'CardDetectTestLevel' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_CardDetectTestLevel(U8 data);
/*! \brief Reads the bit group 'CardDetectTestLevel' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_CardDetectTestLevel(void);
/*! \brief Writes the bit group 'CardDetectSigDet' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_CardDetectSigDet(U8 data);
/*! \brief Reads the bit group 'CardDetectSigDet' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_CardDetectSigDet(void);
/*! \brief Writes the bit group 'SdBusPower' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_SdBusPower(U8 data);
/*! \brief Reads the bit group 'SdBusPower' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_SdBusPower(void);
/*! \brief Writes the bit group 'SdBusVoltageSelect' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_SdBusVoltageSelect(U8 data);
/*! \brief Reads the bit group 'SdBusVoltageSelect' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_SdBusVoltageSelect(void);
/*! \brief Writes the bit group 'StopAtBlkGapReq' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_StopAtBlkGapReq(U8 data);
/*! \brief Reads the bit group 'StopAtBlkGapReq' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_StopAtBlkGapReq(void);
/*! \brief Writes the bit group 'RWaitControl' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_RWaitControl(U8 data);
/*! \brief Reads the bit group 'RWaitControl' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_RWaitControl(void);
/*! \brief Writes the bit group 'ContinueReq' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_ContinueReq(U8 data);
/*! \brief Reads the bit group 'ContinueReq' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_ContinueReq(void);
/*! \brief Writes the bit group 'IntAtBlkGap' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_IntAtBlkGap(U8 data);
/*! \brief Reads the bit group 'IntAtBlkGap' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_IntAtBlkGap(void);
/*! \brief Writes the bit group 'DriveCcsd' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_DriveCcsd(U8 data);
/*! \brief Reads the bit group 'DriveCcsd' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_DriveCcsd(void);
/*! \brief Writes the bit group 'SpiMode' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_SpiMode(U8 data);
/*! \brief Reads the bit group 'SpiMode' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_SpiMode(void);
/*! \brief Writes the bit group 'BootEn' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_BootEn(U8 data);
/*! \brief Reads the bit group 'BootEn' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_BootEn(void);
/*! \brief Writes the bit group 'AltBootEn' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_AltBootEn(U8 data);
/*! \brief Reads the bit group 'AltBootEn' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_AltBootEn(void);
/*! \brief Writes the bit group 'WakeupEvetEnOnCardIns' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardIns(U8 data);
/*! \brief Reads the bit group 'WakeupEvetEnOnCardIns' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardIns(void);
/*! \brief Writes the bit group 'WakeupEvetEnOnCardInt' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardInt(U8 data);
/*! \brief Reads the bit group 'WakeupEvetEnOnCardInt' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardInt(void);
/*! \brief Writes the bit group 'WakeupEvetEnOnCardRem' of register 'SDIO0_Control00Reg'. */
void GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardRem(U8 data);
/*! \brief Reads the bit group 'WakeupEvetEnOnCardRem' of register 'SDIO0_Control00Reg'. */
U8   GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardRem(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_PresentStateReg (read)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SDIO0_PresentStateReg'. */
U32  GH_SDIO0_get_PresentStateReg(void);
/*! \brief Reads the bit group 'CmdInhibitCmd' of register 'SDIO0_PresentStateReg'. */
U8   GH_SDIO0_get_PresentStateReg_CmdInhibitCmd(void);
/*! \brief Reads the bit group 'DataLineActive' of register 'SDIO0_PresentStateReg'. */
U8   GH_SDIO0_get_PresentStateReg_DataLineActive(void);
/*! \brief Reads the bit group 'CmdInhibitData' of register 'SDIO0_PresentStateReg'. */
U8   GH_SDIO0_get_PresentStateReg_CmdInhibitData(void);
/*! \brief Reads the bit group 'RTraActive' of register 'SDIO0_PresentStateReg'. */
U8   GH_SDIO0_get_PresentStateReg_RTraActive(void);
/*! \brief Reads the bit group 'BufWEn' of register 'SDIO0_PresentStateReg'. */
U8   GH_SDIO0_get_PresentStateReg_BufWEn(void);
/*! \brief Reads the bit group 'WTraActive' of register 'SDIO0_PresentStateReg'. */
U8   GH_SDIO0_get_PresentStateReg_WTraActive(void);
/*! \brief Reads the bit group 'BufREn' of register 'SDIO0_PresentStateReg'. */
U8   GH_SDIO0_get_PresentStateReg_BufREn(void);
/*! \brief Reads the bit group 'CardInserted' of register 'SDIO0_PresentStateReg'. */
U8   GH_SDIO0_get_PresentStateReg_CardInserted(void);
/*! \brief Reads the bit group 'CardDetectPinLevel' of register 'SDIO0_PresentStateReg'. */
U8   GH_SDIO0_get_PresentStateReg_CardDetectPinLevel(void);
/*! \brief Reads the bit group 'CardStateStable' of register 'SDIO0_PresentStateReg'. */
U8   GH_SDIO0_get_PresentStateReg_CardStateStable(void);
/*! \brief Reads the bit group 'WProSwiPinLevel' of register 'SDIO0_PresentStateReg'. */
U8   GH_SDIO0_get_PresentStateReg_WProSwiPinLevel(void);
/*! \brief Reads the bit group 'Data03LineSigLevel' of register 'SDIO0_PresentStateReg'. */
U8   GH_SDIO0_get_PresentStateReg_Data03LineSigLevel(void);
/*! \brief Reads the bit group 'CmdLineSigLevel' of register 'SDIO0_PresentStateReg'. */
U8   GH_SDIO0_get_PresentStateReg_CmdLineSigLevel(void);
/*! \brief Reads the bit group 'Data47LineSigLevel' of register 'SDIO0_PresentStateReg'. */
U8   GH_SDIO0_get_PresentStateReg_Data47LineSigLevel(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_ArgReg (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_ArgReg'. */
void GH_SDIO0_set_ArgReg(U32 data);
/*! \brief Reads the register 'SDIO0_ArgReg'. */
U32  GH_SDIO0_get_ArgReg(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_CapReg (read)                                               */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SDIO0_CapReg'. */
U32  GH_SDIO0_get_CapReg(void);
/*! \brief Reads the bit group 'TimeoutClkFre' of register 'SDIO0_CapReg'. */
U8   GH_SDIO0_get_CapReg_TimeoutClkFre(void);
/*! \brief Reads the bit group 'TimeoutClkUnit' of register 'SDIO0_CapReg'. */
U8   GH_SDIO0_get_CapReg_TimeoutClkUnit(void);
/*! \brief Reads the bit group 'BaseClkFreForSdClk' of register 'SDIO0_CapReg'. */
U8   GH_SDIO0_get_CapReg_BaseClkFreForSdClk(void);
/*! \brief Reads the bit group 'MaxBlkLen' of register 'SDIO0_CapReg'. */
U8   GH_SDIO0_get_CapReg_MaxBlkLen(void);
/*! \brief Reads the bit group 'ExtendedMediaBusSup' of register 'SDIO0_CapReg'. */
U8   GH_SDIO0_get_CapReg_ExtendedMediaBusSup(void);
/*! \brief Reads the bit group 'HighSpeedSup' of register 'SDIO0_CapReg'. */
U8   GH_SDIO0_get_CapReg_HighSpeedSup(void);
/*! \brief Reads the bit group 'SusResSup' of register 'SDIO0_CapReg'. */
U8   GH_SDIO0_get_CapReg_SusResSup(void);
/*! \brief Reads the bit group 'SdmaSup' of register 'SDIO0_CapReg'. */
U8   GH_SDIO0_get_CapReg_SdmaSup(void);
/*! \brief Reads the bit group 'VoltageSup33v' of register 'SDIO0_CapReg'. */
U8   GH_SDIO0_get_CapReg_VoltageSup33v(void);
/*! \brief Reads the bit group 'VoltageSup30v' of register 'SDIO0_CapReg'. */
U8   GH_SDIO0_get_CapReg_VoltageSup30v(void);
/*! \brief Reads the bit group 'VoltageSup18v' of register 'SDIO0_CapReg'. */
U8   GH_SDIO0_get_CapReg_VoltageSup18v(void);
/*! \brief Reads the bit group 'IntMode' of register 'SDIO0_CapReg'. */
U8   GH_SDIO0_get_CapReg_IntMode(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_AutoCmd12ErrStatusReg (read)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SDIO0_AutoCmd12ErrStatusReg'. */
U32  GH_SDIO0_get_AutoCmd12ErrStatusReg(void);
/*! \brief Reads the bit group 'AutoCmd12TimeoutErr' of register 'SDIO0_AutoCmd12ErrStatusReg'. */
U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr(void);
/*! \brief Reads the bit group 'AutoCmd12CrcErr' of register 'SDIO0_AutoCmd12ErrStatusReg'. */
U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr(void);
/*! \brief Reads the bit group 'AutoCmd12EndBitErr' of register 'SDIO0_AutoCmd12ErrStatusReg'. */
U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr(void);
/*! \brief Reads the bit group 'AutoCmd12NotExe' of register 'SDIO0_AutoCmd12ErrStatusReg'. */
U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe(void);
/*! \brief Reads the bit group 'AutoCmd12IndexErr' of register 'SDIO0_AutoCmd12ErrStatusReg'. */
U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr(void);
/*! \brief Reads the bit group 'CmdNotIssuedByAutoCmd12Err' of register 'SDIO0_AutoCmd12ErrStatusReg'. */
U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_BufferDataPortReg (read/write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_BufferDataPortReg'. */
void GH_SDIO0_set_BufferDataPortReg(U32 data);
/*! \brief Reads the register 'SDIO0_BufferDataPortReg'. */
U32  GH_SDIO0_get_BufferDataPortReg(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_MaxCurCapReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SDIO0_MaxCurCapReg'. */
void GH_SDIO0_set_MaxCurCapReg(U32 data);
/*! \brief Reads the register 'SDIO0_MaxCurCapReg'. */
U32  GH_SDIO0_get_MaxCurCapReg(void);
/*! \brief Writes the bit group 'MaxCurFor33v' of register 'SDIO0_MaxCurCapReg'. */
void GH_SDIO0_set_MaxCurCapReg_MaxCurFor33v(U8 data);
/*! \brief Reads the bit group 'MaxCurFor33v' of register 'SDIO0_MaxCurCapReg'. */
U8   GH_SDIO0_get_MaxCurCapReg_MaxCurFor33v(void);
/*! \brief Writes the bit group 'MaxCurFor30v' of register 'SDIO0_MaxCurCapReg'. */
void GH_SDIO0_set_MaxCurCapReg_MaxCurFor30v(U8 data);
/*! \brief Reads the bit group 'MaxCurFor30v' of register 'SDIO0_MaxCurCapReg'. */
U8   GH_SDIO0_get_MaxCurCapReg_MaxCurFor30v(void);
/*! \brief Writes the bit group 'MaxCurFor18v' of register 'SDIO0_MaxCurCapReg'. */
void GH_SDIO0_set_MaxCurCapReg_MaxCurFor18v(U8 data);
/*! \brief Reads the bit group 'MaxCurFor18v' of register 'SDIO0_MaxCurCapReg'. */
U8   GH_SDIO0_get_MaxCurCapReg_MaxCurFor18v(void);

/*----------------------------------------------------------------------------*/
/* register SDIO0_SlotIntStatusReg (read)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SDIO0_SlotIntStatusReg'. */
U32  GH_SDIO0_get_SlotIntStatusReg(void);
/*! \brief Reads the bit group 'IntSigForEachSlot' of register 'SDIO0_SlotIntStatusReg'. */
U8   GH_SDIO0_get_SlotIntStatusReg_IntSigForEachSlot(void);
/*! \brief Reads the bit group 'SpecifiVerNum' of register 'SDIO0_SlotIntStatusReg'. */
U8   GH_SDIO0_get_SlotIntStatusReg_SpecifiVerNum(void);
/*! \brief Reads the bit group 'VendorVerNum' of register 'SDIO0_SlotIntStatusReg'. */
U8   GH_SDIO0_get_SlotIntStatusReg_VendorVerNum(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_SDIO0_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_sdio0.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_SDIO0_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

