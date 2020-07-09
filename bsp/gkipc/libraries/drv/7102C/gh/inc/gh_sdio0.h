/*!
*******************************************************************************
**
** \file      gh_sdio0.h
**
** \brief     SDIO0 Host Controller.
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
#define REG_SDIO0_SYSADDRREG                                FIO_ADDRESS(SDIO0,0x90000000) /* read/write */
#define REG_SDIO0_TRANMODEREG                               FIO_ADDRESS(SDIO0,0x90000004) /* read/write */
#define REG_SDIO0_NORINTSIGENREG                            FIO_ADDRESS(SDIO0,0x90000006) /* read/write */
#define REG_SDIO0_ERRINTSIGENREG                            FIO_ADDRESS(SDIO0,0x90000008) /* read/write */
#define REG_SDIO0_BLKCOUREG                                 FIO_ADDRESS(SDIO0,0x9000000A) /* read/write */
#define REG_SDIO0_BLKSIZEREG                                FIO_ADDRESS(SDIO0,0x9000000C) /* read/write */
#define REG_SDIO0_NORINTSTAENREG                            FIO_ADDRESS(SDIO0,0x9000000E) /* read/write */
#define REG_SDIO0_ERRINTSTAENREG                            FIO_ADDRESS(SDIO0,0x90000010) /* read/write */
#define REG_SDIO0_NORINTSTAREG                              FIO_ADDRESS(SDIO0,0x90000012) /* read/write */
#define REG_SDIO0_ERRINTSTATUSREG                           FIO_ADDRESS(SDIO0,0x90000014) /* read/write */
#define REG_SDIO0_COMMONDREG                                FIO_ADDRESS(SDIO0,0x90000016) /* read/write */
#define REG_SDIO0_SOFTRESETREG                              FIO_ADDRESS(SDIO0,0x90000018) /* read/write */
#define REG_SDIO0_CLKCONTROLREG                             FIO_ADDRESS(SDIO0,0x9000001A) /* read/write */
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
        U16                             : 6;
        U16 fixedto0                    : 1;
    } bitc;
} GH_SDIO0_NORINTSIGENREG_S;

typedef union { /* SDIO0_ErrIntSigEnReg */
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
} GH_SDIO0_ERRINTSIGENREG_S;

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
        U16                             : 1;
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

typedef union { /* SDIO0_ErrIntStatusReg */
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
} GH_SDIO0_ERRINTSTATUSREG_S;

typedef union { /* SDIO0_CommondReg */
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
} GH_SDIO0_COMMONDREG_S;

typedef union { /* SDIO0_SoftResetReg */
    U16 all;
    struct {
        U16 datatimeoutcountervalue     : 4;
        U16                             : 4;
        U16 softwareresetcmdline        : 1;
        U16 softwareresetall            : 1;
        U16 softwareresetdatline        : 1;
        U16                             : 5;
    } bitc;
} GH_SDIO0_SOFTRESETREG_S;

typedef union { /* SDIO0_ClkControlReg */
    U16 all;
    struct {
        U16 internalclken               : 1;
        U16 internalclkstable           : 1;
        U16 sdclken                     : 1;
        U16                             : 5;
        U16 sdclkfreselect              : 8;
    } bitc;
} GH_SDIO0_CLKCONTROLREG_S;

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
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO0_SysAddrReg'. */
void GH_SDIO0_set_SysAddrReg(U32 data);
/*! \brief Reads the register 'SDIO0_SysAddrReg'. */
U32  GH_SDIO0_get_SysAddrReg(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_SysAddrReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_SYSADDRREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_SysAddrReg] <-- 0x%08x\n",
                        REG_SDIO0_SYSADDRREG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO0_get_SysAddrReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_SYSADDRREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SysAddrReg] --> 0x%08x\n",
                        REG_SDIO0_SYSADDRREG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_TranModeReg (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_TranModeReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_TRANMODEREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,data,data);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_TranModeReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO0_set_TranModeReg_BlkCountEn(U8 data)
{
    GH_SDIO0_TRANMODEREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG;
    d.bitc.blkcounten = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_BlkCountEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_TranModeReg_BlkCountEn(void)
{
    GH_SDIO0_TRANMODEREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_BlkCountEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.blkcounten;
}
GH_INLINE void GH_SDIO0_set_TranModeReg_AutoCmd12En(U8 data)
{
    GH_SDIO0_TRANMODEREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG;
    d.bitc.autocmd12en = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_AutoCmd12En] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_TranModeReg_AutoCmd12En(void)
{
    GH_SDIO0_TRANMODEREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_AutoCmd12En] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.autocmd12en;
}
GH_INLINE void GH_SDIO0_set_TranModeReg_DmaEn(U8 data)
{
    GH_SDIO0_TRANMODEREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG;
    d.bitc.dmaen = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_DmaEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_TranModeReg_DmaEn(void)
{
    GH_SDIO0_TRANMODEREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_DmaEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.dmaen;
}
GH_INLINE void GH_SDIO0_set_TranModeReg_MSBlkSelect(U8 data)
{
    GH_SDIO0_TRANMODEREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG;
    d.bitc.msblkselect = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_MSBlkSelect] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_TranModeReg_MSBlkSelect(void)
{
    GH_SDIO0_TRANMODEREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_MSBlkSelect] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.msblkselect;
}
GH_INLINE void GH_SDIO0_set_TranModeReg_DataTraDirSelect(U8 data)
{
    GH_SDIO0_TRANMODEREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG;
    d.bitc.datatradirselect = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_DataTraDirSelect] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_TranModeReg_DataTraDirSelect(void)
{
    GH_SDIO0_TRANMODEREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_DataTraDirSelect] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.datatradirselect;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_NorIntSigEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,data,data);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_NorIntSigEnReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_CmdCompleteSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.cmdcompletesigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_CmdCompleteSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_CmdCompleteSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_CmdCompleteSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cmdcompletesigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_TraCompleteSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.tracompletesigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_TraCompleteSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_TraCompleteSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_TraCompleteSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.tracompletesigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_BlkGapEveSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.blkgapevesigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_BlkGapEveSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_BlkGapEveSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_BlkGapEveSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.blkgapevesigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_DmaIntSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.dmaintsigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_DmaIntSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_DmaIntSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_DmaIntSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.dmaintsigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_BufWReadySigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.bufwreadysigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_BufWReadySigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_BufWReadySigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_BufWReadySigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.bufwreadysigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_BufRReadySigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.bufrreadysigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_BufRReadySigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_BufRReadySigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_BufRReadySigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.bufrreadysigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_CardInsertionSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.cardinsertionsigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_CardInsertionSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_CardInsertionSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_CardInsertionSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardinsertionsigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_CardRemSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.cardremsigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_CardRemSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_CardRemSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_CardRemSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardremsigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_CardIntSigEN(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.cardintsigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_CardIntSigEN] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_CardIntSigEN(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_CardIntSigEN] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardintsigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_FixedTo0(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG;
    d.bitc.fixedto0 = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_FixedTo0] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_FixedTo0(void)
{
    GH_SDIO0_NORINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_FixedTo0] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.fixedto0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntSigEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO0_ErrIntSigEnReg'. */
void GH_SDIO0_set_ErrIntSigEnReg(U16 data);
/*! \brief Reads the register 'SDIO0_ErrIntSigEnReg'. */
U16  GH_SDIO0_get_ErrIntSigEnReg(void);
/*! \brief Writes the bit group 'CmdTimeoutErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
void GH_SDIO0_set_ErrIntSigEnReg_CmdTimeoutErrSigEn(U8 data);
/*! \brief Reads the bit group 'CmdTimeoutErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
U8   GH_SDIO0_get_ErrIntSigEnReg_CmdTimeoutErrSigEn(void);
/*! \brief Writes the bit group 'CmdEndBitErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
void GH_SDIO0_set_ErrIntSigEnReg_CmdEndBitErrSigEn(U8 data);
/*! \brief Reads the bit group 'CmdEndBitErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
U8   GH_SDIO0_get_ErrIntSigEnReg_CmdEndBitErrSigEn(void);
/*! \brief Writes the bit group 'CmdIndexErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
void GH_SDIO0_set_ErrIntSigEnReg_CmdIndexErrSigEn(U8 data);
/*! \brief Reads the bit group 'CmdIndexErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
U8   GH_SDIO0_get_ErrIntSigEnReg_CmdIndexErrSigEn(void);
/*! \brief Writes the bit group 'DataTimeoutErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
void GH_SDIO0_set_ErrIntSigEnReg_DataTimeoutErrSigEn(U8 data);
/*! \brief Reads the bit group 'DataTimeoutErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
U8   GH_SDIO0_get_ErrIntSigEnReg_DataTimeoutErrSigEn(void);
/*! \brief Writes the bit group 'CmdCrcErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
void GH_SDIO0_set_ErrIntSigEnReg_CmdCrcErrSigEn(U8 data);
/*! \brief Reads the bit group 'CmdCrcErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
U8   GH_SDIO0_get_ErrIntSigEnReg_CmdCrcErrSigEn(void);
/*! \brief Writes the bit group 'DataCrcErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
void GH_SDIO0_set_ErrIntSigEnReg_DataCrcErrSigEn(U8 data);
/*! \brief Reads the bit group 'DataCrcErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
U8   GH_SDIO0_get_ErrIntSigEnReg_DataCrcErrSigEn(void);
/*! \brief Writes the bit group 'DataEndBitErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
void GH_SDIO0_set_ErrIntSigEnReg_DataEndBitErrSigEn(U8 data);
/*! \brief Reads the bit group 'DataEndBitErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
U8   GH_SDIO0_get_ErrIntSigEnReg_DataEndBitErrSigEn(void);
/*! \brief Writes the bit group 'CurLimitErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
void GH_SDIO0_set_ErrIntSigEnReg_CurLimitErrSigEn(U8 data);
/*! \brief Reads the bit group 'CurLimitErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
U8   GH_SDIO0_get_ErrIntSigEnReg_CurLimitErrSigEn(void);
/*! \brief Writes the bit group 'AutoCmd12ErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
void GH_SDIO0_set_ErrIntSigEnReg_AutoCmd12ErrSigEn(U8 data);
/*! \brief Reads the bit group 'AutoCmd12ErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
U8   GH_SDIO0_get_ErrIntSigEnReg_AutoCmd12ErrSigEn(void);
/*! \brief Writes the bit group 'VendorSpecificErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
void GH_SDIO0_set_ErrIntSigEnReg_VendorSpecificErrSigEn(U8 data);
/*! \brief Reads the bit group 'VendorSpecificErrSigEn' of register 'SDIO0_ErrIntSigEnReg'. */
U8   GH_SDIO0_get_ErrIntSigEnReg_VendorSpecificErrSigEn(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_ErrIntSigEnReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,data,data);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_ErrIntSigEnReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEnReg_CmdTimeoutErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.cmdtimeouterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_CmdTimeoutErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEnReg_CmdTimeoutErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_CmdTimeoutErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cmdtimeouterrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEnReg_CmdEndBitErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.cmdendbiterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_CmdEndBitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEnReg_CmdEndBitErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_CmdEndBitErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cmdendbiterrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEnReg_CmdIndexErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.cmdindexerrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_CmdIndexErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEnReg_CmdIndexErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_CmdIndexErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cmdindexerrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEnReg_DataTimeoutErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.datatimeouterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_DataTimeoutErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEnReg_DataTimeoutErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_DataTimeoutErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.datatimeouterrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEnReg_CmdCrcErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.cmdcrcerrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_CmdCrcErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEnReg_CmdCrcErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_CmdCrcErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cmdcrcerrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEnReg_DataCrcErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.datacrcerrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_DataCrcErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEnReg_DataCrcErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_DataCrcErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.datacrcerrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEnReg_DataEndBitErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.dataendbiterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_DataEndBitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEnReg_DataEndBitErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_DataEndBitErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.dataendbiterrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEnReg_CurLimitErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.curlimiterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_CurLimitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEnReg_CurLimitErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_CurLimitErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.curlimiterrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEnReg_AutoCmd12ErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.autocmd12errsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_AutoCmd12ErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEnReg_AutoCmd12ErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_AutoCmd12ErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.autocmd12errsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEnReg_VendorSpecificErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG;
    d.bitc.vendorspecificerrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEnReg_VendorSpecificErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEnReg_VendorSpecificErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEnReg_VendorSpecificErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGENREG,value);
    #endif
    return tmp_value.bitc.vendorspecificerrsigen;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_BlkCouReg (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO0_BlkCouReg'. */
void GH_SDIO0_set_BlkCouReg(U16 data);
/*! \brief Reads the register 'SDIO0_BlkCouReg'. */
U16  GH_SDIO0_get_BlkCouReg(void);
/*! \brief Writes the bit group 'BlkCountForCurTra' of register 'SDIO0_BlkCouReg'. */
void GH_SDIO0_set_BlkCouReg_BlkCountForCurTra(U16 data);
/*! \brief Reads the bit group 'BlkCountForCurTra' of register 'SDIO0_BlkCouReg'. */
U16  GH_SDIO0_get_BlkCouReg_BlkCountForCurTra(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_BlkCouReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_BLKCOUREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkCouReg] <-- 0x%08x\n",
                        REG_SDIO0_BLKCOUREG,data,data);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_BlkCouReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_BLKCOUREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkCouReg] --> 0x%08x\n",
                        REG_SDIO0_BLKCOUREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO0_set_BlkCouReg_BlkCountForCurTra(U16 data)
{
    GH_SDIO0_BLKCOUREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_BLKCOUREG;
    d.bitc.blkcountforcurtra = data;
    *(volatile U16 *)REG_SDIO0_BLKCOUREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkCouReg_BlkCountForCurTra] <-- 0x%08x\n",
                        REG_SDIO0_BLKCOUREG,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_BlkCouReg_BlkCountForCurTra(void)
{
    GH_SDIO0_BLKCOUREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_BLKCOUREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkCouReg_BlkCountForCurTra] --> 0x%08x\n",
                        REG_SDIO0_BLKCOUREG,value);
    #endif
    return tmp_value.bitc.blkcountforcurtra;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_BlkSizeReg (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_BlkSizeReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_BLKSIZEREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeReg] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,data,data);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_BlkSizeReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_BLKSIZEREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeReg] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO0_set_BlkSizeReg_TraBlkSize(U16 data)
{
    GH_SDIO0_BLKSIZEREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_BLKSIZEREG;
    d.bitc.trablksize = data;
    *(volatile U16 *)REG_SDIO0_BLKSIZEREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeReg_TraBlkSize] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_BlkSizeReg_TraBlkSize(void)
{
    GH_SDIO0_BLKSIZEREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_BLKSIZEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeReg_TraBlkSize] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,value);
    #endif
    return tmp_value.bitc.trablksize;
}
GH_INLINE void GH_SDIO0_set_BlkSizeReg_HostSdmaBufSize(U8 data)
{
    GH_SDIO0_BLKSIZEREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_BLKSIZEREG;
    d.bitc.hostsdmabufsize = data;
    *(volatile U16 *)REG_SDIO0_BLKSIZEREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeReg_HostSdmaBufSize] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_BlkSizeReg_HostSdmaBufSize(void)
{
    GH_SDIO0_BLKSIZEREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_BLKSIZEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeReg_HostSdmaBufSize] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,value);
    #endif
    return tmp_value.bitc.hostsdmabufsize;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_NorIntStaEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,data,data);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_NorIntStaEnReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_CmdCompleteStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.cmdcompletestatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_CmdCompleteStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_CmdCompleteStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_CmdCompleteStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdcompletestatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_TraCompleteStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.tracompletestatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_TraCompleteStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_TraCompleteStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_TraCompleteStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.tracompletestatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_BlkGapEveStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.blkgapevestatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_BlkGapEveStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_BlkGapEveStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_BlkGapEveStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.blkgapevestatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_DmaIntStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.dmaintstatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_DmaIntStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_DmaIntStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_DmaIntStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.dmaintstatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_BufWReadyStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.bufwreadystatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_BufWReadyStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_BufWReadyStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_BufWReadyStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.bufwreadystatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_BufRReadyStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.bufrreadystatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_BufRReadyStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_BufRReadyStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_BufRReadyStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.bufrreadystatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_CardInsertionStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.cardinsertionstatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_CardInsertionStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_CardInsertionStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_CardInsertionStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardinsertionstatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_CardRemStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.cardremstatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_CardRemStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_CardRemStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_CardRemStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardremstatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_CardIntStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.cardintstatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_CardIntStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_CardIntStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_CardIntStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardintstatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_FixedTo0(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG;
    d.bitc.fixedto0 = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_FixedTo0] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_FixedTo0(void)
{
    GH_SDIO0_NORINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_FixedTo0] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.fixedto0;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntStaEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,data,data);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_ErrIntStaEnReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.cmdtimeouterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdtimeouterrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_CmdEndBitErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.cmdendbiterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CmdEndBitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_CmdEndBitErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CmdEndBitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdendbiterrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_CmdCrcErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.cmdcrcerrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CmdCrcErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_CmdCrcErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CmdCrcErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdcrcerrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_CmdIndexErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.cmdindexerrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CmdIndexErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_CmdIndexErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CmdIndexErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdindexerrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_DataCrcErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.datacrcerrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_DataCrcErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_DataCrcErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_DataCrcErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.datacrcerrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_DataTimeoutErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.datatimeouterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_DataTimeoutErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_DataTimeoutErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_DataTimeoutErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.datatimeouterrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_DataEndBitErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.dataendbiterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_DataEndBitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_DataEndBitErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_DataEndBitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.dataendbiterrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_CurLimitErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.curlimiterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CurLimitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_CurLimitErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CurLimitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.curlimiterrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.autocmd12errstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.autocmd12errstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_VendorSpecificErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG;
    d.bitc.vendorspecificerrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_VendorSpecificErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_VendorSpecificErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_VendorSpecificErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.vendorspecificerrstatusen;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_NorIntStaReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_NorIntStaReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,data,data);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_NorIntStaReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_CmdComplete(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.cmdcomplete = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_CmdComplete] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_CmdComplete(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_CmdComplete] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdcomplete;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_BlkGapEvent(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.blkgapevent = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_BlkGapEvent] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_BlkGapEvent(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_BlkGapEvent] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.blkgapevent;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_DmaInt(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.dmaint = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_DmaInt] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_DmaInt(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_DmaInt] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.dmaint;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_TraComplete(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.tracomplete = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_TraComplete] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_TraComplete(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_TraComplete] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.tracomplete;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_BufWReady(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.bufwready = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_BufWReady] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_BufWReady(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_BufWReady] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bufwready;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_CardInsertion(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.cardinsertion = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_CardInsertion] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_CardInsertion(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_CardInsertion] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardinsertion;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_BufRReady(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.bufrready = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_BufRReady] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_BufRReady(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_BufRReady] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bufrready;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_CardRemoval(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.cardremoval = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_CardRemoval] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_CardRemoval(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_CardRemoval] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardremoval;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_CardInt(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.cardint = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_CardInt] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_CardInt(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_CardInt] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardint;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_BootAckRcv(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.bootackrcv = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_BootAckRcv] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_BootAckRcv(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_BootAckRcv] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bootackrcv;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_ErrInt(U8 data)
{
    GH_SDIO0_NORINTSTAREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG;
    d.bitc.errint = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_ErrInt] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_ErrInt(void)
{
    GH_SDIO0_NORINTSTAREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_ErrInt] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.errint;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntStatusReg (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO0_ErrIntStatusReg'. */
void GH_SDIO0_set_ErrIntStatusReg(U16 data);
/*! \brief Reads the register 'SDIO0_ErrIntStatusReg'. */
U16  GH_SDIO0_get_ErrIntStatusReg(void);
/*! \brief Writes the bit group 'CmdTimeoutErr' of register 'SDIO0_ErrIntStatusReg'. */
void GH_SDIO0_set_ErrIntStatusReg_CmdTimeoutErr(U8 data);
/*! \brief Reads the bit group 'CmdTimeoutErr' of register 'SDIO0_ErrIntStatusReg'. */
U8   GH_SDIO0_get_ErrIntStatusReg_CmdTimeoutErr(void);
/*! \brief Writes the bit group 'CmdCrcErr' of register 'SDIO0_ErrIntStatusReg'. */
void GH_SDIO0_set_ErrIntStatusReg_CmdCrcErr(U8 data);
/*! \brief Reads the bit group 'CmdCrcErr' of register 'SDIO0_ErrIntStatusReg'. */
U8   GH_SDIO0_get_ErrIntStatusReg_CmdCrcErr(void);
/*! \brief Writes the bit group 'CmdEndBitErr' of register 'SDIO0_ErrIntStatusReg'. */
void GH_SDIO0_set_ErrIntStatusReg_CmdEndBitErr(U8 data);
/*! \brief Reads the bit group 'CmdEndBitErr' of register 'SDIO0_ErrIntStatusReg'. */
U8   GH_SDIO0_get_ErrIntStatusReg_CmdEndBitErr(void);
/*! \brief Writes the bit group 'CmdIndexErr' of register 'SDIO0_ErrIntStatusReg'. */
void GH_SDIO0_set_ErrIntStatusReg_CmdIndexErr(U8 data);
/*! \brief Reads the bit group 'CmdIndexErr' of register 'SDIO0_ErrIntStatusReg'. */
U8   GH_SDIO0_get_ErrIntStatusReg_CmdIndexErr(void);
/*! \brief Writes the bit group 'DataTimeoutErr' of register 'SDIO0_ErrIntStatusReg'. */
void GH_SDIO0_set_ErrIntStatusReg_DataTimeoutErr(U8 data);
/*! \brief Reads the bit group 'DataTimeoutErr' of register 'SDIO0_ErrIntStatusReg'. */
U8   GH_SDIO0_get_ErrIntStatusReg_DataTimeoutErr(void);
/*! \brief Writes the bit group 'DataCrcErr' of register 'SDIO0_ErrIntStatusReg'. */
void GH_SDIO0_set_ErrIntStatusReg_DataCrcErr(U8 data);
/*! \brief Reads the bit group 'DataCrcErr' of register 'SDIO0_ErrIntStatusReg'. */
U8   GH_SDIO0_get_ErrIntStatusReg_DataCrcErr(void);
/*! \brief Writes the bit group 'DataEndBitErr' of register 'SDIO0_ErrIntStatusReg'. */
void GH_SDIO0_set_ErrIntStatusReg_DataEndBitErr(U8 data);
/*! \brief Reads the bit group 'DataEndBitErr' of register 'SDIO0_ErrIntStatusReg'. */
U8   GH_SDIO0_get_ErrIntStatusReg_DataEndBitErr(void);
/*! \brief Writes the bit group 'CurLimitErr' of register 'SDIO0_ErrIntStatusReg'. */
void GH_SDIO0_set_ErrIntStatusReg_CurLimitErr(U8 data);
/*! \brief Reads the bit group 'CurLimitErr' of register 'SDIO0_ErrIntStatusReg'. */
U8   GH_SDIO0_get_ErrIntStatusReg_CurLimitErr(void);
/*! \brief Writes the bit group 'AutoCmd12Err' of register 'SDIO0_ErrIntStatusReg'. */
void GH_SDIO0_set_ErrIntStatusReg_AutoCmd12Err(U8 data);
/*! \brief Reads the bit group 'AutoCmd12Err' of register 'SDIO0_ErrIntStatusReg'. */
U8   GH_SDIO0_get_ErrIntStatusReg_AutoCmd12Err(void);
/*! \brief Writes the bit group 'VendorSpecificErrStatus' of register 'SDIO0_ErrIntStatusReg'. */
void GH_SDIO0_set_ErrIntStatusReg_VendorSpecificErrStatus(U8 data);
/*! \brief Reads the bit group 'VendorSpecificErrStatus' of register 'SDIO0_ErrIntStatusReg'. */
U8   GH_SDIO0_get_ErrIntStatusReg_VendorSpecificErrStatus(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_ErrIntStatusReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,data,data);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_ErrIntStatusReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO0_set_ErrIntStatusReg_CmdTimeoutErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.cmdtimeouterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_CmdTimeoutErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStatusReg_CmdTimeoutErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_CmdTimeoutErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.cmdtimeouterr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStatusReg_CmdCrcErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.cmdcrcerr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_CmdCrcErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStatusReg_CmdCrcErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_CmdCrcErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.cmdcrcerr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStatusReg_CmdEndBitErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.cmdendbiterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_CmdEndBitErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStatusReg_CmdEndBitErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_CmdEndBitErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.cmdendbiterr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStatusReg_CmdIndexErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.cmdindexerr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_CmdIndexErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStatusReg_CmdIndexErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_CmdIndexErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.cmdindexerr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStatusReg_DataTimeoutErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.datatimeouterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_DataTimeoutErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStatusReg_DataTimeoutErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_DataTimeoutErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.datatimeouterr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStatusReg_DataCrcErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.datacrcerr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_DataCrcErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStatusReg_DataCrcErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_DataCrcErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.datacrcerr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStatusReg_DataEndBitErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.dataendbiterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_DataEndBitErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStatusReg_DataEndBitErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_DataEndBitErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.dataendbiterr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStatusReg_CurLimitErr(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.curlimiterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_CurLimitErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStatusReg_CurLimitErr(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_CurLimitErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.curlimiterr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStatusReg_AutoCmd12Err(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.autocmd12err = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_AutoCmd12Err] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStatusReg_AutoCmd12Err(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_AutoCmd12Err] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12err;
}
GH_INLINE void GH_SDIO0_set_ErrIntStatusReg_VendorSpecificErrStatus(U8 data)
{
    GH_SDIO0_ERRINTSTATUSREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG;
    d.bitc.vendorspecificerrstatus = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStatusReg_VendorSpecificErrStatus] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStatusReg_VendorSpecificErrStatus(void)
{
    GH_SDIO0_ERRINTSTATUSREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStatusReg_VendorSpecificErrStatus] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.vendorspecificerrstatus;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_CommondReg (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO0_CommondReg'. */
void GH_SDIO0_set_CommondReg(U16 data);
/*! \brief Reads the register 'SDIO0_CommondReg'. */
U16  GH_SDIO0_get_CommondReg(void);
/*! \brief Writes the bit group 'RepTypeSelect' of register 'SDIO0_CommondReg'. */
void GH_SDIO0_set_CommondReg_RepTypeSelect(U8 data);
/*! \brief Reads the bit group 'RepTypeSelect' of register 'SDIO0_CommondReg'. */
U8   GH_SDIO0_get_CommondReg_RepTypeSelect(void);
/*! \brief Writes the bit group 'CmdCrcCheckEn' of register 'SDIO0_CommondReg'. */
void GH_SDIO0_set_CommondReg_CmdCrcCheckEn(U8 data);
/*! \brief Reads the bit group 'CmdCrcCheckEn' of register 'SDIO0_CommondReg'. */
U8   GH_SDIO0_get_CommondReg_CmdCrcCheckEn(void);
/*! \brief Writes the bit group 'DataPreSelect' of register 'SDIO0_CommondReg'. */
void GH_SDIO0_set_CommondReg_DataPreSelect(U8 data);
/*! \brief Reads the bit group 'DataPreSelect' of register 'SDIO0_CommondReg'. */
U8   GH_SDIO0_get_CommondReg_DataPreSelect(void);
/*! \brief Writes the bit group 'CmdIndexCheckEn' of register 'SDIO0_CommondReg'. */
void GH_SDIO0_set_CommondReg_CmdIndexCheckEn(U8 data);
/*! \brief Reads the bit group 'CmdIndexCheckEn' of register 'SDIO0_CommondReg'. */
U8   GH_SDIO0_get_CommondReg_CmdIndexCheckEn(void);
/*! \brief Writes the bit group 'CmdType' of register 'SDIO0_CommondReg'. */
void GH_SDIO0_set_CommondReg_CmdType(U8 data);
/*! \brief Reads the bit group 'CmdType' of register 'SDIO0_CommondReg'. */
U8   GH_SDIO0_get_CommondReg_CmdType(void);
/*! \brief Writes the bit group 'CmdIndex' of register 'SDIO0_CommondReg'. */
void GH_SDIO0_set_CommondReg_CmdIndex(U8 data);
/*! \brief Reads the bit group 'CmdIndex' of register 'SDIO0_CommondReg'. */
U8   GH_SDIO0_get_CommondReg_CmdIndex(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_CommondReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_COMMONDREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CommondReg] <-- 0x%08x\n",
                        REG_SDIO0_COMMONDREG,data,data);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_CommondReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_COMMONDREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CommondReg] --> 0x%08x\n",
                        REG_SDIO0_COMMONDREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO0_set_CommondReg_RepTypeSelect(U8 data)
{
    GH_SDIO0_COMMONDREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_COMMONDREG;
    d.bitc.reptypeselect = data;
    *(volatile U16 *)REG_SDIO0_COMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CommondReg_RepTypeSelect] <-- 0x%08x\n",
                        REG_SDIO0_COMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_CommondReg_RepTypeSelect(void)
{
    GH_SDIO0_COMMONDREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_COMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CommondReg_RepTypeSelect] --> 0x%08x\n",
                        REG_SDIO0_COMMONDREG,value);
    #endif
    return tmp_value.bitc.reptypeselect;
}
GH_INLINE void GH_SDIO0_set_CommondReg_CmdCrcCheckEn(U8 data)
{
    GH_SDIO0_COMMONDREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_COMMONDREG;
    d.bitc.cmdcrcchecken = data;
    *(volatile U16 *)REG_SDIO0_COMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CommondReg_CmdCrcCheckEn] <-- 0x%08x\n",
                        REG_SDIO0_COMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_CommondReg_CmdCrcCheckEn(void)
{
    GH_SDIO0_COMMONDREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_COMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CommondReg_CmdCrcCheckEn] --> 0x%08x\n",
                        REG_SDIO0_COMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdcrcchecken;
}
GH_INLINE void GH_SDIO0_set_CommondReg_DataPreSelect(U8 data)
{
    GH_SDIO0_COMMONDREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_COMMONDREG;
    d.bitc.datapreselect = data;
    *(volatile U16 *)REG_SDIO0_COMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CommondReg_DataPreSelect] <-- 0x%08x\n",
                        REG_SDIO0_COMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_CommondReg_DataPreSelect(void)
{
    GH_SDIO0_COMMONDREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_COMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CommondReg_DataPreSelect] --> 0x%08x\n",
                        REG_SDIO0_COMMONDREG,value);
    #endif
    return tmp_value.bitc.datapreselect;
}
GH_INLINE void GH_SDIO0_set_CommondReg_CmdIndexCheckEn(U8 data)
{
    GH_SDIO0_COMMONDREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_COMMONDREG;
    d.bitc.cmdindexchecken = data;
    *(volatile U16 *)REG_SDIO0_COMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CommondReg_CmdIndexCheckEn] <-- 0x%08x\n",
                        REG_SDIO0_COMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_CommondReg_CmdIndexCheckEn(void)
{
    GH_SDIO0_COMMONDREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_COMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CommondReg_CmdIndexCheckEn] --> 0x%08x\n",
                        REG_SDIO0_COMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdindexchecken;
}
GH_INLINE void GH_SDIO0_set_CommondReg_CmdType(U8 data)
{
    GH_SDIO0_COMMONDREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_COMMONDREG;
    d.bitc.cmdtype = data;
    *(volatile U16 *)REG_SDIO0_COMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CommondReg_CmdType] <-- 0x%08x\n",
                        REG_SDIO0_COMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_CommondReg_CmdType(void)
{
    GH_SDIO0_COMMONDREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_COMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CommondReg_CmdType] --> 0x%08x\n",
                        REG_SDIO0_COMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdtype;
}
GH_INLINE void GH_SDIO0_set_CommondReg_CmdIndex(U8 data)
{
    GH_SDIO0_COMMONDREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_COMMONDREG;
    d.bitc.cmdindex = data;
    *(volatile U16 *)REG_SDIO0_COMMONDREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CommondReg_CmdIndex] <-- 0x%08x\n",
                        REG_SDIO0_COMMONDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_CommondReg_CmdIndex(void)
{
    GH_SDIO0_COMMONDREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_COMMONDREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CommondReg_CmdIndex] --> 0x%08x\n",
                        REG_SDIO0_COMMONDREG,value);
    #endif
    return tmp_value.bitc.cmdindex;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_SoftResetReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO0_SoftResetReg'. */
void GH_SDIO0_set_SoftResetReg(U16 data);
/*! \brief Reads the register 'SDIO0_SoftResetReg'. */
U16  GH_SDIO0_get_SoftResetReg(void);
/*! \brief Writes the bit group 'DataTimeoutCounterValue' of register 'SDIO0_SoftResetReg'. */
void GH_SDIO0_set_SoftResetReg_DataTimeoutCounterValue(U8 data);
/*! \brief Reads the bit group 'DataTimeoutCounterValue' of register 'SDIO0_SoftResetReg'. */
U8   GH_SDIO0_get_SoftResetReg_DataTimeoutCounterValue(void);
/*! \brief Writes the bit group 'SoftwareResetCmdLine' of register 'SDIO0_SoftResetReg'. */
void GH_SDIO0_set_SoftResetReg_SoftwareResetCmdLine(U8 data);
/*! \brief Reads the bit group 'SoftwareResetCmdLine' of register 'SDIO0_SoftResetReg'. */
U8   GH_SDIO0_get_SoftResetReg_SoftwareResetCmdLine(void);
/*! \brief Writes the bit group 'SoftwareResetAll' of register 'SDIO0_SoftResetReg'. */
void GH_SDIO0_set_SoftResetReg_SoftwareResetAll(U8 data);
/*! \brief Reads the bit group 'SoftwareResetAll' of register 'SDIO0_SoftResetReg'. */
U8   GH_SDIO0_get_SoftResetReg_SoftwareResetAll(void);
/*! \brief Writes the bit group 'SoftwareResetDatLine' of register 'SDIO0_SoftResetReg'. */
void GH_SDIO0_set_SoftResetReg_SoftwareResetDatLine(U8 data);
/*! \brief Reads the bit group 'SoftwareResetDatLine' of register 'SDIO0_SoftResetReg'. */
U8   GH_SDIO0_get_SoftResetReg_SoftwareResetDatLine(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_SoftResetReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_SOFTRESETREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_SoftResetReg] <-- 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,data,data);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_SoftResetReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_SOFTRESETREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SoftResetReg] --> 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO0_set_SoftResetReg_DataTimeoutCounterValue(U8 data)
{
    GH_SDIO0_SOFTRESETREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_SOFTRESETREG;
    d.bitc.datatimeoutcountervalue = data;
    *(volatile U16 *)REG_SDIO0_SOFTRESETREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_SoftResetReg_DataTimeoutCounterValue] <-- 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_SoftResetReg_DataTimeoutCounterValue(void)
{
    GH_SDIO0_SOFTRESETREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_SOFTRESETREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SoftResetReg_DataTimeoutCounterValue] --> 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,value);
    #endif
    return tmp_value.bitc.datatimeoutcountervalue;
}
GH_INLINE void GH_SDIO0_set_SoftResetReg_SoftwareResetCmdLine(U8 data)
{
    GH_SDIO0_SOFTRESETREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_SOFTRESETREG;
    d.bitc.softwareresetcmdline = data;
    *(volatile U16 *)REG_SDIO0_SOFTRESETREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_SoftResetReg_SoftwareResetCmdLine] <-- 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_SoftResetReg_SoftwareResetCmdLine(void)
{
    GH_SDIO0_SOFTRESETREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_SOFTRESETREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SoftResetReg_SoftwareResetCmdLine] --> 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,value);
    #endif
    return tmp_value.bitc.softwareresetcmdline;
}
GH_INLINE void GH_SDIO0_set_SoftResetReg_SoftwareResetAll(U8 data)
{
    GH_SDIO0_SOFTRESETREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_SOFTRESETREG;
    d.bitc.softwareresetall = data;
    *(volatile U16 *)REG_SDIO0_SOFTRESETREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_SoftResetReg_SoftwareResetAll] <-- 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_SoftResetReg_SoftwareResetAll(void)
{
    GH_SDIO0_SOFTRESETREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_SOFTRESETREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SoftResetReg_SoftwareResetAll] --> 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,value);
    #endif
    return tmp_value.bitc.softwareresetall;
}
GH_INLINE void GH_SDIO0_set_SoftResetReg_SoftwareResetDatLine(U8 data)
{
    GH_SDIO0_SOFTRESETREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_SOFTRESETREG;
    d.bitc.softwareresetdatline = data;
    *(volatile U16 *)REG_SDIO0_SOFTRESETREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_SoftResetReg_SoftwareResetDatLine] <-- 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_SoftResetReg_SoftwareResetDatLine(void)
{
    GH_SDIO0_SOFTRESETREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_SOFTRESETREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SoftResetReg_SoftwareResetDatLine] --> 0x%08x\n",
                        REG_SDIO0_SOFTRESETREG,value);
    #endif
    return tmp_value.bitc.softwareresetdatline;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_ClkControlReg (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO0_ClkControlReg'. */
void GH_SDIO0_set_ClkControlReg(U16 data);
/*! \brief Reads the register 'SDIO0_ClkControlReg'. */
U16  GH_SDIO0_get_ClkControlReg(void);
/*! \brief Writes the bit group 'InternalClkEn' of register 'SDIO0_ClkControlReg'. */
void GH_SDIO0_set_ClkControlReg_InternalClkEn(U8 data);
/*! \brief Reads the bit group 'InternalClkEn' of register 'SDIO0_ClkControlReg'. */
U8   GH_SDIO0_get_ClkControlReg_InternalClkEn(void);
/*! \brief Writes the bit group 'InternalClkStable' of register 'SDIO0_ClkControlReg'. */
void GH_SDIO0_set_ClkControlReg_InternalClkStable(U8 data);
/*! \brief Reads the bit group 'InternalClkStable' of register 'SDIO0_ClkControlReg'. */
U8   GH_SDIO0_get_ClkControlReg_InternalClkStable(void);
/*! \brief Writes the bit group 'SdClkEn' of register 'SDIO0_ClkControlReg'. */
void GH_SDIO0_set_ClkControlReg_SdClkEn(U8 data);
/*! \brief Reads the bit group 'SdClkEn' of register 'SDIO0_ClkControlReg'. */
U8   GH_SDIO0_get_ClkControlReg_SdClkEn(void);
/*! \brief Writes the bit group 'SdclkFreSelect' of register 'SDIO0_ClkControlReg'. */
void GH_SDIO0_set_ClkControlReg_SdclkFreSelect(U8 data);
/*! \brief Reads the bit group 'SdclkFreSelect' of register 'SDIO0_ClkControlReg'. */
U8   GH_SDIO0_get_ClkControlReg_SdclkFreSelect(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_ClkControlReg(U16 data)
{
    *(volatile U16 *)REG_SDIO0_CLKCONTROLREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ClkControlReg] <-- 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,data,data);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_ClkControlReg(void)
{
    U16 value = (*(volatile U16 *)REG_SDIO0_CLKCONTROLREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ClkControlReg] --> 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO0_set_ClkControlReg_InternalClkEn(U8 data)
{
    GH_SDIO0_CLKCONTROLREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_CLKCONTROLREG;
    d.bitc.internalclken = data;
    *(volatile U16 *)REG_SDIO0_CLKCONTROLREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ClkControlReg_InternalClkEn] <-- 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ClkControlReg_InternalClkEn(void)
{
    GH_SDIO0_CLKCONTROLREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_CLKCONTROLREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ClkControlReg_InternalClkEn] --> 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,value);
    #endif
    return tmp_value.bitc.internalclken;
}
GH_INLINE void GH_SDIO0_set_ClkControlReg_InternalClkStable(U8 data)
{
    GH_SDIO0_CLKCONTROLREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_CLKCONTROLREG;
    d.bitc.internalclkstable = data;
    *(volatile U16 *)REG_SDIO0_CLKCONTROLREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ClkControlReg_InternalClkStable] <-- 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ClkControlReg_InternalClkStable(void)
{
    GH_SDIO0_CLKCONTROLREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_CLKCONTROLREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ClkControlReg_InternalClkStable] --> 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,value);
    #endif
    return tmp_value.bitc.internalclkstable;
}
GH_INLINE void GH_SDIO0_set_ClkControlReg_SdClkEn(U8 data)
{
    GH_SDIO0_CLKCONTROLREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_CLKCONTROLREG;
    d.bitc.sdclken = data;
    *(volatile U16 *)REG_SDIO0_CLKCONTROLREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ClkControlReg_SdClkEn] <-- 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ClkControlReg_SdClkEn(void)
{
    GH_SDIO0_CLKCONTROLREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_CLKCONTROLREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ClkControlReg_SdClkEn] --> 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,value);
    #endif
    return tmp_value.bitc.sdclken;
}
GH_INLINE void GH_SDIO0_set_ClkControlReg_SdclkFreSelect(U8 data)
{
    GH_SDIO0_CLKCONTROLREG_S d;
    d.all = *(volatile U16 *)REG_SDIO0_CLKCONTROLREG;
    d.bitc.sdclkfreselect = data;
    *(volatile U16 *)REG_SDIO0_CLKCONTROLREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ClkControlReg_SdclkFreSelect] <-- 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ClkControlReg_SdclkFreSelect(void)
{
    GH_SDIO0_CLKCONTROLREG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_CLKCONTROLREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ClkControlReg_SdclkFreSelect] --> 0x%08x\n",
                        REG_SDIO0_CLKCONTROLREG,value);
    #endif
    return tmp_value.bitc.sdclkfreselect;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp0Reg (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SDIO0_Resp0Reg'. */
U32  GH_SDIO0_get_Resp0Reg(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO0_get_Resp0Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_RESP0REG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Resp0Reg] --> 0x%08x\n",
                        REG_SDIO0_RESP0REG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp1Reg (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SDIO0_Resp1Reg'. */
U32  GH_SDIO0_get_Resp1Reg(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO0_get_Resp1Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_RESP1REG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Resp1Reg] --> 0x%08x\n",
                        REG_SDIO0_RESP1REG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp2Reg (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SDIO0_Resp2Reg'. */
U32  GH_SDIO0_get_Resp2Reg(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO0_get_Resp2Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_RESP2REG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Resp2Reg] --> 0x%08x\n",
                        REG_SDIO0_RESP2REG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp3Reg (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SDIO0_Resp3Reg'. */
U32  GH_SDIO0_get_Resp3Reg(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO0_get_Resp3Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_RESP3REG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Resp3Reg] --> 0x%08x\n",
                        REG_SDIO0_RESP3REG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_Control00Reg (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_Control00Reg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO0_get_Control00Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_LedControl(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.ledcontrol = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_LedControl] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_LedControl(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_LedControl] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.ledcontrol;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_DataTraWidth(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.datatrawidth = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_DataTraWidth] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_DataTraWidth(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_DataTraWidth] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.datatrawidth;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_Sd8BitMode(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.sd8bitmode = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_Sd8BitMode] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_Sd8BitMode(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_Sd8BitMode] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.sd8bitmode;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_HostSpeedEn(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.hostspeeden = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_HostSpeedEn] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_HostSpeedEn(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_HostSpeedEn] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.hostspeeden;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_CardDetectTestLevel(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.carddetecttestlevel = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_CardDetectTestLevel] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_CardDetectTestLevel(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_CardDetectTestLevel] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.carddetecttestlevel;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_CardDetectSigDet(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.carddetectsigdet = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_CardDetectSigDet] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_CardDetectSigDet(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_CardDetectSigDet] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.carddetectsigdet;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_SdBusPower(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.sdbuspower = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_SdBusPower] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_SdBusPower(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_SdBusPower] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.sdbuspower;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_SdBusVoltageSelect(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.sdbusvoltageselect = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_SdBusVoltageSelect] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_SdBusVoltageSelect(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_SdBusVoltageSelect] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.sdbusvoltageselect;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_StopAtBlkGapReq(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.stopatblkgapreq = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_StopAtBlkGapReq] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_StopAtBlkGapReq(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_StopAtBlkGapReq] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.stopatblkgapreq;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_RWaitControl(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.rwaitcontrol = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_RWaitControl] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_RWaitControl(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_RWaitControl] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.rwaitcontrol;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_ContinueReq(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.continuereq = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_ContinueReq] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_ContinueReq(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_ContinueReq] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.continuereq;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_IntAtBlkGap(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.intatblkgap = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_IntAtBlkGap] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_IntAtBlkGap(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_IntAtBlkGap] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.intatblkgap;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_DriveCcsd(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.driveccsd = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_DriveCcsd] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_DriveCcsd(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_DriveCcsd] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.driveccsd;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_SpiMode(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.spimode = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_SpiMode] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_SpiMode(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_SpiMode] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.spimode;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_BootEn(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.booten = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_BootEn] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_BootEn(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_BootEn] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.booten;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_AltBootEn(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.altbooten = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_AltBootEn] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_AltBootEn(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_AltBootEn] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.altbooten;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardIns(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.wakeupevetenoncardins = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardIns] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardIns(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardIns] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.wakeupevetenoncardins;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardInt(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.wakeupevetenoncardint = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardInt] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardInt(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardInt] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.wakeupevetenoncardint;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardRem(U8 data)
{
    GH_SDIO0_CONTROL00REG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG;
    d.bitc.wakeupevetenoncardrem = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardRem] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardRem(void)
{
    GH_SDIO0_CONTROL00REG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardRem] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.wakeupevetenoncardrem;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_PresentStateReg (read)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO0_get_PresentStateReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_CmdInhibitCmd(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CmdInhibitCmd] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cmdinhibitcmd;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_DataLineActive(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_DataLineActive] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.datalineactive;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_CmdInhibitData(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CmdInhibitData] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cmdinhibitdata;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_RTraActive(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_RTraActive] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.rtraactive;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_BufWEn(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_BufWEn] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.bufwen;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_WTraActive(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_WTraActive] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.wtraactive;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_BufREn(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_BufREn] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.bufren;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_CardInserted(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CardInserted] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cardinserted;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_CardDetectPinLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CardDetectPinLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.carddetectpinlevel;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_CardStateStable(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CardStateStable] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cardstatestable;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_WProSwiPinLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_WProSwiPinLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.wproswipinlevel;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_Data03LineSigLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_Data03LineSigLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.data03linesiglevel;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_CmdLineSigLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CmdLineSigLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cmdlinesiglevel;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_Data47LineSigLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_Data47LineSigLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.data47linesiglevel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_ArgReg (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO0_ArgReg'. */
void GH_SDIO0_set_ArgReg(U32 data);
/*! \brief Reads the register 'SDIO0_ArgReg'. */
U32  GH_SDIO0_get_ArgReg(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_ArgReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_ARGREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ArgReg] <-- 0x%08x\n",
                        REG_SDIO0_ARGREG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO0_get_ArgReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_ARGREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ArgReg] --> 0x%08x\n",
                        REG_SDIO0_ARGREG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_CapReg (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO0_get_CapReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_TimeoutClkFre(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_TimeoutClkFre] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.timeoutclkfre;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_TimeoutClkUnit(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_TimeoutClkUnit] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.timeoutclkunit;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_BaseClkFreForSdClk(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_BaseClkFreForSdClk] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.baseclkfreforsdclk;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_MaxBlkLen(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_MaxBlkLen] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.maxblklen;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_ExtendedMediaBusSup(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_ExtendedMediaBusSup] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.extendedmediabussup;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_HighSpeedSup(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_HighSpeedSup] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.highspeedsup;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_SusResSup(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_SusResSup] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.susressup;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_SdmaSup(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_SdmaSup] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.sdmasup;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_VoltageSup33v(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_VoltageSup33v] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.voltagesup33v;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_VoltageSup30v(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_VoltageSup30v] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.voltagesup30v;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_VoltageSup18v(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_VoltageSup18v] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.voltagesup18v;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_IntMode(void)
{
    GH_SDIO0_CAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_IntMode] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.intmode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_AutoCmd12ErrStatusReg (read)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO0_get_AutoCmd12ErrStatusReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12timeouterr;
}
GH_INLINE U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12crcerr;
}
GH_INLINE U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12endbiterr;
}
GH_INLINE U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12notexe;
}
GH_INLINE U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12indexerr;
}
GH_INLINE U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.cmdnotissuedbyautocmd12err;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_BufferDataPortReg (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SDIO0_BufferDataPortReg'. */
void GH_SDIO0_set_BufferDataPortReg(U32 data);
/*! \brief Reads the register 'SDIO0_BufferDataPortReg'. */
U32  GH_SDIO0_get_BufferDataPortReg(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_BufferDataPortReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_BUFFERDATAPORTREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BufferDataPortReg] <-- 0x%08x\n",
                        REG_SDIO0_BUFFERDATAPORTREG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO0_get_BufferDataPortReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_BUFFERDATAPORTREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BufferDataPortReg] --> 0x%08x\n",
                        REG_SDIO0_BUFFERDATAPORTREG,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_MaxCurCapReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
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
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SDIO0_set_MaxCurCapReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_MAXCURCAPREG = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_MaxCurCapReg] <-- 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,data,data);
    #endif
}
GH_INLINE U32  GH_SDIO0_get_MaxCurCapReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_MAXCURCAPREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_MaxCurCapReg] --> 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,value);
    #endif
    return value;
}
GH_INLINE void GH_SDIO0_set_MaxCurCapReg_MaxCurFor33v(U8 data)
{
    GH_SDIO0_MAXCURCAPREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_MAXCURCAPREG;
    d.bitc.maxcurfor33v = data;
    *(volatile U32 *)REG_SDIO0_MAXCURCAPREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_MaxCurCapReg_MaxCurFor33v] <-- 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_MaxCurCapReg_MaxCurFor33v(void)
{
    GH_SDIO0_MAXCURCAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_MAXCURCAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_MaxCurCapReg_MaxCurFor33v] --> 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,value);
    #endif
    return tmp_value.bitc.maxcurfor33v;
}
GH_INLINE void GH_SDIO0_set_MaxCurCapReg_MaxCurFor30v(U8 data)
{
    GH_SDIO0_MAXCURCAPREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_MAXCURCAPREG;
    d.bitc.maxcurfor30v = data;
    *(volatile U32 *)REG_SDIO0_MAXCURCAPREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_MaxCurCapReg_MaxCurFor30v] <-- 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_MaxCurCapReg_MaxCurFor30v(void)
{
    GH_SDIO0_MAXCURCAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_MAXCURCAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_MaxCurCapReg_MaxCurFor30v] --> 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,value);
    #endif
    return tmp_value.bitc.maxcurfor30v;
}
GH_INLINE void GH_SDIO0_set_MaxCurCapReg_MaxCurFor18v(U8 data)
{
    GH_SDIO0_MAXCURCAPREG_S d;
    d.all = *(volatile U32 *)REG_SDIO0_MAXCURCAPREG;
    d.bitc.maxcurfor18v = data;
    *(volatile U32 *)REG_SDIO0_MAXCURCAPREG = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_MaxCurCapReg_MaxCurFor18v] <-- 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_MaxCurCapReg_MaxCurFor18v(void)
{
    GH_SDIO0_MAXCURCAPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_MAXCURCAPREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_MaxCurCapReg_MaxCurFor18v] --> 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,value);
    #endif
    return tmp_value.bitc.maxcurfor18v;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SDIO0_SlotIntStatusReg (read)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SDIO0_SlotIntStatusReg'. */
U32  GH_SDIO0_get_SlotIntStatusReg(void);
/*! \brief Reads the bit group 'IntSigForEachSlot' of register 'SDIO0_SlotIntStatusReg'. */
U8   GH_SDIO0_get_SlotIntStatusReg_IntSigForEachSlot(void);
/*! \brief Reads the bit group 'SpecifiVerNum' of register 'SDIO0_SlotIntStatusReg'. */
U8   GH_SDIO0_get_SlotIntStatusReg_SpecifiVerNum(void);
/*! \brief Reads the bit group 'VendorVerNum' of register 'SDIO0_SlotIntStatusReg'. */
U8   GH_SDIO0_get_SlotIntStatusReg_VendorVerNum(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SDIO0_get_SlotIntStatusReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_SLOTINTSTATUSREG);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SlotIntStatusReg] --> 0x%08x\n",
                        REG_SDIO0_SLOTINTSTATUSREG,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SDIO0_get_SlotIntStatusReg_IntSigForEachSlot(void)
{
    GH_SDIO0_SLOTINTSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_SLOTINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SlotIntStatusReg_IntSigForEachSlot] --> 0x%08x\n",
                        REG_SDIO0_SLOTINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.intsigforeachslot;
}
GH_INLINE U8   GH_SDIO0_get_SlotIntStatusReg_SpecifiVerNum(void)
{
    GH_SDIO0_SLOTINTSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_SLOTINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SlotIntStatusReg_SpecifiVerNum] --> 0x%08x\n",
                        REG_SDIO0_SLOTINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.specifivernum;
}
GH_INLINE U8   GH_SDIO0_get_SlotIntStatusReg_VendorVerNum(void)
{
    GH_SDIO0_SLOTINTSTATUSREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_SLOTINTSTATUSREG);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SlotIntStatusReg_VendorVerNum] --> 0x%08x\n",
                        REG_SDIO0_SLOTINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.vendorvernum;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_SDIO0_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_SDIO0_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

