/******************************************************************************
**
** \file      gh_sdio0.c
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
#ifndef SRC_INLINE
#include "gh_sdio0.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_SDIO0_SYSADDRREG_REAL                           FIO_ADDRESS(SDIO0,0x60002000) /* read/write */
#define REG_SDIO0_BLKSIZEREG_REAL                           FIO_ADDRESS(SDIO0,0x60002004) /* read/write */
#define REG_SDIO0_BLKCOUREG_REAL                            FIO_ADDRESS(SDIO0,0x60002006) /* read/write */
#define REG_SDIO0_ARGREG_REAL                               FIO_ADDRESS(SDIO0,0x60002008) /* read/write */
#define REG_SDIO0_TRANMODEREG_REAL                          FIO_ADDRESS(SDIO0,0x6000200C) /* read/write */
#define REG_SDIO0_CMDREG_REAL                               FIO_ADDRESS(SDIO0,0x6000200E) /* read/write */
#define REG_SDIO0_RESP0REG_REAL                             FIO_ADDRESS(SDIO0,0x60002010) /* read */
#define REG_SDIO0_RESP1REG_REAL                             FIO_ADDRESS(SDIO0,0x60002014) /* read */
#define REG_SDIO0_RESP2REG_REAL                             FIO_ADDRESS(SDIO0,0x60002018) /* read */
#define REG_SDIO0_RESP3REG_REAL                             FIO_ADDRESS(SDIO0,0x6000201C) /* read */
#define REG_SDIO0_BUFFERDATAPORTREG_REAL                    FIO_ADDRESS(SDIO0,0x60002020) /* read/write */
#define REG_SDIO0_PRESENTSTATEREG_REAL                      FIO_ADDRESS(SDIO0,0x60002024) /* read */
#define REG_SDIO0_CONTROL00REG_REAL                         FIO_ADDRESS(SDIO0,0x60002028) /* read/write */
#define REG_SDIO0_CONTROL01REG_REAL                         FIO_ADDRESS(SDIO0,0x6000202C) /* read/write */
#define REG_SDIO0_NORINTSTAREG_REAL                         FIO_ADDRESS(SDIO0,0x60002030) /* read/write */
#define REG_SDIO0_ERRINTSTAREG_REAL                         FIO_ADDRESS(SDIO0,0x60002032) /* read/write */
#define REG_SDIO0_NORINTSTAENREG_REAL                       FIO_ADDRESS(SDIO0,0x60002034) /* read/write */
#define REG_SDIO0_ERRINTSTAENREG_REAL                       FIO_ADDRESS(SDIO0,0x60002036) /* read/write */
#define REG_SDIO0_NORINTSIGENREG_REAL                       FIO_ADDRESS(SDIO0,0x60002038) /* read/write */
#define REG_SDIO0_ERRINTSIGENREG_REAL                       FIO_ADDRESS(SDIO0,0x6000203A) /* read/write */
#define REG_SDIO0_AUTOCMD12ERRSTATUSREG_REAL                FIO_ADDRESS(SDIO0,0x6000203C) /* read/write */
#define REG_SDIO0_CAPREG_REAL                               FIO_ADDRESS(SDIO0,0x60002040) /* read */
#define REG_SDIO0_MAXCURCAPREG_REAL                         FIO_ADDRESS(SDIO0,0x60002048) /* read/write */
#define REG_SDIO0_SLOTINTSTATUSREG_REAL                     FIO_ADDRESS(SDIO0,0x600020FC) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* SDIO0_BlkSizeReg */
    U16 all;
    struct {
        U16 trablksize                  : 12;
        U16 hostsdmabufsize             : 3;
        U16                             : 1;
    } bitc;
} GH_SDIO0_BLKSIZEREG_REAL_S;

typedef union { /* SDIO0_BlkCouReg */
    U16 all;
    struct {
        U16 blkcountforcurtra           : 16;
    } bitc;
} GH_SDIO0_BLKCOUREG_REAL_S;

typedef union { /* SDIO0_TranModeReg */
    U16 all;
    struct {
        U16 dmaen                       : 1;
        U16 blkcounten                  : 1;
        U16 autocmd12en                 : 1;
        U16                             : 1;
        U16 datatradirselect            : 1;
        U16 msblkselect                 : 1;
        U16                             : 10;
    } bitc;
} GH_SDIO0_TRANMODEREG_REAL_S;

typedef union { /* SDIO0_CmdReg */
    U16 all;
    struct {
        U16 reptypeselect               : 2;
        U16                             : 1;
        U16 cmdcrcchecken               : 1;
        U16 cmdindexchecken             : 1;
        U16 datapreselect               : 1;
        U16 cmdtype                     : 2;
        U16 cmdindex                    : 6;
        U16                             : 2;
    } bitc;
} GH_SDIO0_CMDREG_REAL_S;

typedef union { /* SDIO0_PresentStateReg */
    U32 all;
    struct {
        U32 cmdinhibitcmd               : 1;
        U32 cmdinhibitdata              : 1;
        U32 datalineactive              : 1;
        U32                             : 5;
        U32 wtraactive                  : 1;
        U32 rtraactive                  : 1;
        U32 bufwen                      : 1;
        U32 bufren                      : 1;
        U32                             : 4;
        U32 cardinserted                : 1;
        U32 cardstatestable             : 1;
        U32 carddetectpinlevel          : 1;
        U32 wproswipinlevel             : 1;
        U32 data03linesiglevel          : 4;
        U32 cmdlinesiglevel             : 1;
        U32 data47linesiglevel          : 4;
        U32                             : 3;
    } bitc;
} GH_SDIO0_PRESENTSTATEREG_REAL_S;

typedef union { /* SDIO0_Control00Reg */
    U32 all;
    struct {
        U32 ledcontrol                  : 1;
        U32 datatrawidth                : 1;
        U32 hostspeeden                 : 1;
        U32 sd8bitmode                  : 1;
        U32                             : 2;
        U32 carddetecttestlevel         : 1;
        U32 carddetectsigdet            : 1;
        U32 sdbuspower                  : 1;
        U32 sdbusvoltageselect          : 3;
        U32                             : 4;
        U32 stopatblkgapreq             : 1;
        U32 continuereq                 : 1;
        U32 rwaitcontrol                : 1;
        U32 intatblkgap                 : 1;
        U32 driveccsd                   : 1;
        U32 spimode                     : 1;
        U32 booten                      : 1;
        U32 altbooten                   : 1;
        U32 wakeupevetenoncardint       : 1;
        U32 wakeupevetenoncardins       : 1;
        U32 wakeupevetenoncardrem       : 1;
        U32                             : 5;
    } bitc;
} GH_SDIO0_CONTROL00REG_REAL_S;

typedef union { /* SDIO0_Control01Reg */
    U32 all;
    struct {
        U32 internalclken               : 1;
        U32 internalclkstable           : 1;
        U32 sdclken                     : 1;
        U32                             : 5;
        U32 sdclkfreselect              : 8;
        U32 datatimeoutcountervalue     : 4;
        U32                             : 4;
        U32 softwareresetall            : 1;
        U32 softwareresetcmdline        : 1;
        U32 softwareresetdatline        : 1;
        U32                             : 5;
    } bitc;
} GH_SDIO0_CONTROL01REG_REAL_S;

typedef union { /* SDIO0_NorIntStaReg */
    U16 all;
    struct {
        U16 cmdcomplete                 : 1;
        U16 tracomplete                 : 1;
        U16 blkgapevent                 : 1;
        U16 dmaint                      : 1;
        U16 bufwready                   : 1;
        U16 bufrready                   : 1;
        U16 cardinsertion               : 1;
        U16 cardremoval                 : 1;
        U16 cardint                     : 1;
        U16 bootackrcv                  : 1;
        U16                             : 5;
        U16 errint                      : 1;
    } bitc;
} GH_SDIO0_NORINTSTAREG_REAL_S;

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
} GH_SDIO0_ERRINTSTAREG_REAL_S;

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
} GH_SDIO0_NORINTSTAENREG_REAL_S;

typedef union { /* SDIO0_ErrIntStaEnReg */
    U16 all;
    struct {
        U16 cmdtimeouterrstatusen       : 1;
        U16 cmdcrcerrstatusen           : 1;
        U16 cmdendbiterrstatusen        : 1;
        U16 cmdindexerrstatusen         : 1;
        U16 datatimeouterrstatusen      : 1;
        U16 datacrcerrstatusen          : 1;
        U16 dataendbiterrstatusen       : 1;
        U16 curlimiterrstatusen         : 1;
        U16 autocmd12errstatusen        : 1;
        U16                             : 5;
        U16 vendorspecificerrstatusen   : 2;
    } bitc;
} GH_SDIO0_ERRINTSTAENREG_REAL_S;

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
} GH_SDIO0_NORINTSIGENREG_REAL_S;

typedef union { /* SDIO0_ErrIntSigEnReg */
    U16 all;
    struct {
        U16 cmdtimeouterrsigen          : 1;
        U16 cmdcrcerrsigen              : 1;
        U16 cmdendbiterrsigen           : 1;
        U16 cmdindexerrsigen            : 1;
        U16 datatimeouterrsigen         : 1;
        U16 datacrcerrsigen             : 1;
        U16 dataendbiterrsigen          : 1;
        U16 curlimiterrsigen            : 1;
        U16 autocmd12errsigen           : 1;
        U16                             : 5;
        U16 vendorspecificerrsigen      : 2;
    } bitc;
} GH_SDIO0_ERRINTSIGENREG_REAL_S;

typedef union { /* SDIO0_AutoCmd12ErrStatusReg */
    U32 all;
    struct {
        U32 autocmd12notexe             : 1;
        U32 autocmd12timeouterr         : 1;
        U32 autocmd12crcerr             : 1;
        U32 autocmd12endbiterr          : 1;
        U32 autocmd12indexerr           : 1;
        U32                             : 2;
        U32 cmdnotissuedbyautocmd12err  : 1;
        U32                             : 24;
    } bitc;
} GH_SDIO0_AUTOCMD12ERRSTATUSREG_REAL_S;

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
        U32 sdmasup                     : 1;
        U32 susressup                   : 1;
        U32 voltagesup33v               : 1;
        U32 voltagesup30v               : 1;
        U32 voltagesup18v               : 1;
        U32 intmode                     : 1;
        U32                             : 4;
    } bitc;
} GH_SDIO0_CAPREG_REAL_S;

typedef union { /* SDIO0_MaxCurCapReg */
    U32 all;
    struct {
        U32 maxcurfor33v                : 8;
        U32 maxcurfor30v                : 8;
        U32 maxcurfor18v                : 8;
        U32                             : 8;
    } bitc;
} GH_SDIO0_MAXCURCAPREG_REAL_S;

typedef union { /* SDIO0_SlotIntStatusReg */
    U32 all;
    struct {
        U32 intsigforeachslot           : 8;
        U32                             : 8;
        U32 specifivernum               : 8;
        U32 vendorvernum                : 8;
    } bitc;
} GH_SDIO0_SLOTINTSTATUSREG_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register SDIO0_SysAddrReg (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_SysAddrReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_SYSADDRREG_REAL = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_SysAddrReg] <-- 0x%08x\n",
                        REG_SDIO0_SYSADDRREG,value,value);
    #endif
}
GH_INLINE U32  GH_SDIO0_get_SysAddrReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_SYSADDRREG_REAL);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SysAddrReg] --> 0x%08x\n",
                        REG_SDIO0_SYSADDRREG,value);
    #endif
    return value;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_TranModeReg (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_TranModeReg(U16 data)
{
    GH_SDIO0_TRANMODEREG_REAL_S tranmodereg_real;
    GH_SDIO0_TRANMODEREG_S dummy;
    dummy.all = data ;
    tranmodereg_real.all = (*(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL);
    tranmodereg_real.bitc.blkcounten = dummy.bitc.blkcounten;
    tranmodereg_real.bitc.autocmd12en = dummy.bitc.autocmd12en;
    tranmodereg_real.bitc.dmaen = dummy.bitc.dmaen;
    tranmodereg_real.bitc.msblkselect = dummy.bitc.msblkselect;
    tranmodereg_real.bitc.datatradirselect = dummy.bitc.datatradirselect;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL = tranmodereg_real.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,dummy.all,dummy.all);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_TranModeReg(void)
{
    GH_SDIO0_TRANMODEREG_REAL_S tranmodereg_real;
    GH_SDIO0_TRANMODEREG_S dummy;
    tranmodereg_real.all = (*(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL);

    dummy.bitc.blkcounten = tranmodereg_real.bitc.blkcounten;
    dummy.bitc.autocmd12en = tranmodereg_real.bitc.autocmd12en;
    dummy.bitc.dmaen = tranmodereg_real.bitc.dmaen;
    dummy.bitc.msblkselect = tranmodereg_real.bitc.msblkselect;
    dummy.bitc.datatradirselect = tranmodereg_real.bitc.datatradirselect;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE void GH_SDIO0_set_TranModeReg_BlkCountEn(U8 data)
{
    GH_SDIO0_TRANMODEREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL;
    d.bitc.blkcounten = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_BlkCountEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_TranModeReg_BlkCountEn(void)
{
    GH_SDIO0_TRANMODEREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_BlkCountEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.blkcounten;
}
GH_INLINE void GH_SDIO0_set_TranModeReg_AutoCmd12En(U8 data)
{
    GH_SDIO0_TRANMODEREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL;
    d.bitc.autocmd12en = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_AutoCmd12En] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_TranModeReg_AutoCmd12En(void)
{
    GH_SDIO0_TRANMODEREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_AutoCmd12En] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.autocmd12en;
}
GH_INLINE void GH_SDIO0_set_TranModeReg_DmaEn(U8 data)
{
    GH_SDIO0_TRANMODEREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL;
    d.bitc.dmaen = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_DmaEn] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_TranModeReg_DmaEn(void)
{
    GH_SDIO0_TRANMODEREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_DmaEn] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.dmaen;
}
GH_INLINE void GH_SDIO0_set_TranModeReg_MSBlkSelect(U8 data)
{
    GH_SDIO0_TRANMODEREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL;
    d.bitc.msblkselect = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_MSBlkSelect] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_TranModeReg_MSBlkSelect(void)
{
    GH_SDIO0_TRANMODEREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_MSBlkSelect] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.msblkselect;
}
GH_INLINE void GH_SDIO0_set_TranModeReg_DataTraDirSelect(U8 data)
{
    GH_SDIO0_TRANMODEREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL;
    d.bitc.datatradirselect = data;
    *(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_TranModeReg_DataTraDirSelect] <-- 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_TranModeReg_DataTraDirSelect(void)
{
    GH_SDIO0_TRANMODEREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_TRANMODEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_TranModeReg_DataTraDirSelect] --> 0x%08x\n",
                        REG_SDIO0_TRANMODEREG,value);
    #endif
    return tmp_value.bitc.datatradirselect;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_NorIntSigEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg(U16 data)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S norintsigenreg_real;
    GH_SDIO0_NORINTSIGENREG_S dummy;
    dummy.all = data ;
    norintsigenreg_real.all = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL);
    norintsigenreg_real.bitc.cmdcompletesigen = dummy.bitc.cmdcompletesigen;
    norintsigenreg_real.bitc.tracompletesigen = dummy.bitc.tracompletesigen;
    norintsigenreg_real.bitc.blkgapevesigen = dummy.bitc.blkgapevesigen;
    norintsigenreg_real.bitc.dmaintsigen = dummy.bitc.dmaintsigen;
    norintsigenreg_real.bitc.bufwreadysigen = dummy.bitc.bufwreadysigen;
    norintsigenreg_real.bitc.bufrreadysigen = dummy.bitc.bufrreadysigen;
    norintsigenreg_real.bitc.cardinsertionsigen = dummy.bitc.cardinsertionsigen;
    norintsigenreg_real.bitc.cardremsigen = dummy.bitc.cardremsigen;
    norintsigenreg_real.bitc.cardintsigen = dummy.bitc.cardintsigen;
    norintsigenreg_real.bitc.fixedto0 = dummy.bitc.fixedto0;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL = norintsigenreg_real.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,dummy.all,dummy.all);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_NorIntSigEnReg(void)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S norintsigenreg_real;
    GH_SDIO0_NORINTSIGENREG_S dummy;
    norintsigenreg_real.all = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL);

    dummy.bitc.cmdcompletesigen = norintsigenreg_real.bitc.cmdcompletesigen;
    dummy.bitc.tracompletesigen = norintsigenreg_real.bitc.tracompletesigen;
    dummy.bitc.blkgapevesigen = norintsigenreg_real.bitc.blkgapevesigen;
    dummy.bitc.dmaintsigen = norintsigenreg_real.bitc.dmaintsigen;
    dummy.bitc.bufwreadysigen = norintsigenreg_real.bitc.bufwreadysigen;
    dummy.bitc.bufrreadysigen = norintsigenreg_real.bitc.bufrreadysigen;
    dummy.bitc.cardinsertionsigen = norintsigenreg_real.bitc.cardinsertionsigen;
    dummy.bitc.cardremsigen = norintsigenreg_real.bitc.cardremsigen;
    dummy.bitc.cardintsigen = norintsigenreg_real.bitc.cardintsigen;
    dummy.bitc.fixedto0 = norintsigenreg_real.bitc.fixedto0;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_CmdCompleteSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL;
    d.bitc.cmdcompletesigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_CmdCompleteSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_CmdCompleteSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_CmdCompleteSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cmdcompletesigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_TraCompleteSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL;
    d.bitc.tracompletesigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_TraCompleteSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_TraCompleteSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_TraCompleteSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.tracompletesigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_BlkGapEveSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL;
    d.bitc.blkgapevesigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_BlkGapEveSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_BlkGapEveSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_BlkGapEveSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.blkgapevesigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_DmaIntSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL;
    d.bitc.dmaintsigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_DmaIntSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_DmaIntSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_DmaIntSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.dmaintsigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_BufWReadySigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL;
    d.bitc.bufwreadysigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_BufWReadySigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_BufWReadySigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_BufWReadySigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.bufwreadysigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_BufRReadySigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL;
    d.bitc.bufrreadysigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_BufRReadySigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_BufRReadySigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_BufRReadySigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.bufrreadysigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_CardInsertionSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL;
    d.bitc.cardinsertionsigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_CardInsertionSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_CardInsertionSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_CardInsertionSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardinsertionsigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_CardRemSigEn(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL;
    d.bitc.cardremsigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_CardRemSigEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_CardRemSigEn(void)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_CardRemSigEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardremsigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_CardIntSigEN(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL;
    d.bitc.cardintsigen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_CardIntSigEN] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_CardIntSigEN(void)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_CardIntSigEN] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.cardintsigen;
}
GH_INLINE void GH_SDIO0_set_NorIntSigEnReg_FixedTo0(U8 data)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL;
    d.bitc.fixedto0 = data;
    *(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntSigEnReg_FixedTo0] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntSigEnReg_FixedTo0(void)
{
    GH_SDIO0_NORINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntSigEnReg_FixedTo0] --> 0x%08x\n",
                        REG_SDIO0_NORINTSIGENREG,value);
    #endif
    return tmp_value.bitc.fixedto0;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntSigEn (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_ErrIntSigEn(U16 data)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S errintsigenreg_real;
    GH_SDIO0_ERRINTSIGEN_S dummy;
    dummy.all = data ;
    errintsigenreg_real.all = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL);
    errintsigenreg_real.bitc.cmdtimeouterrsigen = dummy.bitc.cmdtimeouterrsigen;
    errintsigenreg_real.bitc.cmdendbiterrsigen = dummy.bitc.cmdendbiterrsigen;
    errintsigenreg_real.bitc.cmdindexerrsigen = dummy.bitc.cmdindexerrsigen;
    errintsigenreg_real.bitc.datatimeouterrsigen = dummy.bitc.datatimeouterrsigen;
    errintsigenreg_real.bitc.cmdcrcerrsigen = dummy.bitc.cmdcrcerrsigen;
    errintsigenreg_real.bitc.datacrcerrsigen = dummy.bitc.datacrcerrsigen;
    errintsigenreg_real.bitc.dataendbiterrsigen = dummy.bitc.dataendbiterrsigen;
    errintsigenreg_real.bitc.curlimiterrsigen = dummy.bitc.curlimiterrsigen;
    errintsigenreg_real.bitc.autocmd12errsigen = dummy.bitc.autocmd12errsigen;
    errintsigenreg_real.bitc.vendorspecificerrsigen = dummy.bitc.vendorspecificerrsigen;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL = errintsigenreg_real.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,dummy.all,dummy.all);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_ErrIntSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S errintsigenreg_real;
    GH_SDIO0_ERRINTSIGEN_S dummy;
    errintsigenreg_real.all = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL);

    dummy.bitc.cmdtimeouterrsigen = errintsigenreg_real.bitc.cmdtimeouterrsigen;
    dummy.bitc.cmdendbiterrsigen = errintsigenreg_real.bitc.cmdendbiterrsigen;
    dummy.bitc.cmdindexerrsigen = errintsigenreg_real.bitc.cmdindexerrsigen;
    dummy.bitc.datatimeouterrsigen = errintsigenreg_real.bitc.datatimeouterrsigen;
    dummy.bitc.cmdcrcerrsigen = errintsigenreg_real.bitc.cmdcrcerrsigen;
    dummy.bitc.datacrcerrsigen = errintsigenreg_real.bitc.datacrcerrsigen;
    dummy.bitc.dataendbiterrsigen = errintsigenreg_real.bitc.dataendbiterrsigen;
    dummy.bitc.curlimiterrsigen = errintsigenreg_real.bitc.curlimiterrsigen;
    dummy.bitc.autocmd12errsigen = errintsigenreg_real.bitc.autocmd12errsigen;
    dummy.bitc.vendorspecificerrsigen = errintsigenreg_real.bitc.vendorspecificerrsigen;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEn_CmdTimeoutErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL;
    d.bitc.cmdtimeouterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEn_CmdTimeoutErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEn_CmdTimeoutErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEn_CmdTimeoutErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,value);
    #endif
    return tmp_value.bitc.cmdtimeouterrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEn_CmdEndBitErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL;
    d.bitc.cmdendbiterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEn_CmdEndBitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEn_CmdEndBitErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEn_CmdEndBitErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,value);
    #endif
    return tmp_value.bitc.cmdendbiterrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEn_CmdIndexErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL;
    d.bitc.cmdindexerrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEn_CmdIndexErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEn_CmdIndexErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEn_CmdIndexErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,value);
    #endif
    return tmp_value.bitc.cmdindexerrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEn_DataTimeoutErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL;
    d.bitc.datatimeouterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEn_DataTimeoutErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEn_DataTimeoutErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEn_DataTimeoutErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,value);
    #endif
    return tmp_value.bitc.datatimeouterrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEn_CmdCrcErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL;
    d.bitc.cmdcrcerrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEn_CmdCrcErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEn_CmdCrcErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEn_CmdCrcErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,value);
    #endif
    return tmp_value.bitc.cmdcrcerrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEn_DataCrcErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL;
    d.bitc.datacrcerrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEn_DataCrcErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEn_DataCrcErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEn_DataCrcErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,value);
    #endif
    return tmp_value.bitc.datacrcerrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEn_DataEndBitErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL;
    d.bitc.dataendbiterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEn_DataEndBitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEn_DataEndBitErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEn_DataEndBitErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,value);
    #endif
    return tmp_value.bitc.dataendbiterrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEn_CurLimitErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL;
    d.bitc.curlimiterrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEn_CurLimitErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEn_CurLimitErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEn_CurLimitErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,value);
    #endif
    return tmp_value.bitc.curlimiterrsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEn_AutoCmd12ErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL;
    d.bitc.autocmd12errsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEn_AutoCmd12ErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEn_AutoCmd12ErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEn_AutoCmd12ErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,value);
    #endif
    return tmp_value.bitc.autocmd12errsigen;
}
GH_INLINE void GH_SDIO0_set_ErrIntSigEn_VendorSpecificErrSigEn(U8 data)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL;
    d.bitc.vendorspecificerrsigen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntSigEn_VendorSpecificErrSigEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntSigEn_VendorSpecificErrSigEn(void)
{
    GH_SDIO0_ERRINTSIGENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSIGENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntSigEn_VendorSpecificErrSigEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSIGEN,value);
    #endif
    return tmp_value.bitc.vendorspecificerrsigen;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_BlkCouReg (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_BlkCouReg(U16 data)
{
    GH_SDIO0_BLKCOUREG_REAL_S blkcoureg_real;
    GH_SDIO0_BLKCOUREG_S dummy;
    dummy.all = data ;
    blkcoureg_real.all = (*(volatile U16 *)REG_SDIO0_BLKCOUREG_REAL);
    blkcoureg_real.bitc.blkcountforcurtra = dummy.bitc.blkcountforcurtra;
    *(volatile U16 *)REG_SDIO0_BLKCOUREG_REAL = blkcoureg_real.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkCouReg] <-- 0x%08x\n",
                        REG_SDIO0_BLKCOUREG,dummy.all,dummy.all);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_BlkCouReg(void)
{
    GH_SDIO0_BLKCOUREG_REAL_S blkcoureg_real;
    GH_SDIO0_BLKCOUREG_S dummy;
    blkcoureg_real.all = (*(volatile U16 *)REG_SDIO0_BLKCOUREG_REAL);

    dummy.bitc.blkcountforcurtra = blkcoureg_real.bitc.blkcountforcurtra;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkCouReg] --> 0x%08x\n",
                        REG_SDIO0_BLKCOUREG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE void GH_SDIO0_set_BlkCouReg_BlkCountForCurTra(U16 data)
{
    GH_SDIO0_BLKCOUREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_BLKCOUREG_REAL;
    d.bitc.blkcountforcurtra = data;
    *(volatile U16 *)REG_SDIO0_BLKCOUREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkCouReg_BlkCountForCurTra] <-- 0x%08x\n",
                        REG_SDIO0_BLKCOUREG,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_BlkCouReg_BlkCountForCurTra(void)
{
    GH_SDIO0_BLKCOUREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_BLKCOUREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkCouReg_BlkCountForCurTra] --> 0x%08x\n",
                        REG_SDIO0_BLKCOUREG,value);
    #endif
    return tmp_value.bitc.blkcountforcurtra;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_BlkSizeReg (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_BlkSizeReg(U16 data)
{
    GH_SDIO0_BLKSIZEREG_REAL_S blksizereg_real;
    GH_SDIO0_BLKSIZEREG_S dummy;
    dummy.all = data ;
    blksizereg_real.all = (*(volatile U16 *)REG_SDIO0_BLKSIZEREG_REAL);
    blksizereg_real.bitc.trablksize = dummy.bitc.trablksize;
    blksizereg_real.bitc.hostsdmabufsize = dummy.bitc.hostsdmabufsize;
    *(volatile U16 *)REG_SDIO0_BLKSIZEREG_REAL = blksizereg_real.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeReg] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,dummy.all,dummy.all);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_BlkSizeReg(void)
{
    GH_SDIO0_BLKSIZEREG_REAL_S blksizereg_real;
    GH_SDIO0_BLKSIZEREG_S dummy;
    blksizereg_real.all = (*(volatile U16 *)REG_SDIO0_BLKSIZEREG_REAL);

    dummy.bitc.trablksize = blksizereg_real.bitc.trablksize;
    dummy.bitc.hostsdmabufsize = blksizereg_real.bitc.hostsdmabufsize;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeReg] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE void GH_SDIO0_set_BlkSizeReg_TraBlkSize(U16 data)
{
    GH_SDIO0_BLKSIZEREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_BLKSIZEREG_REAL;
    d.bitc.trablksize = data;
    *(volatile U16 *)REG_SDIO0_BLKSIZEREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeReg_TraBlkSize] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_BlkSizeReg_TraBlkSize(void)
{
    GH_SDIO0_BLKSIZEREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_BLKSIZEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeReg_TraBlkSize] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,value);
    #endif
    return tmp_value.bitc.trablksize;
}
GH_INLINE void GH_SDIO0_set_BlkSizeReg_HostSdmaBufSize(U8 data)
{
    GH_SDIO0_BLKSIZEREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_BLKSIZEREG_REAL;
    d.bitc.hostsdmabufsize = data;
    *(volatile U16 *)REG_SDIO0_BLKSIZEREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BlkSizeReg_HostSdmaBufSize] <-- 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_BlkSizeReg_HostSdmaBufSize(void)
{
    GH_SDIO0_BLKSIZEREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_BLKSIZEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BlkSizeReg_HostSdmaBufSize] --> 0x%08x\n",
                        REG_SDIO0_BLKSIZEREG,value);
    #endif
    return tmp_value.bitc.hostsdmabufsize;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_NorIntStaEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg(U16 data)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S norintstaenreg_real;
    GH_SDIO0_NORINTSTAENREG_S dummy;
    dummy.all = data ;
    norintstaenreg_real.all = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL);
    norintstaenreg_real.bitc.cmdcompletestatusen = dummy.bitc.cmdcompletestatusen;
    norintstaenreg_real.bitc.tracompletestatusen = dummy.bitc.tracompletestatusen;
    norintstaenreg_real.bitc.blkgapevestatusen = dummy.bitc.blkgapevestatusen;
    norintstaenreg_real.bitc.dmaintstatusen = dummy.bitc.dmaintstatusen;
    norintstaenreg_real.bitc.bufwreadystatusen = dummy.bitc.bufwreadystatusen;
    norintstaenreg_real.bitc.bufrreadystatusen = dummy.bitc.bufrreadystatusen;
    norintstaenreg_real.bitc.cardinsertionstatusen = dummy.bitc.cardinsertionstatusen;
    norintstaenreg_real.bitc.cardremstatusen = dummy.bitc.cardremstatusen;
    norintstaenreg_real.bitc.cardintstatusen = dummy.bitc.cardintstatusen;
    norintstaenreg_real.bitc.fixedto0 = dummy.bitc.fixedto0;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL = norintstaenreg_real.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,dummy.all,dummy.all);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_NorIntStaEnReg(void)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S norintstaenreg_real;
    GH_SDIO0_NORINTSTAENREG_S dummy;
    norintstaenreg_real.all = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL);

    dummy.bitc.cmdcompletestatusen = norintstaenreg_real.bitc.cmdcompletestatusen;
    dummy.bitc.tracompletestatusen = norintstaenreg_real.bitc.tracompletestatusen;
    dummy.bitc.blkgapevestatusen = norintstaenreg_real.bitc.blkgapevestatusen;
    dummy.bitc.dmaintstatusen = norintstaenreg_real.bitc.dmaintstatusen;
    dummy.bitc.bufwreadystatusen = norintstaenreg_real.bitc.bufwreadystatusen;
    dummy.bitc.bufrreadystatusen = norintstaenreg_real.bitc.bufrreadystatusen;
    dummy.bitc.cardinsertionstatusen = norintstaenreg_real.bitc.cardinsertionstatusen;
    dummy.bitc.cardremstatusen = norintstaenreg_real.bitc.cardremstatusen;
    dummy.bitc.cardintstatusen = norintstaenreg_real.bitc.cardintstatusen;
    dummy.bitc.fixedto0 = norintstaenreg_real.bitc.fixedto0;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_CmdCompleteStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL;
    d.bitc.cmdcompletestatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_CmdCompleteStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_CmdCompleteStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_CmdCompleteStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdcompletestatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_TraCompleteStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL;
    d.bitc.tracompletestatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_TraCompleteStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_TraCompleteStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_TraCompleteStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.tracompletestatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_BlkGapEveStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL;
    d.bitc.blkgapevestatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_BlkGapEveStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_BlkGapEveStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_BlkGapEveStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.blkgapevestatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_DmaIntStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL;
    d.bitc.dmaintstatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_DmaIntStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_DmaIntStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_DmaIntStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.dmaintstatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_BufWReadyStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL;
    d.bitc.bufwreadystatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_BufWReadyStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_BufWReadyStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_BufWReadyStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.bufwreadystatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_BufRReadyStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL;
    d.bitc.bufrreadystatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_BufRReadyStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_BufRReadyStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_BufRReadyStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.bufrreadystatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_CardInsertionStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL;
    d.bitc.cardinsertionstatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_CardInsertionStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_CardInsertionStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_CardInsertionStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardinsertionstatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_CardRemStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL;
    d.bitc.cardremstatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_CardRemStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_CardRemStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_CardRemStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardremstatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_CardIntStatusEn(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL;
    d.bitc.cardintstatusen = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_CardIntStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_CardIntStatusEn(void)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_CardIntStatusEn] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cardintstatusen;
}
GH_INLINE void GH_SDIO0_set_NorIntStaEnReg_FixedTo0(U8 data)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL;
    d.bitc.fixedto0 = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaEnReg_FixedTo0] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaEnReg_FixedTo0(void)
{
    GH_SDIO0_NORINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaEnReg_FixedTo0] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAENREG,value);
    #endif
    return tmp_value.bitc.fixedto0;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntStaEnReg (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg(U16 data)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S errintstaenreg_real;
    GH_SDIO0_ERRINTSTAENREG_S dummy;
    dummy.all = data ;
    errintstaenreg_real.all = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL);
    errintstaenreg_real.bitc.cmdtimeouterrstatusen = dummy.bitc.cmdtimeouterrstatusen;
    errintstaenreg_real.bitc.cmdendbiterrstatusen = dummy.bitc.cmdendbiterrstatusen;
    errintstaenreg_real.bitc.cmdcrcerrstatusen = dummy.bitc.cmdcrcerrstatusen;
    errintstaenreg_real.bitc.cmdindexerrstatusen = dummy.bitc.cmdindexerrstatusen;
    errintstaenreg_real.bitc.datacrcerrstatusen = dummy.bitc.datacrcerrstatusen;
    errintstaenreg_real.bitc.datatimeouterrstatusen = dummy.bitc.datatimeouterrstatusen;
    errintstaenreg_real.bitc.dataendbiterrstatusen = dummy.bitc.dataendbiterrstatusen;
    errintstaenreg_real.bitc.curlimiterrstatusen = dummy.bitc.curlimiterrstatusen;
    errintstaenreg_real.bitc.autocmd12errstatusen = dummy.bitc.autocmd12errstatusen;
    errintstaenreg_real.bitc.vendorspecificerrstatusen = dummy.bitc.vendorspecificerrstatusen;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL = errintstaenreg_real.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,dummy.all,dummy.all);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_ErrIntStaEnReg(void)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S errintstaenreg_real;
    GH_SDIO0_ERRINTSTAENREG_S dummy;
    errintstaenreg_real.all = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL);

    dummy.bitc.cmdtimeouterrstatusen = errintstaenreg_real.bitc.cmdtimeouterrstatusen;
    dummy.bitc.cmdendbiterrstatusen = errintstaenreg_real.bitc.cmdendbiterrstatusen;
    dummy.bitc.cmdcrcerrstatusen = errintstaenreg_real.bitc.cmdcrcerrstatusen;
    dummy.bitc.cmdindexerrstatusen = errintstaenreg_real.bitc.cmdindexerrstatusen;
    dummy.bitc.datacrcerrstatusen = errintstaenreg_real.bitc.datacrcerrstatusen;
    dummy.bitc.datatimeouterrstatusen = errintstaenreg_real.bitc.datatimeouterrstatusen;
    dummy.bitc.dataendbiterrstatusen = errintstaenreg_real.bitc.dataendbiterrstatusen;
    dummy.bitc.curlimiterrstatusen = errintstaenreg_real.bitc.curlimiterrstatusen;
    dummy.bitc.autocmd12errstatusen = errintstaenreg_real.bitc.autocmd12errstatusen;
    dummy.bitc.vendorspecificerrstatusen = errintstaenreg_real.bitc.vendorspecificerrstatusen;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL;
    d.bitc.cmdtimeouterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CmdTimeoutErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CmdTimeoutErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdtimeouterrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_CmdEndBitErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL;
    d.bitc.cmdendbiterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CmdEndBitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_CmdEndBitErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CmdEndBitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdendbiterrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_CmdCrcErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL;
    d.bitc.cmdcrcerrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CmdCrcErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_CmdCrcErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CmdCrcErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdcrcerrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_CmdIndexErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL;
    d.bitc.cmdindexerrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CmdIndexErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_CmdIndexErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CmdIndexErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.cmdindexerrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_DataCrcErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL;
    d.bitc.datacrcerrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_DataCrcErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_DataCrcErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_DataCrcErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.datacrcerrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_DataTimeoutErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL;
    d.bitc.datatimeouterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_DataTimeoutErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_DataTimeoutErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_DataTimeoutErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.datatimeouterrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_DataEndBitErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL;
    d.bitc.dataendbiterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_DataEndBitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_DataEndBitErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_DataEndBitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.dataendbiterrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_CurLimitErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL;
    d.bitc.curlimiterrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_CurLimitErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_CurLimitErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_CurLimitErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.curlimiterrstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL;
    d.bitc.autocmd12errstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_AutoCmd12ErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_AutoCmd12ErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.autocmd12errstatusen;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaEnReg_VendorSpecificErrStatusEn(U8 data)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL;
    d.bitc.vendorspecificerrstatusen = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaEnReg_VendorSpecificErrStatusEn] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaEnReg_VendorSpecificErrStatusEn(void)
{
    GH_SDIO0_ERRINTSTAENREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAENREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaEnReg_VendorSpecificErrStatusEn] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAENREG,value);
    #endif
    return tmp_value.bitc.vendorspecificerrstatusen;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_NorIntStaReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_NorIntStaReg(U16 data)
{
    GH_SDIO0_NORINTSTAREG_REAL_S norintstareg_real;
    GH_SDIO0_NORINTSTAREG_S dummy;
    dummy.all = data ;
    norintstareg_real.all = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL);
    norintstareg_real.bitc.cmdcomplete = dummy.bitc.cmdcomplete;
    norintstareg_real.bitc.blkgapevent = dummy.bitc.blkgapevent;
    norintstareg_real.bitc.dmaint = dummy.bitc.dmaint;
    norintstareg_real.bitc.tracomplete = dummy.bitc.tracomplete;
    norintstareg_real.bitc.bufwready = dummy.bitc.bufwready;
    norintstareg_real.bitc.cardinsertion = dummy.bitc.cardinsertion;
    norintstareg_real.bitc.bufrready = dummy.bitc.bufrready;
    norintstareg_real.bitc.cardremoval = dummy.bitc.cardremoval;
    norintstareg_real.bitc.cardint = dummy.bitc.cardint;
    norintstareg_real.bitc.bootackrcv = dummy.bitc.bootackrcv;
    norintstareg_real.bitc.errint = dummy.bitc.errint;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL = norintstareg_real.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,dummy.all,dummy.all);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_NorIntStaReg(void)
{
    GH_SDIO0_NORINTSTAREG_REAL_S norintstareg_real;
    GH_SDIO0_NORINTSTAREG_S dummy;
    norintstareg_real.all = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL);

    dummy.bitc.cmdcomplete = norintstareg_real.bitc.cmdcomplete;
    dummy.bitc.blkgapevent = norintstareg_real.bitc.blkgapevent;
    dummy.bitc.dmaint = norintstareg_real.bitc.dmaint;
    dummy.bitc.tracomplete = norintstareg_real.bitc.tracomplete;
    dummy.bitc.bufwready = norintstareg_real.bitc.bufwready;
    dummy.bitc.cardinsertion = norintstareg_real.bitc.cardinsertion;
    dummy.bitc.bufrready = norintstareg_real.bitc.bufrready;
    dummy.bitc.cardremoval = norintstareg_real.bitc.cardremoval;
    dummy.bitc.cardint = norintstareg_real.bitc.cardint;
    dummy.bitc.bootackrcv = norintstareg_real.bitc.bootackrcv;
    dummy.bitc.errint = norintstareg_real.bitc.errint;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_CmdComplete(U8 data)
{
    GH_SDIO0_NORINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL;
    d.bitc.cmdcomplete = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_CmdComplete] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_CmdComplete(void)
{
    GH_SDIO0_NORINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_CmdComplete] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdcomplete;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_BlkGapEvent(U8 data)
{
    GH_SDIO0_NORINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL;
    d.bitc.blkgapevent = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_BlkGapEvent] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_BlkGapEvent(void)
{
    GH_SDIO0_NORINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_BlkGapEvent] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.blkgapevent;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_DmaInt(U8 data)
{
    GH_SDIO0_NORINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL;
    d.bitc.dmaint = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_DmaInt] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_DmaInt(void)
{
    GH_SDIO0_NORINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_DmaInt] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.dmaint;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_TraComplete(U8 data)
{
    GH_SDIO0_NORINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL;
    d.bitc.tracomplete = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_TraComplete] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_TraComplete(void)
{
    GH_SDIO0_NORINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_TraComplete] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.tracomplete;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_BufWReady(U8 data)
{
    GH_SDIO0_NORINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL;
    d.bitc.bufwready = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_BufWReady] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_BufWReady(void)
{
    GH_SDIO0_NORINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_BufWReady] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bufwready;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_CardInsertion(U8 data)
{
    GH_SDIO0_NORINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL;
    d.bitc.cardinsertion = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_CardInsertion] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_CardInsertion(void)
{
    GH_SDIO0_NORINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_CardInsertion] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardinsertion;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_BufRReady(U8 data)
{
    GH_SDIO0_NORINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL;
    d.bitc.bufrready = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_BufRReady] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_BufRReady(void)
{
    GH_SDIO0_NORINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_BufRReady] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bufrready;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_CardRemoval(U8 data)
{
    GH_SDIO0_NORINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL;
    d.bitc.cardremoval = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_CardRemoval] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_CardRemoval(void)
{
    GH_SDIO0_NORINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_CardRemoval] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardremoval;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_CardInt(U8 data)
{
    GH_SDIO0_NORINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL;
    d.bitc.cardint = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_CardInt] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_CardInt(void)
{
    GH_SDIO0_NORINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_CardInt] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.cardint;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_BootAckRcv(U8 data)
{
    GH_SDIO0_NORINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL;
    d.bitc.bootackrcv = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_BootAckRcv] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_BootAckRcv(void)
{
    GH_SDIO0_NORINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_BootAckRcv] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.bootackrcv;
}
GH_INLINE void GH_SDIO0_set_NorIntStaReg_ErrInt(U8 data)
{
    GH_SDIO0_NORINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL;
    d.bitc.errint = data;
    *(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_NorIntStaReg_ErrInt] <-- 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_NorIntStaReg_ErrInt(void)
{
    GH_SDIO0_NORINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_NORINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_NorIntStaReg_ErrInt] --> 0x%08x\n",
                        REG_SDIO0_NORINTSTAREG,value);
    #endif
    return tmp_value.bitc.errint;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_ErrIntStaReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_ErrIntStaReg(U16 data)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S errintstareg_real;
    GH_SDIO0_ERRINTSTAREG_S dummy;
    dummy.all = data ;
    errintstareg_real.all = (*(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL);
    errintstareg_real.bitc.cmdtimeouterr = dummy.bitc.cmdtimeouterr;
    errintstareg_real.bitc.cmdcrcerr = dummy.bitc.cmdcrcerr;
    errintstareg_real.bitc.cmdendbiterr = dummy.bitc.cmdendbiterr;
    errintstareg_real.bitc.cmdindexerr = dummy.bitc.cmdindexerr;
    errintstareg_real.bitc.datatimeouterr = dummy.bitc.datatimeouterr;
    errintstareg_real.bitc.datacrcerr = dummy.bitc.datacrcerr;
    errintstareg_real.bitc.dataendbiterr = dummy.bitc.dataendbiterr;
    errintstareg_real.bitc.curlimiterr = dummy.bitc.curlimiterr;
    errintstareg_real.bitc.autocmd12err = dummy.bitc.autocmd12err;
    errintstareg_real.bitc.vendorspecificerrstatus = dummy.bitc.vendorspecificerrstatus;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL = errintstareg_real.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaReg] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,dummy.all,dummy.all);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_ErrIntStaReg(void)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S errintstareg_real;
    GH_SDIO0_ERRINTSTAREG_S dummy;
    errintstareg_real.all = (*(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL);

    dummy.bitc.cmdtimeouterr = errintstareg_real.bitc.cmdtimeouterr;
    dummy.bitc.cmdcrcerr = errintstareg_real.bitc.cmdcrcerr;
    dummy.bitc.cmdendbiterr = errintstareg_real.bitc.cmdendbiterr;
    dummy.bitc.cmdindexerr = errintstareg_real.bitc.cmdindexerr;
    dummy.bitc.datatimeouterr = errintstareg_real.bitc.datatimeouterr;
    dummy.bitc.datacrcerr = errintstareg_real.bitc.datacrcerr;
    dummy.bitc.dataendbiterr = errintstareg_real.bitc.dataendbiterr;
    dummy.bitc.curlimiterr = errintstareg_real.bitc.curlimiterr;
    dummy.bitc.autocmd12err = errintstareg_real.bitc.autocmd12err;
    dummy.bitc.vendorspecificerrstatus = errintstareg_real.bitc.vendorspecificerrstatus;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaReg] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaReg_CmdTimeoutErr(U8 data)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL;
    d.bitc.cmdtimeouterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaReg_CmdTimeoutErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaReg_CmdTimeoutErr(void)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaReg_CmdTimeoutErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdtimeouterr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaReg_CmdCrcErr(U8 data)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL;
    d.bitc.cmdcrcerr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaReg_CmdCrcErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaReg_CmdCrcErr(void)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaReg_CmdCrcErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdcrcerr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaReg_CmdEndBitErr(U8 data)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL;
    d.bitc.cmdendbiterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaReg_CmdEndBitErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaReg_CmdEndBitErr(void)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaReg_CmdEndBitErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdendbiterr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaReg_CmdIndexErr(U8 data)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL;
    d.bitc.cmdindexerr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaReg_CmdIndexErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaReg_CmdIndexErr(void)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaReg_CmdIndexErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,value);
    #endif
    return tmp_value.bitc.cmdindexerr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaReg_DataTimeoutErr(U8 data)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL;
    d.bitc.datatimeouterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaReg_DataTimeoutErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaReg_DataTimeoutErr(void)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaReg_DataTimeoutErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,value);
    #endif
    return tmp_value.bitc.datatimeouterr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaReg_DataCrcErr(U8 data)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL;
    d.bitc.datacrcerr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaReg_DataCrcErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaReg_DataCrcErr(void)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaReg_DataCrcErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,value);
    #endif
    return tmp_value.bitc.datacrcerr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaReg_DataEndBitErr(U8 data)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL;
    d.bitc.dataendbiterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaReg_DataEndBitErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaReg_DataEndBitErr(void)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaReg_DataEndBitErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,value);
    #endif
    return tmp_value.bitc.dataendbiterr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaReg_CurLimitErr(U8 data)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL;
    d.bitc.curlimiterr = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaReg_CurLimitErr] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaReg_CurLimitErr(void)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaReg_CurLimitErr] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,value);
    #endif
    return tmp_value.bitc.curlimiterr;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaReg_AutoCmd12Err(U8 data)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL;
    d.bitc.autocmd12err = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaReg_AutoCmd12Err] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaReg_AutoCmd12Err(void)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaReg_AutoCmd12Err] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,value);
    #endif
    return tmp_value.bitc.autocmd12err;
}
GH_INLINE void GH_SDIO0_set_ErrIntStaReg_VendorSpecificErrStatus(U8 data)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL;
    d.bitc.vendorspecificerrstatus = data;
    *(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ErrIntStaReg_VendorSpecificErrStatus] <-- 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_ErrIntStaReg_VendorSpecificErrStatus(void)
{
    GH_SDIO0_ERRINTSTAREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_ERRINTSTAREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ErrIntStaReg_VendorSpecificErrStatus] --> 0x%08x\n",
                        REG_SDIO0_ERRINTSTAREG,value);
    #endif
    return tmp_value.bitc.vendorspecificerrstatus;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_CmdReg (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_CmdReg(U16 data)
{
    GH_SDIO0_CMDREG_REAL_S cmdreg_real;
    GH_SDIO0_CMDREG_S dummy;
    dummy.all = data ;
    cmdreg_real.all = (*(volatile U16 *)REG_SDIO0_CMDREG_REAL);
    cmdreg_real.bitc.reptypeselect = dummy.bitc.reptypeselect;
    cmdreg_real.bitc.cmdcrcchecken = dummy.bitc.cmdcrcchecken;
    cmdreg_real.bitc.datapreselect = dummy.bitc.datapreselect;
    cmdreg_real.bitc.cmdindexchecken = dummy.bitc.cmdindexchecken;
    cmdreg_real.bitc.cmdtype = dummy.bitc.cmdtype;
    cmdreg_real.bitc.cmdindex = dummy.bitc.cmdindex;
    *(volatile U16 *)REG_SDIO0_CMDREG_REAL = cmdreg_real.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CmdReg] <-- 0x%08x\n",
                        REG_SDIO0_CMDREG,dummy.all,dummy.all);
    #endif
}
GH_INLINE U16  GH_SDIO0_get_CmdReg(void)
{
    GH_SDIO0_CMDREG_REAL_S cmdreg_real;
    GH_SDIO0_CMDREG_S dummy;
    cmdreg_real.all = (*(volatile U16 *)REG_SDIO0_CMDREG_REAL);

    dummy.bitc.reptypeselect = cmdreg_real.bitc.reptypeselect;
    dummy.bitc.cmdcrcchecken = cmdreg_real.bitc.cmdcrcchecken;
    dummy.bitc.datapreselect = cmdreg_real.bitc.datapreselect;
    dummy.bitc.cmdindexchecken = cmdreg_real.bitc.cmdindexchecken;
    dummy.bitc.cmdtype = cmdreg_real.bitc.cmdtype;
    dummy.bitc.cmdindex = cmdreg_real.bitc.cmdindex;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CmdReg] --> 0x%08x\n",
                        REG_SDIO0_CMDREG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE void GH_SDIO0_set_CmdReg_RepTypeSelect(U8 data)
{
    GH_SDIO0_CMDREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_CMDREG_REAL;
    d.bitc.reptypeselect = data;
    *(volatile U16 *)REG_SDIO0_CMDREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CmdReg_RepTypeSelect] <-- 0x%08x\n",
                        REG_SDIO0_CMDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_CmdReg_RepTypeSelect(void)
{
    GH_SDIO0_CMDREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_CMDREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CmdReg_RepTypeSelect] --> 0x%08x\n",
                        REG_SDIO0_CMDREG,value);
    #endif
    return tmp_value.bitc.reptypeselect;
}
GH_INLINE void GH_SDIO0_set_CmdReg_CmdCrcCheckEn(U8 data)
{
    GH_SDIO0_CMDREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_CMDREG_REAL;
    d.bitc.cmdcrcchecken = data;
    *(volatile U32 *)REG_SDIO0_CMDREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CmdReg_CmdCrcCheckEn] <-- 0x%08x\n",
                        REG_SDIO0_CMDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_CmdReg_CmdCrcCheckEn(void)
{
    GH_SDIO0_CMDREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_CMDREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CmdReg_CmdCrcCheckEn] --> 0x%08x\n",
                        REG_SDIO0_CMDREG,value);
    #endif
    return tmp_value.bitc.cmdcrcchecken;
}
GH_INLINE void GH_SDIO0_set_CmdReg_DataPreSelect(U8 data)
{
    GH_SDIO0_CMDREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_CMDREG_REAL;
    d.bitc.datapreselect = data;
    *(volatile U16 *)REG_SDIO0_CMDREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CmdReg_DataPreSelect] <-- 0x%08x\n",
                        REG_SDIO0_CMDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_CmdReg_DataPreSelect(void)
{
    GH_SDIO0_CMDREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_CMDREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CmdReg_DataPreSelect] --> 0x%08x\n",
                        REG_SDIO0_CMDREG,value);
    #endif
    return tmp_value.bitc.datapreselect;
}
GH_INLINE void GH_SDIO0_set_CmdReg_CmdIndexCheckEn(U8 data)
{
    GH_SDIO0_CMDREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_CMDREG_REAL;
    d.bitc.cmdindexchecken = data;
    *(volatile U16 *)REG_SDIO0_CMDREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CmdReg_CmdIndexCheckEn] <-- 0x%08x\n",
                        REG_SDIO0_CMDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_CmdReg_CmdIndexCheckEn(void)
{
    GH_SDIO0_CMDREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_CMDREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CmdReg_CmdIndexCheckEn] --> 0x%08x\n",
                        REG_SDIO0_CMDREG,value);
    #endif
    return tmp_value.bitc.cmdindexchecken;
}
GH_INLINE void GH_SDIO0_set_CmdReg_CmdType(U8 data)
{
    GH_SDIO0_CMDREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_CMDREG_REAL;
    d.bitc.cmdtype = data;
    *(volatile U16 *)REG_SDIO0_CMDREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CmdReg_CmdType] <-- 0x%08x\n",
                        REG_SDIO0_CMDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_CmdReg_CmdType(void)
{
    GH_SDIO0_CMDREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_CMDREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CmdReg_CmdType] --> 0x%08x\n",
                        REG_SDIO0_CMDREG,value);
    #endif
    return tmp_value.bitc.cmdtype;
}
GH_INLINE void GH_SDIO0_set_CmdReg_CmdIndex(U8 data)
{
    GH_SDIO0_CMDREG_REAL_S d;
    d.all = *(volatile U16 *)REG_SDIO0_CMDREG_REAL;
    d.bitc.cmdindex = data;
    *(volatile U16 *)REG_SDIO0_CMDREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_CmdReg_CmdIndex] <-- 0x%08x\n",
                        REG_SDIO0_CMDREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_CmdReg_CmdIndex(void)
{
    GH_SDIO0_CMDREG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_SDIO0_CMDREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CmdReg_CmdIndex] --> 0x%08x\n",
                        REG_SDIO0_CMDREG,value);
    #endif
    return tmp_value.bitc.cmdindex;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_Control01Reg (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_Control01Reg(U32 data)
{
    GH_SDIO0_CONTROL01REG_REAL_S control01reg_real;
    GH_SDIO0_CONTROL01REG_S dummy;
    dummy.all = data ;
    control01reg_real.all = (*(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL);
    control01reg_real.bitc.datatimeoutcountervalue = dummy.bitc.datatimeoutcountervalue;
    control01reg_real.bitc.softwareresetcmdline = dummy.bitc.softwareresetcmdline;
    control01reg_real.bitc.softwareresetall = dummy.bitc.softwareresetall;
    control01reg_real.bitc.softwareresetdatline = dummy.bitc.softwareresetdatline;
    control01reg_real.bitc.internalclken = dummy.bitc.internalclken;
    control01reg_real.bitc.internalclkstable = dummy.bitc.internalclkstable;
    control01reg_real.bitc.sdclken = dummy.bitc.sdclken;
    control01reg_real.bitc.sdclkfreselect = dummy.bitc.sdclkfreselect;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL = control01reg_real.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,dummy.all,dummy.all);
    #endif
}
GH_INLINE U32  GH_SDIO0_get_Control01Reg(void)
{
    GH_SDIO0_CONTROL01REG_REAL_S control01reg_real;
    GH_SDIO0_CONTROL01REG_S dummy;
    control01reg_real.all = (*(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL);

    dummy.bitc.datatimeoutcountervalue = control01reg_real.bitc.datatimeoutcountervalue;
    dummy.bitc.softwareresetcmdline = control01reg_real.bitc.softwareresetcmdline;
    dummy.bitc.softwareresetall = control01reg_real.bitc.softwareresetall;
    dummy.bitc.softwareresetdatline = control01reg_real.bitc.softwareresetdatline;
    dummy.bitc.internalclken = control01reg_real.bitc.internalclken;
    dummy.bitc.internalclkstable = control01reg_real.bitc.internalclkstable;
    dummy.bitc.sdclken = control01reg_real.bitc.sdclken;
    dummy.bitc.sdclkfreselect = control01reg_real.bitc.sdclkfreselect;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE void GH_SDIO0_set_Control01Reg_DataTimeoutCounterValue(U8 data)
{
    GH_SDIO0_CONTROL01REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL;
    d.bitc.datatimeoutcountervalue = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_DataTimeoutCounterValue] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control01Reg_DataTimeoutCounterValue(void)
{
    GH_SDIO0_CONTROL01REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_DataTimeoutCounterValue] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.datatimeoutcountervalue;
}
GH_INLINE void GH_SDIO0_set_Control01Reg_SoftwareResetCmdLine(U8 data)
{
    GH_SDIO0_CONTROL01REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL;
    d.bitc.softwareresetcmdline = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_SoftwareResetCmdLine] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control01Reg_SoftwareResetCmdLine(void)
{
    GH_SDIO0_CONTROL01REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_SoftwareResetCmdLine] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.softwareresetcmdline;
}
GH_INLINE void GH_SDIO0_set_Control01Reg_SoftwareResetAll(U8 data)
{
    GH_SDIO0_CONTROL01REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL;
    d.bitc.softwareresetall = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_SoftwareResetAll] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control01Reg_SoftwareResetAll(void)
{
    GH_SDIO0_CONTROL01REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_SoftwareResetAll] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.softwareresetall;
}
GH_INLINE void GH_SDIO0_set_Control01Reg_SoftwareResetDatLine(U8 data)
{
    GH_SDIO0_CONTROL01REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL;
    d.bitc.softwareresetdatline = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_SoftwareResetDatLine] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control01Reg_SoftwareResetDatLine(void)
{
    GH_SDIO0_CONTROL01REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_SoftwareResetDatLine] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.softwareresetdatline;
}
GH_INLINE void GH_SDIO0_set_Control01Reg_InternalClkEn(U8 data)
{
    GH_SDIO0_CONTROL01REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL;
    d.bitc.internalclken = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_InternalClkEn] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control01Reg_InternalClkEn(void)
{
    GH_SDIO0_CONTROL01REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_InternalClkEn] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.internalclken;
}
GH_INLINE void GH_SDIO0_set_Control01Reg_InternalClkStable(U8 data)
{
    GH_SDIO0_CONTROL01REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL;
    d.bitc.internalclkstable = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_InternalClkStable] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control01Reg_InternalClkStable(void)
{
    GH_SDIO0_CONTROL01REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_InternalClkStable] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.internalclkstable;
}
GH_INLINE void GH_SDIO0_set_Control01Reg_SdClkEn(U8 data)
{
    GH_SDIO0_CONTROL01REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL;
    d.bitc.sdclken = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_SdClkEn] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control01Reg_SdClkEn(void)
{
    GH_SDIO0_CONTROL01REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_SdClkEn] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.sdclken;
}
GH_INLINE void GH_SDIO0_set_Control01Reg_SdclkFreSelect(U8 data)
{
    GH_SDIO0_CONTROL01REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL;
    d.bitc.sdclkfreselect = data;
    *(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control01Reg_SdclkFreSelect] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control01Reg_SdclkFreSelect(void)
{
    GH_SDIO0_CONTROL01REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL01REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control01Reg_SdclkFreSelect] --> 0x%08x\n",
                        REG_SDIO0_CONTROL01REG,value);
    #endif
    return tmp_value.bitc.sdclkfreselect;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp0Reg (read)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO0_get_Resp0Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_RESP0REG_REAL);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Resp0Reg] --> 0x%08x\n",
                        REG_SDIO0_RESP0REG,value);
    #endif
    return value;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp1Reg (read)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO0_get_Resp1Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_RESP1REG_REAL);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Resp1Reg] --> 0x%08x\n",
                        REG_SDIO0_RESP1REG,value);
    #endif
    return value;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp2Reg (read)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO0_get_Resp2Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_RESP2REG_REAL);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Resp2Reg] --> 0x%08x\n",
                        REG_SDIO0_RESP2REG,value);
    #endif
    return value;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_Resp3Reg (read)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO0_get_Resp3Reg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_RESP3REG_REAL);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Resp3Reg] --> 0x%08x\n",
                        REG_SDIO0_RESP3REG,value);
    #endif
    return value;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_Control00Reg (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_Control00Reg(U32 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S control00reg_real;
    GH_SDIO0_CONTROL00REG_S dummy;
    dummy.all = data ;
    control00reg_real.all = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);
    control00reg_real.bitc.ledcontrol = dummy.bitc.ledcontrol;
    control00reg_real.bitc.datatrawidth = dummy.bitc.datatrawidth;
    control00reg_real.bitc.sd8bitmode = dummy.bitc.sd8bitmode;
    control00reg_real.bitc.hostspeeden = dummy.bitc.hostspeeden;
    control00reg_real.bitc.carddetecttestlevel = dummy.bitc.carddetecttestlevel;
    control00reg_real.bitc.carddetectsigdet = dummy.bitc.carddetectsigdet;
    control00reg_real.bitc.sdbuspower = dummy.bitc.sdbuspower;
    control00reg_real.bitc.sdbusvoltageselect = dummy.bitc.sdbusvoltageselect;
    control00reg_real.bitc.stopatblkgapreq = dummy.bitc.stopatblkgapreq;
    control00reg_real.bitc.rwaitcontrol = dummy.bitc.rwaitcontrol;
    control00reg_real.bitc.continuereq = dummy.bitc.continuereq;
    control00reg_real.bitc.intatblkgap = dummy.bitc.intatblkgap;
    control00reg_real.bitc.driveccsd = dummy.bitc.driveccsd;
    control00reg_real.bitc.spimode = dummy.bitc.spimode;
    control00reg_real.bitc.booten = dummy.bitc.booten;
    control00reg_real.bitc.altbooten = dummy.bitc.altbooten;
    control00reg_real.bitc.wakeupevetenoncardins = dummy.bitc.wakeupevetenoncardins;
    control00reg_real.bitc.wakeupevetenoncardint = dummy.bitc.wakeupevetenoncardint;
    control00reg_real.bitc.wakeupevetenoncardrem = dummy.bitc.wakeupevetenoncardrem;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = control00reg_real.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,dummy.all,dummy.all);
    #endif
}
GH_INLINE U32  GH_SDIO0_get_Control00Reg(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S control00reg_real;
    GH_SDIO0_CONTROL00REG_S dummy;
    control00reg_real.all = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    dummy.bitc.ledcontrol = control00reg_real.bitc.ledcontrol;
    dummy.bitc.datatrawidth = control00reg_real.bitc.datatrawidth;
    dummy.bitc.sd8bitmode = control00reg_real.bitc.sd8bitmode;
    dummy.bitc.hostspeeden = control00reg_real.bitc.hostspeeden;
    dummy.bitc.carddetecttestlevel = control00reg_real.bitc.carddetecttestlevel;
    dummy.bitc.carddetectsigdet = control00reg_real.bitc.carddetectsigdet;
    dummy.bitc.sdbuspower = control00reg_real.bitc.sdbuspower;
    dummy.bitc.sdbusvoltageselect = control00reg_real.bitc.sdbusvoltageselect;
    dummy.bitc.stopatblkgapreq = control00reg_real.bitc.stopatblkgapreq;
    dummy.bitc.rwaitcontrol = control00reg_real.bitc.rwaitcontrol;
    dummy.bitc.continuereq = control00reg_real.bitc.continuereq;
    dummy.bitc.intatblkgap = control00reg_real.bitc.intatblkgap;
    dummy.bitc.driveccsd = control00reg_real.bitc.driveccsd;
    dummy.bitc.spimode = control00reg_real.bitc.spimode;
    dummy.bitc.booten = control00reg_real.bitc.booten;
    dummy.bitc.altbooten = control00reg_real.bitc.altbooten;
    dummy.bitc.wakeupevetenoncardins = control00reg_real.bitc.wakeupevetenoncardins;
    dummy.bitc.wakeupevetenoncardint = control00reg_real.bitc.wakeupevetenoncardint;
    dummy.bitc.wakeupevetenoncardrem = control00reg_real.bitc.wakeupevetenoncardrem;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_LedControl(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.ledcontrol = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_LedControl] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_LedControl(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_LedControl] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.ledcontrol;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_DataTraWidth(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.datatrawidth = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_DataTraWidth] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_DataTraWidth(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_DataTraWidth] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.datatrawidth;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_Sd8BitMode(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.sd8bitmode = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_Sd8BitMode] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_Sd8BitMode(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_Sd8BitMode] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.sd8bitmode;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_HostSpeedEn(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.hostspeeden = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_HostSpeedEn] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_HostSpeedEn(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_HostSpeedEn] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.hostspeeden;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_CardDetectTestLevel(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.carddetecttestlevel = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_CardDetectTestLevel] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_CardDetectTestLevel(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_CardDetectTestLevel] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.carddetecttestlevel;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_CardDetectSigDet(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.carddetectsigdet = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_CardDetectSigDet] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_CardDetectSigDet(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_CardDetectSigDet] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.carddetectsigdet;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_SdBusPower(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.sdbuspower = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_SdBusPower] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_SdBusPower(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_SdBusPower] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.sdbuspower;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_SdBusVoltageSelect(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.sdbusvoltageselect = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_SdBusVoltageSelect] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_SdBusVoltageSelect(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_SdBusVoltageSelect] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.sdbusvoltageselect;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_StopAtBlkGapReq(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.stopatblkgapreq = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_StopAtBlkGapReq] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_StopAtBlkGapReq(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_StopAtBlkGapReq] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.stopatblkgapreq;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_RWaitControl(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.rwaitcontrol = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_RWaitControl] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_RWaitControl(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_RWaitControl] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.rwaitcontrol;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_ContinueReq(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.continuereq = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_ContinueReq] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_ContinueReq(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_ContinueReq] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.continuereq;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_IntAtBlkGap(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.intatblkgap = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_IntAtBlkGap] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_IntAtBlkGap(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_IntAtBlkGap] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.intatblkgap;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_DriveCcsd(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.driveccsd = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_DriveCcsd] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_DriveCcsd(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_DriveCcsd] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.driveccsd;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_SpiMode(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.spimode = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_SpiMode] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_SpiMode(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_SpiMode] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.spimode;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_BootEn(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.booten = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_BootEn] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_BootEn(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_BootEn] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.booten;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_AltBootEn(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.altbooten = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_AltBootEn] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_AltBootEn(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_AltBootEn] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.altbooten;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardIns(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.wakeupevetenoncardins = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardIns] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardIns(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardIns] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.wakeupevetenoncardins;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardInt(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.wakeupevetenoncardint = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardInt] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardInt(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardInt] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.wakeupevetenoncardint;
}
GH_INLINE void GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardRem(U8 data)
{
    GH_SDIO0_CONTROL00REG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL;
    d.bitc.wakeupevetenoncardrem = data;
    *(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_Control00Reg_WakeupEvetEnOnCardRem] <-- 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardRem(void)
{
    GH_SDIO0_CONTROL00REG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CONTROL00REG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_Control00Reg_WakeupEvetEnOnCardRem] --> 0x%08x\n",
                        REG_SDIO0_CONTROL00REG,value);
    #endif
    return tmp_value.bitc.wakeupevetenoncardrem;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_PresentStateReg (read)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO0_get_PresentStateReg(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S presentstatereg_real;
    GH_SDIO0_PRESENTSTATEREG_S dummy;
    presentstatereg_real.all = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    dummy.bitc.cmdinhibitcmd = presentstatereg_real.bitc.cmdinhibitcmd;
    dummy.bitc.datalineactive = presentstatereg_real.bitc.datalineactive;
    dummy.bitc.cmdinhibitdata = presentstatereg_real.bitc.cmdinhibitdata;
    dummy.bitc.rtraactive = presentstatereg_real.bitc.rtraactive;
    dummy.bitc.bufwen = presentstatereg_real.bitc.bufwen;
    dummy.bitc.wtraactive = presentstatereg_real.bitc.wtraactive;
    dummy.bitc.bufren = presentstatereg_real.bitc.bufren;
    dummy.bitc.cardinserted = presentstatereg_real.bitc.cardinserted;
    dummy.bitc.carddetectpinlevel = presentstatereg_real.bitc.carddetectpinlevel;
    dummy.bitc.cardstatestable = presentstatereg_real.bitc.cardstatestable;
    dummy.bitc.wproswipinlevel = presentstatereg_real.bitc.wproswipinlevel;
    dummy.bitc.data03linesiglevel = presentstatereg_real.bitc.data03linesiglevel;
    dummy.bitc.cmdlinesiglevel = presentstatereg_real.bitc.cmdlinesiglevel;
    dummy.bitc.data47linesiglevel = presentstatereg_real.bitc.data47linesiglevel;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_CmdInhibitCmd(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CmdInhibitCmd] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cmdinhibitcmd;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_DataLineActive(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_DataLineActive] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.datalineactive;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_CmdInhibitData(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CmdInhibitData] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cmdinhibitdata;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_RTraActive(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_RTraActive] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.rtraactive;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_BufWEn(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_BufWEn] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.bufwen;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_WTraActive(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_WTraActive] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.wtraactive;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_BufREn(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_BufREn] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.bufren;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_CardInserted(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CardInserted] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cardinserted;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_CardDetectPinLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CardDetectPinLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.carddetectpinlevel;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_CardStateStable(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CardStateStable] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cardstatestable;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_WProSwiPinLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_WProSwiPinLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.wproswipinlevel;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_Data03LineSigLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_Data03LineSigLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.data03linesiglevel;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_CmdLineSigLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_CmdLineSigLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.cmdlinesiglevel;
}
GH_INLINE U8   GH_SDIO0_get_PresentStateReg_Data47LineSigLevel(void)
{
    GH_SDIO0_PRESENTSTATEREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_PRESENTSTATEREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_PresentStateReg_Data47LineSigLevel] --> 0x%08x\n",
                        REG_SDIO0_PRESENTSTATEREG,value);
    #endif
    return tmp_value.bitc.data47linesiglevel;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_ArgReg (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_ArgReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_ARGREG_REAL = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_ArgReg] <-- 0x%08x\n",
                        REG_SDIO0_ARGREG,value,value);
    #endif
}
GH_INLINE U32  GH_SDIO0_get_ArgReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_ARGREG_REAL);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_ArgReg] --> 0x%08x\n",
                        REG_SDIO0_ARGREG,value);
    #endif
    return value;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_CapReg (read)                                               */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO0_get_CapReg(void)
{
    GH_SDIO0_CAPREG_REAL_S capreg_real;
    GH_SDIO0_CAPREG_S dummy;
    capreg_real.all = (*(volatile U32 *)REG_SDIO0_CAPREG_REAL);

    dummy.bitc.timeoutclkfre = capreg_real.bitc.timeoutclkfre;
    dummy.bitc.timeoutclkunit = capreg_real.bitc.timeoutclkunit;
    dummy.bitc.baseclkfreforsdclk = capreg_real.bitc.baseclkfreforsdclk;
    dummy.bitc.maxblklen = capreg_real.bitc.maxblklen;
    dummy.bitc.extendedmediabussup = capreg_real.bitc.extendedmediabussup;
    dummy.bitc.highspeedsup = capreg_real.bitc.highspeedsup;
    dummy.bitc.susressup = capreg_real.bitc.susressup;
    dummy.bitc.sdmasup = capreg_real.bitc.sdmasup;
    dummy.bitc.voltagesup33v = capreg_real.bitc.voltagesup33v;
    dummy.bitc.voltagesup30v = capreg_real.bitc.voltagesup30v;
    dummy.bitc.voltagesup18v = capreg_real.bitc.voltagesup18v;
    dummy.bitc.intmode = capreg_real.bitc.intmode;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_TimeoutClkFre(void)
{
    GH_SDIO0_CAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_TimeoutClkFre] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.timeoutclkfre;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_TimeoutClkUnit(void)
{
    GH_SDIO0_CAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_TimeoutClkUnit] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.timeoutclkunit;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_BaseClkFreForSdClk(void)
{
    GH_SDIO0_CAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_BaseClkFreForSdClk] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.baseclkfreforsdclk;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_MaxBlkLen(void)
{
    GH_SDIO0_CAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_MaxBlkLen] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.maxblklen;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_ExtendedMediaBusSup(void)
{
    GH_SDIO0_CAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_ExtendedMediaBusSup] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.extendedmediabussup;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_HighSpeedSup(void)
{
    GH_SDIO0_CAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_HighSpeedSup] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.highspeedsup;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_SusResSup(void)
{
    GH_SDIO0_CAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_SusResSup] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.susressup;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_SdmaSup(void)
{
    GH_SDIO0_CAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_SdmaSup] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.sdmasup;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_VoltageSup33v(void)
{
    GH_SDIO0_CAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_VoltageSup33v] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.voltagesup33v;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_VoltageSup30v(void)
{
    GH_SDIO0_CAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_VoltageSup30v] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.voltagesup30v;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_VoltageSup18v(void)
{
    GH_SDIO0_CAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_VoltageSup18v] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.voltagesup18v;
}
GH_INLINE U8   GH_SDIO0_get_CapReg_IntMode(void)
{
    GH_SDIO0_CAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_CAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_CapReg_IntMode] --> 0x%08x\n",
                        REG_SDIO0_CAPREG,value);
    #endif
    return tmp_value.bitc.intmode;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_AutoCmd12ErrStatusReg (read)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO0_get_AutoCmd12ErrStatusReg(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_REAL_S autocmd12errstatusreg_real;
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_S dummy;
    autocmd12errstatusreg_real.all = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG_REAL);

    dummy.bitc.autocmd12timeouterr = autocmd12errstatusreg_real.bitc.autocmd12timeouterr;
    dummy.bitc.autocmd12crcerr = autocmd12errstatusreg_real.bitc.autocmd12crcerr;
    dummy.bitc.autocmd12endbiterr = autocmd12errstatusreg_real.bitc.autocmd12endbiterr;
    dummy.bitc.autocmd12notexe = autocmd12errstatusreg_real.bitc.autocmd12notexe;
    dummy.bitc.autocmd12indexerr = autocmd12errstatusreg_real.bitc.autocmd12indexerr;
    dummy.bitc.cmdnotissuedbyautocmd12err = autocmd12errstatusreg_real.bitc.cmdnotissuedbyautocmd12err;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12TimeoutErr] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12timeouterr;
}
GH_INLINE U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12CrcErr] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12crcerr;
}
GH_INLINE U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12EndBitErr] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12endbiterr;
}
GH_INLINE U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12NotExe] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12notexe;
}
GH_INLINE U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_AutoCmd12IndexErr] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.autocmd12indexerr;
}
GH_INLINE U8   GH_SDIO0_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err(void)
{
    GH_SDIO0_AUTOCMD12ERRSTATUSREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_AUTOCMD12ERRSTATUSREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_AutoCmd12ErrStatusReg_CmdNotIssuedByAutoCmd12Err] --> 0x%08x\n",
                        REG_SDIO0_AUTOCMD12ERRSTATUSREG,value);
    #endif
    return tmp_value.bitc.cmdnotissuedbyautocmd12err;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_BufferDataPortReg (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_BufferDataPortReg(U32 data)
{
    *(volatile U32 *)REG_SDIO0_BUFFERDATAPORTREG_REAL = data;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_BufferDataPortReg] <-- 0x%08x\n",
                        REG_SDIO0_BUFFERDATAPORTREG,value,value);
    #endif
}
GH_INLINE U32  GH_SDIO0_get_BufferDataPortReg(void)
{
    U32 value = (*(volatile U32 *)REG_SDIO0_BUFFERDATAPORTREG_REAL);

    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_BufferDataPortReg] --> 0x%08x\n",
                        REG_SDIO0_BUFFERDATAPORTREG,value);
    #endif
    return value;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_MaxCurCapReg (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_set_MaxCurCapReg(U32 data)
{
    GH_SDIO0_MAXCURCAPREG_REAL_S real;
    GH_SDIO0_MAXCURCAPREG_S dummy;
    dummy.all = data ;
    real.bitc.maxcurfor33v = dummy.bitc.maxcurfor33v;
    real.bitc.maxcurfor30v = dummy.bitc.maxcurfor30v;
    real.bitc.maxcurfor18v = dummy.bitc.maxcurfor18v;
    *(volatile U32 *)REG_SDIO0_MAXCURCAPREG_REAL = real.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_MaxCurCapReg] <-- 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,dummy.all,dummy.all);
    #endif
}
GH_INLINE U32  GH_SDIO0_get_MaxCurCapReg(void)
{
    GH_SDIO0_MAXCURCAPREG_REAL_S real;
    GH_SDIO0_MAXCURCAPREG_S dummy;
     real.all = (*(volatile U32 *)REG_SDIO0_MAXCURCAPREG_REAL);

    dummy.bitc.maxcurfor33v = real.bitc.maxcurfor33v;
    dummy.bitc.maxcurfor30v = real.bitc.maxcurfor30v;
    dummy.bitc.maxcurfor18v = real.bitc.maxcurfor18v;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_MaxCurCapReg] --> 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE void GH_SDIO0_set_MaxCurCapReg_MaxCurFor33v(U8 data)
{
    GH_SDIO0_MAXCURCAPREG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_MAXCURCAPREG_REAL;
    d.bitc.maxcurfor33v = data;
    *(volatile U32 *)REG_SDIO0_MAXCURCAPREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_MaxCurCapReg_MaxCurFor33v] <-- 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_MaxCurCapReg_MaxCurFor33v(void)
{
    GH_SDIO0_MAXCURCAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_MAXCURCAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_MaxCurCapReg_MaxCurFor33v] --> 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,value);
    #endif
    return tmp_value.bitc.maxcurfor33v;
}
GH_INLINE void GH_SDIO0_set_MaxCurCapReg_MaxCurFor30v(U8 data)
{
    GH_SDIO0_MAXCURCAPREG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_MAXCURCAPREG_REAL;
    d.bitc.maxcurfor30v = data;
    *(volatile U32 *)REG_SDIO0_MAXCURCAPREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_MaxCurCapReg_MaxCurFor30v] <-- 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_MaxCurCapReg_MaxCurFor30v(void)
{
    GH_SDIO0_MAXCURCAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_MAXCURCAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_MaxCurCapReg_MaxCurFor30v] --> 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,value);
    #endif
    return tmp_value.bitc.maxcurfor30v;
}
GH_INLINE void GH_SDIO0_set_MaxCurCapReg_MaxCurFor18v(U8 data)
{
    GH_SDIO0_MAXCURCAPREG_REAL_S d;
    d.all = *(volatile U32 *)REG_SDIO0_MAXCURCAPREG_REAL;
    d.bitc.maxcurfor18v = data;
    *(volatile U32 *)REG_SDIO0_MAXCURCAPREG_REAL = d.all;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SDIO0_set_MaxCurCapReg_MaxCurFor18v] <-- 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SDIO0_get_MaxCurCapReg_MaxCurFor18v(void)
{
    GH_SDIO0_MAXCURCAPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_MAXCURCAPREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_MaxCurCapReg_MaxCurFor18v] --> 0x%08x\n",
                        REG_SDIO0_MAXCURCAPREG,value);
    #endif
    return tmp_value.bitc.maxcurfor18v;
}

/*----------------------------------------------------------------------------*/
/* register SDIO0_SlotIntStatusReg (read)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SDIO0_get_SlotIntStatusReg(void)
{
    GH_SDIO0_SLOTINTSTATUSREG_REAL_S real;
    GH_SDIO0_SLOTINTSTATUSREG_S dummy;
     real.all = (*(volatile U32 *)REG_SDIO0_SLOTINTSTATUSREG_REAL);

    dummy.bitc.intsigforeachslot = real.bitc.intsigforeachslot;
    dummy.bitc.specifivernum = real.bitc.specifivernum;
    dummy.bitc.vendorvernum = real.bitc.vendorvernum;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SlotIntStatusReg] --> 0x%08x\n",
                        REG_SDIO0_SLOTINTSTATUSREG,dummy.all);
    #endif
    return dummy.all;
}
GH_INLINE U8   GH_SDIO0_get_SlotIntStatusReg_IntSigForEachSlot(void)
{
    GH_SDIO0_SLOTINTSTATUSREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_SLOTINTSTATUSREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SlotIntStatusReg_IntSigForEachSlot] --> 0x%08x\n",
                        REG_SDIO0_SLOTINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.intsigforeachslot;
}
GH_INLINE U8   GH_SDIO0_get_SlotIntStatusReg_SpecifiVerNum(void)
{
    GH_SDIO0_SLOTINTSTATUSREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_SLOTINTSTATUSREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SlotIntStatusReg_SpecifiVerNum] --> 0x%08x\n",
                        REG_SDIO0_SLOTINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.specifivernum;
}
GH_INLINE U8   GH_SDIO0_get_SlotIntStatusReg_VendorVerNum(void)
{
    GH_SDIO0_SLOTINTSTATUSREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SDIO0_SLOTINTSTATUSREG_REAL);

    tmp_value.all = value;
    #if GH_SDIO0_ENABLE_DEBUG_PRINT
    GH_SDIO0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SDIO0_get_SlotIntStatusReg_VendorVerNum] --> 0x%08x\n",
                        REG_SDIO0_SLOTINTSTATUSREG,value);
    #endif
    return tmp_value.bitc.vendorvernum;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SDIO0_init(void)
{
    GH_SDIO0_set_SysAddrReg((U32)0x0000);
    GH_SDIO0_set_TranModeReg((U16)0x0000);
    GH_SDIO0_set_NorIntSigEnReg((U16)0x0000);
    GH_SDIO0_set_ErrIntSigEn((U16)0x0000);
    GH_SDIO0_set_BlkCouReg((U16)0x0000);
    GH_SDIO0_set_BlkSizeReg((U16)0x0000);
    GH_SDIO0_set_NorIntStaEnReg((U16)0x0000);
    GH_SDIO0_set_ErrIntStaEnReg((U16)0x0000);
    GH_SDIO0_set_NorIntStaReg((U16)0x0000);
    GH_SDIO0_set_ErrIntStaReg((U16)0x0000);
    GH_SDIO0_set_CmdReg((U16)0x0000);
    GH_SDIO0_set_Control01Reg((U32)0x00000000);
    GH_SDIO0_set_Control00Reg((U32)0x00000000);
    GH_SDIO0_set_ArgReg((U32)0x00000000);
    GH_SDIO0_set_MaxCurCapReg((U32)0x00000001);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

