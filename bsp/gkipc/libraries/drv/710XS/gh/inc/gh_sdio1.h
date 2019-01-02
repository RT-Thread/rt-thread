/*!
*******************************************************************************
**
** \file      gh_sdio1.h
**
** \brief     SDIO1 Host Controller.
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
#ifndef _GH_SDIO1_H
#define _GH_SDIO1_H

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

#define GH_SDIO1_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_SDIO1_DEBUG_PRINT_FUNCTION printk
#else
#define GH_SDIO1_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_SDIO1_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/* check configuration */
#ifndef GH_INLINE_LEVEL
  #error "GH_INLINE_LEVEL is not defined!"
#endif
#if GH_INLINE_LEVEL > 2
  #error "GH_INLINE_LEVEL must be set 0, 1 or 2!"
#endif
#ifndef GH_INLINE
  #error "GH_INLINE is not defined!"
#endif

/* disable inlining for debugging */
#ifdef DEBUG
  #undef GH_INLINE_LEVEL
  #define GH_INLINE_LEVEL 0
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_SDIO1_SYSADDRREG                                FIO_ADDRESS(SDIO1,0x90010000) /* read/write */
#define REG_SDIO1_TRANMODENORINTSIGENREG                    FIO_ADDRESS(SDIO1,0x90010004) /* read/write */
#define REG_SDIO1_ERRINTSIGENBLKCOUREG                      FIO_ADDRESS(SDIO1,0x90010008) /* read/write */
#define REG_SDIO1_BLKSIZENORINTSTAENREG                     FIO_ADDRESS(SDIO1,0x9001000C) /* read/write */
#define REG_SDIO1_ERRINTSTAENNORINTSTAREG                   FIO_ADDRESS(SDIO1,0x90010010) /* read/write */
#define REG_SDIO1_ERRINTSTATUSCOMMONDREG                    FIO_ADDRESS(SDIO1,0x90010014) /* read/write */
#define REG_SDIO1_CONTROL01REG                              FIO_ADDRESS(SDIO1,0x90010018) /* read/write */
#define REG_SDIO1_RESP0REG                                  FIO_ADDRESS(SDIO1,0x9001001C) /* read */
#define REG_SDIO1_RESP1REG                                  FIO_ADDRESS(SDIO1,0x90010020) /* read */
#define REG_SDIO1_RESP2REG                                  FIO_ADDRESS(SDIO1,0x90010024) /* read */
#define REG_SDIO1_RESP3REG                                  FIO_ADDRESS(SDIO1,0x90010028) /* read */
#define REG_SDIO1_CONTROL00REG                              FIO_ADDRESS(SDIO1,0x9001002C) /* read/write */
#define REG_SDIO1_PRESENTSTATEREG                           FIO_ADDRESS(SDIO1,0x90010030) /* read */
#define REG_SDIO1_ARGREG                                    FIO_ADDRESS(SDIO1,0x90010034) /* read/write */
#define REG_SDIO1_CAPREG                                    FIO_ADDRESS(SDIO1,0x90010038) /* read */
#define REG_SDIO1_AUTOCMD12ERRSTATUSREG                     FIO_ADDRESS(SDIO1,0x9001003C) /* read */
#define REG_SDIO1_BUFFERDATAPORTREG                         FIO_ADDRESS(SDIO1,0x90010040) /* read/write */
#define REG_SDIO1_MAXCURCAPREG                              FIO_ADDRESS(SDIO1,0x90010048) /* read/write */
#define REG_SDIO1_SLOTINTSTATUSREG                          FIO_ADDRESS(SDIO1,0x900100FC) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* SDIO1_TranModeNorIntSigEnReg */
    U32 all;
    struct {
        U32 blkcounten                  : 1;
        U32 autocmd12en                 : 1;
        U32 dmaen                       : 1;
        U32                             : 1;
        U32 msblkselect                 : 1;
        U32 datatradirselect            : 1;
        U32                             : 10;
        U32 cmdcompletesigen            : 1;
        U32 tracompletesigen            : 1;
        U32 blkgapevesigen              : 1;
        U32 dmaintsigen                 : 1;
        U32 bufwreadysigen              : 1;
        U32 bufrreadysigen              : 1;
        U32 cardinsertionsigen          : 1;
        U32 cardremsigen                : 1;
        U32 cardintsigen                : 1;
        U32                             : 6;
        U32 fixedto0                    : 1;
    } bitc;
} GH_SDIO1_TRANMODENORINTSIGENREG_S;

typedef union { /* SDIO1_ErrIntSigEnBlkCouReg */
    U32 all;
    struct {
        U32 cmdtimeouterrsigen          : 1;
        U32 cmdendbiterrsigen           : 1;
        U32 cmdindexerrsigen            : 1;
        U32 datatimeouterrsigen         : 1;
        U32 cmdcrcerrsigen              : 1;
        U32 datacrcerrsigen             : 1;
        U32 dataendbiterrsigen          : 1;
        U32 curlimiterrsigen            : 1;
        U32 autocmd12errsigen           : 1;
        U32                             : 5;
        U32 vendorspecificerrsigen      : 2;
        U32 blkcountforcurtra           : 16;
    } bitc;
} GH_SDIO1_ERRINTSIGENBLKCOUREG_S;

typedef union { /* SDIO1_BlkSizeNorIntStaEnReg */
    U32 all;
    struct {
        U32 trablksize                  : 12;
        U32 hostsdmabufsize             : 3;
        U32                             : 1;
        U32 cmdcompletestatusen         : 1;
        U32 tracompletestatusen         : 1;
        U32 blkgapevestatusen           : 1;
        U32 dmaintstatusen              : 1;
        U32 bufwreadystatusen           : 1;
        U32 bufrreadystatusen           : 1;
        U32 cardinsertionstatusen       : 1;
        U32 cardremstatusen             : 1;
        U32 cardintstatusen             : 1;
        U32                             : 6;
        U32 fixedto0                    : 1;
    } bitc;
} GH_SDIO1_BLKSIZENORINTSTAENREG_S;

typedef union { /* SDIO1_ErrIntStaEnNorIntStaReg */
    U32 all;
    struct {
        U32 cmdtimeouterrstatusen       : 1;
        U32 cmdendbiterrstatusen        : 1;
        U32 cmdcrcerrstatusen           : 1;
        U32 cmdindexerrstatusen         : 1;
        U32 datacrcerrstatusen          : 1;
        U32 datatimeouterrstatusen      : 1;
        U32 dataendbiterrstatusen       : 1;
        U32 curlimiterrstatusen         : 1;
        U32 autocmd12errstatusen        : 1;
        U32                             : 5;
        U32 vendorspecificerrstatusen   : 2;
        U32 cmdcomplete                 : 1;
        U32 blkgapevent                 : 1;
        U32 dmaint                      : 1;
        U32 tracomplete                 : 1;
        U32 bufwready                   : 1;
        U32 cardinsertion               : 1;
        U32 bufrready                   : 1;
        U32 cardremoval                 : 1;
        U32 cardint                     : 1;
        U32 bootackrcv                  : 1;
        U32                             : 5;
        U32 errint                      : 1;
    } bitc;
} GH_SDIO1_ERRINTSTAENNORINTSTAREG_S;

typedef union { /* SDIO1_ErrIntStatusCommondReg */
    U32 all;
    struct {
        U32 cmdtimeouterr               : 1;
        U32 cmdcrcerr                   : 1;
        U32 cmdendbiterr                : 1;
        U32 cmdindexerr                 : 1;
        U32 datatimeouterr              : 1;
        U32 datacrcerr                  : 1;
        U32 dataendbiterr               : 1;
        U32 curlimiterr                 : 1;
        U32 autocmd12err                : 1;
        U32                             : 5;
        U32 vendorspecificerrstatus     : 2;
        U32 reptypeselect               : 2;
        U32                             : 1;
        U32 cmdcrcchecken               : 1;
        U32 datapreselect               : 1;
        U32 cmdindexchecken             : 1;
        U32 cmdtype                     : 2;
        U32 cmdindex                    : 6;
        U32                             : 2;
    } bitc;
} GH_SDIO1_ERRINTSTATUSCOMMONDREG_S;

typedef union { /* SDIO1_Control01Reg */
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
} GH_SDIO1_CONTROL01REG_S;

typedef union { /* SDIO1_Control00Reg */
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
} GH_SDIO1_CONTROL00REG_S;

typedef union { /* SDIO1_PresentStateReg */
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
} GH_SDIO1_PRESENTSTATEREG_S;

typedef union { /* SDIO1_CapReg */
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
} GH_SDIO1_CAPREG_S;

typedef union { /* SDIO1_AutoCmd12ErrStatusReg */
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
} GH_SDIO1_AUTOCMD12ERRSTATUSREG_S;

typedef union { /* SDIO1_MaxCurCapReg */
    U32 all;
    struct {
        U32 maxcurfor33v                : 8;
        U32 maxcurfor30v                : 8;
        U32 maxcurfor18v                : 8;
        U32                             : 8;
    } bitc;
} GH_SDIO1_MAXCURCAPREG_S;

typedef union { /* SDIO1_SlotIntStatusReg */
    U32 all;
    struct {
        U32 intsigforeachslot           : 8;
        U32                             : 8;
        U32 specifivernum               : 8;
        U32 vendorvernum                : 8;
    } bitc;
} GH_SDIO1_SLOTINTSTATUSREG_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register SDIO1_SysAddrReg (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO1_SysAddrReg'. */
void GH_SDIO1_set_SysAddrReg(U32 data);
/*! \brief Reads the register 'SDIO1_SysAddrReg'. */
U32  GH_SDIO1_get_SysAddrReg(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO1_set_SysAddrReg(U32 data)
{
    *(volatile U32 *)REG_SDIO1_SYSADDRREG = data;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_SysAddrReg] <-- 0x%08x\n",
                        REG_SDIO1_SYSADDRREG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO1_get_SysAddrReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_SYSADDRREG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_SysAddrReg] --> 0x%08x\n",
                        REG_SDIO1_SYSADDRREG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_TranModeNorIntSigEnReg (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg(U32 data);
/*! \brief Reads the register 'SDIO1_TranModeNorIntSigEnReg'. */
U32  GH_SDIO1_get_TranModeNorIntSigEnReg(void);
/*! \brief Writes the bit group 'BlkCountEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_BlkCountEn(U8 data);
/*! \brief Reads the bit group 'BlkCountEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_BlkCountEn(void);
/*! \brief Writes the bit group 'AutoCmd12En' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_AutoCmd12En(U8 data);
/*! \brief Reads the bit group 'AutoCmd12En' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_AutoCmd12En(void);
/*! \brief Writes the bit group 'DmaEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_DmaEn(U8 data);
/*! \brief Reads the bit group 'DmaEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_DmaEn(void);
/*! \brief Writes the bit group 'MSBlkSelect' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_MSBlkSelect(U8 data);
/*! \brief Reads the bit group 'MSBlkSelect' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_MSBlkSelect(void);
/*! \brief Writes the bit group 'DataTraDirSelect' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_DataTraDirSelect(U8 data);
/*! \brief Reads the bit group 'DataTraDirSelect' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_DataTraDirSelect(void);
/*! \brief Writes the bit group 'CmdCompleteSigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_CmdCompleteSigEn(U8 data);
/*! \brief Reads the bit group 'CmdCompleteSigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_CmdCompleteSigEn(void);
/*! \brief Writes the bit group 'TraCompleteSigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_TraCompleteSigEn(U8 data);
/*! \brief Reads the bit group 'TraCompleteSigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_TraCompleteSigEn(void);
/*! \brief Writes the bit group 'BlkGapEveSigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_BlkGapEveSigEn(U8 data);
/*! \brief Reads the bit group 'BlkGapEveSigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_BlkGapEveSigEn(void);
/*! \brief Writes the bit group 'DmaIntSigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_DmaIntSigEn(U8 data);
/*! \brief Reads the bit group 'DmaIntSigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_DmaIntSigEn(void);
/*! \brief Writes the bit group 'BufWReadySigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_BufWReadySigEn(U8 data);
/*! \brief Reads the bit group 'BufWReadySigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_BufWReadySigEn(void);
/*! \brief Writes the bit group 'BufRReadySigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_BufRReadySigEn(U8 data);
/*! \brief Reads the bit group 'BufRReadySigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_BufRReadySigEn(void);
/*! \brief Writes the bit group 'CardInsertionSigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_CardInsertionSigEn(U8 data);
/*! \brief Reads the bit group 'CardInsertionSigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_CardInsertionSigEn(void);
/*! \brief Writes the bit group 'CardRemSigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_CardRemSigEn(U8 data);
/*! \brief Reads the bit group 'CardRemSigEn' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_CardRemSigEn(void);
/*! \brief Writes the bit group 'CardIntSigEN' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_CardIntSigEN(U8 data);
/*! \brief Reads the bit group 'CardIntSigEN' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_CardIntSigEN(void);
/*! \brief Writes the bit group 'FixedTo0' of register 'SDIO1_TranModeNorIntSigEnReg'. */
void GH_SDIO1_set_TranModeNorIntSigEnReg_FixedTo0(U8 data);
/*! \brief Reads the bit group 'FixedTo0' of register 'SDIO1_TranModeNorIntSigEnReg'. */
U8   GH_SDIO1_get_TranModeNorIntSigEnReg_FixedTo0(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg(U32 data)
{
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = data;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO1_get_TranModeNorIntSigEnReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_BlkCountEn(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.blkcounten = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_BlkCountEn] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_BlkCountEn(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_BlkCountEn] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.blkcounten;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_AutoCmd12En(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.autocmd12en = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_AutoCmd12En] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_AutoCmd12En(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_AutoCmd12En] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.autocmd12en;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_DmaEn(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.dmaen = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_DmaEn] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_DmaEn(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_DmaEn] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.dmaen;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_MSBlkSelect(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.msblkselect = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_MSBlkSelect] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_MSBlkSelect(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_MSBlkSelect] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.msblkselect;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_DataTraDirSelect(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.datatradirselect = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_DataTraDirSelect] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_DataTraDirSelect(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_DataTraDirSelect] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.datatradirselect;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_CmdCompleteSigEn(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.cmdcompletesigen = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_CmdCompleteSigEn] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_CmdCompleteSigEn(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_CmdCompleteSigEn] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cmdcompletesigen;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_TraCompleteSigEn(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.tracompletesigen = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_TraCompleteSigEn] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_TraCompleteSigEn(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_TraCompleteSigEn] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.tracompletesigen;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_BlkGapEveSigEn(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.blkgapevesigen = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_BlkGapEveSigEn] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_BlkGapEveSigEn(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_BlkGapEveSigEn] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.blkgapevesigen;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_DmaIntSigEn(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.dmaintsigen = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_DmaIntSigEn] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_DmaIntSigEn(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_DmaIntSigEn] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.dmaintsigen;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_BufWReadySigEn(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.bufwreadysigen = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_BufWReadySigEn] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_BufWReadySigEn(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_BufWReadySigEn] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.bufwreadysigen;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_BufRReadySigEn(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.bufrreadysigen = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_BufRReadySigEn] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_BufRReadySigEn(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_BufRReadySigEn] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.bufrreadysigen;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_CardInsertionSigEn(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.cardinsertionsigen = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_CardInsertionSigEn] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_CardInsertionSigEn(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_CardInsertionSigEn] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardinsertionsigen;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_CardRemSigEn(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.cardremsigen = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_CardRemSigEn] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_CardRemSigEn(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_CardRemSigEn] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardremsigen;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_CardIntSigEN(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.cardintsigen = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_CardIntSigEN] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_CardIntSigEN(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_CardIntSigEN] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardintsigen;
}
GH_INLINE void GH_SDIO1_set_TranModeNorIntSigEnReg_FixedTo0(U8 data)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG;
    d.bitc.fixedto0 = data;
    *(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_TranModeNorIntSigEnReg_FixedTo0] <-- 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_TranModeNorIntSigEnReg_FixedTo0(void)
{
    GH_SDIO1_TRANMODENORINTSIGENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_TRANMODENORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_TranModeNorIntSigEnReg_FixedTo0] --> 0x%08x\n",
                        REG_SDIO1_TRANMODENORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.fixedto0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_ErrIntSigEnBlkCouReg (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO1_ErrIntSigEnBlkCouReg'. */
void GH_SDIO1_set_ErrIntSigEnBlkCouReg(U32 data);
/*! \brief Reads the register 'SDIO1_ErrIntSigEnBlkCouReg'. */
U32  GH_SDIO1_get_ErrIntSigEnBlkCouReg(void);
/*! \brief Writes the bit group 'CmdTimeoutErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
void GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn(U8 data);
/*! \brief Reads the bit group 'CmdTimeoutErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn(void);
/*! \brief Writes the bit group 'CmdEndBitErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
void GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn(U8 data);
/*! \brief Reads the bit group 'CmdEndBitErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn(void);
/*! \brief Writes the bit group 'CmdIndexErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
void GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn(U8 data);
/*! \brief Reads the bit group 'CmdIndexErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn(void);
/*! \brief Writes the bit group 'DataTimeoutErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
void GH_SDIO1_set_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn(U8 data);
/*! \brief Reads the bit group 'DataTimeoutErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn(void);
/*! \brief Writes the bit group 'CmdCrcErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
void GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn(U8 data);
/*! \brief Reads the bit group 'CmdCrcErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn(void);
/*! \brief Writes the bit group 'DataCrcErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
void GH_SDIO1_set_ErrIntSigEnBlkCouReg_DataCrcErrSigEn(U8 data);
/*! \brief Reads the bit group 'DataCrcErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_DataCrcErrSigEn(void);
/*! \brief Writes the bit group 'DataEndBitErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
void GH_SDIO1_set_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn(U8 data);
/*! \brief Reads the bit group 'DataEndBitErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn(void);
/*! \brief Writes the bit group 'CurLimitErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
void GH_SDIO1_set_ErrIntSigEnBlkCouReg_CurLimitErrSigEn(U8 data);
/*! \brief Reads the bit group 'CurLimitErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_CurLimitErrSigEn(void);
/*! \brief Writes the bit group 'AutoCmd12ErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
void GH_SDIO1_set_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn(U8 data);
/*! \brief Reads the bit group 'AutoCmd12ErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn(void);
/*! \brief Writes the bit group 'VendorSpecificErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
void GH_SDIO1_set_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn(U8 data);
/*! \brief Reads the bit group 'VendorSpecificErrSigEn' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn(void);
/*! \brief Writes the bit group 'BlkCountForCurTra' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
void GH_SDIO1_set_ErrIntSigEnBlkCouReg_BlkCountForCurTra(U16 data);
/*! \brief Reads the bit group 'BlkCountForCurTra' of register 'SDIO1_ErrIntSigEnBlkCouReg'. */
U16  GH_SDIO1_get_ErrIntSigEnBlkCouReg_BlkCountForCurTra(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO1_set_ErrIntSigEnBlkCouReg(U32 data)
{
    *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG = data;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntSigEnBlkCouReg] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO1_get_ErrIntSigEnBlkCouReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntSigEnBlkCouReg] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn(U8 data)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG;
    d.bitc.cmdtimeouterrsigen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn(void)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdTimeoutErrSigEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.cmdtimeouterrsigen;
}
GH_INLINE void GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn(U8 data)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG;
    d.bitc.cmdendbiterrsigen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn(void)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdEndBitErrSigEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.cmdendbiterrsigen;
}
GH_INLINE void GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn(U8 data)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG;
    d.bitc.cmdindexerrsigen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn(void)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdIndexErrSigEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.cmdindexerrsigen;
}
GH_INLINE void GH_SDIO1_set_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn(U8 data)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG;
    d.bitc.datatimeouterrsigen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn(void)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntSigEnBlkCouReg_DataTimeoutErrSigEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.datatimeouterrsigen;
}
GH_INLINE void GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn(U8 data)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG;
    d.bitc.cmdcrcerrsigen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn(void)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntSigEnBlkCouReg_CmdCrcErrSigEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.cmdcrcerrsigen;
}
GH_INLINE void GH_SDIO1_set_ErrIntSigEnBlkCouReg_DataCrcErrSigEn(U8 data)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG;
    d.bitc.datacrcerrsigen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntSigEnBlkCouReg_DataCrcErrSigEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_DataCrcErrSigEn(void)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntSigEnBlkCouReg_DataCrcErrSigEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.datacrcerrsigen;
}
GH_INLINE void GH_SDIO1_set_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn(U8 data)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG;
    d.bitc.dataendbiterrsigen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn(void)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntSigEnBlkCouReg_DataEndBitErrSigEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.dataendbiterrsigen;
}
GH_INLINE void GH_SDIO1_set_ErrIntSigEnBlkCouReg_CurLimitErrSigEn(U8 data)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG;
    d.bitc.curlimiterrsigen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntSigEnBlkCouReg_CurLimitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_CurLimitErrSigEn(void)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntSigEnBlkCouReg_CurLimitErrSigEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.curlimiterrsigen;
}
GH_INLINE void GH_SDIO1_set_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn(U8 data)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG;
    d.bitc.autocmd12errsigen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn(void)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntSigEnBlkCouReg_AutoCmd12ErrSigEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.autocmd12errsigen;
}
GH_INLINE void GH_SDIO1_set_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn(U8 data)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG;
    d.bitc.vendorspecificerrsigen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn(void)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntSigEnBlkCouReg_VendorSpecificErrSigEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.vendorspecificerrsigen;
}
GH_INLINE void GH_SDIO1_set_ErrIntSigEnBlkCouReg_BlkCountForCurTra(U16 data)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG;
    d.bitc.blkcountforcurtra = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntSigEnBlkCouReg_BlkCountForCurTra] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_SDIO1_get_ErrIntSigEnBlkCouReg_BlkCountForCurTra(void)
{
    GH_SDIO1_ERRINTSIGENBLKCOUREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSIGENBLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntSigEnBlkCouReg_BlkCountForCurTra] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSIGENBLKCOUREG,value);
    #endif
    return tmp_value.bitc.blkcountforcurtra;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_BlkSizeNorIntStaEnReg (read/write)                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO1_BlkSizeNorIntStaEnReg'. */
void GH_SDIO1_set_BlkSizeNorIntStaEnReg(U32 data);
/*! \brief Reads the register 'SDIO1_BlkSizeNorIntStaEnReg'. */
U32  GH_SDIO1_get_BlkSizeNorIntStaEnReg(void);
/*! \brief Writes the bit group 'TraBlkSize' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
void GH_SDIO1_set_BlkSizeNorIntStaEnReg_TraBlkSize(U16 data);
/*! \brief Reads the bit group 'TraBlkSize' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
U16  GH_SDIO1_get_BlkSizeNorIntStaEnReg_TraBlkSize(void);
/*! \brief Writes the bit group 'HostSdmaBufSize' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
void GH_SDIO1_set_BlkSizeNorIntStaEnReg_HostSdmaBufSize(U8 data);
/*! \brief Reads the bit group 'HostSdmaBufSize' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_HostSdmaBufSize(void);
/*! \brief Writes the bit group 'CmdCompleteStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
void GH_SDIO1_set_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn(U8 data);
/*! \brief Reads the bit group 'CmdCompleteStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn(void);
/*! \brief Writes the bit group 'TraCompleteStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
void GH_SDIO1_set_BlkSizeNorIntStaEnReg_TraCompleteStatusEn(U8 data);
/*! \brief Reads the bit group 'TraCompleteStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_TraCompleteStatusEn(void);
/*! \brief Writes the bit group 'BlkGapEveStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
void GH_SDIO1_set_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn(U8 data);
/*! \brief Reads the bit group 'BlkGapEveStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn(void);
/*! \brief Writes the bit group 'DmaIntStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
void GH_SDIO1_set_BlkSizeNorIntStaEnReg_DmaIntStatusEn(U8 data);
/*! \brief Reads the bit group 'DmaIntStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_DmaIntStatusEn(void);
/*! \brief Writes the bit group 'BufWReadyStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
void GH_SDIO1_set_BlkSizeNorIntStaEnReg_BufWReadyStatusEn(U8 data);
/*! \brief Reads the bit group 'BufWReadyStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_BufWReadyStatusEn(void);
/*! \brief Writes the bit group 'BufRReadyStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
void GH_SDIO1_set_BlkSizeNorIntStaEnReg_BufRReadyStatusEn(U8 data);
/*! \brief Reads the bit group 'BufRReadyStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_BufRReadyStatusEn(void);
/*! \brief Writes the bit group 'CardInsertionStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
void GH_SDIO1_set_BlkSizeNorIntStaEnReg_CardInsertionStatusEn(U8 data);
/*! \brief Reads the bit group 'CardInsertionStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_CardInsertionStatusEn(void);
/*! \brief Writes the bit group 'CardRemStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
void GH_SDIO1_set_BlkSizeNorIntStaEnReg_CardRemStatusEn(U8 data);
/*! \brief Reads the bit group 'CardRemStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_CardRemStatusEn(void);
/*! \brief Writes the bit group 'CardIntStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
void GH_SDIO1_set_BlkSizeNorIntStaEnReg_CardIntStatusEn(U8 data);
/*! \brief Reads the bit group 'CardIntStatusEn' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_CardIntStatusEn(void);
/*! \brief Writes the bit group 'FixedTo0' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
void GH_SDIO1_set_BlkSizeNorIntStaEnReg_FixedTo0(U8 data);
/*! \brief Reads the bit group 'FixedTo0' of register 'SDIO1_BlkSizeNorIntStaEnReg'. */
U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_FixedTo0(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO1_set_BlkSizeNorIntStaEnReg(U32 data)
{
    *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG = data;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_BlkSizeNorIntStaEnReg] <-- 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO1_get_BlkSizeNorIntStaEnReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_BlkSizeNorIntStaEnReg] --> 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO1_set_BlkSizeNorIntStaEnReg_TraBlkSize(U16 data)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG;
    d.bitc.trablksize = data;
    *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_BlkSizeNorIntStaEnReg_TraBlkSize] <-- 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_SDIO1_get_BlkSizeNorIntStaEnReg_TraBlkSize(void)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_BlkSizeNorIntStaEnReg_TraBlkSize] --> 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.trablksize;
}
GH_INLINE void GH_SDIO1_set_BlkSizeNorIntStaEnReg_HostSdmaBufSize(U8 data)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG;
    d.bitc.hostsdmabufsize = data;
    *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_BlkSizeNorIntStaEnReg_HostSdmaBufSize] <-- 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_HostSdmaBufSize(void)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_BlkSizeNorIntStaEnReg_HostSdmaBufSize] --> 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.hostsdmabufsize;
}
GH_INLINE void GH_SDIO1_set_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn(U8 data)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG;
    d.bitc.cmdcompletestatusen = data;
    *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn(void)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_BlkSizeNorIntStaEnReg_CmdCompleteStatusEn] --> 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdcompletestatusen;
}
GH_INLINE void GH_SDIO1_set_BlkSizeNorIntStaEnReg_TraCompleteStatusEn(U8 data)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG;
    d.bitc.tracompletestatusen = data;
    *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_BlkSizeNorIntStaEnReg_TraCompleteStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_TraCompleteStatusEn(void)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_BlkSizeNorIntStaEnReg_TraCompleteStatusEn] --> 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.tracompletestatusen;
}
GH_INLINE void GH_SDIO1_set_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn(U8 data)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG;
    d.bitc.blkgapevestatusen = data;
    *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn(void)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_BlkSizeNorIntStaEnReg_BlkGapEveStatusEn] --> 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.blkgapevestatusen;
}
GH_INLINE void GH_SDIO1_set_BlkSizeNorIntStaEnReg_DmaIntStatusEn(U8 data)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG;
    d.bitc.dmaintstatusen = data;
    *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_BlkSizeNorIntStaEnReg_DmaIntStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_DmaIntStatusEn(void)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_BlkSizeNorIntStaEnReg_DmaIntStatusEn] --> 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.dmaintstatusen;
}
GH_INLINE void GH_SDIO1_set_BlkSizeNorIntStaEnReg_BufWReadyStatusEn(U8 data)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG;
    d.bitc.bufwreadystatusen = data;
    *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_BlkSizeNorIntStaEnReg_BufWReadyStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_BufWReadyStatusEn(void)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_BlkSizeNorIntStaEnReg_BufWReadyStatusEn] --> 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.bufwreadystatusen;
}
GH_INLINE void GH_SDIO1_set_BlkSizeNorIntStaEnReg_BufRReadyStatusEn(U8 data)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG;
    d.bitc.bufrreadystatusen = data;
    *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_BlkSizeNorIntStaEnReg_BufRReadyStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_BufRReadyStatusEn(void)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_BlkSizeNorIntStaEnReg_BufRReadyStatusEn] --> 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.bufrreadystatusen;
}
GH_INLINE void GH_SDIO1_set_BlkSizeNorIntStaEnReg_CardInsertionStatusEn(U8 data)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG;
    d.bitc.cardinsertionstatusen = data;
    *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_BlkSizeNorIntStaEnReg_CardInsertionStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_CardInsertionStatusEn(void)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_BlkSizeNorIntStaEnReg_CardInsertionStatusEn] --> 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardinsertionstatusen;
}
GH_INLINE void GH_SDIO1_set_BlkSizeNorIntStaEnReg_CardRemStatusEn(U8 data)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG;
    d.bitc.cardremstatusen = data;
    *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_BlkSizeNorIntStaEnReg_CardRemStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_CardRemStatusEn(void)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_BlkSizeNorIntStaEnReg_CardRemStatusEn] --> 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardremstatusen;
}
GH_INLINE void GH_SDIO1_set_BlkSizeNorIntStaEnReg_CardIntStatusEn(U8 data)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG;
    d.bitc.cardintstatusen = data;
    *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_BlkSizeNorIntStaEnReg_CardIntStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_CardIntStatusEn(void)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_BlkSizeNorIntStaEnReg_CardIntStatusEn] --> 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardintstatusen;
}
GH_INLINE void GH_SDIO1_set_BlkSizeNorIntStaEnReg_FixedTo0(U8 data)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG;
    d.bitc.fixedto0 = data;
    *(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_BlkSizeNorIntStaEnReg_FixedTo0] <-- 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_BlkSizeNorIntStaEnReg_FixedTo0(void)
{
    GH_SDIO1_BLKSIZENORINTSTAENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_BLKSIZENORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_BlkSizeNorIntStaEnReg_FixedTo0] --> 0x%08x\n",
                        REG_SDIO1_BLKSIZENORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.fixedto0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_ErrIntStaEnNorIntStaReg (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg(U32 data);
/*! \brief Reads the register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U32  GH_SDIO1_get_ErrIntStaEnNorIntStaReg(void);
/*! \brief Writes the bit group 'CmdTimeoutErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn(U8 data);
/*! \brief Reads the bit group 'CmdTimeoutErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn(void);
/*! \brief Writes the bit group 'CmdEndBitErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn(U8 data);
/*! \brief Reads the bit group 'CmdEndBitErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn(void);
/*! \brief Writes the bit group 'CmdCrcErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn(U8 data);
/*! \brief Reads the bit group 'CmdCrcErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn(void);
/*! \brief Writes the bit group 'CmdIndexErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn(U8 data);
/*! \brief Reads the bit group 'CmdIndexErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn(void);
/*! \brief Writes the bit group 'DataCrcErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn(U8 data);
/*! \brief Reads the bit group 'DataCrcErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn(void);
/*! \brief Writes the bit group 'DataTimeoutErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn(U8 data);
/*! \brief Reads the bit group 'DataTimeoutErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn(void);
/*! \brief Writes the bit group 'DataEndBitErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn(U8 data);
/*! \brief Reads the bit group 'DataEndBitErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn(void);
/*! \brief Writes the bit group 'CurLimitErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn(U8 data);
/*! \brief Reads the bit group 'CurLimitErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn(void);
/*! \brief Writes the bit group 'AutoCmd12ErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn(U8 data);
/*! \brief Reads the bit group 'AutoCmd12ErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn(void);
/*! \brief Writes the bit group 'VendorSpecificErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn(U8 data);
/*! \brief Reads the bit group 'VendorSpecificErrStatusEn' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn(void);
/*! \brief Writes the bit group 'CmdComplete' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdComplete(U8 data);
/*! \brief Reads the bit group 'CmdComplete' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdComplete(void);
/*! \brief Writes the bit group 'BlkGapEvent' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BlkGapEvent(U8 data);
/*! \brief Reads the bit group 'BlkGapEvent' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BlkGapEvent(void);
/*! \brief Writes the bit group 'DmaInt' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DmaInt(U8 data);
/*! \brief Reads the bit group 'DmaInt' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DmaInt(void);
/*! \brief Writes the bit group 'TraComplete' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_TraComplete(U8 data);
/*! \brief Reads the bit group 'TraComplete' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_TraComplete(void);
/*! \brief Writes the bit group 'BufWReady' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BufWReady(U8 data);
/*! \brief Reads the bit group 'BufWReady' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BufWReady(void);
/*! \brief Writes the bit group 'CardInsertion' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CardInsertion(U8 data);
/*! \brief Reads the bit group 'CardInsertion' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CardInsertion(void);
/*! \brief Writes the bit group 'BufRReady' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BufRReady(U8 data);
/*! \brief Reads the bit group 'BufRReady' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BufRReady(void);
/*! \brief Writes the bit group 'CardRemoval' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CardRemoval(U8 data);
/*! \brief Reads the bit group 'CardRemoval' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CardRemoval(void);
/*! \brief Writes the bit group 'CardInt' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CardInt(U8 data);
/*! \brief Reads the bit group 'CardInt' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CardInt(void);
/*! \brief Writes the bit group 'BootAckRcv' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BootAckRcv(U8 data);
/*! \brief Reads the bit group 'BootAckRcv' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BootAckRcv(void);
/*! \brief Writes the bit group 'ErrInt' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_ErrInt(U8 data);
/*! \brief Reads the bit group 'ErrInt' of register 'SDIO1_ErrIntStaEnNorIntStaReg'. */
U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_ErrInt(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg(U32 data)
{
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = data;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO1_get_ErrIntStaEnNorIntStaReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.cmdtimeouterrstatusen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdTimeoutErrStatusEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdtimeouterrstatusen;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.cmdendbiterrstatusen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdEndBitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdendbiterrstatusen;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.cmdcrcerrstatusen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdCrcErrStatusEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdcrcerrstatusen;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.cmdindexerrstatusen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdIndexErrStatusEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdindexerrstatusen;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.datacrcerrstatusen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DataCrcErrStatusEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.datacrcerrstatusen;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.datatimeouterrstatusen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DataTimeoutErrStatusEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.datatimeouterrstatusen;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.dataendbiterrstatusen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DataEndBitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.dataendbiterrstatusen;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.curlimiterrstatusen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CurLimitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.curlimiterrstatusen;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.autocmd12errstatusen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_AutoCmd12ErrStatusEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.autocmd12errstatusen;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.vendorspecificerrstatusen = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_VendorSpecificErrStatusEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.vendorspecificerrstatusen;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdComplete(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.cmdcomplete = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CmdComplete] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdComplete(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CmdComplete] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdcomplete;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BlkGapEvent(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.blkgapevent = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BlkGapEvent] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BlkGapEvent(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BlkGapEvent] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.blkgapevent;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DmaInt(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.dmaint = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_DmaInt] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DmaInt(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_DmaInt] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.dmaint;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_TraComplete(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.tracomplete = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_TraComplete] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_TraComplete(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_TraComplete] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.tracomplete;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BufWReady(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.bufwready = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BufWReady] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BufWReady(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BufWReady] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bufwready;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CardInsertion(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.cardinsertion = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CardInsertion] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CardInsertion(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CardInsertion] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardinsertion;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BufRReady(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.bufrready = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BufRReady] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BufRReady(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BufRReady] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bufrready;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CardRemoval(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.cardremoval = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CardRemoval] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CardRemoval(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CardRemoval] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardremoval;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CardInt(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.cardint = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_CardInt] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CardInt(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_CardInt] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardint;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BootAckRcv(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.bootackrcv = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_BootAckRcv] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BootAckRcv(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_BootAckRcv] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bootackrcv;
}
GH_INLINE void GH_SDIO1_set_ErrIntStaEnNorIntStaReg_ErrInt(U8 data)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG;
    d.bitc.errint = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStaEnNorIntStaReg_ErrInt] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStaEnNorIntStaReg_ErrInt(void)
{
    GH_SDIO1_ERRINTSTAENNORINTSTAREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTAENNORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStaEnNorIntStaReg_ErrInt] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTAENNORINTSTAREG,value);
    #endif
    return tmp_value.bitc.errint;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_ErrIntStatusCommondReg (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg(U32 data);
/*! \brief Reads the register 'SDIO1_ErrIntStatusCommondReg'. */
U32  GH_SDIO1_get_ErrIntStatusCommondReg(void);
/*! \brief Writes the bit group 'CmdTimeoutErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_CmdTimeoutErr(U8 data);
/*! \brief Reads the bit group 'CmdTimeoutErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdTimeoutErr(void);
/*! \brief Writes the bit group 'CmdCrcErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_CmdCrcErr(U8 data);
/*! \brief Reads the bit group 'CmdCrcErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdCrcErr(void);
/*! \brief Writes the bit group 'CmdEndBitErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_CmdEndBitErr(U8 data);
/*! \brief Reads the bit group 'CmdEndBitErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdEndBitErr(void);
/*! \brief Writes the bit group 'CmdIndexErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_CmdIndexErr(U8 data);
/*! \brief Reads the bit group 'CmdIndexErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdIndexErr(void);
/*! \brief Writes the bit group 'DataTimeoutErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_DataTimeoutErr(U8 data);
/*! \brief Reads the bit group 'DataTimeoutErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_DataTimeoutErr(void);
/*! \brief Writes the bit group 'DataCrcErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_DataCrcErr(U8 data);
/*! \brief Reads the bit group 'DataCrcErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_DataCrcErr(void);
/*! \brief Writes the bit group 'DataEndBitErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_DataEndBitErr(U8 data);
/*! \brief Reads the bit group 'DataEndBitErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_DataEndBitErr(void);
/*! \brief Writes the bit group 'CurLimitErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_CurLimitErr(U8 data);
/*! \brief Reads the bit group 'CurLimitErr' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_CurLimitErr(void);
/*! \brief Writes the bit group 'AutoCmd12Err' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_AutoCmd12Err(U8 data);
/*! \brief Reads the bit group 'AutoCmd12Err' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_AutoCmd12Err(void);
/*! \brief Writes the bit group 'VendorSpecificErrStatus' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_VendorSpecificErrStatus(U8 data);
/*! \brief Reads the bit group 'VendorSpecificErrStatus' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_VendorSpecificErrStatus(void);
/*! \brief Writes the bit group 'RepTypeSelect' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_RepTypeSelect(U8 data);
/*! \brief Reads the bit group 'RepTypeSelect' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_RepTypeSelect(void);
/*! \brief Writes the bit group 'CmdCrcCheckEn' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_CmdCrcCheckEn(U8 data);
/*! \brief Reads the bit group 'CmdCrcCheckEn' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdCrcCheckEn(void);
/*! \brief Writes the bit group 'DataPreSelect' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_DataPreSelect(U8 data);
/*! \brief Reads the bit group 'DataPreSelect' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_DataPreSelect(void);
/*! \brief Writes the bit group 'CmdIndexCheckEn' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_CmdIndexCheckEn(U8 data);
/*! \brief Reads the bit group 'CmdIndexCheckEn' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdIndexCheckEn(void);
/*! \brief Writes the bit group 'CmdType' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_CmdType(U8 data);
/*! \brief Reads the bit group 'CmdType' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdType(void);
/*! \brief Writes the bit group 'CmdIndex' of register 'SDIO1_ErrIntStatusCommondReg'. */
void GH_SDIO1_set_ErrIntStatusCommondReg_CmdIndex(U8 data);
/*! \brief Reads the bit group 'CmdIndex' of register 'SDIO1_ErrIntStatusCommondReg'. */
U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdIndex(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg(U32 data)
{
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = data;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO1_get_ErrIntStatusCommondReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_CmdTimeoutErr(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdtimeouterr = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_CmdTimeoutErr] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdTimeoutErr(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_CmdTimeoutErr] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdtimeouterr;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_CmdCrcErr(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdcrcerr = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_CmdCrcErr] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdCrcErr(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_CmdCrcErr] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdcrcerr;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_CmdEndBitErr(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdendbiterr = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_CmdEndBitErr] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdEndBitErr(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_CmdEndBitErr] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdendbiterr;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_CmdIndexErr(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdindexerr = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_CmdIndexErr] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdIndexErr(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_CmdIndexErr] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdindexerr;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_DataTimeoutErr(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.datatimeouterr = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_DataTimeoutErr] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_DataTimeoutErr(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_DataTimeoutErr] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.datatimeouterr;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_DataCrcErr(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.datacrcerr = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_DataCrcErr] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_DataCrcErr(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_DataCrcErr] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.datacrcerr;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_DataEndBitErr(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.dataendbiterr = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_DataEndBitErr] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_DataEndBitErr(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_DataEndBitErr] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.dataendbiterr;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_CurLimitErr(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.curlimiterr = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_CurLimitErr] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_CurLimitErr(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_CurLimitErr] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.curlimiterr;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_AutoCmd12Err(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.autocmd12err = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_AutoCmd12Err] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_AutoCmd12Err(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_AutoCmd12Err] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.autocmd12err;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_VendorSpecificErrStatus(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.vendorspecificerrstatus = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_VendorSpecificErrStatus] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_VendorSpecificErrStatus(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_VendorSpecificErrStatus] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.vendorspecificerrstatus;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_RepTypeSelect(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.reptypeselect = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_RepTypeSelect] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_RepTypeSelect(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_RepTypeSelect] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.reptypeselect;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_CmdCrcCheckEn(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdcrcchecken = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_CmdCrcCheckEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdCrcCheckEn(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_CmdCrcCheckEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdcrcchecken;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_DataPreSelect(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.datapreselect = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_DataPreSelect] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_DataPreSelect(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_DataPreSelect] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.datapreselect;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_CmdIndexCheckEn(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdindexchecken = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_CmdIndexCheckEn] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdIndexCheckEn(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_CmdIndexCheckEn] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdindexchecken;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_CmdType(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdtype = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_CmdType] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdType(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_CmdType] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdtype;
}
GH_INLINE void GH_SDIO1_set_ErrIntStatusCommondReg_CmdIndex(U8 data)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG;
    d.bitc.cmdindex = data;
    *(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ErrIntStatusCommondReg_CmdIndex] <-- 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_ErrIntStatusCommondReg_CmdIndex(void)
{
    GH_SDIO1_ERRINTSTATUSCOMMONDREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_ERRINTSTATUSCOMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ErrIntStatusCommondReg_CmdIndex] --> 0x%08x\n",
                        REG_SDIO1_ERRINTSTATUSCOMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdindex;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_Control01Reg (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO1_Control01Reg'. */
void GH_SDIO1_set_Control01Reg(U32 data);
/*! \brief Reads the register 'SDIO1_Control01Reg'. */
U32  GH_SDIO1_get_Control01Reg(void);
/*! \brief Writes the bit group 'DataTimeoutCounterValue' of register 'SDIO1_Control01Reg'. */
void GH_SDIO1_set_Control01Reg_DataTimeoutCounterValue(U8 data);
/*! \brief Reads the bit group 'DataTimeoutCounterValue' of register 'SDIO1_Control01Reg'. */
U8   GH_SDIO1_get_Control01Reg_DataTimeoutCounterValue(void);
/*! \brief Writes the bit group 'SoftwareResetCmdLine' of register 'SDIO1_Control01Reg'. */
void GH_SDIO1_set_Control01Reg_SoftwareResetCmdLine(U8 data);
/*! \brief Reads the bit group 'SoftwareResetCmdLine' of register 'SDIO1_Control01Reg'. */
U8   GH_SDIO1_get_Control01Reg_SoftwareResetCmdLine(void);
/*! \brief Writes the bit group 'SoftwareResetAll' of register 'SDIO1_Control01Reg'. */
void GH_SDIO1_set_Control01Reg_SoftwareResetAll(U8 data);
/*! \brief Reads the bit group 'SoftwareResetAll' of register 'SDIO1_Control01Reg'. */
U8   GH_SDIO1_get_Control01Reg_SoftwareResetAll(void);
/*! \brief Writes the bit group 'SoftwareResetDatLine' of register 'SDIO1_Control01Reg'. */
void GH_SDIO1_set_Control01Reg_SoftwareResetDatLine(U8 data);
/*! \brief Reads the bit group 'SoftwareResetDatLine' of register 'SDIO1_Control01Reg'. */
U8   GH_SDIO1_get_Control01Reg_SoftwareResetDatLine(void);
/*! \brief Writes the bit group 'InternalClkEn' of register 'SDIO1_Control01Reg'. */
void GH_SDIO1_set_Control01Reg_InternalClkEn(U8 data);
/*! \brief Reads the bit group 'InternalClkEn' of register 'SDIO1_Control01Reg'. */
U8   GH_SDIO1_get_Control01Reg_InternalClkEn(void);
/*! \brief Writes the bit group 'InternalClkStable' of register 'SDIO1_Control01Reg'. */
void GH_SDIO1_set_Control01Reg_InternalClkStable(U8 data);
/*! \brief Reads the bit group 'InternalClkStable' of register 'SDIO1_Control01Reg'. */
U8   GH_SDIO1_get_Control01Reg_InternalClkStable(void);
/*! \brief Writes the bit group 'SdClkEn' of register 'SDIO1_Control01Reg'. */
void GH_SDIO1_set_Control01Reg_SdClkEn(U8 data);
/*! \brief Reads the bit group 'SdClkEn' of register 'SDIO1_Control01Reg'. */
U8   GH_SDIO1_get_Control01Reg_SdClkEn(void);
/*! \brief Writes the bit group 'SdclkFreSelect' of register 'SDIO1_Control01Reg'. */
void GH_SDIO1_set_Control01Reg_SdclkFreSelect(U8 data);
/*! \brief Reads the bit group 'SdclkFreSelect' of register 'SDIO1_Control01Reg'. */
U8   GH_SDIO1_get_Control01Reg_SdclkFreSelect(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO1_set_Control01Reg(U32 data)
{
    *(volatile U32 *)REG_SDIO1_CONTROL01REG = data;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control01Reg] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO1_get_Control01Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL01REG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control01Reg] --> 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO1_set_Control01Reg_DataTimeoutCounterValue(U8 data)
{
    GH_SDIO1_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL01REG;
    d.bitc.datatimeoutcountervalue = data;
    *(volatile U32 *)REG_SDIO1_CONTROL01REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control01Reg_DataTimeoutCounterValue] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control01Reg_DataTimeoutCounterValue(void)
{
    GH_SDIO1_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control01Reg_DataTimeoutCounterValue] --> 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.datatimeoutcountervalue;
}
GH_INLINE void GH_SDIO1_set_Control01Reg_SoftwareResetCmdLine(U8 data)
{
    GH_SDIO1_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL01REG;
    d.bitc.softwareresetcmdline = data;
    *(volatile U32 *)REG_SDIO1_CONTROL01REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control01Reg_SoftwareResetCmdLine] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control01Reg_SoftwareResetCmdLine(void)
{
    GH_SDIO1_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control01Reg_SoftwareResetCmdLine] --> 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.softwareresetcmdline;
}
GH_INLINE void GH_SDIO1_set_Control01Reg_SoftwareResetAll(U8 data)
{
    GH_SDIO1_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL01REG;
    d.bitc.softwareresetall = data;
    *(volatile U32 *)REG_SDIO1_CONTROL01REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control01Reg_SoftwareResetAll] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control01Reg_SoftwareResetAll(void)
{
    GH_SDIO1_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control01Reg_SoftwareResetAll] --> 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.softwareresetall;
}
GH_INLINE void GH_SDIO1_set_Control01Reg_SoftwareResetDatLine(U8 data)
{
    GH_SDIO1_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL01REG;
    d.bitc.softwareresetdatline = data;
    *(volatile U32 *)REG_SDIO1_CONTROL01REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control01Reg_SoftwareResetDatLine] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control01Reg_SoftwareResetDatLine(void)
{
    GH_SDIO1_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control01Reg_SoftwareResetDatLine] --> 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.softwareresetdatline;
}
GH_INLINE void GH_SDIO1_set_Control01Reg_InternalClkEn(U8 data)
{
    GH_SDIO1_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL01REG;
    d.bitc.internalclken = data;
    *(volatile U32 *)REG_SDIO1_CONTROL01REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control01Reg_InternalClkEn] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control01Reg_InternalClkEn(void)
{
    GH_SDIO1_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control01Reg_InternalClkEn] --> 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.internalclken;
}
GH_INLINE void GH_SDIO1_set_Control01Reg_InternalClkStable(U8 data)
{
    GH_SDIO1_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL01REG;
    d.bitc.internalclkstable = data;
    *(volatile U32 *)REG_SDIO1_CONTROL01REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control01Reg_InternalClkStable] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control01Reg_InternalClkStable(void)
{
    GH_SDIO1_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control01Reg_InternalClkStable] --> 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.internalclkstable;
}
GH_INLINE void GH_SDIO1_set_Control01Reg_SdClkEn(U8 data)
{
    GH_SDIO1_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL01REG;
    d.bitc.sdclken = data;
    *(volatile U32 *)REG_SDIO1_CONTROL01REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control01Reg_SdClkEn] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control01Reg_SdClkEn(void)
{
    GH_SDIO1_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control01Reg_SdClkEn] --> 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.sdclken;
}
GH_INLINE void GH_SDIO1_set_Control01Reg_SdclkFreSelect(U8 data)
{
    GH_SDIO1_CONTROL01REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL01REG;
    d.bitc.sdclkfreselect = data;
    *(volatile U32 *)REG_SDIO1_CONTROL01REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control01Reg_SdclkFreSelect] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control01Reg_SdclkFreSelect(void)
{
    GH_SDIO1_CONTROL01REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL01REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control01Reg_SdclkFreSelect] --> 0x%08x\n",
                        REG_SDIO1_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.sdclkfreselect;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_Resp0Reg (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SDIO1_Resp0Reg'. */
U32  GH_SDIO1_get_Resp0Reg(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO1_get_Resp0Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_RESP0REG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Resp0Reg] --> 0x%08x\n",
                        REG_SDIO1_RESP0REG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_Resp1Reg (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SDIO1_Resp1Reg'. */
U32  GH_SDIO1_get_Resp1Reg(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO1_get_Resp1Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_RESP1REG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Resp1Reg] --> 0x%08x\n",
                        REG_SDIO1_RESP1REG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_Resp2Reg (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SDIO1_Resp2Reg'. */
U32  GH_SDIO1_get_Resp2Reg(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO1_get_Resp2Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_RESP2REG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Resp2Reg] --> 0x%08x\n",
                        REG_SDIO1_RESP2REG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_Resp3Reg (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SDIO1_Resp3Reg'. */
U32  GH_SDIO1_get_Resp3Reg(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO1_get_Resp3Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_RESP3REG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Resp3Reg] --> 0x%08x\n",
                        REG_SDIO1_RESP3REG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_Control00Reg (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg(U32 data);
/*! \brief Reads the register 'SDIO1_Control00Reg'. */
U32  GH_SDIO1_get_Control00Reg(void);
/*! \brief Writes the bit group 'LedControl' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_LedControl(U8 data);
/*! \brief Reads the bit group 'LedControl' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_LedControl(void);
/*! \brief Writes the bit group 'DataTraWidth' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_DataTraWidth(U8 data);
/*! \brief Reads the bit group 'DataTraWidth' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_DataTraWidth(void);
/*! \brief Writes the bit group 'Sd8BitMode' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_Sd8BitMode(U8 data);
/*! \brief Reads the bit group 'Sd8BitMode' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_Sd8BitMode(void);
/*! \brief Writes the bit group 'HostSpeedEn' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_HostSpeedEn(U8 data);
/*! \brief Reads the bit group 'HostSpeedEn' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_HostSpeedEn(void);
/*! \brief Writes the bit group 'CardDetectTestLevel' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_CardDetectTestLevel(U8 data);
/*! \brief Reads the bit group 'CardDetectTestLevel' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_CardDetectTestLevel(void);
/*! \brief Writes the bit group 'CardDetectSigDet' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_CardDetectSigDet(U8 data);
/*! \brief Reads the bit group 'CardDetectSigDet' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_CardDetectSigDet(void);
/*! \brief Writes the bit group 'SdBusPower' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_SdBusPower(U8 data);
/*! \brief Reads the bit group 'SdBusPower' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_SdBusPower(void);
/*! \brief Writes the bit group 'SdBusVoltageSelect' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_SdBusVoltageSelect(U8 data);
/*! \brief Reads the bit group 'SdBusVoltageSelect' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_SdBusVoltageSelect(void);
/*! \brief Writes the bit group 'StopAtBlkGapReq' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_StopAtBlkGapReq(U8 data);
/*! \brief Reads the bit group 'StopAtBlkGapReq' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_StopAtBlkGapReq(void);
/*! \brief Writes the bit group 'RWaitControl' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_RWaitControl(U8 data);
/*! \brief Reads the bit group 'RWaitControl' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_RWaitControl(void);
/*! \brief Writes the bit group 'ContinueReq' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_ContinueReq(U8 data);
/*! \brief Reads the bit group 'ContinueReq' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_ContinueReq(void);
/*! \brief Writes the bit group 'IntAtBlkGap' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_IntAtBlkGap(U8 data);
/*! \brief Reads the bit group 'IntAtBlkGap' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_IntAtBlkGap(void);
/*! \brief Writes the bit group 'DriveCcsd' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_DriveCcsd(U8 data);
/*! \brief Reads the bit group 'DriveCcsd' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_DriveCcsd(void);
/*! \brief Writes the bit group 'SpiMode' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_SpiMode(U8 data);
/*! \brief Reads the bit group 'SpiMode' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_SpiMode(void);
/*! \brief Writes the bit group 'BootEn' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_BootEn(U8 data);
/*! \brief Reads the bit group 'BootEn' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_BootEn(void);
/*! \brief Writes the bit group 'AltBootEn' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_AltBootEn(U8 data);
/*! \brief Reads the bit group 'AltBootEn' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_AltBootEn(void);
/*! \brief Writes the bit group 'WakeupEvetEnOnCardIns' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardIns(U8 data);
/*! \brief Reads the bit group 'WakeupEvetEnOnCardIns' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardIns(void);
/*! \brief Writes the bit group 'WakeupEvetEnOnCardInt' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardInt(U8 data);
/*! \brief Reads the bit group 'WakeupEvetEnOnCardInt' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardInt(void);
/*! \brief Writes the bit group 'WakeupEvetEnOnCardRem' of register 'SDIO1_Control00Reg'. */
void GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardRem(U8 data);
/*! \brief Reads the bit group 'WakeupEvetEnOnCardRem' of register 'SDIO1_Control00Reg'. */
U8   GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardRem(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO1_set_Control00Reg(U32 data)
{
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = data;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO1_get_Control00Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_LedControl(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.ledcontrol = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_LedControl] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_LedControl(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_LedControl] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.ledcontrol;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_DataTraWidth(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.datatrawidth = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_DataTraWidth] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_DataTraWidth(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_DataTraWidth] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.datatrawidth;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_Sd8BitMode(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.sd8bitmode = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_Sd8BitMode] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_Sd8BitMode(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_Sd8BitMode] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.sd8bitmode;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_HostSpeedEn(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.hostspeeden = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_HostSpeedEn] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_HostSpeedEn(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_HostSpeedEn] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.hostspeeden;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_CardDetectTestLevel(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.carddetecttestlevel = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_CardDetectTestLevel] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_CardDetectTestLevel(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_CardDetectTestLevel] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.carddetecttestlevel;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_CardDetectSigDet(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.carddetectsigdet = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_CardDetectSigDet] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_CardDetectSigDet(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_CardDetectSigDet] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.carddetectsigdet;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_SdBusPower(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.sdbuspower = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_SdBusPower] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_SdBusPower(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_SdBusPower] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.sdbuspower;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_SdBusVoltageSelect(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.sdbusvoltageselect = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_SdBusVoltageSelect] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_SdBusVoltageSelect(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_SdBusVoltageSelect] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.sdbusvoltageselect;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_StopAtBlkGapReq(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.stopatblkgapreq = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_StopAtBlkGapReq] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_StopAtBlkGapReq(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_StopAtBlkGapReq] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.stopatblkgapreq;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_RWaitControl(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.rwaitcontrol = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_RWaitControl] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_RWaitControl(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_RWaitControl] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.rwaitcontrol;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_ContinueReq(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.continuereq = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_ContinueReq] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_ContinueReq(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_ContinueReq] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.continuereq;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_IntAtBlkGap(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.intatblkgap = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_IntAtBlkGap] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_IntAtBlkGap(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_IntAtBlkGap] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.intatblkgap;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_DriveCcsd(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.driveccsd = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_DriveCcsd] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_DriveCcsd(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_DriveCcsd] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.driveccsd;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_SpiMode(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.spimode = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_SpiMode] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_SpiMode(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_SpiMode] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.spimode;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_BootEn(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.booten = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_BootEn] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_BootEn(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_BootEn] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.booten;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_AltBootEn(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.altbooten = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_AltBootEn] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_AltBootEn(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_AltBootEn] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.altbooten;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardIns(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.wakeupevetenoncardins = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardIns] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardIns(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardIns] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.wakeupevetenoncardins;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardInt(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.wakeupevetenoncardint = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardInt] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardInt(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardInt] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.wakeupevetenoncardint;
}
GH_INLINE void GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardRem(U8 data)
{
    GH_SDIO1_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_CONTROL00REG;
    d.bitc.wakeupevetenoncardrem = data;
    *(volatile U32 *)REG_SDIO1_CONTROL00REG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_Control00Reg_WakeupEvetEnOnCardRem] <-- 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardRem(void)
{
    GH_SDIO1_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_Control00Reg_WakeupEvetEnOnCardRem] --> 0x%08x\n",
                        REG_SDIO1_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.wakeupevetenoncardrem;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_PresentStateReg (read)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SDIO1_PresentStateReg'. */
U32  GH_SDIO1_get_PresentStateReg(void);
/*! \brief Reads the bit group 'CmdInhibitCmd' of register 'SDIO1_PresentStateReg'. */
U8   GH_SDIO1_get_PresentStateReg_CmdInhibitCmd(void);
/*! \brief Reads the bit group 'DataLineActive' of register 'SDIO1_PresentStateReg'. */
U8   GH_SDIO1_get_PresentStateReg_DataLineActive(void);
/*! \brief Reads the bit group 'CmdInhibitData' of register 'SDIO1_PresentStateReg'. */
U8   GH_SDIO1_get_PresentStateReg_CmdInhibitData(void);
/*! \brief Reads the bit group 'RTraActive' of register 'SDIO1_PresentStateReg'. */
U8   GH_SDIO1_get_PresentStateReg_RTraActive(void);
/*! \brief Reads the bit group 'BufWEn' of register 'SDIO1_PresentStateReg'. */
U8   GH_SDIO1_get_PresentStateReg_BufWEn(void);
/*! \brief Reads the bit group 'WTraActive' of register 'SDIO1_PresentStateReg'. */
U8   GH_SDIO1_get_PresentStateReg_WTraActive(void);
/*! \brief Reads the bit group 'BufREn' of register 'SDIO1_PresentStateReg'. */
U8   GH_SDIO1_get_PresentStateReg_BufREn(void);
/*! \brief Reads the bit group 'CardInserted' of register 'SDIO1_PresentStateReg'. */
U8   GH_SDIO1_get_PresentStateReg_CardInserted(void);
/*! \brief Reads the bit group 'CardDetectPinLevel' of register 'SDIO1_PresentStateReg'. */
U8   GH_SDIO1_get_PresentStateReg_CardDetectPinLevel(void);
/*! \brief Reads the bit group 'CardStateStable' of register 'SDIO1_PresentStateReg'. */
U8   GH_SDIO1_get_PresentStateReg_CardStateStable(void);
/*! \brief Reads the bit group 'WProSwiPinLevel' of register 'SDIO1_PresentStateReg'. */
U8   GH_SDIO1_get_PresentStateReg_WProSwiPinLevel(void);
/*! \brief Reads the bit group 'Data03LineSigLevel' of register 'SDIO1_PresentStateReg'. */
U8   GH_SDIO1_get_PresentStateReg_Data03LineSigLevel(void);
/*! \brief Reads the bit group 'CmdLineSigLevel' of register 'SDIO1_PresentStateReg'. */
U8   GH_SDIO1_get_PresentStateReg_CmdLineSigLevel(void);
/*! \brief Reads the bit group 'Data47LineSigLevel' of register 'SDIO1_PresentStateReg'. */
U8   GH_SDIO1_get_PresentStateReg_Data47LineSigLevel(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO1_get_PresentStateReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SDIO1_get_PresentStateReg_CmdInhibitCmd(void)
{
    GH_SDIO1_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg_CmdInhibitCmd] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cmdinhibitcmd;
}
GH_INLINE U8   GH_SDIO1_get_PresentStateReg_DataLineActive(void)
{
    GH_SDIO1_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg_DataLineActive] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.datalineactive;
}
GH_INLINE U8   GH_SDIO1_get_PresentStateReg_CmdInhibitData(void)
{
    GH_SDIO1_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg_CmdInhibitData] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cmdinhibitdata;
}
GH_INLINE U8   GH_SDIO1_get_PresentStateReg_RTraActive(void)
{
    GH_SDIO1_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg_RTraActive] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.rtraactive;
}
GH_INLINE U8   GH_SDIO1_get_PresentStateReg_BufWEn(void)
{
    GH_SDIO1_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg_BufWEn] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.bufwen;
}
GH_INLINE U8   GH_SDIO1_get_PresentStateReg_WTraActive(void)
{
    GH_SDIO1_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg_WTraActive] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.wtraactive;
}
GH_INLINE U8   GH_SDIO1_get_PresentStateReg_BufREn(void)
{
    GH_SDIO1_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg_BufREn] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.bufren;
}
GH_INLINE U8   GH_SDIO1_get_PresentStateReg_CardInserted(void)
{
    GH_SDIO1_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg_CardInserted] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cardinserted;
}
GH_INLINE U8   GH_SDIO1_get_PresentStateReg_CardDetectPinLevel(void)
{
    GH_SDIO1_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg_CardDetectPinLevel] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.carddetectpinlevel;
}
GH_INLINE U8   GH_SDIO1_get_PresentStateReg_CardStateStable(void)
{
    GH_SDIO1_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg_CardStateStable] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cardstatestable;
}
GH_INLINE U8   GH_SDIO1_get_PresentStateReg_WProSwiPinLevel(void)
{
    GH_SDIO1_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg_WProSwiPinLevel] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.wproswipinlevel;
}
GH_INLINE U8   GH_SDIO1_get_PresentStateReg_Data03LineSigLevel(void)
{
    GH_SDIO1_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg_Data03LineSigLevel] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.data03linesiglevel;
}
GH_INLINE U8   GH_SDIO1_get_PresentStateReg_CmdLineSigLevel(void)
{
    GH_SDIO1_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg_CmdLineSigLevel] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cmdlinesiglevel;
}
GH_INLINE U8   GH_SDIO1_get_PresentStateReg_Data47LineSigLevel(void)
{
    GH_SDIO1_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_PresentStateReg_Data47LineSigLevel] --> 0x%08x\n",
                        REG_SDIO1_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.data47linesiglevel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_ArgReg (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO1_ArgReg'. */
void GH_SDIO1_set_ArgReg(U32 data);
/*! \brief Reads the register 'SDIO1_ArgReg'. */
U32  GH_SDIO1_get_ArgReg(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO1_set_ArgReg(U32 data)
{
    *(volatile U32 *)REG_SDIO1_ARGREG = data;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_ArgReg] <-- 0x%08x\n",
                        REG_SDIO1_ARGREG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO1_get_ArgReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_ARGREG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_ArgReg] --> 0x%08x\n",
                        REG_SDIO1_ARGREG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_CapReg (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SDIO1_CapReg'. */
U32  GH_SDIO1_get_CapReg(void);
/*! \brief Reads the bit group 'TimeoutClkFre' of register 'SDIO1_CapReg'. */
U8   GH_SDIO1_get_CapReg_TimeoutClkFre(void);
/*! \brief Reads the bit group 'TimeoutClkUnit' of register 'SDIO1_CapReg'. */
U8   GH_SDIO1_get_CapReg_TimeoutClkUnit(void);
/*! \brief Reads the bit group 'BaseClkFreForSdClk' of register 'SDIO1_CapReg'. */
U8   GH_SDIO1_get_CapReg_BaseClkFreForSdClk(void);
/*! \brief Reads the bit group 'MaxBlkLen' of register 'SDIO1_CapReg'. */
U8   GH_SDIO1_get_CapReg_MaxBlkLen(void);
/*! \brief Reads the bit group 'ExtendedMediaBusSup' of register 'SDIO1_CapReg'. */
U8   GH_SDIO1_get_CapReg_ExtendedMediaBusSup(void);
/*! \brief Reads the bit group 'HighSpeedSup' of register 'SDIO1_CapReg'. */
U8   GH_SDIO1_get_CapReg_HighSpeedSup(void);
/*! \brief Reads the bit group 'SusResSup' of register 'SDIO1_CapReg'. */
U8   GH_SDIO1_get_CapReg_SusResSup(void);
/*! \brief Reads the bit group 'SdmaSup' of register 'SDIO1_CapReg'. */
U8   GH_SDIO1_get_CapReg_SdmaSup(void);
/*! \brief Reads the bit group 'VoltageSup33v' of register 'SDIO1_CapReg'. */
U8   GH_SDIO1_get_CapReg_VoltageSup33v(void);
/*! \brief Reads the bit group 'VoltageSup30v' of register 'SDIO1_CapReg'. */
U8   GH_SDIO1_get_CapReg_VoltageSup30v(void);
/*! \brief Reads the bit group 'VoltageSup18v' of register 'SDIO1_CapReg'. */
U8   GH_SDIO1_get_CapReg_VoltageSup18v(void);
/*! \brief Reads the bit group 'IntMode' of register 'SDIO1_CapReg'. */
U8   GH_SDIO1_get_CapReg_IntMode(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO1_get_CapReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_CAPREG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_CapReg] --> 0x%08x\n",
                        REG_SDIO1_CAPREG,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SDIO1_get_CapReg_TimeoutClkFre(void)
{
    GH_SDIO1_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_CapReg_TimeoutClkFre] --> 0x%08x\n",
                        REG_SDIO1_CAPREG,value);
    #endif
    return tmp_value.bitc.timeoutclkfre;
}
GH_INLINE U8   GH_SDIO1_get_CapReg_TimeoutClkUnit(void)
{
    GH_SDIO1_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_CapReg_TimeoutClkUnit] --> 0x%08x\n",
                        REG_SDIO1_CAPREG,value);
    #endif
    return tmp_value.bitc.timeoutclkunit;
}
GH_INLINE U8   GH_SDIO1_get_CapReg_BaseClkFreForSdClk(void)
{
    GH_SDIO1_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_CapReg_BaseClkFreForSdClk] --> 0x%08x\n",
                        REG_SDIO1_CAPREG,value);
    #endif
    return tmp_value.bitc.baseclkfreforsdclk;
}
GH_INLINE U8   GH_SDIO1_get_CapReg_MaxBlkLen(void)
{
    GH_SDIO1_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_CapReg_MaxBlkLen] --> 0x%08x\n",
                        REG_SDIO1_CAPREG,value);
    #endif
    return tmp_value.bitc.maxblklen;
}
GH_INLINE U8   GH_SDIO1_get_CapReg_ExtendedMediaBusSup(void)
{
    GH_SDIO1_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_CapReg_ExtendedMediaBusSup] --> 0x%08x\n",
                        REG_SDIO1_CAPREG,value);
    #endif
    return tmp_value.bitc.extendedmediabussup;
}
GH_INLINE U8   GH_SDIO1_get_CapReg_HighSpeedSup(void)
{
    GH_SDIO1_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_CapReg_HighSpeedSup] --> 0x%08x\n",
                        REG_SDIO1_CAPREG,value);
    #endif
    return tmp_value.bitc.highspeedsup;
}
GH_INLINE U8   GH_SDIO1_get_CapReg_SusResSup(void)
{
    GH_SDIO1_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_CapReg_SusResSup] --> 0x%08x\n",
                        REG_SDIO1_CAPREG,value);
    #endif
    return tmp_value.bitc.susressup;
}
GH_INLINE U8   GH_SDIO1_get_CapReg_SdmaSup(void)
{
    GH_SDIO1_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_CapReg_SdmaSup] --> 0x%08x\n",
                        REG_SDIO1_CAPREG,value);
    #endif
    return tmp_value.bitc.sdmasup;
}
GH_INLINE U8   GH_SDIO1_get_CapReg_VoltageSup33v(void)
{
    GH_SDIO1_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_CapReg_VoltageSup33v] --> 0x%08x\n",
                        REG_SDIO1_CAPREG,value);
    #endif
    return tmp_value.bitc.voltagesup33v;
}
GH_INLINE U8   GH_SDIO1_get_CapReg_VoltageSup30v(void)
{
    GH_SDIO1_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_CapReg_VoltageSup30v] --> 0x%08x\n",
                        REG_SDIO1_CAPREG,value);
    #endif
    return tmp_value.bitc.voltagesup30v;
}
GH_INLINE U8   GH_SDIO1_get_CapReg_VoltageSup18v(void)
{
    GH_SDIO1_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_CapReg_VoltageSup18v] --> 0x%08x\n",
                        REG_SDIO1_CAPREG,value);
    #endif
    return tmp_value.bitc.voltagesup18v;
}
GH_INLINE U8   GH_SDIO1_get_CapReg_IntMode(void)
{
    GH_SDIO1_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_CapReg_IntMode] --> 0x%08x\n",
                        REG_SDIO1_CAPREG,value);
    #endif
    return tmp_value.bitc.intmode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_AutoCmd12ErrStatusReg (read)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SDIO1_AutoCmd12ErrStatusReg'. */
U32  GH_SDIO1_get_AutoCmd12ErrStatusReg(void);
/*! \brief Reads the bit group 'AutoCmd12TimeoutErr' of register 'SDIO1_AutoCmd12ErrStatusReg'. */
U8   GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr(void);
/*! \brief Reads the bit group 'AutoCmd12CrcErr' of register 'SDIO1_AutoCmd12ErrStatusReg'. */
U8   GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr(void);
/*! \brief Reads the bit group 'AutoCmd12EndBitErr' of register 'SDIO1_AutoCmd12ErrStatusReg'. */
U8   GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr(void);
/*! \brief Reads the bit group 'AutoCmd12NotExe' of register 'SDIO1_AutoCmd12ErrStatusReg'. */
U8   GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe(void);
/*! \brief Reads the bit group 'AutoCmd12IndexErr' of register 'SDIO1_AutoCmd12ErrStatusReg'. */
U8   GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr(void);
/*! \brief Reads the bit group 'CmdNotIssuedByAutoCmd12Err' of register 'SDIO1_AutoCmd12ErrStatusReg'. */
U8   GH_SDIO1_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO1_get_AutoCmd12ErrStatusReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_AUTOCMD12ERRSTATUSREG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_AutoCmd12ErrStatusReg] --> 0x%08x\n",
                        REG_SDIO1_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr(void)
{
    GH_SDIO1_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr] --> 0x%08x\n",
                        REG_SDIO1_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12timeouterr;
}
GH_INLINE U8   GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr(void)
{
    GH_SDIO1_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr] --> 0x%08x\n",
                        REG_SDIO1_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12crcerr;
}
GH_INLINE U8   GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr(void)
{
    GH_SDIO1_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr] --> 0x%08x\n",
                        REG_SDIO1_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12endbiterr;
}
GH_INLINE U8   GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe(void)
{
    GH_SDIO1_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe] --> 0x%08x\n",
                        REG_SDIO1_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12notexe;
}
GH_INLINE U8   GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr(void)
{
    GH_SDIO1_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr] --> 0x%08x\n",
                        REG_SDIO1_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12indexerr;
}
GH_INLINE U8   GH_SDIO1_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err(void)
{
    GH_SDIO1_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err] --> 0x%08x\n",
                        REG_SDIO1_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.cmdnotissuedbyautocmd12err;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_BufferDataPortReg (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO1_BufferDataPortReg'. */
void GH_SDIO1_set_BufferDataPortReg(U32 data);
/*! \brief Reads the register 'SDIO1_BufferDataPortReg'. */
U32  GH_SDIO1_get_BufferDataPortReg(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO1_set_BufferDataPortReg(U32 data)
{
    *(volatile U32 *)REG_SDIO1_BUFFERDATAPORTREG = data;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_BufferDataPortReg] <-- 0x%08x\n",
                        REG_SDIO1_BUFFERDATAPORTREG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO1_get_BufferDataPortReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_BUFFERDATAPORTREG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_BufferDataPortReg] --> 0x%08x\n",
                        REG_SDIO1_BUFFERDATAPORTREG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_MaxCurCapReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO1_MaxCurCapReg'. */
void GH_SDIO1_set_MaxCurCapReg(U32 data);
/*! \brief Reads the register 'SDIO1_MaxCurCapReg'. */
U32  GH_SDIO1_get_MaxCurCapReg(void);
/*! \brief Writes the bit group 'MaxCurFor33v' of register 'SDIO1_MaxCurCapReg'. */
void GH_SDIO1_set_MaxCurCapReg_MaxCurFor33v(U8 data);
/*! \brief Reads the bit group 'MaxCurFor33v' of register 'SDIO1_MaxCurCapReg'. */
U8   GH_SDIO1_get_MaxCurCapReg_MaxCurFor33v(void);
/*! \brief Writes the bit group 'MaxCurFor30v' of register 'SDIO1_MaxCurCapReg'. */
void GH_SDIO1_set_MaxCurCapReg_MaxCurFor30v(U8 data);
/*! \brief Reads the bit group 'MaxCurFor30v' of register 'SDIO1_MaxCurCapReg'. */
U8   GH_SDIO1_get_MaxCurCapReg_MaxCurFor30v(void);
/*! \brief Writes the bit group 'MaxCurFor18v' of register 'SDIO1_MaxCurCapReg'. */
void GH_SDIO1_set_MaxCurCapReg_MaxCurFor18v(U8 data);
/*! \brief Reads the bit group 'MaxCurFor18v' of register 'SDIO1_MaxCurCapReg'. */
U8   GH_SDIO1_get_MaxCurCapReg_MaxCurFor18v(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO1_set_MaxCurCapReg(U32 data)
{
    *(volatile U32 *)REG_SDIO1_MAXCURCAPREG = data;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_MaxCurCapReg] <-- 0x%08x\n",
                        REG_SDIO1_MAXCURCAPREG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO1_get_MaxCurCapReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_MAXCURCAPREG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_MaxCurCapReg] --> 0x%08x\n",
                        REG_SDIO1_MAXCURCAPREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO1_set_MaxCurCapReg_MaxCurFor33v(U8 data)
{
    GH_SDIO1_MAXCURCAPREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_MAXCURCAPREG;
    d.bitc.maxcurfor33v = data;
    *(volatile U32 *)REG_SDIO1_MAXCURCAPREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_MaxCurCapReg_MaxCurFor33v] <-- 0x%08x\n",
                        REG_SDIO1_MAXCURCAPREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_MaxCurCapReg_MaxCurFor33v(void)
{
    GH_SDIO1_MAXCURCAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_MAXCURCAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_MaxCurCapReg_MaxCurFor33v] --> 0x%08x\n",
                        REG_SDIO1_MAXCURCAPREG,value);
    #endif
    return tmp_value.bitc.maxcurfor33v;
}
GH_INLINE void GH_SDIO1_set_MaxCurCapReg_MaxCurFor30v(U8 data)
{
    GH_SDIO1_MAXCURCAPREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_MAXCURCAPREG;
    d.bitc.maxcurfor30v = data;
    *(volatile U32 *)REG_SDIO1_MAXCURCAPREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_MaxCurCapReg_MaxCurFor30v] <-- 0x%08x\n",
                        REG_SDIO1_MAXCURCAPREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_MaxCurCapReg_MaxCurFor30v(void)
{
    GH_SDIO1_MAXCURCAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_MAXCURCAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_MaxCurCapReg_MaxCurFor30v] --> 0x%08x\n",
                        REG_SDIO1_MAXCURCAPREG,value);
    #endif
    return tmp_value.bitc.maxcurfor30v;
}
GH_INLINE void GH_SDIO1_set_MaxCurCapReg_MaxCurFor18v(U8 data)
{
    GH_SDIO1_MAXCURCAPREG_S d;
    d.all = *(volatile U32 *)REG_SDIO1_MAXCURCAPREG;
    d.bitc.maxcurfor18v = data;
    *(volatile U32 *)REG_SDIO1_MAXCURCAPREG = d.all;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO1_set_MaxCurCapReg_MaxCurFor18v] <-- 0x%08x\n",
                        REG_SDIO1_MAXCURCAPREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO1_get_MaxCurCapReg_MaxCurFor18v(void)
{
    GH_SDIO1_MAXCURCAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_MAXCURCAPREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_MaxCurCapReg_MaxCurFor18v] --> 0x%08x\n",
                        REG_SDIO1_MAXCURCAPREG,value);
    #endif
    return tmp_value.bitc.maxcurfor18v;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO1_SlotIntStatusReg (read)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SDIO1_SlotIntStatusReg'. */
U32  GH_SDIO1_get_SlotIntStatusReg(void);
/*! \brief Reads the bit group 'IntSigForEachSlot' of register 'SDIO1_SlotIntStatusReg'. */
U8   GH_SDIO1_get_SlotIntStatusReg_IntSigForEachSlot(void);
/*! \brief Reads the bit group 'SpecifiVerNum' of register 'SDIO1_SlotIntStatusReg'. */
U8   GH_SDIO1_get_SlotIntStatusReg_SpecifiVerNum(void);
/*! \brief Reads the bit group 'VendorVerNum' of register 'SDIO1_SlotIntStatusReg'. */
U8   GH_SDIO1_get_SlotIntStatusReg_VendorVerNum(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO1_get_SlotIntStatusReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO1_SLOTINTSTATUSREG);

    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_SlotIntStatusReg] --> 0x%08x\n",
                        REG_SDIO1_SLOTINTSTATUSREG,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SDIO1_get_SlotIntStatusReg_IntSigForEachSlot(void)
{
    GH_SDIO1_SLOTINTSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_SLOTINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_SlotIntStatusReg_IntSigForEachSlot] --> 0x%08x\n",
                        REG_SDIO1_SLOTINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.intsigforeachslot;
}
GH_INLINE U8   GH_SDIO1_get_SlotIntStatusReg_SpecifiVerNum(void)
{
    GH_SDIO1_SLOTINTSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_SLOTINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_SlotIntStatusReg_SpecifiVerNum] --> 0x%08x\n",
                        REG_SDIO1_SLOTINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.specifivernum;
}
GH_INLINE U8   GH_SDIO1_get_SlotIntStatusReg_VendorVerNum(void)
{
    GH_SDIO1_SLOTINTSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO1_SLOTINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO1_ENABLE_DEBUG_PRINT
    GH_SDIO1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO1_get_SlotIntStatusReg_VendorVerNum] --> 0x%08x\n",
                        REG_SDIO1_SLOTINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.vendorvernum;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_SDIO1_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_SDIO1_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

