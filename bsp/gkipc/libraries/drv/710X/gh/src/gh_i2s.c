/******************************************************************************
**
** \file      gh_i2s.c
**
** \brief     I2S Interface..
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
#include "gh_i2s.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_I2S_MODE_REAL                                   FIO_ADDRESS(I2S,0x6000A000) /* read/write */
#define REG_I2S_RXCONTR_REAL                                FIO_ADDRESS(I2S,0x6000A004) /* read/write */
#define REG_I2S_TXCONTR_REAL                                FIO_ADDRESS(I2S,0x6000A008) /* read/write */
#define REG_I2S_WLREG_REAL                                  FIO_ADDRESS(I2S,0x6000A00C) /* read/write */
#define REG_I2S_WPREG_REAL                                  FIO_ADDRESS(I2S,0x6000A010) /* read/write */
#define REG_I2S_SLOTREG_REAL                                FIO_ADDRESS(I2S,0x6000A014) /* read/write */
#define REG_I2S_TXFIFOLTH_REAL                              FIO_ADDRESS(I2S,0x6000A018) /* read/write */
#define REG_I2S_RXFIFOGTH_REAL                              FIO_ADDRESS(I2S,0x6000A01c) /* read/write */
#define REG_I2S_CLOCK_REAL                                  FIO_ADDRESS(I2S,0x6000A020) /* read/write */
#define REG_I2S_INITREG_REAL                                FIO_ADDRESS(I2S,0x6000A024) /* read/write */
#define REG_I2S_TXFIFOFLAG_REAL                             FIO_ADDRESS(I2S,0x6000A028) /* read */
#define REG_I2S_TXLEFTDATA_REAL                             FIO_ADDRESS(I2S,0x6000A02c) /* write */
#define REG_I2S_TXRIGHTDATA_REAL                            FIO_ADDRESS(I2S,0x6000A030) /* write */
#define REG_I2S_RXFIFOFLAG_REAL                             FIO_ADDRESS(I2S,0x6000A034) /* read */
#define REG_I2S_RXDATA_REAL                                 FIO_ADDRESS(I2S,0x6000A038) /* read */
#define REG_I2S_TXFIFCNTR_REAL                              FIO_ADDRESS(I2S,0x6000A03c) /* read */
#define REG_I2S_RXFIFCNTR_REAL                              FIO_ADDRESS(I2S,0x6000A040) /* read */
#define REG_I2S_TXINITENREG_REAL                            FIO_ADDRESS(I2S,0x6000A044) /* read/write */
#define REG_I2S_RXINITENREG_REAL                            FIO_ADDRESS(I2S,0x6000A048) /* read/write */
#define REG_I2S_RXECHO_REAL                                 FIO_ADDRESS(I2S,0x6000A04c) /* read/write */
#define REG_I2S_MULTIPMODE_REAL                             FIO_ADDRESS(I2S,0x6000A050) /* read/write */
#define REG_I2S_SHIFT_REAL                                  FIO_ADDRESS(I2S,0x6000A054) /* read/write */
#define REG_I2S_CHANSLECT_REAL                              FIO_ADDRESS(I2S,0x6000A058) /* read/write */
#define REG_I2S_RX_DMA_REAL                                 FIO_ADDRESS(I2S,0x6000A080) /* read */
#define REG_I2S_TX_LEFT_DMA_REAL                            FIO_ADDRESS(I2S,0x6000A0C0) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* I2S_Mode */
    U32 all;
    struct {
        U32 mode                        : 3;
        U32                             : 29;
    } bitc;
} GH_I2S_MODE_REAL_S;

typedef union { /* I2S_RxContr */
    U32 all;
    struct {
        U32 rwi                         : 1;
        U32 rwm                         : 1;
        U32 order                       : 1;
        U32 loopback                    : 1;
        U32                             : 28;
    } bitc;
} GH_I2S_RXCONTR_REAL_S;

typedef union { /* I2S_TxContr */
    U32 all;
    struct {
        U32 momo                        : 2;
        U32 mute                        : 1;
        U32 unison                      : 1;
        U32 twi                         : 1;
        U32 twm                         : 1;
        U32 order                       : 1;
        U32 loopback                    : 1;
        U32                             : 24;
    } bitc;
} GH_I2S_TXCONTR_REAL_S;

typedef union { /* I2S_WlReg */
    U32 all;
    struct {
        U32 wlen                        : 5;
        U32                             : 27;
    } bitc;
} GH_I2S_WLREG_REAL_S;

typedef union { /* I2S_WPREG */
    U32 all;
    struct {
        U32 ignbit                      : 5;
        U32                             : 27;
    } bitc;
} GH_I2S_WPREG_REAL_S;

typedef union { /* I2S_SlotReg */
    U32 all;
    struct {
        U32 slotcont                    : 5;
        U32                             : 27;
    } bitc;
} GH_I2S_SLOTREG_REAL_S;

typedef union { /* I2S_TxFifoLth */
    U32 all;
    struct {
        U32 ft                          : 7;
        U32                             : 25;
    } bitc;
} GH_I2S_TXFIFOLTH_REAL_S;

typedef union { /* I2S_RxFifoGth */
    U32 all;
    struct {
        U32 ft                          : 7;
        U32                             : 25;
    } bitc;
} GH_I2S_RXFIFOGTH_REAL_S;

typedef union { /* I2S_Clock */
    U32 all;
    struct {
        U32 clk_div                     : 5;
        U32 rsp                         : 1;
        U32 tsp                         : 1;
        U32 ss                          : 1;
        U32 soe                         : 1;
        U32 woe                         : 1;
        U32                             : 22;
    } bitc;
} GH_I2S_CLOCK_REAL_S;

typedef union { /* I2S_Initreg */
    U32 all;
    struct {
        U32 frst                        : 1;
        U32 re                          : 1;
        U32 te                          : 1;
        U32 rxfrst                      : 1;
        U32 txfrst                      : 1;
        U32                             : 27;
    } bitc;
} GH_I2S_INITREG_REAL_S;

typedef union { /* I2S_TxFifoFlag */
    U32 all;
    struct {
        U32 fe                          : 1;
        U32 ff                          : 1;
        U32                             : 1;
        U32 ftv                         : 1;
        U32 ti                          : 1;
        U32                             : 27;
    } bitc;
} GH_I2S_TXFIFOFLAG_REAL_S;

typedef union { /* I2S_TxLeftData */
    U32 all;
    struct {
        U32 data                        : 32;
    } bitc;
} GH_I2S_TXLEFTDATA_REAL_S;

typedef union { /* I2S_TxRightData */
    U32 all;
    struct {
        U32 data                        : 24;
        U32                             : 8;
    } bitc;
} GH_I2S_TXRIGHTDATA_REAL_S;

typedef union { /* I2S_RxFifoFlag */
    U32 all;
    struct {
        U32 fe                          : 1;
        U32 ff                          : 1;
        U32 fo                          : 1;
        U32 ftv                         : 1;
        U32 ri                          : 1;
        U32                             : 27;
    } bitc;
} GH_I2S_RXFIFOFLAG_REAL_S;

typedef union { /* I2S_RxData */
    U32 all;
    struct {
        U32 data                        : 24;
        U32                             : 8;
    } bitc;
} GH_I2S_RXDATA_REAL_S;

typedef union { /* I2S_TxFifCntr */
    U32 all;
    struct {
        U32 num                         : 7;
        U32                             : 25;
    } bitc;
} GH_I2S_TXFIFCNTR_REAL_S;

typedef union { /* I2S_Rxfifcntr */
    U32 all;
    struct {
        U32 num                         : 8;
        U32                             : 24;
    } bitc;
} GH_I2S_RXFIFCNTR_REAL_S;

typedef union { /* I2S_TxInitEnReg */
    U32 all;
    struct {
        U32 fe                          : 1;
        U32 ff                          : 1;
        U32                             : 1;
        U32 ftv                         : 1;
        U32 ti                          : 1;
        U32                             : 27;
    } bitc;
} GH_I2S_TXINITENREG_REAL_S;

typedef union { /* I2S_RxInitEnReg */
    U32 all;
    struct {
        U32 fe                          : 1;
        U32 ff                          : 1;
        U32 fo                          : 1;
        U32 ftv                         : 1;
        U32 ri                          : 1;
        U32                             : 27;
    } bitc;
} GH_I2S_RXINITENREG_REAL_S;

typedef union { /* I2S_RxEcho */
    U32 all;
    struct {
        U32 echo                        : 1;
        U32                             : 31;
    } bitc;
} GH_I2S_RXECHO_REAL_S;

typedef union { /* I2S_MultipMode */
    U32 all;
    struct {
        U32 en                          : 1;
        U32 fdmaen                      : 1;
        U32 rest                        : 1;
        U32 dma                         : 1;
        U32                             : 28;
    } bitc;
} GH_I2S_MULTIPMODE_REAL_S;

typedef union { /* I2S_Shift */
    U32 all;
    struct {
        U32 tx                          : 1;
        U32 rx                          : 1;
        U32                             : 30;
    } bitc;
} GH_I2S_SHIFT_REAL_S;

typedef union { /* I2S_ChanSlect */
    U32 all;
    struct {
        U32 chan                        : 2;
        U32                             : 30;
    } bitc;
} GH_I2S_CHANSLECT_REAL_S;

typedef union { /* I2S_Rx_Dma */
    U32 all;
    struct {
        U32 data                        : 24;
        U32                             : 8;
    } bitc;
} GH_I2S_RX_DMA_REAL_S;

typedef union { /* I2S_Tx_Left_Dma */
    U32 all;
    struct {
        U32 data                        : 32;
    } bitc;
} GH_I2S_TX_LEFT_DMA_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_I2S_TXLEFTDATA_S                     m_i2s_txleftdata;
GH_I2S_TXRIGHTDATA_S                    m_i2s_txrightdata;

/*----------------------------------------------------------------------------*/
/* register I2S_Mode (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_Mode(U32 data)
{
    GH_I2S_MODE_REAL_S real;
    GH_I2S_MODE_S dummy;
    dummy.all = data ;
    real.bitc.mode = dummy.bitc.mode;
    *(volatile U32 *)REG_I2S_MODE_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_Mode(void)
{
    GH_I2S_MODE_REAL_S real;
    GH_I2S_MODE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_MODE_REAL);

    dummy.bitc.mode = real.bitc.mode;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_Mode_MODE(U8 data)
{
    GH_I2S_MODE_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_MODE_REAL;
    d.bitc.mode = data;
    *(volatile U32 *)REG_I2S_MODE_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_Mode_MODE(void)
{
    GH_I2S_MODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mode;
}

/*----------------------------------------------------------------------------*/
/* register I2S_RxContr (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_RxContr(U32 data)
{
    GH_I2S_RXCONTR_REAL_S real;
    GH_I2S_RXCONTR_S dummy;
    dummy.all = data ;
    real.bitc.rwi = dummy.bitc.rwi;
    real.bitc.rwm = dummy.bitc.rwm;
    real.bitc.order = dummy.bitc.order;
    real.bitc.loopback = dummy.bitc.loopback;
    *(volatile U32 *)REG_I2S_RXCONTR_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_RxContr(void)
{
    GH_I2S_RXCONTR_REAL_S real;
    GH_I2S_RXCONTR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_RXCONTR_REAL);

    dummy.bitc.rwi = real.bitc.rwi;
    dummy.bitc.rwm = real.bitc.rwm;
    dummy.bitc.order = real.bitc.order;
    dummy.bitc.loopback = real.bitc.loopback;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_RxContr_rwi(U8 data)
{
    GH_I2S_RXCONTR_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_RXCONTR_REAL;
    d.bitc.rwi = data;
    *(volatile U32 *)REG_I2S_RXCONTR_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_RxContr_rwi(void)
{
    GH_I2S_RXCONTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXCONTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rwi;
}
GH_INLINE void GH_I2S_set_RxContr_rwm(U8 data)
{
    GH_I2S_RXCONTR_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_RXCONTR_REAL;
    d.bitc.rwm = data;
    *(volatile U32 *)REG_I2S_RXCONTR_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_RxContr_rwm(void)
{
    GH_I2S_RXCONTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXCONTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rwm;
}
GH_INLINE void GH_I2S_set_RxContr_order(U8 data)
{
    GH_I2S_RXCONTR_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_RXCONTR_REAL;
    d.bitc.order = data;
    *(volatile U32 *)REG_I2S_RXCONTR_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_RxContr_order(void)
{
    GH_I2S_RXCONTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXCONTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.order;
}
GH_INLINE void GH_I2S_set_RxContr_loopback(U8 data)
{
    GH_I2S_RXCONTR_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_RXCONTR_REAL;
    d.bitc.loopback = data;
    *(volatile U32 *)REG_I2S_RXCONTR_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_RxContr_loopback(void)
{
    GH_I2S_RXCONTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXCONTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.loopback;
}

/*----------------------------------------------------------------------------*/
/* register I2S_TxContr (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_TxContr(U32 data)
{
    GH_I2S_TXCONTR_REAL_S real;
    GH_I2S_TXCONTR_S dummy;
    dummy.all = data ;
    real.bitc.momo = dummy.bitc.momo;
    real.bitc.mute = dummy.bitc.mute;
    real.bitc.unison = dummy.bitc.unison;
    real.bitc.twi = dummy.bitc.twi;
    real.bitc.twm = dummy.bitc.twm;
    real.bitc.order = dummy.bitc.order;
    real.bitc.loopback = dummy.bitc.loopback;
    *(volatile U32 *)REG_I2S_TXCONTR_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_TxContr(void)
{
    GH_I2S_TXCONTR_REAL_S real;
    GH_I2S_TXCONTR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_TXCONTR_REAL);

    dummy.bitc.momo = real.bitc.momo;
    dummy.bitc.mute = real.bitc.mute;
    dummy.bitc.unison = real.bitc.unison;
    dummy.bitc.twi = real.bitc.twi;
    dummy.bitc.twm = real.bitc.twm;
    dummy.bitc.order = real.bitc.order;
    dummy.bitc.loopback = real.bitc.loopback;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_TxContr_momo(U8 data)
{
    GH_I2S_TXCONTR_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_TXCONTR_REAL;
    d.bitc.momo = data;
    *(volatile U32 *)REG_I2S_TXCONTR_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_TxContr_momo(void)
{
    GH_I2S_TXCONTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.momo;
}
GH_INLINE void GH_I2S_set_TxContr_mute(U8 data)
{
    GH_I2S_TXCONTR_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_TXCONTR_REAL;
    d.bitc.mute = data;
    *(volatile U32 *)REG_I2S_TXCONTR_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_TxContr_mute(void)
{
    GH_I2S_TXCONTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mute;
}
GH_INLINE void GH_I2S_set_TxContr_unison(U8 data)
{
    GH_I2S_TXCONTR_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_TXCONTR_REAL;
    d.bitc.unison = data;
    *(volatile U32 *)REG_I2S_TXCONTR_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_TxContr_unison(void)
{
    GH_I2S_TXCONTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.unison;
}
GH_INLINE void GH_I2S_set_TxContr_twi(U8 data)
{
    GH_I2S_TXCONTR_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_TXCONTR_REAL;
    d.bitc.twi = data;
    *(volatile U32 *)REG_I2S_TXCONTR_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_TxContr_twi(void)
{
    GH_I2S_TXCONTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.twi;
}
GH_INLINE void GH_I2S_set_TxContr_twm(U8 data)
{
    GH_I2S_TXCONTR_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_TXCONTR_REAL;
    d.bitc.twm = data;
    *(volatile U32 *)REG_I2S_TXCONTR_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_TxContr_twm(void)
{
    GH_I2S_TXCONTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.twm;
}
GH_INLINE void GH_I2S_set_TxContr_order(U8 data)
{
    GH_I2S_TXCONTR_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_TXCONTR_REAL;
    d.bitc.order = data;
    *(volatile U32 *)REG_I2S_TXCONTR_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_TxContr_order(void)
{
    GH_I2S_TXCONTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.order;
}
GH_INLINE void GH_I2S_set_TxContr_loopback(U8 data)
{
    GH_I2S_TXCONTR_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_TXCONTR_REAL;
    d.bitc.loopback = data;
    *(volatile U32 *)REG_I2S_TXCONTR_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_TxContr_loopback(void)
{
    GH_I2S_TXCONTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.loopback;
}

/*----------------------------------------------------------------------------*/
/* register I2S_WlReg (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_WlReg(U32 data)
{
    GH_I2S_WLREG_REAL_S real;
    GH_I2S_WLREG_S dummy;
    dummy.all = data ;
    real.bitc.wlen = dummy.bitc.wlen;
    *(volatile U32 *)REG_I2S_WLREG_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_WlReg(void)
{
    GH_I2S_WLREG_REAL_S real;
    GH_I2S_WLREG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_WLREG_REAL);

    dummy.bitc.wlen = real.bitc.wlen;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_WlReg_Wlen(U8 data)
{
    GH_I2S_WLREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_WLREG_REAL;
    d.bitc.wlen = data;
    *(volatile U32 *)REG_I2S_WLREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_WlReg_Wlen(void)
{
    GH_I2S_WLREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_WLREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.wlen;
}

/*----------------------------------------------------------------------------*/
/* register I2S_WPREG (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_WPREG(U32 data)
{
    GH_I2S_WPREG_REAL_S real;
    GH_I2S_WPREG_S dummy;
    dummy.all = data ;
    real.bitc.ignbit = dummy.bitc.ignbit;
    *(volatile U32 *)REG_I2S_WPREG_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_WPREG(void)
{
    GH_I2S_WPREG_REAL_S real;
    GH_I2S_WPREG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_WPREG_REAL);

    dummy.bitc.ignbit = real.bitc.ignbit;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_WPREG_Ignbit(U8 data)
{
    GH_I2S_WPREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_WPREG_REAL;
    d.bitc.ignbit = data;
    *(volatile U32 *)REG_I2S_WPREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_WPREG_Ignbit(void)
{
    GH_I2S_WPREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_WPREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ignbit;
}

/*----------------------------------------------------------------------------*/
/* register I2S_SlotReg (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_SlotReg(U32 data)
{
    GH_I2S_SLOTREG_REAL_S real;
    GH_I2S_SLOTREG_S dummy;
    dummy.all = data ;
    real.bitc.slotcont = dummy.bitc.slotcont;
    *(volatile U32 *)REG_I2S_SLOTREG_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_SlotReg(void)
{
    GH_I2S_SLOTREG_REAL_S real;
    GH_I2S_SLOTREG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_SLOTREG_REAL);

    dummy.bitc.slotcont = real.bitc.slotcont;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_SlotReg_slotcont(U8 data)
{
    GH_I2S_SLOTREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_SLOTREG_REAL;
    d.bitc.slotcont = data;
    *(volatile U32 *)REG_I2S_SLOTREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_SlotReg_slotcont(void)
{
    GH_I2S_SLOTREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_SLOTREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.slotcont;
}

/*----------------------------------------------------------------------------*/
/* register I2S_TxFifoLth (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_TxFifoLth(U32 data)
{
    GH_I2S_TXFIFOLTH_REAL_S real;
    GH_I2S_TXFIFOLTH_S dummy;
    dummy.all = data ;
    real.bitc.ft = dummy.bitc.ft;
    *(volatile U32 *)REG_I2S_TXFIFOLTH_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_TxFifoLth(void)
{
    GH_I2S_TXFIFOLTH_REAL_S real;
    GH_I2S_TXFIFOLTH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_TXFIFOLTH_REAL);

    dummy.bitc.ft = real.bitc.ft;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_TxFifoLth_ft(U8 data)
{
    GH_I2S_TXFIFOLTH_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_TXFIFOLTH_REAL;
    d.bitc.ft = data;
    *(volatile U32 *)REG_I2S_TXFIFOLTH_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_TxFifoLth_ft(void)
{
    GH_I2S_TXFIFOLTH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFOLTH_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ft;
}

/*----------------------------------------------------------------------------*/
/* register I2S_RxFifoGth (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_RxFifoGth(U32 data)
{
    GH_I2S_RXFIFOGTH_REAL_S real;
    GH_I2S_RXFIFOGTH_S dummy;
    dummy.all = data ;
    real.bitc.ft = dummy.bitc.ft;
    *(volatile U32 *)REG_I2S_RXFIFOGTH_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_RxFifoGth(void)
{
    GH_I2S_RXFIFOGTH_REAL_S real;
    GH_I2S_RXFIFOGTH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_RXFIFOGTH_REAL);

    dummy.bitc.ft = real.bitc.ft;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_RxFifoGth_ft(U8 data)
{
    GH_I2S_RXFIFOGTH_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_RXFIFOGTH_REAL;
    d.bitc.ft = data;
    *(volatile U32 *)REG_I2S_RXFIFOGTH_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_RxFifoGth_ft(void)
{
    GH_I2S_RXFIFOGTH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOGTH_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ft;
}

/*----------------------------------------------------------------------------*/
/* register I2S_Clock (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_Clock(U32 data)
{
    GH_I2S_CLOCK_REAL_S real;
    GH_I2S_CLOCK_S dummy;
    dummy.all = data ;
    real.bitc.clk_div = dummy.bitc.clk_div;
    real.bitc.rsp = dummy.bitc.rsp;
    real.bitc.tsp = dummy.bitc.tsp;
    real.bitc.ss = dummy.bitc.ss;
    real.bitc.soe = dummy.bitc.soe;
    real.bitc.woe = dummy.bitc.woe;
    *(volatile U32 *)REG_I2S_CLOCK_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_Clock(void)
{
    GH_I2S_CLOCK_REAL_S real;
    GH_I2S_CLOCK_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_CLOCK_REAL);

    dummy.bitc.clk_div = real.bitc.clk_div;
    dummy.bitc.rsp = real.bitc.rsp;
    dummy.bitc.tsp = real.bitc.tsp;
    dummy.bitc.ss = real.bitc.ss;
    dummy.bitc.soe = real.bitc.soe;
    dummy.bitc.woe = real.bitc.woe;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_Clock_clk_div(U8 data)
{
    GH_I2S_CLOCK_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_CLOCK_REAL;
    d.bitc.clk_div = data;
    *(volatile U32 *)REG_I2S_CLOCK_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_Clock_clk_div(void)
{
    GH_I2S_CLOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_CLOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clk_div;
}
GH_INLINE void GH_I2S_set_Clock_rsp(U8 data)
{
    GH_I2S_CLOCK_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_CLOCK_REAL;
    d.bitc.rsp = data;
    *(volatile U32 *)REG_I2S_CLOCK_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_Clock_rsp(void)
{
    GH_I2S_CLOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_CLOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rsp;
}
GH_INLINE void GH_I2S_set_Clock_tsp(U8 data)
{
    GH_I2S_CLOCK_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_CLOCK_REAL;
    d.bitc.tsp = data;
    *(volatile U32 *)REG_I2S_CLOCK_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_Clock_tsp(void)
{
    GH_I2S_CLOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_CLOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tsp;
}
GH_INLINE void GH_I2S_set_Clock_ss(U8 data)
{
    GH_I2S_CLOCK_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_CLOCK_REAL;
    d.bitc.ss = data;
    *(volatile U32 *)REG_I2S_CLOCK_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_Clock_ss(void)
{
    GH_I2S_CLOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_CLOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ss;
}
GH_INLINE void GH_I2S_set_Clock_soe(U8 data)
{
    GH_I2S_CLOCK_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_CLOCK_REAL;
    d.bitc.soe = data;
    *(volatile U32 *)REG_I2S_CLOCK_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_Clock_soe(void)
{
    GH_I2S_CLOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_CLOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.soe;
}
GH_INLINE void GH_I2S_set_Clock_woe(U8 data)
{
    GH_I2S_CLOCK_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_CLOCK_REAL;
    d.bitc.woe = data;
    *(volatile U32 *)REG_I2S_CLOCK_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_Clock_woe(void)
{
    GH_I2S_CLOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_CLOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.woe;
}

/*----------------------------------------------------------------------------*/
/* register I2S_Initreg (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_Initreg(U32 data)
{
    GH_I2S_INITREG_REAL_S real;
    GH_I2S_INITREG_S dummy;
    dummy.all = data ;
    real.bitc.frst = dummy.bitc.frst;
    real.bitc.re = dummy.bitc.re;
    real.bitc.te = dummy.bitc.te;
    real.bitc.rxfrst = dummy.bitc.rxfrst;
    real.bitc.txfrst = dummy.bitc.txfrst;
    *(volatile U32 *)REG_I2S_INITREG_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_Initreg(void)
{
    GH_I2S_INITREG_REAL_S real;
    GH_I2S_INITREG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_INITREG_REAL);

    dummy.bitc.frst = real.bitc.frst;
    dummy.bitc.re = real.bitc.re;
    dummy.bitc.te = real.bitc.te;
    dummy.bitc.rxfrst = real.bitc.rxfrst;
    dummy.bitc.txfrst = real.bitc.txfrst;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_Initreg_frst(U8 data)
{
    GH_I2S_INITREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_INITREG_REAL;
    d.bitc.frst = data;
    *(volatile U32 *)REG_I2S_INITREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_Initreg_frst(void)
{
    GH_I2S_INITREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_INITREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.frst;
}
GH_INLINE void GH_I2S_set_Initreg_re(U8 data)
{
    GH_I2S_INITREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_INITREG_REAL;
    d.bitc.re = data;
    *(volatile U32 *)REG_I2S_INITREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_Initreg_re(void)
{
    GH_I2S_INITREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_INITREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.re;
}
GH_INLINE void GH_I2S_set_Initreg_te(U8 data)
{
    GH_I2S_INITREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_INITREG_REAL;
    d.bitc.te = data;
    *(volatile U32 *)REG_I2S_INITREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_Initreg_te(void)
{
    GH_I2S_INITREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_INITREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.te;
}
GH_INLINE void GH_I2S_set_Initreg_rxfrst(U8 data)
{
    GH_I2S_INITREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_INITREG_REAL;
    d.bitc.rxfrst = data;
    *(volatile U32 *)REG_I2S_INITREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_Initreg_rxfrst(void)
{
    GH_I2S_INITREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_INITREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxfrst;
}
GH_INLINE void GH_I2S_set_Initreg_txfrst(U8 data)
{
    GH_I2S_INITREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_INITREG_REAL;
    d.bitc.txfrst = data;
    *(volatile U32 *)REG_I2S_INITREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_Initreg_txfrst(void)
{
    GH_I2S_INITREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_INITREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txfrst;
}

/*----------------------------------------------------------------------------*/
/* register I2S_TxFifoFlag (read)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_I2S_get_TxFifoFlag(void)
{
    GH_I2S_TXFIFOFLAG_REAL_S real;
    GH_I2S_TXFIFOFLAG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_TXFIFOFLAG_REAL);

    dummy.bitc.fe = real.bitc.fe;
    dummy.bitc.ff = real.bitc.ff;
    dummy.bitc.ftv = real.bitc.ftv;
    dummy.bitc.ti = real.bitc.ti;
    return dummy.all;
}
GH_INLINE U8   GH_I2S_get_TxFifoFlag_fe(void)
{
    GH_I2S_TXFIFOFLAG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFOFLAG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fe;
}
GH_INLINE U8   GH_I2S_get_TxFifoFlag_ff(void)
{
    GH_I2S_TXFIFOFLAG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFOFLAG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ff;
}
GH_INLINE U8   GH_I2S_get_TxFifoFlag_ftv(void)
{
    GH_I2S_TXFIFOFLAG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFOFLAG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ftv;
}
GH_INLINE U8   GH_I2S_get_TxFifoFlag_ti(void)
{
    GH_I2S_TXFIFOFLAG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFOFLAG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ti;
}

/*----------------------------------------------------------------------------*/
/* register I2S_TxLeftData (write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_TxLeftData(U32 data)
{
    m_i2s_txleftdata.all = data;
    GH_I2S_TXLEFTDATA_REAL_S real;
    GH_I2S_TXLEFTDATA_S dummy;
    dummy.all = data ;
    real.bitc.data = dummy.bitc.data;
    *(volatile U32 *)REG_I2S_TXLEFTDATA_REAL = real.all;
}
GH_INLINE U32  GH_I2S_getm_TxLeftData(void)
{
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "[GH_I2S_getm_TxLeftData] --> 0x%08x\n",
                        m_i2s_txleftdata.all);
    #endif
    return m_i2s_txleftdata.all;
}
GH_INLINE void GH_I2S_set_TxLeftData_data(U32 data)
{
    m_i2s_txleftdata.bitc.data = data;
    GH_I2S_TXLEFTDATA_REAL_S real;
    real.bitc.data = m_i2s_txleftdata.bitc.data;
    *(volatile U32 *)REG_I2S_TXLEFTDATA_REAL = real.all;
}
GH_INLINE U32  GH_I2S_getm_TxLeftData_data(void)
{
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "[GH_I2S_getm_TxLeftData_data] --> 0x%08x\n",
                        m_i2s_txleftdata.bitc.data);
    #endif
    return m_i2s_txleftdata.bitc.data;
}

/*----------------------------------------------------------------------------*/
/* register I2S_TxRightData (write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_TxRightData(U32 data)
{
    m_i2s_txrightdata.all = data;
    GH_I2S_TXRIGHTDATA_REAL_S real;
    GH_I2S_TXRIGHTDATA_S dummy;
    dummy.all = data ;
    real.bitc.data = dummy.bitc.data;
    *(volatile U32 *)REG_I2S_TXRIGHTDATA_REAL = real.all;
}
GH_INLINE U32  GH_I2S_getm_TxRightData(void)
{
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "[GH_I2S_getm_TxRightData] --> 0x%08x\n",
                        m_i2s_txrightdata.all);
    #endif
    return m_i2s_txrightdata.all;
}
GH_INLINE void GH_I2S_set_TxRightData_data(U32 data)
{
    m_i2s_txrightdata.bitc.data = data;
    GH_I2S_TXRIGHTDATA_REAL_S real;
    real.bitc.data = m_i2s_txrightdata.bitc.data;
    *(volatile U32 *)REG_I2S_TXRIGHTDATA_REAL = real.all;
}
GH_INLINE U32  GH_I2S_getm_TxRightData_data(void)
{
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "[GH_I2S_getm_TxRightData_data] --> 0x%08x\n",
                        m_i2s_txrightdata.bitc.data);
    #endif
    return m_i2s_txrightdata.bitc.data;
}

/*----------------------------------------------------------------------------*/
/* register I2S_RxFifoFlag (read)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_I2S_get_RxFifoFlag(void)
{
    GH_I2S_RXFIFOFLAG_REAL_S real;
    GH_I2S_RXFIFOFLAG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_RXFIFOFLAG_REAL);

    dummy.bitc.fe = real.bitc.fe;
    dummy.bitc.ff = real.bitc.ff;
    dummy.bitc.fo = real.bitc.fo;
    dummy.bitc.ftv = real.bitc.ftv;
    dummy.bitc.ri = real.bitc.ri;
    return dummy.all;
}
GH_INLINE U8   GH_I2S_get_RxFifoFlag_fe(void)
{
    GH_I2S_RXFIFOFLAG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOFLAG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fe;
}
GH_INLINE U8   GH_I2S_get_RxFifoFlag_ff(void)
{
    GH_I2S_RXFIFOFLAG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOFLAG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ff;
}
GH_INLINE U8   GH_I2S_get_RxFifoFlag_fo(void)
{
    GH_I2S_RXFIFOFLAG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOFLAG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fo;
}
GH_INLINE U8   GH_I2S_get_RxFifoFlag_ftv(void)
{
    GH_I2S_RXFIFOFLAG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOFLAG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ftv;
}
GH_INLINE U8   GH_I2S_get_RxFifoFlag_ri(void)
{
    GH_I2S_RXFIFOFLAG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOFLAG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ri;
}

/*----------------------------------------------------------------------------*/
/* register I2S_RxData (read)                                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_I2S_get_RxData(void)
{
    GH_I2S_RXDATA_REAL_S real;
    GH_I2S_RXDATA_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_RXDATA_REAL);

    dummy.bitc.data = real.bitc.data;
    return dummy.all;
}
GH_INLINE U32  GH_I2S_get_RxData_data(void)
{
    GH_I2S_RXDATA_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXDATA_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.data;
}

/*----------------------------------------------------------------------------*/
/* register I2S_TxFifCntr (read)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_I2S_get_TxFifCntr(void)
{
    GH_I2S_TXFIFCNTR_REAL_S real;
    GH_I2S_TXFIFCNTR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_TXFIFCNTR_REAL);

    dummy.bitc.num = real.bitc.num;
    return dummy.all;
}
GH_INLINE U8   GH_I2S_get_TxFifCntr_num(void)
{
    GH_I2S_TXFIFCNTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFCNTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.num;
}

/*----------------------------------------------------------------------------*/
/* register I2S_Rxfifcntr (read)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_I2S_get_Rxfifcntr(void)
{
    GH_I2S_RXFIFCNTR_REAL_S real;
    GH_I2S_RXFIFCNTR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_RXFIFCNTR_REAL);

    dummy.bitc.num = real.bitc.num;
    return dummy.all;
}
GH_INLINE U8   GH_I2S_get_Rxfifcntr_num(void)
{
    GH_I2S_RXFIFCNTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFCNTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.num;
}

/*----------------------------------------------------------------------------*/
/* register I2S_TxInitEnReg (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_TxInitEnReg(U32 data)
{
    GH_I2S_TXINITENREG_REAL_S real;
    GH_I2S_TXINITENREG_S dummy;
    dummy.all = data ;
    real.bitc.fe = dummy.bitc.fe;
    real.bitc.ff = dummy.bitc.ff;
    real.bitc.ftv = dummy.bitc.ftv;
    real.bitc.ti = dummy.bitc.ti;
    *(volatile U32 *)REG_I2S_TXINITENREG_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_TxInitEnReg(void)
{
    GH_I2S_TXINITENREG_REAL_S real;
    GH_I2S_TXINITENREG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_TXINITENREG_REAL);

    dummy.bitc.fe = real.bitc.fe;
    dummy.bitc.ff = real.bitc.ff;
    dummy.bitc.ftv = real.bitc.ftv;
    dummy.bitc.ti = real.bitc.ti;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_TxInitEnReg_fe(U8 data)
{
    GH_I2S_TXINITENREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_TXINITENREG_REAL;
    d.bitc.fe = data;
    *(volatile U32 *)REG_I2S_TXINITENREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_TxInitEnReg_fe(void)
{
    GH_I2S_TXINITENREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXINITENREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fe;
}
GH_INLINE void GH_I2S_set_TxInitEnReg_ff(U8 data)
{
    GH_I2S_TXINITENREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_TXINITENREG_REAL;
    d.bitc.ff = data;
    *(volatile U32 *)REG_I2S_TXINITENREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_TxInitEnReg_ff(void)
{
    GH_I2S_TXINITENREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXINITENREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ff;
}
GH_INLINE void GH_I2S_set_TxInitEnReg_ftv(U8 data)
{
    GH_I2S_TXINITENREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_TXINITENREG_REAL;
    d.bitc.ftv = data;
    *(volatile U32 *)REG_I2S_TXINITENREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_TxInitEnReg_ftv(void)
{
    GH_I2S_TXINITENREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXINITENREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ftv;
}
GH_INLINE void GH_I2S_set_TxInitEnReg_ti(U8 data)
{
    GH_I2S_TXINITENREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_TXINITENREG_REAL;
    d.bitc.ti = data;
    *(volatile U32 *)REG_I2S_TXINITENREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_TxInitEnReg_ti(void)
{
    GH_I2S_TXINITENREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXINITENREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ti;
}

/*----------------------------------------------------------------------------*/
/* register I2S_RxInitEnReg (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_RxInitEnReg(U32 data)
{
    GH_I2S_RXINITENREG_REAL_S real;
    GH_I2S_RXINITENREG_S dummy;
    dummy.all = data ;
    real.bitc.fe = dummy.bitc.fe;
    real.bitc.ff = dummy.bitc.ff;
    real.bitc.fo = dummy.bitc.fo;
    real.bitc.ftv = dummy.bitc.ftv;
    real.bitc.ri = dummy.bitc.ri;
    *(volatile U32 *)REG_I2S_RXINITENREG_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_RxInitEnReg(void)
{
    GH_I2S_RXINITENREG_REAL_S real;
    GH_I2S_RXINITENREG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_RXINITENREG_REAL);

    dummy.bitc.fe = real.bitc.fe;
    dummy.bitc.ff = real.bitc.ff;
    dummy.bitc.fo = real.bitc.fo;
    dummy.bitc.ftv = real.bitc.ftv;
    dummy.bitc.ri = real.bitc.ri;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_RxInitEnReg_fe(U8 data)
{
    GH_I2S_RXINITENREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_RXINITENREG_REAL;
    d.bitc.fe = data;
    *(volatile U32 *)REG_I2S_RXINITENREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_RxInitEnReg_fe(void)
{
    GH_I2S_RXINITENREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXINITENREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fe;
}
GH_INLINE void GH_I2S_set_RxInitEnReg_ff(U8 data)
{
    GH_I2S_RXINITENREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_RXINITENREG_REAL;
    d.bitc.ff = data;
    *(volatile U32 *)REG_I2S_RXINITENREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_RxInitEnReg_ff(void)
{
    GH_I2S_RXINITENREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXINITENREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ff;
}
GH_INLINE void GH_I2S_set_RxInitEnReg_fo(U8 data)
{
    GH_I2S_RXINITENREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_RXINITENREG_REAL;
    d.bitc.fo = data;
    *(volatile U32 *)REG_I2S_RXINITENREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_RxInitEnReg_fo(void)
{
    GH_I2S_RXINITENREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXINITENREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fo;
}
GH_INLINE void GH_I2S_set_RxInitEnReg_ftv(U8 data)
{
    GH_I2S_RXINITENREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_RXINITENREG_REAL;
    d.bitc.ftv = data;
    *(volatile U32 *)REG_I2S_RXINITENREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_RxInitEnReg_ftv(void)
{
    GH_I2S_RXINITENREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXINITENREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ftv;
}
GH_INLINE void GH_I2S_set_RxInitEnReg_ri(U8 data)
{
    GH_I2S_RXINITENREG_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_RXINITENREG_REAL;
    d.bitc.ri = data;
    *(volatile U32 *)REG_I2S_RXINITENREG_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_RxInitEnReg_ri(void)
{
    GH_I2S_RXINITENREG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXINITENREG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ri;
}

/*----------------------------------------------------------------------------*/
/* register I2S_RxEcho (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_RxEcho(U32 data)
{
    GH_I2S_RXECHO_REAL_S real;
    GH_I2S_RXECHO_S dummy;
    dummy.all = data ;
    real.bitc.echo = dummy.bitc.echo;
    *(volatile U32 *)REG_I2S_RXECHO_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_RxEcho(void)
{
    GH_I2S_RXECHO_REAL_S real;
    GH_I2S_RXECHO_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_RXECHO_REAL);

    dummy.bitc.echo = real.bitc.echo;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_RxEcho_echo(U8 data)
{
    GH_I2S_RXECHO_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_RXECHO_REAL;
    d.bitc.echo = data;
    *(volatile U32 *)REG_I2S_RXECHO_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_RxEcho_echo(void)
{
    GH_I2S_RXECHO_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXECHO_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.echo;
}

/*----------------------------------------------------------------------------*/
/* register I2S_MultipMode (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_MultipMode(U32 data)
{
    GH_I2S_MULTIPMODE_REAL_S real;
    GH_I2S_MULTIPMODE_S dummy;
    dummy.all = data ;
    real.bitc.en = dummy.bitc.en;
    real.bitc.fdmaen = dummy.bitc.fdmaen;
    real.bitc.rest = dummy.bitc.rest;
    real.bitc.dma = dummy.bitc.dma;
    *(volatile U32 *)REG_I2S_MULTIPMODE_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_MultipMode(void)
{
    GH_I2S_MULTIPMODE_REAL_S real;
    GH_I2S_MULTIPMODE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_MULTIPMODE_REAL);

    dummy.bitc.en = real.bitc.en;
    dummy.bitc.fdmaen = real.bitc.fdmaen;
    dummy.bitc.rest = real.bitc.rest;
    dummy.bitc.dma = real.bitc.dma;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_MultipMode_en(U8 data)
{
    GH_I2S_MULTIPMODE_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_MULTIPMODE_REAL;
    d.bitc.en = data;
    *(volatile U32 *)REG_I2S_MULTIPMODE_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_MultipMode_en(void)
{
    GH_I2S_MULTIPMODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_MULTIPMODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en;
}
GH_INLINE void GH_I2S_set_MultipMode_fdmaen(U8 data)
{
    GH_I2S_MULTIPMODE_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_MULTIPMODE_REAL;
    d.bitc.fdmaen = data;
    *(volatile U32 *)REG_I2S_MULTIPMODE_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_MultipMode_fdmaen(void)
{
    GH_I2S_MULTIPMODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_MULTIPMODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fdmaen;
}
GH_INLINE void GH_I2S_set_MultipMode_rest(U8 data)
{
    GH_I2S_MULTIPMODE_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_MULTIPMODE_REAL;
    d.bitc.rest = data;
    *(volatile U32 *)REG_I2S_MULTIPMODE_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_MultipMode_rest(void)
{
    GH_I2S_MULTIPMODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_MULTIPMODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rest;
}
GH_INLINE void GH_I2S_set_MultipMode_dma(U8 data)
{
    GH_I2S_MULTIPMODE_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_MULTIPMODE_REAL;
    d.bitc.dma = data;
    *(volatile U32 *)REG_I2S_MULTIPMODE_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_MultipMode_dma(void)
{
    GH_I2S_MULTIPMODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_MULTIPMODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dma;
}

/*----------------------------------------------------------------------------*/
/* register I2S_Shift (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_Shift(U32 data)
{
    GH_I2S_SHIFT_REAL_S real;
    GH_I2S_SHIFT_S dummy;
    dummy.all = data ;
    real.bitc.tx = dummy.bitc.tx;
    real.bitc.rx = dummy.bitc.rx;
    *(volatile U32 *)REG_I2S_SHIFT_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_Shift(void)
{
    GH_I2S_SHIFT_REAL_S real;
    GH_I2S_SHIFT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_SHIFT_REAL);

    dummy.bitc.tx = real.bitc.tx;
    dummy.bitc.rx = real.bitc.rx;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_Shift_tx(U8 data)
{
    GH_I2S_SHIFT_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_SHIFT_REAL;
    d.bitc.tx = data;
    *(volatile U32 *)REG_I2S_SHIFT_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_Shift_tx(void)
{
    GH_I2S_SHIFT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_SHIFT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tx;
}
GH_INLINE void GH_I2S_set_Shift_rx(U8 data)
{
    GH_I2S_SHIFT_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_SHIFT_REAL;
    d.bitc.rx = data;
    *(volatile U32 *)REG_I2S_SHIFT_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_Shift_rx(void)
{
    GH_I2S_SHIFT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_SHIFT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rx;
}

/*----------------------------------------------------------------------------*/
/* register I2S_ChanSlect (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_set_ChanSlect(U32 data)
{
    GH_I2S_CHANSLECT_REAL_S real;
    GH_I2S_CHANSLECT_S dummy;
    dummy.all = data ;
    real.bitc.chan = dummy.bitc.chan;
    *(volatile U32 *)REG_I2S_CHANSLECT_REAL = real.all;
}
GH_INLINE U32  GH_I2S_get_ChanSlect(void)
{
    GH_I2S_CHANSLECT_REAL_S real;
    GH_I2S_CHANSLECT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_CHANSLECT_REAL);

    dummy.bitc.chan = real.bitc.chan;
    return dummy.all;
}
GH_INLINE void GH_I2S_set_ChanSlect_chan(U8 data)
{
    GH_I2S_CHANSLECT_REAL_S d;
    d.all = *(volatile U32 *)REG_I2S_CHANSLECT_REAL;
    d.bitc.chan = data;
    *(volatile U32 *)REG_I2S_CHANSLECT_REAL = d.all;
}
GH_INLINE U8   GH_I2S_get_ChanSlect_chan(void)
{
    GH_I2S_CHANSLECT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_CHANSLECT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.chan;
}

/*----------------------------------------------------------------------------*/
/* register I2S_Rx_Dma (read)                                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_I2S_get_Rx_Dma(void)
{
    GH_I2S_RX_DMA_REAL_S real;
    GH_I2S_RX_DMA_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_RX_DMA_REAL);

    dummy.bitc.data = real.bitc.data;
    return dummy.all;
}
GH_INLINE U32  GH_I2S_get_Rx_Dma_data(void)
{
    GH_I2S_RX_DMA_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RX_DMA_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.data;
}

/*----------------------------------------------------------------------------*/
/* register I2S_Tx_Left_Dma (read)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_I2S_get_Tx_Left_Dma(void)
{
    GH_I2S_TX_LEFT_DMA_REAL_S real;
    GH_I2S_TX_LEFT_DMA_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_I2S_TX_LEFT_DMA_REAL);

    dummy.bitc.data = real.bitc.data;
    return dummy.all;
}
GH_INLINE U32  GH_I2S_get_Tx_Left_Dma_data(void)
{
    GH_I2S_TX_LEFT_DMA_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TX_LEFT_DMA_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.data;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_I2S_init(void)
{
    GH_I2S_set_Mode((U32)0x00000004);
    GH_I2S_set_RxContr((U32)0x00000000);
    GH_I2S_set_TxContr((U32)0x00000000);
    GH_I2S_set_WlReg((U32)0x00000000);
    GH_I2S_set_WPREG((U32)0x00000000);
    GH_I2S_set_SlotReg((U32)0x00000000);
    GH_I2S_set_TxFifoLth((U32)0x00000000);
    GH_I2S_set_RxFifoGth((U32)0x0000003f);
    GH_I2S_set_Clock((U32)0x00000080);
    GH_I2S_set_Initreg((U32)0x00000000);
    GH_I2S_set_TxLeftData((U32)0x00000000);
    GH_I2S_set_TxRightData((U32)0x00000000);
    GH_I2S_set_TxInitEnReg((U32)0x00000008);
    GH_I2S_set_RxInitEnReg((U32)0x00000008);
    GH_I2S_set_RxEcho((U32)0x00000000);
    GH_I2S_set_MultipMode((U32)0x00000008);
    GH_I2S_set_Shift((U32)0x00000000);
    GH_I2S_set_ChanSlect((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

