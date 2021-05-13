/*
 * Copyright (C) 2007 - 2019 Xilinx, Inc.
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

#ifndef __XTOPOLOGY_H_
#define __XTOPOLOGY_H_

#ifdef __cplusplus
extern "C" {
#endif

enum xemac_types { xemac_type_unknown = -1, xemac_type_xps_emaclite, xemac_type_xps_ll_temac, xemac_type_axi_ethernet, xemac_type_emacps };

struct xtopology_t {
	unsigned emac_baseaddr;
	enum xemac_types emac_type;
	unsigned intc_baseaddr;
	unsigned intc_emac_intr;	/* valid only for xemac_type_xps_emaclite */
	unsigned scugic_baseaddr; /* valid only for Zynq */
	unsigned scugic_emac_intr; /* valid only for GEM */
};

extern int xtopology_n_emacs;
extern struct xtopology_t xtopology[];

int xtopology_find_index(unsigned base);

#ifdef __cplusplus
}
#endif

#endif
