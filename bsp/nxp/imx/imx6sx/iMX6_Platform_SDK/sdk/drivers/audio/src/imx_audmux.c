/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
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

/*!
 * @file imx-audmux.c
 * @brief Driver for AUDMUX.
 *
 * @ingroup diag_audio
 */

#include <stdio.h>
#include "sdk.h"
#include "audio/imx_audmux.h"
#include "imx_audmux_priv.h"
#include "registers/regsaudmux.h"

/*!
 * Dump the registers of audmux
 *
 * @return  always 0 
 */
static uint32_t audmux_dump(void)
{
    uint32_t idx;

    printf("=======================AUDMUX dump===================\n");
    for (idx = AUDMUX_PORT_INDEX_MIN; idx <= AUDMUX_PORT_INDEX_MAX; idx++) {
        printf("PTCR%d: 0x%x\n", idx,  HW_AUDMUX_PTCR_RD(idx));
        printf("PDCR%d: 0x%x\n", idx,  HW_AUDMUX_PDCR_RD(idx));
    }

    return 0;
}

uint32_t audmux_port_set(uint32_t port, uint32_t ptcr, uint32_t pdcr)
{
    if ((port < AUDMUX_PORT_INDEX_MIN) || (port > AUDMUX_PORT_INDEX_MAX)) {
        return -1;
    }

    HW_AUDMUX_PTCR_WR(port, ptcr);
    HW_AUDMUX_PDCR_WR(port, pdcr);

    return 0;
}

uint32_t audmux_route(uint32_t intPort, uint32_t extPort, uint32_t is_master)
{
    if ((intPort < AUDMUX_PORT_INDEX_MIN) || (intPort > AUDMUX_PORT_INDEX_MAX) ||
        (extPort < AUDMUX_PORT_INDEX_MIN) || (extPort > AUDMUX_PORT_INDEX_MAX)) {
        return -1;
    }

    // Configure the Audio MUX internal port to connect with the SSI based
    // upon who is acting as the bus master.
    //
    // But regardless of who is the master, we also configure the internal
    // port for synchronous 4-wire operation in normal mode (which is what
    // we actually need to support the SSI and PMIC for either network or I2S
    // modes).
    //
    // Note that we only configure the transmit framesync and bitclock here
    // because we are using synchronous mode and the receiver clock
    // settings will be determined by the transmitter settings.
    if (AUDMUX_SSI_MASTER == is_master) {
        // All clock signals for the internal port are input signals for
        // SSI master mode.
	HW_AUDMUX_PTCR_WR(intPort, BF_AUDMUX_PTCR1_RFS_DIR(AUDMUX_PTCR_TFSDIR_INPUT) |
               BF_AUDMUX_PTCR1_TCLKDIR(AUDMUX_PTCR_TCLKDIR_INPUT) |
               BF_AUDMUX_PTCR1_SYN(AUDMUX_PTCR_SYN_SYNC));
    } else {
        // All clock signals for the internal port are all output signals for
        //  slave mode. The source of the clock signals is the external
        // port that is connected to the PMIC.
	HW_AUDMUX_PTCR_WR(intPort, BF_AUDMUX_PTCR1_TFS_DIR(AUDMUX_PTCR_TFSDIR_OUTPUT) |
               BF_AUDMUX_PTCR1_TFSEL(extPort - 1) |
               BF_AUDMUX_PTCR1_TCLKDIR(AUDMUX_PTCR_TCLKDIR_OUTPUT) |
               BF_AUDMUX_PTCR1_TCSEL(extPort - 1) |
               BF_AUDMUX_PTCR1_SYN(AUDMUX_PTCR_SYN_SYNC));
    }

    HW_AUDMUX_PDCR_WR(intPort, BF_AUDMUX_PDCR1_RXDSEL(extPort - 1) |
           BF_AUDMUX_PDCR1_TXRXEN(AUDMUX_PDCR_TXRXEN_NO_SWAP) |
           BF_AUDMUX_PDCR1_MODE(AUDMUX_PDCR_MODE_NORMAL));

    // Configure the Audio MUX external port to connect with the PMIC based
    // upon who is acting as the bus master.
    //
    // But regardless of who is the master, we also configure the external
    // port for synchronous 4-wire operation in normal mode (which is what
    // we actually need to support the SSI and PMIC in either network or I2S
    // mode).
    if (AUDMUX_SSI_MASTER == is_master) {
        // All clock signals for the external port are output signals for
        // SSI master mode. The source of the clock signals is the internal
        // port that is connected to the SSI.
	HW_AUDMUX_PTCR_WR(extPort, BF_AUDMUX_PTCR1_TFS_DIR(AUDMUX_PTCR_TFSDIR_OUTPUT) |
               BF_AUDMUX_PTCR1_TFSEL(intPort - 1) |
               BF_AUDMUX_PTCR1_TCLKDIR(AUDMUX_PTCR_TCLKDIR_OUTPUT) |
               BF_AUDMUX_PTCR1_TCSEL(intPort - 1) |
               BF_AUDMUX_PTCR1_SYN(AUDMUX_PTCR_SYN_SYNC));
    } else {
        // All clock signals for the external port are input signals for
        // PMIC master mode.
	HW_AUDMUX_PTCR_WR(extPort, BF_AUDMUX_PTCR1_TFS_DIR(AUDMUX_PTCR_TFSDIR_INPUT) |
               BF_AUDMUX_PTCR1_TCLKDIR(AUDMUX_PTCR_TCLKDIR_INPUT) |
               BF_AUDMUX_PTCR1_SYN(AUDMUX_PTCR_SYN_SYNC));
    }

    HW_AUDMUX_PDCR_WR(extPort, BF_AUDMUX_PDCR1_RXDSEL(intPort - 1) |
           BF_AUDMUX_PDCR1_TXRXEN(AUDMUX_PDCR_TXRXEN_NO_SWAP) |
           BF_AUDMUX_PDCR1_MODE(AUDMUX_PDCR_MODE_NORMAL));

    return 0;
}
