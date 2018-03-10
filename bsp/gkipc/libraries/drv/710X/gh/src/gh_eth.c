/******************************************************************************
**
** \file      gh_eth.c
**
** \brief     Ethernet controller.
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
#include "gh_eth.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_ETH_MCR_REAL                                    FIO_ADDRESS(ETH,0x6000E000) /* read/write */
#define REG_ETH_MFFR_REAL                                   FIO_ADDRESS(ETH,0x6000E004) /* read/write */
#define REG_ETH_MHTRH_REAL                                  FIO_ADDRESS(ETH,0x6000E008) /* read/write */
#define REG_ETH_MHTRL_REAL                                  FIO_ADDRESS(ETH,0x6000E00C) /* read/write */
#define REG_ETH_GAR_REAL                                    FIO_ADDRESS(ETH,0x6000E010) /* read/write */
#define REG_ETH_GDR_REAL                                    FIO_ADDRESS(ETH,0x6000E014) /* read/write */
#define REG_ETH_FCR_REAL                                    FIO_ADDRESS(ETH,0x6000E018) /* read/write */
#define REG_ETH_VTR_REAL                                    FIO_ADDRESS(ETH,0x6000E01C) /* read/write */
#define REG_ETH_VR_REAL                                     FIO_ADDRESS(ETH,0x6000E020) /* read */
#define REG_ETH_MAR0H_REAL                                  FIO_ADDRESS(ETH,0x6000E040) /* read/write */
#define REG_ETH_MAR0L_REAL                                  FIO_ADDRESS(ETH,0x6000E044) /* read/write */
#define REG_ETH_MAR1H_REAL                                  FIO_ADDRESS(ETH,0x6000E048) /* read/write */
#define REG_ETH_MAR1L_REAL                                  FIO_ADDRESS(ETH,0x6000E04C) /* read/write */
#define REG_ETH_MAR2H_REAL                                  FIO_ADDRESS(ETH,0x6000E050) /* read/write */
#define REG_ETH_MAR2L_REAL                                  FIO_ADDRESS(ETH,0x6000E054) /* read/write */
#define REG_ETH_EPHY_DEBUG_REAL                             FIO_ADDRESS(ETH,0x6000E058) /* read/write */
#define REG_ETH_BMR_REAL                                    FIO_ADDRESS(ETH,0x6000F000) /* read/write */
#define REG_ETH_TPDR_REAL                                   FIO_ADDRESS(ETH,0x6000F004) /* read/write */
#define REG_ETH_RPDR_REAL                                   FIO_ADDRESS(ETH,0x6000F008) /* read/write */
#define REG_ETH_RDLAR_REAL                                  FIO_ADDRESS(ETH,0x6000F00C) /* read/write */
#define REG_ETH_TDLAR_REAL                                  FIO_ADDRESS(ETH,0x6000F010) /* read/write */
#define REG_ETH_SR_REAL                                     FIO_ADDRESS(ETH,0x6000F014) /* read/write */
#define REG_ETH_OMR_REAL                                    FIO_ADDRESS(ETH,0x6000F018) /* read/write */
#define REG_ETH_IER_REAL                                    FIO_ADDRESS(ETH,0x6000F01C) /* read/write */
#define REG_ETH_MFBOCR_REAL                                 FIO_ADDRESS(ETH,0x6000F020) /* read/write */
#define REG_ETH_CHTDR_REAL                                  FIO_ADDRESS(ETH,0x6000F048) /* read/write */
#define REG_ETH_CHRDR_REAL                                  FIO_ADDRESS(ETH,0x6000F04C) /* read/write */
#define REG_ETH_CHTBAR_REAL                                 FIO_ADDRESS(ETH,0x6000F050) /* read/write */
#define REG_ETH_CHRBAR_REAL                                 FIO_ADDRESS(ETH,0x6000F054) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* ETH_MCR */
    U32 all;
    struct {
        U32                             : 2;
        U32 re                          : 1;
        U32 te                          : 1;
        U32 dc                          : 1;
        U32 bl                          : 2;
        U32 acs                         : 1;
        U32 lud                         : 1;
        U32 dr                          : 1;
        U32 ipc                         : 1;
        U32 dm                          : 1;
        U32 lm                          : 1;
        U32 dro                         : 1;
        U32 fes                         : 1;
        U32 ps                          : 1;
        U32 dcrs                        : 1;
        U32 ifg                         : 3;
        U32 je                          : 1;
        U32 be                          : 1;
        U32 jd                          : 1;
        U32 wd                          : 1;
        U32                             : 8;
    } bitc;
} GH_ETH_MCR_REAL_S;

typedef union { /* ETH_MFFR */
    U32 all;
    struct {
        U32 pr                          : 1;
        U32 huc                         : 1;
        U32 hmc                         : 1;
        U32 ift                         : 1;
        U32 pm                          : 1;
        U32 db                          : 1;
        U32                             : 1;
        U32 pcf                         : 1;
        U32 saif                        : 1;
        U32 saf                         : 1;
        U32 hpf                         : 1;
        U32                             : 20;
        U32 ra                          : 1;
    } bitc;
} GH_ETH_MFFR_REAL_S;

typedef union { /* ETH_MHTRH */
    U32 all;
    struct {
        U32 hth                         : 32;
    } bitc;
} GH_ETH_MHTRH_REAL_S;

typedef union { /* ETH_MHTRL */
    U32 all;
    struct {
        U32 htl                         : 32;
    } bitc;
} GH_ETH_MHTRL_REAL_S;

typedef union { /* ETH_GAR */
    U32 all;
    struct {
        U32 gb                          : 1;
        U32 gw                          : 1;
        U32 cr                          : 3;
        U32                             : 1;
        U32 gr                          : 5;
        U32 pa                          : 5;
        U32                             : 16;
    } bitc;
} GH_ETH_GAR_REAL_S;

typedef union { /* ETH_GDR */
    U32 all;
    struct {
        U32 gd                          : 16;
        U32                             : 16;
    } bitc;
} GH_ETH_GDR_REAL_S;

typedef union { /* ETH_FCR */
    U32 all;
    struct {
        U32 fcb                         : 1;
        U32 tfe                         : 1;
        U32 rfe                         : 1;
        U32 up                          : 1;
        U32 plt                         : 2;
        U32                             : 10;
        U32 pt                          : 16;
    } bitc;
} GH_ETH_FCR_REAL_S;

typedef union { /* ETH_VTR */
    U32 all;
    struct {
        U32 vl                          : 16;
        U32 etv                         : 1;
        U32                             : 15;
    } bitc;
} GH_ETH_VTR_REAL_S;

typedef union { /* ETH_MAR0H */
    U32 all;
    struct {
        U32 a0                          : 16;
        U32                             : 15;
        U32 m0                          : 1;
    } bitc;
} GH_ETH_MAR0H_REAL_S;

typedef union { /* ETH_MAR0L */
    U32 all;
    struct {
        U32 a0                          : 32;
    } bitc;
} GH_ETH_MAR0L_REAL_S;

typedef union { /* ETH_MAR1H */
    U32 all;
    struct {
        U32 a1                          : 16;
        U32                             : 8;
        U32 mbc                         : 6;
        U32 sa                          : 1;
        U32 a1e                         : 1;
    } bitc;
} GH_ETH_MAR1H_REAL_S;

typedef union { /* ETH_MAR1L */
    U32 all;
    struct {
        U32 a1                          : 32;
    } bitc;
} GH_ETH_MAR1L_REAL_S;

typedef union { /* ETH_MAR2H */
    U32 all;
    struct {
        U32 a2                          : 16;
        U32                             : 8;
        U32 mbc                         : 6;
        U32 sa                          : 1;
        U32 a2e                         : 1;
    } bitc;
} GH_ETH_MAR2H_REAL_S;

typedef union { /* ETH_MAR2L */
    U32 all;
    struct {
        U32 a2                          : 32;
    } bitc;
} GH_ETH_MAR2L_REAL_S;

typedef union { /* ETH_EPHY_DEBUG */
    U32 all;
    struct {
        U32                             : 8;
        U32 debug                       : 24;
    } bitc;
} GH_ETH_EPHY_DEBUG_REAL_S;

typedef union { /* ETH_BMR */
    U32 all;
    struct {
        U32 swr                         : 1;
        U32 da                          : 1;
        U32 dsl                         : 5;
        U32                             : 1;
        U32 pbl                         : 6;
        U32 pr                          : 2;
        U32 fb                          : 1;
        U32 rpbl                        : 6;
        U32 usp                         : 1;
        U32 pbl4x                       : 1;
        U32 aal                         : 1;
        U32                             : 6;
    } bitc;
} GH_ETH_BMR_REAL_S;

typedef union { /* ETH_SR */
    U32 all;
    struct {
        U32 ti                          : 1;
        U32 tps                         : 1;
        U32 tu                          : 1;
        U32 tjt                         : 1;
        U32 ovf                         : 1;
        U32 unf                         : 1;
        U32 ri                          : 1;
        U32 ru                          : 1;
        U32 rps                         : 1;
        U32 rwt                         : 1;
        U32 eti                         : 1;
        U32                             : 2;
        U32 fbe                         : 1;
        U32 eri                         : 1;
        U32 ais                         : 1;
        U32 nis                         : 1;
        U32 rs                          : 3;
        U32 ts                          : 3;
        U32 eb                          : 3;
        U32 gli                         : 1;
        U32 gmi                         : 1;
        U32 gpi                         : 1;
        U32                             : 3;
    } bitc;
} GH_ETH_SR_REAL_S;

typedef union { /* ETH_OMR */
    U32 all;
    struct {
        U32                             : 1;
        U32 sr                          : 1;
        U32 osf                         : 1;
        U32 rtc                         : 2;
        U32                             : 1;
        U32 fuf                         : 1;
        U32 fef                         : 1;
        U32 efc                         : 1;
        U32 rfa                         : 2;
        U32 rfd                         : 2;
        U32 st                          : 1;
        U32 ttc                         : 3;
        U32                             : 3;
        U32 ftf                         : 1;
        U32 sf                          : 1;
        U32                             : 10;
    } bitc;
} GH_ETH_OMR_REAL_S;

typedef union { /* ETH_IER */
    U32 all;
    struct {
        U32 ti                          : 1;
        U32 ts                          : 1;
        U32 tu                          : 1;
        U32 tj                          : 1;
        U32 ov                          : 1;
        U32 un                          : 1;
        U32 ri                          : 1;
        U32 ru                          : 1;
        U32 rs                          : 1;
        U32 rw                          : 1;
        U32 ete                         : 1;
        U32                             : 2;
        U32 fbe                         : 1;
        U32 ere                         : 1;
        U32 ai                          : 1;
        U32 ni                          : 1;
        U32                             : 15;
    } bitc;
} GH_ETH_IER_REAL_S;

typedef union { /* ETH_MFBOCR */
    U32 all;
    struct {
        U32 nmfh                        : 16;
        U32 ovmfc                       : 1;
        U32 nmff                        : 11;
        U32 onmff                       : 1;
        U32                             : 3;
    } bitc;
} GH_ETH_MFBOCR_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register ETH_MCR (read/write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_MCR(U32 data)
{
    GH_ETH_MCR_REAL_S real;
    GH_ETH_MCR_S dummy;
    dummy.all = data ;
    real.bitc.re = dummy.bitc.re;
    real.bitc.te = dummy.bitc.te;
    real.bitc.dc = dummy.bitc.dc;
    real.bitc.bl = dummy.bitc.bl;
    real.bitc.acs = dummy.bitc.acs;
    real.bitc.lud = dummy.bitc.lud;
    real.bitc.dr = dummy.bitc.dr;
    real.bitc.ipc = dummy.bitc.ipc;
    real.bitc.dm = dummy.bitc.dm;
    real.bitc.lm = dummy.bitc.lm;
    real.bitc.dro = dummy.bitc.dro;
    real.bitc.fes = dummy.bitc.fes;
    real.bitc.ps = dummy.bitc.ps;
    real.bitc.dcrs = dummy.bitc.dcrs;
    real.bitc.ifg = dummy.bitc.ifg;
    real.bitc.je = dummy.bitc.je;
    real.bitc.be = dummy.bitc.be;
    real.bitc.jd = dummy.bitc.jd;
    real.bitc.wd = dummy.bitc.wd;
    *(volatile U32 *)REG_ETH_MCR_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_MCR(void)
{
    GH_ETH_MCR_REAL_S real;
    GH_ETH_MCR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_MCR_REAL);

    dummy.bitc.re = real.bitc.re;
    dummy.bitc.te = real.bitc.te;
    dummy.bitc.dc = real.bitc.dc;
    dummy.bitc.bl = real.bitc.bl;
    dummy.bitc.acs = real.bitc.acs;
    dummy.bitc.lud = real.bitc.lud;
    dummy.bitc.dr = real.bitc.dr;
    dummy.bitc.ipc = real.bitc.ipc;
    dummy.bitc.dm = real.bitc.dm;
    dummy.bitc.lm = real.bitc.lm;
    dummy.bitc.dro = real.bitc.dro;
    dummy.bitc.fes = real.bitc.fes;
    dummy.bitc.ps = real.bitc.ps;
    dummy.bitc.dcrs = real.bitc.dcrs;
    dummy.bitc.ifg = real.bitc.ifg;
    dummy.bitc.je = real.bitc.je;
    dummy.bitc.be = real.bitc.be;
    dummy.bitc.jd = real.bitc.jd;
    dummy.bitc.wd = real.bitc.wd;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_MCR_RE(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.re = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_RE(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.re;
}
GH_INLINE void GH_ETH_set_MCR_TE(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.te = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_TE(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.te;
}
GH_INLINE void GH_ETH_set_MCR_DC(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.dc = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_DC(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dc;
}
GH_INLINE void GH_ETH_set_MCR_BL(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.bl = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_BL(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bl;
}
GH_INLINE void GH_ETH_set_MCR_ACS(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.acs = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_ACS(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.acs;
}
GH_INLINE void GH_ETH_set_MCR_LUD(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.lud = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_LUD(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lud;
}
GH_INLINE void GH_ETH_set_MCR_DR(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.dr = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_DR(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dr;
}
GH_INLINE void GH_ETH_set_MCR_IPC(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.ipc = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_IPC(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ipc;
}
GH_INLINE void GH_ETH_set_MCR_DM(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.dm = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_DM(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dm;
}
GH_INLINE void GH_ETH_set_MCR_LM(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.lm = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_LM(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lm;
}
GH_INLINE void GH_ETH_set_MCR_DRO(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.dro = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_DRO(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dro;
}
GH_INLINE void GH_ETH_set_MCR_FES(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.fes = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_FES(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fes;
}
GH_INLINE void GH_ETH_set_MCR_PS(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.ps = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_PS(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ps;
}
GH_INLINE void GH_ETH_set_MCR_DCRS(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.dcrs = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_DCRS(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dcrs;
}
GH_INLINE void GH_ETH_set_MCR_IFG(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.ifg = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_IFG(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ifg;
}
GH_INLINE void GH_ETH_set_MCR_JE(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.je = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_JE(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.je;
}
GH_INLINE void GH_ETH_set_MCR_BE(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.be = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_BE(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.be;
}
GH_INLINE void GH_ETH_set_MCR_JD(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.jd = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_JD(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.jd;
}
GH_INLINE void GH_ETH_set_MCR_WD(U8 data)
{
    GH_ETH_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MCR_REAL;
    d.bitc.wd = data;
    *(volatile U32 *)REG_ETH_MCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MCR_WD(void)
{
    GH_ETH_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.wd;
}

/*----------------------------------------------------------------------------*/
/* register ETH_MFFR (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_MFFR(U32 data)
{
    GH_ETH_MFFR_REAL_S real;
    GH_ETH_MFFR_S dummy;
    dummy.all = data ;
    real.bitc.pr = dummy.bitc.pr;
    real.bitc.huc = dummy.bitc.huc;
    real.bitc.hmc = dummy.bitc.hmc;
    real.bitc.ift = dummy.bitc.ift;
    real.bitc.pm = dummy.bitc.pm;
    real.bitc.db = dummy.bitc.db;
    real.bitc.pcf = dummy.bitc.pcf;
    real.bitc.saif = dummy.bitc.saif;
    real.bitc.saf = dummy.bitc.saf;
    real.bitc.hpf = dummy.bitc.hpf;
    real.bitc.ra = dummy.bitc.ra;
    *(volatile U32 *)REG_ETH_MFFR_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_MFFR(void)
{
    GH_ETH_MFFR_REAL_S real;
    GH_ETH_MFFR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_MFFR_REAL);

    dummy.bitc.pr = real.bitc.pr;
    dummy.bitc.huc = real.bitc.huc;
    dummy.bitc.hmc = real.bitc.hmc;
    dummy.bitc.ift = real.bitc.ift;
    dummy.bitc.pm = real.bitc.pm;
    dummy.bitc.db = real.bitc.db;
    dummy.bitc.pcf = real.bitc.pcf;
    dummy.bitc.saif = real.bitc.saif;
    dummy.bitc.saf = real.bitc.saf;
    dummy.bitc.hpf = real.bitc.hpf;
    dummy.bitc.ra = real.bitc.ra;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_MFFR_PR(U8 data)
{
    GH_ETH_MFFR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR_REAL;
    d.bitc.pr = data;
    *(volatile U32 *)REG_ETH_MFFR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MFFR_PR(void)
{
    GH_ETH_MFFR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pr;
}
GH_INLINE void GH_ETH_set_MFFR_HUC(U8 data)
{
    GH_ETH_MFFR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR_REAL;
    d.bitc.huc = data;
    *(volatile U32 *)REG_ETH_MFFR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MFFR_HUC(void)
{
    GH_ETH_MFFR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.huc;
}
GH_INLINE void GH_ETH_set_MFFR_HMC(U8 data)
{
    GH_ETH_MFFR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR_REAL;
    d.bitc.hmc = data;
    *(volatile U32 *)REG_ETH_MFFR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MFFR_HMC(void)
{
    GH_ETH_MFFR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hmc;
}
GH_INLINE void GH_ETH_set_MFFR_IFT(U8 data)
{
    GH_ETH_MFFR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR_REAL;
    d.bitc.ift = data;
    *(volatile U32 *)REG_ETH_MFFR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MFFR_IFT(void)
{
    GH_ETH_MFFR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ift;
}
GH_INLINE void GH_ETH_set_MFFR_PM(U8 data)
{
    GH_ETH_MFFR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR_REAL;
    d.bitc.pm = data;
    *(volatile U32 *)REG_ETH_MFFR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MFFR_PM(void)
{
    GH_ETH_MFFR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pm;
}
GH_INLINE void GH_ETH_set_MFFR_DB(U8 data)
{
    GH_ETH_MFFR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR_REAL;
    d.bitc.db = data;
    *(volatile U32 *)REG_ETH_MFFR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MFFR_DB(void)
{
    GH_ETH_MFFR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.db;
}
GH_INLINE void GH_ETH_set_MFFR_PCF(U8 data)
{
    GH_ETH_MFFR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR_REAL;
    d.bitc.pcf = data;
    *(volatile U32 *)REG_ETH_MFFR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MFFR_PCF(void)
{
    GH_ETH_MFFR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pcf;
}
GH_INLINE void GH_ETH_set_MFFR_SAIF(U8 data)
{
    GH_ETH_MFFR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR_REAL;
    d.bitc.saif = data;
    *(volatile U32 *)REG_ETH_MFFR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MFFR_SAIF(void)
{
    GH_ETH_MFFR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.saif;
}
GH_INLINE void GH_ETH_set_MFFR_SAF(U8 data)
{
    GH_ETH_MFFR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR_REAL;
    d.bitc.saf = data;
    *(volatile U32 *)REG_ETH_MFFR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MFFR_SAF(void)
{
    GH_ETH_MFFR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.saf;
}
GH_INLINE void GH_ETH_set_MFFR_HPF(U8 data)
{
    GH_ETH_MFFR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR_REAL;
    d.bitc.hpf = data;
    *(volatile U32 *)REG_ETH_MFFR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MFFR_HPF(void)
{
    GH_ETH_MFFR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hpf;
}
GH_INLINE void GH_ETH_set_MFFR_RA(U8 data)
{
    GH_ETH_MFFR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFFR_REAL;
    d.bitc.ra = data;
    *(volatile U32 *)REG_ETH_MFFR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MFFR_RA(void)
{
    GH_ETH_MFFR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFFR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ra;
}

/*----------------------------------------------------------------------------*/
/* register ETH_MHTRH (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_MHTRH(U32 data)
{
    GH_ETH_MHTRH_REAL_S real;
    GH_ETH_MHTRH_S dummy;
    dummy.all = data ;
    real.bitc.hth = dummy.bitc.hth;
    *(volatile U32 *)REG_ETH_MHTRH_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_MHTRH(void)
{
    GH_ETH_MHTRH_REAL_S real;
    GH_ETH_MHTRH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_MHTRH_REAL);

    dummy.bitc.hth = real.bitc.hth;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_MHTRH_HTH(U32 data)
{
    GH_ETH_MHTRH_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MHTRH_REAL;
    d.bitc.hth = data;
    *(volatile U32 *)REG_ETH_MHTRH_REAL = d.all;
}
GH_INLINE U32  GH_ETH_get_MHTRH_HTH(void)
{
    GH_ETH_MHTRH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MHTRH_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hth;
}

/*----------------------------------------------------------------------------*/
/* register ETH_MHTRL (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_MHTRL(U32 data)
{
    GH_ETH_MHTRL_REAL_S real;
    GH_ETH_MHTRL_S dummy;
    dummy.all = data ;
    real.bitc.htl = dummy.bitc.htl;
    *(volatile U32 *)REG_ETH_MHTRL_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_MHTRL(void)
{
    GH_ETH_MHTRL_REAL_S real;
    GH_ETH_MHTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_MHTRL_REAL);

    dummy.bitc.htl = real.bitc.htl;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_MHTRL_HTL(U32 data)
{
    GH_ETH_MHTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MHTRL_REAL;
    d.bitc.htl = data;
    *(volatile U32 *)REG_ETH_MHTRL_REAL = d.all;
}
GH_INLINE U32  GH_ETH_get_MHTRL_HTL(void)
{
    GH_ETH_MHTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MHTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.htl;
}

/*----------------------------------------------------------------------------*/
/* register ETH_GAR (read/write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_GAR(U32 data)
{
    GH_ETH_GAR_REAL_S real;
    GH_ETH_GAR_S dummy;
    dummy.all = data ;
    real.bitc.gb = dummy.bitc.gb;
    real.bitc.gw = dummy.bitc.gw;
    real.bitc.cr = dummy.bitc.cr;
    real.bitc.gr = dummy.bitc.gr;
    real.bitc.pa = dummy.bitc.pa;
    *(volatile U32 *)REG_ETH_GAR_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_GAR(void)
{
    GH_ETH_GAR_REAL_S real;
    GH_ETH_GAR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_GAR_REAL);

    dummy.bitc.gb = real.bitc.gb;
    dummy.bitc.gw = real.bitc.gw;
    dummy.bitc.cr = real.bitc.cr;
    dummy.bitc.gr = real.bitc.gr;
    dummy.bitc.pa = real.bitc.pa;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_GAR_GB(U8 data)
{
    GH_ETH_GAR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_GAR_REAL;
    d.bitc.gb = data;
    *(volatile U32 *)REG_ETH_GAR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_GAR_GB(void)
{
    GH_ETH_GAR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_GAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gb;
}
GH_INLINE void GH_ETH_set_GAR_GW(U8 data)
{
    GH_ETH_GAR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_GAR_REAL;
    d.bitc.gw = data;
    *(volatile U32 *)REG_ETH_GAR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_GAR_GW(void)
{
    GH_ETH_GAR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_GAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gw;
}
GH_INLINE void GH_ETH_set_GAR_CR(U8 data)
{
    GH_ETH_GAR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_GAR_REAL;
    d.bitc.cr = data;
    *(volatile U32 *)REG_ETH_GAR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_GAR_CR(void)
{
    GH_ETH_GAR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_GAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cr;
}
GH_INLINE void GH_ETH_set_GAR_GR(U8 data)
{
    GH_ETH_GAR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_GAR_REAL;
    d.bitc.gr = data;
    *(volatile U32 *)REG_ETH_GAR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_GAR_GR(void)
{
    GH_ETH_GAR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_GAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gr;
}
GH_INLINE void GH_ETH_set_GAR_PA(U8 data)
{
    GH_ETH_GAR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_GAR_REAL;
    d.bitc.pa = data;
    *(volatile U32 *)REG_ETH_GAR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_GAR_PA(void)
{
    GH_ETH_GAR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_GAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pa;
}

/*----------------------------------------------------------------------------*/
/* register ETH_GDR (read/write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_GDR(U32 data)
{
    GH_ETH_GDR_REAL_S real;
    GH_ETH_GDR_S dummy;
    dummy.all = data ;
    real.bitc.gd = dummy.bitc.gd;
    *(volatile U32 *)REG_ETH_GDR_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_GDR(void)
{
    GH_ETH_GDR_REAL_S real;
    GH_ETH_GDR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_GDR_REAL);

    dummy.bitc.gd = real.bitc.gd;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_GDR_GD(U16 data)
{
    GH_ETH_GDR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_GDR_REAL;
    d.bitc.gd = data;
    *(volatile U32 *)REG_ETH_GDR_REAL = d.all;
}
GH_INLINE U16  GH_ETH_get_GDR_GD(void)
{
    GH_ETH_GDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_GDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gd;
}

/*----------------------------------------------------------------------------*/
/* register ETH_FCR (read/write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_FCR(U32 data)
{
    GH_ETH_FCR_REAL_S real;
    GH_ETH_FCR_S dummy;
    dummy.all = data ;
    real.bitc.fcb = dummy.bitc.fcb;
    real.bitc.tfe = dummy.bitc.tfe;
    real.bitc.rfe = dummy.bitc.rfe;
    real.bitc.up = dummy.bitc.up;
    real.bitc.plt = dummy.bitc.plt;
    real.bitc.pt = dummy.bitc.pt;
    *(volatile U32 *)REG_ETH_FCR_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_FCR(void)
{
    GH_ETH_FCR_REAL_S real;
    GH_ETH_FCR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_FCR_REAL);

    dummy.bitc.fcb = real.bitc.fcb;
    dummy.bitc.tfe = real.bitc.tfe;
    dummy.bitc.rfe = real.bitc.rfe;
    dummy.bitc.up = real.bitc.up;
    dummy.bitc.plt = real.bitc.plt;
    dummy.bitc.pt = real.bitc.pt;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_FCR_FCB(U8 data)
{
    GH_ETH_FCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_FCR_REAL;
    d.bitc.fcb = data;
    *(volatile U32 *)REG_ETH_FCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_FCR_FCB(void)
{
    GH_ETH_FCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_FCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fcb;
}
GH_INLINE void GH_ETH_set_FCR_TFE(U8 data)
{
    GH_ETH_FCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_FCR_REAL;
    d.bitc.tfe = data;
    *(volatile U32 *)REG_ETH_FCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_FCR_TFE(void)
{
    GH_ETH_FCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_FCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tfe;
}
GH_INLINE void GH_ETH_set_FCR_RFE(U8 data)
{
    GH_ETH_FCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_FCR_REAL;
    d.bitc.rfe = data;
    *(volatile U32 *)REG_ETH_FCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_FCR_RFE(void)
{
    GH_ETH_FCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_FCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rfe;
}
GH_INLINE void GH_ETH_set_FCR_UP(U8 data)
{
    GH_ETH_FCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_FCR_REAL;
    d.bitc.up = data;
    *(volatile U32 *)REG_ETH_FCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_FCR_UP(void)
{
    GH_ETH_FCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_FCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.up;
}
GH_INLINE void GH_ETH_set_FCR_PLT(U8 data)
{
    GH_ETH_FCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_FCR_REAL;
    d.bitc.plt = data;
    *(volatile U32 *)REG_ETH_FCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_FCR_PLT(void)
{
    GH_ETH_FCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_FCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.plt;
}
GH_INLINE void GH_ETH_set_FCR_PT(U16 data)
{
    GH_ETH_FCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_FCR_REAL;
    d.bitc.pt = data;
    *(volatile U32 *)REG_ETH_FCR_REAL = d.all;
}
GH_INLINE U16  GH_ETH_get_FCR_PT(void)
{
    GH_ETH_FCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_FCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pt;
}

/*----------------------------------------------------------------------------*/
/* register ETH_VTR (read/write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_VTR(U32 data)
{
    GH_ETH_VTR_REAL_S real;
    GH_ETH_VTR_S dummy;
    dummy.all = data ;
    real.bitc.vl = dummy.bitc.vl;
    real.bitc.etv = dummy.bitc.etv;
    *(volatile U32 *)REG_ETH_VTR_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_VTR(void)
{
    GH_ETH_VTR_REAL_S real;
    GH_ETH_VTR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_VTR_REAL);

    dummy.bitc.vl = real.bitc.vl;
    dummy.bitc.etv = real.bitc.etv;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_VTR_VL(U16 data)
{
    GH_ETH_VTR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_VTR_REAL;
    d.bitc.vl = data;
    *(volatile U32 *)REG_ETH_VTR_REAL = d.all;
}
GH_INLINE U16  GH_ETH_get_VTR_VL(void)
{
    GH_ETH_VTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_VTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vl;
}
GH_INLINE void GH_ETH_set_VTR_ETV(U8 data)
{
    GH_ETH_VTR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_VTR_REAL;
    d.bitc.etv = data;
    *(volatile U32 *)REG_ETH_VTR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_VTR_ETV(void)
{
    GH_ETH_VTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_VTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.etv;
}

/*----------------------------------------------------------------------------*/
/* register ETH_VR (read)                                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_ETH_get_VR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_VR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register ETH_MAR0H (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_MAR0H(U32 data)
{
    GH_ETH_MAR0H_REAL_S real;
    GH_ETH_MAR0H_S dummy;
    dummy.all = data ;
    real.bitc.a0 = dummy.bitc.a0;
    real.bitc.m0 = dummy.bitc.m0;
    *(volatile U32 *)REG_ETH_MAR0H_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_MAR0H(void)
{
    GH_ETH_MAR0H_REAL_S real;
    GH_ETH_MAR0H_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_MAR0H_REAL);

    dummy.bitc.a0 = real.bitc.a0;
    dummy.bitc.m0 = real.bitc.m0;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_MAR0H_A0(U16 data)
{
    GH_ETH_MAR0H_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR0H_REAL;
    d.bitc.a0 = data;
    *(volatile U32 *)REG_ETH_MAR0H_REAL = d.all;
}
GH_INLINE U16  GH_ETH_get_MAR0H_A0(void)
{
    GH_ETH_MAR0H_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR0H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.a0;
}
GH_INLINE void GH_ETH_set_MAR0H_M0(U8 data)
{
    GH_ETH_MAR0H_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR0H_REAL;
    d.bitc.m0 = data;
    *(volatile U32 *)REG_ETH_MAR0H_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MAR0H_M0(void)
{
    GH_ETH_MAR0H_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR0H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.m0;
}

/*----------------------------------------------------------------------------*/
/* register ETH_MAR0L (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_MAR0L(U32 data)
{
    GH_ETH_MAR0L_REAL_S real;
    GH_ETH_MAR0L_S dummy;
    dummy.all = data ;
    real.bitc.a0 = dummy.bitc.a0;
    *(volatile U32 *)REG_ETH_MAR0L_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_MAR0L(void)
{
    GH_ETH_MAR0L_REAL_S real;
    GH_ETH_MAR0L_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_MAR0L_REAL);

    dummy.bitc.a0 = real.bitc.a0;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_MAR0L_A0(U32 data)
{
    GH_ETH_MAR0L_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR0L_REAL;
    d.bitc.a0 = data;
    *(volatile U32 *)REG_ETH_MAR0L_REAL = d.all;
}
GH_INLINE U32  GH_ETH_get_MAR0L_A0(void)
{
    GH_ETH_MAR0L_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR0L_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.a0;
}

/*----------------------------------------------------------------------------*/
/* register ETH_MAR1H (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_MAR1H(U32 data)
{
    GH_ETH_MAR1H_REAL_S real;
    GH_ETH_MAR1H_S dummy;
    dummy.all = data ;
    real.bitc.a1 = dummy.bitc.a1;
    real.bitc.mbc = dummy.bitc.mbc;
    real.bitc.sa = dummy.bitc.sa;
    real.bitc.a1e = dummy.bitc.a1e;
    *(volatile U32 *)REG_ETH_MAR1H_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_MAR1H(void)
{
    GH_ETH_MAR1H_REAL_S real;
    GH_ETH_MAR1H_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_MAR1H_REAL);

    dummy.bitc.a1 = real.bitc.a1;
    dummy.bitc.mbc = real.bitc.mbc;
    dummy.bitc.sa = real.bitc.sa;
    dummy.bitc.a1e = real.bitc.a1e;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_MAR1H_A1(U16 data)
{
    GH_ETH_MAR1H_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR1H_REAL;
    d.bitc.a1 = data;
    *(volatile U32 *)REG_ETH_MAR1H_REAL = d.all;
}
GH_INLINE U16  GH_ETH_get_MAR1H_A1(void)
{
    GH_ETH_MAR1H_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR1H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.a1;
}
GH_INLINE void GH_ETH_set_MAR1H_MBC(U8 data)
{
    GH_ETH_MAR1H_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR1H_REAL;
    d.bitc.mbc = data;
    *(volatile U32 *)REG_ETH_MAR1H_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MAR1H_MBC(void)
{
    GH_ETH_MAR1H_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR1H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mbc;
}
GH_INLINE void GH_ETH_set_MAR1H_SA(U8 data)
{
    GH_ETH_MAR1H_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR1H_REAL;
    d.bitc.sa = data;
    *(volatile U32 *)REG_ETH_MAR1H_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MAR1H_SA(void)
{
    GH_ETH_MAR1H_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR1H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sa;
}
GH_INLINE void GH_ETH_set_MAR1H_A1E(U8 data)
{
    GH_ETH_MAR1H_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR1H_REAL;
    d.bitc.a1e = data;
    *(volatile U32 *)REG_ETH_MAR1H_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MAR1H_A1E(void)
{
    GH_ETH_MAR1H_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR1H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.a1e;
}

/*----------------------------------------------------------------------------*/
/* register ETH_MAR1L (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_MAR1L(U32 data)
{
    GH_ETH_MAR1L_REAL_S real;
    GH_ETH_MAR1L_S dummy;
    dummy.all = data ;
    real.bitc.a1 = dummy.bitc.a1;
    *(volatile U32 *)REG_ETH_MAR1L_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_MAR1L(void)
{
    GH_ETH_MAR1L_REAL_S real;
    GH_ETH_MAR1L_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_MAR1L_REAL);

    dummy.bitc.a1 = real.bitc.a1;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_MAR1L_A1(U32 data)
{
    GH_ETH_MAR1L_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR1L_REAL;
    d.bitc.a1 = data;
    *(volatile U32 *)REG_ETH_MAR1L_REAL = d.all;
}
GH_INLINE U32  GH_ETH_get_MAR1L_A1(void)
{
    GH_ETH_MAR1L_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR1L_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.a1;
}

/*----------------------------------------------------------------------------*/
/* register ETH_MAR2H (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_MAR2H(U32 data)
{
    GH_ETH_MAR2H_REAL_S real;
    GH_ETH_MAR2H_S dummy;
    dummy.all = data ;
    real.bitc.a2 = dummy.bitc.a2;
    real.bitc.mbc = dummy.bitc.mbc;
    real.bitc.sa = dummy.bitc.sa;
    real.bitc.a2e = dummy.bitc.a2e;
    *(volatile U32 *)REG_ETH_MAR2H_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_MAR2H(void)
{
    GH_ETH_MAR2H_REAL_S real;
    GH_ETH_MAR2H_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_MAR2H_REAL);

    dummy.bitc.a2 = real.bitc.a2;
    dummy.bitc.mbc = real.bitc.mbc;
    dummy.bitc.sa = real.bitc.sa;
    dummy.bitc.a2e = real.bitc.a2e;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_MAR2H_A2(U16 data)
{
    GH_ETH_MAR2H_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR2H_REAL;
    d.bitc.a2 = data;
    *(volatile U32 *)REG_ETH_MAR2H_REAL = d.all;
}
GH_INLINE U16  GH_ETH_get_MAR2H_A2(void)
{
    GH_ETH_MAR2H_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR2H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.a2;
}
GH_INLINE void GH_ETH_set_MAR2H_MBC(U8 data)
{
    GH_ETH_MAR2H_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR2H_REAL;
    d.bitc.mbc = data;
    *(volatile U32 *)REG_ETH_MAR2H_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MAR2H_MBC(void)
{
    GH_ETH_MAR2H_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR2H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mbc;
}
GH_INLINE void GH_ETH_set_MAR2H_SA(U8 data)
{
    GH_ETH_MAR2H_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR2H_REAL;
    d.bitc.sa = data;
    *(volatile U32 *)REG_ETH_MAR2H_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MAR2H_SA(void)
{
    GH_ETH_MAR2H_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR2H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sa;
}
GH_INLINE void GH_ETH_set_MAR2H_A2E(U8 data)
{
    GH_ETH_MAR2H_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR2H_REAL;
    d.bitc.a2e = data;
    *(volatile U32 *)REG_ETH_MAR2H_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MAR2H_A2E(void)
{
    GH_ETH_MAR2H_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR2H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.a2e;
}

/*----------------------------------------------------------------------------*/
/* register ETH_MAR2L (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_MAR2L(U32 data)
{
    GH_ETH_MAR2L_REAL_S real;
    GH_ETH_MAR2L_S dummy;
    dummy.all = data ;
    real.bitc.a2 = dummy.bitc.a2;
    *(volatile U32 *)REG_ETH_MAR2L_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_MAR2L(void)
{
    GH_ETH_MAR2L_REAL_S real;
    GH_ETH_MAR2L_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_MAR2L_REAL);

    dummy.bitc.a2 = real.bitc.a2;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_MAR2L_A2(U32 data)
{
    GH_ETH_MAR2L_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MAR2L_REAL;
    d.bitc.a2 = data;
    *(volatile U32 *)REG_ETH_MAR2L_REAL = d.all;
}
GH_INLINE U32  GH_ETH_get_MAR2L_A2(void)
{
    GH_ETH_MAR2L_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MAR2L_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.a2;
}

/*----------------------------------------------------------------------------*/
/* register ETH_EPHY_DEBUG (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_EPHY_DEBUG(U32 data)
{
    GH_ETH_EPHY_DEBUG_REAL_S real;
    GH_ETH_EPHY_DEBUG_S dummy;
    dummy.all = data ;
    real.bitc.debug = dummy.bitc.debug;
    *(volatile U32 *)REG_ETH_EPHY_DEBUG_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_EPHY_DEBUG(void)
{
    GH_ETH_EPHY_DEBUG_REAL_S real;
    GH_ETH_EPHY_DEBUG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_EPHY_DEBUG_REAL);

    dummy.bitc.debug = real.bitc.debug;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_EPHY_DEBUG_debug(U32 data)
{
    GH_ETH_EPHY_DEBUG_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_EPHY_DEBUG_REAL;
    d.bitc.debug = data;
    *(volatile U32 *)REG_ETH_EPHY_DEBUG_REAL = d.all;
}
GH_INLINE U32  GH_ETH_get_EPHY_DEBUG_debug(void)
{
    GH_ETH_EPHY_DEBUG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_EPHY_DEBUG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.debug;
}

/*----------------------------------------------------------------------------*/
/* register ETH_BMR (read/write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_BMR(U32 data)
{
    GH_ETH_BMR_REAL_S real;
    GH_ETH_BMR_S dummy;
    dummy.all = data ;
    real.bitc.swr = dummy.bitc.swr;
    real.bitc.da = dummy.bitc.da;
    real.bitc.dsl = dummy.bitc.dsl;
    real.bitc.pbl = dummy.bitc.pbl;
    real.bitc.pr = dummy.bitc.pr;
    real.bitc.fb = dummy.bitc.fb;
    real.bitc.rpbl = dummy.bitc.rpbl;
    real.bitc.usp = dummy.bitc.usp;
    real.bitc.pbl4x = dummy.bitc.pbl4x;
    real.bitc.aal = dummy.bitc.aal;
    *(volatile U32 *)REG_ETH_BMR_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_BMR(void)
{
    GH_ETH_BMR_REAL_S real;
    GH_ETH_BMR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_BMR_REAL);

    dummy.bitc.swr = real.bitc.swr;
    dummy.bitc.da = real.bitc.da;
    dummy.bitc.dsl = real.bitc.dsl;
    dummy.bitc.pbl = real.bitc.pbl;
    dummy.bitc.pr = real.bitc.pr;
    dummy.bitc.fb = real.bitc.fb;
    dummy.bitc.rpbl = real.bitc.rpbl;
    dummy.bitc.usp = real.bitc.usp;
    dummy.bitc.pbl4x = real.bitc.pbl4x;
    dummy.bitc.aal = real.bitc.aal;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_BMR_SWR(U8 data)
{
    GH_ETH_BMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR_REAL;
    d.bitc.swr = data;
    *(volatile U32 *)REG_ETH_BMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_BMR_SWR(void)
{
    GH_ETH_BMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.swr;
}
GH_INLINE void GH_ETH_set_BMR_DA(U8 data)
{
    GH_ETH_BMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR_REAL;
    d.bitc.da = data;
    *(volatile U32 *)REG_ETH_BMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_BMR_DA(void)
{
    GH_ETH_BMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.da;
}
GH_INLINE void GH_ETH_set_BMR_DSL(U8 data)
{
    GH_ETH_BMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR_REAL;
    d.bitc.dsl = data;
    *(volatile U32 *)REG_ETH_BMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_BMR_DSL(void)
{
    GH_ETH_BMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsl;
}
GH_INLINE void GH_ETH_set_BMR_PBL(U8 data)
{
    GH_ETH_BMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR_REAL;
    d.bitc.pbl = data;
    *(volatile U32 *)REG_ETH_BMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_BMR_PBL(void)
{
    GH_ETH_BMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pbl;
}
GH_INLINE void GH_ETH_set_BMR_PR(U8 data)
{
    GH_ETH_BMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR_REAL;
    d.bitc.pr = data;
    *(volatile U32 *)REG_ETH_BMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_BMR_PR(void)
{
    GH_ETH_BMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pr;
}
GH_INLINE void GH_ETH_set_BMR_FB(U8 data)
{
    GH_ETH_BMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR_REAL;
    d.bitc.fb = data;
    *(volatile U32 *)REG_ETH_BMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_BMR_FB(void)
{
    GH_ETH_BMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fb;
}
GH_INLINE void GH_ETH_set_BMR_RPBL(U8 data)
{
    GH_ETH_BMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR_REAL;
    d.bitc.rpbl = data;
    *(volatile U32 *)REG_ETH_BMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_BMR_RPBL(void)
{
    GH_ETH_BMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rpbl;
}
GH_INLINE void GH_ETH_set_BMR_USP(U8 data)
{
    GH_ETH_BMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR_REAL;
    d.bitc.usp = data;
    *(volatile U32 *)REG_ETH_BMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_BMR_USP(void)
{
    GH_ETH_BMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.usp;
}
GH_INLINE void GH_ETH_set_BMR_PBL4X(U8 data)
{
    GH_ETH_BMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR_REAL;
    d.bitc.pbl4x = data;
    *(volatile U32 *)REG_ETH_BMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_BMR_PBL4X(void)
{
    GH_ETH_BMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pbl4x;
}
GH_INLINE void GH_ETH_set_BMR_AAL(U8 data)
{
    GH_ETH_BMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_BMR_REAL;
    d.bitc.aal = data;
    *(volatile U32 *)REG_ETH_BMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_BMR_AAL(void)
{
    GH_ETH_BMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_BMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.aal;
}

/*----------------------------------------------------------------------------*/
/* register ETH_TPDR (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_TPDR(U32 data)
{
    *(volatile U32 *)REG_ETH_TPDR_REAL = data;
}
GH_INLINE U32  GH_ETH_get_TPDR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_TPDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register ETH_RPDR (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_RPDR(U32 data)
{
    *(volatile U32 *)REG_ETH_RPDR_REAL = data;
}
GH_INLINE U32  GH_ETH_get_RPDR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_RPDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register ETH_RDLAR (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_RDLAR(U32 data)
{
    *(volatile U32 *)REG_ETH_RDLAR_REAL = data;
}
GH_INLINE U32  GH_ETH_get_RDLAR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_RDLAR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register ETH_TDLAR (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_TDLAR(U32 data)
{
    *(volatile U32 *)REG_ETH_TDLAR_REAL = data;
}
GH_INLINE U32  GH_ETH_get_TDLAR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_TDLAR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register ETH_SR (read/write)                                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_SR(U32 data)
{
    GH_ETH_SR_REAL_S real;
    GH_ETH_SR_S dummy;
    dummy.all = data ;
    real.bitc.ti = dummy.bitc.ti;
    real.bitc.tps = dummy.bitc.tps;
    real.bitc.tu = dummy.bitc.tu;
    real.bitc.tjt = dummy.bitc.tjt;
    real.bitc.ovf = dummy.bitc.ovf;
    real.bitc.unf = dummy.bitc.unf;
    real.bitc.ri = dummy.bitc.ri;
    real.bitc.ru = dummy.bitc.ru;
    real.bitc.rps = dummy.bitc.rps;
    real.bitc.rwt = dummy.bitc.rwt;
    real.bitc.eti = dummy.bitc.eti;
    real.bitc.fbe = dummy.bitc.fbe;
    real.bitc.eri = dummy.bitc.eri;
    real.bitc.ais = dummy.bitc.ais;
    real.bitc.nis = dummy.bitc.nis;
    real.bitc.rs = dummy.bitc.rs;
    real.bitc.ts = dummy.bitc.ts;
    real.bitc.eb = dummy.bitc.eb;
    real.bitc.gli = dummy.bitc.gli;
    real.bitc.gmi = dummy.bitc.gmi;
    real.bitc.gpi = dummy.bitc.gpi;
    *(volatile U32 *)REG_ETH_SR_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_SR(void)
{
    GH_ETH_SR_REAL_S real;
    GH_ETH_SR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_SR_REAL);

    dummy.bitc.ti = real.bitc.ti;
    dummy.bitc.tps = real.bitc.tps;
    dummy.bitc.tu = real.bitc.tu;
    dummy.bitc.tjt = real.bitc.tjt;
    dummy.bitc.ovf = real.bitc.ovf;
    dummy.bitc.unf = real.bitc.unf;
    dummy.bitc.ri = real.bitc.ri;
    dummy.bitc.ru = real.bitc.ru;
    dummy.bitc.rps = real.bitc.rps;
    dummy.bitc.rwt = real.bitc.rwt;
    dummy.bitc.eti = real.bitc.eti;
    dummy.bitc.fbe = real.bitc.fbe;
    dummy.bitc.eri = real.bitc.eri;
    dummy.bitc.ais = real.bitc.ais;
    dummy.bitc.nis = real.bitc.nis;
    dummy.bitc.rs = real.bitc.rs;
    dummy.bitc.ts = real.bitc.ts;
    dummy.bitc.eb = real.bitc.eb;
    dummy.bitc.gli = real.bitc.gli;
    dummy.bitc.gmi = real.bitc.gmi;
    dummy.bitc.gpi = real.bitc.gpi;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_SR_TI(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.ti = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_TI(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ti;
}
GH_INLINE void GH_ETH_set_SR_TPS(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.tps = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_TPS(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tps;
}
GH_INLINE void GH_ETH_set_SR_TU(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.tu = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_TU(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tu;
}
GH_INLINE void GH_ETH_set_SR_TJT(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.tjt = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_TJT(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tjt;
}
GH_INLINE void GH_ETH_set_SR_OVF(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.ovf = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_OVF(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ovf;
}
GH_INLINE void GH_ETH_set_SR_UNF(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.unf = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_UNF(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.unf;
}
GH_INLINE void GH_ETH_set_SR_RI(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.ri = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_RI(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ri;
}
GH_INLINE void GH_ETH_set_SR_RU(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.ru = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_RU(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ru;
}
GH_INLINE void GH_ETH_set_SR_RPS(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.rps = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_RPS(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rps;
}
GH_INLINE void GH_ETH_set_SR_RWT(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.rwt = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_RWT(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rwt;
}
GH_INLINE void GH_ETH_set_SR_ETI(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.eti = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_ETI(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.eti;
}
GH_INLINE void GH_ETH_set_SR_FBE(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.fbe = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_FBE(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fbe;
}
GH_INLINE void GH_ETH_set_SR_ERI(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.eri = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_ERI(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.eri;
}
GH_INLINE void GH_ETH_set_SR_AIS(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.ais = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_AIS(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ais;
}
GH_INLINE void GH_ETH_set_SR_NIS(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.nis = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_NIS(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.nis;
}
GH_INLINE void GH_ETH_set_SR_RS(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.rs = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_RS(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rs;
}
GH_INLINE void GH_ETH_set_SR_TS(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.ts = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_TS(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts;
}
GH_INLINE void GH_ETH_set_SR_EB(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.eb = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_EB(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.eb;
}
GH_INLINE void GH_ETH_set_SR_GLI(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.gli = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_GLI(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gli;
}
GH_INLINE void GH_ETH_set_SR_GMI(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.gmi = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_GMI(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gmi;
}
GH_INLINE void GH_ETH_set_SR_GPI(U8 data)
{
    GH_ETH_SR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_SR_REAL;
    d.bitc.gpi = data;
    *(volatile U32 *)REG_ETH_SR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_SR_GPI(void)
{
    GH_ETH_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gpi;
}

/*----------------------------------------------------------------------------*/
/* register ETH_OMR (read/write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_OMR(U32 data)
{
    GH_ETH_OMR_REAL_S real;
    GH_ETH_OMR_S dummy;
    dummy.all = data ;
    real.bitc.sr = dummy.bitc.sr;
    real.bitc.osf = dummy.bitc.osf;
    real.bitc.rtc = dummy.bitc.rtc;
    real.bitc.fuf = dummy.bitc.fuf;
    real.bitc.fef = dummy.bitc.fef;
    real.bitc.efc = dummy.bitc.efc;
    real.bitc.rfa = dummy.bitc.rfa;
    real.bitc.rfd = dummy.bitc.rfd;
    real.bitc.st = dummy.bitc.st;
    real.bitc.ttc = dummy.bitc.ttc;
    real.bitc.ftf = dummy.bitc.ftf;
    real.bitc.sf = dummy.bitc.sf;
    *(volatile U32 *)REG_ETH_OMR_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_OMR(void)
{
    GH_ETH_OMR_REAL_S real;
    GH_ETH_OMR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_OMR_REAL);

    dummy.bitc.sr = real.bitc.sr;
    dummy.bitc.osf = real.bitc.osf;
    dummy.bitc.rtc = real.bitc.rtc;
    dummy.bitc.fuf = real.bitc.fuf;
    dummy.bitc.fef = real.bitc.fef;
    dummy.bitc.efc = real.bitc.efc;
    dummy.bitc.rfa = real.bitc.rfa;
    dummy.bitc.rfd = real.bitc.rfd;
    dummy.bitc.st = real.bitc.st;
    dummy.bitc.ttc = real.bitc.ttc;
    dummy.bitc.ftf = real.bitc.ftf;
    dummy.bitc.sf = real.bitc.sf;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_OMR_SR(U8 data)
{
    GH_ETH_OMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR_REAL;
    d.bitc.sr = data;
    *(volatile U32 *)REG_ETH_OMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_OMR_SR(void)
{
    GH_ETH_OMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sr;
}
GH_INLINE void GH_ETH_set_OMR_OSF(U8 data)
{
    GH_ETH_OMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR_REAL;
    d.bitc.osf = data;
    *(volatile U32 *)REG_ETH_OMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_OMR_OSF(void)
{
    GH_ETH_OMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.osf;
}
GH_INLINE void GH_ETH_set_OMR_RTC(U8 data)
{
    GH_ETH_OMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR_REAL;
    d.bitc.rtc = data;
    *(volatile U32 *)REG_ETH_OMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_OMR_RTC(void)
{
    GH_ETH_OMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rtc;
}
GH_INLINE void GH_ETH_set_OMR_FUF(U8 data)
{
    GH_ETH_OMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR_REAL;
    d.bitc.fuf = data;
    *(volatile U32 *)REG_ETH_OMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_OMR_FUF(void)
{
    GH_ETH_OMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fuf;
}
GH_INLINE void GH_ETH_set_OMR_FEF(U8 data)
{
    GH_ETH_OMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR_REAL;
    d.bitc.fef = data;
    *(volatile U32 *)REG_ETH_OMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_OMR_FEF(void)
{
    GH_ETH_OMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fef;
}
GH_INLINE void GH_ETH_set_OMR_EFC(U8 data)
{
    GH_ETH_OMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR_REAL;
    d.bitc.efc = data;
    *(volatile U32 *)REG_ETH_OMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_OMR_EFC(void)
{
    GH_ETH_OMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.efc;
}
GH_INLINE void GH_ETH_set_OMR_RFA(U8 data)
{
    GH_ETH_OMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR_REAL;
    d.bitc.rfa = data;
    *(volatile U32 *)REG_ETH_OMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_OMR_RFA(void)
{
    GH_ETH_OMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rfa;
}
GH_INLINE void GH_ETH_set_OMR_RFD(U8 data)
{
    GH_ETH_OMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR_REAL;
    d.bitc.rfd = data;
    *(volatile U32 *)REG_ETH_OMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_OMR_RFD(void)
{
    GH_ETH_OMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rfd;
}
GH_INLINE void GH_ETH_set_OMR_ST(U8 data)
{
    GH_ETH_OMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR_REAL;
    d.bitc.st = data;
    *(volatile U32 *)REG_ETH_OMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_OMR_ST(void)
{
    GH_ETH_OMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.st;
}
GH_INLINE void GH_ETH_set_OMR_TTC(U8 data)
{
    GH_ETH_OMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR_REAL;
    d.bitc.ttc = data;
    *(volatile U32 *)REG_ETH_OMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_OMR_TTC(void)
{
    GH_ETH_OMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ttc;
}
GH_INLINE void GH_ETH_set_OMR_FTF(U8 data)
{
    GH_ETH_OMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR_REAL;
    d.bitc.ftf = data;
    *(volatile U32 *)REG_ETH_OMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_OMR_FTF(void)
{
    GH_ETH_OMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ftf;
}
GH_INLINE void GH_ETH_set_OMR_SF(U8 data)
{
    GH_ETH_OMR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_OMR_REAL;
    d.bitc.sf = data;
    *(volatile U32 *)REG_ETH_OMR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_OMR_SF(void)
{
    GH_ETH_OMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_OMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sf;
}

/*----------------------------------------------------------------------------*/
/* register ETH_IER (read/write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_IER(U32 data)
{
    GH_ETH_IER_REAL_S real;
    GH_ETH_IER_S dummy;
    dummy.all = data ;
    real.bitc.ti = dummy.bitc.ti;
    real.bitc.ts = dummy.bitc.ts;
    real.bitc.tu = dummy.bitc.tu;
    real.bitc.tj = dummy.bitc.tj;
    real.bitc.ov = dummy.bitc.ov;
    real.bitc.un = dummy.bitc.un;
    real.bitc.ri = dummy.bitc.ri;
    real.bitc.ru = dummy.bitc.ru;
    real.bitc.rs = dummy.bitc.rs;
    real.bitc.rw = dummy.bitc.rw;
    real.bitc.ete = dummy.bitc.ete;
    real.bitc.fbe = dummy.bitc.fbe;
    real.bitc.ere = dummy.bitc.ere;
    real.bitc.ai = dummy.bitc.ai;
    real.bitc.ni = dummy.bitc.ni;
    *(volatile U32 *)REG_ETH_IER_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_IER(void)
{
    GH_ETH_IER_REAL_S real;
    GH_ETH_IER_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_IER_REAL);

    dummy.bitc.ti = real.bitc.ti;
    dummy.bitc.ts = real.bitc.ts;
    dummy.bitc.tu = real.bitc.tu;
    dummy.bitc.tj = real.bitc.tj;
    dummy.bitc.ov = real.bitc.ov;
    dummy.bitc.un = real.bitc.un;
    dummy.bitc.ri = real.bitc.ri;
    dummy.bitc.ru = real.bitc.ru;
    dummy.bitc.rs = real.bitc.rs;
    dummy.bitc.rw = real.bitc.rw;
    dummy.bitc.ete = real.bitc.ete;
    dummy.bitc.fbe = real.bitc.fbe;
    dummy.bitc.ere = real.bitc.ere;
    dummy.bitc.ai = real.bitc.ai;
    dummy.bitc.ni = real.bitc.ni;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_IER_TI(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.ti = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_TI(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ti;
}
GH_INLINE void GH_ETH_set_IER_TS(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.ts = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_TS(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ts;
}
GH_INLINE void GH_ETH_set_IER_TU(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.tu = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_TU(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tu;
}
GH_INLINE void GH_ETH_set_IER_TJ(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.tj = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_TJ(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tj;
}
GH_INLINE void GH_ETH_set_IER_OV(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.ov = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_OV(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ov;
}
GH_INLINE void GH_ETH_set_IER_UN(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.un = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_UN(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.un;
}
GH_INLINE void GH_ETH_set_IER_RI(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.ri = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_RI(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ri;
}
GH_INLINE void GH_ETH_set_IER_RU(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.ru = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_RU(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ru;
}
GH_INLINE void GH_ETH_set_IER_RS(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.rs = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_RS(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rs;
}
GH_INLINE void GH_ETH_set_IER_RW(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.rw = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_RW(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rw;
}
GH_INLINE void GH_ETH_set_IER_ETE(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.ete = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_ETE(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ete;
}
GH_INLINE void GH_ETH_set_IER_FBE(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.fbe = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_FBE(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fbe;
}
GH_INLINE void GH_ETH_set_IER_ERE(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.ere = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_ERE(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ere;
}
GH_INLINE void GH_ETH_set_IER_AI(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.ai = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_AI(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ai;
}
GH_INLINE void GH_ETH_set_IER_NI(U8 data)
{
    GH_ETH_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_IER_REAL;
    d.bitc.ni = data;
    *(volatile U32 *)REG_ETH_IER_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_IER_NI(void)
{
    GH_ETH_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ni;
}

/*----------------------------------------------------------------------------*/
/* register ETH_MFBOCR (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_MFBOCR(U32 data)
{
    GH_ETH_MFBOCR_REAL_S real;
    GH_ETH_MFBOCR_S dummy;
    dummy.all = data ;
    real.bitc.nmfh = dummy.bitc.nmfh;
    real.bitc.ovmfc = dummy.bitc.ovmfc;
    real.bitc.nmff = dummy.bitc.nmff;
    real.bitc.onmff = dummy.bitc.onmff;
    *(volatile U32 *)REG_ETH_MFBOCR_REAL = real.all;
}
GH_INLINE U32  GH_ETH_get_MFBOCR(void)
{
    GH_ETH_MFBOCR_REAL_S real;
    GH_ETH_MFBOCR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_ETH_MFBOCR_REAL);

    dummy.bitc.nmfh = real.bitc.nmfh;
    dummy.bitc.ovmfc = real.bitc.ovmfc;
    dummy.bitc.nmff = real.bitc.nmff;
    dummy.bitc.onmff = real.bitc.onmff;
    return dummy.all;
}
GH_INLINE void GH_ETH_set_MFBOCR_NMFH(U16 data)
{
    GH_ETH_MFBOCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFBOCR_REAL;
    d.bitc.nmfh = data;
    *(volatile U32 *)REG_ETH_MFBOCR_REAL = d.all;
}
GH_INLINE U16  GH_ETH_get_MFBOCR_NMFH(void)
{
    GH_ETH_MFBOCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFBOCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.nmfh;
}
GH_INLINE void GH_ETH_set_MFBOCR_OVMFC(U8 data)
{
    GH_ETH_MFBOCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFBOCR_REAL;
    d.bitc.ovmfc = data;
    *(volatile U32 *)REG_ETH_MFBOCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MFBOCR_OVMFC(void)
{
    GH_ETH_MFBOCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFBOCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ovmfc;
}
GH_INLINE void GH_ETH_set_MFBOCR_NMFF(U16 data)
{
    GH_ETH_MFBOCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFBOCR_REAL;
    d.bitc.nmff = data;
    *(volatile U32 *)REG_ETH_MFBOCR_REAL = d.all;
}
GH_INLINE U16  GH_ETH_get_MFBOCR_NMFF(void)
{
    GH_ETH_MFBOCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFBOCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.nmff;
}
GH_INLINE void GH_ETH_set_MFBOCR_ONMFF(U8 data)
{
    GH_ETH_MFBOCR_REAL_S d;
    d.all = *(volatile U32 *)REG_ETH_MFBOCR_REAL;
    d.bitc.onmff = data;
    *(volatile U32 *)REG_ETH_MFBOCR_REAL = d.all;
}
GH_INLINE U8   GH_ETH_get_MFBOCR_ONMFF(void)
{
    GH_ETH_MFBOCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ETH_MFBOCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.onmff;
}

/*----------------------------------------------------------------------------*/
/* register ETH_CHTDR (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_CHTDR(U32 data)
{
    *(volatile U32 *)REG_ETH_CHTDR_REAL = data;
}
GH_INLINE U32  GH_ETH_get_CHTDR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_CHTDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register ETH_CHRDR (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_CHRDR(U32 data)
{
    *(volatile U32 *)REG_ETH_CHRDR_REAL = data;
}
GH_INLINE U32  GH_ETH_get_CHRDR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_CHRDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register ETH_CHTBAR (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_CHTBAR(U32 data)
{
    *(volatile U32 *)REG_ETH_CHTBAR_REAL = data;
}
GH_INLINE U32  GH_ETH_get_CHTBAR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_CHTBAR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register ETH_CHRBAR (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_set_CHRBAR(U32 data)
{
    *(volatile U32 *)REG_ETH_CHRBAR_REAL = data;
}
GH_INLINE U32  GH_ETH_get_CHRBAR(void)
{
    U32 value = (*(volatile U32 *)REG_ETH_CHRBAR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_ETH_init(void)
{
    GH_ETH_set_MCR((U32)0x00000000);
    GH_ETH_set_MFFR((U32)0x00000000);
    GH_ETH_set_MHTRH((U32)0x00000000);
    GH_ETH_set_MHTRL((U32)0x00000000);
    GH_ETH_set_GAR((U32)0x00000000);
    GH_ETH_set_GDR((U32)0x00000000);
    GH_ETH_set_FCR((U32)0x00000000);
    GH_ETH_set_VTR((U32)0x00000000);
    GH_ETH_set_MAR0H((U32)0x00000000);
    GH_ETH_set_MAR0L((U32)0x00000000);
    GH_ETH_set_MAR1H((U32)0x00000000);
    GH_ETH_set_MAR1L((U32)0x00000000);
    GH_ETH_set_MAR2H((U32)0x00000000);
    GH_ETH_set_MAR2L((U32)0x00000000);
    GH_ETH_set_EPHY_DEBUG((U32)0x00000000);
    GH_ETH_set_BMR((U32)0x00010000);
    GH_ETH_set_SR((U32)0x00000000);
    GH_ETH_set_OMR((U32)0x00000000);
    GH_ETH_set_IER((U32)0x00000000);
    GH_ETH_set_MFBOCR((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

