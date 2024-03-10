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

#ifndef __VDOA_H__
#define __VDOA_H__

#include "sdk.h"

//! @addtogroup diag_vdoa
//! @{

//////////////////////////////////////////////////////////////////////////////
// API
//////////////////////////////////////////////////////////////////////////////

/*!
 * @brief Configure the VDOA attribute before transfer start
 *
 * @param width Frame/Field width
 * @param height Frame/Field height
 * @param vpu_sl Strideline for the VPU output memory
 * @param ipu_sl Strideline for the IPU input memory
 * @param interlaced Setting of frame mode, interlaved or progressive
 * @param ipu_sel IPU index selection
 * @param bandLines set the line numbers per band
 * @param pfs Set the pixel format
 */
void vdoa_setup(int width, int height, int vpu_sl, int ipu_sl, int interlaced,
                int ipu_sel, int bandLines, int pfs);

/*!
 * @brief Configure the VDOA for video data transition
 *
 * @param src Source buffer address
 * @param vubo U component offset used for VPU output
 * @param dst Destination buffer address
 * @param iubo U componet offset used for IPU input
 *
 */
void vdoa_start(uint32_t src, uint32_t ubo, uint32_t dst, uint32_t iubo);

/*!
 * @brief Enable VDOA EOT interrupt
 */
void vdoa_enable_interrupt(void);

/*!
 * @brief Disable VDOA EOT interrupt
 */
void vdoa_disable_interrupt(void);

/*!
 * @brief Clear the VDOA EOT(End Of Tranfer) interrupt state
 */
void vdoa_clear_interrupt(void);

/*!
 * @brief Check the VDOA tranfer state
 */
bool vdoa_check_tx_eot(void);

//! @}

#endif

//////////////////////////////////////////////////////////////////////////////
// EOF
//////////////////////////////////////////////////////////////////////////////
