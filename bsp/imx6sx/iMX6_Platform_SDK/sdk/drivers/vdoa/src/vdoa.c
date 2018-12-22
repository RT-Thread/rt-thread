/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "vdoa/vdoa.h"
#include "registers/regsvdoa.h"

///////////////////////////////////////////////////////////////////////////////////
// CODE
///////////////////////////////////////////////////////////////////////////////////

void vdoa_setup(int width, int height, int vpu_sl, int ipu_sl, int interlaced,
                int ipu_sel, int bandLines, int pfs)
{
    // Set control register
    uint32_t value = BF_VDOA_VDOAC_PFS(pfs)
        | BF_VDOA_VDOAC_ISEL(ipu_sel);

    switch (bandLines) {
    case 32:
        value |= BF_VDOA_VDOAC_BNDM(2);
        break;
    case 16:
        value |= BF_VDOA_VDOAC_BNDM(1);
        break;
    default:
        value |= BF_VDOA_VDOAC_BNDM(0);
        break;
    }

    if (interlaced) {
        value |= /*BM_VDOA_VDOAC_NF | */ BM_VDOA_VDOAC_SO;
    }

    HW_VDOA_VDOAC_WR(value);

    // VDOA frame parameters register
    HW_VDOA_VDOAFP_WR(BF_VDOA_VDOAFP_FW(width)
                      | BF_VDOA_VDOAFP_FH(height));

    // VDOA stride line register
    HW_VDOA_VDOASL_WR(BF_VDOA_VDOASL_ISLY(ipu_sl)
                      | BF_VDOA_VDOASL_VSLY(vpu_sl));
}

static void vdoa_set_vpu_buffer(uint32_t vbuf)
{
    if (!HW_VDOA_VDOAC.B.SYNC) {
        HW_VDOA_VDOAVEBA0_WR(vbuf);
    }
}

static void vdoa_set_ipu_buffer(uint32_t ibuf)
{
    HW_VDOA_VDOAIEBA00_WR(ibuf);
}

static void vdoa_set_vpu_ubo(uint32_t vubo)
{
    HW_VDOA_VDOAVUBO_WR(vubo);
}

static void vdoa_set_ipu_ubo(uint32_t iubo)
{
    HW_VDOA_VDOAIUBO_WR(iubo);
}

static void vdoa_start_transfer(void)
{
    HW_VDOA_VDOASRR.B.START = 1;
}

void vdoa_enable_interrupt(void)
{
    HW_VDOA_VDOAIE.B.EIEOT = 1;
}

void vdoa_disable_interrupt(void)
{
    HW_VDOA_VDOAIE.B.EIEOT = 0;
}

void vdoa_clear_interrupt(void)
{
    HW_VDOA_VDOAIST.B.EOT = 1;
}

bool vdoa_check_tx_eot(void)
{
    return (HW_VDOA_VDOAIST.B.EOT == 1);
}

void vdoa_start(uint32_t src, uint32_t vubo, uint32_t dst, uint32_t iubo)
{
    // set the source
    vdoa_set_vpu_buffer(src);
    vdoa_set_vpu_ubo(vubo);

	// set the destination
    vdoa_set_ipu_buffer(dst);
    vdoa_set_ipu_ubo(iubo);

    // start transfer
    vdoa_start_transfer();
}

///////////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////////
