/*!
*******************************************************************************
**
** \file      gh_i2s.h
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
#ifndef _GH_I2S_H
#define _GH_I2S_H

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

#define GH_I2S_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_I2S_DEBUG_PRINT_FUNCTION printk
#else
#define GH_I2S_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_I2S_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_I2S_MODE                                        FIO_ADDRESS(I2S,0x9000A000) /* read/write */
#define REG_I2S_RXCONTR                                     FIO_ADDRESS(I2S,0x9000A004) /* read/write */
#define REG_I2S_TXCONTR                                     FIO_ADDRESS(I2S,0x9000A008) /* read/write */
#define REG_I2S_WLREG                                       FIO_ADDRESS(I2S,0x9000A00C) /* read/write */
#define REG_I2S_WPREG                                       FIO_ADDRESS(I2S,0x9000A010) /* read/write */
#define REG_I2S_SLOTREG                                     FIO_ADDRESS(I2S,0x9000A014) /* read/write */
#define REG_I2S_TXFIFOLTH                                   FIO_ADDRESS(I2S,0x9000A018) /* read/write */
#define REG_I2S_RXFIFOGTH                                   FIO_ADDRESS(I2S,0x9000A01c) /* read/write */
#define REG_I2S_CLOCK                                       FIO_ADDRESS(I2S,0x9000A020) /* read/write */
#define REG_I2S_INITREG                                     FIO_ADDRESS(I2S,0x9000A024) /* read/write */
#define REG_I2S_TXFIFOFLAG                                  FIO_ADDRESS(I2S,0x9000A028) /* read */
#define REG_I2S_TXLEFTDATA                                  FIO_ADDRESS(I2S,0x9000A02c) /* write */
#define REG_I2S_TXRIGHTDATA                                 FIO_ADDRESS(I2S,0x9000A030) /* write */
#define REG_I2S_RXFIFOFLAG                                  FIO_ADDRESS(I2S,0x9000A034) /* read */
#define REG_I2S_RXDATA                                      FIO_ADDRESS(I2S,0x9000A038) /* read */
#define REG_I2S_TXFIFCNTR                                   FIO_ADDRESS(I2S,0x9000A03c) /* read */
#define REG_I2S_RXFIFCNTR                                   FIO_ADDRESS(I2S,0x9000A040) /* read */
#define REG_I2S_TXINITENREG                                 FIO_ADDRESS(I2S,0x9000A044) /* read/write */
#define REG_I2S_RXINITENREG                                 FIO_ADDRESS(I2S,0x9000A048) /* read/write */
#define REG_I2S_RXECHO                                      FIO_ADDRESS(I2S,0x9000A04c) /* read/write */
#define REG_I2S_MULTIPMODE                                  FIO_ADDRESS(I2S,0x9000A050) /* read/write */
#define REG_I2S_SHIFT                                       FIO_ADDRESS(I2S,0x9000A054) /* read/write */
#define REG_I2S_CHANSLECT                                   FIO_ADDRESS(I2S,0x9000A058) /* read/write */
#define REG_I2S_RX_DMA                                      FIO_ADDRESS(I2S,0x9000A080) /* read */
#define REG_I2S_TX_LEFT_DMA                                 FIO_ADDRESS(I2S,0x9000A0C0) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* I2S_Mode */
    U32 all;
    struct {
        U32 mode                        : 3;
        U32                             : 29;
    } bitc;
} GH_I2S_MODE_S;

typedef union { /* I2S_RxContr */
    U32 all;
    struct {
        U32 rwi                         : 1;
        U32 rwm                         : 1;
        U32 order                       : 1;
        U32 loopback                    : 1;
        U32                             : 28;
    } bitc;
} GH_I2S_RXCONTR_S;

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
} GH_I2S_TXCONTR_S;

typedef union { /* I2S_WlReg */
    U32 all;
    struct {
        U32 wlen                        : 5;
        U32                             : 27;
    } bitc;
} GH_I2S_WLREG_S;

typedef union { /* I2S_WPREG */
    U32 all;
    struct {
        U32 ignbit                      : 5;
        U32                             : 27;
    } bitc;
} GH_I2S_WPREG_S;

typedef union { /* I2S_SlotReg */
    U32 all;
    struct {
        U32 slotcont                    : 5;
        U32                             : 27;
    } bitc;
} GH_I2S_SLOTREG_S;

typedef union { /* I2S_TxFifoLth */
    U32 all;
    struct {
        U32 ft                          : 7;
        U32                             : 25;
    } bitc;
} GH_I2S_TXFIFOLTH_S;

typedef union { /* I2S_RxFifoGth */
    U32 all;
    struct {
        U32 ft                          : 7;
        U32                             : 25;
    } bitc;
} GH_I2S_RXFIFOGTH_S;

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
} GH_I2S_CLOCK_S;

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
} GH_I2S_INITREG_S;

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
} GH_I2S_TXFIFOFLAG_S;

typedef union { /* I2S_TxLeftData */
    U32 all;
    struct {
        U32 data                        : 32;
    } bitc;
} GH_I2S_TXLEFTDATA_S;

typedef union { /* I2S_TxRightData */
    U32 all;
    struct {
        U32 data                        : 24;
        U32                             : 8;
    } bitc;
} GH_I2S_TXRIGHTDATA_S;

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
} GH_I2S_RXFIFOFLAG_S;

typedef union { /* I2S_RxData */
    U32 all;
    struct {
        U32 data                        : 24;
        U32                             : 8;
    } bitc;
} GH_I2S_RXDATA_S;

typedef union { /* I2S_TxFifCntr */
    U32 all;
    struct {
        U32 num                         : 7;
        U32                             : 25;
    } bitc;
} GH_I2S_TXFIFCNTR_S;

typedef union { /* I2S_Rxfifcntr */
    U32 all;
    struct {
        U32 num                         : 8;
        U32                             : 24;
    } bitc;
} GH_I2S_RXFIFCNTR_S;

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
} GH_I2S_TXINITENREG_S;

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
} GH_I2S_RXINITENREG_S;

typedef union { /* I2S_RxEcho */
    U32 all;
    struct {
        U32 echo                        : 1;
        U32                             : 31;
    } bitc;
} GH_I2S_RXECHO_S;

typedef union { /* I2S_MultipMode */
    U32 all;
    struct {
        U32 en                          : 1;
        U32 fdmaen                      : 1;
        U32 rest                        : 1;
        U32 dma                         : 1;
        U32                             : 28;
    } bitc;
} GH_I2S_MULTIPMODE_S;

typedef union { /* I2S_Shift */
    U32 all;
    struct {
        U32 tx                          : 1;
        U32 rx                          : 1;
        U32                             : 30;
    } bitc;
} GH_I2S_SHIFT_S;

typedef union { /* I2S_ChanSlect */
    U32 all;
    struct {
        U32 chan                        : 2;
        U32                             : 30;
    } bitc;
} GH_I2S_CHANSLECT_S;

typedef union { /* I2S_Rx_Dma */
    U32 all;
    struct {
        U32 data                        : 24;
        U32                             : 8;
    } bitc;
} GH_I2S_RX_DMA_S;

typedef union { /* I2S_Tx_Left_Dma */
    U32 all;
    struct {
        U32 data                        : 32;
    } bitc;
} GH_I2S_TX_LEFT_DMA_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_I2S_TXLEFTDATA_S                     m_i2s_txleftdata;
extern GH_I2S_TXRIGHTDATA_S                    m_i2s_txrightdata;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register I2S_Mode (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_Mode'. */
void GH_I2S_set_Mode(U32 data);
/*! \brief Reads the register 'I2S_Mode'. */
U32  GH_I2S_get_Mode(void);
/*! \brief Writes the bit group 'MODE' of register 'I2S_Mode'. */
void GH_I2S_set_Mode_MODE(U8 data);
/*! \brief Reads the bit group 'MODE' of register 'I2S_Mode'. */
U8   GH_I2S_get_Mode_MODE(void);

/*----------------------------------------------------------------------------*/
/* register I2S_RxContr (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_RxContr'. */
void GH_I2S_set_RxContr(U32 data);
/*! \brief Reads the register 'I2S_RxContr'. */
U32  GH_I2S_get_RxContr(void);
/*! \brief Writes the bit group 'rwi' of register 'I2S_RxContr'. */
void GH_I2S_set_RxContr_rwi(U8 data);
/*! \brief Reads the bit group 'rwi' of register 'I2S_RxContr'. */
U8   GH_I2S_get_RxContr_rwi(void);
/*! \brief Writes the bit group 'rwm' of register 'I2S_RxContr'. */
void GH_I2S_set_RxContr_rwm(U8 data);
/*! \brief Reads the bit group 'rwm' of register 'I2S_RxContr'. */
U8   GH_I2S_get_RxContr_rwm(void);
/*! \brief Writes the bit group 'order' of register 'I2S_RxContr'. */
void GH_I2S_set_RxContr_order(U8 data);
/*! \brief Reads the bit group 'order' of register 'I2S_RxContr'. */
U8   GH_I2S_get_RxContr_order(void);
/*! \brief Writes the bit group 'loopback' of register 'I2S_RxContr'. */
void GH_I2S_set_RxContr_loopback(U8 data);
/*! \brief Reads the bit group 'loopback' of register 'I2S_RxContr'. */
U8   GH_I2S_get_RxContr_loopback(void);

/*----------------------------------------------------------------------------*/
/* register I2S_TxContr (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_TxContr'. */
void GH_I2S_set_TxContr(U32 data);
/*! \brief Reads the register 'I2S_TxContr'. */
U32  GH_I2S_get_TxContr(void);
/*! \brief Writes the bit group 'momo' of register 'I2S_TxContr'. */
void GH_I2S_set_TxContr_momo(U8 data);
/*! \brief Reads the bit group 'momo' of register 'I2S_TxContr'. */
U8   GH_I2S_get_TxContr_momo(void);
/*! \brief Writes the bit group 'mute' of register 'I2S_TxContr'. */
void GH_I2S_set_TxContr_mute(U8 data);
/*! \brief Reads the bit group 'mute' of register 'I2S_TxContr'. */
U8   GH_I2S_get_TxContr_mute(void);
/*! \brief Writes the bit group 'unison' of register 'I2S_TxContr'. */
void GH_I2S_set_TxContr_unison(U8 data);
/*! \brief Reads the bit group 'unison' of register 'I2S_TxContr'. */
U8   GH_I2S_get_TxContr_unison(void);
/*! \brief Writes the bit group 'twi' of register 'I2S_TxContr'. */
void GH_I2S_set_TxContr_twi(U8 data);
/*! \brief Reads the bit group 'twi' of register 'I2S_TxContr'. */
U8   GH_I2S_get_TxContr_twi(void);
/*! \brief Writes the bit group 'twm' of register 'I2S_TxContr'. */
void GH_I2S_set_TxContr_twm(U8 data);
/*! \brief Reads the bit group 'twm' of register 'I2S_TxContr'. */
U8   GH_I2S_get_TxContr_twm(void);
/*! \brief Writes the bit group 'order' of register 'I2S_TxContr'. */
void GH_I2S_set_TxContr_order(U8 data);
/*! \brief Reads the bit group 'order' of register 'I2S_TxContr'. */
U8   GH_I2S_get_TxContr_order(void);
/*! \brief Writes the bit group 'loopback' of register 'I2S_TxContr'. */
void GH_I2S_set_TxContr_loopback(U8 data);
/*! \brief Reads the bit group 'loopback' of register 'I2S_TxContr'. */
U8   GH_I2S_get_TxContr_loopback(void);

/*----------------------------------------------------------------------------*/
/* register I2S_WlReg (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_WlReg'. */
void GH_I2S_set_WlReg(U32 data);
/*! \brief Reads the register 'I2S_WlReg'. */
U32  GH_I2S_get_WlReg(void);
/*! \brief Writes the bit group 'Wlen' of register 'I2S_WlReg'. */
void GH_I2S_set_WlReg_Wlen(U8 data);
/*! \brief Reads the bit group 'Wlen' of register 'I2S_WlReg'. */
U8   GH_I2S_get_WlReg_Wlen(void);

/*----------------------------------------------------------------------------*/
/* register I2S_WPREG (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_WPREG'. */
void GH_I2S_set_WPREG(U32 data);
/*! \brief Reads the register 'I2S_WPREG'. */
U32  GH_I2S_get_WPREG(void);
/*! \brief Writes the bit group 'Ignbit' of register 'I2S_WPREG'. */
void GH_I2S_set_WPREG_Ignbit(U8 data);
/*! \brief Reads the bit group 'Ignbit' of register 'I2S_WPREG'. */
U8   GH_I2S_get_WPREG_Ignbit(void);

/*----------------------------------------------------------------------------*/
/* register I2S_SlotReg (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_SlotReg'. */
void GH_I2S_set_SlotReg(U32 data);
/*! \brief Reads the register 'I2S_SlotReg'. */
U32  GH_I2S_get_SlotReg(void);
/*! \brief Writes the bit group 'slotcont' of register 'I2S_SlotReg'. */
void GH_I2S_set_SlotReg_slotcont(U8 data);
/*! \brief Reads the bit group 'slotcont' of register 'I2S_SlotReg'. */
U8   GH_I2S_get_SlotReg_slotcont(void);

/*----------------------------------------------------------------------------*/
/* register I2S_TxFifoLth (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_TxFifoLth'. */
void GH_I2S_set_TxFifoLth(U32 data);
/*! \brief Reads the register 'I2S_TxFifoLth'. */
U32  GH_I2S_get_TxFifoLth(void);
/*! \brief Writes the bit group 'ft' of register 'I2S_TxFifoLth'. */
void GH_I2S_set_TxFifoLth_ft(U8 data);
/*! \brief Reads the bit group 'ft' of register 'I2S_TxFifoLth'. */
U8   GH_I2S_get_TxFifoLth_ft(void);

/*----------------------------------------------------------------------------*/
/* register I2S_RxFifoGth (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_RxFifoGth'. */
void GH_I2S_set_RxFifoGth(U32 data);
/*! \brief Reads the register 'I2S_RxFifoGth'. */
U32  GH_I2S_get_RxFifoGth(void);
/*! \brief Writes the bit group 'ft' of register 'I2S_RxFifoGth'. */
void GH_I2S_set_RxFifoGth_ft(U8 data);
/*! \brief Reads the bit group 'ft' of register 'I2S_RxFifoGth'. */
U8   GH_I2S_get_RxFifoGth_ft(void);

/*----------------------------------------------------------------------------*/
/* register I2S_Clock (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_Clock'. */
void GH_I2S_set_Clock(U32 data);
/*! \brief Reads the register 'I2S_Clock'. */
U32  GH_I2S_get_Clock(void);
/*! \brief Writes the bit group 'clk_div' of register 'I2S_Clock'. */
void GH_I2S_set_Clock_clk_div(U8 data);
/*! \brief Reads the bit group 'clk_div' of register 'I2S_Clock'. */
U8   GH_I2S_get_Clock_clk_div(void);
/*! \brief Writes the bit group 'rsp' of register 'I2S_Clock'. */
void GH_I2S_set_Clock_rsp(U8 data);
/*! \brief Reads the bit group 'rsp' of register 'I2S_Clock'. */
U8   GH_I2S_get_Clock_rsp(void);
/*! \brief Writes the bit group 'tsp' of register 'I2S_Clock'. */
void GH_I2S_set_Clock_tsp(U8 data);
/*! \brief Reads the bit group 'tsp' of register 'I2S_Clock'. */
U8   GH_I2S_get_Clock_tsp(void);
/*! \brief Writes the bit group 'ss' of register 'I2S_Clock'. */
void GH_I2S_set_Clock_ss(U8 data);
/*! \brief Reads the bit group 'ss' of register 'I2S_Clock'. */
U8   GH_I2S_get_Clock_ss(void);
/*! \brief Writes the bit group 'soe' of register 'I2S_Clock'. */
void GH_I2S_set_Clock_soe(U8 data);
/*! \brief Reads the bit group 'soe' of register 'I2S_Clock'. */
U8   GH_I2S_get_Clock_soe(void);
/*! \brief Writes the bit group 'woe' of register 'I2S_Clock'. */
void GH_I2S_set_Clock_woe(U8 data);
/*! \brief Reads the bit group 'woe' of register 'I2S_Clock'. */
U8   GH_I2S_get_Clock_woe(void);

/*----------------------------------------------------------------------------*/
/* register I2S_Initreg (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_Initreg'. */
void GH_I2S_set_Initreg(U32 data);
/*! \brief Reads the register 'I2S_Initreg'. */
U32  GH_I2S_get_Initreg(void);
/*! \brief Writes the bit group 'frst' of register 'I2S_Initreg'. */
void GH_I2S_set_Initreg_frst(U8 data);
/*! \brief Reads the bit group 'frst' of register 'I2S_Initreg'. */
U8   GH_I2S_get_Initreg_frst(void);
/*! \brief Writes the bit group 're' of register 'I2S_Initreg'. */
void GH_I2S_set_Initreg_re(U8 data);
/*! \brief Reads the bit group 're' of register 'I2S_Initreg'. */
U8   GH_I2S_get_Initreg_re(void);
/*! \brief Writes the bit group 'te' of register 'I2S_Initreg'. */
void GH_I2S_set_Initreg_te(U8 data);
/*! \brief Reads the bit group 'te' of register 'I2S_Initreg'. */
U8   GH_I2S_get_Initreg_te(void);
/*! \brief Writes the bit group 'rxfrst' of register 'I2S_Initreg'. */
void GH_I2S_set_Initreg_rxfrst(U8 data);
/*! \brief Reads the bit group 'rxfrst' of register 'I2S_Initreg'. */
U8   GH_I2S_get_Initreg_rxfrst(void);
/*! \brief Writes the bit group 'txfrst' of register 'I2S_Initreg'. */
void GH_I2S_set_Initreg_txfrst(U8 data);
/*! \brief Reads the bit group 'txfrst' of register 'I2S_Initreg'. */
U8   GH_I2S_get_Initreg_txfrst(void);

/*----------------------------------------------------------------------------*/
/* register I2S_TxFifoFlag (read)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'I2S_TxFifoFlag'. */
U32  GH_I2S_get_TxFifoFlag(void);
/*! \brief Reads the bit group 'fe' of register 'I2S_TxFifoFlag'. */
U8   GH_I2S_get_TxFifoFlag_fe(void);
/*! \brief Reads the bit group 'ff' of register 'I2S_TxFifoFlag'. */
U8   GH_I2S_get_TxFifoFlag_ff(void);
/*! \brief Reads the bit group 'ftv' of register 'I2S_TxFifoFlag'. */
U8   GH_I2S_get_TxFifoFlag_ftv(void);
/*! \brief Reads the bit group 'ti' of register 'I2S_TxFifoFlag'. */
U8   GH_I2S_get_TxFifoFlag_ti(void);

/*----------------------------------------------------------------------------*/
/* register I2S_TxLeftData (write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_TxLeftData'. */
void GH_I2S_set_TxLeftData(U32 data);
/*! \brief Reads the mirror variable of the register 'I2S_TxLeftData'. */
U32  GH_I2S_getm_TxLeftData(void);
/*! \brief Writes the bit group 'data' of register 'I2S_TxLeftData'. */
void GH_I2S_set_TxLeftData_data(U32 data);
/*! \brief Reads the bit group 'data' from the mirror variable of register 'I2S_TxLeftData'. */
U32  GH_I2S_getm_TxLeftData_data(void);

/*----------------------------------------------------------------------------*/
/* register I2S_TxRightData (write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_TxRightData'. */
void GH_I2S_set_TxRightData(U32 data);
/*! \brief Reads the mirror variable of the register 'I2S_TxRightData'. */
U32  GH_I2S_getm_TxRightData(void);
/*! \brief Writes the bit group 'data' of register 'I2S_TxRightData'. */
void GH_I2S_set_TxRightData_data(U32 data);
/*! \brief Reads the bit group 'data' from the mirror variable of register 'I2S_TxRightData'. */
U32  GH_I2S_getm_TxRightData_data(void);

/*----------------------------------------------------------------------------*/
/* register I2S_RxFifoFlag (read)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'I2S_RxFifoFlag'. */
U32  GH_I2S_get_RxFifoFlag(void);
/*! \brief Reads the bit group 'fe' of register 'I2S_RxFifoFlag'. */
U8   GH_I2S_get_RxFifoFlag_fe(void);
/*! \brief Reads the bit group 'ff' of register 'I2S_RxFifoFlag'. */
U8   GH_I2S_get_RxFifoFlag_ff(void);
/*! \brief Reads the bit group 'fo' of register 'I2S_RxFifoFlag'. */
U8   GH_I2S_get_RxFifoFlag_fo(void);
/*! \brief Reads the bit group 'ftv' of register 'I2S_RxFifoFlag'. */
U8   GH_I2S_get_RxFifoFlag_ftv(void);
/*! \brief Reads the bit group 'ri' of register 'I2S_RxFifoFlag'. */
U8   GH_I2S_get_RxFifoFlag_ri(void);

/*----------------------------------------------------------------------------*/
/* register I2S_RxData (read)                                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'I2S_RxData'. */
U32  GH_I2S_get_RxData(void);
/*! \brief Reads the bit group 'data' of register 'I2S_RxData'. */
U32  GH_I2S_get_RxData_data(void);

/*----------------------------------------------------------------------------*/
/* register I2S_TxFifCntr (read)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'I2S_TxFifCntr'. */
U32  GH_I2S_get_TxFifCntr(void);
/*! \brief Reads the bit group 'num' of register 'I2S_TxFifCntr'. */
U8   GH_I2S_get_TxFifCntr_num(void);

/*----------------------------------------------------------------------------*/
/* register I2S_Rxfifcntr (read)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'I2S_Rxfifcntr'. */
U32  GH_I2S_get_Rxfifcntr(void);
/*! \brief Reads the bit group 'num' of register 'I2S_Rxfifcntr'. */
U8   GH_I2S_get_Rxfifcntr_num(void);

/*----------------------------------------------------------------------------*/
/* register I2S_TxInitEnReg (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_TxInitEnReg'. */
void GH_I2S_set_TxInitEnReg(U32 data);
/*! \brief Reads the register 'I2S_TxInitEnReg'. */
U32  GH_I2S_get_TxInitEnReg(void);
/*! \brief Writes the bit group 'fe' of register 'I2S_TxInitEnReg'. */
void GH_I2S_set_TxInitEnReg_fe(U8 data);
/*! \brief Reads the bit group 'fe' of register 'I2S_TxInitEnReg'. */
U8   GH_I2S_get_TxInitEnReg_fe(void);
/*! \brief Writes the bit group 'ff' of register 'I2S_TxInitEnReg'. */
void GH_I2S_set_TxInitEnReg_ff(U8 data);
/*! \brief Reads the bit group 'ff' of register 'I2S_TxInitEnReg'. */
U8   GH_I2S_get_TxInitEnReg_ff(void);
/*! \brief Writes the bit group 'ftv' of register 'I2S_TxInitEnReg'. */
void GH_I2S_set_TxInitEnReg_ftv(U8 data);
/*! \brief Reads the bit group 'ftv' of register 'I2S_TxInitEnReg'. */
U8   GH_I2S_get_TxInitEnReg_ftv(void);
/*! \brief Writes the bit group 'ti' of register 'I2S_TxInitEnReg'. */
void GH_I2S_set_TxInitEnReg_ti(U8 data);
/*! \brief Reads the bit group 'ti' of register 'I2S_TxInitEnReg'. */
U8   GH_I2S_get_TxInitEnReg_ti(void);

/*----------------------------------------------------------------------------*/
/* register I2S_RxInitEnReg (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_RxInitEnReg'. */
void GH_I2S_set_RxInitEnReg(U32 data);
/*! \brief Reads the register 'I2S_RxInitEnReg'. */
U32  GH_I2S_get_RxInitEnReg(void);
/*! \brief Writes the bit group 'fe' of register 'I2S_RxInitEnReg'. */
void GH_I2S_set_RxInitEnReg_fe(U8 data);
/*! \brief Reads the bit group 'fe' of register 'I2S_RxInitEnReg'. */
U8   GH_I2S_get_RxInitEnReg_fe(void);
/*! \brief Writes the bit group 'ff' of register 'I2S_RxInitEnReg'. */
void GH_I2S_set_RxInitEnReg_ff(U8 data);
/*! \brief Reads the bit group 'ff' of register 'I2S_RxInitEnReg'. */
U8   GH_I2S_get_RxInitEnReg_ff(void);
/*! \brief Writes the bit group 'fo' of register 'I2S_RxInitEnReg'. */
void GH_I2S_set_RxInitEnReg_fo(U8 data);
/*! \brief Reads the bit group 'fo' of register 'I2S_RxInitEnReg'. */
U8   GH_I2S_get_RxInitEnReg_fo(void);
/*! \brief Writes the bit group 'ftv' of register 'I2S_RxInitEnReg'. */
void GH_I2S_set_RxInitEnReg_ftv(U8 data);
/*! \brief Reads the bit group 'ftv' of register 'I2S_RxInitEnReg'. */
U8   GH_I2S_get_RxInitEnReg_ftv(void);
/*! \brief Writes the bit group 'ri' of register 'I2S_RxInitEnReg'. */
void GH_I2S_set_RxInitEnReg_ri(U8 data);
/*! \brief Reads the bit group 'ri' of register 'I2S_RxInitEnReg'. */
U8   GH_I2S_get_RxInitEnReg_ri(void);

/*----------------------------------------------------------------------------*/
/* register I2S_RxEcho (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_RxEcho'. */
void GH_I2S_set_RxEcho(U32 data);
/*! \brief Reads the register 'I2S_RxEcho'. */
U32  GH_I2S_get_RxEcho(void);
/*! \brief Writes the bit group 'echo' of register 'I2S_RxEcho'. */
void GH_I2S_set_RxEcho_echo(U8 data);
/*! \brief Reads the bit group 'echo' of register 'I2S_RxEcho'. */
U8   GH_I2S_get_RxEcho_echo(void);

/*----------------------------------------------------------------------------*/
/* register I2S_MultipMode (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_MultipMode'. */
void GH_I2S_set_MultipMode(U32 data);
/*! \brief Reads the register 'I2S_MultipMode'. */
U32  GH_I2S_get_MultipMode(void);
/*! \brief Writes the bit group 'en' of register 'I2S_MultipMode'. */
void GH_I2S_set_MultipMode_en(U8 data);
/*! \brief Reads the bit group 'en' of register 'I2S_MultipMode'. */
U8   GH_I2S_get_MultipMode_en(void);
/*! \brief Writes the bit group 'fdmaen' of register 'I2S_MultipMode'. */
void GH_I2S_set_MultipMode_fdmaen(U8 data);
/*! \brief Reads the bit group 'fdmaen' of register 'I2S_MultipMode'. */
U8   GH_I2S_get_MultipMode_fdmaen(void);
/*! \brief Writes the bit group 'rest' of register 'I2S_MultipMode'. */
void GH_I2S_set_MultipMode_rest(U8 data);
/*! \brief Reads the bit group 'rest' of register 'I2S_MultipMode'. */
U8   GH_I2S_get_MultipMode_rest(void);
/*! \brief Writes the bit group 'dma' of register 'I2S_MultipMode'. */
void GH_I2S_set_MultipMode_dma(U8 data);
/*! \brief Reads the bit group 'dma' of register 'I2S_MultipMode'. */
U8   GH_I2S_get_MultipMode_dma(void);

/*----------------------------------------------------------------------------*/
/* register I2S_Shift (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_Shift'. */
void GH_I2S_set_Shift(U32 data);
/*! \brief Reads the register 'I2S_Shift'. */
U32  GH_I2S_get_Shift(void);
/*! \brief Writes the bit group 'tx' of register 'I2S_Shift'. */
void GH_I2S_set_Shift_tx(U8 data);
/*! \brief Reads the bit group 'tx' of register 'I2S_Shift'. */
U8   GH_I2S_get_Shift_tx(void);
/*! \brief Writes the bit group 'rx' of register 'I2S_Shift'. */
void GH_I2S_set_Shift_rx(U8 data);
/*! \brief Reads the bit group 'rx' of register 'I2S_Shift'. */
U8   GH_I2S_get_Shift_rx(void);

/*----------------------------------------------------------------------------*/
/* register I2S_ChanSlect (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'I2S_ChanSlect'. */
void GH_I2S_set_ChanSlect(U32 data);
/*! \brief Reads the register 'I2S_ChanSlect'. */
U32  GH_I2S_get_ChanSlect(void);
/*! \brief Writes the bit group 'chan' of register 'I2S_ChanSlect'. */
void GH_I2S_set_ChanSlect_chan(U8 data);
/*! \brief Reads the bit group 'chan' of register 'I2S_ChanSlect'. */
U8   GH_I2S_get_ChanSlect_chan(void);

/*----------------------------------------------------------------------------*/
/* register I2S_Rx_Dma (read)                                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'I2S_Rx_Dma'. */
U32  GH_I2S_get_Rx_Dma(void);
/*! \brief Reads the bit group 'data' of register 'I2S_Rx_Dma'. */
U32  GH_I2S_get_Rx_Dma_data(void);

/*----------------------------------------------------------------------------*/
/* register I2S_Tx_Left_Dma (read)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'I2S_Tx_Left_Dma'. */
U32  GH_I2S_get_Tx_Left_Dma(void);
/*! \brief Reads the bit group 'data' of register 'I2S_Tx_Left_Dma'. */
U32  GH_I2S_get_Tx_Left_Dma_data(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_I2S_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_i2s.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_I2S_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

