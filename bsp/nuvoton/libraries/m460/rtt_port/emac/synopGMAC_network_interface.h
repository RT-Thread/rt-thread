/* ===================================================================================
 * Copyright (c) <2009> Synopsys, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software annotated with this license and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * =================================================================================== */

/** \file
 * Header file for the nework dependent functionality.
 * The function prototype listed here are linux dependent.
 *
 * \internal
 * ---------------------------REVISION HISTORY-------------------
 * Synopsys             01/Aug/2007     Created
 */
#ifndef SYNOP_GMAC_NETWORK_INTERFACE_H
#define SYNOP_GMAC_NETWORK_INTERFACE_H 1

#include  "synopGMAC_Dev.h"
//#define CACHE_ON

/** Tx/Rx buffer structure */
typedef struct
{
    uint8_t au8Buf[PKT_FRAME_BUF_SIZE];
} PKT_FRAME_T;

s32 synopGMAC_setup_tx_desc_queue(synopGMACdevice *gmacdev, DmaDesc *first_desc, u32 no_of_desc, u32 desc_mode);
s32 synopGMAC_setup_rx_desc_queue(synopGMACdevice *gmacdev, DmaDesc *first_desc, u32 no_of_desc, u32 desc_mode);
s32 synopGMAC_xmit_frames(synopGMACdevice *gmacdev, u8 *pkt_data, u32 pkt_len, u32 offload_needed, u32 ts);
s32 synop_handle_received_data(synopGMACdevice *gmacdev, PKT_FRAME_T **ppsPktFrame);
void synop_handle_transmit_over(synopGMACdevice *gmacdev);
void synopGMAC_set_mode(synopGMACdevice *gmacdev, int mode);
void synopGMAC_powerup_mac(synopGMACdevice *gmacdev);
void synopGMAC_powerdown_mac(synopGMACdevice *gmacdev);

#endif /* End of file */
