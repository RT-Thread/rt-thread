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

/*
 * Copyright (c) 2006, Chips & Media.  All rights reserved.
 */

#ifndef GDI_H_INCLUDED
#define GDI_H_INCLUDED

#include "vpu_lib.h"

//! @addtogroup diag_vpu
//! @{

//////////////////////////////////////////////////////////////////////////////
// DEFINITIONS
//////////////////////////////////////////////////////////////////////////////

enum {
    X_SEL = 0,
    Y_SEL = 1,
};

enum {
    CA_SEL = 0,
    BA_SEL = 1,
    RA_SEL = 2,
    Z_SEL = 3,
};

#define XY2CONFIG(A,B,C,D,E,F,G,H,I) ((A)<<20 | (B)<<19 | (C)<<18 | (D)<<17 | (E)<<16 | (F)<<12 | (G)<<8 | (H)<<4 | (I))
#define XY2(A,B,C,D)                 ((A)<<12 | (B)<<8 | (C)<<4 | (D))
#define XY2BANK(A,B,C,D,E,F)         ((A)<<13 | (B)<<12 | (C)<<8 | (D)<<5 | (E)<<4 | (F))
#define RBC(A,B,C,D)                 ((A)<<10 | (B)<< 6 | (C)<<4 | (D))
#define RBC_SAME(A,B)                ((A)<<10 | (B)<< 6 | (A)<<4 | (B))

//! @brief GDI tiled map structure 
typedef struct {
    int xy2ca_map[16];
    int xy2ba_map[16];
    int xy2ra_map[16];
    int rbc2axi_map[32];
    int MapType;

    int xy2rbc_config;
    int tb_separate_map;
    int top_bot_split;
    int tiledMap;
    int ca_inc_hor;
    int value;
} GdiTiledMap;

//////////////////////////////////////////////////////////////////////////////
// API
//////////////////////////////////////////////////////////////////////////////

/*!
 * @brief Configure the GDI for tiled mode. this is a new feature for imx6. tiled mode will 
 *  lease the burden of bandwidth. but need VDOA to cooperate to convert the data.
 *
 * @param TiledMapType tiled map type
 * @param pTiledInfo tiled information
 *
 * @li RETCODE_SUCCESS Successful operation.
 * @li RETCODE_FAILURE When this happened it means tiled map is not supported!
 */
RetCode SetTiledMapTypeInfo(GDI_TILED_MAP_TYPE TiledMapType, GdiTiledMap * pTiledInfo);

/*!
 * @brief Set the GDI registers.
 *
 * @param pTiledInfo tiled information
 */
void SetGDIRegs(GdiTiledMap * pTiledInfo);

//! @}

#endif

//////////////////////////////////////////////////////////////////////////////
// EOF
//////////////////////////////////////////////////////////////////////////////
