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

//! @addtogroup diag_audio
//! @{

/*! 
 * @file imx-audmux.h
 * @brief imx-audmux public inferface.
 */

#ifndef __AUDMUX_H__
#define __AUDMUX_H__

//! @brief AUDMUX ports supported by i.MX audumx controller
typedef enum {
    AUDMUX_PORT_1 = 1,
    AUDMUX_PORT_2,
    AUDMUX_PORT_3,
    AUDMUX_PORT_4,
    AUDMUX_PORT_5,
    AUDMUX_PORT_6,
    AUDMUX_PORT_7,
} audmux_port_e;

//! @brief AUDMUX modes
typedef enum {
    AUDMUX_SSI_SLAVE = 0,
    AUDMUX_SSI_MASTER,
} audmux_ssi_dir_e;

//////////////////////////////////API functions declaration////////////////////////////////
#if defined(__cplusplus)
extern "C" {
#endif                          // __cplusplus

/*!
 * @breif Set ptcr and pdcr of the audmux port
 *
 * @param   port	the port to be set
 * @param   ptcr	ptcr value to be set
 * @param   pdcr	pdcr value to be set
 * @return  0 if succeeded
 *	    -1 if failed. 
 */
    uint32_t audmux_port_set(uint32_t port, uint32_t ptcr, uint32_t pdcr);

/*!
 * @brief Set audmux port according the ssi mode(master/slave).
 *
 * We set the audumx ports in sync mode which is the default status for most codec.
 * 
 * @param   intPort	the internal port to be set
 * @param   extPort	the external port to be set
 * @param   is_master	ssi mode(master/slave)
 * @return  0 if succeeded
 *	    -1 if failed. 
 */
    uint32_t audmux_route(uint32_t intPort, uint32_t extPort, uint32_t is_master);

#if defined(__cplusplus)
}
#endif                          // __cplusplus
#endif
