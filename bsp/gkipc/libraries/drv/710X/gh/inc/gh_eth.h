/*!
*******************************************************************************
**
** \file      gh_eth.h
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
#ifndef _GH_ETH_H
#define _GH_ETH_H

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

#define GH_ETH_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_ETH_DEBUG_PRINT_FUNCTION printk
#else
#define GH_ETH_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_ETH_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_ETH_MCR                                         FIO_ADDRESS(ETH,0x9000E000) /* read/write */
#define REG_ETH_MFFR                                        FIO_ADDRESS(ETH,0x9000E004) /* read/write */
#define REG_ETH_MHTRH                                       FIO_ADDRESS(ETH,0x9000E008) /* read/write */
#define REG_ETH_MHTRL                                       FIO_ADDRESS(ETH,0x9000E00C) /* read/write */
#define REG_ETH_GAR                                         FIO_ADDRESS(ETH,0x9000E010) /* read/write */
#define REG_ETH_GDR                                         FIO_ADDRESS(ETH,0x9000E014) /* read/write */
#define REG_ETH_FCR                                         FIO_ADDRESS(ETH,0x9000E018) /* read/write */
#define REG_ETH_VTR                                         FIO_ADDRESS(ETH,0x9000E01C) /* read/write */
#define REG_ETH_VR                                          FIO_ADDRESS(ETH,0x9000E020) /* read */
#define REG_ETH_MAR0H                                       FIO_ADDRESS(ETH,0x9000E040) /* read/write */
#define REG_ETH_MAR0L                                       FIO_ADDRESS(ETH,0x9000E044) /* read/write */
#define REG_ETH_MAR1H                                       FIO_ADDRESS(ETH,0x9000E048) /* read/write */
#define REG_ETH_MAR1L                                       FIO_ADDRESS(ETH,0x9000E04C) /* read/write */
#define REG_ETH_MAR2H                                       FIO_ADDRESS(ETH,0x9000E050) /* read/write */
#define REG_ETH_MAR2L                                       FIO_ADDRESS(ETH,0x9000E054) /* read/write */
#define REG_ETH_EPHY_DEBUG                                  FIO_ADDRESS(ETH,0x9000E058) /* read/write */
#define REG_ETH_BMR                                         FIO_ADDRESS(ETH,0x9000F000) /* read/write */
#define REG_ETH_TPDR                                        FIO_ADDRESS(ETH,0x9000F004) /* read/write */
#define REG_ETH_RPDR                                        FIO_ADDRESS(ETH,0x9000F008) /* read/write */
#define REG_ETH_RDLAR                                       FIO_ADDRESS(ETH,0x9000F00C) /* read/write */
#define REG_ETH_TDLAR                                       FIO_ADDRESS(ETH,0x9000F010) /* read/write */
#define REG_ETH_SR                                          FIO_ADDRESS(ETH,0x9000F014) /* read/write */
#define REG_ETH_OMR                                         FIO_ADDRESS(ETH,0x9000F018) /* read/write */
#define REG_ETH_IER                                         FIO_ADDRESS(ETH,0x9000F01C) /* read/write */
#define REG_ETH_MFBOCR                                      FIO_ADDRESS(ETH,0x9000F020) /* read/write */
#define REG_ETH_CHTDR                                       FIO_ADDRESS(ETH,0x9000F048) /* read/write */
#define REG_ETH_CHRDR                                       FIO_ADDRESS(ETH,0x9000F04C) /* read/write */
#define REG_ETH_CHTBAR                                      FIO_ADDRESS(ETH,0x9000F050) /* read/write */
#define REG_ETH_CHRBAR                                      FIO_ADDRESS(ETH,0x9000F054) /* read/write */

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
} GH_ETH_MCR_S;

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
} GH_ETH_MFFR_S;

typedef union { /* ETH_MHTRH */
    U32 all;
    struct {
        U32 hth                         : 32;
    } bitc;
} GH_ETH_MHTRH_S;

typedef union { /* ETH_MHTRL */
    U32 all;
    struct {
        U32 htl                         : 32;
    } bitc;
} GH_ETH_MHTRL_S;

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
} GH_ETH_GAR_S;

typedef union { /* ETH_GDR */
    U32 all;
    struct {
        U32 gd                          : 16;
        U32                             : 16;
    } bitc;
} GH_ETH_GDR_S;

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
} GH_ETH_FCR_S;

typedef union { /* ETH_VTR */
    U32 all;
    struct {
        U32 vl                          : 16;
        U32 etv                         : 1;
        U32                             : 15;
    } bitc;
} GH_ETH_VTR_S;

typedef union { /* ETH_MAR0H */
    U32 all;
    struct {
        U32 a0                          : 16;
        U32                             : 15;
        U32 m0                          : 1;
    } bitc;
} GH_ETH_MAR0H_S;

typedef union { /* ETH_MAR0L */
    U32 all;
    struct {
        U32 a0                          : 32;
    } bitc;
} GH_ETH_MAR0L_S;

typedef union { /* ETH_MAR1H */
    U32 all;
    struct {
        U32 a1                          : 16;
        U32                             : 8;
        U32 mbc                         : 6;
        U32 sa                          : 1;
        U32 a1e                         : 1;
    } bitc;
} GH_ETH_MAR1H_S;

typedef union { /* ETH_MAR1L */
    U32 all;
    struct {
        U32 a1                          : 32;
    } bitc;
} GH_ETH_MAR1L_S;

typedef union { /* ETH_MAR2H */
    U32 all;
    struct {
        U32 a2                          : 16;
        U32                             : 8;
        U32 mbc                         : 6;
        U32 sa                          : 1;
        U32 a2e                         : 1;
    } bitc;
} GH_ETH_MAR2H_S;

typedef union { /* ETH_MAR2L */
    U32 all;
    struct {
        U32 a2                          : 32;
    } bitc;
} GH_ETH_MAR2L_S;

typedef union { /* ETH_EPHY_DEBUG */
    U32 all;
    struct {
        U32                             : 8;
        U32 debug                       : 24;
    } bitc;
} GH_ETH_EPHY_DEBUG_S;

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
} GH_ETH_BMR_S;

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
} GH_ETH_SR_S;

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
} GH_ETH_OMR_S;

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
} GH_ETH_IER_S;

typedef union { /* ETH_MFBOCR */
    U32 all;
    struct {
        U32 nmfh                        : 16;
        U32 ovmfc                       : 1;
        U32 nmff                        : 11;
        U32 onmff                       : 1;
        U32                             : 3;
    } bitc;
} GH_ETH_MFBOCR_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register ETH_MCR (read/write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_MCR'. */
void GH_ETH_set_MCR(U32 data);
/*! \brief Reads the register 'ETH_MCR'. */
U32  GH_ETH_get_MCR(void);
/*! \brief Writes the bit group 'RE' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_RE(U8 data);
/*! \brief Reads the bit group 'RE' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_RE(void);
/*! \brief Writes the bit group 'TE' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_TE(U8 data);
/*! \brief Reads the bit group 'TE' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_TE(void);
/*! \brief Writes the bit group 'DC' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_DC(U8 data);
/*! \brief Reads the bit group 'DC' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_DC(void);
/*! \brief Writes the bit group 'BL' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_BL(U8 data);
/*! \brief Reads the bit group 'BL' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_BL(void);
/*! \brief Writes the bit group 'ACS' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_ACS(U8 data);
/*! \brief Reads the bit group 'ACS' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_ACS(void);
/*! \brief Writes the bit group 'LUD' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_LUD(U8 data);
/*! \brief Reads the bit group 'LUD' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_LUD(void);
/*! \brief Writes the bit group 'DR' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_DR(U8 data);
/*! \brief Reads the bit group 'DR' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_DR(void);
/*! \brief Writes the bit group 'IPC' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_IPC(U8 data);
/*! \brief Reads the bit group 'IPC' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_IPC(void);
/*! \brief Writes the bit group 'DM' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_DM(U8 data);
/*! \brief Reads the bit group 'DM' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_DM(void);
/*! \brief Writes the bit group 'LM' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_LM(U8 data);
/*! \brief Reads the bit group 'LM' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_LM(void);
/*! \brief Writes the bit group 'DRO' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_DRO(U8 data);
/*! \brief Reads the bit group 'DRO' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_DRO(void);
/*! \brief Writes the bit group 'FES' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_FES(U8 data);
/*! \brief Reads the bit group 'FES' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_FES(void);
/*! \brief Writes the bit group 'PS' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_PS(U8 data);
/*! \brief Reads the bit group 'PS' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_PS(void);
/*! \brief Writes the bit group 'DCRS' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_DCRS(U8 data);
/*! \brief Reads the bit group 'DCRS' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_DCRS(void);
/*! \brief Writes the bit group 'IFG' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_IFG(U8 data);
/*! \brief Reads the bit group 'IFG' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_IFG(void);
/*! \brief Writes the bit group 'JE' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_JE(U8 data);
/*! \brief Reads the bit group 'JE' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_JE(void);
/*! \brief Writes the bit group 'BE' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_BE(U8 data);
/*! \brief Reads the bit group 'BE' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_BE(void);
/*! \brief Writes the bit group 'JD' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_JD(U8 data);
/*! \brief Reads the bit group 'JD' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_JD(void);
/*! \brief Writes the bit group 'WD' of register 'ETH_MCR'. */
void GH_ETH_set_MCR_WD(U8 data);
/*! \brief Reads the bit group 'WD' of register 'ETH_MCR'. */
U8   GH_ETH_get_MCR_WD(void);

/*----------------------------------------------------------------------------*/
/* register ETH_MFFR (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_MFFR'. */
void GH_ETH_set_MFFR(U32 data);
/*! \brief Reads the register 'ETH_MFFR'. */
U32  GH_ETH_get_MFFR(void);
/*! \brief Writes the bit group 'PR' of register 'ETH_MFFR'. */
void GH_ETH_set_MFFR_PR(U8 data);
/*! \brief Reads the bit group 'PR' of register 'ETH_MFFR'. */
U8   GH_ETH_get_MFFR_PR(void);
/*! \brief Writes the bit group 'HUC' of register 'ETH_MFFR'. */
void GH_ETH_set_MFFR_HUC(U8 data);
/*! \brief Reads the bit group 'HUC' of register 'ETH_MFFR'. */
U8   GH_ETH_get_MFFR_HUC(void);
/*! \brief Writes the bit group 'HMC' of register 'ETH_MFFR'. */
void GH_ETH_set_MFFR_HMC(U8 data);
/*! \brief Reads the bit group 'HMC' of register 'ETH_MFFR'. */
U8   GH_ETH_get_MFFR_HMC(void);
/*! \brief Writes the bit group 'IFT' of register 'ETH_MFFR'. */
void GH_ETH_set_MFFR_IFT(U8 data);
/*! \brief Reads the bit group 'IFT' of register 'ETH_MFFR'. */
U8   GH_ETH_get_MFFR_IFT(void);
/*! \brief Writes the bit group 'PM' of register 'ETH_MFFR'. */
void GH_ETH_set_MFFR_PM(U8 data);
/*! \brief Reads the bit group 'PM' of register 'ETH_MFFR'. */
U8   GH_ETH_get_MFFR_PM(void);
/*! \brief Writes the bit group 'DB' of register 'ETH_MFFR'. */
void GH_ETH_set_MFFR_DB(U8 data);
/*! \brief Reads the bit group 'DB' of register 'ETH_MFFR'. */
U8   GH_ETH_get_MFFR_DB(void);
/*! \brief Writes the bit group 'PCF' of register 'ETH_MFFR'. */
void GH_ETH_set_MFFR_PCF(U8 data);
/*! \brief Reads the bit group 'PCF' of register 'ETH_MFFR'. */
U8   GH_ETH_get_MFFR_PCF(void);
/*! \brief Writes the bit group 'SAIF' of register 'ETH_MFFR'. */
void GH_ETH_set_MFFR_SAIF(U8 data);
/*! \brief Reads the bit group 'SAIF' of register 'ETH_MFFR'. */
U8   GH_ETH_get_MFFR_SAIF(void);
/*! \brief Writes the bit group 'SAF' of register 'ETH_MFFR'. */
void GH_ETH_set_MFFR_SAF(U8 data);
/*! \brief Reads the bit group 'SAF' of register 'ETH_MFFR'. */
U8   GH_ETH_get_MFFR_SAF(void);
/*! \brief Writes the bit group 'HPF' of register 'ETH_MFFR'. */
void GH_ETH_set_MFFR_HPF(U8 data);
/*! \brief Reads the bit group 'HPF' of register 'ETH_MFFR'. */
U8   GH_ETH_get_MFFR_HPF(void);
/*! \brief Writes the bit group 'RA' of register 'ETH_MFFR'. */
void GH_ETH_set_MFFR_RA(U8 data);
/*! \brief Reads the bit group 'RA' of register 'ETH_MFFR'. */
U8   GH_ETH_get_MFFR_RA(void);

/*----------------------------------------------------------------------------*/
/* register ETH_MHTRH (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_MHTRH'. */
void GH_ETH_set_MHTRH(U32 data);
/*! \brief Reads the register 'ETH_MHTRH'. */
U32  GH_ETH_get_MHTRH(void);
/*! \brief Writes the bit group 'HTH' of register 'ETH_MHTRH'. */
void GH_ETH_set_MHTRH_HTH(U32 data);
/*! \brief Reads the bit group 'HTH' of register 'ETH_MHTRH'. */
U32  GH_ETH_get_MHTRH_HTH(void);

/*----------------------------------------------------------------------------*/
/* register ETH_MHTRL (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_MHTRL'. */
void GH_ETH_set_MHTRL(U32 data);
/*! \brief Reads the register 'ETH_MHTRL'. */
U32  GH_ETH_get_MHTRL(void);
/*! \brief Writes the bit group 'HTL' of register 'ETH_MHTRL'. */
void GH_ETH_set_MHTRL_HTL(U32 data);
/*! \brief Reads the bit group 'HTL' of register 'ETH_MHTRL'. */
U32  GH_ETH_get_MHTRL_HTL(void);

/*----------------------------------------------------------------------------*/
/* register ETH_GAR (read/write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_GAR'. */
void GH_ETH_set_GAR(U32 data);
/*! \brief Reads the register 'ETH_GAR'. */
U32  GH_ETH_get_GAR(void);
/*! \brief Writes the bit group 'GB' of register 'ETH_GAR'. */
void GH_ETH_set_GAR_GB(U8 data);
/*! \brief Reads the bit group 'GB' of register 'ETH_GAR'. */
U8   GH_ETH_get_GAR_GB(void);
/*! \brief Writes the bit group 'GW' of register 'ETH_GAR'. */
void GH_ETH_set_GAR_GW(U8 data);
/*! \brief Reads the bit group 'GW' of register 'ETH_GAR'. */
U8   GH_ETH_get_GAR_GW(void);
/*! \brief Writes the bit group 'CR' of register 'ETH_GAR'. */
void GH_ETH_set_GAR_CR(U8 data);
/*! \brief Reads the bit group 'CR' of register 'ETH_GAR'. */
U8   GH_ETH_get_GAR_CR(void);
/*! \brief Writes the bit group 'GR' of register 'ETH_GAR'. */
void GH_ETH_set_GAR_GR(U8 data);
/*! \brief Reads the bit group 'GR' of register 'ETH_GAR'. */
U8   GH_ETH_get_GAR_GR(void);
/*! \brief Writes the bit group 'PA' of register 'ETH_GAR'. */
void GH_ETH_set_GAR_PA(U8 data);
/*! \brief Reads the bit group 'PA' of register 'ETH_GAR'. */
U8   GH_ETH_get_GAR_PA(void);

/*----------------------------------------------------------------------------*/
/* register ETH_GDR (read/write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_GDR'. */
void GH_ETH_set_GDR(U32 data);
/*! \brief Reads the register 'ETH_GDR'. */
U32  GH_ETH_get_GDR(void);
/*! \brief Writes the bit group 'GD' of register 'ETH_GDR'. */
void GH_ETH_set_GDR_GD(U16 data);
/*! \brief Reads the bit group 'GD' of register 'ETH_GDR'. */
U16  GH_ETH_get_GDR_GD(void);

/*----------------------------------------------------------------------------*/
/* register ETH_FCR (read/write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_FCR'. */
void GH_ETH_set_FCR(U32 data);
/*! \brief Reads the register 'ETH_FCR'. */
U32  GH_ETH_get_FCR(void);
/*! \brief Writes the bit group 'FCB' of register 'ETH_FCR'. */
void GH_ETH_set_FCR_FCB(U8 data);
/*! \brief Reads the bit group 'FCB' of register 'ETH_FCR'. */
U8   GH_ETH_get_FCR_FCB(void);
/*! \brief Writes the bit group 'TFE' of register 'ETH_FCR'. */
void GH_ETH_set_FCR_TFE(U8 data);
/*! \brief Reads the bit group 'TFE' of register 'ETH_FCR'. */
U8   GH_ETH_get_FCR_TFE(void);
/*! \brief Writes the bit group 'RFE' of register 'ETH_FCR'. */
void GH_ETH_set_FCR_RFE(U8 data);
/*! \brief Reads the bit group 'RFE' of register 'ETH_FCR'. */
U8   GH_ETH_get_FCR_RFE(void);
/*! \brief Writes the bit group 'UP' of register 'ETH_FCR'. */
void GH_ETH_set_FCR_UP(U8 data);
/*! \brief Reads the bit group 'UP' of register 'ETH_FCR'. */
U8   GH_ETH_get_FCR_UP(void);
/*! \brief Writes the bit group 'PLT' of register 'ETH_FCR'. */
void GH_ETH_set_FCR_PLT(U8 data);
/*! \brief Reads the bit group 'PLT' of register 'ETH_FCR'. */
U8   GH_ETH_get_FCR_PLT(void);
/*! \brief Writes the bit group 'PT' of register 'ETH_FCR'. */
void GH_ETH_set_FCR_PT(U16 data);
/*! \brief Reads the bit group 'PT' of register 'ETH_FCR'. */
U16  GH_ETH_get_FCR_PT(void);

/*----------------------------------------------------------------------------*/
/* register ETH_VTR (read/write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_VTR'. */
void GH_ETH_set_VTR(U32 data);
/*! \brief Reads the register 'ETH_VTR'. */
U32  GH_ETH_get_VTR(void);
/*! \brief Writes the bit group 'VL' of register 'ETH_VTR'. */
void GH_ETH_set_VTR_VL(U16 data);
/*! \brief Reads the bit group 'VL' of register 'ETH_VTR'. */
U16  GH_ETH_get_VTR_VL(void);
/*! \brief Writes the bit group 'ETV' of register 'ETH_VTR'. */
void GH_ETH_set_VTR_ETV(U8 data);
/*! \brief Reads the bit group 'ETV' of register 'ETH_VTR'. */
U8   GH_ETH_get_VTR_ETV(void);

/*----------------------------------------------------------------------------*/
/* register ETH_VR (read)                                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'ETH_VR'. */
U32  GH_ETH_get_VR(void);

/*----------------------------------------------------------------------------*/
/* register ETH_MAR0H (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_MAR0H'. */
void GH_ETH_set_MAR0H(U32 data);
/*! \brief Reads the register 'ETH_MAR0H'. */
U32  GH_ETH_get_MAR0H(void);
/*! \brief Writes the bit group 'A0' of register 'ETH_MAR0H'. */
void GH_ETH_set_MAR0H_A0(U16 data);
/*! \brief Reads the bit group 'A0' of register 'ETH_MAR0H'. */
U16  GH_ETH_get_MAR0H_A0(void);
/*! \brief Writes the bit group 'M0' of register 'ETH_MAR0H'. */
void GH_ETH_set_MAR0H_M0(U8 data);
/*! \brief Reads the bit group 'M0' of register 'ETH_MAR0H'. */
U8   GH_ETH_get_MAR0H_M0(void);

/*----------------------------------------------------------------------------*/
/* register ETH_MAR0L (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_MAR0L'. */
void GH_ETH_set_MAR0L(U32 data);
/*! \brief Reads the register 'ETH_MAR0L'. */
U32  GH_ETH_get_MAR0L(void);
/*! \brief Writes the bit group 'A0' of register 'ETH_MAR0L'. */
void GH_ETH_set_MAR0L_A0(U32 data);
/*! \brief Reads the bit group 'A0' of register 'ETH_MAR0L'. */
U32  GH_ETH_get_MAR0L_A0(void);

/*----------------------------------------------------------------------------*/
/* register ETH_MAR1H (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_MAR1H'. */
void GH_ETH_set_MAR1H(U32 data);
/*! \brief Reads the register 'ETH_MAR1H'. */
U32  GH_ETH_get_MAR1H(void);
/*! \brief Writes the bit group 'A1' of register 'ETH_MAR1H'. */
void GH_ETH_set_MAR1H_A1(U16 data);
/*! \brief Reads the bit group 'A1' of register 'ETH_MAR1H'. */
U16  GH_ETH_get_MAR1H_A1(void);
/*! \brief Writes the bit group 'MBC' of register 'ETH_MAR1H'. */
void GH_ETH_set_MAR1H_MBC(U8 data);
/*! \brief Reads the bit group 'MBC' of register 'ETH_MAR1H'. */
U8   GH_ETH_get_MAR1H_MBC(void);
/*! \brief Writes the bit group 'SA' of register 'ETH_MAR1H'. */
void GH_ETH_set_MAR1H_SA(U8 data);
/*! \brief Reads the bit group 'SA' of register 'ETH_MAR1H'. */
U8   GH_ETH_get_MAR1H_SA(void);
/*! \brief Writes the bit group 'A1E' of register 'ETH_MAR1H'. */
void GH_ETH_set_MAR1H_A1E(U8 data);
/*! \brief Reads the bit group 'A1E' of register 'ETH_MAR1H'. */
U8   GH_ETH_get_MAR1H_A1E(void);

/*----------------------------------------------------------------------------*/
/* register ETH_MAR1L (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_MAR1L'. */
void GH_ETH_set_MAR1L(U32 data);
/*! \brief Reads the register 'ETH_MAR1L'. */
U32  GH_ETH_get_MAR1L(void);
/*! \brief Writes the bit group 'A1' of register 'ETH_MAR1L'. */
void GH_ETH_set_MAR1L_A1(U32 data);
/*! \brief Reads the bit group 'A1' of register 'ETH_MAR1L'. */
U32  GH_ETH_get_MAR1L_A1(void);

/*----------------------------------------------------------------------------*/
/* register ETH_MAR2H (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_MAR2H'. */
void GH_ETH_set_MAR2H(U32 data);
/*! \brief Reads the register 'ETH_MAR2H'. */
U32  GH_ETH_get_MAR2H(void);
/*! \brief Writes the bit group 'A2' of register 'ETH_MAR2H'. */
void GH_ETH_set_MAR2H_A2(U16 data);
/*! \brief Reads the bit group 'A2' of register 'ETH_MAR2H'. */
U16  GH_ETH_get_MAR2H_A2(void);
/*! \brief Writes the bit group 'MBC' of register 'ETH_MAR2H'. */
void GH_ETH_set_MAR2H_MBC(U8 data);
/*! \brief Reads the bit group 'MBC' of register 'ETH_MAR2H'. */
U8   GH_ETH_get_MAR2H_MBC(void);
/*! \brief Writes the bit group 'SA' of register 'ETH_MAR2H'. */
void GH_ETH_set_MAR2H_SA(U8 data);
/*! \brief Reads the bit group 'SA' of register 'ETH_MAR2H'. */
U8   GH_ETH_get_MAR2H_SA(void);
/*! \brief Writes the bit group 'A2E' of register 'ETH_MAR2H'. */
void GH_ETH_set_MAR2H_A2E(U8 data);
/*! \brief Reads the bit group 'A2E' of register 'ETH_MAR2H'. */
U8   GH_ETH_get_MAR2H_A2E(void);

/*----------------------------------------------------------------------------*/
/* register ETH_MAR2L (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_MAR2L'. */
void GH_ETH_set_MAR2L(U32 data);
/*! \brief Reads the register 'ETH_MAR2L'. */
U32  GH_ETH_get_MAR2L(void);
/*! \brief Writes the bit group 'A2' of register 'ETH_MAR2L'. */
void GH_ETH_set_MAR2L_A2(U32 data);
/*! \brief Reads the bit group 'A2' of register 'ETH_MAR2L'. */
U32  GH_ETH_get_MAR2L_A2(void);

/*----------------------------------------------------------------------------*/
/* register ETH_EPHY_DEBUG (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_EPHY_DEBUG'. */
void GH_ETH_set_EPHY_DEBUG(U32 data);
/*! \brief Reads the register 'ETH_EPHY_DEBUG'. */
U32  GH_ETH_get_EPHY_DEBUG(void);
/*! \brief Writes the bit group 'debug' of register 'ETH_EPHY_DEBUG'. */
void GH_ETH_set_EPHY_DEBUG_debug(U32 data);
/*! \brief Reads the bit group 'debug' of register 'ETH_EPHY_DEBUG'. */
U32  GH_ETH_get_EPHY_DEBUG_debug(void);

/*----------------------------------------------------------------------------*/
/* register ETH_BMR (read/write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_BMR'. */
void GH_ETH_set_BMR(U32 data);
/*! \brief Reads the register 'ETH_BMR'. */
U32  GH_ETH_get_BMR(void);
/*! \brief Writes the bit group 'SWR' of register 'ETH_BMR'. */
void GH_ETH_set_BMR_SWR(U8 data);
/*! \brief Reads the bit group 'SWR' of register 'ETH_BMR'. */
U8   GH_ETH_get_BMR_SWR(void);
/*! \brief Writes the bit group 'DA' of register 'ETH_BMR'. */
void GH_ETH_set_BMR_DA(U8 data);
/*! \brief Reads the bit group 'DA' of register 'ETH_BMR'. */
U8   GH_ETH_get_BMR_DA(void);
/*! \brief Writes the bit group 'DSL' of register 'ETH_BMR'. */
void GH_ETH_set_BMR_DSL(U8 data);
/*! \brief Reads the bit group 'DSL' of register 'ETH_BMR'. */
U8   GH_ETH_get_BMR_DSL(void);
/*! \brief Writes the bit group 'PBL' of register 'ETH_BMR'. */
void GH_ETH_set_BMR_PBL(U8 data);
/*! \brief Reads the bit group 'PBL' of register 'ETH_BMR'. */
U8   GH_ETH_get_BMR_PBL(void);
/*! \brief Writes the bit group 'PR' of register 'ETH_BMR'. */
void GH_ETH_set_BMR_PR(U8 data);
/*! \brief Reads the bit group 'PR' of register 'ETH_BMR'. */
U8   GH_ETH_get_BMR_PR(void);
/*! \brief Writes the bit group 'FB' of register 'ETH_BMR'. */
void GH_ETH_set_BMR_FB(U8 data);
/*! \brief Reads the bit group 'FB' of register 'ETH_BMR'. */
U8   GH_ETH_get_BMR_FB(void);
/*! \brief Writes the bit group 'RPBL' of register 'ETH_BMR'. */
void GH_ETH_set_BMR_RPBL(U8 data);
/*! \brief Reads the bit group 'RPBL' of register 'ETH_BMR'. */
U8   GH_ETH_get_BMR_RPBL(void);
/*! \brief Writes the bit group 'USP' of register 'ETH_BMR'. */
void GH_ETH_set_BMR_USP(U8 data);
/*! \brief Reads the bit group 'USP' of register 'ETH_BMR'. */
U8   GH_ETH_get_BMR_USP(void);
/*! \brief Writes the bit group 'PBL4X' of register 'ETH_BMR'. */
void GH_ETH_set_BMR_PBL4X(U8 data);
/*! \brief Reads the bit group 'PBL4X' of register 'ETH_BMR'. */
U8   GH_ETH_get_BMR_PBL4X(void);
/*! \brief Writes the bit group 'AAL' of register 'ETH_BMR'. */
void GH_ETH_set_BMR_AAL(U8 data);
/*! \brief Reads the bit group 'AAL' of register 'ETH_BMR'. */
U8   GH_ETH_get_BMR_AAL(void);

/*----------------------------------------------------------------------------*/
/* register ETH_TPDR (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_TPDR'. */
void GH_ETH_set_TPDR(U32 data);
/*! \brief Reads the register 'ETH_TPDR'. */
U32  GH_ETH_get_TPDR(void);

/*----------------------------------------------------------------------------*/
/* register ETH_RPDR (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_RPDR'. */
void GH_ETH_set_RPDR(U32 data);
/*! \brief Reads the register 'ETH_RPDR'. */
U32  GH_ETH_get_RPDR(void);

/*----------------------------------------------------------------------------*/
/* register ETH_RDLAR (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_RDLAR'. */
void GH_ETH_set_RDLAR(U32 data);
/*! \brief Reads the register 'ETH_RDLAR'. */
U32  GH_ETH_get_RDLAR(void);

/*----------------------------------------------------------------------------*/
/* register ETH_TDLAR (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_TDLAR'. */
void GH_ETH_set_TDLAR(U32 data);
/*! \brief Reads the register 'ETH_TDLAR'. */
U32  GH_ETH_get_TDLAR(void);

/*----------------------------------------------------------------------------*/
/* register ETH_SR (read/write)                                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_SR'. */
void GH_ETH_set_SR(U32 data);
/*! \brief Reads the register 'ETH_SR'. */
U32  GH_ETH_get_SR(void);
/*! \brief Writes the bit group 'TI' of register 'ETH_SR'. */
void GH_ETH_set_SR_TI(U8 data);
/*! \brief Reads the bit group 'TI' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_TI(void);
/*! \brief Writes the bit group 'TPS' of register 'ETH_SR'. */
void GH_ETH_set_SR_TPS(U8 data);
/*! \brief Reads the bit group 'TPS' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_TPS(void);
/*! \brief Writes the bit group 'TU' of register 'ETH_SR'. */
void GH_ETH_set_SR_TU(U8 data);
/*! \brief Reads the bit group 'TU' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_TU(void);
/*! \brief Writes the bit group 'TJT' of register 'ETH_SR'. */
void GH_ETH_set_SR_TJT(U8 data);
/*! \brief Reads the bit group 'TJT' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_TJT(void);
/*! \brief Writes the bit group 'OVF' of register 'ETH_SR'. */
void GH_ETH_set_SR_OVF(U8 data);
/*! \brief Reads the bit group 'OVF' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_OVF(void);
/*! \brief Writes the bit group 'UNF' of register 'ETH_SR'. */
void GH_ETH_set_SR_UNF(U8 data);
/*! \brief Reads the bit group 'UNF' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_UNF(void);
/*! \brief Writes the bit group 'RI' of register 'ETH_SR'. */
void GH_ETH_set_SR_RI(U8 data);
/*! \brief Reads the bit group 'RI' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_RI(void);
/*! \brief Writes the bit group 'RU' of register 'ETH_SR'. */
void GH_ETH_set_SR_RU(U8 data);
/*! \brief Reads the bit group 'RU' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_RU(void);
/*! \brief Writes the bit group 'RPS' of register 'ETH_SR'. */
void GH_ETH_set_SR_RPS(U8 data);
/*! \brief Reads the bit group 'RPS' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_RPS(void);
/*! \brief Writes the bit group 'RWT' of register 'ETH_SR'. */
void GH_ETH_set_SR_RWT(U8 data);
/*! \brief Reads the bit group 'RWT' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_RWT(void);
/*! \brief Writes the bit group 'ETI' of register 'ETH_SR'. */
void GH_ETH_set_SR_ETI(U8 data);
/*! \brief Reads the bit group 'ETI' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_ETI(void);
/*! \brief Writes the bit group 'FBE' of register 'ETH_SR'. */
void GH_ETH_set_SR_FBE(U8 data);
/*! \brief Reads the bit group 'FBE' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_FBE(void);
/*! \brief Writes the bit group 'ERI' of register 'ETH_SR'. */
void GH_ETH_set_SR_ERI(U8 data);
/*! \brief Reads the bit group 'ERI' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_ERI(void);
/*! \brief Writes the bit group 'AIS' of register 'ETH_SR'. */
void GH_ETH_set_SR_AIS(U8 data);
/*! \brief Reads the bit group 'AIS' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_AIS(void);
/*! \brief Writes the bit group 'NIS' of register 'ETH_SR'. */
void GH_ETH_set_SR_NIS(U8 data);
/*! \brief Reads the bit group 'NIS' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_NIS(void);
/*! \brief Writes the bit group 'RS' of register 'ETH_SR'. */
void GH_ETH_set_SR_RS(U8 data);
/*! \brief Reads the bit group 'RS' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_RS(void);
/*! \brief Writes the bit group 'TS' of register 'ETH_SR'. */
void GH_ETH_set_SR_TS(U8 data);
/*! \brief Reads the bit group 'TS' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_TS(void);
/*! \brief Writes the bit group 'EB' of register 'ETH_SR'. */
void GH_ETH_set_SR_EB(U8 data);
/*! \brief Reads the bit group 'EB' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_EB(void);
/*! \brief Writes the bit group 'GLI' of register 'ETH_SR'. */
void GH_ETH_set_SR_GLI(U8 data);
/*! \brief Reads the bit group 'GLI' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_GLI(void);
/*! \brief Writes the bit group 'GMI' of register 'ETH_SR'. */
void GH_ETH_set_SR_GMI(U8 data);
/*! \brief Reads the bit group 'GMI' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_GMI(void);
/*! \brief Writes the bit group 'GPI' of register 'ETH_SR'. */
void GH_ETH_set_SR_GPI(U8 data);
/*! \brief Reads the bit group 'GPI' of register 'ETH_SR'. */
U8   GH_ETH_get_SR_GPI(void);

/*----------------------------------------------------------------------------*/
/* register ETH_OMR (read/write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_OMR'. */
void GH_ETH_set_OMR(U32 data);
/*! \brief Reads the register 'ETH_OMR'. */
U32  GH_ETH_get_OMR(void);
/*! \brief Writes the bit group 'SR' of register 'ETH_OMR'. */
void GH_ETH_set_OMR_SR(U8 data);
/*! \brief Reads the bit group 'SR' of register 'ETH_OMR'. */
U8   GH_ETH_get_OMR_SR(void);
/*! \brief Writes the bit group 'OSF' of register 'ETH_OMR'. */
void GH_ETH_set_OMR_OSF(U8 data);
/*! \brief Reads the bit group 'OSF' of register 'ETH_OMR'. */
U8   GH_ETH_get_OMR_OSF(void);
/*! \brief Writes the bit group 'RTC' of register 'ETH_OMR'. */
void GH_ETH_set_OMR_RTC(U8 data);
/*! \brief Reads the bit group 'RTC' of register 'ETH_OMR'. */
U8   GH_ETH_get_OMR_RTC(void);
/*! \brief Writes the bit group 'FUF' of register 'ETH_OMR'. */
void GH_ETH_set_OMR_FUF(U8 data);
/*! \brief Reads the bit group 'FUF' of register 'ETH_OMR'. */
U8   GH_ETH_get_OMR_FUF(void);
/*! \brief Writes the bit group 'FEF' of register 'ETH_OMR'. */
void GH_ETH_set_OMR_FEF(U8 data);
/*! \brief Reads the bit group 'FEF' of register 'ETH_OMR'. */
U8   GH_ETH_get_OMR_FEF(void);
/*! \brief Writes the bit group 'EFC' of register 'ETH_OMR'. */
void GH_ETH_set_OMR_EFC(U8 data);
/*! \brief Reads the bit group 'EFC' of register 'ETH_OMR'. */
U8   GH_ETH_get_OMR_EFC(void);
/*! \brief Writes the bit group 'RFA' of register 'ETH_OMR'. */
void GH_ETH_set_OMR_RFA(U8 data);
/*! \brief Reads the bit group 'RFA' of register 'ETH_OMR'. */
U8   GH_ETH_get_OMR_RFA(void);
/*! \brief Writes the bit group 'RFD' of register 'ETH_OMR'. */
void GH_ETH_set_OMR_RFD(U8 data);
/*! \brief Reads the bit group 'RFD' of register 'ETH_OMR'. */
U8   GH_ETH_get_OMR_RFD(void);
/*! \brief Writes the bit group 'ST' of register 'ETH_OMR'. */
void GH_ETH_set_OMR_ST(U8 data);
/*! \brief Reads the bit group 'ST' of register 'ETH_OMR'. */
U8   GH_ETH_get_OMR_ST(void);
/*! \brief Writes the bit group 'TTC' of register 'ETH_OMR'. */
void GH_ETH_set_OMR_TTC(U8 data);
/*! \brief Reads the bit group 'TTC' of register 'ETH_OMR'. */
U8   GH_ETH_get_OMR_TTC(void);
/*! \brief Writes the bit group 'FTF' of register 'ETH_OMR'. */
void GH_ETH_set_OMR_FTF(U8 data);
/*! \brief Reads the bit group 'FTF' of register 'ETH_OMR'. */
U8   GH_ETH_get_OMR_FTF(void);
/*! \brief Writes the bit group 'SF' of register 'ETH_OMR'. */
void GH_ETH_set_OMR_SF(U8 data);
/*! \brief Reads the bit group 'SF' of register 'ETH_OMR'. */
U8   GH_ETH_get_OMR_SF(void);

/*----------------------------------------------------------------------------*/
/* register ETH_IER (read/write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_IER'. */
void GH_ETH_set_IER(U32 data);
/*! \brief Reads the register 'ETH_IER'. */
U32  GH_ETH_get_IER(void);
/*! \brief Writes the bit group 'TI' of register 'ETH_IER'. */
void GH_ETH_set_IER_TI(U8 data);
/*! \brief Reads the bit group 'TI' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_TI(void);
/*! \brief Writes the bit group 'TS' of register 'ETH_IER'. */
void GH_ETH_set_IER_TS(U8 data);
/*! \brief Reads the bit group 'TS' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_TS(void);
/*! \brief Writes the bit group 'TU' of register 'ETH_IER'. */
void GH_ETH_set_IER_TU(U8 data);
/*! \brief Reads the bit group 'TU' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_TU(void);
/*! \brief Writes the bit group 'TJ' of register 'ETH_IER'. */
void GH_ETH_set_IER_TJ(U8 data);
/*! \brief Reads the bit group 'TJ' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_TJ(void);
/*! \brief Writes the bit group 'OV' of register 'ETH_IER'. */
void GH_ETH_set_IER_OV(U8 data);
/*! \brief Reads the bit group 'OV' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_OV(void);
/*! \brief Writes the bit group 'UN' of register 'ETH_IER'. */
void GH_ETH_set_IER_UN(U8 data);
/*! \brief Reads the bit group 'UN' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_UN(void);
/*! \brief Writes the bit group 'RI' of register 'ETH_IER'. */
void GH_ETH_set_IER_RI(U8 data);
/*! \brief Reads the bit group 'RI' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_RI(void);
/*! \brief Writes the bit group 'RU' of register 'ETH_IER'. */
void GH_ETH_set_IER_RU(U8 data);
/*! \brief Reads the bit group 'RU' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_RU(void);
/*! \brief Writes the bit group 'RS' of register 'ETH_IER'. */
void GH_ETH_set_IER_RS(U8 data);
/*! \brief Reads the bit group 'RS' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_RS(void);
/*! \brief Writes the bit group 'RW' of register 'ETH_IER'. */
void GH_ETH_set_IER_RW(U8 data);
/*! \brief Reads the bit group 'RW' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_RW(void);
/*! \brief Writes the bit group 'ETE' of register 'ETH_IER'. */
void GH_ETH_set_IER_ETE(U8 data);
/*! \brief Reads the bit group 'ETE' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_ETE(void);
/*! \brief Writes the bit group 'FBE' of register 'ETH_IER'. */
void GH_ETH_set_IER_FBE(U8 data);
/*! \brief Reads the bit group 'FBE' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_FBE(void);
/*! \brief Writes the bit group 'ERE' of register 'ETH_IER'. */
void GH_ETH_set_IER_ERE(U8 data);
/*! \brief Reads the bit group 'ERE' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_ERE(void);
/*! \brief Writes the bit group 'AI' of register 'ETH_IER'. */
void GH_ETH_set_IER_AI(U8 data);
/*! \brief Reads the bit group 'AI' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_AI(void);
/*! \brief Writes the bit group 'NI' of register 'ETH_IER'. */
void GH_ETH_set_IER_NI(U8 data);
/*! \brief Reads the bit group 'NI' of register 'ETH_IER'. */
U8   GH_ETH_get_IER_NI(void);

/*----------------------------------------------------------------------------*/
/* register ETH_MFBOCR (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_MFBOCR'. */
void GH_ETH_set_MFBOCR(U32 data);
/*! \brief Reads the register 'ETH_MFBOCR'. */
U32  GH_ETH_get_MFBOCR(void);
/*! \brief Writes the bit group 'NMFH' of register 'ETH_MFBOCR'. */
void GH_ETH_set_MFBOCR_NMFH(U16 data);
/*! \brief Reads the bit group 'NMFH' of register 'ETH_MFBOCR'. */
U16  GH_ETH_get_MFBOCR_NMFH(void);
/*! \brief Writes the bit group 'OVMFC' of register 'ETH_MFBOCR'. */
void GH_ETH_set_MFBOCR_OVMFC(U8 data);
/*! \brief Reads the bit group 'OVMFC' of register 'ETH_MFBOCR'. */
U8   GH_ETH_get_MFBOCR_OVMFC(void);
/*! \brief Writes the bit group 'NMFF' of register 'ETH_MFBOCR'. */
void GH_ETH_set_MFBOCR_NMFF(U16 data);
/*! \brief Reads the bit group 'NMFF' of register 'ETH_MFBOCR'. */
U16  GH_ETH_get_MFBOCR_NMFF(void);
/*! \brief Writes the bit group 'ONMFF' of register 'ETH_MFBOCR'. */
void GH_ETH_set_MFBOCR_ONMFF(U8 data);
/*! \brief Reads the bit group 'ONMFF' of register 'ETH_MFBOCR'. */
U8   GH_ETH_get_MFBOCR_ONMFF(void);

/*----------------------------------------------------------------------------*/
/* register ETH_CHTDR (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_CHTDR'. */
void GH_ETH_set_CHTDR(U32 data);
/*! \brief Reads the register 'ETH_CHTDR'. */
U32  GH_ETH_get_CHTDR(void);

/*----------------------------------------------------------------------------*/
/* register ETH_CHRDR (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_CHRDR'. */
void GH_ETH_set_CHRDR(U32 data);
/*! \brief Reads the register 'ETH_CHRDR'. */
U32  GH_ETH_get_CHRDR(void);

/*----------------------------------------------------------------------------*/
/* register ETH_CHTBAR (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_CHTBAR'. */
void GH_ETH_set_CHTBAR(U32 data);
/*! \brief Reads the register 'ETH_CHTBAR'. */
U32  GH_ETH_get_CHTBAR(void);

/*----------------------------------------------------------------------------*/
/* register ETH_CHRBAR (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'ETH_CHRBAR'. */
void GH_ETH_set_CHRBAR(U32 data);
/*! \brief Reads the register 'ETH_CHRBAR'. */
U32  GH_ETH_get_CHRBAR(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_ETH_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_eth.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_ETH_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

