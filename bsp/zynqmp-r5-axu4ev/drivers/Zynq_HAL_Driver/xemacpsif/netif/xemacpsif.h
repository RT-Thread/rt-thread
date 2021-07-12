/*
 * Copyright (C) 2010 - 2019 Xilinx, Inc.
 * Copyright (C) 2021 WangHuachen.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 */

#ifndef __NETIF_XEMACPSIF_H__
#define __NETIF_XEMACPSIF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "xlwipconfig.h"
#include "lwip/netif.h"
#include "netif/etharp.h"
#include "lwip/sys.h"
#include "netif/xadapter.h"

#include "xstatus.h"
#include "sleep.h"
#include "xparameters.h"
#include "xparameters_ps.h"    /* defines XPAR values */
#include "xil_types.h"
#include "xil_assert.h"
#include "xil_io.h"
// #include "xil_exception.h"
// #include "xpseudo_asm.h"
#include "xpseudo_asm_gcc.h"
#include "xil_cache.h"
#include "xil_printf.h"
// #include "xscugic.h"
#include "xemacps.h"        /* defines XEmacPs API */

#include "netif/xpqueue.h"
#include "xlwipconfig.h"

#if EL1_NONSECURE
#include "xil_smc.h"
#endif

#define ZYNQ_EMACPS_0_BASEADDR 0xE000B000
#define ZYNQ_EMACPS_1_BASEADDR 0xE000C000

#define ZYNQMP_EMACPS_0_BASEADDR 0xFF0B0000
#define ZYNQMP_EMACPS_1_BASEADDR 0xFF0C0000
#define ZYNQMP_EMACPS_2_BASEADDR 0xFF0D0000
#define ZYNQMP_EMACPS_3_BASEADDR 0xFF0E0000

#define CRL_APB_GEM0_REF_CTRL    0xFF5E0050
#define CRL_APB_GEM1_REF_CTRL    0xFF5E0054
#define CRL_APB_GEM2_REF_CTRL    0xFF5E0058
#define CRL_APB_GEM3_REF_CTRL    0xFF5E005C

#define CRL_APB_GEM_DIV0_MASK    0x00003F00
#define CRL_APB_GEM_DIV0_SHIFT    8
#define CRL_APB_GEM_DIV1_MASK    0x003F0000
#define CRL_APB_GEM_DIV1_SHIFT    16

#define VERSAL_EMACPS_0_BASEADDR 0xFF0C0000
#define VERSAL_EMACPS_1_BASEADDR 0xFF0D0000

#define VERSAL_CRL_GEM0_REF_CTRL    0xFF5E0118
#define VERSAL_CRL_GEM1_REF_CTRL    0xFF5E011C

#define VERSAL_CRL_GEM_DIV_MASK        0x0003FF00
#define VERSAL_CRL_APB_GEM_DIV_SHIFT    8

#if defined (ARMR5) || (__aarch64__) || (ARMA53_32) || (__MICROBLAZE__)
#if defined (USE_JUMBO_FRAMES)
#define ZYNQMP_USE_JUMBO
#endif
#endif

#define GEM_VERSION_ZYNQMP    7
#define GEM_VERSION_VERSAL    0x107

#define MAX_FRAME_SIZE_JUMBO (XEMACPS_MTU_JUMBO + XEMACPS_HDR_SIZE + XEMACPS_TRL_SIZE)

void     xemacpsif_setmac(u32_t index, u8_t *addr);
u8_t*    xemacpsif_getmac(u32_t index);
err_t     xemacpsif_init(struct netif *netif);
s32_t     xemacpsif_input(struct netif *netif);

/* xaxiemacif_hw.c */
void     xemacps_error_handler(XEmacPs * Temac);

/* structure within each netif, encapsulating all information required for
 * using a particular temac instance
 */
typedef struct {
    XEmacPs emacps;

    /* queue to store overflow packets */
    pq_queue_t *recv_q;
    pq_queue_t *send_q;

    /* pointers to memory holding buffer descriptors (used only with SDMA) */
    void *rx_bdspace;
    void *tx_bdspace;

    unsigned int last_rx_frms_cntr;

} xemacpsif_s;

extern xemacpsif_s xemacpsif;

s32_t    is_tx_space_available(xemacpsif_s *emac);

/* xemacpsif_dma.c */

void  process_sent_bds(xemacpsif_s *xemacpsif, XEmacPs_BdRing *txring);
u32_t phy_setup_emacps (XEmacPs *xemacpsp, u32_t phy_addr);
void detect_phy(XEmacPs *xemacpsp);
void emacps_send_handler(void *arg);
XStatus emacps_sgsend(xemacpsif_s *xemacpsif, struct pbuf *p);
void emacps_recv_handler(void *arg);
void emacps_error_handler(void *arg,u8 Direction, u32 ErrorWord);
void setup_rx_bds(xemacpsif_s *xemacpsif, XEmacPs_BdRing *rxring);
void HandleTxErrors(struct xemac_s *xemac);
void HandleEmacPsError(struct xemac_s *xemac);
XEmacPs_Config *xemacps_lookup_config(unsigned mac_base);
void init_emacps(xemacpsif_s *xemacps, struct netif *netif);
void setup_isr (struct xemac_s *xemac);
XStatus init_dma(struct xemac_s *xemac);
void start_emacps (xemacpsif_s *xemacps);
void free_txrx_pbufs(xemacpsif_s *xemacpsif);
void free_onlytx_pbufs(xemacpsif_s *xemacpsif);
void init_emacps_on_error (xemacpsif_s *xemacps, struct netif *netif);
void clean_dma_txdescs(struct xemac_s *xemac);
void resetrx_on_no_rxdata(xemacpsif_s *xemacpsif);
void reset_dma(struct xemac_s *xemac);

#ifdef __cplusplus
}
#endif

#endif /* __NETIF_XAXIEMACIF_H__ */
