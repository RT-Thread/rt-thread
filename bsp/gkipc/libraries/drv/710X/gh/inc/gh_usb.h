/*!
*******************************************************************************
**
** \file      gh_usb.h
**
** \brief     USB.
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
#ifndef _GH_USB_H
#define _GH_USB_H

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

#define GH_USB_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_USB_DEBUG_PRINT_FUNCTION printk
#else
#define GH_USB_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_USB_ENABLE_DEBUG_PRINT
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
#define REG_USB_FADDR                                       FIO_ADDRESS(USB,0x60006000) /* read/write */
#define REG_USB_POWER_R_PERI                                FIO_ADDRESS(USB,0x60006001) /* read */
#define REG_USB_POWER_W_PERI                                FIO_ADDRESS(USB,0x60006001) /* write */
#define REG_USB_POWER_R_HOST                                FIO_ADDRESS(USB,0x60006001) /* read */
#define REG_USB_POWER_W_HOST                                FIO_ADDRESS(USB,0x60006001) /* write */
#define REG_USB_INTRTX                                      FIO_ADDRESS(USB,0x60006002) /* read */
#define REG_USB_INTRRX                                      FIO_ADDRESS(USB,0x60006004) /* read */
#define REG_USB_INTRTXE                                     FIO_ADDRESS(USB,0x60006006) /* read/write */
#define REG_USB_INTRRXE                                     FIO_ADDRESS(USB,0x60006008) /* read/write */
#define REG_USB_INTRUSB                                     FIO_ADDRESS(USB,0x6000600A) /* read */
#define REG_USB_INTRUSBE                                    FIO_ADDRESS(USB,0x6000600B) /* read/write */
#define REG_USB_FRAME                                       FIO_ADDRESS(USB,0x6000600C) /* read */
#define REG_USB_INDEX                                       FIO_ADDRESS(USB,0x6000600E) /* read/write */
#define REG_USB_TESTMODE                                    FIO_ADDRESS(USB,0x6000600F) /* read/write */
#define REG_USB_CSR0L_R_PERI                                FIO_ADDRESS(USB,0x60006012) /* read */
#define REG_USB_CSR0L_W_PERI                                FIO_ADDRESS(USB,0x60006012) /* write */
#define REG_USB_CSR0H_W_PERI                                FIO_ADDRESS(USB,0x60006013) /* write */
#define REG_USB_CSR0L_R_HOST                                FIO_ADDRESS(USB,0x60006012) /* read */
#define REG_USB_CSR0H_R_HOST                                FIO_ADDRESS(USB,0x60006013) /* read */
#define REG_USB_CSR0L_W_HOST                                FIO_ADDRESS(USB,0x60006012) /* write */
#define REG_USB_CSR0H_W_HOST                                FIO_ADDRESS(USB,0x60006013) /* write */
#define REG_USB_COUNT0                                      FIO_ADDRESS(USB,0x60006018) /* read */
#define REG_USB_TYPE0                                       FIO_ADDRESS(USB,0x6000601A) /* read/write */
#define REG_USB_NAKLIMIT0_HOST                              FIO_ADDRESS(USB,0x6000601B) /* read/write */
#define REG_USB_CONFIGDATA                                  FIO_ADDRESS(USB,0x6000601F) /* read */
#define REG_USB_TXMAXP                                      FIO_ADDRESS(USB,0x60006010) /* read/write */
#define REG_USB_TXCSRL_R_PERI                               FIO_ADDRESS(USB,0x60006012) /* read */
#define REG_USB_TXCSRH_R_PERI                               FIO_ADDRESS(USB,0x60006013) /* read */
#define REG_USB_TXCSRL_W_PERI                               FIO_ADDRESS(USB,0x60006012) /* write */
#define REG_USB_TXCSRH_W_PERI                               FIO_ADDRESS(USB,0x60006013) /* write */
#define REG_USB_TXCSRL_R_HOST                               FIO_ADDRESS(USB,0x60006012) /* read */
#define REG_USB_TXCSRH_R_HOST                               FIO_ADDRESS(USB,0x60006013) /* read */
#define REG_USB_TXCSRL_W_HOST                               FIO_ADDRESS(USB,0x60006012) /* write */
#define REG_USB_TXCSRH_W_HOST                               FIO_ADDRESS(USB,0x60006013) /* write */
#define REG_USB_RXMAXP                                      FIO_ADDRESS(USB,0x60006014) /* read/write */
#define REG_USB_RXCSRL_R_PERI                               FIO_ADDRESS(USB,0x60006016) /* read */
#define REG_USB_RXCSRH_R_PERI                               FIO_ADDRESS(USB,0x60006017) /* read */
#define REG_USB_RXCSRL_W_PERI                               FIO_ADDRESS(USB,0x60006016) /* write */
#define REG_USB_RXCSRH_W_PERI                               FIO_ADDRESS(USB,0x60006017) /* write */
#define REG_USB_RXCSRL_R_HOST                               FIO_ADDRESS(USB,0x60006016) /* read */
#define REG_USB_RXCSRH_R_HOST                               FIO_ADDRESS(USB,0x60006017) /* read */
#define REG_USB_RXCSRL_W_HOST                               FIO_ADDRESS(USB,0x60006016) /* write */
#define REG_USB_RXCSRH_W_HOST                               FIO_ADDRESS(USB,0x60006017) /* write */
#define REG_USB_RXCOUNT                                     FIO_ADDRESS(USB,0x60006018) /* read */
#define REG_USB_TXTYPE_HOST                                 FIO_ADDRESS(USB,0x6000610A) /* read/write */
#define REG_USB_TXINTERVAL_HOST                             FIO_ADDRESS(USB,0x6000601B) /* read/write */
#define REG_USB_RXTYPE_HOST                                 FIO_ADDRESS(USB,0x6000601C) /* read/write */
#define REG_USB_RXINTERVAL_HOST                             FIO_ADDRESS(USB,0x6000601D) /* read/write */
#define REG_USB_FIFOSIZE                                    FIO_ADDRESS(USB,0x6000601F) /* read */
#define REG_USB_DEVCTL_R                                    FIO_ADDRESS(USB,0x60006060) /* read */
#define REG_USB_DEVCTL_W                                    FIO_ADDRESS(USB,0x60006060) /* write */
#define REG_USB_MISC                                        FIO_ADDRESS(USB,0x60006061) /* read/write */
#define REG_USB_TXFIFOSZ                                    FIO_ADDRESS(USB,0x60006062) /* read/write */
#define REG_USB_RXFIFOSZ                                    FIO_ADDRESS(USB,0x60006063) /* read/write */
#define REG_USB_TXFIFOADD                                   FIO_ADDRESS(USB,0x60006064) /* read/write */
#define REG_USB_RXFIFOADD                                   FIO_ADDRESS(USB,0x60006066) /* read/write */
#define REG_USB_VSTATUS                                     FIO_ADDRESS(USB,0x60006068) /* read */
#define REG_USB_VCONTROL                                    FIO_ADDRESS(USB,0x60006068) /* write */
#define REG_USB_HWVERS                                      FIO_ADDRESS(USB,0x6000606C) /* read */
#define REG_USB_EPINFO                                      FIO_ADDRESS(USB,0x60006078) /* read */
#define REG_USB_RAMINFO                                     FIO_ADDRESS(USB,0x60006079) /* read */
#define REG_USB_LINKINFO                                    FIO_ADDRESS(USB,0x6000607A) /* read/write */
#define REG_USB_VPLEN                                       FIO_ADDRESS(USB,0x6000607B) /* read/write */
#define REG_USB_HS_EOF1                                     FIO_ADDRESS(USB,0x6000607C) /* read/write */
#define REG_USB_FS_EOF1                                     FIO_ADDRESS(USB,0x6000607D) /* read/write */
#define REG_USB_LS_EOF1                                     FIO_ADDRESS(USB,0x6000607E) /* read/write */
#define REG_USB_SOFT_RST                                    FIO_ADDRESS(USB,0x6000607F) /* read/write */
#define REG_USB_TXFUNCADDR                                  FIO_ADDRESS(USB,0x60006080) /* read/write */
#define REG_USB_TXHUBADDR                                   FIO_ADDRESS(USB,0x60006082) /* read/write */
#define REG_USB_TXHUBPORT                                   FIO_ADDRESS(USB,0x60006083) /* read/write */
#define REG_USB_RXFUNCADDR                                  FIO_ADDRESS(USB,0x60006084) /* read/write */
#define REG_USB_RXHUBADDR                                   FIO_ADDRESS(USB,0x60006086) /* read/write */
#define REG_USB_RXHUBPORT                                   FIO_ADDRESS(USB,0x60006087) /* read/write */
#define REG_USB_DMA_INTR                                    FIO_ADDRESS(USB,0x60006200) /* read/write */
#define REG_USB_DMA_CNTL                                    FIO_ADDRESS(USB,0x60006204) /* read/write */
#define REG_USB_DMA_ADDR                                    FIO_ADDRESS(USB,0x60006208) /* read/write */
#define REG_USB_DMA_COUNT                                   FIO_ADDRESS(USB,0x6000620C) /* read/write */
#define REG_USB_RQPKTCOUNT_HOST                             FIO_ADDRESS(USB,0x60006300) /* read/write */
#define REG_USB_RXDPKTBUFDIS                                FIO_ADDRESS(USB,0x60006340) /* read/write */
#define REG_USB_TXDPKTBUFDIS                                FIO_ADDRESS(USB,0x60006342) /* read/write */
#define REG_USB_C_T_UCH                                     FIO_ADDRESS(USB,0x60006344) /* read/write */
#define REG_USB_C_T_HSRTN                                   FIO_ADDRESS(USB,0x60006346) /* read/write */
#define REG_USB_C_T_HSBT                                    FIO_ADDRESS(USB,0x60006348) /* read/write */
#define REG_USB_LPM_ATTR                                    FIO_ADDRESS(USB,0x60006360) /* read */
#define REG_USB_LPM_CNTRL_PERI                              FIO_ADDRESS(USB,0x60006362) /* read/write */
#define REG_USB_LPM_CNTRL_HOST                              FIO_ADDRESS(USB,0x60006362) /* read/write */
#define REG_USB_LPM_INTREN                                  FIO_ADDRESS(USB,0x60006363) /* read/write */
#define REG_USB_LPM_INTR_PERI                               FIO_ADDRESS(USB,0x60006364) /* read */
#define REG_USB_LPM_INTR_HOST                               FIO_ADDRESS(USB,0x60006364) /* read */
#define REG_USB_LPM_FADDR_HOST                              FIO_ADDRESS(USB,0x60006365) /* read */
#define REG_USB_FIFOS_U32                                   FIO_ADDRESS(USB,0x60006400) /* read/write */  // by yke
#define OFFSET_USB_FIFOS_U32                                0x08
#if 1
#define REG_USB_FIFOS                                       REG_USB_FIFOS_U32            /* read/write */
#define OFFSET_USB_EP_FIFO                                  OFFSET_USB_FIFOS_U32
#else
#define REG_USB_FIFOS                                       FIO_ADDRESS(USB,0x60006020) /* read/write */
#define OFFSET_USB_EP_FIFO                                  0x04
#endif
#define REG_USB_ADDR_FIFO_EP(i)                             FIO_ADDRESS(USB, (REG_USB_FIFOS + OFFSET_USB_EP_FIFO*(i)))

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* USB_FAddr */
    U8 all;
    struct {
        U8 funcaddr                     : 7;
        U8                              : 1;
    } bitc;
} GH_USB_FADDR_S;

typedef union { /* USB_Power_R_PERI */
    U8 all;
    struct {
        U8 enable_suspendm              : 1;
        U8 suspend_mode                 : 1;
        U8 resume                       : 1;
        U8 reset                        : 1;
        U8 hs_mode                      : 1;
        U8 hs_enab                      : 1;
        U8 soft_conn                    : 1;
        U8 iso_update                   : 1;
    } bitc;
} GH_USB_POWER_R_PERI_S;

typedef union { /* USB_Power_W_PERI */
    U8 all;
    struct {
        U8 enable_suspendm              : 1;
        U8                              : 1;
        U8 resume                       : 1;
        U8                              : 2;
        U8 hs_enab                      : 1;
        U8 soft_conn                    : 1;
        U8 iso_update                   : 1;
    } bitc;
} GH_USB_POWER_W_PERI_S;

typedef union { /* USB_Power_R_HOST */
    U8 all;
    struct {
        U8 enable_suspendm              : 1;
        U8                              : 1;
        U8 resume                       : 1;
        U8 reset                        : 1;
        U8 hs_mode                      : 1;
        U8 hs_enab                      : 1;
        U8                              : 2;
    } bitc;
} GH_USB_POWER_R_HOST_S;

typedef union { /* USB_Power_W_HOST */
    U8 all;
    struct {
        U8 enable_suspendm              : 1;
        U8 suspend_mode                 : 1;
        U8 resume                       : 1;
        U8 reset                        : 1;
        U8                              : 1;
        U8 hs_enab                      : 1;
        U8                              : 2;
    } bitc;
} GH_USB_POWER_W_HOST_S;

typedef union { /* USB_IntrTx */
    U16 all;
    struct {
        U16 ep0                         : 1;
        U16 ep1tx                       : 1;
        U16 ep2tx                       : 1;
        U16 ep3tx                       : 1;
        U16 ep4tx                       : 1;
        U16 ep5tx                       : 1;
        U16 ep6tx                       : 1;
        U16 ep7tx                       : 1;
        U16 ep8tx                       : 1;
        U16 ep9tx                       : 1;
        U16 ep10tx                      : 1;
        U16 ep11tx                      : 1;
        U16 ep12tx                      : 1;
        U16 ep13tx                      : 1;
        U16 ep14tx                      : 1;
        U16 ep15tx                      : 1;
    } bitc;
} GH_USB_INTRTX_S;

typedef union { /* USB_IntrRx */
    U16 all;
    struct {
        U16                             : 1;
        U16 ep1rx                       : 1;
        U16 ep2rx                       : 1;
        U16 ep3rx                       : 1;
        U16 ep4rx                       : 1;
        U16 ep5rx                       : 1;
        U16 ep6rx                       : 1;
        U16 ep7rx                       : 1;
        U16 ep8rx                       : 1;
        U16 ep9rx                       : 1;
        U16 ep10rx                      : 1;
        U16 ep11rx                      : 1;
        U16 ep12rx                      : 1;
        U16 ep13rx                      : 1;
        U16 ep14rx                      : 1;
        U16 ep15rx                      : 1;
    } bitc;
} GH_USB_INTRRX_S;

typedef union { /* USB_IntrTxE */
    U16 all;
    struct {
        U16 ep0                         : 1;
        U16 ep1tx                       : 1;
        U16 ep2tx                       : 1;
        U16 ep3tx                       : 1;
        U16 ep4tx                       : 1;
        U16 ep5tx                       : 1;
        U16 ep6tx                       : 1;
        U16 ep7tx                       : 1;
        U16 ep8tx                       : 1;
        U16 ep9tx                       : 1;
        U16 ep10tx                      : 1;
        U16 ep11tx                      : 1;
        U16 ep12tx                      : 1;
        U16 ep13tx                      : 1;
        U16 ep14tx                      : 1;
        U16 ep15tx                      : 1;
    } bitc;
} GH_USB_INTRTXE_S;

typedef union { /* USB_IntrRxE */
    U16 all;
    struct {
        U16                             : 1;
        U16 ep1rx                       : 1;
        U16 ep2rx                       : 1;
        U16 ep3rx                       : 1;
        U16 ep4rx                       : 1;
        U16 ep5rx                       : 1;
        U16 ep6rx                       : 1;
        U16 ep7rx                       : 1;
        U16 ep8rx                       : 1;
        U16 ep9rx                       : 1;
        U16 ep10rx                      : 1;
        U16 ep11rx                      : 1;
        U16 ep12rx                      : 1;
        U16 ep13rx                      : 1;
        U16 ep14rx                      : 1;
        U16 ep15rx                      : 1;
    } bitc;
} GH_USB_INTRRXE_S;

typedef union { /* USB_IntrUSB */
    U8 all;
    struct {
        U8 suspend                      : 1;
        U8 resume                       : 1;
        U8 reset_babble                 : 1;
        U8 sof                          : 1;
        U8 conn                         : 1;
        U8 discon                       : 1;
        U8 sess_req                     : 1;
        U8 vbus_error                   : 1;
    } bitc;
} GH_USB_INTRUSB_S;

typedef union { /* USB_IntrUSBE */
    U8 all;
    struct {
        U8 suspend                      : 1;
        U8 resume                       : 1;
        U8 reset_babble                 : 1;
        U8 sof                          : 1;
        U8 conn                         : 1;
        U8 discon                       : 1;
        U8 sess_req                     : 1;
        U8 vbus_error                   : 1;
    } bitc;
} GH_USB_INTRUSBE_S;

typedef union { /* USB_Frame */
    U16 all;
    struct {
        U16 number                      : 11;
        U16                             : 5;
    } bitc;
} GH_USB_FRAME_S;

typedef union { /* USB_Index */
    U8 all;
    struct {
        U8 selectedendpoint             : 4;
        U8                              : 4;
    } bitc;
} GH_USB_INDEX_S;

typedef union { /* USB_Testmode */
    U8 all;
    struct {
        U8 test_se0_nak                 : 1;
        U8 test_j                       : 1;
        U8 test_k                       : 1;
        U8 test_packet                  : 1;
        U8 force_hs                     : 1;
        U8 force_fs                     : 1;
        U8 fifo_access                  : 1;
        U8 force_host                   : 1;
    } bitc;
} GH_USB_TESTMODE_S;

typedef union { /* USB_CSR0L_R_PERI */
    U8 all;
    struct {
        U8 rxpktrdy                     : 1;
        U8 txpktrdy                     : 1;
        U8 sentstall                    : 1;
        U8                              : 1;
        U8 setupend                     : 1;
        U8                              : 3;
    } bitc;
} GH_USB_CSR0L_R_PERI_S;

typedef union { /* USB_CSR0L_W_PERI */
    U8 all;
    struct {
        U8                              : 1;
        U8 txpktrdy                     : 1;
        U8 sentstall                    : 1;
        U8 dataend                      : 1;
        U8                              : 1;
        U8 sendstall                    : 1;
        U8 servicedrxpktrdy             : 1;
        U8 servicedsetupend             : 1;
    } bitc;
} GH_USB_CSR0L_W_PERI_S;

typedef union { /* USB_CSR0H_W_PERI */
    U8 all;
    struct {
        U8 flushfifo                    : 1;
        U8                              : 7;
    } bitc;
} GH_USB_CSR0H_W_PERI_S;

typedef union { /* USB_CSR0L_R_HOST */
    U8 all;
    struct {
        U8 rxpktrdy                     : 1;
        U8 txpktrdy                     : 1;
        U8 rxstall                      : 1;
        U8 setuppkt                     : 1;
        U8 error                        : 1;
        U8 reqpkt                       : 1;
        U8 statuspkt                    : 1;
        U8 naktimeout                   : 1;
    } bitc;
} GH_USB_CSR0L_R_HOST_S;

typedef union { /* USB_CSR0H_R_HOST */
    U8 all;
    struct {
        U8                              : 1;
        U8 datatoggle                   : 1;
        U8                              : 1;
        U8 disping                      : 1;
        U8                              : 4;
    } bitc;
} GH_USB_CSR0H_R_HOST_S;

typedef union { /* USB_CSR0L_W_HOST */
    U8 all;
    struct {
        U8 rxpktrdy                     : 1;
        U8 txpktrdy                     : 1;
        U8 rxstall                      : 1;
        U8 setuppkt                     : 1;
        U8 error                        : 1;
        U8 reqpkt                       : 1;
        U8 statuspkt                    : 1;
        U8 naktimeout                   : 1;
    } bitc;
} GH_USB_CSR0L_W_HOST_S;

typedef union { /* USB_CSR0H_W_HOST */
    U8 all;
    struct {
        U8 flushfifo                    : 1;
        U8 datatoggle                   : 1;
        U8 datatogglewriteenable        : 1;
        U8 disping                      : 1;
        U8                              : 4;
    } bitc;
} GH_USB_CSR0H_W_HOST_S;

typedef union { /* USB_Count0 */
    U8 all;
    struct {
        U8 endpoint0rxcount             : 8;
    } bitc;
} GH_USB_COUNT0_S;

typedef union { /* USB_Type0 */
    U8 all;
    struct {
        U8                              : 6;
        U8 speed                        : 2;
    } bitc;
} GH_USB_TYPE0_S;

typedef union { /* USB_NAKLimit0_HOST */
    U8 all;
    struct {
        U8 endpoint0naklimit            : 5;
        U8                              : 3;
    } bitc;
} GH_USB_NAKLIMIT0_HOST_S;

typedef union { /* USB_ConfigData */
    U8 all;
    struct {
        U8 utmi_datawidth               : 1;
        U8 softcone                     : 1;
        U8 dynfifo_sizing               : 1;
        U8 hbtxe                        : 1;
        U8 hbrxe                        : 1;
        U8 bigendian                    : 1;
        U8 mptxe                        : 1;
        U8 mprxe                        : 1;
    } bitc;
} GH_USB_CONFIGDATA_S;

typedef union { /* USB_TxMaxP */
    U16 all;
    struct {
        U16 txmaxp                      : 11;
        U16 multiplier                  : 5;
    } bitc;
} GH_USB_TXMAXP_S;

typedef union { /* USB_TXCSRL_R_PERI */
    U8 all;
    struct {
        U8 txpktrdy                     : 1;
        U8 fifonotempty                 : 1;
        U8 underrun                     : 1;
        U8                              : 1;
        U8 sendstall                    : 1;
        U8 sentstall                    : 1;
        U8                              : 1;
        U8 incomptx                     : 1;
    } bitc;
} GH_USB_TXCSRL_R_PERI_S;

typedef union { /* USB_TXCSRH_R_PERI */
    U8 all;
    struct {
        U8                              : 2;
        U8 dmareqmode                   : 1;
        U8 frcdatatog                   : 1;
        U8 dmareqenab                   : 1;
        U8 mode                         : 1;
        U8 iso                          : 1;
        U8 autoset                      : 1;
    } bitc;
} GH_USB_TXCSRH_R_PERI_S;

typedef union { /* USB_TXCSRL_W_PERI */
    U8 all;
    struct {
        U8 txpktrdy                     : 1;
        U8 fifonotempty                 : 1;
        U8 underrun                     : 1;
        U8 flushfifo                    : 1;
        U8 sendstall                    : 1;
        U8 sentstall                    : 1;
        U8 clrdatatog                   : 1;
        U8 incomptx                     : 1;
    } bitc;
} GH_USB_TXCSRL_W_PERI_S;

typedef union { /* USB_TXCSRH_W_PERI */
    U8 all;
    struct {
        U8                              : 2;
        U8 dmareqmode                   : 1;
        U8 frcdatatog                   : 1;
        U8 dmareqenab                   : 1;
        U8 mode                         : 1;
        U8 iso                          : 1;
        U8 autoset                      : 1;
    } bitc;
} GH_USB_TXCSRH_W_PERI_S;

typedef union { /* USB_TXCSRL_R_HOST */
    U8 all;
    struct {
        U8 txpktrdy                     : 1;
        U8 fifonotempty                 : 1;
        U8 error                        : 1;
        U8                              : 1;
        U8 setuppkt                     : 1;
        U8 rxstall                      : 1;
        U8                              : 1;
        U8 incomptx                     : 1;
    } bitc;
} GH_USB_TXCSRL_R_HOST_S;

typedef union { /* USB_TXCSRH_R_HOST */
    U8 all;
    struct {
        U8 datatoggle                   : 1;
        U8                              : 1;
        U8 dmareqmode                   : 1;
        U8 frcdatatog                   : 1;
        U8 dmareqenab                   : 1;
        U8 mode                         : 1;
        U8                              : 1;
        U8 autoset                      : 1;
    } bitc;
} GH_USB_TXCSRH_R_HOST_S;

typedef union { /* USB_TXCSRL_W_HOST */
    U8 all;
    struct {
        U8 txpktrdy                     : 1;
        U8 fifonotempty                 : 1;
        U8 error                        : 1;
        U8 flushfifo                    : 1;
        U8 setuppkt                     : 1;
        U8 rxstall                      : 1;
        U8 clrdatatog                   : 1;
        U8 incomptx                     : 1;
    } bitc;
} GH_USB_TXCSRL_W_HOST_S;

typedef union { /* USB_TXCSRH_W_HOST */
    U8 all;
    struct {
        U8 datatoggle                   : 1;
        U8 datatogglewriteenable        : 1;
        U8 dmareqmode                   : 1;
        U8 frcdatatog                   : 1;
        U8 dmareqenab                   : 1;
        U8 mode                         : 1;
        U8                              : 1;
        U8 autoset                      : 1;
    } bitc;
} GH_USB_TXCSRH_W_HOST_S;

typedef union { /* USB_RxMaxP */
    U16 all;
    struct {
        U16 txmaxp                      : 11;
        U16 multiplier                  : 5;
    } bitc;
} GH_USB_RXMAXP_S;

typedef union { /* USB_RXCSRL_R_PERI */
    U8 all;
    struct {
        U8 rxpktrdy                     : 1;
        U8 fifofull                     : 1;
        U8 overrun                      : 1;
        U8 dataerror                    : 1;
        U8                              : 1;
        U8 sendstall                    : 1;
        U8 sentstall                    : 1;
        U8                              : 1;
    } bitc;
} GH_USB_RXCSRL_R_PERI_S;

typedef union { /* USB_RXCSRH_R_PERI */
    U8 all;
    struct {
        U8 incomprx                     : 1;
        U8                              : 2;
        U8 dmareqmode                   : 1;
        U8 disnyet_piderror             : 1;
        U8 dmareqenab                   : 1;
        U8 iso                          : 1;
        U8 autoclear                    : 1;
    } bitc;
} GH_USB_RXCSRH_R_PERI_S;

typedef union { /* USB_RXCSRL_W_PERI */
    U8 all;
    struct {
        U8 rxpktrdy                     : 1;
        U8                              : 1;
        U8 overrun                      : 1;
        U8                              : 1;
        U8 flushfifo                    : 1;
        U8 sendstall                    : 1;
        U8 sentstall                    : 1;
        U8 clrdatatog                   : 1;
    } bitc;
} GH_USB_RXCSRL_W_PERI_S;

typedef union { /* USB_RXCSRH_W_PERI */
    U8 all;
    struct {
        U8 incomprx                     : 1;
        U8                              : 2;
        U8 dmareqmode                   : 1;
        U8 disnyet_piderror             : 1;
        U8 dmareqenab                   : 1;
        U8 iso                          : 1;
        U8 autoclear                    : 1;
    } bitc;
} GH_USB_RXCSRH_W_PERI_S;

typedef union { /* USB_RXCSRL_R_HOST */
    U8 all;
    struct {
        U8 rxpktrdy                     : 1;
        U8 fifofull                     : 1;
        U8 error                        : 1;
        U8 dataerror_naktimeout         : 1;
        U8                              : 1;
        U8 reqpkt                       : 1;
        U8 rxstall                      : 1;
        U8                              : 1;
    } bitc;
} GH_USB_RXCSRL_R_HOST_S;

typedef union { /* USB_RXCSRH_R_HOST */
    U8 all;
    struct {
        U8 incomprx                     : 1;
        U8 datatoggle                   : 1;
        U8 datatogglewriteenable        : 1;
        U8 dmareqmode                   : 1;
        U8 piderror                     : 1;
        U8 dmareqenab                   : 1;
        U8 autoreq                      : 1;
        U8 autoclear                    : 1;
    } bitc;
} GH_USB_RXCSRH_R_HOST_S;

typedef union { /* USB_RXCSRL_W_HOST */
    U8 all;
    struct {
        U8 rxpktrdy                     : 1;
        U8                              : 1;
        U8 error                        : 1;
        U8 dataerror_naktimeout         : 1;
        U8 flushfifo                    : 1;
        U8 reqpkt                       : 1;
        U8 rxstall                      : 1;
        U8 clrdatatog                   : 1;
    } bitc;
} GH_USB_RXCSRL_W_HOST_S;

typedef union { /* USB_RXCSRH_W_HOST */
    U8 all;
    struct {
        U8 incomprx                     : 1;
        U8                              : 2;
        U8 dmareqmode                   : 1;
        U8                              : 1;
        U8 dmareqenab                   : 1;
        U8 autoreq                      : 1;
        U8 autoclear                    : 1;
    } bitc;
} GH_USB_RXCSRH_W_HOST_S;

typedef union { /* USB_RxCount */
    U8 all;
    struct {
        U8 endpointrxcount              : 8;
    } bitc;
} GH_USB_RXCOUNT_S;

typedef union { /* USB_TxType_HOST */
    U8 all;
    struct {
        U8 targetendpointnumber         : 4;
        U8 protocol                     : 2;
        U8 speed                        : 2;
    } bitc;
} GH_USB_TXTYPE_HOST_S;

typedef union { /* USB_TxInterval_HOST */
    U8 all;
    struct {
        U8 txpollinginterval_naklimit   : 8;
    } bitc;
} GH_USB_TXINTERVAL_HOST_S;

typedef union { /* USB_RxType_HOST */
    U8 all;
    struct {
        U8 targetendpointnumber         : 4;
        U8 protocol                     : 2;
        U8 speed                        : 2;
    } bitc;
} GH_USB_RXTYPE_HOST_S;

typedef union { /* USB_RxInterval_HOST */
    U8 all;
    struct {
        U8 rxpollinginterval_naklimit   : 8;
    } bitc;
} GH_USB_RXINTERVAL_HOST_S;

typedef union { /* USB_FIFOSize */
    U8 all;
    struct {
        U8 txfifosize                   : 4;
        U8 rxfifosize                   : 4;
    } bitc;
} GH_USB_FIFOSIZE_S;

typedef union { /* USB_DevCtl_R */
    U8 all;
    struct {
        U8 session                      : 1;
        U8 host_req                     : 1;
        U8 host_mode                    : 1;
        U8 vbus                         : 2;
        U8 lsdev                        : 1;
        U8 fsdev                        : 1;
        U8 b_device                     : 1;
    } bitc;
} GH_USB_DEVCTL_R_S;

typedef union { /* USB_DevCtl_W */
    U8 all;
    struct {
        U8 session                      : 1;
        U8 host_req                     : 1;
        U8                              : 6;
    } bitc;
} GH_USB_DEVCTL_W_S;

typedef union { /* USB_Misc */
    U8 all;
    struct {
        U8 rx_edma                      : 1;
        U8 tx_edma                      : 1;
        U8                              : 6;
    } bitc;
} GH_USB_MISC_S;

typedef union { /* USB_TxFIFOsz */
    U8 all;
    struct {
        U8 sz                           : 4;
        U8 dpb                          : 1;
        U8                              : 3;
    } bitc;
} GH_USB_TXFIFOSZ_S;

typedef union { /* USB_RxFIFOsz */
    U8 all;
    struct {
        U8 sz                           : 4;
        U8 dpb                          : 1;
        U8                              : 3;
    } bitc;
} GH_USB_RXFIFOSZ_S;

typedef union { /* USB_TxFIFOadd */
    U16 all;
    struct {
        U16 startaddress                : 13;
        U16                             : 3;
    } bitc;
} GH_USB_TXFIFOADD_S;

typedef union { /* USB_RxFIFOadd */
    U16 all;
    struct {
        U16 startaddress                : 13;
        U16                             : 3;
    } bitc;
} GH_USB_RXFIFOADD_S;

typedef union { /* USB_HWVers */
    U16 all;
    struct {
        U16 minorversion                : 10;
        U16 majorversion                : 5;
        U16 rc                          : 1;
    } bitc;
} GH_USB_HWVERS_S;

typedef union { /* USB_EPInfo */
    U8 all;
    struct {
        U8 txendpoints                  : 4;
        U8 rxendpoints                  : 4;
    } bitc;
} GH_USB_EPINFO_S;

typedef union { /* USB_RAMInfo */
    U8 all;
    struct {
        U8 rambits                      : 4;
        U8 dmachans                     : 4;
    } bitc;
} GH_USB_RAMINFO_S;

typedef union { /* USB_LinkInfo */
    U8 all;
    struct {
        U8 wtid                         : 4;
        U8 wtcon                        : 4;
    } bitc;
} GH_USB_LINKINFO_S;

typedef union { /* USB_SOFT_RST */
    U8 all;
    struct {
        U8 nrst                         : 1;
        U8 nrstx                        : 1;
        U8                              : 6;
    } bitc;
} GH_USB_SOFT_RST_S;

typedef union { /* USB_TxFuncAddr */
    U8 all;
    struct {
        U8 addressoftargetfunction      : 7;
        U8                              : 1;
    } bitc;
} GH_USB_TXFUNCADDR_S;

typedef union { /* USB_TxHubAddr */
    U8 all;
    struct {
        U8 hubaddress                   : 7;
        U8 multipletranslators          : 1;
    } bitc;
} GH_USB_TXHUBADDR_S;

typedef union { /* USB_TxHubPort */
    U8 all;
    struct {
        U8 hubport                      : 7;
        U8                              : 1;
    } bitc;
} GH_USB_TXHUBPORT_S;

typedef union { /* USB_RxFuncAddr */
    U8 all;
    struct {
        U8 addressoftargetfunction      : 7;
        U8                              : 1;
    } bitc;
} GH_USB_RXFUNCADDR_S;

typedef union { /* USB_RxHubAddr */
    U8 all;
    struct {
        U8 hubaddress                   : 7;
        U8 multipletranslators          : 1;
    } bitc;
} GH_USB_RXHUBADDR_S;

typedef union { /* USB_RxHubPort */
    U8 all;
    struct {
        U8 hubport                      : 7;
        U8                              : 1;
    } bitc;
} GH_USB_RXHUBPORT_S;

typedef union { /* USB_DMA_INTR */
    U8 all;
    struct {
        U8 ch0                          : 1;
        U8 ch1                          : 1;
        U8 ch2                          : 1;
        U8 ch3                          : 1;
        U8 ch4                          : 1;
        U8 ch5                          : 1;
        U8 ch6                          : 1;
        U8 ch7                          : 1;
    } bitc;
} GH_USB_DMA_INTR_S;

typedef union { /* USB_DMA_CNTL */
    U16 all;
    struct {
        U16 dma_enab                    : 1;
        U16 dma_dir                     : 1;
        U16 dmamode                     : 1;
        U16 dmaie                       : 1;
        U16 dmaep                       : 4;
        U16 dma_err                     : 1;
        U16 dma_brstm                   : 2;
        U16                             : 5;
    } bitc;
} GH_USB_DMA_CNTL_S;

typedef union { /* USB_RxDPktBufDis */
    U16 all;
    struct {
        U16                             : 1;
        U16 ep1                         : 1;
        U16 ep2                         : 1;
        U16 ep3                         : 1;
        U16 ep4                         : 1;
        U16 ep5                         : 1;
        U16 ep6                         : 1;
        U16 ep7                         : 1;
        U16 ep8                         : 1;
        U16 ep9                         : 1;
        U16 ep10                        : 1;
        U16 ep11                        : 1;
        U16 ep12                        : 1;
        U16 ep13                        : 1;
        U16 ep14                        : 1;
        U16 ep15                        : 1;
    } bitc;
} GH_USB_RXDPKTBUFDIS_S;

typedef union { /* USB_TxDPktBufDis */
    U16 all;
    struct {
        U16                             : 1;
        U16 ep1                         : 1;
        U16 ep2                         : 1;
        U16 ep3                         : 1;
        U16 ep4                         : 1;
        U16 ep5                         : 1;
        U16 ep6                         : 1;
        U16 ep7                         : 1;
        U16 ep8                         : 1;
        U16 ep9                         : 1;
        U16 ep10                        : 1;
        U16 ep11                        : 1;
        U16 ep12                        : 1;
        U16 ep13                        : 1;
        U16 ep14                        : 1;
        U16 ep15                        : 1;
    } bitc;
} GH_USB_TXDPKTBUFDIS_S;

typedef union { /* USB_C_T_HSBT */
    U8 all;
    struct {
        U8 hstimeoutadder               : 4;
        U8                              : 4;
    } bitc;
} GH_USB_C_T_HSBT_S;

typedef union { /* USB_LPM_ATTR */
    U16 all;
    struct {
        U16 linkstate                   : 4;
        U16 hird                        : 4;
        U16 rmtwak                      : 1;
        U16                             : 3;
        U16 endpnt                      : 4;
    } bitc;
} GH_USB_LPM_ATTR_S;

typedef union { /* USB_LPM_CNTRL_PERI */
    U8 all;
    struct {
        U8 lpmxmt                       : 1;
        U8 lpmres                       : 1;
        U8 lpmen                        : 2;
        U8 lpmnak                       : 1;
        U8                              : 3;
    } bitc;
} GH_USB_LPM_CNTRL_PERI_S;

typedef union { /* USB_LPM_CNTRL_HOST */
    U8 all;
    struct {
        U8 lpmxmt                       : 1;
        U8 lpmres                       : 1;
        U8                              : 6;
    } bitc;
} GH_USB_LPM_CNTRL_HOST_S;

typedef union { /* USB_LPM_INTREN */
    U8 all;
    struct {
        U8 lpmsten                      : 1;
        U8 lpmnyen                      : 1;
        U8 lpmacken                     : 1;
        U8 lpmncen                      : 1;
        U8 lpmresen                     : 1;
        U8 lpmerren                     : 1;
        U8                              : 2;
    } bitc;
} GH_USB_LPM_INTREN_S;

typedef union { /* USB_LPM_INTR_PERI */
    U8 all;
    struct {
        U8 lpmst                        : 1;
        U8 lpmny                        : 1;
        U8 lpmack                       : 1;
        U8 lpmnc                        : 1;
        U8 lpmres                       : 1;
        U8 lpmerr                       : 1;
        U8                              : 2;
    } bitc;
} GH_USB_LPM_INTR_PERI_S;

typedef union { /* USB_LPM_INTR_HOST */
    U8 all;
    struct {
        U8 lpmst                        : 1;
        U8 lpmny                        : 1;
        U8 lpmack                       : 1;
        U8 lpmnc                        : 1;
        U8 lpmres                       : 1;
        U8 lpmerr                       : 1;
        U8                              : 2;
    } bitc;
} GH_USB_LPM_INTR_HOST_S;

typedef union { /* USB_LPM_FADDR_HOST */
    U8 all;
    struct {
        U8 lpmfaddr                     : 7;
        U8                              : 1;
    } bitc;
} GH_USB_LPM_FADDR_HOST_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_USB_POWER_W_PERI_S                   m_usb_power_w_peri;
extern GH_USB_POWER_W_HOST_S                   m_usb_power_w_host;
extern GH_USB_CSR0L_W_PERI_S                   m_usb_csr0l_w_peri;
extern GH_USB_CSR0H_W_PERI_S                   m_usb_csr0h_w_peri;
extern GH_USB_CSR0L_W_HOST_S                   m_usb_csr0l_w_host;
extern GH_USB_CSR0H_W_HOST_S                   m_usb_csr0h_w_host;
extern GH_USB_TXCSRL_W_PERI_S                  m_usb_txcsrl_w_peri;
extern GH_USB_TXCSRH_W_PERI_S                  m_usb_txcsrh_w_peri;
extern GH_USB_TXCSRL_W_HOST_S                  m_usb_txcsrl_w_host;
extern GH_USB_TXCSRH_W_HOST_S                  m_usb_txcsrh_w_host;
extern GH_USB_RXCSRL_W_PERI_S                  m_usb_rxcsrl_w_peri;
extern GH_USB_RXCSRH_W_PERI_S                  m_usb_rxcsrh_w_peri;
extern GH_USB_RXCSRL_W_HOST_S                  m_usb_rxcsrl_w_host;
extern GH_USB_RXCSRH_W_HOST_S                  m_usb_rxcsrh_w_host;
extern GH_USB_DEVCTL_W_S                       m_usb_devctl_w;
extern U32                                     m_usb_vcontrol;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register USB_FAddr (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_FAddr'. */
void GH_USB_set_FAddr(U8 data);
/*! \brief Reads the register 'USB_FAddr'. */
U8   GH_USB_get_FAddr(void);
/*! \brief Writes the bit group 'FuncAddr' of register 'USB_FAddr'. */
void GH_USB_set_FAddr_FuncAddr(U8 data);
/*! \brief Reads the bit group 'FuncAddr' of register 'USB_FAddr'. */
U8   GH_USB_get_FAddr_FuncAddr(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_FAddr(U8 data)
{
    *(volatile U8 *)REG_USB_FADDR = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_FAddr] <-- 0x%08x\n",
                        REG_USB_FADDR,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_FAddr(void)
{
    U8 value = (*(volatile U8 *)REG_USB_FADDR);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FAddr] --> 0x%08x\n",
                        REG_USB_FADDR,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_FAddr_FuncAddr(U8 data)
{
    GH_USB_FADDR_S d;
    d.all = *(volatile U8 *)REG_USB_FADDR;
    d.bitc.funcaddr = data;
    *(volatile U8 *)REG_USB_FADDR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_FAddr_FuncAddr] <-- 0x%08x\n",
                        REG_USB_FADDR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_FAddr_FuncAddr(void)
{
    GH_USB_FADDR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_FADDR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FAddr_FuncAddr] --> 0x%08x\n",
                        REG_USB_FADDR,value);
    #endif
    return tmp_value.bitc.funcaddr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_Power_R_PERI (read)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_Power_R_PERI'. */
U8   GH_USB_get_Power_R_PERI(void);
/*! \brief Reads the bit group 'Enable_SuspendM' of register 'USB_Power_R_PERI'. */
U8   GH_USB_get_Power_R_PERI_Enable_SuspendM(void);
/*! \brief Reads the bit group 'Suspend_Mode' of register 'USB_Power_R_PERI'. */
U8   GH_USB_get_Power_R_PERI_Suspend_Mode(void);
/*! \brief Reads the bit group 'Resume' of register 'USB_Power_R_PERI'. */
U8   GH_USB_get_Power_R_PERI_Resume(void);
/*! \brief Reads the bit group 'Reset' of register 'USB_Power_R_PERI'. */
U8   GH_USB_get_Power_R_PERI_Reset(void);
/*! \brief Reads the bit group 'HS_Mode' of register 'USB_Power_R_PERI'. */
U8   GH_USB_get_Power_R_PERI_HS_Mode(void);
/*! \brief Reads the bit group 'HS_Enab' of register 'USB_Power_R_PERI'. */
U8   GH_USB_get_Power_R_PERI_HS_Enab(void);
/*! \brief Reads the bit group 'Soft_Conn' of register 'USB_Power_R_PERI'. */
U8   GH_USB_get_Power_R_PERI_Soft_Conn(void);
/*! \brief Reads the bit group 'ISO_Update' of register 'USB_Power_R_PERI'. */
U8   GH_USB_get_Power_R_PERI_ISO_Update(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_Power_R_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_Power_R_PERI_Enable_SuspendM(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_Enable_SuspendM] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.enable_suspendm;
}
GH_INLINE U8   GH_USB_get_Power_R_PERI_Suspend_Mode(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_Suspend_Mode] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.suspend_mode;
}
GH_INLINE U8   GH_USB_get_Power_R_PERI_Resume(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_Resume] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.resume;
}
GH_INLINE U8   GH_USB_get_Power_R_PERI_Reset(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_Reset] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.reset;
}
GH_INLINE U8   GH_USB_get_Power_R_PERI_HS_Mode(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_HS_Mode] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.hs_mode;
}
GH_INLINE U8   GH_USB_get_Power_R_PERI_HS_Enab(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_HS_Enab] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.hs_enab;
}
GH_INLINE U8   GH_USB_get_Power_R_PERI_Soft_Conn(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_Soft_Conn] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.soft_conn;
}
GH_INLINE U8   GH_USB_get_Power_R_PERI_ISO_Update(void)
{
    GH_USB_POWER_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_PERI_ISO_Update] --> 0x%08x\n",
                        REG_USB_POWER_R_PERI,value);
    #endif
    return tmp_value.bitc.iso_update;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_Power_W_PERI (write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_Power_W_PERI'. */
void GH_USB_set_Power_W_PERI(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_Power_W_PERI'. */
U8   GH_USB_getm_Power_W_PERI(void);
/*! \brief Writes the bit group 'Enable_SuspendM' of register 'USB_Power_W_PERI'. */
void GH_USB_set_Power_W_PERI_Enable_SuspendM(U8 data);
/*! \brief Reads the bit group 'Enable_SuspendM' from the mirror variable of register 'USB_Power_W_PERI'. */
U8   GH_USB_getm_Power_W_PERI_Enable_SuspendM(void);
/*! \brief Writes the bit group 'Resume' of register 'USB_Power_W_PERI'. */
void GH_USB_set_Power_W_PERI_Resume(U8 data);
/*! \brief Reads the bit group 'Resume' from the mirror variable of register 'USB_Power_W_PERI'. */
U8   GH_USB_getm_Power_W_PERI_Resume(void);
/*! \brief Writes the bit group 'HS_Enab' of register 'USB_Power_W_PERI'. */
void GH_USB_set_Power_W_PERI_HS_Enab(U8 data);
/*! \brief Reads the bit group 'HS_Enab' from the mirror variable of register 'USB_Power_W_PERI'. */
U8   GH_USB_getm_Power_W_PERI_HS_Enab(void);
/*! \brief Writes the bit group 'Soft_Conn' of register 'USB_Power_W_PERI'. */
void GH_USB_set_Power_W_PERI_Soft_Conn(U8 data);
/*! \brief Reads the bit group 'Soft_Conn' from the mirror variable of register 'USB_Power_W_PERI'. */
U8   GH_USB_getm_Power_W_PERI_Soft_Conn(void);
/*! \brief Writes the bit group 'ISO_Update' of register 'USB_Power_W_PERI'. */
void GH_USB_set_Power_W_PERI_ISO_Update(U8 data);
/*! \brief Reads the bit group 'ISO_Update' from the mirror variable of register 'USB_Power_W_PERI'. */
U8   GH_USB_getm_Power_W_PERI_ISO_Update(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_Power_W_PERI(U8 data)
{
    m_usb_power_w_peri.all = data;
    *(volatile U8 *)REG_USB_POWER_W_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_PERI] <-- 0x%08x\n",
                        REG_USB_POWER_W_PERI,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_Power_W_PERI(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_PERI] --> 0x%08x\n",
                        m_usb_power_w_peri.all);
    #endif
    return m_usb_power_w_peri.all;
}
GH_INLINE void GH_USB_set_Power_W_PERI_Enable_SuspendM(U8 data)
{
    m_usb_power_w_peri.bitc.enable_suspendm = data;
    *(volatile U8 *)REG_USB_POWER_W_PERI = m_usb_power_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_PERI_Enable_SuspendM] <-- 0x%08x\n",
                        REG_USB_POWER_W_PERI,m_usb_power_w_peri.all,m_usb_power_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_Power_W_PERI_Enable_SuspendM(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_PERI_Enable_SuspendM] --> 0x%08x\n",
                        m_usb_power_w_peri.bitc.enable_suspendm);
    #endif
    return m_usb_power_w_peri.bitc.enable_suspendm;
}
GH_INLINE void GH_USB_set_Power_W_PERI_Resume(U8 data)
{
    m_usb_power_w_peri.bitc.resume = data;
    *(volatile U8 *)REG_USB_POWER_W_PERI = m_usb_power_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_PERI_Resume] <-- 0x%08x\n",
                        REG_USB_POWER_W_PERI,m_usb_power_w_peri.all,m_usb_power_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_Power_W_PERI_Resume(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_PERI_Resume] --> 0x%08x\n",
                        m_usb_power_w_peri.bitc.resume);
    #endif
    return m_usb_power_w_peri.bitc.resume;
}
GH_INLINE void GH_USB_set_Power_W_PERI_HS_Enab(U8 data)
{
    m_usb_power_w_peri.bitc.hs_enab = data;
    *(volatile U8 *)REG_USB_POWER_W_PERI = m_usb_power_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_PERI_HS_Enab] <-- 0x%08x\n",
                        REG_USB_POWER_W_PERI,m_usb_power_w_peri.all,m_usb_power_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_Power_W_PERI_HS_Enab(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_PERI_HS_Enab] --> 0x%08x\n",
                        m_usb_power_w_peri.bitc.hs_enab);
    #endif
    return m_usb_power_w_peri.bitc.hs_enab;
}
GH_INLINE void GH_USB_set_Power_W_PERI_Soft_Conn(U8 data)
{
    m_usb_power_w_peri.bitc.soft_conn = data;
    *(volatile U8 *)REG_USB_POWER_W_PERI = m_usb_power_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_PERI_Soft_Conn] <-- 0x%08x\n",
                        REG_USB_POWER_W_PERI,m_usb_power_w_peri.all,m_usb_power_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_Power_W_PERI_Soft_Conn(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_PERI_Soft_Conn] --> 0x%08x\n",
                        m_usb_power_w_peri.bitc.soft_conn);
    #endif
    return m_usb_power_w_peri.bitc.soft_conn;
}
GH_INLINE void GH_USB_set_Power_W_PERI_ISO_Update(U8 data)
{
    m_usb_power_w_peri.bitc.iso_update = data;
    *(volatile U8 *)REG_USB_POWER_W_PERI = m_usb_power_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_PERI_ISO_Update] <-- 0x%08x\n",
                        REG_USB_POWER_W_PERI,m_usb_power_w_peri.all,m_usb_power_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_Power_W_PERI_ISO_Update(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_PERI_ISO_Update] --> 0x%08x\n",
                        m_usb_power_w_peri.bitc.iso_update);
    #endif
    return m_usb_power_w_peri.bitc.iso_update;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_Power_R_HOST (read)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_Power_R_HOST'. */
U8   GH_USB_get_Power_R_HOST(void);
/*! \brief Reads the bit group 'Enable_SuspendM' of register 'USB_Power_R_HOST'. */
U8   GH_USB_get_Power_R_HOST_Enable_SuspendM(void);
/*! \brief Reads the bit group 'Resume' of register 'USB_Power_R_HOST'. */
U8   GH_USB_get_Power_R_HOST_Resume(void);
/*! \brief Reads the bit group 'Reset' of register 'USB_Power_R_HOST'. */
U8   GH_USB_get_Power_R_HOST_Reset(void);
/*! \brief Reads the bit group 'HS_Mode' of register 'USB_Power_R_HOST'. */
U8   GH_USB_get_Power_R_HOST_HS_Mode(void);
/*! \brief Reads the bit group 'HS_Enab' of register 'USB_Power_R_HOST'. */
U8   GH_USB_get_Power_R_HOST_HS_Enab(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_Power_R_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_HOST] --> 0x%08x\n",
                        REG_USB_POWER_R_HOST,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_Power_R_HOST_Enable_SuspendM(void)
{
    GH_USB_POWER_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_HOST_Enable_SuspendM] --> 0x%08x\n",
                        REG_USB_POWER_R_HOST,value);
    #endif
    return tmp_value.bitc.enable_suspendm;
}
GH_INLINE U8   GH_USB_get_Power_R_HOST_Resume(void)
{
    GH_USB_POWER_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_HOST_Resume] --> 0x%08x\n",
                        REG_USB_POWER_R_HOST,value);
    #endif
    return tmp_value.bitc.resume;
}
GH_INLINE U8   GH_USB_get_Power_R_HOST_Reset(void)
{
    GH_USB_POWER_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_HOST_Reset] --> 0x%08x\n",
                        REG_USB_POWER_R_HOST,value);
    #endif
    return tmp_value.bitc.reset;
}
GH_INLINE U8   GH_USB_get_Power_R_HOST_HS_Mode(void)
{
    GH_USB_POWER_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_HOST_HS_Mode] --> 0x%08x\n",
                        REG_USB_POWER_R_HOST,value);
    #endif
    return tmp_value.bitc.hs_mode;
}
GH_INLINE U8   GH_USB_get_Power_R_HOST_HS_Enab(void)
{
    GH_USB_POWER_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_POWER_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Power_R_HOST_HS_Enab] --> 0x%08x\n",
                        REG_USB_POWER_R_HOST,value);
    #endif
    return tmp_value.bitc.hs_enab;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_Power_W_HOST (write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_Power_W_HOST'. */
void GH_USB_set_Power_W_HOST(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_Power_W_HOST'. */
U8   GH_USB_getm_Power_W_HOST(void);
/*! \brief Writes the bit group 'Enable_SuspendM' of register 'USB_Power_W_HOST'. */
void GH_USB_set_Power_W_HOST_Enable_SuspendM(U8 data);
/*! \brief Reads the bit group 'Enable_SuspendM' from the mirror variable of register 'USB_Power_W_HOST'. */
U8   GH_USB_getm_Power_W_HOST_Enable_SuspendM(void);
/*! \brief Writes the bit group 'Suspend_Mode' of register 'USB_Power_W_HOST'. */
void GH_USB_set_Power_W_HOST_Suspend_Mode(U8 data);
/*! \brief Reads the bit group 'Suspend_Mode' from the mirror variable of register 'USB_Power_W_HOST'. */
U8   GH_USB_getm_Power_W_HOST_Suspend_Mode(void);
/*! \brief Writes the bit group 'Resume' of register 'USB_Power_W_HOST'. */
void GH_USB_set_Power_W_HOST_Resume(U8 data);
/*! \brief Reads the bit group 'Resume' from the mirror variable of register 'USB_Power_W_HOST'. */
U8   GH_USB_getm_Power_W_HOST_Resume(void);
/*! \brief Writes the bit group 'Reset' of register 'USB_Power_W_HOST'. */
void GH_USB_set_Power_W_HOST_Reset(U8 data);
/*! \brief Reads the bit group 'Reset' from the mirror variable of register 'USB_Power_W_HOST'. */
U8   GH_USB_getm_Power_W_HOST_Reset(void);
/*! \brief Writes the bit group 'HS_Enab' of register 'USB_Power_W_HOST'. */
void GH_USB_set_Power_W_HOST_HS_Enab(U8 data);
/*! \brief Reads the bit group 'HS_Enab' from the mirror variable of register 'USB_Power_W_HOST'. */
U8   GH_USB_getm_Power_W_HOST_HS_Enab(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_Power_W_HOST(U8 data)
{
    m_usb_power_w_host.all = data;
    *(volatile U8 *)REG_USB_POWER_W_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_HOST] <-- 0x%08x\n",
                        REG_USB_POWER_W_HOST,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_Power_W_HOST(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_HOST] --> 0x%08x\n",
                        m_usb_power_w_host.all);
    #endif
    return m_usb_power_w_host.all;
}
GH_INLINE void GH_USB_set_Power_W_HOST_Enable_SuspendM(U8 data)
{
    m_usb_power_w_host.bitc.enable_suspendm = data;
    *(volatile U8 *)REG_USB_POWER_W_HOST = m_usb_power_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_HOST_Enable_SuspendM] <-- 0x%08x\n",
                        REG_USB_POWER_W_HOST,m_usb_power_w_host.all,m_usb_power_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_Power_W_HOST_Enable_SuspendM(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_HOST_Enable_SuspendM] --> 0x%08x\n",
                        m_usb_power_w_host.bitc.enable_suspendm);
    #endif
    return m_usb_power_w_host.bitc.enable_suspendm;
}
GH_INLINE void GH_USB_set_Power_W_HOST_Suspend_Mode(U8 data)
{
    m_usb_power_w_host.bitc.suspend_mode = data;
    *(volatile U8 *)REG_USB_POWER_W_HOST = m_usb_power_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_HOST_Suspend_Mode] <-- 0x%08x\n",
                        REG_USB_POWER_W_HOST,m_usb_power_w_host.all,m_usb_power_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_Power_W_HOST_Suspend_Mode(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_HOST_Suspend_Mode] --> 0x%08x\n",
                        m_usb_power_w_host.bitc.suspend_mode);
    #endif
    return m_usb_power_w_host.bitc.suspend_mode;
}
GH_INLINE void GH_USB_set_Power_W_HOST_Resume(U8 data)
{
    m_usb_power_w_host.bitc.resume = data;
    *(volatile U8 *)REG_USB_POWER_W_HOST = m_usb_power_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_HOST_Resume] <-- 0x%08x\n",
                        REG_USB_POWER_W_HOST,m_usb_power_w_host.all,m_usb_power_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_Power_W_HOST_Resume(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_HOST_Resume] --> 0x%08x\n",
                        m_usb_power_w_host.bitc.resume);
    #endif
    return m_usb_power_w_host.bitc.resume;
}
GH_INLINE void GH_USB_set_Power_W_HOST_Reset(U8 data)
{
    m_usb_power_w_host.bitc.reset = data;
    *(volatile U8 *)REG_USB_POWER_W_HOST = m_usb_power_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_HOST_Reset] <-- 0x%08x\n",
                        REG_USB_POWER_W_HOST,m_usb_power_w_host.all,m_usb_power_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_Power_W_HOST_Reset(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_HOST_Reset] --> 0x%08x\n",
                        m_usb_power_w_host.bitc.reset);
    #endif
    return m_usb_power_w_host.bitc.reset;
}
GH_INLINE void GH_USB_set_Power_W_HOST_HS_Enab(U8 data)
{
    m_usb_power_w_host.bitc.hs_enab = data;
    *(volatile U8 *)REG_USB_POWER_W_HOST = m_usb_power_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Power_W_HOST_HS_Enab] <-- 0x%08x\n",
                        REG_USB_POWER_W_HOST,m_usb_power_w_host.all,m_usb_power_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_Power_W_HOST_HS_Enab(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_Power_W_HOST_HS_Enab] --> 0x%08x\n",
                        m_usb_power_w_host.bitc.hs_enab);
    #endif
    return m_usb_power_w_host.bitc.hs_enab;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_IntrTx (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_IntrTx'. */
U16  GH_USB_get_IntrTx(void);
/*! \brief Reads the bit group 'EP0' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP0(void);
/*! \brief Reads the bit group 'EP1Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP1Tx(void);
/*! \brief Reads the bit group 'EP2Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP2Tx(void);
/*! \brief Reads the bit group 'EP3Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP3Tx(void);
/*! \brief Reads the bit group 'EP4Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP4Tx(void);
/*! \brief Reads the bit group 'EP5Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP5Tx(void);
/*! \brief Reads the bit group 'EP6Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP6Tx(void);
/*! \brief Reads the bit group 'EP7Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP7Tx(void);
/*! \brief Reads the bit group 'EP8Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP8Tx(void);
/*! \brief Reads the bit group 'EP9Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP9Tx(void);
/*! \brief Reads the bit group 'EP10Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP10Tx(void);
/*! \brief Reads the bit group 'EP11Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP11Tx(void);
/*! \brief Reads the bit group 'EP12Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP12Tx(void);
/*! \brief Reads the bit group 'EP13Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP13Tx(void);
/*! \brief Reads the bit group 'EP14Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP14Tx(void);
/*! \brief Reads the bit group 'EP15Tx' of register 'USB_IntrTx'. */
U8   GH_USB_get_IntrTx_EP15Tx(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_USB_get_IntrTx(void)
{
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP0(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP0] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep0;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP1Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP1Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep1tx;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP2Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP2Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep2tx;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP3Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP3Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep3tx;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP4Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP4Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep4tx;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP5Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP5Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep5tx;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP6Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP6Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep6tx;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP7Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP7Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep7tx;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP8Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP8Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep8tx;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP9Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP9Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep9tx;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP10Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP10Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep10tx;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP11Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP11Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep11tx;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP12Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP12Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep12tx;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP13Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP13Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep13tx;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP14Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP14Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep14tx;
}
GH_INLINE U8   GH_USB_get_IntrTx_EP15Tx(void)
{
    GH_USB_INTRTX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTx_EP15Tx] --> 0x%08x\n",
                        REG_USB_INTRTX,value);
    #endif
    return tmp_value.bitc.ep15tx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_IntrRx (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_IntrRx'. */
U16  GH_USB_get_IntrRx(void);
/*! \brief Reads the bit group 'EP1Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP1Rx(void);
/*! \brief Reads the bit group 'EP2Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP2Rx(void);
/*! \brief Reads the bit group 'EP3Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP3Rx(void);
/*! \brief Reads the bit group 'EP4Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP4Rx(void);
/*! \brief Reads the bit group 'EP5Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP5Rx(void);
/*! \brief Reads the bit group 'EP6Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP6Rx(void);
/*! \brief Reads the bit group 'EP7Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP7Rx(void);
/*! \brief Reads the bit group 'EP8Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP8Rx(void);
/*! \brief Reads the bit group 'EP9Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP9Rx(void);
/*! \brief Reads the bit group 'EP10Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP10Rx(void);
/*! \brief Reads the bit group 'EP11Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP11Rx(void);
/*! \brief Reads the bit group 'EP12Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP12Rx(void);
/*! \brief Reads the bit group 'EP13Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP13Rx(void);
/*! \brief Reads the bit group 'EP14Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP14Rx(void);
/*! \brief Reads the bit group 'EP15Rx' of register 'USB_IntrRx'. */
U8   GH_USB_get_IntrRx_EP15Rx(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_USB_get_IntrRx(void)
{
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP1Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP1Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep1rx;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP2Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP2Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep2rx;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP3Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP3Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep3rx;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP4Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP4Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep4rx;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP5Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP5Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep5rx;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP6Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP6Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep6rx;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP7Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP7Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep7rx;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP8Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP8Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep8rx;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP9Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP9Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep9rx;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP10Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP10Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep10rx;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP11Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP11Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep11rx;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP12Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP12Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep12rx;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP13Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP13Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep13rx;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP14Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP14Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep14rx;
}
GH_INLINE U8   GH_USB_get_IntrRx_EP15Rx(void)
{
    GH_USB_INTRRX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRx_EP15Rx] --> 0x%08x\n",
                        REG_USB_INTRRX,value);
    #endif
    return tmp_value.bitc.ep15rx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_IntrTxE (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE(U16 data);
/*! \brief Reads the register 'USB_IntrTxE'. */
U16  GH_USB_get_IntrTxE(void);
/*! \brief Writes the bit group 'EP0' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP0(U8 data);
/*! \brief Reads the bit group 'EP0' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP0(void);
/*! \brief Writes the bit group 'EP1Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP1Tx(U8 data);
/*! \brief Reads the bit group 'EP1Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP1Tx(void);
/*! \brief Writes the bit group 'EP2Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP2Tx(U8 data);
/*! \brief Reads the bit group 'EP2Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP2Tx(void);
/*! \brief Writes the bit group 'EP3Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP3Tx(U8 data);
/*! \brief Reads the bit group 'EP3Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP3Tx(void);
/*! \brief Writes the bit group 'EP4Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP4Tx(U8 data);
/*! \brief Reads the bit group 'EP4Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP4Tx(void);
/*! \brief Writes the bit group 'EP5Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP5Tx(U8 data);
/*! \brief Reads the bit group 'EP5Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP5Tx(void);
/*! \brief Writes the bit group 'EP6Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP6Tx(U8 data);
/*! \brief Reads the bit group 'EP6Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP6Tx(void);
/*! \brief Writes the bit group 'EP7Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP7Tx(U8 data);
/*! \brief Reads the bit group 'EP7Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP7Tx(void);
/*! \brief Writes the bit group 'EP8Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP8Tx(U8 data);
/*! \brief Reads the bit group 'EP8Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP8Tx(void);
/*! \brief Writes the bit group 'EP9Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP9Tx(U8 data);
/*! \brief Reads the bit group 'EP9Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP9Tx(void);
/*! \brief Writes the bit group 'EP10Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP10Tx(U8 data);
/*! \brief Reads the bit group 'EP10Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP10Tx(void);
/*! \brief Writes the bit group 'EP11Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP11Tx(U8 data);
/*! \brief Reads the bit group 'EP11Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP11Tx(void);
/*! \brief Writes the bit group 'EP12Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP12Tx(U8 data);
/*! \brief Reads the bit group 'EP12Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP12Tx(void);
/*! \brief Writes the bit group 'EP13Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP13Tx(U8 data);
/*! \brief Reads the bit group 'EP13Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP13Tx(void);
/*! \brief Writes the bit group 'EP14Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP14Tx(U8 data);
/*! \brief Reads the bit group 'EP14Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP14Tx(void);
/*! \brief Writes the bit group 'EP15Tx' of register 'USB_IntrTxE'. */
void GH_USB_set_IntrTxE_EP15Tx(U8 data);
/*! \brief Reads the bit group 'EP15Tx' of register 'USB_IntrTxE'. */
U8   GH_USB_get_IntrTxE_EP15Tx(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_IntrTxE(U16 data)
{
    *(volatile U16 *)REG_USB_INTRTXE = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE] <-- 0x%08x\n",
                        REG_USB_INTRTXE,data,data);
    #endif
}
GH_INLINE U16  GH_USB_get_IntrTxE(void)
{
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_IntrTxE_EP0(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep0 = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP0] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP0(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP0] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep0;
}
GH_INLINE void GH_USB_set_IntrTxE_EP1Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep1tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP1Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP1Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP1Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep1tx;
}
GH_INLINE void GH_USB_set_IntrTxE_EP2Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep2tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP2Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP2Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP2Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep2tx;
}
GH_INLINE void GH_USB_set_IntrTxE_EP3Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep3tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP3Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP3Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP3Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep3tx;
}
GH_INLINE void GH_USB_set_IntrTxE_EP4Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep4tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP4Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP4Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP4Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep4tx;
}
GH_INLINE void GH_USB_set_IntrTxE_EP5Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep5tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP5Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP5Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP5Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep5tx;
}
GH_INLINE void GH_USB_set_IntrTxE_EP6Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep6tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP6Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP6Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP6Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep6tx;
}
GH_INLINE void GH_USB_set_IntrTxE_EP7Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep7tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP7Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP7Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP7Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep7tx;
}
GH_INLINE void GH_USB_set_IntrTxE_EP8Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep8tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP8Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP8Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP8Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep8tx;
}
GH_INLINE void GH_USB_set_IntrTxE_EP9Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep9tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP9Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP9Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP9Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep9tx;
}
GH_INLINE void GH_USB_set_IntrTxE_EP10Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep10tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP10Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP10Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP10Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep10tx;
}
GH_INLINE void GH_USB_set_IntrTxE_EP11Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep11tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP11Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP11Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP11Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep11tx;
}
GH_INLINE void GH_USB_set_IntrTxE_EP12Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep12tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP12Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP12Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP12Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep12tx;
}
GH_INLINE void GH_USB_set_IntrTxE_EP13Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep13tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP13Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP13Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP13Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep13tx;
}
GH_INLINE void GH_USB_set_IntrTxE_EP14Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep14tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP14Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP14Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP14Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep14tx;
}
GH_INLINE void GH_USB_set_IntrTxE_EP15Tx(U8 data)
{
    GH_USB_INTRTXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRTXE;
    d.bitc.ep15tx = data;
    *(volatile U16 *)REG_USB_INTRTXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrTxE_EP15Tx] <-- 0x%08x\n",
                        REG_USB_INTRTXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrTxE_EP15Tx(void)
{
    GH_USB_INTRTXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRTXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrTxE_EP15Tx] --> 0x%08x\n",
                        REG_USB_INTRTXE,value);
    #endif
    return tmp_value.bitc.ep15tx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_IntrRxE (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE(U16 data);
/*! \brief Reads the register 'USB_IntrRxE'. */
U16  GH_USB_get_IntrRxE(void);
/*! \brief Writes the bit group 'EP1Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP1Rx(U8 data);
/*! \brief Reads the bit group 'EP1Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP1Rx(void);
/*! \brief Writes the bit group 'EP2Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP2Rx(U8 data);
/*! \brief Reads the bit group 'EP2Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP2Rx(void);
/*! \brief Writes the bit group 'EP3Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP3Rx(U8 data);
/*! \brief Reads the bit group 'EP3Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP3Rx(void);
/*! \brief Writes the bit group 'EP4Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP4Rx(U8 data);
/*! \brief Reads the bit group 'EP4Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP4Rx(void);
/*! \brief Writes the bit group 'EP5Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP5Rx(U8 data);
/*! \brief Reads the bit group 'EP5Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP5Rx(void);
/*! \brief Writes the bit group 'EP6Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP6Rx(U8 data);
/*! \brief Reads the bit group 'EP6Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP6Rx(void);
/*! \brief Writes the bit group 'EP7Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP7Rx(U8 data);
/*! \brief Reads the bit group 'EP7Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP7Rx(void);
/*! \brief Writes the bit group 'EP8Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP8Rx(U8 data);
/*! \brief Reads the bit group 'EP8Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP8Rx(void);
/*! \brief Writes the bit group 'EP9Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP9Rx(U8 data);
/*! \brief Reads the bit group 'EP9Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP9Rx(void);
/*! \brief Writes the bit group 'EP10Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP10Rx(U8 data);
/*! \brief Reads the bit group 'EP10Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP10Rx(void);
/*! \brief Writes the bit group 'EP11Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP11Rx(U8 data);
/*! \brief Reads the bit group 'EP11Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP11Rx(void);
/*! \brief Writes the bit group 'EP12Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP12Rx(U8 data);
/*! \brief Reads the bit group 'EP12Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP12Rx(void);
/*! \brief Writes the bit group 'EP13Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP13Rx(U8 data);
/*! \brief Reads the bit group 'EP13Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP13Rx(void);
/*! \brief Writes the bit group 'EP14Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP14Rx(U8 data);
/*! \brief Reads the bit group 'EP14Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP14Rx(void);
/*! \brief Writes the bit group 'EP15Rx' of register 'USB_IntrRxE'. */
void GH_USB_set_IntrRxE_EP15Rx(U8 data);
/*! \brief Reads the bit group 'EP15Rx' of register 'USB_IntrRxE'. */
U8   GH_USB_get_IntrRxE_EP15Rx(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_IntrRxE(U16 data)
{
    *(volatile U16 *)REG_USB_INTRRXE = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE] <-- 0x%08x\n",
                        REG_USB_INTRRXE,data,data);
    #endif
}
GH_INLINE U16  GH_USB_get_IntrRxE(void)
{
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_IntrRxE_EP1Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep1rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP1Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP1Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP1Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep1rx;
}
GH_INLINE void GH_USB_set_IntrRxE_EP2Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep2rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP2Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP2Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP2Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep2rx;
}
GH_INLINE void GH_USB_set_IntrRxE_EP3Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep3rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP3Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP3Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP3Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep3rx;
}
GH_INLINE void GH_USB_set_IntrRxE_EP4Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep4rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP4Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP4Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP4Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep4rx;
}
GH_INLINE void GH_USB_set_IntrRxE_EP5Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep5rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP5Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP5Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP5Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep5rx;
}
GH_INLINE void GH_USB_set_IntrRxE_EP6Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep6rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP6Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP6Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP6Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep6rx;
}
GH_INLINE void GH_USB_set_IntrRxE_EP7Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep7rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP7Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP7Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP7Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep7rx;
}
GH_INLINE void GH_USB_set_IntrRxE_EP8Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep8rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP8Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP8Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP8Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep8rx;
}
GH_INLINE void GH_USB_set_IntrRxE_EP9Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep9rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP9Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP9Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP9Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep9rx;
}
GH_INLINE void GH_USB_set_IntrRxE_EP10Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep10rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP10Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP10Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP10Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep10rx;
}
GH_INLINE void GH_USB_set_IntrRxE_EP11Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep11rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP11Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP11Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP11Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep11rx;
}
GH_INLINE void GH_USB_set_IntrRxE_EP12Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep12rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP12Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP12Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP12Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep12rx;
}
GH_INLINE void GH_USB_set_IntrRxE_EP13Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep13rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP13Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP13Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP13Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep13rx;
}
GH_INLINE void GH_USB_set_IntrRxE_EP14Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep14rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP14Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP14Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP14Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep14rx;
}
GH_INLINE void GH_USB_set_IntrRxE_EP15Rx(U8 data)
{
    GH_USB_INTRRXE_S d;
    d.all = *(volatile U16 *)REG_USB_INTRRXE;
    d.bitc.ep15rx = data;
    *(volatile U16 *)REG_USB_INTRRXE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrRxE_EP15Rx] <-- 0x%08x\n",
                        REG_USB_INTRRXE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrRxE_EP15Rx(void)
{
    GH_USB_INTRRXE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_INTRRXE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrRxE_EP15Rx] --> 0x%08x\n",
                        REG_USB_INTRRXE,value);
    #endif
    return tmp_value.bitc.ep15rx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_IntrUSB (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_IntrUSB'. */
U8   GH_USB_get_IntrUSB(void);
/*! \brief Reads the bit group 'Suspend' of register 'USB_IntrUSB'. */
U8   GH_USB_get_IntrUSB_Suspend(void);
/*! \brief Reads the bit group 'Resume' of register 'USB_IntrUSB'. */
U8   GH_USB_get_IntrUSB_Resume(void);
/*! \brief Reads the bit group 'Reset_Babble' of register 'USB_IntrUSB'. */
U8   GH_USB_get_IntrUSB_Reset_Babble(void);
/*! \brief Reads the bit group 'SOF' of register 'USB_IntrUSB'. */
U8   GH_USB_get_IntrUSB_SOF(void);
/*! \brief Reads the bit group 'Conn' of register 'USB_IntrUSB'. */
U8   GH_USB_get_IntrUSB_Conn(void);
/*! \brief Reads the bit group 'Discon' of register 'USB_IntrUSB'. */
U8   GH_USB_get_IntrUSB_Discon(void);
/*! \brief Reads the bit group 'Sess_Req' of register 'USB_IntrUSB'. */
U8   GH_USB_get_IntrUSB_Sess_Req(void);
/*! \brief Reads the bit group 'VBus_Error' of register 'USB_IntrUSB'. */
U8   GH_USB_get_IntrUSB_VBus_Error(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_IntrUSB(void)
{
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_IntrUSB_Suspend(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_Suspend] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.suspend;
}
GH_INLINE U8   GH_USB_get_IntrUSB_Resume(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_Resume] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.resume;
}
GH_INLINE U8   GH_USB_get_IntrUSB_Reset_Babble(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_Reset_Babble] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.reset_babble;
}
GH_INLINE U8   GH_USB_get_IntrUSB_SOF(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_SOF] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.sof;
}
GH_INLINE U8   GH_USB_get_IntrUSB_Conn(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_Conn] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.conn;
}
GH_INLINE U8   GH_USB_get_IntrUSB_Discon(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_Discon] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.discon;
}
GH_INLINE U8   GH_USB_get_IntrUSB_Sess_Req(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_Sess_Req] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.sess_req;
}
GH_INLINE U8   GH_USB_get_IntrUSB_VBus_Error(void)
{
    GH_USB_INTRUSB_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSB);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSB_VBus_Error] --> 0x%08x\n",
                        REG_USB_INTRUSB,value);
    #endif
    return tmp_value.bitc.vbus_error;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_IntrUSBE (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_IntrUSBE'. */
void GH_USB_set_IntrUSBE(U8 data);
/*! \brief Reads the register 'USB_IntrUSBE'. */
U8   GH_USB_get_IntrUSBE(void);
/*! \brief Writes the bit group 'Suspend' of register 'USB_IntrUSBE'. */
void GH_USB_set_IntrUSBE_Suspend(U8 data);
/*! \brief Reads the bit group 'Suspend' of register 'USB_IntrUSBE'. */
U8   GH_USB_get_IntrUSBE_Suspend(void);
/*! \brief Writes the bit group 'Resume' of register 'USB_IntrUSBE'. */
void GH_USB_set_IntrUSBE_Resume(U8 data);
/*! \brief Reads the bit group 'Resume' of register 'USB_IntrUSBE'. */
U8   GH_USB_get_IntrUSBE_Resume(void);
/*! \brief Writes the bit group 'Reset_Babble' of register 'USB_IntrUSBE'. */
void GH_USB_set_IntrUSBE_Reset_Babble(U8 data);
/*! \brief Reads the bit group 'Reset_Babble' of register 'USB_IntrUSBE'. */
U8   GH_USB_get_IntrUSBE_Reset_Babble(void);
/*! \brief Writes the bit group 'SOF' of register 'USB_IntrUSBE'. */
void GH_USB_set_IntrUSBE_SOF(U8 data);
/*! \brief Reads the bit group 'SOF' of register 'USB_IntrUSBE'. */
U8   GH_USB_get_IntrUSBE_SOF(void);
/*! \brief Writes the bit group 'Conn' of register 'USB_IntrUSBE'. */
void GH_USB_set_IntrUSBE_Conn(U8 data);
/*! \brief Reads the bit group 'Conn' of register 'USB_IntrUSBE'. */
U8   GH_USB_get_IntrUSBE_Conn(void);
/*! \brief Writes the bit group 'Discon' of register 'USB_IntrUSBE'. */
void GH_USB_set_IntrUSBE_Discon(U8 data);
/*! \brief Reads the bit group 'Discon' of register 'USB_IntrUSBE'. */
U8   GH_USB_get_IntrUSBE_Discon(void);
/*! \brief Writes the bit group 'Sess_Req' of register 'USB_IntrUSBE'. */
void GH_USB_set_IntrUSBE_Sess_Req(U8 data);
/*! \brief Reads the bit group 'Sess_Req' of register 'USB_IntrUSBE'. */
U8   GH_USB_get_IntrUSBE_Sess_Req(void);
/*! \brief Writes the bit group 'VBus_Error' of register 'USB_IntrUSBE'. */
void GH_USB_set_IntrUSBE_VBus_Error(U8 data);
/*! \brief Reads the bit group 'VBus_Error' of register 'USB_IntrUSBE'. */
U8   GH_USB_get_IntrUSBE_VBus_Error(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_IntrUSBE(U8 data)
{
    *(volatile U8 *)REG_USB_INTRUSBE = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrUSBE(void)
{
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_IntrUSBE_Suspend(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.suspend = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_Suspend] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrUSBE_Suspend(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_Suspend] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.suspend;
}
GH_INLINE void GH_USB_set_IntrUSBE_Resume(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.resume = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_Resume] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrUSBE_Resume(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_Resume] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.resume;
}
GH_INLINE void GH_USB_set_IntrUSBE_Reset_Babble(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.reset_babble = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_Reset_Babble] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrUSBE_Reset_Babble(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_Reset_Babble] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.reset_babble;
}
GH_INLINE void GH_USB_set_IntrUSBE_SOF(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.sof = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_SOF] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrUSBE_SOF(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_SOF] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.sof;
}
GH_INLINE void GH_USB_set_IntrUSBE_Conn(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.conn = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_Conn] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrUSBE_Conn(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_Conn] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.conn;
}
GH_INLINE void GH_USB_set_IntrUSBE_Discon(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.discon = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_Discon] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrUSBE_Discon(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_Discon] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.discon;
}
GH_INLINE void GH_USB_set_IntrUSBE_Sess_Req(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.sess_req = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_Sess_Req] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrUSBE_Sess_Req(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_Sess_Req] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.sess_req;
}
GH_INLINE void GH_USB_set_IntrUSBE_VBus_Error(U8 data)
{
    GH_USB_INTRUSBE_S d;
    d.all = *(volatile U8 *)REG_USB_INTRUSBE;
    d.bitc.vbus_error = data;
    *(volatile U8 *)REG_USB_INTRUSBE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_IntrUSBE_VBus_Error] <-- 0x%08x\n",
                        REG_USB_INTRUSBE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_IntrUSBE_VBus_Error(void)
{
    GH_USB_INTRUSBE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INTRUSBE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_IntrUSBE_VBus_Error] --> 0x%08x\n",
                        REG_USB_INTRUSBE,value);
    #endif
    return tmp_value.bitc.vbus_error;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_Frame (read)                                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_Frame'. */
U16  GH_USB_get_Frame(void);
/*! \brief Reads the bit group 'Number' of register 'USB_Frame'. */
U16  GH_USB_get_Frame_Number(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_USB_get_Frame(void)
{
    U16 value = (*(volatile U16 *)REG_USB_FRAME);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Frame] --> 0x%08x\n",
                        REG_USB_FRAME,value);
    #endif
    return value;
}
GH_INLINE U16  GH_USB_get_Frame_Number(void)
{
    GH_USB_FRAME_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_FRAME);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Frame_Number] --> 0x%08x\n",
                        REG_USB_FRAME,value);
    #endif
    return tmp_value.bitc.number;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_Index (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_Index'. */
void GH_USB_set_Index(U8 data);
/*! \brief Reads the register 'USB_Index'. */
U8   GH_USB_get_Index(void);
/*! \brief Writes the bit group 'SelectedEndpoint' of register 'USB_Index'. */
void GH_USB_set_Index_SelectedEndpoint(U8 data);
/*! \brief Reads the bit group 'SelectedEndpoint' of register 'USB_Index'. */
U8   GH_USB_get_Index_SelectedEndpoint(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_Index(U8 data)
{
    *(volatile U8 *)REG_USB_INDEX = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Index] <-- 0x%08x\n",
                        REG_USB_INDEX,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_Index(void)
{
    U8 value = (*(volatile U8 *)REG_USB_INDEX);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Index] --> 0x%08x\n",
                        REG_USB_INDEX,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_Index_SelectedEndpoint(U8 data)
{
    GH_USB_INDEX_S d;
    d.all = *(volatile U8 *)REG_USB_INDEX;
    d.bitc.selectedendpoint = data;
    *(volatile U8 *)REG_USB_INDEX = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Index_SelectedEndpoint] <-- 0x%08x\n",
                        REG_USB_INDEX,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_Index_SelectedEndpoint(void)
{
    GH_USB_INDEX_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_INDEX);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Index_SelectedEndpoint] --> 0x%08x\n",
                        REG_USB_INDEX,value);
    #endif
    return tmp_value.bitc.selectedendpoint;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_Testmode (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_Testmode'. */
void GH_USB_set_Testmode(U8 data);
/*! \brief Reads the register 'USB_Testmode'. */
U8   GH_USB_get_Testmode(void);
/*! \brief Writes the bit group 'Test_SE0_NAK' of register 'USB_Testmode'. */
void GH_USB_set_Testmode_Test_SE0_NAK(U8 data);
/*! \brief Reads the bit group 'Test_SE0_NAK' of register 'USB_Testmode'. */
U8   GH_USB_get_Testmode_Test_SE0_NAK(void);
/*! \brief Writes the bit group 'Test_J' of register 'USB_Testmode'. */
void GH_USB_set_Testmode_Test_J(U8 data);
/*! \brief Reads the bit group 'Test_J' of register 'USB_Testmode'. */
U8   GH_USB_get_Testmode_Test_J(void);
/*! \brief Writes the bit group 'Test_K' of register 'USB_Testmode'. */
void GH_USB_set_Testmode_Test_K(U8 data);
/*! \brief Reads the bit group 'Test_K' of register 'USB_Testmode'. */
U8   GH_USB_get_Testmode_Test_K(void);
/*! \brief Writes the bit group 'Test_Packet' of register 'USB_Testmode'. */
void GH_USB_set_Testmode_Test_Packet(U8 data);
/*! \brief Reads the bit group 'Test_Packet' of register 'USB_Testmode'. */
U8   GH_USB_get_Testmode_Test_Packet(void);
/*! \brief Writes the bit group 'Force_HS' of register 'USB_Testmode'. */
void GH_USB_set_Testmode_Force_HS(U8 data);
/*! \brief Reads the bit group 'Force_HS' of register 'USB_Testmode'. */
U8   GH_USB_get_Testmode_Force_HS(void);
/*! \brief Writes the bit group 'Force_FS' of register 'USB_Testmode'. */
void GH_USB_set_Testmode_Force_FS(U8 data);
/*! \brief Reads the bit group 'Force_FS' of register 'USB_Testmode'. */
U8   GH_USB_get_Testmode_Force_FS(void);
/*! \brief Writes the bit group 'FIFO_Access' of register 'USB_Testmode'. */
void GH_USB_set_Testmode_FIFO_Access(U8 data);
/*! \brief Reads the bit group 'FIFO_Access' of register 'USB_Testmode'. */
U8   GH_USB_get_Testmode_FIFO_Access(void);
/*! \brief Writes the bit group 'Force_Host' of register 'USB_Testmode'. */
void GH_USB_set_Testmode_Force_Host(U8 data);
/*! \brief Reads the bit group 'Force_Host' of register 'USB_Testmode'. */
U8   GH_USB_get_Testmode_Force_Host(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_Testmode(U8 data)
{
    *(volatile U8 *)REG_USB_TESTMODE = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode] <-- 0x%08x\n",
                        REG_USB_TESTMODE,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_Testmode(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_Testmode_Test_SE0_NAK(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.test_se0_nak = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_Test_SE0_NAK] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_Testmode_Test_SE0_NAK(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_Test_SE0_NAK] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.test_se0_nak;
}
GH_INLINE void GH_USB_set_Testmode_Test_J(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.test_j = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_Test_J] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_Testmode_Test_J(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_Test_J] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.test_j;
}
GH_INLINE void GH_USB_set_Testmode_Test_K(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.test_k = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_Test_K] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_Testmode_Test_K(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_Test_K] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.test_k;
}
GH_INLINE void GH_USB_set_Testmode_Test_Packet(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.test_packet = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_Test_Packet] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_Testmode_Test_Packet(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_Test_Packet] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.test_packet;
}
GH_INLINE void GH_USB_set_Testmode_Force_HS(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.force_hs = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_Force_HS] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_Testmode_Force_HS(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_Force_HS] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.force_hs;
}
GH_INLINE void GH_USB_set_Testmode_Force_FS(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.force_fs = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_Force_FS] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_Testmode_Force_FS(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_Force_FS] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.force_fs;
}
GH_INLINE void GH_USB_set_Testmode_FIFO_Access(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.fifo_access = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_FIFO_Access] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_Testmode_FIFO_Access(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_FIFO_Access] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.fifo_access;
}
GH_INLINE void GH_USB_set_Testmode_Force_Host(U8 data)
{
    GH_USB_TESTMODE_S d;
    d.all = *(volatile U8 *)REG_USB_TESTMODE;
    d.bitc.force_host = data;
    *(volatile U8 *)REG_USB_TESTMODE = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Testmode_Force_Host] <-- 0x%08x\n",
                        REG_USB_TESTMODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_Testmode_Force_Host(void)
{
    GH_USB_TESTMODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TESTMODE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Testmode_Force_Host] --> 0x%08x\n",
                        REG_USB_TESTMODE,value);
    #endif
    return tmp_value.bitc.force_host;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_CSR0L_R_PERI (read)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_CSR0L_R_PERI'. */
U8   GH_USB_get_CSR0L_R_PERI(void);
/*! \brief Reads the bit group 'RxPktRdy' of register 'USB_CSR0L_R_PERI'. */
U8   GH_USB_get_CSR0L_R_PERI_RxPktRdy(void);
/*! \brief Reads the bit group 'TxPktRdy' of register 'USB_CSR0L_R_PERI'. */
U8   GH_USB_get_CSR0L_R_PERI_TxPktRdy(void);
/*! \brief Reads the bit group 'SentStall' of register 'USB_CSR0L_R_PERI'. */
U8   GH_USB_get_CSR0L_R_PERI_SentStall(void);
/*! \brief Reads the bit group 'SetupEnd' of register 'USB_CSR0L_R_PERI'. */
U8   GH_USB_get_CSR0L_R_PERI_SetupEnd(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_CSR0L_R_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_PERI] --> 0x%08x\n",
                        REG_USB_CSR0L_R_PERI,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_CSR0L_R_PERI_RxPktRdy(void)
{
    GH_USB_CSR0L_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_PERI_RxPktRdy] --> 0x%08x\n",
                        REG_USB_CSR0L_R_PERI,value);
    #endif
    return tmp_value.bitc.rxpktrdy;
}
GH_INLINE U8   GH_USB_get_CSR0L_R_PERI_TxPktRdy(void)
{
    GH_USB_CSR0L_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_PERI_TxPktRdy] --> 0x%08x\n",
                        REG_USB_CSR0L_R_PERI,value);
    #endif
    return tmp_value.bitc.txpktrdy;
}
GH_INLINE U8   GH_USB_get_CSR0L_R_PERI_SentStall(void)
{
    GH_USB_CSR0L_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_PERI_SentStall] --> 0x%08x\n",
                        REG_USB_CSR0L_R_PERI,value);
    #endif
    return tmp_value.bitc.sentstall;
}
GH_INLINE U8   GH_USB_get_CSR0L_R_PERI_SetupEnd(void)
{
    GH_USB_CSR0L_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_PERI_SetupEnd] --> 0x%08x\n",
                        REG_USB_CSR0L_R_PERI,value);
    #endif
    return tmp_value.bitc.setupend;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_CSR0L_W_PERI (write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_CSR0L_W_PERI'. */
void GH_USB_set_CSR0L_W_PERI(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_CSR0L_W_PERI'. */
U8   GH_USB_getm_CSR0L_W_PERI(void);
/*! \brief Writes the bit group 'TxPktRdy' of register 'USB_CSR0L_W_PERI'. */
void GH_USB_set_CSR0L_W_PERI_TxPktRdy(U8 data);
/*! \brief Reads the bit group 'TxPktRdy' from the mirror variable of register 'USB_CSR0L_W_PERI'. */
U8   GH_USB_getm_CSR0L_W_PERI_TxPktRdy(void);
/*! \brief Writes the bit group 'SentStall' of register 'USB_CSR0L_W_PERI'. */
void GH_USB_set_CSR0L_W_PERI_SentStall(U8 data);
/*! \brief Reads the bit group 'SentStall' from the mirror variable of register 'USB_CSR0L_W_PERI'. */
U8   GH_USB_getm_CSR0L_W_PERI_SentStall(void);
/*! \brief Writes the bit group 'DataEnd' of register 'USB_CSR0L_W_PERI'. */
void GH_USB_set_CSR0L_W_PERI_DataEnd(U8 data);
/*! \brief Reads the bit group 'DataEnd' from the mirror variable of register 'USB_CSR0L_W_PERI'. */
U8   GH_USB_getm_CSR0L_W_PERI_DataEnd(void);
/*! \brief Writes the bit group 'SendStall' of register 'USB_CSR0L_W_PERI'. */
void GH_USB_set_CSR0L_W_PERI_SendStall(U8 data);
/*! \brief Reads the bit group 'SendStall' from the mirror variable of register 'USB_CSR0L_W_PERI'. */
U8   GH_USB_getm_CSR0L_W_PERI_SendStall(void);
/*! \brief Writes the bit group 'ServicedRxPktRdy' of register 'USB_CSR0L_W_PERI'. */
void GH_USB_set_CSR0L_W_PERI_ServicedRxPktRdy(U8 data);
/*! \brief Reads the bit group 'ServicedRxPktRdy' from the mirror variable of register 'USB_CSR0L_W_PERI'. */
U8   GH_USB_getm_CSR0L_W_PERI_ServicedRxPktRdy(void);
/*! \brief Writes the bit group 'ServicedSetupEnd' of register 'USB_CSR0L_W_PERI'. */
void GH_USB_set_CSR0L_W_PERI_ServicedSetupEnd(U8 data);
/*! \brief Reads the bit group 'ServicedSetupEnd' from the mirror variable of register 'USB_CSR0L_W_PERI'. */
U8   GH_USB_getm_CSR0L_W_PERI_ServicedSetupEnd(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_CSR0L_W_PERI(U8 data)
{
    m_usb_csr0l_w_peri.all = data;
    *(volatile U8 *)REG_USB_CSR0L_W_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_PERI] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_PERI,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_PERI(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_PERI] --> 0x%08x\n",
                        m_usb_csr0l_w_peri.all);
    #endif
    return m_usb_csr0l_w_peri.all;
}
GH_INLINE void GH_USB_set_CSR0L_W_PERI_TxPktRdy(U8 data)
{
    m_usb_csr0l_w_peri.bitc.txpktrdy = data;
    *(volatile U8 *)REG_USB_CSR0L_W_PERI = m_usb_csr0l_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_PERI_TxPktRdy] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_PERI,m_usb_csr0l_w_peri.all,m_usb_csr0l_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_PERI_TxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_PERI_TxPktRdy] --> 0x%08x\n",
                        m_usb_csr0l_w_peri.bitc.txpktrdy);
    #endif
    return m_usb_csr0l_w_peri.bitc.txpktrdy;
}
GH_INLINE void GH_USB_set_CSR0L_W_PERI_SentStall(U8 data)
{
    m_usb_csr0l_w_peri.bitc.sentstall = data;
    *(volatile U8 *)REG_USB_CSR0L_W_PERI = m_usb_csr0l_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_PERI_SentStall] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_PERI,m_usb_csr0l_w_peri.all,m_usb_csr0l_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_PERI_SentStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_PERI_SentStall] --> 0x%08x\n",
                        m_usb_csr0l_w_peri.bitc.sentstall);
    #endif
    return m_usb_csr0l_w_peri.bitc.sentstall;
}
GH_INLINE void GH_USB_set_CSR0L_W_PERI_DataEnd(U8 data)
{
    m_usb_csr0l_w_peri.bitc.dataend = data;
    *(volatile U8 *)REG_USB_CSR0L_W_PERI = m_usb_csr0l_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_PERI_DataEnd] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_PERI,m_usb_csr0l_w_peri.all,m_usb_csr0l_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_PERI_DataEnd(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_PERI_DataEnd] --> 0x%08x\n",
                        m_usb_csr0l_w_peri.bitc.dataend);
    #endif
    return m_usb_csr0l_w_peri.bitc.dataend;
}
GH_INLINE void GH_USB_set_CSR0L_W_PERI_SendStall(U8 data)
{
    m_usb_csr0l_w_peri.bitc.sendstall = data;
    *(volatile U8 *)REG_USB_CSR0L_W_PERI = m_usb_csr0l_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_PERI_SendStall] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_PERI,m_usb_csr0l_w_peri.all,m_usb_csr0l_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_PERI_SendStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_PERI_SendStall] --> 0x%08x\n",
                        m_usb_csr0l_w_peri.bitc.sendstall);
    #endif
    return m_usb_csr0l_w_peri.bitc.sendstall;
}
GH_INLINE void GH_USB_set_CSR0L_W_PERI_ServicedRxPktRdy(U8 data)
{
    m_usb_csr0l_w_peri.bitc.servicedrxpktrdy = data;
    *(volatile U8 *)REG_USB_CSR0L_W_PERI = m_usb_csr0l_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_PERI_ServicedRxPktRdy] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_PERI,m_usb_csr0l_w_peri.all,m_usb_csr0l_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_PERI_ServicedRxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_PERI_ServicedRxPktRdy] --> 0x%08x\n",
                        m_usb_csr0l_w_peri.bitc.servicedrxpktrdy);
    #endif
    return m_usb_csr0l_w_peri.bitc.servicedrxpktrdy;
}
GH_INLINE void GH_USB_set_CSR0L_W_PERI_ServicedSetupEnd(U8 data)
{
    m_usb_csr0l_w_peri.bitc.servicedsetupend = data;
    *(volatile U8 *)REG_USB_CSR0L_W_PERI = m_usb_csr0l_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_PERI_ServicedSetupEnd] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_PERI,m_usb_csr0l_w_peri.all,m_usb_csr0l_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_PERI_ServicedSetupEnd(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_PERI_ServicedSetupEnd] --> 0x%08x\n",
                        m_usb_csr0l_w_peri.bitc.servicedsetupend);
    #endif
    return m_usb_csr0l_w_peri.bitc.servicedsetupend;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_CSR0H_W_PERI (write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_CSR0H_W_PERI'. */
void GH_USB_set_CSR0H_W_PERI(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_CSR0H_W_PERI'. */
U8   GH_USB_getm_CSR0H_W_PERI(void);
/*! \brief Writes the bit group 'FlushFIFO' of register 'USB_CSR0H_W_PERI'. */
void GH_USB_set_CSR0H_W_PERI_FlushFIFO(U8 data);
/*! \brief Reads the bit group 'FlushFIFO' from the mirror variable of register 'USB_CSR0H_W_PERI'. */
U8   GH_USB_getm_CSR0H_W_PERI_FlushFIFO(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_CSR0H_W_PERI(U8 data)
{
    m_usb_csr0h_w_peri.all = data;
    *(volatile U8 *)REG_USB_CSR0H_W_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0H_W_PERI] <-- 0x%08x\n",
                        REG_USB_CSR0H_W_PERI,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0H_W_PERI(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0H_W_PERI] --> 0x%08x\n",
                        m_usb_csr0h_w_peri.all);
    #endif
    return m_usb_csr0h_w_peri.all;
}
GH_INLINE void GH_USB_set_CSR0H_W_PERI_FlushFIFO(U8 data)
{
    m_usb_csr0h_w_peri.bitc.flushfifo = data;
    *(volatile U8 *)REG_USB_CSR0H_W_PERI = m_usb_csr0h_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0H_W_PERI_FlushFIFO] <-- 0x%08x\n",
                        REG_USB_CSR0H_W_PERI,m_usb_csr0h_w_peri.all,m_usb_csr0h_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0H_W_PERI_FlushFIFO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0H_W_PERI_FlushFIFO] --> 0x%08x\n",
                        m_usb_csr0h_w_peri.bitc.flushfifo);
    #endif
    return m_usb_csr0h_w_peri.bitc.flushfifo;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_CSR0L_R_HOST (read)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_CSR0L_R_HOST'. */
U8   GH_USB_get_CSR0L_R_HOST(void);
/*! \brief Reads the bit group 'RxPktRdy' of register 'USB_CSR0L_R_HOST'. */
U8   GH_USB_get_CSR0L_R_HOST_RxPktRdy(void);
/*! \brief Reads the bit group 'TxPktRdy' of register 'USB_CSR0L_R_HOST'. */
U8   GH_USB_get_CSR0L_R_HOST_TxPktRdy(void);
/*! \brief Reads the bit group 'RxStall' of register 'USB_CSR0L_R_HOST'. */
U8   GH_USB_get_CSR0L_R_HOST_RxStall(void);
/*! \brief Reads the bit group 'SetupPkt' of register 'USB_CSR0L_R_HOST'. */
U8   GH_USB_get_CSR0L_R_HOST_SetupPkt(void);
/*! \brief Reads the bit group 'Error' of register 'USB_CSR0L_R_HOST'. */
U8   GH_USB_get_CSR0L_R_HOST_Error(void);
/*! \brief Reads the bit group 'ReqPkt' of register 'USB_CSR0L_R_HOST'. */
U8   GH_USB_get_CSR0L_R_HOST_ReqPkt(void);
/*! \brief Reads the bit group 'StatusPkt' of register 'USB_CSR0L_R_HOST'. */
U8   GH_USB_get_CSR0L_R_HOST_StatusPkt(void);
/*! \brief Reads the bit group 'NAKTimeout' of register 'USB_CSR0L_R_HOST'. */
U8   GH_USB_get_CSR0L_R_HOST_NAKTimeout(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_CSR0L_R_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_CSR0L_R_HOST_RxPktRdy(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_RxPktRdy] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.rxpktrdy;
}
GH_INLINE U8   GH_USB_get_CSR0L_R_HOST_TxPktRdy(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_TxPktRdy] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.txpktrdy;
}
GH_INLINE U8   GH_USB_get_CSR0L_R_HOST_RxStall(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_RxStall] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.rxstall;
}
GH_INLINE U8   GH_USB_get_CSR0L_R_HOST_SetupPkt(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_SetupPkt] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.setuppkt;
}
GH_INLINE U8   GH_USB_get_CSR0L_R_HOST_Error(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_Error] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.error;
}
GH_INLINE U8   GH_USB_get_CSR0L_R_HOST_ReqPkt(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_ReqPkt] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.reqpkt;
}
GH_INLINE U8   GH_USB_get_CSR0L_R_HOST_StatusPkt(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_StatusPkt] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.statuspkt;
}
GH_INLINE U8   GH_USB_get_CSR0L_R_HOST_NAKTimeout(void)
{
    GH_USB_CSR0L_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0L_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0L_R_HOST_NAKTimeout] --> 0x%08x\n",
                        REG_USB_CSR0L_R_HOST,value);
    #endif
    return tmp_value.bitc.naktimeout;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_CSR0H_R_HOST (read)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_CSR0H_R_HOST'. */
U8   GH_USB_get_CSR0H_R_HOST(void);
/*! \brief Reads the bit group 'DataToggle' of register 'USB_CSR0H_R_HOST'. */
U8   GH_USB_get_CSR0H_R_HOST_DataToggle(void);
/*! \brief Reads the bit group 'DisPing' of register 'USB_CSR0H_R_HOST'. */
U8   GH_USB_get_CSR0H_R_HOST_DisPing(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_CSR0H_R_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_CSR0H_R_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0H_R_HOST] --> 0x%08x\n",
                        REG_USB_CSR0H_R_HOST,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_CSR0H_R_HOST_DataToggle(void)
{
    GH_USB_CSR0H_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0H_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0H_R_HOST_DataToggle] --> 0x%08x\n",
                        REG_USB_CSR0H_R_HOST,value);
    #endif
    return tmp_value.bitc.datatoggle;
}
GH_INLINE U8   GH_USB_get_CSR0H_R_HOST_DisPing(void)
{
    GH_USB_CSR0H_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CSR0H_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_CSR0H_R_HOST_DisPing] --> 0x%08x\n",
                        REG_USB_CSR0H_R_HOST,value);
    #endif
    return tmp_value.bitc.disping;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_CSR0L_W_HOST (write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_CSR0L_W_HOST'. */
void GH_USB_set_CSR0L_W_HOST(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_CSR0L_W_HOST'. */
U8   GH_USB_getm_CSR0L_W_HOST(void);
/*! \brief Writes the bit group 'RxPktRdy' of register 'USB_CSR0L_W_HOST'. */
void GH_USB_set_CSR0L_W_HOST_RxPktRdy(U8 data);
/*! \brief Reads the bit group 'RxPktRdy' from the mirror variable of register 'USB_CSR0L_W_HOST'. */
U8   GH_USB_getm_CSR0L_W_HOST_RxPktRdy(void);
/*! \brief Writes the bit group 'TxPktRdy' of register 'USB_CSR0L_W_HOST'. */
void GH_USB_set_CSR0L_W_HOST_TxPktRdy(U8 data);
/*! \brief Reads the bit group 'TxPktRdy' from the mirror variable of register 'USB_CSR0L_W_HOST'. */
U8   GH_USB_getm_CSR0L_W_HOST_TxPktRdy(void);
/*! \brief Writes the bit group 'RxStall' of register 'USB_CSR0L_W_HOST'. */
void GH_USB_set_CSR0L_W_HOST_RxStall(U8 data);
/*! \brief Reads the bit group 'RxStall' from the mirror variable of register 'USB_CSR0L_W_HOST'. */
U8   GH_USB_getm_CSR0L_W_HOST_RxStall(void);
/*! \brief Writes the bit group 'SetupPkt' of register 'USB_CSR0L_W_HOST'. */
void GH_USB_set_CSR0L_W_HOST_SetupPkt(U8 data);
/*! \brief Reads the bit group 'SetupPkt' from the mirror variable of register 'USB_CSR0L_W_HOST'. */
U8   GH_USB_getm_CSR0L_W_HOST_SetupPkt(void);
/*! \brief Writes the bit group 'Error' of register 'USB_CSR0L_W_HOST'. */
void GH_USB_set_CSR0L_W_HOST_Error(U8 data);
/*! \brief Reads the bit group 'Error' from the mirror variable of register 'USB_CSR0L_W_HOST'. */
U8   GH_USB_getm_CSR0L_W_HOST_Error(void);
/*! \brief Writes the bit group 'ReqPkt' of register 'USB_CSR0L_W_HOST'. */
void GH_USB_set_CSR0L_W_HOST_ReqPkt(U8 data);
/*! \brief Reads the bit group 'ReqPkt' from the mirror variable of register 'USB_CSR0L_W_HOST'. */
U8   GH_USB_getm_CSR0L_W_HOST_ReqPkt(void);
/*! \brief Writes the bit group 'StatusPkt' of register 'USB_CSR0L_W_HOST'. */
void GH_USB_set_CSR0L_W_HOST_StatusPkt(U8 data);
/*! \brief Reads the bit group 'StatusPkt' from the mirror variable of register 'USB_CSR0L_W_HOST'. */
U8   GH_USB_getm_CSR0L_W_HOST_StatusPkt(void);
/*! \brief Writes the bit group 'NAKTimeout' of register 'USB_CSR0L_W_HOST'. */
void GH_USB_set_CSR0L_W_HOST_NAKTimeout(U8 data);
/*! \brief Reads the bit group 'NAKTimeout' from the mirror variable of register 'USB_CSR0L_W_HOST'. */
U8   GH_USB_getm_CSR0L_W_HOST_NAKTimeout(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_CSR0L_W_HOST(U8 data)
{
    m_usb_csr0l_w_host.all = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_HOST(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST] --> 0x%08x\n",
                        m_usb_csr0l_w_host.all);
    #endif
    return m_usb_csr0l_w_host.all;
}
GH_INLINE void GH_USB_set_CSR0L_W_HOST_RxPktRdy(U8 data)
{
    m_usb_csr0l_w_host.bitc.rxpktrdy = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_RxPktRdy] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_HOST_RxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_RxPktRdy] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.rxpktrdy);
    #endif
    return m_usb_csr0l_w_host.bitc.rxpktrdy;
}
GH_INLINE void GH_USB_set_CSR0L_W_HOST_TxPktRdy(U8 data)
{
    m_usb_csr0l_w_host.bitc.txpktrdy = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_TxPktRdy] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_HOST_TxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_TxPktRdy] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.txpktrdy);
    #endif
    return m_usb_csr0l_w_host.bitc.txpktrdy;
}
GH_INLINE void GH_USB_set_CSR0L_W_HOST_RxStall(U8 data)
{
    m_usb_csr0l_w_host.bitc.rxstall = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_RxStall] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_HOST_RxStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_RxStall] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.rxstall);
    #endif
    return m_usb_csr0l_w_host.bitc.rxstall;
}
GH_INLINE void GH_USB_set_CSR0L_W_HOST_SetupPkt(U8 data)
{
    m_usb_csr0l_w_host.bitc.setuppkt = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_SetupPkt] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_HOST_SetupPkt(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_SetupPkt] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.setuppkt);
    #endif
    return m_usb_csr0l_w_host.bitc.setuppkt;
}
GH_INLINE void GH_USB_set_CSR0L_W_HOST_Error(U8 data)
{
    m_usb_csr0l_w_host.bitc.error = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_Error] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_HOST_Error(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_Error] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.error);
    #endif
    return m_usb_csr0l_w_host.bitc.error;
}
GH_INLINE void GH_USB_set_CSR0L_W_HOST_ReqPkt(U8 data)
{
    m_usb_csr0l_w_host.bitc.reqpkt = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_ReqPkt] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_HOST_ReqPkt(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_ReqPkt] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.reqpkt);
    #endif
    return m_usb_csr0l_w_host.bitc.reqpkt;
}
GH_INLINE void GH_USB_set_CSR0L_W_HOST_StatusPkt(U8 data)
{
    m_usb_csr0l_w_host.bitc.statuspkt = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_StatusPkt] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_HOST_StatusPkt(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_StatusPkt] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.statuspkt);
    #endif
    return m_usb_csr0l_w_host.bitc.statuspkt;
}
GH_INLINE void GH_USB_set_CSR0L_W_HOST_NAKTimeout(U8 data)
{
    m_usb_csr0l_w_host.bitc.naktimeout = data;
    *(volatile U8 *)REG_USB_CSR0L_W_HOST = m_usb_csr0l_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0L_W_HOST_NAKTimeout] <-- 0x%08x\n",
                        REG_USB_CSR0L_W_HOST,m_usb_csr0l_w_host.all,m_usb_csr0l_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0L_W_HOST_NAKTimeout(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0L_W_HOST_NAKTimeout] --> 0x%08x\n",
                        m_usb_csr0l_w_host.bitc.naktimeout);
    #endif
    return m_usb_csr0l_w_host.bitc.naktimeout;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_CSR0H_W_HOST (write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_CSR0H_W_HOST'. */
void GH_USB_set_CSR0H_W_HOST(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_CSR0H_W_HOST'. */
U8   GH_USB_getm_CSR0H_W_HOST(void);
/*! \brief Writes the bit group 'FlushFIFO' of register 'USB_CSR0H_W_HOST'. */
void GH_USB_set_CSR0H_W_HOST_FlushFIFO(U8 data);
/*! \brief Reads the bit group 'FlushFIFO' from the mirror variable of register 'USB_CSR0H_W_HOST'. */
U8   GH_USB_getm_CSR0H_W_HOST_FlushFIFO(void);
/*! \brief Writes the bit group 'DataToggle' of register 'USB_CSR0H_W_HOST'. */
void GH_USB_set_CSR0H_W_HOST_DataToggle(U8 data);
/*! \brief Reads the bit group 'DataToggle' from the mirror variable of register 'USB_CSR0H_W_HOST'. */
U8   GH_USB_getm_CSR0H_W_HOST_DataToggle(void);
/*! \brief Writes the bit group 'DataToggleWriteEnable' of register 'USB_CSR0H_W_HOST'. */
void GH_USB_set_CSR0H_W_HOST_DataToggleWriteEnable(U8 data);
/*! \brief Reads the bit group 'DataToggleWriteEnable' from the mirror variable of register 'USB_CSR0H_W_HOST'. */
U8   GH_USB_getm_CSR0H_W_HOST_DataToggleWriteEnable(void);
/*! \brief Writes the bit group 'DisPing' of register 'USB_CSR0H_W_HOST'. */
void GH_USB_set_CSR0H_W_HOST_DisPing(U8 data);
/*! \brief Reads the bit group 'DisPing' from the mirror variable of register 'USB_CSR0H_W_HOST'. */
U8   GH_USB_getm_CSR0H_W_HOST_DisPing(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_CSR0H_W_HOST(U8 data)
{
    m_usb_csr0h_w_host.all = data;
    *(volatile U8 *)REG_USB_CSR0H_W_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0H_W_HOST] <-- 0x%08x\n",
                        REG_USB_CSR0H_W_HOST,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0H_W_HOST(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0H_W_HOST] --> 0x%08x\n",
                        m_usb_csr0h_w_host.all);
    #endif
    return m_usb_csr0h_w_host.all;
}
GH_INLINE void GH_USB_set_CSR0H_W_HOST_FlushFIFO(U8 data)
{
    m_usb_csr0h_w_host.bitc.flushfifo = data;
    *(volatile U8 *)REG_USB_CSR0H_W_HOST = m_usb_csr0h_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0H_W_HOST_FlushFIFO] <-- 0x%08x\n",
                        REG_USB_CSR0H_W_HOST,m_usb_csr0h_w_host.all,m_usb_csr0h_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0H_W_HOST_FlushFIFO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0H_W_HOST_FlushFIFO] --> 0x%08x\n",
                        m_usb_csr0h_w_host.bitc.flushfifo);
    #endif
    return m_usb_csr0h_w_host.bitc.flushfifo;
}
GH_INLINE void GH_USB_set_CSR0H_W_HOST_DataToggle(U8 data)
{
    m_usb_csr0h_w_host.bitc.datatoggle = data;
    *(volatile U8 *)REG_USB_CSR0H_W_HOST = m_usb_csr0h_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0H_W_HOST_DataToggle] <-- 0x%08x\n",
                        REG_USB_CSR0H_W_HOST,m_usb_csr0h_w_host.all,m_usb_csr0h_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0H_W_HOST_DataToggle(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0H_W_HOST_DataToggle] --> 0x%08x\n",
                        m_usb_csr0h_w_host.bitc.datatoggle);
    #endif
    return m_usb_csr0h_w_host.bitc.datatoggle;
}
GH_INLINE void GH_USB_set_CSR0H_W_HOST_DataToggleWriteEnable(U8 data)
{
    m_usb_csr0h_w_host.bitc.datatogglewriteenable = data;
    *(volatile U8 *)REG_USB_CSR0H_W_HOST = m_usb_csr0h_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0H_W_HOST_DataToggleWriteEnable] <-- 0x%08x\n",
                        REG_USB_CSR0H_W_HOST,m_usb_csr0h_w_host.all,m_usb_csr0h_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0H_W_HOST_DataToggleWriteEnable(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0H_W_HOST_DataToggleWriteEnable] --> 0x%08x\n",
                        m_usb_csr0h_w_host.bitc.datatogglewriteenable);
    #endif
    return m_usb_csr0h_w_host.bitc.datatogglewriteenable;
}
GH_INLINE void GH_USB_set_CSR0H_W_HOST_DisPing(U8 data)
{
    m_usb_csr0h_w_host.bitc.disping = data;
    *(volatile U8 *)REG_USB_CSR0H_W_HOST = m_usb_csr0h_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_CSR0H_W_HOST_DisPing] <-- 0x%08x\n",
                        REG_USB_CSR0H_W_HOST,m_usb_csr0h_w_host.all,m_usb_csr0h_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_CSR0H_W_HOST_DisPing(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_CSR0H_W_HOST_DisPing] --> 0x%08x\n",
                        m_usb_csr0h_w_host.bitc.disping);
    #endif
    return m_usb_csr0h_w_host.bitc.disping;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_Count0 (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_Count0'. */
U8   GH_USB_get_Count0(void);
/*! \brief Reads the bit group 'Endpoint0RxCount' of register 'USB_Count0'. */
U8   GH_USB_get_Count0_Endpoint0RxCount(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_Count0(void)
{
    U8 value = (*(volatile U8 *)REG_USB_COUNT0);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Count0] --> 0x%08x\n",
                        REG_USB_COUNT0,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_Count0_Endpoint0RxCount(void)
{
    GH_USB_COUNT0_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_COUNT0);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Count0_Endpoint0RxCount] --> 0x%08x\n",
                        REG_USB_COUNT0,value);
    #endif
    return tmp_value.bitc.endpoint0rxcount;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_Type0 (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_Type0'. */
void GH_USB_set_Type0(U8 data);
/*! \brief Reads the register 'USB_Type0'. */
U8   GH_USB_get_Type0(void);
/*! \brief Writes the bit group 'Speed' of register 'USB_Type0'. */
void GH_USB_set_Type0_Speed(U8 data);
/*! \brief Reads the bit group 'Speed' of register 'USB_Type0'. */
U8   GH_USB_get_Type0_Speed(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_Type0(U8 data)
{
    *(volatile U8 *)REG_USB_TYPE0 = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Type0] <-- 0x%08x\n",
                        REG_USB_TYPE0,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_Type0(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TYPE0);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Type0] --> 0x%08x\n",
                        REG_USB_TYPE0,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_Type0_Speed(U8 data)
{
    GH_USB_TYPE0_S d;
    d.all = *(volatile U8 *)REG_USB_TYPE0;
    d.bitc.speed = data;
    *(volatile U8 *)REG_USB_TYPE0 = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Type0_Speed] <-- 0x%08x\n",
                        REG_USB_TYPE0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_Type0_Speed(void)
{
    GH_USB_TYPE0_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TYPE0);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Type0_Speed] --> 0x%08x\n",
                        REG_USB_TYPE0,value);
    #endif
    return tmp_value.bitc.speed;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_NAKLimit0_HOST (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_NAKLimit0_HOST'. */
void GH_USB_set_NAKLimit0_HOST(U8 data);
/*! \brief Reads the register 'USB_NAKLimit0_HOST'. */
U8   GH_USB_get_NAKLimit0_HOST(void);
/*! \brief Writes the bit group 'Endpoint0NAKLimit' of register 'USB_NAKLimit0_HOST'. */
void GH_USB_set_NAKLimit0_HOST_Endpoint0NAKLimit(U8 data);
/*! \brief Reads the bit group 'Endpoint0NAKLimit' of register 'USB_NAKLimit0_HOST'. */
U8   GH_USB_get_NAKLimit0_HOST_Endpoint0NAKLimit(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_NAKLimit0_HOST(U8 data)
{
    *(volatile U8 *)REG_USB_NAKLIMIT0_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_NAKLimit0_HOST] <-- 0x%08x\n",
                        REG_USB_NAKLIMIT0_HOST,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_NAKLimit0_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_NAKLIMIT0_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_NAKLimit0_HOST] --> 0x%08x\n",
                        REG_USB_NAKLIMIT0_HOST,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_NAKLimit0_HOST_Endpoint0NAKLimit(U8 data)
{
    GH_USB_NAKLIMIT0_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_NAKLIMIT0_HOST;
    d.bitc.endpoint0naklimit = data;
    *(volatile U8 *)REG_USB_NAKLIMIT0_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_NAKLimit0_HOST_Endpoint0NAKLimit] <-- 0x%08x\n",
                        REG_USB_NAKLIMIT0_HOST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_NAKLimit0_HOST_Endpoint0NAKLimit(void)
{
    GH_USB_NAKLIMIT0_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_NAKLIMIT0_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_NAKLimit0_HOST_Endpoint0NAKLimit] --> 0x%08x\n",
                        REG_USB_NAKLIMIT0_HOST,value);
    #endif
    return tmp_value.bitc.endpoint0naklimit;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_ConfigData (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_ConfigData'. */
U8   GH_USB_get_ConfigData(void);
/*! \brief Reads the bit group 'UTMI_DataWidth' of register 'USB_ConfigData'. */
U8   GH_USB_get_ConfigData_UTMI_DataWidth(void);
/*! \brief Reads the bit group 'SoftConE' of register 'USB_ConfigData'. */
U8   GH_USB_get_ConfigData_SoftConE(void);
/*! \brief Reads the bit group 'DynFIFO_Sizing' of register 'USB_ConfigData'. */
U8   GH_USB_get_ConfigData_DynFIFO_Sizing(void);
/*! \brief Reads the bit group 'HBTxE' of register 'USB_ConfigData'. */
U8   GH_USB_get_ConfigData_HBTxE(void);
/*! \brief Reads the bit group 'HBRxE' of register 'USB_ConfigData'. */
U8   GH_USB_get_ConfigData_HBRxE(void);
/*! \brief Reads the bit group 'BigEndian' of register 'USB_ConfigData'. */
U8   GH_USB_get_ConfigData_BigEndian(void);
/*! \brief Reads the bit group 'MPTxE' of register 'USB_ConfigData'. */
U8   GH_USB_get_ConfigData_MPTxE(void);
/*! \brief Reads the bit group 'MPRxE' of register 'USB_ConfigData'. */
U8   GH_USB_get_ConfigData_MPRxE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_ConfigData(void)
{
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_ConfigData_UTMI_DataWidth(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_UTMI_DataWidth] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.utmi_datawidth;
}
GH_INLINE U8   GH_USB_get_ConfigData_SoftConE(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_SoftConE] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.softcone;
}
GH_INLINE U8   GH_USB_get_ConfigData_DynFIFO_Sizing(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_DynFIFO_Sizing] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.dynfifo_sizing;
}
GH_INLINE U8   GH_USB_get_ConfigData_HBTxE(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_HBTxE] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.hbtxe;
}
GH_INLINE U8   GH_USB_get_ConfigData_HBRxE(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_HBRxE] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.hbrxe;
}
GH_INLINE U8   GH_USB_get_ConfigData_BigEndian(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_BigEndian] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.bigendian;
}
GH_INLINE U8   GH_USB_get_ConfigData_MPTxE(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_MPTxE] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.mptxe;
}
GH_INLINE U8   GH_USB_get_ConfigData_MPRxE(void)
{
    GH_USB_CONFIGDATA_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_CONFIGDATA);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_ConfigData_MPRxE] --> 0x%08x\n",
                        REG_USB_CONFIGDATA,value);
    #endif
    return tmp_value.bitc.mprxe;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxMaxP (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_TxMaxP'. */
void GH_USB_set_TxMaxP(U16 data);
/*! \brief Reads the register 'USB_TxMaxP'. */
U16  GH_USB_get_TxMaxP(void);
/*! \brief Writes the bit group 'TxMaxP' of register 'USB_TxMaxP'. */
void GH_USB_set_TxMaxP_TxMaxP(U16 data);
/*! \brief Reads the bit group 'TxMaxP' of register 'USB_TxMaxP'. */
U16  GH_USB_get_TxMaxP_TxMaxP(void);
/*! \brief Writes the bit group 'multiplier' of register 'USB_TxMaxP'. */
void GH_USB_set_TxMaxP_multiplier(U8 data);
/*! \brief Reads the bit group 'multiplier' of register 'USB_TxMaxP'. */
U8   GH_USB_get_TxMaxP_multiplier(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_TxMaxP(U16 data)
{
    *(volatile U16 *)REG_USB_TXMAXP = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxMaxP] <-- 0x%08x\n",
                        REG_USB_TXMAXP,data,data);
    #endif
}
GH_INLINE U16  GH_USB_get_TxMaxP(void)
{
    U16 value = (*(volatile U16 *)REG_USB_TXMAXP);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxMaxP] --> 0x%08x\n",
                        REG_USB_TXMAXP,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_TxMaxP_TxMaxP(U16 data)
{
    GH_USB_TXMAXP_S d;
    d.all = *(volatile U16 *)REG_USB_TXMAXP;
    d.bitc.txmaxp = data;
    *(volatile U16 *)REG_USB_TXMAXP = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxMaxP_TxMaxP] <-- 0x%08x\n",
                        REG_USB_TXMAXP,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_USB_get_TxMaxP_TxMaxP(void)
{
    GH_USB_TXMAXP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXMAXP);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxMaxP_TxMaxP] --> 0x%08x\n",
                        REG_USB_TXMAXP,value);
    #endif
    return tmp_value.bitc.txmaxp;
}
GH_INLINE void GH_USB_set_TxMaxP_multiplier(U8 data)
{
    GH_USB_TXMAXP_S d;
    d.all = *(volatile U16 *)REG_USB_TXMAXP;
    d.bitc.multiplier = data;
    *(volatile U16 *)REG_USB_TXMAXP = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxMaxP_multiplier] <-- 0x%08x\n",
                        REG_USB_TXMAXP,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxMaxP_multiplier(void)
{
    GH_USB_TXMAXP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXMAXP);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxMaxP_multiplier] --> 0x%08x\n",
                        REG_USB_TXMAXP,value);
    #endif
    return tmp_value.bitc.multiplier;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRL_R_PERI (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_TXCSRL_R_PERI'. */
U8   GH_USB_get_TXCSRL_R_PERI(void);
/*! \brief Reads the bit group 'TxPktRdy' of register 'USB_TXCSRL_R_PERI'. */
U8   GH_USB_get_TXCSRL_R_PERI_TxPktRdy(void);
/*! \brief Reads the bit group 'FIFONotEmpty' of register 'USB_TXCSRL_R_PERI'. */
U8   GH_USB_get_TXCSRL_R_PERI_FIFONotEmpty(void);
/*! \brief Reads the bit group 'UnderRun' of register 'USB_TXCSRL_R_PERI'. */
U8   GH_USB_get_TXCSRL_R_PERI_UnderRun(void);
/*! \brief Reads the bit group 'SendStall' of register 'USB_TXCSRL_R_PERI'. */
U8   GH_USB_get_TXCSRL_R_PERI_SendStall(void);
/*! \brief Reads the bit group 'SentStall' of register 'USB_TXCSRL_R_PERI'. */
U8   GH_USB_get_TXCSRL_R_PERI_SentStall(void);
/*! \brief Reads the bit group 'IncompTx' of register 'USB_TXCSRL_R_PERI'. */
U8   GH_USB_get_TXCSRL_R_PERI_IncompTx(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_TXCSRL_R_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_PERI] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_PERI,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_TXCSRL_R_PERI_TxPktRdy(void)
{
    GH_USB_TXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_PERI_TxPktRdy] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.txpktrdy;
}
GH_INLINE U8   GH_USB_get_TXCSRL_R_PERI_FIFONotEmpty(void)
{
    GH_USB_TXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_PERI_FIFONotEmpty] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.fifonotempty;
}
GH_INLINE U8   GH_USB_get_TXCSRL_R_PERI_UnderRun(void)
{
    GH_USB_TXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_PERI_UnderRun] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.underrun;
}
GH_INLINE U8   GH_USB_get_TXCSRL_R_PERI_SendStall(void)
{
    GH_USB_TXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_PERI_SendStall] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.sendstall;
}
GH_INLINE U8   GH_USB_get_TXCSRL_R_PERI_SentStall(void)
{
    GH_USB_TXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_PERI_SentStall] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.sentstall;
}
GH_INLINE U8   GH_USB_get_TXCSRL_R_PERI_IncompTx(void)
{
    GH_USB_TXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_PERI_IncompTx] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.incomptx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRH_R_PERI (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_TXCSRH_R_PERI'. */
U8   GH_USB_get_TXCSRH_R_PERI(void);
/*! \brief Reads the bit group 'DMAReqMode' of register 'USB_TXCSRH_R_PERI'. */
U8   GH_USB_get_TXCSRH_R_PERI_DMAReqMode(void);
/*! \brief Reads the bit group 'FrcDataTog' of register 'USB_TXCSRH_R_PERI'. */
U8   GH_USB_get_TXCSRH_R_PERI_FrcDataTog(void);
/*! \brief Reads the bit group 'DMAReqEnab' of register 'USB_TXCSRH_R_PERI'. */
U8   GH_USB_get_TXCSRH_R_PERI_DMAReqEnab(void);
/*! \brief Reads the bit group 'Mode' of register 'USB_TXCSRH_R_PERI'. */
U8   GH_USB_get_TXCSRH_R_PERI_Mode(void);
/*! \brief Reads the bit group 'ISO' of register 'USB_TXCSRH_R_PERI'. */
U8   GH_USB_get_TXCSRH_R_PERI_ISO(void);
/*! \brief Reads the bit group 'AutoSet' of register 'USB_TXCSRH_R_PERI'. */
U8   GH_USB_get_TXCSRH_R_PERI_AutoSet(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_TXCSRH_R_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_PERI] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_PERI,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_TXCSRH_R_PERI_DMAReqMode(void)
{
    GH_USB_TXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_PERI_DMAReqMode] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.dmareqmode;
}
GH_INLINE U8   GH_USB_get_TXCSRH_R_PERI_FrcDataTog(void)
{
    GH_USB_TXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_PERI_FrcDataTog] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.frcdatatog;
}
GH_INLINE U8   GH_USB_get_TXCSRH_R_PERI_DMAReqEnab(void)
{
    GH_USB_TXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_PERI_DMAReqEnab] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.dmareqenab;
}
GH_INLINE U8   GH_USB_get_TXCSRH_R_PERI_Mode(void)
{
    GH_USB_TXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_PERI_Mode] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.mode;
}
GH_INLINE U8   GH_USB_get_TXCSRH_R_PERI_ISO(void)
{
    GH_USB_TXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_PERI_ISO] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.iso;
}
GH_INLINE U8   GH_USB_get_TXCSRH_R_PERI_AutoSet(void)
{
    GH_USB_TXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_PERI_AutoSet] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.autoset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRL_W_PERI (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_TXCSRL_W_PERI'. */
void GH_USB_set_TXCSRL_W_PERI(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_TXCSRL_W_PERI'. */
U8   GH_USB_getm_TXCSRL_W_PERI(void);
/*! \brief Writes the bit group 'TxPktRdy' of register 'USB_TXCSRL_W_PERI'. */
void GH_USB_set_TXCSRL_W_PERI_TxPktRdy(U8 data);
/*! \brief Reads the bit group 'TxPktRdy' from the mirror variable of register 'USB_TXCSRL_W_PERI'. */
U8   GH_USB_getm_TXCSRL_W_PERI_TxPktRdy(void);
/*! \brief Writes the bit group 'FIFONotEmpty' of register 'USB_TXCSRL_W_PERI'. */
void GH_USB_set_TXCSRL_W_PERI_FIFONotEmpty(U8 data);
/*! \brief Reads the bit group 'FIFONotEmpty' from the mirror variable of register 'USB_TXCSRL_W_PERI'. */
U8   GH_USB_getm_TXCSRL_W_PERI_FIFONotEmpty(void);
/*! \brief Writes the bit group 'UnderRun' of register 'USB_TXCSRL_W_PERI'. */
void GH_USB_set_TXCSRL_W_PERI_UnderRun(U8 data);
/*! \brief Reads the bit group 'UnderRun' from the mirror variable of register 'USB_TXCSRL_W_PERI'. */
U8   GH_USB_getm_TXCSRL_W_PERI_UnderRun(void);
/*! \brief Writes the bit group 'FlushFIFO' of register 'USB_TXCSRL_W_PERI'. */
void GH_USB_set_TXCSRL_W_PERI_FlushFIFO(U8 data);
/*! \brief Reads the bit group 'FlushFIFO' from the mirror variable of register 'USB_TXCSRL_W_PERI'. */
U8   GH_USB_getm_TXCSRL_W_PERI_FlushFIFO(void);
/*! \brief Writes the bit group 'SendStall' of register 'USB_TXCSRL_W_PERI'. */
void GH_USB_set_TXCSRL_W_PERI_SendStall(U8 data);
/*! \brief Reads the bit group 'SendStall' from the mirror variable of register 'USB_TXCSRL_W_PERI'. */
U8   GH_USB_getm_TXCSRL_W_PERI_SendStall(void);
/*! \brief Writes the bit group 'SentStall' of register 'USB_TXCSRL_W_PERI'. */
void GH_USB_set_TXCSRL_W_PERI_SentStall(U8 data);
/*! \brief Reads the bit group 'SentStall' from the mirror variable of register 'USB_TXCSRL_W_PERI'. */
U8   GH_USB_getm_TXCSRL_W_PERI_SentStall(void);
/*! \brief Writes the bit group 'ClrDataTog' of register 'USB_TXCSRL_W_PERI'. */
void GH_USB_set_TXCSRL_W_PERI_ClrDataTog(U8 data);
/*! \brief Reads the bit group 'ClrDataTog' from the mirror variable of register 'USB_TXCSRL_W_PERI'. */
U8   GH_USB_getm_TXCSRL_W_PERI_ClrDataTog(void);
/*! \brief Writes the bit group 'IncompTx' of register 'USB_TXCSRL_W_PERI'. */
void GH_USB_set_TXCSRL_W_PERI_IncompTx(U8 data);
/*! \brief Reads the bit group 'IncompTx' from the mirror variable of register 'USB_TXCSRL_W_PERI'. */
U8   GH_USB_getm_TXCSRL_W_PERI_IncompTx(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_TXCSRL_W_PERI(U8 data)
{
    m_usb_txcsrl_w_peri.all = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_PERI(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.all);
    #endif
    return m_usb_txcsrl_w_peri.all;
}
GH_INLINE void GH_USB_set_TXCSRL_W_PERI_TxPktRdy(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.txpktrdy = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_TxPktRdy] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_PERI_TxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_TxPktRdy] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.txpktrdy);
    #endif
    return m_usb_txcsrl_w_peri.bitc.txpktrdy;
}
GH_INLINE void GH_USB_set_TXCSRL_W_PERI_FIFONotEmpty(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.fifonotempty = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_FIFONotEmpty] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_PERI_FIFONotEmpty(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_FIFONotEmpty] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.fifonotempty);
    #endif
    return m_usb_txcsrl_w_peri.bitc.fifonotempty;
}
GH_INLINE void GH_USB_set_TXCSRL_W_PERI_UnderRun(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.underrun = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_UnderRun] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_PERI_UnderRun(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_UnderRun] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.underrun);
    #endif
    return m_usb_txcsrl_w_peri.bitc.underrun;
}
GH_INLINE void GH_USB_set_TXCSRL_W_PERI_FlushFIFO(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.flushfifo = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_FlushFIFO] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_PERI_FlushFIFO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_FlushFIFO] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.flushfifo);
    #endif
    return m_usb_txcsrl_w_peri.bitc.flushfifo;
}
GH_INLINE void GH_USB_set_TXCSRL_W_PERI_SendStall(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.sendstall = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_SendStall] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_PERI_SendStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_SendStall] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.sendstall);
    #endif
    return m_usb_txcsrl_w_peri.bitc.sendstall;
}
GH_INLINE void GH_USB_set_TXCSRL_W_PERI_SentStall(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.sentstall = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_SentStall] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_PERI_SentStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_SentStall] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.sentstall);
    #endif
    return m_usb_txcsrl_w_peri.bitc.sentstall;
}
GH_INLINE void GH_USB_set_TXCSRL_W_PERI_ClrDataTog(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.clrdatatog = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_ClrDataTog] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_PERI_ClrDataTog(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_ClrDataTog] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.clrdatatog);
    #endif
    return m_usb_txcsrl_w_peri.bitc.clrdatatog;
}
GH_INLINE void GH_USB_set_TXCSRL_W_PERI_IncompTx(U8 data)
{
    m_usb_txcsrl_w_peri.bitc.incomptx = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_PERI = m_usb_txcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_PERI_IncompTx] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_PERI,m_usb_txcsrl_w_peri.all,m_usb_txcsrl_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_PERI_IncompTx(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_PERI_IncompTx] --> 0x%08x\n",
                        m_usb_txcsrl_w_peri.bitc.incomptx);
    #endif
    return m_usb_txcsrl_w_peri.bitc.incomptx;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRH_W_PERI (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_TXCSRH_W_PERI'. */
void GH_USB_set_TXCSRH_W_PERI(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_TXCSRH_W_PERI'. */
U8   GH_USB_getm_TXCSRH_W_PERI(void);
/*! \brief Writes the bit group 'DMAReqMode' of register 'USB_TXCSRH_W_PERI'. */
void GH_USB_set_TXCSRH_W_PERI_DMAReqMode(U8 data);
/*! \brief Reads the bit group 'DMAReqMode' from the mirror variable of register 'USB_TXCSRH_W_PERI'. */
U8   GH_USB_getm_TXCSRH_W_PERI_DMAReqMode(void);
/*! \brief Writes the bit group 'FrcDataTog' of register 'USB_TXCSRH_W_PERI'. */
void GH_USB_set_TXCSRH_W_PERI_FrcDataTog(U8 data);
/*! \brief Reads the bit group 'FrcDataTog' from the mirror variable of register 'USB_TXCSRH_W_PERI'. */
U8   GH_USB_getm_TXCSRH_W_PERI_FrcDataTog(void);
/*! \brief Writes the bit group 'DMAReqEnab' of register 'USB_TXCSRH_W_PERI'. */
void GH_USB_set_TXCSRH_W_PERI_DMAReqEnab(U8 data);
/*! \brief Reads the bit group 'DMAReqEnab' from the mirror variable of register 'USB_TXCSRH_W_PERI'. */
U8   GH_USB_getm_TXCSRH_W_PERI_DMAReqEnab(void);
/*! \brief Writes the bit group 'Mode' of register 'USB_TXCSRH_W_PERI'. */
void GH_USB_set_TXCSRH_W_PERI_Mode(U8 data);
/*! \brief Reads the bit group 'Mode' from the mirror variable of register 'USB_TXCSRH_W_PERI'. */
U8   GH_USB_getm_TXCSRH_W_PERI_Mode(void);
/*! \brief Writes the bit group 'ISO' of register 'USB_TXCSRH_W_PERI'. */
void GH_USB_set_TXCSRH_W_PERI_ISO(U8 data);
/*! \brief Reads the bit group 'ISO' from the mirror variable of register 'USB_TXCSRH_W_PERI'. */
U8   GH_USB_getm_TXCSRH_W_PERI_ISO(void);
/*! \brief Writes the bit group 'AutoSet' of register 'USB_TXCSRH_W_PERI'. */
void GH_USB_set_TXCSRH_W_PERI_AutoSet(U8 data);
/*! \brief Reads the bit group 'AutoSet' from the mirror variable of register 'USB_TXCSRH_W_PERI'. */
U8   GH_USB_getm_TXCSRH_W_PERI_AutoSet(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_TXCSRH_W_PERI(U8 data)
{
    m_usb_txcsrh_w_peri.all = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_PERI] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_PERI,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_PERI(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_PERI] --> 0x%08x\n",
                        m_usb_txcsrh_w_peri.all);
    #endif
    return m_usb_txcsrh_w_peri.all;
}
GH_INLINE void GH_USB_set_TXCSRH_W_PERI_DMAReqMode(U8 data)
{
    m_usb_txcsrh_w_peri.bitc.dmareqmode = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_PERI = m_usb_txcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_PERI_DMAReqMode] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_PERI,m_usb_txcsrh_w_peri.all,m_usb_txcsrh_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_PERI_DMAReqMode(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_PERI_DMAReqMode] --> 0x%08x\n",
                        m_usb_txcsrh_w_peri.bitc.dmareqmode);
    #endif
    return m_usb_txcsrh_w_peri.bitc.dmareqmode;
}
GH_INLINE void GH_USB_set_TXCSRH_W_PERI_FrcDataTog(U8 data)
{
    m_usb_txcsrh_w_peri.bitc.frcdatatog = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_PERI = m_usb_txcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_PERI_FrcDataTog] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_PERI,m_usb_txcsrh_w_peri.all,m_usb_txcsrh_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_PERI_FrcDataTog(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_PERI_FrcDataTog] --> 0x%08x\n",
                        m_usb_txcsrh_w_peri.bitc.frcdatatog);
    #endif
    return m_usb_txcsrh_w_peri.bitc.frcdatatog;
}
GH_INLINE void GH_USB_set_TXCSRH_W_PERI_DMAReqEnab(U8 data)
{
    m_usb_txcsrh_w_peri.bitc.dmareqenab = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_PERI = m_usb_txcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_PERI_DMAReqEnab] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_PERI,m_usb_txcsrh_w_peri.all,m_usb_txcsrh_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_PERI_DMAReqEnab(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_PERI_DMAReqEnab] --> 0x%08x\n",
                        m_usb_txcsrh_w_peri.bitc.dmareqenab);
    #endif
    return m_usb_txcsrh_w_peri.bitc.dmareqenab;
}
GH_INLINE void GH_USB_set_TXCSRH_W_PERI_Mode(U8 data)
{
    m_usb_txcsrh_w_peri.bitc.mode = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_PERI = m_usb_txcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_PERI_Mode] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_PERI,m_usb_txcsrh_w_peri.all,m_usb_txcsrh_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_PERI_Mode(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_PERI_Mode] --> 0x%08x\n",
                        m_usb_txcsrh_w_peri.bitc.mode);
    #endif
    return m_usb_txcsrh_w_peri.bitc.mode;
}
GH_INLINE void GH_USB_set_TXCSRH_W_PERI_ISO(U8 data)
{
    m_usb_txcsrh_w_peri.bitc.iso = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_PERI = m_usb_txcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_PERI_ISO] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_PERI,m_usb_txcsrh_w_peri.all,m_usb_txcsrh_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_PERI_ISO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_PERI_ISO] --> 0x%08x\n",
                        m_usb_txcsrh_w_peri.bitc.iso);
    #endif
    return m_usb_txcsrh_w_peri.bitc.iso;
}
GH_INLINE void GH_USB_set_TXCSRH_W_PERI_AutoSet(U8 data)
{
    m_usb_txcsrh_w_peri.bitc.autoset = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_PERI = m_usb_txcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_PERI_AutoSet] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_PERI,m_usb_txcsrh_w_peri.all,m_usb_txcsrh_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_PERI_AutoSet(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_PERI_AutoSet] --> 0x%08x\n",
                        m_usb_txcsrh_w_peri.bitc.autoset);
    #endif
    return m_usb_txcsrh_w_peri.bitc.autoset;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRL_R_HOST (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_TXCSRL_R_HOST'. */
U8   GH_USB_get_TXCSRL_R_HOST(void);
/*! \brief Reads the bit group 'TxPktRdy' of register 'USB_TXCSRL_R_HOST'. */
U8   GH_USB_get_TXCSRL_R_HOST_TxPktRdy(void);
/*! \brief Reads the bit group 'FIFONotEmpty' of register 'USB_TXCSRL_R_HOST'. */
U8   GH_USB_get_TXCSRL_R_HOST_FIFONotEmpty(void);
/*! \brief Reads the bit group 'Error' of register 'USB_TXCSRL_R_HOST'. */
U8   GH_USB_get_TXCSRL_R_HOST_Error(void);
/*! \brief Reads the bit group 'SetupPkt' of register 'USB_TXCSRL_R_HOST'. */
U8   GH_USB_get_TXCSRL_R_HOST_SetupPkt(void);
/*! \brief Reads the bit group 'RxStall' of register 'USB_TXCSRL_R_HOST'. */
U8   GH_USB_get_TXCSRL_R_HOST_RxStall(void);
/*! \brief Reads the bit group 'IncompTx' of register 'USB_TXCSRL_R_HOST'. */
U8   GH_USB_get_TXCSRL_R_HOST_IncompTx(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_TXCSRL_R_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_HOST] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_HOST,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_TXCSRL_R_HOST_TxPktRdy(void)
{
    GH_USB_TXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_HOST_TxPktRdy] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.txpktrdy;
}
GH_INLINE U8   GH_USB_get_TXCSRL_R_HOST_FIFONotEmpty(void)
{
    GH_USB_TXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_HOST_FIFONotEmpty] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.fifonotempty;
}
GH_INLINE U8   GH_USB_get_TXCSRL_R_HOST_Error(void)
{
    GH_USB_TXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_HOST_Error] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.error;
}
GH_INLINE U8   GH_USB_get_TXCSRL_R_HOST_SetupPkt(void)
{
    GH_USB_TXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_HOST_SetupPkt] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.setuppkt;
}
GH_INLINE U8   GH_USB_get_TXCSRL_R_HOST_RxStall(void)
{
    GH_USB_TXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_HOST_RxStall] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.rxstall;
}
GH_INLINE U8   GH_USB_get_TXCSRL_R_HOST_IncompTx(void)
{
    GH_USB_TXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRL_R_HOST_IncompTx] --> 0x%08x\n",
                        REG_USB_TXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.incomptx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRH_R_HOST (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_TXCSRH_R_HOST'. */
U8   GH_USB_get_TXCSRH_R_HOST(void);
/*! \brief Reads the bit group 'DataToggle' of register 'USB_TXCSRH_R_HOST'. */
U8   GH_USB_get_TXCSRH_R_HOST_DataToggle(void);
/*! \brief Reads the bit group 'DMAReqMode' of register 'USB_TXCSRH_R_HOST'. */
U8   GH_USB_get_TXCSRH_R_HOST_DMAReqMode(void);
/*! \brief Reads the bit group 'FrcDataTog' of register 'USB_TXCSRH_R_HOST'. */
U8   GH_USB_get_TXCSRH_R_HOST_FrcDataTog(void);
/*! \brief Reads the bit group 'DMAReqEnab' of register 'USB_TXCSRH_R_HOST'. */
U8   GH_USB_get_TXCSRH_R_HOST_DMAReqEnab(void);
/*! \brief Reads the bit group 'Mode' of register 'USB_TXCSRH_R_HOST'. */
U8   GH_USB_get_TXCSRH_R_HOST_Mode(void);
/*! \brief Reads the bit group 'AutoSet' of register 'USB_TXCSRH_R_HOST'. */
U8   GH_USB_get_TXCSRH_R_HOST_AutoSet(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_TXCSRH_R_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_HOST] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_HOST,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_TXCSRH_R_HOST_DataToggle(void)
{
    GH_USB_TXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_HOST_DataToggle] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.datatoggle;
}
GH_INLINE U8   GH_USB_get_TXCSRH_R_HOST_DMAReqMode(void)
{
    GH_USB_TXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_HOST_DMAReqMode] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.dmareqmode;
}
GH_INLINE U8   GH_USB_get_TXCSRH_R_HOST_FrcDataTog(void)
{
    GH_USB_TXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_HOST_FrcDataTog] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.frcdatatog;
}
GH_INLINE U8   GH_USB_get_TXCSRH_R_HOST_DMAReqEnab(void)
{
    GH_USB_TXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_HOST_DMAReqEnab] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.dmareqenab;
}
GH_INLINE U8   GH_USB_get_TXCSRH_R_HOST_Mode(void)
{
    GH_USB_TXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_HOST_Mode] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.mode;
}
GH_INLINE U8   GH_USB_get_TXCSRH_R_HOST_AutoSet(void)
{
    GH_USB_TXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TXCSRH_R_HOST_AutoSet] --> 0x%08x\n",
                        REG_USB_TXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.autoset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRL_W_HOST (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_TXCSRL_W_HOST'. */
void GH_USB_set_TXCSRL_W_HOST(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_TXCSRL_W_HOST'. */
U8   GH_USB_getm_TXCSRL_W_HOST(void);
/*! \brief Writes the bit group 'TxPktRdy' of register 'USB_TXCSRL_W_HOST'. */
void GH_USB_set_TXCSRL_W_HOST_TxPktRdy(U8 data);
/*! \brief Reads the bit group 'TxPktRdy' from the mirror variable of register 'USB_TXCSRL_W_HOST'. */
U8   GH_USB_getm_TXCSRL_W_HOST_TxPktRdy(void);
/*! \brief Writes the bit group 'FIFONotEmpty' of register 'USB_TXCSRL_W_HOST'. */
void GH_USB_set_TXCSRL_W_HOST_FIFONotEmpty(U8 data);
/*! \brief Reads the bit group 'FIFONotEmpty' from the mirror variable of register 'USB_TXCSRL_W_HOST'. */
U8   GH_USB_getm_TXCSRL_W_HOST_FIFONotEmpty(void);
/*! \brief Writes the bit group 'Error' of register 'USB_TXCSRL_W_HOST'. */
void GH_USB_set_TXCSRL_W_HOST_Error(U8 data);
/*! \brief Reads the bit group 'Error' from the mirror variable of register 'USB_TXCSRL_W_HOST'. */
U8   GH_USB_getm_TXCSRL_W_HOST_Error(void);
/*! \brief Writes the bit group 'FlushFIFO' of register 'USB_TXCSRL_W_HOST'. */
void GH_USB_set_TXCSRL_W_HOST_FlushFIFO(U8 data);
/*! \brief Reads the bit group 'FlushFIFO' from the mirror variable of register 'USB_TXCSRL_W_HOST'. */
U8   GH_USB_getm_TXCSRL_W_HOST_FlushFIFO(void);
/*! \brief Writes the bit group 'SetupPkt' of register 'USB_TXCSRL_W_HOST'. */
void GH_USB_set_TXCSRL_W_HOST_SetupPkt(U8 data);
/*! \brief Reads the bit group 'SetupPkt' from the mirror variable of register 'USB_TXCSRL_W_HOST'. */
U8   GH_USB_getm_TXCSRL_W_HOST_SetupPkt(void);
/*! \brief Writes the bit group 'RxStall' of register 'USB_TXCSRL_W_HOST'. */
void GH_USB_set_TXCSRL_W_HOST_RxStall(U8 data);
/*! \brief Reads the bit group 'RxStall' from the mirror variable of register 'USB_TXCSRL_W_HOST'. */
U8   GH_USB_getm_TXCSRL_W_HOST_RxStall(void);
/*! \brief Writes the bit group 'ClrDataTog' of register 'USB_TXCSRL_W_HOST'. */
void GH_USB_set_TXCSRL_W_HOST_ClrDataTog(U8 data);
/*! \brief Reads the bit group 'ClrDataTog' from the mirror variable of register 'USB_TXCSRL_W_HOST'. */
U8   GH_USB_getm_TXCSRL_W_HOST_ClrDataTog(void);
/*! \brief Writes the bit group 'IncompTx' of register 'USB_TXCSRL_W_HOST'. */
void GH_USB_set_TXCSRL_W_HOST_IncompTx(U8 data);
/*! \brief Reads the bit group 'IncompTx' from the mirror variable of register 'USB_TXCSRL_W_HOST'. */
U8   GH_USB_getm_TXCSRL_W_HOST_IncompTx(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_TXCSRL_W_HOST(U8 data)
{
    m_usb_txcsrl_w_host.all = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_HOST(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.all);
    #endif
    return m_usb_txcsrl_w_host.all;
}
GH_INLINE void GH_USB_set_TXCSRL_W_HOST_TxPktRdy(U8 data)
{
    m_usb_txcsrl_w_host.bitc.txpktrdy = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_TxPktRdy] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_HOST_TxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_TxPktRdy] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.txpktrdy);
    #endif
    return m_usb_txcsrl_w_host.bitc.txpktrdy;
}
GH_INLINE void GH_USB_set_TXCSRL_W_HOST_FIFONotEmpty(U8 data)
{
    m_usb_txcsrl_w_host.bitc.fifonotempty = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_FIFONotEmpty] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_HOST_FIFONotEmpty(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_FIFONotEmpty] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.fifonotempty);
    #endif
    return m_usb_txcsrl_w_host.bitc.fifonotempty;
}
GH_INLINE void GH_USB_set_TXCSRL_W_HOST_Error(U8 data)
{
    m_usb_txcsrl_w_host.bitc.error = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_Error] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_HOST_Error(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_Error] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.error);
    #endif
    return m_usb_txcsrl_w_host.bitc.error;
}
GH_INLINE void GH_USB_set_TXCSRL_W_HOST_FlushFIFO(U8 data)
{
    m_usb_txcsrl_w_host.bitc.flushfifo = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_FlushFIFO] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_HOST_FlushFIFO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_FlushFIFO] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.flushfifo);
    #endif
    return m_usb_txcsrl_w_host.bitc.flushfifo;
}
GH_INLINE void GH_USB_set_TXCSRL_W_HOST_SetupPkt(U8 data)
{
    m_usb_txcsrl_w_host.bitc.setuppkt = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_SetupPkt] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_HOST_SetupPkt(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_SetupPkt] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.setuppkt);
    #endif
    return m_usb_txcsrl_w_host.bitc.setuppkt;
}
GH_INLINE void GH_USB_set_TXCSRL_W_HOST_RxStall(U8 data)
{
    m_usb_txcsrl_w_host.bitc.rxstall = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_RxStall] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_HOST_RxStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_RxStall] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.rxstall);
    #endif
    return m_usb_txcsrl_w_host.bitc.rxstall;
}
GH_INLINE void GH_USB_set_TXCSRL_W_HOST_ClrDataTog(U8 data)
{
    m_usb_txcsrl_w_host.bitc.clrdatatog = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_ClrDataTog] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_HOST_ClrDataTog(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_ClrDataTog] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.clrdatatog);
    #endif
    return m_usb_txcsrl_w_host.bitc.clrdatatog;
}
GH_INLINE void GH_USB_set_TXCSRL_W_HOST_IncompTx(U8 data)
{
    m_usb_txcsrl_w_host.bitc.incomptx = data;
    *(volatile U8 *)REG_USB_TXCSRL_W_HOST = m_usb_txcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRL_W_HOST_IncompTx] <-- 0x%08x\n",
                        REG_USB_TXCSRL_W_HOST,m_usb_txcsrl_w_host.all,m_usb_txcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRL_W_HOST_IncompTx(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRL_W_HOST_IncompTx] --> 0x%08x\n",
                        m_usb_txcsrl_w_host.bitc.incomptx);
    #endif
    return m_usb_txcsrl_w_host.bitc.incomptx;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_TXCSRH_W_HOST (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_TXCSRH_W_HOST'. */
void GH_USB_set_TXCSRH_W_HOST(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_TXCSRH_W_HOST'. */
U8   GH_USB_getm_TXCSRH_W_HOST(void);
/*! \brief Writes the bit group 'DataToggle' of register 'USB_TXCSRH_W_HOST'. */
void GH_USB_set_TXCSRH_W_HOST_DataToggle(U8 data);
/*! \brief Reads the bit group 'DataToggle' from the mirror variable of register 'USB_TXCSRH_W_HOST'. */
U8   GH_USB_getm_TXCSRH_W_HOST_DataToggle(void);
/*! \brief Writes the bit group 'DataToggleWriteEnable' of register 'USB_TXCSRH_W_HOST'. */
void GH_USB_set_TXCSRH_W_HOST_DataToggleWriteEnable(U8 data);
/*! \brief Reads the bit group 'DataToggleWriteEnable' from the mirror variable of register 'USB_TXCSRH_W_HOST'. */
U8   GH_USB_getm_TXCSRH_W_HOST_DataToggleWriteEnable(void);
/*! \brief Writes the bit group 'DMAReqMode' of register 'USB_TXCSRH_W_HOST'. */
void GH_USB_set_TXCSRH_W_HOST_DMAReqMode(U8 data);
/*! \brief Reads the bit group 'DMAReqMode' from the mirror variable of register 'USB_TXCSRH_W_HOST'. */
U8   GH_USB_getm_TXCSRH_W_HOST_DMAReqMode(void);
/*! \brief Writes the bit group 'FrcDataTog' of register 'USB_TXCSRH_W_HOST'. */
void GH_USB_set_TXCSRH_W_HOST_FrcDataTog(U8 data);
/*! \brief Reads the bit group 'FrcDataTog' from the mirror variable of register 'USB_TXCSRH_W_HOST'. */
U8   GH_USB_getm_TXCSRH_W_HOST_FrcDataTog(void);
/*! \brief Writes the bit group 'DMAReqEnab' of register 'USB_TXCSRH_W_HOST'. */
void GH_USB_set_TXCSRH_W_HOST_DMAReqEnab(U8 data);
/*! \brief Reads the bit group 'DMAReqEnab' from the mirror variable of register 'USB_TXCSRH_W_HOST'. */
U8   GH_USB_getm_TXCSRH_W_HOST_DMAReqEnab(void);
/*! \brief Writes the bit group 'Mode' of register 'USB_TXCSRH_W_HOST'. */
void GH_USB_set_TXCSRH_W_HOST_Mode(U8 data);
/*! \brief Reads the bit group 'Mode' from the mirror variable of register 'USB_TXCSRH_W_HOST'. */
U8   GH_USB_getm_TXCSRH_W_HOST_Mode(void);
/*! \brief Writes the bit group 'AutoSet' of register 'USB_TXCSRH_W_HOST'. */
void GH_USB_set_TXCSRH_W_HOST_AutoSet(U8 data);
/*! \brief Reads the bit group 'AutoSet' from the mirror variable of register 'USB_TXCSRH_W_HOST'. */
U8   GH_USB_getm_TXCSRH_W_HOST_AutoSet(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_TXCSRH_W_HOST(U8 data)
{
    m_usb_txcsrh_w_host.all = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_HOST(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.all);
    #endif
    return m_usb_txcsrh_w_host.all;
}
GH_INLINE void GH_USB_set_TXCSRH_W_HOST_DataToggle(U8 data)
{
    m_usb_txcsrh_w_host.bitc.datatoggle = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = m_usb_txcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST_DataToggle] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,m_usb_txcsrh_w_host.all,m_usb_txcsrh_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_HOST_DataToggle(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST_DataToggle] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.bitc.datatoggle);
    #endif
    return m_usb_txcsrh_w_host.bitc.datatoggle;
}
GH_INLINE void GH_USB_set_TXCSRH_W_HOST_DataToggleWriteEnable(U8 data)
{
    m_usb_txcsrh_w_host.bitc.datatogglewriteenable = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = m_usb_txcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST_DataToggleWriteEnable] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,m_usb_txcsrh_w_host.all,m_usb_txcsrh_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_HOST_DataToggleWriteEnable(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST_DataToggleWriteEnable] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.bitc.datatogglewriteenable);
    #endif
    return m_usb_txcsrh_w_host.bitc.datatogglewriteenable;
}
GH_INLINE void GH_USB_set_TXCSRH_W_HOST_DMAReqMode(U8 data)
{
    m_usb_txcsrh_w_host.bitc.dmareqmode = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = m_usb_txcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST_DMAReqMode] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,m_usb_txcsrh_w_host.all,m_usb_txcsrh_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_HOST_DMAReqMode(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST_DMAReqMode] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.bitc.dmareqmode);
    #endif
    return m_usb_txcsrh_w_host.bitc.dmareqmode;
}
GH_INLINE void GH_USB_set_TXCSRH_W_HOST_FrcDataTog(U8 data)
{
    m_usb_txcsrh_w_host.bitc.frcdatatog = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = m_usb_txcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST_FrcDataTog] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,m_usb_txcsrh_w_host.all,m_usb_txcsrh_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_HOST_FrcDataTog(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST_FrcDataTog] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.bitc.frcdatatog);
    #endif
    return m_usb_txcsrh_w_host.bitc.frcdatatog;
}
GH_INLINE void GH_USB_set_TXCSRH_W_HOST_DMAReqEnab(U8 data)
{
    m_usb_txcsrh_w_host.bitc.dmareqenab = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = m_usb_txcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST_DMAReqEnab] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,m_usb_txcsrh_w_host.all,m_usb_txcsrh_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_HOST_DMAReqEnab(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST_DMAReqEnab] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.bitc.dmareqenab);
    #endif
    return m_usb_txcsrh_w_host.bitc.dmareqenab;
}
GH_INLINE void GH_USB_set_TXCSRH_W_HOST_Mode(U8 data)
{
    m_usb_txcsrh_w_host.bitc.mode = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = m_usb_txcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST_Mode] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,m_usb_txcsrh_w_host.all,m_usb_txcsrh_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_HOST_Mode(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST_Mode] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.bitc.mode);
    #endif
    return m_usb_txcsrh_w_host.bitc.mode;
}
GH_INLINE void GH_USB_set_TXCSRH_W_HOST_AutoSet(U8 data)
{
    m_usb_txcsrh_w_host.bitc.autoset = data;
    *(volatile U8 *)REG_USB_TXCSRH_W_HOST = m_usb_txcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TXCSRH_W_HOST_AutoSet] <-- 0x%08x\n",
                        REG_USB_TXCSRH_W_HOST,m_usb_txcsrh_w_host.all,m_usb_txcsrh_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_TXCSRH_W_HOST_AutoSet(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_TXCSRH_W_HOST_AutoSet] --> 0x%08x\n",
                        m_usb_txcsrh_w_host.bitc.autoset);
    #endif
    return m_usb_txcsrh_w_host.bitc.autoset;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_RxMaxP (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_RxMaxP'. */
void GH_USB_set_RxMaxP(U16 data);
/*! \brief Reads the register 'USB_RxMaxP'. */
U16  GH_USB_get_RxMaxP(void);
/*! \brief Writes the bit group 'TxMaxP' of register 'USB_RxMaxP'. */
void GH_USB_set_RxMaxP_TxMaxP(U16 data);
/*! \brief Reads the bit group 'TxMaxP' of register 'USB_RxMaxP'. */
U16  GH_USB_get_RxMaxP_TxMaxP(void);
/*! \brief Writes the bit group 'multiplier' of register 'USB_RxMaxP'. */
void GH_USB_set_RxMaxP_multiplier(U8 data);
/*! \brief Reads the bit group 'multiplier' of register 'USB_RxMaxP'. */
U8   GH_USB_get_RxMaxP_multiplier(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_RxMaxP(U16 data)
{
    *(volatile U16 *)REG_USB_RXMAXP = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxMaxP] <-- 0x%08x\n",
                        REG_USB_RXMAXP,data,data);
    #endif
}
GH_INLINE U16  GH_USB_get_RxMaxP(void)
{
    U16 value = (*(volatile U16 *)REG_USB_RXMAXP);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxMaxP] --> 0x%08x\n",
                        REG_USB_RXMAXP,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_RxMaxP_TxMaxP(U16 data)
{
    GH_USB_RXMAXP_S d;
    d.all = *(volatile U16 *)REG_USB_RXMAXP;
    d.bitc.txmaxp = data;
    *(volatile U16 *)REG_USB_RXMAXP = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxMaxP_TxMaxP] <-- 0x%08x\n",
                        REG_USB_RXMAXP,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_USB_get_RxMaxP_TxMaxP(void)
{
    GH_USB_RXMAXP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXMAXP);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxMaxP_TxMaxP] --> 0x%08x\n",
                        REG_USB_RXMAXP,value);
    #endif
    return tmp_value.bitc.txmaxp;
}
GH_INLINE void GH_USB_set_RxMaxP_multiplier(U8 data)
{
    GH_USB_RXMAXP_S d;
    d.all = *(volatile U16 *)REG_USB_RXMAXP;
    d.bitc.multiplier = data;
    *(volatile U16 *)REG_USB_RXMAXP = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxMaxP_multiplier] <-- 0x%08x\n",
                        REG_USB_RXMAXP,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxMaxP_multiplier(void)
{
    GH_USB_RXMAXP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXMAXP);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxMaxP_multiplier] --> 0x%08x\n",
                        REG_USB_RXMAXP,value);
    #endif
    return tmp_value.bitc.multiplier;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRL_R_PERI (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_RXCSRL_R_PERI'. */
U8   GH_USB_get_RXCSRL_R_PERI(void);
/*! \brief Reads the bit group 'RxPktRdy' of register 'USB_RXCSRL_R_PERI'. */
U8   GH_USB_get_RXCSRL_R_PERI_RxPktRdy(void);
/*! \brief Reads the bit group 'FIFOFull' of register 'USB_RXCSRL_R_PERI'. */
U8   GH_USB_get_RXCSRL_R_PERI_FIFOFull(void);
/*! \brief Reads the bit group 'OverRun' of register 'USB_RXCSRL_R_PERI'. */
U8   GH_USB_get_RXCSRL_R_PERI_OverRun(void);
/*! \brief Reads the bit group 'DataError' of register 'USB_RXCSRL_R_PERI'. */
U8   GH_USB_get_RXCSRL_R_PERI_DataError(void);
/*! \brief Reads the bit group 'SendStall' of register 'USB_RXCSRL_R_PERI'. */
U8   GH_USB_get_RXCSRL_R_PERI_SendStall(void);
/*! \brief Reads the bit group 'SentStall' of register 'USB_RXCSRL_R_PERI'. */
U8   GH_USB_get_RXCSRL_R_PERI_SentStall(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_RXCSRL_R_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_PERI] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_PERI,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_RXCSRL_R_PERI_RxPktRdy(void)
{
    GH_USB_RXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_PERI_RxPktRdy] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.rxpktrdy;
}
GH_INLINE U8   GH_USB_get_RXCSRL_R_PERI_FIFOFull(void)
{
    GH_USB_RXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_PERI_FIFOFull] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.fifofull;
}
GH_INLINE U8   GH_USB_get_RXCSRL_R_PERI_OverRun(void)
{
    GH_USB_RXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_PERI_OverRun] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.overrun;
}
GH_INLINE U8   GH_USB_get_RXCSRL_R_PERI_DataError(void)
{
    GH_USB_RXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_PERI_DataError] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.dataerror;
}
GH_INLINE U8   GH_USB_get_RXCSRL_R_PERI_SendStall(void)
{
    GH_USB_RXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_PERI_SendStall] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.sendstall;
}
GH_INLINE U8   GH_USB_get_RXCSRL_R_PERI_SentStall(void)
{
    GH_USB_RXCSRL_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_PERI_SentStall] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_PERI,value);
    #endif
    return tmp_value.bitc.sentstall;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRH_R_PERI (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_RXCSRH_R_PERI'. */
U8   GH_USB_get_RXCSRH_R_PERI(void);
/*! \brief Reads the bit group 'IncompRx' of register 'USB_RXCSRH_R_PERI'. */
U8   GH_USB_get_RXCSRH_R_PERI_IncompRx(void);
/*! \brief Reads the bit group 'DMAReqMode' of register 'USB_RXCSRH_R_PERI'. */
U8   GH_USB_get_RXCSRH_R_PERI_DMAReqMode(void);
/*! \brief Reads the bit group 'DisNyet_PIDError' of register 'USB_RXCSRH_R_PERI'. */
U8   GH_USB_get_RXCSRH_R_PERI_DisNyet_PIDError(void);
/*! \brief Reads the bit group 'DMAReqEnab' of register 'USB_RXCSRH_R_PERI'. */
U8   GH_USB_get_RXCSRH_R_PERI_DMAReqEnab(void);
/*! \brief Reads the bit group 'ISO' of register 'USB_RXCSRH_R_PERI'. */
U8   GH_USB_get_RXCSRH_R_PERI_ISO(void);
/*! \brief Reads the bit group 'AutoClear' of register 'USB_RXCSRH_R_PERI'. */
U8   GH_USB_get_RXCSRH_R_PERI_AutoClear(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_RXCSRH_R_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_PERI] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_PERI,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_RXCSRH_R_PERI_IncompRx(void)
{
    GH_USB_RXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_PERI_IncompRx] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.incomprx;
}
GH_INLINE U8   GH_USB_get_RXCSRH_R_PERI_DMAReqMode(void)
{
    GH_USB_RXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_PERI_DMAReqMode] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.dmareqmode;
}
GH_INLINE U8   GH_USB_get_RXCSRH_R_PERI_DisNyet_PIDError(void)
{
    GH_USB_RXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_PERI_DisNyet_PIDError] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.disnyet_piderror;
}
GH_INLINE U8   GH_USB_get_RXCSRH_R_PERI_DMAReqEnab(void)
{
    GH_USB_RXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_PERI_DMAReqEnab] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.dmareqenab;
}
GH_INLINE U8   GH_USB_get_RXCSRH_R_PERI_ISO(void)
{
    GH_USB_RXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_PERI_ISO] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.iso;
}
GH_INLINE U8   GH_USB_get_RXCSRH_R_PERI_AutoClear(void)
{
    GH_USB_RXCSRH_R_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_PERI_AutoClear] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_PERI,value);
    #endif
    return tmp_value.bitc.autoclear;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRL_W_PERI (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_RXCSRL_W_PERI'. */
void GH_USB_set_RXCSRL_W_PERI(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_RXCSRL_W_PERI'. */
U8   GH_USB_getm_RXCSRL_W_PERI(void);
/*! \brief Writes the bit group 'RxPktRdy' of register 'USB_RXCSRL_W_PERI'. */
void GH_USB_set_RXCSRL_W_PERI_RxPktRdy(U8 data);
/*! \brief Reads the bit group 'RxPktRdy' from the mirror variable of register 'USB_RXCSRL_W_PERI'. */
U8   GH_USB_getm_RXCSRL_W_PERI_RxPktRdy(void);
/*! \brief Writes the bit group 'OverRun' of register 'USB_RXCSRL_W_PERI'. */
void GH_USB_set_RXCSRL_W_PERI_OverRun(U8 data);
/*! \brief Reads the bit group 'OverRun' from the mirror variable of register 'USB_RXCSRL_W_PERI'. */
U8   GH_USB_getm_RXCSRL_W_PERI_OverRun(void);
/*! \brief Writes the bit group 'FlushFIFO' of register 'USB_RXCSRL_W_PERI'. */
void GH_USB_set_RXCSRL_W_PERI_FlushFIFO(U8 data);
/*! \brief Reads the bit group 'FlushFIFO' from the mirror variable of register 'USB_RXCSRL_W_PERI'. */
U8   GH_USB_getm_RXCSRL_W_PERI_FlushFIFO(void);
/*! \brief Writes the bit group 'SendStall' of register 'USB_RXCSRL_W_PERI'. */
void GH_USB_set_RXCSRL_W_PERI_SendStall(U8 data);
/*! \brief Reads the bit group 'SendStall' from the mirror variable of register 'USB_RXCSRL_W_PERI'. */
U8   GH_USB_getm_RXCSRL_W_PERI_SendStall(void);
/*! \brief Writes the bit group 'SentStall' of register 'USB_RXCSRL_W_PERI'. */
void GH_USB_set_RXCSRL_W_PERI_SentStall(U8 data);
/*! \brief Reads the bit group 'SentStall' from the mirror variable of register 'USB_RXCSRL_W_PERI'. */
U8   GH_USB_getm_RXCSRL_W_PERI_SentStall(void);
/*! \brief Writes the bit group 'ClrDataTog' of register 'USB_RXCSRL_W_PERI'. */
void GH_USB_set_RXCSRL_W_PERI_ClrDataTog(U8 data);
/*! \brief Reads the bit group 'ClrDataTog' from the mirror variable of register 'USB_RXCSRL_W_PERI'. */
U8   GH_USB_getm_RXCSRL_W_PERI_ClrDataTog(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_RXCSRL_W_PERI(U8 data)
{
    m_usb_rxcsrl_w_peri.all = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_PERI] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_PERI,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_PERI(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_PERI] --> 0x%08x\n",
                        m_usb_rxcsrl_w_peri.all);
    #endif
    return m_usb_rxcsrl_w_peri.all;
}
GH_INLINE void GH_USB_set_RXCSRL_W_PERI_RxPktRdy(U8 data)
{
    m_usb_rxcsrl_w_peri.bitc.rxpktrdy = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_PERI = m_usb_rxcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_PERI_RxPktRdy] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_PERI,m_usb_rxcsrl_w_peri.all,m_usb_rxcsrl_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_PERI_RxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_PERI_RxPktRdy] --> 0x%08x\n",
                        m_usb_rxcsrl_w_peri.bitc.rxpktrdy);
    #endif
    return m_usb_rxcsrl_w_peri.bitc.rxpktrdy;
}
GH_INLINE void GH_USB_set_RXCSRL_W_PERI_OverRun(U8 data)
{
    m_usb_rxcsrl_w_peri.bitc.overrun = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_PERI = m_usb_rxcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_PERI_OverRun] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_PERI,m_usb_rxcsrl_w_peri.all,m_usb_rxcsrl_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_PERI_OverRun(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_PERI_OverRun] --> 0x%08x\n",
                        m_usb_rxcsrl_w_peri.bitc.overrun);
    #endif
    return m_usb_rxcsrl_w_peri.bitc.overrun;
}
GH_INLINE void GH_USB_set_RXCSRL_W_PERI_FlushFIFO(U8 data)
{
    m_usb_rxcsrl_w_peri.bitc.flushfifo = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_PERI = m_usb_rxcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_PERI_FlushFIFO] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_PERI,m_usb_rxcsrl_w_peri.all,m_usb_rxcsrl_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_PERI_FlushFIFO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_PERI_FlushFIFO] --> 0x%08x\n",
                        m_usb_rxcsrl_w_peri.bitc.flushfifo);
    #endif
    return m_usb_rxcsrl_w_peri.bitc.flushfifo;
}
GH_INLINE void GH_USB_set_RXCSRL_W_PERI_SendStall(U8 data)
{
    m_usb_rxcsrl_w_peri.bitc.sendstall = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_PERI = m_usb_rxcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_PERI_SendStall] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_PERI,m_usb_rxcsrl_w_peri.all,m_usb_rxcsrl_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_PERI_SendStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_PERI_SendStall] --> 0x%08x\n",
                        m_usb_rxcsrl_w_peri.bitc.sendstall);
    #endif
    return m_usb_rxcsrl_w_peri.bitc.sendstall;
}
GH_INLINE void GH_USB_set_RXCSRL_W_PERI_SentStall(U8 data)
{
    m_usb_rxcsrl_w_peri.bitc.sentstall = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_PERI = m_usb_rxcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_PERI_SentStall] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_PERI,m_usb_rxcsrl_w_peri.all,m_usb_rxcsrl_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_PERI_SentStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_PERI_SentStall] --> 0x%08x\n",
                        m_usb_rxcsrl_w_peri.bitc.sentstall);
    #endif
    return m_usb_rxcsrl_w_peri.bitc.sentstall;
}
GH_INLINE void GH_USB_set_RXCSRL_W_PERI_ClrDataTog(U8 data)
{
    m_usb_rxcsrl_w_peri.bitc.clrdatatog = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_PERI = m_usb_rxcsrl_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_PERI_ClrDataTog] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_PERI,m_usb_rxcsrl_w_peri.all,m_usb_rxcsrl_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_PERI_ClrDataTog(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_PERI_ClrDataTog] --> 0x%08x\n",
                        m_usb_rxcsrl_w_peri.bitc.clrdatatog);
    #endif
    return m_usb_rxcsrl_w_peri.bitc.clrdatatog;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRH_W_PERI (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_RXCSRH_W_PERI'. */
void GH_USB_set_RXCSRH_W_PERI(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_RXCSRH_W_PERI'. */
U8   GH_USB_getm_RXCSRH_W_PERI(void);
/*! \brief Writes the bit group 'IncompRx' of register 'USB_RXCSRH_W_PERI'. */
void GH_USB_set_RXCSRH_W_PERI_IncompRx(U8 data);
/*! \brief Reads the bit group 'IncompRx' from the mirror variable of register 'USB_RXCSRH_W_PERI'. */
U8   GH_USB_getm_RXCSRH_W_PERI_IncompRx(void);
/*! \brief Writes the bit group 'DMAReqMode' of register 'USB_RXCSRH_W_PERI'. */
void GH_USB_set_RXCSRH_W_PERI_DMAReqMode(U8 data);
/*! \brief Reads the bit group 'DMAReqMode' from the mirror variable of register 'USB_RXCSRH_W_PERI'. */
U8   GH_USB_getm_RXCSRH_W_PERI_DMAReqMode(void);
/*! \brief Writes the bit group 'DisNyet_PIDError' of register 'USB_RXCSRH_W_PERI'. */
void GH_USB_set_RXCSRH_W_PERI_DisNyet_PIDError(U8 data);
/*! \brief Reads the bit group 'DisNyet_PIDError' from the mirror variable of register 'USB_RXCSRH_W_PERI'. */
U8   GH_USB_getm_RXCSRH_W_PERI_DisNyet_PIDError(void);
/*! \brief Writes the bit group 'DMAReqEnab' of register 'USB_RXCSRH_W_PERI'. */
void GH_USB_set_RXCSRH_W_PERI_DMAReqEnab(U8 data);
/*! \brief Reads the bit group 'DMAReqEnab' from the mirror variable of register 'USB_RXCSRH_W_PERI'. */
U8   GH_USB_getm_RXCSRH_W_PERI_DMAReqEnab(void);
/*! \brief Writes the bit group 'ISO' of register 'USB_RXCSRH_W_PERI'. */
void GH_USB_set_RXCSRH_W_PERI_ISO(U8 data);
/*! \brief Reads the bit group 'ISO' from the mirror variable of register 'USB_RXCSRH_W_PERI'. */
U8   GH_USB_getm_RXCSRH_W_PERI_ISO(void);
/*! \brief Writes the bit group 'AutoClear' of register 'USB_RXCSRH_W_PERI'. */
void GH_USB_set_RXCSRH_W_PERI_AutoClear(U8 data);
/*! \brief Reads the bit group 'AutoClear' from the mirror variable of register 'USB_RXCSRH_W_PERI'. */
U8   GH_USB_getm_RXCSRH_W_PERI_AutoClear(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_RXCSRH_W_PERI(U8 data)
{
    m_usb_rxcsrh_w_peri.all = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_PERI] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_PERI,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRH_W_PERI(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_PERI] --> 0x%08x\n",
                        m_usb_rxcsrh_w_peri.all);
    #endif
    return m_usb_rxcsrh_w_peri.all;
}
GH_INLINE void GH_USB_set_RXCSRH_W_PERI_IncompRx(U8 data)
{
    m_usb_rxcsrh_w_peri.bitc.incomprx = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_PERI = m_usb_rxcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_PERI_IncompRx] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_PERI,m_usb_rxcsrh_w_peri.all,m_usb_rxcsrh_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRH_W_PERI_IncompRx(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_PERI_IncompRx] --> 0x%08x\n",
                        m_usb_rxcsrh_w_peri.bitc.incomprx);
    #endif
    return m_usb_rxcsrh_w_peri.bitc.incomprx;
}
GH_INLINE void GH_USB_set_RXCSRH_W_PERI_DMAReqMode(U8 data)
{
    m_usb_rxcsrh_w_peri.bitc.dmareqmode = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_PERI = m_usb_rxcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_PERI_DMAReqMode] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_PERI,m_usb_rxcsrh_w_peri.all,m_usb_rxcsrh_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRH_W_PERI_DMAReqMode(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_PERI_DMAReqMode] --> 0x%08x\n",
                        m_usb_rxcsrh_w_peri.bitc.dmareqmode);
    #endif
    return m_usb_rxcsrh_w_peri.bitc.dmareqmode;
}
GH_INLINE void GH_USB_set_RXCSRH_W_PERI_DisNyet_PIDError(U8 data)
{
    m_usb_rxcsrh_w_peri.bitc.disnyet_piderror = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_PERI = m_usb_rxcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_PERI_DisNyet_PIDError] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_PERI,m_usb_rxcsrh_w_peri.all,m_usb_rxcsrh_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRH_W_PERI_DisNyet_PIDError(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_PERI_DisNyet_PIDError] --> 0x%08x\n",
                        m_usb_rxcsrh_w_peri.bitc.disnyet_piderror);
    #endif
    return m_usb_rxcsrh_w_peri.bitc.disnyet_piderror;
}
GH_INLINE void GH_USB_set_RXCSRH_W_PERI_DMAReqEnab(U8 data)
{
    m_usb_rxcsrh_w_peri.bitc.dmareqenab = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_PERI = m_usb_rxcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_PERI_DMAReqEnab] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_PERI,m_usb_rxcsrh_w_peri.all,m_usb_rxcsrh_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRH_W_PERI_DMAReqEnab(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_PERI_DMAReqEnab] --> 0x%08x\n",
                        m_usb_rxcsrh_w_peri.bitc.dmareqenab);
    #endif
    return m_usb_rxcsrh_w_peri.bitc.dmareqenab;
}
GH_INLINE void GH_USB_set_RXCSRH_W_PERI_ISO(U8 data)
{
    m_usb_rxcsrh_w_peri.bitc.iso = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_PERI = m_usb_rxcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_PERI_ISO] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_PERI,m_usb_rxcsrh_w_peri.all,m_usb_rxcsrh_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRH_W_PERI_ISO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_PERI_ISO] --> 0x%08x\n",
                        m_usb_rxcsrh_w_peri.bitc.iso);
    #endif
    return m_usb_rxcsrh_w_peri.bitc.iso;
}
GH_INLINE void GH_USB_set_RXCSRH_W_PERI_AutoClear(U8 data)
{
    m_usb_rxcsrh_w_peri.bitc.autoclear = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_PERI = m_usb_rxcsrh_w_peri.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_PERI_AutoClear] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_PERI,m_usb_rxcsrh_w_peri.all,m_usb_rxcsrh_w_peri.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRH_W_PERI_AutoClear(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_PERI_AutoClear] --> 0x%08x\n",
                        m_usb_rxcsrh_w_peri.bitc.autoclear);
    #endif
    return m_usb_rxcsrh_w_peri.bitc.autoclear;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRL_R_HOST (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_RXCSRL_R_HOST'. */
U8   GH_USB_get_RXCSRL_R_HOST(void);
/*! \brief Reads the bit group 'RxPktRdy' of register 'USB_RXCSRL_R_HOST'. */
U8   GH_USB_get_RXCSRL_R_HOST_RxPktRdy(void);
/*! \brief Reads the bit group 'FIFOFull' of register 'USB_RXCSRL_R_HOST'. */
U8   GH_USB_get_RXCSRL_R_HOST_FIFOFull(void);
/*! \brief Reads the bit group 'Error' of register 'USB_RXCSRL_R_HOST'. */
U8   GH_USB_get_RXCSRL_R_HOST_Error(void);
/*! \brief Reads the bit group 'DataError_NAKTimeout' of register 'USB_RXCSRL_R_HOST'. */
U8   GH_USB_get_RXCSRL_R_HOST_DataError_NAKTimeout(void);
/*! \brief Reads the bit group 'ReqPkt' of register 'USB_RXCSRL_R_HOST'. */
U8   GH_USB_get_RXCSRL_R_HOST_ReqPkt(void);
/*! \brief Reads the bit group 'RxStall' of register 'USB_RXCSRL_R_HOST'. */
U8   GH_USB_get_RXCSRL_R_HOST_RxStall(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_RXCSRL_R_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_HOST] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_HOST,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_RXCSRL_R_HOST_RxPktRdy(void)
{
    GH_USB_RXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_HOST_RxPktRdy] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.rxpktrdy;
}
GH_INLINE U8   GH_USB_get_RXCSRL_R_HOST_FIFOFull(void)
{
    GH_USB_RXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_HOST_FIFOFull] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.fifofull;
}
GH_INLINE U8   GH_USB_get_RXCSRL_R_HOST_Error(void)
{
    GH_USB_RXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_HOST_Error] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.error;
}
GH_INLINE U8   GH_USB_get_RXCSRL_R_HOST_DataError_NAKTimeout(void)
{
    GH_USB_RXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_HOST_DataError_NAKTimeout] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.dataerror_naktimeout;
}
GH_INLINE U8   GH_USB_get_RXCSRL_R_HOST_ReqPkt(void)
{
    GH_USB_RXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_HOST_ReqPkt] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.reqpkt;
}
GH_INLINE U8   GH_USB_get_RXCSRL_R_HOST_RxStall(void)
{
    GH_USB_RXCSRL_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRL_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRL_R_HOST_RxStall] --> 0x%08x\n",
                        REG_USB_RXCSRL_R_HOST,value);
    #endif
    return tmp_value.bitc.rxstall;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRH_R_HOST (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_RXCSRH_R_HOST'. */
U8   GH_USB_get_RXCSRH_R_HOST(void);
/*! \brief Reads the bit group 'IncompRx' of register 'USB_RXCSRH_R_HOST'. */
U8   GH_USB_get_RXCSRH_R_HOST_IncompRx(void);
/*! \brief Reads the bit group 'DataToggle' of register 'USB_RXCSRH_R_HOST'. */
U8   GH_USB_get_RXCSRH_R_HOST_DataToggle(void);
/*! \brief Reads the bit group 'DataToggleWriteEnable' of register 'USB_RXCSRH_R_HOST'. */
U8   GH_USB_get_RXCSRH_R_HOST_DataToggleWriteEnable(void);
/*! \brief Reads the bit group 'DMAReqMode' of register 'USB_RXCSRH_R_HOST'. */
U8   GH_USB_get_RXCSRH_R_HOST_DMAReqMode(void);
/*! \brief Reads the bit group 'PIDError' of register 'USB_RXCSRH_R_HOST'. */
U8   GH_USB_get_RXCSRH_R_HOST_PIDError(void);
/*! \brief Reads the bit group 'DMAReqEnab' of register 'USB_RXCSRH_R_HOST'. */
U8   GH_USB_get_RXCSRH_R_HOST_DMAReqEnab(void);
/*! \brief Reads the bit group 'AutoReq' of register 'USB_RXCSRH_R_HOST'. */
U8   GH_USB_get_RXCSRH_R_HOST_AutoReq(void);
/*! \brief Reads the bit group 'AutoClear' of register 'USB_RXCSRH_R_HOST'. */
U8   GH_USB_get_RXCSRH_R_HOST_AutoClear(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_RXCSRH_R_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_RXCSRH_R_HOST_IncompRx(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_IncompRx] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.incomprx;
}
GH_INLINE U8   GH_USB_get_RXCSRH_R_HOST_DataToggle(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_DataToggle] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.datatoggle;
}
GH_INLINE U8   GH_USB_get_RXCSRH_R_HOST_DataToggleWriteEnable(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_DataToggleWriteEnable] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.datatogglewriteenable;
}
GH_INLINE U8   GH_USB_get_RXCSRH_R_HOST_DMAReqMode(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_DMAReqMode] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.dmareqmode;
}
GH_INLINE U8   GH_USB_get_RXCSRH_R_HOST_PIDError(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_PIDError] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.piderror;
}
GH_INLINE U8   GH_USB_get_RXCSRH_R_HOST_DMAReqEnab(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_DMAReqEnab] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.dmareqenab;
}
GH_INLINE U8   GH_USB_get_RXCSRH_R_HOST_AutoReq(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_AutoReq] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.autoreq;
}
GH_INLINE U8   GH_USB_get_RXCSRH_R_HOST_AutoClear(void)
{
    GH_USB_RXCSRH_R_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCSRH_R_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RXCSRH_R_HOST_AutoClear] --> 0x%08x\n",
                        REG_USB_RXCSRH_R_HOST,value);
    #endif
    return tmp_value.bitc.autoclear;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRL_W_HOST (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_RXCSRL_W_HOST'. */
void GH_USB_set_RXCSRL_W_HOST(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_RXCSRL_W_HOST'. */
U8   GH_USB_getm_RXCSRL_W_HOST(void);
/*! \brief Writes the bit group 'RxPktRdy' of register 'USB_RXCSRL_W_HOST'. */
void GH_USB_set_RXCSRL_W_HOST_RxPktRdy(U8 data);
/*! \brief Reads the bit group 'RxPktRdy' from the mirror variable of register 'USB_RXCSRL_W_HOST'. */
U8   GH_USB_getm_RXCSRL_W_HOST_RxPktRdy(void);
/*! \brief Writes the bit group 'Error' of register 'USB_RXCSRL_W_HOST'. */
void GH_USB_set_RXCSRL_W_HOST_Error(U8 data);
/*! \brief Reads the bit group 'Error' from the mirror variable of register 'USB_RXCSRL_W_HOST'. */
U8   GH_USB_getm_RXCSRL_W_HOST_Error(void);
/*! \brief Writes the bit group 'DataError_NAKTimeout' of register 'USB_RXCSRL_W_HOST'. */
void GH_USB_set_RXCSRL_W_HOST_DataError_NAKTimeout(U8 data);
/*! \brief Reads the bit group 'DataError_NAKTimeout' from the mirror variable of register 'USB_RXCSRL_W_HOST'. */
U8   GH_USB_getm_RXCSRL_W_HOST_DataError_NAKTimeout(void);
/*! \brief Writes the bit group 'FlushFIFO' of register 'USB_RXCSRL_W_HOST'. */
void GH_USB_set_RXCSRL_W_HOST_FlushFIFO(U8 data);
/*! \brief Reads the bit group 'FlushFIFO' from the mirror variable of register 'USB_RXCSRL_W_HOST'. */
U8   GH_USB_getm_RXCSRL_W_HOST_FlushFIFO(void);
/*! \brief Writes the bit group 'ReqPkt' of register 'USB_RXCSRL_W_HOST'. */
void GH_USB_set_RXCSRL_W_HOST_ReqPkt(U8 data);
/*! \brief Reads the bit group 'ReqPkt' from the mirror variable of register 'USB_RXCSRL_W_HOST'. */
U8   GH_USB_getm_RXCSRL_W_HOST_ReqPkt(void);
/*! \brief Writes the bit group 'RxStall' of register 'USB_RXCSRL_W_HOST'. */
void GH_USB_set_RXCSRL_W_HOST_RxStall(U8 data);
/*! \brief Reads the bit group 'RxStall' from the mirror variable of register 'USB_RXCSRL_W_HOST'. */
U8   GH_USB_getm_RXCSRL_W_HOST_RxStall(void);
/*! \brief Writes the bit group 'ClrDataTog' of register 'USB_RXCSRL_W_HOST'. */
void GH_USB_set_RXCSRL_W_HOST_ClrDataTog(U8 data);
/*! \brief Reads the bit group 'ClrDataTog' from the mirror variable of register 'USB_RXCSRL_W_HOST'. */
U8   GH_USB_getm_RXCSRL_W_HOST_ClrDataTog(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_RXCSRL_W_HOST(U8 data)
{
    m_usb_rxcsrl_w_host.all = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_HOST(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.all);
    #endif
    return m_usb_rxcsrl_w_host.all;
}
GH_INLINE void GH_USB_set_RXCSRL_W_HOST_RxPktRdy(U8 data)
{
    m_usb_rxcsrl_w_host.bitc.rxpktrdy = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = m_usb_rxcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST_RxPktRdy] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,m_usb_rxcsrl_w_host.all,m_usb_rxcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_HOST_RxPktRdy(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST_RxPktRdy] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.bitc.rxpktrdy);
    #endif
    return m_usb_rxcsrl_w_host.bitc.rxpktrdy;
}
GH_INLINE void GH_USB_set_RXCSRL_W_HOST_Error(U8 data)
{
    m_usb_rxcsrl_w_host.bitc.error = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = m_usb_rxcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST_Error] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,m_usb_rxcsrl_w_host.all,m_usb_rxcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_HOST_Error(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST_Error] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.bitc.error);
    #endif
    return m_usb_rxcsrl_w_host.bitc.error;
}
GH_INLINE void GH_USB_set_RXCSRL_W_HOST_DataError_NAKTimeout(U8 data)
{
    m_usb_rxcsrl_w_host.bitc.dataerror_naktimeout = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = m_usb_rxcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST_DataError_NAKTimeout] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,m_usb_rxcsrl_w_host.all,m_usb_rxcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_HOST_DataError_NAKTimeout(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST_DataError_NAKTimeout] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.bitc.dataerror_naktimeout);
    #endif
    return m_usb_rxcsrl_w_host.bitc.dataerror_naktimeout;
}
GH_INLINE void GH_USB_set_RXCSRL_W_HOST_FlushFIFO(U8 data)
{
    m_usb_rxcsrl_w_host.bitc.flushfifo = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = m_usb_rxcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST_FlushFIFO] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,m_usb_rxcsrl_w_host.all,m_usb_rxcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_HOST_FlushFIFO(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST_FlushFIFO] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.bitc.flushfifo);
    #endif
    return m_usb_rxcsrl_w_host.bitc.flushfifo;
}
GH_INLINE void GH_USB_set_RXCSRL_W_HOST_ReqPkt(U8 data)
{
    m_usb_rxcsrl_w_host.bitc.reqpkt = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = m_usb_rxcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST_ReqPkt] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,m_usb_rxcsrl_w_host.all,m_usb_rxcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_HOST_ReqPkt(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST_ReqPkt] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.bitc.reqpkt);
    #endif
    return m_usb_rxcsrl_w_host.bitc.reqpkt;
}
GH_INLINE void GH_USB_set_RXCSRL_W_HOST_RxStall(U8 data)
{
    m_usb_rxcsrl_w_host.bitc.rxstall = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = m_usb_rxcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST_RxStall] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,m_usb_rxcsrl_w_host.all,m_usb_rxcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_HOST_RxStall(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST_RxStall] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.bitc.rxstall);
    #endif
    return m_usb_rxcsrl_w_host.bitc.rxstall;
}
GH_INLINE void GH_USB_set_RXCSRL_W_HOST_ClrDataTog(U8 data)
{
    m_usb_rxcsrl_w_host.bitc.clrdatatog = data;
    *(volatile U8 *)REG_USB_RXCSRL_W_HOST = m_usb_rxcsrl_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRL_W_HOST_ClrDataTog] <-- 0x%08x\n",
                        REG_USB_RXCSRL_W_HOST,m_usb_rxcsrl_w_host.all,m_usb_rxcsrl_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRL_W_HOST_ClrDataTog(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRL_W_HOST_ClrDataTog] --> 0x%08x\n",
                        m_usb_rxcsrl_w_host.bitc.clrdatatog);
    #endif
    return m_usb_rxcsrl_w_host.bitc.clrdatatog;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_RXCSRH_W_HOST (write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_RXCSRH_W_HOST'. */
void GH_USB_set_RXCSRH_W_HOST(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_RXCSRH_W_HOST'. */
U8   GH_USB_getm_RXCSRH_W_HOST(void);
/*! \brief Writes the bit group 'IncompRx' of register 'USB_RXCSRH_W_HOST'. */
void GH_USB_set_RXCSRH_W_HOST_IncompRx(U8 data);
/*! \brief Reads the bit group 'IncompRx' from the mirror variable of register 'USB_RXCSRH_W_HOST'. */
U8   GH_USB_getm_RXCSRH_W_HOST_IncompRx(void);
/*! \brief Writes the bit group 'DMAReqMode' of register 'USB_RXCSRH_W_HOST'. */
void GH_USB_set_RXCSRH_W_HOST_DMAReqMode(U8 data);
/*! \brief Reads the bit group 'DMAReqMode' from the mirror variable of register 'USB_RXCSRH_W_HOST'. */
U8   GH_USB_getm_RXCSRH_W_HOST_DMAReqMode(void);
/*! \brief Writes the bit group 'DMAReqEnab' of register 'USB_RXCSRH_W_HOST'. */
void GH_USB_set_RXCSRH_W_HOST_DMAReqEnab(U8 data);
/*! \brief Reads the bit group 'DMAReqEnab' from the mirror variable of register 'USB_RXCSRH_W_HOST'. */
U8   GH_USB_getm_RXCSRH_W_HOST_DMAReqEnab(void);
/*! \brief Writes the bit group 'AutoReq' of register 'USB_RXCSRH_W_HOST'. */
void GH_USB_set_RXCSRH_W_HOST_AutoReq(U8 data);
/*! \brief Reads the bit group 'AutoReq' from the mirror variable of register 'USB_RXCSRH_W_HOST'. */
U8   GH_USB_getm_RXCSRH_W_HOST_AutoReq(void);
/*! \brief Writes the bit group 'AutoClear' of register 'USB_RXCSRH_W_HOST'. */
void GH_USB_set_RXCSRH_W_HOST_AutoClear(U8 data);
/*! \brief Reads the bit group 'AutoClear' from the mirror variable of register 'USB_RXCSRH_W_HOST'. */
U8   GH_USB_getm_RXCSRH_W_HOST_AutoClear(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_RXCSRH_W_HOST(U8 data)
{
    m_usb_rxcsrh_w_host.all = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_HOST] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_HOST,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRH_W_HOST(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_HOST] --> 0x%08x\n",
                        m_usb_rxcsrh_w_host.all);
    #endif
    return m_usb_rxcsrh_w_host.all;
}
GH_INLINE void GH_USB_set_RXCSRH_W_HOST_IncompRx(U8 data)
{
    m_usb_rxcsrh_w_host.bitc.incomprx = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_HOST = m_usb_rxcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_HOST_IncompRx] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_HOST,m_usb_rxcsrh_w_host.all,m_usb_rxcsrh_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRH_W_HOST_IncompRx(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_HOST_IncompRx] --> 0x%08x\n",
                        m_usb_rxcsrh_w_host.bitc.incomprx);
    #endif
    return m_usb_rxcsrh_w_host.bitc.incomprx;
}
GH_INLINE void GH_USB_set_RXCSRH_W_HOST_DMAReqMode(U8 data)
{
    m_usb_rxcsrh_w_host.bitc.dmareqmode = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_HOST = m_usb_rxcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_HOST_DMAReqMode] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_HOST,m_usb_rxcsrh_w_host.all,m_usb_rxcsrh_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRH_W_HOST_DMAReqMode(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_HOST_DMAReqMode] --> 0x%08x\n",
                        m_usb_rxcsrh_w_host.bitc.dmareqmode);
    #endif
    return m_usb_rxcsrh_w_host.bitc.dmareqmode;
}
GH_INLINE void GH_USB_set_RXCSRH_W_HOST_DMAReqEnab(U8 data)
{
    m_usb_rxcsrh_w_host.bitc.dmareqenab = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_HOST = m_usb_rxcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_HOST_DMAReqEnab] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_HOST,m_usb_rxcsrh_w_host.all,m_usb_rxcsrh_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRH_W_HOST_DMAReqEnab(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_HOST_DMAReqEnab] --> 0x%08x\n",
                        m_usb_rxcsrh_w_host.bitc.dmareqenab);
    #endif
    return m_usb_rxcsrh_w_host.bitc.dmareqenab;
}
GH_INLINE void GH_USB_set_RXCSRH_W_HOST_AutoReq(U8 data)
{
    m_usb_rxcsrh_w_host.bitc.autoreq = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_HOST = m_usb_rxcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_HOST_AutoReq] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_HOST,m_usb_rxcsrh_w_host.all,m_usb_rxcsrh_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRH_W_HOST_AutoReq(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_HOST_AutoReq] --> 0x%08x\n",
                        m_usb_rxcsrh_w_host.bitc.autoreq);
    #endif
    return m_usb_rxcsrh_w_host.bitc.autoreq;
}
GH_INLINE void GH_USB_set_RXCSRH_W_HOST_AutoClear(U8 data)
{
    m_usb_rxcsrh_w_host.bitc.autoclear = data;
    *(volatile U8 *)REG_USB_RXCSRH_W_HOST = m_usb_rxcsrh_w_host.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RXCSRH_W_HOST_AutoClear] <-- 0x%08x\n",
                        REG_USB_RXCSRH_W_HOST,m_usb_rxcsrh_w_host.all,m_usb_rxcsrh_w_host.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_RXCSRH_W_HOST_AutoClear(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_RXCSRH_W_HOST_AutoClear] --> 0x%08x\n",
                        m_usb_rxcsrh_w_host.bitc.autoclear);
    #endif
    return m_usb_rxcsrh_w_host.bitc.autoclear;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_RxCount (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_RxCount'. */
U8   GH_USB_get_RxCount(void);
/*! \brief Reads the bit group 'EndpointRxCount' of register 'USB_RxCount'. */
U8   GH_USB_get_RxCount_EndpointRxCount(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_RxCount(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXCOUNT);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxCount] --> 0x%08x\n",
                        REG_USB_RXCOUNT,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_RxCount_EndpointRxCount(void)
{
    GH_USB_RXCOUNT_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXCOUNT);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxCount_EndpointRxCount] --> 0x%08x\n",
                        REG_USB_RXCOUNT,value);
    #endif
    return tmp_value.bitc.endpointrxcount;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxType_HOST (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_TxType_HOST'. */
void GH_USB_set_TxType_HOST(U8 data);
/*! \brief Reads the register 'USB_TxType_HOST'. */
U8   GH_USB_get_TxType_HOST(void);
/*! \brief Writes the bit group 'TargetEndpointNumber' of register 'USB_TxType_HOST'. */
void GH_USB_set_TxType_HOST_TargetEndpointNumber(U8 data);
/*! \brief Reads the bit group 'TargetEndpointNumber' of register 'USB_TxType_HOST'. */
U8   GH_USB_get_TxType_HOST_TargetEndpointNumber(void);
/*! \brief Writes the bit group 'Protocol' of register 'USB_TxType_HOST'. */
void GH_USB_set_TxType_HOST_Protocol(U8 data);
/*! \brief Reads the bit group 'Protocol' of register 'USB_TxType_HOST'. */
U8   GH_USB_get_TxType_HOST_Protocol(void);
/*! \brief Writes the bit group 'Speed' of register 'USB_TxType_HOST'. */
void GH_USB_set_TxType_HOST_Speed(U8 data);
/*! \brief Reads the bit group 'Speed' of register 'USB_TxType_HOST'. */
U8   GH_USB_get_TxType_HOST_Speed(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_TxType_HOST(U8 data)
{
    *(volatile U8 *)REG_USB_TXTYPE_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxType_HOST] <-- 0x%08x\n",
                        REG_USB_TXTYPE_HOST,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_TxType_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TXTYPE_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxType_HOST] --> 0x%08x\n",
                        REG_USB_TXTYPE_HOST,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_TxType_HOST_TargetEndpointNumber(U8 data)
{
    GH_USB_TXTYPE_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_TXTYPE_HOST;
    d.bitc.targetendpointnumber = data;
    *(volatile U8 *)REG_USB_TXTYPE_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxType_HOST_TargetEndpointNumber] <-- 0x%08x\n",
                        REG_USB_TXTYPE_HOST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxType_HOST_TargetEndpointNumber(void)
{
    GH_USB_TXTYPE_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXTYPE_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxType_HOST_TargetEndpointNumber] --> 0x%08x\n",
                        REG_USB_TXTYPE_HOST,value);
    #endif
    return tmp_value.bitc.targetendpointnumber;
}
GH_INLINE void GH_USB_set_TxType_HOST_Protocol(U8 data)
{
    GH_USB_TXTYPE_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_TXTYPE_HOST;
    d.bitc.protocol = data;
    *(volatile U8 *)REG_USB_TXTYPE_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxType_HOST_Protocol] <-- 0x%08x\n",
                        REG_USB_TXTYPE_HOST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxType_HOST_Protocol(void)
{
    GH_USB_TXTYPE_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXTYPE_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxType_HOST_Protocol] --> 0x%08x\n",
                        REG_USB_TXTYPE_HOST,value);
    #endif
    return tmp_value.bitc.protocol;
}
GH_INLINE void GH_USB_set_TxType_HOST_Speed(U8 data)
{
    GH_USB_TXTYPE_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_TXTYPE_HOST;
    d.bitc.speed = data;
    *(volatile U8 *)REG_USB_TXTYPE_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxType_HOST_Speed] <-- 0x%08x\n",
                        REG_USB_TXTYPE_HOST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxType_HOST_Speed(void)
{
    GH_USB_TXTYPE_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXTYPE_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxType_HOST_Speed] --> 0x%08x\n",
                        REG_USB_TXTYPE_HOST,value);
    #endif
    return tmp_value.bitc.speed;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxInterval_HOST (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_TxInterval_HOST'. */
void GH_USB_set_TxInterval_HOST(U8 data);
/*! \brief Reads the register 'USB_TxInterval_HOST'. */
U8   GH_USB_get_TxInterval_HOST(void);
/*! \brief Writes the bit group 'TxPollingInterval_NAKLimit' of register 'USB_TxInterval_HOST'. */
void GH_USB_set_TxInterval_HOST_TxPollingInterval_NAKLimit(U8 data);
/*! \brief Reads the bit group 'TxPollingInterval_NAKLimit' of register 'USB_TxInterval_HOST'. */
U8   GH_USB_get_TxInterval_HOST_TxPollingInterval_NAKLimit(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_TxInterval_HOST(U8 data)
{
    *(volatile U8 *)REG_USB_TXINTERVAL_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxInterval_HOST] <-- 0x%08x\n",
                        REG_USB_TXINTERVAL_HOST,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_TxInterval_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TXINTERVAL_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxInterval_HOST] --> 0x%08x\n",
                        REG_USB_TXINTERVAL_HOST,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_TxInterval_HOST_TxPollingInterval_NAKLimit(U8 data)
{
    GH_USB_TXINTERVAL_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_TXINTERVAL_HOST;
    d.bitc.txpollinginterval_naklimit = data;
    *(volatile U8 *)REG_USB_TXINTERVAL_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxInterval_HOST_TxPollingInterval_NAKLimit] <-- 0x%08x\n",
                        REG_USB_TXINTERVAL_HOST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxInterval_HOST_TxPollingInterval_NAKLimit(void)
{
    GH_USB_TXINTERVAL_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXINTERVAL_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxInterval_HOST_TxPollingInterval_NAKLimit] --> 0x%08x\n",
                        REG_USB_TXINTERVAL_HOST,value);
    #endif
    return tmp_value.bitc.txpollinginterval_naklimit;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxType_HOST (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_RxType_HOST'. */
void GH_USB_set_RxType_HOST(U8 data);
/*! \brief Reads the register 'USB_RxType_HOST'. */
U8   GH_USB_get_RxType_HOST(void);
/*! \brief Writes the bit group 'TargetEndpointNumber' of register 'USB_RxType_HOST'. */
void GH_USB_set_RxType_HOST_TargetEndpointNumber(U8 data);
/*! \brief Reads the bit group 'TargetEndpointNumber' of register 'USB_RxType_HOST'. */
U8   GH_USB_get_RxType_HOST_TargetEndpointNumber(void);
/*! \brief Writes the bit group 'Protocol' of register 'USB_RxType_HOST'. */
void GH_USB_set_RxType_HOST_Protocol(U8 data);
/*! \brief Reads the bit group 'Protocol' of register 'USB_RxType_HOST'. */
U8   GH_USB_get_RxType_HOST_Protocol(void);
/*! \brief Writes the bit group 'Speed' of register 'USB_RxType_HOST'. */
void GH_USB_set_RxType_HOST_Speed(U8 data);
/*! \brief Reads the bit group 'Speed' of register 'USB_RxType_HOST'. */
U8   GH_USB_get_RxType_HOST_Speed(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_RxType_HOST(U8 data)
{
    *(volatile U8 *)REG_USB_RXTYPE_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxType_HOST] <-- 0x%08x\n",
                        REG_USB_RXTYPE_HOST,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_RxType_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXTYPE_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxType_HOST] --> 0x%08x\n",
                        REG_USB_RXTYPE_HOST,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_RxType_HOST_TargetEndpointNumber(U8 data)
{
    GH_USB_RXTYPE_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_RXTYPE_HOST;
    d.bitc.targetendpointnumber = data;
    *(volatile U8 *)REG_USB_RXTYPE_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxType_HOST_TargetEndpointNumber] <-- 0x%08x\n",
                        REG_USB_RXTYPE_HOST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxType_HOST_TargetEndpointNumber(void)
{
    GH_USB_RXTYPE_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXTYPE_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxType_HOST_TargetEndpointNumber] --> 0x%08x\n",
                        REG_USB_RXTYPE_HOST,value);
    #endif
    return tmp_value.bitc.targetendpointnumber;
}
GH_INLINE void GH_USB_set_RxType_HOST_Protocol(U8 data)
{
    GH_USB_RXTYPE_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_RXTYPE_HOST;
    d.bitc.protocol = data;
    *(volatile U8 *)REG_USB_RXTYPE_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxType_HOST_Protocol] <-- 0x%08x\n",
                        REG_USB_RXTYPE_HOST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxType_HOST_Protocol(void)
{
    GH_USB_RXTYPE_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXTYPE_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxType_HOST_Protocol] --> 0x%08x\n",
                        REG_USB_RXTYPE_HOST,value);
    #endif
    return tmp_value.bitc.protocol;
}
GH_INLINE void GH_USB_set_RxType_HOST_Speed(U8 data)
{
    GH_USB_RXTYPE_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_RXTYPE_HOST;
    d.bitc.speed = data;
    *(volatile U8 *)REG_USB_RXTYPE_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxType_HOST_Speed] <-- 0x%08x\n",
                        REG_USB_RXTYPE_HOST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxType_HOST_Speed(void)
{
    GH_USB_RXTYPE_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXTYPE_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxType_HOST_Speed] --> 0x%08x\n",
                        REG_USB_RXTYPE_HOST,value);
    #endif
    return tmp_value.bitc.speed;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxInterval_HOST (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_RxInterval_HOST'. */
void GH_USB_set_RxInterval_HOST(U8 data);
/*! \brief Reads the register 'USB_RxInterval_HOST'. */
U8   GH_USB_get_RxInterval_HOST(void);
/*! \brief Writes the bit group 'RxPollingInterval_NAKLimit' of register 'USB_RxInterval_HOST'. */
void GH_USB_set_RxInterval_HOST_RxPollingInterval_NAKLimit(U8 data);
/*! \brief Reads the bit group 'RxPollingInterval_NAKLimit' of register 'USB_RxInterval_HOST'. */
U8   GH_USB_get_RxInterval_HOST_RxPollingInterval_NAKLimit(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_RxInterval_HOST(U8 data)
{
    *(volatile U8 *)REG_USB_RXINTERVAL_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxInterval_HOST] <-- 0x%08x\n",
                        REG_USB_RXINTERVAL_HOST,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_RxInterval_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXINTERVAL_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxInterval_HOST] --> 0x%08x\n",
                        REG_USB_RXINTERVAL_HOST,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_RxInterval_HOST_RxPollingInterval_NAKLimit(U8 data)
{
    GH_USB_RXINTERVAL_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_RXINTERVAL_HOST;
    d.bitc.rxpollinginterval_naklimit = data;
    *(volatile U8 *)REG_USB_RXINTERVAL_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxInterval_HOST_RxPollingInterval_NAKLimit] <-- 0x%08x\n",
                        REG_USB_RXINTERVAL_HOST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxInterval_HOST_RxPollingInterval_NAKLimit(void)
{
    GH_USB_RXINTERVAL_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXINTERVAL_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxInterval_HOST_RxPollingInterval_NAKLimit] --> 0x%08x\n",
                        REG_USB_RXINTERVAL_HOST,value);
    #endif
    return tmp_value.bitc.rxpollinginterval_naklimit;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_FIFOSize (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_FIFOSize'. */
U8   GH_USB_get_FIFOSize(void);
/*! \brief Reads the bit group 'TxFIFOSize' of register 'USB_FIFOSize'. */
U8   GH_USB_get_FIFOSize_TxFIFOSize(void);
/*! \brief Reads the bit group 'RxFIFOSize' of register 'USB_FIFOSize'. */
U8   GH_USB_get_FIFOSize_RxFIFOSize(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_FIFOSize(void)
{
    U8 value = (*(volatile U8 *)REG_USB_FIFOSIZE);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FIFOSize] --> 0x%08x\n",
                        REG_USB_FIFOSIZE,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_FIFOSize_TxFIFOSize(void)
{
    GH_USB_FIFOSIZE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_FIFOSIZE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FIFOSize_TxFIFOSize] --> 0x%08x\n",
                        REG_USB_FIFOSIZE,value);
    #endif
    return tmp_value.bitc.txfifosize;
}
GH_INLINE U8   GH_USB_get_FIFOSize_RxFIFOSize(void)
{
    GH_USB_FIFOSIZE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_FIFOSIZE);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FIFOSize_RxFIFOSize] --> 0x%08x\n",
                        REG_USB_FIFOSIZE,value);
    #endif
    return tmp_value.bitc.rxfifosize;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_FIFOs (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_FIFOs'. */
void GH_USB_set_FIFOs(U8 index, U8 data);
/*! \brief Reads the register 'USB_FIFOs'. */
U8   GH_USB_get_FIFOs(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_FIFOs(U8 index, U8 data)
{
    *(volatile U8 *)(REG_USB_FIFOS + index * FIO_MOFFSET(USB,OFFSET_USB_EP_FIFO)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_FIFOs] <-- 0x%08x\n",
                        (REG_USB_FIFOS + index * FIO_MOFFSET(USB,OFFSET_USB_EP_FIFO)),data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_FIFOs(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_USB_FIFOS + index * FIO_MOFFSET(USB,OFFSET_USB_EP_FIFO)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FIFOs] --> 0x%08x\n",
                        (REG_USB_FIFOS + index * FIO_MOFFSET(USB,OFFSET_USB_EP_FIFO)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_DevCtl_R (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_DevCtl_R'. */
U8   GH_USB_get_DevCtl_R(void);
/*! \brief Reads the bit group 'Session' of register 'USB_DevCtl_R'. */
U8   GH_USB_get_DevCtl_R_Session(void);
/*! \brief Reads the bit group 'Host_Req' of register 'USB_DevCtl_R'. */
U8   GH_USB_get_DevCtl_R_Host_Req(void);
/*! \brief Reads the bit group 'Host_Mode' of register 'USB_DevCtl_R'. */
U8   GH_USB_get_DevCtl_R_Host_Mode(void);
/*! \brief Reads the bit group 'VBus' of register 'USB_DevCtl_R'. */
U8   GH_USB_get_DevCtl_R_VBus(void);
/*! \brief Reads the bit group 'LSDev' of register 'USB_DevCtl_R'. */
U8   GH_USB_get_DevCtl_R_LSDev(void);
/*! \brief Reads the bit group 'FSDev' of register 'USB_DevCtl_R'. */
U8   GH_USB_get_DevCtl_R_FSDev(void);
/*! \brief Reads the bit group 'B_Device' of register 'USB_DevCtl_R'. */
U8   GH_USB_get_DevCtl_R_B_Device(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_DevCtl_R(void)
{
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_DevCtl_R_Session(void)
{
    GH_USB_DEVCTL_R_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R_Session] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return tmp_value.bitc.session;
}
GH_INLINE U8   GH_USB_get_DevCtl_R_Host_Req(void)
{
    GH_USB_DEVCTL_R_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R_Host_Req] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return tmp_value.bitc.host_req;
}
GH_INLINE U8   GH_USB_get_DevCtl_R_Host_Mode(void)
{
    GH_USB_DEVCTL_R_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R_Host_Mode] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return tmp_value.bitc.host_mode;
}
GH_INLINE U8   GH_USB_get_DevCtl_R_VBus(void)
{
    GH_USB_DEVCTL_R_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R_VBus] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return tmp_value.bitc.vbus;
}
GH_INLINE U8   GH_USB_get_DevCtl_R_LSDev(void)
{
    GH_USB_DEVCTL_R_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R_LSDev] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return tmp_value.bitc.lsdev;
}
GH_INLINE U8   GH_USB_get_DevCtl_R_FSDev(void)
{
    GH_USB_DEVCTL_R_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R_FSDev] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return tmp_value.bitc.fsdev;
}
GH_INLINE U8   GH_USB_get_DevCtl_R_B_Device(void)
{
    GH_USB_DEVCTL_R_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DEVCTL_R);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DevCtl_R_B_Device] --> 0x%08x\n",
                        REG_USB_DEVCTL_R,value);
    #endif
    return tmp_value.bitc.b_device;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_DevCtl_W (write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_DevCtl_W'. */
void GH_USB_set_DevCtl_W(U8 data);
/*! \brief Reads the mirror variable of the register 'USB_DevCtl_W'. */
U8   GH_USB_getm_DevCtl_W(void);
/*! \brief Writes the bit group 'Session' of register 'USB_DevCtl_W'. */
void GH_USB_set_DevCtl_W_Session(U8 data);
/*! \brief Reads the bit group 'Session' from the mirror variable of register 'USB_DevCtl_W'. */
U8   GH_USB_getm_DevCtl_W_Session(void);
/*! \brief Writes the bit group 'Host_Req' of register 'USB_DevCtl_W'. */
void GH_USB_set_DevCtl_W_Host_Req(U8 data);
/*! \brief Reads the bit group 'Host_Req' from the mirror variable of register 'USB_DevCtl_W'. */
U8   GH_USB_getm_DevCtl_W_Host_Req(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_DevCtl_W(U8 data)
{
    m_usb_devctl_w.all = data;
    *(volatile U8 *)REG_USB_DEVCTL_W = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DevCtl_W] <-- 0x%08x\n",
                        REG_USB_DEVCTL_W,data,data);
    #endif
}
GH_INLINE U8   GH_USB_getm_DevCtl_W(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_DevCtl_W] --> 0x%08x\n",
                        m_usb_devctl_w.all);
    #endif
    return m_usb_devctl_w.all;
}
GH_INLINE void GH_USB_set_DevCtl_W_Session(U8 data)
{
    m_usb_devctl_w.bitc.session = data;
    *(volatile U8 *)REG_USB_DEVCTL_W = m_usb_devctl_w.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DevCtl_W_Session] <-- 0x%08x\n",
                        REG_USB_DEVCTL_W,m_usb_devctl_w.all,m_usb_devctl_w.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_DevCtl_W_Session(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_DevCtl_W_Session] --> 0x%08x\n",
                        m_usb_devctl_w.bitc.session);
    #endif
    return m_usb_devctl_w.bitc.session;
}
GH_INLINE void GH_USB_set_DevCtl_W_Host_Req(U8 data)
{
    m_usb_devctl_w.bitc.host_req = data;
    *(volatile U8 *)REG_USB_DEVCTL_W = m_usb_devctl_w.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DevCtl_W_Host_Req] <-- 0x%08x\n",
                        REG_USB_DEVCTL_W,m_usb_devctl_w.all,m_usb_devctl_w.all);
    #endif
}
GH_INLINE U8   GH_USB_getm_DevCtl_W_Host_Req(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_DevCtl_W_Host_Req] --> 0x%08x\n",
                        m_usb_devctl_w.bitc.host_req);
    #endif
    return m_usb_devctl_w.bitc.host_req;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_Misc (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_Misc'. */
void GH_USB_set_Misc(U8 data);
/*! \brief Reads the register 'USB_Misc'. */
U8   GH_USB_get_Misc(void);
/*! \brief Writes the bit group 'rx_edma' of register 'USB_Misc'. */
void GH_USB_set_Misc_rx_edma(U8 data);
/*! \brief Reads the bit group 'rx_edma' of register 'USB_Misc'. */
U8   GH_USB_get_Misc_rx_edma(void);
/*! \brief Writes the bit group 'tx_edma' of register 'USB_Misc'. */
void GH_USB_set_Misc_tx_edma(U8 data);
/*! \brief Reads the bit group 'tx_edma' of register 'USB_Misc'. */
U8   GH_USB_get_Misc_tx_edma(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_Misc(U8 data)
{
    *(volatile U8 *)REG_USB_MISC = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Misc] <-- 0x%08x\n",
                        REG_USB_MISC,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_Misc(void)
{
    U8 value = (*(volatile U8 *)REG_USB_MISC);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Misc] --> 0x%08x\n",
                        REG_USB_MISC,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_Misc_rx_edma(U8 data)
{
    GH_USB_MISC_S d;
    d.all = *(volatile U8 *)REG_USB_MISC;
    d.bitc.rx_edma = data;
    *(volatile U8 *)REG_USB_MISC = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Misc_rx_edma] <-- 0x%08x\n",
                        REG_USB_MISC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_Misc_rx_edma(void)
{
    GH_USB_MISC_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_MISC);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Misc_rx_edma] --> 0x%08x\n",
                        REG_USB_MISC,value);
    #endif
    return tmp_value.bitc.rx_edma;
}
GH_INLINE void GH_USB_set_Misc_tx_edma(U8 data)
{
    GH_USB_MISC_S d;
    d.all = *(volatile U8 *)REG_USB_MISC;
    d.bitc.tx_edma = data;
    *(volatile U8 *)REG_USB_MISC = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_Misc_tx_edma] <-- 0x%08x\n",
                        REG_USB_MISC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_Misc_tx_edma(void)
{
    GH_USB_MISC_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_MISC);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_Misc_tx_edma] --> 0x%08x\n",
                        REG_USB_MISC,value);
    #endif
    return tmp_value.bitc.tx_edma;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxFIFOsz (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_TxFIFOsz'. */
void GH_USB_set_TxFIFOsz(U8 data);
/*! \brief Reads the register 'USB_TxFIFOsz'. */
U8   GH_USB_get_TxFIFOsz(void);
/*! \brief Writes the bit group 'SZ' of register 'USB_TxFIFOsz'. */
void GH_USB_set_TxFIFOsz_SZ(U8 data);
/*! \brief Reads the bit group 'SZ' of register 'USB_TxFIFOsz'. */
U8   GH_USB_get_TxFIFOsz_SZ(void);
/*! \brief Writes the bit group 'DPB' of register 'USB_TxFIFOsz'. */
void GH_USB_set_TxFIFOsz_DPB(U8 data);
/*! \brief Reads the bit group 'DPB' of register 'USB_TxFIFOsz'. */
U8   GH_USB_get_TxFIFOsz_DPB(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_TxFIFOsz(U8 data)
{
    *(volatile U8 *)REG_USB_TXFIFOSZ = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxFIFOsz] <-- 0x%08x\n",
                        REG_USB_TXFIFOSZ,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_TxFIFOsz(void)
{
    U8 value = (*(volatile U8 *)REG_USB_TXFIFOSZ);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxFIFOsz] --> 0x%08x\n",
                        REG_USB_TXFIFOSZ,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_TxFIFOsz_SZ(U8 data)
{
    GH_USB_TXFIFOSZ_S d;
    d.all = *(volatile U8 *)REG_USB_TXFIFOSZ;
    d.bitc.sz = data;
    *(volatile U8 *)REG_USB_TXFIFOSZ = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxFIFOsz_SZ] <-- 0x%08x\n",
                        REG_USB_TXFIFOSZ,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxFIFOsz_SZ(void)
{
    GH_USB_TXFIFOSZ_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXFIFOSZ);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxFIFOsz_SZ] --> 0x%08x\n",
                        REG_USB_TXFIFOSZ,value);
    #endif
    return tmp_value.bitc.sz;
}
GH_INLINE void GH_USB_set_TxFIFOsz_DPB(U8 data)
{
    GH_USB_TXFIFOSZ_S d;
    d.all = *(volatile U8 *)REG_USB_TXFIFOSZ;
    d.bitc.dpb = data;
    *(volatile U8 *)REG_USB_TXFIFOSZ = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxFIFOsz_DPB] <-- 0x%08x\n",
                        REG_USB_TXFIFOSZ,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxFIFOsz_DPB(void)
{
    GH_USB_TXFIFOSZ_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_TXFIFOSZ);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxFIFOsz_DPB] --> 0x%08x\n",
                        REG_USB_TXFIFOSZ,value);
    #endif
    return tmp_value.bitc.dpb;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxFIFOsz (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_RxFIFOsz'. */
void GH_USB_set_RxFIFOsz(U8 data);
/*! \brief Reads the register 'USB_RxFIFOsz'. */
U8   GH_USB_get_RxFIFOsz(void);
/*! \brief Writes the bit group 'SZ' of register 'USB_RxFIFOsz'. */
void GH_USB_set_RxFIFOsz_SZ(U8 data);
/*! \brief Reads the bit group 'SZ' of register 'USB_RxFIFOsz'. */
U8   GH_USB_get_RxFIFOsz_SZ(void);
/*! \brief Writes the bit group 'DPB' of register 'USB_RxFIFOsz'. */
void GH_USB_set_RxFIFOsz_DPB(U8 data);
/*! \brief Reads the bit group 'DPB' of register 'USB_RxFIFOsz'. */
U8   GH_USB_get_RxFIFOsz_DPB(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_RxFIFOsz(U8 data)
{
    *(volatile U8 *)REG_USB_RXFIFOSZ = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxFIFOsz] <-- 0x%08x\n",
                        REG_USB_RXFIFOSZ,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_RxFIFOsz(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RXFIFOSZ);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxFIFOsz] --> 0x%08x\n",
                        REG_USB_RXFIFOSZ,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_RxFIFOsz_SZ(U8 data)
{
    GH_USB_RXFIFOSZ_S d;
    d.all = *(volatile U8 *)REG_USB_RXFIFOSZ;
    d.bitc.sz = data;
    *(volatile U8 *)REG_USB_RXFIFOSZ = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxFIFOsz_SZ] <-- 0x%08x\n",
                        REG_USB_RXFIFOSZ,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxFIFOsz_SZ(void)
{
    GH_USB_RXFIFOSZ_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXFIFOSZ);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxFIFOsz_SZ] --> 0x%08x\n",
                        REG_USB_RXFIFOSZ,value);
    #endif
    return tmp_value.bitc.sz;
}
GH_INLINE void GH_USB_set_RxFIFOsz_DPB(U8 data)
{
    GH_USB_RXFIFOSZ_S d;
    d.all = *(volatile U8 *)REG_USB_RXFIFOSZ;
    d.bitc.dpb = data;
    *(volatile U8 *)REG_USB_RXFIFOSZ = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxFIFOsz_DPB] <-- 0x%08x\n",
                        REG_USB_RXFIFOSZ,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxFIFOsz_DPB(void)
{
    GH_USB_RXFIFOSZ_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RXFIFOSZ);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxFIFOsz_DPB] --> 0x%08x\n",
                        REG_USB_RXFIFOSZ,value);
    #endif
    return tmp_value.bitc.dpb;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxFIFOadd (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_TxFIFOadd'. */
void GH_USB_set_TxFIFOadd(U16 data);
/*! \brief Reads the register 'USB_TxFIFOadd'. */
U16  GH_USB_get_TxFIFOadd(void);
/*! \brief Writes the bit group 'Startaddress' of register 'USB_TxFIFOadd'. */
void GH_USB_set_TxFIFOadd_Startaddress(U16 data);
/*! \brief Reads the bit group 'Startaddress' of register 'USB_TxFIFOadd'. */
U16  GH_USB_get_TxFIFOadd_Startaddress(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_TxFIFOadd(U16 data)
{
    *(volatile U16 *)REG_USB_TXFIFOADD = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxFIFOadd] <-- 0x%08x\n",
                        REG_USB_TXFIFOADD,data,data);
    #endif
}
GH_INLINE U16  GH_USB_get_TxFIFOadd(void)
{
    U16 value = (*(volatile U16 *)REG_USB_TXFIFOADD);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxFIFOadd] --> 0x%08x\n",
                        REG_USB_TXFIFOADD,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_TxFIFOadd_Startaddress(U16 data)
{
    GH_USB_TXFIFOADD_S d;
    d.all = *(volatile U16 *)REG_USB_TXFIFOADD;
    d.bitc.startaddress = data;
    *(volatile U16 *)REG_USB_TXFIFOADD = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxFIFOadd_Startaddress] <-- 0x%08x\n",
                        REG_USB_TXFIFOADD,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_USB_get_TxFIFOadd_Startaddress(void)
{
    GH_USB_TXFIFOADD_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXFIFOADD);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxFIFOadd_Startaddress] --> 0x%08x\n",
                        REG_USB_TXFIFOADD,value);
    #endif
    return tmp_value.bitc.startaddress;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxFIFOadd (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_RxFIFOadd'. */
void GH_USB_set_RxFIFOadd(U16 data);
/*! \brief Reads the register 'USB_RxFIFOadd'. */
U16  GH_USB_get_RxFIFOadd(void);
/*! \brief Writes the bit group 'Startaddress' of register 'USB_RxFIFOadd'. */
void GH_USB_set_RxFIFOadd_Startaddress(U16 data);
/*! \brief Reads the bit group 'Startaddress' of register 'USB_RxFIFOadd'. */
U16  GH_USB_get_RxFIFOadd_Startaddress(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_RxFIFOadd(U16 data)
{
    *(volatile U16 *)REG_USB_RXFIFOADD = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxFIFOadd] <-- 0x%08x\n",
                        REG_USB_RXFIFOADD,data,data);
    #endif
}
GH_INLINE U16  GH_USB_get_RxFIFOadd(void)
{
    U16 value = (*(volatile U16 *)REG_USB_RXFIFOADD);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxFIFOadd] --> 0x%08x\n",
                        REG_USB_RXFIFOADD,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_RxFIFOadd_Startaddress(U16 data)
{
    GH_USB_RXFIFOADD_S d;
    d.all = *(volatile U16 *)REG_USB_RXFIFOADD;
    d.bitc.startaddress = data;
    *(volatile U16 *)REG_USB_RXFIFOADD = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxFIFOadd_Startaddress] <-- 0x%08x\n",
                        REG_USB_RXFIFOADD,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_USB_get_RxFIFOadd_Startaddress(void)
{
    GH_USB_RXFIFOADD_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXFIFOADD);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxFIFOadd_Startaddress] --> 0x%08x\n",
                        REG_USB_RXFIFOADD,value);
    #endif
    return tmp_value.bitc.startaddress;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_VStatus (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_VStatus'. */
U32  GH_USB_get_VStatus(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_USB_get_VStatus(void)
{
    U32 value = (*(volatile U32 *)REG_USB_VSTATUS);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_VStatus] --> 0x%08x\n",
                        REG_USB_VSTATUS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_VControl (write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'USB_VControl'. */
void GH_USB_set_VControl(U32 data);
/*! \brief Reads the mirror variable of the register 'USB_VControl'. */
U32  GH_USB_getm_VControl(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_USB_set_VControl(U32 data)
{
    m_usb_vcontrol = data;
    *(volatile U32 *)REG_USB_VCONTROL = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_VControl] <-- 0x%08x\n",
                        REG_USB_VCONTROL,data,data);
    #endif
}
GH_INLINE U32  GH_USB_getm_VControl(void)
{
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "[GH_USB_getm_VControl] --> 0x%08x\n",
                        m_usb_vcontrol);
    #endif
    return m_usb_vcontrol;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register USB_HWVers (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_HWVers'. */
U16  GH_USB_get_HWVers(void);
/*! \brief Reads the bit group 'MinorVersion' of register 'USB_HWVers'. */
U16  GH_USB_get_HWVers_MinorVersion(void);
/*! \brief Reads the bit group 'MajorVersion' of register 'USB_HWVers'. */
U8   GH_USB_get_HWVers_MajorVersion(void);
/*! \brief Reads the bit group 'RC' of register 'USB_HWVers'. */
U8   GH_USB_get_HWVers_RC(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_USB_get_HWVers(void)
{
    U16 value = (*(volatile U16 *)REG_USB_HWVERS);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_HWVers] --> 0x%08x\n",
                        REG_USB_HWVERS,value);
    #endif
    return value;
}
GH_INLINE U16  GH_USB_get_HWVers_MinorVersion(void)
{
    GH_USB_HWVERS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_HWVERS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_HWVers_MinorVersion] --> 0x%08x\n",
                        REG_USB_HWVERS,value);
    #endif
    return tmp_value.bitc.minorversion;
}
GH_INLINE U8   GH_USB_get_HWVers_MajorVersion(void)
{
    GH_USB_HWVERS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_HWVERS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_HWVers_MajorVersion] --> 0x%08x\n",
                        REG_USB_HWVERS,value);
    #endif
    return tmp_value.bitc.majorversion;
}
GH_INLINE U8   GH_USB_get_HWVers_RC(void)
{
    GH_USB_HWVERS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_HWVERS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_HWVers_RC] --> 0x%08x\n",
                        REG_USB_HWVERS,value);
    #endif
    return tmp_value.bitc.rc;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_EPInfo (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_EPInfo'. */
U8   GH_USB_get_EPInfo(void);
/*! \brief Reads the bit group 'TxEndPoints' of register 'USB_EPInfo'. */
U8   GH_USB_get_EPInfo_TxEndPoints(void);
/*! \brief Reads the bit group 'RxEndPoints' of register 'USB_EPInfo'. */
U8   GH_USB_get_EPInfo_RxEndPoints(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_EPInfo(void)
{
    U8 value = (*(volatile U8 *)REG_USB_EPINFO);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_EPInfo] --> 0x%08x\n",
                        REG_USB_EPINFO,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_EPInfo_TxEndPoints(void)
{
    GH_USB_EPINFO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_EPINFO);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_EPInfo_TxEndPoints] --> 0x%08x\n",
                        REG_USB_EPINFO,value);
    #endif
    return tmp_value.bitc.txendpoints;
}
GH_INLINE U8   GH_USB_get_EPInfo_RxEndPoints(void)
{
    GH_USB_EPINFO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_EPINFO);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_EPInfo_RxEndPoints] --> 0x%08x\n",
                        REG_USB_EPINFO,value);
    #endif
    return tmp_value.bitc.rxendpoints;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RAMInfo (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_RAMInfo'. */
U8   GH_USB_get_RAMInfo(void);
/*! \brief Reads the bit group 'RamBits' of register 'USB_RAMInfo'. */
U8   GH_USB_get_RAMInfo_RamBits(void);
/*! \brief Reads the bit group 'DMAChans' of register 'USB_RAMInfo'. */
U8   GH_USB_get_RAMInfo_DMAChans(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_RAMInfo(void)
{
    U8 value = (*(volatile U8 *)REG_USB_RAMINFO);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RAMInfo] --> 0x%08x\n",
                        REG_USB_RAMINFO,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_RAMInfo_RamBits(void)
{
    GH_USB_RAMINFO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RAMINFO);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RAMInfo_RamBits] --> 0x%08x\n",
                        REG_USB_RAMINFO,value);
    #endif
    return tmp_value.bitc.rambits;
}
GH_INLINE U8   GH_USB_get_RAMInfo_DMAChans(void)
{
    GH_USB_RAMINFO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_RAMINFO);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RAMInfo_DMAChans] --> 0x%08x\n",
                        REG_USB_RAMINFO,value);
    #endif
    return tmp_value.bitc.dmachans;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LinkInfo (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_LinkInfo'. */
void GH_USB_set_LinkInfo(U8 data);
/*! \brief Reads the register 'USB_LinkInfo'. */
U8   GH_USB_get_LinkInfo(void);
/*! \brief Writes the bit group 'WTID' of register 'USB_LinkInfo'. */
void GH_USB_set_LinkInfo_WTID(U8 data);
/*! \brief Reads the bit group 'WTID' of register 'USB_LinkInfo'. */
U8   GH_USB_get_LinkInfo_WTID(void);
/*! \brief Writes the bit group 'WTCON' of register 'USB_LinkInfo'. */
void GH_USB_set_LinkInfo_WTCON(U8 data);
/*! \brief Reads the bit group 'WTCON' of register 'USB_LinkInfo'. */
U8   GH_USB_get_LinkInfo_WTCON(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_LinkInfo(U8 data)
{
    *(volatile U8 *)REG_USB_LINKINFO = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LinkInfo] <-- 0x%08x\n",
                        REG_USB_LINKINFO,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_LinkInfo(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LINKINFO);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LinkInfo] --> 0x%08x\n",
                        REG_USB_LINKINFO,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_LinkInfo_WTID(U8 data)
{
    GH_USB_LINKINFO_S d;
    d.all = *(volatile U8 *)REG_USB_LINKINFO;
    d.bitc.wtid = data;
    *(volatile U8 *)REG_USB_LINKINFO = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LinkInfo_WTID] <-- 0x%08x\n",
                        REG_USB_LINKINFO,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_LinkInfo_WTID(void)
{
    GH_USB_LINKINFO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LINKINFO);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LinkInfo_WTID] --> 0x%08x\n",
                        REG_USB_LINKINFO,value);
    #endif
    return tmp_value.bitc.wtid;
}
GH_INLINE void GH_USB_set_LinkInfo_WTCON(U8 data)
{
    GH_USB_LINKINFO_S d;
    d.all = *(volatile U8 *)REG_USB_LINKINFO;
    d.bitc.wtcon = data;
    *(volatile U8 *)REG_USB_LINKINFO = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LinkInfo_WTCON] <-- 0x%08x\n",
                        REG_USB_LINKINFO,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_LinkInfo_WTCON(void)
{
    GH_USB_LINKINFO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LINKINFO);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LinkInfo_WTCON] --> 0x%08x\n",
                        REG_USB_LINKINFO,value);
    #endif
    return tmp_value.bitc.wtcon;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_VPLen (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_VPLen'. */
void GH_USB_set_VPLen(U8 data);
/*! \brief Reads the register 'USB_VPLen'. */
U8   GH_USB_get_VPLen(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_VPLen(U8 data)
{
    *(volatile U8 *)REG_USB_VPLEN = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_VPLen] <-- 0x%08x\n",
                        REG_USB_VPLEN,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_VPLen(void)
{
    U8 value = (*(volatile U8 *)REG_USB_VPLEN);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_VPLen] --> 0x%08x\n",
                        REG_USB_VPLEN,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_HS_EOF1 (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_HS_EOF1'. */
void GH_USB_set_HS_EOF1(U8 data);
/*! \brief Reads the register 'USB_HS_EOF1'. */
U8   GH_USB_get_HS_EOF1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_HS_EOF1(U8 data)
{
    *(volatile U8 *)REG_USB_HS_EOF1 = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_HS_EOF1] <-- 0x%08x\n",
                        REG_USB_HS_EOF1,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_HS_EOF1(void)
{
    U8 value = (*(volatile U8 *)REG_USB_HS_EOF1);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_HS_EOF1] --> 0x%08x\n",
                        REG_USB_HS_EOF1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_FS_EOF1 (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_FS_EOF1'. */
void GH_USB_set_FS_EOF1(U8 data);
/*! \brief Reads the register 'USB_FS_EOF1'. */
U8   GH_USB_get_FS_EOF1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_FS_EOF1(U8 data)
{
    *(volatile U8 *)REG_USB_FS_EOF1 = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_FS_EOF1] <-- 0x%08x\n",
                        REG_USB_FS_EOF1,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_FS_EOF1(void)
{
    U8 value = (*(volatile U8 *)REG_USB_FS_EOF1);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FS_EOF1] --> 0x%08x\n",
                        REG_USB_FS_EOF1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LS_EOF1 (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_LS_EOF1'. */
void GH_USB_set_LS_EOF1(U8 data);
/*! \brief Reads the register 'USB_LS_EOF1'. */
U8   GH_USB_get_LS_EOF1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_LS_EOF1(U8 data)
{
    *(volatile U8 *)REG_USB_LS_EOF1 = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LS_EOF1] <-- 0x%08x\n",
                        REG_USB_LS_EOF1,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_LS_EOF1(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LS_EOF1);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LS_EOF1] --> 0x%08x\n",
                        REG_USB_LS_EOF1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_SOFT_RST (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_SOFT_RST'. */
void GH_USB_set_SOFT_RST(U8 data);
/*! \brief Reads the register 'USB_SOFT_RST'. */
U8   GH_USB_get_SOFT_RST(void);
/*! \brief Writes the bit group 'NRST' of register 'USB_SOFT_RST'. */
void GH_USB_set_SOFT_RST_NRST(U8 data);
/*! \brief Reads the bit group 'NRST' of register 'USB_SOFT_RST'. */
U8   GH_USB_get_SOFT_RST_NRST(void);
/*! \brief Writes the bit group 'NRSTX' of register 'USB_SOFT_RST'. */
void GH_USB_set_SOFT_RST_NRSTX(U8 data);
/*! \brief Reads the bit group 'NRSTX' of register 'USB_SOFT_RST'. */
U8   GH_USB_get_SOFT_RST_NRSTX(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_SOFT_RST(U8 data)
{
    *(volatile U8 *)REG_USB_SOFT_RST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_SOFT_RST] <-- 0x%08x\n",
                        REG_USB_SOFT_RST,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_SOFT_RST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_SOFT_RST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_SOFT_RST] --> 0x%08x\n",
                        REG_USB_SOFT_RST,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_SOFT_RST_NRST(U8 data)
{
    GH_USB_SOFT_RST_S d;
    d.all = *(volatile U8 *)REG_USB_SOFT_RST;
    d.bitc.nrst = data;
    *(volatile U8 *)REG_USB_SOFT_RST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_SOFT_RST_NRST] <-- 0x%08x\n",
                        REG_USB_SOFT_RST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_SOFT_RST_NRST(void)
{
    GH_USB_SOFT_RST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_SOFT_RST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_SOFT_RST_NRST] --> 0x%08x\n",
                        REG_USB_SOFT_RST,value);
    #endif
    return tmp_value.bitc.nrst;
}
GH_INLINE void GH_USB_set_SOFT_RST_NRSTX(U8 data)
{
    GH_USB_SOFT_RST_S d;
    d.all = *(volatile U8 *)REG_USB_SOFT_RST;
    d.bitc.nrstx = data;
    *(volatile U8 *)REG_USB_SOFT_RST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_SOFT_RST_NRSTX] <-- 0x%08x\n",
                        REG_USB_SOFT_RST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_SOFT_RST_NRSTX(void)
{
    GH_USB_SOFT_RST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_SOFT_RST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_SOFT_RST_NRSTX] --> 0x%08x\n",
                        REG_USB_SOFT_RST,value);
    #endif
    return tmp_value.bitc.nrstx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxFuncAddr (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_TxFuncAddr'. */
void GH_USB_set_TxFuncAddr(U8 index, U8 data);
/*! \brief Reads the register 'USB_TxFuncAddr'. */
U8   GH_USB_get_TxFuncAddr(U8 index);
/*! \brief Writes the bit group 'AddressofTargetFunction' of register 'USB_TxFuncAddr'. */
void GH_USB_set_TxFuncAddr_AddressofTargetFunction(U8 index, U8 data);
/*! \brief Reads the bit group 'AddressofTargetFunction' of register 'USB_TxFuncAddr'. */
U8   GH_USB_get_TxFuncAddr_AddressofTargetFunction(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_TxFuncAddr(U8 index, U8 data)
{
    *(volatile U8 *)(REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxFuncAddr] <-- 0x%08x\n",
                        (REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_TxFuncAddr(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxFuncAddr] --> 0x%08x\n",
                        (REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_TxFuncAddr_AddressofTargetFunction(U8 index, U8 data)
{
    GH_USB_TXFUNCADDR_S d;
    d.all = *(volatile U8 *)(REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.addressoftargetfunction = data;
    *(volatile U8 *)(REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxFuncAddr_AddressofTargetFunction] <-- 0x%08x\n",
                        (REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxFuncAddr_AddressofTargetFunction(U8 index)
{
    GH_USB_TXFUNCADDR_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxFuncAddr_AddressofTargetFunction] --> 0x%08x\n",
                        (REG_USB_TXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.addressoftargetfunction;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxHubAddr (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_TxHubAddr'. */
void GH_USB_set_TxHubAddr(U8 index, U8 data);
/*! \brief Reads the register 'USB_TxHubAddr'. */
U8   GH_USB_get_TxHubAddr(U8 index);
/*! \brief Writes the bit group 'HubAddress' of register 'USB_TxHubAddr'. */
void GH_USB_set_TxHubAddr_HubAddress(U8 index, U8 data);
/*! \brief Reads the bit group 'HubAddress' of register 'USB_TxHubAddr'. */
U8   GH_USB_get_TxHubAddr_HubAddress(U8 index);
/*! \brief Writes the bit group 'MultipleTranslators' of register 'USB_TxHubAddr'. */
void GH_USB_set_TxHubAddr_MultipleTranslators(U8 index, U8 data);
/*! \brief Reads the bit group 'MultipleTranslators' of register 'USB_TxHubAddr'. */
U8   GH_USB_get_TxHubAddr_MultipleTranslators(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_TxHubAddr(U8 index, U8 data)
{
    *(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxHubAddr] <-- 0x%08x\n",
                        (REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_TxHubAddr(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxHubAddr] --> 0x%08x\n",
                        (REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_TxHubAddr_HubAddress(U8 index, U8 data)
{
    GH_USB_TXHUBADDR_S d;
    d.all = *(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.hubaddress = data;
    *(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxHubAddr_HubAddress] <-- 0x%08x\n",
                        (REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxHubAddr_HubAddress(U8 index)
{
    GH_USB_TXHUBADDR_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxHubAddr_HubAddress] --> 0x%08x\n",
                        (REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.hubaddress;
}
GH_INLINE void GH_USB_set_TxHubAddr_MultipleTranslators(U8 index, U8 data)
{
    GH_USB_TXHUBADDR_S d;
    d.all = *(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.multipletranslators = data;
    *(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxHubAddr_MultipleTranslators] <-- 0x%08x\n",
                        (REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxHubAddr_MultipleTranslators(U8 index)
{
    GH_USB_TXHUBADDR_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxHubAddr_MultipleTranslators] --> 0x%08x\n",
                        (REG_USB_TXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.multipletranslators;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxHubPort (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_TxHubPort'. */
void GH_USB_set_TxHubPort(U8 index, U8 data);
/*! \brief Reads the register 'USB_TxHubPort'. */
U8   GH_USB_get_TxHubPort(U8 index);
/*! \brief Writes the bit group 'HubPort' of register 'USB_TxHubPort'. */
void GH_USB_set_TxHubPort_HubPort(U8 index, U8 data);
/*! \brief Reads the bit group 'HubPort' of register 'USB_TxHubPort'. */
U8   GH_USB_get_TxHubPort_HubPort(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_TxHubPort(U8 index, U8 data)
{
    *(volatile U8 *)(REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxHubPort] <-- 0x%08x\n",
                        (REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_TxHubPort(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxHubPort] --> 0x%08x\n",
                        (REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_TxHubPort_HubPort(U8 index, U8 data)
{
    GH_USB_TXHUBPORT_S d;
    d.all = *(volatile U8 *)(REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.hubport = data;
    *(volatile U8 *)(REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxHubPort_HubPort] <-- 0x%08x\n",
                        (REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxHubPort_HubPort(U8 index)
{
    GH_USB_TXHUBPORT_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxHubPort_HubPort] --> 0x%08x\n",
                        (REG_USB_TXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.hubport;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxFuncAddr (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_RxFuncAddr'. */
void GH_USB_set_RxFuncAddr(U8 index, U8 data);
/*! \brief Reads the register 'USB_RxFuncAddr'. */
U8   GH_USB_get_RxFuncAddr(U8 index);
/*! \brief Writes the bit group 'AddressofTargetFunction' of register 'USB_RxFuncAddr'. */
void GH_USB_set_RxFuncAddr_AddressofTargetFunction(U8 index, U8 data);
/*! \brief Reads the bit group 'AddressofTargetFunction' of register 'USB_RxFuncAddr'. */
U8   GH_USB_get_RxFuncAddr_AddressofTargetFunction(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_RxFuncAddr(U8 index, U8 data)
{
    *(volatile U8 *)(REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxFuncAddr] <-- 0x%08x\n",
                        (REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_RxFuncAddr(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxFuncAddr] --> 0x%08x\n",
                        (REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_RxFuncAddr_AddressofTargetFunction(U8 index, U8 data)
{
    GH_USB_RXFUNCADDR_S d;
    d.all = *(volatile U8 *)(REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.addressoftargetfunction = data;
    *(volatile U8 *)(REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxFuncAddr_AddressofTargetFunction] <-- 0x%08x\n",
                        (REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxFuncAddr_AddressofTargetFunction(U8 index)
{
    GH_USB_RXFUNCADDR_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxFuncAddr_AddressofTargetFunction] --> 0x%08x\n",
                        (REG_USB_RXFUNCADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.addressoftargetfunction;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxHubAddr (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_RxHubAddr'. */
void GH_USB_set_RxHubAddr(U8 index, U8 data);
/*! \brief Reads the register 'USB_RxHubAddr'. */
U8   GH_USB_get_RxHubAddr(U8 index);
/*! \brief Writes the bit group 'HubAddress' of register 'USB_RxHubAddr'. */
void GH_USB_set_RxHubAddr_HubAddress(U8 index, U8 data);
/*! \brief Reads the bit group 'HubAddress' of register 'USB_RxHubAddr'. */
U8   GH_USB_get_RxHubAddr_HubAddress(U8 index);
/*! \brief Writes the bit group 'MultipleTranslators' of register 'USB_RxHubAddr'. */
void GH_USB_set_RxHubAddr_MultipleTranslators(U8 index, U8 data);
/*! \brief Reads the bit group 'MultipleTranslators' of register 'USB_RxHubAddr'. */
U8   GH_USB_get_RxHubAddr_MultipleTranslators(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_RxHubAddr(U8 index, U8 data)
{
    *(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxHubAddr] <-- 0x%08x\n",
                        (REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_RxHubAddr(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxHubAddr] --> 0x%08x\n",
                        (REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_RxHubAddr_HubAddress(U8 index, U8 data)
{
    GH_USB_RXHUBADDR_S d;
    d.all = *(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.hubaddress = data;
    *(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxHubAddr_HubAddress] <-- 0x%08x\n",
                        (REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxHubAddr_HubAddress(U8 index)
{
    GH_USB_RXHUBADDR_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxHubAddr_HubAddress] --> 0x%08x\n",
                        (REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.hubaddress;
}
GH_INLINE void GH_USB_set_RxHubAddr_MultipleTranslators(U8 index, U8 data)
{
    GH_USB_RXHUBADDR_S d;
    d.all = *(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.multipletranslators = data;
    *(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxHubAddr_MultipleTranslators] <-- 0x%08x\n",
                        (REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxHubAddr_MultipleTranslators(U8 index)
{
    GH_USB_RXHUBADDR_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxHubAddr_MultipleTranslators] --> 0x%08x\n",
                        (REG_USB_RXHUBADDR + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.multipletranslators;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxHubPort (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_RxHubPort'. */
void GH_USB_set_RxHubPort(U8 index, U8 data);
/*! \brief Reads the register 'USB_RxHubPort'. */
U8   GH_USB_get_RxHubPort(U8 index);
/*! \brief Writes the bit group 'HubPort' of register 'USB_RxHubPort'. */
void GH_USB_set_RxHubPort_HubPort(U8 index, U8 data);
/*! \brief Reads the bit group 'HubPort' of register 'USB_RxHubPort'. */
U8   GH_USB_get_RxHubPort_HubPort(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_RxHubPort(U8 index, U8 data)
{
    *(volatile U8 *)(REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxHubPort] <-- 0x%08x\n",
                        (REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_RxHubPort(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxHubPort] --> 0x%08x\n",
                        (REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_RxHubPort_HubPort(U8 index, U8 data)
{
    GH_USB_RXHUBPORT_S d;
    d.all = *(volatile U8 *)(REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008));
    d.bitc.hubport = data;
    *(volatile U8 *)(REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxHubPort_HubPort] <-- 0x%08x\n",
                        (REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxHubPort_HubPort(U8 index)
{
    GH_USB_RXHUBPORT_S tmp_value;
    U8 value = (*(volatile U8 *)(REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxHubPort_HubPort] --> 0x%08x\n",
                        (REG_USB_RXHUBPORT + index * FIO_MOFFSET(USB,0x00000008)),value);
    #endif
    return tmp_value.bitc.hubport;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_DMA_INTR (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_DMA_INTR'. */
void GH_USB_set_DMA_INTR(U8 data);
/*! \brief Reads the register 'USB_DMA_INTR'. */
U8   GH_USB_get_DMA_INTR(void);
/*! \brief Writes the bit group 'CH0' of register 'USB_DMA_INTR'. */
void GH_USB_set_DMA_INTR_CH0(U8 data);
/*! \brief Reads the bit group 'CH0' of register 'USB_DMA_INTR'. */
U8   GH_USB_get_DMA_INTR_CH0(void);
/*! \brief Writes the bit group 'CH1' of register 'USB_DMA_INTR'. */
void GH_USB_set_DMA_INTR_CH1(U8 data);
/*! \brief Reads the bit group 'CH1' of register 'USB_DMA_INTR'. */
U8   GH_USB_get_DMA_INTR_CH1(void);
/*! \brief Writes the bit group 'CH2' of register 'USB_DMA_INTR'. */
void GH_USB_set_DMA_INTR_CH2(U8 data);
/*! \brief Reads the bit group 'CH2' of register 'USB_DMA_INTR'. */
U8   GH_USB_get_DMA_INTR_CH2(void);
/*! \brief Writes the bit group 'CH3' of register 'USB_DMA_INTR'. */
void GH_USB_set_DMA_INTR_CH3(U8 data);
/*! \brief Reads the bit group 'CH3' of register 'USB_DMA_INTR'. */
U8   GH_USB_get_DMA_INTR_CH3(void);
/*! \brief Writes the bit group 'CH4' of register 'USB_DMA_INTR'. */
void GH_USB_set_DMA_INTR_CH4(U8 data);
/*! \brief Reads the bit group 'CH4' of register 'USB_DMA_INTR'. */
U8   GH_USB_get_DMA_INTR_CH4(void);
/*! \brief Writes the bit group 'CH5' of register 'USB_DMA_INTR'. */
void GH_USB_set_DMA_INTR_CH5(U8 data);
/*! \brief Reads the bit group 'CH5' of register 'USB_DMA_INTR'. */
U8   GH_USB_get_DMA_INTR_CH5(void);
/*! \brief Writes the bit group 'CH6' of register 'USB_DMA_INTR'. */
void GH_USB_set_DMA_INTR_CH6(U8 data);
/*! \brief Reads the bit group 'CH6' of register 'USB_DMA_INTR'. */
U8   GH_USB_get_DMA_INTR_CH6(void);
/*! \brief Writes the bit group 'CH7' of register 'USB_DMA_INTR'. */
void GH_USB_set_DMA_INTR_CH7(U8 data);
/*! \brief Reads the bit group 'CH7' of register 'USB_DMA_INTR'. */
U8   GH_USB_get_DMA_INTR_CH7(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_DMA_INTR(U8 data)
{
    *(volatile U8 *)REG_USB_DMA_INTR = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_INTR(void)
{
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_DMA_INTR_CH0(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch0 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH0] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_INTR_CH0(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH0] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch0;
}
GH_INLINE void GH_USB_set_DMA_INTR_CH1(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch1 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH1] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_INTR_CH1(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH1] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch1;
}
GH_INLINE void GH_USB_set_DMA_INTR_CH2(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch2 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH2] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_INTR_CH2(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH2] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch2;
}
GH_INLINE void GH_USB_set_DMA_INTR_CH3(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch3 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH3] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_INTR_CH3(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH3] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch3;
}
GH_INLINE void GH_USB_set_DMA_INTR_CH4(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch4 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH4] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_INTR_CH4(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH4] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch4;
}
GH_INLINE void GH_USB_set_DMA_INTR_CH5(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch5 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH5] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_INTR_CH5(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH5] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch5;
}
GH_INLINE void GH_USB_set_DMA_INTR_CH6(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch6 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH6] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_INTR_CH6(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH6] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch6;
}
GH_INLINE void GH_USB_set_DMA_INTR_CH7(U8 data)
{
    GH_USB_DMA_INTR_S d;
    d.all = *(volatile U8 *)REG_USB_DMA_INTR;
    d.bitc.ch7 = data;
    *(volatile U8 *)REG_USB_DMA_INTR = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_INTR_CH7] <-- 0x%08x\n",
                        REG_USB_DMA_INTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_INTR_CH7(void)
{
    GH_USB_DMA_INTR_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_DMA_INTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_INTR_CH7] --> 0x%08x\n",
                        REG_USB_DMA_INTR,value);
    #endif
    return tmp_value.bitc.ch7;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_DMA_CNTL (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_DMA_CNTL'. */
void GH_USB_set_DMA_CNTL(U8 index, U16 data);
/*! \brief Reads the register 'USB_DMA_CNTL'. */
U16  GH_USB_get_DMA_CNTL(U8 index);
/*! \brief Writes the bit group 'DMA_ENAB' of register 'USB_DMA_CNTL'. */
void GH_USB_set_DMA_CNTL_DMA_ENAB(U8 index, U8 data);
/*! \brief Reads the bit group 'DMA_ENAB' of register 'USB_DMA_CNTL'. */
U8   GH_USB_get_DMA_CNTL_DMA_ENAB(U8 index);
/*! \brief Writes the bit group 'DMA_DIR' of register 'USB_DMA_CNTL'. */
void GH_USB_set_DMA_CNTL_DMA_DIR(U8 index, U8 data);
/*! \brief Reads the bit group 'DMA_DIR' of register 'USB_DMA_CNTL'. */
U8   GH_USB_get_DMA_CNTL_DMA_DIR(U8 index);
/*! \brief Writes the bit group 'DMAMODE' of register 'USB_DMA_CNTL'. */
void GH_USB_set_DMA_CNTL_DMAMODE(U8 index, U8 data);
/*! \brief Reads the bit group 'DMAMODE' of register 'USB_DMA_CNTL'. */
U8   GH_USB_get_DMA_CNTL_DMAMODE(U8 index);
/*! \brief Writes the bit group 'DMAIE' of register 'USB_DMA_CNTL'. */
void GH_USB_set_DMA_CNTL_DMAIE(U8 index, U8 data);
/*! \brief Reads the bit group 'DMAIE' of register 'USB_DMA_CNTL'. */
U8   GH_USB_get_DMA_CNTL_DMAIE(U8 index);
/*! \brief Writes the bit group 'DMAEP' of register 'USB_DMA_CNTL'. */
void GH_USB_set_DMA_CNTL_DMAEP(U8 index, U8 data);
/*! \brief Reads the bit group 'DMAEP' of register 'USB_DMA_CNTL'. */
U8   GH_USB_get_DMA_CNTL_DMAEP(U8 index);
/*! \brief Writes the bit group 'DMA_ERR' of register 'USB_DMA_CNTL'. */
void GH_USB_set_DMA_CNTL_DMA_ERR(U8 index, U8 data);
/*! \brief Reads the bit group 'DMA_ERR' of register 'USB_DMA_CNTL'. */
U8   GH_USB_get_DMA_CNTL_DMA_ERR(U8 index);
/*! \brief Writes the bit group 'DMA_BRSTM' of register 'USB_DMA_CNTL'. */
void GH_USB_set_DMA_CNTL_DMA_BRSTM(U8 index, U8 data);
/*! \brief Reads the bit group 'DMA_BRSTM' of register 'USB_DMA_CNTL'. */
U8   GH_USB_get_DMA_CNTL_DMA_BRSTM(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_DMA_CNTL(U8 index, U16 data)
{
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),data,data);
    #endif
}
GH_INLINE U16  GH_USB_get_DMA_CNTL(U8 index)
{
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_DMA_CNTL_DMA_ENAB(U8 index, U8 data)
{
    GH_USB_DMA_CNTL_S d;
    d.all = *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010));
    d.bitc.dma_enab = data;
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL_DMA_ENAB] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_CNTL_DMA_ENAB(U8 index)
{
    GH_USB_DMA_CNTL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL_DMA_ENAB] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return tmp_value.bitc.dma_enab;
}
GH_INLINE void GH_USB_set_DMA_CNTL_DMA_DIR(U8 index, U8 data)
{
    GH_USB_DMA_CNTL_S d;
    d.all = *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010));
    d.bitc.dma_dir = data;
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL_DMA_DIR] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_CNTL_DMA_DIR(U8 index)
{
    GH_USB_DMA_CNTL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL_DMA_DIR] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return tmp_value.bitc.dma_dir;
}
GH_INLINE void GH_USB_set_DMA_CNTL_DMAMODE(U8 index, U8 data)
{
    GH_USB_DMA_CNTL_S d;
    d.all = *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010));
    d.bitc.dmamode = data;
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL_DMAMODE] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_CNTL_DMAMODE(U8 index)
{
    GH_USB_DMA_CNTL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL_DMAMODE] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return tmp_value.bitc.dmamode;
}
GH_INLINE void GH_USB_set_DMA_CNTL_DMAIE(U8 index, U8 data)
{
    GH_USB_DMA_CNTL_S d;
    d.all = *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010));
    d.bitc.dmaie = data;
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL_DMAIE] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_CNTL_DMAIE(U8 index)
{
    GH_USB_DMA_CNTL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL_DMAIE] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return tmp_value.bitc.dmaie;
}
GH_INLINE void GH_USB_set_DMA_CNTL_DMAEP(U8 index, U8 data)
{
    GH_USB_DMA_CNTL_S d;
    d.all = *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010));
    d.bitc.dmaep = data;
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL_DMAEP] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_CNTL_DMAEP(U8 index)
{
    GH_USB_DMA_CNTL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL_DMAEP] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return tmp_value.bitc.dmaep;
}
GH_INLINE void GH_USB_set_DMA_CNTL_DMA_ERR(U8 index, U8 data)
{
    GH_USB_DMA_CNTL_S d;
    d.all = *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010));
    d.bitc.dma_err = data;
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL_DMA_ERR] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_CNTL_DMA_ERR(U8 index)
{
    GH_USB_DMA_CNTL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL_DMA_ERR] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return tmp_value.bitc.dma_err;
}
GH_INLINE void GH_USB_set_DMA_CNTL_DMA_BRSTM(U8 index, U8 data)
{
    GH_USB_DMA_CNTL_S d;
    d.all = *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010));
    d.bitc.dma_brstm = data;
    *(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)) = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_CNTL_DMA_BRSTM] <-- 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_DMA_CNTL_DMA_BRSTM(U8 index)
{
    GH_USB_DMA_CNTL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)));

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_CNTL_DMA_BRSTM] --> 0x%08x\n",
                        (REG_USB_DMA_CNTL + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return tmp_value.bitc.dma_brstm;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_DMA_ADDR (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_DMA_ADDR'. */
void GH_USB_set_DMA_ADDR(U8 index, U32 data);
/*! \brief Reads the register 'USB_DMA_ADDR'. */
U32  GH_USB_get_DMA_ADDR(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_DMA_ADDR(U8 index, U32 data)
{
    *(volatile U32 *)(REG_USB_DMA_ADDR + index * FIO_MOFFSET(USB,0x00000010)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_ADDR] <-- 0x%08x\n",
                        (REG_USB_DMA_ADDR + index * FIO_MOFFSET(USB,0x00000010)),data,data);
    #endif
}
GH_INLINE U32  GH_USB_get_DMA_ADDR(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_USB_DMA_ADDR + index * FIO_MOFFSET(USB,0x00000010)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_ADDR] --> 0x%08x\n",
                        (REG_USB_DMA_ADDR + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_DMA_COUNT (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_DMA_COUNT'. */
void GH_USB_set_DMA_COUNT(U8 index, U32 data);
/*! \brief Reads the register 'USB_DMA_COUNT'. */
U32  GH_USB_get_DMA_COUNT(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_DMA_COUNT(U8 index, U32 data)
{
    *(volatile U32 *)(REG_USB_DMA_COUNT + index * FIO_MOFFSET(USB,0x00000010)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_DMA_COUNT] <-- 0x%08x\n",
                        (REG_USB_DMA_COUNT + index * FIO_MOFFSET(USB,0x00000010)),data,data);
    #endif
}
GH_INLINE U32  GH_USB_get_DMA_COUNT(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_USB_DMA_COUNT + index * FIO_MOFFSET(USB,0x00000010)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_DMA_COUNT] --> 0x%08x\n",
                        (REG_USB_DMA_COUNT + index * FIO_MOFFSET(USB,0x00000010)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RqPktCount_HOST (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_RqPktCount_HOST'. */
void GH_USB_set_RqPktCount_HOST(U16 data);
/*! \brief Reads the register 'USB_RqPktCount_HOST'. */
U16  GH_USB_get_RqPktCount_HOST(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_RqPktCount_HOST(U16 data)
{
    *(volatile U16 *)REG_USB_RQPKTCOUNT_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RqPktCount_HOST] <-- 0x%08x\n",
                        REG_USB_RQPKTCOUNT_HOST,data,data);
    #endif
}
GH_INLINE U16  GH_USB_get_RqPktCount_HOST(void)
{
    U16 value = (*(volatile U16 *)REG_USB_RQPKTCOUNT_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RqPktCount_HOST] --> 0x%08x\n",
                        REG_USB_RQPKTCOUNT_HOST,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_RxDPktBufDis (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis(U16 data);
/*! \brief Reads the register 'USB_RxDPktBufDis'. */
U16  GH_USB_get_RxDPktBufDis(void);
/*! \brief Writes the bit group 'EP1' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP1(U8 data);
/*! \brief Reads the bit group 'EP1' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP1(void);
/*! \brief Writes the bit group 'EP2' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP2(U8 data);
/*! \brief Reads the bit group 'EP2' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP2(void);
/*! \brief Writes the bit group 'EP3' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP3(U8 data);
/*! \brief Reads the bit group 'EP3' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP3(void);
/*! \brief Writes the bit group 'EP4' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP4(U8 data);
/*! \brief Reads the bit group 'EP4' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP4(void);
/*! \brief Writes the bit group 'EP5' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP5(U8 data);
/*! \brief Reads the bit group 'EP5' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP5(void);
/*! \brief Writes the bit group 'EP6' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP6(U8 data);
/*! \brief Reads the bit group 'EP6' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP6(void);
/*! \brief Writes the bit group 'EP7' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP7(U8 data);
/*! \brief Reads the bit group 'EP7' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP7(void);
/*! \brief Writes the bit group 'EP8' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP8(U8 data);
/*! \brief Reads the bit group 'EP8' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP8(void);
/*! \brief Writes the bit group 'EP9' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP9(U8 data);
/*! \brief Reads the bit group 'EP9' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP9(void);
/*! \brief Writes the bit group 'EP10' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP10(U8 data);
/*! \brief Reads the bit group 'EP10' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP10(void);
/*! \brief Writes the bit group 'EP11' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP11(U8 data);
/*! \brief Reads the bit group 'EP11' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP11(void);
/*! \brief Writes the bit group 'EP12' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP12(U8 data);
/*! \brief Reads the bit group 'EP12' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP12(void);
/*! \brief Writes the bit group 'EP13' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP13(U8 data);
/*! \brief Reads the bit group 'EP13' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP13(void);
/*! \brief Writes the bit group 'EP14' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP14(U8 data);
/*! \brief Reads the bit group 'EP14' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP14(void);
/*! \brief Writes the bit group 'EP15' of register 'USB_RxDPktBufDis'. */
void GH_USB_set_RxDPktBufDis_EP15(U8 data);
/*! \brief Reads the bit group 'EP15' of register 'USB_RxDPktBufDis'. */
U8   GH_USB_get_RxDPktBufDis_EP15(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_RxDPktBufDis(U16 data)
{
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,data,data);
    #endif
}
GH_INLINE U16  GH_USB_get_RxDPktBufDis(void)
{
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP1(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep1 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP1] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP1(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP1] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep1;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP2(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep2 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP2] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP2(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP2] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep2;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP3(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep3 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP3] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP3(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP3] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep3;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP4(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep4 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP4] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP4(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP4] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep4;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP5(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep5 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP5] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP5(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP5] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep5;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP6(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep6 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP6] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP6(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP6] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep6;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP7(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep7 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP7] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP7(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP7] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep7;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP8(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep8 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP8] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP8(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP8] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep8;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP9(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep9 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP9] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP9(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP9] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep9;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP10(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep10 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP10] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP10(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP10] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep10;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP11(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep11 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP11] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP11(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP11] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep11;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP12(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep12 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP12] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP12(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP12] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep12;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP13(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep13 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP13] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP13(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP13] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep13;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP14(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep14 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP14] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP14(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP14] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep14;
}
GH_INLINE void GH_USB_set_RxDPktBufDis_EP15(U8 data)
{
    GH_USB_RXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_RXDPKTBUFDIS;
    d.bitc.ep15 = data;
    *(volatile U16 *)REG_USB_RXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_RxDPktBufDis_EP15] <-- 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_RxDPktBufDis_EP15(void)
{
    GH_USB_RXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_RXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_RxDPktBufDis_EP15] --> 0x%08x\n",
                        REG_USB_RXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep15;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_TxDPktBufDis (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis(U16 data);
/*! \brief Reads the register 'USB_TxDPktBufDis'. */
U16  GH_USB_get_TxDPktBufDis(void);
/*! \brief Writes the bit group 'EP1' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP1(U8 data);
/*! \brief Reads the bit group 'EP1' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP1(void);
/*! \brief Writes the bit group 'EP2' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP2(U8 data);
/*! \brief Reads the bit group 'EP2' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP2(void);
/*! \brief Writes the bit group 'EP3' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP3(U8 data);
/*! \brief Reads the bit group 'EP3' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP3(void);
/*! \brief Writes the bit group 'EP4' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP4(U8 data);
/*! \brief Reads the bit group 'EP4' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP4(void);
/*! \brief Writes the bit group 'EP5' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP5(U8 data);
/*! \brief Reads the bit group 'EP5' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP5(void);
/*! \brief Writes the bit group 'EP6' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP6(U8 data);
/*! \brief Reads the bit group 'EP6' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP6(void);
/*! \brief Writes the bit group 'EP7' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP7(U8 data);
/*! \brief Reads the bit group 'EP7' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP7(void);
/*! \brief Writes the bit group 'EP8' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP8(U8 data);
/*! \brief Reads the bit group 'EP8' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP8(void);
/*! \brief Writes the bit group 'EP9' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP9(U8 data);
/*! \brief Reads the bit group 'EP9' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP9(void);
/*! \brief Writes the bit group 'EP10' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP10(U8 data);
/*! \brief Reads the bit group 'EP10' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP10(void);
/*! \brief Writes the bit group 'EP11' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP11(U8 data);
/*! \brief Reads the bit group 'EP11' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP11(void);
/*! \brief Writes the bit group 'EP12' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP12(U8 data);
/*! \brief Reads the bit group 'EP12' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP12(void);
/*! \brief Writes the bit group 'EP13' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP13(U8 data);
/*! \brief Reads the bit group 'EP13' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP13(void);
/*! \brief Writes the bit group 'EP14' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP14(U8 data);
/*! \brief Reads the bit group 'EP14' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP14(void);
/*! \brief Writes the bit group 'EP15' of register 'USB_TxDPktBufDis'. */
void GH_USB_set_TxDPktBufDis_EP15(U8 data);
/*! \brief Reads the bit group 'EP15' of register 'USB_TxDPktBufDis'. */
U8   GH_USB_get_TxDPktBufDis_EP15(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_TxDPktBufDis(U16 data)
{
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,data,data);
    #endif
}
GH_INLINE U16  GH_USB_get_TxDPktBufDis(void)
{
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP1(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep1 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP1] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP1(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP1] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep1;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP2(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep2 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP2] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP2(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP2] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep2;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP3(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep3 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP3] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP3(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP3] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep3;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP4(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep4 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP4] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP4(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP4] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep4;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP5(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep5 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP5] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP5(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP5] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep5;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP6(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep6 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP6] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP6(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP6] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep6;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP7(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep7 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP7] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP7(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP7] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep7;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP8(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep8 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP8] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP8(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP8] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep8;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP9(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep9 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP9] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP9(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP9] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep9;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP10(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep10 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP10] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP10(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP10] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep10;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP11(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep11 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP11] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP11(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP11] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep11;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP12(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep12 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP12] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP12(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP12] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep12;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP13(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep13 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP13] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP13(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP13] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep13;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP14(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep14 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP14] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP14(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP14] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep14;
}
GH_INLINE void GH_USB_set_TxDPktBufDis_EP15(U8 data)
{
    GH_USB_TXDPKTBUFDIS_S d;
    d.all = *(volatile U16 *)REG_USB_TXDPKTBUFDIS;
    d.bitc.ep15 = data;
    *(volatile U16 *)REG_USB_TXDPKTBUFDIS = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_TxDPktBufDis_EP15] <-- 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_TxDPktBufDis_EP15(void)
{
    GH_USB_TXDPKTBUFDIS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_TXDPKTBUFDIS);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_TxDPktBufDis_EP15] --> 0x%08x\n",
                        REG_USB_TXDPKTBUFDIS,value);
    #endif
    return tmp_value.bitc.ep15;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_C_T_UCH (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_C_T_UCH'. */
void GH_USB_set_C_T_UCH(U16 data);
/*! \brief Reads the register 'USB_C_T_UCH'. */
U16  GH_USB_get_C_T_UCH(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_C_T_UCH(U16 data)
{
    *(volatile U16 *)REG_USB_C_T_UCH = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_C_T_UCH] <-- 0x%08x\n",
                        REG_USB_C_T_UCH,data,data);
    #endif
}
GH_INLINE U16  GH_USB_get_C_T_UCH(void)
{
    U16 value = (*(volatile U16 *)REG_USB_C_T_UCH);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_C_T_UCH] --> 0x%08x\n",
                        REG_USB_C_T_UCH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_C_T_HSRTN (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_C_T_HSRTN'. */
void GH_USB_set_C_T_HSRTN(U16 data);
/*! \brief Reads the register 'USB_C_T_HSRTN'. */
U16  GH_USB_get_C_T_HSRTN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_C_T_HSRTN(U16 data)
{
    *(volatile U16 *)REG_USB_C_T_HSRTN = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_C_T_HSRTN] <-- 0x%08x\n",
                        REG_USB_C_T_HSRTN,data,data);
    #endif
}
GH_INLINE U16  GH_USB_get_C_T_HSRTN(void)
{
    U16 value = (*(volatile U16 *)REG_USB_C_T_HSRTN);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_C_T_HSRTN] --> 0x%08x\n",
                        REG_USB_C_T_HSRTN,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_C_T_HSBT (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_C_T_HSBT'. */
void GH_USB_set_C_T_HSBT(U8 data);
/*! \brief Reads the register 'USB_C_T_HSBT'. */
U8   GH_USB_get_C_T_HSBT(void);
/*! \brief Writes the bit group 'HSTimeoutAdder' of register 'USB_C_T_HSBT'. */
void GH_USB_set_C_T_HSBT_HSTimeoutAdder(U8 data);
/*! \brief Reads the bit group 'HSTimeoutAdder' of register 'USB_C_T_HSBT'. */
U8   GH_USB_get_C_T_HSBT_HSTimeoutAdder(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_C_T_HSBT(U8 data)
{
    *(volatile U8 *)REG_USB_C_T_HSBT = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_C_T_HSBT] <-- 0x%08x\n",
                        REG_USB_C_T_HSBT,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_C_T_HSBT(void)
{
    U8 value = (*(volatile U8 *)REG_USB_C_T_HSBT);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_C_T_HSBT] --> 0x%08x\n",
                        REG_USB_C_T_HSBT,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_C_T_HSBT_HSTimeoutAdder(U8 data)
{
    GH_USB_C_T_HSBT_S d;
    d.all = *(volatile U8 *)REG_USB_C_T_HSBT;
    d.bitc.hstimeoutadder = data;
    *(volatile U8 *)REG_USB_C_T_HSBT = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_C_T_HSBT_HSTimeoutAdder] <-- 0x%08x\n",
                        REG_USB_C_T_HSBT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_C_T_HSBT_HSTimeoutAdder(void)
{
    GH_USB_C_T_HSBT_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_C_T_HSBT);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_C_T_HSBT_HSTimeoutAdder] --> 0x%08x\n",
                        REG_USB_C_T_HSBT,value);
    #endif
    return tmp_value.bitc.hstimeoutadder;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LPM_ATTR (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_LPM_ATTR'. */
U16  GH_USB_get_LPM_ATTR(void);
/*! \brief Reads the bit group 'LinkState' of register 'USB_LPM_ATTR'. */
U8   GH_USB_get_LPM_ATTR_LinkState(void);
/*! \brief Reads the bit group 'HIRD' of register 'USB_LPM_ATTR'. */
U8   GH_USB_get_LPM_ATTR_HIRD(void);
/*! \brief Reads the bit group 'RmtWak' of register 'USB_LPM_ATTR'. */
U8   GH_USB_get_LPM_ATTR_RmtWak(void);
/*! \brief Reads the bit group 'EndPnt' of register 'USB_LPM_ATTR'. */
U8   GH_USB_get_LPM_ATTR_EndPnt(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_USB_get_LPM_ATTR(void)
{
    U16 value = (*(volatile U16 *)REG_USB_LPM_ATTR);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_ATTR] --> 0x%08x\n",
                        REG_USB_LPM_ATTR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_LPM_ATTR_LinkState(void)
{
    GH_USB_LPM_ATTR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_LPM_ATTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_ATTR_LinkState] --> 0x%08x\n",
                        REG_USB_LPM_ATTR,value);
    #endif
    return tmp_value.bitc.linkstate;
}
GH_INLINE U8   GH_USB_get_LPM_ATTR_HIRD(void)
{
    GH_USB_LPM_ATTR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_LPM_ATTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_ATTR_HIRD] --> 0x%08x\n",
                        REG_USB_LPM_ATTR,value);
    #endif
    return tmp_value.bitc.hird;
}
GH_INLINE U8   GH_USB_get_LPM_ATTR_RmtWak(void)
{
    GH_USB_LPM_ATTR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_LPM_ATTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_ATTR_RmtWak] --> 0x%08x\n",
                        REG_USB_LPM_ATTR,value);
    #endif
    return tmp_value.bitc.rmtwak;
}
GH_INLINE U8   GH_USB_get_LPM_ATTR_EndPnt(void)
{
    GH_USB_LPM_ATTR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_LPM_ATTR);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_ATTR_EndPnt] --> 0x%08x\n",
                        REG_USB_LPM_ATTR,value);
    #endif
    return tmp_value.bitc.endpnt;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LPM_CNTRL_PERI (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_LPM_CNTRL_PERI'. */
void GH_USB_set_LPM_CNTRL_PERI(U8 data);
/*! \brief Reads the register 'USB_LPM_CNTRL_PERI'. */
U8   GH_USB_get_LPM_CNTRL_PERI(void);
/*! \brief Writes the bit group 'LPMXMT' of register 'USB_LPM_CNTRL_PERI'. */
void GH_USB_set_LPM_CNTRL_PERI_LPMXMT(U8 data);
/*! \brief Reads the bit group 'LPMXMT' of register 'USB_LPM_CNTRL_PERI'. */
U8   GH_USB_get_LPM_CNTRL_PERI_LPMXMT(void);
/*! \brief Writes the bit group 'LPMRES' of register 'USB_LPM_CNTRL_PERI'. */
void GH_USB_set_LPM_CNTRL_PERI_LPMRES(U8 data);
/*! \brief Reads the bit group 'LPMRES' of register 'USB_LPM_CNTRL_PERI'. */
U8   GH_USB_get_LPM_CNTRL_PERI_LPMRES(void);
/*! \brief Writes the bit group 'LPMEN' of register 'USB_LPM_CNTRL_PERI'. */
void GH_USB_set_LPM_CNTRL_PERI_LPMEN(U8 data);
/*! \brief Reads the bit group 'LPMEN' of register 'USB_LPM_CNTRL_PERI'. */
U8   GH_USB_get_LPM_CNTRL_PERI_LPMEN(void);
/*! \brief Writes the bit group 'LPMNAK' of register 'USB_LPM_CNTRL_PERI'. */
void GH_USB_set_LPM_CNTRL_PERI_LPMNAK(U8 data);
/*! \brief Reads the bit group 'LPMNAK' of register 'USB_LPM_CNTRL_PERI'. */
U8   GH_USB_get_LPM_CNTRL_PERI_LPMNAK(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_LPM_CNTRL_PERI(U8 data)
{
    *(volatile U8 *)REG_USB_LPM_CNTRL_PERI = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_PERI] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_CNTRL_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_PERI] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_LPM_CNTRL_PERI_LPMXMT(U8 data)
{
    GH_USB_LPM_CNTRL_PERI_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_CNTRL_PERI;
    d.bitc.lpmxmt = data;
    *(volatile U8 *)REG_USB_LPM_CNTRL_PERI = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_PERI_LPMXMT] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_CNTRL_PERI_LPMXMT(void)
{
    GH_USB_LPM_CNTRL_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_PERI_LPMXMT] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,value);
    #endif
    return tmp_value.bitc.lpmxmt;
}
GH_INLINE void GH_USB_set_LPM_CNTRL_PERI_LPMRES(U8 data)
{
    GH_USB_LPM_CNTRL_PERI_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_CNTRL_PERI;
    d.bitc.lpmres = data;
    *(volatile U8 *)REG_USB_LPM_CNTRL_PERI = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_PERI_LPMRES] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_CNTRL_PERI_LPMRES(void)
{
    GH_USB_LPM_CNTRL_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_PERI_LPMRES] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,value);
    #endif
    return tmp_value.bitc.lpmres;
}
GH_INLINE void GH_USB_set_LPM_CNTRL_PERI_LPMEN(U8 data)
{
    GH_USB_LPM_CNTRL_PERI_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_CNTRL_PERI;
    d.bitc.lpmen = data;
    *(volatile U8 *)REG_USB_LPM_CNTRL_PERI = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_PERI_LPMEN] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_CNTRL_PERI_LPMEN(void)
{
    GH_USB_LPM_CNTRL_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_PERI_LPMEN] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,value);
    #endif
    return tmp_value.bitc.lpmen;
}
GH_INLINE void GH_USB_set_LPM_CNTRL_PERI_LPMNAK(U8 data)
{
    GH_USB_LPM_CNTRL_PERI_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_CNTRL_PERI;
    d.bitc.lpmnak = data;
    *(volatile U8 *)REG_USB_LPM_CNTRL_PERI = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_PERI_LPMNAK] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_CNTRL_PERI_LPMNAK(void)
{
    GH_USB_LPM_CNTRL_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_PERI_LPMNAK] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_PERI,value);
    #endif
    return tmp_value.bitc.lpmnak;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LPM_CNTRL_HOST (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_LPM_CNTRL_HOST'. */
void GH_USB_set_LPM_CNTRL_HOST(U8 data);
/*! \brief Reads the register 'USB_LPM_CNTRL_HOST'. */
U8   GH_USB_get_LPM_CNTRL_HOST(void);
/*! \brief Writes the bit group 'LPMXMT' of register 'USB_LPM_CNTRL_HOST'. */
void GH_USB_set_LPM_CNTRL_HOST_LPMXMT(U8 data);
/*! \brief Reads the bit group 'LPMXMT' of register 'USB_LPM_CNTRL_HOST'. */
U8   GH_USB_get_LPM_CNTRL_HOST_LPMXMT(void);
/*! \brief Writes the bit group 'LPMRES' of register 'USB_LPM_CNTRL_HOST'. */
void GH_USB_set_LPM_CNTRL_HOST_LPMRES(U8 data);
/*! \brief Reads the bit group 'LPMRES' of register 'USB_LPM_CNTRL_HOST'. */
U8   GH_USB_get_LPM_CNTRL_HOST_LPMRES(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_LPM_CNTRL_HOST(U8 data)
{
    *(volatile U8 *)REG_USB_LPM_CNTRL_HOST = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_HOST] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_HOST,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_CNTRL_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_HOST] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_HOST,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_LPM_CNTRL_HOST_LPMXMT(U8 data)
{
    GH_USB_LPM_CNTRL_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_CNTRL_HOST;
    d.bitc.lpmxmt = data;
    *(volatile U8 *)REG_USB_LPM_CNTRL_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_HOST_LPMXMT] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_HOST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_CNTRL_HOST_LPMXMT(void)
{
    GH_USB_LPM_CNTRL_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_HOST_LPMXMT] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_HOST,value);
    #endif
    return tmp_value.bitc.lpmxmt;
}
GH_INLINE void GH_USB_set_LPM_CNTRL_HOST_LPMRES(U8 data)
{
    GH_USB_LPM_CNTRL_HOST_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_CNTRL_HOST;
    d.bitc.lpmres = data;
    *(volatile U8 *)REG_USB_LPM_CNTRL_HOST = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_CNTRL_HOST_LPMRES] <-- 0x%08x\n",
                        REG_USB_LPM_CNTRL_HOST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_CNTRL_HOST_LPMRES(void)
{
    GH_USB_LPM_CNTRL_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_CNTRL_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_CNTRL_HOST_LPMRES] --> 0x%08x\n",
                        REG_USB_LPM_CNTRL_HOST,value);
    #endif
    return tmp_value.bitc.lpmres;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LPM_INTREN (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_LPM_INTREN'. */
void GH_USB_set_LPM_INTREN(U8 data);
/*! \brief Reads the register 'USB_LPM_INTREN'. */
U8   GH_USB_get_LPM_INTREN(void);
/*! \brief Writes the bit group 'LPMSTEN' of register 'USB_LPM_INTREN'. */
void GH_USB_set_LPM_INTREN_LPMSTEN(U8 data);
/*! \brief Reads the bit group 'LPMSTEN' of register 'USB_LPM_INTREN'. */
U8   GH_USB_get_LPM_INTREN_LPMSTEN(void);
/*! \brief Writes the bit group 'LPMNYEN' of register 'USB_LPM_INTREN'. */
void GH_USB_set_LPM_INTREN_LPMNYEN(U8 data);
/*! \brief Reads the bit group 'LPMNYEN' of register 'USB_LPM_INTREN'. */
U8   GH_USB_get_LPM_INTREN_LPMNYEN(void);
/*! \brief Writes the bit group 'LPMACKEN' of register 'USB_LPM_INTREN'. */
void GH_USB_set_LPM_INTREN_LPMACKEN(U8 data);
/*! \brief Reads the bit group 'LPMACKEN' of register 'USB_LPM_INTREN'. */
U8   GH_USB_get_LPM_INTREN_LPMACKEN(void);
/*! \brief Writes the bit group 'LPMNCEN' of register 'USB_LPM_INTREN'. */
void GH_USB_set_LPM_INTREN_LPMNCEN(U8 data);
/*! \brief Reads the bit group 'LPMNCEN' of register 'USB_LPM_INTREN'. */
U8   GH_USB_get_LPM_INTREN_LPMNCEN(void);
/*! \brief Writes the bit group 'LPMRESEN' of register 'USB_LPM_INTREN'. */
void GH_USB_set_LPM_INTREN_LPMRESEN(U8 data);
/*! \brief Reads the bit group 'LPMRESEN' of register 'USB_LPM_INTREN'. */
U8   GH_USB_get_LPM_INTREN_LPMRESEN(void);
/*! \brief Writes the bit group 'LPMERREN' of register 'USB_LPM_INTREN'. */
void GH_USB_set_LPM_INTREN_LPMERREN(U8 data);
/*! \brief Reads the bit group 'LPMERREN' of register 'USB_LPM_INTREN'. */
U8   GH_USB_get_LPM_INTREN_LPMERREN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_set_LPM_INTREN(U8 data)
{
    *(volatile U8 *)REG_USB_LPM_INTREN = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_INTREN] <-- 0x%08x\n",
                        REG_USB_LPM_INTREN,data,data);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_INTREN(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTREN);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTREN] --> 0x%08x\n",
                        REG_USB_LPM_INTREN,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_set_LPM_INTREN_LPMSTEN(U8 data)
{
    GH_USB_LPM_INTREN_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_INTREN;
    d.bitc.lpmsten = data;
    *(volatile U8 *)REG_USB_LPM_INTREN = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_INTREN_LPMSTEN] <-- 0x%08x\n",
                        REG_USB_LPM_INTREN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_INTREN_LPMSTEN(void)
{
    GH_USB_LPM_INTREN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTREN);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTREN_LPMSTEN] --> 0x%08x\n",
                        REG_USB_LPM_INTREN,value);
    #endif
    return tmp_value.bitc.lpmsten;
}
GH_INLINE void GH_USB_set_LPM_INTREN_LPMNYEN(U8 data)
{
    GH_USB_LPM_INTREN_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_INTREN;
    d.bitc.lpmnyen = data;
    *(volatile U8 *)REG_USB_LPM_INTREN = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_INTREN_LPMNYEN] <-- 0x%08x\n",
                        REG_USB_LPM_INTREN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_INTREN_LPMNYEN(void)
{
    GH_USB_LPM_INTREN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTREN);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTREN_LPMNYEN] --> 0x%08x\n",
                        REG_USB_LPM_INTREN,value);
    #endif
    return tmp_value.bitc.lpmnyen;
}
GH_INLINE void GH_USB_set_LPM_INTREN_LPMACKEN(U8 data)
{
    GH_USB_LPM_INTREN_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_INTREN;
    d.bitc.lpmacken = data;
    *(volatile U8 *)REG_USB_LPM_INTREN = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_INTREN_LPMACKEN] <-- 0x%08x\n",
                        REG_USB_LPM_INTREN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_INTREN_LPMACKEN(void)
{
    GH_USB_LPM_INTREN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTREN);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTREN_LPMACKEN] --> 0x%08x\n",
                        REG_USB_LPM_INTREN,value);
    #endif
    return tmp_value.bitc.lpmacken;
}
GH_INLINE void GH_USB_set_LPM_INTREN_LPMNCEN(U8 data)
{
    GH_USB_LPM_INTREN_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_INTREN;
    d.bitc.lpmncen = data;
    *(volatile U8 *)REG_USB_LPM_INTREN = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_INTREN_LPMNCEN] <-- 0x%08x\n",
                        REG_USB_LPM_INTREN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_INTREN_LPMNCEN(void)
{
    GH_USB_LPM_INTREN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTREN);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTREN_LPMNCEN] --> 0x%08x\n",
                        REG_USB_LPM_INTREN,value);
    #endif
    return tmp_value.bitc.lpmncen;
}
GH_INLINE void GH_USB_set_LPM_INTREN_LPMRESEN(U8 data)
{
    GH_USB_LPM_INTREN_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_INTREN;
    d.bitc.lpmresen = data;
    *(volatile U8 *)REG_USB_LPM_INTREN = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_INTREN_LPMRESEN] <-- 0x%08x\n",
                        REG_USB_LPM_INTREN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_INTREN_LPMRESEN(void)
{
    GH_USB_LPM_INTREN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTREN);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTREN_LPMRESEN] --> 0x%08x\n",
                        REG_USB_LPM_INTREN,value);
    #endif
    return tmp_value.bitc.lpmresen;
}
GH_INLINE void GH_USB_set_LPM_INTREN_LPMERREN(U8 data)
{
    GH_USB_LPM_INTREN_S d;
    d.all = *(volatile U8 *)REG_USB_LPM_INTREN;
    d.bitc.lpmerren = data;
    *(volatile U8 *)REG_USB_LPM_INTREN = d.all;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_LPM_INTREN_LPMERREN] <-- 0x%08x\n",
                        REG_USB_LPM_INTREN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_get_LPM_INTREN_LPMERREN(void)
{
    GH_USB_LPM_INTREN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTREN);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTREN_LPMERREN] --> 0x%08x\n",
                        REG_USB_LPM_INTREN,value);
    #endif
    return tmp_value.bitc.lpmerren;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LPM_INTR_PERI (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_LPM_INTR_PERI'. */
U8   GH_USB_get_LPM_INTR_PERI(void);
/*! \brief Reads the bit group 'LPMST' of register 'USB_LPM_INTR_PERI'. */
U8   GH_USB_get_LPM_INTR_PERI_LPMST(void);
/*! \brief Reads the bit group 'LPMNY' of register 'USB_LPM_INTR_PERI'. */
U8   GH_USB_get_LPM_INTR_PERI_LPMNY(void);
/*! \brief Reads the bit group 'LPMACK' of register 'USB_LPM_INTR_PERI'. */
U8   GH_USB_get_LPM_INTR_PERI_LPMACK(void);
/*! \brief Reads the bit group 'LPMNC' of register 'USB_LPM_INTR_PERI'. */
U8   GH_USB_get_LPM_INTR_PERI_LPMNC(void);
/*! \brief Reads the bit group 'LPMRES' of register 'USB_LPM_INTR_PERI'. */
U8   GH_USB_get_LPM_INTR_PERI_LPMRES(void);
/*! \brief Reads the bit group 'LPMERR' of register 'USB_LPM_INTR_PERI'. */
U8   GH_USB_get_LPM_INTR_PERI_LPMERR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_LPM_INTR_PERI(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_PERI);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_PERI] --> 0x%08x\n",
                        REG_USB_LPM_INTR_PERI,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_LPM_INTR_PERI_LPMST(void)
{
    GH_USB_LPM_INTR_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_PERI_LPMST] --> 0x%08x\n",
                        REG_USB_LPM_INTR_PERI,value);
    #endif
    return tmp_value.bitc.lpmst;
}
GH_INLINE U8   GH_USB_get_LPM_INTR_PERI_LPMNY(void)
{
    GH_USB_LPM_INTR_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_PERI_LPMNY] --> 0x%08x\n",
                        REG_USB_LPM_INTR_PERI,value);
    #endif
    return tmp_value.bitc.lpmny;
}
GH_INLINE U8   GH_USB_get_LPM_INTR_PERI_LPMACK(void)
{
    GH_USB_LPM_INTR_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_PERI_LPMACK] --> 0x%08x\n",
                        REG_USB_LPM_INTR_PERI,value);
    #endif
    return tmp_value.bitc.lpmack;
}
GH_INLINE U8   GH_USB_get_LPM_INTR_PERI_LPMNC(void)
{
    GH_USB_LPM_INTR_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_PERI_LPMNC] --> 0x%08x\n",
                        REG_USB_LPM_INTR_PERI,value);
    #endif
    return tmp_value.bitc.lpmnc;
}
GH_INLINE U8   GH_USB_get_LPM_INTR_PERI_LPMRES(void)
{
    GH_USB_LPM_INTR_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_PERI_LPMRES] --> 0x%08x\n",
                        REG_USB_LPM_INTR_PERI,value);
    #endif
    return tmp_value.bitc.lpmres;
}
GH_INLINE U8   GH_USB_get_LPM_INTR_PERI_LPMERR(void)
{
    GH_USB_LPM_INTR_PERI_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_PERI);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_PERI_LPMERR] --> 0x%08x\n",
                        REG_USB_LPM_INTR_PERI,value);
    #endif
    return tmp_value.bitc.lpmerr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LPM_INTR_HOST (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_LPM_INTR_HOST'. */
U8   GH_USB_get_LPM_INTR_HOST(void);
/*! \brief Reads the bit group 'LPMST' of register 'USB_LPM_INTR_HOST'. */
U8   GH_USB_get_LPM_INTR_HOST_LPMST(void);
/*! \brief Reads the bit group 'LPMNY' of register 'USB_LPM_INTR_HOST'. */
U8   GH_USB_get_LPM_INTR_HOST_LPMNY(void);
/*! \brief Reads the bit group 'LPMACK' of register 'USB_LPM_INTR_HOST'. */
U8   GH_USB_get_LPM_INTR_HOST_LPMACK(void);
/*! \brief Reads the bit group 'LPMNC' of register 'USB_LPM_INTR_HOST'. */
U8   GH_USB_get_LPM_INTR_HOST_LPMNC(void);
/*! \brief Reads the bit group 'LPMRES' of register 'USB_LPM_INTR_HOST'. */
U8   GH_USB_get_LPM_INTR_HOST_LPMRES(void);
/*! \brief Reads the bit group 'LPMERR' of register 'USB_LPM_INTR_HOST'. */
U8   GH_USB_get_LPM_INTR_HOST_LPMERR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_LPM_INTR_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_HOST] --> 0x%08x\n",
                        REG_USB_LPM_INTR_HOST,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_LPM_INTR_HOST_LPMST(void)
{
    GH_USB_LPM_INTR_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_HOST_LPMST] --> 0x%08x\n",
                        REG_USB_LPM_INTR_HOST,value);
    #endif
    return tmp_value.bitc.lpmst;
}
GH_INLINE U8   GH_USB_get_LPM_INTR_HOST_LPMNY(void)
{
    GH_USB_LPM_INTR_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_HOST_LPMNY] --> 0x%08x\n",
                        REG_USB_LPM_INTR_HOST,value);
    #endif
    return tmp_value.bitc.lpmny;
}
GH_INLINE U8   GH_USB_get_LPM_INTR_HOST_LPMACK(void)
{
    GH_USB_LPM_INTR_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_HOST_LPMACK] --> 0x%08x\n",
                        REG_USB_LPM_INTR_HOST,value);
    #endif
    return tmp_value.bitc.lpmack;
}
GH_INLINE U8   GH_USB_get_LPM_INTR_HOST_LPMNC(void)
{
    GH_USB_LPM_INTR_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_HOST_LPMNC] --> 0x%08x\n",
                        REG_USB_LPM_INTR_HOST,value);
    #endif
    return tmp_value.bitc.lpmnc;
}
GH_INLINE U8   GH_USB_get_LPM_INTR_HOST_LPMRES(void)
{
    GH_USB_LPM_INTR_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_HOST_LPMRES] --> 0x%08x\n",
                        REG_USB_LPM_INTR_HOST,value);
    #endif
    return tmp_value.bitc.lpmres;
}
GH_INLINE U8   GH_USB_get_LPM_INTR_HOST_LPMERR(void)
{
    GH_USB_LPM_INTR_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_INTR_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_INTR_HOST_LPMERR] --> 0x%08x\n",
                        REG_USB_LPM_INTR_HOST,value);
    #endif
    return tmp_value.bitc.lpmerr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_LPM_FADDR_HOST (read)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_LPM_FADDR_HOST'. */
U8   GH_USB_get_LPM_FADDR_HOST(void);
/*! \brief Reads the bit group 'LPMFADDR' of register 'USB_LPM_FADDR_HOST'. */
U8   GH_USB_get_LPM_FADDR_HOST_LPMFADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_USB_get_LPM_FADDR_HOST(void)
{
    U8 value = (*(volatile U8 *)REG_USB_LPM_FADDR_HOST);

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_FADDR_HOST] --> 0x%08x\n",
                        REG_USB_LPM_FADDR_HOST,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_get_LPM_FADDR_HOST_LPMFADDR(void)
{
    GH_USB_LPM_FADDR_HOST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_USB_LPM_FADDR_HOST);

    tmp_value.all = value;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_LPM_FADDR_HOST_LPMFADDR] --> 0x%08x\n",
                        REG_USB_LPM_FADDR_HOST,value);
    #endif
    return tmp_value.bitc.lpmfaddr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_FIFOs_U32 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_FIFOs_U32'. */
void GH_USB_set_FIFOs_U32(U8 index, U32 data);
/*! \brief Reads the register 'USB_FIFOs_U32'. */
U32  GH_USB_get_FIFOs_U32(U8 index);
#else
GH_INLINE void GH_USB_set_FIFOs_U32(U8 index, U32 data)
{
    *(volatile U32 *)(REG_USB_FIFOS_U32 + index * FIO_MOFFSET(USB,OFFSET_USB_FIFOS_U32)) = data;
    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_set_FIFOs_U32] <-- 0x%08x\n",
                        (REG_USB_FIFOS_U32 + index * FIO_MOFFSET(USB,OFFSET_USB_FIFOS_U32)),data,data);
    #endif
}
GH_INLINE U32  GH_USB_get_FIFOs_U32(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_USB_FIFOS_U32 + index * FIO_MOFFSET(USB,OFFSET_USB_FIFOS_U32)));

    #if GH_USB_ENABLE_DEBUG_PRINT
    GH_USB_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_get_FIFOs_U32] --> 0x%08x\n",
                        (REG_USB_FIFOS_U32 + index * FIO_MOFFSET(USB,OFFSET_USB_FIFOS_U32)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_USB_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_USB_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

