/******************************************************************************
**
** \file      gh_spi2.c
**
** \brief     Slave interface; Slave3, TSSI.
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
#include "gh_spi2.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_SPI2_CTRLR0_REAL                                FIO_ADDRESS(SPI2,0x70001000) /* read/write */
#define REG_SPI2_CTRLR1_REAL                                FIO_ADDRESS(SPI2,0x70001004) /* read/write */
#define REG_SPI2_SSIENR_REAL                                FIO_ADDRESS(SPI2,0x70001008) /* read/write */
#define REG_SPI2_SER_REAL                                   FIO_ADDRESS(SPI2,0x70001010) /* read/write */
#define REG_SPI2_BAUDR_REAL                                 FIO_ADDRESS(SPI2,0x70001014) /* read/write */
#define REG_SPI2_TXFTLR_REAL                                FIO_ADDRESS(SPI2,0x70001018) /* read/write */
#define REG_SPI2_RXFTLR_REAL                                FIO_ADDRESS(SPI2,0x7000101C) /* read/write */
#define REG_SPI2_TXFLR_REAL                                 FIO_ADDRESS(SPI2,0x70001020) /* read/write */
#define REG_SPI2_RXFLR_REAL                                 FIO_ADDRESS(SPI2,0x70001024) /* read/write */
#define REG_SPI2_SR_REAL                                    FIO_ADDRESS(SPI2,0x70001028) /* read */
#define REG_SPI2_IMR_REAL                                   FIO_ADDRESS(SPI2,0x7000102C) /* read/write */
#define REG_SPI2_ISR_REAL                                   FIO_ADDRESS(SPI2,0x70001030) /* read */
#define REG_SPI2_RISR_REAL                                  FIO_ADDRESS(SPI2,0x70001034) /* read */
#define REG_SPI2_TXOICR_REAL                                FIO_ADDRESS(SPI2,0x70001038) /* read */
#define REG_SPI2_RXOICR_REAL                                FIO_ADDRESS(SPI2,0x7000103C) /* read */
#define REG_SPI2_RXUICR_REAL                                FIO_ADDRESS(SPI2,0x70001040) /* read */
#define REG_SPI2_MSTICR_REAL                                FIO_ADDRESS(SPI2,0x70001044) /* read */
#define REG_SPI2_ICR_REAL                                   FIO_ADDRESS(SPI2,0x70001048) /* read */
#define REG_SPI2_IDR_REAL                                   FIO_ADDRESS(SPI2,0x70001058) /* read */
#define REG_SPI2_DR_REAL                                    FIO_ADDRESS(SPI2,0x70001060) /* read */
#define REG_SPI2_DW_REAL                                    FIO_ADDRESS(SPI2,0x70001060) /* write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* SPI2_CTRLR0 */
    U32 all;
    struct {
        U32 dfs                         : 4;
        U32 frf                         : 2;
        U32 scph                        : 1;
        U32 scpol                       : 1;
        U32 tmod                        : 2;
        U32 slv_oe                      : 1;
        U32 srl                         : 1;
        U32 cfs                         : 4;
        U32                             : 16;
    } bitc;
} GH_SPI2_CTRLR0_REAL_S;

typedef union { /* SPI2_CTRLR1 */
    U32 all;
    struct {
        U32 ndf                         : 16;
        U32                             : 16;
    } bitc;
} GH_SPI2_CTRLR1_REAL_S;

typedef union { /* SPI2_SSIENR */
    U32 all;
    struct {
        U32 ssi_enb                     : 1;
        U32                             : 31;
    } bitc;
} GH_SPI2_SSIENR_REAL_S;

typedef union { /* SPI2_SER */
    U32 all;
    struct {
        U32 ser_l                       : 2;
        U32                             : 2;
        U32 ser_h                       : 4;
        U32                             : 24;
    } bitc;
} GH_SPI2_SER_REAL_S;

typedef union { /* SPI2_BAUDR */
    U32 all;
    struct {
        U32 sckdv                       : 16;
        U32                             : 16;
    } bitc;
} GH_SPI2_BAUDR_REAL_S;

typedef union { /* SPI2_TXFTLR */
    U32 all;
    struct {
        U32 tft                         : 4;
        U32                             : 28;
    } bitc;
} GH_SPI2_TXFTLR_REAL_S;

typedef union { /* SPI2_RXFTLR */
    U32 all;
    struct {
        U32 rft                         : 4;
        U32                             : 28;
    } bitc;
} GH_SPI2_RXFTLR_REAL_S;

typedef union { /* SPI2_TXFLR */
    U32 all;
    struct {
        U32 txtfl                       : 5;
        U32                             : 27;
    } bitc;
} GH_SPI2_TXFLR_REAL_S;

typedef union { /* SPI2_RXFLR */
    U32 all;
    struct {
        U32 rxtfl                       : 5;
        U32                             : 27;
    } bitc;
} GH_SPI2_RXFLR_REAL_S;

typedef union { /* SPI2_SR */
    U32 all;
    struct {
        U32 busy                        : 1;
        U32 tfnf                        : 1;
        U32 tfe                         : 1;
        U32 rfne                        : 1;
        U32 rff                         : 1;
        U32 txe                         : 1;
        U32 dcol                        : 1;
        U32                             : 25;
    } bitc;
} GH_SPI2_SR_REAL_S;

typedef union { /* SPI2_IMR */
    U32 all;
    struct {
        U32 txeim                       : 1;
        U32 txoim                       : 1;
        U32 rxuim                       : 1;
        U32 rxoim                       : 1;
        U32 rxfim                       : 1;
        U32 mstim                       : 1;
        U32                             : 26;
    } bitc;
} GH_SPI2_IMR_REAL_S;

typedef union { /* SPI2_ISR */
    U32 all;
    struct {
        U32 txeis                       : 1;
        U32 txois                       : 1;
        U32 rxuis                       : 1;
        U32 rxois                       : 1;
        U32 rxfis                       : 1;
        U32 mstis                       : 1;
        U32                             : 26;
    } bitc;
} GH_SPI2_ISR_REAL_S;

typedef union { /* SPI2_RISR */
    U32 all;
    struct {
        U32 txeir                       : 1;
        U32 txoir                       : 1;
        U32 rxuir                       : 1;
        U32 rxoir                       : 1;
        U32 rxfir                       : 1;
        U32 mstir                       : 1;
        U32                             : 26;
    } bitc;
} GH_SPI2_RISR_REAL_S;

typedef union { /* SPI2_TXOICR */
    U32 all;
    struct {
        U32 txoicr                      : 1;
        U32                             : 31;
    } bitc;
} GH_SPI2_TXOICR_REAL_S;

typedef union { /* SPI2_RXOICR */
    U32 all;
    struct {
        U32 rxoicr                      : 1;
        U32                             : 31;
    } bitc;
} GH_SPI2_RXOICR_REAL_S;

typedef union { /* SPI2_RXUICR */
    U32 all;
    struct {
        U32 rxuicr                      : 1;
        U32                             : 31;
    } bitc;
} GH_SPI2_RXUICR_REAL_S;

typedef union { /* SPI2_MSTICR */
    U32 all;
    struct {
        U32 msticr                      : 1;
        U32                             : 31;
    } bitc;
} GH_SPI2_MSTICR_REAL_S;

typedef union { /* SPI2_ICR */
    U32 all;
    struct {
        U32 icr                         : 1;
        U32                             : 31;
    } bitc;
} GH_SPI2_ICR_REAL_S;

typedef union { /* SPI2_IDR */
    U32 all;
    struct {
        U32 id                          : 1;
        U32                             : 31;
    } bitc;
} GH_SPI2_IDR_REAL_S;

typedef union { /* SPI2_DR */
    U32 all;
    struct {
        U32 dr                          : 16;
        U32                             : 16;
    } bitc;
} GH_SPI2_DR_REAL_S;

typedef union { /* SPI2_DW */
    U32 all;
    struct {
        U32 dw                          : 16;
        U32                             : 16;
    } bitc;
} GH_SPI2_DW_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_SPI2_DW_S                            m_spi2_dw;

/*----------------------------------------------------------------------------*/
/* register SPI2_CTRLR0 (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SPI2_set_CTRLR0(U32 data)
{
    GH_SPI2_CTRLR0_REAL_S real;
    GH_SPI2_CTRLR0_S dummy;
    dummy.all = data ;
    real.bitc.dfs = dummy.bitc.dfs;
    real.bitc.frf = dummy.bitc.frf;
    real.bitc.scph = dummy.bitc.scph;
    real.bitc.scpol = dummy.bitc.scpol;
    real.bitc.tmod = dummy.bitc.tmod;
    real.bitc.slv_oe = dummy.bitc.slv_oe;
    real.bitc.srl = dummy.bitc.srl;
    real.bitc.cfs = dummy.bitc.cfs;
    *(volatile U32 *)REG_SPI2_CTRLR0_REAL = real.all;
}
GH_INLINE U32  GH_SPI2_get_CTRLR0(void)
{
    GH_SPI2_CTRLR0_REAL_S real;
    GH_SPI2_CTRLR0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_CTRLR0_REAL);

    dummy.bitc.dfs = real.bitc.dfs;
    dummy.bitc.frf = real.bitc.frf;
    dummy.bitc.scph = real.bitc.scph;
    dummy.bitc.scpol = real.bitc.scpol;
    dummy.bitc.tmod = real.bitc.tmod;
    dummy.bitc.slv_oe = real.bitc.slv_oe;
    dummy.bitc.srl = real.bitc.srl;
    dummy.bitc.cfs = real.bitc.cfs;
    return dummy.all;
}
GH_INLINE void GH_SPI2_set_CTRLR0_DFS(U8 data)
{
    GH_SPI2_CTRLR0_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_CTRLR0_REAL;
    d.bitc.dfs = data;
    *(volatile U32 *)REG_SPI2_CTRLR0_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_CTRLR0_DFS(void)
{
    GH_SPI2_CTRLR0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_CTRLR0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dfs;
}
GH_INLINE void GH_SPI2_set_CTRLR0_FRF(U8 data)
{
    GH_SPI2_CTRLR0_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_CTRLR0_REAL;
    d.bitc.frf = data;
    *(volatile U32 *)REG_SPI2_CTRLR0_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_CTRLR0_FRF(void)
{
    GH_SPI2_CTRLR0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_CTRLR0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.frf;
}
GH_INLINE void GH_SPI2_set_CTRLR0_SCPH(U8 data)
{
    GH_SPI2_CTRLR0_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_CTRLR0_REAL;
    d.bitc.scph = data;
    *(volatile U32 *)REG_SPI2_CTRLR0_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_CTRLR0_SCPH(void)
{
    GH_SPI2_CTRLR0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_CTRLR0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.scph;
}
GH_INLINE void GH_SPI2_set_CTRLR0_SCPOL(U8 data)
{
    GH_SPI2_CTRLR0_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_CTRLR0_REAL;
    d.bitc.scpol = data;
    *(volatile U32 *)REG_SPI2_CTRLR0_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_CTRLR0_SCPOL(void)
{
    GH_SPI2_CTRLR0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_CTRLR0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.scpol;
}
GH_INLINE void GH_SPI2_set_CTRLR0_TMOD(U8 data)
{
    GH_SPI2_CTRLR0_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_CTRLR0_REAL;
    d.bitc.tmod = data;
    *(volatile U32 *)REG_SPI2_CTRLR0_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_CTRLR0_TMOD(void)
{
    GH_SPI2_CTRLR0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_CTRLR0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tmod;
}
GH_INLINE void GH_SPI2_set_CTRLR0_SLV_OE(U8 data)
{
    GH_SPI2_CTRLR0_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_CTRLR0_REAL;
    d.bitc.slv_oe = data;
    *(volatile U32 *)REG_SPI2_CTRLR0_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_CTRLR0_SLV_OE(void)
{
    GH_SPI2_CTRLR0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_CTRLR0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.slv_oe;
}
GH_INLINE void GH_SPI2_set_CTRLR0_SRL(U8 data)
{
    GH_SPI2_CTRLR0_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_CTRLR0_REAL;
    d.bitc.srl = data;
    *(volatile U32 *)REG_SPI2_CTRLR0_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_CTRLR0_SRL(void)
{
    GH_SPI2_CTRLR0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_CTRLR0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.srl;
}
GH_INLINE void GH_SPI2_set_CTRLR0_CFS(U8 data)
{
    GH_SPI2_CTRLR0_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_CTRLR0_REAL;
    d.bitc.cfs = data;
    *(volatile U32 *)REG_SPI2_CTRLR0_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_CTRLR0_CFS(void)
{
    GH_SPI2_CTRLR0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_CTRLR0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cfs;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_CTRLR1 (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SPI2_set_CTRLR1(U32 data)
{
    GH_SPI2_CTRLR1_REAL_S real;
    GH_SPI2_CTRLR1_S dummy;
    dummy.all = data ;
    real.bitc.ndf = dummy.bitc.ndf;
    *(volatile U32 *)REG_SPI2_CTRLR1_REAL = real.all;
}
GH_INLINE U32  GH_SPI2_get_CTRLR1(void)
{
    GH_SPI2_CTRLR1_REAL_S real;
    GH_SPI2_CTRLR1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_CTRLR1_REAL);

    dummy.bitc.ndf = real.bitc.ndf;
    return dummy.all;
}
GH_INLINE void GH_SPI2_set_CTRLR1_NDF(U16 data)
{
    GH_SPI2_CTRLR1_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_CTRLR1_REAL;
    d.bitc.ndf = data;
    *(volatile U32 *)REG_SPI2_CTRLR1_REAL = d.all;
}
GH_INLINE U16  GH_SPI2_get_CTRLR1_NDF(void)
{
    GH_SPI2_CTRLR1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_CTRLR1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ndf;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_SSIENR (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SPI2_set_SSIENR(U32 data)
{
    GH_SPI2_SSIENR_REAL_S real;
    GH_SPI2_SSIENR_S dummy;
    dummy.all = data ;
    real.bitc.ssi_enb = dummy.bitc.ssi_enb;
    *(volatile U32 *)REG_SPI2_SSIENR_REAL = real.all;
}
GH_INLINE U32  GH_SPI2_get_SSIENR(void)
{
    GH_SPI2_SSIENR_REAL_S real;
    GH_SPI2_SSIENR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_SSIENR_REAL);

    dummy.bitc.ssi_enb = real.bitc.ssi_enb;
    return dummy.all;
}
GH_INLINE void GH_SPI2_set_SSIENR_ssi_enb(U8 data)
{
    GH_SPI2_SSIENR_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_SSIENR_REAL;
    d.bitc.ssi_enb = data;
    *(volatile U32 *)REG_SPI2_SSIENR_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_SSIENR_ssi_enb(void)
{
    GH_SPI2_SSIENR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_SSIENR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ssi_enb;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_SER (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SPI2_set_SER(U32 data)
{
    GH_SPI2_SER_REAL_S real;
    GH_SPI2_SER_S dummy;
    dummy.all = data ;
    real.bitc.ser_l = dummy.bitc.ser_l;
    real.bitc.ser_h = dummy.bitc.ser_h;
    *(volatile U32 *)REG_SPI2_SER_REAL = real.all;
}
GH_INLINE U32  GH_SPI2_get_SER(void)
{
    GH_SPI2_SER_REAL_S real;
    GH_SPI2_SER_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_SER_REAL);

    dummy.bitc.ser_l = real.bitc.ser_l;
    dummy.bitc.ser_h = real.bitc.ser_h;
    return dummy.all;
}
GH_INLINE void GH_SPI2_set_SER_SER_L(U8 data)
{
    GH_SPI2_SER_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_SER_REAL;
    d.bitc.ser_l = data;
    *(volatile U32 *)REG_SPI2_SER_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_SER_SER_L(void)
{
    GH_SPI2_SER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_SER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ser_l;
}
GH_INLINE void GH_SPI2_set_SER_SER_H(U8 data)
{
    GH_SPI2_SER_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_SER_REAL;
    d.bitc.ser_h = data;
    *(volatile U32 *)REG_SPI2_SER_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_SER_SER_H(void)
{
    GH_SPI2_SER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_SER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ser_h;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_BAUDR (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SPI2_set_BAUDR(U32 data)
{
    GH_SPI2_BAUDR_REAL_S real;
    GH_SPI2_BAUDR_S dummy;
    dummy.all = data ;
    real.bitc.sckdv = dummy.bitc.sckdv;
    *(volatile U32 *)REG_SPI2_BAUDR_REAL = real.all;
}
GH_INLINE U32  GH_SPI2_get_BAUDR(void)
{
    GH_SPI2_BAUDR_REAL_S real;
    GH_SPI2_BAUDR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_BAUDR_REAL);

    dummy.bitc.sckdv = real.bitc.sckdv;
    return dummy.all;
}
GH_INLINE void GH_SPI2_set_BAUDR_SCKDV(U16 data)
{
    GH_SPI2_BAUDR_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_BAUDR_REAL;
    d.bitc.sckdv = data;
    *(volatile U32 *)REG_SPI2_BAUDR_REAL = d.all;
}
GH_INLINE U16  GH_SPI2_get_BAUDR_SCKDV(void)
{
    GH_SPI2_BAUDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_BAUDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sckdv;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_TXFTLR (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SPI2_set_TXFTLR(U32 data)
{
    GH_SPI2_TXFTLR_REAL_S real;
    GH_SPI2_TXFTLR_S dummy;
    dummy.all = data ;
    real.bitc.tft = dummy.bitc.tft;
    *(volatile U32 *)REG_SPI2_TXFTLR_REAL = real.all;
}
GH_INLINE U32  GH_SPI2_get_TXFTLR(void)
{
    GH_SPI2_TXFTLR_REAL_S real;
    GH_SPI2_TXFTLR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_TXFTLR_REAL);

    dummy.bitc.tft = real.bitc.tft;
    return dummy.all;
}
GH_INLINE void GH_SPI2_set_TXFTLR_TFT(U8 data)
{
    GH_SPI2_TXFTLR_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_TXFTLR_REAL;
    d.bitc.tft = data;
    *(volatile U32 *)REG_SPI2_TXFTLR_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_TXFTLR_TFT(void)
{
    GH_SPI2_TXFTLR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_TXFTLR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tft;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_RXFTLR (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SPI2_set_RXFTLR(U32 data)
{
    GH_SPI2_RXFTLR_REAL_S real;
    GH_SPI2_RXFTLR_S dummy;
    dummy.all = data ;
    real.bitc.rft = dummy.bitc.rft;
    *(volatile U32 *)REG_SPI2_RXFTLR_REAL = real.all;
}
GH_INLINE U32  GH_SPI2_get_RXFTLR(void)
{
    GH_SPI2_RXFTLR_REAL_S real;
    GH_SPI2_RXFTLR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_RXFTLR_REAL);

    dummy.bitc.rft = real.bitc.rft;
    return dummy.all;
}
GH_INLINE void GH_SPI2_set_RXFTLR_RFT(U8 data)
{
    GH_SPI2_RXFTLR_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_RXFTLR_REAL;
    d.bitc.rft = data;
    *(volatile U32 *)REG_SPI2_RXFTLR_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_RXFTLR_RFT(void)
{
    GH_SPI2_RXFTLR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_RXFTLR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rft;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_TXFLR (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SPI2_set_TXFLR(U32 data)
{
    GH_SPI2_TXFLR_REAL_S real;
    GH_SPI2_TXFLR_S dummy;
    dummy.all = data ;
    real.bitc.txtfl = dummy.bitc.txtfl;
    *(volatile U32 *)REG_SPI2_TXFLR_REAL = real.all;
}
GH_INLINE U32  GH_SPI2_get_TXFLR(void)
{
    GH_SPI2_TXFLR_REAL_S real;
    GH_SPI2_TXFLR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_TXFLR_REAL);

    dummy.bitc.txtfl = real.bitc.txtfl;
    return dummy.all;
}
GH_INLINE void GH_SPI2_set_TXFLR_TXTFL(U8 data)
{
    GH_SPI2_TXFLR_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_TXFLR_REAL;
    d.bitc.txtfl = data;
    *(volatile U32 *)REG_SPI2_TXFLR_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_TXFLR_TXTFL(void)
{
    GH_SPI2_TXFLR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_TXFLR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txtfl;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_RXFLR (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SPI2_set_RXFLR(U32 data)
{
    GH_SPI2_RXFLR_REAL_S real;
    GH_SPI2_RXFLR_S dummy;
    dummy.all = data ;
    real.bitc.rxtfl = dummy.bitc.rxtfl;
    *(volatile U32 *)REG_SPI2_RXFLR_REAL = real.all;
}
GH_INLINE U32  GH_SPI2_get_RXFLR(void)
{
    GH_SPI2_RXFLR_REAL_S real;
    GH_SPI2_RXFLR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_RXFLR_REAL);

    dummy.bitc.rxtfl = real.bitc.rxtfl;
    return dummy.all;
}
GH_INLINE void GH_SPI2_set_RXFLR_RXTFL(U8 data)
{
    GH_SPI2_RXFLR_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_RXFLR_REAL;
    d.bitc.rxtfl = data;
    *(volatile U32 *)REG_SPI2_RXFLR_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_RXFLR_RXTFL(void)
{
    GH_SPI2_RXFLR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_RXFLR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxtfl;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_SR (read)                                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SPI2_get_SR(void)
{
    GH_SPI2_SR_REAL_S real;
    GH_SPI2_SR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_SR_REAL);

    dummy.bitc.busy = real.bitc.busy;
    dummy.bitc.tfnf = real.bitc.tfnf;
    dummy.bitc.tfe = real.bitc.tfe;
    dummy.bitc.rfne = real.bitc.rfne;
    dummy.bitc.rff = real.bitc.rff;
    dummy.bitc.txe = real.bitc.txe;
    dummy.bitc.dcol = real.bitc.dcol;
    return dummy.all;
}
GH_INLINE U8   GH_SPI2_get_SR_BUSY(void)
{
    GH_SPI2_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.busy;
}
GH_INLINE U8   GH_SPI2_get_SR_TFNF(void)
{
    GH_SPI2_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tfnf;
}
GH_INLINE U8   GH_SPI2_get_SR_TFE(void)
{
    GH_SPI2_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tfe;
}
GH_INLINE U8   GH_SPI2_get_SR_RFNE(void)
{
    GH_SPI2_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rfne;
}
GH_INLINE U8   GH_SPI2_get_SR_RFF(void)
{
    GH_SPI2_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rff;
}
GH_INLINE U8   GH_SPI2_get_SR_TXE(void)
{
    GH_SPI2_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txe;
}
GH_INLINE U8   GH_SPI2_get_SR_DCOL(void)
{
    GH_SPI2_SR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_SR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dcol;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_IMR (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SPI2_set_IMR(U32 data)
{
    GH_SPI2_IMR_REAL_S real;
    GH_SPI2_IMR_S dummy;
    dummy.all = data ;
    real.bitc.txeim = dummy.bitc.txeim;
    real.bitc.txoim = dummy.bitc.txoim;
    real.bitc.rxuim = dummy.bitc.rxuim;
    real.bitc.rxoim = dummy.bitc.rxoim;
    real.bitc.rxfim = dummy.bitc.rxfim;
    real.bitc.mstim = dummy.bitc.mstim;
    *(volatile U32 *)REG_SPI2_IMR_REAL = real.all;
}
GH_INLINE U32  GH_SPI2_get_IMR(void)
{
    GH_SPI2_IMR_REAL_S real;
    GH_SPI2_IMR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_IMR_REAL);

    dummy.bitc.txeim = real.bitc.txeim;
    dummy.bitc.txoim = real.bitc.txoim;
    dummy.bitc.rxuim = real.bitc.rxuim;
    dummy.bitc.rxoim = real.bitc.rxoim;
    dummy.bitc.rxfim = real.bitc.rxfim;
    dummy.bitc.mstim = real.bitc.mstim;
    return dummy.all;
}
GH_INLINE void GH_SPI2_set_IMR_TXEIM(U8 data)
{
    GH_SPI2_IMR_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_IMR_REAL;
    d.bitc.txeim = data;
    *(volatile U32 *)REG_SPI2_IMR_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_IMR_TXEIM(void)
{
    GH_SPI2_IMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_IMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txeim;
}
GH_INLINE void GH_SPI2_set_IMR_TXOIM(U8 data)
{
    GH_SPI2_IMR_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_IMR_REAL;
    d.bitc.txoim = data;
    *(volatile U32 *)REG_SPI2_IMR_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_IMR_TXOIM(void)
{
    GH_SPI2_IMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_IMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txoim;
}
GH_INLINE void GH_SPI2_set_IMR_RXUIM(U8 data)
{
    GH_SPI2_IMR_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_IMR_REAL;
    d.bitc.rxuim = data;
    *(volatile U32 *)REG_SPI2_IMR_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_IMR_RXUIM(void)
{
    GH_SPI2_IMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_IMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxuim;
}
GH_INLINE void GH_SPI2_set_IMR_RXOIM(U8 data)
{
    GH_SPI2_IMR_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_IMR_REAL;
    d.bitc.rxoim = data;
    *(volatile U32 *)REG_SPI2_IMR_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_IMR_RXOIM(void)
{
    GH_SPI2_IMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_IMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxoim;
}
GH_INLINE void GH_SPI2_set_IMR_RXFIM(U8 data)
{
    GH_SPI2_IMR_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_IMR_REAL;
    d.bitc.rxfim = data;
    *(volatile U32 *)REG_SPI2_IMR_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_IMR_RXFIM(void)
{
    GH_SPI2_IMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_IMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxfim;
}
GH_INLINE void GH_SPI2_set_IMR_MSTIM(U8 data)
{
    GH_SPI2_IMR_REAL_S d;
    d.all = *(volatile U32 *)REG_SPI2_IMR_REAL;
    d.bitc.mstim = data;
    *(volatile U32 *)REG_SPI2_IMR_REAL = d.all;
}
GH_INLINE U8   GH_SPI2_get_IMR_MSTIM(void)
{
    GH_SPI2_IMR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_IMR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mstim;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_ISR (read)                                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SPI2_get_ISR(void)
{
    GH_SPI2_ISR_REAL_S real;
    GH_SPI2_ISR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_ISR_REAL);

    dummy.bitc.txeis = real.bitc.txeis;
    dummy.bitc.txois = real.bitc.txois;
    dummy.bitc.rxuis = real.bitc.rxuis;
    dummy.bitc.rxois = real.bitc.rxois;
    dummy.bitc.rxfis = real.bitc.rxfis;
    dummy.bitc.mstis = real.bitc.mstis;
    return dummy.all;
}
GH_INLINE U8   GH_SPI2_get_ISR_TXEIS(void)
{
    GH_SPI2_ISR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_ISR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txeis;
}
GH_INLINE U8   GH_SPI2_get_ISR_TXOIS(void)
{
    GH_SPI2_ISR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_ISR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txois;
}
GH_INLINE U8   GH_SPI2_get_ISR_RXUIS(void)
{
    GH_SPI2_ISR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_ISR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxuis;
}
GH_INLINE U8   GH_SPI2_get_ISR_RXOIS(void)
{
    GH_SPI2_ISR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_ISR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxois;
}
GH_INLINE U8   GH_SPI2_get_ISR_RXFIS(void)
{
    GH_SPI2_ISR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_ISR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxfis;
}
GH_INLINE U8   GH_SPI2_get_ISR_MSTIS(void)
{
    GH_SPI2_ISR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_ISR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mstis;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_RISR (read)                                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SPI2_get_RISR(void)
{
    GH_SPI2_RISR_REAL_S real;
    GH_SPI2_RISR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_RISR_REAL);

    dummy.bitc.txeir = real.bitc.txeir;
    dummy.bitc.txoir = real.bitc.txoir;
    dummy.bitc.rxuir = real.bitc.rxuir;
    dummy.bitc.rxoir = real.bitc.rxoir;
    dummy.bitc.rxfir = real.bitc.rxfir;
    dummy.bitc.mstir = real.bitc.mstir;
    return dummy.all;
}
GH_INLINE U8   GH_SPI2_get_RISR_TXEIR(void)
{
    GH_SPI2_RISR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_RISR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txeir;
}
GH_INLINE U8   GH_SPI2_get_RISR_TXOIR(void)
{
    GH_SPI2_RISR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_RISR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txoir;
}
GH_INLINE U8   GH_SPI2_get_RISR_RXUIR(void)
{
    GH_SPI2_RISR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_RISR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxuir;
}
GH_INLINE U8   GH_SPI2_get_RISR_RXOIR(void)
{
    GH_SPI2_RISR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_RISR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxoir;
}
GH_INLINE U8   GH_SPI2_get_RISR_RXFIR(void)
{
    GH_SPI2_RISR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_RISR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxfir;
}
GH_INLINE U8   GH_SPI2_get_RISR_MSTIR(void)
{
    GH_SPI2_RISR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_RISR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mstir;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_TXOICR (read)                                                */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SPI2_get_TXOICR(void)
{
    GH_SPI2_TXOICR_REAL_S real;
    GH_SPI2_TXOICR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_TXOICR_REAL);

    dummy.bitc.txoicr = real.bitc.txoicr;
    return dummy.all;
}
GH_INLINE U8   GH_SPI2_get_TXOICR_TXOICR(void)
{
    GH_SPI2_TXOICR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_TXOICR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txoicr;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_RXOICR (read)                                                */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SPI2_get_RXOICR(void)
{
    GH_SPI2_RXOICR_REAL_S real;
    GH_SPI2_RXOICR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_RXOICR_REAL);

    dummy.bitc.rxoicr = real.bitc.rxoicr;
    return dummy.all;
}
GH_INLINE U8   GH_SPI2_get_RXOICR_RXOICR(void)
{
    GH_SPI2_RXOICR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_RXOICR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxoicr;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_RXUICR (read)                                                */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SPI2_get_RXUICR(void)
{
    GH_SPI2_RXUICR_REAL_S real;
    GH_SPI2_RXUICR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_RXUICR_REAL);

    dummy.bitc.rxuicr = real.bitc.rxuicr;
    return dummy.all;
}
GH_INLINE U8   GH_SPI2_get_RXUICR_RXUICR(void)
{
    GH_SPI2_RXUICR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_RXUICR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxuicr;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_MSTICR (read)                                                */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SPI2_get_MSTICR(void)
{
    GH_SPI2_MSTICR_REAL_S real;
    GH_SPI2_MSTICR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_MSTICR_REAL);

    dummy.bitc.msticr = real.bitc.msticr;
    return dummy.all;
}
GH_INLINE U8   GH_SPI2_get_MSTICR_MSTICR(void)
{
    GH_SPI2_MSTICR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_MSTICR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.msticr;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_ICR (read)                                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SPI2_get_ICR(void)
{
    GH_SPI2_ICR_REAL_S real;
    GH_SPI2_ICR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_ICR_REAL);

    dummy.bitc.icr = real.bitc.icr;
    return dummy.all;
}
GH_INLINE U8   GH_SPI2_get_ICR_ICR(void)
{
    GH_SPI2_ICR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_ICR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.icr;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_IDR (read)                                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SPI2_get_IDR(void)
{
    GH_SPI2_IDR_REAL_S real;
    GH_SPI2_IDR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_IDR_REAL);

    dummy.bitc.id = real.bitc.id;
    return dummy.all;
}
GH_INLINE U8   GH_SPI2_get_IDR_ID(void)
{
    GH_SPI2_IDR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_IDR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.id;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_DR (read)                                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_SPI2_get_DR(void)
{
    GH_SPI2_DR_REAL_S real;
    GH_SPI2_DR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_SPI2_DR_REAL);

    dummy.bitc.dr = real.bitc.dr;
    return dummy.all;
}
GH_INLINE U16  GH_SPI2_get_DR_DR(void)
{
    GH_SPI2_DR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI2_DR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dr;
}

/*----------------------------------------------------------------------------*/
/* register SPI2_DW (write)                                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SPI2_set_DW(U32 data)
{
    m_spi2_dw.all = data;
    GH_SPI2_DW_REAL_S real;
    GH_SPI2_DW_S dummy;
    dummy.all = data ;
    real.bitc.dw = dummy.bitc.dw;
    *(volatile U32 *)REG_SPI2_DW_REAL = real.all;
}
GH_INLINE U32  GH_SPI2_getm_DW(void)
{
    #if GH_SPI2_ENABLE_DEBUG_PRINT
    GH_SPI2_DEBUG_PRINT_FUNCTION( "[GH_SPI2_getm_DW] --> 0x%08x\n",
                        m_spi2_dw.all);
    #endif
    return m_spi2_dw.all;
}
GH_INLINE void GH_SPI2_set_DW_DW(U16 data)
{
    m_spi2_dw.bitc.dw = data;
    GH_SPI2_DW_REAL_S real;
    real.bitc.dw = m_spi2_dw.bitc.dw;
    *(volatile U32 *)REG_SPI2_DW_REAL = real.all;
}
GH_INLINE U16  GH_SPI2_getm_DW_DW(void)
{
    #if GH_SPI2_ENABLE_DEBUG_PRINT
    GH_SPI2_DEBUG_PRINT_FUNCTION( "[GH_SPI2_getm_DW_DW] --> 0x%08x\n",
                        m_spi2_dw.bitc.dw);
    #endif
    return m_spi2_dw.bitc.dw;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_SPI2_init(void)
{
    GH_SPI2_set_CTRLR0((U32)0x00000007);
    GH_SPI2_set_CTRLR1((U32)0x00000000);
    GH_SPI2_set_SSIENR((U32)0x00000000);
    GH_SPI2_set_SER((U32)0x00000000);
    GH_SPI2_set_BAUDR((U32)0x00000000);
    GH_SPI2_set_TXFTLR((U32)0x00000000);
    GH_SPI2_set_RXFTLR((U32)0x00000000);
    GH_SPI2_set_TXFLR((U32)0x00000000);
    GH_SPI2_set_RXFLR((U32)0x00000000);
    GH_SPI2_set_IMR((U32)0x0000003f);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

