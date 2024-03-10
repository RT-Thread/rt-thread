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

#ifndef __LDB_DEF_H__
#define __LDB_DEF_H__

//! @addtogroup diag_ldb
//! @{

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

//! @brief Enumeration of available BIT mode for LDB
enum lvds_panel_bit_mode {
    LVDS_PANEL_18BITS_MODE = 0x0,
    LVDS_PANEL_24BITS_MODE = 0x1,
};

//! @brief Enumeration of LVDS port mode
//
//! LVDS_DUAL_PORT means the two ports are activated together with duplicated
//! content.
//!
//! LVDS_SPLIT_PORT means the two ports are activated together, one to display
//! the odd columns and the other for even columns
enum lvds_port {
    LVDS_PORT0,
    LVDS_PORT1,
    LVDS_DUAL_PORT,
    LVDS_SPLIT_PORT,
};

//! @brief Enumeration of LVDS bitmap
enum lvds_bitmap {
    SPWG,
    JEIDA,
};

///////////////////////////////////////////////////////////////////////////////
// API
///////////////////////////////////////////////////////////////////////////////

/*!
 * @brief Configure the LVDS bridge to driven the synchronous LVDS panel
 *
 * @param ipu_port IPU display port selection, available value could be IPU<x>_DI<y>
 * @param lvds_port LVDS channel selection
 * @param data_width 18 or 24bit mode selection
 * @param bit_map SPWG or JEIDA mode selection 
 */
void ldb_config(int ipu_port, int lvds_port, int data_width, int bit_map);

/*!
 * @brief Vsync polarity setting
 * 
 * @param ipu_port IPU display port selection, di0 or di1
 * @param vs_pol Vsync polarity setting
 * 
 */
void ldb_set_vs_polarity(int ipu_port, int vs_pol);

//! @}
#endif
///////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////

