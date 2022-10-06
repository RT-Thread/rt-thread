

/**
 *  @Component:   CPSW
 *
 *  @Filename:    cpsw_ss_cred.h
 *
 ============================================================================ */
/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/



#ifndef _HW_CPSW_SS_H_
#define _HW_CPSW_SS_H_

#ifdef __cplusplus
extern "C" {
#endif


/***********************************************************************\
 * Register arrays Definition
\***********************************************************************/


/***********************************************************************\
 * Bundle arrays Definition
\***********************************************************************/


/***********************************************************************\
 * Bundles Definition
\***********************************************************************/



/*************************************************************************\
 * Registers Definition
\*************************************************************************/

#define CPSW_SS_ID_VER   (0x0)
#define CPSW_SS_CONTROL   (0x4)
#define CPSW_SS_SOFT_RESET   (0x8)
#define CPSW_SS_STAT_PORT_EN   (0xc)
#define CPSW_SS_PTYPE   (0x10)
#define CPSW_SS_SOFT_IDLE   (0x14)
#define CPSW_SS_THRU_RATE   (0x18)
#define CPSW_SS_GAP_THRESH   (0x1c)
#define CPSW_SS_TX_START_WDS   (0x20)
#define CPSW_SS_FLOW_CONTROL   (0x24)
#define CPSW_SS_VLAN_LTYPE   (0x28)
#define CPSW_SS_TS_LTYPE   (0x2c)
#define CPSW_SS_DLR_LTYPE   (0x30)

/**************************************************************************\
 * Field Definition Macros
\**************************************************************************/

/* ID_VER */
#define CPSW_SS_ID_VER_CPSW_3G_IDENT   (0xFFFF0000u)
#define CPSW_SS_ID_VER_CPSW_3G_IDENT_SHIFT   (0x00000010u)

#define CPSW_SS_ID_VER_CPSW_3G_MAJ_VER   (0x00000700u)
#define CPSW_SS_ID_VER_CPSW_3G_MAJ_VER_SHIFT   (0x00000008u)

#define CPSW_SS_ID_VER_CPSW_3G_MINOR_VER   (0x000000FFu)
#define CPSW_SS_ID_VER_CPSW_3G_MINOR_VER_SHIFT   (0x00000000u)

#define CPSW_SS_ID_VER_CPSW_3G_RTL_VER   (0x0000F800u)
#define CPSW_SS_ID_VER_CPSW_3G_RTL_VER_SHIFT   (0x0000000Bu)


/* CONTROL */
#define CPSW_SS_CONTROL_DLR_EN   (0x00000008u)
#define CPSW_SS_CONTROL_DLR_EN_SHIFT   (0x00000003u)

#define CPSW_SS_CONTROL_FIFO_LOOPBACK   (0x00000001u)
#define CPSW_SS_CONTROL_FIFO_LOOPBACK_SHIFT   (0x00000000u)

#define CPSW_SS_CONTROL_RX_VLAN_ENCAP   (0x00000004u)
#define CPSW_SS_CONTROL_RX_VLAN_ENCAP_SHIFT   (0x00000002u)

#define CPSW_SS_CONTROL_VLAN_AWARE   (0x00000002u)
#define CPSW_SS_CONTROL_VLAN_AWARE_SHIFT   (0x00000001u)


/* SOFT_RESET */
#define CPSW_SS_SOFT_RESET_SOFT_RESET   (0x00000001u)
#define CPSW_SS_SOFT_RESET_SOFT_RESET_SHIFT   (0x00000000u)


/* STAT_PORT_EN */
#define CPSW_SS_STAT_PORT_EN_P0_STAT_EN   (0x00000001u)
#define CPSW_SS_STAT_PORT_EN_P0_STAT_EN_SHIFT   (0x00000000u)

#define CPSW_SS_STAT_PORT_EN_P1_STAT_EN   (0x00000002u)
#define CPSW_SS_STAT_PORT_EN_P1_STAT_EN_SHIFT   (0x00000001u)

#define CPSW_SS_STAT_PORT_EN_P2_STAT_EN   (0x00000004u)
#define CPSW_SS_STAT_PORT_EN_P2_STAT_EN_SHIFT   (0x00000002u)


/* PTYPE */
#define CPSW_SS_PTYPE_ESC_PRI_LD_VAL   (0x0000001Fu)
#define CPSW_SS_PTYPE_ESC_PRI_LD_VAL_SHIFT   (0x00000000u)

#define CPSW_SS_PTYPE_P0_PTYPE_ESC   (0x00000100u)
#define CPSW_SS_PTYPE_P0_PTYPE_ESC_SHIFT   (0x00000008u)

#define CPSW_SS_PTYPE_P1_PRI1_SHAPE_EN   (0x00010000u)
#define CPSW_SS_PTYPE_P1_PRI1_SHAPE_EN_SHIFT   (0x00000010u)

#define CPSW_SS_PTYPE_P1_PRI2_SHAPE_EN   (0x00020000u)
#define CPSW_SS_PTYPE_P1_PRI2_SHAPE_EN_SHIFT   (0x00000011u)

#define CPSW_SS_PTYPE_P1_PRI3_SHAPE_EN   (0x00040000u)
#define CPSW_SS_PTYPE_P1_PRI3_SHAPE_EN_SHIFT   (0x00000012u)

#define CPSW_SS_PTYPE_P1_PTYPE_ESC   (0x00000200u)
#define CPSW_SS_PTYPE_P1_PTYPE_ESC_SHIFT   (0x00000009u)

#define CPSW_SS_PTYPE_P2_PRI1_SHAPE_EN   (0x00080000u)
#define CPSW_SS_PTYPE_P2_PRI1_SHAPE_EN_SHIFT   (0x00000013u)

#define CPSW_SS_PTYPE_P2_PRI2_SHAPE_EN   (0x00100000u)
#define CPSW_SS_PTYPE_P2_PRI2_SHAPE_EN_SHIFT   (0x00000014u)

#define CPSW_SS_PTYPE_P2_PRI3_SHAPE_EN   (0x00200000u)
#define CPSW_SS_PTYPE_P2_PRI3_SHAPE_EN_SHIFT   (0x00000015u)

#define CPSW_SS_PTYPE_P2_PTYPE_ESC   (0x00000400u)
#define CPSW_SS_PTYPE_P2_PTYPE_ESC_SHIFT   (0x0000000Au)


/* SOFT_IDLE */
#define CPSW_SS_SOFT_IDLE_SOFT_IDLE   (0x00000001u)
#define CPSW_SS_SOFT_IDLE_SOFT_IDLE_SHIFT   (0x00000000u)


/* THRU_RATE */
#define CPSW_SS_THRU_RATE_CPDMA_THRU_RATE   (0x0000000Fu)
#define CPSW_SS_THRU_RATE_CPDMA_THRU_RATE_SHIFT   (0x00000000u)

#define CPSW_SS_THRU_RATE_SL_RX_THRU_RATE   (0x0000F000u)
#define CPSW_SS_THRU_RATE_SL_RX_THRU_RATE_SHIFT   (0x0000000Cu)


/* GAP_THRESH */
#define CPSW_SS_GAP_THRESH_GAP_THRESH   (0x0000001Fu)
#define CPSW_SS_GAP_THRESH_GAP_THRESH_SHIFT   (0x00000000u)


/* TX_START_WDS */
#define CPSW_SS_TX_START_WDS_TX_START_WDS   (0x000007FFu)
#define CPSW_SS_TX_START_WDS_TX_START_WDS_SHIFT   (0x00000000u)


/* FLOW_CONTROL */
#define CPSW_SS_FLOW_CONTROL_P0_FLOW_EN   (0x00000001u)
#define CPSW_SS_FLOW_CONTROL_P0_FLOW_EN_SHIFT   (0x00000000u)

#define CPSW_SS_FLOW_CONTROL_P1_FLOW_EN   (0x00000002u)
#define CPSW_SS_FLOW_CONTROL_P1_FLOW_EN_SHIFT   (0x00000001u)

#define CPSW_SS_FLOW_CONTROL_P2_FLOW_EN   (0x00000004u)
#define CPSW_SS_FLOW_CONTROL_P2_FLOW_EN_SHIFT   (0x00000002u)


/* VLAN_LTYPE */
#define CPSW_SS_VLAN_LTYPE_VLAN_LTYPE1   (0x0000FFFFu)
#define CPSW_SS_VLAN_LTYPE_VLAN_LTYPE1_SHIFT   (0x00000000u)

#define CPSW_SS_VLAN_LTYPE_VLAN_LTYPE2   (0xFFFF0000u)
#define CPSW_SS_VLAN_LTYPE_VLAN_LTYPE2_SHIFT   (0x00000010u)


/* TS_LTYPE */
#define CPSW_SS_TS_LTYPE_TS_LTYPE1   (0x0000FFFFu)
#define CPSW_SS_TS_LTYPE_TS_LTYPE1_SHIFT   (0x00000000u)

#define CPSW_SS_TS_LTYPE_TS_LTYPE2   (0x003F0000u)
#define CPSW_SS_TS_LTYPE_TS_LTYPE2_SHIFT   (0x00000010u)


/* DLR_LTYPE */
#define CPSW_SS_DLR_LTYPE_DLR_LTYPE   (0x0000FFFFu)
#define CPSW_SS_DLR_LTYPE_DLR_LTYPE_SHIFT   (0x00000000u)



#ifdef __cplusplus
}
#endif

#endif
